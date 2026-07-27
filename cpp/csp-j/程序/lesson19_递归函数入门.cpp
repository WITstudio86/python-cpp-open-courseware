/*
 * CSP-J 备考课程
 * 第19课：递归函数入门
 *
 * 对照讲义覆盖：
 *  1. 什么是递归（递与归、俄罗斯套娃、倒计时示例）
 *  2. 递归三要素（边界 / 关系式 / 参数收敛）
 *  3. 阶乘递归 + 调用栈可视化 + 迭代对比
 *  4. 斐波那契：朴素递归 / 记忆化 / 迭代 + 递归树说明
 *  5. 递归调用栈说明性输出
 *  6. 递归与迭代对比
 *  7. 递归思维训练：数字和、倒序输出、求位数、求和、幂
 *  代码模板：阶乘双写法、斐波那契三写法
 *  真题：递归求和、递归求位数
 *  易错点：错误递归示例（注释说明，不实际执行无限递归）
 *
 * 编译：g++ -std=c++17 lesson19_递归函数入门.cpp -o lesson19
 * 运行：./lesson19（自带示例数据，无需交互）
 */

#include <iostream>
#include <cstring>
#include <string>
using namespace std;

// ============================================================
//  全局：斐波那契记忆化数组
// ============================================================
const int MEMO_N = 100;
long long memo[MEMO_N];
long long callCountNaive = 0;   // 统计朴素递归调用次数
long long callCountMemo = 0;    // 统计记忆化递归调用次数

// ============================================================
//  声明
// ============================================================
void printBanner(const string& title);
void printLine(char ch, int len);
void printIndent(int depth);

// 倒计时（递与归）
void countdown(int n);
void countdownWithDepth(int n, int depth);

// 阶乘
long long factorialRecursive(int n);
long long factorialRecursiveTrace(int n, int depth);
long long factorialIterative(int n);

// 斐波那契三种实现（0-based：fib(0)=0, fib(1)=1）
long long fibNaive(int n);
long long fibNaiveCount(int n);          // 带调用计数
long long fibMemo(int n);
long long fibMemoCount(int n);
long long fibIterative(int n);
void printFibTreeExplanation(int n);

// 经典小递归
long long sumRecursive(int n);
int digitCount(int n);
int digitSum(int n);
void printDigitsReverse(int n);          // 倒序输出各位
void printDigitsForward(int n);          // 正序输出各位（先递归再输出）
long long powerRecursive(int base, int exp);
int gcdRecursive(int a, int b);
long long arraySumRecursive(const int arr[], int n);

// 演示调度
void demo1_whatIsRecursion();
void demo2_threeElements();
void demo3_factorial();
void demo4_fibonacci();
void demo5_callStack();
void demo6_recursionVsIteration();
void demo7_thinkingTraining();
void demo8_templates();
void demo9_problems();
void demo10_commonMistakes();

// ============================================================
//  main
// ============================================================
int main() {
    printBanner("第19课：递归函数入门 —— 完整演示");

    demo1_whatIsRecursion();
    demo2_threeElements();
    demo3_factorial();
    demo4_fibonacci();
    demo5_callStack();
    demo6_recursionVsIteration();
    demo7_thinkingTraining();
    demo8_templates();
    demo9_problems();
    demo10_commonMistakes();

    printBanner("全部演示结束");
    return 0;
}

// ============================================================
//  演示 1：什么是递归（讲义 §1）
// ============================================================
void demo1_whatIsRecursion() {
    printBanner("演示1：什么是递归");

    cout << "递归：函数在函数体内直接或间接调用自身。\n";
    cout << "「递」= 把问题交给更小规模的自己；「归」= 层层返回结果。\n";
    cout << "比喻：俄罗斯套娃 —— 一直打开到最小实心娃，再逐层装回。\n\n";

    cout << "【倒计时示例】countdown(3)\n";
    cout << "  递阶段输出 n，再调 countdown(n-1)；\n";
    cout << "  边界 n<=0 输出「发射！」；\n";
    cout << "  归阶段再输出 n（调用点之后的语句）。\n";
    cout << "实际输出：";
    countdown(3);
    cout << endl;
    cout << "期望形态：3 2 1 发射！ 1 2 3\n";

    cout << "\n【带缩进看清递与归】\n";
    countdownWithDepth(3, 0);
    printLine('-', 56);
    cout << endl;
}

