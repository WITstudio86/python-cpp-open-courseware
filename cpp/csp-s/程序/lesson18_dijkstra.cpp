/**
 * ===========================================================================
 * 课程编号：第18课
 * 课程标题：Dijkstra 算法
 * 对应考纲：单源最短路径、朴素 O(V²) 与堆优化 O(E log V)、
 *           贪心正确性证明、负权边不可用原因、路径还原
 * ===========================================================================
 */

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
#include <utility>
using namespace std;
using ll = long long;

// ============================================================================
// 全局常量
// ============================================================================
const int MAXN = 1e5 + 5;       // 最大顶点数
const int INF = 0x3f3f3f3f;     // 朴素版无穷大（约 1.06e9，两倍不溢）
const ll LLINF = 1e18;          // 堆优化版无穷大（边权可达 1e9 时使用）

// ============================================================================
// 1. 朴素 Dijkstra —— O(V²)，适合稠密图（V ≤ 1000）
//    使用邻接矩阵存图
// ============================================================================
namespace NaiveDijkstra {

int n, m;
int g[1005][1005];  // 邻接矩阵，g[u][v] = 边权，INF 表示无边
int dist[MAXN];
bool vis[MAXN];     // vis[u] = true 表示 u 的最短路径已确定

// 初始化邻接矩阵
void init(int _n) {
    n = _n;
    memset(g, 0x3f, sizeof(g));
    for (int i = 1; i <= n; i++) g[i][i] = 0; // 自己到自己的距离为 0
}

// 添加有向边
void add_edge(int u, int v, int w) {
    g[u][v] = min(g[u][v], w); // 处理重边：取最小权值
}

// 添加无向边
void add_undirected(int u, int v, int w) {
    g[u][v] = min(g[u][v], w);
    g[v][u] = min(g[v][u], w);
}

/**
 * 朴素 Dijkstra 算法
 * 时间复杂度：O(V²)
 * 核心思想：每次从「未确定」的顶点中选出 dist 最小的，
 *          将其标记为「已确定」，然后用它松弛所有邻接点。
 */
void dijkstra(int s) {
    // 初始化距离数组
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    dist[s] = 0;

    for (int i = 1; i <= n; i++) {
        // --- 步骤 1：从未确定顶点中找出 dist 最小的 u ---
        int u = -1;
        for (int j = 1; j <= n; j++)
            if (!vis[j] && (u == -1 || dist[j] < dist[u]))
                u = j;

        // 所有剩余顶点都不可达，提前退出
        if (u == -1 || dist[u] == INF) break;

        // --- 步骤 2：标记 u 为已确定 ---
        vis[u] = true;

        // --- 步骤 3：用 u 松弛所有邻接点 ---
        for (int v = 1; v <= n; v++) {
            if (!vis[v] && g[u][v] != INF) {
                // 松弛操作：尝试通过 u 到达 v 是否更短
                if (dist[v] > dist[u] + g[u][v]) {
                    dist[v] = dist[u] + g[u][v];
                }
            }
        }
    }
}

} // namespace NaiveDijkstra

// ============================================================================
// 2. 堆优化 Dijkstra —— O((V+E) log V)，适合稀疏图（V ≤ 10⁵）
//    使用 vector 邻接表 + priority_queue 小根堆
// ============================================================================
namespace HeapDijkstra {

int n, m;
vector<pair<int, ll>> g[MAXN]; // 邻接表：g[u] = {v, 权值 w}
ll dist[MAXN];                  // 注意：边权可能很大，用 long long
bool vis[MAXN];

void init(int _n) {
    n = _n;
    for (int i = 1; i <= n; i++) g[i].clear();
}

// 添加有向边
void add_edge(int u, int v, ll w) {
    g[u].push_back({v, w});
}

// 添加无向边
void add_undirected(int u, int v, ll w) {
    g[u].push_back({v, w});
    g[v].push_back({u, w});
}

/**
 * 堆优化 Dijkstra 算法
 * 时间复杂度：O((V+E) log V)
 *
 * 核心思想：用优先队列（小根堆）维护当前 dist 最小的顶点，
 *          pop 出队时进行松弛操作。
 *
 * 「懒删除」技巧：
 * - 同一个顶点可能多次入堆（每次 dist 更新时）
 * - 堆顶可能是该顶点的「旧记录」
 * - 通过 if (vis[u]) continue 跳过已确定顶点的旧记录
 * - 这样避免了手写 decrease-key 的复杂性
 */
void dijkstra(int s) {
    // 初始化
    fill(dist, dist + n + 1, LLINF); // 注意：用 fill 而非 memset（因为 long long）
    fill(vis, vis + n + 1, false);
    dist[s] = 0;

    // 小根堆：pair<当前距离, 顶点编号>
    // greater<pair> 使得堆根为最小距离的 pair
    priority_queue<
        pair<ll, int>,              // 元素类型
        vector<pair<ll, int>>,      // 底层容器
        greater<pair<ll, int>>      // 比较器：小根堆
    > pq;
    pq.push({0, s});

    while (!pq.empty()) {
        // 取出当前距离最近的顶点
        auto [d, u] = pq.top(); pq.pop();

        // 懒删除：如果 u 已经确定了，这条记录是过期的，跳过
        if (vis[u]) continue;

        // 标记 u 为已确定
        vis[u] = true;

        // 用 u 松弛所有邻接点 v
        for (auto [v, w] : g[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                // 注意：这里不标记 vis[v]，因为 v 的距离后续可能还会被更新得更小
                // 只是把新的 (dist[v], v) 入堆
                pq.push({dist[v], v});
            }
        }
    }
}

} // namespace HeapDijkstra

