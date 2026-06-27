# 第26课：LCS（最长公共子序列）与编辑距离

## 一、考纲要求

- 最长公共子序列（LCS）问题的 DP 解法
- LCS 的空间优化（滚动数组）
- 编辑距离（Levenshtein 距离）的 DP 解法
- 编辑距离的空间优化
- 序列比对算法思想（Needleman-Wunsch / Smith-Waterman）
- 字符串 DP 的常见变形与技巧

## 二、知识精讲

### 2.1 LCS 问题定义

**问题描述：** 给定两个字符串（或序列）s1 和 s2，求它们的最长公共子序列的长度。子序列不要求连续，但要求保持原序列中的相对顺序。

例如：s1 = "ABCBDAB"，s2 = "BDCABA"，最长公共子序列为 "BCBA" 或 "BDAB"，长度为 4。

### 2.2 LCS 的 O(n×m) DP 解法

**状态定义：** `dp[i][j]` 表示 s1 的前 i 个字符与 s2 的前 j 个字符的最长公共子序列长度。

**状态转移方程：**
```
dp[i][j] = dp[i-1][j-1] + 1                 (当 s1[i-1] == s2[j-1] 时)
dp[i][j] = max(dp[i-1][j], dp[i][j-1])     (当 s1[i-1] != s2[j-1] 时)
```

**含义解释：**
- 当两个字符相同时，这个字符必然可以被包含在 LCS 中，因此 `dp[i][j] = dp[i-1][j-1] + 1`
- 当两个字符不同时，当前字符不能同时出现在 LCS 中，因此从两个方向取最大值：要么跳过 s1 的当前字符，要么跳过 s2 的当前字符

**初始化：** `dp[0][j] = dp[i][0] = 0`（任一序列为空时，LCS 长度为 0）

**最终答案：** `dp[n][m]`

**时间复杂度：** O(n×m)，空间复杂度：O(n×m)

**DP 表格示例（s1="ABC", s2="AC"）：**

| dp | ""| A | C |
|----|---|---|---|
| "" | 0 | 0 | 0 |
| A  | 0 | 1 | 1 |
| B  | 0 | 1 | 1 |
| C  | 0 | 1 | 2 |

### 2.3 LCS 空间优化：滚动数组

**核心观察：** `dp[i][j]` 只依赖于 `dp[i-1][j-1]` 和 `dp[i-1][j]` 以及 `dp[i][j-1]`，即只依赖于上一行和当前行的左侧。

**滚动数组方案一（两行交替）：**
使用 `dp[2][m+1]`，用 `cur = i % 2` 和 `pre = 1 - cur` 交替。
```cpp
int dp[2][MAXM];
int cur = 0;
for (int i = 1; i <= n; ++i) {
    cur ^= 1;
    for (int j = 1; j <= m; ++j) {
        if (s1[i-1] == s2[j-1])
            dp[cur][j] = dp[cur^1][j-1] + 1;
        else
            dp[cur][j] = max(dp[cur^1][j], dp[cur][j-1]);
    }
}
```

**滚动数组方案二（一维数组倒序/特殊更新）：**
LCS 不能简单地用一维数组正序更新，因为 `dp[i][j]` 同时依赖 `dp[i-1][j]`（上一行的 j 列）、`dp[i][j-1]`（当前行的 j-1 列）和 `dp[i-1][j-1]`（上一行的 j-1 列）。如果直接用一维数组正序更新，`dp[j]` 会先被覆盖，导致 `dp[j-1]` 的依赖出错。

**正确的一维优化：** 需要额外变量保存左上角的值：
```cpp
vector<int> dp(m + 1, 0);
for (int i = 1; i <= n; ++i) {
    int prev = 0;  // 保存 dp[i-1][j-1]
    for (int j = 1; j <= m; ++j) {
        int temp = dp[j];  // 暂存当前值（下一轮的左上角）
        if (s1[i-1] == s2[j-1])
            dp[j] = prev + 1;
        else
            dp[j] = max(dp[j], dp[j-1]);
        prev = temp;
    }
}
```

**要点：** 滚动数组优化后，空间复杂度从 O(n×m) 降至 O(min(n, m))。初始化边界条件仍然必须正确：dp 数组初始化为全 0。

### 2.4 LCS 路径回溯

若要构造最长公共子序列本身而非仅长度，需要额外记录转移方向。

**方法：** 维护一个 `dire[i][j]` 记录 `dp[i][j]` 是从哪个方向转移来的：
- 0：从左上角来（匹配）
- 1：从上方来
- 2：从左方来

然后从 `dp[n][m]` 反向回溯，当 `dire[i][j] == 0` 时将 `s1[i-1]`（或 `s2[j-1]`）加入结果。

**注意：** LCS 可能不唯一！上述回溯只能找到其中一种。

