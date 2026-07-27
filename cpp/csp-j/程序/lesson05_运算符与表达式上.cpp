/*
 * CSP-J 备考课程
 * 第5课：运算符与表达式（上）
 * 考纲知识点：算术运算符(+ - * / %)、赋值运算符(= += -= *= /= %=)、
 *            自增自减(++ --)、运算符优先级、表达式求值
 *
 * 本文件包含：
 * 1. 算术运算符演示
 * 2. 取模技巧与数位分离
 * 3. 自增自减（含安全拆分写法）
 * 4. 复合赋值与优先级
 * 5. 表达式求值综合
 * 6. 真题1/真题2 AC 验证
 *
 * 编译：g++ -std=c++17 -Wall -o lesson05 lesson05_运算符与表达式上.cpp
 * 说明：同一表达式中对同一变量多次 ++/-- 会产生 unsequenced 告警，
 *       考试常考但实际应避免；本文件用分开语句演示效果。
 */

#include <iostream>
#include <iomanip>
using namespace std;

// ==================== 工具：打印分隔线 ====================
void print_title(const char* title) {
    cout << endl;
    cout << "========================================" << endl;
    cout << "  " << title << endl;
    cout << "========================================" << endl;
}

// ==================== 演示1：算术运算符 ====================
void demo01_arithmetic() {
    print_title("演示1：算术运算符 + - * / %");

    int a = 17, b = 5;
    cout << "a = " << a << ", b = " << b << endl;
    cout << "a + b = " << (a + b) << endl;
    cout << "a - b = " << (a - b) << endl;
    cout << "a * b = " << (a * b) << endl;
    cout << "a / b = " << (a / b) << "  (整数除法，截断小数)" << endl;
    cout << "a % b = " << (a % b) << endl;
    cout << "浮点除法 (double)a / b = " << fixed << setprecision(4)
         << ((double)a / b) << endl;
    cout << "错误示范 (double)(a / b) = " << ((double)(a / b))
         << "  (先整除再转，仍是整数)" << endl;

    cout << endl << "向零取整（C++11）：" << endl;
    cout << " 5 / 2 = " << (5 / 2) << endl;
    cout << "-5 / 2 = " << (-5 / 2) << endl;
    cout << " 5 / -2 = " << (5 / -2) << endl;
    cout << "-5 / -2 = " << (-5 / -2) << endl;

    cout << endl << "单目正负号：" << endl;
    int x = 5;
    cout << "x = " << x << ", -x = " << (-x) << ", +x = " << (+x) << endl;
    cout << endl;
}

// ==================== 演示2：取模规则与技巧 ====================
void demo02_modulo() {
    print_title("演示2：取模规则与数位技巧");

    cout << "取模符号跟随被除数（左操作数）：" << endl;
    cout << " 5 %  3 = " << (5 % 3) << endl;
    cout << " 5 % -3 = " << (5 % -3) << endl;
    cout << "-5 %  3 = " << (-5 % 3) << endl;
    cout << "-5 % -3 = " << (-5 % -3) << endl;

    cout << endl << "验证 a = (a/b)*b + (a%b)：" << endl;
    int pairs[][2] = {{17, 5}, {-17, 5}, {17, -5}, {-17, -5}};
    for (int i = 0; i < 4; i++) {
        int p = pairs[i][0], q = pairs[i][1];
        cout << "  " << p << " = (" << p << "/" << q << ")*" << q
             << " + (" << p << "%" << q << ") → "
             << (p / q) * q << " + " << (p % q) << " = "
             << (p / q) * q + (p % q) << endl;
    }

    int n = 12345;
    cout << endl << "数位分离 n = " << n << endl;
    cout << "  个位: " << n % 10 << endl;
    cout << "  十位: " << n / 10 % 10 << endl;
    cout << "  百位: " << n / 100 % 10 << endl;
    cout << "  千位: " << n / 1000 % 10 << endl;
    cout << "  万位: " << n / 10000 << endl;
    cout << "  后两位: " << n % 100 << endl;

    int sum = 0, t = n;
    while (t > 0) {
        sum += t % 10;
        t /= 10;
    }
    cout << "  数位和: " << sum << endl;

    cout << endl << "奇偶判断 (1~10)：" << endl;
    for (int i = 1; i <= 10; i++) {
        cout << "  " << i << (i % 2 == 0 ? " 偶" : " 奇");
        if (i % 5 == 0) cout << endl;
    }

    cout << endl << "环形时钟：当前 23 点，下一小时 = "
         << (23 + 1) % 24 << endl;
    cout << endl;
}

