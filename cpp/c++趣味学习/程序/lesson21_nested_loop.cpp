/*
 * C++趣味学习 - 第21课：循环套循环——嵌套循环入门
 * 知识点：嵌套for、内外层关系、循环次数分析
 * 项目：打印数字正方形
 */

#include <iostream>
#include <iomanip>
using namespace std;

// ============ 示例1：打印数字正方形 ============
void example1_number_square() {
    cout << "════════════════════════════════" << endl;
    cout << "  示例1：🟦 数字正方形生成器" << endl;
    cout << "════════════════════════════════" << endl;

    int n;
    cout << "请输入正方形的边长：";
    cin >> n;

    cout << endl << "边长为 " << n << " 的数字正方形：" << endl;
    cout << "┌";
    for (int j = 1; j <= n * 2 - 1; j++) cout << "─";
    cout << "┐" << endl;

    for (int i = 1; i <= n; i++) {         // 外层：控制行
        cout << "│";
        for (int j = 1; j <= n; j++) {     // 内层：控制列
            cout << " " << j;              // 打印列号
        }
        cout << " │" << endl;              // 每行结束
    }

    cout << "└";
    for (int j = 1; j <= n * 2 - 1; j++) cout << "─";
    cout << "┘" << endl;

    cout << "🌟 总执行次数：" << n << " × " << n << " = " << n * n << " 次" << endl;
    cout << endl;
}

// ============ 示例2：打印坐标网格 ============
void example2_coordinate_grid() {
    cout << "════════════════════════════════" << endl;
    cout << "  示例2：📍 坐标网格系统" << endl;
    cout << "════════════════════════════════" << endl;

    int rows, cols;
    cout << "请输入行数：";
    cin >> rows;
    cout << "请输入列数：";
    cin >> cols;

    cout << endl << "坐标网格（" << rows << "行 × " << cols << "列）：" << endl;
    cout << "每个位置用(行号,列号)表示" << endl;
    cout << "-------------------------------------------" << endl;

    // 表头
    cout << "      ";
    for (int col = 1; col <= cols; col++) {
        cout << setw(8) << ("列" + to_string(col));
    }
    cout << endl;

    // 分隔线
    cout << "     ┌";
    for (int col = 1; col <= cols; col++) {
        cout << "────────";
    }
    cout << "┐" << endl;

    // 网格内容
    for (int row = 1; row <= rows; row++) {
        cout << "行" << setw(2) << row << " │";
        for (int col = 1; col <= cols; col++) {
            cout << " (" << setw(2) << row << "," << setw(2) << col << ") ";
        }
        cout << "│" << endl;
    }

    // 底部分隔线
    cout << "     └";
    for (int col = 1; col <= cols; col++) {
        cout << "────────";
    }
    cout << "┘" << endl;

    cout << "🌟 总坐标数：" << rows << " × " << cols << " = " << rows * cols << " 个" << endl;
    cout << endl;
}

// ============ 示例3：嵌套循环次数分析 ============
void example3_loop_analysis() {
    cout << "════════════════════════════════" << endl;
    cout << "  示例3：🔢 嵌套循环次数分析" << endl;
    cout << "════════════════════════════════" << endl;

    cout << "实验1：内层次数固定" << endl;
    cout << "for(i=1; i<=3; i++)            " << endl;
    cout << "    for(j=1; j<=4; j++)        " << endl;
    cout << "总次数 = 3 × 4 = 12 次" << endl;
    cout << endl;

    cout << "实验2：内层次数随外层变化" << endl;
    cout << "for(i=1; i<=5; i++)            " << endl;
    cout << "    for(j=1; j<=i; j++)        " << endl;
    cout << "总次数 = 1 + 2 + 3 + 4 + 5 = 15 次" << endl;
    cout << endl;

    // 可视化嵌套循环的执行过程
    cout << "------- 执行过程可视化 -------" << endl;
    for (int i = 1; i <= 3; i++) {
        cout << "外层 i=" << i << " 开始 → ";
        for (int j = 1; j <= 3; j++) {
            cout << "(内层 j=" << j << ") ";
        }
        cout << "→ 外层 i=" << i << " 结束" << endl;
    }
    cout << "------------------------------" << endl;
    cout << "👀 观察：外层每走1圈，内层完整走3圈！" << endl;
    cout << endl;
}

// ============ 练习答案 ============

// 练习1：打印星号矩形
void practice1_star_rectangle() {
    cout << "════════════════════════════════" << endl;
    cout << "  练习1答案：打印5×8星号矩形" << endl;
    cout << "════════════════════════════════" << endl;

    int rows = 5, cols = 8;

    cout << rows << "行 × " << cols << "列的星号矩形：" << endl;
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= cols; j++) {
            cout << "* ";
        }
        cout << endl;
    }
    cout << endl;
}

