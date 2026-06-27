/*
 * CSP-J 备考课程
 * 第10课：for 循环结构
 * 考纲知识点：for(初始化;条件;更新)语法、循环变量作用域、
 *            累加/累乘模式、循环嵌套（外层控制行内层控制列）、
 *            循环次数计算
 *
 * 本文件包含：
 * 1. for循环三要素详解 + 执行流程演示
 * 2. 累加模式演示（1~n求和）
 * 3. 累乘模式演示（阶乘）
 * 4. 循环变量作用域演示
 * 5. 嵌套循环演示——九九乘法表
 * 6. 嵌套循环演示——图形打印（三角形、金字塔、倒三角）
 * 7. 循环次数计算演示
 * 8. 因子枚举演示
 * 9. 真题1：循环执行次数计算
 * 10. 真题2：嵌套循环输出分析（金字塔）
 */

#include <iostream>
#include <iomanip>
using namespace std;

// ==================== 演示函数 ====================

// 1. for循环三要素详解 + 执行流程演示
void demo01_basic_for() {
    cout << "=== 演示1：for 循环三要素详解 ===" << endl;
    cout << "语法：for(初始化; 条件; 更新) { 循环体 }" << endl;
    cout << endl;

    cout << "示例：输出 1 到 10" << endl;
    cout << "代码：for (int i = 1; i <= 10; i++)" << endl;
    cout << "执行流程追踪：" << endl;

    for (int i = 1; i <= 10; i++) {
        cout << "  第 " << i << " 次循环：i = " << i;
        if (i < 10) {
            cout << " → 条件 i<=10 为 true，继续";
        } else {
            cout << " → 这是最后一次";
        }
        cout << endl;
    }
    cout << "  循环结束：i = 11，条件 i<=10 为 false，退出循环" << endl;
    cout << endl;

    // 演示倒序循环
    cout << "倒序输出 10 到 1：" << endl;
    cout << "代码：for (int i = 10; i >= 1; i--)" << endl;
    for (int i = 10; i >= 1; i--) {
        cout << i << " ";
    }
    cout << endl << endl;

    // 演示步长
    cout << "输出 1~20 中的所有奇数（步长 2）：" << endl;
    cout << "代码：for (int i = 1; i <= 20; i += 2)" << endl;
    for (int i = 1; i <= 20; i += 2) {
        cout << i << " ";
    }
    cout << endl << endl;
}

// 2. 累加模式演示
void demo02_accumulate_sum() {
    cout << "=== 演示2：累加模式 ===" << endl;
    cout << "请输入 n，计算 1+2+...+n：";
    int n;
    cin >> n;

    // 方法1：循环累加
    int sum1 = 0;
    for (int i = 1; i <= n; i++) {
        sum1 += i;
    }

    // 方法2：公式法（高斯求和公式）
    int sum2 = n * (n + 1) / 2;

    cout << "循环累加结果：sum = " << sum1 << endl;
    cout << "公式计算结果：sum = n*(n+1)/2 = " << sum2 << endl;
    cout << "两种方法结果" << (sum1 == sum2 ? "一致" : "不一致！") << endl;
    cout << endl;

    // 扩展：平方和
    cout << "同时计算 1²+2²+...+" << n << "²：" << endl;
    int sumSquare = 0;
    for (int i = 1; i <= n; i++) {
        sumSquare += i * i;
    }
    cout << "平方和 = " << sumSquare << endl;
    cout << endl;
}

// 3. 累乘模式演示
void demo03_accumulate_product() {
    cout << "=== 演示3：累乘模式 ===" << endl;
    cout << "请输入 n，计算 n!（阶乘）：";
    int n;
    cin >> n;

    if (n < 0) {
        cout << "负数没有阶乘！" << endl;
    } else if (n > 12) {
        cout << "n 太大，结果可能溢出 int 范围！" << endl;
        // 使用 long long 防止溢出
        long long factorial = 1;
        for (int i = 1; i <= n; i++) {
            factorial *= i;
        }
        cout << n << "! = " << factorial << "（使用 long long）" << endl;
    } else {
        int factorial = 1;
        cout << "计算过程：";
        for (int i = 1; i <= n; i++) {
            factorial *= i;
            cout << i;
            if (i < n) cout << " x ";
        }
        cout << " = " << factorial << endl;
    }
    cout << endl;

    // 提示：累乘器初始化为 1，不是 0！
    cout << "注意：累乘器必须初始化为 1（乘法的单位元），" << endl;
    cout << "      如果初始化为 0，任何数乘以 0 都是 0！" << endl;
    cout << endl;
}

