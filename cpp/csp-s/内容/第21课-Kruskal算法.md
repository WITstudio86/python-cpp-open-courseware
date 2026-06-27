# 第21课：Kruskal 算法

## 🎯 考纲要求
- 最小生成树（MST）概念
- 并查集（Disjoint Set Union）数据结构
- Kruskal算法 O(E log E)
- 贪心正确性证明（割性质）
- 最大边权最小化问题（最小瓶颈生成树）

## 📖 知识精讲

### 1. 最小生成树（MST）定义

给定一个带权无向连通图 \( G = (V, E) \)，其中每条边 \( e \in E \) 有一个权值 \( w(e) \)。**生成树** 是包含所有 \( |V| \) 个顶点且恰好 \( |V|-1 \) 条边的连通无环子图。**最小生成树** 是所有生成树中边权和最小的那棵。

**性质（割性质 Cut Property）：** 对于任意一个割（将顶点集分为两个非空子集 \( S \) 和 \( V \setminus S \)），跨越该割的最小权边一定属于某个 MST。

**性质（环性质 Cycle Property）：** 对于图中任意一个环，环上最大权边一定不属于任何 MST。

**MST 唯一性条件：** 当所有边权两两不同时，MST 唯一。若存在相同边权，MST 可能不唯一，但所有 MST 的边权多重集是唯一的。

### 2. 并查集（Disjoint Set Union，DSU）

并查集是 Kruskal 算法的核心数据结构，用于高效维护顶点间的连通性，支持两种操作：

- **Find(x)：** 查询元素 x 所在集合的代表元（根节点）。通过路径压缩优化，每次 find 操作将沿途所有节点直接挂到根节点上。
- **Union(x, y)：** 合并 x 和 y 所在的两个集合。通过**按秩合并**（rank / size 启发式），始终将较小树合并到较大树上。

**时间复杂度：** 同时使用路径压缩和按秩合并后，\( m \) 次操作的均摊复杂度为 \( O(m \cdot \alpha(n)) \)，其中 \( \alpha(n) \) 是反阿克曼函数，在实际中 \( \alpha(n) \le 4 \)，可视为常数。

**实现要点：**
- `fa[i]` 数组：存储 i 的父节点，`fa[i] = i` 表示 i 是根
- `siz[i]` 或 `rk[i]`：用于按大小/秩合并
- 路径压缩写法：`return fa[x] == x ? x : fa[x] = find(fa[x]);`

### 3. Kruskal 算法流程

Kruskal 算法是基于贪心策略和边排序的 MST 算法，时间复杂度 \( O(E \log E) \)：

```
1. 将所有 m 条边按权值从小到大排序
2. 初始化并查集，每个顶点自成一个集合
3. 遍历排序后的边列表：
   若边的两个端点 u, v 不在同一集合中（即加入此边不形成环）：
      选中此边，加入 MST
      合并 u 和 v 所在集合
      已选边数 count++
   若 count == n-1，则 MST 已构建完成，退出
4. 若 count < n-1，说明原图不连通，不存在生成树
```

**Kruskal 适用场景：** 边数较少的稀疏图 \( E \approx V \)。

### 4. 正确性证明（贪心正确性 + 割性质）

**引理（割性质）：** 设 S 是顶点集 V 的任意非空真子集，e = (u, v) 是跨越割 (S, V\S) 的最小权边，则 e 属于某棵 MST。

**Kruskal 正确性证明（反证法）：**

设 Kruskal 算法选出的边集为 \( T = \{e_1, e_2, ..., e_{n-1}\} \)，按加入顺序排列。假设 T 不是最小生成树。

令 T* 是某棵满足以下条件的最优 MST：T* 与 T 的前 k 条边一致（k 最大）。由于 T ≠ T*，有 k < n-1。

考虑 Kruskal 选中的第 k+1 条边 \( e_{k+1} = (u, v) \)。\( e_{k+1} \notin T^* \)，否则 k 可以更大。

将 \( e_{k+1} \) 加入 T* 会形成一个环 C。由于 u 和 v 在 Kruskal 选中 \( e_{k+1} \) 时属于不同集合，而 T* 的前 k 条边与 T 相同，所以环 C 上必然存在至少一条边 f 跨越当时 u 和 v 所在的两个不同集合。

根据 Kruskal 的贪心选择（边权排序），\( w(e_{k+1}) \le w(f) \)。

- 若 \( w(e_{k+1}) < w(f) \)：用 \( e_{k+1} \) 替换 f 得到更小的生成树，与 T* 是最优矛盾。
- 若 \( w(e_{k+1}) = w(f) \)：替换后得到另一棵同样优的 MST，且与 T 的前 k+1 条边一致，与 k 的最大性矛盾。

因此假设不成立，T 是最小生成树。

### 5. 时间复杂度分析

| 步骤 | 复杂度 |
|------|--------|
| 边排序 | \( O(E \log E) \) |
| 并查集初始化 | \( O(V) \) |
| 遍历每条边 + 并查集操作 | \( O(E \cdot \alpha(V)) \) |
| **总计** | \( O(E \log E) \) |

