/*
 * ================================================================
 * C++算法提高 第20课：区间调度问题——安排尽可能多的活动
 * ================================================================
 *
 * 算法知识点：
 *   - 贪心算法：按结束时间排序，选择不重叠的区间
 *   - 结构体存储区间（开始时间 + 结束时间）
 *   - sort 自定义比较函数（按结束时间从小到大排序）
 *   - 贪心选择性质：每次选结束最早且不与已选区间重叠的区间
 *
 * 经典例题：
 *   例题1 - 活动选择：N个活动，选最多互不冲突的活动
 *   例题2 - 最多不重叠区间：N个区间，选最多不重叠区间并输出编号
 */

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// ================================================================
// 区间结构体定义
// 用于存储每个区间（活动）的开始时间和结束时间
// 例题2中额外存储原始编号，用于输出选中的区间列表
// ================================================================

struct Interval {
    int start;  // 开始时间（区间左端点）
    int end;    // 结束时间（区间右端点）

    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

// 带编号的区间结构体（用于例题2需要输出原始编号的场景）
struct IndexedInterval {
    int start;  // 开始时间（区间左端点）
    int end;    // 结束时间（区间右端点）
    int id;     // 原始输入编号（从1开始）

    IndexedInterval() : start(0), end(0), id(0) {}
    IndexedInterval(int s, int e, int i) : start(s), end(e), id(i) {}
};

// ================================================================
// 自定义比较函数：按结束时间从小到大排序
// 这是区间调度贪心算法的核心——结束最早的区间优先考虑
// 如果结束时间相同，按开始时间排序（虽然不影响最终答案）
// ================================================================

bool cmpByEnd(const Interval &a, const Interval &b) {
    return a.end < b.end;  // 结束时间早的排在前面
}

bool cmpByEndIndexed(const IndexedInterval &a, const IndexedInterval &b) {
    if (a.end != b.end) return a.end < b.end;    // 主要按结束时间排序
    return a.start < b.start;                      // 结束时间相同时按开始时间排序
}

// ================================================================
// 例题1：活动选择问题
// 题目描述：
//   学校有 N 个活动需要申请礼堂。每个活动 i 有开始时间 s[i]
//   和结束时间 f[i]（s[i] < f[i]，均为整数）。礼堂同一时间只能
//   被一个活动使用。求最多可以选择多少个互不冲突的活动。
//
// 贪心策略：
//   1. 将所有活动按结束时间从小到大排序
//   2. 从排好序的列表中，依次选取开始时间 ≥ 上一个已选活动结束时间的活动
//   3. 每选中一个活动，更新"上一个已选活动的结束时间"
//
// 正确性（交换论证直观理解）：
//   结束最早的活动，留给后面活动的时间最多。
//   任何一个最优解都可以通过"把第一个活动换成结束最早的活动"
//   而保持不变或变得更好。
//
// 时间复杂度：O(N log N) — 排序是瓶颈
// 空间复杂度：O(N) — 存储 N 个活动
// ================================================================

int activitySelection(Interval activities[], int n) {
    if (n == 0) return 0;  // 没有活动的情况

    // 第一步：按结束时间从小到大排序
    sort(activities, activities + n, cmpByEnd);

    // 第二步：贪心选择
    int count = 1;                        // 第一个活动（结束最早）必选
    int lastEnd = activities[0].end;      // 记录上一个选中活动的结束时间

    for (int i = 1; i < n; i++) {
        // 如果当前活动的开始时间 ≥ 上一个选中活动的结束时间
        // 说明当前活动与已选活动不重叠，可以选中
        if (activities[i].start >= lastEnd) {
            count++;                       // 选中当前活动
            lastEnd = activities[i].end;   // 更新最后结束时间
        }
    }

    return count;
}

// ================================================================
// 例题2：最多不重叠区间
// 题目描述：
//   给定数轴上的 N 个闭区间 [l_i, r_i]。选出尽可能多的区间，
//   使得任意两个选出的区间互不重叠（即 r_a ≤ l_b 或 r_b ≤ l_a）。
//   输出最多区间个数，以及一种具体选法（按原输入顺序输出编号）。
//
// 与例题1的关系：
//   本质上和活动选择是同一个问题。区别在于：
//   1. 需要记录每个区间的原始编号（因为排序会打乱顺序）
//   2. 需要输出具体的选法，而不仅仅是数量
//
// 关键技巧：
//   - 在结构体中增加 id 字段，排序前记录原始编号
//   - 使用 vector 动态记录被选中的区间编号
// ================================================================

void maxNonOverlapIntervals(IndexedInterval intervals[], int n) {
    if (n == 0) {
        cout << 0 << endl;
        return;
    }

    // 第一步：按右端点从小到大排序
    sort(intervals, intervals + n, cmpByEndIndexed);

    // 第二步：贪心选择
    vector<int> chosen;                       // 存储被选中区间的原始编号
    chosen.push_back(intervals[0].id);        // 第一个区间（右端点最小）必选
    int lastR = intervals[0].end;             // 上一个选中区间的右端点

    for (int i = 1; i < n; i++) {
        // 当前区间的左端点 ≥ 上一个选中区间的右端点 → 不重叠，可以选
        if (intervals[i].start >= lastR) {
            chosen.push_back(intervals[i].id);
            lastR = intervals[i].end;         // 更新右端点
        }
    }

    // 第三步：输出结果
    cout << chosen.size() << endl;            // 最大不重叠区间数
    for (int i = 0; i < (int)chosen.size(); i++) {
        if (i > 0) cout << " ";
        cout << chosen[i];                    // 输出被选中区间的原始编号
    }
    cout << endl;
}

// ================================================================
// 测试函数：例题1 — 活动选择
// ================================================================

void testActivitySelection() {
    cout << "╔══════════════════════════════════════════════╗" << endl;
    cout << "║     例题1：活动选择问题                       ║" << endl;
    cout << "╚══════════════════════════════════════════════╝" << endl;
    cout << endl;

    // 测试数据：6个活动
    // 活动索引:  0      1      2      3      4      5
    // 开始时间:  1      3      0      5      3      5
    // 结束时间:  4      5      6      7      8      9
    Interval act[6];
    act[0] = Interval(1, 4);
    act[1] = Interval(3, 5);
    act[2] = Interval(0, 6);
    act[3] = Interval(5, 7);
    act[4] = Interval(3, 8);
    act[5] = Interval(5, 9);

    cout << "输入：N = 6 个活动" << endl;
    cout << "活动列表（开始, 结束）：" << endl;
    for (int i = 0; i < 6; i++) {
        cout << "  活动" << (i + 1) << ": (" << act[i].start << ", " << act[i].end << ")" << endl;
    }
    cout << endl;

    // 调用贪心算法
    int result = activitySelection(act, 6);

    cout << "排序后（按结束时间）：" << endl;
    // 注意：数组已被 sort 修改，此处打印排序后的顺序
    for (int i = 0; i < 6; i++) {
        cout << "  (" << act[i].start << ", " << act[i].end << ")";
        if (i == 0) cout << " ← 结束最早，选中";
        cout << endl;
    }
    cout << endl;

    // 模拟选择过程
    cout << "贪心选择过程：" << endl;
    int count = 1;
    int lastEnd = act[0].end;
    cout << "  第1步：选中 (" << act[0].start << ", " << act[0].end
         << ")，lastEnd = " << lastEnd << endl;
    for (int i = 1; i < 6; i++) {
        if (act[i].start >= lastEnd) {
            count++;
            cout << "  第" << count << "步：选中 (" << act[i].start << ", "
                 << act[i].end << ")，lastEnd = " << act[i].end << endl;
            lastEnd = act[i].end;
        } else {
            cout << "  跳过：  (" << act[i].start << ", " << act[i].end
                 << ")，因为 " << act[i].start << " < " << lastEnd << "（与已选活动重叠）" << endl;
        }
    }

    cout << endl;
    cout << "结果：最多可以选择 " << result << " 个互不冲突的活动" << endl;
    cout << endl;
}

// ================================================================
// 测试函数：例题2 — 最多不重叠区间
// ================================================================

void testMaxNonOverlap() {
    cout << "╔══════════════════════════════════════════════╗" << endl;
    cout << "║     例题2：最多不重叠区间                     ║" << endl;
    cout << "╚══════════════════════════════════════════════╝" << endl;
    cout << endl;

    // 测试数据：5个区间
    // 编号: 1      2      3      4      5
    // 区间: [1,3] [2,4] [3,6] [5,7] [6,8]
    IndexedInterval iv[5];
    iv[0] = IndexedInterval(1, 3, 1);
    iv[1] = IndexedInterval(2, 4, 2);
    iv[2] = IndexedInterval(3, 6, 3);
    iv[3] = IndexedInterval(5, 7, 4);
    iv[4] = IndexedInterval(6, 8, 5);

    cout << "输入：N = 5 个区间" << endl;
    cout << "区间列表（编号, 左端点, 右端点）：" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "  区间" << iv[i].id << ": [" << iv[i].start << ", " << iv[i].end << "]" << endl;
    }
    cout << endl;

