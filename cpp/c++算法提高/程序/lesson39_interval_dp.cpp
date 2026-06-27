/*
 * 第39课：区间DP入门
 *
 * 本程序演示区间DP的两个经典问题：
 * 1. 石子合并（直线版）  — O(n³)
 * 2. 矩阵链乘            — O(n³)
 *
 * 核心思想：dp[i][j] 表示区间 [i, j] 的最优值，
 * 通过枚举分割点 k，将大区间分解为两个小区间来求解。
 * 枚举顺序：区间长度 → 左端点 → 分割点
 */

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

/**
 * 石子合并（直线版）
 *
 * 有 n 堆石子排成一行，每次合并相邻两堆，
 * 合并代价为两堆石子数之和，求最小总代价。
 *
 * dp[i][j] = 将第 i 堆到第 j 堆石子合并成一堆的最小代价
 * 转移方程：
 *   dp[i][j] = min(dp[i][k] + dp[k+1][j]) + sum(i, j)
 *   其中 i ≤ k < j
 *
 * @param a  石子数量数组，a[1..n] 有效
 * @return   最小总合并代价
 */
int stoneMerge(const vector<int>& a) {
    int n = a.size() - 1;  // a[0] 不使用，实际石子从 a[1] 开始
    if (n <= 1) return 0;

    // 前缀和：sum[i] = a[1] + a[2] + ... + a[i]
    vector<int> sum(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + a[i];
    }

    // dp[i][j]：合并区间 [i, j] 的最小代价
    // 初始化为 0，dp[i][i] = 0（单堆无需合并）
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    // 按区间长度从小到大枚举——这是区间DP的关键！
    for (int len = 2; len <= n; len++) {            // 区间长度
        for (int i = 1; i + len - 1 <= n; i++) {    // 左端点
            int j = i + len - 1;                     // 右端点
            dp[i][j] = INT_MAX;
            // 枚举分割点：将 [i, j] 分成 [i, k] 和 [k+1, j]
            for (int k = i; k < j; k++) {
                // 合并两个子区间的代价 = 子区间代价之和 + 本次合并代价
                // 本次合并代价 = 区间 [i, j] 的石子总数 = sum[j] - sum[i-1]
                int cost = dp[i][k] + dp[k + 1][j] + sum[j] - sum[i - 1];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }

    return dp[1][n];  // 合并全部 n 堆的最小代价
}

/**
 * 矩阵链乘
 *
 * 给定 n 个矩阵的维度序列 r[0], r[1], ..., r[n]，
 * 第 i 个矩阵为 r[i-1] 行 × r[i] 列。
 * 求通过加括号改变计算顺序后的最少标量乘法次数。
 *
 * dp[i][j] = 计算矩阵 i 到矩阵 j 相乘的最少乘法次数
 * 转移方程：
 *   dp[i][j] = min(dp[i][k] + dp[k+1][j] + r[i-1] * r[k] * r[j])
 *   其中 i ≤ k < j
 *
 * @param r  维度数组，r[0..n]，共 n+1 个元素
 * @return   最少标量乘法次数
 */
int matrixChain(const vector<int>& r) {
    int n = r.size() - 1;  // 矩阵个数
    if (n <= 1) return 0;

    // dp[i][j]：矩阵 i 到矩阵 j 的最少乘法次数
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    for (int len = 2; len <= n; len++) {            // 区间长度
        for (int i = 1; i + len - 1 <= n; i++) {    // 左端点
            int j = i + len - 1;                     // 右端点
            dp[i][j] = INT_MAX;
            // 枚举分割点 k：最后一个执行的乘法
            // 左边：[i, k] 相乘得到一个 r[i-1]×r[k] 的矩阵
            // 右边：[k+1, j] 相乘得到一个 r[k]×r[j] 的矩阵
            // 两者相乘的代价：r[i-1] * r[k] * r[j]
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k + 1][j] + r[i - 1] * r[k] * r[j];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }

    return dp[1][n];
}

/**
 * 测试主函数
 * 使用样例数据分别测试石子合并和矩阵链乘
 */
int main() {
    // ========== 测试1：石子合并 ==========
    cout << "========== 第39课：区间DP入门 ==========" << endl;
    cout << endl;
    cout << "【测试1】石子合并（直线版）" << endl;
    cout << "样例：4 堆石子，数量分别为 1, 3, 5, 2" << endl;

    // a[0] 占位，实际数据从 a[1] 开始
    vector<int> stones = {0, 1, 3, 5, 2};
    int result1 = stoneMerge(stones);
    cout << "最小合并代价 = " << result1 << endl;
    cout << "预期答案 = 22" << endl;
    cout << "结果：" << (result1 == 22 ? "✓ 通过" : "✗ 未通过") << endl;
    cout << endl;

    // ========== 测试2：矩阵链乘 ==========
    cout << "【测试2】矩阵链乘" << endl;
    cout << "样例：3 个矩阵，维度序列为 10, 100, 5, 50" << endl;
    cout << "  矩阵1: 10 × 100" << endl;
    cout << "  矩阵2: 100 × 5" << endl;
    cout << "  矩阵3: 5 × 50" << endl;

    vector<int> dims = {10, 100, 5, 50};
    int result2 = matrixChain(dims);
    cout << "最少乘法次数 = " << result2 << endl;
    cout << "预期答案 = 7500 （即 (A1×A2)×A3）" << endl;
    cout << "结果：" << (result2 == 7500 ? "✓ 通过" : "✗ 未通过") << endl;
    cout << endl;

    // ========== 附加测试 ==========
    cout << "【附加测试】石子合并（n=6）" << endl;
    cout << "石子：3, 4, 6, 5, 4, 2" << endl;
    vector<int> stones2 = {0, 3, 4, 6, 5, 4, 2};
    int result3 = stoneMerge(stones2);
    cout << "最小合并代价 = " << result3 << endl;
    cout << endl;

    cout << "【附加测试】矩阵链乘（n=4）" << endl;
    cout << "维度：5, 4, 6, 2, 7" << endl;
    vector<int> dims2 = {5, 4, 6, 2, 7};
    int result4 = matrixChain(dims2);
    cout << "最少乘法次数 = " << result4 << endl;
    cout << endl;

    cout << "========== 所有测试完成 ==========" << endl;
    return 0;
}
