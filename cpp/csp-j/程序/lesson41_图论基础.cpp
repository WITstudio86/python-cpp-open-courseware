/**
 * CSP-J 备考课程 - 第41课：图论基础
 *
 * 本文件包含：
 *   1. 邻接矩阵存储与基本操作
 *   2. 邻接表存储与基本操作
 *   3. 带权图邻接表
 *   4. 度数统计（入度/出度）
 *   5. 基础DFS遍历
 *   6. 基础BFS遍历
 *
 * 知识点：图的定义、有向/无向图、带权/无权图、邻接矩阵与邻接表、
 *         顶点的度、路径与回路、图的遍历基础
 */

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

// ======================== 常量定义 ========================
const int N = 100005;  // 最大顶点数

// ======================== 1. 邻接矩阵存储 ========================

/**
 * 邻接矩阵演示
 * 适用于 n <= 1000 的稠密图
 */
void demo_adjacency_matrix() {
    cout << "========== 1. 邻接矩阵演示 ==========" << endl;

    const int MAXN = 10;
    int g[MAXN][MAXN];  // 邻接矩阵
    memset(g, 0, sizeof(g));

    int n = 5, m = 6;
    // 边列表：(1,2) (1,3) (2,3) (2,4) (3,4) (4,5)
    int edges[][2] = {{1,2}, {1,3}, {2,3}, {2,4}, {3,4}, {4,5}};

    cout << "建图（无向图）：" << endl;
    for (int i = 0; i < m; i++) {
        int u = edges[i][0], v = edges[i][1];
        g[u][v] = 1;
        g[v][u] = 1;  // 无向图双向标记
        cout << "  添加边: " << u << " <-> " << v << endl;
    }

    // 判断边是否存在
    cout << "\n判断边：1和3之间有边吗？" << (g[1][3] ? " 有" : " 没有") << endl;
    cout << "判断边：1和5之间有边吗？" << (g[1][5] ? " 有" : " 没有") << endl;

    // 遍历顶点1的所有邻接点
    cout << "顶点1的邻接点：";
    for (int v = 1; v <= n; v++) {
        if (g[1][v]) cout << v << " ";
    }
    cout << endl;

    // 打印整个邻接矩阵
    cout << "\n邻接矩阵：" << endl;
    cout << "  ";
    for (int j = 1; j <= n; j++) cout << j << " ";
    cout << endl;
    for (int i = 1; i <= n; i++) {
        cout << i << " ";
        for (int j = 1; j <= n; j++) {
            cout << g[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// ======================== 2. 邻接表存储 ========================

/**
 * 邻接表演示
 * 适用于稀疏图，n 可达 100000+
 */
void demo_adjacency_list() {
    cout << "========== 2. 邻接表演示 ==========" << endl;

    vector<int> g[N];
    int n = 5, m = 6;
    int edges[][2] = {{1,2}, {1,3}, {2,3}, {2,4}, {3,4}, {4,5}};

    cout << "建图（无向图）：" << endl;
    for (int i = 0; i < m; i++) {
        int u = edges[i][0], v = edges[i][1];
        g[u].push_back(v);
        g[v].push_back(u);  // 无向图：双向都要存
        cout << "  添加边: " << u << " <-> " << v << endl;
    }

    // 遍历每个顶点的邻接点
    cout << "\n每个顶点的邻接点：" << endl;
    for (int i = 1; i <= n; i++) {
        cout << "  顶点" << i << "的邻接点：";
        for (int v : g[i]) {
            cout << v << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// ======================== 3. 带权图邻接表 ========================

/**
 * 带权图邻接表演示
 * 每条边有一个权值 weight
 */
void demo_weighted_graph() {
    cout << "========== 3. 带权图邻接表演示 ==========" << endl;

    struct Edge {
        int to;      // 目标顶点
        int weight;  // 边权
    };

    vector<Edge> g[N];
    int n = 4, m = 5;

    // 边列表：(u, v, w)
    // (1,2,10) (1,3,5) (2,3,2) (2,4,8) (3,4,3)
    cout << "建图（带权有向图）：" << endl;
    g[1].push_back({2, 10});
    g[1].push_back({3, 5});
    g[2].push_back({3, 2});
    g[2].push_back({4, 8});
    g[3].push_back({4, 3});

    for (int i = 1; i <= n; i++) {
        for (Edge e : g[i]) {
            cout << "  " << i << " -> " << e.to << " (权值=" << e.weight << ")" << endl;
        }
    }

    // 遍历顶点1的所有邻接边
    cout << "\n顶点1的邻接边：" << endl;
    for (Edge e : g[1]) {
        cout << "  到顶点" << e.to << "，权值=" << e.weight << endl;
    }
    cout << endl;
}

// ======================== 4. 度数统计 ========================

/**
 * 度数统计演示
 * 统计有向图的入度和出度
 */
void demo_degree_calculation() {
    cout << "========== 4. 度数统计演示 ==========" << endl;

    int n = 5, m = 7;
    int edges[][2] = {{1,2}, {1,3}, {2,3}, {2,4}, {3,4}, {4,5}, {5,1}};

    int indeg[N] = {0}, outdeg[N] = {0};
    vector<int> g[N];

    cout << "建图（有向图）：" << endl;
    for (int i = 0; i < m; i++) {
        int u = edges[i][0], v = edges[i][1];
        g[u].push_back(v);  // 有向图，只存一个方向
        outdeg[u]++;
        indeg[v]++;
        cout << "  " << u << " -> " << v << endl;
    }

    cout << "\n顶点度数统计：" << endl;
    cout << "顶点\t入度\t出度\t总度数" << endl;
    for (int i = 1; i <= n; i++) {
        cout << i << "\t" << indeg[i] << "\t" << outdeg[i]
             << "\t" << indeg[i] + outdeg[i] << endl;
    }

    // 验证：入度总和 = 出度总和 = 边数
    int sumIn = 0, sumOut = 0;
    for (int i = 1; i <= n; i++) {
        sumIn += indeg[i];
        sumOut += outdeg[i];
    }
    cout << "\n验证：入度总和=" << sumIn << ", 出度总和=" << sumOut
         << ", 边数=" << m << endl;
    cout << "（入度总和 = 出度总和 = 边数，性质成立）" << endl << endl;
}

// ======================== 5. 基础DFS遍历 ========================

bool vis[N];
vector<int> dfs_g[N];

void dfs(int u) {
    vis[u] = true;
    cout << u << " ";  // 访问顶点
    for (int v : dfs_g[u]) {
        if (!vis[v]) {
            dfs(v);
        }
    }
}

void demo_dfs_traversal() {
    cout << "========== 5. 基础DFS遍历演示 ==========" << endl;

    int n = 7, m = 6;
    int edges[][2] = {{1,2}, {1,3}, {2,4}, {2,5}, {3,6}, {3,7}};

    for (int i = 0; i < m; i++) {
        int u = edges[i][0], v = edges[i][1];
        dfs_g[u].push_back(v);
        dfs_g[v].push_back(u);
    }

    memset(vis, false, sizeof(vis));

    cout << "从顶点1开始DFS遍历：";
    dfs(1);
    cout << endl << endl;
}

// ======================== 6. 基础BFS遍历 ========================

bool bfs_vis[N];

void bfs(int start, vector<int> g[], int n) {
    queue<int> q;
    q.push(start);
    bfs_vis[start] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << u << " ";

        for (int v : g[u]) {
            if (!bfs_vis[v]) {
                bfs_vis[v] = true;
                q.push(v);
            }
        }
    }
}

void demo_bfs_traversal() {
    cout << "========== 6. 基础BFS遍历演示 ==========" << endl;

    int n = 7, m = 6;
    int edges[][2] = {{1,2}, {1,3}, {2,4}, {2,5}, {3,6}, {3,7}};

    vector<int> g[N];
    for (int i = 0; i < m; i++) {
        int u = edges[i][0], v = edges[i][1];
        g[u].push_back(v);
        g[v].push_back(u);
    }

    memset(bfs_vis, false, sizeof(bfs_vis));

    cout << "从顶点1开始BFS遍历：";
    bfs(1, g, n);
    cout << endl << endl;

    cout << "说明：DFS（深度优先）: 1 2 4 5 3 6 7" << endl;
    cout << "      BFS（广度优先）: 1 2 3 4 5 6 7" << endl;
    cout << "      DFS是一条路走到黑，BFS是逐层扩展。" << endl << endl;
}

// ======================== 7. 路径判断 ========================

/**
 * 判断两个顶点之间是否存在路径（BFS实现）
 */
bool has_path(int start, int target, vector<int> g[], int n) {
    bool visited[N] = {false};
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == target) return true;

        for (int v : g[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    return false;
}

void demo_path_check() {
    cout << "========== 7. 路径可达性判断 ==========" << endl;

    int n = 6, m = 5;
    int edges[][2] = {{1,2}, {2,3}, {3,4}, {5,6}};

    vector<int> g[N];
    for (int i = 0; i < m; i++) {
        int u = edges[i][0], v = edges[i][1];
        g[u].push_back(v);
        g[v].push_back(u);
    }

    cout << "图结构：1-2-3-4 和 5-6 是两个连通块" << endl;
    cout << "1到4有路径吗？" << (has_path(1, 4, g, n) ? " 有" : " 没有") << endl;
    cout << "1到5有路径吗？" << (has_path(1, 5, g, n) ? " 有" : " 没有") << endl;
    cout << "5到6有路径吗？" << (has_path(5, 6, g, n) ? " 有" : " 没有") << endl;
    cout << endl;
}

// ======================== 8. 连通块计数 ========================

void demo_connected_components() {
    cout << "========== 8. 连通块计数 ==========" << endl;

    // 三个连通块：1-2-3，4-5，以及孤立点 6
    const int n = 6;
    int edges[][2] = {{1, 2}, {2, 3}, {4, 5}};
    const int m = 3;
    vector<int> g[N];
    for (int i = 0; i < m; i++) {
        int u = edges[i][0], v = edges[i][1];
        g[u].push_back(v);
        g[v].push_back(u);
    }

    bool visited[N];
    memset(visited, false, sizeof(visited));

    // 使用普通 DFS，避免依赖递归 lambda
    // 这里用静态辅助：直接写循环式 BFS 更稳妥
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (visited[i]) continue;
        cnt++;
        queue<int> q;
        q.push(i);
        visited[i] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }
    cout << "图：1-2-3，4-5，6 孤立 → 连通块数 = " << cnt << "（期望 3）" << endl;
    cout << endl;
}

// ======================== 主函数 ========================

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║   CSP-J 第41课：图论基础 - 代码演示      ║" << endl;
    cout << "╚══════════════════════════════════════════╝" << endl << endl;

    // 依次演示各个知识点
    demo_adjacency_matrix();
    demo_adjacency_list();
    demo_weighted_graph();
    demo_degree_calculation();
    demo_dfs_traversal();
    demo_bfs_traversal();
    demo_path_check();
    demo_connected_components();

    cout << "========== 演示完毕 ==========" << endl;
    cout << "\n关键要点：" << endl;
    cout << "1. n <= 1000 稠密图 → 邻接矩阵 g[i][j]" << endl;
    cout << "2. n > 5000 稀疏图 → 邻接表 vector<int> g[N]" << endl;
    cout << "3. 无向图：双向都要存储！" << endl;
    cout << "4. 有向图：入度/出度要分清" << endl;
    cout << "5. 遍历时务必使用 vis 数组标记已访问" << endl;
    cout << "编译：g++ -std=c++17 lesson41_图论基础.cpp -o lesson41" << endl;

    return 0;
}
