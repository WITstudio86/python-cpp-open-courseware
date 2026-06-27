/**
 * 洛谷 P1063 - 能量项链（NOIP2006 提高组）
 *
 * 题目描述：
 * 在 Mars 星球上，每个 Mars 人都随身佩带着一串能量项链。
 * 项链上有 N 颗能量珠，每颗珠子有头标记与尾标记。
 * 相邻珠子：前一颗的尾标记 = 后一颗的头标记。
 * 聚合能量：m × r × n（前头、共享标记、后尾）
 * 求最大总能量。
 *
 * 核心技巧：
 * 1. 环形 → 破环成链 ×2
 * 2. 区间DP：dp[l][r] 表示合并珠子 l 到 r 的最大能量
 * 3. 转移：dp[l][r] = max(dp[l][k] + dp[k][r] + head[l] * head[k+1] * head[r+1])
 *    注意这里是 dp[l][k] + dp[k][r]（不是 dp[k+1][r]），因为珠子合并涉及边界标记
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // head[i] 表示第 i 颗珠子的头标记，head[i+1] 是它的尾标记
    // 环形：head[n+1] = head[1]
    vector<int> head(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> head[i];
    }

    // 破环成链 ×2
    vector<int> h(2 * n + 1);
    for (int i = 1; i <= n; ++i) {
        h[i] = head[i];
        h[i + n] = head[i];
    }

    // dp[l][r]：合并珠子 l 到 r 的最大能量
    // 注意：合并后新珠子头标记 = head[l]，尾标记 = head[r+1]
    vector<vector<int>> dp(2 * n + 1, vector<int>(2 * n + 1, 0));

    // 区间DP：按长度枚举
    for (int len = 2; len <= n; ++len) {
        for (int l = 1; l + len - 1 <= 2 * n; ++l) {
            int r = l + len - 1;
            for (int k = l; k < r; ++k) {
                // 合并 [l, k] 和 [k+1, r]，注意能量公式中的索引
                // 左半部分合并后头标记 = h[l], 尾标记 = h[k+1]
                // 右半部分合并后头标记 = h[k+1], 尾标记 = h[r+1]
                dp[l][r] = max(dp[l][r],
                    dp[l][k] + dp[k + 1][r] + h[l] * h[k + 1] * h[r + 1]);
            }
        }
    }

    // 遍历所有长度为 n 的区间，取最大值
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans = max(ans, dp[i][i + n - 1]);
    }

    cout << ans << endl;

    return 0;
}
