/*
 * CSP-J 备考课程 第33课：贪心算法（上）
 *
 * 包含以下完整实现：
 * 1. 活动选择问题（区间调度）—— 贪心策略：按结束时间排序
 * 2. 硬币找零问题 —— 贪心版（仅适用规范硬币系统）+ DP版（通用正确版）
 * 3. 区间覆盖问题 —— 贪心策略：按左端点排序，选最大右端点
 * 4. 排队接水问题 —— 贪心策略：短作业优先
 *
 * 编译命令：g++ -std=c++11 -O2 lesson33_贪心算法上.cpp -o lesson33
 */

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

// ============================================================
// 一、活动选择问题（区间调度）
// 题目：给定 n 个活动 [start, end)，选择最多的互不重叠的活动
// 策略：按结束时间升序排序，依次选择不冲突的活动
// 时间复杂度：O(n log n)
// ============================================================

const int MAXN = 100005;

struct Activity {
    int start, end;
};

bool cmpByEnd(Activity a, Activity b) {
    return a.end < b.end;  // 严格小于，不能写成 <=
}

int activitySelection(Activity a[], int n) {
    sort(a, a + n, cmpByEnd);       // 按结束时间排序

    int ans = 1;                     // 至少选择第一个活动
    int lastEnd = a[0].end;

    for (int i = 1; i < n; i++) {
        if (a[i].start >= lastEnd) { // 当前活动与已选活动不冲突
            ans++;
            lastEnd = a[i].end;
        }
    }
    return ans;
}

void testActivitySelection() {
    cout << "========================================" << endl;
    cout << "一、活动选择问题（区间调度）" << endl;
    cout << "========================================" << endl;

    // 样例1：课堂上讲解的例子
    Activity a1[] = {
        {1, 4}, {3, 5}, {0, 6}, {5, 7}, {8, 9}, {5, 9}
    };
    int n1 = 6;
    cout << "样例1（6个活动）：最多可选 " << activitySelection(a1, n1) << " 个活动" << endl;
    cout << "预期答案：3（活动 [1,4)、[5,7)、[8,9)）" << endl;

    // 样例2：所有活动都重叠
    Activity a2[] = {
        {1, 10}, {2, 9}, {3, 8}, {4, 7}
    };
    int n2 = 4;
    cout << "样例2（全部重叠）：最多可选 " << activitySelection(a2, n2) << " 个活动" << endl;
    cout << "预期答案：1" << endl;

    // 样例3：所有活动互不重叠
    Activity a3[] = {
        {1, 2}, {3, 4}, {5, 6}, {7, 8}
    };
    int n3 = 4;
    cout << "样例3（全不重叠）：最多可选 " << activitySelection(a3, n3) << " 个活动" << endl;
    cout << "预期答案：4" << endl;

    cout << endl;
}

// ============================================================
// 二、硬币找零问题
// 题目：给定面额数组 coins 和金额 amount，求最少硬币数
// 方法1（贪心）：每次选最大面额，仅适用"规范硬币系统"
// 方法2（DP）：完全背包，保证正确，适用所有情况
// ============================================================

// 方法1：贪心策略（仅适用于人民币等规范硬币系统）
int greedyCoinChange(int coins[], int m, int amount) {
    int count = 0;
    for (int i = 0; i < m; i++) {
        if (amount >= coins[i]) {
            int num = amount / coins[i];
            count += num;
            amount -= num * coins[i];
        }
        if (amount == 0) break;
    }
    return (amount == 0) ? count : -1;
}

// 方法2：动态规划（完全背包，保证正确，适用于任何硬币系统）
const int INF = 0x3f3f3f3f;
const int MAX_AMOUNT = 10005;

int dpCoinChange(int coins[], int m, int amount) {
    int dp[MAX_AMOUNT];
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;

    for (int i = 1; i <= amount; i++) {
        for (int j = 0; j < m; j++) {
            if (i >= coins[j]) {
                dp[i] = min(dp[i], dp[i - coins[j]] + 1);
            }
        }
    }
    return (dp[amount] == INF) ? -1 : dp[amount];
}

void testCoinChange() {
    cout << "========================================" << endl;
    cout << "二、硬币找零问题" << endl;
    cout << "========================================" << endl;

    // 测试1：人民币面额（规范硬币系统，贪心正确）
    int rmb[] = {100, 50, 20, 10, 5, 1};  // 按从大到小排序
    int m1 = 6;
    int amount1 = 87;
    cout << "测试1（人民币面额找零87元）：" << endl;
    cout << "  贪心法结果：" << greedyCoinChange(rmb, m1, amount1) << " 枚硬币" << endl;
    cout << "  DP法结果：  " << dpCoinChange(rmb, m1, amount1) << " 枚硬币" << endl;
    cout << "  预期答案：6 枚（50+20+10+5+1+1）" << endl;

    // 测试2：非规范硬币系统（贪心会出错！）
    int bad[] = {4, 3, 1};  // 按从大到小排序
    int m2 = 3;
    int amount2 = 6;
    cout << "测试2（非规范硬币{4,3,1}找零6元，贪心会出错！）：" << endl;
    cout << "  贪心法结果：" << greedyCoinChange(bad, m2, amount2) << " 枚硬币（错误！）" << endl;
    cout << "  DP法结果：  " << dpCoinChange(bad, m2, amount2) << " 枚硬币（正确）" << endl;
    cout << "  预期答案：2 枚（3+3），贪心给出 3 枚（4+1+1）" << endl;

    // 测试3：无法找零的情况
    int coins3[] = {5, 2};  // 按从大到小
    int m3 = 2;
    int amount3 = 3;
    cout << "测试3（硬币{5,2}无法凑出3元）：" << endl;
    cout << "  贪心法结果：" << greedyCoinChange(coins3, m3, amount3) << "（-1表示无法凑出）" << endl;
    cout << "  DP法结果：  " << dpCoinChange(coins3, m3, amount3) << "（-1表示无法凑出）" << endl;

    cout << endl;
}

