/*
 * CSP-J 备考课程
 * 第3课：变量与基本数据类型
 * 考纲：int/long long/float/double/char/bool、命名、sizeof、const、初始化、溢出
 *
 * 编译运行：
 *   g++ -std=c++17 -O2 lesson03_变量与基本数据类型.cpp -o lesson03 && ./lesson03
 *
 * 本文件采用模块化 demo + main 菜单调度；默认依次运行全部演示（非交互卡住）。
 */

#include <iostream>
#include <iomanip>
#include <climits>
#include <cmath>
#include <string>
using namespace std;

// ------------------------------------------------------------
// 工具：分隔线
// ------------------------------------------------------------
void print_banner(const string& title) {
    cout << "\n========== " << title << " ==========\n";
}

void print_line() {
    cout << "----------------------------------------\n";
}

// ------------------------------------------------------------
// Demo 1：sizeof 与各类型占用
// ------------------------------------------------------------
void demo01_sizeof() {
    print_banner("Demo1: sizeof 与类型占用字节");
    cout << left;
    cout << setw(14) << "类型" << setw(10) << "sizeof" << "说明\n";
    print_line();
    cout << setw(14) << "int" << setw(10) << sizeof(int) << "常见 4 字节，约 ±21 亿\n";
    cout << setw(14) << "long long" << setw(10) << sizeof(long long) << "常见 8 字节，约 ±9e18\n";
    cout << setw(14) << "float" << setw(10) << sizeof(float) << "约 7 位有效数字\n";
    cout << setw(14) << "double" << setw(10) << sizeof(double) << "约 15~16 位有效数字\n";
    cout << setw(14) << "char" << setw(10) << sizeof(char) << "标准保证恒为 1\n";
    cout << setw(14) << "bool" << setw(10) << sizeof(bool) << "true/false\n";

    int a = 42;
    double b = 3.14;
    cout << "\nsizeof(变量 a): " << sizeof(a) << endl;
    cout << "sizeof(a + 1LL): " << sizeof(a + 1LL) << " (表达式类型提升)\n";
    cout << "sizeof(b): " << sizeof(b) << endl;

    int arr[10];
    cout << "sizeof(arr) = " << sizeof(arr)
         << ", 元素个数 = " << sizeof(arr) / sizeof(arr[0]) << endl;
}

// ------------------------------------------------------------
// Demo 2：int / long long 基本用法与范围
// ------------------------------------------------------------
void demo02_integer_types() {
    print_banner("Demo2: int 与 long long");
    int age = 15;
    int year = 2026;
    long long big = 14000000000LL;
    long long product = 100000LL * 100000LL;

    cout << "int age = " << age << endl;
    cout << "int year = " << year << endl;
    cout << "long long big = " << big << " (140 亿)\n";
    cout << "100000LL * 100000LL = " << product << endl;

    cout << "\nclimits 常量:\n";
    cout << "INT_MAX   = " << INT_MAX << endl;
    cout << "INT_MIN   = " << INT_MIN << endl;
    cout << "LLONG_MAX = " << LLONG_MAX << endl;
    cout << "LLONG_MIN = " << LLONG_MIN << endl;
}

// ------------------------------------------------------------
// Demo 3：float / double 精度对比
// ------------------------------------------------------------
void demo03_floating() {
    print_banner("Demo3: float 与 double 精度");
    float f = 1.0f / 3.0f;
    double d = 1.0 / 3.0;

    cout << fixed << setprecision(12);
    cout << "float  1/3 = " << f << "  (精度较低)\n";
    cout << "double 1/3 = " << d << "  (精度较高)\n";

    // 浮点比较
    double x = 0.1 + 0.2;
    cout << setprecision(20);
    cout << "0.1 + 0.2 实际存储约 = " << x << endl;
    cout << "直接 == 0.3 ? " << (x == 0.3 ? "true" : "false") << endl;
    const double EPS = 1e-9;
    cout << "fabs 容差比较 ? " << (fabs(x - 0.3) < EPS ? "true" : "false") << endl;
    cout << defaultfloat;  // 恢复默认格式
}

