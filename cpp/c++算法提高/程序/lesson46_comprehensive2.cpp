/*
 * ============================================================
 * 第46课：算法综合实战（二）—— DP+图论综合
 * lesson46_comprehensive2.cpp
 *
 * 包含两道综合题目的完整实现：
 *   1. 数字三角形   —— 经典DP（自底向上+自顶向下两种写法）
 *   2. 最小路径和   —— 二维网格DP（DP+图论视角）
 *
 * 适用对象：具备基础C++知识的中小学生
 * ============================================================
 */

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

// ============================================================
// 第一部分：数字三角形问题
// 题目：给定N行数字三角形，从顶部走到底部，求路径和最大值
// 移动规则：每次只能向左下方或右下方走一步
// ============================================================

const int MAXN = 105;            // 最大行数
int a[MAXN][MAXN];               // 存储数字三角形
int dp1[MAXN][MAXN];             // DP数组（自底向上）
int dp2[MAXN][MAXN];             // DP数组（自顶向下/记忆化搜索）
int n;                           // 三角形的行数

/*
 * 方法1：自底向上递推（推荐！）
 *
 * 思路：从最底层开始，逐层向上计算
 * - 状态定义：dp[i][j] = 从底部走到第i行第j列的最大路径和
 * - 边界条件：dp[n][j] = a[n][j]（最底层的值就是自身）
 * - 状态转移：dp[i][j] = a[i][j] + max(dp[i+1][j], dp[i+1][j+1])
 *   （当前格子的值 + 下方两个邻居中较大的那个）
 * - 最终答案：dp[1][1]（三角形顶部）
 *
 * 三角形结构示意：
 *              (1,1)
 *          (2,1) (2,2)
 *       (3,1) (3,2) (3,3)
 *     (4,1) (4,2) (4,3) (4,4)
 *   (5,1) (5,2) (5,3) (5,4) (5,5)
 *
 * 每个位置(i,j)的下一步可以选择(i+1,j)或(i+1,j+1)
 */
int solveTriangle_BottomUp() {
    // 第一步：初始化最底层
    for (int j = 1; j <= n; j++) {
        dp1[n][j] = a[n][j];
    }

    // 第二步：从倒数第二层开始，逐层向上递推
    for (int i = n - 1; i >= 1; i--) {
        for (int j = 1; j <= i; j++) {
            // 状态转移：当前值 + 下方两个邻居中较大的
            dp1[i][j] = a[i][j] + max(dp1[i + 1][j], dp1[i + 1][j + 1]);
        }
    }

    // 第三步：返回顶部结果
    return dp1[1][1];
}

/*
 * 方法2：自顶向下记忆化搜索
 *
 * 思路：从顶部开始，递归计算每个位置的最大路径和
 * - 状态定义：dp2[i][j] = 从顶部走到第i行第j列的最大路径和
 * - 边界条件：dp2[1][1] = a[1][1]（起点）
 * - 状态转移：dp2[i][j] = a[i][j] + max(dp2[i-1][j-1], dp2[i-1][j])
 *   （当前格子的值 + 上方两个邻居中较大的那个）
 * - 最终答案：max(dp2[n][1], dp2[n][2], ..., dp2[n][n])（最底层的最大值）
 */
int solveTriangle_TopDown() {
    // 初始化边界：起点
    dp2[1][1] = a[1][1];

    // 逐行从上往下递推
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            if (j == 1) {
                // 最左边的格子只能从正上方来
                dp2[i][j] = a[i][j] + dp2[i - 1][j];
            } else if (j == i) {
                // 最右边的格子只能从左上方来
                dp2[i][j] = a[i][j] + dp2[i - 1][j - 1];
            } else {
                // 中间的格子可以从左上方或正上方来，取较大值
                dp2[i][j] = a[i][j] + max(dp2[i - 1][j - 1], dp2[i - 1][j]);
            }
        }
    }

    // 在最底层找最大值
    int ans = dp2[n][1];
    for (int j = 2; j <= n; j++) {
        if (dp2[n][j] > ans) {
            ans = dp2[n][j];
        }
    }
    return ans;
}

/*
 * 数字三角形问题的测试示例
 */
