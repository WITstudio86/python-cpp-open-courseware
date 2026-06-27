/*
 * Lesson 29: 冒泡排序与选择排序
 *
 * 本课内容：
 * 1. 冒泡排序：通过相邻元素两两比较，将较大（小）的元素逐步"冒泡"到数组末尾
 * 2. 选择排序：每次从未排序部分选择最小（大）的元素，放到已排序部分的末尾
 * 3. 排序稳定性：相等元素的相对顺序在排序后是否保持不变
 * 4. 比较次数与交换次数的统计与对比
 *
 * 时间复杂度：
 * - 冒泡排序：O(n^2) 最坏/平均，O(n) 最好（优化版）
 * - 选择排序：O(n^2) 所有情况
 *
 * 空间复杂度：均为 O(1)
 *
 * 稳定性：
 * - 冒泡排序：稳定（相等元素不交换，相对顺序不变）
 * - 选择排序：不稳定（可能跳过相等元素，破坏相对顺序）
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <iomanip>

using namespace std;

// ==================== 数据结构定义 ====================

// 用于演示排序稳定性的结构体
// 每个元素有 value（排序键）和 id（记录原始顺序）
struct Data {
    int value;  // 排序依据的值
    int id;     // 原始位置标识，用于判断稳定性
    string label; // 标签，用于直观展示

    Data() : value(0), id(0), label("") {}
    Data(int v, int i, string l) : value(v), id(i), label(l) {}
};

// ==================== 冒泡排序 ====================

/**
 * 标准冒泡排序（升序）
 *
 * 算法思想：
 * - 外层循环控制轮数：共 n-1 轮
 * - 内层循环进行相邻比较：每一轮将当前未排序部分的最大值"冒泡"到末尾
 * - 第 i 轮排序后，最后 i 个元素已经排好序
 *
 * 参数：
 *   a[] - 待排序数组
 *   n   - 数组长度
 *   cmp_count - 输出参数：记录比较次数
 *   swap_count - 输出参数：记录交换次数
 */
void bubbleSort(int a[], int n, int& cmp_count, int& swap_count) {
    cmp_count = 0;
    swap_count = 0;

    // 外层循环：控制排序的轮数，共需要 n-1 轮
    for (int i = 0; i < n - 1; i++) {
        // 内层循环：从第 0 个元素开始，比较到第 n-1-i 个元素
        // 因为每轮结束后，末尾 i 个元素已经排好序，不需要再比较
        // 使用 j < n - 1 - i 避免数组越界（j+1 在有效范围内）
        for (int j = 0; j < n - 1 - i; j++) {
            cmp_count++;  // 统计一次比较

            // 如果前一个元素大于后一个元素，则交换它们
            // 使用 > 而不是 >= 可以保证排序的稳定性
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                swap_count++;  // 统计一次交换
            }
        }
    }
}

/**
 * 优化冒泡排序（升序，带 swapped 标记）
 *
 * 优化思想：
 * - 如果某一轮比较中没有任何交换发生，说明数组已经有序
 * - 此时可以提前结束排序，避免不必要的比较
 * - 最好情况（已有序）：只需 O(n) 次比较，0 次交换
 *
 * 参数同标准版
 */
void bubbleSortOptimized(int a[], int n, int& cmp_count, int& swap_count) {
    cmp_count = 0;
    swap_count = 0;

    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;  // 标记本轮是否发生了交换

        for (int j = 0; j < n - 1 - i; j++) {
            cmp_count++;

            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                swap_count++;
                swapped = true;  // 发生了交换，标记为 true
            }
        }

        // 如果本轮没有发生任何交换，说明数组已经完全有序
        // 可以直接结束排序，后续轮次不需要再执行
        if (!swapped) {
            break;
        }
    }
}

// ==================== 选择排序 ====================

/**
 * 选择排序（升序）
 *
 * 算法思想：
 * - 每一轮从未排序部分中找到最小值的位置
 * - 将该最小值与未排序部分的第一个元素交换
 * - 经过 n-1 轮后，数组有序
 *
 * 为什么不稳定？
 * - 例如 [5, 8, 5, 2, 9]，第一轮找到最小值 2（下标 3）
 * - 将 2 与第一个 5（下标 0）交换，得到 [2, 8, 5, 5, 9]
 * - 两个 5 的相对顺序发生了改变！
 *
 * 参数：
 *   a[] - 待排序数组
 *   n   - 数组长度
 *   cmp_count - 输出参数：记录比较次数
 *   swap_count - 输出参数：记录交换次数
 */
void selectionSort(int a[], int n, int& cmp_count, int& swap_count) {
    cmp_count = 0;
    swap_count = 0;

    // 外层循环：控制已排序部分的扩展
    // 当 i = n-1 时，只剩一个元素，无需排序，所以到 n-2
    for (int i = 0; i < n - 1; i++) {
        // 假设当前未排序部分的第一个元素就是最小值
        int min_idx = i;

        // 内层循环：在未排序部分 [i, n-1] 中查找真正的最小值
        for (int j = i + 1; j < n; j++) {
            cmp_count++;  // 统计比较次数

            if (a[j] < a[min_idx]) {
                min_idx = j;  // 更新最小值的位置
            }
        }

        // 如果最小值不在当前位置（i），则交换
        // 注意：即使 min_idx == i 也要计数为 0 次交换
        if (min_idx != i) {
            swap(a[i], a[min_idx]);
            swap_count++;
        }
    }
}