// ============================================================
//  演示 2：递归三要素（讲义 §2）
// ============================================================
void demo2_threeElements() {
    printBanner("演示2：递归三要素");

    cout << "任何一个正确的递归函数必须同时具备：\n\n";

    cout << "【要素一：递归边界 Base Case】\n";
    cout << "  问题小到不能再分时的直接答案，是递归的「出口」。\n";
    cout << "  例：0! = 1；fib(0)=0, fib(1)=1；n<=0 停止倒计时。\n\n";

    cout << "【要素二：递归关系式 Recursive Relation】\n";
    cout << "  大问题答案如何由小问题答案推出。\n";
    cout << "  例：n! = n*(n-1)!；fib(n)=fib(n-1)+fib(n-2)。\n\n";

    cout << "【要素三：参数变化方向 Parameter Convergence】\n";
    cout << "  每次调用必须让参数更接近边界，否则无限递归。\n";
    cout << "  正确：factorial(n-1) 向 0 靠近。\n";
    cout << "  错误：bad(n+1) 永远到不了 n==0。\n\n";

    cout << "用阶乘验证三要素是否齐全：\n";
    for (int i = 0; i <= 6; i++) {
        cout << "  " << i << "! = " << factorialRecursive(i) << endl;
    }

    cout << "\n三要素是有机整体：缺边界→栈溢出；关系错→结果错；不收敛→栈溢出。\n";
    printLine('-', 56);
    cout << endl;
}

// ============================================================
//  演示 3：阶乘（讲义 §3 + 模板1）
// ============================================================
void demo3_factorial() {
    printBanner("演示3：阶乘的递归实现与调用栈跟踪");

    cout << "定义：0! = 1；n! = n * (n-1)! \n\n";

    cout << "【带缩进跟踪 factorial(5)】\n";
    long long ans = factorialRecursiveTrace(5, 0);
    cout << "最终结果：" << ans << endl;

    cout << "\n【ASCII 调用过程摘要】\n";
    cout << "  递：fact(5) 等待 fact(4) ... 等待 fact(0)\n";
    cout << "  归：fact(0)->1, fact(1)=1*1=1, fact(2)=2,\n";
    cout << "      fact(3)=6, fact(4)=24, fact(5)=120\n";
    cout << "  关键：递阶段都在「等待」；边界返回后才开始归并计算。\n";

    cout << "\n【递归 vs 迭代对照】\n";
    cout << "  n   递归       迭代\n";
    for (int i = 0; i <= 10; i++) {
        cout << "  " << i << "   "
             << factorialRecursive(i) << "\t  "
             << factorialIterative(i) << endl;
    }
    cout << "  时间都是 O(n)；递归额外 O(n) 栈空间，迭代 O(1) 空间。\n";
    printLine('-', 56);
    cout << endl;
}

