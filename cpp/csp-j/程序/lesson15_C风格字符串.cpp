/*
 * CSP-J 备考课程
 * 第15课：C 风格字符串
 * 考纲知识点：char数组、'\0'结束符、字符串函数、回文判断
 *
 * 本文件包含：
 * 1. C风格字符串定义与初始化
 * 2. 常用字符串函数演示(strlen/strcpy/strcat/strcmp)
 * 3. 回文判断
 * 4. 真题AC代码
 *
 * 编译：g++ -std=c++17 lesson15_C风格字符串.cpp -o lesson15
 * 运行：./lesson15
 */

#include <iostream>
#include <cstring>
using namespace std;

// ============================================
// 演示1：C风格字符串的定义与初始化
// ============================================
void demo1_definition() {
    cout << "====== 演示1：C风格字符串的定义与初始化 ======" << endl;

    // 方式1：用字符串字面量初始化
    char s1[100] = "hello";
    cout << "s1 = \"" << s1 << "\" (长度: " << strlen(s1) << ")" << endl;

    // 方式2：不指定大小
    char s2[] = "world";
    cout << "s2 = \"" << s2 << "\" (sizeof: " << sizeof(s2) << ")" << endl;

    // 方式3：逐个字符初始化（必须手动加'\0'）
    char s3[6] = {'h', 'e', 'l', 'l', 'o', '\0'};
    cout << "s3 = \"" << s3 << "\"" << endl;

    // 错误示例：缺少'\0'
    char s4[5] = {'h', 'e', 'l', 'l', 'o'};
    cout << "s4 (无'\\0') = 乱码或越界（危险！）" << endl;
    // cout << s4 << endl;  // 取消注释会导致未定义行为

    // '\0' 的 ASCII 值
    cout << "'\\0' 的 ASCII 码值 = " << (int)'\0' << endl;

    cout << endl;
}

// ============================================
// 演示2：字符串输入与输出
// ============================================
void demo2_input_output() {
    cout << "====== 演示2：字符串输入与输出 ======" << endl;

    char s[100];

    // cin >> s：遇空格停止
    cout << "请输入一个单词（不要含空格）：";
    cin >> s;
    cout << "cin >> s 读取结果：\"" << s << "\"" << endl;

    // 清除输入缓冲区的换行符
    cin.ignore();

    // cin.getline：读取整行（含空格）
    cout << "请输入一句话（可含空格）：";
    cin.getline(s, 100);
    cout << "cin.getline 读取结果：\"" << s << "\"" << endl;

    // puts 输出（自动换行）
    cout << "使用 puts 输出：";
    puts(s);

    cout << endl;
}

// ============================================
// 演示3：strlen 字符串长度
// ============================================
void demo3_strlen() {
    cout << "====== 演示3：strlen 求字符串长度 ======" << endl;

    char s1[] = "Hello";
    char s2[] = "你好世界";   // 中文字符在UTF-8中占3个字节
    char s3[] = "";          // 空字符串
    char s4[100] = "abc";

    cout << "\"Hello\" 的长度：strlen = " << strlen(s1)
         << ", sizeof = " << sizeof(s1) << endl;
    cout << "\"你好世界\" 的长度：strlen = " << strlen(s2)
         << ", sizeof = " << sizeof(s2) << endl;
    cout << "\"\" 的长度：strlen = " << strlen(s3)
         << ", sizeof = " << sizeof(s3) << endl;
    cout << "\"abc\" 在 char[100] 中：strlen = " << strlen(s4)
         << ", sizeof = " << sizeof(s4) << endl;

    // strlen 与 sizeof 的区别总结
    cout << "注意：strlen 返回实际字符串长度（绕过 '\\0'），"
         << "sizeof 返回数组声明的总大小。" << endl;

    cout << endl;
}

