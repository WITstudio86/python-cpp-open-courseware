/**
 * lesson30_multi_group_knapsack.cpp
 * 第30课：多重背包与分组背包
 *
 * 包含以下实现：
 * 1. 多重背包 - 朴素实现 O(V * Σc[i])
 * 2. 多重背包 - 二进制拆分优化 O(V * Σ log c[i])
 * 3. 多重背包 - 单调队列优化 O(V * n)
 * 4. 分组背包 - 标准实现
 * 5. 真题1：宝物筛选（多重背包模板题）
 * 6. 真题2：选拔队员（分组背包题）
 *
 * 编译：g++ -std=c++17 -O2 lesson30_multi_group_knapsack.cpp -o lesson30
 * 运行：./lesson30
 */

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// 1. 多重背包 - 朴素实现 O(V * Σc[i])
// 逐件物品枚举 k 从 0 到 c[i]，逐个更新 dp
// 仅用于对比, 实际比赛不建议使用
// ============================================================
int knapsack_multi_naive(int n, int V, const vector<int>& w,
                          const vector<int>& v, const vector<int>& c) {
    vector<int> dp(V + 1, 0);
    for (int i = 0; i < n; i++) {
        // 容量逆序 —— 因为本质上是 01 背包（每个 k 件是一个选择）
        for (int j = V; j >= w[i]; j--) {
            for (int k = 1; k <= c[i] && k * w[i] <= j; k++) {
                dp[j] = max(dp[j], dp[j - k * w[i]] + k * v[i]);
            }
        }
    }
    return dp[V];
}

// ============================================================
// 2. 多重背包 - 二进制拆分优化 O(V * Σ log c[i])
// 核心：将 c[i] 件拆分为 1, 2, 4, ..., 2^k, r 件打包物品
// 这些打包物品可以组合出 0~c[i] 之间的任意数量
// 拆分后转化为 01 背包问题求解
// ============================================================
int knapsack_multi_binary(int n, int V, const vector<int>& w,
                           const vector<int>& v, const vector<int>& c) {
    vector<int> dp(V + 1, 0);

    for (int i = 0; i < n; i++) {
        int weight = w[i], value = v[i], cnt = c[i];

        // 可行性剪枝：如果总重量 ≥ V，转化为完全背包
        if ((long long)cnt * weight >= V) {
            for (int j = weight; j <= V; j++) {
                dp[j] = max(dp[j], dp[j - weight] + value);
            }
            continue;
        }

        // 二进制拆分：将 cnt 拆成 1, 2, 4, 8, ..., 2^k, r
        // k 从 1 开始，每次翻倍，直到超过剩余数量
        for (int k = 1; k <= cnt; k <<= 1) {
            // 打包物品：(k * weight, k * value)
            int pack_w = weight * k;
            int pack_v = value * k;
            // 01 背包 —— 容量逆序
            for (int j = V; j >= pack_w; j--) {
                dp[j] = max(dp[j], dp[j - pack_w] + pack_v);
            }
            cnt -= k; // 减去已拆分的数量
        }
        // 处理余数 r
        if (cnt > 0) {
            int pack_w = weight * cnt;
            int pack_v = value * cnt;
            for (int j = V; j >= pack_w; j--) {
                dp[j] = max(dp[j], dp[j - pack_w] + pack_v);
            }
        }
    }
    return dp[V];
}

