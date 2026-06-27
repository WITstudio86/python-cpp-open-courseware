/*
 * C++趣味学习 - 第24课：数学小天才——循环应用
 * 知识点：判断素数、找完数、水仙花数
 * 项目：寻找数字中的宝藏
 */

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// ============ 示例1：素数判断器 ============
void example1_prime_checker() {
    cout << "════════════════════════════════" << endl;
    cout << "  示例1：🔍 素数判断器" << endl;
    cout << "════════════════════════════════" << endl;

    int n;
    cout << "请输入一个正整数：";
    cin >> n;

    if (n <= 1) {
        cout << n << " 不是素数（素数必须大于1）" << endl;
        cout << endl;
        return;
    }

    bool isPrime = true;
    int factor = 0;

    // 只需检查到sqrt(n)，用break优化
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            isPrime = false;
            factor = i;
            break;  // 找到一个因子就够了
        }
    }

    if (isPrime) {
        cout << "✅ " << n << " 是素数！" << endl;
        cout << "   它只能被1和自身整除。" << endl;
    } else {
        cout << "❌ " << n << " 不是素数。" << endl;
        cout << "   它有一个因子：" << factor << "（" << factor << " × " << (n/factor) << " = " << n << "）" << endl;
    }
    cout << endl;
}

// ============ 示例2：寻找完数 ============
void example2_perfect_numbers() {
    cout << "════════════════════════════════" << endl;
    cout << "  示例2：🏆 完数猎人" << endl;
    cout << "════════════════════════════════" << endl;

    int limit;
    cout << "请输入搜索范围上限（建议不超过10000）：";
    cin >> limit;

    cout << endl;
    cout << "正在搜索 1 ~ " << limit << " 范围内的完数..." << endl;
    cout << "完数定义：一个数等于它的所有真因子之和" << endl;
    cout << "-------------------------------------------" << endl;

    int count = 0;

    for (int n = 2; n <= limit; n++) {
        int sum = 1;  // 1总是真因子

        // 找所有真因子并求和（优化：只需检查到sqrt(n)）
        for (int i = 2; i <= sqrt(n); i++) {
            if (n % i == 0) {
                sum += i;
                if (i != n / i) {  // 避免重复计算（如25的因子5）
                    sum += n / i;
                }
            }
        }

        // 如果是完数，显示详细信息
        if (sum == n && n != 1) {
            count++;
            cout << "💎 第" << count << "个完数：" << n << " = 1";

            // 显示所有真因子
            for (int i = 2; i < n; i++) {
                if (n % i == 0) {
                    cout << " + " << i;
                }
            }
            cout << endl;
        }
    }

    cout << "-------------------------------------------" << endl;
    if (count == 0) {
        cout << "在 " << limit << " 以内没有找到完数。试试更大的范围？" << endl;
    } else {
        cout << "🌟 在 " << limit << " 以内共找到 " << count << " 个完数。" << endl;
    }
    cout << endl;
}

// ============ 示例3：寻找水仙花数 ============
void example3_narcissistic_numbers() {
    cout << "════════════════════════════════" << endl;
    cout << "  示例3：🌸 水仙花数寻踪" << endl;
    cout << "════════════════════════════════" << endl;

    cout << "水仙花数（三位数）：各位数字的立方和等于该数本身" << endl;
    cout << "例如：153 = 1³ + 5³ + 3³ = 1 + 125 + 27 = 153" << endl;
    cout << "-------------------------------------------" << endl;

    cout << "搜索所有三位水仙花数（100-999）：" << endl;

    int count = 0;

    for (int num = 100; num <= 999; num++) {
        int ge = num % 10;           // 个位数
        int shi = num / 10 % 10;     // 十位数
        int bai = num / 100;         // 百位数

        int sum = ge * ge * ge + shi * shi * shi + bai * bai * bai;

        if (sum == num) {
            count++;
            cout << "🌸 第" << count << "朵水仙花：" << num << " = ";
            cout << bai << "³ + " << shi << "³ + " << ge << "³ = ";
            cout << (bai*bai*bai) << " + " << (shi*shi*shi) << " + " << (ge*ge*ge);
            cout << " = " << sum << endl;
        }
    }

    cout << "-------------------------------------------" << endl;
    cout << "🌟 三位水仙花数共有 " << count << " 个。" << endl;
    cout << endl;
}

