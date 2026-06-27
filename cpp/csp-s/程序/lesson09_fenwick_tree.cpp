/**
 * 第09课：树状数组（Fenwick Tree / Binary Indexed Tree）
 * 对应CSP-S考纲知识点：
 *   - 树状数组的基本操作（单点修改、区间查询）
 *   - 区间修改与单点查询（差分树状数组）
 *   - 二维树状数组
 *   - 逆序对计数
 *
 * 包含以下实现：
 *   1. 一维树状数组模板（单点修改 + 区间查询）
 *   2. 差分树状数组（区间修改 + 单点查询）
 *   3. 二维树状数组模板
 *   4. 逆序对计数（排列版 + 离散化版）
 *   5. 树状数组求第K小数
 */

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// 一、一维树状数组模板
// 功能：单点修改、区间查询
// 时间复杂度：单次操作 O(log n)
// 下标要求：从 1 开始
// ============================================================
struct FenwickTree {
    int n;
    vector<long long> c;

    FenwickTree(int sz) : n(sz), c(sz + 2, 0) {}

    int lowbit(int x) { return x & (-x); }

    // 单点修改：位置 x 增加 v
    void add(int x, long long v) {
        while (x <= n) {
            c[x] += v;
            x += lowbit(x);
        }
    }

    // 前缀和查询：sum[1..x]
    long long sum(int x) {
        long long res = 0;
        while (x > 0) {
            res += c[x];
            x -= lowbit(x);
        }
        return res;
    }

    // 区间和查询：sum[l..r]
    long long range_sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};

// ============================================================
// 二、差分树状数组
// 功能：区间修改（加）、单点查询
// 原理：维护差分数组 d[i] = a[i] - a[i-1]
//       区间 [l, r] +v → d[l] += v, d[r+1] -= v
//       单点查询 a[x] = sum_d[1..x]
// ============================================================
struct DiffFenwick {
    int n;
    vector<long long> c;

    DiffFenwick(int sz) : n(sz), c(sz + 2, 0) {}

    int lowbit(int x) { return x & (-x); }

    void _add(int x, long long v) {
        while (x <= n) {
            c[x] += v;
            x += lowbit(x);
        }
    }

    // 区间 [l, r] 全部加 v
    void range_add(int l, int r, long long v) {
        _add(l, v);
        _add(r + 1, -v);
    }

    // 单点查询 a[x]
    long long point_query(int x) {
        long long res = 0;
        while (x > 0) {
            res += c[x];
            x -= lowbit(x);
        }
        return res;
    }

    // 建立差分树状数组（从原数组初始化）
    void build(const vector<long long>& a) {
        for (int i = 1; i <= n; i++) {
            _add(i, a[i] - a[i - 1]);
        }
    }
};

// ============================================================
// 三、二维树状数组模板
// 功能：二维单点修改、子矩阵求和
// 时间复杂度：单次操作 O(log n * log m)
// 注意：n, m 建议不超过 2000，否则 MLE
// ============================================================
const int MAXN = 1005;
struct Fenwick2D {
    int n, m;
    long long c[MAXN][MAXN];

    Fenwick2D() : n(0), m(0) { memset(c, 0, sizeof(c)); }
    Fenwick2D(int r, int col) : n(r), m(col) { memset(c, 0, sizeof(c)); }

    int lowbit(int x) { return x & (-x); }

    // 单点修改：位置 (x, y) 增加 v
    void add(int x, int y, long long v) {
        for (int i = x; i <= n; i += lowbit(i))
            for (int j = y; j <= m; j += lowbit(j))
                c[i][j] += v;
    }

    // 二维前缀和：sum[(1,1) .. (x,y)]
    long long sum(int x, int y) {
        long long res = 0;
        for (int i = x; i > 0; i -= lowbit(i))
            for (int j = y; j > 0; j -= lowbit(j))
                res += c[i][j];
        return res;
    }

