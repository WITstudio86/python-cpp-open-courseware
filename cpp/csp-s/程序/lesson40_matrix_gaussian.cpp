/**
 * 第40课：矩阵快速幂与高斯消元
 * 对应CSP-S考纲知识点：
 *   - 矩阵乘法（定义、结合律、不满足交换律）
 *   - 矩阵快速幂（加速线性递推，如斐波那契 O(log n)）
 *   - 高斯消元解线性方程组（无解、唯一解、无穷多解）
 *   - 高斯消元求行列式（上三角化 + 对角线乘积）
 *   - 高斯消元求逆矩阵（增广矩阵法）
 *
 * 包含以下实现：
 *   1. 矩阵乘法（模板，支持任意大小）
 *   2. 矩阵快速幂（模板）
 *   3. 斐波那契数列的矩阵快速幂解法
 *   4. 通用线性递推加速（k阶递推 → k×k矩阵）
 *   5. 高斯消元解线性方程组（浮点数版，处理三种解情况）
 *   6. 高斯消元求行列式（模质数版）
 *   7. 高斯消元求逆矩阵（模质数版）
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;
using ll = long long;

const ll MOD = 1000000007;  // 常用模数
const double EPS = 1e-9;   // 浮点数精度

// ============================================================
// 一、快速幂（整数版，用于求逆元等）
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
// 二、矩阵乘法（模 MOD 版本）
// C = A × B，其中 A 是 n×m，B 是 m×p，结果 C 是 n×p
// 时间复杂度：O(n*m*p)，使用 i-k-j 循环顺序优化缓存
// ============================================================
using Matrix = vector<vector<ll>>;

Matrix mat_mul(const Matrix& A, const Matrix& B, ll mod = MOD) {
    int n = A.size();          // A 的行数
    int m = B.size();          // A 的列数 = B 的行数
    int p = B[0].size();       // B 的列数
    Matrix C(n, vector<ll>(p, 0));

    // i-k-j 循环顺序：对缓存更友好
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < m; k++) {
            if (A[i][k] == 0) continue;  // 稀疏优化
            ll aik = A[i][k];
            for (int j = 0; j < p; j++) {
                C[i][j] = (C[i][j] + aik * B[k][j]) % mod;
            }
        }
    }
    return C;
}

// 矩阵加法（用于某些应用场景）
Matrix mat_add(const Matrix& A, const Matrix& B, ll mod = MOD) {
    int n = A.size(), m = A[0].size();
    Matrix C(n, vector<ll>(m, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            C[i][j] = (A[i][j] + B[i][j]) % mod;
    return C;
}

// 创建单位矩阵
Matrix identity(int n) {
    Matrix I(n, vector<ll>(n, 0));
    for (int i = 0; i < n; i++) I[i][i] = 1;
    return I;
}

// 打印矩阵（调试用）
void print_matrix(const Matrix& mat, const string& name = "") {
    if (!name.empty()) cout << name << " =" << endl;
    for (auto& row : mat) {
        for (auto& val : row) cout << val << " ";
        cout << endl;
    }
}

// ============================================================
// 三、矩阵快速幂
// A^n，A 必须是方阵（n×n）
// 时间复杂度：O(sz^3 · log n)
// ============================================================
Matrix mat_pow(Matrix A, ll n, ll mod = MOD) {
    int sz = A.size();
    Matrix res = identity(sz);
    while (n) {
        if (n & 1) res = mat_mul(res, A, mod);
        A = mat_mul(A, A, mod);
        n >>= 1;
    }
    return res;
}

// ============================================================
// 四、斐波那契数列的矩阵快速幂解法
// fib(0) = 0, fib(1) = 1, fib(n) = fib(n-1) + fib(n-2)
// 转移矩阵 T = [[1, 1], [1, 0]]
// [fib(n), fib(n-1)]^T = T^(n-1) * [fib(1), fib(0)]^T
// 时间复杂度：O(log n)
// ============================================================
ll fibonacci(ll n, ll mod = MOD) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    Matrix T = {{1, 1}, {1, 0}};
    T = mat_pow(T, n - 1, mod);
    // 初始向量 [fib(1), fib(0)] = [1, 0]
    // 结果向量的第一个分量就是 fib(n)
    return T[0][0];
}

// 斐波那契数列（返回第 n 项，用于对比验证）
ll fibonacci_linear(ll n, ll mod = MOD) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    ll a = 0, b = 1;
    for (ll i = 2; i <= n; i++) {
        ll c = (a + b) % mod;
        a = b;
        b = c;
    }
    return b;
}

// ============================================================
// 五、通用 k 阶线性递推加速
// 递推式：a_n = c1 * a_{n-1} + c2 * a_{n-2} + ... + ck * a_{n-k}
// 构造 k×k 转移矩阵，第一行为系数 [c1, c2, ..., ck]
// 下方为偏移单位矩阵
// 初始向量：V = [a_{k-1}, a_{k-2}, ..., a_0]^T（注意顺序）
// 结果：T^(n-k+1) * V 得到 [a_n, a_{n-1}, ..., a_{n-k+1}]^T
// ============================================================

// 构建 k 阶递推的转移矩阵
// coeffs = [c1, c2, ..., ck]（注意 c1 是 a_{n-1} 的系数）
Matrix build_recurrence_matrix(const vector<ll>& coeffs) {
    int k = coeffs.size();
    Matrix T(k, vector<ll>(k, 0));
    // 第一行填系数
    for (int j = 0; j < k; j++) T[0][j] = coeffs[j] % MOD;
    // 下方偏移单位矩阵
    for (int i = 1; i < k; i++) T[i][i-1] = 1;
    return T;
}

// 通用递推求解 a_n
// coeffs: [c1, c2, ..., ck]
// init_vals: [a_0, a_1, a_2, ..., a_{k-1}]（前 k 项的初始值，顺序为从小到大）
ll solve_recurrence(ll n, const vector<ll>& coeffs, const vector<ll>& init_vals) {
    int k = coeffs.size();
    if (n < k) return init_vals[n] % MOD;

    Matrix T = build_recurrence_matrix(coeffs);
    T = mat_pow(T, n - k + 1);

    // 计算 a_n = Σ T[0][j] * init_vals[k-1-j]
    // 初始向量的排列：V = [a_{k-1}, a_{k-2}, ..., a_0]^T
    ll res = 0;
    for (int j = 0; j < k; j++) {
        res = (res + T[0][j] * init_vals[k-1-j]) % MOD;
    }
    return res;
}

// ============================================================
// 六、高斯消元解线性方程组（浮点数版本）
// 输入：增广矩阵 a（n × (n+1)），a[i][n] 为等式右边
// 输出：x 为解向量
// 返回值：-1 = 无解，0 = 无穷多解，1 = 唯一解
// 时间复杂度：O(n^3)
// ============================================================
int gauss_solve(vector<vector<double>> a, vector<double>& x) {
    int n = a.size();
    int m = n + 1;  // 增广矩阵的列数

    // 记录每个变量对应的主元行，-1 表示自由变量
    vector<int> pivot_row(n, -1);

    // ---- 第一步：前向消元（化为行阶梯形） ----
    int row = 0;  // 当前处理到哪一行
    for (int col = 0; col < n && row < n; col++) {
        // 选主元：在第 row 行及以下中找 col 列绝对值最大的行
        int best = row;
        for (int i = row + 1; i < n; i++) {
            if (fabs(a[i][col]) > fabs(a[best][col])) {
                best = i;
            }
        }

        // 如果主元接近 0，该列跳过（成为自由变量）
        if (fabs(a[best][col]) < EPS) continue;

        // 将主元行交换到当前行
        swap(a[row], a[best]);
        pivot_row[col] = row;

        // 消去下方所有行的第 col 列
        for (int i = row + 1; i < n; i++) {
            double factor = a[i][col] / a[row][col];
            // 从 col 列开始消（col 之前的列已经是 0）
            for (int j = col; j < m; j++) {
                a[i][j] -= factor * a[row][j];
            }
        }
        row++;
    }

    // ---- 第二步：检查是否有矛盾行（无解判定） ----
    for (int i = row; i < n; i++) {
        // 如果某行系数全为 0 但 b 不为 0，则无解
        bool all_zero = true;
        for (int j = 0; j < n; j++) {
            if (fabs(a[i][j]) > EPS) { all_zero = false; break; }
        }
        if (all_zero && fabs(a[i][n]) > EPS) {
            return -1;  // 无解
        }
    }

    // ---- 第三步：检查是否有自由变量（无穷多解判定） ----
    for (int col = 0; col < n; col++) {
        if (pivot_row[col] == -1) {
            return 0;  // 存在自由变量 → 无穷多解
        }
    }

    // ---- 第四步：回代求解（唯一解） ----
    x.assign(n, 0);
    for (int col = n - 1; col >= 0; col--) {
        int r = pivot_row[col];
        double sum = a[r][n];  // 等式右边
        for (int j = col + 1; j < n; j++) {
            sum -= a[r][j] * x[j];
        }
        x[col] = sum / a[r][col];
    }
    return 1;  // 唯一解
}

// ============================================================
// 七、高斯消元求行列式（模质数版本）
// 将矩阵化为上三角矩阵，对角线乘积即为行列式
// 注意：交换行时行列式变号
// 时间复杂度：O(n^3)
// ============================================================
ll determinant(Matrix a, ll mod = MOD) {
    int n = a.size();
    ll det = 1;

    for (int col = 0; col < n; col++) {
        // 找主元（非零元素）
        int pivot = -1;
        for (int r = col; r < n; r++) {
            if (a[r][col] != 0) {
                pivot = r;
                break;
            }
        }

        // 该列全为 0，行列式为 0
        if (pivot == -1) return 0;

        // 如果主元不在当前行，交换行（行列式变号）
        if (pivot != col) {
            swap(a[col], a[pivot]);
            det = (mod - det) % mod;  // 乘以 -1
        }

        // 乘上主元（在消元之前记录）
        det = det * a[col][col] % mod;

        // 消去下方行
        ll inv_pivot = qpow(a[col][col], mod - 2, mod);
        for (int r = col + 1; r < n; r++) {
            if (a[r][col] == 0) continue;
            ll factor = a[r][col] * inv_pivot % mod;
            for (int c = col; c < n; c++) {
                a[r][c] = (a[r][c] - factor * a[col][c] % mod + mod) % mod;
            }
        }
    }
    return det;
}

// 高斯消元求行列式（浮点数版本，用于对比验证）
double determinant_double(vector<vector<double>> a) {
    int n = a.size();
    double det = 1.0;

    for (int col = 0; col < n; col++) {
        // 选主元
        int pivot = col;
        for (int r = col + 1; r < n; r++) {
            if (fabs(a[r][col]) > fabs(a[pivot][col])) {
                pivot = r;
            }
        }

        if (fabs(a[pivot][col]) < EPS) return 0.0;

        if (pivot != col) {
            swap(a[col], a[pivot]);
            det = -det;
        }

        det *= a[col][col];

        for (int r = col + 1; r < n; r++) {
            double factor = a[r][col] / a[col][col];
            for (int c = col; c < n; c++) {
                a[r][c] -= factor * a[col][c];
            }
        }
    }
    return det;
}

// ============================================================
// 八、高斯消元求逆矩阵（模质数版本）
// 增广矩阵法：[A | I] → 行变换 → [I | A^(-1)]
// 返回值：true = 成功，false = 矩阵不可逆
// 时间复杂度：O(n^3)
// ============================================================
bool mat_inverse(const Matrix& A, Matrix& inv, ll mod = MOD) {
    int n = A.size();

    // 构造增广矩阵 augmented = [A | I]
    Matrix aug(n, vector<ll>(2 * n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            aug[i][j] = A[i][j] % mod;
        }
        aug[i][n + i] = 1;  // 右侧单位矩阵
    }

    // 高斯-约当消元
    for (int col = 0; col < n; col++) {
        // 找主元
        int pivot = -1;
        for (int r = col; r < n; r++) {
            if (aug[r][col] != 0) {
                pivot = r;
                break;
            }
        }
        if (pivot == -1) return false;  // 不可逆
        swap(aug[col], aug[pivot]);

        // 将主元化为 1
        ll inv_pivot = qpow(aug[col][col], mod - 2, mod);
        for (int j = 0; j < 2 * n; j++) {
            aug[col][j] = aug[col][j] * inv_pivot % mod;
        }

        // 消去其他所有行的第 col 列（不仅仅是下方行）
        for (int r = 0; r < n; r++) {
            if (r == col) continue;
            ll factor = aug[r][col];
            if (factor == 0) continue;
            for (int j = 0; j < 2 * n; j++) {
                aug[r][j] = (aug[r][j] - factor * aug[col][j] % mod + mod) % mod;
            }
        }
    }

    // 提取逆矩阵
    inv.assign(n, vector<ll>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inv[i][j] = aug[i][n + j];
        }
    }
    return true;
}

// ============================================================
// 辅助函数：生成 n×n 的随机矩阵（用于测试）
// ============================================================
Matrix random_matrix(int n, ll mod = MOD) {
    Matrix mat(n, vector<ll>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            mat[i][j] = rand() % mod;
    return mat;
}

// ============================================================
// 主函数：演示所有功能
// ============================================================
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(0));

    cout << fixed << setprecision(6);
    cout << "═══════════════════════════════════════" << endl;
    cout << "  第40课：矩阵快速幂与高斯消元 — 代码演示" << endl;
    cout << "═══════════════════════════════════════" << endl << endl;

    // ---------- 1. 矩阵乘法演示 ----------
    cout << "【1】矩阵乘法" << endl;
    Matrix A = {{1, 2}, {3, 4}};
    Matrix B = {{5, 6}, {7, 8}};
    Matrix C = mat_mul(A, B);
    print_matrix(A, "  A");
    print_matrix(B, "  B");
    print_matrix(C, "  A×B");
    cout << "  验证：(1)(5)+(2)(7)=" << 1*5+2*7 << " (1)(6)+(2)(8)=" << 1*6+2*8 << endl;
    cout << "        (3)(5)+(4)(7)=" << 3*5+4*7 << " (3)(6)+(4)(8)=" << 3*6+4*8 << endl << endl;

    // ---------- 2. 矩阵快速幂演示 ----------
    cout << "【2】矩阵快速幂" << endl;
    Matrix T = {{2, 1}, {1, 0}};
    cout << "  T = [[2,1],[1,0]]" << endl;
    Matrix T3 = mat_pow(T, 3);
    print_matrix(T3, "  T^3");
    // 手工验证 T^2 = [[5,2],[2,1]], T^3 = T^2 * T = [[12,5],[5,2]]
    cout << "  验证：T^3[0][0] 应为 12，实际 " << T3[0][0] << endl << endl;

    // ---------- 3. 斐波那契数列 ----------
    cout << "【3】斐波那契数列矩阵快速幂解法" << endl;
    vector<ll> fib_tests = {0, 1, 2, 3, 5, 10, 20, 50};
    for (ll n : fib_tests) {
        cout << "  fib(" << n << ") = " << fibonacci(n) << endl;
    }
    // 大数测试
    ll big_n = 1000000000000000000LL;  // 1e18
    cout << "  fib(10^18) mod 1e9+7 = " << fibonacci(big_n) << endl;
    // 用线性递推验证小数据
    cout << "  fib(20) 线性验证 = " << fibonacci_linear(20) << endl << endl;

    // ---------- 4. 通用线性递推 ----------
    cout << "【4】通用线性递推加速（三阶递推示例）" << endl;
    // 例：a_n = a_{n-1} + 2*a_{n-2} + a_{n-3}，初值 a0=1, a1=1, a2=3
    vector<ll> coeffs = {1, 2, 1};  // c1=1, c2=2, c3=1
    vector<ll> init = {1, 1, 3};    // a0=1, a1=1, a2=3
    cout << "  递推: a_n = a_{n-1} + 2*a_{n-2} + a_{n-3}" << endl;
    cout << "  初值: a0=1, a1=1, a2=3" << endl;
    for (ll n = 0; n <= 10; n++) {
        cout << "  a_" << n << " = " << solve_recurrence(n, coeffs, init) << endl;
    }
    cout << endl;

    // ---------- 5. 高斯消元解方程组 ----------
    cout << "【5】高斯消元解线性方程组" << endl;

    // 测试1：唯一解
    cout << "  --- 测试1：唯一解 ---" << endl;
    // x + y = 3
    // 2x - y = 0
    // 解：x=1, y=2
    vector<vector<double>> eq1 = {
        {1, 1, 3},
        {2, -1, 0}
    };
    vector<double> sol1;
    int ret1 = gauss_solve(eq1, sol1);
    if (ret1 == 1) {
        cout << "  解为: x=" << sol1[0] << ", y=" << sol1[1] << endl;
        cout << "  期望: x=1, y=2" << endl;
    }

    // 测试2：无穷多解
    cout << "  --- 测试2：无穷多解 ---" << endl;
    // x + y = 3
    // 2x + 2y = 6  （第二个方程是第一个的2倍）
    vector<vector<double>> eq2 = {
        {1, 1, 3},
        {2, 2, 6}
    };
    vector<double> sol2;
    int ret2 = gauss_solve(eq2, sol2);
    cout << "  结果: " << (ret2 == 0 ? "无穷多解" : (ret2 == -1 ? "无解" : "唯一解")) << endl;

    // 测试3：无解
    cout << "  --- 测试3：无解 ---" << endl;
    // x + y = 3
    // x + y = 5  （矛盾）
    vector<vector<double>> eq3 = {
        {1, 1, 3},
        {1, 1, 5}
    };
    vector<double> sol3;
    int ret3 = gauss_solve(eq3, sol3);
    cout << "  结果: " << (ret3 == 0 ? "无穷多解" : (ret3 == -1 ? "无解" : "唯一解")) << endl;

    // 测试4：三元方程组
    cout << "  --- 测试4：三元方程组（唯一解） ---" << endl;
    // x + y + z = 6
    // x - y + z = 2
    // x + y - z = 0
    // 解：x=1, y=2, z=3
    vector<vector<double>> eq4 = {
        {1, 1, 1, 6},
        {1, -1, 1, 2},
        {1, 1, -1, 0}
    };
    vector<double> sol4;
    int ret4 = gauss_solve(eq4, sol4);
    if (ret4 == 1) {
        cout << "  解为: x=" << sol4[0] << ", y=" << sol4[1] << ", z=" << sol4[2] << endl;
        cout << "  期望: x=1, y=2, z=3" << endl;
    }
    cout << endl;

    // ---------- 6. 求行列式 ----------
    cout << "【6】高斯消元求行列式" << endl;

    // 测试矩阵
    Matrix mat_det = {
        {2, 1, 3},
        {1, 0, 4},
        {3, 2, 1}
    };
    cout << "  矩阵:" << endl;
    for (auto& row : mat_det) {
        cout << "    ";
        for (auto& v : row) cout << v << " ";
        cout << endl;
    }
    ll det_val = determinant(mat_det);
    cout << "  det mod 1e9+7 = " << det_val << endl;

    // 浮点数验证
    vector<vector<double>> mat_det_double = {
        {2, 1, 3},
        {1, 0, 4},
        {3, 2, 1}
    };
    double det_double = determinant_double(mat_det_double);
    cout << "  det (double) = " << det_double << endl;
    // 手工：det = 2*(0*1-4*2) - 1*(1*1-4*3) + 3*(1*2-0*3)
    //      = 2*(-8) - 1*(1-12) + 3*(2) = -16 - 1*(-11) + 6 = -16+11+6 = 1
    cout << "  手工验证结果应为 1" << endl << endl;

    // ---------- 7. 求逆矩阵 ----------
    cout << "【7】高斯消元求逆矩阵" << endl;

    Matrix mat_inv_test = {
        {1, 2},
        {3, 4}
    };
    cout << "  原矩阵:" << endl;
    for (auto& row : mat_inv_test) {
        cout << "    ";
        for (auto& v : row) cout << v << " ";
        cout << endl;
    }
    Matrix inv_result;
    bool inv_ok = mat_inverse(mat_inv_test, inv_result);
    if (inv_ok) {
        cout << "  逆矩阵:" << endl;
        for (auto& row : inv_result) {
            cout << "    ";
            for (auto& v : row) cout << v << " ";
            cout << endl;
        }
        // 验证：A * A^(-1) 应等于单位矩阵
        Matrix verify = mat_mul(mat_inv_test, inv_result);
        cout << "  验证 A * A^{-1}:" << endl;
        for (auto& row : verify) {
            cout << "    ";
            for (auto& v : row) cout << v << " ";
            cout << endl;
        }
        cout << "  （应为单位矩阵 [[1,0],[0,1]]）" << endl;
    } else {
        cout << "  矩阵不可逆！" << endl;
    }

    cout << "\n═══════════════════════════════════════" << endl;
    cout << "  所有功能演示完毕！" << endl;
    cout << "═══════════════════════════════════════" << endl;

    return 0;
}
