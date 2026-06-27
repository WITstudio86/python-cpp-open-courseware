/*
 * 第32课：像素小画家——二维数组趣味应用
 * 项目：字符画创作大师
 * 第三单元：数据的组织
 *
 * 本课学习：
 *   1. 用字符数组填充图案（矩形、三角形）
 *   2. 创作ASCII艺术形状（菱形、空心正方形）
 *   3. 用数字模拟地形图
 *   4. 交互式字符画创作程序
 *
 * 日期：2026年6月
 */

#include <iostream>
#include <iomanip>
using namespace std;

// ============================================================
// 辅助函数：打印分隔线
// ============================================================
void printSeparator(const char* title) {
    cout << "\n========================================" << endl;
    cout << "  " << title << endl;
    cout << "========================================" << endl;
}

// ============================================================
// 示例1：填充字符图案——矩形与直角三角形
// ============================================================
void example1_fillPatterns() {
    printSeparator("示例1：字符图案填充——矩形与直角三角形");

    char fillChar = '*';
    int width = 8, height = 4;

    // ---- 实心矩形 ----
    cout << "\n实心矩形 (" << width << "×" << height << ")：" << endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cout << fillChar << " ";
        }
        cout << endl;
    }

    // ---- 左下角直角三角形 ----
    cout << "\n直角三角形——左下角（高度=5）：" << endl;
    int n = 5;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            cout << fillChar << " ";
        }
        cout << endl;
    }

    // ---- 右下角直角三角形 ----
    cout << "\n直角三角形——右下角（高度=5）：" << endl;
    for (int i = 0; i < n; i++) {
        // 前面填充空格
        for (int j = 0; j < n - i - 1; j++) {
            cout << "  ";
        }
        // 画星星
        for (int j = 0; j <= i; j++) {
            cout << fillChar << " ";
        }
        cout << endl;
    }

    // ---- 左上角直角三角形 ----
    cout << "\n直角三角形——左上角（高度=5）：" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            cout << fillChar << " ";
        }
        cout << endl;
    }

    // ---- 等腰三角形（居中） ----
    cout << "\n等腰三角形——居中（高度=5）：" << endl;
    for (int i = 0; i < n; i++) {
        // 打印前导空格
        for (int j = 0; j < n - i - 1; j++) {
            cout << "  ";
        }
        // 打印星星：第i行打印 2*i+1 个
        for (int j = 0; j < 2 * i + 1; j++) {
            cout << fillChar << " ";
        }
        cout << endl;
    }

    cout << "\n规律总结：每种三角形只是改变了 空格数量 和 星星数量 的计算公式。" << endl;
}

