/*
 * CSP-J 备考课程
 * 第17课：函数的定义与调用
 *
 * 对照讲义覆盖：
 *  一、为什么需要函数（复用 / 模块化 / 可维护）
 *  二、函数定义四要素（返回类型 / 函数名 / 参数列表 / 函数体）
 *  三、函数声明与定义的分离
 *  四、函数调用机制（压栈 / 跳转 / 执行 / 返回）——说明性输出
 *  五、返回值的几种使用模式
 *  六、void 函数（含提前 return）
 *  七、main 函数的特殊地位
 *  八、函数设计原则（单一职责、命名规范）
 *  代码模板一：多函数完整组织
 *  代码模板二：数字操作函数集
 *  真题：统计素数个数、完美数检测
 *
 * 编译：g++ -std=c++17 lesson17_函数的定义与调用.cpp -o lesson17
 * 运行：./lesson17（自带示例数据，无需交互）
 */

#include <iostream>
#include <string>
using namespace std;

// ============================================================
//  函数声明（原型）—— 集中放在文件开头，相当于程序"目录"
// ============================================================

// ---------- 分隔与排版辅助 ----------
void printBanner(const string& title);
void printLine(char ch, int len);
void printSectionEnd();

// ---------- 基础运算（演示返回类型与多参数） ----------
int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
int square(int x);
int max2(int a, int b);
int max3(int a, int b, int c);
double average2(int a, int b);

// ---------- 判断类（bool 返回） ----------
bool isEven(int n);
bool isPrime(int n);
bool isPerfect(int n);
bool isPalindrome(int n);

// ---------- 数字操作 ----------
int sumOfDigits(int n);
int reverseNumber(int n);
int countDigits(int n);
long long factorial(int n);
int sumOfDivisors(int x);  // 除自身外正因子之和

// ---------- void 输出类 ----------
void sayHello();
void printHello();
void greet(int hour);
void printArray(int arr[], int n);
void printArrayLabeled(const string& label, int arr[], int n);

// ---------- 带过程说明的调用演示 ----------
int addWithTrace(int a, int b);
int max2WithTrace(int a, int b);

// ---------- 演示调度函数 ----------
void demo1_whyNeedFunctions();
void demo2_fourElements();
void demo3_declarationAndDefinition();
void demo4_callMechanism();
void demo5_returnValuePatterns();
void demo6_voidFunctions();
void demo7_mainSpecialStatus();
void demo8_designPrinciples();
void demo9_templateMultiFunctions();
void demo10_templateDigitOps();
void demo11_problemPrimeCount();
void demo12_problemPerfectNumber();

// ============================================================
//  main —— 程序唯一入口，只负责调度各 demo
// ============================================================
int main() {
    printBanner("第17课：函数的定义与调用 —— 完整演示");

    demo1_whyNeedFunctions();
    demo2_fourElements();
    demo3_declarationAndDefinition();
    demo4_callMechanism();
    demo5_returnValuePatterns();
    demo6_voidFunctions();
    demo7_mainSpecialStatus();
    demo8_designPrinciples();
    demo9_templateMultiFunctions();
    demo10_templateDigitOps();
    demo11_problemPrimeCount();
    demo12_problemPerfectNumber();

    printBanner("全部演示结束");
    return 0;  // 返回 0 表示正常退出（建议显式写出）
}

// ============================================================
//  演示 1：为什么需要函数（讲义 §一）
// ============================================================
void demo1_whyNeedFunctions() {
    printBanner("演示1：为什么需要函数");

    cout << "【没有函数时】判断素数的逻辑要写多遍，冗长且易错。\n";
    cout << "【有了函数后】写一次 isPrime，可在多处复用：\n\n";

    int samples[] = {17, 29, 1, 2, 15, 97};
    int n = sizeof(samples) / sizeof(samples[0]);
    for (int i = 0; i < n; i++) {
        int x = samples[i];
        // 复用同一个函数，体现"写一次，多次调用"
        cout << "  isPrime(" << x << ") -> "
             << (isPrime(x) ? "YES" : "NO") << endl;
    }

    cout << "\n三大好处：\n";
    cout << "  1. 代码复用：修改逻辑只需改一处\n";
    cout << "  2. 模块化：复杂问题拆成小函数\n";
    cout << "  3. 可维护性：结构清晰，便于调试\n";
    printSectionEnd();
}

