/*
 * 第43课：最短路径入门
 * 日期：2026-06-27
 * 内容：Dijkstra 算法（单源最短路径）+ Floyd-Warshall 算法（多源最短路径）
 * 例题1：城市间最短距离（Dijkstra）
 * 例题2：多源最短路径（Floyd）
 */

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 105;
const int INF = 0x3f3f3f3f;  // 一个很大的数，当作「无穷大」

// ==================== Dijkstra 算法 ====================

/**
 * 使用 Dijkstra 算法计算从起点 start 到所有节点的最短距离
 *
 * 原理：
 *   1. 初始化 dist[start] = 0，其余为 INF
 *   2. 每次选出一个「未确定」且距离最小的节点 u
 *   3. 标记 u 为「已确定」
 *   4. 用 u 去「松弛」所有邻居：如果 dist[u] + g[u][v] < dist[v]，就更新 dist[v]
 *   5. 重复步骤 2-4，直到所有节点都确定
 *
 * 时间复杂度：O(V^2)，适合稠密图
 * 要求：图中所有边的权值必须 >= 0
 */

int g_dijk[MAXN][MAXN];   // 邻接矩阵存储图
int dist[MAXN];            // dist[i]：起点到 i 的最短距离
bool vis[MAXN];            // vis[i]：节点 i 是否已被「确定」
int n_dijk, m_dijk;        // n 个节点，m 条边

