# 第42课：DFS深度优先搜索

## 🎯 考纲要求
- 对应CSP-J考纲中的具体知识点：深度优先搜索（DFS）的实现框架、回溯法的基本思想与应用、连通块计数、迷宫寻路问题、排列组合的DFS枚举。DFS是CSP-J复赛必考内容，几乎每年都有一道DFS相关题目。

## 📖 知识精讲

### 一、什么是DFS？

深度优先搜索（Depth First Search，简称DFS）是一种用于遍历或搜索树/图的算法。它的核心思想是：**沿着一条路径尽可能深地探索，直到无法继续才回溯到上一个分支点，尝试其他路径**。

可以形象地理解为走迷宫：你一直往前走，遇到岔路就选一条继续走，走到死胡同就退回到上一个岔路口，换另一条路。这种"一条路走到黑、不撞南墙不回头"的策略就是DFS。

### 二、DFS递归实现框架

DFS通常使用**递归**实现，代码框架非常固定，必须熟练背诵：

```cpp
bool vis[N];           // 标记数组，记录哪些顶点已被访问
vector<int> g[N];      // 邻接表存储的图

// DFS递归函数
void dfs(int u) {
    vis[u] = true;     // 标记当前顶点已访问
    // 在这里可以做一些处理，比如输出、计数等
    
    for (int v : g[u]) {       // 遍历 u 的所有邻接点
        if (!vis[v]) {         // 如果 v 未被访问
            dfs(v);            // 递归深入探索
        }
    }
}
```

**关键要素**：
1. `vis[]` 数组：**必须标记已访问的顶点**，否则在图中会陷入无限循环（A→B→A→B...）
2. 递归入口：选择一个未访问的顶点作为起点调用 `dfs(start)`
3. 递归出口：当当前顶点的所有邻接点都被访问过时，函数自然返回（回溯）

**遍历整个图**（可能有多个连通分量）：

```cpp
for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
        dfs(i);  // 每调用一次，访问一个连通块
    }
}
```

### 三、DFS与BFS的区别

| 特性 | DFS | BFS |
|------|-----|-----|
| 实现方式 | 递归（或栈） | 队列 |
| 遍历顺序 | 深度优先 | 广度（层次）优先 |
| 空间复杂度 | O(h)，h为递归深度 | O(w)，w为最大宽度 |
| 适用场景 | 连通块、回溯、排列组合 | 最短路径（无权图）、层次遍历 |
| 是否适合求最短路 | 不适合（需要枚举所有路径） | 适合（首次到达即最短） |

**注意**：DFS本身不保证找到最短路径，因为它是"深度优先"的，可能绕远路才到达目标。求无权图最短路径请用BFS。

### 四、回溯法

回溯法是DFS思想的延伸，是CSP-J考试的重难点。它的核心流程是：

```
试探 → 递归 → 恢复状态
```

具体步骤：
1. **做选择**：尝试当前这一步（比如将某个数放入排列中）
2. **递归**：基于当前选择，继续向下探索
3. **撤销选择（回溯）**：恢复状态，以便尝试其他可能性

回溯法最经典的应用是**排列问题**和**组合问题**。

#### 全排列生成

生成 1 到 n 的所有全排列：

```cpp
int n;
int path[N];       // 当前排列
bool used[N];      // 标记数字是否已被使用

void dfs(int k) {  // k 表示当前已经选了几个数
    if (k == n) {  // 选满了，输出一个排列
        for (int i = 0; i < n; i++) cout << path[i] << " ";
        cout << endl;
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            path[k] = i;       // 做选择
            used[i] = true;    // 标记已使用
            dfs(k + 1);        // 递归
            used[i] = false;   // 回溯：恢复状态
        }
    }
}
```

**时间复杂度**：O(n × n!)，因为共有 n! 个排列，每个排列输出需要 O(n)。

**回溯法的精髓**：递归调用之前的代码是"做选择"，递归调用之后的代码是"撤销选择"。初学者最容易忘记写 `used[i] = false` 这行回溯代码，导致只能找到第一个排列。

### 五、连通块计数

在无向图中，如果一个连通块内的任意两个顶点都有路径相连，而不同连通块的顶点之间没有路径，那么图的连通块就是最大的连通子图。

**问题**：给定一个无向图，求图中连通块的数量。

**思路**：对每个未访问的顶点调用一次DFS，每调用一次DFS就会访问完该顶点所在连通块的所有顶点。因此调用DFS的次数就是连通块的数量。

