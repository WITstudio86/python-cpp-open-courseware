/**
 * CSP-J 第23课：STL入门——vector与string
 * 完整演示程序
 * 编译：g++ -std=c++14 -o lesson23 lesson23_STL入门vector与string.cpp
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
using namespace std;

// ==================== 辅助函数 ====================
void printSection(const string& title) {
    cout << "\n" << string(60, '=') << endl;
    cout << "  " << title << endl;
    cout << string(60, '=') << endl;
}

void printSub(const string& title) {
    cout << "\n--- " << title << " ---" << endl;
}

// ==================== 主程序 ====================
int main() {
    // ==========================================
    // 第一部分：vector 的声明与初始化
    // ==========================================
    printSection("第一部分：vector 的声明与初始化");

    printSub("1.1 空vector");
    vector<int> v1;
    cout << "v1.size() = " << v1.size() << endl;
    cout << "v1.empty() = " << (v1.empty() ? "true" : "false") << endl;

    printSub("1.2 指定大小的vector");
    vector<int> v2(5);  // 5个int，默认都是0
    cout << "v2.size() = " << v2.size() << endl;
    cout << "v2内容: ";
    for (int x : v2) cout << x << " ";
    cout << endl;

    printSub("1.3 指定大小和初始值");
    vector<int> v3(5, 42);  // 5个int，都是42
    cout << "v3内容: ";
    for (int x : v3) cout << x << " ";
    cout << endl;

    printSub("1.4 列表初始化 (C++11)");
    vector<int> v4 = {10, 20, 30, 40, 50};
    cout << "v4内容: ";
    for (int x : v4) cout << x << " ";
    cout << endl;

    printSub("1.5 拷贝构造");
    vector<int> v5(v4);
    cout << "v5内容(拷贝自v4): ";
    for (int x : v5) cout << x << " ";
    cout << endl;

    // ==========================================
    // 第二部分：vector 常用操作
    // ==========================================
    printSection("第二部分：vector 常用操作");

    printSub("2.1 push_back() 添加元素");
    vector<int> v;
    for (int i = 1; i <= 5; i++) {
        v.push_back(i * 10);
        cout << "push_back(" << i * 10 << ") -> size = " << v.size() << endl;
    }
    cout << "最终内容: ";
    for (int x : v) cout << x << " ";
    cout << endl;

    printSub("2.2 pop_back() 删除末尾元素");
    cout << "弹出前: ";
    for (int x : v) cout << x << " ";
    cout << endl;
    v.pop_back();
    cout << "pop_back() 后: ";
    for (int x : v) cout << x << " ";
    cout << endl;
    cout << "size = " << v.size() << endl;

    printSub("2.3 front() 和 back()");
    cout << "当前vector: ";
    for (int x : v) cout << x << " ";
    cout << endl;
    cout << "front() = " << v.front() << endl;
    cout << "back()  = " << v.back() << endl;

    printSub("2.4 下标访问 v[i]");
    cout << "v[0] = " << v[0] << endl;
    cout << "v[1] = " << v[1] << endl;
    cout << "修改v[0] = 999" << endl;
    v[0] = 999;
    cout << "修改后: ";
    for (int x : v) cout << x << " ";
    cout << endl;

    printSub("2.5 at() 带边界检查的访问");
    cout << "v.at(0) = " << v.at(0) << endl;
    cout << "v.at(1) = " << v.at(1) << endl;
    // 以下代码会抛出 std::out_of_range 异常，演示时注释掉
    // cout << v.at(100) << endl;

    printSub("2.6 empty() 和 clear()");
    cout << "清空前 empty() = " << (v.empty() ? "true" : "false") << endl;
    cout << "清空前 size() = " << v.size() << endl;
    v.clear();
    cout << "clear() 后 empty() = " << (v.empty() ? "true" : "false") << endl;
    cout << "clear() 后 size() = " << v.size() << endl;

    // ==========================================
    // 第三部分：vector 遍历方式
    // ==========================================
    printSection("第三部分：vector 的三种遍历方式");

    vector<int> nums = {100, 200, 300, 400, 500};

    printSub("3.1 下标循环遍历");
    cout << "for (int i = 0; i < nums.size(); i++):" << endl;
    for (size_t i = 0; i < nums.size(); i++) {
        cout << "  nums[" << i << "] = " << nums[i] << endl;
    }

    printSub("3.2 迭代器遍历");
    cout << "使用 iterator: ";
    for (vector<int>::iterator it = nums.begin(); it != nums.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    printSub("3.3 范围for循环遍历 (C++11)");
    cout << "for (int x : nums): ";
    for (int x : nums) {
        cout << x << " ";
    }
    cout << endl;

    printSub("3.4 范围for + auto");
    cout << "for (auto x : nums): ";
    for (auto x : nums) {
        cout << x << " ";
    }
    cout << endl;

    // ==========================================
    // 第四部分：二维 vector
    // ==========================================
    printSection("第四部分：二维 vector（九九乘法表）");

    // 创建 9x9 的乘法表
    vector<vector<int>> table(9, vector<int>(9, 0));

    // 填充乘法表
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            table[i][j] = (i + 1) * (j + 1);
        }
    }

    // 输出乘法表
    cout << "  九九乘法表（二维vector）:" << endl;
    cout << "    ";
    for (int j = 1; j <= 9; j++) {
        printf("%4d", j);
    }
    cout << endl;
    cout << "    " << string(36, '-') << endl;
    for (int i = 0; i < 9; i++) {
        printf("%2d |", i + 1);
        for (int j = 0; j < 9; j++) {
            printf("%4d", table[i][j]);
        }
        cout << endl;
    }

    // ==========================================
    // 第五部分：vector 排序与去重
    // ==========================================
    printSection("第五部分：vector 排序与去重");

    vector<int> data = {5, 2, 8, 2, 9, 1, 5, 5, 3, 8};
    cout << "原始数据: ";
    for (int x : data) cout << x << " ";
    cout << endl;

    // 排序
    sort(data.begin(), data.end());
    cout << "sort() 后: ";
    for (int x : data) cout << x << " ";
    cout << endl;

    // 去重
    auto last = unique(data.begin(), data.end());
    data.erase(last, data.end());
    cout << "unique() + erase() 去重后: ";
    for (int x : data) cout << x << " ";
    cout << endl;
    cout << "去重后元素个数: " << data.size() << endl;

    // ==========================================
    // 第六部分：vector reserve 扩容性能
    // ==========================================
    printSection("第六部分：reserve() vs 无reserve()");

    vector<int> vNoReserve;
    cout << "无reserve初始: size=" << vNoReserve.size()
         << ", capacity=" << vNoReserve.capacity() << endl;
    for (int i = 0; i < 10; i++) {
        vNoReserve.push_back(i);
        cout << "  push_back(" << i << "): size=" << vNoReserve.size()
             << ", capacity=" << vNoReserve.capacity() << endl;
    }

    cout << endl;
    vector<int> vWithReserve;
    vWithReserve.reserve(10);
    cout << "reserve(10)后: size=" << vWithReserve.size()
         << ", capacity=" << vWithReserve.capacity() << endl;
    for (int i = 0; i < 10; i++) {
        vWithReserve.push_back(i);
        cout << "  push_back(" << i << "): size=" << vWithReserve.size()
             << ", capacity=" << vWithReserve.capacity() << endl;
    }

    // ==========================================
    // 第七部分：string 基础操作
    // ==========================================
    printSection("第七部分：string 基础与高级操作");

    printSub("7.1 getline() 演示");
    cout << "请输入一行文字（含空格）进行测试：" << endl;
    // 由于是演示程序，这里使用硬编码示例演示 getline 逻辑
    string sampleInput = "CSP-J 2025 备赛";
    cout << "  模拟输入: \"" << sampleInput << "\"" << endl;
    cout << "  getline读取结果: " << sampleInput << endl;

    printSub("7.2 cin >> 后使用 getline 的正确写法");
    cout << "  如果程序中有 cin >> n; 之后要用 getline，必须加 cin.ignore();" << endl;
    cout << "  否则 getline 会读到残留的换行符。" << endl;
    cout << "  示例代码: int n; cin >> n; cin.ignore(); string s; getline(cin, s);" << endl;

    printSub("7.3 find() 查找子串");
    string s = "CSP-J 竞赛真好，CSP-J 加油！";
    cout << "原始字符串: \"" << s << "\"" << endl;

    size_t pos = s.find("CSP-J");
    cout << "find(\"CSP-J\") = " << pos << " (第一个出现位置)" << endl;

    pos = s.find("CSP-J", 10);  // 从下标10开始找
    cout << "find(\"CSP-J\", 10) = " << pos << " (从下标10开始找)" << endl;

    pos = s.find("NOIP");
    if (pos == string::npos) {
        cout << "find(\"NOIP\") = string::npos (没找到)" << endl;
    }

    printSub("7.4 substr() 截取子串");
    string text = "0123456789";
    cout << "原始字符串: \"" << text << "\"" << endl;
    cout << "substr(0, 3)  = \"" << text.substr(0, 3) << "\"" << endl;
    cout << "substr(3, 4)  = \"" << text.substr(3, 4) << "\"" << endl;
    cout << "substr(5)     = \"" << text.substr(5) << "\" (到末尾)" << endl;
    cout << "substr(7, 10) = \"" << text.substr(7, 10) << "\" (len超过也不会报错)" << endl;

    printSub("7.5 insert() 和 erase()");
    string msg = "Hello World";
    cout << "原始: \"" << msg << "\"" << endl;
    msg.insert(5, " beautiful");
    cout << "insert(5, \" beautiful\") -> \"" << msg << "\"" << endl;
    msg.erase(5, 10);
    cout << "erase(5, 10) -> \"" << msg << "\"" << endl;

    string t = "abcdefg";
    cout << "t = \"" << t << "\"" << endl;
    t.erase(2, 3);
    cout << "erase(2, 3) -> \"" << t << "\" (删掉了cde)" << endl;

    printSub("7.6 length() 和 size()");
    string str = "CSP-J";
    cout << "\"" << str << "\".length() = " << str.length() << endl;
    cout << "\"" << str << "\".size()   = " << str.size() << endl;
    cout << "(length() 和 size() 完全等价)" << endl;

    printSub("7.7 字符串比较");
    string a = "abc", b = "abd", c = "abc";
    cout << "\"abc\" == \"abc\": " << (a == c ? "true" : "false") << endl;
    cout << "\"abc\" <  \"abd\": " << (a < b ? "true" : "false") << endl;
    cout << "\"abc\" >  \"abd\": " << (a > b ? "true" : "false") << endl;
    cout << "字符串比较按字典序(lexicographical order)" << endl;

    printSub("7.8 to_string / stoi 数字与字符串互转");
    int num = 123;
    string numStr = to_string(num);
    cout << "to_string(123) -> \"" << numStr << "\"" << endl;
    cout << "to_string(3.14) -> \"" << to_string(3.14) << "\"" << endl;

    string numStr2 = "456";
    int parsed = stoi(numStr2);
    cout << "stoi(\"456\") -> " << parsed << endl;
    cout << "stoi(\"456\") + 100 = " << parsed + 100 << endl;

    // ==========================================
    // 第八部分：字符串分割（CSV风格）
    // ==========================================
    printSection("第八部分：字符串分割演示");

    string csv = "张三,15,数学,95,A";
    cout << "CSV字符串: \"" << csv << "\"" << endl;
    cout << "分割结果:" << endl;

    vector<string> fields;
    size_t splitPos = 0;
    while ((splitPos = csv.find(',')) != string::npos) {
        fields.push_back(csv.substr(0, splitPos));
        csv.erase(0, splitPos + 1);
    }
    fields.push_back(csv);  // 最后一段

    for (size_t i = 0; i < fields.size(); i++) {
        cout << "  字段[" << i << "]: \"" << fields[i] << "\"" << endl;
    }

    // 方式二：不用erase的分割
    printSub("方式二：维护起始位置的分割");
    string csv2 = "apple,banana,cherry,date";
    cout << "CSV字符串: \"" << csv2 << "\"" << endl;

    vector<string> fields2;
    size_t start = 0, end;
    while ((end = csv2.find(',', start)) != string::npos) {
        fields2.push_back(csv2.substr(start, end - start));
        start = end + 1;
    }
    fields2.push_back(csv2.substr(start));

    for (size_t i = 0; i < fields2.size(); i++) {
        cout << "  字段[" << i << "]: \"" << fields2[i] << "\"" << endl;
    }

    // ==========================================
    // 第九部分：auto 关键字演示
    // ==========================================
    printSection("第九部分：auto 关键字演示");

    printSub("9.1 基本类型推导");
    auto i = 42;          // int
    auto d = 3.14;        // double
    auto c = 'A';         // char
    auto str = "hello";   // const char*

    cout << "auto i = 42;     -> int    (值: " << i << ")" << endl;
    cout << "auto d = 3.14;   -> double (值: " << d << ")" << endl;
    cout << "auto c = 'A';    -> char   (值: " << c << ")" << endl;
    cout << "auto str = \"hello\"; -> const char* (值: " << str << ")" << endl;

    printSub("9.2 迭代器类型推导");
    vector<int> vv = {10, 20, 30, 40, 50};
    auto it = vv.begin();  // vector<int>::iterator
    cout << "auto it = vv.begin(); -> vector<int>::iterator" << endl;
    cout << "*it = " << *it << endl;
    cout << "遍历: ";
    for (auto it = vv.begin(); it != vv.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    printSub("9.3 复杂类型推导");
    vector<vector<int>> matrix(3, vector<int>(3));
    auto row = matrix[0];  // vector<int>
    cout << "auto row = matrix[0]; -> vector<int> (size=" << row.size() << ")" << endl;

    // ==========================================
    // 第十部分：范围for循环详细演示
    // ==========================================
    printSection("第十部分：范围for循环 (Range-based for)");

    vector<int> scores = {85, 92, 78, 95, 88};

    printSub("10.1 只读遍历 (auto x : v)");
    cout << "原始成绩: ";
    for (auto x : scores) {
        cout << x << " ";
    }
    cout << endl;

    printSub("10.2 修改元素 (auto& x : v)");
    cout << "每人加5分..." << endl;
    for (auto& x : scores) {
        x += 5;  // 注意：auto& 才能修改原元素
    }
    cout << "加分后: ";
    for (const auto& x : scores) {
        cout << x << " ";
    }
    cout << endl;

    printSub("10.3 验证 auto 不会修改原值");
    vector<int> testV = {1, 2, 3};
    cout << "auto x 遍历前: ";
    for (int x : testV) cout << x << " ";
    cout << endl;
    for (auto x : testV) {
        x = 999;  // 修改的是拷贝，不影响原vector
    }
    cout << "auto x 遍历后: ";
    for (int x : testV) cout << x << " ";
    cout << " (不变! 因为是拷贝)" << endl;

    printSub("10.4 string 范围for遍历");
    string word = "CSP-J";
    cout << "遍历\"" << word << "\": ";
    for (auto ch : word) {
        cout << ch << " ";
    }
    cout << endl;

    printSub("10.5 const auto& 避免拷贝");
    vector<string> names = {"张三", "李四", "王五", "赵六"};
    cout << "学生名单 (const auto&): ";
    for (const auto& name : names) {
        cout << name << " ";
    }
    cout << endl;

    // ==========================================
    // 第十一部分：综合应用 - 去重排序完整示例
    // ==========================================
    printSection("第十一部分：综合应用 - 去重排序");

    vector<int> raw = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    cout << "原始数据: ";
    for (int x : raw) cout << x << " ";
    cout << endl;

    sort(raw.begin(), raw.end());
    cout << "排序后: ";
    for (int x : raw) cout << x << " ";
    cout << endl;

    auto uniqueEnd = unique(raw.begin(), raw.end());
    cout << "unique后逻辑大小: " << (uniqueEnd - raw.begin()) << endl;
    cout << "unique后物理大小: " << raw.size() << endl;
    cout << "unique后容器内容: ";
    for (int x : raw) cout << x << " ";
    cout << " (注意尾部有残留)" << endl;

    raw.erase(uniqueEnd, raw.end());
    cout << "erase后: ";
    for (int x : raw) cout << x << " ";
    cout << endl;
    cout << "最终大小: " << raw.size() << endl;

    // ==========================================
    // 第十二部分：迭代器高级用法
    // ==========================================
    printSection("第十二部分：迭代器高级用法");

    vector<int> iv = {10, 20, 30, 40, 50};
    cout << "原始: ";
    for (int x : iv) cout << x << " ";
    cout << endl;

    // insert
    iv.insert(iv.begin() + 2, 25);
    cout << "insert(begin()+2, 25): ";
    for (int x : iv) cout << x << " ";
    cout << endl;

    // erase by iterator
    iv.erase(iv.begin() + 1);
    cout << "erase(begin()+1): ";
    for (int x : iv) cout << x << " ";
    cout << endl;

    // reverse
    reverse(iv.begin(), iv.end());
    cout << "reverse(): ";
    for (int x : iv) cout << x << " ";
    cout << endl;

    // find
    auto found = find(iv.begin(), iv.end(), 30);
    if (found != iv.end()) {
        cout << "find(30): 找到了，位置索引 = " << (found - iv.begin()) << endl;
    } else {
        cout << "find(30): 没找到" << endl;
    }

    // ==========================================
    // 第十三部分：cin.ignore 陷阱演示说明
    // ==========================================
    printSection("第十三部分：cin >> 与 getline 混用陷阱");

    cout << "【陷阱演示】" << endl;
    cout << "以下代码模拟 cin >> n 之后直接 getline:" << endl;
    cout << "  int n;" << endl;
    cout << "  cin >> n;           // 用户输入 42<回车>" << endl;
    cout << "  string s;" << endl;
    cout << "  getline(cin, s);    // s = \"\" (读到的是残留的换行符!)" << endl;
    cout << "" << endl;
    cout << "【正确做法】" << endl;
    cout << "  int n;" << endl;
    cout << "  cin >> n;" << endl;
    cout << "  cin.ignore();       // 吃掉残留的换行符" << endl;
    cout << "  string s;" << endl;
    cout << "  getline(cin, s);    // s 现在正确读到下一行内容" << endl;

    // ==========================================
    // 总结
    // ==========================================
    printSection("演示程序结束");

    cout << "\n本程序覆盖了CSP-J第23课所有核心知识点：" << endl;
    cout << "  [1] vector声明与初始化（多种方式）" << endl;
    cout << "  [2] vector常用操作（push_back/pop_back/size/clear/empty/front/back）" << endl;
    cout << "  [3] vector三种遍历方式（下标/迭代器/范围for）" << endl;
    cout << "  [4] 二维vector（乘法表示例）" << endl;
    cout << "  [5] sort排序与unique去重" << endl;
    cout << "  [6] reserve容量管理" << endl;
    cout << "  [7] string高级操作（find/substr/insert/erase/length）" << endl;
    cout << "  [8] 字符串分割（CSV解析）" << endl;
    cout << "  [9] auto关键字（类型推导、迭代器简化）" << endl;
    cout << "  [10] 范围for循环（auto/auto&/const auto&）" << endl;
    cout << "  [11] 迭代器高级用法（insert/erase/find/reverse）" << endl;
    cout << "  [12] cin.ignore陷阱说明" << endl;
    cout << endl;

    return 0;
}
