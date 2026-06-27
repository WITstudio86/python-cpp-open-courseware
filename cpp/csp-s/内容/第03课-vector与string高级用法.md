# 第03课：vector 与 string 高级用法

## 🎯 考纲要求

- **vector 内存管理**：理解 size / capacity / reserve / resize / shrink_to_fit 的关系与使用场景
- **vector 底层实现**：掌握动态数组扩容机制（扩容因子 1.5 或 2），理解均摊 O(1) 复杂度
- **迭代器失效**：深入理解插入、删除、重新分配导致迭代器/指针/引用失效的 6 种场景
- **emplace_back vs push_back**：理解原位构造与拷贝构造的性能差异
- **string 高级操作**：掌握 find / rfind / substr / compare 的高效用法
- **stringstream**：灵活运用字符串流进行类型转换、字符串分割与格式化输入输出
- **综合应用**：能运用上述技巧解决 CSP-S 级别模拟与字符串处理问题

---

## 📖 知识精讲

### 一、vector 内存管理机制

#### 1.1 size 与 capacity 的本质区别

| 属性 | 含义 | 复杂度 |
|------|------|--------|
| `size()` | 当前容器中实际存储的元素个数 | O(1) |
| `capacity()` | 当前已分配内存最多能容纳的元素个数（不触发重新分配） | O(1) |

`capacity()` 永远大于等于 `size()`。当 `size() == capacity()` 时，如果再插入元素，vector 会：

1. 分配一块更大的新内存
2. 将旧元素移动/拷贝到新内存
3. 释放旧内存
4. 插入新元素

这个过程的代价是 O(n) 的，但它不会频繁发生——这就是**均摊分析**的关键。

#### 1.2 扩容因子分析

扩容因子（growth factor）决定了 new_capacity = old_capacity × k。

- **k = 2**（GCC libstdc++ 的做法）：每次容量翻倍，内存浪费最多 100%，但扩容频率低
- **k = 1.5**（MSVC / Clang libc++ 的做法）：内存浪费最多 50%，且更能利用先前释放的内存块（因为 1 + 1.5 + 1.5² + … 的级数收敛性质）

**均摊 O(1) 的数学证明**（以 k = 2 为例）：

设最终插入 n 个元素，容量序列为 1, 2, 4, 8, …, 2^m（其中 2^m ≥ n）。

扩容总拷贝次数：1 + 2 + 4 + … + 2^(m−1) = 2^m − 1 ≤ 2n − 1 = O(n)

均摊到每个元素：(2n − 1) / n ≈ 2 次拷贝 → O(1) 均摊。

#### 1.3 内存管理函数详解

```cpp
vector<int> v;
v.reserve(100);      // 预分配至少 100 个元素的空间，size 不变，仅改变 capacity
v.resize(50);        // 将 size 设为 50（若 capacity 不足则先扩容），新元素默认值初始化
v.resize(50, 42);    // 将 size 设为 50，新元素初始化为 42
v.shrink_to_fit();   // 请求将 capacity 缩减至 size（仅为建议，标准库可忽略）
v.clear();           // 清空所有元素，size = 0，但 capacity 不变
```

**关键公式**：`reserve` + `push_back` 是避免频繁扩容的最优实践。

```cpp
// ❌ 不良写法：每次 push_back 可能触发扩容
vector<int> v;
for (int i = 0; i < 1000000; i++) v.push_back(i);

// ✅ 最佳实践：先 reserve 再填充
vector<int> v;
v.reserve(1000000);
for (int i = 0; i < 1000000; i++) v.push_back(i);
// 或 C++11: v.emplace_back(i);  —— 原位构造，避免临时对象
```

#### 1.4 利用 swap 释放内存的技巧

`clear()` 不释放内存，`shrink_to_fit()` 仅是建议。**100% 保证释放内存的方法**：

```cpp
vector<int>().swap(v);  // 用空 vector 与 v 交换，v 的内存被释放
```

这利用了临时对象在表达式结束后析构时释放其持有的内存。

---

### 二、string 高阶用法

#### 2.1 find 系列函数

```cpp
string s = "hello world, hello cpp";

// find: 从左向右查找，返回第一次出现的位置，未找到返回 string::npos
size_t pos = s.find("hello");       // pos = 0
pos = s.find("hello", 1);           // 从索引 1 开始找 → pos = 12

// rfind: 从右向左查找（反向查找），返回最后一次出现的位置
pos = s.rfind("hello");             // pos = 12

// find_first_of: 查找参数中任意一个字符首次出现的位置
pos = s.find_first_of("aeiou");     // 查找第一个元音 → pos = 1 ('e')

// find_last_of: 查找参数中任意一个字符最后出现的位置
pos = s.find_last_of("aeiou");      // pos = 17 ('o')

// find_first_not_of: 查找第一个不在参数中的字符
pos = s.find_first_not_of("helo "); // 跳过 "helo " 字符 → 找到 'w'

// find_last_not_of: 从末尾查找第一个不在参数中的字符
```

