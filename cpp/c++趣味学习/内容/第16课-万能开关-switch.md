# 第16课：万能开关——switch语句

## 🎯 学习目标
- 掌握switch-case语句的语法结构
- 理解break语句在switch中的关键作用
- 知道什么时候该用switch，什么时候该用if-else

## 📖 知识讲解

### 欢迎来到万能开关世界！

同学们，上一课我们学了if-else if-else多分支结构，它像一个**多岔路口**。今天我们要认识一位更酷的新朋友——**switch语句**，它就像一个**万能开关**！

想象一下你家里的电视遥控器：按"1"键跳到CCTV1，按"2"键跳到CCTV2，按"3"键跳到CCTV3……每个按键对应一个固定的频道。switch语句的工作原理和遥控器简直一模一样！

### switch为什么叫"开关"？

switch的英文意思是"开关"或"切换"。你可以把它想象成一个**多档位旋转开关**：

```
        ┌─────────────┐
        │  开关旋钮    │
        │  switch(变量)│
        └──────┬──────┘
               │
    ┌──────────┼──────────┐
    │          │          │
    ▼          ▼          ▼
┌───────┐ ┌───────┐ ┌───────┐
│ case 1│ │ case 2│ │ case 3│  ...
│ 频道1 │ │ 频道2 │ │ 频道3 │
└───────┘ └───────┘ └───────┘
```

当你把旋钮转到某个档位，对应的电路就接通了，该做的事就开始执行。

### switch-case 的语法结构

```cpp
switch (变量或表达式) {
    case 值1:
        // 当变量 == 值1 时执行
        break;      // ← 跳出开关！
    case 值2:
        // 当变量 == 值2 时执行
        break;
    case 值3:
        // 当变量 == 值3 时执行
        break;
    default:
        // 所有case都不匹配时执行
        break;
}
```

**几个重要的语法规则（一定要记住！）：**

1. **switch后面跟的是圆括号 `()`**，里面放要判断的变量
2. **case后面跟的是冒号 `:`**，不是分号！（这是超容易犯错的地方）
3. **每个case的值必须是整数或字符**（int、char），不能是小数或字符串
4. **case的值不能重复**——不能有两个 `case 1:`
5. **default是可选的**，但建议写上，就像if-else里的else

### break——最关键的"刹车"

**break是本课最重要的知识点！** 它就像一辆高速行驶汽车的"刹车"——遇到break，立即跳出switch结构。

**如果没有break会怎样？** 会发生可怕的"穿透"现象——执行完当前case的代码后，不会停下来，而是**继续执行下一个case的代码**，直到遇到break或switch结束！

来看一个例子：

```cpp
int day = 3;

// ❌ 忘记写break！
switch (day) {
    case 1: cout << "星期一";
    case 2: cout << "星期二";
    case 3: cout << "星期三";
    case 4: cout << "星期四";
    case 5: cout << "星期五";
}
```

猜一猜输出什么？答案是：**星期三星期四星期五**！因为当 `day == 3` 匹配后，从 `case 3` 开始执行，由于没有break，它一路"穿透"下去，把case 4和case 5的代码也执行了！

**正确的写法：**

```cpp
switch (day) {
    case 1: cout << "星期一"; break;
    case 2: cout << "星期二"; break;
    case 3: cout << "星期三"; break;  // ← break在这里刹车！
    case 4: cout << "星期四"; break;
    case 5: cout << "星期五"; break;
}
```

### 什么时候"穿透"是有用的？

有时候故意不写break反而很方便——比如多个case做同样的事情：

```cpp
// 判断工作日还是周末
switch (day) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        cout << "今天是工作日，要上学哦！" << endl;
        break;
    case 6:
    case 7:
        cout << "今天是周末，可以休息啦！" << endl;
        break;
}
```

这里case 1到5都没有break，它们全部"穿透"到case 5后面那句代码才执行，共同输出"工作日"。周末的两个case也一样。

### switch vs if-else：什么时候用哪个？

