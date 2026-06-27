/*
 * ============================================================
 * 课程：CSP-J 算法入门 — 第26课  枚举算法（下）
 *
 * 上一课学习了朴素的线性枚举（水仙花数、百钱百鸡、数字统计），
 * 本课进一步学习更复杂的枚举技巧：
 *   - 排列枚举（生成全排列）
 *   - 子集枚举（生成所有子集）
 *   - 回溯法解决组合约束问题（N皇后）
 *
 * 本课演示内容：
 *   1. next_permutation 生成全排列（数组 {1,2,3,4}）
 *   2. 手动递归实现全排列（swap 回溯法）
 *   3. 子集枚举：位运算方法（集合 {1,2,3} 的所有子集）
 *   4. N皇后问题（4皇后，棋盘格式输出所有方案）
 *
 * 学习目标：
 *   - 掌握 C++ STL 库函数 next_permutation 的使用
 *   - 理解递归回溯法生成排列的原理
 *   - 掌握位运算枚举子集的核心技巧
 *   - 理解回溯法在约束搜索中的应用
 * ============================================================
 */

#include <iostream>
#include <algorithm>   // next_permutation, sort
#include <vector>
#include <cmath>       // abs
#include <cstring>     // memset
using namespace std;

// ============================================================
// 演示 1：使用 C++ STL next_permutation 生成全排列
//
// next_permutation 是 C++ <algorithm> 中用于生成"下一个排列"的函数。
// 它会将序列重排为字典序中下一个更大的排列，如果已经是最大排列则返回 false。
//
// 使用方法：
//   1. 先将数组/容器排序（升序），得到字典序最小的排列。
//   2. 反复调用 next_permutation，每次生成下一个排列。
//   3. 直到 next_permutation 返回 false，说明已遍历所有排列。
//
// 对于 n 个不同元素的全排列，共有 n! 种。
// 例如 {1,2,3,4} 共有 4! = 24 种排列。
// ============================================================

/**
 * @brief 使用 next_permutation 生成全排列
 *
 * 演示对数组 {1, 2, 3, 4} 生成所有排列，
 * 输出格式：序号 + 排列内容。
 */
void demoNextPermutation() {
    cout << "【演示1】使用 next_permutation 生成全排列：" << endl;
    cout << "  元素集合: {1, 2, 3, 4}" << endl;
    cout << "  全排列共 4! = 24 种：" << endl;
    cout << endl;

    int arr[] = {1, 2, 3, 4};   // 原始数组
    int n = 4;                   // 数组长度
    int count = 0;               // 排列计数器

    // 重要：必须先排序！next_permutation 按字典序生成下一个排列，
    // 如果数组未排序，会"跳过"前面那些比当前排列更小的排列。
    sort(arr, arr + n);

    do {
        // 输出当前排列
        cout << "  No." << (++count) << ":  {";
        for (int i = 0; i < n; i++) {
            cout << arr[i];
            if (i < n - 1) cout << ", ";
        }
        cout << "}" << endl;
    } while (next_permutation(arr, arr + n));
    // next_permutation 返回 true 表示成功生成下一个排列；
    // 返回 false 表示已经是字典序最大的排列，遍历结束。

    cout << "  共生成 " << count << " 种排列。" << endl;
    cout << endl;
}

// ============================================================
// 演示 2：手动递归实现全排列（swap 回溯法）
//
// 核心思想：固定第 pos 个位置，枚举每一个可以做该位置元素的候选。
//
// 算法步骤（以数组 {1,2,3,4} 为例）：
//   1. 从位置 pos=0 开始，i 从 pos 遍历到 n-1。
//   2. 交换 arr[pos] 与 arr[i]，相当于让 arr[i] 成为第 pos 位的元素。
//   3. 递归处理 pos+1（下一位）。
//   4. 回溯：再交换回来（恢复原状），尝试下一个 i。
//   5. 当 pos == n 时，得到一个完整排列，输出。
//
// 这种方法的优点是不需要额外数组存储已使用标记，
// 通过在原数组上 swap 来复用空间。
// ============================================================

// 全局变量：存储当前排列（swap 回溯法直接在原数组上操作）
int permArr[10];  // 最多支持 n=10 的全排列

/**
 * @brief 递归回溯生成全排列（swap 法）
 *
 * 参数说明：
 *   pos  当前正在确定的位置下标（0-based）
 *   n    数组总长度
 *
 * 递归终止条件：pos == n 时，arr[0..n-1] 即为一个完整排列，输出之。
 *
 * @param pos  当前处理位置
 * @param n    数组长度
 * @param count  引用，累计已生成的排列数
 */
