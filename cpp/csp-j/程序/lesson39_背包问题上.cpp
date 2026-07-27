/**
 * lesson39_背包问题上.cpp
 * CSP-J 备考课程 第39课
 *
 * 包含内容：
 * 1. 01背包 二维DP演示（输出DP表格）
 * 2. 01背包 一维DP（倒序遍历）
 * 3. 01背包 一维DP的正确 vs 错误对比（正序 vs 倒序）
 * 4. 完全背包 一维DP（正序遍历）
 * 5. 恰好装满的01背包（-INF初始化）
 */

#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <iomanip>
using namespace std;

// ============================================================
// 一、01背包 二维DP演示（小数据量，输出DP表格）
// ============================================================
// 状态：dp[i][j] = 前i件物品，容量j时的最大价值
// 转移：dp[i][j] = max(dp[i-1][j], dp[i-1][j-w[i]] + v[i])
// -----------------------------------------------------------
void knapsack01_2d_demo() {
    cout << "========== 01背包 二维DP演示 ==========" << endl;
    cout << endl;
    cout << "（演示小数据量，会输出完整的DP表格）" << endl;
    cout << endl;

    int N, W;
    cout << "请输入物品数量 N（建议≤5）和背包容量 W（建议≤10）：";
    cin >> N >> W;

    vector<int> w(N + 1), v(N + 1);
    cout << "请依次输入每件物品的重量和价值：" << endl;
    for (int i = 1; i <= N; i++) {
        cout << "  物品" << i << "：";
        cin >> w[i] >> v[i];
    }

    // 二维DP
    vector<vector<int>> dp(N + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= W; j++) {
            dp[i][j] = dp[i-1][j];
            if (j >= w[i])
                dp[i][j] = max(dp[i][j], dp[i-1][j-w[i]] + v[i]);
        }
    }

    // 输出DP表格
    cout << endl;
    cout << "========== DP表格 ==========" << endl;
    cout << "（行 = 前i件物品，列 = 容量j）" << endl;
    cout << endl;

    // 表头
    cout << "  i\\j ";
    for (int j = 0; j <= W; j++)
        cout << setw(4) << j;
    cout << endl;

    // 分隔线
    cout << "-----";
    for (int j = 0; j <= W; j++)
        cout << "----";
    cout << endl;

    // 数据行
    for (int i = 1; i <= N; i++) {
        cout << setw(4) << i << " |";
        for (int j = 0; j <= W; j++)
            cout << setw(4) << dp[i][j];
        cout << endl;
    }

    cout << endl;
    cout << "最大总价值 = " << dp[N][W] << endl;

    // 回溯输出选择的物品
    cout << "选择的物品：";
    int j = W;
    vector<int> chosen;
    for (int i = N; i >= 1; i--) {
        if (j >= w[i] && dp[i][j] == dp[i-1][j-w[i]] + v[i]) {
            chosen.push_back(i);
            j -= w[i];
        }
    }
    if (chosen.empty()) {
        cout << "无";
    } else {
        reverse(chosen.begin(), chosen.end());
        for (size_t k = 0; k < chosen.size(); k++) {
            if (k > 0) cout << ", ";
            cout << "物品" << chosen[k]
                 << "(重量" << w[chosen[k]] << ",价值" << v[chosen[k]] << ")";
        }
    }
    cout << endl << endl;
}

