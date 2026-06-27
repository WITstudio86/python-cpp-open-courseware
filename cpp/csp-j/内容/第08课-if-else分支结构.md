# 第8课：if-else 分支结构

## 🎯 考纲要求
- 单分支 if
- 双分支 if-else
- 多分支 if-else if-else
- 嵌套 if
- 悬空 else 问题（else与最近的if匹配）

## 📖 知识精讲

### 一、单分支 if

**语法**：
```cpp
if (条件表达式) {
    语句块;  // 条件为true时执行
}
```

**执行流程**：
1. 计算"条件表达式"的值
2. 若为true（非0），执行花括号内的语句
3. 若为false（0），跳过花括号内的语句
4. 继续执行后面的代码

```cpp
int score = 85;
if (score >= 60) {
    cout << "及格" << endl;
}
```

**简化写法**（只有一条语句时可以省略花括号）：
```cpp
if (score >= 60) cout << "及格" << endl;
```
但考试中建议**始终保留花括号**，避免出错。

### 二、双分支 if-else

**语法**：
```cpp
if (条件表达式) {
    语句块1;  // 条件为true时执行
} else {
    语句块2;  // 条件为false时执行
}
```

```cpp
int score = 85;
if (score >= 60) {
    cout << "及格" << endl;
} else {
    cout << "不及格" << endl;
}
```

### 三、多分支 if-else if-else

**语法**：
```cpp
if (条件1) {
    语句块1;
} else if (条件2) {
    语句块2;
} else if (条件3) {
    语句块3;
} else {
    语句块4;  // 以上条件都不满足时执行
}
```

**执行流程**：从上到下依次检查条件，找到第一个为true的条件就执行对应的语句块并结束整个if结构。**即使后面还有条件为true也不再判断**。

**典型应用：成绩等级判定**
```cpp
int score;
cin >> score;

if (score >= 90) {
    cout << "A" << endl;
} else if (score >= 80) {
    cout << "B" << endl;
} else if (score >= 70) {
    cout << "C" << endl;
} else if (score >= 60) {
    cout << "D" << endl;
} else {
    cout << "E" << endl;
}
```

**注意**：条件顺序很重要！如果把 `score >= 80` 放在 `score >= 90` 前面，输入95会得到 B 而不是 A。多分支条件必须从**严格到宽松**排列。

### 四、嵌套 if

在 if 或 else 的语句块中再包含 if 结构。

```cpp
int a, b, c;
cin >> a >> b >> c;

if (a > b) {
    if (a > c) {
        cout << "a最大" << endl;
    } else {
        cout << "c最大" << endl;
    }
} else {
    if (b > c) {
        cout << "b最大" << endl;
    } else {
        cout << "c最大" << endl;
    }
}
```

### 五、悬空 else 问题（考试重点！）

**规则**：else 总是与最近的、尚未配对的 if 匹配（就近原则）。

**经典例题**：
```cpp
int a = 1, b = 2;
if (a == 0)
    if (b == 2)
        cout << "A" << endl;
else          // 这个else和哪个if配对？
    cout << "B" << endl;
```

**解析**：根据就近原则，else 与最近的 `if (b == 2)` 配对。因为 `a == 0` 为false，整个内层if-else都被跳过。所以**无输出**。

**改进**：使用花括号明确配对关系
```cpp
if (a == 0) {
    if (b == 2)
        cout << "A" << endl;
} else {
    cout << "B" << endl;  // 输出B，因为a==0为false
}
```

### 六、条件表达式深入

**条件可以是任意能转换为bool的表达式**：
```cpp
if (a)           // a != 0 时为true
if (!a)          // a == 0 时为true
if (a % 2)       // 奇数时为true
if (a % 2 == 0)  // 偶数时为true
```

**多个条件的组合**：
```cpp
// 判断是否为闰年
if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
    cout << "闰年" << endl;
}
```

## 💻 代码模板

### 多分支-成绩等级模板
```cpp
#include <iostream>
using namespace std;

int main() {
    int score;
    cin >> score;
    
    // 多分支判断（条件从大到小排列）
    if (score >= 90) {
        cout << "A" << endl;
    } else if (score >= 80) {
        cout << "B" << endl;
    } else if (score >= 70) {
        cout << "C" << endl;
    } else if (score >= 60) {
        cout << "D" << endl;
    } else {
        cout << "E" << endl;
    }
    
    return 0;
}
```

