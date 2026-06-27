/*
 * ================================================================
 * C++算法提高 第16课：二分答案——从查找值到查找解
 * ================================================================
 *
 * 算法知识点：
 *   - 二分答案的核心思想：将最优化问题转化为判定问题
 *   - check 判定函数的设计方法
 *   - 二分答案的两种模式：求最大值 / 求最小值
 *   - 答案范围的确定与单调性分析
 *
 * 经典例题：
 *   例题1 - 砍树问题：确定电锯最大高度，获得至少 M 米木材
 *   例题2 - 跳石头问题：移除至多 M 块石头，最大化最小间距
 *
 * 编译运行（macOS/Linux）：
 *   g++ -std=c++11 -O2 -o lesson16 lesson16_binary_answer.cpp
 *   ./lesson16
 *
 * 编译运行（Windows MinGW）：
 *   g++ -std=c++11 -O2 -o lesson16.exe lesson16_binary_answer.cpp
 *   lesson16.exe
 */

#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

// ================================================================
// 第一部分：二分答案模板函数（注释中的参考代码）
// ================================================================
// 下面是两个二分答案的标准模板，实际使用时将 check() 替换为具体判定函数。
// 本程序中砍树问题和跳石头问题各自内含完整的二分答案实现，可直接运行。

/*
 * 【模板1】二分答案 —— 求最大值（找最后一个满足 check 的位置）
 *
 * 适用场景：check(x) 在 x 较小时返回 true，在 x 较大时返回 false
 *         我们要找使得 check(x) 成立的最大 x
 *
 * check 序列示意：
 *   x:    0     1     2    ...   ans   ans+1  ...
 *   check: true  true  true  ...  true  false  ...
 *                                    ↑
 *                              我们要找这个位置
 *
 * 参考代码框架：
 *   long long left = L, right = R, ans = L;
 *   while (left <= right) {
 *       long long mid = left + (right - left) / 2;  // 防溢出
 *       if (check(mid)) {
 *           ans = mid;        // mid 可行，记录答案
 *           left = mid + 1;   // 尝试更大的值 → 向右搜索
 *       } else {
 *           right = mid - 1;  // mid 不可行 → 向左缩小范围
 *       }
 *   }
 *   // ans 就是最终答案！
 *
 * 典型应用：砍树问题（最大高度）、跳石头问题（最大最小间距）
 */

/*
 * 【模板2】二分答案 —— 求最小值（找第一个满足 check 的位置）
 *
 * 适用场景：check(x) 在 x 较小时返回 false，在 x 较大时返回 true
 *         我们要找使得 check(x) 成立的最小 x
 *
 * check 序列示意：
 *   x:    0     1     2    ...   ans-1  ans   ans+1  ...
 *   check: false false false ...  false  true  true   ...
 *                                         ↑
 *                                   我们要找这个位置
 *
 * 参考代码框架：
 *   long long left = L, right = R, ans = R;
 *   while (left <= right) {
 *       long long mid = left + (right - left) / 2;
 *       if (check(mid)) {
 *           ans = mid;        // mid 可行，记录答案
 *           right = mid - 1;  // 尝试更小的值 → 向左搜索
 *       } else {
 *           left = mid + 1;   // mid 不可行 → 向右缩小范围
 *       }
 *   }
 *   // ans 就是最终答案！
 *
 * 典型应用：最小化最大距离、分配任务使最大工作量最小
 */

// ================================================================
// 第二部分：例题1 —— 砍树问题
// ================================================================

