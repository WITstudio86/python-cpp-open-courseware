/**
 * 第10课：线段树基础（Segment Tree Basic）
 * 对应CSP-S考纲知识点：
 *   - 线段树的建树（build）
 *   - 单点修改与区间查询
 *   - 懒标记（Lazy Tag）实现区间修改
 *   - 维护区间和、区间最大值/最小值
 *
 * 包含以下实现：
 *   1. 线段树模板（区间和 + 懒标记）
 *   2. 线段树模板（区间最大值，无懒标记）
 *   3. 线段树模板（区间最小值）
 *   4. 真题1：区间修改+区间查询（AC代码）
 *   5. 真题2：区间最大值（AC代码）
 *   6. 真题3：区间最小值与出现次数（AC代码）
 */

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// 通用宏与常量
// ============================================================
const long long INF = 1e18;

// ============================================================
// 一、线段树模板：区间和 + 懒标记（区间加法）
// 功能：区间加法修改、区间和查询
// 空间：tree[4*N], lazy[4*N]
// ============================================================
class SegTreeSum {
private:
    int n;
    vector<long long> tree, lazy;

    void pushup(int p) {
        tree[p] = tree[p << 1] + tree[p << 1 | 1];
    }

    void build(int p, int l, int r, const vector<long long>& a) {
        lazy[p] = 0;
        if (l == r) {
            tree[p] = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, a);
        build(p << 1 | 1, mid + 1, r, a);
        pushup(p);
    }

    void pushdown(int p, int l, int r) {
        if (lazy[p] != 0) {
            int mid = (l + r) >> 1;
            int left_len = mid - l + 1;
            int right_len = r - mid;

            tree[p << 1] += lazy[p] * left_len;
            tree[p << 1 | 1] += lazy[p] * right_len;

            lazy[p << 1] += lazy[p];
            lazy[p << 1 | 1] += lazy[p];

            lazy[p] = 0;
        }
    }

    void update(int p, int l, int r, int ql, int qr, long long v) {
        if (ql <= l && r <= qr) {
            tree[p] += v * (r - l + 1);
            lazy[p] += v;
            return;
        }
        pushdown(p, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr, v);
        if (qr > mid)  update(p << 1 | 1, mid + 1, r, ql, qr, v);
        pushup(p);
    }

    long long query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p];
        pushdown(p, l, r);
        int mid = (l + r) >> 1;
        long long res = 0;
        if (ql <= mid) res += query(p << 1, l, mid, ql, qr);
        if (qr > mid)  res += query(p << 1 | 1, mid + 1, r, ql, qr);
        return res;
    }

public:
    SegTreeSum(int sz) : n(sz) {
        tree.resize(4 * n + 5);
        lazy.resize(4 * n + 5);
    }

    void build(const vector<long long>& a) {
        build(1, 1, n, a);
    }

    void add(int l, int r, long long v) {
        update(1, 1, n, l, r, v);
    }

    long long sum(int l, int r) {
        return query(1, 1, n, l, r);
    }
};

// ============================================================
// 二、线段树模板：区间最大值（单点修改）
// 功能：单点赋值、区间最大值查询
// 用途：RMQ 问题、滑动窗口最大值
// ============================================================
class SegTreeMax {
private:
    int n;
    vector<int> tree;

    void pushup(int p) {
        tree[p] = max(tree[p << 1], tree[p << 1 | 1]);
    }

    void build(int p, int l, int r, const vector<int>& a) {
        if (l == r) {
            tree[p] = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, a);
        build(p << 1 | 1, mid + 1, r, a);
        pushup(p);
    }

    void update(int p, int l, int r, int x, int v) {
        if (l == r) {
            tree[p] = v;
            return;
        }
        int mid = (l + r) >> 1;
        if (x <= mid) update(p << 1, l, mid, x, v);
        else          update(p << 1 | 1, mid + 1, r, x, v);
        pushup(p);
    }

    int query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p];
        int mid = (l + r) >> 1;
        int res = -2e9;
        if (ql <= mid) res = max(res, query(p << 1, l, mid, ql, qr));
        if (qr > mid)  res = max(res, query(p << 1 | 1, mid + 1, r, ql, qr));
        return res;
    }

public:
    SegTreeMax(int sz) : n(sz) {
        tree.resize(4 * n + 5);
    }

    void build(const vector<int>& a) {
        build(1, 1, n, a);
    }

    void set(int x, int v) {
        update(1, 1, n, x, v);
    }

    int query_max(int l, int r) {
        return query(1, 1, n, l, r);
    }
};

// ============================================================
// 三、线段树模板：区间最小值（单点修改）
// 用途：RMQ、区间最小值维护
// ============================================================
class SegTreeMin {
private:
    int n;
    vector<int> tree;

    void pushup(int p) {
        tree[p] = min(tree[p << 1], tree[p << 1 | 1]);
    }

    void build(int p, int l, int r, const vector<int>& a) {
        if (l == r) {
            tree[p] = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, a);
        build(p << 1 | 1, mid + 1, r, a);
        pushup(p);
    }

