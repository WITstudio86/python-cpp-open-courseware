/*
 * ============================================================
 * 课程：CSP-J 算法入门 — 第28课  模拟算法（下）
 *
 * 本课继续深入模拟算法，涉及更多生活与竞赛中常见的模拟问题，
 * 同时引入一些巧妙优化（如约瑟夫环的数学递推公式）。
 *
 * 本课演示内容：
 *   1. 剪刀石头布游戏模拟 —— N轮对决，统计得分
 *   2. 约瑟夫环问题 —— 队列模拟 + 数学递推公式两种解法
 *   3. 高精度乘法 —— 大整数乘普通整数 + 大整数乘大整数
 *   4. 进制转换 —— 任意进制转十进制 + 十进制转任意进制
 *
 * 学习目标：
 *   - 学会将游戏规则翻译为代码逻辑
 *   - 掌握队列模拟与数学递推两种解题范式
 *   - 深入理解高精度乘法的竖式模拟
 *   - 掌握进制转换的通法（除基取余法 / 按权展开法）
 * ============================================================
 */

#include <iostream>
#include <algorithm>   // reverse, max
#include <vector>
#include <string>
#include <queue>       // 用于约瑟夫环队列模拟
using namespace std;

// ============================================================
// 演示 1：剪刀石头布游戏模拟
//
// 规则：
//   剪刀(0) 赢 布(2)
//   石头(1) 赢 剪刀(0)
//   布(2)   赢 石头(1)
//   相同 → 平局
//
// 给定两个玩家的出拳序列（用数字 0/1/2 表示），进行 N 轮对决，
// 统计每个玩家的得分。
// ============================================================

/**
 * @brief 判断单局剪刀石头布的胜负
 *
 * 规则映射：
 *   0 = 剪刀, 1 = 石头, 2 = 布
 *   利用模运算判断胜负：如果 (a + 1) % 3 == b，则 b 赢 a。
 *   验证：剪刀(0)+1=1(石头) 克剪刀；石头(1)+1=2(布) 克石头；布(2)+1=0(剪刀) 克布。
 *
 * @param a  玩家A的出拳（0=剪刀, 1=石头, 2=布）
 * @param b  玩家B的出拳
 * @return   1 表示A胜, -1 表示B胜, 0 表示平局
 */
int judgeRockPaperScissors(int a, int b) {
    if (a == b) {
        return 0;                        // 平局
    } else if ((a + 1) % 3 == b) {
        return -1;                       // B 胜（B 的拳正好克 A）
    } else {
        return 1;                        // A 胜
    }
}

/**
 * @brief 模拟剪刀石头布游戏
 *
 * 算法：逐轮调用 judgeRockPaperScissors 判断胜负并累加得分。
 *
 * @param movesA  玩家A的出拳序列
 * @param movesB  玩家B的出拳序列
 * @param rounds  总轮数
 */
void simulateRPS(vector<int>& movesA, vector<int>& movesB, int rounds) {
    // 出拳代号对应的中文名称，方便输出
    const char* names[] = {"剪刀", "石头", "布"};

    int scoreA = 0;  // 玩家A得分
    int scoreB = 0;  // 玩家B得分

    cout << "  逐轮详情：" << endl;
    for (int i = 0; i < rounds; i++) {
        int a = movesA[i];  // A 第 i 轮出拳
        int b = movesB[i];  // B 第 i 轮出拳

        int result = judgeRockPaperScissors(a, b);

        // 输出本轮详情
        cout << "    第" << (i + 1) << "轮: A出" << names[a]
             << ", B出" << names[b] << " → ";

        if (result == 1) {
            cout << "A 胜";
            scoreA++;
        } else if (result == -1) {
            cout << "B 胜";
            scoreB++;
        } else {
            cout << "平局";
        }
        cout << "  (比分 A:" << scoreA << " B:" << scoreB << ")" << endl;
    }

    // 最终结果
    cout << "  最终比分: A=" << scoreA << ", B=" << scoreB << " → ";
    if (scoreA > scoreB)
        cout << "A 获胜！" << endl;
    else if (scoreB > scoreA)
        cout << "B 获胜！" << endl;
    else
        cout << "平局！" << endl;
}