```cpp
int cnt = 0;          // 连通块计数器
for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
        cnt++;        // 发现一个新的连通块
        dfs(i);       // DFS访问整个连通块
    }
}
cout << cnt << endl;  // 输出连通块数
```

**扩展**：还可以在DFS过程中统计每个连通块的大小（顶点数量）：

```cpp
int dfs(int u) {
    vis[u] = true;
    int size = 1;  // 当前连通块大小，至少包含 u 自身
    for (int v : g[u]) {
        if (!vis[v]) {
            size += dfs(v);
        }
    }
    return size;
}
```

### 六、迷宫寻路问题

迷宫是DFS的经典应用场景。给定一个 N×M 的网格迷宫，`'.'` 表示可通行的空地，`'#'` 表示障碍物（墙壁），问从起点 (sx, sy) 是否能走到终点 (tx, ty)。

**DFS解法**：

```cpp
int N, M;
char maze[105][105];
bool vis[105][105];
int dx[4] = {0, 0, 1, -1};  // 四个方向的偏移量
int dy[4] = {1, -1, 0, 0};

bool dfs(int x, int y) {
    // 到达终点
    if (x == tx && y == ty) return true;
    
    vis[x][y] = true;
    
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        // 检查边界、障碍物和访问状态
        if (nx >= 1 && nx <= N && ny >= 1 && ny <= M 
            && maze[nx][ny] == '.' && !vis[nx][ny]) {
            if (dfs(nx, ny)) return true;  // 找到路径，逐层返回
        }
    }
    
    return false;  // 四个方向都走不通
}
```

**注意事项**：
- 边界检查：`nx` 和 `ny` 必须在 [1, N] 和 [1, M] 范围内
- 障碍物检查：不能走到 `'#'` 上
- vis 标记：走过的格子不能再走，否则会来回走无限循环
- DFS求迷宫通路时，如果只需要判断"能否到达"，可以在找到后立即返回 true，剪枝优化

**注意**：DFS找到的迷宫路径不一定是最短路径。如果需要最短路径，请使用BFS。

### 七、DFS的时间复杂度分析

- **图的DFS遍历**：O(n + m)，每个顶点和每条边都访问一次
- **全排列DFS**：O(n × n!)，因为有 n! 种排列
- **组合DFS（C(n, k)）**：O(C(n, k))，即组合数
- **迷宫DFS**：O(N × M)，最坏情况访问所有格子

**剪枝的重要性**：在回溯法中，通过提前判断某些分支不可能产生有效解来避免无意义的递归，称为"剪枝"。良好的剪枝可以大幅降低实际运行时间。

### 八、DFS的递归深度与栈溢出

递归深度过大可能导致**栈溢出**（Stack Overflow）。通常C++的默认栈空间约为 8MB，递归深度大约能支持到 10⁵~10⁶ 层（取决于每层局部变量大小）。

如果图的深度（最长路径）非常大（比如 n = 200000 的链状图），DFS递归可能栈溢出。此时有两种解决方案：
1. 改为用栈（stack）手动模拟DFS
2. 改用BFS（用队列实现，不存在递归深度问题）

不过CSP-J的题目规模通常不会刻意卡栈深度，用递归DFS一般是安全的。

## 💻 代码模板

### DFS递归遍历图（完整模板）

```cpp
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int N = 100005;
vector<int> g[N];
bool vis[N];
int n, m;

void dfs(int u) {
    vis[u] = true;
    cout << u << " ";  // 访问顶点 u
    
    for (int v : g[u]) {
        if (!vis[v]) {
            dfs(v);
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    // 从顶点 1 开始DFS
    dfs(1);
    
    return 0;
}
```

### 全排列生成模板

```cpp
#include <iostream>
using namespace std;

const int N = 15;
int n;
int path[N];
bool used[N];

void dfs(int k) {
    if (k == n) {
        for (int i = 0; i < n; i++) {
            cout << path[i] << " \n"[i == n - 1];
        }
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            path[k] = i;
            used[i] = true;
            dfs(k + 1);
            used[i] = false;  // 回溯
        }
    }
}

int main() {
    cin >> n;
    dfs(0);
    return 0;
}
```

### 连通块计数模板

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 100005;
vector<int> g[N];
bool vis[N];

