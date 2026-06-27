/**
 * lesson46_综合模拟二.cpp
 * CSP-J 备考课程 - 第46课：综合模拟（二）
 *
 * 内容：编程题专项训练
 * 涵盖：模拟算法、枚举算法、贪心算法、排序与查找
 *
 * 本文件包含：
 * 1. 高精度加法
 * 2. 日期计算与模拟（闰年判断、日期差值）
 * 3. 枚举优化（三数之和为零 - 双指针）
 * 4. 区间调度（贪心 - 活动选择）
 * 5. 二分答案（砍树问题）
 * 6. 综合演示与测试
 */

#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <climits>
using namespace std;

// ============================================================
// 一、高精度加法
// ============================================================

/**
 * 高精度加法：计算两个非负大整数的和
 * 使用字符串表示大整数，模拟竖式加法
 *
 * @param a 第一个非负大整数（字符串形式）
 * @param b 第二个非负大整数（字符串形式）
 * @return 两数之和（字符串形式）
 */
string highPrecisionAdd(string a, string b) {
    string result = "";
    int carry = 0;  // 进位
    int i = a.size() - 1, j = b.size() - 1;

    // 从最低位开始逐位相加
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';
        result += (sum % 10) + '0';  // 当前位
        carry = sum / 10;             // 进位
    }

    // 结果反转（因为是从低位到高位构建的）
    reverse(result.begin(), result.end());
    return result;
}

/**
 * 高精度加法演示
 */
void demoHighPrecisionAdd() {
    cout << "========== 高精度加法演示 ==========" << endl;

    string a = "12345678901234567890";
    string b = "98765432109876543210";
    cout << "  " << a << endl;
    cout << "+ " << b << endl;
    cout << "= " << highPrecisionAdd(a, b) << endl;

    // 更多测试用例
    cout << "\n更多测试:" << endl;
    cout << "999 + 1 = " << highPrecisionAdd("999", "1") << endl;
    cout << "0 + 0 = " << highPrecisionAdd("0", "0") << endl;
    cout << "123 + 456 = " << highPrecisionAdd("123", "456") << endl;

    cout << endl;
}

// ============================================================
// 二、日期计算与模拟
// ============================================================

/**
 * 判断闰年
 * 规则：能被4整除但不能被100整除，或能被400整除
 */
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

/**
 * 获取某年某月的天数
 */
int daysInMonth(int year, int month) {
    int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year)) return 29;
    return days[month];
}

/**
 * 计算从公元1年1月1日到指定日期的总天数
 * 使用"基准日"方法简化日期差计算
 *
 * @param year 年份
 * @param month 月份
 * @param day 日
 * @return 从公元1年1月1日起的总天数
 */
long long daysSinceEpoch(int year, int month, int day) {
    long long total = 0;

    // 累加整年天数
    for (int y = 1; y < year; y++) {
        total += isLeapYear(y) ? 366 : 365;
    }

    // 累加整月天数
    for (int m = 1; m < month; m++) {
        total += daysInMonth(year, m);
    }

    // 累加天数
    total += day;

    return total;
}

/**
 * 计算两个日期之间的天数差
 * 日期格式: YYYY-MM-DD (例如: 2024-01-01)
 * 假设 date1 <= date2
 */
long long daysBetweenDates(int y1, int m1, int d1, int y2, int m2, int d2) {
    long long t1 = daysSinceEpoch(y1, m1, d1);
    long long t2 = daysSinceEpoch(y2, m2, d2);
    return t2 - t1;
}

/**
 * 日期计算演示
 */
