/**
 * lesson40_背包问题下与区间DP.cpp
 * CSP-J 备考课程 第40课
 *
 * 包含内容：
 * 1. 多重背包 二进制优化演示（展示拆分过程）
 * 2. 多重背包 朴素做法对比
 * 3. 分组背包 正确写法演示
 * 4. 分组背包 循环顺序对比实验（正确 vs 错误）
 * 5. 石子合并 区间DP演示（输出DP表格）
 * 6. 区间DP 通用框架总结
 */

#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <iomanip>
using namespace std;

// ============================================================
// 一、多重背包 二进制优化演示
// ============================================================
// 核心：将 c[i] 个物品按 1,2,4,8,... 拆分，转化为01背包
// 口诀："多重二进制拆"
// -----------------------------------------------------------
void multiple_knapsack_binary() {
    cout << "========== 多重背包 二进制优化演示 ==========" << endl;
    cout << endl;
    cout << "（展示二进制拆分过程，然后01背包求解）" << endl;
    cout << endl;

    int N, W;
    cout << "请输入物品种类数 N 和背包容量 W：";
    cin >> N >> W;

    vector<int> weight(N + 1), value(N + 1), limit(N + 1);
    cout << "请依次输入每种物品的 重量 价值 数量上限：" << endl;
    for (int i = 1; i <= N; i++) {
        cout << "  物品" << i << "：";
        cin >> weight[i] >> value[i] >> limit[i];
    }

    // 二进制拆分
    const int MAX_ITEMS = N * 15;  // log2(10000) ≈ 14
    vector<int> new_w(MAX_ITEMS + 1), new_v(MAX_ITEMS + 1);
    int cnt = 0;

    cout << endl;
    cout << "========== 二进制拆分过程 ==========" << endl;
    for (int i = 1; i <= N; i++) {
        int w = weight[i], v = value[i], c = limit[i];
        cout << "物品" << i << "（重量=" << w << ", 价值=" << v
             << ", 数量=" << c << "）→ 拆分为：";

        vector<string> parts;
        for (int k = 1; k <= c; k <<= 1) {
            new_w[++cnt] = k * w;
            new_v[cnt] = k * v;
            c -= k;
            parts.push_back(to_string(k) + "个(" + to_string(k * w) + "kg, " + to_string(k * v) + "元)");
        }
        if (c > 0) {
            new_w[++cnt] = c * w;
            new_v[cnt] = c * v;
            parts.push_back(to_string(c) + "个(" + to_string(c * w) + "kg, " + to_string(c * v) + "元)");
        }
        for (size_t p = 0; p < parts.size(); p++) {
            if (p > 0) cout << " + ";
            cout << parts[p];
        }
        cout << endl;
    }
    cout << "拆分后共 " << cnt << " 个打包物品" << endl;
    cout << endl;

    // 01背包求解
    vector<int> dp(W + 1, 0);
    for (int i = 1; i <= cnt; i++) {
        for (int j = W; j >= new_w[i]; j--) {
            dp[j] = max(dp[j], dp[j - new_w[i]] + new_v[i]);
        }
    }

    cout << "最大总价值 = " << dp[W] << endl;
    cout << endl;
    cout << "复杂度分析：原始物品数=" << N
         << "，拆分后物品数=" << cnt
         << "，每件O(log c[i])" << endl;
    cout << endl;
}

