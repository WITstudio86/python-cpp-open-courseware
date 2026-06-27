/*
 * C++趣味学习 - 第23课：对称之美——打印菱形与沙漏
 * 知识点：复杂图形、对称算法
 * 项目：闪闪钻石图案
 */

#include <iostream>
using namespace std;

// ============ 示例1：闪闪钻石（菱形） ============
void example1_diamond() {
    cout << "════════════════════════════════" << endl;
    cout << "  示例1：💎 闪闪钻石（菱形）" << endl;
    cout << "════════════════════════════════" << endl;

    int n;
    cout << "请输入钻石的一半高度：";
    cin >> n;
    cout << endl;

    cout << "🌟 " << (2 * n - 1) << "行的钻石图案：" << endl << endl;

    // 上半部分：正三角形（第1行到第n行）
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

    // 下半部分：倒三角形（第n-1行到第1行）
    for (int i = n - 1; i >= 1; i--) {
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
    cout << "💡 分析：菱形 = 正三角形（1→" << n << "行） + 倒三角形（" << (n-1) << "→1行）" << endl;
    cout << "   上半每行：空格=" << n << "-i，星号=2i-1" << endl;
    cout << "   下半每行：空格=" << n << "-i，星号=2i-1（公式相同，i递减）" << endl;
    cout << endl;
}

// ============ 示例2：时光沙漏 ============
void example2_hourglass() {
    cout << "════════════════════════════════" << endl;
    cout << "  示例2：⏳ 时光沙漏" << endl;
    cout << "════════════════════════════════" << endl;

    int n;
    cout << "请输入沙漏的一半高度：";
    cin >> n;
    cout << endl;

    cout << "⏳ " << (2 * n - 1) << "行的沙漏图案：" << endl << endl;

    // 上半部分：倒三角形（第n行到第1行）
    for (int i = n; i >= 1; i--) {
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

    // 下半部分：正三角形（第2行到第n行）
    for (int i = 2; i <= n; i++) {
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
    cout << "💡 分析：沙漏 = 倒三角形（" << n << "→1行） + 正三角形（2→" << n << "行）" << endl;
    cout << "   沙漏和菱形的公式完全一样，只是循环方向相反！" << endl;
    cout << endl;
}

// ============ 示例3：空心菱形 ============
void example3_hollow_diamond() {
    cout << "════════════════════════════════" << endl;
    cout << "  示例3：💠 空心钻石" << endl;
    cout << "════════════════════════════════" << endl;

    int n;
    cout << "请输入钻石的一半高度：";
    cin >> n;
    cout << endl;

    cout << "💠 " << (2 * n - 1) << "行的空心钻石：" << endl << endl;

    // 上半部分
    for (int i = 1; i <= n; i++) {
        // 打印左边的空格
        for (int j = 1; j <= n - i; j++) {
            cout << " ";
        }
        // 打印星号和内部空格
        for (int j = 1; j <= 2 * i - 1; j++) {
            // 每行的第一个或最后一个位置打印星号
            if (j == 1 || j == 2 * i - 1) {
                cout << "*";
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }

    // 下半部分
    for (int i = n - 1; i >= 1; i--) {
        // 打印左边的空格
        for (int j = 1; j <= n - i; j++) {
            cout << " ";
        }
        // 打印星号和内部空格
        for (int j = 1; j <= 2 * i - 1; j++) {
            if (j == 1 || j == 2 * i - 1) {
                cout << "*";
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }

    cout << endl;
    cout << "💡 技巧：空心 = 每行只打印两端星号，中间用空格填充" << endl;
    cout << "   条件：j==1（左端）或 j==2i-1（右端）时打星号" << endl;
    cout << endl;
}

// ============ 练习答案 ============

// 练习1：蝴蝶翅膀
void practice1_butterfly() {
    cout << "════════════════════════════════" << endl;
    cout << "  练习1答案：🦋 蝴蝶翅膀" << endl;
    cout << "════════════════════════════════" << endl;

    int n = 5;
    cout << n << "行蝴蝶翅膀图案：" << endl << endl;

    for (int i = 1; i <= n; i++) {
        // 左翅膀
        for (int j = 1; j <= i; j++) {
            cout << "*";
        }
        // 中间空格
        for (int j = 1; j <= 2 * (n - i); j++) {
            cout << " ";
        }
        // 右翅膀
        for (int j = 1; j <= i; j++) {
            cout << "*";
        }
        cout << endl;
    }

    cout << endl;
}

// 练习2：数字菱形
void practice2_number_diamond() {
    cout << "════════════════════════════════" << endl;
    cout << "  练习2答案：🔢 数字菱形" << endl;
    cout << "════════════════════════════════" << endl;

    int n = 4;
    cout << n << "层数字菱形：" << endl << endl;

    // 上半部分
    for (int i = 1; i <= n; i++) {
        // 空格
        for (int j = 1; j <= n - i; j++) {
            cout << "  ";
        }
        // 递增数字
        for (int j = 1; j <= i; j++) {
            cout << j << " ";
        }
        // 递减数字
        for (int j = i - 1; j >= 1; j--) {
            cout << j << " ";
        }
        cout << endl;
    }

    // 下半部分
    for (int i = n - 1; i >= 1; i--) {
        // 空格
        for (int j = 1; j <= n - i; j++) {
            cout << "  ";
        }
        // 递增数字
        for (int j = 1; j <= i; j++) {
            cout << j << " ";
        }
        // 递减数字
        for (int j = i - 1; j >= 1; j--) {
            cout << j << " ";
        }
        cout << endl;
    }

    cout << endl;
}

// 练习3：自定义字符菱形
void practice3_custom_char_diamond() {
    cout << "════════════════════════════════" << endl;
    cout << "  练习3答案：自定义字符菱形" << endl;
    cout << "════════════════════════════════" << endl;

    int n;
    char ch;
    cout << "请输入菱形一半高度：";
    cin >> n;
    cout << "请输入填充字符：";
    cin >> ch;
    cout << endl;

    cout << "用 '" << ch << "' 绘制的菱形：" << endl << endl;

    // 上半
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n - i; j++) cout << " ";
        for (int j = 1; j <= 2 * i - 1; j++) cout << ch;
        cout << endl;
    }
    // 下半
    for (int i = n - 1; i >= 1; i--) {
        for (int j = 1; j <= n - i; j++) cout << " ";
        for (int j = 1; j <= 2 * i - 1; j++) cout << ch;
        cout << endl;
    }

    cout << endl;
}

// ============ 挑战任务：空心菱形 ============
void challenge_hollow_diamond_detailed() {
    cout << "════════════════════════════════" << endl;
    cout << "  挑战任务：💠 空心菱形（详解版）" << endl;
    cout << "════════════════════════════════" << endl;

    int n;
    cout << "请输入空心菱形的一半高度：";
    cin >> n;
    cout << endl;

    cout << "💠 " << (2 * n - 1) << "行的空心菱形：" << endl << endl;

    // 上半
    for (int i = 1; i <= n; i++) {
        // 打印左边空格
        for (int j = 1; j <= n - i; j++) {
            cout << " ";
        }

        // 打印星号与内部空格
        // 左星号在位置1，右星号在位置2i-1
        cout << "*";  // 左边星号
        for (int j = 1; j <= 2 * i - 3; j++) {
            cout << " ";  // 内部空格
        }
        if (i > 1) cout << "*";  // 右边星号（第一行只有一个星号）

        cout << endl;
    }

    // 下半
    for (int i = n - 1; i >= 1; i--) {
        // 打印左边空格
        for (int j = 1; j <= n - i; j++) {
            cout << " ";
        }

        // 打印星号与内部空格
        cout << "*";  // 左边星号
        for (int j = 1; j <= 2 * i - 3; j++) {
            cout << " ";  // 内部空格
        }
        if (i > 1) cout << "*";  // 右边星号

        cout << endl;
    }

    cout << endl;
    cout << "📐 空心菱形分析：" << endl;
    cout << "   上半第i行：" << endl;
    cout << "     - 左空格：" << (n - i) << "个" << endl;
    cout << "     - 左星号位置：1" << endl;
    cout << "     - 内部空格：" << (2 * i - 3) << "个（i=1时为-1，不打印）" << endl;
    cout << "     - 右星号位置：2i-1" << endl;
    cout << endl;

    // 加分：添加颜色提示（纯文本）
    cout << "🌟 试试看我上半和下半的代码结构！" << endl;
    cout << "   上半i从1→" << n << "，内部空格从0→" << (2*n-3) << endl;
    cout << "   下半i从" << (n-1) << "→1，内部空格从" << (2*(n-1)-3) << "→0" << endl;
    cout << endl;
}

// ============ 主函数 ============
int main() {
    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║  第23课：对称之美——打印菱形与沙漏     ║" << endl;
    cout << "║  知识点：复杂图形、对称算法             ║" << endl;
    cout << "╚══════════════════════════════════════════╝" << endl;
    cout << endl;

    int choice;
    while (true) {
        cout << "请选择要运行的示例：" << endl;
        cout << "1. 闪闪钻石（菱形）" << endl;
        cout << "2. 时光沙漏" << endl;
        cout << "3. 空心钻石" << endl;
        cout << "4. 练习1：蝴蝶翅膀" << endl;
        cout << "5. 练习2：数字菱形" << endl;
        cout << "6. 练习3：自定义字符菱形" << endl;
        cout << "7. 🏆 挑战：空心菱形（详解版）" << endl;
        cout << "0. 退出程序" << endl;
        cout << "请输入选择（0-7）：";
        cin >> choice;
        cout << endl;

        if (choice == 0) break;

        switch (choice) {
            case 1: example1_diamond(); break;
            case 2: example2_hourglass(); break;
            case 3: example3_hollow_diamond(); break;
            case 4: practice1_butterfly(); break;
            case 5: practice2_number_diamond(); break;
            case 6: practice3_custom_char_diamond(); break;
            case 7: challenge_hollow_diamond_detailed(); break;
            default:
                cout << "无效选择，请重新输入！" << endl;
        }
    }

    cout << "感谢学习！我们下一课再见！👋" << endl;
    return 0;
}
