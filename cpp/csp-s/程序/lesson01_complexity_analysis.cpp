/*
 * ============================================================
 * 第01课：时间复杂度分析与计算
 * 对应CSP-S考纲：算法复杂度分析、大O表示法、主定理
 *
 * 本程序演示不同复杂度的算法实现与性能对比：
 *   1. O(log n)   - 二分查找
 *   2. O(n)       - 线性搜索
 *   3. O(n log n) - 归并排序
 *   4. O(n^2)     - 冒泡排序
 *   5. O(2^n)     - 递归斐波那契（指数爆炸）
 *   6. O(n)       - 迭代斐波那契（线性优化）
 *
 * 通过计时对比，直观感受不同复杂度在实际运行中的差异。
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;
using namespace chrono;
using ll = long long;

// ==================== 工具函数 ====================

/*
 * 计时器：测量函数 f 在规模 n 下的运行时间（秒）
 * 通过高分辨率时钟获取精确的执行时间
 */
template<typename Func>
double measure_time(Func f, int n) {
    auto start = high_resolution_clock::now();
    f(n);
    auto end = high_resolution_clock::now();
    duration<double> elapsed = end - start;
    return elapsed.count();
}

/*
 * 生成有序数组 [0, 1, 2, ..., n-1]
 */
vector<int> generate_sorted_array(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; i++) arr[i] = i;
    return arr;
}

/*
 * 生成随机数组，元素范围 [0, n-1]
 */
vector<int> generate_random_array(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; i++) arr[i] = rand() % n;
    return arr;
}

// ==================== O(1) - 常数复杂度 ====================

/*
 * 直接通过下标访问数组元素，复杂度 O(1)
 * 无论数组多大，访问时间恒定为常数
 */
void demo_constant_time(int n) {
    vector<int> arr = generate_random_array(n);
    // 访问第一个元素的地址和最后一个元素，都是 O(1)
    volatile int x = arr[0];        // O(1)
    volatile int y = arr[n - 1];    // O(1)
    volatile int z = arr[n / 2];    // O(1)
    (void)x; (void)y; (void)z;      // 防止编译器优化
}

// ==================== O(log n) - 二分查找 ====================

/*
 * 二分查找：在有序数组中查找目标值
 * 时间复杂度：O(log n)
 * 递推式：T(n) = T(n/2) + O(1)  =>  T(n) = O(log n)
 *
 * 每次比较后搜索范围减半：
 * n, n/2, n/4, ..., 1  =>  共约 log₂(n) 步
 */
int binary_search_iterative(const vector<int>& arr, int target) {
    int l = 0, r = arr.size() - 1;
    int steps = 0;
    while (l <= r) {
        steps++;
        int mid = l + (r - l) / 2;  // 防止 (l+r)/2 溢出
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return -1;  // 未找到
}

/*
 * 演示二分查找的性能：
 * 对大小为 n 的有序数组执行多次查找
 */
void demo_binary_search(int n) {
    vector<int> arr = generate_sorted_array(n);
    // 执行 log₂(n) 次查找以放大时间差异（但每次仍是 O(log n)）
    int queries = max(1, (int)log2(n));
    for (int i = 0; i < queries; i++) {
        int target = rand() % n;
        int pos = binary_search_iterative(arr, target);
        // 验证正确性：arr[pos] 应该等于 target
        if (pos == -1 || arr[pos] != target) {
            // 这种情况不应发生（因为 target 在 [0, n-1] 范围内）
        }
    }
}

// ==================== O(n) - 线性搜索 ====================

/*
 * 线性搜索：在无序数组中查找目标值
 * 时间复杂度：
 *   最好：O(1) —— 目标在第一个位置
 *   最坏：O(n) —— 目标在最后一个位置或不存在
 *   平均：O(n) —— 期望检查 n/2 个元素
 */
int linear_search(const vector<int>& arr, int target) {
    for (int i = 0; i < (int)arr.size(); i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}

/*
 * 演示线性搜索的性能
 */
void demo_linear_search(int n) {
    vector<int> arr = generate_random_array(n);
    // 执行 10 次查找（最坏情况：查找不存在的元素）
    for (int t = 0; t < 10; t++) {
        int target = n + rand();  // 确保不存在，触发最坏情况
        volatile int pos = linear_search(arr, target);
    }
}

// ==================== O(n log n) - 归并排序 ====================

/*
 * 归并排序的合并步骤
 * 将两个有序子数组 arr[l..mid] 和 arr[mid+1..r] 合并
 */
void merge(vector<int>& arr, int l, int mid, int r) {
    int n1 = mid - l + 1;
    int n2 = r - mid;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

/*
 * 归并排序主函数
 * 时间复杂度：O(n log n)
 * 递推式：T(n) = 2·T(n/2) + O(n)
 * 根据主定理情况2（d = log₂2 = 1）：T(n) = O(n log n)
 *
 * 空间复杂度：O(n)（需要临时数组）
 * 稳定性：稳定排序（相等元素保持原有顺序）
 */
void merge_sort(vector<int>& arr, int l, int r) {
    if (l >= r) return;
    int mid = l + (r - l) / 2;
    merge_sort(arr, l, mid);       // 递归排序左半部分
    merge_sort(arr, mid + 1, r);   // 递归排序右半部分
    merge(arr, l, mid, r);         // 合并两个有序子数组
}

/*
 * 演示归并排序的性能
 */
void demo_merge_sort(int n) {
    vector<int> arr = generate_random_array(n);
    merge_sort(arr, 0, n - 1);
    // 验证有序性
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i - 1]) {
            cerr << "错误：归并排序结果不正确！" << endl;
            break;
        }
    }
}

