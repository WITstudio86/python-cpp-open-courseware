/**
 * lesson22_prim_second_mst.cpp
 * 第22课：Prim 算法与次小生成树 — 完整实现（可AC）
 *
 * 功能：
 *   1. Prim 朴素实现 O(V²)（邻接矩阵，稠密图适用）
 *   2. Prim 堆优化实现 O(E log V)（邻接表 + 优先队列）
 *   3. 严格次小生成树（Kruskal + 树上倍增 + LCA + 最大/次大边权）
 *   4. 充足的注释，使用 using namespace std;
 *
 * 题目适配：
 *   - 洛谷 P3366【模板】最小生成树（Kruskal/Prim均可）
 *   - 洛谷 P4180【BJWC2010】严格次小生成树
 *   - 洛谷 P1546 [USACO3.1] 最短网络 Agri-Net（稠密图，朴素Prim）
 */

#include <bits/stdc++.h>
using namespace std;

// ============================================
// 第一部分：Prim 朴素实现 O(V²)
// 适用场景：稠密图（完全图、邻接矩阵输入）
// 当 V ≤ 5000 且 E 很大（接近 V²）时，
// 朴素 Prim 比堆优化甚至比 Kruskal 都快
// ============================================

/**
 * prim_dense(n, g): 朴素 Prim 算法（邻接矩阵版本）
 *
 * 参数：
 *   n — 顶点数（1-indexed）
 *   g — 邻接矩阵，g[i][j] 表示 i 到 j 的边权
 *       不存在的边应设为 INF
 *
 * 返回值：
 *   MST 总权值；若图不连通返回 -1
 *
 * 时间复杂度：O(V²)
 * 空间复杂度：O(V²)
 *
 * 注意事项：
 *   - 与 Dijkstra 的区别仅在于 dis 的更新公式
 *     Dijkstra: dis[v] = min(dis[v], dis[u] + w)  （到源点的路径和）
 *     Prim:     dis[v] = min(dis[v], w)            （到已选集合的最小边权）
 *   - 竞赛中这是最容易混淆的两个算法之一
 */
long long prim_dense(int n, const vector<vector<int>>& g) {
    const int INF = 0x3f3f3f3f;

    // dis[i]: 节点 i 到当前已选集合 S 的最小边权
    vector<int> dis(n + 1, INF);
    // vis[i]: 节点 i 是否已加入 S
    vector<bool> vis(n + 1, false);

    // 从任意起点开始（通常选 1）
    dis[1] = 0;
    long long mst_weight = 0;

    // 每次迭代选一个节点加入 S，共 n 次
    for (int iter = 1; iter <= n; iter++) {
        // Step 1: 在未访问节点中找到 dis 最小的节点 u
        int u = -1;
        for (int j = 1; j <= n; j++) {
            if (!vis[j] && (u == -1 || dis[j] < dis[u])) {
                u = j;
            }
        }

        // 若找不到（dis[u] 仍为 INF），说明图不连通
        if (u == -1 || dis[u] == INF) {
            return -1;
        }

        // Step 2: 将 u 加入集合 S
        vis[u] = true;
        mst_weight += dis[u];   // dis[u] 就是连接 u 到 S 的最小边权

        // Step 3: 用 u 更新所有未访问邻接点 v 的 dis 值
        // 注意：这里是 dis[v] = min(dis[v], g[u][v])，不是 dis[u] + g[u][v]
        for (int v = 1; v <= n; v++) {
            if (!vis[v] && g[u][v] < dis[v]) {
                dis[v] = g[u][v];
            }
        }
    }

    return mst_weight;
}

// ============================================
// 第二部分：Prim 堆优化 O(E log V)
// 适用场景：稀疏图（E ≈ V）
// 使用邻接表 + 优先队列（最小堆）
// ============================================

