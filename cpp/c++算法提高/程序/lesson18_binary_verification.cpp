/**
 * Lesson 18: 综合练习——查找算法应用
 *
 * 核心算法：二分答案 + 贪心验证
 *
 * 本文件包含两个经典问题的完整解法：
 *   1. 数列分段：将 N 个数分成 M 段，最小化最大段和
 *   2. 月度开销：将 N 天的开销分成 M 个月，最小化最大月度开销
 *
 * 两个问题的本质相同，都使用“二分答案 + 贪心 check()”的模式解决。
 */

#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100005;
long long a[MAXN];        // 数列分段用的数组
long long expense[MAXN];  // 月度开销用的数组
int n, m;

// ============================================================
// 问题1：数列分段 Section
// ============================================================
// 题目描述：
//   给定长度为 N 的正整数数列，将其分成 M 段（每段连续），
//   求每段和的最大值的最小可能值。
//
// 解题思路：
//   二分答案：枚举"最大段和的上限" mid
//   check(mid)：贪心地从左到右扫描，尽可能把元素放入当前段，
//              当前段和超过 mid 时新起一段，最终判断段数是否 ≤ M。
//   如果段数 ≤ M，说明 mid 可行（可以尝试更小的上限）；
//   否则 mid 不可行（需要更大的上限）。
// ============================================================

/**
 * 数列分段的 check 函数
 * @param limit  当前猜测的最大段和上限
 * @return       能否在每段和 ≤ limit 的情况下，将序列分成 ≤ m 段
 *
 * 时间复杂度：O(n)，只需扫描一次数组
 */
bool checkSegments(long long limit) {
    int segments = 1;          // 当前段数，初始为 1（至少有一段）
    long long currentSum = 0;  // 当前段内元素之和

    for (int i = 0; i < n; i++) {
        // 剪枝：如果单个元素就超过了上限，无论如何都不可行
        if (a[i] > limit) {
            return false;
        }

        // 贪心策略：尽量往当前段加元素，塞不下就新起一段
        if (currentSum + a[i] > limit) {
            // 当前段已经装不下 a[i]，新起一段
            segments++;
            currentSum = a[i];   // a[i] 成为新段的第一个元素
        } else {
            // 可以继续往当前段加
            currentSum += a[i];
        }
    }

    // 如果所需段数 ≤ m，说明这个上限足够大，可行
    return segments <= m;
}

/**
 * 数列分段的二分答案主函数
 * @return 最小的最大段和
 *
 * 时间复杂度：O(n log S)，其中 S 是答案搜索范围
 */
long long solveSegments() {
    // 确定二分上下界
    long long left = 0;   // 下界：数组中的最大值（一段至少包含一个元素）
    long long right = 0;  // 上界：所有元素之和（全部归为一段）

    for (int i = 0; i < n; i++) {
        left = max(left, a[i]);
        right += a[i];
    }

    // 二分搜索：在 [left, right] 中找到最小的可行上限
    long long ans = right;  // 最坏情况：所有元素分一段
    while (left <= right) {
        long long mid = left + (right - left) / 2;

        if (checkSegments(mid)) {
            // mid 可行！尝试更小的上限
            ans = mid;
            right = mid - 1;
        } else {
            // mid 不可行，需要更大的上限
            left = mid + 1;
        }
    }

    return ans;
}

// ============================================================
// 问题2：月度开销 Section
// ============================================================
// 题目描述：
//   给出未来 N 天中每天的开销，需要将这 N 天划分为 M 个
//   连续的"fajo 月"，使得开销最大的那个月的开销尽可能小。
//
// 解题思路：
//   与数列分段完全一致。唯一的区别是：
//   - 数列分段的"段" → 月度开销的"月"
//   - 数列分段的"数组元素" → 月度开销的"每天开销"
//   算法框架完全相同：二分答案 + 贪心 check()
// ============================================================

/**
 * 月度开销的 check 函数
 * @param limit  当前猜测的最大月度开销上限
 * @return       能否在每月开销 ≤ limit 的情况下，划分成 ≤ m 个月
 *
 * 贪心思路：
 *   尽可能把相邻的天合并到同一个月，直到再加一天就会
 *   超过上限 limit。这样得到的月份数是最少的。
 *   如果最少月份数 ≤ m，说明 limit 可行。
 */
bool checkMonthly(long long limit) {
    int months = 1;            // 当前已划分的月份数
    long long currentSum = 0;  // 当前月的开销总和

    for (int i = 0; i < n; i++) {
        // 单天开销超过上限，无法满足
        if (expense[i] > limit) {
            return false;
        }

        if (currentSum + expense[i] > limit) {
            // 当前月装不下今天的开销，新开一个月
            months++;
            currentSum = expense[i];
        } else {
            // 今天的开销可以归入当前月
            currentSum += expense[i];
        }
    }

    return months <= m;
}

/**
 * 月度开销的二分答案主函数
 * @return 最小的最大月度开销
 */
long long solveMonthly() {
    // 确定二分上下界
    long long left = 0;   // 下界：单天最大开销
    long long right = 0;  // 上界：所有天开销之和

    for (int i = 0; i < n; i++) {
        left = max(left, expense[i]);
        right += expense[i];
    }

    // 二分搜索最小可行上限
    long long ans = right;
    while (left <= right) {
        long long mid = left + (right - left) / 2;

        if (checkMonthly(mid)) {
            ans = mid;
            right = mid - 1;   // 尝试更小的上限
        } else {
            left = mid + 1;    // 需要更大的上限
        }
    }

    return ans;
}

