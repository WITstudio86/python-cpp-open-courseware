/*
 * ============================================================
 * 第47课：知识问答王——题库系统
 * C++趣味学习课程
 * ============================================================
 *
 * 本课学习内容：
 *   1. 设计题库结构体（题干、选项、答案一体化）
 *   2. 结构体数组的初始化（嵌套花括号）
 *   3. 随机出题（不重复抽题）
 *   4. 答案验证（大小写统一处理）
 *   5. 计分统计与评语（正确率、总分、等级评语）
 *
 * 本文件包含以下程序：
 *   程序1：简单问答系统 —— 3道题，顺序答题，入门演示
 *   程序2：完整知识竞赛 —— 8道题，随机顺序，计分统计，含解析
 *   程序3：练习题参考答案 —— 自定义题库，随机抽2题
 *
 * 编译方式（以 g++ 为例）：
 *   g++ -std=c++11 lesson47_quiz_system.cpp -o lesson47
 *   ./lesson47
 * ============================================================
 */

#include <iostream>
#include <string>
#include <cstdlib>   // 包含 rand() 和 srand()
#include <ctime>     // 包含 time()，用于随机种子
#include <cctype>    // 包含 toupper()，用于答案大小写转换
using namespace std;

// ============================================================
// 第一部分：结构体定义
// ============================================================

// 基础题目结构体 —— 用于简单问答
struct Question {
    string question;       // 题干
    string options[4];    // 四个选项（索引 0/1/2/3 对应 A/B/C/D）
    char answer;          // 正确答案（'A'/'B'/'C'/'D'）
};

// 完整题目结构体 —— 比基础版多了"解析"字段
struct FullQuestion {
    string question;       // 题干
    string options[4];    // 四个选项
    char answer;          // 正确答案
    string explanation;   // 答案解析（答完后展示，帮助学习）
};