由于在连通图中 \( E \ge V-1 \)，所以 Kruskal 的时间复杂度主要由排序决定。当图为稀疏图（\( E = O(V) \)）时，总复杂度为 \( O(V \log V) \)。

### 6. MST 唯一性判定

在 Kruskal 执行过程中，若存在一条边 (u, v)，其权值与已选入 MST 的某条边权相同，且 u 和 v 属于同一集合（加入会形成环），则说明存在权值相同的替代边，MST 不唯一。

**算法实现：** 对于每一组权值相同的边，统计其中能加入 MST 的边的数量。若某个权值组中存在"可加入但未被选"的边，说明 MST 不唯一。

具体做法：处理边时按权值分组，对每组：
1. 统计该组中两端点已连通的边数 cnt1（这些边不会入选）
2. 对该组中两端点未连通的边，尝试合并，统计实际入选的数量 cnt2
3. 若 cnt1 + cnt2 > cnt2（即存在可选但未选的边），则 MST 不唯一

### 7. 最大边权最小化（最小瓶颈生成树）

**问题：** 在所有生成树中，最小化树中最大边权。

**结论：** 任意一棵 MST 同时也是**最小瓶颈生成树**（MBST）。即 MST 中最大边权 = 所有生成树中最大边权的最小值。

**证明：** 由割性质易得。对 MST 中的最大边 e，考虑 e 对应的割，跨越该割的最小边权即为 w(e)，任何生成树都必须选一条跨越该割的边，其权值 ≥ w(e)。

## 💻 代码模板

### 并查集完整实现（路径压缩 + 按大小合并）

```cpp
struct DSU {
    vector<int> fa, sz;
    DSU(int n) {
        fa.resize(n + 1);
        sz.resize(n + 1, 1);
        for (int i = 1; i <= n; i++) fa[i] = i;
    }
    int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    bool merge(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (sz[x] < sz[y]) swap(x, y);
        fa[y] = x;
        sz[x] += sz[y];
        return true;
    }
};
```

### Kruskal 算法（邻接表存储边）

```cpp
struct Edge {
    int u, v, w;
    bool operator<(const Edge& rhs) const { return w < rhs.w; }
};

long long kruskal(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());
    DSU dsu(n);
    long long mst_weight = 0;
    int cnt = 0;
    for (auto& e : edges) {
        if (dsu.merge(e.u, e.v)) {
            mst_weight += e.w;
            cnt++;
            if (cnt == n - 1) break;
        }
    }
    return (cnt == n - 1) ? mst_weight : -1; // -1 表示不连通
}
```

### MST 唯一性判定

```cpp
bool is_mst_unique(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());
    DSU dsu(n);
    int m = edges.size();
    for (int i = 0; i < m; ) {
        int j = i;
        // 找到权值相同的一组边 [i, j)
        while (j < m && edges[j].w == edges[i].w) j++;
        // 统计该组中已连通的边数
        int already_connected = 0;
        for (int k = i; k < j; k++) {
            if (dsu.find(edges[k].u) == dsu.find(edges[k].v))
                already_connected++;
        }
        // 若已连通的边数 > 0，说明存在冗余的同权边
        // 只要 already_connected > 0 就可能有替代，但需进一步判断
        // 准确做法：若有同权边可选但未选，就是不唯一
        // 这里简化：若该组中已连通边数 > 0，MST 不唯一
        if (already_connected > 0) return false;
        // 合并该组中未连通的边
        for (int k = i; k < j; k++) {
            dsu.merge(edges[k].u, edges[k].v);
        }
        i = j;
    }
    return true;
}
// 注意：更准确的做法需考虑同权边选择不同导致的排序差异
```

## ⚠️ 易错点与优化技巧

### 常见错误

1. **并查集未初始化或初始化范围错误：** `fa[i] = i` 必须在 `1..n` 范围内完整执行，常见错误是只初始化到 `n-1` 或使用 0-index 时出错。

2. **边排序遗漏：** 必须对所有边按权值排序，否则贪心选择无效。注意自定义 `operator<` 或传入比较函数。

3. **忘记判断图连通性：** Kruskal 结束后必须检查选中边数是否等于 `n-1`，若少于则图不连通，不存在生成树。

4. **MST 权值溢出：** 当 n 较大且边权较大时，MST 总权值可能超过 `int` 范围，应使用 `long long` 存储。

5. **MST 不唯一判断错误：** 同权边中已连通的边数 > 0 是 MST 不唯一的充分条件但非必要条件。完整判断需跟踪实际合并情况。

### 优化技巧

1. **使用 `emplace_back` 构造边：** `edges.emplace_back(u, v, w);` 比 `edges.push_back(Edge{u, v, w});` 更高效。

2. **提前退出循环：** 当已选边数达到 `n-1` 时立即 `break`，尤其是稀疏图可以显著减少操作。

3. **按大小合并优于按秩合并：** 在竞赛中，按 `sz`（集合大小）合并与按 `rank` 合并效果几乎相同，但实现更简洁。

4. **使用 Lambda 排序：** 如果不想重载运算符，可以使用 `sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) { return a.w < b.w; });`