// ============================================================
// 示例2：ASCII艺术形状——菱形与空心正方形
// ============================================================
void example2_asciiArt() {
    printSeparator("示例2：ASCII艺术——菱形与空心正方形");

    int n = 4;  // 菱形半高（不包括中间行）
    char ch = '#';

    // ---- 菱形 ----
    cout << "\n菱形图案（半高=" << n << "）：" << endl;

    // 上半部分（含中间行）
    for (int i = 0; i <= n; i++) {
        // 前导空格
        for (int j = 0; j < n - i; j++) {
            cout << "  ";
        }
        // 画字符：第i行画 2*i+1 个
        for (int j = 0; j < 2 * i + 1; j++) {
            cout << ch << " ";
        }
        cout << endl;
    }

    // 下半部分
    for (int i = n - 1; i >= 0; i--) {
        // 前导空格
        for (int j = 0; j < n - i; j++) {
            cout << "  ";
        }
        // 画字符：第i行画 2*i+1 个
        for (int j = 0; j < 2 * i + 1; j++) {
            cout << ch << " ";
        }
        cout << endl;
    }

    // ---- 空心正方形 ----
    int size = 6;
    cout << "\n空心正方形（边长=" << size << "）：" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            // 只在边界位置画字符
            if (i == 0 || i == size - 1 || j == 0 || j == size - 1) {
                cout << ch << " ";
            } else {
                cout << "  ";
            }
        }
        cout << endl;
    }

    // ---- 空心菱形 ----
    cout << "\n空心菱形（半高=" << n << "）：" << endl;
    // 上半部分
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < n - i; j++) {
            cout << "  ";
        }
        // 2*i+1 个位置中，只画第一个和最后一个
        for (int j = 0; j < 2 * i + 1; j++) {
            if (j == 0 || j == 2 * i) {
                cout << ch << " ";
            } else {
                cout << "  ";
            }
        }
        cout << endl;
    }
    // 下半部分
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < n - i; j++) {
            cout << "  ";
        }
        for (int j = 0; j < 2 * i + 1; j++) {
            if (j == 0 || j == 2 * i) {
                cout << ch << " ";
            } else {
                cout << "  ";
            }
        }
        cout << endl;
    }

    // ---- 数字三角形 ----
    cout << "\n数字三角形（高度=5）：" << endl;
    for (int i = 1; i <= 5; i++) {
        for (int j = 0; j < 5 - i; j++) {
            cout << "  ";
        }
        for (int j = 1; j <= i; j++) {
            cout << j << " ";
        }
        for (int j = i - 1; j >= 1; j--) {
            cout << j << " ";
        }
        cout << endl;
    }
}

// ============================================================
// 示例3：简单地图模拟——数字代表地形
// ============================================================
void example3_terrainMap() {
    printSeparator("示例3：简单地形图模拟");

    // 地形编码：0=海洋(~), 1=平原(.), 2=高山(^), 3=森林(T), 4=沙漠(s)
    const int ROWS = 6, COLS = 6;
    int map[ROWS][COLS] = {
        {0, 0, 0, 1, 1, 0},
        {0, 0, 1, 2, 2, 1},
        {0, 1, 2, 3, 2, 1},
        {0, 1, 2, 2, 1, 0},
        {1, 1, 1, 4, 4, 0},
        {0, 1, 1, 1, 1, 0}
    };

    cout << "\n图例说明：" << endl;
    cout << "  ~  = 海洋（0）" << endl;
    cout << "  .  = 平原（1）" << endl;
    cout << "  ^  = 高山（2）" << endl;
    cout << "  T  = 森林（3）" << endl;
    cout << "  s  = 沙漠（4）" << endl;

    cout << "\n地形图 (" << ROWS << "×" << COLS << ")：" << endl;
    cout << "  +";
    for (int j = 0; j < COLS; j++) cout << "--";
    cout << "+" << endl;

    for (int i = 0; i < ROWS; i++) {
        cout << "  |";
        for (int j = 0; j < COLS; j++) {
            switch (map[i][j]) {
                case 0: cout << "~ "; break;   // 海洋
                case 1: cout << ". "; break;   // 平原
                case 2: cout << "^ "; break;   // 高山
                case 3: cout << "T "; break;   // 森林
                case 4: cout << "s "; break;   // 沙漠
                default: cout << "? "; break;
            }
        }
        cout << "|" << endl;
    }

    cout << "  +";
    for (int j = 0; j < COLS; j++) cout << "--";
    cout << "+" << endl;

    // ---- 地形统计 ----
    cout << "\n地形统计：" << endl;
    int count[5] = {0};  // 统计5种地形数量
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (map[i][j] >= 0 && map[i][j] < 5) {
                count[map[i][j]]++;
            }
        }
    }
    const char* names[] = {"海洋", "平原", "高山", "森林", "沙漠"};
    const char* symbols[] = {"~", ".", "^", "T", "s"};
    for (int k = 0; k < 5; k++) {
        cout << "  " << symbols[k] << " " << names[k] << "：" << count[k] << " 格" << endl;
    }

    // ---- 显示数字地图（原始数据） ----
    cout << "\n原始数字地图（对照）：" << endl;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << setw(2) << map[i][j] << " ";
        }
        cout << endl;
    }
}

