/*
 * CSP-J 备考课程
 * 第4课：输入输出与格式化
 * 考纲：cin/cout、scanf/printf、setw/setprecision/fixed、转义字符、getchar/putchar、I/O 加速
 *
 * 编译运行：
 *   g++ -std=c++17 -O2 lesson04_输入输出与格式化.cpp -o lesson04 && ./lesson04
 *
 * 说明：
 *   - 所有本需键盘输入的演示均使用写死示例值，避免交互卡住
 *   - 真实输入写法在注释中保留，便于对照学习
 */

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <string>
using namespace std;

// ------------------------------------------------------------
// 工具
// ------------------------------------------------------------
void print_banner(const string& title) {
    cout << "\n========== " << title << " ==========\n";
}

void print_line() {
    cout << "----------------------------------------\n";
}

// ------------------------------------------------------------
// Demo 1：cout 基本输出
// ------------------------------------------------------------
void demo01_cout_basic() {
    print_banner("Demo1: cout 基本输出");
    int a = 3, b = 5;
    cout << "Hello, CSP-J!" << endl;
    cout << "a=" << a << ", b=" << b << "\n";
    cout << "a + b = " << a + b << "\n";
    cout << "使用 endl 换行并刷新；使用 \\n 仅换行。\n";

    bool ok = true;
    cout << "bool 默认输出: " << ok << " (true->1)\n";
}

// ------------------------------------------------------------
// Demo 2：cin 模拟（写死值）
// ------------------------------------------------------------
void demo02_cin_simulated() {
    print_banner("Demo2: cin 输入模拟（写死示例）");
    cout << "【真实写法】int a,b; cin >> a >> b;\n";
    cout << "【模拟输入】10 20\n";

    int a = 10, b = 20;  // 模拟 cin >> a >> b;
    cout << "读入结果: a=" << a << ", b=" << b << endl;
    cout << "a + b = " << a + b << endl;

    cout << "\n再模拟：读入 n 和 x（3 3.5）\n";
    int n = 3;
    double x = 3.5;  // 模拟 cin >> n >> x;
    cout << "n=" << n << ", x=" << x << ", n*x=" << n * x << endl;
}

// ------------------------------------------------------------
// Demo 3：I/O 加速说明 + 写法展示
// ------------------------------------------------------------
void demo03_fast_io() {
    print_banner("Demo3: I/O 加速写法");
    cout << "竞赛常用两行（main 开头）：\n";
    cout << "  ios::sync_with_stdio(false);\n";
    cout << "  cin.tie(nullptr);\n";
    cout << "效果：显著加快 cin/cout。\n";
    cout << "注意：之后不要混用 scanf/printf。\n";
    cout << "本演示文件为对照 cout/printf，main 中未关闭同步。\n";

    // 展示“若只使用流 I/O 时”的推荐写法（注释级模板）
    cout << "\n推荐比赛模板片段：\n";
    cout << "int main() {\n";
    cout << "    ios::sync_with_stdio(false);\n";
    cout << "    cin.tie(nullptr);\n";
    cout << "    // ... 仅 cin/cout ...\n";
    cout << "    return 0;\n";
    cout << "}\n";
}

// ------------------------------------------------------------
// Demo 4：printf 格式符大全
// ------------------------------------------------------------
void demo04_printf_specifiers() {
    print_banner("Demo4: printf 常用格式符");
    int num = 42;
    long long bigNum = 10000000000LL;
    double val = 3.14159;
    char ch = 'X';
    const char* s = "Hello";

    printf("%%d   (int)        : %d\n", num);
    printf("%%lld (long long)  : %lld\n", bigNum);
    printf("%%f   (double)     : %f\n", val);
    printf("%%c   (char)       : %c\n", ch);
    printf("%%s   (string)     : %s\n", s);
    printf("%%x   (hex lower)  : %x\n", num);
    printf("%%X   (hex upper)  : %X\n", num);
    printf("%%o   (octal)      : %o\n", num);
    printf("%%%%  (percent)    : 100%%\n");
}

