/*
 * 第38课：邮递员送信——参数与返回值
 * 主题：📬 数据快递站
 *
 * 知识点：
 *   1. 函数的形参（形式参数）与实参（实际参数）
 *   2. return 语句——把计算结果"寄回"给调用方
 *   3. void 函数——"只干活不退货"
 *   4. 传递多个参数——数量、类型、顺序要一一对应
 *
 * 课程项目：
 * - 示例1：快递计费计算器（有参数有返回值的函数）
 * - 示例2：电子面单打印机（void 函数，只干活不退货）
 * - 示例3：快递分拣系统（多参数函数，"快递站"综合应用）
 * - 示例4：练习答案展示
 *
 * 编译方法：
 *   g++ -std=c++11 lesson38_parameters_return.cpp -o lesson38_parameters_return
 *   运行：./lesson38_parameters_return
 */

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// ============================================================
// 示例1：快递计费计算器 —— 有参数、有返回值的函数
// 说明：这是一个"有来有回"的函数，收到数据，返回计算结果
// 形参 weight, distance, isUrgent 就像快递单上的空白栏
// 调用时传入的实参就像填写了具体的内容
// ============================================================
double calculateFee(double weight, int distance, bool isUrgent) {
    // 形参说明：
    //   weight   —— 形参，代表包裹重量（调用时由实参赋值）
    //   distance —— 形参，代表运送距离
    //   isUrgent —— 形参，代表是否加急

    double fee = 0.0;

    // 基础费用：每千克 2 元
    fee = weight * 2.0;

    // 远距离附加费：超过1000公里加收10元
    if (distance > 1000) {
        fee += 10.0;
        cout << "     [系统提示] 检测到远距离运输，附加10元长途费" << endl;
    }

    // 加急服务费：加急加收15元
    if (isUrgent) {
        fee += 15.0;
        cout << "     [系统提示] 检测到加急服务，附加15元加急费" << endl;
    }

    // 限时优惠：如果总费用超过30元，打9折
    if (fee > 30.0) {
        cout << "     [系统提示] 大额订单享9折优惠！" << endl;
        fee = fee * 0.9;
    }

    return fee;  // return：把计算结果"寄回"给调用方
}


// ============================================================
// 示例2：电子面单打印机 —— void 函数（只干活，不退货）
// 说明：void 表示"我不返回任何值"，只管执行任务
//       就像邮递员把通知贴到公告栏就走，不需要带回签收单
// ============================================================
void printReceipt(string sender, string receiver,
                  double weight, int distance, bool isUrgent) {
    // void 函数的特点：
    // 1. 函数名前写 void
    // 2. 没有 return 语句（执行完就自动结束）
    // 3. 调用方不能用变量接收它的"返回值"（因为它没有返回值）

    // 在 void 函数内部，我们可以调用其他函数来帮忙
    double fee = calculateFee(weight, distance, isUrgent);

    cout << endl;
    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║       📬 数据快递站 · 电子面单           ║" << endl;
    cout << "╠══════════════════════════════════════════╣" << endl;
    cout << "║  快递单号：KD2024" << (1000 + (int)weight * 100 + distance % 100) << "            ║" << endl;
    cout << "╠══════════════════════════════════════════╣" << endl;

    // 发件人
    cout << "║  发件人：";
    cout << sender;
    int padLen = 26 - (int)sender.length() * 2;
    if (padLen < 0) padLen = 0;
    for (int i = 0; i < padLen; i++) cout << " ";
    cout << "║" << endl;

    // 收件人
    cout << "║  收件人：";
    cout << receiver;
    padLen = 26 - (int)receiver.length() * 2;
    if (padLen < 0) padLen = 0;
    for (int i = 0; i < padLen; i++) cout << " ";
    cout << "║" << endl;

    // 重量
    cout << "║  重量：  " << weight << " kg";
    padLen = 20;
    for (int i = 0; i < padLen; i++) cout << " ";
    cout << "║" << endl;

    // 距离
    cout << "║  距离：  " << distance << " 公里";
    padLen = 18;
    for (int i = 0; i < padLen; i++) cout << " ";
    cout << "║" << endl;

    // 服务类型
    cout << "║  服务：  ";
    cout << (isUrgent ? "加急快递" : "普通快递");
    padLen = 20;
    for (int i = 0; i < padLen; i++) cout << " ";
    cout << "║" << endl;

    cout << "╠══════════════════════════════════════════╣" << endl;

    // 费用
    cout << "║  费用合计：￥";
    cout << fixed << setprecision(2) << fee;
    padLen = 22;
    for (int i = 0; i < padLen; i++) cout << " ";
    cout << "║" << endl;

    cout << "╚══════════════════════════════════════════╝" << endl;
    cout << endl;

    // void 函数不需要 return —— 执行到这里就自动结束了
}