// ============================================================
// 二、多重背包 朴素做法 vs 二进制优化 对比
// ============================================================
// 目的：直观展示朴素做法的低效与二进制优化的高效
// -----------------------------------------------------------
void multiple_knapsack_compare() {
    cout << "========== 朴素做法 vs 二进制优化 对比 ==========" << endl;
    cout << endl;
    cout << "使用固定数据：2种物品，容量=15" << endl;
    cout << "  物品1：重量=3，价值=2，数量=7" << endl;
    cout << "  物品2：重量=5，价值=4，数量=4" << endl;
    cout << endl;

    const int N = 2, W = 15;
    int w[] = {0, 3, 5};
    int v[] = {0, 2, 4};
    int c[] = {0, 7, 4};

    // --- 朴素做法（三重循环）---
    cout << "【朴素做法：三重循环 O(N*W*max(c[i]))】" << endl;
    vector<int> dp_naive(W + 1, 0);
    for (int i = 1; i <= N; i++) {
        for (int j = W; j >= 0; j--) {
            for (int k = 0; k <= c[i] && k * w[i] <= j; k++) {
                dp_naive[j] = max(dp_naive[j], dp_naive[j - k * w[i]] + k * v[i]);
            }
        }
        cout << "  处理物品" << i << "后 dp = [";
        for (int j = 0; j <= W; j++) cout << setw(3) << dp_naive[j];
        cout << " ]" << endl;
    }
    cout << "  朴素做法结果 = " << dp_naive[W] << endl;
    cout << "  内层循环次数 ≈ " << N * W * (c[1] + c[2]) / 2 << " 次" << endl;
    cout << endl;

    // --- 二进制优化 ---
    cout << "【二进制优化：拆分后01背包 O(W*Σlog(c[i]))】" << endl;
    vector<int> new_w, new_v;
    for (int i = 1; i <= N; i++) {
        int rem = c[i];
        for (int k = 1; k <= rem; k <<= 1) {
            new_w.push_back(k * w[i]);
            new_v.push_back(k * v[i]);
            rem -= k;
        }
        if (rem > 0) {
            new_w.push_back(rem * w[i]);
            new_v.push_back(rem * v[i]);
        }
    }
    cout << "  拆分后物品数 = " << new_w.size() << " 个" << endl;
    cout << "  打包物品分别为：";
    for (size_t i = 0; i < new_w.size(); i++) {
        cout << "(" << new_w[i] << "kg, " << new_v[i] << "元) ";
    }
    cout << endl;

    vector<int> dp_bin(W + 1, 0);
    for (size_t i = 0; i < new_w.size(); i++) {
        for (int j = W; j >= new_w[i]; j--) {
            dp_bin[j] = max(dp_bin[j], dp_bin[j - new_w[i]] + new_v[i]);
        }
        cout << "  处理打包物品" << i + 1 << "后 dp = [";
        for (int j = 0; j <= W; j++) cout << setw(3) << dp_bin[j];
        cout << " ]" << endl;
    }
    cout << "  二进制优化结果 = " << dp_bin[W] << endl;
    cout << "  内层循环次数 ≈ " << new_w.size() * W << " 次" << endl;
    cout << endl;

    cout << "结论：两种方法结果相同（" << dp_naive[W] << " = " << dp_bin[W] << "），" << endl;
    cout << "      但二进制优化在大数据量下效率远超朴素做法！" << endl;
    cout << "      当c[i]=10000时，朴素做法≈10^8次，二进制优化≈10^5次。" << endl;
    cout << endl;
}

// ============================================================
// 三、分组背包 正确写法演示
// ============================================================
// 核心：组 → 容量（倒序）→ 组内物品
// 口诀："分组容量外"
// -----------------------------------------------------------
void group_knapsack_demo() {
    cout << "========== 分组背包 正确写法演示 ==========" << endl;
    cout << endl;

    int G, W;
    cout << "请输入组数 G 和背包容量 W：";
    cin >> G >> W;

    vector<int> dp(W + 1, 0);

    for (int g = 1; g <= G; g++) {
        int cnt;
        cout << "请输入第" << g << "组的物品数量：";
        cin >> cnt;

        vector<pair<int, int>> items(cnt);  // {weight, value}
        cout << "请依次输入该组每个物品的 重量 价值：" << endl;
        for (int k = 0; k < cnt; k++) {
            cout << "  第" << g << "组-物品" << k + 1 << "：";
            cin >> items[k].first >> items[k].second;
        }

        // 关键：容量循环在外，物品循环在内
        for (int j = W; j >= 0; j--) {
            for (int k = 0; k < cnt; k++) {
                int w = items[k].first, v = items[k].second;
                if (j >= w)
                    dp[j] = max(dp[j], dp[j - w] + v);
            }
        }

        cout << "  处理第" << g << "组后 dp = [";
        for (int j = 0; j <= W; j++) {
            if (j % 5 == 0 && j > 0) cout << " ";
            cout << setw(3) << dp[j];
        }
        cout << " ]" << endl;
    }

    cout << endl;
    cout << "最大总价值 = " << dp[W] << endl;
    cout << endl;
    cout << "核心要点：容量循环在外→每组最多选一个物品！" << endl;
    cout << endl;
}

