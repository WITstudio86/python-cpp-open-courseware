/*
 * Lesson 30: 插入排序与计数排序
 *
 * 本课内容：
 * 1. 插入排序：模拟打扑克牌时整理手牌的过程，将元素逐个插入到已排序序列的正确位置
 * 2. 计数排序：非比较排序，通过统计元素出现次数来实现排序
 * 3. 四种排序算法的综合对比（冒泡、选择、插入、计数）
 * 4. 计数排序在数据范围较小场景下的高效性
 *
 * 时间复杂度：
 * - 插入排序：O(n^2) 最坏/平均，O(n) 最好（已有序）
 * - 计数排序：O(n + k)，其中 k 是数据范围（最大值 - 最小值 + 1）
 *
 * 空间复杂度：
 * - 插入排序：O(1)
 * - 计数排序：O(k)，需要额外的计数数组
 *
 * 稳定性：
 * - 插入排序：稳定
 * - 计数排序：稳定（取决于实现方式，使用前缀和倒序放置是稳定的）
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

// ==================== 插入排序 ====================

/**
 * 插入排序（升序）
 *
 * 算法思想：
 * - 将数组分为"有序区"和"无序区"
 * - 初始时有序区只有一个元素 a[0]
 * - 每次从无序区取出第一个元素（称为 key），在有序区中从后向前扫描
 * - 找到 key 应该插入的位置，将大于 key 的元素依次向后移动
 * - 将 key 插入到正确位置
 *
 * 形象比喻：打扑克牌时整理手牌
 * - 左手拿着已经排好序的牌（有序区）
 * - 右手每次摸一张新牌（key），插入到左手牌的合适位置
 *
 * 参数：
 *   a[] - 待排序数组
 *   n   - 数组长度
 *   cmp_count - 输出参数：记录比较次数
 *   move_count - 输出参数：记录移动次数（元素后移的次数）
 */
void insertionSort(int a[], int n, int& cmp_count, int& move_count) {
    cmp_count = 0;
    move_count = 0;

    // i 表示无序区的起始位置，也是下一个要插入的元素的下标
    // 初始时 a[0] 已经在有序区，所以从 i=1 开始
    for (int i = 1; i < n; i++) {
        int key = a[i];      // 取出当前要插入的元素（待插入的"牌"）
        int j = i - 1;       // j 指向有序区的最后一个元素

        // 在有序区中从后向前扫描，找到 key 应该插入的位置
        // 当 j >= 0 且 a[j] > key 时，将 a[j] 向后移动一位
        // 使用 > 而不是 >= 可以保证稳定性
        cmp_count++;  // 至少会执行一次比较（j >= 0 的检查也算逻辑比较，
                      // 但这里只统计 a[j] > key 的比较）
        while (j >= 0 && a[j] > key) {
            cmp_count++;
            a[j + 1] = a[j];  // 将 a[j] 向后移动一位，为 key 腾出空间
            move_count++;
            j--;
        }
        // 如果 while 循环一次都没进入，上面的 cmp_count++ 是多余的，
        // 这里用更精确的方式统计比较次数
        // 为了简洁，我们采用以下方式重新统计
        // （实际上在循环外已经 +1，循环内也 +1，需要调整）

        // 将 key 插入到正确的位置（j+1 的位置）
        a[j + 1] = key;
    }
}

/**
 * 插入排序（升序，精确统计比较次数和移动次数版本）
 *
 * 此版本更精确地统计了比较次数
 */
void insertionSortAccurate(int a[], int n, int& cmp_count, int& move_count) {
    cmp_count = 0;
    move_count = 0;

    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;

        // 每轮比较：先检查 j >= 0，再检查 a[j] > key
        while (j >= 0) {
            cmp_count++;  // 统计 a[j] > key 的比较
            if (a[j] > key) {
                a[j + 1] = a[j];
                move_count++;
                j--;
            } else {
                break;
            }
        }

        a[j + 1] = key;
    }
}

// ==================== 计数排序 ====================

