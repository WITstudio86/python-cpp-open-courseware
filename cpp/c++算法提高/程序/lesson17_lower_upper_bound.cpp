/**
 * ============================================================
 * C++ 算法提高 — 第17课：二分查找的边界处理
 * ============================================================
 *
 * 本课核心内容：
 *   1. 手写 lower_bound：查找有序数组中第一个 >= x 的位置
 *   2. 手写 upper_bound：查找有序数组中第一个 > x 的位置
 *   3. 利用 lower_bound + upper_bound 解决"数的范围"问题
 *
 * lower_bound 与 upper_bound 是二分查找中最重要的两个变体，
 * 它们的区别仅在于判断条件的不同：
 *   - lower_bound: a[mid] >= x  → 找"第一个不小于 x"的位置
 *   - upper_bound: a[mid] >  x  → 找"第一个大于 x"的位置
 *
 * 适用年级：初中 / 高中
 * 前置知识：数组、循环、基本的二分查找
 * ============================================================
 */

#include <iostream>
using namespace std;

// ================================================================
// 第一部分：核心算法实现
// ================================================================

/**
 * my_lower_bound —— 在升序数组 a[0..n-1] 中查找第一个 >= x 的位置
 *
 * @param a   升序排列的整数数组（允许重复元素）
 * @param n   数组的长度
 * @param x   要查找的目标值
 * @return    第一个满足 a[i] >= x 的下标 i
 *            如果所有元素都小于 x，则返回 n（表示不存在）
 *
 * 算法思路（手动模拟）：
 *   以数组 [1, 3, 3, 5, 7, 9, 9, 9, 11]，查询 x = 9 为例：
 *
 *   初始：left = 0, right = 8, ans = 9
 *   第1轮：mid = 4, a[4]=7 < 9  → left = 5
 *   第2轮：mid = 6, a[6]=9 >= 9 → ans = 6, right = 5
 *   第3轮：mid = 5, a[5]=9 >= 9 → ans = 5, right = 4
 *   循环结束（left=5, right=4），返回 ans = 5 ✓
 *
 * 时间复杂度：O(log n)
 * 空间复杂度：O(1)
 */
int my_lower_bound(int a[], int n, int x) {
    int left = 0;                // 搜索区间的左端点
    int right = n - 1;           // 搜索区间的右端点（闭区间）
    int ans = n;                 // 候选答案，默认为 n（表示"不存在"）

    // 当 left <= right 时，区间内还有元素需要检查
    // 注意：必须用 <= 而不是 <，否则 left == right 时唯一元素会被跳过！
    while (left <= right) {
        // 计算中点，使用 left + (right - left) / 2 防止溢出
        // 等价于 (left + right) / 2，但更安全
        int mid = left + (right - left) / 2;

        if (a[mid] >= x) {
            // a[mid] 已经满足条件，记录为候选答案
            ans = mid;
            // 但左边可能还有更小的索引也满足条件，
            // 所以继续向左搜索（缩小右边界）
            right = mid - 1;
        } else {
            // a[mid] < x，mid 以及 mid 左边的元素都不满足条件
            // 答案一定在右边，缩小左边界
            left = mid + 1;
        }
    }
    return ans;
}

/**
 * my_upper_bound —— 在升序数组 a[0..n-1] 中查找第一个 > x 的位置
 *
 * @param a   升序排列的整数数组
 * @param n   数组的长度
 * @param x   要查找的目标值
 * @return    第一个满足 a[i] > x 的下标 i
 *            如果所有元素都 ≤ x，则返回 n
 *
 * 与 lower_bound 的区别只有一处：
 *   判断条件从 a[mid] >= x 变为 a[mid] > x
 *
 * 算法模拟（同样数组 [1, 3, 3, 5, 7, 9, 9, 9, 11]，查询 x = 9）：
 *
 *   初始：left = 0, right = 8, ans = 9
 *   第1轮：mid = 4, a[4]=7 > 9? 否 → left = 5
 *   第2轮：mid = 6, a[6]=9 > 9? 否 → left = 7
 *   第3轮：mid = 7, a[7]=9 > 9? 否 → left = 8
 *   第4轮：mid = 8, a[8]=11 > 9! → ans = 8, right = 7
 *   循环结束（left=8, right=7），返回 ans = 8 ✓
 *
 * 注意：ans = 8 是元素 11 的位置，
 *   upper_bound(9) - 1 = 7 才是最后一个 9 的位置
 */
