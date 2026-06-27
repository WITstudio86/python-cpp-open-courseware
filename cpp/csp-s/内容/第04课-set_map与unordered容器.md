# 第04课：set/map 与 unordered 容器

## 🎯 考纲要求

- **有序关联容器**：掌握 set / multiset / map / multimap 的底层红黑树实现与 O(log n) 操作复杂度
- **无序关联容器**：掌握 unordered_set / unordered_map 的哈希表实现与均摊 O(1) 操作复杂度
- **自定义比较器**：理解函数对象、lambda 表达式、std::less 特化的三种写法
- **哈希表优化**：掌握预分配 bucket、自定义哈希函数、冲突解决策略（链地址法 vs 开放寻址法）
- **容器选择**：能在平衡树与哈希表之间做出合理的工程选择
- **综合应用**：灵活运用有序/无序容器解决 CSP-S 级别的查找、统计、排序问题

---

## 📖 知识精讲

### 一、红黑树原理

#### 1.1 红黑树的 5 条核心性质

红黑树是一种**自平衡二叉搜索树**，它通过以下 5 条性质保证树的高度为 O(log n)：

| 性质 | 描述 |
|------|------|
| 性质1 | 每个节点要么是红色，要么是黑色 |
| 性质2 | **根节点是黑色** |
| 性质3 | 每个叶子节点（NIL）是黑色 |
| 性质4 | **红色节点的两个子节点必须是黑色**（即不存在两个连续红色节点） |
| 性质5 | 从任一节点到其每个叶子节点的所有简单路径上，**黑色节点数量相同**（黑高相等） |

**推导结论**：由性质 4 和 5 可以推出，红黑树的最长路径不超过最短路径的 2 倍。因为：
- 最短路径：全黑节点，长度 = 黑高 h
- 最长路径：红黑交替，长度 = 2h − 1（红色节点不能连续）

因此红黑树的高度上限为 2 log(n+1)，保证 O(log n) 的操作复杂度。

#### 1.2 红黑树与 AVL 树的对比

| 特性 | 红黑树 | AVL 树 |
|------|--------|--------|
| 平衡条件 | 较宽松（最长 ≤ 2×最短） | 严格（高度差 ≤ 1） |
| 插入旋转次数 | 最多 2 次 | 最多 2 次（但可能回溯到根） |
| 删除旋转次数 | 最多 3 次 | 可能 O(log n) 次 |
| 查找性能 | 略慢（树稍高） | 略快（更平衡） |
| 插入删除性能 | **更快** | 更慢 |
| C++ STL 选择 | **红黑树**（set/map） | — |

**为什么 STL 选择红黑树？** 因为 STL 容器需要支持频繁的插入和删除操作（如 `insert`、`erase`），红黑树在写入性能上优于 AVL 树，且 log n 的常数因子更稳定。

#### 1.3 红黑树插入修复：旋转与颜色翻转

插入新节点（初始为红色）后可能违反性质 2（根为红）或性质 4（连续红色）。修复手段有两种：

**(1) 旋转（Rotation）**

```
左旋（Left Rotate）:          右旋（Right Rotate）:
    x                            y
   / \                          / \
  a   y        →               x   c
     / \                      / \
    b   c                    a   b
```

旋转操作保持二叉搜索树性质不变，用于调整树结构。

**(2) 颜色翻转（Color Flip）**

当插入节点的**叔叔节点也是红色**时，将父节点、叔叔节点变为黑色，祖父节点变为红色，然后递归向上检查。

插入修复的三种情况（父节点是祖父的左孩子）：

| 情况 | 条件 | 修复方式 |
|------|------|----------|
| Case 1 | 叔叔是红色 | 颜色翻转（父、叔变黑，祖父变红），继续向上 |
| Case 2 | 叔叔是黑色，新节点是右孩子 | 先左旋转为 Case 3 |
| Case 3 | 叔叔是黑色，新节点是左孩子 | 右旋 + 颜色翻转（父变黑，祖父变红） |

---

### 二、std::set 与 std::map 的实现与使用

#### 2.1 底层实现

```cpp
// set<T>  ≈ 红黑树存储 T 类型的键（键即值）
// map<K,V> ≈ 红黑树存储 pair<const K, V>，按 K 排序

// 操作复杂度（均基于红黑树）：
//   查找 find / count / contains(C++20) → O(log n)
//   插入 insert / emplace             → O(log n)
//   删除 erase                         → O(log n)
//   遍历 (iterator)                    → O(n)（中序遍历为有序序列）
```

