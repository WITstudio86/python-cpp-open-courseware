#include <iostream>
#include <cstring>
using namespace std;

// ==================== 1. 汉诺塔问题 ====================
// 函数功能：递归求解汉诺塔问题
// 参数说明：
//   n     - 当前需要移动的盘子数量
//   from  - 起始柱子编号
//   to    - 目标柱子编号
//   aux   - 辅助柱子编号
//   moves - 移动步数计数器（引用传递，累加总步数）
void hanoi(int n, char from, char to, char aux, int &moves) {
    // 递归边界：只剩一个盘子时直接移动
    if (n == 1) {
        moves++;
        cout << "步骤 " << moves << "：将盘子 1 从 " << from << " 移动到 " << to << endl;
        return;
    }
    // 第一步：将上面 n-1 个盘子从 from 借助 to 移动到 aux
    hanoi(n - 1, from, aux, to, moves);
    // 第二步：将最大的盘子（第 n 个）从 from 移动到 to
    moves++;
    cout << "步骤 " << moves << "：将盘子 " << n << " 从 " << from << " 移动到 " << to << endl;
    // 第三步：将 n-1 个盘子从 aux 借助 from 移动到 to
    hanoi(n - 1, aux, to, from, moves);
}

// ==================== 2. 最大公约数 GCD ====================
// 函数功能：使用辗转相除法（欧几里得算法）递归求解最大公约数
// 参数说明：
//   a, b - 两个正整数
// 返回值：a 和 b 的最大公约数
int gcdRecursive(int a, int b) {
    // 递归边界：当 b 为 0 时，a 即为最大公约数
    if (b == 0) {
        return a;
    }
    // 递归调用：gcd(a, b) = gcd(b, a % b)
    return gcdRecursive(b, a % b);
}