// ============================================================
//  演示 4：斐波那契三种实现（讲义 §4 + 模板2）
// ============================================================
void demo4_fibonacci() {
    printBanner("演示4：斐波那契 —— 朴素 / 记忆化 / 迭代");

    cout << "定义：fib(0)=0, fib(1)=1；fib(n)=fib(n-1)+fib(n-2)\n\n";

    // 序列输出
    int showN = 15;
    cout << "前 " << showN << " 项（三种方法）：\n";
    cout << "  下标: ";
    for (int i = 0; i < showN; i++) cout << i << (i + 1 < showN ? " " : "\n");

    cout << "  朴素: ";
    for (int i = 0; i < showN; i++) cout << fibNaive(i) << (i + 1 < showN ? " " : "\n");

    memset(memo, -1, sizeof(memo));
    cout << "  记忆: ";
    for (int i = 0; i < showN; i++) cout << fibMemo(i) << (i + 1 < showN ? " " : "\n");

    cout << "  迭代: ";
    for (int i = 0; i < showN; i++) cout << fibIterative(i) << (i + 1 < showN ? " " : "\n");

    // 递归树说明
    cout << "\n";
    printFibTreeExplanation(5);

    // 调用次数对比：展示重复计算
    cout << "\n【调用次数对比】（直观感受重复计算）\n";
    for (int n = 5; n <= 12; n++) {
        callCountNaive = 0;
        long long v1 = fibNaiveCount(n);

        callCountMemo = 0;
        memset(memo, -1, sizeof(memo));
        long long v2 = fibMemoCount(n);

        cout << "  fib(" << n << ") = " << v1
             << "  | 朴素调用次数=" << callCountNaive
             << "  | 记忆化调用次数=" << callCountMemo
             << "  | 一致?" << (v1 == v2 ? "Y" : "N") << endl;
    }

    cout << "\n复杂度小结：\n";
    cout << "  朴素递归：时间 O(2^n)，空间 O(n)  —— n>40 极慢\n";
    cout << "  记忆化：  时间 O(n)，空间 O(n)\n";
    cout << "  迭代：    时间 O(n)，空间 O(1)\n";

    // 较大 n 只跑记忆化与迭代
    int big = 50;
    memset(memo, -1, sizeof(memo));
    cout << "\n  fib(" << big << ") 记忆化 = " << fibMemo(big) << endl;
    cout << "  fib(" << big << ") 迭代   = " << fibIterative(big) << endl;
    cout << "  （朴素对 n=50 过慢，跳过）\n";
    printLine('-', 56);
    cout << endl;
}

// ============================================================
//  演示 5：递归调用栈（讲义 §5）
// ============================================================
void demo5_callStack() {
    printBanner("演示5：递归调用栈可视化（factorial(3)）");

    cout << "每次调用压入一个栈帧（参数、局部变量、返回地址）；\n";
    cout << "返回时弹出。LIFO 正好匹配「后调用的先返回」。\n\n";

    cout << "【模拟栈帧变化】\n";
    cout << "main 调 fact(3):\n";
    cout << "  [栈] fact(n=3) | main\n";
    cout << "fact(3) 调 fact(2):\n";
    cout << "  [栈] fact(n=2) | fact(n=3)等待 | main\n";
    cout << "fact(2) 调 fact(1):\n";
    cout << "  [栈] fact(n=1) | fact(n=2) | fact(n=3) | main\n";
    cout << "fact(1) 调 fact(0):\n";
    cout << "  [栈] fact(n=0) | fact(1) | fact(2) | fact(3) | main\n";
    cout << "fact(0) 边界返回 1，弹栈\n";
    cout << "  fact(1)=1*1=1 弹栈\n";
    cout << "  fact(2)=2*1=2 弹栈\n";
    cout << "  fact(3)=3*2=6 弹栈，回到 main\n\n";

    cout << "【实际跟踪输出】\n";
    long long r = factorialRecursiveTrace(3, 0);
    cout << "结果 = " << r << endl;

    cout << "\n注意：默认栈空间有限（约数 MB），深度过万可能 Stack Overflow。\n";
    cout << "深度过大时改用迭代或显式 stack 模拟。\n";
    printLine('-', 56);
    cout << endl;
}