#### 2.2 核心操作速查

```cpp
set<int> s = {3, 1, 4, 1, 5};  // 自动去重排序 → {1, 3, 4, 5}

// 插入
auto [it, ok] = s.insert(2);   // ok=true，it 指向新元素
// C++17 结构化绑定：ok 表示是否插入成功

// 查找
if (s.find(3) != s.end()) { /* 找到 */ }
if (s.count(3))            { /* 找到（返回 0 或 1） */ }

// 二分查找系列（仅有序容器有）
auto it = s.lower_bound(3);  // 第一个 ≥ 3 的元素
it = s.upper_bound(3);       // 第一个 > 3 的元素
auto [lo, hi] = s.equal_range(3); // pair<it, it> 区间 [lo, hi)

// 删除
s.erase(3);     // 按值删除，返回删除个数
s.erase(it);    // 按迭代器删除，返回下一个迭代器
```

#### 2.3 map 的特殊操作

```cpp
map<string, int> mp;

// 插入或更新
mp["key"] = 42;            // 若 key 不存在则插入默认值 0 再赋值
mp.insert({"key", 42});   // 若 key 已存在则不插入
mp.emplace("key", 42);    // 原位构造

// 查找
if (mp.count("key")) { /* 存在 */ }
auto it = mp.find("key");
if (it != mp.end()) cout << it->second;

// 删除
mp.erase("key");
```

**⚠️ `operator[]` 的陷阱**：`mp[key]` 若 key 不存在会**默认插入**一个值初始化的元素。若只想查找，请用 `find` 或 `at`（`at` 不存在时抛出异常）。

---

### 三、自定义比较器（3 种写法）

#### 方法一：函数对象（Functor）

```cpp
struct CmpByLen {
    bool operator()(const string& a, const string& b) const {
        if (a.size() != b.size()) return a.size() < b.size();
        return a < b;  // 长度相同时字典序
    }
};
set<string, CmpByLen> s;
map<string, int, CmpByLen> mp;
```

> **要求**：比较器必须满足**严格弱序**（Strict Weak Ordering）—— 反自反性、反对称性、传递性。

#### 方法二：Lambda 表达式（C++11 + decltype）

```cpp
auto cmp = [](const string& a, const string& b) {
    if (a.size() != b.size()) return a.size() > b.size(); // 按长度降序
    return a > b;
};
set<string, decltype(cmp)> s(cmp);  // 必须将 cmp 传给构造函数
```

**注意**：无捕获的 lambda 可以转为函数指针，但有捕获的 lambda 必须用 `decltype` 推导类型并传入构造。

#### 方法三：特化 std::less（不推荐，仅用于理解）

```cpp
template<>
struct std::less<string> {
    bool operator()(const string& a, const string& b) const {
        return a.size() < b.size();
    }
};
// 之后 set<string> 将自动按此规则排序
```

> **不推荐原因**：全局特化污染了 std 命名空间，影响所有使用 `set<string>` 的代码。只应在极特殊的全局策略场景使用。

---

### 四、哈希表实现原理

#### 4.1 std::unordered_map 的底层结构

C++ 标准库的 `unordered_map` 使用**链地址法**（Separate Chaining）：

```
Bucket 0: → (key1,val1) → (key3,val3)   // 链表
Bucket 1: → (key2,val2)
Bucket 2: → empty
Bucket 3: → (key4,val4) → (key5,val5) → (key8,val8)
...
```

- 哈希函数 `hash(key)` 将键映射为整数
- 通过 `hash(key) % bucket_count()` 确定落入哪个桶
- 同一桶内的元素用链表（或更优化的结构）维护

#### 4.2 负载因子与 rehash

```
负载因子(load_factor) = size() / bucket_count()
最大负载因子(max_load_factor) 默认为 1.0
```

当 `load_factor > max_load_factor` 时触发 **rehash**：分配更多桶，重新分布所有元素。rehash 的时间复杂度为 O(n)。

#### 4.3 冲突解决方法对比

| 方法 | 实现方式 | 优点 | 缺点 |
|------|----------|------|------|
| **链地址法**（C++ STL） | 每个桶是一个链表 | 实现简单，删除方便，负载因子可 >1 | 缓存不友好（节点分散在堆上） |
| **开放寻址法** | 冲突时探测下一个位置 | 缓存友好，内存连续 | 删除困难（需惰性删除标记），负载因子 ≤ 0.7 |

C++ 标准库选择链地址法，主要是因为迭代器稳定性要求以及删除操作的简便性。