**如果使用了滚动数组优化，则无法直接回溯路径。** 此时要么保留完整的二维 DP 表（n×m 不大时），要么使用其他技术（如 Hirschberg 算法，分治+DP 实现 O(n×m) 时间、O(min(n,m)) 空间且可回溯）。

### 2.5 编辑距离（Levenshtein 距离）

**问题定义：** 给定两个字符串 word1 和 word2，计算将 word1 转换为 word2 所需的最少操作次数。允许的操作有：
- 插入一个字符
- 删除一个字符
- 替换一个字符

**状态定义：** `dp[i][j]` 表示 word1 的前 i 个字符转换为 word2 的前 j 个字符所需的最小操作数。

**状态转移方程：**
```
dp[i][j] = dp[i-1][j-1]                          (当 word1[i-1] == word2[j-1] 时)
dp[i][j] = 1 + min(dp[i-1][j],                   删除
                   dp[i][j-1],                   插入
                   dp[i-1][j-1])                 替换
```

**初始化：**
- `dp[0][j] = j`（空串变为 word2[0..j)，需要插入 j 次）
- `dp[i][0] = i`（word1[0..i) 变为空串，需要删除 i 次）

**最终答案：** `dp[n][m]`

**复杂度：** O(n×m) 时间，O(n×m) 空间。可滚动数组优化到 O(min(n, m)) 空间。

### 2.6 编辑距离的空间优化

与 LCS 类似，编辑距离也可以优化到一维 + 额外变量：

```cpp
vector<int> dp(m + 1);
iota(dp.begin(), dp.end(), 0);  // dp[j] = j

for (int i = 1; i <= n; ++i) {
    int prev = dp[0];  // dp[i-1][0]
    dp[0] = i;         // dp[i][0]
    for (int j = 1; j <= m; ++j) {
        int temp = dp[j];
        if (word1[i-1] == word2[j-1])
            dp[j] = prev;
        else
            dp[j] = 1 + min({dp[j], dp[j-1], prev});
        prev = temp;
    }
}
```

### 2.7 序列比对算法简介

**Needleman-Wunsch 算法（全局比对）：**
- 用于将两条序列从头到尾进行全局比对
- 本质上是 LCS 的推广：引入匹配得分、错配罚分和空位罚分（gap penalty）
- 转移方程：`dp[i][j] = max(dp[i-1][j-1] + score(i,j), dp[i-1][j] + gap, dp[i][j-1] + gap)`

**Smith-Waterman 算法（局部比对）：**
- 用于寻找两条序列中相似度最高的局部片段
- 与 NW 算法的区别：允许从任意位置开始，`dp[i][j]` 允许为 0（重新开始）
- 转移方程：`dp[i][j] = max(0, dp[i-1][j-1] + score(i,j), dp[i-1][j] + gap, dp[i][j-1] + gap)`

这两个算法是生物信息学中序列比对的基础，其 DP 思想与 LCS/编辑距离一脉相承。

## 三、代码模板

### 3.1 LCS 二维 DP

```cpp
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
```

### 3.2 LCS 一维滚动优化

```cpp
int lcs_optimized(const string& s1, const string& s2) {
    int n = s1.size(), m = s2.size();
    vector<int> dp(m + 1, 0);
    for (int i = 1; i <= n; ++i) {
        int prev = 0;  // dp[i-1][j-1]
        for (int j = 1; j <= m; ++j) {
            int temp = dp[j];
            if (s1[i-1] == s2[j-1])
                dp[j] = prev + 1;
            else
                dp[j] = max(dp[j], dp[j-1]);
            prev = temp;
        }
    }
    return dp[m];
}
```

### 3.3 LCS 路径回溯

```cpp
string lcs_trace(const string& s1, const string& s2) {
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    vector<vector<int>> dir(n + 1, vector<int>(m + 1, 0));
    // dir: 0=左上(match), 1=上, 2=左
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
                dir[i][j] = 0;
            } else if (dp[i-1][j] >= dp[i][j-1]) {
                dp[i][j] = dp[i-1][j];
                dir[i][j] = 1;
            } else {
                dp[i][j] = dp[i][j-1];
                dir[i][j] = 2;
            }
        }
    }
    
    // 回溯
    string result;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (dir[i][j] == 0) {
            result += s1[i-1];
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
```

### 3.4 编辑距离 DP

```cpp
int edit_distance(const string& word1, const string& word2) {
    int n = word1.size(), m = word2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    for (int i = 0; i <= n; ++i) dp[i][0] = i;
    for (int j = 0; j <= m; ++j) dp[0][j] = j;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (word1[i-1] == word2[j-1])
                dp[i][j] = dp[i-1][j-1];
            else
                dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
        }
    }
    return dp[n][m];
}
```

## 四、易错点与优化技巧

### 4.1 易错点

