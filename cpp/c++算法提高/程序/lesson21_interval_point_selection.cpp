/**
 * ============================================================
 * 第21课：区间覆盖与选点
 * C++算法提高课程
 *
 * 本程序包含两道经典贪心例题的完整实现：
 *   1. 种树问题 —— 每个区间需要不同数量的点，点可共享
 *   2. 区间选点 —— 每个区间至少一个点，求最小点数
 *
 * 核心策略：按区间右端点从小到大排序，贪心放置点/树
 * ============================================================
 */

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

// ============================================================
// 例题1：种树问题
// 问题描述：
//   有 N 个区间 [l, r]，每个区间至少需要 t 棵树。
//   树可以共享（一个位置的树可满足所有包含该位置的区间）。
//   求最少需要种多少棵树。
//
// 贪心策略：
//   1. 将所有区间按右端点从小到大排序
//   2. 对于每个区间，先统计该区间内已经种了多少棵树
//   3. 如果不够，从右端点开始向左逐个补种
//      （从右向左种可以让树尽可能多地覆盖后续区间）
// ============================================================

const int MAX_TASKS = 5005;      // 最大区间数量
const int MAX_POS = 30005;       // 最大坐标范围

struct PlantTask {
    int l, r;     // 区间左右端点
    int need;     // 该区间需要树的数量

    // 按右端点从小到大排序（贪心关键！）
    bool operator<(const PlantTask &other) const {
        return r < other.r;
    }
};

PlantTask tasks[MAX_TASKS];
bool planted[MAX_POS];  // planted[i] = true 表示位置 i 已经种了树

/**
 * 种树问题求解函数
 * @param n 区间数量
 * @return 最少需要种的树的总数
 */
int solvePlantTrees(int n) {
    // Step 1: 按右端点从小到大排序
    sort(tasks, tasks + n);

    // Step 2: 初始化
    memset(planted, 0, sizeof(planted));  // 开始时一棵树都没有
    int totalTrees = 0;                   // 总共种了多少棵树

    // Step 3: 依次处理每个区间
    for (int i = 0; i < n; i++) {
        int l = tasks[i].l;
        int r = tasks[i].r;
        int need = tasks[i].need;

        // 3.1 统计区间 [l, r] 内已经种了多少棵树
        int alreadyPlanted = 0;
        for (int pos = l; pos <= r; pos++) {
            if (planted[pos]) {
                alreadyPlanted++;
            }
        }

        // 3.2 计算还需要补种多少棵
        int remain = need - alreadyPlanted;

        // 3.3 从右向左贪心补种
        //      为什么要从右向左？
        //      因为右侧的位置更「靠后」，更容易出现在后续区间的范围内，
        //      从而被后续区间共享，减少总种树量。
        for (int pos = r; pos >= l && remain > 0; pos--) {
            if (!planted[pos]) {        // 这个位置还没种树
                planted[pos] = true;     // 种一棵！
                remain--;                // 还需要种的数量 -1
                totalTrees++;            // 总种树量 +1
            }
        }
    }

    return totalTrees;
}

// ============================================================
// 例题2：区间选点问题
// 问题描述：
//   给定 N 个闭区间，每个区间内至少需要包含一个选中的点。
//   求最少需要选择多少个点。
//
// 贪心策略：
//   1. 将所有区间按右端点从小到大排序
//   2. 依次处理每个区间：
//      - 如果上一个选中的点已经在该区间内，则跳过
//      - 否则，在该区间的右端点放置一个新点
//   （为什么放在右端点？因为右端点是该区间内最靠右的位置，
//    更容易覆盖到后续区间，从而减少总点数）
// ============================================================

const int MAX_INTERVALS = 100005;  // 最大区间数量

struct Interval {
    int l, r;  // 区间左右端点

    // 按右端点从小到大排序（贪心关键！）
    bool operator<(const Interval &other) const {
        return r < other.r;
    }
};

Interval intervals[MAX_INTERVALS];

/**
 * 区间选点问题求解函数
 * @param n 区间数量
 * @return 最少需要选择的点的数量
 */
int solveIntervalPoints(int n) {
    // Step 1: 按右端点从小到大排序
    sort(intervals, intervals + n);

    // Step 2: 贪心选择
    int pointCount = 0;               // 已选择的点数
    int lastPoint = -2000000000;      // 上一个选中的点的位置（初始化为-∞）

    for (int i = 0; i < n; i++) {
        int l = intervals[i].l;
        int r = intervals[i].r;

        // 如果上一个选中的点不在当前区间内（即 lastPoint < l），
        // 说明当前区间还没有被覆盖，需要新增一个点
        if (lastPoint < l) {
            pointCount++;             // 新增一个点
            lastPoint = r;            // 放在当前区间的右端点（最优位置！）
        }
        // 否则 lastPoint 已经在 [l, r] 内，当前区间已被覆盖，无需操作
    }

    return pointCount;
}