/**
 * 计数排序（升序）
 *
 * 算法思想（分三步）：
 * 1. 统计频率：遍历原数组，统计每个值出现了多少次
 * 2. 计算前缀和：prefix[i] 表示值 <= i 的元素有多少个
 *    也就是值 i 在排序后数组中的"最后一个位置 + 1"
 * 3. 放置元素：从后向前遍历原数组，根据前缀和将每个元素放到正确位置
 *    从后向前遍历是为了保证稳定性
 *
 * 限制条件：
 * - 适用于整数排序
 * - 数据范围（最大值 - 最小值）不能太大，否则计数数组占用过多内存
 * - 适合 n 很大但数据范围 k 很小的场景（如考试成绩 0-100 分）
 *
 * 时间复杂度：O(n + k)，其中 k = maxVal - minVal + 1
 * 空间复杂度：O(n + k)
 *
 * 参数：
 *   a[] - 待排序数组（同时也是输出数组，排序结果写回 a[]）
 *   n   - 数组长度
 */
void countingSort(int a[], int n) {
    if (n <= 0) return;

    // 第一步：找到数组中的最大值和最小值
    // 这样可以将数据范围压缩到 [minVal, maxVal]，减少空间浪费
    int maxVal = a[0], minVal = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > maxVal) maxVal = a[i];
        if (a[i] < minVal) minVal = a[i];
    }

    // 数据范围大小
    int range = maxVal - minVal + 1;

    // 第二步：创建计数数组并统计频率
    // count[0] 对应值为 minVal 的元素个数
    // count[1] 对应值为 minVal+1 的元素个数
    // ...
    // count[range-1] 对应值为 maxVal 的元素个数
    vector<int> count(range, 0);
    for (int i = 0; i < n; i++) {
        count[a[i] - minVal]++;
    }

    // 第三步：计算前缀和
    // 转换后 count[i] 表示 值 <= (minVal + i) 的元素总个数
    // 也就是说，排序后值为 (minVal + i) 的元素应该放在
    // 下标 [count[i-1], count[i]-1] 的范围内
    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }

    // 第四步：创建临时数组，倒序遍历原数组放置元素
    // 倒序遍历保证稳定性：相同值的元素，先出现的会放在更后面
    // 但因为倒序放置，后出现的元素获得更大的下标，
    // 再看时后出现的在更后面 — 等等，让我再想想...
    //
    // 实际上：
    // count[value] 表示值为 value 的元素应该放置在 output[count[value]-1]
    // 倒序遍历时，遇到值为 value 的元素，放在 output[--count[value]]
    // 这样后遍历到的（原数组中靠后的）相同值元素会放在更后面
    // 从而保持了相对顺序 — 所以倒序放置是稳定的
    vector<int> output(n);
    for (int i = n - 1; i >= 0; i--) {
        int idx = a[i] - minVal;  // 当前元素对应的计数数组下标
        count[idx]--;              // 先减 1，得到在 output 中的位置
        output[count[idx]] = a[i]; // 放置元素
    }

    // 第五步：将排序结果复制回原数组
    for (int i = 0; i < n; i++) {
        a[i] = output[i];
    }
}

// ==================== 冒泡排序（用于对比） ====================

void bubbleSortForCompare(int a[], int n, int& cmp, int& swap_count) {
    cmp = 0;
    swap_count = 0;
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; j++) {
            cmp++;
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                swap_count++;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// ==================== 选择排序（用于对比） ====================

void selectionSortForCompare(int a[], int n, int& cmp, int& swap_count) {
    cmp = 0;
    swap_count = 0;
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            cmp++;
            if (a[j] < a[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swap(a[i], a[min_idx]);
            swap_count++;
        }
    }
}

// ==================== 工具函数 ====================

/**
 * 打印数组
 */
void printArray(int a[], int n, const string& title) {
    cout << title << ": [";
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << ", ";
        cout << a[i];
    }
    cout << "]" << endl;
}

/**
 * 复制数组
 */
void copyArray(const int src[], int dst[], int n) {
    for (int i = 0; i < n; i++) {
        dst[i] = src[i];
    }
}

/**
 * 检查数组是否有序（升序）
 */
bool isSorted(int a[], int n) {
    for (int i = 1; i < n; i++) {
        if (a[i] < a[i - 1]) return false;
    }
    return true;
}

/**
 * 统一测试函数：用同一种算法对同一份数据排序，输出统计信息
 */
