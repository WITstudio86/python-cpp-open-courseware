# 第19课：Bellman-Ford 与 SPFA

## 🎯 考纲要求

- **Bellman-Ford算法**处理负权边的单源最短路
- **负环检测**方法：第 n 轮仍发生松弛则存在负环
- **SPFA算法**（队列优化的 Bellman-Ford），及其期望/最坏复杂度
- SPFA 的优化技巧：**SLF**（Small Label First）、**LLL**（Large Label Last）
- 卡 SPFA 的数据构造原理与应对策略

## 📖 知识精讲

### 一、Bellman-Ford 算法

#### 1. 核心思想

Bellman-Ford 算法可以处理**带有负权边**的有向图（但不能有负环，否则不存在最短路）。算法基于动态规划：对所有边进行 V-1 轮松弛操作。

**状态定义**：第 k 轮松弛后，`dist[v]` 表示从源点出发，经过**不超过 k 条边**到达 v 的最短距离。

**松弛操作**：对每条边 `(u, v, w)`，若 `dist[u] + w < dist[v]`，则更新 `dist[v] = dist[u] + w`。

#### 2. 为什么是 V-1 轮？

在无负环的图中，任意两点间的最短路径最多经过 V-1 条边（因为路径中不会重复经过同一个点）。因此 V-1 轮松弛足以找出所有最短路。

#### 3. 负环检测

进行第 V 轮松弛：若仍有边可以被松弛，说明图中存在**从源点可达的负环**。因为经过 V 条边的路径一定重复经过了某个顶点，形成了环路，且该环路权值和为负。

#### 4. 复杂度

- 时间复杂度：O(VE)
- 空间复杂度：O(V + E)（若使用边集数组，仅需 O(V) 存 dist）

#### 5. 路径还原

松弛时记录前驱 `pre[v] = u`，最后从终点反向追踪即可还原路径。若存在负环，则路径无意义。

---

### 二、SPFA 算法（Shortest Path Faster Algorithm）

#### 1. 核心思想

SPFA 是 Bellman-Ford 的**队列优化**版本。观察到：只有上一轮被松弛的节点，其出边才可能在下一轮引起新的松弛。因此用队列维护"被更新过的节点"。

**算法流程**：

1. 初始化 `dist[s] = 0`，其余为 INF，源点入队
2. 当队列非空：
   - 取出队首 u，标记为不在队列中
   - 遍历 u 的所有出边 `(u, v, w)`
   - 若 `dist[u] + w < dist[v]`：
     - 更新 `dist[v] = dist[u] + w`
     - 若 v 不在队列中，则 v 入队
3. 队列为空时算法结束

#### 2. 复杂度分析

- **期望复杂度**（随机图）：O(kE)，其中 k 是一个小常数（通常 k ≤ 2）
- **最坏时间复杂度**：O(VE)，和 Bellman-Ford 相同
- **空间复杂度**：O(V + E)

#### 3. 负环检测（SPFA版本）

方法一：统计每个节点的**入队次数**，若某节点入队超过 V 次，则存在负环。

方法二：统计最短路径的**边数** `cnt[v]`，若 `cnt[v] ≥ V`，则存在负环。

---

### 三、SLF 与 LLL 优化

#### 1. SLF（Small Label First）

入队时，若 `dist[v] < dist[q.front()]`，则将 v 插入**队首**而非队尾。这使距离更小的节点优先被处理，减少无效松弛。实现时需使用 `deque`。

```cpp
if (dist[v] < dist[q.front()])
    q.push_front(v);
else
    q.push_back(v);
```

#### 2. LLL（Large Label Last）

出队时，若队首节点的 `dist` 大于队列中所有节点 dist 的平均值，则将其移到队尾，取下一个。

实际竞赛中 SLF 更常用，LLL 效果不稳定。二者可结合使用。

---

### 四、卡 SPFA 的数据构造

#### 1. 攻击原理

构造**网格图**（grid graph）或**蒲公英图**，使得大量节点的距离被反复更新的节点反复松弛，退化为 O(VE)。

典型的构造方式：让最短路的更新顺序和 SPFA 的遍历顺序高度不一致，导致每个节点被松弛 O(V) 次。

#### 2. 应对策略