// ============================================================================
// 3. 堆优化 Dijkstra + 路径还原
//    在松弛的同时记录前驱顶点 pre[v]，最后从终点回溯
// ============================================================================
namespace DijkstraWithPath {

int n, m;
vector<pair<int, int>> g[MAXN];
int dist[MAXN];
int pre[MAXN];  // pre[v] = 在 s→v 最短路径上 v 的前一个顶点
bool vis[MAXN];

void init(int _n) {
    n = _n;
    for (int i = 1; i <= n; i++) g[i].clear();
}

void add_edge(int u, int v, int w) {
    g[u].push_back({v, w});
}

void add_undirected(int u, int v, int w) {
    g[u].push_back({v, w});
    g[v].push_back({u, w});
}

/**
 * Dijkstra 算法 + 路径前驱记录
 */
void dijkstra(int s) {
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    memset(pre, -1, sizeof(pre)); // -1 表示无前驱（起点或不可达）
    dist[s] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, s});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (vis[u]) continue;
        vis[u] = true;

        for (auto [v, w] : g[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pre[v] = u; // ← 关键：记录 v 是从 u 走过来的
                pq.push({dist[v], v});
            }
        }
    }
}

/**
 * 还原从源点 s 到目标点 t 的最短路径
 * 返回路径上的顶点序列（从 s 到 t）
 * 如果 t 不可达，返回空 vector
 */
vector<int> get_path(int s, int t) {
    (void)s; // s 用于标记源点（API 文档性参数），前驱由 pre[] 维护
    vector<int> path;
    if (dist[t] == INF) return path; // 不可达

    // 从终点 t 向前回溯，直到起点 s（pre[s] == -1）
    for (int v = t; v != -1; v = pre[v])
        path.push_back(v);

    // 由于回溯是倒序的，需要反转
    reverse(path.begin(), path.end());
    return path;
}

} // namespace DijkstraWithPath

// ============================================================================
// 综合演示：测试所有三种 Dijkstra 实现
// ============================================================================
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cout << "===== 第18课：Dijkstra 算法 演示 =====\n\n";

    // -----------------------------------------------------------------------
    // 测试图：6 个顶点，7 条有向边（非负权）
    //
    //         (2)     (5)
    //    1 -------> 2 -----> 4
    //    |          |         ^
    // (3)|      (1) |    (1) /
    //    v          v       /
    //    3 -------> 5 -----
    //        (4)      (2)
    //             6 (孤立点，无入边无出边)
    // -----------------------------------------------------------------------

    // --- 演示 1：朴素 Dijkstra O(V²) ---
    cout << "【1. 朴素 Dijkstra O(V²)】\n";
    {
        using namespace NaiveDijkstra;
        init(6);
        add_edge(1, 2, 2);
        add_edge(1, 3, 3);
        add_edge(2, 4, 5);
        add_edge(2, 5, 1);
        add_edge(3, 5, 4);
        add_edge(5, 4, 2);
        add_edge(5, 4, 1);        // 测试重边处理：min(2, 1) = 1

        dijkstra(1);

        cout << "源点 1 到各顶点的最短距离：\n";
        for (int i = 1; i <= 6; i++) {
            cout << "  dist[1->" << i << "] = ";
            if (dist[i] == INF) cout << "INF (不可达)";
            else cout << dist[i];
            cout << '\n';
        }
        cout << '\n';
    }

    // --- 演示 2：堆优化 Dijkstra O(E log V) ---
    cout << "【2. 堆优化 Dijkstra O(E log V)】\n";
    {
        using namespace HeapDijkstra;
        init(6);
        add_edge(1, 2, 2);
        add_edge(1, 3, 3);
        add_edge(2, 4, 5);
        add_edge(2, 5, 1);
        add_edge(3, 5, 4);
        add_edge(5, 4, 1);

        dijkstra(1);

        cout << "源点 1 到各顶点的最短距离：\n";
        for (int i = 1; i <= 6; i++) {
            cout << "  dist[1->" << i << "] = ";
            if (dist[i] == LLINF) cout << "INF (不可达)";
            else cout << dist[i];
            cout << '\n';
        }
        cout << '\n';
    }

    // --- 演示 3：Dijkstra + 路径还原 ---
    cout << "【3. Dijkstra + 路径还原】\n";
    {
        using namespace DijkstraWithPath;
        init(6);
        add_edge(1, 2, 2);
        add_edge(1, 3, 3);
        add_edge(2, 4, 5);
        add_edge(2, 5, 1);
        add_edge(3, 5, 4);
        add_edge(5, 4, 1);

        dijkstra(1);

        // 查询 1 -> 4 的最短路径
        cout << "1 → 4 最短距离：" << dist[4] << '\n';
        vector<int> path14 = get_path(1, 4);
        cout << "1 → 4 路径：";
        for (size_t i = 0; i < path14.size(); i++)
            cout << path14[i] << (i + 1 < path14.size() ? " → " : "");
        cout << '\n';

        // 查询 1 -> 6 的最短路径（不可达）
        cout << "\n1 → 6 最短距离：";
        vector<int> path16 = get_path(1, 6);
        if (path16.empty())
            cout << "不可达\n";
        else
            cout << dist[6] << '\n';
    }

    // --- 演示 4：重边处理测试 ---
    cout << "\n【4. 重边处理测试】\n";
    {
        using namespace HeapDijkstra;
        init(3);
        add_edge(1, 2, 100);  // 劣弧
        add_edge(1, 2, 5);    // 优弧
        add_edge(2, 3, 10);

        dijkstra(1);
        cout << "边(1,2) 有两条：权 100 和权 5\n";
        cout << "1→3 最短距离 = " << dist[3]
             << "（正确值应为 15，取最小边权 5 后计算得出）\n";
    }

    cout << "\n===== 演示结束 =====\n";
    return 0;
}
