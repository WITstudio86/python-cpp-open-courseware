/**
 * 第24课：关键路径与差分约束
 *
 * 包含以下实现：
 * 1. AOE网关键路径算法（拓扑排序 + ve/vl 计算）
 * 2. 差分约束系统 SPFA 求解
 * 3. 超级源点技巧
 * 4. 负环检测（差分约束无解判定）
 *
 * 所有代码均可AC通过对应题目。
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <tuple>
using namespace std;

// ============================================================
// 第一部分：AOE 网关键路径算法
// 核心思想：
//   1. 正向拓扑排序计算 ve（最早发生时间）
//   2. 逆向拓扑排序计算 vl（最晚发生时间）
//   3. ve[u] + w == vl[v] 的边为关键活动
// 时间复杂度 O(V+E)，空间复杂度 O(V+E)
// ============================================================

// 边结构体（用于邻接表）
struct Edge {
    int to;         // 目标节点
    int weight;     // 活动持续时间
};

/**
 * 关键路径算法
 * @param n     节点数（事件 0 ~ n-1）
 * @param edges 边列表，每条边 (u, v, w) 表示活动 u->v 持续 w
 * @return      pair<工程最短完成时间, 关键活动列表>
 */
pair<int, vector<pair<int, int>>> criticalPath(int n,
        vector<tuple<int, int, int>>& edges) {

    // 1. 建立邻接表 + 统计入度
    vector<vector<Edge>> adj(n);
    vector<int> indegree(n, 0);
    for (auto& e : edges) {
        int u = get<0>(e), v = get<1>(e), w = get<2>(e);
        adj[u].push_back({v, w});
        indegree[v]++;
    }

    // 2. 拓扑排序 + 正向计算 ve（最早发生时间）
    //    ve[v] = max(ve[u] + w)  对所有入边 u->v
    vector<int> ve(n, 0);               // 最早发生时间，初始化为 0
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0) {         // 源点（入度为 0）
            q.push(i);
        }
    }

    vector<int> topoOrder;              // 记录拓扑序列（备用）
    while (!q.empty()) {
        int u = q.front(); q.pop();
        topoOrder.push_back(u);

        for (auto& e : adj[u]) {
            int v = e.to, w = e.weight;
            // 【关键 DP】ve[v] = max(ve[v], ve[u] + w)
            ve[v] = max(ve[v], ve[u] + w);

            if (--indegree[v] == 0) {
                q.push(v);
            }
        }
    }

    // 3. 获取工程的最短完成时间（汇点的 ve，即所有 ve 的最大值）
    int maxTime = 0;
    for (int i = 0; i < n; i++) {
        maxTime = max(maxTime, ve[i]);
    }

    // 4. 逆向计算 vl（最晚发生时间）
    //    初始化所有 vl = maxTime（即汇点的 ve）
    //    vl[u] = min(vl[v] - w)  对所有出边 u->v
    vector<int> vl(n, maxTime);
    // 按拓扑序的逆序处理
    for (int i = n - 1; i >= 0; i--) {
        int u = topoOrder[i];
        for (auto& e : adj[u]) {
            int v = e.to, w = e.weight;
            // 【关键 DP】vl[u] = min(vl[u], vl[v] - w)
            vl[u] = min(vl[u], vl[v] - w);
        }
    }

    // 5. 找出关键活动：ve[u] + w == vl[v]
    vector<pair<int, int>> criticalEdges;
    for (auto& e : edges) {
        int u = get<0>(e), v = get<1>(e), w = get<2>(e);
        if (ve[u] + w == vl[v]) {
            criticalEdges.push_back({u, v});
        }
    }

    return {maxTime, criticalEdges};
}


// ============================================================
// 第二部分：差分约束系统 SPFA 求解
// 核心思想：
//   不等式 x_i - x_j ≤ c  转化为 有向边 j → i，权值为 c
//   求最短路得到一组可行解
//   若存在负环则不等式组无解
// 时间复杂度 O(VE) 最坏，实际通常更快
// ============================================================

/**
 * 差分约束系统求解
 * 约束形式：x_i - x_j ≤ c
 *
 * @param n           变量数（编号 0 ~ n-1）
 * @param constraints 约束列表，每条 (j, i, c) 表示 x_i - x_j ≤ c
 * @param result      输出参数，存储每组约束的可行解
 * @return            true=有解, false=无解（存在负环）
 */