    void update(int p, int l, int r, int x, int v) {
        if (l == r) {
            tree[p] = v;
            return;
        }
        int mid = (l + r) >> 1;
        if (x <= mid) update(p << 1, l, mid, x, v);
        else          update(p << 1 | 1, mid + 1, r, x, v);
        pushup(p);
    }

    int query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p];
        int mid = (l + r) >> 1;
        int res = 2e9;
        if (ql <= mid) res = min(res, query(p << 1, l, mid, ql, qr));
        if (qr > mid)  res = min(res, query(p << 1 | 1, mid + 1, r, ql, qr));
        return res;
    }

public:
    SegTreeMin(int sz) : n(sz) {
        tree.resize(4 * n + 5);
    }

    void build(const vector<int>& a) {
        build(1, 1, n, a);
    }

    void set(int x, int v) {
        update(1, 1, n, x, v);
    }

    int query_min(int l, int r) {
        return query(1, 1, n, l, r);
    }
};

// ============================================================
// 四、线段树模板：区间最小值 + 出现次数（单点修改）
// 真题：查询区间最小值及其出现次数
// ============================================================
class SegTreeMinCount {
private:
    int n;
    struct Node {
        int min_val;  // 区间最小值
        int cnt;      // 最小值的出现次数
    };
    vector<Node> tree;

    Node pushup(const Node& L, const Node& R) {
        Node res;
        if (L.min_val < R.min_val) {
            res.min_val = L.min_val;
            res.cnt = L.cnt;
        } else if (R.min_val < L.min_val) {
            res.min_val = R.min_val;
            res.cnt = R.cnt;
        } else {
            res.min_val = L.min_val;
            res.cnt = L.cnt + R.cnt;
        }
        return res;
    }

    void build(int p, int l, int r, const vector<int>& a) {
        if (l == r) {
            tree[p] = {a[l], 1};
            return;
        }
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, a);
        build(p << 1 | 1, mid + 1, r, a);
        tree[p] = pushup(tree[p << 1], tree[p << 1 | 1]);
    }

    void update(int p, int l, int r, int x, int v) {
        if (l == r) {
            tree[p] = {v, 1};
            return;
        }
        int mid = (l + r) >> 1;
        if (x <= mid) update(p << 1, l, mid, x, v);
        else          update(p << 1 | 1, mid + 1, r, x, v);
        tree[p] = pushup(tree[p << 1], tree[p << 1 | 1]);
    }

    Node query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p];
        int mid = (l + r) >> 1;
        // 根据区间范围分情况处理
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);       // 完全在左子树
        if (ql > mid)  return query(p << 1 | 1, mid + 1, r, ql, qr); // 完全在右子树
        Node L = query(p << 1, l, mid, ql, qr);        // 横跨两子树
        Node R = query(p << 1 | 1, mid + 1, r, ql, qr);
        return pushup(L, R);
    }

public:
    SegTreeMinCount(int sz) : n(sz) {
        tree.resize(4 * n + 5);
    }

    void build(const vector<int>& a) { build(1, 1, n, a); }
    void set(int x, int v) { update(1, 1, n, x, v); }
    pair<int, int> query_min_count(int l, int r) {
        Node res = query(1, 1, n, l, r);
        return {res.min_val, res.cnt};
    }
};

// ============================================================
// 五、测试与示例程序
// ============================================================

// 示例1：区间修改 + 区间查询（CSP-S真题模板）
// 输入格式：
//   n m
//   a[1] a[2] ... a[n]
//   m 行操作：op l r [v]
//     op=1: 区间加 v
//     op=2: 查询区间和
void solve_range_sum() {
    int n, m;
    cin >> n >> m;
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    SegTreeSum seg(n);
    seg.build(a);

    while (m--) {
        int op, l, r;
        long long v;
        cin >> op >> l >> r;
        if (op == 1) {
            cin >> v;
            seg.add(l, r, v);
        } else {
            cout << seg.sum(l, r) << '\n';
        }
    }
}

// 示例2：区间最大值查询
void solve_range_max() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    SegTreeMax seg(n);
    seg.build(a);

    while (m--) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1) {
            seg.set(x, y);          // 单点修改
        } else {
            cout << seg.query_max(x, y) << '\n';
        }
    }
}

// 示例3：区间最小值与出现次数
// 输入格式：
//   n m
//   a[1] ... a[n]
//   m 行操作：op x y
//     op=1: 单点修改 a[x]=y
//     op=2: 查询区间 [x, y] 的最小值及其出现次数
void solve_range_min_count() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    SegTreeMinCount seg(n);
    seg.build(a);

    while (m--) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1) {
            seg.set(x, y);   // 单点修改
        } else {
            auto [min_val, cnt] = seg.query_min_count(x, y);
            cout << min_val << " " << cnt << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // solve_range_sum();         // 区间修改+区间查询
    // solve_range_max();         // 区间最大值
    // solve_range_min_count();   // 区间最小值与出现次数

    return 0;
}
