/*
 * 第3课：操作数据 —— 查找、筛选与统计
 * 项目：任务管理器 v3.0（完整操作版）
 *
 * 知识点：
 *   1. 线性查找（findTaskById）
 *   2. vector 的 erase 删除
 *   3. 数据筛选（只显示未完成任务）
 *   4. 数据统计（完成率、优先级分布）
 *   5. 二次确认（删除前询问）
 *
 * 编译方法：
 *   g++ -std=c++11 lesson_cli_03_数据操作.cpp -o lesson_cli_03_数据操作
 *   运行：./lesson_cli_03_数据操作
 */

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

// ---------- 数据结构 ----------
struct Task {
    int id;
    string title;
    bool done;
    int priority;  // 1=高, 2=中, 3=低
};

// ---------- 全局数据 ----------
vector<Task> tasks;
int nextId = 1;

// ---------- 辅助函数：根据ID查找任务，返回下标；找不到返回 -1 ----------
int findTaskById(int id) {
    for (int i = 0; i < tasks.size(); i++) {
        if (tasks[i].id == id) {
            return i;
        }
    }
    return -1;
}

// ---------- 菜单显示（新增选项 5、6） ----------
void showMenu() {
    cout << "\n╔══════════════════════════════╗" << endl;
    cout << "║     📋 任务管理器 v3.0       ║" << endl;
    cout << "╠══════════════════════════════╣" << endl;
    cout << "║  1. ➕ 添加新任务            ║" << endl;
    cout << "║  2. 📋 查看所有任务          ║" << endl;
    cout << "║  3. ✅ 标记任务完成/未完成   ║" << endl;
    cout << "║  4. 🗑️  删除任务             ║" << endl;
    cout << "║  5. 🔍 查看待完成任务        ║" << endl;
    cout << "║  6. 📊 任务统计              ║" << endl;
    cout << "║  0. 🚪 退出程序              ║" << endl;
    cout << "╚══════════════════════════════╝" << endl;
    cout << "请输入你的选择：";
}

// ---------- 功能1：添加任务 ----------
void addTask() {
    Task t;
    t.id = nextId++;
    t.done = false;

    cout << "请输入任务标题：";
    cin.ignore();
    getline(cin, t.title);

    cout << "优先级（1=高🔴, 2=中🟡, 3=低🟢）：";
    cin >> t.priority;
    if (t.priority < 1 || t.priority > 3) t.priority = 2;

    tasks.push_back(t);
    cout << "✓ 任务添加成功！（编号：" << t.id << "，标题：" << t.title << "）" << endl;
}

// ---------- 功能2：查看所有任务 ----------
void viewTasks() {
    if (tasks.empty()) {
        cout << "\n📭 暂无任务！试试「1. 添加新任务」吧！" << endl;
        return;
    }

    cout << "\n┌──────┬──────────────────────────┬────────────┬────────┐" << endl;
    cout << "│ 编号 │        任务标题          │    状态    │ 优先级 │" << endl;
    cout << "├──────┼──────────────────────────┼────────────┼────────┤" << endl;

    for (int i = 0; i < tasks.size(); i++) {
        Task& t = tasks[i];
        cout << "│ " << setw(3) << t.id << "  │  " << t.title;

        int displayLen = t.title.length() * 2;
        for (int s = 0; s < 28 - displayLen; s++) cout << " ";

        cout << "│  " << (t.done ? "✅ 已完成" : "⬜ 未完成") << "  │";
        if (t.priority == 1) cout << "   🔴高  │" << endl;
        else if (t.priority == 2) cout << "   🟡中  │" << endl;
        else cout << "   🟢低  │" << endl;
    }

    cout << "└──────┴──────────────────────────┴────────────┴────────┘" << endl;

    int doneCount = 0;
    for (int i = 0; i < tasks.size(); i++) {
        if (tasks[i].done) doneCount++;
    }
    cout << "📊 共 " << tasks.size() << " 个任务（已完成 " << doneCount
         << "，未完成 " << tasks.size() - doneCount << "）" << endl;
}

// ---------- 功能3：标记任务完成/取消完成 ----------
void markDone() {
    if (tasks.empty()) {
        cout << "📭 暂无任务！" << endl;
        return;
    }

    int id;
    cout << "请输入要切换状态的任务编号：";
    cin >> id;

    int idx = findTaskById(id);
    if (idx == -1) {
        cout << "❌ 未找到编号为 " << id << " 的任务！" << endl;
        cout << "   提示：请使用「2. 查看所有任务」确认正确的任务编号。" << endl;
        return;
    }

    // 切换状态：! 运算符取反
    tasks[idx].done = !tasks[idx].done;

    cout << "✓ 任务 #" << id << "「" << tasks[idx].title << "」";
    if (tasks[idx].done)
        cout << " 已标记为 ✅ 已完成" << endl;
    else
        cout << " 已标记为 ⬜ 未完成" << endl;
}

