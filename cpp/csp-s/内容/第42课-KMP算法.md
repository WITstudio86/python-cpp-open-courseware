# 第42课：KMP算法

## 🎯 考纲要求
- **CSP-S 考纲对应**：KMP（Knuth-Morris-Pratt）字符串匹配算法
- 暴力匹配的时间复杂度问题 O(n×m)
- next 数组（部分匹配表 / 前缀函数）的定义和推导
- next 数组的递推构建过程（双指针 i 和 j）
- KMP 匹配过程（失配时 j 跳转到 next[j]）
- 时间复杂度 O(n+m) 的均摊分析
- 最小循环节定理：若 len % (len - next[len]) == 0，则最小循环节长度为 len - next[len]
- KMP 的扩展应用：求每个前缀的出现次数、周期统计

## 📖 知识精讲

### 一、暴力匹配的问题

给定文本串 T（长度 n）和模式串 P（长度 m），在 T 中查找 P 的所有出现位置。

**暴力匹配**（朴素算法）：

```cpp
for (int i = 0; i <= n - m; i++) {
    bool match = true;
    for (int j = 0; j < m; j++) {
        if (T[i + j] != P[j]) {
            match = false;
            break;
        }
    }
    if (match) cout << i << '\n';
}
```

**时间复杂度**：O(n×m)，最坏情况下（如 T = "aaaa...a"，P = "aaa...b"）每次都要比较接近 m 次。

KMP 算法的目标：**利用已匹配的信息避免回溯**，将时间复杂度降至 O(n+m)。

### 二、next 数组的定义和推导

#### 定义

next[i] 表示：**模式串 P 的前缀 P[0..i] 中，最长的相等的真前缀与真后缀的长度**（即最长公共前后缀长度）。

> "真前缀"指不包括整个字符串本身的前缀；"真后缀"同理。

**示例**：P = "ababc"

| 下标 i | 前缀 P[0..i] | 最长公共前后缀 | next[i] |
|--------|--------------|---------------|---------|
| 0 | "a" | (空) | 0 |
| 1 | "ab" | (空) | 0 |
| 2 | "aba" | "a" | 1 |
| 3 | "abab" | "ab" | 2 |
| 4 | "ababc" | (空) | 0 |

**理解 next 数组的含义**：next[i] = k 意味着 P[0..k-1] == P[i-k+1..i]，即前缀 P[0..k-1] 等于以 i 结尾的长度为 k 的后缀。

#### 失配时的应用

当匹配到 P[j] 与 T[i] 失配时，根据 next 数组的定义：
- 已知 P[0..j-1] == T[i-j..i-1]
- next[j-1] = k，说明 P[0..k-1] == P[j-k..j-1]
- 因此 P[0..k-1] == T[i-k..i-1]，无需重新比较这 k 个字符
- 直接将 j 设为 k，继续比较 P[k] 与 T[i]

**图示**：

```
失配时：
T: ... a b a b c ...
          |   |
P:   a b a b d
          ↑
          j=4 处失配

next[3] = 2 (因为 "ab" 是 "abab" 的最长公共前后缀)

跳转后：
T: ... a b a b c ...
              |
P:       a b a b d
          ↑
          j=2，跳过了 "ab" 的重复比较
```

### 三、next 数组的递推构建

使用双指针 i 和 j 递推构建 next 数组：

- **i**：当前正在计算 next[i] 的位置（从 1 开始）
- **j**：当前已匹配的前缀长度（即 next[i-1]）

**算法步骤**：

1. 初始化 next[0] = 0, j = 0
2. 对于 i 从 1 到 m-1：
   - 当 j > 0 且 P[i] != P[j] 时：j = next[j-1]（回退）
   - 若 P[i] == P[j]：j++
   - next[i] = j

**以 P = "ababac" 为例演示递推过程**：

```
i=1: P[1]='b', P[j=0]='a', 不相等 → next[1]=0
i=2: P[2]='a', P[j=0]='a', 相等 → j=1, next[2]=1
i=3: P[3]='b', P[j=1]='b', 相等 → j=2, next[3]=2
i=4: P[4]='a', P[j=2]='a', 相等 → j=3, next[4]=3
i=5: P[5]='c', P[j=3]='b', 不相等 → j=next[2]=1
     P[5]='c', P[j=1]='b', 不相等 → j=next[0]=0
     next[5]=0
```

### 四、KMP 匹配过程

有了 next 数组后，匹配过程如下：

- **i**：文本串 T 的当前匹配位置（不回退）
- **j**：模式串 P 的当前匹配位置

