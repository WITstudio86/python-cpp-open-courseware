/*
 * ==========================================
 *  第35课：字符串神探——字符串操作
 *  知识点：length()、索引访问[]、substr()、find()
 *  C++趣味学习系列
 * ==========================================
 */

#include <iostream>
#include <string>
#include <cstdlib>   // 用于 rand() 和 srand()
#include <ctime>     // 用于 time()
using namespace std;

// ===== 函数声明 =====
void demo1_length_and_index();
void demo2_substr_and_find();
void exercise1_char_counter();
void exercise2_name_splitter();
void exercise3_keyword_replacer();
void challenge_encrypt_decrypt();

// ==================================================================
// main 函数：程序入口，依次执行所有演示和练习
// ==================================================================
int main() {
    // 初始化随机数种子（用于挑战任务的噪音生成）
    srand(static_cast<unsigned int>(time(0)));

    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║     🕵️  第35课：字符串神探——字符串操作  ║" << endl;
    cout << "║     length() | 索引[] | substr() | find() ║" << endl;
    cout << "╚══════════════════════════════════════════╝" << endl;
    cout << endl;

    // =====================================
    // 演示1：字符串长度和索引访问
    // =====================================
    demo1_length_and_index();

    // =====================================
    // 演示2：子串提取和查找操作
    // =====================================
    demo2_substr_and_find();

    // =====================================
    // 练习1：字符统计员
    // =====================================
    exercise1_char_counter();

    // =====================================
    // 练习2：姓名拆分器
    // =====================================
    exercise2_name_splitter();

    // =====================================
    // 练习3：关键词替换器
    // =====================================
    exercise3_keyword_replacer();

    // =====================================
    // 挑战任务：信息加密与破译系统
    // =====================================
    challenge_encrypt_decrypt();

    // =====================================
    // 程序结束
    // =====================================
    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║     🎉  神探训练结束！恭喜毕业！  🎉      ║" << endl;
    cout << "╚══════════════════════════════════════════╝" << endl;

    return 0;
}

// ==================================================================
// 演示1：字符串长度和索引访问
// 功能：展示 length() 方法和 [] 索引访问的基本用法
// ==================================================================
void demo1_length_and_index() {
    cout << "══════════ 演示1：字符串长度和索引访问 ══════════" << endl;
    cout << endl;

    // --- 1.1 认识 length() ---
    cout << "📏 --- 1.1 length() 方法 ---" << endl;
    string word1 = "Hello";
    string word2 = "你好世界";
    string word3 = "C++编程123";

    cout << "字符串 \"" << word1 << "\" 的长度是：" << word1.length() << endl;
    cout << "字符串 \"" << word2 << "\" 的长度是：" << word2.length() << endl;
    cout << "字符串 \"" << word3 << "\" 的长度是：" << word3.length() << endl;
    // 注意：对于中文字符，在 UTF-8 编码下，string::length() 返回的是字节数
    // 但在本课的基础层面，我们简化把每个 char 视为一个"字符单位"
    cout << endl;

    // --- 1.2 认识索引[] ---
    cout << "🔢 --- 1.2 [] 索引访问 ---" << endl;
    string alphabet = "ABCDEFG";

    cout << "字符串：" << alphabet << endl;
    cout << "索引 0 → " << alphabet[0] << " （第1个字符）" << endl;
    cout << "索引 1 → " << alphabet[1] << " （第2个字符）" << endl;
    cout << "索引 3 → " << alphabet[3] << " （第4个字符）" << endl;
    cout << "索引 6 → " << alphabet[6] << " （最后一个字符）" << endl;

    // 演示用 length()-1 访问最后一个字符
    int lastIdx = alphabet.length() - 1;
    cout << "最后一个字符（用 length()-1）：" << alphabet[lastIdx] << endl;
    cout << endl;

    // --- 1.3 遍历字符串 ---
    cout << "🔄 --- 1.3 用 for 循环遍历字符串 ---" << endl;
    string name = "侦探柯南";
    cout << "遍历「" << name << "」的每个字符：" << endl;
    for (int i = 0; i < name.length(); i++) {
        cout << "  位置 " << i << "：「" << name[i] << "」" << endl;
    }
    cout << endl;

    // --- 1.4 反向遍历 ---
    cout << "◀️  --- 1.4 反向遍历（倒着念）---" << endl;
    cout << "倒序输出「" << name << "」：" << endl;
    cout << "  ";
    for (int i = name.length() - 1; i >= 0; i--) {
        cout << name[i];
    }
    cout << " ← 倒着念就是这样的！" << endl;
    cout << endl;
}

