/*
 * ============================================================
 * 第42课：排排坐吃果果——冒泡排序
 * C++ 趣味学习 - 进阶阶段
 *
 * 本文件包含3个完整的冒泡排序程序：
 *   程序1：基础冒泡排序演示（从小到大）
 *   程序2：优化版冒泡排序（带提前退出标志位）
 *   程序3：练习答案——逐步展示排序过程
 *
 * 编译方法：
 *   g++ lesson42_bubble_sort.cpp -o lesson42_bubble_sort
 * 运行方法：
 *   ./lesson42_bubble_sort
 * ============================================================
 */

#include <iostream>
using namespace std;

// ============================================================
// 辅助函数：打印数组
// 参数：arr - 数组名（指针），n - 数组长度
// ============================================================
void printArray(int arr[], int n) {
    cout << "[";
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "]";
}

// ============================================================
// 辅助函数：打印分隔线
// ============================================================
void printSeparator(string title) {
    cout << "\n" << string(60, '=') << endl;
    cout << "  " << title << endl;
    cout << string(60, '=') << endl;
}

// ============================================================
// 程序1：基础冒泡排序演示
// 功能：将5个乱序数字从小到大排列
// 学习重点：理解双层循环结构和交换操作
// ============================================================
void program1_basicBubbleSort() {
    printSeparator("程序1：基础冒泡排序（从小到大）");

    // 准备待排序的数组
    int arr[] = {5, 3, 8, 1, 6};
    int n = 5;

    // 输出排序前的数组
    cout << "排序前：";
    printArray(arr, n);
    cout << endl;

    /*
     * 冒泡排序的核心：两层循环
     *
     * 外层循环 i：控制排序的"轮数"
     *   - n 个元素最多需要 n-1 轮
     *   - 因为最后一轮只剩一个元素，不需要比较
     *
     * 内层循环 j：控制每轮的"比较和交换"
     *   - 第 i 轮时，数组末尾的 i 个元素已经排好
     *   - 所以 j 只需从 0 到 n-2-i
     *   - 每次比较 arr[j] 和 arr[j+1]
     */
    for (int i = 0; i < n - 1; i++) {
        // j 的上限是 n-1-i，因为每次比较 j 和 j+1
        // 用 j < n-1-i 保证 j+1 不会越界
        for (int j = 0; j < n - 1 - i; j++) {
            // 如果前面的元素比后面的大 → 交换
            if (arr[j] > arr[j + 1]) {
                // 三步交换法（必须用临时变量！）
                int temp = arr[j];       // 第1步：暂存 arr[j]
                arr[j] = arr[j + 1];    // 第2步：arr[j+1] 覆盖 arr[j]
                arr[j + 1] = temp;      // 第3步：temp 放到 arr[j+1]
            }
        }
    }

    // 输出排序后的数组
    cout << "排序后：";
    printArray(arr, n);
    cout << endl;

    cout << "\n💡 说明：" << endl;
    cout << "  - 外层循环 i 从 0 到 n-2（共 n-1 轮）" << endl;
    cout << "  - 内层循环 j 从 0 到 n-2-i（每轮减少一次比较）" << endl;
    cout << "  - 总比较次数：n(n-1)/2 = " << n*(n-1)/2 << " 次" << endl;
}

// ============================================================
// 程序2：优化版冒泡排序（带提前退出标志位）
// 功能：在基础版本上增加 swapped 标志，排序完成后提前结束
// 学习重点：理解算法优化思想，学会使用 bool 标志位
// ============================================================
void program2_optimizedBubbleSort() {
    printSeparator("程序2：优化版冒泡排序（带提前退出）");

    // 使用一个"基本有序"的数组来展示优化效果
    // 只需要几轮就能排好，优化后可以提前结束
    int arr[] = {1, 3, 5, 2, 8, 4};
    int n = 6;

    cout << "排序前：";
    printArray(arr, n);
    cout << endl << endl;

    // 外层循环：控制轮数
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;  // 本轮是否发生了交换

        cout << "第 " << i + 1 << " 轮比较：";

        // 内层循环：相邻比较和交换
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                // 发生交换
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;  // 标记：本轮有交换
            }
        }

        // 打印本轮结束后的数组状态
        printArray(arr, n);
        cout << "  (交换：" << (swapped ? "是" : "否") << ")" << endl;

        /*
         * 优化关键：检查标志位
         * 如果本轮没有发生任何交换，说明数组已经完全有序
         * 后面的轮次都是多余的，可以直接 break 退出！
         */
        if (!swapped) {
            cout << "\n✨ 第 " << i + 1 << " 轮没有发生交换！" << endl;
            cout << "   数组已经有序，提前结束排序。" << endl;
            cout << "   实际执行了 " << i + 1 << " 轮（如果不用优化，需要 " << n - 1 << " 轮）" << endl;
            break;
        }
    }

    cout << "\n最终结果：";
    printArray(arr, n);
    cout << endl;

    cout << "\n💡 什么时候优化效果最好？" << endl;
    cout << "  - 数组已经基本有序时（如 [1,2,4,3,5]）" << endl;
    cout << "  - 数组完全有序时，只需1轮就结束" << endl;
    cout << "  - 完全逆序时优化无效（每轮都有交换）" << endl;
}

