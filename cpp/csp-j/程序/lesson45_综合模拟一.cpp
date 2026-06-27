/**
 * lesson45_综合模拟一.cpp
 * CSP-J 备考课程 - 第45课：综合模拟（一）
 *
 * 内容：选择题+程序阅读+程序填空专项训练
 * 涵盖：计算机基础、进制转换、数据类型、运算符优先级、分支循环、数组字符串
 *
 * 本文件包含：
 * 1. 进制转换函数（十进制 ↔ 二进制/八进制/十六进制）
 * 2. 运算符优先级演示
 * 3. 位运算操作
 * 4. 数组与字符串操作
 * 5. 模拟程序阅读题（含注释解释输出）
 */

#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <climits>
using namespace std;

// ============================================================
// 一、进制转换
// ============================================================

/**
 * 十进制转任意进制（支持 2-36 进制）
 * @param n 待转换的十进制数（非负）
 * @param base 目标进制
 * @return 转换后的字符串
 */
string decToBase(int n, int base) {
    if (n == 0) return "0";
    string digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string result = "";
    while (n > 0) {
        result += digits[n % base];
        n /= base;
    }
    reverse(result.begin(), result.end());
    return result;
}

/**
 * 任意进制转十进制
 * @param s 待转换的字符串（只包含数字和大写字母）
 * @param base 原进制
 * @return 十进制数值
 */
int baseToDec(string s, int base) {
    int result = 0;
    for (char c : s) {
        int digit;
        if (c >= '0' && c <= '9')
            digit = c - '0';
        else if (c >= 'A' && c <= 'Z')
            digit = c - 'A' + 10;
        else
            digit = 0;  // 非法字符
        result = result * base + digit;
    }
    return result;
}

/**
 * 演示进制转换
 */
void demoBaseConversion() {
    cout << "========== 进制转换演示 ==========" << endl;

    // 十进制 → 二进制
    cout << "255 (十进制) → 二进制: " << decToBase(255, 2) << endl;
    cout << "128 (十进制) → 二进制: " << decToBase(128, 2) << endl;

    // 十进制 → 八进制
    cout << "255 (十进制) → 八进制: " << decToBase(255, 8) << endl;

    // 十进制 → 十六进制
    cout << "255 (十进制) → 十六进制: " << decToBase(255, 16) << endl;
    cout << "2024 (十进制) → 十六进制: " << decToBase(2024, 16) << endl;

    // 任意进制 → 十进制
    cout << "11111111 (二进制) → 十进制: " << baseToDec("11111111", 2) << endl;
    cout << "377 (八进制) → 十进制: " << baseToDec("377", 8) << endl;
    cout << "FF (十六进制) → 十进制: " << baseToDec("FF", 16) << endl;
    cout << "2A (十六进制) → 十进制: " << baseToDec("2A", 16) << endl;

    cout << endl;
}

// ============================================================
// 二、运算符优先级演示
// ============================================================

/**
 * 演示各类运算符的优先级和结合性
 */
void demoOperatorPrecedence() {
    cout << "========== 运算符优先级演示 ==========" << endl;

    // 1. 算术运算符 vs 赋值运算符（算术 > 赋值）
    int a = 3 + 4 * 5;  // 4*5=20, 3+20=23
    cout << "3 + 4 * 5 = " << a << " (乘法优先于加法)" << endl;

    // 2. 关系运算符 vs 逻辑运算符（关系 > 逻辑）
    bool b = 5 > 3 && 2 < 4;  // (5>3) && (2<4) → true && true → true
    cout << "5 > 3 && 2 < 4 = " << b << " (关系优先于逻辑与)" << endl;

    // 3. 逻辑非 ! 优先级很高
    bool c = !false && false;  // (!false) && false → true && false → false
    cout << "!false && false = " << c << " (! 优先于 &&)" << endl;

    // 4. 赋值运算符优先级很低，右结合
    int x, y, z;
    x = y = z = 10;  // 右结合: z=10, 返回10; y=10, 返回10; x=10
    cout << "x = y = z = 10 → x=" << x << ", y=" << y << ", z=" << z << endl;

    // 5. 条件运算符（三元）优先级仅高于赋值
    int d = 5 > 3 ? 10 : 20;
    cout << "5 > 3 ? 10 : 20 = " << d << endl;

    // 6. 位运算优先级：<< >> 高于 & ^ |，低于算术
    int e = 1 + 2 << 1;  // (1+2) << 1 → 3 << 1 → 6
    cout << "1 + 2 << 1 = " << e << " (加法优先于左移)" << endl;

    // 7. 常见陷阱：== 和 = 的混淆
    int flag = 5;
    if (flag = 3) {  // 赋值表达式值为 3，非零即 true
        cout << "flag = 3 在 if 中条件为 true（赋值，不是比较！）" << endl;
    }

    cout << endl;
}

