# 第43课：BFS 广度优先搜索

## 🎯 考纲要求
- 对应CSP-J考纲中的具体知识点：图的遍历算法（广度优先搜索/BFS）
- 掌握队列（queue）的基本操作及其在BFS中的应用
- 理解无权图中BFS求最短路径的原理
- 能够使用BFS解决迷宫最短路径、层序遍历等问题
- 区分DFS与BFS的适用场景，能根据题目要求选择合适的搜索策略

## 📖 知识精讲

### 一、什么是BFS？

广度优先搜索（Breadth-First Search，简称BFS）是一种图的遍历算法。它的核心思想是：从起点开始，按照"先近后远"的顺序逐层访问节点。类似于水波纹从中心向外扩散，先访问距离起点为1的节点，再访问距离为2的节点，以此类推。

BFS与DFS（深度优先搜索）最大的区别在于：DFS是一条路走到黑，撞了南墙再回头；BFS则是齐头并进，一层一层地向外扩展。

**生活中的类比**：想象你在朋友圈中寻找一个人。DFS的做法是：找到一个人就问"你认识他吗？不认识的话你认识谁可能认识他？"然后顺着一条线索深挖下去。BFS的做法则是：先问完你所有的直接朋友（第1层），如果没找到，再问所有朋友的朋友（第2层），逐层扩大搜索范围。显然，如果要找的那个人离你"最近"（关系最近），BFS会先于DFS找到他。

### 二、BFS的核心数据结构——队列

BFS必须借助队列（queue）来实现。为什么是队列？因为BFS需要保证"先被发现的节点先被访问"，这是典型的FIFO（先进先出）特性。

STL中的queue基本操作：
```cpp
#include <queue>
queue<int> q;
q.push(x);   // 将元素x入队
q.pop();     // 队首元素出队
q.front();   // 访问队首元素
q.empty();   // 判断队列是否为空
q.size();    // 获取队列大小
```

### 三、BFS标准框架

BFS有一个极其固定的代码框架，牢记这个框架，考试直接套用即可：

```cpp
#include <queue>
#include <cstring>

const int MAXN = 100005;
vector<int> G[MAXN];  // 邻接表存图
bool vis[MAXN];       // 访问标记数组
int dist[MAXN];       // 距离数组（可选，用于求最短路径）

void bfs(int start) {
    queue<int> q;
    q.push(start);          // 1. 起点入队
    vis[start] = true;      // 2. 标记起点已访问
    dist[start] = 0;        // 3. 起点距离为0

    while (!q.empty()) {    // 4. 当队列非空
        int u = q.front();   // 5. 取出队首元素
        q.pop();             // 6. 队首出队

        // 7. 遍历u的所有邻接点
        for (int v : G[u]) {
            if (!vis[v]) {          // 8. 如果未访问
                vis[v] = true;      // 9. 标记为已访问
                dist[v] = dist[u] + 1; // 10. 更新距离
                q.push(v);          // 11. 入队
            }
        }
    }
}
```

**框架要点总结**：
1. **初始化队列**：将起点入队，并标记为已访问。
2. **while循环**：只要队列不为空就继续处理。
3. **取队首**：使用front()获取队首元素，然后pop()移出队列。
4. **扩展邻接点**：遍历当前节点的所有邻接点，将未访问的节点入队。
5. **标记时机**：必须在入队时就标记为已访问（不是在出队时标记），否则会导致同一个节点被多次入队，严重浪费时间和空间。

**为什么标记必须在入队时？** 考虑这样一个场景：节点A同时与B和C相邻，而B和C又都连接到D。在处理A时，B和C同时入队。接着处理B时，发现D未访问，D入队。处理C时，又发现D"未访问"（因为D刚入队但可能还没被标记），D会再次入队。这就导致了重复入队。如果在入队时就标记，处理B时将D入队并标记，处理C时发现D已标记，就不会重复入队了。

### 四、BFS求最短路径

BFS最重要的性质是：**在无权图中，BFS天然求出的是起点到各点的最短路径**（经过的边数最少）。