    // 调用算法
    cout << "输出结果：" << endl;
    maxNonOverlapIntervals(iv, 5);
    cout << endl;

    // 解释
    cout << "解释：" << endl;
    cout << "  排序后（按右端点）：" << endl;
    sort(iv, iv + 5, cmpByEndIndexed);
    for (int i = 0; i < 5; i++) {
        cout << "    区间" << iv[i].id << ": [" << iv[i].start << ", " << iv[i].end << "]";
        if (i == 0) cout << " ← 右端点最小";
        cout << endl;
    }
    cout << "  区间[1,3]和[3,6]在端点3处恰好相接，不算重叠" << endl;
    cout << "  区间[6,8]和[5,7]不能同时选，因为[5,7]与[3,6]选后lastR=6，" << endl;
    cout << "  可见需要选[6,8]而不是[5,7]" << endl;
    cout << endl;
}

// ================================================================
// 附加测试：边界情况
// ================================================================

void testEdgeCases() {
    cout << "╔══════════════════════════════════════════════╗" << endl;
    cout << "║     边界情况测试                              ║" << endl;
    cout << "╚══════════════════════════════════════════════╝" << endl;
    cout << endl;

    // 测试1：只有一个活动
    cout << "【测试1】只有一个活动" << endl;
    Interval t1[] = { Interval(1, 5) };
    cout << "  活动：(1, 5)" << endl;
    cout << "  结果：" << activitySelection(t1, 1) << " 个（应为 1）" << endl;
    cout << endl;

    // 测试2：所有活动完全不重叠
    cout << "【测试2】所有活动完全不重叠" << endl;
    Interval t2[] = {
        Interval(1, 2),
        Interval(3, 4),
        Interval(5, 6)
    };
    cout << "  活动：(1,2) (3,4) (5,6)" << endl;
    cout << "  结果：" << activitySelection(t2, 3) << " 个（应为 3）" << endl;
    cout << endl;

    // 测试3：所有活动完全重叠
    cout << "【测试3】所有活动完全重叠" << endl;
    Interval t3[] = {
        Interval(1, 10),
        Interval(2, 9),
        Interval(3, 8)
    };
    cout << "  活动：(1,10) (2,9) (3,8)" << endl;
    cout << "  结果：" << activitySelection(t3, 3) << " 个（应为 1）" << endl;
    cout << endl;

    // 测试4：端点恰好相接
    cout << "【测试4】端点恰好相接（不算重叠）" << endl;
    Interval t4[] = {
        Interval(1, 3),
        Interval(3, 5),
        Interval(5, 7)
    };
    cout << "  活动：(1,3) (3,5) (5,7)" << endl;
    cout << "  结果：" << activitySelection(t4, 3) << " 个（应为 3）" << endl;
    cout << endl;
}