// ==================== 稳定性演示（结构体版本） ====================

/**
 * 对结构体数组进行冒泡排序（升序，按 value 排序）
 * 冒泡排序是稳定的：相等 value 的元素不会交换，保持原始相对顺序
 */
void bubbleSortStruct(Data a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; j++) {
            // 只有严格大于才交换，相等时不交换，保证稳定性
            if (a[j].value > a[j + 1].value) {
                swap(a[j], a[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

/**
 * 对结构体数组进行选择排序（升序，按 value 排序）
 * 选择排序是不稳定的：可能跨过相等 value 的元素进行交换
 */
void selectionSortStruct(Data a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j].value < a[min_idx].value) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            // 这次交换可能破坏相等元素的相对顺序
            swap(a[i], a[min_idx]);
        }
    }
}

// ==================== 工具函数 ====================

/**
 * 打印整数数组
 */
void printArray(int a[], int n, const string& title) {
    cout << title << ": [";
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << ", ";
        cout << a[i];
    }
    cout << "]" << endl;
}

/**
 * 打印结构体数组，显示 value、id 和 label
 */
void printDataArray(Data a[], int n, const string& title) {
    cout << title << ":" << endl;
    for (int i = 0; i < n; i++) {
        cout << "  [" << i << "] value=" << setw(2) << a[i].value
             << "  id=" << a[i].id
             << "  label=" << a[i].label << endl;
    }
}

/**
 * 复制数组内容（从源数组到目标数组）
 */
void copyArray(const int src[], int dst[], int n) {
    for (int i = 0; i < n; i++) {
        dst[i] = src[i];
    }
}

/**
 * 复制结构体数组
 */
void copyDataArray(const Data src[], Data dst[], int n) {
    for (int i = 0; i < n; i++) {
        dst[i] = src[i];
    }
}

// ==================== 主函数 ====================