**复杂度**：以上均为 O(n)，未特殊优化（不是 KMP）。

#### 2.2 substr 与字符串切片

```cpp
string s = "0123456789";
string sub1 = s.substr(3);      // "3456789"  从索引 3 到末尾
string sub2 = s.substr(3, 4);   // "3456"     从索引 3 开始取 4 个字符

// ⚠️ 注意：substr(pos, len) 中若 pos + len > size()，自动截断到末尾
// ⚠️ 若 pos > size()，抛出 std::out_of_range 异常
```

#### 2.3 compare 与字符串比较

```cpp
string a = "abc", b = "abd";
int cmp = a.compare(b);          // < 0   (a < b)
cmp = a.compare(0, 2, b, 0, 2);  // a[0..1] vs b[0..1] → "ab" vs "ab" → 0

// 等价于 a < b，但 compare 可以直接比较子串，避免创建临时 string
```

#### 2.4 字符串分割（split）的标准实现

C++ 标准库没有内置 split 函数，需自行实现：

```cpp
vector<string> split(const string& s, char delim = ' ') {
    vector<string> tokens;
    stringstream ss(s);
    string token;
    while (getline(ss, token, delim)) {
        if (!token.empty()) tokens.push_back(token);
    }
    return tokens;
}
```

---

### 三、stringstream 的三大用途

#### 3.1 类型转换（万能转换器）

```cpp
// 任意类型 → 字符串
template<typename T>
string to_string_custom(const T& val) {
    ostringstream oss;
    oss << val;
    return oss.str();
}

// 字符串 → 任意类型
template<typename T>
T from_string(const string& s) {
    istringstream iss(s);
    T val;
    iss >> val;
    return val;
}
```

#### 3.2 格式化输入输出

```cpp
// 模拟 scanf 行为：从字符串中解析多种类型
string input = "Alice 18 95.5";
istringstream iss(input);
string name; int age; double score;
iss >> name >> age >> score;

// 格式化输出
ostringstream oss;
oss << fixed << setprecision(2) << 3.14159;  // "3.14"
```

#### 3.3 字符串分割的高效实现

使用 stringstream + getline 是最简洁的分割方法：

```cpp
string s = "one,two,three,four";
stringstream ss(s);
string item;
while (getline(ss, item, ',')) {
    // 处理 item
}
```

---

### 四、迭代器失效（6 种场景）

> **核心原则**：任何可能导致底层内存重新分配或元素位置移动的操作，都会使迭代器失效。

| 场景 | 操作 | 失效范围 | 解决办法 |
|------|------|----------|----------|
| 场景1 | `push_back` / `emplace_back` 触发扩容 | **所有**迭代器、指针、引用失效 | 提前 `reserve` |
| 场景2 | `insert` 触发扩容 | **所有**迭代器失效 | 提前 `reserve`；或使用 `insert` 返回值 |
| 场景3 | `insert` 未触发扩容 | 插入点**之后**的迭代器失效 | 使用 `insert` 返回值更新迭代器 |
| 场景4 | `erase` 删除元素 | 删除点**及之后**的迭代器失效 | 使用 `erase` 返回值：`it = v.erase(it);` |
| 场景5 | `resize` 使 size 增大且触发扩容 | **所有**迭代器失效 | 先 `reserve` 再 `resize` |
| 场景6 | `clear` / `swap` | **所有**迭代器失效 | 重新获取迭代器 |

#### 特殊的保障

- `pop_back()`：仅使 `end()` 和被删除元素的迭代器失效，不影响其他迭代器
- `reserve` 不改变 size：不使任何迭代器失效（除非 reserve 的参数 > capacity 触发重新分配）

#### 修复示例

```cpp
// ❌ 错误：删除元素时迭代器失效
vector<int> v = {1, 2, 3, 4, 5};
for (auto it = v.begin(); it != v.end(); ++it) {
    if (*it % 2 == 0) v.erase(it);  // it 失效，++it 是未定义行为！
}

// ✅ 正确：使用 erase 的返回值
for (auto it = v.begin(); it != v.end(); ) {
    if (*it % 2 == 0) it = v.erase(it);  // erase 返回下一个有效迭代器
    else ++it;
}

// ✅ 更优：使用 erase-remove 惯用法（C++20 前）
v.erase(remove_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; }), v.end());

// ✅ C++20: std::erase_if
erase_if(v, [](int x) { return x % 2 == 0; });
```

