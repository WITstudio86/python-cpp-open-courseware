/**
 * 第23课：拓扑排序
 *
 * 包含以下实现：
 * 1. Kahn算法（BFS + 入度表）—— 最常用的拓扑排序算法
 * 2. DFS拓扑排序（后序遍历逆序 + 三色标记判环）
 * 3. 字典序最小拓扑序（优先队列优化）
 * 4. DAG判环（两种方法）
 * 5. LeetCode 207 课程表I（判环）
 * 6. LeetCode 210 课程表II（输出拓扑序）
 *
 * 所有代码均可AC通过对应题目。
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

// ============================================================
// 方法一：Kahn算法（BFS + 入度表）
// 时间复杂度 O(V+E)，空间复杂度 O(V+E)
// 这是最常用的拓扑排序算法
// ============================================================

/**
 * Kahn算法求拓扑排序
 * @param n      节点数量（编号 0 ~ n-1）
 * @param edges  边列表，每条边为 [u, v] 表示 u -> v
 * @return       拓扑序列；若存在环则返回空 vector
 */
vector<int> kahnTopologicalSort(int n, vector<vector<int>>& edges) {
    // 1. 建立邻接表
    vector<vector<int>> adj(n);
    // 2. 统计每个节点的入度
    vector<int> indegree(n, 0);
    for (auto& e : edges) {
        int u = e[0], v = e[1];      // 边 u -> v
        adj[u].push_back(v);          // 邻接表记录出边
        indegree[v]++;                // v 的入度 +1
    }

    // 3. 将所有入度为 0 的节点加入队列（多源BFS的初始化）
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    // 4. BFS 处理，维护拓扑序列
    vector<int> topoOrder;            // 存储拓扑排序结果
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topoOrder.push_back(u);       // 将当前节点加入拓扑序列

        // 遍历 u 的所有出边邻接点
        for (int v : adj[u]) {
            indegree[v]--;            // 「删除」边 u->v，v 入度减 1
            if (indegree[v] == 0) {   // v 的前置依赖全部完成
                q.push(v);            // v 可以入队处理
            }
        }
    }

    // 5. 判环：若拓扑序列长度 < n，说明存在环（无法拓扑排序）
    if ((int)topoOrder.size() < n) {
        return {};                    // 有环，返回空序列
    }
    return topoOrder;
}


// ============================================================
// 方法二：DFS拓扑排序（后序遍历逆序 + 三色标记判环）
// 时间复杂度 O(V+E)，空间复杂度 O(V+E)
// 核心思想：后序遍历意味着子节点先于父节点，反转后即拓扑序
// ============================================================

/**
 * DFS递归函数（三色标记法）
 * @param u       当前访问节点
 * @param adj     邻接表
 * @param state   状态数组：0=未访问, 1=访问中(在递归栈中), 2=已完成
 * @param result  存储后序遍历结果（需要 reverse 才得到拓扑序）
 * @return        是否无环（true=无环，false=发现环）
 */
bool dfsTopo(int u, vector<vector<int>>& adj, vector<int>& state, vector<int>& result) {
    state[u] = 1;                           // 标记为「正在访问」

    for (int v : adj[u]) {                  // 遍历所有邻接点（后继节点）
        if (state[v] == 1) {                // 遇到正在递归栈中的节点
            return false;                   // 发现后向边，即存在环
        }
        if (state[v] == 0) {                // 未访问过的节点
            if (!dfsTopo(v, adj, state, result)) {
                return false;               // 子节点发现环，向上传递
            }
        }
        // state[v] == 2 的情况：已完成的节点，无需处理
    }

    state[u] = 2;                           // 标记为「已完成」
    result.push_back(u);                    // 后序遍历位置：子节点都处理完后才加入
    return true;
}

/**
 * DFS方法求拓扑排序
 * @return 拓扑序列；若存在环则返回空 vector
 */
vector<int> dfsTopologicalSort(int n, vector<vector<int>>& edges) {
    // 1. 建立邻接表
    vector<vector<int>> adj(n);
    for (auto& e : edges) {
        adj[e[0]].push_back(e[1]);          // 边 u -> v
    }

    // 2. DFS 遍历
    vector<int> state(n, 0);                // 三色标记：0未访问 1访问中 2已完成
    vector<int> result;                     // 后序遍历结果

    for (int i = 0; i < n; i++) {
        if (state[i] == 0) {                // 对每个未访问节点启动DFS
            if (!dfsTopo(i, adj, state, result)) {
                return {};                  // 发现环，返回空
            }
        }
    }

    // 3. 后序遍历的逆序 = 拓扑排序
    reverse(result.begin(), result.end());
    return result;
}


