# 第18课：Dijkstra 算法

## 🎯 考纲要求
- 单源最短路径：Dijkstra 算法
- 朴素实现 $O(V^2)$ 与堆优化 $O(E \log V)$
- 贪心正确性证明
- 负权边不可用的原因

---

## 📖 知识精讲

### 1. 单源最短路径问题

**问题定义**：给定带权图 $G = (V, E)$ 和一个源点 $s$，求 $s$ 到所有其他顶点的最短路径长度。

**Dijkstra 算法**：由荷兰计算机科学家 Edsger W. Dijkstra 于 1956 年提出，解决**非负权图**上的单源最短路径问题。

### 2. 算法核心思想（贪心策略）

Dijkstra 算法的核心思想是**贪心**：

1. 维护集合 $S$：已确定最短路径的顶点集合。
2. 初始时 $S = \{s\}$，$dist[s] = 0$，其余顶点 $dist[v] = \infty$。
3. 每次从**尚未确定**的顶点中选出 $dist$ 值最小的顶点 $u$，将其加入 $S$。
4. 用 $u$ 更新其所有邻接点 $v$ 的距离：$dist[v] = \min(dist[v], dist[u] + w(u, v))$。这一操作称为**松弛（Relaxation）**。
5. 重复步骤 3-4，直到 $S = V$。

**关键洞察**：为什么每次选 dist 最小的未确定顶点是正确的？因为所有边权非负，经过其他尚未确定的顶点到达 $u$ 的路径长度只会更长，不可能比当前 $dist[u]$ 更短。

### 3. 朴素实现 $O(V^2)$

```cpp
int dist[MAXN];
bool vis[MAXN]; // vis[i] = true 表示顶点 i 已确定（已加入 S）

void dijkstra(int s) {
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    dist[s] = 0;
    for (int i = 1; i <= n; i++) {
        // 1. 从未确定顶点中找出 dist 最小的 u
        int u = -1;
        for (int j = 1; j <= n; j++)
            if (!vis[j] && (u == -1 || dist[j] < dist[u]))
                u = j;
        if (u == -1) break; // 剩余顶点不可达
        vis[u] = true;
        // 2. 松弛 u 的所有邻接点
        for (int v = 1; v <= n; v++)
            if (!vis[v] && g[u][v] != INF)
                dist[v] = min(dist[v], dist[u] + g[u][v]);
    }
}
```

- **时间复杂度**：$O(V^2)$。每次找最小 dist 需要 $O(V)$，共 $V$ 轮。
- **适用场景**：**稠密图**（$E \approx V^2$，如 $V \le 1000$）。此时 $O(V^2)$ 优于堆优化的 $O(E \log V)$。

### 4. 堆优化实现 $O(E \log V)$

朴素实现中，"找最小 dist"这一步是瓶颈。使用**优先队列（小根堆）**优化：

```cpp
int dist[MAXN];
bool vis[MAXN];

void dijkstra(int s) {
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    dist[s] = 0;
    // 小根堆：pair<距离, 顶点编号>
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (vis[u]) continue; // 懒删除：已确定顶点跳过
        vis[u] = true;
        for (auto [v, w] : g[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}
```

- **时间复杂度**：$O((V + E) \log V)$，通常简记为 $O(E \log V)$。
  - 每个顶点最多出队一次：$O(V \log V)$。
  - 每条边触发一次松弛，可能产生一次 push：$O(E \log V)$。
- **适用场景**：**稀疏图**（$E \ll V^2$，如 $V = 10^5, E = 2 \times 10^5$）。CSP-S 最常用版本。

### 5. 两种实现对比

| 维度 | 朴素 $O(V^2)$ | 堆优化 $O(E \log V)$ |
|------|-------------|------------------|
| 数据结构 | 邻接矩阵 | 邻接表 + priority\_queue |
| 找最小 | 暴力 $O(V)$ 扫描 | 堆顶 $O(\log V)$ |
| 总复杂度 | $O(V^2)$ | $O((V+E) \log V)$ |
| 适合图类型 | **稠密图** $E \approx V^2$ | **稀疏图** $E \ll V^2$ |
| $V=1000, E=10^5$ | 优 | 也可以 |
| $V=10^5, E=2\times 10^5$ | TLE | ✅ AC |

