/*
 * CSP-J 备考课程
 * 第1课：计算机基础与进制转换
 * 考纲知识点：计算机发展史、冯·诺依曼结构、硬件组成、
 *           二进制/八进制/十六进制互转、ASCII 编码
 *
 * 本文件演示清单：
 * 1. demoStorageUnits      —— 存储单位与 sizeof
 * 2. demoBaseLiterals      —— 整型字面量（十/八/十六进制）
 * 3. demoBaseOutput        —— dec/oct/hex/bitset 输出
 * 4. demoBinToDec          —— 二进制按权展开 / 字符串转十进制
 * 5. demoDecToBinSteps     —— 除 2 取余过程模拟
 * 6. demoOctHexGroup       —— 二⇔八（3 位）与 二⇔十六（4 位）
 * 7. demoAsciiBasics       —— ASCII 锚点与大小写/数字转换
 * 8. demoAsciiExpression   —— 字符表达式求值
 * 9. demoQuickTable        —— 0~15 对照表
 * 10. demoExamProblems     —— 讲义真题验证
 */

#include <iostream>
#include <bitset>
#include <iomanip>
#include <string>
using namespace std;

// ==================== 工具函数 ====================

void printTitle(const string &title) {
    cout << "\n========================================" << endl;
    cout << "  " << title << endl;
    cout << "========================================" << endl;
}

void printSub(const string &s) {
    cout << "\n--- " << s << " ---" << endl;
}

// 将非负整数转为二进制字符串（不含前导 0，0 则返回 "0"）
string toBinString(unsigned long long n) {
    if (n == 0) return "0";
    string s;
    while (n > 0) {
        s = char('0' + (n % 2)) + s;
        n /= 2;
    }
    return s;
}

// 二进制字符串 → 十进制
long long binStringToDec(const string &bin) {
    long long ans = 0;
    for (size_t i = 0; i < bin.size(); i++) {
        char c = bin[i];
        if (c != '0' && c != '1') continue;
        ans = ans * 2 + (c - '0');
    }
    return ans;
}

// ==================== 1. 存储单位与 sizeof ====================

void demoStorageUnits() {
    printTitle("1. 存储单位与数据类型大小");

    cout << "换算关系（CSP-J 常用 1024）：" << endl;
    cout << "  1 Byte = 8 bit" << endl;
    cout << "  1 KB   = 1024 B" << endl;
    cout << "  1 MB   = 1024 KB" << endl;
    cout << "  1 GB   = 1024 MB" << endl;

    cout << "\nsizeof 结果（单位：字节）：" << endl;
    cout << "  sizeof(char)      = " << sizeof(char)
         << "  → " << sizeof(char) * 8 << " bit" << endl;
    cout << "  sizeof(bool)      = " << sizeof(bool) << endl;
    cout << "  sizeof(int)       = " << sizeof(int)
         << "  → " << sizeof(int) * 8 << " bit" << endl;
    cout << "  sizeof(long long) = " << sizeof(long long)
         << "  → " << sizeof(long long) * 8 << " bit" << endl;
    cout << "  sizeof(float)     = " << sizeof(float) << endl;
    cout << "  sizeof(double)    = " << sizeof(double) << endl;

    // 简单内存估算示例：1024x768 真彩色
    long long pixels = 1024LL * 768;
    long long bytes = pixels * 3; // 每像素 3 字节
    cout << "\n示例：1024×768 真彩色(3B/像素) 约 "
         << bytes << " 字节 ≈ "
         << fixed << setprecision(2)
         << (bytes / 1024.0 / 1024.0) << " MB" << endl;
    cout << defaultfloat;
}

// ==================== 2. 字面量 ====================

void demoBaseLiterals() {
    printTitle("2. C++ 整型字面量（前缀）");

    int dec = 26;
    int oct = 032;    // 3*8 + 2 = 26
    int hex = 0x1A;   // 1*16 + 10 = 26
    int hex2 = 0X1a;  // 大小写均可

    cout << "int dec = 26;    → " << dec << endl;
    cout << "int oct = 032;   → " << oct << "  (八进制 32)" << endl;
    cout << "int hex = 0x1A;  → " << hex << "  (十六进制 1A)" << endl;
    cout << "int hex2= 0X1a;  → " << hex2 << endl;

    cout << "\n易错对比：" << endl;
    cout << "  012 的十进制值 = " << 012 << " （不是 12！）" << endl;
    cout << "  0x12 的十进制值 = " << 0x12 << " （不是 12！）" << endl;
    cout << "  12 的十进制值 = " << 12 << endl;

    cout << "\n常见十六进制：" << endl;
    cout << "  0xFF = " << 0xFF << ", 0x10 = " << 0x10
         << ", 0x2F = " << 0x2F << endl;
}

// ==================== 3. 进制输出 ====================

