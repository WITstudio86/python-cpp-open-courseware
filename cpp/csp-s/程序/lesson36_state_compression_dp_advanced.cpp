/**
 * ============================================================
 * 课程编号：第36课
 * 课程标题：状态压缩DP进阶
 * 对应考纲：状态压缩DP进阶、轮廓线DP、期望DP
 *
 * 本文件包含两道真题的 AC 代码：
 *   题目1：蒙德里安的梦想（骨牌覆盖，按列状压DP）
 *   题目2：奖励关（期望DP + 状压，逆推策略）
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
// 【题目1】蒙德里安的梦想（骨牌覆盖）
//
// 题目来源：AcWing 291 / 洛谷 P5075（蒙德里安的梦想）
// 难度：提高+/省选-
//
// 问题描述：
//   求把 N×M 的棋盘分割成若干个 1×2 的长方形（骨牌），有多少种方案。
//   骨牌可以横放也可以竖放。
//
// 算法：按列状压DP
//   状态设计：dp[col][state] =
//     前 col 列已铺满，第 col 列的状态为 state（哪些行有骨牌伸出到 col+1 列）
//   预处理：
//     st[state]：state 的所有连续 0 段是否都是偶数长度
//     合法转移：prev & cur == 0 且 st[prev | cur] == true
//   时间复杂度：O(M × 4^N)，N ≤ 11 时可行
// ============================================================

const int MAX_N = 12;               // N ≤ 11
const int MAX_M = 12;               // M ≤ 11
const int MAX_STATE = 1 << MAX_N;   // 最大状态数 2^12 = 4096

int N, M;                            // 棋盘的行数 N，列数 M
bool st[MAX_STATE];                  // st[state] = 连续0段长度是否全为偶数
long long dp_mondrian[MAX_M][MAX_STATE];
                                     // dp[col][state]，用 long long 防止溢出
vector<int> trans[MAX_STATE];        // trans[prev] = 所有可以与 prev 转移的 cur 状态列表

// 预处理：判断 state 的连续 0 段是否都是偶数长度
bool check_even_zeros(int state, int n) {
    int cnt = 0;                     // 当前连续 0 的个数
    for (int i = 0; i < n; i++) {
        if ((state >> i) & 1) {      // 第 i 位是 1（有骨牌伸出）
            if (cnt & 1) return false; // 连续 0 个数为奇数 → 不合法
            cnt = 0;
        } else {
            cnt++;                   // 又一个连续的 0
        }
    }
    // 检查最后一段连续 0
    if (cnt & 1) return false;
    return true;
}

void solve_mondrian() {
    // 循环处理多组测试数据
    while (true) {
        N = read();
        M = read();
        if (N == 0 && M == 0) break;

        // 确保 N ≤ M，可以减少状态数量（选较小的作为行数）
        // 这样可以减少 2^N 的大小
        // 注意：这里 N 是行数（决定状态位数），M 是列数
        // 如果 N > M，可以交换使得 N 较小（因为复杂度 O(M × 2^(2N))，N 在指数上）
        // 但实际上蒙德里安梦想中 N 和 M 不能简单交换，因为骨牌方向不同
        // 不过 N 和 M 都 ≤ 11，2^11 = 2048，直接算也可以

        int full = 1 << N;           // 状态总数 2^N

        // === Step 1: 预处理 st[] 数组 ===
        for (int state = 0; state < full; state++) {
            st[state] = check_even_zeros(state, N);
        }

        // === Step 2: 预处理合法转移 ===
        for (int prev = 0; prev < full; prev++) {
            trans[prev].clear();
            for (int cur = 0; cur < full; cur++) {
                // 条件1：prev 和 cur 不能有冲突（同一行不能同时被两个横骨牌占据）
                // 条件2：prev | cur 的空格（连续0）必须都是偶数
                if ((prev & cur) == 0 && st[prev | cur]) {
                    trans[prev].push_back(cur);
                }
            }
        }

        // === Step 3: DP ===
        memset(dp_mondrian, 0, sizeof(dp_mondrian));
        // 初始状态：第 0 列没有骨牌伸出（即没有任何横向骨牌跨越第0列和第1列）
        dp_mondrian[0][0] = 1;

        for (int col = 1; col <= M; col++) {
            for (int prev = 0; prev < full; prev++) {
                if (dp_mondrian[col - 1][prev] == 0) continue; // 剪枝
                for (int cur : trans[prev]) {
                    dp_mondrian[col][cur] += dp_mondrian[col - 1][prev];
                }
            }
        }

        // === Step 4: 输出答案 ===
        // 答案：处理完 M 列后，第 M 列没有任何骨牌伸出
        // 即 dp[M][0]
        printf("%lld\n", dp_mondrian[M][0]);
    }
}

// ============================================================
// 【题目2】奖励关（期望DP + 状压）
//
// 题目来源：洛谷 P2473 [SCOI2008] 奖励关
// 难度：省选/NOI-
//
// 问题描述：
//   系统进行 K 轮，每轮等概率随机抛出 n 种宝物中的一种（可重复）。
//   每种宝物 i 有分值 p_i 和前提集合 s_i（必须先获得s_i中的宝物）。
//   每次可以选择获取（需满足前提）或放弃。每种宝物最多获取一次。
//   求最优策略下的期望总分。
//
// 算法：期望DP + 状态压缩（逆推法）
//   状态设计：dp[round][mask] =
//     从第 round 轮开始到结束，当前已收集 mask，能获得的最大期望得分
//
//   逆推转移（从第 K 轮到第 1 轮）：
//     dp[round][mask] = (1/n) × Σ_i best_i
//     其中 best_i：
//       - 若 s_i ⊆ mask：best_i = max(dp[round+1][mask], dp[round+1][mask|(1<<i)] + p_i)
//       - 若 s_i ⊈ mask：best_i = dp[round+1][mask]（只能放弃）
//
//   初始化：dp[K+1][mask] = 0
//   答案：dp[1][0]
//
//   时间复杂度：O(K × n × 2^n)
// ============================================================

const int MAX_K = 105;               // 最大轮数
const int MAX_n = 16;                // 最大宝物数量（n ≤ 15）
const int FULL_MASK = 1 << MAX_n;    // 状态总数 2^15 = 32768

int K_rounds, nn;                    // 轮数 K，宝物数 n
int score[MAX_n];                    // score[i] = 宝物 i 的分值
int require[MAX_n];                  // require[i] = 宝物 i 的前提集合（位掩码）

double dp_reward[MAX_K][FULL_MASK];  // dp[round][mask]

void solve_reward() {
    K_rounds = read();
    nn = read();

    // 读入每个宝物的信息
    for (int i = 0; i < nn; i++) {
        score[i] = read();
        require[i] = 0;
        // 读入前提宝物列表，以 0 结尾
        while (true) {
            int pre = read();
            if (pre == 0) break;
            pre--;                   // 转换为 0-based 编号
            require[i] |= (1 << pre);
        }
    }

    int full = 1 << nn;

    // === DP 初始化 ===
    // dp[K_rounds + 1][mask] 已经是 0（全局变量默认初始化）
    // 注意：使用 double 数组，memset 为 0 即可
    memset(dp_reward, 0, sizeof(dp_reward));

    // === 逆推 DP ===
    // 从第 K 轮向前递推到第 1 轮
    for (int round = K_rounds; round >= 1; round--) {
        for (int mask = 0; mask < full; mask++) {

            double sum = 0.0;        // 本轮所有可能情况的最优期望之和

            // 枚举本系统抛出的宝物 i（等概率 1/n）
            for (int i = 0; i < nn; i++) {

                // 检查 mask 是否满足宝物 i 的前提条件
                // 即 require[i] 的所有位在 mask 中都是 1
                if ((mask & require[i]) == require[i]) {
                    // 前提满足，可以获取也可以放弃，取较优者
                    double take = dp_reward[round + 1][mask | (1 << i)] + score[i];
                    double skip = dp_reward[round + 1][mask];
                    sum += max(take, skip);
                } else {
                    // 前提不满足，只能放弃
                    sum += dp_reward[round + 1][mask];
                }
            }

            // 求平均（除以 n），得到本状态的期望
            dp_reward[round][mask] = sum / nn;
        }
    }

    // === 输出答案 ===
    // 第 1 轮开始，未收集任何宝物（mask=0）的期望得分
    printf("%.6f\n", dp_reward[1][0]);
}

// ============================================================
// 主函数
// ============================================================
int main() {
    // 题目选择：取消注释即可运行对应题目
    // solve_mondrian();  // 蒙德里安的梦想（多组数据）
    // solve_reward();    // 奖励关（期望DP）

    // 默认运行蒙德里安的梦想
    solve_mondrian();

    return 0;
}
