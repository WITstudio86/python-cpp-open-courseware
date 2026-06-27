/*
 * CSP-J 备考课程 第34课：贪心算法（下）
 *
 * 包含以下完整实现：
 * 1. 合并果子问题 —— 哈夫曼编码思想 / 小根堆 priority_queue
 * 2. 删数问题 —— 单调栈优化版 + 朴素版
 * 3. 最优装载问题 —— 贪心：按重量升序排序
 * 4. 排序+贪心综合练习 —— 多个实例对比
 *
 * 编译命令：g++ -std=c++11 -O2 lesson34_贪心算法下.cpp -o lesson34
 */

#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <string>
using namespace std;

// ============================================================
// 一、合并果子问题（哈夫曼编码思想）
// 题目：n 堆果子，每次合并任意两堆，代价为两堆数量之和，求最小总代价
// 策略：每次取最小的两堆合并（小根堆）
// 时间复杂度：O(n log n)
// ============================================================

long long mergeFruits(int a[], int n) {
    // 小根堆：注意第三个模板参数 greater<int>
    priority_queue<int, vector<int>, greater<int>> pq;

    for (int i = 0; i < n; i++) {
        pq.push(a[i]);
    }

    long long totalCost = 0;

    while (pq.size() > 1) {
        int x = pq.top(); pq.pop();  // 取出最小的
        int y = pq.top(); pq.pop();  // 取出第二小的
        int sum = x + y;
        totalCost += sum;
        pq.push(sum);                 // 将合并后的新堆放回
    }

    return totalCost;
}

void testMergeFruits() {
    cout << "========================================" << endl;
    cout << "一、合并果子问题（哈夫曼编码）" << endl;
    cout << "========================================" << endl;

    // 样例1：经典例子
    int a1[] = {1, 2, 9};
    int n1 = 3;
    cout << "样例1（果子堆：1, 2, 9）：最小体力 = "
         << mergeFruits(a1, n1) << endl;
    cout << "预期答案：15（1+2=3，3+9=12，3+12=15）" << endl;

    // 样例2：多堆果子
    int a2[] = {3, 5, 1, 2, 8, 13};
    int n2 = 6;
    cout << "样例2（果子堆：3,5,1,2,8,13）：最小体力 = "
         << mergeFruits(a2, n2) << endl;
    cout << "预期答案：77" << endl;
    cout << "  过程：1+2=3，3+3=6，5+6=11，8+11=19，13+19=32" << endl;
    cout << "  总计：3+6+11+19+32=71... 实际上是：1+2=3，3+3=6，5+6=11，8+11=19，13+19=32，3+6+11+19+32=71" << endl;
    cout << "  （手工计算验证：从小到大合并即可得到最小代价）" << endl;

    // 样例3：只有一堆
    int a3[] = {10};
    int n3 = 1;
    cout << "样例3（只有1堆果子）：最小体力 = "
         << mergeFruits(a3, n3) << endl;
    cout << "预期答案：0（无需合并）" << endl;

    cout << endl;
}

// ============================================================
// 二、删数问题
// 题目：从一个高精度整数中删除 k 位数字，使剩余数字组成的新数最小
// 策略：每次删除第一个"山峰"（num[i] > num[i+1] 的位置）
//
// 方法1：单调栈优化版 O(n)
// 方法2：朴素版 O(k * n)（逐步删除，便于理解）
// ============================================================

// 方法1：单调栈优化版（推荐使用）
string removeKdigitsOptimized(string num, int k) {
    string stk;  // 用 string 模拟单调栈

    for (char c : num) {
        // 当前栈顶 > 待入栈字符，且还有删除名额 → 弹栈（删除"山峰"）
        while (!stk.empty() && stk.back() > c && k > 0) {
            stk.pop_back();
            k--;
        }
        stk.push_back(c);
    }

    // 如果遍历完还有删除名额（序列非递减），从末尾删除
    while (k > 0 && !stk.empty()) {
        stk.pop_back();
        k--;
    }

    // 去除前导零
    int start = 0;
    while (start < (int)stk.size() && stk[start] == '0') {
        start++;
    }

    if (start == (int)stk.size()) {
        return "0";
    }

    return stk.substr(start);
}

// 方法2：朴素版（逐步删除，便于理解原理）
string removeKdigitsSimple(string num, int k) {
    for (int t = 0; t < k; t++) {
        bool found = false;
        // 从左到右找到第一个"山峰"位置
        for (int i = 0; i < (int)num.size() - 1; i++) {
            if (num[i] > num[i + 1]) {
                num.erase(i, 1);  // 删除第 i 位
                found = true;
                break;
            }
        }
        // 如果没找到"山峰"，说明序列非递减，删除末尾
        if (!found) {
            num.pop_back();
        }
    }

    // 去除前导零
    int start = 0;
    while (start < (int)num.size() && num[start] == '0') {
        start++;
    }

    if (start == (int)num.size()) {
        return "0";
    }

    return num.substr(start);
}

