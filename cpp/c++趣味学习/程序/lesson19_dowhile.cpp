/*
 * C++趣味学习 - 第19课：先斩后奏——do-while循环
 * 知识点：do-while特点、循环选择
 * 项目：掷骰子直到6
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

// ============ 示例1：掷骰子直到6 ============
void example1_dice_game() {
    cout << "════════════════════════════════" << endl;
    cout << "  示例1：🎲 掷骰子直到6" << endl;
    cout << "════════════════════════════════" << endl;

    srand(time(0));
    int dice;
    int count = 0;

    cout << "开始掷骰子！掷到6点就停止！" << endl;
    cout << "------------------------------" << endl;

    do {
        dice = rand() % 6 + 1;  // 生成1-6的随机数
        count++;
        cout << "第" << count << "次：掷出了 " << dice << " 点";

        // 根据点数给出不同的表情
        switch (dice) {
            case 1: cout << " ⚀"; break;
            case 2: cout << " ⚁"; break;
            case 3: cout << " ⚂"; break;
            case 4: cout << " ⚃"; break;
            case 5: cout << " ⚄"; break;
            case 6: cout << " ⚅ 🎉"; break;
        }
        cout << endl;
    } while (dice != 6);

    cout << "------------------------------" << endl;
    cout << "🏆 一共掷了 " << count << " 次才掷出6点！" << endl;

    // 根据次数给出评价
    if (count == 1) {
        cout << "🌟 第一把就出6！你运气爆棚！" << endl;
    } else if (count <= 5) {
        cout << "👍 运气不错！" << endl;
    } else if (count <= 10) {
        cout << "😊 正常范围，还不错！" << endl;
    } else {
        cout << "😅 有点非酋体质...不过坚持就是胜利！" << endl;
    }
    cout << endl;
}

// ============ 示例2：密码验证系统 ============
void example2_password_check() {
    cout << "════════════════════════════════" << endl;
    cout << "  示例2：🔐 密码验证系统" << endl;
    cout << "════════════════════════════════" << endl;

    const string PASSWORD = "c++123";
    string input;
    int attempts = 0;
    const int MAX_ATTEMPTS = 3;

    cout << "系统已锁定，请输入密码（最多" << MAX_ATTEMPTS << "次机会）。" << endl;
    cout << "提示：密码是 'c++123'" << endl;
    cout << "------------------------------" << endl;

    do {
        cout << "第" << (attempts + 1) << "次输入 - 密码：";
        cin >> input;
        attempts++;

        if (input == PASSWORD) {
            cout << "✅ 密码正确！" << endl;
            cout << "🔓 系统已解锁，欢迎进入！" << endl;
            break;
        } else {
            cout << "❌ 密码错误！" << endl;
            if (attempts < MAX_ATTEMPTS) {
                cout << "   还剩 " << (MAX_ATTEMPTS - attempts) << " 次机会。" << endl;
            }
        }
        cout << endl;
    } while (attempts < MAX_ATTEMPTS);

    if (input != PASSWORD) {
        cout << "🔒 尝试次数用完，账户已锁定！请30分钟后再试。" << endl;
    }
    cout << endl;
}

// ============ 示例3：do-while vs while 对比演示 ============
void example3_compare_loops() {
    cout << "════════════════════════════════" << endl;
    cout << "  示例3：🆚 do-while vs while" << endl;
    cout << "════════════════════════════════" << endl;

    int x = 10;

    cout << "当前 x = " << x << "，条件为 x < 5" << endl;
    cout << "------------------------------" << endl;

    cout << "▶ while循环（条件一开始就不满足）：" << endl;
    cout << "   输出：";
    while (x < 5) {
        cout << x << " ";  // 这行不会被执行
    }
    cout << "（没有任何输出，因为条件为假）" << endl;
    cout << endl;

    cout << "▶ do-while循环（条件一开始就不满足）：" << endl;
    cout << "   输出：";
    do {
        cout << x << " ";  // 这行会被执行一次！
    } while (x < 5);
    cout << "（输出了一次 " << x << "，因为do-while先执行再判断）" << endl;
    cout << endl;

    cout << "📌 结论：while可能一次都不执行，do-while至少执行一次！" << endl;
    cout << endl;
}

// ============ 练习答案 ============

// 练习1：猜数字（至少猜一次）
void practice1_guess_number() {
    cout << "════════════════════════════════" << endl;
    cout << "  练习1答案：猜数字（do-while版）" << endl;
    cout << "════════════════════════════════" << endl;

    srand(time(0));
    int target = rand() % 10 + 1;
    int guess;

    cout << "我想了一个1-10之间的数字。" << endl;
    cout << "------------------------------" << endl;

    do {
        cout << "你猜是多少？";
        cin >> guess;

        if (guess > target) {
            cout << "📉 大了！再小一点～" << endl;
        } else if (guess < target) {
            cout << "📈 小了！再大一点～" << endl;
        }
    } while (guess != target);

    cout << "🎯 猜对了！答案就是 " << target << "！" << endl;
    cout << endl;
}

// 练习2：数字输入验证
void practice2_input_validation() {
    cout << "════════════════════════════════" << endl;
    cout << "  练习2答案：数字输入验证" << endl;
    cout << "════════════════════════════════" << endl;

    int num;

    do {
        cout << "请输入一个1-100之间的整数：";
        cin >> num;

        if (num < 1 || num > 100) {
            cout << "❌ 输入不合法！必须在1到100之间哦。" << endl;
        }
    } while (num < 1 || num > 100);

    cout << "✅ 你输入的数字是：" << num << "，合法！" << endl;
    cout << endl;
}

// 练习3：简易计算器
void practice3_simple_calculator() {
    cout << "════════════════════════════════" << endl;
    cout << "  练习3答案：简易计算器" << endl;
    cout << "════════════════════════════════" << endl;

    int choice;
    double a, b;

    do {
        cout << endl;
        cout << "┌──────── 简易计算器 ────────┐" << endl;
        cout << "│  1. 加法 (+)              │" << endl;
        cout << "│  2. 减法 (-)              │" << endl;
        cout << "│  3. 乘法 (×)              │" << endl;
        cout << "│  4. 除法 (÷)              │" << endl;
        cout << "│  5. 退出                  │" << endl;
        cout << "└───────────────────────────┘" << endl;
        cout << "请选择（1-5）：";
        cin >> choice;

        if (choice >= 1 && choice <= 4) {
            cout << "请输入第一个数：";
            cin >> a;
            cout << "请输入第二个数：";
            cin >> b;

            switch (choice) {
                case 1:
                    cout << a << " + " << b << " = " << (a + b) << endl;
                    break;
                case 2:
                    cout << a << " - " << b << " = " << (a - b) << endl;
                    break;
                case 3:
                    cout << a << " × " << b << " = " << (a * b) << endl;
                    break;
                case 4:
                    if (b != 0) {
                        cout << a << " ÷ " << b << " = " << (a / b) << endl;
                    } else {
                        cout << "❌ 除数不能为0！" << endl;
                    }
                    break;
            }
        } else if (choice != 5) {
            cout << "❌ 无效选项！" << endl;
        }
    } while (choice != 5);

    cout << "👋 感谢使用，再见！" << endl;
    cout << endl;
}

// ============ 挑战任务：多功能运算器 ============
void challenge_multi_calculator() {
    cout << "════════════════════════════════" << endl;
    cout << "  挑战任务：🔢 多功能运算器" << endl;
    cout << "════════════════════════════════" << endl;

    int choice;
    double num1, num2, result;

    do {
        cout << endl;
        cout << "╔══════════ 多功能运算器 ══════════╗" << endl;
        cout << "║  1. 加法运算    2. 减法运算    ║" << endl;
        cout << "║  3. 乘法运算    4. 除法运算    ║" << endl;
        cout << "║  5. 求平方      6. 求立方      ║" << endl;
        cout << "║  7. 退出程序                    ║" << endl;
        cout << "╚═════════════════════════════════╝" << endl;
        cout << "请输入你的选择（1-7）：";
        cin >> choice;

        cout << "─────────────────────────────────" << endl;

        switch (choice) {
            case 1:  // 加法
                cout << "【加法运算】" << endl;
                cout << "请输入第一个加数："; cin >> num1;
                cout << "请输入第二个加数："; cin >> num2;
                cout << num1 << " + " << num2 << " = " << (num1 + num2) << endl;
                break;

            case 2:  // 减法
                cout << "【减法运算】" << endl;
                cout << "请输入被减数："; cin >> num1;
                cout << "请输入减数："; cin >> num2;
                cout << num1 << " - " << num2 << " = " << (num1 - num2) << endl;
                break;

            case 3:  // 乘法
                cout << "【乘法运算】" << endl;
                cout << "请输入第一个因数："; cin >> num1;
                cout << "请输入第二个因数："; cin >> num2;
                cout << num1 << " × " << num2 << " = " << (num1 * num2) << endl;
                break;

            case 4:  // 除法
                cout << "【除法运算】" << endl;
                cout << "请输入被除数："; cin >> num1;
                cout << "请输入除数："; cin >> num2;
                if (num2 != 0) {
                    cout << num1 << " ÷ " << num2 << " = " << (num1 / num2) << endl;
                } else {
                    cout << "❌ 错误：除数不能为0！" << endl;
                }
                break;

            case 5:  // 求平方
                cout << "【求平方】" << endl;
                cout << "请输入一个数："; cin >> num1;
                cout << num1 << " 的平方 = " << (num1 * num1) << endl;
                break;

            case 6:  // 求立方
                cout << "【求立方】" << endl;
                cout << "请输入一个数："; cin >> num1;
                cout << num1 << " 的立方 = " << (num1 * num1 * num1) << endl;
                break;

            case 7:  // 退出
                cout << "感谢使用多功能运算器！再见！👋" << endl;
                break;

            default:
                cout << "❌ 无效选项，请选择1-7之间的数字！" << endl;
        }
        cout << "─────────────────────────────────" << endl;

    } while (choice != 7);

    cout << endl;
}

// ============ 主函数 ============
int main() {
    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║  第19课：先斩后奏——do-while循环        ║" << endl;
    cout << "║  知识点：do-while特点、循环选择         ║" << endl;
    cout << "╚══════════════════════════════════════════╝" << endl;
    cout << endl;

    int choice;
    do {
        cout << "请选择要运行的示例：" << endl;
        cout << "1. 掷骰子直到6" << endl;
        cout << "2. 密码验证系统" << endl;
        cout << "3. do-while vs while 对比" << endl;
        cout << "4. 练习1：猜数字（do-while版）" << endl;
        cout << "5. 练习2：数字输入验证" << endl;
        cout << "6. 练习3：简易计算器" << endl;
        cout << "7. 🏆 挑战：多功能运算器" << endl;
        cout << "0. 退出程序" << endl;
        cout << "请输入选择（0-7）：";
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1: example1_dice_game(); break;
            case 2: example2_password_check(); break;
            case 3: example3_compare_loops(); break;
            case 4: practice1_guess_number(); break;
            case 5: practice2_input_validation(); break;
            case 6: practice3_simple_calculator(); break;
            case 7: challenge_multi_calculator(); break;
            case 0: break;
            default:
                cout << "无效选择，请重新输入！" << endl;
        }
    } while (choice != 0);

    cout << "感谢学习！我们下一课再见！👋" << endl;
    return 0;
}