**证明思路**：BFS按层扩展，第k层扩展到的所有节点，距离起点恰好为k。如果一个节点在第k层被首次访问，那么不存在一条更短的路径到达它（因为如果有更短路径，它应该在第k-1层或更早的层被访问）。

**代码扩展**：在标准BFS框架的基础上，我们可以记录每个节点的"前驱"节点，从而在BFS结束后回溯出最短路径：

```cpp
int pre[MAXN];  // 记录前驱节点

void bfs_with_path(int start) {
    // ... BFS标准框架 ...
    for (int v : G[u]) {
        if (!vis[v]) {
            vis[v] = true;
            dist[v] = dist[u] + 1;
            pre[v] = u;     // 记录前驱
            q.push(v);
        }
    }
}

// 回溯路径
void print_path(int start, int end) {
    if (start == end) {
        cout << start;
        return;
    }
    print_path(start, pre[end]);
    cout << " -> " << end;
}
```

### 五、网格BFS（迷宫问题）

CSP-J中非常常见的一类BFS应用是网格迷宫问题。给定一个n*m的网格，有些格子是墙（不可通过），有些是空地（可通过），求从起点到终点的最短步数。

网格BFS与图BFS的区别在于，网格的"邻接点"是上下左右四个方向（或八个方向），而不是通过邻接表获取。

```cpp
int n, m;
char grid[105][105];
bool vis[105][105];
int dist[105][105];
int dx[4] = {0, 0, 1, -1};  // 四个方向
int dy[4] = {1, -1, 0, 0};

int bfs_grid(int sx, int sy, int ex, int ey) {
    queue<pair<int, int>> q;
    q.push({sx, sy});
    vis[sx][sy] = true;
    dist[sx][sy] = 0;

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        if (x == ex && y == ey) return dist[x][y];  // 到达终点

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            // 边界检查 + 障碍物检查 + 访问检查
            if (nx >= 0 && nx < n && ny >= 0 && ny < m
                && grid[nx][ny] != '#' && !vis[nx][ny]) {
                vis[nx][ny] = true;
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
    return -1;  // 无法到达
}
```

**关键细节**：边界检查的顺序很重要。必须先用边界条件短路（`nx >= 0 && nx < n && ny >= 0 && ny < m`），再判断`grid[nx][ny] != '#'`，否则可能访问越界内存导致RE（运行时错误）。

### 六、BFS的层序遍历

层序遍历（或称层次遍历）是BFS的经典应用。在处理普通的图时，如果需要知道当前位于第几层，可以在BFS中加入层计数：

```cpp
void bfs_level_order(int start) {
    queue<int> q;
    q.push(start);
    vis[start] = true;
    int level = 0;

    while (!q.empty()) {
        int sz = q.size();  // 当前层的节点数
        cout << "第" << level << "层: ";
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
}
```

**关键技巧**：`int sz = q.size()`获取当前队列大小，这恰好是当前层的节点个数。通过在内层for循环中处理恰好sz个节点，就能实现对每一层的独立处理。这个技巧在树的层序遍历中同样适用。

### 七、DFS与BFS的选择

这是考试中的高频考点，务必理解两者的适用场景：

| 特性 | DFS | BFS |
|------|-----|-----|
| 数据结构 | 栈（递归隐式调用系统栈） | 队列（显式使用queue） |
| 空间复杂度 | O(深度)，可能很深 | O(宽度)，可能很大 |
| 最短路径 | 不能保证 | 无权图中天然最短 |
| 全部解 | 适合（可回溯） | 不方便 |
| 连通性 | 适合（标记即可） | 适合（标记即可） |
| 拓扑排序 | 适合（后序遍历） | 适合（Kahn算法） |

**选择策略**：
1. **求最短路径/最少步数** → 首选BFS（无权图场景）
2. **求所有可能的路径/方案** → 首选DFS（需要回溯枚举）
3. **判断连通性/能否到达** → DFS和BFS均可，DFS代码更简单（递归写法）
4. **图特别深**（如链状图）→ BFS更安全（DFS可能爆栈）
5. **图特别宽**（如星形图）→ DFS更安全（BFS队列可能很大）
6. **需要按层处理** → BFS（如层序遍历）