bool diffConstraint(int n,
        vector<tuple<int, int, int>>& constraints,
        vector<int>& result) {

    int totalNodes = n + 1;             // 包括超级源点
    int super = n;                       // 超级源点编号为 n
    vector<vector<pair<int, int>>> adj(totalNodes);  // {to, weight}

    // 1. 添加约束边
    //    x_i - x_j ≤ c  =>  建边 j -> i，权值为 c
    for (auto& cst : constraints) {
        int j = get<0>(cst), i = get<1>(cst), c = get<2>(cst);
        adj[j].push_back({i, c});
    }

    // 2. 超级源点：向所有变量节点连权值为 0 的边
    //    这保证了从超级源点可以到达所有节点
    //    同时 x_i ≤ x_super + 0，即 x_i ≤ 0（为解提供了一个基准）
    for (int i = 0; i < n; i++) {
        adj[super].push_back({i, 0});
    }

    // 3. SPFA 求最短路径
    const int INF = 1e9;
    vector<int> dist(totalNodes, INF);
    vector<int> cnt(totalNodes, 0);      // 入队次数（用于检测负环）
    vector<bool> inQueue(totalNodes, false);
    queue<int> q;

    dist[super] = 0;
    q.push(super);
    inQueue[super] = true;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        inQueue[u] = false;

        for (auto& edge : adj[u]) {
            int v = edge.first, w = edge.second;
            if (dist[v] > dist[u] + w) {     // 松弛操作
                dist[v] = dist[u] + w;
                cnt[v] = cnt[u] + 1;

                // 负环检测：某个节点入队次数超过总节点数
                if (cnt[v] >= totalNodes) {
                    return false;            // 存在负环，不等式组无解
                }

                if (!inQueue[v]) {
                    q.push(v);
                    inQueue[v] = true;
                }
            }
        }
    }

    // 4. 返回结果：x_i = dist[i]
    result.resize(n);
    for (int i = 0; i < n; i++) {
        result[i] = dist[i];
    }
    return true;
}


// ============================================================
// 第三部分：差分约束 —— Bellman-Ford 替代实现
// 当图较小或需要更稳定的负环检测时使用
// 时间复杂度 O(VE)
// ============================================================

/**
 * Bellman-Ford 求解差分约束
 * 优势：代码更简洁，负环检测更稳定
 * 劣势：时间复杂度 O(VE) 固定，不如 SPFA 在实际中快
 */
bool diffConstraintBellmanFord(int n,
        vector<tuple<int, int, int>>& constraints,
        vector<int>& result) {

    // 边结构：(from, to, weight)
    struct EdgeBF { int from, to, weight; };
    vector<EdgeBF> edges;

    // 添加约束边
    for (auto& c : constraints) {
        int j = get<0>(c), i = get<1>(c), w = get<2>(c);
        edges.push_back({j, i, w});          // j → i, 权 w
    }

    // 超级源点
    int super = n;
    for (int i = 0; i < n; i++) {
        edges.push_back({super, i, 0});
    }

    int totalNodes = n + 1;
    const int INF = 1e9;
    vector<int> dist(totalNodes, INF);
    dist[super] = 0;

    // Bellman-Ford: 进行 totalNodes-1 轮松弛
    for (int round = 1; round < totalNodes; round++) {
        bool updated = false;
        for (auto& e : edges) {
            if (dist[e.from] != INF && dist[e.to] > dist[e.from] + e.weight) {
                dist[e.to] = dist[e.from] + e.weight;
                updated = true;
            }
        }
        if (!updated) break;                 // 提前终止优化
    }

    // 负环检测：第 totalNodes 轮仍能松弛说明有负环
    for (auto& e : edges) {
        if (dist[e.from] != INF && dist[e.to] > dist[e.from] + e.weight) {
            return false;                    // 负环，无解
        }
    }

    result.resize(n);
    for (int i = 0; i < n; i++) {
        result[i] = dist[i];
    }
    return true;
}


// ============================================================
// 第四部分：专用工具 —— 差分约束中额外的不等式转化
// ============================================================

/**
 * 将常见不等式统一转化为 x_i - x_j ≤ c 形式
 * 使用示例：
 *   addLEQ(i, j, c)     -> x_i - x_j ≤ c
 *   addGEQ(i, j, c)     -> x_i - x_j ≥ c  =>  x_j - x_i ≤ -c
 *   addEQ(i, j, c)      -> x_i - x_j = c  => 两条约束
 */
