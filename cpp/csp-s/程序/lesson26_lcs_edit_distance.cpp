/*
 * 第26课：LCS（最长公共子序列）与编辑距离
 * 考纲知识点：LCS的二维DP与滚动数组优化、编辑距离DP、序列比对思想
 */

#include <bits/stdc++.h>
using namespace std;

// ==================== 1. LCS - O(n*m) 二维DP ====================
// dp[i][j] 表示 s1 的前 i 个字符与 s2 的前 j 个字符的 LCS 长度
int lcs(const string& s1, const string& s2) {
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s1[i-1] == s2[j-1])
                dp[i][j] = dp[i-1][j-1] + 1;
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
    return dp[n][m];
}

// ==================== 2. LCS - O(min(n,m)) 滚动数组优化 ====================
// 核心：dp[i][j] 只依赖于 dp[i-1][j-1]（左上）、dp[i-1][j]（上）、dp[i][j-1]（左）
// 使用一维数组 + prev 变量保存左上角的值
int lcs_optimized(const string& s1, const string& s2) {
    int n = s1.size(), m = s2.size();
    vector<int> dp(m + 1, 0);
    for (int i = 1; i <= n; ++i) {
        int prev = 0;  // 保存 dp[i-1][j-1]
        for (int j = 1; j <= m; ++j) {
            int temp = dp[j];  // 暂存 dp[i-1][j]，下一轮的左上角
            if (s1[i-1] == s2[j-1])
                dp[j] = prev + 1;
            else
                dp[j] = max(dp[j], dp[j-1]);
            prev = temp;
        }
    }
    return dp[m];
}

// ==================== 3. LCS 路径回溯（构造子序列） ====================
// 使用 dir 数组记录转移方向：0=左上(match), 1=上, 2=左
string lcs_trace(const string& s1, const string& s2) {
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    vector<vector<int>> dir(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
                dir[i][j] = 0;  // 来自左上（匹配）
            } else if (dp[i-1][j] >= dp[i][j-1]) {
                dp[i][j] = dp[i-1][j];
                dir[i][j] = 1;  // 来自上方
            } else {
                dp[i][j] = dp[i][j-1];
                dir[i][j] = 2;  // 来自左方
            }
        }
    }

    // 从右下角回溯
    string result;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (dir[i][j] == 0) {
            result += s1[i-1];  // 或 s2[j-1]
            --i; --j;
        } else if (dir[i][j] == 1) {
            --i;
        } else {
            --j;
        }
    }
    reverse(result.begin(), result.end());
    return result;
}

// ==================== 4. 编辑距离（Levenshtein 距离）标准DP ====================
// 操作：插入、删除、替换，各代价为1
int edit_distance(const string& word1, const string& word2) {
    int n = word1.size(), m = word2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));

    // 初始化边界
    for (int i = 0; i <= n; ++i) dp[i][0] = i;  // 全部删除
    for (int j = 0; j <= m; ++j) dp[0][j] = j;  // 全部插入

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (word1[i-1] == word2[j-1]) {
                dp[i][j] = dp[i-1][j-1];  // 字符相同，无需操作
            } else {
                dp[i][j] = 1 + min({dp[i-1][j],      // 删除 word1[i-1]
                                    dp[i][j-1],      // 插入 word2[j-1]
                                    dp[i-1][j-1]});  // 替换
            }
        }
    }
    return dp[n][m];
}

// ==================== 5. 编辑距离 - 滚动数组空间优化 ====================
int edit_distance_optimized(const string& word1, const string& word2) {
    int n = word1.size(), m = word2.size();
    vector<int> dp(m + 1);
    iota(dp.begin(), dp.end(), 0);  // dp[j] = j

    for (int i = 1; i <= n; ++i) {
        int prev = dp[0];  // dp[i-1][0]
        dp[0] = i;         // dp[i][0] = i
        for (int j = 1; j <= m; ++j) {
            int temp = dp[j];  // 暂存 dp[i-1][j]
            if (word1[i-1] == word2[j-1]) {
                dp[j] = prev;
            } else {
                dp[j] = 1 + min({dp[j],      // dp[i-1][j]（删除）
                                 dp[j-1],    // dp[i][j-1]（插入）
                                 prev});     // dp[i-1][j-1]（替换）
            }
            prev = temp;
        }
    }
    return dp[m];
}

