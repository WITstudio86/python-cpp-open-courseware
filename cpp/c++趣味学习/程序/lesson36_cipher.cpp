/*
 * =====================================================================
 * 第36课：密文特工队——字符串趣味应用
 * 大小写转换、凯撒加密 | 编写秘密暗号
 * =====================================================================
 *
 * 本文件包含以下程序演示：
 *   1. 使用 <cctype> 的 toupper/tolower 进行大小写转换
 *   2. 使用 ASCII 码手动进行大小写转换（不依赖库函数）
 *   3. 凯撒加密与解密（单字符 + 字符串）
 *   4. 交互式加密解密程序（可配置偏移量）
 *   5. 暴力破解凯撒密文
 *   6. 练习答案：大小写翻转 + 解密练习
 *
 * 编译方式：
 *   g++ -std=c++11 -o lesson36_cipher lesson36_cipher.cpp
 * 运行方式：
 *   ./lesson36_cipher
 *
 * 在程序运行时会显示菜单，选择对应的功能即可。
 * =====================================================================
 */

#include <iostream>
#include <string>
#include <cctype>   // 提供 toupper() 和 tolower()
using namespace std;

// =====================================================================
// 通用工具函数
// =====================================================================

/*
 * 功能：使用 cctype 库函数将字符转换为大写
 * 参数：ch - 待转换的字符
 * 返回：转换后的大写字符（如果是小写字母），否则返回原字符
 */
char toUpperLib(char ch) {
    return (char)toupper(ch);
}

/*
 * 功能：使用 cctype 库函数将字符转换为小写
 * 参数：ch - 待转换的字符
 * 返回：转换后的小写字符（如果是大写字母），否则返回原字符
 */
char toLowerLib(char ch) {
    return (char)tolower(ch);
}

/*
 * 功能：使用 ASCII 码手动将小写字母转换为大写（不依赖 cctype）
 * 原理：小写字母 ASCII 码比对应大写字母大 32
 * 参数：ch - 待转换的字符
 * 返回：转换后的大写字符（如果是小写字母），否则返回原字符
 */
char toUpperAscii(char ch) {
    if (ch >= 'a' && ch <= 'z') {
        // 方法1：直接减 32
        // return ch - 32;

        // 方法2：更专业、可读性更好的写法
        return ch - ('a' - 'A');   // 'a' - 'A' == 32
    }
    return ch;
}

/*
 * 功能：使用 ASCII 码手动将大写字母转换为小写（不依赖 cctype）
 * 原理：小写字母 ASCII 码比对应大写字母大 32
 * 参数：ch - 待转换的字符
 * 返回：转换后的小写字符（如果是大写字母），否则返回原字符
 */
char toLowerAscii(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        // 方法1：直接加 32
        // return ch + 32;

        // 方法2：更专业、可读性更好的写法
        return ch + ('a' - 'A');   // 'a' - 'A' == 32
    }
    return ch;
}

/*
 * 功能：凯撒加密 - 对单个字符进行加密
 * 原理：将字母按字母表顺序向后移动 shift 位
 *       非字母字符保持不变
 *       使用模运算 % 26 实现循环（如 Z 后移 1 位变成 A）
 * 参数：ch    - 待加密的字符
 *       shift - 偏移量（正数向后移，负数向前移）
 * 返回：加密后的字符
 */
char caesarEncryptChar(char ch, int shift) {
    // 处理大写字母 A~Z (ASCII: 65~90)
    if (ch >= 'A' && ch <= 'Z') {
        // 步骤拆解：
        // 1. ch - 'A'：将字母映射到 0~25 的数字
        // 2. + shift：加上偏移量
        // 3. % 26：取模，确保在 0~25 范围内循环
        // 4. + 'A'：映射回 ASCII 字符
        return (ch - 'A' + shift) % 26 + 'A';
    }
    // 处理小写字母 a~z (ASCII: 97~122)
    else if (ch >= 'a' && ch <= 'z') {
        return (ch - 'a' + shift) % 26 + 'a';
    }
    // 非字母字符（空格、数字、标点等）保持不变
    return ch;
}

/*
 * 功能：凯撒解密 - 对单个字符进行解密
 * 原理：将字母按字母表顺序向前移动 shift 位（即加密的逆操作）
 *       注意 C++ 中负数 % 正数可能得到负数，所以要先 +26
 * 参数：ch    - 待解密的字符
 *       shift - 偏移量（与加密时相同的值）
 * 返回：解密后的字符
 */
