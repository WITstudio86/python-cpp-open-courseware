/*
 * CSP-J 备考课程
 * 第6课：运算符与表达式（下）
 * 考纲知识点：关系运算符、逻辑运算符及短路特性、位运算符、三目运算符
 *
 * 本文件包含：
 * 1. 关系运算符演示
 * 2. 逻辑运算与真值表
 * 3. 短路特性（重点）
 * 4. 位运算符与经典技巧
 * 5. 三目运算符
 * 6. 真题 AC 验证
 *
 * 编译：g++ -std=c++17 -Wall -o lesson06 lesson06_运算符与表达式下.cpp
 */

#include <iostream>
#include <bitset>
#include <string>
#include <cmath>
using namespace std;

void print_title(const char* title) {
    cout << endl;
    cout << "========================================" << endl;
    cout << "  " << title << endl;
    cout << "========================================" << endl;
}

// ==================== 演示1：关系运算符 ====================
void demo01_relational() {
    print_title("演示1：关系运算符 > < >= <= == !=");

    int a = 10, b = 20, c = 10;
    cout << "a=" << a << ", b=" << b << ", c=" << c << endl;
    cout << boolalpha;
    cout << "a < b  : " << (a < b) << endl;
    cout << "a > b  : " << (a > b) << endl;
    cout << "a <= c : " << (a <= c) << endl;
    cout << "a >= b : " << (a >= b) << endl;
    cout << "a == c : " << (a == c) << endl;
    cout << "a != b : " << (a != b) << endl;
    cout << noboolalpha;
    cout << "输出为 0/1 时: (a<b)=" << (a < b) << endl;

    cout << endl << "关系结果参与算术: (5>3)+10 = " << ((5 > 3) + 10) << endl;

    cout << endl << "字符按 ASCII 比较:" << endl;
    cout << "  'A' < 'B' : " << ('A' < 'B') << "  (65<66)" << endl;
    cout << "  'a' > 'A' : " << ('a' > 'A') << "  (97>65)" << endl;
    cout << "  '0' < '9' : " << ('0' < '9') << endl;

    cout << endl << "数学链式比较陷阱:" << endl;
    int x = 5;
    cout << "  x=5; 数学希望 0<x<10" << endl;
    cout << "  错误写法 0<x<10 的值 = " << (0 < x < 10)
         << "  (先算 0<x 得1，再 1<10 得1，恒易错)" << endl;
    cout << "  正确写法 0<x && x<10 = " << (0 < x && x < 10) << endl;

    cout << endl << "== 与 = 的区别:" << endl;
    int t = 3;
    cout << "  t 初始 = " << t << endl;
    if (t = 5) {
        cout << "  if(t=5) 进入了！t 被赋值为 " << t << endl;
    }
    if (t == 5) {
        cout << "  if(t==5) 判断相等，正确进入" << endl;
    }
    cout << endl;
}

// ==================== 演示2：逻辑运算真值表 ====================
void demo02_logic_truth() {
    print_title("演示2：逻辑运算符 && || !");

    cout << "真值表 (用 1/0 表示 true/false):" << endl;
    cout << " a b | && | || | !a" << endl;
    cout << " ----+----+----+----" << endl;
    for (int a = 1; a >= 0; a--) {
        for (int b = 1; b >= 0; b--) {
            cout << " " << a << " " << b << " |  "
                 << (a && b) << " |  " << (a || b)
                 << " |  " << (!a) << endl;
        }
    }

    cout << endl << "非0即真:" << endl;
    cout << "  (bool)5 = " << (bool)5 << ", (bool)0 = " << (bool)0
         << ", (bool)-1 = " << (bool)-1 << endl;
    cout << "  5 && 3 = " << (5 && 3) << "  (逻辑与，两边非0)" << endl;
    cout << "  5 & 3  = " << (5 & 3) << "  (按位与，0101&0011=0001)" << endl;
    cout << "  4 && 2 = " << (4 && 2) << "  (逻辑 → 1)" << endl;
    cout << "  4 & 2  = " << (4 & 2) << "  (按位 → 0，不同！)" << endl;

    cout << endl << "! 与 ~ 对比:" << endl;
    cout << "  !5 = " << (!5) << "  (逻辑非)" << endl;
    cout << "  ~5 = " << (~5) << "  (按位取反)" << endl;
    cout << "  !!5 = " << (!!5) << "  (规范化为 0/1)" << endl;
    cout << endl;
}

