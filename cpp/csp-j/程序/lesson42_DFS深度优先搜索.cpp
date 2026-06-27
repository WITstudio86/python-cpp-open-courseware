/**
 * CSP-J 备考课程 - 第42课：DFS深度优先搜索
 *
 * 本文件包含：
 *   1. DFS递归遍历框架（图的深度优先遍历）
 *   2. 连通块计数
 *   3. 连通块大小统计
 *   4. 迷宫寻路问题
 *   5. 全排列生成（回溯法）
 *   6. 组合数生成（回溯法）
 *   7. N皇后问题（经典回溯）
 *
 * 知识点：DFS递归框架、vis标记数组、回溯法（试探→递归→恢复）、
 *         连通块计数、迷宫寻路、排列组合枚举
 */

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

// ======================== 常量定义 ========================
const int N = 100005;

// ======================== 1. DFS递归遍历框架 ========================

bool dfs_vis[N];
vector<int> dfs_g[N];

/**
 * DFS递归遍历图的核心框架
 * 从顶点 u 开始，深度优先访问所有可达顶点
 */
void dfs_basic(int u) {
    dfs_vis[u] = true;           // 步骤1：标记当前顶点已访问
    cout << u << " ";            // 步骤2：处理当前顶点（这里是输出）

    for (int v : dfs_g[u]) {     // 步骤3：遍历所有邻接点
        if (!dfs_vis[v]) {       // 步骤4：如果邻接点未访问
            dfs_basic(v);        // 步骤5：递归深入
        }
    }
}

void demo_dfs_basic() {
    cout << "========== 1. DFS递归遍历框架演示 ==========" << endl;

    int n = 8, m = 7;
    // 树状结构：1 -> 2,3; 2 -> 4,5; 3 -> 6,7; 5 -> 8
    int edges[][2] = {{1,2}, {1,3}, {2,4}, {2,5}, {3,6}, {3,7}, {5,8}};

    cout << "图结构（树）：" << endl;
    cout << "        1" << endl;
    cout << "       / \\" << endl;
    cout << "      2   3" << endl;
    cout << "     /\\  /\\" << endl;
    cout << "    4 5 6 7" << endl;
    cout << "      |" << endl;
    cout << "      8" << endl;

    for (int i = 0; i < m; i++) {
        int u = edges[i][0], v = edges[i][1];
        dfs_g[u].push_back(v);
        dfs_g[v].push_back(u);
    }

    memset(dfs_vis, false, sizeof(dfs_vis));
    cout << "\nDFS遍历顺序（从1开始）：";
    dfs_basic(1);
    cout << endl << endl;

    cout << "代码框架说明：" << endl;
    cout << "void dfs(int u) {" << endl;
    cout << "    vis[u] = true;      // ①标记已访问" << endl;
    cout << "    for (int v : g[u])   // ②遍历邻接点" << endl;
    cout << "        if (!vis[v])      // ③未访问才递归" << endl;
    cout << "            dfs(v);       // ④深入探索" << endl;
    cout << "}" << endl << endl;
}

// ======================== 2. 连通块计数 ========================

bool cc_vis[N];

void cc_dfs(int u, vector<int> g[]) {
    cc_vis[u] = true;
    for (int v : g[u]) {
        if (!cc_vis[v]) {
            cc_dfs(v, g);
        }
    }
}

void demo_connected_components() {
    cout << "========== 2. 连通块计数演示 ==========" << endl;

    int n = 9, m = 6;
    // 三个连通块: {1,2,3}, {4,5,6}, {7,8,9}（独立顶点）
    int edges[][2] = {{1,2}, {2,3}, {4,5}, {5,6}, {4,6}, {7,8}};

    vector<int> g[N];
    for (int i = 0; i < m; i++) {
        int u = edges[i][0], v = edges[i][1];
        g[u].push_back(v);
        g[v].push_back(u);
    }

    cout << "图结构：三个连通块" << endl;
    cout << "  连通块1：1 - 2 - 3" << endl;
    cout << "  连通块2：4 - 5 - 6  (三角形)" << endl;
    cout << "  连通块3：7 - 8" << endl;
    cout << "  独立顶点：9" << endl;

    memset(cc_vis, false, sizeof(cc_vis));
    int cnt = 0;

    cout << "\n探索过程：" << endl;
    for (int i = 1; i <= n; i++) {
        if (!cc_vis[i]) {
            cnt++;
            cout << "  发现新的连通块" << cnt << "，从顶点" << i << "开始DFS..." << endl;
            cc_dfs(i, g);
        }
    }

    cout << "\n总共 " << cnt << " 个连通块" << endl;
    cout << "关键：每调用一次DFS，就访问完一整个连通块" << endl << endl;
}

// ======================== 3. 连通块大小统计 ========================

bool ccs_vis[N];

/**
 * 返回从顶点 u 出发能访问到的顶点数量
 */