// ==================== 演示3：自增自减 ====================
void demo03_inc_dec() {
    print_title("演示3：自增自减 ++ / --");

    // 前置
    int x1 = 5, y1;
    y1 = ++x1;
    cout << "前置++: x1=5; y1=++x1 → x1=" << x1 << ", y1=" << y1 << endl;

    // 后置
    int x2 = 5, y2;
    y2 = x2++;
    cout << "后置++: x2=5; y2=x2++ → x2=" << x2 << ", y2=" << y2 << endl;

    // 前置自减
    int x3 = 5, y3;
    y3 = --x3;
    cout << "前置--: x3=5; y3=--x3 → x3=" << x3 << ", y3=" << y3 << endl;

    // 后置自减
    int x4 = 5, y4;
    y4 = x4--;
    cout << "后置--: x4=5; y4=x4-- → x4=" << x4 << ", y4=" << y4 << endl;

    cout << endl << "单独成语句时，前置后置效果相同：" << endl;
    int s1 = 10, s2 = 10;
    s1++;
    ++s2;
    cout << "  s1++ 后 s1=" << s1 << ", ++s2 后 s2=" << s2 << endl;

    cout << endl << "输出流中的自增：" << endl;
    int m = 10;
    cout << "  初始 m=" << m << endl;
    cout << "  cout << m++ 输出: " << m++ << "  (先用后加)" << endl;
    cout << "  现在 m=" << m << endl;
    cout << "  cout << ++m 输出: " << ++m << "  (先加后用)" << endl;
    cout << "  现在 m=" << m << endl;

    cout << endl << "不同变量混合（定义良好）：" << endl;
    int x = 5, y = 10;
    int z = x++ + ++y;
    cout << "  x=5,y=10; z=x++ + ++y" << endl;
    cout << "  → x=" << x << ", y=" << y << ", z=" << z << endl;
    cout << "  解释: x++用5→x=6; ++y→y=11用11; z=16" << endl;

    // 考试常考但实际应避免：同一变量多次修改
    // 下面用分开语句模拟「从左到右」考试常见答案，避免 unsequenced 警告
    cout << endl << "同一变量多次修改（考试常考，实际应避免）：" << endl;
    cout << "  危险写法: q = ++p + p++;  // unsequenced / 未定义风险" << endl;
    int p = 3;
    int left = ++p;    // 先加后用 → left=4, p=4
    int right = p++;   // 先用后加 → right=4, p=5
    int q = left + right;
    cout << "  安全拆分模拟从左到右: p 初值3 → p=" << p
         << ", q=" << q << " (期望 5, 8)" << endl;
    cout << "  工程建议: 永远拆成多条语句，不要在同一表达式改同一变量两次" << endl;
    cout << endl;
}