这是一个很实际的问题。记住这条黄金法则：

| 场景 | 推荐使用 | 原因 |
|------|----------|------|
| 判断**具体值**（如：1、2、3，'A'、'B'、'C'） | switch | 代码更清晰、直观 |
| 判断**范围**（如：>=90、>60、<0） | if-else if-else | switch无法判断范围！ |
| 判断**条件复杂**（多个条件，与或非） | if-else if-else | switch只能判断相等 |
| 选项**非常多**（10个以上具体值） | switch | 代码更整洁 |

**简单来说：** 判断"是不是等于某个值"用switch，判断"大于小于某个范围"用if-else。

比如：
- 星期几？→ 具体值1~7 → 用switch ✅
- 分数等级？→ 范围>=90, >=80... → 用if-else ✅
- 菜单选择？→ 具体值1~5 → 用switch ✅
- 温度判断？→ 大于30度/小于0度 → 用if-else ✅

## 💻 示例代码

### 示例1：星期几翻译器
```cpp
#include <iostream>
using namespace std;

int main() {
    int day;
    
    cout << "📅 ===== 星期几翻译器 =====" << endl;
    cout << "请输入数字1-7：";
    cin >> day;
    
    cout << endl;
    
    switch (day) {
        case 1:
            cout << "星期一 Monday —— 新的一周开始啦！💪" << endl;
            break;
        case 2:
            cout << "星期二 Tuesday —— 进入学习状态！📚" << endl;
            break;
        case 3:
            cout << "星期三 Wednesday —— 一周过半啦！🎯" << endl;
            break;
        case 4:
            cout << "星期四 Thursday —— 胜利在望！⭐" << endl;
            break;
        case 5:
            cout << "星期五 Friday —— 明天就是周末！🎉" << endl;
            break;
        case 6:
            cout << "星期六 Saturday —— 周末快乐！🎮" << endl;
            break;
        case 7:
            cout << "星期日 Sunday —— 好好休息！😴" << endl;
            break;
        default:
            cout << "❌ 输入错误！请输入1-7之间的数字。" << endl;
            break;
    }
    
    return 0;
}
```

### 示例2：switch的"穿透"演示
```cpp
#include <iostream>
using namespace std;

int main() {
    
    cout << "⚡ ===== 穿透现象演示 =====" << endl;
    cout << endl;
    
    // 演示1：没有break的穿透
    cout << "--- 没有break（穿透了！）---" << endl;
    int num = 2;
    switch (num) {
        case 1: cout << "执行了 case 1" << endl;
        case 2: cout << "执行了 case 2" << endl;
        case 3: cout << "执行了 case 3" << endl;
        case 4: cout << "执行了 case 4" << endl;
        // 输出：执行了 case 2、3、4 —— 全穿透了！
    }
    
    cout << endl;
    
    // 演示2：有break的正常情况
    cout << "--- 有break（正常）---" << endl;
    num = 2;
    switch (num) {
        case 1: cout << "执行了 case 1" << endl; break;
        case 2: cout << "执行了 case 2" << endl; break;
        case 3: cout << "执行了 case 3" << endl; break;
        case 4: cout << "执行了 case 4" << endl; break;
        // 输出：只执行了 case 2 —— break刹车成功！
    }
    
    cout << endl;
    
    // 演示3：巧妙利用穿透——多个case做同一件事
    cout << "--- 巧用穿透：判断工作日/周末 ---" << endl;
    int day = 3;
    switch (day) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            cout << "工作日，认真上课！📖" << endl;
            break;
        case 6:
        case 7:
            cout << "周末，尽情玩耍！🎮" << endl;
            break;
    }
    
    return 0;
}
```

