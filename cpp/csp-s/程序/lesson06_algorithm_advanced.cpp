/*
 * ============================================================
 * CSP-S 第06课：algorithm 库高级函数
 * ============================================================
 *
 * 对应考纲知识点：
 *   - sort 与自定义比较函数（Introsort 原理、三种比较方式）
 *   - nth_element 的 O(n) 快速选择算法
 *   - next_permutation / prev_permutation 字典序排列生成
 *   - lower_bound / upper_bound / binary_search 二分查找
 *   - 离散化的两种实现方法（排序+去重+二分 / map 映射）
 *   - unique 的去重原理与 erase-remove idiom
 *   - stable_sort 的语义与应用场景
 *
 * 日期：2026-06-27
 * ============================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <set>
#include <map>
using namespace std;

// ==================== 模块1：sort 自定义排序多示例 ====================

// -------------------- 示例1：函数指针方式 --------------------
bool cmp_desc_func(int a, int b) {
    // 降序：a > b 时 a 应排在 b 前面
    return a > b;
}

// -------------------- 示例2：仿函数 (struct) 方式 --------------------
struct CmpDesc {
    // 仿函数：重载 operator()，使得对象可以像函数一样调用
    // 相比函数指针，编译器更容易内联优化
    bool operator()(int a, int b) const {
        return a > b;
    }
};

// 用于多关键字排序的仿函数
struct CmpMulti {
    // 先按绝对值降序，再按原始值升序
    bool operator()(int a, int b) const {
        if (abs(a) != abs(b)) return abs(a) > abs(b);
        return a < b;
    }
};

// -------------------- 示例3：lambda 表达式方式 --------------------
//（在主函数中直接演示，方便捕获外部变量）

// -------------------- 示例4：多关键字排序 --------------------
// 定义一个学生结构体，用于演示多关键字排序
struct Student {
    string name;
    int score;   // 分数——主关键字，降序
    int id;      // 编号——次关键字，升序

    // 重载 << 方便输出
    friend ostream& operator<<(ostream& os, const Student& s) {
        os << "{" << s.name << ", score=" << s.score << ", id=" << s.id << "}";
        return os;
    }
};

void demo_sort_module() {
    cout << "\n========== 模块1：sort 自定义排序多示例 ==========\n\n";

    vector<int> v;

    // --- 示例1：函数指针 ---
    v = {3, 1, 4, 1, 5, 9, 2, 6};
    sort(v.begin(), v.end(), cmp_desc_func);
    cout << "[函数指针降序] ";
    for (int x : v) cout << x << " ";
    cout << "\n";

    // --- 示例2：仿函数 ---
    v = {3, 1, 4, 1, 5, 9, 2, 6};
    sort(v.begin(), v.end(), CmpDesc());
    cout << "[仿函数降序]   ";
    for (int x : v) cout << x << " ";
    cout << "\n";

    // --- 示例3：lambda 表达式 ---
    v = {3, 1, 4, 1, 5, 9, 2, 6};
    sort(v.begin(), v.end(), [](int a, int b) {
        return a > b;  // 降序 lambda
    });
    cout << "[lambda降序]   ";
    for (int x : v) cout << x << " ";
    cout << "\n";

    // lambda 带捕获：按与 5 的距离排序
    int center = 5;
    sort(v.begin(), v.end(), [center](int a, int b) {
        return abs(a - center) < abs(b - center);
    });
    cout << "[按离" << center << "的距离排序] ";
    for (int x : v) cout << x << " ";
    cout << "\n";

    // --- 示例4：多关键字排序 ---
    vector<Student> stu = {
        {"Alice", 95, 3},
        {"Bob",   85, 1},
        {"Carol", 95, 2},
        {"Dave",  85, 4},
        {"Eve",   90, 5}
    };

    // 先按 score 降序，score 相同时按 id 升序
    sort(stu.begin(), stu.end(), [](const Student& a, const Student& b) {
        if (a.score != b.score) return a.score > b.score;  // 分数高的在前
        return a.id < b.id;                                 // 分数相同，编号小的在前
    });

    cout << "\n[多关键字排序：score降序, id升序]\n";
    for (const auto& s : stu) {
        cout << "  " << s << "\n";
    }

    // --- 示例5：stable_sort 使用场景 ---
    // 场景：先按 name 排序，再按 score 排序，
    //      希望 score 相同的学生保持 name 的字典序
    vector<Student> stu2 = {
        {"Bob",   90, 1},
        {"Alice", 85, 2},
        {"Bob",   85, 3},
        {"Alice", 90, 4},
        {"Carol", 90, 5}
    };

    // 第一步：按 name 升序排序（用 sort 即可）
    sort(stu2.begin(), stu2.end(), [](const Student& a, const Student& b) {
        return a.name < b.name;
    });

    // 第二步：按 score 降序排序，使用 stable_sort 保持同分数的 name 顺序
    stable_sort(stu2.begin(), stu2.end(), [](const Student& a, const Student& b) {
        return a.score > b.score;
    });

    cout << "\n[stable_sort：先按name排，再stable_sort按score降序]\n";
    cout << "  （分数相同时，保留名字的字典序）\n";
    for (const auto& s : stu2) {
        cout << "  " << s << "\n";
    }
}

// ==================== 模块2：nth_element 示例 ====================

void demo_nth_element() {
    cout << "\n========== 模块2：nth_element 示例 ==========\n\n";

    // 原始数组
    vector<int> v = {7, 2, 5, 1, 8, 3, 9, 4, 6};
    int n = v.size();

    // --- 求第 k 小的元素（1-based） ---
    vector<int> temp = v;  // 保留副本
    int k = 4;  // 求第 4 小的元素

    cout << "原始数组: ";
    for (int x : v) cout << x << " ";
    cout << "\n";

    // nth_element 将第 k-1 个位置上的元素放到正确位置
    nth_element(temp.begin(), temp.begin() + k - 1, temp.end());
    cout << "第 " << k << " 小的元素: " << temp[k - 1] << "\n";

    // 验证：左侧元素 <= 第 k 小，右侧元素 >= 第 k 小
    cout << "左侧区间（前 " << k - 1 << " 个，无序）: ";
    for (int i = 0; i < k - 1; ++i) cout << temp[i] << " ";
    cout << "\n";
    cout << "右侧区间（后 " << n - k << " 个，无序）: ";
    for (int i = k; i < n; ++i) cout << temp[i] << " ";
    cout << "\n";

    // --- 求中位数 ---
    temp = v;
    nth_element(temp.begin(), temp.begin() + n / 2, temp.end());
    int median = temp[n / 2];
    cout << "中位数（n=" << n << "）: " << median << "（位置 n/2=" << n/2 << "）\n";

    // --- 求前 k 小的元素（不保证有序，可根据需要排序） ---
    temp = v;
    k = 3;
    nth_element(temp.begin(), temp.begin() + k, temp.end());
    // 前 k 个元素现在是整个数组中最小的 k 个，但内部无序
    cout << "前 " << k << " 小的元素（无序）: ";
    for (int i = 0; i < k; ++i) cout << temp[i] << " ";
    cout << "\n";

    // 如果需要对前 k 个排序
    sort(temp.begin(), temp.begin() + k);
    cout << "前 " << k << " 小的元素（有序）: ";
    for (int i = 0; i < k; ++i) cout << temp[i] << " ";
    cout << "\n";

    // --- 性能对比提示 ---
    cout << "\n[性能提示]\n";
    cout << "  sort 求第k小:     O(n log n) ≈ " << n << " * " << int(log2(n)) << " ≈ " << n * int(log2(n)) << " 次比较\n";
    cout << "  nth_element 求第k小: O(n) ≈ " << n << " 次比较\n";
    cout << "  n 越大，nth_element 优势越明显\n";
}

// ==================== 模块3：next_permutation 全排列生成 ====================

void demo_permutation() {
    cout << "\n========== 模块3：next_permutation 全排列生成 ==========\n\n";

    // --- next_permutation 生成全排列 ---
    vector<int> v = {1, 2, 3};  // ★ 必须初始为升序，才能生成所有排列
    cout << "全排列生成（n=3）:\n";
    int cnt = 0;
    do {
        cout << "  " << ++cnt << ": ";
        for (int x : v) cout << x << " ";
        cout << "\n";
    } while (next_permutation(v.begin(), v.end()));

    // --- 判断是否还有下一个排列 ---
    cout << "\n判断是否还有下一个排列:\n";
    vector<int> p = {3, 2, 1};  // 最大排列
    cout << "  当前排列: ";
    for (int x : p) cout << x << " ";
    cout << "\n";
    bool has_next = next_permutation(p.begin(), p.end());
    cout << "  有下一个排列? " << (has_next ? "是" : "否（已回绕到最小排列）") << "\n";
    cout << "  next_permutation 后: ";
    for (int x : p) cout << x << " ";
    cout << "\n";

    // --- prev_permutation 生成上一个排列 ---
    cout << "\nprev_permutation 示例（降序起始）:\n";
    vector<int> q = {3, 2, 1};
    cnt = 0;
    do {
        cout << "  " << ++cnt << ": ";
        for (int x : q) cout << x << " ";
        cout << "\n";
    } while (prev_permutation(q.begin(), q.end()));

    // --- 部分排列演示 ---
    cout << "\n部分排列（选择 4 个元素，演示更长序列）:\n";
    vector<int> w = {1, 2, 3, 4};
    cout << "  {1, 2, 3, 4} 的下一个排列: ";
    next_permutation(w.begin(), w.end());
    for (int x : w) cout << x << " ";  // 应输出 1 2 4 3
    cout << "\n";
}

// ==================== 模块4：lower_bound / upper_bound 正确用法 ====================

void demo_binary_search() {
    cout << "\n========== 模块4：lower_bound / upper_bound 正确用法 ==========\n\n";

    // --- 在有序数组中使用 ---
    vector<int> v = {1, 2, 2, 2, 3, 5, 7};  // 升序
    int x = 2;

    cout << "有序数组: ";
    for (int val : v) cout << val << " ";
    cout << "\n查找值 x = " << x << "\n\n";

    // lower_bound：第一个 >= x 的位置
    auto lb = lower_bound(v.begin(), v.end(), x);
    cout << "lower_bound(x): 第一个 >= " << x << " 的位置 = 下标 " << (lb - v.begin());
    cout << "（值 = " << *lb << "）\n";

    // upper_bound：第一个 > x 的位置
    auto ub = upper_bound(v.begin(), v.end(), x);
    cout << "upper_bound(x): 第一个 >  " << x << " 的位置 = 下标 " << (ub - v.begin());
    cout << "（值 = " << *ub << "）\n";

    // 等于 x 的元素个数 = ub - lb
    int cnt_eq = ub - lb;
    cout << "等于 " << x << " 的元素个数: " << cnt_eq << "\n";

    // 小于 x 的元素个数 = lb - begin
    int cnt_lt = lb - v.begin();
    cout << "小于 " << x << " 的元素个数: " << cnt_lt << "\n";

    // 大于 x 的元素个数 = end - ub
    int cnt_gt = v.end() - ub;
    cout << "大于 " << x << " 的元素个数: " << cnt_gt << "\n";

    // --- binary_search：判断是否存在 ---
    cout << "\nbinary_search(" << x << "): "
         << (binary_search(v.begin(), v.end(), x) ? "存在" : "不存在") << "\n";
    cout << "binary_search(10): "
         << (binary_search(v.begin(), v.end(), 10) ? "存在" : "不存在") << "\n";

    // --- 降序序列中的二分查找（需传入 greater<int>()） ---
    vector<int> v_desc = {9, 7, 5, 3, 1};
    cout << "\n降序数组: ";
    for (int val : v_desc) cout << val << " ";
    cout << "\n";

    auto lb_desc = lower_bound(v_desc.begin(), v_desc.end(), 5, greater<int>());
    // 在降序中，lower_bound 返回第一个 <= 5 的位置
    cout << "降序 lower_bound(5): 下标 " << (lb_desc - v_desc.begin());
    cout << "（值 = " << *lb_desc << "）\n";

    // --- 对 set 使用成员函数 lower_bound ---
    cout << "\n[重要：set 须用成员函数 lower_bound]\n";
    set<int> s = {1, 3, 5, 7, 9, 11};

    // ★ 正确：使用 set::lower_bound —— O(log n)
    auto it_set = s.lower_bound(5);
    cout << "  s.lower_bound(5)    (O(log n)): " << *it_set << "\n";

    // ★ 错误演示（概念说明，不实际执行以避免性能问题）：
    cout << "  std::lower_bound(s.begin(), s.end(), 5): ";
    cout << "注意！对 set 使用 std::lower_bound 会退化为 O(n) 遍历！\n";
    cout << "  因为 set 的迭代器不是随机访问迭代器。\n";

    // --- 检查 end() 的重要性 ---
    cout << "\n[安全示范：检查返回值]\n";
    auto it_safe = lower_bound(v.begin(), v.end(), 100);
    if (it_safe != v.end()) {
        cout << "  找到元素: " << *it_safe << "\n";
    } else {
        cout << "  未找到 >= 100 的元素（it == end()）\n";
    }
}

// ==================== 模块5：离散化完整模板 ====================

void demo_discretization() {
    cout << "\n========== 模块5：离散化完整模板 ==========\n\n";

    // 原始数据：包含大坐标和重复值
    vector<int> raw = {1000000000, -500, 3, 1000000000, 7, -500, 2024};

    cout << "原始数据: ";
    for (int x : raw) cout << x << " ";
    cout << "\n\n";

    // =========== 方法1：排序 + 去重 + 二分查找 ===========
    cout << "--- 方法1：排序 + 去重 + 二分查找 ---\n";

    vector<int> sorted = raw;  // 复制一份用于排序去重
    sort(sorted.begin(), sorted.end());
    cout << "  排序后: ";
    for (int x : sorted) cout << x << " ";
    cout << "\n";

    // unique 将不重复的元素移到前面，返回新结尾迭代器
    auto new_end = unique(sorted.begin(), sorted.end());
    sorted.erase(new_end, sorted.end());  // 必须配合 erase 才能真正删除
    cout << "  去重后: ";
    for (int x : sorted) cout << x << " ";
    cout << "\n";

    // 构造离散化查询函数（1-based 索引，常用于树状数组等）
    auto get_id_1based = [&sorted](int x) {
        // lower_bound 返回第一个 >= x 的位置
        return lower_bound(sorted.begin(), sorted.end(), x) - sorted.begin() + 1;
    };

    // 0-based 版本（备用，如需要可与 1-based 版本互换）
    // auto get_id_0based = [&sorted](int x) {
    //     return lower_bound(sorted.begin(), sorted.end(), x) - sorted.begin();
    // };

    cout << "\n  离散化映射结果（1-based）:\n";
    for (int x : raw) {
        cout << "    " << x << " -> id = " << get_id_1based(x) << "\n";
    }

    // --- 还原：通过 ID 找回原始值 ---
    cout << "\n  还原映射:\n";
    for (int id = 1; id <= (int)sorted.size(); ++id) {
        cout << "    id " << id << " -> 原始值 " << sorted[id - 1] << "\n";
    }

    // =========== 方法2：map 映射 ===========
    cout << "\n--- 方法2：map 映射 ---\n";

    map<int, int> id_map;
    int cur_id = 0;  // 0-based
    for (int x : raw) {
        if (id_map.find(x) == id_map.end()) {
            id_map[x] = ++cur_id;  // 首次出现才分配新 ID（1-based）
        }
    }

    cout << "  map 映射结果（1-based）:\n";
    for (int x : raw) {
        cout << "    " << x << " -> id = " << id_map[x] << "\n";
    }

    // =========== 方法对比 ===========
    cout << "\n--- 方法对比 ---\n";
    cout << "  方法1（排序+去重+二分）:\n";
    cout << "    - 预处理 O(n log n)，单次查询 O(log n)（常数小）\n";
    cout << "    - 映射值紧凑连续，可直接用作数组下标\n";
    cout << "    - 适合离线处理（所有数据已知的情况）\n";
    cout << "  方法2（map 映射）:\n";
    cout << "    - 单次插入/查询 O(log n)（常数较大，红黑树）\n";
    cout << "    - 映射值也连续，但 map 本身有额外内存开销\n";
    cout << "    - 适合在线处理（数据逐步给出的情况）\n";

    // =========== unique 原理深入演示 ===========
    cout << "\n--- unique 原理深入演示 ---\n";
    vector<int> u = {1, 2, 2, 3, 3, 3, 4, 5, 5};
    cout << "  原始数组:            ";
    for (int x : u) cout << x << " ";
    cout << "\n";

    auto it = unique(u.begin(), u.end());
    cout << "  unique 后（未 erase）: ";
    for (int x : u) cout << x << " ";  // 末尾是未定义的值
    cout << "\n";
    cout << "  unique 返回的迭代器指向下标 " << (it - u.begin()) << "\n";

    u.erase(it, u.end());
    cout << "  erase 后:            ";
    for (int x : u) cout << x << " ";
    cout << "\n";
}

// ==================== 模块6：综合测试 main 函数 ====================

int main() {
    // 加速 I/O
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "============================================================\n";
    cout << "  CSP-S 第06课：algorithm 库高级函数 —— 综合演示程序\n";
    cout << "============================================================\n";

    // 按顺序演示所有模块
    demo_sort_module();
    demo_nth_element();
    demo_permutation();
    demo_binary_search();
    demo_discretization();

    cout << "\n============================================================\n";
    cout << "  所有模块演示完毕！\n";
    cout << "============================================================\n";

    return 0;
}
