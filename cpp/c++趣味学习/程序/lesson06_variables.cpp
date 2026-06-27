/*
 * ==========================================
 *  第06课：听电脑说话——变量入门
 *  知识点：变量的概念、int类型、声明与赋值
 *  C++趣味学习系列
 * ==========================================
 *
 *  程序说明：
 *  变量是编程中最基础的概念之一。
 *  本程序演示变量的声明、赋值、修改和使用。
 *  通过生动的例子帮助理解变量的"储物柜"概念。
 */

#include <iostream>
#include <string>
using namespace std;

int main() {
    // =====================================
    // 示例1：变量的基本概念
    // =====================================
    cout << "========== 示例1：认识变量 ==========" << endl;
    cout << "变量 = 储物柜，有名字、能放东西、能换东西。" << endl;
    cout << endl;

    // 声明一个变量（准备一个柜子）
    int myAge;  // int 是类型（整数），myAge 是名字

    // 给变量赋值（把东西放进柜子）
    myAge = 10;
    cout << "我的年龄是：" << myAge << "岁" << endl;

    // 变量的值可以改变！
    myAge = 11;
    cout << "过了一年，我" << myAge << "岁了。" << endl;

    // 声明并初始化（一步到位）
    int birthYear = 2026 - myAge;  // 计算出生年份
    cout << "我出生于" << birthYear << "年。" << endl;
    cout << endl;

    // =====================================
    // 示例2：多个变量的使用
    // =====================================
    cout << "========== 示例2：多个变量 ==========" << endl;

    // 小明各科成绩
    int math = 95;
    int chinese = 88;
    int english = 92;
    int science = 90;

    // 用变量做计算
    int total = math + chinese + english + science;
    int average = total / 4;  // 整数除法，结果也是整数

    cout << "===== 成绩单 =====" << endl;
    cout << "数学：" << math << "分" << endl;
    cout << "语文：" << chinese << "分" << endl;
    cout << "英语：" << english << "分" << endl;
    cout << "科学：" << science << "分" << endl;
    cout << "------------------" << endl;
    cout << "总分：" << total << "分" << endl;
    cout << "平均分：" << average << "分" << endl;
    cout << endl;

    // =====================================
    // 示例3：变量的值可以改变
    // =====================================
    cout << "========== 示例3：变量值改变 ==========" << endl;

    int score = 80;
    cout << "初始成绩：" << score << "分" << endl;

    score = 90;  // 成绩提高了！
    cout << "第一次修改：" << score << "分" << endl;

    score = score + 5;  // 先算右边 score+5=95，再存回 score
    cout << "第二次修改（+5）：" << score << "分" << endl;

    score = score - 3;  // 扣了3分
    cout << "第三次修改（-3）：" << score << "分" << endl;
    cout << endl;

    // =====================================
    // 示例4：交换两个变量的值
    // =====================================
    cout << "========== 示例4：变量交换 ==========" << endl;
    cout << "如何交换两个杯子里的水？你需要第三个杯子！" << endl;

    int cupA = 10;
    int cupB = 20;
    cout << "交换前：cupA = " << cupA << ", cupB = " << cupB << endl;

    // 交换步骤：
    int temp = cupA;  // 第1步：把A倒进临时杯子
    cupA = cupB;      // 第2步：把B倒进A
    cupB = temp;      // 第3步：把临时杯子的水倒进B

    cout << "交换后：cupA = " << cupA << ", cupB = " << cupB << endl;
    cout << endl;

    // =====================================
    // 示例5：变量命名规则
    // =====================================
    cout << "========== 示例5：命名规则 ==========" << endl;
    cout << "变量命名规则：" << endl;
    cout << "  ✅ 只能使用字母、数字、下划线" << endl;
    cout << "  ✅ 第一个字符不能是数字" << endl;
    cout << "  ✅ 区分大小写（age 和 Age 不同）" << endl;
    cout << "  ✅ 不能使用C++关键字（int、return等）" << endl;
    cout << "  ✅ 见名知意（用有意义的英文或拼音）" << endl;
    cout << endl;

    // 好的命名示例
    int studentAge = 10;     // 驼峰式：学生年龄
    int total_score = 100;   // 下划线式：总分
    int nianLing = 10;       // 拼音：年龄

    cout << "好的变量名示例：" << endl;
    cout << "  studentAge = " << studentAge << endl;
    cout << "  total_score = " << total_score << endl;
    cout << "  nianLing = " << nianLing << endl;
    cout << endl;

    // =====================================
    // 示例6：变量自增自减（提前了解一下）
    // =====================================
    cout << "========== 示例6：自增自减 ==========" << endl;

    int counter = 0;
    cout << "初始值：" << counter << endl;

    counter = counter + 1;  // 增加1
    cout << "加1后：" << counter << endl;

    counter = counter + 1;  // 再增加1
    cout << "再加1后：" << counter << endl;

    counter = counter - 1;  // 减少1
    cout << "减1后：" << counter << endl;

    // 更简单的写法（以后会学）
    // counter++;  // 等同于 counter = counter + 1;
    // counter--;  // 等同于 counter = counter - 1;
    cout << endl;

    // =====================================
    // 练习1参考答案：找错误修正
    // =====================================
    cout << "========== 练习1答案：修正错误 ==========" << endl;
    int firstPlace = 100;    // 修正：变量名不能以数字开头
    int score2 = 0;          // 修正：先赋值再使用
    cout << "score的值是：" << score2 << endl;
    int returnValue = 5;     // 修正：不能用关键字做变量名
    cout << "三个变量都已正确声明！" << endl;
    cout << endl;

    // =====================================
    // 练习2参考答案：长方形计算
    // =====================================
    cout << "========== 练习2答案：长方形计算 ==========" << endl;
    int length = 10;
    int width = 5;
    int perimeter = 2 * (length + width);  // 周长
    int area = length * width;             // 面积
    cout << "长方形：长=" << length << "，宽=" << width << endl;
    cout << "周长 = 2 × (" << length << " + " << width << ") = " << perimeter << endl;
    cout << "面积 = " << length << " × " << width << " = " << area << endl;
    cout << endl;

    // =====================================
    // 练习3参考答案：倒计时
    // =====================================
    cout << "========== 练习3答案：倒计时 ==========" << endl;
    int count = 5;
    cout << "倒计时开始！" << endl;
    cout << count << "..." << endl;
    count = count - 1;
    cout << count << "..." << endl;
    count = count - 1;
    cout << count << "..." << endl;
    count = count - 1;
    cout << count << "..." << endl;
    count = count - 1;
    cout << count << "..." << endl;
    cout << "发射！🚀" << endl;
    cout << endl;

    // =====================================
    // 挑战任务参考答案：小小收银员
    // =====================================
    cout << "========== 挑战任务：小小收银员 ==========" << endl;
    int applePrice = 5;     // 苹果单价：5元/个
    int appleCount = 8;     // 买了8个苹果
    int moneyPaid = 100;    // 付了100元

    int totalPrice = applePrice * appleCount;
    int change = moneyPaid - totalPrice;

    cout << "========== 购物小票 ==========" << endl;
    cout << "商品：苹果" << endl;
    cout << "单价：" << applePrice << "元/个" << endl;
    cout << "数量：" << appleCount << "个" << endl;
    cout << "----------------------------" << endl;
    cout << "总价：" << totalPrice << "元" << endl;
    cout << "付款：" << moneyPaid << "元" << endl;
    cout << "找零：" << change << "元" << endl;
    cout << "==============================" << endl;
    cout << "谢谢惠顾！欢迎下次再来！" << endl;
    cout << endl;

    // =====================================
    // 程序结束
    // =====================================
    cout << "========== 程序结束 ==========" << endl;
    cout << "今天学习了变量，你的编程'工具箱'又丰富了！" << endl;

    return 0;
}

/*
 * ==========================================
 *  本课核心内容总结：
 *
 *  1. 变量 = 储物柜：有类型（int）、名字（age）、值（10）
 *  2. 声明：int score;  —— 告诉电脑"我要一个柜子"
 *  3. 赋值：score = 100; —— 把东西放进去
 *  4. 初始化：int score = 100; —— 一步完成
 *  5. 值可变：score = 95; —— 随时换新东西
 *  6. 命名规则：有意义、不数字开头、非关键字
 *
 *  口诀：
 *  变量就像储物柜，贴上标签放东西；
 *  int整数最常见，先声明后再使用！
 * ==========================================
 */
