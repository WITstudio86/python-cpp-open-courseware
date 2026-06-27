/**
 * 第11课：线段树进阶（Segment Tree Advanced）
 * 对应CSP-S考纲知识点：
 *   - 区间修改（加法+乘法）与多懒标记协同
 *   - 权值线段树（值域线段树）实现第K小数查询
 *   - 动态开点线段树
 *   - 线段树合并
 *   - 可持久化线段树（主席树）入门
 *
 * 包含以下实现：
 *   1. 多懒标记线段树（区间加法+乘法，取模）
 *   2. 动态开点权值线段树（第K小、排名、前驱后继）
 *   3. 线段树合并模板
 *   4. 可持久化线段树（主席树）模板
 */

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// 一、多懒标记线段树：区间加法 + 区间乘法（模 P）
// 原则：先乘后加
// 初始化：mul=1, add=0
// ============================================================
class SegTreeAddMul {
private:
    int n;
    long long P;
    vector<long long> sum, add, mul;

    void pushup(int p) {
        sum[p] = (sum[p << 1] + sum[p << 1 | 1]) % P;
    }

    void build(int p, int l, int r, const vector<long long>& a) {
        add[p] = 0; mul[p] = 1;
        if (l == r) {
            sum[p] = a[l] % P;
            return;
        }
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, a);
        build(p << 1 | 1, mid + 1, r, a);
        pushup(p);
    }

    void apply(int p, int len, long long mu, long long ad) {
        // 对节点 p 施加乘法 mu 和加法 ad
        sum[p] = (sum[p] * mu + ad * len) % P;
        mul[p] = (mul[p] * mu) % P;
        add[p] = (add[p] * mu + ad) % P;
    }

    void pushdown(int p, int l, int r) {
        int mid = (l + r) >> 1;
        apply(p << 1, mid - l + 1, mul[p], add[p]);
        apply(p << 1 | 1, r - mid, mul[p], add[p]);
        mul[p] = 1; add[p] = 0;
    }

    void update(int p, int l, int r, int ql, int qr, long long mu, long long ad) {
        if (ql <= l && r <= qr) {
            apply(p, r - l + 1, mu, ad);
            return;
        }
        pushdown(p, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr, mu, ad);
        if (qr > mid)  update(p << 1 | 1, mid + 1, r, ql, qr, mu, ad);
        pushup(p);
    }

    long long query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return sum[p];
        pushdown(p, l, r);
        int mid = (l + r) >> 1;
        long long res = 0;
        if (ql <= mid) res = (res + query(p << 1, l, mid, ql, qr)) % P;
        if (qr > mid)  res = (res + query(p << 1 | 1, mid + 1, r, ql, qr)) % P;
        return res;
    }

public:
    SegTreeAddMul(int sz, long long mod) : n(sz), P(mod) {
        sum.resize(4 * n + 5);
        add.resize(4 * n + 5);
        mul.resize(4 * n + 5);
    }

    void build(const vector<long long>& a) { build(1, 1, n, a); }

    void mul_range(int l, int r, long long v) { update(1, 1, n, l, r, v % P, 0); }
    void add_range(int l, int r, long long v) { update(1, 1, n, l, r, 1, v % P); }

    long long query_sum(int l, int r) { return query(1, 1, n, l, r); }
};

// ============================================================
// 二、动态开点权值线段树
// 功能：插入、删除、第K小、排名查询、前驱、后继
// 值域：[L, R]（包含负数），动态开点
// 空间复杂度：O(q * log(R-L))，约 q * 30
// ============================================================
class DynamicWeightSegTree {
private:
    struct Node {
        int lc, rc, cnt;
        Node() : lc(0), rc(0), cnt(0) {}
    };
    vector<Node> t;
    int root, L, R;

    void pushup(int p) {
        t[p].cnt = t[t[p].lc].cnt + t[t[p].rc].cnt;
    }

