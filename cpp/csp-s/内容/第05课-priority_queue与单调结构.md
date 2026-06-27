# 第05课：priority_queue 与单调结构

## 🎯 考纲要求
- 掌握堆（Heap）的数据结构原理与 priority_queue 的使用
- 理解完全二叉树的数组存储方式，掌握 shiftUp / shiftDown 操作的实现
- 能够使用自定义比较函数实现不同优先级的堆
- 掌握单调栈（Monotonic Stack）的核心思想与经典应用（下一个更大元素、最大矩形面积）
- 掌握单调队列（Monotonic Queue）的核心思想与经典应用（滑动窗口最大值、DP 优化）
- 能够分析相关算法的时间复杂度，理解建堆 O(n) 的证明

## 📖 知识精讲

### 一、堆（Heap）的完全二叉树性质与数组存储

#### 1.1 什么是堆

堆是一种特殊的完全二叉树，满足**堆性质**：
- **最小堆（Min-Heap）**：每个节点的值都不大于其子节点的值，即 `heap[parent] <= heap[child]`
- **最大堆（Max-Heap）**：每个节点的值都不小于其子节点的值，即 `heap[parent] >= heap[child]`

堆通常用于实现**优先队列（Priority Queue）**——一种每次取出优先级最高（最大或最小）元素的数据结构。

#### 1.2 完全二叉树的数组存储

由于堆是一棵完全二叉树，我们可以用数组来紧凑存储，无需指针。

**索引约定**（**1-based**，即从索引 1 开始存储）：
- 根节点存储在 `heap[1]`
- 对于索引为 `i` 的节点：
  - **父节点索引**：`parent(i) = i / 2`（整数除法向下取整）
  - **左子节点索引**：`left(i) = 2 * i`
  - **右子节点索引**：`right(i) = 2 * i + 1`
- 堆的大小为 `n` 时，有效节点在 `heap[1]` 到 `heap[n]`，`heap[0]` 通常作为哨兵（Sentinel）占位

**为什么用 1-based 索引？**
因为下标公式简洁：`parent = i/2`，`left = 2i`，`right = 2i+1`。如果使用 0-based 索引，公式变为 `parent = (i-1)/2`，`left = 2i+1`，`right = 2i+2`，多了一些常数偏移，容易写错。

图解堆的数组存储结构（以最小堆为例）：

```
索引:    1   2   3   4   5   6   7
数组:   [1,  3,  5,  7,  9,  8, 10]

对应完全二叉树：
         1
       /   \
      3     5
     / \   / \
    7   9 8  10
```

#### 1.3 shiftUp（上浮）操作

**目的**：当在堆的末尾插入一个新元素后，需要通过上浮操作将其移动到正确位置，以恢复堆性质。

**伪代码**：

```
function shiftUp(idx):
    while idx > 1:
        parent = idx / 2
        if heap[idx] < heap[parent]:   // 最小堆：子节点小于父节点则交换
            swap(heap[idx], heap[parent])
            idx = parent
        else:
            break
```

**操作过程**（以最小堆为例）：
1. 比较当前节点 `heap[idx]` 与其父节点 `heap[idx/2]`
2. 如果当前节点更小，与父节点交换，然后继续向上比较
3. 重复直到到达根节点或满足堆性质

**时间复杂度**：O(log n)，因为堆的高度为 O(log n)，最多交换 `log n` 次。

**插入操作（push）**的完整流程：
```
function push(val):
    heap.append(val)      // 将新元素放到末尾
    shiftUp(heap.size-1)  // 上浮到正确位置
```

#### 1.4 shiftDown（下沉）操作

**目的**：当删除堆顶元素后，将最后一个元素移到堆顶，然后通过下沉操作将其移动到正确位置。

**伪代码**：

