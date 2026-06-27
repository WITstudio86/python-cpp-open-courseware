/*
 * ==========================================
 *  第33课：字母大家族——字符类型
 *  知识点：char类型、ASCII码、字符运算、大小写转换、凯撒密码
 *  C++趣味学习系列
 *
 *  本程序包含以下演示模块：
 *    程序1 - char 类型的基本用法：声明、输入输出、ASCII查询
 *    程序2 - ASCII 编码表打印：用循环打印大写字母和小写字母的ASCII码对照表
 *    程序3 - 字符算术运算与大小写转换：演示字符加减和大小写互相转换
 *    程序4 - 简单凯撒密码：加密和解密单个字母
 *    练习答案 - 三个课后练习的参考实现（注释函数形式）
 *
 *  编译方法：
 *    g++ -std=c++11 lesson33_char_ascii.cpp -o lesson33_char_ascii
 *  运行方法：
 *    ./lesson33_char_ascii
 * ==========================================
 */

#include <iostream>
#include <cctype>    // 提供 isupper、islower、isdigit、toupper、tolower 等函数
#include <iomanip>   // 提供 setw 设置输出宽度
using namespace std;

// ============================================
// 练习答案函数：练习1 - ASCII侦探
// 输入一个字符，输出它的ASCII码
// ============================================
void exercise1_asciiDetective() {
    cout << "\n========== 练习1：ASCII侦探 ==========" << endl;
    cout << "输入一个字符，我会告诉你它的ASCII码！" << endl;

    char ch;
    cout << "请输入字符：";
    cin >> ch;

    // 将字符转换为整数，得到ASCII码
    int asciiValue = (int)ch;   // 或者写 int asciiValue = ch;

    cout << "字符 '" << ch << "' 的ASCII码是：" << asciiValue << endl;
    cout << endl;

    // 展示几个常见字符的ASCII码
    cout << "--- 常见字符速查 ---" << endl;
    cout << "'M' 的ASCII码 = " << (int)'M' << endl;
    cout << "'9' 的ASCII码 = " << (int)'9' << endl;
    cout << "ASCII码 100 对应字符 = " << (char)100 << endl;
    cout << "ASCII码 70 对应字符 = " << (char)70 << endl;
}

// ============================================
// 练习答案函数：练习2 - 大小写魔术师
// 输入大写字母，转小写，并后移5位
// ============================================
void exercise2_caseMagic() {
    cout << "\n========== 练习2：大小写魔术师 ==========" << endl;
    cout << "输入一个大写字母，我帮你转小写并后移5位！" << endl;

    char upper;
    cout << "请输入大写字母（A-Z）：";
    cin >> upper;

    // 检查是否为大写字母
    if (upper >= 'A' && upper <= 'Z') {
        // 方法1：用ASCII差值转换
        char lower = upper + 32;
        cout << "原字母 " << upper << " 的小写形式是：" << lower << endl;

        // 后移5位（以小写字母为基础）
        char shifted = lower + 5;

        // 超出'z'就回绕到'a'继续
        if (shifted > 'z') {
            shifted = shifted - 26;
        }

        cout << lower << " 后移5位变成：" << shifted << endl;

        // 也展示一下用 toupper/tolower 函数的方式
        cout << "\n💡 用 cctype 库函数也能实现：" << endl;
        cout << "  tolower('" << upper << "') = "
             << (char)tolower(upper) << endl;
    } else {
        cout << "❌ 请输入大写字母（A-Z）！你输入的不是大写字母哦。" << endl;
    }
}

