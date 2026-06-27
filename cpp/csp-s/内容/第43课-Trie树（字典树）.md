# 第43课：Trie 树（字典树）

## 🎯 考纲要求

| 知识点 | 要求 |
|--------|------|
| Trie 字典树的数据结构与实现 | 掌握 |
| 字符串的插入与查询操作 | 掌握 |
| 前缀统计与计数 | 掌握 |
| 01Trie 求最大异或对 | 掌握 |
| 可持久化 Trie 基本思想 | 了解 |
| Trie 图与 AC 自动机 | 了解 |

---

## 📖 知识精讲

### 一、Trie 树（字典树）概述

Trie 树（又名字典树、前缀树）是一种用于高效存储和检索字符串集合的树形数据结构。它的核心思想是利用字符串的公共前缀来减少查询时间，最大限度地减少无谓的字符串比较。

**基本性质：**

1. 根节点不包含字符，根节点以外的每个节点只包含一个字符
2. 从根节点到某一节点，路径上经过的字符连接起来，为该节点对应的字符串
3. 每个节点的所有子节点包含的字符都不相同

**时间复杂度：**

- 插入一个长度为 L 的字符串：`O(L)`
- 查询一个长度为 L 的字符串：`O(L)`
- 空间复杂度：`O(总字符数 × 字符集大小)`

### 二、数据结构定义

Trie 树通常用二维数组实现：

```cpp
// 普通 Trie（小写字母，字符集大小 26）
const int N = 100010;  // 节点总数 = 总字符数
int son[N][26];        // son[i][c] 表示节点 i 的字符 c 子节点编号
int cnt[N];            // cnt[i] 表示以节点 i 结尾的字符串数量
int idx = 0;           // 当前节点编号（0 为根节点）

// 01Trie（二进制，字符集大小 2）
int son[N][2];         // son[i][0/1] 表示节点 i 的 0/1 子节点
int cnt[N];            // 节点经过次数
```

**注意事项：**

- 节点编号从 `1` 开始分配，`0` 是根节点（不存储字符）
- `son[0][c]` 表示从根节点出发，走字符 `c` 到达的节点
- 数组大小 `N` 需要开到「总字符数 + 1」，而不是字符串个数

### 三、插入操作

逐个字符遍历字符串，从根节点出发：

- 如果当前字符对应的子节点不存在，则新建一个节点（`++idx`）
- 向下移动到子节点
- 遍历结束后，在终止节点上 `cnt[p]++` 标记该字符串

```cpp
void insert(const string &s) {
    int p = 0;  // 从根节点开始
    for (char ch : s) {
        int c = ch - 'a';
        if (!son[p][c]) son[p][c] = ++idx;  // 不存在则新建节点
        p = son[p][c];
    }
    cnt[p]++;  // 字符串结束标记
}
```

**时间复杂度：** `O(|s|)`，其中 `|s|` 为字符串长度。

### 四、查询操作

#### 4.1 查询完整字符串是否存在

```cpp
bool query(const string &s) {
    int p = 0;
    for (char ch : s) {
        int c = ch - 'a';
        if (!son[p][c]) return false;  // 路径不存在
        p = son[p][c];
    }
    return cnt[p] > 0;  // 判断该节点是否为某个字符串的终止节点
}
```

#### 4.2 查询前缀出现的次数

在 Trie 中额外维护一个 `pass[N]` 数组，记录每个节点被经过的次数：

```cpp
void insert(const string &s) {
    int p = 0;
    for (char ch : s) {
        int c = ch - 'a';
        if (!son[p][c]) son[p][c] = ++idx;
        p = son[p][c];
        pass[p]++;  // 记录该节点被经过
    }
    cnt[p]++;
}

int countPrefix(const string &prefix) {
    int p = 0;
    for (char ch : prefix) {
        int c = ch - 'a';
        if (!son[p][c]) return 0;
        p = son[p][c];
    }
    return pass[p];  // 返回以 prefix 为前缀的单词数量
}
```

### 五、01Trie 与最大异或对

#### 5.1 01Trie 的基本思想

01Trie 是 Trie 树的特例：将整数按二进制位插入 Trie（字符集为 `{0, 1}`），从高位到低位依次处理。

**为什么从高位开始？** 因为高位对数值大小的影响更大。求解最大异或值时，高位能取 `1` 比低位能取 `1` 重要得多。

#### 5.2 插入整数

```cpp
void insert(int x) {
    int p = 0;
    for (int i = 30; i >= 0; i--) {   // 31 位整数，从最高位开始
        int bit = (x >> i) & 1;
        if (!son[p][bit]) son[p][bit] = ++idx;
        p = son[p][bit];
        cnt[p]++;  // 记录该节点被经过的次数
    }
}
```

