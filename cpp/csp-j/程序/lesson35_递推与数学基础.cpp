/*
 * CSP-J 备考课程 — 第35课：递推与数学基础
 *
 * 本文件包含以下完整实现：
 *   1. 斐波那契数列（递推）
 *   2. 一维前缀和（区间和 O(1) 查询）
 *   3. 二维前缀和（矩形区域和 O(1) 查询）
 *   4. 差分数组（区间修改 O(1)，单点查询 O(1)）
 *
 * 运行方式：
 *   g++ -std=c++17 -O2 lesson35_递推与数学基础.cpp -o lesson35 && ./lesson35
 *   按照交互提示选择对应功能进行测试
 */

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

const int MOD = 1e9 + 7;

// ============================================================
// 1. 斐波那契数列 — 递推实现（迭代）
//    时间复杂度：O(n)
//    空间复杂度：O(1)
//    注意：每一步都要取模，防止溢出
// ============================================================
void demo_fibonacci() {
    cout << "\n========== 1. 斐波那契数列（递推） ==========\n";
    cout << "输入 n，计算第 n 个斐波那契数（对 1e9+7 取模）：\n> ";

    int n;
    cin >> n;

    if (n <= 0) {
        cout << "n 必须为正整数" << endl;
        return;
    }
    if (n <= 2) {
        cout << "F(" << n << ") = 1" << endl;
        return;
    }

    long long a = 1, b = 1, c;
    for (int i = 3; i <= n; i++) {
        c = (a + b) % MOD;
        a = b;
        b = c;
    }

    cout << "F(" << n << ") = " << b << " (mod " << MOD << ")" << endl;

    // 额外输出前若干项供参考
    cout << "前 " << min(n, 20) << " 项斐波那契数: ";
    a = 1, b = 1;
    if (min(n, 20) >= 1) cout << 1;
    if (min(n, 20) >= 2) cout << " " << 1;
    for (int i = 3; i <= min(n, 20); i++) {
        c = a + b;
        a = b;
        b = c;
        cout << " " << c;
    }
    cout << endl;
}

// ============================================================
// 2. 一维前缀和
//    构建：pre[i] = pre[i-1] + a[i]
//    查询：[l, r] 的和 = pre[r] - pre[l-1]
//    时间复杂度：预处理 O(n)，查询 O(1)
// ============================================================
void demo_prefix_sum_1d() {
    cout << "\n========== 2. 一维前缀和 ==========\n";
    cout << "输入数组长度 n 和询问次数 q：\n> ";

    int n, q;
    cin >> n >> q;

    vector<long long> a(n + 1);
    vector<long long> pre(n + 1, 0);

    cout << "输入 " << n << " 个整数（空格分隔）：\n> ";
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pre[i] = pre[i - 1] + a[i];
    }

    cout << "\n前缀和数组已构建。\n";
    cout << "前缀和数组: ";
    for (int i = 1; i <= n; i++) {
        cout << pre[i] << " ";
    }
    cout << endl;

    cout << "\n请输入 " << q << " 个询问，每行 l r（1 <= l <= r <= " << n << "）：\n";
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << "区间 [" << l << ", " << r << "] 的和 = "
             << pre[r] - pre[l - 1] << endl;
    }
}

// ============================================================
// 3. 二维前缀和
//    构建：pre[i][j] = pre[i-1][j] + pre[i][j-1] - pre[i-1][j-1] + a[i][j]
//    查询：(x1,y1) 到 (x2,y2) 的和 =
//          pre[x2][y2] - pre[x1-1][y2] - pre[x2][y1-1] + pre[x1-1][y1-1]
//    时间复杂度：预处理 O(n*m)，查询 O(1)
// ============================================================
void demo_prefix_sum_2d() {
    cout << "\n========== 3. 二维前缀和 ==========\n";
    cout << "输入矩阵行数 n、列数 m 和询问次数 q：\n> ";

    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<long long>> a(n + 1, vector<long long>(m + 1));
    vector<vector<long long>> pre(n + 1, vector<long long>(m + 1, 0));

    cout << "输入 " << n << " 行 " << m << " 列的矩阵：\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
            pre[i][j] = pre[i-1][j] + pre[i][j-1] - pre[i-1][j-1] + a[i][j];
        }
    }

    cout << "\n二维前缀和矩阵：\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << setw(4) << pre[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\n请输入 " << q << " 个询问，每行 x1 y1 x2 y2：\n";
    while (q--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        long long sum = pre[x2][y2] - pre[x1-1][y2]
                      - pre[x2][y1-1] + pre[x1-1][y1-1];
        cout << "矩形 (" << x1 << "," << y1 << ") 到 ("
             << x2 << "," << y2 << ") 的和 = " << sum << endl;
    }
}