```
function shiftDown(idx):
    n = heap.size - 1
    while 2 * idx <= n:        // 存在左子节点
        child = 2 * idx         // 先假设左子节点是较小的
        if child + 1 <= n and heap[child + 1] < heap[child]:
            child = child + 1   // 右子节点更小，选择右子节点
        if heap[child] < heap[idx]:
            swap(heap[idx], heap[child])
            idx = child
        else:
            break
```

**操作过程**（以最小堆为例）：
1. 找到当前节点的两个子节点中较小的那个
2. 如果较小子节点比当前节点小，交换它们，然后继续向下比较
3. 重复直到到达叶子节点或满足堆性质

**时间复杂度**：O(log n)。

**删除堆顶操作（pop）**的完整流程：
```
function pop():
    heap[1] = heap[heap.size - 1]  // 用最后一个元素覆盖堆顶
    heap.remove_last()              // 删除最后一个元素
    shiftDown(1)                    // 下沉到正确位置
```

#### 1.5 建堆（Build Heap）的 O(n) 复杂度证明

**问题**：给定一个无序数组，如何将其转化为堆？

**方法一（逐个插入）**：将元素逐个 push 入空堆。时间复杂度为 O(n log n)（每个元素插入 O(log n)，共 n 个）。

**方法二（自底向上 heapify）**：从最后一个非叶子节点开始，向前逐个执行 shiftDown。时间复杂度为 **O(n)**。

**为什么是 O(n)？——严格证明：**

堆的高度为 `h = floor(log n)`。考虑每个元素执行 shiftDown 时下沉的高度：
- 高度为 `h` 的节点（叶子节点）：有约 `n/2` 个，下沉次数为 0
- 高度为 `h-1` 的节点：有约 `n/4` 个，最多下沉 1 次
- 高度为 `h-2` 的节点：有约 `n/8` 个，最多下沉 2 次
- ...
- 高度为 0 的节点（根节点）：有 1 个，最多下沉 h 次

总操作次数：
```
S = 0 * (n/2) + 1 * (n/4) + 2 * (n/8) + ... + h * 1
```

这是一个经典的公式，对上界可以计算无穷级数：
```
S ≤ n * Σ(i=0 to ∞) i / 2^(i+1) = n * 1 = n
```

其中恒等式 `Σ(i=0 to ∞) i / 2^(i+1) = 1` 可通过以下方式证明：
令 `A = Σ(i=0 to ∞) i / 2^i = 0/1 + 1/2 + 2/4 + 3/8 + 4/16 + ...`
则 `2A = 0 + 1 + 2/2 + 3/4 + 4/8 + ...`
`2A - A = A = 1 + 1/2 + 1/4 + 1/8 + ... = 2`
因此 `A = 2`，所以 `A/2 = 1`。

**结论**：自底向上的建堆方法可以在 **O(n)** 时间内完成。

**实现伪代码**：
```
function buildHeap(arr):
    heap = [0] + arr      // 1-based，arr 放在 heap[1..n]
    for i = n/2 down to 1:
        shiftDown(i)
```

> 实际从 `n/2` 开始，因为索引 `n/2+1` 到 `n` 的节点都是叶子节点（没有子节点），无需下沉。

---

### 二、priority_queue 的 3 种自定义比较函数写法

C++ 标准库中的 `std::priority_queue` 默认是**最大堆**（使用 `std::less` 作为比较器，但实际行为是最大堆——这是历史设计上的"反直觉"点，需要特别注意）。如需最小堆，需指定比较器。

#### 方法1：struct 重载 operator()（仿函数 / Functor）

**适用场景**：比较逻辑复杂、需要复用、需要携带额外状态的场景。

```cpp
// 自定义比较器：让 priority_queue 成为最小堆
struct MinHeapCmp {
    bool operator()(int a, int b) {
        return a > b;  // 注意：返回 true 表示 a 应该排在 b 后面
                       // a > b 为 true 时，a 优先级更低
    }
};

priority_queue<int, vector<int>, MinHeapCmp> pq;

// 自定义比较器：比较自定义结构体
struct Node {
    int val, idx;
};

struct NodeCmp {
    bool operator()(const Node& a, const Node& b) {
        return a.val > b.val;  // 按 val 升序，即 val 小的优先级高
    }
};

priority_queue<Node, vector<Node>, NodeCmp> pq;
```