// ==================== 6. 编辑距离带权重（自定义操作代价） ====================
// insert_cost, delete_cost, replace_cost 可自定义
int edit_distance_weighted(const string& word1, const string& word2,
                           int ins, int del, int rep) {
    int n = word1.size(), m = word2.size();
    vector<int> dp(m + 1);
    for (int j = 0; j <= m; ++j) dp[j] = j * ins;  // 插入代价

    for (int i = 1; i <= n; ++i) {
        int prev = dp[0];
        dp[0] = i * del;  // 删除代价
        for (int j = 1; j <= m; ++j) {
            int temp = dp[j];
            if (word1[i-1] == word2[j-1]) {
                dp[j] = prev;
            } else {
                dp[j] = min({dp[j] + del,      // 删除
                             dp[j-1] + ins,    // 插入
                             prev + rep});     // 替换
            }
            prev = temp;
        }
    }
    return dp[m];
}

// ==================== 7. 真题1：LCS 模板题 ====================
// 题目：给定两个字符串，求最长公共子序列长度
void solve_lcs_template() {
    string s1, s2;
    cin >> s1 >> s2;
    cout << lcs(s1, s2) << endl;
}

// ==================== 8. 真题2：编辑距离（字符串变换） ====================
// 题目：将 word1 转换为 word2 的最少操作次数
void solve_edit_distance() {
    string word1, word2;
    cin >> word1 >> word2;
    cout << edit_distance(word1, word2) << endl;
}

// ==================== 9. 真题3：判断子序列（编辑距离的简化版） ====================
// 判断 s 是否为 t 的子序列（双指针法，O(n+m)）
// 这是编辑距离中"只允许删除"的特例
bool is_subsequence(const string& s, const string& t) {
    int i = 0, j = 0;
    while (i < (int)s.size() && j < (int)t.size()) {
        if (s[i] == t[j]) ++i;
        ++j;
    }
    return i == (int)s.size();
}

// ==================== 10. 最短公共超序列（Shortest Common Supersequence） ====================
// SCS 长度 = n + m - LCS 长度
// 这是因为 LCS 中的字符在两个字符串中都被使用，其余字符各出现一次
int shortest_common_supersequence_length(const string& s1, const string& s2) {
    return s1.size() + s2.size() - lcs(s1, s2);
}

// ==================== 主函数：测试与演示 ====================
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // -------------------- LCS 测试 --------------------
    string s1 = "ABCBDAB", s2 = "BDCABA";
    cout << "=== LCS 测试 ===" << endl;
    cout << "s1 = " << s1 << ", s2 = " << s2 << endl;
    cout << "LCS 二维DP: " << lcs(s1, s2) << endl;
    cout << "LCS 滚动优化: " << lcs_optimized(s1, s2) << endl;
    cout << "LCS 路径回溯: " << lcs_trace(s1, s2) << endl;
    cout << "最短公共超序列长度: " << shortest_common_supersequence_length(s1, s2) << endl;
    cout << endl;

    // -------------------- 编辑距离测试 --------------------
    cout << "=== 编辑距离测试 ===" << endl;
    string w1 = "horse", w2 = "ros";
    cout << "word1 = " << w1 << ", word2 = " << w2 << endl;
    cout << "编辑距离 二维DP: " << edit_distance(w1, w2) << endl;
    cout << "编辑距离 滚动优化: " << edit_distance_optimized(w1, w2) << endl;
    cout << "编辑距离 带权重(ins=2,del=1,rep=3): "
         << edit_distance_weighted(w1, w2, 2, 1, 3) << endl;
    cout << endl;

    // -------------------- 更多测试 --------------------
    cout << "=== 更多测试 ===" << endl;
    string a1 = "abcdef", a2 = "acef";
    cout << "LCS('abcdef', 'acef') = " << lcs(a1, a2) << endl;
    cout << "LCS path = " << lcs_trace(a1, a2) << endl;

    string b1 = "intention", b2 = "execution";
    cout << "EditDist('intention', 'execution') = " << edit_distance(b1, b2) << endl;

    cout << "Is 'abc' subsequence of 'ahbgdc'? "
         << (is_subsequence("abc", "ahbgdc") ? "Yes" : "No") << endl;

    return 0;
}