### 示例3：自动点餐机
```cpp
#include <iostream>
using namespace std;

int main() {
    int choice;
    
    cout << "🍔 ===== 欢迎来到自动点餐机！ =====" << endl;
    cout << endl;
    cout << "📋 今日菜单：" << endl;
    cout << "  1. 🍔 汉堡 —— 15元" << endl;
    cout << "  2. 🍟 薯条 —— 8元" << endl;
    cout << "  3. 🥤 可乐 —— 5元" << endl;
    cout << "  4. 🍦 冰淇淋 —— 6元" << endl;
    cout << "  5. 🍗 鸡翅 —— 12元" << endl;
    cout << endl;
    cout << "请输入菜品序号（1-5）：";
    cin >> choice;
    
    cout << endl;
    cout << "===== 点餐结果 =====" << endl;
    
    switch (choice) {
        case 1:
            cout << "✅ 点餐成功！" << endl;
            cout << "🍔 汉堡 ×1 —— 15元" << endl;
            cout << "   请取餐，祝您用餐愉快！" << endl;
            break;
        case 2:
            cout << "✅ 点餐成功！" << endl;
            cout << "🍟 薯条 ×1 —— 8元" << endl;
            cout << "   请取餐，祝您用餐愉快！" << endl;
            break;
        case 3:
            cout << "✅ 点餐成功！" << endl;
            cout << "🥤 可乐 ×1 —— 5元" << endl;
            cout << "   请取餐，祝您用餐愉快！" << endl;
            break;
        case 4:
            cout << "✅ 点餐成功！" << endl;
            cout << "🍦 冰淇淋 ×1 —— 6元" << endl;
            cout << "   请取餐，祝您用餐愉快！" << endl;
            break;
        case 5:
            cout << "✅ 点餐成功！" << endl;
            cout << "🍗 鸡翅 ×1 —— 12元" << endl;
            cout << "   请取餐，祝您用餐愉快！" << endl;
            break;
        default:
            cout << "❌ 抱歉，没有这个菜品！" << endl;
            cout << "   请输入1-5之间的序号哦~" << endl;
            break;
    }
    
    return 0;
}
```

## 🎮 趣味练习

### 练习1：星期翻译官
写一个switch程序，输入数字1-7，输出对应的中文星期几。如果输入不在1-7范围内，提示"输入错误"。

**参考答案：**
```cpp
#include <iostream>
using namespace std;

int main() {
    int day;
    cout << "请输入数字（1-7）：";
    cin >> day;
    
    switch (day) {
        case 1: cout << "星期一" << endl; break;
        case 2: cout << "星期二" << endl; break;
        case 3: cout << "星期三" << endl; break;
        case 4: cout << "星期四" << endl; break;
        case 5: cout << "星期五" << endl; break;
        case 6: cout << "星期六" << endl; break;
        case 7: cout << "星期日" << endl; break;
        default: cout << "输入错误！请输入1-7。" << endl; break;
    }
    
    return 0;
}
```

### 练习2：穿透大考验
下面代码输入数字3时会输出什么？

```cpp
int n = 3;
switch (n) {
    case 1: cout << "A";
    case 2: cout << "B";
    case 3: cout << "C";
    case 4: cout << "D";
    case 5: cout << "E";
}
```

**参考答案：**
输出：**CDE**

因为case 3匹配后，从"C"开始执行，由于没有break，一路穿透下去，依次输出C、D、E。注意A、B不会输出，因为switch是从匹配的那个case开始执行的，不是从头开始！

### 练习3：选对工具
想一想：第15课的成绩等级评定系统（90-100→A，80-89→B……），用switch改写合适吗？为什么？

**参考答案：**
**不合适！** 原因是：
- 分数等级是基于**范围**判断的（>=90、>=80、>=70……），而switch只能判断**是否等于某个具体值**
- 如果硬要用switch，需要写100个case（case 0到case 100），把每个分数都映射到对应等级，这显然是不现实的
- 所以成绩等级评定用 **if-else if-else** 才是正确选择！

**这印证了我们的选择原则：判断范围用if-else，判断具体值用switch。**

## 🏆 挑战任务

### 挑战：完整自动点餐机

