/*
 * 第25课：数据排排队——数组初识
 * 课程项目：制作班级花名册
 *
 * 知识点：
 *   1. 数组的声明与初始化
 *   2. 使用下标访问数组元素
 *   3. 数组越界的概念
 *   4. 配合循环遍历数组
 *
 * 编译方法：
 *   g++ -std=c++11 lesson25_数组初识.cpp -o lesson25_数组初识
 *   运行：./lesson25_数组初识
 */

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// ---------- 示例1：数组的基本声明与初始化 ----------
void ejemplo1_declaracionBasica() {
    cout << "╔══════════════════════════════════════╗" << endl;
    cout << "║   示例1：数组的基本声明与初始化     ║" << endl;
    cout << "╚══════════════════════════════════════╝" << endl;
    cout << endl;

    // 1.1 声明整数数组（未初始化，内容是垃圾值）
    int scores[40];
    cout << "1.1 声明了一个能存40个整数的数组：int scores[40];" << endl;
    cout << "    （注意：未初始化时，元素的值是不确定的）" << endl;
    cout << endl;

    // 1.2 声明并完全初始化
    int numbers[5] = {10, 20, 30, 40, 50};
    cout << "1.2 声明并初始化：int numbers[5] = {10, 20, 30, 40, 50};" << endl;
    cout << "    数组内容：";
    for (int i = 0; i < 5; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl << endl;

    // 1.3 部分初始化（剩余自动为0）
    int nums[5] = {1, 2};
    cout << "1.3 部分初始化：int nums[5] = {1, 2};" << endl;
    cout << "    数组内容：";
    for (int i = 0; i < 5; i++) {
        cout << nums[i] << " ";
    }
    cout << "  ← 后面3个元素自动为0" << endl;
    cout << endl;

    // 1.4 省略大小的初始化
    int grades[] = {90, 85, 92, 78, 95};
    cout << "1.4 省略大小：int grades[] = {90, 85, 92, 78, 95};" << endl;
    cout << "    编译器自动确定大小为：";
    // sizeof(grades) 返回整个数组的字节数，sizeof(grades[0]) 返回一个元素的字节数
    cout << sizeof(grades) / sizeof(grades[0]) << " 个元素" << endl;
    cout << endl;

    // 1.5 全部初始化为0
    int zeros[100] = {0};
    cout << "1.5 全部初始化为0：int zeros[100] = {0};" << endl;
    cout << "    前5个元素：";
    for (int i = 0; i < 5; i++) {
        cout << zeros[i] << " ";
    }
    cout << "（全部都是0）" << endl;
    cout << endl;

    // 1.6 字符串数组
    string names[3] = {"小明", "小红", "小刚"};
    cout << "1.6 字符串数组：string names[3] = {\"小明\", \"小红\", \"小刚\"};" << endl;
    cout << "    内容：";
    for (int i = 0; i < 3; i++) {
        cout << names[i] << " ";
    }
    cout << endl;
    cout << endl;
}

// ---------- 示例2：使用下标访问数组元素 ----------
void ejemplo2_accesoPorSubindice() {
    cout << "╔══════════════════════════════════════╗" << endl;
    cout << "║   示例2：使用下标访问数组元素       ║" << endl;
    cout << "╚══════════════════════════════════════╝" << endl;
    cout << endl;

    int arr[5] = {10, 20, 30, 40, 50};

    cout << "数组元素：{10, 20, 30, 40, 50}" << endl;
    cout << endl;

    // 2.1 逐个访问
    cout << "2.1 逐个访问每个元素：" << endl;
    cout << "    arr[0] = " << arr[0] << "  （第1个元素）" << endl;
    cout << "    arr[1] = " << arr[1] << "  （第2个元素）" << endl;
    cout << "    arr[2] = " << arr[2] << "  （第3个元素）" << endl;
    cout << "    arr[3] = " << arr[3] << "  （第4个元素）" << endl;
    cout << "    arr[4] = " << arr[4] << "  （第5个元素）" << endl;
    cout << endl;

    // 2.2 修改元素
    cout << "2.2 修改元素值：" << endl;
    cout << "    修改前 arr[2] = " << arr[2] << endl;
    arr[2] = 100;
    cout << "    执行 arr[2] = 100; 后 → arr[2] = " << arr[2] << endl;
    cout << endl;

    // 2.3 下标与"第几个"的关系
    cout << "2.3 下标 vs 第几个：" << endl;
    cout << "    ┌────────┬─────────┬──────────┐" << endl;
    cout << "    │ 第几个 │  下标   │   值     │" << endl;
    cout << "    ├────────┼─────────┼──────────┤" << endl;
    for (int i = 0; i < 5; i++) {
        // 使用setw进行对齐
        cout << "    │   " << i + 1 << "    │   arr[" << i << "] │";
        if (arr[i] >= 100) {
            cout << "   " << arr[i] << "    │" << endl;
        } else {
            cout << "    " << arr[i] << "     │" << endl;
        }
    }
    cout << "    └────────┴─────────┴──────────┘" << endl;
    cout << endl;

    // 2.4 演示数组越界的危险（仅作概念说明，不实际执行）
    cout << "2.4 数组越界警告：" << endl;
    cout << "    数组 arr 有5个元素，有效下标范围：0 ~ 4" << endl;
    cout << "    arr[5] 或 arr[-1] 会导致越界访问！" << endl;
    cout << "    这就像在5个人的队伍里喊'第6位同学'——没有这个人！" << endl;
    cout << "    越界访问可能导致程序崩溃或得到奇怪的值。" << endl;
    cout << endl;
}

// ---------- 示例3：班级花名册程序 ----------
void ejemplo3_rosterDeClase() {
    cout << "╔══════════════════════════════════════╗" << endl;
    cout << "║   示例3：制作班级花名册             ║" << endl;
    cout << "╚══════════════════════════════════════╝" << endl;
    cout << endl;

    // 花名册数据
    string names[5] = {"小明", "小红", "小刚", "小丽", "小华"};
    int ages[5] = {11, 10, 12, 11, 10};
    string hobbies[5] = {"踢足球", "画画", "编程", "跳舞", "阅读"};

    // 显示标题
    cout << "    ╔═══════════════════════════════════════════╗" << endl;
    cout << "    ║         三（1）班 班级花名册              ║" << endl;
    cout << "    ╠════╦═══════════╦══════╦══════════════════╣" << endl;
    cout << "    ║ 编号║   姓名    ║ 年龄 ║     爱好         ║" << endl;
    cout << "    ╠════╬═══════════╬══════╬══════════════════╣" << endl;

    for (int i = 0; i < 5; i++) {
        cout << "    ║  " << i + 1 << "  ║  " << names[i];
        // 手动对齐：中文在等宽字体中占2个字符宽度
        int nameLen = names[i].length() * 2;  // 一个中文约等于2个英文字符宽度
        for (int s = 0; s < 9 - nameLen; s++) {
            cout << " ";
        }
        cout << "║   " << ages[i] << "  ║  " << hobbies[i];
        int hobbyLen = hobbies[i].length() * 2;
        for (int s = 0; s < 15 - hobbyLen; s++) {
            cout << " ";
        }
        cout << "║" << endl;
    }
    cout << "    ╚════╩═══════════╩══════╩══════════════════╝" << endl;
    cout << endl;

    // 查找功能
    cout << "查找第3位同学的信息：" << endl;
    int idx = 2;  // 下标 = 编号 - 1
    cout << "    姓名：" << names[idx] << endl;
    cout << "    年龄：" << ages[idx] << "岁" << endl;
    cout << "    爱好：" << hobbies[idx] << endl;
    cout << endl;

    // 修改花名册
    cout << "小刚转学了，新同学'小强'加入！" << endl;
    names[2] = "小强";
    ages[2] = 12;
    hobbies[2] = "打篮球";
    cout << "修改后第3位同学：" << names[2] << "，" << ages[2] << "岁，爱好" << hobbies[2] << endl;
    cout << endl;

    // 显示更新后的简易花名册
    cout << "更新后的花名册：" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "    " << i + 1 << ". " << names[i]
             << "（" << ages[i] << "岁）" << endl;
    }
    cout << endl;
}