// ==================== 演示4：复合赋值 ====================
void demo04_compound_assign() {
    print_title("演示4：复合赋值运算符");

    int val = 10;
    cout << "初始 val = " << val << endl;
    val += 5;
    cout << "val += 5 → " << val << endl;
    val -= 3;
    cout << "val -= 3 → " << val << endl;
    val *= 2;
    cout << "val *= 2 → " << val << endl;
    val /= 4;
    cout << "val /= 4 → " << val << endl;
    val %= 3;
    cout << "val %= 3 → " << val << endl;

    cout << endl << "复合赋值右侧整体优先：" << endl;
    int r = 5;
    cout << "  r=5; r *= 2 + 3;" << endl;
    r *= 2 + 3;  // r = 5 * 5 = 25
    cout << "  → r = " << r << "  (先算 2+3=5，再 r*=5)" << endl;
    cout << "  不是 (5*2)+3=13！" << endl;

    cout << endl << "连续赋值（右结合）：" << endl;
    int u, v, w;
    u = v = w = 100;
    cout << "  u = v = w = 100 → u=" << u << ", v=" << v << ", w=" << w << endl;

    cout << endl << "赋值链：a += b += c" << endl;
    int aa = 2, bb = 3, cc = 4;
    aa += bb += cc;  // bb = 7, aa = 9
    cout << "  a=2,b=3,c=4; a += b += c → a=" << aa << ", b=" << bb
         << ", c=" << cc << endl;
    cout << endl;
}

// ==================== 演示5：运算符优先级 ====================
void demo05_precedence() {
    print_title("演示5：运算符优先级与结合性");

    int result;
    result = 3 + 5 * 2;
    cout << "3 + 5 * 2 = " << result << "  (乘优先)" << endl;

    result = (3 + 5) * 2;
    cout << "(3 + 5) * 2 = " << result << "  (括号优先)" << endl;

    result = 10 - 3 - 2;
    cout << "10 - 3 - 2 = " << result << "  (左结合 → 5)" << endl;

    result = 10 - (3 - 2);
    cout << "10 - (3 - 2) = " << result << "  (括号改变 → 9)" << endl;

    int t = 5;
    int u = -t + 3;
    cout << "-t + 3 (t=5) = " << u << "  (单目负号优先 → -2)" << endl;

    cout << endl << "混合：" << endl;
    int a = 2, b = 3, c = 4;
    cout << "a=2,b=3,c=4" << endl;
    cout << "a + b * c = " << (a + b * c) << endl;
    cout << "(a + b) * c = " << ((a + b) * c) << endl;
    cout << "a * b + c * a = " << (a * b + c * a) << endl;

    cout << endl << "口诀: 单目 > 算术 > 关系 > 逻辑 > 赋值" << endl;
    cout << "不确定时：加括号！" << endl;
    cout << endl;
}

// ==================== 演示6：溢出与类型转换 ====================
void demo06_overflow_cast() {
    print_title("演示6：溢出与类型转换");

    int a = 100000, b = 100000;
    int bad = a * b;  // 溢出
    long long good = (long long)a * b;
    cout << "a = b = 100000" << endl;
    cout << "int 乘法 a*b (溢出): " << bad << endl;
    cout << "(long long)a * b: " << good << endl;

    cout << endl << "整数除法再赋值给 double：" << endl;
    int x = 5, y = 2;
    double z1 = x / y;
    double z2 = 1.0 * x / y;
    double z3 = (double)x / y;
    cout << "  double z = 5/2 → " << z1 << endl;
    cout << "  double z = 1.0*5/2 → " << z2 << endl;
    cout << "  double z = (double)5/2 → " << z3 << endl;
    cout << endl;
}

// ==================== 演示7：表达式求值综合练习 ====================
void demo07_expression_drill() {
    print_title("演示7：表达式求值综合");

    int A = 10, B = 3;
    cout << "A=10, B=3" << endl;
    cout << "A / B = " << (A / B) << endl;
    cout << "A % B = " << (A % B) << endl;
    A += B;
    cout << "A += B → A = " << A << endl;
    A *= 2 + 3;
    cout << "A *= 2 + 3 → A = " << A << endl;

    cout << endl << "再练一组：" << endl;
    int p = 8, q = 3, r = 2;
    cout << "p=8,q=3,r=2" << endl;
    cout << "p / q * r = " << (p / q * r) << "  (左结合: 2*2=4)" << endl;
    cout << "p / (q * r) = " << (p / (q * r)) << "  (8/6=1)" << endl;
    cout << "p % q + r = " << (p % q + r) << endl;
    p += q *= r;  // q=6, p=14
    cout << "p += q *= r → p=" << p << ", q=" << q << ", r=" << r << endl;
    cout << endl;
}

