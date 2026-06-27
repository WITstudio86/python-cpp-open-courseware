/**
 * 第20课：Floyd 与传递闭包
 *
 * 本文件实现了以下算法（全部可AC）：
 * 1. 标准 Floyd-Warshall 算法（O(V³)）
 * 2. 传递闭包 —— Warshall 算法
 * 3. 传递闭包 —— bitset 优化版（O(V³/64)）
 * 4. 无向图最小环检测
 * 5. 有向图最小环检测
 * 6. 路径还原
 *
 * 所有代码使用 using namespace std; 并提供充足的注释。
 *
 * 编译命令：g++ -std=c++17 -O2 lesson20_floyd.cpp -o lesson20
 * 运行方式：./lesson20 < input.txt
 */

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// 全局常量定义
// ============================================================
const int MAXN = 1005;                   // Floyd 适用约 n ≤ 800
const long long INF = 1e18;              // 无穷大（需保证 INF + INF 不溢出）

// ============================================================
// 1. 标准 Floyd-Warshall 算法
// ============================================================
// 适用场景：全源最短路，n ≤ 800（约 5e8 操作，1s 左右）
// 时间复杂度：O(n³)
// 空间复杂度：O(n²)

namespace Floyd {

    long long dist[MAXN][MAXN];          // dist[i][j] = i 到 j 的最短距离
    int nxt[MAXN][MAXN];                 // nxt[i][j] = 从 i 出发到 j 的最短路，i 的下一个节点
    int n;

    void init(int _n) {
        n = _n;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i == j) {
                    dist[i][j] = 0;
                    nxt[i][j] = j;      // 自己到自己
                } else {
                    dist[i][j] = INF;
                    nxt[i][j] = -1;     // 无路径
                }
            }
        }
    }

    // 添加有向边
    void add_edge(int u, int v, long long w) {
        if (w < dist[u][v]) {            // 处理重边，取最小
            dist[u][v] = w;
            nxt[u][v] = v;
        }
    }

    /**
     * floyd() —— 标准 Floyd-Warshall 算法
     *
     * 核心 DP：
     *   dp[k][i][j] = min(dp[k-1][i][j], dp[k-1][i][k] + dp[k-1][k][j])
     *
     * k 循环必须在最外层！
     * 下面的实现使用了滚动数组优化，直接在 dist 上更新。
     */
    void floyd() {
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                // 剪枝：若 i 无法到达 k，跳过
                if (dist[i][k] == INF) continue;
                for (int j = 1; j <= n; j++) {
                    // 防溢出：检查 dist[k][j] 是否可达
                    if (dist[k][j] == INF) continue;

                    long long new_dist = dist[i][k] + dist[k][j];
                    if (new_dist < dist[i][j]) {
                        dist[i][j] = new_dist;

                        // 路径还原：i→j 的最短路中，走出 i 后的第一个点
                        // = i→k 最短路中，走出 i 后的第一个点
                        nxt[i][j] = nxt[i][k];
                    }
                }
            }
        }
    }

    /**
     * has_negative_cycle() —— 检测负环
     * Floyd 结束后，若 dist[i][i] < 0，则点 i 在负环上。
     */
    bool has_negative_cycle() {
        // 先跑一遍 Floyd 以确保 dist 是最短路
        floyd();
        for (int i = 1; i <= n; i++) {
            if (dist[i][i] < 0) return true;
        }
        return false;
    }

    /**
     * print_path(i, j) —— 打印从 i 到 j 的最短路径
     */
    void print_path(int i, int j) {
        if (dist[i][j] == INF) {
            cout << "不可达" << endl;
            return;
        }
        if (i == j) {
            cout << i << endl;
            return;
        }
        int cur = i;
        while (cur != j) {
            cout << cur << " -> ";
            cur = nxt[cur][j];
            if (cur == -1) {
                cout << "(断链)" << endl;
                return;
            }
        }
        cout << j << endl;
    }

    /**
     * print_all_pairs() —— 输出全源最短距离矩阵
     */
    void print_all_pairs() {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][j] == INF)
                    cout << setw(5) << "INF";
                else
                    cout << setw(5) << dist[i][j];
                cout << ' ';
            }
            cout << endl;
        }
    }

} // namespace Floyd


// ============================================================
// 2. 传递闭包 —— Warshall 算法
// ============================================================
// 判断有向图中任意两点是否存在路径（i 能否到达 j）
// 时间复杂度：O(n³)，n ≤ 200 时轻松可过