// ---------- 练习答案 ----------
void ejercicio1_respuesta() {
    cout << "╔══════════════════════════════════════╗" << endl;
    cout << "║   练习1答案：填空补全               ║" << endl;
    cout << "╚══════════════════════════════════════╝" << endl;
    cout << endl;

    cout << "补全后的代码：" << endl;
    cout << "┌─────────────────────────────────────────────┐" << endl;
    cout << "│ int arr[7] = {1, 2, 3, 4, 5, 6, 7};        │" << endl;
    cout << "│ for (int i = 0; i < 7; i++) {               │" << endl;
    cout << "│     cout << \"arr[\" << i << \"] = \" << arr[i]; │" << endl;
    cout << "│ }                                           │" << endl;
    cout << "└─────────────────────────────────────────────┘" << endl;
    cout << endl;

    // 实际运行
    int arr[7] = {1, 2, 3, 4, 5, 6, 7};
    cout << "运行结果：" << endl;
    for (int i = 0; i < 7; i++) {
        cout << "    arr[" << i << "] = " << arr[i] << endl;
    }
    cout << endl;
}

void ejercicio2_respuesta() {
    cout << "╔══════════════════════════════════════╗" << endl;
    cout << "║   练习2答案：纠错小侦探             ║" << endl;
    cout << "╚══════════════════════════════════════╝" << endl;
    cout << endl;

    cout << "错误1：cout << arr[3];" << endl;
    cout << "    数组 arr 有3个元素，下标范围是 0~2。" << endl;
    cout << "    arr[3] 访问的是第4个元素（不存在），会导致越界！" << endl;
    cout << "    如果想输出最后一个元素，应该写 arr[2]。" << endl;
    cout << endl;

    cout << "错误2：cout << arr[1, 2];" << endl;
    cout << "    在C++中，arr[1, 2] 中的逗号是'逗号运算符'，" << endl;
    cout << "    它的值是最后一个表达式，即 arr[2]。" << endl;
    cout << "    正确的写法是：cout << arr[1] << \" \" << arr[2];" << endl;
    cout << endl;

    cout << "改正后的代码：" << endl;
    int arr[3] = {1, 2, 3};
    cout << "    正确的输出最后一个元素：cout << arr[2];  → 结果：" << arr[2] << endl;
    cout << "    正确的输出第2、3个元素：cout << arr[1] << \" \" << arr[2]; → 结果：" << arr[1] << " " << arr[2] << endl;
    cout << endl;
}

