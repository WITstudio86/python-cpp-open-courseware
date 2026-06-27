/*
 * Lesson 31: STL sort 与自定义排序
 *
 * 本课内容：
 * 1. sort() 默认升序排序
 * 2. sort() + greater<int>() 降序排序
 * 3. sort() + 自定义 cmp 函数（绝对值降序、奇偶分组等复杂排序规则）
 * 4. 结构体多关键字排序（学生按成绩降序、成绩相同按学号升序、都相同按姓名升序）
 * 5. stable_sort() 稳定排序的用法与意义
 *
 * 头文件：#include <algorithm>
 *
 * sort() 语法：
 *   sort(begin, end)            // 默认升序
 *   sort(begin, end, greater<T>())  // 降序
 *   sort(begin, end, cmp)       // 自定义比较函数
 *
 * stable_sort() 语法：
 *   stable_sort(begin, end, cmp) // 稳定排序，保持相等元素的相对顺序
 *
 * 时间复杂度：
 * - sort()：O(n log n)
 * - stable_sort()：O(n log n) ~ O(n log² n)（视实现而定）
 *
 * 重要知识点：
 * - sort() 是快速排序的变体（内省排序 introsort），不是稳定的
 * - stable_sort() 通常是归并排序，保证稳定性
 * - 自定义比较函数必须满足"严格弱序"（strict weak ordering）
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <cmath>
#include <iomanip>

using namespace std;

// ==================== 数据结构定义 ====================

/**
 * 学生结构体：用于多关键字排序演示
 */
struct Student {
    string name;   // 姓名
    int id;        // 学号
    int score;     // 成绩

    Student() : name(""), id(0), score(0) {}
    Student(string n, int i, int s) : name(n), id(i), score(s) {}
};

/**
 * 用于稳定排序演示的结构体
 * value 是排序依据，seq 记录原始输入顺序
 */
struct StableItem {
    int value;
    int seq;       // 原始输入顺序
    string label;

    StableItem() : value(0), seq(0), label("") {}
    StableItem(int v, int s, string l) : value(v), seq(s), label(l) {}
};

// ==================== 自定义比较函数 ====================

/**
 * 比较函数1：按绝对值降序排列
 * 规则：绝对值大的排在前面，如果绝对值相同，则数值大的排在前面
 *
 * 比较函数的要求（严格弱序）：
 * 1. 非自反性：cmp(x, x) 必须返回 false
 * 2. 非对称性：如果 cmp(a, b) 为 true，则 cmp(b, a) 必须为 false
 * 3. 传递性：如果 cmp(a, b) 和 cmp(b, c) 都为 true，则 cmp(a, c) 也为 true
 */
bool cmpAbsDesc(int a, int b) {
    // 先按绝对值降序比较
    if (abs(a) != abs(b)) {
        return abs(a) > abs(b);  // 绝对值大的在前
    }
    // 绝对值相同时，按原值升序（数值小的在前）
    return a < b;
}

/**
 * 比较函数2：奇偶分组排序
 * 规则：所有奇数排在前面，所有偶数排在后面
 *       奇数之间按升序排列，偶数之间按降序排列
 */
bool cmpOddEven(int a, int b) {
    bool aOdd = (a % 2 != 0);
    bool bOdd = (b % 2 != 0);

    // 如果奇偶性不同，奇数优先级更高（排在前面）
    if (aOdd != bOdd) {
        return aOdd;  // a 是奇数 → a 排在 b 前面
    }

    // 如果奇偶性相同
    if (aOdd) {
        // 都是奇数：按升序排列
        return a < b;
    } else {
        // 都是偶数：按降序排列
        return a > b;
    }
}

/**
 * 比较函数3：学生多关键字排序
 *
 * 需求：
 * - 第一关键字：成绩（降序）— 成绩高的排在前面
 * - 第二关键字：学号（升序）— 成绩相同时，学号小的排在前面
 * - 第三关键字：姓名（升序，按字典序）— 成绩和学号都相同时，姓名按字母顺序排列
 *
 * 思考方式：
 *   cmp(a, b) 返回 true 表示"a 应该排在 b 前面"
 *   所以当多个判断条件存在时，按重要性从高到低依次判断
 */
bool cmpStudent(const Student& a, const Student& b) {
    // 第一关键字：成绩降序
    if (a.score != b.score) {
        return a.score > b.score;  // a 成绩更高 → a 排在前面
    }

    // 第二关键字：学号升序
    if (a.id != b.id) {
        return a.id < b.id;  // a 学号更小 → a 排在前面
    }

    // 第三关键字：姓名升序（字典序）
    return a.name < b.name;
}