// ============================================================
//  演示 2：函数定义四要素（讲义 §二）
// ============================================================
void demo2_fourElements() {
    printBanner("演示2：函数定义四要素");

    cout << "完整形式：返回类型  函数名  (参数列表) { 函数体 }\n\n";

    // 要素一：返回类型
    cout << "【要素一：返回类型】\n";
    cout << "  int    add(3,5)      = " << add(3, 5) << endl;
    cout << "  bool   isEven(8)     = " << (isEven(8) ? "true" : "false") << endl;
    cout << "  double average2(3,5) = " << average2(3, 5) << endl;
    cout << "  long long 5!         = " << factorial(5) << endl;
    cout << "  void   printHello()  无返回值，只执行动作：\n    ";
    printHello();

    // 返回类型与 return 表达式应匹配
    cout << "\n  注意：返回类型应与 return 表达式匹配。\n";
    cout << "  若 int 函数 return 3.14，小数会被截断（隐式转换）。\n";

    // 要素二：函数名
    cout << "\n【要素二：函数名】\n";
    cout << "  好的命名（动词/动词短语，驼峰）：\n";
    cout << "    isPrime / getMax / sumOfDigits / printArray\n";
    cout << "  不好的命名：\n";
    cout << "    f / check / doIt  —— 含义含糊\n";

    // 要素三：参数列表
    cout << "\n【要素三：参数列表】\n";
    cout << "  无参数：  sayHello()\n    ";
    sayHello();
    cout << "  一个参数：square(7) = " << square(7) << endl;
    cout << "  两个参数：max2(10, 25) = " << max2(10, 25) << endl;
    cout << "  三个参数：max3(10, 25, 18) = " << max3(10, 25, 18) << endl;
    cout << "  形参 = 定义时的参数名；实参 = 调用时传入的具体值\n";

    // 要素四：函数体
    cout << "\n【要素四：函数体】\n";
    cout << "  用 {} 包裹；非 void 函数每条路径都应有 return。\n";
    cout << "  执行到 return 立即结束，并把值交给调用者。\n";
    cout << "  示例：factorial(6) = " << factorial(6) << endl;
    printSectionEnd();
}

// ============================================================
//  演示 3：声明与定义分离（讲义 §三）
// ============================================================
void demo3_declarationAndDefinition() {
    printBanner("演示3：函数声明与定义的分离");

    cout << "【声明（原型）】只写返回类型、函数名、参数列表，以分号结尾。\n";
    cout << "  例如：int add(int a, int b);\n\n";
    cout << "【定义】写出完整函数体。\n";
    cout << "  例如：int add(int a, int b) { return a + b; }\n\n";

    cout << "C++ 从上到下编译。若 main 调用 add，则 add 须先声明或先定义。\n";
    cout << "推荐组织方式：\n";
    cout << "  1) 文件开头集中写全部声明（目录感）\n";
    cout << "  2) main 中调用\n";
    cout << "  3) main 之后写全部定义\n\n";

    cout << "本文件正是这种组织。验证调用：\n";
    cout << "  add(3, 5)      = " << add(3, 5) << endl;
    cout << "  subtract(10,4) = " << subtract(10, 4) << endl;
    cout << "  multiply(6, 7) = " << multiply(6, 7) << endl;

    cout << "\n【易错】声明与定义返回类型/参数类型必须一致：\n";
    cout << "  声明 int getValue();  定义 double getValue()  —— 错误\n";
    cout << "【易错】声明末尾必须有分号；定义用 {}，末尾无分号要求。\n";
    printSectionEnd();
}