| 易错点 | 说明 | 正确做法 |
|--------|------|----------|
| DP 下标混淆 | 字符串下标从 0 开始，DP 表下标从 1 开始 | 统一使用 `s[i-1]` 访问字符串 |
| 边界初始化遗漏 | LCS 的 `dp[0][j]` 和 `dp[i][0]` 必须为 0 | 创建 DP 表时就全部初始化为 0 |
| 编辑距离初始化错误 | `dp[i][0] = i`（删除 i 次），`dp[0][j] = j`（插入 j 次） | 不能遗漏或颠倒 |
| 滚动数组更新顺序 | 一维优化的更新必须注意"左上角"依赖 | 使用 `prev` 变量保存 `dp[i-1][j-1]` |
| 路径回溯方向 | LCS 的回溯方向判断需与 DP 转移一致 | 统一使用 dir 数组记录方向 |

### 4.2 优化技巧

1. **空间优化：** 当 n 和 m 很大（如 5000+）但内存有限时，必须使用滚动数组。注意使较小的维度作为内层循环以节省更多空间。
2. **时间优化：** LCS 在一般情况下没有低于 O(n×m) 的算法（SETH 假设）。但对于特殊数据（如字符集很小、字符串高度相似），可以使用位运算优化（bitset）。
3. **LCS 与 LIS 的关系：** 如果其中一个序列的元素是互不相同的，可以将 LCS 问题转化为 LIS 问题，从而使用 O(n log n) 算法。
   - 具体做法：将 s1 中的每个字符映射为其在 s2 中出现的位置，得到位置序列，对该序列求 LIS。
4. **编辑距离的变体：**
   - 仅允许删除：相当于判断 s1 是否是 s2 的子序列
   - 不同操作代价不同：修改 min 中的权重即可
   - Damerau-Levenshtein 距离：额外允许交换相邻字符的操作

## 五、真题精练

### 5.1 真题1：最长公共子序列（LCS 模板题）

**题目描述：**
给定两个字符串 s1 和 s2（长度均不超过 1000），求它们的最长公共子序列的长度。

**输入格式：**
两行，每行一个字符串，只包含小写英文字母。

**输出格式：**
一个整数，表示最长公共子序列的长度。

**解题思路：** 标准 LCS 二维 DP 模板题。

**AC 代码核心：**
- 构建 (n+1) × (m+1) 的 DP 表
- 双重循环按转移方程填表
- 输出 dp[n][m]

**复杂度分析：** O(n×m) 时间，O(n×m) 或 O(min(n,m)) 空间

### 5.2 真题2：编辑距离（LeetCode 72 / 字符串变换）

**题目描述：**
给定两个单词 word1 和 word2（长度均不超过 500），计算将 word1 转换为 word2 所需的最小操作次数。你可以对一个单词进行如下三种操作：插入一个字符、删除一个字符、替换一个字符。

**输入格式：**
两行，每行一个字符串。

**输出格式：**
一个整数，表示最少操作次数。

**样例输入：**
```
horse
ros
```

**样例输出：**
```
3
```

**解释：**
horse -> rorse (将 'h' 替换为 'r')
rorse -> rose (删除 'r')
rose -> ros (删除 'e')

**解题思路：** 标准编辑距离 DP。删除 = dp[i-1][j] + 1，插入 = dp[i][j-1] + 1，替换 = dp[i-1][j-1] + 1。

**优化：** 可以使用滚动数组将空间优化到 O(min(n,m))。

**复杂度分析：** O(n×m) 时间，O(min(n,m)) 空间（优化后）

## 六、本课小结

| 知识点 | 核心内容 |
|--------|----------|
| LCS 问题 | 最经典的二维字符串 DP，dp[i][j] = dp[i-1][j-1]+1 或 max(dp[i-1][j], dp[i][j-1]) |
| LCS 空间优化 | 滚动数组（两行交替 或 一维+prev变量），注意左上角依赖 |
| LCS 路径回溯 | dir 数组记录转移方向，从右下角反向追踪 |
| 编辑距离 | 三种操作（插入/删除/替换），初始化边界有讲究 |
| 编辑距离空间优化 | 与 LCS 类似，也是 O(min(n,m)) 的一维优化 |
| 序列比对 | NW 算法（全局比对）和 SW 算法（局部比对），评分矩阵+空位罚分 |
| LCS → LIS 转化 | 当字符唯一时，可以将 O(nm) 的 LCS 优化到 O(n log n) |
| 三个操作的理解 | dp[i-1][j] 对应删除（word1 少一个），dp[i][j-1] 对应插入（word2 少一个），dp[i-1][j-1] 对应替换 |

**配套程序：** `程序/lesson26_lcs_edit_distance.cpp`
**配套课件：** `课件/第26课-LCS（最长公共子序列）与编辑距离.html`
