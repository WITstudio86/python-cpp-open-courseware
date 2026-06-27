/*
 * CSP-J 备考课程
 * 第14课：二维数组
 * 考纲知识点：二维数组定义、初始化、行列遍历、矩阵操作、杨辉三角
 *
 * 本文件包含：
 * 1. 二维数组定义与初始化演示
 * 2. 矩阵输入输出
 * 3. 矩阵转置
 * 4. 对角线元素提取
 * 5. 杨辉三角生成
 * 6. 真题AC代码
 */

#include <iostream>
#include <iomanip>
using namespace std;

const int N = 25;     // 小矩阵用常量
int a[N][N], b[N][N];  // 全局二维数组，避免栈溢出

// 演示1：二维数组定义与初始化
void demo01_definition() {
    cout << "=== 演示1：二维数组定义与初始化 ===" << endl;

    // 方式一：按行初始化（推荐）
    int arr1[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    cout << "按行初始化 arr1[2][3]:" << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            cout << setw(3) << arr1[i][j];
        }
        cout << endl;
    }
    cout << endl;

    // 方式二：省略第一维
    int arr2[][3] = {
        {10, 20, 30},
        {40, 50, 60},
        {70, 80, 90}
    };
    int rows = sizeof(arr2) / sizeof(arr2[0]);
    cout << "省略第一维 arr2 (自动推导为" << rows << "行):" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < 3; j++) {
            cout << setw(4) << arr2[i][j];
        }
        cout << endl;
    }
    cout << endl;

    // 方式三：全部清零
    int arr3[3][3] = {0};
    cout << "全部清零 arr3[3][3]:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << setw(3) << arr3[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

// 演示2：矩阵输入输出
void demo02_io() {
    cout << "=== 演示2：矩阵输入输出 ===" << endl;
    cout << "请输入矩阵行数 n 和列数 m: ";
    int n, m;
    cin >> n >> m;

    cout << "请输入 " << n << "x" << m << " 矩阵的元素:" << endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> a[i][j];

    cout << "矩阵为:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << setw(4) << a[i][j];
        }
        cout << endl;
    }

    // 求总和与平均值
    int sum = 0, cnt = n * m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            sum += a[i][j];
    cout << "元素总和: " << sum << endl;
    cout << "平均值: " << fixed << setprecision(2) << 1.0 * sum / cnt << endl;
    cout << endl;
}

// 演示3：矩阵转置
void demo03_transpose() {
    cout << "=== 演示3：矩阵转置 ===" << endl;
    cout << "请输入矩阵行数 n 和列数 m: ";
    int n, m;
    cin >> n >> m;

    cout << "请输入矩阵元素:" << endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> a[i][j];

    cout << "原矩阵 (" << n << "x" << m << "):" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << setw(4) << a[i][j];
        }
        cout << endl;
    }

    // 转置到 b（b 是 m 行 n 列）
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            b[j][i] = a[i][j];

    cout << "转置矩阵 (" << m << "x" << n << "):" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(4) << b[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

// 演示4：对角线元素
void demo04_diagonal() {
    cout << "=== 演示4：对角线元素提取 ===" << endl;
    cout << "请输入方阵大小 n: ";
    int n;
    cin >> n;

    cout << "请输入 " << n << "x" << n << " 方阵:" << endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];

    cout << "方阵:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(4) << a[i][j];
        }
        cout << endl;
    }

    // 主对角线
    cout << "主对角线元素 (i == j): ";
    int sum1 = 0;
    for (int i = 0; i < n; i++) {
        cout << a[i][i] << " ";
        sum1 += a[i][i];
    }
    cout << "→ 和 = " << sum1 << endl;

    // 副对角线
    cout << "副对角线元素 (i + j == " << n - 1 << "): ";
    int sum2 = 0;
    for (int i = 0; i < n; i++) {
        cout << a[i][n - 1 - i] << " ";
        sum2 += a[i][n - 1 - i];
    }
    cout << "→ 和 = " << sum2 << endl;

    // 边缘元素
    cout << "边缘元素: ";
    int sum3 = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 || i == n - 1 || j == 0 || j == n - 1) {
                cout << a[i][j] << " ";
                sum3 += a[i][j];
            }
        }
    }
    cout << "→ 和 = " << sum3 << endl;
    cout << endl;
}