### if-else 通用模板
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int a, b, c;
    cin >> a >> b >> c;
    
    // 求最大值（嵌套if）
    int maxVal;
    if (a >= b && a >= c) {
        maxVal = a;
    } else if (b >= a && b >= c) {
        maxVal = b;
    } else {
        maxVal = c;
    }
    cout << "最大值: " << maxVal << endl;
    
    // 更简洁的方式
    cout << "最大值(简洁): " << max({a, b, c}) << endl;
    
    // 排序三个数
    if (a > b) swap(a, b);
    if (a > c) swap(a, c);
    if (b > c) swap(b, c);
    cout << "排序: " << a << " " << b << " " << c << endl;
    
    return 0;
}
```

## ⚠️ 易错点

- **if后面加分号**：`if (a > b);` 这表示if后面是一个空语句，大括号里的代码会无条件执行！千万不要在if条件后面加分号（除非你明确需要空语句）。
- **等号与双等号混淆**：`if (a = 5)` 是赋值（结果始终为true），`if (a == 5)` 才是判断。这是最隐蔽也最常见的错误。
- **悬空else问题**：不带花括号的嵌套if中，else与最近的if配对。解决办法：始终使用花括号 `{}` 明确代码结构。
- **多分支条件顺序**：if-else if结构按顺序检查，一旦满足就停止。条件必须从最严格到最宽松排列，否则永远到不了后面的分支。
- **复合条件优先级不明确**：`if (a > 0 || b > 0 && c > 0)` 的含义是 `if (a > 0 || (b > 0 && c > 0))`，因为 `&&` 优先级高于 `||`。不确定时加括号最安全。
- **浮点数比较**：`if (x == 0.1)` 可能为假！浮点数用近似比较：`if (fabs(x - 0.1) < 1e-9)`。

## 📝 真题精练

### 题目1：悬空 else
**题目描述**：阅读以下程序，写出运行结果。
```cpp
#include <iostream>
using namespace std;
int main() {
    int x = 5, y = 0;
    if (x > 0)
        if (y > 0)
            cout << "A" << endl;
    else
        cout << "B" << endl;
    return 0;
}
```

**分析过程**：
- x=5>0为true，进入外层if
- 判断内层条件 y>0，y=0为false
- else与最近的if（内层 `if(y>0)`）匹配，所以执行else中的 `cout << "B"`
- 输出 B

**答案**：`B`

```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 5, y = 0;
    
    // 悬空else：else与最近的if(y>0)匹配
    if (x > 0)
        if (y > 0)
            cout << "A" << endl;
        else
            cout << "B" << endl;  // 输出B
    
    // 正确写法：使用花括号明确范围
    if (x > 0) {
        if (y > 0) {
            cout << "A" << endl;
        } else {
            cout << "B" << endl;
        }
    }
    
    return 0;
}
```

### 题目2：多分支条件判断
**题目描述**：阅读以下程序，如果输入 `85`，输出是什么？
```cpp
#include <iostream>
using namespace std;
int main() {
    int score;
    cin >> score;
    if (score >= 60) {
        cout << "及格" << endl;
    } else if (score >= 80) {
        cout << "良好" << endl;
    } else if (score >= 90) {
        cout << "优秀" << endl;
    }
    return 0;
}
```

**分析过程**：
- 输入85
- 先判断第一个条件 `score >= 60`，85>=60为true
- 输出"及格"，整个if-else if结构结束
- 后面的 `score >= 80` 和 `score >= 90` 都不会被判断
- 这就是条件顺序错误的典型问题！

**答案**：`及格`

**正确写法**：条件从大到小排列。
```cpp
#include <iostream>
using namespace std;

int main() {
    int score;
    cin >> score;
    
    // 错误写法：条件从宽到严
    // 输入85只会输出"及格"
    
    // 正确写法：条件从严到宽
    if (score >= 90) {
        cout << "优秀" << endl;
    } else if (score >= 80) {
        cout << "良好" << endl;
    } else if (score >= 60) {
        cout << "及格" << endl;
    } else {
        cout << "不及格" << endl;
    }
    
    return 0;
}
```

## 🎯 本课小结
1. 三种分支结构：if（单分支）、if-else（双分支）、if-else if-else（多分支）
2. 嵌套if：在if/else内部再写if结构，用于复杂条件判断
3. 悬空else规则：else总是与最近的、尚未配对的if匹配（就近原则）
4. 多分支条件顺序：必须从最严格到最宽松排列，否则后续条件永远不会执行
5. 注意三个高频坑：if后面多加分号、`=`当成`==`、浮点数直接比较相等
