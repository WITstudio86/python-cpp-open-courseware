/**
 * 第14课：带权并查集与扩展域
 * 对应CSP-S考纲知识点：
 *   - 种类并查集（扩展域）：2倍/3倍空间法
 *   - 边带权并查集：维护节点到父节点的关系值
 *   - 关系传递与推导（模运算）
 *   - 经典问题：食物链（模3）、关押罪犯（模2）、奇偶性判定
 *
 * 包含以下实现：
 *   1. 扩展域并查集（食物链，3倍空间）
 *   2. 边带权并查集模板（模 m 关系）
 *   3. 扩展域并查集（XOR 奇偶性，2倍空间）
 *   4. 关押罪犯（2倍空间）
 */

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// 一、扩展域并查集 — 食物链（3 类，3 倍空间）
// 将每个动物 x 拆成 3 个域：
//   x       : x 属于 A 类
//   x + n   : x 属于 B 类
//   x + 2n  : x 属于 C 类
// ============================================================
class FoodChain_DSU {
private:
    vector<int> fa;

    int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }

    void unite(int x, int y) {
        fa[find(x)] = find(y);
    }

public:
    int n;
    FoodChain_DSU(int sz) : n(sz) {
        fa.resize(3 * n + 1);
        for (int i = 1; i <= 3 * n; i++) fa[i] = i;
    }

    // 判断同类：1 x y
    // 返回 true 表示可以接受，false 表示矛盾
    bool set_same(int x, int y) {
        if (x > n || y > n) return false;
        // 矛盾：x 在 A 而 y 在 B，或 x 在 A 而 y 在 C
        if (find(x) == find(y + n) || find(x) == find(y + 2 * n))
            return false;
        // 合并且三个域
        unite(x, y);
        unite(x + n, y + n);
        unite(x + 2 * n, y + 2 * n);
        return true;
    }

    // 判断 x 吃 y（2 x y）
    bool set_eat(int x, int y) {
        if (x > n || y > n || x == y) return false;
        // 矛盾：同类，或 y 吃 x（x在A且y在C 等价于 y吃x）
        if (find(x) == find(y) || find(x) == find(y + 2 * n))
            return false;
        // A吃B, B吃C, C吃A
        unite(x, y + n);           // x是A → y是B
        unite(x + n, y + 2 * n);   // x是B → y是C
        unite(x + 2 * n, y);       // x是C → y是A
        return true;
    }

    // 查询 x 和 y 的关系
    // 返回: 0=同类, 1=x吃y, 2=y吃x, -1=未知
    int relation(int x, int y) {
        if (find(x) == find(y)) return 0;
        if (find(x) == find(y + n)) return 1;
        if (find(x + n) == find(y)) return 2;
        return -1;
    }
};

// ============================================================
// 二、边带权并查集模板（通用模 m 关系）
// d[x]: x 与 fa[x] 的关系值（模 m 意义下）
// 关系值的含义由题目定义（如：0同类，1吃，2被吃）
// ============================================================
class WeightedDSU {
private:
    vector<int> fa, d;
    int mod;

    int find(int x) {
        if (fa[x] == x) return x;
        int root = find(fa[x]);         // 先递归
        d[x] = (d[x] + d[fa[x]]) % mod; // 再更新 d[x]
        return fa[x] = root;
    }

public:
    WeightedDSU(int sz, int m) : mod(m) {
        fa.resize(sz + 1);
        d.resize(sz + 1, 0);
        for (int i = 1; i <= sz; i++) fa[i] = i;
    }

    // 合并 x 和 y，x 对 y 的关系为 rel（0≤rel<mod）
    // 返回 true 成功，false 矛盾
    bool unite(int x, int y, int rel) {
        int fx = find(x), fy = find(y);
        if (fx == fy) {
            // 检查一致性：d[x] - d[y] ≡ rel (mod mod)
            return ((d[x] - d[y]) % mod + mod) % mod == rel;
        }
        fa[fx] = fy;
        // 推导 d[fx]: fx → fy
        // d[fx] = d[y] - d[x] + rel (mod mod)
        d[fx] = ((d[y] - d[x] + rel) % mod + mod) % mod;
        return true;
    }

