/*
 * =============================================
 * C++趣味学习 —— 第16课：万能开关——switch语句
 * 知识点：switch-case结构、break的作用、default分支
 * 趣味项目：🍔 自动点餐机
 * 阶段：第三单元——选择与决策
 * =============================================
 */

#include <iostream>
using namespace std;

int main() {

    // ==========================================
    // 示例1：基本switch —— 星期几翻译器
    // 功能：输入数字1-7，输出对应的星期几（中英文）
    // 重点：每个case后面必须用冒号(:)，不是分号(;)！
    //       每个case结尾要有break跳出switch
    // ==========================================
    cout << "========== 示例1：星期几翻译器 ==========" << endl;
    {
        int day = 3;  // 可以修改1-7测试不同结果

        cout << "输入数字：" << day << endl;
        cout << "翻译结果：";

        // switch(变量)：把变量和每个case后面的值比较
        // 匹配到哪个，就从哪个开始执行
        switch (day) {
            case 1:    // ← 这里是冒号 : 不是分号 ; !!
                cout << "星期一 Monday —— 新的一周，元气满满！💪" << endl;
                break;  // ← break：跳出switch，防止"穿透"到下一个case

            case 2:
                cout << "星期二 Tuesday —— 渐入佳境，认真学习！📚" << endl;
                break;

            case 3:
                cout << "星期三 Wednesday —— 一周过半，继续加油！🎯" << endl;
                break;

            case 4:
                cout << "星期四 Thursday —— 胜利在望，坚持就是胜利！⭐" << endl;
                break;

            case 5:
                cout << "星期五 Friday —— 最后一天，明天就周末啦！🎉" << endl;
                break;

            case 6:
                cout << "星期六 Saturday —— 周末愉快，尽情玩耍！🎮" << endl;
                break;

            case 7:
                cout << "星期日 Sunday —— 好好休息，养精蓄锐！😴" << endl;
                break;

            default:   // ← default：所有case都不匹配时执行
                cout << "❌ 输入错误！请输入1-7之间的数字。" << endl;
                break;   // default后面也建议加break（好习惯）
        }
    }
    cout << endl;
    cout << endl;

    // ==========================================
    // 示例2：switch的"穿透"现象演示
    // 功能：对比有break和没有break的区别
    // 重点：没有break时，会从匹配的case一路往下执行
    //       （这就是"穿透"——fall-through）
    // ==========================================
    cout << "========== 示例2：穿透现象演示 ==========" << endl;

    // --- 演示A：没有break的穿透 ---
    cout << "--- A. 没有break（穿透警告！）---" << endl;
    {
        int num = 2;
        cout << "num = " << num << "，switch结果：" << endl;

        switch (num) {
            case 1:
                cout << "  执行了 case 1" << endl;
                // 没有break！继续往下穿透！
            case 2:
                cout << "  执行了 case 2" << endl;
                // 没有break！继续往下穿透！
            case 3:
                cout << "  执行了 case 3" << endl;
                // 没有break！继续往下穿透！
            case 4:
                cout << "  执行了 case 4" << endl;
                // 最后一个case，虽然没有break，但switch到此结束
            default:
                cout << "  执行了 default" << endl;
        }
        cout << "  ⚠️ 看！num=2匹配了case 2，但case 3、4、default都执行了！" << endl;
        cout << "     这就是\"穿透\"——因为没有break来\"刹车\"！" << endl;
    }
    cout << endl;

    // --- 演示B：有break的正常情况 ---
    cout << "--- B. 有break（正常情况）---" << endl;
    {
        int num = 2;
        cout << "num = " << num << "，switch结果：" << endl;

        switch (num) {
            case 1:
                cout << "  执行了 case 1" << endl;
                break;   // ← break刹车！跳出switch
            case 2:
                cout << "  执行了 case 2" << endl;
                break;   // ← break刹车！跳出switch
            case 3:
                cout << "  执行了 case 3" << endl;
                break;
            case 4:
                cout << "  执行了 case 4" << endl;
                break;
            default:
                cout << "  执行了 default" << endl;
                break;
        }
        cout << "  ✅ 这次只执行了匹配的case 2，后面的都没执行！" << endl;
        cout << "     break成功\"刹车\"，阻止了穿透！" << endl;
    }
    cout << endl;

    // --- 演示C：巧妙利用穿透 —— 多个case做同一件事 ---
    cout << "--- C. 巧用穿透：判断工作日/周末 ---" << endl;
    {
        int day = 3;  // 可以改成6或7测试
        cout << "今天是星期" << day << "，";

        switch (day) {
            case 1:   // 这里故意没有break和代码
            case 2:   // 穿透下来
            case 3:   // 穿透下来
            case 4:   // 穿透下来
            case 5:   // 穿透下来，所有工作日汇聚到一起
                cout << "是工作日，要认真上课哦！📖" << endl;
                break;   // 工作日判断完毕，break跳出

            case 6:   // 没有break，穿透
            case 7:   // 周末汇聚
                cout << "是周末，可以休息玩耍啦！🎮" << endl;
                break;

            default:
                cout << "输入错误！" << endl;
                break;
        }
        cout << "  💡 这里故意让case 1-5\"穿透\"，共用同一段代码，非常巧妙！" << endl;
    }
    cout << endl;
    cout << endl;

    // ==========================================
    // 示例3：自动点餐机（基础版）
    // 功能：显示菜单，用户选择序号，输出菜品和价格
    // 重点：switch处理具体的菜单选项，default处理无效输入
    // ==========================================
    cout << "========== 示例3：自动点餐机 ==========" << endl;
    {
        int choice = 3;  // 可以修改1-5测试不同菜品

        cout << "📋 菜单：" << endl;
        cout << "  1. 🍔 汉堡  —— 15元" << endl;
        cout << "  2. 🍟 薯条  ——  8元" << endl;
        cout << "  3. 🥤 可乐  ——  5元" << endl;
        cout << "  4. 🍦 冰淇淋 ——  6元" << endl;
        cout << "  5. 🍗 鸡翅  —— 12元" << endl;
        cout << endl;
        cout << "您选择了序号：" << choice << endl;

        switch (choice) {
            case 1:
                cout << "✅ 点餐成功！🍔 汉堡 ×1 = 15元" << endl;
                break;
            case 2:
                cout << "✅ 点餐成功！🍟 薯条 ×1 = 8元" << endl;
                break;
            case 3:
                cout << "✅ 点餐成功！🥤 可乐 ×1 = 5元" << endl;
                break;
            case 4:
                cout << "✅ 点餐成功！🍦 冰淇淋 ×1 = 6元" << endl;
                break;
            case 5:
                cout << "✅ 点餐成功！🍗 鸡翅 ×1 = 12元" << endl;
                break;
            default:
                cout << "❌ 抱歉，没有这个菜品！请输入1-5之间的序号。" << endl;
                break;
        }
    }
    cout << endl;
    cout << endl;

    // ==========================================
    // 练习1答案：星期翻译官
    // 要求：输入1-7，输出中文星期几
    // ==========================================
    cout << "========== 练习1答案：星期翻译官 ==========" << endl;
    {
        int day = 5;
        cout << "输入数字：" << day << " → ";

        switch (day) {
            case 1: cout << "星期一" << endl; break;
            case 2: cout << "星期二" << endl; break;
            case 3: cout << "星期三" << endl; break;
            case 4: cout << "星期四" << endl; break;
            case 5: cout << "星期五" << endl; break;
            case 6: cout << "星期六" << endl; break;
            case 7: cout << "星期日" << endl; break;
            default: cout << "输入错误！请输入1-7。" << endl; break;
        }
    }
    cout << endl;
    cout << endl;

    // ==========================================
    // 练习2答案：穿透大考验分析
    // 代码：n=3, switch(n) { case1:A case2:B case3:C case4:D case5:E }
    // 问题：所有case都没有break！
    // 结果：从case 3匹配开始，输出 C D E
    // 解释：A和B不会输出，因为switch从匹配的case开始执行，
    //       不是从头开始！所以1和2被跳过了。
    // ==========================================
    cout << "========== 练习2答案：穿透大考验 ==========" << endl;
    cout << "原题：n=3，所有case都没有break" << endl;
    cout << endl;
    cout << "实际输出（模拟）：" << endl;
    {
        int n = 3;
        switch (n) {
            case 1: cout << "A";
            case 2: cout << "B";
            case 3: cout << "C";
            case 4: cout << "D";
            case 5: cout << "E";
        }
        cout << endl;
    }
    cout << endl;
    cout << "答案分析：" << endl;
    cout << "  输出：CDE" << endl;
    cout << "  原因1：n=3，从case 3开始匹配，跳过case 1和2" << endl;
    cout << "  原因2：所有case都没有break，所以case 3执行完后" << endl;
    cout << "         穿透到case 4（输出D），再穿透到case 5（输出E）" << endl;
    cout << "  注意：A和B没有被输出！因为switch不是从头开始执行的！" << endl;
    cout << endl;
    cout << endl;

    // ==========================================
    // 练习3分析：switch vs if-else 的选择
    // 问题：成绩等级评定（>=90→A, >=80→B...）能用switch吗？
    // 答案：不适合用switch！
    // 原因：switch只能判断"等于具体值"，不能判断"大于等于范围"
    //       如果硬要用switch，需要写100个case(0-100)，不现实
    //       正确选择：判断范围用if-else，判断具体值用switch
    // ==========================================
    cout << "========== 练习3分析：switch vs if-else ==========" << endl;
    cout << "问题：成绩等级评定能用switch改写吗？" << endl;
    cout << endl;
    cout << "答案：❌ 不适合！" << endl;
    cout << endl;
    cout << "原因分析：" << endl;
    cout << "  1. 等级是基于分数\"范围\"判断的：" << endl;
    cout << "     90-100→A, 80-89→B, 70-79→C, 60-69→D, 0-59→E" << endl;
    cout << "  2. switch只能判断\"是否等于某个具体值\"" << endl;
    cout << "     比如 case 95: 它是精确值，不是范围" << endl;
    cout << "  3. 如果硬要用switch，需要写100个case：" << endl;
    cout << "     case 90: case 91: ... case 100: cout << \"A\";" << endl;
    cout << "     这显然不现实，也不是好的编程习惯！" << endl;
    cout << endl;
    cout << "选择原则总结：" << endl;
    cout << "  ├─ 判断\"等于具体值\" → 用 switch  ✅" << endl;
    cout << "  │  例：菜单选项(1-5)、星期几(1-7)、等级(ABCD)" << endl;
    cout << "  └─ 判断\"大于小于范围\" → 用 if-else  ✅" << endl;
    cout << "     例：分数等级(>=90)、温度范围、年龄阶段" << endl;
    cout << endl;
    cout << endl;

    // ==========================================
    // 挑战任务：完整自动点餐机（交互版）
    // 功能：
    //   1. 显示精美菜单
    //   2. 用户选择菜品序号
    //   3. switch判断菜品并记录价格
    //   4. 用户输入数量
    //   5. 计算总价并输出订单详情
    // ==========================================
    cout << "========== 挑战任务：完整自动点餐机 ==========" << endl;
    {
        int choice, quantity;
        double price = 0;
        string itemName = "";       // 菜品名称
        string itemEmoji = "";      // 菜品对应的emoji

        // --- 显示菜单 ---
        cout << "🍔 ═══════════════════════ 🍔" << endl;
        cout << "    欢迎来到 自动点餐机！    " << endl;
        cout << "═══════════════════════════" << endl;
        cout << endl;
        cout << "  📋 今日菜单：" << endl;
        cout << "  ┌────┬──────────┬──────┐" << endl;
        cout << "  │序号│   菜品   │ 价格 │" << endl;
        cout << "  ├────┼──────────┼──────┤" << endl;
        cout << "  │ 1  │ 🍔 汉堡  │ 15元 │" << endl;
        cout << "  │ 2  │ 🍟 薯条  │  8元 │" << endl;
        cout << "  │ 3  │ 🥤 可乐  │  5元 │" << endl;
        cout << "  │ 4  │ 🍦 冰淇淋│  6元 │" << endl;
        cout << "  │ 5  │ 🍗 鸡翅  │ 12元 │" << endl;
        cout << "  └────┴──────────┴──────┘" << endl;
        cout << endl;

        // --- 用户选择 ---
        cout << "请选择菜品序号（1-5）：";
        cin >> choice;

        // --- 用switch判断用户选择 ---
        switch (choice) {
            case 1:
                itemName = "汉堡";
                itemEmoji = "🍔";
                price = 15;
                break;
            case 2:
                itemName = "薯条";
                itemEmoji = "🍟";
                price = 8;
                break;
            case 3:
                itemName = "可乐";
                itemEmoji = "🥤";
                price = 5;
                break;
            case 4:
                itemName = "冰淇淋";
                itemEmoji = "🍦";
                price = 6;
                break;
            case 5:
                itemName = "鸡翅";
                itemEmoji = "🍗";
                price = 12;
                break;
            default:
                cout << endl;
                cout << "❌ 抱歉，没有序号 " << choice << " 的菜品！" << endl;
                cout << "   请输入1-5之间的序号哦~" << endl;
                return 0;  // 提前结束程序
        }

        // --- 输入数量 ---
        cout << "请输入购买数量：";
        cin >> quantity;

        if (quantity <= 0) {
            cout << "❌ 数量必须大于0哦！" << endl;
            return 0;
        }

        // --- 计算总价并显示订单 ---
        double total = price * quantity;

        cout << endl;
        cout << "══════ 📋 订单详情 ══════" << endl;
        cout << "  菜品：" << itemEmoji << " " << itemName << endl;
        cout << "  单价：" << price << " 元" << endl;
        cout << "  数量：" << quantity << " 份" << endl;
        cout << "  ─────────────────────" << endl;
        cout << "  总价：" << total << " 元" << endl;
        cout << "════════════════════════" << endl;
        cout << endl;
        cout << "✅ 点餐成功！请取餐，祝您用餐愉快！🍽️" << endl;
    }
    cout << endl;

    // ==========================================
    // 程序结束
    // ==========================================
    cout << "========== 第16课学习完毕 ==========" << endl;
    cout << "核心要点：" << endl;
    cout << "  1. switch(变量) { case 值: ... break; }" << endl;
    cout << "  2. case后面是冒号(:)，不是分号(;)！" << endl;
    cout << "  3. break是\"刹车\"，没有break会\"穿透\"" << endl;
    cout << "  4. default是\"兜底\"，处理所有不匹配的情况" << endl;
    cout << "  5. 判断具体值用switch，判断范围用if-else" << endl;

    return 0;
}

