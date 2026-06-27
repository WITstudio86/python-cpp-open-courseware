/******************************************************************************
 * 课程编号：第05课
 * 课程标题：priority_queue 与单调结构
 * 对应CSP-S考纲知识点：
 *   - 堆（Heap）的实现原理、数组存储、shiftUp/shiftDown 操作
 *   - priority_queue 的自定义比较函数（仿函数、lambda、greater/less）
 *   - 单调栈（Monotonic Stack）：下一个更大元素、最大矩形面积
 *   - 单调队列（Monotonic Queue）：滑动窗口最大值
 * 日期：2026/06/27
 ******************************************************************************/

#include <bits/stdc++.h>
using namespace std;

// ==================== 模块1：手写最小堆完整实现 ====================

/**
 * MinHeap 类
 * 使用 1-based 索引的数组存储完全二叉树
 * heap[0] 作为哨兵不使用，有效元素从 heap[1] 开始
 * 索引关系（1-based）：
 *   parent(i) = i / 2
 *   left(i)   = 2 * i
 *   right(i)  = 2 * i + 1
 */
class MinHeap {
private:
    vector<int> heap;  // 1-based 存储，heap[0] 为哨兵

    /**
     * 上浮操作（Shift Up）
     * 作用：当堆末尾插入新元素后，将其上浮到正确位置以维护堆性质
     * 时间复杂度：O(log n)
     * 过程：不断与父节点比较，如果当前节点更小则交换，直到满足堆性质
     */
    void shiftUp(int idx) {
        // 当不是根节点（idx > 1）且当前节点小于父节点时
        while (idx > 1 && heap[idx] < heap[idx / 2]) {
            swap(heap[idx], heap[idx / 2]);
            idx /= 2;  // 继续向上检查
        }
    }

    /**
     * 下沉操作（Shift Down）
     * 作用：当堆顶被替换后，将新堆顶下沉到正确位置以维护堆性质
     * 时间复杂度：O(log n)
     * 过程：找到两个子节点中较小的，如果比当前节点小则交换，继续下沉
     */
    void shiftDown(int idx) {
        int n = heap.size() - 1;  // 有效元素个数（排除哨兵）

        // 当存在左子节点时继续下沉
        while (2 * idx <= n) {
            int child = 2 * idx;  // 先假设左子节点是最小的

            // 如果右子节点存在且更小，则选择右子节点
            if (child + 1 <= n && heap[child + 1] < heap[child]) {
                child++;
            }

            // 如果较小子节点比当前节点小，交换并继续下沉
            if (heap[child] < heap[idx]) {
                swap(heap[idx], heap[child]);
                idx = child;
            } else {
                // 已经满足堆性质，停止下沉
                break;
            }
        }
    }

public:
    /**
     * 构造函数
     * 在索引 0 处放置哨兵值 0（不会被使用）
     * 这样做使得从索引 1 开始的 1-based 索引公式成立
     */
    MinHeap() {
        heap.push_back(0);  // 哨兵占位
    }

    /**
     * 插入元素
     * 将新元素放入数组末尾，然后执行上浮操作
     * 时间复杂度：O(log n)
     */
    void push(int val) {
        heap.push_back(val);           // 放到末尾
        shiftUp(heap.size() - 1);      // 上浮到正确位置
    }

    /**
     * 删除堆顶元素
     * 用最后一个元素覆盖堆顶，然后删除最后一个元素，再执行下沉操作
     * 时间复杂度：O(log n)
     */
    void pop() {
        if (heap.size() <= 1) {
            // 堆为空，忽略操作
            return;
        }
        heap[1] = heap.back();  // 用最后一个元素覆盖堆顶
        heap.pop_back();         // 删除最后一个元素
        shiftDown(1);            // 下沉新堆顶
    }

    /**
     * 返回堆顶元素（最小值）
     * 时间复杂度：O(1)
     */
    int top() {
        // 调用者需要保证堆非空
        return heap[1];
    }