/**
 * prim_heap(n, adj): 堆优化 Prim 算法
 *
 * 参数：
 *   n   — 顶点数（1-indexed）
 *   adj — 邻接表，adj[u] = {{v1, w1}, {v2, w2}, ...}
 *
 * 返回值：
 *   MST 总权值；若图不连通返回 -1
 *
 * 时间复杂度：O((V + E) log V)
 * 空间复杂度：O(V + E)
 *
 * 注意事项：
 *   - 同一个节点可能因 dis 更新而多次入队
 *     使用 vis 数组跳过已处理节点（类似 Dijkstra 的懒惰删除）
 *   - 堆中存储 pair<边权, 节点>，C++ 默认大根堆，
 *     使用 greater<> 转为小根堆
 */
long long prim_heap(int n, const vector<vector<pair<int,int>>>& adj) {
    const int INF = 0x3f3f3f3f;

    vector<int> dis(n + 1, INF);
    vector<bool> vis(n + 1, false);

    // 最小堆：pair<边权, 节点编号>
    // greater<pair<int,int>> 使堆顶为最小边权
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    dis[1] = 0;
    pq.push({0, 1});     // {边权, 节点}

    long long mst_weight = 0;
    int selected = 0;    // 已选节点数

    while (!pq.empty() && selected < n) {
        // 取出当前距离集合最小的节点
        auto [d, u] = pq.top();
        pq.pop();

        // 懒惰删除：跳过已处理的节点
        if (vis[u]) continue;

        // 将 u 加入集合 S
        vis[u] = true;
        mst_weight += d;
        selected++;

        // 用 u 更新邻接节点 v
        // 注意更新公式：dis[v] = min(dis[v], w)，不是 dis[u] + w
        for (auto& [v, w] : adj[u]) {
            if (!vis[v] && w < dis[v]) {
                dis[v] = w;
                pq.push({w, v});
            }
        }
    }

    // 若未选满 n 个节点，说明图不连通
    return (selected == n) ? mst_weight : -1;
}

// ============================================
// 第三部分：严格次小生成树
// ============================================

/**
 * 严格次小生成树算法：
 *
 *   Step 1: 用 Kruskal 求出 MST，同时构建 MST 的邻接表
 *   Step 2: 在 MST 上 DFS，预处理树上倍增数组（up, mx, mx2, depth）
 *           用于 O(log n) 查询路径上最大边权和严格次大边权
 *   Step 3: 枚举所有非树边 e = (u, v, w)：
 *           查询 u-v 路径上的最大边权 max_w 和严格次大边权 max2_w
 *           - 若 w > max_w：候选 = mst_weight - max_w + w
 *           - 若 w == max_w 且 max2_w 存在：候选 = mst_weight - max2_w + w
 *           取所有候选的最小值
 *
 *   "严格"的含义：次小生成树权值必须严格大于 MST 权值
 *   因此当替换边权 == 路径最大边权时，替换后权值不变
 *   必须使用严格次大边权来替换，才能得到严格更大的生成树
 */

using ll = long long;
const int MAXN = 100005;         // 最大顶点数
const int MAXM = 300005;         // 最大边数
const int LOG = 20;              // log2(MAXN) ≈ 17，取 20 保险
const ll INF_LL = 1e18;         // 足够大的"无穷"，边权 ≤ 1e9, n ≤ 1e5, MST ≤ 1e14

// ===== 边结构体（带 MST 标记） =====
struct Edge {
    int u, v, w, id;
    bool in_mst;                  // 是否属于 MST

    // 按边权升序（Kruskal 排序）
    bool operator<(const Edge& rhs) const {
        if (w != rhs.w) return w < rhs.w;
        return u < rhs.u;         // 稳定性保证（可选）
    }
};

// ===== 并查集 =====
struct DSU {
    int fa[MAXN], sz[MAXN];

    void init(int n) {
        for (int i = 1; i <= n; i++) {
            fa[i] = i;
            sz[i] = 1;
        }
    }

    int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }

    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (sz[x] < sz[y]) swap(x, y);
        fa[y] = x;
        sz[x] += sz[y];
        return true;
    }
};

// ===== 全局变量 =====
Edge edges[MAXM];
vector<pair<int,int>> mst_adj[MAXN];  // MST 的邻接表（节点, 边权）
int n, m;

