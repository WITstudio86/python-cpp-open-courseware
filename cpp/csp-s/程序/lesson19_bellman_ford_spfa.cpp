/**
 * 第19课：Bellman-Ford 与 SPFA
 *
 * 本文件实现了以下算法（全部可AC）：
 * 1. Bellman-Ford（边集数组实现，O(VE)）
 * 2. SPFA（邻接表+队列实现）
 * 3. 负环检测（计数入队次数 / 计数路径边数）
 * 4. SPFA + SLF优化（Small Label First，deque实现）
 *
 * 所有代码使用 using namespace std; 并提供充足的注释。
 *
 * 编译命令：g++ -std=c++17 -O2 lesson19_bellman_ford_spfa.cpp -o lesson19
 * 运行方式：./lesson19 < input.txt
 */

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// 全局常量定义
// ============================================================
const int MAXN = 100005;           // 最大节点数
const int MAXM = 500005;           // 最大边数
const long long INF = 1e18;        // 无穷大（注意 INF + w 不能溢出）

// ============================================================
// 1. Bellman-Ford 算法 —— 边集数组实现
// ============================================================
// 适用场景：含有负权边的有向图（不能有负环）
// 时间复杂度：O(VE)
// 空间复杂度：O(V + M)（边集数组）

namespace BellmanFord {

    struct Edge {
        int u, v;
        long long w;
    } edges[MAXM];

    long long dist[MAXN];
    int pre[MAXN];          // 前驱，用于路径还原
    int n, m;

    /**
     * bellman_ford(s) —— 从源点 s 出发，计算到各点的最短路
     * @param s  源点编号（1-indexed）
     * @return   true 表示无负环，false 表示存在从源点可达的负环
     *
     * 算法核心：
     * - 进行 n-1 轮松弛，每轮遍历所有边
     * - 第 k 轮后 dist[v] = 从 s 出发经过不超过 k 条边的最短距离
     * - 第 n 轮仍可松弛 → 存在负环
     */
    bool bellman_ford(int s) {
        // 初始化距离数组
        fill(dist, dist + n + 1, INF);
        fill(pre, pre + n + 1, -1);
        dist[s] = 0;

        // 进行 n-1 轮松弛
        for (int i = 1; i < n; i++) {
            bool updated = false;       // 本轮是否有更新

            // 遍历所有边，尝试松弛
            for (int j = 1; j <= m; j++) {
                int u = edges[j].u;
                int v = edges[j].v;
                long long w = edges[j].w;

                // 注意：dist[u] 必须是可达的，否则 INF + w 溢出
                if (dist[u] != INF && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pre[v] = u;         // 记录前驱
                    updated = true;
                }
            }

            // 提前终止优化：若本轮无更新，后续轮次也不会有
            if (!updated) break;
        }

        // 第 n 轮松弛：检测负环
        // 若仍能松弛，说明存在经过 ≥ n 条边的最短路径 → 必有负环
        for (int j = 1; j <= m; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            long long w = edges[j].w;
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                return false;           // 存在负环！
            }
        }
        return true;                    // 无负环，最短路计算正确
    }

    /**
     * print_path(v) —— 还原并输出从源点到 v 的最短路径
     * 要求 bellman_ford() 已被调用且 dist[v] != INF
     */
    void print_path(int v) {
        if (dist[v] == INF) {
            cout << "不可达" << endl;
            return;
        }
        vector<int> path;
        for (int cur = v; cur != -1; cur = pre[cur])
            path.push_back(cur);
        reverse(path.begin(), path.end());
        for (size_t i = 0; i < path.size(); i++) {
            if (i) cout << " -> ";
            cout << path[i];
        }
        cout << endl;
    }

} // namespace BellmanFord


// ============================================================
// 2. SPFA 算法 —— 邻接表 + 队列实现
// ============================================================
// 适用场景：Bellman-Ford 的队列优化，期望更快（随机图 O(kE)）
// 最坏时间复杂度：O(VE)（网格图等特殊构造会退化）
// 空间复杂度：O(V + E)

namespace SPFA {

    // 邻接表存储：g[u] = vector<{v, w}>
    vector<pair<int, long long>> g[MAXN];

    long long dist[MAXN];
    int cnt[MAXN];          // cnt[v] = 从源点到 v 的最短路径经历的边数（用于判负环）
    bool inq[MAXN];         // inq[v] = true 表示 v 当前在队列中
    int pre[MAXN];          // 前驱
    int n, m;