// ============================================================
// 3. 多重背包 - 单调队列优化 O(V * n)
//
// 核心思想：
// 1. 按 j mod w[i] 分组，每组内状态转移只依赖同组前面的状态
// 2. 每组维护一个单调递减队列，在滑动窗口内求最大值
//
// 状态转移：dp[j] = max{ dp[j - k*w] + k*v }  (0 <= k <= c, k*w <= j)
// 设 j = r + x*w，其中 r = j % w, x = j / w
// 则 dp[r + x*w] = max_{x-c <= t <= x} { g[r + t*w] - t*v } + x*v
//
// g[] 是上一轮 dp 的拷贝，保证物品只被使用一次
// 候选值 candidate[t] = g[r + t*w] - t*v
// 单调队列维护 candidate 的递减序列，队首是窗口内最大值
// ============================================================
int knapsack_multi_monoqueue(int n, int V, const vector<int>& w,
                              const vector<int>& v, const vector<int>& c) {
    vector<int> dp(V + 1, 0);
    vector<int> g(V + 1, 0); // 保存上一轮 dp 状态

    for (int i = 0; i < n; i++) {
        int weight = w[i], value = v[i], cnt = c[i];

        // 保存上一轮状态
        g = dp;

        // 按余数 r 分组 (0 <= r < weight)
        for (int r = 0; r < weight; r++) {
            deque<int> q; // 单调递减队列，存储下标 x (即 j/w)
            // 遍历同余序列: r, r+w, r+2w, ..., r+x*w <= V
            for (int x = 0; r + x * weight <= V; x++) {
                int j = r + x * weight; // 当前容量

                // 计算候选值: candidate[t] = g[r + t*w] - t * value
                // 对于当前 x，candidate[x] = g[j] - x * value
                int cur_candidate = g[j] - x * value;

                // 维护队列单调递减：弹出队尾所有 ≤ cur_candidate 的元素
                // 因为它们永远不会成为窗口内的最大值
                while (!q.empty()) {
                    int t_back = q.back();
                    int back_candidate = g[r + t_back * weight] - t_back * value;
                    if (back_candidate <= cur_candidate) {
                        q.pop_back();
                    } else {
                        break;
                    }
                }
                q.push_back(x);

                // 弹出窗口外的元素：窗口范围 [x - cnt, x]
                while (!q.empty() && q.front() < x - cnt) {
                    q.pop_front();
                }

                // 队首是窗口内最大 candidate 对应的下标
                int best_t = q.front();
                // dp[j] = max_candidate + x * value
                //        = (g[r + best_t*w] - best_t*value) + x*value
                dp[j] = g[r + best_t * weight] + (x - best_t) * value;
            }
        }
    }
    return dp[V];
}

// ============================================================
// 4. 分组背包 - 标准实现
// 问题：有 n 组物品，每组最多选一件，求最大价值
//
// 循环顺序说明：
//   外层：枚举组 i
//   中层：逆序枚举容量 j = V .. 0
//   内层：枚举组内物品 k
//
// 为什么中层必须逆序？
//   如果正序，当前组物品 k 更新 dp[j] 后，
//   更大的 j' 处可能再次使用同组物品（因为 dp[j' - w[k']] 已含物品 k），
//   导致同组选多件，违反约束。
//   逆序保证每个 dp[j] 只用上一组的状态来更新。
// ============================================================
int knapsack_group(int n, int V,
                    const vector<vector<pair<int, int>>>& groups) {
    // groups[i] = vector of (weight, value) for group i
    vector<int> dp(V + 1, 0);

    for (int i = 0; i < n; i++) {                     // 外层：枚举组
        for (int j = V; j >= 0; j--) {                // 中层：容量逆序
            for (auto& item : groups[i]) {            // 内层：枚举组内物品
                int w = item.first, v = item.second;
                if (j >= w) {
                    dp[j] = max(dp[j], dp[j - w] + v);
                }
            }
        }
    }
    return dp[V];
}

// ============================================================
// 5. 真题1：宝物筛选（多重背包模板题 —— 二进制拆分版本）
// 题目来源：Luogu P1776
// N 种宝物，容量 V，每种有重量 w、价值 v、数量 c
// 数据范围：N <= 100, V <= 40000, c <= 100
// ============================================================
void solve_treasure_filter() {
    cout << "========== 真题1：宝物筛选（多重背包） ==========" << endl;
    int n, V;
    cin >> n >> V;
    vector<int> w(n), v(n), c(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i] >> w[i] >> c[i]; // 注意输入顺序：价值 重量 数量
    }
    int ans = knapsack_multi_binary(n, V, w, v, c);
    cout << ans << endl;
}

// ============================================================
// 6. 真题2：选拔队员（分组背包题）
// N 个班级，预算 V，每班若干候选人（费用 w, 能力 v），每班最多选1人
// ============================================================
void solve_team_selection() {
    cout << "========== 真题2：选拔队员（分组背包） ==========" << endl;
    int n, V;
    cin >> n >> V;
    vector<vector<pair<int, int>>> groups(n);
    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        groups[i].resize(m);
        for (int j = 0; j < m; j++) {
            int w, v;
            cin >> w >> v;
            groups[i][j] = {w, v};
        }
    }
    int ans = knapsack_group(n, V, groups);
    cout << ans << endl;
}

