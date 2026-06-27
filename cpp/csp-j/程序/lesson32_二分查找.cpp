/*
 * Lesson 32: 二分查找
 *
 * 本课内容：
 * 1. 二分查找 while(l <= r) 写法（经典闭区间写法，返回目标下标）
 * 2. 二分查找 while(l < r) 写法（半开区间写法，常用于找边界）
 * 3. lower_bound() 和 upper_bound() 标准库函数用法
 * 4. 二分答案：砍树问题（在答案范围上二分查找满足条件的最大值）
 * 5. 浮点数二分：求平方根（通过精度控制终止条件）
 *
 * 核心思想：
 * - 二分查找适用于"有序"序列
 * - 每次将搜索范围缩小一半，时间复杂度 O(log n)
 * - 二分答案适用于"单调性"问题：答案具有单调性，可以在答案空间上二分
 *
 * 时间复杂度：O(log n)
 * 空间复杂度：O(1)（迭代版）或 O(log n)（递归版）
 *
 * 前置条件：
 * - 普通二分查找：数组必须有序
 * - 二分答案：答案空间必须具有单调性
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <cmath>
#include <iomanip>

using namespace std;

// ==================== 1. 二分查找 while(l <= r) 写法 ====================

/**
 * 二分查找：闭区间写法 while(l <= r)
 *
 * 算法思想：
 * - 维护搜索区间 [l, r]，左右都是闭区间
 * - 每次取中间位置 mid = l + (r - l) / 2（防止溢出）
 * - 如果 a[mid] == target，找到目标，返回下标
 * - 如果 a[mid] < target，说明目标在右半部分，l = mid + 1
 * - 如果 a[mid] > target，说明目标在左半部分，r = mid - 1
 * - 当 l > r 时，区间为空，查找失败，返回 -1
 *
 * 特点：
 * - 每次都能明确排除 mid 位置（l = mid+1 或 r = mid-1）
 * - 循环条件是 l <= r，表示区间非空
 * - 适合查找确切值是否存在
 *
 * 参数：
 *   a[]    - 已排序的升序数组
 *   n      - 数组长度
 *   target - 要查找的目标值
 * 返回值：
 *   找到则返回目标值的下标，否则返回 -1
 */
int binarySearch(const int a[], int n, int target) {
    // 搜索区间为 [l, r]，左右都是闭区间
    int l = 0, r = n - 1;

    // 当 l <= r 时，区间非空，继续搜索
    // 当 l > r 时，区间为空，搜索失败
    while (l <= r) {
        // 计算中间位置
        // 使用 l + (r - l) / 2 而不是 (l + r) / 2
        // 是为了防止 l + r 溢出（虽然 int 不太可能溢出，但这是好习惯）
        int mid = l + (r - l) / 2;

        if (a[mid] == target) {
            return mid;  // 找到目标，返回下标
        } else if (a[mid] < target) {
            // 目标在右半部分，缩小左边界
            // 因为 a[mid] != target，所以 mid 可以排除
            l = mid + 1;
        } else {
            // 目标在左半部分，缩小右边界
            r = mid - 1;
        }
    }

    // 搜索区间为空，未找到目标
    return -1;
}

/**
 * 二分查找 while(l <= r)：查找第一个等于 target 的位置（含重复元素）
 *
 * 当数组中有重复元素时，此函数返回最左边的那个 target 的下标
 * 实现方式：找到 target 后不立即返回，而是继续向左搜索
 */
