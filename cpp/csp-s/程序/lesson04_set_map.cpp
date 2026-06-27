/**
 * ============================================================
 * 课程编号：第04课
 * 课程标题：set / map 与 unordered 容器
 * 对应考纲：红黑树实现、哈希表实现、自定义比较器、unordered_map优化
 *
 * 本程序演示：
 *   1. set 自定义排序（函数对象 / lambda 两种方式）
 *   2. map 自定义 key 排序
 *   3. unordered_map 自定义哈希（pair<int,int> 等复合类型）
 *   4. unordered_map reserve 预分配优化
 *   5. set/map vs unordered_map 性能对比测试
 *   6. multiset 与 multimap 的基础用法
 *   7. lower_bound / upper_bound / equal_range 范围查询
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

// ==================== 1. set 自定义排序 ====================

// 方法一：函数对象（Functor）
struct CmpByLen {
    bool operator()(const string& a, const string& b) const {
        if (a.size() != b.size()) return a.size() < b.size();  // 按长度升序
        return a < b;  // 长度相同时字典序升序
    }
};

struct CmpDesc {
    bool operator()(int a, int b) const {
        return a > b;  // 降序排列
    }
};

void demo_set_custom_cmp() {
    cout << "\n========== 1. set 自定义排序 ==========\n\n";

    // 1.1 默认升序
    cout << "【默认升序 set<int>】\n  ";
    set<int> s1 = {5, 2, 8, 1, 9, 3};
    for (int x : s1) cout << x << ' ';
    cout << "\n\n";

    // 1.2 降序排列（函数对象）
    cout << "【降序 set<int, CmpDesc>】\n  ";
    set<int, CmpDesc> s2 = {5, 2, 8, 1, 9, 3};
    for (int x : s2) cout << x << ' ';
    cout << "\n\n";

    // 1.3 按字符串长度排序
    cout << "【按长度排序 set<string, CmpByLen>】\n";
    set<string, CmpByLen> s3 = {"apple", "pie", "a", "banana", "c", "dog"};
    cout << "  原始: apple pie a banana c dog\n";
    cout << "  排序: ";
    for (const auto& str : s3) cout << str << ' ';
    cout << "\n\n";

    // 1.4 使用 greater<int> 快捷实现降序
    cout << "【使用 greater<int> 快捷降序】\n  ";
    set<int, greater<int>> s4 = {5, 2, 8, 1, 9, 3};
    for (int x : s4) cout << x << ' ';
    cout << "\n\n";

    // 1.5 Lambda 表达式（C++11 + decltype）
    cout << "【Lambda 自定义比较】\n";
    auto cmp = [](int a, int b) { return a > b; };
    set<int, decltype(cmp)> s5(cmp);  // 必须传 lambda 给构造函数
    s5 = {5, 2, 8, 1, 9, 3};
    cout << "  ";
    for (int x : s5) cout << x << ' ';
    cout << "\n  (使用 decltype(lambda) 声明类型)\n\n";
}

// ==================== 2. map 自定义 key 排序 ====================

// 按 pair 的第一个元素降序，第一个相同时第二个升序
struct PairCmp {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) const {
        if (a.first != b.first) return a.first > b.first;  // first 降序
        return a.second < b.second;  // second 升序
    }
};

void demo_map_custom_key() {
    cout << "========== 2. map 自定义 key 排序 ==========\n\n";

    // 2.1 默认排序（first 升序）
    cout << "【默认 map<pair<int,int>, string>】\n";
    map<pair<int, int>, string> mp1;
    mp1[{2, 3}] = "A";
    mp1[{2, 1}] = "B";
    mp1[{1, 5}] = "C";
    mp1[{3, 0}] = "D";
    for (const auto& [k, v] : mp1)
        cout << "  (" << k.first << "," << k.second << ") -> " << v << '\n';
    cout << "\n";

    // 2.2 自定义 pair 排序
    cout << "【自定义 map<pair<int,int>, string, PairCmp>】\n";
    cout << "  规则：first 降序，second 升序\n";
    map<pair<int, int>, string, PairCmp> mp2;
    mp2[{2, 3}] = "A";
    mp2[{2, 1}] = "B";
    mp2[{1, 5}] = "C";
    mp2[{3, 0}] = "D";
    for (const auto& [k, v] : mp2)
        cout << "  (" << k.first << "," << k.second << ") -> " << v << '\n';
    cout << "\n";

    // 2.3 自定义结构体作为 key
    cout << "【自定义结构体作为 key（需 operator<）】\n";
    struct Point {
        int x, y;
        bool operator<(const Point& o) const {
            if (x != o.x) return x < o.x;
            return y < o.y;
        }
    };
    map<Point, string> mp3;
    mp3[{2, 3}] = "P1";
    mp3[{1, 5}] = "P2";
    mp3[{2, 1}] = "P3";
    mp3[{3, 0}] = "P4";
    for (const auto& [k, v] : mp3)
        cout << "  (" << k.x << "," << k.y << ") -> " << v << '\n';
    cout << "\n";
}

// ==================== 3. unordered_map 自定义哈希 ====================

// 为 pair<int, int> 提供哈希函数
struct PairHash {
    size_t operator()(const pair<int, int>& p) const {
        auto h1 = hash<int>{}(p.first);
        auto h2 = hash<int>{}(p.second);
        // hash_combine: 黄金比例 + 移位，避免 (1,2) 与 (2,1) 相同哈希
        return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
    }
};

// 为 pair 提供相等比较（unordered_map 也需要 == 运算符）
struct PairEq {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) const {
        return a.first == b.first && a.second == b.second;
    }
};

// 为自定义结构体提供哈希
struct PointHash {
    size_t operator()(const pair<int, int>& p) const {
        return (size_t)p.first * 1000000007ULL + (size_t)p.second;
    }
};

void demo_unordered_map_custom_hash() {
    cout << "========== 3. unordered_map 自定义哈希 ==========\n\n";

    // 3.1 pair<int,int> 自定义哈希
    cout << "【unordered_map<pair<int,int>, int, PairHash>】\n";
    unordered_map<pair<int, int>, int, PairHash> ump;
    ump[{1, 2}] = 10;
    ump[{2, 1}] = 20;  // (1,2) 和 (2,1) 是不同的 key
    ump[{1, 2}] = 30;  // 覆盖了 10
    for (const auto& [k, v] : ump)
        cout << "  (" << k.first << "," << k.second << ") -> " << v << '\n';
    cout << "\n";

    // 3.2 演示哈希冲突：查看 bucket 分布
    cout << "【Bucket 分布（验证哈希质量）】\n";
    unordered_map<pair<int, int>, int, PairHash> ump2;
    ump2.reserve(100);
    // 插入 20 个不同 pair
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 4; j++)
            ump2[{i, j}] = i * 10 + j;

    cout << "  bucket_count = " << ump2.bucket_count() << "\n";
    cout << "  load_factor  = " << ump2.load_factor() << "\n";
    cout << "  各 bucket 元素数量：\n";
    set<int> bucket_sizes;
    for (size_t b = 0; b < ump2.bucket_count(); b++) {
        int sz = (int)ump2.bucket_size(b);
        if (sz > 0) bucket_sizes.insert(sz);
    }
    cout << "  出现过的 bucket 大小: ";
    for (int sz : bucket_sizes) cout << sz << ' ';
    cout << " (理想情况下应均匀分布)\n\n";

    // 3.3 字符串的自定义哈希（不区分大小写）
    cout << "【字符串的自定义哈希（不区分大小写）】\n";
    struct CaseInsensitiveHash {
        size_t operator()(const string& s) const {
            string lower = s;
            for (char& c : lower) c = tolower(c);
            return hash<string>{}(lower);
        }
    };
    struct CaseInsensitiveEq {
        bool operator()(const string& a, const string& b) const {
            if (a.size() != b.size()) return false;
            for (size_t i = 0; i < a.size(); i++)
                if (tolower(a[i]) != tolower(b[i])) return false;
            return true;
        }
    };
    // 注意：这里仅演示哈希，实际映射时 key 仍为原始大小写
    cout << "  (演示完毕，此功能用于不区分大小写的键匹配)\n\n";
}

// ==================== 4. unordered_map reserve 预分配 ====================

void demo_unordered_reserve() {
    cout << "========== 4. unordered_map reserve 预分配 ==========\n\n";

    const int N = 50000;

    // 4.1 无 reserve
    {
        unordered_map<int, int> ump;
        auto start = high_resolution_clock::now();
        for (int i = 0; i < N; i++) ump[i] = i;
        auto end = high_resolution_clock::now();
        auto dur = duration_cast<microseconds>(end - start).count();
        cout << "  无 reserve: " << dur << " μs";
        cout << "  (bucket_count=" << ump.bucket_count()
             << ", load_factor=" << ump.load_factor() << ")\n";
    }

    // 4.2 有 reserve
    {
        unordered_map<int, int> ump;
        ump.reserve(N);  // 关键优化！
        auto start = high_resolution_clock::now();
        for (int i = 0; i < N; i++) ump[i] = i;
        auto end = high_resolution_clock::now();
        auto dur = duration_cast<microseconds>(end - start).count();
        cout << "  有 reserve: " << dur << " μs";
        cout << "  (bucket_count=" << ump.bucket_count()
             << ", load_factor=" << ump.load_factor() << ")\n";
    }

    // 4.3 调整 max_load_factor
    {
        unordered_map<int, int> ump;
        ump.max_load_factor(0.5);  // 降低负载因子，减少冲突
        ump.reserve(N);
        auto start = high_resolution_clock::now();
        for (int i = 0; i < N; i++) ump[i] = i;
        auto end = high_resolution_clock::now();
        auto dur = duration_cast<microseconds>(end - start).count();
        cout << "  reserve+低负载: " << dur << " μs";
        cout << "  (bucket_count=" << ump.bucket_count()
             << ", load_factor=" << ump.load_factor() << ")\n";
    }
    cout << "  → reserve 是最廉价的哈希表优化，务必使用！\n\n";
}

// ==================== 5. set/map vs unordered_map 性能对比 ====================

void demo_performance_comparison() {
    cout << "========== 5. set/map vs unordered_map 性能对比 ==========\n\n";

    const int N = 200000;

    auto now = [] { return high_resolution_clock::now(); };
    auto elapsed = [](auto start, auto end) {
        return duration_cast<microseconds>(end - start).count();
    };

    // 生成测试数据：N 个随机数
    vector<int> data(N);
    mt19937 rng(42);
    uniform_int_distribution<int> dist(1, N * 10);
    for (int i = 0; i < N; i++) data[i] = dist(rng);

    // ---- 插入测试 ----
    cout << "【插入 " << N << " 个随机整数】\n";
    {
        set<int> s;
        auto start = now();
        for (int x : data) s.insert(x);
        auto end = now();
        cout << "  set:           " << setw(8) << elapsed(start, end) << " μs\n";
    }
    {
        unordered_set<int> us;
        auto start = now();
        for (int x : data) us.insert(x);
        auto end = now();
        cout << "  unordered_set: " << setw(8) << elapsed(start, end) << " μs\n";
    }
    {
        unordered_set<int> us;
        us.reserve(N);
        auto start = now();
        for (int x : data) us.insert(x);
        auto end = now();
        cout << "  unordered_set(reserve): " << elapsed(start, end) << " μs\n";
    }

    // ---- 查找测试 ----
    cout << "\n【查找 " << N << " 次】\n";
    {
        set<int> s(data.begin(), data.end());
        auto start = now();
        long long checksum = 0;
        for (int x : data) if (s.count(x)) checksum += x;
        auto end = now();
        cout << "  set:           " << setw(8) << elapsed(start, end) << " μs (checksum=" << checksum << ")\n";
    }
    {
        unordered_set<int> us(data.begin(), data.end());
        auto start = now();
        long long checksum = 0;
        for (int x : data) if (us.count(x)) checksum += x;
        auto end = now();
        cout << "  unordered_set: " << setw(8) << elapsed(start, end) << " μs (checksum=" << checksum << ")\n";
    }

    // ---- 有序遍历测试 ----
    cout << "\n【有序遍历（只有 set/map 能做到）】\n";
    {
        set<int> s(data.begin(), data.end());
        auto start = now();
        long long sum = 0;
        for (int x : s) sum += x;
        auto end = now();
        cout << "  set 有序遍历:  " << elapsed(start, end) << " μs (sum=" << sum << ")\n";
        cout << "  → unordered_set 无法直接有序遍历，需拷贝到 vector 再 sort\n";
    }
    cout << "\n";
}

// ==================== 6. multiset / multimap ====================

void demo_multiset_multimap() {
    cout << "========== 6. multiset / multimap ==========\n\n";

    cout << "【multiset：允许重复元素的有序集合】\n";
    multiset<int> ms = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    cout << "  原始：" << "3 1 4 1 5 9 2 6 5\n";
    cout << "  排序：";
    for (int x : ms) cout << x << ' ';
    cout << "\n";
    cout << "  count(1) = " << ms.count(1) << "\n";
    cout << "  count(5) = " << ms.count(5) << "\n";
    cout << "  count(7) = " << ms.count(7) << " (不存在)\n";

    // 删除所有 5
    ms.erase(5);
    cout << "  erase(5) 后: ";
    for (int x : ms) cout << x << ' ';
    cout << "\n";

    // 只删除一个 1
    auto it = ms.find(1);
    if (it != ms.end()) ms.erase(it);
    cout << "  删除一个1后: ";
    for (int x : ms) cout << x << ' ';
    cout << "\n\n";

    cout << "【multimap：允许重复 key 的有序映射】\n";
    multimap<string, int> mmp;
    mmp.insert({"Alice", 95});
    mmp.insert({"Bob", 87});
    mmp.insert({"Alice", 92});
    mmp.insert({"Alice", 88});
    mmp.insert({"Bob", 91});

    cout << "  所有记录：\n";
    for (const auto& [name, score] : mmp)
        cout << "    " << name << ": " << score << '\n';

    // 查找 Alice 的所有成绩
    cout << "  Alice 的成绩：\n";
    auto [lo, hi] = mmp.equal_range("Alice");
    for (auto it = lo; it != hi; ++it)
        cout << "    " << it->second << '\n';
    cout << "\n";
}

// ==================== 7. lower_bound / upper_bound 范围查询 ====================

void demo_range_queries() {
    cout << "========== 7. lower_bound / upper_bound 范围查询 ==========\n\n";

    set<int> s = {1, 3, 5, 7, 9, 11, 13, 15};
    cout << "  集合：";
    for (int x : s) cout << x << ' ';
    cout << "\n\n";

    // lower_bound(x)：第一个 ≥ x 的元素
    cout << "【lower_bound / upper_bound】\n";
    cout << "  lower_bound(5)  = " << *s.lower_bound(5) << "  (第一个 ≥ 5)\n";
    cout << "  lower_bound(6)  = " << *s.lower_bound(6) << "  (第一个 ≥ 6)\n";
    cout << "  upper_bound(5)  = " << *s.upper_bound(5) << "  (第一个 > 5)\n";
    cout << "  upper_bound(15) == end()? "
         << (s.upper_bound(15) == s.end() ? "true" : "false") << "\n\n";

    // equal_range(x)：返回 [lower_bound(x), upper_bound(x))
    cout << "【equal_range】\n";
    cout << "  equal_range(7) 区间内的元素：";
    auto [lo, hi] = s.equal_range(7);
    for (auto it = lo; it != hi; ++it) cout << *it << ' ';
    cout << "(仅一个元素)\n";

    // 范围查询：统计 [5, 11] 内的元素
    cout << "  [5, 11] 范围内的元素：";
    auto lo2 = s.lower_bound(5);
    auto hi2 = s.upper_bound(11);
    int cnt = 0;
    for (auto it = lo2; it != hi2; ++it) {
        cout << *it << ' ';
        cnt++;
    }
    cout << " → 共 " << cnt << " 个\n\n";

    // map 的范围查询
    cout << "【map 的范围查询】\n";
    map<int, string> mp = {
        {10, "A"}, {20, "B"}, {30, "C"}, {40, "D"}, {50, "E"}
    };
    cout << "  key 在 [25, 45] 范围内的元素：\n";
    auto mlo = mp.lower_bound(25);
    auto mhi = mp.upper_bound(45);
    for (auto it = mlo; it != mhi; ++it)
        cout << "    " << it->first << " -> " << it->second << '\n';
    cout << "\n";
}

// ==================== main ====================

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "╔══════════════════════════════════════════════════════╗\n";
    cout << "║  第04课：set/map 与 unordered 容器 — 演示程序    ║\n";
    cout << "╚══════════════════════════════════════════════════════╝\n";

    demo_set_custom_cmp();
    demo_map_custom_key();
    demo_unordered_map_custom_hash();
    demo_unordered_reserve();
    demo_performance_comparison();
    demo_multiset_multimap();
    demo_range_queries();

    cout << "══════════════════════════════════════════════════════\n";
    cout << "  演示完毕！\n";
    cout << "══════════════════════════════════════════════════════\n";

    return 0;
}