// ------------------------------------------------------------
// Demo 5：printf 宽度与精度
// ------------------------------------------------------------
void demo05_printf_width_precision() {
    print_banner("Demo5: printf 宽度 / 精度 / 对齐");
    double pi = 3.1415926535;
    int n = 42;

    printf("默认:           [%f]\n", pi);
    printf("两位小数:       [%.2f]\n", pi);
    printf("宽度10两位小数: [%10.2f]\n", pi);
    printf("左对齐宽度10:   [%-10.2f]\n", pi);
    printf("前导0宽度10:    [%010.2f]\n", pi);
    printf("整数宽度8:      [%8d]\n", n);
    printf("整数左对齐8:    [%-8d]\n", n);
    printf("整数前导0宽8:   [%08d]\n", n);
    printf("科学计数法:     [%e]\n", pi);
}

// ------------------------------------------------------------
// Demo 6：scanf 模拟（写死值 + 注释真写法）
// ------------------------------------------------------------
void demo06_scanf_simulated() {
    print_banner("Demo6: scanf 输入模拟（写死示例）");
    cout << "【真实写法】scanf(\"%d %d\", &x, &y);  // 必须 &\n";
    cout << "【模拟输入】7 8\n";

    int x = 7, y = 8;  // 模拟 scanf("%d %d", &x, &y);
    printf("scanf 模拟结果: x=%d, y=%d, x+y=%d\n", x, y, x + y);

    cout << "\n【真实写法】scanf(\"%lf\", &d);  // double 用 %lf\n";
    cout << "【模拟输入】2.5\n";
    double d = 2.5;  // 模拟 scanf("%lf", &d);
    printf("double d = %.2f\n", d);

    cout << "\n错误示范（注释）：\n";
    cout << "  // scanf(\"%d\", x);   // 漏 &\n";
    cout << "  // scanf(\"%f\", &d);  // double 误用 %f\n";
    cout << "  // printf(\"%d\", big_long_long); // 格式不匹配\n";
}

// ------------------------------------------------------------
// Demo 7：iomanip — setw / setprecision / fixed
// ------------------------------------------------------------
void demo07_iomanip() {
    print_banner("Demo7: iomanip 格式化");
    double pi = 3.1415926535;

    cout << "默认输出: " << pi << endl;

    cout << fixed << setprecision(3);
    cout << "fixed + setprecision(3): " << pi << endl;

    cout << setprecision(6);
    cout << "setprecision(6): " << pi << endl;

    cout << "setw(10) 右对齐: [" << setw(10) << pi << "]\n";
    cout << left;
    cout << "setw(10) 左对齐: [" << setw(10) << pi << "]\n";
    cout << right;

    cout << "\nsetw 只作用于下一次输出:\n";
    cout << "[" << setw(5) << 1 << 2 << 3 << "]\n";
    cout << "正确写法: ";
    cout << "[" << setw(5) << 1 << setw(5) << 2 << setw(5) << 3 << "]\n";

    cout << setfill('0');
    cout << "setfill('0') + setw(5): " << setw(5) << 42 << endl;
    cout << setfill(' ');  // 恢复
    cout << defaultfloat;
}

// ------------------------------------------------------------
// Demo 8：表格对齐（cout vs printf）
// ------------------------------------------------------------
void demo08_table() {
    print_banner("Demo8: 表格对齐输出");
    cout << fixed << setprecision(1);

    cout << left;
    cout << setw(12) << "Name" << setw(8) << "Age" << setw(10) << "Score" << endl;
    print_line();
    cout << setw(12) << "Alice" << setw(8) << 15 << setw(10) << 98.5 << endl;
    cout << setw(12) << "Bob" << setw(8) << 16 << setw(10) << 92.0 << endl;
    cout << setw(12) << "Carol" << setw(8) << 15 << setw(10) << 100.0 << endl;
    cout << right;

    printf("\n--- printf 对照 ---\n");
    printf("%-12s%-8s%-10s\n", "Name", "Age", "Score");
    printf("%-12s%-8d%-10.1f\n", "Alice", 15, 98.5);
    printf("%-12s%-8d%-10.1f\n", "Bob", 16, 92.0);
    printf("%-12s%-8d%-10.1f\n", "Carol", 15, 100.0);
    cout << defaultfloat;
}

// ------------------------------------------------------------
// Demo 9：转义字符
// ------------------------------------------------------------
void demo09_escape() {
    print_banner("Demo9: 转义字符");
    cout << "换行 \\n : 第一行\n第二行\n";
    cout << "制表 \\t : A\tB\tC\n";
    cout << "双引号: \"Hello, CSP-J\"\n";
    cout << "单引号: \'A\'\n";
    cout << "反斜杠: C:\\Program Files\\\n";
    printf("printf 百分号: 100%%\n");
    cout << "空字符 \\0 是 C 字符串结束标志（ASCII 0）\n";

    cout << "\n阅读题演示: cout << \"A\\tB\\nC\\\\D\\\"E\";\n";
    cout << "实际输出:\n";
    cout << "A\tB\nC\\D\"E" << endl;
}