// ==================================================================
// 演示2：子串提取和查找操作
// 功能：展示 substr() 截取和 find() 搜索的用法
// ==================================================================
void demo2_substr_and_find() {
    cout << "══════════ 演示2：子串提取和查找操作 ══════════" << endl;
    cout << endl;

    // --- 2.1 substr() 基本用法 ---
    cout << "✂️  --- 2.1 substr() 截取子串 ---" << endl;
    string message = "嫌疑人在图书馆三楼";

    cout << "原始文本：「" << message << "」" << endl;
    cout << "长度：" << message.length() << endl;

    // substr(pos, len)：从 pos 开始截取 len 个字符
    string word1 = message.substr(0, 3);   // 前3个字
    string word2 = message.substr(3, 3);   // 从第4个字开始取3个
    string word3 = message.substr(6, 2);   // 从第7个字开始取2个

    cout << "  substr(0, 3) → " << word1 << " （嫌疑人）" << endl;
    cout << "  substr(3, 3) → " << word2 << " （在图书）" << endl;
    cout << "  substr(6, 2) → " << word3 << " （馆三）" << endl;
    cout << endl;

    // --- 2.2 substr() 省略第二个参数 ---
    cout << "📌 --- 2.2 substr(pos) 取到末尾 ---" << endl;
    string clue = "密码是473829";
    cout << "线索文本：「" << clue << "」" << endl;
    string password = clue.substr(4);  // 从索引4开始取到末尾
    cout << "  clue.substr(4) → " << password << " （取到末尾！）" << endl;
    cout << endl;

    // --- 2.3 find() 基本用法 ---
    cout << "🔍 --- 2.3 find() 查找关键词 ---" << endl;
    string report = "目击者说看到穿红色外套的人进入大楼";

    cout << "目击报告：「" << report << "」" << endl;

    // 查找"红色"
    int posRed = report.find("红色");
    if (posRed != string::npos) {
        cout << "  找到「红色」在位置 " << posRed << endl;
    } else {
        cout << "  没有找到「红色」" << endl;
    }

    // 查找"大楼"
    int posBuilding = report.find("大楼");
    if (posBuilding != string::npos) {
        cout << "  找到「大楼」在位置 " << posBuilding << endl;
    } else {
        cout << "  没有找到「大楼」" << endl;
    }

    // 查找不存在的词
    int posNot = report.find("汽车");
    if (posNot == string::npos) {
        cout << "  「汽车」没有找到（返回 string::npos）" << endl;
    }
    cout << endl;

    // --- 2.4 find() 从指定位置开始搜索 ---
    cout << "🔎 --- 2.4 find() 指定起始位置搜索 ---" << endl;
    string text = "abc abc abc abc";
    cout << "文本：「" << text << "」" << endl;

    int p1 = text.find("abc");          // 从开头找第一个
    int p2 = text.find("abc", p1 + 1);  // 从 p1+1 开始找第二个
    int p3 = text.find("abc", p2 + 1);  // 从 p2+1 开始找第三个

    cout << "  第1个 \"abc\" 在位置：" << p1 << endl;
    cout << "  第2个 \"abc\" 在位置：" << p2 << endl;
    cout << "  第3个 \"abc\" 在位置：" << p3 << endl;
    cout << endl;

    // --- 2.5 substr + find 综合实战 ---
    cout << "🕵️ --- 2.5 综合实战：提取关键信息 ---" << endl;
    string caseFile = "案件编号：XJ-2024-089，嫌疑人：张三，特征：戴眼镜、身高180cm";

    cout << "案卷：「" << caseFile << "」" << endl;

    // 提取案件编号
    int idStart = caseFile.find("XJ");
    string caseID = caseFile.substr(idStart, 11);
    cout << "  案件编号：" << caseID << endl;

    // 提取嫌疑人姓名
    int nameStart = caseFile.find("张三");
    string suspect = caseFile.substr(nameStart, 2);
    cout << "  嫌疑人：" << suspect << endl;

    // 提取特征
    int featStart = caseFile.find("特征：");
    string feature = caseFile.substr(featStart + 3);  // "+3" 跳过"特征："
    cout << "  特征：" << feature << endl;
    cout << endl;
}