void demoDateCalculation() {
    cout << "========== 日期计算演示 ==========" << endl;

    // 闰年判断
    cout << "闰年判断:" << endl;
    cout << "  2000年: " << (isLeapYear(2000) ? "是闰年" : "不是闰年")
         << " (能被400整除)" << endl;
    cout << "  1900年: " << (isLeapYear(1900) ? "是闰年" : "不是闰年")
         << " (能被100整除但不能被400整除)" << endl;
    cout << "  2024年: " << (isLeapYear(2024) ? "是闰年" : "不是闰年")
         << " (能被4整除且不能被100整除)" << endl;
    cout << "  2023年: " << (isLeapYear(2023) ? "是闰年" : "不是闰年")
         << " (不能被4整除)" << endl;

    // 每月天数
    cout << "\n每月天数 (2024年):" << endl;
    for (int m = 1; m <= 12; m++) {
        cout << "  " << m << "月: " << daysInMonth(2024, m) << "天";
        if (m % 4 == 0) cout << endl;
    }

    // 日期差值计算
    cout << "\n日期差值计算:" << endl;
    cout << "  2024-01-01 到 2024-01-10: "
         << daysBetweenDates(2024, 1, 1, 2024, 1, 10) << " 天" << endl;
    cout << "  2023-01-01 到 2024-01-01: "
         << daysBetweenDates(2023, 1, 1, 2024, 1, 1) << " 天" << endl;
    cout << "  2000-01-01 到 2024-01-01: "
         << daysBetweenDates(2000, 1, 1, 2024, 1, 1) << " 天" << endl;

    // 日期模拟：给定起始日期和天数，求结束日期
    cout << "\n日期模拟 (2024-01-01 往后推100天):" << endl;
    int y = 2024, m = 1, d = 1;
    int addDays = 100;
    for (int i = 0; i < addDays; i++) {
        d++;
        if (d > daysInMonth(y, m)) {
            d = 1;
            m++;
            if (m > 12) {
                m = 1;
                y++;
            }
        }
    }
    printf("  2024-01-01 + 100天 = %04d-%02d-%02d\n", y, m, d);

    cout << endl;
}

// ============================================================
// 三、枚举优化：三数之和为零（排序 + 双指针）
// ============================================================

/**
 * 在数组中找到三个数使得它们的和为零（优化版）
 * 使用排序 + 双指针，时间复杂度 O(n^2)
 *
 * @param a 数组
 * @param n 数组长度
 * @return 是否存在这样的三元组
 */
bool threeSumToZero(int a[], int n) {
    sort(a, a + n);  // O(n log n) 排序

    // 枚举第一个数
    for (int i = 0; i < n - 2; i++) {
        // 剪枝：如果最小的数已经大于 0，不可能有三个数和为 0
        if (a[i] > 0) break;

        // 跳过重复的第一个数（不是必须，但可以减少重复查找）
        if (i > 0 && a[i] == a[i - 1]) continue;

        int left = i + 1, right = n - 1;
        while (left < right) {
            int sum = a[i] + a[left] + a[right];
            if (sum == 0) {
                return true;
            } else if (sum < 0) {
                left++;   // 和太小，左指针右移增大和
            } else {
                right--;  // 和太大，右指针左移减小和
            }
        }
    }
    return false;
}

/**
 * 枚举优化演示
 */
void demoEnumerationOptimization() {
    cout << "========== 枚举优化: 三数之和为零 ==========" << endl;

    // 测试用例1：存在解 {-1, 0, 1} 或 {-1, -1, 2}
    int arr1[] = {-1, 0, 1, 2, -1, -4};
    int n1 = 6;
    cout << "数组 {-1, 0, 1, 2, -1, -4}: "
         << (threeSumToZero(arr1, n1) ? "存在三个数和为零 YES" : "不存在 NO")
         << endl;

    // 测试用例2：不存在解
    int arr2[] = {1, 2, 3, 4, 5};
    int n2 = 5;
    cout << "数组 {1, 2, 3, 4, 5}: "
         << (threeSumToZero(arr2, n2) ? "存在三个数和为零 YES" : "不存在 NO")
         << endl;

    // 测试用例3：全零
    int arr3[] = {0, 0, 0, 0};
    int n3 = 4;
    cout << "数组 {0, 0, 0, 0}: "
         << (threeSumToZero(arr3, n3) ? "存在三个数和为零 YES" : "不存在 NO")
         << endl;

    // 演示朴素枚举 vs 优化枚举的时间复杂度
    cout << "\n时间复杂度分析:" << endl;
    cout << "  朴素三重循环: O(n^3) - n=1000 时约 10^9 次运算 (超时)" << endl;
    cout << "  排序+双指针: O(n^2) - n=1000 时约 10^6 次运算 (可接受)" << endl;

    cout << endl;
}

// ============================================================
// 四、区间调度（贪心 - 活动选择）
// ============================================================

/**
 * 活动结构体
 */
struct Activity {
    int start;  // 开始时间
    int end;    // 结束时间
};

/**
 * 比较函数：按结束时间升序排序
 * 这是贪心策略的关键——优先选择结束早的活动
 */
bool cmpActivity(const Activity& a, const Activity& b) {
    return a.end < b.end;
}

/**
 * 活动选择问题（区间调度）
 * 贪心策略：每次选择结束时间最早且不与已选活动冲突的活动
 *
 * @param activities 活动数组
 * @param n 活动数量
 * @return 最多可选的活动数量
 */
