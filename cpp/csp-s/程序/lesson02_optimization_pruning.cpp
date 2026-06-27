/*
 * ============================================================
 * 第02课：常数优化与剪枝技巧
 * 对应CSP-S考纲：常数优化、位运算优化、搜索剪枝、记忆化搜索
 *
 * 本程序演示以下优化技巧与算法：
 *   1. 快速读入/读出函数模板（输入输出优化）
 *   2. 位运算技巧集（lowbit、popcount、快速幂、子集枚举）
 *   3. N皇后问题 —— 三种剪枝方案性能对比
 *   4. 记忆化搜索 —— 斐波那契 / 数字三角形
 *
 * 通过实际运行对比，直观感受剪枝和优化的威力。
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;
using namespace chrono;
using ll = long long;

// ==================== 快速读入/读出 ====================

/*
 * 快速读入整数（支持负数）
 * 原理：使用 getchar() 逐字符读取，避免格式化输入的开销
 * 比 scanf 快约 2-3 倍，比 cin 快约 5-10 倍（解同步前）
 *
 * ch ^ 48：位运算等价于 ch - '0'（字符 '0' 的 ASCII 码是 48）
 * 位运算减法比算术减法略快（现代编译器差异不大，但作为习惯）
 */
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    // 跳过非数字字符，处理负号
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    // 读取数字
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + (ch ^ 48);  // ch ^ 48 等价于 ch - '0'
        ch = getchar();
    }
    return x * f;
}

/*
 * 快速读入 long long（支持负数）
 */
inline ll read_ll() {
    ll x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}

/*
 * 快速输出整数（支持负数）
 * 递归输出每一位，最后统一写入
 */
