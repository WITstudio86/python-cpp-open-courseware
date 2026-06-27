# 第23课：STL入门——vector与string

## 🎯 考纲要求

- **vector动态数组**：定义、添加（`push_back`）、访问（`[]`）、大小（`size`）、清空（`clear`）
- **迭代器初步**：`begin()`、`end()` 的含义与基本用法
- **string类高级操作**：`find`、`substr`、`insert`、`erase`、`getline`
- **C++11特性**：`auto` 关键字、范围for循环（range-based for loop）

## 📖 知识精讲

### 一、为什么CSP-J选手必须掌握STL？

STL（Standard Template Library，标准模板库）是C++自带的"武器库"。在CSP-J竞赛中，时间就是分数。使用STL有三大好处：

1. **节省编码时间**：手动实现一个动态数组需要写上百行代码（分配内存、拷贝、释放），而STL的`vector`一行声明即可。省下的时间可以用来思考算法本身。
2. **减少Bug**：自己写的动态数组容易出现内存泄漏、越界访问、浅拷贝等问题。STL经过数十年打磨，极其可靠。竞赛中因为一个手写数据结构的Bug丢分，是最可惜的事情。
3. **代码可读性高**：当你用`v.push_back(x)`时，评委一眼就知道你在往数组末尾加元素；而手写版本可能需要三行指针操作。清晰的代码有助于调试，也更容易拿到高分。

**一句话总结**：STL让你的注意力从"怎么实现数据结构"解放到"怎么解决问题"。CSP-J考的是算法思维，不是造轮子能力。

---

### 二、vector详解——会自己长大的数组

#### 2.1 什么是vector？

`vector`是一个**动态数组**。普通数组（`int a[100]`）的大小在编译时就必须确定，而`vector`可以**在运行时自动扩容**。你今天不知道数据有多少个？没关系，往`vector`里塞就行。

使用`vector`需要引入头文件：

```cpp
#include <vector>
```

#### 2.2 声明与初始化

```cpp
vector<int> v;                  // 空vector，size为0
vector<int> v(10);              // 10个元素，默认初始化为0
vector<int> v(10, 5);           // 10个元素，每个都是5
vector<int> v = {1, 2, 3, 4};   // C++11列表初始化
vector<int> v2(v);              // 拷贝构造，和v一样
vector<int> v3 = v;             // 赋值拷贝
```

> **注意**：`vector<int> v(10)` 创建的是含有10个0的vector，而不是一个容量为10的空vector！如果只是想预留空间，用`v.reserve(10)`。

#### 2.3 常用操作一览

| 操作 | 说明 | 时间复杂度 |
|------|------|-----------|
| `v.push_back(x)` | 在末尾添加元素x | 均摊O(1) |
| `v.pop_back()` | 删除末尾元素 | O(1) |
| `v.size()` | 返回元素个数 | O(1) |
| `v.empty()` | 判断是否为空 | O(1) |
| `v.clear()` | 清空所有元素 | O(n) |
| `v.front()` | 返回第一个元素 | O(1) |
| `v.back()` | 返回最后一个元素 | O(1) |
| `v[i]` | 下标访问（无越界检查） | O(1) |
| `v.at(i)` | 下标访问（有越界检查） | O(1) |
| `v.resize(n)` | 调整大小为n | O(n) |
| `v.reserve(n)` | 预留容量为n | O(n) |

完整演示代码：

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v;
    
    // 添加元素
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    cout << "当前大小: " << v.size() << endl;  // 输出 3
    
    // 下标访问
    cout << "v[0] = " << v[0] << endl;        // 输出 10
    cout << "v[1] = " << v[1] << endl;        // 输出 20
    cout << "v[2] = " << v[2] << endl;        // 输出 30
    
    // front() 和 back()
    cout << "首元素: " << v.front() << endl;  // 输出 10
    cout << "尾元素: " << v.back() << endl;   // 输出 30
    
    // 删除末尾
    v.pop_back();
    cout << "pop_back后大小: " << v.size() << endl;  // 输出 2
    cout << "新尾元素: " << v.back() << endl;        // 输出 20
    
    // 判空
    cout << "是否为空: " << (v.empty() ? "是" : "否") << endl;
    
    // 清空
    v.clear();
    cout << "clear后大小: " << v.size() << endl;     // 输出 0
    cout << "是否为空: " << (v.empty() ? "是" : "否") << endl;
    
    return 0;
}
```

#### 2.4 vector的三种遍历方式

**方式一：传统下标循环**

```cpp
vector<int> v = {1, 2, 3, 4, 5};
for (int i = 0; i < v.size(); i++) {
    cout << v[i] << " ";
}
```

**方式二：迭代器**

```cpp
for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
    cout << *it << " ";
}
```

**方式三：范围for循环（C++11，最推荐）**

```cpp
for (int x : v) {
    cout << x << " ";
}
```

> **CSP-J建议**：优先使用下标循环（需要用到下标时）或范围for循环（只遍历值时）。迭代器的写法冗长，但在某些STL算法（如`sort`、`find`）中不可避免。

#### 2.5 二维vector——邻接表的基础

二维vector是CSP-J图论题中**邻接表**的常用实现方式：

```cpp
// 声明一个有n行的二维vector
int n = 5;
vector<vector<int>> matrix(n);  // n行，每行是一个空vector

