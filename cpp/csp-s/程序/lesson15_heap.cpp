/**
 * 第15课：二叉堆与对顶堆（Binary Heap & Double Heap）
 * 对应CSP-S考纲知识点：
 *   - 二叉堆的插入（swim）和删除（sink）
 *   - 堆化（heapify）O(n) 建堆
 *   - 堆排序（Heap Sort）O(n log n) 原地排序
 *   - 对顶堆（双堆）维护动态中位数
 *   - 优先队列（priority_queue）在贪心问题中的应用
 *   - 合并果子（Huffman 编码）
 *
 * 包含以下实现：
 *   1. 手写小根堆（完整实现：push, pop, top, heapify）
 *   2. 堆排序
 *   3. 对顶堆（动态中位数）
 *   4. 合并果子
 *   5. STL priority_queue 使用技巧
 *   6. 真题扩展：第K小的动态数据流（对顶堆变体）
 */

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// 一、手写小根堆（数组实现，下标从 1 开始）
// 功能：push O(log n), pop O(log n), top O(1), heapify O(n)
// ============================================================
class MinHeap {
private:
    vector<int> heap;  // heap[0] 占位，实际数据从 heap[1] 开始
    int sz;            // 当前堆大小

    // 上浮：新插入的元素向上调整
    void swim(int i) {
        while (i > 1 && heap[i] < heap[i / 2]) {
            swap(heap[i], heap[i / 2]);
            i /= 2;
        }
    }

    // 下沉：堆顶元素向下调整
    void sink(int i) {
        while (2 * i <= sz) {
            int j = 2 * i;  // 左儿子
            // 选更小的儿子
            if (j < sz && heap[j + 1] < heap[j]) j++;
            if (heap[i] <= heap[j]) break;  // 堆序已满足
            swap(heap[i], heap[j]);
            i = j;
        }
    }

public:
    MinHeap() : heap(1, 0), sz(0) {}  // heap[0] 占位

    // 插入元素
    void push(int x) {
        heap.push_back(x);
        sz++;
        swim(sz);
    }

    // 删除堆顶
    void pop() {
        if (sz == 0) return;
        heap[1] = heap[sz];
        heap.pop_back();
        sz--;
        if (sz > 0) sink(1);
    }

    // 获取堆顶
    int top() const { return sz > 0 ? heap[1] : -1; }

    int size() const { return sz; }
    bool empty() const { return sz == 0; }

    // O(n) 建堆：从最后一个非叶子节点开始下沉
    void heapify(const vector<int>& arr) {
        sz = arr.size();
        heap.resize(sz + 1);
        for (int i = 0; i < sz; i++) heap[i + 1] = arr[i];
        for (int i = sz / 2; i >= 1; i--) sink(i);
    }

    // 获取底层数组（调试用）
    const vector<int>& data() const { return heap; }
};

// ============================================================
// 二、大根堆（类似实现，比较方向取反）
// ============================================================
class MaxHeap {
private:
    vector<int> heap;
    int sz;

    void swim(int i) {
        while (i > 1 && heap[i] > heap[i / 2]) {
            swap(heap[i], heap[i / 2]);
            i /= 2;
        }
    }

    void sink(int i) {
        while (2 * i <= sz) {
            int j = 2 * i;
            if (j < sz && heap[j + 1] > heap[j]) j++;  // 选更大的儿子
            if (heap[i] >= heap[j]) break;
            swap(heap[i], heap[j]);
            i = j;
        }
    }

public:
    MaxHeap() : heap(1, 0), sz(0) {}

    void push(int x) {
        heap.push_back(x); sz++;
        swim(sz);
    }

    void pop() {
        if (sz == 0) return;
        heap[1] = heap[sz];
        heap.pop_back(); sz--;
        if (sz > 0) sink(1);
    }

    int top() const { return sz > 0 ? heap[1] : -1; }
    int size() const { return sz; }
    bool empty() const { return sz == 0; }
};

