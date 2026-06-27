#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

// ==================== 结构体定义 ====================
struct Student {
    string name;
    int age;
    int chinese, math, english;
    int total;
};

struct Point {
    int x, y;
    double dist;
};

struct Date {
    int year, month, day;
};

struct StudentWithBirthday {
    string name;
    Date birthday;
    int total;
};

// ==================== 函数声明 ====================
void printSeparator(const string &title) {
    cout << "\n========== " << title << " ==========" << endl;
}

// 按总分降序比较
bool cmpByTotal(const Student &a, const Student &b) {
    if (a.total != b.total)
        return a.total > b.total;
    return a.name < b.name;
}

// 按姓名升序比较
bool cmpByName(const Student &a, const Student &b) {
    return a.name < b.name;
}

// 按距离升序比较
bool cmpByDist(const Point &a, const Point &b) {
    return a.dist < b.dist;
}

// 值传递——不会修改原数据
void printByValue(Student s) {
    cout << "[值传递] 姓名: " << s.name << ", 总分: " << s.total << endl;
    s.total = 0; // 修改副本，不影响原数据
    cout << "[值传递] 内部尝试修改后总分: " << s.total << endl;
}

// 引用传递——会修改原数据
void printByRef(Student &s) {
    cout << "[引用传递] 姓名: " << s.name << ", 总分: " << s.total << endl;
    s.total = 999; // 修改原数据
}

// 只读引用传递——安全高效
void printByConstRef(const Student &s) {
    cout << "[const引用] 姓名: " << s.name << ", 总分: " << s.total << endl;
    // s.total = 0; // 编译错误！不能修改 const 引用
}

// 返回结构体的函数
Point makePoint(int x, int y) {
    Point p;
    p.x = x;
    p.y = y;
    p.dist = sqrt(x * x + y * y);
    return p;
}

// 交换两个学生（引用传递）
void swapStudent(Student &a, Student &b) {
    Student temp = a;
    a = b;
    b = temp;
}