// ==================== O(n^2) - 冒泡排序 ====================

/*
 * 冒泡排序（带优化：提前终止）
 * 时间复杂度：
 *   最好：O(n) —— 数组已排序，内层循环第一次遍历无交换即终止
 *   最坏：O(n^2) —— 数组逆序，需要完整的两层循环
 *   平均：O(n^2)
 *
 * 优化技巧：使用 swapped 标志检测是否已有序
 */
void bubble_sort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        // 每次冒泡将最大的未排序元素"浮"到末尾
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        // 优化：如果某轮没有发生交换，说明数组已有序
        if (!swapped) break;
    }
}

/*
 * 演示冒泡排序的性能
 * 注意：输入规模较大时，冒泡排序会非常慢（O(n^2)）
 */
void demo_bubble_sort(int n) {
    vector<int> arr = generate_random_array(n);
    bubble_sort(arr);
}

// ==================== O(2^n) vs O(n) - 斐波那契对比 ====================

/*
 * 递归求解斐波那契数列（指数复杂度，非常低效）
 * 时间复杂度：O(2^n)
 * 递推式：T(n) = T(n-1) + T(n-2) + O(1)
 * 解：T(n) = O(φ^n) ≈ O(1.618^n)，近似 O(2^n)
 *
 * 问题：存在大量重复计算
 * F(5) 调用结构（重复计算严重）：
 *           F(5)
 *         /      \
 *      F(4)      F(3)
 *     /    \     /   \
 *   F(3)  F(2) F(2) F(1)
 *   ...
 * 仅 n=40 就要计算约 2 亿次！
 */