```cpp
int kmp_search(const string& T, const string& P) {
    int n = T.size(), m = P.size();
    if (m == 0) return 0;
    vector<int> next = get_next(P);
    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j > 0 && T[i] != P[j]) {
            j = next[j - 1];  // 失配时 j 跳转到 next[j-1]
        }
        if (T[i] == P[j]) {
            j++;
        }
        if (j == m) {
            // 找到一个匹配，起始位置为 i - m + 1
            cout << (i - m + 1) << '\n';
            j = next[j - 1];  // 继续查找下一个匹配（允许重叠）
        }
    }
}
```

**关键洞察**：在匹配过程中，i 从不回退，j 通过 next 数组实现「智能跳转」——这就是 KMP 线性复杂度的核心。

### 五、时间复杂度分析 O(n+m) 的均摊证明

**next 数组构建**：O(m)
- 指针 j 每次最多增加 1（i 每步最多让 j+1）
- j 的减少量受限于 j 之前增加的总量（每次回退至少让 j 减少 1）
- 因此 j 最多增加 m 次，也最多减少 m 次
- 总操作次数 O(m)

**匹配过程**：O(n)
- 同理，j 在匹配过程中最多增加 n 次，也最多减少 n 次
- 总操作次数 O(n)

**总复杂度**：O(n+m)，线性时间。

### 六、最小循环节定理

**定理**：对于长度为 len 的字符串 s，若 `len % (len - next[len-1]) == 0`，则 s 可以由长度为 `len - next[len-1]` 的循环节重复构成，且该长度为**最小循环节**。

**推导**：
- next[len-1] 是 s 的最长公共前后缀长度
- len - next[len-1] 是「不在公共前后缀中」的那段长度
- 如果 len 能被这个长度整除，说明整个字符串由这个循环节重复构成

**示例**：
- s = "abcabcabc"，len = 9，next[8] = 6
  - len - next[8] = 3，9 % 3 == 0 ✓
  - 最小循环节为 "abc"，长度 3
- s = "abcab"，len = 5，next[4] = 2
  - len - next[4] = 3，5 % 3 != 0
  - 不能由单一循环节重复构成

**补充成循环串**：若字符串不能由循环节构成，最少需要添加 `(len - next[len-1]) - len % (len - next[len-1])` 个字符（当不整除时）。

### 七、KMP 的扩展应用

**应用 1：求每个前缀的出现次数**

定义 cnt[i] 表示前缀 P[0..i] 在 P 中作为子串出现的次数（不包括自身作为整个前缀的情况，或者根据题目需求定义）。

利用 next 数组的「拓扑序」：从后向前累加 cnt[next[i]] += cnt[i]。

**应用 2：周期统计**

一个字符串的前缀 P[0..i] 是周期的当且仅当 (i+1) % ((i+1) - next[i]) == 0，周期长度为 (i+1) - next[i]。

**应用 3：统计每个前缀在文本串中的出现次数**

在匹配过程中，每匹配到一个位置就对应某些前缀的出现，利用 next 数组可以快速统计。

## 💻 代码模板

```cpp
// ============ getNext（下标从 0 开始） ============
vector<int> get_next(const string& P) {
    int m = P.size();
    vector<int> next(m, 0);
    int j = 0;  // j 表示当前匹配的前缀长度
    for (int i = 1; i < m; i++) {
        while (j > 0 && P[i] != P[j]) {
            j = next[j - 1];  // 回退
        }
        if (P[i] == P[j]) {
            j++;
        }
        next[i] = j;
    }
    return next;
}

// ============ KMP 匹配（查找所有出现位置） ============
vector<int> kmp_search(const string& T, const string& P) {
    vector<int> res;
    int n = T.size(), m = P.size();
    if (m == 0) return res;
    vector<int> next = get_next(P);
    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j > 0 && T[i] != P[j]) {
            j = next[j - 1];
        }
        if (T[i] == P[j]) {
            j++;
        }
        if (j == m) {
            res.push_back(i - m + 1);
            j = next[j - 1];  // 继续匹配（允许重叠）
        }
    }
    return res;
}

// ============ 最小循环节 ============
int min_cycle_len(const string& s) {
    int n = s.size();
    vector<int> next = get_next(s);
    int cycle = n - next[n - 1];
    if (n % cycle == 0) return cycle;
    return n;  // 无循环节，整个串自身
}
```

## ⚠️ 易错点与优化技巧

1. **next 数组下标从 0 或 1 开始的差异**：
   - 从 0 开始：next[0] = 0，定义方便，匹配时 j == m 说明已匹配 m 个字符
   - 从 1 开始：next[1] = 0，失配时 j = next[j]，代码略简单但下标容易出错
   - **推荐使用下标从 0 开始的版本**，与 C++ 字符串索引一致