char caesarDecryptChar(char ch, int shift) {
    // 处理大写字母
    if (ch >= 'A' && ch <= 'Z') {
        // 解密公式：(ch - 'A' - shift + 26) % 26 + 'A'
        // 为什么 +26？因为 C++ 中 -1 % 26 的结果可能是 -1（取决于编译器），
        // 加上 26 后变成 25 % 26 = 25，即正确的循环结果。
        return (ch - 'A' - shift + 26) % 26 + 'A';
    }
    // 处理小写字母
    else if (ch >= 'a' && ch <= 'z') {
        return (ch - 'a' - shift + 26) % 26 + 'a';
    }
    // 非字母字符保持不变
    return ch;
}

/*
 * 功能：对整个字符串进行凯撒加密
 * 参数：text  - 明文字符串
 *       shift - 偏移量
 * 返回：加密后的密文字符串
 */
string caesarEncrypt(string text, int shift) {
    string result = "";
    for (int i = 0; i < text.length(); i++) {
        result += caesarEncryptChar(text[i], shift);
    }
    return result;
}

/*
 * 功能：对整个字符串进行凯撒解密
 * 参数：text  - 密文字符串
 *       shift - 偏移量（与加密时相同）
 * 返回：解密后的明文字符串
 */
string caesarDecrypt(string text, int shift) {
    string result = "";
    for (int i = 0; i < text.length(); i++) {
        result += caesarDecryptChar(text[i], shift);
    }
    return result;
}

// =====================================================================
// 程序 1：使用 cctype 库函数进行大小写转换
// =====================================================================
void demo1_cctypeCaseConversion() {
    cout << "\n==============================================" << endl;
    cout << "  程序 1：使用 <cctype> 库进行大小写转换" << endl;
    cout << "==============================================" << endl;

    // 测试字符数组
    char testChars[] = {'a', 'Z', 'm', 'Q', '3', '!', ' ', 'b'};
    int count = 8;

    cout << "原始字符： ";
    for (int i = 0; i < count; i++) {
        cout << testChars[i] << "  ";
    }
    cout << endl;

    cout << "转大写后： ";
    for (int i = 0; i < count; i++) {
        cout << toUpperLib(testChars[i]) << "  ";
    }
    cout << endl;

    cout << "转小写后： ";
    for (int i = 0; i < count; i++) {
        cout << toLowerLib(testChars[i]) << "  ";
    }
    cout << endl;

    // 展示字符串整体转换
    string message = "Hello, C++ World! 你好，编程世界！";
    cout << "\n原始字符串：" << message << endl;

    string upperStr = "";
    for (int i = 0; i < message.length(); i++) {
        upperStr += toupper(message[i]);
    }
    cout << "全部大写：  " << upperStr << endl;

    string lowerStr = "";
    for (int i = 0; i < message.length(); i++) {
        lowerStr += tolower(message[i]);
    }
    cout << "全部小写：  " << lowerStr << endl;

    // 注意：中文字符不是 ASCII 字母，toupper/tolower 对它们没有影响
    cout << "\n💡 注意：中文字符和标点符号不受 toupper/tolower 影响。" << endl;
}