ll fibonacci_recursive(int n) {
    if (n <= 1) return n;
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

// 递归调用计数器（用于演示重复计算的严重性）
ll fib_call_count = 0;

ll fibonacci_recursive_count(int n) {
    fib_call_count++;
    if (n <= 1) return n;
    return fibonacci_recursive_count(n - 1) + fibonacci_recursive_count(n - 2);
}

/*
 * 迭代求解斐波那契数列（线性复杂度，高效）
 * 时间复杂度：O(n)
 * 空间复杂度：O(1) —— 只用了 3 个变量
 *
 * 原理：自底向上计算，避免重复计算
 * F(0)=0, F(1)=1, F(2)=1, F(3)=2, ...
 */
ll fibonacci_iterative(int n) {
    if (n <= 1) return n;
    ll a = 0, b = 1;  // a = F(0), b = F(1)
    for (int i = 2; i <= n; i++) {
        ll c = a + b;  // F(i) = F(i-2) + F(i-1)
        a = b;
        b = c;
    }
    return b;
}

/*
 * 矩阵快速幂求解斐波那契（对数复杂度）
 * 时间复杂度：O(log n)
 *
 * 原理：利用矩阵幂的性质
 * [F(n+1) F(n)  ]   =   [1 1]^n
 * [F(n)   F(n-1)]       [1 0]
 *
 * 通过快速幂将矩阵的 n 次方降为 O(log n)
 */
const ll MOD = 1000000007;

struct Matrix {
    ll a[2][2];
    Matrix() {
        a[0][0] = a[0][1] = a[1][0] = a[1][1] = 0;
    }
};

Matrix mat_mul(const Matrix& A, const Matrix& B) {
    Matrix C;
    for (int i = 0; i < 2; i++)
        for (int k = 0; k < 2; k++)
            if (A.a[i][k])
                for (int j = 0; j < 2; j++)
                    C.a[i][j] = (C.a[i][j] + A.a[i][k] * B.a[k][j]) % MOD;
    return C;
}

Matrix mat_pow(Matrix A, int n) {
    Matrix res;
    res.a[0][0] = res.a[1][1] = 1;  // 单位矩阵
    while (n) {
        if (n & 1) res = mat_mul(res, A);
        A = mat_mul(A, A);
        n >>= 1;
    }
    return res;
}

ll fibonacci_matrix(int n) {
    if (n <= 1) return n;
    Matrix base;
    base.a[0][0] = base.a[0][1] = base.a[1][0] = 1;
    base.a[1][1] = 0;
    Matrix res = mat_pow(base, n - 1);
    return res.a[0][0];
}

/*
 * 演示斐波那契三种实现的性能差异
 */
void demo_fibonacci(int n) {
    // 注意：n 不要太大，否则递归版会卡死
    // 这里仅对比迭代版和矩阵版
    ll ans1 = fibonacci_iterative(n);
    ll ans2 = fibonacci_matrix(n);
    if (ans1 != ans2) {
        cerr << "错误：迭代版和矩阵版结果不一致！" << endl;
    }
}

// ==================== O(n!) - 全排列示例 ====================

/*
 * 递归生成全排列（阶乘复杂度）
 * 时间复杂度：O(n!)
 *
 * 适用场景：n 很小的时候（n ≤ 10），如旅行商问题的暴力枚举
 * CSP-S 中常见的用法：
 *   - next_permutation() 枚举排列（习题：全排列、八皇后）
 *   - 暴力枚举用于小数据范围的验证
 */
void generate_permutations(vector<int>& arr, int idx, int& count) {
    if (idx == (int)arr.size()) {
        count++;
        // 此处可以处理每个排列，例如计算代价
        return;
    }
    for (int i = idx; i < (int)arr.size(); i++) {
        swap(arr[idx], arr[i]);
        generate_permutations(arr, idx + 1, count);
        swap(arr[idx], arr[i]);  // 回溯
    }
}

/*
 * 演示全排列的复杂度（仅对小规模展示）
 */
void demo_permutations(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; i++) arr[i] = i + 1;
    int count = 0;
    generate_permutations(arr, 0, count);
    // n! = 1*2*...*n，验证计数
    int expected = 1;
    for (int i = 2; i <= n; i++) expected *= i;
    if (count != expected) {
        cerr << "排列计数 != n! (n=" << n << ", count=" << count << ", n!=" << expected << ")" << endl;
    }
}

