/*
 * =====================================================================
 * 第34课：文字处理机——字符串入门
 * lesson34_string_intro.cpp
 * =====================================================================
 *
 * 本文件包含 4 个演示程序，展示 C++ string 类型的核心用法：
 *
 *   【程序1】字符串声明与基本输入输出
 *     - string 类型的声明、赋值、length() 获取长度、通过索引访问字符
 *
 *   【程序2】cin vs getline 行为对比
 *     - 对比 cin >> 和 getline() 读取带空格文本的不同表现
 *     - 演示 cin.ignore() 在混合输入中的作用
 *
 *   【程序3】⭐ 名片生成器（本课主项目）
 *     - 综合运用 getline 输入、字符串拼接、格式化输出
 *     - 制作个性化的文字名片
 *
 *   【程序4】课后练习答案
 *     - 练习一：填空补全代码的完整答案
 *     - 挑战任务：智能问候机器人的实现
 *
 * 编译方式（任一均可）：
 *   g++ lesson34_string_intro.cpp -o lesson34_string_intro
 *   clang++ lesson34_string_intro.cpp -o lesson34_string_intro
 *
 * 运行：./lesson34_string_intro
 *
 * 适用对象：中国中小学 C++ 初学者
 * 课时：第34课 | 第三阶段：数据类型进阶
 * =====================================================================
 */

#include <iostream>
#include <string>
using namespace std;

// -------------------------------------------------------
// 工具函数：打印分隔线，让输出更清晰
// -------------------------------------------------------
void printDivider(const string& title) {
    cout << endl;
    cout << "========================================" << endl;
    cout << "  " << title << endl;
    cout << "========================================" << endl;
}

// -------------------------------------------------------
// 工具函数：暂停，等待用户按回车继续
// -------------------------------------------------------
void waitForEnter() {
    cout << endl;
    cout << "按回车键继续..." << endl;
    cin.get();
}

/*
 * =====================================================================
 * 程序1：字符串声明与基本输入输出
 * =====================================================================
 * 演示内容：
 *   - 如何声明 string 变量
 *   - 如何使用 cin >> 输入字符串
 *   - 如何用 length() 获取字符个数
 *   - 如何用索引 [i] 访问单个字符
 *   - 如何重新赋值修改字符串内容
 * =====================================================================
 */
void demo1_basicStringIO() {
    printDivider("【程序1】字符串声明与基本输入输出");

    // --- 1. 声明与初始化 ---
    string name = "小明";
    cout << "初始名字：" << name << endl;
    cout << "（这是声明时直接赋的值）" << endl;

    // --- 2. 从键盘输入新名字（使用 cin >>） ---
    cout << endl;
    cout << "请输入一个新的名字（不要有空格哦）：";
    cin >> name;
    cout << "你输入的新名字是：" << name << endl;

    // --- 3. 获取字符串长度 ---
    cout << endl;
    cout << "【字符串长度】" << endl;
    cout << "\"" << name << "\" 一共有 " << name.length() << " 个字符" << endl;
    // 注意：length() 返回的是字节数还是字符数取决于编码
    // 在 UTF-8 环境下，一个中文字通常占 3 个字节，
    // 这里用 length() 会得到字节数，用来说明 length() 的含义。

    // --- 4. 访问单个字符 ---
    cout << endl;
    cout << "【访问单个字符（索引从0开始）】" << endl;
    if (name.length() > 0) {
        cout << "第一个字符（索引0）：" << name[0] << endl;
        cout << "最后一个字符（索引" << name.length() - 1 << "）："
             << name[name.length() - 1] << endl;
    }

    // --- 5. 判断是否为空 ---
    cout << endl;
    cout << "【判断字符串是否为空】" << endl;
    string emptyStr = "";
    cout << "空字符串 empty() 的返回值：" << boolalpha << emptyStr.empty() << endl;
    cout << "\"" << name << "\" empty() 的返回值：" << name.empty() << endl;

    // --- 6. 清空字符串 ---
    cout << endl;
    cout << "【清空字符串】" << endl;
    string test = "临时数据";
    cout << "清空前：" << test << "（长度：" << test.length() << "）" << endl;
    test.clear();
    cout << "清空后：" << test << "（长度：" << test.length() << "）" << endl;

    // 清除输入缓冲区（为后面的 getline 做准备）
    cin.ignore(10000, '\n');
    waitForEnter();
}

