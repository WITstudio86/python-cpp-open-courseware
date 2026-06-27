/**
 * 第13课：并查集基础（Union-Find / Disjoint Set Union）
 * 对应CSP-S考纲知识点：
 *   - 路径压缩（Path Compression）
 *   - 按秩合并（Union by Rank / Size）
 *   - 时间复杂度分析（反阿克曼函数 α(n)，近似 O(1)）
 *   - 连通块计数与维护
 *   - 离线逆序处理
 *
 * 包含以下实现：
 *   1. 标准 DSU 模板（路径压缩 + 按大小合并）
 *   2. 按秩（高度）合并版本
 *   3. 连通块维护
 *   4. Kruskal 最小生成树（应用并查集）
 *   5. 离线删边转加边
 */

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// 一、标准并查集模板（路径压缩 + 按大小合并）
// 功能：find 查根、unite 合并、same 判连通、size 查集合大小
// 时间复杂度：单次操作 O(α(n)) ≈ O(1)
// ============================================================
struct DSU {
    vector<int> fa, sz;
    int comp;  // 连通块（集合）数量

    DSU(int n) : fa(n + 1), sz(n + 1, 1), comp(n) {
        for (int i = 1; i <= n; i++) fa[i] = i;
    }

    // 查找（路径压缩 — 递归版）
    int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }

    // 查找（路径压缩 — 迭代版，防栈溢出）
    int find_iter(int x) {
        int root = x;
        while (fa[root] != root) root = fa[root];
        while (x != root) {           // 路径压缩
            int nxt = fa[x];
            fa[x] = root;
            x = nxt;
        }
        return root;
    }

    // 合并：小树挂到大树上
    // 返回 true 表示成功合并，false 表示已连通
    bool unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (sz[x] < sz[y]) swap(x, y);  // 确保 x 是较大的树
        fa[y] = x;
        sz[x] += sz[y];
        comp--;
        return true;
    }

    // 判断两个元素是否在同一集合
    bool same(int x, int y) { return find(x) == find(y); }

    // 查询 x 所属集合的大小
    int size(int x) { return sz[find(x)]; }
};

// ============================================================
// 二、按秩（高度）合并的 DSU
// rank 是树高的上界估计值
// ============================================================
struct DSU_Rank {
    vector<int> fa, rk;
    int comp;

    DSU_Rank(int n) : fa(n + 1), rk(n + 1, 0), comp(n) {
        for (int i = 1; i <= n; i++) fa[i] = i;
    }

    int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }

    bool unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (rk[x] < rk[y]) swap(x, y);
        fa[y] = x;
        if (rk[x] == rk[y]) rk[x]++;  // 等高时才增加秩
        comp--;
        return true;
    }
};

// ============================================================
// 三、Kruskal 最小生成树（并查集经典应用）
// 给定 n 个点 m 条带权边的无向图，求最小生成树的边权和
// ============================================================
struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

long long kruskal(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());  // 按边权升序
    DSU dsu(n);
    long long mst_weight = 0;
    int cnt = 0;  // 已选边数

    for (auto& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            mst_weight += e.w;
            cnt++;
            if (cnt == n - 1) break;  // 树已形成
        }
    }

    // 若 cnt < n - 1，则图不连通，不存在 MST
    return (cnt == n - 1) ? mst_weight : -1;
}

// ============================================================
// 四、离线删边转加边
// 问题：给定一张图，依次删除 k 条边，每次删边后求连通块数
// 解法：反向处理，初始加入所有未被删除的边，然后逆序加回被删的边
// ============================================================
vector<int> offline_delete_edges(int n, const vector<pair<int,int>>& all_edges,
                                  const vector<pair<int,int>>& delete_edges) {
    int k = delete_edges.size();

    // 用 set 标记被删除的边（无向边需规范化）
    set<pair<int,int>> deleted;
    for (auto& e : delete_edges) {
        int u = e.first, v = e.second;
        if (u > v) swap(u, v);
        deleted.insert({u, v});
    }

    // 建 DSU，先加入所有未被删除的边
    DSU dsu(n);
    for (auto& e : all_edges) {
        int u = e.first, v = e.second;
        if (u > v) swap(u, v);
        if (deleted.find({u, v}) == deleted.end()) {
            dsu.unite(u, v);
        }
    }

    // 逆序加回被删除的边，记录每次加边前的连通块数
    vector<int> ans(k);
    for (int i = k - 1; i >= 0; i--) {
        ans[i] = dsu.comp;
        int u = delete_edges[i].first, v = delete_edges[i].second;
        dsu.unite(u, v);
    }
    return ans;
}

// ============================================================
// 五、测试与示例程序
// ============================================================

// 示例1：基本连通性查询
void solve_connectivity() {
    int n, m;
    cin >> n >> m;
    DSU dsu(n);

    while (m--) {
        char op;
        int x, y;
        cin >> op >> x >> y;
        if (op == 'M') {          // Merge
            dsu.unite(x, y);
        } else if (op == 'Q') {   // Query
            cout << (dsu.same(x, y) ? "Yes" : "No")
                 << " (components: " << dsu.comp << ")\n";
        }
    }
}

// 示例2：Kruskal 最小生成树
void solve_mst() {
    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    long long ans = kruskal(n, edges);
    if (ans == -1) cout << "orz\n";  // 不连通
    else cout << ans << '\n';
}

// 示例3：离线删边
void solve_offline_delete() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<pair<int,int>> all_edges(m);
    for (int i = 0; i < m; i++) {
        cin >> all_edges[i].first >> all_edges[i].second;
    }
    vector<pair<int,int>> del_edges(k);
    for (int i = 0; i < k; i++) {
        cin >> del_edges[i].first >> del_edges[i].second;
    }
    vector<int> ans = offline_delete_edges(n, all_edges, del_edges);
    for (int x : ans) cout << x << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // solve_connectivity();     // 连通性查询
    // solve_mst();              // 最小生成树
    // solve_offline_delete();   // 离线删边

    return 0;
}
