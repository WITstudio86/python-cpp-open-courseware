#include <iostream>
#include <cstdio>
using namespace std;

// ==================== 辅助函数 ====================
void printSeparator(const string &title) {
    cout << "\n========== " << title << " ==========" << endl;
}

// ==================== 1. 指针基本声明与初始化 ====================
void demo1_BasicPointer() {
    printSeparator("1. 指针的基本声明与初始化");

    int a = 42;
    double b = 3.14;
    char c = 'A';

    // 声明指针并初始化
    int *pInt = &a;        // pInt 指向 int 变量 a
    double *pDouble = &b;  // pDouble 指向 double 变量 b
    char *pChar = &c;      // pChar 指向 char 变量 c

    cout << "a 的值: " << a << ", a 的地址: " << &a << endl;
    cout << "pInt 存储的地址: " << pInt << ", *pInt = " << *pInt << endl;
    cout << endl;

    cout << "b 的值: " << b << ", b 的地址: " << &b << endl;
    cout << "pDouble 存储的地址: " << pDouble << ", *pDouble = " << *pDouble << endl;
    cout << endl;

    cout << "c 的值: " << c << ", c 的地址: " << (void*)&c << endl;
    cout << "pChar 存储的地址: " << (void*)pChar << ", *pChar = " << *pChar << endl;

    // 指针本身也是变量，也有自己的地址
    cout << "\n指针本身的地址:" << endl;
    cout << "&pInt = " << &pInt << endl;
    cout << "&pDouble = " << &pDouble << endl;
    cout << "&pChar = " << (void*)&pChar << endl;
}

// ==================== 2. 取地址 & 与 解引用 * ====================
void demo2_AddressOfAndDereference() {
    printSeparator("2. 取地址 & 与 解引用 *");

    int x = 100;
    int *ptr = &x;  // & 取地址

    cout << "初始状态: x = " << x << endl;
    cout << "通过 *ptr 读取值: " << *ptr << endl;

    // 通过指针修改原始变量的值
    *ptr = 200;
    cout << "*ptr = 200 后, x = " << x << " (原始变量被修改！)" << endl;

    // 改变指针的指向
    int y = 999;
    ptr = &y;
    cout << "ptr 指向 y 后, *ptr = " << *ptr << endl;

    // 演示指针与普通变量的独立性
    int m = 50;
    int *p1 = &m;
    int *p2 = p1;    // p2 也指向 m
    *p1 = 60;
    cout << "\np1 和 p2 同时指向 m:" << endl;
    cout << "m=" << m << ", *p1=" << *p1 << ", *p2=" << *p2 << " (三者一致)" << endl;
}

// ==================== 3. 指针算术运算 ====================
void demo3_PointerArithmetic() {
    printSeparator("3. 指针算术运算与数组遍历");

    int arr[8] = {10, 20, 30, 40, 50, 60, 70, 80};
    int n = 8;

    cout << "数组元素: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    int *p = arr;  // p 指向 arr[0]

    // 指针与数组名的关系
    cout << "\narr = " << arr << " (数组首地址)" << endl;
    cout << "p   = " << p << " (ptr 指向 arr[0])" << endl;
    cout << "&arr[0] = " << &arr[0] << " (与 arr 相同)" << endl;

    // 指针算术：p + n
    cout << "\n指针算术运算 (int 类型, sizeof(int)=" << sizeof(int) << "):" << endl;
    cout << "p     = " << p << " -> *p = " << *p << endl;
    cout << "p + 1 = " << p + 1 << " -> *(p+1) = " << *(p + 1) << endl;
    cout << "p + 3 = " << p + 3 << " -> *(p+3) = " << *(p + 3) << endl;

    // 用指针遍历数组
    cout << "\n用指针遍历数组: ";
    for (int *q = arr; q < arr + n; q++) {
        cout << *q << " ";
    }
    cout << endl;

    // 验证 arr[i] == *(arr + i) == p[i] == *(p + i)
    cout << "\narr[2] 的四种等价访问方式:" << endl;
    cout << "arr[2]   = " << arr[2] << endl;
    cout << "*(arr+2) = " << *(arr + 2) << endl;
    cout << "p[2]     = " << p[2] << endl;
    cout << "*(p+2)   = " << *(p + 2) << endl;

    // 指针相减
    int *pStart = &arr[2];
    int *pEnd = &arr[6];
    cout << "\n&arr[6] - &arr[2] = " << pEnd - pStart << " (元素个数)" << endl;

    // 演示不同类型指针的步长
    double dArr[3] = {1.1, 2.2, 3.3};
    double *dp = dArr;
    cout << "\n不同类型指针运算的步长差异:" << endl;
    cout << "double *p  : p=" << dp << ", p+1=" << dp + 1
         << " (差 " << sizeof(double) << " 字节)" << endl;
    cout << "int *p     : p=" << p << ", p+1=" << p + 1
         << " (差 " << sizeof(int) << " 字节)" << endl;
}