    /**
     * 判断堆是否为空
     * heap 中至少有哨兵（heap[0]），所以空堆的 size() == 1
     */
    bool empty() {
        return heap.size() <= 1;
    }

    /**
     * 返回堆中元素个数（不包含哨兵）
     */
    int size() {
        return heap.size() - 1;
    }
};


// ==================== 模块2：priority_queue 自定义比较器 3 种写法 ====================

/**
 * 写法1：struct 重载 operator()（仿函数 / Functor）
 * 这是最传统、最兼容的写法，适用于所有 C++ 版本
 * 优点：可以携带状态、可以给类型命名、方便复用
 * 适用场景：比较逻辑复杂、需要在多处使用、或需要携带额外数据
 */
struct MinHeapCmp1 {
    // operator() 返回 true 表示 a 的优先级低于 b（a 排在 b 之后）
    // a > b 为 true 时，a 更大，优先级更低，所以这是最小堆
    bool operator()(int a, int b) {
        return a > b;
    }
};

// 自定义类型 + 自定义比较器示例
struct Student {
    string name;
    int score;

    Student(string n, int s) : name(n), score(s) {}
};

struct StudentCmp {
    // 按分数降序排列：分数高的优先级高（最大堆）
    bool operator()(const Student& a, const Student& b) {
        return a.score < b.score;
    }
};

/**
 * 写法2：lambda + decltype
 * C++11 起可用，适合一次性使用的简单比较器
 * 注意：C++20 之前 lambda 不可默认构造，必须将 lambda 对象传给构造函数
 * 适用场景：比较逻辑简单、仅在局部使用、不想额外定义 struct
 */
void demo_lambda_cmp() {
    // 定义一个比较用的 lambda 表达式
    auto cmp = [](int a, int b) {
        return a > b;  // 最小堆：小的优先级高
    };

    // 必须将 lambda 对象 cmp 传给 priority_queue 的构造函数
    // 因为 C++20 之前 lambda 类型不可默认构造
    priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);

    // 使用示例
    pq.push(5);
    pq.push(2);
    pq.push(8);
    while (!pq.empty()) {
        cout << pq.top() << " ";  // 输出：2 5 8
        pq.pop();
    }
    cout << "\n";
}

/**
 * 写法3：std::greater / std::less（基本类型与定义了 operator< 的类型）
 * 最简单的写法，只需要反转默认的排序方向
 * 适用场景：基本类型（int, double 等）或已定义比较运算符的自定义类型
 */
void demo_greater_cmp() {
    // 默认：最大堆（大的在堆顶）
    priority_queue<int> max_pq;  // 等价于 priority_queue<int, vector<int>, less<int>>

    // 最小堆：使用 greater<int>
    priority_queue<int, vector<int>, greater<int>> min_pq;

    // 测试数据
    vector<int> test = {3, 1, 4, 1, 5, 9, 2, 6};
    for (int x : test) {
        max_pq.push(x);
        min_pq.push(x);
    }

    // 输出最大堆（降序）
    cout << "最大堆（默认，less<int>）：";
    while (!max_pq.empty()) {
        cout << max_pq.top() << " ";
        max_pq.pop();
    }
    cout << "\n";

    // 输出最小堆（升序）
    cout << "最小堆（greater<int>）：";
    while (!min_pq.empty()) {
        cout << min_pq.top() << " ";
        min_pq.pop();
    }
    cout << "\n";
}


// ==================== 模块3：单调栈模板 ====================

/**
 * 题目：下一个更大元素 I（LeetCode 496 风格）
 * 描述：对于 nums 中的每个元素，找到其右侧第一个比它大的元素
 * 如果不存在，则该位置的结果为 -1
 *
 * 核心思想：使用单调递减栈
 * - 栈中存储索引，对应 nums 值从栈底到栈顶递减（栈顶最小）
 * - 遍历数组，当新元素大于栈顶元素对应的值时，
 *   新元素就是栈顶元素的"下一个更大元素"
 *
 * 时间复杂度：O(n)——每个元素最多入栈一次、出栈一次
 * 空间复杂度：O(n)——栈中最多存储 n 个元素
 */
