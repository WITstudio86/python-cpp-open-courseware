/*
 * 第44课：终极排序大赛——排序综合
 * 主题：冒泡排序 vs 选择排序对比、结构体排序、多条件排序
 * 项目：成绩排名大比拼
 * 适用：中小学C++趣味学习
 * 日期：2026年
 */

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// ==========================================
// 结构体定义
// ==========================================

// 学生结构体：用于成绩排名
struct Student {
    string name;      // 姓名
    int age;          // 年龄
    double score;     // 成绩
};

// 运动员结构体：用于运动会排行榜
struct Athlete {
    string name;      // 姓名
    int classId;      // 班级编号
    int gold;         // 金牌数
    int silver;       // 银牌数
    int bronze;       // 铜牌数
    int total;        // 奖牌总数
};

// ==========================================
// 辅助函数：打印分隔线
// ==========================================
void printLine(string title) {
    cout << "\n========================================" << endl;
    cout << "  " << title << endl;
    cout << "========================================" << endl;
}

// ==========================================
// 辅助函数：打印整数数组
// ==========================================
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// ==========================================
// 示例1：冒泡排序 vs 选择排序对比（带计数器）
// ==========================================
void example1_sortComparison() {
    printLine("示例1：冒泡排序 vs 选择排序对比");

    // 准备两个完全相同的数组，分别用两种排序
    int bubbleArr[] = {9, 5, 7, 3, 1, 8, 6, 4, 2, 0};
    int selectArr[] = {9, 5, 7, 3, 1, 8, 6, 4, 2, 0};
    int n = 10;

    // ---- 冒泡排序（升序） ----
    int bubbleCompares = 0;  // 比较次数计数器
    int bubbleSwaps = 0;     // 交换次数计数器

    cout << "\n冒泡排序过程（原数组：9 5 7 3 1 8 6 4 2 0）" << endl;

    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;  // 优化标记：本轮是否发生过交换
        for (int j = 0; j < n - 1 - i; j++) {
            bubbleCompares++;   // 每次比较，计数器+1
            if (bubbleArr[j] > bubbleArr[j+1]) {
                // 交换相邻元素
                int temp = bubbleArr[j];
                bubbleArr[j] = bubbleArr[j+1];
                bubbleArr[j+1] = temp;
                bubbleSwaps++;  // 每次交换，计数器+1
                swapped = true;
            }
        }
        // 如果本轮没有发生任何交换，说明已经有序，提前结束
        if (!swapped) {
            cout << "  第" << i + 1 << "轮后已有序，提前结束！" << endl;
            break;
        }
    }

    cout << "冒泡排序结果：";
    printArray(bubbleArr, n);
    cout << "冒泡排序 - 比较次数：" << bubbleCompares << " 次" << endl;
    cout << "冒泡排序 - 交换次数：" << bubbleSwaps << " 次" << endl;

    // ---- 选择排序（升序） ----
    int selectCompares = 0;  // 比较次数计数器
    int selectSwaps = 0;     // 交换次数计数器

    cout << "\n选择排序过程" << endl;

    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;  // 假设当前位置是最小值
        for (int j = i + 1; j < n; j++) {
            selectCompares++;  // 每次比较，计数器+1
            if (selectArr[j] < selectArr[minIndex]) {
                minIndex = j;  // 找到更小的，更新最小值位置
            }
        }
        // 如果最小值不在当前位置，则交换
        if (minIndex != i) {
            int temp = selectArr[i];
            selectArr[i] = selectArr[minIndex];
            selectArr[minIndex] = temp;
            selectSwaps++;  // 每轮最多交换一次
        }
    }

    cout << "选择排序结果：";
    printArray(selectArr, n);
    cout << "选择排序 - 比较次数：" << selectCompares << " 次" << endl;
    cout << "选择排序 - 交换次数：" << selectSwaps << " 次" << endl;

    // ---- 对比总结 ----
    cout << "\n========== 对比总结 ==========" << endl;
    cout << "排列指标        | 冒泡排序 | 选择排序" << endl;
    cout << "----------------|---------|---------" << endl;
    cout << "比较次数        | " << bubbleCompares << " 次    | " << selectCompares << " 次" << endl;
    cout << "交换次数        | " << bubbleSwaps << " 次     | " << selectSwaps << " 次" << endl;
    cout << "是否稳定        | 稳定    | 不稳定" << endl;
    cout << "提前结束        | 支持    | 不支持" << endl;

    cout << "\n 分析：" << endl;
    cout << "  比较次数相同，但选择排序的交换次数少得多！" << endl;
    cout << "  冒泡排序每发现一次逆序就交换，选择排序每轮只交换一次。" << endl;
}

