/*
 * CSP-J 备考课程
 * 第6课：运算符与表达式（下）
 * 考纲知识点：关系运算符、逻辑运算符及短路特性、位运算符、三目运算符
 *
 * 本文件包含：
 * 1. 关系运算符演示
 * 2. 逻辑运算符与短路特性
 * 3. 位运算符详解
 * 4. 三目运算符
 */

#include <iostream>
#include <bitset>
using namespace std;

int main() {
    cout << "========== CSP-J 第6课：运算符与表达式（下） ==========" << endl;
    cout << endl;

    // ===== 一、关系运算符 =====
    cout << "【一、关系运算符】" << endl;

    int a = 10, b = 20, c = 10;
    cout << "a = " << a << ", b = " << b << ", c = " << c << endl;
    cout << "a < b:  " << (a < b) << " (true=1)" << endl;
    cout << "a > b:  " << (a > b) << " (false=0)" << endl;
    cout << "a <= c: " << (a <= c) << " (true=1)" << endl;
    cout << "a >= b: " << (a >= b) << " (false=0)" << endl;
    cout << "a == c: " << (a == c) << " (true=1)" << endl;
    cout << "a != b: " << (a != b) << " (true=1)" << endl;
    cout << endl;

    // 字符比较(比ASCII码)
    cout << "字符比较(ASCII码):" << endl;
    cout << "'A' < 'B': " << ('A' < 'B') << endl;  // true
    cout << "'a' < 'A': " << ('a' < 'A') << endl;  // false (97 < 65)
    cout << endl;

    // ===== 二、逻辑运算符与短路特性 =====
    cout << "【二、逻辑运算符与短路特性】" << endl;

    // 逻辑运算真值表示例
    cout << "真值表演示:" << endl;
    cout << "true && true   = " << (true && true) << endl;
    cout << "true && false  = " << (true && false) << endl;
    cout << "false && true  = " << (false && true) << endl;
    cout << "false && false = " << (false && false) << endl;
    cout << "true || true   = " << (true || true) << endl;
    cout << "true || false  = " << (true || false) << endl;
    cout << "false || false = " << (false || false) << endl;
    cout << "!true          = " << (!true) << endl;
    cout << "!false         = " << (!false) << endl;
    cout << endl;

    // 短路特性演示（重点！）
    cout << "短路特性演示（考试重点）:" << endl;

    int x = 0, y = 0;
    cout << "初始: x=" << x << ", y=" << y << endl;

    // && 短路：左边为false，右边不执行
    cout << "执行: (x != 0) && (y = 100)" << endl;
    bool r1 = (x != 0) && (y = 100);
    cout << "结果: x=" << x << ", y=" << y << " (y未被赋值，因为短路!)" << endl;

    // || 短路：左边为true，右边不执行
    int p = 5;
    cout << "执行: (p > 0) || (p = 999)" << endl;
    bool r2 = (p > 0) || (p = 999);
    cout << "结果: p=" << p << " (p未被改为999，因为短路!)" << endl;
    cout << endl;

    // 短路特性的实际应用
    cout << "短路特性的实际应用:" << endl;
    int num = 0;
    // 安全除法：先判断除数不为0
    if (num != 0 && 100 / num > 10) {
        cout << "这个不会执行" << endl;
    } else {
        cout << "num=0时，100/num不会执行（安全!）" << endl;
    }
    cout << endl;

    // ===== 三、位运算符 =====
    cout << "【三位运算符】" << endl;

    int m = 5, n = 3;  // m=0101, n=0011
    cout << "m = " << m << " (二进制: " << bitset<4>(m) << ")" << endl;
    cout << "n = " << n << " (二进制: " << bitset<4>(n) << ")" << endl;
    cout << endl;

    cout << "按位与  m & n = " << (m & n) << " (" << bitset<4>(m & n) << ")" << endl;
    cout << "按位或  m | n = " << (m | n) << " (" << bitset<4>(m | n) << ")" << endl;
    cout << "按位异或 m ^ n = " << (m ^ n) << " (" << bitset<4>(m ^ n) << ")" << endl;
    cout << "按位取反 ~m = " << (~m) << " (补码表示)" << endl;
    cout << endl;

    // 移位运算
    cout << "移位运算:" << endl;
    cout << "m << 1 = " << (m << 1) << " (" << bitset<4>(m << 1) << ") = m * 2" << endl;
    cout << "m << 2 = " << (m << 2) << " (" << bitset<4>(m << 2) << ") = m * 4" << endl;
    cout << "m >> 1 = " << (m >> 1) << " (" << bitset<4>(m >> 1) << ") = m / 2" << endl;
    cout << endl;

    // 位运算经典应用
    cout << "位运算经典应用:" << endl;

    // 1. 判断奇偶
    cout << "1. 判断奇偶 (n & 1):" << endl;
    for (int i = 1; i <= 8; i++) {
        cout << i << (i & 1 ? "(奇) " : "(偶) ");
    }
    cout << endl;

    // 2. 交换两个数
    int A = 10, B = 20;
    cout << "2. 不用临时变量交换:" << endl;
    cout << "交换前: A=" << A << ", B=" << B << endl;
    A ^= B; B ^= A; A ^= B;
    cout << "交换后: A=" << A << ", B=" << B << endl;

    // 3. 获取第k位
    cout << "3. 获取第k位 (n >> k) & 1:" << endl;
    int val = 13;  // 1101
    cout << val << " 的二进制: " << bitset<4>(val) << endl;
    for (int k = 3; k >= 0; k--) {
        cout << "第" << k << "位: " << ((val >> k) & 1) << endl;
    }

    // 4. 判断2的幂
    cout << "4. 判断2的幂 (n & (n-1) == 0):" << endl;
    for (int i = 1; i <= 16; i++) {
        if ((i & (i - 1)) == 0) {
            cout << i << " 是2的幂" << endl;
        }
    }
    cout << endl;

    // ===== 四、三目运算符 =====
    cout << "【四、三目运算符（?:）】" << endl;

    int score = 85;
    cout << "成绩: " << score << endl;

    // 基本用法
    string result = (score >= 60) ? "及格" : "不及格";
    cout << "基本用法: " << result << endl;

    // 嵌套用法
    char grade = (score >= 90) ? 'A' :
                 (score >= 80) ? 'B' :
                 (score >= 70) ? 'C' :
                 (score >= 60) ? 'D' : 'E';
    cout << "等级(嵌套): " << grade << endl;

    // 求最大值
    int v1 = 15, v2 = 25;
    int maxVal = (v1 > v2) ? v1 : v2;
    cout << "max(" << v1 << ", " << v2 << ") = " << maxVal << endl;

    // 求绝对值
    int neg = -10;
    int absVal = (neg >= 0) ? neg : -neg;
    cout << "|" << neg << "| = " << absVal << endl;
    cout << endl;

    // ===== 五、综合练习 =====
    cout << "【五、综合练习】" << endl;

    // 逻辑短路题目
    int t1 = 0, t2 = 0;
    if (t1++ && t2++) {
        t1++;
    }
    cout << "短路题: t1=0; if(t1++ && t2++) {...}" << endl;
    cout << "t1=" << t1 << ", t2=" << t2 << " (t2++被短路，未执行)" << endl;

    // 位运算+三目题目
    int X = 5, Y = 3;
    int Z = (X & Y) ? (X << 1) : (Y << 1);
    cout << endl;
    cout << "位运算+三目: X=5, Y=3; Z = (X&Y) ? (X<<1) : (Y<<1)" << endl;
    cout << "X & Y = " << (X & Y) << " (非0=真), 所以 Z = X<<1 = " << Z << endl;

    cout << endl << "========== 第6课演示结束 ==========" << endl;
    return 0;
}