// ============================================================
// 三、位运算操作
// ============================================================

/**
 * 演示位运算的各种操作
 */
void demoBitManipulation() {
    cout << "========== 位运算演示 ==========" << endl;

    int a = 5;  // 0101
    int b = 3;  // 0011

    cout << "a = 5 (0101), b = 3 (0011)" << endl;
    cout << "a & b (按位与) = " << (a & b) << " (0001)" << endl;
    cout << "a | b (按位或) = " << (a | b) << " (0111)" << endl;
    cout << "a ^ b (按位异或) = " << (a ^ b) << " (0110)" << endl;
    cout << "~a (按位取反) = " << (~a) << " (...11111010)" << endl;
    cout << "a << 1 (左移1位, 乘2) = " << (a << 1) << endl;
    cout << "a >> 1 (右移1位, 除2) = " << (a >> 1) << endl;

    // 常用位运算技巧
    int x = 8;
    cout << "\n--- 常用位运算技巧 (x=8, 二进制 1000) ---" << endl;

    // 判断奇偶：x & 1，结果为 1 是奇数，0 是偶数
    cout << "x & 1 = " << (x & 1) << " → " << (x & 1 ? "奇数" : "偶数") << endl;

    // 判断是否为 2 的幂：x & (x-1) == 0
    cout << "x & (x-1) = " << (x & (x - 1)) << " → "
         << ((x & (x - 1)) == 0 ? "是2的幂" : "不是2的幂") << endl;

    // 获取第 k 位（最低位为第 0 位）
    int k = 2;
    cout << "x 的第 " << k << " 位 = " << ((x >> k) & 1) << endl;

    // 设置第 k 位为 1
    cout << "x | (1<<1) = " << (x | (1 << 1)) << " (将第1位置1: 1010 = 10)" << endl;

    // 将第 k 位清零
    cout << "x & ~(1<<3) = " << (x & ~(1 << 3)) << " (将第3位清零: 0000 = 0)" << endl;

    // 交换两个数（不使用临时变量）
    int p = 10, q = 20;
    cout << "\n交换前: p=" << p << ", q=" << q << endl;
    p = p ^ q;
    q = p ^ q;
    p = p ^ q;
    cout << "交换后: p=" << p << ", q=" << q << endl;

    cout << endl;
}

// ============================================================
// 四、数组与字符串操作
// ============================================================

/**
 * 演示数组常见操作
 */