// =====================================================================
// 程序 2：使用 ASCII 码手动进行大小写转换
// =====================================================================
void demo2_manualAsciiConversion() {
    cout << "\n==============================================" << endl;
    cout << "  程序 2：使用 ASCII 码手动进行大小写转换" << endl;
    cout << "==============================================" << endl;

    // 展示 ASCII 码表关键信息
    cout << "ASCII 码表关键数据：" << endl;
    cout << "  'A' 的 ASCII 码 = " << (int)'A' << endl;
    cout << "  'Z' 的 ASCII 码 = " << (int)'Z' << endl;
    cout << "  'a' 的 ASCII 码 = " << (int)'a' << endl;
    cout << "  'z' 的 ASCII 码 = " << (int)'z' << endl;
    cout << "  大小写差值 'a' - 'A' = " << ('a' - 'A') << endl;
    cout << endl;

    // 展示完整的 A~Z 和 a~z 对应关系
    cout << "字母对应关系表：" << endl;
    cout << "  大写 | ASCII |  小写 | ASCII | 差值" << endl;
    cout << "  -----|-------|-------|-------|-----" << endl;
    for (char c = 'A'; c <= 'Z'; c++) {
        char lower = c + ('a' - 'A');
        cout << "    " << c << "  |  "
             << (int)c << "   |   " << lower << "  |  "
             << (int)lower << "   |  " << (int)(lower - c) << endl;
    }

    // 测试字符串转换
    string testStr = "AbCdEfGhIjKlMnOpQrStUvWxYz";
    cout << "\n测试字符串（交替大小写）：" << testStr << endl;

    cout << "手动转大写（ASCII法）：";
    for (int i = 0; i < testStr.length(); i++) {
        cout << toUpperAscii(testStr[i]);
    }
    cout << endl;

    cout << "手动转小写（ASCII法）：";
    for (int i = 0; i < testStr.length(); i++) {
        cout << toLowerAscii(testStr[i]);
    }
    cout << endl;

    // 验证手动方法的结果与库函数一致
    cout << "\n✅ 手动方法与 <cctype> 库函数结果一致吗？" << endl;
    bool allMatch = true;
    for (int i = 0; i < testStr.length(); i++) {
        if (toUpperAscii(testStr[i]) != toupper(testStr[i]) ||
            toLowerAscii(testStr[i]) != tolower(testStr[i])) {
            allMatch = false;
            break;
        }
    }
    cout << (allMatch ? "  是的，完全一致！" : "  不，存在差异。") << endl;
}

// =====================================================================
// 程序 3：凯撒加密与解密演示
// =====================================================================
void demo3_caesarCipher() {
    cout << "\n==============================================" << endl;
    cout << "  程序 3：凯撒加密与解密演示" << endl;
    cout << "==============================================" << endl;

    cout << "\n--- 凯撒加密原理图解 ---" << endl;
    cout << "明文：A B C D E F G ... X Y Z" << endl;
    cout << "      ↓ ↓ ↓ ↓ ↓ ↓ ↓     ↓ ↓ ↓  (偏移量 = 3)" << endl;
    cout << "密文：D E F G H I J ... A B C" << endl;
    cout << endl;

    int shift = 3;
    cout << "使用偏移量 shift = " << shift << " 进行演示：" << endl << endl;

    // 演示单个字母的加密解密过程
    cout << "【单个字母演示】" << endl;
    char demoLetters[] = {'A', 'Z', 'a', 'z', 'H', 'e', 'l', 'o', ' ', '!'};
    int letterCount = 10;

    for (int i = 0; i < letterCount; i++) {
        char ch = demoLetters[i];
        char encrypted = caesarEncryptChar(ch, shift);
        char decrypted = caesarDecryptChar(encrypted, shift);

        cout << "  '" << ch << "' (ASCII:" << (int)ch << ")";
        // 用更宽的间距对齐
        if ((int)ch < 100) cout << " ";
        cout << " → 加密 → '" << encrypted
             << "' (ASCII:" << (int)encrypted << ")";
        if ((int)encrypted < 100) cout << " ";
        cout << " → 解密 → '" << decrypted
             << "' (ASCII:" << (int)decrypted << ")";
        cout << (ch == decrypted ? " ✅" : " ❌") << endl;
    }

    // 演示整句加密
    cout << "\n【整句加密演示】" << endl;
    string plainText1 = "HELLO WORLD";
    string cipherText1 = caesarEncrypt(plainText1, shift);
    string backText1 = caesarDecrypt(cipherText1, shift);

    cout << "  原文：" << plainText1 << endl;
    cout << "  密文：" << cipherText1 << endl;
    cout << "  解密：" << backText1 << endl;
    cout << "  验证：" << (plainText1 == backText1 ? "✅ 成功" : "❌ 失败") << endl;

    // 演示混合大小写的句子
    cout << "\n【混合大小写演示】" << endl;
    string plainText2 = "I love C++ Programming!";
    string cipherText2 = caesarEncrypt(plainText2, shift);
    string backText2 = caesarDecrypt(cipherText2, shift);

    cout << "  原文：" << plainText2 << endl;
    cout << "  密文：" << cipherText2 << endl;
    cout << "  解密：" << backText2 << endl;
    cout << "  验证：" << (plainText2 == backText2 ? "✅ 成功" : "❌ 失败") << endl;

    // 演示不同偏移量的效果
    cout << "\n【不同偏移量效果对比】" << endl;
    string testWord = "Secret";
    cout << "  原文 = \"" << testWord << "\"" << endl;
    for (int s = 1; s <= 5; s++) {
        cout << "  shift=" << s << " → \"" << caesarEncrypt(testWord, s) << "\"" << endl;
    }

    // ROT13 特例展示
    cout << "\n【ROT13 特例（shift=13）】" << endl;
    string rot13test = "Hello";
    string rot13once = caesarEncrypt(rot13test, 13);
    string rot13twice = caesarEncrypt(rot13once, 13);
    cout << "  原文　　　：" << rot13test << endl;
    cout << "  ROT13一次　：" << rot13once << endl;
    cout << "  ROT13两次　：" << rot13twice << endl;
    cout << "  💡 ROT13 加密两次等于原文！（因为 13 + 13 = 26 = 一圈）" << endl;
}

