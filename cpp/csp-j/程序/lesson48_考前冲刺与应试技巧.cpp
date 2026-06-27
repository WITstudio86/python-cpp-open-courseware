/*
 * ============================================================================
 * 课程：Lesson 48 - CSP-J 考前冲刺与应试技巧
 * 内容：常见错误陷阱、调试技巧、算法模板复习
 * 目标：通过"错误示范 + 正确修正"的对比方式，强化避坑意识；
 *       复习高频算法模板，确保考场上能快速准确地写出代码
 * 难度：CSP-J 综合复习
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// 第一部分：常见陷阱 —— 错误示范与修正
// ============================================================================

// ---------------------------------------------------------------------------
// 陷阱1：数组越界访问
// ---------------------------------------------------------------------------

/*
 * 【错误示范】访问 arr[n] 导致越界
 * 数组声明为 a[5]，合法下标是 0~4，但循环中访问了 a[5]
 */
void pitfall_array_oob_wrong() {
    cout << "--- 陷阱1：数组越界 ---" << endl;

    // 错误代码（注释掉，仅展示）
    // int a[5] = {10, 20, 30, 40, 50};
    // for (int i = 0; i <= 5; i++) {  // BUG: 应该是 i < 5
    //     cout << a[i] << " ";        // 访问 a[5] 越界！
    // }

    cout << "  [错误示范] int a[5]; for(i=0; i<=5; i++) 会访问 a[5]，越界！" << endl;
    cout << "  [后果] 未定义行为，可能读到垃圾值或程序崩溃" << endl;
}

/*
 * 【正确修正】严格保证下标在 [0, n-1] 范围内
 */
void pitfall_array_oob_fixed() {
    int a[5] = {10, 20, 30, 40, 50};
    cout << "  [正确修正] ";
    for (int i = 0; i < 5; i++) {      // 正确：i < 5
        cout << a[i] << " ";
    }
    cout << endl;

    // 通用模式：用 const 变量代替魔数
    const int N = 5;
    int b[N];
    for (int i = 0; i < N; i++) {
        b[i] = i * 10;
    }
    cout << "  [最佳实践] 用 const int N 定义数组大小，循环条件写 i < N，b[4]=" << b[N-1] << endl;
}

// ---------------------------------------------------------------------------
// 陷阱2：未初始化的变量
// ---------------------------------------------------------------------------

/*
 * 【错误示范】局部变量未初始化，包含垃圾值
 */
void pitfall_uninit_wrong() {
    cout << "--- 陷阱2：未初始化变量 ---" << endl;

    // 错误代码（仅展示逻辑）
    // int sum;
    // for (int i = 1; i <= 10; i++) {
    //     sum += i;       // BUG: sum 未初始化，初值是垃圾值！
    // }

    cout << "  [错误示范] int sum; sum += i;   // sum 未初始化，初值是垃圾值" << endl;
    cout << "  [后果] 结果不可预测，每次运行可能不同" << endl;
}

/*
 * 【正确修正】声明时立即赋初值
 */
void pitfall_uninit_fixed() {
    int sum = 0;  // 正确：声明的同时初始化为 0
    for (int i = 1; i <= 10; i++) {
        sum += i;
    }
    cout << "  [正确修正] int sum = 0;  sum = " << sum << " (1到10的和=55)" << endl;
    if (sum == 55) {
        cout << "  [验证] 结果正确" << endl;
    }
}

// ---------------------------------------------------------------------------
// 陷阱3：整数溢出
// ---------------------------------------------------------------------------

/*
 * 【错误示范】两个大 int 相乘溢出
 */
void pitfall_overflow_wrong() {
    cout << "--- 陷阱3：整数溢出 ---" << endl;

    int a = 100000;
    int b = 100000;
    int result = a * b;  // BUG: 10^10 > INT_MAX (约 2.1e9)，溢出！

    cout << "  [错误示范] int a=100000, b=100000; int result = a * b;" << endl;
    cout << "  [错误结果] result = " << result << " (正确应为 10000000000)" << endl;
    cout << "  [原因] 10^10 超过 int 范围 (≈2.1×10^9)，发生了溢出" << endl;
}

/*
 * 【正确修正】使用 long long 类型，或在运算前强转
 */
