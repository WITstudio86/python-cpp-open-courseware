# 第17课：转圈的机器人——while循环

## 🎯 学习目标
- 理解while循环的基本语法和执行流程
- 掌握循环条件的设置技巧，避免死循环
- 能够使用while循环解决简单的重复执行问题

## 📖 知识讲解

### 什么是while循环？

小明家里有一个扫地机器人，它有一个特别的本领：只要电量充足，它就会不停地在地上转圈清扫，直到电量不足才停下来。C++中的`while`循环就像这个转圈的机器人——只要某个条件成立，就会一遍又一遍地执行同一段代码。

想象一下，你在操场上跑步，老师说："在哨声响起之前，一直跑！"这个"哨声响起之前"就是循环条件。只要哨声还没响（条件为真），你就继续跑（执行循环体）；哨声一响（条件为假），你就停下来。

### while循环的语法

```cpp
while (条件) {
    // 循环体：条件成立时要执行的代码
}
```

while循环的执行流程是这样的：
1. 首先检查"条件"是否为真（true）
2. 如果条件为真，执行循环体中的代码
3. 执行完循环体后，回到第1步，再次检查条件
4. 如果条件为假（false），跳过循环体，继续执行后面的代码

这就像去超市买东西："只要购物清单上还有东西没买，就继续逛！"每次买完一样东西后，再看清单上是否还有东西——没买完就继续，买完了就结账回家。

### 循环三要素

一个完整的while循环通常包含三个重要部分，缺一不可：

1. **循环变量初始化**：在循环开始前，给循环变量一个初始值。就像跑步前要站在起点。

2. **循环条件**：决定循环是否继续的判断条件。就像"还没跑到终点"这个条件。

3. **循环变量更新**：在循环体内部，每次执行后更新循环变量。就像每跑一步就离终点更近一点。

让我们用一个"吃包子"的比喻来理解这三个要素：

```
初始化：盘子里有5个包子（int baozi = 5）
条件：只要盘子里还有包子（while (baozi > 0)）
更新：每吃一个，包子就少一个（baozi--）
```

如果忘记了第3步——更新循环变量，就会造成**死循环**（也叫无限循环）。程序会一直执行下去，永远停不下来，就像机器人忘记检查电量一直转圈！比如：

```cpp
int i = 1;
while (i <= 10) {
    cout << i << " ";
    // 糟糕！忘记写 i++ 了，i永远是1，循环永远不会结束！
}
```

**三要素自查清单**：
- [ ] 循环变量有没有在循环之前初始化？
- [ ] 条件表达式会不会有变为false的那一天？
- [ ] 循环体里有没有修改循环变量的语句？

三个问题都回答"是"，你的while循环就基本不会出问题！

### do-while与while的区别

C++中有两种while循环：`while` 和 `do-while`。它们很像，但有一个关键区别。

**while循环**：**先判断，再执行**。条件不成立时，循环体可能一次都不执行。就像你进餐厅前先看有没有位子，没有位子就不进去。

**do-while循环**：**先执行，再判断**。循环体至少执行一次。就像你先进餐厅，吃完后再决定要不要加菜。

用代码来对比：

```cpp
// ===== while循环：先判断，再执行 =====
int x = 10;
while (x < 5) {
    cout << "while: x = " << x << endl;  // 这行永远不会执行！
    x++;
}
// 输出：什么都不输出（因为10<5一开始就是false）

// ===== do-while循环：先执行，再判断 =====
int y = 10;
do {
    cout << "do-while: y = " << y << endl;  // 这行会执行一次！
    y++;
} while (y < 5);
// 输出：do-while: y = 10
```