/**
 * @brief 演示剪刀石头布游戏
 */
void demoRockPaperScissors() {
    cout << "【演示1】剪刀石头布游戏模拟：" << endl;
    cout << "  规则：剪刀(0) < 石头(1) < 布(2) < 剪刀(0)" << endl;
    cout << endl;

    // 模拟数据：8轮对决
    // A: 剪刀 石头 剪刀 布   石头 石头 布   剪刀
    // B: 石头 剪刀 剪刀 剪刀 布   石头 石头 布
    vector<int> movesA = {0, 1, 0, 2, 1, 1, 2, 0};
    vector<int> movesB = {1, 0, 0, 0, 2, 1, 1, 2};
    int rounds = movesA.size();

    simulateRPS(movesA, movesB, rounds);
    cout << endl;
}

// ============================================================
// 演示 2：约瑟夫环问题（Josephus Problem）
//
// 问题描述：n 个人围成一圈，从第 1 个人开始报数，
// 每次数到 m 的人出列，下一个人继续从 1 报数。
// 求最后剩下的人的编号（或出列顺序）。
//
// 本演示提供两种解法：
//   A. 队列模拟：用 queue 模拟围圈过程，直观易懂。
//   B. 数学递推公式：f(1) = 0, f(i) = (f(i-1) + m) % i
//      最后结果 +1 即得编号（因为公式使用 0-based 索引）。
//      时间复杂度 O(n)，空间复杂度 O(1)。
// ============================================================

/**
 * @brief 约瑟夫环 — 队列模拟法
 *
 * 算法步骤：
 *   1. 将 1~n 依次入队。
 *   2. 重复以下操作直到队列只剩 1 人：
 *      - 将队首的 m-1 个人依次出队再入队（相当于跳过）。
 *      - 第 m 个人出队（被淘汰），不重新入队。
 *   3. 队列中剩下的最后一个人就是答案。
 *
 * 时间复杂度：O(n*m)，最坏情况 O(n^2)。
 * 优点：直观模拟了围圈报数的过程，容易理解。
 *
 * @param n  总人数
 * @param m  报数到 m 出列
 * @return   最后剩下的人的编号（1-based）
 */
int josephusQueue(int n, int m) {
    queue<int> q;              // 用队列模拟环形结构

    // 初始化：所有人按编号 1~n 入队
    for (int i = 1; i <= n; i++) {
        q.push(i);
    }

    // 模拟出列过程
    while (q.size() > 1) {
        // 前 m-1 个人：出队后立刻入队（相当于跳过）
        for (int i = 1; i < m; i++) {
            int front = q.front();  // 队首元素
            q.pop();                // 出队
            q.push(front);          // 排到队尾（模拟环形）
        }
        // 第 m 个人：出队且不再入队（被淘汰）
        // int eliminated = q.front();  // 如需查看淘汰顺序，取消此行注释
        q.pop();
    }

    // 最后剩下的人
    return q.front();
}

/**
 * @brief 约瑟夫环 — 数学递推公式法（最优解）
 *
 * 递推公式推导（使用 0-based 索引）：
 *   设 f(i) 为 i 个人报数到 m 时最后幸存者的 0-based 索引。
 *   当只有 1 个人时：f(1) = 0
 *   当 i > 1 时：f(i) = (f(i-1) + m) % i
 *
 * 为什么是 (f(i-1) + m) % i？
 *   每次淘汰一人后，下一个开始报数的人编号变为新的"起点 0"，
 *   相当于所有人的编号在模 i 意义下向前偏移了 m。
 *   所以幸存者的编号也随之偏移 m，再对 i 取模。
 *
 * 最终答案 = f(n) + 1（从 0-based 转为 1-based）。
 *
 * 时间复杂度：O(n)，空间复杂度：O(1)。
 *
 * @param n  总人数
 * @param m  报数到 m 出列
 * @return   最后剩下的人的编号（1-based）
 */