// ============================================================
// 示例3：快递分拣系统 —— 多参数函数综合应用
// 说明：这个系统模拟了一个快递站的分拣流程
//       发件人把包裹交给快递站 → 快递站分拣配送 → 收件人签收
// ============================================================

// 3.1 分拣判断：根据目的地决定投递方式
string determineDeliveryMethod(string destination, double weight) {
    if (weight > 20.0) {
        return "🚛 货车配送（超重包裹，20kg以上）";
    }
    if (destination == "本地" || destination == "同城") {
        return "🛵 电动车配送（本地件）";
    }
    if (destination == "省内") {
        return "🚚 卡车配送（省内件）";
    }
    return "✈️ 航空配送（跨省/国际件）";
}

// 3.2 预计送达时间计算
int calculateDeliveryDays(string destination, bool isUrgent) {
    if (isUrgent) {
        return 1;  // 加急次日达
    }
    if (destination == "本地" || destination == "同城") {
        return 1;  // 同城次日达
    }
    if (destination == "省内") {
        return 2;  // 省内2天
    }
    if (destination == "跨省") {
        return 4;  // 跨省4天
    }
    return 7;  // 国际件7天
}

// 3.3 快递分拣主函数 —— 综合所有信息
void processPackage(string sender, string receiver,
                    string destination, double weight, bool isUrgent) {
    // 这个函数展示了如何在函数内部调用其他函数
    // 就像快递站的各个岗位互相协作

    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║     📦 快递分拣系统 · 包裹处理中...     ║" << endl;
    cout << "╚══════════════════════════════════════════╝" << endl;
    cout << endl;

    // 步骤1：打印基本信息
    cout << "📋 包裹信息确认：" << endl;
    cout << "   发件人：" << sender << "    收件人：" << receiver << endl;
    cout << "   目的地：" << destination << "    重量：" << weight << " kg" << endl;
    cout << "   模式：" << (isUrgent ? "加急" : "普通") << endl;
    cout << endl;

    // 步骤2：确定投递方式（调用 determineDeliveryMethod）
    cout << "🔍 正在匹配最佳配送路线..." << endl;
    string method = determineDeliveryMethod(destination, weight);
    cout << "   → " << method << endl;
    cout << endl;

    // 步骤3：计算费用（调用 calculateFee）
    int distance = 0;
    if (destination == "本地" || destination == "同城") distance = 30;
    else if (destination == "省内") distance = 300;
    else if (destination == "跨省") distance = 1500;
    else distance = 5000;

    double fee = calculateFee(weight, distance, isUrgent);
    // 注意：calculateFee 内部的 cout 会在此处输出提示信息
    cout << "   → 快递费用：￥" << fixed << setprecision(2) << fee << endl;
    cout << endl;

    // 步骤4：预计送达时间（调用 calculateDeliveryDays）
    int days = calculateDeliveryDays(destination, isUrgent);
    cout << "📅 预计送达时间：" << days << " 天" << endl;
    cout << endl;

    // 步骤5：模拟发货过程
    cout << "📬 包裹状态更新：" << endl;
    cout << "   [✓] 已揽收 —— 快递员已取件" << endl;
    cout << "   [✓] 已分拣 —— " << method << endl;
    cout << "   [→] 运输中 —— 预计 " << days << " 天后送达" << endl;
    cout << endl;
    cout << "   感谢使用数据快递站！您的包裹正在路上~ 🚀" << endl;
    cout << endl;
}


