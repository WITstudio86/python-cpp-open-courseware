/*
 * ============================================================
 * 第45课：算法综合实战（一）—— 枚举+贪心+二分
 * lesson45_comprehensive1.cpp
 *
 * 包含两道综合题目的完整实现：
 *   1. 切割绳子问题 —— 二分答案 + 贪心验证
 *   2. 最优配对问题   —— 排序 + 贪心配对
 *
 * 适用对象：具备基础C++知识的中小学生
 * ============================================================
 */

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

// ============================================================
// 第一部分：切割绳子问题（二分答案 + 贪心验证）
// 题目：有N条绳子，需要切成K段等长的绳子，求每段的最大长度
// ============================================================

const int MAXN = 10005;      // 最大绳子数量
const double EPS = 1e-5;     // 二分精度（保留两位小数需要更小的精度）
double len[MAXN];             // 存储每条绳子的长度
int N, K;                     // N条绳子，需要K段

/*
 * check函数 —— 贪心验证
 * 功能：判断是否能切出至少K段长度为x的绳子
 * 参数：x - 当前尝试的每段长度
 * 返回：true表示可以切出≥K段，false表示不能
 *
 * 贪心策略：对于每条绳子，尽可能多地切割出长度为x的段
 * 每条绳子能切的段数 = floor(绳子长度 / x)
 */
bool check(double x) {
    int cnt = 0;                     // 计数器：总共能切出多少段
    for (int i = 0; i < N; i++) {
        cnt += (int)(len[i] / x);    // 第i条绳子能切出的段数
    }
    return cnt >= K;                 // 是否满足K段的要求
}

/*
 * 切割绳子——主求解函数
 * 使用二分答案的方法搜索最大可行长度
 *
 * 二分策略：
 * - 如果check(mid)为true，说明mid可行，尝试更大的值 → left = mid
 * - 如果check(mid)为false，说明mid太大，需要减小 → right = mid
 * - 当right-left < EPS时停止，left即为答案
 */
double solveCutRope() {
    // 确定二分上下界
    double left = 0.0;               // 最小可能长度
    double right = 0.0;              // 最大可能长度（最长的绳子）
    for (int i = 0; i < N; i++) {
        if (len[i] > right) right = len[i];
    }

    // 二分搜索
    while (right - left > EPS) {
        double mid = (left + right) / 2.0;
        if (check(mid)) {
            left = mid;              // mid可行 → 尝试更长的
        } else {
            right = mid;             // mid不可行 → 缩短
        }
    }

    return left;                     // 返回最大可行长度
}

/*
 * 切割绳子问题的测试示例
 */
void demoCutRope() {
    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║      例题1：切割绳子问题                  ║" << endl;
    cout << "║      算法：二分答案 + 贪心验证            ║" << endl;
    cout << "╚══════════════════════════════════════════╝" << endl;
    cout << endl;

    // 样例测试
    N = 4; K = 11;
    len[0] = 8.02;
    len[1] = 7.43;
    len[2] = 4.57;
    len[3] = 5.39;

    cout << "【样例输入】" << endl;
    cout << N << " " << K << endl;
    for (int i = 0; i < N; i++) {
        cout << len[i] << " ";
    }
    cout << endl << endl;

    double ans = solveCutRope();

    cout << "【样例输出】" << endl;
    printf("%.2f\n", ans);
    cout << endl;

    cout << "【算法分析】" << endl;
    cout << "  - 二分搜索范围：[0, " << len[3] << "]" << endl;
    cout << "  - 每次check遍历N条绳子，计算可切段数" << endl;
    cout << "  - 时间复杂度：O(N × log(范围/精度))" << endl;
    cout << "  - 精度要求：保留两位小数，EPS设为1e-5" << endl;
    cout << endl;
}

// ============================================================
// 第二部分：最优配对问题（排序 + 贪心）
// 题目：有2N个数，两两配对，使每对差的绝对值之和最小
// ============================================================

const int MAXM = 2005;         // 最多2N个数
int arr[MAXM];                 // 存储所有数

/*
 * 最优配对——主求解函数
 * 贪心策略：将数组排序后，相邻的两个数配对
 *
 * 为什么正确？
 * 假设四个数 a ≤ b ≤ c ≤ d
 * 配对方案1（相邻配对）：|b-a| + |d-c| = (b-a) + (d-c)
 * 配对方案2（交叉配对）：|c-a| + |d-b| = (c-a) + (d-b)
 * 方案1-方案2 = (b-a+d-c) - (c-a+d-b) = 2b-2c ≤ 0（因为b≤c）
 * 所以方案1 ≤ 方案2，相邻配对是最优的
 */