// 或者直接初始化 n行m列, 全部为0
int m = 3;
vector<vector<int>> grid(n, vector<int>(m, 0));

// 邻接表用法：graph[u]存储u的所有邻居
vector<vector<int>> graph(n + 1);  // n个节点，1-indexed
graph[1].push_back(2);  // 节点1到节点2有一条边
graph[1].push_back(3);  // 节点1到节点3有一条边
graph[2].push_back(4);  // 节点2到节点4有一条边

// 遍历节点1的所有邻居
for (int neighbor : graph[1]) {
    cout << neighbor << " ";  // 输出 2 3
}
```

#### 2.6 性能注意事项

- `push_back`的均摊时间复杂度是O(1)。当容量不够时，vector会分配一块更大的内存（通常翻倍），然后把旧元素拷贝过去。虽然单次扩容是O(n)，但均摊到每次`push_back`是O(1)。
- 如果**预先知道**需要存储多少元素，用`reserve(n)`提前分配空间，可以避免多次扩容。
- `v[i]`比`v.at(i)`快但不安全。竞赛中为了保证速度，习惯使用`v[i]`，但你**必须自己保证下标不越界**。

---

### 三、迭代器初步——广义的"指针"

#### 3.1 什么是迭代器？

**迭代器**（iterator）是一种可以遍历容器中元素的对象。你可以把它理解成一个**封装的指针**：`*it` 取它指向的值，`++it` 让它指向下一个元素。

```cpp
vector<int> v = {10, 20, 30, 40, 50};

// begin() 指向第一个元素
vector<int>::iterator it = v.begin();
cout << *it << endl;  // 输出 10

// end() 指向最后一个元素之后的位置（不是最后一个元素！）
// 因此遍历条件是 it != v.end()，不是 it <= v.end()

for (auto it = v.begin(); it != v.end(); ++it) {
    cout << *it << " ";  // 输出 10 20 30 40 50
}
```

#### 3.2 迭代器的常用场景

```cpp
// 1. 插入元素到指定位置
v.insert(v.begin() + 2, 100);  // 在下标2处插入100

// 2. 删除指定位置的元素
v.erase(v.begin() + 1);  // 删除下标1处的元素

// 3. 配合algorithm算法
sort(v.begin(), v.end());                    // 排序
reverse(v.begin(), v.end());                 // 反转
auto it = find(v.begin(), v.end(), 30);      // 查找30
if (it != v.end()) {
    cout << "找到了! 位置: " << (it - v.begin()) << endl;
}
```

---

### 四、string高级操作——不仅仅是字符数组

`string` 在C++中远不止`cin >> s`。掌握以下操作，字符串处理题你就赢了一半。

使用string需要引入：

```cpp
#include <string>
```

#### 4.1 getline()——读入一整行（含空格）

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string line;
    cout << "请输入一行文字：";
    getline(cin, line);  // 读入一整行（包括空格），直到遇到换行符
    cout << "你输入的是：" << line << endl;
    return 0;
}
```

> **常见陷阱**：在 `cin >> n` 之后直接用 `getline`，会读到一个空行！因为 `cin >> n` 在缓冲区留下了换行符。解决方法：在 `getline` 前加 `cin.ignore()` 清除缓冲区。

```cpp
int n;
cin >> n;
cin.ignore();               // 清除换行符，必须加！
string line;
getline(cin, line);         // 现在能正确读到内容了
```

#### 4.2 find()——查找子串

