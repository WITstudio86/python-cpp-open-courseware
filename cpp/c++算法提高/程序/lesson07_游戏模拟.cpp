/*
 * ================================================================
 * C++算法提高 第07课：游戏模拟——规则驱动
 * ================================================================
 *
 * 算法知识点：
 *   - 环形结构的数组模拟：用取模运算 (pos+1)%n 实现循环
 *   - 约瑟夫环问题：模拟法 vs 递推公式法
 *   - 报数游戏模拟：状态追踪 + 条件判断
 *   - 淘汰/出列的处理：bool数组标记状态
 *   - 递推公式：f(i) = (f(i-1) + m) % i
 *
 * 经典例题：
 *   例题1 - 约瑟夫环：n个人数到m出列，输出出列顺序或求最后幸存者
 *   例题2 - 报数游戏：含7或7的倍数拍手，求第k次拍手的人
 *
 * 关键技巧：
 *   - 取模实现环形：(current % n) + 1 得到1~n的循环
 *   - 淘汰标记：bool eliminated[] 记录是否已出列
 *   - 只数未出列的人：if(!eliminated[pos]) count++
 */

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

// ================================================================
// 演示：取模运算实现环形遍历
// 这是理解约瑟夫环等环形游戏的关键基础
// ================================================================
void demoCircularArray() {
    cout << "══════════════════════════════════════" << endl;
    cout << "  环形遍历演示：取模运算" << endl;
    cout << "══════════════════════════════════════" << endl;

    int n = 8;  // 8个人围成一圈
    cout << n << " 个人围成一圈，遍历两圈（16步）：" << endl;

    cout << "方法1: pos = (pos % n) + 1;" << endl;
    int pos = 0;
    for (int i = 1; i <= 16; i++) {
        pos = (pos % n) + 1;
        cout << pos << " ";
        if (i == n) cout << "← 第一圈结束";
        cout << endl;
    }

    cout << "\n方法2: 直接用 i%n+1" << endl;
    for (int i = 0; i < 16; i++) {
        cout << (i % n) + 1 << " ";
        if ((i + 1) % n == 0) cout << "← 一圈结束";
        cout << endl;
    }
    cout << endl;
}

// ================================================================
// 例题1：约瑟夫环（Josephus Problem）
// 题目：n个人围成一圈，编号1~n。从1号开始报数1~m，
//       数到m的人出列。下一个人重新从1开始报。
//       输出：最后剩下的人的编号，以及全部出列顺序。
//
// 解法一：模拟法（直接模拟游戏过程）
//   用 bool eliminated[] 标记出列状态
//   循环报数，只数还在圈内的人
//
// 解法二：递推公式法（数学归纳）
//   f(1) = 0
//   f(i) = (f(i-1) + m) % i
//   答案 = f(n) + 1
// ================================================================
void solveJosephus() {
    cout << "══════════════════════════════════════" << endl;
    cout << "  例题1：约瑟夫环（Josephus Problem）" << endl;
    cout << "══════════════════════════════════════" << endl;

    int n, m;
    cout << "请输入人数 n: ";
    cin >> n;
    cout << "请输入报数上限 m: ";
    cin >> m;

    // ---- 解法一：模拟法（输出出列顺序） ----
    cout << "\n【解法一：模拟法】" << endl;
    cout << "出列顺序：";

    // eliminated[i] = true 表示 i 号已出列
    // 索引 1~n 使用，eliminated[0] 不用
    bool eliminated[1005] = {false};
    int remain = n;    // 剩余人数
    int pos = 0;       // 当前位置（下一个从1开始）

    while (remain > 0) {
        // 报数：需要跳过 m 个还没出列的人
        int cnt = 0;
        while (cnt < m) {
            pos = (pos % n) + 1;       // 环形移动到下一个人
            if (!eliminated[pos]) cnt++; // 只数还没出列的
        }

        // pos 位置的人出列
        eliminated[pos] = true;
        remain--;
        cout << pos;
        if (remain > 0) cout << " → ";
    }
    cout << endl;

    // ---- 解法一续：显示逐轮淘汰过程 ----
    cout << "\n是否显示逐轮淘汰过程？(1=是/0=否): ";
    int debug;
    cin >> debug;

    if (debug) {
        // 重置状态，重新模拟
        for (int i = 1; i <= n; i++) eliminated[i] = false;
        remain = n;
        pos = 0;

        cout << "\n--- 逐轮淘汰过程（n=" << n << ", m=" << m << "）---" << endl;

        // 显示初始圆圈
        cout << "初始圆圈: ";
        for (int i = 1; i <= n; i++) cout << setw(3) << i;
        cout << endl;

        int round = 0;
        while (remain > 0) {
            round++;
            int cnt = 0;
            while (cnt < m) {
                pos = (pos % n) + 1;
                if (!eliminated[pos]) cnt++;
            }
            eliminated[pos] = true;
            remain--;

            cout << "第" << setw(2) << round << "轮: ";
            cout << pos << "号出列 → 剩余: [";
            bool first = true;
            for (int i = 1; i <= n; i++) {
                if (!eliminated[i]) {
                    if (!first) cout << ", ";
                    cout << i;
                    first = false;
                }
            }
            cout << "] (" << remain << "人)" << endl;
        }
    }

    // ---- 解法二：递推公式法（只求最后幸存者） ----
    cout << "\n【解法二：递推公式法】" << endl;
    int survivor = 0;  // f(1) = 0
    for (int i = 2; i <= n; i++) {
        survivor = (survivor + m) % i;
    }
    cout << "最后幸存者编号 = f(" << n << ")+1 = "
         << survivor << "+1 = " << (survivor + 1) << endl;

    // 验证
    cout << "模拟法结果与递推法结果"
         << (survivor + 1 == pos ? "一致 ✓" : "不一致 ✗") << endl;

    // 解释递推公式
    cout << "\n递推公式推导（供进阶学习）：" << endl;
    cout << "  f(1) = 0" << endl;
    cout << "  f(i) = (f(i-1) + m) % i  （i=2,3,...,n）" << endl;
    cout << "  最终答案 = f(n) + 1" << endl;
    cout << "  含义：i个人时的幸存者位置 = (i-1个人时的幸存位置 + m) 对 i 取模" << endl;
    cout << endl;
}