// =====================================================================
// 程序 4：交互式加密解密程序
// =====================================================================
void demo4_interactiveCipher() {
    cout << "\n==============================================" << endl;
    cout << "  程序 4：交互式加密解密程序" << endl;
    cout << "==============================================" << endl;

    int shift;
    string message;

    cout << "\n🔐 欢迎使用凯撒加密系统！" << endl;
    cout << "----------------------------------------------" << endl;

    // 获取偏移量
    cout << "请输入偏移量（建议 1~25）：";
    cin >> shift;

    // 确保偏移量在有效范围内（归一化到 1~25）
    shift = shift % 26;
    if (shift == 0) {
        cout << "⚠️  偏移量是 26 的倍数，密文和原文一样哦！" << endl;
        shift = 26; // 保持为 26，这样加密后等于原文，方便展示原理
    }
    if (shift < 0) {
        shift = shift + 26;  // 负数偏移量转为等价的正常移量
    }

    // 清除输入缓冲区（cin >> 后留下的换行符）
    cin.ignore();

    // 获取要加密的消息
    cout << "请输入要加密的消息：";
    getline(cin, message);

    cout << "\n----------------------------------------------" << endl;
    cout << "  加密参数" << endl;
    cout << "----------------------------------------------" << endl;
    cout << "  偏移量：" << shift << endl;
    cout << "  原文：\"" << message << "\"" << endl;

    // 加密
    string encrypted = caesarEncrypt(message, shift);
    cout << "  密文：\"" << encrypted << "\"" << endl;

    // 解密
    string decrypted = caesarDecrypt(encrypted, shift);
    cout << "  解密：\"" << decrypted << "\"" << endl;

    // 验证
    cout << "----------------------------------------------" << endl;
    if (message == decrypted) {
        cout << "  ✅ 加密解密成功！密文安全送达，特工任务完成！" << endl;
    } else {
        cout << "  ❌ 解密结果与原文不一致，请检查程序逻辑。" << endl;
    }
    cout << "==============================================" << endl;
}

// =====================================================================
// 程序 5：暴力破解凯撒密文
// =====================================================================
void demo5_bruteForce() {
    cout << "\n==============================================" << endl;
    cout << "  程序 5：暴力破解凯撒密文" << endl;
    cout << "==============================================" << endl;

    string cipherText;
    cout << "\n请输入要破解的凯撒密文：";
    cin.ignore();
    getline(cin, cipherText);

    cout << "\n📋 尝试所有可能的偏移量（1~25）：" << endl;
    cout << "----------------------------------------------" << endl;

    for (int s = 1; s <= 25; s++) {
        string attempt = caesarDecrypt(cipherText, s);
        // 如果偏移量小于 10，加个空格保持对齐
        cout << "  偏移量 ";
        if (s < 10) cout << " ";
        cout << s << " → \"" << attempt << "\"" << endl;
    }

    cout << "----------------------------------------------" << endl;
    cout << "💡 请从上面的 25 行中找到有意义的那一行，" << endl;
    cout << "   它对应的偏移量就是加密时使用的密钥！" << endl;
}

