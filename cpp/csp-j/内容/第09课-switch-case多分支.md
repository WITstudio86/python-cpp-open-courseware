# 第9课：switch-case 多分支结构

## 🎯 考纲要求

- **switch-case 语法结构**：掌握 `switch(表达式)` 和 `case 常量:` 的基本写法
- **break 的作用**：理解 break 语句在 case 块中的作用，掌握「穿透现象」的产生与控制
- **default 分支**：了解 default 的使用场景与合理位置
- **switch 与 if-else 的选择**：能根据题目需求（离散值 vs 范围判断）正确选择分支结构
- **嵌套 switch**：了解 switch 嵌套的基本写法与应用场景

---

## 📖 知识精讲

### 一、多分支的现实需求

在程序设计中，我们经常遇到「根据不同取值，执行不同操作」的场景。比如：

- 一个简单的计算器，用户输入运算符 `+` `-` `*` `/`，程序需要根据运算符执行相应的运算；
- 成绩等级转换，输入分数段（A/B/C/D/F），输出对应的评语；
- 菜单选择系统，用户输入 1~5 的数字，程序跳转到对应功能。

当一个变量有多个离散的可能取值，且每个取值对应一段独立的逻辑时，if-else 链虽然能完成任务，但代码会变得冗长、可读性差。C++ 提供了 **switch-case** 结构来优雅地解决这个问题。

### 二、基本语法

switch-case 的基本语法如下：

```cpp
switch (表达式) {
    case 常量1:
        语句块1;
        break;
    case 常量2:
        语句块2;
        break;
    case 常量3:
        语句块3;
        break;
    // ... 更多 case
    default:
        默认语句块;
        break;
}
```

**关键要素说明：**

1. **switch 后的表达式**：必须是 **整型**（`int`）、**字符型**（`char`）或 **枚举类型**。C++ 中不能使用 `float`、`double`、`string` 作为 switch 的表达式。表达式的值会与各个 case 后的常量逐一比较。

2. **case 后的常量**：必须是 **编译期确定的常量**（字面量或 `const` 常量），不能是变量。例如 `case 1:` 正确，`case x:`（x 是变量）错误。多个 case 不能有相同的值。

3. **break 语句**：用于跳出 switch 结构。执行完一个 case 的代码后，如果遇到 break，程序跳转到 switch 块之后继续执行。如果没有 break，程序会「穿透」到下一个 case，继续执行其代码。

4. **default 分支**：当表达式的值与所有 case 都不匹配时，执行 default 后的代码。default 是可选的，但建议总是写上，用于处理异常输入。

5. **花括号**：整个 switch 结构用一对 `{ }` 包裹，case 和 default 标签都在这个大括号内部。

让我们看一个最简单的例子——根据数字输出星期几：

```cpp
int day = 3;
switch (day) {
    case 1: cout << "星期一" << endl; break;
    case 2: cout << "星期二" << endl; break;
    case 3: cout << "星期三" << endl; break;
    case 4: cout << "星期四" << endl; break;
    case 5: cout << "星期五" << endl; break;
    case 6: cout << "星期六" << endl; break;
    case 7: cout << "星期日" << endl; break;
    default: cout << "输入错误" << endl; break;
}
```

输出：`星期三`

### 三、break 与穿透现象（Fall-through）

**穿透现象** 是指：当一个 case 块执行完毕后，如果没有遇到 break，程序不会跳出 switch，而是继续执行下一个 case 的代码，直到遇到 break 或 switch 结束。

这个特性既是 C++ 的设计选择，也成为初学者最容易出错的地方。来看一个「忘记 break」的例子：

```cpp
int x = 2;
switch (x) {
    case 1: cout << "A";
    case 2: cout << "B";
    case 3: cout << "C";
    default: cout << "D";
}
```

输出：`BCD`

**分析**：x == 2，程序跳转到 `case 2`，输出 B。因为没有 break，继续执行 `case 3`，输出 C；再继续执行 `default`，输出 D。最终输出 `BCD`，这显然不是我们期望的结果。

**穿透现象的合理利用**：虽然无意的穿透是 bug 的来源，但有意的穿透可以简化代码。当多个 case 需要执行相同的操作时，可以共享代码块：

