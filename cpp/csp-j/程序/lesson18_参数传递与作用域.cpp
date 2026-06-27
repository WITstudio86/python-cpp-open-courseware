/**
 * 第18课：参数传递与作用域 —— 完整演示程序
 *
 * 本程序演示了 C++ 中参数传递和变量作用域的核心概念：
 * 1. 值传递（形参获得实参的副本，不改变原始变量）
 * 2. 引用传递（& 符号，改变原始变量）
 * 3. 数组作为参数（传递首地址，修改会反映到原始数组）
 * 4. 全局变量的使用
 * 5. 静态变量 static（生命周期贯穿整个程序，只初始化一次）
 * 6. 局部变量的作用域和生命周期
 */

#include <iostream>
using namespace std;

// ==================== 全局变量 ====================
int globalCounter = 0;   // 全局变量，自动初始化为 0
int globalMax = -10000;  // 用于记录全局最大值

// ==================== 函数声明 ====================

// 值传递演示
void tryModifyByValue(int num);
void demonstrateValuePass();

// 引用传递演示
void swap(int &a, int &b);
void incrementBoth(int &a, int &b, int amount);
void getSumAndDiff(int a, int b, int &sum, int &diff);
void demonstrateReferencePass();

// 数组参数演示
void doubleElements(int arr[], int n);
void resetArray(int arr[], int n, int value);
void printArray(const int arr[], int n);
void demonstrateArrayParam();

// 全局变量演示
void updateGlobalCounter();
void updateGlobalMax(int val);
void readAndUpdateGlobal();
void demonstrateGlobalVars();

// 静态变量演示
int getNextID();
void countCalls();
void demonstrateStaticVars();

// 局部变量作用域演示
void demonstrateLocalScope();

// 综合演示
void mixedScopeDemo();

// ==================== 主函数 ====================

int main() {
    cout << "============================================" << endl;
    cout << "  第18课：参数传递与作用域 —— 演示程序" << endl;
    cout << "============================================" << endl;

    // ---------- 1. 值传递演示 ----------
    cout << "\n【1. 值传递演示 —— 修改形参不影响实参】" << endl;
    demonstrateValuePass();

    // ---------- 2. 引用传递演示 ----------
    cout << "\n【2. 引用传递演示 —— & 符号让函数修改实参】" << endl;
    demonstrateReferencePass();

    // ---------- 3. 数组参数演示 ----------
    cout << "\n【3. 数组参数演示 —— 传递地址，修改影响原数组】" << endl;
    demonstrateArrayParam();

    // ---------- 4. 全局变量演示 ----------
    cout << "\n【4. 全局变量演示 —— 所有函数共享的数据】" << endl;
    demonstrateGlobalVars();

    // ---------- 5. 静态变量演示 ----------
    cout << "\n【5. 静态变量演示 —— 只初始化一次，跨调用保持值】" << endl;
    demonstrateStaticVars();

    // ---------- 6. 局部变量作用域演示 ----------
    cout << "\n【6. 局部变量作用域演示 —— 离开作用域即销毁】" << endl;
    demonstrateLocalScope();

    // ---------- 7. 综合演示 ----------
    cout << "\n【7. 综合演示 —— 全局/静态/局部变量同台】" << endl;
    mixedScopeDemo();

    cout << "\n============================================" << endl;
    cout << "            演示程序运行完毕" << endl;
    cout << "============================================" << endl;

    return 0;
}

// ==================== 值传递函数 ====================

void tryModifyByValue(int num) {
    cout << "  函数内（修改前）：num = " << num << endl;
    num = 9999;
    cout << "  函数内（修改后）：num = " << num << endl;
}

void demonstrateValuePass() {
    int a = 42;
    cout << "  调用前：a = " << a << endl;
    tryModifyByValue(a);
    cout << "  调用后：a = " << a << "  ← 未改变！因为值传递只传递了副本" << endl;

    cout << "\n  再测一个例子：" << endl;
    int x = 100, y = 200;
    cout << "  交换前：x = " << x << ", y = " << y << endl;

    // 注意：swap 接受引用参数，这里是为了对比演示
    // 如果有一个"值传递版 swap"，下面的代码就无法真正交换
    cout << "  （提示：值传递版 swap 无法真正交换，因为只交换了副本）" << endl;
}

// ==================== 引用传递函数 ====================

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void incrementBoth(int &a, int &b, int amount) {
    a += amount;
    b += amount;
}

void getSumAndDiff(int a, int b, int &sum, int &diff) {
    sum = a + b;
    diff = (a > b) ? (a - b) : (b - a);
}

void demonstrateReferencePass() {
    // swap 演示
    int m = 100, n = 200;
    cout << "  [swap 函数]" << endl;
    cout << "  交换前：m = " << m << ", n = " << n << endl;
    swap(m, n);
    cout << "  交换后：m = " << m << ", n = " << n << "  ← 真正交换了！" << endl;

    // incrementBoth 演示
    int p = 10, q = 20;
    cout << "\n  [incrementBoth 函数]" << endl;
    cout << "  增加前：p = " << p << ", q = " << q << endl;
    incrementBoth(p, q, 5);
    cout << "  各增加 5 后：p = " << p << ", q = " << q << "  ← 两个都改变了！" << endl;

    // getSumAndDiff 演示 —— 通过引用"返回"多个值
    cout << "\n  [getSumAndDiff 函数 —— 通过引用返回多个结果]" << endl;
    int s, d;
    getSumAndDiff(30, 12, s, d);
    cout << "  30 和 12：sum = " << s << ", diff = " << d << endl;
}

