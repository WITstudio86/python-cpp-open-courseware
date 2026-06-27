/*
 * 第26课：平均分大作战——数组遍历
 * 课程项目：成绩统计分析器
 *
 * 知识点：
 *   1. 使用 for 循环遍历数组
 *   2. 数组元素的求和与平均值计算
 *   3. 在遍历中进行条件统计
 *   4. 找最大值、最小值
 *   5. 数据可视化（简易柱状图）
 *
 * 编译方法：
 *   g++ -std=c++11 lesson26_数组遍历.cpp -o lesson26_数组遍历
 *   运行：./lesson26_数组遍历
 */

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// ---------- 示例1：数组的基本遍历 ----------
void ejemplo1_traversalBasico() {
    cout << "╔══════════════════════════════════════╗" << endl;
    cout << "║   示例1：数组的基本遍历             ║" << endl;
    cout << "╚══════════════════════════════════════╝" << endl;
    cout << endl;

    // 声明并初始化一个数组
    int numbers[8] = {15, 28, 3, 47, 9, 62, 31, 54};

    cout << "数组内容：{15, 28, 3, 47, 9, 62, 31, 54}" << endl;
    cout << "数组大小：" << sizeof(numbers) / sizeof(numbers[0]) << " 个元素" << endl;
    cout << endl;

    // 1.1 正向遍历：从头到尾
    cout << "1.1 正向遍历（从头到尾）：" << endl;
    cout << "    下标:  ";
    for (int i = 0; i < 8; i++) {
        cout << "[" << i << "]  ";
    }
    cout << endl;
    cout << "    元素: ";
    for (int i = 0; i < 8; i++) {
        cout << " " << numbers[i];
        if (numbers[i] < 10) cout << "  ";   // 对齐
        else cout << " ";
    }
    cout << endl << endl;

    // 1.2 反向遍历：从尾到头
    cout << "1.2 反向遍历（从尾到头）：" << endl;
    cout << "    下标:  ";
    for (int i = 7; i >= 0; i--) {
        cout << "[" << i << "]  ";
    }
    cout << endl;
    cout << "    元素: ";
    for (int i = 7; i >= 0; i--) {
        cout << " " << numbers[i];
        if (numbers[i] < 10) cout << "  ";
        else cout << " ";
    }
    cout << endl << endl;

    // 1.3 隔一个访问（访问偶数下标元素）
    cout << "1.3 隔一个访问（偶数下标元素）：" << endl;
    cout << "    ";
    for (int i = 0; i < 8; i += 2) {
        cout << "numbers[" << i << "]=" << numbers[i] << "  ";
    }
    cout << endl << endl;

    // 1.4 遍历时显示"第几个"
    cout << "1.4 带编号的遍历：" << endl;
    for (int i = 0; i < 8; i++) {
        cout << "    第" << i + 1 << "个元素：numbers[" << i << "] = " << numbers[i] << endl;
    }
    cout << endl;
}