void pitfall_overflow_fixed() {
    long long a = 100000LL;
    long long b = 100000LL;
    long long result = a * b;  // 正确：long long 足够存储

    cout << "  [正确修正] long long a=100000, b=100000; long long result = a * b;" << endl;
    cout << "  [正确结果] result = " << result << " (10000000000)" << endl;

    // 另一种方式：int 变量做乘法时强制转换
    int x = 100000, y = 100000;
    long long res2 = 1LL * x * y;  // 1LL 使得整个表达式按 long long 计算
    cout << "  [替代方案] 1LL * x * y = " << res2 << endl;
}

// ---------------------------------------------------------------------------
// 陷阱4：文件输入输出（freopen）
// ---------------------------------------------------------------------------

/*
 * 【正确用法】使用 freopen 重定向 stdin/stdout
 * 考试中通常会使用文件输入输出，需要在 main 开头正确设置
 */
void pitfall_freopen_demo() {
    cout << "--- 陷阱4：freopen 文件I/O ---" << endl;

    cout << "  [考试标准模板]" << endl;
    cout << "  int main() {" << endl;
    cout << "      freopen(\"problem.in\",  \"r\", stdin);   // 重定向输入" << endl;
    cout << "      freopen(\"problem.out\", \"w\", stdout);  // 重定向输出" << endl;
    cout << "      // 之后正常使用 cin / cout 即可" << endl;
    cout << "      // ..." << endl;
    cout << "      fclose(stdin);   // 可选：关闭文件" << endl;
    cout << "      fclose(stdout);" << endl;
    cout << "      return 0;" << endl;
    cout << "  }" << endl;

    cout << "  [注意1] 文件名要与题目要求一致，注意大小写" << endl;
    cout << "  [注意2] 不要在 freopen 之后再使用 ios::sync_with_stdio(false)" << endl;
    cout << "  [注意3] 本地调试时可注释掉 freopen，提交前取消注释" << endl;
}

// ---------------------------------------------------------------------------
// 陷阱5：assert 调试宏
// ---------------------------------------------------------------------------

/*
 * assert() 用于在开发阶段检查不变量，发现逻辑错误
 * 在正式提交时可以通过 #define NDEBUG 禁用所有 assert
 */
void pitfall_assert_demo() {
    cout << "--- 陷阱5：assert 使用 ---" << endl;

    // 示例：检查数组下标
    const int N = 10;
    int arr[N] = {0};

    int index = 5;
    assert(index >= 0 && index < N);  // 确保下标合法
    arr[index] = 42;
    cout << "  [assert 检查通过] arr[" << index << "] = " << arr[index] << endl;

    // 示例：检查函数前置条件
    int divisor = 3;
    assert(divisor != 0);  // 确保除数不为0
    int quotient = 100 / divisor;
    cout << "  [assert 检查通过] 100 / " << divisor << " = " << quotient << endl;

    cout << "  [注意] 如果 assert 条件为 false，程序会立即终止并输出文件和行号" << endl;
    cout << "  [考试建议] 调试时保留 assert，提交前可加 #define NDEBUG 去掉" << endl;
}

// ---------------------------------------------------------------------------
// 陷阱6：DEBUG_PRINT 条件调试宏
// ---------------------------------------------------------------------------

/*
 * 调试宏：在本地调试时输出详细信息，提交时一键关闭
 */
#define DEBUG  // 注释掉此行可关闭所有调试输出

#ifdef DEBUG
    #define DEBUG_PRINT(x) do { cerr << "[DEBUG] " << x << endl; } while(0)
#else
    #define DEBUG_PRINT(x) do { } while(0)
#endif

void pitfall_debug_print_demo() {
    cout << "--- 陷阱6：DEBUG_PRINT 调试宏 ---" << endl;
    cout << "  [说明] 使用 DEBUG_PRINT 输出到 cerr，不影响标准输出" << endl;
    cout << "  [说明] 注释 #define DEBUG 可一键关闭所有调试输出" << endl;

    DEBUG_PRINT("当前正在 pitfall_debug_print_demo() 中");

    int a = 10, b = 20;
    DEBUG_PRINT("a = " << a << ", b = " << b);  // 仅在 DEBUG 定义时输出

    int sum = a + b;
    DEBUG_PRINT("a + b = " << sum);

    cout << "  [演示] a + b = " << sum << " (正常输出)" << endl;
}

// ============================================================================
//  第二部分：CSP-J 算法模板复习
// ============================================================================

// ---------------------------------------------------------------------------
// 模板1：快速排序 (Quick Sort)
// ---------------------------------------------------------------------------