/*
 * =====================================================================
 * 程序2：cin >>  vs  getline()  行为对比
 * =====================================================================
 * 演示内容：
 *   - cin >> 遇到空格就停止，只能读取一个"单词"
 *   - getline() 可以读取包含空格的整行文本
 *   - 混合使用 cin >> 和 getline() 时的"坑"及解决方案
 * =====================================================================
 */
void demo2_cinVsGetline() {
    printDivider("【程序2】cin >>  vs  getline() 行为对比");

    // ===== 场景A：只用 cin >> =====
    cout << "【场景A：使用 cin >> 输入】" << endl;
    cout << "请输入两个词语（用空格隔开，例如 \"Hello World\"）：" << endl;

    string word1, word2;
    cin >> word1;
    cin >> word2;

    cout << endl;
    cout << "cin >> word1 读到：" << word1 << endl;
    cout << "cin >> word2 读到：" << word2 << endl;
    cout << ">> 发现了吗？一次输入的两个词被分别存入了两个变量！" << endl;

    // 清除缓冲区
    cin.ignore(10000, '\n');

    cout << endl;
    cout << "----------------------------------------" << endl;

    // ===== 场景B：只用 getline() =====
    cout << "【场景B：使用 getline() 输入】" << endl;
    cout << "请输入一句完整的话（可以有空格）：" << endl;

    string fullLine;
    getline(cin, fullLine);

    cout << endl;
    cout << "getline 读到：" << fullLine << endl;
    cout << ">> getline 把整行（包括空格）都完整读进来了！" << endl;

    cout << endl;
    cout << "----------------------------------------" << endl;

    // ===== 场景C：混合使用的陷阱 =====
    cout << "【场景C：混合使用的陷阱】" << endl;
    cout << "先输入一个单词：";
    string tempWord;
    cin >> tempWord;
    cout << "单词：" << tempWord << endl;

    // 如果不加 cin.ignore()，下面的 getline 会立即读到残留的换行符
    cout << endl;
    cout << "⚠️  如果不调用 cin.ignore()，getline 会立即读到换行符而跳过输入！" << endl;
    cout << "✅  现在调用 cin.ignore() 清除缓冲区..." << endl;
    cin.ignore(10000, '\n');

    cout << endl;
    cout << "现在请输入一句完整的话：";
    string afterIgnore;
    getline(cin, afterIgnore);
    cout << "getline 读到：" << afterIgnore << endl;
    cout << ">> 成功！getline 正常工作了。" << endl;

    // 总结对比
    cout << endl;
    cout << "========================================" << endl;
    cout << "📋 cin >>  vs  getline() 总结：        " << endl;
    cout << "========================================" << endl;
    cout << "  cin >>    →  只读一个词，遇空格就停  " << endl;
    cout << "  getline() →  读一整行，空格也保留    " << endl;
    cout << "  混用时    →  记得用 cin.ignore()！    " << endl;
    cout << "========================================" << endl;

    // 这里不需要再 ignore，因为场景C最后用的是 getline
    waitForEnter();
}

/*
 * =====================================================================
 * 程序3：⭐ 个人名片生成器（本课主项目）
 * =====================================================================
 * 演示内容：
 *   - 综合运用 getline() 收集用户多项信息
 *   - 使用 + 和 += 进行字符串拼接
 *   - 使用 for 循环做简单的对齐格式化
 *   - 使用 length() 统计信息字符数
 * =====================================================================
 */
