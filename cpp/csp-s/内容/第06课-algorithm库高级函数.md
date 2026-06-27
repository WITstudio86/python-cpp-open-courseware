# 第06课：algorithm 库高级函数

## 🎯 考纲要求
- 掌握 `sort` 与自定义比较函数的高级用法，理解内省排序（Introsort）的内部原理
- 掌握 `nth_element` 的 O(n) 快速选择算法及其应用场景
- 掌握 `next_permutation` / `prev_permutation` 的字典序排列生成
- 掌握 `lower_bound` / `upper_bound` / `binary_search` 的正确使用与常见误区
- 掌握离散化的两种实现方法（排序+去重 / map映射），理解适用场景与性能差异
- 掌握 `unique` 的去重原理与配合 `erase` 的经典用法
- 理解 `stable_sort` 的语义与应用场景

## 📖 知识精讲

### 1. sort 的内部实现原理：内省排序（Introsort）

`std::sort` 在 C++ 标准库中的实现通常采用 **内省排序（Introsort）**，这是一种混合排序算法，由 David Musser 于 1997 年提出。它将三种排序算法的优势结合在一起：

#### 1.1 三种基础排序算法的特点

| 算法 | 平均时间复杂度 | 最坏时间复杂度 | 空间复杂度 | 稳定性 | 适用场景 |
|------|-------------|-------------|----------|------|---------|
| 快速排序 | O(n log n) | O(n²) | O(log n) | 不稳定 | 通用场景，实际平均性能最优 |
| 堆排序 | O(n log n) | O(n log n) | O(1) | 不稳定 | 需要严格 O(n log n) 保证时 |
| 插入排序 | O(n²) | O(n²) | O(1) | 稳定 | 数据量很小（n < 16~32）时最优 |

**快速排序的问题**：虽然平均性能出色，但在面对已排序数据（如选择第一个元素作为 pivot）时，每次划分极不均匀，递归深度达到 O(n)，时间复杂度退化为 O(n²)。这种退化在实际编程竞赛中可能被刻意构造的数据卡掉。

**堆排序的优势**：堆排序提供严格的 O(n log n) 时间保证，且空间复杂度 O(1)。但它的常数因子较大（约为快排的 2~3 倍），在平均情况下不如快排。

**插入排序的优势**：对于小规模数据（阈值通常设为 16~32），插入排序由于常数极小、缓存友好，实际运行速度反而快于快排和堆排。当递归划分子数组大小低于阈值时切换到插入排序，可以显著提升整体性能。

#### 1.2 内省排序的核心思想

Introsort 以快速排序为主线，同时引入两个保护机制：

1. **深度监控（Depth Check）**：设定最大递归深度为 **2 × ⌊log₂(n)⌋**。当快速排序递归深度超过此阈值时，判定当前划分可能存在退化风险，立即切换到堆排序。由此将最坏时间复杂度严格控制在 O(n log n)。

2. **小数组优化（Threshold Switch）**：当子数组规模小于阈值（典型值为 16）时，不再递归调用快排，而是切换为插入排序。对近乎有序的小数组，插入排序几乎可以达到 O(n)。

```
Introsort 伪代码：

IntroSort(A, left, right, depthLimit):
    if right - left + 1 < THRESHOLD:   // 通常 THRESHOLD = 16
        对 A[left..right] 执行插入排序
        return
    if depthLimit == 0:                // 递归过深，切换到堆排序
        对 A[left..right] 执行堆排序（使用 make_heap + sort_heap）
        return
    pivot = MedianOfThree(A, left, right)  // 三数取中选 pivot
    p = Partition(A, left, right, pivot)
    IntroSort(A, left, p - 1, depthLimit - 1)
    IntroSort(A, p + 1, right, depthLimit - 1)
```

#### 1.3 递归深度阈值的推导

设数组长度为 n。在理想情况下，每次划分将数组分为两半，递归深度为 log₂(n)。考虑到划分可能不均匀（如 pivot 选在 1/4 位置），深度最多到 2 × log₂(n)。因此将 depthLimit 设定为 2⌊log₂(n)⌋ 是合理的：只要递归深度在此范围内，使用的是快速排序；一旦超过，说明划分持续糟糕，切换到堆排序保证 O(n log n)。

#### 1.4 三数取中（Median of Three）

为防止快速排序在已排序或几乎排序数据上退化，`std::sort` 的 pivot 选择通常使用三数取中法：取 `A[left]`、`A[mid]`、`A[right]` 的中位数作为 pivot。对于刻意构造的反例（如 killer sequence），Introsort 的深度监控机制仍会触发堆排序。