// ============================================================
// 三、堆排序（Heap Sort）
// 使用大根堆实现升序排序
// 时间复杂度 O(n log n)，空间 O(1)（原地排序）
// 不稳定排序
// ============================================================
void heap_sort(vector<int>& a) {
    int n = a.size();

    // 将 0-indexed 转为 1-indexed（在函数内操作副本）
    // 方法：直接在原数组上使用 0-indexed 的堆操作
    // 对于 0-indexed：父=(i-1)/2, 左子=2i+1, 右子=2i+2

    // 1. 建大根堆（heapify）
    auto sink = [&](int i, int heap_size) {
        while (true) {
            int l = 2 * i + 1, r = 2 * i + 2;
            int largest = i;
            if (l < heap_size && a[l] > a[largest]) largest = l;
            if (r < heap_size && a[r] > a[largest]) largest = r;
            if (largest == i) break;
            swap(a[i], a[largest]);
            i = largest;
        }
    };

    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        sink(i, n);
    }

    // 2. 排序：依次将堆顶（最大值）与末尾交换，然后缩小堆
    for (int i = n - 1; i > 0; i--) {
        swap(a[0], a[i]);   // 最大值到末尾
        sink(0, i);          // 恢复堆序（堆大小 = i）
    }
}

// ============================================================
// 四、对顶堆（动态中位数）
// 大根堆存储较小的一半 → top 即为中位数（奇数时）
// 小根堆存储较大的一半
// 始终保持：maxHeap.size() == minHeap.size() 或 maxHeap.size() == minHeap.size() + 1
// ============================================================
class MedianFinder {
private:
    priority_queue<int> maxHeap;                              // 较小的一半（大根堆）
    priority_queue<int, vector<int>, greater<int>> minHeap;   // 较大的一半（小根堆）

public:
    // 插入一个数 O(log n)
    void addNum(int x) {
        if (maxHeap.empty() || x <= maxHeap.top()) {
            maxHeap.push(x);
        } else {
            minHeap.push(x);
        }
        // 平衡
        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        } else if (minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }

    // 查询中位数 O(1)
    double findMedian() {
        if (maxHeap.size() > minHeap.size()) {
            return maxHeap.top();
        } else {
            return (maxHeap.top() + minHeap.top()) / 2.0;
        }
    }

    // 查询当前元素个数
    int size() { return maxHeap.size() + minHeap.size(); }
};

// ============================================================
// 五、合并果子（Huffman 编码，贪心 + 小根堆）
// 每次取最小的两堆合并，将新堆放回
// ============================================================
long long merge_fruits(const vector<int>& fruits) {
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int x : fruits) pq.push(x);

    long long total_cost = 0;
    while (pq.size() > 1) {
        int a = pq.top(); pq.pop();
        int b = pq.top(); pq.pop();
        total_cost += a + b;
        pq.push(a + b);
    }
    return total_cost;
}

// ============================================================
// 六、STL priority_queue 使用技巧
// ============================================================
void stl_demo() {
    // 1. 默认大根堆
    priority_queue<int> max_pq;

    // 2. 小根堆
    priority_queue<int, vector<int>, greater<int>> min_pq;

    // 3. 自定义比较器（大根堆，另一种写法）
    auto cmp = [](int a, int b) { return a < b; };  // 注意：返回 true 则 a 在 b 之后
    priority_queue<int, vector<int>, decltype(cmp)> custom_pq(cmp);

    // 4. 存 pair，按第一个元素排序
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pair_pq;
    // 注意：pair 比较是先 first 后 second

    // 5. 大根堆存负数 = 变相小根堆（技巧）
    priority_queue<int> neg_pq;
    neg_pq.push(-5);  // 存负数，top 取反即为原来最小值
}

// ============================================================
// 七、第K小的动态数据流（对顶堆变体）
// 左堆（大根堆）存储最小的k个元素 → 堆顶即为第k小
// 右堆（小根堆）存储其余元素
// 支持插入 O(log n)、查询 O(1)（在已维护好k的前提下）
// ============================================================
class KthSmallest {
private:
    priority_queue<int> maxHeap;                              // 存储最小的k个（大根堆）
    priority_queue<int, vector<int>, greater<int>> minHeap;   // 存储其余元素（小根堆）
    int k;