**原理**：`priority_queue` 的第三个模板参数是比较器类型，它需要是一个可调用对象。`struct` 重载 `operator()` 是最传统的方式，兼容所有 C++ 版本。

#### 方法2：lambda + decltype

**适用场景**：比较逻辑简单、一次性使用、不想额外定义 struct 的场景。C++11 起可用。

```cpp
// 使用 lambda 定义比较器
auto cmp = [](int a, int b) { return a > b; };  // 最小堆

priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
//                                           ^^^^  需要将 lambda 对象传给构造函数
//                                     ^^^^^^^^ decltype 推导 lambda 的类型
```

**注意要点**：
- lambda 的类型是匿名且唯一的，必须用 `decltype(cmp)` 获取
- 必须将 lambda 对象 `cmp` 传给 `priority_queue` 的构造函数，因为 lambda 类型**不可默认构造**（C++20 之前）
- 如果忘记传 `cmp`，编译会报错

**更简洁的写法（C++20 起）**：
```cpp
// C++20: lambda 可以默认构造，不需要传 cmp
priority_queue<int, vector<int>, decltype([](int a, int b) { return a > b; })> pq;
```

#### 方法3：std::greater / std::less（仅适用于基本类型的简单比较器）

**适用场景**：只需要反转默认排序方向（最大堆 ↔ 最小堆），比较的元素类型已定义 `<` 运算符。

```cpp
// 默认：最大堆（使用 less，但大的元素在堆顶）
priority_queue<int> max_pq;  // 等价于 priority_queue<int, vector<int>, less<int>>

// 最小堆：使用 greater
priority_queue<int, vector<int>, greater<int>> min_pq;

// 自定义类型示例
struct Student {
    int score;
    string name;
    bool operator<(const Student& other) const {
        return score < other.score;  // 按分数排序
    }
};
// 默认最大堆：分数高的在堆顶
priority_queue<Student> pq;

// 使用 greater 变成最小堆（分数低的在堆顶）
// 注意：需要定义 operator>，或者 greater 会回退到使用 operator<
priority_queue<Student, vector<Student>, greater<Student>> min_pq;
```

**重要提醒：priority_queue 的比较器语义**

C++ 的 `priority_queue` 比较器的语义是**严格弱序（Strict Weak Ordering）**中的"比较"关系。对于比较器 `cmp(a, b)`：
- 返回 `true` 表示 `a` 的**优先级低于** `b`（即 a 应该排在 b 之后）
- 堆顶元素是优先级最高的元素

因此：
- `less<int>`：`cmp(a, b)` = `a < b`，当 `a < b` 返回 `true`，但堆顶是**最大**元素
- `greater<int>`：`cmp(a, b)` = `a > b`，当 `a > b` 返回 `true`，堆顶是**最小**元素

这和 `std::sort` 的语义一致（`sort` 用 `less` 得到升序，`less` 返回 `true` 意味着 `a` 排在 `b` 前面），但 `priority_queue` 中"排在后面"意味着"优先级低、离堆顶远"，所以 `less` 得到最大堆。

---

### 三、单调栈（Monotonic Stack）

#### 3.1 核心思想

**单调栈**是一种特殊的栈结构，其内部元素始终保持**单调递增**或**单调递减**。

- **单调递增栈**：栈底到栈顶的元素值递增（栈顶最大）
- **单调递减栈**：栈底到栈顶的元素值递减（栈顶最小）

**维护单调性的核心操作**：
当新元素入栈时，如果它破坏了栈的单调性，就不断弹出栈顶元素，直到满足单调性为止。