---

### 五、emplace_back vs push_back

| 方面 | `push_back` | `emplace_back` |
|------|-------------|----------------|
| 构造方式 | 拷贝或移动已有对象 | 在原位直接构造 |
| 参数 | 需要一个已构造的对象 | 直接传递构造函数参数 |
| 临时对象 | 若传右值可能有临时对象 | **零临时对象** |
| 性能 | 多一次移动/拷贝 | 最优 |

```cpp
vector<pair<int, string>> v;

// push_back: 先构造 pair，再拷贝/移动到 vector
v.push_back(make_pair(1, "hello"));         // 需要临时 pair
v.push_back({1, "hello"});                   // 同上

// emplace_back: 直接在 vector 内部构造 pair
v.emplace_back(1, "hello");                  // 最优！零拷贝
```

---

## 💻 代码模板

```cpp
#include <bits/stdc++.h>
using namespace std;

// ========== 1. vector 内存管理优化模板 ==========
vector<int> build_with_reserve(int n) {
    vector<int> v;
    v.reserve(n);  // 关键：避免扩容
    for (int i = 0; i < n; i++)
        v.emplace_back(i);
    return v;
}

// ========== 2. string 分割模板 ==========
vector<string> split(const string& s, char delim = ' ') {
    vector<string> tokens;
    stringstream ss(s);
    string token;
    while (getline(ss, token, delim))
        if (!token.empty())
            tokens.push_back(token);
    return tokens;
}

// ========== 3. stringstream 类型转换模板 ==========
template<typename T>
T sto(const string& s) {
    T val;
    istringstream(s) >> val;
    return val;
}

template<typename T>
string tos(const T& val) {
    ostringstream oss;
    oss << val;
    return oss.str();
}

// ========== 4. 迭代器安全删除模板（erase-remove 惯用法） ==========
template<typename Container, typename Predicate>
void erase_if(Container& c, Predicate pred) {
    c.erase(remove_if(c.begin(), c.end(), pred), c.end());
}

// ========== 5. 迭代器安全遍历删除模板 ==========
template<typename Container, typename Predicate>
void safe_erase_while_iterate(Container& c, Predicate pred) {
    for (auto it = c.begin(); it != c.end(); ) {
        if (pred(*it)) it = c.erase(it);
        else ++it;
    }
}
```

---

## ⚠️ 易错点与优化技巧

### 常见错误

1. **误用 size() 与 capacity()**：`reserve` 只改变 capacity，不改变 size；用下标访问前必须确保 `index < size()`。
2. **在循环中向 vector 添加元素而不 reserve**：导致多次扩容，O(n²) 时间复杂度。
3. **使用失效的迭代器**：任何修改 container 的操作后，都需要检查迭代器是否仍然有效。
4. **string::find 返回值判断**：不要用 `>= 0` 判断，要用 `!= string::npos`。`npos` 是 `size_t` 类型的最大值（= -1），用 int 接收会发生截断。
5. **substr 越界**：C++11 起 `substr(pos, len)` 若 `pos > size()` 抛异常，务必先检查边界。
6. **stringstream 重复使用不清空**：`ss.clear()` 清除错误状态，`ss.str("")` 清空内容。

### 性能优化技巧

1. **预分配策略**：`v.reserve(预估大小)` 是最廉价的性能优化。
2. **emplace 系列优先**：`emplace_back`、`emplace` 替代 `push_back`、`insert`。
3. **用 string_view 避免拷贝**（C++17）：函数参数用 `string_view` 替代 `const string&`，避免不必要的 string 构造。
4. **小字符串优化（SSO）**：大多数实现中长度 ≤ 15 的 string 不分配堆内存，直接存储在栈上。
5. **移动语义**：返回局部 vector 时编译器自动使用移动语义（或 RVO/NRVO），无需手动 `std::move`。
6. **reserve + emplace_back 组合**：比直接 push_back 快 30%-50%（取决于元素类型）。

---

## 📝 真题精练

### 真题一：字符串展开（改编自 CSP-S 模拟）

**题目描述**

在初赛的阅读程序题中，经常会出现一种「字符串展开」的题目。给定一个压缩字符串，按照以下规则展开：

- 压缩形式为 `n(str)`，表示将括号内的字符串 `str` 重复 `n` 次，其中 `n` 是一个正整数
- 括号可以嵌套
- 字符串由小写字母组成，不含数字和括号
- 展开后的字符串总长度不超过 10⁶

例如：
- `3(ab)` → `ababab`
- `2(a3(bc))` → `abcbcbcabcbcbc`

**输入格式**

一行，一个压缩字符串，长度不超过 10⁵。

**输出格式**

