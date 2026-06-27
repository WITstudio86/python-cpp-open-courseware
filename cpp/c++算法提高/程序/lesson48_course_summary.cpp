/*
 * ============================================================
 * 第48课：课程总结与进阶之路
 * lesson48_course_summary.cpp
 *
 * 模拟测试 - 包含3道题目，覆盖本课程核心知识点：
 *   1. 图的连通分量（图论 - DFS/BFS）
 *   2. 最小花费路径（动态规划）
 *   3. 最短路径计数（图 + DP）
 *
 * 适用对象：完成第41-47课学习的中小学生
 * ============================================================
 */

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
#include <climits>
using namespace std;

const int MAXN = 1005;
const int INF = 0x3f3f3f3f;
const int MOD = 1000000007;

// ============================================================
// 题目1：图的连通分量（DFS遍历）
// 问题：给定无向图，求连通分量个数和每个分量的大小
// ============================================================

vector<int> adj1[MAXN];   // 邻接表存储图
bool vis1[MAXN];           // 访问标记
int n1, m1;                // 节点数、边数

/*
 * DFS 遍历一个连通分量
 * 参数：u - 当前节点
 * 返回：该连通分量的大小
 */
int dfs1(int u) {
    vis1[u] = true;
    int sz = 1;  // 当前节点算一个
    for (int v : adj1[u]) {
        if (!vis1[v]) {
            sz += dfs1(v);
        }
    }
    return sz;
}

/*
 * 题目1 主求解函数
 * 遍历所有节点，对每个未访问节点启动DFS
 * 收集所有连通分量的大小，排序后输出
 */
void solve_connected_components() {
    cout << "\n========== 题目1：图的连通分量 ==========" << endl;
    cout << "输入 N, M：";
    cin >> n1 >> m1;

    // 初始化
    for (int i = 1; i <= n1; i++) {
        adj1[i].clear();
        vis1[i] = false;
    }

    // 建图
    cout << "输入 " << m1 << " 条边（u v）：" << endl;
    for (int i = 0; i < m1; i++) {
        int u, v;
        cin >> u >> v;
        adj1[u].push_back(v);
        adj1[v].push_back(u);  // 无向图
    }

    // 统计连通分量
    vector<int> component_sizes;
    for (int i = 1; i <= n1; i++) {
        if (!vis1[i]) {
            component_sizes.push_back(dfs1(i));
        }
    }

    // 排序后输出
    sort(component_sizes.begin(), component_sizes.end());

    cout << "\n结果：" << endl;
    cout << "  连通分量个数：" << component_sizes.size() << endl;
    cout << "  各分量大小：";
    for (int sz : component_sizes) {
        cout << sz << " ";
    }
    cout << endl;
}

// ============================================================
// 题目1 自动测试
// ============================================================
void test_connected_components() {
    cout << "\n--- 题目1 自动测试 ---" << endl;
    cout << "图：5个节点，3条边（1-2, 2-3, 4-5）" << endl;

    n1 = 5; m1 = 3;
    for (int i = 1; i <= n1; i++) {
        adj1[i].clear();
        vis1[i] = false;
    }
    adj1[1].push_back(2); adj1[2].push_back(1);
    adj1[2].push_back(3); adj1[3].push_back(2);
    adj1[4].push_back(5); adj1[5].push_back(4);

    vector<int> component_sizes;
    for (int i = 1; i <= n1; i++) {
        if (!vis1[i]) {
            component_sizes.push_back(dfs1(i));
        }
    }
    sort(component_sizes.begin(), component_sizes.end());

    cout << "输出：" << component_sizes.size() << endl;
    for (int sz : component_sizes) cout << sz << " ";
    cout << endl;
    cout << "解释：有两个连通分量，{1,2,3} 大小3，{4,5} 大小2" << endl;
}

// ============================================================
// 题目2：最小花费路径（二维DP）
// 问题：N×M网格，从(1,1)到(N,M)，只能向右或向下，求最小花费
// ============================================================