// ---------- 示例2：求和与平均值计算 ----------
void ejemplo2_sumaYPromedio() {
    cout << "╔══════════════════════════════════════╗" << endl;
    cout << "║   示例2：求和与平均值计算           ║" << endl;
    cout << "╚══════════════════════════════════════╝" << endl;
    cout << endl;

    // 模拟一组考试成绩
    int scores[6] = {85, 92, 78, 95, 88, 72};

    cout << "成绩数组：";
    for (int i = 0; i < 6; i++) {
        cout << scores[i] << " ";
    }
    cout << endl << endl;

    // 2.1 计算总和
    cout << "2.1 计算总和：" << endl;
    int sum = 0;
    cout << "    累加过程演示：" << endl;
    for (int i = 0; i < 6; i++) {
        cout << "    第" << i + 1 << "步：sum = " << sum << " + " << scores[i] << " = ";
        sum += scores[i];  // 等价于 sum = sum + scores[i]
        cout << sum << endl;
    }
    cout << "    最终总和 sum = " << sum << endl;
    cout << endl;

    // 2.2 计算平均值
    cout << "2.2 计算平均值：" << endl;
    // 方法1：直接除法（整数除法，会丢失小数）
    int avgInt = sum / 6;
    cout << "    整数除法 sum / 6 = " << avgInt << "  （错误！丢失了小数部分）" << endl;
    // 方法2：强制类型转换
    double avgDouble1 = (double)sum / 6;
    cout << "    (double)sum / 6 = " << avgDouble1 << "  （正确）" << endl;
    // 方法3：乘以1.0
    double avgDouble2 = sum * 1.0 / 6;
    cout << "    sum * 1.0 / 6 = " << avgDouble2 << "  （正确）" << endl;
    // 方法4：除数写小数
    double avgDouble3 = sum / 6.0;
    cout << "    sum / 6.0 = " << avgDouble3 << "  （正确）" << endl;
    cout << endl;

    // 2.3 格式化输出
    cout << fixed << setprecision(2);  // 保留2位小数
    cout << "2.3 成绩统计：" << endl;
    cout << "    ┌──────────┬────────┐" << endl;
    cout << "    │   项目   │  数值  │" << endl;
    cout << "    ├──────────┼────────┤" << endl;
    cout << "    │  总  分  │ " << setw(4) << sum << "  │" << endl;
    cout << "    │  平均分  │ " << setw(6) << avgDouble1 << " │" << endl;
    cout << "    └──────────┴────────┘" << endl;
    cout << endl;

    // 恢复默认格式
    cout << defaultfloat;
}