    // 子矩阵查询：sum[(x1,y1) .. (x2,y2)]
    long long query(int x1, int y1, int x2, int y2) {
        return sum(x2, y2) - sum(x1 - 1, y2)
             - sum(x2, y1 - 1) + sum(x1 - 1, y1 - 1);
    }
};

// ============================================================
// 四、逆序对计数
// 4.1 排列版（值域为 [1..n]，无需离散化）
// ============================================================
long long count_inversions_permutation(const vector<int>& a) {
    int n = a.size();
    // BIT 数组，下标从 1 开始
    vector<int> bit(n + 2, 0);
    auto lowbit = [](int x) { return x & (-x); };
    auto add = [&](int x, int v) {
        while (x <= n) { bit[x] += v; x += lowbit(x); }
    };
    auto sum = [&](int x) {
        int res = 0;
        while (x > 0) { res += bit[x]; x -= lowbit(x); }
        return res;
    };

    // 从右向左遍历：对于 a[i]，查询 BIT 中比 a[i] 小的元素个数
    long long ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        ans += sum(a[i] - 1);       // 小于 a[i] 的、已在 BIT 中的元素
        add(a[i], 1);
    }
    return ans;
}

// 4.2 通用版（值域任意，需离散化）
long long count_inversions_general(vector<int>& a) {
    int n = a.size();
    // 离散化：将值映射到 [1..n]
    vector<int> b = a;
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    int m = b.size();

    vector<int> bit(m + 2, 0);
    auto lowbit = [](int x) { return x & (-x); };
    auto add = [&](int x, int v) {
        while (x <= m) { bit[x] += v; x += lowbit(x); }
    };
    auto sum = [&](int x) {
        int res = 0;
        while (x > 0) { res += bit[x]; x -= lowbit(x); }
        return res;
    };

    long long ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        int rank = lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1;
        ans += sum(rank - 1);
        add(rank, 1);
    }
    return ans;
}

// ============================================================
// 五、树状数组求第 K 小数
// 原理：在值域 [1..n] 上通过二进制倍增寻找前缀和达到 k 的最小位置
// 时间复杂度：O(log n)
// 注意：此方法要求 BIT 维护的是每个值的出现次数
// ============================================================
int kth_smallest(const vector<int>& bit, int n, int k) {
    // bit 必须是一个 FenwickTree 的内部数组，这里演示倍增法
    // 使用引用数组中已存储的数据
    // 实际使用请配合 FenwickTree 结构体调用
    int pos = 0;
    int max_pow = 1;
    while (max_pow <= n) max_pow <<= 1;
    max_pow >>= 1;

    for (int step = max_pow; step > 0; step >>= 1) {
        int nxt = pos + step;
        if (nxt <= n && bit[nxt] < k) {
            k -= bit[nxt];
            pos = nxt;
        }
    }
    return pos + 1;
}

// ============================================================
// 六、测试用 main 函数（CSP-S 真题模拟）
// ============================================================

// 题目1：逆序对计数（n ≤ 5e5，排列）
void solve_problem1() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    cout << count_inversions_permutation(a) << '\n';
}

// 题目2：二维矩阵操作（n, m ≤ 1000, q ≤ 1e5）
void solve_problem2() {
    int n, m, q;
    cin >> n >> m >> q;
    Fenwick2D ft(n, m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            int x; cin >> x;
            if (x != 0) ft.add(i, j, x);
        }
    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int x, y, k; cin >> x >> y >> k;
            ft.add(x, y, k);
        } else {
            int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
            cout << ft.query(x1, y1, x2, y2) << '\n';
        }
    }
}

// 题目3：区间修改 + 单点查询
void solve_problem3() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    DiffFenwick df(n);
    df.build(a);

    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int l, r, v; cin >> l >> r >> v;
            df.range_add(l, r, v);
        } else {
            int x; cin >> x;
            cout << df.point_query(x) << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // 根据题目选择执行
    // solve_problem1();   // 逆序对
    // solve_problem2();   // 二维 BIT
    // solve_problem3();   // 差分 BIT

    return 0;
}
