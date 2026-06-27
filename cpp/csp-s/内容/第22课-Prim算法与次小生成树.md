# 第22课：Prim 算法与次小生成树

## 🎯 考纲要求
- Prim算法 O(V²) 朴素实现（稠密图适用）
- Prim堆优化 O(E log V)
- 严格次小生成树（非严格/严格）
- 枚举非树边替换

## 📖 知识精讲

### 1. Prim 算法原理

Prim 算法是另一种经典的 MST 构造算法，与 Kruskal 的"选边"不同，Prim 采取"选点"策略。

**核心思想：** 维护一个已选顶点集合 S，初始 S = {1}（任意起点）。每次从 S 到 V\S 的跨越边中选择权值最小的边 (u, v)，其中 u ∈ S，v ∈ V\S，然后将 v 加入 S。重复直到 S = V。

**直观理解：** 就像一棵树从根节点开始"生长"，每次将离树最近的外部节点"吸收"进来。

**Prim 与 Dijkstra 的区别：**
- Dijkstra 维护的是"到源点的最短距离"，更新条件：`dis[v] = min(dis[v], dis[u] + w)`
- Prim 维护的是"到已选集合的最小边权"，更新条件：`dis[v] = min(dis[v], w)`

两段代码几乎完全相同，唯一区别在于更新距离的公式：Dijkstra 累加路径，Prim 只需边权本身。这也是竞赛中常见的"混淆点"。

### 2. 朴素 Prim — O(V²)

使用邻接矩阵 `g[u][v]` 存储边权，适用于 **稠密图**（\( E \approx V^2 \)）。

**算法步骤：**
```
dis[1..n] ← INF
dis[1] ← 0
vis[1..n] ← false
mst ← 0
for i = 1..n:
    在所有未访问节点中找 dis 最小的节点 u
    vis[u] ← true
    mst ← mst + dis[u]
    for v = 1..n:
        if !vis[v] and g[u][v] < dis[v]:
            dis[v] ← g[u][v]
```

**时间复杂度：** \( O(V^2) \)。当 \( V \le 5000 \) 且 \( E \) 很大时，朴素 Prim 反而比堆优化更快（常数小、无堆操作开销）。

**适用场景判断：**
- 完全图或接近完全图（如 \( m \approx n^2 \)）→ 朴素 Prim
- 随机稀疏图 → Kruskal 或堆优化 Prim

### 3. 堆优化 Prim — O(E log V)

使用邻接表 `adj` + 优先队列（最小堆），适用于 **稀疏图**（与 Kruskal 竞争的场景）。

**算法步骤：**
```
dis[1..n] ← INF
vis[1..n] ← false
dis[1] ← 0
pq.push({0, 1})  // {边权, 节点}
mst ← 0, cnt ← 0
while !pq.empty() and cnt < n:
    {d, u} ← pq.top(), pq.pop()
    if vis[u]: continue
    vis[u] ← true
    mst ← mst + d, cnt++
    for {v, w} in adj[u]:
        if !vis[v] and w < dis[v]:
            dis[v] ← w
            pq.push({w, v})
```

**时间复杂度：** \( O((V + E) \log V) \) 或简写为 \( O(E \log V) \)。

**与 Kruskal 对比：**

| 维度 | Kruskal O(E log E) | Prim (堆优化) O(E log V) | Prim (朴素) O(V²) |
|------|-------------------|------------------------|-------------------|
| 核心操作 | 排序 + 并查集 | 优先队列 | 线性扫描 |
| 适合图类型 | 稀疏图 | 稀疏图 | **稠密图** |
| 空间需求 | O(E + V) | O(E + V) | **O(V²)** |
| 实现难度 | 简单 | 中等 | 最简单 |
| 能否处理负权边 | 能（排序即可） | 能 | 能 |

### 4. 次小生成树（Second MST）

**定义：** 所有生成树中边权和**第二小**的那棵。若与 MST 权值相等也算"次小"（非严格次小），若必须**严格小于**则是严格次小。

