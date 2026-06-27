/*
 * CSP-J 备考课程
 * 第16课：string 类与字符处理
 * 考纲知识点：string类定义/输入/拼接/比较/长度/子串/查找、字符判断函数
 *
 * 本文件包含：
 * 1. string 类的定义与初始化
 * 2. 输入方式对比（cin vs getline）
 * 3. 拼接、比较、长度、子串、查找演示
 * 4. 字符判断函数演示（isdigit/isalpha/islower/isupper/tolower/toupper）
 * 5. 字符统计综合练习
 * 6. 真题AC代码
 *
 * 编译：g++ -std=c++11 lesson16_string类与字符处理.cpp -o lesson16
 * 运行：./lesson16
 */

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// ============================================
// 演示1：string 的定义与初始化
// ============================================
void demo1_definition() {
    cout << "====== 演示1：string 的定义与初始化 ======" << endl;

    string s1;                     // 空字符串
    string s2 = "hello";           // 用字面量初始化
    string s3("world");            // 构造函数方式
    string s4 = s2;                // 拷贝初始化
    string s5(5, 'a');             // 重复字符 "aaaaa"
    string s6 = s2 + " " + s3;     // 拼接初始化

    cout << "s1 = \"" << s1 << "\" (空字符串)" << endl;
    cout << "s2 = \"" << s2 << "\"" << endl;
    cout << "s3 = \"" << s3 << "\"" << endl;
    cout << "s4 = \"" << s4 << "\" (拷贝s2)" << endl;
    cout << "s5 = \"" << s5 << "\" (5个'a')" << endl;
    cout << "s6 = \"" << s6 << "\" (拼接)" << endl;

    // string 与 C 风格字符串的转换
    const char* cstr = s6.c_str();
    cout << "s6.c_str() = \"" << cstr << "\"" << endl;

    cout << endl;
}

// ============================================
// 演示2：string 的输入方式
// ============================================
void demo2_input() {
    cout << "====== 演示2：string 的输入方式 ======" << endl;

    string s;

    // cin >> s：遇空格停止
    cout << "请输入一个单词（不要含空格）：";
    cin >> s;
    cout << "cin >> s 结果：\"" << s << "\"" << endl;

    cin.ignore();  // 清除换行符

    // getline：读取整行
    cout << "请输入一句话（可含空格）：";
    getline(cin, s);
    cout << "getline 结果：\"" << s << "\"" << endl;

    // 混用陷阱演示
    cout << "\n--- 混用cin和getline的陷阱演示 ---" << endl;
    int n;
    cout << "请输入一个整数：";
    cin >> n;
    cout << "你输入了：" << n << endl;

    // 如果没有 cin.ignore()，下面的 getline 会立即读到空行
    cout << "（使用 cin.ignore() 清除换行符后）请输入一行文字：";
    cin.ignore();
    getline(cin, s);
    cout << "getline 结果：\"" << s << "\"" << endl;

    cout << endl;
}

// ============================================
// 演示3：string 基本操作（拼接/比较/长度）
// ============================================
void demo3_basic_operations() {
    cout << "====== 演示3：拼接、比较、长度 ======" << endl;

    // 拼接
    string s1 = "Hello";
    string s2 = "World";
    string s3 = s1 + " " + s2;
    cout << "拼接 s1 + \" \" + s2 = \"" << s3 << "\"" << endl;

    s1 += " CSP-J";
    cout << "s1 += \" CSP-J\" → \"" << s1 << "\"" << endl;

    // 比较
    string a = "abc", b = "abd", c = "abc";
    cout << "\"abc\" == \"abc\" : " << (a == c) << " (1=true)" << endl;
    cout << "\"abc\" != \"abd\" : " << (a != b) << " (1=true)" << endl;
    cout << "\"abc\" <  \"abd\" : " << (a < b)  << " (1=true, 'c'<'d')" << endl;
    cout << "\"ab\"  <  \"abc\" : " << (string("ab") < string("abc"))
         << " (1=true, 短<长)" << endl;
    cout << "\"Apple\" < \"apple\" : " << (string("Apple") < string("apple"))
         << " (1=true, 'A'(65) < 'a'(97))" << endl;

    // 长度
    cout << "\n\"" << s3 << "\" 的长度：" << s3.length() << endl;
    cout << ".length() 和 .size() 等价：" << (s3.length() == s3.size()) << endl;

    // 访问单个字符
    cout << "s3[0] = '" << s3[0] << "'" << endl;
    cout << "s3[6] = '" << s3[6] << "'" << endl;

    cout << endl;
}

