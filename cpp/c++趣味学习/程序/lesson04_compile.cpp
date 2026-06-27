/*
 * ==========================================
 *  第04课：小小翻译官——C++程序的运行
 *  知识点：编译、运行、编译错误、调试思路
 *  C++趣味学习系列
 * ==========================================
 *
 *  程序说明：
 *  这个程序展示了常见的编译错误类型，
 *  以及如何通过阅读错误信息来修复代码。
 *  正确版本是可以编译运行的，错误版本用注释展示。
 */

#include <iostream>
#include <string>
using namespace std;

int main() {
    // =====================================
    // 示例1：正确的程序（能编译通过）
    // =====================================
    cout << "========== 示例1：正确的程序 ==========" << endl;
    cout << "这个程序没有Bug，编译和运行都很顺利！" << endl;
    cout << "编译器 → 目标文件 → 链接器 → 可执行程序 → 运行！" << endl;
    cout << endl;

    // =====================================
    // 示例2：常见错误类型展示
    //   注意：下面的错误代码已被注释掉，所以程序能正常运行
    //   如果想看编译报错，可以取消注释试试！
    // =====================================
    cout << "========== 示例2：常见错误类型 ==========" << endl;

    // 错误类型1：忘记分号
    // 取消下面的注释会导致编译错误：
    // cout << "这行少了分号" << endl     // ← 编译报错：expected ';'

    // 错误类型2：拼写错误
    // 取消下面的注释会导致编译错误：
    // cout << "cout拼错了" << end;     // ← 编译报错：'end' was not declared

    // 错误类型3：变量未定义
    // 取消下面的注释会导致编译错误：
    // cout << unknownVar;               // ← 编译报错：'unknownVar' was not declared

    // 错误类型4：字符串没加引号
    // 取消下面的注释会导致编译错误：
    // cout << 你好;                     // ← 编译报错：各种奇怪的错误

    // 错误类型5：缺少花括号（这个最隐蔽！）
    // 一般编译器会报：expected '}' at end of input

    cout << "常见的编译错误：" << endl;
    cout << "  1. 忘记分号 → expected ';'" << endl;
    cout << "  2. 拼写错误 → 'xxx' was not declared" << endl;
    cout << "  3. 变量未定义 → undeclared identifier" << endl;
    cout << "  4. 字符串忘加引号 → 各种奇怪的报错" << endl;
    cout << "  5. 缺少花括号 → expected '}'" << endl;
    cout << endl;

    // =====================================
    // 示例3：Bug侦探游戏 —— 展示如何找Bug
    // =====================================
    cout << "========== 示例3：Bug侦探游戏 ==========" << endl;
    cout << "现在你是Bug侦探！看看下面的错误代码：" << endl;
    cout << endl;
    cout << "  错误代码：" << endl;
    cout << "  cout << \"Bug侦探\" << endl     // 少分号" << endl;
    cout << "  int score = 100                  // 少分号" << endl;
    cout << "  cout << score << end;            // end应该是endl" << endl;
    cout << "  retrun 0;                        // retrun应该是return" << endl;
    cout << endl;
    cout << "  编译器会报以下错误：" << endl;
    cout << "  1. expected ';' before 'int'" << endl;
    cout << "  2. expected ';' before 'cout'" << endl;
    cout << "  3. 'end' was not declared" << endl;
    cout << "  4. 'retrun' was not declared" << endl;
    cout << endl;

    // =====================================
    // 示例4：找出下面代码的所有Bug（已修复版）
    // =====================================
    cout << "========== 示例4：修复后的代码 ==========" << endl;

    // 修正版本 —— 所有Bug都已修复
    cout << "Bug侦探游戏" << endl;          // ← 加了分号
    int bugsFound = 4;                      // ← 加了分号
    cout << "一共找到了" << bugsFound << "个bug" << endl;  // ← 加了分号
    cout << "你找到了几个？" << endl;        // ← end 改成 endl
    // return 的拼写也是正确的！

    cout << "恭喜！所有Bug都修复了！" << endl;
    cout << endl;

    // =====================================
    // 示例5：调试口诀
    // =====================================
    cout << "========== 示例5：调试口诀 ==========" << endl;
    cout << "写代码 → 编译 → 出错 → 读错误信息" << endl;
    cout << "  ↓" << endl;
    cout << "找到错误行 → 分析原因 → 修改代码" << endl;
    cout << "  ↓" << endl;
    cout << "重新编译 → 成功！→ 运行看结果！" << endl;
    cout << endl;

    // =====================================
    // 练习1参考答案：找出4个Bug
    // =====================================
    cout << "========== 练习1答案：Bug侦探 ==========" << endl;
    string answer[] = {
        "Bug1: 第1个cout语句末尾缺分号",
        "Bug2: 第2个cout语句末尾缺分号",
        "Bug3: 'end' 应该是 'endl'",
        "Bug4: 'retrun' 应该是 'return'"
    };
    for (int i = 0; i < 4; i++) {
        cout << "  " << answer[i] << endl;
    }
    cout << endl;

    // =====================================
    // 挑战任务参考答案：Bug收集册
    // =====================================
    cout << "========== 挑战任务：Bug收集册 ==========" << endl;
    cout << endl;

    // Bug1：缺少分号 → 编译报错：expected ';'
    cout << "Bug1示例（已修正）：";
    int number = 42;  // 有分号，正确！
    cout << "  number = " << number << endl;

    // Bug2：拼写错误 → 编译报错：'xxx' was not declared
    cout << "Bug2示例（已修正）：";
    cout << "  cout没有拼错！" << endl;  // cout拼写正确

    // Bug3：变量未定义就使用
    cout << "Bug3示例（已修正）：";
    string fruit = "苹果";  // 先定义
    cout << "  我喜欢吃" << fruit << endl;  // 再使用

    // Bug4：字符串忘记加引号
    cout << "Bug4示例（已修正）：";
    cout << "  字符串记得加引号哦！" << endl;  // 引号包裹

    // Bug5：缺少花括号（已在main函数中检查完毕）
    cout << "Bug5示例：花括号成对出现，没有缺少！" << endl;

    cout << endl;
    cout << "========== Bug收集册完成 ==========" << endl;
    cout << "恭喜！你已经掌握了找Bug的基本技能！" << endl;

    return 0;  // return拼写正确，有分号
}

/*
 * ==========================================
 *  Bug侦探速查表：
 *
 *  | 症状 | 编译报错 | 解决方案 |
 *  |------|----------|----------|
 *  | 忘分号 | expected ';' | 在语句末尾加 ; |
 *  | 拼写错 | 'xxx' was not declared | 检查拼写 |
 *  | 忘定义 | undeclared identifier | 先定义再使用 |
 *  | 缺引号 | 各种奇怪报错 | 字符串要加 "" |
 *  | 少花括号 | expected '}' | 检查 { } 是否配对 |
 *  | 忘头文件 | cout was not declared | 加 #include <iostream> |
 *
 *  口诀：
 *  写代码、存文件、编译器来翻译；
 *  找Bug、读信息、小小侦探真仔细！
 * ==========================================
 */
