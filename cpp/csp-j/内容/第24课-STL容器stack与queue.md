# 第24课：STL容器——stack与queue

## 🎯 考纲要求

- **stack栈**：LIFO（后进先出），操作 `push` / `pop` / `top` / `empty` / `size`
- **queue队列**：FIFO（先进先出），操作 `push` / `pop` / `front` / `back` / `empty` / `size`
- **应用场景**：括号匹配、排队模拟、广度优先搜索（BFS）预备

## 📖 知识精讲

### 一、为什么需要stack和queue？

数组和vector解决的是"存数据"的问题，但竞赛中我们经常遇到需要**按特定顺序处理数据**的场景：

- 括号嵌套匹配：遇到左括号先存着，遇到右括号时应该匹配**最后一个**左括号（后进先出）→ **栈**
- 排队叫号：先到的人先服务（先进先出）→ **队列**

如果你用数组手写这些逻辑，不仅代码多，还容易错。STL提供了现成的`stack`和`queue`，几行代码就能搞定。

---

### 二、Stack（栈）——后进先出 (LIFO)

#### 2.1 现实中的栈

- **一摞盘子**：最后放上去的盘子，第一个被拿走。
- **浏览器的后退按钮**：最后访问的页面，后退时最先回去。
- **撤销操作（Ctrl+Z）**：最后做的操作，撤销时最先被还原。

程序员常说的"函数调用栈"（call stack）也是这个原理：最后一个调用的函数最先返回。

#### 2.2 头文件与声明

```cpp
#include <stack>
using namespace std;

stack<int> s;                    // 存储int的栈
stack<char> charStack;           // 存储char的栈
stack<string> strStack;          // 存储string的栈
```

#### 2.3 核心操作

| 操作 | 说明 | 时间复杂度 |
|------|------|-----------|
| `s.push(x)` | 将元素x压入栈顶 | O(1) |
| `s.pop()` | 弹出栈顶元素（不返回！） | O(1) |
| `s.top()` | 返回栈顶元素（不弹出） | O(1) |
| `s.empty()` | 判断栈是否为空 | O(1) |
| `s.size()` | 返回栈中元素个数 | O(1) |

> **最重要的坑**：`pop()` **不返回值**！要获取栈顶元素必须先`top()`，再`pop()`。这和某些其他语言（如Python的`list.pop()`）完全不一样。

#### 2.4 完整操作演示

```cpp
#include <iostream>
#include <stack>
using namespace std;

int main() {
    stack<int> s;

    // 压入三个元素
    s.push(10);
    s.push(20);
    s.push(30);
    cout << "栈顶: " << s.top() << endl;   // 输出 30
    cout << "大小: " << s.size() << endl;  // 输出 3

    // 依次弹出
    while (!s.empty()) {
        cout << "弹出: " << s.top() << endl;  // 先取值
        s.pop();                               // 再弹出
    }
    // 输出顺序: 30, 20, 10（后进先出）

    cout << "栈是否为空: " << (s.empty() ? "是" : "否") << endl;  // 是
    return 0;
}
```

**执行过程追踪：**

| 步骤 | 操作 | 栈内容（栈顶→栈底） | top()返回值 | size() |
|------|------|---------------------|-------------|--------|
| 0 | 创建 | [] | - | 0 |
| 1 | push(10) | [10] | 10 | 1 |
| 2 | push(20) | [20, 10] | 20 | 2 |
| 3 | push(30) | [30, 20, 10] | 30 | 3 |
| 4 | pop() | [20, 10] | 20 | 2 |
| 5 | pop() | [10] | 10 | 1 |
| 6 | pop() | [] | - | 0 |

#### 2.5 底层实现

STL中`stack`默认基于`deque`（双端队列）实现。你也可以指定底层容器：

```cpp
stack<int, vector<int>> s;   // 基于vector的栈
stack<int, list<int>> s;     // 基于list的栈
```

竞赛中不需要关心底层，用默认的`stack<int>`就行。

---

