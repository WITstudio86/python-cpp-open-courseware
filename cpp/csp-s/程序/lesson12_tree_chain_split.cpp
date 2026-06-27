/**
 * 第12课：树链剖分（Heavy-Light Decomposition）
 * 对应CSP-S考纲知识点：
 *   - 轻重链剖分：两次DFS，确定重链和DFS序
 *   - DFS序与连续区间映射
 *   - 树上路径操作转化为区间操作（线段树）
 *   - 树上路径查询与修改（O(log² n)）
 *   - 子树操作（O(log n)）
 *   - HLD 求 LCA（O(log n)）
 *
 * 包含以下实现：
 *   1. HLD 模板（两遍 DFS）
 *   2. 路径修改 + 路径查询（配合线段树）
 *   3. 子树修改 + 子树查询
 *   4. HLD 求 LCA
 *   5. 完整真题 AC 代码
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

// ============================================================
// 线段树模板（区间加法 + 区间求和，用于配合 HLD）
// ============================================================
class SegTree {
private:
    int n;
    vector<long long> tree, lazy;

    void pushup(int p) { tree[p] = tree[p << 1] + tree[p << 1 | 1]; }

    void build(int p, int l, int r, const vector<long long>& a) {
        lazy[p] = 0;
        if (l == r) { tree[p] = a[l]; return; }
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, a);
        build(p << 1 | 1, mid + 1, r, a);
        pushup(p);
    }

    void pushdown(int p, int l, int r) {
        if (lazy[p]) {
            int mid = (l + r) >> 1;
            tree[p << 1] += lazy[p] * (mid - l + 1);
            tree[p << 1 | 1] += lazy[p] * (r - mid);
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
    SegTree() : n(0) {}
    SegTree(int sz) : n(sz) {
        tree.resize(4 * n + 5);
        lazy.resize(4 * n + 5);
    }

    void build(const vector<long long>& a) { build(1, 1, n, a); }
    void add(int l, int r, long long v) { update(1, 1, n, l, r, v); }
    long long sum(int l, int r) { return query(1, 1, n, l, r); }
};

// ============================================================
// 树链剖分核心模板
// ============================================================
class HLD {
private:
    int n, timer;
    vector<vector<int>> adj;

    // 第一次 DFS
    vector<int> parent, depth, siz, heavy;
    void dfs1(int u, int fa) {
        parent[u] = fa;
        depth[u] = depth[fa] + 1;
        siz[u] = 1;
        heavy[u] = 0;
        int max_siz = 0;
        for (int v : adj[u]) {
            if (v == fa) continue;
            dfs1(v, u);
            siz[u] += siz[v];
            if (siz[v] > max_siz) {
                max_siz = siz[v];
                heavy[u] = v;
            }
        }
    }

    // 第二次 DFS：分配 DFS 序，优先遍历重儿子
    vector<int> dfn, rnk, top;
    void dfs2(int u, int tp) {
        dfn[u] = ++timer;
        rnk[timer] = u;
        top[u] = tp;
        if (heavy[u] == 0) return;   // 叶子
        dfs2(heavy[u], tp);          // 先走重儿子，保持重链连续
        for (int v : adj[u]) {
            if (v == parent[u] || v == heavy[u]) continue;
            dfs2(v, v);              // 轻儿子：新重链的顶端
        }
    }

public:
    SegTree seg;

    HLD(int sz) : n(sz), timer(0) {
        adj.resize(n + 1);
        parent.resize(n + 1);
        depth.resize(n + 1);
        siz.resize(n + 1);
        heavy.resize(n + 1);
        dfn.resize(n + 1);
        rnk.resize(n + 1);
        top.resize(n + 1);
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 根据原节点权值初始化（调用前需要先 init_hld）
    void init_hld(int root, const vector<long long>& w) {
        depth[0] = -1;  // 根节点 depth = 0
        dfs1(root, 0);
        dfs2(root, root);

        // 构建线段树：按 DFS 序排列权值
        vector<long long> a(n + 1);
        for (int i = 1; i <= n; i++) {
            a[dfn[i]] = w[i];  // 原权值映射到 DFS 序位置
        }
        seg = SegTree(n);
        seg.build(a);
    }

    // 获取节点的 DFS 序
    int get_dfn(int u) { return dfn[u]; }

    // ---------- 路径操作 ----------

    // 路径 u-v 上所有节点加 val
    void update_path(int u, int v, long long val) {
        while (top[u] != top[v]) {
            if (depth[top[u]] < depth[top[v]]) swap(u, v);
            seg.add(dfn[top[u]], dfn[u], val);
            u = parent[top[u]];  // 跳到链顶的父节点
        }
        if (depth[u] > depth[v]) swap(u, v);
        seg.add(dfn[u], dfn[v], val);
    }

    // 查询路径 u-v 上所有节点的和
    long long query_path(int u, int v) {
        long long res = 0;
        while (top[u] != top[v]) {
            if (depth[top[u]] < depth[top[v]]) swap(u, v);
            res += seg.sum(dfn[top[u]], dfn[u]);
            u = parent[top[u]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        res += seg.sum(dfn[u], dfn[v]);
        return res;
    }

    // ---------- 子树操作 ----------
    // 子树节点在 DFS 序中连续：[dfn[u], dfn[u] + siz[u] - 1]

    void update_subtree(int u, long long val) {
        seg.add(dfn[u], dfn[u] + siz[u] - 1, val);
    }

    long long query_subtree(int u) {
        return seg.sum(dfn[u], dfn[u] + siz[u] - 1);
    }

    // ---------- LCA ----------
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (depth[top[u]] < depth[top[v]]) swap(u, v);
            u = parent[top[u]];
        }
        return depth[u] < depth[v] ? u : v;
    }
};

// ============================================================
// 测试与示例程序
// ============================================================

// 题目：树上路径修改 + 路径查询 + 子树查询
// 输入格式：
//   n m
//   w[1] w[2] ... w[n]          （节点初始权值）
//   u1 v1 u2 v2 ...             (n-1 条边)
//   m 行操作：
//     op=1 u v x  : 路径加 x
//     op=2 u v    : 查询路径和
//     op=3 u x    : 子树加 x
//     op=4 u      : 查询子树和
void solve() {
    int n, m;
    cin >> n >> m;

    vector<long long> w(n + 1);
    for (int i = 1; i <= n; i++) cin >> w[i];

    HLD hld(n);
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        hld.add_edge(u, v);
    }

    hld.init_hld(1, w);  // 以 1 为根

    while (m--) {
        int op, u, v;
        long long x;
        cin >> op;
        if (op == 1) {
            cin >> u >> v >> x;
            hld.update_path(u, v, x);
        } else if (op == 2) {
            cin >> u >> v;
            cout << hld.query_path(u, v) << '\n';
        } else if (op == 3) {
            cin >> u >> x;
            hld.update_subtree(u, x);
        } else if (op == 4) {
            cin >> u;
            cout << hld.query_subtree(u) << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