vector<int> nextGreaterElement(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans(n, -1);  // 默认值 -1 表示不存在下一个更大元素
    stack<int> st;            // 存储索引，维护 nums[st] 单调递减

    for (int i = 0; i < n; ++i) {
        // 当前元素 nums[i] 大于栈顶元素对应的值时
        // nums[i] 就是栈顶元素的下一个更大元素
        while (!st.empty() && nums[i] > nums[st.top()]) {
            ans[st.top()] = nums[i];  // 记录答案
            st.pop();                  // 弹出已找到答案的元素
        }
        // 当前索引入栈
        st.push(i);
    }
    // 遍历结束后栈中剩余元素没有下一个更大元素，ans 保持默认的 -1

    return ans;
}

/**
 * 题目：柱状图中的最大矩形（LeetCode 84 风格）
 * 描述：给定 heights 数组表示柱子高度，柱子宽度为 1
 * 求柱状图中能勾勒出的最大矩形面积
 *
 * 核心思想：单调递增栈
 * - 对于每根柱子 i，以它的高度为矩形高度
 * - 左边界：左边第一个比它矮的柱子
 * - 右边界：右边第一个比它矮的柱子
 * - 面积 = heights[i] * (right - left - 1)
 *
 * 技巧：在数组末尾追加一个高度为 0 的虚拟柱子
 * 这样可以确保循环结束时所有柱子都被处理完毕
 *
 * 时间复杂度：O(n)
 * 空间复杂度：O(n)
 */
int largestRectangleArea(vector<int>& heights) {
    int n = heights.size();
    stack<int> st;        // 存储索引，维护 heights 值单调递增
    int maxArea = 0;

    // 遍历到 n（包含虚拟的索引 n），heights[n] 视为 0
    for (int i = 0; i <= n; ++i) {
        // 当前柱子的高度（索引 n 对应虚拟高度 0）
        int currentHeight = (i == n) ? 0 : heights[i];

        // 当遇到一个比栈顶柱子矮的柱子时
        // 栈顶柱子的右边界就是当前索引 i
        while (!st.empty() && currentHeight < heights[st.top()]) {
            int h = heights[st.top()];  // 栈顶柱子的高度
            st.pop();

            // 计算宽度
            // 如果栈空了，说明左边没有比它矮的柱子，宽度为 i（从 0 到 i-1）
            // 否则左边界为当前栈顶的索引
            int width = st.empty() ? i : (i - st.top() - 1);

            // 更新最大面积
            maxArea = max(maxArea, h * width);
        }
        st.push(i);
    }

    return maxArea;
}


// ==================== 模块4：单调队列模板 ====================

