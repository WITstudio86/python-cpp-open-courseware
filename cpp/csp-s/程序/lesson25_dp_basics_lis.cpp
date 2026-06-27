/*
 * 第25课：DP基础与LIS（最长上升子序列）
 * 考纲知识点：动态规划基本概念、最优子结构、无后效性、LIS的O(n²)与O(n log n)解法
 */

#include <bits/stdc++.h>
using namespace std;

// ==================== 1. LIS - O(n²) DP ====================
// dp[i] 表示以 a[i] 结尾的最长上升子序列长度
// 状态转移：dp[i] = max(dp[j] + 1)  for all j < i, a[j] < a[i]
int lis_n2(const vector<int>& a) {
    int n = a.size();
    vector<int> dp(n, 1);
    int ans = 1;
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (a[j] < a[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        ans = max(ans, dp[i]);
    }
    return ans;
}

// ==================== 2. LIS - O(n log n) 贪心+二分 ====================
// tails[i] 表示长度为 i+1 的上升子序列的最小末尾元素
// 贪心性质：末尾元素越小，越容易接上新的元素
int lis_nlogn(const vector<int>& a) {
    vector<int> tails;
    for (int x : a) {
        auto it = lower_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) {
            tails.push_back(x);
        } else {
            *it = x;
        }
    }
    return tails.size();
}

// ==================== 3. LIS 路径还原 ====================
vector<int> lis_path(const vector<int>& a) {
    int n = a.size();
    vector<int> dp(n, 1), pre(n, -1);
    int best_end = 0;
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (a[j] < a[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                pre[i] = j;
            }
        }
        if (dp[i] > dp[best_end]) best_end = i;
    }
    vector<int> path;
    for (int i = best_end; i != -1; i = pre[i]) {
        path.push_back(a[i]);
    }
    reverse(path.begin(), path.end());
    return path;
}

// ==================== 4. 最长不下降子序列 (LNDS) ====================
int lnds_nlogn(const vector<int>& a) {
    vector<int> tails;
    for (int x : a) {
        // 使用 upper_bound 允许相等元素
        auto it = upper_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) {
            tails.push_back(x);
        } else {
            *it = x;
        }
    }
    return tails.size();
}

// ==================== 5. 真题1：导弹拦截（NOIP1999 提高组） ====================
// 问题：求最长不上升子序列长度（最多拦截数）和最少拦截系统数
// 分析：最少拦截系统数 = 最长上升子序列长度（Dilworth定理）
void missile_interception() {
    vector<int> a;
    int x;
    while (cin >> x) a.push_back(x);
    if (a.empty()) return;

    int n = a.size();

    // 第一问：最长不上升子序列长度
    // 将问题转化为求 LIS 在逆序数组上
    vector<int> tails1;
    for (int i = 0; i < n; ++i) {
        int x = a[i];
        // 求不上升：找第一个 < x 的位置（严格递减条件）
        auto it = upper_bound(tails1.begin(), tails1.end(), x, greater<int>());
        if (it == tails1.end()) {
            tails1.push_back(x);
        } else {
            *it = x;
        }
    }
    cout << tails1.size() << endl;

    // 第二问：最少系统数 = 最长上升子序列长度
    vector<int> tails2;
    for (int x : a) {
        auto it = lower_bound(tails2.begin(), tails2.end(), x);
        if (it == tails2.end()) {
            tails2.push_back(x);
        } else {
            *it = x;
        }
    }
    cout << tails2.size() << endl;
}

// ==================== 6. 真题2：合唱队形（NOIP2004 提高组） ====================
// 问题：从N人中剔除最少的人，使得剩下的人呈先上升后下降的队形
// 分析：对每个位置i，求以i结尾的LIS长度left[i]，以i开头的LDS长度right[i]
//       答案 = N - max(left[i] + right[i] - 1)
int chorus_formation(const vector<int>& h) {
    int n = h.size();
    vector<int> left(n, 1), right(n, 1);

    // 从左到右的 LIS
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (h[j] < h[i]) {
                left[i] = max(left[i], left[j] + 1);
            }
        }
    }

    // 从右到左的 LIS（等价于从左看的LDS）
    for (int i = n - 1; i >= 0; --i) {
        for (int j = n - 1; j > i; --j) {
            if (h[j] < h[i]) {
                right[i] = max(right[i], right[j] + 1);
            }
        }
    }

    int max_len = 0;
    for (int i = 0; i < n; ++i) {
        max_len = max(max_len, left[i] + right[i] - 1);
    }
    return n - max_len;  // 最少需要剔除的人数
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 测试 LIS
    vector<int> a = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << "LIS O(n^2): " << lis_n2(a) << endl;          // 4
    cout << "LIS O(n log n): " << lis_nlogn(a) << endl;   // 4

    // 测试路径还原
    auto path = lis_path(a);
    cout << "LIS path: ";
    for (int x : path) cout << x << " ";
    cout << endl;

    // 测试 LNDS
    vector<int> b = {1, 3, 3, 3, 5};
    cout << "LNDS: " << lnds_nlogn(b) << endl;  // 5

    // 测试合唱队形
    vector<int> h = {186, 186, 150, 200, 160, 130, 197, 220};
    cout << "Chorus formation remove: " << chorus_formation(h) << endl;

    return 0;
}
