/*
 * =============================================
 * C++趣味学习 —— 第13课：人生的十字路口——if语句
 * 知识点：单分支if、代码块{}
 * 趣味项目：🚦 制作交通信号灯
 * =============================================
 *
 * 本文件包含：
 *   示例1：检查数字是否为正数
 *   示例2：交通信号灯（完整版）
 *   示例3：if的陷阱——忘记{}的后果
 *   练习1：正数判断器
 *   练习2：代码阅读（理解{}作用）
 *   练习3：交通信号灯程序
 *   挑战任务：简易银行取款程序
 *
 * 编译运行方式：
 *   g++ lesson13_if.cpp -o lesson13_if
 *   ./lesson13_if
 * =============================================
 */

#include <iostream>
#include <iomanip>
using namespace std;

// ==================== 示例1：最简单的if——检查数字是否为正数 ====================
void example1_checkPositive() {
    cout << "\n========== 示例1：检查数字是否为正数 ==========" << endl;

    int number;
    cout << "请输入一个整数：";
    cin >> number;

    // 单分支if：只有当number > 0成立时，花括号里的代码才会执行
    if (number > 0) {
        cout << number << " 是一个正数！" << endl;
        cout << "正数都大于零哦~" << endl;
        // 花括号里的这两行是一个整体
    }

    // 这行代码不在if的控制范围内，无论条件成立与否都会执行
    cout << "程序结束，谢谢使用！" << endl;
}

// ==================== 示例2：if配合代码块——交通信号灯 ====================
void example2_trafficLight() {
    cout << "\n========== 示例2：交通信号灯 ==========" << endl;

    char light;
    cout << "请输入信号灯颜色（R=红，G=绿，Y=黄）：";
    cin >> light;

    // 用三个独立的if分别判断三种颜色的灯
    // 注意：这里每个if都有{}，代码块里的内容是一个整体

    if (light == 'R' || light == 'r') {
        cout << "=== 交通信号灯 ===" << endl;
        cout << "当前信号：红灯 🔴" << endl;
        cout << "请停下！耐心等待~" << endl;
        cout << "==================" << endl;
    }

    if (light == 'G' || light == 'g') {
        cout << "=== 交通信号灯 ===" << endl;
        cout << "当前信号：绿灯 🟢" << endl;
        cout << "可以安全通行！" << endl;
        cout << "==================" << endl;
    }

    if (light == 'Y' || light == 'y') {
        cout << "=== 交通信号灯 ===" << endl;
        cout << "当前信号：黄灯 🟡" << endl;
        cout << "请减速，准备停下！" << endl;
        cout << "==================" << endl;
    }

    // 思考：如果用户输入的不是R/G/Y，会怎样？
    // 答案：三个if的条件都不成立，什么灯的状态都不会输出
}

// ==================== 示例3：if的陷阱——忘记加{}的后果 ====================
void example3_trapWithoutBraces() {
    cout << "\n========== 示例3：if的陷阱——忘记{}的后果 ==========" << endl;

    int x = -5;  // 把x改成5试试看，输出会有什么不同？

    cout << "x 的值是：" << x << endl;
    cout << "--- 没有{}的版本 ---" << endl;

    // 陷阱版本：没有花括号
    // if只能控制紧跟它的第一条语句（即下一行）
    if (x > 0)
        cout << "A：x是正数（受if控制）" << endl;
        cout << "B：这行不受if控制，总是执行！" << endl;
        // 上面这一行缩进看起来像是在if里面，但实际上不是！

    cout << "--- 有{}的正确版本 ---" << endl;

    // 正确版本：使用花括号明确代码块范围
    if (x > 0) {
        cout << "C：x是正数（受if控制）" << endl;
        cout << "D：这行也受if控制（因为在花括号内）" << endl;
    }

    cout << "--- 总结 ---" << endl;
    cout << "当x=-5时：只有B会输出（A、C、D都被跳过）" << endl;
    cout << "当x=5时：A、B、C、D全部输出" << endl;
    cout << "结论：无论什么时候，都建议写{}来避免歧义！" << endl;
}

// ==================== 示例4：嵌套if——游乐园身高检查 ====================
void example4_amusementPark() {
    cout << "\n========== 示例4：游乐园身高检查（嵌套if） ==========" << endl;

    int height;
    cout << "🏰 欢迎来到欢乐谷游乐园！" << endl;
    cout << "请输入你的身高（厘米）：";
    cin >> height;

    // 外层if：判断能否进入游乐园
    if (height >= 120) {
        cout << "✅ 你可以进入游乐园！" << endl;

        // 内层if-else if-else：根据身高推荐项目
        if (height >= 160) {
            cout << "🎢 你可以玩所有项目：过山车、跳楼机、大摆锤……尽情享受吧！" << endl;
        } else if (height >= 140) {
            cout << "🎡 你可以玩大部分项目，但过山车还需要再长高一点哦！" << endl;
            cout << "   推荐：海盗船、碰碰车、旋转飞椅" << endl;
        } else {
            cout << "🎠 欢迎来到儿童专区！旋转木马、小火车在向你招手~" << endl;
        }
    } else {
        cout << "😢 抱歉，身高不够120厘米，还不能进入游乐园。" << endl;
        cout << "   等你长高了再来玩哦！" << endl;
    }

    cout << "\n💡 这个程序使用了嵌套if结构——判断里面还有判断！" << endl;
    cout << "   外层if控制是否能入园，内层if控制能玩哪些项目。" << endl;
}