```cpp
char grade = 'B';
switch (grade) {
    case 'A':
        cout << "优秀！" << endl;
        break;
    case 'B':
    case 'C':
        cout << "良好！" << endl;
        break;
    case 'D':
        cout << "及格。" << endl;
        break;
    case 'F':
        cout << "需要努力。" << endl;
        break;
    default:
        cout << "无效等级。" << endl;
}
```

这里 `case 'B':` 和 `case 'C':` 共享了同一段输出代码——「良好！」。这种写法简洁直观，是穿透现象的经典用法。注意 `case 'B':` 后面虽然没有 break，但它是**故意**让程序穿透到 `case 'C':` 的代码块的。

再看一个合并 case 的实用例子——判断月份的天数：

```cpp
int month = 2;
switch (month) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        cout << "31天" << endl;
        break;
    case 4: case 6: case 9: case 11:
        cout << "30天" << endl;
        break;
    case 2:
        cout << "28天或29天（闰年）" << endl;
        break;
    default:
        cout << "无效月份" << endl;
}
```

多个 case 标签可以连续写在同一个代码块前面，这是 switch-case 的一个重要编码技巧，可以大大减少重复代码。

### 四、default 分支的作用与位置

default 分支用于**兜底**——当 switch 表达式的值与所有 case 常量都不匹配时执行。虽然 default 可以放在 switch 块的任意位置（开头、中间、结尾），但习惯上放在**最后**。放在末尾时，default 的 break 可以省略（因为已经是最后一个），但为了代码一致性和可维护性，建议也写上 break。

**default 的典型用途：**

1. **错误处理**：当输入一个预期之外的值时给出提示。
2. **默认行为**：没有匹配到具体 case 时执行一个通用操作。

示例——简单的菜单系统：

```cpp
int choice;
cin >> choice;
switch (choice) {
    case 1: cout << "新建文件" << endl; break;
    case 2: cout << "打开文件" << endl; break;
    case 3: cout << "保存文件" << endl; break;
    case 4: cout << "退出程序" << endl; break;
    default: cout << "无效选项，请重新输入！" << endl; break;
}
```

### 五、switch 与 if-else 的选择策略

这是 CSP-J 考试中经常涉及的选择题考点。我们需要根据具体情况选择最合适的分支结构。

**使用 switch-case 的场景：**

- 判断条件是**单个变量的离散值**（如 1、2、3 或 'A'、'B'、'C'）
- 可能的取值数量较多（3 个以上）且每个值对应明确的操作
- 需要利用穿透现象合并多个 case
- 代码可读性是首要考虑

**使用 if-else 的场景：**

- 判断条件是**范围判断**（如 x > 0 && x < 100）
- 判断涉及**多个变量**的组合条件
- 判断条件是**浮点数**或**字符串**
- 分支数量很少（1~2 个）

**对比示例：**

```cpp
// 场景1：成绩等级——离散值，适合 switch
char grade;
cin >> grade;
switch (grade) {
    case 'A': cout << "90-100" << endl; break;
    case 'B': cout << "80-89" << endl; break;
    // ...
}

// 场景2：分数段——范围判断，必须用 if-else
int score;
cin >> score;
if (score >= 90) {
    cout << "A" << endl;
} else if (score >= 80) {
    cout << "B" << endl;
} else if (score >= 70) {
    cout << "C" << endl;
} else {
    cout << "D" << endl;
}
```

注意场景 2 不能直接用 switch 处理，因为 case 后面必须跟确定的值，不能写 `case score >= 90:`（语法错误），也不能给 0~100 每一个分数写一个 case（不现实）。此时 if-else 链是唯一合理的选择。

**一个重要的面试/考试考点**：switch 的表达式类型只能是整型、字符型或枚举类型。浮点数和字符串不能用于 switch。这是因为 switch 底层通过**跳转表**实现，要求 case 值是可以在编译期确定和比较的离散值。

### 六、嵌套 switch

switch 可以嵌套使用，即在一个 case 块内部再写一个 switch。这在处理「两级分类」的场景中很有用。