// 4. 循环变量作用域演示
void demo04_scope() {
    cout << "=== 演示4：循环变量作用域 ===" << endl;

    // 情况1：在 for 内部声明
    cout << "【情况1】在 for 内部声明循环变量：" << endl;
    cout << "  for (int i = 1; i <= 3; i++) { ... }" << endl;
    for (int i = 1; i <= 3; i++) {
        cout << "    循环内：i = " << i << endl;
    }
    cout << "  // cout << i;  ← 编译错误！i 已超出作用域" << endl;
    cout << "  结论：for 内声明的 i 在循环结束后不可访问" << endl;
    cout << endl;

    // 情况2：在 for 外部声明
    cout << "【情况2】在 for 外部声明循环变量：" << endl;
    cout << "  int j;" << endl;
    cout << "  for (j = 1; j <= 3; j++) { ... }" << endl;
    int j;
    for (j = 1; j <= 3; j++) {
        cout << "    循环内：j = " << j << endl;
    }
    cout << "  循环结束后：j = " << j << "（j 仍然可以访问）" << endl;
    cout << "  结论：for 外声明的 j 在循环结束后仍有效" << endl;
    cout << endl;

    // 情况3：循环结束时的变量值
    cout << "【情况3】循环结束时循环变量的值：" << endl;
    int k;
    for (k = 0; k < 5; k++) {
        // 循环体
    }
    cout << "  for (k = 0; k < 5; k++) 执行完毕后，k = " << k << endl;
    cout << "  解释：最后一次 k++ 将 k 变为 5，此时条件 k<5 为 false，退出" << endl;
    cout << endl;
}

// 5. 嵌套循环演示——九九乘法表
void demo05_multiplication_table() {
    cout << "=== 演示5：嵌套循环 - 九九乘法表 ===" << endl;
    cout << "规则：外层控制行（i: 1~9），内层控制列（j: 1~i）" << endl;
    cout << endl;

    // 表头
    cout << "    ";
    for (int col = 1; col <= 9; col++) {
        cout << setw(4) << col;
    }
    cout << endl;
    cout << "    " << string(36, '-') << endl;

    // 九九乘法表
    for (int i = 1; i <= 9; i++) {
        cout << setw(2) << i << " |";
        for (int j = 1; j <= i; j++) {
            cout << setw(4) << i * j;
        }
        cout << endl;
    }
    cout << endl;

    // 完整版（上三角）
    cout << "完整 9x9 乘法表：" << endl;
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            cout << setw(2) << j << "x" << setw(1) << i
                 << "=" << setw(2) << i * j << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

// 6. 嵌套循环演示——图形打印
void demo06_pattern_printing() {
    cout << "=== 演示6：嵌套循环 - 图形打印 ===" << endl;
    int n = 5;

    // 图形1：直角三角形（左下角）
    cout << "【图形1】直角三角形（左下角）：" << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            cout << "*";
        }
        cout << endl;
    }
    cout << endl;

    // 图形2：直角三角形（右下角）
    cout << "【图形2】直角三角形（右下角）：" << endl;
    for (int i = 1; i <= n; i++) {
        // 先打印空格
        for (int j = 1; j <= n - i; j++) {
            cout << " ";
        }
        // 再打印星号
        for (int j = 1; j <= i; j++) {
            cout << "*";
        }
        cout << endl;
    }
    cout << endl;

    // 图形3：倒直角三角形
    cout << "【图形3】倒直角三角形：" << endl;
    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= i; j++) {
            cout << "*";
        }
        cout << endl;
    }
    cout << endl;

    // 图形4：金字塔
    cout << "【图形4】金字塔：" << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n - i; j++) {
            cout << " ";
        }
        for (int k = 1; k <= 2 * i - 1; k++) {
            cout << "*";
        }
        cout << endl;
    }
    cout << endl;

    // 图形5：菱形
    cout << "【图形5】菱形：" << endl;
    // 上半部分
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n - i; j++) cout << " ";
        for (int k = 1; k <= 2 * i - 1; k++) cout << "*";
        cout << endl;
    }
    // 下半部分
    for (int i = n - 1; i >= 1; i--) {
        for (int j = 1; j <= n - i; j++) cout << " ";
        for (int k = 1; k <= 2 * i - 1; k++) cout << "*";
        cout << endl;
    }
    cout << endl;
}