// ==================== 演示3：短路特性 ====================
void demo03_short_circuit() {
    print_title("演示3：短路特性（考试重点）");

    // && 短路
    int x = 0, y = 0;
    cout << "初始: x=0, y=0" << endl;
    cout << "执行: bool r = (x != 0) && (y = 100);" << endl;
    bool r1 = (x != 0) && (y = 100);
    cout << "结果: r1=" << r1 << ", x=" << x << ", y=" << y
         << "  (y 未改，因 && 短路)" << endl;

    // || 短路
    int p = 5;
    cout << endl << "初始: p=5" << endl;
    cout << "执行: (p > 0) || (p = 999);" << endl;
    bool r2 = (p > 0) || (p = 999);
    cout << "结果: r2=" << r2 << ", p=" << p
         << "  (p 未改，因 || 短路)" << endl;

    // 安全除法
    cout << endl << "安全除法: num=0" << endl;
    int num = 0;
    if (num != 0 && 100 / num > 10) {
        cout << "  不会执行" << endl;
    } else {
        cout << "  100/num 未执行，避免除零" << endl;
    }

    // 经典题 a++ && b++
    cout << endl << "经典: a=0,b=0; if(a++ && b++) a++;" << endl;
    int a = 0, b = 0;
    if (a++ && b++) {
        a++;
    }
    cout << "  → a=" << a << ", b=" << b << "  (预期 1 0)" << endl;

    cout << endl << "对比 || : c=0,d=0; if(c++ || d++) ;" << endl;
    int c = 0, d = 0;
    if (c++ || d++) {
        // empty
    }
    cout << "  → c=" << c << ", d=" << d << "  (两边都执行，1 1)" << endl;

    cout << endl << "|| 左真短路: e=1,f=0; if(e++ || f++) e++;" << endl;
    int e = 1, f = 0;
    if (e++ || f++) {
        e++;
    }
    cout << "  → e=" << e << ", f=" << f << "  (f++被短路，e=3 f=0)" << endl;

    // 数组安全访问示意
    cout << endl << "下标安全顺序: 先判范围再访问" << endl;
    int arr[3] = {10, 20, 30};
    int n = 3, i = 5;
    if (i >= 0 && i < n && arr[i] > 0) {
        cout << "  访问 arr[" << i << "]" << endl;
    } else {
        cout << "  i=" << i << " 越界，短路保护未访问 arr[i]" << endl;
    }
    cout << endl;
}

// ==================== 演示4：位运算符基础 ====================
void demo04_bitwise_basic() {
    print_title("演示4：位运算符 & | ^ ~ << >>");

    int m = 5, n = 3;
    cout << "m = " << m << " 二进制 " << bitset<8>(m) << endl;
    cout << "n = " << n << " 二进制 " << bitset<8>(n) << endl;
    cout << endl;
    cout << "m & n = " << (m & n) << "  " << bitset<8>(m & n) << "  按位与" << endl;
    cout << "m | n = " << (m | n) << "  " << bitset<8>(m | n) << "  按位或" << endl;
    cout << "m ^ n = " << (m ^ n) << "  " << bitset<8>(m ^ n) << "  按位异或" << endl;
    cout << "~m    = " << (~m) << "  (补码，32位全取反)" << endl;
    cout << "m << 1 = " << (m << 1) << "  (= m*2)" << endl;
    cout << "m << 2 = " << (m << 2) << "  (= m*4)" << endl;
    cout << "m >> 1 = " << (m >> 1) << "  (= m/2)" << endl;
    cout << "m >> 2 = " << (m >> 2) << endl;

    cout << endl << "移位与乘除对照 (正数):" << endl;
    for (int k = 0; k <= 4; k++) {
        int v = 3;
        cout << "  3 << " << k << " = " << (v << k)
             << ", 3 * 2^" << k << " = " << (3 * (1 << k)) << endl;
    }

    cout << endl << "大移位请用 1LL:" << endl;
    cout << "  1LL << 40 = " << (1LL << 40) << endl;
    cout << endl;
}

