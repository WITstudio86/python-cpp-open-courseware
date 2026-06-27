/*
 * CSP-J 备考课程
 * 第1课：计算机基础与进制转换
 * 考纲知识点：计算机发展史、硬件组成、进制转换、ASCII编码
 *
 * 本文件包含：
 * 1. 进制输出演示
 * 2. ASCII码操作演示
 * 3. 真题/模拟题 AC 代码
 */

#include <iostream>
#include <bitset>
#include <iomanip>
using namespace std;

int main() {
    cout << "========== CSP-J 第1课：计算机基础与进制转换 ==========" << endl;
    cout << endl;

    // ===== 一、进制输出演示 =====
    cout << "【一、进制输出演示】" << endl;
    int n = 2024;

    cout << "十进制: " << dec << n << endl;
    cout << "八进制: " << oct << n << endl;
    cout << "十六进制(小写): " << hex << n << endl;
    cout << "十六进制(大写): " << hex << uppercase << n << endl;
    cout << "二进制(16位): " << bitset<16>(n) << endl;
    cout << dec;  // 恢复十进制输出
    cout << endl;

    // ===== 二、进制转换练习 =====
    cout << "【二、进制转换练习】" << endl;

    // 示例：二进制 10110110 的转换
    int val = 1*128 + 0*64 + 1*32 + 1*16 + 0*8 + 1*4 + 1*2 + 0*1;
    cout << "二进制 10110110 的十进制值: " << val << endl;
    cout << "二进制 10110110 的八进制值: " << oct << val << endl;
    cout << "二进制 10110110 的十六进制值: " << hex << uppercase << val << endl;
    cout << dec;
    cout << endl;

    // 示例：十进制 2024 转二进制和十六进制
    int year = 2024;
    cout << "十进制 " << year << " 的二进制: " << bitset<16>(year) << endl;
    cout << "十进制 " << year << " 的十六进制: " << hex << uppercase << year << endl;
    cout << dec;
    cout << endl;

    // ===== 三、ASCII码操作演示 =====
    cout << "【三、ASCII码操作演示】" << endl;

    // 字符与ASCII码互转
    char ch = 'A';
    cout << "字符 '" << ch << "' 的ASCII码: " << (int)ch << endl;

    // 大小写转换
    cout << "'A' + 32 = '" << (char)(ch + 32) << "' (小写)" << endl;
    cout << "'a' - 32 = '" << (char)('a' - 32) << "' (大写)" << endl;

    // 数字字符转数值
    char digit = '7';
    int num = digit - '0';
    cout << "字符 '" << digit << "' 转数值: " << num << endl;

    // 字符运算
    cout << "'E' - 'A' + 'd' = '" << (char)('E' - 'A' + 'd') << "'" << endl;

    // 输出常见字符的ASCII码
    cout << endl << "常见字符ASCII码对照表:" << endl;
    cout << "'0' = " << (int)'0' << endl;
    cout << "'A' = " << (int)'A' << endl;
    cout << "'a' = " << (int)'a' << endl;
    cout << "' ' = " << (int)' ' << endl;
    cout << "'\\n' = " << (int)'\n' << endl;
    cout << endl;

    // ===== 四、存储单位换算 =====
    cout << "【四、数据类型大小】" << endl;
    cout << "sizeof(int)      = " << sizeof(int) << " 字节 = " << sizeof(int) * 8 << " bit" << endl;
    cout << "sizeof(long long)= " << sizeof(long long) << " 字节" << endl;
    cout << "sizeof(char)     = " << sizeof(char) << " 字节" << endl;
    cout << "sizeof(bool)     = " << sizeof(bool) << " 字节" << endl;
    cout << "sizeof(double)   = " << sizeof(double) << " 字节" << endl;
    cout << endl;

    // ===== 五、进制输入练习 =====
    cout << "【五、进制输入练习】" << endl;
    cout << "请输入一个十进制整数: ";
    int input;
    cin >> input;

    cout << "→ 二进制: " << bitset<16>(input) << endl;
    cout << "→ 八进制: " << oct << input << endl;
    cout << "→ 十六进制: " << hex << uppercase << input << endl;
    cout << dec;

    cout << endl;
    cout << "========== 第1课演示结束 ==========" << endl;
    return 0;
}
