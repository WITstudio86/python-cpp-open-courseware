/**
 * ===========================================================================
 * 课程编号：第48课
 * 课程标题：CSP-S 真题精讲（下）与考前总结
 * 对应考纲：CSP-S近年真题T3/T4分析与精讲，考试策略与心态调整
 *
 * 包含题目：
 *   T3:  树的最大权值独立集（根必须选） —— 树形DP变式，O(n)
 *         部分分解法：子集枚举（n≤20）、链状特判
 *   T4:  加权区间调度 —— DP + 数据结构（线段树/树状数组优化），O(n log n)
 *         部分分解法：O(n²) DP
 *
 * 附录：常见算法模板快速参考
 * ===========================================================================
 */

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <tuple>
#include <functional>
using namespace std;

// ============================================================================
// 快读优化
// ============================================================================
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = x * 10 + (ch ^ 48); ch = getchar(); }
    return x * f;
}

inline long long readll() {
    long long x = 0;
    int f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = x * 10 + (ch ^ 48); ch = getchar(); }
    return x * f;
}

// ============================================================================
// 题目1：树的最大权值独立集（根必须选）—— T3
// 题意：给定一棵 n 个节点的树，节点有权值 w_i。选择一个节点子集：
//       1) 任意两个被选节点不相邻（经典最大独立集约束）
//       2) 附加约束：根节点（1号节点）必须被选择
//       求最大总权值。
//
// 数据范围：
//   - Subtask 1 (20分)：n ≤ 20，可子集枚举 O(2^n)
//   - Subtask 2 (30分)：树是一条链（特殊性质），可线性DP
//   - Subtask 3 (50分)：n ≤ 10^5，树形DP O(n)
//
// 正解（树形DP）：
//   dp[u][0] = 以 u 为根的子树中，不选 u 的最大权值
//   dp[u][1] = 以 u 为根的子树中，选 u 的最大权值
//
//   转移（标准）：
//     dp[u][0] = Σ max(dp[v][0], dp[v][1])  // 不选u，儿子可选可不选
//     dp[u][1] = w[u] + Σ dp[v][0]          // 选u，所有儿子都不能选
//
//   根必须选的修改：
//     - 在计算完整个树的 DP 后，强制答案 = dp[1][1]（而不是 max(dp[1][0], dp[1][1])）
//     - 这意味着根节点必须被选，所有儿子自然不能选，但儿子的儿子可以选...
//     - 实际上 DP 本身就会正确传播这个约束：因为 dp[1][1] 的计算依赖于 dp[son][0]
//     - 但要注意：dp[1][1] 已经是考虑了"根被选"的最优解，无需额外修改
//     - 关键：如果树形 DP 是从下往上做的，根必须选意味着最终答案就是 dp[1][1]
//
//   实际上，标准的树形DP已经正确了。根必须选 → ans = dp[1][1] 即可。
// ============================================================================
namespace Problem3_TreeMaxIndependentSet {

const int MAXN = 100005;
const long long INF = 1e18;

int n;
vector<int> g[MAXN];            // 邻接表
long long w[MAXN];              // 节点权值
long long dp[MAXN][2];          // dp[u][0] 不选u, dp[u][1] 选u

// --- 树形DP（后序遍历）---
void dfs(int u, int fa) {
    dp[u][0] = 0;
    dp[u][1] = w[u];

    for (int v : g[u]) {
        if (v == fa) continue;
        dfs(v, u);
        // 不选 u：儿子 v 可选可不选
        dp[u][0] += max(dp[v][0], dp[v][1]);
        // 选 u：儿子 v 一定不能选
        dp[u][1] += dp[v][0];
    }
}

// --- 暴力解法：子集枚举（Subtask 1, n ≤ 20）---
long long brute_subset_enum(int n, const vector<long long>& wt,
                           const vector<pair<int,int>>& edges) {
    // 建立邻接矩阵便于快速判断相邻
    vector<vector<bool>> adj(n + 1, vector<bool>(n + 1, false));
    for (auto& e : edges) {
        adj[e.first][e.second] = adj[e.second][e.first] = true;
    }

    long long best = -INF;
    // 枚举所有子集
    for (int mask = 0; mask < (1 << n); mask++) {
        // 根（节点1）必须被选
        if (!(mask & 1)) continue;

        bool ok = true;
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                sum += wt[i + 1];
                // 检查与已选节点的相邻关系
                for (int j = i + 1; j < n; j++) {
                    if ((mask & (1 << j)) && adj[i + 1][j + 1]) {
                        ok = false;
                        break;
                    }
                }
                if (!ok) break;
            }
        }
        if (ok) best = max(best, sum);
    }
    return best == -INF ? -1 : best;
}