    void init(int _n, int _m) {
        n = _n; m = _m;
        for (int i = 1; i <= n; i++) {
            g[i].clear();
        }
    }

    void add_edge(int u, int v, long long w) {
        g[u].push_back({v, w});
        // 如果是无向图，取消下一行的注释：
        // g[v].push_back({u, w});
    }

    /**
     * spfa(s) —— 从源点 s 出发的 SPFA 算法
     * @param s  源点编号
     * @return   true 表示无负环，false 表示存在负环
     *
     * 算法核心：
     * - 只有被更新过的节点才入队（因为只有它们可能引起新的松弛）
     * - cnt[v] 记录最短路径的边数，≥ n 则存在负环
     */
    bool spfa(int s) {
        // 初始化
        fill(dist, dist + n + 1, INF);
        fill(cnt, cnt + n + 1, 0);
        fill(inq, inq + n + 1, false);
        fill(pre, pre + n + 1, -1);

        queue<int> q;
        dist[s] = 0;
        q.push(s);
        inq[s] = true;
        cnt[s] = 0;  // 源点路径边数为 0

        while (!q.empty()) {
            int u = q.front(); q.pop();
            inq[u] = false;

            // 遍历 u 的所有出边，尝试松弛
            for (auto &edge : g[u]) {
                int v = edge.first;
                long long w = edge.second;

                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pre[v] = u;
                    cnt[v] = cnt[u] + 1;        // 更新路径边数

                    // 负环检测：路径边数 ≥ n → 经过 n+1 个节点 → 存在负环
                    if (cnt[v] >= n) {
                        return false;
                    }

                    if (!inq[v]) {
                        q.push(v);
                        inq[v] = true;
                    }
                }
            }
        }
        return true;       // 无负环
    }

    /**
     * spfa_detect_all() —— 检测全图是否存在负环（处理图不连通的情况）
     * 将所有节点初始入队，任意节点可达的负环都能被检测到
     * @return true 表示存在负环，false 表示无负环
     */
    bool spfa_detect_all() {
        fill(dist, dist + n + 1, 0);    // 初始距离设为 0
        fill(cnt, cnt + n + 1, 0);
        fill(inq, inq + n + 1, false);

        queue<int> q;
        // 所有节点初始入队
        for (int i = 1; i <= n; i++) {
            q.push(i);
            inq[i] = true;
        }

        while (!q.empty()) {
            int u = q.front(); q.pop();
            inq[u] = false;

            for (auto &edge : g[u]) {
                int v = edge.first;
                long long w = edge.second;

                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    cnt[v] = cnt[u] + 1;

                    if (cnt[v] >= n) {
                        return true;        // 存在负环！
                    }

                    if (!inq[v]) {
                        q.push(v);
                        inq[v] = true;
                    }
                }
            }
        }
        return false;      // 无负环
    }

    // 路径还原（与 Bellman-Ford 版本相同）
    void print_path(int v) {
        if (dist[v] == INF) {
            cout << "不可达" << endl;
            return;
        }
        vector<int> path;
        for (int cur = v; cur != -1; cur = pre[cur])
            path.push_back(cur);
        reverse(path.begin(), path.end());
        for (size_t i = 0; i < path.size(); i++) {
            if (i) cout << " -> ";
            cout << path[i];
        }
        cout << endl;
    }

} // namespace SPFA


// ============================================================
// 3. SPFA + SLF 优化（Small Label First）
// ============================================================
// SLF 核心思想：入队时，若新节点的 dist 比队首更小，
// 则将其插入队首（而非队尾），让距离更小的节点优先被处理。
// 实现上需要使用 deque 代替 queue。
//
// 注意：SLF 在随机图上通常有加速效果，但在某些特殊数据上可能变慢。

namespace SPFA_SLF {

    vector<pair<int, long long>> g[MAXN];
    long long dist[MAXN];
    int cnt[MAXN];
    bool inq[MAXN];
    int n, m;

    void init(int _n, int _m) {
        n = _n; m = _m;
        for (int i = 1; i <= n; i++)
            g[i].clear();
    }

    void add_edge(int u, int v, long long w) {
        g[u].push_back({v, w});
    }