// ============================================================
//  演示 6：递归与迭代对比（讲义 §6）
// ============================================================
void demo6_recursionVsIteration() {
    printBanner("演示6：递归与迭代对比");

    cout << "维度对比：\n";
    cout << "  代码简洁性  递归贴近数学定义；迭代要维护循环变量\n";
    cout << "  可读性      树/图/分治用递归更自然；线性题迭代更直观\n";
    cout << "  时间        朴素递归可能指数级；迭代通常 O(n)\n";
    cout << "  空间        递归 O(深度)；迭代常 O(1)\n";
    cout << "  栈溢出      递归有风险；迭代无此问题\n\n";

    cout << "【同一问题对比】n=10\n";
    int n = 10;
    cout << "  阶乘：递归=" << factorialRecursive(n)
         << "  迭代=" << factorialIterative(n) << endl;
    cout << "  求和：递归=" << sumRecursive(n)
         << "  公式=" << n * (n + 1) / 2 << endl;
    cout << "  fib ：递归=" << fibNaive(n)
         << "  迭代=" << fibIterative(n) << endl;

    cout << "\n选择指南：\n";
    cout << "  - 树/图 DFS、分治、回溯 → 优先递归\n";
    cout << "  - 简单线性递推（阶乘、fib）→ 优先迭代\n";
    cout << "  - 深度可能 > 1e4~1e5 → 避免朴素递归\n";
    printLine('-', 56);
    cout << endl;
}

// ============================================================
//  演示 7：递归思维训练（讲义 §7）
// ============================================================
void demo7_thinkingTraining() {
    printBanner("演示7：递归思维训练（五步法 + 经典题）");

    cout << "五步法：找自相似 → 定最小答案 → 写关系式 → 信任子调用 → 验证收敛\n\n";

    // 数字各位和
    cout << "【1】各位数字之和 digitSum\n";
    cout << "  结构：digitSum(n) = n%10 + digitSum(n/10)，边界 n<10 返回 n\n";
    int dsTests[] = {0, 7, 123, 9999, 10001};
    for (int i = 0; i < 5; i++) {
        int x = dsTests[i];
        cout << "  digitSum(" << x << ") = " << digitSum(x) << endl;
    }

    // 倒序 / 正序输出数字
    cout << "\n【2】倒序输出各位 / 正序输出各位\n";
    int num = 12345;
    cout << "  原数 " << num << "\n  倒序：";
    printDigitsReverse(num);
    cout << "\n  正序：";
    printDigitsForward(num);
    cout << endl;

    // 位数
    cout << "\n【3】递归求位数 digitCount\n";
    int dcTests[] = {5, 42, 100, 9999, 123456789};
    for (int i = 0; i < 5; i++) {
        cout << "  digitCount(" << dcTests[i] << ") = "
             << digitCount(dcTests[i]) << endl;
    }

    // 求和
    cout << "\n【4】递归求和 sum(n)=n+sum(n-1)\n";
    cout << "  sum(5)   = " << sumRecursive(5) << "（期望 15）\n";
    cout << "  sum(100) = " << sumRecursive(100) << "（期望 5050）\n";

    // 幂
    cout << "\n【5】递归求幂 power(base, exp)\n";
    cout << "  2^0=" << powerRecursive(2, 0)
         << "  2^10=" << powerRecursive(2, 10)
         << "  3^5=" << powerRecursive(3, 5)
         << "  5^4=" << powerRecursive(5, 4) << endl;

    // 最大公约数（欧几里得）
    cout << "\n【6】欧几里得 gcd(a,b)=gcd(b,a%b)，边界 b==0 返回 a\n";
    cout << "  gcd(48,18) = " << gcdRecursive(48, 18) << endl;
    cout << "  gcd(100,35)= " << gcdRecursive(100, 35) << endl;
    cout << "  gcd(17,13) = " << gcdRecursive(17, 13) << endl;

    // 数组递归求和
    cout << "\n【7】数组和 = 首元素 + 剩余部分的和\n";
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int len = 10;
    cout << "  arr[0..9] 递归和 = " << arraySumRecursive(arr, len)
         << "（期望 55）\n";
    printLine('-', 56);
    cout << endl;
}

