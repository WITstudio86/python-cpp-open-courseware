/**
 * lesson37_动态规划基础.cpp
 * CSP-J 备考课程 第37课
 *
 * 包含内容：
 * 1. 数字三角形 - 从底向上递推DP（自底向上）
 * 2. 数字三角形 - 记忆化搜索（自顶向下）
 * 3. 网格路径计数
 * 4. 带障碍物的路径计数（过河卒）
 */

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// 一、数字三角形（从底向上递推DP - 推荐写法）
// ============================================================
// 问题：给定n行数字三角形，从顶部出发，每次向左下或右下走，求到达底部的最大路径和。
// 状态：dp[i][j] 表示从(i,j)出发到达底部的最大和
// 转移：dp[i][j] = max(dp[i+1][j], dp[i+1][j+1]) + a[i][j]
// 时间 O(n^2), 空间 O(n^2)
// -----------------------------------------------------------
void digitalTriangleBottomUp() {
    cout << "========== 数字三角形（从底向上递推DP）==========" << endl;

    int n;
    cout << "请输入三角形的行数 n：";
    cin >> n;

    vector<vector<int>> a(n + 2, vector<int>(n + 2, 0));
    vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));

    cout << "请输入数字三角形（每行 " << "i 个整数）：" << endl;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            cin >> a[i][j];

    // 初始化最后一行
    for (int j = 1; j <= n; j++)
        dp[n][j] = a[n][j];

    // 从底向上递推
    for (int i = n - 1; i >= 1; i--)
        for (int j = 1; j <= i; j++)
            dp[i][j] = max(dp[i+1][j], dp[i+1][j+1]) + a[i][j];

    cout << "最大路径和 = " << dp[1][1] << endl;
    cout << endl;
}

// ============================================================
// 二、数字三角形（记忆化搜索 - 自顶向下）
// ============================================================
// 用递归+缓存实现，适合理解DP思想
// -----------------------------------------------------------
const int MAXN = 1005;
int tri[MAXN][MAXN];
int memo[MAXN][MAXN];
bool visited[MAXN][MAXN];
int g_n;

int dfs(int i, int j) {
    // 非法位置
    if (j < 1 || j > i) return -1e9;
    // 到达底部
    if (i == g_n) return tri[i][j];
    // 已经计算过
    if (visited[i][j]) return memo[i][j];

    visited[i][j] = true;
    return memo[i][j] = max(dfs(i+1, j), dfs(i+1, j+1)) + tri[i][j];
}

void digitalTriangleMemo() {
    cout << "========== 数字三角形（记忆化搜索）==========" << endl;

    cout << "请输入三角形的行数 n：";
    cin >> g_n;

    cout << "请输入数字三角形：" << endl;
    for (int i = 1; i <= g_n; i++)
        for (int j = 1; j <= i; j++)
            cin >> tri[i][j];

    // 重置记忆化数组
    memset(visited, 0, sizeof(visited));

    int ans = dfs(1, 1);
    cout << "最大路径和（记忆化搜索） = " << ans << endl;
    cout << endl;
}

// ============================================================
// 三、网格路径计数（无障碍）
// ============================================================
// 问题：m*n网格，从(1,1)到(m,n)，每次只能向右或向下走，求路径数。
// 状态：dp[i][j] = 从(1,1)到(i,j)的路径数
// 转移：dp[i][j] = dp[i-1][j] + dp[i][j-1]
// -----------------------------------------------------------
const int MOD = 1e9 + 7;

void gridPathCount() {
    cout << "========== 网格路径计数（无障碍）==========" << endl;

    int m, n;
    cout << "请输入网格的行数 m 和列数 n：";
    cin >> m >> n;

    vector<vector<long long>> dp(m + 1, vector<long long>(n + 1, 0));

    // 初始化第一行和第一列
    for (int j = 1; j <= n; j++) dp[1][j] = 1;
    for (int i = 1; i <= m; i++) dp[i][1] = 1;

    // 递推
    for (int i = 2; i <= m; i++)
        for (int j = 2; j <= n; j++)
            dp[i][j] = (dp[i-1][j] + dp[i][j-1]) % MOD;

    cout << "从(1,1)到(" << m << "," << n << ")的路径数 = " << dp[m][n] << endl;
    cout << "（结果对 1e9+7 取模）" << endl;
    cout << endl;
}

// ============================================================
// 四、过河卒 - 带障碍物的路径计数
// ============================================================
// 经典CSP-J题目：棋盘上卒从(0,0)到(n,m)，马在(x,y)及控制点处不可走。
// 卒只能向右或向下走。
// -----------------------------------------------------------
void horseAndPawn() {
    cout << "========== 过河卒（带障碍物路径计数）==========" << endl;

    const int MAX = 25;
    long long dp[MAX][MAX];
    bool block[MAX][MAX];

    // 马的控制点偏移（8个方向 + 自身）
    int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2, 0};
    int dy[] = {1, 2, 2, 1, -1, -2, -2, -1, 0};

    int n, m, hx, hy;
    cout << "请输入B点坐标(n m)和马的位置(x y)：";
    cin >> n >> m >> hx >> hy;

    memset(dp, 0, sizeof(dp));
    memset(block, 0, sizeof(block));

    // 标记马的控制点
    for (int k = 0; k < 9; k++) {
        int nx = hx + dx[k];
        int ny = hy + dy[k];
        if (nx >= 0 && nx <= n && ny >= 0 && ny <= m)
            block[nx][ny] = true;
    }

    // DP初始化
    dp[0][0] = block[0][0] ? 0 : 1;

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (block[i][j]) {
                dp[i][j] = 0;
                continue;
            }
            if (i == 0 && j == 0) continue;
            if (i > 0) dp[i][j] += dp[i-1][j];
            if (j > 0) dp[i][j] += dp[i][j-1];
        }
    }

    cout << "从(0,0)到(" << n << "," << m << ")的路径数 = " << dp[n][m] << endl;
    cout << endl;
}

// ============================================================
// 主菜单
// ============================================================
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cout << "========================================" << endl;
    cout << "  CSP-J 第37课：动态规划基础" << endl;
    cout << "  程序演示合集" << endl;
    cout << "========================================" << endl;
    cout << endl;

    while (true) {
        cout << "请选择要运行的示例：" << endl;
        cout << "  1. 数字三角形（从底向上递推DP）" << endl;
        cout << "  2. 数字三角形（记忆化搜索）" << endl;
        cout << "  3. 网格路径计数（无障碍）" << endl;
        cout << "  4. 过河卒（带障碍物路径计数）" << endl;
        cout << "  0. 退出" << endl;
        cout << "请输入编号：";

        int choice;
        cin >> choice;

        if (choice == 0) {
            cout << "再见！" << endl;
            break;
        }

        switch (choice) {
            case 1: digitalTriangleBottomUp(); break;
            case 2: digitalTriangleMemo(); break;
            case 3: gridPathCount(); break;
            case 4: horseAndPawn(); break;
            default: cout << "无效选择，请重试。" << endl;
        }
    }

    return 0;
}