**非严格次小生成树：** 边权和 ≥ MST 权值的最小生成树（可与 MST 权值相同）。

**严格次小生成树：** 边权和 **严格大于** MST 权值的最小生成树。

**核心算法（枚举非树边替换）：**

1. 先求出 MST，记录 MST 边集。
2. 对于每一条**非树边** \( e = (u, v, w) \)：
   - 将 e 加入 MST 会形成一个环
   - 从环上去掉一条**最大边权**（或严格次大，下文说明）的树边 f
   - 新生成树的权值 = `mst_weight - w(f) + w(e)`
3. 取所有替换方案中的最小值即得次小生成树。

**严格 vs 非严格的区别：**
- **非严格：** 去掉 MST 路径上最大边权即可（即使 `w(f) == w(e)`，权值不变，也算合法次小）
- **严格：** 若 `w(f) == w(e)`，替换后权值不变，需要去掉**严格次大边权**（第二大的）

因此严格次小生成树需要预处理树上每条路径的**最大值**和**严格次大值**。

### 5. 树上路径最大值 / 次大值预处理（倍增 + LCA）

对于 MST 上的每条路径，需要用倍增法（或树剖）预处理：

- `up[u][k]`：节点 u 的第 \( 2^k \) 级祖先
- `mx[u][k]`：节点 u 到第 \( 2^k \) 级祖先路径上的**最大边权**
- `mx2[u][k]`：节点 u 到第 \( 2^k \) 级祖先路径上的**严格次大边权**

**DFS 预处理：**
```
up[v][0] = u
mx[v][0] = w_uv
mx2[v][0] = -INF  // 单条边没有次大值
for k = 1..LOG-1:
    up[v][k] = up[up[v][k-1]][k-1]
    mx[v][k] = max(mx[v][k-1], mx[up[v][k-1]][k-1])
    // 次大值在四个候选值中找严格小于最大值的最大者
    mx2[v][k] = 四选一(mx[v][k-1], mx2[v][k-1], mx[up[v][k-1]][k-1], mx2[up[v][k-1]][k-1])
```

**查询 `query(u, v)` 获取路径上最大/次大值：**
- 类似 LCA 查询，将 u 和 v 跳到同一深度
- 沿途收集各段的 `mx` 和 `mx2`
- 在所有收集到的值中找出最大值和严格次大值

### 6. 严格次小生成树完整算法

1. Kruskal（或 Prim）求 MST，记录 MST 边集
2. 在 MST 上进行 DFS，预处理倍增数组（`up`, `mx`, `mx2`, `depth`）
3. 遍历所有**非树边** `e = (u, v, w)`：
   - 查询 u 到 v 路径上的最大边权 `max_w` 和严格次大边权 `max2_w`
   - 若 `w > max_w`：候选答案 = `mst_weight - max_w + w`（替换最大边）
   - 若 `w == max_w` 且 `max2_w != -INF`：候选答案 = `mst_weight - max2_w + w`（替换次大边，得到严格更大的生成树）
4. 所有候选答案的最小值即为严格次小生成树权值

**复杂度：** MST O(E log E) + 倍增预处理 O(V log V) + 枚举非树边 O(E log V) = **O(E log E + V log V)**

### 7. 代码实现要点

- `mx2[ ][ ]` 初始化为 `-INF`（或 -1e18），表示"不存在次大值"
- 合并四个候选值时注意去重（两个最大值相等时，次大值取第二大的不同值）
- 倍增的 LOG 一般取 `ceil(log2(n)) + 1`，n ≤ 1e5 时取 17-20

## 💻 代码模板

### 朴素 Prim（邻接矩阵）