// ==================== 4. 数组名作为指针 ====================
void demo4_ArrayNameAsPointer() {
    printSeparator("4. 数组名作为指针");

    int arr[6] = {1, 3, 5, 7, 9, 11};

    // 数组名可以像指针一样使用
    cout << "*arr = " << *arr << " (即 arr[0])" << endl;
    cout << "*(arr+3) = " << *(arr + 3) << " (即 arr[3])" << endl;

    // 但不能修改数组名！
    // arr = ...;    // 错误！数组名是常量
    // arr++;        // 错误！数组名是常量

    // sizeof 的区别
    cout << "\nsizeof(arr) = " << sizeof(arr) << " (整个数组的字节数)" << endl;
    int *p = arr;
    cout << "sizeof(p) = " << sizeof(p) << " (指针变量本身的字节数)" << endl;

    // arr 和 &arr 的区别
    cout << "\narr  = " << arr << " (指向第一个元素的指针)" << endl;
    cout << "&arr = " << &arr << " (指向整个数组的指针, 类型不同)" << endl;
    cout << "arr+1 = " << arr + 1 << " (跳到第二个元素)" << endl;
    cout << "&arr+1 = " << &arr + 1 << " (跳过整个数组!)" << endl;
}

// ==================== 5. 用指针的 swap 函数 ====================
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void demo5_SwapFunction() {
    printSeparator("5. 用指针实现 swap 函数");

    int x = 10, y = 20;
    cout << "交换前: x = " << x << ", y = " << y << endl;

    swap(&x, &y);  // 传递 x 和 y 的地址

    cout << "交换后: x = " << x << ", y = " << y << endl;
    cout << "(原始变量 x 和 y 的值被成功交换!)" << endl;

    // 演示与不使用指针的对比
    cout << "\n不使用指针的函数无法交换实参：" << endl;
    int m = 5, n = 8;
    cout << "swap_value(5, 8) 调用后: ";
    // 值传递的 swap（无效）
    auto swap_value = [](int a, int b) { int t = a; a = b; b = t; };
    swap_value(m, n);
    cout << "m = " << m << ", n = " << n << " (未改变！)" << endl;
}

// ==================== 6. 通过指针修改数组 ====================
void doubleArray(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] *= 2;  // 等价于 *(arr + i) *= 2;
    }
}

void addToArray(int *arr, int n, int val) {
    for (int *p = arr; p < arr + n; p++) {
        *p += val;
    }
}

void demo6_ModifyArrayViaPointer() {
    printSeparator("6. 通过指针参数修改数组");

    int nums[6] = {1, 2, 3, 4, 5, 6};
    int n = 6;

    cout << "原始数组: ";
    for (int i = 0; i < n; i++) cout << nums[i] << " ";
    cout << endl;

    doubleArray(nums, n);
    cout << "翻倍后: ";
    for (int i = 0; i < n; i++) cout << nums[i] << " ";
    cout << endl;

    addToArray(nums, n, 10);
    cout << "加10后: ";
    for (int i = 0; i < n; i++) cout << nums[i] << " ";
    cout << endl;
}

// ==================== 7. 用指针找最大最小值 ====================
int* findMax(int *arr, int n) {
    int *maxPtr = arr;
    for (int *p = arr + 1; p < arr + n; p++) {
        if (*p > *maxPtr) maxPtr = p;
    }
    return maxPtr;
}

int* findMin(int *arr, int n) {
    int *minPtr = arr;
    for (int *p = arr + 1; p < arr + n; p++) {
        if (*p < *minPtr) minPtr = p;
    }
    return minPtr;
}

void demo7_FindMaxMin() {
    printSeparator("7. 用指针找最大值和最小值");

    int arr[8] = {45, 12, 78, 34, 90, 23, 56, 8};
    int n = 8;

    cout << "数组: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    int *pMax = findMax(arr, n);
    int *pMin = findMin(arr, n);

    cout << "最大值: " << *pMax << " (位置: " << pMax - arr << ")" << endl;
    cout << "最小值: " << *pMin << " (位置: " << pMin - arr << ")" << endl;

    // pMax - arr 的含义：两个指针相减，得到元素个数
    cout << "\n指针相减说明: pMax - arr = " << pMax - arr
         << " (即从 arr[0] 到最大值的偏移量)" << endl;
}