/*
 * 快速排序的分区函数：选取最右侧元素为 pivot
 * 将小于 pivot 的元素放在左边，大于 pivot 的放在右边
 * 返回 pivot 最终位置
 */
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];  // 选取最右侧元素作为基准
    int i = low - 1;        // i 指向小于 pivot 区域的最后一个元素

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);  // 将 pivot 放到正确位置
    return i + 1;
}

/*
 * 快速排序主函数：递归分治
 * 时间复杂度：平均 O(N log N)，最坏 O(N^2)（可通过随机 pivot 优化）
 * 空间复杂度：O(log N)（递归栈）
 */
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);  // 分区点
        quickSort(arr, low, pi - 1);          // 递归排序左半部分
        quickSort(arr, pi + 1, high);         // 递归排序右半部分
    }
}

// ---------------------------------------------------------------------------
// 模板2：二分查找 (Binary Search)
// ---------------------------------------------------------------------------

/*
 * 二分查找：在有序数组中查找目标值
 * 返回目标值的下标，若不存在则返回 -1
 * 时间复杂度：O(log N)
 */
int binarySearch(const vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;  // 防溢出写法
        if (arr[mid] == target) {
            return mid;           // 找到目标
        } else if (arr[mid] < target) {
            left = mid + 1;       // 目标在右半部分
        } else {
            right = mid - 1;      // 目标在左半部分
        }
    }
    return -1;  // 未找到
}

/*
 * 二分查找变体：查找第一个 >= target 的位置 (lower_bound)
 */
int lowerBound(const vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size();  // 注意：right 初始化为 n，不是 n-1

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] >= target) {
            right = mid;       // 答案在 [left, mid]
        } else {
            left = mid + 1;    // 答案在 [mid+1, right]
        }
    }
    return left;  // left 指向第一个 >= target 的位置
}

// ---------------------------------------------------------------------------
// 模板3：前缀和 (Prefix Sum)
// ---------------------------------------------------------------------------

/*
 * 一维前缀和：pre[i] = arr[0] + arr[1] + ... + arr[i-1]
 * 区间 [l, r] 的和 = pre[r+1] - pre[l]
 * 时间复杂度：预处理 O(N)，查询 O(1)
 */
vector<long long> prefixSum(const vector<int>& arr) {
    const int N = arr.size();
    vector<long long> pre(N + 1, 0);
    for (int i = 0; i < N; i++) {
        pre[i + 1] = pre[i] + arr[i];
    }
    return pre;
}

/*
 * 二维前缀和：pre[i][j] = 矩阵 (0,0) 到 (i-1,j-1) 的和
 * 子矩阵 (x1,y1) 到 (x2,y2) 的和：
 *   sum = pre[x2+1][y2+1] - pre[x1][y2+1] - pre[x2+1][y1] + pre[x1][y1]
 */
vector<vector<long long>> prefixSum2D(const vector<vector<int>>& matrix) {
    const int R = matrix.size();
    const int C = matrix[0].size();
    vector<vector<long long>> pre(R + 1, vector<long long>(C + 1, 0));

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            pre[i + 1][j + 1] = pre[i][j + 1] + pre[i + 1][j]
                              - pre[i][j] + matrix[i][j];
        }
    }
    return pre;
}

// ---------------------------------------------------------------------------
// 模板4：GCD 和 LCM
// ---------------------------------------------------------------------------

/*
 * 欧几里得算法（辗转相除法）求最大公约数
 * 递归版本，简洁优雅
 */
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

/*
 * 迭代版本（避免递归栈开销，某些环境下更安全）
 */