// ============================================================
// 课后练习答案
// ============================================================
void exerciseAnswers() {
    printSeparator("课后练习答案");

    // ---- 练习1：靠右的直角三角形 ----
    cout << "\n【练习1】靠右直角三角形（高度=5）：" << endl;
    int n = 5;
    char ch = '*';
    for (int i = 0; i < n; i++) {
        // 打印前导空格：第i行需要 (n-i-1)*2 个空格
        for (int j = 0; j < n - i - 1; j++) {
            cout << "  ";
        }
        // 打印星星
        for (int j = 0; j <= i; j++) {
            cout << ch << " ";
        }
        cout << endl;
    }

    // ---- 练习2：空心正方形 ----
    cout << "\n【练习2】空心正方形（边长=5）：" << endl;
    int side = 5;
    for (int i = 0; i < side; i++) {
        for (int j = 0; j < side; j++) {
            if (i == 0 || i == side - 1 || j == 0 || j == side - 1) {
                cout << ch << " ";
            } else {
                cout << "  ";
            }
        }
        cout << endl;
    }

    // ---- 练习3：扩展地形图（含沙漠） ----
    cout << "\n【练习3】扩展地形图（含5种地形）：" << endl;
    const int R = 6, C = 6;
    int mapEx[R][C] = {
        {0, 0, 0, 4, 4, 0},
        {0, 1, 1, 2, 4, 0},
        {0, 1, 2, 3, 2, 1},
        {1, 2, 2, 3, 1, 0},
        {4, 4, 1, 2, 1, 0},
        {4, 4, 4, 1, 1, 0}
    };

    cout << "\n图例: ~=海洋 .=平原 ^=高山 T=森林 s=沙漠" << endl << endl;
    for (int i = 0; i < R; i++) {
        cout << "  ";
        for (int j = 0; j < C; j++) {
            switch (mapEx[i][j]) {
                case 0: cout << "~ "; break;
                case 1: cout << ". "; break;
                case 2: cout << "^ "; break;
                case 3: cout << "T "; break;
                case 4: cout << "s "; break;
                default: cout << "? "; break;
            }
        }
        cout << endl;
    }
}