```cpp
// 单调递减栈模板（从栈底到栈顶递减）
stack<int> st;
for (int x : nums) {
    while (!st.empty() && st.top() < x) {
        st.pop();  // 弹出所有比 x 小的元素
    }
    st.push(x);     // 入栈
}
```

**时间复杂度分析**：虽然内层有 `while` 循环，但**每个元素最多入栈一次、出栈一次**，所以总时间复杂度为 **O(n)**。这是单调栈最关键的复杂度保证。

#### 3.2 经典应用一：下一个更大元素（Next Greater Element）

**问题描述**（LeetCode 496 风格）：给定一个数组 `nums`，对于每个元素，找出其右侧第一个比它大的元素。如果不存在，返回 -1。

**算法思路**：
- 使用**单调递减栈**（栈顶到栈底递增，即栈顶最小）
- 从左到右遍历数组
- 对于每个元素 `nums[i]`：
  - 当栈非空且 `nums[i] > nums[栈顶下标]` 时，`nums[i]` 就是栈顶元素的下一个更大元素
  - 记录答案后弹出栈顶
  - 将当前下标 `i` 入栈
- 遍历结束后，栈中剩余的元素没有下一个更大元素，答案设为 -1

```cpp
// 下一个更大元素 I
vector<int> nextGreaterElement(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans(n, -1);
    stack<int> st;  // 存储的是索引，维护栈中元素值单调递减
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && nums[i] > nums[st.top()]) {
            ans[st.top()] = nums[i];
            st.pop();
        }
        st.push(i);
    }
    return ans;
}
```

**时间复杂度**：O(n)，每个元素最多入栈一次、出栈一次。

**变体**：
- 下一个更小元素：改为单调递增栈，判断条件改为 `nums[i] < nums[st.top()]`
- 上一个更大元素：从右向左遍历
- 循环数组中的下一个更大元素：遍历两次数组（`2n`）

#### 3.3 经典应用二：柱状图中的最大矩形（Largest Rectangle in Histogram）

**问题描述**（LeetCode 84）：给定一个非负整数数组 `heights`，表示柱状图中每个柱子的高度，柱子宽度为 1。求柱状图中能勾勒出的最大矩形面积。

**算法思路**（单调递增栈）：
- 对于每根柱子 `i`，以它的高度作为矩形高度时，最大宽度取决于**左边和右边第一个比它矮的柱子**
- 左边界：`i` 左边第一个高度小于 `heights[i]` 的位置
- 右边界：`i` 右边第一个高度小于 `heights[i]` 的位置
- 面积 = `heights[i] × (right_boundary - left_boundary - 1)`

**实现**：
```cpp
int largestRectangleArea(vector<int>& heights) {
    int n = heights.size();
    stack<int> st;
    int maxArea = 0;

    for (int i = 0; i <= n; ++i) {
        // 当前处理的高度（在索引 n 处视为高度 0，用于清空栈）
        int h = (i == n) ? 0 : heights[i];

        while (!st.empty() && h < heights[st.top()]) {
            int height = heights[st.top()];
            st.pop();
            int width = st.empty() ? i : (i - st.top() - 1);
            maxArea = max(maxArea, height * width);
        }
        st.push(i);
    }
    return maxArea;
}
```

**核心技巧**：
- 在末尾增加一个高度为 0 的虚拟柱子，确保遍历结束时所有柱子都被处理
- 栈中存储的是索引，且对应的高度保持**单调递增**（从栈底到栈顶递增）
- 当遇到一个比栈顶矮的柱子时，栈顶柱子的右边界就确定了

---

### 四、单调队列（Monotonic Queue）

#### 4.1 核心思想

**单调队列**是一种双端队列（deque），其内部元素始终保持**单调性**。与单调栈不同的是，单调队列还需要处理**元素的过期**问题（例如滑动窗口中超出窗口范围的元素）。