// ------------------------------------------------------------
// Demo 10：getchar / putchar（非交互）
// ------------------------------------------------------------
void demo10_getchar_putchar() {
    print_banner("Demo10: getchar / putchar（非交互演示）");
    cout << "【真实写法】char c = getchar();\n";
    cout << "【模拟】假设读到字符 'Z'\n";

    char c = 'Z';  // 模拟 getchar()
    cout << "getchar 模拟得到: '";
    putchar(c);
    cout << "' ASCII=" << (int)c << endl;

    cout << "\nputchar 输出 Hello:\n  ";
    const char* msg = "Hello";
    for (int i = 0; msg[i] != '\0'; i++) {
        putchar(msg[i]);
    }
    putchar('\n');

    cout << "\n各字符 ASCII:\n";
    for (int i = 0; msg[i] != '\0'; i++) {
        printf("  '%c' -> %d\n", msg[i], (int)msg[i]);
    }

    cout << "\n对比: cin>>ch 会跳过空白; getchar 不会跳过空白。\n";
}

// ------------------------------------------------------------
// Demo 11：cout 与 printf 小数对照
// ------------------------------------------------------------
void demo11_float_format_compare() {
    print_banner("Demo11: 小数格式化对照");
    double x = 3.1415926535;

    cout << fixed << setprecision(0) << "0位: " << x << endl;
    cout << setprecision(2) << "2位: " << x << endl;
    cout << setprecision(4) << "4位: " << x << endl;

    printf("printf 0位: %.0f\n", x);
    printf("printf 2位: %.2f\n", x);
    printf("printf 4位: %.4f\n", x);

    // 四舍五入观察
    double y = 2.5;
    printf("printf %.0f of 2.5 -> %.0f (实现相关，常见四舍五入到偶数/远离0，此处观察输出)\n", y, y);
    cout << defaultfloat;
}

// ------------------------------------------------------------
// Demo 12：真题 — 格式化阅读结果复现
// ------------------------------------------------------------
void demo12_problem_format_read() {
    print_banner("Demo12: 真题复现 — fixed/setw");
    double x = 3.14159;
    cout << fixed << setprecision(3);
    cout << x << endl;
    cout << setw(10) << x << endl;
    printf("printf 对照: %10.3f\n", x);
    cout << defaultfloat;
}

// ------------------------------------------------------------
// Demo 13：真题 — A+B 风格 scanf/printf
// ------------------------------------------------------------
void demo13_problem_ab() {
    print_banner("Demo13: 真题复现 — scanf A+B");
    cout << "模拟输入: 10 20\n";
    int a = 10, b = 20;  // scanf("%d%d", &a, &b);
    printf("a=%d\n", a);
    printf("b=%d\n", b);
    printf("a+b=%d\n", a + b);
}

// ------------------------------------------------------------
// Demo 14：圆的周长与面积（保留两位小数）
// ------------------------------------------------------------
void demo14_circle() {
    print_banner("Demo14: 圆的周长与面积（保留2位）");
    const double PI = 3.14159;
    cout << "【真实写法】cin >> r;\n";
    cout << "【模拟输入】r = 5\n";
    double r = 5.0;
    double circumference = 2 * PI * r;
    double area = PI * r * r;

    cout << fixed << setprecision(2);
    cout << "cout: " << circumference << " " << area << endl;
    printf("printf: %.2f %.2f\n", circumference, area);
    cout << defaultfloat;
}

// ------------------------------------------------------------
// Demo 15：多变量混合输出模式
// ------------------------------------------------------------
void demo15_mixed_patterns() {
    print_banner("Demo15: 常见输入输出模式");

    // 模式 A
    cout << "[模式A] 单行多整数 3 5 7\n";
    int a = 3, b = 5, c = 7;
    cout << "和 = " << a + b + c << endl;

    // 模式 B
    cout << "\n[模式B] 先 n 后 n 个数: n=4, 1 2 3 4\n";
    int n = 4;
    int arr[4] = {1, 2, 3, 4};
    long long sum = 0;
    for (int i = 0; i < n; i++) sum += arr[i];
    cout << "sum = " << sum << endl;

    // 模式 C：字符+数字
    cout << "\n[模式C] 字符与数字: A 65\n";
    char ch = 'A';
    int code = 65;
    cout << "ch='" << ch << "' code=" << code
         << " 校验ASCII=" << (int)ch << endl;

    // long long 输出
    long long big = 10000000000LL;
    cout << "\n[long long] cout -> " << big << endl;
    printf("[long long] printf %%lld -> %lld\n", big);
}

