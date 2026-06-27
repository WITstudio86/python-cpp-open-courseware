/*
 * 第28课：你来比划我来猜——数组趣味应用
 * 主题：频率计数、标记数组
 * 项目：数字频率计数器
 * 适用：中小学C++趣味学习
 * 日期：2026年
 */

#include <iostream>
#include <string>
using namespace std;

int main() {
    // ==========================================
    // 示例1：频率计数器——统计数字出现次数
    // ==========================================
    cout << "=== 示例1：频率计数器 ===" << endl;

    {
        int count[11] = {0};  // 下标0不用，下标1-10分别计数字1-10
        int n, num;

        cout << "请输入数字的个数：";
        cin >> n;

        cout << "请输入 " << n << " 个数字（范围1-10）：" << endl;
        for (int i = 0; i < n; i++) {
            cin >> num;
            if (num >= 1 && num <= 10) {
                count[num]++;  // 核心：对应数字的计数器加1
            } else {
                cout << "数字 " << num << " 不在1-10范围内，已忽略。" << endl;
            }
        }

        cout << "\n数字出现次数统计：" << endl;
        for (int i = 1; i <= 10; i++) {
            if (count[i] > 0) {
                cout << "数字 " << i << " 出现了 " << count[i] << " 次";
                // 用星号画出简易柱状图
                cout << "  ";
                for (int j = 0; j < count[i]; j++) {
                    cout << "*";
                }
                cout << endl;
            }
        }
    }
    cout << endl;

    // ==========================================
    // 示例2：标记数组——判断数字是否出现过
    // ==========================================
    cout << "=== 示例2：标记数组去重 ===" << endl;

    {
        bool appeared[101] = {false};  // 标记数字1-100是否出现过
        int n, num;

        cout << "请输入数字的个数（范围1-100）：";
        cin >> n;

        cout << "请输入 " << n << " 个数字：";
        int distinctCount = 0;
        for (int i = 0; i < n; i++) {
            cin >> num;
            if (num >= 1 && num <= 100) {
                if (!appeared[num]) {
                    cout << num << " ";
                    appeared[num] = true;
                    distinctCount++;
                }
            }
        }
        cout << endl;
        cout << "共输入 " << n << " 个数字，其中不重复的有 " << distinctCount << " 个。" << endl;
    }
    cout << endl;

    // ==========================================
    // 示例3：数字频率计数器（完整项目）
    // ==========================================
    cout << "=== 示例3：数字频率计数器 ===" << endl;

    {
        int digitCount[10] = {0};  // digitCount[0]~[9] 分别统计数字0~9
        long long n;

        cout << "请输入一个整数：";
        cin >> n;

        long long original = n;  // 保存原始值用于输出

        // 如果输入的是负数，先转为正数
        if (n < 0) {
            n = -n;
        }

        // 如果是0，单独处理
        if (n == 0) {
            digitCount[0] = 1;
        }

        // 逐位提取数字并计数
        int totalDigits = 0;
        while (n > 0) {
            int digit = n % 10;    // 取出最后一位数字
            digitCount[digit]++;   // 对应的计数器加1
            n = n / 10;            // 去掉最后一位
            totalDigits++;
        }

        cout << "\n========================================" << endl;
        cout << "  数字 " << original << " 的频率统计" << endl;
        cout << "========================================" << endl;
        cout << "总位数：" << totalDigits << " 位" << endl;
        cout << endl;

        // 找出最大出现次数
        int maxCount = 0;
        for (int i = 0; i < 10; i++) {
            if (digitCount[i] > maxCount) {
                maxCount = digitCount[i];
            }
        }

        // 输出统计结果（带柱状图）
        for (int i = 0; i < 10; i++) {
            cout << "数字 " << i << " 出现了 " << digitCount[i] << " 次  ";
            // 用星号画出简易柱状图
            for (int j = 0; j < digitCount[i]; j++) {
                cout << "█";
            }
            cout << endl;
        }

        // 找出出现次数最多的数字
        cout << "\n出现次数最多的数字（" << maxCount << " 次）：";
        bool first = true;
        for (int i = 0; i < 10; i++) {
            if (digitCount[i] == maxCount) {
                if (!first) cout << "、";
                cout << i;
                first = false;
            }
        }
        cout << endl;

        // 找出没有出现的数字
        cout << "没有出现的数字：";
        bool hasMissing = false;
        for (int i = 0; i < 10; i++) {
            if (digitCount[i] == 0) {
                if (hasMissing) cout << "、";
                cout << i;
                hasMissing = true;
            }
        }
        if (!hasMissing) {
            cout << "无（所有数字都出现了）";
        }
        cout << endl;
    }

    // ==========================================
    // 课后练习参考答案
    // ==========================================
    cout << "\n========================================" << endl;
    cout << "  课后练习参考答案（独立运行）" << endl;
    cout << "========================================" << endl;

    // ---------- 练习1：成绩分布统计 ----------
    cout << "\n--- 练习1：成绩分布统计 ---" << endl;
    {
        int segCount[5] = {0};  // 0:不及格 1:及格 2:中等 3:良好 4:优秀
        int score;

        cout << "请输入成绩（输入 -1 结束）：" << endl;
        while (true) {
            cin >> score;
            if (score == -1) break;
            if (score < 0 || score > 100) {
                cout << "成绩 " << score << " 无效，请输入0-100之间的值。" << endl;
                continue;
            }
            if (score < 60) {
                segCount[0]++;  // 不及格
            } else if (score < 70) {
                segCount[1]++;  // 及格
            } else if (score < 80) {
                segCount[2]++;  // 中等
            } else if (score < 90) {
                segCount[3]++;  // 良好
            } else {
                segCount[4]++;  // 优秀
            }
        }

        string segNames[5] = {"不及格(0-59)", "及格(60-69)", "中等(70-79)", "良好(80-89)", "优秀(90-100)"};
        cout << "\n成绩分布统计：" << endl;
        int totalStudents = 0;
        for (int i = 0; i < 5; i++) {
            cout << segNames[i] << "：" << segCount[i] << " 人";
            cout << "  ";
            for (int j = 0; j < segCount[i]; j++) {
                cout << "█";
            }
            cout << endl;
            totalStudents += segCount[i];
        }
        cout << "总人数：" << totalStudents << " 人" << endl;
    }

    // ---------- 练习2：数字出现次数 ----------
    cout << "\n--- 练习2：数字出现次数（0-9） ---" << endl;
    {
        int freq[10] = {0};
        int num;

        cout << "请输入10个整数（范围0-9）：" << endl;
        for (int i = 0; i < 10; i++) {
            cin >> num;
            if (num >= 0 && num <= 9) {
                freq[num]++;
            } else {
                cout << "数字 " << num << " 超出范围，已忽略。" << endl;
            }
        }

        cout << "\n统计结果：" << endl;
        int maxFreq = 0;
        for (int i = 0; i < 10; i++) {
            cout << "数字 " << i << "：" << freq[i] << " 次" << endl;
            if (freq[i] > maxFreq) {
                maxFreq = freq[i];
            }
        }

        cout << "出现次数最多的数字（" << maxFreq << " 次）：";
        bool first = true;
        for (int i = 0; i < 10; i++) {
            if (freq[i] == maxFreq) {
                if (!first) cout << "、";
                cout << i;
                first = false;
            }
        }
        cout << endl;
    }

    // ---------- 练习3：字母频率统计 ----------
    cout << "\n--- 练习3：字母频率统计 ---" << endl;
    {
        int letterCount[26] = {0};
        string text;

        cout << "请输入一个只包含小写字母的字符串：";
        cin >> text;

        for (int i = 0; i < text.length(); i++) {
            char ch = text[i];
            if (ch >= 'a' && ch <= 'z') {
                letterCount[ch - 'a']++;  // 'a'对应下标0，'b'对应1...
            }
        }

        cout << "\n字母频率统计：" << endl;
        int maxLetterCount = 0;
        for (int i = 0; i < 26; i++) {
            if (letterCount[i] > 0) {
                cout << "字母 " << char('a' + i) << "：" << letterCount[i] << " 次" << endl;
                if (letterCount[i] > maxLetterCount) {
                    maxLetterCount = letterCount[i];
                }
            }
        }

        if (maxLetterCount > 0) {
            cout << "出现次数最多的字母：";
            bool first = true;
            for (int i = 0; i < 26; i++) {
                if (letterCount[i] == maxLetterCount) {
                    if (!first) cout << "、";
                    cout << char('a' + i);
                    first = false;
                }
            }
            cout << "（" << maxLetterCount << " 次）" << endl;
        } else {
            cout << "没有统计到任何小写字母。" << endl;
        }
    }

    cout << "\n========== 第28课学习完毕！ ==========" << endl;

    return 0;
}