int my_upper_bound(int a[], int n, int x) {
    int left = 0;
    int right = n - 1;
    int ans = n;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (a[mid] > x) {
            // 【关键区别】：这里用的是 > 而不是 >=
            // 只有严格大于 x 的元素才被记录
            ans = mid;
            right = mid - 1;       // 继续向左找更靠前的位置
        } else {
            // a[mid] <= x，不满足"严格大于"的条件
            left = mid + 1;
        }
    }
    return ans;
}

// ================================================================
// 第二部分：问题1 —— 查找第一个 >= x 的位置
// ================================================================

/**
 * 问题描述：
 *   给定一个升序数组，有 q 次查询，每次查询输出第一个 >= x 的元素下标。
 *   如果不存在，输出 -1。
 *
 * 本函数将 my_lower_bound 的返回值做了适配：
 *   若返回 n（表示不存在），统一输出 -1
 */

/**
 * lower_bound_pos —— 查找第一个 >= x 的位置（适配版）
 *
 * @return 第一个 >= x 的下标，若不存在返回 -1
 */
int lower_bound_pos(int a[], int n, int x) {
    int pos = my_lower_bound(a, n, x);
    // my_lower_bound 返回 n 表示不存在，这里转为 -1
    if (pos == n) return -1;
    return pos;
}

/**
 * solve_problem1 —— 解决"查找第一个 >= x 的位置"问题
 *
 * 输入格式：
 *   第一行：n q
 *   第二行：n 个升序整数
 *   接下来 q 行：每行一个查询 x
 *
 * 输出格式：
 *   每行输出一个整数，第一个 >= x 的下标，不存在输出 -1
 */
void solve_problem1() {
    // ---- 测试数据（硬编码，方便直接运行验证） ----
    // 数组：[1, 3, 5, 7, 7, 9]，长度 n = 6
    // 查询：3, 7, 10, 0
    int a[] = {1, 3, 5, 7, 7, 9};
    int n = 6;
    int queries[] = {3, 7, 10, 0};
    int q = 4;

    cout << "================================================" << endl;
    cout << "  例题1：查找第一个 >= x 的位置" << endl;
    cout << "================================================" << endl;
    cout << "数组：[1, 3, 5, 7, 7, 9]" << endl;
    cout << "查询结果：" << endl;

    for (int i = 0; i < q; i++) {
        int x = queries[i];
        int pos = lower_bound_pos(a, n, x);
        cout << "  x = " << x << "  →  ";
        if (pos == -1) {
            cout << "-1（不存在 ≥ " << x << " 的元素）" << endl;
        } else {
            cout << "下标 " << pos << "（a[" << pos << "] = " << a[pos] << "）" << endl;
        }
    }
    cout << endl;

    // 预期输出：
    // x = 3  → 下标 1（a[1] = 3）
    // x = 7  → 下标 3（a[3] = 7）
    // x = 10 → -1（不存在 ≥ 10 的元素）
    // x = 0  → 下标 0（a[0] = 1）
}

// ================================================================
// 第三部分：问题2 —— 数的范围
// ================================================================

/**
 * 问题描述（"数的范围"）：
 *   给定一个升序数组，有 q 次查询。
 *   对于每次查询 x，输出 x 在数组中的起始位置和终止位置。
 *   如果 x 不存在，输出 "-1 -1"。
 *
 * 核心思路：
 *   - 起始位置 = my_lower_bound(x)   （第一个 >= x 的位置）
 *   - 终止位置 = my_upper_bound(x) - 1（最后一个 <= x 的位置）
 *   - 如果 lower_bound 返回的位置不等于 x，说明 x 不存在
 *
 * 为什么 upper_bound(x) - 1 就是最后一个 x 的位置？
 *   upper_bound(x) 返回的是第一个 > x 的位置。
 *   因此 upper_bound(x) - 1 就是"最后一个 ≤ x"的位置。
 *   如果 x 存在，这个位置上的值一定等于 x。
 *   如果 x 不存在，upper_bound(x) - 1 上的值 < x，
 *   而 lower_bound(x) 的位置上的值 > x，两者矛盾，
 *   所以通过检查 a[lower_bound(x)] == x 即可判断存在性。
 */

/**
 * find_range —— 查找 x 在数组中的范围
 *
 * @param a      升序数组
 * @param n      数组长度
 * @param x      目标值
 * @param first  输出参数：起始位置（若不存在则为 -1）
 * @param last   输出参数：终止位置（若不存在则为 -1）
 */
