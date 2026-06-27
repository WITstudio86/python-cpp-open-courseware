/**
 * ============================================================
 * 课程编号：第38课
 * 课程标题：筛法与素数
 * 对应考纲：素数筛法、欧拉函数、数论基础
 * CSP-S 常考知识点，掌握后可解决素数判定、区间筛、欧拉函数求和等问题
 * ============================================================
 */

#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

typedef long long ll;

// =================== 全局数组（大数组必须全局或 static）===================
const int MAXN = 10000005;  // 10^7 + 5

// =================== 1. 试除法判定素数（朴素版）===================
// 时间复杂度：O(sqrt(n))
// 用途：单点判定一个数是否为素数
bool isPrimeTrial(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// =================== 1b. 试除法判定素数（优化版 - 6k±1）===================
// 常数优化，约快 3 倍
bool isPrimeTrialFast(ll n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    // 素数（除了 2 和 3）都可以表示为 6k±1 的形式
    for (ll i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

// =================== 2. 埃拉托色尼筛法（埃氏筛）===================
// 时间复杂度：O(n log log n)
// 空间复杂度：O(n)
// 用途：筛出 1..n 所有素数，n 可达 10^7
bool isPrimeEra[MAXN];

int eratosthenes(int n) {
    // 初始化：假设所有数都是素数
    fill(isPrimeEra, isPrimeEra + n + 1, true);
    isPrimeEra[0] = isPrimeEra[1] = false;
    int cnt = 0;

    for (int i = 2; i <= n; i++) {
        if (isPrimeEra[i]) {
            cnt++;
            // 从 i*i 开始标记（i*2, i*3, ..., i*(i-1) 已被更小的素数筛过）
            if ((ll)i * i <= n) {
                for (int j = i * i; j <= n; j += i) {
                    isPrimeEra[j] = false;
                }
            }
        }
    }
    return cnt;
}

// =================== 3. 欧拉筛（线性筛）—— 重点算法 ====================
// 时间复杂度：O(n)，每个合数只被其最小质因子筛一次
// 空间复杂度：O(n)
int primes[MAXN];     // 存储找到的素数
bool isPrime[MAXN];   // 标记是否为素数

int eulerSieve(int n) {
    fill(isPrime, isPrime + n + 1, true);
    isPrime[0] = isPrime[1] = false;
    int cnt = 0;  // 当前找到的素数个数

    for (int i = 2; i <= n; i++) {
        // 如果 i 是素数，加入质数列表
        if (isPrime[i]) {
            primes[cnt++] = i;
        }

        // 用已有的素数筛掉合数
        // 核心：每个合数只被其最小质因子筛掉
        for (int j = 0; j < cnt; j++) {
            int p = primes[j];
            // 防止溢出：i * p <= n
            if ((ll)i * p > n) break;

            isPrime[i * p] = false;

            // 关键判断：如果 i 能被 p 整除
            // 则 p 是 i 的最小质因子，也是 i*p 的最小质因子
            // 跳出循环，保证 p 只筛以它为最小质因子的合数
            if (i % p == 0) break;
        }
    }
    return cnt;
}

// =================== 4. 区间筛 ====================
// 用途：求 [a, b] 区间内的素数个数
// b 可高达 10^12，但 b - a <= 10^6
// 思路：先用欧拉筛求出 [2, sqrt(b)] 的素数，再用这些素数筛区间
vector<bool> isPrimeSeg; // 区间标记数组

ll segmentSieve(ll a, ll b) {
    // 步骤1：预处理 [2, sqrt(b)] 的素数
    ll limit = (ll)sqrt(b);
    int cnt = eulerSieve(limit);  // primes[0..cnt-1] 存储了 [2, limit] 的素数

    // 步骤2：初始化区间标记数组
    isPrimeSeg.assign(b - a + 1, true);
    if (a == 1) isPrimeSeg[0] = false;  // 1 不是素数

    // 步骤3：用每个素数筛区间内的合数
    for (int i = 0; i < cnt; i++) {
        ll p = primes[i];
        if (p * p > b) break;  // 无需考虑大于 sqrt(b) 的素数

        // 找到区间内第一个 p 的倍数（向上取整技巧）
        // start = ceil(a / p) * p，但不能小于 p*p
        ll start = max(p * p, (a + p - 1) / p * p);

        for (ll j = start; j <= b; j += p) {
            isPrimeSeg[j - a] = false;
        }
    }

    // 步骤4：统计结果
    ll result = 0;
    for (ll i = a; i <= b; i++) {
        if (isPrimeSeg[i - a]) result++;
    }
    return result;
}

// =================== 5. 单点求欧拉函数 O(sqrt(n)) ====================
// φ(n) = n * Π(1 - 1/p_i)，其中 p_i 是 n 的质因子
ll phi(ll n) {
    ll res = n;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            res = res / i * (i - 1);  // res *= (1 - 1/i) = res/i*(i-1)
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) {
        // n 本身是质数
        res = res / n * (n - 1);
    }
    return res;
}

// =================== 6. 线性筛同时求欧拉函数 ====================
// 时间复杂度：O(n)
// 在欧拉筛的过程中，利用欧拉函数的积性，计算 φ(1..n)
int primesPhi[MAXN];
bool isPrimePhi[MAXN];
ll phiArr[MAXN];  // phiArr[i] = φ(i)

int eulerSieveWithPhi(int n) {
    fill(isPrimePhi, isPrimePhi + n + 1, true);
    isPrimePhi[0] = isPrimePhi[1] = false;
    int cnt = 0;
    phiArr[1] = 1;

    for (int i = 2; i <= n; i++) {
        if (isPrimePhi[i]) {
            primesPhi[cnt++] = i;
            phiArr[i] = i - 1;  // φ(p) = p - 1（p 为质数）
        }

        for (int j = 0; j < cnt; j++) {
            int p = primesPhi[j];
            if ((ll)i * p > n) break;

            isPrimePhi[i * p] = false;

            if (i % p == 0) {
                // 情况1：p 是 i 的质因子
                // φ(i * p) = φ(i) * p
                phiArr[i * p] = phiArr[i] * p;
                break;  // 线性筛的关键：跳出循环
            } else {
                // 情况2：p 与 i 互质
                // φ(i * p) = φ(i) * φ(p) = φ(i) * (p - 1)
                phiArr[i * p] = phiArr[i] * (p - 1);
            }
        }
    }
    return cnt;
}

// =================== 主函数：演示所有功能 ====================
int main() {
    cout << "==================== 第38课：筛法与素数 ====================" << endl;

    // ---- 1. 试除法 ----
    cout << "\n【1. 试除法判定素数】" << endl;
    int testNums[] = {2, 3, 4, 17, 97, 100, 9973, 10007};
    for (int n : testNums) {
        cout << "  " << n << ": 朴素=" << (isPrimeTrial(n) ? "素数" : "合数")
             << " | 优化=" << (isPrimeTrialFast(n) ? "素数" : "合数") << endl;
    }

    // 大数测试（10^12 级别）
    ll big = 1000000007;
    cout << "  " << big << ": " << (isPrimeTrialFast(big) ? "素数" : "合数")
         << " (1000000007 是质数)" << endl;

    // ---- 2. 埃氏筛 ----
    cout << "\n【2. 埃拉托色尼筛法 (n=100)】" << endl;
    int cntEra = eratosthenes(100);
    cout << "  1~100 内素数个数: " << cntEra << " (预期: 25)" << endl;
    cout << "  素数列表前 10 个: ";
    for (int i = 2, k = 0; i <= 100 && k < 10; i++) {
        if (isPrimeEra[i]) {
            cout << i << " ";
            k++;
        }
    }
    cout << endl;

    // ---- 3. 欧拉筛（线性筛）----
    cout << "\n【3. 欧拉筛/线性筛 (n=100)】" << endl;
    int cntEuler = eulerSieve(100);
    cout << "  1~100 内素数个数: " << cntEuler << " (预期: 25)" << endl;
    cout << "  素数列表: ";
    for (int i = 0; i < cntEuler; i++) {
        cout << primes[i] << " ";
    }
    cout << endl;

    // 大规模测试
    const int TEST_N = 1000000;
    cntEuler = eulerSieve(TEST_N);
    cout << "  1~" << TEST_N << " 内素数个数: " << cntEuler
         << " (理论值约 " << (int)(TEST_N / log(TEST_N)) << ")" << endl;

    // 验证第 10000 个素数的近似
    cout << "  第 10000 个素数: " << primes[9999]
         << " (理论近似: " << (int)(10000 * log(10000)) << ")" << endl;

    // ---- 4. 区间筛 ----
    cout << "\n【4. 区间筛】" << endl;

    // 测试1：小范围
    ll a = 1, b = 100;
    ll segCnt = segmentSieve(a, b);
    cout << "  [" << a << ", " << b << "] 内素数个数: " << segCnt
         << " (预期: 25)" << endl;

    // 测试2：大范围小间距
    a = 100000000000LL;  // 10^11
    b = 100000000100LL;  // 间距 100
    segCnt = segmentSieve(a, b);
    cout << "  [" << a << ", " << b << "] 内素数个数: " << segCnt << endl;
    cout << "  素数列表: ";
    for (ll i = a; i <= b; i++) {
        if (isPrimeSeg[i - a]) cout << i << " ";
    }
    cout << endl;

    // ---- 5. 单点欧拉函数 ----
    cout << "\n【5. 单点求欧拉函数】" << endl;
    for (int n : {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 100}) {
        cout << "  φ(" << n << ") = " << phi(n) << endl;
    }
    // 质数的 φ(p) = p-1
    cout << "  φ(97) = " << phi(97) << " (应等于 96)" << endl;

    // ---- 6. 线性筛求欧拉函数 ----
    cout << "\n【6. 线性筛求欧拉函数 (n=30)】" << endl;
    int nScan = 30;
    eulerSieveWithPhi(nScan);
    cout << "  逐项 φ(i):" << endl;
    for (int i = 1; i <= nScan; i++) {
        cout << "  φ(" << i << ")=" << phiArr[i];
        if (i % 5 == 0) cout << endl;
    }

    // 验证：∑ φ(d) = n（d|n）
    cout << "\n  验证性质：∑_{d|12} φ(d) = 12" << endl;
    ll sum = 0;
    for (int d = 1; d <= 12; d++) {
        if (12 % d == 0) {
            sum += phiArr[d];
            cout << "    φ(" << d << ") = " << phiArr[d] << ", 累计 = " << sum << endl;
        }
    }
    cout << "  总和 = " << sum << " (预期: 12)" << endl;

    // ---- 7. 大规模欧拉函数求和 ----
    cout << "\n【7. 欧拉函数求和 (n=1000)】" << endl;
    eulerSieveWithPhi(1000);
    ll phiSum = 0;
    for (int i = 1; i <= 1000; i++) {
        phiSum += phiArr[i];
    }
    cout << "  Σ φ(i) (i=1..1000) = " << phiSum << endl;

    // ---- 8. 性能对比 ----
    cout << "\n【8. 筛法性能简要对比】" << endl;
    cout << "  n=10000000(10^7):" << endl;
    cout << "    欧拉筛(线性筛) O(n) 预计 ~0.1秒" << endl;
    cout << "    埃氏筛 O(n log log n) 预计 ~0.2秒" << endl;

    cout << "\n==================== 演示结束 ====================" << endl;
    return 0;
}
