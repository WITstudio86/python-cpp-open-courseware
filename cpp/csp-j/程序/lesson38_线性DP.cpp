/**
 * lesson38_线性DP.cpp
 * CSP-J 备考课程 第38课
 *
 * 包含内容：
 * 1. 最长上升子序列 LIS - O(n^2) 解法
 * 2. 最长公共子序列 LCS - O(n*m) 解法
 * 3. 最大子段和 - Kadane算法 O(n)
 * 4. 编辑距离 - O(n*m) 解法
 */

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// 一、最长上升子序列（LIS）- O(n^2)
// ============================================================
// 状态：dp[i] 表示以 a[i] 结尾的最长上升子序列长度
// 转移：dp[i] = max(dp[j] + 1), 对所有 j < i 且 a[j] < a[i]
// 答案：max(dp[1..n])
// -----------------------------------------------------------
void longestIncreasingSubsequence() {
    cout << "========== 最长上升子序列 LIS（O(n^2)）==========" << endl;

    int n;
    cout << "请输入序列长度 n：";
    cin >> n;

    vector<int> a(n + 1), dp(n + 1, 0);
    vector<int> pre(n + 1, 0);  // 记录前驱，用于输出具体序列

    cout << "请输入 " << n << " 个整数：";
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    int ans = 0, best_end = 1;

    for (int i = 1; i <= n; i++) {
        dp[i] = 1;
        pre[i] = 0;
        for (int j = 1; j < i; j++) {
            if (a[j] < a[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                pre[i] = j;
            }
        }
        if (dp[i] > ans) {
            ans = dp[i];
            best_end = i;
        }
    }

    cout << "最长上升子序列长度 = " << ans << endl;

    // 回溯输出具体序列
    vector<int> seq;
    int cur = best_end;
    while (cur != 0) {
        seq.push_back(a[cur]);
        cur = pre[cur];
    }
    reverse(seq.begin(), seq.end());

    cout << "其中一个最长上升子序列：";
    for (size_t i = 0; i < seq.size(); i++) {
        if (i > 0) cout << " ";
        cout << seq[i];
    }
    cout << endl << endl;
}

// ============================================================
// 二、最长公共子序列（LCS）- O(n*m)
// ============================================================
// 状态：dp[i][j] 表示 A前i个 与 B前j个 的LCS长度
// 转移：
//   若 A[i] == B[j]: dp[i][j] = dp[i-1][j-1] + 1
//   若 A[i] != B[j]: dp[i][j] = max(dp[i-1][j], dp[i][j-1])
// -----------------------------------------------------------
void longestCommonSubsequence() {
    cout << "========== 最长公共子序列 LCS（O(n*m)）==========" << endl;

    string a, b;
    cout << "请输入字符串A：";
    cin >> a;
    cout << "请输入字符串B：";
    cin >> b;

    int n = a.size(), m = b.size();

    // 下标从1开始，前面补占位符
    a = " " + a;
    b = " " + b;

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i] == b[j])
                dp[i][j] = dp[i-1][j-1] + 1;
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }

    cout << "最长公共子序列长度 = " << dp[n][m] << endl;

    // 回溯输出LCS的具体内容
    string lcs;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (a[i] == b[j]) {
            lcs = a[i] + lcs;
            i--; j--;
        } else if (dp[i-1][j] >= dp[i][j-1]) {
            i--;
        } else {
            j--;
        }
    }

    cout << "其中一个最长公共子序列：";
    if (lcs.empty())
        cout << "（空）";
    else
        cout << lcs;
    cout << endl << endl;
}

// ============================================================
// 三、最大子段和 - Kadane算法 O(n)
// ============================================================
// 状态：dp[i] 表示以 a[i] 结尾的最大子段和
// 转移：dp[i] = max(dp[i-1] + a[i], a[i])
// 优化：空间O(1)，只需维护cur和ans
// -----------------------------------------------------------
void maximumSubarraySum() {
    cout << "========== 最大子段和（Kadane算法 O(n)）==========" << endl;

    int n;
    cout << "请输入序列长度 n：";
    cin >> n;

    vector<int> a(n);
    cout << "请输入 " << n << " 个整数（可包含负数）：";
    for (int i = 0; i < n; i++)
        cin >> a[i];

    // Kadane算法
    int cur = a[0];    // 以当前位置结尾的最大和
    int ans = a[0];    // 全局最大和
    int start = 0, end = 0;     // 记录最大子段的起止位置
    int temp_start = 0;

    for (int i = 1; i < n; i++) {
        // 判断是接在后面好，还是自己独立成段好
        if (cur + a[i] >= a[i]) {
            cur = cur + a[i];
        } else {
            cur = a[i];
            temp_start = i;
        }

        if (cur > ans) {
            ans = cur;
            start = temp_start;
            end = i;
        }
    }

    cout << "最大子段和 = " << ans << endl;
    cout << "对应子段位置：[" << start << ", " << end << "]" << endl;
    cout << "子段内容：";
    for (int i = start; i <= end; i++) {
        if (i > start) cout << " ";
        cout << a[i];
    }
    cout << endl << endl;
}