// ---------- 示例3：完整的成绩统计分析器 ----------
void ejemplo3_analizadorCompleto() {
    cout << "╔══════════════════════════════════════╗" << endl;
    cout << "║   示例3：完整的成绩统计分析器       ║" << endl;
    cout << "╚══════════════════════════════════════╝" << endl;
    cout << endl;

    const int MAX = 100;
    int scores[MAX];
    int n;

    // ===== 输入阶段 =====
    cout << "请输入班级人数（最多" << MAX << "人）：";
    cin >> n;

    if (n <= 0 || n > MAX) {
        cout << "人数超出范围，程序退出。" << endl;
        return;
    }

    cout << "\n请逐个输入成绩（0~100）：" << endl;
    for (int i = 0; i < n; i++) {
        cout << "  第" << i + 1 << "位同学的成绩：";
        cin >> scores[i];

        // 输入验证：确保成绩在0~100之间
        while (scores[i] < 0 || scores[i] > 100) {
            cout << "  成绩无效！请输入0~100之间的分数：";
            cin >> scores[i];
        }
    }

    // ===== 显示所有成绩 =====
    cout << "\n===== 全班成绩一览 =====" << endl;
    cout << "┌──────┬───────┐" << endl;
    cout << "│ 编号 │ 成绩  │" << endl;
    cout << "├──────┼───────┤" << endl;
    for (int i = 0; i < n; i++) {
        cout << "│  " << setw(2) << i + 1 << "   │  " << setw(3) << scores[i] << "  │" << endl;
    }
    cout << "└──────┴───────┘" << endl;

    // ===== 统计分析 =====
    // 1. 计算总和
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += scores[i];
    }
    double average = (double)sum / n;

    // 2. 找最高分和最低分（同时记录位置）
    int maxScore = scores[0];
    int minScore = scores[0];
    int maxIndex = 0;  // 最高分所在位置（下标）
    int minIndex = 0;  // 最低分所在位置（下标）

    for (int i = 1; i < n; i++) {
        if (scores[i] > maxScore) {
            maxScore = scores[i];
            maxIndex = i;
        }
        if (scores[i] < minScore) {
            minScore = scores[i];
            minIndex = i;
        }
    }

    // 3. 分数段统计
    int excellent = 0;   // 优秀 >= 90
    int good = 0;        // 良好 80~89
    int medium = 0;      // 中等 70~79
    int pass = 0;        // 及格 60~69
    int fail = 0;        // 不及格 < 60

    int aboveAvg = 0;    // 高于平均分的人数
    int belowAvg = 0;    // 低于平均分的人数
    int equalAvg = 0;    // 等于平均分的人数

    for (int i = 0; i < n; i++) {
        // 分数段统计
        if (scores[i] >= 90) {
            excellent++;
        } else if (scores[i] >= 80) {
            good++;
        } else if (scores[i] >= 70) {
            medium++;
        } else if (scores[i] >= 60) {
            pass++;
        } else {
            fail++;
        }

        // 与平均分比较
        if (scores[i] > average) {
            aboveAvg++;
        } else if (scores[i] < average) {
            belowAvg++;
        } else {
            equalAvg++;
        }
    }

    // ===== 输出分析报告 =====
    cout << fixed << setprecision(1);
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║          成  绩  分  析  报  告       ║" << endl;
    cout << "╠════════════════════════════════════════╣" << endl;
    cout << "║                                        ║" << endl;
    cout << "║  【基本数据】                          ║" << endl;
    cout << "║   班级人数：     " << setw(3) << n << " 人                   ║" << endl;
    cout << "║   总分：         " << setw(3) << sum << " 分                   ║" << endl;
    cout << "║   平均分：       " << setw(5) << average << " 分                  ║" << endl;
    cout << "║   最高分：       " << setw(3) << maxScore << " 分（第" << maxIndex + 1 << "位同学）    ║" << endl;
    cout << "║   最低分：       " << setw(3) << minScore << " 分（第" << minIndex + 1 << "位同学）    ║" << endl;
    cout << "║                                        ║" << endl;
    cout << "║  【分数段分布】                        ║" << endl;
    cout << "║   优秀（90~100）：" << setw(3) << excellent << " 人  "
         << "占比 " << setw(5) << (double)excellent / n * 100 << "%     ║" << endl;
    cout << "║   良好（80~89）： " << setw(3) << good << " 人  "
         << "占比 " << setw(5) << (double)good / n * 100 << "%     ║" << endl;
    cout << "║   中等（70~79）： " << setw(3) << medium << " 人  "
         << "占比 " << setw(5) << (double)medium / n * 100 << "%     ║" << endl;
    cout << "║   及格（60~69）： " << setw(3) << pass << " 人  "
         << "占比 " << setw(5) << (double)pass / n * 100 << "%     ║" << endl;
    cout << "║   不及格（<60）： " << setw(3) << fail << " 人  "
         << "占比 " << setw(5) << (double)fail / n * 100 << "%     ║" << endl;
    cout << "║                                        ║" << endl;
    cout << "║  【平均分对比】                        ║" << endl;
    cout << "║   高于平均分：   " << setw(3) << aboveAvg << " 人                   ║" << endl;
    cout << "║   低于平均分：   " << setw(3) << belowAvg << " 人                   ║" << endl;
    if (equalAvg > 0) {
        cout << "║   等于平均分：   " << setw(3) << equalAvg << " 人                   ║" << endl;
    }
    cout << "║   及格率：       " << setw(5)
         << (double)(excellent + good + medium + pass) / n * 100 << "%                ║" << endl;
    cout << "║                                        ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;

    // ===== 成绩柱状图 =====
    cout << "\n===== 成绩分布柱状图 =====" << endl;
    cout << endl;

    // 找到最大值用于确定柱状图比例
    int maxCount = excellent;
    if (good > maxCount) maxCount = good;
    if (medium > maxCount) maxCount = medium;
    if (pass > maxCount) maxCount = pass;
    if (fail > maxCount) maxCount = fail;
    if (maxCount == 0) maxCount = 1;  // 避免除以0

    const int BAR_MAX = 30;  // 柱状图最大宽度

    string labels[5] = {"优秀(≥90)", "良好(80)", "中等(70)", "及格(60)", "不及格  "};
    int counts[5] = {excellent, good, medium, pass, fail};

    cout << "    0%        25%        50%        75%       100%" << endl;
    cout << "    ├──────────┼──────────┼──────────┼──────────┤" << endl;

    for (int i = 0; i < 5; i++) {
        int barLen = (int)((double)counts[i] / maxCount * BAR_MAX);
        if (counts[i] > 0 && barLen == 0) barLen = 1;  // 至少有1格

        cout << labels[i] << " │";
        for (int j = 0; j < barLen; j++) {
            cout << "█";
        }
        for (int j = barLen; j < BAR_MAX; j++) {
            cout << " ";
        }
        cout << "│ " << setw(2) << counts[i] << "人" << endl;
    }
    cout << "    └──────────┴──────────┴──────────┴──────────┘" << endl;

    // 恢复浮点数默认格式
    cout << defaultfloat;
    cout << endl;
}

