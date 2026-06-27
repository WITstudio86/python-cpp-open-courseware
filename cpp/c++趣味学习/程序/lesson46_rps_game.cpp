/*
 * ============================================================
 * 第46课：石头剪刀布 —— 人机对战
 * C++ 趣味学习课件 - 配套程序文件
 * ============================================================
 * 本文件包含三个程序：
 *   1. 单局石头剪刀布（一局定胜负）
 *   2. 三局两胜制完整游戏（多轮、计分、最终判定）
 *   3. 增强版：带手势图形显示的石头剪刀布
 *
 * 知识点：
 *   - 随机数生成：srand(time(0)) + rand() % 3
 *   - 多条件判断：if-else 实现胜负逻辑
 *   - 循环与计分：while 循环实现多轮比赛
 *   - 数组应用：用 string 数组存储手势名称
 *
 * 编译方式：
 *   g++ -o rps_game lesson46_rps_game.cpp
 *   ./rps_game
 * ============================================================
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// ==========================================
// 程序1：单局石头剪刀布（一局定胜负）
// ==========================================
void singleRound() {
    cout << endl;
    cout << "╔══════════════════════════════╗" << endl;
    cout << "║  程序1：单局石头剪刀布       ║" << endl;
    cout << "╚══════════════════════════════╝" << endl;
    cout << endl;

    // 设置随机种子，让电脑每次出拳不同
    srand(time(0));

    int player, computer;
    string gestures[] = {"石头", "剪刀", "布"};

    // 显示菜单，引导玩家输入
    cout << "请出拳：" << endl;
    cout << "  0 —— 石头 ✊" << endl;
    cout << "  1 —— 剪刀 ✌" << endl;
    cout << "  2 —— 布   ✋" << endl;
    cout << "你的选择：";
    cin >> player;

    // 检查输入是否合法（必须在 0-2 之间）
    if (player < 0 || player > 2) {
        cout << "输入无效！请输入 0、1 或 2。" << endl;
        return;
    }

    // 电脑随机出拳：rand() % 3 生成 0、1、2 中的一个
    computer = rand() % 3;

    // 显示双方出拳结果
    cout << endl;
    cout << "你出了：" << gestures[player] << endl;
    cout << "电脑出了：" << gestures[computer] << endl;

    // ---------- 胜负判断 ----------
    // 胜负判断的数学规律：
    //   玩家赢的情况：(player + 1) % 3 == computer
    //   即：石头(0)赢剪刀(1)、剪刀(1)赢布(2)、布(2)赢石头(0)
    if (player == computer) {
        cout << "结果：平局！再来一次吧 🤝" << endl;
    } else if ((player + 1) % 3 == computer) {
        cout << "结果：你赢了！好厉害 🎉" << endl;
    } else {
        cout << "结果：电脑赢了！别灰心，继续加油 💪" << endl;
    }
}

// ==========================================
// 程序2：三局两胜制完整游戏
// ==========================================
void bestOfThree() {
    cout << endl;
    cout << "╔══════════════════════════════╗" << endl;
    cout << "║  程序2：三局两胜制完整游戏   ║" << endl;
    cout << "╚══════════════════════════════╝" << endl;
    cout << endl;

    srand(time(0));

    // score 变量用于记录双方得分
    int playerScore = 0;
    int computerScore = 0;
    int round = 1;                     // 当前是第几局
    string gestures[] = {"石头", "剪刀", "布"};

    cout << "规则说明：" << endl;
    cout << "  1. 共进行最多 3 局比赛" << endl;
    cout << "  2. 先赢 2 局者获得最终胜利" << endl;
    cout << "  3. 平局不计分，但计局数" << endl;
    cout << endl;

    // while 循环控制比赛流程：
    //   继续比赛的条件 —— 双方都没有赢到 2 局 &&
    //   还没打完 3 局
    while (playerScore < 2 && computerScore < 2 && round <= 3) {
        // 显示当前局数和比分
        cout << "──────── 第 " << round << " 局 ────────" << endl;
        cout << "当前比分：你 " << playerScore
             << " - " << computerScore << " 电脑" << endl;
        cout << endl;

        int player, computer;

        // 引导玩家出拳
        cout << "请出拳（0=石头, 1=剪刀, 2=布）：";
        cin >> player;

        // 输入验证：如果输入非法，提示后重新输入
        if (player < 0 || player > 2) {
            cout << "❌ 输入无效！请输入 0、1 或 2。" << endl;
            cout << endl;
            continue;   // 跳过本轮循环，回到 while 开头
        }

        // 电脑随机出拳
        computer = rand() % 3;

        // 展示双方出拳
        cout << "  你出了：" << gestures[player] << endl;
        cout << "  电脑出了：" << gestures[computer] << endl;

        // 判断本局胜负，并更新比分
        if (player == computer) {
            cout << "  本局结果：平局！不分胜负" << endl;
        } else if ((player + 1) % 3 == computer) {
            cout << "  本局结果：你赢！🏆 得分 +1" << endl;
            playerScore++;   // 玩家得分加 1
        } else {
            cout << "  本局结果：电脑赢！💻 得分 +1" << endl;
            computerScore++; // 电脑得分加 1
        }

        round++;
        cout << endl;

        // 提前结束判断：如果已经有人赢到 2 局，提前退出
        if (playerScore >= 2 || computerScore >= 2) {
            cout << ">>> 比赛提前结束！已经有人赢得 2 局 <<<" << endl;
            cout << endl;
            break;
        }
    }

    // ---------- 最终结果判定 ----------
    cout << "══════════════════════════════" << endl;
    cout << "        最终结算               " << endl;
    cout << "══════════════════════════════" << endl;
    cout << "最终比分：你 " << playerScore
         << " - " << computerScore << " 电脑" << endl;
    cout << "比赛局数：" << (round - 1) << " 局" << endl;
    cout << endl;

    if (playerScore > computerScore) {
        cout << "🎉🎉🎉 恭喜你，获得了最终胜利！🎉🎉🎉" << endl;
        cout << "你以 " << playerScore << ":" << computerScore
             << " 战胜了电脑！" << endl;
    } else if (computerScore > playerScore) {
        cout << "😢 很遗憾，电脑获得了最终胜利！" << endl;
        cout << "不要气馁，下次一定能赢！" << endl;
    } else {
        cout << "🤝 平局收场！势均力敌呢~" << endl;
    }
}

// ==========================================
// 程序3：增强版 —— 带手势图形显示的石头剪刀布
// ==========================================
void enhancedVersion() {
    cout << endl;
    cout << "╔══════════════════════════════╗" << endl;
    cout << "║  程序3：增强版石头剪刀布     ║" << endl;
    cout << "╚══════════════════════════════╝" << endl;
    cout << endl;

    srand(time(0));

    // 使用二维字符数组存储手势的 ASCII 艺术图形
    // 让游戏界面更加生动有趣
    string gestureArt[3][5] = {
        {   // 石头 ✊（拳头形状）
            "    _______   ",
            "---'   ____)  ",
            "      (_____) ",
            "      (_____) ",
            "      (____)  "
        },
        {   // 剪刀 ✌（剪刀形状）
            "    _______   ",
            "---'   ____)__",
            "          ____)",
            "       _______)",
            "      (____)  "
        },
        {   // 布 ✋（手掌形状）
            "    _______   ",
            "---'   ____)__",
            "          ____)",
            "       _______)",
            "      _______)"
        }
    };

    string gestureName[] = {"石头 ✊", "剪刀 ✌", "布 ✋"};

    int playerScore = 0, computerScore = 0;
    int totalGames = 0;     // 总局数
    int playerWins = 0;     // 玩家胜局数
    int computerWins = 0;   // 电脑胜局数
    int draws = 0;          // 平局数
    char playAgain;         // 是否继续游戏

    cout << "欢迎来到增强版石头剪刀布！" << endl;
    cout << "特色功能：" << endl;
    cout << "  • 手势图形显示" << endl;
    cout << "  • 无限对战（直到你选择退出）" << endl;
    cout << "  • 实时胜率统计" << endl;
    cout << endl;

    do {
        int player, computer;
        totalGames++;

        cout << "──────── 第 " << totalGames << " 局 ────────" << endl;

        // 显示漂亮的菜单
        cout << "请出拳：" << endl;
        cout << "  [0] 石头 ✊" << endl;
        cout << "  [1] 剪刀 ✌" << endl;
        cout << "  [2] 布   ✋" << endl;
        cout << endl;
        cout << "你的选择：";
        cin >> player;

        // 输入验证
        if (player < 0 || player > 2) {
            cout << "输入无效！请重新输入。" << endl;
            totalGames--;  // 无效游戏不计入统计
            continue;
        }

        // 电脑出拳
        computer = rand() % 3;

        // ---------- 显示双方手势图形 ----------
        cout << endl;
        cout << "你的手势：" << gestureName[player] << endl;
        // 逐行打印手势图形
        for (int i = 0; i < 5; i++) {
            cout << "  " << gestureArt[player][i] << endl;
        }
        cout << endl;

        cout << "电脑的手势：" << gestureName[computer] << endl;
        for (int i = 0; i < 5; i++) {
            cout << "  " << gestureArt[computer][i] << endl;
        }
        cout << endl;

        // ---------- 判断胜负并统计 ----------
        if (player == computer) {
            cout << "👉 平局！🤝" << endl;
            draws++;
        } else if ((player + 1) % 3 == computer) {
            cout << "👉 你赢了！🎉" << endl;
            playerWins++;
        } else {
            cout << "👉 电脑赢了！💻" << endl;
            computerWins++;
        }

        // 显示实时统计
        cout << endl;
        cout << "══════ 实时统计 ══════" << endl;
        cout << "总局数：" << totalGames << endl;
        cout << "你赢了：" << playerWins << " 局" << endl;
        cout << "电脑赢了：" << computerWins << " 局" << endl;
        cout << "平局：" << draws << " 局" << endl;

        // 计算并显示胜率（避免除以零）
        if (totalGames > 0) {
            double winRate = (double)playerWins / totalGames * 100;
            cout << "你的胜率：" << winRate << "%" << endl;
        }
        cout << "════════════════════" << endl;
        cout << endl;

        // 询问是否继续
        cout << "是否继续游戏？(y/n)：";
        cin >> playAgain;
        cout << endl;

    } while (playAgain == 'y' || playAgain == 'Y');

    // 最终总结
    cout << "══════════════════════════════" << endl;
    cout << "      游戏结束，感谢游玩！    " << endl;
    cout << "══════════════════════════════" << endl;
    cout << "共进行了 " << totalGames << " 局比赛" << endl;

    if (totalGames > 0) {
        double finalWinRate = (double)playerWins / totalGames * 100;
        cout << "最终胜率：" << finalWinRate << "%" << endl;

        // 根据胜率给出评价
        if (finalWinRate >= 80) {
            cout << "🏆 评价：你是石头剪刀布大师！" << endl;
        } else if (finalWinRate >= 60) {
            cout << "👍 评价：还不错，继续加油！" << endl;
        } else if (finalWinRate >= 40) {
            cout << "📚 评价：势均力敌，多练练会更好！" << endl;
        } else {
            cout << "💪 评价：没关系，运气成分也很大！" << endl;
        }
    }

    cout << "期待下次再战！再见~" << endl;
}

// ==========================================
// 主函数：选择要运行的演示程序
// ==========================================
int main() {
    int choice;

    cout << "╔══════════════════════════════════╗" << endl;
    cout << "║  第46课：石头剪刀布 —— 人机对战 ║" << endl;
    cout << "║       C++ 趣味学习程序演示       ║" << endl;
    cout << "╚══════════════════════════════════╝" << endl;
    cout << endl;
    cout << "请选择要运行的程序：" << endl;
    cout << "  1 —— 单局石头剪刀布" << endl;
    cout << "  2 —— 三局两胜制完整游戏" << endl;
    cout << "  3 —— 增强版（手势图形 + 胜率统计）" << endl;
    cout << "  0 —— 退出" << endl;
    cout << endl;
    cout << "请输入选择：";
    cin >> choice;

    // 根据用户选择调用对应的函数
    switch (choice) {
        case 1:
            singleRound();
            break;
        case 2:
            bestOfThree();
            break;
        case 3:
            enhancedVersion();
            break;
        case 0:
            cout << "再见！" << endl;
            break;
        default:
            cout << "无效的选择！" << endl;
            break;
    }

    cout << endl;
    cout << "程序运行完毕，谢谢使用！" << endl;

    return 0;
}