// ============================================================
// 方法三：字典序最小拓扑序（优先队列）
// 时间复杂度 O(V log V + E)，空间复杂度 O(V+E)
// 应用场景：需要输出编号最小的合法拓扑序列
// ============================================================

/**
 * 求字典序最小的拓扑序列
 * 通过将普通队列替换为小根堆（优先队列）实现
 */
vector<int> minLexicalTopoSort(int n, vector<vector<int>>& edges) {
    vector<vector<int>> adj(n);
    vector<int> indegree(n, 0);
    for (auto& e : edges) {
        int u = e[0], v = e[1];
        adj[u].push_back(v);
        indegree[v]++;
    }

    // 【关键】使用小根堆代替普通队列
    // greater<int> 使得堆顶始终是最小的元素
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0) {
            pq.push(i);
        }
    }

    vector<int> result;
    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();
        result.push_back(u);                // 当前最小的入度为0节点

        for (int v : adj[u]) {
            indegree[v]--;
            if (indegree[v] == 0) {
                pq.push(v);
            }
        }
    }

    if ((int)result.size() < n) return {};  // 有环
    return result;
}


// ============================================================
// 方法四：DAG判环（独立判环函数，不关心拓扑序列）
// 使用 Kahn 算法判断是否为 DAG
// ============================================================

/**
 * 判断有向图是否包含环
 * @return true=无环（是DAG），false=有环
 */
bool isDAG(int n, vector<vector<int>>& edges) {
    vector<vector<int>> adj(n);
    vector<int> indegree(n, 0);
    for (auto& e : edges) {
        adj[e[0]].push_back(e[1]);
        indegree[e[1]]++;
    }

    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0) q.push(i);
    }

    int processed = 0;                      // 已处理节点计数
    while (!q.empty()) {
        int u = q.front(); q.pop();
        processed++;
        for (int v : adj[u]) {
            if (--indegree[v] == 0) {
                q.push(v);
            }
        }
    }

    return processed == n;                  // 全部处理完 = 无环
}


// ============================================================
// 经典问题一：课程表 I（LeetCode 207）
// 判断是否可以完成所有课程
// 本质：判断有向图是否为 DAG
// ============================================================

/**
 * LeetCode 207: 课程表
 * @param numCourses    课程总数 n
 * @param prerequisites 先修关系 [a, b] 表示先学 b 才能学 a (b -> a)
 * @return              是否能完成所有课程
 */
bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    int n = numCourses;
    vector<vector<int>> adj(n);
    vector<int> indegree(n, 0);

    // 建图：学完 b 才能学 a，即 b -> a
    for (auto& p : prerequisites) {
        int a = p[0], b = p[1];             // a 依赖 b
        adj[b].push_back(a);                // b -> a
        indegree[a]++;
    }

    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0) q.push(i);
    }

    int completed = 0;
    while (!q.empty()) {
        int course = q.front(); q.pop();
        completed++;
        for (int next : adj[course]) {
            if (--indegree[next] == 0) {
                q.push(next);
            }
        }
    }

    return completed == n;                  // 能修完所有课 = 无环
}


// ============================================================
// 经典问题二：课程表 II（LeetCode 210）
// 返回任意一个可行的课程学习顺序
// 本质：求拓扑排序
// ============================================================

/**
 * LeetCode 210: 课程表 II
 * @param numCourses    课程总数 n
 * @param prerequisites 先修关系 [a, b] 表示先学 b 才能学 a (b -> a)
 * @return              任意一个合法的学习顺序，若不可行则返回空数组
 */
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    int n = numCourses;
    vector<vector<int>> adj(n);
    vector<int> indegree(n, 0);

    for (auto& p : prerequisites) {
        int a = p[0], b = p[1];
        adj[b].push_back(a);
        indegree[a]++;
    }

    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0) q.push(i);
    }

    vector<int> order;
    while (!q.empty()) {
        int course = q.front(); q.pop();
        order.push_back(course);
        for (int next : adj[course]) {
            if (--indegree[next] == 0) {
                q.push(next);
            }
        }
    }

    if ((int)order.size() == n) return order;
    return {};                              // 有环，无法完成
}