// ------------------------------------------------------------
// Demo 16：setprecision 无 fixed 的差异说明
// ------------------------------------------------------------
void demo16_precision_without_fixed() {
    print_banner("Demo16: setprecision 有无 fixed");
    double v = 123.456789;

    cout << "默认: " << v << endl;
    cout << "仅 setprecision(4): " << setprecision(4) << v << endl;
    cout << fixed;
    cout << "fixed + setprecision(4): " << setprecision(4) << v << endl;
    cout << defaultfloat;
    cout << "结论: 要“小数点后k位”，用 fixed + setprecision(k) 或 printf。\n";
}

// ------------------------------------------------------------
// 运行全部
// ------------------------------------------------------------
void run_all() {
    demo01_cout_basic();
    demo02_cin_simulated();
    demo03_fast_io();
    demo04_printf_specifiers();
    demo05_printf_width_precision();
    demo06_scanf_simulated();
    demo07_iomanip();
    demo08_table();
    demo09_escape();
    demo10_getchar_putchar();
    demo11_float_format_compare();
    demo12_problem_format_read();
    demo13_problem_ab();
    demo14_circle();
    demo15_mixed_patterns();
    demo16_precision_without_fixed();
}

// ------------------------------------------------------------
// 主菜单
// ------------------------------------------------------------
int main() {
    // 注意：本演示文件会混用 cout 与 printf 做对照教学，
    // 因此 main 中**不**关闭同步，避免输出顺序错乱。
    // 正式做题时若只用 cin/cout，可在 main 开头写：
    //   ios::sync_with_stdio(false);
    //   cin.tie(nullptr);
    // 详见 demo03_fast_io()。

    cout << "================================================\n";
    cout << "  CSP-J 第4课：输入输出与格式化 — 代码演示\n";
    cout << "================================================\n";
    cout << "  0. 运行全部演示（默认）\n";
    cout << "  1. cout 基础\n";
    cout << "  2. cin 模拟\n";
    cout << "  3. I/O 加速说明\n";
    cout << "  4. printf 格式符\n";
    cout << "  5. printf 宽度精度\n";
    cout << "  6. scanf 模拟\n";
    cout << "  7. iomanip\n";
    cout << "  8. 表格对齐\n";
    cout << "  9. 转义字符\n";
    cout << " 10. getchar/putchar\n";
    cout << " 11. 小数格式对照\n";
    cout << " 12. 真题 fixed/setw\n";
    cout << " 13. 真题 A+B\n";
    cout << " 14. 圆面积周长\n";
    cout << " 15. 常见 I/O 模式\n";
    cout << " 16. precision 差异\n";
    cout << "================================================\n";
    cout << "说明：为避免交互卡住，自动执行全部演示。\n";
    cout << "输入相关 demo 均用写死示例值，真实 cin/scanf 见注释。\n";

    int choice = 0;
    // 交互写法（需要时取消注释）：
    // cout << "请选择 (0-16): ";
    // cin >> choice;

    cout << "当前 choice = " << choice << endl;

    switch (choice) {
        case 0: run_all(); break;
        case 1: demo01_cout_basic(); break;
        case 2: demo02_cin_simulated(); break;
        case 3: demo03_fast_io(); break;
        case 4: demo04_printf_specifiers(); break;
        case 5: demo05_printf_width_precision(); break;
        case 6: demo06_scanf_simulated(); break;
        case 7: demo07_iomanip(); break;
        case 8: demo08_table(); break;
        case 9: demo09_escape(); break;
        case 10: demo10_getchar_putchar(); break;
        case 11: demo11_float_format_compare(); break;
        case 12: demo12_problem_format_read(); break;
        case 13: demo13_problem_ab(); break;
        case 14: demo14_circle(); break;
        case 15: demo15_mixed_patterns(); break;
        case 16: demo16_precision_without_fixed(); break;
        default: cout << "无效选择\n"; break;
    }

    cout << "\n========== 第4课演示结束 ==========\n";
    return 0;
}
