/*
 * CSP-J 备考课程
 * 第7课：顺序结构与程序调试
 * 考纲知识点：顺序执行、断点调试、变量监视、常见编译错误、程序阅读方法
 *
 * 本文件模块：
 * 1. 顺序执行演示
 * 2. 变量追踪（交换 / 多变量）
 * 3. 调试输出宏技巧
 * 4. 常见错误说明（安全演示）
 * 5. 读程：变量追踪表
 * 6. 常见陷阱
 * 7. 真题1：多变量顺序追踪 AC
 * 8. 真题2：三变量交换读程 AC
 *
 * 编译：g++ -std=c++17 -Wall -o lesson07 lesson07_顺序结构与程序调试.cpp
 */

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// -------------------- 调试宏 --------------------
// 演示默认开启；正式提交竞赛代码时应关闭
#define DEBUG_MODE

#ifdef DEBUG_MODE
#define DBG(x) cerr << "[DEBUG] " << #x << " = " << (x) << '\n'
#else
#define DBG(x) do {} while (0)
#endif

// -------------------- 工具函数 --------------------
void print_divider(const string& title) {
    cout << "\n========================================\n";
    cout << "  " << title << '\n';
    cout << "========================================\n";
}

void print_state3(const char* step, int a, int b, int c) {
    cout << left << setw(14) << step
         << " a=" << setw(5) << a
         << " b=" << setw(5) << b
         << " c=" << setw(5) << c << '\n';
}

void print_state2(const char* step, int x, int y) {
    cout << left << setw(14) << step
         << " x=" << setw(5) << x
         << " y=" << setw(5) << y << '\n';
}

// -------------------- 演示 1：顺序执行 --------------------
void demo01_sequential_execution() {
    print_divider("演示1：顺序执行");
    cout << "程序默认按书写顺序从上到下执行。\n\n";

    int a = 10;
    cout << "语句1: int a = 10;          → a=" << a << '\n';

    int b = 20;
    cout << "语句2: int b = 20;          → b=" << b << '\n';

    int c = a + b;
    cout << "语句3: int c = a + b;       → c=" << c << '\n';

    c = c * 2;
    cout << "语句4: c = c * 2;           → c=" << c << '\n';

    cout << "\n结论：后句可以使用前句结果；前句未完成，后句不会开始。\n";
}

// -------------------- 演示 2：变量追踪（交换） --------------------
void demo02_swap_trace() {
    print_divider("演示2：变量追踪 - 临时变量交换");

    int x = 5, y = 8;
    print_state2("初始", x, y);

    int t = x;
    print_state2("t=x", x, y);
    cout << "  (t=" << t << ")\n";

    x = y;
    print_state2("x=y", x, y);

    y = t;
    print_state2("y=t", x, y);

    cout << "\n交换成功：x=" << x << ", y=" << y << '\n';

    cout << "\n--- 对比：无临时变量的错误写法 ---\n";
    x = 5;
    y = 8;
    print_state2("初始", x, y);
    x = y;
    print_state2("x=y", x, y);
    y = x;
    print_state2("y=x", x, y);
    cout << "结果错误：两个都变成了原 y 的值。\n";
}

// -------------------- 演示 3：加减法交换 + 多变量 --------------------
void demo03_multi_var_trace() {
    print_divider("演示3：加减交换 与 多变量追踪");

    cout << "【3.1 加减法交换（了解，注意溢出风险）】\n";
    int x = 5, y = 8;
    print_state2("初始", x, y);
    x = x + y;
    print_state2("x=x+y", x, y);
    y = x - y;
    print_state2("y=x-y", x, y);
    x = x - y;
    print_state2("x=x-y", x, y);
    cout << "最终：x=" << x << ", y=" << y << "（已交换）\n\n";

    cout << "【3.2 三变量顺序计算】\n";
    int p = 3, q = 7, r = 4;
    print_state3("初始", p, q, r);
    p = q - p;
    print_state3("p=q-p", p, q, r);
    q = r * p;
    print_state3("q=r*p", p, q, r);
    r = q + p;
    print_state3("r=q+p", p, q, r);
    cout << "最终：p=" << p << ", q=" << q << ", r=" << r << '\n';
}

// -------------------- 演示 4：调试输出技巧 --------------------
void demo04_debug_output() {
    print_divider("演示4：调试输出技巧");

#ifdef DEBUG_MODE
    cout << "当前 DEBUG_MODE 已开启（调试信息输出到 cerr）。\n";
#else
    cout << "当前 DEBUG_MODE 已关闭。\n";
#endif

    int total = 0;
    for (int i = 1; i <= 5; i++) {
        total += i;
        DBG(i);
        DBG(total);
    }
    cout << "正式结果 total = " << total << "  （应走 cout）\n";

    cout << "\n技巧：\n";
    cout << "1) 中间量用 cerr / DBG 宏，避免污染标准答案输出；\n";
    cout << "2) 提交前注释 #define DEBUG_MODE；\n";
    cout << "3) 全文搜索 DEBUG / cerr 做最后检查。\n";
}