// ============================================================
// 练习答案
// ============================================================

// 练习1答案：圆面积计算器
void ejercicio1_respuesta() {
    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║       练习1答案：圆面积计算器           ║" << endl;
    cout << "╚══════════════════════════════════════════╝" << endl;
    cout << endl;

    // 正确的函数定义
    cout << "补全后的代码：" << endl;
    cout << "┌──────────────────────────────────────────┐" << endl;
    cout << "│ double circleArea(double r) {            │" << endl;
    cout << "│     const double PI = 3.14159;           │" << endl;
    cout << "│     return PI * r * r;                   │" << endl;
    cout << "│ }                                        │" << endl;
    cout << "└──────────────────────────────────────────┘" << endl;
    cout << endl;

    // 实际运行演示
    double testRadii[] = {1.0, 2.0, 3.5};
    cout << "运行演示：" << endl;
    for (int i = 0; i < 3; i++) {
        double r = testRadii[i];
        const double PI = 3.14159;
        double area = PI * r * r;
        cout << "   半径 r = " << r << " → 面积 = " << area << endl;
    }
    cout << endl;
}

// 练习2答案：判断正误
void ejercicio2_respuesta() {
    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║        练习2答案：判断正误              ║" << endl;
    cout << "╚══════════════════════════════════════════╝" << endl;
    cout << endl;

    cout << "1. '形参可以不给名字' → ❌ 错误" << endl;
    cout << "   函数定义中的形参必须有名字，因为函数体需要通过" << endl;
    cout << "   形参名来使用传入的值。" << endl;
    cout << endl;

    cout << "2. 'void 函数中可以写 return 0' → ❌ 错误" << endl;
    cout << "   void 函数表示不返回任何值，如果要提前退出，" << endl;
    cout << "   只能写 return; （不带值），不能写 return 0;" << endl;
    cout << endl;

    cout << "3. '实参和形参的名字必须相同' → ❌ 错误" << endl;
    cout << "   形参和实参的名字可以完全不同。关键是位置对应，" << endl;
    cout << "   不是名字对应。例：int add(int x, int y) 可以" << endl;
    cout << "   用 add(a, b) 调用，其中 a 和 b 是实参。" << endl;
    cout << endl;

    cout << "4. '2个int形参必须传2个int实参' → ✅ 正确" << endl;
    cout << "   调用函数时，实参的数量和类型必须与形参一一对应。" << endl;
    cout << "   int calculate(int x, int y) 需要正好2个 int 实参。" << endl;
    cout << endl;
}

// 练习3答案：代码改错
void ejercicio3_respuesta() {
    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║        练习3答案：代码改错              ║" << endl;
    cout << "╚══════════════════════════════════════════╝" << endl;
    cout << endl;

    cout << "错误①: int multiply(int x, y)" << endl;
    cout << "   每个形参都必须有自己的类型。改为：" << endl;
    cout << "   int multiply(int x, int y)" << endl;
    cout << endl;

    cout << "错误②: void 函数中 return answer;" << endl;
    cout << "   void 函数不能返回任何值。删掉这行即可。" << endl;
    cout << endl;

    cout << "错误③: multiply(a) 只传了1个实参" << endl;
    cout << "   multiply 需要2个 int 实参。改为：multiply(a, b)" << endl;
    cout << endl;

    cout << "错误④: int d = printResult(c)" << endl;
    cout << "   不能把 void 函数的调用赋给变量。改为：printResult(c);" << endl;
    cout << endl;

    // 运行修正后的代码
    cout << "修正后运行演示：" << endl;
    int a = 7, b = 8;
    int c = a * b;  // 模拟 multiply 的结果
    cout << "   multiply(7, 8) = " << c << endl;
    cout << "   printResult -> 结果是：" << c << endl;
    cout << endl;
}


