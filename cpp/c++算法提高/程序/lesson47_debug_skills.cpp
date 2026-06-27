/*
 * C++算法提高 第47课 竞赛技巧与调试方法
 *
 * 本程序包含以下内容：
 *   第一部分：常见错误演示（5 种常见 Bug 及修复）
 *   第二部分：对拍系统 — 最大子段和（暴力 O(N²) vs 优化 O(N)）
 *   第三部分：时间复杂度估算指南
 *
 * 通过交互式菜单选择要运行的功能。
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <climits>
#include <cassert>
#include <cmath>
using namespace std;

// ============================================================
// 第一部分：常见错误演示
// ============================================================

// Bug 1：数组越界 — 修复演示
void demo_array_bounds() {
    cout << "\n========== Bug 1：数组越界 ==========" << endl;
    int a[100];

    // ❌ 错误写法（故意演示—这里不会实际执行越界，只展示逻辑）
    // for (int i = 0; i <= 100; i++) a[i] = i;  // i=100 时越界！

    // ✅ 正确写法
    for (int i = 0; i < 100; i++) {
        a[i] = i * i;
    }
    cout << "✅ 正确：数组 a[99] = " << a[99] << " (下标范围 0~99，共 100 个元素)" << endl;
    cout << "   错误：如果循环写成 i <= 100，则 a[100] 越界" << endl;
}

// Bug 2：未初始化变量 — 修复演示
void demo_uninit() {
    cout << "\n========== Bug 2：未初始化变量 ==========" << endl;

    // ❌ 错误写法
    // int sum;  // 局部变量未初始化，值是随机的！
    // for (int i = 0; i < 10; i++) sum += i;  // 结果不可预知

    // ✅ 正确写法
    int sum = 0;  // 必须显式赋初值
    for (int i = 0; i < 10; i++) {
        sum += i;
    }
    cout << "✅ 正确：sum = " << sum << " (初始化 sum = 0 后累加 0+1+...+9 = 45)" << endl;
    cout << "   错误：如果 sum 不初始化，值可能是内存中的随机垃圾值" << endl;
}

// Bug 3：整数溢出 — 修复演示
void demo_overflow() {
    cout << "\n========== Bug 3：整数溢出 ==========" << endl;

    // ❌ 错误写法
    int a = 100000, b = 100000;
    int c_wrong = a * b;  // 10^10 超出 int（约 2.1×10^9）范围，溢出！
    cout << "   ❌ int 溢出：100000 * 100000 = " << c_wrong << " (错误！应为 10000000000)" << endl;

    // ✅ 正确写法
    long long la = 100000, lb = 100000;
    long long c_correct = la * lb;
    cout << "   ✅ long long：100000 * 100000 = " << c_correct << " (正确)" << endl;

    // 另一个常见陷阱：int 相乘再赋给 long long
    int x = 100000, y = 100000;
    long long z_pitfall = (long long)x * y;  // 需要先强制转换
    // long long z_pitfall = x * y;  // ❌ 先做 int 乘法，结果已经溢出！
    cout << "   注意：int 相乘必须在乘法前就转为 long long" << endl;
    cout << "   long long 范围：约 ±9.2×10^18，int 范围：约 ±2.1×10^9" << endl;
}

// Bug 4：Off-by-One — 修复演示
void demo_off_by_one() {
    cout << "\n========== Bug 4：Off-by-One（边界差一） ==========" << endl;

    // 在有序数组中二分查找
    int arr[] = {1, 3, 5, 7, 9, 11, 13};
    int n = 7;
    int target = 9;

    // ✅ 正确的二分查找
    int left = 0, right = n - 1, found = -1;
    while (left <= right) {  // <= 确保检查 single-element 情况
        int mid = left + (right - left) / 2;  // 防止 left+right 溢出
        if (arr[mid] == target) {
            found = mid;
            break;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    cout << "✅ 正确：二分查找 target=9 的下标为 " << found << " (使用 left <= right)" << endl;
    cout << "   错误一：left < right 会漏掉 left==right 时唯一元素的情况" << endl;
    cout << "   错误二：mid = (left+right)/2 在大数组时可能溢出" << endl;
}

// Bug 5：死循环 — 修复演示
void demo_infinite_loop() {
    cout << "\n========== Bug 5：死循环 ==========" << endl;

    // ❌ 错误写法
    // int x = 1;
    // while (x > 0) {  // x 永远大于 0，死循环！
    //     cout << x << " ";
    //     x++;
    // }

    // ✅ 正确写法
    int x = 1;
    cout << "✅ 正确：打印 1 到 10: ";
    while (x <= 10) {
        cout << x << " ";
        x++;
    }
    cout << endl;
    cout << "   错误：while(x > 0) 没有终止条件会导致死循环" << endl;
    cout << "   另一个常见死循环：while(l<r){...} 内没有更新 l 或 r" << endl;
}

// ============================================================
// 第二部分：对拍系统 — 最大子段和
// ============================================================

// 暴力解法 O(N²)：枚举所有子数组
int max_subarray_brute(const vector<int>& a) {
    int n = a.size();
    int max_sum = INT_MIN;  // 初始化为最小值，处理全负数情况
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = i; j < n; j++) {
            sum += a[j];
            if (sum > max_sum) {
                max_sum = sum;
            }
        }
    }
    return max_sum;
}

// 优化解法 O(N)：Kadane 算法（动态规划）
int max_subarray_optimized(const vector<int>& a) {
    int max_ending_here = 0;
    int max_so_far = INT_MIN;
    for (int x : a) {
        // 关键：当前元素要么加入前面的子数组，要么自己单独开始
        max_ending_here = max(x, max_ending_here + x);
        max_so_far = max(max_so_far, max_ending_here);
    }
    return max_so_far;
}

// 随机数据生成器
vector<int> generate_test(int n, int value_range) {
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        // 生成 [-value_range, value_range] 范围内的随机整数
        a[i] = (rand() % (2 * value_range + 1)) - value_range;
    }
    return a;
}

// 对拍函数：运行 rounds 轮测试，比较两个解法的输出
void duipai(int rounds = 1000, int max_n = 100, int value_range = 100) {
    cout << "\n========== 对拍：最大子段和 ==========" << endl;
    cout << "测试轮数：" << rounds << "，最大数组长度：" << max_n << endl;
    cout << "正在测试..." << endl;

    srand((unsigned int)time(0));
    int passed = 0;

    for (int t = 1; t <= rounds; t++) {
        int n = rand() % max_n + 1;  // 1 ~ max_n
        vector<int> a = generate_test(n, value_range);

        int ans_brute = max_subarray_brute(a);
        int ans_optimized = max_subarray_optimized(a);

        if (ans_brute == ans_optimized) {
            passed++;
        } else {
            cout << "\n❌ 测试 #" << t << " 失败！n = " << n << endl;
            cout << "   暴力 O(N²) 答案：" << ans_brute << endl;
            cout << "   优化 O(N)  答案：" << ans_optimized << endl;
            cout << "   出错的数组：";
            for (int x : a) cout << x << " ";
            cout << endl;
            return;  // 发现 Bug 立即停止
        }

        // 每 200 轮打印一次进度
        if (t % 200 == 0) {
            cout << "   已通过 " << passed << "/" << t << " 组测试..." << endl;
        }
    }

    cout << "\n🎉 全部 " << rounds << " 组测试通过！" << endl;
    cout << "   优化解法的正确性得到充分验证。" << endl;
}

// 手动演示：用具体数组展示两种算法
void demo_max_subarray() {
    cout << "\n========== 最大子段和手动演示 ==========" << endl;

    vector<int> a = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << "数组：";
    for (int x : a) cout << x << " ";
    cout << endl;

    int ans1 = max_subarray_brute(a);
    int ans2 = max_subarray_optimized(a);

    cout << "暴力 O(N²) 结果：" << ans1 << " (子数组 [4, -1, 2, 1] 的和)" << endl;
    cout << "优化 O(N)  结果：" << ans2 << " (Kadane 算法)" << endl;
    cout << "最大子数组：[4, -1, 2, 1] → 和为 6" << endl;
}

// ============================================================
// 第三部分：时间复杂度估算指南
// ============================================================

void complexity_guide() {
    cout << "\n========== 时间复杂度估算指南 ==========" << endl;
    cout << endl;
    cout << "  ┌────────────────┬──────────────────────┬──────────────────────────────┐" << endl;
    cout << "  │ 数据范围 N     │ 可接受的时间复杂度   │ 典型算法                     │" << endl;
    cout << "  ├────────────────┼──────────────────────┼──────────────────────────────┤" << endl;
    cout << "  │ N ≤ 10         │ O(N!), O(2^N)        │ 全排列、回溯                 │" << endl;
    cout << "  │ N ≤ 15         │ O(2^N)               │ 子集枚举                     │" << endl;
    cout << "  │ N ≤ 20         │ O(N·2^N)             │ 状态压缩 DP                  │" << endl;
    cout << "  │ N ≤ 100        │ O(N³)                │ Floyd-Warshall、区间 DP      │" << endl;
    cout << "  │ N ≤ 500        │ O(N³)                │ 三重循环枚举                 │" << endl;
    cout << "  │ N ≤ 2000       │ O(N²)                │ 简单 DP、二维前缀和          │" << endl;
    cout << "  │ N ≤ 10⁵        │ O(N log N)            │ 排序、二分、堆优化 Dijkstra  │" << endl;
    cout << "  │ N ≤ 10⁶        │ O(N log N) 或 O(N)   │ 排序、线性筛、贪心           │" << endl;
    cout << "  │ N ≤ 10⁷        │ O(N)                 │ 线性扫描、前缀和             │" << endl;
    cout << "  │ N ≤ 10⁸        │ O(log N) 或 O(1)     │ 公式 / 二分查找              │" << endl;
    cout << "  └────────────────┴──────────────────────┴──────────────────────────────┘" << endl;
    cout << endl;
    cout << "💡 经验法则：现代评测机 ~10⁸ 次基本操作/秒" << endl;
    cout << "   示例：N=10⁵，O(N²)=10¹⁰ 次 → 约100秒 → 超时！" << endl;
    cout << "         N=10⁵，O(N log N)≈1.7×10⁶ 次 → 瞬间完成" << endl;
    cout << endl;
    cout << "🔢 常见函数增长速度对比（N=100000 时）：" << endl;
    cout << "   log₂N ≈ 17" << endl;
    cout << "   sqrt(N) ≈ 316" << endl;
    cout << "   N = 100,000" << endl;
    cout << "   N log N ≈ 1,700,000" << endl;
    cout << "   N² = 10,000,000,000  ← 已经不可接受！" << endl;
}

// ============================================================
// 断言（assert）使用演示
// ============================================================

void demo_assert() {
    cout << "\n========== assert 断言演示 ==========" << endl;

    // assert 用于开发阶段检查不变量
    int n = 5;
    assert(n > 0 && n <= 1000);  // 检查输入范围

    int a[] = {1, 2, 3, 4, 5};
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    assert(sum == 15);  // 检查累加结果

    cout << "✅ assert 检查通过：n=5在合法范围内，sum=15 正确" << endl;
    cout << "   如果 assert 失败，程序会立即终止并报告文件和行号" << endl;
    cout << "   在 OJ 提交时记得注释掉 assert 或使用 NDEBUG" << endl;
}

// ============================================================
// 调试宏演示
// ============================================================

void demo_debug_macro() {
    cout << "\n========== 调试宏演示 ==========" << endl;
    cout << "调试时在代码中添加：" << endl;
    cout << "  #define debug(x) cerr << #x << \" = \" << x << endl;" << endl;
    cout << "  debug(a[i]);  → 输出到标准错误流（不影响答案输出）" << endl;
    cout << "提交时注释掉 #define 行即可关闭所有调试输出。" << endl;
}

// ============================================================
// 打印调试演示
// ============================================================

void demo_print_debug() {
    cout << "\n========== 打印调试演示 ==========" << endl;

    // 模拟调试场景：在数组中找最大值
    int a[] = {3, 7, 2, 9, 1, 5};
    int n = 6;
    int max_val = INT_MIN;

    cout << "模拟查找最大值过程：" << endl;
    for (int i = 0; i < n; i++) {
        // 调试打印：观察每一次迭代的状态
        cerr << "[DEBUG] i=" << i << ", a[" << i << "]=" << a[i]
             << ", current_max=" << max_val << endl;

        if (a[i] > max_val) {
            max_val = a[i];
        }
    }
    cout << "最大值：" << max_val << " (调试信息已输出到 cerr)" << endl;
    cout << "提示：cout 输出答案，cerr 输出调试信息，互不干扰" << endl;
}

// ============================================================
// 主菜单
// ============================================================

void show_menu() {
    cout << "\n╔══════════════════════════════════════════════╗" << endl;
    cout << "║  第47课：竞赛技巧与调试方法 — 交互式演示     ║" << endl;
    cout << "╠══════════════════════════════════════════════╣" << endl;
    cout << "║  第一部分：常见错误分析                       ║" << endl;
    cout << "║    1. 数组越界                                ║" << endl;
    cout << "║    2. 未初始化变量                            ║" << endl;
    cout << "║    3. 整数溢出                                ║" << endl;
    cout << "║    4. Off-by-One（边界差一）                   ║" << endl;
    cout << "║    5. 死循环                                  ║" << endl;
    cout << "║    6. 一次性演示所有 Bug                       ║" << endl;
    cout << "╠══════════════════════════════════════════════╣" << endl;
    cout << "║  第二部分：对拍系统                            ║" << endl;
    cout << "║    7. 手动演示最大子段和                       ║" << endl;
    cout << "║    8. 运行对拍（自动验证）                     ║" << endl;
    cout << "╠══════════════════════════════════════════════╣" << endl;
    cout << "║  第三部分：工具演示                            ║" << endl;
    cout << "║    9. 时间复杂度估算指南                       ║" << endl;
    cout << "║   10. assert 断言演示                          ║" << endl;
    cout << "║   11. 调试宏演示                               ║" << endl;
    cout << "║   12. 打印调试演示                             ║" << endl;
    cout << "╠══════════════════════════════════════════════╣" << endl;
    cout << "║    0. 退出                                    ║" << endl;
    cout << "╚══════════════════════════════════════════════╝" << endl;
    cout << "请选择 [0-12]：";
}

int main() {
    // 设置中文本地环境
    setlocale(LC_ALL, "");

    int choice;
    do {
        show_menu();
        cin >> choice;

        switch (choice) {
            case 1:  demo_array_bounds();   break;
            case 2:  demo_uninit();         break;
            case 3:  demo_overflow();       break;
            case 4:  demo_off_by_one();     break;
            case 5:  demo_infinite_loop();  break;
            case 6:
                demo_array_bounds();
                demo_uninit();
                demo_overflow();
                demo_off_by_one();
                demo_infinite_loop();
                break;
            case 7:  demo_max_subarray();   break;
            case 8:  duipai();              break;
            case 9:  complexity_guide();    break;
            case 10: demo_assert();         break;
            case 11: demo_debug_macro();    break;
            case 12: demo_print_debug();    break;
            case 0:
                cout << "\n再见！祝竞赛顺利 🚀" << endl;
                break;
            default:
                cout << "无效选项，请重新选择。" << endl;
        }
    } while (choice != 0);

    return 0;
}
