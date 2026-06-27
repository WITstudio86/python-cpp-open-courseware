/**
 * 第39课：组合数学基础
 * 对应CSP-S考纲知识点：
 *   - 排列组合基础公式（杨辉三角递推、阶乘+逆元O(1)查询）
 *   - 卢卡斯定理（Lucas Theorem，大n大k小质数p）
 *   - 卡特兰数（Catalan Number，多种计算方式与经典应用）
 *   - 容斥原理（Inclusion-Exclusion Principle，二进制枚举子集）
 *
 * 包含以下实现：
 *   1. 杨辉三角递推求组合数（适合n≤5000）
 *   2. 阶乘预处理 + 逆元求组合数（O(1)查询，n≤1e6）
 *   3. 卢卡斯定理完整实现
 *   4. 卡特兰数计算（组合数公式 + 递推公式）
 *   5. 容斥原理示例（求1~n中与m互质的数的个数）
 *   6. 真题精练：出栈序列计数 + 区间容斥
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;
using ll = long long;

// ============================================================
// 常量定义
// ============================================================
const int MAXN = 2000005;        // 阶乘预处理上限
const ll MOD = 1000000007;       // 常用模数（质数）
const ll MOD2 = 998244353;       // 备用模数（质数）

// ============================================================
// 一、快速幂（通用工具）
// 功能：计算 a^b mod MOD
// 时间复杂度：O(log b)
// ============================================================
ll qpow(ll a, ll b, ll mod = MOD) {
    ll res = 1;
    a %= mod;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

// ============================================================
// 二、杨辉三角递推求组合数
// 适用场景：n ≤ 5000，需要大量查询 C(n, k)
// 时间复杂度：O(n^2) 预处理，O(1) 查询
// 空间复杂度：O(n^2) 或 O(n) 滚动数组
// ============================================================
struct PascalTriangle {
    vector<vector<ll>> c;  // c[n][k] = C(n, k) mod MOD

    // 构建杨辉三角，预处理到 maxN
    void build(int maxN, ll mod = MOD) {
        c.assign(maxN + 1, vector<ll>(maxN + 1, 0));
        for (int i = 0; i <= maxN; i++) {
            c[i][0] = c[i][i] = 1;
            for (int j = 1; j < i; j++) {
                c[i][j] = (c[i-1][j-1] + c[i-1][j]) % mod;
            }
        }
    }

    // O(1) 查询 C(n, k)
    ll C(int n, int k) {
        if (k < 0 || k > n) return 0;
        return c[n][k];
    }
};

// ============================================================
// 三、阶乘预处理 + 逆元求组合数（O(1) 查询版）
// 适用场景：n 较大（≤ 1e6），mod 为质数且 n < mod
// 时间复杂度：O(n) 预处理，O(1) 查询
// ============================================================
struct Combinatorics {
    vector<ll> fact, inv_fact;
    ll mod;

    Combinatorics(ll m = MOD) : mod(m) {}

    // 预处理阶乘和阶乘逆元
    void init(int n) {
        fact.resize(n + 1);
        inv_fact.resize(n + 1);
        fact[0] = 1;
        for (int i = 1; i <= n; i++) {
            fact[i] = fact[i-1] * i % mod;
        }
        // 费马小定理求 inv_fact[n]，然后倒推
        inv_fact[n] = qpow(fact[n], mod - 2, mod);
        for (int i = n; i >= 1; i--) {
            inv_fact[i-1] = inv_fact[i] * i % mod;
        }
    }

    // O(1) 查询组合数 C(n, k)
    ll C(ll n, ll k) {
        if (k < 0 || k > n) return 0;
        return fact[n] * inv_fact[k] % mod * inv_fact[n-k] % mod;
    }

    // 排列数 P(n, k)
    ll P(ll n, ll k) {
        if (k < 0 || k > n) return 0;
        return fact[n] * inv_fact[n-k] % mod;
    }
};

// ============================================================
// 四、卢卡斯定理（Lucas Theorem）
// 适用场景：n 和 k 极大（可达 1e18），但质数 p 较小
// 公式：C(n, k) % p = C(n%p, k%p) * Lucas(n/p, k/p) % p
// 时间复杂度：O(log_p n)，预处理 O(p)
// ============================================================
struct LucasTheorem {
    vector<ll> fact, inv_fact;
    ll p;  // 质数模数

    LucasTheorem(ll prime) : p(prime) {}

    // 预处理模 p 范围内的阶乘
    void init() {
        fact.resize(p);
        inv_fact.resize(p);
        fact[0] = 1;
        for (int i = 1; i < p; i++) {
            fact[i] = fact[i-1] * i % p;
        }
        inv_fact[p-1] = qpow(fact[p-1], p - 2, p);
        for (int i = p - 1; i >= 1; i--) {
            inv_fact[i-1] = inv_fact[i] * i % p;
        }
    }

    // 小组合数 C(a, b) % p（要求 a, b < p）
    ll smallC(ll a, ll b) {
        if (b < 0 || b > a) return 0;
        return fact[a] * inv_fact[b] % p * inv_fact[a-b] % p;
    }

    // 卢卡斯定理主函数
    ll lucas(ll n, ll k) {
        if (k == 0) return 1;
        return smallC(n % p, k % p) * lucas(n / p, k / p) % p;
    }
};

// ============================================================
// 五、卡特兰数（Catalan Number）
// 定义：H_n = C(2n, n) / (n+1) = C(2n, n) - C(2n, n-1)
// 经典应用：括号序列、出栈序列、二叉树形态、凸多边形三角剖分
// ============================================================
struct Catalan {
    vector<ll> H;  // H[i] = 第 i 个卡特兰数
    ll mod;

    Catalan(ll m = MOD) : mod(m) {}

    // 方法1：使用组合数公式 H_n = C(2n, n) / (n+1)
    // 前提：需要阶乘预处理支持到 2*maxN
    void build_by_formula(int maxN, Combinatorics& comb) {
        H.resize(maxN + 1);
        for (int i = 0; i <= maxN; i++) {
            // H_i = C(2i, i) * inv(i+1) % mod
            H[i] = comb.C(2*i, i) * qpow(i + 1, mod - 2, mod) % mod;
        }
    }

    // 方法2：使用递推公式 H_n = H_{n-1} * (4n-2) / (n+1)
    // 时间复杂度：O(n)，不需要阶乘预处理
    void build_by_recurrence(int maxN) {
        H.resize(maxN + 1);
        H[0] = 1;
        for (int i = 1; i <= maxN; i++) {
            // H[i] = H[i-1] * (4*i-2) * inv(i+1) % mod
            ll numerator = H[i-1] * (4LL * i - 2) % mod;
            H[i] = numerator * qpow(i + 1, mod - 2, mod) % mod;
        }
    }

    // 方法3：使用第二个组合数公式 H_n = C(2n, n) - C(2n, n-1)
    ll get_single(int n, Combinatorics& comb) {
        ll res = comb.C(2*n, n) - comb.C(2*n, n-1);
        return (res % mod + mod) % mod;
    }
};

// ============================================================
// 六、容斥原理（Inclusion-Exclusion Principle）
// 求1~n中与m互质的数的个数
// 思路：对 m 做质因子分解，然后二进制枚举子集进行容斥
// 时间复杂度：O(sqrt(m) + 2^k)，k 为 m 的不同质因子个数
// ============================================================

// 对 m 进行质因子分解，返回不同的质因子列表
vector<ll> prime_factors(ll m) {
    vector<ll> factors;
    for (ll i = 2; i * i <= m; i++) {
        if (m % i == 0) {
            factors.push_back(i);
            while (m % i == 0) m /= i;
        }
    }
    if (m > 1) factors.push_back(m);
    return factors;
}

// 求 [1, x] 中与 m 互质的数的个数
// 即求 [1, x] 中不被 m 的任一质因子整除的数的个数
ll coprime_count(ll x, const vector<ll>& primes) {
    if (x <= 0) return 0;
    int k = primes.size();
    ll total = 0;  // total = 能被至少一个质因子整除的数的个数

    // 二进制枚举非空子集
    for (int mask = 1; mask < (1 << k); mask++) {
        ll prod = 1;
        int bits = 0;
        bool overflow = false;
        for (int i = 0; i < k; i++) {
            if (mask & (1 << i)) {
                // 防止乘法溢出
                if (prod > x / primes[i]) {
                    overflow = true;
                    break;
                }
                prod *= primes[i];
                bits++;
            }
        }
        if (overflow) continue;  // 乘积超过 x，贡献为 0，跳过

        ll cnt = x / prod;
        if (bits & 1) total += cnt;  // 奇数个集合：加
        else          total -= cnt;  // 偶数个集合：减
    }

    // 与 m 互质 = 全集 - 能被任一质因子整除的
    return x - total;
}

// 求区间 [l, r] 中至少能被给定质数列表中一个整除的数的个数
// 即容斥原理的另一个应用方向
ll divisible_count(ll l, ll r, const vector<ll>& primes) {
    // 利用前缀思想：f(r) - f(l-1)
    // 其中 f(x) = [1, x] 中至少能被一个质数整除的数的个数
    auto f = [&](ll x) -> ll {
        if (x <= 0) return 0;
        int k = primes.size();
        ll total = 0;
        for (int mask = 1; mask < (1 << k); mask++) {
            ll prod = 1;
            int bits = 0;
            bool overflow = false;
            for (int i = 0; i < k; i++) {
                if (mask & (1 << i)) {
                    if (prod > x / primes[i]) { overflow = true; break; }
                    prod *= primes[i];
                    bits++;
                }
            }
            if (overflow) continue;
            ll cnt = x / prod;
            if (bits & 1) total += cnt;
            else          total -= cnt;
        }
        return total;
    };
    return f(r) - f(l - 1);
}

// ============================================================
// 七、真题精练 — 出栈序列计数（卡特兰数直接应用）
// 问题：n 个元素依次入栈，求合法出栈序列的个数 mod MOD
// 答案 = 卡特兰数 H_n
// ============================================================
ll stack_sequences(int n, Combinatorics& comb) {
    return comb.C(2*n, n) * qpow(n + 1, MOD - 2) % MOD;
}

// ============================================================
// 主函数：演示所有功能
// ============================================================
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "═══════════════════════════════════════" << endl;
    cout << "  第39课：组合数学基础 — 代码演示" << endl;
    cout << "═══════════════════════════════════════" << endl << endl;

    // ---------- 1. 杨辉三角演示 ----------
    cout << "【1】杨辉三角递推求组合数（前10行）" << endl;
    PascalTriangle pascal;
    pascal.build(10);
    for (int i = 0; i <= 10; i++) {
        cout << "  n=" << i << ": ";
        for (int j = 0; j <= i; j++) {
            cout << pascal.C(i, j) << " ";
        }
        cout << endl;
    }
    cout << "  C(10, 5) = " << pascal.C(10, 5) << "（验证：252）" << endl << endl;

    // ---------- 2. 阶乘+逆元 O(1) 组合数 ----------
    cout << "【2】阶乘预处理 + 逆元 O(1) 组合数" << endl;
    Combinatorics comb(MOD);
    comb.init(200000);  // 预处理到 20 万
    cout << "  C(100, 50) mod 1e9+7 = " << comb.C(100, 50) << endl;
    cout << "  C(1000, 500) mod 1e9+7 = " << comb.C(1000, 500) << endl;
    cout << "  P(10, 3) = 10*9*8 = " << comb.P(10, 3) << "（验证：720）" << endl;
    cout << "  对称性: C(10,3)=" << comb.C(10,3) << " vs C(10,7)=" << comb.C(10,7) << endl << endl;

    // ---------- 3. 卢卡斯定理 ----------
    cout << "【3】卢卡斯定理（n 和 k 可达 1e18，p 较小）" << endl;
    LucasTheorem lucas(10007);
    lucas.init();
    cout << "  C(1000000000000, 500000000000) mod 10007 = "
         << lucas.lucas(1000000000000LL, 500000000000LL) << endl;
    // 小验证：C(10, 3) mod 10007 = 120 mod 10007 = 120
    cout << "  C(10, 3) mod 10007 = " << lucas.lucas(10, 3) << "（验证：120）" << endl << endl;

    // ---------- 4. 卡特兰数 ----------
    cout << "【4】卡特兰数（Catalan Numbers）" << endl;
    Catalan catalan;
    catalan.build_by_recurrence(20);
    cout << "  前 11 个卡特兰数：";
    for (int i = 0; i <= 10; i++) cout << catalan.H[i] << " ";
    cout << endl;
    cout << "  （标准值：1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796）" << endl;
    cout << "  H_10（通过组合数公式验证）：" << catalan.get_single(10, comb) << endl << endl;

    // ---------- 5. 容斥原理 ----------
    cout << "【5】容斥原理 — 与 m 互质的数的个数" << endl;
    ll m_test = 30;
    auto factors = prime_factors(m_test);
    cout << "  m = " << m_test << " 的质因子：";
    for (ll f : factors) cout << f << " ";
    cout << endl;
    ll n_test = 100;
    cout << "  1~" << n_test << " 中与 " << m_test << " 互质的数的个数："
         << coprime_count(n_test, factors) << endl;
    // 手工验证：与 30 互质即不被 2,3,5 整除
    int manual = 0;
    for (int i = 1; i <= n_test; i++)
        if (i % 2 != 0 && i % 3 != 0 && i % 5 != 0) manual++;
    cout << "  手工验证结果：" << manual << endl << endl;

    // ---------- 6. 真题精练 1: 出栈序列 ----------
    cout << "【真题1】出栈序列计数（卡特兰数）" << endl;
    int test_n[] = {1, 2, 3, 4, 5, 10};
    for (int n : test_n) {
        cout << "  n=" << n << " 个元素的出栈序列数 = "
             << stack_sequences(n, comb) << endl;
    }
    cout << "  （标准值：1, 2, 5, 14, 42, 16796）" << endl << endl;

    // ---------- 7. 真题精练 2: 区间容斥 ----------
    cout << "【真题2】区间内能被质数集合中至少一个整除的数的个数" << endl;
    vector<ll> test_primes = {2, 3, 5, 7};
    ll a = 1, b = 100;
    cout << "  质数集合: {2, 3, 5, 7}" << endl;
    cout << "  区间 [" << a << ", " << b << "] 中能被至少一个整除的数的个数 = "
         << divisible_count(a, b, test_primes) << endl;
    // 手工验证
    int manual2 = 0;
    for (int i = a; i <= b; i++)
        if (i % 2 == 0 || i % 3 == 0 || i % 5 == 0 || i % 7 == 0)
            manual2++;
    cout << "  手工验证结果：" << manual2 << endl;

    cout << "\n═══════════════════════════════════════" << endl;
    cout << "  所有功能演示完毕！" << endl;
    cout << "═══════════════════════════════════════" << endl;

    return 0;
}
