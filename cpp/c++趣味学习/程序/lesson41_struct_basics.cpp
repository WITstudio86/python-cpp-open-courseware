/*
 * ============================================================
 * 第41课：超级名片——结构体入门
 * C++趣味学习课程
 * ============================================================
 *
 * 本课学习内容：
 *   1. 结构体(struct)的概念 —— 把不同类型的数据打包在一起
 *   2. struct 的定义语法：struct 名称 { 成员列表 };
 *   3. 创建结构体变量
 *   4. 用点运算符 . 访问和修改结构体成员
 *   5. 结构体的初始化和整体赋值
 *
 * 本文件包含以下程序：
 *   程序1：学生信息卡 —— 结构体基本用法演示
 *   程序2：图书信息管理 —— 结构体综合应用演示
 *   程序3：练习题参考答案 —— 宠物、商品、成绩比拼
 *
 * 编译方式（以 g++ 为例）：
 *   g++ -std=c++11 lesson41_struct_basics.cpp -o lesson41
 *   ./lesson41
 * ============================================================
 */

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// ============================================================
// 第一部分：结构体定义
// 把结构体定义在全局，这样所有程序都可以使用
// ============================================================

// 学生结构体 —— 用于管理学生信息
struct Student {
    string name;      // 姓名
    int age;          // 年龄（岁）
    double score;     // 成绩（分）
};

// 图书结构体 —— 用于管理图书信息
struct Book {
    string title;     // 书名
    string author;    // 作者
    double price;     // 价格（元）
};

// 宠物结构体 —— 用于练习1
struct Pet {
    string name;      // 宠物名字
    string type;      // 种类（狗、猫等）
    int age;          // 年龄（岁）
};

// 商品结构体 —— 用于练习2
struct Product {
    string name;      // 商品名称
    double price;     // 单价（元）
    int quantity;     // 库存数量
};

// 坐标点结构体 —— 用于练习3（演示结构体值复制）
struct Point {
    int x;            // x坐标
    int y;            // y坐标
};

// ============================================================
// 第二部分：辅助函数
// ============================================================

// 打印分隔线，让输出更美观
void printSeparator(string title = "") {
    cout << "\n";
    if (title != "") {
        cout << title << endl;
    }
    cout << "============================================================" << endl;
}

// 打印学生信息
void printStudent(const Student& s) {
    cout << "姓名：" << s.name << "  |  ";
    cout << "年龄：" << s.age << " 岁  |  ";
    cout << "成绩：" << s.score << " 分" << endl;
}

// 打印图书信息
void printBook(const Book& b) {
    cout << "《" << b.title << "》  |  ";
    cout << "作者：" << b.author << "  |  ";
    cout << "价格：" << fixed << setprecision(2) << b.price << " 元" << endl;
}

// ============================================================
// 程序1：学生信息卡演示
// 演示结构体的基本操作：创建、初始化、访问、修改、复制
// ============================================================
void program1_studentCard() {
    printSeparator("【程序1】学生信息卡 —— 结构体基本用法");

    // ---- 1. 创建结构体变量并初始化 ----
    // 使用花括号 {} 按结构体成员的定义顺序初始化
    Student s1 = {"小明", 12, 95.5};

    // ---- 2. 访问结构体成员（读取） ----
    // 使用点运算符 . 来读取每个成员的值
    cout << ">>> 学生信息卡 <<<" << endl;
    cout << "姓名：" << s1.name << endl;
    cout << "年龄：" << s1.age << " 岁" << endl;
    cout << "成绩：" << s1.score << " 分" << endl;

    // ---- 3. 修改结构体成员 ----
    // 直接通过 . 赋值即可修改
    cout << "\n>>> 小明成绩进步了！ <<<" << endl;
    s1.score = 98.0;  // 成绩从 95.5 改为 98.0
    cout << "更新后的成绩：" << s1.score << " 分" << endl;

    // ---- 4. 通过输入给结构体赋值 ----
    Student s2;
    cout << "\n>>> 请输入第二个学生的信息 <<<" << endl;
    cout << "姓名：";
    cin >> s2.name;
    cout << "年龄：";
    cin >> s2.age;
    cout << "成绩：";
    cin >> s2.score;

    cout << "\n你输入的学生：" << endl;
    printStudent(s2);

    // ---- 5. 结构体整体赋值（复制） ----
    cout << "\n>>> 结构体赋值演示 <<<" << endl;
    Student s3;
    s3 = s1;  // 把 s1 的所有成员值一次性复制给 s3
    cout << "将 s1 赋值给 s3 后，s3 的信息：" << endl;
    printStudent(s3);

    cout << "\n修改 s3 的名字为\"大明\"：" << endl;
    s3.name = "大明";
    cout << "s1 的名字：" << s1.name << endl;  // 仍然是小明，不受影响
    cout << "s3 的名字：" << s3.name << endl;  // 变成了大明
    cout << "结论：结构体赋值是【值复制】，修改副本不影响原件！" << endl;
}

