/*
 * 第2课：存储数据 —— 结构体与向量
 * 项目：任务管理器 v2.0（数据存储版）
 *
 * 知识点：
 *   1. struct 结构体定义
 *   2. vector<T> 动态数组容器
 *   3. push_back / size / empty
 *   4. 全局数据共享
 *   5. 格式化表格输出
 *
 * 编译方法：
 *   g++ -std=c++11 lesson_cli_02_数据存储.cpp -o lesson_cli_02_数据存储
 *   运行：./lesson_cli_02_数据存储
 */

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

// ---------- 数据结构 ----------
struct Task {
    int id;           // 任务编号（自动分配）
    string title;     // 任务标题
    bool done;        // 是否完成
    int priority;     // 优先级（1=高, 2=中, 3=低）
};

// ---------- 全局数据 ----------
vector<Task> tasks;   // 存储所有任务的动态数组
int nextId = 1;       // 下一个可用的任务编号

// ---------- 菜单显示 ----------
void showMenu() {
    cout << "\n╔══════════════════════════╗" << endl;
    cout << "║    📋 任务管理器 v2.0    ║" << endl;
    cout << "╠══════════════════════════╣" << endl;
    cout << "║  1. ➕ 添加新任务        ║" << endl;
    cout << "║  2. 📋 查看所有任务      ║" << endl;
    cout << "║  3. ✅ 标记任务完成      ║" << endl;
    cout << "║  4. 🗑️  删除任务         ║" << endl;
    cout << "║  0. 🚪 退出程序          ║" << endl;
    cout << "╚══════════════════════════╝" << endl;
    cout << "请输入你的选择：";
}

// ---------- 功能1：添加任务 ----------
void addTask() {
    Task t;
    t.id = nextId++;      // 自动分配编号，然后编号+1
    t.done = false;       // 新任务默认未完成

    cout << "请输入任务标题：";
    cin.ignore();
    getline(cin, t.title);

    cout << "优先级（1=高🔴, 2=中🟡, 3=低🟢）：";
    cin >> t.priority;

    // 校验优先级输入
    if (t.priority < 1 || t.priority > 3) {
        t.priority = 2;  // 默认中等优先级
        cout << "  输入无效，已设为默认优先级（中）。" << endl;
    }

    tasks.push_back(t);  // 将任务添加到列表
    cout << "✓ 任务添加成功！" << endl;
    cout << "  编号：" << t.id << " | 标题：" << t.title
         << " | 优先级：";
    if (t.priority == 1) cout << "高🔴";
    else if (t.priority == 2) cout << "中🟡";
    else cout << "低🟢";
    cout << endl;
}

// ---------- 功能2：查看所有任务 ----------
void viewTasks() {
    if (tasks.empty()) {
        cout << "\n📭 暂无任务！" << endl;
        cout << "  试试选择「1. 添加新任务」来创建第一个任务吧！" << endl;
        return;
    }

    // 表头
    cout << "\n┌──────┬──────────────────────────┬────────────┬────────┐" << endl;
    cout << "│ 编号 │        任务标题          │    状态    │ 优先级 │" << endl;
    cout << "├──────┼──────────────────────────┼────────────┼────────┤" << endl;

    // 表体：遍历每个任务
    for (int i = 0; i < tasks.size(); i++) {
        Task& t = tasks[i];

        cout << "│ " << setw(3) << t.id << "  │  " << t.title;

        // 手动对齐：中文在等宽字体中约占 2 个英文字符宽度
        int displayLen = t.title.length() * 2;
        for (int s = 0; s < 28 - displayLen; s++) cout << " ";

        cout << "│  " << (t.done ? "✅ 已完成" : "⬜ 未完成") << "  │";

        // 优先级显示
        if (t.priority == 1) cout << "   🔴 高  │" << endl;
        else if (t.priority == 2) cout << "   🟡 中  │" << endl;
        else cout << "   🟢 低  │" << endl;
    }

    cout << "└──────┴──────────────────────────┴────────────┴────────┘" << endl;

    // 统计信息
    int doneCount = 0;
    for (int i = 0; i < tasks.size(); i++) {
        if (tasks[i].done) doneCount++;
    }
    cout << "📊 共 " << tasks.size() << " 个任务（"
         << doneCount << " 已完成, "
         << tasks.size() - doneCount << " 未完成）" << endl;
}

// ---------- 占位功能（第3课实现） ----------
void markDone() {
    if (tasks.empty()) {
        cout << "📭 暂无任务！" << endl;
        return;
    }
    cout << "  ⏳ [功能开发中] 标记完成功能将在第3课实现！" << endl;
    cout << "     当前已有 " << tasks.size() << " 个任务等待管理。" << endl;
}

void deleteTask() {
    if (tasks.empty()) {
        cout << "📭 暂无任务！" << endl;
        return;
    }
    cout << "  ⏳ [功能开发中] 删除任务功能将在第3课实现！" << endl;
    cout << "     当前已有 " << tasks.size() << " 个任务。" << endl;
}

// ---------- 主函数 ----------
int main() {
    int choice;

    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║     第2课：存储数据 —— 结构体与向量             ║" << endl;
    cout << "║     C++ 4节小课：从零构建 CLI 任务管理器         ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    do {
        showMenu();
        cin >> choice;
        cin.ignore();  // 清空缓冲区

        cout << endl;

        switch (choice) {
            case 1: addTask();    break;
            case 2: viewTasks();  break;
            case 3: markDone();   break;
            case 4: deleteTask(); break;
            case 0:
                cout << "👋 感谢使用任务管理器，再见！" << endl;
                cout << "   当前共有 " << tasks.size() << " 个任务。" << endl;
                cout << "   下节课我们将实现标记完成和删除功能！" << endl;
                break;
            default:
                cout << "❌ 无效选择！请输入 0~4 之间的数字。" << endl;
                break;
        }
    } while (choice != 0);

    return 0;
}