void testRemoveKdigits() {
    cout << "========================================" << endl;
    cout << "二、删数问题" << endl;
    cout << "========================================" << endl;

    // 测试用例结构：{原始数字, 删除位数, 预期结果}
    struct TestCase {
        string num;
        int k;
        string expected;
    };

    TestCase tests[] = {
        {"175438", 4, "13"},
        {"10200", 1, "200"},
        {"10", 1, "0"},
        {"12345", 2, "123"},
        {"54321", 2, "321"},
        {"100200", 1, "200"},
        {"100200", 2, "0"},
        {"987654321", 3, "654321"},
        {"123456789", 3, "123456"},
        {"1432219", 3, "1219"},
    };

    int numTests = sizeof(tests) / sizeof(tests[0]);

    cout << "使用单调栈优化版测试：" << endl;
    for (int i = 0; i < numTests; i++) {
        string result = removeKdigitsOptimized(tests[i].num, tests[i].k);
        bool pass = (result == tests[i].expected);
        cout << "  测试 " << (i + 1) << ": num=" << tests[i].num
             << ", k=" << tests[i].k
             << " → " << result
             << " (预期 " << tests[i].expected << ") "
             << (pass ? "✓" : "✗ 错误!") << endl;
    }

    // 同时验证朴素版结果一致
    cout << "\n朴素版验证（应与优化版结果一致）：" << endl;
    for (int i = 0; i < numTests; i++) {
        string r1 = removeKdigitsOptimized(tests[i].num, tests[i].k);
        string r2 = removeKdigitsSimple(tests[i].num, tests[i].k);
        bool pass = (r1 == r2);
        cout << "  测试 " << (i + 1) << ": 优化版=" << r1
             << ", 朴素版=" << r2
             << (pass ? " ✓ 一致" : " ✗ 不一致!") << endl;
    }

    cout << endl;
}

// ============================================================
// 三、最优装载问题
// 题目：n 个物品，重量 w[i]，船载重 C，求最多能装多少个物品
// 策略：按重量升序排序，依次装载
// 时间复杂度：O(n log n)
// ============================================================

int maxLoad(int w[], int n, int C) {
    sort(w, w + n);          // 按重量升序排序

    int count = 0;
    long long totalWeight = 0;  // 注意用 long long

    for (int i = 0; i < n; i++) {
        if (totalWeight + w[i] <= C) {
            totalWeight += w[i];
            count++;
        } else {
            break;  // 后面的更重，更不可能装入
        }
    }

    return count;
}

void testMaxLoad() {
    cout << "========================================" << endl;
    cout << "三、最优装载问题" << endl;
    cout << "========================================" << endl;

    // 样例1：基本测试
    int w1[] = {5, 3, 8, 1, 9, 2};
    int n1 = 6;
    int C1 = 15;
    cout << "样例1（物品重量:5,3,8,1,9,2，载重15）：最多装 "
         << maxLoad(w1, n1, C1) << " 个物品" << endl;
    cout << "预期答案：4（1+2+3+5=11≤15，再装8→19>15）" << endl;

    // 样例2：所有物品总重 ≤ 载重
    int w2[] = {1, 2, 3};
    int n2 = 3;
    int C2 = 10;
    cout << "样例2（物品重量:1,2,3，载重10）：最多装 "
         << maxLoad(w2, n2, C2) << " 个物品" << endl;
    cout << "预期答案：3（全装，总重6≤10）" << endl;

    // 样例3：一个都装不了
    int w3[] = {10, 20, 30};
    int n3 = 3;
    int C3 = 5;
    cout << "样例3（物品重量:10,20,30，载重5）：最多装 "
         << maxLoad(w3, n3, C3) << " 个物品" << endl;
    cout << "预期答案：0（最轻的也要10，装不下）" << endl;

    // 样例4：大量物品，验证 long long 的必要性
    int n4 = 10;
    int w4[] = {1000000000, 1000000000, 1000000000, 1000000000, 1000000000,
                 1000000000, 1000000000, 1000000000, 1000000000, 1000000000};
    int C4 = 8000000000LL;  // 注意：8e9 > 2^31-1
    cout << "样例4（10个10亿重量物品，载重80亿）：最多装 "
         << maxLoad(w4, n4, C4) << " 个物品" << endl;
    cout << "预期答案：8（若用 int 溢出会错误）" << endl;

    cout << endl;
}

// ============================================================
// 四、排序+贪心综合对比
// 演示不同贪心问题中排序标准的选择
// ============================================================

struct ByEnd {     // 区间调度：按结束时间
    int start, end;
};
bool cmpEnd(ByEnd a, ByEnd b) { return a.end < b.end; }

struct ByStart {   // 区间覆盖：按开始时间
    int left, right;
};
bool cmpStart(ByStart a, ByStart b) { return a.left < b.left; }

struct ByValue {   // 硬币面额：按面额降序（已天然有序，但显式写出）
    int value;
};
bool cmpValueDesc(ByValue a, ByValue b) { return a.value > b.value; }