// ============================================================
// 四、编辑距离 - O(n*m)
// ============================================================
// 状态：dp[i][j] 表示将 A前i个字符 转换为 B前j个字符 的最少操作数
// 转移：
//   若 A[i] == B[j]: dp[i][j] = dp[i-1][j-1]
//   若 A[i] != B[j]: dp[i][j] = min(dp[i-1][j-1], dp[i-1][j], dp[i][j-1]) + 1
//         dp[i-1][j-1] + 1  → 替换 A[i] 为 B[j]
//         dp[i-1][j] + 1    → 删除 A[i]
//         dp[i][j-1] + 1    → 在 A[i] 后插入 B[j]
// -----------------------------------------------------------
void editDistance() {
    cout << "========== 编辑距离 ==========" << endl;

    string a, b;
    cout << "请输入字符串A：";
    cin >> a;
    cout << "请输入字符串B：";
    cin >> b;

    int n = a.size(), m = b.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // 初始化边界
    for (int i = 0; i <= n; i++) dp[i][0] = i;  // 删除i个字符
    for (int j = 0; j <= m; j++) dp[0][j] = j;  // 插入j个字符

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i-1] == b[j-1]) {
                dp[i][j] = dp[i-1][j-1];  // 不需要操作
            } else {
                dp[i][j] = min({dp[i-1][j-1], dp[i-1][j], dp[i][j-1]}) + 1;
            }
        }
    }

    cout << "编辑距离 = " << dp[n][m] << endl;
    cout << "（即将 \"" << a << "\" 转换为 \"" << b << "\" 所需的最少操作数）" << endl;
    cout << endl;
}

// ============================================================
// 五、最大子段和变种 - 环形数组
// ============================================================
// 问题：给定一个环形数组，求最大子段和。
// 思路：max(最大子段和, 总和 - 最小子段和)
// 注意：全负数时需要特判
// -----------------------------------------------------------
void circularMaxSubarraySum() {
    cout << "========== 环形数组最大子段和 ==========" << endl;

    int n;
    cout << "请输入数组长度 n：";
    cin >> n;

    vector<int> a(n);
    cout << "请输入 " << n << " 个整数：";
    for (int i = 0; i < n; i++)
        cin >> a[i];

    // 普通最大子段和
    int cur_max = a[0], max_sum = a[0];
    int cur_min = a[0], min_sum = a[0];
    int total = a[0];

    for (int i = 1; i < n; i++) {
        total += a[i];
        // 最大
        cur_max = max(cur_max + a[i], a[i]);
        max_sum = max(max_sum, cur_max);
        // 最小
        cur_min = min(cur_min + a[i], a[i]);
        min_sum = min(min_sum, cur_min);
    }

    // 环形最大子段和
    int circular_max;
    if (max_sum < 0) {
        // 全为负数的情况
        circular_max = max_sum;
    } else {
        circular_max = max(max_sum, total - min_sum);
    }

    cout << "普通最大子段和 = " << max_sum << endl;
    cout << "环形最大子段和 = " << circular_max << endl;
    cout << endl;
}

// ============================================================
// 主菜单
// ============================================================
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cout << "========================================" << endl;
    cout << "  CSP-J 第38课：线性DP" << endl;
    cout << "  程序演示合集" << endl;
    cout << "========================================" << endl;
    cout << endl;

    while (true) {
        cout << "请选择要运行的示例：" << endl;
        cout << "  1. 最长上升子序列 LIS（O(n^2)）" << endl;
        cout << "  2. 最长公共子序列 LCS（O(n*m)）" << endl;
        cout << "  3. 最大子段和（Kadane O(n)）" << endl;
        cout << "  4. 编辑距离" << endl;
        cout << "  5. 环形数组最大子段和（变种）" << endl;
        cout << "  0. 退出" << endl;
        cout << "请输入编号：";

        int choice;
        cin >> choice;

        if (choice == 0) {
            cout << "再见！" << endl;
            break;
        }

        switch (choice) {
            case 1: longestIncreasingSubsequence(); break;
            case 2: longestCommonSubsequence(); break;
            case 3: maximumSubarraySum(); break;
            case 4: editDistance(); break;
            case 5: circularMaxSubarraySum(); break;
            default: cout << "无效选择，请重试。" << endl;
        }
    }

    return 0;
}
