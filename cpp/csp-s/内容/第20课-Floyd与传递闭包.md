# 第20课：Floyd 与传递闭包

## 🎯 考纲要求

- **多源最短路径**：Floyd-Warshall 算法，时间复杂度 O(V³)
- **动态规划视角**推导 Floyd 的状态定义与转移方程
- **传递闭包**（Warshall 算法）及其 bitset 优化
- **最小环问题**：无向图最小环、有向图最小环的检测与计算
- Floyd 的**路径还原**

## 📖 知识精讲

### 一、Floyd-Warshall 算法

#### 1. 核心思想

Floyd 算法解决**全源最短路**（All-Pairs Shortest Path）问题：对于图中任意两点 u, v，求出从 u 到 v 的最短距离。

算法基于动态规划，通过逐步引入中间节点来优化路径。

#### 2. 动态规划推导

**状态定义**：

设 `dp[k][i][j]` 表示从节点 i 到节点 j，且仅经过编号为 1~k 的中间节点时的最短距离。

**状态转移**：

```
dp[k][i][j] = min(dp[k-1][i][j], dp[k-1][i][k] + dp[k-1][k][j])
```

含义：i 到 j 的最短路径，要么不经过 k，要么经过 k。

- 不经过 k：`dp[k-1][i][j]`
- 经过 k：`dp[k-1][i][k] + dp[k-1][k][j]`（两段最短路径相加）

**滚动数组优化**：

观察到 `dp[k][...]` 只依赖于 `dp[k-1][...]`，且 `dp[k][i][k] = dp[k-1][i][k]`（终点就是 k 的路径不会再用 k 作为中间点），因此可以省去第一维，直接在同一个二维数组上更新：

```cpp
for (int k = 1; k <= n; k++)
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
```

#### 3. 为什么 k 循环必须在最外层

这是 Floyd 最常见的错误！从 DP 定义看，`dp[k][i][j]` 依赖的是 `dp[k-1][i][k]` 和 `dp[k-1][k][j]`，即**用同一个 k-1 阶段的中间结果来更新**。

如果把 k 放在内层，更新 `dist[i][j]` 时可能已经使用了经过 k 的信息来更新 `dist[i][k]` 或 `dist[k][j]`，导致使用了本阶段（k）而非上一阶段（k-1）的结果，破坏了 DP 的正确性。

#### 4. 复杂度分析

- 时间复杂度：**O(V³)**，三重循环，常数很小
- 空间复杂度：**O(V²)**（邻接矩阵存储）

---

### 二、传递闭包（Warshall 算法）

#### 1. 定义

传递闭包问题：在有向图中，判断任意两点之间是否存在路径（即 i 是否能到达 j）。

#### 2. 算法

和 Floyd 同构，将 `min` 替换为逻辑或（`|`），加法替换为逻辑与（`&`）：

```cpp
for (int k = 1; k <= n; k++)
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            reach[i][j] |= (reach[i][k] & reach[k][j]);
```

#### 3. bitset 优化

用 `bitset<N>` 存储行向量，内层 j 循环替换为 bitset 的按位操作，复杂度降为 O(V³ / 64)：

```cpp
bitset<MAXN> reach[MAXN];
for (int k = 1; k <= n; k++)
    for (int i = 1; i <= n; i++)
        if (reach[i][k])
            reach[i] |= reach[k];
```

此优化在实际竞赛中效果显著，V=2000 时也能较快运行。

---

### 三、最小环问题

#### 1. 无向图最小环

在 Floyd 的 k 循环中，**在更新 dist 之前**，利用「已确定的只经过 1..k-1 的最短路」来计算经过 k 的环：

```cpp
int min_cycle = INF;
for (int k = 1; k <= n; k++) {
    // 先找最小环：i → k → j → ... → i
    for (int i = 1; i < k; i++)
        for (int j = i + 1; j < k; j++)
            min_cycle = min(min_cycle, dist[i][j] + g[i][k] + g[k][j]);
    // 再更新 Floyd
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}
```