void dijkstra(int start) {
    // 第一步：初始化
    memset(dist, 0x3f, sizeof(dist));  // 所有距离设为「无穷大」
    memset(vis, 0, sizeof(vis));       // 所有节点标记为「未确定」
    dist[start] = 0;                    // 起点到自己的距离为 0

    // 第二步：循环 n 次，每次确定一个节点
    for (int i = 1; i <= n_dijk; i++) {
        // 在「未确定」的节点中，找出距离最小的节点 u
        int u = -1;
        int minDist = INF;
        for (int j = 1; j <= n_dijk; j++) {
            if (!vis[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }

        // 如果找不到（剩余节点都不可达），提前结束
        if (u == -1) break;

        // 将 u 标记为「已确定」
        vis[u] = true;

        // 用 u 去「松弛」所有邻居节点 v
        for (int v = 1; v <= n_dijk; v++) {
            // 如果有边 u-v，且 v 还未确定
            if (g_dijk[u][v] != INF && !vis[v]) {
                // 松弛操作：如果从起点到 u 再到 v 比当前记录的到 v 的距离更短
                if (dist[u] + g_dijk[u][v] < dist[v]) {
                    dist[v] = dist[u] + g_dijk[u][v];
                }
            }
        }
    }
}

// 例题1：城市间最短距离
void solve_problem1() {
    cout << "\n========== 例题1：城市间最短距离（Dijkstra）==========\n";
    cout << "题目：有 N 个城市，M 条双向道路。求从城市 1 到其他所有城市的最短距离。\n\n";

    // 初始化邻接矩阵（全设为 INF）
    memset(g_dijk, 0x3f, sizeof(g_dijk));

    // 输入节点数和边数
    cout << "请输入 N 和 M（如：5 7）：";
    cin >> n_dijk >> m_dijk;

    // 输入每条边
    cout << "请输入 " << m_dijk << " 条边（每行：u v w）：\n";
    for (int i = 0; i < m_dijk; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        // 处理重边：保留权值最小的那条
        if (w < g_dijk[u][v]) {
            g_dijk[u][v] = g_dijk[v][u] = w;  // 无向图，双向赋值
        }
    }

    // 运行 Dijkstra
    cout << "\n正在计算最短路径...\n";
    dijkstra(1);  // 以节点 1 为起点

    // 输出结果
    cout << "\n城市 1 到各城市的最短距离：\n";
    for (int i = 1; i <= n_dijk; i++) {
        cout << "  城市 " << i << "：";
        if (dist[i] == INF) {
            cout << "不可达 (-1)";
        } else {
            cout << dist[i];
        }
        cout << endl;
    }
    cout << endl;
}

// ==================== Floyd-Warshall 算法 ====================

/**
 * 使用 Floyd-Warshall 算法计算所有节点对之间的最短距离
 *
 * 原理（动态规划）：
 *   dp[k][i][j] = 只允许经过前 k 个节点中转时，i 到 j 的最短距离
 *   转移方程：dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
 *   滚动数组优化后只需二维数组
 *
 * 核心思想：试试「经过 k 中转」会不会让 i 到 j 的距离更短
 *
 * 时间复杂度：O(V^3)，适合 V <= 200 的场景
 * 优点：可以处理负权边（但不能有负环）
 */

int floyd_dist[MAXN][MAXN];  // floyd_dist[i][j]：i 到 j 的最短距离
int n_floyd, m_floyd, q_floyd;

void floyd() {
    // Floyd 三重循环核心
    // k 是「中转节点」，放在最外层
    for (int k = 1; k <= n_floyd; k++) {
        // i 是「起点」
        for (int i = 1; i <= n_floyd; i++) {
            // j 是「终点」
            for (int j = 1; j <= n_floyd; j++) {
                // 如果经过 k 中转更短，就更新
                // 注意：使用 long long 的写法（或者先判断是否 INF 避免溢出）
                if (floyd_dist[i][k] != INF && floyd_dist[k][j] != INF) {
                    if (floyd_dist[i][k] + floyd_dist[k][j] < floyd_dist[i][j]) {
                        floyd_dist[i][j] = floyd_dist[i][k] + floyd_dist[k][j];
                    }
                }
            }
        }
    }
}

// 例题2：多源最短路径
void solve_problem2() {
    cout << "\n========== 例题2：多源最短路径（Floyd）==========\n";
    cout << "题目：给定 N 个城市和 M 条道路，回答 Q 个查询（任意两个城市之间的最短距离）。\n\n";

    // 初始化距离矩阵
    memset(floyd_dist, 0x3f, sizeof(floyd_dist));

    // 输入节点数、边数、查询数
    cout << "请输入 N, M, Q（如：4 5 3）：";
    cin >> n_floyd >> m_floyd >> q_floyd;

    // 自己到自己的距离为 0
    for (int i = 1; i <= n_floyd; i++) {
        floyd_dist[i][i] = 0;
    }

    // 输入边
    cout << "请输入 " << m_floyd << " 条边（每行：u v w）：\n";
    for (int i = 0; i < m_floyd; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        // 处理重边：保留最小值
        if (w < floyd_dist[u][v]) {
            floyd_dist[u][v] = floyd_dist[v][u] = w;
        }
    }

    // 运行 Floyd
    cout << "\n正在计算所有点对的最短路径...\n";
    floyd();

    // 显示距离矩阵（可选）
    cout << "\n所有城市之间的最短距离矩阵：\n";
    cout << "    ";
    for (int j = 1; j <= n_floyd; j++) {
        cout << "  [" << j << "]";
    }
    cout << endl;
    for (int i = 1; i <= n_floyd; i++) {
        cout << " [" << i << "] ";
        for (int j = 1; j <= n_floyd; j++) {
            if (floyd_dist[i][j] == INF) {
                cout << " INF";
            } else {
                printf("%4d", floyd_dist[i][j]);
            }
        }
        cout << endl;
    }

    // 回答查询
    cout << "\n请输入 " << q_floyd << " 个查询（每行：a b）：\n";
    for (int i = 0; i < q_floyd; i++) {
        int a, b;
        cin >> a >> b;
        int ans = floyd_dist[a][b];
        if (ans == INF) {
            cout << a << " -> " << b << "：不可达 (-1)" << endl;
        } else {
            cout << a << " -> " << b << "：" << ans << endl;
        }
    }
    cout << endl;
}

// ==================== 测试用例自动演示 ====================

// 使用预设数据的测试用例（不需要手动输入）
void run_test_cases() {
    cout << "\n========== 自动测试用例演示 ==========\n";

    // ---- 测试 Dijkstra ----
    cout << "\n--- Dijkstra 测试 ---\n";
    cout << "图结构（5 个节点，7 条边）：\n";
    cout << "  边：1-2(2), 1-3(5), 2-3(1), 2-4(3), 3-4(2), 3-5(4), 4-5(1)\n";

    n_dijk = 5; m_dijk = 7;
    memset(g_dijk, 0x3f, sizeof(g_dijk));
    int test_edges[7][3] = {
        {1,2,2}, {1,3,5}, {2,3,1}, {2,4,3}, {3,4,2}, {3,5,4}, {4,5,1}
    };
    for (int i = 0; i < 7; i++) {
        int u = test_edges[i][0], v = test_edges[i][1], w = test_edges[i][2];
        g_dijk[u][v] = g_dijk[v][u] = w;
    }

    dijkstra(1);
    cout << "城市 1 到各城市的最短距离：\n";
    for (int i = 1; i <= n_dijk; i++) {
        cout << "  城市 " << i << "：" << (dist[i] == INF ? -1 : dist[i]) << endl;
    }

    // ---- 测试 Floyd ----
    cout << "\n--- Floyd 测试 ---\n";
    cout << "图结构（4 个节点，5 条边）：\n";
    cout << "  边：1-2(2), 1-3(5), 2-3(1), 2-4(3), 3-4(2)\n";

    n_floyd = 4; m_floyd = 5;
    memset(floyd_dist, 0x3f, sizeof(floyd_dist));
    for (int i = 1; i <= n_floyd; i++) floyd_dist[i][i] = 0;

    int test_edges2[5][3] = {
        {1,2,2}, {1,3,5}, {2,3,1}, {2,4,3}, {3,4,2}
    };
    for (int i = 0; i < 5; i++) {
        int u = test_edges2[i][0], v = test_edges2[i][1], w = test_edges2[i][2];
        floyd_dist[u][v] = floyd_dist[v][u] = w;
    }

    floyd();

    cout << "最短距离矩阵：\n    [1] [2] [3] [4]\n";
    for (int i = 1; i <= n_floyd; i++) {
        cout << "[" << i << "] ";
        for (int j = 1; j <= n_floyd; j++) {
            if (floyd_dist[i][j] == INF) cout << "INF ";
            else printf("%3d ", floyd_dist[i][j]);
        }
        cout << endl;
    }

    cout << "\n查询示例：\n";
    int queries[3][2] = {{1,4}, {2,3}, {2,4}};
    for (int i = 0; i < 3; i++) {
        int a = queries[i][0], b = queries[i][1];
        cout << "  " << a << " -> " << b << "：" << floyd_dist[a][b] << endl;
    }
    cout << endl;
}

// ==================== 主菜单 ====================

int main() {
    cout << "===========================================\n";
    cout << "   第43课：最短路径入门 - 算法演示程序\n";
    cout << "   日期：2026-06-27\n";
    cout << "===========================================\n";
    cout << "本程序包含：\n";
    cout << "  1. Dijkstra 算法实现（单源最短路径）\n";
    cout << "  2. Floyd-Warshall 算法实现（多源最短路径）\n";
    cout << "  3. 例题1：城市间最短距离（Dijkstra）\n";
    cout << "  4. 例题2：多源最短路径（Floyd）\n";
    cout << "  5. 自动测试用例演示\n";

    int choice;
    do {
        cout << "\n-------------------------------------------\n";
        cout << "请选择功能：\n";
        cout << "  1 - 例题1：城市间最短距离（Dijkstra，手动输入）\n";
        cout << "  2 - 例题2：多源最短路径（Floyd，手动输入）\n";
        cout << "  3 - 自动测试用例演示\n";
        cout << "  0 - 退出程序\n";
        cout << "请输入你的选择：";

        cin >> choice;

        switch (choice) {
            case 1:
                solve_problem1();
                break;
            case 2:
                solve_problem2();
                break;
            case 3:
                run_test_cases();
                break;
            case 0:
                cout << "感谢使用！再见！\n";
                break;
            default:
                cout << "输入无效，请重新选择！\n";
        }
    } while (choice != 0);

    return 0;
}