int maxActivities(Activity activities[], int n) {
    // 按结束时间升序排序
    sort(activities, activities + n, cmpActivity);

    int count = 0;
    int lastEnd = -1;  // 上一个选中活动的结束时间

    for (int i = 0; i < n; i++) {
        if (activities[i].start >= lastEnd) {
            count++;
            lastEnd = activities[i].end;
        }
    }

    return count;
}

/**
 * 区间调度演示
 */
void demoIntervalScheduling() {
    cout << "========== 区间调度（贪心）演示 ==========" << endl;

    Activity acts[] = {
        {1, 4},
        {3, 5},
        {0, 6},
        {5, 7},
        {3, 8},
        {5, 9},
        {6, 10},
        {8, 11},
        {8, 12},
        {2, 13},
        {12, 14}
    };
    int n = sizeof(acts) / sizeof(acts[0]);

    cout << "活动列表 (开始, 结束):" << endl;
    for (int i = 0; i < n; i++) {
        cout << "  活动" << i + 1 << ": (" << acts[i].start
             << ", " << acts[i].end << ")" << endl;
    }

    int result = maxActivities(acts, n);
    cout << "最多可选活动数: " << result << endl;

    // 显示选中的活动
    cout << "\n选中的活动:" << endl;
    sort(acts, acts + n, cmpActivity);
    int count = 0, lastEnd = -1;
    for (int i = 0; i < n; i++) {
        if (acts[i].start >= lastEnd) {
            count++;
            cout << "  " << count << ". 开始=" << acts[i].start
                 << ", 结束=" << acts[i].end << endl;
            lastEnd = acts[i].end;
        }
    }

    // 证明贪心正确性：与错误策略对比
    cout << "\n贪心策略正确性说明:" << endl;
    cout << "  为什么按开始时间排序不行?" << endl;
    cout << "  反例: [1,10], [2,3], [4,5]" << endl;
    cout << "  按开始时间 → 选[1,10]，只能选1个" << endl;
    cout << "  按结束时间 → 选[2,3], [4,5]，能选2个 (最优)" << endl;

    cout << endl;
}

// ============================================================
// 五、二分答案（砍树问题）
// ============================================================

/**
 * 判断在锯子高度为 H 时，能否获得至少 M 长度的木材
 *
 * @param heights 每棵树的高度数组
 * @param n 树的数量
 * @param H 锯子设置高度
 * @param M 需要的木材总长度
 * @return true 如果可以获得至少 M 的木材
 */
bool canGetEnoughWood(int heights[], int n, int H, long long M) {
    long long total = 0;
    for (int i = 0; i < n; i++) {
        if (heights[i] > H) {
            total += heights[i] - H;
        }
        // 提前剪枝
        if (total >= M) return true;
    }
    return total >= M;
}

/**
 * 二分答案求解最高锯子高度
 *
 * 单调性: 锯子越高 → 获得的木材越少
 * 求满足"获得木材 >= M"条件下，锯子高度的最大值
 *
 * @param heights 树的高度数组
 * @param n 树的数量
 * @param M 需要的木材总长度
 * @return 锯子的最高设置高度
 */
int maxSawHeight(int heights[], int n, long long M) {
    // 找出最高的树，确定二分范围
    int maxH = 0;
    for (int i = 0; i < n; i++) {
        if (heights[i] > maxH) maxH = heights[i];
    }

    int left = 0, right = maxH;
    int ans = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;  // 防止溢出的写法
        if (canGetEnoughWood(heights, n, mid, M)) {
            ans = mid;
            left = mid + 1;  // 尝试更大的高度
        } else {
            right = mid - 1;  // 降低高度
        }
    }

    return ans;
}

/**
 * 二分答案演示
 */
void demoBinarySearchAnswer() {
    cout << "========== 二分答案（砍树问题）演示 ==========" << endl;

    // 测试用例1: 标准示例
    int trees1[] = {20, 15, 10, 17};
    int n1 = 4;
    long long M1 = 7;
    int H1 = maxSawHeight(trees1, n1, M1);
    cout << "树高: {20, 15, 10, 17}, 需要木材: 7" << endl;
    cout << "最高锯子高度: " << H1 << endl;
    cout << "验证 - 当 H=" << H1 << "时获得的木材: ";
    long long wood = 0;
    for (int i = 0; i < n1; i++) {
        if (trees1[i] > H1) {
            wood += trees1[i] - H1;
            cout << trees1[i] - H1 << " ";
        } else {
            cout << "0 ";
        }
    }
    cout << "= " << wood << endl;

    // 测试用例2: 需要木材为0时，可以设置到最高树的高度
    cout << "\n树高: {5, 4, 3}, 需要木材: 0" << endl;
    int trees2[] = {5, 4, 3};
    cout << "最高锯子高度: " << maxSawHeight(trees2, 3, 0) << " (刚好不砍任何树)" << endl;

    // 测试用例3: 需要大量木材，必须砍低
    int trees3[] = {10, 10, 10};
    cout << "\n树高: {10, 10, 10}, 需要木材: 25" << endl;
    int H3 = maxSawHeight(trees3, 3, 25);
    cout << "最高锯子高度: " << H3 << " (需要砍很多，锯子必须低)" << endl;

    // 二分过程演示
    cout << "\n二分过程演示 (树高{20,15,10,17}, M=7):" << endl;
    cout << "  left=0, right=20" << endl;
    int demoTrees[] = {20, 15, 10, 17};
    for (int mid : {10, 15, 17, 16}) {
        cout << "  mid=" << mid << ": "
             << (canGetEnoughWood(demoTrees, 4, mid, 7) ? "满足 → 提高left" : "不满足 → 降低right")
             << endl;
    }
    cout << "  最终 ans = 15" << endl;

    cout << endl;
}