inline void write(int x) {
    if (x < 0) { putchar('-'); x = -x; }
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

/*
 * 快速输出后换行
 */
inline void writeln(int x) {
    write(x);
    putchar('\n');
}

// ==================== 位运算工具集 ====================

/*
 * lowbit：获取 x 的二进制表示中最低位的 1 所代表的值
 * 公式：x & (-x)
 * 原理：负数用补码表示，-x = ~x + 1，因此 x & (-x) 保留最低位的 1
 * 应用：树状数组的核心操作
 *
 * 示例：x = 12 (1100₂) → lowbit = 4 (100₂)
 *       x = 7  (0111₂) → lowbit = 1 (001₂)
 */
inline int lowbit(int x) {
    return x & -x;
}

/*
 * popcount（统计二进制中 1 的个数）
 * 方法1：Brian Kernighan 算法 —— 每次消除最低位的 1
 * 复杂度：O(答案) = O(popcount(x))
 */
int popcount_manual(unsigned int x) {
    int cnt = 0;
    while (x) {
        x &= x - 1;  // x & (x-1) 将最低位的 1 变为 0
        cnt++;
    }
    return cnt;
}

/*
 * popcount：使用 GCC 内置函数（映射到 CPU 的 POPCNT 指令）
 * 复杂度：O(1)，硬件级别加速
 */
inline int popcount(unsigned int x) {
    return __builtin_popcount(x);
}

/*
 * 判断 x 是否为 2 的幂
 * 原理：2 的幂的二进制表示只有 1 个 1，因此 x & (x-1) == 0
 * 注意：需要排除 x <= 0 的情况
 *
 * 示例：x=8 (1000₂), x-1=7 (0111₂) → 8 & 7 = 0 ✅
 *       x=6 (0110₂), x-1=5 (0101₂) → 6 & 5 = 4 ≠ 0 ❌
 */
inline bool is_power_of_two(int x) {
    return x > 0 && (x & (x - 1)) == 0;
}

/*
 * 获取 x 的二进制最高位 1 的位置（即 floor(log2(x))）
 * __builtin_clz: Count Leading Zeros（统计前导零的个数）
 * 32 位整数：31 - clz(x) 即为最高位 1 的索引
 *
 * 示例：x=18 (10010₂) → clz(18)=27 → highbit=31-27=4
 */
inline int highbit(unsigned int x) {
    return x ? 31 - __builtin_clz(x) : -1;
}

/*
 * 获取 x 的二进制最低位 1 的位置
 * __builtin_ctz: Count Trailing Zeros（统计尾部零的个数）
 *
 * 示例：x=18 (10010₂) → ctz(18)=1 → 最低位 1 在索引 1
 */
inline int ctz(unsigned int x) {
    return __builtin_ctz(x);
}

/*
 * 快速幂：计算 a^b mod MOD
 * 时间复杂度：O(log b)
 * 原理：将指数 b 按二进制拆分
 * 如 a^13 = a^(1101₂) = a^8 · a^4 · a^1
 *
 * 这是竞赛中最常用的取模幂运算模板
 */
ll qpow(ll a, ll b, ll mod) {
    ll res = 1;
    a %= mod;
    while (b) {
        if (b & 1) res = res * a % mod;  // b 的最低位是 1
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

/*
 * 子集枚举（降序遍历 mask 的所有非空子集）
 * 应用：状态压缩 DP 中的子集遍历
 * 复杂度：O(3^n)（所有子集的子集之和）
 *
 * 用法：
 *   for (int sub = mask; sub; sub = (sub - 1) & mask) {
 *       // sub 是 mask 的一个非空子集
 *   }
 */
void demo_subset_enumeration(int mask) {
    cout << "mask = " << mask << " (" << bitset<4>(mask) << ") 的所有子集：\n";
    vector<int> subsets;
    for (int sub = mask; sub; sub = (sub - 1) & mask) {
        subsets.push_back(sub);
    }
    // 逆序输出（因为枚举顺序是降序的）
    reverse(subsets.begin(), subsets.end());
    for (int sub : subsets) {
        cout << "  " << sub << " (" << bitset<4>(sub) << ")\n";
    }
}

// ==================== N皇后问题：三种剪枝方案 ====================

/*
 * N皇后问题的三种实现，展示剪枝优化的威力。
 * 规定：每行只能放一个皇后（行剪枝），按行深搜。
 */

// -------- 方案1：数组标记剪枝 （可行性剪枝） --------
namespace NQueen_Array {
    int n, ans = 0;
    bool col[50];       // col[c] = true 表示第 c 列已被占用
    bool diag1[100];    // diag1[r+c] = true 表示主对角线已占用
    bool diag2[100];    // diag2[r-c+n] = true 表示副对角线已占用

    /*
     * 剪枝分析：
     * - 列剪枝：col[c] → 每个皇后不同列
     * - 主对角线剪枝：diag1[r+c] → 主对角线上行号+列号相同
     * - 副对角线剪枝：diag2[r-c+n] → 副对角线上行号-列号相同（+n 防止负数）
     *
     * 有了这三个剪枝，时间复杂度从裸 DFS 的 O(N^N) 降到实际可搜索的规模。
     * N=8：92 个解，搜索约 2000 个节点
     * N=14：365596 个解，搜索约 2800 万节点
     */
    void dfs(int r) {
        if (r == n) {
            ans++;
            return;
        }
        for (int c = 0; c < n; c++) {
            // 可行性剪枝：列或任一对角线被占用则跳过
            if (col[c] || diag1[r + c] || diag2[r - c + n])
                continue;

            // 放置皇后
            col[c] = diag1[r + c] = diag2[r - c + n] = true;
            dfs(r + 1);
            // 回溯：撤销放置
            col[c] = diag1[r + c] = diag2[r - c + n] = false;
        }
    }

    int solve(int _n) {
        n = _n; ans = 0;
        memset(col, 0, sizeof(col));
        memset(diag1, 0, sizeof(diag1));
        memset(diag2, 0, sizeof(diag2));
        dfs(0);
        return ans;
    }
}

// -------- 方案2：位运算优化剪枝 (更快的常数) --------
namespace NQueen_Bitwise {
    int n, ans = 0;
    int full_mask;  // (1 << n) - 1，所有可能的列位置

    /*
     * 位运算版 N 皇后
     *
     * 参数说明（位掩码表示哪些列已被占用）：
     *   col_mask   : 当前哪些列已被放置皇后
     *   diag1_mask : 主对角线在下一行中哪些列不可用
     *   diag2_mask : 副对角线在下一行中哪些列不可用
     *
     * 为什么比方案1更快：
     *   1. 三个 bool 数组的判断合并为一条位运算
     *   2. lowbit 操作直接用 CPU 指令
     *   3. 所有操作在寄存器中完成，无需访问内存
     */
    void dfs(int r, int col_mask, int diag1_mask, int diag2_mask) {
        if (r == n) {
            ans++;
            return;
        }
        // 计算当前行所有可用的列位置
        // available 的每个为 1 的位表示该列可用
        int available = full_mask & ~(col_mask | diag1_mask | diag2_mask);

        // 逐个处理可用列（使用 lowbit 加速）
        while (available) {
            int pos = available & -available;  // lowbit：取最低位的 1
            available -= pos;                   // 移除该位置

            // 递归下一行
            // diag1: 下一行时主对角线向右"移动"一位（<<1）
            // diag2: 下一行时副对角线向左"移动"一位（>>1）
            dfs(r + 1,
                col_mask | pos,
                (diag1_mask | pos) << 1,
                (diag2_mask | pos) >> 1);
        }
    }

    int solve(int _n) {
        n = _n; ans = 0;
        full_mask = (1 << n) - 1;
        dfs(0, 0, 0, 0);
        return ans;
    }
}

/*
 * N皇后对比演示
 */
void demo_n_queens() {
    cout << "\n【演示】N皇后问题：剪枝方案性能对比" << endl;
    cout << string(60, '-') << endl;
    cout << "  N\t答案\t\t方案1(数组)\t方案2(位运算)\t加速比" << endl;
    cout << string(60, '-') << endl;

    for (int n = 8; n <= 14; n++) {
        cout << "  " << n << "\t";

        // 方案1
        auto start1 = high_resolution_clock::now();
        int ans1 = NQueen_Array::solve(n);
        auto end1 = high_resolution_clock::now();
        double t1 = duration<double>(end1 - start1).count();

        // 方案2
        auto start2 = high_resolution_clock::now();
        int ans2 = NQueen_Bitwise::solve(n);
        auto end2 = high_resolution_clock::now();
        double t2 = duration<double>(end2 - start2).count();

        cout << ans1 << "\t\t";
        cout << fixed << setprecision(4) << t1 << "s\t\t";
        cout << fixed << setprecision(4) << t2 << "s\t\t";
        if (t2 > 0) {
            cout << fixed << setprecision(1) << (t1 / t2) << "x";
        }
        cout << endl;

        // 验证两种方案结果一致
        if (ans1 != ans2) {
            cerr << "错误：两种方案结果不一致！" << endl;
        }
    }
}

// ==================== 记忆化搜索 ====================

// -------- 斐波那契：三种实现对比 --------

/*
 * 斐波那契递归版（无记忆化，指数复杂度）
 * T(n) = T(n-1) + T(n-2) + O(1)
 * 复杂度：O(2^n)，存在大量重复计算
 */
ll fib_naive(int n) {
    if (n <= 1) return n;
    return fib_naive(n - 1) + fib_naive(n - 2);
}

/*
 * 斐波那契记忆化版（缓存已计算结果）
 * 复杂度：O(n)，每个子问题只计算一次
 *
 * 记忆化将指数级复杂度降为线性！
 */
const int MAXFIB = 100000;
ll fib_memo[MAXFIB];
bool fib_vis[MAXFIB];

ll fib_memoized(int n) {
    if (n <= 1) return n;
    if (fib_vis[n]) return fib_memo[n];  // 记忆化：直接返回缓存
    fib_vis[n] = true;
    return fib_memo[n] = fib_memoized(n - 1) + fib_memoized(n - 2);
}

/*
 * 斐波那契迭代版（线性，无递归开销）
 * 复杂度：O(n)，空间 O(1)
 */
ll fib_iter(int n) {
    if (n <= 1) return n;
    ll a = 0, b = 1;
    for (int i = 2; i <= n; i++) {
        ll c = a + b;
        a = b;
        b = c;
    }
    return b;
}

/*
 * 斐波那契对比演示
 */
void demo_fibonacci_memo() {
    cout << "\n【演示】斐波那契：朴素递归 vs 记忆化 vs 迭代" << endl;
    cout << string(60, '-') << endl;

    // 朴素递归：仅对很小的 n 测试（n>40 就太慢）
    cout << "  朴素递归 O(2^n) — 仅测试小 n：" << endl;
    cout << "  n\tF(n)\t\t调用次数\t时间" << endl;
    cout << "  " << string(50, '-') << endl;
    for (int n = 20; n <= 40; n += 5) {
        auto start = high_resolution_clock::now();
        ll ans = fib_naive(n);
        auto end = high_resolution_clock::now();
        double t = duration<double>(end - start).count();
        cout << "  " << n << "\t" << ans << "\t\t"
             << ((1LL << (n + 1)) - 1) << "\t\t"
             << fixed << setprecision(4) << t << "s" << endl;
    }

    // 记忆化 vs 迭代：测试大 n
    cout << "\n  记忆化 O(n) vs 迭代 O(n) — 大 n 对比：" << endl;
    cout << "  n\t\t记忆化\t\t迭代" << endl;
    cout << "  " << string(50, '-') << endl;
    vector<int> ns = {100, 1000, 10000, 50000, 100000};
    for (int n : ns) {
        memset(fib_vis, 0, sizeof(fib_vis));
        auto start = high_resolution_clock::now();
        ll ans_memo = fib_memoized(n);
        auto mid = high_resolution_clock::now();
        ll ans_iter = fib_iter(n);
        auto end = high_resolution_clock::now();

        cout << "  " << n << "\t\t"
             << fixed << setprecision(6)
             << duration<double>(mid - start).count() << "s\t"
             << duration<double>(end - mid).count() << "s"
             << "  (ans=" << ans_memo << ")" << endl;

        if (ans_memo != ans_iter) {
            cerr << "错误：记忆化和迭代结果不一致！" << endl;
        }
    }
}

// -------- 数字三角形（经典 DP 的记忆化实现）--------

/*
 * 数字三角形问题：
 * 给定一个 n 行的数字三角形，从顶部出发，在每一节点可以选择向左下或右下走，
 * 一直走到底层，求最大路径和。
 *
 * 示例（n=5）：
 *       7
 *      3 8
 *     8 1 0
 *    2 7 4 4
 *   4 5 2 6 5
 *
 * 答案：30（7→3→8→7→5）
 */

const int MAXTR = 1005;
int triangle[MAXTR][MAXTR];
ll dp[MAXTR][MAXTR];
bool vis[MAXTR][MAXTR];

/*
 * 记忆化搜索版：自顶向下
 * dfs(i, j)：从位置 (i, j) 出发到达底层的最大路径和
 *
 * 状态定义：dp[i][j] = 从 (i,j) 到底层的最大路径和
 * 状态转移：dp[i][j] = a[i][j] + max(dp[i+1][j], dp[i+1][j+1])
 *
 * 复杂度：O(n^2)，每个状态只计算一次
 */
ll dfs_triangle(int i, int j, int n) {
    if (i == n) return triangle[i][j];  // 到达底层
    if (vis[i][j]) return dp[i][j];     // 记忆化：直接返回

    vis[i][j] = true;
    ll left = dfs_triangle(i + 1, j, n);
    ll right = dfs_triangle(i + 1, j + 1, n);
    return dp[i][j] = triangle[i][j] + max(left, right);
}

/*
 * 递推版：自底向上
 * 可以对比记忆化和递推的效率差异
 */
ll dp_iterative(int n) {
    // dp[i][j] 使用原数组存储
    for (int i = n - 1; i >= 1; i--) {
        for (int j = 1; j <= i; j++) {
            triangle[i][j] += max(triangle[i+1][j], triangle[i+1][j+1]);
        }
    }
    return triangle[1][1];
}

/*
 * 数字三角形演示
 */
void demo_triangle() {
    cout << "\n【演示】数字三角形：记忆化搜索 vs 自底向上递推" << endl;
    cout << string(60, '-') << endl;

    // 准备测试数据
    int n = 1000;  // 1000 行的三角形，约 50 万个状态
    srand(42);     // 固定随机种子保证可复现

    // 生成随机三角形
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            triangle[i][j] = rand() % 100;
        }
    }

    // 备份三角形（递推版会修改原数组）
    vector<vector<int>> backup(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            backup[i][j] = triangle[i][j];

    // 记忆化搜索版
    memset(vis, 0, sizeof(vis));
    auto start = high_resolution_clock::now();
    ll ans_memo = dfs_triangle(1, 1, n);
    auto end = high_resolution_clock::now();
    double t_memo = duration<double>(end - start).count();

    // 递推版（需要恢复数据）
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            triangle[i][j] = backup[i][j];

    start = high_resolution_clock::now();
    ll ans_iter = dp_iterative(n);
    end = high_resolution_clock::now();
    double t_iter = duration<double>(end - start).count();

    cout << "  规模：n = " << n << " (总状态数 ≈ " << (ll)n * (n + 1) / 2 << ")" << endl;
    cout << "  记忆化搜索：" << fixed << setprecision(6) << t_memo << "s" << endl;
    cout << "  自底向上递推：" << fixed << setprecision(6) << t_iter << "s" << endl;
    cout << "  答案：" << ans_memo << " (两方法一致: " << (ans_memo == ans_iter ? "✅" : "❌") << ")" << endl;
    cout << endl;
    cout << "  分析：递推版通常更快（无递归开销、访问连续内存）。" << endl;
    cout << "  记忆化适用于状态空间稀疏或拓扑序不明确的场景。" << endl;
}

// ==================== 搜索剪枝综合示例：0-1背包 ====================

/*
 * 0-1 背包问题（搜索 + 剪枝 解法）
 *
 * 虽然 0-1 背包的标准解法是 DP，但搜索 + 剪枝 方法可以展示
 * 可行性剪枝和最优性剪枝的整体框架。
 */

const int MAXITEM = 100;
int w[MAXITEM], v[MAXITEM];  // 重量、价值
int best_val = 0;            // 当前最优解
int capacity;                // 背包容量
int n_items;                 // 物品数量

// 后缀价值数组：suffix_val[i] = 物品 i..n-1 的价值之和
int suffix_val[MAXITEM];

/*
 * 0-1 背包的 DFS + 剪枝
 *
 * 剪枝策略：
 *   1. 可行性剪枝：当前重量超过容量 → 立即回溯
 *   2. 最优性剪枝：当前价值 + 剩余所有物品的总价值 ≤ 当前最优 → 剪枝
 *   3. 顺序性剪枝：可以加入估价函数做更精细的剪枝
 */
void knapsack_dfs(int idx, int cur_w, int cur_v) {
    // 剪枝1：可行性剪枝 —— 超重
    if (cur_w > capacity) return;

    // 剪枝2：最优性剪枝 —— 无论如何不可能超过当前最优
    if (cur_v + suffix_val[idx] <= best_val) return;

    // 到达末尾：更新最优解
    if (idx == n_items) {
        best_val = max(best_val, cur_v);
        return;
    }

    // 分支1：不选第 idx 个物品
    knapsack_dfs(idx + 1, cur_w, cur_v);

    // 分支2：选第 idx 个物品
    knapsack_dfs(idx + 1, cur_w + w[idx], cur_v + v[idx]);
}

/*
 * 0-1 背包标准 DP 解法（用于对比）
 */
int knapsack_dp(int T, int M) {
    vector<int> dp(T + 1, 0);
    for (int i = 0; i < M; i++) {
        for (int j = T; j >= w[i]; j--) {
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
    }
    return dp[T];
}

void demo_knapsack_pruning() {
    cout << "\n【演示】0-1背包：DFS剪枝 vs DP 性能对比" << endl;
    cout << string(60, '-') << endl;

    // 测试数据
    n_items = 30;
    capacity = 1000;
    srand(123);
    for (int i = 0; i < n_items; i++) {
        w[i] = rand() % 200 + 1;
        v[i] = rand() % 200 + 1;
    }

    // 计算后缀价值（用于最优性剪枝）
    suffix_val[n_items] = 0;
    for (int i = n_items - 1; i >= 0; i--) {
        suffix_val[i] = suffix_val[i + 1] + v[i];
    }

    // DFS + 剪枝
    best_val = 0;
    auto start = high_resolution_clock::now();
    knapsack_dfs(0, 0, 0);
    auto end = high_resolution_clock::now();
    double t_dfs = duration<double>(end - start).count();

    // DP 解法
    start = high_resolution_clock::now();
    int ans_dp = knapsack_dp(capacity, n_items);
    end = high_resolution_clock::now();
    double t_dp = duration<double>(end - start).count();

    cout << "  物品数: " << n_items << ", 容量: " << capacity << endl;
    cout << "  DFS+剪枝 (最优价=" << best_val << "): "
         << fixed << setprecision(6) << t_dfs << "s" << endl;
    cout << "  DP 解法  (最优价=" << ans_dp << "): "
         << fixed << setprecision(6) << t_dp << "s" << endl;

    if (best_val == ans_dp) {
        cout << "  结果一致 ✅" << endl;
    }

    cout << endl;
    cout << "  说明：对于 0-1 背包，DP 是 O(N×T) 的，而 DFS+剪枝在最坏情况下" << endl;
    cout << "  仍可能是指数级的。剪枝适用于搜索空间\"天然\"较小的场景。" << endl;
}

// ==================== 主程序 ====================

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "============================================================" << endl;
    cout << "  第02课：常数优化与剪枝技巧 —— 性能对比演示" << endl;
    cout << "============================================================" << endl;

    // ============ 1. 位运算工具集演示 ============
    cout << "\n【演示1】位运算工具集" << endl;
    cout << string(60, '-') << endl;

    int test_x = 18;  // 10010₂
    cout << "  测试数值 x = " << test_x << " (二进制: " << bitset<8>(test_x) << ")" << endl;
    cout << "  lowbit(x)        = " << lowbit(test_x) << " (二进制: " << bitset<8>(lowbit(test_x)) << ")" << endl;
    cout << "  popcount(x)      = " << popcount(test_x) << endl;
    cout << "  is_power_of_two  = " << (is_power_of_two(test_x) ? "true" : "false") << endl;
    cout << "  highbit(x)       = " << highbit(test_x) << endl;
    cout << "  ctz(x)           = " << ctz(test_x) << endl;
    cout << endl;

    // 2 的幂测试
    cout << "  2的幂测试：" << endl;
    for (int v : {1, 2, 4, 8, 16, 32, 3, 6, 10, 18}) {
        cout << "    " << setw(2) << v << ": "
             << (is_power_of_two(v) ? "是" : "否") << endl;
    }
    cout << endl;

    // 子集枚举
    cout << "  子集枚举示例：" << endl;
    demo_subset_enumeration(0b1011);  // mask = 11
    cout << endl;

    // 快速幂测试
    cout << "  快速幂测试：2^10 mod 1000000007 = "
         << qpow(2, 10, 1000000007) << endl;
    cout << "  快速幂测试：3^20 mod 1000000007 = "
         << qpow(3, 20, 1000000007) << endl;
    cout << endl;

    // ============ 2. N皇后剪枝对比 ============
    demo_n_queens();

    // ============ 3. 斐波那契：记忆化 ============
    demo_fibonacci_memo();

    // ============ 4. 数字三角形：记忆化 vs 递推 ============
    demo_triangle();

    // ============ 5. 0-1背包：搜索剪枝 ============
    demo_knapsack_pruning();

    // ============ 总结 ============
    cout << "\n【总结】优化与剪枝核心技巧" << endl;
    cout << string(60, '-') << endl;
    cout << "  1. 快速读入：使用 getchar() 逐字符读取，比 cin 快 5-10 倍" << endl;
    cout << "  2. 位运算：lowbit/快速幂/子集枚举，竞赛高频必备" << endl;
    cout << "  3. 搜索剪枝：可行性/最优性/顺序性，三把剪刀缺一不可" << endl;
    cout << "  4. 记忆化：用空间换时间，将指数算法降为多项式" << endl;
    cout << "  5. 编译器优化：开 -O2，大多数情况下已经足够" << endl;
    cout << endl;
    cout << "  应试建议：先保证正确性，再针对瓶颈做常数优化。" << endl;
    cout << "  搜索题必须加剪枝，不加剪枝几乎必超时！" << endl;

    return 0;
}