// 演示5：杨辉三角
void demo05_yanghui() {
    cout << "=== 演示5：杨辉三角 ===" << endl;
    cout << "请输入杨辉三角行数 n (<=20): ";
    int n;
    cin >> n;

    // 初始化数组
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            a[i][j] = 0;
        }
    }

    // 生成杨辉三角
    for (int i = 0; i < n; i++) {
        a[i][0] = 1;    // 每行第一个为 1
        a[i][i] = 1;    // 每行最后一个为 1
        for (int j = 1; j < i; j++) {
            a[i][j] = a[i - 1][j - 1] + a[i - 1][j];
        }
    }

    // 输出
    cout << "杨辉三角前 " << n << " 行:" << endl;
    for (int i = 0; i < n; i++) {
        // 打印前导空格使三角形居中
        for (int k = 0; k < n - i - 1; k++) {
            cout << "  ";
        }
        for (int j = 0; j <= i; j++) {
            cout << setw(3) << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// 演示6：棋盘遍历（按行 vs 按列）
void demo06_traverse_patterns() {
    cout << "=== 演示6：不同遍历顺序对比 ===" << endl;
    int n = 3, m = 4;
    int arr[3][4] = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9, 10, 11, 12}
    };

    cout << "原始矩阵:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << setw(4) << arr[i][j];
        }
        cout << endl;
    }

    cout << "按行遍历 (标准): ";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cout << arr[i][j] << " ";
    cout << endl;

    cout << "按列遍历: ";
    for (int j = 0; j < m; j++)
        for (int i = 0; i < n; i++)
            cout << arr[i][j] << " ";
    cout << endl;
    cout << "注意：按列遍历结果不是按行连续出现的！" << endl << endl;
}

// ============ 真题AC代码 ============

// 真题1：矩阵转置
void exam01_transpose() {
    cout << "=== 真题1：矩阵转置输出 ===" << endl;
    cout << "样例输入：" << endl;
    cout << "2 3" << endl;
    cout << "1 2 3" << endl;
    cout << "4 5 6" << endl << endl;

    cout << "请手动输入测试数据：" << endl;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> a[i][j];

    // 转置到 b（b 是 m x n）
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            b[j][i] = a[i][j];

    cout << "转置结果:" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << b[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// 真题2：杨辉三角
void exam02_yanghui() {
    cout << "=== 真题2：杨辉三角 ===" << endl;
    cout << "样例输入：5" << endl;
    cout << "样例输出：" << endl;
    cout << "1" << endl;
    cout << "1 1" << endl;
    cout << "1 2 1" << endl;
    cout << "1 3 3 1" << endl;
    cout << "1 4 6 4 1" << endl << endl;

    cout << "请手动输入 n: ";
    int n;
    cin >> n;

    // 生成
    for (int i = 0; i < n; i++) {
        a[i][0] = a[i][i] = 1;
        for (int j = 1; j < i; j++) {
            a[i][j] = a[i - 1][j - 1] + a[i - 1][j];
        }
    }

    // 输出
    cout << "输出:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// 主菜单
int main() {
    int choice;

    do {
        cout << "========================================" << endl;
        cout << "   CSP-J 第14课：二维数组 — 代码演示" << endl;
        cout << "========================================" << endl;
        cout << "1. 二维数组定义与初始化演示" << endl;
        cout << "2. 矩阵输入输出" << endl;
        cout << "3. 矩阵转置演示" << endl;
        cout << "4. 对角线元素提取演示" << endl;
        cout << "5. 杨辉三角生成演示" << endl;
        cout << "6. 不同遍历顺序对比演示" << endl;
        cout << "7. 真题1：矩阵转置" << endl;
        cout << "8. 真题2：杨辉三角" << endl;
        cout << "0. 退出" << endl;
        cout << "----------------------------------------" << endl;
        cout << "请输入选项 (0-8): ";
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 0:
                cout << "再见！" << endl;
                break;
            case 1:
                demo01_definition();
                break;
            case 2:
                demo02_io();
                break;
            case 3:
                demo03_transpose();
                break;
            case 4:
                demo04_diagonal();
                break;
            case 5:
                demo05_yanghui();
                break;
            case 6:
                demo06_traverse_patterns();
                break;
            case 7:
                exam01_transpose();
                break;
            case 8:
                exam02_yanghui();
                break;
            default:
                cout << "无效选项，请重新选择！" << endl << endl;
        }
    } while (choice != 0);

    return 0;
}