2. **字符串下标与 next 下标的对应关系**：
   - next[i] 对应的是前缀 P[0..i] 的最长公共前后缀长度
   - 失配时是 j = next[j-1]，而不是 next[j]（因为 j 位置还未匹配）

3. **最小循环节判别条件**：
   - 必须满足 `len % (len - next[len-1]) == 0` 才存在完整循环节
   - 不满足时，循环节长度为 len（整个串）
   - 注意：循环节是针对**整个字符串**而言，而非任意前缀

4. **匹配结束后的处理**：
   - 找到一次匹配后，j = next[j-1] 可以继续匹配后续出现的模式串（允许重叠）
   - 如果不允许重叠，则 j = 0
   - CSP-S 中通常允许重叠

5. **next 数组 vs prefix function（前缀函数）**：
   - 算法竞赛中，next 数组通常指代 KMP 的 pi 数组（prefix function）
   - 有些教材中将 next 数组整体右移 1 位，使用时注意区分

6. **失配回退的 while 循环**：
   - `while (j > 0 && P[i] != P[j])` 中的 j > 0 条件不能省略
   - 当 j == 0 时 next[j-1] 越界

## 📝 真题精练

### 真题一：KMP 标准匹配（统计出现次数）

**题目描述**：
给定文本串 T 和模式串 P，统计 P 在 T 中出现的次数（允许重叠）。

**数据范围**：
- 1 ≤ |T| ≤ 10⁶
- 1 ≤ |P| ≤ 10⁵

**解题思路**：
标准 KMP 匹配，每次匹配成功后 count++，j = next[j-1] 继续匹配。

**AC 代码**：

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> get_next(const string& P) {
    int m = P.size();
    vector<int> next(m, 0);
    int j = 0;
    for (int i = 1; i < m; i++) {
        while (j > 0 && P[i] != P[j]) j = next[j - 1];
        if (P[i] == P[j]) j++;
        next[i] = j;
    }
    return next;
}

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
            j = next[j - 1];
        }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string T, P;
    cin >> T >> P;
    cout << kmp_count(T, P) << '\n';
    return 0;
}
```

**复杂度分析**：时间 O(|T| + |P|)，空间 O(|P|)。

### 真题二：最小循环节

**题目描述**：
给定一个字符串 s，求：
1. 若 s 可由某个子串重复 k 次构成，输出该子串和 k
2. 否则输出「需要添加 x 个字符才能使其成为循环串」的最小 x

**数据范围**：
- 1 ≤ |s| ≤ 10⁶

**解题思路**：
利用最小循环节定理。设 len = |s|，cycle = len - next[len-1]。
- 若 len % cycle == 0，则循环节长度为 cycle，k = len / cycle
- 否则，需要添加 cycle - len % cycle 个字符

**AC 代码**：

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> get_next(const string& s) {
    int n = s.size();
    vector<int> next(n, 0);
    int j = 0;
    for (int i = 1; i < n; i++) {
        while (j > 0 && s[i] != s[j]) j = next[j - 1];
        if (s[i] == s[j]) j++;
        next[i] = j;
    }
    return next;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string s; cin >> s;
    int n = s.size();
    vector<int> next = get_next(s);

    int cycle = n - next[n - 1];

    if (n % cycle == 0 && cycle < n) {
        cout << "循环节: " << s.substr(0, cycle) << '\n';
        cout << "重复次数 k = " << n / cycle << '\n';
    } else {
        int need = cycle - n % cycle;
        cout << "需要添加 " << need << " 个字符\n";
        cout << "添加后: " << s;
        // 补全循环节
        for (int i = 0; i < need; i++) {
            cout << s[(n + i) % cycle];
        }
        cout << '\n';
    }
    return 0;
}
```

**复杂度分析**：时间 O(|s|)，空间 O(|s|)。

## 🎯 本课小结

1. **KMP 核心思想**：利用已匹配信息，通过 next 数组避免 i 指针回溯，实现 O(n+m) 线性匹配
2. **next 数组定义**：next[i] = 前缀 P[0..i] 的最长公共前后缀长度
3. **失配处理**：j = next[j-1]，利用 next 的「记忆」跳转到下一个可能匹配的位置
4. **最小循环节定理**：cycle = len - next[len-1]，若 len % cycle == 0 则存在循环节
5. **扩展应用**：周期统计、前缀出现次数、border 统计等
6. **实战建议**：next 数组从 0 开始定义最方便，牢记 while 回退条件是 j > 0