// 函数功能：使用辗转相除法迭代求解最大公约数
// 参数说明：
//   a, b - 两个正整数
// 返回值：a 和 b 的最大公约数
int gcdIterative(int a, int b) {
    // 当 b 不为 0 时，持续更新 a 和 b
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// ==================== 3. 二分查找 ====================
// 函数功能：在有序数组中递归查找目标值
// 参数说明：
//   arr    - 有序数组（升序排列）
//   left   - 当前查找区间的左边界下标
//   right  - 当前查找区间的右边界下标
//   target - 需要查找的目标值
// 返回值：目标值的下标（找到时），或 -1（未找到时）
int binarySearch(int arr[], int left, int right, int target) {
    // 打印当前查找区间的信息
    cout << "  查找范围：left = " << left << "（值=" << arr[left] << "）, "
         << "right = " << right << "（值=" << arr[right] << "）";

    // 递归边界：查找区间无效，说明未找到目标值
    if (left > right) {
        cout << " => 区间无效，未找到！" << endl;
        return -1;
    }

    // 计算中间位置，避免整数溢出
    int mid = left + (right - left) / 2;
    cout << ", mid = " << mid << "（值=" << arr[mid] << "）";

    // 找到目标值
    if (arr[mid] == target) {
        cout << " => 找到了！" << endl;
        return mid;
    }
    // 目标值在右半部分
    else if (arr[mid] < target) {
        cout << " => 目标值 " << target << " > " << arr[mid] << "，向右搜索" << endl;
        return binarySearch(arr, mid + 1, right, target);
    }
    // 目标值在左半部分
    else {
        cout << " => 目标值 " << target << " < " << arr[mid] << "，向左搜索" << endl;
        return binarySearch(arr, left, mid - 1, target);
    }
}

// ==================== 4. 全排列生成 ====================
// 函数功能：递归生成 1 到 n 的所有排列（全排列）
// 参数说明：
//   depth - 当前递归深度（已经确定了几个位置的数字）
//   n     - 排列的总长度
//   path  - 存储当前正在生成的排列序列
//   used  - 标记数组，used[i] 为 true 表示数字 i 已经被使用
void permute(int depth, int n, int path[], bool used[]) {
    // 递归边界：所有位置都已填充完毕，输出当前排列
    if (depth == n) {
        cout << "  [";
        for (int i = 0; i < n; i++) {
            cout << path[i];
            if (i < n - 1) {
                cout << ", ";
            }
        }
        cout << "]" << endl;
        return;
    }

    // 尝试将数字 i 放入当前位置（depth）
    for (int i = 1; i <= n; i++) {
        // 如果数字 i 还没有被使用
        if (!used[i]) {
            // 做选择：将 i 放入 path[depth]，并标记为已使用
            path[depth] = i;
            used[i] = true;

            // 递归处理下一个位置
            permute(depth + 1, n, path, used);

            // 回溯：撤销选择，将 i 标记为未使用
            used[i] = false;
        }
    }
}

// ==================== 5. 二进制串生成 ====================
// 函数功能：递归生成长度为 n 的所有二进制串
// 参数说明：
//   depth - 当前递归深度（已经确定了几个位置的字符）
//   n     - 二进制串的总长度
//   str   - 字符数组，存储当前正在生成的二进制串
void generateBinary(int depth, int n, char str[]) {
    // 递归边界：所有位置都已填充完毕，输出当前二进制串
    if (depth == n) {
        // 确保字符串以 '\0' 结尾
        str[n] = '\0';
        cout << "  \"" << str << "\"" << endl;
        return;
    }

    // 分支一：当前位置填 '0'
    str[depth] = '0';
    generateBinary(depth + 1, n, str);

    // 分支二：当前位置填 '1'
    str[depth] = '1';
    generateBinary(depth + 1, n, str);
}

// ==================== 主函数 ====================
int main() {
    // ---------- 汉诺塔问题 ----------
    cout << "==================== 汉诺塔问题 ====================" << endl;

    // 测试 n = 3 的情况
    cout << "\n【测试 1】n = 3 时的汉诺塔移动步骤：" << endl;
    int moves1 = 0;
    hanoi(3, 'A', 'C', 'B', moves1);
    cout << "总步数：" << moves1 << "（理论值：2^3 - 1 = 7）" << endl;

    // 测试 n = 4 的情况
    cout << "\n【测试 2】n = 4 时的汉诺塔移动步骤：" << endl;
    int moves2 = 0;
    hanoi(4, 'A', 'C', 'B', moves2);
    cout << "总步数：" << moves2 << "（理论值：2^4 - 1 = 15）" << endl;

    // ---------- 最大公约数 GCD ----------
    cout << "\n==================== 最大公约数 GCD ====================" << endl;

    // 定义测试数据对
    int testPairs[4][2] = {
        {12, 18},
        {48, 36},
        {1071, 462},
        {17, 13}
    };

    // 逐对测试两种 GCD 方法
    for (int i = 0; i < 4; i++) {
        int a = testPairs[i][0];
        int b = testPairs[i][1];
        cout << "\n【测试 " << (i + 1) << "】gcd(" << a << ", " << b << ")" << endl;
        cout << "  递归法结果：" << gcdRecursive(a, b) << endl;
        cout << "  迭代法结果：" << gcdIterative(a, b) << endl;
    }

    // ---------- 二分查找 ----------
    cout << "\n==================== 二分查找 ====================" << endl;

    // 定义有序数组
    int sortedArr[] = {2, 5, 8, 12, 16, 23, 38, 45, 56, 67, 78};
    int arrSize = sizeof(sortedArr) / sizeof(sortedArr[0]);

    // 打印数组内容
    cout << "\n有序数组：";
    for (int i = 0; i < arrSize; i++) {
        cout << sortedArr[i];
        if (i < arrSize - 1) {
            cout << ", ";
        }
    }
    cout << endl;

    // 测试查找 23（存在的情况）
    cout << "\n【测试 1】查找目标值 23：" << endl;
    int result1 = binarySearch(sortedArr, 0, arrSize - 1, 23);
    if (result1 != -1) {
        cout << "查找成功！目标值 23 的下标为：" << result1 << endl;
    } else {
        cout << "查找失败！目标值 23 不在数组中。" << endl;
    }

    // 测试查找 30（不存在的情况）
    cout << "\n【测试 2】查找目标值 30：" << endl;
    int result2 = binarySearch(sortedArr, 0, arrSize - 1, 30);
    if (result2 != -1) {
        cout << "查找成功！目标值 30 的下标为：" << result2 << endl;
    } else {
        cout << "查找失败！目标值 30 不在数组中。" << endl;
    }

    // ---------- 全排列生成 ----------
    cout << "\n==================== 全排列生成 ====================" << endl;

    int n_perm = 3;
    cout << "\nn = " << n_perm << " 的所有排列（共 " << n_perm << "! = 6 种）：" << endl;

    // 分配存储空间（使用动态分配以满足可变长度数组需求）
    int *path = new int[n_perm];
    bool *used = new bool[n_perm + 1];

    // 初始化 used 数组，将所有数字标记为未使用
    for (int i = 1; i <= n_perm; i++) {
        used[i] = false;
    }

    // 从深度 0 开始递归生成全排列
    permute(0, n_perm, path, used);

    // 释放动态分配的内存
    delete[] path;
    delete[] used;

    // ---------- 二进制串生成 ----------
    cout << "\n==================== 二进制串生成 ====================" << endl;

    int n_bin = 3;
    cout << "\nn = " << n_bin << " 的所有二进制串（共 2^" << n_bin << " = " << (1 << n_bin) << " 种）：" << endl;

    // 分配字符数组空间，多一个位置用于存储字符串结尾符 '\0'
    char *binStr = new char[n_bin + 1];
    binStr[n_bin] = '\0';

    // 从深度 0 开始递归生成所有二进制串
    generateBinary(0, n_bin, binStr);

    // 释放动态分配的内存
    delete[] binStr;

    cout << "\n==================== 程序结束 ====================" << endl;

    return 0;
}