// ============================================================
// 测试代码
// ============================================================

int main() {
    // ---------- 测试1：Kahn算法基本拓扑排序 ----------
    cout << "===== 测试1：Kahn算法 =====\n";
    {
        int n = 6;  // 节点 0~5
        // 边: 5->2, 5->0, 4->0, 4->1, 2->3, 3->1
        vector<vector<int>> edges = {{5,2}, {5,0}, {4,0}, {4,1}, {2,3}, {3,1}};
        vector<int> result = kahnTopologicalSort(n, edges);
        cout << "拓扑序列: ";
        for (int x : result) cout << x << " ";
        cout << "\n";
        // 预期输出一种合法序列（如 4 5 0 2 3 1）
    }

    // ---------- 测试2：DFS拓扑排序 ----------
    cout << "\n===== 测试2：DFS拓扑排序 =====\n";
    {
        int n = 6;
        vector<vector<int>> edges = {{5,2}, {5,0}, {4,0}, {4,1}, {2,3}, {3,1}};
        vector<int> result = dfsTopologicalSort(n, edges);
        cout << "拓扑序列: ";
        for (int x : result) cout << x << " ";
        cout << "\n";
        // 预期输出一种合法序列（如 5 4 2 3 1 0）
    }

    // ---------- 测试3：字典序最小拓扑序 ----------
    cout << "\n===== 测试3：字典序最小拓扑序 =====\n";
    {
        int n = 6;
        vector<vector<int>> edges = {{5,2}, {5,0}, {4,0}, {4,1}, {2,3}, {3,1}};
        vector<int> result = minLexicalTopoSort(n, edges);
        cout << "字典序最小拓扑序列: ";
        for (int x : result) cout << x << " ";
        cout << "\n";
        // 预期输出：4 5 0 2 3 1（字典序最小）
    }

    // ---------- 测试4：DAG判环 ----------
    cout << "\n===== 测试4：DAG判环 =====\n";
    {
        // 无环图
        int n1 = 4;
        vector<vector<int>> edges1 = {{0,1}, {1,2}, {2,3}};
        cout << "无环图判环结果: " << (isDAG(n1, edges1) ? "DAG (无环)" : "有环") << "\n";

        // 有环图：0->1->2->0
        int n2 = 3;
        vector<vector<int>> edges2 = {{0,1}, {1,2}, {2,0}};
        cout << "有环图判环结果: " << (isDAG(n2, edges2) ? "DAG (无环)" : "有环") << "\n";
    }

    // ---------- 测试5：课程表 I（207） ----------
    cout << "\n===== 测试5：课程表 I =====\n";
    {
        // 示例1：2门课，[[1,0]]，可以完成
        int n1 = 2;
        vector<vector<int>> pre1 = {{1,0}};
        cout << "示例1 (可行): " << (canFinish(n1, pre1) ? "可以完成" : "无法完成") << "\n";

        // 示例2：2门课，[[1,0],[0,1]]，无法完成（0和1互为前置）
        int n2 = 2;
        vector<vector<int>> pre2 = {{1,0}, {0,1}};
        cout << "示例2 (有环): " << (canFinish(n2, pre2) ? "可以完成" : "无法完成") << "\n";
    }

    // ---------- 测试6：课程表 II（210） ----------
    cout << "\n===== 测试6：课程表 II =====\n";
    {
        // 示例1：4门课，[[1,0],[2,0],[3,1],[3,2]]
        int n1 = 4;
        vector<vector<int>> pre1 = {{1,0}, {2,0}, {3,1}, {3,2}};
        vector<int> order = findOrder(n1, pre1);
        cout << "学习顺序: ";
        for (int x : order) cout << x << " ";
        cout << "\n";
        // 预期输出一种合法序列（如 0 1 2 3 或 0 2 1 3）

        // 示例2：1门课，无边
        int n2 = 1;
        vector<vector<int>> pre2 = {};
        vector<int> order2 = findOrder(n2, pre2);
        cout << "单门课顺序: ";
        for (int x : order2) cout << x << " ";
        cout << "\n";
    }

    return 0;
}
