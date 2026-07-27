/*
 * CSP-J 备考课程
 * 第2课：C++编程环境与第一个程序
 * 考纲知识点：Dev-C++/CodeBlocks 使用、程序基本结构、
 *           #include / main / return、编译运行四步骤、注释
 *
 * 本文件演示清单：
 * 1. demoProgramSkeleton     —— 最小程序骨架说明性输出
 * 2. demoHelloWorld          —— Hello World 与多行输出
 * 3. demoIncludeAndNamespace —— 头文件与 std 命名空间
 * 4. demoCoutBasics          —— cout 链式输出与表达式
 * 5. demoEscapeChars         —— 转义字符
 * 6. demoComments            —— 单行/多行注释效果
 * 7. demoDebugPrint          —— 调试输出技巧
 * 8. demoCompilePipeline     —— 四步骤概念文字演示
 * 9. demoCommonMistakes      —— 易错点对照（正确写法演示）
 * 10. demoExamProblems       —— 讲义真题输出验证
 * 11. demoTemplateStyle      —— 竞赛模板风格示意
 */

#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>
using namespace std;

// ==================== 工具 ====================

void printBanner(const string &title) {
    cout << "\n========================================" << endl;
    cout << "  " << title << endl;
    cout << "========================================" << endl;
}

void printLine() {
    cout << "----------------------------------------" << endl;
}

// ==================== 1. 程序骨架 ====================

void demoProgramSkeleton() {
    printBanner("1. 程序基本结构要素");

    cout << "一个可评分的 C++ 程序通常包含：" << endl;
    cout << "  (1) #include <iostream>   —— 引入输入输出" << endl;
    cout << "  (2) using namespace std;  —— 使用标准命名空间" << endl;
    cout << "  (3) int main() { ... }   —— 唯一入口" << endl;
    cout << "  (4) cout / 计算逻辑       —— 题目功能" << endl;
    cout << "  (5) return 0;            —— 正常结束" << endl;

    printLine();
    cout << "当前函数本身就运行在 main 调用链中，说明：" << endl;
    cout << "  操作系统从 main 开始执行，再调用各个 demo 函数。" << endl;
}

// ==================== 2. Hello World ====================

void demoHelloWorld() {
    printBanner("2. Hello World 与多行输出");

    cout << "Hello, CSP-J!" << endl;
    cout << "Welcome to C++ programming." << endl;

    // 一次 cout 输出多行
    cout << "Line1\nLine2\nLine3" << endl;

    // 拼接多个字符串字面量（编译期相邻合并也可，这里用流）
    cout << "I " << "love " << "OI!" << endl;
}

// ==================== 3. 头文件与命名空间 ====================

void demoIncludeAndNamespace() {
    printBanner("3. 头文件与命名空间示意");

    cout << "本文件已包含的标准头（示例用途）：" << endl;
    cout << "  <iostream>  → cout/cin" << endl;
    cout << "  <cstdio>    → printf/scanf（本 demo 用 printf 演示）" << endl;
    cout << "  <cmath>     → sqrt 等" << endl;
    cout << "  <algorithm> → max/min/sort 等" << endl;
    cout << "  <string>    → string 类型" << endl;

    // 使用 cstdio
    printf("  printf 演示: %d + %d = %d\n", 3, 4, 3 + 4);

    // 使用 cmath
    cout << "  sqrt(16) = " << sqrt(16.0) << endl;

    // 使用 algorithm
    cout << "  max(7, 9) = " << max(7, 9) << endl;

    // 使用 string
    string s = "CSP-J";
    cout << "  string s = \"" << s << "\", 长度 = " << s.size() << endl;

    cout << "\n不用 using 时需写 std:: 前缀，例如：" << endl;
    std::cout << "  std::cout 仍然可用（即使有 using）" << std::endl;
}

// ==================== 4. cout 基础 ====================

void demoCoutBasics() {
    printBanner("4. cout 链式输出与表达式");

    int a = 10, b = 20;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "a + b = " << a + b << endl;
    cout << "a * b = " << a * b << endl;

    // 表达式优先级：先算再输出
    cout << "2 + 3 * 4 = " << 2 + 3 * 4 << endl; // 14
    cout << "(2 + 3) * 4 = " << (2 + 3) * 4 << endl; // 20

    // 连续输出不同类型
    char ch = 'X';
    double pi = 3.14;
    cout << "混合输出: " << ch << ", " << pi << ", " << 100 << endl;

    // endl 与 \n
    cout << "使用 endl 换行" << endl;
    cout << "使用 \\n 换行\n";
    cout << "(上一行已换行)" << endl;
}