int josephusFormula(int n, int m) {
    int survivor = 0;  // f(1) = 0（只有1个人时，幸存者索引为0）

    // 从 2 个人开始递推，直到 n 个人
    for (int i = 2; i <= n; i++) {
        survivor = (survivor + m) % i;  // f(i) = (f(i-1) + m) % i
    }

    // 转换为 1-based 编号并返回
    return survivor + 1;
}

/**
 * @brief 演示约瑟夫环问题
 */
void demoJosephus() {
    cout << "【演示2】约瑟夫环问题：" << endl;
    cout << "  问题：n 人围圈，报数到 m 者出列，求最后幸存者" << endl;
    cout << endl;

    int n = 10;  // 10 个人
    int m = 3;   // 每 3 人淘汰 1 人

    // 方法A：队列模拟
    cout << "  [方法A] 队列模拟（n=" << n << ", m=" << m << "）：" << endl;
    cout << "    模拟围圈报数过程..." << endl;
    int resultQueue = josephusQueue(n, m);
    cout << "    最后幸存者编号：" << resultQueue << endl;
    cout << "    （时间复杂度 O(n*m)，队列模拟直观但较慢）" << endl;

    // 方法B：数学递推公式
    cout << "  [方法B] 数学递推公式法（n=" << n << ", m=" << m << "）：" << endl;
    int resultFormula = josephusFormula(n, m);
    cout << "    最后幸存者编号：" << resultFormula << endl;
    cout << "    （递推公式：f(i) = (f(i-1) + " << m << ") % i）" << endl;
    cout << "    （时间复杂度 O(n)，空间复杂度 O(1)）" << endl;

    // 验证两种方法结果一致
    if (resultQueue == resultFormula) {
        cout << "  ✓ 两种方法结果一致！" << endl;
    }

    // 额外示例：经典的约瑟夫故事参数 n=41, m=3
    cout << endl;
    cout << "  经典示例：n=41, m=3（约瑟夫传说）→ 幸存者编号："
         << josephusFormula(41, 3) << endl;
    // 历史记载约瑟夫和朋友站在第16和31位幸存

    cout << endl;
}

// ============================================================
// 演示 3：高精度乘法
//
// 高精度乘法比加法更复杂，需要处理"错位相加"。
// 本演示提供两种变体：
//   A. 高精度 × 普通整数（大整数乘以一个较小整数）
//   B. 高精度 × 高精度（两个大整数相乘）
// ============================================================

/**
 * @brief 高精度乘法 — 大整数 × 普通整数
 *
 * 算法（模拟竖式乘法）：
 *   将大整数 a 的每一位与整数 b 相乘，处理进位。
 *
 *   例如 123 × 45：
 *     1×45=45（进位4，写5）
 *     2×45+4=94（进位9，写4）
 *     3×45+9=144（进位14，写4）
 *     进位14→最终写 41
 *     结果：5535
 *
 * @param a  大整数（字符串形式，如 "123456789"）
 * @param b  普通整数（较小，在 int 范围内）
 * @return   乘积的字符串表示
 */
string highPrecisionMultiplyInt(string a, int b) {
    if (b == 0) return "0";  // 乘以 0 结果为 0

    // 反转 a，让低位（个位）在索引 0 处
    reverse(a.begin(), a.end());

    string result = "";            // 存储结果（低位在前）
    int carry = 0;                 // 进位
    int lenA = a.length();

    for (int i = 0; i < lenA; i++) {
        int digit = a[i] - '0';           // 当前位的数值
        int product = digit * b + carry;  // 当前位 × 乘数 + 进位
        int curDigit = product % 10;      // 当前位结果
        carry = product / 10;             // 新的进位
        result += (char)(curDigit + '0'); // 追加到结果
    }

    // 处理最后的进位
    while (carry > 0) {
        result += (char)((carry % 10) + '0');
        carry /= 10;
    }

    // 反转回来
    reverse(result.begin(), result.end());
    return result;
}