// --- 链状特判（Subtask 2, 树是一条链）---
// 链上的最大独立集（根必须选）用线性DP解决
// 思路：将链还原为线性顺序，做标准DP，强制根的位置必须选
// dp[i][0/1] = 考虑链上位置 0..i，位置 i 不选/选的最大权值
// 转移：
//   dp[i][0] = max(dp[i-1][0], dp[i-1][1])
//   dp[i][1] = dp[i-1][0] + vals[i]
// 强制根（位置 pos1）必须选 → dp[pos1][0] = -INF
long long chain_solve(int n, const vector<long long>& wt,
                      const vector<pair<int,int>>& edges) {
    // 先找出链的顺序
    vector<int> deg(n + 1, 0);
    for (auto& e : edges) {
        deg[e.first]++;
        deg[e.second]++;
    }
    int start = 1;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 1) { start = i; break; }
    }

    // DFS 获取链的线性顺序
    vector<int> order;
    vector<bool> vis(n + 1, false);
    vector<vector<int>> gg(n + 1);
    for (auto& e : edges) {
        gg[e.first].push_back(e.second);
        gg[e.second].push_back(e.first);
    }
    function<void(int)> traverse = [&](int u) {
        vis[u] = true;
        order.push_back(u);
        for (int v : gg[u]) {
            if (!vis[v]) traverse(v);
        }
    };
    traverse(start);

    // 找到根（节点1）在 order 中的位置
    int sz = order.size();
    int pos1 = -1;
    for (int i = 0; i < sz; i++) {
        if (order[i] == 1) { pos1 = i; break; }
    }

    vector<long long> vals(sz);
    for (int i = 0; i < sz; i++) vals[i] = wt[order[i]];

    // 标准线性DP：dp[i][0] 不选位置i，dp[i][1] 选位置i
    vector<vector<long long>> dp(sz, vector<long long>(2, -INF));
    dp[0][0] = 0;
    dp[0][1] = vals[0];

    // 如果根在位置0，强制 dp[0][0] = -INF
    if (pos1 == 0) dp[0][0] = -INF;

    for (int i = 1; i < sz; i++) {
        dp[i][0] = max(dp[i-1][0], dp[i-1][1]);
        // 如果上一个状态为 -INF（根被强制选了，前一位置不能选），
        // 那么 dp[i-1][1] = -INF，dp[i][1] 自然为 -INF
        dp[i][1] = dp[i-1][0] + vals[i];

        // 强制根必须选：将 dp[pos1][0] 设为 -INF
        if (i == pos1) dp[i][0] = -INF;
    }

    return max(dp[sz-1][0], dp[sz-1][1]);
}

// --- AC 正解：树形DP，O(n) ---
long long solve(int n, const vector<long long>& wt,
                const vector<pair<int,int>>& edges) {
    // 建图
    for (int i = 1; i <= n; i++) {
        g[i].clear();
        w[i] = wt[i];
    }
    for (auto& e : edges) {
        g[e.first].push_back(e.second);
        g[e.second].push_back(e.first);
    }

    dfs(1, 0);

    // 根必须选，所以取 dp[1][1]
    return dp[1][1];
}

