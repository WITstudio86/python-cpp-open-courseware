/*
 * C++趣味学习 - 第22课：图形魔法师——打印三角形
 * 知识点：星号三角形、数字三角形、空格与星号关系
 * 项目：绘制三角形图案
 */

#include <iostream>
using namespace std;

// ============ 示例1：各种直角三角形 ============
void example1_right_triangles() {
    cout << "════════════════════════════════" << endl;
    cout << "  示例1：🔺 直角三角形家族" << endl;
    cout << "════════════════════════════════" << endl;

    int n;
    cout << "请输入行数：";
    cin >> n;
    cout << endl;

    // 1. 左下角直角三角形
    cout << "【左下角直角三角形】" << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            cout << "* ";
        }
        cout << endl;
    }
    cout << endl;

    // 2. 左上角倒直角三角形
    cout << "【左上角倒直角三角形】" << endl;
    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= i; j++) {
            cout << "* ";
        }
        cout << endl;
    }
    cout << endl;

    // 3. 右下角直角三角形
    cout << "【右下角直角三角形】" << endl;
    for (int i = 1; i <= n; i++) {
        // 空格
        for (int j = 1; j <= n - i; j++) {
            cout << "  ";
        }
        // 星号
        for (int j = 1; j <= i; j++) {
            cout << "* ";
        }
        cout << endl;
    }
    cout << endl;

    // 4. 右上角倒直角三角形
    cout << "【右上角倒直角三角形】" << endl;
    for (int i = n; i >= 1; i--) {
        // 空格
        for (int j = 1; j <= n - i; j++) {
            cout << "  ";
        }
        // 星号
        for (int j = 1; j <= i; j++) {
            cout << "* ";
        }
        cout << endl;
    }
    cout << endl;
}

// ============ 示例2：等腰三角形（正三角形） ============
void example2_isosceles_triangle() {
    cout << "════════════════════════════════" << endl;
    cout << "  示例2：🔺 等腰三角形（金字塔）" << endl;
    cout << "════════════════════════════════" << endl;

    int n;
    cout << "请输入金字塔层数：";
    cin >> n;
    cout << endl;

    cout << "🌟 " << n << "层金字塔：" << endl << endl;

    for (int i = 1; i <= n; i++) {
        // 打印空格：n-i个
        for (int j = 1; j <= n - i; j++) {
            cout << " ";
        }
        // 打印星号：2i-1个
        for (int j = 1; j <= 2 * i - 1; j++) {
            cout << "*";
        }
        cout << endl;
    }

    cout << endl;
    cout << "📐 公式：第" << n << "层，空格=" << n << "-i，星号=2i-1" << endl;
    cout << "   第1行：" << n-1 << "个空格，" << (2*1-1) << "个星号" << endl;
    cout << "   第2行：" << n-2 << "个空格，" << (2*2-1) << "个星号" << endl;
    cout << "   第" << n << "行：0个空格，" << (2*n-1) << "个星号" << endl;
    cout << endl;
}

// ============ 示例3：数字三角形 ============
void example3_number_triangle() {
    cout << "════════════════════════════════" << endl;
    cout << "  示例3：🔢 数字三角形" << endl;
    cout << "════════════════════════════════" << endl;

    int n;
    cout << "请输入行数：";
    cin >> n;
    cout << endl;

    // 数字递增三角形
    cout << "【数字递增三角形】" << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            cout << j << " ";
        }
        cout << endl;
    }
    cout << endl;

    // 数字金字塔（回文）
    cout << "【数字金字塔（回文）】" << endl;
    for (int i = 1; i <= n; i++) {
        // 空格
        for (int j = 1; j <= n - i; j++) {
            cout << "  ";
        }
        // 递增部分
        for (int j = 1; j <= i; j++) {
            cout << j << " ";
        }
        // 递减部分
        for (int j = i - 1; j >= 1; j--) {
            cout << j << " ";
        }
        cout << endl;
    }
    cout << endl;

    // 弗洛伊德三角形
    cout << "【弗洛伊德三角形】" << endl;
    int num = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            cout << num << "\t";
            num++;
        }
        cout << endl;
    }
    cout << endl;
}

// ============ 练习答案 ============