/**
 * 题目：滑动窗口最大值（LeetCode 239）
 * 描述：给定数组 nums 和窗口大小 k，窗口每次向右滑动一个位置
 * 返回每个窗口中最大的元素
 *
 * 核心思想：单调递减队列（deque）
 * - 队列从队首到队尾对应的 nums 值严格递减，队首始终是当前窗口最大值
 * - 两个核心操作：
 *   1. 维护单调性：新元素入队时，从队尾弹出所有比它小的元素
 *   2. 删除过期元素：从队首弹出已经滑出窗口的元素
 *
 * 时间复杂度：O(n)——每个元素最多入队一次、出队一次
 * 空间复杂度：O(k)——deque 中最多存储 k 个索引
 */
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    int n = nums.size();
    deque<int> dq;     // 存储索引，维护对应 nums 值单调递减
    vector<int> ans;
    ans.reserve(n - k + 1);  // 预分配空间，优化性能

    for (int i = 0; i < n; ++i) {
        // 步骤1：删除过期元素（队首）
        // 当前窗口范围是 [i-k+1, i]
        // 队首索引小于 i-k+1 说明已经滑出窗口
        while (!dq.empty() && dq.front() < i - k + 1) {
            dq.pop_front();
        }

        // 步骤2：维护单调递减性（队尾）
        // 弹出队尾所有小于等于 nums[i] 的元素
        // 因为它们不可能是后续任何包含 i 的窗口中的最大值
        // 使用 <= 而非 <，确保单调递减（新元素优先级更高，覆盖等值旧元素）
        while (!dq.empty() && nums[dq.back()] <= nums[i]) {
            dq.pop_back();
        }

        // 步骤3：当前索引入队
        dq.push_back(i);

        // 步骤4：窗口形成后记录答案
        // 当 i >= k-1 时，第一个完整窗口形成
        if (i >= k - 1) {
            ans.push_back(nums[dq.front()]);  // 队首即为当前窗口最大值
        }
    }

    return ans;
}


