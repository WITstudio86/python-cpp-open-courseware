/*
 * CSP-J 备考课程
 * 第8课：if-else 分支结构
 * 考纲知识点：单/双/多分支、嵌套 if、悬空 else、条件表达式
 *
 * 本文件模块：
 * 1. 单分支 if
 * 2. 双分支 if-else
 * 3. 多分支 if-else if-else（含错误顺序对比）
 * 4. 嵌套 if（三数最值与排序）
 * 5. 悬空 else（dangling-else）考点演示
 * 6. 闰年判断
 * 7. 条件表达式与常见陷阱
 * 8. 真题1：悬空 else 读程 AC
 * 9. 真题2：多分支顺序 / 成绩等级 AC
 * 10. 真题3：分段函数 AC
 *
 * 编译：g++ -std=c++17 -Wall -o lesson08 lesson08_if_else分支结构.cpp
 * 说明：悬空 else 演示可能触发 -Wdangling-else，已在注释中标明考点。
 */

#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
using namespace std;

// -------------------- 工具 --------------------
void print_divider(const string& title) {
    cout << "\n========================================\n";
    cout << "  " << title << '\n';
    cout << "========================================\n";
}

// -------------------- 演示 1：单分支 if --------------------
void demo01_single_if() {
    print_divider("演示1：单分支 if");

    int score1 = 85;
    cout << "成绩 " << score1 << " → ";
    if (score1 >= 60) {
        cout << "及格";
    }
    cout << '\n';

    int score2 = 55;
    cout << "成绩 " << score2 << " → ";
    if (score2 >= 60) {
        cout << "及格";
    } else {
        // 这里用 else 仅作对照说明“单分支时条件不成立则无输出”
        cout << "（单分支 if 时此处本可无输出；演示用 else 提示）";
    }
    cout << "\n\n要点：条件为真执行块，为假跳过，然后继续后续语句。\n";
}

// -------------------- 演示 2：双分支 if-else --------------------
void demo02_if_else() {
    print_divider("演示2：双分支 if-else");

    cout << "请输入一个整数：";
    int n;
    cin >> n;

    if (n % 2 == 0) {
        cout << n << " 是偶数\n";
    } else {
        cout << n << " 是奇数\n";
    }

    // 符号判断
    if (n > 0) {
        cout << "正数\n";
    } else if (n < 0) {
        cout << "负数\n";
    } else {
        cout << "零\n";
    }
}

// -------------------- 演示 3：多分支 --------------------
void demo03_multi_branch() {
    print_divider("演示3：多分支 if-else if-else");

    cout << "请输入成绩 (0-100)：";
    int score;
    cin >> score;

    cout << "\n【正确顺序：从严到宽】\n";
    if (score >= 90) {
        cout << "等级: A (优秀)\n";
    } else if (score >= 80) {
        cout << "等级: B (良好)\n";
    } else if (score >= 70) {
        cout << "等级: C (中等)\n";
    } else if (score >= 60) {
        cout << "等级: D (及格)\n";
    } else {
        cout << "等级: E (不及格)\n";
    }

    cout << "\n【错误顺序演示：从宽到严】\n";
    if (score >= 60) {
        cout << "错误链命中: 及格  （后面的良好/优秀不可达）\n";
    } else if (score >= 80) {
        cout << "良好\n";
    } else if (score >= 90) {
        cout << "优秀\n";
    } else {
        cout << "不及格\n";
    }

    cout << "结论：else if 命中即停，范围条件必须从严到宽。\n";
}

// -------------------- 演示 4：嵌套 if --------------------
void demo04_nested_if() {
    print_divider("演示4：嵌套 if");

    cout << "请输入三个整数（空格分隔）：";
    int a, b, c;
    cin >> a >> b >> c;

    int maxVal;
    if (a >= b) {
        if (a >= c) {
            maxVal = a;
        } else {
            maxVal = c;
        }
    } else {
        if (b >= c) {
            maxVal = b;
        } else {
            maxVal = c;
        }
    }
    cout << "最大值(嵌套 if) = " << maxVal << '\n';
    cout << "最大值(max 函数) = " << max({a, b, c}) << '\n';

    int x = a, y = b, z = c;
    if (x > y) swap(x, y);
    if (x > z) swap(x, z);
    if (y > z) swap(y, z);
    cout << "升序排序: " << x << ' ' << y << ' ' << z << '\n';

    // 象限判断：嵌套 vs 拍平
    cout << "\n以 (a,b) 做平面象限判断：\n";
    if (a == 0 || b == 0) {
        cout << "在坐标轴上\n";
    } else if (a > 0) {
        if (b > 0) cout << "第一象限\n";
        else cout << "第四象限\n";
    } else {
        if (b > 0) cout << "第二象限\n";
        else cout << "第三象限\n";
    }
}