/*
 * 砍树问题
 *
 * 题目描述：
 *   有 n 棵树，每棵树高度为 h[i] 米。伐木工需要获得至少 M 米长的木材。
 *   将电锯设置在高度 H 处，所有高度大于 H 的树会被砍掉高于 H 的部分。
 *   请确定电锯的最大高度 H，使得获得的木材总长度至少为 M 米。
 *
 * 输入格式：
 *   第一行：n M        （n <= 1000000, M <= 2*10^9）
 *   第二行：h[1]...h[n]（每棵树的高度，<= 10^9）
 *
 * 输出格式：
 *   一个整数，表示电锯的最大设置高度
 *
 * 样例输入：          样例输出：
 *   4 7                 15
 *   20 15 10 17
 *
 * 样例解释：
 *   电锯设在 15 米：
 *     第1棵: 20-15=5, 第2棵: 15-15=0, 第3棵: 10<15不砍, 第4棵: 17-15=2
 *     总木材 = 5+0+0+2 = 7 米 ✓
 *   电锯设在 16 米：
 *     总木材 = 4+0+0+1 = 5 米 ✗（不够）
 *   因此最大高度为 15。
 *
 * 算法分析：
 *   1. 答案范围：H ∈ [0, max(树高)]
 *   2. 单调性：H 越小，砍到的木材越多；H 越大，砍到的木材越少
 *      → check(H): H 越小越容易满足 → 前半段 true，后半段 false
 *   3. 策略：求最大值模式，找最后一个满足 check 的 H
 *   4. check(H)：遍历所有树，累加 max(0, h[i]-H)，判断总和是否 ≥ M
 *   5. 时间复杂度：O(n log maxH)，空间复杂度：O(n)
 */

const int MAXN_TREE = 1000005;  // 树的最大数量
long long treeH[MAXN_TREE];     // 存储每棵树的高度
int nTrees;                     // 树的数量
long long needWood;             // 需要的木材总长度 M

// 砍树问题的 check 函数
// 判断：将电锯设在高度 H 处，能否获得至少 needWood 米木材？
// 参数 H：电锯的设置高度
// 返回：true 表示可行（满足木材需求），false 表示不可行
bool checkTree(long long H) {
    long long total = 0;  // 累加得到的木材总长度

    for (int i = 0; i < nTrees; i++) {
        if (treeH[i] > H) {
            // 只砍高于电锯高度的部分
            total += treeH[i] - H;
        }
        // 优化：如果已经满足需求，提前返回 true
        // 这对于大数据量（n 可能达到 1000000）非常有帮助
        if (total >= needWood) return true;
    }

    // 遍历完所有树后，检查总木材是否达到需求
    return total >= needWood;
}

// 砍树问题的求解函数
void solveTree() {
    cout << "══════════════════════════════════════════" << endl;
    cout << "  例题1：砍树问题" << endl;
    cout << "══════════════════════════════════════════" << endl;

    // ---- 输入数据 ----
    cout << "输入树的数量 n 和需要的木材量 M：" << endl;
    cin >> nTrees >> needWood;

    long long maxHeight = 0;  // 记录最高树的高度，作为二分上界
    cout << "输入每棵树的高度：" << endl;
    for (int i = 0; i < nTrees; i++) {
        cin >> treeH[i];
        if (treeH[i] > maxHeight) {
            maxHeight = treeH[i];  // 更新最大高度
        }
    }

    // ---- 二分答案：求最大可行高度 ----
    // 答案范围：[0, maxHeight]
    // 使用求最大值模式
    long long left = 0, right = maxHeight, ans = 0;

    while (left <= right) {
        long long mid = left + (right - left) / 2;  // 防溢出

        if (checkTree(mid)) {
            // 高度 mid 可行（能获得足够木材）
            ans = mid;        // 记录当前可行解
            left = mid + 1;   // 尝试更高的设置（追求更大的 H）
        } else {
            // 高度 mid 不可行（木材不够）
            right = mid - 1;  // 降低高度（H 太大会导致木材不足）
        }
    }

    // ---- 输出结果 ----
    cout << "电锯的最大设置高度为：" << ans << " 米" << endl;
    cout << endl;

    // ---- 验证结果 ----
    long long verify = 0;
    for (int i = 0; i < nTrees; i++) {
        if (treeH[i] > ans) verify += treeH[i] - ans;
    }
    cout << "验证：在高度 " << ans << " 米处可获木材 " << verify << " 米";
    if (verify >= needWood) {
        cout << " ≥ " << needWood << " 米 ✓" << endl;
    } else {
        cout << " < " << needWood << " 米 ✗" << endl;
    }
    cout << endl;
}