### 三、Queue（队列）——先进先出 (FIFO)

#### 3.1 现实中的队列

- **排队买票**：排在最前面的人最先买到票。
- **打印队列**：先提交的文档先被打印。
- **消息队列**：先收到的消息先被处理。

队列是BFS（广度优先搜索）的**核心数据结构**。任何"一层一层往外扩展"的算法都需要队列。今天先学队列的操作，为后续的图论和搜索课程打好基础。

#### 3.2 头文件与声明

```cpp
#include <queue>
using namespace std;

queue<int> q;                    // 存储int的队列
queue<string> nameQueue;         // 存储string的队列
```

#### 3.3 核心操作

| 操作 | 说明 | 时间复杂度 |
|------|------|-----------|
| `q.push(x)` | 将元素x添加到队尾 | O(1) |
| `q.pop()` | 移除队首元素（不返回！） | O(1) |
| `q.front()` | 返回队首元素（不移除） | O(1) |
| `q.back()` | 返回队尾元素（不移除） | O(1) |
| `q.empty()` | 判断队列是否为空 | O(1) |
| `q.size()` | 返回队列中元素个数 | O(1) |

> **注意**：和stack一样，`pop()`也不返回值！使用 `front()` 取队首，然后 `pop()` 移除。

#### 3.4 完整操作演示

```cpp
#include <iostream>
#include <queue>
using namespace std;

int main() {
    queue<int> q;

    // 依次入队
    q.push(10);
    q.push(20);
    q.push(30);
    cout << "队首: " << q.front() << endl;  // 输出 10
    cout << "队尾: " << q.back() << endl;   // 输出 30
    cout << "大小: " << q.size() << endl;   // 输出 3

    // 依次出队
    while (!q.empty()) {
        cout << "出队: " << q.front() << endl;  // 先看队首
        q.pop();                                  // 再出队
    }
    // 输出顺序: 10, 20, 30（先进先出）

    cout << "队列是否为空: " << (q.empty() ? "是" : "否") << endl;
    return 0;
}
```

**执行过程追踪：**

| 步骤 | 操作 | 队列内容（队首→队尾） | front() | back() | size() |
|------|------|-----------------------|---------|--------|--------|
| 0 | 创建 | [] | - | - | 0 |
| 1 | push(10) | [10] | 10 | 10 | 1 |
| 2 | push(20) | [10, 20] | 10 | 20 | 2 |
| 3 | push(30) | [10, 20, 30] | 10 | 30 | 3 |
| 4 | pop() | [20, 30] | 20 | 30 | 2 |
| 5 | pop() | [30] | 30 | 30 | 1 |
| 6 | pop() | [] | - | - | 0 |

---

### 四、应用场景1：括号匹配（Stack经典题）

**问题描述**：给定一个包含 `(` `)` `[` `]` `{` `}` 的字符串，判断括号是否正确匹配。

**算法步骤**：
1. 遍历字符串中的每个字符
2. 遇到**左括号**（`(`、`[`、`{`）→ 压入栈中
3. 遇到**右括号** → 检查栈是否为空：
   - 栈空 → 匹配失败（右括号多了）
   - 栈顶不是对应的左括号 → 匹配失败（类型不匹配）
   - 栈顶是对应的左括号 → 弹出栈顶，继续遍历
4. 遍历结束后：
   - 栈空 → 完全匹配！
   - 栈非空 → 匹配失败（左括号多了）

