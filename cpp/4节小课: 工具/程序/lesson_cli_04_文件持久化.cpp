/*
 * 第4课：持久化 —— 文件读写与完整发布
 * 项目：任务管理器 v4.0（完整发布版）✅
 *
 * 知识点：
 *   1. ofstream 写文件
 *   2. ifstream 读文件
 *   3. 字符串解析（find + substr + stoi）
 *   4. 自动保存 / 自动加载
 *   5. ANSI 颜色转义码
 *   6. 完整项目发布
 *
 * 编译方法：
 *   g++ -std=c++11 lesson_cli_04_文件持久化.cpp -o todo
 *   运行：./todo
 *
 * 数据文件：tasks.txt（自动创建，与程序同目录）
 * 格式示例：1|完成数学作业|0|1
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

// ===== ANSI 颜色常量 =====
#ifdef _WIN32
    // Windows 旧版控制台可能不支持 ANSI，设为空
    const string RED    = "";
    const string GREEN  = "";
    const string YELLOW = "";
    const string CYAN   = "";
    const string RESET  = "";
#else
    const string RED    = "\033[31m";
    const string GREEN  = "\033[32m";
    const string YELLOW = "\033[33m";
    const string CYAN   = "\033[36m";
    const string RESET  = "\033[0m";
#endif

// ===== 数据结构 =====
struct Task {
    int id;
    string title;
    bool done;
    int priority;  // 1=高, 2=中, 3=低
};

// ===== 全局数据 =====
vector<Task> tasks;
int nextId = 1;

// ===== 辅助函数：根据ID查找任务 =====
int findTaskById(int id) {
    for (int i = 0; i < tasks.size(); i++) {
        if (tasks[i].id == id) return i;
    }
    return -1;
}

// ===== 文件操作 =====

// 保存数据到文件
void saveToFile() {
    ofstream file("tasks.txt");
    if (!file.is_open()) {
        cout << RED << "❌ 无法保存文件！请检查磁盘空间或权限。" << RESET << endl;
        return;
    }

    // 格式：id|title|done(0/1)|priority
    for (int i = 0; i < tasks.size(); i++) {
        file << tasks[i].id << "|"
             << tasks[i].title << "|"
             << tasks[i].done << "|"
             << tasks[i].priority << endl;
    }

    file.close();
}

// 从文件加载数据
void loadFromFile() {
    ifstream file("tasks.txt");
    if (!file.is_open()) {
        cout << YELLOW << "📝 首次使用，未找到数据文件。" << RESET << endl;
        cout << "   程序将在当前目录创建 tasks.txt 保存你的任务数据。" << endl;
        return;
    }

    tasks.clear();
    string line;
    int lineNum = 0;

    while (getline(file, line)) {
        lineNum++;
        if (line.empty()) continue;  // 跳过空行

        // 解析格式：id|title|done|priority
        int p1 = line.find('|');
        int p2 = line.find('|', p1 + 1);
        int p3 = line.find('|', p2 + 1);

        // 验证格式完整性
        if (p1 == string::npos || p2 == string::npos || p3 == string::npos) {
            cout << YELLOW << "⚠ 第 " << lineNum << " 行格式错误，已跳过。" << RESET << endl;
            continue;
        }

        Task t;
        t.id       = stoi(line.substr(0, p1));
        t.title    = line.substr(p1 + 1, p2 - p1 - 1);
        t.done     = (line.substr(p2 + 1, p3 - p2 - 1) == "1");
        t.priority = stoi(line.substr(p3 + 1));

        tasks.push_back(t);
    }

    file.close();

    // 更新 nextId
    if (!tasks.empty()) {
        nextId = tasks.back().id + 1;
    }

    cout << GREEN << "✓ 已从文件加载 " << tasks.size() << " 条任务。" << RESET << endl;
}

// ===== 菜单显示 =====
void showMenu() {
    cout << "\n" << CYAN;
    cout << "╔══════════════════════════════╗" << endl;
    cout << "║     📋 任务管理器 v4.0       ║" << endl;
    cout << "╠══════════════════════════════╣" << endl;
    cout << "║  1. ➕ 添加新任务            ║" << endl;
    cout << "║  2. 📋 查看所有任务          ║" << endl;
    cout << "║  3. ✅ 标记任务完成/未完成   ║" << endl;
    cout << "║  4. 🗑️  删除任务             ║" << endl;
    cout << "║  5. 🔍 查看待完成任务        ║" << endl;
    cout << "║  6. 📊 任务统计              ║" << endl;
    cout << "║  0. 🚪 退出程序              ║" << endl;
    cout << "╚══════════════════════════════╝" << RESET << endl;
    cout << "请输入你的选择：";
}

// ===== 功能1：添加任务（含自动保存） =====
void addTask() {
    Task t;
    t.id = nextId++;
    t.done = false;

    cout << "请输入任务标题：";
    cin.ignore();
    getline(cin, t.title);

    // 检查标题中是否包含分隔符
    if (t.title.find('|') != string::npos) {
        cout << YELLOW << "⚠ 标题不能包含 '|' 字符，已自动替换为 '-'。" << RESET << endl;
        for (int i = 0; i < t.title.length(); i++) {
            if (t.title[i] == '|') t.title[i] = '-';
        }
    }

    cout << "优先级（1=高🔴, 2=中🟡, 3=低🟢）：";
    cin >> t.priority;
    if (t.priority < 1 || t.priority > 3) t.priority = 2;

    tasks.push_back(t);

    // ★ 自动保存
    saveToFile();

    cout << GREEN << "✓ 任务添加成功！（编号：" << t.id << "，标题：" << t.title << "）" << RESET << endl;
}

// ===== 功能2：查看所有任务 =====
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

        if (t.done)
            cout << "│  " << GREEN << "✅ 已完成" << RESET << "  │";
        else
            cout << "│  ⬜ 未完成  │";

        if (t.priority == 1) cout << "   🔴高  │" << endl;
        else if (t.priority == 2) cout << "   🟡中  │" << endl;
        else cout << "   🟢低  │" << endl;
    }

    cout << "└──────┴──────────────────────────┴────────────┴────────┘" << endl;

    int doneCount = 0;
    for (int i = 0; i < tasks.size(); i++) {
        if (tasks[i].done) doneCount++;
    }
    cout << "📊 共 " << tasks.size() << " 个任务（"
         << GREEN << doneCount << RESET << " 已完成, "
         << tasks.size() - doneCount << " 未完成）" << endl;
}

// ===== 功能3：标记任务完成/取消完成（含自动保存） =====
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
        cout << RED << "❌ 未找到编号为 " << id << " 的任务！" << RESET << endl;
        return;
    }

    tasks[idx].done = !tasks[idx].done;

    // ★ 自动保存
    saveToFile();

    cout << GREEN << "✓ 任务 #" << id << "「" << tasks[idx].title << "」";
    if (tasks[idx].done)
        cout << " 已标记为 ✅ 已完成" << RESET << endl;
    else
        cout << " 已标记为 ⬜ 未完成" << RESET << endl;
}

// ===== 功能4：删除任务（含自动保存） =====
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
        cout << RED << "❌ 未找到编号为 " << id << " 的任务！" << RESET << endl;
        return;
    }

    // 二次确认
    cout << "\n⚠️  确定要删除以下任务吗？" << endl;
    cout << "    编号：" << tasks[idx].id << endl;
    cout << "    标题：" << tasks[idx].title << endl;
    cout << "    状态：" << (tasks[idx].done ? "已完成" : "未完成") << endl;
    cout << "\n确认删除？(y/n)：";
    char confirm;
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        string deletedTitle = tasks[idx].title;
        tasks.erase(tasks.begin() + idx);

        // ★ 自动保存
        saveToFile();

        cout << GREEN << "✓ 任务「" << deletedTitle << "」已删除！" << RESET << endl;
    } else {
        cout << "  已取消删除。" << endl;
    }
}

// ===== 功能5：查看待完成任务（筛选） =====
void viewPending() {
    if (tasks.empty()) {
        cout << "\n📭 暂无任务！" << endl;
        return;
    }

    int count = 0;
    cout << "\n📋 待完成的任务：" << endl;
    cout << "─────────────────────────────────────" << endl;

    for (int i = 0; i < tasks.size(); i++) {
        if (!tasks[i].done) {
            count++;
            cout << "  [" << tasks[i].id << "] " << tasks[i].title;
            if (tasks[i].priority == 1) cout << " " << RED << "🔴" << RESET;
            else if (tasks[i].priority == 2) cout << " " << YELLOW << "🟡" << RESET;
            else cout << " 🟢";
            cout << endl;
        }
    }

    if (count == 0) {
        cout << "  " << GREEN << "🎉 太棒了！所有任务都已完成！" << RESET << endl;
    } else {
        cout << "─────────────────────────────────────" << endl;
        cout << "  共 " << count << " 个待完成任务。" << endl;
    }
}

// ===== 功能6：任务统计 =====
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
        if (i < filled) cout << GREEN << "█" << RESET;
        else cout << "░";
    }
    cout << "] " << (percent >= 50 ? GREEN : YELLOW) << percent << "%" << RESET << endl;
}

// ===== 主函数 =====
int main() {
    int choice;

    cout << CYAN;
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║     第4课：持久化 —— 文件读写与完整发布         ║" << endl;
    cout << "║     C++ 4节小课：从零构建 CLI 任务管理器         ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << RESET << endl;

    // ★ 启动时自动加载数据
    loadFromFile();

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
                // ★ 退出前保存
                saveToFile();
                cout << GREEN << "👋 数据已保存到 tasks.txt，再见！" << RESET << endl;
                cout << "\n🎉 恭喜你完成了全部 4 节课的学习！" << endl;
                cout << "   你现在可以用 ./todo 命令随时管理你的任务了！" << endl;
                break;
            default:
                cout << RED << "❌ 无效选择！请输入 0~6 之间的数字。" << RESET << endl;
                break;
        }
    } while (choice != 0);

    return 0;
}
