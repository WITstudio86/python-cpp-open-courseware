/*
 * C++趣味学习 - 第17课：转圈的机器人——while循环
 * 知识点：while语法、循环条件、死循环
 * 项目：数字倒计时器
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// ============ 示例1：数字倒计时器 ============
void example1_countdown() {
    cout << "════════════════════════════════" << endl;
    cout << "  示例1：🚀 火箭发射倒计时器" << endl;
    cout << "════════════════════════════════" << endl;

    int countdown = 10;

    cout << "火箭发射倒计时开始！" << endl;
    cout << "------------------------------" << endl;

    while (countdown > 0) {
        cout << "T-" << countdown << " 秒..." << endl;
        countdown--;  // 每次减1，这是关键！没有这行就会死循环
    }

    cout << "🔥 发射！火箭升空！🚀" << endl;
    cout << endl;
}

// ============ 示例2：猜数字游戏 ============
void example2_guessing_game() {
    cout << "════════════════════════════════" << endl;
    cout << "  示例2：🎯 猜数字游戏" << endl;
    cout << "════════════════════════════════" << endl;

    srand(time(0));
    int secret = rand() % 100 + 1;  // 生成1-100的随机数
    int guess = 0;
    int tries = 0;

    cout << "我想了一个1到100之间的数字，来猜猜看！" << endl;
    cout << "------------------------------" << endl;

    while (guess != secret) {
        cout << "请输入你猜的数字：";
        cin >> guess;
        tries++;

        if (guess > secret) {
            cout << "⬇️ 太大了！往下猜猜～" << endl;
        } else if (guess < secret) {
            cout << "⬆️ 太小了！往上猜猜～" << endl;
        }
    }

    cout << "🎉 恭喜你猜对了！数字就是 " << secret << "！" << endl;
    cout << "你一共猜了 " << tries << " 次。" << endl;

    if (tries <= 5) {
        cout << "🏆 太厉害了！你是猜数字高手！" << endl;
    } else if (tries <= 10) {
        cout << "👍 不错！继续加油！" << endl;
    } else {
        cout << "😅 下次可以试着用二分法更快找到哦！" << endl;
    }
    cout << endl;
}

// ============ 新增：do-while与while对比演示 ============
void example_while_vs_dowhile() {
    cout << "════════════════════════════════" << endl;
    cout << "  对比演示：while vs do-while" << endl;
    cout << "════════════════════════════════" << endl;

    int a = 1, b = 1;

    cout << "【情况1：条件一直成立（1<=3）】" << endl;
    cout << "while循环：";
    a = 1;
    while (a <= 3) {
        cout << a << " ";
        a++;
    }
    cout << endl;

    cout << "do-while循环：";
    b = 1;
    do {
        cout << b << " ";
        b++;
    } while (b <= 3);
    cout << endl;
    cout << "结论：条件成立时，两者行为完全一样" << endl;
    cout << endl;

    cout << "【情况2：条件一开始就不成立（10<=3）】" << endl;
    cout << "while循环：";
    a = 10;
    while (a <= 3) {
        cout << a << " ";  // 一次都不执行
        a++;
    }
    cout << "（什么都不输出——一次都没执行！）" << endl;

    cout << "do-while循环：";
    b = 10;
    do {
        cout << b << " ";  // 至少执行一次！
        b++;
    } while (b <= 3);
    cout << "（执行了一次！）" << endl;
    cout << endl;

    cout << "📖 关键区别：" << endl;
    cout << "  while   → 先判断，再执行（可能一次都不执行）" << endl;
    cout << "  do-while → 先执行，再判断（至少执行一次）" << endl;
    cout << endl;
}

// ============ 示例3：求1到N的和（while版本） ============
void example3_sum() {
    cout << "════════════════════════════════" << endl;
    cout << "  示例3：➕ while循环求和" << endl;
    cout << "════════════════════════════════" << endl;

    int n;
    cout << "请输入一个正整数n，计算1+2+...+n的和：";
    cin >> n;

    int i = 1;
    int sum = 0;

    while (i <= n) {
        sum += i;  // 等价于 sum = sum + i
        i++;
    }

    cout << "1到" << n << "的和是：" << sum << endl;

    // 验证：用公式 n*(n+1)/2
    cout << "验证（公式法）：" << n << "×(" << n << "+1)÷2 = " << n * (n + 1) / 2 << endl;
    cout << endl;
}

// ============ 新增示例：while计数器——统计数字位数 ============
void example_counter_digits() {
    cout << "════════════════════════════════" << endl;
    cout << "  示例：while计数器——统计数字位数" << endl;
    cout << "════════════════════════════════" << endl;

    int number;
    cout << "请输入一个正整数：";
    cin >> number;

    int count = 0;       // 计数器，初始为0
    int temp = number;   // 保存原始数字的副本

    // 每次循环去掉最后一位，计数器加1
    while (temp > 0) {
        temp = temp / 10;  // 去掉最后一位
        count++;           // 计数器加1
    }

    cout << number << " 是一个 " << count << " 位数。" << endl;

    if (count == 1) {
        cout << "个位数！简单明了~" << endl;
    } else if (count <= 4) {
        cout << count << "位数，很不错！" << endl;
    } else {
        cout << "哇，" << count << "位数！这是一个很大的数字呢！" << endl;
    }
    cout << endl;
}

// ============ 新增示例：while累加器——计算平均分 ============
void example_accumulator_average() {
    cout << "════════════════════════════════" << endl;
    cout << "  示例：while累加器——班级平均分" << endl;
    cout << "════════════════════════════════" << endl;

    int n;
    cout << "请输入班级人数：";
    cin >> n;

    int i = 1;          // 循环变量：当前是第几个同学
    double score;       // 每个同学的成绩
    double sum = 0;     // 累加器：总分，初始为0

    while (i <= n) {
        cout << "请输入第" << i << "位同学的成绩：";
        cin >> score;

        // 输入验证：成绩必须在0-100之间
        if (score < 0 || score > 100) {
            cout << "⚠️ 成绩不合法（0-100），请重新输入！" << endl;
            continue;  // 不累加也不增加i，直接回到循环开头
        }

        sum = sum + score;  // 累加到总分
        i++;                // 移到下一位同学
    }

    double average = sum / n;
    cout << "\n—— 统计结果 ——" << endl;
    cout << "班级人数：" << n << " 人" << endl;
    cout << "总分：" << sum << " 分" << endl;
    cout << "平均分：" << average << " 分" << endl;

    if (average >= 90) {
        cout << "🏆 太棒了！这个班是学霸班！" << endl;
    } else if (average >= 70) {
        cout << "👍 不错，继续加油！" << endl;
    } else {
        cout << "💪 需要更加努力哦！" << endl;
    }
    cout << endl;
}

// ============ 新增示例：while输入验证——密码登录系统 ============
void example_input_validation() {
    cout << "════════════════════════════════" << endl;
    cout << "  示例：while输入验证——密码登录" << endl;
    cout << "════════════════════════════════" << endl;

    const int CORRECT_PASSWORD = 2024;
    int password;
    int attempts = 0;          // 尝试次数
    const int MAX_ATTEMPTS = 3; // 最大允许次数

    cout << "你最多有 " << MAX_ATTEMPTS << " 次尝试机会" << endl;

    while (attempts < MAX_ATTEMPTS) {
        cout << "\n请输入密码：";
        cin >> password;
        attempts++;

        if (password == CORRECT_PASSWORD) {
            cout << "✅ 密码正确！欢迎进入系统！" << endl;
            cout << "你用了 " << attempts << " 次尝试。" << endl;
            return;  // 登录成功，结束函数
        } else {
            cout << "❌ 密码错误！" << endl;
            int remaining = MAX_ATTEMPTS - attempts;
            if (remaining > 0) {
                cout << "你还剩 " << remaining << " 次机会。" << endl;
                cout << "提示：密码是一个年份~" << endl;
            }
        }
    }

    // 循环结束 = 尝试次数用完了
    cout << "\n🚫 尝试次数已用完！账户已锁定。" << endl;
    cout << endl;
}

// ============ 练习答案 ============

// 练习1：打印1到20
void practice1_print_1_to_20() {
    cout << "════════════════════════════════" << endl;
    cout << "  练习1答案：打印1到20" << endl;
    cout << "════════════════════════════════" << endl;

    int i = 1;
    while (i <= 20) {
        cout << i << " ";
        i++;
    }
    cout << endl << endl;
}

// 练习2：计算1到100的和
void practice2_sum_1_to_100() {
    cout << "════════════════════════════════" << endl;
    cout << "  练习2答案：1到100的和" << endl;
    cout << "════════════════════════════════" << endl;

    int i = 1, sum = 0;
    while (i <= 100) {
        sum += i;
        i++;
    }
    cout << "1到100的和是：" << sum << "（应该是5050）" << endl << endl;
}

// 练习3：新年倒计时
void practice3_newyear_countdown() {
    cout << "════════════════════════════════" << endl;
    cout << "  练习3答案：新年倒计时" << endl;
    cout << "════════════════════════════════" << endl;

    int n;
    cout << "请输入倒计时起始数字：";
    cin >> n;

    while (n >= 1) {
        cout << n << "！" << endl;
        n--;
        // 模拟倒计时的停顿感（实际运行中看不太出来，但概念上要有）
    }
    cout << "🎆 新年快乐！Happy New Year！🎆" << endl;
    cout << endl;
}

// ============ 练习4：求1到100所有奇数的和 ============
void practice4_odd_sum() {
    cout << "════════════════════════════════" << endl;
    cout << "  练习4：1到100奇数的和" << endl;
    cout << "════════════════════════════════" << endl;

    int i = 1, sum = 0;
    while (i <= 100) {
        if (i % 2 == 1) {  // 判断i是否为奇数
            sum += i;
        }
        i++;
    }
    cout << "1到100所有奇数的和是：" << sum << "（应该是2500）" << endl;
    cout << endl;
}

// ============ 练习5：乘法表查询器 ============
void practice5_multiplication_table() {
    cout << "════════════════════════════════" << endl;
    cout << "  练习5：乘法表查询器" << endl;
    cout << "════════════════════════════════" << endl;

    int n;
    cout << "请输入1-9之间的整数，查看它的乘法表：";
    cin >> n;

    if (n >= 1 && n <= 9) {
        int i = 1;
        cout << "—— " << n << " 的乘法表 ——" << endl;
        while (i <= 9) {
            cout << n << " × " << i << " = " << n * i << endl;
            i++;
        }
    } else {
        cout << "请输入1-9之间的整数哦！" << endl;
    }
    cout << endl;
}

// ============ 挑战任务：ATM取款机模拟 ============
void challenge_atm() {
    cout << "════════════════════════════════" << endl;
    cout << "  挑战任务：🏧 ATM取款机模拟" << endl;
    cout << "════════════════════════════════" << endl;

    double balance = 1000.0;  // 初始余额
    int choice;
    double amount;

    while (true) {
        cout << endl;
        cout << "┌─────────────────────────┐" << endl;
        cout << "│      🏧 ATM自动取款机    │" << endl;
        cout << "├─────────────────────────┤" << endl;
        cout << "│  1. 查询余额            │" << endl;
        cout << "│  2. 取款                │" << endl;
        cout << "│  3. 存款                │" << endl;
        cout << "│  4. 退出                │" << endl;
        cout << "└─────────────────────────┘" << endl;
        cout << "请选择操作（1-4）：";
        cin >> choice;

        if (choice == 1) {
            // 查询余额
            cout << "💰 当前余额：" << balance << " 元" << endl;

        } else if (choice == 2) {
            // 取款
            cout << "请输入取款金额：";
            cin >> amount;

            if (amount <= 0) {
                cout << "❌ 金额必须大于0！" << endl;
            } else if (amount > balance) {
                cout << "❌ 余额不足！当前余额为 " << balance << " 元。" << endl;
            } else {
                balance -= amount;
                cout << "✅ 取款成功！取款 " << amount << " 元。" << endl;
                cout << "💰 当前余额：" << balance << " 元。" << endl;
            }

        } else if (choice == 3) {
            // 存款
            cout << "请输入存款金额：";
            cin >> amount;

            if (amount <= 0) {
                cout << "❌ 金额必须大于0！" << endl;
            } else {
                balance += amount;
                cout << "✅ 存款成功！存入 " << amount << " 元。" << endl;
                cout << "💰 当前余额：" << balance << " 元。" << endl;
            }

        } else if (choice == 4) {
            cout << "👋 感谢使用ATM，再见！" << endl;
            break;  // 退出循环

        } else {
            cout << "❌ 无效选项，请重新选择！" << endl;
        }
    }
    cout << endl;
}

// ============ 主函数 ============
int main() {
    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║  第17课：转圈的机器人——while循环       ║" << endl;
    cout << "║  知识点：while语法、循环条件、死循环    ║" << endl;
    cout << "╚══════════════════════════════════════════╝" << endl;
    cout << endl;

    int choice;
    while (true) {
        cout << "请选择要运行的示例：" << endl;
        cout << "1. 火箭发射倒计时器" << endl;
        cout << "2. 猜数字游戏" << endl;
        cout << "3. while vs do-while 对比演示" << endl;
        cout << "4. while循环求和（1到N）" << endl;
        cout << "5. 计数器：统计数字位数" << endl;
        cout << "6. 累加器：班级平均分" << endl;
        cout << "7. 输入验证：密码登录" << endl;
        cout << "8. 练习1：打印1到20" << endl;
        cout << "9. 练习2：1到100的和" << endl;
        cout << "10. 练习3：新年倒计时" << endl;
        cout << "11. 练习4：1到100奇数和" << endl;
        cout << "12. 练习5：乘法表查询器" << endl;
        cout << "13. 🏆 挑战：ATM取款机模拟" << endl;
        cout << "0. 退出程序" << endl;
        cout << "请输入选择（0-13）：";
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1: example1_countdown(); break;
            case 2: example2_guessing_game(); break;
            case 3: example_while_vs_dowhile(); break;
            case 4: example3_sum(); break;
            case 5: example_counter_digits(); break;
            case 6: example_accumulator_average(); break;
            case 7: example_input_validation(); break;
            case 8: practice1_print_1_to_20(); break;
            case 9: practice2_sum_1_to_100(); break;
            case 10: practice3_newyear_countdown(); break;
            case 11: practice4_odd_sum(); break;
            case 12: practice5_multiplication_table(); break;
            case 13: challenge_atm(); break;
            case 0:
                cout << "感谢学习！我们下一课再见！👋" << endl;
                return 0;
            default:
                cout << "无效选择，请重新输入！" << endl;
        }
    }
}