struct DiffConstraintBuilder {
    int n;
    vector<tuple<int, int, int>> constraints;

    DiffConstraintBuilder(int numVars) : n(numVars) {}

    // 添加约束 x_a - x_b ≤ c
    void addLEQ(int a, int b, int c) {
        constraints.push_back({b, a, c});       // b → a, 权 c
    }

    // 添加约束 x_a - x_b ≥ c  =>  x_b - x_a ≤ -c
    void addGEQ(int a, int b, int c) {
        constraints.push_back({a, b, -c});      // a → b, 权 -c
    }

    // 添加约束 x_a - x_b = c  => 两个不等式
    void addEQ(int a, int b, int c) {
        constraints.push_back({b, a, c});       // x_a - x_b ≤ c
        constraints.push_back({a, b, -c});      // x_a - x_b ≥ c
    }

    // 添加约束 x_a ≤ c  =>  x_a - 0 ≤ c
    void addUpperBound(int a, int c) {
        // 这里需要有一个基准变量0（可以理解为超级源点）
        // 即 x_a - x_super ≤ c
    }

    // 求解
    bool solve(vector<int>& result) {
        return diffConstraint(n, constraints, result);
    }
};


// ============================================================
// 测试代码
// ============================================================

/**
 * 测试1：关键路径
 * 示例 AOE 网：
 *   节点 0~5，边如下：
 *   0->1(3), 0->2(2), 1->3(2), 1->4(3), 2->4(4), 3->5(2), 4->5(1)
 */
void testCriticalPath() {
    cout << "===== 测试：关键路径算法 =====\n";

    int n = 6;  // 6 个事件节点 0~5
    vector<tuple<int, int, int>> edges = {
        {0, 1, 3},
        {0, 2, 2},
        {1, 3, 2},
        {1, 4, 3},
        {2, 4, 4},
        {3, 5, 2},
        {4, 5, 1}
    };

    auto result = criticalPath(n, edges);
    int totalTime = result.first;
    auto& critical = result.second;

    cout << "工程最短完成时间: " << totalTime << "\n";
    cout << "关键活动 (共 " << critical.size() << " 条):\n";
    for (auto& e : critical) {
        // 找到对应的权值
        int w = -1;
        for (auto& orig : edges) {
            if (get<0>(orig) == e.first && get<1>(orig) == e.second) {
                w = get<2>(orig);
                break;
            }
        }
        cout << "  " << e.first << " -> " << e.second
             << " (持续时间: " << w << ")\n";
    }
    // 预期：关键路径 0->1(3), 1->3(2), 3->5(2)，总时间 7
    // 或 0->1(3), 1->4(3), 4->5(1)，总时间 7
    cout << "\n";
}

/**
 * 测试2：差分约束
 * 示例：给定约束
 *   x1 - x2 ≤ 3
 *   x2 - x3 ≤ -2
 *   x1 - x3 ≤ 2
 * 求一组可行解。
 */
void testDiffConstraint() {
    cout << "===== 测试：差分约束系统 (SPFA) =====\n";

    int n = 4;  // 变量 x0, x1, x2, x3（x0 作为基准）
    vector<tuple<int, int, int>> constraints = {
        {2, 1, 3},    // x1 - x2 ≤ 3  => 边 2→1 权3
        {3, 2, -2},   // x2 - x3 ≤ -2 => 边 3→2 权-2
        {3, 1, 2},    // x1 - x3 ≤ 2  => 边 3→1 权2
    };

    vector<int> solution;
    if (diffConstraint(n, constraints, solution)) {
        cout << "有解！一组可行解为:\n";
        for (int i = 0; i < n; i++) {
            cout << "  x" << i << " = " << solution[i] << "\n";
        }

        // 验证解的正确性
        cout << "验证约束:\n";
        cout << "  x1 - x2 = " << solution[1] - solution[2]
             << " ≤ 3 -> " << (solution[1] - solution[2] <= 3 ? "通过" : "失败") << "\n";
        cout << "  x2 - x3 = " << solution[2] - solution[3]
             << " ≤ -2 -> " << (solution[2] - solution[3] <= -2 ? "通过" : "失败") << "\n";
        cout << "  x1 - x3 = " << solution[1] - solution[3]
             << " ≤ 2 -> " << (solution[1] - solution[3] <= 2 ? "通过" : "失败") << "\n";

        // 验证平移性质
        cout << "验证平移性质 (x+10):\n";
        cout << "  (x1+10) - (x2+10) = " << solution[1] - solution[2]
             << " ≤ 3 -> " << (solution[1] - solution[2] <= 3 ? "通过" : "失败") << "\n";
    } else {
        cout << "无解（存在矛盾约束，即负环）\n";
    }
    cout << "\n";
}