namespace Warshall {

    // reach[i][j] = true 表示 i 可以到达 j（int 存储，方便位运算）
    int reach[MAXN][MAXN];
    int n;

    void init(int _n) {
        n = _n;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                reach[i][j] = (i == j);  // 自己可达自己
            }
        }
    }

    void add_edge(int u, int v) {
        reach[u][v] = true;
    }

    /**
     * warshall() —— 传递闭包算法
     *
     * 转移方程（与 Floyd 同构）：
     *   reach[i][j] |= (reach[i][k] & reach[k][j])
     */
    void warshall() {
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                if (!reach[i][k]) continue;  // 剪枝
                for (int j = 1; j <= n; j++) {
                    reach[i][j] |= (reach[i][k] & reach[k][j]);
                    // 等价于：if (reach[i][k] && reach[k][j]) reach[i][j] = 1;
                }
            }
        }
    }

    void print_matrix() {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++)
                cout << reach[i][j] << ' ';
            cout << endl;
        }
    }

} // namespace Warshall


// ============================================================
// 3. 传递闭包 —— bitset 优化版
// ============================================================
// bitset 将内层循环向量化，复杂度降为 O(n³ / 64)
// n = 2000 时，朴素 O(n³)=8e9 不可过，bitset 优化后约 1.25e8 可勉强通过

namespace WarshallBitset {

    const int MAXN_BS = 2005;
    bitset<MAXN_BS> reach[MAXN_BS];   // reach[i][j] = 1 表示 i 可达 j
    int n;

    void init(int _n) {
        n = _n;
        for (int i = 1; i <= n; i++) {
            reach[i].reset();
            reach[i][i] = true;        // 自己可达自己
        }
    }

    void add_edge(int u, int v) {
        reach[u][v] = true;
    }

    /**
     * warshall_bitset() —— bitset 优化的传递闭包
     *
     * 核心优化：内层 j 循环被 bitset 的 |= 操作替代
     *   for each i: if reach[i][k] then reach[i] |= reach[k]
     *
     * 一个 bitset 的 OR 操作是 O(n/64)，总体 O(n³/64)
     */
    void warshall_bitset() {
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                // 只有 i 可达 k 时，才需要合并 reach[k] 的行
                if (reach[i][k]) {
                    reach[i] |= reach[k];
                }
            }
        }
    }

    void print_matrix(int limit = 10) {
        for (int i = 1; i <= min(n, limit); i++) {
            for (int j = 1; j <= min(n, limit); j++)
                cout << reach[i][j] << ' ';
            cout << endl;
        }
        if (n > limit) cout << "  ... (仅显示前 " << limit << " 行/列)" << endl;
    }

} // namespace WarshallBitset


// ============================================================
// 4. 无向图最小环检测
// ============================================================
// 在 Floyd 的 k 循环中，利用 1..k-1 的最短路来检测经过 k 的最小环
// 时间复杂度：O(n³)（包含在 Floyd 内）

namespace MinCycleUndirected {

    long long g[MAXN][MAXN];        // 原始边权（直接边）
    long long dist[MAXN][MAXN];     // 经过 1..k-1 的最短路
    int n;

    void init(int _n) {
        n = _n;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                g[i][j] = dist[i][j] = INF;
            }
            g[i][i] = dist[i][i] = 0;
        }
    }

    void add_edge(int u, int v, long long w) {
        // 无向图：双向建边
        if (w < g[u][v]) {
            g[u][v] = g[v][u] = w;
            dist[u][v] = dist[v][u] = w;
        }
    }

    /**
     * find_min_cycle() —— 无向图最小环
     *
     * 原理：
     *   对于每个 k，枚举环上另两个节点 i, j (1 ≤ i < j < k)
     *   环的权值 = dist[i][j] + g[i][k] + g[k][j]
     *
     *   dist[i][j] 是 Floyd 进行到 k 之前的结果（只经过 1..k-1）
     *   因此这保证环上所有中间节点都 < k，环正确且不重复
     *
     * @return 最小环的权值和，若 INF 则表示不存在环
     */
    long long find_min_cycle() {
        long long ans = INF;

        for (int k = 1; k <= n; k++) {
            // 步骤1：利用 1..k-1 的最短路，计算经过 k 的最小环
            // 注意 i,j 必须 < k，确保环上的中间节点都来自 1..k-1
            for (int i = 1; i < k; i++) {
                for (int j = i + 1; j < k; j++) {
                    // 需保证三条边均存在
                    if (dist[i][j] != INF && g[i][k] != INF && g[k][j] != INF) {
                        long long cycle_w = dist[i][j] + g[i][k] + g[k][j];
                        if (cycle_w < ans) {
                            ans = cycle_w;
                        }
                    }
                }
            }

            // 步骤2：正常的 Floyd 更新，将 k 用作中间节点
            for (int i = 1; i <= n; i++) {
                if (dist[i][k] == INF) continue;
                for (int j = 1; j <= n; j++) {
                    if (dist[k][j] == INF) continue;
                    long long new_dist = dist[i][k] + dist[k][j];
                    if (new_dist < dist[i][j]) {
                        dist[i][j] = new_dist;
                    }
                }
            }
        }

        return ans;
    }

} // namespace MinCycleUndirected