void find_range(int a[], int n, int x, int &first, int &last) {
    // 步骤1：利用 lower_bound 找起始位置
    first = my_lower_bound(a, n, x);

    // 步骤2：检查 x 是否真的存在
    // 条件：first 没有越界，且 a[first] 真的等于 x
    if (first >= n || a[first] != x) {
        // x 不存在
        first = -1;
        last = -1;
        return;
    }

    // 步骤3：利用 upper_bound 找终止位置
    // upper_bound(x) - 1 就是最后一个 x 的位置
    last = my_upper_bound(a, n, x) - 1;
}

/**
 * solve_problem2 —— 解决"数的范围"问题
 *
 * 输入格式：
 *   第一行：n q
 *   第二行：n 个升序整数
 *   接下来 q 行：每行一个查询 x
 *
 * 输出格式：
 *   每行两个整数，x 的起始和终止位置，不存在则输出 "-1 -1"
 */
void solve_problem2() {
    // ---- 测试数据（硬编码） ----
    // 数组：[1, 2, 2, 3, 3, 3, 5, 7]，长度 n = 8
    // 查询：3, 4, 2, 7
    int a[] = {1, 2, 2, 3, 3, 3, 5, 7};
    int n = 8;
    int queries[] = {3, 4, 2, 7};
    int q = 4;

    cout << "================================================" << endl;
    cout << "  例题2：数的范围" << endl;
    cout << "================================================" << endl;
    cout << "数组：[1, 2, 2, 3, 3, 3, 5, 7]" << endl;
    cout << endl;

    // 为了帮助理解，先打印 lower_bound 和 upper_bound 的中间结果
    cout << "【逐步演示】" << endl;
    for (int i = 0; i < q; i++) {
        int x = queries[i];
        int lb = my_lower_bound(a, n, x);
        int ub = my_upper_bound(a, n, x);
        cout << "  x = " << x << "：" << endl;
        cout << "    lower_bound(" << x << ") = " << lb;
        if (lb < n) cout << "（a[" << lb << "] = " << a[lb] << "）";
        else cout << "（超出数组范围）";
        cout << endl;
        cout << "    upper_bound(" << x << ") = " << ub;
        if (ub < n) cout << "（a[" << ub << "] = " << a[ub] << "）";
        else cout << "（超出数组范围）";
        cout << endl;
        cout << "    → 起始位置 = lower_bound = " << lb;
        cout << "，终止位置 = upper_bound - 1 = " << ub - 1;
        if (lb < n && a[lb] == x) {
            cout << " ✓";
        } else {
            cout << " ✗（" << x << " 不存在）";
        }
        cout << endl;
    }
    cout << endl;

    cout << "【最终结果】" << endl;
    for (int i = 0; i < q; i++) {
        int x = queries[i];
        int first, last;
        find_range(a, n, x, first, last);

        cout << "  x = " << x << "  →  ";
        if (first == -1) {
            cout << "-1 -1" << endl;
        } else {
            cout << first << " " << last;
            // 额外显示子数组以便理解
            cout << "（数组中的位置：";
            for (int j = first; j <= last; j++) {
                cout << a[j];
                if (j < last) cout << ", ";
            }
            cout << "）" << endl;
        }
    }

    // 预期输出：
    // x = 3 → 3 5  (元素 3 出现在索引 3, 4, 5)
    // x = 4 → -1 -1 (4 不存在)
    // x = 2 → 1 2  (元素 2 出现在索引 1, 2)
    // x = 7 → 7 7  (元素 7 只出现在索引 7)
}


// ================================================================
// 第四部分：额外测试 —— 边界情况
// ================================================================

/**
 * test_edge_cases —— 测试各种边界情况
 *
 * 包括：
 *   1. 所有元素都小于 x（lower_bound 应返回 n）
 *   2. 所有元素都大于 x（lower_bound 应返回 0）
 *   3. x 等于第一个元素
 *   4. x 等于最后一个元素
 *   5. 只有一个元素的数组
 *   6. 全部相同元素的数组
 *   7. lower_bound 和 upper_bound 在重复元素上的区别
 */