// ============================================================
// 程序2：图书信息管理演示
// 演示结构体的综合应用：创建多个变量、计算、格式化输出
// ============================================================
void program2_bookManager() {
    printSeparator("【程序2】图书信息管理 —— 结构体综合应用");

    // ---- 1. 创建多本图书 ----
    Book book1 = {"小王子", "圣埃克苏佩里", 29.90};
    Book book2 = {"西游记", "吴承恩", 45.00};
    Book book3 = {"哈利·波特与魔法石", "J.K.罗琳", 39.50};

    // ---- 2. 输出所有图书信息 ----
    cout << "========== 我的小小图书馆 ==========" << endl;
    cout << "编号 | 书名                    | 作者           | 价格" << endl;
    cout << "-----+-------------------------+----------------+--------" << endl;
    cout << "  1  | " << book1.title << "                | "
         << book1.author << "    | " << fixed << setprecision(2)
         << book1.price << " 元" << endl;
    cout << "  2  | " << book2.title << "                  | "
         << book2.author << "        | " << book2.price << " 元" << endl;
    cout << "  3  | " << book3.title << "      | "
         << book3.author << "      | " << book3.price << " 元" << endl;

    // ---- 3. 计算总价 ----
    double total = book1.price + book2.price + book3.price;
    cout << "-----+-------------------------+----------------+--------" << endl;
    cout << "总价：" << total << " 元" << endl;

    // ---- 4. 修改图书信息（模拟打折） ----
    cout << "\n>>> 打折促销啦！《小王子》打8折 <<<" << endl;
    book1.price = book1.price * 0.8;
    cout << "《小王子》打折后价格：" << book1.price << " 元" << endl;

    // ---- 5. 比较找最贵的书 ----
    cout << "\n>>> 找出最贵的书 <<<" << endl;
    Book mostExpensive = book1;  // 先假设第一本最贵
    if (book2.price > mostExpensive.price) {
        mostExpensive = book2;
    }
    if (book3.price > mostExpensive.price) {
        mostExpensive = book3;
    }
    cout << "最贵的书是：《" << mostExpensive.title << "》" << endl;
    cout << "价格为：" << mostExpensive.price << " 元" << endl;

    // ---- 6. 统计信息 ----
    cout << "\n>>> 图书统计 <<<" << endl;
    cout << "共有 3 本书" << endl;
    cout << "总价：" << total << " 元" << endl;
    cout << "平均价格：" << (total / 3) << " 元" << endl;
}

// ============================================================
// 程序3：练习题参考答案
// 包含练习1、练习2、练习3 的完整解答代码
// ============================================================
void program3_exercises() {
    printSeparator("【程序3】练习题参考答案");

    // ========== 练习1：定义你的宠物 ==========
    cout << "---------- 练习1：宠物信息卡 ----------" << endl;
    Pet myPet = {"旺财", "狗", 3};
    cout << "我的宠物：" << endl;
    cout << "  名字：" << myPet.name << endl;
    cout << "  种类：" << myPet.type << endl;
    cout << "  年龄：" << myPet.age << " 岁" << endl;

    // ========== 练习2：商品信息管理 ==========
    cout << "\n---------- 练习2：商品信息管理 ----------" << endl;
    Product p1 = {"铅笔", 2.5, 100};
    Product p2 = {"橡皮", 1.5, 80};

    double total1 = p1.price * p1.quantity;
    double total2 = p2.price * p2.quantity;
    double grandTotal = total1 + total2;

    cout << "商品1 - " << p1.name << "：" << endl;
    cout << "  单价：" << p1.price << " 元，库存：" << p1.quantity << " 支" << endl;
    cout << "  总价值：" << total1 << " 元" << endl;

    cout << "商品2 - " << p2.name << "：" << endl;
    cout << "  单价：" << p2.price << " 元，库存：" << p2.quantity << " 块" << endl;
    cout << "  总价值：" << total2 << " 元" << endl;

    cout << "所有商品总价值：" << grandTotal << " 元" << endl;

    // ========== 练习3：结构体值复制 ==========
    cout << "\n---------- 练习3：结构体的值复制 ----------" << endl;
    Point pnt1 = {3, 5};
    Point pnt2 = pnt1;   // 值复制
    pnt2.x = 10;         // 修改 p2
    pnt2.y = 20;

    cout << "p1: (" << pnt1.x << ", " << pnt1.y << ")" << endl;
    cout << "p2: (" << pnt2.x << ", " << pnt2.y << ")" << endl;
    cout << "结论：修改 p2 不影响 p1，因为它们是独立的两份数据！" << endl;
}