// -------------------- 演示 5：常见错误说明（注释形式） --------------------
void demo05_common_errors() {
    print_divider("演示5：常见编译/逻辑错误说明");
    cout << "以下错误以注释展示，取消注释会导致编译失败或逻辑错误。\n\n";

    cout << "1) 缺少分号\n";
    cout << "   // cout << \"error\"\n";
    cout << "   正确：cout << \"text\";\n\n";

    cout << "2) 变量未声明\n";
    cout << "   // cout << unknownVar;\n";
    cout << "   正确：先声明再使用。\n\n";

    cout << "3) 类型不匹配\n";
    cout << "   // int x = \"hello\";\n";
    cout << "   正确：string s = \"hello\";\n\n";

    cout << "4) 花括号不匹配\n";
    cout << "   报错常见：expected '}' at end of input\n\n";

    cout << "5) 主函数签名\n";
    cout << "   // void main()  —— 不推荐/不标准\n";
    cout << "   正确：int main() { ... return 0; }\n\n";

    cout << "6) 中文分号/全角括号\n";
    cout << "   从网页复制时务必检查标点是否为英文符号。\n";
}

// -------------------- 演示 6：读程变量表 --------------------
void demo06_trace_table() {
    print_divider("演示6：程序阅读 - 变量追踪表");
    cout << "代码：m=10,n=3; m=m+n; n=m-n; m=m-n;\n\n";

    int m = 10, n = 3;
    cout << left << setw(12) << "步骤" << setw(8) << "m" << setw(8) << "n" << "说明\n";
    cout << string(40, '-') << '\n';
    cout << left << setw(12) << "初始" << setw(8) << m << setw(8) << n << "声明\n";

    m = m + n;  // 13
    cout << left << setw(12) << "m=m+n" << setw(8) << m << setw(8) << n << "10+3=13\n";

    n = m - n;  // 10
    cout << left << setw(12) << "n=m-n" << setw(8) << m << setw(8) << n << "13-3=10\n";

    m = m - n;  // 3
    cout << left << setw(12) << "m=m-n" << setw(8) << m << setw(8) << n << "13-10=3\n";

    cout << "\n结果：m=" << m << ", n=" << n << "（值已互换）\n";
    cout << "读程口诀：一步一更新，绝不跳步心算。\n";
}

// -------------------- 演示 7：常见陷阱 --------------------
void demo07_traps() {
    print_divider("演示7：常见陷阱");

    // 陷阱1：整数除法
    cout << "【陷阱1】整数除法\n";
    int u = 5, v = 2;
    cout << "5 / 2 = " << (u / v) << "（不是 2.5）\n";
    cout << "5.0 / 2 = " << (5.0 / 2) << '\n';
    cout << "a/2*2 当 a=5 时 = " << (u / 2 * 2) << "（不等于 a）\n\n";

    // 陷阱2：未初始化
    cout << "【陷阱2】未初始化局部变量\n";
    cout << "int s; s = s + 1;  // s 是垃圾值（此处不演示未定义行为）\n";
    int initialized = 0;
    initialized = initialized + 1;
    cout << "正确：先初始化再使用 → " << initialized << "\n\n";

    // 陷阱3：= 与 ==
    cout << "【陷阱3】= 与 == 混淆\n";
    int val = 5;
    cout << "执行 if (val = 10) 前 val=" << val << '\n';
    if (val = 10) {  // 赋值，结果为 10，条件为真
        cout << "条件成立，但这里是赋值！val 现为 " << val << '\n';
    }
    cout << "正确比较应写：if (val == 10)\n\n";

    // 陷阱4：空语句
    cout << "【陷阱4】if 后多余分号\n";
    int t = -1;
    cout << "t=" << t << "，执行 if(t>0); { cout << \"执行了\"; }\n";
    if (t > 0);  // 空语句
    {
        cout << "花括号内代码无条件执行！\n";
    }
}