// ================================================================
// 例题2：报数游戏（含7或7的倍数拍手）
// 题目：n个小朋友围成一圈，从1号开始从数字1开始报数。
//       当报到的数字包含数字7或是7的倍数时拍手。
//       问第k次拍手时是哪个小朋友？
//
// 模拟思路：
//   - 记录当前报到的数字 number
//   - 记录当前小朋友 person（环形移动）
//   - 判断是否需要拍手（needClap函数）
//   - 计数拍手次数，到第k次时停止
// ================================================================
bool needClap(int x) {
    // 判断数字x是否包含数字7或是7的倍数
    if (x % 7 == 0) return true;  // 7的倍数

    // 检查每一位是否包含数字7
    while (x > 0) {
        if (x % 10 == 7) return true;
        x /= 10;
    }
    return false;
}

void solveClappingGame() {
    cout << "══════════════════════════════════════" << endl;
    cout << "  例题2：报数游戏（含7或7的倍数拍手）" << endl;
    cout << "══════════════════════════════════════" << endl;

    int n, k;
    cout << "请输入小朋友人数 n: ";
    cin >> n;
    cout << "请输入第几次拍手 k: ";
    cin >> k;

    int person = 1;      // 当前报数的小朋友编号
    int number = 1;      // 当前报的数字
    int clapCount = 0;   // 已拍手次数

    // 显示前几次拍手的过程
    cout << "\n拍手记录（前10次）：" << endl;
    int shown = 0;

    while (clapCount < k) {
        if (needClap(number)) {
            clapCount++;
            if (clapCount <= 10) {
                cout << "第" << setw(3) << clapCount << "次拍手: ";
                cout << "小朋友" << setw(3) << person;
                cout << "，报到数字 " << setw(4) << number;
                // 说明原因
                cout << "（";
                if (number % 7 == 0)
                    cout << "7的倍数: " << number << " = 7×" << number/7;
                else
                    cout << "包含数字7";
                cout << "）" << endl;
                shown++;
            }
            if (clapCount == k) {
                cout << "\n===== 结果 =====" << endl;
                cout << "第 " << k << " 次拍手的是: " << person << " 号小朋友！" << endl;
                cout << "此时报到的数字是: " << number << endl;
                break;
            }
        }

        // 下一个小朋友（环形移动）
        person = person % n + 1;
        // 下一个数字
        number++;
    }

    // 验证：列出前30个需要拍手的数字
    cout << "\n前30个需要拍手的数字（验证用）：" << endl;
    int check = 0;
    for (int num = 1; check < 30; num++) {
        if (needClap(num)) {
            cout << num << " ";
            check++;
            if (check % 10 == 0) cout << endl;
        }
    }
    cout << endl << endl;
}

// ================================================================
// 附加演示：从约瑟夫环到递推公式的推导过程
// ================================================================
void demoJosephusDerivation() {
    cout << "══════════════════════════════════════" << endl;
    cout << "  附加：约瑟夫环递推公式推导" << endl;
    cout << "══════════════════════════════════════" << endl;

    int m = 3;
    cout << "以 m=" << m << " 为例，展示递推过程：" << endl;
    cout << endl;

    int f = 0;  // f(1) = 0
    cout << setw(8) << "n" << " | " << setw(15) << "f(n)" << " | " << "幸存者编号" << endl;
    cout << "---------+-----------------+-----------" << endl;

    for (int n = 1; n <= 10; n++) {
        if (n > 1) {
            f = (f + m) % n;
        }
        cout << setw(8) << n << " | "
             << "f(" << n << ")=" << setw(2) << f
             << "         | " << setw(3) << (f + 1) << "号" << endl;
    }
    cout << endl;
    cout << "解释：f(n) 表示编号从0开始的幸存者位置。" << endl;
    cout << "      实际编号从1开始，所以答案是 f(n)+1。" << endl;
    cout << endl;
}

// ================================================================
// 主函数
// ================================================================
int main() {
    cout << "╔══════════════════════════════════════════════╗" << endl;
    cout << "║   C++ 算法提高 —— 第07课：游戏模拟            ║" << endl;
    cout << "║   规则驱动 —— 环形结构 + 回合制模拟           ║" << endl;
    cout << "╚══════════════════════════════════════════════╝" << endl;
    cout << endl;

    // 环形遍历演示
    demoCircularArray();

    // 例题1：约瑟夫环
    solveJosephus();

    // 例题2：报数游戏
    solveClappingGame();

    // 附加：递推公式推导演示
    demoJosephusDerivation();

    cout << "══════════════════════════════════════" << endl;
    cout << "  本课小结" << endl;
    cout << "══════════════════════════════════════" << endl;
    cout << "1. 环形结构 = 取模运算：(pos % n) + 1" << endl;
    cout << "2. 约瑟夫环模拟法：bool数组 + 报数计数" << endl;
    cout << "3. 约瑟夫环递推法：f(i) = (f(i-1)+m) % i" << endl;
    cout << "4. 报数游戏：状态追踪 + 条件函数化" << endl;
    cout << "5. 游戏模拟核心：准确翻译规则为代码" << endl;
    cout << "══════════════════════════════════════" << endl;

    return 0;
}