// ============================================================
//  演示 8：代码模板汇总（讲义 💻）
// ============================================================
void demo8_templates() {
    printBanner("演示8：代码模板汇总运行");

    cout << "=== 模板1：阶乘（递归 + 迭代）n=10 ===\n";
    int n = 10;
    cout << "  递归结果：" << factorialRecursive(n) << endl;
    cout << "  迭代结果：" << factorialIterative(n) << endl;

    cout << "\n=== 模板2：斐波那契三种实现 n=20 ===\n";
    int f = 20;
    memset(memo, -1, sizeof(memo));
    cout << "  朴素递归：fib(" << f << ") = " << fibNaive(f) << endl;
    cout << "  记忆化：  fib(" << f << ") = " << fibMemo(f) << endl;
    cout << "  迭代：    fib(" << f << ") = " << fibIterative(f) << endl;

    cout << "\n  n=35 时朴素仍可接受：\n";
    cout << "  朴素 fib(35) = " << fibNaive(35) << endl;
    memset(memo, -1, sizeof(memo));
    cout << "  记忆 fib(35) = " << fibMemo(35) << endl;
    cout << "  迭代 fib(35) = " << fibIterative(35) << endl;
    printLine('-', 56);
    cout << endl;
}

// ============================================================
//  演示 9：真题精练（讲义 📝）
// ============================================================
void demo9_problems() {
    printBanner("演示9：真题 —— 递归求和 / 递归求位数");

    // 题目1：递归求和
    cout << "【题目1】递归求 1+2+...+n（禁止循环与公式）\n";
    int sumCases[] = {5, 100, 1, 10};
    for (int i = 0; i < 4; i++) {
        int n = sumCases[i];
        cout << "  n=" << n << " -> " << sumRecursive(n)
             << "（校验 " << (long long)n * (n + 1) / 2 << "）\n";
    }
    cout << "  复杂度：时间 O(n)，空间 O(n)。n 很大时可能栈溢出，应改迭代。\n";

    // 题目2：递归求位数
    cout << "\n【题目2】递归求十进制位数\n";
    int digCases[] = {12345, 100, 1, 9, 10, 999999999};
    for (int i = 0; i < 6; i++) {
        int n = digCases[i];
        cout << "  n=" << n << " -> 位数 " << digitCount(n) << endl;
    }
    cout << "  复杂度：时间/空间 O(log n)，n<=1e9 最多约 10 层，安全。\n";

    // 变式：二进制中 1 的个数（讲义思考题）
    cout << "\n【变式】二进制 1 的个数：countOne(n)=(n&1)+countOne(n>>1)，边界 n==0\n";
    // 用局部 lambda 风格手写等价函数逻辑的小循环演示期望值
    // 这里直接写一个局部递归函数（C++ 不允许嵌套函数，故用预先定义的辅助思路内联演示）
    // 为保持模块清晰，用迭代校验 + 说明递归式
    int binTests[] = {0, 1, 2, 3, 7, 8, 255, 1023};
    for (int i = 0; i < 8; i++) {
        int x = binTests[i];
        int cnt = 0;
        int t = x;
        // 与递归式等价的迭代验证
        while (t > 0) {
            cnt += (t & 1);
            t >>= 1;
        }
        cout << "  countOne(" << x << ") 期望 = " << cnt << endl;
    }
    printLine('-', 56);
    cout << endl;
}