int dfs_count_size(int u, vector<int> g[]) {
    ccs_vis[u] = true;
    int size = 1;  // 当前顶点算一个
    for (int v : g[u]) {
        if (!ccs_vis[v]) {
            size += dfs_count_size(v, g);
        }
    }
    return size;
}

void demo_component_size() {
    cout << "========== 3. 连通块大小统计演示 ==========" << endl;

    int n = 9, m = 6;
    int edges[][2] = {{1,2}, {2,3}, {4,5}, {5,6}, {4,6}, {7,8}};

    vector<int> g[N];
    for (int i = 0; i < m; i++) {
        int u = edges[i][0], v = edges[i][1];
        g[u].push_back(v);
        g[v].push_back(u);
    }

    memset(ccs_vis, false, sizeof(ccs_vis));

    cout << "每个连通块的大小：" << endl;
    for (int i = 1; i <= n; i++) {
        if (!ccs_vis[i]) {
            int sz = dfs_count_size(i, g);
            cout << "  以顶点" << i << "为首的连通块大小 = " << sz << endl;
        }
    }
    cout << endl;
}

// ======================== 4. 迷宫寻路 ========================

const int MAX_N = 15;
char maze[MAX_N][MAX_N];
bool maze_vis[MAX_N][MAX_N];
int N_rows, M_cols;
int start_x, start_y, target_x, target_y;
bool found;

// 四个方向：右、左、下、上
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
string dir_name[4] = {"右", "左", "下", "上"};

void dfs_maze(int x, int y, string path) {
    // 到达终点
    if (x == target_x && y == target_y) {
        found = true;
        cout << "    找到路径！" << path << endl;
        return;
    }

    maze_vis[x][y] = true;

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 1 && nx <= N_rows && ny >= 1 && ny <= M_cols
            && maze[nx][ny] == '.' && !maze_vis[nx][ny]) {
            dfs_maze(nx, ny, path + " → " + dir_name[i]);
            if (found) return;  // 找到一条路径就停止
        }
    }

    maze_vis[x][y] = false;  // 回溯：恢复状态（允许其他路径经过）
}

void demo_maze_pathfinding() {
    cout << "========== 4. 迷宫寻路演示 ==========" << endl;

    N_rows = 5; M_cols = 5;
    // 迷宫地图: '.' 可通行, '#' 障碍物
    // S=起点(1,1), T=终点(4,5)
    string raw[] = {
        ".....",
        ".##..",
        "..#..",
        ".....",
        "....."
    };

    cout << "迷宫地图（S=起点，T=终点）：" << endl;
    start_x = 1; start_y = 1;
    target_x = 4; target_y = 5;

    for (int i = 0; i < N_rows; i++) {
        for (int j = 0; j < M_cols; j++) {
            maze[i+1][j+1] = raw[i][j];
        }
    }

    for (int i = 1; i <= N_rows; i++) {
        cout << "  ";
        for (int j = 1; j <= M_cols; j++) {
            if (i == start_x && j == start_y) cout << "S";
            else if (i == target_x && j == target_y) cout << "T";
            else cout << maze[i][j];
        }
        cout << endl;
    }

    memset(maze_vis, false, sizeof(maze_vis));
    found = false;

    cout << "\nDFS探索过程：" << endl;
    dfs_maze(start_x, start_y, "起点");

    if (!found) {
        cout << "  无法到达终点！" << endl;
    }

    cout << "\n注意事项：" << endl;
    cout << "  1. 边界检查：nx, ny 必须在 [1,N] 和 [1,M] 内" << endl;
    cout << "  2. 障碍物检查：maze[nx][ny] == '.'" << endl;
    cout << "  3. vis 标记：防止在迷宫中来回走" << endl;
    cout << "  4. DFS找到的路径不一定是最短路径" << endl << endl;
}

// ======================== 5. 全排列生成（回溯法） ========================

int perm_n;
int perm_path[15];
bool perm_used[15];
int perm_count = 0;

/**
 * 回溯法生成 1~n 的全排列
 * k: 当前已经选了几个数
 */
void dfs_permutation(int k) {
    if (k == perm_n) {
        // 输出排列
        cout << "    ";
        for (int i = 0; i < perm_n; i++) {
            cout << perm_path[i] << " ";
        }
        cout << endl;
        perm_count++;
        return;
    }

    for (int i = 1; i <= perm_n; i++) {
        if (!perm_used[i]) {
            perm_path[k] = i;       // 步骤1：做选择
            perm_used[i] = true;    // 步骤2：标记已使用
            dfs_permutation(k + 1); // 步骤3：递归深入
            perm_used[i] = false;   // 步骤4：回溯！恢复状态
        }
    }
}

