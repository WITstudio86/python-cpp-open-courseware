/*
 * ============================================================
 * 第9课：冒泡排序——相邻交换
 * lesson09_bubble_sort.cpp
 *
 * 本程序包含：
 *   1. 基础版冒泡排序函数（bubbleSort）
 *   2. 优化版冒泡排序函数（bubbleSortOptimized，带提前终止）
 *   3. 例题1：成绩排序（bubbleSortForGrades）
 *   4. 例题2：数列排序——输出每轮排序过程（bubbleSortWithRounds）
 *   5. main() 函数中包含所有题目的测试用例
 *
 * 适用对象：具备基础C++知识的中小学生
 * ============================================================
 */

#include <iostream>
using namespace std;

// -------------------------------------------------------
// 函数1：基础版冒泡排序（升序排列）
// 参数：
//   arr[] - 待排序的整数数组
//   n     - 数组元素的个数
// 返回值：无（在原数组上直接修改）
// -------------------------------------------------------
void bubbleSort(int arr[], int n) {
    // 外层循环：控制排序的轮数
    // n 个元素最多需要 n-1 轮冒泡
    for (int i = 0; i < n - 1; i++) {

        // 内层循环：进行每一轮的相邻比较和交换
        // j 从 0 到 n-2-i，因为末尾 i 个元素已经排好了
        for (int j = 0; j < n - 1 - i; j++) {

            // 核心判断：如果前面的元素比后面的大
            if (arr[j] > arr[j + 1]) {

                // 交换两个元素（经典的三步交换法）
                int temp = arr[j];        // 第1步：把arr[j]暂存到temp
                arr[j] = arr[j + 1];      // 第2步：把arr[j+1]放到arr[j]的位置
                arr[j + 1] = temp;        // 第3步：把暂存的值放到arr[j+1]的位置
            }
        }
        // 本轮结束，最大值已经"浮"到了正确的位置
    }
}


// -------------------------------------------------------
// 函数2：优化版冒泡排序（带提前终止的标志变量）
// 核心优化：如果某一轮没有发生任何交换，
//           说明数组已经有序，可以直接结束排序
// -------------------------------------------------------
void bubbleSortOptimized(int arr[], int n) {
    // 外层循环：最多 n-1 轮
    for (int i = 0; i < n - 1; i++) {

        // ★ swapped 标志变量：
        //   初始值 false 表示"本轮还没有发生交换"
        //   如果本轮结束仍然为 false，说明数组已有序
        bool swapped = false;

        // 内层循环：相邻比较与交换
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {

                // 交换相邻元素
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                swapped = true;  // 发生了交换，更新标志
            }
        }

        // ★ 提前终止检查：
        //   如果一整轮都没有交换，说明数组已经完全有序
        if (!swapped) {
            // 可以选择在这里打印提示（调试用）
            // cout << "第 " << i + 1 << " 轮没有发生交换，数组已有序，提前结束！" << endl;
            break;  // 跳出外层循环，排序完成
        }
    }
}


// -------------------------------------------------------
// 函数3：打印数组的辅助函数
// -------------------------------------------------------
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        // 元素之间用空格分隔，最后一个元素后面不加空格
        if (i < n - 1) {
            cout << " ";
        }
    }
    cout << endl;  // 输出完一行后换行
}


// -------------------------------------------------------
// 例题1：成绩排序
// 题目描述：有 n 个学生，每个学生有一个成绩（0-100的整数），
//          请将这 n 个学生的成绩从低到高排序输出。
// 使用冒泡排序实现。
// -------------------------------------------------------
void solveProblem1_GradeSorting() {
    cout << "========== 例题1：成绩排序 ==========" << endl;

    // 输入学生人数
    int n;
    cout << "请输入学生人数 n：";
    cin >> n;

    // 输入 n 个学生的成绩
    int grades[1000];  // 题目保证 n ≤ 1000，开足够大的数组
    cout << "请输入 " << n << " 个学生的成绩（0-100的整数）：" << endl;
    for (int i = 0; i < n; i++) {
        cin >> grades[i];
    }

    // 使用优化版冒泡排序对成绩进行升序排列
    bubbleSortOptimized(grades, n);

    // 输出排序后的成绩
    cout << "成绩从低到高排序结果：" << endl;
    printArray(grades, n);

    cout << endl;
}


// -------------------------------------------------------
// 例题2：数列排序——输出每一轮冒泡后的序列状态
// 题目描述：输入一个整数序列，使用冒泡排序将其从小到大排列，
//          输出每一轮冒泡后的序列状态。
// 注意：使用优化版，如果某一轮没有交换则不输出该轮并结束。
// -------------------------------------------------------
void solveProblem2_SequenceSortingWithRounds() {
    cout << "========== 例题2：数列排序（输出每轮过程） ==========" << endl;

    // 输入数列长度
    int n;
    cout << "请输入数列长度 n：";
    cin >> n;

    // 输入 n 个整数
    int arr[100];  // 题目保证 n ≤ 100
    cout << "请输入 " << n << " 个整数：" << endl;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "初始序列：";
    printArray(arr, n);
    cout << "--- 开始排序，逐轮输出 ---" << endl;

    int roundCount = 0;  // 记录实际执行的轮数

    // 冒泡排序（带逐轮输出）
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;  // 本轮是否发生了交换

        // 内层循环：相邻比较与交换
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                // 交换
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }

        // 如果本轮有交换，输出本轮结束后的序列
        if (swapped) {
            roundCount++;
            cout << "第 " << roundCount << " 轮后：";
            printArray(arr, n);
        } else {
            // 本轮没有交换，说明已经有序
            cout << "第 " << i + 1 << " 轮没有发生交换，排序提前结束！" << endl;
            break;
        }
    }

    cout << "--- 排序完成，共执行 " << roundCount << " 轮 ---" << endl;
    cout << "最终结果：";
    printArray(arr, n);

    cout << endl;
}