// -------------------- 演示 5：悬空 else（重点） --------------------
void demo05_dangling_else() {
    print_divider("演示5：悬空 else（dangling else）");

    cout << "规则：else 与最近的、尚未配对的 if 匹配（与缩进无关）。\n\n";

    // ========== 考点：悬空 else ==========
    // 下列无花括号嵌套可能触发编译器警告：-Wdangling-else
    // 这是 CSP-J 读程高频考点，故保留“危险写法”用于演示语义。
    cout << "【示例1】x=1, y=0\n";
    cout << "代码：if(x>0) if(y>0) cout<<\"A\"; else cout<<\"B\";\n";
    int xx = 1, yy = 0;
    cout << "输出: ";
    if (xx > 0)
        if (yy > 0)
            cout << "A\n";
        else
            cout << "B\n";  // 匹配内层 if(y>0)
    cout << "解释: else 匹配 if(y>0)；y 不大于 0，故输出 B。\n\n";

    cout << "【示例2】x=-1, y=0（危险写法下应无输出）\n";
    int x2 = -1, y2 = 0;
    cout << "输出: ";
    // 考点代码（可能 -Wdangling-else）：else 仍匹配内层 if(y2>0)
    if (x2 > 0)
        if (y2 > 0)
            cout << "A";
        else
            cout << "B";
    // x2>0 为假 → 内层整段跳过，上面两个 cout 都不执行
    cout << "（无输出）\n";
    cout << "解释: 外层 x>0 为假，整个内层 if-else 被跳过。\n\n";

    cout << "【示例3】正确写法：花括号明确配对外层 else\n";
    int x3 = -1;
    if (x3 > 0) {
        if (yy > 0) {
            cout << "A\n";
        }
    } else {
        cout << "B (外层 else)\n";
    }

    cout << "\n【示例4】正确写法：花括号明确配对内层 else\n";
    int x4 = 5, y4 = 0;
    if (x4 > 0) {
        if (y4 > 0) {
            cout << "A\n";
        } else {
            cout << "B (内层 else)\n";
        }
    }

    cout << "\n建议：任何嵌套 if 都写 {}，从根源消灭悬空 else 歧义。\n";
}

// -------------------- 演示 6：闰年 --------------------
void demo06_leap_year() {
    print_divider("演示6：闰年判断");

    cout << "请输入年份：";
    int year;
    cin >> year;

    // 能被4整除且不能被100整除，或能被400整除
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        cout << year << " 是闰年\n";
    } else {
        cout << year << " 不是闰年（平年）\n";
    }

    cout << "\n自测参考：2000 闰，1900 平，2024 闰，2023 平。\n";
}

// -------------------- 演示 7：条件与陷阱 --------------------
void demo07_condition_traps() {
    print_divider("演示7：条件表达式与常见陷阱");

    // 陷阱1：if 后分号
    cout << "【陷阱1】if 后多加分号\n";
    int trap1 = -5;
    cout << "trap1=" << trap1 << "\n";
    if (trap1 > 0);  // 空语句！
    {
        cout << "花括号内无条件执行（即使条件为假）\n";
    }
    cout << '\n';

    // 陷阱2：= 与 ==
    cout << "【陷阱2】if (x = 5) 是赋值\n";
    int trap2 = 0;
    if (trap2 = 5) {
        cout << "条件“成立”，且 trap2 被改成 " << trap2 << '\n';
    }
    cout << "正确：if (trap2 == 5)\n\n";

    // 陷阱3：浮点比较
    cout << "【陷阱3】浮点数 == 比较\n";
    double d1 = 0.1 + 0.2;
    double d2 = 0.3;
    cout << "0.1+0.2 = " << d1 << ", 0.3 = " << d2 << '\n';
    if (d1 == d2) {
        cout << "直接 == ：相等\n";
    } else {
        cout << "直接 == ：不相等（精度问题）\n";
    }
    if (fabs(d1 - d2) < 1e-9) {
        cout << "近似比较 fabs(d1-d2)<1e-9 ：视为相等\n";
    }
    cout << '\n';

    // 陷阱4：优先级
    cout << "【陷阱4】&& 优先于 ||\n";
    int a = 0, b = 1, c = 1;
    bool r = a > 0 || b > 0 && c > 0;  // a>0 || (b>0 && c>0)
    cout << "a=0,b=1,c=1;  a>0 || b>0 && c>0  → " << r
         << " （等价于 a>0 || (b>0 && c>0)）\n";

    // 非零为真
    cout << "\n【补充】非零为真\n";
    int k = 3;
    if (k) cout << "if(k) 当 k=3 时为真\n";
    if (k % 2) cout << "if(k%2) 奇数时为真\n";
}

// -------------------- 演示 8：票价 / 复合条件 --------------------
void demo08_ticket_price() {
    print_divider("演示8：分段票价（复合多分支）");

    cout << "请输入年龄：";
    int age;
    cin >> age;

    int price;
    if (age < 0) {
        cout << "年龄非法\n";
        return;
    } else if (age < 6) {
        price = 0;
    } else if (age <= 12) {
        price = 20;
    } else if (age < 60) {
        price = 40;
    } else {
        price = 20;  // 老人优惠
    }
    cout << "票价 = " << price << " 元\n";
}