```cpp
#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool isValid(string s) {
    stack<char> st;
    for (char ch : s) {
        // 左括号：压栈
        if (ch == '(' || ch == '[' || ch == '{') {
            st.push(ch);
        }
        // 右括号：检查匹配
        else {
            if (st.empty()) return false;  // 没有匹配的左括号

            char top = st.top();
            if ((ch == ')' && top == '(') ||
                (ch == ']' && top == '[') ||
                (ch == '}' && top == '{')) {
                st.pop();  // 匹配成功，弹出
            } else {
                return false;  // 类型不匹配
            }
        }
    }
    // 最后栈应为空
    return st.empty();
}

int main() {
    cout << boolalpha;  // 让bool输出true/false而不是1/0
    cout << "()        -> " << isValid("()") << endl;        // true
    cout << "()[]{}    -> " << isValid("()[]{}") << endl;    // true
    cout << "(]        -> " << isValid("(]") << endl;        // false
    cout << "([)]      -> " << isValid("([)]") << endl;      // false
    cout << "{[]}      -> " << isValid("{[]}") << endl;      // true
    cout << "(((())))  -> " << isValid("(((())))") << endl;  // true
    cout << "(()       -> " << isValid("(()") << endl;       // false
    return 0;
}
```

---

### 五、应用场景2：约瑟夫问题（Queue经典题）

**问题描述**：n个人围成一圈，从第1个人开始报数，数到m的人出列，下一个人重新从1开始报数。求出列顺序。

这是queue的经典应用题——所有元素先入队，然后循环"出队-判定-入队或淘汰"。

```cpp
#include <iostream>
#include <queue>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;  // n个人，数到m出列

    queue<int> q;
    for (int i = 1; i <= n; i++) {
        q.push(i);  // 所有人入队
    }

    cout << "出列顺序: ";
    while (!q.empty()) {
        // 前 m-1 个人：从队首移到队尾
        for (int i = 1; i < m; i++) {
            q.push(q.front());
            q.pop();
        }
        // 第 m 个人：出列
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;

    return 0;
}
```

**输入样例**：
```
5 3
```
**输出样例**：
```
出列顺序: 3 1 5 2 4
```

**算法解释**（n=5, m=3）：
- 初始队列：[1, 2, 3, 4, 5]
- 第1轮：1→队尾, 2→队尾, 3出列。队列：[4, 5, 1, 2]。出列：3
- 第2轮：4→队尾, 5→队尾, 1出列。队列：[2, 4, 5]。出列：3, 1
- 第3轮：2→队尾, 4→队尾, 5出列。队列：[2, 4]。出列：3, 1, 5
- 第4轮：2→队尾, 4→队尾, 2出列。队列：[4]。出列：3, 1, 5, 2
- 第5轮：队列只有一个元素，4前移到队尾两次（实际不变），4出列。

---

### 六、应用场景3：队列模拟服务窗口

**问题描述**：一个服务窗口，有n个客户依次到达。每个客户有到达时间和所需服务时间。同一时刻只能服务一个客户。求每个客户的等待时间。

```cpp
#include <iostream>
#include <queue>
using namespace std;

struct Customer {
    int id;          // 客户编号
    int arriveTime;  // 到达时间
    int serveTime;   // 所需服务时间
    int waitTime;    // 等待时间（结果）
};

int main() {
    int n;
    cin >> n;
    queue<Customer> q;

    for (int i = 1; i <= n; i++) {
        Customer c;
        c.id = i;
        cin >> c.arriveTime >> c.serveTime;
        c.waitTime = 0;
        q.push(c);
    }

    int currentTime = 0;  // 当前时间
    int totalWait = 0;

    while (!q.empty()) {
        Customer c = q.front();
        q.pop();

        // 如果客户还没到（理论上数据保证到了才被处理）
        if (currentTime < c.arriveTime) {
            currentTime = c.arriveTime;  // 窗口空闲，跳到客户到达时间
        }

        c.waitTime = currentTime - c.arriveTime;
        totalWait += c.waitTime;
        currentTime += c.serveTime;  // 服务这个客户

        cout << "客户" << c.id << ": 到达时间=" << c.arriveTime
             << " 等待=" << c.waitTime
             << " 完成时间=" << currentTime << endl;
    }

    cout << "总等待时间: " << totalWait << endl;
    if (n > 0) {
        cout << "平均等待时间: " << (double)totalWait / n << endl;
    }

    return 0;
}
```

---

### 七、BFS预备知识——队列的核心价值

广度优先搜索（BFS）是后续图论和搜索课程的重点。先理解队列在其中扮演的角色：

