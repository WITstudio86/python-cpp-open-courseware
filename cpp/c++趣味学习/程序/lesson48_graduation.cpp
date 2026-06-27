/*
 * ============================================================
 * 第48课：我的编程毕业礼——综合复习
 * C++趣味学习课程 - 毕业课
 * ============================================================
 *
 * 本课学习内容：
 *   1. 综合复习：结构体、排序算法、随机数、循环、条件判断等
 *   2. 学生成绩管理系统 —— 结构体 + 冒泡排序/选择排序 + 菜单
 *   3. 多功能工具箱 —— 整合猜数字、计算器、成绩排序等多个模块
 *   4. 毕业作品示例 —— 完整的综合项目演示
 *
 * 本文件包含以下程序：
 *   程序1：学生成绩管理系统
 *          —— 结构体数组 + 冒泡排序 + 选择排序 + 菜单交互 + 统计分析
 *   程序2：多功能工具箱
 *          —— 猜数字游戏 + 成绩排序器 + 简易计算器 + 数组分析
 *   程序3：毕业作品示例：班级信息总管
 *          —— 通讯录管理 + 成绩管理 + 知识问答 + 数据统计
 *
 * 编译方式（以 g++ 为例）：
 *   g++ -std=c++11 lesson48_graduation.cpp -o lesson48
 *   ./lesson48
 * ============================================================
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

// ============================================================
// 第一部分：全局结构体定义
// ============================================================

// 学生结构体 —— 用于学生成绩管理
struct Student {
    string name;      // 姓名
    int age;          // 年龄
    double score;     // 成绩（0~100分）
};

// 扩展学生结构体 —— 用于毕业作品（多科目成绩）
struct FullStudent {
    string name;      // 姓名
    int id;           // 学号
    double chinese;   // 语文成绩
    double math;      // 数学成绩
    double english;   // 英语成绩
    double total;     // 总分（由程序计算）
};

// 通讯录结构体 —— 用于班级信息总管
struct Contact {
    string name;      // 姓名
    int age;          // 年龄
    string phone;     // 电话
    string qq;        // QQ号
};

// 知识问答题结构体
struct Question {
    string question;  // 题目
    string options[4];// 选项 A B C D
    char answer;      // 正确答案（A/B/C/D）
};

// ============================================================
// 第二部分：通用辅助函数
// ============================================================

// 打印分隔线，让输出更美观
void printSeparator(string title = "") {
    cout << "\n";
    if (title != "") {
        cout << title << endl;
    }
    cout << "============================================================" << endl;
}

// 暂停等待用户按回车
void waitForEnter() {
    cout << "\n按 Enter 键继续...";
    cin.ignore(10000, '\n');
    cin.get();
}

// 清屏辅助（打印多行空行模拟清屏效果）
void clearScreen() {
    for (int i = 0; i < 3; i++) cout << endl;
}

// ============================================================
// 程序1：学生成绩管理系统
// ============================================================
// 功能说明：
//   整合了结构体、结构体数组、冒泡排序、选择排序、
//   菜单交互、统计分析等多个知识点。
//   用户可以通过菜单选择不同的操作来管理学生成绩数据。
// ============================================================

// ---- 1a. 显示所有学生信息 ----
void showAllStudents(Student arr[], int n) {
    cout << "\n┌────┬──────────┬──────┬────────┬──────┐" << endl;
    cout << "│学号│   姓名   │ 年龄 │  成绩  │ 等级 │" << endl;
    cout << "├────┼──────────┼──────┼────────┼──────┤" << endl;
    for (int i = 0; i < n; i++) {
        // 根据成绩评定等级
        char grade;
        if (arr[i].score >= 90)      grade = 'A';
        else if (arr[i].score >= 80) grade = 'B';
        else if (arr[i].score >= 70) grade = 'C';
        else if (arr[i].score >= 60) grade = 'D';
        else                         grade = 'E';

        cout << "│ " << (i + 1) << "  │ "
             << left << setw(8) << arr[i].name << " │ "
             << right << setw(4) << arr[i].age << " │ "
             << fixed << setprecision(1) << setw(6) << arr[i].score << " │  "
             << grade << "   │" << endl;
    }
    cout << "└────┴──────────┴──────┴────────┴──────┘" << endl;
}

// ---- 1b. 冒泡排序：按成绩从高到低（降序） ----
void bubbleSortByScore(Student arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;  // 优化标志位
        for (int j = 0; j < n - 1 - i; j++) {
            // 降序排列：如果前面的成绩小于后面的，就交换
            if (arr[j].score < arr[j + 1].score) {
                // 交换整个结构体（三个步骤 + 临时变量）
                Student temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        // 如果这一轮没有发生任何交换，说明已经排好序了
        if (!swapped) {
            cout << "  [优化] 第" << (i + 1) << "轮无交换，数组已有序，提前结束！" << endl;
            break;
        }
    }
}

// ---- 1c. 选择排序：按年龄从小到大（升序） ----
void selectionSortByAge(Student arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;  // 假设当前 i 位置的值是最小的

        // 在未排序区中寻找最小元素的索引
        for (int j = i + 1; j < n; j++) {
            if (arr[j].age < arr[minIdx].age) {
                minIdx = j;
            }
        }

        // 如果找到了更小的元素（不在 i 位置），就交换
        if (minIdx != i) {
            Student temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
        }
    }
}

// ---- 1d. 统计分析 ----
void showStatistics(Student arr[], int n) {
    double sum = 0.0;           // 总分
    double maxScore = arr[0].score;  // 最高分
    double minScore = arr[0].score;  // 最低分
    int maxIdx = 0, minIdx = 0;

    for (int i = 0; i < n; i++) {
        sum += arr[i].score;
        // 找最高分
        if (arr[i].score > maxScore) {
            maxScore = arr[i].score;
            maxIdx = i;
        }
        // 找最低分
        if (arr[i].score < minScore) {
            minScore = arr[i].score;
            minIdx = i;
        }
    }

    double average = sum / n;  // 平均分

    // 统计各等级人数
    int countA = 0, countB = 0, countC = 0, countD = 0, countE = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i].score >= 90)      countA++;
        else if (arr[i].score >= 80) countB++;
        else if (arr[i].score >= 70) countC++;
        else if (arr[i].score >= 60) countD++;
        else                         countE++;
    }

    cout << fixed << setprecision(1);
    cout << "\n┌──────────────────────────────┐" << endl;
    cout << "│        📊 成绩统计分析       │" << endl;
    cout << "├──────────────────────────────┤" << endl;
    cout << "│ 学生总数：" << setw(4) << n << " 人           │" << endl;
    cout << "│ 平均成绩：" << setw(6) << average << " 分         │" << endl;
    cout << "│ 最高分：  " << arr[maxIdx].name << " "
         << setw(5) << maxScore << " 分   │" << endl;
    cout << "│ 最低分：  " << arr[minIdx].name << " "
         << setw(5) << minScore << " 分   │" << endl;
    cout << "├──────────────────────────────┤" << endl;
    cout << "│ 等级分布：                  │" << endl;
    cout << "│  A(90+): " << countA << "人  B(80-89): " << countB << "人  │" << endl;
    cout << "│  C(70-79): " << countC << "人  D(60-69): " << countD << "人  │" << endl;
    cout << "│  E(<60):  " << countE << "人                     │" << endl;
    cout << "└──────────────────────────────┘" << endl;
}

// ---- 1e. 按姓名查找学生 ----
void searchByName(Student arr[], int n, string target) {
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (arr[i].name == target) {
            cout << "\n🔍 找到了！" << endl;
            cout << "  姓名：" << arr[i].name << endl;
            cout << "  年龄：" << arr[i].age << " 岁" << endl;
            cout << "  成绩：" << arr[i].score << " 分" << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "\n❌ 未找到名为 \"" << target << "\" 的学生！" << endl;
    }
}

// ---- 程序1主入口 ----
void program1_studentManagement() {
    printSeparator("【程序1】📚 学生成绩管理系统");

    // 初始化5个学生的数据（结构体数组）
    const int N = 5;
    Student students[N] = {
        {"小明",  12, 88.5},
        {"小红",  11, 96.0},
        {"小刚",  12, 75.5},
        {"小丽",  13, 91.0},
        {"小强",  11, 62.0}
    };

    int choice;
    while (true) {
        cout << "\n╔══════════════════════════════════╗" << endl;
        cout << "║   📚 学生成绩管理系统 v1.0      ║" << endl;
        cout << "╠══════════════════════════════════╣" << endl;
        cout << "║  1. 查看所有学生信息            ║" << endl;
        cout << "║  2. 按成绩排名（冒泡排序-降序） ║" << endl;
        cout << "║  3. 按年龄排序（选择排序-升序） ║" << endl;
        cout << "║  4. 查看成绩统计分析            ║" << endl;
        cout << "║  5. 按姓名查找学生              ║" << endl;
        cout << "║  6. 退出系统                    ║" << endl;
        cout << "╚══════════════════════════════════╝" << endl;
        cout << "请输入你的选择(1-6)：";
        cin >> choice;

        switch (choice) {
            case 1:
                // 功能1：查看所有学生信息
                showAllStudents(students, N);
                break;

            case 2:
                // 功能2：冒泡排序 + 展示结果
                cout << "\n>>> 正在使用【冒泡排序】按成绩从高到低排列..." << endl;
                bubbleSortByScore(students, N);
                showAllStudents(students, N);
                break;

            case 3:
                // 功能3：选择排序 + 展示结果
                cout << "\n>>> 正在使用【选择排序】按年龄从小到大排列..." << endl;
                selectionSortByAge(students, N);
                showAllStudents(students, N);
                break;

            case 4:
                // 功能4：成绩统计分析
                showStatistics(students, N);
                break;

            case 5: {
                // 功能5：按姓名查找
                string searchName;
                cout << "请输入要查找的学生姓名：";
                cin >> searchName;
                searchByName(students, N, searchName);
                break;
            }

            case 6:
                // 退出系统
                cout << "\n👋 感谢使用学生成绩管理系统，再见！" << endl;
                return;

            default:
                cout << "⚠️  输入错误，请输入1~6之间的数字！" << endl;
        }
    }
}

// ============================================================
// 程序2：多功能工具箱
// ============================================================
// 功能说明：
//   包含4个独立的功能模块：猜数字游戏、成绩排序器、
//   简易计算器、数组分析器。
//   演示了模块化编程的思想——每个功能独立封装为函数。
// ============================================================

// ---- 2a. 猜数字游戏 ----
// 知识点：随机数(rand/srand/time)、循环(while)、条件判断(if-else)
void module_guessNumber() {
    printSeparator("🎯 猜数字游戏");

    // 初始化随机数种子（使用当前时间，确保每次运行结果不同）
    int target = rand() % 100 + 1;  // 生成1~100之间的随机数
    int guess;
    int count = 0;  // 记录猜测次数

    cout << "我已经想好了一个 1~100 之间的数字，来猜猜看吧！" << endl;

    while (true) {
        cout << "请输入你猜的数字：";
        cin >> guess;
        count++;  // 猜测次数+1

        // 条件判断：给出提示
        if (guess > target) {
            cout << "📉 太大了！往小了猜～" << endl;
        } else if (guess < target) {
            cout << "📈 太小了！往大了猜～" << endl;
        } else {
            // 猜对了！
            cout << "\n🎉 恭喜你猜对了！" << endl;
            cout << "正确答案就是 " << target << "！" << endl;
            cout << "你一共猜了 " << count << " 次。" << endl;

            // 评价猜测表现
            if (count <= 5) {
                cout << "🏆 太厉害了！你是猜数字大师！" << endl;
            } else if (count <= 10) {
                cout << "👍 不错！继续加油！" << endl;
            } else {
                cout << "💪 多练练会更快哦～" << endl;
            }
            break;  // 猜对了，退出循环
        }
    }
}

// ---- 2b. 成绩排序器 ----
// 知识点：结构体数组、冒泡排序、for循环
void module_scoreSorter() {
    printSeparator("📊 成绩排序器");

    // 结构体：成绩记录
    struct ScoreRecord {
        string name;
        double score;
    };

    const int N = 5;
    ScoreRecord records[N];

    // 输入学生姓名和成绩
    cout << "请输入 " << N << " 位同学的姓名和成绩：" << endl;
    for (int i = 0; i < N; i++) {
        cout << "第" << (i + 1) << "位 → 姓名：";
        cin >> records[i].name;
        cout << "        成绩：";
        cin >> records[i].score;
    }

    // 冒泡排序：成绩从高到低
    for (int i = 0; i < N - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < N - 1 - i; j++) {
            if (records[j].score < records[j + 1].score) {
                ScoreRecord temp = records[j];
                records[j] = records[j + 1];
                records[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }

    // 输出排名榜
    cout << "\n╔══════════════════════════╗" << endl;
    cout << "║     🏆 成绩排行榜       ║" << endl;
    cout << "╠════╦══════════╦═════════╣" << endl;
    cout << "║ 排名║   姓名   ║  成绩   ║" << endl;
    cout << "╠════╬══════════╬═════════╣" << endl;
    for (int i = 0; i < N; i++) {
        cout << "║  " << (i + 1) << "  ║ "
             << left << setw(8) << records[i].name << " ║ "
             << right << fixed << setprecision(1) << setw(6) << records[i].score << " ║" << endl;
    }
    cout << "╚════╩══════════╩═════════╝" << endl;
}

// ---- 2c. 简易计算器 ----
// 知识点：switch-case、if-else、算术运算
void module_calculator() {
    printSeparator("🧮 简易计算器");

    double num1, num2, result;
    char op;

    cout << "支持的运算：加法(+)、减法(-)、乘法(*)、除法(/)" << endl;
    cout << "请输入算式（格式：数字 运算符 数字）：" << endl;
    cout << "例如：3.5 + 2.1 或 10 / 4" << endl;
    cout << "> ";
    cin >> num1 >> op >> num2;

    cout << "\n计算结果：" << endl;

    // 使用 switch-case 处理不同运算符
    switch (op) {
        case '+':
            result = num1 + num2;
            cout << num1 << " + " << num2 << " = " << result << endl;
            break;

        case '-':
            result = num1 - num2;
            cout << num1 << " - " << num2 << " = " << result << endl;
            break;

        case '*':
            result = num1 * num2;
            cout << num1 << " * " << num2 << " = " << result << endl;
            break;

        case '/':
            // 除法需要检查除数是否为0
            if (num2 != 0) {
                result = num1 / num2;
                cout << num1 << " / " << num2 << " = " << result << endl;
            } else {
                cout << "❌ 错误：除数不能为0！" << endl;
            }
            break;

        default:
            cout << "❌ 不支持的运算符：" << op << endl;
            cout << "   请使用 +、-、*、/ 中的一个。" << endl;
    }
}

// ---- 2d. 数组分析器 ----
// 知识点：数组遍历、找最大值/最小值、求和、平均值
void module_arrayAnalyzer() {
    printSeparator("🔍 数组分析器");

    int n;
    // 最多支持100个数字
    int arr[100];

    cout << "请输入你想分析的数字个数（最多100个）：";
    cin >> n;

    // 安全检查：确保n在有效范围内
    if (n <= 0 || n > 100) {
        cout << "❌ 数量必须在1~100之间！" << endl;
        return;
    }

    cout << "请输入 " << n << " 个整数：" << endl;
    for (int i = 0; i < n; i++) {
        cout << "第" << (i + 1) << "个：";
        cin >> arr[i];
    }

    // 同时找最大值、最小值和总和
    int maxVal = arr[0], minVal = arr[0];
    int maxIdx = 0, minIdx = 0;
    double sum = 0.0;

    for (int i = 0; i < n; i++) {
        sum += arr[i];

        if (arr[i] > maxVal) {
            maxVal = arr[i];
            maxIdx = i;
        }
        if (arr[i] < minVal) {
            minVal = arr[i];
            minIdx = i;
        }
    }

    double average = sum / n;

    // 统计奇数和偶数的个数
    int oddCount = 0, evenCount = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            evenCount++;
        } else {
            oddCount++;
        }
    }

    // 输出分析结果
    cout << "\n╔═══════════════════════════════╗" << endl;
    cout << "║      📈 数组分析报告         ║" << endl;
    cout << "╠═══════════════════════════════╣" << endl;
    cout << "║ 数据个数：" << setw(4) << n << "               ║" << endl;
    cout << "║ 最大值：  " << setw(6) << maxVal << "（第" << (maxIdx + 1) << "个）  ║" << endl;
    cout << "║ 最小值：  " << setw(6) << minVal << "（第" << (minIdx + 1) << "个）  ║" << endl;
    cout << "║ 总和：    " << setw(6) << (int)sum << "               ║" << endl;
    cout << "║ 平均值：  " << fixed << setprecision(2)
         << setw(8) << average << "           ║" << endl;
    cout << "║ 奇数个数：" << setw(4) << oddCount << "             ║" << endl;
    cout << "║ 偶数个数：" << setw(4) << evenCount << "             ║" << endl;
    cout << "╚═══════════════════════════════╝" << endl;

    // 输出原数组用于核对
    cout << "\n原始数据：[";
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "]" << endl;
}

// ---- 程序2主入口 ----
void program2_toolbox() {
    srand(time(0));  // 初始化随机数种子（只需一次）

    int choice;
    while (true) {
        cout << "\n╔══════════════════════════════════════╗" << endl;
        cout << "║     🎓 我的编程工具箱 v1.0          ║" << endl;
        cout << "╠══════════════════════════════════════╣" << endl;
        cout << "║  1. 🎯 猜数字游戏                   ║" << endl;
        cout << "║  2. 📊 成绩排序器                   ║" << endl;
        cout << "║  3. 🧮 简易计算器                   ║" << endl;
        cout << "║  4. 🔍 数组分析器                   ║" << endl;
        cout << "║  5. 🚪 退出工具箱                   ║" << endl;
        cout << "╚══════════════════════════════════════╝" << endl;
        cout << "请输入你的选择(1-5)：";
        cin >> choice;

        switch (choice) {
            case 1: module_guessNumber();    break;
            case 2: module_scoreSorter();    break;
            case 3: module_calculator();     break;
            case 4: module_arrayAnalyzer();  break;
            case 5:
                cout << "\n👋 感谢使用我的编程工具箱，再见！" << endl;
                return;
            default:
                cout << "⚠️  输入错误，请输入1~5之间的数字！" << endl;
        }
    }
}

// ============================================================
// 程序3：毕业作品示例 —— 班级信息总管
// ============================================================
// 功能说明：
//   这是一个综合性的毕业作品示例，整合了多个功能模块：
//   - 模块A：通讯录管理（结构体数组 + 查找 + 排序）
//   - 模块B：成绩管理（结构体数组 + 冒泡排序 + 统计分析）
//   - 模块C：知识问答（结构体数组 + 随机数 + 计分）
//   - 模块D：数据统计（总和、平均值、排名）
//
//   本程序展示了一个"毕业作品"应有的复杂度、完整性和趣味性。
// ============================================================

// ---- 3a. 通讯录管理模块 ----
void moduleA_contacts(Contact contacts[], int& contactCount) {
    // contactCount 使用引用，可以在函数内部修改实际值
    int subChoice;
    while (true) {
        cout << "\n--- 📇 通讯录管理 ---" << endl;
        cout << "  1. 查看所有联系人" << endl;
        cout << "  2. 添加新联系人" << endl;
        cout << "  3. 按姓名查找" << endl;
        cout << "  4. 按年龄排序" << endl;
        cout << "  5. 返回主菜单" << endl;
        cout << "请输入选择(1-5)：";
        cin >> subChoice;

        if (subChoice == 1) {
            // 查看所有联系人
            if (contactCount == 0) {
                cout << "通讯录为空，请先添加联系人！" << endl;
            } else {
                cout << "\n===== 通讯录（共 " << contactCount << " 人）=====" << endl;
                for (int i = 0; i < contactCount; i++) {
                    cout << "[" << (i + 1) << "] " << contacts[i].name
                         << " | 年龄：" << contacts[i].age
                         << " | 电话：" << contacts[i].phone
                         << " | QQ：" << contacts[i].qq << endl;
                }
            }
        } else if (subChoice == 2) {
            // 添加新联系人
            if (contactCount >= 50) {
                cout << "通讯录已满（最多50人）！" << endl;
            } else {
                cout << "\n--- 添加新联系人 ---" << endl;
                cout << "姓名：";
                cin >> contacts[contactCount].name;
                cout << "年龄：";
                cin >> contacts[contactCount].age;
                cout << "电话：";
                cin >> contacts[contactCount].phone;
                cout << "QQ号：";
                cin >> contacts[contactCount].qq;
                contactCount++;
                cout << "✅ 添加成功！当前共有 " << contactCount << " 位联系人。" << endl;
            }
        } else if (subChoice == 3) {
            // 按姓名查找
            if (contactCount == 0) {
                cout << "通讯录为空！" << endl;
            } else {
                string searchName;
                cout << "请输入要查找的姓名：";
                cin >> searchName;
                bool found = false;
                for (int i = 0; i < contactCount; i++) {
                    if (contacts[i].name == searchName) {
                        cout << "\n🔍 找到了！" << endl;
                        cout << "  姓名：" << contacts[i].name << endl;
                        cout << "  年龄：" << contacts[i].age << endl;
                        cout << "  电话：" << contacts[i].phone << endl;
                        cout << "  QQ：" << contacts[i].qq << endl;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "❌ 未找到！" << endl;
                }
            }
        } else if (subChoice == 4) {
            // 按年龄排序（冒泡排序，升序）
            if (contactCount <= 1) {
                cout << "至少需要2个联系人才能排序！" << endl;
            } else {
                for (int i = 0; i < contactCount - 1; i++) {
                    for (int j = 0; j < contactCount - 1 - i; j++) {
                        if (contacts[j].age > contacts[j + 1].age) {
                            Contact temp = contacts[j];
                            contacts[j] = contacts[j + 1];
                            contacts[j + 1] = temp;
                        }
                    }
                }
                cout << "✅ 已按年龄从小到大排序！" << endl;
                cout << "\n排序后：" << endl;
                for (int i = 0; i < contactCount; i++) {
                    cout << "  " << contacts[i].name << " - " << contacts[i].age << "岁" << endl;
                }
            }
        } else if (subChoice == 5) {
            return;  // 返回主菜单
        } else {
            cout << "⚠️  输入错误！" << endl;
        }
    }
}

// ---- 3b. 成绩管理模块 ----
void moduleB_scores() {
    const int SN = 5;
    FullStudent students[SN] = {
        {"小明", 1001, 88, 92, 85, 0},
        {"小红", 1002, 95, 89, 93, 0},
        {"小刚", 1003, 72, 68, 75, 0},
        {"小丽", 1004, 91, 96, 88, 0},
        {"小强", 1005, 65, 70, 60, 0}
    };

    // 计算每个人的总分
    for (int i = 0; i < SN; i++) {
        students[i].total = students[i].chinese + students[i].math + students[i].english;
    }

    int subChoice;
    while (true) {
        cout << "\n--- 📊 成绩管理 ---" << endl;
        cout << "  1. 查看所有成绩" << endl;
        cout << "  2. 按总分排名（冒泡排序）" << endl;
        cout << "  3. 成绩统计分析" << endl;
        cout << "  4. 返回主菜单" << endl;
        cout << "请输入选择(1-4)：";
        cin >> subChoice;

        if (subChoice == 1) {
            // 查看所有成绩
            cout << "\n学号\t姓名\t语文\t数学\t英语\t总分" << endl;
            cout << "----\t----\t----\t----\t----\t----" << endl;
            for (int i = 0; i < SN; i++) {
                cout << students[i].id << "\t"
                     << students[i].name << "\t"
                     << students[i].chinese << "\t"
                     << students[i].math << "\t"
                     << students[i].english << "\t"
                     << fixed << setprecision(1) << students[i].total << endl;
            }
        } else if (subChoice == 2) {
            // 按总分排名：冒泡排序（降序）
            FullStudent sorted[SN];
            for (int i = 0; i < SN; i++) sorted[i] = students[i];

            for (int i = 0; i < SN - 1; i++) {
                bool swapped = false;
                for (int j = 0; j < SN - 1 - i; j++) {
                    if (sorted[j].total < sorted[j + 1].total) {
                        FullStudent temp = sorted[j];
                        sorted[j] = sorted[j + 1];
                        sorted[j + 1] = temp;
                        swapped = true;
                    }
                }
                if (!swapped) break;
            }

            cout << "\n===== 🏆 总分排名榜 =====" << endl;
            for (int i = 0; i < SN; i++) {
                cout << "第" << (i + 1) << "名：" << sorted[i].name
                     << "（总分：" << sorted[i].total << "）" << endl;
            }
        } else if (subChoice == 3) {
            // 成绩统计分析
            double sumC = 0, sumM = 0, sumE = 0;
            double maxC = students[0].chinese, maxM = students[0].math, maxE = students[0].english;
            double minC = students[0].chinese, minM = students[0].math, minE = students[0].english;

            for (int i = 0; i < SN; i++) {
                sumC += students[i].chinese;
                sumM += students[i].math;
                sumE += students[i].english;
                if (students[i].chinese > maxC) maxC = students[i].chinese;
                if (students[i].math > maxM) maxM = students[i].math;
                if (students[i].english > maxE) maxE = students[i].english;
                if (students[i].chinese < minC) minC = students[i].chinese;
                if (students[i].math < minM) minM = students[i].math;
                if (students[i].english < minE) minE = students[i].english;
            }

            cout << "\n===== 📈 成绩统计分析 =====" << endl;
            cout << fixed << setprecision(1);
            cout << "        语文    数学    英语" << endl;
            cout << "最高分  " << maxC << "   " << maxM << "   " << maxE << endl;
            cout << "最低分  " << minC << "   " << minM << "   " << minE << endl;
            cout << "平均分  " << (sumC / SN) << "  "
                 << (sumM / SN) << "  " << (sumE / SN) << endl;

            // 找出不及格的同学（任一科<60）
            cout << "\n⚠️  不及格提醒：" << endl;
            bool hasFailing = false;
            for (int i = 0; i < SN; i++) {
                if (students[i].chinese < 60 || students[i].math < 60 || students[i].english < 60) {
                    cout << "  " << students[i].name << " - ";
                    if (students[i].chinese < 60) cout << "语文:" << students[i].chinese << " ";
                    if (students[i].math < 60) cout << "数学:" << students[i].math << " ";
                    if (students[i].english < 60) cout << "英语:" << students[i].english;
                    cout << endl;
                    hasFailing = true;
                }
            }
            if (!hasFailing) {
                cout << "  🎉 全部及格！大家都很棒！" << endl;
            }
        } else if (subChoice == 4) {
            return;
        } else {
            cout << "⚠️  输入错误！" << endl;
        }
    }
}

// ---- 3c. 知识问答模块 ----
void moduleC_quiz() {
    // 题库：使用结构体数组存储题目
    Question quiz[5] = {
        {"C++中，用于输出的关键字是什么？",
         {"A. print", "B. cout", "C. printf", "D. output"},
         'B'},
        {"以下哪个循环会至少执行一次？",
         {"A. for", "B. while", "C. do-while", "D. if"},
         'C'},
        {"数组的下标通常从哪个数字开始？",
         {"A. 1", "B. 0", "C. -1", "D. 随机"},
         'B'},
        {"struct 关键字用于定义什么？",
         {"A. 变量", "B. 函数", "C. 循环", "D. 结构体"},
         'D'},
        {"冒泡排序中，每一轮会把什么元素'浮'到最后？",
         {"A. 最小的", "B. 随机的", "C. 最大的", "D. 中间的"},
         'C'}
    };

    const int QN = 5;
    int score = 0;
    char answer;

    cout << "\n===== 🏆 知识问答挑战 =====" << endl;
    cout << "共 " << QN << " 道题，每题20分，满分100分！" << endl;
    cout << "请输入你的答案（A/B/C/D）：" << endl;

    // 随机打乱题目顺序（简单的Fisher-Yates洗牌）
    for (int i = QN - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Question temp = quiz[i];
        quiz[i] = quiz[j];
        quiz[j] = temp;
    }

    for (int i = 0; i < QN; i++) {
        cout << "\n第" << (i + 1) << "题：" << quiz[i].question << endl;
        for (int j = 0; j < 4; j++) {
            cout << "  " << quiz[i].options[j] << endl;
        }
        cout << "你的答案：";
        cin >> answer;

        // 统一转大写，方便比较
        if (answer >= 'a' && answer <= 'd') {
            answer = answer - 'a' + 'A';
        }

        if (answer == quiz[i].answer) {
            cout << "✅ 正确！+20分" << endl;
            score += 20;
        } else {
            cout << "❌ 错误！正确答案是 " << quiz[i].answer << endl;
        }
    }

    // 输出成绩和评语
    cout << "\n===== 📊 最终成绩 =====" << endl;
    cout << "得分：" << score << " / 100" << endl;
    if (score == 100) {
        cout << "🏆 满分！你是知识达人！" << endl;
    } else if (score >= 80) {
        cout << "👍 优秀！知识储备很不错！" << endl;
    } else if (score >= 60) {
        cout << "📚 及格了，再复习一下会更好！" << endl;
    } else {
        cout << "💪 加油！多看看之前的课程吧！" << endl;
    }
}

// ---- 程序3主入口 ----
void program3_graduationProject() {
    srand(time(0));  // 初始化随机数种子

    // 通讯录数据（跨模块使用）
    Contact contacts[50];  // 最多50个联系人
    int contactCount = 0;  // 当前联系人数

    int choice;
    while (true) {
        cout << "\n╔══════════════════════════════════════╗" << endl;
        cout << "║    🎓 班级信息总管 —— 毕业作品     ║" << endl;
        cout << "╠══════════════════════════════════════╣" << endl;
        cout << "║  1. 📇 通讯录管理                  ║" << endl;
        cout << "║  2. 📊 成绩管理                    ║" << endl;
        cout << "║  3. 🏆 知识问答挑战                ║" << endl;
        cout << "║  4. 📋 查看系统信息                ║" << endl;
        cout << "║  5. 🚪 退出系统                    ║" << endl;
        cout << "╚══════════════════════════════════════╝" << endl;
        cout << "请输入你的选择(1-5)：";
        cin >> choice;

        switch (choice) {
            case 1:
                moduleA_contacts(contacts, contactCount);
                break;
            case 2:
                moduleB_scores();
                break;
            case 3:
                moduleC_quiz();
                break;
            case 4:
                cout << "\n╔══════════════════════════════════════╗" << endl;
                cout << "║         📋 系统信息                ║" << endl;
                cout << "╠══════════════════════════════════════╣" << endl;
                cout << "║  程序名：班级信息总管 v1.0         ║" << endl;
                cout << "║  开发者：（你的名字）              ║" << endl;
                cout << "║  知识点：结构体、排序、随机数      ║" << endl;
                cout << "║          循环、条件判断、数组      ║" << endl;
                cout << "║          函数、字符串、菜单交互    ║" << endl;
                cout << "╠══════════════════════════════════════╣" << endl;
                cout << "║  这是第48课的毕业作品！            ║" << endl;
                cout << "║  恭喜完成C++趣味学习全部课程！     ║" << endl;
                cout << "╚══════════════════════════════════════╝" << endl;
                break;
            case 5:
                cout << "\n╔══════════════════════════════════════╗" << endl;
                cout << "║                                      ║" << endl;
                cout << "║   🎓 恭喜毕业！                     ║" << endl;
                cout << "║                                      ║" << endl;
                cout << "║   你已完成C++趣味学习全部48节课！   ║" << endl;
                cout << "║   从第一行 Hello World 到今天，     ║" << endl;
                cout << "║   你已经是一名真正的程序员了！      ║" << endl;
                cout << "║                                      ║" << endl;
                cout << "║   继续前进，编程的世界无限广阔！    ║" << endl;
                cout << "║                                      ║" << endl;
                cout << "╚══════════════════════════════════════╝" << endl;
                cout << "\n👋 再见，未来的编程之星！✨" << endl;
                return;
            default:
                cout << "⚠️  输入错误，请输入1~5之间的数字！" << endl;
        }
    }
}

// ============================================================
// main 函数：程序入口
// 依次运行所有演示程序
// ============================================================
int main() {
    // ========================================================
    // 设置输出中文（在不同操作系统中可能需要调整）
    // Windows: system("chcp 65001");
    // 本程序在支持 UTF-8 的终端中直接运行即可
    // ========================================================

    cout << "\n";
    cout << "╔══════════════════════════════════════════════════════════╗" << endl;
    cout << "║                                                          ║" << endl;
    cout << "║   🎓 第48课：我的编程毕业礼 —— 综合复习                ║" << endl;
    cout << "║   C++ 趣味学习课程 —— 毕业课                            ║" << endl;
    cout << "║                                                          ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════╝" << endl;

    cout << "\n欢迎来到C++趣味学习的最后一课！" << endl;
    cout << "本程序将依次演示三个综合项目：" << endl;
    cout << "\n  📚 程序1：学生成绩管理系统" << endl;
    cout << "      结构体 + 冒泡排序 + 选择排序 + 菜单交互 + 统计分析" << endl;
    cout << "\n  🧰 程序2：多功能工具箱" << endl;
    cout << "      猜数字游戏 + 成绩排序器 + 简易计算器 + 数组分析器" << endl;
    cout << "\n  🎓 程序3：班级信息总管（毕业作品示例）" << endl;
    cout << "      通讯录管理 + 成绩管理 + 知识问答 + 系统信息" << endl;

    cout << "\n═══════════════════════════════════════════════════════════" << endl;
    int mainChoice;
    cout << "\n请选择要运行的演示程序：" << endl;
    cout << "  1 - 学生成绩管理系统" << endl;
    cout << "  2 - 多功能工具箱" << endl;
    cout << "  3 - 班级信息总管（毕业作品）" << endl;
    cout << "  0 - 退出" << endl;
    cout << "请输入选择：";
    cin >> mainChoice;

    switch (mainChoice) {
        case 1:
            program1_studentManagement();
            break;
        case 2:
            program2_toolbox();
            break;
        case 3:
            program3_graduationProject();
            break;
        case 0:
            cout << "\n再见！" << endl;
            break;
        default:
            cout << "\n⚠️  无效选择，程序退出。" << endl;
    }

    cout << "\n╔══════════════════════════════════════════════════════════╗" << endl;
    cout << "║                                                          ║" << endl;
    cout << "║   🎉 本课所有演示程序结束！                             ║" << endl;
    cout << "║                                                          ║" << endl;
    cout << "║   恭喜你完成了C++趣味学习全部48节课！                   ║" << endl;
    cout << "║   从 Hello World 到毕业作品，你真的很了不起！           ║" << endl;
    cout << "║                                                          ║" << endl;
    cout << "║   编程之路才刚刚开始，继续加油！ 🚀                     ║" << endl;
    cout << "║                                                          ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════╝" << endl;
    cout << endl;

    return 0;
}
