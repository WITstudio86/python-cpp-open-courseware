/**
 * ============================================================
 * 课程编号：第37课
 * 课程标题：快速幂与逆元
 * 对应考纲：快速幂、乘法逆元、模运算、组合数学取模
 * CSP-S 常考知识点，掌握后可解决大量组合数学与计数问题
 * ============================================================
 */

#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

// =================== 1. 快速幂（迭代版 - 推荐）===================
// 时间复杂度：O(log b)
// 用途：计算 a^b mod MOD，b 可高达 10^18
ll fastPow(ll a, ll b, ll MOD) {
    ll result = 1;
    a %= MOD;  // 先对 a 取模，防止后续乘法溢出
    while (b > 0) {
        if (b & 1)  // 如果当前二进制位为 1
            result = result * a % MOD;
        a = a * a % MOD;  // a 平方：a -> a^2 -> a^4 -> a^8
        b >>= 1;
    }
    return result;
}

// =================== 2. 快速幂（递归版）===================
// 更直观但可能栈溢出（b 极大时），实际竞赛推荐迭代版
ll fastPowRecursive(ll a, ll b, ll MOD) {
    if (b == 0) return 1;
    ll half = fastPowRecursive(a, b / 2, MOD);
    half = half * half % MOD;
    if (b & 1)
        half = half * a % MOD;
    return half;
}

// =================== 3. 费马小定理求逆元 ===================
// 条件：MOD 必须是质数
// 推导：a^{MOD-1} ≡ 1 (mod MOD) => a^{-1} ≡ a^{MOD-2} (mod MOD)
// 时间复杂度：O(log MOD)
ll invFermat(ll a, ll MOD) {
    return fastPow(a, MOD - 2, MOD);
}

// =================== 4. 扩展欧几里得算法 ===================
// 求解 ax + by = gcd(a, b)，返回 gcd(a, b)
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, y, x);
    // 此时 y 是新的 x'，x 是新的 y'，
    // 需要调整：y = y - (a/b) * x
    y -= a / b * x;
    return d;
}

// =================== 5. 扩展欧几里得求逆元 ===================
// 条件：gcd(a, MOD) = 1（MOD 不一定是质数）
// 思路：解 ax + MOD*y = 1，则 x 即为 a 的逆元
// 时间复杂度：O(log min(a, MOD))
ll invExgcd(ll a, ll MOD) {
    ll x, y;
    ll d = exgcd(a, MOD, x, y);
    if (d != 1) return -1;  // 逆元不存在（a 与 MOD 不互质）
    return (x % MOD + MOD) % MOD;  // 确保返回非负值
}

// =================== 6. 组合数取模 ===================
const int MAXN = 1000005;
ll fact[MAXN];     // fact[i] = i! mod MOD
ll invFact[MAXN];  // invFact[i] = (i!)^(-1) mod MOD

// 预处理阶乘和阶乘逆元
// 时间复杂度：O(n + log MOD)
void precomputeCombi(int n, ll MOD) {
    // 计算阶乘
    fact[0] = 1;
    for (int i = 1; i <= n; i++)
        fact[i] = fact[i - 1] * i % MOD;

    // 用费马小定理求 n! 的逆元
    invFact[n] = fastPow(fact[n], MOD - 2, MOD);

    // 倒推所有阶乘逆元
    // invFact[i-1] = invFact[i] * i % MOD
    for (int i = n; i >= 1; i--)
        invFact[i - 1] = invFact[i] * i % MOD;
}

// O(1) 查询组合数 C(n, k) mod MOD
ll C(int n, int k, ll MOD) {
    if (k < 0 || k > n) return 0;
    return fact[n] * invFact[k] % MOD * invFact[n - k] % MOD;
}

// =================== 7. 线性求逆元 (O(n)) ===================
// 条件：MOD 必须是质数
// 递推公式：inv[i] = (MOD - MOD/i) * inv[MOD % i] % MOD
// 推导：设 MOD = k*i + r，则 k*i + r ≡ 0 (mod MOD)
//       r ≡ -k*i (mod MOD)，两边乘 i^{-1}*r^{-1}
//       得 i^{-1} ≡ -k * r^{-1} (mod MOD)
void linearInv(int n, ll MOD, ll inv[]) {
    inv[1] = 1;
    for (int i = 2; i <= n; i++) {
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
    }
}