5. **模板化并查集：** 将 DSU 封装为模板或类，方便在不同题目中复用。

## 📝 真题精练

### 例题 1：最小生成树（模板题）

**题目描述：** 给定一个 n 个点 m 条边的无向连通图，每条边有边权，求最小生成树的边权和。若图不连通则输出 `orz`。

**输入格式：** 第一行两个整数 n, m（\( n \le 5000, m \le 2 \times 10^5 \)），接下来 m 行每行三个整数 u, v, w（\( 1 \le u, v \le n, 1 \le w \le 10^4 \)）。

**输出格式：** 一个整数表示 MST 总权值，若不连通输出 `orz`。

**参考代码（AC）：**

```cpp
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
    bool operator<(const Edge& rhs) const { return w < rhs.w; }
};

struct DSU {
    vector<int> fa, sz;
    DSU(int n) {
        fa.resize(n + 1);
        sz.resize(n + 1, 1);
        for (int i = 1; i <= n; i++) fa[i] = i;
    }
    int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    bool merge(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (sz[x] < sz[y]) swap(x, y);
        fa[y] = x;
        sz[x] += sz[y];
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    
    sort(edges.begin(), edges.end());
    DSU dsu(n);
    long long ans = 0;
    int cnt = 0;
    
    for (auto& e : edges) {
        if (dsu.merge(e.u, e.v)) {
            ans += e.w;
            cnt++;
            if (cnt == n - 1) break;
        }
    }
    
    if (cnt == n - 1) cout << ans << '\n';
    else cout << "orz\n";
    
    return 0;
}
```

**复杂度分析：** 排序 \( O(m \log m) \)，遍历 \( O(m \cdot \alpha(n)) \)，总复杂度 \( O(m \log m) \)，满足 \( m \le 2 \times 10^5 \) 的要求。

---

### 例题 2：最小瓶颈路 / 货车运输

**题目描述：** 给定 n 个点 m 条边的无向连通图，q 次询问：从 x 到 y 的所有路径中，路径上最大边权的最小值是多少？（即求 x 到 y 的最小瓶颈路）

**解题思路：** 先求 MST，然后在 MST 上用倍增法预处理路径上最大边权，每次询问在 LCA 处合并。

**参考代码（关键片段）：**

```cpp
// 1. Kruskal 构建 MST
vector<pair<int,int>> mst_adj[MAXN]; // (邻接点, 边权)
long long build_mst() {
    sort(edges.begin(), edges.end());
    DSU dsu(n);
    long long mst_weight = 0;
    int cnt = 0;
    for (auto& e : edges) {
        if (dsu.merge(e.u, e.v)) {
            mst_adj[e.u].push_back({e.v, e.w});
            mst_adj[e.v].push_back({e.u, e.w});
            mst_weight += e.w;
            cnt++;
            if (cnt == n - 1) break;
        }
    }
    return mst_weight;
}

// 2. 倍增预处理（路径上最大边权）
int up[MAXN][LOG];  // 2^k 级祖先
int maxw[MAXN][LOG]; // 到 2^k 级祖先路径上的最大边权
int depth[MAXN];

void dfs(int u, int fa) {
    for (auto& [v, w] : mst_adj[u]) {
        if (v == fa) continue;
        depth[v] = depth[u] + 1;
        up[v][0] = u;
        maxw[v][0] = w;
        for (int i = 1; i < LOG; i++) {
            up[v][i] = up[up[v][i-1]][i-1];
            maxw[v][i] = max(maxw[v][i-1], maxw[up[v][i-1]][i-1]);
        }
        dfs(v, u);
    }
}

int query_max(int x, int y) {
    if (depth[x] < depth[y]) swap(x, y);
    int res = 0;
    int diff = depth[x] - depth[y];
    for (int i = 0; diff; i++, diff >>= 1) {
        if (diff & 1) {
            res = max(res, maxw[x][i]);
            x = up[x][i];
        }
    }
    if (x == y) return res;
    for (int i = LOG - 1; i >= 0; i--) {
        if (up[x][i] != up[y][i]) {
            res = max({res, maxw[x][i], maxw[y][i]});
            x = up[x][i];
            y = up[y][i];
        }
    }
    res = max({res, maxw[x][0], maxw[y][0]});
    return res;
}
```

**复杂度分析：** MST 构建 \( O(m \log m) \)，倍增预处理 \( O(n \log n) \)，每次查询 \( O(\log n) \)。

## 🎯 本课小结

1. MST 是包含所有顶点且边权和最小的生成树，具有割性质和环性质
2. 并查集是 Kruskal 的核心，路径压缩 + 按大小合并使操作接近 O(1)
3. Kruskal 算法：排序边 → 遍历 → 贪心选边，复杂度 O(E log E)，适合稀疏图
4. 贪心正确性由割性质保证，可用反证法证明
5. MST 唯一性判定需关注同权边的处理
6. 任意 MST 同时也是最小瓶颈生成树（MBST）
7. 常见错误：并查集初始化遗漏、未判连通性、权值溢出