**两个核心操作**：
1. **维护单调性**：新元素入队时，从队尾弹出所有破坏单调性的元素
2. **删除过期元素**：从队首弹出已经离开窗口的元素

**时间复杂度**：每个元素最多入队一次、出队一次，总复杂度 **O(n)**。

#### 4.2 经典应用：滑动窗口最大值

**问题描述**（LeetCode 239）：给定数组 `nums` 和窗口大小 `k`，窗口从左到右每次滑动一个位置。返回每个窗口中的最大值。

**算法思路**（单调递减队列，队首最大）：
- 使用 deque 存储**索引**，队列从头到尾对应的 `nums` 值**单调递减**
- 对于每个新元素 `nums[i]`：
  1. 如果队首元素已滑出窗口（`i - deque.front() >= k`），弹出队首
  2. 从队尾弹出所有 `nums` 值小于等于 `nums[i]` 的元素（维护递减）
  3. 将当前索引 `i` 入队尾
  4. 当窗口形成（`i >= k-1`），队首元素即为当前窗口最大值

```cpp
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    int n = nums.size();
    deque<int> dq;         // 存储索引，维护 nums 值单调递减
    vector<int> ans;

    for (int i = 0; i < n; ++i) {
        // 1. 移除窗口外的过期元素（队首）
        while (!dq.empty() && i - dq.front() >= k) {
            dq.pop_front();
        }
        // 2. 维护单调递减性（队尾）
        while (!dq.empty() && nums[i] >= nums[dq.back()]) {
            dq.pop_back();
        }
        // 3. 当前元素索引入队
        dq.push_back(i);
        // 4. 记录答案（窗口形成后）
        if (i >= k - 1) {
            ans.push_back(nums[dq.front()]);
        }
    }
    return ans;
}
```

#### 4.3 单调队列的 DP 优化简介

单调队列可以用于优化一类**带区间限制的动态规划问题**。

**典型场景**：DP 转移方程形如 `dp[i] = max/min{dp[j] + f(i)}`，其中 `j ∈ [i-k, i-1]`，即在长度为 k 的窗口内取最值。

**示例**：「跳跃游戏 VI」（LeetCode 1696）：
- `dp[i] = nums[i] + max{dp[j]}`，其中 `j ∈ [max(0, i-k), i-1]`
- 使用单调队列维护窗口 `[i-k, i-1]` 内 dp[j] 的最大值
- 每个状态转移 O(1)，总复杂度 O(n)

---

## 💻 代码模板

### 模板1：手写最小堆（1-based）

```cpp
class MinHeap {
private:
    vector<int> heap;

    void shiftUp(int idx) {
        while (idx > 1 && heap[idx] < heap[idx / 2]) {
            swap(heap[idx], heap[idx / 2]);
            idx /= 2;
        }
    }

    void shiftDown(int idx) {
        int n = heap.size() - 1;
        while (2 * idx <= n) {
            int child = 2 * idx;
            if (child + 1 <= n && heap[child + 1] < heap[child])
                child++;
            if (heap[child] < heap[idx]) {
                swap(heap[idx], heap[child]);
                idx = child;
            } else break;
        }
    }

public:
    MinHeap() { heap.push_back(0); }  // 哨兵

    void push(int val) {
        heap.push_back(val);
        shiftUp(heap.size() - 1);
    }

    void pop() {
        if (heap.size() <= 1) return;
        heap[1] = heap.back();
        heap.pop_back();
        shiftDown(1);
    }

    int top() { return heap[1]; }

    bool empty() { return heap.size() <= 1; }

    int size() { return heap.size() - 1; }
};
```

### 模板2：单调栈——下一个更大元素

```cpp
vector<int> nextGreaterElement(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans(n, -1);
    stack<int> st;
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && nums[i] > nums[st.top()]) {
            ans[st.top()] = nums[i];
            st.pop();
        }
        st.push(i);
    }
    return ans;
}
```