// ============================================================
// 四、分组背包 循环顺序对比实验
// ============================================================
// 目的：直观展示正确顺序（容量外）vs 错误顺序（物品外）
// -----------------------------------------------------------
void group_knapsack_order_comparison() {
    cout << "========== 分组背包 循环顺序对比实验 ==========" << endl;
    cout << endl;
    cout << "使用固定数据：2组，容量=10" << endl;
    cout << "  第1组：物品A(3kg,5元), 物品B(4kg,6元)" << endl;
    cout << "  第2组：物品C(2kg,3元), 物品D(5kg,8元)" << endl;
    cout << endl;
    cout << "正确结果：每组最多选1个 → 最多选2个物品" << endl;
    cout << "理论最大值：选B(4kg,6元)+D(5kg,8元)=9kg,14元" << endl;
    cout << endl;

    const int G = 2, W = 10;
    vector<vector<pair<int, int>>> groups = {
        {},  // 占位
        {{3, 5}, {4, 6}},   // 第1组
        {{2, 3}, {5, 8}}    // 第2组
    };

    // --- 正确写法：容量外循环 ---
    cout << "【正确写法：组 → 容量（倒序）→ 组内物品】" << endl;
    vector<int> dp_right(W + 1, 0);
    for (int g = 1; g <= G; g++) {
        for (int j = W; j >= 0; j--) {
            for (auto &item : groups[g]) {
                int w = item.first, v = item.second;
                if (j >= w)
                    dp_right[j] = max(dp_right[j], dp_right[j - w] + v);
            }
        }
        cout << "  处理第" << g << "组后 dp = [";
        for (int j = 0; j <= W; j++) cout << setw(3) << dp_right[j];
        cout << " ]" << endl;
    }
    cout << "  正确结果 dp[" << W << "] = " << dp_right[W] << endl;
    cout << endl;

    // --- 错误写法：物品外循环 ---
    cout << "【错误写法：组 → 物品 → 容量（正序）← 会造成同组多选！】" << endl;
    vector<int> dp_wrong(W + 1, 0);
    for (int g = 1; g <= G; g++) {
        for (auto &item : groups[g]) {
            int w = item.first, v = item.second;
            for (int j = w; j <= W; j++) {
                dp_wrong[j] = max(dp_wrong[j], dp_wrong[j - w] + v);
            }
            cout << "  处理第" << g << "组-物品(" << w << "kg," << v
                 << "元)后 dp = [";
            for (int j = 0; j <= W; j++) cout << setw(3) << dp_wrong[j];
            cout << " ]" << endl;
        }
    }
    cout << "  错误结果 dp[" << W << "] = " << dp_wrong[W]
         << " ← 可能超了！同组多选导致。" << endl;
    cout << endl;

    cout << "对比结论：" << endl;
    cout << "  正确顺序（容量外）：dp[10]=" << dp_right[W]
         << " ← 每组最多选一个" << endl;
    cout << "  错误顺序（物品外）：dp[10]=" << dp_wrong[W]
         << " ← 同组物品可能都被选中" << endl;
    cout << endl;
    cout << "记忆口诀：分组容量外！" << endl;
    cout << endl;
}