```cpp
const int MAXN = 5005;
const int INF = 0x3f3f3f3f;
int g[MAXN][MAXN];  // 邻接矩阵
int dis[MAXN];
bool vis[MAXN];

long long prim(int n) {
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    dis[1] = 0;
    long long mst = 0;
    for (int i = 1; i <= n; i++) {
        int u = -1;
        for (int j = 1; j <= n; j++)
            if (!vis[j] && (u == -1 || dis[j] < dis[u]))
                u = j;
        if (dis[u] == INF) return -1;  // 不连通
        vis[u] = true;
        mst += dis[u];
        for (int v = 1; v <= n; v++)
            if (!vis[v] && g[u][v] < dis[v])
                dis[v] = g[u][v];
    }
    return mst;
}
```

### 堆优化 Prim（邻接表 + 优先队列）

```cpp
struct Edge { int to, w; };
vector<Edge> adj[MAXN];
int dis[MAXN];
bool vis[MAXN];

long long prim_heap(int n) {
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    dis[1] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    pq.push({0, 1});
    long long mst = 0;
    int cnt = 0;
    while (!pq.empty() && cnt < n) {
        auto [d, u] = pq.top(); pq.pop();
        if (vis[u]) continue;
        vis[u] = true;
        mst += d;
        cnt++;
        for (auto& e : adj[u]) {
            int v = e.to, w = e.w;
            if (!vis[v] && w < dis[v]) {
                dis[v] = w;
                pq.push({w, v});
            }
        }
    }
    return (cnt == n) ? mst : -1;
}
```

### 严格次小生成树（倍增 + LCA）

```cpp
const int MAXN = 100005;
const int LOG = 20;
const long long INF_LL = 1e18;

int up[MAXN][LOG];
long long mx[MAXN][LOG], mx2[MAXN][LOG];
int depth[MAXN];
vector<pair<int,int>> mst_adj[MAXN]; // MST 邻接表

// DFS 预处理倍增数组
void dfs(int u, int fa) {
    for (auto& [v, w] : mst_adj[u]) {
        if (v == fa) continue;
        depth[v] = depth[u] + 1;
        up[v][0] = u;
        mx[v][0] = w;
        mx2[v][0] = -INF_LL;
        for (int i = 1; i < LOG; i++) {
            up[v][i] = up[up[v][i-1]][i-1];
            // 合并四个候选值取最大和严格次大
            long long cand[4] = {
                mx[v][i-1], mx2[v][i-1],
                mx[up[v][i-1]][i-1], mx2[up[v][i-1]][i-1]
            };
            mx[v][i] = -INF_LL;
            mx2[v][i] = -INF_LL;
            for (int j = 0; j < 4; j++) {
                if (cand[j] > mx[v][i]) {
                    mx2[v][i] = mx[v][i];
                    mx[v][i] = cand[j];
                } else if (cand[j] < mx[v][i] && cand[j] > mx2[v][i]) {
                    mx2[v][i] = cand[j];
                }
            }
        }
        dfs(v, u);
    }
}

// 查询 u 到 v 路径上的最大值和严格次大值
// 返回 {max_w, max2_w}
pair<long long, long long> query(int u, int v) {
    long long max_w = -INF_LL, max2_w = -INF_LL;
    if (depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    for (int i = 0; diff; i++, diff >>= 1) {
        if (diff & 1) {
            // 合并当前段
            if (mx[u][i] > max_w) {
                max2_w = max({max2_w, max_w, mx2[u][i]});
                max_w = mx[u][i];
            } else if (mx[u][i] < max_w && mx[u][i] > max2_w) {
                max2_w = mx[u][i];
            }
            u = up[u][i];
        }
    }
    if (u == v) return {max_w, max2_w};
    for (int i = LOG - 1; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            // 合并 u 段
            if (mx[u][i] > max_w) {
                max2_w = max({max2_w, max_w, mx2[u][i]});
                max_w = mx[u][i];
            } else if (mx[u][i] < max_w && mx[u][i] > max2_w) {
                max2_w = mx[u][i];
            }
            // 合并 v 段
            if (mx[v][i] > max_w) {
                max2_w = max({max2_w, max_w, mx2[v][i]});
                max_w = mx[v][i];
            } else if (mx[v][i] < max_w && mx[v][i] > max2_w) {
                max2_w = mx[v][i];
            }
            u = up[u][i];
            v = up[v][i];
        }
    }
    // 最后一步（父节点）
    for (int x : {u, v}) {
        if (mx[x][0] > max_w) {
            max2_w = max({max2_w, max_w, mx2[x][0]});
            max_w = mx[x][0];
        } else if (mx[x][0] < max_w && mx[x][0] > max2_w) {
            max2_w = mx[x][0];
        }
    }
    return {max_w, max2_w};
}
```