// ==========================================
// 示例2：学生结构体数组按成绩排序（冒泡排序）
// ==========================================
void example2_studentRanking() {
    printLine("示例2：学生成绩排名（结构体数组 + 冒泡排序）");

    const int N = 6;

    // 创建学生数组并初始化
    Student students[N] = {
        {"小明", 12, 88.5},
        {"小红", 11, 95.0},
        {"小刚", 13, 76.0},
        {"小丽", 12, 95.0},   // 和小红成绩相同，测试稳定性
        {"小华", 14, 82.5},
        {"小强", 11, 69.0}
    };

    // 输出排序前的名单
    cout << "\n------------ 排序前的学生名单 ------------" << endl;
    cout << "序号  姓名    年龄    成绩" << endl;
    cout << "----------------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        cout << " " << i + 1 << "    "
             << students[i].name << "    "
             << students[i].age << "岁    "
             << students[i].score << "分" << endl;
    }

    // ==========================================
    // 核心：结构体排序
    // 比较的是结构体的 score 成员
    // 但交换的是整个 Student 结构体变量
    // ==========================================
    // 使用冒泡排序，按成绩从高到低排列（降序）
    // 降序的条件：前面的成绩 < 后面的成绩 → 交换（把低的往后移）
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1 - i; j++) {
            // 关键：比较的是 .score 成员
            if (students[j].score < students[j+1].score) {
                // 关键：交换的是整个结构体！
                Student temp = students[j];
                students[j] = students[j+1];
                students[j+1] = temp;
            }
        }
    }

    // 输出排序后的排行榜
    cout << "\n========== 🏅 成绩排行榜（降序） ==========" << endl;
    cout << "排名  姓名    年龄    成绩    荣誉" << endl;
    cout << "----------------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        // 判断荣誉等级
        string honor;
        if (students[i].score >= 90) {
            honor = "🏆 优秀";
        } else if (students[i].score >= 80) {
            honor = "⭐ 良好";
        } else if (students[i].score >= 60) {
            honor = " 及格";
        } else {
            honor = " 加油";
        }

        cout << "第" << i + 1 << "名 "
             << students[i].name << "    "
             << students[i].age << "岁    "
             << students[i].score << "分   "
             << honor << endl;
    }

    // 观察排序稳定性
    cout << "\n 稳定性观察：" << endl;
    cout << "  小红(11岁,95分) 在原始数组中排在小丽(12岁,95分)前面" << endl;
    cout << "  冒泡排序后，小红仍然在小丽前面 → 冒泡排序是稳定的！" << endl;

    // 计算平均分
    double totalScore = 0;
    for (int i = 0; i < N; i++) {
        totalScore += students[i].score;
    }
    double average = totalScore / N;

    cout << "\n------------ 成绩统计 ------------" << endl;
    cout << fixed << setprecision(1);
    cout << "总人数：" << N << " 人" << endl;
    cout << "总分：" << totalScore << " 分" << endl;
    cout << "平均分：" << average << " 分" << endl;
    cout << "最高分：" << students[0].name << " " << students[0].score << " 分" << endl;
    cout << "最低分：" << students[N-1].name << " " << students[N-1].score << " 分" << endl;
}