int cost_grid[MAXN][MAXN];  // 网格花费
int dp2[MAXN][MAXN];         // dp[i][j]：到达(i,j)的最小花费
int n2, m2;                  // 行数、列数

/*
 * 题目2 主求解函数
 * 状态定义：dp[i][j] = 从(1,1)到(i,j)的最小花费
 * 状态转移：dp[i][j] = cost[i][j] + min(dp[i-1][j], dp[i][j-1])
 * 边界条件：dp[1][1] = cost[1][1]
 */
int solve_min_cost_path() {
    // 初始化
    memset(dp2, 0x3f, sizeof(dp2));
    dp2[1][1] = cost_grid[1][1];

    // DP递推（拓扑序：从上到下、从左到右）
    for (int i = 1; i <= n2; i++) {
        for (int j = 1; j <= m2; j++) {
            if (i == 1 && j == 1) continue;
            int from_up = (i > 1) ? dp2[i-1][j] : INF;
            int from_left = (j > 1) ? dp2[i][j-1] : INF;
            dp2[i][j] = cost_grid[i][j] + min(from_up, from_left);
        }
    }

    return dp2[n2][m2];
}

/*
 * 题目2 交互式输入
 */
void solve_min_cost_path_interactive() {
    cout << "\n========== 题目2：最小花费路径 ==========" << endl;
    cout << "输入 N, M：";
    cin >> n2 >> m2;

    cout << "输入网格（" << n2 << "行 " << m2 << "列）：" << endl;
    for (int i = 1; i <= n2; i++) {
        for (int j = 1; j <= m2; j++) {
            cin >> cost_grid[i][j];
        }
    }

    int ans = solve_min_cost_path();
    cout << "\n结果：最小花费 = " << ans << endl;
}

/*
 * 题目2 自动测试
 */
void test_min_cost_path() {
    cout << "\n--- 题目2 自动测试 ---" << endl;
    cout << "网格（3×3）：" << endl;
    n2 = 3; m2 = 3;
    int test[3][3] = {
        {1, 3, 1},
        {1, 5, 1},
        {4, 2, 1}
    };
    for (int i = 0; i < 3; i++) {
        cout << "  ";
        for (int j = 0; j < 3; j++) {
            cost_grid[i+1][j+1] = test[i][j];
            cout << test[i][j] << " ";
        }
        cout << endl;
    }

    int ans = solve_min_cost_path();
    cout << "输出：" << ans << endl;
    cout << "解释：最优路径 (1,1)→(1,2)→(1,3)→(2,3)→(3,3)，花费 1+3+1+1+1=7" << endl;

    // 打印DP表格
    cout << "\nDP表格（dp[i][j] = 到(i,j)的最小花费）：" << endl;
    for (int i = 1; i <= n2; i++) {
        cout << "  ";
        for (int j = 1; j <= m2; j++) {
            cout << dp2[i][j] << "\t";
        }
        cout << endl;
    }
}

// ============================================================
// 题目3：最短路径计数（图 + DP / 拓扑排序）
// 问题：给定DAG，求从1到N的最短路径长度（边数）和路径条数
// ============================================================

vector<int> adj3[MAXN];     // 邻接表
int indegree[MAXN];          // 入度（用于拓扑排序）
int dist[MAXN];              // dist[i]：从1到i的最短距离（边数）
int cnt[MAXN];               // cnt[i]：从1到i的最短路径条数
int n3, m3;                  // 节点数、边数

/*
 * 题目3 主求解函数（拓扑排序 + DP）
 *
 * 核心思路：
 * 1. 因为图是DAG，先用拓扑排序得到DP顺序
 * 2. 在拓扑序上做DP：
 *    - dist[v] = min(dist[v], dist[u] + 1)
 *    - cnt[v] = 如果 dist[v] 被更新，则 cnt[v] = cnt[u]
 *               如果 dist[v] == dist[u] + 1，则 cnt[v] += cnt[u]
 */