// ==================== 真题1 AC ====================
void exam01_expression() {
    print_title("真题1：表达式求值（AC 验证）");
    cout << "程序逻辑：" << endl;
    cout << "  int a=10,b=3;" << endl;
    cout << "  cout << a/b; a%b; a+=b; a*=2+3;" << endl;
    cout << "预期输出：" << endl;
    cout << "3\n1\n13\n65" << endl;
    cout << "实际输出：" << endl;

    int a = 10, b = 3;
    cout << a / b << endl;
    cout << a % b << endl;
    a += b;
    cout << a << endl;
    a *= 2 + 3;
    cout << a << endl;
    cout << endl;
}

// ==================== 真题2 AC ====================
void exam02_inc_dec() {
    print_title("真题2：自增自减混合（AC 验证）");
    cout << "  int x=5,y=10; int z=x++ + ++y;" << endl;
    cout << "预期: x=6, y=11, z=16" << endl;

    int x = 5, y = 10;
    int z = x++ + ++y;
    cout << "实际: x=" << x << ", y=" << y << ", z=" << z << endl;
    cout << endl;
}

// ==================== 真题3 拓展：数位和 ====================
void exam03_digit_sum() {
    print_title("真题3拓展：数位和与个位（演示固定样例）");
    int n = 12345;
    cout << "样例 n = " << n << endl;
    int ones = n % 10;
    int sum = 0, t = n;
    while (t > 0) {
        sum += t % 10;
        t /= 10;
    }
    cout << "输出: " << sum << " " << ones << "  (预期 15 5)" << endl;
    cout << endl;
}

// ==================== 一键运行全部演示 ====================
void run_all() {
    demo01_arithmetic();
    demo02_modulo();
    demo03_inc_dec();
    demo04_compound_assign();
    demo05_precedence();
    demo06_overflow_cast();
    demo07_expression_drill();
    exam01_expression();
    exam02_inc_dec();
    exam03_digit_sum();
}

// ==================== 主菜单 ====================
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int choice;
    do {
        cout << "========================================" << endl;
        cout << "  CSP-J 第5课：运算符与表达式（上）" << endl;
        cout << "========================================" << endl;
        cout << " 1. 算术运算符" << endl;
        cout << " 2. 取模与数位技巧" << endl;
        cout << " 3. 自增自减" << endl;
        cout << " 4. 复合赋值" << endl;
        cout << " 5. 优先级与结合性" << endl;
        cout << " 6. 溢出与类型转换" << endl;
        cout << " 7. 表达式求值综合" << endl;
        cout << " 8. 真题1：表达式求值 AC" << endl;
        cout << " 9. 真题2：自增自减 AC" << endl;
        cout << "10. 真题3：数位和演示" << endl;
        cout << "11. 运行全部演示" << endl;
        cout << " 0. 退出" << endl;
        cout << "----------------------------------------" << endl;
        cout << "请输入选项: ";
        if (!(cin >> choice)) {
            break;
        }
        cout << endl;

        switch (choice) {
            case 0:
                cout << "再见！" << endl;
                break;
            case 1: demo01_arithmetic(); break;
            case 2: demo02_modulo(); break;
            case 3: demo03_inc_dec(); break;
            case 4: demo04_compound_assign(); break;
            case 5: demo05_precedence(); break;
            case 6: demo06_overflow_cast(); break;
            case 7: demo07_expression_drill(); break;
            case 8: exam01_expression(); break;
            case 9: exam02_inc_dec(); break;
            case 10: exam03_digit_sum(); break;
            case 11: run_all(); break;
            default:
                cout << "无效选项，请重新选择。" << endl << endl;
        }
    } while (choice != 0);

    return 0;
}
