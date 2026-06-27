/*
 * =============================================
 * C++趣味学习 —— 第14课：二选一的智慧——if-else
 * 知识点：双分支if-else、else配对规则
 * 趣味项目：🎯 猜数字小游戏
 * =============================================
 *
 * 本文件包含：
 *   示例1：基本if-else——判断奇偶数
 *   示例2：if-else判断成绩是否及格
 *   示例3：嵌套if-else——判断正数、负数还是零
 *   示例4：else配对规则演示
 *   练习1：奇偶判断器
 *   练习2：else配对谜题
 *   练习3：登录验证程序
 *   挑战任务：猜数字小游戏（完整版）
 *
 * 编译运行方式：
 *   g++ lesson14_if_else.cpp -o lesson14_if_else
 *   ./lesson14_if_else
 * =============================================
 */

#include <iostream>
#include <string>
#include <cstdlib>   // 用于rand()和srand()
#include <ctime>     // 用于time()
using namespace std;

// ==================== 示例1：基本if-else——判断奇偶数 ====================
void example1_oddEven() {
    cout << "\n======== 示例1：判断奇偶数 ========" << endl;

    int number;
    cout << "请输入一个整数：";
    cin >> number;

    // 使用 %（取余）运算符：number % 2 表示 number 除以 2 的余数
    // 如果余数为0，说明能被2整除，就是偶数
    if (number % 2 == 0) {
        // 条件成立：是偶数
        cout << number << " 是偶数！" << endl;
        cout << "偶数可以被2整除，没有余数哦~" << endl;
        cout << "判断方法：" << number << " ÷ 2 = " << (number / 2) << " 余 " << (number % 2) << endl;
    } else {
        // 条件不成立：是奇数
        cout << number << " 是奇数！" << endl;
        cout << "奇数除以2会余1哦~" << endl;
        cout << "判断方法：" << number << " ÷ 2 = " << (number / 2) << " 余 " << (number % 2) << endl;
    }

    // 这行无论奇偶都会执行
    cout << "判断完毕！" << endl;
}

// ==================== 示例2：if-else判断成绩是否及格 ====================
void example2_passOrFail() {
    cout << "\n======== 示例2：成绩是否及格 ========" << endl;

    int score;
    cout << "请输入你的考试分数（0~100）：";
    cin >> score;

    // 60分是及格线
    if (score >= 60) {
        // 及格了！
        cout << "🎉 恭喜你，及格了！" << endl;
        cout << "你的分数是：" << score << " 分" << endl;

        // 还可以根据分数给出不同评价
        if (score >= 90) {
            cout << "你的成绩非常优秀！继续保持！" << endl;
        }
        if (score >= 70 && score < 90) {
            cout << "成绩不错，继续努力可以更好！" << endl;
        }
        if (score >= 60 && score < 70) {
            cout << "刚刚及格，还有很大的进步空间！" << endl;
        }
    } else {
        // 没及格
        cout << "💪 这次没有及格，不要灰心！" << endl;
        cout << "你的分数是：" << score << " 分" << endl;
        cout << "距离及格还差 " << (60 - score) << " 分" << endl;
        cout << "认真复习，下次一定能过！加油！" << endl;
    }
}

// ==================== 示例3：嵌套if-else——判断正数、负数还是零 ====================
void example3_positiveNegativeZero() {
    cout << "\n======== 示例3：正数、负数还是零 ========" << endl;

    int number;
    cout << "请输入一个整数：";
    cin >> number;

    // 使用嵌套的if-else实现三种情况的判断
    if (number > 0) {
        // 第一种情况：大于0 → 正数
        cout << number << " 是正数！(+)" << endl;
        cout << "正数都大于零，在数轴的右边。" << endl;
    } else {
        // 走到这里说明 number <= 0
        // 在else里面再判断：是0还是负数？
        if (number == 0) {
            // 第二种情况：等于0
            cout << "你输入的是零！" << endl;
            cout << "零是一个特殊的数：它既不是正数，也不是负数。" << endl;
            cout << "零是正数和负数的分界线。" << endl;
        } else {
            // 第三种情况：小于0 → 负数
            cout << number << " 是负数！(-)" << endl;
            cout << "负数都小于零，在数轴的左边。" << endl;
        }
    }

    // 画出简易数轴帮助理解
    cout << "\n--- 数轴示意 ---" << endl;
    cout << " 负数区域       零       正数区域" << endl;
    cout << " <---------[ 0 ]--------->" << endl;
    cout << "你的数字 " << number << " 在数轴的这边 ↑" << endl;
}

