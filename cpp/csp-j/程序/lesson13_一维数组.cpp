/*
 * CSP-J 备考课程
 * 第13课：一维数组
 * 考纲知识点：数组定义、初始化、下标从0开始、遍历、越界、应用
 *
 * 本文件包含：
 * 1. 数组定义与初始化演示
 * 2. 数组遍历与最值查找
 * 3. 数组反转
 * 4. 桶计数 / 循环右移
 * 5. 真题AC代码
 *
 * 编译：g++ -std=c++17 lesson13_一维数组.cpp -o lesson13
 */

#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

const int N = 1005;
int a[N];  // 全局大数组，避免栈溢出

// 演示1：数组定义与初始化
void demo01_definition() {
    cout << "=== 演示1：数组定义与初始化 ===" << endl;

    // 方式一：全部初始化
    int arr1[5] = {10, 20, 30, 40, 50};
    cout << "全部初始化 arr1: ";
    for (int i = 0; i < 5; i++) cout << arr1[i] << " ";
    cout << endl;

    // 方式二：部分初始化（未指定的自动为0）
    int arr2[5] = {1, 2};
    cout << "部分初始化 arr2: ";
    for (int i = 0; i < 5; i++) cout << arr2[i] << " ";
    cout << endl;

    // 方式三：全部清零
    int arr3[10] = {0};
    cout << "全部清零 arr3: ";
    for (int i = 0; i < 10; i++) cout << arr3[i] << " ";
    cout << endl;

    // 方式四：省略大小
    int arr4[] = {1, 3, 5, 7, 9};
    int sz = sizeof(arr4) / sizeof(arr4[0]);
    cout << "省略大小 arr4 (大小=" << sz << "): ";
    for (int i = 0; i < sz; i++) cout << arr4[i] << " ";
    cout << endl << endl;
}

// 演示2：下标从0开始
void demo02_index() {
    cout << "=== 演示2：下标从0开始 ===" << endl;
    int arr[5] = {100, 200, 300, 400, 500};
    cout << "数组大小: 5" << endl;
    cout << "arr[0] (第1个) = " << arr[0] << endl;
    cout << "arr[1] (第2个) = " << arr[1] << endl;
    cout << "arr[4] (第5个/最后) = " << arr[4] << endl;
    cout << "有效下标范围: 0 ~ " << 5 - 1 << endl;
    cout << endl;
}

// 演示3：数组遍历与统计
void demo03_traverse() {
    cout << "=== 演示3：数组遍历与统计 ===" << endl;
    int n = 8;
    int arr[8] = {85, 92, 78, 65, 90, 88, 73, 95};

    cout << "原始数据: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    // 求和
    int sum = 0;
    for (int i = 0; i < n; i++) sum += arr[i];
    cout << "总和: " << sum << endl;
    cout << "平均值: " << fixed << setprecision(2) << 1.0 * sum / n << endl;

    // 找最值
    int maxVal = arr[0], minVal = arr[0], maxPos = 0, minPos = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) { maxVal = arr[i]; maxPos = i; }
        if (arr[i] < minVal) { minVal = arr[i]; minPos = i; }
    }
    cout << "最大值: " << maxVal << " (位置: " << maxPos + 1 << ")" << endl;
    cout << "最小值: " << minVal << " (位置: " << minPos + 1 << ")" << endl;

    // 统计及格人数（>=60）
    int passCount = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] >= 60) passCount++;
    }
    cout << "及格人数(>=60): " << passCount << endl;
    cout << endl;
}

// 演示4：数组反转
void demo04_reverse() {
    cout << "=== 演示4：数组反转 ===" << endl;
    int n = 6;
    int arr[6] = {1, 2, 3, 4, 5, 6};

    cout << "反转前: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    // 反转算法
    for (int i = 0; i < n / 2; i++) {
        swap(arr[i], arr[n - 1 - i]);
    }

    cout << "反转后: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl << endl;
}

// 演示5：线性查找
void demo05_search() {
    cout << "=== 演示5：线性查找 ===" << endl;
    int n = 7;
    int arr[7] = {15, 8, 23, 42, 4, 16, 30};

    cout << "数组: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    int target = 42;
    int pos = -1;
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            pos = i;
            break;
        }
    }

    if (pos != -1)
        cout << target << " 找到了，位置: " << pos + 1 << endl;
    else
        cout << target << " 未找到" << endl;

    target = 99;
    pos = -1;
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) { pos = i; break; }
    }
    if (pos != -1)
        cout << target << " 找到了，位置: " << pos + 1 << endl;
    else
        cout << target << " 未找到" << endl;
    cout << endl;
}

