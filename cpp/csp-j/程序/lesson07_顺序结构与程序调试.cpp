/*
 * CSP-J 备考课程
 * 第7课：顺序结构与程序调试
 * 考纲知识点：顺序执行、断点调试、变量监视、常见编译错误、程序阅读方法
 *
 * 本文件包含：
 * 1. 顺序执行演示
 * 2. 变量追踪练习
 * 3. 调试输出技巧
 * 4. 常见错误示例
 */

#include <iostream>
#include <iomanip>
using namespace std;

// 调试开关：注释掉可关闭调试输出
#define DEBUG_MODE

int main() {
    cout << "========== CSP-J 第7课：顺序结构与程序调试 ==========" << endl;
    cout << endl;

    // ===== 一、顺序执行演示 =====
    cout << "【一、顺序执行演示】" << endl;

    int a = 10;
    cout << "语句1: a = " << a << endl;

    int b = 20;
    cout << "语句2: b = " << b << endl;

    int c = a + b;
    cout << "语句3: c = a + b = " << c << endl;

    c = c * 2;
    cout << "语句4: c = c * 2 = " << c << endl;

    cout << "每条语句按从上到下的顺序执行" << endl;
    cout << endl;

    // ===== 二、变量追踪练习 =====
    cout << "【二、变量追踪练习】" << endl;

    cout << "练习1: 变量值交换" << endl;
    int x = 5, y = 8;
    cout << "初始: x=" << x << ", y=" << y << endl;

    x = x + y;
    cout << "x = x + y → x=" << x << ", y=" << y << endl;

    y = x - y;
    cout << "y = x - y → x=" << x << ", y=" << y << endl;

    x = x - y;
    cout << "x = x - y → x=" << x << ", y=" << y << endl;
    cout << "成功交换！(不使用临时变量)" << endl;
    cout << endl;

    cout << "练习2: 多变量追踪" << endl;
    int p = 3, q = 7, r = 4;
    cout << "初始: p=" << p << ", q=" << q << ", r=" << r << endl;

    p = q - p;        cout << "p=q-p → p=" << p << endl;
    q = r * p;        cout << "q=r*p → q=" << q << endl;
    r = q + p;        cout << "r=q+p → r=" << r << endl;
    cout << "最终: p=" << p << ", q=" << q << ", r=" << r << endl;
    cout << endl;

    // ===== 三、调试输出技巧 =====
    cout << "【三、调试输出技巧】" << endl;

#ifdef DEBUG_MODE
    cout << "[DEBUG] 调试模式已开启" << endl;
#endif

    int total = 0;
    for (int i = 1; i <= 5; i++) {
        total += i;
#ifdef DEBUG_MODE
        cout << "[DEBUG] i=" << i << ", total=" << total << endl;
#endif
    }
    cout << "最终结果: total = " << total << endl;
    cout << endl;

    // ===== 四、常见编译错误演示 =====
    cout << "【四、常见错误说明】" << endl;
    cout << "以下错误在注释中展示，取消注释会导致编译失败:" << endl;
    cout << endl;

    cout << "1. 缺少分号: ";
    // cout << "error"  ← 少了分号
    cout << "应为: cout << \"text\";" << endl;

    cout << "2. 变量未定义: ";
    // cout << unknownVar;  ← 变量未声明
    cout << "使用前必须先声明变量" << endl;

    cout << "3. 类型不匹配: ";
    // int x = "hello";  ← 类型错误
    cout << "类型必须兼容" << endl;
    cout << endl;

    // ===== 五、变量追踪表练习 =====
    cout << "【五、程序阅读：变量追踪表】" << endl;
    cout << "阅读以下代码，追踪变量变化:" << endl;

    int m = 10, n = 3;
    cout << "初始: m=" << setw(3) << m << ", n=" << setw(3) << n << endl;

    m = m + n;    // m=13
    cout << "m=m+n: m=" << setw(3) << m << ", n=" << setw(3) << n << endl;

    n = m - n;    // n=10
    cout << "n=m-n: m=" << setw(3) << m << ", n=" << setw(3) << n << endl;

    m = m - n;    // m=3
    cout << "m=m-n: m=" << setw(3) << m << ", n=" << setw(3) << n << endl;

    cout << "结果: m=" << m << ", n=" << n << " (值已互换!)" << endl;
    cout << endl;

    // ===== 六、常见陷阱示例 =====
    cout << "【六、常见陷阱示例】" << endl;

    // 陷阱1：整数除法
    cout << "陷阱1：整数除法" << endl;
    int u = 5, v = 2;
    cout << "5 / 2 = " << (u / v) << " (不是2.5!)" << endl;
    cout << "正确: 5.0 / 2 = " << (5.0 / 2) << endl;
    cout << endl;

    // 陷阱2：未初始化变量
    cout << "陷阱2：未初始化变量" << endl;
    cout << "局部变量必须初始化，否则值是随机的!" << endl;
    int initialized = 0;  // 正确做法
    cout << "初始化后的变量: " << initialized << endl;
    cout << endl;

    // 陷阱3：= 与 == 混淆
    cout << "陷阱3: = 与 == 混淆" << endl;
    int val1 = 5;
    if (val1 = 10) {  // 注意：这是赋值，不是比较！
        cout << "if(val1=10) 是赋值语句，始终为true!" << endl;
        cout << "val1 被改为: " << val1 << endl;
    }
    cout << "正确写法: if(val1 == 10)" << endl;

    cout << endl << "========== 第7课演示结束 ==========" << endl;
    return 0;
}
