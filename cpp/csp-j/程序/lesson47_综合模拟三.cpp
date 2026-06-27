/*
 * ============================================================================
 * 课程：Lesson 47 - CSP-J 综合模拟练习三
 * 内容：经典算法综合练习，包含动态规划、图论、数论等核心算法的完整实现
 * 目标：熟练掌握 CSP-J 常考算法的编码能力，通过综合测试验证算法正确性
 * 难度：CSP-J 提高组
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// 第一部分：01 背包问题
// ============================================================================

/*
 * 01背包 - 二维DP版本
 * 时间复杂度：O(N * W)，空间复杂度：O(N * W)
 * dp[i][w] 表示前 i 件物品放入容量为 w 的背包能获得的最大价值
 */
int knapsack01_2d(const vector<int>& weights, const vector<int>& values, int capacity) {
    const int N = weights.size();
    // dp[i][w]: 考虑前 i 件物品，背包容量为 w 时的最大价值
    vector<vector<int>> dp(N + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= N; ++i) {
        int w_i = weights[i - 1];
        int v_i = values[i - 1];
        for (int w = 0; w <= capacity; ++w) {
            if (w >= w_i) {
                // 状态转移：选或不选第 i 件物品
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - w_i] + v_i);
            } else {
                // 装不下，只能不选
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    return dp[N][capacity];
}

/*
 * 01背包 - 一维DP优化版本（滚动数组）
 * 时间复杂度：O(N * W)，空间复杂度：O(W)
 * 注意：内层循环必须从大到小遍历，确保每件物品只使用一次
 */
int knapsack01_1d(const vector<int>& weights, const vector<int>& values, int capacity) {
    const int N = weights.size();
    // dp[w]: 容量为 w 时的最大价值
    vector<int> dp(capacity + 1, 0);

    for (int i = 0; i < N; ++i) {
        int w_i = weights[i];
        int v_i = values[i];
        // 从大到小遍历，防止同一物品被多次使用（完全背包是从小到大）
        for (int w = capacity; w >= w_i; --w) {
            dp[w] = max(dp[w], dp[w - w_i] + v_i);
        }
    }
    return dp[capacity];
}

// ============================================================================
// 第二部分：最长递增子序列 (LIS)
// ============================================================================

/*
 * 最长递增子序列 - O(N^2) DP 解法
 * dp[i] 表示以第 i 个元素结尾的 LIS 长度
 */
int longestIncreasingSubsequence(const vector<int>& nums) {
    const int N = nums.size();
    if (N == 0) return 0;

    // dp[i]: 以 nums[i] 结尾的最长递增子序列长度
    vector<int> dp(N, 1);

    for (int i = 1; i < N; ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[j] < nums[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    // 最终答案是所有 dp[i] 的最大值
    return *max_element(dp.begin(), dp.end());
}

// ============================================================================
// 第三部分：图遍历 —— DFS 求连通分量数量
// ============================================================================

// DFS 四个方向的偏移量
const int DX[4] = {0, 1, 0, -1};
const int DY[4] = {1, 0, -1, 0};

/*
 * DFS 遍历网格中一个连通分量
 * 从 (x, y) 出发，将所有相连的 '1' 标记为已访问
 */
void dfsGrid(int x, int y, vector<vector<char>>& grid, vector<vector<bool>>& visited) {
    const int rows = grid.size();
    const int cols = grid[0].size();

    visited[x][y] = true;

    for (int d = 0; d < 4; ++d) {
        int nx = x + DX[d];
        int ny = y + DY[d];
        // 检查新坐标是否合法、是陆地且未访问过
        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols
            && grid[nx][ny] == '1' && !visited[nx][ny]) {
            dfsGrid(nx, ny, grid, visited);
        }
    }
}

/*
 * 计算网格中的连通分量数量
 * grid 中 '1' 表示陆地，'0' 表示水域
 * 返回岛屿数量（四连通）
 */
int dfsConnectedComponent(vector<vector<char>>& grid) {
    if (grid.empty() || grid[0].empty()) return 0;

    const int rows = grid.size();
    const int cols = grid[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    int components = 0;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == '1' && !visited[i][j]) {
                ++components;
                dfsGrid(i, j, grid, visited);
            }
        }
    }
    return components;
}

// ============================================================================
// 第四部分：BFS 求最短路径（网格迷宫）
// ============================================================================

/*
 * BFS 在网格迷宫中求从起点 (sx, sy) 到终点 (ex, ey) 的最短路径长度
 * grid 中 0 表示可通行，1 表示障碍物
 * 返回最短步数，若不可达则返回 -1
 */