// 倍增相关
int up[MAXN][LOG];          // up[u][k]: u 的 2^k 级祖先
ll mx[MAXN][LOG];           // mx[u][k]: u 到 2^k 祖先路径上的最大边权
ll mx2[MAXN][LOG];          // mx2[u][k]: u 到 2^k 祖先路径上的严格次大边权
int depth[MAXN];            // 节点深度（根节点深度 = 1）

/**
 * merge_four(values): 从四个候选值中提取最大和严格次大
 *
 * 用于倍增节点的合并：每个倍增段提供 mx 和 mx2 两个值，
 * 父段的 mx 和 mx2 加上当前段的 mx 和 mx2 共四个候选值，
 * 需要从中找出最大值和严格次大值。
 *
 * 参数：
 *   vals — 四个候选值（其中可能包含 -INF_LL 表示不存在）
 *
 * 返回值：
 *   pair<ll, ll> {最大值, 严格次大值}
 *   若不存在次大值，second = -INF_LL
 */
pair<ll, ll> merge_four(const vector<ll>& vals) {
    ll first = -INF_LL, second = -INF_LL;
    for (ll val : vals) {
        if (val > first) {
            second = first;
            first = val;
        } else if (val < first && val > second) {
            second = val;
        }
    }
    return {first, second};
}

/**
 * dfs(u, fa): 在 MST 上 DFS，预处理倍增数组
 *
 * up[v][0] = u（v 的父节点）
 * mx[v][0] = w_uv
 * mx2[v][0] = -INF_LL（单条边无次大值）
 *
 * 对于 k >= 1：
 *   up[v][k] = up[up[v][k-1]][k-1]
 *   合并 mx[v][k-1], mx2[v][k-1], mx[up[v][k-1]][k-1], mx2[up[v][k-1]][k-1]
 *   取最大和严格次大
 */
void dfs(int u, int fa) {
    for (auto& [v, w] : mst_adj[u]) {
        if (v == fa) continue;

        depth[v] = depth[u] + 1;

        // 初始化 k=0
        up[v][0] = u;
        mx[v][0] = w;
        mx2[v][0] = -INF_LL;

        // 递推计算 k >= 1
        for (int k = 1; k < LOG; k++) {
            int mid = up[v][k - 1];       // 2^(k-1) 祖先
            up[v][k] = up[mid][k - 1];    // 2^k 祖先

            // 合并四个候选值
            auto [max_val, max2_val] = merge_four({
                mx[v][k - 1], mx2[v][k - 1],
                mx[mid][k - 1], mx2[mid][k - 1]
            });
            mx[v][k] = max_val;
            mx2[v][k] = max2_val;
        }

        dfs(v, u);
    }
}

/**
 * query(u, v): 查询 MST 上 u 到 v 路径的最大边权和严格次大边权
 *
 * 类似 LCA 查询，但沿途收集每个跳跃段的 mx 和 mx2，
 * 最终在所有收集到的值中取全局最大和严格次大。
 *
 * 返回值：pair<ll, ll> {最大边权, 严格次大边权}
 */
pair<ll, ll> query(int u, int v) {
    ll max_w = -INF_LL, max2_w = -INF_LL;

    // ===== 阶段 1：将 u 和 v 跳到同一深度 =====
    if (depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    for (int i = 0; diff; i++, diff >>= 1) {
        if (diff & 1) {
            // 合并当前跳跃段的 mx 和 mx2
            auto [m1, m2] = merge_four({max_w, max2_w, mx[u][i], mx2[u][i]});
            max_w = m1;
            max2_w = m2;
            u = up[u][i];
        }
    }

    if (u == v) return {max_w, max2_w};

    // ===== 阶段 2：同时上跳直到父节点相同 =====
    for (int i = LOG - 1; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            // 合并 u 的跳跃段
            auto [mu1, mu2] = merge_four({max_w, max2_w, mx[u][i], mx2[u][i]});
            max_w = mu1; max2_w = mu2;
            // 合并 v 的跳跃段
            auto [mv1, mv2] = merge_four({max_w, max2_w, mx[v][i], mx2[v][i]});
            max_w = mv1; max2_w = mv2;

            u = up[u][i];
            v = up[v][i];
        }
    }

    // ===== 阶段 3：最后一步（到 LCA） =====
    auto [m1, m2] = merge_four({max_w, max2_w, mx[u][0], mx[v][0]});
    max_w = m1;
    max2_w = m2;

    return {max_w, max2_w};
}

