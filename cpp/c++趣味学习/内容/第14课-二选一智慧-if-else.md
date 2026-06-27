# 第14课：二选一的智慧——if-else

## 🎯 学习目标
- 掌握if-else双分支结构的语法
- 理解else的配对规则（else与最近的未配对if配对）
- 能运用if-else解决"二选一"的实际问题

## 📖 知识讲解

同学们，上一课我们学习了if语句——当条件成立时执行某段代码。但你有没有想过：**如果条件不成立，我们能不能做点别的事情呢？**

答案是：当然可以！这就需要今天的主角——**if-else**双分支结构登场了！

### 生活中的"二选一"

人生充满了选择，就像走到岔路口，不是向左就是向右。你每天都在做"二选一"的判断：

- 考试分数 >= 60？→ **及格啦！** / 否则 → **要加油哦～**
- 今天下雨了？→ **带雨伞** / 否则 → **不带伞**
- 余额够买？→ **下单支付** / 否则 → **余额不足，下次再来**
- 肚子饿了？→ **去吃饭** / 否则 → **继续学习**

if-else就是帮我们把这种"不是A就是B"的选择写成代码。

### if-else的基本语法

```cpp
if (条件) {
    // 条件成立 → 走这条路
    // 执行的代码A
} else {
    // 条件不成立 → 走另外一条路
    // 执行的代码B
}
```

**关键理解**：if和else是**互斥**的——要么执行if里的代码，要么执行else里的代码，**二者必选其一，不可能两个都执行，也不可能两个都不执行**。

### 流程图理解

```
            [ 开始 ]
               |
               v
        [ 判断条件 ] 
        /          \
     true          false
      /              \
     v                v
[ 执行if代码块 ]  [ 执行else代码块 ]
      \              /
       v            v
        [ 继续往下走 ]
```

### else的配对规则

这是本节课的**重点和难点**！当你的代码中出现多个if和else时，else到底和哪个if配对呢？

**规则**：else总是和它上面最近的、还没有配对的if配对。

看例子：

```cpp
if (score >= 90)        // 第1个if
    if (score == 100)   // 第2个if
        cout << "满分！太厉害了！" << endl;
    else                // 这个else和谁配对？
        cout << "优秀！" << endl;
```

上面的else和谁配对？根据规则：它和最近的未配对if配对——也就是**第2个if（score == 100）**。

所以这段代码的逻辑是：
- score >= 90 且 score == 100 → 输出"满分！"  
- score >= 90 且 score != 100 → 输出"优秀！"
- score < 90 → 什么都不输出

这是不是你想要的效果？如果不是——你就需要用**花括号{}**来明确配对关系！

### 用花括号明确配对

```cpp
if (score >= 90) {
    if (score == 100) {
        cout << "满分！太厉害了！" << endl;
    }
} else {   // 现在这个else明确和第一个if配对
    cout << "要继续努力哦！" << endl;
}
```

**最佳实践**：不管代码多简单，都加上花括号！这样永远不会有歧义。

### 嵌套if-else：更多选择

当"二选一"不够用时，我们可以在if或else里面再嵌套if-else：

```cpp
if (number > 0) {
    cout << "正数" << endl;
} else {
    // 在else里面再判断
    if (number == 0) {
        cout << "零" << endl;
    } else {
        cout << "负数" << endl;
    }
}
```

这种"在else里再写if-else"的写法非常常见，后续我们还会学到更简洁的`else if`写法！

## 💻 示例代码

### 示例1：基本if-else——判断奇偶数

```cpp
#include <iostream>
using namespace std;

int main() {
    int number;
    cout << "请输入一个整数：";
    cin >> number;
    
    // 用取余运算 % 判断奇偶
    // 如果除以2的余数为0，就是偶数；否则是奇数
    if (number % 2 == 0) {
        cout << number << " 是偶数！" << endl;
        cout << "偶数可以被2整除哦~" << endl;
    } else {
        cout << number << " 是奇数！" << endl;
        cout << "奇数除以2会余1~" << endl;
    }
    
    return 0;
}
```

### 示例2：if-else判断成绩是否及格

```cpp
#include <iostream>
using namespace std;

int main() {
    int score;
    cout << "请输入你的考试分数：";
    cin >> score;
    
    if (score >= 60) {
        cout << "🎉 恭喜！你及格了！" << endl;
        cout << "你的分数是：" << score << " 分" << endl;
    } else {
        cout << "💪 这次没有及格，不要灰心！" << endl;
        cout << "你的分数是：" << score << " 分" << endl;
        cout << "距离及格还差 " << (60 - score) << " 分，继续加油！" << endl;
    }
    
    return 0;
}
```

### 示例3：嵌套if-else——判断正数、负数还是零

