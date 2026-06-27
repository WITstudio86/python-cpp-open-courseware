/**
 * ============================================================
 * Lesson 14：计数排序与 sort 函数
 * C++算法提高课程
 *
 * 本文件包含：
 *   1. 计数排序（Counting Sort）完整实现
 *   2. STL sort 函数的多种使用方式
 *   3. 例题1：年龄排序（计数排序解法）
 *   4. 例题2：成绩统计（计数排序思想）
 *
 * 适用读者：具备基础C++知识的中小学生
 * ============================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>  // sort, min, max, greater
#include <cstring>    // memset（用于初始化数组）
using namespace std;

// ============================================================
// 第一部分：计数排序核心实现
// ============================================================

/**
 * 计数排序函数
 *
 * 算法原理：
 *   1. 找到数组中的最大值和最小值，确定数据范围
 *   2. 创建一个"计数桶"数组，大小覆盖整个数据范围
 *   3. 遍历原数组，每个元素放入对应桶中（计数+1）
 *   4. 按桶的顺序，将计数不为0的元素依次填回原数组
 *
 * 时间复杂度：O(n + m)，n是元素个数，m是数据范围大小
 * 空间复杂度：O(m)
 *
 * 适用条件：
 *   - 数据是整数（或可映射为整数）
 *   - 数据范围 m 不宜过大（建议不超过10^6）
 *   - 当 n 很大而 m 很小时，效率极高
 *
 * @param arr  待排序的整数数组（排序结果直接写入该数组）
 * @param n    数组的元素个数
 */
void countingSort(int arr[], int n) {
    // 边界情况：空数组或只有一个元素，无需排序
    if (n <= 1) return;

    // ---------- 第1步：找最小值和最大值 ----------
    // 确定数据的范围，这样我们才知道需要多少个"桶"
    int minVal = arr[0];
    int maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
    }

    // ---------- 第2步：创建计数桶 ----------
    // 桶的数量 = 最大值 - 最小值 + 1
    // 例如：最小5，最大8，则 range=4，下标0~3对应值5~8
    int range = maxVal - minVal + 1;
    // 使用 vector 动态分配，全部初始化为 0
    vector<int> bucket(range, 0);

    // ---------- 第3步：遍历原数组，元素"入桶" ----------
    // arr[i] 对应的桶下标 = arr[i] - minVal
    // 例如 arr[i]=7，minVal=5，则放入 bucket[2]
    for (int i = 0; i < n; i++) {
        bucket[arr[i] - minVal]++;
    }

    // ---------- 第4步：从桶中"倒出"数据，填回原数组 ----------
    int idx = 0;  // 写入原数组的当前位置
    for (int i = 0; i < range; i++) {
        // 第 i 个桶里装了 bucket[i] 个值为 (i + minVal) 的元素
        // 将它们逐个填回
        int value = i + minVal;  // 桶下标还原为实际值
        while (bucket[i] > 0) {
            arr[idx] = value;
            idx++;
            bucket[i]--;
        }
    }
    // 排序完成！数组 arr 现在是升序排列的
}

/**
 * 带打印的计数排序演示函数
 * 供教学使用，输出每个步骤的中间状态
 */
void countingSortDemo(int arr[], int n) {
    if (n <= 1) return;

    // 找范围
    int minVal = arr[0], maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
    }

    int range = maxVal - minVal + 1;
    cout << "  [步骤1] 数据范围: [" << minVal << ", " << maxVal
         << "], 需要 " << range << " 个桶" << endl;

    // 创建桶
    vector<int> bucket(range, 0);

    // 入桶
    cout << "  [步骤2] 元素入桶:" << endl;
    for (int i = 0; i < n; i++) {
        bucket[arr[i] - minVal]++;
        cout << "    读到 " << arr[i] << " → 桶[" << (arr[i] - minVal)
             << "]（值=" << arr[i] << "）计数变为 " << bucket[arr[i] - minVal] << endl;
    }

    // 打印桶状态
    cout << "  [步骤3] 桶的最终状态:" << endl;
    cout << "    桶编号: ";
    for (int i = 0; i < range; i++) cout << "[" << i << "] ";
    cout << endl;
    cout << "    对应值: ";
    for (int i = 0; i < range; i++) cout << " " << (i + minVal) << "  ";
    cout << endl;
    cout << "    计数值: ";
    for (int i = 0; i < range; i++) cout << " " << bucket[i] << "  ";
    cout << endl;

    // 出桶
    cout << "  [步骤4] 从桶中倒出排序结果: [";
    int idx = 0;
    bool first = true;
    for (int i = 0; i < range; i++) {
        int value = i + minVal;
        while (bucket[i] > 0) {
            arr[idx++] = value;
            if (!first) cout << ", ";
            cout << value;
            first = false;
            bucket[i]--;
        }
    }
    cout << "]" << endl;
}