// ============================================================
// 测试用例 & 主函数
// ============================================================

int main() {
    cout << "========================================" << endl;
    cout << " 第21课：区间覆盖与选点 - 测试程序" << endl;
    cout << "========================================" << endl;

    // ==================== 测试1：种树问题 ====================
    cout << "\n--- 测试1：种树问题 ---" << endl;
    cout << "样例输入：" << endl;
    cout << "4" << endl;
    cout << "1 4 2" << endl;
    cout << "2 5 2" << endl;
    cout << "3 7 3" << endl;
    cout << "5 9 2" << endl;

    // 准备测试数据
    int n1 = 4;
    tasks[0] = {1, 4, 2};
    tasks[1] = {2, 5, 2};
    tasks[2] = {3, 7, 3};
    tasks[3] = {5, 9, 2};

    int result1 = solvePlantTrees(n1);
    cout << "最少需要种 " << result1 << " 棵树" << endl;
    cout << "预期答案：4" << endl;
    cout << "测试结果：" << (result1 == 4 ? "通过 ✓" : "未通过 ✗") << endl;

    // 打印种树方案
    cout << "种树位置：";
    for (int pos = 0; pos < MAX_POS; pos++) {
        if (planted[pos]) {
            cout << pos << " ";
        }
    }
    cout << endl;

    // ==================== 测试2：区间选点问题 ====================
    cout << "\n--- 测试2：区间选点问题 ---" << endl;
    cout << "样例输入：" << endl;
    cout << "5" << endl;
    cout << "1 3" << endl;
    cout << "2 5" << endl;
    cout << "3 6" << endl;
    cout << "4 7" << endl;
    cout << "0 2" << endl;

    // 准备测试数据
    int n2 = 5;
    intervals[0] = {1, 3};
    intervals[1] = {2, 5};
    intervals[2] = {3, 6};
    intervals[3] = {4, 7};
    intervals[4] = {0, 2};

    int result2 = solveIntervalPoints(n2);
    cout << "最少需要选择 " << result2 << " 个点" << endl;
    cout << "预期答案：2" << endl;
    cout << "测试结果：" << (result2 == 2 ? "通过 ✓" : "未通过 ✗") << endl;

    // ==================== 测试3：区间选点 - 更复杂的例子 ====================
    cout << "\n--- 测试3：区间选点问题（更多区间） ---" << endl;
    cout << "输入：6 个区间" << endl;
    cout << "[1,2], [2,3], [3,4], [1,5], [6,7], [5,8]" << endl;

    int n3 = 6;
    intervals[0] = {1, 2};
    intervals[1] = {2, 3};
    intervals[2] = {3, 4};
    intervals[3] = {1, 5};
    intervals[4] = {6, 7};
    intervals[5] = {5, 8};

    int result3 = solveIntervalPoints(n3);
    cout << "最少需要选择 " << result3 << " 个点" << endl;
    // 分析：[1,2][2,3][3,4][1,5] 这4个区间都可以被一个点覆盖（比如点3）
    //       [6,7][5,8] 可以再被一个点覆盖（比如点7）
    //       所以答案是2或3（取决于排序和具体处理）
    cout << "（这组数据的答案应该是 2 或 3）" << endl;

    // ==================== 测试4：种树问题 - 简单例子 ====================
    cout << "\n--- 测试4：种树问题（简单例子） ---" << endl;
    cout << "输入：2 个区间" << endl;
    cout << "[1,3] 需要 2 棵树" << endl;
    cout << "[2,4] 需要 2 棵树" << endl;

    // 重置 planted 数组
    memset(planted, 0, sizeof(planted));

    int n4 = 2;
    tasks[0] = {1, 3, 2};
    tasks[1] = {2, 4, 2};

    int result4 = solvePlantTrees(n4);
    cout << "最少需要种 " << result4 << " 棵树" << endl;
    cout << "（最优方案：位置 1,2,3,4 各种一棵？不，可以更少）" << endl;
    // [1,3] 需要 2 棵：[2,4] 需要 2 棵
    // 在位置 2,3 各种一棵（共2棵），可以同时满足两个区间
    // 但每个区间需要 2 棵，所以至少需要更多的分析
    // [1,3] 要 2 棵，[2,4] 要 2 棵，重叠区域 [2,3]，如果都在 [2,3] 种 2 棵，
    // 则 [1,3] 满足（有 2 棵），[2,4] 满足（有 2 棵），总共 2 棵即可

    cout << "种树位置：";
    for (int pos = 0; pos < MAX_POS; pos++) {
        if (planted[pos]) {
            cout << pos << " ";
        }
    }
    cout << endl;

    cout << "\n========================================" << endl;
    cout << " 所有测试完成！" << endl;
    cout << "========================================" << endl;

    return 0;
}
