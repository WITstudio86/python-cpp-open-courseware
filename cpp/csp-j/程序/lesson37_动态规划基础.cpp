/**
 * CSP-J 备考课程
 * 第37课：动态规划基础 —— 完整演示程序
 *
 * 本文件覆盖：
 * 1. DP 四要素示意（状态 / 转移 / 边界 / 计算顺序）
 * 2. 数字三角形 —— 自底向上递推
 * 3. 数字三角形 —— 记忆化搜索（自顶向下）
 * 4. 网格路径计数（无障碍）
 * 5. 带障碍路径计数（过河卒思想）
 * 6. 递推 vs 记忆化 vs 暴力递归对比说明
 *
 * 全部使用内置样例数据，无需交互输入，便于课堂演示与打印。
 */

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <climits>
using namespace std;

// ==================== 工具 ====================

void printSep(const string &title) {
    cout << "\n========== " << title << " ==========\n";
}

// ==================== 1. DP 四要素示意 ====================
// 问题：爬楼梯，每次 1 或 2 阶，求爬到 n 阶的方案数
// 状态：f[i] = 爬到 i 阶的方案数
// 转移：f[i] = f[i-1] + f[i-2]
// 边界：f[0]=1, f[1]=1（或 f[1]=1, f[2]=2）
// 顺序：从小到大

void demoClimbStairsDP() {
    printSep("1. DP四要素示例：爬楼梯方案数");
    int n = 10;
    vector<long long> f(n + 1, 0);
    f[0] = 1;
    f[1] = 1;
    for (int i = 2; i <= n; i++) {
        f[i] = f[i - 1] + f[i - 2];
    }
    cout << "爬 " << n << " 阶楼梯的方案数 f[" << n << "] = " << f[n] << endl;
    cout << "前缀序列: ";
    for (int i = 0; i <= n; i++) cout << f[i] << (i == n ? "\n" : " ");
    cout << "要点：先定状态与转移，再写边界与循环顺序。\n";
}

// ==================== 2. 数字三角形 自底向上 ====================

void digitalTriangleBottomUp() {
    printSep("2. 数字三角形（自底向上递推DP）");
    // 样例三角形：
    //      7
    //     3 8
    //    8 1 0
    //   2 7 4 4
    //  4 5 2 6 5
    // 答案 30 = 7-3-8-7-5
    int n = 5;
    int a[6][6] = {{0}};
    a[1][1] = 7;
    a[2][1] = 3; a[2][2] = 8;
    a[3][1] = 8; a[3][2] = 1; a[3][3] = 0;
    a[4][1] = 2; a[4][2] = 7; a[4][3] = 4; a[4][4] = 4;
    a[5][1] = 4; a[5][2] = 5; a[5][3] = 2; a[5][4] = 6; a[5][5] = 5;

    int dp[6][6] = {{0}};
    for (int j = 1; j <= n; j++) dp[n][j] = a[n][j];
    for (int i = n - 1; i >= 1; i--) {
        for (int j = 1; j <= i; j++) {
            dp[i][j] = max(dp[i + 1][j], dp[i + 1][j + 1]) + a[i][j];
        }
    }

    cout << "样例三角形行数 n = " << n << endl;
    cout << "最大路径和 dp[1][1] = " << dp[1][1] << "（期望 30）\n";
    cout << "转移：dp[i][j] = a[i][j] + max(dp[i+1][j], dp[i+1][j+1])\n";
}

// ==================== 3. 数字三角形 记忆化搜索 ====================

const int MAXN = 20;
int tri[MAXN][MAXN];
int memo[MAXN][MAXN];
bool vis[MAXN][MAXN];
int g_n;

int dfsTriangle(int i, int j) {
    if (j < 1 || j > i) return INT_MIN / 4;
    if (i == g_n) return tri[i][j];
    if (vis[i][j]) return memo[i][j];
    vis[i][j] = true;
    memo[i][j] = tri[i][j] + max(dfsTriangle(i + 1, j), dfsTriangle(i + 1, j + 1));
    return memo[i][j];
}

void digitalTriangleMemo() {
    printSep("3. 数字三角形（记忆化搜索）");
    g_n = 5;
    memset(vis, 0, sizeof(vis));
    memset(memo, 0, sizeof(memo));
    tri[1][1] = 7;
    tri[2][1] = 3; tri[2][2] = 8;
    tri[3][1] = 8; tri[3][2] = 1; tri[3][3] = 0;
    tri[4][1] = 2; tri[4][2] = 7; tri[4][3] = 4; tri[4][4] = 4;
    tri[5][1] = 4; tri[5][2] = 5; tri[5][3] = 2; tri[5][4] = 6; tri[5][5] = 5;

    int ans = dfsTriangle(1, 1);
    cout << "记忆化搜索结果 = " << ans << "（应与递推一致）\n";
    cout << "本质：递归树 + 缓存，每个状态只算一次。\n";
}

