/*
 * 第44课：最小生成树入门
 * 日期：2026-06-27
 * 内容：Prim 算法 + Kruskal 算法（含并查集实现）
 * 例题1：修路问题（Prim）
 * 例题2：连接所有城市（Kruskal）
 */

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 105;
const int MAXM = 10005;
const int INF = 0x3f3f3f3f;  // 一个很大的数，当作「无穷大」

// ==================== Prim 算法 ====================

/**
 * Prim 算法（加点法）—— 求最小生成树
 *
 * 核心思想：
 *   1. 从一个起点开始，维护一个「已加入 MST 的节点集合」
 *   2. 每次选择一条连接「已加入」和「未加入」节点中权值最小的边
 *   3. 把这条边另一端的节点加入 MST
 *   4. 重复步骤 2-3，直到所有节点都加入
 *
 * 形象理解：就像一棵小树苗，每次都从「树」的边缘
 *           找一条最短的枝干往外生长
 *
 * 时间复杂度：O(V^2)，适合稠密图
 */

int g_prim[MAXN][MAXN];    // 邻接矩阵存储图
int dis[MAXN];              // dis[i]：节点 i 到当前 MST 的最短距离
bool inMST[MAXN];           // inMST[i]：节点 i 是否已在 MST 中
int n_prim, m_prim;         // n 个节点，m 条边

int prim() {
    // 第一步：初始化
    memset(dis, 0x3f, sizeof(dis));   // 所有节点到 MST 的距离设为无穷大
    memset(inMST, 0, sizeof(inMST));  // 所有节点初始都不在 MST 中
    dis[1] = 0;                        // 从节点 1 开始构建 MST
    int totalWeight = 0;               // MST 的总权值

    // 第二步：循环 n 次，每次加入一个节点
    for (int i = 1; i <= n_prim; i++) {
        // 在「未加入 MST」的节点中，找出距离 MST 最近的节点 u
        int u = -1;
        int minDis = INF;
        for (int j = 1; j <= n_prim; j++) {
            if (!inMST[j] && dis[j] < minDis) {
                minDis = dis[j];
                u = j;
            }
        }

        // 如果找不到（图不连通），返回 -1
        if (u == -1) return -1;

        // 将 u 加入 MST
        inMST[u] = true;
        totalWeight += dis[u];  // 累加这条边的权值

        // 用新加入的节点 u 更新其他节点到 MST 的距离
        // 如果节点 v 还未加入，且边 u-v 比 dis[v] 更短，则更新
        for (int v = 1; v <= n_prim; v++) {
            if (!inMST[v] && g_prim[u][v] < dis[v]) {
                dis[v] = g_prim[u][v];
            }
        }
    }
    return totalWeight;
}

// 例题1：修路问题
void solve_problem1() {
    cout << "\n========== 例题1：修路问题（Prim 算法）==========\n";
    cout << "题目：N 个村庄，M 条可选道路。求使所有村庄连通的最少总成本。\n\n";

    // 初始化邻接矩阵（全设为 INF）
    memset(g_prim, 0x3f, sizeof(g_prim));

    // 输入
    cout << "请输入 N 和 M（如：4 5）：";
    cin >> n_prim >> m_prim;

    cout << "请输入 " << m_prim << " 条边（每行：u v w）：\n";
    for (int i = 0; i < m_prim; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        // 处理重边：保留最小值
        if (w < g_prim[u][v]) {
            g_prim[u][v] = g_prim[v][u] = w;
        }
    }

    // 运行 Prim
    int result = prim();

    // 输出结果
    if (result == -1) {
        cout << "\n结果：无法使所有村庄连通！（图不连通）\n";
    } else {
        cout << "\n使所有村庄连通的最少总成本：" << result << endl;
    }
    cout << endl;
}

// ==================== Kruskal 算法 + 并查集 ====================

/**
 * Kruskal 算法（加边法）—— 求最小生成树
 *
 * 核心思想：
 *   1. 将所有边按权值从小到大排序
 *   2. 按顺序考虑每条边：
 *      - 如果这条边的两个端点不在同一个集合中（不会形成环），则选取这条边
 *      - 否则跳过
 *   3. 直到选取了 N-1 条边
 *
 * 关键数据结构：并查集（Union-Find）
 *   - Find(x)：找到 x 所在集合的根节点（祖宗）
 *   - Unite(x, y)：合并 x 和 y 所在的集合
 *   - 通过「路径压缩」优化，使得操作近乎 O(1)
 *
 * 时间复杂度：O(E log E)，主要由排序决定
 */