### 6. 贪心正确性证明

**定理**：在边权非负的图中，Dijkstra 算法能正确求出单源最短路径。

**证明**（数学归纳法）：

设 $S$ 为已确定最短路径的顶点集合。归纳假设：对任意 $u \in S$，$dist[u]$ 等于 $s$ 到 $u$ 的最短距离。

初始时 $S = \{s\}$，$dist[s] = 0$，成立。

归纳步骤：设当前选中的最小 dist 顶点为 $u \notin S$。下面证明 $dist[u]$ 就是 $s$ 到 $u$ 的最短距离。

反证法：假设存在一条更短的 $s \to u$ 路径 $P$。由于 $u \notin S$，路径 $P$ 必然在某个点首次离开 $S$——设该点为 $x$，下一个点为 $y \notin S$。则：
$$
\text{len}(P) \ge dist[x] + w(x, y) \ge dist[y]
$$
（因为 $dist[y]$ 可能已被 $x$ 更新过，即 $dist[y] \le dist[x] + w(x, y)$。）

又因为算法选择的是 $dist$ 最小的未确定顶点，所以 $dist[u] \le dist[y]$。

因此 $\text{len}(P) \ge dist[y] \ge dist[u]$，与 $P$ 比 $dist[u]$ 更短的假设矛盾。故 $dist[u]$ 就是最短距离。$\square$

**关键前提**：边权非负保证了经过更多边不会使路径更短（即 $dist[x] + w(x, y) \ge dist[x]$），从而 $dist[y]$ 的下界是单调的。

### 7. 为什么 Dijkstra 不能处理负权边

**核心原因**：Dijkstra 的贪心性质依赖于"一旦确定某顶点的最短距离，之后就不可能被更新得更短"。这个性质在负权边存在时不成立。

**反例**：

```
    A --(-1)--> B
    |           |
   (2)        (2)
    |           |
    +----(0)--> C
```

- $dist[A]=0$，选择 $B$（$dist[B]=-1$）加入 $S$，确定 $dist[B] = -1$。
- 但实际上存在路径 $A \to C \to B$（经过负权边），因为 $C$ 尚未处理，我们永远不知道这条路会不会更短。
- 更典型的反例：三角形 $A \xrightarrow{2} B, B \xrightarrow{-3} C, A \xrightarrow{1} C$。Dijkstra 先确定 $dist[C]=1$，但实际最短是 $A \to B \to C = -1$。

**负权边场景的替代方案**：SPFA 算法（Bellman-Ford 的队列优化版本）或 Bellman-Ford 算法 $O(VE)$。

### 8. 路径还原

在更新 $dist[v]$ 时记录前驱顶点，最后从终点回溯即可还原完整路径。

```cpp
int pre[MAXN]; // pre[v] = 在最短路径上 v 的前一个顶点
// 在松弛时：
if (dist[v] > dist[u] + w) {
    dist[v] = dist[u] + w;
    pre[v] = u;
    pq.push({dist[v], v});
}
// 还原 s -> t 的路径：
vector<int> path;
for (int v = t; v != s; v = pre[v]) path.push_back(v);
path.push_back(s);
reverse(path.begin(), path.end());
```

### 9. 与其它最短路径算法的关系

| 算法 | 复杂度 | 负权边 | 负环检测 | 适用场景 |
|------|--------|--------|---------|---------|
| Dijkstra（堆优化） | $O(E \log V)$ | ❌ | ❌ | 非负权图首选 |
| Bellman-Ford | $O(VE)$ | ✅ | ✅ | 负权边、负环检测 |
| SPFA | $O(kE)$ 平均，$O(VE)$ 最坏 | ✅ | ✅ | 负权边；竞赛可能被卡 |
| Floyd | $O(V^3)$ | ✅ | ❌ | 全源最短、$V \le 500$ |

---

## 💻 代码模板

### 模板 1：朴素 Dijkstra $O(V^2)$

