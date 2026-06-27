# 第31课：STL sort 与自定义排序

## 🎯 考纲要求
- 掌握 C++ STL 中 `sort()` 函数的基本用法（默认升序）
- 掌握自定义比较函数 `cmp` 的编写方法，实现降序或多关键字排序
- 理解 `greater<int>()` 和 `less<int>()` 仿函数的使用
- 掌握结构体多关键字排序（先按 A 降序，A 相同按 B 升序等）
- 了解 `stable_sort()` 稳定排序的用法和适用场景

## 📖 知识精讲

前两节课我们学习了冒泡、选择、插入和计数等基础排序算法，这些算法帮助我们理解排序的本质。但在实际编程竞赛中，CSP-J 复赛几乎不需要手写排序——C++ 标准库提供了强大的 `sort()` 函数，时间复杂度为 O(n log n)，效率远超我们手写的 O(n²) 算法。本节课我们就来系统学习 `sort()` 的使用方法和自定义排序技巧。

### 一、sort 函数基本用法（默认升序）

`sort()` 定义在 `<algorithm>` 头文件中，用于对数组或容器中的元素进行排序。它的基本调用形式为：

```cpp
sort(起始地址, 结束地址);
```

其中：
- **起始地址**：指向待排序区间第一个元素的指针/迭代器
- **结束地址**：指向待排序区间**最后一个元素的下一个位置**的指针/迭代器（即左闭右开区间 `[begin, end)`）

**对普通数组排序**：

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int a[] = {5, 3, 8, 1, 9, 2, 7, 4, 6};
    int n = 9;
    
    // sort(a, a + n)：对 a[0] 到 a[n-1] 排序，默认升序
    sort(a, a + n);
    
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
    // 输出：1 2 3 4 5 6 7 8 9
    
    return 0;
}
```

**关键理解**：`a` 是指向 `a[0]` 的指针，`a + n` 是指向 `a[n]` 的指针（超出数组末尾一个位置）。所以 `sort(a, a + n)` 实际上排序的是 `[a[0], a[n-1]]` 这个闭区间。

**对部分元素排序**：如果我们只想排序数组中的某一段，比如只排序 `a[2]` 到 `a[6]`：

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int a[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int n = 9;
    
    // 只排序 a[2] 到 a[6]（共 5 个元素）
    sort(a + 2, a + 7);  // 区间 [a+2, a+7) 即 a[2]~a[6]
    
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
    // 输出：9 8 3 4 5 6 7 2 1
    // a[0]~a[1] 和 a[7]~a[8] 维持原样
    
    return 0;
}
```

**对 vector 排序**：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> v = {5, 3, 8, 1, 9, 2};
    
    sort(v.begin(), v.end());  // 使用迭代器
    
    for (int x : v) {
        cout << x << " ";
    }
    cout << endl;
    // 输出：1 2 3 5 8 9
    
    return 0;
}
```

### 二、自定义比较函数 cmp

`sort()` 的完整调用形式实际上是三参数版本：

```cpp
sort(起始地址, 结束地址, 比较函数);
```

第三个参数是一个**比较函数**（或仿函数），用于定义排序规则。比较函数 `cmp(a, b)` 需要返回一个 `bool` 值：
- 返回 `true`：表示 `a` 应该**排在 `b` 的前面**
- 返回 `false`：表示 `a` 不应该排在 `b` 的前面（即 `b` 排在 `a` 前面或二者等价）

**重要理解**：cmp 返回 true 的语义是 "a 应当排在 b 前面"，而不是 "a < b"。初学者最容易搞混这点。默认的升序排序实际上等价于 `cmp(a, b) = (a < b)`，即较小的数排在前面。

**实现降序排序**：

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

// 自定义比较函数：降序
// 返回 true 表示 a 应该排在 b 前面
bool cmp(int a, int b) {
    return a > b;  // 如果 a > b，a 排在 b 前面 → 大的在前 → 降序
}

int main() {
    int a[] = {5, 3, 8, 1, 9, 2};
    int n = 6;
    
    sort(a, a + n, cmp);  // 使用自定义比较函数
    
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
    // 输出：9 8 5 3 2 1
    
    return 0;
}
```

**理解 cmp 的逻辑**：这里的 `cmp(a, b)` 返回 `a > b`。当 a=9, b=3 时，`a > b` 为 true，表示 9 排在 3 前面。所以大的数都排在前面，实现了降序。

### 三、仿函数 greater<int>() 和 less<int>()

C++ STL 提供了两个常用的仿函数（函数对象），可以直接作为 `sort()` 的第三个参数：

- **`greater<int>()`**：降序排序（从大到小）。内部等价于 `return a > b;`
- **`less<int>()`**：升序排序（从小到大）。这是默认行为，内部等价于 `return a < b;`