---

### 五、unordered_map 优化技巧

#### 5.1 预分配 bucket（reserve）

```cpp
unordered_map<int, int> ump;
ump.reserve(100000);  // 预分配至少 100000 个桶的空间
// 作用：避免 rehash，大幅提升插入性能
```

**原理**：reserve(n) 将 bucket_count 设置为至少 `ceil(n / max_load_factor)`，确保在插入 n 个元素前不会触发 rehash。

#### 5.2 自定义哈希函数（以 pair 为例）

C++ 标准库没有为 `pair` 提供 `std::hash` 特化，需要自己实现：

```cpp
// 方法：使用 boost 风格的 hash_combine
struct PairHash {
    size_t operator()(const pair<int, int>& p) const {
        auto h1 = hash<int>{}(p.first);
        auto h2 = hash<int>{}(p.second);
        // hash_combine: 经典位运算组合，避免 (1,2) 和 (2,1) 冲突
        return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
    }
};

unordered_map<pair<int, int>, int, PairHash> ump;
// 或更简洁的写法：
unordered_set<pair<int, int>, PairHash> us;
```

> **hash_combine 原理**：`0x9e3779b9` 是黄金比例的二进制表示（2³² / φ），配合移位操作实现良好的雪崩效应，让相近的输入产生差异足够大的哈希值。

#### 5.3 max_load_factor 调优

```cpp
ump.max_load_factor(0.5);  // 降低负载因子
// 优点：减少冲突，加速查找
// 缺点：占用更多内存
// 适用场景：查询远多于插入/删除
```

---

### 六、平衡树 vs 哈希表：如何选择？

| 需求场景 | 推荐容器 | 原因 |
|----------|----------|------|
| 需要**有序遍历**（按 key 顺序输出） | set / map | 红黑树中序遍历即有序 |
| 需要**范围查询**（lower_bound / upper_bound） | set / map | 哈希表不支持范围查询 |
| 需要前驱/后继（prev/next） | set / map | 哈希表无此概念 |
| **纯增删查改**，不关心顺序 | unordered_set / unordered_map | 均摊 O(1)，更快 |
| 键类型**哈希计算昂贵**或**无法哈希** | set / map | 只需要比较运算 |
| **内存敏感** | set / map | 哈希表额外开销更大（桶数组 + 链表节点） |
| 需要**稳定迭代器**（插入不使迭代器失效） | set / map | unordered 容器 rehash 会使所有迭代器失效 |

**CSP-S 竞赛经验法则**：
- 默认用 `unordered_map`（对于 int/string 键）
- 需要有序输出 / 范围查询时用 `map`
- 不确定时用 `map`（保证 O(log n)，不会因冲突退化为 O(n)）

---

### 七、multiset / multimap 简介

```cpp
multiset<int> ms = {3, 1, 4, 1, 5};  // {1, 1, 3, 4, 5} —— 允许重复
ms.count(1);  // 返回 2（不限于 0 或 1）

// 删除所有值为 1 的元素
ms.erase(1);  // ms = {3, 4, 5}

// 只删除一个值为 4 的元素
auto it = ms.find(4);
if (it != ms.end()) ms.erase(it);  // ms = {3, 5}
```

---

## 💻 代码模板

```cpp
#include <bits/stdc++.h>
using namespace std;

// ========== 1. 自定义比较器：按字符串长度排序的 set ==========
struct CmpByLen {
    bool operator()(const string& a, const string& b) const {
        if (a.size() != b.size()) return a.size() < b.size();
        return a < b;
    }
};
set<string, CmpByLen> len_set;

// ========== 2. 自定义哈希：pair<int,int> 的哈希 ==========
struct PairHash {
    size_t operator()(const pair<int, int>& p) const {
        auto h1 = hash<int>{}(p.first);
        auto h2 = hash<int>{}(p.second);
        return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
    }
};
unordered_map<pair<int, int>, int, PairHash> pair_map;

// ========== 3. unordered_map 带 reserve 的初始化 ==========
unordered_map<int, int> create_fast_map(int expected_size) {
    unordered_map<int, int> ump;
    ump.reserve(expected_size);
    return ump;
}

// ========== 4. set 实现去重+排序（求前 K 大值） ==========
vector<int> top_k_unique(const vector<int>& arr, int k) {
    set<int, greater<int>> s(arr.begin(), arr.end());  // 降序去重
    vector<int> result;
    for (int x : s) {
        if ((int)result.size() >= k) break;
        result.push_back(x);
    }
    return result;
}

// ========== 5. map 实现频率统计 ==========
map<int, int> frequency_map(const vector<int>& arr) {
    map<int, int> freq;
    for (int x : arr) freq[x]++;
    return freq;
}

// ========== 6. 利用 map 的 lower_bound/upper_bound 实现范围查询 ==========
int count_in_range(const map<int, int>& mp, int low, int high) {
    auto lo = mp.lower_bound(low);
    auto hi = mp.upper_bound(high);
    int total = 0;
    for (auto it = lo; it != hi; ++it) total += it->second;
    return total;
}
```