// ============================================
// 演示4：子串 .substr() 和查找 .find()
// ============================================
void demo4_substr_find() {
    cout << "====== 演示4：子串与查找 ======" << endl;

    string s = "Hello World, Hello CSP-J!";
    cout << "原始字符串：\"" << s << "\" (长度: " << s.length() << ")" << endl;

    // substr
    cout << "\n--- substr 演示 ---" << endl;
    cout << "s.substr(0, 5)   = \"" << s.substr(0, 5) << "\" (从0开始取5个)" << endl;
    cout << "s.substr(6, 5)   = \"" << s.substr(6, 5) << "\" (从6开始取5个)" << endl;
    cout << "s.substr(13)     = \"" << s.substr(13) << "\" (从13开始到末尾)" << endl;
    cout << "s.substr(0, 100) = \"" << s.substr(0, 100) << "\" (len超范围，取到末尾)" << endl;

    // find
    cout << "\n--- find 演示 ---" << endl;
    size_t pos1 = s.find("World");
    cout << "s.find(\"World\")     = " << pos1 << " (第一次出现的位置)" << endl;

    size_t pos2 = s.find("Hello");
    cout << "s.find(\"Hello\")     = " << pos2 << " (第一次出现在开头)" << endl;

    size_t pos3 = s.find("XYZ");
    cout << "s.find(\"XYZ\")       = " << pos3;
    if (pos3 == string::npos) {
        cout << " (string::npos，未找到)" << endl;
    }

    // 从指定位置开始查找
    size_t pos4 = s.find("Hello", 1);  // 从索引1开始查找
    cout << "s.find(\"Hello\", 1)  = " << pos4 << " (跳过第一个，找第二个Hello)" << endl;

    // string::npos 的值
    cout << "\nstring::npos 的值 = " << string::npos << endl;

    cout << endl;
}

// ============================================
// 演示5：字符判断函数
// ============================================
void demo5_char_functions() {
    cout << "====== 演示5：字符判断函数 ======" << endl;

    char test_chars[] = {'A', 'z', '5', ' ', '@', 'm', 'Z', '0', '9', '\n'};

    cout << "字符\tisdigit\tisalpha\tislower\tisupper\tisalnum\tisspace" << endl;
    cout << "----\t-------\t-------\t-------\t-------\t-------\t-------" << endl;

    for (int i = 0; i < 10; i++) {
        char c = test_chars[i];
        cout << "'" << (c == '\n' ? "\\n"[0] ? '?' : c : c) << "'";
        if (c == '\n') cout << "(换行)";
        cout << "\t" << (isdigit(c) ? "✓" : " ")
             << "\t" << (isalpha(c) ? "✓" : " ")
             << "\t" << (islower(c) ? "✓" : " ")
             << "\t" << (isupper(c) ? "✓" : " ")
             << "\t" << (isalnum(c) ? "✓" : " ")
             << "\t" << (isspace(c) ? "✓" : " ") << endl;
    }

    // 大小写转换
    cout << "\n--- 大小写转换 ---" << endl;
    cout << "tolower('A') = '" << (char)tolower('A') << "'" << endl;
    cout << "tolower('Z') = '" << (char)tolower('Z') << "'" << endl;
    cout << "toupper('a') = '" << (char)toupper('a') << "'" << endl;
    cout << "toupper('z') = '" << (char)toupper('z') << "'" << endl;
    cout << "tolower('5') = '" << (char)tolower('5') << "' (数字不变)" << endl;
    cout << "toupper('@') = '" << (char)toupper('@') << "' (符号不变)" << endl;

    cout << endl;
}

// ============================================
// 演示6：字符统计综合练习
// ============================================
void demo6_char_statistics() {
    cout << "====== 演示6：字符统计综合练习 ======" << endl;

    string s;
    cout << "请输入任意字符串：";
    cin.ignore();  // 清除可能残留的换行符
    getline(cin, s);

    int digit_cnt = 0, upper_cnt = 0, lower_cnt = 0;
    int space_cnt = 0, other_cnt = 0;

    for (char c : s) {
        if (isdigit(c))         digit_cnt++;
        else if (isupper(c))    upper_cnt++;
        else if (islower(c))    lower_cnt++;
        else if (isspace(c))    space_cnt++;
        else                    other_cnt++;
    }

    cout << "\n统计结果：" << endl;
    cout << "  数字字符：" << digit_cnt << endl;
    cout << "  大写字母：" << upper_cnt << endl;
    cout << "  小写字母：" << lower_cnt << endl;
    cout << "  空白字符：" << space_cnt << endl;
    cout << "  其他字符：" << other_cnt << endl;
    cout << "  总字符数：" << s.length() << endl;

    cout << endl;
}