// ---------- 练习答案 ----------
void ejercicio1_respuesta() {
    cout << "╔══════════════════════════════════════╗" << endl;
    cout << "║   练习1答案：计算总和与平均值       ║" << endl;
    cout << "╚══════════════════════════════════════╝" << endl;
    cout << endl;

    int numbers[6] = {23, 45, 12, 67, 34, 89};
    int sum = 0;                          // 答案：初始化为0
    for (int i = 0; i < 6; i++) {         // 答案：i < 6
        sum += numbers[i];                // 答案：numbers[i]
    }
    double avg = sum / 6.0;               // 答案：sum / 6.0

    cout << "补全后的代码运行结果：" << endl;
    cout << "    总和：" << sum << endl;
    cout << "    平均值：" << avg << endl;
    cout << endl;

    cout << "填空答案：" << endl;
    cout << "    第1空：0（累加器初始化为0）" << endl;
    cout << "    第2空：6（数组有6个元素）" << endl;
    cout << "    第3空：numbers[i]（当前元素）" << endl;
    cout << "    第4空：sum（总和）" << endl;
    cout << endl;
}

void ejercicio2_respuesta() {
    cout << "╔══════════════════════════════════════╗" << endl;
    cout << "║   练习2答案：找最大最小值           ║" << endl;
    cout << "╚══════════════════════════════════════╝" << endl;
    cout << endl;

    int arr[8] = {34, 12, 89, 7, 56, 91, 23, 45};

    cout << "数组内容：";
    for (int i = 0; i < 8; i++) {
        cout << arr[i] << " ";
    }
    cout << endl << endl;

    // 找最大值和最小值及其位置
    int maxVal = arr[0];
    int minVal = arr[0];
    int maxPos = 0;
    int minPos = 0;

    for (int i = 1; i < 8; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
            maxPos = i;
        }
        if (arr[i] < minVal) {
            minVal = arr[i];
            minPos = i;
        }
    }

    cout << "分析结果：" << endl;
    cout << "    最大值：" << maxVal << "，位于下标 " << maxPos
         << "（第" << maxPos + 1 << "个元素）" << endl;
    cout << "    最小值：" << minVal << "，位于下标 " << minPos
         << "（第" << minPos + 1 << "个元素）" << endl;
    cout << endl;

    cout << "参考代码：" << endl;
    cout << "┌──────────────────────────────────────────┐" << endl;
    cout << "│ int maxVal = arr[0], minVal = arr[0];    │" << endl;
    cout << "│ int maxPos = 0, minPos = 0;              │" << endl;
    cout << "│ for (int i = 1; i < 8; i++) {            │" << endl;
    cout << "│     if (arr[i] > maxVal) {               │" << endl;
    cout << "│         maxVal = arr[i]; maxPos = i;     │" << endl;
    cout << "│     }                                    │" << endl;
    cout << "│     if (arr[i] < minVal) {               │" << endl;
    cout << "│         minVal = arr[i]; minPos = i;     │" << endl;
    cout << "│     }                                    │" << endl;
    cout << "│ }                                        │" << endl;
    cout << "└──────────────────────────────────────────┘" << endl;
    cout << endl;
}

