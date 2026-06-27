/**
 * 第38课：背包问题（二）——完全背包
 *
 * 本文件包含：
 * 1. completeKnapsack()  —— 一维DP正向遍历，求最大价值
 * 2. coinChange()        —— 计数型完全背包（硬币找零方案数）
 * 3. comparison01Complete() —— 01背包与完全背包的遍历方向对比演示
 * 4. 例题1：完全背包
 * 5. 例题2：货币系统（货币系统）
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

/**
 * 完全背包：一维DP + 正向遍历
 *
 * dp[j] = 容量为j时能获得的最大总价值
 *
 * 【关键】正向遍历（j从w[i]到C）：
 *   正向遍历时，dp[j - w[i]] 可能已经在当前轮（当前物品i）被更新过，
 *   也就是说 dp[j - w[i]] 中可能已经包含了物品i。
 *   在此基础上再加一个物品i，就实现了「物品i可以被多次选取」的效果。
 *
 *   举例：w=3, v=5, C=6
 *     j=3: dp[3] = max(dp[3], dp[0]+5) = 5   → 拿了1个物品
 *     j=6: dp[6] = max(dp[6], dp[3]+5) = 10  → 又拿了1个（dp[3]已经包含了物品）
 *     结果：相当于拿了2个物品！
 *
 * 参数：
 *   w - 物品重量数组
 *   v - 物品价值数组
 *   C - 背包容量
 * 返回值：最大总价值
 */
