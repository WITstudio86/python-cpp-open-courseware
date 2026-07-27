# 第8课：if-else 分支结构

## 🎯 考纲要求

| 考点 | 掌握程度 | 说明 |
|------|----------|------|
| 单分支 `if` | **必会** | 条件成立才执行语句块 |
| 双分支 `if-else` | **必会** | 成立走 if，否则走 else |
| 多分支 `if-else if-else` | **必会** | 自上而下匹配，命中即停 |
| 嵌套 if | **必会** | if/else 内部再写 if |
| 悬空 else（dangling else） | **必会** | else 与最近未配对 if 匹配 |
| 条件表达式 | **必会** | 关系/逻辑运算、非零为真 |
| 条件顺序与边界 | **必会** | 从严到宽，注意等于边界 |
| 常见陷阱 | **必会** | 分号、`=`/`==`、浮点比较、优先级 |

---

## 📖 知识精讲

### 一、为什么需要分支结构？

顺序结构只能“一条道走到黑”。现实问题却经常是：

- 分数 ≥ 60 输出“及格”，否则“不及格”；
- 根据年龄判断票价；
- 判断闰年、奇偶、三角形类型；
- 多档成绩等级 A/B/C/D/E。

**分支结构**让程序根据条件选择不同路径执行。C++ 中最基础、也是 CSP-J 最高频的分支语法就是 `if-else`。

可以把分支理解成十字路口：

```
        条件？
       /     \
    true     false
     |         |
   路径A     路径B
```

### 二、单分支 if

#### 1. 语法

```cpp
if (条件表达式) {
    语句块;   // 条件为 true（非 0）时执行
}
// 无论是否执行语句块，都会继续往后走
```

#### 2. 执行流程

1. 计算括号内条件表达式；
2. 若结果为真（非 0）→ 执行花括号内语句；
3. 若结果为假（0）→ 跳过花括号；
4. 继续执行 if 结构后面的代码。

```cpp
int score = 85;
if (score >= 60) {
    cout << "及格" << endl;
}
cout << "程序继续" << endl;
```

输出：

```
及格
程序继续
```

若 `score = 50`，则只输出 `程序继续`。

#### 3. 何时可省略花括号？

当 if 后面**只有一条语句**时，语法上可省略 `{}`：

```cpp
if (score >= 60) cout << "及格" << endl;
```

但考试与工程中**强烈建议始终写花括号**。原因：

- 以后加第二行代码时，很容易忘记补 `{}`，造成逻辑错误；
- 与悬空 else 问题强相关。

### 三、双分支 if-else

#### 1. 语法

```cpp
if (条件表达式) {
    语句块1;   // 条件为真
} else {
    语句块2;   // 条件为假
}
```

#### 2. 特点

- if 与 else **二选一**，不会都执行，也不会都不执行（在条件可计算的前提下）；
- else 不能单独出现，必须依附某个 if。

```cpp
int n;
cin >> n;
if (n % 2 == 0) {
    cout << "偶数" << endl;
} else {
    cout << "奇数" << endl;
}
```

#### 3. 流程图思维

```
读入 n
  |
n%2==0 ?
 /      \
是       否
 |        |
偶数     奇数
 \        /
  汇合继续
```

### 四、多分支 if-else if-else

#### 1. 语法

```cpp
if (条件1) {
    语句块1;
} else if (条件2) {
    语句块2;
} else if (条件3) {
    语句块3;
} else {
    语句块4;   // 以上全假
}
```

#### 2. 核心规则：命中即停

系统**从上到下**检查：

- 找到第一个为真的条件 → 执行对应语句块 → **结束整个 if-else if 链**；
- 后面即使还有为真的条件，也**不会再判断**。

这是多分支最重要的考试点。

#### 3. 成绩等级（经典模板）

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

对 `score = 85`：

1. `85 >= 90`？假；
2. `85 >= 80`？真 → 输出 B，停止。

#### 4. 条件必须“从严到宽”

**错误示例：**