/**
 * @brief 高精度乘法 — 大整数 × 大整数
 *
 * 算法（模拟竖式乘法，双重循环）：
 *   对于 a 的第 i 位（从低位开始）和 b 的第 j 位：
 *     product = a[i] * b[j]
 *     这个 product 应该加到结果的第 (i+j) 位上。
 *
 *   例如 123 × 456：
 *     3×6=18   → 结果的第0位 += 18
 *     2×6=12   → 结果的第1位 += 12  (实际上是 20×6=120)
 *     1×6=6    → 结果的第2位 += 6   (实际上是 100×6=600)
 *     3×5=15   → 结果的第1位 += 15  (实际上是 3×50=150)
 *     ...
 *     最后统一处理进位。
 *
 * 时间复杂度：O(lenA × lenB)
 *
 * @param a  第一个大整数（字符串形式）
 * @param b  第二个大整数（字符串形式）
 * @return   乘积的字符串表示
 */
string highPrecisionMultiply(string a, string b) {
    // 特判：任一乘数为 0 则结果为 0
    if (a == "0" || b == "0") return "0";

    // 反转，使低位在前
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    int lenA = a.length();
    int lenB = b.length();

    // 乘积最多有 lenA + lenB 位
    // 例如 999 × 999 = 998001，3 + 3 = 6 位
    vector<int> result(lenA + lenB, 0);  // 初始全为 0

    // 双重循环：a 的每一位乘以 b 的每一位
    for (int i = 0; i < lenA; i++) {
        int digitA = a[i] - '0';
        for (int j = 0; j < lenB; j++) {
            int digitB = b[j] - '0';
            // a[i] * b[j] 的结果加到 result[i+j] 上
            result[i + j] += digitA * digitB;
        }
    }

    // 统一处理进位
    // 从最低位开始，将 >=10 的部分进位到高位
    for (int i = 0; i < lenA + lenB; i++) {
        if (result[i] >= 10) {
            result[i + 1] += result[i] / 10;  // 进位加到下一位
            result[i] %= 10;                   // 保留个位
        }
    }

    // 构建结果字符串（反向处理）
    string answer = "";
    // 从高位向低位扫描，跳过前导零
    int start = lenA + lenB - 1;
    while (start >= 0 && result[start] == 0) {
        start--;  // 跳过前导零
    }
    for (int i = start; i >= 0; i--) {
        answer += (char)(result[i] + '0');
    }

    return answer;
}

/**
 * @brief 演示高精度乘法
 */
void demoHighPrecisionMultiply() {
    cout << "【演示3】高精度乘法：" << endl;
    cout << endl;

    // 子演示 A：大整数 × 普通整数
    cout << "  [A] 大整数 × 普通整数：" << endl;
    string a1 = "123456789";
    int b1 = 45;
    string result1 = highPrecisionMultiplyInt(a1, b1);
    cout << "    " << a1 << " × " << b1 << " = " << result1 << endl;

    string a2 = "99999999999999999999";  // 20个9
    int b2 = 2;
    string result2 = highPrecisionMultiplyInt(a2, b2);
    cout << "    " << a2 << " × " << b2 << " = " << result2 << endl;

    // 子演示 B：大整数 × 大整数
    cout << endl;
    cout << "  [B] 大整数 × 大整数：" << endl;
    string a3 = "123";
    string b3 = "456";
    string result3 = highPrecisionMultiply(a3, b3);
    cout << "    " << a3 << " × " << b3 << " = " << result3 << endl;
    // 验证：123 × 456 = 56088
    cout << "    （验证：123 × 456 = "<< 123 * 456 << "）" << endl;

    string a4 = "12345678901234567890";
    string b4 = "98765432109876543210";
    string result4 = highPrecisionMultiply(a4, b4);
    cout << "    大整数1: " << a4 << endl;
    cout << "    大整数2: " << b4 << endl;
    cout << "    乘积:    " << result4 << endl;

    string a5 = "9999999999";  // 10个9
    string b5 = "9999999999";
    string result5 = highPrecisionMultiply(a5, b5);
    cout << "    验证: 9999999999² = " << result5 << endl;
    // 应该等于 99999999980000000001

    cout << endl;
}