/**
 * kruskal_and_build_mst(): Kruskal 求 MST + 构建 MST 邻接表
 *
 * 返回值：MST 总权值（图保证连通，否则返回 -1）
 */
ll kruskal_and_build_mst() {
    // Step 1: 边排序
    sort(edges + 1, edges + m + 1);

    // Step 2: 初始化并查集
    DSU dsu;
    dsu.init(n);

    // Step 3: 贪心选边
    ll mst_weight = 0;
    int cnt = 0;

    for (int i = 1; i <= m && cnt < n - 1; i++) {
        if (dsu.merge(edges[i].u, edges[i].v)) {
            mst_weight += edges[i].w;
            edges[i].in_mst = true;
            cnt++;

            // 构建 MST 邻接表（用于后续 DFS）
            int u = edges[i].u, v = edges[i].v, w = edges[i].w;
            mst_adj[u].push_back({v, w});
            mst_adj[v].push_back({u, w});
        }
    }

    return (cnt == n - 1) ? mst_weight : -1;
}

/**
 * second_mst_strict(mst_weight): 求严格次小生成树
 *
 * 参数：
 *   mst_weight — 已求出的 MST 总权值
 *
 * 返回值：
 *   严格次小生成树权值
 *   若不存在严格次小生成树，返回 INF_LL
 *
 * 算法：
 *   枚举每条非树边 e = (u, v, w)，尝试替换 MST 上 u-v 路径中的某条边
 *   若 w > 路径最大边 max_w：替换最大边，得到严格更大的生成树
 *   若 w == max_w：替换路径严格次大边 max2_w（若存在），得到严格更大的生成树
 */
ll solve_second_mst_strict(ll mst_weight) {
    // Step 1: DFS 预处理倍增数组
    // 初始化根节点 1
    depth[1] = 1;
    for (int i = 0; i < LOG; i++) {
        up[1][i] = 1;          // 根的祖先设为自身（边界处理）
        mx[1][i] = -INF_LL;
        mx2[1][i] = -INF_LL;
    }
    dfs(1, 0);

    // Step 2: 枚举非树边，计算每种替换方案的权值
    ll ans = INF_LL;

    for (int i = 1; i <= m; i++) {
        if (edges[i].in_mst) continue;     // 跳过树边

        int u = edges[i].u, v = edges[i].v;
        ll w = edges[i].w;

        // 查询 MST 上 u-v 路径的最大边权和严格次大边权
        auto [max_w, max2_w] = query(u, v);

        if (w > max_w) {
            // 情况 1：替换最大边，新权值严格大于 MST
            ans = min(ans, mst_weight - max_w + w);
        } else if (w == max_w && max2_w != -INF_LL) {
            // 情况 2：w == max_w，替换后权值不变，需替换次大边
            // （要求 w > max2_w 自动满足，因为 max2_w < max_w == w）
            ans = min(ans, mst_weight - max2_w + w);
        }
        // 情况 3：w < max_w 且 max2_w 不存在（路径上所有边权都相同）
        // 此时无法通过替换得到严格更大的生成树，跳过
    }

    return ans;
}