void demoBaseOutput() {
    printTitle("3. dec / oct / hex / bitset 输出");

    int n = 2024;
    cout << "n = " << n << endl;
    cout << "  十进制:     " << dec << n << endl;
    cout << "  八进制:     " << oct << n << endl;
    cout << "  十六进制:   " << hex << n << endl;
    cout << "  十六进制大写: " << hex << uppercase << n << endl;
    cout << nouppercase << dec;

    cout << "  二进制(16位): " << bitset<16>(n) << endl;
    cout << "  二进制(32位): " << bitset<32>(n) << endl;
    cout << "  手写二进制串: " << toBinString((unsigned long long)n) << endl;

    // 演示 hex 会“粘住”
    printSub("注意：hex 会改变后续整数输出格式");
    cout << "  输出 hex 后直接输出 10 → " << hex << 10 << endl;
    cout << "  恢复 dec 后输出 10 → " << dec << 10 << endl;
}

// ==================== 4. 二进制 → 十进制 ====================

void demoBinToDec() {
    printTitle("4. 二进制 → 十进制（按权展开）");

    // 例：1011. 这里只演示整数部分 1011
    string samples[] = {"1011", "11001", "10110110", "11111101000"};
    int expected[] = {11, 25, 182, 2024};

    for (int i = 0; i < 4; i++) {
        long long v = binStringToDec(samples[i]);
        cout << "  (" << samples[i] << ")2 = " << v
             << "  [期望 " << expected[i] << "]"
             << (v == expected[i] ? " OK" : " FAIL") << endl;
    }

    printSub("逐步按权展开 10110110");
    // 从左到右：权 128..1
    int weights[] = {128, 64, 32, 16, 8, 4, 2, 1};
    string b = "10110110";
    int sum = 0;
    for (int i = 0; i < 8; i++) {
        int bit = b[i] - '0';
        int term = bit * weights[i];
        sum += term;
        cout << "  bit[" << i << "]=" << bit
             << " × " << weights[i] << " = " << term << endl;
    }
    cout << "  合计 = " << sum << endl;
}

// ==================== 5. 十进制 → 二进制步骤 ====================

void demoDecToBinSteps() {
    printTitle("5. 十进制整数 → 二进制（除 2 取余倒序）");

    int n = 25;
    cout << "将 " << n << " 转为二进制：" << endl;

    int remainders[64];
    int cnt = 0;
    int x = n;
    if (x == 0) {
        cout << "  0 的二进制是 0" << endl;
        return;
    }
    while (x > 0) {
        int r = x % 2;
        remainders[cnt++] = r;
        cout << "  " << x << " ÷ 2 = " << (x / 2)
             << " 余 " << r << endl;
        x /= 2;
    }
    cout << "  余数从下往上写（倒序）：";
    for (int i = cnt - 1; i >= 0; i--) cout << remainders[i];
    cout << endl;
    cout << "  bitset 验证: " << bitset<8>(n) << endl;
    cout << "  字符串验证: " << toBinString((unsigned long long)n) << endl;

    printSub("再演示 2024");
    cout << "  2024 二进制 = " << toBinString(2024) << endl;
    cout << "  bitset<16>  = " << bitset<16>(2024) << endl;
}

// ==================== 6. 分组转换 ====================

void demoOctHexGroup() {
    printTitle("6. 二进制 ⇔ 八进制 / 十六进制（分组）");

    string bin = "10101110";
    long long val = binStringToDec(bin);
    cout << "原二进制: " << bin << " → 十进制 " << val << endl;

    // 补齐到 3 的倍数再按 3 位转八进制（演示）
    string b3 = bin;
    while (b3.size() % 3 != 0) b3 = "0" + b3;
    cout << "  补齐后(3位一组): " << b3 << " → ";
    for (size_t i = 0; i < b3.size(); i += 3) {
        int d = (b3[i] - '0') * 4 + (b3[i + 1] - '0') * 2 + (b3[i + 2] - '0');
        cout << d;
    }
    cout << " (八进制)" << endl;
    cout << "  oct 操纵符验证: " << oct << val << dec << endl;

    // 4 位一组转十六进制
    string b4 = bin;
    while (b4.size() % 4 != 0) b4 = "0" + b4;
    cout << "  补齐后(4位一组): " << b4 << " → ";
    const char *hexDigits = "0123456789ABCDEF";
    for (size_t i = 0; i < b4.size(); i += 4) {
        int d = (b4[i] - '0') * 8 + (b4[i + 1] - '0') * 4
              + (b4[i + 2] - '0') * 2 + (b4[i + 3] - '0');
        cout << hexDigits[d];
    }
    cout << " (十六进制)" << endl;
    cout << "  hex 操纵符验证: " << hex << uppercase << val << dec << nouppercase << endl;

    printSub("十六进制 0x2F → 二进制");
    int x = 0x2F;
    cout << "  0x2F = " << x << " → " << bitset<8>(x) << endl;

    printSub("2024 的十六进制");
    cout << "  " << hex << uppercase << 2024 << dec << nouppercase
         << " （期望 7E8）" << endl;
}

// ==================== 7. ASCII 基础 ====================