long long solveOptimalPair(int m) {
    // 第一步：排序（让数据有序化，便于贪心）
    sort(arr, arr + m);

    // 第二步：贪心配对——相邻两数配对
    long long ans = 0;
    for (int i = 0; i < m; i += 2) {
        ans += (arr[i + 1] - arr[i]);   // 第i和第i+1个数配对
    }

    return ans;
}

/*
 * 最优配对问题的测试示例
 */
void demoOptimalPair() {
    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║      例题2：最优配对问题                  ║" << endl;
    cout << "║      算法：排序 + 贪心配对                ║" << endl;
    cout << "╚══════════════════════════════════════════╝" << endl;
    cout << endl;

    // 样例1测试
    int m = 6;
    arr[0] = 1;
    arr[1] = 3;
    arr[2] = 4;
    arr[3] = 6;
    arr[4] = 7;
    arr[5] = 9;

    cout << "【样例1输入】" << endl;
    cout << m / 2 << endl;
    for (int i = 0; i < m; i++) {
        cout << arr[i] << " ";
    }
    cout << endl << endl;

    long long ans1 = solveOptimalPair(m);

    cout << "【样例1输出】" << endl;
    cout << ans1 << endl;
    cout << "  配对方案：(" << arr[0] << "," << arr[1] << ") ";
    for (int i = 2; i < m; i += 2) {
        cout << "(" << arr[i] << "," << arr[i+1] << ") ";
    }
    cout << endl << endl;

    // 样例2测试（手动输入演示）
    cout << "【样例2】n=2, 数字: 10 20 30 40" << endl;
    m = 4;
    arr[0] = 10; arr[1] = 20; arr[2] = 30; arr[3] = 40;
    long long ans2 = solveOptimalPair(m);
    cout << "  最小差值之和：" << ans2 << endl;
    cout << "  配对方案：(10,20) (30,40)，差值=10+10=20" << endl;
    cout << endl;

    // 样例3测试（含重复数字）
    cout << "【样例3】n=2, 数字: 5 5 5 5" << endl;
    m = 4;
    arr[0] = 5; arr[1] = 5; arr[2] = 5; arr[3] = 5;
    long long ans3 = solveOptimalPair(m);
    cout << "  最小差值之和：" << ans3 << "（所有数字相同，差值为0）" << endl;
    cout << endl;

    cout << "【算法分析】" << endl;
    cout << "  - 排序时间：O(M log M)，M = 2N" << endl;
    cout << "  - 贪心配对：O(M)" << endl;
    cout << "  - 总时间复杂度：O(N log N)" << endl;
    cout << "  - 空间复杂度：O(N)" << endl;
    cout << endl;
}

// ============================================================
// 第三部分：交互式菜单
// ============================================================

/*
 * 打印程序主菜单
 */
void printMenu() {
    cout << endl;
    cout << "┌──────────────────────────────────────────────┐" << endl;
    cout << "│       第45课：算法综合实战（一）             │" << endl;
    cout << "│       枚举 + 贪心 + 二分                     │" << endl;
    cout << "├──────────────────────────────────────────────┤" << endl;
    cout << "│  1. 例题1：切割绳子（二分答案+贪心验证）     │" << endl;
    cout << "│  2. 例题2：最优配对（排序+贪心配对）         │" << endl;
    cout << "│  3. 运行全部例题                              │" << endl;
    cout << "│  0. 退出程序                                  │" << endl;
    cout << "└──────────────────────────────────────────────┘" << endl;
    cout << "请输入你的选择（0-3）：";
}

/*
 * 主函数
 */
int main() {
    int choice;

    do {
        printMenu();
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1:
                demoCutRope();
                break;
            case 2:
                demoOptimalPair();
                break;
            case 3:
                demoCutRope();
                cout << "\n" << string(50, '=') << "\n" << endl;
                demoOptimalPair();
                break;
            case 0:
                cout << "感谢学习！期待在下一课与你相见~" << endl;
                break;
            default:
                cout << "输入有误，请重新输入（0-3）！" << endl;
        }
    } while (choice != 0);

    return 0;
}