```cpp
#include <iostream>
#include <algorithm>
#include <functional>  // greater 和 less 需要此头文件
using namespace std;

int main() {
    int a[] = {5, 3, 8, 1, 9, 2};
    int n = 6;
    
    // 方法 1：使用 greater<int>() 降序
    sort(a, a + n, greater<int>());
    
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
    // 输出：9 8 5 3 2 1
    
    // 方法 2：使用 less<int>() 升序（默认，通常省略）
    sort(a, a + n, less<int>());
    
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
    // 输出：1 2 3 5 8 9
    
    return 0;
}
```

**仿函数 vs 函数指针**：仿函数（Functor）是一个重载了 `operator()` 的类对象，`greater<int>()` 就是一个临时的仿函数对象。相比函数指针 `cmp`，仿函数可以被编译器内联优化，效率稍高一些。在实际比赛中，两种写法都可以，看个人习惯。自定义比较逻辑复杂时用 cmp 函数，简单降序时用 `greater<int>()` 最方便。

### 四、结构体多关键字排序

这是 CSP-J 中最常考、最实用的自定义排序场景。比如有一个学生信息结构体，要求：
- **先按总成绩降序排列**（成绩高的在前）
- **成绩相同时按学号升序排列**（学号小的在前）

**完整示例**：

```cpp
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

struct Student {
    int id;            // 学号
    string name;       // 姓名
    int score;         // 总成绩
};

// 多关键字比较函数
// 先按成绩降序，成绩相同按学号升序
bool cmp(const Student& a, const Student& b) {
    if (a.score != b.score) {
        return a.score > b.score;   // 成绩高的排前面（降序）
    }
    return a.id < b.id;             // 成绩相同，学号小的排前面（升序）
}

int main() {
    Student stu[] = {
        {101, "Alice", 85},
        {102, "Bob",   92},
        {103, "Carol", 85},
        {104, "David", 78},
        {105, "Eve",   92}
    };
    int n = 5;
    
    sort(stu, stu + n, cmp);
    
    cout << "排名  学号  姓名  成绩" << endl;
    cout << "---------------------" << endl;
    for (int i = 0; i < n; i++) {
        cout << " " << i+1 << "    "
             << stu[i].id << "   "
             << stu[i].name << "   "
             << stu[i].score << endl;
    }
    /*
    输出：
    排名  学号  姓名  成绩
    ---------------------
     1    102   Bob    92
     2    105   Eve    92
     3    101   Alice  85
     4    103   Carol  85
     5    104   David  78
    */
    
    return 0;
}
```

**多关键字排序的通用写法**：

```cpp
// 通用模式：优先级高的条件写前面
bool cmp(const Type& a, const Type& b) {
    if (a.field1 != b.field1) return a.field1 > b.field1;  // 第一关键字（降序）
    if (a.field2 != b.field2) return a.field2 < b.field2;  // 第二关键字（升序）
    return a.field3 < b.field3;                             // 第三关键字（升序）
}
```

**二级排序的简化写法**（当第二个条件也是排序时）：

```cpp
// 如果分数相同，可以简化为：
bool cmp(const Student& a, const Student& b) {
    if (a.score != b.score) return a.score > b.score;
    return a.id < b.id;
}
```

**使用 pair 进行双关键字排序**（无需写 cmp）：

```cpp
#include <iostream>
#include <algorithm>
#include <utility>
using namespace std;

int main() {
    // pair<int, int>：first=成绩(降序), second=学号(升序)
    // 注意：pair 的默认排序是先按 first 升序，first 相同按 second 升序
    // 如果需要降序成绩，可以取负数存储
    
    pair<int, int> arr[] = {
        {-85, 101},   // 成绩取负，实现降序效果
        {-92, 102},
        {-85, 103},
        {-78, 104},
        {-92, 105}
    };
    int n = 5;
    
    sort(arr, arr + n);  // 默认升序：负成绩升序 = 原来成绩降序
    
    for (int i = 0; i < n; i++) {
        cout << "成绩：" << -arr[i].first
             << " 学号：" << arr[i].second << endl;
    }
    /*
    输出：
    成绩：92 学号：102
    成绩：92 学号：105
    成绩：85 学号：101
    成绩：85 学号：103
    成绩：78 学号：104
    */
    
    return 0;
}
```

这个"取负数"的技巧非常实用：当需要按某个字段降序排序，但又不方便写 cmp 时（比如使用 `std::pair` 或优先队列），可以存储该字段的负值，利用默认的升序来实现降序的效果。

### 五、stable_sort 稳定排序

`stable_sort()` 与 `sort()` 用法几乎完全相同，唯一的区别是：**`stable_sort()` 保证排序的稳定性**（相等元素的相对顺序不变）。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

struct Item {
    int value;
    int originalIndex;
};

// 只按 value 排序（不特意处理相等情况）
bool cmp(const Item& a, const Item& b) {
    return a.value < b.value;
}

