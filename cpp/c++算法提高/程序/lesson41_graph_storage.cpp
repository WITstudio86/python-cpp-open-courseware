/*
 * ================================================================
 * C++算法提高 第41课：图的认识与存储
 * ================================================================
 *
 * 算法知识点：
 *   - 图的基本概念：顶点、边、有向图/无向图、带权图
 *   - 邻接矩阵存储：二维数组，O(1)查边，O(V²)空间
 *   - 邻接表存储：vector 数组，O(degree)查边，O(V+E)空间
 *   - 链式前向星：邻接表的数组高效实现
 *
 * 经典例题：
 *   例题1 - 朋友关系存储：邻接矩阵建图，输出所有朋友对
 *   例题2 - 度数统计：邻接表建图，统计每个顶点的度数
 */

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 101;   // 最大顶点数
const int MAXM = 10001; // 最大边数

// ================================================================
// 实现1：邻接矩阵存储
//   - 用二维 int 数组存储
//   - adjMat[i][j] = 1 表示顶点 i 到 j 有边
//   - 无向图：adjMat[i][j] == adjMat[j][i]（对称）
//   - 带权图：adjMat[i][j] = w 表示边的权重
// ================================================================
class Graph {
private:
    int adjMat[MAXN][MAXN];  // 邻接矩阵
    int n;                   // 顶点数

public:
    // 构造函数：初始化矩阵为 0
    Graph(int vertices = 0) {
        n = vertices;
        memset(adjMat, 0, sizeof(adjMat));
    }

    // 设置顶点数
    void setVertices(int vertices) {
        n = vertices;
        memset(adjMat, 0, sizeof(adjMat));
    }

    // 添加无向边（对称赋值）
    void addEdge(int u, int v) {
        if (u < 1 || u > n || v < 1 || v > n) {
            cout << "错误：顶点编号超出范围！" << endl;
            return;
        }
        adjMat[u][v] = 1;
        adjMat[v][u] = 1;  // 无向图对称
    }

    // 添加有向边 u → v
    void addDirectedEdge(int u, int v) {
        if (u < 1 || u > n || v < 1 || v > n) return;
        adjMat[u][v] = 1;
    }

    // 添加带权边（无向）
    void addWeightedEdge(int u, int v, int w) {
        if (u < 1 || u > n || v < 1 || v > n) return;
        adjMat[u][v] = w;
        adjMat[v][u] = w;
    }

    // 判断 u 和 v 是否相邻
    bool isAdjacent(int u, int v) {
        if (u < 1 || u > n || v < 1 || v > n) return false;
        return adjMat[u][v] != 0;
    }

    // 获取顶点 u 的度数（无向图中与 u 相连的边数）
    int getDegree(int u) {
        if (u < 1 || u > n) return 0;
        int deg = 0;
        for (int v = 1; v <= n; v++) {
            if (adjMat[u][v] != 0) deg++;
        }
        return deg;
    }

    // 打印完整的邻接矩阵
    void printMatrix() {
        cout << endl;
        cout << "邻接矩阵 (" << n << " × " << n << "):" << endl;
        cout << "   ";
        for (int j = 1; j <= n; j++) {
            cout << j << " ";
        }
        cout << endl;

        // 顶部分隔线
        cout << "  ┌─";
        for (int j = 1; j < n; j++) cout << "──";
        cout << "─┐" << endl;

        for (int i = 1; i <= n; i++) {
            cout << i << " │ ";
            for (int j = 1; j <= n; j++) {
                cout << adjMat[i][j] << " ";
            }
            cout << "│" << endl;
        }

        // 底部分隔线
        cout << "  └─";
        for (int j = 1; j < n; j++) cout << "──";
        cout << "─┘" << endl;
    }
};

// ================================================================
// 实现2：邻接表存储
//   - 用 vector<int> 数组存储
//   - adj[u] 包含顶点 u 的所有邻居
//   - 空间复杂度 O(V + E)，适合稀疏图
// ================================================================
vector<int> adjList[MAXN];  // 全局邻接表

// 添加无向边
void addEdgeList(int u, int v) {
    adjList[u].push_back(v);
    adjList[v].push_back(u);
}

