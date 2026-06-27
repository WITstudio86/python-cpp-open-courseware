/*
 * CSP-J 备考课程
 * 第9课：switch-case 多分支结构
 * 考纲知识点：switch-case语法结构、break的作用（穿透现象）、default分支、
 *            switch与if-else选择策略、嵌套switch
 *
 * 本文件包含：
 * 1. 基础语法演示（星期几输出）
 * 2. 穿透现象演示（有意 vs 无意）
 * 3. 合并case演示（元音字母判断、月份天数）
 * 4. 嵌套switch演示（两级分类）
 * 5. 真题1：简单计算器（AC代码）
 * 6. 真题2：成绩等级转换（AC代码）
 * 7. 表达式类型对比（switch vs if-else）
 */

#include <iostream>
#include <cstdio>
using namespace std;

// ==================== 演示函数 ====================

// 1. 基础语法演示：根据数字输出星期几
void demo01_basic_syntax() {
    cout << "=== 演示1：基础语法 - 星期几输出 ===" << endl;
    cout << "请输入数字 1-7：";
    int day;
    cin >> day;

    switch (day) {
        case 1: cout << "星期一" << endl; break;
        case 2: cout << "星期二" << endl; break;
        case 3: cout << "星期三" << endl; break;
        case 4: cout << "星期四" << endl; break;
        case 5: cout << "星期五" << endl; break;
        case 6: cout << "星期六" << endl; break;
        case 7: cout << "星期日" << endl; break;
        default: cout << "输入错误！请输入 1-7。" << endl; break;
    }
    cout << endl;
}

// 2. 穿透现象演示：展示忘记 break 的后果
void demo02_fallthrough() {
    cout << "=== 演示2：穿透现象（Fall-through） ===" << endl;
    cout << "代码：" << endl;
    cout << "  switch (x) {" << endl;
    cout << "      case 1: cout << \"A\";" << endl;
    cout << "      case 2: cout << \"B\";" << endl;
    cout << "      case 3: cout << \"C\";" << endl;
    cout << "      default: cout << \"D\";" << endl;
    cout << "  }" << endl;
    cout << endl;

    for (int x = 1; x <= 4; x++) {
        cout << "x = " << x << " 时，输出：";
        switch (x) {
            case 1: cout << "A";
            case 2: cout << "B";
            case 3: cout << "C";
            default: cout << "D";
        }
        cout << endl;
    }
    cout << "结论：忘记 break 会导致意外穿透，输出多余的字符！" << endl;
    cout << endl;
}

// 3. 合并 case 演示1：元音/辅音字母判断
void demo03_merge_case_vowels() {
    cout << "=== 演示3：合并 case - 元音字母判断 ===" << endl;
    cout << "请输入一个英文字母：";
    char ch;
    cin >> ch;

    switch (ch) {
        case 'a': case 'e': case 'i': case 'o': case 'u':
        case 'A': case 'E': case 'I': case 'O': case 'U':
            cout << "\'" << ch << "\' 是元音字母" << endl;
            break;
        default:
            if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
                cout << "\'" << ch << "\' 是辅音字母" << endl;
            } else {
                cout << "输入的不是英文字母！" << endl;
            }
            break;
    }
    cout << endl;
}

// 4. 合并 case 演示2：月份天数
void demo04_merge_case_months() {
    cout << "=== 演示4：合并 case - 月份天数 ===" << endl;
    cout << "请输入月份 1-12：";
    int month;
    cin >> month;

    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            cout << month << "月有 31 天" << endl;
            break;
        case 4: case 6: case 9: case 11:
            cout << month << "月有 30 天" << endl;
            break;
        case 2:
            cout << month << "月有 28 天或 29 天（闰年）" << endl;
            break;
        default:
            cout << "无效的月份！请输入 1-12。" << endl;
            break;
    }
    cout << endl;
}

// 5. 嵌套 switch 演示：两级分类
void demo05_nested_switch() {
    cout << "=== 演示5：嵌套 switch - 两级分类 ===" << endl;
    cout << "一级分类：1-电子产品  2-食品  3-服装" << endl;
    cout << "请输入一级分类编号：";
    int category;
    cin >> category;
    cout << "二级分类编号：";
    int subType;
    cin >> subType;

    switch (category) {
        case 1:  // 电子产品
            cout << "分类：电子产品 -> ";
            switch (subType) {
                case 1: cout << "手机" << endl; break;
                case 2: cout << "电脑" << endl; break;
                case 3: cout << "平板" << endl; break;
                case 4: cout << "耳机" << endl; break;
                default: cout << "其他电子产品" << endl; break;
            }
            break;
        case 2:  // 食品
            cout << "分类：食品 -> ";
            switch (subType) {
                case 1: cout << "水果" << endl; break;
                case 2: cout << "蔬菜" << endl; break;
                case 3: cout << "肉类" << endl; break;
                case 4: cout << "饮料" << endl; break;
                default: cout << "其他食品" << endl; break;
            }
            break;
        case 3:  // 服装
            cout << "分类：服装 -> ";
            switch (subType) {
                case 1: cout << "上衣" << endl; break;
                case 2: cout << "裤子" << endl; break;
                case 3: cout << "鞋子" << endl; break;
                case 4: cout << "配饰" << endl; break;
                default: cout << "其他服装" << endl; break;
            }
            break;
        default:
            cout << "无效的一级分类！" << endl;
            break;
    }
    cout << endl;
}