// ==================== 示例5：数字大小比较器 ====================
void example5_numberComparer() {
    cout << "\n========== 示例5：数字大小比较器 ==========" << endl;

    int a, b;
    cout << "请输入第一个整数：";
    cin >> a;
    cout << "请输入第二个整数：";
    cin >> b;

    cout << "\n—— 比较结果 ——" << endl;

    // 分别用三种比较运算符
    if (a > b) {
        cout << a << " 大于 " << b << " —— 第一个数更大！" << endl;
    }
    if (a < b) {
        cout << a << " 小于 " << b << " —— 第二个数更大！" << endl;
    }
    if (a == b) {
        cout << a << " 等于 " << b << " —— 两个数一样大！" << endl;
    }

    // 额外判断：是否为特殊数字
    if (a == 0 || b == 0) {
        cout << "💡 提示：你输入了数字 0！任意数加0还是它自己哦~" << endl;
    }
    if (a % b == 0 && b != 0) {
        cout << "💡 发现：" << a << " 可以被 " << b << " 整除！" << endl;
    }

    cout << "\n谢谢使用，再见！" << endl;
}

// ==================== 练习1：正数判断器 ====================
void exercise1_positiveChecker() {
    cout << "\n========== 练习1：正数判断器 ==========" << endl;

    int num;
    cout << "请输入一个整数：";
    cin >> num;

    // 如果数字大于0，就输出提示
    if (num > 0) {
        cout << num << " 是正数 ✓" << endl;
    }

    // 扩展思考：如果数字不大于0，会发生什么？
    // 答案：什么都不输出。程序直接结束。
    // 后续我们会学到if-else来处理"不大于0"的情况
}

// ==================== 练习2：代码阅读——理解{}的作用 ====================
void exercise2_codeReading() {
    cout << "\n========== 练习2：代码阅读——理解{}的作用 ==========" << endl;

    cout << "题目：下面代码会输出什么？" << endl;
    cout << "  int x = -5;" << endl;
    cout << "  if (x > 0)" << endl;
    cout << "      cout << \"A\";" << endl;
    cout << "      cout << \"B\";" << endl;
    cout << endl;

    // 实际运行这段代码来验证
    int x = -5;
    cout << "运行结果：";
    if (x > 0)
        cout << "A";
        cout << "B";     // 这行不在if控制范围内
    cout << endl;

    cout << "答案：只输出 \"B\"" << endl;
    cout << "原因：if(x > 0)不成立，所以A被跳过；但是B没有在{}里，" << endl;
    cout << "      它不受if控制，所以B总是会执行。" << endl;
    cout << "教训：永远给if加上花括号！即使只有一条语句也建议加上！" << endl;
}

// ==================== 练习3：交通信号灯程序 ====================
void exercise3_trafficLightSimple() {
    cout << "\n========== 练习3：交通信号灯程序 ==========" << endl;

    char light;
    cout << "请输入信号灯颜色（R/G/Y）：";
    cin >> light;

    cout << "—— 信号灯判断结果 ——" << endl;

    if (light == 'R' || light == 'r') {
        cout << "🔴 停下！红灯亮起，请不要通行。" << endl;
    }
    if (light == 'G' || light == 'g') {
        cout << "🟢 通行！绿灯亮起，可以安全通过。" << endl;
    }
    if (light == 'Y' || light == 'y') {
        cout << "🟡 注意！黄灯亮起，请减速准备停下。" << endl;
    }
}

