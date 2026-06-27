/*
 * CSP-J 备考课程
 * 第11课：while 与 do-while 循环
 * 考纲知识点：
 *   - while(条件)先判断后执行
 *   - do-while先执行后判断（至少执行一次）
 *   - 循环条件设计
 *   - 死循环避免
 *   - while与for的适用场景对比
 *
 * 本文件包含：
 *   1. while循环基础演示（数字位数统计）
 *   2. do-while循环演示（输入校验）
 *   3. while与do-while对比演示
 *   4. 真题AC代码
 */

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// -------------------------------------------
// 演示1：while循环 - 统计数字位数
// -------------------------------------------
void demo_while_digit_count() {
    cout << "\n========== 演示1：while 统计数字位数 ==========" << endl;
    int n;
    cout << "请输入一个正整数：";
    cin >> n;

    if (n == 0) {
        cout << "0 是 1 位数" << endl;
        return;
    }

    int original = n;   // 保存原数用于显示
    int cnt = 0;
    while (n > 0) {
        cnt++;
        n /= 10;
    }
    cout << original << " 是 " << cnt << " 位数" << endl;
    cout << "循环执行了 " << cnt << " 次" << endl;
}

// -------------------------------------------
// 演示2：while循环 - 数字反转
// -------------------------------------------
void demo_while_reverse_number() {
    cout << "\n========== 演示2：while 数字反转 ==========" << endl;
    int n;
    cout << "请输入一个正整数：";
    cin >> n;

    int original = n;
    int rev = 0;
    while (n > 0) {
        int digit = n % 10;
        rev = rev * 10 + digit;
        n /= 10;
        cout << "  取出 " << digit << "，当前 rev = " << rev << endl;
    }
    cout << original << " 反转后为 " << rev << endl;
}

// -------------------------------------------
// 演示3：while - 读取直到EOF
// -------------------------------------------
void demo_while_read_until_eof() {
    cout << "\n========== 演示3：while 读取直到EOF ==========" << endl;
    cout << "请输入若干整数（Ctrl+D 结束）：" << endl;
    int x, sum = 0, cnt = 0;
    while (cin >> x) {
        sum += x;
        cnt++;
        cout << "  读到第 " << cnt << " 个数：" << x << "，累加和 = " << sum << endl;
    }
    // 清除cin的错误状态，以便后续输入正常
    cin.clear();
    cout << "共读取 " << cnt << " 个数，总和 = " << sum << endl;
}

// -------------------------------------------
// 演示4：do-while循环 - 输入校验
// -------------------------------------------
void demo_do_while_input_validation() {
    cout << "\n========== 演示4：do-while 输入校验 ==========" << endl;
    int score;
    int attempts = 0;
    do {
        attempts++;
        cout << "第 " << attempts << " 次尝试 - 请输入成绩（0-100）：";
        cin >> score;
        if (score < 0 || score > 100) {
            cout << "  [不合法] 成绩必须在 0 到 100 之间！" << endl;
        }
    } while (score < 0 || score > 100);

    cout << "成绩有效：" << score << " 分（共尝试 " << attempts << " 次）" << endl;
}

// -------------------------------------------
// 演示5：do-while - 菜单选择
// -------------------------------------------
void demo_do_while_menu() {
    cout << "\n========== 演示5：do-while 菜单选择 ==========" << endl;
    int choice;
    do {
        cout << "\n--- 简易菜单 ---" << endl;
        cout << "1. 说你好" << endl;
        cout << "2. 显示当前菜单演示次数" << endl;
        cout << "3. 显示一条鼓励语" << endl;
        cout << "0. 退出菜单" << endl;
        cout << "请选择：";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "  你好！祝你学习进步！" << endl;
                break;
            case 2:
                cout << "  do-while 菜单演示中..." << endl;
                break;
            case 3:
                cout << "  每天进步一点点，CSP-J 一定能拿奖！" << endl;
                break;
            case 0:
                cout << "  再见！" << endl;
                break;
            default:
                cout << "  无效选项，请重新选择！" << endl;
                break;
        }
    } while (choice != 0);
}

// -------------------------------------------
// 演示6：while vs do-while 对比
// -------------------------------------------
void demo_while_vs_do_while() {
    cout << "\n========== 演示6：while vs do-while 对比 ==========" << endl;

    // 条件为 false 时的情况
    cout << "\n--- 场景：条件一开始就为 false (n = 0) ---" << endl;
    int n = 0;

    cout << "while 版本：";
    int while_count = 0;
    while (n > 0) {
        while_count++;
    }
    cout << "循环体执行了 " << while_count << " 次" << endl;

    cout << "do-while 版本：";
    int dowhile_count = 0;
    do {
        dowhile_count++;
    } while (n > 0);
    cout << "循环体执行了 " << dowhile_count << " 次" << endl;

    // 条件为 true 时的情况
    cout << "\n--- 场景：条件为 true (n = 3) ---" << endl;
    n = 3;
    cout << "while 版本（倒计时）：";
    while (n > 0) {
        cout << n << " ";
        n--;
    }
    cout << endl;

    n = 3;
    cout << "do-while 版本（倒计时）：";
    do {
        cout << n << " ";
        n--;
    } while (n > 0);
    cout << endl;
    cout << "结论：条件为 true 时，两者行为相同" << endl;
}