// 边的结构体
struct Edge {
    int u, v, w;   // 起点、终点、权值

    // 重载 < 运算符，方便 sort 按权值升序排序
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

Edge edges[MAXM];          // 存储所有边
int parent[MAXN];          // 并查集：parent[x] = x 所在集合的父节点
int n_kruskal, m_kruskal;  // n 个节点，m 条边

/**
 * 并查集 —— 查找操作（带路径压缩）
 *
 * 路径压缩原理：在查找的过程中，将沿途的每个节点都直接
 * 连接到根节点上，使得下次查找更快。
 *
 * 例子：parent = {1:2, 2:3, 3:3} 表示 1→2→3（3 是根）
 *   find(1) 会先递归 find(2)，再递归 find(3)，返回 3
 *   同时把 parent[1] 和 parent[2] 都直接设为 3
 *   下次 find(1) 就直接返回 3 了！
 */
int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);  // 递归查找 + 路径压缩
    }
    return parent[x];
}

/**
 * 并查集 —— 合并操作
 * 将 a 和 b 所在的集合合并
 * 返回 true 表示合并成功（原来不在同一集合）
 * 返回 false 表示已在同一集合（不需要合并，加入会形成环）
 */
bool unite(int a, int b) {
    int rootA = find(a);
    int rootB = find(b);
    if (rootA == rootB) return false;  // 已在同一集合，不可合并
    parent[rootA] = rootB;              // 将 rootA 接在 rootB 下面
    return true;
}

/**
 * Kruskal 算法主函数
 * 返回 MST 的总权值，如果图不连通则返回 -1
 */
int kruskal() {
    // 第一步：初始化并查集（每个节点自成一个集合）
    for (int i = 1; i <= n_kruskal; i++) {
        parent[i] = i;
    }

    // 第二步：将所有边按权值从小到大排序
    sort(edges, edges + m_kruskal);

    // 第三步：贪心选边
    int totalWeight = 0;  // MST 的总权值
    int chosenCount = 0;  // 已选择的边数

    for (int i = 0; i < m_kruskal; i++) {
        // 尝试合并这条边的两个端点
        if (unite(edges[i].u, edges[i].v)) {
            // 合并成功 → 选中这条边
            totalWeight += edges[i].w;
            chosenCount++;

            // 如果已经选了 N-1 条边，MST 构建完成！
            if (chosenCount == n_kruskal - 1) break;
        }
        // 合并失败 → 两个端点已连通，选它会形成环 → 跳过
    }

    // 如果选了 N-1 条边，说明图连通；否则不连通
    return (chosenCount == n_kruskal - 1) ? totalWeight : -1;
}