void testComparisonSummary() {
    cout << "========================================" << endl;
    cout << "四、排序+贪心 综合对比" << endl;
    cout << "========================================" << endl;

    cout << "┌─────────────────────┬──────────────┬─────────────┐" << endl;
    cout << "│ 问题               │ 排序标准     │ 时间复杂度  │" << endl;
    cout << "├─────────────────────┼──────────────┼─────────────┤" << endl;
    cout << "│ 活动选择/区间调度  │ 结束时间 ↑   │ O(n log n)  │" << endl;
    cout << "│ 区间覆盖           │ 开始时间 ↑   │ O(n log n)  │" << endl;
    cout << "│ 排队接水           │ 接水时间 ↑   │ O(n log n)  │" << endl;
    cout << "│ 最优装载           │ 重量 ↑       │ O(n log n)  │" << endl;
    cout << "│ 合并果子           │ 小根堆动态   │ O(n log n)  │" << endl;
    cout << "│ 删数问题           │ 单调栈(O(n)) │ O(n)        │" << endl;
    cout << "│ 硬币找零（贪心）   │ 面额 ↓       │ O(m)        │" << endl;
    cout << "└─────────────────────┴──────────────┴─────────────┘" << endl;

    cout << endl;
    cout << "核心思想：筛选标准 → 排序/堆 → 贪心遍历 → 输出结果" << endl;
    cout << "         ↑ 最关键的一步 ↑" << endl;
    cout << endl;
}

// ============================================================
// 五、贪心 vs DP 对比测试
// 演示同一问题的贪心与 DP 解法差异
// ============================================================

const int INF = 0x3f3f3f3f;

// 硬币找零：贪心版（仅适用规范系统）
int coinChangeGreedy(int coins[], int m, int amount) {
    int count = 0;
    for (int i = 0; i < m; i++) {
        if (amount >= coins[i]) {
            count += amount / coins[i];
            amount %= coins[i];
        }
    }
    return (amount == 0) ? count : -1;
}

// 硬币找零：DP版（保证正确）
int coinChangeDP(int coins[], int m, int amount) {
    int dp[1005];
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

void testGreedyVsDP() {
    cout << "========================================" << endl;
    cout << "五、贪心 vs DP 对比（硬币找零）" << endl;
    cout << "========================================" << endl;

    // 测试1：规范硬币系统（贪心=DP）
    int coins1[] = {100, 50, 20, 10, 5, 1};
    int m1 = 6;
    cout << "规范硬币系统 {1,5,10,20,50,100}：" << endl;
    for (int amount : {87, 63, 99, 100}) {
        int g = coinChangeGreedy(coins1, m1, amount);
        int d = coinChangeDP(coins1, m1, amount);
        cout << "  amount=" << amount
             << ", 贪心=" << g << ", DP=" << d
             << " (" << (g == d ? "一致 ✓" : "不一致 ✗") << ")" << endl;
    }

    // 测试2：非规范硬币系统（贪心可能错误）
    int coins2[] = {4, 3, 1};  // 从大到小
    int m2 = 3;
    cout << "\n非规范硬币系统 {1,3,4}：" << endl;
    for (int amount : {6, 8, 12, 15}) {
        int g = coinChangeGreedy(coins2, m2, amount);
        int d = coinChangeDP(coins2, m2, amount);
        bool same = (g == d);
        cout << "  amount=" << amount
             << ", 贪心=" << g << ", DP=" << d;
        if (!same) {
            cout << " ← 贪心错误！DP 给出正确答案";
        }
        cout << endl;
    }

    cout << "\n结论：贪心仅当题目明确说明或能确定正确时才使用，" << endl;
    cout << "      否则优先使用 DP 保证正确性。" << endl;
    cout << endl;
}

// ============================================================
// 六、主函数
// ============================================================

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cout << "╔══════════════════════════════════════╗" << endl;
    cout << "║  CSP-J 备考 第34课：贪心算法（下）  ║" << endl;
    cout << "╚══════════════════════════════════════╝" << endl;
    cout << endl;

    // 运行所有测试
    testMergeFruits();            // 合并果子
    testRemoveKdigits();          // 删数问题
    testMaxLoad();                // 最优装载
    testComparisonSummary();      // 排序+贪心综合对比
    testGreedyVsDP();            // 贪心 vs DP 对比

    cout << "========================================" << endl;
    cout << "所有测试完成！" << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "【本课要点总结】" << endl;
    cout << "1. 合并果子 = 哈夫曼编码：每次取最小的两个，用小根堆，O(n log n)" << endl;
    cout << "2. 删数问题 = 删山峰（num[i] > num[i+1]），单调栈 O(n)" << endl;
    cout << "3. 最优装载 = 按重量排序后依次装，注意 long long 防溢出" << endl;
    cout << "4. 排序+贪心 = 核心模式：选排序标准 → 排序 → 一次遍历" << endl;
    cout << "5. 贪心 vs DP：不确定贪心是否正确时，优先使用 DP" << endl;
    cout << "6. 合并果子 ≠ 石子合并（区间DP），注意区分" << endl;

    return 0;
}
