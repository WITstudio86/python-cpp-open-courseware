/**
 * CSP-J 备考课程 — 第43课：BFS 广度优先搜索
 *
 * 涵盖内容：
 *   1. BFS 标准模板（邻接表）
 *   2. BFS 求无权图最短路径
 *   3. 网格 BFS（迷宫最短路径）
 *   4. BFS 层序遍历
 *
 * 编译运行：g++ -std=c++11 -O2 lesson43_BFS广度优先搜索.cpp -o bfs_demo && ./bfs_demo
 */

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 100005;

// ==============================
// 示例1：BFS 标准模板（邻接表）
// ==============================
void demo_bfs_standard() {
    cout << "========== 示例1：BFS 标准模板 ==========" << endl;

    // 建图（无向图）
    // 节点：1-2-3-4，外加1-5
    int n = 5, m = 4;
    vector<int> G[6];  // 1-indexed

    // 边：(1,2), (2,3), (3,4), (1,5)
    G[1].push_back(2); G[2].push_back(1);
    G[2].push_back(3); G[3].push_back(2);
    G[3].push_back(4); G[4].push_back(3);
    G[1].push_back(5); G[5].push_back(1);

    bool vis[6] = {false};
    int dist[6];
    memset(dist, -1, sizeof(dist));

    queue<int> q;
    int start = 1;
    q.push(start);
    vis[start] = true;
    dist[start] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : G[u]) {
            if (!vis[v]) {
                vis[v] = true;
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    cout << "从节点1出发的最短距离（边数）：" << endl;
    for (int i = 1; i <= n; i++) {
        cout << "  dist[" << i << "] = " << dist[i] << endl;
    }
    cout << endl;
}

// ==============================
// 示例2：BFS 求最短路径 + 路径回溯
// ==============================
void demo_bfs_shortest_path() {
    cout << "========== 示例2：BFS 求最短路径 + 路径回溯 ==========" << endl;

    // 建图：1-2-4-5, 1-3-4
    vector<int> G[6];
    G[1].push_back(2); G[2].push_back(1);
    G[2].push_back(4); G[4].push_back(2);
    G[4].push_back(5); G[5].push_back(4);
    G[1].push_back(3); G[3].push_back(1);
    G[3].push_back(4); G[4].push_back(3);

    bool vis[6] = {false};
    int dist[6], pre[6];
    memset(dist, -1, sizeof(dist));
    memset(pre, -1, sizeof(pre));

    int start = 1, end = 5;
    queue<int> q;
    q.push(start);
    vis[start] = true;
    dist[start] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == end) break;  // 找到终点可提前退出

        for (int v : G[u]) {
            if (!vis[v]) {
                vis[v] = true;
                dist[v] = dist[u] + 1;
                pre[v] = u;
                q.push(v);
            }
        }
    }

    cout << "从" << start << "到" << end << "的最短距离：" << dist[end] << " (边数)" << endl;

    // 回溯路径
    cout << "最短路径：";
    vector<int> path;
    for (int p = end; p != -1; p = pre[p]) {
        path.push_back(p);
    }
    // 逆序输出（从起点到终点）
    for (int i = (int)path.size() - 1; i >= 0; i--) {
        cout << path[i];
        if (i > 0) cout << " -> ";
    }
    cout << endl << endl;
}