这里 `g` 是原始边权，`dist` 是经过 1..k-1 的最短路。环的权值 = `dist[i][j] + g[i][k] + g[k][j]`，其中 i, j 取 k 之前的节点。

#### 2. 有向图最小环

在有向图中更简单：环至少包含两个节点。跑完 Floyd 后，对于每个节点 i，检查 `dist[i][i]` 的最小值（若初始化为 INF），但注意需要从邻接边初始化 `dist`：

- 初始 `dist[i][i] = 0`，`dist[i][j] = g[i][j]`（直接边权）
- Floyd 结束后，`min(dist[i][i])` 即为最小环权值和（注意排除 0）

更严谨的做法：跑 Floyd 时维护经过 k 的有向环 `dist[i][k] + g[k][i]`（k 作为"最后一条边"回到出发点）。

---

### 四、路径还原

在 `dist[i][j]` 被 `dist[i][k] + dist[k][j]` 更新时，记录 `nxt[i][j] = nxt[i][k]`（表示从 i 到 j 的最短路中，i 的下一个节点是谁）。

初始时：若 i 和 j 有直接边，`nxt[i][j] = j`；否则 `nxt[i][j] = -1`。

递归输出路径：

```cpp
void print_path(int i, int j) {
    if (nxt[i][j] == -1) { cout << "无路径"; return; }
    int cur = i;
    while (cur != j) {
        cout << cur << " -> ";
        cur = nxt[cur][j];
    }
    cout << j;
}
```

---

## 💻 代码模板

### 1. 标准 Floyd（滚动数组优化）

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 505;
const long long INF = 1e18;

long long dist[MAXN][MAXN];
int nxt[MAXN][MAXN];  // 路径还原
int n, m;

void floyd() {
    // k 必须在最外层！
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            if (dist[i][k] == INF) continue;  // 剪枝优化
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    nxt[i][j] = nxt[i][k];    // 更新路径
                }
            }
        }
    }
}
```

### 2. 传递闭包（bitset 优化）

```cpp
#include <bitset>
bitset<MAXN> reach[MAXN];

void transitive_closure() {
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            if (reach[i][k])
                reach[i] |= reach[k];
}
```

### 3. 无向图最小环

```cpp
long long find_min_cycle_undirected() {
    long long ans = INF;
    for (int k = 1; k <= n; k++) {
        // 先利用 1..k-1 的最短路找经过 k 的环
        for (int i = 1; i < k; i++)
            for (int j = i + 1; j < k; j++)
                if (g[i][k] != INF && g[k][j] != INF)
                    ans = min(ans, dist[i][j] + g[i][k] + g[k][j]);
        // 再更新 Floyd
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
    }
    return ans;
}
```

---

## ⚠️ 易错点与优化技巧

### 常见错误

1. **k 循环不在最外层**：破坏 DP 的正确性，短样例可能对、长样例错

2. **INF 初始化防溢出**：
   - 若 `dist[i][k] != INF` 但 `dist[k][j] == INF`，相加会溢出（正 INF 相加 → 负数）
   - 正确写法：使用 `if (dist[i][k] != INF && dist[k][j] != INF)` 或是 `min(dist[i][j], dist[i][k] + dist[k][j])`（当 INF 足够大且不溢出时后者可用）
   - 推荐 INF 设为 `0x3f3f3f3f`（int）或 `1e18`（long long），配合 `memset(dist, 0x3f, sizeof(dist))`

3. **`dist[i][i]` 的初始值**：必须初始化为 0（自己到自己的距离），否则 Floyd 无法正确传递

4. **传递闭包的读入**：注意重边、自环的影响。自环通常在传递闭包中无意义（自己总能到达自己，`reach[i][i] = true`）

### 优化技巧

1. **bitset 优化传递闭包**：V=2000 时，朴素 O(V³) 需要 ~8×10⁹ 操作，bitset 优化至 ~1.25×10⁸，在 1s 时限内勉强可行

2. **剪枝优化**：Floyd 中若 `dist[i][k] == INF`，跳过内层 j 循环（`continue`），稠密图几乎没有收益，稀疏图中可能有用

3. **Floyd 处理负环**：跑完 Floyd 后，若存在 `dist[i][i] < 0`，说明 i 在一个负环上

4. **何时用 Floyd**：V ≤ 500 是多源最短路的阈值，超过此范围考虑跑 V 次 Dijkstra（O(V·(V+E)logV)）

---

## 📝 真题精练

### 题目1：B3611 【模板】传递闭包

**题意**：给定 n 个点的有向图邻接矩阵，输出传递闭包矩阵。n ≤ 100。

**思路**：直接跑 Warshall 算法，三重循环 O(n³)，n=100 完全可行。

**AC 代码**：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 105;

int reach[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> reach[i][j];

    // Warshall 算法
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                reach[i][j] |= (reach[i][k] & reach[k][j]);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            cout << reach[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}
```