// 砍树问题的测试用例（不需要手动输入）
void testTree() {
    cout << "--- 砍树问题测试 ---" << endl;

    // 样例测试数据
    nTrees = 4;
    needWood = 7;
    long long testData[] = {20, 15, 10, 17};
    long long maxH = 0;

    for (int i = 0; i < nTrees; i++) {
        treeH[i] = testData[i];
        if (treeH[i] > maxH) maxH = treeH[i];
    }

    cout << "树的高度: ";
    for (int i = 0; i < nTrees; i++) cout << treeH[i] << " ";
    cout << "| 需要木材: " << needWood << " 米" << endl;

    // 演示二分过程
    long long left = 0, right = maxH, ans = 0;
    int step = 0;
    cout << "\n二分查找过程：" << endl;
    cout << "初始范围: [" << left << ", " << right << "]" << endl;

    while (left <= right) {
        step++;
        long long mid = left + (right - left) / 2;
        long long wood = 0;
        for (int i = 0; i < nTrees; i++) {
            if (treeH[i] > mid) wood += treeH[i] - mid;
        }

        cout << "第" << step << "步: mid=" << mid
             << " → 获得木材=" << wood;

        if (wood >= needWood) {
            ans = mid;
            left = mid + 1;
            cout << " ≥ " << needWood << " ✓ (可行，尝试更大)";
        } else {
            right = mid - 1;
            cout << " < " << needWood << " ✗ (不可行，减小高度)";
        }
        cout << " → 新范围: [" << left << ", " << right << "]" << endl;
    }

    cout << "\n最终答案: " << ans << " 米" << endl;
    cout << "预期答案: 15 米" << endl;
    cout << "测试" << (ans == 15 ? "通过 ✓" : "失败 ✗") << endl;
    cout << endl;
}

// ================================================================
// 第三部分：例题2 —— 跳石头问题
// ================================================================

/*
 * 跳石头问题
 *
 * 题目描述：
 *   一条直线上有 n 块石头（不含起点和终点），起点到终点的距离为 L。
 *   需要移除至多 M 块石头，使得相邻石头之间的最小距离尽可能大。
 *   求这个最小距离的最大值。
 *
 * 输入格式：
 *   第一行：L n M    （L ≤ 10^9, n ≤ 50000, M ≤ n）
 *   第二行：n 个整数，每块石头到起点的距离（递增给出）
 *
 * 输出格式：
 *   一个整数，表示最小距离的最大值
 *
 * 样例输入：                    样例输出：
 *   25 5 2                        4
 *   2 11 14 17 21
 *
 * 样例解释：
 *   起点=0, 终点=25, 石头位置=[2,11,14,17,21]
 *   移除位置2和14的石头（共2块 ≤ M=2）后：
 *     剩余石头: [11, 17, 21]
 *     间距: 11, 6, 4, 4
 *     最小距离 = 4
 *   若尝试最小距离≥5，则无论怎么移除都无法做到 → 答案为 4
 *
 * 算法分析：
 *   1. 答案范围：d ∈ [1, L]
 *   2. 单调性：d 越小，需要移除的石头越少，越容易满足
 *      → check(d): d 越小越容易满足 → 前半段 true，后半段 false
 *   3. 策略：求最大值模式，找最后一个满足 check 的 d
 *   4. check(d)：贪心策略——
 *      遍历石头，维护上一块保留石头的位置 prev
 *      如果当前石头与 prev 的距离 < d，则移除当前石头（计数+1）
 *      如果移除数量 > M，则不可行
 *      最后检查终点与最后一块保留石头的距离是否 ≥ d
 *   5. 时间复杂度：O(n log L)，空间复杂度：O(n)
 */

const int MAXN_ROCK = 50005;  // 石头的最大数量
int totalLen;                 // 起点到终点的总距离 L
int numRocks;                 // 石头的数量 n
int maxRemove;                // 最多可移除的石头数 M
int rockPos[MAXN_ROCK];       // rockPos[i] 表示第 i 块石头到起点的距离