// =================== 主函数：演示所有功能 ===================
int main() {
    cout << "==================== 第37课：快速幂与逆元 ====================" << endl;
    const ll MOD = 1000000007;

    // ---- 1. 快速幂演示 ----
    cout << "\n【1. 快速幂】" << endl;
    ll a = 2, b = 10;
    cout << "fastPow(" << a << ", " << b << ", " << MOD << ") = "
         << fastPow(a, b, MOD) << " (预期: 1024)" << endl;

    a = 3; b = 13;
    cout << "fastPow(" << a << ", " << b << ", " << MOD << ") = "
         << fastPow(a, b, MOD) << " (预期: 1594323)" << endl;

    // 大指数测试
    a = 2; b = 1000000000000000000LL; // 10^18
    cout << "fastPow(2, 10^18, " << MOD << ") = "
         << fastPow(a, b, MOD) << endl;

    // 递归版验证
    cout << "递归版 fastPow(2, 10, 1000000007) = "
         << fastPowRecursive(2, 10, MOD) << " (应与上面一致)" << endl;

    // ---- 2. 费马小定理求逆元 ----
    cout << "\n【2. 费马小定理求逆元】" << endl;
    a = 5;
    ll inv5 = invFermat(a, MOD);
    cout << "invFermat(" << a << ") = " << inv5 << endl;
    cout << "验证: " << a << " * " << inv5 << " % " << MOD
         << " = " << (a * inv5 % MOD) << " (预期: 1)" << endl;

    a = 1234567;
    ll invA = invFermat(a, MOD);
    cout << "invFermat(" << a << ") = " << invA << endl;
    cout << "验证: " << a << " * invA % " << MOD
         << " = " << (a * invA % MOD) << " (预期: 1)" << endl;

    // ---- 3. 扩展欧几里得求逆元 ----
    cout << "\n【3. 扩展欧几里得算法】" << endl;
    // 用 exgcd 求 gcd
    ll x, y;
    ll g = exgcd(15, 35, x, y);
    cout << "exgcd(15, 35): gcd=" << g
         << ", x=" << x << ", y=" << y << endl;
    cout << "验证: 15*" << x << " + 35*" << y << " = "
         << (15 * x + 35 * y) << " (预期: 5)" << endl;

    cout << "\n【4. 扩展欧几里得求逆元】" << endl;
    a = 5;
    inv5 = invExgcd(a, MOD);
    cout << "invExgcd(" << a << ") = " << inv5 << endl;
    cout << "验证: " << a << " * " << inv5 << " % " << MOD
         << " = " << (a * inv5 % MOD) << " (预期: 1)" << endl;

    // 测试非质数模数下的逆元（7 和 15 互质）
    ll MOD2 = 15;
    a = 7;
    ll inv7 = invExgcd(a, MOD2);
    cout << "invExgcd(7, 15) = " << inv7 << endl;
    cout << "验证: 7 * " << inv7 << " % 15 = "
         << (7 * inv7 % MOD2) << " (预期: 1)" << endl;

    // 测试不互质的情况
    a = 3;
    ll inv3 = invExgcd(a, MOD2);
    cout << "invExgcd(3, 15) = " << inv3
         << " (预期: -1，因为 gcd(3,15)=3≠1，逆元不存在)" << endl;

    // ---- 5. 组合数取模 ----
    cout << "\n【5. 组合数取模】" << endl;
    int N = 10;
    precomputeCombi(N, MOD);

    cout << "预处理阶乘和阶乘逆元 (n=" << N << "):" << endl;
    for (int i = 0; i <= N; i++)
        cout << "fact[" << i << "]=" << fact[i]
             << (i == N ? "\n" : ", ");

    cout << "组合数计算 (mod " << MOD << "):" << endl;
    cout << "  C(5, 2) = " << C(5, 2, MOD) << " (预期: 10)" << endl;
    cout << "  C(5, 0) = " << C(5, 0, MOD) << " (预期: 1)" << endl;
    cout << "  C(5, 5) = " << C(5, 5, MOD) << " (预期: 1)" << endl;
    cout << "  C(10, 3) = " << C(10, 3, MOD) << " (预期: 120)" << endl;
    cout << "  C(10, 7) = " << C(10, 7, MOD)
         << " (预期: 120, 应该等于C(10,3))" << endl;

    // 杨辉三角验证 C(n,k) = C(n-1,k-1) + C(n-1,k)
    cout << "  C(9,2) + C(9,3) mod MOD = "
         << (C(9, 2, MOD) + C(9, 3, MOD)) % MOD
         << " (应等于 C(10,3)=" << C(10, 3, MOD) << ")" << endl;

    // ---- 6. 线性求逆元 ----
    cout << "\n【6. 线性求逆元 O(n)】" << endl;
    const int M = 20;
    ll inv[M + 1];
    linearInv(M, MOD, inv);

    cout << "1~" << M << " 的逆元 (mod " << MOD << "):" << endl;
    for (int i = 1; i <= M; i++) {
        cout << "inv[" << i << "]=" << inv[i];
        if (i % 5 == 0) cout << endl;
        else cout << " | ";
    }

    // 验证线性求逆元的结果与费马小定理一致
    cout << "\n验证线性求逆元 (与费马小定理对比):" << endl;
    bool ok = true;
    for (int i = 1; i <= M; i++) {
        if (invFermat(i, MOD) != inv[i]) {
            cout << "  不一致: i=" << i << endl;
            ok = false;
        }
    }
    if (ok) cout << "  全部通过！" << endl;

    // ---- 7. 综合示例：大组合数 ----
    cout << "\n【7. 综合示例：大范围组合数】" << endl;
    // 注意：全局数组 MAXN = 1000005 已分配好
    // 实际使用时根据需要调整 MAXN
    cout << "C(100, 50) mod " << MOD << " 的计算演示（需预处理）" << endl;
    // 小范围演示
    precomputeCombi(100, MOD);
    cout << "  C(100, 50) mod " << MOD << " = " << C(100, 50, MOD) << endl;

    cout << "\n==================== 演示结束 ====================" << endl;
    return 0;
}