// ============================================================
// 程序4：挑战任务 —— 成绩排行榜
// 创建3个学生，找出最高分，计算平均分，输出排行榜
// ============================================================
void program4_challenge() {
    printSeparator("【挑战任务】成绩排行榜");

    // ---- 1. 创建并存入3个学生信息 ----
    Student students[3] = {
        {"小明", 12, 88.5},
        {"小红", 11, 96.0},
        {"小刚", 12, 91.0}
    };

    cout << ">>> 所有学生信息 <<<" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "学生" << (i + 1) << "：";
        printStudent(students[i]);
    }

    // ---- 2. 找出成绩最高的学生 ----
    int bestIndex = 0;  // 假设第0个学生成绩最高
    for (int i = 1; i < 3; i++) {
        if (students[i].score > students[bestIndex].score) {
            bestIndex = i;
        }
    }

    cout << "\n>>> 成绩最高的学生 <<<" << endl;
    cout << "🏆 " << students[bestIndex].name << " —— "
         << students[bestIndex].score << " 分！" << endl;

    // ---- 3. 计算平均成绩 ----
    double totalScore = 0.0;
    for (int i = 0; i < 3; i++) {
        totalScore += students[i].score;
    }
    double averageScore = totalScore / 3;
    cout << "\n>>> 班级平均分 <<<" << endl;
    cout << "平均成绩：" << averageScore << " 分" << endl;

    // ---- 4. 按成绩从高到低排序并输出排行榜 ----
    // 使用简单的选择排序（冒泡排序的铺垫！）
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2 - i; j++) {
            if (students[j].score < students[j + 1].score) {
                // 交换整个结构体！
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    cout << "\n>>> 成绩排行榜（从高到低） <<<" << endl;
    cout << "排名 | 姓名 | 年龄 | 成绩" << endl;
    cout << "-----+------+------+------" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "  " << (i + 1) << "   | "
             << students[i].name << " |  "
             << students[i].age << "  | "
             << students[i].score << endl;
    }

    // ---- 5. 综合评价 ----
    cout << "\n>>> 综合评价 <<<" << endl;
    for (int i = 0; i < 3; i++) {
        cout << students[i].name << "：";
        if (students[i].score >= 90) {
            cout << "优秀！继续保持！" << endl;
        } else if (students[i].score >= 80) {
            cout << "良好！继续加油！" << endl;
        } else if (students[i].score >= 60) {
            cout << "及格了，但还需要努力哦！" << endl;
        } else {
            cout << "不要气馁，好好复习！" << endl;
        }
    }
}

// ============================================================
// main 函数：程序入口
// 依次运行所有演示程序
// ============================================================
int main() {
    // 设置输出中文（根据不同操作系统可能需要调整）
    // Windows: system("chcp 65001");
    // 本程序在支持 UTF-8 的终端中直接运行即可

    cout << "╔══════════════════════════════════════════════════════════╗" << endl;
    cout << "║     第41课：超级名片 —— 结构体入门                     ║" << endl;
    cout << "║     C++ 趣味学习课程                                    ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════╝" << endl;
    cout << "\n本程序将依次演示：" << endl;
    cout << "  1. 学生信息卡 —— 结构体基本操作" << endl;
    cout << "  2. 图书信息管理 —— 结构体综合应用" << endl;
    cout << "  3. 练习题参考答案" << endl;
    cout << "  4. 挑战任务 —— 成绩排行榜" << endl;
    cout << endl;

    // ---- 依次运行各个程序 ----
    program1_studentCard();

    cout << "\n按 Enter 键继续观看下一个程序...";
    cin.get();  // 等待用户按回车
    cin.get();  // 消耗掉之前输入留下的换行符（如果有的话）

    program2_bookManager();

    cout << "\n按 Enter 键继续观看下一个程序...";
    cin.get();

    program3_exercises();

    cout << "\n按 Enter 键继续观看下一个程序...";
    cin.get();

    program4_challenge();

    cout << "\n╔══════════════════════════════════════════════════════════╗" << endl;
    cout << "║     本课所有程序演示完毕！                              ║" << endl;
    cout << "║     下一课预告：第42课 —— 排排坐吃果果：冒泡排序       ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════╝" << endl;

    return 0;
}