void demoArrayOperations() {
    cout << "========== 数组操作演示 ==========" << endl;

    // 一维数组
    int a[] = {3, 1, 4, 1, 5, 9, 2, 6};
    int n = sizeof(a) / sizeof(a[0]);
    cout << "原始数组: ";
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl;

    // 求和
    int sum = 0;
    for (int i = 0; i < n; i++) sum += a[i];
    cout << "求和: " << sum << endl;

    // 求最大值和最小值
    int maxv = a[0], minv = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > maxv) maxv = a[i];
        if (a[i] < minv) minv = a[i];
    }
    cout << "最大值: " << maxv << ", 最小值: " << minv << endl;

    // 反转数组
    for (int i = 0; i < n / 2; i++) {
        swap(a[i], a[n - 1 - i]);
    }
    cout << "反转后: ";
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl;

    // 冒泡排序
    int b[] = {5, 2, 8, 1, 9, 3};
    int m = sizeof(b) / sizeof(b[0]);
    for (int i = 0; i < m - 1; i++) {
        for (int j = 0; j < m - 1 - i; j++) {
            if (b[j] > b[j + 1]) swap(b[j], b[j + 1]);
        }
    }
    cout << "冒泡排序后: ";
    for (int i = 0; i < m; i++) cout << b[i] << " ";
    cout << endl;

    // 使用初始化时默认值（未显式初始化的元素为 0）
    int c[5] = {1, 2};
    cout << "部分初始化数组: c[0]=" << c[0] << " c[1]=" << c[1]
         << " c[2]=" << c[2] << " c[3]=" << c[3] << " c[4]=" << c[4] << endl;

    cout << endl;
}

/**
 * 演示C风格字符串操作
 */
void demoStringOperations() {
    cout << "========== 字符串操作演示 ==========" << endl;

    // C 风格字符串
    char s1[100] = "Hello";
    char s2[] = "World";

    // 字符串长度（不含 '\0'）
    cout << "s1 的长度: " << strlen(s1) << " (不含结束符)" << endl;
    cout << "s1 的 sizeof: " << sizeof(s1) << " (缓冲区大小)" << endl;

    // 字符串拼接
    strcat(s1, " ");
    strcat(s1, s2);
    cout << "拼接后 s1: " << s1 << endl;

    // 字符串复制
    char s3[100];
    strcpy(s3, s1);
    cout << "复制后 s3: " << s3 << endl;

    // 字符串比较
    cout << "strcmp(\"abc\", \"abd\") = " << strcmp("abc", "abd") << " (负数, abc < abd)" << endl;
    cout << "strcmp(\"abc\", \"abc\") = " << strcmp("abc", "abc") << " (0, 相等)" << endl;
    cout << "strcmp(\"abd\", \"abc\") = " << strcmp("abd", "abc") << " (正数, abd > abc)" << endl;

    // 字符分类
    char ch = 'A';
    cout << "\n字符 '" << ch << "' 的分类:" << endl;
    cout << "  大写字母? " << (ch >= 'A' && ch <= 'Z') << endl;
    cout << "  小写字母? " << (ch >= 'a' && ch <= 'z') << endl;
    cout << "  数字? " << (ch >= '0' && ch <= '9') << endl;

    // 大小写转换（利用 ASCII 差值 32）
    char lower = 'a';
    char upper = lower - 32;  // 'a' 的 ASCII 是 97, 'A' 是 65
    cout << "小写 '" << lower << "' → 大写 '" << upper << "'" << endl;

    // 字符串反转
    char s4[] = "ABCDE";
    int len = strlen(s4);
    for (int i = 0; i < len / 2; i++) {
        swap(s4[i], s4[len - 1 - i]);
    }
    cout << "\"ABCDE\" 反转: " << s4 << endl;

    cout << endl;
}

// ============================================================
// 五、模拟程序阅读题
// ============================================================

/**
 * 模拟程序阅读题1：整数除法和取余
 *
 * 原程序：
 * int a = 10, b = 3;
 * cout << a / b << " ";
 * cout << a % b << " ";
 * cout << a / b * b + a % b << " ";
 * cout << double(a) / b << endl;
 *
 * 输出: 3 1 10 3.33333
 */
void programReading1() {
    cout << "========== 模拟程序阅读题1: 整数除法与取余 ==========" << endl;
    int a = 10, b = 3;
    cout << "程序输出: ";
    cout << a / b << " ";          // 整数除法 10/3 = 3
    cout << a % b << " ";          // 取余 10%3 = 1
    cout << a / b * b + a % b << " "; // 商*除数+余数 = 被除数: 3*3+1 = 10
    cout << double(a) / b << endl;    // 浮点除法 10.0/3 ≈ 3.33333
    cout << "解析: 整数除法截断小数，类型转换可得浮点结果" << endl;
    cout << endl;
}