// ============================================================
// 挑战任务：快递费用计算系统（完整版）
// ============================================================
void desafio_expressSystem() {
    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║   挑战任务：快递费用计算系统            ║" << endl;
    cout << "╚══════════════════════════════════════════╝" << endl;
    cout << endl;

    cout << "🚚 === 数据快递站 · 今日订单处理 === 🚚" << endl;
    cout << endl;

    // 订单1：小明寄给小红 —— 普通本地件
    cout << "订单 #1：同城普通件" << endl;
    cout << "──────────────────────────────────────────" << endl;
    processPackage("小明", "小红", "本地", 2.5, false);

    // 分隔线
    cout << "═══════════════════════════════════════════" << endl;
    cout << endl;

    // 订单2：北京寄上海 —— 加急跨省件
    cout << "订单 #2：跨省加急件" << endl;
    cout << "──────────────────────────────────────────" << endl;
    processPackage("北京分公司", "上海分公司", "跨省", 12.0, true);

    // 分隔线
    cout << "═══════════════════════════════════════════" << endl;
    cout << endl;

    // 订单3：妈妈寄给奶奶 —— 省内重件
    cout << "订单 #3：省内普通重件" << endl;
    cout << "──────────────────────────────────────────" << endl;
    processPackage("妈妈", "奶奶", "省内", 25.0, false);

    cout << "📊 今日包裹统计：" << endl;
    cout << "   共处理 3 个包裹，所有订单已完成分拣。" << endl;
    cout << "   感谢使用数据快递站，明天见！" << endl;
    cout << endl;
}


// ============================================================
// 交互式演示：让用户自己试用快递系统
// ============================================================
void interactiveDemo() {
    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║   📬 数据快递站 · 交互式体验            ║" << endl;
    cout << "║   来当一次快递站管理员吧！              ║" << endl;
    cout << "╚══════════════════════════════════════════╝" << endl;
    cout << endl;

    string sender, receiver, destination;
    double weight;
    char urgentChoice;
    bool isUrgent;

    cout << "请输入发件人姓名：";
    getline(cin, sender);

    cout << "请输入收件人姓名：";
    getline(cin, receiver);

    cout << "请输入目的地（本地/省内/跨省/国际）：";
    getline(cin, destination);

    cout << "请输入包裹重量（kg）：";
    cin >> weight;

    cout << "是否加急？(y/n)：";
    cin >> urgentChoice;
    cin.ignore();  // 清除缓冲区

    isUrgent = (urgentChoice == 'y' || urgentChoice == 'Y');

    cout << endl;
    processPackage(sender, receiver, destination, weight, isUrgent);
}