## ⚠️ 易错点与优化技巧

### 常见错误

1. **Prim 与 Dijkstra 混淆：** 两者代码几乎一样，区别在于更新 `dis` 的公式。
   - Prim: `dis[v] = min(dis[v], w)`（到集合的最小边权）
   - Dijkstra: `dis[v] = min(dis[v], dis[u] + w)`（到源点的最短路径）
   写错一个字母，结果完全不同！

2. **次小生成树中"严格"与"非严格"的区别：**
   - 非严格：只需路径最大边权 `max_w`，用 `w(e) - max_w` 更新即可
   - 严格：若 w(e) == max_w，需用 `w(e) - max2_w`（次大值），否则替换后权值不变
   - 常见错误：忘记维护 `mx2` 数组导致严格次小生成树求错

3. **INF 初始化不够大：** 边权范围可能到 1e9，n 到 1e5，MST 权值可能到 1e14，`mx2` 的 `-INF` 需设置为 `-1e18` 级别。

4. **倍增数组大小不足：** `LOG` 需要 ≥ `ceil(log2(n)) + 1`。n=1e5 时 LOG=17 足够，n=3e5 时需要 LOG=19-20。

5. **MST 上 DFS 的根节点选择：** 任意节点均可作为 DFS 起点（通常选 1）。

6. **堆优化 Prim 中的重复入队：** 同一个节点可能多次入队（dis 更新后旧值仍在堆中），需用 `vis` 数组检查。

### 优化技巧

1. **稠密图优先用朴素 Prim：** 当 m ≈ n² 时，O(V²) 的朴素 Prim 常数极小，比 O(E log V) 的堆优化快得多。

2. **MST 唯一性判断：** Kruskal 的同权边组判断法也适用于 Prim 生成的 MST。

3. **次小生成树的非树边遍历优化：** 只需遍历非树边（不在 MST 中的边），可通过标记 `in_mst` 来区分。

4. **合并候选值时提取函数：** 多次出现"四个值中取最大和次大"的逻辑，可封装为 `merge_max2` 函数，减少重复代码和错误。

5. **LCA 查询优化：** 在实际竞赛代码中，可以将"跳深度"和"找 LCA"两阶段合并为一次 `query` 调用，上面模板已体现。

## 📝 真题精练

### 例题 1：最小生成树（稠密图版）

**题目描述：** 给定 n 个点的完全图（n ≤ 5000），每条边 (i, j) 的权值为 `(A_i xor A_j)` 或直接给出邻接矩阵。求 MST。

**输入格式：** 第一行 n，接下来 n 行每行 n 个整数表示邻接矩阵 `g[i][j]`。

**输出格式：** MST 总权值。

**解题思路：** 此题为稠密图（完全图有 O(n²) 条边），使用 Kruskal 或堆优化 Prim 会因边数过多而超时。应使用朴素 Prim O(n²)。

**参考代码（AC）：**

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5005;
const int INF = 0x3f3f3f3f;