void dfs(int u) {
    vis[u] = true;
    for (int v : g[u]) {
        if (!vis[v]) dfs(v);
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            cnt++;
            dfs(i);
        }
    }
    cout << cnt << endl;
    
    return 0;
}
```

## ⚠️ 易错点

- **易错点1：忘记标记vis数组**。DFS中最致命的错误就是在递归进入顶点后忘记 `vis[u] = true`。这会导致重复访问，在无向图中出现死循环（A→B→A→B...）。切记：进入DFS函数的第一件事就是标记当前顶点已访问。

- **易错点2：回溯法忘记恢复状态**。在排列/组合等回溯问题中，递归调用后必须撤销选择（如 `used[i] = false`）。如果忘记恢复，后续分支将无法使用那些被"占用"的元素，导致结果不全。建议将回溯代码写在递归调用的下一行，形成固定的代码结构。

- **易错点3：无向图的邻接表只存一个方向**。本课讲解的是图的DFS，但如果图本身存储时忘了双向存边（无向图），DFS遍历会遗漏大量顶点。在阅读输入和建图时务必检查图是有向还是无向。

- **易错点4：DFS求最短路径**。DFS本身不能直接求无权图的最短路径。如果需要最短路径，必须用BFS。如果题目要求用DFS求迷宫最短路径，则需要枚举所有从起点到终点的路径，记录最短的那条，时间复杂度会很高。

- **易错点5：递归边界条件写错**。在全排列生成中，`k == n` 时输出排列并 return，初学者容易写成 `k == n + 1` 或 `k > n`，导致输出错误。建议在纸上画递归树来验证边界条件。

## 📝 真题精练

### 题目1：连通块计数

**题目描述**：
给定一个包含 n 个顶点和 m 条边的无向图，顶点编号从 1 到 n。请你计算该图中有多少个连通块。

**输入格式**：
第一行包含两个整数 n 和 m（1 ≤ n ≤ 100000，0 ≤ m ≤ 200000）。
接下来 m 行，每行两个整数 u 和 v，表示一条无向边。

**输出格式**：
输出一个整数，表示连通块的数量。

**样例输入**：
```
5 3
1 2
2 3
4 5
```

**样例输出**：
```
2
```

**样例说明**：顶点 1、2、3 属于第一个连通块，顶点 4、5 属于第二个连通块，共 2 个连通块。

**AC代码**：
```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 100005;
vector<int> g[N];
bool vis[N];

void dfs(int u) {
    vis[u] = true;
    for (int v : g[u]) {
        if (!vis[v]) {
            dfs(v);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n, m;
    cin >> n >> m;
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            cnt++;
            dfs(i);
        }
    }
    
    cout << cnt << endl;
    return 0;
}
```

### 题目2：全排列输出

**题目描述**：
给定一个正整数 n（1 ≤ n ≤ 8），按照字典序输出 1 到 n 的所有全排列，每个排列占一行。

**输入格式**：
一个整数 n。

**输出格式**：
输出所有 1 到 n 的全排列，每个排列中的数字用空格隔开，按照字典序排列。

**样例输入**：
```
3
```

**样例输出**：
```
1 2 3
1 3 2
2 1 3
2 3 1
3 1 2
3 2 1
```

**AC代码**：
```cpp
#include <iostream>
using namespace std;

const int N = 15;
int n;
int path[N];
bool used[N];

void dfs(int k) {
    if (k == n) {
        for (int i = 0; i < n; i++) {
            cout << path[i] << " \n"[i == n - 1];
        }
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            path[k] = i;
            used[i] = true;
            dfs(k + 1);
            used[i] = false;  // 回溯，恢复状态
        }
    }
}

int main() {
    cin >> n;
    dfs(0);
    return 0;
}
```

---

### 题目3：迷宫能否到达

**题目描述**：  
N×M 迷宫，`.` 可走，`#` 墙。给出起点 (sx,sy) 与终点 (tx,ty)（1-index）。判断是否可达。

**输入格式**：  
第一行 N M  
接下来 N 行迷宫  
最后一行 sx sy tx ty  

**输出格式**：  
`Yes` 或 `No`

**样例输入**：
```
3 4
....
.#..
....
1 1 3 4
```

**样例输出**：
```
Yes
```