// ============================================================
// 演示 4：进制转换
//
// 进制转换是计算机科学的基础。本演示涵盖两个方向：
//   A. 任意进制 → 十进制（按权展开法）
//   B. 十进制 → 任意进制（除基取余，倒序排列）
//
// 支持的进制范围：2 ~ 36（使用 0-9 和 A-Z 表示数字）
// ============================================================

/**
 * @brief 将单个字符转换为对应的数值
 *
 * '0'~'9' → 0~9
 * 'A'~'Z' → 10~35
 * 'a'~'z' → 10~35（也支持小写）
 *
 * @param ch  表示一个数位的字符
 * @return    对应的数值（0~35）
 */
int charToValue(char ch) {
    if (ch >= '0' && ch <= '9') {
        return ch - '0';          // '0'→0, '9'→9
    } else if (ch >= 'A' && ch <= 'Z') {
        return ch - 'A' + 10;     // 'A'→10, 'Z'→35
    } else if (ch >= 'a' && ch <= 'z') {
        return ch - 'a' + 10;     // 'a'→10, 'z'→35
    }
    return 0;  // 非法字符返回 0（假设输入合法）
}

/**
 * @brief 将数值转换为对应进制的字符
 *
 * 0~9   → '0'~'9'
 * 10~35 → 'A'~'Z'
 *
 * @param value  数值（0~35）
 * @return       对应的字符
 */
char valueToChar(int value) {
    if (value >= 0 && value <= 9) {
        return (char)(value + '0');      // 0→'0', 9→'9'
    } else {
        return (char)(value - 10 + 'A'); // 10→'A', 35→'Z'
    }
}

/**
 * @brief 任意进制转十进制（按权展开法）
 *
 * 算法：
 *   number = d₀×base^{n-1} + d₁×base^{n-2} + ... + d_{n-1}×base⁰
 *
 * 代码中使用"秦九韶算法"（Horner's method）高效实现：
 *   result = result * base + currentDigit
 * 这样避免了重复计算 base 的幂。
 *
 * 例如 2 进制 "1010" → 十进制：
 *   ((1*2 + 0)*2 + 1)*2 + 0 = 10
 *
 * @param numStr  源进制下的数字字符串（如 "1A"）
 * @param base    源进制（2~36）
 * @return        转换后的十进制数值
 */
long long anyBaseToDecimal(string numStr, int base) {
    long long result = 0;  // 累加结果（使用 long long 避免溢出）

    for (int i = 0; i < (int)numStr.length(); i++) {
        int digit = charToValue(numStr[i]);  // 当前位数值
        result = result * base + digit;       // 秦九韶算法：进位 + 加当前位
    }
    return result;
}

/**
 * @brief 十进制转任意进制（除基取余，倒序排列）
 *
 * 算法：
 *   不断将十进制数 n 除以目标进制 base：
 *     余数 → 当前最低位的数字
 *     商   → 继续除
 *   直到商为 0。
 *   将得到的余数序列反转即为结果。
 *
 * 例如 10 进制 13 → 2 进制：
 *   13 ÷ 2 = 6 ... 1
 *    6 ÷ 2 = 3 ... 0
 *    3 ÷ 2 = 1 ... 1
 *    1 ÷ 2 = 0 ... 1
 *   余数倒序：1101 → 结果 "1101"
 *
 * @param n      十进制整数（非负）
 * @param base   目标进制（2~36）
 * @return       目标进制下的字符串表示
 */