void demo3_nameCardGenerator() {
    printDivider("【程序3】⭐ 个人名片生成器");

    string name, school, hobby, phone;

    // --- 步骤1：收集用户信息 ---
    cout << "🎨 欢迎使用个人名片生成器！" << endl;
    cout << "   请按照提示输入你的信息：" << endl;
    cout << endl;

    cout << "  你的姓名：";
    getline(cin, name);

    cout << "  你的学校：";
    getline(cin, school);

    cout << "  你的爱好：";
    getline(cin, hobby);

    cout << "  你的电话：";
    getline(cin, phone);

    // --- 步骤2：拼接生成名片 ---
    // 名片宽度为 26 个半角字符（约等于框线的视觉宽度）
    const int CARD_WIDTH = 26;

    // 辅助函数（lambda）：在内容后面补空格，使总显示宽度接近 CARD_WIDTH
    // 注意：中文字符显示宽度约为英文的2倍，这里用简化计算
    auto padRight = [](const string& content, int targetWidth) -> string {
        string result = "║  " + content;
        // 计算当前"显示宽度"：认为每个字符占1个单位（近似）
        int contentLen = (int)content.length();
        int needed = targetWidth - contentLen - 3; // 3 = "║  " 的宽度近似
        if (needed < 1) needed = 1;
        for (int i = 0; i < needed; i++) {
            result += " ";
        }
        result += "║\n";
        return result;
    };

    // 构建名片
    string card = "";
    card += "╔══════════════════════════╗\n";
    card += "║      🪪  个 人 名 片      ║\n";
    card += "╠══════════════════════════╣\n";
    card += padRight("姓名：" + name, CARD_WIDTH);
    card += padRight("学校：" + school, CARD_WIDTH);
    card += padRight("爱好：" + hobby, CARD_WIDTH);
    card += padRight("电话：" + phone, CARD_WIDTH);
    card += "╚══════════════════════════╝\n";

    // --- 步骤3：输出名片 ---
    cout << endl;
    cout << "🎉 你的专属名片已生成：" << endl;
    cout << endl;
    cout << card;

    // --- 步骤4：输出统计信息 ---
    cout << "━━━━━━━━━━━━━━━━━━━━━━" << endl;
    cout << "📊 名片信息统计：" << endl;
    cout << "  姓名 \"" << name << "\" → " << name.length() << " 个字符" << endl;
    cout << "  学校 \"" << school << "\" → " << school.length() << " 个字符" << endl;
    cout << "  爱好 \"" << hobby << "\" → " << hobby.length() << " 个字符" << endl;
    cout << "  电话 \"" << phone << "\" → " << phone.length() << " 个字符" << endl;
    cout << "━━━━━━━━━━━━━━━━━━━━━━" << endl;

    waitForEnter();
}

/*
 * =====================================================================
 * 程序4：课后练习答案
 * =====================================================================
 * 包含：
 *   练习一：填空补全代码 —— 完整的可运行版本
 *   挑战任务：智能问候机器人 —— 完整实现
 * =====================================================================
 */

// 练习一答案：填空补全代码
void exercise1_fillInBlanks() {
    printDivider("【练习一答案】填空补全代码");

    cout << "以下代码展示的是修正后的完整版本：" << endl;
    cout << endl;
    cout << "--- 开始运行练习一程序 ---" << endl;
    cout << endl;

    string name, subject;
    cout << "你的名字：";
    getline(cin, name);          // ① 补全：cin

    cout << "喜欢的科目：";
    getline(cin, subject);       // ② 补全：subject

    // ③ 补全：+ 运算符拼接，<< 输出
    cout << name + "最喜欢的科目是" + subject + "！" << endl;

    cout << endl;
    cout << "--- 练习一程序结束 ---" << endl;

    cout << endl;
    cout << "📝 答案说明：" << endl;
    cout << "  ① 头文件是 <string>（已在文件顶部包含）" << endl;
    cout << "  ② getline(cin, name) —— 第一个参数是 cin" << endl;
    cout << "  ③ getline(cin, subject) —— 第二个参数是变量 subject" << endl;
    cout << "  ④ 用 + 拼接字符串，用 << 输出 —— name + \"最喜欢的科目是\" + subject + \"！\"" << endl;

    waitForEnter();
}

