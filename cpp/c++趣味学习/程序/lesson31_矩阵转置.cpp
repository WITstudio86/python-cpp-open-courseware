/*
 * 第31课：位置大变换——矩阵转置
 * 项目：神奇的矩阵翻转
 * 第三单元：数据的组织
 *
 * 本课学习：
 *   1. 方阵的原地转置
 *   2. 长方形矩阵转置（MxN -> NxM）
 *   3. 对角线元素识别
 *   4. 对称矩阵判断
 *
 * 日期：2026年6月
 */

#include <iostream>
#include <iomanip>
using namespace std;

// ============================================================
// 示例1：方阵的原地转置 (In-Place Transpose)
// ============================================================
void example1_squareTranspose() {
    cout << "========================================" << endl;
    cout << "  示例1：方阵的原地转置" << endl;
    cout << "========================================" << endl;

    const int N = 3;
    int a[N][N] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    cout << "\n原始矩阵：" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << setw(4) << a[i][j];
        }
        cout << endl;
    }

    // 原地转置：只交换对角线上方的元素
    // 关键：内层循环从 j = i+1 开始，避免重复交换
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            // 交换 a[i][j] 和 a[j][i]
            int temp = a[i][j];
            a[i][j] = a[j][i];
            a[j][i] = temp;
        }
    }

    cout << "\n转置后矩阵：" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << setw(4) << a[i][j];
        }
        cout << endl;
    }

    cout << "\n观察：第1列变成了 {1, 4, 7}，原来第1行的 {1, 2, 3} 变成了第1列。" << endl;
    cout << "主对角线上的元素 {1, 5, 9} 位置没有改变！" << endl;
}

// ============================================================
// 示例2：长方形矩阵转置 (MxN -> NxM)
// ============================================================
void example2_rectangularTranspose() {
    cout << "\n========================================" << endl;
    cout << "  示例2：长方形矩阵转置 (3x4 -> 4x3)" << endl;
    cout << "========================================" << endl;

    const int M = 3;  // 原矩阵行数
    const int N = 4;  // 原矩阵列数
    int a[M][N] = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9, 10, 11, 12}
    };
    int b[N][M];  // 转置后：N行 M列

    cout << "\n原始矩阵 (" << M << " 行 × " << N << " 列)：" << endl;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cout << setw(4) << a[i][j];
        }
        cout << endl;
    }

    // 转置到新矩阵：b[j][i] = a[i][j]
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            b[j][i] = a[i][j];
        }
    }

    cout << "\n转置后矩阵 (" << N << " 行 × " << M << " 列)：" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << setw(4) << b[i][j];
        }
        cout << endl;
    }

    cout << "\n注意：长方形矩阵不能原地转置，因为行数和列数不同！" << endl;
    cout << "必须创建一个新矩阵来存储转置结果。" << endl;
}