// 打印邻接表
void printAdjList(int n) {
    cout << endl;
    cout << "邻接表：" << endl;
    for (int i = 1; i <= n; i++) {
        cout << i << " → ";
        if (adjList[i].empty()) {
            cout << "(无邻居)";
        } else {
            for (size_t j = 0; j < adjList[i].size(); j++) {
                cout << adjList[i][j];
                if (j < adjList[i].size() - 1) cout << " → ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

// ================================================================
// 实现3：链式前向星（进阶）
//   - 邻接表的数组实现，常数更小
//   - head[u] 指向 u 的第一条边
//   - edge[i].next 指向下一条边
// ================================================================
struct Edge {
    int to;      // 边的终点
    int next;    // 同起点下一条边的编号
    int w;       // 边权（可选）
};

Edge edges[MAXM];      // 边数组
int head[MAXN];        // head[u] 指向从 u 出发的第一条边
int edgeCnt = 0;       // 边计数器

// 初始化链式前向星
void initForwardStar() {
    memset(head, -1, sizeof(head));
    edgeCnt = 0;
}

// 链式前向星添加边（有向边 u → v，带权 w）
void addEdgeFS(int u, int v, int w = 1) {
    edgeCnt++;
    edges[edgeCnt].to = v;
    edges[edgeCnt].w = w;
    edges[edgeCnt].next = head[u];  // 新边插入链表头部
    head[u] = edgeCnt;
}

// 添加无向边（调用两次 addEdgeFS）
void addUndirectedEdgeFS(int u, int v, int w = 1) {
    addEdgeFS(u, v, w);
    addEdgeFS(v, u, w);
}

// 遍历顶点 u 的所有邻居（链式前向星）
void traverseNeighborsFS(int u) {
    cout << "顶点 " << u << " 的邻居（链式前向星）：";
    for (int i = head[u]; i != -1; i = edges[i].next) {
        cout << edges[i].to << " ";
    }
    cout << endl;
}

// ================================================================
// 例题1：朋友关系存储（邻接矩阵）
// 题目：输入 N 个人和 M 对朋友关系，使用邻接矩阵存储，
//       输出所有朋友对（只输出 u < v，避免重复）。
// ================================================================
void example1_friends() {
    cout << "══════════════════════════════════════" << endl;
    cout << "  例题1：朋友关系存储（邻接矩阵）" << endl;
    cout << "══════════════════════════════════════" << endl;

    int N, M;
    cout << "请输入人数 N 和关系对数 M（如 5 4）：" << endl;
    cout << "（输入 5 4 使用样例数据）→ ";
    cin >> N >> M;

    Graph g(N);

    cout << "请输入 " << M << " 对朋友关系（每行两个整数 u v）：" << endl;
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    // 打印邻接矩阵
    g.printMatrix();

    // 输出所有朋友对
    cout << endl;
    cout << "所有朋友对（u < v）：" << endl;
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            if (g.isAdjacent(i, j)) {
                cout << "  " << i << " ←→ " << j << endl;
            }
        }
    }

    // 输出每个人的度数
    cout << endl;
    cout << "每个人的朋友数（度数）：" << endl;
    for (int i = 1; i <= N; i++) {
        cout << "  人" << i << "：" << g.getDegree(i) << " 个朋友" << endl;
    }
    cout << endl;
}

// ================================================================
// 例题2：度数统计（邻接表）
// 题目：输入一个无向图，使用邻接表存储，计算每个顶点的度数。
// ================================================================
void example2_degreeCount() {
    cout << "══════════════════════════════════════" << endl;
    cout << "  例题2：度数统计（邻接表）" << endl;
    cout << "══════════════════════════════════════" << endl;

    // 清空邻接表
    for (int i = 0; i < MAXN; i++) {
        adjList[i].clear();
    }

    int N, M;
    cout << "请输入顶点数 N 和边数 M（如 4 5）：" << endl;
    cout << "（输入 4 5 使用样例数据）→ ";
    cin >> N >> M;

    cout << "请输入 " << M << " 条边（每行两个整数 u v）：" << endl;
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        addEdgeList(u, v);
    }

    // 打印邻接表
    printAdjList(N);

    // 统计度数
    cout << "各顶点的度数：" << endl;
    cout << "────────────────" << endl;
    for (int i = 1; i <= N; i++) {
        int degree = (int)adjList[i].size();
        cout << "  顶点 " << i << " 的度数：" << degree;

        // 可视化：用 * 表示度数
        cout << "  ";
        for (int j = 0; j < degree; j++) cout << "■";
        cout << endl;
    }
    cout << endl;

    // 找出度数最大和最小的顶点
    int maxDeg = 0, minDeg = MAXN;
    int maxV = 1, minV = 1;
    for (int i = 1; i <= N; i++) {
        int d = (int)adjList[i].size();
        if (d > maxDeg) { maxDeg = d; maxV = i; }
        if (d < minDeg) { minDeg = d; minV = i; }
    }
    cout << "度数最大的顶点：" << maxV << "（度数为 " << maxDeg << "）" << endl;
    cout << "度数最小的顶点：" << minV << "（度数为 " << minDeg << "）" << endl;
    cout << endl;
}

// ================================================================
// 演示3：链式前向星
// ================================================================
void demo_forwardStar() {
    cout << "══════════════════════════════════════" << endl;
    cout << "  演示：链式前向星 " << endl;
    cout << "══════════════════════════════════════" << endl;

    initForwardStar();

    // 建立示例图：1-2, 1-3, 2-4, 3-4
    addUndirectedEdgeFS(1, 2);
    addUndirectedEdgeFS(1, 3);
    addUndirectedEdgeFS(2, 4);
    addUndirectedEdgeFS(3, 4);

    cout << "示例图：1-2, 1-3, 2-4, 3-4" << endl;
    cout << endl;

    // 遍历每个顶点的邻居
    for (int i = 1; i <= 4; i++) {
        traverseNeighborsFS(i);
    }

    cout << endl;
    cout << "链式前向星内部存储结构：" << endl;
    cout << "head数组：";
    for (int i = 1; i <= 4; i++) {
        cout << "head[" << i << "]=" << head[i] << "  ";
    }
    cout << endl;

    cout << "边数组：" << endl;
    for (int i = 1; i <= edgeCnt; i++) {
        cout << "  edge[" << i << "]: to=" << edges[i].to
             << ", next=" << edges[i].next
             << ", w=" << edges[i].w << endl;
    }
    cout << endl;
}

// ================================================================
// 主函数
// ================================================================
int main() {
    cout << "╔══════════════════════════════════════════════╗" << endl;
    cout << "║    第41课：图的认识与存储                     ║" << endl;
    cout << "║    邻接矩阵 · 邻接表 · 链式前向星              ║" << endl;
    cout << "╚══════════════════════════════════════════════╝" << endl;
    cout << endl;

    int choice;
    do {
        cout << "请选择要运行的功能：" << endl;
        cout << "  1. 例题1：朋友关系存储（邻接矩阵）" << endl;
        cout << "  2. 例题2：度数统计（邻接表）" << endl;
        cout << "  3. 演示：链式前向星" << endl;
        cout << "  4. 三种方式对比测试" << endl;
        cout << "  0. 退出" << endl;
        cout << "请输入选择 → ";
        cin >> choice;
        cout << endl;

        switch (choice) {
        case 1:
            example1_friends();
            break;
        case 2:
            example2_degreeCount();
            break;
        case 3:
            demo_forwardStar();
            break;
        case 4: {
            cout << "══════════════════════════════════════" << endl;
            cout << "  三种存储方式对比" << endl;
            cout << "══════════════════════════════════════" << endl;
            cout << endl;

            cout << "┌──────────┬──────────┬──────────┬──────────────┐" << endl;
            cout << "│ 操作     │ 邻接矩阵 │ 邻接表   │ 链式前向星   │" << endl;
            cout << "├──────────┼──────────┼──────────┼──────────────┤" << endl;
            cout << "│ 存储空间 │ O(V²)    │ O(V+E)   │ O(V+E)       │" << endl;
            cout << "│ 查询边   │ O(1)     │ O(deg)   │ O(deg)       │" << endl;
            cout << "│ 添加边   │ O(1)     │ O(1)     │ O(1)         │" << endl;
            cout << "│ 遍历邻居 │ O(V)     │ O(deg)   │ O(deg)       │" << endl;
            cout << "│ 适用场景 │ 稠密图   │ 稀疏图   │ 竞赛/性能    │" << endl;
            cout << "│ 实现难度 │ ★☆☆☆☆    │ ★★☆☆☆    │ ★★★☆☆        │" << endl;
            cout << "└──────────┴──────────┴──────────┴──────────────┘" << endl;
            cout << endl;

            cout << "选择建议：" << endl;
            cout << "  • V ≤ 500 且边稠密 → 邻接矩阵" << endl;
            cout << "  • V 较大或边稀疏   → 邻接表（vector）" << endl;
            cout << "  • 竞赛追求极致性能 → 链式前向星" << endl;
            cout << endl;
            break;
        }
        case 0:
            cout << "再见！" << endl;
            break;
        default:
            cout << "无效选择，请重新输入。" << endl;
            break;
        }
    } while (choice != 0);

    return 0;
}
