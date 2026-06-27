/*
 * ============================================
 * 第40课：动态规划综合练习
 * ============================================
 * 本程序演示：
 *   1. 数字三角形 —— 自底向上DP（经典二维DP入门）
 *   2. 编辑距离 —— 双字符串DP（Levenshtein距离）
 *   3. DP解题方法论总结
 *
 * 核心思想：系统回顾DP的六步解题法，综合运用所学DP知识。
 * ============================================
 */

#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 105;
const int MAXLEN = 1005;

// ==========================================
// 1. 数字三角形 —— 自底向上DP
//    dp[i][j] = 从底部走到 (i,j) 的最大和
//    转移方程：dp[i][j] = max(dp[i+1][j], dp[i+1][j+1]) + a[i][j]
//    时间复杂度 O(n²)，空间复杂度 O(n²)
// ==========================================
int a[MAXN][MAXN];   // 存储三角形
int dp_tri[MAXN][MAXN];

int numberTriangle(int n) {
    // 初始化最后一行：底部各位置的 dp 值就是自身的值
    for (int j = 0; j < n; j++)
        dp_tri[n - 1][j] = a[n - 1][j];

    // 自底向上递推：从倒数第二行开始，逐层向上
    for (int i = n - 2; i >= 0; i--)
        for (int j = 0; j <= i; j++)
            dp_tri[i][j] = max(dp_tri[i + 1][j], dp_tri[i + 1][j + 1]) + a[i][j];

    return dp_tri[0][0];  // 答案在顶部
}

// ==========================================
// 2. 编辑距离 —— 双字符串DP
//    dp[i][j] = A[0..i-1] 转换为 B[0..j-1] 的最少操作次数
//    转移方程：
//      if A[i-1] == B[j-1]: dp[i][j] = dp[i-1][j-1]
//      else: dp[i][j] = min(删除, 插入, 替换) + 1
//    时间复杂度 O(m*n)，空间复杂度 O(m*n)
// ==========================================
int dp_ed[MAXLEN][MAXLEN];

int editDistance(const string& A, const string& B) {
    int m = A.size();
    int n = B.size();

    // 初始化边界条件
    // dp[i][0] = i：将 A 的前 i 个字符变为空串，需要 i 次删除
    for (int i = 0; i <= m; i++) dp_ed[i][0] = i;
    // dp[0][j] = j：将空串变为 B 的前 j 个字符，需要 j 次插入
    for (int j = 0; j <= n; j++) dp_ed[0][j] = j;

    // 递推填充 DP 表
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (A[i - 1] == B[j - 1]) {
                // 字符相同，无需操作
                dp_ed[i][j] = dp_ed[i - 1][j - 1];
            } else {
                // 三种操作中取最小：
                // dp[i-1][j] + 1   → 删除 A[i-1]
                // dp[i][j-1] + 1   → 在 A 末尾插入 B[j-1]
                // dp[i-1][j-1] + 1 → 替换 A[i-1] 为 B[j-1]
                dp_ed[i][j] = min({dp_ed[i - 1][j] + 1,
                                   dp_ed[i][j - 1] + 1,
                                   dp_ed[i - 1][j - 1] + 1});
            }
        }
    }

    return dp_ed[m][n];
}

// ==========================================
// 3. DP解题方法论总结
//    打印六步解题法的核心要点
// ==========================================
void dpSummary() {
    cout << "╔══════════════════════════════════════════════════════╗" << endl;
    cout << "║          动态规划解题六步法（DP Methodology）         ║" << endl;
    cout << "╠══════════════════════════════════════════════════════╣" << endl;
    cout << "║  Step 1  分析问题 ── 是否有重叠子问题 & 最优子结构？  ║" << endl;
    cout << "║  Step 2  定义状态 ── dp[...] 表示什么？               ║" << endl;
    cout << "║  Step 3  转移方程 ── 状态如何由子状态推得？            ║" << endl;
    cout << "║  Step 4  边界条件 ── 递推的起点是什么？                ║" << endl;
    cout << "║  Step 5  计算顺序 ── 循环该怎么写？正序还是逆序？      ║" << endl;
    cout << "║  Step 6  确定答案 ── 答案在 dp 数组的哪个位置？        ║" << endl;
    cout << "╠══════════════════════════════════════════════════════╣" << endl;
    cout << "║  已学 DP 类型总览：                                   ║" << endl;
    cout << "║  • 记忆化搜索（第35课）：自顶向下 + memo 数组          ║" << endl;
    cout << "║  • 线性DP一维（第36课）：dp[i] 仅依赖前序状态          ║" << endl;
    cout << "║  • 01背包（第37课）：选或不选，反向遍历               ║" << endl;
    cout << "║  • 完全背包（第38课）：无限取用，正向遍历             ║" << endl;
    cout << "║  • 区间DP（第39课）：dp[i][j] 枚举分割点 k             ║" << endl;
    cout << "╚══════════════════════════════════════════════════════╝" << endl;
}

