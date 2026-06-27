/*
 * CSP-J 备考课程
 * 第4课：输入输出与格式化
 * 考纲知识点：cin/cout、scanf/printf、格式化输出(setw/setprecision/fixed)、转义字符、getchar/putchar
 *
 * 本文件包含：
 * 1. cin/cout 基本输入输出
 * 2. scanf/printf 格式化输入输出
 * 3. 格式化控制演示
 * 4. 转义字符演示
 */

#include <iostream>
#include <iomanip>
#include <cstdio>
using namespace std;

int main() {
    cout << "========== CSP-J 第4课：输入输出与格式化 ==========" << endl;
    cout << endl;

    // ===== 一、cin/cout 基本用法 =====
    cout << "【一、cin/cout 基本用法】" << endl;

    int a, b;
    cout << "请输入两个整数（空格分隔）: ";
    cin >> a >> b;
    cout << "你输入的是: a=" << a << ", b=" << b << endl;
    cout << "a + b = " << a + b << endl;
    cout << endl;

    // ===== 二、scanf/printf 基本用法 =====
    cout << "【二、scanf/printf 基本用法】" << endl;

    int x, y;
    cout << "请输入两个整数（空格分隔）: ";
    scanf("%d %d", &x, &y);  // 注意：必须加 &
    printf("你输入的是: x=%d, y=%d\n", x, y);
    printf("x + y = %d\n", x + y);
    cout << endl;

    // ===== 三、格式化输出 =====
    cout << "【三、格式化输出演示】" << endl;

    double pi = 3.1415926535;

    // cout 格式化
    cout << "--- cout 格式化 ---" << endl;
    cout << "默认输出: " << pi << endl;

    cout << fixed << setprecision(3);
    cout << "保留3位小数: " << pi << endl;

    cout << setprecision(6);
    cout << "保留6位小数: " << pi << endl;

    cout << "宽度10右对齐: " << setw(10) << pi << endl;

    // printf 格式化
    cout << endl << "--- printf 格式化 ---" << endl;
    printf("默认输出: %f\n", pi);
    printf("保留2位小数: %.2f\n", pi);
    printf("宽度10，2位小数: %10.2f\n", pi);
    printf("左对齐，宽度10: %-10.2f|\n", pi);
    printf("前导0填充: %010.2f\n", pi);
    printf("科学计数法: %e\n", pi);
    cout << endl;

    // ===== 四、其他格式化演示 =====
    cout << "【四、对齐与填充演示】" << endl;

    cout << left;
    cout << setw(12) << "Name" << setw(8) << "Age" << setw(10) << "Score" << endl;
    cout << setw(12) << "Alice" << setw(8) << 15 << setw(10) << 98.5 << endl;
    cout << setw(12) << "Bob" << setw(8) << 16 << setw(10) << 92.0 << endl;

    // printf 方式
    printf("\n%-12s%-8s%-10s\n", "Name", "Age", "Score");
    printf("%-12s%-8d%-10.1f\n", "Alice", 15, 98.5);
    printf("%-12s%-8d%-10.1f\n", "Bob", 16, 92.0);
    cout << endl;

    // ===== 五、转义字符演示 =====
    cout << "【五、转义字符演示】" << endl;

    cout << "换行符 \\n: 第一行\n第二行" << endl;
    cout << "制表符 \\t: A\tB\tC" << endl;
    cout << "双引号: \"Hello\"" << endl;
    cout << "单引号: \'A\'" << endl;
    cout << "反斜杠: C:\\\\Program Files\\\\" << endl;
    cout << "百分号: printf(\"100%%\");" << endl;
    cout << endl;

    // ===== 六、printf 格式符大全 =====
    cout << "【六、常用格式符参考】" << endl;

    int num = 42;
    long long bigNum = 10000000000LL;
    double val = 3.14159;
    char ch = 'X';

    printf("%%d (int):        %d\n", num);
    printf("%%lld (long long): %lld\n", bigNum);
    printf("%%f (double):      %f\n", val);
    printf("%%c (char):        %c\n", ch);
    printf("%%x (十六进制):    %x\n", num);
    printf("%%X (十六进制大写): %X\n", num);
    printf("%%o (八进制):      %o\n", num);
    printf("%%%% (百分号):    100%%\n");
    cout << endl;

    // ===== 七、字符输入输出 =====
    cout << "【七、字符输入输出演示】" << endl;

    cout << "请输入一个字符: ";
    // 清理输入缓冲区
    while (getchar() != '\n');  // 清掉之前的换行
    char c = getchar();
    cout << "getchar() 读到的字符: '";
    putchar(c);
    cout << "' (ASCII=" << (int)c << ")" << endl;

    cout << "\"Hello\" 每个字符的ASCII码:" << endl;
    const char* str = "Hello";
    for (int i = 0; str[i] != '\0'; i++) {
        printf("  '%c' -> %d\n", str[i], (int)str[i]);
    }

    cout << endl << "========== 第4课演示结束 ==========" << endl;
    return 0;
}