void permute(int pos, int n, int &count) {
    if (pos == n) {
        // 递归基：已填满所有位置，输出当前排列
        cout << "  No." << (++count) << ":  {";
        for (int i = 0; i < n; i++) {
            cout << permArr[i];
            if (i < n - 1) cout << ", ";
        }
        cout << "}" << endl;
        return;
    }

    // 枚举第 pos 位可以放谁：候选范围是 pos 到 n-1
    for (int i = pos; i < n; i++) {
        swap(permArr[pos], permArr[i]);  // 选 arr[i] 放在第 pos 位
        permute(pos + 1, n, count);      // 递归处理下一位
        swap(permArr[pos], permArr[i]);  // 回溯：恢复原状
        // 回溯是关键！不恢复的话，兄弟分支会拿到被修改过的数组。
    }
}

/**
 * @brief 演示手动递归全排列
 */
void demoRecursivePermutation() {
    cout << "【演示2】手动递归实现全排列（swap 回溯法）：" << endl;
    cout << "  元素集合: {1, 2, 3, 4}" << endl;
    cout << "  算法：固定第 pos 位 → 枚举候选 → 递归 → 回溯" << endl;
    cout << endl;

    int n = 4;
    // 初始化数组
    for (int i = 0; i < n; i++) {
        permArr[i] = i + 1;  // {1, 2, 3, 4}
    }

    int count = 0;  // 排列计数器
    permute(0, n, count);

    cout << "  共生成 " << count << " 种排列。" << endl;
    cout << endl;
}

// ============================================================
// 演示 3：子集枚举 — 位运算方法
//
// 对于一个包含 n 个元素的集合，其子集总数为 2^n。
// 每个子集可以用一个 n 位的二进制数表示：
//   第 i 位（从右数，0-based）为 1 → 元素 i 在子集中
//   第 i 位为 0                      → 元素 i 不在子集中
//
// 例如 n=3, 集合 {1, 2, 3}：
//   mask = 0 (二进制 000) → 空集 {}
//   mask = 1 (二进制 001) → {1}
//   mask = 2 (二进制 010) → {2}
//   mask = 3 (二进制 011) → {1, 2}
//   mask = 4 (二进制 100) → {3}
//   ...
//   mask = 7 (二进制 111) → {1, 2, 3}
//
// 核心操作：
//   mask & (1 << i)  → 判断第 i 位是否为 1
// ============================================================

/**
 * @brief 使用位运算枚举集合的所有子集
 *
 * 算法：mask 从 0 枚举到 (1 << n) - 1（即 0 ~ 2^n - 1），
 * 对于每个 mask，检查其每一位是否为 1，
 * 若第 i 位为 1 则输出元素 i（假设元素从 0 编号）。
 *
 * 时间复杂度：O(2^n * n)，对于 n <= 20 的集合可行。
 */
void demoSubsetEnumeration() {
    cout << "【演示3】子集枚举（位运算方法）：" << endl;
    cout << "  原始集合: {1, 2, 3}" << endl;
    cout << "  子集总数: 2^3 = 8" << endl;
    cout << endl;

    int elements[] = {1, 2, 3};  // 原始集合的元素
    int n = 3;                    // 元素个数
    int totalSubsets = 1 << n;    // 2^n，即子集总数

    for (int mask = 0; mask < totalSubsets; mask++) {
        // 输出当前子集
        cout << "  mask=" << mask << " (二进制 ";
        // 打印 mask 的二进制表示（n 位）
        for (int i = n - 1; i >= 0; i--) {
            cout << ((mask >> i) & 1);
        }
        cout << ") → 子集: {";

        bool first = true;  // 用于控制逗号输出
        for (int i = 0; i < n; i++) {
            // 判断 mask 的第 i 位是否为 1
            if (mask & (1 << i)) {
                if (!first) cout << ", ";
                cout << elements[i];
                first = false;
            }
        }
        cout << "}" << endl;
    }

    cout << "  共 " << totalSubsets << " 个子集。" << endl;
    cout << endl;
}

// ============================================================
// 演示 4：N皇后问题（4皇后）
//
// 问题描述：在 N×N 的棋盘上放置 N 个皇后，
// 使得任意两个皇后都不在同一行、同一列或同一对角线上。
// 求所有合法放置方案。
//
// 由于每行必须且只能放一个皇后，
// 可以用一维数组 col[i] 表示第 i 行皇后所在的列号（0-based）。
// 问题转化为：找到 col[0..N-1] 的一个排列，满足对角线约束。
//
// 对角线约束（两个皇后 (r1,c1) 和 (r2,c2)）：
//   不在同一对角线上 ⇔ |r1 - r2| != |c1 - c2|
//   （同一条对角线上的两个格子，行差等于列差）
//
// 本演示用回溯法求解 4 皇后，展示所有 2 组解。
// ============================================================