```cpp
int category = 1;  // 1: 电子产品, 2: 食品
int subType = 2;   // 电子产品的子类

switch (category) {
    case 1:  // 电子产品
        cout << "电子产品 -> ";
        switch (subType) {
            case 1: cout << "手机" << endl; break;
            case 2: cout << "电脑" << endl; break;
            case 3: cout << "平板" << endl; break;
            default: cout << "其他电子产品" << endl; break;
        }
        break;
    case 2:  // 食品
        cout << "食品 -> ";
        switch (subType) {
            case 1: cout << "水果" << endl; break;
            case 2: cout << "蔬菜" << endl; break;
            case 3: cout << "肉类" << endl; break;
            default: cout << "其他食品" << endl; break;
        }
        break;
    default:
        cout << "未知分类" << endl;
}
```

输出：`电子产品 -> 电脑`

嵌套 switch 需要注意：内层 switch 的 break 只跳出内层 switch，不会跳出外层 switch。外层的 break 必须单独写。

---

## 💻 代码模板

### 模板1：经典 switch-case 模板

```cpp
#include <iostream>
using namespace std;

int main() {
    int option;
    cin >> option;
    
    switch (option) {
        case 1:
            // 处理选项1
            cout << "你选择了选项1" << endl;
            break;
        case 2:
            // 处理选项2
            cout << "你选择了选项2" << endl;
            break;
        case 3:
            // 处理选项3
            cout << "你选择了选项3" << endl;
            break;
        default:
            // 处理无效输入
            cout << "无效选项！" << endl;
            break;
    }
    
    return 0;
}
```

### 模板2：合并 case 模板（利用穿透）

```cpp
#include <iostream>
using namespace std;

int main() {
    char ch;
    cin >> ch;
    
    switch (ch) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
        case 'A':
        case 'E':
        case 'I':
        case 'O':
        case 'U':
            cout << "元音字母" << endl;
            break;
        default:
            cout << "辅音字母" << endl;
            break;
    }
    
    return 0;
}
```

---

## ⚠️ 易错点

### 易错点1：忘记写 break（最常见的错误）

**错误代码：**
```cpp
switch (x) {
    case 1: cout << "一";
    case 2: cout << "二";
    case 3: cout << "三";
}
// 当 x==1 时，输出 "一二三"，而不是 "一"
```

**避免方法**：每写完一个 case 的代码块，**立刻**写 break，养成肌肉记忆。写完代码后，手动在脑中模拟每个分支的执行流程，检查是否会意外穿透。

### 易错点2：switch 表达式类型错误

**错误代码：**
```cpp
double x = 3.14;
switch (x) {  // 编译错误！double 不能用于 switch
    case 3.14: cout << "pi"; break;
}

string s = "hello";
switch (s) {  // 编译错误！string 不能用于 switch
    case "hello": cout << "world"; break;
}
```

**避免方法**：记住「switch 只接收整型、字符型、枚举型」。遇到浮点数判断，用 if-else；遇到字符串判断，用 if-else 或 map。这是编译期错误，编译器会明确报错，不必太担心；但在选择题中可能以「以下代码能否编译通过」的形式出现。

### 易错点3：case 后使用了变量

**错误代码：**
```cpp
int a = 5, b = 10;
switch (a) {
    case b:  // 编译错误！b 是变量，不是编译期常量
        cout << "a == b" << endl;
        break;
}
```

**避免方法**：case 后面只能跟**字面常量**（如 `1`、`'A'`）或 **const 常量**。如果需要与变量比较，只能用 if-else。

### 易错点4：多个 case 值相同

**错误代码：**
```cpp
switch (x) {
    case 1: cout << "A"; break;
    case 1: cout << "B"; break;  // 编译错误！重复的 case 值
}
```

**避免方法**：每个 case 的值必须唯一。这是编译期错误，编译器会提醒。

---

## 📝 真题精练

### 真题1：简单计算器

**题目描述：**

编写一个简单的整数计算器程序。输入格式为：`a op b`，其中 a 和 b 是两个整数，op 是一个字符，表示运算符（`+`、`-`、`*`、`/`）。程序需要根据运算符执行相应的运算并输出结果。

对于除法运算，如果 b 为 0，输出 `"Error: Division by zero"`。如果运算符不是 `+` `-` `*` `/` 之一，输出 `"Error: Invalid operator"`。

**输入格式：**

一行，包含一个整数 a、一个字符 op、一个整数 b，中间用空格分隔。

**输出格式：**

一行，输出运算结果（整数）或错误信息。

**样例输入1：**
```
10 + 5
```