一行，展开后的字符串。

**数据范围**

- 输入字符串长度 ≤ 10⁵
- 展开后总长度 ≤ 10⁶
- 1 ≤ n ≤ 10⁴

**AC 代码**

```cpp
#include <bits/stdc++.h>
using namespace std;

string decode(const string& s, int& pos) {
    string result;
    result.reserve(1000000);  // 预分配
    
    while (pos < (int)s.size()) {
        if (s[pos] == ')') {
            pos++;
            return result;
        }
        if (isdigit(s[pos])) {
            int num = 0;
            while (pos < (int)s.size() && isdigit(s[pos])) {
                num = num * 10 + (s[pos] - '0');
                pos++;
            }
            // 跳过 '('
            pos++;
            string sub = decode(s, pos);
            // 重复 num 次
            for (int i = 0; i < num; i++)
                result += sub;  // string 的 += 已优化
        } else if (islower(s[pos])) {
            result += s[pos];
            pos++;
        }
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    cin >> s;
    int pos = 0;
    cout << decode(s, pos) << '\n';
    return 0;
}
```

**复杂度分析**

- 时间复杂度：O(总输出长度)。递归每处理一个字符就向结果添加一个字符，每个输出字符被拼接一次。
- 空间复杂度：O(最大嵌套深度 + 输出长度) = O(10⁵ + 10⁶)。

---

### 真题二：日志分析（改编自 CSP-S 模拟）

**题目描述**

某系统的日志格式为 `YYYY-MM-DD HH:MM:SS LEVEL Message`，其中 LEVEL 为 `INFO`、`WARN` 或 `ERROR`。现需要统计每天（按日期分组）各等级日志的数量，并按照 WARN 数量 + 2 × ERROR 数量 的加权得分降序输出日期。

如果得分相同，按日期升序排列。

**输入格式**

第一行一个整数 n（1 ≤ n ≤ 10⁵），表示日志条数。
接下来 n 行，每行一条日志，格式严格为 `YYYY-MM-DD HH:MM:SS LEVEL Message`。

**输出格式**

每行一个日期及其统计信息，格式为 `YYYY-MM-DD INFO_COUNT WARN_COUNT ERROR_COUNT SCORE`，按得分降序、日期升序排列。

**数据范围**

- 1 ≤ n ≤ 10⁵
- 日期在 2020-01-01 到 2025-12-31 之间
- Message 长度 ≤ 100

**AC 代码**

```cpp
#include <bits/stdc++.h>
using namespace std;

struct LogStat {
    int info = 0, warn = 0, error = 0;
    int score() const { return warn + 2 * error; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    cin.ignore();  // 忽略换行
    
    map<string, LogStat> stats;
    string line;
    
    while (n--) {
        getline(cin, line);
        // 日期在前 10 个字符
        string date = line.substr(0, 10);
        
        // 用 stringstream 解析日志
        stringstream ss(line.substr(11));  // 跳过日期和空格
        string time_str, level;
        ss >> time_str >> level;
        
        if (level == "INFO")  stats[date].info++;
        else if (level == "WARN") stats[date].warn++;
        else if (level == "ERROR") stats[date].error++;
    }
    
    // 转化为 vector 排序
    vector<pair<string, LogStat>> result(stats.begin(), stats.end());
    sort(result.begin(), result.end(),
         [](const auto& a, const auto& b) {
             int sa = a.second.score(), sb = b.second.score();
             if (sa != sb) return sa > sb;      // 得分降序
             return a.first < b.first;           // 日期升序
         });
    
    for (const auto& [date, stat] : result) {
        cout << date << ' ' << stat.info << ' '
             << stat.warn << ' ' << stat.error << ' '
             << stat.score() << '\n';
    }
    return 0;
}
```

**复杂度分析**

- 时间复杂度：O(n log n)。每行日志 O(|Message|) 解析，排序 O(n log n)。
- 空间复杂度：O(n)。存储所有日期的统计信息，最多 n 个不同日期。

---

## 🎯 本课小结

| 知识模块 | 核心要点 |
|----------|----------|
| vector 内存管理 | size vs capacity，扩容因子与均摊分析，reserve 优先 |
| string 高阶用法 | find/rfind/substr/compare，npos 的正确判断方式 |
| stringstream | 类型转换、格式化 IO、字符串分割三大用途 |
| 迭代器失效 | 6 种失效场景，erase 返回值更新，erase-remove 惯用法 |
| 性能优化 | reserve + emplace_back 组合拳，移动语义，SSO |

**CSP-S 考试重点**：迭代器失效是选择题和阅读程序题的常考点；vector 内存管理和 stringstream 的灵活运用是完善程序和编程题的重要得分技能。
