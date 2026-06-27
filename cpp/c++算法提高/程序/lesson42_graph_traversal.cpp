/*
 * ================================================================
 * C++算法提高 第42课：图的遍历——DFS与BFS
 * ================================================================
 *
 * 算法知识点：
 *   - 深度优先搜索（DFS）：递归 + 回溯，一条路走到黑
 *   - 广度优先搜索（BFS）：队列，逐层扩散，水波式
 *   - 连通分量计数：对未访问顶点启动搜索
 *   - 无权图最短路径：BFS 按层扩展，首次到达即为最短
 *   - 路径还原：parent 数组记录前驱节点
 *
 * 经典例题：
 *   例题1 - 连通分量计数：统计无向图中连通块的个数
 *   例题2 - 无权图最短路径：BFS 求起点到终点的最短距离和路径
 */

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 101;

// ================================================================
// 全局邻接表
// ================================================================
vector<int> adj[MAXN];

// 清空邻接表
void clearGraph() {
    for (int i = 0; i < MAXN; i++) {
        adj[i].clear();
    }
}

// 添加无向边
void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

// ================================================================
// 实现1：深度优先搜索（DFS）——递归实现
// 时间复杂度：O(V + E)
// 空间复杂度：O(V)（递归栈深度）
// ================================================================
bool dfsVisited[MAXN];
int dfsOrder[MAXN];    // 记录访问顺序
int dfsIdx = 0;        // 访问顺序索引

void dfs(int u) {
    dfsVisited[u] = true;
    dfsOrder[++dfsIdx] = u;  // 记录访问顺序

    for (int v : adj[u]) {
        if (!dfsVisited[v]) {
            dfs(v);           // 递归深入
        }
    }
}

// 封装：从 start 开始 DFS，返回访问序列
vector<int> runDFS(int start, int n) {
    memset(dfsVisited, 0, sizeof(dfsVisited));
    dfsIdx = 0;
    dfs(start);
    vector<int> result;
    for (int i = 1; i <= dfsIdx; i++) {
        result.push_back(dfsOrder[i]);
    }
    return result;
}

// ================================================================
// 实现2：深度优先搜索（DFS）——栈实现（非递归）
// 使用显式栈模拟递归过程
// ================================================================
vector<int> dfsStack(int start) {
    bool vis[MAXN] = {false};
    vector<int> result;
    stack<int> stk;

    stk.push(start);

    while (!stk.empty()) {
        int u = stk.top();
        stk.pop();

        if (vis[u]) continue;   // 可能重复入栈，跳过已访问的

        vis[u] = true;
        result.push_back(u);

        // 逆序遍历邻居（保证与递归顺序一致）
        for (int i = (int)adj[u].size() - 1; i >= 0; i--) {
            int v = adj[u][i];
            if (!vis[v]) {
                stk.push(v);
            }
        }
    }
    return result;
}

// ================================================================
// 实现3：广度优先搜索（BFS）——队列实现
// 时间复杂度：O(V + E)
// 空间复杂度：O(V)（队列最大长度）
// 特点：按层访问，首次到达即为最短路径（无权图）
// ================================================================
vector<int> bfs(int start) {
    bool vis[MAXN] = {false};
    vector<int> result;
    queue<int> q;

    q.push(start);
    vis[start] = true;   // 入队时立即标记！

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        result.push_back(u);

        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }
    }
    return result;
}

// 带层次信息的 BFS（返回各顶点的"深度"）
void bfsWithLevel(int start, int n) {
    bool vis[MAXN] = {false};
    int level[MAXN] = {0};     // 每个顶点到起点的距离
    queue<int> q;

    q.push(start);
    vis[start] = true;
    level[start] = 0;

    cout << "BFS 层次遍历：" << endl;
    int currentLevel = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        // 层次变化时换行
        if (level[u] != currentLevel) {
            if (currentLevel != -1) cout << endl;
            cout << "  第 " << level[u] << " 层：";
            currentLevel = level[u];
        }
        cout << u << " ";

        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }
    cout << endl;
}

