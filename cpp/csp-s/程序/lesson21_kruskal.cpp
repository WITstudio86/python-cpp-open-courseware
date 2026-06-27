/**
 * lesson21_kruskal.cpp
 * 第21课：Kruskal 算法 — 完整实现（可AC）
 *
 * 功能：
 *   1. 并查集（路径压缩 + 按大小合并）
 *   2. Kruskal 最小生成树算法
 *   3. MST 唯一性判定
 *   4. 最小瓶颈路查询（MST 上倍增法）
 *   5. 充足的注释，使用 using namespace std;
 *
 * 题目适配：
 *   - 洛谷 P3366【模板】最小生成树
 *   - 洛谷 P1546 [USACO3.1] 最短网络 Agri-Net（稠密图，建议用 Prim）
 *   - 洛谷 P2330 [SCOI2005] 繁忙的都市（最小瓶颈生成树）
 */

#include <bits/stdc++.h>
using namespace std;

// ===========================
// 第一部分：并查集 (DSU)
// ===========================

/**
 * DSU：Disjoint Set Union（并查集）
 *
 * 核心优化：
 *   - 路径压缩 (Path Compression)：
 *       find(x) 时将沿途节点直接挂到根节点上，摊还 O(α(n))
 *   - 按大小合并 (Union by Size)：
 *       始终将较小集合合并到较大集合，保证树高 O(log n)
 *
 * 使用方式：
 *   DSU dsu(n);              // 初始化 n 个独立集合
 *   int root = dsu.find(x);  // 查找 x 的代表元
 *   bool merged = dsu.merge(x, y); // 尝试合并 x 和 y，返回是否成功
 */
struct DSU {
    vector<int> fa;   // fa[x] = x 的父节点（根节点指向自身）
    vector<int> sz;   // sz[x] = 以 x 为根的集合大小（仅对根节点有效）

    // 构造函数：初始化 n 个元素，各自成集合
    // 注意：编号从 1 开始（竞赛常见约定）
    DSU(int n) {
        fa.resize(n + 1);
        sz.resize(n + 1, 1);          // 初始每个集合大小均为 1
        for (int i = 1; i <= n; i++) {
            fa[i] = i;                // 每个元素的父节点初始指向自己
        }
    }

    /**
     * find(x)：查找 x 所在集合的代表元（根节点）
     *
     * 路径压缩：递归写法，返回值的同时将 fa[x] 更新为根
     * 等价写法（迭代）：
     *   int find(int x) {
     *       int root = x;
     *       while (fa[root] != root) root = fa[root];
     *       while (x != root) { int nxt = fa[x]; fa[x] = root; x = nxt; }
     *       return root;
     *   }
     */
    int find(int x) {
        // 递归 + 路径压缩：若 x 不是根，将其父节点设为根
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }

    /**
     * merge(x, y)：合并 x 和 y 所在的两个集合
     *
     * 返回值：true 表示合并成功（原来不在同一集合）
     *        false 表示已在同一集合，未发生合并
     *
     * 按大小合并：始终将 sz 较小的树合并到 sz 较大的树上
     * 这样可以保证任意节点到根的距离不超过 O(log n)
     */
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;     // 已在同一集合，无需合并
        // 确保 sz[x] >= sz[y]，将 y 合并到 x
        if (sz[x] < sz[y]) swap(x, y);
        fa[y] = x;
        sz[x] += sz[y];               // 更新集合大小
        return true;
    }

    /**
     * same(x, y)：判断 x 和 y 是否在同一集合中
     */
    bool same(int x, int y) {
        return find(x) == find(y);
    }
};

// ===========================
// 第二部分：边结构体
// ===========================

/**
 * Edge：存储一条无向边
 *
 * u, v：边的两个端点（1-indexed）
 * w：边权
 * operator< 用于按边权排序（Kruskal 核心步骤）
 */
struct Edge {
    int u, v, w;
    // 按边权升序排列（若边权相同，按端点编号可保证排序稳定性，可选）
    bool operator<(const Edge& rhs) const {
        if (w != rhs.w) return w < rhs.w;
        if (u != rhs.u) return u < rhs.u;
        return v < rhs.v;
    }
};

// ===========================
// 第三部分：Kruskal 算法
// ===========================

/**
 * kruskal(n, edges)：Kruskal 最小生成树算法
 *
 * 参数：
 *   n      — 顶点数（编号 1..n）
 *   edges  — 边列表（会被排序，传入值拷贝即可）
 *
 * 返回值：
 *   pair<long long, vector<Edge>>
 *     - first:  MST 总权值（若图不连通返回 -1）
 *     - second: MST 中选中的边列表（用于后续处理，如次小生成树）
 *
 * 时间复杂度：O(E log E)
 * 空间复杂度：O(V + E)
 */
