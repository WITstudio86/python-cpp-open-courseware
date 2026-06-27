/*
 * CSP-J 备考课程
 * 第12课：循环控制与综合应用
 * 考纲知识点：
 *   - break（跳出当前循环）
 *   - continue（跳过本次循环剩余语句）
 *   - 循环嵌套综合（九九乘法表、图形打印）
 *   - 程序阅读分析方法（追踪变量变化）
 *
 * 本文件包含：
 *   1. break 演示 - 提前退出循环
 *   2. continue 演示 - 跳过特定迭代
 *   3. break vs continue 对比
 *   4. 九九乘法表（嵌套循环）
 *   5. 图形打印（三角形、矩形、菱形）
 *   6. 素数判断（break优化）
 *   7. 程序阅读分析（变量追踪）
 *   8. 真题AC代码
 */

#include <iostream>
#include <cmath>
using namespace std;

// -------------------------------------------
// 演示1：break - 提前退出循环
// -------------------------------------------
void demo_break() {
    cout << "\n========== 演示1：break - 提前退出循环 ==========" << endl;

    cout << "【示例1】找到第一个 5 就停止：" << endl;
    for (int i = 1; i <= 10; i++) {
        if (i == 5) {
            cout << "遇到 5，break！" << endl;
            break;
        }
        cout << i << " ";
    }
    cout << endl << "循环已结束。" << endl;

    cout << "\n【示例2】break 在多重循环中只跳出当前层：" << endl;
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 5; j++) {
            if (j == 3) {
                cout << "  [j=" << j << " 时 break 内层]";
                break;
            }
            cout << " (" << i << "," << j << ")";
        }
        cout << endl;  // 外层 i 循环继续
    }
    cout << "注意：外层 i 循环不受内层 break 影响" << endl;
}

// -------------------------------------------
// 演示2：continue - 跳过本次迭代剩余
// -------------------------------------------
void demo_continue() {
    cout << "\n========== 演示2：continue - 跳过本次迭代 ==========" << endl;

    cout << "【示例1】跳过偶数，只输出奇数：" << endl;
    for (int i = 1; i <= 15; i++) {
        if (i % 2 == 0) {
            continue;    // 偶数直接跳过
        }
        cout << i << " ";
    }
    cout << endl;

    cout << "\n【示例2】输出 1~20 中不能被 3 整除的数：" << endl;
    for (int i = 1; i <= 20; i++) {
        if (i % 3 == 0) continue;
        cout << i << " ";
    }
    cout << endl;

    cout << "\n【示例3】continue 在 for 循环中 i++ 仍会执行：" << endl;
    cout << "跳过 i=5 后，下一轮 i=6（i++ 照常执行）：" << endl;
    for (int i = 1; i <= 8; i++) {
        if (i == 5) {
            cout << " [跳过" << i << "] ";
            continue;
        }
        cout << i << " ";
    }
    cout << endl;
}

// -------------------------------------------
// 演示3：while 中使用 continue 的陷阱
// -------------------------------------------
void demo_while_continue_trap() {
    cout << "\n========== 演示3：while 中使用 continue 的陷阱 ==========" << endl;

    cout << "\n【正确做法】while + continue（先更新变量）：" << endl;
    int i = 1;
    while (i <= 10) {
        if (i % 2 == 0) {
            i++;           // 必须先更新，再 continue
            continue;
        }
        cout << i << " ";
        i++;
    }
    cout << endl;

    cout << "\n【对比】for 循环自动处理 i++，更安全：" << endl;
    for (int i = 1; i <= 10; i++) {
        if (i % 2 == 0) continue;
        cout << i << " ";
    }
    cout << endl;
    cout << "结论：while + continue 要手动保证变量更新，否则死循环！" << endl;
}