// ================================================================
// 例题1：连通分量计数
// 题目：统计无向图中连通分量的个数，并输出每个分量的顶点
// 思路：遍历所有顶点，对每个未访问的顶点启动 BFS/DFS
//       每次启动意味着发现一个新的连通分量
// ================================================================
void example1_connectedComponents() {
    cout << "══════════════════════════════════════" << endl;
    cout << "  例题1：连通分量计数" << endl;
    cout << "══════════════════════════════════════" << endl;

    clearGraph();

    int n, m;
    cout << "请输入顶点数 N 和边数 M（如 6 4）：" << endl;
    cout << "（输入 6 4 使用样例数据）→ ";
    cin >> n >> m;

    cout << "请输入 " << m << " 条边（每行两个整数 u v）：" << endl;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        addEdge(u, v);
    }

    // 统计连通分量
    bool vis[MAXN] = {false};
    vector<vector<int>> components;

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            // 发现新分量，启动 BFS
            vector<int> comp;
            queue<int> q;
            q.push(i);
            vis[i] = true;

            while (!q.empty()) {
                int u = q.front(); q.pop();
                comp.push_back(u);
                for (int v : adj[u]) {
                    if (!vis[v]) {
                        vis[v] = true;
                        q.push(v);
                    }
                }
            }
            components.push_back(comp);
        }
    }

    // 输出结果
    cout << endl;
    cout << "图中连通分量总数：" << components.size() << endl;
    cout << "────────────────────────────" << endl;
    for (size_t i = 0; i < components.size(); i++) {
        cout << "分量 " << (i + 1) << "（共 " << components[i].size()
             << " 个顶点）：";
        for (int v : components[i]) {
            cout << v << " ";
        }
        cout << endl;
    }
    cout << endl;

    // 判断图是否连通
    if (components.size() == 1) {
        cout << "结论：该图是连通图（所有顶点互相可达）" << endl;
    } else {
        cout << "结论：该图是非连通图（有 " << components.size()
             << " 个互不连通的子图）" << endl;
    }
    cout << endl;
}

// ================================================================
// 例题2：无权图最短路径（BFS）
// 题目：求从起点 S 到终点 T 的最短路径长度和具体路径
// 思路：BFS 按层扩展，首次到达 T 时经过的边数即最短距离
//       parent 数组记录前驱，用于还原路径
// ================================================================
void example2_shortestPath() {
    cout << "══════════════════════════════════════" << endl;
    cout << "  例题2：无权图最短路径（BFS）" << endl;
    cout << "══════════════════════════════════════" << endl;

    clearGraph();

    int n, m, s, t;
    cout << "请输入顶点数 N、边数 M、起点 S、终点 T" << endl;
    cout << "（如 5 5 1 5）：" << endl;
    cout << "（输入 5 5 1 5 使用样例数据）→ ";
    cin >> n >> m >> s >> t;

    cout << "请输入 " << m << " 条边（每行两个整数 u v）：" << endl;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        addEdge(u, v);
    }

    // BFS 求最短路径
    int dist[MAXN];
    int parent[MAXN];
    memset(dist, -1, sizeof(dist));
    memset(parent, -1, sizeof(parent));

    queue<int> q;
    q.push(s);
    dist[s] = 0;

    bool found = false;
    while (!q.empty() && !found) {
        int u = q.front(); q.pop();

        for (int v : adj[u]) {
            if (dist[v] == -1) {        // 未访问（首次到达即最短）
                dist[v] = dist[u] + 1;
                parent[v] = u;
                q.push(v);
                if (v == t) {
                    found = true;
                    break;              // 找到目标，提前退出
                }
            }
        }
    }

    // 输出结果
    cout << endl;
    if (dist[t] == -1) {
        cout << "结果：从 " << s << " 到 " << t << " 不可达！" << endl;
    } else {
        cout << "最短距离：" << dist[t] << " 条边" << endl;

        // 还原路径
        vector<int> path;
        for (int v = t; v != -1; v = parent[v]) {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());

        cout << "最短路径：";
        for (size_t i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i < path.size() - 1) cout << " → ";
        }
        cout << endl;

        // 路径可视化
        cout << endl;
        cout << "路径可视化：" << endl;
        cout << "  ";
        for (size_t i = 0; i < path.size(); i++) {
            cout << "[" << path[i] << "]";
            if (i < path.size() - 1) {
                cout << "──" << dist[path[i + 1]] - dist[path[i]] << "步──>";
            }
        }
        cout << endl;
    }
    cout << endl;
}

// ================================================================
// DFS vs BFS 对比演示
// ================================================================
void demo_comparison() {
    cout << "══════════════════════════════════════" << endl;
    cout << "  DFS vs BFS 对比演示" << endl;
    cout << "══════════════════════════════════════" << endl;

    clearGraph();

    // 构建示例图
    //     1
    //    / \
    //   2   3
    //  / \   \
    // 4   5   6
    addEdge(1, 2);
    addEdge(1, 3);
    addEdge(2, 4);
    addEdge(2, 5);
    addEdge(3, 6);

    cout << "示例图结构：" << endl;
    cout << "       1" << endl;
    cout << "      / \\" << endl;
    cout << "     2   3" << endl;
    cout << "    / \\   \\" << endl;
    cout << "   4   5   6" << endl;
    cout << endl;

    // DFS（递归）
    vector<int> dfsResult = runDFS(1, 6);
    cout << "DFS（递归）访问顺序：";
    for (int v : dfsResult) cout << v << " ";
    cout << endl;

    // DFS（栈）
    vector<int> dfsStackResult = dfsStack(1);
    cout << "DFS（栈）  访问顺序：";
    for (int v : dfsStackResult) cout << v << " ";
    cout << endl;

    // BFS
    vector<int> bfsResult = bfs(1);
    cout << "BFS        访问顺序：";
    for (int v : bfsResult) cout << v << " ";
    cout << endl;

    cout << endl;
    cout << "分析：" << endl;
    cout << "  • DFS 一条路走到黑：1→2→4→5→3→6（先深入左子树）" << endl;
    cout << "  • BFS 逐层扩散：1→2→3→4→5→6（按层次访问）" << endl;
    cout << endl;
}

