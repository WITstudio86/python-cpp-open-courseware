/**
 * 第41课：字符串哈希（String Hashing）
 * 对应CSP-S考纲知识点：
 *   - BKDR 哈希函数设计（base 取 131 / 13331）
 *   - 自然溢出（unsigned long long）与双哈希（大质数取模）
 *   - 子串哈希 O(1) 查询（前缀哈希 + 幂次预处理）
 *   - 二分 + 哈希求最长公共前缀（LCP）
 *   - 哈希去重与模式匹配（unordered_map / set）
 *
 * 包含以下实现：
 *   1. 自然溢出单哈希结构体（StringHash）
 *   2. 双哈希结构体（DoubleHash）
 *   3. 最长公共前缀（LCP）函数
 *   4. 真题1：字符串去重（N 个字符串中不同串的个数）
 *   5. 真题2：最长回文子串（二分 + 正反哈希）
 */

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// 一、自然溢出单哈希（unsigned long long，自动模 2^64）
// 优点：代码简洁、速度快
// 缺点：2^64 不是质数，存在卡哈希风险
// ============================================================
typedef unsigned long long ull;

struct StringHash {
    int n;                  // 字符串长度
    vector<ull> h;          // 前缀哈希数组，h[i] = hash(s[0..i-1])
    vector<ull> p;          // base 的幂次数组，p[i] = base^i
    static const ull BASE = 131;

    // 构造函数：预处理前缀哈希和幂次
    StringHash(const string& s) {
        n = s.size();
        h.resize(n + 1, 0);
        p.resize(n + 1, 1);
        for (int i = 0; i < n; i++) {
            h[i + 1] = h[i] * BASE + s[i];   // 自然溢出
            p[i + 1] = p[i] * BASE;
        }
    }

    // 获取子串 [l, r] 的哈希值（0-based，闭区间）
    // 公式：hash(l, r) = h[r+1] - h[l] * base^{r-l+1}
    ull get(int l, int r) {
        return h[r + 1] - h[l] * p[r - l + 1];
    }

    // 获取整个字符串的哈希值
    ull get_all() {
        return h[n];
    }
};

// ============================================================
// 二、双哈希（两个大质数分别取模，防冲突）
// 模数：1e9+7 和 1e9+9，均为常用质数
// 双哈希冲突概率 ≈ 1/(M1 × M2) ≈ 10^{-18}，几乎不可能冲突
// ============================================================
const int MOD1 = 1000000007;   // 1e9 + 7
const int MOD2 = 1000000009;   // 1e9 + 9
const int BASE_D = 131;

struct DoubleHash {
    int n;
    vector<long long> h1, h2;    // 两个模数下的前缀哈希
    vector<long long> p1, p2;    // 两个模数下的幂次

    DoubleHash(const string& s) {
        n = s.size();
        h1.resize(n + 1, 0); h2.resize(n + 1, 0);
        p1.resize(n + 1, 1); p2.resize(n + 1, 1);
        for (int i = 0; i < n; i++) {
            h1[i + 1] = (h1[i] * BASE_D + s[i]) % MOD1;
            h2[i + 1] = (h2[i] * BASE_D + s[i]) % MOD2;
            p1[i + 1] = (p1[i] * BASE_D) % MOD1;
            p2[i + 1] = (p2[i] * BASE_D) % MOD2;
        }
    }

    // 获取子串 [l, r] 的哈希值，返回 (hash1, hash2)
    pair<long long, long long> get(int l, int r) {
        long long v1 = (h1[r + 1] - h1[l] * p1[r - l + 1] % MOD1 + MOD1) % MOD1;
        long long v2 = (h2[r + 1] - h2[l] * p2[r - l + 1] % MOD2 + MOD2) % MOD2;
        return {v1, v2};
    }

    // 获取整个字符串的双哈希值
    pair<long long, long long> get_all() {
        return {h1[n], h2[n]};
    }
};

// ============================================================
// 三、最长公共前缀（LCP）
// 利用二分 + 哈希在 O(log n) 时间内求两个位置开始的最长公共前缀长度
// ============================================================