// ==================== 打印函数 ====================

/**
 * 打印整数数组
 */
void printArray(int a[], int n, const string& title) {
    cout << title << ": [";
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << ", ";
        cout << a[i];
    }
    cout << "]" << endl;
}

/**
 * 打印 vector<int>
 */
void printVector(const vector<int>& v, const string& title) {
    cout << title << ": [";
    for (size_t i = 0; i < v.size(); i++) {
        if (i > 0) cout << ", ";
        cout << v[i];
    }
    cout << "]" << endl;
}

/**
 * 打印学生数组
 */
void printStudents(const Student arr[], int n, const string& title) {
    cout << title << ":" << endl;
    cout << "  " << setw(6) << left << "学号"
         << setw(10) << left << "姓名"
         << setw(6) << "成绩" << endl;
    cout << "  " << string(22, '-') << endl;
    for (int i = 0; i < n; i++) {
        cout << "  " << setw(6) << left << arr[i].id
             << setw(10) << left << arr[i].name
             << setw(6) << arr[i].score << endl;
    }
}

/**
 * 打印稳定排序项
 */
void printStableItems(const StableItem arr[], int n, const string& title) {
    cout << title << ":" << endl;
    cout << "  " << setw(6) << "value" << setw(6) << "seq" << setw(15) << "label" << endl;
    cout << "  " << string(27, '-') << endl;
    for (int i = 0; i < n; i++) {
        cout << "  " << setw(6) << arr[i].value
             << setw(6) << arr[i].seq
             << setw(15) << arr[i].label << endl;
    }
}

// ==================== 主函数 ====================