- 在没有负权边的题中，**优先使用 Dijkstra**
- 随机化边表顺序，打乱邻接表（可抵抗非针对性数据）
- 使用 SLF + LLL 组合优化（但并不能完全防御）
- 对于稀疏图的最短路，若确定无负权边，坚决不用 SPFA
- 在 CSP-S 中，出题人若刻意卡 SPFA，通常只有 Bellman-Ford 的严格 O(VE) 或 Floyd 能稳定通过

---

## 💻 代码模板

### 1. Bellman-Ford（边集数组实现）

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005, MAXM = 200005;
const long long INF = 1e18;

struct Edge {
    int u, v, w;
} edges[MAXM];

long long dist[MAXN];
int n, m;

// 返回 true 表示无负环，false 表示存在负环
bool bellman_ford(int s) {
    fill(dist, dist + n + 1, INF);
    dist[s] = 0;
    for (int i = 1; i < n; i++) {          // V-1 轮松弛
        bool updated = false;
        for (int j = 1; j <= m; j++) {
            int u = edges[j].u, v = edges[j].v, w = edges[j].w;
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                updated = true;
            }
        }
        if (!updated) break;  // 提前终止优化
    }
    // 第 V 轮检测负环
    for (int j = 1; j <= m; j++) {
        int u = edges[j].u, v = edges[j].v, w = edges[j].w;
        if (dist[u] != INF && dist[u] + w < dist[v])
            return false;  // 存在负环
    }
    return true;
}
```

### 2. SPFA（邻接表 + 队列）

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
const long long INF = 1e18;

vector<pair<int, int>> g[MAXN];  // (v, w)
long long dist[MAXN];
int cnt[MAXN];   // 入队次数 / 路径边数
bool inq[MAXN];  // 是否在队列中
int n, m;

// 返回 true 表示无负环，false 表示存在负环
bool spfa(int s) {
    fill(dist, dist + n + 1, INF);
    fill(cnt, cnt + n + 1, 0);
    fill(inq, inq + n + 1, false);
    
    queue<int> q;
    dist[s] = 0;
    q.push(s);
    inq[s] = true;
    cnt[s] = 1;
    
    while (!q.empty()) {
        int u = q.front(); q.pop();
        inq[u] = false;
        for (auto &e : g[u]) {
            int v = e.first, w = e.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (!inq[v]) {
                    q.push(v);
                    inq[v] = true;
                    cnt[v]++;
                    if (cnt[v] > n) return false;  // 入队超过 n 次 → 负环
                }
            }
        }
    }
    return true;
}
```

### 3. SPFA + SLF 优化

```cpp
bool spfa_slf(int s) {
    fill(dist, dist + n + 1, INF);
    fill(cnt, cnt + n + 1, 0);
    fill(inq, inq + n + 1, false);
    
    deque<int> q;
    dist[s] = 0;
    q.push_back(s);
    inq[s] = true;
    cnt[s] = 1;
    
    while (!q.empty()) {
        int u = q.front(); q.pop_front();
        inq[u] = false;
        for (auto &e : g[u]) {
            int v = e.first, w = e.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (!inq[v]) {
                    // SLF：若 dist[v] 比队首更小，插入队首
                    if (!q.empty() && dist[v] < dist[q.front()])
                        q.push_front(v);
                    else
                        q.push_back(v);
                    inq[v] = true;
                    cnt[v]++;
                    if (cnt[v] > n) return false;
                }
            }
        }
    }
    return true;
}
```

---

## ⚠️ 易错点与优化技巧

### 常见错误

1. **SPFA 节点可能多次入队**：节点出队后 `inq` 标记清为 false，后续可再次入队。这是正确行为，不是 bug。

2. **负环判断方式要对**：
   - 方法一（入队次数）：`cnt[v] > n`（即入队 n+1 次）—— 严格正确
   - 方法二（路径边数）：`cnt[v] >= n`（路径经过 n 条边，即 n+1 个点）—— 更精确
   - 推荐使用方法二，因为边数超限是最短路径性质直接推出的

3. **INF 的初始化**：使用 `0x3f3f3f3f`（int）或 `1e18`（long long），注意 `INF + w` 不要溢出

4. **disconnected graph**：Bellman-Ford/SPFA 只能更新从源点可达的节点，不可达节点距离保持 INF。负环检测也只检测源点可达的负环

### 优化技巧

1. **优先使用 Dijkstra**：在无负权边的场景下，Dijkstra 的 O((V+E)logV) 稳定且不会被卡

2. **随机化**：建图时 `random_shuffle` 打乱邻接表顺序，可抵抗部分非针对性卡 SPFA 数据