// ============================================
// 演示7：大小写翻转
// ============================================
void demo7_case_flip() {
    cout << "====== 演示7：大小写翻转 ======" << endl;

    string s;
    cout << "请输入一个字符串：";
    cin.ignore();
    getline(cin, s);

    cout << "原始字符串：\"" << s << "\"" << endl;

    // 使用引用 &c 直接修改原字符串
    for (char &c : s) {
        if (isupper(c)) {
            c = tolower(c);
        } else if (islower(c)) {
            c = toupper(c);
        }
    }

    cout << "翻转后：    \"" << s << "\"" << endl;

    cout << endl;
}

// ============================================
// 真题1：string 操作结果判断
// ============================================
void exam1_string_operations() {
    cout << "====== 真题1：string 操作结果判断 ======" << endl;

    string s = "I love CSP-J";

    cout << "原始字符串 s = \"I love CSP-J\"" << endl;
    cout << "\nQ1: s.length() = " << s.length() << endl;

    cout << "Q2: s.substr(7, 5) = \"" << s.substr(7, 5) << "\"" << endl;

    cout << "Q3: s.find(\"CSP\") = " << s.find("CSP") << endl;

    s += "!";
    cout << "Q4: s += \"!\" 后，s = \"" << s << "\"" << endl;

    cout << "Q5: s.find(\"Python\") == string::npos → "
         << (s.find("Python") == string::npos)
         << " (1=true，表示未找到)" << endl;

    cout << endl;
}

// ============================================
// 真题2：字符统计与大小写翻转
// ============================================
void exam2_case_flip_count() {
    cout << "====== 真题2：字符统计与大小写翻转 ======" << endl;

    string s;
    cout << "请输入一个字符串（可含空格）：";
    cin.ignore();
    getline(cin, s);

    int upper_cnt = 0, lower_cnt = 0, digit_cnt = 0;

    for (char &c : s) {
        if (isupper(c)) {
            upper_cnt++;
            c = tolower(c);
        } else if (islower(c)) {
            lower_cnt++;
            c = toupper(c);
        } else if (isdigit(c)) {
            digit_cnt++;
        }
    }

    cout << "大写字母数: " << upper_cnt
         << ", 小写字母数: " << lower_cnt
         << ", 数字数: " << digit_cnt << endl;
    cout << "翻转后的字符串：\"" << s << "\"" << endl;

    cout << endl;
}

// ============================================
// 演示8：string 综合应用——单词统计
// ============================================
void demo8_word_count() {
    cout << "====== 演示8：综合应用——统计单词数量 ======" << endl;

    string s;
    cout << "请输入英文句子：";
    cin.ignore();
    getline(cin, s);

    int word_cnt = 0;
    bool in_word = false;

    for (char c : s) {
        if (isspace(c)) {
            in_word = false;
        } else if (!in_word) {
            in_word = true;
            word_cnt++;
        }
    }

    cout << "单词数量：" << word_cnt << endl;

    cout << endl;
}

// ============================================
// 主菜单
// ============================================
void showMenu() {
    cout << "╔══════════════════════════════════╗" << endl;
    cout << "║   第16课：string 类与字符处理  ║" << endl;
    cout << "║   CSP-J 备考课程               ║" << endl;
    cout << "╠══════════════════════════════════╣" << endl;
    cout << "║  1. string 定义与初始化         ║" << endl;
    cout << "║  2. string 输入方式对比         ║" << endl;
    cout << "║  3. 拼接/比较/长度演示          ║" << endl;
    cout << "║  4. substr 与 find 演示         ║" << endl;
    cout << "║  5. 字符判断函数演示            ║" << endl;
    cout << "║  6. 字符统计综合练习            ║" << endl;
    cout << "║  7. 大小写翻转练习              ║" << endl;
    cout << "║  8. 单词统计                    ║" << endl;
    cout << "║  9. 真题1 - string操作结果判断  ║" << endl;
    cout << "║ 10. 真题2 - 字符统计与翻转      ║" << endl;
    cout << "║  0. 退出                        ║" << endl;
    cout << "╚══════════════════════════════════╝" << endl;
    cout << "请选择（0-10）：";
}

int main() {
    int choice;
    while (true) {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:  demo1_definition();         break;
            case 2:  demo2_input();              break;
            case 3:  demo3_basic_operations();   break;
            case 4:  demo4_substr_find();        break;
            case 5:  demo5_char_functions();     break;
            case 6:  demo6_char_statistics();    break;
            case 7:  demo7_case_flip();          break;
            case 8:  demo8_word_count();         break;
            case 9:  exam1_string_operations();  break;
            case 10: exam2_case_flip_count();    break;
            case 0:
                cout << "再见！" << endl;
                return 0;
            default:
                cout << "无效选项，请重新选择！" << endl;
                cin.ignore();
                break;
        }
    }
    return 0;
}