```cpp
string s = "hello world, hello cpp";
size_t pos = s.find("hello");        // 返回第一个"hello"的位置，这里是0
size_t pos2 = s.find("hello", 5);    // 从下标5开始查找，返回13

if (s.find("java") == string::npos) {
    cout << "没找到 java" << endl;  // 这个会执行
}
```

- `find()` 找到返回位置（从0开始），找不到返回 `string::npos`（一个特殊常量，实际上是一个很大的无符号数）。
- **易错**：`string::npos` 是 `size_t` 类型（无符号）。判断没找到应该写 `s.find(x) == string::npos`，**不要**写 `s.find(x) < 0`，那永远是`false`。

#### 4.3 substr()——提取子串

```cpp
string s = "Hello World";
string sub1 = s.substr(0, 5);   // "Hello"（从0开始，取5个字符）
string sub2 = s.substr(6);      // "World"（从6开始，取到末尾）
string sub3 = s.substr(6, 3);   // "Wor"
```

#### 4.4 insert()与erase()——修改字符串

```cpp
string s = "Hello World";

// insert(pos, str)：在位置pos处插入str
s.insert(5, " beautiful");
cout << s << endl;  // "Hello beautiful World"

// erase(pos, len)：从pos开始删除len个字符
string t = "abcdef";
t.erase(2, 3);       // 删除位置2开始的3个字符
cout << t << endl;   // "abf"

// erase(iterator) 用法
t.erase(t.begin() + 1);  // 删除下标1处的字符
```

#### 4.5 length() / size() 和字符串比较

```cpp
string s = "CSP-J";
cout << s.length() << endl;  // 输出 5（length和size等价）
cout << s.size() << endl;     // 同样输出 5

// 字符串可以直接用 ==, <, > 比较（按字典序）
string a = "abc", b = "abd";
if (a < b) cout << "abc < abd" << endl;       // 会执行
if ("apple" < "banana") cout << "apple先" << endl;  // 会执行
```

#### 4.6 字符串与数字互转

```cpp
// 数字转字符串
string s1 = to_string(123);     // "123"
string s2 = to_string(3.14);    // "3.140000"

// 字符串转数字
int num = stoi("456");          // 456
long long big = stoll("1234567890123");  // 1234567890123
double d = stod("3.14159");     // 3.14159
```

> **注意**：`to_string`、`stoi`、`stoll` 等函数是C++11引入的。CSP-J支持C++14，可以放心使用。

---

### 五、C++11特性——让代码更简洁

#### 5.1 auto关键字——让编译器帮你推类型

`auto` 不是"弱类型"（如JavaScript的var），而是**编译时类型推导**。变量在编译时就有了确定的类型。

```cpp
auto x = 10;                       // int
auto y = 3.14;                     // double
auto s = "hello";                  // const char*
vector<int> v = {1, 2, 3};
auto it = v.begin();               // vector<int>::iterator（太省事了！）
auto first = v[0];                 // int
```

**使用原则**：变量名能表达语义时用auto；类型复杂（如迭代器）时用auto；简单类型（如int、double）可以不写auto，但写了也没错。

#### 5.2 范围for循环——遍历容器的银弹

```cpp
vector<int> v = {1, 2, 3, 4, 5};

// 只读遍历
for (auto x : v) {
    cout << x << " ";  // 1 2 3 4 5
}

// 需要修改元素时，用引用
for (auto& x : v) {
    x *= 2;  // 每个元素翻倍
}
// 现在 v = {2, 4, 6, 8, 10}

// 只读遍历大对象时，用const引用，避免拷贝
for (const auto& x : v) {
    cout << x << " ";
}

// string也可以用范围for
string s = "CSP-J";
for (auto ch : s) {
    cout << ch << " ";  // C S P - J
}
```

**三个关键写法**，记牢：

| 写法 | 含义 | 何时使用 |
|------|------|---------|
| `for (auto x : v)` | 拷贝每个元素 | 值类型小且不需要修改 |
| `for (auto& x : v)` | 引用每个元素 | 需要修改原容器中的值 |
| `for (const auto& x : v)` | 只读引用 | 值类型大（如string），且不需要修改 |

---

### 六、CSP-J常见模式与技巧

#### 模式1：读取未知数量数据，去重排序

```cpp
int n;
cin >> n;
vector<int> a(n);
for (int i = 0; i < n; i++) {
    cin >> a[i];
}
// 去重排序
sort(a.begin(), a.end());
a.erase(unique(a.begin(), a.end()), a.end());
// 现在 a 中是无重复的升序序列
```