```cpp
const int MAXN = 1005;
const int INF = 0x3f3f3f3f;
int g[MAXN][MAXN];  // 邻接矩阵
int dist[MAXN];
bool vis[MAXN];
int n;

void dijkstra(int s) {
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    dist[s] = 0;
    for (int i = 1; i <= n; i++) {
        int u = -1;
        for (int j = 1; j <= n; j++)
            if (!vis[j] && (u == -1 || dist[j] < dist[u]))
                u = j;
        if (u == -1 || dist[u] == INF) break;
        vis[u] = true;
        for (int v = 1; v <= n; v++)
            if (!vis[v] && g[u][v] != INF)
                dist[v] = min(dist[v], dist[u] + g[u][v]);
    }
}
```

### 模板 2：堆优化 Dijkstra $O(E \log V)$

```cpp
const int MAXN = 1e5 + 5;
const int INF = 0x3f3f3f3f;
vector<pair<int, int>> g[MAXN]; // g[u] = {v, w}
int dist[MAXN];
bool vis[MAXN];
int n, m;

void dijkstra(int s) {
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, 0, sizeof(vis));
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
                pq.push({dist[v], v});
            }
        }
    }
}
```

### 模板 3：Dijkstra + 路径还原

```cpp
int pre[MAXN];

void dijkstra_with_path(int s) {
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    memset(pre, -1, sizeof(pre));
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
                pre[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}

// 还原路径 s -> t
vector<int> get_path(int s, int t) {
    vector<int> path;
    if (dist[t] == INF) return path; // 不可达
    for (int v = t; v != -1; v = pre[v]) path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}
```

---

## ⚠️ 易错点与优化技巧

### 常见错误

| 错误 | 原因 | 解决方案 |
|------|------|----------|
| vis 标记时机错误 | 在出队才标记 vis | 必须在**松弛后 push 之前不标记**——而是在**出队 pop 之后**标记 vis（懒删除模式） |
| 优先队列默认大根堆 | `priority_queue` 默认最大堆 | 使用 `greater<>` 改为小根堆，或存负数 trick |
| INF 溢出 | `dist[u] + w` 时 INF 加正整数溢出 | 用 `0x3f3f3f3f`（约 10⁹），不达 `INT_MAX` |
| 链式前向星与堆优化混用 | 遍历代码写错 | 熟练掌握两种遍历范式 |
| dist 数组未初始化为 INF | 忘记 memset | 全局变量在需要多次运行时要手动重置 |
| 重边未处理 | 多条边 (u,v) 有不同权重 | 根据题意取最小权值（即最优那条） |
| 无向图只加单向边 | 忘记反向边 | 无向图：`g[u].push_back({v,w}); g[v].push_back({u,w});` |
| SPFA 被卡却用 Dijkstra | 负权边让 Dijkstra 出错 | 负权图必须用 SPFA/Bellman-Ford |

### 优化技巧

1. **`0x3f3f3f3f`**：`memset(dist, 0x3f, sizeof(dist))` 将每字节设为 0x3f，int 值为 0x3f3f3f3f ≈ 10⁶⁷，两个 INF 相加不溢出。这是竞赛中最常用的技巧。

2. **懒删除（Lazy Deletion）**：堆优化中，`vis[u]` 检查放在 `pop` 后（而非 `push` 前），避免了手动 decrease-key 的复杂性。已废弃的旧距离记录将被直接跳过。

3. **稠密图优先朴素版**：当 $E \approx V^2$（如 $V = 500, E = 10^5$），$O(V^2) = 2.5 \times 10^5$，而堆优化 $O(E \log V) \approx 10^5 \times 9 = 9 \times 10^5$，朴素反而更快。

4. **0-1 BFS 替代**：如果边权只有 0 和 1，使用双端队列 BFS 可做到 $O(V + E)$，比 Dijkstra 更优。

5. **多源最短路径**：建立**超级源点** $S$，向每个源点连权为 0 的边，跑一次 Dijkstra 即可。

---

## 📝 真题精练

### 题目 1：单源最短路径（标准版）