// ============================================================
//  演示 10：易错点（讲义 ⚠️）—— 错误代码仅注释，正确代码可运行
// ============================================================
void demo10_commonMistakes() {
    printBanner("演示10：易错点说明（错误代码不执行）");

    cout << "【易错1】忘记递归边界\n";
    cout << "  // int bad(int n) { return n * bad(n-1); }  // 永不停止\n";
    cout << "  正确：先写 if (n==0) return 1;\n";
    cout << "  验证正确 factorial(5) = " << factorialRecursive(5) << endl;

    cout << "\n【易错2】参数未向边界收敛\n";
    cout << "  // return bad(n+1);  // 边界 n==0，却递增，永远到不了\n";
    cout << "  // 边界 n>100 却写 bad(n-1)  —— 方向反了\n";
    cout << "  正确：每次 n-1 或 n/10 等，确保逼近边界。\n";

    cout << "\n【易错3】返回值未向上传递\n";
    cout << "  // factorial(n-1);          // 调用了但丢弃返回值\n";
    cout << "  // n * factorial(n-1);      // 算了但没 return\n";
    cout << "  正确：return n * factorial(n-1);\n";

    cout << "\n【易错4】递归深度过大\n";
    cout << "  // dfs(100000) 可能栈溢出\n";
    cout << "  对策：改迭代；或手动 stack；检查数据范围。\n";

    cout << "\n【正确示例汇总】\n";
    cout << "  5!           = " << factorialRecursive(5) << endl;
    cout << "  fib(10)      = " << fibIterative(10) << endl;
    cout << "  sum(10)      = " << sumRecursive(10) << endl;
    cout << "  digitSum(99) = " << digitSum(99) << endl;
    cout << "  digitCount(1000) = " << digitCount(1000) << endl;

    cout << "\n编写口诀：边界在前 → 关系正确 → 参数收敛 → 结果 return。\n";
    printLine('-', 56);
    cout << endl;
}

// ============================================================
//  工具函数
// ============================================================
void printBanner(const string& title) {
    cout << "\n";
    printLine('=', 56);
    cout << "  " << title << endl;
    printLine('=', 56);
}

void printLine(char ch, int len) {
    for (int i = 0; i < len; i++) cout << ch;
    cout << endl;
}

void printIndent(int depth) {
    for (int i = 0; i < depth; i++) cout << "  ";
}

// ============================================================
//  倒计时：展示「递」与「归」
// ============================================================
void countdown(int n) {
    if (n <= 0) {
        cout << "发射！ ";
        return;
    }
    cout << n << " ";           // 递
    countdown(n - 1);
    cout << n << " ";           // 归
}

void countdownWithDepth(int n, int depth) {
    printIndent(depth);
    if (n <= 0) {
        cout << "depth=" << depth << " 边界：发射！" << endl;
        return;
    }
    cout << "depth=" << depth << " 递：输出 " << n << "，调用 countdown("
         << (n - 1) << ")" << endl;
    countdownWithDepth(n - 1, depth + 1);
    printIndent(depth);
    cout << "depth=" << depth << " 归：再次输出 " << n << endl;
}

// ============================================================
//  阶乘
// ============================================================
long long factorialRecursive(int n) {
    if (n == 0) return 1;                       // 边界
    return n * factorialRecursive(n - 1);       // 关系 + 收敛
}

long long factorialRecursiveTrace(int n, int depth) {
    printIndent(depth);
    cout << "开始 factorial(" << n << ")" << endl;

    if (n == 0) {
        printIndent(depth);
        cout << "边界 factorial(0) = 1" << endl;
        return 1;
    }

    long long sub = factorialRecursiveTrace(n - 1, depth + 1);
    long long result = n * sub;

    printIndent(depth);
    cout << "factorial(" << n << ") = " << n << " * " << sub
         << " = " << result << endl;
    return result;
}

long long factorialIterative(int n) {
    long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

// ============================================================
//  斐波那契
// ============================================================
long long fibNaive(int n) {
    if (n <= 1) return n;
    return fibNaive(n - 1) + fibNaive(n - 2);
}

long long fibNaiveCount(int n) {
    callCountNaive++;
    if (n <= 1) return n;
    return fibNaiveCount(n - 1) + fibNaiveCount(n - 2);
}

long long fibMemo(int n) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];
    return memo[n] = fibMemo(n - 1) + fibMemo(n - 2);
}

long long fibMemoCount(int n) {
    callCountMemo++;
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];
    return memo[n] = fibMemoCount(n - 1) + fibMemoCount(n - 2);
}