int main() {
    cout << "============================================" << endl;
    cout << "  Lesson 29: 冒泡排序与选择排序" << endl;
    cout << "============================================" << endl;
    cout << endl;

    // ---------- 1. 冒泡排序（标准版） ----------
    cout << "---------- 1. 冒泡排序（标准版） ----------" << endl;
    {
        int arr[] = {64, 34, 25, 12, 22, 11, 90};
        int n = sizeof(arr) / sizeof(arr[0]);
        int cmp_count, swap_count;

        printArray(arr, n, "排序前");

        bubbleSort(arr, n, cmp_count, swap_count);

        printArray(arr, n, "排序后");
        cout << "比较次数: " << cmp_count
             << ", 交换次数: " << swap_count << endl;
    }
    cout << endl;

    // ---------- 2. 冒泡排序（优化版） ----------
    cout << "---------- 2. 冒泡排序（优化版，带 swapped 标记） ----------" << endl;
    {
        // 测试接近有序的数组，观察优化效果
        int arr[] = {1, 2, 3, 4, 5, 10, 6};
        int n = sizeof(arr) / sizeof(arr[0]);
        int cmp_count, swap_count;

        printArray(arr, n, "排序前（几乎有序）");

        bubbleSortOptimized(arr, n, cmp_count, swap_count);

        printArray(arr, n, "排序后");
        cout << "比较次数: " << cmp_count
             << ", 交换次数: " << swap_count << endl;
        cout << "（优化版在几乎有序的数组上可提前结束，减少比较次数）" << endl;
    }
    cout << endl;

    // ---------- 3. 选择排序 ----------
    cout << "---------- 3. 选择排序 ----------" << endl;
    {
        int arr[] = {64, 25, 12, 22, 11};
        int n = sizeof(arr) / sizeof(arr[0]);
        int cmp_count, swap_count;

        printArray(arr, n, "排序前");

        selectionSort(arr, n, cmp_count, swap_count);

        printArray(arr, n, "排序后");
        cout << "比较次数: " << cmp_count
             << ", 交换次数: " << swap_count << endl;
        cout << "（选择排序的比较次数固定为 n*(n-1)/2，交换次数最多为 n-1）" << endl;
    }
    cout << endl;

    // ---------- 4. 排序稳定性演示 ----------
    cout << "---------- 4. 排序稳定性演示 ----------" << endl;
    cout << "稳定性定义：相等元素的相对顺序在排序后保持不变" << endl;
    cout << endl;

    {
        // 构造测试数据：多个相同 value 的元素，通过 id 和 label 区分
        // value=5 有三个，value=3 有两个，value=8 有两个
        Data original[] = {
            Data(5, 0, "第一个5 (id=0)"),
            Data(3, 1, "第一个3 (id=1)"),
            Data(8, 2, "第一个8 (id=2)"),
            Data(5, 3, "第二个5 (id=3)"),
            Data(3, 4, "第二个3 (id=4)"),
            Data(8, 5, "第二个8 (id=5)"),
            Data(5, 6, "第三个5 (id=6)"),
            Data(2, 7, "唯一的2 (id=7)")
        };
        int n = 8;

        cout << "原始数据：" << endl;
        printDataArray(original, n, "");

        cout << endl << "--- 冒泡排序（稳定）---" << endl;
        Data bubbleArr[8];
        copyDataArray(original, bubbleArr, n);
        bubbleSortStruct(bubbleArr, n);
        printDataArray(bubbleArr, n, "冒泡排序结果");
        cout << "观察：相同 value 的元素（如三个5），id 顺序保持为 0, 3, 6" << endl;
        cout << "  => 冒泡排序是【稳定】的" << endl;

        cout << endl << "--- 选择排序（不稳定）---" << endl;
        Data selectArr[8];
        copyDataArray(original, selectArr, n);
        selectionSortStruct(selectArr, n);
        printDataArray(selectArr, n, "选择排序结果");
        cout << "观察：相同 value 的元素，id 顺序可能被打乱" << endl;
        cout << "  => 选择排序是【不稳定】的" << endl;

        cout << endl << "不稳定原因分析：" << endl;
        cout << "  选择排序在每一轮中找到最小值后，会与未排序部分的第一个元素交换。" << endl;
        cout << "  这个交换操作可能将前面的相等元素跳过，从而破坏原始相对顺序。" << endl;
        cout << "  例如：序列 [5a, 3, 8, 5b, 2]，第一轮找到最小值 2（下标4），" << endl;
        cout << "  将 2 与 5a 交换得到 [2, 3, 8, 5b, 5a]，5b 跑到了 5a 前面！" << endl;
    }
    cout << endl;

    // ---------- 5. 冒泡 vs 选择：同数组对比 ----------
    cout << "---------- 5. 冒泡排序 vs 选择排序：同数组对比 ----------" << endl;
    {
        // 使用相同的随机数组，分别用两种算法排序，对比效率
        int original[] = {49, 38, 65, 97, 76, 13, 27, 49, 55, 4};
        int n = sizeof(original) / sizeof(original[0]);
        int arr_copy[n];
        int cmp_bubble, swap_bubble, cmp_select, swap_select;

        printArray(original, n, "原始数组");

        // 冒泡排序（优化版）
        copyArray(original, arr_copy, n);
        bubbleSortOptimized(arr_copy, n, cmp_bubble, swap_bubble);
        printArray(arr_copy, n, "冒泡排序结果");

        // 选择排序
        copyArray(original, arr_copy, n);
        selectionSort(arr_copy, n, cmp_select, swap_select);
        printArray(arr_copy, n, "选择排序结果");

        // 对比统计
        cout << endl;
        cout << "┌──────────┬──────────┬──────────┐" << endl;
        cout << "│   算法    │ 比较次数  │ 交换次数  │" << endl;
        cout << "├──────────┼──────────┼──────────┤" << endl;
        cout << "│ 冒泡排序  │ " << setw(7) << cmp_bubble
             << "  │ " << setw(7) << swap_bubble << "  │" << endl;
        cout << "│ 选择排序  │ " << setw(7) << cmp_select
             << "  │ " << setw(7) << swap_select << "  │" << endl;
        cout << "└──────────┴──────────┴──────────┘" << endl;
        cout << endl;
        cout << "对比分析：" << endl;
        cout << "  - 选择排序的比较次数 = n*(n-1)/2 = "
             << n * (n - 1) / 2 << "（固定值）" << endl;
        cout << "  - 冒泡排序的交换次数通常多于选择排序" << endl;
        cout << "  - 选择排序的交换次数最多为 n-1（每轮最多一次交换）" << endl;
        cout << "  - 如果数据接近有序，冒泡排序优化版可以提前结束" << endl;
    }
    cout << endl;

    // ---------- 6. 降序排序演示 ----------
    cout << "---------- 6. 降序排序演示 ----------" << endl;
    {
        int arr[] = {64, 34, 25, 12, 22, 11, 90};
        int n = sizeof(arr) / sizeof(arr[0]);
        int cmp_count, swap_count;

        printArray(arr, n, "排序前");

        // 降序冒泡排序：将比较条件从 > 改为 <
        cmp_count = 0;
        swap_count = 0;
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - 1 - i; j++) {
                cmp_count++;
                if (arr[j] < arr[j + 1]) {  // 改为 < 实现降序
                    swap(arr[j], arr[j + 1]);
                    swap_count++;
                }
            }
        }

        printArray(arr, n, "降序排序后");
        cout << "比较次数: " << cmp_count
             << ", 交换次数: " << swap_count << endl;
        cout << "说明：将比较条件从 a[j] > a[j+1] 改为 a[j] < a[j+1] 即可实现降序" << endl;
    }
    cout << endl;

    cout << "============================================" << endl;
    cout << "  程序结束" << endl;
    cout << "============================================" << endl;

    return 0;
}