---

### 2. 自定义比较函数的多种写法

在 C++ 中有三种主流方式定义自定义排序规则，各有适用场景。

#### 2.1 方式一：函数指针

```cpp
bool cmp_desc(int a, int b) {
    return a > b;  // 降序：a > b 意味着 a 应排在 b 前面
}
sort(v.begin(), v.end(), cmp_desc);
```

**注意**：比较函数必须满足**严格弱序（Strict Weak Ordering）**：
- `cmp(a, a)` 必须为 `false`（非自反）
- 若 `cmp(a, b)` 为 `true`，则 `cmp(b, a)` 必须为 `false`（非对称）
- 若 `cmp(a, b)` 和 `cmp(b, c)` 均为 `true`，则 `cmp(a, c)` 必须为 `true`（传递性）

常见错误：写成 `return a >= b;` 违反了非自反性，会导致 `sort` 出现未定义行为（如数组越界崩溃）。

#### 2.2 方式二：仿函数（函数对象）

```cpp
struct Cmp {
    bool operator()(int a, int b) const {
        return a > b;
    }
};
sort(v.begin(), v.end(), Cmp());
// 或者用于优先队列等容器
priority_queue<int, vector<int>, Cmp> pq;
```

**优点**：仿函数是类型的一部分，编译器可以内联 `operator()`，性能通常略优于函数指针。在作为模板参数（如 `priority_queue`、`set`、`map`）时，仿函数是必须的写法。

#### 2.3 方式三：Lambda 表达式（C++11+，推荐）

```cpp
sort(v.begin(), v.end(), [](int a, int b) {
    return a > b;
});
```

**优点**：写法简洁，可以捕获外部变量，适合临时比较逻辑。在刷题场景下推荐使用，因为代码紧凑且编译器同样可以内联。

**带捕获的 Lambda 示例**：
```cpp
int key = 5;
sort(v.begin(), v.end(), [key](int a, int b) {
    return abs(a - key) < abs(b - key);  // 按与 key 的距离排序
});
```

#### 2.4 多关键字排序

```cpp
struct Stu { string name; int score, id; };

// 先按 score 降序，score 相同时按 id 升序
sort(stu.begin(), stu.end(), [](const Stu& a, const Stu& b) {
    if (a.score != b.score) return a.score > b.score;
    return a.id < b.id;
});
```

多关键字排序时，**不要分多次 sort**。如果先按次要关键字排序，再按主要关键字排序（使用 `stable_sort`），虽然可行，但不如一次 sort 清晰且更不易出错。

---

### 3. stable_sort 的使用场景

`sstable_sort` 保证相等元素的相对顺序不会改变。

```cpp
struct Rec { string name; int score; }
// 第一轮：按 name 排序（保证姓名相同的在一起）
// 第二轮：按 score 排序，但希望 score 相同时保留第一轮的 name 顺序
stable_sort(rec.begin(), rec.end(), [](const Rec& a, const Rec& b) {
    return a.score > b.score;
});
```

**典型场景**：
- 已按某关键字排好序的数据，需要再按另一个关键字排序，且希望保留前一关键字内部的顺序
- 处理带时间戳的数据，需要先按优先级排序，但同优先级的保留时间顺序

**为什么不总是用 `stable_sort`？** `stable_sort` 实现通常是归并排序的变体，需要 O(n) 额外内存（而 `sort` 是 O(log n) 栈空间），且常数因子略大。在不需要稳定性时，使用 `sort` 更高效。

---

### 4. nth_element 的 O(n) 快速选择原理

`nth_element` 基于快速排序的划分操作，但每次递归只处理一侧。

```cpp
nth_element(v.begin(), v.begin() + k, v.end());
// 效果：v[k] 位置的元素恰好是第 k 小的元素（0-based）
// v[0..k-1] <= v[k] <= v[k+1..n-1]  （但不保证各自区间内部有序）
```

#### 4.1 算法描述（QuickSelect）

```
QuickSelect(A, left, right, k):
    // 在 A[left..right] 中找第 k 小的元素
    while left < right:
        p = Partition(A, left, right)  // 以选定的 pivot 进行划分
        // A[left..p-1] <= A[p] <= A[p+1..right]
        if k == p:
            return A[k]                // 找到
        elif k < p:
            right = p - 1              // 只处理左侧
        else:
            left = p + 1               // 只处理右侧
    return A[left]                     // left == right == k
```