// ============================================================
// 三、区间覆盖问题
// 题目：用最少的给定区间覆盖目标区间 [targetL, targetR]
// 策略：按左端点排序，每次选择能覆盖当前左端点且右端点最远的区间
// 时间复杂度：O(n log n)
// ============================================================

struct Interval {
    int left, right;
};

bool cmpByLeft(Interval a, Interval b) {
    return a.left < b.left;
}

int intervalCover(Interval a[], int n, int targetL, int targetR) {
    sort(a, a + n, cmpByLeft);          // 按左端点升序排序

    int ans = 0;                         // 使用的区间数
    int currentR = targetL;              // 当前已覆盖到的右边界
    int i = 0;

    while (currentR < targetR) {
        int maxR = currentR;
        // 在所有左端点 <= currentR 的区间中，选右端点最大的
        while (i < n && a[i].left <= currentR) {
            if (a[i].right > maxR) {
                maxR = a[i].right;
            }
            i++;
        }
        if (maxR == currentR) {          // 无法继续延伸，无解
            return -1;
        }
        ans++;
        currentR = maxR;
    }
    return ans;
}

void testIntervalCover() {
    cout << "========================================" << endl;
    cout << "三、区间覆盖问题" << endl;
    cout << "========================================" << endl;

    // 样例1：正常覆盖
    Interval a1[] = {
        {1, 5}, {2, 8}, {3, 6}, {5, 10}
    };
    int n1 = 4;
    int ans1 = intervalCover(a1, n1, 1, 10);
    cout << "样例1（覆盖区间[1,10]）：最少需要 " << ans1 << " 个区间" << endl;
    cout << "预期答案：2（[1,5] + [5,10] 或 [2,8] + [5,10]）" << endl;

    // 样例2：无解情况（区间无法覆盖到目标右端点）
    Interval a2[] = {
        {1, 3}, {2, 4}
    };
    int n2 = 2;
    int ans2 = intervalCover(a2, n2, 1, 10);
    cout << "样例2（覆盖区间[1,10]，区间不够）：答案 = " << ans2 << endl;
    cout << "预期答案：-1（无解）" << endl;

    // 样例3：只需要一个区间
    Interval a3[] = {
        {0, 100}, {10, 20}, {30, 40}
    };
    int n3 = 3;
    int ans3 = intervalCover(a3, n3, 5, 50);
    cout << "样例3（覆盖区间[5,50]，有[0,100]大区间）：最少需要 " << ans3 << " 个区间" << endl;
    cout << "预期答案：1" << endl;

    cout << endl;
}

// ============================================================
// 四、排队接水问题
// 题目：n 个人接水，第 i 个人需要 t[i] 时间，求最小总等待时间
// 策略：按接水时间升序排序（短作业优先）
// 时间复杂度：O(n log n)
// ============================================================

long long minTotalWaitTime(int t[], int n) {
    sort(t, t + n);                      // 短作业优先

    long long totalWait = 0;             // 注意用 long long 防溢出
    long long currentTime = 0;

    for (int i = 0; i < n; i++) {
        currentTime += t[i];             // 第 i 个人完成接水的时间
        totalWait += currentTime;        // 累加到总等待时间
    }
    return totalWait;
}

void testQueueWater() {
    cout << "========================================" << endl;
    cout << "四、排队接水问题" << endl;
    cout << "========================================" << endl;

    // 样例1
    int t1[] = {3, 1, 4, 2};
    int n1 = 4;
    cout << "样例1（接水时间：3,1,4,2）：最小总等待时间 = "
         << minTotalWaitTime(t1, n1) << endl;
    cout << "预期答案：20（排序后1,2,3,4，完成时间1,3,6,10，总和20）" << endl;

    // 样例2：所有人时间相同
    int t2[] = {5, 5, 5, 5};
    int n2 = 4;
    cout << "样例2（全部5分钟）：最小总等待时间 = "
         << minTotalWaitTime(t2, n2) << endl;
    cout << "预期答案：5+10+15+20 = 50" << endl;

    // 样例3：只有一个人
    int t3[] = {10};
    int n3 = 1;
    cout << "样例3（只有1人）：最小总等待时间 = "
         << minTotalWaitTime(t3, n3) << endl;
    cout << "预期答案：10" << endl;

    cout << endl;
}

// ============================================================
// 五、主函数
// ============================================================

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cout << "╔══════════════════════════════════════╗" << endl;
    cout << "║  CSP-J 备考 第33课：贪心算法（上）  ║" << endl;
    cout << "╚══════════════════════════════════════╝" << endl;
    cout << endl;

    // 运行所有测试
    testActivitySelection();     // 活动选择
    testCoinChange();            // 硬币找零
    testIntervalCover();         // 区间覆盖
    testQueueWater();            // 排队接水

    cout << "========================================" << endl;
    cout << "所有测试完成！" << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "【本课要点总结】" << endl;
    cout << "1. 贪心算法核心：每步选择当前最优，局部最优→全局最优" << endl;
    cout << "2. 适用条件：贪心选择性质 + 最优子结构性质" << endl;
    cout << "3. 活动选择：按结束时间排序，O(n log n)" << endl;
    cout << "4. 硬币找零：贪心仅适用于规范硬币系统，否则用DP" << endl;
    cout << "5. 区间覆盖：按左端点排序，选最大右端点" << endl;
    cout << "6. 排队接水：短作业优先，排序后累加" << endl;

    return 0;
}