// 使用 StringHash 的 LCP
int lcp(const StringHash& sh, int a, int b) {
    int n = sh.n;
    int lo = 0, hi = min(n - a, n - b);  // hi 为可能的最大公共前缀长度
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;      // 取上取整，避免死循环
        if (sh.get(a, a + mid - 1) == sh.get(b, b + mid - 1))
            lo = mid;
        else
            hi = mid - 1;
    }
    return lo;
}

// 比较两个子串的字典序：返回 true 表示 s[l1..r1] < s[l2..r2]
bool less_than(const StringHash& sh, int l1, int r1, int l2, int r2) {
    int len = lcp(sh, l1, l2);
    int len1 = min(r1 - l1 + 1, r2 - l2 + 1);
    if (len == len1) {
        // 一个串是另一个的前缀
        return (r1 - l1 + 1) < (r2 - l2 + 1);
    }
    // 在第一个不同字符处比较
    return sh.get(l1 + len, l1 + len) < sh.get(l2 + len, l2 + len);
}

// ============================================================
// 四、真题1：字符串去重
// 题目：给定 N 个字符串，问有多少个不同的字符串
// 数据范围：N ≤ 10000，总长度 ≤ 1e6
// 算法：对每个字符串计算双哈希值，存入 set 统计不同个数
// 时间复杂度：O(total_length + N log N)
// ============================================================
void solve_distinct_strings() {
    int N;
    cin >> N;
    set<pair<long long, long long>> seen;
    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        DoubleHash dh(s);
        seen.insert(dh.get_all());
    }
    cout << seen.size() << '\n';
}

// ============================================================
// 五、真题2：最长回文子串
// 题目：给定字符串 s，求其最长回文子串的长度
// 数据范围：|s| ≤ 1e5
// 算法：预处理正串哈希和反串哈希，枚举回文中心，二分半径
//       奇数回文：中心为 s[i]，二分半径 r，判断 s[i-r..i+r]
//       偶数回文：中心在 s[i] 和 s[i+1] 之间，二分半径 r，判断 s[i-r+1..i+r]
// 时间复杂度：O(n log n)
// ============================================================
void solve_longest_palindrome() {
    string s;
    cin >> s;
    int n = s.size();

    // 预处理正串哈希
    StringHash forward_hash(s);

    // 预处理反串哈希（将 s 反转后建哈希）
    string rev_s = s;
    reverse(rev_s.begin(), rev_s.end());
    StringHash reverse_hash(rev_s);

    int ans = 1;  // 至少为 1（单个字符）

    // 枚举奇数长度回文的中心
    for (int i = 0; i < n; i++) {
        int lo = 0, hi = min(i, n - 1 - i);  // hi = 最大可能的半径
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;
            // 正串区间 [i-mid, i+mid]
            // 对应反串区间 [n-1-(i+mid), n-1-(i-mid)]
            ull fwd = forward_hash.get(i - mid, i + mid);
            ull rev = reverse_hash.get(n - 1 - (i + mid), n - 1 - (i - mid));
            if (fwd == rev)
                lo = mid;
            else
                hi = mid - 1;
        }
        ans = max(ans, 2 * lo + 1);
    }

    // 枚举偶数长度回文的中心（在 i 和 i+1 之间）
    for (int i = 0; i < n - 1; i++) {
        if (s[i] != s[i + 1]) continue;  // 中心两个字符不同则不可能有偶数回文
        int lo = 0, hi = min(i + 1, n - 1 - i);
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;
            // 正串区间 [i-mid+1, i+mid]
            ull fwd = forward_hash.get(i - mid + 1, i + mid);
            // 对应反串区间
            ull rev = reverse_hash.get(n - 1 - (i + mid), n - 1 - (i - mid + 1));
            if (fwd == rev)
                lo = mid;
            else
                hi = mid - 1;
        }
        if (lo > 0) ans = max(ans, 2 * lo);
    }

    cout << ans << '\n';
}

// ============================================================
// 六、辅助函数：计算单个字符串的哈希值
// ============================================================
ull single_hash(const string& s) {
    ull h = 0;
    for (char c : s) {
        h = h * 131 + c;   // 自然溢出
    }
    return h;
}

pair<long long, long long> dual_hash(const string& s) {
    long long h1 = 0, h2 = 0;
    for (char c : s) {
        h1 = (h1 * 131 + c) % MOD1;
        h2 = (h2 * 131 + c) % MOD2;
    }
    return {h1, h2};
}

