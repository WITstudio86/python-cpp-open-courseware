/*
 * ============================================================
 * Lesson 10：选择排序 —— 选最小放前面
 * C++ 算法提高课程
 *
 * 本文件包含：
 *   1. selectionSort()       —— 完整的选择排序实现
 *   2. kthSmallest()         —— 利用选择排序找第k小的数
 *   3. selectionSortWithSteps() —— 选择排序（输出每轮过程）
 *   4. main()                —— 测试代码
 *
 * 选择排序核心思想：
 *   每一轮从未排序部分中选出最小值，放到已排序部分的末尾。
 *   长度为n的数组需要n-1轮。
 * ============================================================
 */

#include <iostream>
using namespace std;

/*
 * 函数：selectionSort
 * 功能：使用选择排序将数组按升序排列
 * 参数：
 *   arr[] - 待排序的整数数组
 *   n     - 数组的长度
 * 返回值：无
 *
 * 算法步骤：
 *   外层循环 i（0 到 n-2）：控制轮次，arr[i] 是本轮要放最小值的位置
 *   内层循环 j（i+1 到 n-1）：在未排序区间中扫描，寻找最小值的索引
 *   如果最小值不在 arr[i]，则交换 arr[i] 和 arr[minIndex]
 */
void selectionSort(int arr[], int n) {
    // 外层循环：需要进行 n-1 轮选择
    // i 既是轮次编号，也是"目标位置"——把本轮找到的最小值放到 arr[i]
    for (int i = 0; i < n - 1; i++) {

        // ----- 步骤1：在未排序区间 arr[i..n-1] 中寻找最小值的索引 -----
        int minIndex = i;   // 先假设 arr[i] 就是最小的
        for (int j = i + 1; j < n; j++) {
            // 如果发现更小的元素，更新最小值的索引
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        // ----- 步骤2：将最小值交换到目标位置 -----
        // 只有当最小值不在 arr[i] 时才执行交换（避免不必要的赋值操作）
        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
            // 交换后：arr[i] 就是本轮选出的最小值，前 i+1 个元素已经排好序
        }
    }
}

/*
 * 函数：kthSmallest
 * 功能：利用选择排序的思想，找到数组中第k小的数
 *       只进行 k 轮选择即可，不需要对全数组排序
 * 参数：
 *   arr[] - 整数数组
 *   n     - 数组长度
 *   k     - 要找第k小的数（k 从 1 开始计数）
 * 返回值：第k小的数
 *
 * 为什么可行？
 *   选择排序第1轮把第1小的数放到arr[0]
 *   第2轮把第2小的数放到arr[1]
 *   ...
 *   第k轮把第k小的数放到arr[k-1]
 *   所以只需要执行k轮，arr[k-1]就是答案
 */
int kthSmallest(int arr[], int n, int k) {
    // 只进行 k 轮选择排序
    // 第 i 轮会将第 i+1 小的数放到 arr[i] 的位置
    for (int i = 0; i < k; i++) {
        // 在 arr[i] 到 arr[n-1] 中找最小值的索引
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        // 将找到的最小值交换到 arr[i]
        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }

    // arr[k-1] 就是第 k 小的数（数组索引从0开始）
    return arr[k - 1];
}

/*
 * 函数：selectionSortWithSteps
 * 功能：使用选择排序对数组排序，并输出每一轮交换后的数组状态
 *       适用于"选择排序验证"类题目，方便观察排序过程
 * 参数：
 *   arr[] - 待排序的整数数组
 *   n     - 数组的长度
 * 返回值：无
 *
 * 输出说明：
 *   每次内层循环找到最小值并交换后，立即输出当前数组状态
 *   共输出 n-1 行（当只剩最后一个元素时，它自然归位）
 */
void selectionSortWithSteps(int arr[], int n) {
    // 外层循环：n-1 轮选择
    for (int i = 0; i < n - 1; i++) {

        // 在未排序区间 arr[i..n-1] 中找到最小值的索引
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        // 将最小值交换到目标位置 arr[i]
        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }

        // ----- 输出本轮交换后的数组状态 -----
        for (int j = 0; j < n; j++) {
            if (j > 0) cout << " ";  // 数字之间用空格分隔
            cout << arr[j];
        }
        cout << endl;
    }
}