`i` 从 `30` 开始（而非 `31`），因为我们要处理的是非负整数（`0 ≤ x ≤ 2^31 - 1`）。如果处理 `int` 范围内的负数，可以从 `31` 开始。

#### 5.3 查询与 x 异或的最大值

**贪心策略：** 对于当前位 `bit`，尽量走与 `bit` 相反的边（即 `bit ^ 1`）。如果相反的边不存在，才走相同的边。

```cpp
int queryMaxXor(int x) {
    int p = 0, res = 0;
    for (int i = 30; i >= 0; i--) {
        int bit = (x >> i) & 1;
        if (son[p][bit ^ 1]) {  // 尽量走相反的位
            res |= (1 << i);     // 这一位异或结果为 1
            p = son[p][bit ^ 1];
        } else {
            p = son[p][bit];
        }
    }
    return res;  // 返回最大异或值
}
```

**为什么贪心是正确的？** 对于二进制的每一位，`1` 对最终结果的贡献比所有低位加起来还大（因为 `2^i > 2^{i-1} + 2^{i-2} + ... + 2^0`）。因此我们优先保证高位能异或出 `1`。

### 六、01Trie 的删除操作

利用 `cnt` 数组记录经过次数，删除时只需减少计数：

```cpp
void del(int x) {
    int p = 0;
    for (int i = 30; i >= 0; i--) {
        int bit = (x >> i) & 1;
        int nxt = son[p][bit];
        if (--cnt[nxt] == 0) {  // 没有数再经过该节点，断开连接
            son[p][bit] = 0;
        }
        p = nxt;
    }
}
```

### 七、可持久化 Trie 入门

可持久化 Trie 用于查询历史版本中与某个值异或最大的值。核心思想：

1. 每次插入时，新建一条路径上的所有节点，其他节点复用之前的版本
2. 每个节点记录一个 `version`（版本号），表示该节点是哪个版本的
3. 查询时，只走 `version ≥ L` 的节点

**典型应用：** 区间最大异或和（查询 `a[l..r]` 中与 `x` 异或最大的值）。

```cpp
// 简化版可持久化 Trie 框架
int root[N];              // 每个版本的根节点
int son[N * 32][2];       // 节点数组（乘 32 因为每个整数最多 32 位）
int ver[N * 32];          // 版本信息
int idx = 0;

void insert(int prevRoot, int newVer, int x) {
    int p = root[newVer] = ++idx;
    int q = root[prevRoot];
    for (int i = 30; i >= 0; i--) {
        int bit = (x >> i) & 1;
        son[p][bit ^ 1] = son[q][bit ^ 1];  // 复用另一分支
        son[p][bit] = ++idx;                 // 新建当前分支
        ver[son[p][bit]] = newVer;
        p = son[p][bit];
        q = son[q][bit];
    }
}
```

### 八、Trie 图与 AC 自动机的关系

Trie 图是 AC 自动机的优化形式。普通 AC 自动机在匹配时，如果某个字符的子节点不存在，需要通过 `fail` 指针不断向上跳转寻找。Trie 图则直接将 `son` 数组补全：

- 对于不存在的子节点，直接将其指向 `fail` 指针跳转后的对应子节点
- 这样在匹配时，每一步都能在 Trie 图中直接走，无需跳 `fail`

**公式：** `son[u][c] = son[fail[u]][c]`（当 `son[u][c]` 不存在时）

这种优化将匹配过程的时间复杂度从「可能退化」变为严格的 `O(文本串长度)`。

---

## 💻 代码模板

### 模板一：普通 Trie

```cpp
const int N = 100010;  // 节点总数
int son[N][26], cnt[N], idx;

void insert(const string &s) {
    int p = 0;
    for (char ch : s) {
        int c = ch - 'a';
        if (!son[p][c]) son[p][c] = ++idx;
        p = son[p][c];
    }
    cnt[p]++;
}

bool query(const string &s) {
    int p = 0;
    for (char ch : s) {
        int c = ch - 'a';
        if (!son[p][c]) return false;
        p = son[p][c];
    }
    return cnt[p] > 0;
}
```

### 模板二：01Trie（最大异或对）

```cpp
const int N = 100010 * 31;  // 每个数最多 31 个节点
int son[N][2], cnt[N], idx;

void insert(int x) {
    int p = 0;
    for (int i = 30; i >= 0; i--) {
        int bit = (x >> i) & 1;
        if (!son[p][bit]) son[p][bit] = ++idx;
        p = son[p][bit];
        cnt[p]++;
    }
}

int queryMaxXor(int x) {
    int p = 0, res = 0;
    for (int i = 30; i >= 0; i--) {
        int bit = (x >> i) & 1;
        if (son[p][bit ^ 1]) {
            res |= (1 << i);
            p = son[p][bit ^ 1];
        } else {
            p = son[p][bit];
        }
    }
    return res;
}
```

---

## ⚠️ 易错点与优化技巧