// ==================== 模块5：综合测试 main 函数 ====================

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "============================================\n";
    cout << "  第05课：priority_queue 与单调结构\n";
    cout << "  综合测试程序\n";
    cout << "============================================\n\n";

    // ---------- 测试1：手写最小堆 ----------
    cout << "【测试1】手写最小堆（MinHeap）\n";
    cout << "--------------------------------------------\n";

    MinHeap heap;
    vector<int> testData = {5, 3, 8, 1, 9, 2, 7, 4, 6};

    cout << "插入顺序：";
    for (int x : testData) {
        cout << x << " ";
        heap.push(x);
    }
    cout << "\n";

    cout << "堆中元素个数：" << heap.size() << "\n";

    cout << "逐一出堆（最小堆，升序）：";
    while (!heap.empty()) {
        cout << heap.top() << " ";
        heap.pop();
    }
    cout << "\n\n";

    // ---------- 测试2：手写堆的正确性验证（重新填入数据） ----------
    cout << "堆为空：";
    cout << (heap.empty() ? "是" : "否") << "\n\n";

    // ---------- 测试3：priority_queue 的 3 种比较器 ----------
    cout << "【测试2】priority_queue 自定义比较器\n";
    cout << "--------------------------------------------\n";

    // 写法1：仿函数
    cout << "写法1（struct operator()，最小堆）：";
    {
        priority_queue<int, vector<int>, MinHeapCmp1> pq1;
        for (int x : testData) pq1.push(x);
        while (!pq1.empty()) {
            cout << pq1.top() << " ";
            pq1.pop();
        }
        cout << "\n";
    }

    // 写法2：lambda + decltype
    cout << "写法2（lambda + decltype，最小堆）：";
    demo_lambda_cmp();

    // 写法3：greater（以及默认 less）
    cout << "写法3（greater / less）：\n";
    demo_greater_cmp();

    // 自定义类型 + 比较器
    cout << "自定义类型（Student 按分数降序）：\n";
    {
        priority_queue<Student, vector<Student>, StudentCmp> pq;
        pq.emplace("Alice", 95);
        pq.emplace("Bob", 87);
        pq.emplace("Charlie", 92);
        pq.emplace("Diana", 78);
        while (!pq.empty()) {
            auto s = pq.top();
            cout << "  " << s.name << ": " << s.score << "\n";
            pq.pop();
        }
    }
    cout << "\n";

    // ---------- 测试4：单调栈——下一个更大元素 ----------
    cout << "【测试3】单调栈——下一个更大元素\n";
    cout << "--------------------------------------------\n";

    {
        vector<int> nums1 = {2, 1, 2, 4, 3};
        cout << "输入数组：";
        for (int x : nums1) cout << x << " ";
        cout << "\n";

        vector<int> ans1 = nextGreaterElement(nums1);
        cout << "下一个更大元素：";
        for (int x : ans1) cout << x << " ";
        cout << "\n";
        // 预期输出：4 2 4 -1 -1
    }

    // 额外测试：单调递减情况
    {
        vector<int> nums2 = {5, 4, 3, 2, 1};
        cout << "输入数组（单调递减）：";
        for (int x : nums2) cout << x << " ";
        cout << "\n";

        vector<int> ans2 = nextGreaterElement(nums2);
        cout << "下一个更大元素：";
        for (int x : ans2) cout << x << " ";
        cout << "\n";
        // 预期输出：-1 -1 -1 -1 -1
    }

    // 额外测试：单调递增情况
    {
        vector<int> nums3 = {1, 2, 3, 4, 5};
        cout << "输入数组（单调递增）：";
        for (int x : nums3) cout << x << " ";
        cout << "\n";

        vector<int> ans3 = nextGreaterElement(nums3);
        cout << "下一个更大元素：";
        for (int x : ans3) cout << x << " ";
        cout << "\n";
        // 预期输出：2 3 4 5 -1
    }
    cout << "\n";

    // ---------- 测试5：单调栈——最大矩形面积 ----------
    cout << "【测试4】单调栈——最大矩形面积\n";
    cout << "--------------------------------------------\n";

    {
        vector<int> heights1 = {2, 1, 5, 6, 2, 3};
        cout << "柱状图高度：";
        for (int h : heights1) cout << h << " ";
        cout << "\n";

        int maxArea1 = largestRectangleArea(heights1);
        cout << "最大矩形面积：" << maxArea1 << "（预期：10）\n";
    }

    {
        vector<int> heights2 = {2, 4};
        cout << "柱状图高度：";
        for (int h : heights2) cout << h << " ";
        cout << "\n";

        int maxArea2 = largestRectangleArea(heights2);
        cout << "最大矩形面积：" << maxArea2 << "（预期：4）\n";
    }

    {
        vector<int> heights3 = {1, 1, 1, 1, 1};
        cout << "柱状图高度（全等）：";
        for (int h : heights3) cout << h << " ";
        cout << "\n";

        int maxArea3 = largestRectangleArea(heights3);
        cout << "最大矩形面积：" << maxArea3 << "（预期：5）\n";
    }
    cout << "\n";

    // ---------- 测试6：单调队列——滑动窗口最大值 ----------
    cout << "【测试5】单调队列——滑动窗口最大值\n";
    cout << "--------------------------------------------\n";

    {
        vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
        int k = 3;
        cout << "数组：";
        for (int x : nums) cout << x << " ";
        cout << "\n";
        cout << "窗口大小 k = " << k << "\n";

        vector<int> ans = maxSlidingWindow(nums, k);
        cout << "每个窗口的最大值：";
        for (int x : ans) cout << x << " ";
        cout << "\n";
        // 预期输出：3 3 5 5 6 7
    }

    {
        vector<int> nums2 = {1, -1};
        int k2 = 1;
        cout << "数组：";
        for (int x : nums2) cout << x << " ";
        cout << "\n";
        cout << "窗口大小 k = " << k2 << "\n";

        vector<int> ans2 = maxSlidingWindow(nums2, k2);
        cout << "每个窗口的最大值：";
        for (int x : ans2) cout << x << " ";
        cout << "\n";
        // 预期输出：1 -1
    }

    {
        vector<int> nums3 = {9, 11};
        int k3 = 2;
        cout << "数组：";
        for (int x : nums3) cout << x << " ";
        cout << "\n";
        cout << "窗口大小 k = " << k3 << "\n";

        vector<int> ans3 = maxSlidingWindow(nums3, k3);
        cout << "每个窗口的最大值：";
        for (int x : ans3) cout << x << " ";
        cout << "\n";
        // 预期输出：11
    }

    cout << "\n============================================\n";
    cout << "  所有测试完成！\n";
    cout << "============================================\n";

    return 0;
}