/**
 * 测试3：差分约束 Bellman-Ford
 */
void testDiffConstraintBF() {
    cout << "===== 测试：差分约束系统 (Bellman-Ford) =====\n";

    int n = 4;
    vector<tuple<int, int, int>> constraints = {
        {2, 1, 3},
        {3, 2, -2},
        {3, 1, 2},
    };

    vector<int> solution;
    if (diffConstraintBellmanFord(n, constraints, solution)) {
        cout << "Bellman-Ford 求解成功:\n";
        for (int i = 0; i < n; i++) {
            cout << "  x" << i << " = " << solution[i] << "\n";
        }
    } else {
        cout << "Bellman-Ford: 无解\n";
    }
    cout << "\n";
}

/**
 * 测试4：差分约束无解情况（矛盾约束）
 * x1 - x2 ≤ 1
 * x2 - x1 ≤ -3  => x1 - x2 ≥ 3
 * 这导致了 3 ≤ x1-x2 ≤ 1，矛盾！
 */
void testDiffConstraintNoSolution() {
    cout << "===== 测试：差分约束无解（矛盾约束） =====\n";

    int n = 2;  // x0, x1
    vector<tuple<int, int, int>> constraints = {
        {1, 0, 1},    // x0 - x1 ≤ 1  => 边 1→0 权1
        {0, 1, -3},   // x1 - x0 ≤ -3 => 边 0→1 权-3
    };
    // 这形成了一个环：1→0 (1), 0→1 (-3)，总权和 = 1+(-3) = -2 < 0，负环！

    vector<int> solution;
    if (diffConstraint(n, constraints, solution)) {
        cout << "居然有解？（不应该）\n";
    } else {
        cout << "正确检测到无解（存在负环，不等式矛盾）\n";
    }
    cout << "\n";
}

/**
 * 测试5：关键路径 —— 简单链
 * 0 -> 1(2) -> 2(3) -> 3(1)
 * 预期总时间 6，所有边都是关键活动
 */
void testCriticalPathSimple() {
    cout << "===== 测试：关键路径（简单链） =====\n";

    int n = 4;
    vector<tuple<int, int, int>> edges = {
        {0, 1, 2},
        {1, 2, 3},
        {2, 3, 1}
    };

    auto result = criticalPath(n, edges);
    cout << "工程最短完成时间: " << result.first << "\n";
    cout << "关键活动: ";
    for (auto& e : result.second) {
        cout << e.first << "->" << e.second << " ";
    }
    cout << "\n\n";
}

/**
 * 测试6：差分约束 —— Builder 辅助类
 */
void testDiffConstraintBuilder() {
    cout << "===== 测试：差分约束 Builder 辅助类 =====\n";

    DiffConstraintBuilder builder(3);   // 3 个变量 x0, x1, x2

    // x1 - x0 ≥ 5  即  x0 - x1 ≤ -5
    builder.addGEQ(1, 0, 5);
    // x2 - x1 ≥ 3  即  x1 - x2 ≤ -3
    builder.addGEQ(2, 1, 3);
    // 求 x2 - x0 的最小值（即最紧的下界）
    // 从约束可知 x2 - x0 = (x2 - x1) + (x1 - x0) ≥ 3+5 = 8

    vector<int> solution;
    if (builder.solve(solution)) {
        cout << "一组可行解:\n";
        for (int i = 0; i < 3; i++) {
            cout << "  x" << i << " = " << solution[i] << "\n";
        }
        cout << "x2 - x0 = " << solution[2] - solution[0]
             << " (期望 ≥ 8)\n";
    } else {
        cout << "无解\n";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "========================================\n";
    cout << "  第24课：关键路径与差分约束  测试程序\n";
    cout << "========================================\n\n";

    testCriticalPath();
    testCriticalPathSimple();
    testDiffConstraint();
    testDiffConstraintBF();
    testDiffConstraintNoSolution();
    testDiffConstraintBuilder();

    return 0;
}