// ==================== 挑战任务：简易银行取款程序 ====================
void challenge_bankWithdrawal() {
    cout << "\n========== 挑战任务：简易银行取款程序 ==========" << endl;

    double balance = 1000.00;  // 初始余额
    double amount;              // 取款金额

    // 显示欢迎界面和当前余额
    cout << "╔══════════════════════════════════╗" << endl;
    cout << "║      🏦 简易银行取款系统        ║" << endl;
    cout << "╠══════════════════════════════════╣" << endl;
    cout << fixed << setprecision(2);  // 设置输出保留2位小数
    cout << "║  当前余额：  " << balance << " 元         ║" << endl;
    cout << "╚══════════════════════════════════╝" << endl;
    cout << endl;
    cout << "请输入取款金额：";
    cin >> amount;

    cout << "\n—— 交易结果 ——" << endl;

    // 判断1：取款金额是否合法（大于0）
    if (amount <= 0) {
        cout << "❌ 错误：请输入有效的取款金额（大于0）！" << endl;
    }

    // 判断2：余额是否足够
    if (amount > 0 && amount <= balance) {
        balance = balance - amount;  // 扣除金额
        cout << "✅ 取款成功！" << endl;
        cout << "   取款金额：" << amount << " 元" << endl;
        cout << "   剩余余额：" << balance << " 元" << endl;
        cout << "   请收好您的现金，欢迎下次光临！" << endl;
    }

    // 判断3：余额不足
    if (amount > balance && amount > 0) {
        cout << "❌ 余额不足！取款失败。" << endl;
        cout << "   您想取 " << amount << " 元" << endl;
        cout << "   当前余额仅 " << balance << " 元" << endl;
        cout << "   差额：" << (amount - balance) << " 元" << endl;
    }

    cout << "\n感谢使用本系统，再见！" << endl;
}

// ==================== 练习4：偶数判断器 ====================
void exercise4_evenChecker() {
    cout << "\n========== 练习4：偶数判断器 ==========" << endl;

    int num;
    cout << "请输入一个整数：";
    cin >> num;

    // 判断是否为偶数：除以2余数为0
    if (num % 2 == 0) {
        cout << num << " 是一个偶数 ✓" << endl;
        cout << "偶数除以2的余数总是0哦！" << endl;
    }

    if (num % 2 != 0) {
        cout << num << " 是一个奇数" << endl;
        cout << "奇数除以2的余数总是1！" << endl;
    }
}

// ==================== 练习5：密码验证器 ====================
void exercise5_passwordChecker() {
    cout << "\n========== 练习5：密码验证器 ==========" << endl;

    const int PASSWORD = 1234;  // 预设密码（实际应用中应该更复杂）
    int input;

    cout << "===== 密码验证系统 =====" << endl;
    cout << "请输入四位数字密码：";
    cin >> input;

    if (input == PASSWORD) {
        cout << "✅ 密码正确，欢迎进入！" << endl;
        cout << "你已成功登录系统。" << endl;
    }

    if (input != PASSWORD) {
        cout << "❌ 密码错误，拒绝访问！" << endl;
        cout << "请检查密码后重试。" << endl;
        cout << "\n💡 提示：密码是一个有特殊意义的四位数哦~" << endl;
    }
}

// ==================== 主函数：菜单选择 ====================
int main() {
    int choice;

    cout << "╔══════════════════════════════════════╗" << endl;
    cout << "║  第13课：人生的十字路口——if语句    ║" << endl;
    cout << "║  🚦 趣味项目：交通信号灯           ║" << endl;
    cout << "╠══════════════════════════════════════╣" << endl;
    cout << "║  请选择要运行的示例：               ║" << endl;
    cout << "║  1. 示例1：检查数字是否为正数      ║" << endl;
    cout << "║  2. 示例2：交通信号灯              ║" << endl;
    cout << "║  3. 示例3：if的陷阱                ║" << endl;
    cout << "║  4. 示例4：游乐园身高检查（嵌套if）║" << endl;
    cout << "║  5. 示例5：数字大小比较器          ║" << endl;
    cout << "║  6. 练习1：正数判断器              ║" << endl;
    cout << "║  7. 练习2：代码阅读                ║" << endl;
    cout << "║  8. 练习3：交通信号灯程序          ║" << endl;
    cout << "║  9. 练习4：偶数判断器              ║" << endl;
    cout << "║ 10. 练习5：密码验证器              ║" << endl;
    cout << "║ 11. 🏆 挑战：简易银行取款程序      ║" << endl;
    cout << "║  0. 退出                           ║" << endl;
    cout << "╚══════════════════════════════════════╝" << endl;
    cout << "请输入你的选择：";
    cin >> choice;

    // 根据用户选择执行不同的函数
    if (choice == 1) {
        example1_checkPositive();
    }
    if (choice == 2) {
        example2_trafficLight();
    }
    if (choice == 3) {
        example3_trapWithoutBraces();
    }
    if (choice == 4) {
        example4_amusementPark();
    }
    if (choice == 5) {
        example5_numberComparer();
    }
    if (choice == 6) {
        exercise1_positiveChecker();
    }
    if (choice == 7) {
        exercise2_codeReading();
    }
    if (choice == 8) {
        exercise3_trafficLightSimple();
    }
    if (choice == 9) {
        exercise4_evenChecker();
    }
    if (choice == 10) {
        exercise5_passwordChecker();
    }
    if (choice == 11) {
        challenge_bankWithdrawal();
    }
    if (choice == 0) {
        cout << "再见！记得多练习if语句哦~" << endl;
    }

    cout << endl;
    return 0;
}