void demoTriangle() {
    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║      例题1：数字三角形（DP）             ║" << endl;
    cout << "║      最大路径和                          ║" << endl;
    cout << "╚══════════════════════════════════════════╝" << endl;
    cout << endl;

    // 样例测试
    n = 5;
    // 第1行
    a[1][1] = 7;
    // 第2行
    a[2][1] = 3; a[2][2] = 8;
    // 第3行
    a[3][1] = 8; a[3][2] = 1; a[3][3] = 0;
    // 第4行
    a[4][1] = 2; a[4][2] = 7; a[4][3] = 4; a[4][4] = 4;
    // 第5行
    a[5][1] = 4; a[5][2] = 5; a[5][3] = 2; a[5][4] = 6; a[5][5] = 5;

    cout << "【样例输入】三角形（N=" << n << "）：" << endl;
    cout << "      7" << endl;
    cout << "    3   8" << endl;
    cout << "  8   1   0" << endl;
    cout << "2   7   4   4" << endl;
    cout << "4   5   2   6   5" << endl << endl;

    // 使用方法1（自底向上）求解
    int ans1 = solveTriangle_BottomUp();
    cout << "【自底向上DP】最大路径和：" << ans1 << endl;
    cout << "  最优路径：7 → 3 → 8 → 7 → 5" << endl;
    cout << "  路径和：7+3+8+7+5 = 30" << endl << endl;

    // 使用方法2（自顶向下）求解
    int ans2 = solveTriangle_TopDown();
    cout << "【自顶向下DP】最大路径和：" << ans2 << endl;
    cout << "  （两种方法得到相同结果）" << endl << endl;

    // 打印DP表格（自底向上）
    cout << "【DP表格可视化（自底向上）】" << endl;
    cout << "  dp[i][j] 表示从底部到(i,j)的最大和：" << endl;
    for (int i = 1; i <= n; i++) {
        cout << "  ";
        for (int k = 1; k <= n - i; k++) cout << "  ";
        for (int j = 1; j <= i; j++) {
            cout << dp1[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "【算法分析】" << endl;
    cout << "  - 状态数：" << n << "×(n+1)/2 = " << n*(n+1)/2 << " 个" << endl;
    cout << "  - 每个状态 O(1) 转移" << endl;
    cout << "  - 时间复杂度：O(N²)" << endl;
    cout << "  - 空间复杂度：O(N²)，可优化为 O(N)" << endl;
    cout << "  - 推荐写法：自底向上递推（简洁、无递归开销）" << endl;
    cout << endl;
}

// ============================================================
// 第二部分：最小路径和问题（DP + 图论视角）
// 题目：N×M网格，从左上到右下，只能向右或向下，求最小路径和
// ============================================================

const int MAXM = 105;            // 最大列数
const int INF = 0x3f3f3f3f;     // 无穷大（约10亿，不会溢出）
int grid[MAXN][MAXM];            // 存储网格权值
int dp_grid[MAXN][MAXM];         // DP数组
int rows, cols;                  // 行数和列数

/*
 * 最小路径和——主求解函数
 *
 * 图论视角分析：
 * - 顶点：网格中的每个格子 (i, j)，共 N×M 个顶点
 * - 边：从 (i,j) 到 (i+1,j) 和到 (i,j+1)，共约 2NM 条边
 * - 这是一个有向无环图（DAG），DP的递推顺序就是图的拓扑排序
 *
 * DP分析：
 * - 状态定义：dp[i][j] = 从起点(1,1)走到(i,j)的最小路径和
 * - 边界条件：dp[1][1] = grid[1][1]
 * - 状态转移：dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1])
 *   （当前格子的值 + 从上方或左方过来的最小代价）
 * - 最终答案：dp[n][m]（右下角）
 *
 * 网格示意图（N=3, M=3）：
 *   (1,1) → (1,2) → (1,3)
 *     ↓        ↓        ↓
 *   (2,1) → (2,2) → (2,3)
 *     ↓        ↓        ↓
 *   (3,1) → (3,2) → (3,3)
 *
 * 每个格子(i,j)可以从(i-1,j)（上）或(i,j-1)（左）到达
 */
int solveMinPathSum() {
    // 初始化dp数组为无穷大
    memset(dp_grid, 0x3f, sizeof(dp_grid));

    // 边界条件：起点
    dp_grid[1][1] = grid[1][1];

    // 按拓扑顺序递推：从上到下、从左到右
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= cols; j++) {
            if (i == 1 && j == 1) continue;  // 起点已处理

            // 从上方转移（图论中的"上边"入边）
            int fromUp = (i > 1) ? dp_grid[i - 1][j] : INF;
            // 从左方转移（图论中的"左边"入边）
            int fromLeft = (j > 1) ? dp_grid[i][j - 1] : INF;

            // 状态转移：取上方和左方中较小的，加上当前格子的值
            dp_grid[i][j] = grid[i][j] + min(fromUp, fromLeft);
        }
    }

    // 返回右下角的答案
    return dp_grid[rows][cols];
}

/*
 * 最小路径和问题的测试示例
 */
void demoMinPathSum() {
    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║      例题2：最小路径和（DP+图论）        ║" << endl;
    cout << "║      网格最短路径                        ║" << endl;
    cout << "╚══════════════════════════════════════════╝" << endl;
    cout << endl;

    // 样例1测试
    rows = 3; cols = 3;
    grid[1][1] = 1; grid[1][2] = 3; grid[1][3] = 1;
    grid[2][1] = 1; grid[2][2] = 5; grid[2][3] = 1;
    grid[3][1] = 4; grid[3][2] = 2; grid[3][3] = 1;

    cout << "【样例1输入】网格（" << rows << "×" << cols << "）：" << endl;
    for (int i = 1; i <= rows; i++) {
        cout << "  ";
        for (int j = 1; j <= cols; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    int ans1 = solveMinPathSum();

    cout << "【样例1输出】最小路径和：" << ans1 << endl;
    cout << "  最优路径：(1,1)→(2,1)→(2,2)→(2,3)→(3,3)" << endl;
    cout << "  路径和：1+1+5+1+1 = 9？" << endl;
    cout << "  等等，还有更好的：" << endl;
    cout << "  最优路径：(1,1)→(1,2)→(1,3)→(2,3)→(3,3)" << endl;
    cout << "  路径和：1+3+1+1+1 = 7 ✓" << endl << endl;

    // 打印DP表格
    cout << "【DP表格可视化】" << endl;
    cout << "  dp[i][j] 表示从(1,1)到(i,j)的最小路径和：" << endl;
    for (int i = 1; i <= rows; i++) {
        cout << "  ";
        for (int j = 1; j <= cols; j++) {
            cout << dp_grid[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;

    // 样例2测试（更大的网格）
    cout << "【样例2】4×4 网格：" << endl;
    rows = 4; cols = 4;
    int test2[4][4] = {
        {2, 1, 3, 4},
        {3, 2, 1, 2},
        {1, 5, 2, 1},
        {4, 2, 3, 2}
    };
    for (int i = 1; i <= rows; i++) {
        cout << "  ";
        for (int j = 1; j <= cols; j++) {
            grid[i][j] = test2[i-1][j-1];
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    int ans2 = solveMinPathSum();
    cout << "  最小路径和：" << ans2 << endl << endl;

    cout << "【算法分析】" << endl;
    cout << "  - 状态数：" << rows << "×" << cols << " = " << rows*cols << " 个" << endl;
    cout << "  - 每个状态 O(1) 转移（只依赖上方和左方）" << endl;
    cout << "  - 时间复杂度：O(N×M)" << endl;
    cout << "  - 空间复杂度：O(N×M)，可优化为 O(min(N,M))" << endl;
    cout << "  - 图论视角：网格是有向无环图(DAG)，DP <=> 拓扑排序" << endl;
    cout << endl;
}

// ============================================================
// 第三部分：交互式菜单
// ============================================================

/*
 * 打印程序主菜单
 */
void printMenu() {
    cout << endl;
    cout << "┌──────────────────────────────────────────────┐" << endl;
    cout << "│       第46课：算法综合实战（二）             │" << endl;
    cout << "│       DP + 图论综合                           │" << endl;
    cout << "├──────────────────────────────────────────────┤" << endl;
    cout << "│  1. 例题1：数字三角形（DP自底向上+自顶向下） │" << endl;
    cout << "│  2. 例题2：最小路径和（DP+图论）             │" << endl;
    cout << "│  3. 运行全部例题                              │" << endl;
    cout << "│  0. 退出程序                                  │" << endl;
    cout << "└──────────────────────────────────────────────┘" << endl;
    cout << "请输入你的选择（0-3）：";
}

/*
 * 主函数
 */
int main() {
    int choice;

    do {
        printMenu();
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1:
                demoTriangle();
                break;
            case 2:
                demoMinPathSum();
                break;
            case 3:
                demoTriangle();
                cout << "\n" << string(50, '=') << "\n" << endl;
                demoMinPathSum();
                break;
            case 0:
                cout << "恭喜你完成了两节算法综合实战课程！" << endl;
                cout << "继续加油，算法之路越走越宽~" << endl;
                break;
            default:
                cout << "输入有误，请重新输入（0-3）！" << endl;
        }
    } while (choice != 0);

    return 0;
}