int completeKnapsack(const vector<int>& w, const vector<int>& v, int C) {
    // dp[j]：容量为j时的最大价值，初始全为0
    vector<int> dp(C + 1, 0);

    // 遍历每种物品
    for (size_t i = 0; i < w.size(); i++) {
        // 【重点】正向遍历！从 w[i] 到 C
        // 这样 dp[j - w[i]] 可能已经在当前轮被更新过（包含了物品i）
        // 从而允许同一个物品被多次选取
        for (int j = w[i]; j <= C; j++) {
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
    }

    return dp[C];
}

/**
 * 硬币找零方案数 — 计数型完全背包
 *
 * 给定n种面值的硬币（每种无限个），求凑出金额amount有多少种不同的组合方式。
 *
 * dp[j] = 凑出金额j的方案数
 * dp[0] = 1（凑出0元有一种方案：什么都不选）
 * 转移方程：dp[j] += dp[j - coin[i]]  （正向遍历）
 *
 * 【注意】外层循环是硬币种类，内层循环是金额。
 *   这样保证了组合的无序性，即 {1,2,5} 和 {5,2,1} 被视为同一种方案。
 *   如果反过来（外层金额、内层硬币），则会计算排列数。
 *
 * 参数：
 *   coins  - 硬币面值数组
 *   amount - 目标金额
 * 返回值：方案总数
 */
int coinChange(const vector<int>& coins, int amount) {
    // dp[j]：凑出金额j的方案数
    vector<int> dp(amount + 1, 0);
    dp[0] = 1;  // 凑出0元有一种方案：什么都不选

    // 遍历每种硬币
    for (size_t i = 0; i < coins.size(); i++) {
        // 正向遍历金额，允许多次使用同一种硬币
        for (int j = coins[i]; j <= amount; j++) {
            dp[j] += dp[j - coins[i]];
            // 含义：凑出j元的方案数 += 凑出(j-当前硬币面值)元的方案数
            // 即「使用当前硬币后」新增的方案
        }
    }

    return dp[amount];
}

/**
 * 对比演示：01背包 vs 完全背包的遍历方向
 *
 * 直观展示为什么「正向遍历 = 可重复选取，逆向遍历 = 最多选一次」
 */
void comparison01Complete() {
    cout << "========================================" << endl;
    cout << "  01背包 vs 完全背包：遍历方向对比" << endl;
    cout << "========================================" << endl;
    cout << endl;

    cout << "┌─────────────────────────────────────────────────────┐" << endl;
    cout << "│  问题设定：1种物品，重量w=2，价值v=3，容量C=4   │" << endl;
    cout << "│  期望：                                           │" << endl;
    cout << "│    01背包 → 最多选1个，最优价值=3               │" << endl;
    cout << "│    完全背包 → 可以选2个，最优价值=6             │" << endl;
    cout << "└─────────────────────────────────────────────────────┘" << endl;
    cout << endl;

    // ========== 01背包：逆向遍历 ==========
    {
        vector<int> dp(5, 0);
        int w = 2, v = 3, C = 4;

        cout << "【01背包 — 逆向遍历 for(j=C down to w)】" << endl;
        cout << "初始dp: [0, 0, 0, 0, 0]" << endl;
        cout << endl;

        for (int j = C; j >= w; j--) {
            int oldVal = dp[j];
            dp[j] = max(dp[j], dp[j - w] + v);
            cout << "  j=" << j << ": dp[" << j << "] = max(" << oldVal
                 << ", dp[" << j - w << "]+" << v << ") = " << dp[j];
            cout << "   ← dp[" << j - w << "]=" << dp[j - w] << " 还是旧值(未包含当前物品)" << endl;
        }
        cout << endl;
        cout << "结果dp: [" << dp[0] << ", " << dp[1] << ", " << dp[2]
             << ", " << dp[3] << ", " << dp[4] << "]" << endl;
        cout << "最优价值(01背包) = " << dp[C] << " ✓ 只选了1个物品" << endl;
        cout << endl;
    }

    // ========== 完全背包：正向遍历 ==========
    {
        vector<int> dp(5, 0);
        int w = 2, v = 3, C = 4;

        cout << "【完全背包 — 正向遍历 for(j=w to C)】" << endl;
        cout << "初始dp: [0, 0, 0, 0, 0]" << endl;
        cout << endl;

        for (int j = w; j <= C; j++) {
            int oldVal = dp[j];
            dp[j] = max(dp[j], dp[j - w] + v);
            cout << "  j=" << j << ": dp[" << j << "] = max(" << oldVal
                 << ", dp[" << j - w << "]+" << v << ") = " << dp[j];
            if (j >= 2 * w) {
                cout << "   ★ dp[" << j - w << "]=" << (j >= 2 * w ? 3 : 0)
                     << " 已经被更新过！实现了重复选取！" << endl;
            } else {
                cout << endl;
            }
        }
        cout << endl;
        cout << "结果dp: [" << dp[0] << ", " << dp[1] << ", " << dp[2]
             << ", " << dp[3] << ", " << dp[4] << "]" << endl;
        cout << "最优价值(完全背包) = " << dp[C] << " ✓ 选了2个物品！" << endl;
        cout << endl;
    }

    // ========== 表格总结 ==========
    cout << "┌──────────────┬──────────────────┬──────────────────┐" << endl;
    cout << "│   对比维度   │     01背包       │     完全背包     │" << endl;
    cout << "├──────────────┼──────────────────┼──────────────────┤" << endl;
    cout << "│  遍历方向    │   逆向(j=C→w)    │   正向(j=w→C)    │" << endl;
    cout << "├──────────────┼──────────────────┼──────────────────┤" << endl;
    cout << "│  物品选取    │   最多选1次      │   可选无限次      │" << endl;
    cout << "├──────────────┼──────────────────┼──────────────────┤" << endl;
    cout << "│  转移方程    │  dp[j]=max(dp[j],│  dp[j]=max(dp[j], │" << endl;
    cout << "│              │  dp[j-w]+v)      │  dp[j-w]+v)       │" << endl;
    cout << "├──────────────┼──────────────────┼──────────────────┤" << endl;
    cout << "│  本质原因    │  dp[j-w]来自上一  │  dp[j-w]可能来自  │" << endl;
    cout << "│              │  轮（未包含物品i） │  当前轮（已含物品i）│" << endl;
    cout << "└──────────────┴──────────────────┴──────────────────┘" << endl;
    cout << endl;

    // ========== 口诀 ==========
    cout << "  记忆口诀：正向重复，逆向唯一！" << endl;
    cout << "  → 正向遍历 = 物品可重复使用（完全背包）" << endl;
    cout << "  → 逆向遍历 = 每个物品最多用一次（01背包）" << endl;
    cout << endl;
}

/**
 * 例题1：完全背包
 *
 * 题目描述：
 *   有n种物品，每种物品有无限个。第i种物品重量为w[i]，价值为v[i]。
 *   背包容量为C，求能获得的最大总价值。
 *
 * 输入格式：
 *   第一行：n C
 *   接下来n行：w v
 *
 * 样例输入：
 *   3 10
 *   2 3
 *   3 4
 *   4 5
 *
 * 样例输出：15
 */
void problem1_completeKnapsack() {
    cout << "========================================" << endl;
    cout << "  例题1：完全背包" << endl;
    cout << "========================================" << endl;
    cout << endl;

    // 样例数据
    int n = 3, C = 10;
    vector<int> w = {2, 3, 4};
    vector<int> v = {3, 4, 5};

    cout << "输入：" << endl;
    cout << "  n = " << n << ", C = " << C << endl;
    for (int i = 0; i < n; i++) {
        cout << "  物品" << (i + 1) << "：重量=" << w[i] << ", 价值=" << v[i] << endl;
    }
    cout << endl;

    // 执行完全背包算法
    vector<int> dp(C + 1, 0);

    cout << "DP过程：" << endl;
    for (int i = 0; i < n; i++) {
        cout << "  处理物品" << (i + 1) << " (w=" << w[i] << ", v=" << v[i] << "):" << endl;
        for (int j = w[i]; j <= C; j++) {
            int oldVal = dp[j];
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
            if (dp[j] != oldVal) {
                cout << "    dp[" << j << "] = " << dp[j]
                     << "  (选了物品" << (i + 1) << ")" << endl;
            }
        }
    }
    cout << endl;

    cout << "最终dp数组：" << endl;
    cout << "  ";
    for (int j = 0; j <= C; j++) {
        cout << setw(3) << j;
    }
    cout << endl;
    cout << "  ";
    for (int j = 0; j <= C; j++) {
        cout << setw(3) << dp[j];
    }
    cout << endl;
    cout << endl;

    cout << "最大总价值 = " << dp[C] << endl;
    cout << "（选5个物品1：重量=5×2=10, 价值=5×3=15）" << endl;
    cout << endl;
}

/**
 * 例题2：货币系统（硬币找零方案数）
 *
 * 题目描述：
 *   有n种面值的硬币，每种有无限个。要凑出总价值m，
 *   问有多少种不同的组合方式（硬币顺序不影响，视为同一种方案）。
 *
 * 输入格式：
 *   第一行：n m
 *   第二行：n个整数（硬币面值）
 *
 * 样例输入：
 *   3 10
 *   1 2 5
 *
 * 样例输出：10
 */
void problem2_coinSystem() {
    cout << "========================================" << endl;
    cout << "  例题2：货币系统（硬币找零方案数）" << endl;
    cout << "========================================" << endl;
    cout << endl;

    // 样例数据
    int n = 3, amount = 10;
    vector<int> coins = {1, 2, 5};

    cout << "输入：" << endl;
    cout << "  n = " << n << ", amount = " << amount << endl;
    cout << "  硬币面值：";
    for (int i = 0; i < n; i++) {
        cout << coins[i] << " ";
    }
    cout << endl;
    cout << endl;

    // 执行硬币找零算法
    vector<int> dp(amount + 1, 0);
    dp[0] = 1;  // 凑出0元有一种方案

    cout << "DP过程：" << endl;
    cout << "  初始dp[0] = 1" << endl;

    for (int i = 0; i < n; i++) {
        cout << "  考虑硬币面值 " << coins[i] << "：" << endl;
        for (int j = coins[i]; j <= amount; j++) {
            int oldVal = dp[j];
            dp[j] += dp[j - coins[i]];
            if (dp[j] != oldVal) {
                cout << "    dp[" << j << "] += dp[" << (j - coins[i]) << "] → dp[" << j << "] = " << dp[j] << endl;
            }
        }
    }
    cout << endl;

    // 打印完整dp表
    cout << "完整dp表（凑出金额j的方案数）：" << endl;
    cout << "  金额: ";
    for (int j = 0; j <= amount; j++) {
        cout << setw(4) << j;
    }
    cout << endl;
    cout << "  方案: ";
    for (int j = 0; j <= amount; j++) {
        cout << setw(4) << dp[j];
    }
    cout << endl;
    cout << endl;

    // 验证：列出所有方案（仅用于小额演示）
    cout << "凑出" << amount << "元的方案总数 = " << dp[amount] << endl;
    cout << endl;

    // 列出验证方案
    cout << "验证（手工枚举所有方案）：" << endl;
    cout << "  10 = 5+5" << endl;
    cout << "  10 = 5+2+2+1" << endl;
    cout << "  10 = 5+2+1+1+1" << endl;
    cout << "  10 = 5+1+1+1+1+1" << endl;
    cout << "  10 = 2+2+2+2+2" << endl;
    cout << "  10 = 2+2+2+2+1+1" << endl;
    cout << "  10 = 2+2+2+1+1+1+1" << endl;
    cout << "  10 = 2+2+1+1+1+1+1+1" << endl;
    cout << "  10 = 2+1+1+1+1+1+1+1+1" << endl;
    cout << "  10 = 1+1+1+1+1+1+1+1+1+1" << endl;
    cout << "  共 " << dp[amount] << " 种方案 ✓" << endl;
    cout << endl;
}

/**
 * 主函数：运行所有示例和测试
 */
int main() {
    cout << "╔══════════════════════════════════════════════╗" << endl;
    cout << "║  第38课：背包问题（二）——完全背包          ║" << endl;
    cout << "║  Lesson 38: Complete Knapsack Problem       ║" << endl;
    cout << "╚══════════════════════════════════════════════╝" << endl;
    cout << endl;

    // ========== 1. 基本完全背包测试 ==========
    cout << ">>> 测试1：基本完全背包" << endl;
    cout << "----------------------------------------" << endl;
    {
        vector<int> w = {2, 3, 4};
        vector<int> v = {3, 4, 5};
        int C = 10;
        int result = completeKnapsack(w, v, C);
        cout << "物品：(2,3), (3,4), (4,5), 容量=" << C << endl;
        cout << "最大价值 = " << result;
        if (result == 15) {
            cout << " ✓ 正确" << endl;
        } else {
            cout << " ✗ 期望15" << endl;
        }
    }
    cout << endl;

    // ========== 2. 硬币找零测试 ==========
    cout << ">>> 测试2：硬币找零（计数型完全背包）" << endl;
    cout << "----------------------------------------" << endl;
    {
        vector<int> coins = {1, 2, 5};
        int amount = 10;
        int result = coinChange(coins, amount);
        cout << "硬币面值：1, 2, 5, 目标金额=" << amount << endl;
        cout << "方案数 = " << result;
        if (result == 10) {
            cout << " ✓ 正确" << endl;
        } else {
            cout << " ✗ 期望10" << endl;
        }
    }
    {
        // 额外测试：小额
        vector<int> coins = {1, 2, 5};
        int amount = 5;
        int result = coinChange(coins, amount);
        cout << "硬币面值：1, 2, 5, 目标金额=" << amount << endl;
        cout << "方案数 = " << result;
        if (result == 4) {
            cout << " ✓ 正确 (5=5, 5=2+2+1, 5=2+1+1+1, 5=1+1+1+1+1)" << endl;
        } else {
            cout << " ✗ 期望4" << endl;
        }
    }
    {
        // 额外测试：只有一种硬币
        vector<int> coins = {3};
        int amount = 9;
        int result = coinChange(coins, amount);
        cout << "硬币面值：3, 目标金额=" << amount << endl;
        cout << "方案数 = " << result;
        if (result == 1) {
            cout << " ✓ 正确 (只有3+3+3一种)" << endl;
        } else {
            cout << " ✗ 期望1" << endl;
        }
    }
    cout << endl;

    // ========== 3. 遍历方向对比演示 ==========
    cout << endl;
    comparison01Complete();

    // ========== 4. 例题1演示 ==========
    cout << endl;
    problem1_completeKnapsack();

    // ========== 5. 例题2演示 ==========
    cout << endl;
    problem2_coinSystem();

    cout << "========================================" << endl;
    cout << "  本课总结" << endl;
    cout << "========================================" << endl;
    cout << "  1. 完全背包使用正向遍历（j从w到C），实现物品可重复选取" << endl;
    cout << "  2. 01背包使用逆向遍历（j从C到w），保证物品最多选一次" << endl;
    cout << "  3. 计数型完全背包：dp[j] += dp[j-coin[i]]，dp[0]=1" << endl;
    cout << "  4. 记忆口诀：正向重复，逆向唯一！" << endl;
    cout << "========================================" << endl;
    cout << endl;

    return 0;
}