    // 调整左堆大小恰好为k
    void adjust() {
        while ((int)maxHeap.size() > k) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }
        while ((int)maxHeap.size() < k && !minHeap.empty()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
        // 交叉调整：确保左堆顶 ≤ 右堆顶
        while (!maxHeap.empty() && !minHeap.empty() && maxHeap.top() > minHeap.top()) {
            int a = maxHeap.top(); maxHeap.pop();
            int b = minHeap.top(); minHeap.pop();
            maxHeap.push(b);
            minHeap.push(a);
        }
    }

public:
    KthSmallest() : k(1) {}

    // 插入一个数 O(log n)
    void insert(int x) {
        maxHeap.push(x);
        // 调整左堆大小
        while ((int)maxHeap.size() > k) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }
        // 交叉调整保证堆序
        if (!minHeap.empty() && maxHeap.top() > minHeap.top()) {
            int a = maxHeap.top(); maxHeap.pop();
            int b = minHeap.top(); minHeap.pop();
            maxHeap.push(b);
            minHeap.push(a);
        }
    }

    // 设置当前需要查询的k值，并重新调整
    void setK(int new_k) {
        k = new_k;
        adjust();
    }

    // 查询当前第k小的数 O(1)
    int getKth() {
        if (maxHeap.empty()) return -1;
        return maxHeap.top();
    }

    int size() { return maxHeap.size() + minHeap.size(); }
};

// ============================================================
// 八、测试与示例程序
// ============================================================

// 示例1：手写堆基本操作
void test_custom_heap() {
    MinHeap mh;
    vector<int> data = {5, 3, 8, 1, 9, 2, 7};
    cout << "小根堆测试（heapify 建堆）：\n";
    mh.heapify(data);
    cout << "依次弹出：";
    while (!mh.empty()) {
        cout << mh.top() << " ";
        mh.pop();
    }
    cout << '\n';
}

// 示例2：堆排序
void test_heap_sort() {
    vector<int> a = {5, 3, 8, 1, 9, 2, 7, 4, 6};
    cout << "堆排序前：";
    for (int x : a) cout << x << " ";
    cout << '\n';
    heap_sort(a);
    cout << "堆排序后：";
    for (int x : a) cout << x << " ";
    cout << '\n';
}

// 示例3：动态中位数
void test_median_finder() {
    MedianFinder mf;
    vector<int> stream = {5, 15, 1, 3, 2, 8, 7, 9, 10, 6, 11, 4};
    cout << "数据流动态中位数测试：\n";
    for (int i = 0; i < (int)stream.size(); i++) {
        mf.addNum(stream[i]);
        cout << "加入 " << stream[i] << " → ";
        if (i % 2 == 0) {  // 奇数个
            cout << "中位数 = " << mf.findMedian() << '\n';
        }
    }
}

// 示例4：合并果子
void test_merge_fruits() {
    vector<int> fruits = {1, 2, 9, 5, 3};
    cout << "合并果子最小代价（Huffman）："
         << merge_fruits(fruits) << '\n';
    // 预期：1+2=3, 3+3=6, 5+6=11, 9+11=20 → total=3+6+11+20=40
}

// 示例5：第K小的动态数据流
void test_kth_smallest() {
    KthSmallest kth;
    cout << "第K小动态数据流测试：\n";
    vector<int> stream = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    for (int x : stream) {
        kth.insert(x);
    }
    cout << "数据流: 5 2 8 1 9 3 7 4 6\n";
    for (int k = 1; k <= min(9, kth.size()); k++) {
        kth.setK(k);
        cout << "第" << k << "小 = " << kth.getKth() << '\n';
    }
    // 预期输出: 1, 2, 3, 4, 5, 6, 7, 8, 9
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    test_custom_heap();
    cout << '\n';
    test_heap_sort();
    cout << '\n';
    test_median_finder();
    cout << '\n';
    test_merge_fruits();
    cout << '\n';
    test_kth_smallest();

    return 0;
}
