/**
 * ============================================================
 * 第32课：高精度除法 — 完整 C++ 实现
 * ============================================================
 *
 * 本文件包含以下功能：
 *   1. high_precision_div_single() —— 高精度 ÷ 单精度
 *      原理：模拟竖式除法，从左到右逐位求商，余数传递
 *      输入：大数字符串 + int 除数
 *      输出：商（字符串）和余数（int）
 *
 *   2. high_precision_div_high() —— 高精度 ÷ 高精度
 *      原理：用减法模拟除法，通过补零优化加速
 *      输入：两个大数字符串
 *      输出：商和余数（均为字符串）
 *
 *   3. 辅助函数：
 *      - compare(): 比较两个大数的大小
 *      - high_precision_subtract(): 高精度减法（保证 a >= b）
 *      - high_precision_add(): 高精度加法（用于累加商）
 *
 *   4. main() —— 提供两个例题的测试
 *      例题1：高精度除以单精度
 *      例题2：高精度除以高精度
 *
 * 编译方式：
 *   g++ -std=c++11 -o lesson32 lesson32_high_precision_div.cpp
 * 运行方式：
 *   ./lesson32
 *
 * 作者：C++算法提高课程
 * 日期：2026年
 * ============================================================
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * 比较两个大整数（字符串形式）的大小
 *
 * 比较规则：
 *   1. 先比较长度：位数多的更大
 *   2. 位数相同，从高位到低位逐位比较
 *
 * @param a  第一个大整数（字符串形式）
 * @param b  第二个大整数（字符串形式）
 * @return   a > b 返回 1，a == b 返回 0，a < b 返回 -1
 */
int compare(const string &a, const string &b) {
    // 先比较长度
    if (a.size() != b.size()) {
        return a.size() > b.size() ? 1 : -1;
    }
    // 长度相同，逐位比较（从左到右，即从高位到低位）
    for (int i = 0; i < (int)a.size(); i++) {
        if (a[i] != b[i]) {
            return a[i] > b[i] ? 1 : -1;
        }
    }
    return 0;  // 完全相等
}

/**
 * 高精度减法：计算 a - b
 *
 * 前提条件：a >= b（调用者需要保证）
 * 算法步骤：
 *   1. 倒序存储两个数（个位在索引 0）
 *   2. 从低位到高位逐位相减，不够减时向高位借位
 *   3. 去除结果的前导零
 *
 * @param a  被减数（字符串形式，保证 a >= b）
 * @param b  减数（字符串形式）
 * @return   a - b 的字符串表示
 */
string high_precision_subtract(string a, const string &b) {
    // 倒序存储：索引 0 存个位
    // va 长度为 a.size()，vb 长度也是 a.size()（高位补 0）
    vector<int> va(a.size()), vb(a.size(), 0);

    for (int i = 0; i < (int)a.size(); i++) {
        va[i] = a[a.size() - 1 - i] - '0';
    }
    for (int i = 0; i < (int)b.size(); i++) {
        vb[i] = b[b.size() - 1 - i] - '0';
    }

    // 逐位相减，处理借位
    for (int i = 0; i < (int)a.size(); i++) {
        if (va[i] < vb[i]) {
            // 不够减，向高一位借 1（相当于借 10）
            va[i] += 10;
            va[i + 1]--;
        }
        va[i] -= vb[i];
    }

    // 去除前导零（从最高位开始找第一个非零位置）
    int pos = a.size() - 1;
    while (pos > 0 && va[pos] == 0) {
        pos--;
    }

    // 拼接结果字符串（从高位到低位）
    string result;
    for (int i = pos; i >= 0; i--) {
        result += char(va[i] + '0');
    }
    return result;
}

/**
 * 高精度加法：计算 a + b
 *
 * 用于高精度除以高精度时累加商值
 *
 * @param a  第一个大整数（字符串形式）
 * @param b  第二个大整数（字符串形式）
 * @return   a + b 的字符串表示
 */