/**
 * 模拟程序阅读题2：循环累加平方和
 *
 * 原程序：
 * int s = 0;
 * for (int i = 1; i <= 5; i++) {
 *     s += i * i;
 * }
 * cout << s << endl;
 *
 * 输出: 55
 */
void programReading2() {
    cout << "========== 模拟程序阅读题2: 循环累加平方和 ==========" << endl;
    int s = 0;
    cout << "累加过程: " << endl;
    for (int i = 1; i <= 5; i++) {
        s += i * i;
        cout << "  i=" << i << ", i*i=" << i * i << ", s=" << s << endl;
    }
    cout << "最终输出: " << s << " (即 1+4+9+16+25)" << endl;
    cout << endl;
}

/**
 * 模拟程序阅读题3：冒泡排序
 *
 * 原程序：对 {2,5,1,8,3} 进行冒泡排序
 * 输出: 1 2 3 5 8
 */
void programReading3() {
    cout << "========== 模拟程序阅读题3: 冒泡排序 ==========" << endl;
    int a[] = {2, 5, 1, 8, 3};
    int n = 5;
    cout << "排序前: ";
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            if (a[j] > a[j + 1]) {
                int t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }
    }

    cout << "排序后: ";
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << " (升序排列: 1 2 3 5 8)" << endl;
    cout << "解析: 外层循环控制趟数(共4趟)，内层循环两两比较交换" << endl;
    cout << endl;
}

/**
 * 模拟程序阅读题4：字符串反转
 *
 * 原程序：void f(char s[]) 对 "ABCDE" 进行反转
 * 输出: EDCBA
 */
void programReading4() {
    cout << "========== 模拟程序阅读题4: 字符串反转 ==========" << endl;
    char str[] = "ABCDE";
    int len = strlen(str);
    cout << "原始字符串: " << str << endl;

    for (int i = 0; i < len / 2; i++) {
        char t = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = t;
        cout << "  第" << (i + 1) << "次交换: 交换 str[" << i << "]='" << str[len - 1 - i]
             << "' 与 str[" << (len - 1 - i) << "]='" << str[i]
             << "' → " << str << endl;
    }

    cout << "最终输出: " << str << " (字符串完全反转)" << endl;
    cout << "解析: len/2=2，共交换2次: A↔E, B↔D，中间C不变" << endl;
    cout << endl;
}

/**
 * 模拟程序阅读题5：递归斐波那契
 *
 * 原程序：输入 8，递归计算 fib(8)
 * 输出: 21
 */