---

## ⚠️ 易错点与优化技巧

### 常见错误

1. **map 的 `operator[]` 会意外插入元素**：只想检查存在性时，务用 `find` 或 `count`。
2. **set 迭代器为 const_iterator**：`set<T>::iterator` 实际上等价于 `const_iterator`（无法修改元素，因为修改可能破坏红黑树性质）。
3. **无序容器的迭代器在 rehash 后失效**：所有迭代器、指针、引用全部失效。但 `insert`（不触发 rehash）不会使迭代器失效。
4. **自定义哈希质量差导致退化为 O(n)**：如果哈希函数将所有 key 映射到同一个桶，unordered_map 退化为链表。
5. **忘记给自定义类型提供 `operator<`**：使用 set/map 时需要 `<` 运算符（或提供比较器）。
6. **使用 `lower_bound` 于 unordered 容器**：无序容器没有 `lower_bound`，编译错误。

### 性能优化技巧

1. **unordered_map 必 reserve**：若知道元素数量，`reserve(n)` 是终极优化。
2. **map 用 `emplace` 而非 `insert`**：`mp.emplace(key, val)` 比 `mp.insert({key, val})` 少一次 pair 构造。
3. **unordered_map 优先 int/string 键**：标准库对 `int` 和 `string` 的哈希实现质量高。
4. **set 去重 + 排序一步到位**：`set<int>(v.begin(), v.end())` 比 sort + unique + erase 更简洁，复杂度相同 O(n log n)。
5. **multiset 替代 priority_queue**：需要同时支持删除任意元素时，multiset 比 priority_queue 更灵活。
6. **使用 `contains`（C++20）**：`s.contains(key)` 比 `s.count(key)` 语义更清晰（但 CSP-S 环境可能不支持，稳妥用 `count` 或 `find`）。
7. **map 插入提示（hint）**：`mp.insert(mp.end(), {key, val})` 若 key 恰好在末尾，可优化至 O(1)。

---

## 📝 真题精练

### 真题一：区间合并与查询（改编自 CSP-S）

**题目描述**

给定 n 个闭区间 [lᵢ, rᵢ]，支持两种操作：
1. `ADD l r`：添加区间 [l, r]
2. `QUERY x`：查询 x 被多少个区间覆盖

由于区间数量可能很大，需要高效地维护区间信息。1 ≤ n ≤ 2×10⁵，1 ≤ l ≤ r ≤ 10⁹，1 ≤ x ≤ 10⁹。

**输入格式**

第一行一个整数 n。
接下来 n 行，每行为 `ADD l r` 或 `QUERY x`。

**输出格式**

对每个 QUERY 操作，输出一行表示覆盖该点的区间数量。

**数据范围**

- 1 ≤ n ≤ 2×10⁵
- 坐标在 [1, 10⁹] 范围内

**AC 代码（差分 + map 维护）**

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    map<int, int> diff;  // 差分数组（用 map 处理离散坐标）
    
    while (n--) {
        string op;
        cin >> op;
        if (op == "ADD") {
            int l, r;
            cin >> l >> r;
            diff[l]++;       // 在 l 处 +1
            diff[r + 1]--;   // 在 r+1 处 -1
        } else {
            int x;
            cin >> x;
            int ans = 0;
            // 遍历所有 ≤ x 的事件，累加差分值
            for (auto it = diff.begin(); it != diff.end() && it->first <= x; ++it) {
                ans += it->second;
            }
            cout << ans << '\n';
        }
    }
    return 0;
}
```

**优化版本（使用前缀和 + 二分）**

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<pair<string, pair<int, int>>> ops;
    map<int, int> diff;
    
    // 第一遍：记录所有 ADD 操作并构建差分数组
    for (int i = 0; i < n; i++) {
        string op; cin >> op;
        if (op == "ADD") {
            int l, r; cin >> l >> r;
            ops.push_back({op, {l, r}});
            diff[l]++; diff[r + 1]--;
        } else {
            int x; cin >> x;
            ops.push_back({op, {x, 0}});
        }
    }
    
    // 将差分转换为前缀和数组（有序）
    vector<pair<int, int>> events;  // {坐标, 累计值}
    int cur = 0;
    for (auto& [pos, delta] : diff) {
        cur += delta;
        events.emplace_back(pos, cur);
    }
    
    // 第二遍：用二分回答查询
    for (auto& [op, params] : ops) {
        if (op == "QUERY") {
            int x = params.first;
            // 二分找到最后一个 ≤ x 的事件
            auto it = upper_bound(events.begin(), events.end(),
                                  make_pair(x, INT_MAX));
            if (it == events.begin()) cout << "0\n";
            else cout << prev(it)->second << '\n';
        }
    }
    return 0;
}
```