// ============================================================
//  演示 4：函数调用机制（讲义 §四）
// ============================================================
void demo4_callMechanism() {
    printBanner("演示4：函数调用机制（压栈/跳转/执行/返回）");

    cout << "调用过程四个步骤：\n";
    cout << "  1. 压栈：实参副本 + 返回地址 进入调用栈\n";
    cout << "  2. 跳转：跳到被调函数入口\n";
    cout << "  3. 执行：在函数体中运算（形参是实参的副本）\n";
    cout << "  4. 返回：保存返回值，弹栈，回到调用处下一条语句\n\n";

    cout << "【跟踪示例】int z = addWithTrace(3, 5);\n";
    int z = addWithTrace(3, 5);
    cout << "main 收到返回值 z = " << z << endl;

    cout << "\n【图解概念】\n";
    cout << "  main: x=3, y=5, z=add(3,5)\n";
    cout << "           |\n";
    cout << "           v  压栈：a=3, b=5, 返回地址\n";
    cout << "         add  计算 a+b=8\n";
    cout << "           |\n";
    cout << "           v  返回 8，弹栈\n";
    cout << "  main: z=8，继续执行\n";

    cout << "\n核心概念（为第18课值传递铺垫）：\n";
    cout << "  形参得到的是实参的副本，函数内修改形参不影响外部变量。\n";

    cout << "\n【嵌套调用时的栈】max3 内部会再调 max2：\n";
    cout << "  max3(10, 25, 18) = " << max3(10, 25, 18) << endl;
    cout << "  等价于 max2(max2(10,25), 18)\n";
    printSectionEnd();
}

// ============================================================
//  演示 5：返回值使用模式（讲义 §五）
// ============================================================
void demo5_returnValuePatterns() {
    printBanner("演示5：返回值的几种使用模式");

    // 模式一：直接使用
    cout << "【模式一：直接使用】\n";
    cout << "  cout << max2(10, 20)  =>  " << max2(10, 20) << endl;

    // 模式二：赋值给变量
    cout << "\n【模式二：赋值给变量】\n";
    int result = max2(10, 20);
    cout << "  int result = max2(10, 20);  result = " << result << endl;

    // 模式三：作为条件判断
    cout << "\n【模式三：作为条件判断】\n";
    int n = 17;
    if (isPrime(n)) {
        cout << "  " << n << " 是素数" << endl;
    } else {
        cout << "  " << n << " 不是素数" << endl;
    }
    if (isEven(n)) {
        cout << "  " << n << " 是偶数" << endl;
    } else {
        cout << "  " << n << " 是奇数" << endl;
    }

    // 模式四：作为另一个函数的实参（嵌套调用）
    cout << "\n【模式四：作为另一函数的实参】\n";
    cout << "  max3(10, 20, 30) = "
         << max3(10, 20, 30) << endl;
    cout << "  max3(max2(10, 20), 15, 30) = "
         << max3(max2(10, 20), 15, 30) << endl;
    cout << "  isPalindrome(reverseNumber(12321)) = "
         << (isPalindrome(reverseNumber(12321)) ? "true" : "false") << endl;
    cout << "  square(add(2, 3)) = " << square(add(2, 3)) << endl;

    // 类型匹配
    cout << "\n【类型匹配规则】\n";
    cout << "  int 函数若 return 3.14 会截断为 3 —— 应改用 double\n";
    cout << "  bool 函数：非零表达式隐式为 true\n";
    cout << "  void 函数：不能 return 表达式，也不能把调用写进赋值/运算\n";
    printSectionEnd();
}