// =====================================================================
// 程序 6：练习答案 - 大小写翻转
// =====================================================================
void exercise1_flipCase() {
    cout << "\n==============================================" << endl;
    cout << "  练习 1 答案：大小写翻转" << endl;
    cout << "==============================================" << endl;

    string s;
    cout << "请输入字符串：";
    cin.ignore();
    getline(cin, s);

    // 方法1：使用 cctype 库函数
    string result1 = s;
    for (int i = 0; i < result1.length(); i++) {
        if (result1[i] >= 'a' && result1[i] <= 'z') {
            result1[i] = toupper(result1[i]);
        } else if (result1[i] >= 'A' && result1[i] <= 'Z') {
            result1[i] = tolower(result1[i]);
        }
    }

    // 方法2：使用 ASCII 码手动转换
    string result2 = s;
    for (int i = 0; i < result2.length(); i++) {
        if (result2[i] >= 'a' && result2[i] <= 'z') {
            result2[i] = result2[i] - ('a' - 'A');  // -32
        } else if (result2[i] >= 'A' && result2[i] <= 'Z') {
            result2[i] = result2[i] + ('a' - 'A');  // +32
        }
    }

    cout << "原始字符串：" << s << endl;
    cout << "方法1(cctype)：" << result1 << endl;
    cout << "方法2(ASCII)： " << result2 << endl;

    if (result1 == result2) {
        cout << "✅ 两种方法结果一致！" << endl;
    }
}

// =====================================================================
// 程序 7：练习答案 - 解密截获的密文
// =====================================================================
void exercise2_decryptMessage() {
    cout << "\n==============================================" << endl;
    cout << "  练习 2 答案：解密截获的密文" << endl;
    cout << "==============================================" << endl;

    // 截获的密文
    string cipher = "Xlmw mw e Jsvqirx irgvcTxiv!";
    int shift = 4;  // 已知加密时使用的偏移量

    cout << "截获的密文：" << cipher << endl;
    cout << "已知偏移量：" << shift << endl;

    // 解密
    string plain = "";
    for (int i = 0; i < cipher.length(); i++) {
        char ch = cipher[i];
        if (ch >= 'A' && ch <= 'Z') {
            ch = (ch - 'A' - shift + 26) % 26 + 'A';
        } else if (ch >= 'a' && ch <= 'z') {
            ch = (ch - 'a' - shift + 26) % 26 + 'a';
        }
        plain += ch;
    }

    cout << "解密后的明文：" << plain << endl;
    cout << "\n💡 密文 \"Xlmw mw e Jsvqirx irgvcTxiv!\" 解密后是：" << endl;
    cout << "   \"This is a Program encryption!\"（这是一个程序加密！）" << endl;
}

// =====================================================================
// 主菜单
// =====================================================================
int main() {
    int choice;
    bool running = true;

    while (running) {
        cout << "\n" << endl;
        cout << "╔════════════════════════════════════════════╗" << endl;
        cout << "║   🔐 第36课：密文特工队 - 程序演示菜单   ║" << endl;
        cout << "╠════════════════════════════════════════════╣" << endl;
        cout << "║  1. 大小写转换（<cctype> 库函数）         ║" << endl;
        cout << "║  2. 大小写转换（ASCII 码手动方式）         ║" << endl;
        cout << "║  3. 凯撒加密与解密完整演示                 ║" << endl;
        cout << "║  4. 交互式加密解密（可配置偏移量）         ║" << endl;
        cout << "║  5. 暴力破解凯撒密文                       ║" << endl;
        cout << "║  6. 练习1答案 - 大小写翻转                 ║" << endl;
        cout << "║  7. 练习2答案 - 解密截获密文               ║" << endl;
        cout << "║  0. 退出程序                               ║" << endl;
        cout << "╚════════════════════════════════════════════╝" << endl;
        cout << "请输入你的选择（0~7）：";
        cin >> choice;

        switch (choice) {
            case 1:
                demo1_cctypeCaseConversion();
                break;
            case 2:
                demo2_manualAsciiConversion();
                break;
            case 3:
                demo3_caesarCipher();
                break;
            case 4:
                demo4_interactiveCipher();
                break;
            case 5:
                demo5_bruteForce();
                break;
            case 6:
                exercise1_flipCase();
                break;
            case 7:
                exercise2_decryptMessage();
                break;
            case 0:
                cout << "\n👋 密文特工队任务结束，再见！" << endl;
                cout << "   记住：真正的安全需要更强大的加密算法哦~" << endl;
                running = false;
                break;
            default:
                cout << "\n⚠️  无效选择，请输入 0~7 之间的数字。" << endl;
                break;
        }
    }

    return 0;
}