// ==================================================================
// 练习1：字符统计员
// 功能：输入字符串，统计长度并逐个输出字符
// ==================================================================
void exercise1_char_counter() {
    cout << "══════════ 练习1：字符统计员 ══════════" << endl;
    cout << endl;

    string text;
    cout << "📝 请输入一段文字：";
    getline(cin, text);  // getline 可以读取包含空格的整行文字

    cout << endl;
    cout << "📊 统计结果：" << endl;
    cout << "  文字长度：" << text.length() << " 个字符" << endl;
    cout << "  逐个输出字符：" << endl;

    for (int i = 0; i < text.length(); i++) {
        cout << "    第 " << i << " 个字符：「" << text[i] << "」" << endl;
    }

    // 额外功能：统计字母、数字和其他字符
    int letterCount = 0;
    int digitCount = 0;
    int otherCount = 0;

    // 注意：对于中文字符（多字节），这里简化处理
    for (int i = 0; i < text.length(); i++) {
        char c = text[i];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            letterCount++;
        } else if (c >= '0' && c <= '9') {
            digitCount++;
        } else {
            otherCount++;
        }
    }

    cout << "  其中英文/字母数：" << letterCount << endl;
    cout << "  其中数字数：" << digitCount << endl;
    cout << "  其中其他字符：" << otherCount << endl;

    cout << endl;
}

// ==================================================================
// 练习2：姓名拆分器
// 功能：输入全名，拆分成姓氏和名字
// ==================================================================
void exercise2_name_splitter() {
    cout << "══════════ 练习2：姓名拆分器 ══════════" << endl;
    cout << endl;

    string fullName;
    cout << "👤 请输入你的全名：";
    cin >> fullName;

    cout << "📛 姓名分析：" << endl;
    cout << "  全名：「" << fullName << "」" << endl;
    cout << "  总长度：" << fullName.length() << " 个字符" << endl;

    string surname, givenName;

    // 判断是否为复姓（假设长度≥4的是复姓，如"欧阳修"=4个字）
    // 单姓常见长度为1个中文字符（在编程层面：1个char位置），名字1-2个字
    // 这里我们用长度来简单判断
    if (fullName.length() >= 4) {
        // 可能是复姓（如"欧阳修文"），姓占前2个字
        surname = fullName.substr(0, 2);
        givenName = fullName.substr(2);
        cout << "  🏷️  检测到疑似复姓！" << endl;
    } else {
        // 单姓，姓占第1个字
        surname = fullName.substr(0, 1);
        givenName = fullName.substr(1);
    }

    cout << "  姓氏：" << surname << endl;
    cout << "  名字：" << givenName << endl;

    // 巩固练习：使用 [] 获取首字母（名字的第一个字）
    if (givenName.length() > 0) {
        cout << "  名字的第一个字：" << givenName[0] << endl;
    }

    cout << endl;

    // 清除输入缓冲区（为后续 getline 做准备）
    cin.ignore();
}

// ==================================================================
// 练习3：关键词替换器
// 功能：输入一句话和关键词，把所有关键词替换为 [已加密]
// ==================================================================
void exercise3_keyword_replacer() {
    cout << "══════════ 练习3：关键词替换器 ══════════" << endl;
    cout << endl;

    string sentence, keyword;
    cout << "📝 请输入一句话：";
    getline(cin, sentence);
    cout << "🔑 请输入要加密的关键词：";
    getline(cin, keyword);

    cout << endl;
    cout << "📋 加密前：「" << sentence << "」" << endl;
    cout << "🔑 加密关键词：「" << keyword << "」" << endl;

    string replacement = "[已加密]";
    int pos = 0;
    int replaceCount = 0;

    // 循环查找并替换所有出现的关键词
    size_t searchPos = 0;
    while ((searchPos = sentence.find(keyword, searchPos)) != string::npos) {
        sentence.replace(searchPos, keyword.length(), replacement);
        searchPos += replacement.length();  // 跳过替换后的内容
        replaceCount++;
    }

    cout << "🔒 加密后：「" << sentence << "」" << endl;
    cout << "📊 共替换了 " << replaceCount << " 处关键词" << endl;

    if (replaceCount == 0) {
        cout << "💡 提示：句子中没有找到关键词「" << keyword << "」" << endl;
    }

    cout << endl;
}