// ============================================================
// 示例3：完整程序——矩阵转置 + 对角线高亮 + 对称判断
// ============================================================
void example3_completeProgram() {
    cout << "\n========================================" << endl;
    cout << "  示例3：矩阵转置 + 对角线识别 + 对称判断" << endl;
    cout << "========================================" << endl;

    const int SIZE = 4;
    int original[SIZE][SIZE] = {
        {2, 5, 8, 3},
        {5, 7, 4, 9},
        {8, 4, 5, 0},
        {3, 9, 0, 4}
    };
    int transposed[SIZE][SIZE];  // 存储转置结果

    // ---- 显示原始矩阵（标记主对角线） ----
    cout << "\n原始矩阵（[]表示主对角线元素 i==j）：" << endl;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i == j) {
                cout << "[" << setw(2) << original[i][j] << "]";
            } else {
                cout << " " << setw(2) << original[i][j] << " ";
            }
        }
        cout << endl;
    }

    // ---- 转置 ----
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            transposed[i][j] = original[j][i];
            // 等价于：transposed[j][i] = original[i][j];
            // 两种写法都可以，只要下标互换即可
        }
    }

    // ---- 显示转置矩阵（标记主对角线） ----
    cout << "\n转置后矩阵（[]表示主对角线元素）：" << endl;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i == j) {
                cout << "[" << setw(2) << transposed[i][j] << "]";
            } else {
                cout << " " << setw(2) << transposed[i][j] << " ";
            }
        }
        cout << endl;
    }

    // ---- 显示副对角线元素 ----
    cout << "\n副对角线元素（i + j == " << SIZE - 1 << "）：" << endl;
    cout << "原始矩阵的副对角线: ";
    for (int i = 0; i < SIZE; i++) {
        cout << original[i][SIZE - 1 - i] << " ";
    }
    cout << endl;

    // ---- 判断是否为对称矩阵 ----
    bool isSymmetric = true;
    for (int i = 0; i < SIZE && isSymmetric; i++) {
        for (int j = 0; j < SIZE && isSymmetric; j++) {
            if (original[i][j] != original[j][i]) {
                isSymmetric = false;
            }
        }
    }

    cout << "\n对称矩阵判断：" << endl;
    if (isSymmetric) {
        cout << "✓ 该矩阵是 对称矩阵！(A^T == A)" << endl;
        cout << "  因为对任意 i,j 都有 a[i][j] == a[j][i]。" << endl;
        cout << "  转置后矩阵和原始矩阵完全一样！" << endl;
    } else {
        cout << "✗ 该矩阵不是 对称矩阵。" << endl;
        cout << "  转置后矩阵与原始矩阵不同。" << endl;
    }
}