/*
 * 函数：printArray
 * 功能：打印数组的所有元素（辅助函数，用于测试输出）
 */
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << " ";
        cout << arr[i];
    }
    cout << endl;
}

/*
 * 函数：main
 * 功能：测试上述所有功能
 */
int main() {
    cout << "============================================" << endl;
    cout << "  第10课：选择排序 —— 选最小放前面" << endl;
    cout << "============================================" << endl;

    // =========================================
    // 测试1：完整的选择排序
    // =========================================
    cout << "\n【测试1】完整的选择排序" << endl;
    cout << "----------------------------" << endl;

    int arr1[] = {64, 25, 12, 22, 11};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);  // 计算数组长度

    cout << "排序前：";
    printArray(arr1, n1);

    // 执行选择排序
    selectionSort(arr1, n1);

    cout << "排序后：";
    printArray(arr1, n1);

    // =========================================
    // 测试2：找第k小的数（例题1）
    // =========================================
    cout << "\n【测试2】找第k小的数（例题1）" << endl;
    cout << "----------------------------" << endl;

    // 测试样例：n=5, k=3, 数组=[7, 2, 9, 1, 5]
    // 预期输出：第3小的数是5
    int arr2[] = {7, 2, 9, 1, 5};
    int n2 = 5;
    int k2 = 3;

    // 复制一份数组用于演示（因为 kthSmallest 会修改原数组）
    int arr2_copy[5];
    for (int i = 0; i < n2; i++) arr2_copy[i] = arr2[i];

    cout << "数组：";
    printArray(arr2_copy, n2);
    cout << "找第 " << k2 << " 小的数" << endl;

    int result = kthSmallest(arr2_copy, n2, k2);
    cout << "结果：第 " << k2 << " 小的数是 " << result << endl;
    cout << "（正确答案：5）" << endl;

    // 额外测试：找第1小的数（即最小值）
    for (int i = 0; i < n2; i++) arr2_copy[i] = arr2[i];
    cout << "找第 1 小的数：" << kthSmallest(arr2_copy, n2, 1) << "（最小值）" << endl;

    // 额外测试：找第5小的数（即最大值）
    for (int i = 0; i < n2; i++) arr2_copy[i] = arr2[i];
    cout << "找第 5 小的数：" << kthSmallest(arr2_copy, n2, 5) << "（最大值）" << endl;

    // =========================================
    // 测试3：选择排序验证（例题2）
    // 每轮输出排序后的数组状态
    // =========================================
    cout << "\n【测试3】选择排序验证 —— 每轮状态输出（例题2）" << endl;
    cout << "----------------------------" << endl;

    // 测试样例：n=5, 数组=[64, 25, 12, 22, 11]
    // 预期输出4行，每行是一轮交换后的数组
    int arr3[] = {64, 25, 12, 22, 11};
    int n3 = 5;

    cout << "初始数组：";
    printArray(arr3, n3);
    cout << "每轮排序后的状态：" << endl;
    selectionSortWithSteps(arr3, n3);

    // 再多加一组测试数据
    cout << "\n额外测试数组 [5, 1, 4, 2, 8]：" << endl;
    int arr4[] = {5, 1, 4, 2, 8};
    int n4 = 5;
    cout << "初始数组：";
    printArray(arr4, n4);
    cout << "每轮排序后的状态：" << endl;
    selectionSortWithSteps(arr4, n4);

    // =========================================
    // 总结
    // =========================================
    cout << "\n============================================" << endl;
    cout << "  选择排序要点回顾：" << endl;
    cout << "  1. 外层循环（n-1轮），i 从 0 到 n-2" << endl;
    cout << "  2. 内层循环找最小值，j 从 i+1 到 n-1" << endl;
    cout << "  3. 交换 arr[i] 和 arr[minIndex]" << endl;
    cout << "  4. 时间复杂度 O(n²)，空间复杂度 O(1)" << endl;
    cout << "  5. 应用：找第k小的数只需k轮" << endl;
    cout << "============================================" << endl;

    return 0;
}
