/*
 * CSP-J 备考课程 — 第36课：数论基础
 *
 * 本文件包含以下完整实现：
 *   1. 质数判断 — 试除法（O(√n)）
 *   2. 埃拉托斯特尼筛法（O(n log log n)）
 *   3. 线性筛法 / 欧拉筛（O(n)）
 *   4. 最大公约数 GCD（辗转相除法 + 递归/迭代两种写法）
 *   5. 最小公倍数 LCM（先除后乘防溢出）
 *   6. 快速幂（迭代版 + 递归版）
 *   7. 求一个数的所有约数
 *
 * 运行方式：
 *   g++ -std=c++17 -O2 lesson36_数论基础.cpp -o lesson36 && ./lesson36
 *   按照交互提示选择对应功能进行测试
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

// ============================================================
// 1. 试除法判断质数
//    时间复杂度：O(√n)
//    优化：先排除 ≤1 和偶数，然后只检查奇数
//    注意：i * i 可能溢出，使用 long long 的 i
// ============================================================
void demo_is_prime() {
    cout << "\n========== 1. 试除法判断质数 ==========\n";
    cout << "输入一个正整数 n，判断是否为质数：\n> ";

    long long n;
    cin >> n;

    bool isPrime;
    if (n < 2) {
        isPrime = false;
    } else if (n == 2) {
        isPrime = true;
    } else if (n % 2 == 0) {
        isPrime = false;
    } else {
        isPrime = true;
        // 使用 long long i 防止 i*i 溢出
        for (long long i = 3; i * i <= n; i += 2) {
            if (n % i == 0) {
                isPrime = false;
                cout << "  发现因子: " << i << " × " << n / i << " = " << n << endl;
                break;
            }
        }
    }

    cout << n << (isPrime ? " 是质数" : " 不是质数") << endl;
}

// ============================================================
// 2. 埃拉托斯特尼筛法
//    时间复杂度：O(n log log n)
//    空间复杂度：O(n)
//    核心优化：内层循环从 i*i 开始
// ============================================================
void demo_eratosthenes() {
    cout << "\n========== 2. 埃氏筛法 ==========\n";
    cout << "输入 n，输出 1~n 以内的所有质数：\n> ";

    int n;
    cin >> n;

    if (n < 2) {
        cout << "1~" << n << " 范围内没有质数。" << endl;
        return;
    }

    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;

    // 埃氏筛核心
    for (int i = 2; (long long)i * i <= n; i++) {
        if (isPrime[i]) {
            // 从 i*i 开始标记，因为 2i, 3i, ..., (i-1)*i 已被之前的质数筛过
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }

    // 收集质数
    vector<int> primes;
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }

    cout << "1~" << n << " 内共有 " << primes.size() << " 个质数。" << endl;
    cout << "质数列表: ";
    for (int p : primes) {
        cout << p << " ";
    }
    cout << endl;
}

// ============================================================
// 3. 线性筛法（欧拉筛）
//    时间复杂度：O(n) — 每个合数只被其最小质因子筛一次
//    核心：if (i % primes[j] == 0) break;
// ============================================================
void demo_linear_sieve() {
    cout << "\n========== 3. 线性筛法（欧拉筛） ==========\n";
    cout << "输入 n，输出 1~n 以内的所有质数：\n> ";

    int n;
    cin >> n;

    if (n < 2) {
        cout << "1~" << n << " 范围内没有质数。" << endl;
        return;
    }

    vector<bool> isPrime(n + 1, true);
    vector<int> primes;
    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
        // 用当前质数筛掉一批合数
        for (int p : primes) {
            if ((long long)i * p > n) break;
            isPrime[i * p] = false;
            // 关键行：p 是 i 的最小质因子时停止
            // 保证每个合数只被其最小质因子筛一次
            if (i % p == 0) break;
        }
    }

    cout << "1~" << n << " 内共有 " << primes.size() << " 个质数。" << endl;
    cout << "质数列表: ";
    for (int p : primes) {
        cout << p << " ";
    }
    cout << endl;
}

// ============================================================
// 4. 最大公约数 GCD
//    辗转相除法（欧几里得算法）：gcd(a, b) = gcd(b, a % b)
//    时间复杂度：O(log min(a, b))
//    提供递归（简洁）和迭代（无递归栈开销）两种写法
// ============================================================

// 递归版 GCD
long long gcd_recursive(long long a, long long b) {
    return b == 0 ? a : gcd_recursive(b, a % b);
}

// 迭代版 GCD
long long gcd_iterative(long long a, long long b) {
    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

void demo_gcd() {
    cout << "\n========== 4. 最大公约数 GCD ==========\n";
    cout << "输入两个正整数 a 和 b：\n> ";

    long long a, b;
    cin >> a >> b;

    long long g1 = gcd_recursive(a, b);
    long long g2 = gcd_iterative(a, b);

    cout << "递归版 GCD(" << a << ", " << b << ") = " << g1 << endl;
    cout << "迭代版 GCD(" << a << ", " << b << ") = " << g2 << endl;

    // 验证一致性
    if (g1 == g2) {
        cout << "（两种实现结果一致）" << endl;
    }
}

// ============================================================
// 5. 最小公倍数 LCM
//    lcm(a, b) = a / gcd(a, b) * b
//    注意：必须“先除后乘”，否则 a*b 可能溢出
// ============================================================
void demo_lcm() {
    cout << "\n========== 5. 最小公倍数 LCM ==========\n";
    cout << "输入两个正整数 a 和 b：\n> ";

    long long a, b;
    cin >> a >> b;

    long long g = gcd_recursive(a, b);
    // 先除后乘，防止溢出
    long long l = a / g * b;

    cout << "GCD(" << a << ", " << b << ") = " << g << endl;
    cout << "LCM(" << a << ", " << b << ") = " << l << endl;
    cout << "验证: a × b = " << a * b << ", GCD × LCM = " << g * l << endl;
}

// ============================================================
// 6. 快速幂（二分思想）
//    计算 a^b mod m，时间复杂度 O(log b)
//    提供迭代版（最常用）和递归版两种写法
// ============================================================

// 快速幂 — 迭代版
long long quick_pow_iter(long long a, long long b, long long mod) {
    long long res = 1;
    a %= mod;
    while (b > 0) {
        if (b & 1) {          // b 的当前二进制位为 1
            res = res * a % mod;
        }
        a = a * a % mod;      // a = a^2, a^4, a^8, ...
        b >>= 1;              // b 右移一位
    }
    return res;
}

// 快速幂 — 递归版
long long quick_pow_rec(long long a, long long b, long long mod) {
    if (b == 0) return 1;
    long long half = quick_pow_rec(a, b / 2, mod);
    half = half * half % mod;
    if (b % 2 == 1) {
        half = half * a % mod;
    }
    return half;
}

void demo_quick_pow() {
    cout << "\n========== 6. 快速幂 ==========\n";
    cout << "计算 a^b mod m\n";
    cout << "输入 a b m（空格分隔）：\n> ";

    long long a, b, m;
    cin >> a >> b >> m;

    long long r1 = quick_pow_iter(a, b, m);
    long long r2 = quick_pow_rec(a, b, m);

    cout << "迭代版: " << a << "^" << b << " mod " << m << " = " << r1 << endl;
    cout << "递归版: " << a << "^" << b << " mod " << m << " = " << r2 << endl;

    if (r1 == r2) {
        cout << "（两种实现结果一致）" << endl;
    }

    // 额外演示：取模 1e9+7 的快速幂
    cout << "\n使用 MOD = 1e9+7 的示例：" << endl;
    const long long MOD7 = 1000000007;
    cout << "2^10 mod 1e9+7 = " << quick_pow_iter(2, 10, MOD7) << endl;
    cout << "3^20 mod 1e9+7 = " << quick_pow_iter(3, 20, MOD7) << endl;
    cout << "5^100 mod 1e9+7 = " << quick_pow_iter(5, 100, MOD7) << endl;
}

// ============================================================
// 7. 求一个数的所有约数
//    利用"约数成对出现"的性质，只需遍历到 √n
// ============================================================
void demo_divisors() {
    cout << "\n========== 7. 求一个数的所有约数 ==========\n";
    cout << "输入一个正整数 n：\n> ";

    long long n;
    cin >> n;

    if (n <= 0) {
        cout << "请输入正整数。" << endl;
        return;
    }

    vector<long long> divisors;
    for (long long i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            divisors.push_back(i);
            if (i != n / i) {
                divisors.push_back(n / i);  // 成对的约数
            }
        }
    }
    sort(divisors.begin(), divisors.end());

    cout << n << " 的所有约数 (" << divisors.size() << " 个): ";
    for (long long d : divisors) {
        cout << d << " ";
    }
    cout << endl;

    // 判断 n 是否为完全数（约数和 = 2n）
    long long sum = 0;
    for (long long d : divisors) {
        sum += d;
    }
    if (sum == 2 * n) {
        cout << n << " 是完全数！（约数之和 = " << sum << "）" << endl;
    } else {
        cout << "约数之和 = " << sum << endl;
    }
}

// ============================================================
// 主菜单
// ============================================================
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "================================================\n";
    cout << "  CSP-J 第36课：数论基础 — 代码演示\n";
    cout << "================================================\n";
    cout << "  1. 试除法判断质数\n";
    cout << "  2. 埃氏筛法求质数\n";
    cout << "  3. 线性筛法求质数\n";
    cout << "  4. 最大公约数 GCD\n";
    cout << "  5. 最小公倍数 LCM\n";
    cout << "  6. 快速幂\n";
    cout << "  7. 求所有约数\n";
    cout << "================================================\n";
    cout << "请选择功能 (1-7)：\n> ";

    int choice;
    cin >> choice;

    switch (choice) {
        case 1: demo_is_prime(); break;
        case 2: demo_eratosthenes(); break;
        case 3: demo_linear_sieve(); break;
        case 4: demo_gcd(); break;
        case 5: demo_lcm(); break;
        case 6: demo_quick_pow(); break;
        case 7: demo_divisors(); break;
        default: cout << "无效选择！" << endl; break;
    }

    cout << "\n演示结束。\n";
    return 0;
}