string high_precision_add(const string &a, const string &b) {
    int len1 = a.size();
    int len2 = b.size();
    int maxLen = max(len1, len2);

    // 倒序存储
    vector<int> va(maxLen, 0), vb(maxLen, 0);
    for (int i = 0; i < len1; i++) va[i] = a[len1 - 1 - i] - '0';
    for (int i = 0; i < len2; i++) vb[i] = b[len2 - 1 - i] - '0';

    vector<int> vc(maxLen + 1, 0);

    // 逐位相加并处理进位
    for (int i = 0; i < maxLen; i++) {
        vc[i] += va[i] + vb[i];
        if (vc[i] >= 10) {
            vc[i + 1] += vc[i] / 10;
            vc[i] %= 10;
        }
    }

    // 去除前导零
    int pos = maxLen;
    while (pos > 0 && vc[pos] == 0) pos--;

    // 拼接结果
    string result;
    for (int i = pos; i >= 0; i--) {
        result += char(vc[i] + '0');
    }
    return result;
}

/**
 * 高精度除以单精度（除数在 int 范围内）
 *
 * 算法原理：模拟竖式除法
 *   从左到右逐位处理被除数：
 *     当前被除数 = 上一位的余数 × 10 + 当前位数字
 *     商位 = 当前被除数 / divisor
 *     新的余数 = 当前被除数 % divisor
 *
 * 示例（1234 ÷ 5）：
 *   i=0: cur = 0×10+1 = 1,  1/5=0,  1%5=1 → 商"0", 余1
 *   i=1: cur = 1×10+2 = 12, 12/5=2, 12%5=2 → 商"02", 余2
 *   i=2: cur = 2×10+3 = 23, 23/5=4, 23%5=3 → 商"024", 余3
 *   i=3: cur = 3×10+4 = 34, 34/5=6, 34%5=4 → 商"0246", 余4
 *   去除前导零：商 = "246"，余数 = 4
 *
 * @param num        被除数（大数字符串）
 * @param divisor    除数（int 范围内的正整数）
 * @param remainder  输出参数：余数
 * @return           商的字符串表示
 */
string high_precision_div_single(const string &num, int divisor, int &remainder) {
    // 除数为 0 是错误的
    if (divisor == 0) {
        cerr << "错误：除数不能为 0！" << endl;
        remainder = 0;
        return "";
    }

    // 被除数为 0，商也为 0
    if (num == "0") {
        remainder = 0;
        return "0";
    }

    string quotient;         // 商（可能包含前导零）
    long long cur = 0;       // 当前被除数（使用 long long 防止溢出）

    // 从左到右逐位处理（模拟竖式除法的"逐位取商"）
    for (int i = 0; i < (int)num.size(); i++) {
        // 当前被除数 = 上一步的余数 × 10 + 当前位的数字
        cur = cur * 10 + (num[i] - '0');

        // 当前商位 = 当前被除数 ÷ 除数
        quotient += char(cur / divisor + '0');

        // 更新余数 = 当前被除数 % 除数
        cur %= divisor;
    }

    remainder = (int)cur;  // 最终余数

    // ============================================================
    // 去除商的前导零
    // 例如：quotient = "0246" → "246"
    // 注意：至少保留一位（如商为 "0" 时不全部去掉）
    // ============================================================
    int start = 0;
    while (start < (int)quotient.size() - 1 && quotient[start] == '0') {
        start++;
    }

    return quotient.substr(start);
}

/**
 * 高精度除以高精度（被除数和除数都是大数）
 *
 * 算法原理：用减法模拟除法
 *   核心思想：除法就是"被除数可以减去多少个除数"
 *
 * 优化策略（补零加速）：
 *   1. 在除数后面补零，使除数尽可能接近被除数（但不超过）
 *   2. 反复减去这个扩大后的除数，每次减商增加对应的权重
 *   3. 缩小除数（减少补零数量），继续减法
 *   4. 重复直到除数恢复原始大小
 *
 * 示例（4567 ÷ 23）：
 *   23 → 2300（补2个零），4567 - 2300 = 2267，商+100
 *   2267 < 2300 → 缩小：23 → 230（补1个零）
 *   2267 - 230×9 = 2267 - 2070 = 197，商+90
 *   ...继续直到 23 本身
 *   最终：商 = 198，余数 = 20
 *
 * @param a          被除数（大数字符串）
 * @param b          除数（大数字符串，b > 0）
 * @param quotient   输出参数：商
 * @param remainder  输出参数：余数
 */