// ==================== 5. 转义字符 ====================

void demoEscapeChars() {
    printBanner("5. 常用转义字符");

    cout << "换行符 \\n : 下一行是空行\n" << endl;
    cout << "制表符 \\t :\t列1\t列2\t列3" << endl;
    cout << "双引号 \\\" : 他说:\"加油！\"" << endl;
    cout << "反斜杠 \\\\ : 路径示例 C:\\\\cspj\\\\a.cpp" << endl;

    cout << "\n字符与字符串对比：" << endl;
    cout << "  字符 'A' → " << 'A' << endl;
    cout << "  字符串 \"A\" → " << "A" << endl;
}

// ==================== 6. 注释效果 ====================

void demoComments() {
    printBanner("6. 注释：被注释的代码不会执行");

    cout << "Hello"; // 行尾注释：这行仍会输出 Hello

    // 下面这整行不会执行：
    // cout << " World";

    cout << " CSP-J" << endl; /* 段内注释 */

    /*
     * 多行注释块：
     * cout << "这段完全不可见" << endl;
     * cout << "DEBUG" << endl;
     */

    cout << "只有未被注释的语句会产生输出。" << endl;
    cout << "期望看到：Hello CSP-J" << endl;
}

// ==================== 7. 调试输出 ====================

void demoDebugPrint() {
    printBanner("7. 调试输出技巧");

    int x = 100;
    cout << "[DEBUG] 程序执行到步骤1, x = " << x << endl;

    x = x * 2;
    cout << "[DEBUG] 步骤2: x * 2 => " << x << endl;

    x = x + 50;
    cout << "[DEBUG] 步骤3: x + 50 => " << x << endl;

    // 用 cerr 演示（默认也显示在终端）
    cerr << "[DEBUG/cerr] 若正式提交，请删除调试输出" << endl;

    cout << "正式结果示例: " << x << endl;
}

// ==================== 8. 编译流水线说明 ====================

void demoCompilePipeline() {
    printBanner("8. 编译运行四步骤（概念演示）");

    cout << "源文件 .cpp" << endl;
    cout << "    |" << endl;
    cout << "    v  (1) 预处理 处理 #include / #define" << endl;
    cout << "翻译单元" << endl;
    cout << "    |" << endl;
    cout << "    v  (2) 编译    语法检查 → 目标文件 .o/.obj" << endl;
    cout << "目标文件" << endl;
    cout << "    |" << endl;
    cout << "    v  (3) 链接    与标准库等合并" << endl;
    cout << "可执行文件" << endl;
    cout << "    |" << endl;
    cout << "    v  (4) 运行    从 main 开始执行" << endl;

    printLine();
    cout << "错误类型记忆：" << endl;
    cout << "  语法错误   → 编译阶段失败（缺分号等）" << endl;
    cout << "  链接错误   → 找不到函数实现等" << endl;
    cout << "  运行时错误 → 崩溃/异常（除零等）" << endl;
    cout << "  逻辑错误   → 能跑但答案错" << endl;
}

// ==================== 9. 易错点对照 ====================

void demoCommonMistakes() {
    printBanner("9. 易错点：正确写法演示");

    cout << "[1] 每条语句以英文分号结束" << endl;
    int ok = 1;
    cout << "    int ok = 1;  → ok=" << ok << endl;

    cout << "[2] main 必须是 int main()，区分大小写" << endl;
    cout << "    当前就在 main 调用的 demo 中运行" << endl;

    cout << "[3] 字符串用英文双引号" << endl;
    cout << "    \"Hello\" 正确" << endl;

    cout << "[4] 使用 cout 前需要 iostream + std" << endl;
    cout << "    本文件文件头已正确包含" << endl;

    cout << "[5] 修改代码后要重新编译再运行" << endl;
    cout << "    否则可能看到旧程序的输出" << endl;

    cout << "[6] 字符 'A' 与字符串 \"A\" 不同，但都能输出 A：" << endl;
    cout << "    char: " << 'A' << "  string-literal: " << "A" << endl;
}

// ==================== 10. 真题验证 ====================