// ==========================================
// 例题1：数字三角形 —— 完整交互式解答
// ==========================================
void solve_problem1() {
    cout << "========== 例题1：数字三角形 ==========" << endl;
    cout << "请输入三角形的行数 n：";
    int n;
    cin >> n;

    cout << "请逐行输入三角形的数字（第 i 行有 i 个数）：" << endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= i; j++)
            cin >> a[i][j];

    int result = numberTriangle(n);
    cout << "最大路径和 = " << result << endl;

    // 输出 DP 表以便理解
    cout << endl << "DP 表（自底向上）：" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            cout << dp_tri[i][j] << "\t";
        }
        cout << endl;
    }
}

// ==========================================
// 例题2：编辑距离 —— 完整交互式解答
// ==========================================
void solve_problem2() {
    cout << "========== 例题2：编辑距离 ==========" << endl;
    cout << "请输入字符串 A：";
    string A, B;
    cin >> A;
    cout << "请输入字符串 B：";
    cin >> B;

    int result = editDistance(A, B);
    cout << "将 \"" << A << "\" 转换为 \"" << B << "\" 的最少操作次数 = " << result << endl;

    // 输出 DP 表（若字符串较短）
    int m = A.size(), n = B.size();
    if (m <= 10 && n <= 10) {
        cout << endl << "DP 表：" << endl;
        cout << "    ";
        for (int j = 0; j < n; j++) cout << "  " << B[j];
        cout << endl;
        for (int i = 0; i <= m; i++) {
            if (i == 0)
                cout << "  ";
            else
                cout << A[i - 1] << " ";
            for (int j = 0; j <= n; j++) {
                cout << dp_ed[i][j] << "  ";
            }
            cout << endl;
        }
    }
}

// ==========================================
// 自动测试 —— 使用样例数据验证
// ==========================================
void auto_test() {
    cout << "========== 自动测试（样例数据） ==========" << endl;

    // 测试1：数字三角形
    cout << endl << "【测试1：数字三角形】" << endl;
    int test_tri[5][5] = {
        {7, 0, 0, 0, 0},
        {3, 8, 0, 0, 0},
        {8, 1, 0, 0, 0},
        {2, 7, 4, 4, 0},
        {4, 5, 2, 6, 5}
    };
    int n = 5;
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= i; j++)
            a[i][j] = test_tri[i][j];

    cout << "三角形：" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    int result1 = numberTriangle(n);
    cout << "最大路径和 = " << result1 << "（期望：30）";
    cout << (result1 == 30 ? " ✓ 通过" : " ✗ 失败") << endl;

    // 测试2：编辑距离
    cout << endl << "【测试2：编辑距离】" << endl;
    string A = "sunday";
    string B = "saturday";
    int result2 = editDistance(A, B);
    cout << "\"" << A << "\" → \"" << B << "\"" << endl;
    cout << "编辑距离 = " << result2 << "（期望：3）";
    cout << (result2 == 3 ? " ✓ 通过" : " ✗ 失败") << endl;

    // 额外测试：编辑距离
    cout << endl << "【额外测试：编辑距离】" << endl;
    string test_cases[][2] = {
        {"abc", "abc"},
        {"abc", ""},
        {"", "abc"},
        {"kitten", "sitting"},
        {"intention", "execution"}
    };
    int expected[] = {0, 3, 3, 3, 5};
    for (int k = 0; k < 5; k++) {
        int res = editDistance(test_cases[k][0], test_cases[k][1]);
        cout << "\"" << test_cases[k][0] << "\" → \""
             << test_cases[k][1] << "\" = " << res
             << "（期望：" << expected[k] << "）";
        cout << (res == expected[k] ? " ✓" : " ✗") << endl;
    }
}

// ==========================================
// 主函数 —— 菜单导航
// ==========================================
int main() {
    cout << "╔══════════════════════════════════════╗" << endl;
    cout << "║  第40课：动态规划综合练习           ║" << endl;
    cout << "╚══════════════════════════════════════╝" << endl;
    cout << endl;

    int choice;
    cout << "请选择功能：" << endl;
    cout << "  1 - DP解题方法论总结" << endl;
    cout << "  2 - 例题1：数字三角形（交互输入）" << endl;
    cout << "  3 - 例题2：编辑距离（交互输入）" << endl;
    cout << "  4 - 自动测试（样例数据验证）" << endl;
    cout << "  5 - 全部运行" << endl;
    cout << "请输入 (1-5)：";
    cin >> choice;

    switch (choice) {
        case 1:
            dpSummary();
            break;
        case 2:
            solve_problem1();
            break;
        case 3:
            solve_problem2();
            break;
        case 4:
            auto_test();
            break;
        case 5:
            dpSummary();
            cout << endl;
            solve_problem1();
            cout << endl;
            solve_problem2();
            cout << endl;
            auto_test();
            break;
        default:
            cout << "无效选择！" << endl;
    }

    return 0;
}