void high_precision_div_high(const string &a, const string &b,
                              string &quotient, string &remainder) {
    // 除数为 0 是错误的
    if (b == "0") {
        cerr << "错误：除数不能为 0！" << endl;
        quotient = "";
        remainder = "";
        return;
    }

    // 如果被除数 < 除数，商为 0，余数为被除数本身
    if (compare(a, b) < 0) {
        quotient = "0";
        remainder = a;
        return;
    }

    remainder = a;    // 初始余数 = 被除数
    quotient = "0";   // 初始商 = 0

    // ============================================================
    // 外层循环：只要余数 >= 除数，就继续减
    // ============================================================
    while (compare(remainder, b) >= 0) {
        string temp = b;      // 扩大后的除数
        string weight = "1";  // 当前权重（对应商中增加的量）

        // ============================================================
        // 补零优化：在除数后面补零，使 temp 尽量大但不超过 remainder
        // 例如：remainder=4567, b=23
        //       temp: 23 → 230 → 2300 → 23000(太大了，停止)
        //       weight: 1 → 10 → 100
        // ============================================================
        while (compare(remainder, temp + "0") >= 0) {
            temp += "0";       // 除数扩大 10 倍
            weight += "0";     // 权重也扩大 10 倍
        }

        // ============================================================
        // 内层循环：反复减去扩大后的除数
        // ============================================================
        while (compare(remainder, temp) >= 0) {
            remainder = high_precision_subtract(remainder, temp);
            quotient = high_precision_add(quotient, weight);
        }
    }
}

/**
 * 主函数：测试两个例题
 *
 * 例题1：高精度除以单精度
 *   输入：一个大整数 A 和一个 int 范围内的整数 B
 *   输出：A ÷ B 的商和余数
 *
 * 例题2：高精度除以高精度
 *   输入：两个大整数 A 和 B
 *   输出：A ÷ B 的商和余数
 */
int main() {
    cout << "========================================" << endl;
    cout << "  第32课：高精度除法 — 例题测试" << endl;
    cout << "========================================" << endl;
    cout << endl;

    // ============================================================
    // 例题1：高精度除以单精度
    // ============================================================
    cout << "【例题1】高精度除以单精度" << endl;
    cout << "请输入被除数 A（大整数）：";
    string a;
    cin >> a;
    cout << "请输入除数 B（int 范围内的正整数）：";
    int b;
    cin >> b;

    if (b <= 0) {
        cout << "输入错误：除数必须是正整数！" << endl;
    } else {
        int remainder;
        string quotient = high_precision_div_single(a, b, remainder);

        cout << endl << "--- 计算结果 ---" << endl;
        cout << "商：  " << quotient << endl;
        cout << "余数：" << remainder << endl;

        // 验证结果
        cout << "验证：商 × " << b << " + 余数 = " << quotient
             << " × " << b << " + " << remainder << endl;
    }

    cout << endl;

    // ============================================================
    // 例题2：高精度除以高精度
    // ============================================================
    cout << "【例题2】高精度除以高精度（减法模拟）" << endl;
    cout << "请输入被除数 A：";
    string a2;
    cin >> a2;
    cout << "请输入除数 B：";
    string b2;
    cin >> b2;

    if (b2 == "0") {
        cout << "输入错误：除数不能为 0！" << endl;
    } else {
        string quotient, remainder;
        high_precision_div_high(a2, b2, quotient, remainder);

        cout << endl << "--- 计算结果 ---" << endl;
        cout << "商：  " << quotient << endl;
        cout << "余数：" << remainder << endl;
    }

    cout << endl;
    cout << "测试完成！" << endl;

    return 0;
}