void test_edge_cases() {
    cout << "================================================" << endl;
    cout << "  边界情况测试" << endl;
    cout << "================================================" << endl;

    // 测试1：所有元素都小于 x
    {
        int a[] = {1, 2, 3, 4, 5};
        int n = 5;
        int x = 10;
        int lb = my_lower_bound(a, n, x);
        int ub = my_upper_bound(a, n, x);
        cout << "  测试1 - 所有元素 < x（x=10）：" << endl;
        cout << "    lower_bound = " << lb << "（期望 5 = n，表示不存在）" << endl;
        cout << "    upper_bound = " << ub << "（期望 5 = n）" << endl;
    }

    // 测试2：所有元素都大于 x
    {
        int a[] = {10, 20, 30, 40, 50};
        int n = 5;
        int x = 1;
        int lb = my_lower_bound(a, n, x);
        int ub = my_upper_bound(a, n, x);
        cout << "  测试2 - 所有元素 > x（x=1）：" << endl;
        cout << "    lower_bound = " << lb << "（期望 0，a[0] 就是第一个 ≥1 的）" << endl;
        cout << "    upper_bound = " << ub << "（期望 0，a[0] > 1）" << endl;
    }

    // 测试3：x 等于第一个元素
    {
        int a[] = {3, 5, 7, 9};
        int n = 4;
        int x = 3;
        int lb = my_lower_bound(a, n, x);
        int ub = my_upper_bound(a, n, x);
        cout << "  测试3 - x 等于第一个元素（x=3）：" << endl;
        cout << "    lower_bound = " << lb << "（期望 0）" << endl;
        cout << "    upper_bound = " << ub << "（期望 1，a[1]=5 > 3）" << endl;
    }

    // 测试4：x 等于最后一个元素
    {
        int a[] = {3, 5, 7, 9};
        int n = 4;
        int x = 9;
        int lb = my_lower_bound(a, n, x);
        int ub = my_upper_bound(a, n, x);
        cout << "  测试4 - x 等于最后一个元素（x=9）：" << endl;
        cout << "    lower_bound = " << lb << "（期望 3）" << endl;
        cout << "    upper_bound = " << ub << "（期望 4 = n，没有 > 9 的元素）" << endl;
    }

    // 测试5：只有一个元素的数组
    {
        int a[] = {42};
        int n = 1;
        cout << "  测试5 - 单元素数组（[42]）：" << endl;
        cout << "    lower_bound(41) = " << my_lower_bound(a, n, 41) << "（期望 0）" << endl;
        cout << "    lower_bound(42) = " << my_lower_bound(a, n, 42) << "（期望 0）" << endl;
        cout << "    lower_bound(43) = " << my_lower_bound(a, n, 43) << "（期望 1 = n）" << endl;
        cout << "    upper_bound(41) = " << my_upper_bound(a, n, 41) << "（期望 0）" << endl;
        cout << "    upper_bound(42) = " << my_upper_bound(a, n, 42) << "（期望 1 = n）" << endl;
    }

    // 测试6：全部相同元素
    {
        int a[] = {7, 7, 7, 7, 7};
        int n = 5;
        int lb = my_lower_bound(a, n, 7);
        int ub = my_upper_bound(a, n, 7);
        cout << "  测试6 - 全部相同元素（[7,7,7,7,7]）：" << endl;
        cout << "    lower_bound(7) = " << lb << "（期望 0，第一个 7 的位置）" << endl;
        cout << "    upper_bound(7) = " << ub << "（期望 5 = n，没有 > 7 的元素）" << endl;
        cout << "    → 7 的出现次数 = upper_bound - lower_bound = "
             << ub - lb << "（期望 5）" << endl;
    }

    // 测试7：重复元素场景 —— 展示 lower_bound 和 upper_bound 的关键区别
    {
        int a[] = {1, 3, 3, 3, 5, 7, 9, 9};
        int n = 8;
        int x = 3;
        int lb = my_lower_bound(a, n, x);
        int ub = my_upper_bound(a, n, x);
        cout << "  测试7 - 重复元素（[1,3,3,3,5,7,9,9]，x=3）：" << endl;
        cout << "    lower_bound(3) = " << lb << " → a[" << lb << "] = " << a[lb]
             << "（第一个 ≥3 的元素）" << endl;
        cout << "    upper_bound(3) = " << ub << " → a[" << ub << "] = " << a[ub]
             << "（第一个 >3 的元素）" << endl;
        cout << "    → 3 的出现次数 = " << ub - lb << "（期望 3）" << endl;
        cout << "    → 3 的范围 = [" << lb << ", " << ub - 1 << "]" << endl;
    }

    cout << endl;
}


// ================================================================
// 第五部分：main 函数 —— 运行所有测试
// ================================================================

int main() {
    // 加速输入输出（本程序使用硬编码测试，但保留好习惯）
    ios::sync_with_stdio(false);
    cin.tie(0);

    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║  C++ 算法提高 — 第17课：二分查找的边界处理        ║" << endl;
    cout << "║  lower_bound() 与 upper_bound() 完整实现与测试    ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;
    cout << endl;

    // 运行问题1
    solve_problem1();

    // 运行问题2
    solve_problem2();

    // 运行边界情况测试
    test_edge_cases();

    cout << "================================================" << endl;
    cout << "  所有测试完成！" << endl;
    cout << "================================================" << endl;

    return 0;
}