// ============================================================
// 5. 有向图最小环检测
// ============================================================
// 方法一：跑完 Floyd 后检查 dist[i][i] 的最小值
// 方法二：在 Floyd 过程中检测

namespace MinCycleDirected {

    long long dist[MAXN][MAXN];
    int n;

    void init(int _n) {
        n = _n;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dist[i][j] = INF;
            }
            // 注意：dist[i][i] 初始化为 INF（不是 0）
            // 这样 Floyd 后才能通过 dist[i][i] 找到经过 i 的最小环
            dist[i][i] = INF;
        }
    }

    void add_edge(int u, int v, long long w) {
        if (w < dist[u][v]) {
            dist[u][v] = w;
        }
    }

    /**
     * find_min_cycle() —— 有向图最小环（方法一：后处理）
     *
     * 跑完 Floyd 后，min(dist[i][i]) 即是最小环权值和。
     * 注意要排除 dist[i][i] = 0（自己到自己的 trivial 环）。
     *
     * @return 最小环的权值和
     */
    long long find_min_cycle_post() {
        // 先跑 Floyd
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                if (dist[i][k] == INF) continue;
                for (int j = 1; j <= n; j++) {
                    if (dist[k][j] == INF) continue;
                    long long new_dist = dist[i][k] + dist[k][j];
                    if (new_dist < dist[i][j]) {
                        dist[i][j] = new_dist;
                    }
                }
            }
        }

        long long ans = INF;
        for (int i = 1; i <= n; i++) {
            // dist[i][i] 初始化为 INF，Floyd 后若被更新则说明存在环
            // 取所有被更新过的 dist[i][i] 的最小值即为最小环
            if (dist[i][i] < ans) {
                ans = dist[i][i];
            }
        }
        return ans;
    }

    /**
     * find_min_cycle_online() —— 有向图最小环（方法二：在线检测）
     *
     * 在 Floyd 的 k 循环中检测：dist[i][k] + g[k][i]
     * （未用 Floyd 做缩进也可直接枚举回边，这里演示更直接的方法）
     *
     * 注意：这里利用了已计算好的 1..k-1 阶段的最短路
     */
    // 该方法略去，实际竞赛中方法一（后处理）更常用且简明

} // namespace MinCycleDirected


// ============================================================
// 6. 综合演示与测试
// ============================================================