// ============================================================
// 课后练习答案
// ============================================================
void exerciseAnswers() {
    cout << "\n========================================" << endl;
    cout << "  课后练习答案" << endl;
    cout << "========================================" << endl;

    // ---- 练习1：用户输入矩阵并转置 ----
    cout << "\n【练习1】用户输入3x3矩阵并转置：" << endl;
    const int N1 = 3;
    int mat[N1][N1];
    int trans[N1][N1];

    cout << "请输入 3x3 矩阵的9个元素（每输入一个按回车）：" << endl;
    for (int i = 0; i < N1; i++) {
        for (int j = 0; j < N1; j++) {
            cout << "a[" << i << "][" << j << "] = ";
            cin >> mat[i][j];
        }
    }

    cout << "\n原始矩阵：" << endl;
    for (int i = 0; i < N1; i++) {
        for (int j = 0; j < N1; j++) {
            cout << setw(4) << mat[i][j];
        }
        cout << endl;
    }

    // 转置
    for (int i = 0; i < N1; i++) {
        for (int j = 0; j < N1; j++) {
            trans[j][i] = mat[i][j];
        }
    }

    cout << "\n转置后矩阵：" << endl;
    for (int i = 0; i < N1; i++) {
        for (int j = 0; j < N1; j++) {
            cout << setw(4) << trans[i][j];
        }
        cout << endl;
    }

    // ---- 练习2：判断对称矩阵 ----
    cout << "\n【练习2】判断对称矩阵：" << endl;
    const int N2 = 3;
    int symMat[N2][N2] = {
        {1, 2, 3},
        {2, 4, 5},
        {3, 5, 6}
    };

    cout << "待判断的矩阵：" << endl;
    for (int i = 0; i < N2; i++) {
        for (int j = 0; j < N2; j++) {
            cout << setw(4) << symMat[i][j];
        }
        cout << endl;
    }

    bool sym = true;
    for (int i = 0; i < N2 && sym; i++) {
        for (int j = 0; j < N2 && sym; j++) {
            if (symMat[i][j] != symMat[j][i]) {
                sym = false;
            }
        }
    }

    if (sym) {
        cout << "结果：这是一个对称矩阵！" << endl;
    } else {
        cout << "结果：这不是对称矩阵。" << endl;
    }

    // ---- 练习3：长方形矩阵转置 (2x4 -> 4x2) ----
    cout << "\n【练习3】长方形矩阵转置 (2x4 -> 4x2)：" << endl;
    const int M3 = 2, N3 = 4;
    int rect[M3][N3] = {
        {10, 20, 30, 40},
        {50, 60, 70, 80}
    };
    int rectT[N3][M3];

    cout << "原始矩阵 (2行×4列)：" << endl;
    for (int i = 0; i < M3; i++) {
        for (int j = 0; j < N3; j++) {
            cout << setw(4) << rect[i][j];
        }
        cout << endl;
    }

    for (int i = 0; i < M3; i++) {
        for (int j = 0; j < N3; j++) {
            rectT[j][i] = rect[i][j];
        }
    }

    cout << "\n转置后矩阵 (4行×2列)：" << endl;
    for (int i = 0; i < N3; i++) {
        for (int j = 0; j < M3; j++) {
            cout << setw(4) << rectT[i][j];
        }
        cout << endl;
    }

    // ---- 挑战任务演示：矩阵翻转大师 ----
    cout << "\n========================================" << endl;
    cout << "  挑战任务：矩阵翻转大师" << endl;
    cout << "========================================" << endl;

    const int SIZE_C = 4;
    int challenge[SIZE_C][SIZE_C];
    int challengeT[SIZE_C][SIZE_C];

    cout << "\n请输入 4x4 方阵的16个元素：" << endl;
    for (int i = 0; i < SIZE_C; i++) {
        for (int j = 0; j < SIZE_C; j++) {
            cout << "a[" << i << "][" << j << "] = ";
            cin >> challenge[i][j];
        }
    }

    // 转置
    for (int i = 0; i < SIZE_C; i++) {
        for (int j = 0; j < SIZE_C; j++) {
            challengeT[i][j] = challenge[j][i];
        }
    }

    // 显示原始矩阵（标记主对角线）
    cout << "\n原始矩阵（[]标记主对角线）：" << endl;
    for (int i = 0; i < SIZE_C; i++) {
        for (int j = 0; j < SIZE_C; j++) {
            if (i == j) {
                cout << "[" << setw(3) << challenge[i][j] << "]";
            } else {
                cout << " " << setw(3) << challenge[i][j] << " ";
            }
        }
        cout << endl;
    }

    // 显示转置矩阵（标记主对角线）
    cout << "\n转置矩阵（[]标记主对角线）：" << endl;
    for (int i = 0; i < SIZE_C; i++) {
        for (int j = 0; j < SIZE_C; j++) {
            if (i == j) {
                cout << "[" << setw(3) << challengeT[i][j] << "]";
            } else {
                cout << " " << setw(3) << challengeT[i][j] << " ";
            }
        }
        cout << endl;
    }

    // 副对角线
    cout << "\n副对角线元素（i + j == " << SIZE_C - 1 << "）：" << endl;
    cout << "原始: ";
    for (int i = 0; i < SIZE_C; i++) {
        cout << challenge[i][SIZE_C - 1 - i] << " ";
    }
    cout << endl;
    cout << "转置: ";
    for (int i = 0; i < SIZE_C; i++) {
        cout << challengeT[i][SIZE_C - 1 - i] << " ";
    }
    cout << endl;

    // 对称判断
    bool challengeSym = true;
    for (int i = 0; i < SIZE_C && challengeSym; i++) {
        for (int j = 0; j < SIZE_C && challengeSym; j++) {
            if (challenge[i][j] != challenge[j][i]) {
                challengeSym = false;
            }
        }
    }

    cout << "\n对称矩阵判断：";
    if (challengeSym) {
        cout << "是！(A^T == A)" << endl;
    } else {
        cout << "否。(A^T != A)" << endl;
    }
}

// ============================================================
// 主函数
// ============================================================
int main() {
    cout << "╔════════════════════════════════════════╗" << endl;
    cout << "║  第31课：位置大变换——矩阵转置        ║" << endl;
    cout << "║  项目：神奇的矩阵翻转                 ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;

    example1_squareTranspose();
    example2_rectangularTranspose();
    example3_completeProgram();
    exerciseAnswers();

    cout << "\n================================" << endl;
    cout << "  本课学习完成！" << endl;
    cout << "  核心要点：" << endl;
    cout << "  1. 转置：a[i][j] <-> a[j][i]" << endl;
    cout << "  2. 方阵可原地转置，长方形需新数组" << endl;
    cout << "  3. 主对角线(i==j)元素不移动" << endl;
    cout << "  4. 对称矩阵满足 A^T == A" << endl;
    cout << "================================" << endl;

    return 0;
}