```cpp
if (score >= 60) {
    cout << "及格" << endl;
} else if (score >= 80) {
    cout << "良好" << endl;   // 永远到不了（当 score>=80 时已被上面截走）
} else if (score >= 90) {
    cout << "优秀" << endl;   // 永远到不了
}
```

输入 85：第一个条件就真，输出“及格”。  
**正确顺序**：90 → 80 → 70 → 60 → 其它。

#### 5. 区间判断的两种写法

**写法 A：依赖 else if 的互斥性（推荐）**

```cpp
if (score >= 90) { ... }
else if (score >= 80) { ... }  // 隐含 score < 90
```

**写法 B：显式写区间**

```cpp
if (score >= 90 && score <= 100) { ... }
else if (score >= 80 && score < 90) { ... }
```

写法 A 更简洁；写法 B 在条件顺序打乱时更安全，但更冗长。

### 五、嵌套 if

在 if 或 else 的语句块中再写 if，称为嵌套。

#### 1. 三数求最大值

```cpp
int a, b, c;
cin >> a >> b >> c;

int maxVal;
if (a >= b) {
    if (a >= c) maxVal = a;
    else maxVal = c;
} else {
    if (b >= c) maxVal = b;
    else maxVal = c;
}
cout << maxVal << endl;
```

#### 2. 嵌套 vs 逻辑运算符

很多嵌套可以“拍平”：

```cpp
// 嵌套
if (x > 0) {
    if (y > 0) {
        cout << "第一象限\n";
    }
}

// 等价拍平
if (x > 0 && y > 0) {
    cout << "第一象限\n";
}
```

但并非总是值得拍平：当内外层有不同 else 处理时，嵌套结构更清晰。

#### 3. 嵌套层次建议

- 考试代码嵌套尽量 ≤ 3 层；
- 过深嵌套可读性差，易出现悬空 else；
- 可用 early continue/return（函数中）或重新组织条件降低嵌套。

### 六、悬空 else 问题（考试重点！）

#### 1. 规则（必须背）

> **else 总是与“上面最近的、尚未配对的 if”匹配**（就近原则）。

与缩进无关！C++ 编译器不看缩进，只看语法结构。

#### 2. 经典陷阱

```cpp
int x = 5, y = 0;
if (x > 0)
    if (y > 0)
        cout << "A" << endl;
else
    cout << "B" << endl;
```

很多人凭缩进以为 else 匹配外层 `if (x > 0)`，实际上：

```text
if (x > 0)
    if (y > 0)
        cout << "A";
    else
        cout << "B";   // 配对内层 if (y > 0)
```

分析：

- `x>0` 为真，进入外层；
- `y>0` 为假，执行内层 else → 输出 **B**。

#### 3. 再改一组数据

```cpp
int x = -1, y = 0;
if (x > 0)
    if (y > 0)
        cout << "A";
    else
        cout << "B";
// x>0 为假，整个内层 if-else 被跳过 → 无输出
```

#### 4. 正确做法：永远加花括号

若希望 else 匹配外层：

```cpp
if (x > 0) {
    if (y > 0) {
        cout << "A" << endl;
    }
} else {
    cout << "B" << endl;  // 明确匹配外层
}
```

若确认 else 匹配内层，也建议写清楚：

```cpp
if (x > 0) {
    if (y > 0) {
        cout << "A" << endl;
    } else {
        cout << "B" << endl;
    }
}
```

#### 5. 编译器警告

某些写法会触发 `-Wdangling-else` 警告，提醒你“这可能不是你想要的配对”。  
**对策**：加 `{}`，警告消失，语义清晰。

### 七、条件表达式深入

#### 1. “真”与“假”在 C++ 中的含义

- 条件表达式最终按是否为 **0** 判断；
- 0 → 假；非 0 → 真；
- `bool`、关系运算结果、逻辑运算结果都可直接放进 if。

```cpp
int a = 3;
if (a)        // a != 0，为真
if (!a)       // a == 0 时为真
if (a % 2)    // 奇数时为真（余数 1）
if (a % 2 == 0) // 偶数
```

#### 2. 关系运算符复习