// -------------------------------------------
// 演示4：break vs continue 一图对比
// -------------------------------------------
void demo_break_vs_continue() {
    cout << "\n========== 演示4：break vs continue 对比 ==========" << endl;

    cout << "\nbreak 版本（遇到 5 就停止）：" << endl;
    for (int i = 1; i <= 8; i++) {
        if (i == 5) break;
        cout << i << " ";
    }
    cout << "→ 循环终止于 i=5" << endl;

    cout << "\ncontinue 版本（跳过 5，继续后面）：" << endl;
    for (int i = 1; i <= 8; i++) {
        if (i == 5) continue;
        cout << i << " ";
    }
    cout << "→ 只跳过 5，其他照常输出" << endl;

    cout << "\n关键区别：" << endl;
    cout << "  break    → 结束整个循环，后面的迭代都不执行" << endl;
    cout << "  continue → 只跳过这一次，循环还会继续" << endl;
}

// -------------------------------------------
// 演示5：九九乘法表（嵌套循环经典）
// -------------------------------------------
void demo_multiplication_table() {
    cout << "\n========== 演示5：九九乘法表 ==========" << endl;

    cout << "\n【标准九九乘法表】" << endl;
    cout << "     ";
    for (int col = 1; col <= 9; col++) {
        cout << col << "     ";
    }
    cout << endl;
    cout << "     " << string(45, '-') << endl;

    for (int i = 1; i <= 9; i++) {
        // 外层：控制行
        cout << " " << i << " | ";
        for (int j = 1; j <= i; j++) {
            // 内层：控制列
            printf("%d×%d=%-3d", j, i, i * j);
        }
        cout << endl;
    }

    cout << "\n【完整矩形乘法表】" << endl;
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            printf("%d×%d=%-3d", i, j, i * j);
        }
        cout << endl;
    }
}

// -------------------------------------------
// 演示6：图形打印 - 三角形
// -------------------------------------------
void demo_triangle_patterns() {
    cout << "\n========== 演示6：图形打印 - 三角形 ==========" << endl;
    int n;
    cout << "请输入三角形高度 n：";
    cin >> n;

    cout << "\n【1】正直角三角形（左下角）：" << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            cout << "*";
        }
        cout << endl;
    }

    cout << "\n【2】正直角三角形（右下角）：" << endl;
    for (int i = 1; i <= n; i++) {
        // 先打空格
        for (int j = 1; j <= n - i; j++) {
            cout << " ";
        }
        // 再打星号
        for (int j = 1; j <= i; j++) {
            cout << "*";
        }
        cout << endl;
    }

    cout << "\n【3】等腰三角形（金字塔）：" << endl;
    for (int i = 1; i <= n; i++) {
        // 空格：n - i 个
        for (int j = 1; j <= n - i; j++) {
            cout << " ";
        }
        // 星号：2i - 1 个
        for (int j = 1; j <= 2 * i - 1; j++) {
            cout << "*";
        }
        cout << endl;
    }

    cout << "\n公式总结（第 i 行）：" << endl;
    cout << "  左下直角三角形：星号 = i 个" << endl;
    cout << "  右下直角三角形：空格 = n-i 个，星号 = i 个" << endl;
    cout << "  等腰三角形：空格 = n-i 个，星号 = 2i-1 个" << endl;
}

// -------------------------------------------
// 演示7：图形打印 - 菱形
// -------------------------------------------
void demo_diamond_pattern() {
    cout << "\n========== 演示7：图形打印 - 菱形 ==========" << endl;
    int n;
    cout << "请输入菱形半径（上半部分行数）n：";
    cin >> n;

    cout << "\n【菱形】（上半 n=" << n << "）：" << endl;

    // 上半部分（包括中间行）
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n - i; j++) cout << " ";
        for (int j = 1; j <= 2 * i - 1; j++) cout << "*";
        cout << endl;
    }
    // 下半部分（n-1 行）
    for (int i = n - 1; i >= 1; i--) {
        for (int j = 1; j <= n - i; j++) cout << " ";
        for (int j = 1; j <= 2 * i - 1; j++) cout << "*";
        cout << endl;
    }

    cout << "\n【矩形】（n×n）：" << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << "* ";
        }
        cout << endl;
    }
}