// 6. switch vs if-else 选择策略对比
void demo06_switch_vs_ifelse() {
    cout << "=== 演示6：switch vs if-else 选择策略 ===" << endl;
    cout << "本演示展示两种场景的对比。" << endl;
    cout << endl;

    // 场景A：离散值——适合 switch
    cout << "【场景A：离散值判断 - 适合 switch】" << endl;
    cout << "请输入操作符 (+, -, *, /)：";
    char op;
    cin >> op;

    cout << "使用 switch 实现：" << endl;
    switch (op) {
        case '+': cout << "  加法运算" << endl; break;
        case '-': cout << "  减法运算" << endl; break;
        case '*': cout << "  乘法运算" << endl; break;
        case '/': cout << "  除法运算" << endl; break;
        default: cout << "  无效操作符" << endl; break;
    }
    cout << endl;

    // 场景B：范围判断——只能用 if-else
    cout << "【场景B：范围判断 - 只能用 if-else】" << endl;
    cout << "请输入分数 (0-100)：";
    int score;
    cin >> score;

    cout << "使用 if-else 实现：" << endl;
    if (score >= 90 && score <= 100) {
        cout << "  等级：A (优秀)" << endl;
    } else if (score >= 80) {
        cout << "  等级：B (良好)" << endl;
    } else if (score >= 70) {
        cout << "  等级：C (中等)" << endl;
    } else if (score >= 60) {
        cout << "  等级：D (及格)" << endl;
    } else if (score >= 0) {
        cout << "  等级：F (需要努力)" << endl;
    } else {
        cout << "  无效分数！" << endl;
    }
    cout << "注意：范围判断不能使用 switch，因为 case 后必须是常量。" << endl;
    cout << endl;
}

// ==================== 真题 AC 代码 ====================

// 真题1：简单计算器
void exam01_calculator() {
    cout << "=== 真题1：简单计算器 ===" << endl;
    cout << "输入格式：a op b（如 10 + 5）" << endl;
    cout << "请输入表达式：";

    int a, b;
    char op;
    cin >> a >> op >> b;

    switch (op) {
        case '+':
            cout << a << " + " << b << " = " << a + b << endl;
            break;
        case '-':
            cout << a << " - " << b << " = " << a - b << endl;
            break;
        case '*':
            cout << a << " * " << b << " = " << a * b << endl;
            break;
        case '/':
            if (b == 0) {
                cout << "Error: Division by zero" << endl;
            } else {
                cout << a << " / " << b << " = " << a / b << endl;
            }
            break;
        default:
            cout << "Error: Invalid operator" << endl;
            break;
    }
    cout << endl;
}

// 真题2：成绩等级转换
void exam02_grade_conversion() {
    cout << "=== 真题2：成绩等级转换 ===" << endl;
    cout << "请输入成绩等级 (A/B/C/D/F)：";

    char grade;
    cin >> grade;

    switch (grade) {
        case 'A': case 'a':
            cout << "90-100 优秀" << endl;
            break;
        case 'B': case 'b':
            cout << "80-89 良好" << endl;
            break;
        case 'C': case 'c':
            cout << "70-79 中等" << endl;
            break;
        case 'D': case 'd':
            cout << "60-69 及格" << endl;
            break;
        case 'F': case 'f':
            cout << "0-59 需要努力" << endl;
            break;
        default:
            cout << "无效等级" << endl;
            break;
    }
    cout << endl;
}

// ==================== 菜单系统 ====================

void show_menu() {
    cout << "========================================" << endl;
    cout << "  CSP-J 第9课：switch-case 多分支结构" << endl;
    cout << "========================================" << endl;
    cout << "  [1] 基础语法演示（星期几输出）" << endl;
    cout << "  [2] 穿透现象演示" << endl;
    cout << "  [3] 合并 case - 元音字母判断" << endl;
    cout << "  [4] 合并 case - 月份天数" << endl;
    cout << "  [5] 嵌套 switch 演示" << endl;
    cout << "  [6] switch vs if-else 选择策略" << endl;
    cout << "  [7] 真题1：简单计算器" << endl;
    cout << "  [8] 真题2：成绩等级转换" << endl;
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
            case 1: demo01_basic_syntax(); break;
            case 2: demo02_fallthrough(); break;
            case 3: demo03_merge_case_vowels(); break;
            case 4: demo04_merge_case_months(); break;
            case 5: demo05_nested_switch(); break;
            case 6: demo06_switch_vs_ifelse(); break;
            case 7: exam01_calculator(); break;
            case 8: exam02_grade_conversion(); break;
            case 0:
                cout << "感谢学习！祝 CSP-J 备考顺利！" << endl;
                break;
            default:
                cout << "无效选项，请重新选择！" << endl;
                break;
        }
    } while (choice != 0);

    return 0;
}