// ==================== 演示5：位运算经典技巧 ====================
void demo05_bitwise_tricks() {
    print_title("演示5：位运算经典技巧");

    cout << "1) n & 1 判断奇偶:" << endl;
    for (int i = 1; i <= 8; i++) {
        cout << "  " << i << ((i & 1) ? "(奇)" : "(偶)");
    }
    cout << endl;

    cout << endl << "2) 异或交换 (a、b 必须是不同变量):" << endl;
    int A = 10, B = 20;
    cout << "  交换前 A=" << A << " B=" << B << endl;
    A ^= B;
    B ^= A;
    A ^= B;
    cout << "  交换后 A=" << A << " B=" << B << endl;

    cout << endl << "3) 取第 k 位 (n >> k) & 1, n=13=1101:" << endl;
    int val = 13;
    cout << "  二进制: " << bitset<4>(val) << endl;
    for (int k = 3; k >= 0; k--) {
        cout << "  第" << k << "位: " << ((val >> k) & 1) << endl;
    }

    cout << endl << "4) 置位 / 清零 / 翻转 第 k 位:" << endl;
    int n = 0;
    n |= (1 << 2);   // 置第2位 → 4
    cout << "  置第2位: " << n << " " << bitset<8>(n) << endl;
    n |= (1 << 0);   // 再置第0位 → 5
    cout << "  置第0位: " << n << " " << bitset<8>(n) << endl;
    n &= ~(1 << 2);  // 清第2位 → 1
    cout << "  清第2位: " << n << " " << bitset<8>(n) << endl;
    n ^= (1 << 3);   // 翻第3位 → 9
    cout << "  翻第3位: " << n << " " << bitset<8>(n) << endl;

    cout << endl << "5) 判断 2 的幂: n>0 && (n & (n-1))==0" << endl;
    for (int i = 1; i <= 16; i++) {
        if ((i & (i - 1)) == 0) {
            cout << "  " << i << " 是 2 的幂" << endl;
        }
    }

    cout << endl << "6) lowbit = n & -n (最低位的1):" << endl;
    int lb_n = 12;  // 1100
    cout << "  n=12 " << bitset<8>(lb_n)
         << " lowbit=" << (lb_n & -lb_n) << endl;
    cout << endl;
}

// ==================== 演示6：三目运算符 ====================
void demo06_ternary() {
    print_title("演示6：三目运算符 ?:");

    int score = 85;
    cout << "成绩 score = " << score << endl;
    string result = (score >= 60) ? "及格" : "不及格";
    cout << "基本: " << result << endl;

    char grade = (score >= 90) ? 'A' :
                 (score >= 80) ? 'B' :
                 (score >= 70) ? 'C' :
                 (score >= 60) ? 'D' : 'E';
    cout << "嵌套等级: " << grade << "  (右结合)" << endl;

    int v1 = 15, v2 = 25;
    int maxVal = (v1 > v2) ? v1 : v2;
    int minVal = (v1 < v2) ? v1 : v2;
    cout << "max(" << v1 << "," << v2 << ") = " << maxVal << endl;
    cout << "min(" << v1 << "," << v2 << ") = " << minVal << endl;

    int neg = -10;
    int absVal = (neg >= 0) ? neg : -neg;
    cout << "|" << neg << "| = " << absVal << endl;

    int odd = 7;
    cout << odd << " 是 " << ((odd & 1) ? "奇数" : "偶数") << endl;

    // 结合性说明
    cout << endl << "右结合: a?b:c?d:e 等价于 a?b:(c?d:e)" << endl;
    int a = 0, b = 1, c = 1, d = 2, e = 3;
    int r = a ? b : c ? d : e;
    cout << "  0?1:1?2:3 = " << r << "  (走 c?d:e → 2)" << endl;
    cout << endl;
}

// ==================== 演示7：混合表达式与优先级 ====================
void demo07_mixed() {
    print_title("演示7：关系/逻辑/位 混合与括号");

    int a = 3, b = 5, c = 2;
    cout << "a=3,b=5,c=2" << endl;
    cout << "(a < b) && (b > c) = " << ((a < b) && (b > c)) << endl;
    cout << "a || b && c 注意: && 优先于 ||" << endl;
    cout << "  a||b&&c 值(非0作真) 逻辑结果 = "
         << (a || b && c) << endl;

    cout << endl << "位运算请加括号:" << endl;
    int x = 5, y = 3;
    cout << "  (x & y) && (x > 0) = " << ((x & y) && (x > 0)) << endl;
    cout << "  (x & y) ? (x << 1) : (y << 1) = "
         << ((x & y) ? (x << 1) : (y << 1)) << endl;

    cout << endl << "浮点比较:" << endl;
    double d1 = 0.1 + 0.2;
    double d2 = 0.3;
    cout << "  0.1+0.2 == 0.3 ? " << (d1 == d2) << endl;
    cout << "  fabs 比较: " << (fabs(d1 - d2) < 1e-9) << endl;
    cout << endl;
}

