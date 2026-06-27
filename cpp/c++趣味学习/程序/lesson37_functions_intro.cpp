/*
 * ============================================================
 *  第37课：魔法配方——函数初识
 *  Lesson 37: Magic Recipe — Introduction to Functions
 * ============================================================
 *
 *  课程目标：
 *    1. 理解函数的定义与调用
 *    2. 掌握 void 函数和有返回值函数的区别
 *    3. 学会使用多个函数协作完成复杂任务
 *    4. 体会代码复用的价值
 *
 *  本文件包含 4 个独立的演示程序（运行时会逐一展示）：
 *    程序一：简单的 void 函数 —— 打印魔法书欢迎信息
 *    程序二：带返回值的函数 —— 魔法计算器（add, multiply 等）
 *    程序三：多个函数协作 —— 完整的魔法配方书
 *    程序四：课堂练习参考答案
 *
 *  编译方式（以 g++ 为例）：
 *    g++ -std=c++11 lesson37_functions_intro.cpp -o lesson37
 *    ./lesson37
 *
 * ============================================================
 */

#include <iostream>
#include <string>
#include <cstdlib>   // 用于 system("clear") 或 system("cls")
using namespace std;

// ============================================================
//  辅助函数：清屏并打印分隔标题
// ============================================================
void clearScreen() {
    // 在 macOS/Linux 上使用 "clear"，在 Windows 上使用 "cls"
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void printSectionTitle(const string& title) {
    cout << endl;
    cout << "╔══════════════════════════════════════════════════════╗" << endl;
    cout << "║  " << title << endl;
    cout << "╚══════════════════════════════════════════════════════╝" << endl;
    cout << endl;
}

void pauseAndContinue() {
    cout << endl;
    cout << "▶ 按 Enter 键继续..." << endl;
    cin.get();
}

// ============================================================
//  程序一：简单的 void 函数
//  演示不带返回值的函数 —— 就像魔法书上不需要"产出"的咒语
// ============================================================

// 函数：显示魔法书封面（void 类型 —— 只做动作，不返回值）
void showMagicBookCover() {
    cout << "         ,___," << endl;
    cout << "        (o,o)     ✨ 欢迎翻开魔法编程书 ✨" << endl;
    cout << "        /)_) " << endl;
    cout << "   ╔════════════════════════════════╗" << endl;
    cout << "   ║   📖  魔  法  配  方  书  📖  ║" << endl;
    cout << "   ║                              ║" << endl;
    cout << "   ║   第 37 课：函数 —— 编程的    ║" << endl;
    cout << "   ║           "魔法配方"          ║" << endl;
    cout << "   ║                              ║" << endl;
    cout << "   ║   著者：未来的大魔法师        ║" << endl;
    cout << "   ╚════════════════════════════════╝" << endl;
}

// 函数：打印魔法阵图案（void 类型）
void drawMagicCircle() {
    cout << "        ╭―――――――――――――╮" << endl;
    cout << "       ╱                 ╲" << endl;
    cout << "      ╱   ✦  ✧  ✦  ✧   ╲" << endl;
    cout << "     │    魔法阵 激活！    │" << endl;
    cout << "      ╲   ✧  ✦  ✧  ✦   ╱" << endl;
    cout << "       ╲                 ╱" << endl;
    cout << "        ╰―――――――――――――╯" << endl;
}

// 函数：显示魔法咒语（void 类型，带一个参数）
void castSimpleSpell(const string& spellName) {
    cout << "🔮 吟唱咒语：「" << spellName << "」" << endl;
    cout << "   ✨✨✨ 咒语释放完毕！✨✨✨" << endl;
}

void demo1_voidFunctions() {
    printSectionTitle("程序一：探秘 void 函数 —— 无声的魔法");

    cout << "【知识点】void 类型的函数不返回任何值，只负责执行动作。" << endl;
    cout << "          就像魔法书中的"展示咒"——念出来就好，不需要变出实物。\n" << endl;

    // 调用 void 函数 —— 直接写函数名和括号即可
    showMagicBookCover();

    cout << "\n" << string(50, '─') << endl;

    drawMagicCircle();

    cout << "\n" << string(50, '─') << endl;

    // 带参数的 void 函数
    castSimpleSpell("Lumos Maxima! 荧光闪烁!");
    cout << endl;
    castSimpleSpell("Protego! 盔甲护身!");

    cout << "\n📝 小结：这 3 个函数都是 void 类型，它们被调用后执行了动作，" << endl;
    cout << "        但没有返回任何数据给调用者。就像你让朋友帮忙喊一声"加油！"——" << endl;
    cout << "        朋友做了这件事，但不需要"交还"什么东西给你。\n" << endl;

    pauseAndContinue();
}

// ============================================================
//  程序二：带返回值的函数 —— 魔法计算器
//  演示有返回值的函数，理解 return 的作用
// ============================================================

/**
 *  函数：additionPotion —— 加法药水
 *  @param a  第一个加数（材料一）
 *  @param b  第二个加数（材料二）
 *  @return   两数之和（炼制出的数字药水）
 */
int additionPotion(int a, int b) {
    // return 语句做了两件事：
    //   1. 计算 a + b 的值
    //   2. 把这个值"交还"给调用者
    return a + b;
}

/**
 *  函数：multiplicationPotion —— 乘法药水
 *  @param a  被乘数
 *  @param b  乘数
 *  @return   两数之积
 */
int multiplicationPotion(int a, int b) {
    return a * b;
}

/**
 *  函数：subtractionPotion —— 减法药水
 *  @param a  被减数
 *  @param b  减数
 *  @return   两数之差
 */
int subtractionPotion(int a, int b) {
    return a - b;
}

/**
 *  函数：divisionPotion —— 除法药水
 *  @param a      被除数
 *  @param b      除数
 *  @return       两数之商（double 类型，可以得到小数结果）
 *
 *  注意：返回类型是 double，不是 int！
 *        因为除法可能产生小数（如 5 ÷ 2 = 2.5）
 */
double divisionPotion(int a, int b) {
    // 安全检查：除数不能为零，否则会引发"魔法反噬"！
    if (b == 0) {
        cout << "⚠️ 警告：除数不能为零！魔法反噬！返回 0。" << endl;
        return 0.0;
    }
    // static_cast<double> 将整数转为小数，确保除法得到小数结果
    return static_cast<double>(a) / b;
}

/**
 *  函数：powerPotion —— 乘方药水
 *  @param base  底数
 *  @param exp   指数（必须 >= 0）
 *  @return      base 的 exp 次方
 */
int powerPotion(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

/**
 *  函数：maxPower —— 找出两个药水中更强的那个
 *  @param power1  药水1的效力
 *  @param power2  药水2的效力
 *  @return        较大的效力值
 */
int maxPower(int power1, int power2) {
    return (power1 > power2) ? power1 : power2;
    // 三元运算符：条件 ? 值1 : 值2
    // 等价于：
    // if (power1 > power2) return power1;
    // else return power2;
}

void demo2_returnValueFunctions() {
    printSectionTitle("程序二：魔法计算器 —— 有返回值的函数");

    cout << "【知识点】有返回值的函数像一个"自动贩卖机"：" << endl;
    cout << "          你投进去材料（参数），它加工后还给你成品（返回值）。" << endl;
    cout << "          return 语句就是那个"出货口"。\n" << endl;

    // 准备一些魔法数字
    int ingredient1 = 15;
    int ingredient2 = 4;

    cout << "🧪 当前魔法材料：" << endl;
    cout << "   材料一 = " << ingredient1 << "，材料二 = " << ingredient2 << "\n" << endl;

    cout << string(50, '─') << endl;

    // 调用有返回值的函数，用变量接收结果
    int sum = additionPotion(ingredient1, ingredient2);
    cout << "➕ 加法药水：" << ingredient1 << " + " << ingredient2
         << " = " << sum << endl;

    int diff = subtractionPotion(ingredient1, ingredient2);
    cout << "➖ 减法药水：" << ingredient1 << " - " << ingredient2
         << " = " << diff << endl;

    int prod = multiplicationPotion(ingredient1, ingredient2);
    cout << "✖️  乘法药水：" << ingredient1 << " × " << ingredient2
         << " = " << prod << endl;

    double quot = divisionPotion(ingredient1, ingredient2);
    cout << "➗ 除法药水：" << ingredient1 << " ÷ " << ingredient2
         << " = " << quot << endl;

    int powResult = powerPotion(ingredient1, 3);
    cout << "📈 乘方药水：" << ingredient1 << "^3"
         << " = " << powResult << endl;

    int stronger = maxPower(ingredient1, ingredient2);
    cout << "💪 更强药水：" << ingredient1 << " 和 " << ingredient2
         << " 中更强的是 " << stronger << endl;

    // 也可以直接在输出中调用函数，不需要中间变量
    cout << "\n🔮 直接调用（不用变量接收）：" << endl;
    cout << "   " << ingredient1 << " × 10 = "
         << multiplicationPotion(ingredient1, 10) << endl;

    // 函数的返回值还可以作为另一个函数的参数！
    cout << "\n🔗 函数嵌套调用：" << endl;
    cout << "   max(add(3, 5), multiply(2, 3)) = "
         << maxPower(additionPotion(3, 5), multiplicationPotion(2, 3)) << endl;
    cout << "   （先算 3+5=8 和 2×3=6，然后 max(8,6)=8）" << endl;

    // 测试除零保护
    cout << "\n⚠️ 测试除零保护：" << endl;
    cout << "   10 ÷ 0 = " << divisionPotion(10, 0) << endl;

    pauseAndContinue();
}

// ============================================================
//  程序三：多个函数协作 —— 完整的魔法配方书
//  模拟一个完整的"炼制魔法药水"游戏
// ============================================================

/**
 *  函数：brewPotion —— 炼制药水
 *  根据配方编号和材料数量计算药水效力
 *
 *  @param recipeID   配方编号（1=治疗药水, 2=力量药水, 3=智慧药水）
 *  @param herbs      草药数量
 *  @param crystals   魔法水晶数量
 *  @param moonDust   月光粉尘数量
 *  @return           药水效力值
 */
int brewPotion(int recipeID, int herbs, int crystals, int moonDust) {
    // 不同配方有不同的效力计算公式
    int potency = 0;

    switch (recipeID) {
        case 1:  // 治疗药水配方
            potency = herbs * 5 + crystals * 3 + moonDust * 2;
            break;
        case 2:  // 力量药水配方
            potency = herbs * 2 + crystals * 7 + moonDust * 3;
            break;
        case 3:  // 智慧药水配方
            potency = herbs * 3 + crystals * 3 + moonDust * 6;
            break;
        default:
            cout << "❌ 未知的配方编号！" << endl;
            potency = 0;
    }
    return potency;
}

/**
 *  函数：getRecipeName —— 获取配方名称
 *  @param recipeID  配方编号
 *  @return          配方名称（string 类型）
 */
string getRecipeName(int recipeID) {
    switch (recipeID) {
        case 1:  return "💚 治疗药水";
        case 2:  return "❤️ 力量药水";
        case 3:  return "💙 智慧药水";
        default: return "❓ 未知药水";
    }
}

/**
 *  函数：getPotionGrade —— 鉴定药水等级
 *  @param potency  药水效力
 *  @return         等级描述
 */
string getPotionGrade(int potency) {
    if (potency >= 80) {
        return "🌟🌟🌟 传说级 (Legendary)";
    } else if (potency >= 60) {
        return "🌟🌟  史诗级 (Epic)";
    } else if (potency >= 40) {
        return "🌟   稀有级 (Rare)";
    } else if (potency >= 20) {
        return "⭐   精良级 (Uncommon)";
    } else {
        return "💨   普通级 (Common)";
    }
}

/**
 *  函数：isPotionSuccessful —— 判断炼制是否成功
 *  @param potency  药水效力
 *  @return         true=成功, false=失败（效力太低）
 */
bool isPotionSuccessful(int potency) {
    return potency >= 20;  // 效力低于 20 视为失败
}

/**
 *  函数：calcMaterialCost —— 计算材料总费用
 *  @param herbs      草药数量
 *  @param crystals   魔法水晶数量
 *  @param moonDust   月光粉尘数量
 *  @return           总金币数
 */
int calcMaterialCost(int herbs, int crystals, int moonDust) {
    int herbPrice = 3;      // 每株草药 3 金币
    int crystalPrice = 5;   // 每块水晶 5 金币
    int dustPrice = 4;      // 每份粉尘 4 金币

    return herbs * herbPrice + crystals * crystalPrice + moonDust * dustPrice;
}

/**
 *  函数：displayPotionResult —— 展示炼制结果
 *  这是一个综合性的函数，调用其他函数来组装完整的展示信息
 *
 *  @param recipeID   配方编号
 *  @param herbs      草药数量
 *  @param crystals   魔法水晶数量
 *  @param moonDust   月光粉尘数量
 */
void displayPotionResult(int recipeID, int herbs, int crystals, int moonDust) {
    string name = getRecipeName(recipeID);
    int potency = brewPotion(recipeID, herbs, crystals, moonDust);
    string grade = getPotionGrade(potency);
    bool success = isPotionSuccessful(potency);
    int cost = calcMaterialCost(herbs, crystals, moonDust);

    cout << "╭──────────────────────────────────────╮" << endl;
    cout << "│  🧪 药水炼制报告                     │" << endl;
    cout << "├──────────────────────────────────────┤" << endl;
    cout << "│  配方名称：" << name;
    // 手动对齐中文（中文字符占两个英文字符宽度）
    int padding = 24 - name.length() * 2;  // 粗略估算
    // 简单处理：统一用固定宽度
    cout << endl;
    cout << "│  使用材料：草药×" << herbs
         << "  水晶×" << crystals
         << "  粉尘×" << moonDust << endl;
    cout << "│  材料费用：" << cost << " 金币" << endl;
    cout << "│  药水效力：" << potency << endl;
    cout << "│  药水等级：" << grade << endl;
    cout << "│  炼制结果：" << (success ? "✅ 成功！" : "❌ 失败...效力和材料不足") << endl;
    cout << "╰──────────────────────────────────────╯" << endl;
}

/**
 *  函数：showSpellBookStats —— 打印魔法书统计信息（void 类型）
 *  统计本次会话炼制的药水情况
 *
 *  @param totalPotions   炼制药水总数
 *  @param totalCost      总花费金币
 *  @param bestPotency    最高效力
 */
void showSpellBookStats(int totalPotions, int totalCost, int bestPotency) {
    cout << "\n📊 ╔══════════════════════════╗" << endl;
    cout << "    ║  📖 魔法书统计报告     ║" << endl;
    cout << "    ╠══════════════════════════╣" << endl;
    cout << "    ║  炼制次数：" << totalPotions;
    for (int i = 0; i < 12 - to_string(totalPotions).length(); i++) cout << " ";
    cout << "║" << endl;
    cout << "    ║  总花费：  " << totalCost;
    for (int i = 0; i < 12 - to_string(totalCost).length(); i++) cout << " ";
    cout << "金币║" << endl;
    cout << "    ║  最高效力：" << bestPotency;
    for (int i = 0; i < 12 - to_string(bestPotency).length(); i++) cout << " ";
    cout << "║" << endl;
    cout << "    ╚══════════════════════════╝" << endl;
}

void demo3_magicRecipeBook() {
    printSectionTitle("程序三：完整的魔法配方书 —— 多函数协作");

    cout << "【知识点】一个复杂的程序通常由多个函数组成，" << endl;
    cout << "          每个函数各司其职，像魔法书里的不同章节。\n" << endl;
    cout << "          本程序模拟了一位小魔法师打开魔法书炼制药水的过程。\n" << endl;

    // 显示魔法书封面
    showMagicBookCover();
    cout << endl;

    // 炼制药水的数据（模拟多次炼制）
    // 格式：{配方编号, 草药, 水晶, 粉尘}
    struct BrewAttempt {
        int recipeID;
        int herbs;
        int crystals;
        int moonDust;
    };

    BrewAttempt attempts[] = {
        {1, 5, 3, 2},   // 治疗药水
        {2, 4, 6, 1},   // 力量药水
        {3, 7, 2, 5},   // 智慧药水
        {1, 1, 1, 1},   // 治疗药水（材料不足，看看会不会失败）
        {2, 8, 8, 8},   // 力量药水（豪华材料！）
    };

    int numAttempts = 5;
    int totalCost = 0;
    int bestPotency = 0;

    cout << "🔮 魔法师开始翻阅魔法书，准备炼制药水...\n" << endl;

    for (int i = 0; i < numAttempts; i++) {
        cout << "━━━ 第 " << (i + 1) << " 次炼制 ━━━" << endl;

        // 调用核心函数：展示炼制结果
        displayPotionResult(
            attempts[i].recipeID,
            attempts[i].herbs,
            attempts[i].crystals,
            attempts[i].moonDust
        );

        // 累计统计信息
        int potency = brewPotion(
            attempts[i].recipeID,
            attempts[i].herbs,
            attempts[i].crystals,
            attempts[i].moonDust
        );

        totalCost += calcMaterialCost(
            attempts[i].herbs,
            attempts[i].crystals,
            attempts[i].moonDust
        );

        if (potency > bestPotency) {
            bestPotency = potency;
        }

        cout << endl;
    }

    // 展示统计报告
    showSpellBookStats(numAttempts, totalCost, bestPotency);

    cout << "\n📝 小结：这个程序使用了 7 个自定义函数！" << endl;
    cout << "        - brewPotion()      计算药水效力" << endl;
    cout << "        - getRecipeName()   获取配方名称" << endl;
    cout << "        - getPotionGrade()  鉴定药水等级" << endl;
    cout << "        - isPotionSuccessful()  判断是否成功" << endl;
    cout << "        - calcMaterialCost()  计算材料费用" << endl;
    cout << "        - displayPotionResult()  综合展示结果" << endl;
    cout << "        - showSpellBookStats()  打印统计报告" << endl;
    cout << "\n        每个函数只做一件事，分工明确，这就是"模块化编程"的思想！" << endl;

    pauseAndContinue();
}

// ============================================================
//  程序四：课堂练习参考答案
// ============================================================

/**
 *  练习一答案：square 函数 —— 计算整数平方
 */
int square(int n) {
    return n * n;
}

/**
 *  练习二答案：修正后的 max 函数
 *  原代码错误：参数 b 缺少类型、缺少 else 分支的 return、调用时参数不足
 */
int maxNumber(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

/**
 *  练习三答案：power 函数 —— 计算 base 的 exp 次方
 */
int power(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

/**
 *  挑战任务参考答案辅助函数 —— 判断是否为质数
 */
bool isPrime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

/**
 *  挑战任务参考答案辅助函数 —— 打印质数药水列表
 */
void listPrimePotions(int limit) {
    cout << "🔢 调试药水列表（1-" << limit << " 中的质数配方）：" << endl;
    int count = 0;
    for (int i = 2; i <= limit; i++) {
        if (isPrime(i)) {
            cout << "  🧪 配方 #" << i;
            count++;
            if (count % 5 == 0) cout << endl;  // 每5个换行
        }
    }
    if (count % 5 != 0) cout << endl;
    cout << "  （共 " << count << " 个质数配方）" << endl;
}

void demo4_exerciseAnswers() {
    printSectionTitle("程序四：课堂练习参考答案");

    // ===== 练习一答案演示 =====
    cout << "【练习一】square 函数 —— 计算平方" << endl;
    cout << "  square(5) = " << square(5) << endl;
    cout << "  square(12) = " << square(12) << endl;
    cout << "  square(-3) = " << square(-3) << "  （负数平方也是正数）" << endl;
    cout << endl;

    // ===== 练习二答案演示 =====
    cout << "【练习二】修正后的 max 函数" << endl;
    cout << "  maxNumber(10, 20) = " << maxNumber(10, 20) << endl;
    cout << "  maxNumber(99, 50) = " << maxNumber(99, 50) << endl;
    cout << "  maxNumber(-5, -3) = " << maxNumber(-5, -3) << endl;
    cout << "  （原代码有3处错误：参数b缺类型、缺else分支return、调用时参数不足）" << endl;
    cout << endl;

    // ===== 练习三答案演示 =====
    cout << "【练习三】power 函数 —— 计算乘方" << endl;
    cout << "  power(2, 3)   = " << power(2, 3) << "   （2³ = 8）" << endl;
    cout << "  power(5, 4)   = " << power(5, 4) << "  （5⁴ = 625）" << endl;
    cout << "  power(10, 0)  = " << power(10, 0) << "   （任何数的0次方=1）" << endl;
    cout << "  power(3, 5)   = " << power(3, 5) << "  （3⁵ = 243）" << endl;
    cout << endl;

    // ===== 挑战任务扩展演示 =====
    cout << "【挑战任务扩展】isPrime 和 listPrimePotions —— 质数判断" << endl;
    cout << "  isPrime(7)  = " << (isPrime(7) ? "true" : "false") << endl;
    cout << "  isPrime(12) = " << (isPrime(12) ? "true" : "false") << endl;
    cout << "  isPrime(97) = " << (isPrime(97) ? "true" : "false") << endl;
    cout << endl;
    listPrimePotions(50);

    cout << "\n─────────────────────────────────────────" << endl;
    cout << "  以上是所有练习的参考答案。" << endl;
    cout << "  建议先自己尝试编写，遇到困难再参考答案！" << endl;
    cout << "─────────────────────────────────────────" << endl;

    pauseAndContinue();
}

// ============================================================
//  主函数：程序的入口
//  依次运行四个演示程序
// ============================================================
int main() {
    // 设置为中文环境（如果终端支持）
    // 在 macOS/Linux 终端中可能需要设置 locale
    // setlocale(LC_ALL, "zh_CN.UTF-8");  // 如果中文显示异常可取消注释

    // ===== 程序一 =====
    demo1_voidFunctions();

    // ===== 程序二 =====
    demo2_returnValueFunctions();

    // ===== 程序三 =====
    demo3_magicRecipeBook();

    // ===== 程序四 =====
    demo4_exerciseAnswers();

    // ===== 课程结束 =====
    cout << endl;
    cout << "╔══════════════════════════════════════════════════════╗" << endl;
    cout << "║                                                      ║" << endl;
    cout << "║   🧪  第 37 课「魔法配方——函数初识」学习完毕！ 🧪  ║" << endl;
    cout << "║                                                      ║" << endl;
    cout << "║   记住魔法口诀：                                      ║" << endl;
    cout << "║   定义函数像写配方，返回类型要思量；                  ║" << endl;
    cout << "║   函数名字见名知意，参数列表不能忘；                  ║" << endl;
    cout << "║   花括号里写步骤，return 把结果交上；                 ║" << endl;
    cout << "║   要使用时喊名字，传入实参就能用上！                  ║" << endl;
    cout << "║                                                      ║" << endl;
    cout << "║   下节课预告：第 38 课 —— 参数与返回值深入           ║" << endl;
    cout << "║                                                      ║" << endl;
    cout << "╚══════════════════════════════════════════════════════╝" << endl;
    cout << endl;

    return 0;
}
