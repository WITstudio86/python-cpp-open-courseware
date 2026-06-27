/*
 * ================================================================
 * C++算法提高 第33课：高精度综合运算
 * ================================================================
 *
 * 算法知识点：
 *   - 高精度四则运算的整合：将加法、减法、乘法、除法封装到统一结构体
 *   - BigInt 结构体：使用 vector<int> 倒序存储，实现各种运算
 *   - 高精度 × 低精度：用于阶乘等场景的高效乘法
 *   - 高精度 ÷ 低精度：模拟竖式除法，逐位求商
 *   - 高精度阶乘：循环调用高精度×低精度，计算 n!
 *
 * 经典例题：
 *   例题1 - 高精度计算器模拟：输入运算符和两个大整数（≤200位），输出结果
 *   例题2 - 高精度阶乘：输入 n（≤500），计算 n!
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// ================================================================
// BigInt 结构体：高精度非负整数
//
// 存储方式：vector<int> digits 倒序存储
//   例如：数字 12345 存储为 [5, 4, 3, 2, 1]
//   digits[0] = 个位, digits[1] = 十位, ...
//
// 这种存储方式的优点：
//   1. 加减乘除都是从低位到高位操作，与数组索引增长方向一致
//   2. 进位/借位时在数组末尾添加元素很方便（push_back）
// ================================================================
struct BigInt {
    vector<int> digits;  // 倒序存储每一位数字（0-9）

    // ----------------------------------------------------------
    // 从字符串构造 BigInt
    // 例如："12345" → digits = [5, 4, 3, 2, 1]
    // ----------------------------------------------------------
    void fromString(const string &s) {
        digits.clear();
        // 从字符串末尾开始（个位），逐个转换为数字并存入
        for (int i = s.size() - 1; i >= 0; i--) {
            digits.push_back(s[i] - '0');  // 字符'0'~'9'转整数0~9
        }
    }

    // ----------------------------------------------------------
    // 从整数构造 BigInt
    // 例如：12345 → digits = [5, 4, 3, 2, 1]
    // ----------------------------------------------------------
    void fromInt(long long n) {
        digits.clear();
        if (n == 0) {
            digits.push_back(0);  // 特殊情况：值为0
            return;
        }
        // 不断取出个位数字
        while (n > 0) {
            digits.push_back(n % 10);  // 取个位
            n /= 10;                    // 去掉个位
        }
    }

    // ----------------------------------------------------------
    // 输出 BigInt（从高位到低位打印）
    // ----------------------------------------------------------
    void print() const {
        for (int i = digits.size() - 1; i >= 0; i--) {
            cout << digits[i];
        }
    }

    // ----------------------------------------------------------
    // 比较函数：判断 this >= other
    // 用于减法时保证被减数 >= 减数
    // 返回值：true 表示 this >= other
    // ----------------------------------------------------------
    bool greaterOrEqual(const BigInt &other) const {
        // 先比较位数：位数多的更大
        if (digits.size() != other.digits.size()) {
            return digits.size() > other.digits.size();
        }
        // 位数相同，从高位到低位逐位比较
        for (int i = digits.size() - 1; i >= 0; i--) {
            if (digits[i] != other.digits[i]) {
                return digits[i] > other.digits[i];
            }
        }
        return true;  // 完全相等
    }

    // ==========================================================
    // 高精度加法：this + other
    //
    // 算法流程：
    //   1. 从最低位（i=0）开始，逐位相加
    //   2. 每位计算：sum = a[i] + b[i] + carry（进位）
    //   3. 当前位结果 = sum % 10，新进位 = sum / 10
    //   4. 最后如果还有进位，在最高位补一个1
    //
    // 时间复杂度：O(n)，n = max(len(this), len(other))
    // ==========================================================
    BigInt add(const BigInt &other) const {
        BigInt result;
        int carry = 0;  // 进位，初始为0
        size_t maxLen = max(digits.size(), other.digits.size());

        // 逐位相加
        for (size_t i = 0; i < maxLen; i++) {
            // 获取当前位的数字，如果某数已经没位了则补0
            int a = (i < digits.size()) ? digits[i] : 0;
            int b = (i < other.digits.size()) ? other.digits[i] : 0;
            int sum = a + b + carry;          // 加上进位
            result.digits.push_back(sum % 10); // 当前位
            carry = sum / 10;                  // 更新进位
        }

        // 如果最高位还有进位，补一位
        if (carry > 0) {
            result.digits.push_back(carry);
        }

        return result;
    }

    // ==========================================================
    // 高精度减法：this - other
    //
    // 前提条件：this >= other（调用前需保证）
    //
    // 算法流程：
    //   1. 从最低位开始，逐位相减
    //   2. 每位计算：diff = a[i] - b[i] - borrow（借位）
    //   3. 如果 diff < 0，则 diff += 10，借位置1
    //   4. 最后去除结果中的前导零
    //
    // 时间复杂度：O(n)，n = len(this)
    // ==========================================================
    BigInt subtract(const BigInt &other) const {
        BigInt result;
        int borrow = 0;  // 借位，初始为0

        // 逐位相减
        for (size_t i = 0; i < digits.size(); i++) {
            int a = digits[i];                                      // 被减数当前位
            int b = (i < other.digits.size()) ? other.digits[i] : 0; // 减数当前位
            int diff = a - b - borrow;  // 减去借位

            if (diff < 0) {
                diff += 10;   // 不够减，向高位借1（即加10）
                borrow = 1;   // 标记借位
            } else {
                borrow = 0;   // 够减，无借位
            }

            result.digits.push_back(diff);
        }

        // 去除前导零（例如：100 - 99 = 001，应输出1）
        while (result.digits.size() > 1 && result.digits.back() == 0) {
            result.digits.pop_back();
        }

        return result;
    }

    // ==========================================================
    // 高精度乘法：this × other（两个大整数相乘）
    //
    // 核心公式：c[i+j] += a[i] * b[j]
    //
    // 算法流程：
    //   1. 创建结果数组，大小为 len(a) + len(b)，初始全0
    //   2. 双重循环：将 a[i] * b[j] 累加到 c[i+j]
    //   3. 统一处理进位（从低位到高位）
    //   4. 去除前导零
    //
    // 为什么 c[i+j]？
    //   a[i] 的实际值是 a[i] × 10^i
    //   b[j] 的实际值是 b[j] × 10^j
    //   乘积 = a[i] × b[j] × 10^(i+j)
    //   所以在结果中应该放在第 i+j 位
    //
    // 时间复杂度：O(n×m)，n、m分别为两数位数
    // ==========================================================
    BigInt multiply(const BigInt &other) const {
        BigInt result;
        // 结果最多有 len(a) + len(b) 位
        result.digits.resize(digits.size() + other.digits.size(), 0);

        // 双重循环：逐位相乘，累加到对应位置
        for (size_t i = 0; i < digits.size(); i++) {
            for (size_t j = 0; j < other.digits.size(); j++) {
                result.digits[i + j] += digits[i] * other.digits[j];
            }
        }

        // 统一处理进位
        int carry = 0;
        for (size_t i = 0; i < result.digits.size(); i++) {
            int sum = result.digits[i] + carry;
            result.digits[i] = sum % 10;  // 当前位
            carry = sum / 10;              // 进位
        }
        // 注意：carry 最后一定为0，因为结果数组大小已预留足够

        // 去除前导零
        while (result.digits.size() > 1 && result.digits.back() == 0) {
            result.digits.pop_back();
        }

        return result;
    }

    // ==========================================================
    // 高精度 × 低精度：this × num（num 是普通 int）
    //
    // 与两个大整数相乘不同，这里只需要单层循环：
    //   每位 = digits[i] × num + carry
    //
    // 这个函数特别适用于阶乘等场景，
    // 因为乘数 i 是普通整数（≤500），不需要高精度
    //
    // 时间复杂度：O(n)，n = len(this)
    // ==========================================================
    BigInt multiplyInt(int num) const {
        BigInt result;
        int carry = 0;  // 进位

        // 逐位乘以 num，加上进位
        for (size_t i = 0; i < digits.size(); i++) {
            int prod = digits[i] * num + carry;
            result.digits.push_back(prod % 10);  // 当前位
            carry = prod / 10;                    // 进位
        }

        // 处理剩余的进位
        // 例如：999 × 2，最后 carry 可能有多位
        while (carry > 0) {
            result.digits.push_back(carry % 10);
            carry /= 10;
        }

        return result;
    }

    // ==========================================================
    // 高精度 ÷ 低精度：this ÷ divisor
    //
    // 参数：
    //   divisor  - 除数（普通 int）
    //   remainder - 输出参数，返回余数
    //
    // 算法流程（模拟竖式除法）：
    //   1. 从最高位开始，维护当前余数 r
    //   2. 对于每一位：r = r × 10 + digits[i]
    //   3. 商 = r / divisor，存入结果
    //   4. r = r % divisor，继续下一位
    //   5. 反转结果（因为是从高位到低位计算的）
    //   6. 去除前导零
    //
    // 示例：12345 ÷ 6
    //   i=4: r=1,      1÷6=0余1
    //   i=3: r=12,    12÷6=2余0
    //   i=2: r=3,      3÷6=0余3
    //   i=1: r=34,    34÷6=5余4
    //   i=0: r=45,    45÷6=7余3
    //   商=[0,2,0,5,7] → 反转 → [7,5,0,2,0] → 去零 → 2057
    //   余数=3
    //
    // 时间复杂度：O(n)，n = len(this)
    // ==========================================================
    BigInt divide2(int divisor, int &remainder) const {
        BigInt result;
        int r = 0;  // 当前累计余数

        // 从高位到低位处理
        for (int i = digits.size() - 1; i >= 0; i--) {
            r = r * 10 + digits[i];   // 把当前位"拉下来"
            result.digits.push_back(r / divisor);  // 当前位的商
            r = r % divisor;          // 更新余数
        }

        // 此时商是从高位到低位存储的，需要反转
        // 例如：[0,2,0,5,7] → [7,5,0,2,0]
        reverse(result.digits.begin(), result.digits.end());

        // 去除前导零
        while (result.digits.size() > 1 && result.digits.back() == 0) {
            result.digits.pop_back();
        }

        remainder = r;
        return result;
    }
};

// ================================================================
// 例题2：高精度阶乘
// 题目：输入 n（1 ≤ n ≤ 500），计算 n!
//
// 算法思路：
//   1. 初始化 result = 1
//   2. for i = 2 to n:
//        result = result × i   （高精度 × 低精度）
//   3. 输出 result
//
// 为什么用 multiplyInt 而不是 multiply？
//   因为 i 是普通整数（≤500），使用 multiplyInt 效率更高（O(n) vs O(n²)）
// ================================================================
BigInt factorial(int n) {
    BigInt result;
    result.fromInt(1);  // 初始值：1

    for (int i = 2; i <= n; i++) {
        result = result.multiplyInt(i);  // result = result × i
    }

    return result;
}

// ================================================================
// 辅助函数：打印分隔线
// ================================================================
void printSeparator(const string &title) {
    cout << endl;
    cout << "════════════════════════════════════════" << endl;
    cout << "  " << title << endl;
    cout << "════════════════════════════════════════" << endl;
}

// ================================================================
// 例题1：高精度计算器模拟
//
// 题目描述：
//   输入一个运算符（+、-、*）和两个非负大整数（≤200位）
//   输出计算结果
//
// 输入格式：op a b（空格分隔）
// 输出格式：计算结果
//
// 示例：
//   输入：+ 12345678901234567890 98765432109876543210
//   输出：111111111011111111100
// ================================================================
void solveCalculator() {
    printSeparator("例题1：高精度计算器模拟");

    cout << "请输入运算符（+、-、*）和两个大整数：" << endl;
    cout << "格式：运算符 数字1 数字2" << endl;
    cout << "示例：+ 12345678901234567890 98765432109876543210" << endl;
    cout << "----------------------------------------" << endl;

    char op;
    string sa, sb;
    cin >> op >> sa >> sb;

    BigInt a, b, result;
    a.fromString(sa);
    b.fromString(sb);

    cout << "计算过程：" << endl;
    a.print();
    cout << " " << op << " ";
    b.print();
    cout << " = ";

    // 根据运算符选择对应的运算
    if (op == '+') {
        // 高精度加法
        result = a.add(b);
        result.print();
    } else if (op == '-') {
        // 高精度减法：需要保证结果非负
        if (a.greaterOrEqual(b)) {
            result = a.subtract(b);
            result.print();
        } else {
            // 小数减大数，输出负号，然后大数减小数
            cout << "-";
            result = b.subtract(a);
            result.print();
        }
    } else if (op == '*') {
        // 高精度乘法
        result = a.multiply(b);
        result.print();
    } else {
        cout << "不支持的运算符！仅支持 +、-、*";
    }

    cout << endl;
}

// ================================================================
// 例题2：高精度阶乘演示
//
// 演示 n! 的计算过程，并展示结果
// ================================================================
void solveFactorial() {
    printSeparator("例题2：高精度阶乘");

    cout << "请输入一个正整数 n（1 ≤ n ≤ 500）：" << endl;
    cout << "示例：10 或 50" << endl;
    cout << "----------------------------------------" << endl;

    int n;
    cin >> n;

    if (n < 0) {
        cout << "输入无效，请输入非负整数！" << endl;
        return;
    }

    if (n == 0) {
        cout << "0! = 1" << endl;
        return;
    }

    BigInt result = factorial(n);

    cout << n << "! = ";
    result.print();
    cout << endl;

    // 显示结果的位数
    cout << "（共 " << result.digits.size() << " 位数字）" << endl;
}

// ================================================================
// 附加演示：BigInt 各运算的单元测试
//
// 演示加法、减法、乘法、除法的基本用法
// ================================================================
void demoOperations() {
    printSeparator("演示：高精度四则运算");

    BigInt a, b, result;
    int remainder;

    // 测试数据
    a.fromString("12345678901234567890");
    b.fromString("98765432109876543210");

    // 加法测试
    cout << "【加法测试】" << endl;
    a.print(); cout << " + "; b.print(); cout << " = ";
    result = a.add(b);
    result.print();
    cout << endl << endl;

    // 减法测试（大减小）
    cout << "【减法测试】" << endl;
    b.print(); cout << " - "; a.print(); cout << " = ";
    result = b.subtract(a);
    result.print();
    cout << endl << endl;

    // 乘法测试
    cout << "【乘法测试】" << endl;
    a.print(); cout << " × "; b.print(); cout << " = ";
    result = a.multiply(b);
    result.print();
    cout << endl << endl;

    // 除法测试（除以低精度）
    cout << "【除法测试】12345 ÷ 6" << endl;
    BigInt c;
    c.fromInt(12345);
    result = c.divide2(6, remainder);
    c.print(); cout << " ÷ 6 = ";
    result.print();
    cout << " ... 余 " << remainder;
    cout << endl << endl;

    // 乘以低精度测试
    cout << "【乘以低精度测试】999 × 99" << endl;
    BigInt d;
    d.fromInt(999);
    result = d.multiplyInt(99);
    d.print(); cout << " × 99 = ";
    result.print();
    cout << endl;
}

// ================================================================
// 主函数
// ================================================================
int main() {
    cout << "╔══════════════════════════════════════════════╗" << endl;
    cout << "║   C++ 算法提高 —— 第33课：高精度综合运算      ║" << endl;
    cout << "║   四则运算整合 · 计算器模拟 · 高精度阶乘       ║" << endl;
    cout << "╚══════════════════════════════════════════════╝" << endl;
    cout << endl;

    cout << "本课将高精度加、减、乘、除四种运算整合到" << endl;
    cout << "BigInt 结构体中，实现统一的高精度计算框架。" << endl;
    cout << "包含两个经典例题：计算器模拟和高精度阶乘。" << endl;

    // 选择运行模式
    cout << endl;
    cout << "请选择运行模式：" << endl;
    cout << "  1 - 演示四则运算" << endl;
    cout << "  2 - 例题1：高精度计算器模拟" << endl;
    cout << "  3 - 例题2：高精度阶乘" << endl;
    cout << "  0 - 运行全部" << endl;
    cout << "----------------------------------------" << endl;
    cout << "请输入选项：";

    int choice;
    cin >> choice;

    if (choice == 1 || choice == 0) {
        demoOperations();
    }
    if (choice == 2 || choice == 0) {
        solveCalculator();
    }
    if (choice == 3 || choice == 0) {
        solveFactorial();
    }

    // 本课小结
    cout << endl;
    cout << "════════════════════════════════════════" << endl;
    cout << "  本课小结" << endl;
    cout << "════════════════════════════════════════" << endl;
    cout << "1. 高精度加法：逐位相加，处理进位 O(n)" << endl;
    cout << "2. 高精度减法：逐位相减，处理借位 O(n)" << endl;
    cout << "3. 高精度乘法：c[i+j] += a[i]*b[j] O(n×m)" << endl;
    cout << "4. 高精×低精：逐位乘+进位 O(n)" << endl;
    cout << "5. 高精÷低精：模拟竖式除法 O(n)" << endl;
    cout << "6. 高精度阶乘：循环调用高精×低精" << endl;
    cout << "════════════════════════════════════════" << endl;

    return 0;
}