// 例题2：连接所有城市（含输出选中边）
void solve_problem2() {
    cout << "\n========== 例题2：连接所有城市（Kruskal 算法）==========\n";
    cout << "题目：N 座城市，M 条可选光纤线路。求最小总成本并输出选中的线路。\n\n";

    // 输入
    cout << "请输入 N 和 M（如：5 7）：";
    cin >> n_kruskal >> m_kruskal;

    cout << "请输入 " << m_kruskal << " 条边（每行：u v w）：\n";
    for (int i = 0; i < m_kruskal; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    // 初始化并查集
    for (int i = 1; i <= n_kruskal; i++) {
        parent[i] = i;
    }

    // 排序
    sort(edges, edges + m_kruskal);

    // 记录选中的边
    int chosen[MAXN][2];  // chosen[i][0] 和 chosen[i][1] 表示第 i 条选中边的两个端点
    int chosenCount = 0;
    int totalWeight = 0;

    cout << "\n选边过程：\n";
    for (int i = 0; i < m_kruskal; i++) {
        int u = edges[i].u, v = edges[i].v, w = edges[i].w;
        if (unite(u, v)) {
            totalWeight += w;
            chosen[chosenCount][0] = u;
            chosen[chosenCount][1] = v;
            chosenCount++;
            cout << "  选中边 " << u << "-" << v << " (权值 " << w << ")，已选 " << chosenCount << "/" << n_kruskal - 1 << endl;
            if (chosenCount == n_kruskal - 1) break;
        } else {
            cout << "  跳过边 " << u << "-" << v << " (权值 " << w << ")，会形成环\n";
        }
    }

    // 输出结果
    cout << "\n-------------------------------------------\n";
    if (chosenCount != n_kruskal - 1) {
        cout << "结果：无法连接所有城市！（图不连通）\n";
    } else {
        cout << "最小总成本：" << totalWeight << endl;
        cout << "选中的线路（共 " << chosenCount << " 条）：\n";
        for (int i = 0; i < chosenCount; i++) {
            cout << "  线路 " << (i + 1) << "：连接城市 " << chosen[i][0] << " 和 " << chosen[i][1] << endl;
        }
    }
    cout << endl;
}

// ==================== 测试用例自动演示 ====================

void run_test_cases() {
    cout << "\n========== 自动测试用例演示 ==========\n";

    // ---- 测试 Prim ----
    cout << "\n--- Prim 测试（修路问题）---\n";
    cout << "图结构（4 个村庄，5 条可选道路）：\n";
    cout << "  道路：1-2(2), 1-3(3), 1-4(4), 2-3(1), 3-4(5)\n";

    n_prim = 4; m_prim = 5;
    memset(g_prim, 0x3f, sizeof(g_prim));
    int test_edges_prim[5][3] = {
        {1,2,2}, {1,3,3}, {1,4,4}, {2,3,1}, {3,4,5}
    };
    for (int i = 0; i < 5; i++) {
        int u = test_edges_prim[i][0], v = test_edges_prim[i][1], w = test_edges_prim[i][2];
        g_prim[u][v] = g_prim[v][u] = w;
    }

    int ans = prim();
    if (ans == -1)
        cout << "结果：图不连通！\n";
    else
        cout << "最小总成本：" << ans << "（预期：7）\n";

    // ---- 测试 Kruskal ----
    cout << "\n--- Kruskal 测试（连接所有城市）---\n";
    cout << "图结构（5 个城市，7 条光纤线路）：\n";
    cout << "  线路：1-2(3), 1-4(5), 2-3(1), 2-4(2), 3-4(4), 3-5(6), 4-5(7)\n";

    n_kruskal = 5; m_kruskal = 7;
    int test_edges_kru[7][3] = {
        {1,2,3}, {1,4,5}, {2,3,1}, {2,4,2}, {3,4,4}, {3,5,6}, {4,5,7}
    };
    for (int i = 0; i < 7; i++) {
        edges[i].u = test_edges_kru[i][0];
        edges[i].v = test_edges_kru[i][1];
        edges[i].w = test_edges_kru[i][2];
    }

    ans = kruskal();
    if (ans == -1)
        cout << "结果：图不连通！\n";
    else
        cout << "最小总成本：" << ans << "（预期：12）\n";

    cout << "\n说明：Kruskal 和 Prim 对同一张图求出的 MST 总权值相同！\n";
    cout << endl;
}

// ==================== 主菜单 ====================

int main() {
    cout << "===========================================\n";
    cout << "   第44课：最小生成树入门 - 算法演示程序\n";
    cout << "   日期：2026-06-27\n";
    cout << "===========================================\n";
    cout << "本程序包含：\n";
    cout << "  1. Prim 算法实现（加点法）\n";
    cout << "  2. Kruskal 算法实现（加边法 + 并查集）\n";
    cout << "  3. 例题1：修路问题（Prim）\n";
    cout << "  4. 例题2：连接所有城市（Kruskal）\n";
    cout << "  5. 自动测试用例演示\n";

    int choice;
    do {
        cout << "\n-------------------------------------------\n";
        cout << "请选择功能：\n";
        cout << "  1 - 例题1：修路问题（Prim，手动输入）\n";
        cout << "  2 - 例题2：连接所有城市（Kruskal，手动输入）\n";
        cout << "  3 - 自动测试用例演示\n";
        cout << "  0 - 退出程序\n";
        cout << "请输入你的选择：";

        cin >> choice;

        switch (choice) {
            case 1:
                solve_problem1();
                break;
            case 2:
                solve_problem2();
                break;
            case 3:
                run_test_cases();
                break;
            case 0:
                cout << "感谢使用！再见！\n";
                break;
            default:
                cout << "输入无效，请重新选择！\n";
        }
    } while (choice != 0);

    return 0;
}
