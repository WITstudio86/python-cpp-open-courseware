/*
 * C++趣味学习 - 第20课：循环控制台——break与continue
 * 知识点：跳出循环、跳过本次
 * 项目：数字躲避游戏
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

// ============ 示例1：数字躲避游戏 ============
void example1_number_dodge() {
    cout << "════════════════════════════════" << endl;
    cout << "  示例1：🕹️ 数字躲避游戏" << endl;
    cout << "════════════════════════════════" << endl;

    cout << "规则：从1数到30，遇到以下数字要跳过：" << endl;
    cout << "  - 3的倍数" << endl;
    cout << "  - 个位数是3的数字" << endl;
    cout << "  - 十位数是3的数字" << endl;
    cout << "-------------------------------------------" << endl;

    for (int i = 1; i <= 30; i++) {
        // 判断是否需要跳过
        if (i % 3 == 0 || i % 10 == 3 || i / 10 == 3) {
            cout << "第" << i << "个 → 💨 跳过！（这是一个'危险数字'）" << endl;
            continue;  // 跳过这个数字，进入下一次循环
        }
        cout << "第" << i << "个 → 🔢 " << i << " ✓" << endl;
    }

    cout << "-------------------------------------------" << endl;
    cout << "🎮 游戏结束！你成功避开了所有危险数字！" << endl;
    cout << endl;
}

// ============ 示例2：查找质数——break的应用 ============
void example2_find_primes() {
    cout << "════════════════════════════════" << endl;
    cout << "  示例2：🔍 质数查找器（用break优化）" << endl;
    cout << "════════════════════════════════" << endl;

    int limit;
    cout << "请输入搜索上限：";
    cin >> limit;

    cout << endl << "正在查找 2 ~ " << limit << " 之间的所有质数..." << endl;
    cout << "-------------------------------------------" << endl;

    int count = 0;

    for (int num = 2; num <= limit; num++) {
        bool isPrime = true;

        // 只需检查到sqrt(num)，用break提前终止
        for (int i = 2; i <= sqrt(num); i++) {
            if (num % i == 0) {
                isPrime = false;
                break;  // 找到一个因子就够了，不用继续检查
            }
        }

        if (isPrime) {
            cout << num << "\t";
            count++;
            if (count % 10 == 0) cout << endl;  // 每10个换行
        }
    }

    cout << endl << "-------------------------------------------" << endl;
    cout << "🌟 " << limit << "以内共有 " << count << " 个质数。" << endl;
    cout << endl;
}

// ============ 示例3：break与continue对比实验 ============
void example3_break_vs_continue() {
    cout << "════════════════════════════════" << endl;
    cout << "  示例3：🧪 break vs continue 对比实验" << endl;
    cout << "════════════════════════════════" << endl;

    cout << "实验：循环1到10，遇到5时的不同表现" << endl;
    cout << "-------------------------------------------" << endl;

    // 实验1：正常循环（对照组）
    cout << "🔵 正常循环：            ";
    for (int i = 1; i <= 10; i++) {
        cout << i << " ";
    }
    cout << endl;

    // 实验2：使用break
    cout << "🔴 使用break（遇到5）：  ";
    for (int i = 1; i <= 10; i++) {
        if (i == 5) break;    // 到5就彻底停止
        cout << i << " ";
    }
    cout << "← 5及以后全部消失！" << endl;

    // 实验3：使用continue
    cout << "🟡 使用continue（遇到5）：";
    for (int i = 1; i <= 10; i++) {
        if (i == 5) continue; // 只跳过5
        cout << i << " ";
    }
    cout << "← 只有5被跳过！" << endl;

    cout << "-------------------------------------------" << endl;
    cout << "📌 结论：" << endl;
    cout << "  break    → 一刀两断，循环结束" << endl;
    cout << "  continue → 只跳一段，循环继续" << endl;
    cout << endl;
}

// ============ 练习答案 ============

// 练习1：跳过3的倍数
void practice1_skip_multiples_of_3() {
    cout << "════════════════════════════════" << endl;
    cout << "  练习1答案：跳过3的倍数" << endl;
    cout << "════════════════════════════════" << endl;

    cout << "打印1-30，跳过所有3的倍数：" << endl;
    int count = 0;
    for (int i = 1; i <= 30; i++) {
        if (i % 3 == 0) {
            continue;  // 跳过3的倍数
        }
        cout << i << " ";
        count++;
        if (count % 10 == 0) cout << endl;
    }
    cout << endl << endl;
}

// 练习2：找到第一个7和5的公倍数
void practice2_first_common_multiple() {
    cout << "════════════════════════════════" << endl;
    cout << "  练习2答案：找第一个公倍数" << endl;
    cout << "════════════════════════════════" << endl;

    cout << "在1-100中找第一个能同时被7和5整除的数：" << endl;

    for (int i = 1; i <= 100; i++) {
        if (i % 7 == 0 && i % 5 == 0) {
            cout << "找到了！它是 " << i << endl;
            cout << "验证：35 ÷ 7 = " << (35 / 7) << "，35 ÷ 5 = " << (35 / 5) << endl;
            break;  // 找到就停止
        }
    }
    cout << endl;
}

// 练习3：数字过滤器
void practice3_number_filter() {
    cout << "════════════════════════════════" << endl;
    cout << "  练习3答案：数字过滤器" << endl;
    cout << "════════════════════════════════" << endl;

    int num;
    cout << "请连续输入10个整数（输入0则提前结束），程序只显示偶数。" << endl;
    cout << "-------------------------------------------" << endl;

    for (int i = 1; i <= 10; i++) {
        cout << "第" << i << "个数：";
        cin >> num;

        if (num == 0) {
            cout << "⚠️ 检测到0，结束输入！" << endl;
            break;  // 终止循环
        }

        if (num % 2 != 0) {
            cout << "   → " << num << " 是奇数，跳过。" << endl;
            continue;  // 跳过奇数，不显示在结果中
        }

        cout << "   → ✅ " << num << " 是偶数，已记录！" << endl;
    }
    cout << endl;
}

// ============ 挑战任务：猜数字豪华版 ============
void challenge_guess_number_deluxe() {
    cout << "════════════════════════════════" << endl;
    cout << "  挑战任务：🎯 猜数字豪华版" << endl;
    cout << "════════════════════════════════" << endl;

    srand(time(0));
    int secret = rand() % 100 + 1;
    int guess;
    int tries = 0;
    const int MAX_TRIES = 7;

    cout << "┌─────────────────────────────┐" << endl;
    cout << "│    🎯 猜数字豪华版          │" << endl;
    cout << "│    1-100之间，共7次机会     │" << endl;
    cout << "└─────────────────────────────┘" << endl;
    cout << endl;

    while (tries < MAX_TRIES) {
        cout << "第" << (tries + 1) << "/" << MAX_TRIES << "次 - 请输入你猜的数字：";
        cin >> guess;

        // 无效输入：不消耗次数
        if (guess < 1 || guess > 100) {
            cout << "⚠️ 请输入1-100之间的数字！这次不算。" << endl;
            continue;  // 跳过本次，不增加tries
        }

        tries++;  // 有效输入才计数

        if (guess == secret) {
            cout << "🎉 恭喜你猜对了！数字就是 " << secret << "！" << endl;
            cout << "你用了 " << tries << " 次机会。" << endl;

            if (tries == 1) {
                cout << "🏆 一发入魂！你是神算子！" << endl;
            } else if (tries <= 3) {
                cout << "🌟 非常厉害！" << endl;
            }
            break;  // 猜对了，结束游戏
        }

        // 提示"大了"或"小了"
        if (guess > secret) {
            cout << "📉 太大了！";
        } else {
            cout << "📈 太小了！";
        }

        // 显示剩余机会
        int remaining = MAX_TRIES - tries;
        if (remaining > 0) {
            cout << "还剩 " << remaining << " 次机会。" << endl;

            // 最后2次给额外提示
            if (remaining == 2) {
                cout << "   💡 提示：这个数的范围在左右20以内哦。" << endl;
            }
            if (remaining == 1) {
                int diff = abs(secret - guess);
                cout << "   💡 提示：你离答案还差" << diff << "左右。" << endl;
            }
        }

        // 次数用完
        if (tries >= MAX_TRIES) {
            cout << endl;
            cout << "😢 机会用完了！正确答案是 " << secret << "。" << endl;
        }
    }
    cout << endl;
}

// ============ 主函数 ============
int main() {
    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║  第20课：循环控制台——break与continue   ║" << endl;
    cout << "║  知识点：跳出循环、跳过本次             ║" << endl;
    cout << "╚══════════════════════════════════════════╝" << endl;
    cout << endl;

    int choice;
    while (true) {
        cout << "请选择要运行的示例：" << endl;
        cout << "1. 数字躲避游戏" << endl;
        cout << "2. 质数查找器" << endl;
        cout << "3. break vs continue 对比实验" << endl;
        cout << "4. 练习1：跳过3的倍数" << endl;
        cout << "5. 练习2：找第一个公倍数" << endl;
        cout << "6. 练习3：数字过滤器" << endl;
        cout << "7. 🏆 挑战：猜数字豪华版" << endl;
        cout << "0. 退出程序" << endl;
        cout << "请输入选择（0-7）：";
        cin >> choice;
        cout << endl;

        if (choice == 0) break;

        switch (choice) {
            case 1: example1_number_dodge(); break;
            case 2: example2_find_primes(); break;
            case 3: example3_break_vs_continue(); break;
            case 4: practice1_skip_multiples_of_3(); break;
            case 5: practice2_first_common_multiple(); break;
            case 6: practice3_number_filter(); break;
            case 7: challenge_guess_number_deluxe(); break;
            default:
                cout << "无效选择，请重新输入！" << endl;
        }
    }

    cout << "感谢学习！我们下一课再见！👋" << endl;
    return 0;
}