**【问题描述】**

给定一个 $n$ 个顶点、$m$ 条边的**有向**带权图，边权均为非负整数。求源点 $s$ 到所有顶点的最短距离。若不可达，输出 $-1$。

**【输入格式】**

第一行三个整数 $n, m, s$。接下来 $m$ 行，每行三个整数 $u, v, w$，表示一条从 $u$ 到 $v$、权值为 $w$ 的有向边。

数据范围：$1 \le n \le 10^5$，$1 \le m \le 2 \times 10^5$，$1 \le w \le 10^9$。

**【输出格式】**

一行 $n$ 个整数，第 $i$ 个表示 $s$ 到 $i$ 的最短距离。若不可达输出 $-1$。

**【参考代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 1e5 + 5;
const ll INF = 1e18;
int n, m, s;
vector<pair<int, ll>> g[MAXN]; // v, w
ll dist[MAXN];
bool vis[MAXN];

void dijkstra(int s) {
    fill(dist, dist + n + 1, INF);
    fill(vis, vis + n + 1, false);
    dist[s] = 0;
    // 小根堆：pair<距离, 顶点>
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (auto [v, w] : g[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m >> s;
    for (int i = 0; i < m; i++) {
        int u, v; ll w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
    }

    dijkstra(s);

    for (int i = 1; i <= n; i++) {
        if (dist[i] == INF) cout << -1;
        else cout << dist[i];
        cout << " \n"[i == n];
    }
    return 0;
}
```

**复杂度分析**：堆优化 $O((n + m) \log n)$，$n=10^5, m=2\times 10^5$ 时可 AC。注意边权可达 $10^9$，dist 用 `long long`。

---

### 题目 2：带路径还原的最短路径

**【问题描述】**

给定一个 $n$ 个顶点、$m$ 条边的有向带权图（非负权），求源点 $s$ 到目标点 $t$ 的最短路径。输出路径长度和完整的路径序列。若不可达，输出 `-1`。

数据范围：$1 \le n \le 10^5$，$1 \le m \le 2 \times 10^5$，$1 \le w \le 10^4$。

**【输入格式】**

第一行 $n, m, s, t$。接下来 $m$ 行，每行 $u, v, w$。

**【输出格式】**

第一行输出最短距离。第二行输出路径经过的顶点序列（用空格分隔）。若不可达，只输出 `-1`。

**【参考代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;
const int INF = 0x3f3f3f3f;
vector<pair<int, int>> g[MAXN];
int dist[MAXN], pre[MAXN];
bool vis[MAXN];
int n, m, s, t;

void dijkstra(int s) {
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    memset(pre, -1, sizeof(pre));
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
                pre[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}

vector<int> get_path(int t) {
    vector<int> path;
    if (dist[t] == INF) return path;
    for (int v = t; v != -1; v = pre[v]) path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m >> s >> t;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
    }

    dijkstra(s);
    vector<int> path = get_path(t);

    if (path.empty()) {
        cout << -1 << '\n';
    } else {
        cout << dist[t] << '\n';
        for (size_t i = 0; i < path.size(); i++)
            cout << path[i] << " \n"[i + 1 == path.size()];
    }
    return 0;
}
```

**复杂度分析**：$O((n + m) \log n)$，路径还原只需 $O(n)$ 额外时间。可 AC。

---

## 🎯 本课小结

1. **Dijkstra 算法**是解决**非负权图**单源最短路径的标准算法，基于贪心策略。
2. **朴素 $O(V^2)$** 适合稠密图（$V \le 1000$），配合邻接矩阵使用。
3. **堆优化 $O(E \log V)$** 是 CSP-S 最常用版本，配合邻接表使用。
4. **正确性前提**：所有边权必须非负。负权边请用 SPFA / Bellman-Ford。
5. **关键细节**：vis 标记在 pop 后进行（懒删除），dist 用 $0x3f3f3f3f$ 初始化避免溢出，优先队列用 `greater<>` 实现小根堆。
6. **路径还原**只需在松弛时记录 `pre[v] = u`，最后回溯即可。