// -------------------------------------------
// 演示8：素数判断（break 优化）
// -------------------------------------------
void demo_prime_check() {
    cout << "\n========== 演示8：素数判断（break 优化） ==========" << endl;
    int n;
    cout << "请输入一个正整数：";
    cin >> n;

    if (n <= 1) {
        cout << n << " 不是素数（素数必须大于 1）" << endl;
        return;
    }

    bool isPrime = true;
    int checks = 0;  // 统计检查次数

    // 只需检查到 sqrt(n)
    for (int i = 2; i * i <= n; i++) {
        checks++;
        if (n % i == 0) {
            cout << "找到因子 " << i << "，确定 " << n << " = " << i << " × " << n / i << endl;
            isPrime = false;
            break;  // 找到因子立即退出，不再继续检查
        }
    }

    if (isPrime) {
        cout << n << " 是素数！（检查了 " << checks << " 次）" << endl;
    } else {
        cout << n << " 不是素数（仅检查了 " << checks << " 次就找到因子）" << endl;
    }

    cout << "\n【优化说明】" << endl;
    cout << "  不加 break：需要检查 sqrt(n) 次" << endl;
    cout << "  加了 break：找到第一个因子就停止，大幅减少检查次数" << endl;
}

// -------------------------------------------
// 演示9：程序阅读分析 - 变量追踪表格法
// -------------------------------------------
void demo_program_reading_analysis() {
    cout << "\n========== 演示9：程序阅读分析（变量追踪表格法） ==========" << endl;

    cout << "\n【程序1】分析以下代码输出：" << endl;
    cout << "-----------------------------" << endl;
    cout << "int sum = 0;" << endl;
    cout << "for (int i = 1; i <= 10; i++) {" << endl;
    cout << "    if (i % 3 == 0) continue;" << endl;
    cout << "    if (i == 8) break;" << endl;
    cout << "    sum += i;" << endl;
    cout << "}" << endl;
    cout << "cout << sum;" << endl;
    cout << "-----------------------------" << endl;

    // 实际执行以验证
    int sum = 0;
    cout << "\n【变量追踪表格】" << endl;
    cout << " i  | i%3==0? | i==8? | 操作        | sum" << endl;
    cout << "----|---------|-------|-------------|----" << endl;

    for (int i = 1; i <= 10; i++) {
        cout << " " << i << "  | ";
        if (i % 3 == 0) {
            cout << "是(跳过) |   -   | continue    | " << sum << endl;
            continue;
        }
        cout << " 否     | ";
        if (i == 8) {
            cout << "是(退出)| break      | " << sum << endl;
            break;
        }
        cout << " 否     | ";
        sum += i;
        cout << "sum+=" << i << "      | " << sum << endl;
    }
    cout << "\n最终输出：" << sum << endl;

    cout << "\n【程序2】分析嵌套循环中 break 的效果：" << endl;
    cout << "-----------------------------" << endl;
    cout << "for (int i = 1; i <= 3; i++) {" << endl;
    cout << "    for (int j = 1; j <= 5; j++) {" << endl;
    cout << "        if (j == 3) break;" << endl;
    cout << "        cout << i << \",\" << j << \" \";" << endl;
    cout << "    }" << endl;
    cout << "    cout << endl;" << endl;
    cout << "}" << endl;
    cout << "-----------------------------" << endl;

    cout << "\n【实际输出】" << endl;
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 5; j++) {
            if (j == 3) break;
            cout << i << "," << j << " ";
        }
        cout << endl;
    }
    cout << "→ 内层 break 只终止 j 循环，外层 i 继续！" << endl;
}

// -------------------------------------------
// 真题1：程序阅读 - break/continue 效果
// -------------------------------------------
void zhenti1_program_reading() {
    cout << "\n========== 真题1：break/continue 程序阅读 ==========" << endl;

    cout << "阅读以下程序，写出输出结果：" << endl;
    cout << "-----------------------------" << endl;
    cout << "int sum = 0;" << endl;
    cout << "for (int i = 1; i <= 10; i++) {" << endl;
    cout << "    if (i % 3 == 0) continue;" << endl;
    cout << "    if (i == 8) break;" << endl;
    cout << "    sum += i;" << endl;
    cout << "}" << endl;
    cout << "cout << sum << endl;" << endl;
    cout << "-----------------------------" << endl;

    cout << "\n按回车键查看变量追踪分析..." << endl;
    cin.get(); // 消耗前一次输入的换行
    cin.get();

    cout << "\n【变量追踪表格】" << endl;
    cout << "|  i | i%3==0? | i==8? | 操作     | sum |" << endl;
    cout << "|----|---------|-------|----------|-----|" << endl;

    int sum = 0;
    for (int i = 1; i <= 10; i++) {
        if (i % 3 == 0) {
            cout << "|  " << i << " |  是(continue) |  —    | 跳过加法 |  " << sum << "  |" << endl;
            continue;
        }
        if (i == 8) {
            cout << "|  8 |   否    | 是(break) | 循环终止 |  " << sum << "  |" << endl;
            break;
        }
        sum += i;
        cout << "|  " << i << " |   否    |  否   | sum+=" << i << "   |  " << sum << "  |" << endl;
    }
    cout << "\n最终输出：" << sum << endl;
    cout << "解释：1+2+4+5+7 = 19，3和6被 continue 跳过，8时 break 终止循环" << endl;
}