// ============================================
// 演示4：strcpy 字符串拷贝
// ============================================
void demo4_strcpy() {
    cout << "====== 演示4：strcpy 字符串拷贝 ======" << endl;

    char src[] = "Hello, CSP-J!";
    char dest[50] = "";       // 目标数组必须足够大

    // 拷贝前
    cout << "拷贝前：dest = \"" << dest << "\" (空字符串)" << endl;

    // 执行拷贝
    strcpy(dest, src);
    cout << "拷贝后：dest = \"" << dest << "\"" << endl;

    // 再拷贝另一个字符串（覆盖）
    strcpy(dest, "Goodbye");
    cout << "再次拷贝后：dest = \"" << dest << "\"" << endl;

    // 错误示例说明
    cout << "注意：char small[5]; strcpy(small, \"too long\"); 会导致缓冲区溢出！" << endl;

    cout << endl;
}

// ============================================
// 演示5：strcat 字符串拼接
// ============================================
void demo5_strcat() {
    cout << "====== 演示5：strcat 字符串拼接 ======" << endl;

    char result[100] = "Hello";   // 目标数组要有足够的空间！
    cout << "初始字符串：\"" << result << "\"" << endl;

    strcat(result, " ");          // 拼接空格
    cout << "拼接空格后：\"" << result << "\"" << endl;

    strcat(result, "World");      // 拼接单词
    cout << "拼接 'World' 后：\"" << result << "\"" << endl;

    strcat(result, "!");          // 拼接感叹号
    cout << "拼接 '!' 后：\"" << result << "\"" << endl;

    // 多次拼接循环
    char s[50] = "";
    for (int i = 1; i <= 3; i++) {
        strcat(s, "*");
    }
    cout << "循环拼接3个*：\"" << s << "\"" << endl;

    cout << endl;
}

// ============================================
// 演示6：strcmp 字符串比较
// ============================================
void demo6_strcmp() {
    cout << "====== 演示6：strcmp 字符串比较 ======" << endl;

    // 相等
    cout << "strcmp(\"abc\", \"abc\") = " << strcmp("abc", "abc") << " (相等=0)" << endl;
    // s1 < s2（'a' 的 ASCII < 'b' 的 ASCII）
    cout << "strcmp(\"abc\", \"abd\") = " << strcmp("abc", "abd") << " (负数，s1<s2)" << endl;
    // s1 > s2
    cout << "strcmp(\"abd\", \"abc\") = " << strcmp("abd", "abc") << " (正数，s1>s2)" << endl;
    // 短字符串更小
    cout << "strcmp(\"ab\", \"abc\")  = " << strcmp("ab", "abc") << " (负数，短<s长)" << endl;
    // 大写字母 vs 小写字母：'A'(65) < 'a'(97)
    cout << "strcmp(\"Apple\", \"apple\") = " << strcmp("Apple", "apple") << " (大写ASCII更小)" << endl;
    // 空字符串
    cout << "strcmp(\"\", \"a\") = " << strcmp("", "a") << " (负数，空字符串最小)" << endl;

    // 正确用法：if (strcmp(s1, s2) == 0)
    cout << "\n正确判断相等的写法：" << endl;
    const char* a = "hello";
    const char* b = "hello";
    if (strcmp(a, b) == 0) {
        cout << "\"hello\" 和 \"hello\" 相等！" << endl;
    }

    // 易错提醒
    cout << "\n易错提醒：if (strcmp(...)) 在相等时条件为假！" << endl;
    cout << "推荐始终写 if (strcmp(s1, s2) == 0) 来判断相等。" << endl;

    cout << endl;
}

// ============================================
// 演示7：回文判断
// ============================================
bool isPalindrome(const char s[]) {
    int len = strlen(s);
    for (int i = 0, j = len - 1; i < j; i++, j--) {
        if (s[i] != s[j]) {
            return false;
        }
    }
    return true;
}

void demo7_palindrome() {
    cout << "====== 演示7：回文判断（双指针法）======" << endl;

    // 测试多个字符串
    const char* tests[] = {"level", "radar", "hello", "a", "ab", "aba", "12321", "12345"};
    int n = sizeof(tests) / sizeof(tests[0]);

    for (int k = 0; k < n; k++) {
        cout << "\"" << tests[k] << "\" -> ";
        if (isPalindrome(tests[k])) {
            cout << "是回文 ✓" << endl;
        } else {
            cout << "不是回文 ✗" << endl;
        }
    }

    // 算法解析
    cout << "\n算法思路：双指针 i=0, j=len-1，向中间移动比较。" << endl;
    cout << "时间复杂度 O(n)，空间复杂度 O(1)。" << endl;

    cout << endl;
}