void solve_shortest_path_count() {
    // 初始化
    for (int i = 1; i <= n3; i++) {
        indegree[i] = 0;
        dist[i] = INF;
        cnt[i] = 0;
    }

    // 计算入度
    for (int u = 1; u <= n3; u++) {
        for (int v : adj3[u]) {
            indegree[v]++;
        }
    }

    // 拓扑排序（Kahn算法）
    queue<int> q;
    for (int i = 1; i <= n3; i++) {
        if (indegree[i] == 0) q.push(i);
    }

    // 起点初始化
    dist[1] = 0;
    cnt[1] = 1;

    while (!q.empty()) {
        int u = q.front(); q.pop();

        // 如果u不可达，跳过
        if (dist[u] == INF) {
            for (int v : adj3[u]) {
                if (--indegree[v] == 0) q.push(v);
            }
            continue;
        }

        // 用u更新所有邻居v
        for (int v : adj3[u]) {
            if (dist[v] > dist[u] + 1) {
                // 找到更短的路径 → 更新距离和计数
                dist[v] = dist[u] + 1;
                cnt[v] = cnt[u];
            } else if (dist[v] == dist[u] + 1) {
                // 找到同样短的路径 → 累加计数
                cnt[v] = (cnt[v] + cnt[u]) % MOD;
            }

            if (--indegree[v] == 0) {
                q.push(v);
            }
        }
    }
}

/*
 * 题目3 交互式输入
 */
void solve_shortest_path_count_interactive() {
    cout << "\n========== 题目3：最短路径计数 ==========" << endl;
    cout << "输入 N, M：";
    cin >> n3 >> m3;

    for (int i = 1; i <= n3; i++) adj3[i].clear();

    cout << "输入 " << m3 << " 条边（u v）：" << endl;
    for (int i = 0; i < m3; i++) {
        int u, v;
        cin >> u >> v;
        adj3[u].push_back(v);
    }

    solve_shortest_path_count();

    cout << "\n结果：" << endl;
    if (dist[n3] == INF) {
        cout << "No path（不可达）" << endl;
    } else {
        cout << "  最短路径长度（边数）：" << dist[n3] << endl;
        cout << "  最短路径条数：" << cnt[n3] << endl;
    }
}

/*
 * 题目3 自动测试
 */
void test_shortest_path_count() {
    cout << "\n--- 题目3 自动测试 ---" << endl;
    cout << "图：4个节点，5条边（DAG）" << endl;
    cout << "  边：1→2, 1→3, 2→3, 2→4, 3→4" << endl;

    n3 = 4; m3 = 5;
    for (int i = 1; i <= n3; i++) adj3[i].clear();

    adj3[1].push_back(2);
    adj3[1].push_back(3);
    adj3[2].push_back(3);
    adj3[2].push_back(4);
    adj3[3].push_back(4);

    solve_shortest_path_count();

    cout << "输出：" << endl;
    cout << "  最短路径长度：" << dist[n3] << "（经过2条边）" << endl;
    cout << "  最短路径条数：" << cnt[n3] << "（1→2→4 和 1→3→4 共2条）" << endl;

    // 打印每个节点的状态
    cout << "\n各节点状态：" << endl;
    cout << "  节点\t最短距离\t路径数" << endl;
    for (int i = 1; i <= n3; i++) {
        cout << "  " << i << "\t";
        if (dist[i] == INF) cout << "INF";
        else cout << dist[i];
        cout << "\t\t" << cnt[i] << endl;
    }
}

// ============================================================
// 进阶学习路线展示
// ============================================================