### 八、BFS的时间复杂度分析

使用邻接表存储的BFS，每个节点入队一次、出队一次，每条边被检查两次（无向图）或一次（有向图）。时间复杂度为O(V + E)，其中V是节点数，E是边数。这在CSP-J中属于非常高效的算法。

使用邻接矩阵存储时，每次寻找邻接点需要遍历所有节点，时间复杂度为O(V^2)，在V较大时（如V=10000）会严重超时。因此，BFS强烈建议使用邻接表（vector<int> G[MAXN]）存储图。

## 💻 代码模板

### 模板1：标准BFS框架（邻接表）

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN = 100005;
vector<int> G[MAXN];
bool vis[MAXN];
int dist[MAXN];

void bfs(int start) {
    queue<int> q;
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
}

int main() {
    int n, m;  // n个节点, m条边
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);  // 无向图
    }

    memset(vis, false, sizeof(vis));
    memset(dist, -1, sizeof(dist));
    bfs(1);

    // 输出每个节点到1的距离
    for (int i = 1; i <= n; i++) {
        cout << "dist[" << i << "] = " << dist[i] << endl;
    }
    return 0;
}
```

### 模板2：网格BFS（迷宫最短路径）

```cpp
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int n, m;
char grid[105][105];
bool vis[105][105];
int dist[105][105];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

struct Node { int x, y; };