void ejercicio3_respuesta() {
    cout << "╔══════════════════════════════════════╗" << endl;
    cout << "║   练习3答案：统计奇偶数             ║" << endl;
    cout << "╚══════════════════════════════════════╝" << endl;
    cout << endl;

    int numbers[10] = {7, 14, 23, 8, 19, 30, 45, 12, 6, 33};

    cout << "数组内容：";
    for (int i = 0; i < 10; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl << endl;

    int oddCount = 0;   // 奇数个数
    int evenCount = 0;  // 偶数个数

    cout << "逐一判断：" << endl;
    for (int i = 0; i < 10; i++) {
        if (numbers[i] % 2 == 0) {
            cout << "    " << numbers[i] << " → 偶数" << endl;
            evenCount++;
        } else {
            cout << "    " << numbers[i] << " → 奇数" << endl;
            oddCount++;
        }
    }

    cout << "\n统计结果：" << endl;
    cout << "    奇数个数：" << oddCount << endl;
    cout << "    偶数个数：" << evenCount << endl;
    cout << endl;

    cout << "关键知识点：判断奇偶性用 % 运算符" << endl;
    cout << "    num % 2 == 0  →  偶数" << endl;
    cout << "    num % 2 == 1  →  奇数" << endl;
    cout << endl;
}

// ---------- 挑战任务：增强版成绩统计分析器 ----------
void desafio_analizadorAvanzado() {
    cout << "╔══════════════════════════════════════╗" << endl;
    cout << "║   挑战任务：增强版成绩统计分析器     ║" << endl;
    cout << "╚══════════════════════════════════════╝" << endl;
    cout << endl;

    const int MAX = 100;
    int scores[MAX];
    string grades[MAX];  // 等级数组
    int n;

    // 输入成绩
    cout << "请输入班级人数（最多" << MAX << "人）：";
    cin >> n;
    if (n <= 0 || n > MAX) {
        cout << "人数超出范围！" << endl;
        return;
    }

    cout << "\n请逐个输入成绩（0~100）：" << endl;
    for (int i = 0; i < n; i++) {
        cout << "  第" << i + 1 << "位同学：";
        cin >> scores[i];
        while (scores[i] < 0 || scores[i] > 100) {
            cout << "  成绩无效，请重新输入（0~100）：";
            cin >> scores[i];
        }

        // 评定等级
        if (scores[i] >= 90) grades[i] = "A等（优秀）";
        else if (scores[i] >= 80) grades[i] = "B等（良好）";
        else if (scores[i] >= 70) grades[i] = "C等（中等）";
        else if (scores[i] >= 60) grades[i] = "D等（及格）";
        else grades[i] = "E等（不及格）";
    }

    // 计算基本统计量
    int sum = 0;
    for (int i = 0; i < n; i++) sum += scores[i];
    double average = (double)sum / n;

    // 找最高分和最低分
    int maxScore = scores[0], minScore = scores[0];
    for (int i = 1; i < n; i++) {
        if (scores[i] > maxScore) maxScore = scores[i];
        if (scores[i] < minScore) minScore = scores[i];
    }

    // 冒泡排序（从高到低）
    // 先复制一份数组用于排序
    int sortedScores[MAX];
    int sortedIndex[MAX];  // 记录原始编号
    for (int i = 0; i < n; i++) {
        sortedScores[i] = scores[i];
        sortedIndex[i] = i;  // 原始编号 = 下标 + 1
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (sortedScores[j] < sortedScores[j + 1]) {
                // 交换成绩
                int tempScore = sortedScores[j];
                sortedScores[j] = sortedScores[j + 1];
                sortedScores[j + 1] = tempScore;
                // 同时交换编号
                int tempIndex = sortedIndex[j];
                sortedIndex[j] = sortedIndex[j + 1];
                sortedIndex[j + 1] = tempIndex;
            }
        }
    }

    // 计算中位数
    double median;
    if (n % 2 == 1) {
        // 奇数个：取中间那个
        median = sortedScores[n / 2];
    } else {
        // 偶数个：取中间两个的平均值
        median = (sortedScores[n / 2 - 1] + sortedScores[n / 2]) / 2.0;
    }

    // ===== 输出报告 =====
    cout << fixed << setprecision(1);
    cout << "\n╔══════════════════════════════════════════════╗" << endl;
    cout << "║           成  绩  分  析  报  告            ║" << endl;
    cout << "╠══════════════════════════════════════════════╣" << endl;
    cout << "║  班级人数：" << setw(3) << n << "人    总分：" << setw(4) << sum
         << "    平均分：" << setw(5) << average << "  ║" << endl;
    cout << "║  最高分：" << setw(3) << maxScore << "分    最低分：" << setw(3) << minScore
         << "分    中位数：" << setw(5) << median << "  ║" << endl;
    cout << "╠══════════════════════════════════════════════╣" << endl;

    // 成绩排行榜
    cout << "║  成绩排行榜（从高到低）：                   ║" << endl;
    cout << "║  ┌──────┬──────┬───────┬──────────┐         ║" << endl;
    cout << "║  │ 排名 │ 编号 │ 成绩  │   等级   │         ║" << endl;
    cout << "║  ├──────┼──────┼───────┼──────────┤         ║" << endl;
    for (int i = 0; i < n; i++) {
        int origIndex = sortedIndex[i] + 1;  // 原始编号
        int origScore = scores[origIndex - 1];
        cout << "║  │  " << setw(2) << i + 1 << "  │  " << setw(2) << origIndex
             << "  │  " << setw(3) << origScore << "  │ " << grades[origIndex - 1];
        // 补空格对齐
        int gradeDisplayLen = grades[origIndex - 1].length();
        for (int s = 0; s < 10 - gradeDisplayLen; s++) cout << " ";
        cout << "│         ║" << endl;
    }
    cout << "║  └──────┴──────┴───────┴──────────┘         ║" << endl;

    // 统计及格率
    int passCount = 0;
    for (int i = 0; i < n; i++) {
        if (scores[i] >= 60) passCount++;
    }
    cout << "║  及格率：" << (double)passCount / n * 100 << "%                              ║" << endl;
    cout << "╚══════════════════════════════════════════════╝" << endl;

    cout << defaultfloat;
    cout << endl;
}