// ============================================================
// 五、石子合并 区间DP演示
// ============================================================
// 核心：dp[i][j] = min(dp[i][k] + dp[k+1][j]) + sum(i,j)
// 口诀："区间先长度，石子并着走"
// -----------------------------------------------------------
void stone_merging_demo() {
    cout << "========== 石子合并 区间DP演示 ==========" << endl;
    cout << endl;
    cout << "（小数据量，输出完整DP表格和分割点）" << endl;
    cout << endl;

    int N;
    cout << "请输入石子堆数 N（建议≤8，方便查看表格）：";
    cin >> N;

    vector<int> a(N + 1), pre(N + 1, 0);
    cout << "请输入" << N << "堆石子的数量：" << endl;
    for (int i = 1; i <= N; i++) {
        cout << "  第" << i << "堆：";
        cin >> a[i];
        pre[i] = pre[i - 1] + a[i];
    }

    const int INF = 0x3f3f3f3f;
    vector<vector<int>> dp(N + 1, vector<int>(N + 1, INF));
    vector<vector<int>> split(N + 1, vector<int>(N + 1, 0));  // 记录最优分割点

    // 初始化：长度为1的区间合并代价为0
    for (int i = 1; i <= N; i++) dp[i][i] = 0;

    cout << endl;
    cout << "========== 区间DP计算过程 ==========" << endl;
    cout << endl;

    for (int len = 2; len <= N; len++) {
        cout << "--- 区间长度 len = " << len << " ---" << endl;
        for (int i = 1; i + len - 1 <= N; i++) {
            int j = i + len - 1;
            int best_k = i;
            int best_val = INF;

            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k + 1][j] + pre[j] - pre[i - 1];
                if (cost < best_val) {
                    best_val = cost;
                    best_k = k;
                }
            }

            dp[i][j] = best_val;
            split[i][j] = best_k;

            cout << "  dp[" << i << "][" << j << "] = ";
            cout << "min{";
            for (int k = i; k < j; k++) {
                if (k > i) cout << ", ";
                cout << "dp[" << i << "][" << k << "]+dp[" << k + 1 << "][" << j
                     << "]+sum(" << i << "," << j << ")="
                     << dp[i][k] << "+" << dp[k + 1][j] << "+"
                     << pre[j] - pre[i - 1] << "="
                     << dp[i][k] + dp[k + 1][j] + pre[j] - pre[i - 1];
            }
            cout << "} = " << dp[i][j];
            cout << "  （最优分割点 k=" << best_k << "）" << endl;
        }
        cout << endl;
    }

    // 输出完整DP表格
    cout << "========== 完整DP表格 ==========" << endl;
    cout << "（行:i, 列:j, dp[i][j] = 合并区间[i,j]的最小代价）" << endl;
    cout << endl;

    // 表头
    cout << " i\\j ";
    for (int j = 1; j <= N; j++) cout << setw(10) << j;
    cout << endl;

    for (int i = 1; i <= N; i++) {
        cout << setw(3) << i << " ";
        for (int j = 1; j <= N; j++) {
            if (j < i) {
                cout << "          ";
            } else if (dp[i][j] >= INF / 2) {
                cout << setw(10) << "INF";
            } else {
                cout << setw(10) << dp[i][j];
            }
        }
        cout << endl;
    }
    cout << endl;

    // 前缀和
    cout << "========== 前缀和 ==========" << endl;
    for (int i = 1; i <= N; i++) cout << "  pre[" << i << "] = " << pre[i] << endl;
    cout << endl;

    cout << "最小总代价 = " << dp[1][N] << endl;
    cout << endl;

    // 输出最优合并顺序（递归）
    function<void(int, int)> print_merge_order = [&](int i, int j) {
        if (i == j) {
            cout << "[" << a[i] << "]";
            return;
        }
        int k = split[i][j];
        cout << "(";
        print_merge_order(i, k);
        cout << " + ";
        print_merge_order(k + 1, j);
        cout << "→" << pre[j] - pre[i - 1] << ")";
    };

    cout << "最优合并顺序：";
    print_merge_order(1, N);
    cout << endl;
    cout << endl;
    cout << "记忆口诀: 区间先长度, 石子并着走" << endl;
    cout << endl;
}

// ============================================================
// 六、区间DP 通用框架总结
// ============================================================
void interval_dp_summary() {
    cout << "========== 区间DP 通用框架 ==========" << endl;
    cout << endl;

    cout << "【三层循环结构】" << endl;
    cout << endl;
    cout << "// 1. 初始化长度为1的区间" << endl;
    cout << "for (int i = 1; i <= N; i++) dp[i][i] = 初始值;" << endl;
    cout << endl;
    cout << "// 2. 枚举区间长度（从小到大，必须最外层）" << endl;
    cout << "for (int len = 2; len <= N; len++) {" << endl;
    cout << endl;
    cout << "    // 3. 枚举区间起点" << endl;
    cout << "    for (int i = 1; i + len - 1 <= N; i++) {" << endl;
    cout << "        int j = i + len - 1;  // 区间终点" << endl;
    cout << endl;
    cout << "        // 4. 枚举分割点" << endl;
    cout << "        for (int k = i; k < j; k++) {" << endl;
    cout << "            dp[i][j] = min/max(dp[i][j]," << endl;
    cout << "                dp[i][k] + dp[k+1][j] + 合并代价);" << endl;
    cout << "        }" << endl;
    cout << "    }" << endl;
    cout << "}" << endl;
    cout << endl;
    cout << "【常见题型】" << endl;
    cout << "  1. 石子合并 — 最小合并代价" << endl;
    cout << "  2. 矩阵连乘 — 最少乘法次数" << endl;
    cout << "  3. 回文串 — 最少插入/删除次数" << endl;
    cout << "  4. 括号匹配 — 最少添加括号数" << endl;
    cout << endl;
    cout << "【识别特征】" << endl;
    cout << "  - 问题可以按区间/段来划分" << endl;
    cout << "  - 每次操作合并相邻的两段" << endl;
    cout << "  - 答案通常是 dp[1][N]" << endl;
    cout << endl;
    cout << "【时间复杂度】O(N³)，N≤300 可行" << endl;
    cout << endl;
}