#### 4.2 时间复杂度分析

每次 Partition 是 O(n) 的（n 为当前区间长度）。因为每次只递归一侧：
- 期望情况下：每次划分后区间大致减半 → T(n) = T(n/2) + O(n) → O(n)
- 最坏情况（每次 pivot 都是极值，每次只排除一个元素）→ T(n) = T(n-1) + O(n) → O(n²)

标准库中的 `nth_element` 通常也使用了内省策略（类似于 Introsort），当检测到递归过深时切换到其他选择算法，保证 O(n) 的平均复杂度。

#### 4.3 典型应用

```cpp
// 应用中位数
int n = v.size();
nth_element(v.begin(), v.begin() + n/2, v.end());
int median = v[n/2];

// 求前 k 小的元素（注意区间内部无序）
nth_element(v.begin(), v.begin() + k - 1, v.end());
sort(v.begin(), v.begin() + k);  // 如果需要对前 k 个排序
```

#### 4.4 与 sort / partial_sort 的区别

| 接口 | 用途 | 复杂度 | 结果的有序性 |
|------|-----|-------|------------|
| `sort(b, e)` | 全排序 | O(n log n) | 全局有序 |
| `nth_element(b, b+k, e)` | 找第 k 小元素 | O(n) | 仅保证第 k 个元素就位，前后区间无序 |
| `partial_sort(b, b+k, e)` | 前 k 个最小元素并排序 | O(n log k) | 前 k 个有序，其余无序 |

当只需要找第 k 小/大的元素时，**不要用 sort**，`nth_element` 的 O(n) 比 sort 的 O(n log n) 快很多。例如 n = 5×10⁶ 时，O(n) 约 5×10⁶ 次操作，而 O(n log n) 约 1.1×10⁸ 次操作，差距超过 20 倍。

---

### 5. next_permutation / prev_permutation 的原理和用法

#### 5.1 字典序排列生成算法

`next_permutation` 按照**字典序（lexicographical order）**生成下一个排列。

**算法步骤**（以生成下一个排列为例，设当前排列为 a[0..n-1]）：

1. 从右向左找到第一个**升序对**：找到最大的下标 i，使得 `a[i] < a[i+1]`。如果不存在这样的 i（即整个序列是降序的），说明当前排列是最后一个排列，不存在下一个排列。

2. 从右向左找到第一个大于 a[i] 的元素：找到最大的下标 j（j > i），使得 `a[j] > a[i]`。由于 i 右侧元素是降序的，这是存在的。

3. 交换 a[i] 和 a[j]。

4. 将 a[i+1..n-1] 反转（reverse）。因为交换后 i 右侧仍是降序的，反转可使这部分变为升序，得到字典序刚好比原排列大的排列。

**示例**：排列 {1, 3, 5, 4, 2}
- 步骤1：从右向左找 a[i] < a[i+1] → i = 1（a[1]=3 < a[2]=5）
- 步骤2：从右向左找 a[j] > 3 → j = 3（a[3]=4 > 3）
- 步骤3：交换 a[1] 和 a[3] → {1, 4, 5, 3, 2}
- 步骤4：反转 i+1 到末尾 → {1, 4, 2, 3, 5} ← 下一个排列

**时间复杂度**：O(n)，最坏情况下需要扫描整个序列。

#### 5.2 基本用法

```cpp
vector<int> v = {1, 2, 3};

// 从当前排列开始，生成所有字典序大于当前排列的排列
do {
    // 处理当前排列 v
    for (int x : v) cout << x << " ";
    cout << "\n";
} while (next_permutation(v.begin(), v.end()));

// 输出：
// 1 2 3
// 1 3 2
// 2 1 3
// 2 3 1
// 3 1 2
// 3 2 1
```

**关键注意**：如果要生成全排列（所有 n! 个排列），**初始序列必须已排序（升序）**。因为 `next_permutation` 只生成比当前排列字典序更大的排列。

#### 5.3 实用技巧

```cpp
// 判断是否还有下一个排列
if (next_permutation(v.begin(), v.end())) {
    // 存在下一个排列，v 已被修改
} else {
    // 当前已是最大排列，v 被重置为最小排列
}

// 手动全排列生成（保证包含初始排列）
sort(v.begin(), v.end());
do {
    // 处理排列
} while (next_permutation(v.begin(), v.end()));

// prev_permutation 生成上一个排列
sort(v.begin(), v.end(), greater<int>());  // 降序排列作为起始
do {
    // 从大到小生成排列
} while (prev_permutation(v.begin(), v.end()));
```