编写一个"自动点餐机"程序：
- 显示菜单（1-汉堡15元、2-薯条8元、3-可乐5元、4-冰淇淋6元、5-鸡翅12元）
- 用户输入序号选择
- 用switch输出对应的菜品名称、价格和"点餐成功"
- 输入其他数字用default提示"没有这个菜品，请输入1-5"
- **加分项：** 允许用户输入数量，计算总价

**参考示例：**
```cpp
#include <iostream>
using namespace std;

int main() {
    int choice, quantity;
    double price = 0;
    string itemName = "";
    
    cout << "🍔 ===== 欢迎来到自动点餐机！ =====" << endl;
    cout << endl;
    cout << "📋 今日菜单：" << endl;
    cout << "  ┌────┬──────────┬──────┐" << endl;
    cout << "  │序号│  菜品     │ 价格 │" << endl;
    cout << "  ├────┼──────────┼──────┤" << endl;
    cout << "  │ 1  │ 🍔 汉堡  │ 15元 │" << endl;
    cout << "  │ 2  │ 🍟 薯条  │  8元 │" << endl;
    cout << "  │ 3  │ 🥤 可乐  │  5元 │" << endl;
    cout << "  │ 4  │ 🍦 冰淇淋│  6元 │" << endl;
    cout << "  │ 5  │ 🍗 鸡翅  │ 12元 │" << endl;
    cout << "  └────┴──────────┴──────┘" << endl;
    cout << endl;
    
    cout << "请选择菜品序号（1-5）：";
    cin >> choice;
    
    switch (choice) {
        case 1:
            itemName = "汉堡";
            price = 15;
            break;
        case 2:
            itemName = "薯条";
            price = 8;
            break;
        case 3:
            itemName = "可乐";
            price = 5;
            break;
        case 4:
            itemName = "冰淇淋";
            price = 6;
            break;
        case 5:
            itemName = "鸡翅";
            price = 12;
            break;
        default:
            cout << "❌ 抱歉，没有这个菜品！请输入1-5之间的序号。" << endl;
            return 0;
    }
    
    cout << "请输入数量：";
    cin >> quantity;
    
    if (quantity <= 0) {
        cout << "❌ 数量必须大于0！" << endl;
        return 0;
    }
    
    double total = price * quantity;
    
    cout << endl;
    cout << "===== 📋 订单详情 =====" << endl;
    cout << "菜品：" << itemName << endl;
    cout << "单价：" << price << " 元" << endl;
    cout << "数量：" << quantity << " 份" << endl;
    cout << "总价：" << total << " 元" << endl;
    cout << endl;
    cout << "✅ 点餐成功！请取餐，祝您用餐愉快！🍽️" << endl;
    
    return 0;
}
```

## 📝 本课小结

### 核心知识点回顾

| 知识点 | 说明 |
|--------|------|
| switch语法 | `switch(变量) { case 值: 代码; break; default: 代码; break; }` |
| case | 后面跟冒号`:`，值是具体的整数或字符 |
| break | **关键**！遇到break跳出switch，没有break会"穿透"到下一个case |
| 穿透现象 | 没有break时，会从匹配的case一直往下执行 |
| default | 所有case都不匹配时执行，相当于if-else中的else |
| 适用场景 | 判断**具体值**时用switch，判断**范围**时用if-else |

### switch vs if-else 选择指南

```
要判断的是具体值吗？
    │
    ├── 是 → 选项多吗？
    │        ├── 多（3个以上）→ 用 switch ✅
    │        └── 少（2-3个） → switch或if-else都可以
    │
    └── 否（判断范围、复杂条件）→ 用 if-else if-else ✅
```

### 记住口诀

> **万能开关switch到，case对应把路找；**
> **遇到break就刹车，没有break一路跑！**
> **default做兜底，具体值判断它最好；**
> **范围判断用if-else，选对工具代码妙！**

---

**下一课预告：** 第17课——转圈的机器人while循环，让电脑不知疲倦地重复工作！🤖