void demo_permutation() {
    cout << "========== 5. 全排列生成演示（回溯法） ==========" << endl;

    perm_n = 3;
    perm_count = 0;
    memset(perm_used, false, sizeof(perm_used));

    cout << "生成 1~" << perm_n << " 的所有全排列：" << endl;
    dfs_permutation(0);
    cout << "共 " << perm_count << " 种排列（" << perm_n << "! = " << perm_count << "）" << endl;

    cout << "\n回溯法三步曲：" << endl;
    cout << "  ①做选择：path[k] = i; used[i] = true;" << endl;
    cout << "  ②递归：dfs(k + 1);" << endl;
    cout << "  ③恢复：used[i] = false;  // 千万别忘！" << endl << endl;
}

// ======================== 6. 组合数生成（回溯法） ========================

int comb_n, comb_k;
int comb_path[15];
int comb_count = 0;

/**
 * 回溯法生成组合：从 1~n 中选 k 个数的所有组合
 * start: 从哪个数开始选（保证不重复选择且按顺序）
 * depth: 当前已经选了几个数
 */
void dfs_combination(int start, int depth) {
    if (depth == comb_k) {
        cout << "    ";
        for (int i = 0; i < comb_k; i++) {
            cout << comb_path[i] << " ";
        }
        cout << endl;
        comb_count++;
        return;
    }

    for (int i = start; i <= comb_n; i++) {
        comb_path[depth] = i;
        dfs_combination(i + 1, depth + 1);
    }
}

void demo_combination() {
    cout << "========== 6. 组合数生成演示（回溯法） ==========" << endl;

    comb_n = 5;
    comb_k = 3;
    comb_count = 0;

    cout << "从 1~" << comb_n << " 中选 " << comb_k << " 个数的所有组合：" << endl;
    dfs_combination(1, 0);
    cout << "共 " << comb_count << " 种组合（C(" << comb_n << "," << comb_k
         << ") = " << comb_count << "）" << endl;

    cout << "\n与排列的区别：" << endl;
    cout << "  - 排列考虑顺序：[1,2,3] 和 [1,3,2] 是不同的排列" << endl;
    cout << "  - 组合不考虑顺序：[1,2,3] 和 [1,3,2] 是同一组合" << endl;
    cout << "  - 组合用 start 参数保证按顺序选，避免重复" << endl << endl;
}

// ======================== 7. N皇后问题（经典回溯） ========================

int queen_n;
int queen_col[15];    // queen_col[row] = 棋子放在第row行的第几列
int queen_count = 0;

/**
 * 判断在第 row 行、第 col 列放皇后是否合法
 */
bool is_safe(int row, int col) {
    for (int r = 0; r < row; r++) {
        // 检查同列 或 同对角线
        if (queen_col[r] == col ||
            abs(queen_col[r] - col) == abs(r - row)) {
            return false;
        }
    }
    return true;
}

void dfs_queen(int row) {
    if (row == queen_n) {
        cout << "    第" << ++queen_count << "个解：";
        for (int i = 0; i < queen_n; i++) {
            cout << "(" << i+1 << "," << queen_col[i]+1 << ") ";
        }
        cout << endl;
        return;
    }

    for (int col = 0; col < queen_n; col++) {
        if (is_safe(row, col)) {
            queen_col[row] = col;   // 放皇后
            dfs_queen(row + 1);     // 递归下一行
            // queen_col[row] 会被后续循环覆盖，不需要显式撤销
        }
    }
}

void demo_nqueens() {
    cout << "========== 7. N皇后问题演示（经典回溯） ==========" << endl;

    queen_n = 4;
    queen_count = 0;

    cout << "求解" << queen_n << "皇后问题：" << endl;
    cout << "（在" << queen_n << "×" << queen_n << "棋盘上放置" << queen_n
         << "个皇后，使它们互不攻击）" << endl << endl;

    dfs_queen(0);

    cout << "\n共 " << queen_count << " 个解" << endl;
    cout << "剪枝说明：is_safe 函数提前排除了不合法的列选择，避免无效递归" << endl << endl;
}

// ======================== 主函数 ========================

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cout << "╔════════════════════════════════════════════════╗" << endl;
    cout << "║   CSP-J 第42课：DFS深度优先搜索 - 代码演示      ║" << endl;
    cout << "╚════════════════════════════════════════════════╝" << endl << endl;

    demo_dfs_basic();
    demo_connected_components();
    demo_component_size();
    demo_maze_pathfinding();
    demo_permutation();
    demo_combination();
    demo_nqueens();

    cout << "========== 演示完毕 ==========" << endl;
    cout << "\n关键要点总结：" << endl;
    cout << "1. DFS递归框架：vis标记 → 遍历邻接点 → 递归深入" << endl;
    cout << "2. 回溯法：试探 → 递归 → 恢复状态（恢复是重点！）" << endl;
    cout << "3. 连通块计数：每调一次DFS就是一个连通块" << endl;
    cout << "4. 迷宫寻路：四个方向，边界+障碍物+vis三重检查" << endl;
    cout << "5. 全排列：n! 种可能，n<=10 安全" << endl;
    cout << "6. DFS不能求最短路径（用BFS），深度过大注意栈溢出" << endl;

    return 0;
}