#### 5.4 典型应用场景

- 暴力枚举排列：n ≤ 10 时 n! ≈ 3.6×10⁶，可接受
- 求解旅行商问题（TSP）的小数据情况
- 检测某个排列是否可以通过变换得到
- 字符串的字典序问题

---

### 6. lower_bound / upper_bound / binary_search 的正确使用与常见误区

这三个函数都只能在**已排序**的序列上使用，且基于二分查找实现，时间复杂度 O(log n)。

#### 6.1 函数语义

| 函数 | 返回值 | 含义 | 等效条件 |
|------|-------|------|---------|
| `lower_bound(b, e, x)` | 迭代器 | 第一个 **>= x** 的位置 | 插入 x 且保持有序的最前位置 |
| `upper_bound(b, e, x)` | 迭代器 | 第一个 **> x** 的位置 | 插入 x 且保持有序的最后位置 |
| `binary_search(b, e, x)` | bool | x 是否存在 | `lower_bound(b, e, x) != e && *pos == x` |

```cpp
vector<int> v = {1, 2, 2, 2, 3, 5};

auto lb = lower_bound(v.begin(), v.end(), 2);  // 指向第1个2（下标1）
auto ub = upper_bound(v.begin(), v.end(), 2);  // 指向3（下标4）

// 等于 x 的元素个数：ub - lb
int cnt = upper_bound(v.begin(), v.end(), 2)
        - lower_bound(v.begin(), v.end(), 2);  // cnt = 3

// 小于 x 的元素个数：lb - begin
int lt_cnt = lb - v.begin();  // lt_cnt = 1

// 大于等于 x 的元素个数：end - lb
int ge_cnt = v.end() - lb;  // ge_cnt = 5
```

#### 6.2 自定义比较函数

```cpp
// 降序序列中使用二分查找
vector<int> v = {9, 7, 5, 3, 1};
auto it = lower_bound(v.begin(), v.end(), 5, greater<int>());
// 在降序序列中，lower_bound 返回第一个 <= 5 的位置（指向 5）
```

**注意**：自定义比较器的语义与 sort 的语义一致——`comp(element, value)` 表示 element 在 value 之前。在降序中 `greater<int>()` 表示 a > b 时 a 在 b 前面，所以 `lower_bound` 找到的是第一个"不满足 comp 使得 value 排在它前面"的位置。

#### 6.3 常见误区

**误区1：对未排序的序列使用二分查找**

这是最致命也是最常见的错误。二分查找的正确性严格依赖序列的有序性。如果序列未排序，返回结果不可预测（可能恰好落在中间某处，但不是语义正确的位置）。

**误区2：对 `set` / `map` / `multiset` 使用 `std::lower_bound`**

```cpp
set<int> s = {1, 3, 5, 7, 9};

// ❌ 错误：O(n) 遍历！
auto it = lower_bound(s.begin(), s.end(), 5);

// ✅ 正确：O(log n) 二分
auto it = s.lower_bound(5);
```

**原因**：`set` 的迭代器是双向迭代器（BidirectionalIterator），不是随机访问迭代器（RandomAccessIterator）。`std::lower_bound` 对于非随机访问迭代器只能退化为线性查找 O(n)。而 `set::lower_bound` 利用红黑树的内部结构，实现真正的 O(log n) 二分。

**误区3：忘记类型匹配导致二分失效**

```cpp
int a[] = {1, 2, 3, 4, 5};
// lower_bound 要求区间内的元素类型与查找值类型可比
// 如果区间元素是结构体，需要重载 < 运算符或提供比较函数
```

**误区4：返回值直接解引用而未检查**

```cpp
auto it = lower_bound(v.begin(), v.end(), 100);
// 如果 100 大于所有元素，it == v.end()，解引用是未定义行为
cout << *it;  // ❌ 可能崩溃
```

---

### 7. 离散化的两种实现方法

离散化是处理大范围坐标/数值问题的核心技术。当数据取值范围很大（如 -10⁹ ~ 10⁹）但实际出现的数据个数很小（如 n ≤ 10⁵）时，需要将原始数值映射到较小的连续整数范围。

#### 7.1 方法一：排序 + 去重 + 二分查找（推荐）