// ============================================================
// 4. 差分数组（一维）
//    构建：d[i] = a[i] - a[i-1]
//    区间修改 [l, r] 加 x：d[l] += x, d[r+1] -= x
//    还原：对 d 求前缀和
//    时间复杂度：修改 O(1)，还原 O(n)
// ============================================================
void demo_difference_array() {
    cout << "\n========== 4. 差分数组（一维区间修改） ==========\n";
    cout << "输入数组长度 n 和修改操作次数 m：\n> ";

    int n, m;
    cin >> n >> m;

    vector<long long> a(n + 1);
    vector<long long> d(n + 2, 0);  // 多开一个位置，防止 r+1 越界

    cout << "输入 " << n << " 个初始元素：\n> ";
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        d[i] = a[i] - a[i - 1];  // 构建差分数组
    }

    cout << "\n初始差分数组: ";
    for (int i = 1; i <= n; i++) {
        cout << d[i] << " ";
    }
    cout << endl;

    cout << "\n请输入 " << m << " 个区间修改操作，每行 l r x（区间 [l,r] 加上 x）：\n";
    while (m--) {
        int l, r;
        long long x;
        cin >> l >> r >> x;
        d[l] += x;
        d[r + 1] -= x;
        cout << "  已标记：d[" << l << "] += " << x
             << ", d[" << r+1 << "] -= " << x << endl;
    }

    // 对差分数组求前缀和，还原修改后的数组
    cout << "\n修改后的数组: ";
    for (int i = 1; i <= n; i++) {
        d[i] += d[i - 1];
        cout << d[i] << " ";
    }
    cout << endl;
}

// ============================================================
// 额外演示：卡特兰数（递推实现）
// ============================================================
void demo_catalan() {
    cout << "\n========== 5. 卡特兰数（递推） ==========\n";
    cout << "输入 n，计算第 n 个卡特兰数：\n> ";

    int n;
    cin >> n;

    if (n < 0) {
        cout << "n 必须为非负整数" << endl;
        return;
    }

    vector<long long> C(n + 1, 0);
    C[0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            C[i] += C[j] * C[i - 1 - j];
        }
    }

    cout << "卡特兰数 C(" << n << ") = " << C[n] << endl;

    // 输出前几项卡特兰数
    cout << "卡特兰数列前 " << min(n + 1, 15) << " 项: ";
    for (int i = 0; i <= min(n, 14); i++) {
        cout << C[i] << " ";
    }
    cout << endl;
}

// ============================================================
// 主菜单
// ============================================================
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "================================================\n";
    cout << "  CSP-J 第35课：递推与数学基础 — 代码演示\n";
    cout << "================================================\n";
    cout << "  1. 斐波那契数列\n";
    cout << "  2. 一维前缀和\n";
    cout << "  3. 二维前缀和\n";
    cout << "  4. 差分数组\n";
    cout << "  5. 卡特兰数\n";
    cout << "================================================\n";
    cout << "请选择功能 (1-5)：\n> ";

    int choice;
    cin >> choice;

    switch (choice) {
        case 1: demo_fibonacci(); break;
        case 2: demo_prefix_sum_1d(); break;
        case 3: demo_prefix_sum_2d(); break;
        case 4: demo_difference_array(); break;
        case 5: demo_catalan(); break;
        default: cout << "无效选择！" << endl; break;
    }

    cout << "\n演示结束。\n";
    return 0;
}
