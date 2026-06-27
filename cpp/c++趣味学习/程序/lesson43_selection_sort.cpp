/*
 * 第43课：快刀斩乱麻——选择排序
 * 主题：选择排序（基础选择排序、从大到小选择排序、挑战任务）
 * 算法核心：每轮找最值下标，然后一次性交换
 * 适用：中小学C++趣味学习
 * 日期：2026年
 */

#include <iostream>
#include <cstdlib>  // 用于 rand() 和 srand()
#include <ctime>    // 用于 time()
using namespace std;

int main() {
    // ==========================================
    // 示例1：基础选择排序（从小到大排列）
    // ==========================================
    cout << "========================================" << endl;
    cout << "  示例1：基础选择排序（从小到大）" << endl;
    cout << "========================================" << endl;

    int arr1[] = {64, 25, 12, 22, 11};
    int n1 = 5;  // 数组长度

    // 打印排序前的数组
    cout << "排序前的数组：";
    for (int i = 0; i < n1; i++) {
        cout << arr1[i] << " ";
    }
    cout << endl << endl;

    // ===== 选择排序核心代码 =====
    // 外层循环：控制已排序区的边界
    // 注意：只需要 n-1 轮，因为最后一轮只剩一个元素，它自然就在正确的位置上
    for (int i = 0; i < n1 - 1; i++) {
        // 第 i 轮：在 arr[i] 到 arr[n-1] 之间（未排序区）找最小值的下标
        int minIndex = i;  // 先假设未排序区的第一个就是最小的

        // 内层循环：遍历未排序区，找出真正的最小值
        for (int j = i + 1; j < n1; j++) {
            if (arr1[j] < arr1[minIndex]) {  // 如果发现更小的元素
                minIndex = j;                // 更新最小值的下标
            }
        }

        // 如果找到的最小值不在第 i 个位置，就将它交换到未排序区的第一位
        if (minIndex != i) {
            int temp = arr1[i];
            arr1[i] = arr1[minIndex];
            arr1[minIndex] = temp;
        }

        // 打印每一轮排序后的结果（帮助学生理解算法过程）
        cout << "第 " << i + 1 << " 轮后：";
        for (int k = 0; k < n1; k++) {
            cout << arr1[k] << " ";
        }
        cout << endl;
    }

    // 打印最终排序结果
    cout << "\n排序后的数组：";
    for (int i = 0; i < n1; i++) {
        cout << arr1[i] << " ";
    }
    cout << endl << endl;

    // ==========================================
    // 示例2：选择排序从大到小排列
    // ==========================================
    cout << "========================================" << endl;
    cout << "  示例2：选择排序（从大到小）" << endl;
    cout << "========================================" << endl;

    int arr2[] = {64, 25, 12, 22, 11};
    int n2 = 5;

    cout << "排序前的数组：";
    for (int i = 0; i < n2; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl << endl;

    // ===== 从大到小选择排序核心代码 =====
    // 思路：和从小到大一样，只是把"找最小"改为"找最大"
    for (int i = 0; i < n2 - 1; i++) {
        int maxIndex = i;  // 假设第 i 个是最大的

        for (int j = i + 1; j < n2; j++) {
            if (arr2[j] > arr2[maxIndex]) {  // ★ 关键修改：< 改为 >
                maxIndex = j;
            }
        }

        if (maxIndex != i) {
            int temp = arr2[i];
            arr2[i] = arr2[maxIndex];
            arr2[maxIndex] = temp;
        }

        cout << "第 " << i + 1 << " 轮后：";
        for (int k = 0; k < n2; k++) {
            cout << arr2[k] << " ";
        }
        cout << endl;
    }

    cout << "\n从大到小排序结果：";
    for (int i = 0; i < n2; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl << endl;

    // ==========================================
    // 示例3：成绩排序应用（从高到低排名）
    // ==========================================
    cout << "========================================" << endl;
    cout << "  示例3：考试成绩排名" << endl;
    cout << "========================================" << endl;

    int scores[] = {85, 92, 78, 95, 88};
    int nScores = 5;

    cout << "原始成绩：";
    for (int i = 0; i < nScores; i++) {
        cout << scores[i] << " ";
    }
    cout << endl;

    // 选择排序：从高到低（降序）
    for (int i = 0; i < nScores - 1; i++) {
        int maxIndex = i;
        for (int j = i + 1; j < nScores; j++) {
            if (scores[j] > scores[maxIndex]) {
                maxIndex = j;
            }
        }
        if (maxIndex != i) {
            int temp = scores[i];
            scores[i] = scores[maxIndex];
            scores[maxIndex] = temp;
        }
    }

    cout << "成绩排名（从高到低）：" << endl;
    for (int i = 0; i < nScores; i++) {
        cout << "第 " << i + 1 << " 名：" << scores[i] << " 分" << endl;
    }
    cout << endl;

    // ==========================================
    // 挑战任务：排序算法大比拼
    // ==========================================
    cout << "========================================" << endl;
    cout << "  挑战任务：冒泡排序 VS 选择排序" << endl;
    cout << "========================================" << endl;

    // 用随机种子生成随机数
    srand(time(0));

    const int SIZE = 10;
    int original[SIZE];     // 原始数组
    int arrBubble[SIZE];    // 用于冒泡排序
    int arrSelect[SIZE];    // 用于选择排序

    // 生成随机数组
    cout << "随机生成的数组：";
    for (int i = 0; i < SIZE; i++) {
        original[i] = rand() % 100 + 1;  // 生成 1~100 的随机数
        arrBubble[i] = original[i];      // 复制一份给冒泡排序
        arrSelect[i] = original[i];      // 复制一份给选择排序
        cout << original[i] << " ";
    }
    cout << endl << endl;

    // ----- 冒泡排序（带统计）-----
    int bubbleCompares = 0;  // 比较次数
    int bubbleSwaps = 0;     // 交换次数

    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = 0; j < SIZE - 1 - i; j++) {
            bubbleCompares++;  // 统计比较次数
            if (arrBubble[j] > arrBubble[j + 1]) {
                bubbleSwaps++;  // 统计交换次数
                int temp = arrBubble[j];
                arrBubble[j] = arrBubble[j + 1];
                arrBubble[j + 1] = temp;
            }
        }
    }

    cout << "冒泡排序结果：";
    for (int i = 0; i < SIZE; i++) {
        cout << arrBubble[i] << " ";
    }
    cout << endl;
    cout << "  比较次数：" << bubbleCompares << "  交换次数：" << bubbleSwaps << endl << endl;

    // ----- 选择排序（带统计）-----
    int selectCompares = 0;  // 比较次数
    int selectSwaps = 0;     // 交换次数

    for (int i = 0; i < SIZE - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < SIZE; j++) {
            selectCompares++;  // 统计比较次数
            if (arrSelect[j] < arrSelect[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            selectSwaps++;  // 统计交换次数
            int temp = arrSelect[i];
            arrSelect[i] = arrSelect[minIndex];
            arrSelect[minIndex] = temp;
        }
    }

    cout << "选择排序结果：";
    for (int i = 0; i < SIZE; i++) {
        cout << arrSelect[i] << " ";
    }
    cout << endl;
    cout << "  比较次数：" << selectCompares << "  交换次数：" << selectSwaps << endl << endl;

    // ----- 结果分析 -----
    cout << "========== 分析 ==========" << endl;
    cout << "冒泡排序交换了 " << bubbleSwaps << " 次，" << endl;
    cout << "选择排序只交换了 " << selectSwaps << " 次！" << endl;
    cout << endl;
    if (selectSwaps <= bubbleSwaps) {
        cout << "结论：在这个例子中，选择排序的交换次数更少。" << endl;
        cout << "这是因为选择排序每轮最多只交换 1 次，" << endl;
        cout << "而冒泡排序可能每轮交换多次。" << endl;
        cout << "当数据量大时，选择排序的写操作明显少于冒泡排序。" << endl;
    }

    // ==========================================
    // 练习参考答案
    // ==========================================
    cout << "\n========================================" << endl;
    cout << "  课后练习参考答案" << endl;
    cout << "========================================" << endl;

    // ---------- 练习1：手动模拟 ----------
    cout << "\n--- 练习1：手动模拟选择排序 ---" << endl;
    cout << "给定数组：[29, 10, 14, 37, 13]" << endl;
    cout << "第1轮：最小10（下标1），与29交换 → 10, 29, 14, 37, 13" << endl;
    cout << "第2轮：最小13（下标4），与29交换 → 10, 13, 14, 37, 29" << endl;
    cout << "第3轮：最小14（下标2），已在正确位置 → 10, 13, 14, 37, 29" << endl;
    cout << "第4轮：最小29（下标4），与37交换 → 10, 13, 14, 29, 37" << endl;
    cout << "排序完成！" << endl;

    // ---------- 练习2：成绩排序 ----------
    cout << "\n--- 练习2：成绩排序（用选择排序）---" << endl;
    {
        int testScores[] = {85, 92, 78, 95, 88};
        int n = 5;

        cout << "原始成绩：";
        for (int i = 0; i < n; i++) {
            cout << testScores[i] << " ";
        }
        cout << endl;

        // 选择排序从高到低
        for (int i = 0; i < n - 1; i++) {
            int maxIdx = i;
            for (int j = i + 1; j < n; j++) {
                if (testScores[j] > testScores[maxIdx]) {
                    maxIdx = j;
                }
            }
            if (maxIdx != i) {
                int t = testScores[i];
                testScores[i] = testScores[maxIdx];
                testScores[maxIdx] = t;
            }
        }

        cout << "排名结果：";
        for (int i = 0; i < n; i++) {
            cout << testScores[i] << " ";
        }
        cout << endl;
    }

    // ---------- 练习3：代码输出 ----------
    cout << "\n--- 练习3：代码输出结果 ---" << endl;
    cout << "给定数组：[3, 1, 4, 1, 5]" << endl;
    cout << "选择排序（从小到大）后：1, 1, 3, 4, 5" << endl;
    cout << "说明：选择排序能正确处理重复元素。" << endl;

    cout << "\n========== 第43课学习完毕！ ==========" << endl;

    return 0;
}