// ==================== 数组参数函数 ====================

void doubleElements(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] *= 2;
    }
}

void resetArray(int arr[], int n, int value) {
    for (int i = 0; i < n; i++) {
        arr[i] = value;
    }
}

void printArray(const int arr[], int n) {
    cout << "  [";
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "]" << endl;
}

void demonstrateArrayParam() {
    int nums[] = {1, 3, 5, 7, 9};

    cout << "  原始数组：";
    printArray(nums, 5);

    doubleElements(nums, 5);
    cout << "  doubleElements 后（原数组被修改）：";
    printArray(nums, 5);

    resetArray(nums, 5, 0);
    cout << "  resetArray 重置为 0 后：";
    printArray(nums, 5);

    cout << "  → 说明：数组参数传递的是首地址，函数内修改数组元素" << endl;
    cout << "           会直接影响原始数组，类似引用传递的效果。" << endl;
}

// ==================== 全局变量函数 ====================

void updateGlobalCounter() {
    globalCounter++;
    cout << "  globalCounter 从 " << globalCounter - 1
         << " 增加到 " << globalCounter << endl;
}

void updateGlobalMax(int val) {
    if (val > globalMax) {
        cout << "  globalMax 更新：从 " << globalMax << " 到 " << val << endl;
        globalMax = val;
    } else {
        cout << "  globalMax 保持不变：当前值 " << globalMax
             << "，传入值 " << val << endl;
    }
}

void readAndUpdateGlobal() {
    cout << "  [readAndUpdateGlobal] 读取 globalCounter = " << globalCounter << endl;
    globalCounter += 5;
    cout << "  [readAndUpdateGlobal] 修改后 globalCounter = " << globalCounter << endl;
}

void demonstrateGlobalVars() {
    cout << "  初始 globalCounter = " << globalCounter << endl;
    updateGlobalCounter();
    updateGlobalCounter();
    readAndUpdateGlobal();
    updateGlobalCounter();
    cout << "  最终 globalCounter = " << globalCounter << endl;

    cout << "\n  全局变量 globalMax（初始 = " << globalMax << "）：" << endl;
    updateGlobalMax(30);
    updateGlobalMax(10);
    updateGlobalMax(50);
    updateGlobalMax(40);
    cout << "  最终 globalMax = " << globalMax << endl;
}

// ==================== 静态变量函数 ====================

int getNextID() {
    static int nextID = 1000;
    return nextID++;
}

void countCalls() {
    static int callCount = 0;
    callCount++;
    cout << "  countCalls 已被调用 " << callCount << " 次" << endl;
}

void demonstrateStaticVars() {
    cout << "  [getNextID —— 每次返回递增的 ID]" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "  第 " << (i + 1) << " 个 ID：" << getNextID() << endl;
    }

    cout << "\n  [countCalls —— 统计函数调用次数]" << endl;
    for (int i = 0; i < 4; i++) {
        countCalls();
    }

    cout << "\n  → 说明：static 变量只初始化一次（第一次执行到时），" << endl;
    cout << "           之后每次调用都保留上一次的值。" << endl;
    cout << "           如果是普通局部变量，每次都会重新初始化为 0。" << endl;
}

// ==================== 局部变量作用域演示 ====================

void demonstrateLocalScope() {
    int outer = 100;
    cout << "  外层作用域：outer = " << outer << endl;

    {
        // 新作用域开始
        int inner = 200;
        cout << "  内层作用域：inner = " << inner << endl;
        cout << "  内层可以访问外层：outer = " << outer << endl;

        int outer = 300;  // 遮蔽外层的 outer
        cout << "  内层遮蔽后的 outer = " << outer << endl;
        cout << "  使用 :: 访问全局 globalCounter = " << ::globalCounter << endl;
    }
    // inner 在这里已经被销毁，无法访问

    cout << "  离开内层后：outer = " << outer << "（恢复为 100）" << endl;

    // 演示局部变量每次调用都重新初始化
    cout << "\n  [局部变量生命周期]" << endl;
    for (int i = 0; i < 3; i++) {
        int localVar = 10;
        localVar += i;
        cout << "  第 " << (i + 1) << " 次进入：localVar = " << localVar << endl;
    }
    cout << "  → 每次进入作用域，localVar 都重新初始化为 10，然后加 i。" << endl;
    cout << "    如果是 static int localVar = 10; 结果就会不同。" << endl;
}

// ==================== 综合演示 ====================

void mixedScopeDemo() {
    cout << "  当前全局变量 globalCounter = " << globalCounter << endl;

    // 演示 static 和全局变量的区别
    cout << "  [静态 vs 全局变量]" << endl;
    for (int i = 0; i < 3; i++) {
        static int staticLocal = 0;
        staticLocal++;
        globalCounter++;

        cout << "  第 " << (i + 1) << " 轮：" << endl;
        cout << "    static 局部变量 = " << staticLocal << endl;
        cout << "    全局变量 = " << globalCounter << endl;
    }

    cout << "\n  → static 局部变量只在所在函数中可见，但生命周期为整个程序。" << endl;
    cout << "  → 全局变量在所有函数中都可见，生命周期也为整个程序。" << endl;
}
