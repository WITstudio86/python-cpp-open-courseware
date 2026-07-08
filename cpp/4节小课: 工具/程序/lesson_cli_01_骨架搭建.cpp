/*
 * 第1课：搭建骨架 —— CLI 菜单与输入处理
 * 项目：任务管理器 v1.0（骨架版）
 *
 * 知识点：
 *   1. CLI 程序的基本结构（主循环 + 菜单 + switch）
 *   2. do-while 循环
 *   3. 用户输入处理（cin >>, getline, cin.ignore）
 *   4. 函数封装与增量开发
 *
 * 编译方法：
 *   g++ -std=c++11 lesson_cli_01_骨架搭建.cpp -o lesson_cli_01_骨架搭建
 *   运行：./lesson_cli_01_骨架搭建
 */

#include <iostream>
#include <string>
using namespace std;

// ---------- 菜单显示 ----------
void showMenu() {
    cout << "\n╔══════════════════════════╗" << endl;
    cout << "║    📋 任务管理器 v1.0    ║" << endl;
    cout << "╠══════════════════════════╣" << endl;
    cout << "║  1. ➕ 添加新任务        ║" << endl;
    cout << "║  2. 📋 查看所有任务      ║" << endl;
    cout << "║  3. ✅ 标记任务完成      ║" << endl;
    cout << "║  4. 🗑️  删除任务         ║" << endl;
    cout << "║  0. 🚪 退出程序          ║" << endl;
    cout << "╚══════════════════════════╝" << endl;
    cout << "请输入你的选择：";
}

// ---------- 占位功能函数（后续课程逐步实现） ----------
void addTask() {
    cout << "  ⏳ [功能开发中] 添加任务功能将在第2课实现！" << endl;
    cout << "     届时你可以输入任务标题和优先级。" << endl;
}

void viewTasks() {
    cout << "  ⏳ [功能开发中] 查看任务功能将在第2课实现！" << endl;
    cout << "     届时你可以看到所有任务的表格列表。" << endl;
}

void markDone() {
    cout << "  ⏳ [功能开发中] 标记完成功能将在第3课实现！" << endl;
    cout << "     届时你可以标记任务为「已完成」或「未完成」。" << endl;
}

void deleteTask() {
    cout << "  ⏳ [功能开发中] 删除任务功能将在第3课实现！" << endl;
    cout << "     届时你可以删除不需要的任务。" << endl;
}

// ---------- 主函数 ----------
int main() {
    int choice;

    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║     第1课：搭建骨架 —— CLI 菜单与输入处理       ║" << endl;
    cout << "║     C++ 4节小课：从零构建 CLI 任务管理器         ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    do {
        showMenu();
        cin >> choice;

        // ★ 关键：清空输入缓冲区，防止影响后续 getline 读取
        cin.ignore();

        cout << endl;

        switch (choice) {
            case 1: addTask();    break;
            case 2: viewTasks();  break;
            case 3: markDone();   break;
            case 4: deleteTask(); break;
            case 0:
                cout << "👋 感谢使用任务管理器，再见！" << endl;
                cout << "   下节课我们将添加真正的数据存储功能！" << endl;
                break;
            default:
                cout << "❌ 无效选择！请输入 0~4 之间的数字。" << endl;
                cout << "   提示：输入菜单中显示的数字来选择功能。" << endl;
                break;
        }
    } while (choice != 0);

    return 0;
}
