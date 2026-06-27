/**
 * ===========================================================================
 * 课程编号：第47课
 * 课程标题：CSP-S 真题精讲（上）
 * 对应考纲：CSP-S近年真题T1/T2分析与精讲，题型归纳与得分策略
 *
 * 包含题目：
 *   T1-1: 零和子数组 —— 前缀和 + 哈希表，O(n)
 *         暴力对照：O(n²) 枚举所有子数组
 *   T1-2: 最优任务调度 —— 反悔贪心 + 最小堆，O(n log n)
 *         暴力对照：O(2^n) 子集枚举
 *   T2-1: 分割数组的最小最大段和 —— 二分答案 + 贪心判定，O(n log sum)
 *         暴力对照：O(n²k) DP
 *   T2-2: K 步最短路径 —— 分层图 DP / Bellman-Ford 变式，O(k·m)
 *         暴力对照：O(n^k) DFS 枚举
 *
 * 快读优化：针对大规模输入使用 inline 快读函数
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
// 题目1：零和子数组（T1-1）
// 题意：给定长度为 n 的整数数组，求有多少个连续子数组的和为 0
// 数据范围：1 ≤ n ≤ 2×10^5，|a_i| ≤ 10^9
//
// 暴力解法 O(n²)：枚举所有子数组 [l, r]，计算区间和
//   - 通过率：30%（n ≤ 1000 的测试点）
//   - 思路：两重循环枚举左右端点，内层累加求和
//
// 正解 O(n)：前缀和 + 哈希表
//   - 通过率：100%
//   - 核心观察：a[l..r] 的和为 0 ⟺ prefix[r] == prefix[l-1]
//   - 其中 prefix[i] = a[1] + a[2] + ... + a[i]，prefix[0] = 0
//   - 问题转化为：统计 prefix[0..n] 中每种值出现的次数
//   - 对出现 cnt 次的值，贡献 C(cnt, 2) = cnt * (cnt - 1) / 2
//   - 使用 unordered_map<long long, int> 记录每种前缀和的出现次数
// ============================================================================
namespace Problem1_ZeroSumSubarrays {

// --- 暴力解法 ---
long long brute(int n, const vector<long long>& a) {
    long long ans = 0;
    for (int l = 0; l < n; l++) {
        long long sum = 0;
        for (int r = l; r < n; r++) {
            sum += a[r];
            if (sum == 0) ans++;
        }
    }
    return ans;
}

// --- AC 正解 ---
long long solve(int n, const vector<long long>& a) {
    unordered_map<long long, int> cnt;  // 前缀和 → 出现次数
    cnt[0] = 1;  // prefix[0] = 0（空前缀）
    long long prefix = 0;
    long long ans = 0;

    for (int i = 0; i < n; i++) {
        prefix += a[i];
        // 如果 prefix 之前出现过 cnt[prefix] 次
        // 那么有 cnt[prefix] 个 j (j < i) 满足 prefix[j] == prefix[i]
        // 即 a[j+1..i] 的和为 0
        ans += cnt[prefix];
        cnt[prefix]++;
    }
    return ans;
}

// --- 测试入口 ---
void test() {
    cout << "====== T1-1：零和子数组 ======\n";
    // 样例：2 -2 3 -3 → 前缀和序列：0, 2, 0, 3, 0
    // 0 出现 3 次 → C(3,2) = 3 个子数组：[1,2](2-2=0), [3,4](3-3=0), [1,4](2-2+3-3=0)
    vector<long long> a = {2, -2, 3, -3};
    int n = a.size();
    cout << "数组：";
    for (auto x : a) cout << x << " ";
    cout << "\n";
    cout << "暴力答案：" << brute(n, a) << "\n";
    cout << "正解答案：" << solve(n, a) << "\n";

    // 大数据随机测试：验证暴力与正解的一致性
    cout << "随机测试（n = 200, 100 组）...\n";
    srand((unsigned)time(0));
    for (int t = 0; t < 100; t++) {
        int nn = rand() % 200 + 1;
        vector<long long> arr(nn);
        for (int i = 0; i < nn; i++) arr[i] = (rand() % 21) - 10; // [-10, 10]
        long long b = brute(nn, arr);
        long long s = solve(nn, arr);
        if (b != s) {
            cout << "ERROR! brute=" << b << " solve=" << s << "\n";
            return;
        }
    }
    cout << "全部通过！\n\n";
}

} // namespace Problem1_ZeroSumSubarrays

// ============================================================================
// 题目2：最优任务调度（T1-2）
// 题意：n 个任务，每个任务需 1 单位时间，截止时间 d_i，收益 v_i
//       选择并安排任务，使总收益最大
// 数据范围：1 ≤ n ≤ 10^5，1 ≤ d_i ≤ 10^9，1 ≤ v_i ≤ 10^9
//
// 暴力解法 O(2^n · n)：子集枚举
//   - 通过率：20%（n ≤ 15 的测试点）
//   - 思路：枚举所有 2^n 种选法，按 deadline 排序验证可行性
//
// 正解 O(n log n)：反悔贪心（带撤销的贪心） + 最小堆
//   - 通过率：100%
//   - 核心思路：
//     1. 将所有任务按截止时间 d_i 升序排列
//     2. 遍历任务，使用最小堆（priority_queue）维护已选任务的收益
//     3. 将当前任务收益加入堆
//     4. 若堆大小 > 当前截止时间：说明安排了太多任务，弹出堆顶（最小收益的任务）
//   - 最终堆中所有收益之和即为最大总收益
//   - 正确性：按 deadline 排序后，在任何前缀中选 ≤ d_i 个任务是最优的
// ============================================================================
namespace Problem2_OptimalTaskScheduling {

struct Task {
    long long deadline;
    long long value;
    bool operator<(const Task& other) const {
        return deadline < other.deadline;  // 按截止时间升序
    }
};

// --- 暴力解法：子集枚举，O(2^n · n) ---
long long brute(int n, const vector<Task>& tasks) {
    long long best = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<Task> selected;
        long long total = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                selected.push_back(tasks[i]);
                total += tasks[i].value;
            }
        }
        // 按 deadline 排序
        sort(selected.begin(), selected.end());
        bool ok = true;
        for (int i = 0; i < (int)selected.size(); i++) {
            // 第 i 个被选任务安排在时间 i+1
            if (selected[i].deadline < (long long)(i + 1)) {
                ok = false;
                break;
            }
        }
        if (ok) best = max(best, total);
    }
    return best;
}

// --- AC 正解：反悔贪心 + 最小堆，O(n log n) ---
long long solve(int n, vector<Task> tasks) {
    // 1. 按截止时间升序排序
    sort(tasks.begin(), tasks.end());

    // 2. 最小堆（存储已选任务的收益）
    priority_queue<long long, vector<long long>, greater<long long>> pq;

    for (const auto& t : tasks) {
        pq.push(t.value);
        // 如果已选任务数 > 当前截止时间，说明安排了太多任务
        // 反悔掉收益最小的任务
        if ((long long)pq.size() > t.deadline) {
            pq.pop();
        }
    }

    // 3. 累加堆中所有收益
    long long ans = 0;
    while (!pq.empty()) {
        ans += pq.top();
        pq.pop();
    }
    return ans;
}

// --- 测试入口 ---
void test() {
    cout << "====== T1-2：最优任务调度 ======\n";
    // 样例：
    // 4 个任务：(3,10), (1,5), (2,6), (2,7)
    // 最优：时刻1做收益5，时刻2做收益7，时刻3做收益10 → 总收益22
    // 实际应该输出23（上面分析错了，让我重新算）
    //
    // 任务：(1,5), (2,6), (2,7), (3,10) 按deadline排序后
    // deadline=1: 选5, pq=[5], size=1
    // deadline=2: 选6, pq=[5,6], size=2
    // deadline=2: 选7, pq=[5,6,7], size=3 > 2, pop 5 → pq=[6,7]
    // deadline=3: 选10, pq=[6,7,10], size=3
    // 总收益 = 23
    // 验证：时刻1做5，时刻2做7，时刻3做10 → 但5被踢掉了
    // 实际安排：时刻1做6，时刻2做7，时刻3做10 = 23
    // 或：时刻1做5，时刻2做6，时刻3做10 = 21（但7>6，踢5保留7更优）
    // 总之答案=23
    vector<Task> tasks = {{3, 10}, {1, 5}, {2, 6}, {2, 7}};
    int n = tasks.size();
    cout << "暴力答案：" << brute(n, tasks) << "\n";
    cout << "正解答案：" << solve(n, tasks) << "\n";

    // 随机测试
    cout << "随机测试（n = 12, 200 组）...\n";
    srand((unsigned)time(0));
    for (int t = 0; t < 200; t++) {
        int nn = rand() % 12 + 1;
        vector<Task> arr(nn);
        for (int i = 0; i < nn; i++) {
            arr[i].deadline = rand() % (nn + 1) + 1;
            arr[i].value = rand() % 100 + 1;
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

} // namespace Problem2_OptimalTaskScheduling

// ============================================================================
// 题目3：分割数组的最小最大段和（T2-1）
// 题意：将 n 个正整数的数组划分为最多 k 个连续段，最小化最大段和
// 数据范围：1 ≤ n ≤ 10^5，1 ≤ k ≤ n，1 ≤ a_i ≤ 10^9
//
// 暴力解法 O(n²k)：DP
//   - 通过率：30%（n ≤ 100 的测试点）
//   - 思路：dp[i][j] = 前 i 个元素划分为 j 段的最小最大段和
//
// 正解 O(n log sum)：二分答案 + 贪心判定
//   - 通过率：100%
//   - 单调性：若 X 可行（可划分为 ≤ k 段，每段和 ≤ X），则 X' > X 也可行
//   - 判定函数 check(X)：贪心从左到右切分，段和超过 X 时新开一段
//   - 二分范围：max(a_i) ~ sum(a_i)
// ============================================================================
namespace Problem3_MinimizeMaxSegmentSum {

// --- 暴力解法 DP：O(n²k) ---
// dp[i][j] = 将前 i 个元素分成 j 段的最大段和的最小值
// dp[i][j] = min_{t < i} max(dp[t][j-1], sum[t+1..i])
const long long INF = 1e18;

long long brute(int n, int k, const vector<long long>& a) {
    vector<long long> prefix(n + 1, 0);
    for (int i = 1; i <= n; i++) prefix[i] = prefix[i - 1] + a[i - 1];

    // dp[i][j]：前 i 个元素分 j 段
    vector<vector<long long>> dp(n + 1, vector<long long>(k + 1, INF));
    dp[0][0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= min(i, k); j++) {
            for (int t = 0; t < i; t++) {
                if (dp[t][j - 1] != INF) {
                    long long seg_sum = prefix[i] - prefix[t];
                    long long val = max(dp[t][j - 1], seg_sum);
                    dp[i][j] = min(dp[i][j], val);
                }
            }
        }
    }
    return dp[n][k];
}

// --- AC 正解：二分答案 + 贪心判定，O(n log sum) ---
// 判定：在每段和 ≤ limit 的前提下，最少需要多少段？
int count_segments(int n, const vector<long long>& a, long long limit) {
    int segs = 1;
    long long cur_sum = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > limit) return n + 1;  // 单个元素就超限，不可能
        if (cur_sum + a[i] > limit) {
            segs++;
            cur_sum = a[i];
        } else {
            cur_sum += a[i];
        }
    }
    return segs;
}

long long solve(int n, int k, const vector<long long>& a) {
    long long L = 0, R = 0;
    for (auto x : a) {
        L = max(L, x);  // 下界：最大元素值
        R += x;          // 上界：所有元素之和
    }

    long long ans = R;
    while (L <= R) {
        long long mid = L + (R - L) / 2;
        if (count_segments(n, a, mid) <= k) {
            ans = mid;
            R = mid - 1;  // 尝试更小的最大段和
        } else {
            L = mid + 1;  // 段数太多，需要更大的允许段和
        }
    }
    return ans;
}

// --- 测试入口 ---
void test() {
    cout << "====== T2-1：分割数组的最小最大段和 ======\n";
    vector<long long> a = {7, 2, 5, 10, 8};
    int n = a.size(), k = 3;
    cout << "数组：";
    for (auto x : a) cout << x << " ";
    cout << "\nk = " << k << "\n";
    cout << "暴力答案：" << brute(n, k, a) << "\n";
    cout << "正解答案：" << solve(n, k, a) << "\n";

    // 随机测试（小数据验证暴力与正解一致）
    cout << "随机测试（n = 10, 100 组）...\n";
    srand((unsigned)time(0));
    for (int t = 0; t < 100; t++) {
        int nn = rand() % 10 + 1;
        int kk = rand() % nn + 1;
        vector<long long> arr(nn);
        for (int i = 0; i < nn; i++) arr[i] = rand() % 20 + 1;
        long long b = brute(nn, kk, arr);
        long long s = solve(nn, kk, arr);
        if (b != s) {
            cout << "ERROR! b=" << b << " s=" << s << "\n";
            return;
        }
    }
    cout << "全部通过！\n\n";
}

} // namespace Problem3_MinimizeMaxSegmentSum

// ============================================================================
// 题目4：K 步最短路径（T2-2）
// 题意：有向图中，求从 1 到 n 恰好经过 k 条边的最短路径
// 数据范围：1 ≤ n ≤ 1000，1 ≤ m ≤ 10000，1 ≤ k ≤ 100，1 ≤ w ≤ 1000
//
// 暴力解法 O(n^k)：DFS 枚举所有恰好 k 条边的路径
//   - 通过率：30%（n ≤ 10, k ≤ 5 的测试点）
//
// 正解 O(k·m)：分层图 DP
//   - 通过率：100%
//   - 状态：dp[e][v] = 从 1 出发恰好经过 e 条边到达 v 的最小总权值
//   - 初始化：dp[0][1] = 0, dp[0][v] = INF (v != 1)
//   - 转移：对每条边 (u,v,w)，dp[e][v] = min(dp[e][v], dp[e-1][u] + w)
//   - 答案：dp[k][n]（若 = INF 则输出 -1）
// ============================================================================
namespace Problem4_KStepShortestPath {

const long long INF = 1e18;

// 边结构体
struct Edge {
    int to;
    int weight;
};

// --- 暴力解法：DFS 枚举所有 k 步路径，O(V * (out_degree)^k) ---
long long brute_dfs(int u, int target, int remaining,
                    const vector<vector<Edge>>& g) {
    if (remaining == 0) {
        return (u == target) ? 0 : INF;
    }
    long long best = INF;
    for (const auto& e : g[u]) {
        long long sub = brute_dfs(e.to, target, remaining - 1, g);
        if (sub != INF) {
            best = min(best, sub + e.weight);
        }
    }
    return best;
}

long long brute(int n, int k, const vector<vector<Edge>>& g) {
    long long ans = brute_dfs(1, n, k, g);
    return ans == INF ? -1 : ans;
}

// --- AC 正解：分层 DP，O(k·m) ---
long long solve(int n, int m, int k, const vector<tuple<int,int,int>>& edges) {
    // dp[step][node]
    vector<vector<long long>> dp(k + 1, vector<long long>(n + 1, INF));
    dp[0][1] = 0;

    for (int e = 1; e <= k; e++) {
        for (const auto& [u, v, w] : edges) {
            if (dp[e - 1][u] != INF) {
                dp[e][v] = min(dp[e][v], dp[e - 1][u] + w);
            }
        }
    }

    return (dp[k][n] == INF) ? -1 : dp[k][n];
}

// --- 测试入口 ---
void test() {
    cout << "====== T2-2：K 步最短路径 ======\n";
    // 样例：4 个节点，5 条边，k=3
    // 1→2(1), 2→3(2), 3→4(3), 1→3(5), 2→4(10)
    // 最优路径：1→2→3→4，总权值 = 1+2+3 = 6
    int n = 4, m = 5, k = 3;
    vector<tuple<int,int,int>> edges = {
        {1, 2, 1}, {2, 3, 2}, {3, 4, 3},
        {1, 3, 5}, {2, 4, 10}
    };
    vector<vector<Problem4_KStepShortestPath::Edge>> g(n + 1);
    for (auto& [u, v, w] : edges) {
        g[u].push_back({v, w});
    }

    cout << "暴力答案：" << brute(n, k, g) << "\n";
    cout << "正解答案：" << solve(n, m, k, edges) << "\n";

    // 随机测试
    cout << "随机测试（n=6, m=15, k=4, 100 组）...\n";
    srand((unsigned)time(0));
    for (int t = 0; t < 100; t++) {
        int nn = rand() % 6 + 2;
        int mm = rand() % 15 + 1;
        int kk = rand() % 4 + 1;
        vector<tuple<int,int,int>> e_list;
        vector<vector<Problem4_KStepShortestPath::Edge>> gg(nn + 1);
        for (int i = 0; i < mm; i++) {
            int u = rand() % nn + 1;
            int v = rand() % nn + 1;
            int w = rand() % 10 + 1;
            e_list.push_back({u, v, w});
            gg[u].push_back({v, w});
        }
        long long b = brute(nn, kk, gg);
        long long s = solve(nn, mm, kk, e_list);
        if (b != s) {
            cout << "ERROR! n=" << nn << " m=" << mm << " k=" << kk
                 << " brute=" << b << " solve=" << s << "\n";
            return;
        }
    }
    cout << "全部通过！\n\n";
}

} // namespace Problem4_KStepShortestPath

// ============================================================================
// 主函数：运行所有题目的测试
// ============================================================================
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cout << "============================================\n";
    cout << "  第47课：CSP-S 真题精讲（上）—— 代码演示\n";
    cout << "============================================\n\n";

    Problem1_ZeroSumSubarrays::test();
    Problem2_OptimalTaskScheduling::test();
    Problem3_MinimizeMaxSegmentSum::test();
    Problem4_KStepShortestPath::test();

    cout << "============================================\n";
    cout << "  所有测试完成！\n";
    cout << "============================================\n";

    return 0;
}