// ==================================================================
// 挑战任务：信息加密与破译系统
// 功能：对消息进行加密（插入噪音字符）和破译（提取原消息）
// 加密规则：在每个原始字符后插入一个随机大写字母
// 密文格式："L" + 原长度 + ":" + 加密内容
// ==================================================================
void challenge_encrypt_decrypt() {
    cout << "══════════ 挑战任务：信息加密与破译系统 ══════════" << endl;
    cout << endl;

    // ===== 第一部分：加密 =====
    cout << "🔐 ===== 加密模式 =====" << endl;

    string original;
    cout << "请输入原始消息：";
    getline(cin, original);

    int originalLen = original.length();
    cout << "原始消息：「" << original << "」" << endl;
    cout << "原始长度：" << originalLen << " 个字符" << endl;

    // 构造密文：先加上长度标记
    string encrypted = "L" + to_string(originalLen) + ":";

    // 在每个字符之间插入随机大写字母作为噪音
    for (int i = 0; i < originalLen; i++) {
        encrypted += original[i];
        // 如果不是最后一个字符，插入噪音
        if (i < originalLen - 1) {
            char noise = 'A' + (rand() % 26);  // 随机大写字母 A-Z
            encrypted += noise;
        }
    }

    cout << "🔒 密文：「" << encrypted << "」" << endl;
    cout << "   格式说明：L + 原长度 + : + 加密数据" << endl;
    cout << "   加密数据格式：字符1+噪音+字符2+噪音+...（最后不加噪音）" << endl;
    cout << endl;

    // ===== 第二部分：破译 =====
    cout << "🔓 ===== 破译模式 =====" << endl;
    cout << "正在解析密文..." << endl;

    // 解析长度标记
    int colonPos = encrypted.find(':');
    string header = encrypted.substr(0, colonPos);  // 如 "L5"
    string lenStr = header.substr(1);                // 如 "5"

    // 把字符串转为整数
    int decodedLen = 0;
    for (int i = 0; i < lenStr.length(); i++) {
        decodedLen = decodedLen * 10 + (lenStr[i] - '0');
    }

    cout << "  长度标记解析：原始消息应有 " << decodedLen << " 个字符" << endl;

    // 提取加密数据部分（冒号后面的内容）
    string data = encrypted.substr(colonPos + 1);

    // 破译：从加密数据中每隔一个字符取一个（字符1, 字符3, 字符5...）
    // 因为加密格式是：原始字符 + 噪音 + 原始字符 + 噪音 + ...
    // 所以原始字符在索引 0, 2, 4, 6, ...
    string decrypted = "";
    for (int i = 0; i < data.length(); i += 2) {
        decrypted += data[i];
    }

    cout << "  提取的数据部分：「" << data << "」" << endl;
    cout << "🔓 破译结果：「" << decrypted << "」" << endl;

    // 验证
    cout << endl;
    cout << "✅ 验证：破译结果长度 = " << decrypted.length()
         << "，预期长度 = " << decodedLen << endl;

    if (decrypted == original) {
        cout << "✅ 验证通过！加密和破译完全正确！" << endl;
    } else {
        cout << "⚠️  警告：破译结果与原始消息不一致，请检查加密逻辑。" << endl;
    }

    cout << endl;
    cout << "📐 总结公式：" << endl;
    cout << "  加密数据长度 = 原始长度 × 2 - 1" << endl;
    cout << "  原始数据长度 = (加密数据长度 + 1) / 2" << endl;
    cout << endl;
}

/*
 * 程序结构总结：
 *
 * demo1_length_and_index()
 *   ├── 1.1 length() 方法
 *   ├── 1.2 [] 索引访问
 *   ├── 1.3 for 循环遍历字符串
 *   └── 1.4 反向遍历
 *
 * demo2_substr_and_find()
 *   ├── 2.1 substr(pos, len) 基本用法
 *   ├── 2.2 substr(pos) 取到末尾
 *   ├── 2.3 find() 基本用法
 *   ├── 2.4 find() 指定起始位置
 *   └── 2.5 substr + find 综合实战
 *
 * exercise1_char_counter()    —— 字符统计员
 * exercise2_name_splitter()   —— 姓名拆分器
 * exercise3_keyword_replacer() —— 关键词替换器
 *
 * challenge_encrypt_decrypt() —— 信息加密与破译系统
 *   ├── 加密：原始 → 插入噪音 → 密文
 *   └── 破译：密文 → 解析头部 → 隔位提取 → 明文
 */