**样例输出1：**
```
15
```

**样例输入2：**
```
10 / 0
```

**样例输出2：**
```
Error: Division by zero
```

**样例输入3：**
```
10 ^ 5
```

**样例输出3：**
```
Error: Invalid operator
```

**数据范围：**

|a|, |b| <= 10000，保证输入合法。

**AC 代码：**

```cpp
#include <iostream>
using namespace std;

int main() {
    int a, b;
    char op;
    cin >> a >> op >> b;
    
    switch (op) {
        case '+':
            cout << a + b << endl;
            break;
        case '-':
            cout << a - b << endl;
            break;
        case '*':
            cout << a * b << endl;
            break;
        case '/':
            if (b == 0) {
                cout << "Error: Division by zero" << endl;
            } else {
                cout << a / b << endl;
            }
            break;
        default:
            cout << "Error: Invalid operator" << endl;
            break;
    }
    
    return 0;
}
```

**考点解析：**

1. switch 表达式使用 `char` 类型，根据运算符字符分发到不同 case。
2. 除法需要在 case 内部用 if 进行除零判断——switch 处理不了范围/条件判断。
3. default 分支用于处理非法运算符。
4. 每个 case 都写了 break，避免无意穿透。

---

### 真题2：成绩等级转换

**题目描述：**

输入一个字符表示成绩等级（`A`、`B`、`C`、`D`、`F`，区分大小写），请输出对应的分数范围和评语：

- A/a: `90-100 优秀`
- B/b: `80-89 良好`
- C/c: `70-79 中等`
- D/d: `60-69 及格`
- F/f: `0-59 需要努力`

如果输入其他字符，输出 `无效等级`。

**输入格式：**

一行，一个字符。

**输出格式：**

一行，对应的分数范围和评语，用空格分隔。

**样例输入1：**
```
A
```

**样例输出1：**
```
90-100 优秀
```

**样例输入2：**
```
c
```

**样例输出2：**
```
70-79 中等
```

**样例输入3：**
```
E
```

**样例输出3：**
```
无效等级
```

**AC 代码：**

```cpp
#include <iostream>
using namespace std;

int main() {
    char grade;
    cin >> grade;
    
    switch (grade) {
        case 'A':
        case 'a':
            cout << "90-100 优秀" << endl;
            break;
        case 'B':
        case 'b':
            cout << "80-89 良好" << endl;
            break;
        case 'C':
        case 'c':
            cout << "70-79 中等" << endl;
            break;
        case 'D':
        case 'd':
            cout << "60-69 及格" << endl;
            break;
        case 'F':
        case 'f':
            cout << "0-59 需要努力" << endl;
            break;
        default:
            cout << "无效等级" << endl;
            break;
    }
    
    return 0;
}
```

**考点解析：**

1. 利用穿透现象合并大小写——`case 'A':` 和 `case 'a':` 共享同一段代码，处理大小写不敏感输入。
2. 这是合并 case 的经典应用场景，代码比 if-else 链更简洁清晰。
3. default 分支处理无效输入，体现了程序的健壮性。

---

## 🎯 本课小结

### 核心知识点回顾

| 知识点 | 要点 |
|--------|------|
| switch 语法 | `switch(整型/字符型表达式)` + `case 常量:` + `break;` |
| break 的作用 | 跳出 switch 结构，防止穿透 |
| 穿透现象 | 无 break 时继续执行下一个 case，可合理用于合并 case |
| default 分支 | 兜底处理，当所有 case 都不匹配时执行 |
| switch vs if-else | 离散值用 switch，范围判断用 if-else |
| 表达式限制 | 只能是整型、字符型、枚举型，不能是浮点数或字符串 |
| 嵌套 switch | 内层 break 只跳出内层，外层需单独 break |

### 考试建议

1. **读代码题**高频考点：给一段 switch 代码，问输出结果。核心是判断是否有 break、是否发生穿透。
2. **选择题**高频考点：判断某场景用 switch 还是 if-else。
3. **编程题**高频考点：简单计算器、菜单选择、成绩/日期等分类转换。
4. 写 switch 代码时，建议先写出完整框架（switch + 所有 case + default），再填充各分支代码——避免遗漏 case。
5. 每写完一个 case 就写 break，养成习惯，杜绝穿透 bug。