**BFS的核心思想**：从起点开始，先访问距离为1的所有节点，再访问距离为2的所有节点，以此类推。

这正是队列的行为模式——先进先出保证了**按层处理**：

```
BFS伪代码：
queue<int> q;
q.push(start);          // 起点入队
visited[start] = true;

while (!q.empty()) {
    int cur = q.front(); q.pop();  // 取出队首（当前层的节点）
    for (每个相邻节点 neighbor) {
        if (!visited[neighbor]) {
            visited[neighbor] = true;
            q.push(neighbor);      // 下一层节点入队
        }
    }
}
```

> **直观理解**：队列就像是一个"待处理列表"——谁先来谁先被处理。BFS中所有同一层的节点几乎同时入队，又按顺序被取出处理，自然就实现了逐层扩展。

---

### 八、priority_queue 简要介绍

C++还提供了优先队列（`priority_queue`），默认是**大顶堆**（最大值先出队）：

```cpp
#include <queue>

priority_queue<int> pq;          // 大顶堆，最大值在队首
pq.push(3); pq.push(1); pq.push(5);
cout << pq.top();                // 输出 5（最大值）
pq.pop();
cout << pq.top();                // 输出 3

// 小顶堆（最小值在队首）
priority_queue<int, vector<int>, greater<int>> minHeap;
```

CSP-J中如果遇到"每次取最大值/最小值"的场景（如哈夫曼树），直接上`priority_queue`。

---

### 九、Stack vs Queue 选择指南

| 场景特征 | 应该用... | 原因 |
|---------|----------|------|
| 最后进来的先处理 | **Stack** | LIFO |
| 先进来的先处理 | **Queue** | FIFO |
| 括号匹配、表达式求值 | **Stack** | 嵌套结构→后进先出 |
| 排队模拟、轮流处理 | **Queue** | 公平顺序→先进先出 |
| 函数递归的迭代版 | **Stack** | 模拟调用栈 |
| 逐层扩展（BFS） | **Queue** | 按层次顺序 |
| 每次取最大/最小值 | **priority_queue** | 堆结构 |

**一句话总结**：需要"往回找"用栈，需要"按顺序走"用队列。

---

## 💻 代码模板

### 模板1：括号匹配（Stack）

```cpp
#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool isValid(string s) {
    stack<char> st;
    for (char ch : s) {
        if (ch == '(' || ch == '[' || ch == '{') {
            st.push(ch);
        } else {
            if (st.empty()) return false;
            char top = st.top();
            if ((ch == ')' && top != '(') ||
                (ch == ']' && top != '[') ||
                (ch == '}' && top != '{')) {
                return false;
            }
            st.pop();
        }
    }
    return st.empty();
}

int main() {
    string s;
    cin >> s;
    cout << (isValid(s) ? "Yes" : "No") << endl;
    return 0;
}
```

### 模板2：约瑟夫问题（Queue）

```cpp
#include <iostream>
#include <queue>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    queue<int> q;
    for (int i = 1; i <= n; i++) q.push(i);

    while (!q.empty()) {
        for (int i = 1; i < m; i++) {
            q.push(q.front());
            q.pop();
        }
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
    return 0;
}
```

### 模板3：十进制转二进制（Stack）

```cpp
#include <iostream>
#include <stack>
using namespace std;

int main() {
    int n;
    cin >> n;

    if (n == 0) {
        cout << 0 << endl;
        return 0;
    }

    stack<int> s;
    while (n > 0) {
        s.push(n % 2);  // 余数压栈
        n /= 2;
    }

    // 从栈顶依次输出（正好是倒序→正序）
    while (!s.empty()) {
        cout << s.top();
        s.pop();
    }
    cout << endl;
    return 0;
}
```

---

## ⚠️ 易错点

### 易错点1：`pop()` 不返回元素值

这是新手最常见的错误！