void run_demo() {
    cout << "========================================" << endl;
    cout << "  第20课 演示：Floyd 与传递闭包" << endl;
    cout << "========================================" << endl;

    // ---------- 1) 标准 Floyd ----------
    cout << "\n[1] 标准 Floyd-Warshall 算法" << endl;
    {
        using namespace Floyd;
        int n = 4, m = 5;
        init(n);
        int demo_edges[][3] = {
            {1, 2, 2}, {1, 3, 6}, {2, 3, 1},
            {2, 4, 5}, {3, 4, 3}
        };
        for (int i = 0; i < m; i++)
            add_edge(demo_edges[i][0], demo_edges[i][1], demo_edges[i][2]);

        floyd();
        cout << "全源最短距离矩阵：" << endl;
        print_all_pairs();

        cout << "从 1 到 4 的最短路径：";
        print_path(1, 4);

        cout << "是否存在负环: " << (has_negative_cycle() ? "是" : "否") << endl;
    }

    // ---------- 2) 传递闭包 ----------
    cout << "\n[2] 传递闭包（Warshall 算法）" << endl;
    {
        using namespace Warshall;
        int n = 4, m = 4;
        init(n);
        int demo_edges[][2] = {
            {1, 2}, {2, 3}, {2, 4}, {3, 1}
        };
        for (int i = 0; i < m; i++)
            add_edge(demo_edges[i][0], demo_edges[i][1]);

        warshall();
        cout << "传递闭包矩阵：" << endl;
        print_matrix();
        cout << "节点 1 可达 4: " << (reach[1][4] ? "是" : "否") << endl;
        cout << "节点 4 可达 1: " << (reach[4][1] ? "是" : "否") << endl;
    }

    // ---------- 3) bitset 优化传递闭包 ----------
    cout << "\n[3] 传递闭包（bitset 优化）" << endl;
    {
        using namespace WarshallBitset;
        int n = 4, m = 4;
        init(n);
        int demo_edges[][2] = {
            {1, 2}, {2, 3}, {2, 4}, {3, 1}
        };
        for (int i = 0; i < m; i++)
            add_edge(demo_edges[i][0], demo_edges[i][1]);

        warshall_bitset();
        cout << "bitset 传递闭包矩阵（前4行）：" << endl;
        print_matrix(4);
    }

    // ---------- 4) 无向图最小环 ----------
    cout << "\n[4] 无向图最小环检测" << endl;
    {
        using namespace MinCycleUndirected;
        int n = 4, m = 5;
        init(n);
        int demo_edges[][3] = {
            {1, 2, 2}, {2, 3, 3}, {3, 4, 4},
            {4, 1, 5}, {2, 4, 6}
        };
        for (int i = 0; i < m; i++)
            add_edge(demo_edges[i][0], demo_edges[i][1], demo_edges[i][2]);

        long long min_cycle = find_min_cycle();
        cout << "最小环权值和: ";
        if (min_cycle == INF) cout << "无环" << endl;
        else cout << min_cycle
             << "  (1→2→4→1: 2+6+5=13, 1→2→3→4→1: 2+3+4+5=14, 最小为13)" << endl;
    }

    // ---------- 5) 有向图最小环 ----------
    cout << "\n[5] 有向图最小环检测" << endl;
    {
        using namespace MinCycleDirected;
        int n = 4, m = 5;
        init(n);
        int demo_edges[][3] = {
            {1, 2, 2}, {2, 3, 3}, {3, 1, 1},  // 环 1→2→3→1 权值 2+3+1=6
            {2, 4, 4}, {4, 2, 1}              // 环 2→4→2 权值 4+1=5
        };
        for (int i = 0; i < m; i++)
            add_edge(demo_edges[i][0], demo_edges[i][1], demo_edges[i][2]);

        long long min_cycle = find_min_cycle_post();
        cout << "最小环权值和: ";
        if (min_cycle == INF) cout << "无环" << endl;
        else cout << min_cycle << "  (预期5: 2→4→2)" << endl;
    }

    cout << "\n========================================" << endl;
    cout << "  演示结束" << endl;
    cout << "========================================" << endl;
}


// ============================================================
// 7. 经典题目模板（可直接提交 AC）
// ============================================================

/**
 * B3611 【模板】传递闭包
 *
 * 输入：n 和 n×n 的邻接矩阵（0/1）
 * 输出：传递闭包矩阵
 *
 * 使用方法：注释掉 run_demo()，启用 solve_b3611()
 */
void solve_b3611() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    Warshall::init(n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            int x; cin >> x;
            if (x) Warshall::add_edge(i, j);
        }

    Warshall::warshall();
    Warshall::print_matrix();
}

/**
 * P6175 【模板】无向图最小环
 *
 * 输入：n m，然后 m 行 u v w
 * 输出：最小环权值和，若无环输出 "No solution."
 *
 * 使用方法：注释掉其他 solve，启用 solve_p6175()
 */
void solve_p6175() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    MinCycleUndirected::init(n);
    for (int i = 1; i <= m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        MinCycleUndirected::add_edge(u, v, w);
    }

    long long ans = MinCycleUndirected::find_min_cycle();
    if (ans == INF)
        cout << "No solution.\n";
    else
        cout << ans << '\n';
}


// ============================================================
// 主函数入口
// ============================================================
int main() {
    // ---- 演示模式 (默认启用，注释掉以运行竞赛题目) ----
    run_demo();

    // ---- 竞赛模式 (取消以下注释以提交到 OJ) ----
    // solve_b3611();
    // solve_p6175();

    return 0;
}