int bfsShortestPath(vector<vector<int>>& grid, int sx, int sy, int ex, int ey) {
    const int rows = grid.size();
    const int cols = grid[0].size();

    // 检查起点和终点是否合法
    if (grid[sx][sy] == 1 || grid[ex][ey] == 1) return -1;

    // dist 数组同时承担"已访问"和"距离"两个角色
    vector<vector<int>> dist(rows, vector<int>(cols, -1));
    queue<pair<int, int>> q;

    q.push({sx, sy});
    dist[sx][sy] = 0;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        // 到达终点，返回当前距离
        if (x == ex && y == ey) return dist[x][y];

        for (int d = 0; d < 4; ++d) {
            int nx = x + DX[d];
            int ny = y + DY[d];
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols
                && grid[nx][ny] == 0 && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
    return -1; // 终点不可达
}

// ============================================================================
// 第五部分：Dijkstra 最短路径（邻接表 + 优先队列）
// ============================================================================

/*
 * Dijkstra 算法求从源点 src 到所有其他节点的最短距离
 * 使用邻接表表示图，优先队列优化
 * graph[i] 是一个 vector<pair<int, int>>，每个 pair 为 {邻接点, 边权}
 */
vector<int> dijkstra(int src, const vector<vector<pair<int, int>>>& graph) {
    const int N = graph.size();
    const int INF = 1e9;

    vector<int> dist(N, INF);
    // 优先队列：小顶堆，pair<距离, 节点编号>
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [curDist, u] = pq.top();
        pq.pop();

        // 懒删除：如果当前距离大于已知最短距离，跳过
        if (curDist > dist[u]) continue;

        for (const auto& edge : graph[u]) {
            int v = edge.first;
            int w = edge.second;
            // 松弛操作
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

// ============================================================================
// 第六部分：埃拉托色尼筛法
// ============================================================================

/*
 * 埃拉托色尼筛法：求 [1, n] 内所有素数
 * 返回 vector<bool>，isPrime[i] 表示 i 是否为素数
 */
vector<bool> sieveOfEratosthenes(int n) {
    // isPrime[i] 表示数字 i 是否为素数
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;  // 0 和 1 不是素数

    for (int i = 2; i * i <= n; ++i) {
        if (isPrime[i]) {
            // 从 i*i 开始标记，因为 i*2, i*3, ..., i*(i-1) 已被更小的因子标记过
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    return isPrime;
}

// ============================================================================
// 第七部分：数论基础
// ============================================================================

// 欧几里得算法求最大公约数
// 原理：gcd(a, b) = gcd(b, a % b)，直到 b == 0
int gcd(int a, int b) {
    while (b != 0) {
        int tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

// 最小公倍数，利用公式 lcm(a, b) = a / gcd(a, b) * b（先除后乘防溢出）
int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}

// 快速幂：计算 (base^exp) % mod
// 使用二进制拆分思想，时间复杂度 O(log exp)
long long fastPow(long long base, long long exp, long long mod) {
    long long result = 1 % mod;  // 处理 mod == 1 的边界情况
    base %= mod;

    while (exp > 0) {
        if (exp & 1) {
            // 当前二进制位为 1，乘入结果
            result = (result * base) % mod;
        }
        // 基数平方
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

// ============================================================================
// 测试主函数
// ============================================================================

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int passCount = 0, totalCount = 0;

    // ---------- 测试 01 背包 ----------
    cout << "========== 01 背包测试 ==========" << endl;
    {
        vector<int> w = {2, 3, 4, 5};
        vector<int> v = {3, 4, 5, 6};
        const int cap = 8;

        ++totalCount;
        int res2d = knapsack01_2d(w, v, cap);
        int res1d = knapsack01_1d(w, v, cap);
        if (res2d == 10 && res1d == 10) {
            cout << "[PASS] 01背包: 2D=" << res2d << ", 1D=" << res1d << ", 预期=10" << endl;
            ++passCount;
        } else {
            cout << "[FAIL] 01背包: 2D=" << res2d << ", 1D=" << res1d << ", 预期=10" << endl;
        }

        // 边界：空物品
        ++totalCount;
        vector<int> empty_w, empty_v;
        int empty2d = knapsack01_2d(empty_w, empty_v, 10);
        int empty1d = knapsack01_1d(empty_w, empty_v, 10);
        if (empty2d == 0 && empty1d == 0) {
            cout << "[PASS] 01背包-空物品: 2D=" << empty2d << ", 1D=" << empty1d << ", 预期=0" << endl;
            ++passCount;
        } else {
            cout << "[FAIL] 01背包-空物品: 2D=" << empty2d << ", 1D=" << empty1d << ", 预期=0" << endl;
        }

        // 边界：容量为0
        ++totalCount;
        int zero2d = knapsack01_2d(w, v, 0);
        int zero1d = knapsack01_1d(w, v, 0);
        if (zero2d == 0 && zero1d == 0) {
            cout << "[PASS] 01背包-容量为0: 2D=" << zero2d << ", 1D=" << zero1d << ", 预期=0" << endl;
            ++passCount;
        } else {
            cout << "[FAIL] 01背包-容量为0: 2D=" << zero2d << ", 1D=" << zero1d << ", 预期=0" << endl;
        }

        // 边界：单件物品装不下
        ++totalCount;
        vector<int> big_w = {10};
        vector<int> big_v = {100};
        int big2d = knapsack01_2d(big_w, big_v, 5);
        int big1d = knapsack01_1d(big_w, big_v, 5);
        if (big2d == 0 && big1d == 0) {
            cout << "[PASS] 01背包-装不下: 2D=" << big2d << ", 1D=" << big1d << ", 预期=0" << endl;
            ++passCount;
        } else {
            cout << "[FAIL] 01背包-装不下: 2D=" << big2d << ", 1D=" << big1d << ", 预期=0" << endl;
        }
    }

    // ---------- 测试 LIS ----------
    cout << "========== LIS 最长递增子序列测试 ==========" << endl;
    {
        ++totalCount;
        vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
        int lis = longestIncreasingSubsequence(nums);
        if (lis == 4) {  // [2,3,7,101] 或 [2,5,7,101]
            cout << "[PASS] LIS: 结果=" << lis << ", 预期=4" << endl;
            ++passCount;
        } else {
            cout << "[FAIL] LIS: 结果=" << lis << ", 预期=4" << endl;
        }

        // 边界：空数组
        ++totalCount;
        vector<int> empty_nums;
        int empty_lis = longestIncreasingSubsequence(empty_nums);
        if (empty_lis == 0) {
            cout << "[PASS] LIS-空数组: 结果=" << empty_lis << ", 预期=0" << endl;
            ++passCount;
        } else {
            cout << "[FAIL] LIS-空数组: 结果=" << empty_lis << ", 预期=0" << endl;
        }

        // 边界：递减数组
        ++totalCount;
        vector<int> dec = {5, 4, 3, 2, 1};
        int dec_lis = longestIncreasingSubsequence(dec);
        if (dec_lis == 1) {
            cout << "[PASS] LIS-递减: 结果=" << dec_lis << ", 预期=1" << endl;
            ++passCount;
        } else {
            cout << "[FAIL] LIS-递减: 结果=" << dec_lis << ", 预期=1" << endl;
        }

        // 单元素
        ++totalCount;
        vector<int> single = {42};
        int single_lis = longestIncreasingSubsequence(single);
        if (single_lis == 1) {
            cout << "[PASS] LIS-单元素: 结果=" << single_lis << ", 预期=1" << endl;
            ++passCount;
        } else {
            cout << "[FAIL] LIS-单元素: 结果=" << single_lis << ", 预期=1" << endl;
        }
    }

    // ---------- 测试 DFS 连通分量 ----------
    cout << "========== DFS 连通分量测试 ==========" << endl;
    {
        ++totalCount;
        vector<vector<char>> grid = {
            {'1', '1', '0', '0', '0'},
            {'1', '1', '0', '0', '0'},
            {'0', '0', '1', '0', '0'},
            {'0', '0', '0', '1', '1'}
        };
        int comps = dfsConnectedComponent(grid);
        if (comps == 3) {
            cout << "[PASS] 连通分量: 结果=" << comps << ", 预期=3" << endl;
            ++passCount;
        } else {
            cout << "[FAIL] 连通分量: 结果=" << comps << ", 预期=3" << endl;
        }

        // 边界：全0
        ++totalCount;
        vector<vector<char>> all_zero = {{'0', '0'}, {'0', '0'}};
        int zero_comp = dfsConnectedComponent(all_zero);
        if (zero_comp == 0) {
            cout << "[PASS] 连通分量-全水域: 结果=" << zero_comp << ", 预期=0" << endl;
            ++passCount;
        } else {
            cout << "[FAIL] 连通分量-全水域: 结果=" << zero_comp << ", 预期=0" << endl;
        }

        // 边界：全1
        ++totalCount;
        vector<vector<char>> all_one = {{'1', '1'}, {'1', '1'}};
        int one_comp = dfsConnectedComponent(all_one);
        if (one_comp == 1) {
            cout << "[PASS] 连通分量-全陆地: 结果=" << one_comp << ", 预期=1" << endl;
            ++passCount;
        } else {
            cout << "[FAIL] 连通分量-全陆地: 结果=" << one_comp << ", 预期=1" << endl;
        }
    }

    // ---------- 测试 BFS 最短路径 ----------
    cout << "========== BFS 最短路径测试 ==========" << endl;
    {
        ++totalCount;
        vector<vector<int>> maze = {
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 1, 0}
        };
        int shortest = bfsShortestPath(maze, 0, 0, 3, 3);
        if (shortest == 6) {
            cout << "[PASS] BFS最短路径: 结果=" << shortest << ", 预期=6" << endl;
            ++passCount;
        } else {
            cout << "[FAIL] BFS最短路径: 结果=" << shortest << ", 预期=6" << endl;
        }

        // 边界：起点即终点
        ++totalCount;
        int same = bfsShortestPath(maze, 0, 0, 0, 0);
        if (same == 0) {
            cout << "[PASS] BFS-起点即终点: 结果=" << same << ", 预期=0" << endl;
            ++passCount;
        } else {
            cout << "[FAIL] BFS-起点即终点: 结果=" << same << ", 预期=0" << endl;
        }

        // 边界：不可达
        ++totalCount;
        vector<vector<int>> blocked = {
            {0, 1, 0},
            {1, 1, 1},
            {0, 1, 0}
        };
        int unreach = bfsShortestPath(blocked, 0, 0, 2, 2);
        if (unreach == -1) {
            cout << "[PASS] BFS-不可达: 结果=" << unreach << ", 预期=-1" << endl;
            ++passCount;
        } else {
            cout << "[FAIL] BFS-不可达: 结果=" << unreach << ", 预期=-1" << endl;
        }
    }

    // ---------- 测试 Dijkstra ----------
    cout << "========== Dijkstra 最短路径测试 ==========" << endl;
    {
        ++totalCount;
        // 构建图：5个节点
        vector<vector<pair<int, int>>> graph(5);
        // 边：(u, v, w)
        graph[0].push_back({1, 2});
        graph[0].push_back({2, 4});
        graph[1].push_back({2, 1});
        graph[1].push_back({3, 7});
        graph[2].push_back({4, 3});
        graph[3].push_back({4, 1});

        vector<int> d = dijkstra(0, graph);
        bool ok = (d[0] == 0 && d[1] == 2 && d[2] == 3 && d[3] == 9 && d[4] == 6);
        if (ok) {
            cout << "[PASS] Dijkstra: dist[0..4]=";
            for (int x : d) cout << x << " ";
            cout << ", 预期=0 2 3 9 6" << endl;
            ++passCount;
        } else {
            cout << "[FAIL] Dijkstra: dist[0..4]=";
            for (int x : d) cout << x << " ";
            cout << ", 预期=0 2 3 9 6" << endl;
        }

        // 边界：单节点图
        ++totalCount;
        vector<vector<pair<int, int>>> single_graph(1);
        vector<int> single_d = dijkstra(0, single_graph);
        if (single_d[0] == 0) {
            cout << "[PASS] Dijkstra-单节点: dist[0]=" << single_d[0] << ", 预期=0" << endl;
            ++passCount;
        } else {
            cout << "[FAIL] Dijkstra-单节点: dist[0]=" << single_d[0] << ", 预期=0" << endl;
        }
    }

    // ---------- 测试筛法 ----------
    cout << "========== 筛法求素数测试 ==========" << endl;
    {
        ++totalCount;
        auto isPrime = sieveOfEratosthenes(20);
        // 20 以内的素数：2, 3, 5, 7, 11, 13, 17, 19
        vector<int> expected_primes = {2, 3, 5, 7, 11, 13, 17, 19};
        bool ok = true;
        for (int i = 1; i <= 20; ++i) {
            bool expected = (find(expected_primes.begin(), expected_primes.end(), i) != expected_primes.end());
            if (isPrime[i] != expected) {
                ok = false;
                break;
            }
        }
        if (ok) {
            cout << "[PASS] 筛法: 1~20素数验证正确" << endl;
            ++passCount;
        } else {
            cout << "[FAIL] 筛法: 1~20素数验证出错" << endl;
        }

        // 边界：n=1
        ++totalCount;
        auto isPrime1 = sieveOfEratosthenes(1);
        if (!isPrime1[0] && !isPrime1[1]) {
            cout << "[PASS] 筛法-n=1: 0和1都不是素数" << endl;
            ++passCount;
        } else {
            cout << "[FAIL] 筛法-n=1: 结果不正确" << endl;
        }

        // 边界：n=2
        ++totalCount;
        auto isPrime2 = sieveOfEratosthenes(2);
        if (!isPrime2[0] && !isPrime2[1] && isPrime2[2]) {
            cout << "[PASS] 筛法-n=2: 2是素数" << endl;
            ++passCount;
        } else {
            cout << "[FAIL] 筛法-n=2: 结果不正确" << endl;
        }
    }

    // ---------- 测试 GCD / LCM ----------
    cout << "========== GCD / LCM 测试 ==========" << endl;
    {
        ++totalCount;
        if (gcd(12, 8) == 4 && gcd(17, 13) == 1 && gcd(0, 5) == 5 && gcd(5, 0) == 5) {
            cout << "[PASS] GCD: gcd(12,8)=4, gcd(17,13)=1, gcd(0,5)=5, gcd(5,0)=5" << endl;
            ++passCount;
        } else {
            cout << "[FAIL] GCD: 结果不正确" << endl;
        }

        ++totalCount;
        if (lcm(12, 8) == 24 && lcm(6, 7) == 42 && lcm(1, 5) == 5) {
            cout << "[PASS] LCM: lcm(12,8)=24, lcm(6,7)=42, lcm(1,5)=5" << endl;
            ++passCount;
        } else {
            cout << "[FAIL] LCM: 结果不正确" << endl;
        }
    }

    // ---------- 测试快速幂 ----------
    cout << "========== 快速幂测试 ==========" << endl;
    {
        ++totalCount;
        if (fastPow(2, 10, 1000000007) == 1024) {
            cout << "[PASS] 快速幂: 2^10 mod 1e9+7 = " << fastPow(2, 10, 1000000007) << ", 预期=1024" << endl;
            ++passCount;
        } else {
            cout << "[FAIL] 快速幂: 2^10 结果不正确" << endl;
        }

        ++totalCount;
        long long fp0 = fastPow(5, 0, 100);
        if (fp0 == 1) {
            cout << "[PASS] 快速幂-exp=0: 5^0 mod 100 = " << fp0 << ", 预期=1" << endl;
            ++passCount;
        } else {
            cout << "[FAIL] 快速幂-exp=0: 结果=" << fp0 << ", 预期=1" << endl;
        }

        ++totalCount;
        long long fp1 = fastPow(7, 1, 13);
        if (fp1 == 7) {
            cout << "[PASS] 快速幂-exp=1: 7^1 mod 13 = " << fp1 << ", 预期=7" << endl;
            ++passCount;
        } else {
            cout << "[FAIL] 快速幂-exp=1: 结果=" << fp1 << ", 预期=7" << endl;
        }

        ++totalCount;
        long long fpmod = fastPow(2, 100, 7);
        // 2^100 mod 7，费马小定理：(2^6)^16 * 2^4 ≡ 1 * 16 ≡ 2 (mod 7)
        if (fpmod == 2) {
            cout << "[PASS] 快速幂-大指数: 2^100 mod 7 = " << fpmod << ", 预期=2" << endl;
            ++passCount;
        } else {
            cout << "[FAIL] 快速幂-大指数: 2^100 mod 7 = " << fpmod << ", 预期=2" << endl;
        }

        // 边界：mod=1
        ++totalCount;
        long long fp_mod1 = fastPow(123, 456, 1);
        if (fp_mod1 == 0) {
            cout << "[PASS] 快速幂-mod=1: 123^456 mod 1 = " << fp_mod1 << ", 预期=0" << endl;
            ++passCount;
        } else {
            cout << "[FAIL] 快速幂-mod=1: 结果=" << fp_mod1 << ", 预期=0" << endl;
        }
    }

    // ---------- 汇总 ----------
    cout << "========================================" << endl;
    cout << "测试汇总: " << passCount << " / " << totalCount << " 通过" << endl;
    if (passCount == totalCount) {
        cout << "全部测试通过！恭喜！" << endl;
    } else {
        cout << "有 " << (totalCount - passCount) << " 个测试未通过，请检查代码。" << endl;
    }
    cout << "========================================" << endl;

    return 0;
}