// ============================================
// 练习答案函数：练习3 - 字符分类器
// 输入一个字符，判断类型
// ============================================
void exercise3_charClassifier() {
    cout << "\n========== 练习3：字符分类器 ==========" << endl;
    cout << "输入一个字符，我帮你分类！" << endl;

    char ch;
    cout << "请输入任意一个字符：";
    cin >> ch;

    cout << "\n--- 分析结果 ---" << endl;
    cout << "字符：'" << ch << "'" << endl;
    cout << "ASCII码：" << (int)ch << endl;
    cout << "分类：";

    // 用ASCII范围判断字符类型
    if (ch >= 'A' && ch <= 'Z') {
        cout << "大写字母" << endl;
    } else if (ch >= 'a' && ch <= 'z') {
        cout << "小写字母" << endl;
    } else if (ch >= '0' && ch <= '9') {
        cout << "数字字符" << endl;
    } else if (ch == ' ') {
        cout << "空格" << endl;
    } else {
        cout << "其他字符（可能是标点符号或特殊符号）" << endl;
    }

    // 展示用 cctype 库函数的判断方式
    cout << "\n💡 用 cctype 库函数判断结果：" << endl;
    cout << "  isupper('" << ch << "') = "
         << (isupper(ch) ? "true（是大写）" : "false（不是大写）") << endl;
    cout << "  islower('" << ch << "') = "
         << (islower(ch) ? "true（是小写）" : "false（不是小写）") << endl;
    cout << "  isdigit('" << ch << "') = "
         << (isdigit(ch) ? "true（是数字）" : "false（不是数字）") << endl;
    cout << "  isalpha('" << ch << "') = "
         << (isalpha(ch) ? "true（是字母）" : "false（不是字母）") << endl;
}

// ============================================
// 挑战任务：完整凯撒密码加密/解密系统
// 输入任意英文句子，指定偏移量进行加密和解密
// ============================================
void challenge_caesarCipher() {
    cout << "\n========== 🔐 挑战任务：完整的凯撒密码系统 ==========" << endl;

    // 先吃掉之前输入的换行符（因为可能前面用了cin >> 读取）
    cin.ignore();

    // 1. 输入明文
    string plaintext;
    cout << "请输入一句英文（仅小写字母和空格）：" << endl;
    cout << "> ";
    getline(cin, plaintext);

    // 2. 输入偏移量
    int shift;
    cout << "请输入偏移量（1~25）：";
    cin >> shift;

    // 验证偏移量
    if (shift < 1 || shift > 25) {
        cout << "❌ 偏移量必须在1~25之间！" << endl;
        return;
    }

    // 3. 加密过程
    string ciphertext = "";  // 存储密文
    for (int i = 0; i < plaintext.length(); i++) {
        char c = plaintext[i];
        if (c == ' ') {
            // 空格保持不变
            ciphertext += ' ';
        } else if (c >= 'a' && c <= 'z') {
            // 加密公式：(c - 'a' + shift) % 26 + 'a'
            // 解释：
            //   c - 'a'   → 把字母变成 0~25 的数字
            //   + shift   → 加上偏移量
            //   % 26      → 取余，保证不超出字母表范围（回绕到开头）
            //   + 'a'     → 变回小写字母
            char encrypted = (c - 'a' + shift) % 26 + 'a';
            ciphertext += encrypted;
        } else {
            // 其他字符（如大写、标点）保持原样
            ciphertext += c;
        }
    }

    // 4. 输出加密结果
    cout << "\n--- 加密结果 ---" << endl;
    cout << "原文：" << plaintext << endl;
    cout << "偏移量：" << shift << " 位" << endl;
    cout << "密文：" << ciphertext << endl;

    // 5. 解密验证
    string decrypted = "";
    for (int i = 0; i < ciphertext.length(); i++) {
        char c = ciphertext[i];
        if (c == ' ') {
            decrypted += ' ';
        } else if (c >= 'a' && c <= 'z') {
            // 解密就是反向偏移：
            // 26 - shift 相当于前移 shift 位并处理回绕
            char original = (c - 'a' + (26 - shift)) % 26 + 'a';
            decrypted += original;
        } else {
            decrypted += c;
        }
    }

    cout << "\n--- 解密验证 ---" << endl;
    cout << "密文：" << ciphertext << endl;
    cout << "解密后：" << decrypted << endl;

    if (decrypted == plaintext) {
        cout << "✅ 解密成功！密文已正确还原为原文！" << endl;
    } else {
        cout << "❌ 解密出现偏差，请检查程序。" << endl;
    }

    // 算法小课堂
    cout << "\n💡 算法揭秘：" << endl;
    cout << "  加密公式：(字母 - 'a' + 偏移量) % 26 + 'a'" << endl;
    cout << "  为什么要 % 26？因为英文字母有26个，取余确保" << endl;
    cout << "  不管偏移多少位都能正确回绕。比如 'z' + 3 = 'c'，" << endl;
    cout << "  因为 (25 + 3) % 26 = 2，对应字母 'c'。" << endl;
}