// ============================================================
// 六、二分查找模板
// ============================================================

/**
 * 标准二分查找：在有序数组中查找目标值的下标
 * 找不到返回 -1
 */
int binarySearch(int arr[], int n, int target) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

/**
 * 二分查找：找第一个 >= target 的位置（lower_bound）
 */
int lowerBound(int arr[], int n, int target) {
    int left = 0, right = n;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] >= target) right = mid;
        else left = mid + 1;
    }
    return left;  // 返回第一个 >= target 的位置
}

/**
 * 二分查找演示
 */
void demoBinarySearch() {
    cout << "========== 二分查找演示 ==========" << endl;

    int sorted[] = {1, 3, 5, 7, 9, 11, 13, 15};
    int n = 8;

    cout << "有序数组: ";
    for (int i = 0; i < n; i++) cout << sorted[i] << " ";
    cout << endl;

    // 标准二分查找
    for (int target : {7, 10, 1, 15}) {
        int idx = binarySearch(sorted, n, target);
        if (idx != -1)
            cout << "  查找 " << target << ": 下标=" << idx << " (值=" << sorted[idx] << ")" << endl;
        else
            cout << "  查找 " << target << ": 未找到" << endl;
    }

    // lower_bound 示例
    cout << "\nlower_bound 示例:" << endl;
    for (int target : {6, 8, 0, 16}) {
        int pos = lowerBound(sorted, n, target);
        cout << "  第一个 >= " << target << " 的位置: " << pos;
        if (pos < n) cout << " (值=" << sorted[pos] << ")";
        else cout << " (越界)";
        cout << endl;
    }

    cout << endl;
}

// ============================================================
// 七、排序算法对比
// ============================================================

/**
 * 冒泡排序 O(n^2)
 */
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;  // 优化：如果某趟没有交换，说明已经有序
    }
}

/**
 * 选择排序 O(n^2)
 */
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        if (minIdx != i) swap(arr[i], arr[minIdx]);
    }
}

/**
 * 排序算法对比演示
 */
void demoSortingAlgorithms() {
    cout << "========== 排序算法对比 ==========" << endl;

    int original[] = {64, 34, 25, 12, 22, 11, 90};
    int n = 7;
    cout << "原始数组: ";
    for (int i = 0; i < n; i++) cout << original[i] << " ";
    cout << endl;

    // 冒泡排序
    int arr1[7];
    copy(original, original + n, arr1);
    bubbleSort(arr1, n);
    cout << "冒泡排序: ";
    for (int i = 0; i < n; i++) cout << arr1[i] << " ";
    cout << "(O(n^2), 稳定排序, 每趟将最大值冒泡到最后)" << endl;

    // 选择排序
    int arr2[7];
    copy(original, original + n, arr2);
    selectionSort(arr2, n);
    cout << "选择排序: ";
    for (int i = 0; i < n; i++) cout << arr2[i] << " ";
    cout << "(O(n^2), 不稳定排序, 每趟选最小值放到前面)" << endl;

    // STL sort (快速排序变体)
    int arr3[7];
    copy(original, original + n, arr3);
    sort(arr3, arr3 + n);
    cout << "STL sort: ";
    for (int i = 0; i < n; i++) cout << arr3[i] << " ";
    cout << "(O(n log n), 推荐在竞赛中使用)" << endl;

    cout << endl;
}

// ============================================================
// 八、部分分策略与骗分技巧演示
// ============================================================

/**
 * 演示"打表法"：对于输入范围小的题目，可以预计算答案
 *
 * 场景：输入 n (1<=n<=10)，输出第 n 个斐波那契数
 */