**完整对比程序**：

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 1, b = 1;
    
    cout << "===== while vs do-while 对比 =====" << endl;
    cout << endl;
    
    // while：条件从一开始就成立
    cout << "【情况1：条件一直成立】" << endl;
    cout << "while循环：";
    a = 1;
    while (a <= 3) {
        cout << a << " ";
        a++;
    }
    cout << endl;
    
    cout << "do-while循环：";
    b = 1;
    do {
        cout << b << " ";
        b++;
    } while (b <= 3);
    cout << endl;
    cout << "结论：条件成立时，两者行为完全一样" << endl;
    cout << endl;
    
    // 关键区别：条件一开始就不成立
    cout << "【情况2：条件一开始就不成立】" << endl;
    cout << "while循环：";
    a = 10;
    while (a <= 3) {
        cout << a << " ";  // 一次都不执行
        a++;
    }
    cout << "（什么都不输出——一次都没执行！）" << endl;
    
    cout << "do-while循环：";
    b = 10;
    do {
        cout << b << " ";  // 至少执行一次！
        b++;
    } while (b <= 3);
    cout << "（执行了一次！）" << endl;
    cout << endl;
    
    cout << "结论：do-while 无论条件如何，至少执行一次！" << endl;
    cout << "      而 while 可能一次都不执行。" << endl;
    
    return 0;
}
```

**什么时候用哪个？**

| 场景 | 推荐 | 原因 |
|------|------|------|
| 打印1到100 | while / for | 知道要循环多少次 |
| 用户输入验证 | do-while | 至少要让用户输入一次 |
| 游戏主循环 | while(true) | 一直运行直到退出 |
| 菜单选择 | do-while | 菜单至少显示一次 |
| 文件读取 | while | 文件可能为空，一次都不读 |

### 死循环的产生原因和避免方法

**什么是死循环？**

死循环就是循环的条件永远为真，循环永远停不下来。就像那个转圈的机器人忘了检查电量，一直转到没电为止——但在程序里，它永远不会"没电"。

**死循环的三大原因**：

**原因1：忘了更新循环变量**

```cpp
int i = 1;
while (i <= 10) {
    cout << i << " ";
    // 忘了写 i++;  ← 这就是元凶！
}
// i永远=1，循环永远不会停
```

**原因2：循环变量更新方向错误**

```cpp
int i = 10;
while (i >= 1) {
    cout << i << " ";
    i++;  // 糟糕！i越来越大，离1越来越远！
}
// i=10, 11, 12, 13... 永远>=1，永远停不下来
```

**原因3：条件表达式写错**

```cpp
int score = 60;
while (score = 100) {  // 错误！用了=而不是==
    cout << "检查成绩..." << endl;
}
// score=100的结果是100（非零=true），条件永远成立！
```

**如何避免死循环：**

1. **写完循环后立即检查三要素**：初始化、条件、更新是否齐全
2. **在纸上模拟运行**：拿一个小数字，用手算的方式模拟循环过程，看条件能否变为false
3. **设置循环次数上限**（保险措施）：加一个计数器，超过合理次数就强制退出

```cpp
int i = 1;
int safetyCount = 0;  // 安全计数器

while (i <= 10) {
    cout << i << " ";
    i++;
    
    safetyCount++;
    if (safetyCount > 1000) {  // 如果超过1000次，肯定出问题了
        cout << "\n⚠️ 警告：循环次数异常，强制退出！" << endl;
        break;  // 强制退出循环
    }
}
```

4. **善意的死循环**：有些时候我们故意写死循环，但会在合适的时候用 `break` 跳出

```cpp
while (true) {
    cout << "1. 开始游戏  2. 设置  3. 退出" << endl;
    int choice;
    cin >> choice;
    
    if (choice == 3) {
        cout << "再见！" << endl;
        break;  // 正常退出死循环
    }
    // 处理其他选项...
}
```

## 💻 示例代码

### 示例1：数字倒计时器

火箭发射前的倒计时，是while循环最经典的应用之一！

```cpp
#include <iostream>
using namespace std;

