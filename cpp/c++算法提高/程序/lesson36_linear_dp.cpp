/**
 * Lesson 36: 线性DP —— 一维动态规划
 *
 * 本程序包含：
 * 1. 最大子段和 (Maximum Subarray Sum) —— O(n) 算法
 * 2. 最长上升子序列 (Longest Increasing Subsequence) —— O(n^2) 算法
 * 3. LIS 优化 —— O(n log n) 贪心 + 二分查找（选学内容）
 * 4. 例题1 & 例题2 的完整交互式解答
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ============================================================
// 函数1：最大子段和 —— O(n)
// dp[i] 定义：以第 i 个元素结尾的最大子段和
// 状态转移：dp[i] = max(a[i], dp[i-1] + a[i])
// 空间优化：只需维护 curMax 和 ans 两个变量
// ============================================================
int maxSubarraySum(const vector<int>& a) {
    int n = a.size();
    if (n == 0) return 0;

    // 初始状态：以第一个元素结尾的最大子段和就是 a[0]
    int curMax = a[0];  // 相当于 dp[0]
    int ans = a[0];     // 全局最大子段和

    // 从第二个元素开始递推
    for (int i = 1; i < n; i++) {
        // 决策：要么独自成段，要么接在前面子段后面
        curMax = max(a[i], curMax + a[i]);
        // 更新全局最大值
        ans = max(ans, curMax);
    }

    return ans;
}

// ============================================================
// 函数2：最长上升子序列(LIS) —— O(n^2)
// dp[i] 定义：以第 i 个元素结尾的最长上升子序列的长度
// 状态转移：dp[i] = max(dp[j] + 1)，其中 j < i 且 a[j] < a[i]
// ============================================================
int LIS(const vector<int>& a) {
    int n = a.size();
    if (n == 0) return 0;

    // dp[i] 初始化为 1，因为每个元素自身构成长度为 1 的子序列
    vector<int> dp(n, 1);
    int ans = 1;  // 全局最长上升子序列长度

    // 从第二个元素开始递推
    for (int i = 1; i < n; i++) {
        // 枚举所有 j < i，寻找可以接在后面的最长子序列
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i]) {  // 严格递增条件
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        // 更新全局最大值
        ans = max(ans, dp[i]);
    }

    return ans;
}

// ============================================================
// 函数3（选学）：最长上升子序列 —— O(n log n)
// 使用贪心 + 二分查找优化
// tails[k] 表示长度为 k+1 的上升子序列的最小末尾元素
// ============================================================
int LIS_nlogn(const vector<int>& a) {
    // tails 数组：tails[k] = 长度为 k+1 的上升子序列的最小末尾元素
    vector<int> tails;

    for (int x : a) {
        // 在 tails 中二分查找第一个 >= x 的位置
        // lower_bound 返回指向第一个 >= x 的元素的迭代器
        auto it = lower_bound(tails.begin(), tails.end(), x);

        if (it == tails.end()) {
            // x 比 tails 中所有元素都大，可以扩展子序列长度
            tails.push_back(x);
        } else {
            // 替换这个位置，保持每个长度的末尾元素尽可能小
            // 这是贪心思想：末尾越小，后续越容易扩展
            *it = x;
        }
    }

    // tails 的长度就是 LIS 的长度
    return tails.size();
}

// ============================================================
// 例题1：最大子段和 —— 交互式输入输出
// ============================================================
void solveMaxSubarraySum() {
    cout << "========== 例题1：最大子段和 ==========" << endl;
    cout << "输入序列长度 n: ";
    int n;
    cin >> n;

    cout << "输入 " << n << " 个整数（用空格分隔）: ";
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int result = maxSubarraySum(a);
    cout << "最大子段和为: " << result << endl;
    cout << endl;
}

// ============================================================
// 例题2：最长上升子序列 —— 交互式输入输出
// ============================================================
void solveLIS() {
    cout << "========== 例题2：最长上升子序列 ==========" << endl;
    cout << "输入序列长度 n: ";
    int n;
    cin >> n;

    cout << "输入 " << n << " 个整数（用空格分隔）: ";
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // 使用 O(n^2) 解法
    int resultO2 = LIS(a);
    cout << "最长上升子序列长度 (O(n²)解法): " << resultO2 << endl;

    // 使用 O(n log n) 解法
    int resultOptimized = LIS_nlogn(a);
    cout << "最长上升子序列长度 (O(n log n)解法): " << resultOptimized << endl;
    cout << endl;
}

// ============================================================
// 自动测试：使用课上的样例数据验证算法正确性
// ============================================================
void runTests() {
    cout << "========== 自动测试（使用课上的样例数据） ==========" << endl;

    // 测试1：最大子段和
    // 样例：[-2, 1, -3, 4, -1, 2, 1, -5, 4]，答案应为 6
    vector<int> test1 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int result1 = maxSubarraySum(test1);
    cout << "测试1 - 最大子段和: " << result1;
    cout << " (期望: 6) " << (result1 == 6 ? "✓ PASS" : "✗ FAIL") << endl;

    // 测试2：最长上升子序列 (O(n²))
    // 样例：[3, 1, 4, 1, 5, 9, 2, 6]，答案应为 4
    vector<int> test2 = {3, 1, 4, 1, 5, 9, 2, 6};
    int result2 = LIS(test2);
    cout << "测试2 - LIS O(n²): " << result2;
    cout << " (期望: 4) " << (result2 == 4 ? "✓ PASS" : "✗ FAIL") << endl;

    // 测试3：最长上升子序列 (O(n log n))
    int result3 = LIS_nlogn(test2);
    cout << "测试3 - LIS O(n log n): " << result3;
    cout << " (期望: 4) " << (result3 == 4 ? "✓ PASS" : "✗ FAIL") << endl;

    // 测试4：全负数最大子段和
    // 样例：[-5, -2, -3, -1]，答案应为 -1
    vector<int> test4 = {-5, -2, -3, -1};
    int result4 = maxSubarraySum(test4);
    cout << "测试4 - 全负数最大子段和: " << result4;
    cout << " (期望: -1) " << (result4 == -1 ? "✓ PASS" : "✗ FAIL") << endl;

    // 测试5：单元素上升子序列
    // 样例：[7]，答案应为 1
    vector<int> test5 = {7};
    int result5 = LIS(test5);
    cout << "测试5 - 单元素 LIS: " << result5;
    cout << " (期望: 1) " << (result5 == 1 ? "✓ PASS" : "✗ FAIL") << endl;

    // 测试6：完全递增序列
    // 样例：[1, 2, 3, 4, 5]，答案应为 5
    vector<int> test6 = {1, 2, 3, 4, 5};
    int result6 = LIS(test6);
    cout << "测试6 - 完全递增 LIS: " << result6;
    cout << " (期望: 5) " << (result6 == 5 ? "✓ PASS" : "✗ FAIL") << endl;

    // 测试7：完全递减序列
    // 样例：[5, 4, 3, 2, 1]，答案应为 1
    vector<int> test7 = {5, 4, 3, 2, 1};
    int result7 = LIS(test7);
    cout << "测试7 - 完全递减 LIS: " << result7;
    cout << " (期望: 1) " << (result7 == 1 ? "✓ PASS" : "✗ FAIL") << endl;

    cout << endl;
}

// ============================================================
// 主函数
// ============================================================
int main() {
    cout << "========================================" << endl;
    cout << "  第36课：线性DP —— 一维动态规划" << endl;
    cout << "========================================" << endl;
    cout << endl;

    // 运行自动测试
    runTests();

    // 交互式测试
    // 取消下面的注释可以进行手动输入测试：
    // solveMaxSubarraySum();
    // solveLIS();

    return 0;
}