```cpp
vector<int> raw = {100, 2000000000, 50, 100, -500};  // 原始数据（可能有重复）
vector<int> sorted;

// 第1步：将所有需要离散化的值收集到 sorted
sorted = raw;
sort(sorted.begin(), sorted.end());

// 第2步：去重
sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
// sorted = {-500, 50, 100, 2000000000}

// 第3步：查找映射值（1-based 索引常用在树状数组等场景）
auto get_id = [&](int x) {
    return lower_bound(sorted.begin(), sorted.end(), x) - sorted.begin() + 1;
};

int id_of_100 = get_id(100);  // 返回 3
```

**优点**：
- 时间复杂度 O(n log n)，空间 O(n)
- 通过 lower_bound 查找是 O(log n)
- 映射值紧凑连续，适合作为数组下标（如用于树状数组、线段树）

**缺点**：
- 需要预先收集所有值
- 实现代码略多

#### 7.2 方法二：map 映射（简单但常数大）

```cpp
map<int, int> id;
int cnt = 0;
auto get_id = [&](int x) {
    if (!id.count(x)) id[x] = ++cnt;  // 首次出现才分配新 ID
    return id[x];
};
```

**优点**：
- 实现简单直观
- 不需要预先收集值，适合在线处理
- 不改变原始值的顺序

**缺点**：
- 每次查找 O(log n)，但 map 的红黑树常数较大（约为 vector+lower_bound 的 3~5 倍）
- 如果值全部预先已知，用方法一的性能更好

#### 7.3 方法对比

| 维度 | 排序+去重+二分 | map 映射 |
|------|-------------|---------|
| 预处理时间 | O(n log n) | O(n log n) |
| 单次查询 | O(log n)（常数小） | O(log n)（常数大） |
| 空间 | O(n)（连续） | O(n)（每个节点有额外指针开销） |
| 适用场景 | 离线、已知全部数据 | 在线、数据逐步给出 |
| 与数据结构配合 | 直接用作数组下标 | 需额外转换 |

**典型应用**：
- 静态区间统计问题（配合前缀和/树状数组）
- 坐标压缩后二维前缀和
- 权值线段树/主席树中的值域压缩

---

### 8. unique 的去重原理

很多人误以为 `unique` 会"删除"重复元素，实际上它**不改变容器大小**。

```cpp
vector<int> v = {1, 2, 2, 3, 3, 3, 4};

auto it = unique(v.begin(), v.end());
// 效果：将不重复的元素移到前面，返回"新结尾"的迭代器
// v = {1, 2, 3, 4, ?, ?, ?}   （? 是未定义内容，通常是原值或移动后的值）
// it 指向下标 4（第一个 '?' 的位置）

// 必须配合 erase 才能真正删除：
v.erase(it, v.end());
// v = {1, 2, 3, 4}
```

**内部实现原理**：`unique` 使用双指针技术：
1. 维护一个"写入指针" `result`，初始指向 begin
2. 从第二个元素开始遍历，如果当前元素与上一个已保留的元素不同，则将其写入 result 位置并后移 result
3. 返回 result（即去重后的 end 迭代器）

```cpp
// unique 的简化实现
template<typename It>
It unique(It first, It last) {
    if (first == last) return last;
    It result = first;
    while (++first != last) {
        if (!(*result == *first)) {
            *(++result) = *first;
        }
    }
    return ++result;
}
```

**关键注意**：
- `unique` 只去除**相邻**的重复元素。如果重复元素不连续，需要先 `sort`
- 标准用法 `v.erase(unique(v.begin(), v.end()), v.end())` 被称为"erase-remove idiom"
- 如果只是为了计数不同元素个数，直接用 `unique(v.begin(), v.end()) - v.begin()` 即可，无需 erase

---

## 💻 代码模板

### 模板1：离散化（排序+去重+二分，完整版）

```cpp
#include <bits/stdc++.h>
using namespace std;

// 离散化模板：返回一个映射函数
auto discretize(vector<int>& raw) {
    vector<int> sorted = raw;
    sort(sorted.begin(), sorted.end());
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
    
    // 返回一个函数，输入原始值，输出 1-based 的映射编号
    return [sorted](int x) {
        return lower_bound(sorted.begin(), sorted.end(), x) - sorted.begin() + 1;
    };
}

// 使用示例
int main() {
    vector<int> a = {1000000000, -500, 3, 1000000000, 7};
    auto get_id = discretize(a);
    cout << get_id(-500) << "\n";  // 输出该值对应的离散化编号
    return 0;
}
```

