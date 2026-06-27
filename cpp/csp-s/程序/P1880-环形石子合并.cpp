/**
 * 洛谷 P1880 - 环形石子合并
 *
 * 题目描述：
 * 在一个圆形操场的四周摆放 N 堆石子，现要将石子有次序地合并成一堆。
 * 规定每次只能选相邻的2堆合并成新的一堆，并将新的一堆的石子数记为该次合并的得分。
 * 计算出将 N 堆石子合并成1堆的最小得分和最大得分。
 *
 * 核心技巧：破环成链 ×2
 * 将长度为 n 的环展开为 2n 的链，在链上做区间DP，
 * 最终答案遍历所有长度为 n 的区间取最值。
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

const int INF = 0x3f3f3f3f;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // 破环成链：将原始数组复制一份接在尾部
    vector<int> a(2 * n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i + n] = a[i];
    }

    // 前缀和（长度为 2n+1，pre[0] = 0）
    vector<int> pre(2 * n + 1, 0);
    for (int i = 1; i <= 2 * n; ++i) {
        pre[i] = pre[i - 1] + a[i - 1];
    }
    auto sum = [&](int l, int r) {
        return pre[r + 1] - pre[l];
    };

    // dp_min 和 dp_max
    vector<vector<int>> dp_min(2 * n, vector<int>(2 * n, INF));
    vector<vector<int>> dp_max(2 * n, vector<int>(2 * n, 0));

    // 初始化：单个石子堆的得分为 0
    for (int i = 0; i < 2 * n; ++i) {
        dp_min[i][i] = 0;
    }

    // 区间DP：按区间长度从小到大枚举
    for (int len = 2; len <= n; ++len) {
        for (int l = 0; l + len - 1 < 2 * n; ++l) {
            int r = l + len - 1;
            for (int k = l; k < r; ++k) {
                dp_min[l][r] = min(dp_min[l][r],
                    dp_min[l][k] + dp_min[k + 1][r] + sum(l, r));
                dp_max[l][r] = max(dp_max[l][r],
                    dp_max[l][k] + dp_max[k + 1][r] + sum(l, r));
            }
        }
    }

    // 遍历所有长度为 n 的区间，取最值
    int ans_min = INF, ans_max = 0;
    for (int i = 0; i < n; ++i) {
        ans_min = min(ans_min, dp_min[i][i + n - 1]);
        ans_max = max(ans_max, dp_max[i][i + n - 1]);
    }

    cout << ans_min << endl;
    cout << ans_max << endl;

    return 0;
}