| 运算符 | 含义 | 注意 |
|--------|------|------|
| `>` `>=` `<` `<=` | 比较大小 | 结果 bool |
| `==` | 相等 | 别写成 `=` |
| `!=` | 不等 | |

#### 3. 逻辑运算符与短路

| 运算符 | 含义 | 短路 |
|--------|------|------|
| `&&` | 与 | 左假则右不算 |
| `\|\|` | 或 | 左真则右不算 |
| `!` | 非 | 单目 |

```cpp
// 安全：先判除数非 0
if (b != 0 && a / b > 1) { ... }

// 安全：先判下标合法
if (i >= 0 && i < n && arr[i] > 0) { ... }
```

#### 4. 复合条件的优先级

`&&` 优先于 `||`：

```cpp
if (a > 0 || b > 0 && c > 0);
// 等价于
if (a > 0 || (b > 0 && c > 0));
```

不确定时**加括号**，既防错也利于读程。

#### 5. 闰年判断（复合条件经典）

规则：能被 4 整除且不能被 100 整除，或能被 400 整除。

```cpp
if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
    cout << "闰年" << endl;
} else {
    cout << "平年" << endl;
}
```

测试点：`2000` 闰，`1900` 平，`2024` 闰，`2023` 平。

#### 6. 三目运算符（分支缩写）

```cpp
int maxv = (a > b) ? a : b;   // 等价 if-else 赋值
```

大段逻辑考试中仍建议用 if-else。注意边界要手测（成绩 0/59/60/90/100；闰年 1900/2000/2024）。  
两个**独立 if** 可能都执行；需要“只取一档”时必须用 `else if`。  
范围判断用 if-else；离散常量（星期 1~7）更适合下节课的 switch。

---

## 💻 代码模板

### 模板 1：多分支成绩等级

```cpp
#include <iostream>
using namespace std;

int main() {
    int score;
    cin >> score;

    // 条件从严格到宽松
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

### 模板 2：嵌套 if 求三数最值 + 排序

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int a, b, c;
    cin >> a >> b >> c;

    // 嵌套 if 求最大值
    int maxVal;
    if (a >= b) {
        if (a >= c) maxVal = a;
        else maxVal = c;
    } else {
        if (b >= c) maxVal = b;
        else maxVal = c;
    }
    cout << "max = " << maxVal << endl;

    // 简洁写法
    cout << "max2 = " << max({a, b, c}) << endl;

    // 三数升序（冒泡思想的三步交换）
    if (a > b) swap(a, b);
    if (a > c) swap(a, c);
    if (b > c) swap(b, c);
    cout << a << " " << b << " " << c << endl;

    return 0;
}
```

### 模板 3：悬空 else 安全写法对照

```cpp
#include <iostream>
using namespace std;

int main() {
    int x, y;
    cin >> x >> y;

    // 危险：依赖就近匹配（不推荐）
    // if (x > 0)
    //     if (y > 0) cout << "A\n";
    // else cout << "B\n";

    // 安全：else 明确匹配内层
    if (x > 0) {
        if (y > 0) {
            cout << "A" << endl;
        } else {
            cout << "B" << endl;
        }
    }

    // 安全：else 明确匹配外层
    if (x > 0) {
        if (y > 0) {
            cout << "A" << endl;
        }
    } else {
        cout << "B" << endl;
    }

    return 0;
}
```

---

## ⚠️ 易错点

1. **if 后面多写分号**：`if (a > 0); { ... }` 中分号是空语句，花括号无条件执行。  
2. **`=` 与 `==` 混用**：`if (a = 5)` 是赋值且常为真；比较必须 `==`。  
3. **悬空 else**：else 配最近 if，与缩进无关——**永远写 `{}`**。  
4. **多分支从宽到严**：先 `>=60` 再 `>=90`，高分永远到不了后面——**从严到宽**。  
5. **优先级**：`a || b && c` 等于 `a || (b && c)`，不确定就加括号。  
6. **浮点 `==`**：`0.1+0.2 == 0.3` 可能为假，用 `fabs(x-0.3) < 1e-9`。  
7. **并列 if 重复输出**：只取一档时用 `else if`，不要多个独立 if。  
8. **缺少 else 兜底**：菜单/等级转换建议写最终 else 防漏网。