// 玩家信息结构体 —— 用于课后挑战任务
struct Player {
    string name;          // 玩家姓名
    int score;            // 得分
    int correctCount;     // 答对题数
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

// 显示一道题目（包含题干和四个选项）
void displayQuestion(const FullQuestion& q, int questionNum) {
    cout << "\n第 " << questionNum << " 题：" << q.question << endl;
    for (int j = 0; j < 4; j++) {
        cout << "  " << q.options[j] << endl;
    }
}

// 获取用户答案并统一转为大写
char getUserAnswer() {
    char ans;
    cout << "请输入你的答案（A/B/C/D）：";
    cin >> ans;
    return toupper(ans);  // 转成大写，防止用户输入小写
}

// 显示最终答题成绩
void showFinalResult(int correct, int total, int score) {
    double accuracy = (double)correct / total * 100;
    cout << "\n========================================" << endl;
    cout << "           答 题 结 束" << endl;
    cout << "========================================" << endl;
    cout << "📊 总题数：" << total << " 题" << endl;
    cout << "✅ 答对数：" << correct << " 题" << endl;
    cout << "📈 正确率：" << accuracy << "%" << endl;
    cout << "⭐ 总得分：" << score << " 分（满分 " << total * 10 << " 分）" << endl;
    cout << "----------------------------------------" << endl;
    if (accuracy == 100) {
        cout << "🏆 满分！你是当之无愧的「知识问答王」！" << endl;
    } else if (accuracy >= 80) {
        cout << "🥇 非常优秀！你是「知识达人」！" << endl;
    } else if (accuracy >= 60) {
        cout << "🥈 表现不错，继续努力争上游！" << endl;
    } else if (accuracy >= 40) {
        cout << "🥉 还有进步空间，多读书哦！" << endl;
    } else {
        cout << "💪 不要气馁，学习是长期积累的过程！" << endl;
    }
    cout << "========================================\n" << endl;
}

// ============================================================
// 程序1：简单问答系统
// 只有3道题，按顺序出题，帮助理解基本流程
// 每道题答对 +10分，答错不扣分
// ============================================================
void program1_simpleQuiz() {
    printSeparator("【程序1】简单问答系统 —— 3道题，顺序答题");

    // ---- 1. 初始化题库（结构体数组） ----
    // 使用嵌套花括号：外层是题目，内层是选项数组
    Question quiz[3] = {
        {"中国的首都是哪里？",
         {"A. 上海", "B. 北京", "C. 广州", "D. 深圳"},
         'B'},
        {"1 + 1 等于几？",
         {"A. 1", "B. 2", "C. 3", "D. 4"},
         'B'},
        {"太阳从哪个方向升起？",
         {"A. 东边", "B. 西边", "C. 南边", "D. 北边"},
         'A'}
    };

    // ---- 2. 答题变量 ----
    int score = 0;           // 总得分
    int correctCount = 0;    // 答对题数
    const int TOTAL = 3;     // 总题数

    // ---- 3. 欢迎界面 ----
    cout << "╔════════════════════════════════╗" << endl;
    cout << "║    知识问答王 —— 简单挑战    ║" << endl;
    cout << "╚════════════════════════════════╝" << endl;
    cout << "共有 " << TOTAL << " 道题，每道题10分。准备好了吗？\n" << endl;

    // ---- 4. 逐题问答 ----
    for (int i = 0; i < TOTAL; i++) {
        // 显示题目
        cout << "第 " << i + 1 << " 题：" << quiz[i].question << endl;
        for (int j = 0; j < 4; j++) {
            cout << "  " << quiz[i].options[j] << endl;
        }

        // 获取用户答案
        char userAnswer;
        cout << "请输入你的答案（A/B/C/D）：";
        cin >> userAnswer;
        userAnswer = toupper(userAnswer);  // 统一转大写

        // 判断正误并计分
        if (userAnswer == quiz[i].answer) {
            cout << "✅ 回答正确！+10分\n" << endl;
            score += 10;
            correctCount++;
        } else {
            cout << "❌ 回答错误！正确答案是 " << quiz[i].answer << "\n" << endl;
        }
    }

    // ---- 5. 输出成绩 ----
    cout << "========== 答题结束 ==========" << endl;
    cout << "答对：" << correctCount << " / " << TOTAL << " 题" << endl;
    cout << "总分：" << score << " 分" << endl;
    double accuracy = (double)correctCount / TOTAL * 100;
    cout << "正确率：" << accuracy << "%" << endl;

    if (accuracy == 100) {
        cout << "🏆 满分！你是知识问答王！" << endl;
    } else if (accuracy >= 66) {
        cout << "👍 不错哦！继续加油！" << endl;
    } else {
        cout << "💪 多多学习，下次一定行！" << endl;
    }
}

// ============================================================
// 程序2：完整知识竞赛
// 8道题，随机顺序不重复，计分统计，含答案解析
// 综合运用：结构体数组、随机数、标记数组、循环、条件判断
// ============================================================
void program2_fullCompetition() {
    printSeparator("【程序2】完整知识竞赛 —— 随机出题，计分统计");

    // ---- 1. 初始化随机数生成器 ----
    // srand(time(0)) 用当前时间做种子，保证每次运行结果不同
    srand(time(0));

    // ---- 2. 初始化完整题库（带解析） ----
    const int TOTAL = 8;
    FullQuestion quiz[TOTAL] = {
        {"中国的首都是哪里？",
         {"A. 上海", "B. 北京", "C. 广州", "D. 深圳"},
         'B',
         "北京是中华人民共和国的首都，是一座拥有三千多年历史的古都。"},

        {"地球上最大的海洋是？",
         {"A. 大西洋", "B. 印度洋", "C. 太平洋", "D. 北冰洋"},
         'C',
         "太平洋是世界上面积最大、最深的海洋，面积约1.8亿平方千米。"},

        {"一年有多少天？（平年）",
         {"A. 360天", "B. 365天", "C. 366天", "D. 350天"},
         'B',
         "平年有365天，闰年有366天。能被4整除但不能被100整除的年份是闰年。"},

        {"以下哪个不是四大发明？",
         {"A. 造纸术", "B. 指南针", "C. 蒸汽机", "D. 火药"},
         'C',
         "中国古代四大发明是：造纸术、指南针、火药、印刷术。蒸汽机是西方工业革命的产物。"},

        {"水的化学式是什么？",
         {"A. CO₂", "B. H₂O", "C. O₂", "D. NaCl"},
         'B',
         "水由两个氢原子（H）和一个氧原子（O）组成，化学式为H₂O。"},

        {"《静夜思》的作者是谁？",
         {"A. 杜甫", "B. 白居易", "C. 李白", "D. 王维"},
         'C',
         "《静夜思》是唐代大诗人李白的名作：「床前明月光，疑是地上霜。」"},

        {"人体最大的器官是？",
         {"A. 心脏", "B. 肝脏", "C. 皮肤", "D. 大脑"},
         'C',
         "皮肤是人体最大的器官，一个成年人的皮肤面积约为1.5~2平方米。"},

        {"光年是什么单位？",
         {"A. 时间单位", "B. 距离单位", "C. 速度单位", "D. 重量单位"},
         'B',
         "光年是距离单位，表示光在真空中一年所走的距离，约9.46万亿千米。"}
    };

    // ---- 3. 准备变量 ----
    int score = 0;
    int correctCount = 0;
    int questionOrder[TOTAL];   // 存储随机出题顺序
    bool used[TOTAL] = {false}; // 标记某题是否已出过（初始全false）

    // ---- 4. 随机生成出题顺序（不重复） ----
    // 思路：每次随机选一个没用过的题，标记为已使用
    for (int i = 0; i < TOTAL; i++) {
        int idx;
        do {
            idx = rand() % TOTAL;  // 随机 0 ~ TOTAL-1
        } while (used[idx]);       // 如果已用过，重新选
        questionOrder[i] = idx;    // 记录到顺序数组
        used[idx] = true;          // 标记为已使用
    }

    // ---- 5. 欢迎界面 ----
    cout << "╔════════════════════════════════════════╗" << endl;
    cout << "║     🏆 知识问答王 —— 趣味知识竞赛   ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    cout << "\n欢迎参加知识问答竞赛！" << endl;
    cout << "题库共有 " << TOTAL << " 道题，将随机抽取。" << endl;
    cout << "每道题10分，答对加分，答错不扣分。\n" << endl;
    cout << "准备好了吗？按 Enter 键开始..." << endl;
    cin.get();  // 等待用户按回车

    // ---- 6. 逐题问答 ----
    for (int i = 0; i < TOTAL; i++) {
        int qIndex = questionOrder[i];  // 按随机顺序取出当前题目下标

        // 显示题目
        displayQuestion(quiz[qIndex], i + 1);

        // 获取答案
        char userAnswer = getUserAnswer();

        // 判断正误
        if (userAnswer == quiz[qIndex].answer) {
            cout << "✅ 回答正确！+10分" << endl;
            score += 10;
            correctCount++;
        } else {
            cout << "❌ 回答错误！正确答案是 " << quiz[qIndex].answer << endl;
        }

        // 显示解析（无论对错，帮助学习）
        cout << "💡 解析：" << quiz[qIndex].explanation << endl;
    }

    // ---- 7. 显示最终成绩 ----
    showFinalResult(correctCount, TOTAL, score);
}

// ============================================================
// 程序3：练习题参考答案 —— 自定义题库
// 演示如何创建自己的题库，并随机抽取2道题进行问答
// 对应课文中"练习2：补全程序"的完整版
// ============================================================
void program3_customQuiz() {
    printSeparator("【程序3】自定义题库 —— 随机抽2题（练习题参考答案）");

    // 初始化随机数
    srand(time(0));

    // ---- 自定义题库 ----
    // 这里展示了如何创建自己的题目。你可以按这个格式添加更多题目！
    Question quiz[3] = {
        {"一年有几个季节？",
         {"A. 2个", "B. 3个", "C. 4个", "D. 5个"},
         'C'},
        {"一周有几天？",
         {"A. 5天", "B. 6天", "C. 7天", "D. 8天"},
         'C'},
        {"一个月最多有多少天？",
         {"A. 28天", "B. 29天", "C. 30天", "D. 31天"},
         'D'}
    };

    int score = 0;
    bool used[3] = {false};

    cout << "╔════════════════════════════════╗" << endl;
    cout << "║     自定义题库 —— 随机答题   ║" << endl;
    cout << "╚════════════════════════════════╝" << endl;
    cout << "从3道题中随机抽取2道。\n" << endl;

    // ---- 随机抽取2道题，不重复 ----
    for (int i = 0; i < 2; i++) {
        int idx;
        do {
            idx = rand() % 3;
        } while (used[idx]);
        used[idx] = true;

        // 显示题目
        cout << "第 " << i + 1 << " 题：" << quiz[idx].question << endl;
        for (int j = 0; j < 4; j++) {
            cout << "  " << quiz[idx].options[j] << endl;
        }

        // 获取答案
        char userAnswer;
        cout << "你的答案：";
        cin >> userAnswer;
        userAnswer = toupper(userAnswer);

        // 判断正误
        if (userAnswer == quiz[idx].answer) {
            cout << "✅ 正确！+10分\n" << endl;
            score += 10;
        } else {
            cout << "❌ 错误！正确答案是 " << quiz[idx].answer << "\n" << endl;
        }
    }

    // ---- 输出最终成绩 ----
    cout << "========== 成绩 ==========" << endl;
    cout << "总得分：" << score << " 分（满分20分）" << endl;

    if (score == 20) {
        cout << "🏆 满分！太厉害了！" << endl;
    } else if (score == 10) {
        cout << "👍 答对一半，继续加油！" << endl;
    } else {
        cout << "💪 别灰心，多练习就会进步的！" << endl;
    }
}

// ============================================================
// 程序4：挑战任务 —— 带难度分级的题库（进阶版）
// 给每道题添加 level 字段（1=简单, 2=中等, 3=困难）
// 用户选择难度后只出对应难度的题目
// ============================================================
void program4_levelChallenge() {
    printSeparator("【挑战任务】带难度分级的题库竞赛");

    srand(time(0));

    // ---- 定义带难度的题目结构体 ----
    struct LevelQuestion {
        string question;
        string options[4];
        char answer;
        string explanation;
        int level;   // 1=简单, 2=中等, 3=困难
    };

    // ---- 初始化分级题库 ----
    LevelQuestion quiz[] = {
        // level 1: 简单题
        {"1 + 1 = ?",
         {"A. 1", "B. 2", "C. 3", "D. 4"},
         'B', "最基础的数学题。", 1},
        {"太阳从哪个方向升起？",
         {"A. 东边", "B. 西边", "C. 南边", "D. 北边"},
         'A', "东升西落是自然规律。", 1},
        {"一周有几天？",
         {"A. 5天", "B. 6天", "C. 7天", "D. 8天"},
         'C', "星期一到星期日共7天。", 1},

        // level 2: 中等题
        {"中国的首都是？",
         {"A. 上海", "B. 北京", "C. 广州", "D. 深圳"},
         'B', "北京是中国的首都。", 2},
        {"水的化学式是？",
         {"A. CO₂", "B. H₂O", "C. O₂", "D. NaCl"},
         'B', "水由H和O组成，化学式H₂O。", 2},
        {"《静夜思》的作者是？",
         {"A. 杜甫", "B. 白居易", "C. 李白", "D. 王维"},
         'C', "李白是唐代大诗人。", 2},

        // level 3: 困难题
        {"光年是什么单位？",
         {"A. 时间", "B. 距离", "C. 速度", "D. 重量"},
         'B', "光年是距离单位，约9.46万亿千米。", 3},
        {"人体最大的器官是？",
         {"A. 心脏", "B. 肝脏", "C. 皮肤", "D. 大脑"},
         'C', "皮肤面积约1.5~2平方米。", 3},
        {"以下哪个不是四大发明？",
         {"A. 造纸术", "B. 指南针", "C. 蒸汽机", "D. 火药"},
         'C', "蒸汽机是工业革命的产物。", 3}
    };

    const int TOTAL = sizeof(quiz) / sizeof(quiz[0]);  // 自动计算题库大小

    // ---- 用户选择难度 ----
    int chosenLevel;
    cout << "请选择难度等级：" << endl;
    cout << "  1. 🌱 简单" << endl;
    cout << "  2. 🌿 中等" << endl;
    cout << "  3. 🌳 困难" << endl;
    cout << "请输入你的选择（1/2/3）：";
    cin >> chosenLevel;

    if (chosenLevel < 1 || chosenLevel > 3) {
        cout << "输入无效，默认选择简单难度。" << endl;
        chosenLevel = 1;
    }

    // ---- 筛选出对应难度的题目下标 ----
    int filteredIndex[TOTAL];  // 存储符合难度的题目下标
    int filteredCount = 0;     // 符合条件的题目数量
    for (int i = 0; i < TOTAL; i++) {
        if (quiz[i].level == chosenLevel) {
            filteredIndex[filteredCount] = i;
            filteredCount++;
        }
    }

    if (filteredCount == 0) {
        cout << "该难度下没有题目！" << endl;
        return;
    }

    cout << "\n该难度下共有 " << filteredCount << " 道题。开始答题！\n" << endl;

    // ---- 随机不重复出题 ----
    int score = 0;
    int correctCount = 0;
    bool used[TOTAL] = {false};

    for (int i = 0; i < filteredCount; i++) {
        int pick;
        do {
            pick = rand() % filteredCount;
        } while (used[pick]);
        used[pick] = true;

        int qIndex = filteredIndex[pick];  // 实际题目下标

        // 显示题目（直接输出，不使用 displayQuestion 避免类型强转）
        cout << "\n第 " << i + 1 << " 题：" << quiz[qIndex].question << endl;
        for (int j = 0; j < 4; j++) {
            cout << "  " << quiz[qIndex].options[j] << endl;
        }

        char userAnswer = getUserAnswer();
        if (userAnswer == quiz[qIndex].answer) {
            cout << "✅ 正确！+10分" << endl;
            score += 10;
            correctCount++;
        } else {
            cout << "❌ 错误！正确答案是 " << quiz[qIndex].answer << endl;
        }
        cout << "💡 " << quiz[qIndex].explanation << endl;
    }

    showFinalResult(correctCount, filteredCount, score);
}

// ============================================================
// main 函数：程序入口
// 依次运行所有演示程序
// ============================================================
int main() {
    // 设置输出中文（根据不同操作系统可能需要调整）
    // Windows 用户可能需要取消下面的注释：
    // system("chcp 65001");
    // 本程序在支持 UTF-8 的终端中直接运行即可

    cout << "╔══════════════════════════════════════════════════════════╗" << endl;
    cout << "║     第47课：知识问答王 —— 题库系统                     ║" << endl;
    cout << "║     C++ 趣味学习课程                                    ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════╝" << endl;
    cout << "\n本程序将依次演示：" << endl;
    cout << "  1. 简单问答系统 —— 3道题顺序答题" << endl;
    cout << "  2. 完整知识竞赛 —— 随机出题，计分统计" << endl;
    cout << "  3. 练习题参考答案 —— 自定义题库" << endl;
    cout << "  4. 挑战任务 —— 难度分级问答" << endl;
    cout << endl;

    // ---- 依次运行各个程序 ----
    program1_simpleQuiz();

    cout << "\n按 Enter 键继续观看下一个程序...";
    cin.get();  // 消耗残留换行符
    cin.get();  // 等待用户按回车

    program2_fullCompetition();

    cout << "\n按 Enter 键继续观看下一个程序...";
    cin.get();

    program3_customQuiz();

    cout << "\n按 Enter 键继续观看下一个程序...";
    cin.get();

    program4_levelChallenge();

    cout << "\n╔══════════════════════════════════════════════════════════╗" << endl;
    cout << "║     本课所有程序演示完毕！                              ║" << endl;
    cout << "║     下一课预告：魔法图书馆 —— 文件读写入门             ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════╝" << endl;

    return 0;
}
