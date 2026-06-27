/**
 * ============================================================
 * 课程编号：第03课
 * 课程标题：vector 与 string 高级用法
 * 对应考纲：vector内存管理、string高阶操作、stringstream、迭代器失效
 *
 * 本程序演示：
 *   1. vector 内存管理（reserve/resize/capacity/shrink_to_fit）
 *   2. vector 扩容过程的可视化
 *   3. string 高阶用法（find/rfind/substr/split）
 *   4. stringstream 类型转换与字符串分割
 *   5. 迭代器失效演示与修复方法
 *   6. emplace_back vs push_back 性能对比
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

// ==================== 1. vector 内存管理演示 ====================

void demo_vector_memory() {
    cout << "\n========== 1. vector 内存管理演示 ==========\n\n";

    vector<int> v;

    // 观察默认状态
    cout << "【初始状态】\n";
    cout << "  size     = " << v.size() << "\n";
    cout << "  capacity = " << v.capacity() << "\n\n";

    // reserve 预分配：只改变 capacity，不改变 size
    cout << "【reserve(10) 之后】\n";
    v.reserve(10);
    cout << "  size     = " << v.size() << "\n";
    cout << "  capacity = " << v.capacity() << "\n\n";

    // resize 改变 size：新元素用默认值填充
    cout << "【resize(5) 之后】\n";
    v.resize(5);
    cout << "  size     = " << v.size() << "\n";
    cout << "  capacity = " << v.capacity() << "\n";
    cout << "  元素内容：";
    for (int x : v) cout << x << ' ';
    cout << "\n\n";

    // resize 增大且指定填充值
    cout << "【resize(8, 42) 之后】\n";
    v.resize(8, 42);
    cout << "  size     = " << v.size() << "\n";
    cout << "  capacity = " << v.capacity() << "\n";
    cout << "  元素内容：";
    for (int x : v) cout << x << ' ';
    cout << "\n\n";

    // clear 只清空元素，不释放内存
    cout << "【clear() 之后】\n";
    v.clear();
    cout << "  size     = " << v.size() << "\n";
    cout << "  capacity = " << v.capacity() << "  ← capacity 不变！\n\n";

    // shrink_to_fit 请求缩减容量
    cout << "【shrink_to_fit() 之后】\n";
    v.shrink_to_fit();
    cout << "  size     = " << v.size() << "\n";
    cout << "  capacity = " << v.capacity() << "\n\n";

    // 100% 保证释放内存的方法：swap 技巧
    cout << "【swap 技巧释放内存】\n";
    vector<int> v2;
    v2.reserve(100);
    cout << "  释放前 capacity = " << v2.capacity() << "\n";
    vector<int>().swap(v2);   // 与临时空 vector 交换
    cout << "  释放后 capacity = " << v2.capacity() << "\n\n";
}

// ==================== 2. vector 扩容过程可视化 ====================

void demo_vector_growth() {
    cout << "========== 2. vector 扩容过程可视化 ==========\n\n";

    // 不 reserve，观察扩容
    cout << "【无 reserve 的扩容过程】\n";
    {
        vector<int> v;
        cout << "  初始 capacity = " << v.capacity() << "\n";
        int last_cap = v.capacity();
        for (int i = 0; i < 10; i++) {
            v.push_back(i);
            if ((int)v.capacity() != last_cap) {
                cout << "  插入第 " << i << " 个元素后扩容："
                     << last_cap << " → " << v.capacity() << "\n";
                last_cap = v.capacity();
            }
        }
        cout << "  最终 size=" << v.size() << ", capacity=" << v.capacity() << "\n";
        // 扩容因子 ≈ 2（GCC libstdc++）
    }

    cout << "\n【有 reserve 的无扩容过程】\n";
    {
        vector<int> v;
        v.reserve(10);  // 一次性预分配
        cout << "  reserve(10) 后 capacity = " << v.capacity() << "\n";
        int last_cap = v.capacity();
        for (int i = 0; i < 10; i++) {
            v.push_back(i);
            if ((int)v.capacity() != last_cap) {
                cout << "  扩容发生! " << last_cap << " → " << v.capacity() << "\n";
                last_cap = v.capacity();
            }
        }
        if (last_cap == (int)v.capacity())
            cout << "  全程无扩容！capacity 保持 " << v.capacity() << "\n";
    }
    cout << "\n";
}

// ==================== 3. string 高阶用法 ====================

void demo_string_advanced() {
    cout << "========== 3. string 高阶用法 ==========\n\n";

    string s = "hello world, hello cpp, world of cpp";

    // find：从左向右查找子串
    cout << "【find 系列】\n";
    size_t pos = s.find("hello");
    cout << "  s.find(\"hello\")     = " << pos << "\n";

    pos = s.find("hello", 5);        // 从索引 5 开始
    cout << "  s.find(\"hello\", 5)  = " << pos << "\n";

    pos = s.find("python");          // 不存在
    cout << "  s.find(\"python\")    = " << pos << " (npos=" << string::npos << ")\n";
    if (pos == string::npos)
        cout << "    → 未找到，返回 string::npos\n\n";

    // rfind：从右向左查找
    cout << "【rfind 系列】\n";
    pos = s.rfind("hello");
    cout << "  s.rfind(\"hello\")    = " << pos << "\n";
    pos = s.rfind("world");
    cout << "  s.rfind(\"world\")    = " << pos << "\n\n";

    // find_first_of / find_last_of
    cout << "【find_first_of / find_last_of】\n";
    pos = s.find_first_of("aeiou");   // 第一个元音字母
    cout << "  第一个元音的位置 = " << pos << " ('" << s[pos] << "')\n";
    pos = s.find_last_of("aeiou");
    cout << "  最后一个元音的位置 = " << pos << " ('" << s[pos] << "')\n\n";

    // find_first_not_of
    cout << "【find_first_not_of】\n";
    pos = s.find_first_not_of("helo ");  // 第一个不在集合中的字符
    cout << "  跳过'helo '后第一个字符位置 = " << pos << " ('" << s[pos] << "')\n\n";

    // substr
    cout << "【substr 用法】\n";
    cout << "  s.substr(6)      = \"" << s.substr(6) << "\"\n";
    cout << "  s.substr(6, 5)   = \"" << s.substr(6, 5) << "\"\n";
    cout << "  s.substr(0, 5)   = \"" << s.substr(0, 5) << "\"\n\n";

    // compare
    cout << "【compare 比较】\n";
    string a = "apple", b = "banana";
    cout << "  \"apple\".compare(\"banana\") = " << a.compare(b) << " (<0 表示 a<b)\n";
    cout << "  a.compare(0, 3, b, 0, 3) = " << a.compare(0, 3, b, 0, 3)
         << " (\"app\" vs \"ban\")  ← 只比较子串！\n\n";
}

// ==================== 4. stringstream 类型转换 ====================

// 任意类型 → 字符串
template<typename T>
string tos(const T& val) {
    ostringstream oss;
    oss << val;
    return oss.str();
}

// 字符串 → 任意类型
template<typename T>
T sto(const string& s) {
    T val;
    istringstream(s) >> val;
    return val;
}

void demo_stringstream() {
    cout << "========== 4. stringstream 类型转换与分割 ==========\n\n";

    // 4.1 类型转换
    cout << "【类型转换】\n";
    string s1 = tos(42);
    cout << "  int → string : " << s1 << "\n";
    string s2 = tos(3.14159);
    cout << "  double → string : " << s2 << "\n";
    string s3 = tos(string("hello"));
    cout << "  string → string : " << s3 << "\n";

    int n = sto<int>("12345");
    cout << "  string → int : " << n << "\n";
    double d = sto<double>("3.14159");
    cout << "  string → double : " << d << "\n\n";

    // 4.2 格式化输入
    cout << "【格式化输入解析】\n";
    string input = "Alice 18 95.5";
    istringstream iss(input);
    string name; int age; double score;
    iss >> name >> age >> score;
    cout << "  解析 \"" << input << "\" → 姓名=" << name
         << ", 年龄=" << age << ", 分数=" << score << "\n\n";

    // 4.3 字符串分割
    cout << "【字符串分割】\n";
    string csv = "one,two,three,four,five";
    stringstream ss(csv);
    string item;
    int idx = 0;
    cout << "  原始字符串：\"" << csv << "\"\n  分割结果：\n";
    while (getline(ss, item, ',')) {
        cout << "    [" << idx++ << "] " << item << "\n";
    }
    cout << "\n";

    // 4.4 格式化输出
    cout << "【格式化输出】\n";
    ostringstream oss;
    oss << fixed << setprecision(3) << 3.1415926535;
    cout << "  π ≈ " << oss.str() << "\n\n";
}

// ==================== 5. 迭代器失效演示与修复 ====================

void demo_iterator_invalidation() {
    cout << "========== 5. 迭代器失效演示与修复 ==========\n\n";

    // 5.1 erase 导致迭代器失效 — 错误写法
    cout << "【场景1：erase 导致迭代器失效】\n";
    {
        vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        cout << "  原始数组：";
        for (int x : v) cout << x << ' ';
        cout << "\n";

        // ✅ 正确写法：使用 erase 返回值
        cout << "  ✅ 正确：删除所有偶数\n  ";
        for (auto it = v.begin(); it != v.end(); ) {
            if (*it % 2 == 0)
                it = v.erase(it);   // erase 返回下一个有效迭代器
            else
                ++it;
        }
        cout << "  剩余元素：";
        for (int x : v) cout << x << ' ';
        cout << "\n\n";
    }

    // 5.2 erase-remove 惯用法
    cout << "【场景2：erase-remove 惯用法】\n";
    {
        vector<int> v = {5, 2, 8, 1, 9, 3, 7, 4, 6};
        cout << "  原始数组：";
        for (int x : v) cout << x << ' ';
        cout << "\n";

        // 删除所有 > 5 的元素
        v.erase(remove_if(v.begin(), v.end(),
                [](int x) { return x > 5; }),
                v.end());
        cout << "  删除 >5 后：";
        for (int x : v) cout << x << ' ';
        cout << "\n\n";
    }

    // 5.3 insert 导致迭代器失效
    cout << "【场景3：insert 返回值修复】\n";
    {
        vector<int> v = {1, 2, 3};
        cout << "  原始数组：";
        for (int x : v) cout << x << ' ';
        cout << "\n";

        // 在 2 前面插入 0
        auto it = find(v.begin(), v.end(), 2);
        if (it != v.end()) {
            it = v.insert(it, 0);  // insert 返回指向新插入元素的迭代器
            // it 现在指向 0
            cout << "  在2前插入0：";
            for (int x : v) cout << x << ' ';
            cout << "  (insert 返回迭代器指向: " << *it << ")\n";
        }
        cout << "\n";
    }

    // 5.4 push_back 触发扩容导致迭代器失效
    cout << "【场景4：push_back 扩容导致迭代器失效】\n";
    {
        vector<int> v;
        v.reserve(3);  // 确保后面 push_back 会扩容
        v = {1, 2, 3};

        auto it = v.begin();  // 保存迭代器
        cout << "  初态：*it = " << *it << ", capacity = " << v.capacity() << "\n";

        v.reserve(100);  // 触发重新分配！
        // it 已失效！不能解引用！
        auto new_it = v.begin();  // 重新获取
        cout << "  reserve(100) 后必须重新获取迭代器\n";
        cout << "  新迭代器 *new_it = " << *new_it << "\n\n";
    }
}

// ==================== 6. emplace_back vs push_back 性能对比 ====================

struct HeavyObject {
    int id;
    string name;
    vector<int> data;

    HeavyObject(int i, string n) : id(i), name(move(n)) {
        data.resize(100, i);  // 模拟"重量级"对象
    }

    // 拷贝构造（统计拷贝次数）
    HeavyObject(const HeavyObject& other)
        : id(other.id), name(other.name), data(other.data) {
        // 耗时操作
    }

    HeavyObject(HeavyObject&&) = default;
    HeavyObject& operator=(const HeavyObject&) = default;
    HeavyObject& operator=(HeavyObject&&) = default;
};

void demo_emplace_vs_push() {
    cout << "========== 6. emplace_back vs push_back ==========\n\n";

    cout << "【概念说明】\n";
    cout << "  push_back:   先构造对象 → 再拷贝/移动到 vector\n";
    cout << "  emplace_back: 直接在 vector 内部原地构造，零临时对象\n\n";

    const int N = 100000;

    // 测试 push_back
    {
        vector<pair<int, string>> v;
        v.reserve(N);
        auto start = high_resolution_clock::now();
        for (int i = 0; i < N; i++) {
            v.push_back(make_pair(i, "hello world"));
        }
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start).count();
        cout << "  push_back(make_pair(...)) : " << duration << " μs\n";
    }

    // 测试 emplace_back
    {
        vector<pair<int, string>> v;
        v.reserve(N);
        auto start = high_resolution_clock::now();
        for (int i = 0; i < N; i++) {
            v.emplace_back(i, "hello world");
        }
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start).count();
        cout << "  emplace_back(i, ...)      : " << duration << " μs\n";
    }
    cout << "  → emplace_back 避免了 pair 的临时对象构造，性能更优\n";

    // 不 reserve 的情况
    cout << "\n【无 reserve 时的差异更大】\n";
    {
        vector<pair<int, string>> v;
        auto start = high_resolution_clock::now();
        for (int i = 0; i < 10000; i++) {
            v.push_back(make_pair(i, "test"));
        }
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start).count();
        cout << "  push_back(无reserve) : " << duration << " μs\n";
    }
    {
        vector<pair<int, string>> v;
        auto start = high_resolution_clock::now();
        for (int i = 0; i < 10000; i++) {
            v.emplace_back(i, "test");
        }
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start).count();
        cout << "  emplace_back(无reserve) : " << duration << " μs\n";
    }
    cout << "  → 无 reserve 时扩容也会占主导，但 emplace 仍优于 push\n\n";
}

// ==================== 7. 综合示例：split 函数实现 ====================

vector<string> split(const string& s, char delim = ' ') {
    vector<string> tokens;
    stringstream ss(s);
    string token;
    while (getline(ss, token, delim))
        if (!token.empty())
            tokens.push_back(move(token));
    return tokens;
}

void demo_split_comprehensive() {
    cout << "========== 7. 综合示例：split 函数 ==========\n\n";

    string s = "  apple  banana   cherry  ";
    cout << "  原始：\"" << s << "\"\n";

    auto tokens = split(s, ' ');
    cout << "  分割结果(" << tokens.size() << "个): ";
    for (const auto& t : tokens) cout << "\"" << t << "\" ";
    cout << "\n";
}

// ==================== main ====================

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "╔══════════════════════════════════════════════════╗\n";
    cout << "║  第03课：vector 与 string 高级用法 — 演示程序  ║\n";
    cout << "╚══════════════════════════════════════════════════╝\n";

    demo_vector_memory();
    demo_vector_growth();
    demo_string_advanced();
    demo_stringstream();
    demo_iterator_invalidation();
    demo_emplace_vs_push();
    demo_split_comprehensive();

    return 0;
}
