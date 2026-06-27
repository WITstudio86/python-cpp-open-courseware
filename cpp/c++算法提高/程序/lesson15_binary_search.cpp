/*
 * ============================================================
 * 第15课：线性查找与二分查找 —— 完整代码实现
 * C++算法提高课程
 *
 * 本文件包含：
 *   1. linearSearch        —— 线性查找（顺序查找）
 *   2. binarySearch        —— 二分查找（迭代版，左闭右闭区间）
 *   3. binarySearchRecursive —— 二分查找（递归版）
 *   4. lowerBound          —— 找第一个 >= target 的位置（STL 风格）
 *   5. upperBound          —— 找第一个 >  target 的位置（STL 风格）
 *   6. findFirstEqual      —— 找第一个 == target 的位置
 *   7. findLastEqual       —— 找最后一个 == target 的位置
 *   8. solveFindPosition   —— 例题1：找数字位置
 *   9. solveGuessNumber    —— 例题2：猜数游戏
 * ============================================================
 */

#include <iostream>
using namespace std;

// ==================== 1. 线性查找 ====================

/**
 * 线性查找（顺序查找）
 *
 * 核心思想：从数组的第一个元素开始，逐个与目标值 target 进行比较。
 * 如果相等，返回当前下标；如果遍历完整个数组都没有找到，返回 -1。
 *
 * 优点：不要求数组有序，实现简单。
 * 缺点：最坏情况下需要比较 n 次，时间复杂度 O(n)。
 *
 * @param arr    待查找的数组（可以无序）
 * @param n      数组的长度
 * @param target 要查找的目标值
 * @return       找到则返回元素下标（从0开始），找不到返回 -1
 */
int linearSearch(int arr[], int n, int target) {
    // 从下标 0 开始，依次访问每一个元素
    for (int i = 0; i < n; i++) {
        // 如果当前元素等于目标值，说明找到了
        if (arr[i] == target)
            return i;   // 返回下标，函数结束
    }
    // 循环结束还没返回，说明整个数组里都没有 target
    return -1;  // 返回 -1 表示"未找到"
}


// ==================== 2. 二分查找（迭代版） ====================

/**
 * 二分查找 —— 迭代版本（左闭右闭区间 [left, right]）
 *
 * 前提条件：数组 arr 必须已经按升序排序！
 *
 * 核心思想：
 *   每次取当前区间的中间位置 mid，比较 arr[mid] 与 target：
 *     - 相等 → 找到了，返回 mid
 *     - arr[mid] < target → target 在右半边，左边界 left 右移到 mid+1
 *     - arr[mid] > target → target 在左半边，右边界 right 左移到 mid-1
 *   不断重复，直到 left > right（区间为空），说明不存在。
 *
 * 时间复杂度：O(log n)
 *   例如 n=1000000（100万），最多只需要比较约 20 次！
 *
 * @param arr    已按升序排序的数组
 * @param n      数组的长度
 * @param target 要查找的目标值
 * @return       找到则返回任意一个匹配的下标，找不到返回 -1
 */
int binarySearch(int arr[], int n, int target) {
    // 初始化左右指针
    // left 指向数组第一个元素，right 指向最后一个元素
    // 区间定义：[left, right] —— 左右边界都包含在查找范围内
    int left = 0, right = n - 1;

    // 循环条件：left <= right
    // 当 left == right 时，区间内还有一个元素需要检查
    while (left <= right) {
        // 计算中间位置
        // 注意：不能写成 (left + right) / 2，因为 left+right 可能溢出！
        // left + (right - left) / 2 是安全的写法
        int mid = left + (right - left) / 2;

        // 情况1：中间值正好等于目标值 → 直接返回
        if (arr[mid] == target) {
            return mid;
        }
        // 情况2：中间值比目标值小
        // 说明目标值一定在 mid 的右边（因为数组升序排列）
        else if (arr[mid] < target) {
            left = mid + 1;   // 左边界移动到 mid 的右边一格
        }
        // 情况3：中间值比目标值大
        // 说明目标值一定在 mid 的左边
        else {
            right = mid - 1;  // 右边界移动到 mid 的左边一格
        }
    }
    // 循环结束（left > right），说明查找区间为空，没找到
    return -1;
}


// ==================== 3. 二分查找（递归版） ====================