```cpp
// ❌ 错误写法
stack<int> s;
s.push(10);
int x = s.pop();   // 编译错误！pop()返回void

// ❌ 另一种错误：直接pop没取值
s.pop();           // 元素被丢弃了，你永远不知道它是多少

// ✅ 正确写法
int x = s.top();   // 先取栈顶值
s.pop();           // 再弹出

// queue同理
int y = q.front(); // 先取队首值
q.pop();           // 再弹出
```

### 易错点2：对空容器执行 `pop()` 或 `top()` / `front()`

```cpp
stack<int> s;
s.top();  // ❌ 未定义行为！栈为空
s.pop();  // ❌ 未定义行为！栈为空

// ✅ 正确写法：先检查
if (!s.empty()) {
    int x = s.top();
    s.pop();
}
```

**竞赛铁律**：每次调用 `top()` / `front()` / `pop()` 前，一定要用 `empty()` 检查。

### 易错点3：忘记对应的头文件

```cpp
// ❌ 缺少头文件
stack<int> s;   // 编译错误！

// ✅ 每个容器都要单独include
#include <stack>   // stack
#include <queue>   // queue 和 priority_queue
```

`queue` 和 `priority_queue` 在同一个头文件 `<queue>` 中，但 `stack` 在 `<stack>` 中。当然竞赛中可以用万能头 `#include <bits/stdc++.h>`。

### 易错点4：队列中分不清 `front()` 和 `back()`

```cpp
queue<int> q;
q.push(1);  // 队尾加入1
q.push(2);  // 队尾加入2
q.push(3);  // 队尾加入3

cout << q.front();  // 输出 1（队首，先进来的）
cout << q.back();   // 输出 3（队尾，后进来的）

q.pop();            // 移除队首（1被移除）
cout << q.front();  // 输出 2（新的队首）
```

- `front()` = 队首 = 最先入队的 = 下次pop会移除的
- `back()` = 队尾 = 最后入队的 = 下次push会加在它后面的

### 易错点5：stack/queue不支持遍历

```cpp
stack<int> s;
// ❌ 没有 s[i] 这种下标访问
// ❌ 没有 s.begin() / s.end() 迭代器
// ❌ 不能用范围for循环

// Stack和Queue只允许访问一端（栈顶或队首+队尾）
// 如果需要遍历，考虑用vector
```

---

## 📝 真题精练

### 题目1：有效的括号

**【题目描述】**

给定一个只包含字符 `(` `)` `[` `]` `{` `}` 的字符串 s，判断字符串中的括号是否有效。

有效字符串需满足：
1. 左括号必须用相同类型的右括号闭合
2. 左括号必须以正确的顺序闭合
3. 每个右括号都有一个对应的相同类型的左括号

**【输入格式】**

- 一行一个字符串 s，长度不超过 10^4

**【输出格式】**

- 如果括号有效，输出 `YES`，否则输出 `NO`

**【样例输入】**

```
()[]{}
```

**【样例输出】**

```
YES
```

**【样例输入2】**

```
([)]
```

**【样例输出2】**

```
NO
```

**【AC代码】**

```cpp
#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    string s;
    cin >> s;

    stack<char> st;
    bool ok = true;

    for (char ch : s) {
        // 左括号：压栈
        if (ch == '(' || ch == '[' || ch == '{') {
            st.push(ch);
        }
        // 右括号：匹配栈顶
        else if (ch == ')' || ch == ']' || ch == '}') {
            if (st.empty()) {  // 没有匹配的左括号
                ok = false;
                break;
            }
            char top = st.top();
            if ((ch == ')' && top == '(') ||
                (ch == ']' && top == '[') ||
                (ch == '}' && top == '{')) {
                st.pop();
            } else {
                ok = false;
                break;
            }
        }
    }

    // 检查栈是否为空（有没有多余的左括号）
    if (!st.empty()) ok = false;

    cout << (ok ? "YES" : "NO") << endl;
    return 0;
}
```

**【解题思路】**

典型的栈应用题。遍历每个字符：
- 左括号一律入栈
- 右括号与栈顶匹配：匹配则弹栈，不匹配则直接判定无效
- 最后检查栈是否为空——栈空表示所有括号都完美匹配