### 模板2：nth_element 求中位数与前k小

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    vector<int> a(n);
    
    // 求中位数（0-based 索引，n/2 取上中位数或下中位数均可）
    nth_element(a.begin(), a.begin() + n / 2, a.end());
    int median = a[n / 2];
    
    // 求第 k 小的元素（1-based）
    nth_element(a.begin(), a.begin() + k - 1, a.end());
    int kth = a[k - 1];
    
    // 求前 k 小的元素（不保证有序）+ 可选排序
    nth_element(a.begin(), a.begin() + k, a.end());
    sort(a.begin(), a.begin() + k);  // 如果需要对前 k 个排序
    
    return 0;
}
```

### 模板3：多关键字排序

```cpp
struct Node {
    int score;   // 主关键字：降序
    int time;    // 次关键字：升序（早的在前）
    int id;      // 第三关键字：升序
};

sort(a, a + n, [](const Node& x, const Node& y) {
    if (x.score != y.score) return x.score > y.score;
    if (x.time != y.time) return x.time < y.time;
    return x.id < y.id;
});
```

### 模板4：lower_bound / upper_bound 常用模式

```cpp
// 在有序数组 a[0..n-1] 中
int x; // 查询值

// 第一个 >= x 的位置
int pos_ge = lower_bound(a, a + n, x) - a;

// 第一个 > x 的位置
int pos_gt = upper_bound(a, a + n, x) - a;

// x 的出现次数
int cnt = upper_bound(a, a + n, x) - lower_bound(a, a + n, x);

// x 是否存在
bool exist = binary_search(a, a + n, x);

// 小于 x 的元素个数
int cnt_lt = lower_bound(a, a + n, x) - a;