// ------------------------------------------------------------
// Demo 4：char 与 ASCII
// ------------------------------------------------------------
void demo04_char_ascii() {
    print_banner("Demo4: char 与 ASCII 运算");
    char grade = 'A';
    cout << "grade = '" << grade << "', ASCII = " << (int)grade << endl;
    cout << "'A'+1 按整数输出: " << ('A' + 1) << endl;
    cout << "(char)('A'+1) = '" << (char)('A' + 1) << "'\n";

    cout << "\n常见 ASCII:\n";
    cout << "'0'=" << (int)'0' << " '9'=" << (int)'9' << endl;
    cout << "'A'=" << (int)'A' << " 'Z'=" << (int)'Z' << endl;
    cout << "'a'=" << (int)'a' << " 'z'=" << (int)'z' << endl;
    cout << "' '=" << (int)' ' << " '\\n'=" << (int)'\n' << endl;

    // 数字字符转换
    char dig = '7';
    int val = dig - '0';
    cout << "\n字符 '" << dig << "' 转数值 = " << val << endl;
    cout << "数值 " << val << " 转字符 = '" << (char)(val + '0') << "'\n";

    // 大小写转换
    char lower = 'h';
    char upper = (char)(lower - 'a' + 'A');
    cout << "'" << lower << "' 转大写 = '" << upper << "'\n";
    cout << "'B' 转小写 = '" << (char)('B' - 'A' + 'a') << "'\n";
}

// ------------------------------------------------------------
// Demo 5：bool 逻辑值
// ------------------------------------------------------------
void demo05_bool() {
    print_banner("Demo5: bool 类型");
    bool passed = true;
    bool failed = false;
    cout << "passed = " << passed << " (true 输出为 1)\n";
    cout << "failed = " << failed << " (false 输出为 0)\n";

    cout << "bool(5)  = " << (bool)5 << endl;
    cout << "bool(0)  = " << (bool)0 << endl;
    cout << "bool(-1) = " << (bool)(-1) << endl;

    int score = 60;
    bool ok = (score >= 60);
    cout << "score=" << score << ", 及格标记 ok=" << ok << endl;
}

// ------------------------------------------------------------
// Demo 6：变量命名合法示例（非法名仅注释说明）
// ------------------------------------------------------------
void demo06_naming() {
    print_banner("Demo6: 合法变量命名示例");
    int myVar = 100;
    int _value = 200;
    int total_score = 300;
    int maxValue = 400;
    int studentCount = 500;
    int MAX_N = 1000;  // 非常量命名风格演示；真正常量见 const

    cout << "myVar = " << myVar << endl;
    cout << "_value = " << _value << endl;
    cout << "total_score = " << total_score << endl;
    cout << "maxValue = " << maxValue << endl;
    cout << "studentCount = " << studentCount << endl;
    cout << "MAX_N = " << MAX_N << endl;

    cout << "\n非法命名（仅注释，不能编译）：\n";
    cout << "  // int 2ndPlace;   // 数字开头\n";
    cout << "  // int float;      // 关键字\n";
    cout << "  // int my-name;    // 含 '-'\n";
    cout << "  // int student count; // 含空格\n";
}

// ------------------------------------------------------------
// Demo 7：const 常量
// ------------------------------------------------------------
void demo07_const() {
    print_banner("Demo7: const 常量");
    const int MAXN = 1000000;
    const double PI = 3.1415926535;
    const int MOD = 1000000007;

    cout << "MAXN = " << MAXN << endl;
    cout << "PI = " << PI << endl;
    cout << "MOD = " << MOD << endl;

    double r = 5.0;
    double area = PI * r * r;
    cout << fixed << setprecision(6);
    cout << "半径 r=" << r << " 的圆面积 = " << area << endl;
    cout << defaultfloat;

    // MAXN = 2; // 编译错误：不能修改 const
    cout << "(const 赋值会被编译器拒绝，见源码注释)\n";
}