    // 查询 x 和 y 的关系（需要先 find 更新）
    int relation(int x, int y) {
        find(x); find(y);
        return ((d[x] - d[y]) % mod + mod) % mod;
    }

    bool same(int x, int y) { return find(x) == find(y); }
};

// ============================================================
// 三、扩展域并查集 — 奇偶性判定 / 关押罪犯（2 类，2 倍空间）
// 用于维护两个互斥类别，如：
//   x     : x = 0 或 x 属于集合 1
//   x + n : x = 1 或 x 属于集合 2
// ============================================================
class BinaryRelation_DSU {
private:
    vector<int> fa;
    int n;

    int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }

    void unite(int x, int y) {
        fa[find(x)] = find(y);
    }

public:
    BinaryRelation_DSU(int sz) : n(sz) {
        fa.resize(2 * n + 1);
        for (int i = 1; i <= 2 * n; i++) fa[i] = i;
    }

    // 设置 x 和 y 相同（同类 / XOR=0）
    // 返回 false 表示矛盾
    bool set_same(int x, int y) {
        if (find(x) == find(y + n)) return false;  // 矛盾：本来不同
        unite(x, y);
        unite(x + n, y + n);
        return true;
    }

    // 设置 x 和 y 不同（异类 / XOR=1 / 敌人）
    bool set_diff(int x, int y) {
        if (find(x) == find(y)) return false;      // 矛盾：本来相同
        unite(x, y + n);
        unite(x + n, y);
        return true;
    }

    // 查询 x 和 y 是否同类
    bool is_same(int x, int y) {
        return find(x) == find(y);
    }

    // 检查 x 本身是否矛盾（x 既为 0 又为 1）
    bool is_consistent(int x) {
        return find(x) != find(x + n);
    }
};

// ============================================================
// 四、测试与示例程序
// ============================================================

// 示例1：食物链（NOI 2001）— 扩展域法
void solve_food_chain() {
    int n, k;
    cin >> n >> k;
    FoodChain_DSU dsu(n);
    int ans = 0;

    while (k--) {
        int op, x, y;
        cin >> op >> x >> y;
        if (x > n || y > n) {
            ans++;
            continue;
        }
        if (op == 1) {
            if (!dsu.set_same(x, y)) ans++;
        } else {
            if (!dsu.set_eat(x, y)) ans++;
        }
    }
    cout << ans << '\n';
}

// 示例2：食物链 — 边带权法（模 3）
void solve_food_chain_weighted() {
    int n, k;
    cin >> n >> k;
    // 0: 同类, 1: x吃y, 2: y吃x
    WeightedDSU dsu(n, 3);
    int ans = 0;

    while (k--) {
        int op, x, y;
        cin >> op >> x >> y;
        if (x > n || y > n) { ans++; continue; }
        if (op == 1) {
            if (!dsu.unite(x, y, 0)) ans++;
        } else {
            if (x == y) { ans++; continue; }
            if (!dsu.unite(x, y, 1)) ans++;
        }
    }
    cout << ans << '\n';
}

// 示例3：奇偶性判定（XOR 关系，2倍空间）
void solve_xor_parity() {
    int n, m;
    cin >> n >> m;
    BinaryRelation_DSU dsu(n);

    bool ok = true;
    while (m--) {
        int x, y, p;
        cin >> x >> y >> p;
        if (p == 0) {  // x XOR y = 0 → 相同
            if (!dsu.set_same(x, y)) { ok = false; break; }
        } else {       // x XOR y = 1 → 不同
            if (!dsu.set_diff(x, y)) { ok = false; break; }
        }
    }
    cout << (ok ? "Yes\n" : "No\n");
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // solve_food_chain();            // 食物链（扩展域）
    // solve_food_chain_weighted();   // 食物链（带权）
    // solve_xor_parity();            // 奇偶性判定

    return 0;
}