**复杂度分析**：O(n³)，n=100 时约 10⁶ 次操作，非常轻松。

---

### 题目2：P6175 【模板】无向图最小环 / P1119 灾后重建

**题意（P6175）**：给定 n 个点 m 条边的无向图，求最小环的边权和。n ≤ 100, m ≤ 5000。

**思路**：使用 Floyd 求无向图最小环。在每一轮 k 作为环上**最大编号节点**时，枚举 i, j < k 作为环上另两个节点，环的权值为 `dist[i][j] + g[i][k] + g[k][j]`。

**AC 代码**：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const long long INF = 1e18;

long long dist[MAXN][MAXN];  // 经过 1..k-1 的最短路
long long g[MAXN][MAXN];     // 原始邻接边权
int n, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    // 初始化
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dist[i][j] = g[i][j] = INF;
        }
        dist[i][i] = 0;
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        if (w < g[u][v]) {  // 去重边
            g[u][v] = g[v][u] = w;
            dist[u][v] = dist[v][u] = w;
        }
    }

    long long ans = INF;

    for (int k = 1; k <= n; k++) {
        // 先找最小环：以 k 为最大编号节点
        for (int i = 1; i < k; i++) {
            for (int j = i + 1; j < k; j++) {
                if (dist[i][j] != INF && g[i][k] != INF && g[k][j] != INF) {
                    ans = min(ans, dist[i][j] + g[i][k] + g[k][j]);
                }
            }
        }

        // 再更新 Floyd（加入节点 k 作为中间节点）
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

    if (ans == INF)
        cout << "No solution.\n";
    else
        cout << ans << '\n';

    return 0;
}
```

**复杂度分析**：O(n³)，n=100 时约 10⁶ 次操作，轻松 AC。

---

## 🎯 本课小结

| 知识点 | 核心要点 |
|--------|---------|
| Floyd | DP：dp[k][i][j] = min(dp[k-1][i][j], dp[k-1][i][k] + dp[k-1][k][j]) |
| k 循环位置 | **必须最外层**，否则 DP 顺序错误 |
| 传递闭包 | Floyd 变体，bitset 优化至 O(V³/64) |
| 无向图最小环 | 在 Floyd 更新前计算 dist[i][j] + g[i][k] + g[k][j] |
| 有向图最小环 | 跑完 Floyd 后检查 min(dist[i][i]) |
| 路径还原 | 维护 nxt[i][j]，更新时 nxt[i][j] = nxt[i][k] |

**一句话总结**：Floyd 是解决多源最短路的经典 DP 算法，通过三重循环在 O(V³) 时间内求出所有点对的最短距离，其思想可推广到传递闭包和最小环问题。k 循环在最外层是关键细节，bitset 优化能让传递闭包承受 V=2000 的规模。