// 跳石头问题的 check 函数
// 判断：是否可以通过移除至多 maxRemove 块石头，
//       使得任意相邻保留石头（含起点和终点）之间的距离 ≥ d
// 参数 d：要求的最小距离
// 返回：true 表示可行，false 表示不可行
bool checkRock(int d) {
    int removed = 0;  // 已经移除的石头数量
    int prev = 0;     // 上一块保留石头的位置，初始为起点 0

    // 遍历所有石头
    for (int i = 1; i <= numRocks; i++) {
        if (rockPos[i] - prev < d) {
            // 当前石头距离上一块保留石头太近，必须移除
            removed++;
            // 如果移除数量已经超过限制，直接返回不可行
            if (removed > maxRemove) return false;
        } else {
            // 距离足够，保留这块石头，更新 prev
            prev = rockPos[i];
        }
    }

    // 最后检查：终点到最后一 块保留石头的距离是否 ≥ d
    if (totalLen - prev < d) {
        removed++;  // 需要移除最后一块石头（但实际上无法移除起点和终点）
    }

    return removed <= maxRemove;
}

// 跳石头问题的求解函数
void solveRock() {
    cout << "══════════════════════════════════════════" << endl;
    cout << "  例题2：跳石头问题" << endl;
    cout << "══════════════════════════════════════════" << endl;

    // ---- 输入数据 ----
    cout << "输入总长度 L、石头数 n、最多移除数 M：" << endl;
    cin >> totalLen >> numRocks >> maxRemove;

    cout << "输入每块石头到起点的距离（递增）：" << endl;
    for (int i = 1; i <= numRocks; i++) {
        cin >> rockPos[i];
    }

    // ---- 二分答案：求最大最小距离 ----
    // 答案范围：[1, totalLen]
    // 使用求最大值模式
    int left = 1, right = totalLen, ans = 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (checkRock(mid)) {
            // 距离 mid 可行（移除石头数 ≤ M）
            ans = mid;        // 记录当前可行解
            left = mid + 1;   // 尝试更大的最小距离
        } else {
            // 距离 mid 不可行（需要移除太多石头）
            right = mid - 1;  // 减小要求的距离
        }
    }

    // ---- 输出结果 ----
    cout << "最小距离的最大值为：" << ans << endl;
    cout << endl;
}

// 跳石头问题的测试用例（不需要手动输入）
void testRock() {
    cout << "--- 跳石头问题测试 ---" << endl;

    // 样例测试数据
    totalLen = 25;
    numRocks = 5;
    maxRemove = 2;
    int testData[] = {0, 2, 11, 14, 17, 21};  // testData[0] 占位不用
    for (int i = 1; i <= numRocks; i++) {
        rockPos[i] = testData[i];
    }

    cout << "总长度 L=" << totalLen << ", 石头数 n=" << numRocks
         << ", 最多移除 M=" << maxRemove << endl;
    cout << "石头位置: ";
    for (int i = 1; i <= numRocks; i++) cout << rockPos[i] << " ";
    cout << endl;

    // 演示二分过程
    int left = 1, right = totalLen, ans = 1;
    int step = 0;
    cout << "\n二分查找过程：" << endl;
    cout << "初始范围: [" << left << ", " << right << "]" << endl;

    while (left <= right) {
        step++;
        int mid = left + (right - left) / 2;

        // 模拟 check 过程
        int removed = 0, prev = 0;
        for (int i = 1; i <= numRocks; i++) {
            if (rockPos[i] - prev < mid) {
                removed++;
            } else {
                prev = rockPos[i];
            }
        }

        cout << "第" << step << "步: mid=" << mid
             << " → 需移除石头数=" << removed;

        if (removed <= maxRemove) {
            ans = mid;
            left = mid + 1;
            cout << " ≤ " << maxRemove << " ✓ (可行，尝试更大)";
        } else {
            right = mid - 1;
            cout << " > " << maxRemove << " ✗ (不可行，减小距离)";
        }
        cout << " → 新范围: [" << left << ", " << right << "]" << endl;
    }

    cout << "\n最终答案: " << ans << endl;
    cout << "预期答案: 4" << endl;
    cout << "测试" << (ans == 4 ? "通过 ✓" : "失败 ✗") << endl;
    cout << endl;
}

// ================================================================
// 第四部分：算法可视化演示
// ================================================================