---

## 📝 真题精练

### 题目1：悬空 else 读程

**题目描述**：阅读程序，写出输出。

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

1. 虽然 else 写在与外层 if 对齐的缩进上，但语法上匹配**内层** `if (y > 0)`；
2. `x > 0` 为真，进入外层；
3. `y > 0` 为假，执行内层 else；
4. 输出 `B`。

**答案**：`B`

**AC 验证 / 对照正确写法：**

```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 5, y = 0;

    // 原题语义（悬空 else → 匹配内层）
    if (x > 0)
        if (y > 0)
            cout << "A" << endl;
        else
            cout << "B" << endl;  // 输出 B

    // 若意图是“x<=0 时输出 B”，应写：
    if (x > 0) {
        if (y > 0) {
            cout << "A" << endl;
        }
    } else {
        cout << "B" << endl;
    }

    return 0;
}
```

**考点**：悬空 else 就近匹配；花括号改变配对。

---

### 题目2：多分支条件顺序

**题目描述**：输入为 `85` 时，下列程序输出什么？

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

1. 输入 85；
2. 第一个条件 `85 >= 60` 为真；
3. 输出“及格”，整条链结束；
4. 后面的 80、90 分支不可达。

**答案**：`及格`

**正确写法（AC）：**

```cpp
#include <iostream>
using namespace std;

int main() {
    int score;
    cin >> score;

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

对输入 85，正确输出应为：`良好`。

**考点**：else if 命中即停；条件顺序从严到宽。

---

### 题目3（巩固）：闰年判断编程

**题目描述**：输入年份 `year`，若是闰年输出 `Y`，否则输出 `N`。

**样例：**

```
2000
```

```
Y
```

```
1900
```

```
N
```

**AC 代码：**

```cpp
#include <iostream>
using namespace std;

int main() {
    int year;
    cin >> year;

    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        cout << "Y" << endl;
    } else {
        cout << "N" << endl;
    }
    return 0;
}
```

**考点**：复合逻辑条件、括号优先级、`&&` / `||` 组合。

---

### 题目4（巩固）：分段函数

**题目**：\(y=x\ (x<1);\ 2x-1\ (1\le x<10);\ 3x-11\ (x\ge 10)\)，输入整数 x 输出 y。

**AC 代码：**

```cpp
#include <iostream>
using namespace std;
int main() {
    int x; cin >> x;
    int y;
    if (x < 1) y = x;
    else if (x < 10) y = 2 * x - 1;
    else y = 3 * x - 11;
    cout << y << endl;
    return 0;
}
```

**考点**：多分支区间划分与边界归属。

---

## 🎯 本课小结

### 核心知识点回顾

| 知识点 | 要点 |
|--------|------|
| 单分支 if | 条件真才执行，假则跳过 |
| 双分支 if-else | 二选一，覆盖真假两种路径 |
| 多分支 else if | 自上而下，命中即停 |
| 条件顺序 | 范围判断必须从严到宽 |
| 嵌套 if | 处理更细条件；注意层次与括号 |
| 悬空 else | else 配最近 if；与缩进无关 |
| 条件表达式 | 非 0 为真；注意 `&&` `\|\|` 优先级与短路 |
| 防御性写法 | 始终 `{}`；慎用 `=`；浮点近似比较 |

### 考试建议

1. 读程先找 if 配对；无括号嵌套先重画，再用就近原则；始终加 `{}`。  
2. 编程先列区间表再写条件，并手测边界。  
3. 下一课 `switch-case` 适合离散常量；范围判断仍用 if-else。

### 课后自测清单

- [ ] 能默写单/双/多分支，说明 else if「命中即停」  
- [ ] 能分析悬空 else；会写成绩等级、闰年、分段函数  
- [ ] 能避开分号、`=`/`==`、浮点比较三大坑