// ==================== 8. 用指针实现数组反转 ====================
void reverseArray(int *arr, int n) {
    int *left = arr;
    int *right = arr + n - 1;
    while (left < right) {
        int temp = *left;
        *left = *right;
        *right = temp;
        left++;
        right--;
    }
}

void demo8_ArrayReverse() {
    printSeparator("8. 用指针实现数组反转");

    int arr[7] = {1, 2, 3, 4, 5, 6, 7};
    int n = 7;

    cout << "反转前: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    reverseArray(arr, n);

    cout << "反转后: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    // 再次反转，应该恢复原状
    reverseArray(arr, n);
    cout << "再次反转: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
}

// ==================== 9. 空指针安全检查 ====================
void demo9_NullPointerSafety() {
    printSeparator("9. 空指针安全检查");

    // 初始化指针为 nullptr
    int *p1 = nullptr;
    int *p2 = NULL;     // 传统写法（等价于 nullptr）
    int *p3 = nullptr;

    cout << "p1 = " << p1 << " (nullptr)" << endl;
    cout << "p2 = " << p2 << " (NULL)" << endl;

    // 安全检查：解引用前判断
    if (p1 != nullptr) {
        cout << "*p1 = " << *p1 << endl;
    } else {
        cout << "p1 是空指针，跳过解引用！" << endl;
    }

    // 让指针指向有效内存
    int val = 42;
    p3 = &val;

    if (p3 != nullptr) {
        cout << "p3 不为空, *p3 = " << *p3 << endl;
    } else {
        cout << "p3 是空指针！" << endl;
    }

    // 空指针的常见用途
    cout << "\n空指针的常见用途:" << endl;
    cout << "1. 初始化指针为安全状态" << endl;
    cout << "2. 作为函数返回的无效标识" << endl;
    cout << "3. 在解引用前进行安全检查" << endl;
}

// ==================== 10. 指针 vs 引用对比 ====================
void swapByRef(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void demo10_PointerVsReference() {
    printSeparator("10. 指针 vs 引用对比");

    int x = 100, y = 200;

    // 指针方式
    cout << "=== 指针方式 ===" << endl;
    cout << "swap(&x, &y) 调用前: x=" << x << ", y=" << y << endl;
    swap(&x, &y);
    cout << "swap(&x, &y) 调用后: x=" << x << ", y=" << y << endl;

    // 引用方式
    cout << "\n=== 引用方式 ===" << endl;
    cout << "swapByRef(x, y) 调用前: x=" << x << ", y=" << y << endl;
    swapByRef(x, y);
    cout << "swapByRef(x, y) 调用后: x=" << x << ", y=" << y << endl;

    // 对比总结
    cout << "\n--- 对比总结 ---" << endl;
    cout << "指针:" << endl;
    cout << "  声明: int *p = &a;" << endl;
    cout << "  取值: *p" << endl;
    cout << "  可重新指向: p = &b;" << endl;
    cout << "  可为空: p = nullptr;" << endl;
    cout << "  可运算: p++" << endl;
    cout << endl;
    cout << "引用:" << endl;
    cout << "  声明: int &r = a;" << endl;
    cout << "  使用: r (直接当作变量)" << endl;
    cout << "  不可重新绑定" << endl;
    cout << "  不可为空" << endl;
    cout << "  语法更简洁" << endl;
}

// ==================== 11. 指针与字符串 ====================
void demo11_PointerAndString() {
    printSeparator("11. 指针与C风格字符串");

    const char *msg = "Hello CSP-J!";

    // 用指针遍历字符串
    cout << "逐个字符输出: ";
    const char *p = msg;
    while (*p != '\0') {
        cout << *p;
        p++;
    }
    cout << endl;

    cout << "字符串地址: " << (void*)msg << endl;
    cout << "字符串长度(指针遍历): ";
    int len = 0;
    p = msg;
    while (*p != '\0') { len++; p++; }
    cout << len << " 个字符" << endl;
}

// ==================== 主函数 ====================
int main() {
    demo1_BasicPointer();
    demo2_AddressOfAndDereference();
    demo3_PointerArithmetic();
    demo4_ArrayNameAsPointer();
    demo5_SwapFunction();
    demo6_ModifyArrayViaPointer();
    demo7_FindMaxMin();
    demo8_ArrayReverse();
    demo9_NullPointerSafety();
    demo10_PointerVsReference();
    demo11_PointerAndString();

    cout << "\n==================== 所有演示完成 ====================" << endl;
    return 0;
}