// ============================================================
// 程序3：练习答案——逐步展示排序过程
// 功能：对用户输入的5个数字排序，并逐步展示每轮结果
// 对应课件练习1：数组 [9, 2, 7, 4, 1]
// ============================================================
void program3_stepByStepSort() {
    printSeparator("程序3：逐步展示排序过程（练习答案）");

    // 练习1的数组
    int arr[] = {9, 2, 7, 4, 1};
    int n = 5;

    cout << "📋 练习题目：对数组 ";
    printArray(arr, n);
    cout << " 进行冒泡排序（从小到大）" << endl;
    cout << "\n排序过程如下：\n" << endl;

    // 打印初始状态
    cout << "初始状态：\t";
    printArray(arr, n);
    cout << endl;

    int totalComparisons = 0;  // 统计总比较次数
    int totalSwaps = 0;        // 统计总交换次数

    // 冒泡排序，每轮打印数组状态
    for (int i = 0; i < n - 1; i++) {
        int swapsInRound = 0;     // 本轮交换次数
        int comparisonsInRound = 0; // 本轮比较次数

        for (int j = 0; j < n - 1 - i; j++) {
            comparisonsInRound++;
            totalComparisons++;

            if (arr[j] > arr[j + 1]) {
                // 交换
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapsInRound++;
                totalSwaps++;
            }
        }

        // 打印本轮结果
        cout << "第 " << i + 1 << " 轮后：\t";
        printArray(arr, n);

        // 标注哪个元素归位了
        cout << "  ← 比较 " << comparisonsInRound << " 次";
        if (swapsInRound > 0) {
            cout << "，交换 " << swapsInRound << " 次";
        }
        cout << "，arr[" << n - 1 - i << "]=" << arr[n - 1 - i] << " 已归位";
        cout << endl;
    }

    // 输出最终统计
    cout << "\n📊 排序统计：" << endl;
    cout << "  - 数组长度：n = " << n << endl;
    cout << "  - 总轮数：n-1 = " << n-1 << endl;
    cout << "  - 总比较次数：" << totalComparisons << " 次" << endl;
    cout << "  - 总交换次数：" << totalSwaps << " 次" << endl;
    cout << "  - 理论最大比较次数：n(n-1)/2 = " << n*(n-1)/2 << " 次" << endl;

    cout << "\n✅ 最终结果：";
    printArray(arr, n);
    cout << endl;

    // 验证排序是否正确
    bool isSorted = true;
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            isSorted = false;
            break;
        }
    }
    cout << "\n排序验证：" << (isSorted ? "✅ 排序正确！" : "❌ 排序有误！") << endl;

    cout << "\n📝 练习答案总结：" << endl;
    cout << "  初始： [9, 2, 7, 4, 1]" << endl;
    cout << "  第1轮后：[2, 7, 4, 1, 9]  ← 最大值 9 归位" << endl;
    cout << "  第2轮后：[2, 4, 1, 7, 9]  ← 次大值 7 归位" << endl;
    cout << "  第3轮后：[2, 1, 4, 7, 9]  ← 第三大值 4 归位" << endl;
    cout << "  第4轮后：[1, 2, 4, 7, 9]  ← 排序完成！" << endl;
}

// ============================================================
// 主函数：依次运行三个演示程序
// ============================================================
int main() {
    cout << "╔══════════════════════════════════════════════════════════╗" << endl;
    cout << "║       第42课：排排坐吃果果——冒泡排序                     ║" << endl;
    cout << "║       C++ 趣味学习 - 程序演示                            ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════╝" << endl;

    // 运行程序1：基础冒泡排序
    program1_basicBubbleSort();

    // 运行程序2：优化版冒泡排序
    program2_optimizedBubbleSort();

    // 运行程序3：逐步展示排序过程（练习答案）
    program3_stepByStepSort();

    cout << "\n" << string(60, '=') << endl;
    cout << "  🎉 所有演示程序运行完毕！" << endl;
    cout << "  请同学们仔细阅读代码中的注释，理解每行代码的作用。" << endl;
    cout << string(60, '=') << endl;

    return 0;
}