| 问题 | 说明 | 解决方案 |
|------|------|----------|
| 数组大小不够 | `son[N][26]` 的 N 要是「总字符数」而非「字符串个数」 | `N = max 字符串数 × max 串长` |
| 根节点编号 | 根节点为 0，但很多代码错误地从 1 开始 | 统一约定：`idx = 0`，根节点为 `0` |
| 01Trie 遍历顺序 | 必须从高位到低位 | `for (int i = 30; i >= 0; i--)` |
| 多组测试数据未清空 | `son` 和 `cnt` 数组残留 | 使用 `memset` 或重新初始化（注意只清空 `idx` 范围内的） |
| 内存过大 | 静态数组内存浪费 | 使用 `vector<array<int, 26>> son` 动态开点 |
| 删除不完全 | 只删除 `cnt` 不处理节点 | 01Trie 删除时需要判断 `cnt` 是否为 0 来释放节点 |

### 动态开点优化（节省内存）

```cpp
vector<array<int, 26>> son;
vector<int> cnt;

Trie() {
    son.push_back({});  // 根节点
    cnt.push_back(0);
}

void insert(const string &s) {
    int p = 0;
    for (char ch : s) {
        int c = ch - 'a';
        if (son[p][c] == 0) {
            son[p][c] = son.size();
            son.push_back({});
            cnt.push_back(0);
        }
        p = son[p][c];
    }
    cnt[p]++;
}
```

---

## 📝 真题精练

### 真题1：统计以某字符串为前缀的单词数量

**【题目描述】**

维护一个字符串集合，支持两种操作：

1. `I s`：向集合中插入一个字符串 `s`
2. `Q s`：询问集合中有多少个字符串以 `s` 为前缀

字符串仅包含小写字母，总操作数不超过 `10^5`，字符串总长度不超过 `10^5`。

**【输入格式】**

```
第一行：整数 N，表示操作数
接下来 N 行：每行一个操作，格式为 "I s" 或 "Q s"
```

**【输出格式】**

对于每个 `Q` 操作，输出一个整数表示答案。

**【样例输入】**

```
5
I abc
I abcdef
I ab
Q ab
Q abc
```

**【样例输出】**

```
3
2
```

**【解题思路】**

使用 Trie 树维护字符串集合。除了 `cnt` 数组记录以某节点为结尾的字符串数量，额外使用 `pass` 数组记录每个节点被经过的次数。

- `insert` 时，每经过一个节点就将 `pass[p]++`
- `countPrefix` 时，遍历前缀字符串，如果路径存在则返回最后节点的 `pass` 值，否则返回 0

**【参考代码见 `程序/lesson43_trie.cpp`】**

---

### 真题2：最大异或对（01Trie 经典题）

**【题目描述】**

在给定的 N 个整数 `a1, a2, ..., aN` 中选出两个数进行异或运算，求得到的最大结果。

数据范围：`1 ≤ N ≤ 10^5`，`0 ≤ ai ≤ 2^31 - 1`。

**【输入格式】**

```
第一行：整数 N
第二行：N 个整数 a1 a2 ... aN
```

**【输出格式】**

```
一个整数，表示最大异或值
```

**【样例输入】**

```
5
1 2 3 4 5
```

**【样例输出】**

```
7
```

解释：`4 ⊕ 3 = 7`（`100 ⊕ 011 = 111`）

**【解题思路】**

1. 将每个数按二进制从高位到低位插入 01Trie
2. 对于每个数 `x`，在 01Trie 中贪心地查询与它异或最大的值：每一位尽量走与 `x` 当前位相反的边
3. 遍历所有数，取查询结果的最大值

**时间复杂度：** `O(N × 31)`，即 `O(N log MAX_AI)`

**【参考代码见 `程序/lesson43_trie.cpp`】**

---

## 🎯 本课小结

| 知识点 | 核心内容 |
|--------|----------|
| Trie 定义 | 树形结构，用公共前缀优化字符串存储和查询 |
| 数组实现 | `son[N][26]` + `cnt[N]` + `idx`，根节点为 0 |
| 插入/查询 | `O(L)`，逐字符遍历 |
| 前缀计数 | 维护 `pass` 数组记录经过节点的次数 |
| 01Trie | 按二进制位插入，字符集 `{0, 1}`，高位优先 |
| 最大异或对 | 贪心走相反位，`O(N log MAX)` |
| 可持久化 Trie | 节点复用，记录版本号，支持区间查询 |

**拓展思考：**

1. 如果字符集不是小写字母而是大小写字母 + 数字，Trie 如何设计？（思路：`son[N][62]`，映射函数 `c -> index`）
2. 01Trie 的高位起点如何确定？（根据数据范围，够覆盖最大值的最高位即可）
3. 如何用 Trie 实现字符串排序？（对 Trie 进行 DFS 即可得到字典序）