// ============================================================
// 测试与演示
// ============================================================
int main() {
    cout << "══════════════════════════════════════════" << endl;
    cout << "  第18课：二分答案 + 贪心验证 测试程序" << endl;
    cout << "══════════════════════════════════════════" << endl;

    // ----- 测试1：数列分段 -----
    cout << "\n【测试1】数列分段" << endl;
    cout << "输入：" << endl;
    cout << "  5 3" << endl;
    cout << "  4 2 4 5 1" << endl;

    n = 5, m = 3;
    a[0] = 4; a[1] = 2; a[2] = 4; a[3] = 5; a[4] = 1;

    long long result1 = solveSegments();
    cout << "输出：" << result1 << endl;
    cout << "解释：将 [4,2,4,5,1] 分成3段，" << endl;
    cout << "      最优方案为 [4,2], [4], [5,1]，最大段和 = 6" << endl;
    cout << "      预期答案：6  ← " << (result1 == 6 ? "✓ 正确" : "✗ 错误") << endl;

    // ----- 测试2：数列分段（边界情况） -----
    cout << "\n【测试2】数列分段——M = N（每段一个元素）" << endl;
    cout << "输入：" << endl;
    cout << "  5 5" << endl;
    cout << "  7 2 9 4 6" << endl;

    n = 5, m = 5;
    a[0] = 7; a[1] = 2; a[2] = 9; a[3] = 4; a[4] = 6;

    long long result2 = solveSegments();
    cout << "输出：" << result2 << endl;
    cout << "解释：每段只有一个元素，最大段和 = max(7,2,9,4,6) = 9" << endl;
    cout << "      预期答案：9  ← " << (result2 == 9 ? "✓ 正确" : "✗ 错误") << endl;

    // ----- 测试3：数列分段——M = 1（全部归一段） -----
    cout << "\n【测试3】数列分段——M = 1（全部归一段）" << endl;
    cout << "输入：" << endl;
    cout << "  4 1" << endl;
    cout << "  1 2 3 4" << endl;

    n = 4, m = 1;
    a[0] = 1; a[1] = 2; a[2] = 3; a[3] = 4;

    long long result3 = solveSegments();
    cout << "输出：" << result3 << endl;
    cout << "解释：只有一段，段和 = 1+2+3+4 = 10" << endl;
    cout << "      预期答案：10  ← " << (result3 == 10 ? "✓ 正确" : "✗ 错误") << endl;

    // ----- 测试4：月度开销 -----
    cout << "\n【测试4】月度开销" << endl;
    cout << "输入：" << endl;
    cout << "  7 5" << endl;
    cout << "  100" << endl;
    cout << "  400" << endl;
    cout << "  300" << endl;
    cout << "  100" << endl;
    cout << "  500" << endl;
    cout << "  101" << endl;
    cout << "  400" << endl;

    n = 7, m = 5;
    expense[0] = 100; expense[1] = 400; expense[2] = 300;
    expense[3] = 100; expense[4] = 500; expense[5] = 101;
    expense[6] = 400;

    long long result4 = solveMonthly();
    cout << "输出：" << result4 << endl;
    cout << "解释：划分方案 [100,400], [300,100], [500], [101], [400]" << endl;
    cout << "      最大月度开销 = max(500,400,500,101,400) = 500" << endl;
    cout << "      预期答案：500  ← " << (result4 == 500 ? "✓ 正确" : "✗ 错误") << endl;

    // ----- 测试5：月度开销（边界情况） -----
    cout << "\n【测试5】月度开销——M = N（每天一个 fajo 月）" << endl;
    cout << "输入：" << endl;
    cout << "  3 3" << endl;
    cout << "  200" << endl;
    cout << "  150" << endl;
    cout << "  300" << endl;

    n = 3, m = 3;
    expense[0] = 200; expense[1] = 150; expense[2] = 300;

    long long result5 = solveMonthly();
    cout << "输出：" << result5 << endl;
    cout << "解释：每天一个 fajo 月，最大开销 = max(200,150,300) = 300" << endl;
    cout << "      预期答案：300  ← " << (result5 == 300 ? "✓ 正确" : "✗ 错误") << endl;

    // ----- 测试6：压力测试（较大数据） -----
    cout << "\n【测试6】压力测试——N = 7, M = 3" << endl;
    cout << "输入：7 3, 数组：[10, 20, 30, 40, 50, 60, 70]" << endl;

    n = 7, m = 3;
    a[0] = 10; a[1] = 20; a[2] = 30;
    a[3] = 40; a[4] = 50; a[5] = 60; a[6] = 70;

    long long result6 = solveSegments();
    cout << "输出：" << result6 << endl;
    cout << "解释：将 [10,20,30,40,50,60,70] 分成3段，" << endl;
    cout << "      最优方案 [10,20,30,40], [50,60], [70]" << endl;
    cout << "      段和：100, 110, 70，最大 = 110" << endl;
    cout << "      预期答案：110  ← " << (result6 == 110 ? "✓ 正确" : "✗ 错误") << endl;

    cout << "\n══════════════════════════════════════════" << endl;
    cout << "  所有测试完成！" << endl;
    cout << "══════════════════════════════════════════" << endl;

    return 0;
}