// -------------------------------------------
// 真题2：图形输出 - 等腰三角形
// -------------------------------------------
void zhenti2_triangle_print() {
    cout << "\n========== 真题2：图形输出 - 等腰三角形 ==========" << endl;
    int n;
    cout << "请输入三角形高度 n：";
    cin >> n;

    cout << "\n输出高为 " << n << " 的等腰三角形：" << endl;
    for (int i = 1; i <= n; i++) {
        // (1) 打印空格：第 i 行有 n - i 个空格
        for (int j = 1; j <= n - i; j++) {
            cout << " ";
        }
        // (2) 打印星号：第 i 行有 2 * i - 1 个星号
        for (int j = 1; j <= 2 * i - 1; j++) {
            cout << "*";
        }
        cout << endl;
    }

    cout << "\n规律解析：" << endl;
    cout << "  第 i 行空格数 = n - i = " << n << " - i" << endl;
    cout << "  第 i 行星号数 = 2i - 1" << endl;
    for (int i = 1; i <= n; i++) {
        cout << "  第 " << i << " 行：空格=" << (n - i)
             << "，星号=" << (2 * i - 1) << endl;
    }
}

// -------------------------------------------
// 主菜单
// -------------------------------------------
int main() {
    int choice;
    do {
        cout << "\n╔══════════════════════════════════════════╗" << endl;
        cout << "║   第12课：循环控制与综合应用             ║" << endl;
        cout << "╠══════════════════════════════════════════╣" << endl;
        cout << "║  1. break 演示 - 提前退出循环           ║" << endl;
        cout << "║  2. continue 演示 - 跳过本次迭代        ║" << endl;
        cout << "║  3. while + continue 陷阱               ║" << endl;
        cout << "║  4. break vs continue 对比               ║" << endl;
        cout << "║  5. 九九乘法表（嵌套循环）               ║" << endl;
        cout << "║  6. 图形打印 - 三角形                   ║" << endl;
        cout << "║  7. 图形打印 - 菱形与矩形               ║" << endl;
        cout << "║  8. 素数判断（break 优化）               ║" << endl;
        cout << "║  9. 程序阅读分析（变量追踪）             ║" << endl;
        cout << "║ 10. 真题1：break/continue 程序阅读      ║" << endl;
        cout << "║ 11. 真题2：等腰三角形图形输出           ║" << endl;
        cout << "║  0. 退出                                ║" << endl;
        cout << "╚══════════════════════════════════════════╝" << endl;
        cout << "请选择演示功能：";
        cin >> choice;
        cin.ignore();  // 清除缓冲区中的换行符

        switch (choice) {
            case 1:  demo_break();                      break;
            case 2:  demo_continue();                   break;
            case 3:  demo_while_continue_trap();         break;
            case 4:  demo_break_vs_continue();           break;
            case 5:  demo_multiplication_table();         break;
            case 6:  demo_triangle_patterns();            break;
            case 7:  demo_diamond_pattern();              break;
            case 8:  demo_prime_check();                  break;
            case 9:  demo_program_reading_analysis();     break;
            case 10: zhenti1_program_reading();           break;
            case 11: zhenti2_triangle_print();            break;
            case 0:
                cout << "感谢学习第12课，循环部分已全部完成！" << endl;
                break;
            default:
                cout << "无效选择，请重新输入！" << endl;
                break;
        }
    } while (choice != 0);

    return 0;
}
