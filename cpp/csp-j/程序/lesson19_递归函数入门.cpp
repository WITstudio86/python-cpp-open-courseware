#include <iostream>
#include <cstring>
using namespace std;

// ==================== 1. 阶乘：带缩进跟踪的递归版本 ====================
// 辅助函数：打印指定深度的缩进
void printIndent(int depth) {
    for (int i = 0; i < depth; i++) {
        cout << "  ";  // 每层缩进 2 个空格
    }
}

// 带跟踪的递归阶乘函数
int factorialRecursive(int n, int depth) {
    printIndent(depth);
    cout << "开始计算 factorial(" << n << ")" << endl;

    // 递归边界：n 等于 0 或 1 时直接返回 1
    if (n == 0 || n == 1) {
        printIndent(depth);
        cout << "到达边界 factorial(" << n << ") = 1" << endl;
        return 1;
    }

    // 递归调用：n * factorialRecursive(n - 1)
    int subResult = factorialRecursive(n - 1, depth + 1);
    int result = n * subResult;

    printIndent(depth);
    cout << "factorial(" << n << ") = " << result << endl;

    return result;
}

// ==================== 2. 阶乘：迭代版本 ====================
int factorialIterative(int n) {
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

// ==================== 3. 斐波那契数列 ====================
// 3a. 普通递归版本（会重复计算，效率较低）
int fibRecursive(int n) {
    // 边界条件：fib(1) = 1, fib(2) = 1
    if (n == 1 || n == 2) {
        return 1;
    }
    return fibRecursive(n - 1) + fibRecursive(n - 2);
}

// 3b. 记忆化递归版本（用 memo 数组缓存已计算结果，避免重复计算）
int fibMemoHelper(int n, int memo[]) {
    // 边界条件
    if (n == 1 || n == 2) {
        return 1;
    }

    // 如果已经计算过，直接返回缓存的结果
    if (memo[n] != 0) {
        return memo[n];
    }

    // 未计算过，递归计算并存入缓存
    memo[n] = fibMemoHelper(n - 1, memo) + fibMemoHelper(n - 2, memo);
    return memo[n];
}

int fibMemoization(int n) {
    // memo 数组下标从 1 开始，长度设为 n + 1，全部初始化为 0
    int memo[100] = {0};
    return fibMemoHelper(n, memo);
}

// 3c. 迭代版本（用循环递推，效率最高）
int fibIterative(int n) {
    if (n == 1 || n == 2) {
        return 1;
    }

    int prev2 = 1;  // fib(1)
    int prev1 = 1;  // fib(2)
    int current = 0;

    for (int i = 3; i <= n; i++) {
        current = prev1 + prev2;  // 当前项 = 前两项之和
        prev2 = prev1;            // 向前移动
        prev1 = current;
    }

    return current;
}

// ==================== 4. 递归求和：1 + 2 + ... + n ====================
int sumRecursive(int n) {
    // 边界条件：n 为 1 时和就是 1
    if (n == 1) {
        return 1;
    }
    // 递归关系：sum(n) = n + sum(n-1)
    return n + sumRecursive(n - 1);
}

// ==================== 5. 递归求数字位数 ====================
int countDigits(int n) {
    // 确保处理负数
    if (n < 0) {
        n = -n;
    }
    // 边界条件：个位数只有 1 位
    if (n < 10) {
        return 1;
    }
    // 递归关系：位数 = 1 + countDigits(n / 10)
    return 1 + countDigits(n / 10);
}

// ==================== 6. 递归求幂：base^exp ====================
int powerRecursive(int base, int exp) {
    // 边界条件：任何数的 0 次方都是 1
    if (exp == 0) {
        return 1;
    }
    // 递归关系：base^exp = base * base^(exp-1)
    return base * powerRecursive(base, exp - 1);
}

// ==================== 主函数 ====================
int main() {
    // ========== 阶乘演示 ==========
    cout << "========== 阶乘演示：递归（带跟踪） ==========" << endl;
    int n = 5;
    int factResult = factorialRecursive(n, 0);
    cout << endl;

    cout << "========== 阶乘演示：迭代版本 ==========" << endl;
    for (int i = 1; i <= 8; i++) {
        cout << i << "! = " << factorialIterative(i) << endl;
    }
    cout << endl;

    // ========== 斐波那契数列演示 ==========
    cout << "========== 斐波那契数列演示 ==========" << endl;
    int fibN = 10;

    // 普通递归
    cout << "普通递归版：前 " << fibN << " 项 = ";
    for (int i = 1; i <= fibN; i++) {
        cout << fibRecursive(i);
        if (i < fibN) cout << ", ";
    }
    cout << endl;

    // 记忆化递归
    cout << "记忆化递归版：前 " << fibN << " 项 = ";
    for (int i = 1; i <= fibN; i++) {
        cout << fibMemoization(i);
        if (i < fibN) cout << ", ";
    }
    cout << endl;

    // 迭代版本
    cout << "迭代版：前 " << fibN << " 项 = ";
    for (int i = 1; i <= fibN; i++) {
        cout << fibIterative(i);
        if (i < fibN) cout << ", ";
    }
    cout << endl << endl;

    // ========== 递归求和演示 ==========
    cout << "========== 递归求和演示 ==========" << endl;
    int sumN = 10;
    cout << "1 + 2 + ... + " << sumN << " = " << sumRecursive(sumN) << endl;
    sumN = 100;
    cout << "1 + 2 + ... + " << sumN << " = " << sumRecursive(sumN) << endl;
    cout << endl;

    // ========== 递归求位数演示 ==========
    cout << "========== 递归求位数演示 ==========" << endl;
    int testNums[] = {5, 42, 100, 9999, 123456};
    int testCount = sizeof(testNums) / sizeof(testNums[0]);
    for (int i = 0; i < testCount; i++) {
        cout << testNums[i] << " 的位数 = " << countDigits(testNums[i]) << endl;
    }
    cout << endl;

    // ========== 递归求幂演示 ==========
    cout << "========== 递归求幂演示 ==========" << endl;
    int bases[] = {2, 3, 5, 10};
    int exps[]  = {0, 3, 4, 5};
    int powerCount = sizeof(bases) / sizeof(bases[0]);
    for (int i = 0; i < powerCount; i++) {
        cout << bases[i] << "^" << exps[i] << " = " << powerRecursive(bases[i], exps[i]) << endl;
    }
    cout << endl;

    // ========== 综合对比 ==========
    cout << "========== 递归 vs 迭代 综合对比 ==========" << endl;
    int compareN = 7;
    cout << "计算 fib(" << compareN << "):" << endl;
    cout << "  普通递归结果 = " << fibRecursive(compareN) << endl;
    cout << "  记忆化递归结果 = " << fibMemoization(compareN) << endl;
    cout << "  迭代结果 = " << fibIterative(compareN) << endl;
    cout << endl;

    cout << "计算 " << compareN << "! :" << endl;
    cout << "  递归结果 = " << factorialRecursive(compareN, 0) << endl;
    cout << "  迭代结果 = " << factorialIterative(compareN) << endl;

    return 0;
}