int main() {
    int countdown = 10;  // 从10开始倒计时

    cout << "🚀 火箭发射倒计时开始！" << endl;

    while (countdown > 0) {
        cout << countdown << "..." << endl;
        countdown--;  // 每次减1，至关重要！没有这行就会死循环
    }

    cout << "🔥 发射！火箭升空！" << endl;
    return 0;
}
```

**运行结果：**
```
🚀 火箭发射倒计时开始！
10...
9...
8...
7...
6...
5...
4...
3...
2...
1...
🔥 发射！火箭升空！
```

### 示例2：猜数字游戏

```cpp
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));  // 设置随机种子
    int secret = rand() % 100 + 1;  // 1到100的随机数
    int guess = 0;
    int tries = 0;

    cout << "🎯 猜数字游戏（1-100）" << endl;

    while (guess != secret) {
        cout << "请输入你猜的数字：";
        cin >> guess;
        tries++;

        if (guess > secret) {
            cout << "太大了！往下猜猜～" << endl;
        } else if (guess < secret) {
            cout << "太小了！往上猜猜～" << endl;
        }
    }

    cout << "🎉 恭喜你猜对了！数字是 " << secret << endl;
    cout << "你一共猜了 " << tries << " 次" << endl;
    return 0;
}
```

### 示例3：while计数器——统计数字位数

```cpp
#include <iostream>
using namespace std;

int main() {
    int number;
    cout << "请输入一个正整数：";
    cin >> number;
    
    int count = 0;       // 计数器，初始为0
    int temp = number;   // 保存原始数字的副本
    
    // 每次循环去掉最后一位，计数器加1
    while (temp > 0) {
        temp = temp / 10;  // 去掉最后一位
        count++;           // 计数器加1
    }
    
    cout << number << " 是一个 " << count << " 位数。" << endl;
    
    // 趣味分析
    if (count == 1) {
        cout << "个位数！简单明了~" << endl;
    } else if (count <= 4) {
        cout << count << "位数，很不错！" << endl;
    } else {
        cout << "哇，" << count << "位数！这是一个很大的数字呢！" << endl;
    }
    
    return 0;
}
```

**运行效果**：输入12345 → 输出"12345 是一个 5 位数。哇，5位数！这是一个很大的数字呢！"

### 示例4：while累加器——计算平均分

```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "===== 班级平均分计算器 =====" << endl;
    cout << "请输入班级人数：";
    cin >> n;
    
    int i = 1;          // 循环变量：当前是第几个同学
    double score;       // 每个同学的成绩
    double sum = 0;     // 累加器：总分，初始为0
    
    while (i <= n) {
        cout << "请输入第" << i << "位同学的成绩：";
        cin >> score;
        
        // 输入验证：成绩必须在0-100之间
        if (score < 0 || score > 100) {
            cout << "⚠️ 成绩不合法（0-100），请重新输入！" << endl;
            continue;  // 不累加也不增加i，直接回到循环开头
        }
        
        sum = sum + score;  // 累加到总分
        i++;                // 移到下一位同学
    }
    
    double average = sum / n;
    cout << "\n—— 统计结果 ——" << endl;
    cout << "班级人数：" << n << " 人" << endl;
    cout << "总分：" << sum << " 分" << endl;
    cout << "平均分：" << average << " 分" << endl;
    
    // 对平均分做出评价
    if (average >= 90) {
        cout << "🏆 太棒了！这个班是学霸班！" << endl;
    } else if (average >= 70) {
        cout << "👍 不错，继续加油！" << endl;
    } else {
        cout << "💪 需要更加努力哦！" << endl;
    }
    
    return 0;
}
```

**要点**：注意 `continue` 的使用——当成绩不合法时，跳过累加，直接回到循环开头让用户重新输入。这保证了统计的准确性。

### 示例5：while输入验证——密码登录系统

```cpp
#include <iostream>
using namespace std;