// 7. 循环次数计算演示
void demo07_loop_count() {
    cout << "=== 演示7：循环次数计算 ===" << endl;

    cout << "【公式1】for (i=a; i<=b; i++) → 执行 b-a+1 次" << endl;
    cout << "  例：for (i=1; i<=10; i++) → 10-1+1 = 10 次" << endl;

    cout << "【公式2】for (i=a; i<b; i++)  → 执行 b-a 次" << endl;
    cout << "  例：for (i=0; i<10; i++) → 10-0 = 10 次" << endl;

    cout << "【公式3】for (i=a; i>=b; i--) → 执行 a-b+1 次" << endl;
    cout << "  例：for (i=10; i>=1; i--) → 10-1+1 = 10 次" << endl;

    cout << endl;

    // 实际验证
    cout << "实际验证（用计数器统计）：" << endl;

    int cnt1 = 0;
    for (int i = 1; i <= 10; i++) cnt1++;
    cout << "  for (i=1; i<=10; i++) → 执行了 " << cnt1 << " 次" << endl;

    int cnt2 = 0;
    for (int i = 0; i < 10; i++) cnt2++;
    cout << "  for (i=0; i<10; i++)  → 执行了 " << cnt2 << " 次" << endl;

    int cnt3 = 0;
    for (int i = 10; i >= 1; i--) cnt3++;
    cout << "  for (i=10; i>=1; i--) → 执行了 " << cnt3 << " 次" << endl;

    cout << endl;

    // 嵌套循环次数
    cout << "嵌套循环次数计算：" << endl;
    int cntNest = 0;
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 4; j++) {
            cntNest++;
        }
    }
    cout << "  for(i=1~3) for(j=1~4) → 3 x 4 = " << cntNest << " 次" << endl;

    // Off-by-one 陷阱
    cout << endl;
    cout << "【off-by-one 陷阱】" << endl;
    cout << "  for (i=1; i<10; i++)  → 执行 9 次（注意：不是 10 次！）" << endl;
    cout << "  for (i=0; i<=10; i++) → 执行 11 次（注意：不是 10 次！）" << endl;
    cout << "  记忆：<  不包含边界，<= 包含边界" << endl;
    cout << endl;
}

// 8. 因子枚举演示
void demo08_factor_enumeration() {
    cout << "=== 演示8：因子枚举 ===" << endl;
    cout << "请输入一个正整数，找出它的所有因子：";
    int n;
    cin >> n;

    cout << n << " 的因子有：";
    int factorCount = 0;
    int factorSum = 0;

    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            cout << i << " ";
            factorCount++;
            factorSum += i;
        }
    }
    cout << endl;
    cout << "因子个数：" << factorCount << endl;
    cout << "因子之和：" << factorSum << endl;

    if (factorCount == 2) {
        cout << "结论：" << n << " 是素数（只有 1 和它本身两个因子）" << endl;
    } else {
        cout << "结论：" << n << " 不是素数" << endl;
    }
    cout << endl;

    // 优化版：只枚举到 sqrt(n)
    cout << "优化提示：其实只需要枚举到 sqrt(" << n << ") = ";
    // 手动计算整数平方根
    int sqrtN = 1;
    while (sqrtN * sqrtN <= n) sqrtN++;
    sqrtN--;
    cout << sqrtN << " 即可找出所有因子（进阶优化技巧）" << endl;
    cout << endl;
}

// ==================== 真题 AC 代码 ====================

// 真题1：循环执行次数计算
void exam01_loop_count() {
    cout << "=== 真题1：循环执行次数计算 ===" << endl;
    cout << "题目：分析以下三段代码的输出结果。" << endl;
    cout << endl;

    // 问题1
    cout << "【问题1】" << endl;
    cout << "int count = 0;" << endl;
    cout << "for (int i = 0; i < 5; i++)" << endl;
    cout << "    for (int j = 0; j <= i; j++)" << endl;
    cout << "        count++;" << endl;
    cout << "cout << count;" << endl;

    int count1 = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j <= i; j++) {
            count1++;
        }
    }
    cout << "输出：" << count1 << "  （分析：1+2+3+4+5 = 15）" << endl;
    cout << endl;

    // 问题2
    cout << "【问题2】" << endl;
    cout << "若内层循环改为 for (int j = 0; j < 3; j++)：" << endl;
    int count2 = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            count2++;
        }
    }
    cout << "输出：" << count2 << "  （分析：5 × 3 = 15）" << endl;
    cout << endl;

    // 问题3
    cout << "【问题3】" << endl;
    cout << "外层 for(i=1;i<=5;i++)，内层 for(j=1;j<=i;j++)，count += j：" << endl;
    int count3 = 0;
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= i; j++) {
            count3 += j;
        }
    }
    cout << "输出：" << count3 << "  （分析：1+(1+2)+(1+2+3)+(1+2+3+4)+(1+2+3+4+5) = 35）" << endl;
    cout << endl;

    // 详细分析表
    cout << "详细分析表：" << endl;
    cout << " i | j 取值范围  | 本行累加值 | 累计 count" << endl;
    cout << "---|-------------|-----------|----------" << endl;
    int cnt = 0;
    for (int i = 1; i <= 5; i++) {
        int rowSum = 0;
        cout << " " << i << " | j=1 ~ " << i << "      | ";
        for (int j = 1; j <= i; j++) {
            rowSum += j;
            cnt += j;
        }
        cout << setw(9) << rowSum << " | " << setw(8) << cnt << endl;
    }
    cout << endl;
}