// --- 测试入口 ---
void test() {
    cout << "====== T3：树的最大权值独立集（根必须选） ======\n";

    // 样例：5 个节点的树
    //       1(10)
    //      / | \
    //   2(5) 3(8) 4(3)
    //         |
    //        5(6)
    // 根1必须选 → 1选了，2,3,4不能选 → 5可以选
    // 总权值 = 10 + 6 = 16
    n = 5;
    vector<long long> wt = {0, 10, 5, 8, 3, 6}; // 1-indexed
    vector<pair<int,int>> edges = {{1,2}, {1,3}, {1,4}, {3,5}};

    cout << "暴力答案：" << brute_subset_enum(n, wt, edges) << "\n";
    cout << "正解答案：" << solve(n, wt, edges) << "\n";

    // 链状测试
    cout << "\n链状测试：\n";
    // 链 1-2-3-4, 权值 [10, 5, 8, 3]
    // 1必须选：只能选1和3（或1和4），但1和3相邻？1-2-3-4是链，1和3不相邻
    // 选1,3: 10+8=18, 选1,4: 10+3=13, 最大=18
    int n2 = 4;
    vector<long long> wt2 = {0, 10, 5, 8, 3};
    vector<pair<int,int>> edges2 = {{1,2}, {2,3}, {3,4}};
    cout << "链暴力答案：" << brute_subset_enum(n2, wt2, edges2) << "\n";
    cout << "链特判答案：" << chain_solve(n2, wt2, edges2) << "\n";
    cout << "正解答案(通用)：" << solve(n2, wt2, edges2) << "\n";

    // 随机测试（小数据验证正解与暴力一致）
    cout << "\n随机测试（n=12, 100组）...\n";
    srand((unsigned)time(0));
    for (int t = 0; t < 100; t++) {
        int nn = rand() % 12 + 1;
        vector<long long> ww(nn + 1);
        for (int i = 1; i <= nn; i++) ww[i] = rand() % 20 + 1;
        // 生成随机树
        vector<pair<int,int>> ee;
        for (int i = 2; i <= nn; i++) {
            int p = rand() % (i - 1) + 1;
            ee.push_back({p, i});
        }
        long long b = brute_subset_enum(nn, ww, ee);
        long long s = solve(nn, ww, ee);
        if (b != s) {
            cout << "ERROR! n=" << nn << " brute=" << b << " solve=" << s << "\n";
            return;
        }
    }
    cout << "全部通过！\n\n";
}

} // namespace Problem3_TreeMaxIndependentSet