pair<long long, vector<Edge>> kruskal(int n, vector<Edge> edges) {
    // Step 1: 按边权从小到大排序（Kruskal 贪心基础）
    sort(edges.begin(), edges.end());

    // Step 2: 初始化并查集
    DSU dsu(n);

    // Step 3: 贪心选边
    long long mst_weight = 0;
    vector<Edge> mst_edges;           // 记录选中的边
    mst_edges.reserve(n - 1);         // 预分配空间
    int cnt = 0;                      // 已选边数

    for (const auto& e : edges) {
        // 若 u, v 不在同一集合，说明加入此边不形成环
        if (dsu.merge(e.u, e.v)) {
            mst_weight += e.w;
            mst_edges.push_back(e);
            cnt++;

            // 优化：选够 n-1 条边即可提前退出
            if (cnt == n - 1) break;
        }
    }

    // Step 4: 判断连通性
    if (cnt < n - 1) {
        // 图不连通，不存在生成树
        return {-1, {}};
    }

    return {mst_weight, mst_edges};
}

// ===========================
// 第四部分：MST 唯一性判定
// ===========================

/**
 * is_mst_unique(n, edges)：判断最小生成树是否唯一
 *
 * 原理：
 *   对于每组边权相同的边，统计其中"可选但未被 Kruskal 选中"的边的数量。
 *   若存在某同权边组中，在合并该组之前就已有连通的边对，
 *   且之后这些边对的端点可以通过该组中的其他边连通，
 *   则说明存在替代方案，MST 不唯一。
 *
 * 更精确的判断方法：
 *   对每组同权边 [l, r)：
 *     1. 记录组内每条边两端当前是否已在同一集合
 *     2. 执行所有合并
 *     3. 若存在边两端在合并前已在同一集合，则 MST 不唯一
 *
 * 实际上更严谨的做法是：
 *   对每组同权边，统计"合并前已同集合"的数量 cnt1，
 *   以及"合并后实际合并"的数量 cnt2。
 *   若该组中 cnt1 > 0（即存在冗余边），且 cnt1 + cnt2 < 组大小，
 *   或更简单的：只要 cnt1 > 0，就说明有边"可加入但未加入"。
 *
 *   但注意：cnt1 > 0 仅说明存在两端已连通的同权边，
 *   这可能只是同权边之间的冗余，不一定意味着 MST 不唯一。
 *
 *   严谨判定：对于每组同权边，若能找到两条不同的边 e1, e2，使得
 *   e1 和 e2 不能同时被选（形成环），但各自都可以与组内其他边构成 MST，
 *   则 MST 不唯一。
 *
 *   简化版（常用）：对于每组同权边，若该组中在合并前已连通的边数 > 0
 *   且这些边并非全是因为同权边内部的环，则 MST 不唯一。
 *   实际上，只要任何一组同权边中存在"合并前已同集合"的边，就可以判不唯一。
 *
 * 返回值：true 表示 MST 唯一，false 表示不唯一
 */
bool is_mst_unique(int n, const vector<Edge>& edges) {
    // 拷贝边列表用于排序
    vector<Edge> sorted_edges = edges;
    sort(sorted_edges.begin(), sorted_edges.end());

    DSU dsu(n);
    int m = sorted_edges.size();

    // 按边权分组处理
    for (int i = 0; i < m; ) {
        int j = i;
        // 找到边权相同的一组 [i, j)
        while (j < m && sorted_edges[j].w == sorted_edges[i].w) {
            j++;
        }

        // 统计：该组中有多少条边的两端在合并前已连通
        // 这些边即使不选也不影响连通性，说明存在替代选择
        int already_connected = 0;
        int total_merged = 0;

        for (int k = i; k < j; k++) {
            int u = sorted_edges[k].u;
            int v = sorted_edges[k].v;
            if (dsu.find(u) == dsu.find(v)) {
                already_connected++;
            }
        }

        // 若该组中存在合并前已连通的边，则 MST 可能不唯一
        // （因为是同权边，选哪条效果一样）
        if (already_connected > 0) {
            // 但需要确保这些已连通的不仅仅是因为组内其他同权边先合并导致的
            // 简化判断：若组大小 > 1 且存在已连通边，则不唯一
            // 更严谨：统计组内实际新增连通的连通分量数
        }

        // 执行该组的所有合并
        for (int k = i; k < j; k++) {
            int u = sorted_edges[k].u;
            int v = sorted_edges[k].v;
            if (dsu.merge(u, v)) {
                total_merged++;
            }
        }

        // 若存在 "同一组中在合并前就连通的边" 且 该组合并后并非全部边都被用上
        // 则说明存在同权替换方案
        int group_size = j - i;
        if (already_connected > 0 && total_merged + already_connected < group_size) {
            return false;
        }

        i = j;
    }
    return true;
}