// ============================================================
// 七、综合对比总结
// ============================================================
void comprehensive_summary() {
    cout << "========== 第40课综合对比总结 ==========" << endl;
    cout << endl;

    cout << "+------------------+--------------------------------+---------------------------+" << endl;
    cout << "|     问题类型     |          核心技巧               |       记忆口诀           |" << endl;
    cout << "+------------------+--------------------------------+---------------------------+" << endl;
    cout << "| 多重背包         | 二进制拆分 → 01背包            | 多重二进制拆             |" << endl;
    cout << "| 分组背包         | 容量外循环，物品内循环          | 分组容量外               |" << endl;
    cout << "| 区间DP           | 枚举len→i→k，前缀和优化         | 区间先长度，石子并着走   |" << endl;
    cout << "+------------------+--------------------------------+---------------------------+" << endl;
    cout << endl;

    cout << "【循环顺序对比】" << endl;
    cout << "  01背包：    物品 外层，容量 内层（倒序）" << endl;
    cout << "  完全背包：  物品 外层，容量 内层（正序）" << endl;
    cout << "  多重背包：  拆分后同上（01背包）" << endl;
    cout << "  分组背包：  组 外层，容量 中层（倒序），物品 内层" << endl;
    cout << "  区间DP：    长度 外层，起点 中层，分割点 内层" << endl;
    cout << endl;

    cout << "【三类背包关系】" << endl;
    cout << "  01背包   ⊂ 多重背包（c[i]=1时退化为01背包）" << endl;
    cout << "  完全背包 ⊂ 多重背包（c[i]=∞时退化为完全背包）" << endl;
    cout << "  多重背包 → 二进制拆分 → 01背包（通用转化！）" << endl;
    cout << endl;

    cout << "【扩展思考】" << endl;
    cout << "  - 多重背包的单调队列优化（O(N*W)，进阶内容）" << endl;
    cout << "  - 环形石子合并（将环拆成2N的链）" << endl;
    cout << "  - 四边形不等式优化区间DP（降为O(N²)）" << endl;
    cout << endl;

    cout << "口诀总结：" << endl;
    cout << "  多重二进制拆，分组容量外。" << endl;
    cout << "  区间先长度，石子并着走。" << endl;
    cout << endl;
}

// ============================================================
// 主菜单
// ============================================================
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cout << "========================================" << endl;
    cout << "  CSP-J 第40课：背包问题（下）与区间DP" << endl;
    cout << "  程序演示合集" << endl;
    cout << "========================================" << endl;
    cout << endl;

    while (true) {
        cout << "请选择要运行的示例：" << endl;
        cout << "  1. 多重背包 二进制优化演示（展示拆分过程）" << endl;
        cout << "  2. 多重背包 朴素做法 vs 二进制优化 对比" << endl;
        cout << "  3. 分组背包 正确写法演示" << endl;
        cout << "  4. 分组背包 循环顺序对比实验（正确 vs 错误）" << endl;
        cout << "  5. 石子合并 区间DP演示（输出DP表格）" << endl;
        cout << "  6. 区间DP 通用框架总结" << endl;
        cout << "  7. 第40课综合对比总结" << endl;
        cout << "  0. 退出" << endl;
        cout << "请输入编号：";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 0) {
            cout << "再见！记住口诀：多重二进制拆，分组容量外。区间先长度，石子并着走！" << endl;
            break;
        }

        cout << endl;

        switch (choice) {
            case 1: multiple_knapsack_binary(); break;
            case 2: multiple_knapsack_compare(); break;
            case 3: group_knapsack_demo(); break;
            case 4: group_knapsack_order_comparison(); break;
            case 5: stone_merging_demo(); break;
            case 6: interval_dp_summary(); break;
            case 7: comprehensive_summary(); break;
            default: cout << "无效选择，请重试。" << endl << endl;
        }
    }

    return 0;
}
