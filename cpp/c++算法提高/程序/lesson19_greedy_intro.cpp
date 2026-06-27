/*
 * ============================================================
 * Lesson 19: 贪心算法入门 — 局部最优到全局最优
 * C++ 算法提高课程
 *
 * 本文件包含两个经典贪心问题的完整实现：
 *   1. 找零钱问题 —— 每次选择面额最大的纸币
 *   2. 最大分数 —— 按分数降序排序，尽量将作业安排在截止日期前
 *
 * 编译: g++ -std=c++11 lesson19_greedy_intro.cpp -o lesson19_greedy_intro
 * 运行: ./lesson19_greedy_intro
 * ============================================================
 */

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

// ================================================================
// 问题1: 找零钱问题
// ================================================================
// 贪心策略: 在人民币面额体系 (100, 50, 20, 10, 5, 1) 下，
//           每次选择不超过剩余金额的最大面额纸币。
//           这套面额满足贪心选择性质，因此能得到全局最优解。
//
// 时间复杂度: O(k)，k 为面额种类数 (此处 k = 6)
// 空间复杂度: O(k)，用于存储各面额的张数
// ================================================================

void solveCoinChange() {
    cout << "========== 问题1: 找零钱问题 ==========" << endl;

    // 人民币面额，从大到小排列（贪心要求优先使用大面额）
    int denominations[] = {100, 50, 20, 10, 5, 1};
    int numTypes = 6;                       // 面额种类数
    int counts[6] = {0};                    // 记录每种面额的使用张数
    int N;                                  // 待找零金额

    cout << "请输入找零金额 N: ";
    cin >> N;

    int remain = N;                         // 剩余待找零金额
    int totalCoins = 0;                     // 总纸币张数

    // 贪心遍历：每种面额尽可能多用
    for (int i = 0; i < numTypes; i++) {
        counts[i] = remain / denominations[i];  // 当前面额最多用几张
        remain %= denominations[i];              // 更新剩余金额
        totalCoins += counts[i];                 // 累加总张数
    }

    // 输出结果
    cout << "\n最少需要 " << totalCoins << " 张纸币:" << endl;
    for (int i = 0; i < numTypes; i++) {
        if (counts[i] > 0) {
            cout << "  " << denominations[i] << "元: " << counts[i] << "张" << endl;
        }
    }
}

// ================================================================
// 问题2: 最大分数
// ================================================================
// 贪心策略: 将作业按分数从高到低排序，优先安排分数高的作业。
//           对每项作业，从截止日期当天往前找第一个空闲的日子，
//           若找到则安排该作业，否则放弃。
//
// 正确性: 这本质上是一个带权重的调度问题。按分数降序贪心是正确的，
//         因为如果某项高分作业被放弃，那么所有已安排的作业分数
//         都 >= 它，替换不会产生更优解。
//
// 时间复杂度: O(N log N + N * maxDeadline)
//             排序 O(N log N)，安排 O(N * maxDeadline)
// 空间复杂度: O(maxDeadline)，用于记录每天是否已被占用
// ================================================================

// 作业结构体
struct Job {
    int deadline;   // 截止日期
    int score;      // 完成可获得的分值
};

// 自定义排序：按分数从高到低
// 分数越高越值得优先安排，这是贪心策略的核心
bool compareByScore(Job a, Job b) {
    return a.score > b.score;
}

void solveMaxScore() {
    cout << "\n========== 问题2: 最大分数 ==========" << endl;

    int n;                                  // 作业数量
    cout << "请输入作业数量 N: ";
    cin >> n;

    Job jobs[1005];                         // 最多支持 1000 项作业
    int maxDeadline = 0;                    // 记录最晚的截止日期

    cout << "请依次输入每项作业的截止日期和分数 (d s):" << endl;
    for (int i = 0; i < n; i++) {
        cin >> jobs[i].deadline >> jobs[i].score;
        if (jobs[i].deadline > maxDeadline) {
            maxDeadline = jobs[i].deadline;
        }
    }

    // 贪心步骤1: 按分数从高到低排序
    sort(jobs, jobs + n, compareByScore);

    // used[t] = true 表示第 t 天已经被某项作业占用
    // 天数的范围是 [1, maxDeadline]
    bool used[1005] = {false};
    int totalScore = 0;                     // 获得的总分数

    // 贪心步骤2: 按分数从高到低，依次尝试安排每项作业
    for (int i = 0; i < n; i++) {
        // 从该作业的截止日期往前找空闲日子
        // 越晚安排越好，为其他作业留出更早的时间槽位
        for (int day = jobs[i].deadline; day >= 1; day--) {
            if (!used[day]) {               // 找到空闲日
                used[day] = true;           // 占用这一天
                totalScore += jobs[i].score; // 计入总分
                break;                      // 该作业已安排，处理下一项
            }
        }
        // 如果遍历完所有可能的日子都没找到，说明该作业无法完成，
        // 自动放弃，不加入总分
    }

    cout << "\n最大总分数: " << totalScore << endl;
}