// ============================================================
// 第二部分：STL sort 的使用示例
// ============================================================

/**
 * 自定义比较函数示例
 * 用于演示 sort 的第三个参数
 */

// 比较函数1：降序排列（从大到小）
// 规则：如果 a 应该排在 b 前面，返回 true
bool cmpDesc(int a, int b) {
    return a > b;  // a > b 时 a 应在前面 → 降序
}

// 比较函数2：按绝对值从小到大排序
bool cmpAbs(int a, int b) {
    return abs(a) < abs(b);
}

// 比较函数3：奇数在前，偶数在后；同类中按数值从小到大
bool cmpOddEven(int a, int b) {
    // 判断奇偶性：a%2!=0 表示奇数
    bool aOdd = (a % 2 != 0);
    bool bOdd = (b % 2 != 0);

    if (aOdd && !bOdd) return true;   // a 奇 b 偶 → a 在前
    if (!aOdd && bOdd) return false;  // a 偶 b 奇 → b 在前
    return a < b;                     // 同奇偶 → 数值小的在前
}

/**
 * STL sort 综合演示
 */
void demonstrateSTLSort() {
    cout << "========== STL sort 函数演示 ==========" << endl << endl;

    // --- 演示1：基本升序排序 ---
    {
        int arr[] = {42, 17, 89, 5, 73, 31, 56, 8};
        int n = sizeof(arr) / sizeof(arr[0]);

        cout << "[演示1] 基本升序排序（默认）" << endl;
        cout << "  排序前: ";
        for (int i = 0; i < n; i++) cout << arr[i] << " ";
        cout << endl;

        sort(arr, arr + n);  // 默认升序，等价于 sort(arr, arr+n, less<int>())

        cout << "  排序后: ";
        for (int i = 0; i < n; i++) cout << arr[i] << " ";
        cout << endl << endl;
    }

    // --- 演示2：降序排序 ---
    {
        int arr[] = {42, 17, 89, 5, 73, 31, 56, 8};
        int n = sizeof(arr) / sizeof(arr[0]);

        cout << "[演示2] 降序排序（greater<int>()）" << endl;
        cout << "  排序前: ";
        for (int i = 0; i < n; i++) cout << arr[i] << " ";
        cout << endl;

        sort(arr, arr + n, greater<int>());  // 使用标准库的 greater 函数对象

        cout << "  排序后: ";
        for (int i = 0; i < n; i++) cout << arr[i] << " ";
        cout << endl << endl;
    }

    // --- 演示3：自定义比较函数（降序） ---
    {
        int arr[] = {42, 17, 89, 5, 73, 31, 56, 8};
        int n = sizeof(arr) / sizeof(arr[0]);

        cout << "[演示3] 自定义比较函数降序（cmpDesc）" << endl;
        cout << "  排序前: ";
        for (int i = 0; i < n; i++) cout << arr[i] << " ";
        cout << endl;

        sort(arr, arr + n, cmpDesc);

        cout << "  排序后: ";
        for (int i = 0; i < n; i++) cout << arr[i] << " ";
        cout << endl << endl;
    }

    // --- 演示4：按绝对值排序 ---
    {
        int arr[] = {-5, 3, -9, 1, -2, 7, -4, 6};
        int n = sizeof(arr) / sizeof(arr[0]);

        cout << "[演示4] 按绝对值从小到大排序（cmpAbs）" << endl;
        cout << "  排序前: ";
        for (int i = 0; i < n; i++) cout << arr[i] << " ";
        cout << endl;

        sort(arr, arr + n, cmpAbs);

        cout << "  排序后: ";
        for (int i = 0; i < n; i++) cout << arr[i] << " ";
        cout << endl;
        cout << "  绝对值: ";
        for (int i = 0; i < n; i++) cout << abs(arr[i]) << " ";
        cout << endl << endl;
    }

    // --- 演示5：奇数在前，偶数在后 ---
    {
        int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int n = sizeof(arr) / sizeof(arr[0]);

        cout << "[演示5] 奇数在前，偶数在后（cmpOddEven）" << endl;
        cout << "  排序前: ";
        for (int i = 0; i < n; i++) cout << arr[i] << " ";
        cout << endl;

        sort(arr, arr + n, cmpOddEven);

        cout << "  排序后: ";
        for (int i = 0; i < n; i++) cout << arr[i] << " ";
        cout << endl << endl;
    }

    // --- 演示6：对 vector 排序 ---
    {
        vector<int> v = {64, 25, 12, 22, 11};

        cout << "[演示6] 对 vector 容器排序" << endl;
        cout << "  排序前: ";
        for (int x : v) cout << x << " ";
        cout << endl;

        sort(v.begin(), v.end());  // 使用 begin() 和 end() 迭代器

        cout << "  排序后: ";
        for (int x : v) cout << x << " ";
        cout << endl << endl;
    }

    // --- 演示7：部分排序（只排序前一半） ---
    {
        int arr[] = {9, 3, 7, 1, 5, 2, 8, 4, 6, 0};
        int n = sizeof(arr) / sizeof(arr[0]);

        cout << "[演示7] 只排序前5个元素" << endl;
        cout << "  排序前: ";
        for (int i = 0; i < n; i++) cout << arr[i] << " ";
        cout << endl;

        sort(arr, arr + 5);  // 只排序 arr[0] 到 arr[4]

        cout << "  排序后: ";
        for (int i = 0; i < n; i++) cout << arr[i] << " ";
        cout << " (前5个已排序，后5个不变)" << endl << endl;
    }
}