// ---------- 主函数 ----------
int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║     第26课：平均分大作战——数组遍历              ║" << endl;
    cout << "║     C++ 趣味学习——成绩统计分析器                ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;
    cout << endl;

    int opcion;

    do {
        cout << "请选择要运行的功能：" << endl;
        cout << "    1. 示例1：数组的基本遍历" << endl;
        cout << "    2. 示例2：求和与平均值计算" << endl;
        cout << "    3. 示例3：完整的成绩统计分析器" << endl;
        cout << "    4. 练习1答案：计算总和与平均值" << endl;
        cout << "    5. 练习2答案：找最大最小值" << endl;
        cout << "    6. 练习3答案：统计奇偶数" << endl;
        cout << "    7. 挑战任务：增强版成绩统计分析器" << endl;
        cout << "    0. 退出程序" << endl;
        cout << "请输入数字选择：";
        cin >> opcion;
        cout << endl;

        switch (opcion) {
            case 1:
                ejemplo1_traversalBasico();
                break;
            case 2:
                ejemplo2_sumaYPromedio();
                break;
            case 3:
                ejemplo3_analizadorCompleto();
                break;
            case 4:
                ejercicio1_respuesta();
                break;
            case 5:
                ejercicio2_respuesta();
                break;
            case 6:
                ejercicio3_respuesta();
                break;
            case 7:
                desafio_analizadorAvanzado();
                break;
            case 0:
                cout << "再见！继续加油，你离编程高手越来越近了！" << endl;
                break;
            default:
                cout << "无效选择，请重新输入！" << endl;
        }
    } while (opcion != 0);

    return 0;
}
