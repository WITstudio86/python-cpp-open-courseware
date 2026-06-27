/*
 * CSP-J 备考课程
 * 第2课：C++编程环境与第一个程序
 * 考纲知识点：Dev-C++/CodeBlocks使用、程序基本结构、编译运行流程、注释
 *
 * 本文件包含：
 * 1. 标准程序框架演示
 * 2. 注释使用演示
 * 3. 调试输出技巧
 */

#include <iostream>     // 输入输出流
#include <cstdio>       // C风格输入输出
#include <cmath>        // 数学函数库
#include <algorithm>    // 算法库
using namespace std;

/*
 * 函数：printSeparator
 * 功能：打印分隔线
 */
void printSeparator() {
    cout << "----------------------------------------" << endl;
}

int main() {
    // 第1部分：演示程序基本结构
    cout << "===== CSP-J 第2课：C++编程环境 =====" << endl;
    printSeparator();

    // 第2部分：cout 输出演示
    cout << "【cout 基本输出】" << endl;
    cout << "Hello, CSP-J!" << endl;           // 输出并换行
    cout << "第一行" << "\n";                    // 使用\\n换行
    cout << "第二行" << endl;
    printSeparator();

    // 第3部分：变量定义与输出
    cout << "【变量定义与输出】" << endl;
    int a = 10;
    int b = 20;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "a + b = " << a + b << endl;
    printSeparator();

    // 第4部分：调试输出技巧
    cout << "【调试输出技巧】" << endl;
    cout << "程序执行到步骤1" << endl;

    int x = 100;
    cout << "调试: x = " << x << endl;

    x = x * 2;
    cout << "调试: x * 2 = " << x << endl;

    x = x + 50;
    cout << "调试: x + 50 = " << x << endl;
    printSeparator();

    // 第5部分：注释演示
    cout << "【注释演示】" << endl;

    // 这是单行注释，以下代码被注释掉，不会执行：
    // cout << "这行不会输出" << endl;

    /*
     * 这是多行注释
     * 被注释的代码不会执行
     * cout << "这行也不会输出" << endl;
     */

    cout << "只有未被注释的代码会执行" << endl;  // 行尾注释
    printSeparator();

    // 第6部分：验证 return 0
    cout << "程序即将正常结束..." << endl;
    cout << "return 0 表示程序正常退出" << endl;

    /*
     * 此注释中包含以下代码（仅作示例）：
     * cout << "被注释的代码" << endl;
     * cout << "不会执行" << endl;
     */

    return 0;
}