// ============================================================
// 主函数：程序入口
// ============================================================
int main() {
    cout << endl;
    cout << "╔══════════════════════════════════════════════════════╗" << endl;
    cout << "║     第38课：邮递员送信——参数与返回值               ║" << endl;
    cout << "║     📬 数据快递站 —— C++ 趣味学习                  ║" << endl;
    cout << "╚══════════════════════════════════════════════════════╝" << endl;
    cout << endl;

    int opcion;

    do {
        cout << "┌────────────────────────────────────────────────┐" << endl;
        cout << "│           📬 数据快递站 · 功能菜单             │" << endl;
        cout << "├────────────────────────────────────────────────┤" << endl;
        cout << "│  1. 示例1：快递计费计算器（参数+返回值）      │" << endl;
        cout << "│  2. 示例2：电子面单打印机（void函数）         │" << endl;
        cout << "│  3. 示例3：快递分拣系统（多参数综合）         │" << endl;
        cout << "│  4. 练习1答案：圆面积计算器                   │" << endl;
        cout << "│  5. 练习2答案：判断正误                       │" << endl;
        cout << "│  6. 练习3答案：代码改错                       │" << endl;
        cout << "│  7. 挑战任务：快递费用计算系统（完整版）      │" << endl;
        cout << "│  8. 交互式体验：自己当快递站管理员            │" << endl;
        cout << "│  0. 退出程序                                  │" << endl;
        cout << "└────────────────────────────────────────────────┘" << endl;
        cout << "请输入数字选择：";
        cin >> opcion;
        cin.ignore();  // 清除缓冲区中的换行符
        cout << endl;

        switch (opcion) {
            case 1: {
                // 示例1：演示 calculateFee 函数
                cout << "╔══════════════════════════════════════════╗" << endl;
                cout << "║  示例1：快递计费计算器                   ║" << endl;
                cout << "║  （有参数、有返回值的函数）              ║" << endl;
                cout << "╚══════════════════════════════════════════╝" << endl;
                cout << endl;

                cout << "演示1：普通包裹 2.5kg，500公里，非加急" << endl;
                double fee1 = calculateFee(2.5, 500, false);
                cout << "   → 最终费用：￥" << fee1 << endl;
                cout << endl;

                cout << "演示2：加急包裹 8.0kg，1500公里，加急" << endl;
                double fee2 = calculateFee(8.0, 1500, true);
                cout << "   → 最终费用：￥" << fee2 << endl;
                cout << endl;

                cout << "【知识点小结】" << endl;
                cout << "  calculateFee 有3个形参：(double weight, int distance, bool isUrgent)" << endl;
                cout << "  调用时传入3个实参，类型必须匹配，顺序必须正确！" << endl;
                cout << "  函数通过 return 把计算结果'寄回'给调用方。" << endl;
                cout << endl;
                break;
            }

            case 2: {
                // 示例2：演示 void 函数
                cout << "╔══════════════════════════════════════════╗" << endl;
                cout << "║  示例2：电子面单打印机                   ║" << endl;
                cout << "║  （void 函数 —— 只干活，不退货）          ║" << endl;
                cout << "╚══════════════════════════════════════════╝" << endl;

                // void 函数直接调用，不需要赋值
                printReceipt("小红", "小刚的奶奶", 1.2, 200, false);
                printReceipt("小明", "小华的爸爸", 15.0, 2000, true);

                cout << "【知识点小结】" << endl;
                cout << "  printReceipt 是 void 函数，它只是'干活'（打印面单），" << endl;
                cout << "  不返回任何值。不能写成 int x = printReceipt(...);" << endl;
                cout << "  void 函数内部还可以调用其他函数（如 calculateFee）。" << endl;
                cout << endl;
                break;
            }

            case 3: {
                // 示例3：演示多参数函数
                cout << "╔══════════════════════════════════════════╗" << endl;
                cout << "║  示例3：快递分拣系统                     ║" << endl;
                cout << "║  （多参数函数综合应用）                  ║" << endl;
                cout << "╚══════════════════════════════════════════╝" << endl;
                cout << endl;

                processPackage("小明", "小红", "本地", 1.5, false);
                cout << "──────────────────────────────────────────" << endl;
                processPackage("快递站", "上海分公司", "跨省", 8.0, true);

                cout << "【知识点小结】" << endl;
                cout << "  processPackage 接收5个参数，展示多参数函数的用法。" << endl;
                cout << "  函数内部调用其他函数（determineDeliveryMethod、calculateFee等），" << endl;
                cout << "  体现了函数之间的互相协作——模块化编程的核心思想。" << endl;
                cout << endl;
                break;
            }

            case 4:
                ejercicio1_respuesta();
                break;

            case 5:
                ejercicio2_respuesta();
                break;

            case 6:
                ejercicio3_respuesta();
                break;

            case 7:
                desafio_expressSystem();
                break;

            case 8:
                interactiveDemo();
                break;

            case 0:
                cout << "📬 感谢使用数据快递站！" << endl;
                cout << "   记住：形参是占位符，实参是真数据；" << endl;
                cout << "        return 带回来，void 不退货！" << endl;
                cout << "   再见！" << endl;
                cout << endl;
                break;

            default:
                cout << "无效选择，请输入 0-8 之间的数字！" << endl;
                cout << endl;
        }
    } while (opcion != 0);

    return 0;
}
