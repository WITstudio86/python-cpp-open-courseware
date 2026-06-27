/**
 * ============================================================
 * 课程编号：第35课
 * 课程标题：状态压缩DP基础
 * 对应考纲：状态压缩DP、位运算优化、NP-hard问题的精确算法
 *
 * 本文件包含三道真题的 AC 代码：
 *   题目1：最短Hamilton路径（TSP问题，经典状压DP模板）
 *   题目2：互不侵犯（棋盘状压DP，预处理 + 按行转移）
 *   题目3：蒙德里安的梦想（骨牌覆盖，按列状压DP）
 * ============================================================
 */

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

// ============================================================
// 通用优化：快速读入
// ============================================================
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

// ============================================================
// 【题目1】最短Hamilton路径
//
// 题目来源：AcWing 91 / 洛谷 P1171（售货员的难题变体）
// 难度：提高+/省选-
//
// 问题描述：
//   给定 n 个点的带权无向完全图（0~n-1），求从 0 出发，
//   恰好访问每个点一次，最终到达 n-1 的最短路径长度。
//
// 算法：状态压缩DP
//   状态设计：dp[mask][i] = 已访问 mask 中的点，当前在点 i 的最短路径
//   转移方程：dp[mask][i] = min(dp[mask^(1<<i)][j] + dist[j][i])
//   时间复杂度：O(n^2 * 2^n)
//   空间复杂度：O(n * 2^n)
// ============================================================

const int MAXN_1 = 20;              // 最大点数（n ≤ 20）
const int INF_1   = 0x3f3f3f3f;     // 无穷大（约 1e9，且 memset 安全）

int n1;                              // 点的数量
int dist[MAXN_1][MAXN_1];           // 邻接矩阵，dist[i][j] = i到j的距离
int dp1[1 << MAXN_1][MAXN_1];       // dp[mask][i] 状态数组

void solve_hamilton() {
    n1 = read();
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n1; j++) {
            dist[i][j] = read();
        }
    }

    // 初始化 dp 数组为无穷大
    // 使用 memset 快速填充：0x3f 是常用技巧
    // memset 按字节填充，每个 int 变成 0x3f3f3f3f ≈ 1.06e9
    memset(dp1, 0x3f, sizeof(dp1));

    // 起点：从城市 0 出发，只访问了 {0}，当前在 0
    dp1[1 << 0][0] = 0;

    // 枚举所有已访问城市的集合 mask
    // mask 从小到大，保证转移时子状态已计算
    for (int mask = 1; mask < (1 << n1); mask++) {

        // 枚举当前停留的城市 i
        for (int i = 0; i < n1; i++) {

            // 城市 i 必须在 mask 中（已被访问）
            if (!(mask & (1 << i))) continue;

            // 到达 i 之前的状态：从 mask 中去掉 i
            int prev_mask = mask ^ (1 << i);

            // 枚举上一个停留的城市 j
            for (int j = 0; j < n1; j++) {

                // 城市 j 必须在 prev_mask 中
                if (!(prev_mask & (1 << j))) continue;

                // 状态转移：从 j 走到 i
                // dp[mask][i] = min(dp[mask][i], dp[prev_mask][j] + dist[j][i])
                dp1[mask][i] = min(dp1[mask][i], dp1[prev_mask][j] + dist[j][i]);
            }
        }
    }

    // 答案：访问完所有城市（mask = (1<<n)-1），最终停在 n-1
    // 如果要求终点为任意城市，需要 min dp[(1<<n)-1][i] for all i
    int ans = dp1[(1 << n1) - 1][n1 - 1];
    printf("%d\n", ans);
}

// ============================================================
// 【题目2】互不侵犯（棋盘状压DP）
//
// 题目来源：洛谷 P1896 [SCOI2005] 互不侵犯
// 难度：提高+/省选-
//
// 问题描述：
//   在 N×N 的棋盘里面放 K 个国王，使它们互不攻击。
//   国王能攻击上下左右及对角线共 8 个相邻格子。
//   求共有多少种摆放方案。
//
// 算法：按行状压DP
//   状态设计：dp[row][state][cnt] =
//     前 row 行，第 row 行状态为 state，共摆了 cnt 个国王的方案数
//   转移方程：
//     dp[row][cur][cnt] = sum(dp[row-1][prev][cnt - popcount(cur)])
//     其中 prev 和 cur 兼容（上下行及对角线不冲突）
//   时间复杂度：O(N * 合法状态数^2 * K)
// ============================================================

const int MAXN_2 = 10;              // N ≤ 9，留一点余量
const int MAXK_2 = 100;             // K ≤ N^2 ≤ 81

int N, K;                            // 棋盘大小 N，国王数量 K
long long dp2[MAXN_2][1 << MAXN_2][MAXK_2];
                                     // dp[row][state][cnt]，注意用 long long（方案数可能很大）

vector<int> legal_state;             // 所有"自身合法"的行状态（没有相邻的国王）
vector<int> legal_state_cnt;         // 对应状态的国王数量
vector<int> compatible[1 << MAXN_2]; // compatible[prev] = 与 prev 兼容的状态列表

// 判断行状态是否自身合法（同一行没有相邻的国王）
bool is_row_legal(int state) {
    // 检查是否有相邻的 1
    // 例如：state=0110，state<<1=1100，0110 & 1100 = 0100 ≠ 0 → 有相邻
    return (state & (state << 1)) == 0;
}