// ==================== 主程序：性能对比演示 ====================

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "============================================================" << endl;
    cout << "  第01课：时间复杂度分析与计算 —— 性能对比演示" << endl;
    cout << "============================================================" << endl;
    cout << endl;

    // 设置随机种子
    srand(time(nullptr));

    // ============ 斐波那契：递归 vs 迭代（指数 vs 线性） ============
    cout << "【演示1】斐波那契数列：递归 O(2^n) vs 迭代 O(n)" << endl;
    cout << "------------------------------------------------------" << endl;

    // 递归版：展示调用次数的指数增长
    cout << "递归版调用次数分析（n 小时才可测试）：" << endl;
    cout << "  n\t调用次数\t\t理论 2^(n+1)-1" << endl;
    cout << "  " << string(50, '-') << endl;
    for (int n = 10; n <= 30; n += 5) {
        fib_call_count = 0;
        fibonacci_recursive_count(n);
        ll theory = (1LL << (n + 1)) - 1;  // 2^(n+1) - 1
        cout << "  " << n << "\t" << fib_call_count
             << "\t\t" << theory << endl;
    }
    cout << endl;

    // 迭代版 vs 矩阵版性能对比
    cout << "迭代版 O(n) vs 矩阵版 O(log n) 时间对比：" << endl;
    vector<int> fib_ns = {40, 100000, 1000000, 10000000, 100000000};

    for (int n : fib_ns) {
        cout << "  n = " << n << ":" << endl;

        // 迭代版 O(n)
        if (n <= 100000000) {
            double t_iter = measure_time(demo_fibonacci, n);
            // 仅用迭代，取模后结果才有意义
            auto start = high_resolution_clock::now();
            ll ans_iter = fibonacci_iterative(n) % MOD;
            auto end = high_resolution_clock::now();
            duration<double> elapsed = end - start;
            cout << "    迭代 O(n)     : " << fixed << setprecision(6)
                 << elapsed.count() << "s  (ans=" << ans_iter << ")" << endl;
        }

        // 矩阵版 O(log n)
        {
            auto start = high_resolution_clock::now();
            ll ans_mat = fibonacci_matrix(n);
            auto end = high_resolution_clock::now();
            duration<double> elapsed = end - start;
            cout << "    矩阵 O(log n) : " << fixed << setprecision(6)
                 << elapsed.count() << "s  (ans=" << ans_mat << ")" << endl;
        }
    }
    cout << endl;

    // ============ 排序算法：不同复杂度对比 ============
    cout << "【演示2】排序算法复杂度对比" << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "  规模 n\t归并排序 O(n log n)\t冒泡排序 O(n^2)" << endl;
    cout << "  " << string(55, '-') << endl;

    vector<int> sizes = {1000, 5000, 10000, 20000, 50000, 100000};

    for (int n : sizes) {
        cout << "  " << n;

        // 归并排序
        {
            double t = measure_time(demo_merge_sort, n);
            cout << "\t" << fixed << setprecision(4) << t << "s";
        }

        // 冒泡排序（n 大时跳过，太慢）
        if (n <= 20000) {
            double t = measure_time(demo_bubble_sort, n);
            cout << "\t\t" << fixed << setprecision(4) << t << "s";
        } else {
            cout << "\t\t>>>> 跳过（预计耗时过长）";
        }

        cout << endl;
    }
    cout << endl;

    // ============ 二分查找 vs 线性搜索 ============
    cout << "【演示3】二分查找 O(log n) vs 线性搜索 O(n)" << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "  规模 n\t二分查找\t\t线性搜索" << endl;
    cout << "  " << string(55, '-') << endl;

    sizes = {1000, 10000, 100000, 1000000, 10000000};

    for (int n : sizes) {
        cout << "  " << n;

        {
            double t = measure_time(demo_binary_search, n);
            cout << "\t" << fixed << setprecision(6) << t << "s";
        }

        {
            double t = measure_time(demo_linear_search, n);
            cout << "\t" << fixed << setprecision(6) << t << "s";
        }

        cout << endl;
    }
    cout << endl;

    // ============ 全排列：阶乘复杂度 ============
    cout << "【演示4】全排列：O(n!) 复杂度" << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "  n\tn!\t\t操作次数\t时间" << endl;
    cout << "  " << string(50, '-') << endl;

    for (int n = 3; n <= 10; n++) {
        int fact = 1;
        for (int i = 2; i <= n; i++) fact *= i;

        double t = measure_time(demo_permutations, n);

        cout << "  " << n << "\t" << fact;
        if (fact < 100000) cout << "\t\t";
        else cout << "\t";
        cout << fact << "\t\t" << fixed << setprecision(6) << t << "s" << endl;
    }
    cout << endl;

    // ============ 复杂度理论总结表 ============
    cout << "【总结】常见复杂度在1秒时限下的最大可行规模" << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "  复杂度级别\t\t 最大 n (约)\t典型算法" << endl;
    cout << "  " << string(55, '-') << endl;
    cout << "  O(n!)\t\t\t 10\t\t全排列枚举" << endl;
    cout << "  O(2^n)\t\t 25\t\t状态压缩DP / 子集枚举" << endl;
    cout << "  O(n^3)\t\t 200\t\tFloyd最短路" << endl;
    cout << "  O(n^2)\t\t 5000\t\t基础DP / 冒泡排序" << endl;
    cout << "  O(n sqrt(n))\t\t 10^5\t\t分块算法" << endl;
    cout << "  O(n log n)\t\t 10^6\t\t排序 / 线段树" << endl;
    cout << "  O(n)\t\t\t 10^7\t\t线性扫描 / 前缀和" << endl;
    cout << "  O(log n)\t\t --\t\t二分查找 / 快速幂" << endl;
    cout << "  O(1)\t\t\t --\t\t公式计算" << endl;

    return 0;
}
