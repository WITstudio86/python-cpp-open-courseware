/**
 * 第17课：函数的定义与调用 —— 完整演示程序
 *
 * 本程序展示了 C++ 函数的核心概念：
 * 1. 函数声明（原型）与定义的分离
 * 2. 多种返回类型的函数（int, bool, long long, void）
 * 3. 函数的嵌套调用
 * 4. main 函数作为程序入口
 *
 * 包含函数：add, max2, max3, isPrime, isPerfect, sumOfDigits,
 *          reverseNumber, isPalindrome, factorial, printLine, printArray
 */

#include <iostream>
using namespace std;

// ==================== 函数声明（原型） ====================

// 基础数学运算
int add(int a, int b);
int max2(int a, int b);
int max3(int a, int b, int c);

// 数论相关
bool isPrime(int n);
bool isPerfect(int n);

// 数字操作
int sumOfDigits(int n);
int reverseNumber(int n);
bool isPalindrome(int n);

// 计算与输出
long long factorial(int n);
void printLine(char ch, int len);
void printArray(int arr[], int n);

// ==================== 主函数 ====================

int main() {
    // 设置输出格式
    cout << "========================================" << endl;
    cout << "  第17课：函数的定义与调用 —— 演示程序" << endl;
    cout << "========================================" << endl;

    // ---------- 1. 基础数学运算 ----------
    cout << "\n【1. 基础数学运算】" << endl;
    cout << "add(25, 17) = " << add(25, 17) << endl;
    cout << "max2(88, 63) = " << max2(88, 63) << endl;
    cout << "max3(15, 42, 38) = " << max3(15, 42, 38) << endl;

    // ---------- 2. 数论函数 ----------
    cout << "\n【2. 数论函数 —— 素数判断】" << endl;
    int testNums[] = {1, 2, 7, 15, 97, 100};
    for (int i = 0; i < 6; i++) {
        int num = testNums[i];
        cout << num << (isPrime(num) ? " 是素数" : " 不是素数") << endl;
    }

    cout << "\n【3. 数论函数 —— 完美数判断】" << endl;
    // 已知的完美数：6, 28, 496, 8128
    int perfectTest[] = {6, 10, 28, 100, 496};
    for (int i = 0; i < 5; i++) {
        int num = perfectTest[i];
        cout << num << (isPerfect(num) ? " 是完美数" : " 不是完美数") << endl;
    }

    // ---------- 4. 数字操作 ----------
    cout << "\n【4. 数字操作】" << endl;
    int digitalNum = 12321;
    cout << "测试数字: " << digitalNum << endl;
    cout << "  各位数字之和: " << sumOfDigits(digitalNum) << endl;
    cout << "  反转后的数字: " << reverseNumber(digitalNum) << endl;
    cout << "  是否回文数: " << (isPalindrome(digitalNum) ? "是" : "否") << endl;

    int digitalNum2 = 9876;
    cout << "\n测试数字: " << digitalNum2 << endl;
    cout << "  各位数字之和: " << sumOfDigits(digitalNum2) << endl;
    cout << "  反转后的数字: " << reverseNumber(digitalNum2) << endl;
    cout << "  是否回文数: " << (isPalindrome(digitalNum2) ? "是" : "否") << endl;

    // ---------- 5. 阶乘计算 ----------
    cout << "\n【5. 阶乘计算】" << endl;
    for (int i = 0; i <= 10; i++) {
        cout << i << "! = " << factorial(i) << endl;
    }

    // ---------- 6. 输出辅助函数 ----------
    cout << "\n【6. 输出辅助函数】" << endl;

    cout << "printLine('-', 40) 效果：" << endl;
    printLine('-', 40);

    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6};
    cout << "printArray 效果：" << endl;
    printArray(arr, 8);

    // ---------- 7. 嵌套调用示例 ----------
    cout << "\n【7. 函数嵌套调用示例】" << endl;
    cout << "max3(100, max2(50, 80), 60) = "
         << max3(100, max2(50, 80), 60) << endl;
    cout << "isPalindrome(reverseNumber(12321)) 恒为 true，结果: "
         << (isPalindrome(reverseNumber(12321)) ? "true" : "false") << endl;

    cout << "\n========================================" << endl;
    cout << "          演示程序运行完毕" << endl;
    cout << "========================================" << endl;

    return 0;
}

// ==================== 函数定义 ====================

// ---------- 基础数学运算 ----------

int add(int a, int b) {
    return a + b;
}

int max2(int a, int b) {
    return a > b ? a : b;
}

int max3(int a, int b, int c) {
    // 嵌套调用 max2 来实现三个数的最大值
    return max2(max2(a, b), c);
}

// ---------- 数论相关 ----------

bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

bool isPerfect(int n) {
    if (n <= 1) return false;
    int sum = 0;
    // 找出 n 的所有真因子（小于 n 的正因子）并求和
    for (int i = 1; i <= n / 2; i++) {
        if (n % i == 0) {
            sum += i;
        }
    }
    return sum == n;
}

// ---------- 数字操作 ----------

int sumOfDigits(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;   // 取出最后一位
        n /= 10;         // 去掉最后一位
    }
    return sum;
}

int reverseNumber(int n) {
    int rev = 0;
    while (n > 0) {
        rev = rev * 10 + n % 10;
        n /= 10;
    }
    return rev;
}

bool isPalindrome(int n) {
    // 回文数的定义：正读反读都一样，即 n == reverseNumber(n)
    return n == reverseNumber(n);
}

// ---------- 计算与输出 ----------

long long factorial(int n) {
    long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

void printLine(char ch, int len) {
    for (int i = 0; i < len; i++) {
        cout << ch;
    }
    cout << endl;
}

void printArray(int arr[], int n) {
    cout << "[";
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "]" << endl;
}