/**
 * 二分查找 —— 递归版本
 *
 * 递归思想：
 *   基础情况：如果 left > right，说明区间为空，返回 -1
 *   递归情况：
 *     计算 mid，比较 arr[mid] 与 target
 *     - 相等 → 返回 mid
 *     - arr[mid] < target → 递归查找右半部分 [mid+1, right]
 *     - arr[mid] > target → 递归查找左半部分 [left, mid-1]
 *
 * 空间复杂度：O(log n)，因为递归调用会占用调用栈空间
 * 时间复杂度：O(log n)，和迭代版相同
 *
 * @param arr    已排序的数组
 * @param left   当前查找区间的左边界（包含）
 * @param right  当前查找区间的右边界（包含）
 * @param target 要查找的目标值
 * @return       找到返回下标，找不到返回 -1
 */
int binarySearchRecursive(int arr[], int left, int right, int target) {
    // 递归终止条件：区间为空（左边界超过了右边界）
    if (left > right) {
        return -1;   // 没找到
    }

    // 计算中间位置（防溢出写法）
    int mid = left + (right - left) / 2;

    // 情况1：找到了
    if (arr[mid] == target) {
        return mid;
    }
    // 情况2：目标在右半边 → 递归搜索右半区间
    else if (arr[mid] < target) {
        return binarySearchRecursive(arr, mid + 1, right, target);
    }
    // 情况3：目标在左半边 → 递归搜索左半区间
    else {
        return binarySearchRecursive(arr, left, mid - 1, target);
    }
}


// ==================== 4. lowerBound —— 第一个 >= target ====================

/**
 * lowerBound：在有序数组中，找到第一个 **大于等于** target 的元素下标
 *
 * 这是 C++ STL 中 std::lower_bound 的手动实现。
 *
 * 核心思路：
 *   不断二分缩小范围。当 arr[mid] >= target 时，mid 可能是答案，
 *   但我们不确定左边是否还有更靠前的满足条件的元素，
 *   所以记录 mid 后继续往左找。
 *   当 arr[mid] < target 时，答案一定在右边。
 *
 * 应用场景：
 *   - 在有序数组中插入元素，找到插入位置
 *   - 求第一个不小于 target 的元素
 *
 * @param arr    已排序的数组
 * @param n      数组长度
 * @param target 目标值
 * @return       第一个 >= target 的元素下标；如果所有元素都 < target，返回 n
 */
int lowerBound(int arr[], int n, int target) {
    int left = 0, right = n - 1;
    int ans = n;  // 默认答案为 n，表示"不存在"（超出数组范围）

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] >= target) {
            ans = mid;       // 记录当前位置（可能不是最靠前的，先记下）
            right = mid - 1; // 继续往左找，看有没有更靠前的
        } else {
            left = mid + 1;  // arr[mid] < target，答案在右边
        }
    }
    return ans;  // 返回第一个 >= target 的位置
}


// ==================== 5. upperBound —— 第一个 > target ====================

/**
 * upperBound：在有序数组中，找到第一个 **严格大于** target 的元素下标
 *
 * 这是 C++ STL 中 std::upper_bound 的手动实现。
 *
 * 与 lowerBound 的区别仅在于比较条件：
 *   lowerBound：arr[mid] >= target → 包含"等于"
 *   upperBound：arr[mid] >  target → 严格大于
 *
 * @param arr    已排序的数组
 * @param n      数组长度
 * @param target 目标值
 * @return       第一个 > target 的元素下标；如果所有元素都 <= target，返回 n
 */
int upperBound(int arr[], int n, int target) {
    int left = 0, right = n - 1;
    int ans = n;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] > target) {
            ans = mid;       // 记录当前位置
            right = mid - 1; // 继续往左找更靠前的
        } else {
            left = mid + 1;  // arr[mid] <= target，答案在右边
        }
    }
    return ans;
}


// ==================== 6. findFirstEqual —— 第一个 == target ====================

/**
 * findFirstEqual：在有序数组中，找到 target **第一次出现** 的位置
 *
 * 关键技巧：当 arr[mid] == target 时，不要立刻返回！
 *   先记录下 mid，然后继续往左边找，看有没有更靠前的相同元素。
 *
 * @param arr    已排序的数组（可能包含重复元素）
 * @param n      数组长度
 * @param target 目标值
 * @return       target 第一次出现的下标；如果不存在，返回 -1
 */
int findFirstEqual(int arr[], int n, int target) {
    int left = 0, right = n - 1;
    int ans = -1;  // 默认 -1 表示"不存在"

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] >= target) {
            if (arr[mid] == target)
                ans = mid;   // 记录当前找到的位置
            right = mid - 1; // 继续往左搜索，可能有更靠前的
        } else {
            left = mid + 1;  // arr[mid] < target，往右找
        }
    }
    return ans;
}


// ==================== 7. findLastEqual —— 最后一个 == target ====================