int g[MAXN][MAXN];
int dis[MAXN];
bool vis[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // 读入邻接矩阵
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> g[i][j];
        }
    }

    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));

    dis[1] = 0;
    long long mst = 0;

    for (int i = 1; i <= n; i++) {
        int u = -1;
        // 找到未访问节点中 dis 最小的
        for (int j = 1; j <= n; j++) {
            if (!vis[j] && (u == -1 || dis[j] < dis[u])) {
                u = j;
            }
        }

        if (dis[u] == INF) {
            cout << "orz\n";  // 不连通（完全图不会出现）
            return 0;
        }

        vis[u] = true;
        mst += dis[u];

        // 用 u 更新邻接点
        for (int v = 1; v <= n; v++) {
            if (!vis[v] && g[u][v] < dis[v]) {
                dis[v] = g[u][v];
            }
        }
    }

    cout << mst << '\n';
    return 0;
}
```

**复杂度分析：** O(n²)，对于 n ≤ 5000 的完全图，操作量约 2.5 × 10⁷，在 C++ 中可 1s 内完成。若用 Kruskal，边数 = n(n-1)/2 ≈ 1.25 × 10⁷，排序 O(m log m) 会超时。

---

### 例题 2：严格次小生成树（模板题）

**题目描述：** 给定 n 个点 m 条边的无向连通图（n ≤ 10⁵, m ≤ 3×10⁵），求**严格次小生成树**的边权和。数据保证存在严格次小生成树。

**输入格式：** 第一行 n m，接下来 m 行 u v w（1 ≤ w ≤ 10⁹）。

**输出格式：** 严格次小生成树的边权和。

**参考代码（AC）：**

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int MAXN = 100005;
const int MAXM = 300005;
const int LOG = 20;
const ll INF_LL = 1e18;

struct Edge {
    int u, v, w, id;
    bool in_mst;
    bool operator<(const Edge& rhs) const {
        if (w != rhs.w) return w < rhs.w;
        return u < rhs.u;
    }
} edges[MAXM];

// 并查集
struct DSU {
    int fa[MAXN], sz[MAXN];
    void init(int n) {
        for (int i = 1; i <= n; i++) fa[i] = i, sz[i] = 1;
    }
    int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
    bool merge(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (sz[x] < sz[y]) swap(x, y);
        fa[y] = x; sz[x] += sz[y];
        return true;
    }
} dsu;

// MST 邻接表
vector<pair<int,int>> mst_adj[MAXN];

// 倍增
int up[MAXN][LOG];
ll mx[MAXN][LOG], mx2[MAXN][LOG];
int depth[MAXN];

void dfs(int u, int fa) {
    for (auto& [v, w] : mst_adj[u]) {
        if (v == fa) continue;
        depth[v] = depth[u] + 1;
        up[v][0] = u;
        mx[v][0] = w;
        mx2[v][0] = -INF_LL;
        for (int i = 1; i < LOG; i++) {
            int mid = up[v][i-1];
            up[v][i] = up[mid][i-1];
            // 四个候选值
            vector<ll> cand = {mx[v][i-1], mx2[v][i-1], mx[mid][i-1], mx2[mid][i-1]};
            mx[v][i] = -INF_LL; mx2[v][i] = -INF_LL;
            for (ll val : cand) {
                if (val > mx[v][i]) {
                    mx2[v][i] = mx[v][i];
                    mx[v][i] = val;
                } else if (val < mx[v][i] && val > mx2[v][i]) {
                    mx2[v][i] = val;
                }
            }
        }
        dfs(v, u);
    }
}

// 查询 u->v 路径的 {最大值, 严格次大值}
pair<ll, ll> query(int u, int v) {
    ll max_w = -INF_LL, max2_w = -INF_LL;
    if (depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    for (int i = 0; diff; i++, diff >>= 1) {
        if (diff & 1) {
            if (mx[u][i] > max_w) {
                max2_w = max({max2_w, max_w, mx2[u][i]});
                max_w = mx[u][i];
            } else if (mx[u][i] < max_w && mx[u][i] > max2_w) {
                max2_w = mx[u][i];
            }
            u = up[u][i];
        }
    }
    if (u == v) return {max_w, max2_w};
    for (int i = LOG - 1; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            // 合并 u 段
            if (mx[u][i] > max_w) {
                max2_w = max({max2_w, max_w, mx2[u][i]});
                max_w = mx[u][i];
            } else if (mx[u][i] < max_w && mx[u][i] > max2_w) {
                max2_w = mx[u][i];
            }
            // 合并 v 段
            if (mx[v][i] > max_w) {
                max2_w = max({max2_w, max_w, mx2[v][i]});
                max_w = mx[v][i];
            } else if (mx[v][i] < max_w && mx[v][i] > max2_w) {
                max2_w = mx[v][i];
            }
            u = up[u][i]; v = up[v][i];
        }
    }
    // 合并最后一步
    for (int x : {u, v}) {
        if (mx[x][0] > max_w) {
            max2_w = max({max2_w, max_w, mx2[x][0]});
            max_w = mx[x][0];
        } else if (mx[x][0] < max_w && mx[x][0] > max2_w) {
            max2_w = mx[x][0];
        }
    }
    return {max_w, max2_w};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].id = i;
        edges[i].in_mst = false;
    }

    // ===== 1. Kruskal 求 MST =====
    sort(edges + 1, edges + m + 1);
    dsu.init(n);
    ll mst_weight = 0;
    int cnt = 0;
    for (int i = 1; i <= m; i++) {
        if (dsu.merge(edges[i].u, edges[i].v)) {
            mst_weight += edges[i].w;
            edges[i].in_mst = true;
            cnt++;
            int u = edges[i].u, v = edges[i].v, w = edges[i].w;
            mst_adj[u].push_back({v, w});
            mst_adj[v].push_back({u, w});
            if (cnt == n - 1) break;
        }
    }

    // ===== 2. 倍增预处理 =====
    depth[1] = 1;
    for (int i = 0; i < LOG; i++) {
        up[1][i] = 1;
        mx[1][i] = -INF_LL;
        mx2[1][i] = -INF_LL;
    }
    dfs(1, 0);

    // ===== 3. 枚举非树边求次小生成树 =====
    ll ans = INF_LL;
    for (int i = 1; i <= m; i++) {
        if (edges[i].in_mst) continue;  // 跳过树边
        int u = edges[i].u, v = edges[i].v, w = edges[i].w;
        auto [max_w, max2_w] = query(u, v);
        if (w > max_w) {
            ans = min(ans, mst_weight - max_w + w);
        } else if (max2_w != -INF_LL) {
            // w == max_w，用严格次大值替换
            ans = min(ans, mst_weight - max2_w + w);
        }
    }

    cout << ans << '\n';
    return 0;
}
```