时间复杂度 O(n)，空间复杂度 O(n)。

---

### 题目2：纸牌游戏（双队列对战）

**【题目描述】**

有两个玩家 A 和 B，每人手上有 n 张牌，面值为 1 到 13。游戏规则如下：

- 每轮双方各出一张牌（从牌堆顶部取），牌面值大的玩家赢得这一轮，将两张牌都收入自己的牌堆**底部**（先放自己的牌，再放对方的牌）。
- 如果牌面值相同，双方都收回自己的牌（放回自己牌堆底部）。
- 当某一方没有牌时，游戏结束，有牌的一方获胜。
- 如果进行超过 1000 轮仍未结束，判为平局。

**【输入格式】**

- 第一行：一个整数 n（1 ≤ n ≤ 26），表示初始每人手中的牌数
- 第二行：n个整数（空格分隔），表示 A 的初始牌（从顶到底）
- 第三行：n个整数（空格分隔），表示 B 的初始牌（从顶到底）

**【输出格式】**

- 若A胜，输出 `A WIN`；若B胜，输出 `B WIN`；若平局，输出 `DRAW`
- 第二行输出游戏进行的轮数

**【样例输入】**

```
5
3 5 1 8 2
4 6 9 7 10
```

**【样例输出】**

```
B WIN
9
```

**【AC代码】**

```cpp
#include <iostream>
#include <queue>
using namespace std;

int main() {
    int n;
    cin >> n;

    queue<int> a, b;

    // 读入A的牌
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a.push(x);
    }

    // 读入B的牌
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        b.push(x);
    }

    int rounds = 0;
    const int MAX_ROUNDS = 1000;

    while (!a.empty() && !b.empty() && rounds < MAX_ROUNDS) {
        rounds++;

        int cardA = a.front(); a.pop();
        int cardB = b.front(); b.pop();

        if (cardA > cardB) {
            // A赢，将两张牌收入A的牌堆底部
            a.push(cardA);
            a.push(cardB);
        } else if (cardB > cardA) {
            // B赢
            b.push(cardB);
            b.push(cardA);
        } else {
            // 平局，各收回自己的牌
            a.push(cardA);
            b.push(cardB);
        }
    }

    if (rounds >= MAX_ROUNDS) {
        cout << "DRAW" << endl;
    } else if (b.empty()) {
        cout << "A WIN" << endl;
    } else {
        cout << "B WIN" << endl;
    }

    cout << rounds << endl;

    return 0;
}
```

**【解题思路】**

用两个队列模拟两个玩家的牌堆。每轮：
1. 双方从各自队列 `front()` 取出牌，然后 `pop()`
2. 比较牌面值，决定牌的去向——赢家将两张牌 `push()` 到自己的队列
3. 平局时各收回自己的牌

注意设置轮数上限（如1000轮），防止无限循环。

---

## 🎯 本课小结

| 知识点 | 关键内容 | 一句话记忆 |
|--------|---------|-----------|
| **Stack** | push进入, top查看, pop移除 | 后进先出，像一摞盘子 |
| **Queue** | push进入, front看队首, back看队尾, pop移除 | 先进先出，像排队买票 |
| **括号匹配** | 左括号进栈，右括号匹配栈顶弹出 | 栈的经典应用 |
| **约瑟夫问题** | 前m-1人移到队尾，第m人出队 | 队列循环模型 |
| **pop不返回值** | 先top/front取值，再pop移除 | 最易错的STL设计 |
| **priority_queue** | 默认大顶堆，top返回最大值 | 需要"优先"时用它 |

**竞赛建议**：
- stack和queue都是"限制性"容器——只能操作一端。这其实是个优点：限制了使用方式，也就限制了出错的可能。
- 遇到"嵌套/配对/回溯"问题 → 想stack
- 遇到"排队/轮流/逐层"问题 → 想queue
- pop()之前一定要检查empty()，这是一个5秒钟的习惯，但能省下半小时的调试时间