// ============================================================
// 第三部分：例题1 - 年龄排序
// ============================================================

/**
 * 例题1：年龄排序
 *
 * 题目描述：
 *   某学校进行体检，需要将学生的年龄从小到大排序输出。
 *   已知学生年龄在6-18岁之间。
 *
 * 解题思路：
 *   年龄范围很小（只有13个可能值：6~18），非常适合计数排序。
 *   我们直接用一个大小为19的数组（下标0~18），在读入时统计每个
 *   年龄的人数，然后按年龄顺序输出即可。
 *
 * 输入格式：
 *   第一行：整数 n (1 ≤ n ≤ 100000)，学生人数
 *   第二行：n 个整数，每个学生的年龄
 *
 * 输出格式：
 *   一行 n 个整数，按从小到大排序后的年龄
 */
void solveAgeSorting() {
    cout << "========== 例题1：年龄排序 ==========" << endl;
    cout << "请输入学生人数 n 和 n 个年龄（6~18）：" << endl;

    int n;
    cin >> n;

    // 年龄范围 6~18，开一个大小为 19 的数组（0~18 都用得上）
    // 其实只需要 6~18，但多开几个位置不影响正确性且更方便
    const int MAX_AGE = 18;
    int cnt[MAX_AGE + 1] = {0};

    // 读入年龄并统计
    for (int i = 0; i < n; i++) {
        int age;
        cin >> age;
        cnt[age]++;  // 年龄 age 的桶 +1
    }

    // 输出排序结果
    bool first = true;  // 用于控制空格格式
    for (int age = 6; age <= 18; age++) {
        for (int j = 0; j < cnt[age]; j++) {
            if (!first) cout << " ";
            cout << age;
            first = false;
        }
    }
    cout << endl;
}

