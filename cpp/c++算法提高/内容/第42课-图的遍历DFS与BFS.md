# 第42课：图的遍历——DFS与BFS

## 🎯 学习目标
- 理解图遍历的意义：系统地访问图中所有顶点
- 掌握深度优先搜索（DFS）：递归与栈实现
- 掌握广度优先搜索（BFS）：队列实现
- 理解 DFS 与 BFS 的区别、应用场景与时间/空间复杂度
- 能够用 DFS/BFS 解决连通分量、最短路径等基础图论问题

## 📖 算法讲解

### 一、什么是图的遍历？

图的遍历（Graph Traversal）是指**从图中的某个顶点出发，按照一定的规则，访问图中所有顶点各一次**的过程。

想象你在逛一个大型博物馆：
- **DFS（深度优先）**：选定一个展厅，一直往深处走，走到尽头再回头——就像走迷宫时"一条路走到黑"
- **BFS（广度优先）**：先逛完当前展厅的所有相邻展厅，再逐层向外扩展——就像水波纹一圈圈扩散

```
        图的遍历对比（从顶点1出发）
        
           图结构:              DFS访问顺序:          BFS访问顺序:
           
             1                    1 → 2 → 4 → 3        1 → 2 → 3 → 4
            / \                   (一直深入)
           2   3
            \
             4
```

### 二、深度优先搜索（DFS）

#### 2.1 核心思想

DFS 的核心思想可以概括为**递归 + 回溯**：

1. 从起点出发，标记为已访问
2. 选择一个未访问的邻居，递归地深入探索
3. 当没有未访问的邻居时，回溯到上一个顶点
4. 重复直到所有可达顶点都被访问

```
    DFS 的执行过程（动画式分解）
    
    状态:              访问路径栈:          visited 数组:
    
    ① 从 1 出发        [1]                [1:√, 2:✗, 3:✗, 4:✗]
    ② 1→2 (深入)      [1, 2]             [1:√, 2:√, 3:✗, 4:✗]
    ③ 2→4 (深入)      [1, 2, 4]          [1:√, 2:√, 3:✗, 4:√]
    ④ 4 无路(回溯)    [1, 2]             同上
    ⑤ 2 无其他邻居    [1]                同上
    ⑥ 1→3 (深入)      [1, 3]             [1:√, 2:√, 3:√, 4:√]
    ⑦ 3 无路, 1 探索完毕 → 结束
```

#### 2.2 递归实现

```cpp
bool visited[MAXN];           // 访问标记数组
vector<int> adj[MAXN];        // 邻接表

void dfs(int u) {
    visited[u] = true;        // 标记当前顶点已访问
    cout << u << " ";         // 访问（输出）当前顶点

    for (int v : adj[u]) {    // 遍历 u 的所有邻居
        if (!visited[v]) {    // 如果邻居 v 未被访问
            dfs(v);           // 递归访问 v
        }
    }
}
```

#### 2.3 栈实现（非递归）

```cpp
#include <stack>

void dfs_stack(int start, int n) {
    bool visited[MAXN] = {false};
    stack<int> stk;

    stk.push(start);

    while (!stk.empty()) {
        int u = stk.top();
        stk.pop();

        if (visited[u]) continue;
        visited[u] = true;
        cout << u << " ";

        // 注意：为了与递归顺序一致，邻居需逆序入栈
        for (int i = adj[u].size() - 1; i >= 0; i--) {
            int v = adj[u][i];
            if (!visited[v]) {
                stk.push(v);
            }
        }
    }
}
```

### 三、广度优先搜索（BFS）

#### 3.1 核心思想

BFS 使用**队列**，按照"距离起点的层数"逐层访问——先访问距离为 1 的顶点，再访问距离为 2 的顶点，以此类推。

```
    BFS 的执行过程（动画式分解）
    
    状态:              队列:               层次:
    
    ① 1 入队           [1]                层0: {1}
    ② 1 出队, 2&3 入队  [2, 3]             层1: {2, 3}
    ③ 2 出队, 4 入队    [3, 4]             层2: {4}
    ④ 3 出队, 4 已在    [4]                 
    ⑤ 4 出队, 队列空     []                 → 结束
    
    BFS 访问顺序：1 → 2 → 3 → 4
```

#### 3.2 队列实现