// ==========================================
// 示例3：多条件结构体排序
// 规则：先按成绩降序，成绩相同按年龄升序
// ==========================================
void example3_multiConditionSorting() {
    printLine("示例3：多条件排序（成绩降序 + 年龄升序）");

    const int N = 8;

    // 创建学生数组（包含成绩相同、年龄不同的情况）
    Student students[N] = {
        {"张伟",  13, 92.0},
        {"李娜",  12, 88.5},
        {"王芳",  14, 92.0},   // 和张伟成绩相同，年龄不同
        {"赵雷",  11, 88.5},   // 和李娜成绩相同，年龄不同
        {"陈静",  12, 76.0},
        {"杨洋",  13, 95.0},
        {"刘涛",  11, 95.0},   // 和杨洋成绩相同，年龄不同
        {"周杰",  14, 82.5}
    };

    cout << "\n------------ 排序前的学生名单 ------------" << endl;
    for (int i = 0; i < N; i++) {
        cout << i + 1 << ". " << students[i].name
             << " 年龄" << students[i].age << "岁"
             << " 成绩" << students[i].score << "分" << endl;
    }

    // ==========================================
    // 多条件冒泡排序
    // 第一条件（主条件）：成绩从高到低（降序）
    // 第二条件（次条件）：成绩相同时，年龄从小到大（升序）
    // ==========================================
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1 - i; j++) {
            // 先判断主条件：成绩
            if (students[j].score < students[j+1].score) {
                // 成绩低 → 往后移（实现成绩降序）
                Student temp = students[j];
                students[j] = students[j+1];
                students[j+1] = temp;
            }
            else if (students[j].score == students[j+1].score) {
                // 成绩相同 → 再判断次条件：年龄
                if (students[j].age > students[j+1].age) {
                    // 年龄大 → 往后移（实现年龄升序）
                    // 注意：这里用的是 >，因为要升序
                    Student temp = students[j];
                    students[j] = students[j+1];
                    students[j+1] = temp;
                }
            }
            // 成绩高且年龄小的情况不需要交换
        }
    }

    // 输出多条件排序结果
    cout << "\n===== 多条件排序结果 =====" << endl;
    cout << "规则：①成绩从高到低  ②成绩相同时，年龄从小到大" << endl;
    cout << "\n排名  姓名    年龄    成绩" << endl;
    cout << "--------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        cout << "第" << i + 1 << "名 "
             << students[i].name << "    "
             << students[i].age << "岁    "
             << students[i].score << "分" << endl;
    }

    // 验证排序结果
    cout << "\n 验证多条件排序：" << endl;

    // 验证成绩降序
    bool scoreOrderOK = true;
    for (int i = 0; i < N - 1; i++) {
        if (students[i].score < students[i+1].score) {
            scoreOrderOK = false;
            break;
        }
    }
    cout << "  成绩降序排列：" << (scoreOrderOK ? "✅ 正确" : "❌ 有误") << endl;

    // 验证成绩相同时年龄升序
    bool ageOrderOK = true;
    for (int i = 0; i < N - 1; i++) {
        if (students[i].score == students[i+1].score) {
            if (students[i].age > students[i+1].age) {
                ageOrderOK = false;
                break;
            }
        }
    }
    cout << "  同分年龄升序：" << (ageOrderOK ? "✅ 正确" : "❌ 有误") << endl;

    // 详细分析同分情况
    cout << "\n 同分情况分析：" << endl;
    cout << "  杨洋(13岁,95分) vs 刘涛(11岁,95分) → 成绩相同，年龄小的刘涛排前面 ✅" << endl;
    cout << "  张伟(13岁,92分) vs 王芳(14岁,92分) → 成绩相同，年龄小的张伟排前面 ✅" << endl;
    cout << "  李娜(12岁,88.5分) vs 赵雷(11岁,88.5分) → 成绩相同，年龄小的赵雷排前面 ✅" << endl;
}