int main() {
    // ==================== 1. 结构体定义与初始化 ====================
    printSeparator("1. 结构体的定义与初始化");

    // 方式1：逐个赋值
    Student s1;
    s1.name = "张三";
    s1.age = 12;
    s1.chinese = 90;
    s1.math = 85;
    s1.english = 88;
    s1.total = s1.chinese + s1.math + s1.english;

    // 方式2：C++11 统一初始化
    Student s2{"李四", 13, 82, 91, 95, 0};
    s2.total = s2.chinese + s2.math + s2.english;

    // 方式3：初始化列表
    Student s3 = {"王五", 12, 78, 80, 85, 0};
    s3.total = s3.chinese + s3.math + s3.english;

    cout << s1.name << " 年龄" << s1.age << " 总分: " << s1.total << endl;
    cout << s2.name << " 年龄" << s2.age << " 总分: " << s2.total << endl;
    cout << s3.name << " 年龄" << s3.age << " 总分: " << s3.total << endl;

    // ==================== 2. 点运算符访问成员 ====================
    printSeparator("2. 点运算符访问成员");

    s1.math = 95; // 修改成员值
    cout << "修改后 " << s1.name << " 的数学成绩: " << s1.math << endl;
    double avg = (s1.chinese + s1.math + s1.english) / 3.0;
    cout << "平均分: " << avg << endl;

    // ==================== 3. 结构体数组与统计 ====================
    printSeparator("3. 结构体数组与统计");

    Student stus[5] = {
        {"小明", 11, 92, 88, 95, 0},
        {"小红", 12, 85, 93, 88, 0},
        {"小刚", 11, 78, 82, 80, 0},
        {"小丽", 13, 95, 90, 92, 0},
        {"小华", 12, 70, 75, 72, 0}
    };
    int n = 5;

    // 计算总分
    for (int i = 0; i < n; i++) {
        stus[i].total = stus[i].chinese + stus[i].math + stus[i].english;
    }

    // 找最高分、最低分、计算平均分
    int maxIdx = 0, minIdx = 0;
    int sumTotal = 0;
    for (int i = 0; i < n; i++) {
        sumTotal += stus[i].total;
        if (stus[i].total > stus[maxIdx].total) maxIdx = i;
        if (stus[i].total < stus[minIdx].total) minIdx = i;
    }

    cout << "最高分: " << stus[maxIdx].name
         << " 总分=" << stus[maxIdx].total << endl;
    cout << "最低分: " << stus[minIdx].name
         << " 总分=" << stus[minIdx].total << endl;
    cout << "班级平均分: " << (double)sumTotal / n << endl;

    // ==================== 4. sort 排序 ====================
    printSeparator("4. 结构体排序(sort + cmp)");

    // 按总分降序
    sort(stus, stus + n, cmpByTotal);
    cout << "--- 按总分降序 ---" << endl;
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ". " << stus[i].name
             << " 总分=" << stus[i].total
             << " (语" << stus[i].chinese
             << " 数" << stus[i].math
             << " 英" << stus[i].english << ")" << endl;
    }

    // 按姓名升序
    sort(stus, stus + n, cmpByName);
    cout << "\n--- 按姓名升序 ---" << endl;
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ". " << stus[i].name
             << " 总分=" << stus[i].total << endl;
    }

    // ==================== 5. Point 结构体与距离计算 ====================
    printSeparator("5. Point 结构体与距离计算");

    Point pts[5] = {
        {3, 4, 0},
        {1, 1, 0},
        {0, 5, 0},
        {6, 8, 0},
        {2, 2, 0}
    };
    int m = 5;

    // 计算每个点到原点的距离
    for (int i = 0; i < m; i++) {
        pts[i].dist = sqrt(pts[i].x * pts[i].x + pts[i].y * pts[i].y);
    }

    // 按距离升序排序
    sort(pts, pts + m, cmpByDist);
    cout << "--- 按到原点距离升序 ---" << endl;
    for (int i = 0; i < m; i++) {
        printf("点(%d, %d)  距离=%.2f\n", pts[i].x, pts[i].y, pts[i].dist);
    }

    // 使用 makePoint 函数
    Point p1 = makePoint(5, 12);
    cout << "\nmakePoint(5, 12): 距离=" << p1.dist << endl;

    // ==================== 6. 值传递 vs 引用传递 ====================
    printSeparator("6. 值传递 vs 引用传递");

    Student stuA = {"测试A", 12, 80, 80, 80, 240};
    Student stuB = {"测试B", 13, 90, 90, 90, 270};

    cout << "--- 值传递 ---" << endl;
    cout << "调用前 stuA.total = " << stuA.total << endl;
    printByValue(stuA);
    cout << "调用后 stuA.total = " << stuA.total << " (未改变！)" << endl;

    cout << "\n--- 引用传递 ---" << endl;
    cout << "调用前 stuB.total = " << stuB.total << endl;
    printByRef(stuB);
    cout << "调用后 stuB.total = " << stuB.total << " (被修改了！)" << endl;

    // const 引用传递（安全高效）
    cout << "\n--- const引用传递 ---" << endl;
    printByConstRef(stuA);

    // ==================== 7. 交换结构体 ====================
    printSeparator("7. 交换结构体(引用传递)");

    Student x1 = {"苹果", 10, 100, 100, 100, 300};
    Student x2 = {"香蕉", 11, 90, 90, 90, 270};

    cout << "交换前: " << x1.name << "=" << x1.total
         << ", " << x2.name << "=" << x2.total << endl;
    swapStudent(x1, x2);
    cout << "交换后: " << x1.name << "=" << x1.total
         << ", " << x2.name << "=" << x2.total << endl;

    // ==================== 8. 嵌套结构体 ====================
    printSeparator("8. 嵌套结构体");

    StudentWithBirthday swb;
    swb.name = "小星";
    swb.birthday.year = 2012;
    swb.birthday.month = 3;
    swb.birthday.day = 15;
    swb.total = 285;

    cout << "姓名: " << swb.name << endl;
    cout << "生日: " << swb.birthday.year << "/"
         << swb.birthday.month << "/"
         << swb.birthday.day << endl;
    cout << "总分: " << swb.total << endl;

    // ==================== 9. 函数返回结构体 ====================
    printSeparator("9. 函数返回结构体");

    Student createResult = {"新建", 11, 85, 88, 90, 263};
    cout << "函数返回的学生: " << createResult.name
         << " 总分=" << createResult.total << endl;

    cout << "\n==================== 所有演示完成 ====================" << endl;
    return 0;
}