// ============================================================
//  演示 6：void 函数（讲义 §六）
// ============================================================
void demo6_voidFunctions() {
    printBanner("演示6：void 函数");

    cout << "void 函数不返回值，常用于打印、执行操作。\n\n";

    cout << "printLine('*', 20):\n";
    printLine('*', 20);

    cout << "printLine('-', 40):\n";
    printLine('-', 40);

    int arr[] = {1, 3, 5, 7, 9};
    cout << "printArray(arr, 5):\n  ";
    printArray(arr, 5);

    cout << "\n【提前 return】greet 根据小时分支，用 return 提前结束：\n";
    int hours[] = {3, 9, 14, 20};
    for (int i = 0; i < 4; i++) {
        cout << "  hour=" << hours[i] << " -> ";
        greet(hours[i]);
    }

    cout << "\nvoid 函数末尾可不写 return; 自然结束即相当于 return;\n";
    cout << "void 函数不能：int x = printHello();  —— 编译错误\n";
    cout << "void 中若需提前退出：写 return;  （不带值）\n";
    printSectionEnd();
}

// ============================================================
//  演示 7：main 的特殊地位（讲义 §七）
// ============================================================
void demo7_mainSpecialStatus() {
    printBanner("演示7：main 函数的特殊地位");

    cout << "main 是 C++ 程序唯一入口，由操作系统启动时调用。\n\n";
    cout << "特殊规则：\n";
    cout << "  1. 每个可执行程序必须有且仅有一个 main\n";
    cout << "  2. 返回类型必须是 int；0 正常，非 0 异常退出\n";
    cout << "  3. 程序中其他函数不应调用 main\n";
    cout << "  4. 合法形式：int main() 或 int main(int argc, char* argv[])\n";
    cout << "  5. 末尾 return 0; 可省略（编译器隐式添加），但建议写明\n\n";

    cout << "本程序的 main 只做调度：依次调用 demo1 ... demo12。\n";
    cout << "业务逻辑都在独立函数中，main 保持简洁 —— 这是良好习惯。\n";
    printSectionEnd();
}

// ============================================================
//  演示 8：函数设计原则（讲义 §八）
// ============================================================
void demo8_designPrinciples() {
    printBanner("演示8：函数设计原则（单一职责）");

    cout << "【不好】一个 process 同时判素数、算阶乘、求各位和、打印 —— 难测难改。\n";
    cout << "【好】每个函数只做一件事：\n\n";

    int n = 17;
    cout << "对 n = " << n << "：\n";
    cout << "  素数判断 isPrime:     " << (isPrime(n) ? "是" : "否") << endl;
    cout << "  阶乘     factorial:   " << factorial(n) << endl;
    cout << "  各位和   sumOfDigits: " << sumOfDigits(n) << endl;
    cout << "  位数     countDigits: " << countDigits(n) << endl;
    cout << "  是否偶数 isEven:      " << (isEven(n) ? "是" : "否") << endl;

    cout << "\n命名规范：\n";
    cout << "  动词开头：calculate / print / get / set\n";
    cout << "  布尔用 is / has：isPrime, isEven, hasDuplicates\n";
    cout << "  取值用 get 或名词：getMax, sumOfDigits, reverseNumber\n";
    cout << "  优先纯函数：只依赖参数、返回结果、不乱改外部状态\n";
    printSectionEnd();
}

// ============================================================
//  演示 9：模板一 —— 多函数完整组织（讲义代码模板一）
// ============================================================
void demo9_templateMultiFunctions() {
    printBanner("演示9：模板一 —— 多函数完整组织");

    cout << "对应讲义模板：isPrime / max2 / max3 / printArray\n\n";

    int x = 17;
    cout << x << (isPrime(x) ? " 是素数" : " 不是素数") << endl;
    cout << "max(10, 25) = " << max2(10, 25) << endl;
    cout << "max(10, 25, 18) = " << max3(10, 25, 18) << endl;

    int arr[] = {1, 3, 5, 7, 9};
    printArrayLabeled("数组内容", arr, 5);

    // 扩展一组测试
    cout << "\n扩展测试：\n";
    int more[] = {2, 4, 6, 8, 11, 13};
    for (int i = 0; i < 6; i++) {
        cout << "  " << more[i]
             << (isPrime(more[i]) ? " 素数" : " 合数/非素数") << endl;
    }
    cout << "  max3(-5, 0, 3) = " << max3(-5, 0, 3) << endl;
    cout << "  max3(100, max2(50, 80), 60) = "
         << max3(100, max2(50, 80), 60) << endl;
    printSectionEnd();
}