int gcd_iterative(int a, int b) {
    while (b != 0) {
        int tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

/*
 * 最小公倍数：先除后乘防溢出
 */
int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}

// ---------------------------------------------------------------------------
// 模板5：快速幂（含取模）
// ---------------------------------------------------------------------------

/*
 * 快速幂：计算 (base^exp) % mod
 * 原理：将指数按二进制拆分，e.g. 2^13 = 2^(1101)_2 = 2^8 * 2^4 * 2^1
 * 时间复杂度：O(log exp)
 */
long long fastPow(long long base, long long exp, long long mod) {
    long long result = 1 % mod;
    base %= mod;

    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

// ---------------------------------------------------------------------------
// 模板6：基础素数判断
// ---------------------------------------------------------------------------

/*
 * 判断一个数是否为素数
 * 只需检查到 sqrt(n)，因为如果 n 有因子，必然有一个 <= sqrt(n)
 * 时间复杂度：O(sqrt(N))
 */
bool isPrime(int n) {
    if (n <= 1) return false;       // 0 和 1 不是素数
    if (n <= 3) return true;        // 2 和 3 是素数
    if (n % 2 == 0 || n % 3 == 0) return false;  // 排除 2 和 3 的倍数

    // 检查 6k ± 1 形式的因子
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

// ============================================================================
// 第三部分：常用技巧速查
// ============================================================================

/*
 * 技巧清单：
 * 1. memset 只能赋 0、-1、0x3f 等字节级值，不能用于填充其他值
 * 2. vector 初始化：vector<int> v(n, 0)  // n 个 0
 * 3. 取整技巧：向上取整 (a + b - 1) / b
 * 4. 字符串转数字：stoi, stoll, stod
 * 5. 数字转字符串：to_string(value)
 * 6. 去重：sort(v.begin(), v.end()); v.erase(unique(...), v.end());
 * 7. 使用 1LL << k 而不是 1 << k 来避免移位溢出
 * 8. INF 常量建议 0x3f3f3f3f（约 1.06e9），两个 INF 相加不溢出
 */

// ============================================================================
// 第四部分：综合演示与测试主函数
// ============================================================================

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "====================================================" << endl;
    cout << "  Lesson 48: CSP-J 考前冲刺与应试技巧" << endl;
    cout << "====================================================" << endl;
    cout << endl;

    // ==================== 陷阱演示 ====================
    cout << "【第一部分：常见陷阱演示】" << endl;
    cout << "==============================================" << endl;

    pitfall_array_oob_wrong();
    pitfall_array_oob_fixed();
    cout << endl;

    pitfall_uninit_wrong();
    pitfall_uninit_fixed();
    cout << endl;

    pitfall_overflow_wrong();
    pitfall_overflow_fixed();
    cout << endl;

    pitfall_freopen_demo();
    cout << endl;

    pitfall_assert_demo();
    cout << endl;

    pitfall_debug_print_demo();
    cout << endl;

    // ==================== 算法模板测试 ====================
    cout << endl;
    cout << "【第二部分：算法模板复习与测试】" << endl;
    cout << "==============================================" << endl;

    // --- 快速排序 ---
    cout << "--- 快速排序 ---" << endl;
    {
        vector<int> arr = {38, 27, 43, 3, 9, 82, 10};
        cout << "  排序前: ";
        for (int x : arr) cout << x << " ";
        cout << endl;

        quickSort(arr, 0, arr.size() - 1);

        cout << "  排序后: ";
        for (int x : arr) cout << x << " ";
        cout << endl;

        // 验证
        bool sorted = true;
        for (size_t i = 1; i < arr.size(); i++) {
            if (arr[i] < arr[i - 1]) { sorted = false; break; }
        }
        cout << "  [验证] " << (sorted ? "排序正确" : "排序错误！") << endl;
    }
    cout << endl;

    // --- 二分查找 ---
    cout << "--- 二分查找 ---" << endl;
    {
        vector<int> arr = {2, 5, 8, 12, 16, 23, 38, 45, 56, 72};
        cout << "  有序数组: ";
        for (int x : arr) cout << x << " ";
        cout << endl;

        int t1 = 23, t2 = 50;
        int idx1 = binarySearch(arr, t1);
        int idx2 = binarySearch(arr, t2);

        cout << "  查找 " << t1 << ": 索引=" << idx1 << " (期望5) "
             << (idx1 == 5 ? "[正确]" : "[错误]") << endl;
        cout << "  查找 " << t2 << ": 索引=" << idx2 << " (期望-1) "
             << (idx2 == -1 ? "[正确]" : "[错误]") << endl;

        int lb = lowerBound(arr, 40);
        cout << "  lower_bound(40): 索引=" << lb << " (期望7, 即45的位置) "
             << (lb == 7 ? "[正确]" : "[错误]") << endl;
    }
    cout << endl;

    // --- 前缀和 ---
    cout << "--- 前缀和 ---" << endl;
    {
        vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6};
        vector<long long> pre = prefixSum(arr);

        cout << "  原数组: ";
        for (int x : arr) cout << x << " ";
        cout << endl;

        cout << "  前缀和: ";
        for (long long x : pre) cout << x << " ";
        cout << endl;

        // 区间 [2, 5] 的和 = arr[2]+arr[3]+arr[4]+arr[5] = 4+1+5+9 = 19
        int l = 2, r = 5;
        long long sum = pre[r + 1] - pre[l];
        cout << "  区间 [" << l << ", " << r << "] 的和 = " << sum
             << " (期望19) " << (sum == 19 ? "[正确]" : "[错误]") << endl;
    }
    cout << endl;

    // --- 二维前缀和 ---
    cout << "--- 二维前缀和 ---" << endl;
    {
        vector<vector<int>> mat = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };
        auto pre2d = prefixSum2D(mat);

        // 子矩阵 (0,0) 到 (1,1) 的和 = 1+2+4+5 = 12
        int x1 = 0, y1 = 0, x2 = 1, y2 = 1;
        long long sum = pre2d[x2 + 1][y2 + 1] - pre2d[x1][y2 + 1]
                      - pre2d[x2 + 1][y1] + pre2d[x1][y1];
        cout << "  子矩阵 (" << x1 << "," << y1 << ") 到 (" << x2 << "," << y2 << ") 的和 = " << sum
             << " (期望12) " << (sum == 12 ? "[正确]" : "[错误]") << endl;
    }
    cout << endl;

    // --- GCD / LCM ---
    cout << "--- GCD / LCM ---" << endl;
    {
        cout << "  gcd(36, 48)   = " << gcd(36, 48)
             << " (期望12) " << (gcd(36, 48) == 12 ? "[正确]" : "[错误]") << endl;
        cout << "  gcd(17, 13)   = " << gcd(17, 13)
             << " (期望1) " << (gcd(17, 13) == 1 ? "[正确]" : "[错误]") << endl;
        cout << "  gcd(100, 0)   = " << gcd(100, 0)
             << " (期望100) " << (gcd(100, 0) == 100 ? "[正确]" : "[错误]") << endl;
        cout << "  lcm(12, 18)   = " << lcm(12, 18)
             << " (期望36) " << (lcm(12, 18) == 36 ? "[正确]" : "[错误]") << endl;
        cout << "  lcm(7, 11)    = " << lcm(7, 11)
             << " (期望77) " << (lcm(7, 11) == 77 ? "[正确]" : "[错误]") << endl;
    }
    cout << endl;

    // --- 快速幂 ---
    cout << "--- 快速幂 ---" << endl;
    {
        const long long MOD = 1000000007LL;
        cout << "  2^10 mod 1e9+7  = " << fastPow(2, 10, MOD)
             << " (期望1024) " << (fastPow(2, 10, MOD) == 1024 ? "[正确]" : "[错误]") << endl;
        cout << "  3^5  mod 100    = " << fastPow(3, 5, 100)
             << " (期望43) " << (fastPow(3, 5, 100) == 43 ? "[正确]" : "[错误]") << endl;
        cout << "  7^0  mod 13     = " << fastPow(7, 0, 13)
             << " (期望1) " << (fastPow(7, 0, 13) == 1 ? "[正确]" : "[错误]") << endl;
        cout << "  5^3  mod 1      = " << fastPow(5, 3, 1)
             << " (期望0) " << (fastPow(5, 3, 1) == 0 ? "[正确]" : "[错误]") << endl;
    }
    cout << endl;

    // --- 素数判断 ---
    cout << "--- 素数判断 ---" << endl;
    {
        int tests[] = {1, 2, 3, 4, 17, 25, 97, 100, 1000000007};
        for (int n : tests) {
            cout << "  isPrime(" << n << ") = " << (isPrime(n) ? "true" : "false") << endl;
        }
        cout << "  [记忆] 1不是素数，2是最小的素数" << endl;
    }
    cout << endl;

    // ==================== 考前提醒 ====================
    cout << "============================================" << endl;
    cout << "【考前重要提醒】" << endl;
    cout << "============================================" << endl;
    cout << "  1. 文件名：确认题目要求的输入/输出文件名" << endl;
    cout << "  2. 文件操作：freopen 不要写错文件名" << endl;
    cout << "  3. 数据类型：注意 int vs long long，防止溢出" << endl;
    cout << "  4. 数组大小：开够空间，通常比题目最大值多 5~10" << endl;
    cout << "  5. 初始化：所有变量一定要初始化" << endl;
    cout << "  6. 边界条件：n=0, n=1 的情况要单独处理" << endl;
    cout << "  7. 取模运算：每次运算后及时取模，防止中间溢出" << endl;
    cout << "  8. 调试输出：提交前删除或注释掉所有调试输出" << endl;
    cout << "  9. 样例测试：提交前一定要用题目给的样例测试" << endl;
    cout << "  10. 时间管理：先做简单题，确保基础分，再攻坚难题" << endl;
    cout << "============================================" << endl;

    return 0;
}