string decimalToAnyBase(long long n, int base) {
    if (n == 0) return "0";  // 特判：十进制 0 在任何进制下都是 "0"

    string result = "";  // 存储余数序列（倒序排列前的状态）

    while (n > 0) {
        int remainder = n % base;               // 当前余数
        result += valueToChar(remainder);       // 追加对应字符
        n /= base;                              // 更新商
    }

    // 反转得到正确顺序
    reverse(result.begin(), result.end());
    return result;
}

/**
 * @brief 演示进制转换
 */
void demoBaseConversion() {
    cout << "【演示4】进制转换：" << endl;
    cout << endl;

    // 子演示 A：任意进制 → 十进制
    cout << "  [A] 任意进制 → 十进制（按权展开 / 秦九韶算法）：" << endl;
    cout << "    二进制 \"1010\" (base=2)  → 十进制 " << anyBaseToDecimal("1010", 2) << endl;
    cout << "    八进制 \"77\"   (base=8)  → 十进制 " << anyBaseToDecimal("77", 8) << endl;
    cout << "    十六进制 \"1A\" (base=16) → 十进制 " << anyBaseToDecimal("1A", 16) << endl;
    cout << "    十六进制 \"FF\" (base=16) → 十进制 " << anyBaseToDecimal("FF", 16) << endl;
    cout << "    十六进制 \"ABC\"(base=16) → 十进制 " << anyBaseToDecimal("ABC", 16) << endl;

    // 验证：FF = 255
    cout << "    （验证：十六进制 FF = 15×16 + 15 = 255）" << endl;

    // 子演示 B：十进制 → 任意进制
    cout << endl;
    cout << "  [B] 十进制 → 任意进制（除基取余，倒序排列）：" << endl;
    cout << "    十进制 10 → 二进制  = \"" << decimalToAnyBase(10, 2) << "\"" << endl;
    cout << "    十进制 63 → 八进制  = \"" << decimalToAnyBase(63, 8) << "\"" << endl;
    cout << "    十进制 255 → 十六进制 = \"" << decimalToAnyBase(255, 16) << "\"" << endl;
    cout << "    十进制 2748 → 十六进制 = \"" << decimalToAnyBase(2748, 16) << "\"" << endl;
    // 2748 = 0xABC
    cout << "    （验证：2748 = 0xABC = 10×256 + 11×16 + 12 = 2748）" << endl;

    // 综合验证：先转十进制再转回原进制，应得原串
    cout << endl;
    cout << "  [C] 综合验证（往返转换）：" << endl;
    string original = "1A3F";
    int base = 16;
    long long decimal = anyBaseToDecimal(original, base);
    string converted = decimalToAnyBase(decimal, base);
    cout << "    十六进制 \"" << original << "\" → 十进制 " << decimal
         << " → 十六进制 \"" << converted << "\"";
    if (original == converted) {
        cout << " ✓ 一致！" << endl;
    } else {
        cout << " ✗ 不一致！" << endl;
    }

    cout << endl;
}

// ============================================================
// 主函数：依次运行四个演示
// ============================================================
int main() {
    cout << "========================================" << endl;
    cout << "  第28课：模拟算法（下）— 演示程序" << endl;
    cout << "========================================" << endl;
    cout << endl;

    // 演示 1：剪刀石头布游戏模拟
    demoRockPaperScissors();

    // 演示 2：约瑟夫环问题
    demoJosephus();

    // 演示 3：高精度乘法
    demoHighPrecisionMultiply();

    // 演示 4：进制转换
    demoBaseConversion();

    cout << "========================================" << endl;
    cout << "  所有演示完成！" << endl;
    cout << "========================================" << endl;

    return 0;
}