int main() {
    const int CORRECT_PASSWORD = 2024;
    int password;
    int attempts = 0;          // 尝试次数
    const int MAX_ATTEMPTS = 3; // 最大允许次数
    
    cout << "===== 🔐 密码登录系统 =====" << endl;
    cout << "你最多有 " << MAX_ATTEMPTS << " 次尝试机会" << endl;
    
    while (attempts < MAX_ATTEMPTS) {
        cout << "\n请输入密码：";
        cin >> password;
        attempts++;
        
        if (password == CORRECT_PASSWORD) {
            cout << "✅ 密码正确！欢迎进入系统！" << endl;
            cout << "你用了 " << attempts << " 次尝试。" << endl;
            return 0;  // 登录成功，程序结束
        } else {
            cout << "❌ 密码错误！" << endl;
            int remaining = MAX_ATTEMPTS - attempts;
            if (remaining > 0) {
                cout << "你还剩 " << remaining << " 次机会。" << endl;
                cout << "提示：密码是一个年份~" << endl;
            }
        }
    }
    
    // 循环结束 = 尝试次数用完了
    cout << "\n🚫 尝试次数已用完！账户已锁定。" << endl;
    cout << "请30分钟后重试。" << endl;
    
    return 0;
}
```

**要点**：这个程序有三个while循环的经典应用：
1. **计数器**（`attempts`）：统计输入了几次
2. **输入验证**：判断密码是否正确
3. **上限保护**（`MAX_ATTEMPTS`）：防止无限尝试

## 🎮 趣味练习

### 练习1：报数小能手

使用while循环，打印数字1到20，每个数字之间用空格隔开。

**参考答案：**
```cpp
int i = 1;
while (i <= 20) {
    cout << i << " ";
    i++;
}
```

### 练习2：求和计算器

使用while循环，计算1到100所有整数的和，并输出结果。（提示：5050）

**参考答案：**
```cpp
int i = 1, sum = 0;
while (i <= 100) {
    sum += i;  // 等价于 sum = sum + i
    i++;
}
cout << "1到100的和是：" << sum << endl;  // 输出5050
```

### 练习3：新年倒计时

写一个程序，让用户输入一个正整数n，然后从n倒数到1，最后输出"新年快乐！"

### 练习4：while累加器——求奇数和

使用while循环，计算1到100之间所有奇数的和。（提示：2500）

**参考答案：**
```cpp
int i = 1, sum = 0;
while (i <= 100) {
    if (i % 2 == 1) {  // 判断i是否为奇数
        sum += i;
    }
    i++;
}
cout << "1到100奇数的和是：" << sum << endl;  // 输出2500
```

**思考**：如果不加if判断，怎样只通过修改循环变量更新方式来求奇数和？（提示：每次i增加2）

### 练习5：乘法表查询器

让用户输入一个1到9之间的整数n，使用while循环输出n的乘法口诀（从 n×1 到 n×9）。

**参考答案：**
```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "请输入1-9之间的整数，查看它的乘法表：";
    cin >> n;
    
    if (n >= 1 && n <= 9) {
        int i = 1;
        cout << "—— " << n << " 的乘法表 ——" << endl;
        while (i <= 9) {
            cout << n << " × " << i << " = " << n * i << endl;
            i++;
        }
    } else {
        cout << "请输入1-9之间的整数哦！" << endl;
    }
    
    return 0;
}
```

## 🏆 挑战任务

### ATM取款机模拟

设计一个简单的ATM取款模拟程序。初始余额为1000元，每次操作可以：
- 输入1：查看余额
- 输入2：取款（输入金额）
- 输入3：退出

使用while(true)创建一个循环菜单，直到用户选择退出。取款时如果余额不足要给出提示。

**提示：** 需要使用`while(true)`、`if-else`和`break`的组合。

## 📝 本课小结

- **while循环**是C++中最基本的循环结构，格式为`while(条件){循环体}`
- while循环**先判断条件，再执行循环体**。条件为假时，循环体可能一次都不执行
- 循环必须包含**初始化、条件、更新**三要素，缺一不可
- 忘记更新循环变量会导致**死循环**，让程序永远运行下去
- `while(true)`可以创建故意无限循环，配合`break`可以在需要时跳出
- while循环适合**不知道具体循环次数**的场景，比如输入验证、游戏主循环等
