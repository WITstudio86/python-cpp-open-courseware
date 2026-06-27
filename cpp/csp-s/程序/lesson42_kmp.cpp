/**
 * 第42课：KMP算法（Knuth-Morris-Pratt）
 * 对应CSP-S考纲知识点：
 *   - KMP 字符串匹配算法（next 数组 / 前缀函数）
 *   - next 数组的递推构建（双指针 i, j）
 *   - 线性时间复杂度 O(n+m) 的 KMP 匹配过程
 *   - 最小循环节定理：cycle = len - next[len-1]
 *   - KMP 扩展：前缀出现次数、border 统计
 *
 * 包含以下实现：
 *   1. get_next 函数（两种写法：下标从 0 开始 / 从 1 开始）
 *   2. kmp_search 函数（查找所有出现位置）
 *   3. kmp_count 函数（统计出现次数，允许重叠）
 *   4. 最小循环节计算函数
 *   5. 真题1：KMP 匹配统计出现次数
 *   6. 真题2：最小循环节与补充成循环串
 */

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// 一、get_next 函数：构建 next 数组（下标从 0 开始）
// next[i] = 前缀 P[0..i] 的最长公共前后缀长度（真前缀 & 真后缀）
// 通俗解释：next[i] = k 意味着 P[0..k-1] == P[i-k+1..i]
// 时间复杂度：O(m)，其中 m = |P|
// ============================================================
vector<int> get_next(const string& P) {
    int m = P.size();
    vector<int> next(m, 0);
    int j = 0;  // j 表示「当前已匹配的前缀长度」，也是「待比较的前缀字符下标」

    // i 从 1 开始，因为 next[0] 恒为 0（长度为 1 的前缀没有真前后缀）
    for (int i = 1; i < m; i++) {
        // 失配时，j 回退到 next[j-1]（利用已计算的 next 信息）
        while (j > 0 && P[i] != P[j]) {
            j = next[j - 1];
        }
        // 匹配成功，j 前进
        if (P[i] == P[j]) {
            j++;
        }
        next[i] = j;
    }
    return next;
}

// ============================================================
// 二、get_next 函数：下标从 1 开始的版本（部分教材使用）
// next[1] = 0, next[i] 表示 P[1..i-1] 的最长公共前后缀长度
// 注意：需要将 P 变为 1-indexed（P = " " + original_P）
// ============================================================
vector<int> get_next_1based(const string& P) {
    // 假设传入的 P 已经是 1-indexed：P[0] 为占位符，实际内容从 P[1] 开始
    int m = P.size() - 1;  // 实际字符数
    vector<int> next(m + 2, 0);
    next[1] = 0;
    int j = 0;
    for (int i = 2; i <= m; i++) {
        while (j > 0 && P[i] != P[j + 1]) {
            j = next[j];
        }
        if (P[i] == P[j + 1]) {
            j++;
        }
        next[i] = j;
    }
    return next;
}

// ============================================================
// 三、kmp_search：查找模式串 P 在文本串 T 中的所有出现位置
// 返回起始下标列表（0-based）
// 时间复杂度：O(n+m)
// ============================================================
vector<int> kmp_search(const string& T, const string& P) {
    vector<int> positions;
    int n = T.size(), m = P.size();
    if (m == 0) return positions;

    vector<int> next = get_next(P);
    int j = 0;  // 已匹配的模式串长度

    for (int i = 0; i < n; i++) {
        // 失配：j 通过 next 数组跳转
        while (j > 0 && T[i] != P[j]) {
            j = next[j - 1];
        }
        // 匹配：j 前进
        if (T[i] == P[j]) {
            j++;
        }
        // 完全匹配
        if (j == m) {
            positions.push_back(i - m + 1);  // 起始位置
            j = next[j - 1];  // 允许重叠，继续寻找下一个匹配
        }
    }
    return positions;
}

// ============================================================
// 四、kmp_count：统计模式串 P 在文本串 T 中出现的次数
// 允许重叠匹配，如需不重叠匹配只需将 j = next[j-1] 改为 j = 0
// ============================================================
int kmp_count(const string& T, const string& P) {
    int n = T.size(), m = P.size();
    if (m == 0) return 0;

    vector<int> next = get_next(P);
    int j = 0, cnt = 0;

    for (int i = 0; i < n; i++) {
        while (j > 0 && T[i] != P[j]) j = next[j - 1];
        if (T[i] == P[j]) j++;
        if (j == m) {
            cnt++;
            j = next[j - 1];  // 允许重叠
        }
    }
    return cnt;
}

