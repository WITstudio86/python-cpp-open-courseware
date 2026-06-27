/*
 * C++趣味学习 - 第18课：数数我最行——for循环
 * 知识点：for三要素、循环变量、for与while对比
 * 项目：制作乘法口诀表
 */

#include <iostream>
#include <iomanip>
using namespace std;

// ============ 示例1：九九乘法口诀表 ============
void example1_multiplication_table() {
    cout << "════════════════════════════════" << endl;
    cout << "  示例1：📐 九九乘法口诀表" << endl;
    cout << "════════════════════════════════" << endl;

    cout << endl;
    // 表头
    cout << "      ";
    for (int col = 1; col <= 9; col++) {
        cout << "  " << col << "列 ";
    }
    cout << endl;
    cout << "     ┌─────────────────────────────────────────┐" << endl;

    for (int i = 1; i <= 9; i++) {
        cout << "  " << i << "行 │";
        for (int j = 1; j <= i; j++) {
            // setw(2)让每个乘积占2个字符宽度，对齐美观
            cout << " " << j << "×" << i << "=" << setw(2) << i * j;
        }
        cout << endl;
    }
    cout << endl;
}

// ============ 示例2：分数统计器 ============
void example2_score_statistics() {
    cout << "════════════════════════════════" << endl;
    cout << "  示例2：📊 分数统计器" << endl;
    cout << "════════════════════════════════" << endl;

    int count = 0;
    cout << "请输入学生人数：";
    cin >> count;

    if (count <= 0) {
        cout << "学生人数必须大于0！" << endl;
        return;
    }

    double score, total = 0;
    double maxScore = 0, minScore = 100;

    for (int i = 1; i <= count; i++) {
        cout << "请输入第" << i << "位同学的成绩（0-100）：";
        cin >> score;

        // 输入验证
        while (score < 0 || score > 100) {
            cout << "成绩必须在0-100之间，请重新输入：";
            cin >> score;
        }

        total += score;
        if (score > maxScore) maxScore = score;
        if (score < minScore) minScore = score;
    }

    cout << endl;
    cout << "┌──────────────────────┐" << endl;
    cout << "│      📊 成绩统计     │" << endl;
    cout << "├──────────────────────┤" << endl;
    cout << "│ 学生人数：" << setw(6) << count << "  │" << endl;
    cout << "│ 总分：   " << setw(8) << total << " │" << endl;
    cout << "│ 平均分： " << setw(8) << total / count << " │" << endl;
    cout << "│ 最高分： " << setw(8) << maxScore << " │" << endl;
    cout << "│ 最低分： " << setw(8) << minScore << " │" << endl;
    cout << "└──────────────────────┘" << endl;
    cout << endl;
}

// ============ 示例3：for和while的等价转换演示 ============
void example3_for_vs_while() {
    cout << "════════════════════════════════" << endl;
    cout << "  示例3：🔄 for与while等价转换" << endl;
    cout << "════════════════════════════════" << endl;

    cout << "使用for循环输出1到10：" << endl;
    for (int i = 1; i <= 10; i++) {
        cout << i << " ";
    }
    cout << endl;

    cout << "使用while循环输出1到10：" << endl;
    int j = 1;
    while (j <= 10) {
        cout << j << " ";
        j++;
    }
    cout << endl;

    cout << "✅ 两种写法输出完全一样！" << endl;
    cout << endl;
}

// ============ 练习答案 ============

// 练习1：打印1-100之间的偶数
void practice1_even_numbers() {
    cout << "════════════════════════════════" << endl;
    cout << "  练习1答案：打印1-100的偶数" << endl;
    cout << "════════════════════════════════" << endl;

    cout << "方法1（步长为2）：" << endl;
    int count = 0;
    for (int i = 2; i <= 100; i += 2) {
        cout << i << "\t";
        count++;
        if (count % 10 == 0) cout << endl;
    }
    cout << endl;

    cout << "方法2（取余判断）：" << endl;
    count = 0;
    for (int i = 1; i <= 100; i++) {
        if (i % 2 == 0) {
            cout << i << "\t";
            count++;
            if (count % 10 == 0) cout << endl;
        }
    }
    cout << endl << endl;
}

// 练习2：阶乘计算器
void practice2_factorial() {
    cout << "════════════════════════════════" << endl;
    cout << "  练习2答案：阶乘计算器" << endl;
    cout << "════════════════════════════════" << endl;

    int n;
    cout << "请输入n（n <= 20，防止溢出）：";
    cin >> n;

    if (n < 0) {
        cout << "阶乘只对非负整数定义！" << endl;
        return;
    }

    unsigned long long factorial = 1;  // 用unsigned long long防止溢出
    for (int i = 1; i <= n; i++) {
        factorial *= i;
    }

    cout << n << "! = " << factorial << endl;
    cout << endl;
}

// 练习3：自定义乘法表
void practice3_custom_table() {
    cout << "════════════════════════════════" << endl;
    cout << "  练习3答案：自定义乘法表" << endl;
    cout << "════════════════════════════════" << endl;

    int n;
    cout << "请输入一个数字n，输出1×n到9×n：";
    cin >> n;

    for (int i = 1; i <= 9; i++) {
        cout << i << " × " << n << " = " << i * n << endl;
    }
    cout << endl;
}

// ============ 挑战任务：斐波那契数列 ============
void challenge_fibonacci() {
    cout << "════════════════════════════════" << endl;
    cout << "  挑战任务：🐚 斐波那契数列" << endl;
    cout << "════════════════════════════════" << endl;

    int a = 1, b = 1, c;
    int count = 2;  // 已经有前两项了

    cout << "斐波那契数列前20项（每5个换行）：" << endl;
    cout << "----------------------------------------" << endl;

    // 先输出前两项
    cout << a << "\t" << b << "\t";

    for (int i = 3; i <= 20; i++) {
        c = a + b;  // 当前项 = 前两项之和
        cout << c << "\t";

        if (i % 5 == 0) cout << endl;

        // 更新前两项
        a = b;
        b = c;
    }

    cout << endl;
    cout << "----------------------------------------" << endl;
    cout << "🌟 斐波那契数列在自然界中随处可见：向日葵的种子排列、海螺的螺旋..." << endl;
    cout << endl;
}

// ============ 主函数 ============
int main() {
    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║  第18课：数数我最行——for循环           ║" << endl;
    cout << "║  知识点：for三要素、循环变量            ║" << endl;
    cout << "╚══════════════════════════════════════════╝" << endl;
    cout << endl;

    int choice;
    while (true) {
        cout << "请选择要运行的示例：" << endl;
        cout << "1. 九九乘法口诀表" << endl;
        cout << "2. 分数统计器" << endl;
        cout << "3. for与while等价转换" << endl;
        cout << "4. 练习1：打印1-100偶数" << endl;
        cout << "5. 练习2：阶乘计算器" << endl;
        cout << "6. 练习3：自定义乘法表" << endl;
        cout << "7. 🏆 挑战：斐波那契数列" << endl;
        cout << "0. 退出程序" << endl;
        cout << "请输入选择（0-7）：";
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1: example1_multiplication_table(); break;
            case 2: example2_score_statistics(); break;
            case 3: example3_for_vs_while(); break;
            case 4: practice1_even_numbers(); break;
            case 5: practice2_factorial(); break;
            case 6: practice3_custom_table(); break;
            case 7: challenge_fibonacci(); break;
            case 0:
                cout << "感谢学习！我们下一课再见！👋" << endl;
                return 0;
            default:
                cout << "无效选择，请重新输入！" << endl;
        }
    }
}