// ==================== 4. 网格路径计数 ====================

void gridPathCount() {
    printSep("4. 网格路径计数（无障碍）");
    int m = 3, n = 4;  // 3x4 网格
    vector<vector<long long>> dp(m + 1, vector<long long>(n + 1, 0));
    for (int j = 1; j <= n; j++) dp[1][j] = 1;
    for (int i = 1; i <= m; i++) dp[i][1] = 1;
    for (int i = 2; i <= m; i++)
        for (int j = 2; j <= n; j++)
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];

    cout << "从 (1,1) 到 (" << m << "," << n << ") 只能右/下，路径数 = "
         << dp[m][n] << endl;
    cout << "DP 表：\n";
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) cout << dp[i][j] << "\t";
        cout << "\n";
    }
}

// ==================== 5. 带障碍路径（过河卒简化） ====================

void horseAndPawnDemo() {
    printSep("5. 带障碍路径计数（过河卒思想）");
    // B 点 (n,m)=(6,6)，马在 (2,1)，控制点不可走
    int n = 6, m = 6, hx = 2, hy = 1;
    const int MAX = 30;
    long long dp[MAX][MAX];
    bool block[MAX][MAX];
    memset(dp, 0, sizeof(dp));
    memset(block, 0, sizeof(block));

    int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2, 0};
    int dy[] = {1, 2, 2, 1, -1, -2, -2, -1, 0};
    for (int k = 0; k < 9; k++) {
        int nx = hx + dx[k], ny = hy + dy[k];
        if (nx >= 0 && nx <= n && ny >= 0 && ny <= m)
            block[nx][ny] = true;
    }

    if (!block[0][0]) dp[0][0] = 1;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (block[i][j]) {
                dp[i][j] = 0;
                continue;
            }
            if (i == 0 && j == 0) continue;
            if (i > 0) dp[i][j] += dp[i - 1][j];
            if (j > 0) dp[i][j] += dp[i][j - 1];
        }
    }
    cout << "B=(" << n << "," << m << ") 马=(" << hx << "," << hy << ")\n";
    cout << "路径数 = " << dp[n][m] << endl;
    cout << "技巧：障碍格状态强制为 0，其余仍用 dp[i][j]=左+上。\n";
}

// ==================== 6. 暴力递归 vs 记忆化（斐波那契） ====================

long long fibRaw(int n, long long &calls) {
    calls++;
    if (n <= 1) return n;
    return fibRaw(n - 1, calls) + fibRaw(n - 2, calls);
}

long long fibMemoHelper(int n, vector<long long> &mem, long long &calls) {
    calls++;
    if (n <= 1) return n;
    if (mem[n] != -1) return mem[n];
    return mem[n] = fibMemoHelper(n - 1, mem, calls) + fibMemoHelper(n - 2, mem, calls);
}

void demoFibCompare() {
    printSep("6. 暴力递归 vs 记忆化（理解为何需要DP）");
    int n = 12;
    long long c1 = 0, c2 = 0;
    long long a = fibRaw(n, c1);
    vector<long long> mem(n + 1, -1);
    long long b = fibMemoHelper(n, mem, c2);
    cout << "fib(" << n << ") = " << a << "（暴力调用次数 " << c1 << "）\n";
    cout << "fib(" << n << ") = " << b << "（记忆化调用次数 " << c2 << "）\n";
    cout << "记忆化/DP 把指数级重复计算压到 O(n)。\n";
}

// ==================== 7. 一维滚动数组思想（路径数压缩） ====================

void demoRollingArray() {
    printSep("7. 滚动数组思想：网格路径一维优化");
    int m = 3, n = 4;
    vector<long long> dp(n + 1, 1);  // 第 1 行全为 1，下标 1..n
    dp[0] = 0;
    for (int i = 2; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (j == 1) dp[j] = 1;
            else dp[j] = dp[j] + dp[j - 1];  // 原 dp[i-1][j] + dp[i][j-1]
        }
    }
    cout << "3x4 网格路径数（一维）= " << dp[n] << endl;
    cout << "空间从 O(mn) 降到 O(n)，CSP-J 背包优化同理。\n";
}

// ==================== main ====================

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "============================================\n";
    cout << "  第37课：动态规划基础 —— 演示程序\n";
    cout << "============================================\n";

    demoClimbStairsDP();
    digitalTriangleBottomUp();
    digitalTriangleMemo();
    gridPathCount();
    horseAndPawnDemo();
    demoFibCompare();
    demoRollingArray();

    cout << "\n========== 第37课演示结束 ==========\n";
    return 0;
}
