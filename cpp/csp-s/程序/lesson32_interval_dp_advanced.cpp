/*
 * 第32课：区间DP进阶
 * 考纲知识点：环形区间DP（破环成链×2）、能量项链、合并型与消去型区间DP、四边形不等式优化
 *
 * 本文件包含：
 *   1. 环形石子合并（破环成链 ×2）- 最小值和最大值
 *   2. 能量项链（NOIP2006 提高组）
 *   3. 消去型区间DP示例
 *   4. 四边形不等式优化版本（石子合并）
 *   5. 真题1：环形石子合并【洛谷 P1880】
 *   6. 真题2：能量项链【洛谷 P1063】
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

const int INF = 0x3f3f3f3f;

// ==================== 1. 环形石子合并（破环成链 ×2） ====================
// 技巧：将原序列复制一份接到尾部，得到长度为2n的序列
// 在2n的序列上做区间DP，最终答案遍历所有长度为n的区间

// 环形石子合并 - 最小代价
int circular_merge_stones_min(const vector<int>& a) {
    int n = a.size();
    // 破环成链 ×2
    vector<int> b(2 * n);
    for (int i = 0; i < n; ++i) {
        b[i] = a[i];
        b[i + n] = a[i];
    }

    // 前缀和（长度为2n）
    vector<int> pre(2 * n + 1, 0);
    for (int i = 1; i <= 2 * n; ++i) pre[i] = pre[i-1] + b[i-1];
    auto sum = [&](int l, int r) { return pre[r+1] - pre[l]; };

    // DP数组
    vector<vector<int>> dp(2 * n, vector<int>(2 * n, INF));
    for (int i = 0; i < 2 * n; ++i) dp[i][i] = 0;

    // 区间DP（只枚举长度最多到n即可，因为我们只关心长度为n的区间）
    for (int len = 2; len <= n; ++len) {
        for (int l = 0; l + len - 1 < 2 * n; ++l) {
            int r = l + len - 1;
            for (int k = l; k < r; ++k) {
                dp[l][r] = min(dp[l][r],
                    dp[l][k] + dp[k+1][r] + sum(l, r));
            }
        }
    }

    // 遍历所有长度为n的区间，取最小值
    int ans = INF;
    for (int i = 0; i < n; ++i) {
        ans = min(ans, dp[i][i + n - 1]);
    }
    return ans;
}

// 环形石子合并 - 最大代价
int circular_merge_stones_max(const vector<int>& a) {
    int n = a.size();
    vector<int> b(2 * n);
    for (int i = 0; i < n; ++i) b[i] = b[i + n] = a[i];

    vector<int> pre(2 * n + 1, 0);
    for (int i = 1; i <= 2 * n; ++i) pre[i] = pre[i-1] + b[i-1];
    auto sum = [&](int l, int r) { return pre[r+1] - pre[l]; };

    vector<vector<int>> dp(2 * n, vector<int>(2 * n, 0));
    for (int i = 0; i < 2 * n; ++i) dp[i][i] = 0;

    for (int len = 2; len <= n; ++len) {
        for (int l = 0; l + len - 1 < 2 * n; ++l) {
            int r = l + len - 1;
            for (int k = l; k < r; ++k) {
                dp[l][r] = max(dp[l][r],
                    dp[l][k] + dp[k+1][r] + sum(l, r));
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = max(ans, dp[i][i + n - 1]);
    }
    return ans;
}

// 环形石子合并 - 同时返回最小值和最大值
pair<int, int> circular_merge_stones(const vector<int>& a) {
    return {circular_merge_stones_min(a), circular_merge_stones_max(a)};
}

// ==================== 2. 能量项链（NOIP2006 提高组） ====================
// 问题：环形排列的珠子，每颗珠子有头标记和尾标记
// 前一颗珠子的尾标记 = 后一颗珠子的头标记
// 合并释放能量 = head[l] * head[k] * head[r]
// 注意：这里的转移是 dp[l][r] = max(dp[l][k] + dp[k][r] + ...)，不是 dp[k+1]
int energy_necklace(const vector<int>& head, int n) {
    // 破环成链 ×2（珠子的头标记）
    // head[1..n] 表示n颗珠子的头标记，head[n+1] = head[1]
    vector<int> h(2 * n + 2);
    for (int i = 1; i <= n; ++i) {
        h[i] = head[i];
        h[i + n] = head[i];
    }
    h[2 * n + 1] = h[1];  // 多余一位保证索引不越界

    vector<vector<int>> dp(2 * n + 1, vector<int>(2 * n + 1, 0));

    // len表示合并的珠子个数（2颗合并成1颗，3颗合并成1颗...）
    for (int len = 2; len <= n; ++len) {
        for (int l = 1; l + len - 1 <= 2 * n; ++l) {
            int r = l + len - 1;
            for (int k = l; k < r; ++k) {
                // 合并dp[l][k]和dp[k+1][r]
                // 左边合并结果的头标记=h[l], 尾标记=h[k+1]
                // 右边合并结果的头标记=h[k+1], 尾标记=h[r+1]
                // 能量 = h[l] * h[k+1] * h[r+1]
                dp[l][r] = max(dp[l][r],
                    dp[l][k] + dp[k+1][r] + h[l] * h[k+1] * h[r+1]);
            }
        }
    }

    // 遍历所有长度为n的区间，取最大值
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans = max(ans, dp[i][i + n - 1]);
    }
    return ans;
}

// ==================== 3. 消去型区间DP示例 ====================
// 简化版：给定一个数组，每次可以消除一个子数组（子数组和为0），求最少消除次数
// 这展示了消去型DP的典型模式

// 判断区间[l,r]的和是否为0
bool can_eliminate(const vector<int>& a, const vector<int>& pre, int l, int r) {
    return (pre[r+1] - pre[l]) == 0;
}

// 消去型区间DP：最少消除次数
int min_eliminations(const vector<int>& a) {
    int n = a.size();
    vector<int> pre(n + 1, 0);
    for (int i = 1; i <= n; ++i) pre[i] = pre[i-1] + a[i-1];

    vector<vector<int>> dp(n, vector<int>(n, INF));

    // 初始化：单个元素至少需要1次消除
    for (int i = 0; i < n; ++i) dp[i][i] = 1;

    for (int len = 2; len <= n; ++len) {
        for (int l = 0; l + len - 1 < n; ++l) {
            int r = l + len - 1;

            // 情况1：整个区间可以一次消除
            if (can_eliminate(a, pre, l, r)) {
                dp[l][r] = 1;
                continue;
            }

            // 情况2：分割成两个子区间分别消除
            for (int k = l; k < r; ++k) {
                dp[l][r] = min(dp[l][r], dp[l][k] + dp[k+1][r]);
            }
        }
    }
    return dp[0][n-1];
}

// ==================== 4. 四边形不等式优化（石子合并 - 最小代价） ====================
// 通过记录最优决策点 s[l][r]，将 O(n³) 优化到 O(n²)
// s[l][r-1] <= s[l][r] <= s[l+1][r]
int merge_stones_optimized(const vector<int>& a) {
    int n = a.size();
    vector<int> pre(n + 1, 0);
    for (int i = 1; i <= n; ++i) pre[i] = pre[i-1] + a[i-1];
    auto sum = [&](int l, int r) { return pre[r+1] - pre[l]; };

    vector<vector<int>> dp(n, vector<int>(n, INF));
    vector<vector<int>> s(n, vector<int>(n, 0));  // 最优决策点

    for (int i = 0; i < n; ++i) {
        dp[i][i] = 0;
        s[i][i] = i;  // 单个元素的决策点是自己
    }

    for (int len = 2; len <= n; ++len) {
        for (int l = 0; l + len - 1 < n; ++l) {
            int r = l + len - 1;
            // 利用四边形不等式缩小k的枚举范围
            int left_k = s[l][r-1];       // 下界
            int right_k = s[l+1][r];      // 上界
            // 注意：当 r-1 < l 时（即len=2），left_k = s[l][l] = l
            // 当 l+1 > r 时，right_k 取 r-1

            if (l + 1 > r) right_k = r - 1;
            if (r - 1 < l) left_k = l;

            for (int k = left_k; k <= right_k && k < r; ++k) {
                int val = dp[l][k] + dp[k+1][r] + sum(l, r);
                if (val < dp[l][r]) {
                    dp[l][r] = val;
                    s[l][r] = k;  // 记录最优决策点
                }
            }
        }
    }
    return dp[0][n-1];
}

// ==================== 5. 真题1：环形石子合并【洛谷 P1880】 ====================
void solve_p1880() {
    cout << "\n========== 真题1：环形石子合并【洛谷 P1880】 ==========" << endl;
    int n;
    cout << "请输入石子堆数 n: ";
    cin >> n;
    vector<int> a(n);
    cout << "请输入每堆石子的数量: ";
    for (int i = 0; i < n; ++i) cin >> a[i];

    auto [min_ans, max_ans] = circular_merge_stones(a);
    cout << "最小得分: " << min_ans << endl;
    cout << "最大得分: " << max_ans << endl;
}

// ==================== 6. 真题2：能量项链【洛谷 P1063】 ====================
void solve_p1063() {
    cout << "\n========== 真题2：能量项链【洛谷 P1063】 ==========" << endl;
    int n;
    cout << "请输入珠子数量 n: ";
    cin >> n;
    // 注意：输入的是每颗珠子的头标记
    // head[1..n] 存放，head[n+1] = head[1]
    vector<int> head(n + 1);
    cout << "请输入 " << n << " 个正整数（每颗珠子的头标记）: ";
    for (int i = 1; i <= n; ++i) cin >> head[i];

    cout << "最大总能量: " << energy_necklace(head, n) << endl;
}

// ==================== 7. 打印DP表（调试用） ====================
void print_dp_table(const vector<vector<int>>& dp, int n, const string& title) {
    cout << "=== " << title << " ===" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dp[i][j] >= INF / 2) cout << "∞\t";
            else cout << dp[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

// ==================== 8. 测试函数 ====================
void run_all_tests() {
    cout << "==================== 第32课：区间DP进阶 - 全部测试 ====================" << endl;

    // 测试1：环形石子合并 - 最小值
    {
        vector<int> a = {4, 5, 9, 4};
        auto [min_ans, max_ans] = circular_merge_stones(a);
        cout << "【测试1】环形石子合并 - 输入: [4,5,9,4]" << endl;
        cout << "  最小得分 期望: 43, 实际: " << min_ans << " -> "
             << (min_ans == 43 ? "✓ PASS" : "✗ FAIL") << endl;
        cout << "  最大得分 期望: 54, 实际: " << max_ans << " -> "
             << (max_ans == 54 ? "✓ PASS" : "✗ FAIL") << endl;
    }

    // 测试2：环形石子合并 - 简单情况
    {
        vector<int> a = {1, 2, 3};
        auto [min_ans, max_ans] = circular_merge_stones(a);
        cout << "【测试2】环形石子合并 - 输入: [1,2,3]" << endl;
        cout << "  最小得分: " << min_ans << ", 最大得分: " << max_ans << endl;
        // 环形情况：有三种"断开"方式
        // [1,2,3]: min=9, max=11
        // [2,3,1]: min=9, max=11
        // [3,1,2]: min=9, max=11
    }

    // 测试3：能量项链 - 标准样例
    {
        // 注意：head[1..n]存储，head[1]对应第一颗珠子的头标记
        // 样例：4颗珠子，头标记为 2,3,5,10
        // 第一颗珠子(头=2,尾=3)，第二颗(头=3,尾=5)，第三颗(头=5,尾=10)，第四颗(头=10,尾=2)
        vector<int> head = {0, 2, 3, 5, 10};  // 下标从1开始
        int ans = energy_necklace(head, 4);
        cout << "【测试3】能量项链 - 头标记: [2,3,5,10]" << endl;
        cout << "  期望输出: 710, 实际输出: " << ans << " -> "
             << (ans == 710 ? "✓ PASS" : "✗ FAIL") << endl;
    }

    // 测试4：四边形不等式优化 vs 朴素版本
    {
        vector<int> a = {4, 5, 9, 4, 7, 3, 6, 8};
        int naive = circular_merge_stones_min(a);
        // 直线版本用四边形不等式优化
        int optimized = merge_stones_optimized(a);
        int naive_linear = [&]() {
            int n = a.size();
            vector<int> pre(n+1,0);
            for(int i=1;i<=n;++i) pre[i]=pre[i-1]+a[i-1];
            auto sum = [&](int l,int r){return pre[r+1]-pre[l];};
            vector<vector<int>> dp(n, vector<int>(n, INF));
            for(int i=0;i<n;++i) dp[i][i]=0;
            for(int len=2;len<=n;++len)
                for(int l=0;l+len-1<n;++l){
                    int r=l+len-1;
                    for(int k=l;k<r;++k)
                        dp[l][r]=min(dp[l][r],dp[l][k]+dp[k+1][r]+sum(l,r));
                }
            return dp[0][n-1];
        }();

        cout << "【测试4】四边形不等式优化验证" << endl;
        cout << "  朴素直线版: " << naive_linear << endl;
        cout << "  优化直线版: " << optimized << " -> "
             << (naive_linear == optimized ? "✓ PASS" : "✗ FAIL") << endl;
    }

    // 测试5：消去型区间DP
    {
        vector<int> a = {1, -1, 2, -2, 3, -3};
        int ans = min_eliminations(a);
        cout << "【测试5】消去型区间DP - 输入: [1,-1,2,-2,3,-3]" << endl;
        cout << "  最少消除次数: " << ans << " (每个和为0的子数组可一次消除)" << endl;
    }

    // 测试6：消去型区间DP - 全正数
    {
        vector<int> a = {1, 2, 3};
        int ans = min_eliminations(a);
        cout << "【测试6】消去型区间DP - 输入: [1,2,3]" << endl;
        // 没有和为0的子数组，只能一个一个消 -> 3次
        cout << "  期望输出: 3, 实际输出: " << ans << " -> "
             << (ans == 3 ? "✓ PASS" : "✗ FAIL") << endl;
    }

    // 测试7：四边形不等式 - 大数组性能测试
    {
        int n = 200;
        vector<int> a(n);
        srand(time(0));
        for (int i = 0; i < n; ++i) a[i] = rand() % 100 + 1;

        auto start = clock();
        int opt = merge_stones_optimized(a);
        auto end = clock();
        double time_opt = (double)(end - start) / CLOCKS_PER_SEC;

        cout << "【测试7】四边形不等式 - n=200 性能测试" << endl;
        cout << "  优化版结果: " << opt << ", 耗时: " << time_opt << "s" << endl;

        auto start2 = clock();
        // 朴素O(n³)
        auto naive_linear = [&]() {
            int n = a.size();
            vector<int> pre(n+1,0);
            for(int i=1;i<=n;++i) pre[i]=pre[i-1]+a[i-1];
            auto sum = [&](int l,int r){return pre[r+1]-pre[l];};
            vector<vector<int>> dp(n, vector<int>(n, INF));
            for(int i=0;i<n;++i) dp[i][i]=0;
            for(int len=2;len<=n;++len)
                for(int l=0;l+len-1<n;++l){
                    int r=l+len-1;
                    for(int k=l;k<r;++k)
                        dp[l][r]=min(dp[l][r],dp[l][k]+dp[k+1][r]+sum(l,r));
                }
            return dp[0][n-1];
        }();
        auto end2 = clock();
        double time_naive = (double)(end2 - start2) / CLOCKS_PER_SEC;

        cout << "  朴素版结果: " << naive_linear << ", 耗时: " << time_naive << "s" << endl;
        cout << "  结果一致: " << (opt == naive_linear ? "✓" : "✗") << endl;
        cout << "  加速比: " << (time_naive / max(time_opt, 0.000001)) << "x" << endl;
    }

    cout << "\n==================== 全部测试完成 ====================" << endl;
}

// ==================== 主函数 ====================
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 运行所有测试
    run_all_tests();

    // 如需交互式输入，取消以下注释：
    // solve_p1880();
    // solve_p1063();

    return 0;
}