// -------------------- 演示 8：断点调试操作说明 --------------------
void demo08_breakpoint_guide() {
    print_divider("演示8：断点调试操作指南（文字版）");
    cout << "以 VS Code / CLion / Dev-C++ 通用流程为例：\n\n";
    cout << "1. 在目标行左侧单击，设置红色断点；\n";
    cout << "2. 使用“调试运行”（不是普通运行）；\n";
    cout << "3. 程序在断点处暂停；\n";
    cout << "4. 打开 Variables / Watch 窗口观察变量；\n";
    cout << "5. Step Over：执行当前行；\n";
    cout << "6. Step Into：进入函数内部；\n";
    cout << "7. Continue：跑到下一个断点；\n";
    cout << "8. 每一步对比“实际值”和“预期值”。\n\n";

    cout << "下面用顺序计算模拟“单步监视”：\n";
    int a = 2, b = 3, c = 0;
    DBG(a);
    DBG(b);
    c = a * a + b * b;
    DBG(c);
    c = c + 1;
    DBG(c);
    cout << "正式输出 c = " << c << '\n';
}

// -------------------- 真题 1：多变量顺序追踪 --------------------
void exam01_trace_abc() {
    print_divider("真题1：多变量顺序追踪（AC）");
    cout << "原题：a=3,b=7,c=4; a=b-a; b=c*a; c=b+a; 输出 c\n";
    cout << "样例答案：20\n\n";

    int a = 3, b = 7, c = 4;
    print_state3("初始", a, b, c);

    a = b - a;
    print_state3("a=b-a", a, b, c);

    b = c * a;
    print_state3("b=c*a", a, b, c);

    c = b + a;
    print_state3("c=b+a", a, b, c);

    cout << "\n输出：";
    cout << c << '\n';
    cout << "判定：与答案 20 一致。\n";
}

// -------------------- 真题 2：交换读程 --------------------
void exam02_swap_read() {
    print_divider("真题2：交换变量读程（AC）");
    cout << "原题：x=15,y=8; t=x; x=y; y=t; 输出 x y\n";
    cout << "样例答案：8 15\n\n";

    int x = 15, y = 8;
    print_state2("初始", x, y);

    int t = x;
    cout << "t = " << t << '\n';
    x = y;
    print_state2("x=y", x, y);
    y = t;
    print_state2("y=t", x, y);

    cout << "\n输出：";
    cout << x << ' ' << y << '\n';
    cout << "功能：使用临时变量完成两变量交换。\n";
}

// -------------------- 附加：带整数除法的综合读程 --------------------
void exam03_div_trace() {
    print_divider("附加练习：含整数除法的顺序追踪");
    cout << "代码：a=10,b=3; c=a/b; a=a+c; b=a%b+c;\n";
    cout << "预期输出：13 4 3\n\n";

    int a = 10, b = 3, c = 0;
    print_state3("初始", a, b, c);

    c = a / b;
    print_state3("c=a/b", a, b, c);

    a = a + c;
    print_state3("a=a+c", a, b, c);

    b = a % b + c;
    print_state3("b=a%b+c", a, b, c);

    cout << "\n输出：";
    cout << a << ' ' << b << ' ' << c << '\n';
}

// -------------------- 菜单 --------------------
void show_menu() {
    cout << "\n========================================\n";
    cout << "  CSP-J 第7课：顺序结构与程序调试\n";
    cout << "========================================\n";
    cout << "  [1] 顺序执行演示\n";
    cout << "  [2] 变量追踪：临时变量交换\n";
    cout << "  [3] 加减交换 与 多变量追踪\n";
    cout << "  [4] 调试输出宏技巧\n";
    cout << "  [5] 常见错误说明\n";
    cout << "  [6] 读程：变量追踪表\n";
    cout << "  [7] 常见陷阱\n";
    cout << "  [8] 断点调试操作指南\n";
    cout << "  [9] 真题1：多变量顺序追踪\n";
    cout << "  [10] 真题2：交换变量读程\n";
    cout << "  [11] 附加：整数除法综合读程\n";
    cout << "  [0] 退出\n";
    cout << "========================================\n";
    cout << "请选择：";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int choice = -1;
    do {
        show_menu();
        if (!(cin >> choice)) {
            break;
        }
        cout << '\n';

        switch (choice) {
            case 1: demo01_sequential_execution(); break;
            case 2: demo02_swap_trace(); break;
            case 3: demo03_multi_var_trace(); break;
            case 4: demo04_debug_output(); break;
            case 5: demo05_common_errors(); break;
            case 6: demo06_trace_table(); break;
            case 7: demo07_traps(); break;
            case 8: demo08_breakpoint_guide(); break;
            case 9: exam01_trace_abc(); break;
            case 10: exam02_swap_read(); break;
            case 11: exam03_div_trace(); break;
            case 0:
                cout << "感谢学习第7课！下一课：if-else 分支结构。\n";
                break;
            default:
                cout << "无效选项，请输入 0-11。\n";
                break;
        }
    } while (choice != 0);

    return 0;
}