int bfs_grid(int sx, int sy, int ex, int ey) {
    queue<Node> q;
    q.push({sx, sy});
    vis[sx][sy] = true;
    dist[sx][sy] = 0;

    while (!q.empty()) {
        Node cur = q.front();
        q.pop();

        if (cur.x == ex && cur.y == ey)
            return dist[cur.x][cur.y];

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
    return -1;
}
```

### 模板3：BFS层序遍历框架

```cpp
void bfs_levels(int start) {
    queue<int> q;
    q.push(start);
    vis[start] = true;
    int level = 0;

    while (!q.empty()) {
        int sz = q.size();
        // 处理当前层的sz个节点
        for (int i = 0; i < sz; i++) {
            int u = q.front();
            q.pop();
            // 对u进行处理...

            for (int v : G[u]) {
                if (!vis[v]) {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
        level++;
    }
}
```

## ⚠️ 易错点

- **错误1：入队时忘记标记vis数组**。这是BFS中最常见、最致命的错误。如果不在入队时标记vis，而是在出队时标记，会导致同一个节点被重复入队多次。在极端情况下（如完全图），节点数量会指数级膨胀，导致MLE（内存超限）或TLE（时间超限）。**解决方法**：养成习惯，在q.push(v)之前务必写vis[v]=true。

- **错误2：网格BFS中边界检查顺序错误**。写`if (grid[nx][ny] != '#' && nx >= 0 && nx < n && ny >= 0 && ny < m)`会导致先访问grid[nx][ny]再检查边界，当nx或ny越界时程序崩溃（RE）。**解决方法**：始终先检查边界范围，再检查网格内容。使用短路求值特性：`if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] != '#')`。

- **错误3：多组测试数据时忘记重置vis数组和dist数组**。CSP-J题目往往有多组测试数据，每次BFS前必须用memset或fill重置vis和dist。常见错误是只写了memset，但数组大小与MAXN不一致，导致部分数据残留。**解决方法**：使用`memset(vis, 0, sizeof(vis))`或`fill(vis, vis + n + 1, false)`，确保重置范围正确覆盖所有使用的下标。

- **错误4：混淆了DFS和BFS的适用场景**。用BFS去求所有路径方案（需要回溯），或用DFS去求最短路径（不能保证最优）。**解决方法**：记住口诀——"最短看BFS，全部看DFS，连通看哪个都行"。

- **错误5：忘记考虑图不连通的情况**。BFS从某个起点出发只能访问其所在连通分量中的节点。如果图不连通，需要在外层循环遍历所有节点，对每个未访问的节点启动BFS。

- **错误6：使用邻接矩阵而非邻接表存储稀疏图**。在节点数较大（n >= 10000）时，邻接矩阵O(V^2)的BFS会严重超时。**解决方法**：默认使用vector<int> G[MAXN]邻接表。

## 📝 真题精练

### 题目1：社交距离

**题目描述**：在一个社交网络中，有n个用户（编号1到n）和m对好友关系。定义两个用户之间的"社交距离"为他们之间最短路径经过的好友关系数。请计算从用户1出发，到其他所有用户的最短社交距离。如果某个用户不可达，输出-1。

**输入格式**：
第一行两个整数n, m（1 <= n <= 100000, 0 <= m <= 200000）。
接下来m行，每行两个整数u, v，表示u和v是好友关系。

**输出格式**：
输出n行，第i行输出用户1到用户i的最短社交距离。如果不可达输出-1。

**样例输入**：
```
5 4
1 2
2 3
3 4
1 5
```

**样例输出**：
```
0
1
2
3
1
```

**AC代码**：

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN = 100005;
vector<int> G[MAXN];
int dist[MAXN];

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    memset(dist, -1, sizeof(dist));
    queue<int> q;
    q.push(1);
    dist[1] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : G[u]) {
            if (dist[v] == -1) {  // dist[v] == -1 表示未访问
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << dist[i] << endl;
    }
    return 0;
}
```

**解析**：这是BFS求最短路径的模板题。使用dist数组同时承担"距离记录"和"访问标记"两个功能（初始化为-1，-1表示未访问）。注意无向图需要双向建边。

### 题目2：迷宫逃脱

**题目描述**：给定一个n行m列的迷宫，用字符矩阵表示。其中'.'表示空地，'#'表示墙壁，'S'表示起点，'E'表示终点。每次可以向上、下、左、右移动一格，不能穿过墙壁。请问从起点到终点的最短步数是多少？如果无法到达，输出"Impossible"。

**输入格式**：
第一行两个整数n, m（1 <= n, m <= 100）。
接下来n行，每行一个长度为m的字符串，表示迷宫。

**输出格式**：
输出一个整数表示最短步数，或输出"Impossible"。

**样例输入**：
```
5 5
S.#..
.#...
..#..
...#.
....E
```

**样例输出**：
```
8
```

**AC代码**：

```cpp
#include <iostream>
#include <queue>
using namespace std;

const int MAXN = 105;
char grid[MAXN][MAXN];
bool vis[MAXN][MAXN];
int dist[MAXN][MAXN];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

struct Node { int x, y; };

int main() {
    int n, m;
    cin >> n >> m;
    int sx, sy, ex, ey;

    for (int i = 0; i < n; i++) {
        cin >> grid[i];
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'S') {
                sx = i; sy = j;
            }
            if (grid[i][j] == 'E') {
                ex = i; ey = j;
            }
        }
    }

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

    if (ans == -1)
        cout << "Impossible" << endl;
    else
        cout << ans << endl;

    return 0;
}
```

**解析**：经典的网格BFS问题。关键在于正确设置四个移动方向、边界检查短路求值、以及到达终点后使用break跳出循环。注意getline和cin混用可能导致行末问题，这里使用cin读取字符串是安全的。

## 🎯 本课小结

1. **BFS核心思想**：逐层扩展，先近后远，使用队列实现FIFO特性。
2. **标准框架**：初始化队列 → while(!q.empty()) → front()+pop() → 遍历邻接点 → 未访问则标记并入队。这个框架必须熟记。
3. **最短路径**：无权图中BFS天然求最短路径（最少步数），这是BFS最重要的性质，考试中大量题目利用此性质。
4. **标记时机**：必须在入队时标记vis，不是在出队时。这条规则要刻在脑子里。
5. **网格BFS**：网格迷宫问题中，邻接点是四个方向，边界检查必须在内容检查之前（短路求值）。
6. **DFS vs BFS选择**：最短路径选BFS，求所有方案选DFS，判断连通性两者皆可。
7. **时间复杂度**：O(V + E)（邻接表），O(V^2)（邻接矩阵），优先使用邻接表。