// -------------------------------------------
// 演示7：死循环演示与避免
// -------------------------------------------
void demo_infinite_loop_and_fix() {
    cout << "\n========== 演示7：死循环识别与避免 ==========" << endl;

    // 注意：这里展示死循环的样子，但不实际执行
    cout << "\n【错误示例 - 仅供观察，不执行】" << endl;
    cout << "int i = 1;" << endl;
    cout << "while (i <= 10) {" << endl;
    cout << "    cout << i << endl;" << endl;
    cout << "    // 忘记 i++，死循环！" << endl;
    cout << "}" << endl;

    cout << "\n【正确示例】" << endl;
    int i = 1;
    while (i <= 10) {
        cout << i << " ";
        i++;  // 关键：更新循环变量
    }
    cout << endl;
    cout << "循环正常结束，共执行 10 次" << endl;

    // 刻意使用 while(true) + break
    cout << "\n【while(true) + break 模式】" << endl;
    cout << "演示：不断读取数字，输入 -1 结束" << endl;
    cout << "请输入若干整数（-1 结束）：";
    while (true) {
        int x;
        cin >> x;
        if (x == -1) {
            cout << "检测到 -1，跳出循环！" << endl;
            break;
        }
        cout << "  读到：" << x << "，其平方为：" << x * x << endl;
    }
}

// -------------------------------------------
// 真题1：数字反转（while）
// -------------------------------------------
void zhenti1_reverse_number() {
    cout << "\n========== 真题1：数字反转 ==========" << endl;
    int n;
    cout << "请输入一个正整数 N：";
    cin >> n;

    int rev = 0;
    while (n > 0) {
        int digit = n % 10;      // 取出最后一位
        rev = rev * 10 + digit;  // 拼接到反转结果
        n /= 10;                 // 去掉最后一位
    }

    cout << "反转后：" << rev << endl;
}

// -------------------------------------------
// 真题2：输入校验（do-while）
// -------------------------------------------
bool isAllDigit(const string& s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (!isdigit(c)) return false;
    }
    return true;
}

void zhenti2_password_validation() {
    cout << "\n========== 真题2：密码输入校验 ==========" << endl;
    cout << "密码要求：" << endl;
    cout << "  1. 长度在 6 到 16 位之间" << endl;
    cout << "  2. 不能全是数字" << endl;

    string password;
    bool valid;

    do {
        valid = true;
        cout << "\n请输入密码：";
        cin >> password;

        // 检查长度
        if (password.length() < 6) {
            cout << "密码长度不足（当前 " << password.length() << " 位），请重新输入！" << endl;
            valid = false;
        }
        else if (password.length() > 16) {
            cout << "密码长度超出（当前 " << password.length() << " 位），请重新输入！" << endl;
            valid = false;
        }
        // 检查是否全数字
        else if (isAllDigit(password)) {
            cout << "密码不能全为数字，请重新输入！" << endl;
            valid = false;
        }

    } while (!valid);

    cout << "密码设置成功！" << endl;
}

// -------------------------------------------
// 主菜单
// -------------------------------------------
int main() {
    int choice;
    do {
        cout << "\n╔══════════════════════════════════════════╗" << endl;
        cout << "║   第11课：while 与 do-while 循环         ║" << endl;
        cout << "╠══════════════════════════════════════════╣" << endl;
        cout << "║  1. while - 统计数字位数                ║" << endl;
        cout << "║  2. while - 数字反转                    ║" << endl;
        cout << "║  3. while - 读取直到EOF                 ║" << endl;
        cout << "║  4. do-while - 输入校验                 ║" << endl;
        cout << "║  5. do-while - 菜单选择                 ║" << endl;
        cout << "║  6. while vs do-while 对比              ║" << endl;
        cout << "║  7. 死循环演示与避免                    ║" << endl;
        cout << "║  8. 真题1：数字反转（while）            ║" << endl;
        cout << "║  9. 真题2：密码输入校验（do-while）     ║" << endl;
        cout << "║  0. 退出                                ║" << endl;
        cout << "╚══════════════════════════════════════════╝" << endl;
        cout << "请选择演示功能：";
        cin >> choice;

        switch (choice) {
            case 1:  demo_while_digit_count();          break;
            case 2:  demo_while_reverse_number();        break;
            case 3:  demo_while_read_until_eof();        break;
            case 4:  demo_do_while_input_validation();   break;
            case 5:  demo_do_while_menu();               break;
            case 6:  demo_while_vs_do_while();           break;
            case 7:  demo_infinite_loop_and_fix();       break;
            case 8:  zhenti1_reverse_number();           break;
            case 9:  zhenti2_password_validation();      break;
            case 0:
                cout << "感谢学习第11课，再见！" << endl;
                break;
            default:
                cout << "无效选择，请重新输入！" << endl;
                break;
        }
    } while (choice != 0);

    return 0;
}