/**
 * 例题1 带测试数据演示版（不需要手动输入）
 */
void demoAgeSorting() {
    cout << "========== 例题1演示：年龄排序 ==========" << endl;

    // 模拟输入数据
    int ages[] = {12, 15, 8, 10, 13, 8, 15, 10};
    int n = sizeof(ages) / sizeof(ages[0]);

    cout << "输入: n=" << n << endl;
    cout << "年龄: ";
    for (int i = 0; i < n; i++) cout << ages[i] << " ";
    cout << endl;

    // 计数排序
    const int MAX_AGE = 18;
    int cnt[MAX_AGE + 1] = {0};

    for (int i = 0; i < n; i++) {
        cnt[ages[i]]++;
    }

    // 打印桶状态
    cout << "计数桶状态（年龄:人数）：" << endl;
    for (int age = 6; age <= 18; age++) {
        if (cnt[age] > 0) {
            cout << "  " << age << "岁: " << cnt[age] << "人";
            // 可视化桶中的"水量"
            cout << "  [";
            for (int k = 0; k < cnt[age]; k++) cout << "█";
            cout << "]" << endl;
        }
    }

    // 输出结果
    cout << "排序结果: ";
    bool first = true;
    for (int age = 6; age <= 18; age++) {
        for (int j = 0; j < cnt[age]; j++) {
            if (!first) cout << " ";
            cout << age;
            first = false;
        }
    }
    cout << endl << endl;
}

// ============================================================
// 第四部分：例题2 - 成绩统计
// ============================================================

/**
 * 例题2：成绩统计
 *
 * 题目描述：
 *   输入 n 个学生的成绩（0~100），统计每个分数的人数，
 *   并按成绩从高到低输出有学生的成绩及对应人数。
 *
 * 解题思路：
 *   用计数排序的思想，开一个大小为101的数组统计每个分数的人数。
 *   然后从100遍历到0，只输出人数>0的分数。
 *
 * 输入格式：
 *   第一行：整数 n (1 ≤ n ≤ 100000)
 *   第二行：n 个整数，表示成绩
 *
 * 输出格式：
 *   多行，每行 "成绩: 人数"，按成绩从高到低输出
 */
void solveScoreStatistics() {
    cout << "========== 例题2：成绩统计 ==========" << endl;
    cout << "请输入学生人数 n 和 n 个成绩（0~100）：" << endl;

    int n;
    cin >> n;

    int cnt[101] = {0};  // 0~100 共101个分数

    // 读入成绩并统计
    for (int i = 0; i < n; i++) {
        int score;
        cin >> score;
        cnt[score]++;
    }

    // 从高到低输出
    for (int score = 100; score >= 0; score--) {
        if (cnt[score] > 0) {
            cout << score << ": " << cnt[score] << endl;
        }
    }
}

/**
 * 例题2 带测试数据演示版（不需要手动输入）
 */
void demoScoreStatistics() {
    cout << "========== 例题2演示：成绩统计 ==========" << endl;

    // 模拟输入数据
    int scores[] = {85, 92, 85, 78, 92};
    int n = sizeof(scores) / sizeof(scores[0]);

    cout << "输入: n=" << n << endl;
    cout << "成绩: ";
    for (int i = 0; i < n; i++) cout << scores[i] << " ";
    cout << endl;

    // 统计
    int cnt[101] = {0};
    for (int i = 0; i < n; i++) {
        cnt[scores[i]]++;
    }

    // 可视化显示
    cout << "成绩分布（从高到低）：" << endl;
    cout << "  ┌──────────┬──────┬──────────┐" << endl;
    cout << "  │   成绩   │ 人数 │   柱状图  │" << endl;
    cout << "  ├──────────┼──────┼──────────┤" << endl;
    for (int score = 100; score >= 0; score--) {
        if (cnt[score] > 0) {
            printf("  │ %6d   │ %4d │ ", score, cnt[score]);
            for (int k = 0; k < cnt[score]; k++) cout << "█";
            cout << endl;
        }
    }
    cout << "  └──────────┴──────┴──────────┘" << endl;
}