// ================================================================
// 测试用例: 使用预设数据快速验证两个问题的正确性
// ================================================================

void runTests() {
    cout << "\n========== 自动测试用例 ==========" << endl;

    // --- 测试1: 找零钱问题 ---
    cout << "\n[测试1] 找零钱: N = 286" << endl;
    {
        int denominations[] = {100, 50, 20, 10, 5, 1};
        int counts[6] = {0};
        int N = 286, remain = N, total = 0;
        for (int i = 0; i < 6; i++) {
            counts[i] = remain / denominations[i];
            remain %= denominations[i];
            total += counts[i];
        }
        cout << "  最少纸币数: " << total << " (期望: 7)" << endl;
        // 100*2 + 50*1 + 20*1 + 10*1 + 5*1 + 1*1 = 7张 ✓
    }

    {
        cout << "\n[测试2] 找零钱: N = 63" << endl;
        int denominations[] = {100, 50, 20, 10, 5, 1};
        int counts[6] = {0};
        int N = 63, remain = N, total = 0;
        for (int i = 0; i < 6; i++) {
            counts[i] = remain / denominations[i];
            remain %= denominations[i];
            total += counts[i];
        }
        cout << "  最少纸币数: " << total << " (期望: 5)" << endl;
        // 50*1 + 10*1 + 1*3 = 5张 ✓
    }

    // --- 测试2: 最大分数 ---
    cout << "\n[测试3] 最大分数: 样例1" << endl;
    {
        // 5项作业: (2,60), (1,30), (2,40), (1,80), (3,100)
        Job jobs[5] = {{2,60}, {1,30}, {2,40}, {1,80}, {3,100}};
        int n = 5;
        sort(jobs, jobs + n, compareByScore);
        bool used[1005] = {false};
        int total = 0;
        for (int i = 0; i < n; i++) {
            for (int day = jobs[i].deadline; day >= 1; day--) {
                if (!used[day]) {
                    used[day] = true;
                    total += jobs[i].score;
                    break;
                }
            }
        }
        cout << "  最大分数: " << total << " (期望: 240)" << endl;
    }

    cout << "\n[测试4] 最大分数: 样例2" << endl;
    {
        // 4项作业: (1,50), (2,50), (2,100), (3,100)
        Job jobs[4] = {{1,50}, {2,50}, {2,100}, {3,100}};
        int n = 4;
        sort(jobs, jobs + n, compareByScore);
        bool used[1005] = {false};
        int total = 0;
        for (int i = 0; i < n; i++) {
            for (int day = jobs[i].deadline; day >= 1; day--) {
                if (!used[day]) {
                    used[day] = true;
                    total += jobs[i].score;
                    break;
                }
            }
        }
        cout << "  最大分数: " << total << " (期望: 250)" << endl;
    }

    cout << "\n========== 测试完成 ==========" << endl;
}

// ================================================================
// 主函数
// ================================================================

int main() {
    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║  第19课: 贪心算法入门                    ║" << endl;
    cout << "║  局部最优到全局最优                      ║" << endl;
    cout << "╚══════════════════════════════════════════╝" << endl;
    cout << endl;

    int choice;
    cout << "请选择操作:" << endl;
    cout << "  1 - 找零钱问题 (交互输入)" << endl;
    cout << "  2 - 最大分数问题 (交互输入)" << endl;
    cout << "  3 - 运行自动测试用例" << endl;
    cout << "  0 - 退出" << endl;
    cout << "请输入选择: ";
    cin >> choice;

    switch (choice) {
        case 1:
            solveCoinChange();
            break;
        case 2:
            solveMaxScore();
            break;
        case 3:
            runTests();
            break;
        case 0:
            cout << "再见！" << endl;
            break;
        default:
            cout << "无效选择！" << endl;
            break;
    }

    return 0;
}
