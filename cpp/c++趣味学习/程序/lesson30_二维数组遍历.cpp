/*
 * ==========================================
 *  第30课：矩阵总动员——二维数组遍历
 *  知识点：嵌套循环遍历二维数组、行和、列和
 *  项目：矩阵行列表
 *  C++趣味学习系列
 * ==========================================
 */

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    // =====================================
    // 示例1：基本嵌套循环遍历二维数组
    // =====================================
    cout << "========== 示例1：嵌套循环遍历二维数组 ==========" << endl;

    int grid[3][4] = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9, 10, 11, 12}
    };

    cout << "使用嵌套循环遍历 3×4 的二维数组：" << endl;
    cout << "执行顺序：外层 i=0 → 内层 j=0,1,2,3 → 外层 i=1 → 内层 j=0,1,2,3 → ..." << endl;
    cout << endl;

    // 逐行遍历
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            cout << "grid[" << i << "][" << j << "] = " << setw(2) << grid[i][j] << "  ";
        }
        cout << endl;   // 每行结束后换行
    }
    cout << endl;

    // 逐列遍历演示
    cout << "--- 逐列遍历（了解即可） ---" << endl;
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 3; i++) {
            cout << grid[i][j] << " ";
        }
        cout << "(第" << j + 1 << "列元素)" << endl;
    }
    cout << endl;

    // =====================================
    // 示例2：计算行和与列和
    // =====================================
    cout << "========== 示例2：计算行和与列和 ==========" << endl;

    int matrix[3][4] = {
        {12, 25,  8, 19},
        {33,  7, 41, 15},
        {22, 18,  5, 30}
    };

    const int ROWS = 3;
    const int COLS = 4;

    // 显示矩阵
    cout << "原始矩阵：" << endl;
    for (int i = 0; i < ROWS; i++) {
        cout << "  ";
        for (int j = 0; j < COLS; j++) {
            cout << setw(4) << matrix[i][j];
        }
        cout << endl;
    }
    cout << endl;

    // 计算每行的和
    cout << "--- 行和 ---" << endl;
    int rowSums[ROWS];
    for (int i = 0; i < ROWS; i++) {
        rowSums[i] = 0;
        for (int j = 0; j < COLS; j++) {
            rowSums[i] += matrix[i][j];
        }
        cout << "第" << i + 1 << "行: ";
        for (int j = 0; j < COLS; j++) {
            cout << matrix[i][j];
            if (j < COLS - 1) cout << " + ";
        }
        cout << " = " << rowSums[i] << endl;
    }
    cout << endl;

    // 计算每列的和
    cout << "--- 列和 ---" << endl;
    int colSums[COLS];
    for (int j = 0; j < COLS; j++) {
        colSums[j] = 0;
        for (int i = 0; i < ROWS; i++) {
            colSums[j] += matrix[i][j];
        }
        cout << "第" << j + 1 << "列: ";
        for (int i = 0; i < ROWS; i++) {
            cout << matrix[i][j];
            if (i < ROWS - 1) cout << " + ";
        }
        cout << " = " << colSums[j] << endl;
    }
    cout << endl;

    // 计算总和
    int grandTotal = 0;
    int elementCount = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grandTotal += matrix[i][j];
            elementCount++;
        }
    }
    cout << "--- 总和与平均值 ---" << endl;
    cout << "总和 = " << grandTotal << endl;
    cout << "元素个数 = " << elementCount << " (行数×列数 = " << ROWS << "×" << COLS << " = " << ROWS * COLS << ")" << endl;
    cout << "平均值 = " << fixed << setprecision(2) << grandTotal * 1.0 / elementCount << endl;
    cout << endl;

    // =====================================
    // 示例3：完整矩阵行列表（带格式化输出）
    // =====================================
    cout << "========== 示例3：矩阵行列表（完整版） ==========" << endl;

    // 一个5×5的矩阵
    int data[5][5] = {
        { 8, 15,  3, 22,  7},
        {14,  6, 19, 11, 25},
        { 2, 18,  9, 31, 12},
        {20, 27,  5, 16, 10},
        {13,  4, 24, 17, 21}
    };

    const int SIZE = 5;

    // 计算每行的和
    int dataRowSums[SIZE];
    for (int i = 0; i < SIZE; i++) {
        dataRowSums[i] = 0;
        for (int j = 0; j < SIZE; j++) {
            dataRowSums[i] += data[i][j];
        }
    }

    // 计算每列的和
    int dataColSums[SIZE];
    for (int j = 0; j < SIZE; j++) {
        dataColSums[j] = 0;
        for (int i = 0; i < SIZE; i++) {
            dataColSums[j] += data[i][j];
        }
    }

    // 计算总和
    int dataTotal = 0;
    for (int i = 0; i < SIZE; i++) {
        dataTotal += dataRowSums[i];
    }

    // 格式化输出矩阵行列表
    cout << "╔══════════════════════════════════════════════════════╗" << endl;
    cout << "║                   矩阵行列表                        ║" << endl;
    cout << "╠═════════╦═════════╦═════════╦═════════╦═════════╦═════════╣" << endl;
    cout << "║         ║  列 1   ║  列 2   ║  列 3   ║  列 4   ║  列 5   ║  行 和  ║" << endl;
    cout << "╠═════════╬═════════╬═════════╬═════════╬═════════╬═════════╬═════════╣" << endl;
    for (int i = 0; i < SIZE; i++) {
        cout << "║ 行 " << i + 1 << "   ║";
        for (int j = 0; j < SIZE; j++) {
            cout << "  " << setw(4) << data[i][j] << " ║";
        }
        cout << "  " << setw(4) << dataRowSums[i] << " ║" << endl;
        if (i < SIZE - 1) {
            cout << "╠═════════╬═════════╬═════════╬═════════╬═════════╬═════════╬═════════╣" << endl;
        }
    }
    cout << "╠═════════╬═════════╬═════════╬═════════╬═════════╬═════════╬═════════╣" << endl;
    cout << "║  列 和  ║";
    for (int j = 0; j < SIZE; j++) {
        cout << "  " << setw(4) << dataColSums[j] << " ║";
    }
    cout << "  " << setw(4) << dataTotal << " ║" << endl;
    cout << "╚═════════╩═════════╩═════════╩═════════╩═════════╩═════════╩═════════╝" << endl;
    cout << endl;

    // 找出和最大的行
    int maxRowSum = dataRowSums[0];
    int maxRowIdx = 0;
    for (int i = 1; i < SIZE; i++) {
        if (dataRowSums[i] > maxRowSum) {
            maxRowSum = dataRowSums[i];
            maxRowIdx = i;
        }
    }
    cout << "行和最大：第" << maxRowIdx + 1 << "行（和 = " << maxRowSum << "）" << endl;

    // 找出和最小的列
    int minColSum = dataColSums[0];
    int minColIdx = 0;
    for (int j = 1; j < SIZE; j++) {
        if (dataColSums[j] < minColSum) {
            minColSum = dataColSums[j];
            minColIdx = j;
        }
    }
    cout << "列和最小：第" << minColIdx + 1 << "列（和 = " << minColSum << "）" << endl;
    cout << endl;

    // 成绩统计表示例
    cout << "--- 附加：成绩统计表 ---" << endl;
    string students[5] = {"小明", "小红", "小刚", "小丽", "小华"};
    int scores[5][3] = {
        {95, 87, 91},
        {78, 92, 85},
        {88, 76, 90},
        {92, 89, 94},
        {80, 85, 78}
    };
    string subjects[3] = {"语文", "数学", "英语"};

    cout << setw(6) << "姓名";
    for (int k = 0; k < 3; k++) {
        cout << setw(8) << subjects[k];
    }
    cout << setw(8) << "总分" << setw(8) << "平均分" << endl;
    cout << string(46, '-') << endl;

    for (int i = 0; i < 5; i++) {
        cout << setw(6) << students[i];
        int stuTotal = 0;
        for (int j = 0; j < 3; j++) {
            cout << setw(8) << scores[i][j];
            stuTotal += scores[i][j];
        }
        cout << setw(8) << stuTotal;
        cout << setw(8) << fixed << setprecision(1) << stuTotal / 3.0 << endl;
    }

    cout << string(46, '-') << endl;
    // 各科平均
    cout << setw(6) << "全班";
    for (int j = 0; j < 3; j++) {
        double subAvg = 0;
        for (int i = 0; i < 5; i++) {
            subAvg += scores[i][j];
        }
        subAvg /= 5.0;
        cout << setw(8) << fixed << setprecision(1) << subAvg;
    }
    cout << endl;
    cout << endl;

    // =====================================
    // 练习1 参考答案：对角线元素之和
    // =====================================
    cout << "========== 练习1答案：对角线元素之和 ==========" << endl;
    int mat[3][3] = {{2, 5, 8}, {3, 7, 1}, {6, 4, 9}};
    int diagSum = 0;
    for (int i = 0; i < 3; i++) {
        diagSum += mat[i][i];   // 对角线元素：行下标 == 列下标
    }
    cout << "矩阵：" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "  ";
        for (int j = 0; j < 3; j++) {
            cout << setw(3) << mat[i][j];
        }
        cout << endl;
    }
    cout << "主对角线元素：mat[0][0]=" << mat[0][0]
         << ", mat[1][1]=" << mat[1][1]
         << ", mat[2][2]=" << mat[2][2] << endl;
    cout << "对角线元素之和 = " << diagSum << " （" << mat[0][0]
         << " + " << mat[1][1] << " + " << mat[2][2] << " = " << diagSum << "）" << endl;
    cout << endl;

    // 附加：副对角线（从右上到左下）
    int antiDiagSum = 0;
    for (int i = 0; i < 3; i++) {
        antiDiagSum += mat[i][2 - i];   // 副对角线：行下标 + 列下标 = N - 1
    }
    cout << "副对角线元素：mat[0][2]=" << mat[0][2]
         << ", mat[1][1]=" << mat[1][1]
         << ", mat[2][0]=" << mat[2][0] << endl;
    cout << "副对角线元素之和 = " << antiDiagSum << endl;
    cout << endl;

    // =====================================
    // 练习2 参考答案（纠错）
    // =====================================
    cout << "========== 练习2答案：纠错小侦探 ==========" << endl;
    cout << "原代码错误分析：" << endl;
    cout << "  错误1: for (int i = 0; i <= 2; i++) → 应改为 i < 2" << endl;
    cout << "        data[2][3]只有2行(0~1)，i<=2会导致越界！" << endl;
    cout << "  错误2: int sum; → 应改为 int sum = 0;" << endl;
    cout << "        未初始化的局部变量值是不确定的！" << endl;
    cout << "  错误3: sum += data[j][i]; → 应改为 sum += data[i][j];" << endl;
    cout << "        数组名后面第一个下标是行，第二个是列！data[j][i]顺序反了！" << endl;
    cout << endl;

    // 正确版本
    cout << "--- 正确代码演示 ---" << endl;
    int data2[2][3] = {{1, 2, 3}, {4, 5, 6}};
    for (int i = 0; i < 2; i++) {
        int sum = 0;                       // ✅ 初始化
        for (int j = 0; j < 3; j++) {
            sum += data2[i][j];           // ✅ 正确的下标顺序：data[行][列]
        }
        cout << "第" << i + 1 << "行和：" << sum << endl;
    }
    cout << endl;

    // =====================================
    // 练习3 参考答案：我的成绩单
    // =====================================
    cout << "========== 练习3答案：我的成绩单 ==========" << endl;

    // 4门课，每门课3次测验成绩
    string courses[4] = {"编程", "数学", "物理", "英语"};
    int myScores[4][3] = {
        {92, 88, 95},    // 编程：3次测验
        {85, 90, 87},    // 数学
        {78, 82, 80},    // 物理
        {91, 89, 94}     // 英语
    };

    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║           我的成绩单                     ║" << endl;
    cout << "╠════════╦════════╦════════╦════════╦════════╣" << endl;
    cout << "║  科目  ║ 测验1  ║ 测验2  ║ 测验3  ║ 平均分 ║" << endl;
    cout << "╠════════╬════════╬════════╬════════╬════════╣" << endl;

    double bestAvg = 0;
    int bestIdx = 0;

    for (int i = 0; i < 4; i++) {
        cout << "║ " << setw(6) << courses[i] << " ║";
        int courseTotal = 0;
        for (int j = 0; j < 3; j++) {
            cout << "  " << setw(4) << myScores[i][j] << " ║";
            courseTotal += myScores[i][j];
        }
        double avg = courseTotal / 3.0;
        cout << "  " << setw(4) << fixed << setprecision(1) << avg << " ║" << endl;

        if (avg > bestAvg) {
            bestAvg = avg;
            bestIdx = i;
        }

        if (i < 3) {
            cout << "╠════════╬════════╬════════╬════════╬════════╣" << endl;
        }
    }
    cout << "╚════════╩════════╩════════╩════════╩════════╝" << endl;
    cout << endl;

    cout << "最高平均分的科目：" << courses[bestIdx]
         << "（平均分 = " << fixed << setprecision(1) << bestAvg << "）" << endl;
    cout << endl;

    // =====================================
    // 挑战任务参考答案：矩阵行列表完整版
    // =====================================
    cout << "========== 挑战任务答案：矩阵行列表 ==========" << endl;

    int challengeMat[5][5] = {
        { 3,  7,  2,  9,  1},
        { 5,  4,  8,  3,  6},
        { 1,  9,  5,  2,  7},
        { 8,  3,  6,  4,  5},
        { 2,  5,  7,  8,  9}
    };

    const int N = 5;
    int chRowSums[N] = {0};
    int chColSums[N] = {0};
    int chTotal = 0;

    // 输出表头
    cout << "       列1  列2  列3  列4  列5  行和" << endl;
    cout << "     +-------------------------------+------+" << endl;

    for (int i = 0; i < N; i++) {
        cout << "行" << i + 1 << "   |";
        for (int j = 0; j < N; j++) {
            cout << setw(4) << challengeMat[i][j] << " ";
            chRowSums[i] += challengeMat[i][j];
            chColSums[j] += challengeMat[i][j];
        }
        chTotal += chRowSums[i];
        cout << " | " << setw(3) << chRowSums[i] << endl;
    }

    cout << "     +-------------------------------+------+" << endl;
    cout << "列和  |";
    for (int j = 0; j < N; j++) {
        cout << setw(4) << chColSums[j] << " ";
    }
    cout << " | " << setw(3) << chTotal << endl;
    cout << "     +-------------------------------+------+" << endl;
    cout << endl;

    // 找最大行和与最小列和
    int chMaxRowSum = chRowSums[0], chMaxRowIdx = 0;
    int chMinColSum = chColSums[0], chMinColIdx = 0;
    for (int k = 1; k < N; k++) {
        if (chRowSums[k] > chMaxRowSum) {
            chMaxRowSum = chRowSums[k];
            chMaxRowIdx = k;
        }
        if (chColSums[k] < chMinColSum) {
            chMinColSum = chColSums[k];
            chMinColIdx = k;
        }
    }
    cout << "行和最大：第" << chMaxRowIdx + 1 << "行（" << chMaxRowSum << "）" << endl;
    cout << "列和最小：第" << chMinColIdx + 1 << "列（" << chMinColSum << "）" << endl;
    cout << endl;

    // =====================================
    // 程序结束
    // =====================================
    cout << "========== 程序结束 ==========" << endl;
    cout << "恭喜！你已经掌握了二维数组的遍历与统计！" << endl;
    cout << "记住口诀：外行内列来遍历，行和列和都能算！" << endl;

    return 0;
}