// ============================================================
// 第五部分：主函数
// ============================================================

/**
 * 打印数组的辅助函数
 */
void printArray(int arr[], int n, const string& msg = "") {
    if (!msg.empty()) cout << msg;
    cout << "[";
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << ", ";
        cout << arr[i];
    }
    cout << "]" << endl;
}

int main() {
    // 设置中文输出（部分环境需要）
    // 如果终端不支持中文，可注释掉下行或改为英文

    cout << "╔══════════════════════════════════════════════╗" << endl;
    cout << "║   第14课：计数排序与 sort 函数              ║" << endl;
    cout << "║   C++ 算法提高课程                          ║" << endl;
    cout << "╚══════════════════════════════════════════════╝" << endl;
    cout << endl;

    // ========== 计数排序演示 ==========
    cout << "========================================" << endl;
    cout << "  一、计数排序（Counting Sort）演示" << endl;
    cout << "========================================" << endl << endl;

    {
        int arr[] = {3, 1, 2, 3, 0, 2, 3, 1};
        int n = sizeof(arr) / sizeof(arr[0]);
        cout << "[测试1] 基本测试" << endl;
        cout << "  原始数组: ";
        for (int i = 0; i < n; i++) cout << arr[i] << " ";
        cout << endl;

        countingSortDemo(arr, n);

        cout << "  排序结果: ";
        for (int i = 0; i < n; i++) cout << arr[i] << " ";
        cout << endl << endl;
    }

    {
        // 测试包含更大范围的数据
        int arr2[] = {95, 87, 100, 87, 92, 95, 100, 88};
        int n2 = sizeof(arr2) / sizeof(arr2[0]);
        cout << "[测试2] 成绩数据测试" << endl;
        cout << "  原始数组: ";
        for (int i = 0; i < n2; i++) cout << arr2[i] << " ";
        cout << endl;

        countingSort(arr2, n2);

        cout << "  排序结果: ";
        for (int i = 0; i < n2; i++) cout << arr2[i] << " ";
        cout << endl << endl;
    }

    {
        // 测试包含负数的情况
        int arr3[] = {-3, 5, 0, -1, 2, -3, 4, -1};
        int n3 = sizeof(arr3) / sizeof(arr3[0]);
        cout << "[测试3] 包含负数的测试" << endl;
        cout << "  原始数组: ";
        for (int i = 0; i < n3; i++) cout << arr3[i] << " ";
        cout << endl;

        countingSort(arr3, n3);

        cout << "  排序结果: ";
        for (int i = 0; i < n3; i++) cout << arr3[i] << " ";
        cout << endl << endl;
    }

    {
        // 测试单元素
        int arr4[] = {42};
        cout << "[测试4] 单元素边界测试" << endl;
        cout << "  原始数组: [42]" << endl;
        countingSort(arr4, 1);
        cout << "  排序结果: [42]" << endl << endl;
    }

    // ========== STL sort 演示 ==========
    demonstrateSTLSort();

    // ========== 例题演示（使用预设数据，不等待用户输入） ==========
    cout << "========================================" << endl;
    cout << "  三、例题演示（预设数据）" << endl;
    cout << "========================================" << endl << endl;

    demoAgeSorting();
    demoScoreStatistics();

    // ========== 交互式选择（可选） ==========
    cout << "========================================" << endl;
    cout << "  四、交互式练习" << endl;
    cout << "========================================" << endl;
    cout << "请选择要运行的程序：" << endl;
    cout << "  1 - 例题1：年龄排序（手动输入）" << endl;
    cout << "  2 - 例题2：成绩统计（手动输入）" << endl;
    cout << "  0 - 退出" << endl;
    cout << "请输入选择：";

    int choice;
    cin >> choice;

    if (choice == 1) {
        solveAgeSorting();
    } else if (choice == 2) {
        solveScoreStatistics();
    } else {
        cout << "程序结束，再见！" << endl;
    }

    return 0;
}