```cpp
#include <queue>

bool visited[MAXN];

void bfs(int start) {
    queue<int> q;

    q.push(start);
    visited[start] = true;   // 入队时标记（避免重复入队）

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << u << " ";    // 出队时访问

        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}
```

### 四、DFS vs BFS 全面对比

```
    ┌───────────────┬─────────────────────┬─────────────────────┐
    │     特性      │        DFS          │        BFS          │
    ├───────────────┼─────────────────────┼─────────────────────┤
    │  数据结构     │  栈（递归/显式栈）   │  队列               │
    │  遍历策略     │  深度优先，一条路    │  广度优先，逐层     │
    │              │  走到黑              │  扩散               │
    │  时间复杂度   │  O(V + E)           │  O(V + E)           │
    │  空间复杂度   │  O(V)（递归栈深度）  │  O(V)（队列大小）   │
    │  找到的路径   │  不一定是最短        │  无权图最短路径      │
    │  递归实现     │  简洁自然            │  不常用（可用队列）  │
    │  连通性检测   │  ✔️                  │  ✔️                  │
    │  拓扑排序     │  ✔️（后序）           │  ✔️（Kahn算法）      │
    │  迷宫问题     │  ✔️（找一条通路）     │  ✔️（最短通路）      │
    │  判环         │  ✔️（三色标记）       │  ✔️（拓扑判环）      │
    └───────────────┴─────────────────────┴─────────────────────┘
```

### 五、经典应用场景

| 问题类型 | 推荐算法 | 原因 |
|----------|----------|------|
| 连通分量计数 | DFS/BFS | 每发现一个未访问顶点就开启新搜索 |
| 无权图最短路径 | BFS | 按层扩展，首次到达即为最短 |
| 迷宫所有通路 | DFS+回溯 | 需要探索所有可能性并回溯 |
| 拓扑排序 | DFS后序 | 天然符合拓扑序 |
| 二分图判定 | BFS/DFS染色 | 相邻顶点染不同色 |
| 找环 | DFS三色标记 | 能区分"正在访问"和"已完成" |

## 💻 代码实现

### 完整框架：DFS + BFS 模板

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <cstring>
using namespace std;

const int MAXN = 101;

// ============ 基础 DFS（递归） ============
bool visited[MAXN];
vector<int> adj[MAXN];

void dfs(int u) {
    visited[u] = true;
    cout << u << " ";
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v);
        }
    }
}

// ============ DFS（栈，非递归） ============
void dfsStack(int start) {
    bool vis[MAXN] = {false};
    stack<int> stk;
    stk.push(start);

    while (!stk.empty()) {
        int u = stk.top(); stk.pop();
        if (vis[u]) continue;
        vis[u] = true;
        cout << u << " ";
        for (int i = adj[u].size() - 1; i >= 0; i--) {
            if (!vis[adj[u][i]]) stk.push(adj[u][i]);
        }
    }
}

// ============ BFS（队列） ============
void bfs(int start) {
    bool vis[MAXN] = {false};
    queue<int> q;
    q.push(start);
    vis[start] = true;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        cout << u << " ";
        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }
    }
}

// ============ 计算连通分量数 ============
int countComponents(int n) {
    bool vis[MAXN] = {false};
    int components = 0;

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            components++;
            // BFS 标记该连通分量所有顶点
            queue<int> q;
            q.push(i);
            vis[i] = true;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int v : adj[u]) {
                    if (!vis[v]) {
                        vis[v] = true;
                        q.push(v);
                    }
                }
            }
        }
    }
    return components;
}
```

## 📊 复杂度分析

| 项目 | DFS | BFS |
|------|-----|-----|
| 时间复杂度 | O(V + E) | O(V + E) |
| 空间复杂度（递归） | O(V)（最坏退化为链） | O(V)（队列） |
| 空间复杂度（非递归） | O(V)（显式栈） | O(V)（队列） |
| 完整性（有解必找到） | 是（在有限图中） | 是（在有限图中） |
| 最优性（找到最短路径） | 不保证 | 保证（无权图） |

- V 为顶点数，E 为边数
- DFS 递归深度可能达到 V（如一条链），需注意栈溢出
- BFS 队列最大长度不超过 V

## 🏋️ 经典例题

### 例题1：连通分量计数

**题目描述**：  
给定一个无向图，判断图中有多少个连通分量（互相可达的顶点组成一个连通分量）。

**输入样例**：
```
6 4
1 2
2 3
4 5
5 6
```

**输出样例**：
```
连通分量数：2
分量1：1 2 3
分量2：4 5 6
```

**解答代码**：

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 101;
vector<int> adj[MAXN];
bool visited[MAXN];

void bfsComponent(int start, vector<int>& comp) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        comp.push_back(u);
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int compCount = 0;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            compCount++;
            vector<int> comp;
            bfsComponent(i, comp);
            cout << "分量" << compCount << "：";
            for (int v : comp) cout << v << " ";
            cout << endl;
        }
    }
    cout << "连通分量数：" << compCount << endl;
    return 0;
}
```

