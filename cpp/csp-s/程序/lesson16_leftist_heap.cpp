/**
 * 第16课：可并堆与左偏树（Leftist Heap / Meldable Heap）
 * 对应CSP-S考纲知识点：
 *   - 左偏树（Leftist Heap）的原理与性质
 *   - npl（Null Path Length / dist）的维护
 *   - 合并（merge / meld）操作：O(log n)
 *   - 插入、删除堆顶（基于合并实现）
 *   - 经典问题：猴子打架（Monkey King）— 左偏树 + 并查集
 *
 * 包含以下实现：
 *   1. 左偏树模板（小根堆 + 大根堆）
 *   2. 猴子打架（HDU 1512）AC 代码
 *   3. 动态组最小值维护
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;  // 猴子打架需要动态创建节点，开大一些

// ============================================================
// 一、左偏树模板（小根堆）
// 节点：val(值), lc(左儿子), rc(右儿子), dist(npl)
// ============================================================
struct LeftistHeap {
    vector<int> val, lc, rc, dist;

    LeftistHeap() {
        // 0 号节点为空节点
        val.push_back(0);
        lc.push_back(0);
        rc.push_back(0);
        dist.push_back(0);
    }

    // 创建新节点，返回编号
    int new_node(int v) {
        val.push_back(v);
        lc.push_back(0);
        rc.push_back(0);
        dist.push_back(0);
        return val.size() - 1;
    }

    // 合并两棵左偏树，返回新根
    int merge(int x, int y) {
        if (!x || !y) return x + y;        // 一方为空
        if (val[x] > val[y]) swap(x, y);   // 小根堆：根较小者在上
        rc[x] = merge(rc[x], y);           // 递归合并右儿子
        // 维护左偏性质
        if (dist[lc[x]] < dist[rc[x]]) swap(lc[x], rc[x]);
        // 更新 dist
        dist[x] = dist[rc[x]] + 1;
        return x;
    }

    // 插入值，返回新根
    int push(int root, int v) {
        return merge(root, new_node(v));
    }

    // 删除堆顶，返回新根
    int pop(int root) {
        return merge(lc[root], rc[root]);
    }

    // 获取堆顶值
    int top(int root) {
        return val[root];
    }

    // 判断是否为空
    bool empty(int root) {
        return root == 0;
    }
};

// ============================================================
// 二、左偏树模板（大根堆版本，用于猴子打架）
// 只需修改 merge 中的比较方向
// ============================================================
struct LeftistHeapMax {
    vector<int> val, lc, rc, dist;

    LeftistHeapMax() {
        val.push_back(0); lc.push_back(0);
        rc.push_back(0); dist.push_back(0);
    }

    int new_node(int v) {
        val.push_back(v); lc.push_back(0);
        rc.push_back(0); dist.push_back(0);
        return val.size() - 1;
    }

    int merge(int x, int y) {
        if (!x || !y) return x + y;
        if (val[x] < val[y]) swap(x, y);   // 大根堆：根较大者在上
        rc[x] = merge(rc[x], y);
        if (dist[lc[x]] < dist[rc[x]]) swap(lc[x], rc[x]);
        dist[x] = dist[rc[x]] + 1;
        return x;
    }

    int push(int root, int v) { return merge(root, new_node(v)); }

    int pop(int root) { return merge(lc[root], rc[root]); }

    int top(int root) { return val[root]; }
};

// ============================================================
// 三、并查集模板（用于配合左偏树）
// ============================================================
struct DSU {
    vector<int> fa;
    DSU(int n) : fa(n + 1) {
        for (int i = 1; i <= n; i++) fa[i] = i;
    }
    int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
    void unite(int x, int y) { fa[find(y)] = find(x); }
};

// ============================================================
// 经典问题一：猴子打架（Monkey King / HDU 1512）
// 算法：
//   1. 并查集维护朋友圈
//   2. 每个朋友圈用一个大根左偏树维护强壮值
//   3. 打架：取出最强 → 减半 → 放回 → 合并两个堆
// ============================================================
void solve_monkey_king() {
    int n;
    while (cin >> n) {
        LeftistHeapMax heap;
        DSU dsu(n);
        vector<int> root(n + 1, 0);  // 每个猴子朋友圈的左偏树根

        // 初始每只猴子自成一个堆
        for (int i = 1; i <= n; i++) {
            int v; cin >> v;
            root[i] = heap.new_node(v);
        }

        int m; cin >> m;
        while (m--) {
            int x, y; cin >> x >> y;
            int fx = dsu.find(x), fy = dsu.find(y);

            if (fx == fy) {
                cout << "-1\n";
                continue;
            }

            // 处理 fx 圈：取出最强猴子，减半，放回
            int rx = root[fx];
            int strongest_x = heap.top(rx);
            root[fx] = heap.pop(rx);
            int new_x = heap.new_node(strongest_x / 2);
            root[fx] = heap.merge(root[fx], new_x);

            // 处理 fy 圈：取出最强猴子，减半，放回
            int ry = root[fy];
            int strongest_y = heap.top(ry);
            root[fy] = heap.pop(ry);
            int new_y = heap.new_node(strongest_y / 2);
            root[fy] = heap.merge(root[fy], new_y);

            // 合并两个朋友圈
            dsu.unite(fx, fy);
            root[fx] = heap.merge(root[fx], root[fy]);

            // 输出新圈中最强猴子的强壮值
            cout << heap.top(root[fx]) << '\n';
        }
    }
}

// ============================================================
// 经典问题二：动态组最小值维护
// 操作：
//   1 a b  : 合并组 a 和组 b
//   2 a    : 查询组 a 的最小值并删除
//   3 a v  : 向组 a 插入值 v
// ============================================================
void solve_group_min() {
    int n, q;
    cin >> n >> q;

    LeftistHeap heap;
    DSU dsu(n);
    vector<int> root(n + 1, 0);

    // 初始每组一个数
    for (int i = 1; i <= n; i++) {
        int v; cin >> v;
        root[i] = heap.new_node(v);
    }

    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int a, b; cin >> a >> b;
            int fa = dsu.find(a), fb = dsu.find(b);
            if (fa == fb) continue;
            dsu.unite(fa, fb);
            root[fa] = heap.merge(root[fa], root[fb]);
        } else if (op == 2) {
            int a; cin >> a;
            int fa = dsu.find(a);
            if (heap.empty(root[fa])) {
                cout << "-1\n";
                continue;
            }
            cout << heap.top(root[fa]) << '\n';
            root[fa] = heap.pop(root[fa]);
        } else if (op == 3) {
            int a, v; cin >> a >> v;
            int fa = dsu.find(a);
            root[fa] = heap.push(root[fa], v);
        }
    }
}

// ============================================================
// 四、测试与示例程序
// ============================================================

// 左偏树基本功能测试
void test_leftist_heap() {
    LeftistHeap heap;
    int root = 0;

    cout << "左偏树测试（小根堆）：\n";
    vector<int> vals = {5, 3, 8, 1, 9, 2, 7};
    for (int v : vals) root = heap.push(root, v);

    cout << "依次弹出（升序）：";
    while (!heap.empty(root)) {
        cout << heap.top(root) << " ";
        root = heap.pop(root);
    }
    cout << '\n';

    // 合并测试
    cout << "合并测试：\n";
    int h1 = 0, h2 = 0;
    h1 = heap.push(h1, 10); h1 = heap.push(h1, 4);
    h2 = heap.push(h2, 3);  h2 = heap.push(h2, 8);
    int merged = heap.merge(h1, h2);
    cout << "合并后堆顶（应为 3）：" << heap.top(merged) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // test_leftist_heap();    // 基本功能测试
    // solve_monkey_king();    // 猴子打架
    // solve_group_min();      // 动态组最小值

    return 0;
}