// 练习2：九九加法表
void practice2_addition_table() {
    cout << "════════════════════════════════" << endl;
    cout << "  练习2答案：九九加法表" << endl;
    cout << "════════════════════════════════" << endl;

    cout << "     ";
    for (int col = 1; col <= 9; col++) {
        cout << setw(5) << col;
    }
    cout << endl;
    cout << "    ┌─────────────────────────────────────────────┐" << endl;

    for (int i = 1; i <= 9; i++) {
        cout << setw(3) << i << " │";
        for (int j = 1; j <= 9; j++) {
            cout << setw(5) << (i + j);
        }
        cout << endl;
    }
    cout << endl;
}

// 练习3：两个骰子的所有组合
void practice3_dice_combinations() {
    cout << "════════════════════════════════" << endl;
    cout << "  练习3答案：骰子组合统计" << endl;
    cout << "════════════════════════════════" << endl;

    int count = 0;

    cout << "两个骰子（1-6）的所有组合：" << endl;
    cout << "-------------------------------------------" << endl;

    for (int dice1 = 1; dice1 <= 6; dice1++) {
        for (int dice2 = 1; dice2 <= 6; dice2++) {
            cout << "(" << dice1 << "," << dice2 << ")=" << dice1 + dice2 << "\t";
            count++;
            if (count % 6 == 0) cout << endl;
        }
    }

    cout << "-------------------------------------------" << endl;
    cout << "🌟 一共有 " << count << " 种组合（6×6=36）。" << endl;
    cout << "   和为7的组合最可能（6种），和为2或12的组合最少（各1种）。" << endl;
    cout << endl;
}

// ============ 挑战任务：数字螺旋方阵 ============
void challenge_spiral_square() {
    cout << "════════════════════════════════" << endl;
    cout << "  挑战任务：🌀 数字螺旋方阵（简化版）" << endl;
    cout << "════════════════════════════════" << endl;

    int n;
    cout << "请输入方阵边长（建议3-9）：";
    cin >> n;

    // 使用二维数组存储螺旋方阵
    // 这里简化处理：先生成行优先的方阵（按顺序填数）
    cout << endl << n << "×" << n << " 按顺序填充的方阵：" << endl;
    cout << "-------------------------------------------" << endl;

    int counter = 1;
    for (int i = 1; i <= n; i++) {
        cout << "  ";
        for (int j = 1; j <= n; j++) {
            cout << setw(4) << counter;
            counter++;
        }
        cout << endl;
    }

    cout << "-------------------------------------------" << endl;
    cout << "💡 要生成真正的螺旋方阵，需要用到数组的知识，" << endl;
    cout << "   我们会在后面的课程中学习哦！" << endl;
    cout << endl;

    // 加分：打印蛇形填充（奇数行正序、偶数行倒序）
    cout << "🌟 加分挑战：蛇形填充方阵" << endl;
    cout << "-------------------------------------------" << endl;
    counter = 1;
    for (int i = 1; i <= n; i++) {
        cout << "  ";
        if (i % 2 == 1) {
            // 奇数行：正序
            for (int j = 1; j <= n; j++) {
                cout << setw(4) << counter;
                counter++;
            }
        } else {
            // 偶数行：倒序
            int end = counter + n - 1;
            for (int j = end; j >= counter; j--) {
                cout << setw(4) << j;
            }
            counter = end + 1;
        }
        cout << endl;
    }
    cout << endl;
}

// ============ 主函数 ============
int main() {
    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║  第21课：循环套循环——嵌套循环入门     ║" << endl;
    cout << "║  知识点：嵌套for、内外层关系           ║" << endl;
    cout << "╚══════════════════════════════════════════╝" << endl;
    cout << endl;

    int choice;
    while (true) {
        cout << "请选择要运行的示例：" << endl;
        cout << "1. 数字正方形生成器" << endl;
        cout << "2. 坐标网格系统" << endl;
        cout << "3. 嵌套循环次数分析" << endl;
        cout << "4. 练习1：打印星号矩形" << endl;
        cout << "5. 练习2：九九加法表" << endl;
        cout << "6. 练习3：骰子组合统计" << endl;
        cout << "7. 🏆 挑战：数字方阵" << endl;
        cout << "0. 退出程序" << endl;
        cout << "请输入选择（0-7）：";
        cin >> choice;
        cout << endl;

        if (choice == 0) break;

        switch (choice) {
            case 1: example1_number_square(); break;
            case 2: example2_coordinate_grid(); break;
            case 3: example3_loop_analysis(); break;
            case 4: practice1_star_rectangle(); break;
            case 5: practice2_addition_table(); break;
            case 6: practice3_dice_combinations(); break;
            case 7: challenge_spiral_square(); break;
            default:
                cout << "无效选择，请重新输入！" << endl;
        }
    }

    cout << "感谢学习！我们下一课再见！👋" << endl;
    return 0;
}