/*
 * =============================================
 * 本课知识点总结：
 *
 * 1. switch-case 基本语法：
 *    switch (变量) {
 *        case 值1:
 *            代码;
 *            break;    // ← 必不可少！
 *        case 值2:
 *            代码;
 *            break;
 *        default:
 *            代码;      // ← 可选但建议写
 *            break;
 *    }
 *
 * 2. 语法注意事项（极易出错！）：
 *    - case后面跟冒号(:)，不是分号(;) ← 初学者最高频错误！
 *    - case的值必须是整数或字符（int、char）
 *    - case的值不能重复
 *    - switch后面的变量也要用圆括号()
 *
 * 3. break的三种情况：
 *    - 有break：执行完对应case后跳出switch（正常）
 *    - 无break：穿透到下一个case继续执行（通常要避免）
 *    - 利用穿透：多个case共享同一段代码（巧妙用法）
 *
 * 4. switch vs if-else 选择原则：
 *    ┌──────────────────────────────────────┐
 *    │  判断"等于具体值" → switch          │
 *    │  判断"大于/小于/范围" → if-else     │
 *    │  条件复杂(&& ||) → if-else          │
 *    │  选项多且都是精确值 → switch更清晰   │
 *    └──────────────────────────────────────┘
 *
 * =============================================
 */