#### 模式2：用vector存图的邻接表

```cpp
int n, m;  // n个节点，m条边
cin >> n >> m;
vector<vector<int>> g(n + 1);  // 1-indexed
for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);  // 无向图
}
```

#### 模式3：解析逗号分隔的字符串

```cpp
string line;
getline(cin, line);
vector<string> fields;
string current;
for (char ch : line) {
    if (ch == ',') {
        fields.push_back(current);
        current.clear();
    } else {
        current += ch;
    }
}
if (!current.empty()) {
    fields.push_back(current);
}
// 现在 fields 里是分割后的各个字段
```

---

## 💻 代码模板

### 模板1：vector综合操作

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // 创建和初始化
    vector<int> v;
    
    // 读取n个数并添加
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        v.push_back(x);
    }
    
    // 排序
    sort(v.begin(), v.end());
    
    // 去重
    v.erase(unique(v.begin(), v.end()), v.end());
    
    // 输出
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " \n"[i == v.size() - 1];
    }
    
    return 0;
}
```

### 模板2：字符串解析

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    string line;
    getline(cin, line);
    
    // find + substr 方式分割
    vector<string> parts;
    size_t pos = 0;
    string delimiter = ",";
    while ((pos = line.find(delimiter)) != string::npos) {
        parts.push_back(line.substr(0, pos));
        line.erase(0, pos + delimiter.length());
    }
    parts.push_back(line);  // 最后一段
    
    // 输出结果
    for (const auto& part : parts) {
        cout << part << endl;
    }
    
    return 0;
}
```

### 模板3：auto + 范围for模式

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    vector<string> names = {"张三", "李四", "王五"};
    
    // 只读遍历
    cout << "学生名单：";
    for (const auto& name : names) {
        cout << name << " ";
    }
    cout << endl;
    
    // 修改元素
    vector<int> scores = {85, 92, 78};
    for (auto& score : scores) {
        score += 5;  // 每人加5分
    }
    
    // 输出修改后的成绩
    for (const auto& score : scores) {
        cout << score << " ";
    }
    cout << endl;
    
    return 0;
}
```

---

## ⚠️ 易错点

### 易错点1：vector越界访问

```cpp
vector<int> v(5);  // 有5个元素：v[0]到v[4]
v[5] = 10;         // ❌ 错误！越界访问，但编译器不报错
                   // 运行时可能崩溃，也可能悄悄破坏其他数据
```

**正确做法**：始终保证下标 `i >= 0 && i < v.size()`。在循环中用 `for (int i = 0; i < v.size(); i++)`，注意是 `<` 不是 `<=`。

### 易错点2：忘记 `#include <vector>` 或 `#include <string>`

```cpp
// ❌ 编译器报错：'vector' was not declared in this scope
vector<int> v;

// ✅ 正确
#include <vector>
#include <string>
using namespace std;
```

CSP-J中每一个使用的STL容器都要单独 `#include`。你也可以用万能头 `#include <bits/stdc++.h>`（CSP-J允许，但不是标准C++）。

### 易错点3：混淆 `size()` 和 `capacity()`

```cpp
vector<int> v;
v.reserve(100);
cout << v.size();      // 输出 0！（元素个数为0）
cout << v.capacity();  // 输出 >= 100（预留的空间大小）
```

- `size()` 返回的是**实际存储**的元素数量。
- `capacity()` 返回的是**已分配内存**能容纳的元素数量。
- `reserve()` 只改变capacity，不改变size。访问 `v[0]` 仍然会越界！
- `resize()` 会同时改变size和内容（新增位置填默认值）。

### 易错点4：`string::npos` 比较错误

```cpp
string s = "abc";

// ❌ 错误写法
if (s.find("z") < 0) { ... }  // 永远为false！find返回的是无符号数

// ❌ 错误写法
if (s.find("z") == -1) { ... }  // 也可能不对，因为类型不匹配

// ✅ 正确写法
if (s.find("z") == string::npos) {
    cout << "没找到" << endl;
}

// ✅ 另一种正确写法：存为int（但有溢出风险，仅小字符串安全）
int pos = s.find("z");
if (pos == -1) { cout << "没找到" << endl; }  // 此时int的-1和size_t的npos比较会转换
```

> **建议**：直接用 `if (s.find(x) == string::npos)`，这是最安全的写法。

### 易错点5：`cin >>` 和 `getline()` 混用