// ==================== 示例4：else配对规则演示 ====================
void example4_elsePairing() {
    cout << "\n======== 示例4：else配对规则 ========" << endl;
    cout << "这个示例演示else配对的重要规则！" << endl;
    cout << endl;

    int score;
    cout << "请输入分数：";
    cin >> score;

    cout << "\n--- 版本1：没有花括号（陷阱！） ---" << endl;
    cout << "代码：" << endl;
    cout << "  if (score >= 90)" << endl;
    cout << "      if (score == 100)" << endl;
    cout << "          cout << \"满分！\";" << endl;
    cout << "  else" << endl;
    cout << "      cout << \"优秀！\";" << endl;
    cout << "运行结果：";

    // 陷阱版本：else和里面的if配对
    if (score >= 90)
        if (score == 100)
            cout << "满分！" << endl;
        else
            cout << "优秀！" << endl;
    // score < 90 时，什么都不输出！

    cout << "\n解释：else和里面if(score==100)配对" << endl;
    cout << "  - score=100 → 输出\"满分！\"" << endl;
    cout << "  - score=95  → 输出\"优秀！\"" << endl;
    cout << "  - score=80  → 什么都不输出（注意！）" << endl;

    cout << "\n--- 版本2：有花括号（正确！） ---" << endl;
    cout << "代码：" << endl;
    cout << "  if (score >= 90) {" << endl;
    cout << "      if (score == 100)" << endl;
    cout << "          cout << \"满分！\";" << endl;
    cout << "  } else {" << endl;
    cout << "      cout << \"继续加油！\";" << endl;
    cout << "  }" << endl;
    cout << "运行结果：";

    // 正确版本：花括号明确了配对关系
    if (score >= 90) {
        if (score == 100)
            cout << "满分！" << endl;
    } else {
        cout << "继续加油！" << endl;
    }

    cout << "\n解释：花括号让else和外面if(score >= 90)配对" << endl;
    cout << "  - score >= 90 → 进入if检查是否满分" << endl;
    cout << "  - score < 90  → 执行else，输出\"继续加油！\"" << endl;
    cout << endl;
    cout << "结论：永远使用花括号！它能帮你避免配对错误！" << endl;
}

// ==================== 练习1：奇偶判断器 ====================
void exercise1_oddEvenChecker() {
    cout << "\n======== 练习1：奇偶判断器 ========" << endl;

    int num;
    cout << "请输入一个整数：";
    cin >> num;

    // 核心逻辑：用 % 判断是否能被2整除
    if (num % 2 == 0) {
        cout << num << " 是偶数 ✓" << endl;
    } else {
        cout << num << " 是奇数 ✓" << endl;
    }
}

// ==================== 练习2：else配对谜题 ====================
void exercise2_pairingPuzzle() {
    cout << "\n======== 练习2：else配对谜题 ========" << endl;

    cout << "题目代码：" << endl;
    cout << "  if (score >= 90)" << endl;
    cout << "      if (score == 100)" << endl;
    cout << "          cout << \"满分！\";" << endl;
    cout << "  else" << endl;
    cout << "      cout << \"优秀！\";" << endl;
    cout << endl;

    cout << "问：else和哪个if配对？" << endl;
    cout << "答：else和里面最近的 if(score == 100) 配对！" << endl;
    cout << endl;

    cout << "让我们用不同分数来测试：" << endl;
    cout << endl;

    // 测试1：score = 100
    int score1 = 100;
    cout << "测试1：score = " << score1 << " → 输出：";
    if (score1 >= 90)
        if (score1 == 100)
            cout << "满分！";
        else
            cout << "优秀！";
    cout << endl;
    cout << "  （满分，正确！）" << endl;

    // 测试2：score = 95
    int score2 = 95;
    cout << "测试2：score = " << score2 << " → 输出：";
    if (score2 >= 90)
        if (score2 == 100)
            cout << "满分！";
        else
            cout << "优秀！";
    cout << endl;
    cout << "  （95分输出\"优秀！\"，else和==100的if配对了）" << endl;

    // 测试3：score = 80
    int score3 = 80;
    cout << "测试3：score = " << score3 << " → 输出：";
    if (score3 >= 90)
        if (score3 == 100)
            cout << "满分！";
        else
            cout << "优秀！";
    cout << endl;
    cout << "  （80分什么都没输出！因为80 < 90，最外层if都没进去）" << endl;

    cout << "\n结论：else配对规则 = else和最近的、未配对的if配对" << endl;
    cout << "解决方法：用花括号明确配对关系！" << endl;
}