int main() {
    Item a[] = {{3, 0}, {1, 1}, {3, 2}, {2, 3}, {1, 4}};
    int n = 5;
    
    // 使用 stable_sort
    stable_sort(a, a + n, cmp);
    
    cout << "value  originalIndex" << endl;
    for (int i = 0; i < n; i++) {
        cout << "  " << a[i].value << "      " << a[i].originalIndex << endl;
    }
    /*
    输出：
    value  originalIndex
      1      1          ← originalIndex=1 的 1 在前（原来就在前面）
      1      4
      2      3
      3      0          ← originalIndex=0 的 3 在前（原来就在前面）
      3      2
    */
    
    // 对比：如果用 sort，相同 value 的元素相对顺序可能被改变
    sort(a, a + n, cmp);
    
    cout << endl << "sort 后的结果（相对顺序可能改变）：" << endl;
    for (int i = 0; i < n; i++) {
        cout << "  " << a[i].value << "      " << a[i].originalIndex << endl;
    }
    
    return 0;
}
```

**何时使用 stable_sort**：
- 已经按某个条件排好序，希望在此基础上按另一个条件排序，且保留之前的相对顺序
- 题目明确要求排序必须是稳定的
- 对结构体排序，且相等元素的先后有意义

**注意**：`stable_sort()` 在大多数实现中内部使用归并排序，时间复杂度也是 O(n log n)，但常数因子通常比 `sort()` 略大（`sort()` 通常使用内省排序，结合了快排、堆排和插入排序）。在不需要稳定性的场合，优先使用 `sort()`。

## 💻 代码模板

**模板一：基本 sort 用法**

```cpp
#include <algorithm>
using namespace std;

// 对数组 a[0..n-1] 升序排序
sort(a, a + n);                     // 默认升序

// 对数组 a[0..n-1] 降序排序
sort(a, a + n, greater<int>());     // 使用仿函数降序

// 对 vector 排序
vector<int> v;
sort(v.begin(), v.end());           // 升序
sort(v.begin(), v.end(), greater<int>());  // 降序
```

**模板二：自定义 cmp 函数模板**

```cpp
#include <algorithm>
using namespace std;

// 降序比较函数
bool cmpDesc(int a, int b) {
    return a > b;  // a > b 时 a 排前面 → 大的在前
}

// 使用
sort(a, a + n, cmpDesc);
```

**模板三：结构体多关键字排序模板**

```cpp
#include <algorithm>
#include <string>
using namespace std;

struct Node {
    int a, b, c;
};

// 先按 a 降序，a 相同按 b 升序，b 相同按 c 升序
bool cmp(const Node& x, const Node& y) {
    if (x.a != y.a) return x.a > y.a;
    if (x.b != y.b) return x.b < y.b;
    return x.c < y.c;
}

// 使用
Node arr[MAXN];
sort(arr, arr + n, cmp);
```

**模板四：stable_sort 稳定排序**

```cpp
#include <algorithm>
using namespace std;

// stable_sort 与 sort 用法完全相同，但保证稳定性
stable_sort(a, a + n);                     // 稳定升序
stable_sort(a, a + n, greater<int>());     // 稳定降序
stable_sort(a, a + n, cmp);                // 稳定自定义排序
```

## ⚠️ 易错点

- **cmp 函数的逻辑搞反**：记住口诀——`cmp(a, b)` 返回 `true` 表示 "a 应该排在 b 前面"。如果想让大的在前（降序），就写 `return a > b;`。很多同学会写成 `return a < b;` 却期望降序，这是最常见的错误。检验方法：想象 a=5, b=3，`a > b` 为 true，所以大的 5 排在 3 前面——确实是降序。

- **cmp 函数中相等时必须返回 false**：这是 C++ 标准的要求，比较函数必须满足"严格弱序"。如果 `a == b` 却返回 `true`，程序可能崩溃或产生未定义行为。比如 `return a >= b;` 就是错误的——当 a==b 时返回 true，同时 b==a 也返回 true，自相矛盾。正确写法是 `return a > b;`。

- **忘记 `#include <algorithm>`**：`sort()` 和 `stable_sort()` 定义在 `<algorithm>` 中。`greater<int>()` 和 `less<int>()` 定义在 `<functional>` 中（不过许多编译器 `<algorithm>` 也会间接包含它，但为了可移植性建议显式包含）。

- **区间范围写错**：`sort(a, a + n)` 排序的是 `a[0]` 到 `a[n-1]`，不是 `a[0]` 到 `a[n]`。因为第二个参数是"最后一个元素的下一个位置"。如果想排序 `a[l]` 到 `a[r]`（含两端），应该写 `sort(a + l, a + r + 1)`——注意是 `r+1` 不是 `r`。这是下标计算最易错的地方。

## 📝 真题精练