// ---------- 挑战任务：完整的班级花名册程序 ----------
void desafio_rosterCompleto() {
    cout << "╔══════════════════════════════════════╗" << endl;
    cout << "║   挑战任务：完整的班级花名册程序     ║" << endl;
    cout << "╚══════════════════════════════════════╝" << endl;
    cout << endl;

    const int MAX = 100;       // 最多支持100人
    string roster[MAX];        // 花名册数组
    int count;                 // 实际人数

    // 输入人数
    cout << "请输入班级人数（最多" << MAX << "人）：";
    cin >> count;

    // 验证输入
    if (count <= 0 || count > MAX) {
        cout << "人数超出范围，程序退出。" << endl;
        return;
    }

    // 清空输入缓冲区
    cin.ignore();

    // 输入每个同学的名字
    cout << "\n请逐个输入同学的名字：" << endl;
    for (int i = 0; i < count; i++) {
        cout << "    第" << i + 1 << "位同学：";
        getline(cin, roster[i]);
    }

    // 显示花名册
    cout << "\n╔═════════════════════════╗" << endl;
    cout << "║      班级花名册         ║" << endl;
    cout << "╠════╦════════════════════╣" << endl;
    cout << "║ 编号║       姓名        ║" << endl;
    cout << "╠════╬════════════════════╣" << endl;
    for (int i = 0; i < count; i++) {
        cout << "║  " << i + 1;
        if (i + 1 < 10) cout << " ";
        cout << " ║  " << roster[i];
        int nameDisplayLen = roster[i].length() * 2;
        for (int s = 0; s < 16 - nameDisplayLen; s++) {
            cout << " ";
        }
        cout << "║" << endl;
    }
    cout << "╚════╩════════════════════╝" << endl;
    cout << "\n当前班级共有 " << count << " 位同学。" << endl;

    // 修改功能
    char choice;
    cout << "\n是否需要修改某位同学的名字？(y/n)：";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        int num;
        cout << "请输入要修改的同学编号（1~" << count << "）：";
        cin >> num;

        if (num >= 1 && num <= count) {
            cin.ignore();  // 清空缓冲区
            cout << "当前第" << num << "位同学是：" << roster[num - 1] << endl;
            cout << "请输入新的名字：";
            getline(cin, roster[num - 1]);
            cout << "✓ 修改成功！" << endl;

            // 显示更新后的花名册
            cout << "\n更新后的花名册：" << endl;
            for (int i = 0; i < count; i++) {
                cout << "    " << i + 1 << ". " << roster[i] << endl;
            }
        } else {
            cout << "编号超出范围！" << endl;
        }
    }

    cout << "\n感谢使用班级花名册程序！再见！" << endl;
    cout << endl;
}

// ---------- 主函数 ----------
int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║     第25课：数据排排队——数组初识                ║" << endl;
    cout << "║     C++ 趣味学习——制作班级花名册                ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;
    cout << endl;

    int opcion;

    do {
        cout << "请选择要运行的功能：" << endl;
        cout << "    1. 示例1：数组的基本声明与初始化" << endl;
        cout << "    2. 示例2：使用下标访问数组元素" << endl;
        cout << "    3. 示例3：班级花名册程序" << endl;
        cout << "    4. 练习1答案：填空补全" << endl;
        cout << "    5. 练习2答案：纠错小侦探" << endl;
        cout << "    6. 挑战任务：完整的班级花名册程序" << endl;
        cout << "    0. 退出程序" << endl;
        cout << "请输入数字选择：";
        cin >> opcion;
        cout << endl;

        switch (opcion) {
            case 1:
                ejemplo1_declaracionBasica();
                break;
            case 2:
                ejemplo2_accesoPorSubindice();
                break;
            case 3:
                ejemplo3_rosterDeClase();
                break;
            case 4:
                ejercicio1_respuesta();
                break;
            case 5:
                ejercicio2_respuesta();
                break;
            case 6:
                desafio_rosterCompleto();
                break;
            case 0:
                cout << "再见！记得完成课后练习哦！" << endl;
                break;
            default:
                cout << "无效选择，请重新输入！" << endl;
        }
    } while (opcion != 0);

    return 0;
}