// ============================================================================
// 题目2：加权区间调度 —— T4
// 题意：给定 n 个区间 [l_i, r_i]，每个区间有权值 w_i。
//       选择一些互不重叠的区间，使得总权值最大。
// 数据范围：
//   - Subtask 1 (30分)：n ≤ 1000, O(n²) DP
//   - Subtask 2 (70分)：n ≤ 2×10^5, O(n log n) DP + 数据结构
//
// 正解：
//   1. 将所有区间按右端点 r_i 升序排列
//   2. dp[i] = 考虑前 i 个区间（按 r 排序后），能获得的最大总权值
//   3. 对于第 i 个区间，有两种选择：
//      - 不选它：dp[i] = dp[i-1]
//      - 选它：找到右端点 < l_i 的最靠右区间 p[i]，dp[i] = dp[p[i]] + w_i
//   4. p[i] 可以通过二分查找求得：在 r 数组中找最后一个 r < l_i 的位置
//   5. 最终 dp[i] = max(dp[i-1], dp[p[i]] + w_i)
//   6. 总时间复杂度 O(n log n)
//
// 注意：dp 数组实际上是单调不降的，因此 dp[i-1] 总是 ≥ dp[i-2]
//       这也意味着我们可以使用线段树对 r 值域做 RMQ 优化，
//       但 n ≤ 2×10^5 时二分查找的方式足够优秀。
// ============================================================================
namespace Problem4_WeightedIntervalScheduling {

struct Interval {
    long long l, r;
    long long w;
    bool operator<(const Interval& other) const {
        if (r != other.r) return r < other.r;  // 按右端点升序
        return l < other.l;
    }
};

// --- 暴力 DP：O(n²)（Subtask 1）---
long long brute(int n, vector<Interval> intervals) {
    // 按右端点排序
    sort(intervals.begin(), intervals.end());
    vector<long long> dp(n, 0);
    long long ans = 0;

    for (int i = 0; i < n; i++) {
        dp[i] = intervals[i].w;
        // 找所有不与 i 重叠的 j
        for (int j = 0; j < i; j++) {
            if (intervals[j].r < intervals[i].l) {
                dp[i] = max(dp[i], dp[j] + intervals[i].w);
            }
        }
        ans = max(ans, dp[i]);
    }
    return ans;
}

// --- AC 正解：DP + 二分查找，O(n log n) ---
long long solve(int n, vector<Interval> intervals) {
    // 1. 按右端点排序
    sort(intervals.begin(), intervals.end());

    // 2. dp[i] = 考虑前 i 个区间的最大总权值（i 从 1 开始，1-indexed）
    vector<long long> dp(n + 1, 0);
    // 预存所有右端点，方便二分查找
    vector<long long> right_ends(n);
    for (int i = 0; i < n; i++) right_ends[i] = intervals[i].r;

    for (int i = 0; i < n; i++) {
        // 不选第 i 个区间
        long long skip = (i == 0) ? 0 : dp[i];  // dp[i] 即 dp[i-1] in 0-indexed

        // 选第 i 个区间：找到最后一个右端点 < l_i 的区间
        // upper_bound 找第一个 > l_i-1 的位置，减 1 即为最后一个 < l_i
        int p = upper_bound(right_ends.begin(), right_ends.end(),
                            intervals[i].l - 1) - right_ends.begin() - 1;
        long long take = intervals[i].w;
        if (p >= 0) take += dp[p + 1];  // p+1 是因为 dp 是 1-indexed

        dp[i + 1] = max(skip, take);
    }

    return dp[n];
}

// --- 测试入口 ---
void test() {
    cout << "====== T4：加权区间调度 ======\n";

    // 样例：5 个区间
    // [1,3] w=10, [2,5] w=5, [5,7] w=15, [4,8] w=20, [8,10] w=8
    // 不重叠(r_i < l_j 严格)条件下：
    // 选 [1,3](10) + [5,7](15) + [8,10](8) = 33（最优）
    // 或 [1,3](10) + [8,10](8) = 18
    // 或 [2,5](5) + [5,7](15) + [8,10](8) = 28([2,5]与[5,7]接触也算重叠，故为 5+8=13)
    // 最大 = 33
    int n = 5;
    vector<Interval> intervals = {
        {1, 3, 10},
        {2, 5, 5},
        {5, 7, 15},
        {4, 8, 20},
        {8, 10, 8}
    };

    cout << "暴力答案：" << brute(n, intervals) << "\n";
    cout << "正解答案：" << solve(n, intervals) << "\n";

    // 随机测试
    cout << "随机测试（n=10, 200组）...\n";
    srand((unsigned)time(0));
    for (int t = 0; t < 200; t++) {
        int nn = rand() % 10 + 1;
        vector<Interval> arr(nn);
        for (int i = 0; i < nn; i++) {
            arr[i].l = rand() % 20 + 1;
            arr[i].r = arr[i].l + rand() % 10 + 1;
            arr[i].w = rand() % 50 + 1;
        }
        long long b = brute(nn, arr);
        long long s = solve(nn, arr);
        if (b != s) {
            cout << "ERROR! n=" << nn << " brute=" << b << " solve=" << s << "\n";
            return;
        }
    }
    cout << "全部通过！\n\n";
}

} // namespace Problem4_WeightedIntervalScheduling

// ============================================================================
// 附录：常见算法模板快速参考
// 在考前冲刺阶段，以下模板应熟记于心
// ============================================================================