**复杂度分析**

- 时间复杂度：O(n log n)。map 插入 O(log n)，查询需要遍历（优化版用二分 O(log n)）。
- 空间复杂度：O(n)。存储差分事件。

---

### 真题二：前 K 个高频单词（改编自 LeetCode 692 / CSP-S 风格）

**题目描述**

给定一个单词列表 words 和一个整数 k，返回前 k 个出现次数最多的单词。答案应按频率从高到低排序。频率相同的单词按字典序升序排列。

**输入格式**

第一行两个整数 n 和 k（1 ≤ k ≤ n ≤ 10⁵）。
接下来 n 行，每行一个单词（只含小写字母，长度 ≤ 10）。

**输出格式**

k 行，每行一个单词，按频率降序、字典序升序排列。

**AC 代码**

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    
    // 1. 哈希表统计频率（最优性能）
    unordered_map<string, int> freq;
    freq.reserve(n);
    for (int i = 0; i < n; i++) {
        string word;
        cin >> word;
        freq[word]++;
    }
    
    // 2. 将频率数据放入 vector，用自定义排序
    vector<pair<string, int>> items(freq.begin(), freq.end());
    
    // 3. 自定义排序：频率降序，同频率字典序升序
    sort(items.begin(), items.end(),
         [](const auto& a, const auto& b) {
             if (a.second != b.second) return a.second > b.second;  // 频率降序
             return a.first < b.first;  // 字典序升序
         });
    
    // 4. 输出前 k 个
    for (int i = 0; i < k && i < (int)items.size(); i++) {
        cout << items[i].first << '\n';
    }
    
    return 0;
}
```

**使用 set 自定义排序的替代方案**

```cpp
#include <bits/stdc++.h>
using namespace std;

struct Cmp {
    bool operator()(const pair<string, int>& a, const pair<string, int>& b) const {
        if (a.second != b.second) return a.second > b.second;
        return a.first < b.first;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    
    unordered_map<string, int> freq;
    freq.reserve(n);
    for (int i = 0; i < n; i++) {
        string word; cin >> word;
        freq[word]++;
    }
    
    // 直接用 set 维护有序性
    set<pair<string, int>, Cmp> s(freq.begin(), freq.end());
    
    int cnt = 0;
    for (auto& [word, f] : s) {
        if (++cnt > k) break;
        cout << word << '\n';
    }
    return 0;
}
```

**复杂度分析**

- 方案一（unordered_map + sort）：O(n + n log n) = O(n log n) 时间，O(n) 空间。
- 方案二（unordered_map + set）：O(n log n) 时间（每次插入 set 是 O(log n)），O(n) 空间。
- 当 k 较小时方案一更优（sort 只需部分排序可优化为 O(n log k)）。

---

## 🎯 本课小结

| 知识模块 | 核心要点 |
|----------|----------|
| 红黑树原理 | 5 条性质 → 树高 ≤ 2log(n+1)；旋转 + 颜色翻转修复插入 |
| set/map | 红黑树实现；O(log n) 操作；自动排序去重；支持 lower_bound/upper_bound |
| 自定义比较器 | 函数对象 / lambda+decltype / less 特化 三种方式 |
| 哈希表原理 | 链地址法；负载因子触发 rehash；哈希冲突解决 |
| unordered 优化 | reserve 预分配 bucket；自定义哈希函数；max_load_factor 调优 |
| 选择策略 | 有序需求用 set/map；纯查找用 unordered；不确定用 map（稳定 O(log n)） |

**CSP-S 考试重点**：set/map 的自定义比较器是完善程序题的常考点；unordered_map 的自定义哈希和 reserve 优化是编程题的高分技巧；红黑树的性质是选择题的理论考点。
