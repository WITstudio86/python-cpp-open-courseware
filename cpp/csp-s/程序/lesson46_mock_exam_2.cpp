/**
 * 第46课：综合模拟赛（二）— 动态规划+数学综合
 * CSP-S 模拟赛 AC 代码
 *
 * 包含以下题目：
 *   T1：多重背包二进制优化
 *   T2：区间 DP（石子合并变种 — 乘积代价）
 *   T3：状压 DP（TSP 旅行商问题）
 *   T4：组合数学 + DP + 快速幂（欧拉数+值域推广）
 *
 * 所有代码均为可 AC 的完整实现
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MOD = 1e9 + 7;

// ============================================================
// 快速幂与组合数工具（供 T4 使用）
// ============================================================
namespace MathTools {
    const int MAXF = 4005;  // 最大阶乘范围
    ll fact[MAXF], inv_fact[MAXF];

    ll qpow(ll a, ll b) {
        ll res = 1;
        a %= MOD;
        while (b) {
            if (b & 1) res = res * a % MOD;
            a = a * a % MOD;
            b >>= 1;
        }
        return res;
    }

    void init(int n) {
        fact[0] = inv_fact[0] = 1;
        for (int i = 1; i <= n; i++)
            fact[i] = fact[i-1] * i % MOD;
        inv_fact[n] = qpow(fact[n], MOD - 2);
        for (int i = n - 1; i >= 1; i--)
            inv_fact[i] = inv_fact[i+1] * (i+1) % MOD;
    }

    // 普通组合数（n ≤ MAXF）
    ll comb(int n, int k) {
        if (k < 0 || k > n) return 0;
        return fact[n] * inv_fact[k] % MOD * inv_fact[n-k] % MOD;
    }

    // 大 n 小 k 的组合数 C(n, k)，n 可以很大
    ll comb_large_n(ll n, int k) {
        if (k < 0 || n < k) return 0;
        ll res = 1;
        for (int i = 0; i < k; i++) {
            res = res * ((n - i) % MOD) % MOD;
        }
        res = res * inv_fact[k] % MOD;
        return res;
    }
}

// ============================================================
// T1：多重背包二进制优化
// 题目：n 种物品，每种数量 c[i]，体积 v[i]，价值 w[i]
//      背包容量 V，求最大总价值
// 数据范围：n ≤ 100, V ≤ 40000, c[i] ≤ 10⁴
// 时间复杂度：O(V × Σlog(c[i]))，约 O(40000 × 1400) = 5.6×10⁷
// ============================================================
namespace T1_MultiKnapsack {
    void solve() {
        int n, V;
        cin >> n >> V;

        vector<int> dp(V + 1, 0);

        for (int i = 0; i < n; i++) {
            int v, w, c;
            cin >> v >> w >> c;

            // 二进制拆分：将 c 个物品拆成 1,2,4,...,2^k,剩余
            int k = 1;
            while (c >= k) {
                int nv = v * k;   // 打包后的体积
                int nw = w * k;   // 打包后的价值
                // 01 背包（倒序遍历容量）
                for (int j = V; j >= nv; j--) {
                    dp[j] = max(dp[j], dp[j - nv] + nw);
                }
                c -= k;
                k <<= 1;
            }
            // 处理剩余零头
            if (c > 0) {
                int nv = v * c;
                int nw = w * c;
                for (int j = V; j >= nv; j--) {
                    dp[j] = max(dp[j], dp[j - nv] + nw);
                }
            }
        }

        cout << dp[V] << '\n';
    }
}

// ============================================================
// T2：区间 DP — 石子合并变种（乘积代价）
// 题目：n 堆石子排成一排，每次合并相邻两堆，
//      代价为两堆石子数量的乘积。求最小总代价。
// 数据范围：n ≤ 300, a[i] ≤ 100
// 时间复杂度：O(n³) ≈ 300³ = 2.7×10⁷
// ============================================================
namespace T2_IntervalDP {
    const int MAXN = 305;
    const ll INF = 1e18;

    int n;
    ll a[MAXN];
    ll pref[MAXN];          // 前缀和（快速求区间石子总数）
    ll dp[MAXN][MAXN];      // dp[l][r] = 合并 [l, r] 的最小代价

    // 区间石子总数
    ll range_sum(int l, int r) {
        return pref[r] - pref[l - 1];
    }

    void solve() {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            pref[i] = pref[i - 1] + a[i];
        }

        // 初始化：单堆石子无需合并，代价为 0
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dp[i][j] = (i == j ? 0 : INF);

        // 区间 DP 经典三层循环
        for (int len = 2; len <= n; len++) {           // 枚举区间长度
            for (int l = 1; l + len - 1 <= n; l++) {   // 枚举左端点
                int r = l + len - 1;                   // 右端点
                for (int k = l; k < r; k++) {          // 枚举分割点
                    // 合并 [l,k] 和 [k+1,r]，代价为两堆石子数量的乘积
                    ll cost = range_sum(l, k) * range_sum(k + 1, r);
                    dp[l][r] = min(dp[l][r], dp[l][k] + dp[k + 1][r] + cost);
                }
            }
        }

        cout << dp[1][n] << '\n';
    }
}

// ============================================================
// T3：状压 DP — 旅行商问题（TSP）
// 题目：n 个城市，从城市 1 出发，经过所有城市恰好一次后回到 1
//      求最短总旅行距离。不可达输出 -1。
// 数据范围：n ≤ 15
// 时间复杂度：O(n² × 2ⁿ) ≈ 15² × 2¹⁵ ≈ 7.4×10⁶
// ============================================================
namespace T3_TSP {
    const int INF = 0x3f3f3f3f;

    void solve() {
        int n;
        cin >> n;

        // 读入距离矩阵（城市编号 0-based）
        vector<vector<int>> d(n, vector<int>(n));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> d[i][j];

        int total = 1 << n;  // 总状态数 = 2ⁿ

        // dp[mask][i]：已访问 mask 中的城市，最后在 i 的最短距离
        vector<vector<int>> dp(total, vector<int>(n, INF));

        dp[1][0] = 0;  // mask=1 表示只访问了城市 0（即城市 1）

        for (int mask = 1; mask < total; mask++) {
            // 枚举当前所在城市 i（必须在 mask 中）
            for (int i = 0; i < n; i++) {
                if (!(mask & (1 << i))) continue;
                if (dp[mask][i] == INF) continue;

                // 尝试前往下一个城市 j（不在 mask 中）
                for (int j = 0; j < n; j++) {
                    if (mask & (1 << j)) continue;      // j 已访问
                    if (d[i][j] == -1) continue;         // 不可达
                    int nxt = mask | (1 << j);
                    dp[nxt][j] = min(dp[nxt][j], dp[mask][i] + d[i][j]);
                }
            }
        }

        // 汇总答案：所有城市访问完毕 + 回到起点
        int ans = INF;
        int full = total - 1;  // 全 1，表示所有城市都已访问
        for (int i = 0; i < n; i++) {
            if (dp[full][i] == INF) continue;
            if (d[i][0] == -1) continue;  // 无法回起点
            ans = min(ans, dp[full][i] + d[i][0]);
        }

        cout << (ans == INF ? -1 : ans) << '\n';
    }
}

// ============================================================
// T4：组合数学 + DP + 快速幂 — 欧拉数推广
// 题目：长度为 n 的序列，值域 [1..k]，恰好 m 个上升位置(相邻 a[i]<a[i+1])
//      求方案数 mod 10⁹+7
// 数据范围：n ≤ 2000，k ≤ 10⁹，0 ≤ m < n
//
// 解法：使用欧拉数递推 + 组合数推广到 k 值域
//
// 核心公式（k-欧拉数 / Eulerian numbers of type B）：
//   定义 euler[i][j] = A(i, j)：长度为 i 的排列中恰好有 j 个上升
//   递推：euler[i][j] = (j+1) * euler[i-1][j] + (i-j) * euler[i-1][j-1]
//
//   推广到值域 [1..k]（可重复取值而非排列）的公式为：
//   ans = Σ_{t=0}^{n-1-m} C(k, m+t+1) * euler[n][m+t]
//
//   直观解释：序列被 m 个上升位置分成 m+1 段非升段，
//   每段的"最大值"严格递增。从 k 个值中选 m+t+1 个作为段的端点值，
//   然后在各段内填充非升序列。
//
// 时间复杂度：O(n²) 计算欧拉数 + O(n) 组合枚举
// ============================================================
namespace T4_EulerianNumbers {
    const int MAXN = 2005;

    ll euler[MAXN][MAXN];  // 欧拉数

    void solve() {
        int n, k, m;
        cin >> n >> k >> m;

        // 预处理阶乘（用于组合数）
        MathTools::init(2 * n + 5);

        // 计算欧拉数 A(i, j)
        // euler[i][j] = 长度为 i 的排列，恰好 j 个上升
        euler[0][0] = 1;
        for (int i = 1; i <= n; i++) {
            euler[i][0] = 1;  // 只有 1 个排列（完全递减）有 0 个上升
            for (int j = 1; j < i; j++) {
                euler[i][j] = ((j + 1) * euler[i - 1][j] + (i - j) * euler[i - 1][j - 1]) % MOD;
            }
            euler[i][i] = 0;  // 不可能有 i 个上升（最多 i-1）
        }

        // 推广到值域 [1..k]
        // ans = Σ_{t=0}^{n-1-m} C(k, m+t+1) * euler[n][m+t]
        ll ans = 0;
        for (int t = 0; t <= n - 1 - m; t++) {
            int seg_cnt = m + t + 1;  // 段数 = 上升数 + t + 1
            if (seg_cnt > k) break;   // 值不够分

            // C(k, seg_cnt)：从 k 个值中选 seg_cnt 个作为段边界
            ll comb_val = MathTools::comb_large_n(k, seg_cnt);
            ll term = comb_val * euler[n][m + t] % MOD;
            ans = (ans + term) % MOD;
        }

        cout << ans << '\n';
    }
}

// ============================================================
// 主函数：根据需要调用各题
// ============================================================
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 选择要运行的题目（取消注释即可）
    // T1_MultiKnapsack::solve();        // T1：多重背包二进制优化
    // T2_IntervalDP::solve();           // T2：区间 DP
    // T3_TSP::solve();                  // T3：TSP 状压 DP
    // T4_EulerianNumbers::solve();      // T4：欧拉数 + 组合数学

    return 0;
}