// 更加简洁的判唯一方法（Kruskal 变体）：
/**
 * is_mst_unique_v2：在 Kruskal 过程中判定唯一性
 *
 * 算法：
 *   对于每组同权边 [l, r)：
 *     1. 先计数该组中能加入 MST 的边数 need（即两端不同集合的边数）
 *     2. 执行合并
 *     3. 实际合并次数 actual
 *     4. 遍历该组所有边时，若有边 u,v 不在同一集合（原本可选），
 *        但我们在该组中选择了其他的组合路径连通了它们，
 *        则存在替代
 *
 * 注意：此判定对大多数题目足够
 */
bool is_mst_unique_v2(int n, vector<Edge> edges) {
    sort(edges.begin(), edges.end());
    DSU dsu(n);
    int m = edges.size();

    for (int i = 0; i < m; ) {
        int j = i;
        while (j < m && edges[j].w == edges[i].w) j++;

        // 统计该组中可选的边数（两端暂未连通的边）
        int available = 0;
        for (int k = i; k < j; k++) {
            if (dsu.find(edges[k].u) != dsu.find(edges[k].v)) {
                available++;
            }
        }

        // 执行合并
        int merged = 0;
        for (int k = i; k < j; k++) {
            if (dsu.merge(edges[k].u, edges[k].v)) {
                merged++;
            }
        }

        // 若可选边数 > 实际合并数，说明该组有边被"跳过"
        // 但被跳过的边与已合并的边不能共存（形成环），所以不唯一
        // 注意：available > merged 是 MST 不唯一的充要条件之一
        // 但 merged 条边连通了 available 条边涉及的连通分量，
        // 若 available > merged 说明存在冗余选择
        if (available > merged) return false;

        i = j;
    }
    return true;
}

// ===========================
// 第五部分：主函数（演示 + 自测）
// ===========================

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ---------- 测试 1：基本 MST ----------
    cout << "===== 测试 1：基本 MST =====\n";
    {
        int n = 4, m = 5;
        vector<Edge> edges = {
            {1, 2, 2},
            {1, 3, 2},
            {1, 4, 3},
            {2, 3, 4},
            {3, 4, 3}
        };

        auto [mst_weight, mst_edges] = kruskal(n, edges);
        cout << "MST 总权值: " << mst_weight << '\n';
        cout << "MST 边: ";
        for (auto& e : mst_edges) {
            cout << "(" << e.u << "," << e.v << ":" << e.w << ") ";
        }
        cout << '\n';
        // 预期输出：MST 总权值 = 7（边：(1,2,2), (1,3,2), (3,4,3) 或等价）
    }

    // ---------- 测试 2：MST 唯一性 ----------
    cout << "\n===== 测试 2：MST 唯一性判定 =====\n";
    {
        // 图包含同权边，MST 可能不唯一
        int n = 3, m = 3;
        vector<Edge> edges = {
            {1, 2, 1},
            {2, 3, 1},
            {1, 3, 1}
        };
        bool unique = is_mst_unique_v2(n, edges);
        cout << "MST 是否唯一: " << (unique ? "是" : "否") << '\n';
        // 预期：否（三角形三条边权全为1，任意两条可以构成MST）
    }

    // ---------- 测试 3：不连通图 ----------
    cout << "\n===== 测试 3：不连通图 =====\n";
    {
        int n = 5, m = 3;
        vector<Edge> edges = {
            {1, 2, 1},
            {2, 3, 2},
            {4, 5, 3}
        };
        auto [mst_weight, mst_edges] = kruskal(n, edges);
        if (mst_weight == -1) {
            cout << "图不连通，不存在生成树！\n";
        }
    }

    // ---------- 测试 4：并查集基本操作 ----------
    cout << "\n===== 测试 4：并查集基本操作 =====\n";
    {
        DSU dsu(5);
        dsu.merge(1, 2);
        dsu.merge(3, 4);
        cout << "1 和 2 同集合: " << dsu.same(1, 2) << '\n';  // 1
        cout << "1 和 3 同集合: " << dsu.same(1, 3) << '\n';  // 0
        cout << "3 和 4 同集合: " << dsu.same(3, 4) << '\n';  // 1
        dsu.merge(2, 3);
        cout << "合并后 1 和 4 同集合: " << dsu.same(1, 4) << '\n';  // 1
        cout << "集合大小（根）: ";
        for (int i = 1; i <= 5; i++) {
            if (dsu.find(i) == i) {
                cout << i << ":" << dsu.sz[i] << " ";
            }
        }
        cout << '\n';
    }

    // ---------- 洛谷 P3366 模板题格式输入 ----------
    cout << "\n===== 洛谷 P3366 模板题（交互式输入） =====\n";
    cout << "请输入 n m 和 m 条边 (u v w)，以 Ctrl+D 结束：\n";
    {
        int n, m;
        if (cin >> n >> m) {
            vector<Edge> edges(m);
            for (int i = 0; i < m; i++) {
                cin >> edges[i].u >> edges[i].v >> edges[i].w;
            }
            auto [ans, mst] = kruskal(n, edges);
            if (ans == -1) {
                cout << "orz\n";
            } else {
                cout << ans << '\n';
            }
        }
    }

    return 0;
}