int binarySearchFirst(const int a[], int n, int target) {
    int l = 0, r = n - 1;
    int result = -1;  // 记录找到的位置

    while (l <= r) {
        int mid = l + (r - l) / 2;

        if (a[mid] == target) {
            result = mid;     // 记录当前找到的位置
            r = mid - 1;      // 继续在左半部分查找（找更靠前的）
        } else if (a[mid] < target) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    return result;
}

/**
 * 二分查找 while(l <= r)：查找最后一个等于 target 的位置（含重复元素）
 */
int binarySearchLast(const int a[], int n, int target) {
    int l = 0, r = n - 1;
    int result = -1;

    while (l <= r) {
        int mid = l + (r - l) / 2;

        if (a[mid] == target) {
            result = mid;     // 记录当前找到的位置
            l = mid + 1;      // 继续在右半部分查找（找更靠后的）
        } else if (a[mid] < target) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    return result;
}

// ==================== 2. 二分查找 while(l < r) 写法 ====================

/**
 * 二分查找：半开区间写法 while(l < r)
 *
 * 用于查找"第一个 >= target"的位置（即 lower_bound 的手动实现）
 *
 * 算法思想：
 * - 维护搜索区间 [l, r)，左闭右开
 * - 每次取 mid = l + (r - l) / 2
 * - 如果 a[mid] >= target，说明答案在 [l, mid] 中，r = mid
 * - 如果 a[mid] < target，说明答案在 [mid+1, r) 中，l = mid + 1
 * - 当 l == r 时，区间收缩到一个点，l 就是答案
 *
 * 特点：
 * - l 始终指向可能满足条件的位置
 * - 循环结束后 l 就是第一个 >= target 的位置
 * - 如果所有元素都 < target，l 会等于 n（表示不存在）
 *
 * 与 while(l <= r) 的区别：
 * - while(l <= r) 用于查找确切值，mid 被明确排除
 * - while(l < r) 用于查找边界，mid 可能被保留在区间中
 */
int lowerBoundManual(const int a[], int n, int target) {
    int l = 0, r = n;  // 区间 [l, r)，r 是数组长度（开区间）

    // 当 l < r 时，区间至少包含一个元素
    while (l < r) {
        int mid = l + (r - l) / 2;

        if (a[mid] >= target) {
            // a[mid] 满足条件，mid 可能是答案
            // 将右边界缩小到 mid（包含 mid）
            r = mid;
        } else {
            // a[mid] 不满足条件，mid 不可能是答案
            // 将左边界移动到 mid+1（排除 mid）
            l = mid + 1;
        }
    }

    // 循环结束时 l == r
    // 检查 l 是否在有效范围内且 a[l] >= target
    if (l < n && a[l] >= target) {
        return l;
    }
    return -1;  // 未找到满足条件的元素
}

/**
 * 手动实现 upper_bound：查找"第一个 > target"的位置
 */
int upperBoundManual(const int a[], int n, int target) {
    int l = 0, r = n;

    while (l < r) {
        int mid = l + (r - l) / 2;

        if (a[mid] > target) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }

    if (l < n && a[l] > target) {
        return l;
    }
    return -1;
}

// ==================== 3. 二分答案：砍树问题 ====================

/**
 * 砍树问题（经典二分答案）
 *
 * 问题描述：
 * 有 n 棵树，每棵树的高度为 h[i]。
 * 伐木工需要获得至少 M 米长的木材。
 * 如果将锯片设置在高度 H，那么他能从第 i 棵树获得 max(0, h[i] - H) 米木材。
 * 问：在获得至少 M 米木材的前提下，锯片高度 H 最大可以设置多高？
 *
 * 解法：二分答案
 * - 答案范围：[0, 最高的树的高度]
 * - 单调性：如果 H1 < H2，那么在 H1 能获得的木材 >= 在 H2 能获得的木材
 *           即"锯片越高，获得的木材越少"
 * - 目标：在获得木材 >= M 的条件下，找到最大的 H
 *
 * 时间复杂度：O(n log maxH)
 */

/**
 * 检查在锯片高度 H 下，能否获得至少 M 米木材
 *
 * @param heights 每棵树的高度数组
 * @param n       树的数量
 * @param H       锯片高度
 * @param M       需要的木材总长度
 * @return        获得的木材总量 >= M 则返回 true
 */
bool canGetEnoughWood(const int heights[], int n, long long H, long long M) {
    long long total = 0;  // 获得的木材总量

    for (int i = 0; i < n; i++) {
        if (heights[i] > H) {
            total += (heights[i] - H);
        }
        // 提前退出：如果已经满足要求，不再继续计算
        if (total >= M) {
            return true;
        }
    }

    return total >= M;
}

/**
 * 砍树问题的二分答案求解
 *
 * @param heights 每棵树的高度数组
 * @param n       树的数量
 * @param M       需要的木材总长度
 * @return        锯片可以设置的最大高度
 */
int solveWoodCutting(const int heights[], int n, long long M) {
    // 答案范围：[0, maxHeight]
    // H=0 时获得所有树的高度之和（最多木材）
    // H=maxHeight 时获得 0 木材
    int l = 0, r = 0;

    // 找到最高的树的高度，作为上界
    for (int i = 0; i < n; i++) {
        if (heights[i] > r) r = heights[i];
    }

    int answer = 0;  // 记录答案

    // 二分查找：在 [l, r] 中找满足条件的最大 H
    // 使用 while(l <= r) 写法，结合记录答案的方式
    while (l <= r) {
        int mid = l + (r - l) / 2;

        if (canGetEnoughWood(heights, n, mid, M)) {
            // mid 高度能满足要求，记录答案并尝试更高的高度
            answer = mid;
            l = mid + 1;  // 尝试更大的 H（更高的锯片）
        } else {
            // mid 高度无法满足要求，需要降低锯片
            r = mid - 1;
        }
    }

    return answer;
}

// ==================== 4. 浮点数二分：求平方根 ====================

/**
 * 浮点数二分：求 x 的平方根
 *
 * 问题：给定一个正实数 x，求 sqrt(x)，误差不超过 1e-9
 *
 * 解法：浮点数二分
 * - 答案范围：[0, x]（当 x >= 1）或 [0, 1]（当 x < 1 时，sqrt(x) > x）
 * - 单调性：函数 f(mid) = mid² 是单调递增的
 * - 二分直到区间长度足够小（精度满足要求）
 *
 * 浮点数二分与整数二分的区别：
 * - 整数二分用 while(l <= r) 或 while(l < r)
 * - 浮点数二分用 while(r - l > eps)，其中 eps 是精度要求
 * - 浮点数二分中 l 和 r 直接用 mid 赋值（不需要 ±1）
 *
 * @param x   要求平方根的正实数
 * @param eps 精度要求（如 1e-9）
 * @return    x 的平方根近似值
 */
double sqrtBinarySearch(double x, double eps = 1e-9) {
    if (x < 0) return -1;  // 负数没有实数平方根
    if (x == 0) return 0;

    // 确定搜索范围
    // 当 x >= 1 时，sqrt(x) 在 [1, x] 之间
    // 当 0 < x < 1 时，sqrt(x) 在 [x, 1] 之间
    double l, r;
    if (x >= 1.0) {
        l = 1.0;
        r = x;
    } else {
        l = x;
        r = 1.0;
    }

    // 浮点数二分：当区间长度 > eps 时继续
    // 固定迭代次数也是常用方法：for(int i=0; i<100; i++)
    while (r - l > eps) {
        double mid = (l + r) / 2.0;

        if (mid * mid <= x) {
            // mid 的平方小于等于 x，说明 sqrt(x) >= mid
            // 答案在 [mid, r] 中
            l = mid;
        } else {
            // mid 的平方大于 x，说明 sqrt(x) < mid
            // 答案在 [l, mid] 中
            r = mid;
        }
    }

    // 返回区间中点作为近似值
    return (l + r) / 2.0;
}

/**
 * 浮点数二分求平方根 — 固定迭代次数版本
 *
 * 此版本通过固定迭代次数来控制精度，避免了浮点数比较的潜在问题
 * 迭代 100 次可以将区间缩小到原来的 1/2^100，精度远超 double 类型
 */
double sqrtFixedIter(double x) {
    if (x < 0) return -1;
    if (x == 0) return 0;

    double l = 0, r = max(1.0, x);  // 确保 r >= sqrt(x)

    // 迭代 100 次，精度约为 2^-100 ≈ 7.9e-31
    for (int i = 0; i < 100; i++) {
        double mid = (l + r) / 2.0;
        if (mid * mid <= x) {
            l = mid;
        } else {
            r = mid;
        }
    }

    return (l + r) / 2.0;
}

// ==================== 工具函数 ====================

/**
 * 打印数组
 */
void printArray(const int a[], int n, const string& title) {
    cout << title << ": [";
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << ", ";
        cout << a[i];
    }
    cout << "]" << endl;
}

// ==================== 主函数 ====================

int main() {
    cout << "============================================" << endl;
    cout << "  Lesson 32: 二分查找" << endl;
    cout << "============================================" << endl;
    cout << endl;

    // ---------- 1. 二分查找 while(l <= r) ----------
    cout << "---------- 1. 二分查找 while(l <= r) 经典写法 ----------" << endl;
    {
        // 有序数组
        int arr[] = {2, 5, 8, 12, 16, 23, 38, 45, 56, 67, 78, 89};
        int n = sizeof(arr) / sizeof(arr[0]);

        printArray(arr, n, "有序数组");

        cout << endl << "查找测试：" << endl;
        int test_targets[] = {23, 45, 2, 89, 1, 100, 5};
        int m = sizeof(test_targets) / sizeof(test_targets[0]);

        for (int i = 0; i < m; i++) {
            int target = test_targets[i];
            int index = binarySearch(arr, n, target);

            if (index != -1) {
                cout << "  查找 " << setw(3) << target << " → 找到！下标为 "
                     << index << "，值为 " << arr[index] << endl;
            } else {
                cout << "  查找 " << setw(3) << target << " → 未找到" << endl;
            }
        }

        // 查找过程可视化
        cout << endl << "查找过程详解（以 target=23 为例）：" << endl;
        cout << "  数组：[2, 5, 8, 12, 16, 23, 38, 45, 56, 67, 78, 89]" << endl;
        cout << "  1. l=0, r=11, mid=5, arr[5]=23 == 23，找到！返回下标 5" << endl;
        cout << "  只需 1 次比较！而线性查找需要 6 次比较。" << endl;
    }
    cout << endl;

    // ---------- 2. 查找重复元素的第一个和最后一个位置 ----------
    cout << "---------- 2. 含重复元素时查找第一个和最后一个位置 ----------" << endl;
    {
        // 含有重复元素的有序数组
        int arr[] = {1, 2, 2, 2, 3, 3, 4, 5, 5, 5, 5, 6, 7};
        int n = sizeof(arr) / sizeof(arr[0]);

        printArray(arr, n, "含重复元素的有序数组");

        // 查找 2 的第一个和最后一个位置
        int first2 = binarySearchFirst(arr, n, 2);
        int last2 = binarySearchLast(arr, n, 2);
        cout << "值 2 的位置范围：[" << first2 << ", " << last2 << "]，共 "
             << (last2 - first2 + 1) << " 个" << endl;

        // 查找 5 的第一个和最后一个位置
        int first5 = binarySearchFirst(arr, n, 5);
        int last5 = binarySearchLast(arr, n, 5);
        cout << "值 5 的位置范围：[" << first5 << ", " << last5 << "]，共 "
             << (last5 - first5 + 1) << " 个" << endl;

        // 查找 3
        int first3 = binarySearchFirst(arr, n, 3);
        int last3 = binarySearchLast(arr, n, 3);
        cout << "值 3 的位置范围：[" << first3 << ", " << last3 << "]，共 "
             << (last3 - first3 + 1) << " 个" << endl;

        cout << endl << "应用场景：" << endl;
        cout << "  统计有序数组中某个值的出现次数：" << endl;
        cout << "  count = lastIndex - firstIndex + 1（O(log n) 时间）" << endl;
    }
    cout << endl;

    // ---------- 3. lower_bound 和 upper_bound ----------
    cout << "---------- 3. lower_bound() 和 upper_bound() 标准库函数 ----------" << endl;
    {
        int arr[] = {1, 3, 3, 5, 7, 7, 7, 9, 11, 11};
        int n = sizeof(arr) / sizeof(arr[0]);

        printArray(arr, n, "有序数组");

        cout << endl;
        cout << "lower_bound(arr, arr+n, target)：返回「第一个 >= target」的位置" << endl;
        cout << "upper_bound(arr, arr+n, target)：返回「第一个 > target」的位置" << endl;
        cout << endl;

        // 测试不同的 target 值
        int targets[] = {3, 5, 7, 8, 11, 0, 15, 1};
        int m = sizeof(targets) / sizeof(targets[0]);

        cout << setw(8) << "target"
             << setw(18) << "lower_bound 位置"
             << setw(10) << "对应值"
             << setw(18) << "upper_bound 位置"
             << setw(10) << "对应值"
             << setw(8) << "个数"
             << endl;
        cout << string(72, '-') << endl;

        for (int i = 0; i < m; i++) {
            int t = targets[i];

            // lower_bound: 返回第一个 >= t 的位置
            int* lb = lower_bound(arr, arr + n, t);
            int lb_idx = lb - arr;  // 转换为下标

            // upper_bound: 返回第一个 > t 的位置
            int* ub = upper_bound(arr, arr + n, t);
            int ub_idx = ub - arr;

            // 计算值 t 在数组中出现的次数
            int count = ub_idx - lb_idx;

            cout << setw(8) << t
                 << setw(18) << lb_idx
                 << setw(10) << (lb_idx < n ? to_string(arr[lb_idx]) : "越界")
                 << setw(18) << ub_idx
                 << setw(10) << (ub_idx < n ? to_string(arr[ub_idx]) : "越界")
                 << setw(8) << count
                 << endl;
        }

        cout << endl;
        cout << "重要结论：" << endl;
        cout << "  1. 值 t 的出现次数 = upper_bound - lower_bound" << endl;
        cout << "  2. 如果 lower_bound == upper_bound，说明 t 不在数组中" << endl;
        cout << "  3. 如果 lower_bound == n，说明所有元素都 < t（越界）" << endl;
        cout << "  4. 如果 lower_bound == 0 且 arr[0] > t，说明所有元素都 > t" << endl;
    }
    cout << endl;

    // ---------- 4. while(l < r) 手动实现 lower_bound ----------
    cout << "---------- 4. while(l < r) 写法手动实现 lower_bound ----------" << endl;
    {
        int arr[] = {1, 3, 3, 5, 7, 7, 7, 9, 11, 11};
        int n = sizeof(arr) / sizeof(arr[0]);

        printArray(arr, n, "有序数组");

        cout << endl;
        cout << "对比手动实现与标准库函数：" << endl;
        cout << endl;
        cout << setw(10) << "target"
             << setw(18) << "手动 lower_bound"
             << setw(18) << "标准 lower_bound"
             << setw(18) << "手动 upper_bound"
             << setw(18) << "标准 upper_bound"
             << endl;
        cout << string(82, '-') << endl;

        int targets[] = {1, 3, 5, 7, 9, 11, 0, 15};
        for (int i = 0; i < 8; i++) {
            int t = targets[i];

            int manual_lb = lowerBoundManual(arr, n, t);
            int std_lb = lower_bound(arr, arr + n, t) - arr;
            int manual_ub = upperBoundManual(arr, n, t);
            int std_ub = upper_bound(arr, arr + n, t) - arr;

            cout << setw(10) << t
                 << setw(15) << (manual_lb == -1 ? -1 : manual_lb)
                 << setw(18) << std_lb
                 << setw(15) << (manual_ub == -1 ? -1 : manual_ub)
                 << setw(18) << std_ub
                 << endl;
        }
    }
    cout << endl;

    // ---------- 5. 二分答案：砍树问题 ----------
    cout << "---------- 5. 二分答案：砍树问题 ----------" << endl;
    cout << "问题：有 N 棵树，需要至少 M 米木材，锯片高度 H 最大可以是多少？" << endl;
    cout << endl;

    {
        // 示例数据
        int heights[] = {20, 15, 10, 17};
        int n = sizeof(heights) / sizeof(heights[0]);
        long long M = 7;  // 需要 7 米木材

        cout << "树的高度：";
        printArray(heights, n, "");
        cout << "需要的木材：至少 " << M << " 米" << endl;
        cout << endl;

        // 分析
        cout << "分析：不同的锯片高度 H 对应可获得的木材量" << endl;
        cout << setw(8) << "锯片H" << " | 获得的木材计算过程" << setw(20) << " | 总木材" << endl;
        cout << string(55, '-') << endl;
        for (int H = 20; H >= 10; H--) {
            long long total = 0;
            cout << setw(6) << H << "  | ";
            for (int i = 0; i < n; i++) {
                int wood = max(0, heights[i] - H);
                total += wood;
                cout << "树" << i + 1 << ":" << setw(2) << wood << "  ";
            }
            cout << " | " << setw(3) << total;
            if (total >= M) cout << "  ← 满足要求！";
            cout << endl;
        }

        // 求解
        int bestH = solveWoodCutting(heights, n, M);
        cout << endl;
        cout << "二分答案求解结果：最大锯片高度 H = " << bestH << endl;

        // 验证
        long long wood = 0;
        for (int i = 0; i < n; i++) {
            wood += max(0, heights[i] - bestH);
        }
        cout << "验证：在 H=" << bestH << " 时可获得 " << wood << " 米木材";
        cout << (wood >= M ? "，满足要求" : "，不满足要求") << endl;

        // 如果 H 再高 1
        wood = 0;
        for (int i = 0; i < n; i++) {
            wood += max(0, heights[i] - (bestH + 1));
        }
        cout << "      在 H=" << bestH + 1 << " 时可获得 " << wood << " 米木材";
        cout << (wood >= M ? "，满足要求" : "，不满足要求（说明 " + to_string(bestH) + " 确实是最大值）") << endl;

        cout << endl;
        cout << "二分答案解题步骤总结：" << endl;
        cout << "  1. 确定答案范围 [L, R]（锯片高度范围）" << endl;
        cout << "  2. 写出检查函数 check(H)：判断在高度 H 下能否满足条件" << endl;
        cout << "  3. 二分查找：如果 check(mid) 为真，尝试更大的 mid" << endl;
        cout << "  4. 输出满足条件的最大值/最小值" << endl;
        cout << endl;
        cout << "核心前提：答案空间具有单调性" << endl;
        cout << "  H 增大 → 木材减少（单调递减）" << endl;
        cout << "  因此可以在答案空间上二分" << endl;
    }
    cout << endl;

    // ---------- 6. 浮点数二分：求平方根 ----------
    cout << "---------- 6. 浮点数二分：求平方根 ----------" << endl;
    {
        // 测试多个值
        double test_values[] = {2.0, 3.0, 10.0, 0.25, 100.0, 0.01, 7.0};
        int n = sizeof(test_values) / sizeof(test_values[0]);

        cout << fixed << setprecision(10);  // 设置输出精度

        cout << setw(8) << "x"
             << setw(22) << "二分法 sqrt(x)"
             << setw(22) << "标准库 sqrt(x)"
             << setw(16) << "误差"
             << endl;
        cout << string(68, '-') << endl;

        for (int i = 0; i < n; i++) {
            double x = test_values[i];
            double my_sqrt = sqrtBinarySearch(x, 1e-12);
            double std_sqrt = sqrt(x);
            double error = abs(my_sqrt - std_sqrt);

            cout << setprecision(6) << setw(8) << x
                 << setprecision(12) << setw(22) << my_sqrt
                 << setw(22) << std_sqrt
                 << setprecision(2) << scientific << setw(16) << error
                 << fixed << endl;
        }

        // 手动验证 2 的平方根
        cout << endl;
        cout << "详细展示 sqrt(2) 的二分求解过程：" << endl;
        double sqrt2 = sqrtBinarySearch(2.0, 1e-12);
        cout << "  计算值：  " << setprecision(15) << sqrt2 << endl;
        cout << "  标准值：  " << sqrt(2.0) << endl;
        cout << "  平方验证：" << sqrt2 * sqrt2 << endl;
        cout << "  误差：    " << abs(sqrt2 * sqrt2 - 2.0) << endl;

        // 使用固定迭代次数版本
        cout << endl;
        cout << "固定迭代次数版本（100次）：" << endl;
        double sqrt2_fixed = sqrtFixedIter(2.0);
        cout << "  sqrt(2) = " << setprecision(15) << sqrt2_fixed << endl;
        cout << "  平方 = " << sqrt2_fixed * sqrt2_fixed << endl;
    }
    cout << endl;

    // ---------- 7. 浮点数二分：更多应用 ----------
    cout << "---------- 7. 浮点数二分：求立方根 ----------" << endl;
    {
        // 求立方根的演示
        double x = 27.0;
        double l = 0, r = x;
        if (x < 1.0) { l = 0; r = 1.0; }

        double eps = 1e-12;
        while (r - l > eps) {
            double mid = (l + r) / 2.0;
            if (mid * mid * mid <= x) {
                l = mid;
            } else {
                r = mid;
            }
        }

        double cube_root = (l + r) / 2.0;
        cout << "x = " << x << endl;
        cout << "二分法求立方根：" << setprecision(12) << cube_root << endl;
        cout << "实际值：" << pow(x, 1.0/3.0) << endl;
        cout << "验证：" << cube_root << "^3 = " << cube_root * cube_root * cube_root << endl;

        cout << endl;
        cout << "浮点数二分通用模板：" << endl;
        cout << "  double l = L, r = R;" << endl;
        cout << "  while (r - l > eps) {" << endl;
        cout << "      double mid = (l + r) / 2;" << endl;
        cout << "      if (check(mid)) l = mid;  // mid 合法" << endl;
        cout << "      else r = mid;              // mid 不合法" << endl;
        cout << "  }" << endl;
        cout << "  return (l + r) / 2;" << endl;
    }
    cout << endl;

    // ---------- 8. 总结对比 ----------
    cout << "---------- 8. 二分查找方法总结 ----------" << endl;
    cout << endl;
    cout << "┌────────────────────┬───────────────────────────┬─────────────────────────────┐" << endl;
    cout << "│       写法          │        循环条件             │         适用场景              │" << endl;
    cout << "├────────────────────┼───────────────────────────┼─────────────────────────────┤" << endl;
    cout << "│ while(l <= r)      │ 闭区间 [l, r]，区间非空就搜  │ 查找确切值是否存在             │" << endl;
    cout << "│ while(l < r)       │ 半开区间 [l, r)，区间至少1元素│ 查找边界（如 lower_bound）     │" << endl;
    cout << "│ 整数二分答案        │ while(l <= r) + 记录答案    │ 在答案空间上找满足条件的最大/小值│" << endl;
    cout << "│ 浮点数二分          │ while(r - l > eps)         │ 需要高精度数值解               │" << endl;
    cout << "└────────────────────┴───────────────────────────┴─────────────────────────────┘" << endl;
    cout << endl;

    cout << "二分查找的核心前提：有序 / 单调性" << endl;
    cout << "  - 查找值：数组必须有序" << endl;
    cout << "  - 二分答案：「答案 vs 条件」必须具有单调性" << endl;
    cout << "  - 浮点数二分：检查函数必须单调" << endl;
    cout << endl;

    cout << "============================================" << endl;
    cout << "  程序结束" << endl;
    cout << "============================================" << endl;

    return 0;
}