// ============================================================
// 挑战任务：字符画创作大师（交互式程序）
// ============================================================
void challenge_artCreator() {
    printSeparator("挑战任务：字符画创作大师");

    char choice;
    bool running = true;

    while (running) {
        cout << "\n╔════════════════════════════════╗" << endl;
        cout << "║     字符画创作大师 菜单       ║" << endl;
        cout << "╠════════════════════════════════╣" << endl;
        cout << "║  (A) 画实心矩形               ║" << endl;
        cout << "║  (B) 画等腰三角形             ║" << endl;
        cout << "║  (C) 画菱形                   ║" << endl;
        cout << "║  (D) 画实心正方形             ║" << endl;
        cout << "║  (E) 显示地形图               ║" << endl;
        cout << "║  (Q) 退出程序                 ║" << endl;
        cout << "╚════════════════════════════════╝" << endl;
        cout << "请选择 (A/B/C/D/E/Q)：";
        cin >> choice;

        // 将小写转为大写
        if (choice >= 'a' && choice <= 'z') {
            choice = choice - 'a' + 'A';
        }

        int w, h;
        char fill;

        switch (choice) {
            case 'A':
                // 画实心矩形
                cout << "输入矩形的宽度：";
                cin >> w;
                cout << "输入矩形的高度：";
                cin >> h;
                cout << "输入填充字符：";
                cin >> fill;
                cout << "\n实心矩形 (" << w << "×" << h << ")：" << endl;
                for (int i = 0; i < h; i++) {
                    for (int j = 0; j < w; j++) {
                        cout << fill << " ";
                    }
                    cout << endl;
                }
                break;

            case 'B':
                // 画等腰三角形
                cout << "输入三角形的高度：";
                cin >> h;
                cout << "输入填充字符：";
                cin >> fill;
                cout << "\n等腰三角形（高度=" << h << "）：" << endl;
                for (int i = 0; i < h; i++) {
                    for (int j = 0; j < h - i - 1; j++) {
                        cout << "  ";
                    }
                    for (int j = 0; j < 2 * i + 1; j++) {
                        cout << fill << " ";
                    }
                    cout << endl;
                }
                break;

            case 'C':
                // 画菱形
                cout << "输入菱形的半高（不含中间行）：";
                cin >> h;
                cout << "输入填充字符：";
                cin >> fill;
                cout << "\n菱形（半高=" << h << "）：" << endl;
                // 上半部分
                for (int i = 0; i <= h; i++) {
                    for (int j = 0; j < h - i; j++) cout << "  ";
                    for (int j = 0; j < 2 * i + 1; j++) cout << fill << " ";
                    cout << endl;
                }
                // 下半部分
                for (int i = h - 1; i >= 0; i--) {
                    for (int j = 0; j < h - i; j++) cout << "  ";
                    for (int j = 0; j < 2 * i + 1; j++) cout << fill << " ";
                    cout << endl;
                }
                break;

            case 'D':
                // 画实心正方形
                cout << "输入正方形的边长：";
                cin >> w;
                cout << "输入填充字符：";
                cin >> fill;
                cout << "\n实心正方形（边长=" << w << "）：" << endl;
                for (int i = 0; i < w; i++) {
                    for (int j = 0; j < w; j++) {
                        cout << fill << " ";
                    }
                    cout << endl;
                }
                break;

            case 'E': {
                // 显示地形图
                const int R2 = 6, C2 = 6;
                int map[R2][C2] = {
                    {0, 0, 0, 1, 1, 0},
                    {0, 0, 1, 2, 2, 1},
                    {0, 1, 2, 3, 2, 1},
                    {0, 1, 2, 2, 1, 0},
                    {1, 1, 1, 4, 4, 0},
                    {0, 1, 1, 1, 1, 0}
                };
                cout << "\n图例: ~=海洋 .=平原 ^=高山 T=森林 s=沙漠\n" << endl;
                for (int i = 0; i < R2; i++) {
                    cout << "  ";
                    for (int j = 0; j < C2; j++) {
                        switch (map[i][j]) {
                            case 0: cout << "~ "; break;
                            case 1: cout << ". "; break;
                            case 2: cout << "^ "; break;
                            case 3: cout << "T "; break;
                            case 4: cout << "s "; break;
                        }
                    }
                    cout << endl;
                }
                break;
            }

            case 'Q':
                running = false;
                cout << "\n感谢使用字符画创作大师，再见！" << endl;
                break;

            default:
                cout << "\n无效的选择，请重新输入 A/B/C/D/E/Q。" << endl;
                break;
        }
    }
}

// ============================================================
// 主函数
// ============================================================
int main() {
    cout << "╔════════════════════════════════════════╗" << endl;
    cout << "║  第32课：像素小画家——二维数组趣味应用 ║" << endl;
    cout << "║  项目：字符画创作大师                  ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;

    example1_fillPatterns();
    example2_asciiArt();
    example3_terrainMap();
    exerciseAnswers();
    challenge_artCreator();

    cout << "\n================================" << endl;
    cout << "  本课学习完成！" << endl;
    cout << "  核心要点：" << endl;
    cout << "  1. 二维字符数组 = 字符画的\"画布\"" << endl;
    cout << "  2. 图案 = 嵌套循环 + 位置判断条件" << endl;
    cout << "  3. 空心形状只需在边界画字符" << endl;
    cout << "  4. 地形图：数字 -> 符号映射" << endl;
    cout << "  5. 发挥创意，用代码画画！" << endl;
    cout << "================================" << endl;

    return 0;
}