// ==========================================
// 示例4：运动会奖牌排行榜（挑战任务参考）
// 多条件排序：金牌→银牌→铜牌，均为降序
// ==========================================
void example4_olympicRanking() {
    printLine("示例4：运动会奖牌排行榜（挑战任务）");

    const int N = 6;

    // 创建运动员数组
    Athlete athletes[N] = {
        {"刘翔",  2, 5, 3, 2, 0},  // total 待计算
        {"苏炳添", 1, 5, 2, 4, 0},
        {"姚明",  3, 3, 5, 1, 0},
        {"林丹",  2, 3, 3, 3, 0},
        {"李娜",  1, 4, 4, 2, 0},
        {"孙杨",  3, 4, 3, 2, 0}
    };

    // 计算每个运动员的奖牌总数
    for (int i = 0; i < N; i++) {
        athletes[i].total = athletes[i].gold + athletes[i].silver + athletes[i].bronze;
    }

    // ==========================================
    // 多条件排序（使用冒泡排序，保证稳定性）
    // 第一条件：金牌数降序
    // 第二条件：银牌数降序
    // 第三条件：铜牌数降序
    // ==========================================
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1 - i; j++) {
            bool shouldSwap = false;

            // 第一条件：金牌数
            if (athletes[j].gold < athletes[j+1].gold) {
                shouldSwap = true;
            }
            else if (athletes[j].gold == athletes[j+1].gold) {
                // 第二条件：银牌数（金牌相同时）
                if (athletes[j].silver < athletes[j+1].silver) {
                    shouldSwap = true;
                }
                else if (athletes[j].silver == athletes[j+1].silver) {
                    // 第三条件：铜牌数（金银都相同时）
                    if (athletes[j].bronze < athletes[j+1].bronze) {
                        shouldSwap = true;
                    }
                }
            }

            if (shouldSwap) {
                Athlete temp = athletes[j];
                athletes[j] = athletes[j+1];
                athletes[j+1] = temp;
            }
        }
    }

    // 输出排行榜
    cout << "\n🏅 ========== 运动会奖牌排行榜 ========== 🏅" << endl;
    cout << "排名  姓名      班级   🥇金牌  🥈银牌  🥉铜牌  📊总数" << endl;
    cout << "--------------------------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        // 第一名特殊标注
        string medalEmoji;
        if (i == 0) medalEmoji = "🥇";
        else if (i == 1) medalEmoji = "🥈";
        else if (i == 2) medalEmoji = "🥉";
        else medalEmoji = "  ";

        cout << medalEmoji << "第" << i + 1 << "名 "
             << athletes[i].name << "      "
             << athletes[i].classId << "班    "
             << athletes[i].gold << "      "
             << athletes[i].silver << "      "
             << athletes[i].bronze << "      "
             << athletes[i].total << endl;
    }

    // 班级统计
    int classTotal[4] = {0};  // 假设有1-3班
    for (int i = 0; i < N; i++) {
        classTotal[athletes[i].classId] += athletes[i].total;
    }

    cout << "\n------------ 班级奖牌统计 ------------" << endl;
    for (int c = 1; c <= 3; c++) {
        cout << c << "班总奖牌数：" << classTotal[c] << " 枚" << endl;
    }

    // 找出奖牌最多的班级
    int bestClass = 1;
    for (int c = 2; c <= 3; c++) {
        if (classTotal[c] > classTotal[bestClass]) {
            bestClass = c;
        }
    }
    cout << "🏆 奖牌总数最多的班级是：" << bestClass << "班！" << endl;
}