void demoTableLookup() {
    cout << "========== 部分分技巧: 打表法 ==========" << endl;

    // 预计算的斐波那契数列（下标从0开始）
    int fib[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89};

    cout << "对于 n <= 10 的斐波那契问题，可以直接打表：" << endl;
    for (int n = 0; n <= 10; n++) {
        cout << "  fib(" << n << ") = " << fib[n] << endl;
    }
    cout << "这是一种有效的部分分策略，尤其对于小范围数据" << endl;
    cout << endl;
}

/**
 * 演示"特判法"：针对特殊情况进行特判拿分
 */
void demoSpecialCases() {
    cout << "========== 部分分技巧: 特判法 ==========" << endl;

    cout << "示例场景: 判断一个字符串是否回文" << endl;
    cout << "特判1: 长度为1的字符串一定是回文 → 直接输出 YES" << endl;
    cout << "特判2: 长度为0的字符串 → 视题目要求" << endl;

    char test1[] = "a";
    char test2[] = "ab";
    char test3[] = "aba";

    cout << "\"" << test1 << "\" 长度=" << strlen(test1);
    if (strlen(test1) == 1) cout << " → 特判: 单字符必为回文";
    cout << endl;

    cout << "\"" << test2 << "\": ";
    bool isPal = true;
    int len = strlen(test2);
    for (int i = 0; i < len / 2; i++) {
        if (test2[i] != test2[len - 1 - i]) {
            isPal = false;
            break;
        }
    }
    cout << (isPal ? "是回文" : "不是回文") << endl;

    cout << "\"" << test3 << "\": ";
    isPal = true;
    len = strlen(test3);
    for (int i = 0; i < len / 2; i++) {
        if (test3[i] != test3[len - 1 - i]) {
            isPal = false;
            break;
        }
    }
    cout << (isPal ? "是回文" : "不是回文") << endl;

    cout << endl;
}

// ============================================================
// 九、主函数
// ============================================================

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cout << "========================================================" << endl;
    cout << "  CSP-J 第46课：综合模拟（二）— 编程题专项训练" << endl;
    cout << "========================================================" << endl;
    cout << endl;

    // 一、高精度加法
    demoHighPrecisionAdd();

    // 二、日期计算
    demoDateCalculation();

    // 三、枚举优化
    demoEnumerationOptimization();

    // 四、区间调度（贪心）
    demoIntervalScheduling();

    // 五、二分答案
    demoBinarySearchAnswer();

    // 六、二分查找
    demoBinarySearch();

    // 七、排序算法对比
    demoSortingAlgorithms();

    // 八、部分分技巧
    demoTableLookup();
    demoSpecialCases();

    // 附加：综合测试
    cout << "========================================================" << endl;
    cout << "  综合测试：4道编程题 AC 代码正确性验证" << endl;
    cout << "========================================================" << endl;

    // 测试1：日期差值
    long long diff = daysBetweenDates(2024, 1, 1, 2024, 1, 10);
    cout << "测试1 [日期差值] 2024-01-01 到 2024-01-10: "
         << diff << " 天 (预期: 9) " << (diff == 9 ? "✓" : "✗") << endl;

    // 测试2：三数之和为零
    int testArr[] = {-1, 0, 1, 2, -1, -4};
    bool hasTriplet = threeSumToZero(testArr, 6);
    cout << "测试2 [三数之和为零] {-1,0,1,2,-1,-4}: "
         << (hasTriplet ? "YES" : "NO") << " (预期: YES) "
         << (hasTriplet ? "✓" : "✗") << endl;

    // 测试3：活动选择
    Activity testActs[] = {{1, 4}, {3, 5}, {0, 6}, {5, 7}, {3, 8}};
    int maxAct = maxActivities(testActs, 5);
    cout << "测试3 [活动选择] 5个活动: " << maxAct
         << " 个可选 (预期: 2) " << (maxAct == 2 ? "✓" : "✗") << endl;

    // 测试4：二分答案
    int testTrees[] = {20, 15, 10, 17};
    int maxH = maxSawHeight(testTrees, 4, 7);
    cout << "测试4 [砍树问题] 需要7单位木材: H=" << maxH
         << " (预期: 15) " << (maxH == 15 ? "✓" : "✗") << endl;

    cout << "\n========================================================" << endl;
    cout << "  程序演示完毕！所有模块均已完成。" << endl;
    cout << "  建议：将各模块的 AC 代码模板记熟，" << endl;
    cout << "  考场上可以直接套用，节省编码时间。" << endl;
    cout << "========================================================" << endl;

    return 0;
}