// -------------------------------------------------------
// main() 函数：程序的入口
// 可以选择运行例题1、例题2或自定义测试
// -------------------------------------------------------
int main() {
    // 提示用户选择模式
    cout << "========================================" << endl;
    cout << "   第9课：冒泡排序——相邻交换" << endl;
    cout << "   请选择要运行的题目：" << endl;
    cout << "   1 - 例题1：成绩排序" << endl;
    cout << "   2 - 例题2：数列排序（输出过程）" << endl;
    cout << "   3 - 基础版冒泡排序测试" << endl;
    cout << "   4 - 优化版冒泡排序测试" << endl;
    cout << "   5 - 全部测试" << endl;
    cout << "========================================" << endl;

    int choice;
    cout << "请输入你的选择（1-5）：";
    cin >> choice;

    cout << endl;

    switch (choice) {
        case 1:
            // 例题1：成绩排序
            solveProblem1_GradeSorting();
            break;

        case 2:
            // 例题2：数列排序（输出每轮过程）
            solveProblem2_SequenceSortingWithRounds();
            break;

        case 3: {
            // 基础版冒泡排序测试
            cout << "========== 基础版冒泡排序测试 ==========" << endl;
            int testArr[] = {5, 3, 8, 1, 2};
            int n = 5;

            cout << "排序前：";
            printArray(testArr, n);

            bubbleSort(testArr, n);  // 调用基础版冒泡排序

            cout << "排序后：";
            printArray(testArr, n);
            cout << endl;
            break;
        }

        case 4: {
            // 优化版冒泡排序测试
            cout << "========== 优化版冒泡排序测试 ==========" << endl;

            // 测试1：普通乱序数组
            cout << "【测试1：乱序数组】" << endl;
            int testArr1[] = {5, 3, 8, 1, 2};
            int n1 = 5;
            cout << "排序前：";
            printArray(testArr1, n1);
            bubbleSortOptimized(testArr1, n1);
            cout << "排序后：";
            printArray(testArr1, n1);
            cout << endl;

            // 测试2：已经有序的数组（验证提前终止）
            cout << "【测试2：已有序数组（验证提前终止）】" << endl;
            int testArr2[] = {1, 2, 3, 4, 5};
            int n2 = 5;
            cout << "排序前：";
            printArray(testArr2, n2);
            bubbleSortOptimized(testArr2, n2);
            cout << "排序后：";
            printArray(testArr2, n2);
            cout << "（如果触发了提前终止，只进行了1轮比较）" << endl;
            cout << endl;

            // 测试3：完全逆序数组（最坏情况）
            cout << "【测试3：完全逆序数组（最坏情况）】" << endl;
            int testArr3[] = {5, 4, 3, 2, 1};
            int n3 = 5;
            cout << "排序前：";
            printArray(testArr3, n3);
            bubbleSortOptimized(testArr3, n3);
            cout << "排序后：";
            printArray(testArr3, n3);
            cout << endl;

            // 测试4：包含重复元素
            cout << "【测试4：包含重复元素】" << endl;
            int testArr4[] = {3, 1, 4, 1, 5, 9, 2, 6};
            int n4 = 8;
            cout << "排序前：";
            printArray(testArr4, n4);
            bubbleSortOptimized(testArr4, n4);
            cout << "排序后：";
            printArray(testArr4, n4);
            cout << endl;

            break;
        }

        case 5:
            // 全部测试
            cout << "========== 运行全部测试 ==========" << endl << endl;
            solveProblem1_GradeSorting();
            solveProblem2_SequenceSortingWithRounds();

            // 额外测试：基础版与优化版对比
            cout << "========== 基础版冒泡排序 ==========" << endl;
            int arr1[] = {9, 7, 5, 3, 1};
            cout << "原数组：";
            printArray(arr1, 5);
            bubbleSort(arr1, 5);
            cout << "排序后：";
            printArray(arr1, 5);
            cout << endl;

            cout << "========== 优化版冒泡排序 ==========" << endl;
            int arr2[] = {9, 7, 5, 3, 1};
            cout << "原数组：";
            printArray(arr2, 5);
            bubbleSortOptimized(arr2, 5);
            cout << "排序后：";
            printArray(arr2, 5);
            cout << endl;

            break;

        default:
            cout << "输入无效，请输入 1-5 之间的数字。" << endl;
            break;
    }

    return 0;  // 程序正常结束
}