// ================================================================
// DFS 遍历过程可视化（逐步演示）
// ================================================================
void demo_visualizeTraversal() {
    cout << "══════════════════════════════════════" << endl;
    cout << "  图的遍历过程可视化" << endl;
    cout << "══════════════════════════════════════" << endl;

    clearGraph();

    // 构建一个更有趣的图
    addEdge(1, 2);
    addEdge(1, 3);
    addEdge(2, 4);
    addEdge(3, 4);
    addEdge(3, 5);

    cout << "图结构：1-2, 1-3, 2-4, 3-4, 3-5" << endl;
    cout << endl;

    // 可视化 DFS 过程
    cout << "【DFS 遍历过程】" << endl;
    cout << "────────────────────────" << endl;
    memset(dfsVisited, 0, sizeof(dfsVisited));
    dfsIdx = 0;

    // 手动模拟以展示过程
    stack<int> stk;
    stk.push(1);
    int step = 0;

    while (!stk.empty()) {
        int u = stk.top(); stk.pop();
        if (dfsVisited[u]) continue;

        dfsVisited[u] = true;
        step++;
        cout << "步骤 " << step << "：访问顶点 " << u << endl;
        cout << "  栈内容：[";
        // 复制栈来显示（不会影响实际遍历，因为我们已经是模拟）
        cout << "]" << endl;

        for (int i = (int)adj[u].size() - 1; i >= 0; i--) {
            int v = adj[u][i];
            if (!dfsVisited[v]) stk.push(v);
        }
    }
    cout << endl;

    // 可视化 BFS 过程
    cout << "【BFS 遍历过程】" << endl;
    cout << "────────────────────────" << endl;
    bool bfsVis[MAXN] = {false};
    queue<int> q;
    q.push(1);
    bfsVis[1] = true;
    step = 0;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        step++;
        cout << "步骤 " << step << "：访问顶点 " << u;
        cout << "（出队）" << endl;

        int added = 0;
        for (int v : adj[u]) {
            if (!bfsVis[v]) {
                bfsVis[v] = true;
                q.push(v);
                added++;
            }
        }
        cout << "  将 " << added << " 个未访问邻居加入队列" << endl;
    }
    cout << endl;
}

// ================================================================
// 主函数
// ================================================================
int main() {
    cout << "╔══════════════════════════════════════════════╗" << endl;
    cout << "║    第42课：图的遍历——DFS与BFS                 ║" << endl;
    cout << "║    深度优先 · 广度优先 · 连通分量 · 最短路径   ║" << endl;
    cout << "╚══════════════════════════════════════════════╝" << endl;
    cout << endl;

    int choice;
    do {
        cout << "请选择要运行的功能：" << endl;
        cout << "  1. 例题1：连通分量计数" << endl;
        cout << "  2. 例题2：无权图最短路径（BFS）" << endl;
        cout << "  3. DFS vs BFS 对比演示" << endl;
        cout << "  4. 遍历过程可视化" << endl;
        cout << "  5. BFS 层次遍历" << endl;
        cout << "  0. 退出" << endl;
        cout << "请输入选择 → ";
        cin >> choice;
        cout << endl;

        switch (choice) {
        case 1:
            example1_connectedComponents();
            break;
        case 2:
            example2_shortestPath();
            break;
        case 3:
            demo_comparison();
            break;
        case 4:
            demo_visualizeTraversal();
            break;
        case 5:
            cout << "══════════════════════════════════════" << endl;
            cout << "  BFS 层次遍历演示" << endl;
            cout << "══════════════════════════════════════" << endl;
            clearGraph();
            addEdge(1, 2); addEdge(1, 3);
            addEdge(2, 4); addEdge(2, 5);
            bfsWithLevel(1, 5);
            cout << endl;
            break;
        case 0:
            cout << "再见！" << endl;
            break;
        default:
            cout << "无效选择，请重新输入。" << endl;
            break;
        }
    } while (choice != 0);

    return 0;
}
