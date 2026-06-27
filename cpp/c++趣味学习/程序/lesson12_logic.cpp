/*
 * =============================================
 * C++趣味学习 —— 第12课：逻辑大侦探——逻辑运算符
 * 知识点：&&、||、!、真值表
 * 趣味项目：🔎 破译逻辑密码
 * =============================================
 */

#include <iostream>
using namespace std;

int main() {
    // =============================================
    // 示例1：逻辑与(&&)——都要满足
    // 游乐园入园检查：要买票且身高够
    // =============================================
    cout << "========== 示例1：&& 逻辑与——游乐园入园检查 ==========" << endl;
    {
        bool has_ticket = true;
        int height = 130;

        cout << "入园条件：①买了票 ②身高 >= 120cm" << endl;
        cout << "买票了吗？ " << (has_ticket ? "买了✓" : "没买✗") << endl;
        cout << "身高多少？ " << height << "cm" << endl;
        cout << endl;

        // 使用 && 组合两个条件
        if (has_ticket && height >= 120) {
            cout << "✅ 欢迎进入游乐园！请尽情玩耍！" << endl;
        } else {
            cout << "❌ 抱歉，暂时不能进入。" << endl;
            if (!has_ticket) {
                cout << "   原因：还没买票哦～" << endl;
            }
            if (height < 120) {
                cout << "   原因：身高还不够呢，再长高点吧！" << endl;
            }
        }
    }
    cout << endl;

    // =============================================
    // 示例2：逻辑或(||)——满足一个就行
    // 周末活动选择器
    // =============================================
    cout << "========== 示例2：|| 逻辑或——周末活动选择器 ==========" << endl;
    {
        bool watch_tv = true;
        bool play_outside = false;
        bool read_book = true;

        cout << "周末可以做什么？" << endl;
        cout << "  看电视？    " << (watch_tv ? "可以✓" : "不行✗") << endl;
        cout << "  出去玩？    " << (play_outside ? "可以✓" : "不行✗") << endl;
        cout << "  看书？      " << (read_book ? "可以✓" : "不行✗") << endl;
        cout << endl;

        // || 只要有一个条件满足就是 true
        if (watch_tv || play_outside || read_book) {
            cout << "😊 至少有一件事可以做，周末不无聊！" << endl;
        } else {
            cout << "😴 什么都没安排，睡大觉吧！" << endl;
        }

        // 演示：如果全部是false
        cout << endl;
        cout << "----- 如果什么都不想做 -----" << endl;
        bool all_false = false || false || false;
        cout << "false || false || false = " << all_false << " （全假才假！）" << endl;
    }
    cout << endl;

    // =============================================
    // 示例3：逻辑非(!)——说反话
    // =============================================
    cout << "========== 示例3：! 逻辑非——说反话 ==========" << endl;
    {
        bool is_raining = false;
        bool is_sunny = true;

        cout << "下雨了吗？    " << (is_raining ? "是的🌧️" : "没有☀️") << endl;
        cout << "没下雨？（!） " << (!is_raining ? "对！没下雨" : "不对，下雨了") << endl;
        cout << endl;
        cout << "是晴天吗？    " << (is_sunny ? "是的☀️" : "不是🌧️") << endl;
        cout << "不是晴天？（!）" << (!is_sunny ? "对！不是晴天" : "不对，是晴天") << endl;
        cout << endl;

        // 展示 ! 的真值表
        cout << "----- ! 真值表 -----" << endl;
        cout << "!true  = " << !true  << "（真变假）" << endl;
        cout << "!false = " << !false << "（假变真）" << endl;

        // 双重否定
        cout << endl;
        cout << "----- 双重否定（!!）-----" << endl;
        bool value = true;
        cout << "value  = " << value << endl;
        cout << "!value = " << !value << "（取反一次）" << endl;
        cout << "!!value = " << !!value << "（取反两次，回到原样！）" << endl;
        cout << "就像：我不是不喜欢 = 我喜欢 😄" << endl;
    }
    cout << endl;

    // =============================================
    // 示例4：&& 和 || 的真值表演示
    // =============================================
    cout << "========== 示例4：真值表演示 ==========" << endl;
    {
        cout << "----- &&（与）真值表 -----" << endl;
        cout << "true  && true  = " << (true && true)   << "  ← 全真才真" << endl;
        cout << "true  && false = " << (true && false)  << "  ← 一假全假" << endl;
        cout << "false && true  = " << (false && true)  << "  ← 一假全假" << endl;
        cout << "false && false = " << (false && false) << "  ← 全假才假" << endl;
        cout << endl;

        cout << "----- ||（或）真值表 -----" << endl;
        cout << "true  || true  = " << (true || true)   << "  ← 一真全真" << endl;
        cout << "true  || false = " << (true || false)  << "  ← 一真全真" << endl;
        cout << "false || true  = " << (false || true)  << "  ← 一真全真" << endl;
        cout << "false || false = " << (false || false) << "  ← 全假才假" << endl;
    }
    cout << endl;

    // =============================================
    // 示例5：成绩区间判断
    // 比较运算符 + 逻辑运算符 = 黄金搭档
    // =============================================
    cout << "========== 示例5：成绩区间判断 ==========" << endl;
    {
        int score;
        cout << "请输入你的考试分数（0~100）：";
        cin >> score;
        cout << endl;

        // 使用 && 组合区间条件
        if (score >= 90 && score <= 100) {
            cout << "成绩：" << score << " 分" << endl;
            cout << "评价：优秀！太棒了！🏆" << endl;
        } else if (score >= 80 && score < 90) {
            cout << "成绩：" << score << " 分" << endl;
            cout << "评价：良好，保持住！👍" << endl;
        } else if (score >= 60 && score < 80) {
            cout << "成绩：" << score << " 分" << endl;
            cout << "评价：及格了，但还有进步空间！💪" << endl;
        } else if (score >= 0 && score < 60) {
            cout << "成绩：" << score << " 分" << endl;
            cout << "评价：这次没及格，下次一定要加油哦！📚" << endl;
        } else {
            cout << "分数不合法，请输入0~100之间的分数。" << endl;
        }
    }
    cout << endl;

    // =============================================
    // 练习1 参考答案：逻辑侦探考试
    // =============================================
    cout << "========== 练习1答案：逻辑侦探考试 ==========" << endl;
    {
        cout << "① true && false          → " << (true && false ? "true" : "false") << endl;
        cout << "② true || false          → " << (true || false ? "true" : "false") << endl;
        cout << "③ !true                  → " << (!true ? "true" : "false") << endl;
        cout << "④ (5>3) && (2<1)         → " << ((5 > 3) && (2 < 1) ? "true" : "false") << endl;
        cout << "⑤ (8==8) || (3>10)       → " << ((8 == 8) || (3 > 10) ? "true" : "false") << endl;
        cout << "⑥ !(4<=2)                → " << (!(4 <= 2) ? "true" : "false") << endl;
        cout << "⑦ (10>5)&&(6!=3)&&(7>=7) → " << ((10 > 5) && (6 != 3) && (7 >= 7) ? "true" : "false") << endl;
        cout << "⑧ false||false||true     → " << (false || false || true ? "true" : "false") << endl;
    }
    cout << endl;

    // =============================================
    // 练习3 参考答案：判断一个数是否在10到20之间
    // =============================================
    cout << "========== 练习3答案：区间判断 [10, 20] ==========" << endl;
    {
        int num;
        cout << "请输入一个整数：";
        cin >> num;

        // 判断是否在 [10, 20] 闭区间内
        if (num >= 10 && num <= 20) {
            cout << num << " 在10到20之间！✅" << endl;
        } else {
            cout << num << " 不在10到20之间。❌" << endl;
            if (num < 10) {
                cout << "（它比10小）" << endl;
            } else {
                cout << "（它比20大）" << endl;
            }
        }
    }
    cout << endl;

    // =============================================
    // 挑战任务 参考答案：闰年判断器
    // =============================================
    cout << "========== 挑战任务：🔍 闰年判断器 ==========" << endl;
    {
        int year;
        cout << "请输入一个年份：";
        cin >> year;
        cout << endl;

        // 闰年规则：
        // 1. 能被4整除，但不能被100整除
        // 2. 或者能被400整除
        // 公式：(year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)
        bool is_leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

        cout << "===== 判断结果 =====" << endl;
        cout << "年份：" << year << " 年" << endl;

        if (is_leap) {
            cout << "结果：是闰年！✅" << endl;
            cout << year << "年的2月有29天哦！" << endl;
        } else {
            cout << "结果：不是闰年。❌" << endl;
            cout << year << "年的2月有28天。" << endl;
        }

        // 详细判断过程
        cout << endl;
        cout << "----- 判断过程分解 -----" << endl;
        bool rule1 = (year % 4 == 0 && year % 100 != 0);
        bool rule2 = (year % 400 == 0);

        cout << year << " % 4 == 0 ?   " << (year % 4 == 0 ? "是" : "否") << endl;
        cout << year << " % 100 != 0 ? " << (year % 100 != 0 ? "是" : "否") << endl;
        cout << "  → 规则1（能被4整除 且 不能被100整除）：" << (rule1 ? "满足✅" : "不满足❌") << endl;
        cout << endl;
        cout << year << " % 400 == 0 ? " << (year % 400 == 0 ? "是" : "否") << endl;
        cout << "  → 规则2（能被400整除）：" << (rule2 ? "满足✅" : "不满足❌") << endl;
        cout << endl;
        cout << "最终判断（规则1 或 规则2）：" << (is_leap ? "闰年！" : "不是闰年。") << endl;
    }
    cout << endl;

    // =============================================
    // 程序结束
    // =============================================
    cout << "========== 程序结束 ==========" << endl;
    cout << "恭喜！你已经掌握了三种逻辑运算符！" << endl;
    cout << "记住口诀：" << endl;
    cout << "  && 全真才真，一假全假！" << endl;
    cout << "  || 一真全真，全假才假！" << endl;
    cout << "  !  真假颠倒，说反话！" << endl;

    return 0;
}