/*
 * 演示二分答案的搜索过程
 * 用 ASCII 图示展示 check 序列和搜索路径
 */
void demoBinaryAnswer() {
    cout << "══════════════════════════════════════════" << endl;
    cout << "  演示：二分答案的搜索过程可视化" << endl;
    cout << "══════════════════════════════════════════" << endl;

    // 模拟：答案范围 0~20，可行解为 0~12（即 check(0..12)=true, check(13..20)=false）
    // 我们要找最大值 12
    int L = 0, R = 20;
    int actualAns = 12;  // 实际正确答案

    cout << "假设答案范围 [0, 20]，可行解为 0~" << actualAns << endl;
    cout << "check 函数: H ≤ " << actualAns << " 时 true，H > " << actualAns << " 时 false" << endl;
    cout << endl;

    // 显示 check 序列
    cout << "check 序列: ";
    for (int i = 0; i <= 20; i++) {
        if (i == actualAns + 1) cout << "  |  ";  // 分界点标记
        cout << (i <= actualAns ? "✓" : "✗");
        if (i < 20 && i != actualAns) cout << " ";
    }
    cout << endl;
    cout << "            ↑ 分界点 (最优解 = " << actualAns << ")" << endl;
    cout << endl;

    // 演示二分查找过程
    cout << "二分查找过程：" << endl;
    cout << "┌──────┬──────┬───────┬───────┬──────────┬──────────────┐" << endl;
    cout << "│ 步骤 │ left │ right │  mid  │ check?   │ 下一步操作    │" << endl;
    cout << "├──────┼──────┼───────┼───────┼──────────┼──────────────┤" << endl;

    int left = L, right = R, ans = L;
    int step = 0;

    while (left <= right && step < 15) {
        step++;
        int mid = left + (right - left) / 2;
        bool ok = (mid <= actualAns);

        cout << "│  " << step;
        cout << "   │ " << left;
        cout << (left < 10 ? "   " : "  ") << "│ " << right;
        cout << (right < 10 ? "    " : "   ") << "│ " << mid;
        cout << (mid < 10 ? "   " : "  ") << "│ ";
        cout << (ok ? "可行(✓)   " : "不可行(✗) ");
        cout << "│ ";

        if (ok) {
            ans = mid;
            left = mid + 1;
            cout << "left=mid+1(向右)";
        } else {
            right = mid - 1;
            cout << "right=mid-1(向左)";
        }
        cout << " │" << endl;
    }

    cout << "└──────┴──────┴───────┴───────┴──────────┴──────────────┘" << endl;
    cout << endl;
    cout << "最终找到的答案: " << ans << " (预期: " << actualAns << ")" << endl;
    cout << "二分查找共用了 " << step << " 步，而线性枚举需要 " << (R - L + 1) << " 步！" << endl;
    cout << endl;
}

// ================================================================
// 第五部分：主函数
// ================================================================

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   C++ 算法提高 —— 第16课：二分答案               ║" << endl;
    cout << "║   从查找值到查找解 —— 将最优化转化为判定          ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;
    cout << endl;

    // ---- 1. 演示二分答案的搜索过程 ----
    demoBinaryAnswer();

    // ---- 2. 砍树问题 ----
    testTree();

    // ---- 3. 跳石头问题 ----
    testRock();

    // ---- 本课小结 ----
    cout << "══════════════════════════════════════════" << endl;
    cout << "  本课小结" << endl;
    cout << "══════════════════════════════════════════" << endl;
    cout << "1. 二分答案 = 判定问题 + 二分查找" << endl;
    cout << "2. 前提条件：答案空间具有单调性" << endl;
    cout << "3. 两种模式：" << endl;
    cout << "   - 求最大值：满足时 left=mid+1（向右）" << endl;
    cout << "   - 求最小值：满足时 right=mid-1（向左）" << endl;
    cout << "4. check 函数是二分答案的灵魂" << endl;
    cout << "5. 时间效率：O(log R) 次判定，远优于线性枚举" << endl;
    cout << "6. 经典问题：砍树（最大化）、跳石头（最大化最小）" << endl;
    cout << "══════════════════════════════════════════" << endl;

    return 0;
}