    /**
     * spfa_slf(s) —— 带 SLF 优化的 SPFA
     * 使用 deque 实现：
     *   若 dist[v] < dist[q.front()] 则 push_front（SLF 规则）
     *   否则 push_back（正常入队）
     *
     * 可额外开启 LLL 优化（Large Label Last），但实际竞赛中 SLF 最常用
     */
    bool spfa_slf(int s) {
        fill(dist, dist + n + 1, INF);
        fill(cnt, cnt + n + 1, 0);
        fill(inq, inq + n + 1, false);

        deque<int> q;
        dist[s] = 0;
        q.push_back(s);
        inq[s] = true;

        while (!q.empty()) {
            int u = q.front(); q.pop_front();
            inq[u] = false;

            for (auto &edge : g[u]) {
                int v = edge.first;
                long long w = edge.second;

                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    cnt[v] = cnt[u] + 1;

                    if (cnt[v] >= n) {
                        return false;           // 负环
                    }

                    if (!inq[v]) {
                        // SLF 优化：更小距离 → 插入队首
                        if (!q.empty() && dist[v] < dist[q.front()]) {
                            q.push_front(v);
                        } else {
                            q.push_back(v);
                        }
                        inq[v] = true;
                    }
                }
            }
        }
        return true;
    }

    /**
     * spfa_slf_detect_all() —— SLF 版本的全局负环检测
     */
    bool spfa_slf_detect_all() {
        fill(dist, dist + n + 1, 0);
        fill(cnt, cnt + n + 1, 0);
        fill(inq, inq + n + 1, false);

        deque<int> q;
        for (int i = 1; i <= n; i++) {
            q.push_back(i);
            inq[i] = true;
        }

        while (!q.empty()) {
            int u = q.front(); q.pop_front();
            inq[u] = false;

            for (auto &edge : g[u]) {
                int v = edge.first;
                long long w = edge.second;

                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    cnt[v] = cnt[u] + 1;

                    if (cnt[v] >= n) {
                        return true;
                    }

                    if (!inq[v]) {
                        if (!q.empty() && dist[v] < dist[q.front()]) {
                            q.push_front(v);
                        } else {
                            q.push_back(v);
                        }
                        inq[v] = true;
                    }
                }
            }
        }
        return false;
    }

} // namespace SPFA_SLF


// ============================================================
// 4. 综合演示与测试
// ============================================================
// 下面是一个完整的测试例子，演示四种算法的使用。
// 示例图：
//   5 个节点，7 条边（有负权边，无负环）
//   1 → 2 (6)
//   1 → 3 (7)
//   2 → 4 (5)
//   2 → 3 (8)
//   3 → 4 (-3)    ← 负权边！
//   3 → 5 (9)
//   4 → 5 (7)
// 从节点 1 出发的最短路应为：
//   1→2: 6, 1→3: 7, 1→4: 4 (1→3→4), 1→5: 11 (1→3→4→5)