### 模板3：单调队列——滑动窗口最大值

```cpp
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    int n = nums.size();
    deque<int> dq;
    vector<int> ans;
    for (int i = 0; i < n; ++i) {
        while (!dq.empty() && i - dq.front() >= k)
            dq.pop_front();
        while (!dq.empty() && nums[i] >= nums[dq.back()])
            dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1)
            ans.push_back(nums[dq.front()]);
    }
    return ans;
}
```

---

## ⚠️ 易错点与优化技巧

### 易错点

1. **数组索引错误**：手写堆时使用 1-based 还是 0-based 必须统一。建议使用 1-based（公式更简洁），并在构造时 push 哨兵 `heap.push_back(0)`。

2. **priority_queue 的比较器语义**：
   - `priority_queue<int, vector<int>, greater<int>>` → **最小堆**
   - `priority_queue<int>` → **最大堆**（这是最常被搞反的）
   - 记住口诀：greater → 小的优先级高 → 最小堆

3. **lambda 作为比较器时忘记传参**：
   ```cpp
   // 错误：lambda 不可默认构造（C++20前）
   auto cmp = [](int a, int b) { return a > b; };
   priority_queue<int, vector<int>, decltype(cmp)> pq;  // 编译错误！
   
   // 正确：需要将 lambda 传给构造函数
   priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);  // 正确
   ```

4. **单调栈/队列存索引还是存值**：强烈建议**存储索引**。存储值会丢失位置信息，无法判断是否过期。

5. **单调队列的过期判断**：使用 `i - dq.front() >= k` 而不是 `> k`。窗口 `[i-k+1, i]` 包含 k 个元素。

6. **遍历结束后栈中剩余元素**：单调栈遍历结束后，栈中剩余元素表示它们没有找到下一个更大/更小元素，需要设为默认值（通常是 -1 或 n）。

### 优化技巧

1. **使用 reserve 减少 vector 扩容**：
   ```cpp
   vector<int> ans;
   ans.reserve(n - k + 1);  // 预分配空间
   ```

2. **小根堆 vs 大根堆的选择**：
   - 需要取最小值 → 小根堆（`greater<int>`）
   - 需要取最大值 → 大根堆（默认 `less<int>`）
   - 需要第 k 大 → 小根堆（维护 k 个最大元素）
   - 需要第 k 小 → 大根堆（维护 k 个最小元素）

3. **使用 `emplace` 替代 `push`**：对于存储 pair/struct 的优先队列，`emplace` 可以原地构造，避免临时对象。
   ```cpp
   pq.emplace(val, idx);  // 比 pq.push({val, idx}) 更高效
   ```

4. **手写堆 vs STL priority_queue**：
   - STL priority_queue 不支持删除堆中任意元素
   - 如需删除/修改任意元素，可手写堆或使用 `std::set`
   - 竞赛中优先使用 STL priority_queue，除非需要特殊操作

5. **单调栈优化技巧**：
   - 在数组末尾补一个"极小值"（或极大值），可以统一处理逻辑，避免遍历后单独处理栈内剩余元素

6. **单调队列与优先队列的选择**：
   - 滑动窗口最大值 → 单调队列 O(n)，优先队列 O(n log k)
   - 数据范围 n <= 10^6 时，单调队列的 O(n) 优势明显

---

## 📝 真题精练

### 真题1：合并K个有序链表（优先队列经典应用）

**题目描述**：

给定 K 个升序排列的链表，将它们合并成一个升序链表，返回合并后的链表头节点。

**输入格式**：

第一行一个整数 K（1 <= K <= 10^5），表示链表个数。

接下来 K 行，每行表示一个链表：第一个整数 n_i 表示该链表的节点数，后面跟着 n_i 个整数表示链表节点的值（升序排列）。

**输出格式**：

一行，输出合并后链表的所有节点值，用空格分隔。