```cpp
#include <iostream>
using namespace std;

int main() {
    int number;
    cout << "请输入一个整数：";
    cin >> number;
    
    if (number > 0) {
        cout << number << " 是正数" << endl;
    } else {
        // 走到这里说明 number <= 0
        // 在else里继续判断
        if (number == 0) {
            cout << "你输入的是零！" << endl;
            cout << "零既不是正数也不是负数。" << endl;
        } else {
            cout << number << " 是负数" << endl;
        }
    }
    
    return 0;
}
```

## 🎮 趣味练习

### 练习1：奇偶判断器

输入一个整数，判断它是奇数还是偶数。

```cpp
#include <iostream>
using namespace std;

int main() {
    int num;
    cout << "请输入一个整数：";
    cin >> num;
    
    if (num % 2 == 0) {
        cout << num << " 是偶数" << endl;
    } else {
        cout << num << " 是奇数" << endl;
    }
    
    return 0;
}
```

### 练习2：else配对谜题

下面代码有什么问题？else和谁配对？

```cpp
if (score >= 90)
    if (score == 100)
        cout << "满分！";
else
    cout << "优秀！";
```

**答案**：else和里面的`if (score == 100)`配对，而不是和外面的`if (score >= 90)`配对！这会导致：
- 当score >= 90 且 score == 100 时，输出"满分！"
- 当score >= 90 且 score != 100 时，输出"优秀！"
- 当score < 90 时，**什么都不输出**（这很可能不是你想要的效果！）

**修复方法**：给每个if加上花括号，明确控制范围：
```cpp
if (score >= 90) {
    if (score == 100) {
        cout << "满分！";
    }
} else {
    cout << "要继续加油哦！";
}
```

### 练习3：登录验证程序

输入用户名和密码，判断是否能登录。预设用户名`admin`，密码`123456`。

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string username, password;
    string correctUser = "admin";
    string correctPass = "123456";
    
    cout << "===== 用户登录 =====" << endl;
    cout << "用户名：";
    cin >> username;
    cout << "密码：";
    cin >> password;
    
    if (username == correctUser && password == correctPass) {
        cout << "✅ 登录成功！欢迎回来，" << username << "！" << endl;
    } else {
        cout << "❌ 登录失败！用户名或密码错误。" << endl;
    }
    
    return 0;
}
```

## 🏆 挑战任务

### 🎯 猜数字小游戏

编写"猜数字小游戏"：预设一个秘密数字`secret = 42`，让用户输入猜测的数字。如果猜对了输出"恭喜你猜对了！"，否则根据大小给出"猜大了"或"猜小了"的提示。

```cpp
#include <iostream>
using namespace std;

int main() {
    int secret = 42;   // 秘密数字
    int guess;          // 用户的猜测
    
    cout << "╔══════════════════════════════════╗" << endl;
    cout << "║      🎯 猜数字小游戏           ║" << endl;
    cout << "║  我心里想了一个1~100之间的数  ║" << endl;
    cout << "║  你能猜到是哪个吗？           ║" << endl;
    cout << "╚══════════════════════════════════╝" << endl;
    cout << endl;
    cout << "请输入你猜的数字：";
    cin >> guess;
    
    if (guess == secret) {
        cout << "🎉🎉🎉 恭喜你猜对了！就是" << secret << "！" << endl;
        cout << "你太厉害了，一次就猜中了！" << endl;
    } else {
        // 没猜对，告诉用户大了还是小了
        if (guess > secret) {
            cout << "📈 猜大了！" << endl;
            cout << "你猜的是 " << guess << "，比秘密数字大哦~" << endl;
            cout << "提示：往小一点的数字猜！" << endl;
        } else {
            cout << "📉 猜小了！" << endl;
            cout << "你猜的是 " << guess << "，比秘密数字小哦~" << endl;
            cout << "提示：往大一点的数字猜！" << endl;
        }
    }
    
    cout << "\n游戏结束，谢谢参与！" << endl;
    return 0;
}
```

**扩展思考**：你能改成让用户有3次猜的机会吗？（提示：后续会学到循环！）

## 📝 本课小结

| 知识点 | 说明 |
|--------|------|
| if-else语法 | `if (条件) { 代码A; } else { 代码B; }` |
| 执行逻辑 | 条件成立→执行A，不成立→执行B，二者必选其一 |
| else配对规则 | else与上面最近的未配对if配对 |
| 嵌套if-else | 在if或else代码块里再写if-else，实现多路选择 |
| 最佳实践 | 永远使用花括号{}避免配对歧义 |

**if-else 与 单if 的区别**：

| 对比项 | 单if | if-else |
|--------|------|---------|
| 条件不成立时 | 什么都不做，直接跳过 | 执行else里的代码 |
| 使用场景 | "如果...就..." | "如果...就...否则..." |
| 选择数量 | 0或1个选择 | 必须选1个（二选一） |

记住口诀：**条件成立走if路，条件不成走else路；两条路里必选一，花括号里看清楚！else配对有规律，最近if是归属；若想配对不迷路，花括号来把路铺！**