// ============================================
// 真题1：统计数字字符个数
// ============================================
void exam1_count_digits() {
    cout << "====== 真题1：统计字符串中数字字符的个数 ======" << endl;

    char s[110];
    cout << "请输入一个字符串（可含空格）：";
    cin.ignore();  // 清除之前可能残留的换行符
    cin.getline(s, 110);

    int cnt = 0;
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            cnt++;
        }
    }

    cout << "数字字符的个数：" << cnt << endl;
    cout << endl;
}

// ============================================
// 真题2：验证回文
// ============================================
void exam2_check_palindrome() {
    cout << "====== 真题2：验证回文 ======" << endl;

    char s[110];
    cout << "请输入一个由小写字母组成的字符串：";
    cin >> s;

    int len = strlen(s);
    bool flag = true;
    for (int i = 0, j = len - 1; i < j; i++, j--) {
        if (s[i] != s[j]) {
            flag = false;
            break;
        }
    }

    if (flag) {
        cout << "yes（是回文）" << endl;
    } else {
        cout << "no（不是回文）" << endl;
    }
    cout << endl;
}

// ============================================
// 综合演示：strlen/strcpy/strcat 配合使用
// ============================================
void demo8_comprehensive() {
    cout << "====== 演示8：综合练习——构建格式化字符串 ======" << endl;

    char result[200] = "姓名: ";
    char name[50];

    cout << "请输入姓名：";
    cin.getline(name, 50);

    strcat(result, name);
    strcat(result, "，成绩: ");

    char scoreStr[20];
    int score = 95;
    // 将整数转为字符串
    int idx = 0, temp = score;
    // 提取各位数字（注意顺序是反的）
    char rev[20];
    int revIdx = 0;
    do {
        rev[revIdx++] = (temp % 10) + '0';
        temp /= 10;
    } while (temp > 0);
    rev[revIdx] = '\0';
    // 反转
    for (int i = revIdx - 1, j = 0; i >= 0; i--, j++) {
        scoreStr[j] = rev[i];
    }
    scoreStr[revIdx] = '\0';

    strcat(result, scoreStr);
    strcat(result, " 分");

    cout << "\n拼接结果：\"" << result << "\"" << endl;
    cout << endl;
}

// ============================================
// 主菜单
// ============================================
void showMenu() {
    cout << "╔══════════════════════════════════╗" << endl;
    cout << "║   第15课：C 风格字符串         ║" << endl;
    cout << "║   CSP-J 备考课程               ║" << endl;
    cout << "╠══════════════════════════════════╣" << endl;
    cout << "║  1. 字符串定义与初始化          ║" << endl;
    cout << "║  2. 字符串输入与输出            ║" << endl;
    cout << "║  3. strlen 演示                 ║" << endl;
    cout << "║  4. strcpy 演示                 ║" << endl;
    cout << "║  5. strcat 演示                 ║" << endl;
    cout << "║  6. strcmp 演示                 ║" << endl;
    cout << "║  7. 回文判断                    ║" << endl;
    cout << "║  8. 综合练习                    ║" << endl;
    cout << "║  9. 真题1 - 统计数字个数        ║" << endl;
    cout << "║ 10. 真题2 - 验证回文            ║" << endl;
    cout << "║  0. 退出                        ║" << endl;
    cout << "╚══════════════════════════════════╝" << endl;
    cout << "请选择（0-10）：";
}

int main() {
    int choice;
    while (true) {
        showMenu();
        cin >> choice;
        cin.ignore();  // 清除换行符

        switch (choice) {
            case 1:  demo1_definition();       break;
            case 2:  demo2_input_output();     break;
            case 3:  demo3_strlen();           break;
            case 4:  demo4_strcpy();           break;
            case 5:  demo5_strcat();           break;
            case 6:  demo6_strcmp();           break;
            case 7:  demo7_palindrome();       break;
            case 8:  demo8_comprehensive();    break;
            case 9:  exam1_count_digits();     break;
            case 10: exam2_check_palindrome(); break;
            case 0:
                cout << "再见！" << endl;
                return 0;
            default:
                cout << "无效选项，请重新选择！" << endl;
                break;
        }
    }
    return 0;
}