// 判断两个行状态是否兼容（上下行国王不冲突）
bool are_compatible(int prev, int cur) {
    // 条件1：不能在同一列都有国王
    if (prev & cur) return false;
    // 条件2：不能在对角线（左上-右下方向，即 cur 右移一位和 prev 冲突）
    if (prev & (cur << 1)) return false;
    // 条件3：不能在对角线（右上-左下方向，即 cur 左移一位和 prev 冲突）
    if (prev & (cur >> 1)) return false;
    return true;
}

void solve_kings() {
    N = read();
    K = read();

    // === Step 1: 预处理自身合法的行状态 ===
    for (int state = 0; state < (1 << N); state++) {
        if (is_row_legal(state)) {
            legal_state.push_back(state);
            // 计算该状态的国王数量（二进制中 1 的个数）
            legal_state_cnt.push_back(__builtin_popcount(state));
        }
    }

    int state_count = legal_state.size(); // 合法状态数（N=9 时约 89 个）

    // === Step 2: 预处理状态之间的兼容性 ===
    for (int i = 0; i < state_count; i++) {
        for (int j = 0; j < state_count; j++) {
            if (are_compatible(legal_state[i], legal_state[j])) {
                compatible[i].push_back(j);
            }
        }
    }

    // === Step 3: DP初始化 ===
    // 第1行：对于每个合法状态，如果国王数不超过K，方案数为1
    for (int i = 0; i < state_count; i++) {
        int cnt = legal_state_cnt[i];
        if (cnt <= K) {
            dp2[1][i][cnt] = 1;
        }
    }

    // === Step 4: 逐行DP转移 ===
    for (int row = 2; row <= N; row++) {
        for (int i = 0; i < state_count; i++) {          // 当前行状态索引
            int cur_state = legal_state[i];
            int cur_cnt   = legal_state_cnt[i];

            for (int p : compatible[i]) {                 // 枚举兼容的上一行状态
                int prev_state = legal_state[p];
                int prev_cnt   = legal_state_cnt[p];

                // 转移：dp[row][cur][total] += dp[row-1][prev][total - cur_cnt]
                for (int total = cur_cnt; total <= K; total++) {
                    dp2[row][i][total] += dp2[row - 1][p][total - cur_cnt];
                }
            }
        }
    }

    // === Step 5: 统计答案 ===
    // 答案 = 所有合法状态的 dp[N][state][K] 之和
    long long ans = 0;
    for (int i = 0; i < state_count; i++) {
        ans += dp2[N][i][K];
    }

    printf("%lld\n", ans);
}

// ============================================================
// 【题目3】蒙德里安的梦想（骨牌覆盖状压DP）
//
// 题目来源：AcWing 291 / 算法竞赛进阶指南
// 难度：提高+/省选-
//
// 问题描述：
//   求把 N×M 的棋盘分割成若干个 1×2 的长方形（骨牌），
//   有多少种不同的分割方案。
//
// 算法：按列状压DP
//   dp[mask]：当前列被伸出来的骨牌占据的行集合为 mask 的方案数
//   转移：prev_mask → cur_mask，需满足兼容性条件
//   时间复杂度：O(M × 4^N)
// ============================================================

const int MAXN_3 = 12;

int N3, M3;                          // 棋盘尺寸
long long dp[1 << MAXN_3];           // dp[mask]，滚动数组
bool valid[1 << MAXN_3];             // valid[mask]：mask中连续0的个数是否都是偶数

void solve_mondrian() {
    while (true) {
        cin >> N3 >> M3;
        if (N3 == 0 && M3 == 0) break;

        // 预处理：判断每个mask自身的合法性
        // 合法条件：mask中所有连续0段的长度均为偶数
        for (int mask = 0; mask < (1 << N3); mask++) {
            int cnt = 0;      // 连续0的个数
            bool ok = true;
            for (int i = 0; i < N3; i++) {
                if (mask & (1 << i)) {   // 此位置是1（有伸出来的骨牌）
                    if (cnt & 1) {       // 前面的连续0是奇数个 → 非法
                        ok = false;
                        break;
                    }
                    cnt = 0;
                } else {
                    cnt++;
                }
            }
            if (cnt & 1) ok = false;     // 末尾的连续0也必须是偶数
            valid[mask] = ok;
        }

        // DP初始化：第0列没有任何伸出来的骨牌
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;

        // 逐列DP
        for (int col = 1; col <= M3; col++) {
            long long ndp[1 << MAXN_3] = {0};
            for (int prev = 0; prev < (1 << N3); prev++) {
                if (dp[prev] == 0) continue;
                for (int cur = 0; cur < (1 << N3); cur++) {
                    // cur：当前列新放置的横向骨牌（伸到下一列）
                    // prev：上一列伸到当前列的骨牌
                    // 条件1：prev 和 cur 不能重叠
                    if (prev & cur) continue;
                    // 条件2：剩余空位（竖骨牌占位）必须满足"连续0为偶数"
                    if (valid[prev | cur]) {
                        ndp[cur] += dp[prev];
                    }
                }
            }
            memcpy(dp, ndp, sizeof(dp));
        }

        // 答案：M列填完后，第M+1列没有伸出来的骨牌
        cout << dp[0] << '\n';
    }
}

// ============================================================
// 主函数
// ============================================================
int main() {
    // 题目选择：取消注释即可运行对应题目
    // solve_hamilton();   // 最短Hamilton路径
    // solve_kings();      // 互不侵犯
    // solve_mondrian();   // 蒙德里安的梦想

    // 默认运行 Hamilton 路径问题
    solve_hamilton();

    return 0;
}