/**
 * findLastEqual：在有序数组中，找到 target **最后一次出现** 的位置
 *
 * 与 findFirstEqual 对称：当 arr[mid] == target 时，记录后往右边继续找。
 *
 * @param arr    已排序的数组（可能包含重复元素）
 * @param n      数组长度
 * @param target 目标值
 * @return       target 最后一次出现的下标；如果不存在，返回 -1
 */
int findLastEqual(int arr[], int n, int target) {
    int left = 0, right = n - 1;
    int ans = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] <= target) {
            if (arr[mid] == target)
                ans = mid;   // 记录当前找到的位置
            left = mid + 1;  // 继续往右搜索，可能有更靠后的
        } else {
            right = mid - 1; // arr[mid] > target，往左找
        }
    }
    return ans;
}


// ==================== 8. 例题1：找数字位置 ====================

/**
 * 例题1：找数字位置
 *
 * 题目：给定一个已排序数组和目标值 target，找出 target 在数组中第一次出现的
 *       位置（下标从0开始）。如果不存在，输出 -1。
 *
 * 输入格式：
 *   第一行：n target   （n 为数组长度，1 ≤ n ≤ 100000）
 *   第二行：n 个已从小到大排序的整数
 *
 * 输出格式：一个整数，第一次出现的位置或 -1
 */
void solveFindPosition() {
    cout << "========== 例题1：找数字位置 ==========" << endl;

    // 读取输入
    int n, target;
    cout << "请输入 n 和 target（用空格分隔）：";
    cin >> n >> target;

    // 动态分配数组，支持更大的数据范围
    int* arr = new int[n];
    cout << "请输入 " << n << " 个已排序的整数（用空格分隔）：";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // 使用二分查找找到第一次出现的位置
    int result = findFirstEqual(arr, n, target);

    // 输出结果
    cout << "结果：target 第一次出现的位置是 " << result << endl;

    if (result != -1) {
        cout << "验证：arr[" << result << "] = " << arr[result] << endl;
    }

    delete[] arr;  // 释放动态分配的内存
}


// ==================== 9. 例题2：猜数游戏 ====================

/**
 * 例题2：猜数游戏
 *
 * 题目：系统有一个 1 到 100 之间的秘密数字。用二分查找策略，
 *       模拟猜测过程，输出每一步的猜测和系统反馈。
 *
 * 输入：secret，一个 1 到 100 之间的整数
 * 输出：每步猜测及结果，最后输出总猜测次数
 */
void solveGuessNumber() {
    cout << "\n========== 例题2：猜数游戏 ==========" << endl;

    int secret;
    cout << "请输入秘密数字（1~100）：";
    cin >> secret;

    // 确保 secret 在有效范围内
    if (secret < 1 || secret > 100) {
        cout << "秘密数字必须在 1 到 100 之间！" << endl;
        return;
    }

    int left = 1, right = 100;  // 初始猜数范围：[1, 100]
    int cnt = 0;                 // 猜测次数计数器

    cout << "\n开始二分查找猜数：" << endl;
    cout << "------------------------" << endl;

    while (left <= right) {
        cnt++;
        // 二分策略：每次猜当前范围的中间值
        int guess = left + (right - left) / 2;

        // 输出本次猜测
        cout << "第 " << cnt << " 次猜测：" << guess << "，结果：";

        if (guess == secret) {
            cout << "正确！猜中了！" << endl;
            break;
        } else if (guess < secret) {
            cout << "小了（范围缩小到 [" << guess + 1 << ", " << right << "]）" << endl;
            left = guess + 1;  // 猜小了 → 答案在更大的区域
        } else {
            cout << "大了（范围缩小到 [" << left << ", " << guess - 1 << "]）" << endl;
            right = guess - 1; // 猜大了 → 答案在更小的区域
        }
    }

    cout << "------------------------" << endl;
    cout << "一共猜了 " << cnt << " 次。" << endl;
    cout << "理论最大值：log₂(100) ≈ 6.64，最多 7 次。" << endl;
}


// ==================== 辅助函数：打印数组 ====================

/**
 * 打印数组的所有元素，方便测试时查看数组内容
 *
 * @param arr 要打印的数组
 * @param n   数组长度
 */
void printArray(int arr[], int n) {
    cout << "[";
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "]" << endl;
}


// ==================== 主函数：测试所有算法 ====================

