/*
 * CSP-J 备考课程
 * 第5课：运算符与表达式（上）
 * 考纲知识点：算术运算符(+ - * / %)、赋值运算符(= += -= *= /= %=)、自增自减(++ --)、运算符优先级
 *
 * 本文件包含：
 * 1. 算术运算符演示
 * 2. 自增自减详解
 * 3. 复合赋值运算符
 * 4. 优先级演示
 */

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    cout << "========== CSP-J 第5课：运算符与表达式（上） ==========" << endl;
    cout << endl;

    // ===== 一、算术运算符 =====
    cout << "【一、算术运算符】" << endl;

    int a = 17, b = 5;
    cout << "a = " << a << ", b = " << b << endl;
    cout << "a + b = " << a + b << endl;      // 22
    cout << "a - b = " << a - b << endl;      // 12
    cout << "a * b = " << a * b << endl;      // 85
    cout << "a / b = " << a / b << " (整数除法!)" << endl;  // 3
    cout << "a % b = " << a % b << endl;      // 2

    cout << "浮点除法: " << (double)a / b << endl;
    cout << endl;

    // ===== 二、取模运算 =====
    cout << "【二、取模运算（%）】" << endl;

    int n = 12345;
    cout << "数字: " << n << endl;
    cout << "个位: " << n % 10 << endl;          // 5
    cout << "十位: " << n / 10 % 10 << endl;     // 4
    cout << "百位: " << n / 100 % 10 << endl;    // 3
    cout << "千位: " << n / 1000 % 10 << endl;   // 2
    cout << "万位: " << n / 10000 << endl;       // 1
    cout << endl;

    // 取模符号规则
    cout << "取模符号规则（结果符号跟随被除数）:" << endl;
    cout << "5 % 3 = " << (5 % 3) << endl;       // 2
    cout << "5 % -3 = " << (5 % -3) << endl;     // 2
    cout << "-5 % 3 = " << (-5 % 3) << endl;     // -2
    cout << "-5 % -3 = " << (-5 % -3) << endl;   // -2
    cout << endl;

    // 判断奇偶
    cout << "奇偶判断:" << endl;
    for (int i = 1; i <= 10; i++) {
        cout << i << (i % 2 == 0 ? "是偶数" : "是奇数") << "  ";
    }
    cout << endl << endl;

    // ===== 三、自增自减（重点） =====
    cout << "【三、自增自减运算符（考试重点）】" << endl;

    // 前置自增
    int x1 = 5, y1;
    y1 = ++x1;  // 先加后用
    cout << "前置++: x1=5; y1=++x1 → x1=" << x1 << ", y1=" << y1 << endl;

    // 后置自增
    int x2 = 5, y2;
    y2 = x2++;  // 先用后加
    cout << "后置++: x2=5; y2=x2++ → x2=" << x2 << ", y2=" << y2 << endl;

    // 前置自减
    int x3 = 5, y3;
    y3 = --x3;  // 先减后用
    cout << "前置--: x3=5; y3=--x3 → x3=" << x3 << ", y3=" << y3 << endl;

    // 后置自减
    int x4 = 5, y4;
    y4 = x4--;  // 先用后减
    cout << "后置--: x4=5; y4=x4-- → x4=" << x4 << ", y4=" << y4 << endl;
    cout << endl;

    // 复杂自增表达式分析
    cout << "复杂表达式分析:" << endl;
    int p = 3;
    int q = ++p + p++;
    cout << "p=3; q = ++p + p++;" << endl;
    cout << "分析: ++p先加→p=4,值为4; p++先用值4,再加→p=5" << endl;
    cout << "结果: p=" << p << ", q=" << q << endl;
    cout << endl;

    // 自增自减逐步分析
    cout << "逐步分析示例:" << endl;
    int m = 10;
    cout << "初始: m = " << m << endl;
    cout << "cout << m++ 输出: " << m++ << " (先输出10,再m=11)" << endl;
    cout << "现在: m = " << m << endl;
    cout << "cout << ++m 输出: " << ++m << " (先m=12,再输出12)" << endl;
    cout << "现在: m = " << m << endl;
    cout << endl;

    // ===== 四、复合赋值运算符 =====
    cout << "【四、复合赋值运算符】" << endl;

    int val = 10;
    cout << "初始 val = " << val << endl;

    val += 5;   cout << "val += 5 → " << val << endl;   // 15
    val -= 3;   cout << "val -= 3 → " << val << endl;   // 12
    val *= 2;   cout << "val *= 2 → " << val << endl;   // 24
    val /= 5;   cout << "val /= 5 → " << val << endl;   // 4
    val %= 3;   cout << "val %= 3 → " << val << endl;   // 1
    cout << endl;

    // ===== 五、运算符优先级演示 =====
    cout << "【五、运算符优先级演示】" << endl;

    int result;

    result = 3 + 5 * 2;
    cout << "3 + 5 * 2 = " << result << " (乘号优先于加号)" << endl;

    result = (3 + 5) * 2;
    cout << "(3 + 5) * 2 = " << result << " (括号改变优先级)" << endl;

    result = 10 - 3 - 2;
    cout << "10 - 3 - 2 = " << result << " (左结合)" << endl;

    // 复合赋值优先级低
    int r = 5;
    r *= 2 + 3;  // 等价于 r *= (2+3) = r *= 5
    cout << "r=5; r *= 2 + 3 → r = " << r << " (先算2+3=5, 再r*=5)" << endl;

    // 赋值运算符右结合
    int u, v, w;
    u = v = w = 100;
    cout << "u = v = w = 100 → u=" << u << ", v=" << v << ", w=" << w << endl;
    cout << endl;

    // ===== 六、综合练习 =====
    cout << "【六、表达式求值综合练习】" << endl;

    int A = 10, B = 3;
    cout << "A = 10, B = 3" << endl;
    cout << "A / B = " << A / B << endl;           // 3
    cout << "A % B = " << A % B << endl;           // 1

    A += B;
    cout << "A += B → A = " << A << endl;          // 13

    A *= 2 + 3;
    cout << "A *= 2 + 3 → A = " << A << endl;      // 65
    cout << endl;

    // 经典题目：自增混合
    cout << "经典自增题:" << endl;
    int i = 5;
    int j = i++ + ++i;
    cout << "i=5; j = i++ + ++i;" << endl;
    cout << "i++: 先用5, i变6; ++i: 先i变7, 用7; j = 5+7 = 12" << endl;
    cout << "结果: i=" << i << ", j=" << j << endl;

    cout << endl << "========== 第5课演示结束 ==========" << endl;
    return 0;
}