// ==================== 练习3：登录验证程序 ====================
void exercise3_loginCheck() {
    cout << "\n======== 练习3：登录验证 ========" << endl;

    // 预设正确的用户名和密码
    string correctUser = "admin";
    string correctPass = "123456";

    string username, password;

    cout << "╔════════════════════════╗" << endl;
    cout << "║     用户登录系统      ║" << endl;
    cout << "╚════════════════════════╝" << endl;
    cout << endl;
    cout << "用户名：";
    cin >> username;
    cout << "密码：";
    cin >> password;

    cout << "\n—— 验证结果 ——" << endl;

    // 同时检查用户名和密码是否都正确
    // && 是"与"运算符，两边都成立才为true
    if (username == correctUser && password == correctPass) {
        cout << "✅ 登录成功！" << endl;
        cout << "   欢迎回来，" << username << "！" << endl;
        cout << "   您已成功登录系统。" << endl;
    } else {
        cout << "❌ 登录失败！" << endl;

        // 进一步判断是哪里错了
        if (username != correctUser) {
            cout << "   → 用户名错误！（正确的用户名是：admin）" << endl;
        }
        if (password != correctPass) {
            cout << "   → 密码错误！（正确的密码是：123456）" << endl;
        }
        cout << "   请检查后重新尝试。" << endl;
    }
}

