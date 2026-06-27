/*
 * ============================================
 * 第35课：动态规划入门——记忆化搜索
 * ============================================
 * 本程序演示：
 *   1. 朴素递归斐波那契（低效，用于对比）
 *   2. 记忆化搜索斐波那契（高效）
 *   3. 记忆化搜索爬楼梯问题
 *   4. 例题完整解答
 *
 * 核心思想：用数组存储已计算的结果，避免重复计算，
 * 将时间复杂度从 O(2^n) 降为 O(n)。
 * ============================================
 */

#include <iostream>
#include <cstring>   // memset
#include <ctime>     // clock
using namespace std;

// ==========================================
// 1. 朴素递归 —— 斐波那契（仅用于对比）
//    时间复杂度 O(2^n)，空间复杂度 O(n)
//    警告：n > 40 时运行极慢，仅作演示！
// ==========================================
long long fib_naive(int n) {
    if (n <= 2) return 1;                     // 递归边界：F(1)=1, F(2)=1
    return fib_naive(n - 1) + fib_naive(n - 2); // 递推公式
}

// ==========================================
// 2. 记忆化搜索 —— 斐波那契
//    时间复杂度 O(n)，空间复杂度 O(n)
//    memo[i] = -1 表示尚未计算
// ==========================================
long long fib_memo[100];  // 备忘录数组，足够容纳 n≤80

// 初始化备忘录（将数组全部置为 -1）
void init_fib_memo() {
    memset(fib_memo, -1, sizeof(fib_memo));
}

long long fib(int n) {
    if (n <= 2) return 1;                        // 递归边界
    if (fib_memo[n] != -1) return fib_memo[n];   // 已计算过，直接返回
    // 计算并存入备忘录
    return fib_memo[n] = fib(n - 1) + fib(n - 2);
}

// ==========================================
// 3. 记忆化搜索 —— 爬楼梯问题
//    每次可以爬 1 级或 2 级台阶
//    f(1)=1, f(2)=2, f(n)=f(n-1)+f(n-2)
//    时间复杂度 O(n)，空间复杂度 O(n)
// ==========================================
long long climb_memo[100];  // 备忘录数组

// 初始化备忘录
void init_climb_memo() {
    memset(climb_memo, -1, sizeof(climb_memo));
}

long long climb(int n) {
    if (n == 1) return 1;                          // 1 级台阶：1 种方法（爬 1 级）
    if (n == 2) return 2;                          // 2 级台阶：2 种方法（1+1 或 2）
    if (climb_memo[n] != -1) return climb_memo[n]; // 已计算过，直接返回
    // 计算并存入备忘录
    return climb_memo[n] = climb(n - 1) + climb(n - 2);
}

// ==========================================
// 4. 例题1 完整解答 —— 斐波那契数列优化
//    输入 n，输出 F(n)，使用记忆化搜索
// ==========================================
void solve_problem1() {
    cout << "========== 例题1：斐波那契数列 ==========" << endl;
    cout << "请输入 n (1 ≤ n ≤ 80)：";
    int n;
    cin >> n;

    if (n < 1 || n > 80) {
        cout << "n 的取值范围为 1 ~ 80！" << endl;
        return;
    }

    init_fib_memo();
    cout << "F(" << n << ") = " << fib(n) << endl;
}

// ==========================================
// 5. 例题2 完整解答 —— 爬楼梯
//    输入 n，输出爬到第 n 级的方法数
// ==========================================
void solve_problem2() {
    cout << "========== 例题2：爬楼梯 ==========" << endl;
    cout << "请输入 n (1 ≤ n ≤ 70)：";
    int n;
    cin >> n;

    if (n < 1 || n > 70) {
        cout << "n 的取值范围为 1 ~ 70！" << endl;
        return;
    }

    init_climb_memo();
    cout << "爬到第 " << n << " 级有 " << climb(n) << " 种方法" << endl;
}

// ==========================================
// 6. 辅助函数 —— 对比测试
//    展示朴素递归与记忆化搜索的性能差异
// ==========================================
void performance_test() {
    cout << "========== 性能对比测试 ==========" << endl;
    cout << "测试 n = 40 时两种方法的速度差异：" << endl;

    // 朴素递归（n=40 时运行较慢，约需数秒）
    clock_t start = clock();
    long long result_naive = fib_naive(40);
    clock_t end = clock();
    double time_naive = double(end - start) / CLOCKS_PER_SEC;
    cout << "朴素递归: F(40) = " << result_naive
         << " | 耗时: " << time_naive << " 秒" << endl;

    // 记忆化搜索（瞬间完成）
    init_fib_memo();
    start = clock();
    long long result_memo = fib(40);
    end = clock();
    double time_memo = double(end - start) / CLOCKS_PER_SEC;
    cout << "记忆化搜索: F(40) = " << result_memo
         << " | 耗时: " << time_memo << " 秒" << endl;

    cout << "记忆化搜索快了约 "
         << (time_naive > 0 ? int(time_naive / time_memo) : 99999)
         << " 倍！" << endl;

    // 展示记忆化搜索可以轻松计算大 n
    cout << endl << "记忆化搜索可以轻松计算更大的 n：" << endl;
    init_fib_memo();
    init_climb_memo();
    int test_values[] = {50, 60, 70, 80};
    for (int i = 0; i < 4; i++) {
        int n = test_values[i];
        cout << "  F(" << n << ") = " << fib(n);
        cout << "  |  爬" << n << "级楼梯: " << climb(n) << " 种方法" << endl;
    }
}

// ==========================================
// 主函数 —— 测试与交互
// ==========================================
int main() {
    cout << "╔══════════════════════════════════════╗" << endl;
    cout << "║  第35课：动态规划入门——记忆化搜索  ║" << endl;
    cout << "╚══════════════════════════════════════╝" << endl;
    cout << endl;

    int choice;
    cout << "请选择功能：" << endl;
    cout << "  1 - 例题1：斐波那契数列" << endl;
    cout << "  2 - 例题2：爬楼梯" << endl;
    cout << "  3 - 性能对比测试" << endl;
    cout << "  4 - 全部运行" << endl;
    cout << "请输入 (1-4)：";
    cin >> choice;

    switch (choice) {
        case 1:
            solve_problem1();
            break;
        case 2:
            solve_problem2();
            break;
        case 3:
            performance_test();
            break;
        case 4:
            solve_problem1();
            cout << endl;
            solve_problem2();
            cout << endl;
            performance_test();
            break;
        default:
            cout << "无效选择！" << endl;
    }

    return 0;
}