// ================================================================
// 主函数：运行所有测试
// ================================================================

int main() {
    // 设置输出中文标题
    cout << "╔══════════════════════════════════════════════╗" << endl;
    cout << "║   C++ 算法提高 —— 第20课：区间调度问题        ║" << endl;
    cout << "║   贪心策略：按结束时间排序，选最多的不重叠区间 ║" << endl;
    cout << "╚══════════════════════════════════════════════╝" << endl;
    cout << endl;

    // 例题1：活动选择
    testActivitySelection();

    // 例题2：最多不重叠区间
    testMaxNonOverlap();

    // 边界测试
    testEdgeCases();

    // 本课小结
    cout << "╔══════════════════════════════════════════════╗" << endl;
    cout << "║                  本课小结                     ║" << endl;
    cout << "╚══════════════════════════════════════════════╝" << endl;
    cout << endl;
    cout << "1. 区间调度问题的贪心策略：按结束时间排序" << endl;
    cout << "2. 排序后依次选择开始时间 >= 上一个已选结束时间的区间" << endl;
    cout << "3. 正确性：结束最早的区间给后面留出最多的空间" << endl;
    cout << "4. 时间复杂度：O(N log N)，瓶颈在排序" << endl;
    cout << "5. 使用 struct 存储区间，sort 自定义比较函数" << endl;
    cout << "6. 端点恰好相接（start == end）不算重叠" << endl;
    cout << endl;
    cout << "══════════════════════════════════════════════" << endl;

    return 0;
}