3. **SLF 开关**：部分题目 SLF 反而会拖慢速度，可自行测试后决定是否开启

4. **SPFA 判负环**：可用一个全局计数器，累计松弛次数超过某个阈值（如 `m * log(n)`）时直接判定为负环，加速判环

---

## 📝 真题精练

### 题目1：P3385 【模板】负环

**题意**：给定 n 个点 m 条有向边（有负权），判断是否存在负环。

**思路**：直接跑 SPFA 判负环模板。注意图可能不连通（负环可能不在源点可达范围内），需要将所有点初始入队或建立超级源点。

**AC 代码**：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2005, MAXM = 6005;
const int INF = 0x3f3f3f3f;

struct Edge { int to, w, nxt; } e[MAXM];
int head[MAXN], tot;
int dist[MAXN], cnt[MAXN];
bool inq[MAXN];
int n, m;

void add(int u, int v, int w) {
    e[++tot] = {v, w, head[u]};
    head[u] = tot;
}

bool spfa() {
    queue<int> q;
    // 所有点初始入队（处理不连通情况）
    for (int i = 1; i <= n; i++) {
        dist[i] = 0;
        cnt[i] = 0;
        inq[i] = true;
        q.push(i);
    }
    int relax_cnt = 0;  // 松弛总次数（加速判环）
    while (!q.empty()) {
        int u = q.front(); q.pop();
        inq[u] = false;
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].to, w = e[i].w;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= n) return true;  // 存在负环
                if (++relax_cnt > 10000 * n) return true;  // 阈值加速
                if (!inq[v]) {
                    q.push(v);
                    inq[v] = true;
                }
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        cin >> n >> m;
        tot = 0;
        fill(head, head + n + 1, 0);
        for (int i = 1; i <= m; i++) {
            int u, v, w; cin >> u >> v >> w;
            add(u, v, w);
            if (w >= 0) add(v, u, w);  // 题目规定非负权边是双向的
        }
        cout << (spfa() ? "YES\n" : "NO\n");
    }
    return 0;
}
```

**复杂度分析**：最坏 O(VE)，实际期望 O(kE)。N ≤ 2000, M ≤ 6000 可行。

---

### 题目2：P3371 【模板】单源最短路径（弱化版）

**题意**：n ≤ 10^4, m ≤ 5×10^5，有向带权图（可能有负权），求源点到各点的最短距离。

**思路**：Bellman-Ford O(VE) = 5×10^9 会超时，需要 SPFA。若数据未刻意卡，SPFA 可以通过。

**AC 代码**（SPFA 核心逻辑同上题，略去判环部分）：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 10005, MAXM = 500005;
const long long INF = 2147483647;  // 题目指定

struct Edge { int to, w, nxt; } e[MAXM];
int head[MAXN], tot;
long long dist[MAXN];
bool inq[MAXN];

void add(int u, int v, int w) {
    e[++tot] = {v, w, head[u]};
    head[u] = tot;
}

void spfa(int s) {
    fill(dist, dist + MAXN, INF);
    queue<int> q;
    dist[s] = 0; q.push(s); inq[s] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        inq[u] = false;
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].to, w = e[i].w;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (!inq[v]) { q.push(v); inq[v] = true; }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, s;
    cin >> n >> m >> s;
    for (int i = 1; i <= m; i++) {
        int u, v, w; cin >> u >> v >> w;
        add(u, v, w);
    }
    spfa(s);
    for (int i = 1; i <= n; i++)
        cout << dist[i] << " \n"[i == n];
    return 0;
}
```

**复杂度分析**：期望 O(kE)，最坏 O(VE)。在有负权边的场景下是合理选择。

---

## 🎯 本课小结

| 知识点 | 核心要点 |
|--------|---------|
| Bellman-Ford | V-1轮松弛，第k轮的dist表示经过不超过k条边的最短路 |
| 负环检测 | 第V轮仍可松弛 → 存在负环；SPFA中cnt[v] ≥ n → 负环 |
| SPFA | 队列优化，期望O(kE)，最坏O(VE) |
| SLF优化 | dist[v] < 队首则插入队首，使用deque |
| 卡SPFA | 网格图/蒲公英图构造，优先用Dijkstra处理正权图 |

**一句话总结**：Bellman-Ford 可以处理负权边，SPFA 是其队列优化版，在随机图上很快但可能被卡退化为 O(VE)。竞赛中无负权边优先选 Dijkstra，有负权边再考虑 SPFA。