**数据范围**：
- 1 <= K <= 10^5
- 0 <= n_i <= 500
- 总节点数 N = Σ n_i <= 10^5
- 节点值范围：-10^4 <= val <= 10^4

**样例输入**：
```
3
3 1 4 5
3 1 3 4
2 2 6
```

**样例输出**：
```
1 1 2 3 4 4 5 6
```

**样例解释**：
三个链表分别为 [1,4,5]、[1,3,4]、[2,6]，合并后为 [1,1,2,3,4,4,5,6]。

**AC 代码**：

```cpp
#include <bits/stdc++.h>
using namespace std;

// 链表节点定义
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// 优先队列的比较器：按节点值升序（最小堆）
struct Cmp {
    bool operator()(ListNode* a, ListNode* b) {
        return a->val > b->val;  // val 小的优先级高
    }
};

ListNode* mergeKLists(vector<ListNode*>& lists) {
    // 最小堆，存储每个链表的当前头节点
    priority_queue<ListNode*, vector<ListNode*>, Cmp> pq;

    // 将所有非空链表的头节点入堆
    for (ListNode* head : lists) {
        if (head != nullptr) {
            pq.push(head);
        }
    }

    // 哨兵头节点，简化边界处理
    ListNode dummy(0);
    ListNode* tail = &dummy;

    // 每次取出最小的节点，接到结果链表尾部
    while (!pq.empty()) {
        ListNode* node = pq.top();
        pq.pop();

        tail->next = node;
        tail = tail->next;

        // 如果该节点后面还有节点，将下一个节点入堆
        if (node->next != nullptr) {
            pq.push(node->next);
        }
    }

    return dummy.next;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;

    vector<ListNode*> lists(K);
    for (int i = 0; i < K; ++i) {
        int n;
        cin >> n;

        ListNode dummy(0);
        ListNode* tail = &dummy;
        for (int j = 0; j < n; ++j) {
            int val;
            cin >> val;
            tail->next = new ListNode(val);
            tail = tail->next;
        }
        lists[i] = dummy.next;
    }

    ListNode* result = mergeKLists(lists);

    // 输出结果
    while (result != nullptr) {
        cout << result->val;
        result = result->next;
        if (result != nullptr) cout << " ";
    }
    cout << "\n";

    return 0;
}
```

**复杂度分析**：
- **时间复杂度**：O(N log K)，其中 N 为总节点数，K 为链表个数。每个节点入堆和出堆各一次，堆操作 O(log K)。
- **空间复杂度**：O(K)，优先队列中最多同时存储 K 个节点（每个链表一个当前节点）。

**关键技巧**：
- 使用哨兵头节点（dummy node）简化结果链表的构建
- 每次从优先队列取出一个节点后，将该节点的下一个节点入堆
- 比较器 `a->val > b->val` 使得 val 小的节点优先级更高（最小堆）

---

### 真题2：滑动窗口最大值（单调队列经典应用）

**题目描述**：

给定一个整数数组 `nums` 和一个整数 `k`，请找出所有长度为 k 的滑动窗口中的最大值，并按顺序返回。

**输入格式**：

第一行两个整数 n 和 k（1 <= k <= n <= 10^6），分别表示数组长度和窗口大小。

第二行 n 个整数，表示数组 nums 的元素。

**输出格式**：

一行，输出 n-k+1 个整数，表示每个窗口的最大值，用空格分隔。

**数据范围**：
- 1 <= k <= n <= 10^6
- -10^4 <= nums[i] <= 10^4

**样例输入**：
```
8 3
1 3 -1 -3 5 3 6 7
```

**样例输出**：
```
3 3 5 5 6 7
```

**样例解释**：
```
窗口位置                窗口内容        最大值
[1  3  -1] -3  5  3  6  7       3
1  [3  -1  -3] 5  3  6  7       3
1  3  [-1  -3  5] 3  6  7       5
1  3  -1  [-3  5  3] 6  7       5
1  3  -1  -3  [5  3  6] 7       6
1  3  -1  -3  5  [3  6  7]      7
```