// 大于 x 的元素个数
int cnt_gt = n - (upper_bound(a, a + n, x) - a);
```

---

## ⚠️ 易错点与优化技巧

### 易错点

1. **比较函数写成 `<=` 或 `>=`**：`sort` 的比较函数必须严格小于（`<`）。写成 `<=` 会导致相等元素判定为"应该在前面"，违反严格弱序，可能造成数组越界或死循环。

2. **`next_permutation` 使用前未排序**：如果初始序列不是升序的，`do-while` 循环只能生成部分排列，会遗漏排列。务必在最外层调用前确保序列已排序。

3. **对未排序数据使用 `lower_bound`**：结果完全不可靠。即使碰巧返回了一个位置，语义也不正确。

4. **对 `set` 使用 `std::lower_bound`**：如前所述，这会退化为 O(n) 的线性查找。应使用成员函数 `set::lower_bound()`。

5. **`nth_element` 后直接认为前 k 个元素有序**：`nth_element` 只保证第 k 个元素就位，前后区间都不保证有序。

6. **`unique` 后忘记 `erase`**：`unique` 只返回新结尾，不释放多余空间。如果不 erase，容器大小不变，末尾可能存在无意义的残留值。

7. **二分查找返回值直接解引用**：`lower_bound` 可能返回 `end()`，必须先检查。

8. **二分查找的迭代器类型的陷阱**：对 `vector` 使用 `v.begin()`，对数组使用 `a`（数组名退化为指针），混用可能导致编译错误。对于数组，用 `a`、`a + n` 作为范围参数；对于 `vector`，用 `v.begin()`、`v.end()`。

### 性能优化技巧

1. **排序前预分配**：如果已知大致结果，`v.reserve(n)` 可以减少 vector 扩容带来的拷贝开销。

2. **用 `emplace_back` 代替 `push_back`**：减少一次拷贝/移动构造。

3. **对于大型结构体的排序**：传引用（`const T&`）而非传值，避免每次比较都拷贝整个结构体。

4. **离散化时先 reserve 空间**：如果数据量已知，`sorted.reserve(raw.size())` 可减少扩容。

5. **n ≤ 16 时的微优化**：对于很小的数组，插入排序（或直接 sort，因为 sort 内部已有阈值优化）通常是最佳选择。不要在小数组上使用复杂的 O(n log n) 算法。

6. **避免不必要的 stable_sort**：如果不需要稳定性，`sort` 的空间和时间都更优。

7. **二分查找替代线性查找**：任何时候涉及"找边界"、"找位置"的问题，先想能否排序后二分。

8. **使用 `std::lower_bound` 替代手写二分**：手写二分极易出错（边界 ±1 问题、死循环问题），标准库版本经过严格测试，正确性有保障。

---

## 📝 真题精练

### 题目1：区间覆盖统计（离散化 + 差分）

**【题目描述】**

在数轴上有 n 个区间 [l_i, r_i]，坐标范围很大（|l_i|, |r_i| ≤ 10⁹）。你需要回答 m 个询问，每个询问给出一个整数 x，问 x 被多少个区间覆盖。注意区间端点可能非常大，不能开数组直接标记。

**【输入格式】**

第一行两个整数 n, m（1 ≤ n, m ≤ 2×10⁵）。
接下来 n 行，每行两个整数 l_i, r_i（|l_i|, |r_i| ≤ 10⁹，l_i ≤ r_i）。
接下来 m 行，每行一个整数 x（|x| ≤ 10⁹），表示询问的坐标。

**【输出格式】**

对于每个询问，输出一行一个整数，表示点 x 被多少个区间覆盖。

**【样例输入】**
```
3 3
1 5
3 8
2 6
3
7
10
```

**【样例输出】**
```
3
2
0
```

**【数据范围】**

- 对于 40% 的数据，n, m ≤ 1000，坐标 ≤ 10⁴
- 对于 100% 的数据，n, m ≤ 2×10⁵，|坐标| ≤ 10⁹

**【解题思路】**

坐标范围高达 10⁹，不能直接开数组。但实际出现的坐标数量（区间端点 + 询问点）最多为 2n + m ≤ 6×10⁵，使用离散化压缩到整数下标上。

**步骤**：
1. 收集所有"有意义的坐标"：所有 l_i、r_i+1（因为差分需要在 r_i+1 处减去贡献）、所有询问的 x
2. 对坐标排序去重得到离散化映射
3. 使用差分数组 diff[]：对于每个区间 [l, r]，对映射后的 l 位置 +1，r+1 位置 -1
4. 对 diff 求前缀和得到每个位置的覆盖数
5. 对每个询问 x，二分查找其映射位置，输出对应的前缀和值

**【AC代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> L(n), R(n);
    vector<int> queries(m);
    vector<int> coords;  // 收集所有需要离散化的坐标
    coords.reserve(2 * n + m);

    for (int i = 0; i < n; ++i) {
        cin >> L[i] >> R[i];
        coords.push_back(L[i]);
        coords.push_back(R[i] + 1);  // 差分右端点+1
    }
    for (int i = 0; i < m; ++i) {
        cin >> queries[i];
        coords.push_back(queries[i]);
    }

    // 离散化：排序 + 去重
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());

    // 将坐标映射到 0-based 索引
    auto idx = [&](int x) {
        return lower_bound(coords.begin(), coords.end(), x) - coords.begin();
    };

    // 差分数组
    int sz = coords.size();
    vector<int> diff(sz + 1, 0);

    for (int i = 0; i < n; ++i) {
        diff[idx(L[i])]++;
        diff[idx(R[i] + 1)]--;
    }

    // 前缀和
    vector<int> cover(sz, 0);
    cover[0] = diff[0];
    for (int i = 1; i < sz; ++i) {
        cover[i] = cover[i - 1] + diff[i];
    }

    // 回答询问
    for (int q : queries) {
        cout << cover[idx(q)] << "\n";
    }

    return 0;
}
```

**【复杂度分析】**

- 时间复杂度：O((n + m) log (n + m))
  - 坐标收集 O(n + m)
  - 排序 O((n + m) log (n + m))
  - 差分填充 O(n)
  - 前缀和 O(n + m)
  - 每个询问二分 O(m log (n + m))
- 空间复杂度：O(n + m)，用于存储坐标、差分数组和前缀和

---

### 题目2：第 K 小数（多种解法对比）

**【题目描述】**

给定一个长度为 n 的整数序列 a_1, a_2, ..., a_n。有 q 次询问，每次询问给出一个整数 k，你需要输出序列中第 k 小的数（k 从 1 开始计数）。

**【输入格式】**

第一行两个整数 n, q（1 ≤ n ≤ 5×10⁶，1 ≤ q ≤ 10）。
第二行 n 个整数 a_i（|a_i| ≤ 10⁹）。
接下来 q 行，每行一个整数 k（1 ≤ k ≤ n）。

**【输出格式】**

对于每个询问，输出一行一个整数，表示第 k 小的数。

**【样例输入】**
```
6 3
5 2 7 1 8 3
1
3
6
```

**【样例输出】**
```
1
3
8
```

**【数据范围】**

- 对于 30% 的数据，n ≤ 1000，q ≤ 10
- 对于 60% 的数据，n ≤ 10⁵，q ≤ 10
- 对于 100% 的数据，n ≤ 5×10⁶，q ≤ 10

**【解题思路】**