// 练习1：右下角倒直角三角形
void practice1_inverted_right_triangle() {
    cout << "════════════════════════════════" << endl;
    cout << "  练习1答案：右下角倒直角三角形" << endl;
    cout << "════════════════════════════════" << endl;

    int n = 5;
    cout << n << "行右下角倒直角三角形：" << endl;

    for (int i = n; i >= 1; i--) {
        // 空格：n-i个
        for (int j = 1; j <= n - i; j++) {
            cout << "  ";
        }
        // 星号：i个
        for (int j = 1; j <= i; j++) {
            cout << "* ";
        }
        cout << endl;
    }
    cout << endl;
}

// 练习2：字母三角形
void practice2_alphabet_triangle() {
    cout << "════════════════════════════════" << endl;
    cout << "  练习2答案：字母三角形" << endl;
    cout << "════════════════════════════════" << endl;

    int n = 5;
    cout << n << "行字母三角形：" << endl;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            cout << char('A' + j) << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// 练习3：空心等腰三角形
void practice3_hollow_triangle() {
    cout << "════════════════════════════════" << endl;
    cout << "  练习3答案：空心等腰三角形" << endl;
    cout << "════════════════════════════════" << endl;

    int n = 5;
    cout << n << "层空心等腰三角形：" << endl;

    for (int i = 1; i <= n; i++) {
        // 打印空格
        for (int j = 1; j <= n - i; j++) {
            cout << " ";
        }
        // 打印星号或空格
        for (int j = 1; j <= 2 * i - 1; j++) {
            // 每行的第一个、最后一个字符，或者最后一行全部打印
            if (j == 1 || j == 2 * i - 1 || i == n) {
                cout << "*";
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

// ============ 挑战任务：弗洛伊德三角形（8行） ============
void challenge_floyd_triangle() {
    cout << "════════════════════════════════" << endl;
    cout << "  挑战任务：🔢 弗洛伊德三角形（8行）" << endl;
    cout << "════════════════════════════════" << endl;

    int n = 8;
    int num = 1;

    cout << "弗洛伊德三角形（" << n << "行）：" << endl;
    cout << "-------------------------------------------" << endl;

    for (int i = 1; i <= n; i++) {
        cout << "第" << i << "行：";
        for (int j = 1; j <= i; j++) {
            cout << num;
            if (j < i) cout << ", ";
            num++;
        }
        cout << endl;
    }

    cout << "-------------------------------------------" << endl;
    cout << "📐 弗洛伊德三角形的第" << n << "行最后一个数是：" << num - 1 << endl;
    cout << "   总共填充了 " << n * (n + 1) / 2 << " 个连续自然数。" << endl;
    cout << endl;
}

// ============ 主函数 ============
int main() {
    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║  第22课：图形魔法师——打印三角形       ║" << endl;
    cout << "║  知识点：星号三角形、数字三角形         ║" << endl;
    cout << "╚══════════════════════════════════════════╝" << endl;
    cout << endl;

    int choice;
    while (true) {
        cout << "请选择要运行的示例：" << endl;
        cout << "1. 直角三角形家族（四种）" << endl;
        cout << "2. 等腰三角形（金字塔）" << endl;
        cout << "3. 数字三角形（三种）" << endl;
        cout << "4. 练习1：右下角倒直角三角形" << endl;
        cout << "5. 练习2：字母三角形" << endl;
        cout << "6. 练习3：空心等腰三角形" << endl;
        cout << "7. 🏆 挑战：弗洛伊德三角形（8行）" << endl;
        cout << "0. 退出程序" << endl;
        cout << "请输入选择（0-7）：";
        cin >> choice;
        cout << endl;

        if (choice == 0) break;

        switch (choice) {
            case 1: example1_right_triangles(); break;
            case 2: example2_isosceles_triangle(); break;
            case 3: example3_number_triangle(); break;
            case 4: practice1_inverted_right_triangle(); break;
            case 5: practice2_alphabet_triangle(); break;
            case 6: practice3_hollow_triangle(); break;
            case 7: challenge_floyd_triangle(); break;
            default:
                cout << "无效选择，请重新输入！" << endl;
        }
    }

    cout << "感谢学习！我们下一课再见！👋" << endl;
    return 0;
}