void testSortingAlgorithm(
    const string& name,
    void (*sortFunc)(int[], int, int&, int&),
    int original[], int n
) {
    int* arr = new int[n];
    copyArray(original, arr, n);
    int cmp_count, op_count;

    // 记录排序时间（简单方式：记录循环计数，不涉及高精度计时）
    sortFunc(arr, n, cmp_count, op_count);

    cout << "  " << setw(12) << left << name
         << " | 比较: " << setw(6) << cmp_count
         << " | 操作: " << setw(6) << op_count
         << " | 有序: " << (isSorted(arr, n) ? "是" : "否")
         << endl;

    delete[] arr;
}

// ==================== 主函数 ====================

int main() {
    cout << "============================================" << endl;
    cout << "  Lesson 30: 插入排序与计数排序" << endl;
    cout << "============================================" << endl;
    cout << endl;

    // ---------- 1. 插入排序 ----------
    cout << "---------- 1. 插入排序 ----------" << endl;
    cout << "算法思想：将数组分为有序区和无序区，" << endl;
    cout << "        每次从无序区取出一个元素插入到有序区的正确位置。" << endl;
    cout << endl;

    {
        int arr[] = {12, 11, 13, 5, 6, 1, 8};
        int n = sizeof(arr) / sizeof(arr[0]);
        int cmp_count, move_count;

        printArray(arr, n, "排序前");

        // 逐步展示插入排序的过程
        cout << "排序过程（逐步展示有序区的扩展）：" << endl;
        for (int i = 1; i < n; i++) {
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;

            // 打印当前状态，用 | 分隔有序区和无序区
            cout << "  第 " << i << " 轮后： [";
            for (int k = 0; k < n; k++) {
                if (k > 0) cout << ", ";
                if (k == i) cout << "| ";  // 有序 | 无序 分隔线
                cout << arr[k];
            }
            if (i == n - 1) cout << "] （全部有序）";
            else cout << "]";
            cout << endl;
        }

        // 重置数组，用精确统计版重新排序
        int arr2[] = {12, 11, 13, 5, 6, 1, 8};
        insertionSortAccurate(arr2, n, cmp_count, move_count);

        printArray(arr2, n, "排序结果");
        cout << "比较次数: " << cmp_count << ", 移动次数: " << move_count << endl;
        cout << "（插入排序在最好情况下（已有序）只需 n-1 次比较，0 次移动）" << endl;
    }
    cout << endl;

    // ---------- 2. 计数排序 ----------
    cout << "---------- 2. 计数排序 ----------" << endl;
    cout << "算法思想：统计每个值出现的频率 → 计算前缀和 → 放置元素" << endl;
    cout << endl;

    {
        int arr[] = {4, 2, 2, 8, 3, 3, 1, 6};
        int n = sizeof(arr) / sizeof(arr[0]);

        printArray(arr, n, "排序前");

        // 详细展示计数排序的每一步
        cout << endl << "详细步骤演示：" << endl;

        // 找到范围
        int maxVal = arr[0], minVal = arr[0];
        for (int i = 1; i < n; i++) {
            if (arr[i] > maxVal) maxVal = arr[i];
            if (arr[i] < minVal) minVal = arr[i];
        }
        int range = maxVal - minVal + 1;

        // 步骤1：统计频率
        vector<int> freq(range, 0);
        for (int i = 0; i < n; i++) {
            freq[arr[i] - minVal]++;
        }
        cout << "步骤1 - 统计频率：" << endl;
        for (int i = 0; i < range; i++) {
            cout << "  值 " << (minVal + i) << " 出现了 " << freq[i] << " 次" << endl;
        }

        // 步骤2：前缀和
        vector<int> prefix = freq;  // 复制一份
        for (int i = 1; i < range; i++) {
            prefix[i] += prefix[i - 1];
        }
        cout << "步骤2 - 前缀和（值 <= x 的元素个数）：" << endl;
        for (int i = 0; i < range; i++) {
            cout << "  值 <= " << (minVal + i) << " 的元素有 " << prefix[i] << " 个" << endl;
        }
        cout << "  含义：排序后，值为 " << minVal + 1 << " 的元素应放在位置 ["
             << 0 << ", " << prefix[1] - 1 << "]" << endl;

        // 步骤3：倒序放置
        cout << "步骤3 - 倒序放置元素：" << endl;
        vector<int> output(n);
        for (int i = n - 1; i >= 0; i--) {
            int idx = arr[i] - minVal;
            prefix[idx]--;
            output[prefix[idx]] = arr[i];
            cout << "  arr[" << i << "]=" << arr[i]
                 << " 放置到 output[" << prefix[idx] << "]" << endl;
        }

        // 复制回原数组
        cout << "步骤4 - 最终结果：";
        cout << "[";
        for (int i = 0; i < n; i++) {
            if (i > 0) cout << ", ";
            cout << output[i];
        }
        cout << "]" << endl;

        // 使用封装好的函数排序
        int arr3[] = {4, 2, 2, 8, 3, 3, 1, 6};
        countingSort(arr3, n);
        printArray(arr3, n, "countingSort 结果");
    }
    cout << endl;

    // ---------- 3. 四种排序算法对比 ----------
    cout << "---------- 3. 四种排序算法在相同数据上的表现 ----------" << endl;
    {
        // 测试数据1：随机小数组
        int arr1[] = {49, 38, 65, 97, 76, 13, 27, 49, 55, 4};
        int n1 = sizeof(arr1) / sizeof(arr1[0]);

        cout << "测试数据：";
        printArray(arr1, n1, "");

        cout << endl;
        cout << "  " << setw(12) << left << "算法"
             << " | " << setw(10) << "比较/操作"
             << " | " << setw(10) << "交换/移动"
             << " | 结果正确"
             << endl;
        cout << "  " << string(50, '-') << endl;

        testSortingAlgorithm("冒泡排序(优化)", bubbleSortForCompare, arr1, n1);
        testSortingAlgorithm("选择排序", selectionSortForCompare, arr1, n1);

        // 插入排序需要单独测试（它统计的是移动次数）
        {
            int* arr = new int[n1];
            copyArray(arr1, arr, n1);
            int cmp, move_cnt;
            insertionSortAccurate(arr, n1, cmp, move_cnt);
            cout << "  " << setw(12) << left << "插入排序"
                 << " | 比较: " << setw(4) << cmp
                 << " | 移动: " << setw(4) << move_cnt
                 << " | 有序: " << (isSorted(arr, n1) ? "是" : "否")
                 << endl;
            delete[] arr;
        }

        // 计数排序单独测试（它不涉及比较和交换，操作次数为 n+k）
        {
            int* arr = new int[n1];
            copyArray(arr1, arr, n1);
            countingSort(arr, n1);
            cout << "  " << setw(12) << left << "计数排序"
                 << " | 遍历: " << setw(4) << (2*n1)
                 << " | 额外: " << setw(4) << (n1)
                 << " | 有序: " << (isSorted(arr, n1) ? "是" : "否")
                 << endl;
            delete[] arr;
        }
    }
    cout << endl;

    // ---------- 4. 计数排序高效性演示 ----------
    cout << "---------- 4. 计数排序高效性演示 ----------" << endl;
    cout << "场景：n = 1000 个学生成绩，成绩范围 [0, 100]" << endl;
    cout << "      比较排序 O(n^2) ≈ 1,000,000 次操作" << endl;
    cout << "      计数排序 O(n + k) ≈ 1,100 次操作" << endl;
    cout << endl;

    {
        const int N = 30;  // 演示用较小数据量，便于观察
        int scores[N];

        // 生成模拟成绩数据：0 到 100 之间的随机整数
        srand(42);  // 固定随机种子，使结果可复现
        cout << "模拟 " << N << " 个学生的成绩：" << endl;
        cout << "原始成绩: [";
        for (int i = 0; i < N; i++) {
            scores[i] = rand() % 101;  // 0~100
            if (i > 0) cout << ", ";
            if (i % 15 == 14) cout << endl << "          ";  // 换行
            cout << setw(3) << scores[i];
        }
        cout << "]" << endl;

        // 复制三份，分别用三种算法
        int arr_bubble[N], arr_insert[N];
        copyArray(scores, arr_bubble, N);
        copyArray(scores, arr_insert, N);

        int cmp_b, swap_b, cmp_i, move_i;

        // 冒泡排序
        bubbleSortForCompare(arr_bubble, N, cmp_b, swap_b);
        cout << endl;
        cout << "冒泡排序 - 比较: " << cmp_b << " 次, 交换: " << swap_b << " 次" << endl;

        // 插入排序
        insertionSortAccurate(arr_insert, N, cmp_i, move_i);
        cout << "插入排序 - 比较: " << cmp_i << " 次, 移动: " << move_i << " 次" << endl;

        // 计数排序
        countingSort(scores, N);
        cout << "计数排序 - 只需 " << (2 * N + 101) << " 次基本操作（遍历+前缀和+放置）" << endl;

        cout << endl;
        cout << "结论：当数据范围 k 远小于数据量 n 时，" << endl;
        cout << "      计数排序 O(n+k) 远优于 O(n²) 的比较排序。" << endl;
        cout << "      典型场景：成绩排名（0~100）、年龄排序（0~150）等。" << endl;
    }
    cout << endl;

    // ---------- 5. 计数排序的局限性 ----------
    cout << "---------- 5. 计数排序的局限性 ----------" << endl;
    cout << "计数排序不适合以下场景：" << endl;
    cout << "  (1) 数据范围太大（如 [0, 10^9]），计数数组内存不足" << endl;
    cout << "  (2) 存在负数时需要偏移处理（已实现）" << endl;
    cout << "  (3) 非整数数据无法直接映射到计数数组下标" << endl;
    cout << "  (4) 当 n 很小但 k 很大时，O(n+k) 不如 O(n log n)" << endl;
    cout << endl;

    // 演示范围大的问题
    {
        cout << "示例：数据范围大的情况" << endl;
        int data[] = {1, 1000, 500, 2000, 750};
        int n2 = sizeof(data) / sizeof(data[0]);
        // 范围 = 2000 - 1 + 1 = 2000，但实际只有 5 个元素
        int range = 2000 - 1 + 1;
        cout << "  数据量 n = " << n2 << ", 范围 k = " << range << endl;
        cout << "  计数排序需要 " << range << " 大小的计数数组（浪费！）" << endl;

        // 但计数排序仍然可以工作
        int data_copy[5];
        copyArray(data, data_copy, n2);
        countingSort(data_copy, n2);
        cout << "  计数排序结果: ";
        printArray(data_copy, n2, "");
        cout << "  但在这种情况下，插入排序 O(n²) = 25 次比较，" << endl;
        cout << "  计数排序 O(n+k) = 2005 次操作，反而更慢！" << endl;
    }
    cout << endl;

    // ---------- 6. 插入排序的稳定性验证 ----------
    cout << "---------- 6. 插入排序稳定性验证 ----------" << endl;
    {
        // 与 Lesson 29 类似的结构体测试
        struct Item {
            int value;
            int id;
        };

        Item items[] = {
            {5, 0}, {3, 1}, {8, 2}, {5, 3}, {3, 4}, {2, 5}
        };
        int n3 = 6;

        cout << "原始数据：";
        cout << "[";
        for (int i = 0; i < n3; i++) {
            if (i > 0) cout << ", ";
            cout << items[i].value << "(id=" << items[i].id << ")";
        }
        cout << "]" << endl;

        // 插入排序（稳定）
        for (int i = 1; i < n3; i++) {
            Item key = items[i];
            int j = i - 1;
            // 使用 > 而不是 >= 来保证相等元素不交换，维持稳定性
            while (j >= 0 && items[j].value > key.value) {
                items[j + 1] = items[j];
                j--;
            }
            items[j + 1] = key;
        }

        cout << "插入排序后：";
        cout << "[";
        for (int i = 0; i < n3; i++) {
            if (i > 0) cout << ", ";
            cout << items[i].value << "(id=" << items[i].id << ")";
        }
        cout << "]" << endl;

        cout << "观察：value=5 的元素 id 顺序为 0, 3（保持原始顺序）" << endl;
        cout << "      value=3 的元素 id 顺序为 1, 4（保持原始顺序）" << endl;
        cout << "  => 插入排序是【稳定】的" << endl;
    }
    cout << endl;

    cout << "============================================" << endl;
    cout << "  程序结束" << endl;
    cout << "============================================" << endl;

    return 0;
}