// ==================== 真题1 ====================
void exam01_short_circuit() {
    print_title("真题1：逻辑短路 AC 验证");
    cout << "代码: a=0,b=0; if(a++ && b++) a++; cout<<a<<' '<<b;" << endl;
    cout << "预期: 1 0" << endl;
    int a = 0, b = 0;
    if (a++ && b++) {
        a++;
    }
    cout << "实际: " << a << " " << b << endl;
    cout << endl;
}

// ==================== 真题2 ====================
void exam02_bit_ternary() {
    print_title("真题2：位运算+三目 AC 验证");
    cout << "x=5,y=3; z=(x&y)?(x<<1):(y<<1);" << endl;
    cout << "x&y=1 真 → z=x<<1=10" << endl;
    int x = 5, y = 3;
    int z = (x & y) ? (x << 1) : (y << 1);
    cout << "实际 z = " << z << endl;
    cout << "辅助: x&y=" << (x & y) << ", x<<1=" << (x << 1) << endl;
    cout << endl;
}

// ==================== 真题3 拓展 ====================
void exam03_short_circuit_plus() {
    print_title("真题3拓展：短路综合");
    int a = 1, b = 2, c = 3;
    int r1 = a < b && b < c;
    int r2 = a > b || b < c;
    int x = 0, y = 5;
    int r3 = x && (y = 100);
    cout << "r1=" << r1 << " r2=" << r2 << " r3=" << r3
         << " y(在r3后)=" << y << endl;
    int r4 = x || (y = 100);
    cout << "r4=" << r4 << " y(在r4后)=" << y << endl;
    cout << "整行输出: " << r1 << " " << r2 << " " << r3 << " "
         << y << " " << r4 << "  (预期 1 1 0 100 1)" << endl;
    cout << endl;
}

// ==================== 真题4 奇偶与2的幂 ====================
void exam04_odd_power2() {
    print_title("真题4拓展：奇偶与2的幂（固定样例）");
    long long samples[] = {1, 2, 3, 8};
    int n = 4;
    cout << "输入 n=4 及 1 2 3 8" << endl;
    cout << "输出:" << endl;
    for (int i = 0; i < n; i++) {
        long long x = samples[i];
        if (x & 1) {
            cout << "odd";
        } else {
            cout << "even";
        }
        if (x > 0 && (x & (x - 1)) == 0) {
            cout << " power2";
        }
        cout << endl;
    }
    cout << endl;
}

void run_all() {
    demo01_relational();
    demo02_logic_truth();
    demo03_short_circuit();
    demo04_bitwise_basic();
    demo05_bitwise_tricks();
    demo06_ternary();
    demo07_mixed();
    exam01_short_circuit();
    exam02_bit_ternary();
    exam03_short_circuit_plus();
    exam04_odd_power2();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int choice;
    do {
        cout << "========================================" << endl;
        cout << "  CSP-J 第6课：运算符与表达式（下）" << endl;
        cout << "========================================" << endl;
        cout << " 1. 关系运算符" << endl;
        cout << " 2. 逻辑运算真值表" << endl;
        cout << " 3. 短路特性（重点）" << endl;
        cout << " 4. 位运算符基础" << endl;
        cout << " 5. 位运算经典技巧" << endl;
        cout << " 6. 三目运算符" << endl;
        cout << " 7. 混合表达式与优先级" << endl;
        cout << " 8. 真题1：逻辑短路 AC" << endl;
        cout << " 9. 真题2：位运算+三目 AC" << endl;
        cout << "10. 真题3：短路综合" << endl;
        cout << "11. 真题4：奇偶与2的幂" << endl;
        cout << "12. 运行全部演示" << endl;
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
            case 1: demo01_relational(); break;
            case 2: demo02_logic_truth(); break;
            case 3: demo03_short_circuit(); break;
            case 4: demo04_bitwise_basic(); break;
            case 5: demo05_bitwise_tricks(); break;
            case 6: demo06_ternary(); break;
            case 7: demo07_mixed(); break;
            case 8: exam01_short_circuit(); break;
            case 9: exam02_bit_ternary(); break;
            case 10: exam03_short_circuit_plus(); break;
            case 11: exam04_odd_power2(); break;
            case 12: run_all(); break;
            default:
                cout << "无效选项，请重新选择。" << endl << endl;
        }
    } while (choice != 0);

    return 0;
}