### 真题一：多关键字排序

**题目描述**：某次 CSP-J 模拟赛有 n 名选手参加。每名选手有编号 id 和分数 score。请按以下规则排序：
1. 分数高的排在前面（降序）
2. 分数相同时，编号小的排在前面（升序）

输出排序后的选手编号，用空格分隔。

**输入格式**：
- 第一行一个整数 n（1 ≤ n ≤ 1000）
- 接下来 n 行，每行两个整数 id 和 score（1 ≤ id ≤ 10000，0 ≤ score ≤ 600）

**输出格式**：
- 一行 n 个整数，为排序后的选手编号，用空格分隔

**样例输入**：
```
5
1 85
2 92
3 85
4 78
5 92
```

**样例输出**：
```
2 5 1 3 4
```

**完整 AC 代码**：

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1005;

struct Player {
    int id;
    int score;
} p[MAXN];

// 先按分数降序，分数相同按编号升序
bool cmp(const Player& a, const Player& b) {
    if (a.score != b.score) {
        return a.score > b.score;  // 分数高在前
    }
    return a.id < b.id;            // 编号小在前
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> p[i].id >> p[i].score;
    }
    
    sort(p, p + n, cmp);
    
    for (int i = 0; i < n; i++) {
        cout << p[i].id << (i < n - 1 ? " " : "\n");
    }
    
    return 0;
}
```

**考点分析**：本题是 CSP-J 中最经典的多关键字排序题型。核心是 cmp 函数的编写：先判断第一关键字，不相等时直接返回排序逻辑；相等时再判断第二关键字。这类题目几乎每年都会以不同面貌出现（可能换成分数、年龄、身高、字典序等），熟练掌握 cmp 的写法是必须的。

---

### 真题二：自定义排序规则题

**题目描述**：给定 n 个正整数，请将它们按照以下规则排序：
1. 如果一个数是偶数，另一个是奇数，则偶数排在奇数前面
2. 如果两个都是偶数，按数值从小到大排列（升序）
3. 如果两个都是奇数，按数值从大到小排列（降序）

输出排序后的序列。

**输入格式**：
- 第一行一个整数 n（1 ≤ n ≤ 1000）
- 第二行 n 个正整数，每个数不超过 10000

**输出格式**：
- 一行 n 个整数，为排序后的序列，用空格分隔

**样例输入**：
```
8
1 2 3 4 5 6 7 8
```

**样例输出**：
```
2 4 6 8 7 5 3 1
```

**解释**：偶数 2,4,6,8 排在前面且升序；奇数 7,5,3,1 排在后面且降序。

**完整 AC 代码**：

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1005;
int a[MAXN];

// 自定义排序规则
bool cmp(int a, int b) {
    // 判断奇偶性：a%2==0 为偶数，a%2!=0 为奇数
    bool aIsEven = (a % 2 == 0);
    bool bIsEven = (b % 2 == 0);
    
    // 规则 1：偶数排在奇数前面
    if (aIsEven != bIsEven) {
        return aIsEven;  // a 是偶数时返回 true（a 排前面）
    }
    
    // 规则 2：都是偶数，升序（小的在前）
    if (aIsEven) {
        return a < b;
    }
    
    // 规则 3：都是奇数，降序（大的在前）
    return a > b;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    sort(a, a + n, cmp);
    
    for (int i = 0; i < n; i++) {
        cout << a[i] << (i < n - 1 ? " " : "\n");
    }
    
    return 0;
}
```

**考点分析**：本题考察复杂自定义排序规则的编写。核心技巧是将排序规则分解为优先级层次：先判断最高优先级的条件（奇偶分离），再在同组内应用次要条件（偶数升序，奇数降序）。cmp 函数中的 `if-return` 结构是实现分层决策的标准模式。这类题目考察的是"将自然语言描述的排序需求转化为 cmp 函数"的能力。

---

## 🎯 本课小结
- `sort()` 是 C++ 竞赛中最常用的排序工具，时间复杂度 O(n log n)，使用格式为 `sort(起始, 结束, [比较函数])`，区间为左闭右开 `[begin, end)`。
- cmp 比较函数的核心规则：返回 `true` 表示第一个参数应排在第二个参数前面。多关键字排序时用 `if-return` 结构逐层判断——第一关键字不相等时直接返回，相等时继续判断第二关键字。
- `greater<int>()` 实现降序，`less<int>()` 实现升序（默认）。"取负数"存储技巧可以避免手写 cmp 实现降序效果。`stable_sort()` 保证相等元素的相对顺序，在需要稳定性的场景使用。
- 常见错误：cmp 中相等时返回 true（必须返回 false）、区间 `r+1` 写成 `r`、忘记包含 `<algorithm>` 头文件、cmp 逻辑写反。多写多练，cmp 函数的编写自然就能一气呵成。