// ============================================================
// 七、测试用 main 函数
// ============================================================
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ---------- 测试1：子串哈希 O(1) 查询 ----------
    cout << "========== 测试1：子串哈希查询 ==========" << endl;
    {
        string s = "abcabcabc";
        StringHash sh(s);
        // s[0..2] = "abc", s[3..5] = "abc", s[6..8] = "abc" 应该相等
        cout << "hash(\"abc\") = " << sh.get(0, 2) << endl;
        cout << "hash(s[3..5]) = " << sh.get(3, 5) << endl;
        cout << "hash(s[6..8]) = " << sh.get(6, 8) << endl;
        cout << "前两个子串相等: " << (sh.get(0, 2) == sh.get(3, 5) ? "YES" : "NO") << endl;
        cout << endl;
    }

    // ---------- 测试2：LCP ----------
    cout << "========== 测试2：最长公共前缀 ==========" << endl;
    {
        string s = "ababcababc";
        StringHash sh(s);
        // s[0..] = "ababcababc", s[5..] = "ababc"
        int len = lcp(sh, 0, 5);
        cout << "s[0..] 和 s[5..] 的 LCP 长度: " << len << endl;
        cout << "（预期 5，因为 s[0..4] == s[5..9] == \"ababc\"）" << endl;
        cout << endl;
    }

    // ---------- 测试3：双哈希 ----------
    cout << "========== 测试3：双哈希 ==========" << endl;
    {
        string a = "helloworld";
        string b = "helloworld";
        string c = "helloworlD";
        DoubleHash dh_a(a), dh_b(b), dh_c(c);
        cout << "a == b (双哈希): " << (dh_a.get_all() == dh_b.get_all() ? "YES" : "NO") << endl;
        cout << "a == c (双哈希): " << (dh_a.get_all() == dh_c.get_all() ? "YES" : "NO") << endl;
        cout << endl;
    }

    // ---------- 测试4：字符串去重 ----------
    cout << "========== 测试4：字符串去重 ==========" << endl;
    {
        // 模拟输入：5 个字符串，其中 2 个重复
        vector<string> test = {"apple", "banana", "apple", "cherry", "banana"};
        set<pair<long long, long long>> seen;
        for (const string& s : test) {
            seen.insert(dual_hash(s));
        }
        cout << "不同字符串个数: " << seen.size() << "（预期 3）" << endl;
        cout << endl;
    }

    // ---------- 测试5：最长回文子串 ----------
    cout << "========== 测试5：最长回文子串 ==========" << endl;
    {
        // 手动测试（不依赖 cin）
        string s = "ababa";
        int n = s.size();
        StringHash fwd(s);
        string rev = s; reverse(rev.begin(), rev.end());
        StringHash rev_hash(rev);
        int ans = 1;
        // 奇数
        for (int i = 0; i < n; i++) {
            int lo = 0, hi = min(i, n - 1 - i);
            while (lo < hi) {
                int mid = (lo + hi + 1) / 2;
                ull a = fwd.get(i - mid, i + mid);
                ull b = rev_hash.get(n - 1 - (i + mid), n - 1 - (i - mid));
                if (a == b) lo = mid;
                else hi = mid - 1;
            }
            ans = max(ans, 2 * lo + 1);
        }
        // 偶数
        for (int i = 0; i < n - 1; i++) {
            if (s[i] != s[i + 1]) continue;
            int lo = 0, hi = min(i + 1, n - 1 - i);
            while (lo < hi) {
                int mid = (lo + hi + 1) / 2;
                ull a = fwd.get(i - mid + 1, i + mid);
                ull b = rev_hash.get(n - 1 - (i + mid), n - 1 - (i - mid + 1));
                if (a == b) lo = mid;
                else hi = mid - 1;
            }
            if (lo > 0) ans = max(ans, 2 * lo);
        }
        cout << "字符串 \"ababa\" 的最长回文子串长度: " << ans << "（预期 5）" << endl;
        cout << endl;
    }

    // ---------- 真题测试（取消注释以使用标准输入） ----------
    // solve_distinct_strings();
    // solve_longest_palindrome();

    return 0;
}
