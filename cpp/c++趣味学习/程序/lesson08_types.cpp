/*
 * ==========================================
 *  第08课：数字的多样性——变量类型
 *  知识点：int、double、char、bool、string、sizeof
 *  C++趣味学习系列
 * ==========================================
 *
 *  程序说明：
 *  欢迎来到"数据类型大观园"！
 *  本程序全面展示C++的常用数据类型，
 *  让你学会根据需求选择合适的类型。
 *  每种类型都有自己的特点和用途，
 *  就像工具箱里不同形状的螺丝刀。
 */

#include <iostream>
#include <string>
using namespace std;

int main() {
    // =====================================
    // 示例1：全部数据类型展示
    // =====================================
    cout << "========== 示例1：数据类型大观园 ==========" << endl;
    cout << "C++有多种数据类型，各有各的用途。" << endl;
    cout << endl;

    // int —— 整数
    int myAge = 10;
    int myScore = 98;
    int currentYear = 2026;
    int negativeNumber = -5;

    cout << "【int —— 整数型】" << endl;
    cout << "  年龄：" << myAge << "岁" << endl;
    cout << "  分数：" << myScore << "分" << endl;
    cout << "  年份：" << currentYear << "年" << endl;
    cout << "  负数：" << negativeNumber << endl;
    cout << "  范围：约-21亿 ~ 21亿" << endl;
    cout << endl;

    // double —— 小数（浮点数）
    double pi = 3.14159;
    double height = 1.45;
    double price = 12.50;
    double average = 95.5;

    cout << "【double —— 小数型（浮点数）】" << endl;
    cout << "  圆周率：" << pi << endl;
    cout << "  身高：" << height << "米" << endl;
    cout << "  价格：" << price << "元" << endl;
    cout << "  平均分：" << average << "分" << endl;
    cout << "  精度：约15-17位有效数字" << endl;
    cout << endl;

    // char —— 单个字符
    char grade = 'A';
    char firstLetter = 'X';
    char digit = '7';      // 注意：这是字符'7'，不是数字7
    char symbol = '+';
    char space = ' ';

    cout << "【char —— 字符型】" << endl;
    cout << "  等级：" << grade << endl;
    cout << "  首字母：" << firstLetter << endl;
    cout << "  数字字符：" << digit << "（是字符，不是数字）" << endl;
    cout << "  符号：" << symbol << endl;
    cout << "  注意：char用单引号 ' ' 包裹" << endl;
    cout << endl;

    // bool —— 真假值
    bool isRaining = false;
    bool isPassed = true;
    bool hasHomework = true;
    bool isWeekend = false;

    cout << "【bool —— 布尔型（真假型）】" << endl;
    cout << "  今天下雨吗？" << isRaining << "（0=false, 1=true）" << endl;
    cout << "  考试通过了吗？" << isPassed << endl;
    cout << "  有作业吗？" << hasHomework << endl;
    cout << "  是周末吗？" << isWeekend << endl;
    cout << "  bool只有两个值：true 或 false" << endl;
    cout << endl;

    // string —— 字符串
    string myName = "小明";
    string school = "阳光小学";
    string greeting = "Hello, World!";
    string emptyStr = "";

    cout << "【string —— 字符串型】" << endl;
    cout << "  姓名：" << myName << endl;
    cout << "  学校：" << school << endl;
    cout << "  问候语：" << greeting << endl;
    cout << "  空字符串：" << emptyStr << "（什么都没有）" << endl;
    cout << "  注意：string用双引号包裹，需要 #include <string>" << endl;
    cout << endl;

    // =====================================
    // 示例2：sizeof —— 测量数据类型大小
    // =====================================
    cout << "========== 示例2：sizeof 测量大小 ==========" << endl;
    cout << "每种数据类型在内存中占用不同的空间：" << endl;
    cout << endl;

    cout << "  数据类型      |  占用内存" << endl;
    cout << "  --------------|----------" << endl;
    cout << "  int           |  " << sizeof(int) << " 字节" << endl;
    cout << "  double        |  " << sizeof(double) << " 字节" << endl;
    cout << "  char          |  " << sizeof(char) << " 字节" << endl;
    cout << "  bool          |  " << sizeof(bool) << " 字节" << endl;
    cout << "  string(固定)  |  " << sizeof(string) << " 字节" << endl;
    cout << endl;

    // sizeof 也可以测量变量
    int testInt = 100;
    double testDouble = 3.14;
    char testChar = 'Z';

    cout << "  变量 testInt (int) 占用：" << sizeof(testInt) << " 字节" << endl;
    cout << "  变量 testDouble (double) 占用：" << sizeof(testDouble) << " 字节" << endl;
    cout << "  变量 testChar (char) 占用：" << sizeof(testChar) << " 字节" << endl;
    cout << endl;

    cout << "  知识卡片：1字节 = 8比特（bit）" << endl;
    cout << "  1字节能表示256种不同的值（0~255）" << endl;
    cout << endl;

    // =====================================
    // 示例3：类型转换与运算
    // =====================================
    cout << "========== 示例3：类型转换与运算 ==========" << endl;

    int a = 10;
    int b = 3;
    double c = 3.0;

    cout << "整数除法 vs 小数除法：" << endl;
    cout << "  " << a << " / " << b << " = " << a / b
         << "  （整数除法，结果也是整数，小数被丢弃）" << endl;
    cout << "  " << a << " / " << c << " = " << a / c
         << "  （有double参与，结果是小数）" << endl;
    cout << "  " << a << " / 2.0 = " << a / 2.0
         << "  （2.0是double，所以结果是小数）" << endl;
    cout << endl;

    // 显式类型转换
    double piValue = 3.14159;
    int piInt = (int)piValue;  // 强制转为int，丢弃小数部分
    cout << "显式转换：(int)" << piValue << " = " << piInt
         << "  （小数部分被丢弃了）" << endl;

    double dValue = 3.99;
    int iValue = (int)dValue;
    cout << "  (int)" << dValue << " = " << iValue
         << "  （不是四舍五入，是直接丢弃！）" << endl;
    cout << endl;

    // =====================================
    // 示例4：int 和 double 的混合运算
    // =====================================
    cout << "========== 示例4：混合运算 ==========" << endl;

    int students = 30;          // 学生数量（整数）
    double totalScore = 2805.0; // 总分（带小数）
    double avgScore = totalScore / students;  // 平均分

    cout << "班级人数（int）：" << students << "人" << endl;
    cout << "总分（double）：" << totalScore << "分" << endl;
    cout << "平均分（int/double混合）：" << avgScore << "分" << endl;
    cout << "  （int和double一起运算，结果自动变成double）" << endl;
    cout << endl;

    // =====================================
    // 示例5：学生信息卡（综合运用）
    // =====================================
    cout << "========== 示例5：学生信息卡 ==========" << endl;

    // 用不同数据类型存储完整的学生信息
    string studentName = "小明";        // 姓名 → string
    int studentAge = 10;               // 年龄 → int
    double studentHeight = 1.45;       // 身高 → double
    char bloodType = 'O';              // 血型 → char
    bool isMonitor = true;             // 是否班长 → bool
    int mathScore = 98;                // 数学成绩 → int
    double avgTotalScore = 93.5;       // 平均成绩 → double

    cout << "========== 学生信息卡 ==========" << endl;
    cout << "  姓名（string）：" << studentName << endl;
    cout << "  年龄（int）：" << studentAge << "岁" << endl;
    cout << "  身高（double）：" << studentHeight << "米" << endl;
    cout << "  血型（char）：" << bloodType << "型" << endl;
    cout << "  班长（bool）：" << (isMonitor ? "是" : "否") << endl;
    cout << "  数学成绩（int）：" << mathScore << "分" << endl;
    cout << "  平均成绩（double）：" << avgTotalScore << "分" << endl;
    cout << endl;

    // =====================================
    // 练习2参考答案：sizeof实验
    // =====================================
    cout << "========== 练习2答案：sizeof实验 ==========" << endl;

    int varInt = 10;
    double varDouble = 3.14;
    char varChar = 'X';
    bool varBool = true;
    string varString = "hello";

    cout << "变量名       类型        值         大小" << endl;
    cout << "-----------  ----------  ---------  -----" << endl;
    cout << "varInt       int         " << varInt << "         "
         << sizeof(varInt) << "字节" << endl;
    cout << "varDouble    double      " << varDouble << "      "
         << sizeof(varDouble) << "字节" << endl;
    cout << "varChar      char        " << varChar << "          "
         << sizeof(varChar) << "字节" << endl;
    cout << "varBool      bool        " << varBool << "       "
         << sizeof(varBool) << "字节" << endl;
    cout << "varString    string      " << varString << "     "
         << sizeof(varString) << "字节(固定)" << endl;
    cout << endl;

    // =====================================
    // 挑战任务：我的数据名片
    // =====================================
    cout << "========== 挑战任务：我的数据名片 ==========" << endl;

    string cardName = "小明";
    int cardAge = 10;
    double cardHeight = 1.45;
    char cardFavLetter = 'C';
    bool cardLoveCoding = true;

    cout << "🌟 ================================ 🌟" << endl;
    cout << "           我的数据名片" << endl;
    cout << "🌟 ================================ 🌟" << endl;
    cout << endl;

    cout << "📛 姓名（string）：" << cardName;
    cout << " | 占用 " << sizeof(cardName) << " 字节（固定部分）" << endl;

    cout << "🎂 年龄（int）：" << cardAge << "岁";
    cout << " | 占用 " << sizeof(cardAge) << " 字节" << endl;

    cout << "📏 身高（double）：" << cardHeight << "米";
    cout << " | 占用 " << sizeof(cardHeight) << " 字节" << endl;

    cout << "🔤 最喜欢字母（char）：" << cardFavLetter;
    cout << " | 占用 " << sizeof(cardFavLetter) << " 字节" << endl;

    cout << "💻 喜欢编程（bool）：" << (cardLoveCoding ? "是" : "否");
    cout << " | 占用 " << sizeof(cardLoveCoding) << " 字节" << endl;

    cout << endl;
    cout << "🌟 ================================ 🌟" << endl;
    // 计算总计占用（这只是大概估计）
    int totalSize = sizeof(cardName) + sizeof(cardAge) + sizeof(cardHeight)
                    + sizeof(cardFavLetter) + sizeof(cardLoveCoding);
    cout << "  变量总计占用（固定部分）：" << totalSize << " 字节" << endl;
    cout << "🌟 ================================ 🌟" << endl;
    cout << endl;

    // =====================================
    // 程序结束
    // =====================================
    cout << "========== 程序结束 ==========" << endl;
    cout << "今天参观了'数据类型大观园'，你认识了多少种类型？" << endl;
    cout << "记住：int数数，double小数，char字母，bool真假，string句子！" << endl;

    return 0;
}

/*
 * ==========================================
 *  数据类型速查表：
 *
 *  ┌─────────┬──────────┬────────────┬──────────────┐
 *  │  类型   │  关键字  │   存储内容  │   内存占用   │
 *  ├─────────┼──────────┼────────────┼──────────────┤
 *  │  整数   │   int    │   整数     │    4字节     │
 *  │  小数   │  double  │   浮点数   │    8字节     │
 *  │  字符   │   char   │  单个字符  │    1字节     │
 *  │  真假   │   bool   │ true/false │    1字节     │
 *  │  字符串 │  string  │  文字串    │    可变      │
 *  └─────────┴──────────┴────────────┴──────────────┘
 *
 *  选择类型的口诀：
 *    数数用 int，小数用 double，
 *    字母用 char，真假用 bool，
 *    句子用 string，选对类型省空间！
 *
 *  sizeof 口诀：
 *    int 4, double 8, char 1, bool 1
 *    量量看，记住了！
 * ==========================================
 */