// ------------------------------------------------------------
// Demo 8：声明与初始化
// ------------------------------------------------------------
void demo08_init() {
    print_banner("Demo8: 声明与初始化");
    int b = 10;
    int c(20);
    int d{30};
    int x = 0, y = 0;
    int p = 1, q = p + 2;

    cout << "b= " << b << ", c= " << c << ", d= " << d << endl;
    cout << "x= " << x << ", y= " << y << endl;
    cout << "p= " << p << ", q= " << q << endl;

    // 局部未初始化：不读取垃圾值，只做说明
    // int a; cout << a; // 危险：未定义行为
    cout << "提示：局部变量务必初始化，避免读取垃圾值。\n";

    int sum = 0;
    for (int i = 1; i <= 5; i++) sum += i;
    cout << "1+...+5 = " << sum << " (累加器从 0 开始)\n";
}

// ------------------------------------------------------------
// Demo 9：整数溢出
// ------------------------------------------------------------
void demo09_overflow() {
    print_banner("Demo9: 整数溢出与安全写法");
    int intMax = INT_MAX;
    cout << "INT_MAX = " << intMax << endl;
    cout << "INT_MAX + 1 (溢出演示) = " << (intMax + 1) << endl;

    int a = 100000, b = 100000;
    long long bad = a * b;           // 先 int 乘再赋值
    long long good1 = 1LL * a * b;
    long long good2 = (long long)a * b;

    cout << "\na=" << a << ", b=" << b << endl;
    cout << "long long bad  = a * b;        -> " << bad << "  (可能错误)\n";
    cout << "long long good = 1LL * a * b;  -> " << good1 << "  (正确)\n";
    cout << "long long good = (ll)a * b;    -> " << good2 << "  (正确)\n";

    // n*(n+1)/2 安全写法
    int n = 100000;
    // long long s = n * (n + 1) / 2; // 危险：n*(n+1) 可能先按 int 溢出
    long long s = 1LL * n * (n + 1) / 2;
    cout << "\n1+...+" << n << " = " << s << endl;
}

// ------------------------------------------------------------
// Demo 10：整数除法 vs 浮点除法
// ------------------------------------------------------------
void demo10_division() {
    print_banner("Demo10: 整数除法与类型转换");
    cout << "5 / 2 = " << (5 / 2) << "  (截断)\n";
    cout << "5.0 / 2 = " << (5.0 / 2) << endl;
    cout << "(double)5 / 2 = " << ((double)5 / 2) << endl;
    cout << "5 / 2.0 = " << (5 / 2.0) << endl;

    int a = 5, b = 2;
    double wrong = a / b;
    double right = (double)a / b;
    cout << "double wrong = a/b -> " << wrong << endl;
    cout << "double right = (double)a/b -> " << right << endl;

    cout << fixed << setprecision(2);
    int sum = 250, cnt = 3;
    cout << "平均分 = " << (1.0 * sum / cnt) << endl;
    cout << defaultfloat;
}

// ------------------------------------------------------------
// Demo 11：变量交换
// ------------------------------------------------------------
void demo11_swap() {
    print_banner("Demo11: 变量交换");
    int x = 10, y = 20;
    cout << "交换前: x=" << x << ", y=" << y << endl;
    int temp = x;
    x = y;
    y = temp;
    cout << "交换后: x=" << x << ", y=" << y << endl;

    // 再演示算术交换（了解即可，有溢出风险，竞赛更推荐 temp 或 std::swap）
    int p = 3, q = 7;
    cout << "\n算术交换前: p=" << p << ", q=" << q << endl;
    p = p + q;
    q = p - q;
    p = p - q;
    cout << "算术交换后: p=" << p << ", q=" << q << endl;
}

// ------------------------------------------------------------
// Demo 12：真题思路 — 人口与安全乘法
// ------------------------------------------------------------
void demo12_problem_population() {
    print_banner("Demo12: 真题思路 — 人口存储与乘法");
    int population = 1400000000;  // 14 亿，int 可存
    cout << "population(int) = " << population << endl;
    cout << "是否 <= INT_MAX ? " << (population <= INT_MAX ? "是" : "否") << endl;

    long long totalGDP = 80000LL * (long long)population;
    cout << "80000 * population (long long) = " << totalGDP << endl;
}