// ============================================
// 主函数
// ============================================
int main() {
    // 程序标题
    cout << "╔════════════════════════════════════╗" << endl;
    cout << "║   第33课：字母大家族——字符类型    ║" << endl;
    cout << "║   char、ASCII码、字符运算         ║" << endl;
    cout << "╚════════════════════════════════════╝" << endl;
    cout << endl;

    // ==========================================
    // 程序1：char 类型的基本用法
    // 演示：声明char变量、输入输出、ASCII码查询
    // ==========================================
    {
        cout << "╔════════════════════════════════════╗" << endl;
        cout << "║  程序1：char 类型基本用法         ║" << endl;
        cout << "╚════════════════════════════════════╝" << endl;
        cout << endl;

        // 1.1 声明并初始化char变量
        cout << "--- 声明 char 变量 ---" << endl;
        char grade = 'A';        // 成绩等级
        char symbol = '#';       // 特殊符号
        char digitChar = '7';    // 数字字符（不是数字7！）
        char space = ' ';        // 空格字符

        cout << "成绩等级字符：'" << grade << "'" << endl;
        cout << "特殊符号：'" << symbol << "'" << endl;
        cout << "数字字符：'" << digitChar << "'（注意：这不是数字7！）" << endl;
        cout << "空格字符：'" << space << "'（你看不到它，但它在！）" << endl;

        // 1.2 展示字符和其ASCII码的对应关系
        cout << "\n--- 字符 vs ASCII码 ---" << endl;
        cout << "字符 '" << grade << "' 的ASCII码是：" << (int)grade
             << "（用 (int)grade 转换得到）" << endl;
        cout << "字符 '" << digitChar << "' 的ASCII码是：" << (int)digitChar << endl;

        // 1.3 从ASCII码反查字符
        cout << "\n--- ASCII码 → 字符 ---" << endl;
        cout << "ASCII码 65 对应的字符是：'" << (char)65 << "'" << endl;
        cout << "ASCII码 97 对应的字符是：'" << (char)97 << "'" << endl;
        cout << "ASCII码 48 对应的字符是：'" << (char)48 << "'" << endl;

        // 1.4 验证字符'7'不等于数字7
        cout << "\n--- ⚠️ 重要：字符'7' ≠ 数字7 ---" << endl;
        cout << "  C++代码：     cout << '7' + 1" << endl;
        cout << "  输出结果：    " << digitChar + 1 << "（因为 '7' 的ASCII码55 + 1 = 56）" << endl;
        cout << "  而：          cout << 7 + 1" << endl;
        cout << "  输出结果：    " << 7 + 1 << endl;
        cout << "  两者完全不同！单引号里的'7'是一个字符，不是数字。" << endl;

        // 1.5 交互式ASCII查询
        cout << "\n--- 🔍 交互式ASCII码查询 ---" << endl;
        cout << "请输入一个字符，我告诉你它的ASCII码：";
        char query;
        cin >> query;
        cout << "字符 '" << query << "' 的ASCII码 = " << (int)query << endl;
        cout << endl;
    }

    // ==========================================
    // 程序2：ASCII编码表打印
    // 演示：用for循环打印大写字母、小写字母的ASCII码对照表
    // ==========================================
    {
        cout << "╔════════════════════════════════════╗" << endl;
        cout << "║  程序2：ASCII编码表打印           ║" << endl;
        cout << "╚════════════════════════════════════╝" << endl;
        cout << endl;

        // 2.1 打印大写字母表（A~Z）及ASCII码
        cout << "--- 大写字母 ASCII 码对照表 ---" << endl;
        cout << "┌──────┬──────┬──────┐" << endl;
        cout << "│ 序号 │ 字母 │ ASCII│" << endl;
        cout << "├──────┼──────┼──────┤" << endl;
        int index = 1;
        for (char c = 'A'; c <= 'Z'; c++) {
            cout << "│  " << setw(3) << index
                 << " │  '" << c << "'  │  " << setw(3) << (int)c << " │" << endl;
            index++;
        }
        cout << "└──────┴──────┴──────┘" << endl;

        // 2.2 打印小写字母表（a~z）及ASCII码
        cout << "\n--- 小写字母 ASCII 码对照表 ---" << endl;
        cout << "┌──────┬──────┬──────┐" << endl;
        cout << "│ 序号 │ 字母 │ ASCII│" << endl;
        cout << "├──────┼──────┼──────┤" << endl;
        index = 1;
        for (char c = 'a'; c <= 'z'; c++) {
            cout << "│  " << setw(3) << index
                 << " │  '" << c << "'  │  " << setw(3) << (int)c << " │" << endl;
            index++;
        }
        cout << "└──────┴──────┴──────┘" << endl;

        // 2.3 打印数字字符（0~9）的ASCII码
        cout << "\n--- 数字字符 ASCII 码对照表 ---" << endl;
        cout << "┌──────┬──────┬──────┐" << endl;
        cout << "│ 序号 │ 字符 │ ASCII│" << endl;
        cout << "├──────┼──────┼──────┤" << endl;
        for (char c = '0'; c <= '9'; c++) {
            cout << "│  " << setw(3) << (c - '0' + 1)
                 << " │  '" << c << "'  │  " << setw(3) << (int)c << " │" << endl;
        }
        cout << "└──────┴──────┴──────┘" << endl;

        // 2.4 重要规律总结
        cout << "\n📐 重要规律总结：" << endl;
        cout << "  ① 大写字母 'A'~'Z' → ASCII码 65~90" << endl;
        cout << "  ② 小写字母 'a'~'z' → ASCII码 97~122" << endl;
        cout << "  ③ 数字字符 '0'~'9' → ASCII码 48~57" << endl;
        cout << "  ④ 大写字母 + 32 = 对应小写字母" << endl;
        cout << "  ⑤ 小写字母 - 32 = 对应大写字母" << endl;
        cout << "  ⑥ ASCII码顺序：数字字符 < 大写字母 < 小写字母" << endl;
        cout << "     验证：" << (int)'9' << " < " << (int)'A'
             << " < " << (int)'a' << " ✓" << endl;
        cout << endl;
    }

    // ==========================================
    // 程序3：字符算术运算与大小写转换
    // 演示：字符加减法、大小写互相转换的两种方法
    // ==========================================
    {
        cout << "╔════════════════════════════════════╗" << endl;
        cout << "║  程序3：字符运算与大小写转换      ║" << endl;
        cout << "╚════════════════════════════════════╝" << endl;
        cout << endl;

        // 3.1 字符算术运算
        cout << "--- 字符做加法 ---" << endl;
        char base = 'A';
        cout << "从 '" << base << "' 开始：" << endl;
        for (int i = 0; i <= 25; i += 5) {
            cout << "  加" << i << "位 → '" << (char)(base + i) << "'"
                 << " (ASCII码：" << (int)(base + i) << ")" << endl;
        }

        // 3.2 大小写转换（方法1：直接加减32）
        cout << "\n--- 大小写转换（方法1：加减32） ---" << endl;
        char original1 = 'H';
        cout << "原字母：" << original1 << " (ASCII码：" << (int)original1 << ")" << endl;

        char upperToLower = original1 + 32;  // 大写→小写
        cout << "转小写（+32）：" << upperToLower
             << " (ASCII码：" << (int)upperToLower << ")" << endl;

        char lowerToUpper = upperToLower - 32;  // 小写→大写
        cout << "再转大写（-32）：" << lowerToUpper
             << " (ASCII码：" << (int)lowerToUpper << ")" << endl;

        // 3.3 大小写转换（方法2：用cctype库函数）
        cout << "\n--- 大小写转换（方法2：cctype库函数） ---" << endl;
        char original2 = 'z';
        cout << "原字母：" << original2 << endl;
        cout << "toupper()：" << (char)toupper(original2)
             << " → '" << (char)toupper(original2) << "'" << endl;

        original2 = 'G';
        cout << "原字母：" << original2 << endl;
        cout << "tolower()：" << (char)tolower(original2)
             << " → '" << (char)tolower(original2) << "'" << endl;

        // 3.4 字符比较演示
        cout << "\n--- 字符比较 ---" << endl;
        cout << "请输入两个字符，我帮你比较它们的 ASCII 码大小：" << endl;

        char char1, char2;
        cout << "第1个字符：";
        cin >> char1;
        cout << "第2个字符：";
        cin >> char2;

        cout << "\n'" << char1 << "' 的 ASCII码 = " << (int)char1 << endl;
        cout << "'" << char2 << "' 的 ASCII码 = " << (int)char2 << endl;

        if (char1 > char2) {
            cout << "结果：'" << char1 << "' > '" << char2 << "'（"
                 << (int)char1 << " > " << (int)char2 << "）" << endl;
        } else if (char1 < char2) {
            cout << "结果：'" << char1 << "' < '" << char2 << "'（"
                 << (int)char1 << " < " << (int)char2 << "）" << endl;
        } else {
            cout << "结果：'" << char1 << "' == '" << char2 << "'（两个字符相同）" << endl;
        }

        // 3.5 判断字符类型
        cout << "\n--- 字符类型判断 ---" << endl;
        cout << "请输入一个字符，我判断它的类型：" << endl;
        char typeChar;
        cout << "输入字符：";
        cin >> typeChar;

        cout << "\n字符 '" << typeChar << "' 的判断结果：" << endl;
        cout << "  isalpha（是字母）：" << (isalpha(typeChar) ? "✓" : "✗") << endl;
        cout << "  isupper（是大写）：" << (isupper(typeChar) ? "✓" : "✗") << endl;
        cout << "  islower（是小写）：" << (islower(typeChar) ? "✓" : "✗") << endl;
        cout << "  isdigit（是数字）：" << (isdigit(typeChar) ? "✓" : "✗") << endl;
        cout << "  isspace（是空白）：" << (isspace(typeChar) ? "✓" : "✗") << endl;
        cout << endl;
    }

    // ==========================================
    // 程序4：简单凯撒密码加密器
    // 演示：输入一个字母，后移3位加密，前移3位解密
    // ==========================================
    {
        cout << "╔════════════════════════════════════╗" << endl;
        cout << "║  程序4：🔐 凯撒密码加密解密器     ║" << endl;
        cout << "╚════════════════════════════════════╝" << endl;
        cout << endl;
        cout << "规则：把每个小写字母后移3位进行加密" << endl;
        cout << "      例如：a→d, b→e, ..., x→a, y→b, z→c" << endl;
        cout << "      解密时反方向前移3位即可" << endl;
        cout << endl;

        // 输入需要加密的字母
        char letter;
        cout << "请输入一个小写字母（a-z）进行加密：";
        cin >> letter;

        // 判断是否为小写字母
        if (letter >= 'a' && letter <= 'z') {
            // 加密：后移3位
            char encrypted = letter + 3;

            // 处理超出'z'的情况（回绕到'a'）
            if (encrypted > 'z') {
                encrypted = encrypted - 26;  // 26个字母，绕回来
            }

            // 解密：前移3位
            char decrypted = encrypted - 3;
            if (decrypted < 'a') {
                decrypted = decrypted + 26;  // 回绕到'z'
            }

            // 输出结果
            cout << "\n--- 🔐 加密解密过程 ---" << endl;
            cout << "原文   '" << letter << "'\tASCII码：" << (int)letter << endl;

            // 展示计算步骤
            cout << "加密计算：'" << letter << "' + 3" << endl;
            if (letter + 3 > 'z') {
                cout << "  → " << (int)(letter) << " + 3 = " << (int)(letter) + 3
                     << "，超出'z'(" << (int)'z' << ")，回绕-" << 26
                     << " = " << (int)encrypted
                     << " → '" << encrypted << "'" << endl;
            } else {
                cout << "  → " << (int)(letter) << " + 3 = " << (int)(letter) + 3
                     << " → '" << encrypted << "'" << endl;
            }
            cout << "密文   '" << encrypted << "'\tASCII码：" << (int)encrypted << endl;

            cout << "\n解密计算：'" << encrypted << "' - 3" << endl;
            cout << "  → " << (int)(encrypted) << " - 3 = " << (int)decrypted
                 << " → '" << decrypted << "'" << endl;
            cout << "解密后 '" << decrypted << "'\tASCII码：" << (int)decrypted << endl;

            // 验证
            if (decrypted == letter) {
                cout << "\n✅ 解密成功！结果与原文一致！" << endl;
            }

            // 展示所有字母的加密对照表
            cout << "\n--- 完整加密对照表（偏移3位） ---" << endl;
            cout << "原文：a b c d e f g h i j k l m n o p q r s t u v w x y z" << endl;
            cout << "密文：";
            for (char c = 'a'; c <= 'z'; c++) {
                char enc = c + 3;
                if (enc > 'z') enc -= 26;
                cout << enc << " ";
            }
            cout << endl;

        } else {
            cout << "❌ 请输入小写字母（a-z）！" << endl;
        }
        cout << endl;
    }

    // ==========================================
    // 课后练习参考答案演示
    // 执行前提示用户
    // ==========================================
    cout << "╔════════════════════════════════════╗" << endl;
    cout << "║  课后练习参考答案演示              ║" << endl;
    cout << "╚════════════════════════════════════╝" << endl;

    // 练习1：ASCII侦探
    exercise1_asciiDetective();

    // 练习2：大小写魔术师
    exercise2_caseMagic();

    // 练习3：字符分类器
    exercise3_charClassifier();

    // ==========================================
    // 挑战任务：完整凯撒密码加密/解密系统
    // ==========================================
    cout << "\n╔════════════════════════════════════╗" << endl;
    cout << "║  🏆 挑战任务：凯撒密码系统        ║" << endl;
    cout << "╚════════════════════════════════════╝" << endl;

    char runChallenge;
    cout << "\n是否运行挑战任务——完整凯撒密码系统？(y/n)：";
    cin >> runChallenge;
    if (runChallenge == 'y' || runChallenge == 'Y') {
        challenge_caesarCipher();
    } else {
        cout << "跳过挑战任务。你可以以后自己运行试试！" << endl;
    }

    // ==========================================
    // 课程总结
    // ==========================================
    cout << "\n╔══════════════════════════════════════════════╗" << endl;
    cout << "║  📝 本课核心知识点总结                      ║" << endl;
    cout << "╠══════════════════════════════════════════════╣" << endl;
    cout << "║  1. char类型  → 存储单个字符，用单引号      ║" << endl;
    cout << "║  2. ASCII编码 → 字符背后的数字身份证        ║" << endl;
    cout << "║      大写 A-Z: 65~90                         ║" << endl;
    cout << "║      小写 a-z: 97~122                        ║" << endl;
    cout << "║      数字 0-9: 48~57                         ║" << endl;
    cout << "║  3. 大小写转换 → 大写+32=小写，小写-32=大写 ║" << endl;
    cout << "║  4. 字符运算   → 字符可以加减整数           ║" << endl;
    cout << "║  5. 字符比较   → 按ASCII码比大小            ║" << endl;
    cout << "║  6. 凯撒密码   → 利用ASCII偏移实现加密      ║" << endl;
    cout << "╠══════════════════════════════════════════════╣" << endl;
    cout << "║  🔑 口诀：                                   ║" << endl;
    cout << "║  字母背后藏数字，ASCII编码记心间；          ║" << endl;
    cout << "║  大写小写差三二，字符也能做加减；            ║" << endl;
    cout << "║  加密解密都靠它，密码达人就是你！            ║" << endl;
    cout << "╚══════════════════════════════════════════════╝" << endl;

    cout << "\n程序结束。感谢学习第33课：字母大家族——字符类型！" << endl;

    return 0;
}