void demoExamProblems() {
    printBanner("10. 讲义题目输出验证");

    cout << "【题目1】程序结构选择题答案：D" << endl;
    cout << "  return 0 表示程序正常结束" << endl;

    printLine();
    cout << "【题目2】注释程序输出应为：Hello CSP-J" << endl;
    cout << "  实际运行: ";
    cout << "Hello";
    // cout << " World";
    cout << " CSP-J" << endl;

    printLine();
    cout << "【题目4】两行欢迎语：" << endl;
    cout << "Hello, CSP-J!" << endl;
    cout << "I love programming." << endl;

    printLine();
    cout << "【题目5】表达式与注释：" << endl;
    cout << 2 + 3 * 4 << endl;
    // cout << 100 << endl;
    cout << "OK" << endl;
}

// ==================== 11. 竞赛模板风格 ====================

void demoTemplateStyle() {
    printBanner("11. 竞赛模板风格示意（无交互）");

    // 竞赛中常写：
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    // 这里仅演示“本地计算输出”，不强制读入

    int sampleA = 17;
    int sampleB = 25;
    cout << "假设输入 a=17, b=25（示例数据，非键盘输入）" << endl;
    cout << "a + b = " << sampleA + sampleB << endl;
    cout << "a * b = " << sampleA * sampleB << endl;
    cout << "max(a,b) = " << max(sampleA, sampleB) << endl;

    // 展示算法头的 swap
    int x = 1, y = 2;
    cout << "swap 前: x=" << x << " y=" << y << endl;
    swap(x, y);
    cout << "swap 后: x=" << x << " y=" << y << endl;
}

// ==================== 12. IDE 操作提示（文字） ====================

void demoIdeTips() {
    printBanner("12. Dev-C++ / Code::Blocks 操作备忘");

    cout << "Dev-C++ 常见：" << endl;
    cout << "  新建 Ctrl+N | 保存 Ctrl+S | 编译运行 F11" << endl;
    cout << "  建议路径: D:\\\\cspj\\\\lesson02\\\\hello.cpp" << endl;

    cout << "\nCode::Blocks 常见：" << endl;
    cout << "  编译并运行 F9 | 确认 Compiler 为 GNU GCC" << endl;

    cout << "\n通用建议：" << endl;
    cout << "  1. 先保存再编译" << endl;
    cout << "  2. 看清错误行号" << endl;
    cout << "  3. 对照样例输出" << endl;
    cout << "  4. 提交前删调试信息" << endl;
}

// ==================== 13. return 含义 ====================

void demoReturnMeaning() {
    printBanner("13. return 0 的含义");

    cout << "main 中 return 0; 表示：" << endl;
    cout << "  程序成功执行完毕，向操作系统返回状态码 0。" << endl;
    cout << "  非 0 常表示异常（脚本/评测有时会检查）。" << endl;
    cout << "  教学要求：显式写出 return 0;" << endl;

    // 普通函数中的 return 用于返回值（后续函数课展开）
    cout << "\n说明：demo 函数是 void，用 return; 可提前结束函数。" << endl;
}

// ==================== 14. 综合小节目 ====================

void demoMiniShow() {
    printBanner("14. 综合小节目：结构 + 输出 + 注释");

    /*
     * 文件级风格注释示例（函数内演示）
     * 功能：打印课程信息
     */
    cout << "Course: CSP-J Lesson 02" << endl;
    cout << "Topic : Environment & First Program" << endl;

    int lessons = 48;
    cout << "Total lessons in outline: " << lessons << endl;

    // int hidden = 0;
    // cout << hidden; // 注释掉的变量与输出

    cout << "Status: Ready for Lesson 03 (variables)" << endl;
}

// ==================== main ====================

int main() {
    // 可选加速（演示模板中的两行；本程序输出量大无妨开启）
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "############################################" << endl;
    cout << "#  CSP-J 第2课：C++编程环境与第一个程序    #" << endl;
    cout << "############################################" << endl;

    demoProgramSkeleton();
    demoHelloWorld();
    demoIncludeAndNamespace();
    demoCoutBasics();
    demoEscapeChars();
    demoComments();
    demoDebugPrint();
    demoCompilePipeline();
    demoCommonMistakes();
    demoExamProblems();
    demoTemplateStyle();
    demoIdeTips();
    demoReturnMeaning();
    demoMiniShow();

    cout << "\n############################################" << endl;
    cout << "#              第2课演示结束               #" << endl;
    cout << "#   return 0 表示本演示程序正常退出        #" << endl;
    cout << "############################################" << endl;

    return 0;
}