// 不重叠版本
int kmp_count_non_overlap(const string& T, const string& P) {
    int n = T.size(), m = P.size();
    if (m == 0) return 0;

    vector<int> next = get_next(P);
    int j = 0, cnt = 0;

    for (int i = 0; i < n; i++) {
        while (j > 0 && T[i] != P[j]) j = next[j - 1];
        if (T[i] == P[j]) j++;
        if (j == m) {
            cnt++;
            j = 0;  // 不允许重叠，完全从头开始
        }
    }
    return cnt;
}

// ============================================================
// 五、最小循环节计算
// 定理：对长度为 len 的字符串 s，
//   设 cycle = len - next[len-1]
//   若 len % cycle == 0，则最小循环节长度为 cycle
//   否则不存在完整循环节，最小循环节长度为 len
// ============================================================

// 返回最小循环节长度
int min_cycle_len(const string& s) {
    int n = s.size();
    if (n == 0) return 0;
    vector<int> next = get_next(s);
    int cycle = n - next[n - 1];
    if (n % cycle == 0) return cycle;
    return n;  // 整个字符串作为循环节
}

// 获取循环节的重复次数（若存在循环节）
// 返回 pair(cycle_len, repeat_count)，若不存在循环节 repeat_count = 1
pair<int, int> get_cycle_info(const string& s) {
    int n = s.size();
    vector<int> next = get_next(s);
    int cycle = n - next[n - 1];
    if (n % cycle == 0 && cycle < n) {
        return {cycle, n / cycle};
    }
    return {n, 1};
}

// 补充最少字符使其成为循环串：返回需要添加的字符数，以及补充后的字符串
// 补充规则：cycle = len - next[len-1]，需要补充 (cycle - len % cycle) % cycle 个字符
int chars_needed_for_cycle(const string& s) {
    int n = s.size();
    vector<int> next = get_next(s);
    int cycle = n - next[n - 1];
    if (n % cycle == 0) return 0;  // 已经是循环串
    return cycle - n % cycle;
}

string complete_cycle(const string& s) {
    int n = s.size();
    vector<int> next = get_next(s);
    int cycle = n - next[n - 1];
    int need = (cycle - n % cycle) % cycle;
    // 补充的字符来自 s 的前面部分（按 cycle 循环）
    string result = s;
    for (int i = 0; i < need; i++) {
        result += s[i % cycle];  // 按循环节补充
    }
    return result;
}

// ============================================================
// 六、扩展应用：求每个前缀在自身中的出现次数
// 原理：cnt[i] 表示前缀 P[0..i] 作为 P 的 border 出现的次数
//       从后向前遍历 i，将 cnt[next[i]-1] += cnt[i]
// ============================================================
vector<int> prefix_occurrence_count(const string& s) {
    int n = s.size();
    vector<int> next = get_next(s);
    vector<int> cnt(n, 1);  // 每个前缀至少自身出现一次

    // 从后向前累加（因为 next[i] < i+1，所以从大到小遍历安全）
    for (int i = n - 1; i >= 0; i--) {
        if (next[i] > 0) {
            cnt[next[i] - 1] += cnt[i];
        }
    }
    return cnt;
}

// ============================================================
// 七、真题1：KMP 匹配统计出现次数
// 题目：给定文本串 T 和模式串 P，统计 P 在 T 中出现的次数（允许重叠）
// 数据范围：|T| ≤ 1e6, |P| ≤ 1e5
// ============================================================
void solve_problem1() {
    string T, P;
    cin >> T >> P;
    cout << kmp_count(T, P) << '\n';
}