// -------------------- 真题 1：悬空 else --------------------
void exam01_dangling_else() {
    print_divider("真题1：悬空 else 读程（AC）");
    cout << "原题：x=5,y=0; if(x>0) if(y>0) A; else B;\n";
    cout << "标准答案：B\n\n";

    int x = 5, y = 0;
    cout << "运行输出：";
    // 考点代码（可能 -Wdangling-else）：else 匹配内层 if(y>0)
    if (x > 0)
        if (y > 0)
            cout << "A" << endl;
        else
            cout << "B" << endl;

    cout << "\n正确加括号（语义同原题，消除警告）：\n";
    if (x > 0) {
        if (y > 0) {
            cout << "A" << endl;
        } else {
            cout << "B" << endl;
        }
    }
}

// -------------------- 真题 2：成绩等级（正确顺序） --------------------
void exam02_grade() {
    print_divider("真题2：成绩多分支（AC）");
    cout << "请输入成绩，将按正确顺序输出等级：";
    int score;
    cin >> score;

    // AC：从严到宽
    if (score >= 90) {
        cout << "优秀\n";
    } else if (score >= 80) {
        cout << "良好\n";
    } else if (score >= 60) {
        cout << "及格\n";
    } else {
        cout << "不及格\n";
    }

    cout << "\n对照：若错误地把 >=60 放第一，输入 85 会得到“及格”。\n";
}

// -------------------- 真题 3：分段函数 --------------------
void exam03_piecewise() {
    print_divider("真题3：分段函数（AC）");
    cout << "y = x (x<1);  2x-1 (1<=x<10);  3x-11 (x>=10)\n";
    cout << "请输入整数 x：";
    int x;
    cin >> x;

    int y;
    if (x < 1) {
        y = x;
    } else if (x < 10) {
        y = 2 * x - 1;
    } else {
        y = 3 * x - 11;
    }
    cout << "y = " << y << '\n';
}

// -------------------- 真题 4：闰年 Y/N --------------------
void exam04_leap_yn() {
    print_divider("真题4：闰年 Y/N（AC）");
    cout << "请输入年份：";
    int year;
    cin >> year;

    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        cout << "Y\n";
    } else {
        cout << "N\n";
    }
}

// -------------------- 附加：三数关系分类 --------------------
void demo09_triangle_type() {
    print_divider("附加：三角形类型判断");
    cout << "请输入三边 a b c：";
    int a, b, c;
    cin >> a >> b >> c;

    // 排序便于判断
    if (a > b) swap(a, b);
    if (a > c) swap(a, c);
    if (b > c) swap(b, c);

    if (a + b <= c) {
        cout << "不能构成三角形\n";
    } else if (a == b && b == c) {
        cout << "等边三角形\n";
    } else if (a == b || b == c) {
        cout << "等腰三角形\n";
    } else if (a * a + b * b == c * c) {
        cout << "直角三角形\n";
    } else {
        cout << "一般三角形\n";
    }
}

// -------------------- 菜单 --------------------
void show_menu() {
    cout << "\n========================================\n";
    cout << "  CSP-J 第8课：if-else 分支结构\n";
    cout << "========================================\n";
    cout << "  [1] 单分支 if\n";
    cout << "  [2] 双分支 if-else\n";
    cout << "  [3] 多分支 if-else if（含错误顺序）\n";
    cout << "  [4] 嵌套 if（最值/排序/象限）\n";
    cout << "  [5] 悬空 else 专题（含 -Wdangling-else 考点）\n";
    cout << "  [6] 闰年判断\n";
    cout << "  [7] 条件表达式与陷阱\n";
    cout << "  [8] 分段票价\n";
    cout << "  [9] 真题1：悬空 else 读程\n";
    cout << "  [10] 真题2：成绩等级 AC\n";
    cout << "  [11] 真题3：分段函数 AC\n";
    cout << "  [12] 真题4：闰年 Y/N AC\n";
    cout << "  [13] 附加：三角形类型\n";
    cout << "  [0] 退出\n";
    cout << "========================================\n";
    cout << "请选择：";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int choice = -1;
    do {
        show_menu();
        if (!(cin >> choice)) {
            break;
        }
        cout << '\n';

        switch (choice) {
            case 1: demo01_single_if(); break;
            case 2: demo02_if_else(); break;
            case 3: demo03_multi_branch(); break;
            case 4: demo04_nested_if(); break;
            case 5: demo05_dangling_else(); break;
            case 6: demo06_leap_year(); break;
            case 7: demo07_condition_traps(); break;
            case 8: demo08_ticket_price(); break;
            case 9: exam01_dangling_else(); break;
            case 10: exam02_grade(); break;
            case 11: exam03_piecewise(); break;
            case 12: exam04_leap_yn(); break;
            case 13: demo09_triangle_type(); break;
            case 0:
                cout << "感谢学习第8课！下一课：switch-case 多分支。\n";
                break;
            default:
                cout << "无效选项，请输入 0-13。\n";
                break;
        }
    } while (choice != 0);

    return 0;
}