// ============================================================
//  演示 10：模板二 —— 数字操作函数集（讲义代码模板二）
// ============================================================
void demo10_templateDigitOps() {
    printBanner("演示10：模板二 —— 数字操作函数集");

    int nums[] = {12321, 12345, 7, 1001, 9876};
    int cnt = sizeof(nums) / sizeof(nums[0]);

    for (int i = 0; i < cnt; i++) {
        int num = nums[i];
        cout << "数字: " << num << endl;
        cout << "  各位数字之和: " << sumOfDigits(num) << endl;
        cout << "  反转后的数字: " << reverseNumber(num) << endl;
        cout << "  是否回文数:   " << (isPalindrome(num) ? "是" : "否") << endl;
        cout << "  位数:         " << countDigits(num) << endl;
        cout << endl;
    }

    cout << "说明：isPalindrome 复用 reverseNumber，体现函数协作。\n";
    printSectionEnd();
}

// ============================================================
//  演示 11：真题 —— 统计 1 到 n 的素数个数（讲义真题一）
// ============================================================
// 用内置数据模拟输入 n=20，期望输出 8
void demo11_problemPrimeCount() {
    printBanner("演示11：真题 —— 统计 1 到 n 的素数个数");

    // 样例数据（非交互）
    int n = 20;
    int cnt = 0;
    cout << "输入 n = " << n << "（样例）\n";
    cout << "1 到 " << n << " 的素数：";
    for (int i = 1; i <= n; i++) {
        if (isPrime(i)) {
            cout << i << " ";
            cnt++;
        }
    }
    cout << "\n素数个数 = " << cnt << "（期望 8）\n";

    // 再测几组
    int tests[] = {1, 2, 10, 30, 100};
    cout << "\n更多测试：\n";
    for (int t = 0; t < 5; t++) {
        int m = tests[t];
        int c = 0;
        for (int i = 1; i <= m; i++) {
            if (isPrime(i)) c++;
        }
        cout << "  [1, " << m << "] 素数个数 = " << c << endl;
    }
    printSectionEnd();
}

// ============================================================
//  演示 12：真题 —— 完美数检测（讲义真题二）
// ============================================================
void demo12_problemPerfectNumber() {
    printBanner("演示12：真题 —— 完美数检测");

    cout << "完美数：等于除自身外所有正因子之和。\n";
    cout << "例如 6 = 1+2+3，28 = 1+2+4+7+14。\n\n";

    int tests[] = {6, 10, 28, 100, 496, 8128, 12, 1};
    int cnt = sizeof(tests) / sizeof(tests[0]);
    for (int i = 0; i < cnt; i++) {
        int x = tests[i];
        cout << "  n=" << x
             << "  因子和(不含自身)=" << sumOfDivisors(x)
             << "  => " << (isPerfect(x) ? "YES" : "NO") << endl;
    }

    cout << "\n设计：sumOfDivisors 只算因子和，isPerfect 只做判断，\n";
    cout << "      符合「一个函数只做一件事」。\n";
    printSectionEnd();
}

// ============================================================
//  辅助：排版
// ============================================================
void printBanner(const string& title) {
    cout << "\n";
    printLine('=', 56);
    cout << "  " << title << endl;
    printLine('=', 56);
}

void printLine(char ch, int len) {
    for (int i = 0; i < len; i++) {
        cout << ch;
    }
    cout << endl;
}

void printSectionEnd() {
    printLine('-', 56);
    cout << endl;
}