// ============================================================
// 二、01背包 一维DP（倒序遍历，标准写法）
// ============================================================
// 核心：dp[j] = max(dp[j], dp[j-w[i]] + v[i])
// 关键：必须倒序遍历容量 — "零一倒着走"
// -----------------------------------------------------------
void knapsack01_1d() {
    cout << "========== 01背包 一维DP（倒序遍历）==========" << endl;
    cout << endl;

    int N, W;
    cout << "请输入物品数量 N：";
    cin >> N;
    cout << "请输入背包容量 W：";
    cin >> W;

    vector<int> w(N + 1), v(N + 1);
    cout << "请依次输入每件物品的重量和价值：" << endl;
    for (int i = 1; i <= N; i++) {
        cout << "  物品" << i << "：";
        cin >> w[i] >> v[i];
    }

    vector<int> dp(W + 1, 0);

    cout << endl;
    cout << "算法执行过程（每处理一件物品后输出dp数组）：" << endl;
    cout << endl;

    for (int i = 1; i <= N; i++) {
        for (int j = W; j >= w[i]; j--) {
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
        // 输出当前物品处理后的dp数组
        cout << "加入物品" << i << "（重量" << w[i] << ",价值" << v[i] << "）后：";
        for (int j = 0; j <= W; j++) {
            if (j % 5 == 0) cout << endl << "  ";
            cout << "dp[" << setw(2) << j << "]=" << setw(3) << dp[j] << "  ";
        }
        cout << endl << endl;
    }

    cout << "最大总价值 = " << dp[W] << endl;
    cout << endl;
}

// ============================================================
// 三、01背包 正序 vs 倒序 对比实验
// ============================================================
// 目的：直观展示正序遍历为什么会导致物品重复使用
// -----------------------------------------------------------
void knapsack01_order_comparison() {
    cout << "========== 正序 vs 倒序 对比实验 ==========" << endl;
    cout << endl;
    cout << "使用固定数据：3件物品，容量=8" << endl;
    cout << "  物品1：重量=3，价值=4" << endl;
    cout << "  物品2：重量=4，价值=5" << endl;
    cout << "  物品3：重量=5，价值=6" << endl;
    cout << endl;

    const int N = 3, W = 8;
    int w[] = {0, 3, 4, 5};
    int v[] = {0, 4, 5, 6};

    // --- 正序遍历（错误）---
    vector<int> dp_wrong(W + 1, 0);
    cout << "【错误示范：正序遍历（会变成完全背包）】" << endl;
    for (int i = 1; i <= N; i++) {
        for (int j = w[i]; j <= W; j++) {
            dp_wrong[j] = max(dp_wrong[j], dp_wrong[j - w[i]] + v[i]);
        }
        cout << "  处理物品" << i << "后：";
        for (int j = 0; j <= W; j++)
            cout << setw(3) << dp_wrong[j];
        cout << endl;
    }
    cout << "  正序遍历结果 dp[" << W << "] = " << dp_wrong[W]
         << "  ← 错误！物品被重复使用" << endl;
    cout << endl;

    // --- 倒序遍历（正确）---
    vector<int> dp_right(W + 1, 0);
    cout << "【正确示范：倒序遍历（标准01背包）】" << endl;
    for (int i = 1; i <= N; i++) {
        for (int j = W; j >= w[i]; j--) {
            dp_right[j] = max(dp_right[j], dp_right[j - w[i]] + v[i]);
        }
        cout << "  处理物品" << i << "后：";
        for (int j = 0; j <= W; j++)
            cout << setw(3) << dp_right[j];
        cout << endl;
    }
    cout << "  倒序遍历结果 dp[" << W << "] = " << dp_right[W]
         << "  ← 正确！" << endl;
    cout << endl;

    cout << "对比结论：正序遍历使物品1被使用了 ceil(8/3)≈3 次，" << endl;
    cout << "          而01背包要求物品只能选0或1次。" << endl;
    cout << "          这就是为什么必须倒序遍历！" << endl;
    cout << endl;
}

// ============================================================
// 四、完全背包 一维DP（正序遍历）
// ============================================================
// 核心：dp[j] = max(dp[j], dp[j-w[i]] + v[i])
// 关键：正序遍历容量 — "完全正着走"
// -----------------------------------------------------------
void knapsack_complete() {
    cout << "========== 完全背包 一维DP（正序遍历）==========" << endl;
    cout << endl;

    int N, W;
    cout << "请输入物品数量 N：";
    cin >> N;
    cout << "请输入背包容量 W：";
    cin >> W;

    vector<int> w(N + 1), v(N + 1);
    cout << "请依次输入每件物品的重量和价值：" << endl;
    for (int i = 1; i <= N; i++) {
        cout << "  物品" << i << "：";
        cin >> w[i] >> v[i];
    }

    vector<int> dp(W + 1, 0);

    cout << endl;
    cout << "算法执行过程（每处理一件物品后输出dp数组）：" << endl;
    cout << endl;

    for (int i = 1; i <= N; i++) {
        // 正序遍历 — 关键！
        for (int j = w[i]; j <= W; j++) {
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
        // 输出当前物品处理后的dp数组
        cout << "加入物品" << i << "（重量" << w[i] << ",价值" << v[i]
             << "，无限次）后：";
        for (int j = 0; j <= W; j++) {
            if (j % 5 == 0) cout << endl << "  ";
            cout << "dp[" << setw(2) << j << "]=" << setw(3) << dp[j] << "  ";
        }
        cout << endl << endl;
    }

    cout << "最大总价值 = " << dp[W] << endl;
    cout << endl;

    // 解释
    cout << "提示：完全背包的正序遍历让每件物品可以被使用多次。" << endl;
    cout << "      比如容量为j时，dp[j-w[i]]可能已经包含了物品i，" << endl;
    cout << "      从而允许物品i被反复使用。" << endl;
    cout << endl;
}

// ============================================================
// 五、恰好装满的01背包
// ============================================================
// 初始化：dp[0] = 0，其余 = -INF
// 含义：只有"恰好装满容量j"的状态可达，不可达为-INF
// -----------------------------------------------------------
void knapsack01_exact_full() {
    cout << "========== 恰好装满的01背包 ==========" << endl;
    cout << endl;

    int N, W;
    cout << "请输入物品数量 N：";
    cin >> N;
    cout << "请输入背包容量 W：";
    cin >> W;

    vector<int> w(N + 1), v(N + 1);
    cout << "请依次输入每件物品的重量和价值：" << endl;
    for (int i = 1; i <= N; i++) {
        cout << "  物品" << i << "：";
        cin >> w[i] >> v[i];
    }

    const int INF = 0x3f3f3f3f;

    // 初始化：dp[0]=0，其余=-INF
    vector<int> dp(W + 1, -INF);
    dp[0] = 0;

    cout << endl;
    cout << "初始化状态：" << endl;
    cout << "  dp[0] = 0（容量0恰好装满，价值0）" << endl;
    cout << "  dp[1.." << W << "] = -INF（不可达）" << endl;
    cout << endl;

    for (int i = 1; i <= N; i++) {
        for (int j = W; j >= w[i]; j--) {
            // 注意：dp[j-w[i]]不为-INF才转移（否则无意义）
            if (dp[j - w[i]] != -INF)
                dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
        // 输出dp数组
        cout << "处理物品" << i << "（重量" << w[i] << ",价值" << v[i] << "）后：";
        for (int j = 0; j <= W; j++) {
            if (j % 5 == 0) cout << endl << "  ";
            if (dp[j] == -INF)
                cout << "dp[" << setw(2) << j << "]= -∞  ";
            else
                cout << "dp[" << setw(2) << j << "]=" << setw(3) << dp[j] << "  ";
        }
        cout << endl << endl;
    }

    if (dp[W] < 0)
        cout << "结果：无法恰好装满容量 " << W << " 的背包！" << endl;
    else
        cout << "恰好装满容量 " << W << " 的最大价值 = " << dp[W] << endl;
    cout << endl;
}

// ============================================================
// 六、采药（01背包固定样例）
// ============================================================
void demo_herbs() {
    cout << "========== 采药（01背包样例）==========" << endl;
    cout << "样例：M=70, N=3" << endl;
    cout << "  草药1: t=71 v=100" << endl;
    cout << "  草药2: t=69 v=1" << endl;
    cout << "  草药3: t=1  v=2" << endl;
    cout << endl;

    const int M = 70, N = 3;
    int t[] = {0, 71, 69, 1};
    int v[] = {0, 100, 1, 2};
    int dp[1005] = {0};

    for (int i = 1; i <= N; i++) {
        for (int j = M; j >= t[i]; j--) {
            dp[j] = max(dp[j], dp[j - t[i]] + v[i]);
        }
    }
    cout << "最大价值 = " << dp[M] << "（期望 3）" << endl;
    cout << "解释：草药1超时不能采；采 2+3 得 1+2=3。" << endl << endl;
}

// ============================================================
// 七、货币系统（完全背包方案数样例）
// ============================================================
void demo_coin_ways() {
    cout << "========== 货币系统（完全背包方案数）==========" << endl;
    cout << "面值 1,2,5 组成 10 的方案数" << endl;

    int a[] = {0, 1, 2, 5};
    int n = 3, m = 10;
    long long dp[10005] = {0};
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = a[i]; j <= m; j++) {
            dp[j] += dp[j - a[i]];
        }
    }
    cout << "方案数 = " << dp[m] << "（期望 10）" << endl;
    cout << "要点：外层物品、内层金额 → 组合数；dp[0]=1；正序。" << endl << endl;
}

// ============================================================
// 八、01背包 vs 完全背包 核心对比
// ============================================================
void comparison_summary() {
    cout << "========== 01背包 vs 完全背包 核心对比 ==========" << endl;
    cout << endl;
    cout << "+------------------+---------------------+---------------------+" << endl;
    cout << "|     对比项       |      01背包         |      完全背包       |" << endl;
    cout << "+------------------+---------------------+---------------------+" << endl;
    cout << "| 物品选择         | 最多选1次           | 可选无限次          |" << endl;
    cout << "| 二维转移         | dp[i-1][j-w[i]]+v[i]| dp[i][j-w[i]]+v[i]  |" << endl;
    cout << "| 一维遍历方向     | 倒序(j从W到w[i])   | 正序(j从w[i]到W)   |" << endl;
    cout << "| dp[j]依赖        | 上一轮的旧值        | 本轮已更新的值      |" << endl;
    cout << "| 初始化(最大价值) | dp全为0             | dp全为0            |" << endl;
    cout << "| 初始化(恰好满)   | dp[0]=0,余=-INF     | dp[0]=0,余=-INF    |" << endl;
    cout << "| 记忆口诀         | 零一倒着走          | 完全正着走          |" << endl;
    cout << "+------------------+---------------------+---------------------+" << endl;
    cout << endl;
    cout << "核心记忆：" << endl;
    cout << "  - 01背包倒序：防止物品i被本轮更新污染 → 保证只选0或1次" << endl;
    cout << "  - 完全背包正序：允许物品i被本轮更新 → 实现无限次选择" << endl;
    cout << endl;
}

// ============================================================
// 主菜单
// ============================================================
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cout << "========================================" << endl;
    cout << "  CSP-J 第39课：背包问题（上）" << endl;
    cout << "  程序演示合集" << endl;
    cout << "========================================" << endl;
    cout << endl;

    while (true) {
        cout << "请选择要运行的示例：" << endl;
        cout << "  1. 01背包 二维DP演示（输出DP表格）" << endl;
        cout << "  2. 01背包 一维DP（倒序遍历，标准写法）" << endl;
        cout << "  3. 正序 vs 倒序 对比实验（直观理解原理）" << endl;
        cout << "  4. 完全背包 一维DP（正序遍历）" << endl;
        cout << "  5. 恰好装满的01背包（-INF初始化）" << endl;
        cout << "  6. 采药固定样例（01）" << endl;
        cout << "  7. 货币系统固定样例（完全-方案数）" << endl;
        cout << "  8. 01背包 vs 完全背包 核心对比表" << endl;
        cout << "  0. 退出" << endl;
        cout << "请输入编号：";

        int choice;
        cin >> choice;
        cin.ignore();  // 清除换行符

        if (choice == 0) {
            cout << "再见！记住口诀：零一倒着走，完全正着走！" << endl;
            break;
        }

        cout << endl;

        switch (choice) {
            case 1: knapsack01_2d_demo(); break;
            case 2: knapsack01_1d(); break;
            case 3: knapsack01_order_comparison(); break;
            case 4: knapsack_complete(); break;
            case 5: knapsack01_exact_full(); break;
            case 6: demo_herbs(); break;
            case 7: demo_coin_ways(); break;
            case 8: comparison_summary(); break;
            default: cout << "无效选择，请重试。" << endl << endl;
        }
    }

    return 0;
}