int main() {
    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║  第15课：线性查找与二分查找  —  代码演示  ║" << endl;
    cout << "╚══════════════════════════════════════════╝" << endl;

    // ---------- 测试数据 ----------
    // 有序数组（包含重复元素），便于测试各种二分查找变体
    int arr[] = {1, 3, 3, 3, 5, 7, 9, 11, 13, 15};
    int n = sizeof(arr) / sizeof(arr[0]);  // 自动计算数组长度

    cout << "\n测试数组（有序，含重复元素）：";
    printArray(arr, n);
    cout << "数组长度 n = " << n << endl;

    // ---------- 测试1：线性查找 ----------
    int testTargets[] = {7, 3, 2, 15, 100};  // 多个测试目标
    cout << "\n===== 测试1：线性查找（Linear Search） =====" << endl;
    for (int t : testTargets) {
        int result = linearSearch(arr, n, t);
        cout << "  查找 " << t << " → ";
        if (result != -1)
            cout << "找到了，下标为 " << result;
        else
            cout << "未找到";
        cout << endl;
    }

    // ---------- 测试2：二分查找（迭代版） ----------
    cout << "\n===== 测试2：二分查找——迭代版（任意一个位置） =====" << endl;
    for (int t : testTargets) {
        int result = binarySearch(arr, n, t);
        cout << "  查找 " << t << " → ";
        if (result != -1)
            cout << "找到了，下标为 " << result << "，arr[" << result << "] = " << arr[result];
        else
            cout << "未找到";
        cout << endl;
    }

    // ---------- 测试3：二分查找（递归版） ----------
    cout << "\n===== 测试3：二分查找——递归版 =====" << endl;
    for (int t : testTargets) {
        int result = binarySearchRecursive(arr, 0, n - 1, t);
        cout << "  查找 " << t << " → ";
        if (result != -1)
            cout << "找到了，下标为 " << result;
        else
            cout << "未找到";
        cout << endl;
    }

    // ---------- 测试4：lowerBound（第一个 >= target） ----------
    cout << "\n===== 测试4：lowerBound（第一个 >= target） =====" << endl;
    int lbTests[] = {3, 4, 1, 16};
    for (int t : lbTests) {
        int result = lowerBound(arr, n, t);
        cout << "  第一个 >= " << t << " 的位置 → 下标 " << result;
        if (result < n)
            cout << "（arr[" << result << "] = " << arr[result] << "）";
        else
            cout << "（超出数组范围，不存在）";
        cout << endl;
    }

    // ---------- 测试5：upperBound（第一个 > target） ----------
    cout << "\n===== 测试5：upperBound（第一个 > target） =====" << endl;
    for (int t : lbTests) {
        int result = upperBound(arr, n, t);
        cout << "  第一个 > " << t << " 的位置 → 下标 " << result;
        if (result < n)
            cout << "（arr[" << result << "] = " << arr[result] << "）";
        else
            cout << "（超出数组范围，不存在）";
        cout << endl;
    }

    // ---------- 测试6：findFirstEqual（第一次出现） ----------
    cout << "\n===== 测试6：findFirstEqual（第一次出现的位置） =====" << endl;
    for (int t : testTargets) {
        int result = findFirstEqual(arr, n, t);
        cout << "  查找 " << t << " 的第一次出现 → 下标 " << result;
        if (result != -1)
            cout << "（arr[" << result << "] = " << arr[result] << "）";
        cout << endl;
    }

    // ---------- 测试7：findLastEqual（最后一次出现） ----------
    cout << "\n===== 测试7：findLastEqual（最后一次出现的位置） =====" << endl;
    for (int t : testTargets) {
        int result = findLastEqual(arr, n, t);
        cout << "  查找 " << t << " 的最后一次出现 → 下标 " << result;
        if (result != -1)
            cout << "（arr[" << result << "] = " << arr[result] << "）";
        cout << endl;
    }

    // ---------- 时间复杂度验证 ----------
    cout << "\n===== 时间复杂度直观对比 =====" << endl;
    cout << "  数组长度 n = " << n << endl;
    cout << "  线性查找：最多需要 " << n << " 次比较（O(n)）" << endl;
    cout << "  二分查找：最多需要约 " << (int)(log2(n) + 1)
         << " 次比较（O(log n)）" << endl;
    cout << "  当 n = 1000000 时，线性需 1000000 次，二分仅需 ~20 次！" << endl;

    // ---------- 运行例题（交互模式） ----------
    cout << "\n========================================" << endl;
    cout << "接下来可以运行例题，或者直接按 Ctrl+C 退出。" << endl;
    cout << "========================================" << endl;

    char choice;
    cout << "\n运行例题1（找数字位置）？(y/n)：";
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        solveFindPosition();
    }

    cout << "\n运行例题2（猜数游戏）？(y/n)：";
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        solveGuessNumber();
    }

    cout << "\n╔══════════════════════════════════════════╗" << endl;
    cout << "║          所有测试完成，感谢学习！          ║" << endl;
    cout << "╚══════════════════════════════════════════╝" << endl;

    return 0;
}
