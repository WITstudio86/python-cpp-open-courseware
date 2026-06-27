/*
 * Lesson 37: 背包问题（一）——01背包
 * 包含：二维DP、一维优化DP、采药问题、装箱问题
 */

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 105;    // 最大物品数
const int MAXC = 20005;  // 最大容量

int w[MAXN], v[MAXN];    // 物品重量和价值
int dp2[MAXN][MAXC];     // 二维DP数组
int dp1[MAXC];           // 一维DP数组

// ============================================================
// 1. 二维DP解法
// dp[i][j]: 考虑前 i 个物品，背包容量为 j 时的最大价值
// ============================================================
int knapsack2D(int n, int C) {
    // 初始化第 0 行：没有物品时，任何容量下价值都为 0
    for (int j = 0; j <= C; j++) {
        dp2[0][j] = 0;
    }

    // 逐个考虑每个物品
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= C; j++) {
            // 不选第 i 个物品：直接继承上一行的结果
            dp2[i][j] = dp2[i - 1][j];

            // 选第 i 个物品：前提是当前容量足够装下该物品
            if (j >= w[i]) {
                dp2[i][j] = max(dp2[i][j], dp2[i - 1][j - w[i]] + v[i]);
            }
        }
    }

    return dp2[n][C];
}

// ============================================================
// 2. 一维DP解法（空间优化）
// dp[j]: 容量为 j 时的最大价值
// 关键：j 必须反向遍历（从 C 递减到 w[i]），确保每个物品只被用一次
// 如果正序遍历，dp[j - w[i]] 可能已经被当前物品更新过，
// 相当于当前物品被使用了多次，会退化成为"完全背包"
// ============================================================
int knapsack1D(int n, int C) {
    // 初始化一维 DP 数组为 0
    memset(dp1, 0, sizeof(dp1));

    for (int i = 1; i <= n; i++) {
        // 反向遍历：从大到小更新，保证 dp[j - w[i]] 是上一轮的旧值
        for (int j = C; j >= w[i]; j--) {
            dp1[j] = max(dp1[j], dp1[j - w[i]] + v[i]);
        }
    }

    return dp1[C];
}

// ============================================================
// 3. 例题1：采药问题
// 山洞里有 n 株草药，每株需要 t 时间采摘，价值为 v
// 总共有 T 时间，问能采到的最大总价值
// 思路：标准01背包，时间=重量，价值=价值
// ============================================================
int herbPicking() {
    int T, n;
    cout << "【采药问题】" << endl;
    cout << "输入总时间 T 和草药数量 n：" << endl;
    cin >> T >> n;

    memset(dp1, 0, sizeof(dp1));

    for (int i = 1; i <= n; i++) {
        int t, val;
        cin >> t >> val;  // t=采摘时间(重量), val=价值

        // 标准 01 背包，反向遍历
        for (int j = T; j >= t; j--) {
            dp1[j] = max(dp1[j], dp1[j - t] + val);
        }
    }

    cout << "最大总价值：" << dp1[T] << endl;
    return dp1[T];
}

// ============================================================
// 4. 例题2：装箱问题
// 箱子容量 V，n 个物品各有体积 v[i]
// 求箱子剩余空间最小（即装入物品总体积最大）
// 思路：物品体积 = 重量 = 价值，求最大能装入的体积
// 答案 = V - dp[V]
// ============================================================
int binPacking() {
    int V, n;
    cout << "【装箱问题】" << endl;
    cout << "输入箱子容量 V 和物品数 n：" << endl;
    cin >> V >> n;

    memset(dp1, 0, sizeof(dp1));

    for (int i = 1; i <= n; i++) {
        int vol;
        cin >> vol;  // 物品体积，同时也是重量和价值

        // 体积 = 重量 = 价值，01 背包
        for (int j = V; j >= vol; j--) {
            dp1[j] = max(dp1[j], dp1[j - vol] + vol);
        }
    }

    int minRemain = V - dp1[V];
    cout << "最小剩余空间：" << minRemain << endl;
    return minRemain;
}

// ============================================================
// 测试主函数
// ============================================================
int main() {
    cout << "========== 第37课：背包问题（一）——01背包 ==========" << endl;
    cout << endl;

    // --- 测试1：二维DP ---
    cout << "--- 测试1：二维DP ---" << endl;
    {
        // 样例：3个物品 (w=2,v=3) (w=3,v=4) (w=4,v=5)，容量=8
        int n = 3, C = 8;
        w[1] = 2; v[1] = 3;
        w[2] = 3; v[2] = 4;
        w[3] = 4; v[3] = 5;
        int result = knapsack2D(n, C);
        cout << "物品: (2,3) (3,4) (4,5), 容量: 8" << endl;
        cout << "二维DP最大价值: " << result << " (期望: 9)" << endl;
    }
    cout << endl;

    // --- 测试2：一维DP ---
    cout << "--- 测试2：一维DP（空间优化） ---" << endl;
    {
        int n = 3, C = 8;
        w[1] = 2; v[1] = 3;
        w[2] = 3; v[2] = 4;
        w[3] = 4; v[3] = 5;
        int result = knapsack1D(n, C);
        cout << "物品: (2,3) (3,4) (4,5), 容量: 8" << endl;
        cout << "一维DP最大价值: " << result << " (期望: 9)" << endl;
    }
    cout << endl;

    // --- 测试3：采药问题 ---
    cout << "--- 测试3：采药问题 ---" << endl;
    {
        int T = 70, n = 3;
        int herbs[3][2] = { {71, 100}, {69, 1}, {1, 2} };
        memset(dp1, 0, sizeof(dp1));
        for (int i = 0; i < n; i++) {
            int t = herbs[i][0], val = herbs[i][1];
            for (int j = T; j >= t; j--) {
                dp1[j] = max(dp1[j], dp1[j - t] + val);
            }
        }
        cout << "输入: T=70, n=3, 草药=(71,100) (69,1) (1,2)" << endl;
        cout << "最大总价值: " << dp1[T] << " (期望: 3)" << endl;
    }
    cout << endl;

    // --- 测试4：装箱问题 ---
    cout << "--- 测试4：装箱问题 ---" << endl;
    {
        int V = 24, n = 6;
        int volumes[6] = { 8, 3, 12, 7, 9, 7 };
        memset(dp1, 0, sizeof(dp1));
        for (int i = 0; i < n; i++) {
            int vol = volumes[i];
            for (int j = V; j >= vol; j--) {
                dp1[j] = max(dp1[j], dp1[j - vol] + vol);
            }
        }
        cout << "输入: V=24, n=6, 物品体积=8 3 12 7 9 7" << endl;
        cout << "最大装入体积: " << dp1[V] << endl;
        cout << "最小剩余空间: " << V - dp1[V] << " (期望: 0)" << endl;
    }
    cout << endl;

    cout << "========== 测试完毕 ==========" << endl;
    return 0;
}