// --- 模板1：快速幂（求 a^b mod m）---
long long qpow(long long a, long long b, long long m) {
    long long res = 1;
    a %= m;
    while (b) {
        if (b & 1) res = (res * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}

// --- 模板2：最大公约数（GCD）---
long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

// --- 模板3：扩展欧几里得（求 ax + by = gcd(a,b)）---
long long exgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    long long d = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return d;
}

// --- 模板4：乘法逆元（费马小定理，m 为质数）---
long long modinv(long long a, long long m) {
    return qpow(a, m - 2, m);
}

// --- 模板5：并查集（路径压缩 + 按秩合并）---
struct DSU {
    vector<int> fa, sz;
    DSU(int n) : fa(n + 1), sz(n + 1, 1) {
        for (int i = 1; i <= n; i++) fa[i] = i;
    }
    int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
    void unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return;
        if (sz[x] < sz[y]) swap(x, y);
        fa[y] = x; sz[x] += sz[y];
    }
    bool same(int x, int y) { return find(x) == find(y); }
};

// --- 模板6：树状数组（单点修改 + 区间查询）---
template<typename T>
struct BIT {
    int n;
    vector<T> c;
    BIT(int _n) : n(_n), c(_n + 1, 0) {}
    void add(int x, T v) {
        for (; x <= n; x += x & -x) c[x] += v;
    }
    T sum(int x) {
        T s = 0;
        for (; x > 0; x -= x & -x) s += c[x];
        return s;
    }
    T range_sum(int l, int r) { return sum(r) - sum(l - 1); }
};

// --- 模板7：Dijkstra 堆优化 ---
vector<long long> dijkstra(int n, int start,
                           const vector<vector<pair<int, long long>>>& g) {
    const long long INF = 1e18;
    vector<long long> dist(n + 1, INF);
    priority_queue<pair<long long, int>,
                   vector<pair<long long, int>>,
                   greater<>> pq;
    dist[start] = 0;
    pq.push({0, start});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d != dist[u]) continue;
        for (auto [v, w] : g[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

// --- 模板8：KMP 字符串匹配 ---
vector<int> get_next(const string& p) {
    int m = p.size();
    vector<int> nxt(m);
    for (int i = 1, j = 0; i < m; i++) {
        while (j > 0 && p[i] != p[j]) j = nxt[j - 1];
        if (p[i] == p[j]) j++;
        nxt[i] = j;
    }
    return nxt;
}
vector<int> kmp_match(const string& s, const string& p) {
    vector<int> nxt = get_next(p), res;
    int n = s.size(), m = p.size();
    for (int i = 0, j = 0; i < n; i++) {
        while (j > 0 && s[i] != p[j]) j = nxt[j - 1];
        if (s[i] == p[j]) j++;
        if (j == m) { res.push_back(i - m + 1); j = nxt[j - 1]; }
    }
    return res;
}

// --- 模板9：组合数（预处理阶乘 + 逆元）---
const int MOD = 1000000007;
const int MAXC = 200005;
long long fact[MAXC], inv_fact[MAXC];

void precompute_factorials() {
    fact[0] = inv_fact[0] = 1;
    for (int i = 1; i < MAXC; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    inv_fact[MAXC - 1] = qpow(fact[MAXC - 1], MOD - 2, MOD);
    for (int i = MAXC - 2; i >= 1; i--) {
        inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD;
    }
}
long long C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}

// ============================================================================
// 主函数：运行所有题目的测试
// ============================================================================
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cout << "============================================\n";
    cout << "  第48课：CSP-S 真题精讲（下）与考前总结\n";
    cout << "  代码演示 + 算法模板快速参考\n";
    cout << "============================================\n\n";

    Problem3_TreeMaxIndependentSet::test();
    Problem4_WeightedIntervalScheduling::test();

    cout << "============================================\n";
    cout << "  算法模板已附在代码末尾，供考前速查。\n";
    cout << "  所有测试完成！\n";
    cout << "============================================\n";

    return 0;
}