**AC 代码**：

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    int n = nums.size();
    deque<int> dq;  // 存储索引，维护 nums 值单调递减
    vector<int> ans;
    ans.reserve(n - k + 1);  // 预分配空间

    for (int i = 0; i < n; ++i) {
        // 步骤1：移除窗口外的过期元素（队首）
        // 窗口范围是 [i-k+1, i]，队首索引小于 i-k+1 则过期
        while (!dq.empty() && dq.front() < i - k + 1) {
            dq.pop_front();
        }

        // 步骤2：维护单调递减性（队尾）
        // 弹出所有值小于当前元素的值（它们不可能是后续窗口的最大值）
        while (!dq.empty() && nums[dq.back()] <= nums[i]) {
            dq.pop_back();
        }

        // 步骤3：当前元素索引入队
        dq.push_back(i);

        // 步骤4：窗口形成后记录答案（队首即为当前窗口最大值）
        if (i >= k - 1) {
            ans.push_back(nums[dq.front()]);
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }

    vector<int> result = maxSlidingWindow(nums, k);

    for (int i = 0; i < (int)result.size(); ++i) {
        if (i > 0) cout << " ";
        cout << result[i];
    }
    cout << "\n";

    return 0;
}
```

**复杂度分析**：
- **时间复杂度**：O(n)，每个元素最多入队一次、出队一次。deque 的 push/pop 操作均为 O(1)。
- **空间复杂度**：O(k)，deque 中最多存储 k 个索引。

**关键技巧**：
- 使用 **deque**（双端队列）同时支持队首和队尾的弹出操作
- 过期判断：`dq.front() < i - k + 1`（等价于 `i - dq.front() >= k`）
- 维护递减：弹出队尾所有 `<= nums[i]` 的元素（使用 `<=` 而非 `<`，确保单调递减，新元素优先级更高）
- 使用 `reserve` 预分配答案数组空间，减少扩容开销
- `ios::sync_with_stdio(false); cin.tie(nullptr);` 加速 IO，对于 n <= 10^6 的数据量至关重要

---

## 🎯 本课小结

### 核心知识掌握清单

| 知识点 | 掌握要求 | 复杂度 |
|--------|---------|--------|
| 堆的数组存储（1-based） | 熟练写出 parent/left/right 索引公式 | O(1) |
| shiftUp / shiftDown 操作 | 能手写完整实现，理解终止条件 | O(log n) |
| 建堆 heapify | 理解 O(n) 证明思路，能手写 | O(n) |
| priority_queue 自定义比较器 | 掌握 3 种写法，理解比较器语义 | O(log n) per push/pop |
| 单调栈（递增/递减） | 能手写模板，理解入栈出栈条件 | O(n) |
| 单调队列（滑动窗口） | 能手写模板，理解过期删除与单调维护 | O(n) |
| 单调结构应用 | 能识别并解决经典问题变体 | — |

### 解题思维总结

1. **看到"第K大/第K小"** → 优先队列（维护大小为 K 的堆）
2. **看到"合并多个有序序列"** → 优先队列（多路归并）
3. **看到"下一个更大/更小元素"** → 单调栈
4. **看到"某个区间内的最值"** → 单调队列（固定窗口）/ 优先队列（变长窗口）
5. **看到"最大矩形面积"** → 单调递增栈
6. **看到"带区间限制的 DP 最优化转移"** → 单调队列优化 DP

### 常见坑点回顾

- `priority_queue` 默认是**最大堆**，最小堆需指定 `greater<int>`
- lambda 作为比较器必须传对象给构造函数（C++20 前）
- 单调栈/队列**存索引**比存值更灵活
- 单调队列的过期条件用索引差判断（`dq.front() < i - k + 1`）
- 数组末尾添加虚拟元素可以简化单调栈的收尾逻辑