void show_learning_path() {
    cout << "\n========== 进阶学习路线 ==========" << endl;
    cout << endl;
    cout << "  ┌─────────────────────────────────────────────────────┐" << endl;
    cout << "  │ 阶段一：基础巩固（已完成）                          │" << endl;
    cout << "  │   图论基础 · 基础算法 · 动态规划入门 · 竞赛技巧     │" << endl;
    cout << "  ├─────────────────────────────────────────────────────┤" << endl;
    cout << "  │ 阶段二：数据结构进阶                                │" << endl;
    cout << "  │   线段树 · 树状数组 · 并查集优化 · ST表 · 单调栈    │" << endl;
    cout << "  ├─────────────────────────────────────────────────────┤" << endl;
    cout << "  │ 阶段三：图论进阶                                    │" << endl;
    cout << "  │   强连通分量 · 割点与桥 · 二分图 · 网络流 · LCA    │" << endl;
    cout << "  ├─────────────────────────────────────────────────────┤" << endl;
    cout << "  │ 阶段四：动态规划进阶                                │" << endl;
    cout << "  │   区间DP · 树形DP · 状压DP · 数位DP · 斜率优化     │" << endl;
    cout << "  ├─────────────────────────────────────────────────────┤" << endl;
    cout << "  │ 阶段五：专项算法                                    │" << endl;
    cout << "  │   字符串 · 数论 · 计算几何 · 概率DP · 博弈论       │" << endl;
    cout << "  └─────────────────────────────────────────────────────┘" << endl;
    cout << endl;
    cout << "  推荐OJ平台：" << endl;
    cout << "    洛谷(luogu.com.cn) · Codeforces · AtCoder · AcWing" << endl;
    cout << endl;
    cout << "  推荐策略：每周5-10题 + 参加比赛 + 多看题解 + 坚持对拍" << endl;
}

// ============================================================
// 主菜单
// ============================================================

void show_menu() {
    cout << "\n╔══════════════════════════════════════════════╗" << endl;
    cout << "║  第48课：课程总结与进阶之路 — 模拟测试      ║" << endl;
    cout << "╠══════════════════════════════════════════════╣" << endl;
    cout << "║  模拟测试（3道题）：                         ║" << endl;
    cout << "║    1. 图的连通分量（图论 - DFS遍历）          ║" << endl;
    cout << "║    2. 最小花费路径（动态规划）                ║" << endl;
    cout << "║    3. 最短路径计数（图 + DP / 拓扑排序）      ║" << endl;
    cout << "╠══════════════════════════════════════════════╣" << endl;
    cout << "║    4. 自动测试全部3道题                       ║" << endl;
    cout << "║    5. 查看进阶学习路线                        ║" << endl;
    cout << "║    0. 退出                                    ║" << endl;
    cout << "╚══════════════════════════════════════════════╝" << endl;
    cout << "请选择 [0-5]：";
}

int main() {
    int choice;
    do {
        show_menu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\n提示：也可直接选择 4 查看自动测试结果" << endl;
                solve_connected_components();
                break;
            case 2:
                cout << "\n提示：也可直接选择 4 查看自动测试结果" << endl;
                solve_min_cost_path_interactive();
                break;
            case 3:
                cout << "\n提示：也可直接选择 4 查看自动测试结果" << endl;
                solve_shortest_path_count_interactive();
                break;
            case 4:
                test_connected_components();
                test_min_cost_path();
                test_shortest_path_count();
                break;
            case 5:
                show_learning_path();
                break;
            case 0:
                cout << "\n╔══════════════════════════════════════════════╗" << endl;
                cout << "║  恭喜你完成了「C++算法提高」全部课程！       ║" << endl;
                cout << "║                                              ║" << endl;
                cout << "║  从图论基础到最短路径，从动态规划到          ║" << endl;
                cout << "║  算法综合实战，你已经在算法之路上            ║" << endl;
                cout << "║  迈出了坚实的一大步。                        ║" << endl;
                cout << "║                                              ║" << endl;
                cout << "║  记住：算法之路没有终点，只有不断            ║" << endl;
                cout << "║  前进的旅程。坚持做题，坚持思考，            ║" << endl;
                cout << "║  你一定会越来越强！                          ║" << endl;
                cout << "║                                              ║" << endl;
                cout << "║  再见，未来的算法高手！                      ║" << endl;
                cout << "╚══════════════════════════════════════════════╝" << endl;
                break;
            default:
                cout << "无效选项，请重新选择。" << endl;
        }
    } while (choice != 0);

    return 0;
}
