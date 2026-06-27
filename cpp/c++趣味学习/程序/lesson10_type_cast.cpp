/*
 * ==========================================
 *  第10课：数字变形记——类型转换
 *  知识点：隐式类型转换、强制转换、数据溢出
 *  C++趣味学习系列
 * ==========================================
 */

#include <iostream>
#include <cstdio>          // 提供 printf 函数，用于格式化输出
#include <iomanip>         // 提供 fixed 和 setprecision
using namespace std;

int main() {
    // =====================================
    // 示例1：隐式类型转换
    //   int 和 double 一起运算时，
    //   int 会自动"换装"成 double
    // =====================================
    cout << "========== 示例1：隐式类型转换 ==========" << endl;

    int a = 5;             // a 穿着 int 的衣服
    double b = 3.2;        // b 穿着 double 的衣服

    // a 自动转换成 double（5 → 5.0），然后和 b 相加
    double sum = a + b;    // 5.0 + 3.2 = 8.2
    cout << a << " + " << b << " = " << sum << endl;
    cout << "sum 是 double 类型，占用 " << sizeof(sum) << " 字节" << endl;

    // int 赋值给 double：安全！小数衣服更大
    double d = a;          // int 5 自动变成 double 5.0
    cout << "int " << a << " 赋值给 double → " << d << endl;

    // double 赋值给 int：危险！小数部分会被丢掉
    int i = b;             // double 3.2 → int 3（丢失了 .2）
    cout << "double " << b << " 赋值给 int → " << i << "（小数部分丢失了！）" << endl;
    cout << endl;

    // =====================================
    // 示例2：强制类型转换——手动换装
    //   两种写法：(类型名)变量 和 static_cast<类型名>(变量)
    //   注意：不是四舍五入，是直接砍掉小数！
    // =====================================
    cout << "========== 示例2：强制类型转换 ==========" << endl;

    double pi = 3.1415926;

    // 方法1：C语言风格 —— (类型名)变量
    int pi_int1 = (int)pi;
    cout << "C风格:   (int)" << pi << " = " << pi_int1 << endl;

    // 方法2：C++风格（推荐） —— static_cast<类型名>(变量)
    int pi_int2 = static_cast<int>(pi);
    cout << "C++风格: static_cast<int>(" << pi << ") = " << pi_int2 << endl;

    // 演示：强制转换不是四舍五入！
    double num1 = 5.9;
    double num2 = 3.1;
    cout << "(int)" << num1 << " = " << (int)num1 << "（不是四舍五入！）" << endl;
    cout << "(int)" << num2 << " = " << (int)num2 << "（不是四舍五入！）" << endl;

    // 整数除法的陷阱对比
    cout << "\n=== 整数除法 vs 浮点除法 ===" << endl;
    cout << "5 / 2         = " << 5 / 2 << "   ← 整数除法，结果也是整数！" << endl;
    cout << "5.0 / 2       = " << 5.0 / 2 << "   ← 有小数参与，结果正确！" << endl;
    cout << "5 / 2.0       = " << 5 / 2.0 << "   ← 有小数参与，结果正确！" << endl;
    cout << "(double)5 / 2 = " << (double)5 / 2 << "   ← 强制转换后，结果正确！" << endl;
    cout << "5.0 / 2.0     = " << 5.0 / 2.0 << "   ← 两边都是小数，结果正确！" << endl;
    cout << endl;

    // =====================================
    // 示例3：数据溢出演示
    //   char 类型范围：-128 ~ 127
    //   就像一个小水杯，只能装这么多水
    // =====================================
    cout << "========== 示例3：数据溢出演示 ==========" << endl;

    // char 溢出示意
    char c = 127;  // char 能装的最大值
    cout << "char 类型范围：-128 ~ 127" << endl;
    cout << "char c = " << (int)c << "（当前值：127，杯子快满了）" << endl;

    c = c + 1;     // 再加 1，水杯溢出！
    cout << "c = c + 1 → c = " << (int)c << "（溢出！变成了 -128）" << endl;
    cout << "  解释：127 + 1 = 128，但 char 装不下 128，于是绕回了 -128" << endl;

    // 再演示一次：从 -128 继续加
    c = c + 1;
    cout << "c = c + 1 → c = " << (int)c << "（从 -128 到了 -127）" << endl;

    // int 类型的溢出（范围大得多，但也不是无限的）
    cout << "\n--- int 类型溢出演示 ---" << endl;
    int max_int = 2147483647;  // int 能装的最大值（约 21 亿）
    cout << "int 最大值：     " << max_int << endl;
    cout << "int 最大值 + 1： " << max_int + 1 << "（溢出！变成了负数）" << endl;
    cout << "int 最大值 + 2： " << max_int + 2 << "（继续绕圈...）" << endl;

    // 不同类型的"杯子"大小对比
    cout << "\n--- 各类型的「杯子」（范围）对比 ---" << endl;
    cout << "char 范围：     -128 ~ 127（最小的杯子）" << endl;
    cout << "short 范围：    -32768 ~ 32767" << endl;
    cout << "int 范围：      约 -21 亿 ~ 21 亿" << endl;
    cout << "long long 范围：约 -9百京 ~ 9百京（超大的杯子）" << endl;
    cout << "double 范围：   可以装下极大和极小的数" << endl;
    cout << endl;

    // =====================================
    // 练习1 答案：(int)5.7 的预测与验证
    // =====================================
    cout << "========== 练习1答案：(int)5.7 的结果 ==========" << endl;
    cout << "(int)5.7 = " << (int)5.7 << endl;
    cout << "解释：强制转换是直接砍掉小数部分，不是四舍五入！";
    cout << "所以 5.7 变成 5，而不是 6。" << endl;
    cout << endl;

    // =====================================
    // 练习2 答案：华氏度转摄氏度
    //   公式：C = (F - 32) × 5 ÷ 9
    //   注意：一定要避免整数除法！
    // =====================================
    cout << "========== 练习2答案：华氏度 → 摄氏度 ==========" << endl;

    double fahrenheit = 98.6;  // 人体正常体温（华氏度）

    // 方法1：使用 5.0 / 9 —— 其中一个用小数即可
    double celsius1 = (fahrenheit - 32) * 5.0 / 9;
    cout << "方法1（5.0/9）：     " << fahrenheit << " °F = "
         << celsius1 << " °C" << endl;

    // 方法2：使用 5 / 9.0
    double celsius2 = (fahrenheit - 32) * 5 / 9.0;
    cout << "方法2（5/9.0）：     " << fahrenheit << " °F = "
         << celsius2 << " °C" << endl;

    // 方法3：使用 (double) 强制转换
    double celsius3 = (fahrenheit - 32) * (double)5 / 9;
    cout << "方法3（强制转换）：  " << fahrenheit << " °F = "
         << celsius3 << " °C" << endl;

    // 错误示范：如果写成 (F-32)*5/9，结果会是 0！
    int wrong = (int)(fahrenheit - 32) * 5 / 9;
    cout << "\n【错误示范】用整数除法：" << (int)(fahrenheit - 32)
         << " * 5 / 9 = " << wrong << "（完全错误！）" << endl;
    cout << "  原因：(F-32)*5/9 中全是 int，5/9 = 0，任何数乘 0 都等于 0！" << endl;
    cout << endl;

    // =====================================
    // 练习3 答案：127+1 在 char 中的结果
    // =====================================
    cout << "========== 练习3答案：127+1 存入 char ==========" << endl;

    char ch = 127;
    cout << "char ch = " << (int)ch << "（初始值）" << endl;

    ch = ch + 1;
    cout << "ch = 127 + 1 → ch = " << (int)ch << endl;
    cout << "原因：char 的范围是 -128~127，127 是最大正数。" << endl;
    cout << "      127 的二进制是 01111111，" << endl;
    cout << "      加 1 变成 10000000（在补码中表示 -128），" << endl;
    cout << "      就像钟表一样，走到头就绕回来了！" << endl;
    cout << endl;

    // =====================================
    // 挑战任务答案：万能温度转换器
    //   输入摄氏度，输出华氏度和开尔文
    //   保留 2 位小数
    // =====================================
    cout << "========== 挑战任务答案：万能温度转换器 ==========" << endl;

    double celsius_input;  // 存放用户输入的摄氏度

    cout << "请输入摄氏温度：";
    cin >> celsius_input;

    // 计算华氏度和开尔文
    // 公式：F = C × 9 ÷ 5 + 32
    //       K = C + 273.15
    double f = celsius_input * 9.0 / 5.0 + 32;   // 华氏度
    double k = celsius_input + 273.15;            // 开尔文

    // 使用 printf 输出，%.2f 表示保留两位小数
    cout << "\n===== 温度转换结果 =====" << endl;
    printf("摄氏度 (C)：  %.2f °C\n", celsius_input);
    printf("华氏度 (F)：  %.2f °F\n", f);
    printf("开尔文 (K)：  %.2f K\n", k);

    // 也可以使用 cout 配合 fixed 和 setprecision
    cout << "\n（使用 cout + fixed + setprecision 的方式）" << endl;
    cout << fixed << setprecision(2);    // 设置保留两位小数
    cout << "摄氏度 (C)：  " << celsius_input << " °C" << endl;
    cout << "华氏度 (F)：  " << f << " °F" << endl;
    cout << "开尔文 (K)：  " << k << " K" << endl;

    // =====================================
    // 程序结束
    // =====================================
    cout << "\n========== 程序结束 ==========" << endl;
    cout << "恭喜！你已经掌握了C++中的类型转换！" << endl;
    cout << "记住：数字换装要小心，小数除法记得用小数哦！" << endl;

    return 0;  // 程序正常结束
}