long long fibIterative(int n) {
    if (n <= 1) return n;
    long long a = 0, b = 1, c = 0;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

void printFibTreeExplanation(int n) {
    cout << "【fib(" << n << ") 递归树示意（朴素，存在重复子问题）】\n";
    if (n == 5) {
        cout << "                  fib(5)\n";
        cout << "                 /      \\\n";
        cout << "            fib(4)      fib(3)\n";
        cout << "           /     \\      /     \\\n";
        cout << "       fib(3)  fib(2) fib(2) fib(1)\n";
        cout << "       /    \\   /   \\   /   \\\n";
        cout << "   fib(2) fib(1) ...  大量重复！\n";
        cout << "  观察：fib(3) 算了多次，fib(2) 更多 —— 指数爆炸根源。\n";
    } else {
        cout << "  fib(" << n << ") 分裂为 fib(" << (n - 1) << ") 与 fib("
             << (n - 2) << ")，形成二叉树状调用。\n";
    }
}

// ============================================================
//  经典小递归
// ============================================================
long long sumRecursive(int n) {
    if (n == 1) return 1;                    // 边界（n>=1）
    return n + sumRecursive(n - 1);
}

int digitCount(int n) {
    if (n < 0) n = -n;
    if (n < 10) return 1;                    // 一位数
    return 1 + digitCount(n / 10);
}

int digitSum(int n) {
    if (n < 0) n = -n;
    if (n < 10) return n;
    return (n % 10) + digitSum(n / 10);
}

// 倒序：先输出个位，再递归前缀 —— 递阶段输出
void printDigitsReverse(int n) {
    if (n < 0) {
        cout << "-";
        n = -n;
    }
    if (n < 10) {
        cout << n;
        return;
    }
    cout << (n % 10) << " ";
    printDigitsReverse(n / 10);
}

// 正序：先递归前缀，再输出个位 —— 归阶段输出
void printDigitsForward(int n) {
    if (n < 0) {
        cout << "-";
        n = -n;
    }
    if (n < 10) {
        cout << n;
        return;
    }
    printDigitsForward(n / 10);
    cout << " " << (n % 10);
}

long long powerRecursive(int base, int exp) {
    if (exp == 0) return 1;
    return base * powerRecursive(base, exp - 1);
}

int gcdRecursive(int a, int b) {
    if (b == 0) return a;
    return gcdRecursive(b, a % b);
}

// 数组前 n 个元素之和：sum = arr[n-1] + sum(前 n-1 个)
long long arraySumRecursive(const int arr[], int n) {
    if (n <= 0) return 0;
    if (n == 1) return arr[0];
    return arr[n - 1] + arraySumRecursive(arr, n - 1);
}

/*
 * ==================== 错误递归示例（仅注释，切勿取消注释运行） ====================
 *
 * // 1. 无边界 —— 栈溢出
 * int factorial_wrong(int n) {
 *     return n * factorial_wrong(n - 1);
 * }
 *
 * // 2. 参数背离边界
 * int wrong_converge(int n) {
 *     if (n == 0) return 1;
 *     return n * wrong_converge(n + 1);  // 应 n-1
 * }
 *
 * // 3. 方向错误
 * int wrong_direction(int n) {
 *     if (n > 100) return n;
 *     return wrong_direction(n - 1);     // n 变小永远到不了 >100
 * }
 *
 * // 4. 丢弃返回值
 * int factorial_no_return(int n) {
 *     if (n == 0) return 1;
 *     factorial_no_return(n - 1);        // 未 return
 * }
 *
 * // 5. 算了却不 return
 * int factorial_forgot_return(int n) {
 *     if (n == 0) return 1;
 *     n * factorial_forgot_return(n - 1);
 * }
 *
 * // 6. 深度过大
 * void dfs_too_deep(int n) {
 *     if (n == 0) return;
 *     dfs_too_deep(n - 1);
 * }
 * // main 中 dfs_too_deep(100000);  // 可能崩溃
 */