void demoAsciiBasics() {
    printTitle("7. ASCII 锚点与常用变换");

    cout << "三大锚点：" << endl;
    cout << "  '0' = " << (int)'0' << endl;
    cout << "  'A' = " << (int)'A' << endl;
    cout << "  'a' = " << (int)'a' << endl;
    cout << "  空格 = " << (int)' ' << endl;
    cout << "  '\\n' = " << (int)'\n' << endl;

    cout << "\n大小写相差 32：" << endl;
    cout << "  'a' - 'A' = " << ('a' - 'A') << endl;
    cout << "  'A' + 32 = '" << (char)('A' + 32) << "'" << endl;
    cout << "  'z' - 32 = '" << (char)('z' - 32) << "'" << endl;

    cout << "\n数字字符 ↔ 数值：" << endl;
    char digit = '7';
    int num = digit - '0';
    cout << "  '" << digit << "' - '0' = " << num << endl;
    cout << "  3 + '0' = '" << (char)(3 + '0') << "'" << endl;

    cout << "\n字母序号：" << endl;
    cout << "  'D' - 'A' = " << ('D' - 'A') << " (从 0 起)" << endl;
    cout << "  'D' - 'A' + 1 = " << ('D' - 'A' + 1) << " (从 1 起)" << endl;

    printSub("输出 A~Z 与部分码值");
    for (char c = 'A'; c <= 'Z'; c++) {
        if (c == 'A' || c == 'M' || c == 'Z') {
            cout << "  '" << c << "'=" << (int)c;
        }
    }
    cout << endl;
}

// ==================== 8. ASCII 表达式 ====================

void demoAsciiExpression() {
    printTitle("8. ASCII 表达式求值演示");

    char r1 = 'E' - 'A' + 'd';
    cout << "  'E' - 'A' + 'd' = '" << r1
         << "' (码值 " << (int)r1 << ")" << endl;

    char r2 = 'B' - 'A' + 'a';
    cout << "  'B' - 'A' + 'a' = '" << r2 << "'" << endl;

    int r3 = '9' - '0' + '1' - '0';
    cout << "  ('9'-'0') + ('1'-'0') = " << r3 << endl;

    // 连续字符
    cout << "  'A'+3 作为字符: '" << (char)('A' + 3) << "'" << endl;
    cout << "  'A'+3 作为整数: " << ('A' + 3) << endl;
}

// ==================== 9. 0~15 对照表 ====================

void demoQuickTable() {
    printTitle("9. 0~15 二进制/八/十/十六进制对照");

    cout << "  dec  bin   oct  hex" << endl;
    cout << "  -------------------" << endl;
    for (int i = 0; i <= 15; i++) {
        cout << "  " << setw(2) << dec << i << "  "
             << bitset<4>(i) << "   "
             << oct << i << "    "
             << hex << uppercase << i
             << nouppercase << dec << endl;
    }
}

// ==================== 10. 真题验证 ====================

void demoExamProblems() {
    printTitle("10. 讲义真题 / 模拟题验证");

    printSub("题目1：二进制 10110110");
    string bin = "10110110";
    int decVal = (int)binStringToDec(bin);
    cout << "  十进制 = " << decVal << " (期望 182)" << endl;
    cout << "  八进制 = " << oct << decVal << " (期望 266)" << endl;
    cout << "  十六进制 = " << hex << uppercase << decVal
         << " (期望 B6)" << dec << nouppercase << endl;
    cout << "  bitset<8> = " << bitset<8>(decVal) << endl;

    printSub("题目2：'E' - 'A' + 'd'");
    char ans = 'E' - 'A' + 'd';
    cout << "  结果字符 = '" << ans << "' (期望 'h')" << endl;
    cout << "  码值 = " << (int)ans << " (期望 104)" << endl;

    printSub("题目4：0x2F 的二进制");
    cout << "  " << bitset<8>(0x2F) << " (期望 00101111)" << endl;

    printSub("综合：2024 的多进制");
    int year = 2024;
    cout << "  dec=" << year
         << " oct=" << oct << year
         << " hex=" << hex << uppercase << year
         << " bin=" << bitset<16>(year)
         << dec << nouppercase << endl;
}

// ==================== 附加：小数乘 2 取整示意 ====================

void demoFracToBin() {
    printTitle("附加：十进制小数 → 二进制（乘 2 取整）");
    // 0.625 → 0.101
    double frac = 0.625;
    cout << "  小数 " << frac << " → 二进制 0.";
    for (int step = 0; step < 8; step++) {
        frac *= 2;
        int bit = (int)frac;
        cout << bit;
        frac -= bit;
        if (frac < 1e-12) break;
    }
    cout << "  (期望 0.101)" << endl;
}

// ==================== main ====================

int main() {
    cout << "############################################" << endl;
    cout << "#  CSP-J 第1课：计算机基础与进制转换 演示  #" << endl;
    cout << "############################################" << endl;

    demoStorageUnits();
    demoBaseLiterals();
    demoBaseOutput();
    demoBinToDec();
    demoDecToBinSteps();
    demoOctHexGroup();
    demoAsciiBasics();
    demoAsciiExpression();
    demoQuickTable();
    demoExamProblems();
    demoFracToBin();

    cout << "\n############################################" << endl;
    cout << "#              第1课演示结束               #" << endl;
    cout << "############################################" << endl;
    return 0;
}