// 演示6：桶计数（分数 0~100）
void demo06_bucket_count() {
    cout << "=== 演示6：桶计数统计 ===" << endl;
    int n = 8;
    int arr[8] = {85, 92, 78, 85, 90, 85, 73, 92};
    int cnt[101] = {0};

    cout << "成绩: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
        cnt[arr[i]]++;
    }
    cout << endl;

    cout << "出现次数 > 0 的分数:" << endl;
    for (int s = 0; s <= 100; s++) {
        if (cnt[s] > 0) {
            cout << "  分数 " << s << " 出现 " << cnt[s] << " 次" << endl;
        }
    }
    cout << endl;
}

// 演示7：循环右移 k 位
void demo07_rotate_right() {
    cout << "=== 演示7：循环右移 ===" << endl;
    int n = 6;
    int arr[6] = {1, 2, 3, 4, 5, 6};
    int k = 2;
    k %= n;

    cout << "原数组: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
    cout << "右移 k=" << k << " 位" << endl;

    int b[6];
    for (int i = 0; i < n; i++) {
        b[(i + k) % n] = arr[i];
    }
    cout << "结果: ";
    for (int i = 0; i < n; i++) cout << b[i] << " ";
    cout << endl << endl;
}

// ============ 真题AC代码 ============

// 真题1：不与最大数相同的数字之和
void exam01_maxExcludeSum() {
    cout << "=== 真题1：不与最大数相同的数字之和 ===" << endl;
    cout << "输入示例：" << endl;
    cout << "3" << endl;
    cout << "1 2 3" << endl;
    cout << "预期输出：3" << endl << endl;

    cout << "请手动输入测试数据：" << endl;
    int n;
    cin >> n;

    int maxVal = -2000000;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] > maxVal) maxVal = a[i];
    }

    int sum = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] != maxVal) sum += a[i];
    }
    cout << "输出: " << sum << endl;
    cout << endl;
}

// 真题2：数组逆序重放
void exam02_reverseArray() {
    cout << "=== 真题2：数组逆序重放 ===" << endl;
    cout << "输入示例：" << endl;
    cout << "5" << endl;
    cout << "8 6 5 4 1" << endl;
    cout << "预期输出：1 4 5 6 8" << endl << endl;

    cout << "请手动输入测试数据：" << endl;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];

    // 双指针法反转
    int left = 0, right = n - 1;
    while (left < right) {
        int temp = a[left];
        a[left] = a[right];
        a[right] = temp;
        left++;
        right--;
    }

    cout << "输出: ";
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl << endl;
}

// 主菜单
int main() {
    int choice;

    do {
        cout << "========================================" << endl;
        cout << "   CSP-J 第13课：一维数组 — 代码演示" << endl;
        cout << "========================================" << endl;
        cout << "1. 数组定义与初始化演示" << endl;
        cout << "2. 下标从0开始演示" << endl;
        cout << "3. 数组遍历与统计（求和、平均、最值、及格率）" << endl;
        cout << "4. 数组反转演示" << endl;
        cout << "5. 线性查找演示" << endl;
        cout << "6. 桶计数统计演示" << endl;
        cout << "7. 循环右移演示" << endl;
        cout << "8. 真题1：不与最大数相同的数字之和" << endl;
        cout << "9. 真题2：数组逆序重放" << endl;
        cout << "0. 退出" << endl;
        cout << "----------------------------------------" << endl;
        cout << "请输入选项 (0-9): ";
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
                demo02_index();
                break;
            case 3:
                demo03_traverse();
                break;
            case 4:
                demo04_reverse();
                break;
            case 5:
                demo05_search();
                break;
            case 6:
                demo06_bucket_count();
                break;
            case 7:
                demo07_rotate_right();
                break;
            case 8:
                exam01_maxExcludeSum();
                break;
            case 9:
                exam02_reverseArray();
                break;
            default:
                cout << "无效选项，请重新选择！" << endl << endl;
        }
    } while (choice != 0);

    return 0;
}
