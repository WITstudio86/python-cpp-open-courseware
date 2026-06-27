/*
 * 第27课：找呀找呀找——数组查找
 * 主题：线性查找、查找最大值/最小值
 * 项目：寻找最高分的同学
 * 适用：中小学C++趣味学习
 * 日期：2026年
 */

#include <iostream>
#include <string>
using namespace std;

int main() {
    // ==========================================
    // 示例1：线性查找——在数组中查找特定值
    // ==========================================
    cout << "=== 示例1：线性查找 ===" << endl;

    int scores1[] = {85, 92, 78, 95, 88, 76, 90, 83};
    int n1 = 8;  // 数组长度
    int target;

    cout << "当前成绩数组：85, 92, 78, 95, 88, 76, 90, 83" << endl;
    cout << "请输入要查找的分数：";
    cin >> target;

    int pos = -1;  // -1 表示没找到
    for (int i = 0; i < n1; i++) {
        if (scores1[i] == target) {
            pos = i;
            break;  // 找到了，退出循环
        }
    }

    if (pos != -1) {
        cout << "找到了！分数 " << target << " 在第 " << pos + 1
             << " 个位置（下标 " << pos << "）。" << endl;
    } else {
        cout << "没有找到分数 " << target << "。" << endl;
    }
    cout << endl;

    // ==========================================
    // 示例2：查找最大值和最小值及其位置
    // ==========================================
    cout << "=== 示例2：查找最大值和最小值 ===" << endl;

    int scores2[] = {85, 92, 78, 95, 88, 76, 90, 83};
    int n2 = 8;

    int maxScore = scores2[0];  // 假设第一个是最大值
    int maxIndex = 0;           // 记录最大值的位置

    for (int i = 1; i < n2; i++) {
        if (scores2[i] > maxScore) {
            maxScore = scores2[i];
            maxIndex = i;
        }
    }

    int minScore = scores2[0];  // 假设第一个是最小值
    int minIndex = 0;           // 记录最小值的位置

    for (int i = 1; i < n2; i++) {
        if (scores2[i] < minScore) {
            minScore = scores2[i];
            minIndex = i;
        }
    }

    cout << "成绩数组：";
    for (int i = 0; i < n2; i++) {
        cout << scores2[i] << " ";
    }
    cout << endl;
    cout << "最高分是：" << maxScore << "（第 " << maxIndex + 1 << " 个位置）" << endl;
    cout << "最低分是：" << minScore << "（第 " << minIndex + 1 << " 个位置）" << endl;
    cout << endl;

    // ==========================================
    // 示例3：寻找最高分的同学（完整项目）
    // ==========================================
    cout << "=== 示例3：寻找最高分的同学 ===" << endl;

    const int N = 5;
    string names[N];
    int scores[N];

    // 输入学生姓名和成绩
    cout << "请输入 " << N << " 位同学的姓名和成绩：" << endl;
    for (int i = 0; i < N; i++) {
        cout << "第 " << i + 1 << " 位同学姓名：";
        cin >> names[i];
        cout << names[i] << " 的成绩：";
        cin >> scores[i];
    }

    // 查找最高分
    int classMax = scores[0];
    int classMaxIdx = 0;
    for (int i = 1; i < N; i++) {
        if (scores[i] > classMax) {
            classMax = scores[i];
            classMaxIdx = i;
        }
    }

    // 查找最低分
    int classMin = scores[0];
    int classMinIdx = 0;
    for (int i = 1; i < N; i++) {
        if (scores[i] < classMin) {
            classMin = scores[i];
            classMinIdx = i;
        }
    }

    // 计算平均分
    int sum = 0;
    for (int i = 0; i < N; i++) {
        sum += scores[i];
    }
    double average = sum * 1.0 / N;

    cout << "\n========== 成绩分析结果 ==========" << endl;
    cout << "最高分：" << names[classMaxIdx] << " 同学，成绩为 "
         << classMax << " 分！" << endl;
    cout << "最低分：" << names[classMinIdx] << " 同学，成绩为 "
         << classMin << " 分。" << endl;
    cout << "平均分：" << average << " 分。" << endl;

    // 输出所有高于平均分的同学
    cout << "\n成绩高于平均分的同学：" << endl;
    for (int i = 0; i < N; i++) {
        if (scores[i] > average) {
            cout << "  " << names[i] << "：" << scores[i] << " 分" << endl;
        }
    }

    // 查找特定同学
    string searchName;
    cout << "\n请输入要查找的同学姓名：";
    cin >> searchName;

    bool found = false;
    for (int i = 0; i < N; i++) {
        if (names[i] == searchName) {
            cout << searchName << " 的成绩是：" << scores[i] << " 分。" << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "没有找到 " << searchName << " 同学。" << endl;
    }

    // ==========================================
    // 课后练习参考答案
    // ==========================================
    cout << "\n========================================" << endl;
    cout << "  课后练习参考答案（独立运行）" << endl;
    cout << "========================================" << endl;

    // ---------- 练习1：找最小值 ----------
    cout << "\n--- 练习1：找最小值 ---" << endl;
    {
        int arr[10];
        cout << "请输入10个整数：" << endl;
        for (int i = 0; i < 10; i++) {
            cin >> arr[i];
        }

        int minVal = arr[0];
        int minIdx = 0;
        for (int i = 1; i < 10; i++) {
            if (arr[i] < minVal) {
                minVal = arr[i];
                minIdx = i;
            }
        }

        cout << "最小值是 " << minVal << "，下标为 " << minIdx
             << "（第 " << minIdx + 1 << " 个数）。" << endl;
    }

    // ---------- 练习2：统计分数段 ----------
    cout << "\n--- 练习2：统计分数段 ---" << endl;
    {
        int examScores[] = {95, 62, 78, 91, 88, 55, 73, 94, 60, 82,
                            45, 97, 70, 86, 59};
        int n = 15;
        int excellent = 0;  // 90分以上
        int fail = 0;       // 60分以下

        for (int i = 0; i < n; i++) {
            if (examScores[i] >= 90) {
                excellent++;
            }
            if (examScores[i] < 60) {
                fail++;
            }
        }

        cout << "15位同学的考试成绩统计：" << endl;
        cout << "90分以上（优秀）：" << excellent << " 人" << endl;
        cout << "60分以下（不及格）：" << fail << " 人" << endl;

        if (excellent > 0) {
            cout << "优秀的同学成绩：";
            for (int i = 0; i < n; i++) {
                if (examScores[i] >= 90) {
                    cout << examScores[i] << " ";
                }
            }
            cout << endl;
        }
    }

    // ---------- 练习3：找大于平均分的同学 ----------
    cout << "\n--- 练习3：找大于平均分的同学 ---" << endl;
    {
        const int M = 5;
        string stuNames[M];
        int stuScores[M];

        cout << "请输入5位同学的姓名和成绩：" << endl;
        for (int i = 0; i < M; i++) {
            cout << "姓名：";
            cin >> stuNames[i];
            cout << "成绩：";
            cin >> stuScores[i];
        }

        int total = 0;
        for (int i = 0; i < M; i++) {
            total += stuScores[i];
        }
        double avg = total * 1.0 / M;
        cout << "平均分是：" << avg << " 分" << endl;

        cout << "成绩高于平均分的同学：" << endl;
        bool hasAbove = false;
        for (int i = 0; i < M; i++) {
            if (stuScores[i] > avg) {
                cout << "  " << stuNames[i] << "：" << stuScores[i] << " 分" << endl;
                hasAbove = true;
            }
        }
        if (!hasAbove) {
            cout << "  没有人高于平均分。" << endl;
        }
    }

    cout << "\n========== 第27课学习完毕！ ==========" << endl;

    return 0;
}