int main() {
    cout << "============================================" << endl;
    cout << "  Lesson 31: STL sort 与自定义排序" << endl;
    cout << "============================================" << endl;
    cout << endl;

    // ---------- 1. sort() 默认升序排序 ----------
    cout << "---------- 1. sort() 默认升序排序 ----------" << endl;
    {
        int arr[] = {5, 2, 9, 1, 5, 6, 3, 8, 7, 4};
        int n = sizeof(arr) / sizeof(arr[0]);

        printArray(arr, n, "原始数组");

        // sort(begin, end) 对 [begin, end) 范围内的元素进行升序排序
        // begin = arr（首元素指针），end = arr + n（尾后指针）
        sort(arr, arr + n);

        printArray(arr, n, "sort() 升序结果");

        cout << endl << "语法说明：" << endl;
        cout << "  sort(arr, arr + n);" << endl;
        cout << "  - arr: 指向第一个元素的指针（迭代器）" << endl;
        cout << "  - arr + n: 指向最后一个元素的下一个位置（尾后迭代器）" << endl;
        cout << "  - 范围是左闭右开 [arr, arr+n)" << endl;
    }
    cout << endl;

    // ---------- 2. sort() + greater<int>() 降序排序 ----------
    cout << "---------- 2. sort() + greater<int>() 降序排序 ----------" << endl;
    {
        int arr[] = {5, 2, 9, 1, 5, 6, 3, 8, 7, 4};
        int n = sizeof(arr) / sizeof(arr[0]);

        printArray(arr, n, "原始数组");

        // greater<int>() 是一个函数对象，它调用 > 运算符进行比较
        // sort 根据 greater<int>() 的返回值来判断元素顺序
        // 如果 greater<int>()(a, b) 返回 true，即 a > b 时，
        // sort 认为 a 应该排在 b 前面，从而实现降序
        sort(arr, arr + n, greater<int>());

        printArray(arr, n, "sort() + greater<int>() 降序结果");

        cout << endl << "语法说明：" << endl;
        cout << "  sort(arr, arr + n, greater<int>());" << endl;
        cout << "  - greater<int>() 是一个函数对象，实现 a > b 的比较" << endl;
        cout << "  - 等价于自写比较函数: bool cmp(int a, int b) { return a > b; }" << endl;
        cout << "  - 也可使用 less<int>() 显式指定升序（此为默认行为）" << endl;
    }
    cout << endl;

    // ---------- 3. sort() + 自定义 cmp 函数 ----------
    cout << "---------- 3. sort() + 自定义 cmp 函数 ----------" << endl;

    // 3a. 按绝对值降序排序
    cout << "--- 3a. 按绝对值降序排列 ---" << endl;
    {
        int arr[] = {-5, 3, -8, 2, -1, 7, -4, 6, -9, 0};
        int n = sizeof(arr) / sizeof(arr[0]);

        printArray(arr, n, "原始数组");

        // 传入自定义比较函数 cmpAbsDesc
        // 注意：传入的是函数名（函数指针），不是函数调用
        sort(arr, arr + n, cmpAbsDesc);

        printArray(arr, n, "按绝对值降序排列后");
        cout << "规则：绝对值大的在前；绝对值相同时，数值小的在前" << endl;
    }

    cout << endl;

    // 3b. 奇偶分组排序
    cout << "--- 3b. 奇偶分组排序 ---" << endl;
    {
        int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
        int n = sizeof(arr) / sizeof(arr[0]);

        printArray(arr, n, "原始数组");

        sort(arr, arr + n, cmpOddEven);

        printArray(arr, n, "奇偶分组排序后");
        cout << "规则：奇数全部在前（升序），偶数全部在后（降序）" << endl;

        // 验证是否满足规则
        cout << "验证：";
        bool valid = true;
        bool seenEven = false;
        for (int i = 0; i < n; i++) {
            if (arr[i] % 2 == 0) seenEven = true;
            if (seenEven && arr[i] % 2 != 0) valid = false;  // 偶数后面不应有奇数
        }
        cout << (valid ? "通过" : "失败") << " — 所有奇数都在偶数前面" << endl;
    }
    cout << endl;

    // ---------- 4. 结构体多关键字排序 ----------
    cout << "---------- 4. 结构体多关键字排序（学生成绩排名） ----------" << endl;
    {
        Student students[] = {
            Student("张三",    1001, 92),
            Student("李四",    1002, 87),
            Student("王五",    1003, 92),
            Student("赵六",    1004, 76),
            Student("孙七",    1005, 87),
            Student("周八",    1006, 92),
            Student("吴九",    1007, 88),
            Student("郑十",    1008, 76),
            Student("钱十一",  1009, 92),
            Student("陈十二",  1010, 88)
        };
        int n = sizeof(students) / sizeof(students[0]);

        cout << "排序规则：" << endl;
        cout << "  第一关键字：成绩（降序）— 成绩高的排在前面" << endl;
        cout << "  第二关键字：学号（升序）— 成绩相同时，学号小的在前" << endl;
        cout << "  第三关键字：姓名（升序）— 成绩和学号都相同时，姓名按字典序排列" << endl;
        cout << endl;

        printStudents(students, n, "排序前");

        // 使用自定义比较函数进行排序
        sort(students, students + n, cmpStudent);

        cout << endl;
        printStudents(students, n, "排序后");

        cout << endl << "观察：" << endl;
        cout << "  - 成绩 92 分的共有 4 人，按学号升序排列（1001, 1003, 1006, 1009）" << endl;
        cout << "  - 成绩 88 分的共 2 人，按学号升序排列（1007, 1010）" << endl;
        cout << "  - 成绩 87 分的共 2 人，按学号升序排列（1002, 1005）" << endl;
        cout << "  - 成绩 76 分的共 2 人，按学号升序排列（1004, 1008）" << endl;
    }
    cout << endl;

    // ---------- 5. stable_sort() 稳定排序演示 ----------
    cout << "---------- 5. stable_sort() 稳定排序演示 ----------" << endl;
    cout << "稳定排序定义：排序后，相等元素的相对顺序与排序前保持一致" << endl;
    cout << endl;

    {
        // 构造多个相同 value 的元素，通过 seq 和 label 区分
        StableItem items[] = {
            StableItem(3, 1, "第1个值3"),
            StableItem(1, 2, "第1个值1"),
            StableItem(4, 3, "第1个值4"),
            StableItem(3, 4, "第2个值3"),
            StableItem(2, 5, "第1个值2"),
            StableItem(1, 6, "第2个值1"),
            StableItem(5, 7, "第1个值5"),
            StableItem(3, 8, "第3个值3"),
            StableItem(2, 9, "第2个值2"),
            StableItem(1, 10, "第3个值1")
        };
        int n = 10;

        printStableItems(items, n, "原始数据");
        cout << endl;

        // 先用 sort() 排序（不保证稳定性）
        StableItem sortArr[10];
        for (int i = 0; i < n; i++) sortArr[i] = items[i];

        sort(sortArr, sortArr + n,
             [](const StableItem& a, const StableItem& b) {
                 return a.value < b.value;
             });

        printStableItems(sortArr, n, "sort() 排序后（不保证稳定）");
        cout << endl;

        // 再用 stable_sort() 排序（保证稳定性）
        StableItem stableArr[10];
        for (int i = 0; i < n; i++) stableArr[i] = items[i];

        stable_sort(stableArr, stableArr + n,
                    [](const StableItem& a, const StableItem& b) {
                        return a.value < b.value;
                    });

        printStableItems(stableArr, n, "stable_sort() 排序后（保证稳定）");

        cout << endl << "对比观察：" << endl;
        cout << "  对于 value=1 的元素：" << endl;
        cout << "    sort()      中 seq 可能为 2, 6, 10 或乱序（不稳定）" << endl;
        cout << "    stable_sort() 中 seq 保持为 2, 6, 10（原始顺序，稳定）" << endl;
        cout << endl;
        cout << "使用场景：" << endl;
        cout << "  如果已经按次要关键字排好序，现在想按主要关键字再排序，" << endl;
        cout << "  使用 stable_sort() 可以保持次要关键字的原有顺序。" << endl;
        cout << "  示例：先按姓名排序，再用 stable_sort 按班级排序，" << endl;
        cout << "        则同班同学仍按姓名排列（实现了两关键字排序）。" << endl;
    }
    cout << endl;

    // ---------- 6. sort() 与 vector 的使用 ----------
    cout << "---------- 6. sort() 与 vector 的使用 ----------" << endl;
    {
        vector<int> v = {42, 17, 89, 3, 56, 21, 74, 9};

        printVector(v, "原始 vector");

        // 使用 vector 的迭代器
        sort(v.begin(), v.end());

        printVector(v, "sort(v.begin(), v.end()) 升序");

        // 对 vector 的一部分排序（如只排前5个）
        vector<int> v2 = {42, 17, 89, 3, 56, 21, 74, 9};
        sort(v2.begin(), v2.begin() + 5);

        printVector(v2, "sort(v.begin(), v.begin()+5) 只排前5个");

        // 降序排序
        vector<int> v3 = {42, 17, 89, 3, 56, 21, 74, 9};
        sort(v3.begin(), v3.end(), greater<int>());

        printVector(v3, "sort(v.begin(), v.end(), greater<int>()) 降序");
    }
    cout << endl;

    // ---------- 7. lambda 表达式作为比较函数 ----------
    cout << "---------- 7. lambda 表达式作为比较函数 ----------" << endl;
    {
        // lambda 表达式语法：
        // [捕获列表](参数列表) -> 返回类型 { 函数体 }
        // 可以就地定义比较函数，无需单独写函数

        vector<int> v = {5, -3, 8, -2, 1, -7, 4, -6, 0, -1};

        printVector(v, "原始数组");

        // 使用 lambda：按平方值升序排序
        sort(v.begin(), v.end(),
             [](int a, int b) {
                 return a * a < b * b;  // 平方小的在前
             });

        printVector(v, "按平方值升序排序");
        cout << "（使用了 lambda 表达式：[](int a, int b) { return a * a < b * b; }）" << endl;

        cout << endl << "lambda 表达式写法对比：" << endl;
        cout << "  传统写法：单独定义 bool cmp(int a, int b) { return a*a < b*b; }" << endl;
        cout << "  lambda：   [](int a, int b) { return a * a < b * b; }" << endl;
        cout << "  lambda 的优势：简单规则可以就地定义，不需要额外函数" << endl;
    }
    cout << endl;

    // ---------- 8. C 风格字符串数组排序 ----------
    cout << "---------- 8. C 风格字符串数组的排序 ----------" << endl;
    {
        const char* names[] = {
            "banana", "apple", "cherry", "date", "elderberry", "fig"
        };
        int n = sizeof(names) / sizeof(names[0]);

        cout << "原始字符串数组: [";
        for (int i = 0; i < n; i++) {
            if (i > 0) cout << ", ";
            cout << names[i];
        }
        cout << "]" << endl;

        // 使用 lambda 进行字典序排序
        // 注意：比较的是 const char*，需要使用 strcmp
        sort(names, names + n,
             [](const char* a, const char* b) {
                 return strcmp(a, b) < 0;  // strcmp 返回负值表示 a < b
             });

        cout << "字典序排序后: [";
        for (int i = 0; i < n; i++) {
            if (i > 0) cout << ", ";
            cout << names[i];
        }
        cout << "]" << endl;

        // 按字符串长度降序排序
        sort(names, names + n,
             [](const char* a, const char* b) {
                 size_t lenA = strlen(a);
                 size_t lenB = strlen(b);
                 if (lenA != lenB) return lenA > lenB;  // 长的在前
                 return strcmp(a, b) < 0;               // 等长按字典序
             });

        cout << "按长度降序排序后: [";
        for (int i = 0; i < n; i++) {
            if (i > 0) cout << ", ";
            cout << names[i];
        }
        cout << "]" << endl;
    }
    cout << endl;

    cout << "============================================" << endl;
    cout << "  程序结束" << endl;
    cout << "============================================" << endl;

    return 0;
}
