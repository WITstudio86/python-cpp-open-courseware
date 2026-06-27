/*
 * CSP-J 备考课程
 * 第3课：变量与基本数据类型
 * 考纲知识点：int/long long/float/double/char/bool、变量命名规则、sizeof、const
 *
 * 本文件包含：
 * 1. 各数据类型大小演示
 * 2. 变量命名合法示例
 * 3. const 常量使用
 * 4. 数据类型选择建议
 */

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    cout << "========== CSP-J 第3课：变量与基本数据类型 ==========" << endl;

    // ===== 一、各数据类型大小 =====
    cout << endl << "【一、各数据类型占用字节数】" << endl;
    cout << "int:       " << sizeof(int) << " 字节 (范围: ±21亿)" << endl;
    cout << "long long: " << sizeof(long long) << " 字节 (范围: ±9×10¹⁸)" << endl;
    cout << "float:     " << sizeof(float) << " 字节 (约7位有效数字)" << endl;
    cout << "double:    " << sizeof(double) << " 字节 (约15位有效数字)" << endl;
    cout << "char:      " << sizeof(char) << " 字节" << endl;
    cout << "bool:      " << sizeof(bool) << " 字节" << endl;

    // ===== 二、基本数据类型使用 =====
    cout << endl << "【二、基本数据类型使用示例】" << endl;

    // int
    int age = 15;
    cout << "int age = " << age << endl;

    // long long
    long long bigNumber = 14000000000LL;
    cout << "long long = " << bigNumber << " (14亿)" << endl;

    // double（推荐用于浮点数）
    double score = 98.56;
    cout << "double score = " << score << endl;

    // 浮点数精度对比
    float f = 1.0 / 3.0;
    double d = 1.0 / 3.0;
    cout << fixed << setprecision(10);
    cout << "float  1/3 = " << f << " (精度较低)" << endl;
    cout << "double 1/3 = " << d << " (精度较高)" << endl;

    // char
    char grade = 'A';
    cout << "char grade = '" << grade << "' ASCII=" << (int)grade << endl;

    // bool
    bool passed = true;
    bool failed = false;
    cout << "bool passed = " << passed << " (true=1)" << endl;
    cout << "bool failed = " << failed << " (false=0)" << endl;

    // ===== 三、变量命名演示 =====
    cout << endl << "【三、变量命名演示】" << endl;

    int myVar = 100;           // 合法：字母开头
    int _value = 200;          // 合法：下划线开头
    int total_score = 300;     // 合法：下划线连接
    int maxValue = 400;        // 合法：驼峰命名
    int studentCount = 500;    // 合法：驼峰命名

    cout << "myVar = " << myVar << endl;
    cout << "_value = " << _value << endl;
    cout << "total_score = " << total_score << endl;
    cout << "maxValue = " << maxValue << endl;
    cout << "studentCount = " << studentCount << endl;

    // ===== 四、const 常量 =====
    cout << endl << "【四、const 常量使用】" << endl;

    const int MAXN = 1000000;
    const double PI = 3.1415926535;
    const int MOD = 1000000007;

    cout << "MAXN = " << MAXN << endl;
    cout << "PI = " << PI << endl;
    cout << "MOD = " << MOD << endl;
    cout << "圆的面积(r=5): " << PI * 5 * 5 << endl;

    // ===== 五、溢出演示 =====
    cout << endl << "【五、int 溢出演示】" << endl;

    int intMax = 2147483647;
    cout << "int 最大值: " << intMax << endl;
    cout << "int 最大值 + 1 (溢出!): " << intMax + 1 << endl;

    // 正确做法：使用 long long
    long long safe = 100000LL * 100000LL;
    cout << "100000 * 100000 (用long long): " << safe << endl;

    // ===== 六、整数除法注意事项 =====
    cout << endl << "【六、整数除法演示】" << endl;

    cout << "5 / 2 = " << (5 / 2) << " (整数除法，截断!)" << endl;
    cout << "5.0 / 2 = " << (5.0 / 2) << " (浮点除法)" << endl;
    cout << "(double)5 / 2 = " << ((double)5 / 2) << " (强制转换)" << endl;

    // ===== 七、变量值互换演示 =====
    cout << endl << "【七、变量值互换】" << endl;

    int x = 10, y = 20;
    cout << "交换前: x=" << x << ", y=" << y << endl;

    // 使用临时变量交换
    int temp = x;
    x = y;
    y = temp;
    cout << "交换后: x=" << x << ", y=" << y << endl;

    cout << endl << "========== 第3课演示结束 ==========" << endl;
    return 0;
}