// ------------------------------------------------------------
// Demo 13：字符分类小练习（写死样例）
// ------------------------------------------------------------
void demo13_char_classify() {
    print_banner("Demo13: 字符分类（样例写死）");
    const char samples[] = {'7', 'A', 'z', '#'};
    int n = 4;
    for (int i = 0; i < n; i++) {
        char ch = samples[i];
        cout << "字符 '" << ch << "': ";
        if (ch >= '0' && ch <= '9') {
            cout << "数字，值=" << (ch - '0');
        } else if (ch >= 'A' && ch <= 'Z') {
            cout << "大写，对应小写='" << (char)(ch - 'A' + 'a') << "'";
        } else if (ch >= 'a' && ch <= 'z') {
            cout << "小写，对应大写='" << (char)(ch - 'a' + 'A') << "'";
        } else {
            cout << "其他字符，ASCII=" << (int)ch;
        }
        cout << endl;
    }
}

// ------------------------------------------------------------
// Demo 14：综合小系统
// ------------------------------------------------------------
void demo14_integrated() {
    print_banner("Demo14: 综合 — 学生信息小结构");
    const int FULL = 100;
    int chinese = 90;
    int math = 95;
    int english = 88;
    char level = 'A';
    bool pass = true;
    double average = (chinese + math + english) / 3.0;

    cout << fixed << setprecision(2);
    cout << "语文=" << chinese << " 数学=" << math << " 英语=" << english << endl;
    cout << "平均分=" << average << endl;
    cout << "等级='" << level << "' 及格=" << pass << " 满分常量=" << FULL << endl;
    cout << "sizeof(average)=" << sizeof(average) << endl;
    cout << defaultfloat;
}

// ------------------------------------------------------------
// 运行全部演示
// ------------------------------------------------------------
void run_all() {
    demo01_sizeof();
    demo02_integer_types();
    demo03_floating();
    demo04_char_ascii();
    demo05_bool();
    demo06_naming();
    demo07_const();
    demo08_init();
    demo09_overflow();
    demo10_division();
    demo11_swap();
    demo12_problem_population();
    demo13_char_classify();
    demo14_integrated();
}

// ------------------------------------------------------------
// 主菜单
// ------------------------------------------------------------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "================================================\n";
    cout << "  CSP-J 第3课：变量与基本数据类型 — 代码演示\n";
    cout << "================================================\n";
    cout << "  0. 运行全部演示（默认推荐）\n";
    cout << "  1. sizeof\n";
    cout << "  2. int / long long\n";
    cout << "  3. float / double\n";
    cout << "  4. char / ASCII\n";
    cout << "  5. bool\n";
    cout << "  6. 命名\n";
    cout << "  7. const\n";
    cout << "  8. 初始化\n";
    cout << "  9. 溢出\n";
    cout << " 10. 除法与转换\n";
    cout << " 11. 交换\n";
    cout << " 12. 人口真题思路\n";
    cout << " 13. 字符分类\n";
    cout << " 14. 综合示例\n";
    cout << "================================================\n";
    cout << "说明：为避免交互卡住，自动执行「0. 全部演示」。\n";
    cout << "若需单独模块，可将下方 choice 改为 1~14。\n";

    int choice = 0;  // 写死：默认全部运行
    // 交互写法（需要时取消注释）：
    // cout << "请选择 (0-14): ";
    // cin >> choice;

    cout << "当前 choice = " << choice << endl;

    switch (choice) {
        case 0: run_all(); break;
        case 1: demo01_sizeof(); break;
        case 2: demo02_integer_types(); break;
        case 3: demo03_floating(); break;
        case 4: demo04_char_ascii(); break;
        case 5: demo05_bool(); break;
        case 6: demo06_naming(); break;
        case 7: demo07_const(); break;
        case 8: demo08_init(); break;
        case 9: demo09_overflow(); break;
        case 10: demo10_division(); break;
        case 11: demo11_swap(); break;
        case 12: demo12_problem_population(); break;
        case 13: demo13_char_classify(); break;
        case 14: demo14_integrated(); break;
        default: cout << "无效选择\n"; break;
    }

    cout << "\n========== 第3课演示结束 ==========\n";
    return 0;
}