**复杂度分析：**
- Kruskal 排序：O(m log m) ≈ 3×10⁵ × 18 ≈ 5.4×10⁶
- 倍增预处理：O(n log n) ≈ 10⁵ × 20 = 2×10⁶
- 枚举非树边查询：O(m log n) ≈ 3×10⁵ × 20 = 6×10⁶
- 总复杂度：O((n+m) log n)，足以通过 n≤10⁵, m≤3×10⁵ 的数据。

---

## 🎯 本课小结

1. **Prim 算法** 是"选点"策略，维护到已选集合的最小边权
2. **朴素 Prim O(V²)** 适合稠密图（完全图、邻接矩阵输入）
3. **堆优化 Prim O(E log V)** 适合稀疏图，与 Kruskal 竞争
4. **Prim 与 Dijkstra 的区别**：更新公式不同（`dis[v]=min(dis[v], w)` vs `dis[v]=min(dis[v], dis[u]+w)`）
5. **次小生成树**：枚举非树边替换 MST 中的边
6. **严格次小生成树**需预处理树上路径的**最大值和严格次大值**（倍增法）
7. 当替换边权 == 路径最大边权时，必须用次大值替换才能得到严格更大的生成树
8. INF 初始化需足够大（边权 1e9 × 点数 1e5 = 1e14，INF 取 1e18）
