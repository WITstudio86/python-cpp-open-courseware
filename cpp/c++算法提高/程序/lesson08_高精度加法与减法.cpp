/**
 * 第08课：高精度加法与减法
 *
 * 算法知识点：
 * 1. 大数存储 — 字符串读入，倒序存入 vector<int>（索引0=个位）
 * 2. 高精度加法 — 逐位相加，t % 10 得当前位，t / 10 得进位
 * 3. 高精度减法 — 逐位相减，(t+10)%10 统一处理正负；不够减借位
 * 4. 大数比较 — 先比位数，位数相同从高位向低位逐位比较
 * 5. 前导零处理 — 减法结果 pop_back 去除末尾的 0
 * 6. 负数处理 — A<B 时交换计算并在结果前加 "-"
 *
 * 适用场景：int（~10位）和 long long（~19位）无法容纳的超大整数运算
 * 作者：C++算法提高课程
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
using namespace std;

// ============================================================
// 辅助函数：将字符串转换为倒序存储的 vector<int>
// 例如："123" → [3, 2, 1]（索引 0 是个位）
// ============================================================
vector<int> toVector(const string &s) {
    vector<int> res;
    for (int i = s.size() - 1; i >= 0; --i)
        res.push_back(s[i] - '0');
    return res;
}

// ============================================================
// 辅助函数：将倒序 vector<int> 转为可读字符串，自动去前导零
// 例如：[3, 2, 1] → "123"; [0, 0, 1] → "1"
// ============================================================
string toString(const vector<int> &v) {
    if (v.empty()) return "0";
    string res;
    for (int i = v.size() - 1; i >= 0; --i)
        res += char(v[i] + '0');
    int pos = 0;
    while (pos + 1 < (int)res.size() && res[pos] == '0') ++pos;
    return res.substr(pos);
}

// ============================================================
// 辅助函数：大数比较 — A >= B 返回 true（倒序存储）
// ============================================================
bool cmp(const vector<int> &A, const vector<int> &B) {
    if (A.size() != B.size())
        return A.size() > B.size();
    for (int i = A.size() - 1; i >= 0; --i)
        if (A[i] != B[i])
            return A[i] > B[i];
    return true;  // 完全相等
}

// ============================================================
// 核心算法1：高精度加法
// t 变量一箭三雕：进位载体 + 累加器 + 当前位来源
// ============================================================
vector<int> add(const vector<int> &A, const vector<int> &B) {
    vector<int> C;
    int t = 0;
    for (size_t i = 0; i < max(A.size(), B.size()); ++i) {
        if (i < A.size()) t += A[i];
        if (i < B.size()) t += B[i];
        C.push_back(t % 10);   // 当前位 = 累加和的个位
        t /= 10;               // 进位 = 累加和的十位
    }
    if (t) C.push_back(t);     // 最高位仍有进位
    return C;
}

// ============================================================
// 核心算法2：高精度减法（A >= B）
// (t+10)%10 统一处理正负：t≥0得t，t<0得t+10
// ============================================================
vector<int> sub(const vector<int> &A, const vector<int> &B) {
    vector<int> C;
    int t = 0;  // 借位标记
    for (int i = 0; i < (int)A.size(); ++i) {
        t = A[i] - t;                      // 减去借位
        if (i < (int)B.size()) t -= B[i];  // 减去减数
        C.push_back((t + 10) % 10);        // 统一处理正负
        t = (t < 0) ? 1 : 0;               // 更新借位
    }
    // 去除前导零（高位多余的零）
    while (C.size() > 1 && C.back() == 0)
        C.pop_back();
    return C;
}

// ============================================================
// 问题求解1：A+B Problem（高精度）
// ============================================================
void solveAdd() {
    string a, b;
    cout << "请输入两个非负大整数 A 和 B（用空格或换行分隔）：" << endl;
    cin >> a >> b;
    vector<int> A = toVector(a);
    vector<int> B = toVector(b);
    vector<int> C = add(A, B);
    cout << "A + B = " << toString(C) << endl;
}

// ============================================================
// 问题求解2：大数减法（自动处理负数）
// ============================================================
void solveSub() {
    string a, b;
    cout << "请输入被减数 A 和减数 B（用空格或换行分隔）：" << endl;
    cin >> a >> b;
    vector<int> A = toVector(a);
    vector<int> B = toVector(b);

    if (cmp(A, B)) {
        vector<int> C = sub(A, B);
        cout << "A - B = " << toString(C) << endl;
    } else {
        vector<int> C = sub(B, A);
        cout << "A - B = -" << toString(C) << endl;
    }
}

// ============================================================
// 自动测试：运行预设测试用例
// ============================================================
void runTests() {
    cout << "========== 高精度加法 自动测试 ==========" << endl;

    struct { string a, b, expected; } addTests[] = {
        {"123",       "456",       "579"},
        {"999",       "1",         "1000"},
        {"0",         "0",         "0"},
        {"999999",    "1",         "1000000"},
        {"12345678901234567890", "98765432109876543210", "111111111011111111100"},
        {"11111111111111111111", "22222222222222222222", "33333333333333333333"},
    };

    int passCount = 0;
    for (auto &tc : addTests) {
        vector<int> A = toVector(tc.a);
        vector<int> B = toVector(tc.b);
        vector<int> C = add(A, B);
        string result = toString(C);
        bool pass = (result == tc.expected);
        if (pass) ++passCount;
        cout << "  " << tc.a << " + " << tc.b << " = " << result
             << "  [" << (pass ? "PASS" : "FAIL") << "]" << endl;
        if (!pass) cout << "    期望: " << tc.expected << endl;
    }
    cout << "  加法通过: " << passCount << "/6" << endl << endl;

    cout << "========== 高精度减法 自动测试 ==========" << endl;

    struct { string a, b, expected; } subTests[] = {
        {"1000",      "1",         "999"},
        {"1",         "1000",      "-999"},
        {"12345",     "12345",     "0"},
        {"10000",     "1234",      "8766"},
        {"98765432109876543210", "12345678901234567890", "86419753208641975320"},
        {"100000000000000000000", "1", "99999999999999999999"},
    };

    passCount = 0;
    for (auto &tc : subTests) {
        vector<int> A = toVector(tc.a);
        vector<int> B = toVector(tc.b);

        string result;
        if (cmp(A, B)) {
            vector<int> C = sub(A, B);
            result = toString(C);
        } else {
            vector<int> C = sub(B, A);
            result = "-" + toString(C);
        }

        bool pass = (result == tc.expected);
        if (pass) ++passCount;
        cout << "  " << tc.a << " - " << tc.b << " = " << result
             << "  [" << (pass ? "PASS" : "FAIL") << "]" << endl;
        if (!pass) cout << "    期望: " << tc.expected << endl;
    }
    cout << "  减法通过: " << passCount << "/6" << endl << endl;
}

// ============================================================
// 交互式主菜单
// ============================================================
int main() {
    cout << "========================================" << endl;
    cout << "  第08课：高精度加法与减法" << endl;
    cout << "  大数存储 · 逐位运算 · 进位借位" << endl;
    cout << "========================================" << endl;

    while (true) {
        cout << endl;
        cout << "请选择操作：" << endl;
        cout << "  1. 高精度加法（A + B）" << endl;
        cout << "  2. 高精度减法（A - B）" << endl;
        cout << "  3. 自动运行测试用例" << endl;
        cout << "  0. 退出" << endl;
        cout << "请输入选项 (0-3): ";

        int choice;
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "无效输入，请输入数字 0-3。" << endl;
            continue;
        }
        cin.ignore(10000, '\n');

        switch (choice) {
            case 1: cout << endl; solveAdd(); break;
            case 2: cout << endl; solveSub(); break;
            case 3: cout << endl; runTests(); break;
            case 0: cout << "再见！" << endl; return 0;
            default: cout << "无效选项，请重新输入。" << endl; break;
        }
    }
    return 0;
}