// ============================================
// 第四部分：主函数（演示 + 自测）
// ============================================

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ---------- 测试 1：朴素 Prim ----------
    cout << "===== 测试 1：朴素 Prim (稠密图) =====\n";
    {
        int n1 = 4;
        // 邻接矩阵：g[i][j] = INF 表示无边
        const int INF = 0x3f3f3f3f;
        vector<vector<int>> g(n1 + 1, vector<int>(n1 + 1, INF));
        // 手动构造一个简单图
        g[1][2] = g[2][1] = 2;
        g[1][3] = g[3][1] = 3;
        g[1][4] = g[4][1] = 1;
        g[2][3] = g[3][2] = 4;
        g[3][4] = g[4][3] = 5;

        long long ans = prim_dense(n1, g);
        cout << "朴素 Prim MST 权值: " << ans << '\n';
        // 预期输出：MST 权值 = 7（边：1-4(1), 1-2(2), 1-3(3)）
    }

    // ---------- 测试 2：堆优化 Prim ----------
    cout << "\n===== 测试 2：堆优化 Prim (稀疏图) =====\n";
    {
        int n2 = 4;
        vector<vector<pair<int,int>>> adj(n2 + 1);
        adj[1].push_back({2, 2});
        adj[2].push_back({1, 2});
        adj[1].push_back({3, 3});
        adj[3].push_back({1, 3});
        adj[1].push_back({4, 1});
        adj[4].push_back({1, 1});
        adj[2].push_back({3, 4});
        adj[3].push_back({2, 4});
        adj[3].push_back({4, 5});
        adj[4].push_back({3, 5});

        long long ans = prim_heap(n2, adj);
        cout << "堆优化 Prim MST 权值: " << ans << '\n';
    }

    // ---------- 测试 3：严格次小生成树 ----------
    cout << "\n===== 测试 3：严格次小生成树 =====\n";
    {
        // 手动构造一个小图测试
        n = 4; m = 6;
        // 边：(1,2,1), (2,3,2), (3,4,3), (1,4,4), (1,3,5), (2,4,6)
        // MST = {(1,2,1), (2,3,2), (3,4,3)} = 6
        // 替换 (1,4,4)：去掉 (3,4,3) 或 (2,3,2)+(1,2,1) 中最大 3 → 6-3+4=7
        // 次小 = 7
        edges[1] = {1, 2, 1, 1, false};
        edges[2] = {2, 3, 2, 2, false};
        edges[3] = {3, 4, 3, 3, false};
        edges[4] = {1, 4, 4, 4, false};
        edges[5] = {1, 3, 5, 5, false};
        edges[6] = {2, 4, 6, 6, false};

        // 注意：先清空全局邻接表
        for (int i = 1; i <= n; i++) mst_adj[i].clear();

        ll mst_w = kruskal_and_build_mst();
        cout << "MST 权值: " << mst_w << '\n';
        cout << "MST 边: ";
        for (int i = 1; i <= m; i++) {
            if (edges[i].in_mst) {
                cout << "(" << edges[i].u << "," << edges[i].v << ":" << edges[i].w << ") ";
            }
        }
        cout << '\n';

        ll second_mst = solve_second_mst_strict(mst_w);
        cout << "严格次小生成树权值: " << second_mst << '\n';
        // 预期：7
    }

    // ---------- 测试 4：Prim 与 Dijkstra 的区别演示 ----------
    cout << "\n===== 测试 4：Prim 与 Dijkstra 公式对比 =====\n";
    {
        cout << "关键区别（已选集合 S）：\n";
        cout << "  Prim:     dis[v] = min(dis[v], w(u,v))     ← 到集合的最小边权\n";
        cout << "  Dijkstra: dis[v] = min(dis[v], dis[u] + w) ← 到源点的最短路径\n";
        cout << "  仅此一处不同，其余代码几乎完全一样。\n";
    }

    // ---------- 洛谷 P4180 严格次小生成树（交互式输入） ----------
    cout << "\n===== 洛谷 P4180 严格次小生成树（交互式输入） =====\n";
    cout << "请输入 n m 和 m 条边 (u v w)，以 Ctrl+D 结束：\n";
    {
        if (cin >> n >> m) {
            // 清空全局状态
            for (int i = 1; i <= n; i++) mst_adj[i].clear();

            for (int i = 1; i <= m; i++) {
                cin >> edges[i].u >> edges[i].v >> edges[i].w;
                edges[i].id = i;
                edges[i].in_mst = false;
            }

            ll mst_w = kruskal_and_build_mst();
            if (mst_w == -1) {
                cout << "图不连通！\n";
            } else {
                ll ans = solve_second_mst_strict(mst_w);
                if (ans == INF_LL) {
                    cout << "不存在严格次小生成树\n";
                } else {
                    cout << ans << '\n';
                }
            }
        }
    }

    return 0;
}