// ---------- 功能4：删除任务 ----------
void deleteTask() {
    if (tasks.empty()) {
        cout << "📭 暂无任务！" << endl;
        return;
    }

    int id;
    cout << "请输入要删除的任务编号：";
    cin >> id;

    int idx = findTaskById(id);
    if (idx == -1) {
        cout << "❌ 未找到编号为 " << id << " 的任务！" << endl;
        return;
    }

    // 二次确认，防止误删
    cout << "\n⚠️  确定要删除以下任务吗？" << endl;
    cout << "    编号：" << tasks[idx].id << endl;
    cout << "    标题：" << tasks[idx].title << endl;
    cout << "    状态：" << (tasks[idx].done ? "已完成" : "未完成") << endl;
    cout << "\n确认删除？(y/n)：";
    char confirm;
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        string deletedTitle = tasks[idx].title;  // 暂存标题用于提示
        tasks.erase(tasks.begin() + idx);         // 删除指定位置元素
        cout << "✓ 任务「" << deletedTitle << "」已删除！" << endl;
    } else {
        cout << "  已取消删除。" << endl;
    }
}

// ---------- 功能5：查看待完成任务（筛选） ----------
void viewPending() {
    if (tasks.empty()) {
        cout << "\n📭 暂无任务！" << endl;
        return;
    }

    int count = 0;
    cout << "\n📋 待完成的任务：" << endl;
    cout << "─────────────────────────────────────" << endl;

    for (int i = 0; i < tasks.size(); i++) {
        if (!tasks[i].done) {   // ★ 筛选：只显示未完成的
            count++;
            cout << "  [" << tasks[i].id << "] " << tasks[i].title;
            // 优先级图标
            if (tasks[i].priority == 1) cout << " 🔴";
            else if (tasks[i].priority == 2) cout << " 🟡";
            else cout << " 🟢";
            cout << endl;
        }
    }

    if (count == 0) {
        cout << "  🎉 太棒了！所有任务都已完成！" << endl;
    } else {
        cout << "─────────────────────────────────────" << endl;
        cout << "  共 " << count << " 个待完成任务。" << endl;
    }
}

// ---------- 功能6：任务统计 ----------
void showStats() {
    if (tasks.empty()) {
        cout << "\n📭 暂无任务，无法统计！" << endl;
        return;
    }

    int total = tasks.size();
    int done = 0;
    int high = 0, mid = 0, low = 0;

    for (int i = 0; i < tasks.size(); i++) {
        if (tasks[i].done) done++;
        if (tasks[i].priority == 1) high++;
        else if (tasks[i].priority == 2) mid++;
        else low++;
    }

    int percent = (total > 0) ? (done * 100 / total) : 0;

    cout << "\n╔═══════════════╦════════╗" << endl;
    cout << "║  📊 任务统计  ║  数据  ║" << endl;
    cout << "╠═══════════════╬════════╣" << endl;
    cout << "║  总任务数     ║    " << setw(2) << total << "  ║" << endl;
    cout << "║  已完成       ║    " << setw(2) << done << "  ║" << endl;
    cout << "║  未完成       ║    " << setw(2) << total - done << "  ║" << endl;
    cout << "║  完成率       ║   " << setw(2) << percent << "% ║" << endl;
    cout << "╠═══════════════╬════════╣" << endl;
    cout << "║  🔴 高优先级  ║    " << setw(2) << high << "  ║" << endl;
    cout << "║  🟡 中优先级  ║    " << setw(2) << mid << "  ║" << endl;
    cout << "║  🟢 低优先级  ║    " << setw(2) << low << "  ║" << endl;
    cout << "╚═══════════════╩════════╝" << endl;

    // 进度条
    cout << "\n完成进度：";
    cout << "[";
    int barLen = 20;
    int filled = (total > 0) ? (done * barLen / total) : 0;
    for (int i = 0; i < barLen; i++) {
        if (i < filled) cout << "█";
        else cout << "░";
    }
    cout << "] " << percent << "%" << endl;
}

// ---------- 主函数 ----------
int main() {
    int choice;

    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║     第3课：操作数据 —— 查找、筛选与统计         ║" << endl;
    cout << "║     C++ 4节小课：从零构建 CLI 任务管理器         ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    do {
        showMenu();
        cin >> choice;
        cin.ignore();  // 清空缓冲区

        cout << endl;

        switch (choice) {
            case 1: addTask();     break;
            case 2: viewTasks();   break;
            case 3: markDone();    break;
            case 4: deleteTask();  break;
            case 5: viewPending(); break;
            case 6: showStats();   break;
            case 0:
                cout << "👋 感谢使用任务管理器，再见！" << endl;
                cout << "   提示：当前数据不会保存，下节课将添加文件存储！" << endl;
                break;
            default:
                cout << "❌ 无效选择！请输入 0~6 之间的数字。" << endl;
                break;
        }
    } while (choice != 0);

    return 0;
}