const int MAX_N = 20;       // 棋盘最大尺寸
int queenCol[MAX_N];        // queenCol[row] = 第 row 行皇后所在的列号
int solutionCountQ = 0;     // 解的数量
int boardSize = 4;          // 棋盘大小（4皇后）

/**
 * @brief 检查在 (row, col) 位置放置皇后是否与之前已放置的皇后冲突
 *
 * 逐一检查第 0 行到第 row-1 行的皇后，
 * 判断是否在同一列或同一对角线上。
 *
 * 注意：因为我们按行逐行放置，所以不需要检查"同一行"。
 *
 * @param row  当前要放置的行
 * @param col  当前要放置的列
 * @return     true 如果不冲突（可以放置），false 如果冲突
 */
bool isSafe(int row, int col) {
    for (int r = 0; r < row; r++) {
        int c = queenCol[r];  // 已放置皇后 r 的列号

        // 同一列冲突：列号相同
        if (c == col) return false;

        // 同一对角线冲突：行差 == 列差
        // 对角线有两种方向：
        //   左上→右下：row - r == col - c  → (row - r) == (col - c)
        //   右上→左下：row - r == c - col  → (row - r) == -(col - c)
        // 统一为：abs(row - r) == abs(col - c)
        if (abs(row - r) == abs(col - c)) return false;
    }
    return true;  // 没有冲突
}

/**
 * @brief 打印棋盘
 *
 * Q 表示皇后，. 表示空格。
 *
 * @param n  棋盘大小
 */
void printBoard(int n) {
    for (int r = 0; r < n; r++) {
        cout << "    ";                          // 缩进对齐
        for (int c = 0; c < n; c++) {
            if (queenCol[r] == c) {
                cout << "Q ";                   // 该格有皇后
            } else {
                cout << ". ";                   // 空格
            }
        }
        cout << endl;
    }
}

/**
 * @brief 回溯法求解 N 皇后
 *
 * 递归在每一行尝试放置一个皇后：
 *   1. 对第 row 行的每一列 col（0 ~ n-1），
 *   2. 检查 (row, col) 是否安全（不冲突），
 *   3. 如果安全：放置 → 递归处理下一行 → 回溯（不需要显式恢复，
 *      因为 queenCol[row] 会被下一次循环覆盖）。
 *   4. 当 row == n 时，所有行都已放置完毕，找到一个解。
 *
 * @param row  当前正在处理的行号（0-based）
 * @param n    棋盘大小
 */
void solveNQueens(int row, int n) {
    if (row == n) {
        // 递归基：n 个皇后全部放置完毕
        cout << "  --- 方案 " << (++solutionCountQ) << " ---" << endl;
        printBoard(n);                       // 打印棋盘
        cout << endl;
        return;
    }

    // 尝试在当前行的每一列放置皇后
    for (int col = 0; col < n; col++) {
        if (isSafe(row, col)) {              // 检查是否安全
            queenCol[row] = col;             // 放置皇后
            solveNQueens(row + 1, n);        // 递归处理下一行
            // 回溯：不需要显式清除 queenCol[row]，
            // 因为下一次循环会覆盖它。
            // 这里不需要额外操作。
        }
    }
}

/**
 * @brief 演示 N皇后问题
 */
void demoNQueens() {
    cout << "【演示4】N皇后问题（4皇后）：" << endl;
    cout << "  在 4×4 棋盘上放置 4 个互不攻击的皇后" << endl;
    cout << "  约束：不同行、不同列、不同对角线" << endl;
    cout << endl;

    solutionCountQ = 0;
    solveNQueens(0, boardSize);

    cout << "  共找到 " << solutionCountQ << " 组解。" << endl;
    // 已知4皇后有2组解：(1,3,0,2) 和 (2,0,3,1)
    cout << "  （4皇后共有 2 组本质不同的解）" << endl;
    cout << endl;
}

// ============================================================
// 主函数：依次运行四个演示
// ============================================================
int main() {
    cout << "========================================" << endl;
    cout << "  第26课：枚举算法（下）— 演示程序" << endl;
    cout << "========================================" << endl;
    cout << endl;

    // 演示 1：next_permutation
    demoNextPermutation();

    // 演示 2：手动递归全排列
    demoRecursivePermutation();

    // 演示 3：子集枚举（位运算）
    demoSubsetEnumeration();

    // 演示 4：N皇后问题
    demoNQueens();

    cout << "========================================" << endl;
    cout << "  所有演示完成！" << endl;
    cout << "========================================" << endl;

    return 0;
}