n 高达 5×10⁶，q ≤ 10。我们对比不同方法的效率：

**方法1：全排序 (sort)**
- 时间复杂度：O(n log n) ≈ 5×10⁶ × 23 ≈ 1.15×10⁸ 次比较
- 对于 n = 5×10⁶ 来说可能较慢，但 O2 优化下 C++ 的 sort 仍然可能勉强通过

**方法2：nth_element**
- 时间复杂度：O(n) 期望，每次询问约 5×10⁶ 次操作
- q = 10 次询问总操作约 5×10⁷，远优于 sort

**方法3：优先队列（维护大小为 k 的最大堆）**
- 每次询问 O(n log k)，比 nth_element 差

**方法4：快速选择（手写）**
- 理论上 O(n)，但实现复杂度高，不如直接用 nth_element

**推荐方法**：本题 q ≤ 10，每次 O(n) 的 nth_element 总复杂度 O(qn) ≈ 5×10⁷，完全可行。由于 q 较小且 n 较大，nth_element 显著优于 sort（只需 O(n) 而非 O(n log n)）。且 nth_element 的实现经过高度优化，常数很小。

**【AC代码 - nth_element 法】**

```cpp
#include <bits/stdc++.h>
using namespace std;

// 使用快速读入优化（n 高达 5e6，cin 可能较慢）
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
    return x * f;
}

int main() {
    int n = read(), q = read();
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = read();
    }

    // 复制一份原始数组，因为 nth_element 会修改数组
    vector<int> b = a;

    while (q--) {
        int k = read();
        // 恢复数组（对于多次询问，每次需要从未被破坏的副本恢复）
        // 或者每次都 nth_element 同一个副本
        
        // 方法A：对副本操作
        copy(a.begin(), a.end(), b.begin());
        nth_element(b.begin(), b.begin() + k - 1, b.end());
        printf("%d\n", b[k - 1]);

        // 注意：如果 q 较大且 n 很大，多次 copy 的 O(nq) 可能成为瓶颈。
        // 本题 q ≤ 10，完全没问题。
    }

    return 0;
}
```

**【复杂度分析】**

- 时间复杂度：O(q × n)（每次 nth_element 期望 O(n)）+ O(q × n)（每次 copy）+ 读入 O(n)
  - 总计约 O(qn)，在 q=10, n=5×10⁶ 时约 5×10⁷ ~ 1×10⁸ 次操作，可在 1~2 秒内完成
- 空间复杂度：O(n)（存储数组和副本）

**【扩展讨论】**

如果 q 很大（如 q ≤ 10⁵），上述方法 O(qn) 不可行。此时应：
1. 先对整个数组排序 O(n log n)
2. 每次询问直接通过下标访问 O(1)
3. 总复杂度 O(n log n + q)，适用于 q 较大的情况

**决策原则**：比较 O(n log n) 与 O(qn)，选择较小的。当 q ≤ log n（本题 n=5×10⁶ 时 log n ≈ 23）时，nth_element 更优；当 q 较大时，直接 sort 更优。

---

## 🎯 本课小结

| 知识点 | 核心内容 | 复杂度 | 关键注意事项 |
|--------|---------|--------|-------------|
| Introsort | 快排 + 堆排 + 插入的混合排序 | O(n log n) | 深度阈值 2log₂n，小数组阈值 16 |
| 自定义比较 | 函数指针 / 仿函数 / Lambda | — | 必须严格小于 `<`，不能 `<=` |
| stable_sort | 保持相等元素的相对顺序 | O(n log n), O(n)空间 | 不需要稳定性时用 sort |
| nth_element | 基于 partition 的快速选择 | O(n) | 只保证第 k 个元素就位 |
| next_permutation | 字典序排列生成 | O(n) | 生成所有排列前需先排序 |
| lower_bound | 第一个 >= x 的位置 | O(log n) | 序列必须有序 |
| upper_bound | 第一个 > x 的位置 | O(log n) | 序列必须有序 |
| 离散化 | 大坐标 → 小下标映射 | O(n log n) | 排序 + 去重 + 二分 优于 map |
| unique | 去除相邻重复 | O(n) | 必须配合 erase 才能真正删除 |

**核心思想**：algorithm 库的高级函数是 CSP-S 中处理排序、查找、排列问题的利器。理解其内部实现原理有助于我们在正确场景下做出最优选择——不要一看到"找第k小"就用 sort，不要一看到"去重"就认为 unique 会改变容器大小，不要一看到"二分查找"就忘记检查序列是否有序。