// ============================================================
//  函数定义 —— 基础运算
// ============================================================
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

int square(int x) {
    return x * x;
}

int max2(int a, int b) {
    return a > b ? a : b;
}

int max3(int a, int b, int c) {
    // 嵌套调用 max2：体现函数协作与返回值作为实参
    return max2(max2(a, b), c);
}

double average2(int a, int b) {
    // 返回 double，注意先转浮点再除
    return (a + b) / 2.0;
}

// ============================================================
//  函数定义 —— 判断类
// ============================================================
bool isEven(int n) {
    return n % 2 == 0;
}

bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int sumOfDivisors(int x) {
    int sum = 0;
    // 除自身外的正因子
    for (int i = 1; i <= x / 2; i++) {
        if (x % i == 0) {
            sum += i;
        }
    }
    return sum;
}

bool isPerfect(int x) {
    if (x <= 1) return false;
    return x == sumOfDivisors(x);
}

bool isPalindrome(int n) {
    return n == reverseNumber(n);
}

// ============================================================
//  函数定义 —— 数字操作
// ============================================================
int sumOfDigits(int n) {
    if (n < 0) n = -n;
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int reverseNumber(int n) {
    // 仅处理非负；与讲义一致
    int rev = 0;
    while (n > 0) {
        rev = rev * 10 + n % 10;
        n /= 10;
    }
    return rev;
}

int countDigits(int n) {
    if (n < 0) n = -n;
    if (n == 0) return 1;
    int cnt = 0;
    while (n > 0) {
        cnt++;
        n /= 10;
    }
    return cnt;
}

long long factorial(int n) {
    long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

// ============================================================
//  函数定义 —— void 输出
// ============================================================
void sayHello() {
    cout << "Hello, CSP-J!" << endl;
}

void printHello() {
    cout << "Hello!" << endl;
}

void greet(int hour) {
    // 提前 return 的典型 void 用法
    if (hour < 6) {
        cout << "夜深了，早点休息！" << endl;
        return;
    }
    if (hour < 12) {
        cout << "早上好！" << endl;
        return;
    }
    if (hour < 18) {
        cout << "下午好！" << endl;
        return;
    }
    cout << "晚上好！" << endl;
    // 函数末尾可以不写 return;
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << " ";
    }
    cout << endl;
}

void printArrayLabeled(const string& label, int arr[], int n) {
    cout << label << ": ";
    printArray(arr, n);
}

// ============================================================
//  函数定义 —— 带调用过程说明（教学用）
// ============================================================
int addWithTrace(int a, int b) {
    cout << "  [压栈] 进入 add，形参 a=" << a << ", b=" << b << endl;
    cout << "  [执行] 计算 a + b ..." << endl;
    int ans = a + b;
    cout << "  [返回] 返回 " << ans << "，弹栈回调用者" << endl;
    return ans;
}

int max2WithTrace(int a, int b) {
    cout << "  [max2] 比较 " << a << " 与 " << b << endl;
    int ans = a > b ? a : b;
    cout << "  [max2] 较大者为 " << ans << endl;
    return ans;
}

/*
 * ==================== 易错点速查（讲义 ⚠️，注释说明，勿取消注释运行） ====================
 *
 * 1) 声明与定义类型不一致：
 *    int getValue();
 *    double getValue() { return 3.14; }  // 错误
 *
 * 2) 非 void 函数忘记 return：
 *    int max2(int a, int b) {
 *        if (a > b) cout << a << endl;  // 没有 return —— 未定义行为
 *    }
 *
 * 3) 声明忘记分号：
 *    int add(int a, int b)   // 缺 ;
 *    int main() { ... }
 *
 * 4) void 中 return 带值：
 *    void printMessage() {
 *        return 0;  // 错误
 *    }
 *
 * 5) 把 void 调用当表达式：
 *    int x = printHello();  // 编译错误
 */
