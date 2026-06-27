/*
 * CSP-J 备考课程
 * 第8课：if-else 分支结构
 * 考纲知识点：单分支if、双分支if-else、多分支if-else if-else、嵌套if、悬空else问题
 *
 * 本文件包含：
 * 1. 三种分支结构演示
 * 2. 嵌套if
 * 3. 悬空else问题详解
 * 4. 成绩等级判定
 * 5. 闰年判断
 */

#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    cout << "========== CSP-J 第8课：if-else 分支结构 ==========" << endl;
    cout << endl;

    // ===== 一、单分支 if =====
    cout << "【一、单分支 if】" << endl;

    int score1 = 85;
    cout << "成绩: " << score1 << " → ";
    if (score1 >= 60) {
        cout << "及格" << endl;
    }

    int score2 = 55;
    cout << "成绩: " << score2 << " → ";
    if (score2 >= 60) {
        cout << "及格" << endl;
    } else {
        cout << "（无输出，因为条件不满足）" << endl;
    }
    cout << endl;

    // ===== 二、双分支 if-else =====
    cout << "【二、双分支 if-else】" << endl;

    int n;
    cout << "请输入一个整数: ";
    cin >> n;

    if (n % 2 == 0) {
        cout << n << " 是偶数" << endl;
    } else {
        cout << n << " 是奇数" << endl;
    }
    cout << endl;

    // ===== 三、多分支 if-else if-else =====
    cout << "【三、多分支 if-else if-else】" << endl;

    int grade_score;
    cout << "请输入成绩 (0-100): ";
    cin >> grade_score;

    // 注意：条件必须从严格到宽松排列！
    if (grade_score >= 90) {
        cout << "等级: A (优秀)" << endl;
    } else if (grade_score >= 80) {
        cout << "等级: B (良好)" << endl;
    } else if (grade_score >= 70) {
        cout << "等级: C (中等)" << endl;
    } else if (grade_score >= 60) {
        cout << "等级: D (及格)" << endl;
    } else {
        cout << "等级: E (不及格)" << endl;
    }
    cout << endl;

    // ===== 四、嵌套 if =====
    cout << "【四、嵌套 if 演示】" << endl;

    int a, b, c;
    cout << "请输入三个整数（空格分隔）: ";
    cin >> a >> b >> c;

    // 方法1：嵌套if找最大值
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
    cout << "最大值(嵌套if): " << maxVal << endl;

    // 方法2：使用 max 函数（更简洁）
    cout << "最大值(max函数): " << max({a, b, c}) << endl;

    // 排序三个数
    int x = a, y = b, z = c;
    if (x > y) swap(x, y);
    if (x > z) swap(x, z);
    if (y > z) swap(y, z);
    cout << "排序结果: " << x << " " << y << " " << z << endl;
    cout << endl;

    // ===== 五、悬空 else 问题（重点） =====
    cout << "【五、悬空 else 问题（考试重点）】" << endl;

    cout << "示例1: 不带花括号的嵌套if" << endl;
    int xx = 1, yy = 0;
    cout << "x=" << xx << ", y=" << yy << endl;

    cout << "执行: if(x>0) if(y>0) cout<<\"A\"; else cout<<\"B\";" << endl;
    cout << "输出: ";
    if (xx > 0)
        if (yy > 0)
            cout << "A" << endl;
        else
            cout << "B" << endl;
    cout << "解释: else与最近的if(y>0)匹配，y>0为false，所以输出B" << endl;
    cout << endl;

    cout << "示例2: 改变条件" << endl;
    int x2 = -1, y2 = 0;
    cout << "x=" << x2 << ", y=" << y2 << endl;
    cout << "执行: if(x>0) if(y>0) cout<<\"A\"; else cout<<\"B\";" << endl;
    cout << "输出: （无输出）";
    if (x2 > 0)
        if (y2 > 0)
            cout << "A" << endl;
        else
            cout << "B" << endl;
    cout << " (因为x>0为false，整个内层跳过)" << endl;
    cout << endl;

    cout << "示例3: 使用花括号明确范围（推荐）" << endl;
    int x3 = -1;
    if (x3 > 0) {  // 花括号明确外层
        if (yy > 0) {
            cout << "A" << endl;
        }
    } else {        // 这个else与外层if配对
        cout << "B (外层else)" << endl;
    }
    cout << endl;

    // ===== 六、闰年判断 =====
    cout << "【六、闰年判断】" << endl;

    int year;
    cout << "请输入年份: ";
    cin >> year;

    // 闰年条件：能被4整除但不能被100整除，或能被400整除
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        cout << year << " 是闰年" << endl;
    } else {
        cout << year << " 不是闰年（平年）" << endl;
    }
    cout << endl;

    // ===== 七、if 条件陷阱演示 =====
    cout << "【七、常见陷阱演示】" << endl;

    // 陷阱1：if后多加分号
    int trap1 = 10;
    cout << "陷阱1: if后多加分号" << endl;
    cout << "if(trap1 > 0); ← 分号构成空语句！" << endl;
    if (trap1 > 0);  // 空语句！下面代码无条件执行
    {
        cout << "这行代码会无条件执行（即使条件不满足）" << endl;
    }
    cout << endl;

    // 陷阱2：将=误写为==
    int trap2 = 0;
    cout << "陷阱2: if(trap2 = 5) ← 这是赋值，结果为5(非0=真)" << endl;
    if (trap2 = 5) {
        cout << "条件\"成立\"！而且trap2被改为: " << trap2 << endl;
    }
    cout << "正确写法: if(trap2 == 5)" << endl;
    cout << endl;

    // 陷阱3：浮点数直接==比较
    cout << "陷阱3: 浮点数比较" << endl;
    double d1 = 0.1 + 0.2;
    double d2 = 0.3;
    cout << "0.1 + 0.2 = " << d1 << endl;
    cout << "0.3 = " << d2 << endl;
    if (d1 == d2) {
        cout << "相等" << endl;
    } else {
        cout << "不相等! (浮点数精度问题)" << endl;
    }
    cout << "正确比较: fabs(d1 - d2) < 1e-9" << endl;

    cout << endl << "========== 第8课演示结束 ==========" << endl;
    return 0;
}