// ============================================================
// 7. 自测函数：用随机数据验证三种多重背包实现的一致性
// ============================================================
void self_test() {
    cout << "========== 自测：验证三种多重背包实现 ==========" << endl;

    // 小数据随机测试
    srand(time(0));
    int test_count = 100;
    bool all_pass = true;

    for (int t = 0; t < test_count; t++) {
        int n = rand() % 5 + 1;       // 1~5 种物品
        int V = rand() % 50 + 1;      // 容量 1~50
        vector<int> w(n), v(n), c(n);
        for (int i = 0; i < n; i++) {
            w[i] = rand() % 10 + 1;   // 重量 1~10
            v[i] = rand() % 20 + 1;   // 价值 1~20
            c[i] = rand() % 5 + 1;    // 数量 1~5
        }

        int ans1 = knapsack_multi_naive(n, V, w, v, c);
        int ans2 = knapsack_multi_binary(n, V, w, v, c);
        int ans3 = knapsack_multi_monoqueue(n, V, w, v, c);

        if (ans1 != ans2 || ans2 != ans3) {
            cout << "测试 " << t + 1 << " 失败!" << endl;
            cout << "  n=" << n << " V=" << V << endl;
            cout << "  朴素=" << ans1 << " 二进制=" << ans2
                 << " 单调队列=" << ans3 << endl;
            all_pass = false;
            break;
        }
    }

    if (all_pass) {
        cout << "全部 " << test_count << " 组随机测试通过！" << endl;
    }
}

// ============================================================
// 8. 演示：小规模手动测试，打印 dp 过程
// ============================================================
void demo() {
    cout << "\n========== 演示：多重背包各实现详细输出 ==========" << endl;

    int n = 3, V = 15;
    vector<int> w = {3, 4, 5};
    vector<int> v = {2, 3, 4};
    vector<int> c = {4, 3, 2};

    cout << "物品数量 n = " << n << ", 容量 V = " << V << endl;
    for (int i = 0; i < n; i++) {
        cout << "  物品" << i + 1 << ": 重量=" << w[i]
             << ", 价值=" << v[i] << ", 数量=" << c[i] << endl;
    }

    cout << "\n朴素实现结果:    " << knapsack_multi_naive(n, V, w, v, c) << endl;
    cout << "二进制拆分结果:  " << knapsack_multi_binary(n, V, w, v, c) << endl;
    cout << "单调队列结果:    " << knapsack_multi_monoqueue(n, V, w, v, c) << endl;

    cout << "\n分组背包演示：" << endl;
    // 2组物品：每组2件
    // 组0: (w=2,v=3), (w=3,v=5)
    // 组1: (w=4,v=6), (w=5,v=9)
    vector<vector<pair<int, int>>> groups = {
        {{2, 3}, {3, 5}},
        {{4, 6}, {5, 9}}
    };
    int group_ans = knapsack_group(2, 10, groups);
    cout << "  2组物品, 容量10, 最大价值 = " << group_ans << endl;
    // 预期：组0选(3,5) + 组1选(5,9) = 14，或组0选(2,3)+组1选(5,9)=12
}

// ============================================================
// main 函数：提供交互式菜单
// ============================================================
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "==================================================" << endl;
    cout << "  第30课：多重背包与分组背包 —— 代码演示" << endl;
    cout << "==================================================" << endl;
    cout << "请选择功能：" << endl;
    cout << "  1 - 自测（随机数据验证三种多重背包实现）" << endl;
    cout << "  2 - 演示（小规模手动测试）" << endl;
    cout << "  3 - 真题1：宝物筛选（输入测试数据）" << endl;
    cout << "  4 - 真题2：选拔队员（输入测试数据）" << endl;
    cout << "请输入选项 (1-4): ";

    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            self_test();
            break;
        case 2:
            demo();
            break;
        case 3:
            cout << "请输入数据（格式：N V，然后每行 v w c）：" << endl;
            solve_treasure_filter();
            break;
        case 4:
            cout << "请输入数据（格式：N V，然后每组 m 及 m行 w v）：" << endl;
            solve_team_selection();
            break;
        default:
            cout << "无效选项，执行默认自测和演示。" << endl;
            self_test();
            demo();
            break;
    }

    return 0;
}
