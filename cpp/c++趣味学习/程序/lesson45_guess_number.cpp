/*
 * 第45课：终极密码——猜数字游戏
 * 主题：随机数生成、二分查找、猜数字游戏
 * 项目：电脑出题玩家猜 / 电脑用二分法猜玩家数字
 * 适用：中小学C++趣味学习
 * 日期：2026年
 */

#include <iostream>
#include <cstdlib>   // 包含 rand() 和 srand() 函数
#include <ctime>     // 包含 time() 函数，用于生成随机种子
using namespace std;

int main() {
    // ==========================================
    // 程序1：基础猜数字游戏（电脑出题，玩家猜）
    // ==========================================
    cout << "========================================" << endl;
    cout << "  程序1：基础猜数字游戏" << endl;
    cout << "  电脑出一个 1~100 的随机数，你来猜！" << endl;
    cout << "========================================" << endl;

    // 设置随机数种子
    // time(0) 获取当前时间（1970年1月1日至今的秒数）
    // 因为时间一直在变，所以每次运行随机数都不同
    srand(time(0));

    // 生成 1~100 的随机数
    // rand() % 100 生成 0~99，加 1 变成 1~100
    int secret1 = rand() % 100 + 1;
    int guess1;       // 存放玩家输入的数字
    int count1 = 0;   // 记录猜测次数

    cout << "\n我已经想好了一个 1~100 之间的数字！" << endl;

    // do-while 循环：至少猜一次，直到猜对为止
    do {
        cout << "请输入你猜的数字：";
        cin >> guess1;
        count1++;  // 每猜一次，计数器加1

        if (guess1 > secret1) {
            cout << "太大了！往小猜一猜~" << endl;
        } else if (guess1 < secret1) {
            cout << "太小了！往大猜一猜~" << endl;
        } else {
            cout << "\n🎉 恭喜你猜对了！" << endl;
            cout << "正确答案就是：" << secret1 << endl;
            cout << "你一共猜了 " << count1 << " 次！" << endl;
        }
    } while (guess1 != secret1);  // 没猜对就继续循环

    cout << "\n" << endl;


    // ==========================================
    // 程序2：升级版猜数字游戏（带提示 + 次数限制）
    // ==========================================
    cout << "========================================" << endl;
    cout << "  程序2：升级版猜数字游戏" << endl;
    cout << "  增加难度：最多只有10次机会！" << endl;
    cout << "========================================" << endl;

    // 重新生成一个随机数
    int secret2 = rand() % 100 + 1;
    int guess2;
    int count2 = 0;
    const int MAX_CHANCES = 10;  // 常量：最大猜测次数

    cout << "\n规则：猜 1~100 的数字，最多 " << MAX_CHANCES << " 次机会！" << endl;
    cout << "提示：试试从中间开始猜，效率更高哦！" << endl;

    while (count2 < MAX_CHANCES) {  // 只要还有机会就继续
        cout << "\n第 " << count2 + 1 << " 次猜测（剩余 "
             << MAX_CHANCES - count2 << " 次机会）：请输入数字：";
        cin >> guess2;
        count2++;

        if (guess2 == secret2) {
            // 猜对了！
            cout << "\n🎉 恭喜！你用了 " << count2 << " 次就猜对了！" << endl;
            cout << "正确答案是：" << secret2 << endl;

            // 根据次数给出评价
            if (count2 == 1) {
                cout << "⭐ 运气爆棚！一次命中！" << endl;
            } else if (count2 <= 3) {
                cout << "⭐ 非常厉害！你是猜数小天才！" << endl;
            } else if (count2 <= 5) {
                cout << "⭐ 不错！逻辑思维很棒！" << endl;
            } else if (count2 <= 7) {
                cout << "⭐ 还可以，继续加油！" << endl;
            } else {
                cout << "💡 建议用二分法：每次猜中间值，效率会翻倍！" << endl;
            }
            break;  // 猜对就结束
        } else if (guess2 > secret2) {
            // 猜大了：给出提示，差距大时额外提醒
            cout << "📉 太大了！";
            if (guess2 - secret2 > 20) {
                cout << " （差得有点远哦，大胆往下减！）";
            }
            cout << endl;
        } else {
            // 猜小了：给出提示，差距大时额外提醒
            cout << "📈 太小了！";
            if (secret2 - guess2 > 20) {
                cout << " （差得有点远哦，大胆往上加！）";
            }
            cout << endl;
        }
    }

    // 如果循环结束还没猜对，说明次数用完了
    if (count2 >= MAX_CHANCES && guess2 != secret2) {
        cout << "\n😢 很遗憾，" << MAX_CHANCES << " 次机会用完了！" << endl;
        cout << "正确答案是：" << secret2 << endl;
        cout << "下次从中间开始猜会更高效哦！" << endl;
    }

    cout << "\n\n";


    // ==========================================
    // 程序3：反向猜数字（电脑用二分法猜玩家的数字）
    // ==========================================
    cout << "========================================" << endl;
    cout << "  程序3：反向猜数字" << endl;
    cout << "  现在轮到电脑来猜你的数字了！" << endl;
    cout << "  电脑使用二分查找策略（每次猜中间值）" << endl;
    cout << "========================================" << endl;

    cout << "\n请你心里想一个 1~100 的数字（或者写在纸上）。" << endl;
    cout << "电脑每次猜一个数，请你输入反馈：" << endl;
    cout << "  输入 'd' 表示猜大了" << endl;
    cout << "  输入 'x' 表示猜小了" << endl;
    cout << "  输入 'y' 表示猜对了" << endl;
    cout << "\n准备好了吗？按回车键开始..." << endl;
    cin.get();  // 吸收之前残留的换行符
    cin.get();  // 等待用户按回车

    // 二分查找的核心变量
    int low = 1;       // 当前范围的下界
    int high = 100;    // 当前范围的上界
    int mid;           // 电脑的猜测（中间值）
    int count3 = 0;    // 电脑的猜测次数
    char feedback;     // 玩家的反馈（d/x/y）

    cout << "\n========== 电脑开始猜了！ ==========" << endl;

    // 二分查找最多需要 7 次（2^7 = 128 > 100），但用 while 循环更灵活
    while (low <= high) {
        // 核心：计算中间值
        // (low + high) / 2 就是范围的中间位置
        mid = (low + high) / 2;
        count3++;

        // 显示当前范围和猜测
        cout << "\n第 " << count3 << " 次猜测：" << endl;
        cout << "  当前范围：[" << low << ", " << high << "]" << endl;
        cout << "  电脑猜的数字是：" << mid << endl;

        // 获取玩家反馈
        cout << "  请输入反馈（d=大了 / x=小了 / y=对了）：";
        cin >> feedback;

        if (feedback == 'y' || feedback == 'Y') {
            // 猜对了！
            cout << "\n🎉 电脑猜对了！答案就是 " << mid << "！" << endl;
            cout << "电脑一共猜了 " << count3 << " 次。" << endl;

            // 理论分析
            cout << "\n📊 二分查找效率分析：" << endl;
            cout << "  1~100 范围内，二分查找最多需要 7 次。" << endl;
            cout << "  电脑只用了 " << count3 << " 次，非常高效！" << endl;
            break;
        } else if (feedback == 'd' || feedback == 'D') {
            // 猜大了：目标在 low 到 mid-1 之间
            cout << "  → 电脑猜大了，范围缩小到 [" << low << ", " << mid - 1 << "]" << endl;
            high = mid - 1;  // 上界缩小到 mid-1
        } else if (feedback == 'x' || feedback == 'X') {
            // 猜小了：目标在 mid+1 到 high 之间
            cout << "  → 电脑猜小了，范围缩小到 [" << mid + 1 << ", " << high << "]" << endl;
            low = mid + 1;   // 下界增大到 mid+1
        } else {
            // 输入了无效的字符
            cout << "  ⚠️ 无效输入！请输入 d、x 或 y。" << endl;
            count3--;  // 这次不算
        }

        // 如果范围交叉了，说明玩家给错了反馈
        if (low > high && (feedback != 'y' && feedback != 'Y')) {
            cout << "\n🤔 嗯？范围变成 [" << low << ", " << high
                 << "] 了，你是不是给错反馈了？" << endl;
            cout << "游戏结束，请重新开始。" << endl;
            break;
        }
    }

    // 二分查找科普
    cout << "\n========================================" << endl;
    cout << "  💡 二分查找小知识：" << endl;
    cout << "  100 个数字 ➜ 最多猜 7 次" << endl;
    cout << "  1000 个数字 ➜ 最多猜 10 次" << endl;
    cout << "  10000 个数字 ➜ 最多猜 14 次" << endl;
    cout << "  100万个数字 ➜ 最多猜 20 次！" << endl;
    cout << "  每次排除一半，效率超级高！" << endl;
    cout << "========================================" << endl;

    cout << "\n========== 第45课学习完毕！ ==========" << endl;

    return 0;
}