void run_demo() {
    cout << "========================================" << endl;
    cout << "  第19课 演示：Bellman-Ford 与 SPFA" << endl;
    cout << "========================================" << endl;

    // 边列表（手动定义，方便演示）
    struct { int u, v; long long w; } demo_edges[] = {
        {1, 2, 6},
        {1, 3, 7},
        {2, 4, 5},
        {2, 3, 8},
        {3, 4, -3},
        {3, 5, 9},
        {4, 5, 7}
    };

    // ---------- 1) Bellman-Ford ----------
    cout << "\n[1] Bellman-Ford 算法" << endl;
    {
        using namespace BellmanFord;
        BellmanFord::n = 5; BellmanFord::m = 7;
        for (int i = 1; i <= m; i++) {
            edges[i].u = demo_edges[i-1].u;
            edges[i].v = demo_edges[i-1].v;
            edges[i].w = demo_edges[i-1].w;
        }

        if (bellman_ford(1)) {
            cout << "最短路计算结果（无负环）：" << endl;
            for (int i = 1; i <= n; i++) {
                if (dist[i] == INF)
                    cout << "  节点 " << i << ": 不可达" << endl;
                else
                    cout << "  节点 " << i << ": " << dist[i] << endl;
            }
            // 展示路径还原
            cout << "从 1 到 5 的路径：";
            print_path(5);
        } else {
            cout << "检测到负环！" << endl;
        }
    }

    // ---------- 2) SPFA ----------
    cout << "\n[2] SPFA 算法" << endl;
    {
        using namespace SPFA;
        init(5, 7);
        for (int i = 0; i < 7; i++) {
            add_edge(demo_edges[i].u, demo_edges[i].v, demo_edges[i].w);
        }

        if (spfa(1)) {
            cout << "最短路计算结果（无负环）：" << endl;
            for (int i = 1; i <= n; i++) {
                if (dist[i] == INF)
                    cout << "  节点 " << i << ": 不可达" << endl;
                else
                    cout << "  节点 " << i << ": " << dist[i] << endl;
            }
            cout << "从 1 到 5 的路径：";
            print_path(5);
        } else {
            cout << "检测到负环！" << endl;
        }
    }

    // ---------- 3) SPFA 全局负环检测 ----------
    cout << "\n[3] SPFA 全局负环检测（通过）" << endl;
    {
        using namespace SPFA;
        init(5, 7);
        for (int i = 0; i < 7; i++) {
            add_edge(demo_edges[i].u, demo_edges[i].v, demo_edges[i].w);
        }
        if (spfa_detect_all())
            cout << "检测到负环！" << endl;
        else
            cout << "无负环。" << endl;
    }

    // ---------- 4) 构造一个负环并测试 ----------
    cout << "\n[4] 加入负权环 (4→2, -10) 后检测" << endl;
    {
        using namespace SPFA_SLF;
        init(5, 7);
        for (int i = 0; i < 7; i++) {
            add_edge(demo_edges[i].u, demo_edges[i].v, demo_edges[i].w);
        }
        // 添加边 4→2 (-10)，形成 2→3→4→2 的负环（-3+(-10)=-13 < 0）
        add_edge(4, 2, -10);

        if (spfa_slf_detect_all())
            cout << "检测到负环！（预期结果）" << endl;
        else
            cout << "未检测到负环（异常）" << endl;
    }

    // ---------- 5) SLF 优化演示 ----------
    cout << "\n[5] SPFA + SLF 优化（无负环图）" << endl;
    {
        using namespace SPFA_SLF;
        init(5, 7);
        for (int i = 0; i < 7; i++) {
            add_edge(demo_edges[i].u, demo_edges[i].v, demo_edges[i].w);
        }

        if (spfa_slf(1)) {
            cout << "SLF最短路计算：" << endl;
            for (int i = 1; i <= n; i++) {
                if (dist[i] == INF)
                    cout << "  节点 " << i << ": 不可达" << endl;
                else
                    cout << "  节点 " << i << ": " << dist[i] << endl;
            }
        } else {
            cout << "检测到负环！（异常，不应出现）" << endl;
        }
    }

    cout << "\n========================================" << endl;
    cout << "  演示结束" << endl;
    cout << "========================================" << endl;
}


// ============================================================
// 5. 经典题目模板（可直接提交 AC）
// ============================================================

/**
 * P3385 【模板】负环 —— 使用 SPFA 判负环
 *
 * 题目描述：T 组数据，每组给定 n 点 m 边，判断是否存在负环。
 * 输入格式：
 *   第一行 T
 *   每组数据第一行 n m
 *   接下来 m 行 u v w
 * 输出格式：YES（有负环）/ NO（无负环）
 *
 * 使用方法：注释掉 run_demo() 的调用，启用 solve_p3385()
 */

void solve_p3385() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;

        // 使用 SPFA_SLF 的 init 和 add_edge
        SPFA_SLF::init(n, m * 2);

        for (int i = 1; i <= m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            SPFA_SLF::add_edge(u, v, w);
            // 题目规定：若 w >= 0 则为双向边
            if (w >= 0) {
                SPFA_SLF::add_edge(v, u, w);
            }
        }

        if (SPFA_SLF::spfa_slf_detect_all())
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}


/**
 * P3371 【模板】单源最短路径（弱化版）—— 使用 SPFA
 *
 * 输入格式：n m s
 *          接下来 m 行 u v w
 * 输出格式：n 个数，s 到各点的最短距离
 *
 * 使用方法：注释掉其他 solve 调用，启用 solve_p3371()
 */

void solve_p3371() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s;
    cin >> n >> m >> s;

    SPFA::init(n, m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        SPFA::add_edge(u, v, w);
    }

    SPFA::spfa(s);

    for (int i = 1; i <= n; i++) {
        if (SPFA::dist[i] == INF)
            cout << 2147483647 << ' ';     // 题目要求不可达输出此值
        else
            cout << SPFA::dist[i] << ' ';
    }
    cout << '\n';
}


// ============================================================
// 主函数入口
// ============================================================
int main() {
    // ---- 演示模式 (默认启用，注释掉以运行竞赛题目) ----
    run_demo();

    // ---- 竞赛模式 (取消以下注释以提交到 OJ) ----
    // solve_p3385();
    // solve_p3371();

    return 0;
}