// 挑战任务答案：智能问候机器人
void challenge_smartGreetingBot() {
    printDivider("【挑战任务答案】智能问候机器人");

    cout << "🤖 你好！我是智能问候机器人！" << endl;
    cout << endl;

    string name, mood;

    cout << "请输入你的名字：";
    getline(cin, name);

    cout << "请输入你现在的心情（如：开心 / 有点困 / 充满能量）：";
    getline(cin, mood);

    cout << endl;
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;

    // 根据心情生成不同的问候语
    if (mood == "开心") {
        cout << name + "，太棒了！保持好心情，今天一定万事如意！" << endl;
    } else if (mood == "有点困") {
        cout << name + "，来一杯热水提提神吧，代码世界需要清醒的你！" << endl;
    } else if (mood == "充满能量") {
        cout << name + "，充满能量就赶紧写代码吧，今天一定收获满满！" << endl;
    } else if (mood == "紧张") {
        cout << name + "，别紧张，深呼吸，你比自己想象的更厉害！" << endl;
    } else if (mood == "无聊") {
        cout << name + "，无聊的时候来写个程序吧，创造是最有趣的游戏！" << endl;
    } else {
        cout << name + "，感谢你的分享，每一天都是新的开始，加油！" << endl;
    }

    cout << endl;
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    cout << endl;
    cout << "📝 挑战任务实现要点：" << endl;
    cout << "  1. 使用 getline() 读取含空格的输入" << endl;
    cout << "  2. 使用 if-else if-else 判断心情" << endl;
    cout << "  3. 用 == 比较两个字符串是否相同" << endl;
    cout << "  4. 用 + 拼接最终的问候语" << endl;
    cout << endl;
    cout << "💡 扩展思路：你还可以添加更多心情选项，" << endl;
    cout << "   让机器人变得更聪明哦！" << endl;

    waitForEnter();
}

/*
 * =====================================================================
 * main() —— 程序入口，提供菜单选择
 * =====================================================================
 */
int main() {
    cout << endl;
    cout << "╔══════════════════════════════════════╗" << endl;
    cout << "║  第34课：文字处理机——字符串入门  ║" << endl;
    cout << "║  lesson34_string_intro.cpp           ║" << endl;
    cout << "╚══════════════════════════════════════╝" << endl;
    cout << endl;

    int choice = 0;
    bool exitProgram = false;

    while (!exitProgram) {
        cout << "请选择要运行的程序：" << endl;
        cout << "  1 → 字符串声明与基本输入输出" << endl;
        cout << "  2 → cin >> vs getline() 行为对比" << endl;
        cout << "  3 → ⭐ 个人名片生成器（主项目）" << endl;
        cout << "  4 → 练习一：填空补全代码（答案）" << endl;
        cout << "  5 → 挑战任务：智能问候机器人（答案）" << endl;
        cout << "  0 → 退出程序" << endl;
        cout << endl;
        cout << "请输入选项（0-5）：";
        cin >> choice;

        // 清除输入缓冲区
        cin.ignore(10000, '\n');

        cout << endl;

        switch (choice) {
            case 1:
                demo1_basicStringIO();
                break;
            case 2:
                demo2_cinVsGetline();
                break;
            case 3:
                demo3_nameCardGenerator();
                break;
            case 4:
                exercise1_fillInBlanks();
                break;
            case 5:
                challenge_smartGreetingBot();
                break;
            case 0:
                cout << "👋 再见！记得多多练习 string 的用法哦！" << endl;
                exitProgram = true;
                break;
            default:
                cout << "❌ 无效选项，请输入 0-5 之间的数字。" << endl;
                break;
        }
    }

    return 0;
}