// 真题2：嵌套循环输出分析（金字塔）
void exam02_pyramid() {
    cout << "=== 真题2：嵌套循环输出分析（金字塔） ===" << endl;
    cout << "题目：分析以下代码的完整输出。" << endl;
    cout << endl;
    cout << "int n = 4;" << endl;
    cout << "for (int i = 1; i <= n; i++) {" << endl;
    cout << "    for (int j = 1; j <= n - i; j++) cout << \" \";" << endl;
    cout << "    for (int k = 1; k <= 2 * i - 1; k++) cout << \"*\";" << endl;
    cout << "    cout << endl;" << endl;
    cout << "}" << endl;
    cout << endl;

    cout << "程序输出：" << endl;
    cout << "---输出开始---" << endl;
    int n = 4;
    for (int i = 1; i <= n; i++) {
        // 打印空格
        for (int j = 1; j <= n - i; j++) {
            cout << " ";
        }
        // 打印星号
        for (int k = 1; k <= 2 * i - 1; k++) {
            cout << "*";
        }
        cout << endl;
    }
    cout << "---输出结束---" << endl;
    cout << endl;

    // 逐行分析
    cout << "逐行分析：" << endl;
    cout << " i | 空格数(n-i) | 星号数(2i-1) | 本行输出" << endl;
    cout << "---|-------------|-------------|---------" << endl;
    for (int i = 1; i <= n; i++) {
        cout << " " << i << " |      " << (n - i) << "      |      "
             << (2 * i - 1) << "      | ";
        for (int j = 1; j <= n - i; j++) cout << " ";
        for (int k = 1; k <= 2 * i - 1; k++) cout << "*";
        cout << endl;
    }
    cout << endl;

    // 扩展：让用户输入 n
    cout << "扩展练习：请输入金字塔层数 n：";
    int userN;
    cin >> userN;
    if (userN > 0 && userN <= 20) {
        cout << userN << " 层金字塔：" << endl;
        for (int i = 1; i <= userN; i++) {
            for (int j = 1; j <= userN - i; j++) cout << " ";
            for (int k = 1; k <= 2 * i - 1; k++) cout << "*";
            cout << endl;
        }
    } else {
        cout << "请输入 1~20 之间的整数。" << endl;
    }
    cout << endl;
}

// ==================== 菜单系统 ====================

void show_menu() {
    cout << "========================================" << endl;
    cout << "  CSP-J 第10课：for 循环结构" << endl;
    cout << "========================================" << endl;
    cout << "  [1] for循环三要素详解 + 执行流程" << endl;
    cout << "  [2] 累加模式演示（1~n求和）" << endl;
    cout << "  [3] 累乘模式演示（阶乘）" << endl;
    cout << "  [4] 循环变量作用域演示" << endl;
    cout << "  [5] 嵌套循环 - 九九乘法表" << endl;
    cout << "  [6] 嵌套循环 - 图形打印" << endl;
    cout << "  [7] 循环次数计算演示" << endl;
    cout << "  [8] 因子枚举演示" << endl;
    cout << "  [9] 真题1：循环执行次数计算" << endl;
    cout << "  [10] 真题2：嵌套循环输出分析" << endl;
    cout << "  [0] 退出" << endl;
    cout << "========================================" << endl;
    cout << "请选择：";
}

// ==================== 主函数 ====================

int main() {
    int choice;

    do {
        show_menu();
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1: demo01_basic_for(); break;
            case 2: demo02_accumulate_sum(); break;
            case 3: demo03_accumulate_product(); break;
            case 4: demo04_scope(); break;
            case 5: demo05_multiplication_table(); break;
            case 6: demo06_pattern_printing(); break;
            case 7: demo07_loop_count(); break;
            case 8: demo08_factor_enumeration(); break;
            case 9: exam01_loop_count(); break;
            case 10: exam02_pyramid(); break;
            case 0:
                cout << "感谢学习！祝 CSP-J 备考顺利！" << endl;
                cout << "提示：第9-10课覆盖了分支选择与 for 循环两大核心结构，" << endl;
                cout << "      建议课后动手写一遍所有真题代码，加深理解。" << endl;
                break;
            default:
                cout << "无效选项，请重新选择！" << endl;
                break;
        }
    } while (choice != 0);

    return 0;
}