    void update(int &p, int l, int r, int x, int v) {
        if (!p) p = t.size(), t.emplace_back();
        if (l == r) {
            t[p].cnt += v;
            return;
        }
        int mid = l + (r - l) / 2;  // 防溢出
        if (x <= mid) update(t[p].lc, l, mid, x, v);
        else          update(t[p].rc, mid + 1, r, x, v);
        pushup(p);
    }

    int kth(int p, int l, int r, int k) {
        if (l == r) return l;
        int mid = l + (r - l) / 2;
        int left_cnt = t[t[p].lc].cnt;
        if (left_cnt >= k)
            return kth(t[p].lc, l, mid, k);
        else
            return kth(t[p].rc, mid + 1, r, k - left_cnt);
    }

    // 查询 < x 的元素个数
    int count_less(int p, int l, int r, int x) {
        if (!p || l >= x) return 0;
        if (r < x) return t[p].cnt;
        int mid = l + (r - l) / 2;
        return count_less(t[p].lc, l, mid, x) + count_less(t[p].rc, mid + 1, r, x);
    }

public:
    DynamicWeightSegTree(int valL, int valR) : L(valL), R(valR) {
        root = 0;
        t.emplace_back();  // 0 号节点为空
    }

    void insert(int x) { update(root, L, R, x, 1); }
    void erase(int x)   { update(root, L, R, x, -1); }

    // 查询第 k 小（1-indexed）
    int kth(int k) {
        if (k < 1 || k > t[root].cnt) return -1; // 不存在
        return kth(root, L, R, k);
    }

    // 查询 x 的排名（比 x 小的数的个数 + 1）
    int get_rank(int x) {
        return count_less(root, L, R, x) + 1;
    }

    // 查询 x 的前驱（严格小于 x 的最大值）
    int predecessor(int x) {
        int rk = count_less(root, L, R, x);
        if (rk == 0) return -1;
        return kth(root, L, R, rk);
    }

    // 查询 x 的后继（严格大于 x 的最小值）
    int successor(int x) {
        int rk = count_less(root, L, R, x + 1);
        if (rk + 1 > t[root].cnt) return -1;
        return kth(root, L, R, rk + 1);
    }
};

// ============================================================
// 三、线段树合并（动态开点）
// 将树 q 合并到树 p 上，返回合并后的根
// 可用于：树上维护子树信息、差分合并等
// ============================================================
class MergeableSegTree {
private:
    struct Node {
        int lc, rc, cnt;
        Node() : lc(0), rc(0), cnt(0) {}
    };
    vector<Node> t;
    int L, R;

    void pushup(int p) {
        t[p].cnt = t[t[p].lc].cnt + t[t[p].rc].cnt;
    }

public:
    MergeableSegTree(int valL, int valR) : L(valL), R(valR) {
        t.emplace_back();  // 0 号节点
    }

    int new_node() {
        t.emplace_back();
        return t.size() - 1;
    }

    void update(int &p, int l, int r, int x, int v) {
        if (!p) p = new_node();
        if (l == r) { t[p].cnt += v; return; }
        int mid = l + (r - l) / 2;
        if (x <= mid) update(t[p].lc, l, mid, x, v);
        else          update(t[p].rc, mid + 1, r, x, v);
        pushup(p);
    }

    void insert(int &p, int x) { update(p, L, R, x, 1); }

    // 将树 q 合并到树 p，返回 p
    int merge(int p, int q, int l, int r) {
        if (!p || !q) return p + q;
        if (l == r) {
            t[p].cnt += t[q].cnt;
            return p;
        }
        int mid = l + (r - l) / 2;
        t[p].lc = merge(t[p].lc, t[q].lc, l, mid);
        t[p].rc = merge(t[p].rc, t[q].rc, mid + 1, r);
        pushup(p);
        return p;
    }

    int merge(int p, int q) { return merge(p, q, L, R); }
};

// ============================================================
// 四、可持久化线段树（主席树）
// 功能：静态区间第 K 小查询
// 每次修改（插入一个数）生成新版本，通过前缀和做差得到区间信息
// ============================================================
class PersistentSegTree {
private:
    struct Node {
        int lc, rc, cnt;
        Node() : lc(0), rc(0), cnt(0) {}
    };
    vector<Node> t;
    vector<int> roots;  // 每个版本的根节点
    int L, R;