### 例题2：无权图最短路径（BFS）

**题目描述**：  
给定一个无权无向图以及起点 S 和终点 T，求从 S 到 T 的最短路径长度（经过的最少边数）。若不可达，输出 -1。

**输入样例**：
```
5 5
1 2
1 3
2 4
3 5
4 5
1 5
```
（前 5 行是 5 条边，最后一行是 S=1, T=5）

**输出样例**：
```
最短距离：2
路径：1 → 3 → 5
```

**解答代码**：

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN = 101;
vector<int> adj[MAXN];
int dist[MAXN];      // dist[i] = 起点到 i 的最短距离
int parent[MAXN];    // parent[i] 记录 BFS 树中 i 的父节点

int bfsShortestPath(int start, int target, int n) {
    memset(dist, -1, sizeof(dist));
    memset(parent, -1, sizeof(parent));

    queue<int> q;
    q.push(start);
    dist[start] = 0;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == target) return dist[u];  // 找到目标

        for (int v : adj[u]) {
            if (dist[v] == -1) {           // 未访问
                dist[v] = dist[u] + 1;
                parent[v] = u;
                q.push(v);
            }
        }
    }
    return -1;  // 不可达
}

// 回溯输出路径
void printPath(int start, int target) {
    if (parent[target] == -1) {
        cout << "不可达";
        return;
    }
    vector<int> path;
    for (int v = target; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    // 逆序输出
    for (int i = path.size() - 1; i >= 0; i--) {
        cout << path[i];
        if (i > 0) cout << " → ";
    }
}

int main() {
    int n, m, s, t;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cin >> s >> t;

    int ans = bfsShortestPath(s, t, n);
    if (ans == -1) {
        cout << "从 " << s << " 到 " << t << " 不可达" << endl;
    } else {
        cout << "最短距离：" << ans << endl;
        cout << "路径：";
        printPath(s, t);
        cout << endl;
    }
    return 0;
}
```

## 🏋️ 课后练习

### 基础题

#### 练习1：连通分量计数

**题目描述**：给定一个 N 个顶点 M 条边的无向图，求图中有多少个连通分量，并输出每个连通分量中的顶点（按编号升序排列）。

**输入格式**：
```
第一行：两个整数 N M（1 ≤ N ≤ 1000）
接下来 M 行：每行两个整数 u v，表示一条无向边
```

**输出格式**：
```
第一行：连通分量个数 K
接下来 K 行：每行输出一个连通分量中的所有顶点（升序，空格分隔）
```

**样例输入**：
```
6 4
1 2
2 3
4 5
5 6
```

**样例输出**：
```
2
1 2 3
4 5 6
```

---

#### 练习2：无权图最短路径（BFS）

**题目描述**：给定一个无权无向图及起点 S，求 S 到每个顶点的最短距离（经过的最少边数）。若不可达则输出 -1。

**输入格式**：
```
第一行：三个整数 N M S（1 ≤ N ≤ 1000，1 ≤ S ≤ N）
接下来 M 行：每行两个整数 u v，表示一条无向边
```

**输出格式**：
```
一行 N 个整数，表示从 S 到顶点 1..N 的最短距离（不可达输出 -1）
```

**样例输入**：
```
5 4 1
1 2
1 3
2 4
3 5
```

**样例输出**：
```
0 1 1 2 2
```

---

### 提高题

#### 练习3：二分图判定

**题目描述**：给定一个无向图，判断它是否为二分图。二分图是可以将顶点分为两个不相交的集合 U 和 V，使得每条边都连接 U 和 V 中各一个顶点的图。试用 BFS 或 DFS 染色法判定。

**输入格式**：
```
第一行：两个整数 N M（1 ≤ N ≤ 1000）
接下来 M 行：每行两个整数 u v
```

**输出格式**：
```
是二分图输出 "Yes"，否则输出 "No"
```

**样例输入**：
```
4 4
1 2
2 3
3 4
4 1
```

**样例输出**：
```
Yes
```

**样例解释**：顶点1和3染一种颜色，2和4染另一种颜色，所有边都连接不同颜色的顶点。

---

### 挑战题

#### 练习4：网格中的岛屿数量

**题目描述**：给定一个 N×M 的二维网格，每个格子为 '1'（陆地）或 '0'（水）。陆地之间上下左右相连（四连通）。求网格中岛屿的数量（被水包围的连通的陆地算一个岛屿）。用 DFS 或 BFS 遍历网格解决。

**输入格式**：
```
第一行：两个整数 N M（1 ≤ N, M ≤ 100）
接下来 N 行：每行 M 个字符（'0' 或 '1'，无空格）
```

**输出格式**：
```
一个整数，表示岛屿数量
```

**样例输入**：
```
4 5
11000
11000
00100
00011
```

**样例输出**：
```
3
```

**样例解释**：左上角 2 个 1 组成一个岛屿，中间的 1 是第二个岛屿，右下角的 2 个 1 是第三个岛屿。

---

### 练习题参考答案

#### 练习1参考代码

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 1005;
vector<int> adj[MAXN];
bool vis[MAXN];

int main() {
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<vector<int>> components;
    for (int i = 1; i <= N; i++) {
        if (!vis[i]) {
            vector<int> comp;
            queue<int> q;
            q.push(i);
            vis[i] = true;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                comp.push_back(u);
                for (int v : adj[u])
                    if (!vis[v]) {
                        vis[v] = true;
                        q.push(v);
                    }
            }
            sort(comp.begin(), comp.end());
            components.push_back(comp);
        }
    }

    cout << components.size() << endl;
    for (auto& comp : components) {
        for (int i = 0; i < (int)comp.size(); i++)
            cout << (i ? " " : "") << comp[i];
        cout << endl;
    }
    return 0;
}
```

#### 练习2参考代码

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN = 1005;
vector<int> adj[MAXN];
int dist[MAXN];

int main() {
    int N, M, S;
    cin >> N >> M >> S;
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    memset(dist, -1, sizeof(dist));
    queue<int> q;
    q.push(S);
    dist[S] = 0;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    for (int i = 1; i <= N; i++)
        cout << dist[i] << (i == N ? '\n' : ' ');
    return 0;
}
```

#### 练习3参考代码

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 1005;
vector<int> adj[MAXN];
int color[MAXN];  // 0=未染色, 1=红色, -1=蓝色

bool bfs(int start) {
    queue<int> q;
    q.push(start);
    color[start] = 1;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (color[v] == 0) {
                color[v] = -color[u];
                q.push(v);
            } else if (color[v] == color[u]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 1; i <= N; i++) {
        if (color[i] == 0) {
            if (!bfs(i)) {
                cout << "No" << endl;
                return 0;
            }
        }
    }
    cout << "Yes" << endl;
    return 0;
}
```

#### 练习4参考代码

```cpp
#include <iostream>
#include <string>
using namespace std;

int N, M;
string grid[105];
bool vis[105][105];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

void dfs(int x, int y) {
    vis[x][y] = true;
    for (int d = 0; d < 4; d++) {
        int nx = x + dx[d], ny = y + dy[d];
        if (nx >= 0 && nx < N && ny >= 0 && ny < M)
            if (grid[nx][ny] == '1' && !vis[nx][ny])
                dfs(nx, ny);
    }
}

int main() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) cin >> grid[i];

    int ans = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (grid[i][j] == '1' && !vis[i][j]) {
                ans++;
                dfs(i, j);
            }

    cout << ans << endl;
    return 0;
}
```

---

## 📝 本课小结

- **DFS（深度优先搜索）**：递归实现，沿一个方向深入探索，适合连通性检测、拓扑排序、回溯问题
- **BFS（广度优先搜索）**：队列实现，逐层展开，适合最短路径（无权图）、层次遍历
- 两者时间复杂度均为 **O(V + E)**，空间复杂度均为 **O(V)**
- **关键区别**：DFS 用栈（递归），找到的不一定是最短路径；BFS 用队列，首次访问即为最短路径
- **连通分量问题**：对每个未访问顶点启动一次 DFS/BFS，启动次数即为连通分量数

掌握了图的遍历，就打开了图论算法的大门。下一课将学习**图的经典算法——最小生成树与最短路径**。