// ============================================================
// 八、真题2：最小循环节
// 题目：给定字符串 s，
//   1. 若 s 由循环节重复构成，输出循环节和 k
//   2. 否则输出需要添加的最少字符数及补充后的字符串
// 数据范围：|s| ≤ 1e6
// ============================================================
void solve_problem2() {
    string s;
    cin >> s;
    int n = s.size();
    vector<int> next = get_next(s);
    int cycle = n - next[n - 1];

    if (n % cycle == 0 && cycle < n) {
        // 存在完整循环节
        cout << "循环节: " << s.substr(0, cycle) << '\n';
        cout << "重复次数 k = " << n / cycle << '\n';
    } else {
        // 需要补充
        int need = cycle - n % cycle;
        cout << "需要添加 " << need << " 个字符\n";
        string added = s;
        for (int i = 0; i < need; i++) {
            added += s[i % cycle];
        }
        cout << "补充后: " << added << '\n';
    }
}

// ============================================================
// 九、测试用 main 函数
// ============================================================
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ---------- 测试1：next 数组构建 ----------
    cout << "========== 测试1：next 数组 ==========" << endl;
    {
        string P = "ababc";
        vector<int> next = get_next(P);
        cout << "P = \"ababc\"" << endl;
        for (int i = 0; i < (int)next.size(); i++) {
            cout << "  next[" << i << "] = " << next[i]
                 << "  (前缀 P[0.." << i << "]=\"" << P.substr(0, i + 1)
                 << "\" 的最长公共前后缀)" << endl;
        }
        cout << "预期: next = [0, 0, 1, 2, 0]" << endl;
        cout << endl;
    }

    // ---------- 测试2：KMP 搜索 ----------
    cout << "========== 测试2：KMP 搜索 ==========" << endl;
    {
        string T = "ababcabcababc";
        string P = "abc";
        vector<int> pos = kmp_search(T, P);
        cout << "T = \"" << T << "\", P = \"" << P << "\"" << endl;
        cout << "出现位置: ";
        for (int p : pos) cout << p << " ";
        cout << "(预期: 2 5 10)" << endl;

        int cnt = kmp_count(T, P);
        cout << "出现次数: " << cnt << " (预期: 3)" << endl;
        cout << endl;
    }

    // ---------- 测试3：允许重叠 vs 不重叠 ----------
    cout << "========== 测试3：重叠 vs 不重叠 ==========" << endl;
    {
        string T = "aaaaa";
        string P = "aa";
        cout << "T = \"aaaaa\", P = \"aa\"" << endl;
        cout << "允许重叠次数: " << kmp_count(T, P)
             << " (预期: 4, 位置: 0 1 2 3)" << endl;
        cout << "不重叠次数:   " << kmp_count_non_overlap(T, P)
             << " (预期: 2, 位置: 0 2)" << endl;
        cout << endl;
    }

    // ---------- 测试4：最小循环节 ----------
    cout << "========== 测试4：最小循环节 ==========" << endl;
    {
        vector<string> tests = {"abcabcabc", "ababab", "abcab", "aaaa"};
        for (const string& s : tests) {
            auto [cyc, k] = get_cycle_info(s);
            int need = chars_needed_for_cycle(s);
            cout << "s = \"" << s << "\": 循环节长度=" << cyc;
            if (k > 1) cout << ", 重复次数=" << k;
            if (need > 0) cout << ", 需要补充 " << need << " 个字符 -> \""
                               << complete_cycle(s) << "\"";
            cout << endl;
        }
        cout << "预期:" << endl;
        cout << "  abcabcabc: cycle=3, k=3" << endl;
        cout << "  ababab:    cycle=2, k=3" << endl;
        cout << "  abcab:     cycle=3, need=1, -> abcabc" << endl;
        cout << "  aaaa:      cycle=1, k=4" << endl;
        cout << endl;
    }

    // ---------- 测试5：前缀出现次数 ----------
    cout << "========== 测试5：前缀出现次数 ==========" << endl;
    {
        string s = "ababa";
        vector<int> cnt = prefix_occurrence_count(s);
        cout << "s = \"ababa\"" << endl;
        for (int i = 0; i < (int)cnt.size(); i++) {
            cout << "  前缀 \"" << s.substr(0, i + 1) << "\" 出现次数: " << cnt[i] << endl;
        }
        cout << endl;
    }

    // ---------- 真题入口（取消注释以使用标准输入） ----------
    // solve_problem1();
    // solve_problem2();

    return 0;
}