// ==========================================
// 示例5：排序方法选择指南（互动演示）
// ==========================================
void example5_sortingGuide() {
    printLine("示例5：排序方法选择指南");

    cout << "\n根据不同场景选择不同的排序方法：\n" << endl;

    cout << "┌─────────────────────────────────────────────────────┐" << endl;
    cout << "│  场景                   │  推荐方法    │  原因      │" << endl;
    cout << "├─────────────────────────────────────────────────────┤" << endl;
    cout << "│  数据量很小（< 20个）   │  任选一种    │  差别不大  │" << endl;
    cout << "│  需要稳定性（保持顺序） │  冒泡排序    │  稳定算法  │" << endl;
    cout << "│  交换代价很大           │  选择排序    │  交换少    │" << endl;
    cout << "│  数据基本有序           │  冒泡排序    │  提前结束  │" << endl;
    cout << "│  多条件排序             │  冒泡排序    │  更可控    │" << endl;
    cout << "│  代码要简单             │  选择排序    │  逻辑直观  │" << endl;
    cout << "└─────────────────────────────────────────────────────┘" << endl;

    cout << "\n 示例演示：稳定性对比" << endl;
    cout << "------------------------------" << endl;

    // 准备两个相同的数据（学生同分情况）
    Student arr1[3] = {
        {"小红", 11, 90.0},
        {"小明", 12, 85.0},
        {"小丽", 12, 90.0}   // 和小红同分，但在小丽后面
    };

    Student arr2[3] = {
        {"小红", 11, 90.0},
        {"小明", 12, 85.0},
        {"小丽", 12, 90.0}
    };

    // 冒泡排序（稳定）
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2 - i; j++) {
            if (arr1[j].score < arr1[j+1].score) {
                Student temp = arr1[j];
                arr1[j] = arr1[j+1];
                arr1[j+1] = temp;
            }
        }
    }

    // 选择排序（不稳定）
    for (int i = 0; i < 2; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < 3; j++) {
            if (arr2[j].score > arr2[maxIdx].score) {
                maxIdx = j;
            }
        }
        if (maxIdx != i) {
            Student temp = arr2[i];
            arr2[i] = arr2[maxIdx];
            arr2[maxIdx] = temp;
        }
    }

    cout << "原始顺序：小红(90) → 小明(85) → 小丽(90)" << endl;
    cout << "\n冒泡排序（稳定）结果：" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "  " << arr1[i].name << "(" << arr1[i].score << "分) ";
    }
    cout << "\n  → 小红(90) 仍然在小丽(90) 前面 ✅ 保持顺序" << endl;

    cout << "\n选择排序（不稳定）结果：" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "  " << arr2[i].name << "(" << arr2[i].score << "分) ";
    }
    cout << "\n  → 小红和小丽的顺序可能发生变化 ⚠️" << endl;
}

// ==========================================
// 主函数
// ==========================================
int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║    第44课：终极排序大赛——排序综合              ║" << endl;
    cout << "║    冒泡排序 vs 选择排序 | 结构体排序 | 多条件排序 ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    // 运行所有示例
    example1_sortComparison();
    example2_studentRanking();
    example3_multiConditionSorting();
    example4_olympicRanking();
    example5_sortingGuide();

    // 最终总结
    cout << "\n\n========================================" << endl;
    cout << "  🎉 第44课学习完毕！ 🎉" << endl;
    cout << "========================================" << endl;
    cout << "本节课你学到了：" << endl;
    cout << "  1. 冒泡排序 vs 选择排序：比较次数相同，" << endl;
    cout << "     但选择排序交换少、冒泡排序稳定" << endl;
    cout << "  2. 结构体排序：比较的是成员，交换的是整个结构体" << endl;
    cout << "  3. 多条件排序：用 if...else if 实现分层判断" << endl;
    cout << "  4. 实际应用：成绩排名、运动会排行榜等" << endl;
    cout << "\n  你已经掌握了排序的综合应用！继续加油！" << endl;
    cout << "========================================" << endl;

    return 0;
}