// ==============================
// 示例3：网格BFS（迷宫最短路径）
// ==============================
void demo_grid_bfs() {
    cout << "========== 示例3：网格BFS（迷宫最短路径） ==========" << endl;

    int n = 5, m = 5;
    // 迷宫：S起点, E终点, .空地, #墙壁
    char grid[5][6] = {
        "S.#..",
        ".#...",
        "..#..",
        "...#.",
        "....E"
    };

    int sx = 0, sy = 0, ex = 4, ey = 4;
    bool vis[5][5] = {false};
    int dist[5][5];
    memset(dist, -1, sizeof(dist));
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    struct Node { int x, y; };
    queue<Node> q;
    q.push({sx, sy});
    vis[sx][sy] = true;
    dist[sx][sy] = 0;

    int ans = -1;
    while (!q.empty()) {
        Node cur = q.front();
        q.pop();

        if (cur.x == ex && cur.y == ey) {
            ans = dist[cur.x][cur.y];
            break;
        }

        for (int i = 0; i < 4; i++) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m
                && grid[nx][ny] != '#' && !vis[nx][ny]) {
                vis[nx][ny] = true;
                dist[nx][ny] = dist[cur.x][cur.y] + 1;
                q.push({nx, ny});
            }
        }
    }

    cout << "迷宫：" << endl;
    for (int i = 0; i < n; i++) {
        cout << "  " << grid[i] << endl;
    }
    cout << "从S到E的最短步数：" << ans << endl;
    cout << endl;
}

// ==============================
// 示例4：BFS 层序遍历
// ==============================
void demo_bfs_level_order() {
    cout << "========== 示例4：BFS 层序遍历 ==========" << endl;

    // 建一个简单的图
    // 层0: 1
    // 层1: 2, 3
    // 层2: 4, 5, 6
    // 层3: 7
    int n = 7;
    vector<int> G[8];
    G[1].push_back(2); G[2].push_back(1);
    G[1].push_back(3); G[3].push_back(1);
    G[2].push_back(4); G[4].push_back(2);
    G[2].push_back(5); G[5].push_back(2);
    G[3].push_back(6); G[6].push_back(3);
    G[5].push_back(7); G[7].push_back(5);

    bool vis[8] = {false};
    queue<int> q;
    q.push(1);
    vis[1] = true;
    int level = 0;

    while (!q.empty()) {
        int sz = (int)q.size();
        cout << "第" << level << "层 (" << sz << "个节点): ";
        for (int i = 0; i < sz; i++) {
            int u = q.front();
            q.pop();
            cout << u << " ";
            for (int v : G[u]) {
                if (!vis[v]) {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
        cout << endl;
        level++;
    }
    cout << endl;
}

// ==============================
// 示例5：多源BFS
// ==============================
void demo_multi_source_bfs() {
    cout << "========== 示例5：多源BFS ==========" << endl;

    // 网格中有多个起点（消防站），求每个点到最近消防站的距离
    int n = 3, m = 4;
    int grid[3][4] = {
        {0, 0, 1, 0},  // 0=普通点, 1=消防站（源点）
        {0, 0, 0, 0},
        {0, 1, 0, 0}
    };

    bool vis[3][4] = {false};
    int dist[3][4];
    memset(dist, -1, sizeof(dist));
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    struct Node { int x, y; };
    queue<Node> q;

    // 将所有源点同时入队
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 1) {
                q.push({i, j});
                vis[i][j] = true;
                dist[i][j] = 0;
            }
        }
    }

    while (!q.empty()) {
        Node cur = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && !vis[nx][ny]) {
                vis[nx][ny] = true;
                dist[nx][ny] = dist[cur.x][cur.y] + 1;
                q.push({nx, ny});
            }
        }
    }

    cout << "网格（1=消防站）：" << endl;
    for (int i = 0; i < n; i++) {
        cout << "  ";
        for (int j = 0; j < m; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    cout << "每个点到最近消防站的距离：" << endl;
    for (int i = 0; i < n; i++) {
        cout << "  ";
        for (int j = 0; j < m; j++) {
            cout << dist[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// ==============================
// main
// ==============================
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "======================================" << endl;
    cout << "  CSP-J 第43课：BFS 广度优先搜索演示" << endl;
    cout << "======================================" << endl << endl;

    demo_bfs_standard();
    demo_bfs_shortest_path();
    demo_grid_bfs();
    demo_bfs_level_order();
    demo_multi_source_bfs();

    return 0;
}