    int new_node() {
        t.emplace_back();
        return t.size() - 1;
    }

    void pushup(int p) {
        t[p].cnt = t[t[p].lc].cnt + t[t[p].rc].cnt;
    }

    int update(int pre, int l, int r, int x) {
        int p = new_node();
        t[p] = t[pre];  // 复制旧节点
        if (l == r) {
            t[p].cnt++;
            return p;
        }
        int mid = l + (r - l) / 2;
        if (x <= mid)
            t[p].lc = update(t[pre].lc, l, mid, x);
        else
            t[p].rc = update(t[pre].rc, mid + 1, r, x);
        pushup(p);
        return p;
    }

    int query(int p, int q, int l, int r, int k) {
        // p: 版本 r 的节点, q: 版本 l-1 的节点
        if (l == r) return l;
        int mid = l + (r - l) / 2;
        int left_cnt = t[t[p].lc].cnt - t[t[q].lc].cnt;
        if (left_cnt >= k)
            return query(t[p].lc, t[q].lc, l, mid, k);
        else
            return query(t[p].rc, t[q].rc, mid + 1, r, k - left_cnt);
    }

public:
    PersistentSegTree(int valL, int valR) : L(valL), R(valR) {
        t.emplace_back();  // 0 号节点
        roots.push_back(0);
    }

    // 插入一个数，生成新版本
    void insert(int x) {
        int pre = roots.back();
        roots.push_back(update(pre, L, R, x));
    }

    // 查询区间 [l, r] 中第 k 小的数（l, r 是版本号，1-indexed）
    int kth_in_range(int l, int r, int k) {
        return query(roots[r], roots[l - 1], L, R, k);
    }
};

// ============================================================
// 五、测试与示例程序
// ============================================================

// 示例1：多懒标记线段树 — 区间乘法 + 加法 + 求和
void solve_multi_lazy() {
    int n, m;
    long long P;
    cin >> n >> m >> P;
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    SegTreeAddMul seg(n, P);
    seg.build(a);

    while (m--) {
        int op, l, r;
        long long v;
        cin >> op >> l >> r;
        if (op == 1) {        // 区间乘法
            cin >> v;
            seg.mul_range(l, r, v);
        } else if (op == 2) { // 区间加法
            cin >> v;
            seg.add_range(l, r, v);
        } else {              // 区间求和
            cout << seg.query_sum(l, r) << '\n';
        }
    }
}

// 示例2：权值线段树 — 插入/删除/排名/第K小
void solve_weight_tree() {
    const int L = -1e7, R = 1e7;
    DynamicWeightSegTree seg(L, R);

    int q;
    cin >> q;
    while (q--) {
        int op, x;
        cin >> op >> x;
        if (op == 1) {
            seg.insert(x);
        } else if (op == 2) {
            seg.erase(x);
        } else if (op == 3) {
            cout << seg.get_rank(x) << '\n';
        } else if (op == 4) {
            cout << seg.kth(x) << '\n';
        } else if (op == 5) {
            cout << seg.predecessor(x) << '\n';
        } else if (op == 6) {
            cout << seg.successor(x) << '\n';
        }
    }
}

// 示例3：主席树 — 静态区间第K小
void solve_persistent() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);

    // 离散化
    vector<int> vals;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        vals.push_back(a[i]);
    }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    int m = vals.size();

    PersistentSegTree seg(1, m);
    for (int i = 1; i <= n; i++) {
        int rank = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin() + 1;
        seg.insert(rank);
    }

    while (q--) {
        int l, r, k;
        cin >> l >> r >> k;
        int rank = seg.kth_in_range(l, r, k);
        cout << vals[rank - 1] << '\n';  // 映射回原值
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // solve_multi_lazy();    // 多懒标记线段树
    // solve_weight_tree();   // 权值线段树
    // solve_persistent();    // 主席树（区间第K小）

    return 0;
}