```cpp
int n;
cin >> n;          // 输入 "5\n"
string s;
getline(cin, s);   // s得到的是空字符串""，不是下一行！

// 解决方法：
int n;
cin >> n;
cin.ignore();      // 清除缓冲区中的换行符
string s;
getline(cin, s);   // 现在s得到的是下一行内容
```

---

## 📝 真题精练

### 题目1：去重排序

**【题目描述】**

给定n个整数，其中可能有重复的数字。请将这些数字从小到大排序，并输出去重后的结果。

**【输入格式】**

- 第一行：一个整数 n（1 ≤ n ≤ 10^5），表示数字的个数
- 第二行：n个整数，每个整数的绝对值不超过10^9

**【输出格式】**

- 第一行：一个整数 m，表示去重后的数字个数
- 第二行：m个整数，从小到大排列，以空格分隔

**【样例输入】**

```
8
3 1 4 1 5 9 2 6
```

**【样例输出】**

```
7
1 2 3 4 5 6 9
```

**【AC代码】**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    // 排序
    sort(a.begin(), a.end());
    
    // 去重：unique返回去重后的逻辑末尾迭代器
    auto last = unique(a.begin(), a.end());
    a.erase(last, a.end());
    
    // 输出
    cout << a.size() << endl;
    for (int i = 0; i < a.size(); i++) {
        if (i > 0) cout << " ";
        cout << a[i];
    }
    cout << endl;
    
    return 0;
}
```

**【解题思路】**

这是一道经典的vector+algorithm练手题。先读入n个数到vector中，用`sort()`排序（O(n log n)），然后用`unique()`将相邻重复元素移到容器末尾，最后用`erase()`删除它们。需要注意`unique`并不会改变容器大小，只是把不重复的元素前移，返回一个新的"逻辑末尾"迭代器。

---

### 题目2：CSV字段解析

**【题目描述】**

逗号分隔值（CSV）是一种常见的数据格式。给定一行CSV数据（不含引号包裹的逗号），请将每个字段提取出来，并输出。

**【输入格式】**

- 一行字符串，长度不超过1000，由字母、数字和逗号组成。数据保证不包含连续的逗号（即没有空字段）。

**【输出格式】**

- 每个字段一行，按照原顺序输出

**【样例输入】**

```
Zhang,San,15,Math,95
```

**【样例输出】**

```
Zhang
San
15
Math
95
```

**【AC代码】**

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    string line;
    getline(cin, line);
    
    vector<string> fields;
    size_t pos = 0;
    while ((pos = line.find(',')) != string::npos) {
        fields.push_back(line.substr(0, pos));
        line.erase(0, pos + 1);
    }
    fields.push_back(line);  // 最后一个字段
    
    for (const auto& field : fields) {
        cout << field << endl;
    }
    
    return 0;
}
```

**【解题思路】**

核心是用`find(',')`循环定位每个逗号的位置，然后用`substr(0, pos)`取出当前字段，用`erase(0, pos + 1)`把已处理部分删掉。循环结束后剩下的就是最后一个字段。这个方法清晰易懂，也是CSP-J字符串解析的常见模式。

**另一种写法**（不用erase，维护一个起始位置）：

```cpp
size_t start = 0, end;
while ((end = line.find(',', start)) != string::npos) {
    fields.push_back(line.substr(start, end - start));
    start = end + 1;
}
fields.push_back(line.substr(start));
```

---

## 🎯 本课小结

| 知识点 | 关键内容 | 一句话记忆 |
|--------|---------|-----------|
| vector | 动态数组，`push_back`添加，`v[i]`访问，`sort`排序 | 会自己变长的数组 |
| 迭代器 | `begin()`指向首元素，`end()`指向尾后 | 广义指针，`*it`取值 |
| string | `getline`读一行，`find`查找，`substr`截取，`to_string`转换 | CSP-J字符串处理三件套 |
| auto | 编译时类型推导 | 让编译器猜类型，你写算法 |
| 范围for | `for (auto x : v)` | 告别`for(int i=0;i<n;i++)` |

**竞赛建议**：
- vector是CSP-J中最常用的容器，几乎所有你需要"不确定个数"的数组场景都用它。
- 学string高级操作，一劳永逸解决字符串解析题。
- `auto`和范围for不是必需的，但用了代码更短、更少出错。
- 考前务必把本课的易错点过一遍——越界访问和getline混用是最常犯的错误。