// ==================== 挑战任务：🎯 猜数字小游戏（完整版） ====================
void challenge_guessNumber() {
    cout << "\n======== 🎯 挑战：猜数字小游戏 ========" << endl;

    // 使用随机数让游戏更有趣
    // srand(time(0)) 用当前时间作为随机种子，每次运行生成不同的数字
    srand(time(0));
    int secret = rand() % 100 + 1;  // 生成1~100之间的随机数

    int guess;        // 用户猜的数字
    int attempts = 0; // 猜测次数

    cout << "╔══════════════════════════════════════╗" << endl;
    cout << "║        🎯 猜数字小游戏             ║" << endl;
    cout << "║                                    ║" << endl;
    cout << "║  规则：我心里想了一个1~100之间的数 ║" << endl;
    cout << "║  你来猜，我会告诉你猜大了还是猜小了║" << endl;
    cout << "║  看看你几次能猜对！               ║" << endl;
    cout << "╚══════════════════════════════════════╝" << endl;
    cout << endl;

    // 最多给7次机会（二分查找理论上7次一定能猜中1~100的数字）
    while (attempts < 7) {
        cout << "第 " << (attempts + 1) << " 次猜测，请输入1~100之间的数字：";
        cin >> guess;

        attempts = attempts + 1;  // 猜测次数+1

        // 先检查输入是否在有效范围内
        if (guess < 1 || guess > 100) {
            cout << "⚠️  请输入1~100之间的有效数字！这次不算，重新来。" << endl;
            attempts = attempts - 1;  // 无效输入不计次数
            continue;  // 跳过本次循环，重新猜
        }

        // 核心判断逻辑
        if (guess == secret) {
            // 猜对了！
            cout << endl;
            cout << "╔══════════════════════════════════════╗" << endl;
            cout << "║  🎉🎉🎉 恭喜你猜对了！            ║" << endl;
            cout << "║  秘密数字就是 " << secret;
            // 根据secret的位数调整对齐
            if (secret < 10) {
                cout << "                    ║" << endl;
            } else if (secret < 100) {
                cout << "                   ║" << endl;
            } else {
                cout << "                  ║" << endl;
            }
            cout << "║  你一共猜了 " << attempts << " 次";
            if (attempts < 10) {
                cout << "                  ║" << endl;
            } else {
                cout << "                 ║" << endl;
            }

            // 根据猜测次数给出评价
            if (attempts == 1) {
                cout << "║  🏆 一次就中！你是天才！          ║" << endl;
            } else if (attempts <= 3) {
                cout << "║  ⭐ 非常厉害！运气和智慧并存！    ║" << endl;
            } else if (attempts <= 5) {
                cout << "║  👍 不错！表现良好！              ║" << endl;
            } else {
                cout << "║  💪 终于猜对了，继续加油！        ║" << endl;
            }
            cout << "╚══════════════════════════════════════╝" << endl;

            return;  // 猜对了，游戏结束
        } else {
            // 没猜对，给出提示
            if (guess > secret) {
                cout << "📈 猜大了！往下猜。" << endl;
            } else {
                cout << "📉 猜小了！往上猜。" << endl;
            }

            // 显示剩余机会
            int remaining = 7 - attempts;
            if (remaining > 0) {
                cout << "   还剩 " << remaining << " 次机会。" << endl;

                // 最后3次给额外提示
                if (remaining <= 3 && remaining > 0) {
                    // 缩小范围提示
                    if (secret % 2 == 0) {
                        cout << "   💡 提示：秘密数字是偶数。" << endl;
                    } else {
                        cout << "   💡 提示：秘密数字是奇数。" << endl;
                    }
                }
            }
            cout << endl;
        }
    }

    // 7次都没猜对
    cout << "╔══════════════════════════════════════╗" << endl;
    cout << "║  😅 很遗憾，7次机会用完了！       ║" << endl;
    cout << "║  秘密数字是 " << secret;
    if (secret < 10) {
        cout << "                       ║" << endl;
    } else if (secret < 100) {
        cout << "                      ║" << endl;
    } else {
        cout << "                     ║" << endl;
    }
    cout << "║  下次一定能猜中！加油！           ║" << endl;
    cout << "╚══════════════════════════════════════╝" << endl;
}

// ==================== 主函数：菜单选择 ====================
int main() {
    int choice;

    cout << "╔══════════════════════════════════════╗" << endl;
    cout << "║ 第14课：二选一的智慧——if-else     ║" << endl;
    cout << "║ 🎯 趣味项目：猜数字小游戏         ║" << endl;
    cout << "╠══════════════════════════════════════╣" << endl;
    cout << "║  请选择要运行的示例：               ║" << endl;
    cout << "║  1. 示例1：判断奇偶数              ║" << endl;
    cout << "║  2. 示例2：成绩是否及格            ║" << endl;
    cout << "║  3. 示例3：正数/负数/零            ║" << endl;
    cout << "║  4. 示例4：else配对规则演示        ║" << endl;
    cout << "║  5. 练习1：奇偶判断器              ║" << endl;
    cout << "║  6. 练习2：else配对谜题            ║" << endl;
    cout << "║  7. 练习3：登录验证程序            ║" << endl;
    cout << "║  8. 🏆 挑战：猜数字小游戏          ║" << endl;
    cout << "║  0. 退出                           ║" << endl;
    cout << "╚══════════════════════════════════════╝" << endl;
    cout << "请输入你的选择：";
    cin >> choice;

    // 使用if-else结构进行菜单选择
    if (choice == 1) {
        example1_oddEven();
    } else if (choice == 2) {
        example2_passOrFail();
    } else if (choice == 3) {
        example3_positiveNegativeZero();
    } else if (choice == 4) {
        example4_elsePairing();
    } else if (choice == 5) {
        exercise1_oddEvenChecker();
    } else if (choice == 6) {
        exercise2_pairingPuzzle();
    } else if (choice == 7) {
        exercise3_loginCheck();
    } else if (choice == 8) {
        challenge_guessNumber();
    } else if (choice == 0) {
        cout << "再见！记得多练习if-else语句哦~" << endl;
    } else {
        cout << "无效的选择，请输入0~8之间的数字。" << endl;
    }

    cout << endl;
    return 0;
}