// ============ 练习答案 ============

// 练习1：找出100-200之间的素数
void practice1_primes_100_200() {
    cout << "════════════════════════════════" << endl;
    cout << "  练习1答案：100-200之间的素数" << endl;
    cout << "════════════════════════════════" << endl;

    int count = 0;
    cout << "100到200之间的素数：" << endl;
    cout << "-------------------------------------------" << endl;

    for (int n = 100; n <= 200; n++) {
        bool isPrime = true;
        for (int i = 2; i <= sqrt(n); i++) {
            if (n % i == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            cout << n << " ";
            count++;
            if (count % 5 == 0) cout << endl;
        }
    }

    cout << endl;
    cout << "-------------------------------------------" << endl;
    cout << "🌟 100到200之间共有 " << count << " 个素数。" << endl;
    cout << endl;
}

// 练习2：回文数判断
void practice2_palindrome() {
    cout << "════════════════════════════════" << endl;
    cout << "  练习2答案：回文数判断" << endl;
    cout << "════════════════════════════════" << endl;

    int n, original, reversed = 0;

    cout << "请输入一个整数，判断是否为回文数：";
    cin >> n;

    original = n;

    // 反转数字
    while (n > 0) {
        reversed = reversed * 10 + n % 10;
        n /= 10;
    }

    cout << "原数：" << original << "，反转后：" << reversed << endl;

    if (original == reversed) {
        cout << "✅ " << original << " 是回文数！（正读反读都一样）" << endl;
    } else {
        cout << "❌ " << original << " 不是回文数。" << endl;
    }
    cout << endl;
}

// 练习3：找所有三位水仙花数
void practice3_all_narcissistic() {
    cout << "════════════════════════════════" << endl;
    cout << "  练习3答案：所有三位水仙花数" << endl;
    cout << "════════════════════════════════" << endl;

    cout << "三位水仙花数列表（100-999）：" << endl;
    cout << "-------------------------------------------" << endl;

    int count = 0;
    for (int num = 100; num <= 999; num++) {
        int a = num / 100;           // 百位
        int b = num / 10 % 10;       // 十位
        int c = num % 10;            // 个位

        if (a*a*a + b*b*b + c*c*c == num) {
            count++;
            cout << num << " = " << a << "³+" << b << "³+" << c << "³";
            cout << " (" << a*a*a << "+" << b*b*b << "+" << c*c*c << ")" << endl;
        }
    }

    cout << "-------------------------------------------" << endl;
    cout << "🌟 共找到 " << count << " 个三位水仙花数。" << endl;
    cout << "   （它们是：153、370、371、407）" << endl;
    cout << endl;
}

// ============ 挑战任务：数字宝藏综合搜索 ============
void challenge_treasure_hunt() {
    cout << "════════════════════════════════" << endl;
    cout << "  挑战任务：🏆 数字宝藏综合搜索" << endl;
    cout << "════════════════════════════════" << endl;

    int choice;
    do {
        cout << endl;
        cout << "╔═════════ 数字宝藏猎人 ═════════╗" << endl;
        cout << "║  1. 🏆 搜索素数（统计个数）   ║" << endl;
        cout << "║  2. 💎 搜索完数               ║" << endl;
        cout << "║  3. 🌸 搜索水仙花数（三位）   ║" << endl;
        cout << "║  4. 🌸 搜索四位水仙花数       ║" << endl;
        cout << "║  5. 🔄 搜索回文数（统计个数） ║" << endl;
        cout << "║  6. 退出宝藏猎人               ║" << endl;
        cout << "╚════════════════════════════════╝" << endl;
        cout << "请选择宝藏类型（1-6）：";
        cin >> choice;

        cout << "─────────────────────────────────" << endl;

        if (choice == 1) {
            // 搜索素数
            int start, end;
            cout << "请输入搜索范围（起始 结束）：";
            cin >> start >> end;

            int count = 0;
            for (int n = start; n <= end; n++) {
                if (n <= 1) continue;
                bool isPrime = true;
                for (int i = 2; i <= sqrt(n); i++) {
                    if (n % i == 0) { isPrime = false; break; }
                }
                if (isPrime) count++;
            }
            cout << "🌟 " << start << "到" << end << "之间共有 " << count << " 个素数。" << endl;

        } else if (choice == 2) {
            // 搜索完数
            int limit;
            cout << "请输入搜索上限：";
            cin >> limit;

            cout << "搜索完数中..." << endl;
            for (int n = 2; n <= limit; n++) {
                int sum = 1;
                for (int i = 2; i <= sqrt(n); i++) {
                    if (n % i == 0) {
                        sum += i;
                        if (i != n / i) sum += n / i;
                    }
                }
                if (sum == n) {
                    cout << "💎 完数：" << n << " = 1";
                    for (int i = 2; i < n; i++) {
                        if (n % i == 0) cout << " + " << i;
                    }
                    cout << endl;
                }
            }

        } else if (choice == 3) {
            // 三位水仙花数
            cout << "三位水仙花数：" << endl;
            for (int num = 100; num <= 999; num++) {
                int a = num / 100;
                int b = num / 10 % 10;
                int c = num % 10;
                if (a*a*a + b*b*b + c*c*c == num) {
                    cout << "🌸 " << num << " = " << a << "³+" << b << "³+" << c << "³" << endl;
                }
            }

        } else if (choice == 4) {
            // 四位水仙花数（四次方）
            cout << "四位水仙花数（四次方）：" << endl;
            for (int num = 1000; num <= 9999; num++) {
                int a = num / 1000;          // 千位
                int b = num / 100 % 10;      // 百位
                int c = num / 10 % 10;       // 十位
                int d = num % 10;            // 个位
                if (a*a*a*a + b*b*b*b + c*c*c*c + d*d*d*d == num) {
                    cout << "🌸 " << num << " = " << a << "⁴+" << b << "⁴+" << c << "⁴+" << d << "⁴" << endl;
                }
            }

        } else if (choice == 5) {
            // 回文数统计
            int start, end;
            cout << "请输入搜索范围（起始 结束）：";
            cin >> start >> end;

            int count = 0;
            for (int num = start; num <= end; num++) {
                int n = num, reversed = 0;
                while (n > 0) {
                    reversed = reversed * 10 + n % 10;
                    n /= 10;
                }
                if (num == reversed) {
                    count++;
                    if (count <= 10) {  // 只显示前10个
                        cout << num << " ";
                    }
                }
            }
            if (count > 10) cout << "...";
            cout << endl;
            cout << "🌟 " << start << "到" << end << "之间共有 " << count << " 个回文数。" << endl;

        } else if (choice == 6) {
            cout << "👋 宝藏猎人收工！再见！" << endl;
        } else {
            cout << "❌ 无效选项！" << endl;
        }
        cout << "─────────────────────────────────" << endl;

    } while (choice != 6);

    cout << endl;
}

// ============ 主函数 ============
int main() {
    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║  第24课：数学小天才——循环应用         ║" << endl;
    cout << "║  知识点：素数、完数、水仙花数           ║" << endl;
    cout << "╚══════════════════════════════════════════╝" << endl;
    cout << endl;

    int choice;
    while (true) {
        cout << "请选择要运行的示例：" << endl;
        cout << "1. 素数判断器" << endl;
        cout << "2. 完数猎人" << endl;
        cout << "3. 水仙花数寻踪" << endl;
        cout << "4. 练习1：100-200之间的素数" << endl;
        cout << "5. 练习2：回文数判断" << endl;
        cout << "6. 练习3：所有三位水仙花数" << endl;
        cout << "7. 🏆 挑战：数字宝藏综合搜索" << endl;
        cout << "0. 退出程序" << endl;
        cout << "请输入选择（0-7）：";
        cin >> choice;
        cout << endl;

        if (choice == 0) break;

        switch (choice) {
            case 1: example1_prime_checker(); break;
            case 2: example2_perfect_numbers(); break;
            case 3: example3_narcissistic_numbers(); break;
            case 4: practice1_primes_100_200(); break;
            case 5: practice2_palindrome(); break;
            case 6: practice3_all_narcissistic(); break;
            case 7: challenge_treasure_hunt(); break;
            default:
                cout << "无效选择，请重新输入！" << endl;
        }
    }

    cout << "感谢学习！🎓 循环单元全部学完，你是编程小天才！👋" << endl;
    return 0;
}