**AC 代码**：
```cpp
#include <iostream>
using namespace std;

const int MAXN = 105;
char maze[MAXN][MAXN];
bool vis[MAXN][MAXN];
int N, M, tx, ty;
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

bool dfs(int x, int y) {
    if (x == tx && y == ty) return true;
    vis[x][y] = true;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx >= 1 && nx <= N && ny >= 1 && ny <= M
            && maze[nx][ny] == '.' && !vis[nx][ny]) {
            if (dfs(nx, ny)) return true;
        }
    }
    return false;
}

int main() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++)
            cin >> maze[i][j];
    int sx, sy;
    cin >> sx >> sy >> tx >> ty;
    // 若起点终点可能是墙，先判断
    if (maze[sx][sy] == '#' || maze[tx][ty] == '#') {
        cout << "No\n";
        return 0;
    }
    cout << (dfs(sx, sy) ? "Yes" : "No") << "\n";
    return 0;
}
```

---

## 🧩 进阶精讲

### 九、组合型 DFS（与排列对比）

选 k 个数的组合（顺序无关）：

```cpp
void dfs(int start, int k) {
    if ((int)path.size() == k) { /* 输出 */ return; }
    for (int i = start; i <= n; i++) {
        path.push_back(i);
        dfs(i + 1, k);       // 下一选更大编号，保证有序
        path.pop_back();     // 回溯
    }
}
```

排列用 `used[]`；组合用 **start 下界** 防重复。

### 十、连通块进阶：染色与最大块

```cpp
int color[N], col = 0, sz[N];
void dfs(int u, int c) {
    vis[u] = true;
    color[u] = c;
    sz[c]++;
    for (int v : g[u]) if (!vis[v]) dfs(v, c);
}
// 主过程
for (int i = 1; i <= n; i++) if (!vis[i]) {
    ++col;
    dfs(i, col);
}
```

可输出：连通块个数、最大连通块大小、每个点所属块编号。

### 十一、剪枝常识

1. **可行性剪枝**：当前已不可能合法则 return（如剩余格子不够）。  
2. **最优性剪枝**：已超过已知最优答案则 return（搜索最优解时）。  
3. **顺序剪枝**：先搜约束紧的分支。  

CSP-J 排列 n≤8~10，组合注意 C(n,k) 规模。

### 十二、DFS 框架记忆口诀

```
标记 → 处理 → 枚举邻居/选择 → 合法则递归 → （回溯题）撤销标记
```

图遍历型：进入时 `vis=true`，一般**不撤销**（连通块）。  
路径/排列型：需要再走其它分支时**必须撤销**。

### 十三、迷宫四方向与八方向

四方向：上下左右。  
八方向：再加四个对角，`dx,dy` 各 8 个偏移。  
题目说“相邻”时要看是否含对角。

### 十四、与 BFS 分工（预告第43课）

| 需求 | 用 |
|------|----|
| 能否到达 / 连通块 / 全部方案 | DFS 或 BFS |
| 无权最短路 / 最少步数 | **BFS** |
| 排列组合搜索树 | DFS 回溯 |
| 拓扑序相关 | 有时 DFS |

### 十五、调试技巧

1. 小图手动画递归树。  
2. 打印进入/离开节点日志查死循环（多半是 vis）。  
3. 无向图建边是否双向。  
4. 边界 `nx,ny` 是否检查。  
5. n=1、m=0、起点=终点等边界。

---

## 💻 补充模板：统计连通块大小

```cpp
int dfsSize(int u) {
    vis[u] = true;
    int s = 1;
    for (int v : g[u])
        if (!vis[v]) s += dfsSize(v);
    return s;
}
int main() {
    // 建图后
    int maxBlock = 0, blocks = 0;
    for (int i = 1; i <= n; i++) if (!vis[i]) {
        blocks++;
        maxBlock = max(maxBlock, dfsSize(i));
    }
    cout << blocks << " " << maxBlock << endl;
}
```

---

## 🎯 本课小结

本课深入学习了DFS深度优先搜索算法，包括递归实现框架、vis标记数组的必要性、回溯法的"试探-递归-恢复"三步曲，以及多个重要应用：连通块计数（每调用一次DFS发现一个连通块）、迷宫寻路（四个方向递归探索）、排列/组合枚举（回溯法）。DFS是CSP-J复赛的必考算法，建议将代码模板背到滚瓜烂熟，同时通过大量练习形成肌肉记忆。注意：求无权图最短路径请用BFS；回溯问题务必记得恢复状态；图遍历型 vis 通常不回溯，搜索型必须回溯；图的规模较大时考虑DFS栈溢出风险。