void programReading5() {
    cout << "========== 模拟程序阅读题5: 递归斐波那契 ==========" << endl;
    int fib[20];
    fib[0] = 0;
    fib[1] = 1;
    cout << "斐波那契数列: " << endl;
    for (int i = 2; i <= 8; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    for (int i = 0; i <= 8; i++) {
        cout << "  fib(" << i << ") = " << fib[i] << endl;
    }
    cout << "输入 8 时递归输出: " << fib[8] << endl;
    cout << "解析: fib(0)=0, fib(1)=1, fib(n)=fib(n-1)+fib(n-2)" << endl;
    cout << endl;
}

// ============================================================
// 六、switch穿透陷阱演示
// ============================================================

/**
 * 演示 switch 语句的穿透（fall-through）陷阱
 * CSP-J 选择题和程序阅读题中的高频考点
 */
void demoSwitchFallThrough() {
    cout << "========== switch 穿透陷阱演示 ==========" << endl;

    cout << "case 1: x=2, 无 break → 穿透" << endl;
    int x = 2;
    cout << "输出: ";
    switch (x) {
        case 1: cout << "A";
        case 2: cout << "B";  // x=2, 从这里开始，没有 break
        case 3: cout << "C"; break;  // 穿透到这里，遇到 break 停止
        default: cout << "D";
    }
    cout << endl;
    cout << "解析: case 2 没有 break，执行完 'B' 后继续执行 case 3 的 'C'" << endl;

    cout << "\ncase 2: x=1, 正常不穿透" << endl;
    x = 1;
    cout << "输出: ";
    switch (x) {
        case 1: cout << "A"; break;  // 有 break，执行完停止
        case 2: cout << "B"; break;
        case 3: cout << "C"; break;
        default: cout << "D";
    }
    cout << endl;

    cout << "\ncase 3: x=4, 匹配 default" << endl;
    x = 4;
    cout << "输出: ";
    switch (x) {
        case 1: cout << "A"; break;
        case 2: cout << "B"; break;
        case 3: cout << "C"; break;
        default: cout << "D";  // 没有匹配的 case，执行 default
    }
    cout << endl;

    cout << endl;
}

// ============================================================
// 七、自增自减陷阱演示
// ============================================================

/**
 * 演示自增自减运算符的区别
 */
void demoIncrementDecrement() {
    cout << "========== 自增自减演示 ==========" << endl;

    // 后置 ++ : 先使用，后自增
    int a = 5;
    int b = a++;  // b = 5, 然后 a = 6
    cout << "int a=5; int b=a++; → a=" << a << ", b=" << b
         << " (后置++: 先用后增)" << endl;

    // 前置 ++ : 先自增，后使用
    int c = 5;
    int d = ++c;  // c = 6, 然后 d = 6
    cout << "int c=5; int d=++c; → c=" << c << ", d=" << d
         << " (前置++: 先增后用)" << endl;

    // 数组中的自增
    int arr[] = {10, 20, 30, 40, 50};
    int i = 1;
    cout << "arr[i++] = " << arr[i++] << " (i=1, 取arr[1]=20, 然后i=2)" << endl;
    i = 1;
    cout << "arr[++i] = " << arr[++i] << " (i先增为2, 取arr[2]=30)" << endl;

    cout << endl;
}

// ============================================================
// 八、主函数
// ============================================================

int main() {
    cout << "========================================================" << endl;
    cout << "  CSP-J 第45课：综合模拟（一）— 程序演示" << endl;
    cout << "========================================================" << endl;
    cout << endl;

    // 一、进制转换
    demoBaseConversion();

    // 二、运算符优先级
    demoOperatorPrecedence();

    // 三、位运算
    demoBitManipulation();

    // 四、数组与字符串
    demoArrayOperations();
    demoStringOperations();

    // 五、switch 穿透陷阱
    demoSwitchFallThrough();

    // 六、自增自减陷阱
    demoIncrementDecrement();

    // 七、模拟程序阅读题
    programReading1();
    programReading2();
    programReading3();
    programReading4();
    programReading5();

    // 附加：二分查找演示
    cout << "========== 二分查找演示 ==========" << endl;
    int sortedArr[] = {1, 3, 5, 7, 9, 11, 13, 15};
    int target = 7;
    int left = 0, right = 7;
    int ans = -1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (sortedArr[mid] == target) {
            ans = mid;
            break;
        } else if (sortedArr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    cout << "在 {1,3,5,7,9,11,13,15} 中查找 " << target
         << "，下标为 " << ans << " (值为 " << sortedArr[ans] << ")" << endl;

    // 附加：素数判断演示
    cout << "\n========== 素数判断演示 ==========" << endl;
    for (int num : {2, 3, 4, 17, 21, 97}) {
        bool isPrime = true;
        if (num < 2) isPrime = false;
        for (int i = 2; i <= sqrt(num); i++) {
            if (num % i == 0) {
                isPrime = false;
                break;
            }
        }
        cout << num << (isPrime ? " 是素数" : " 不是素数") << endl;
    }

    cout << "\n========================================================" << endl;
    cout << "  程序演示完毕！" << endl;
    cout << "========================================================" << endl;

    return 0;
}
