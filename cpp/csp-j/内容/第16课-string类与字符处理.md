# 第16课：string 类与字符处理

## 🎯 考纲要求

- **string 类**：掌握 `string` 类型的定义、输入（`getline`）、拼接（`+`）、比较（`==`）、长度（`.length() / .size()`）、子串（`.substr()`）、查找（`.find()`）
- **字符判断函数**：熟练使用 `isdigit`、`isalpha`、`islower`、`isupper`、`tolower`、`toupper` 进行字符分类与转换
- **string 与 C 风格字符串的区别**：理解 string 类的安全性和便捷性优势

---

## 📖 知识精讲

### 一、为什么要用 string 类？

C 风格字符串虽然底层高效，但存在三大痛点：
1. **手动管理 `'\0'`**：忘记预留空间或忘记添加 `'\0'` 会导致严重 bug。
2. **容量固定**：声明后数组大小不可变，拼接操作前必须预先估算容量。
3. **操作繁琐**：不能直接用 `=` 赋值、`+` 拼接、`==` 比较，必须调用 `strcpy`、`strcat`、`strcmp`。

C++ 标准库提供的 **`string` 类**完美解决了这些问题：
- 自动管理内存，无需关心 `'\0'` 和容量。
- 支持 `=`、`+`、`+=`、`==`、`!=`、`>`、`<` 等直观运算符。
- 提供丰富的成员函数，操作更便捷。

```cpp
#include <string>
using namespace std;

// C 风格字符串的繁琐操作
char a[100] = "hello";
char b[100];
strcpy(b, a);           // 拷贝
strcat(b, " world");    // 拼接
if (strcmp(a, b) == 0)  // 比较

// string 类的简洁操作
string s1 = "hello";
string s2 = s1;         // 直接赋值
s2 += " world";         // 拼接
if (s1 == s2)           // 直接比较
```

### 二、string 的定义与初始化

`string` 类支持多种初始化方式，灵活方便：

```cpp
#include <string>
using namespace std;

string s1;                    // 空字符串 ""
string s2 = "hello";          // 用字符串字面量初始化
string s3("world");           // 用构造函数初始化
string s4 = s2;               // 拷贝初始化
string s5(5, 'a');            // 重复字符："aaaaa"
string s6 = s2 + " " + s3;    // 拼接初始化："hello world"
```

**注意**：`string` 是 C++ 标准库类型，需要 `#include <string>`。它与 C 风格字符串（`char[]`）是不同的类型，但可以通过 `.c_str()` 方法转换为 C 风格字符串。

### 三、string 的输入

`string` 的输入方式与 `char` 数组类似，但更安全（自动调整大小）：

```cpp
string s;

// 方式1：cin >> s —— 遇到空格、Tab、换行停止
cin >> s;          // 输入 "hello world" → s = "hello"

// 方式2：getline(cin, s) —— 读取整行，含空格
getline(cin, s);   // 输入 "hello world" → s = "hello world"
```

> **重要提醒**：`cin >>` 和 `getline` 混用时会有**换行符残留**问题。

```cpp
int n;
cin >> n;            // 用户输入 "3" 然后回车，缓冲区中留下了 '\n'
// getline(cin, s);  // 错误！会立即读到空行（残留的 '\n'）
cin.ignore();        // ✅ 先用 ignore() 清除换行符
getline(cin, s);     // 正确读取下一行
```

### 四、string 的基本操作

#### 1. 拼接：`+` 和 `+=`

`string` 支持用 `+` 运算符直接拼接，`+=` 追加，非常直观：

```cpp
string s1 = "Hello";
string s2 = "World";
string s3 = s1 + " " + s2;   // s3 = "Hello World"
s1 += " CSP-J";               // s1 = "Hello CSP-J"
```

`+` 运算符两侧至少有一个是 `string` 类型。两个 C 风格字符串字面量不能直接用 `+` 拼接（例如 `"a" + "b"` 是错误的，因为字面量是 `const char*`，不能相加）。

#### 2. 比较：`==`、`!=`、`>`、`<`、`>=`、`<=`

`string` 重载了所有比较运算符，按**字典序**逐字符比较：

```cpp
string a = "abc", b = "abd";
if (a == b) cout << "相等";
if (a < b)  cout << "a 小于 b";   // true，因为 'c' < 'd'
if (a != b) cout << "不相等";
```

比较规则与 `strcmp` 一致，但语义更清晰——不需要记住返回值的含义。

#### 3. 长度：`.length()` 和 `.size()`

两者完全等价，返回字符串中字符的个数：

```cpp
string s = "Hello";
cout << s.length();  // 5
cout << s.size();    // 5（与 length() 相同）
```

#### 4. 访问单个字符：`[]`

可以用下标直接访问或修改某个字符：

```cpp
string s = "abc";
cout << s[0];    // 'a'
s[1] = 'x';      // s 变为 "axc"
```

#### 5. 子串：`.substr(pos, len)`

从位置 `pos` 开始，取 `len` 个字符：

```cpp
string s = "Hello World";
cout << s.substr(0, 5);   // "Hello"（从0开始，取5个）
cout << s.substr(6, 5);   // "World"（从6开始，取5个）
cout << s.substr(6);      // "World"（省略len，取到末尾）
```

> **易错提醒**：`.substr(pos, len)` 的第二个参数是**长度**，不是结束位置！`s.substr(2, 3)` 表示从索引 2 开始取 3 个字符（索引 2、3、4），而不是取到索引 3。

#### 6. 查找：`.find(str)`

返回子串**第一次出现**的起始索引。如果没找到，返回 `string::npos`（一个特殊常量，通常定义为最大的 `size_t` 值）：

```cpp
string s = "Hello World";
size_t pos = s.find("World");   // pos = 6
size_t pos2 = s.find("abc");    // pos2 = string::npos

if (s.find("World") != string::npos) {
    cout << "找到了！" << endl;
}
```

> **易错提醒**：找不到时返回 `string::npos`，而非 `-1`。虽然在某些实现中 `string::npos == (size_t)-1`，但从语义上应该使用 `string::npos` 进行比较。

### 五、字符判断函数

使用这些函数需要包含 `#include <cctype>`（C++ 风格，推荐）或 `#include <ctype.h>`（C 风格）。

| 函数 | 作用 | 示例 |
|------|------|------|
| `isdigit(c)` | 判断是否为数字 `'0'~'9'` | `isdigit('5')` → true |
| `isalpha(c)` | 判断是否为字母 `'a'~'z'` 或 `'A'~'Z'` | `isalpha('A')` → true |
| `islower(c)` | 判断是否为小写字母 | `islower('a')` → true |
| `isupper(c)` | 判断是否为大写字母 | `isupper('Z')` → true |
| `isalnum(c)` | 判断是否为字母或数字 | `isalnum('9')` → true |
| `isspace(c)` | 判断是否为空白字符（空格、Tab、换行等） | `isspace(' ')` → true |
| `tolower(c)` | 转为小写字母 | `tolower('A')` → 'a' |
| `toupper(c)` | 转为大写字母 | `toupper('a')` → 'A' |

这些函数的参数和返回值都是 `int` 类型（可以传入 `char`，会自动转换）。返回值非 0 表示 true，0 表示 false。

```cpp
#include <cctype>

char c = 'A';
if (isupper(c)) {
    cout << (char)tolower(c);   // 输出 'a'
}
```

### 六、综合应用示例：字符统计

统计一个字符串中各类字符的数量：

```cpp
string s;
getline(cin, s);
int digits = 0, letters = 0, upper = 0, lower = 0;

for (char c : s) {
    if (isdigit(c)) digits++;
    if (isalpha(c)) letters++;
    if (isupper(c)) upper++;
    if (islower(c)) lower++;
}

cout << "数字: " << digits << endl;
cout << "字母: " << letters << endl;
cout << "大写: " << upper << endl;
cout << "小写: " << lower << endl;
```

---

## 💻 代码模板

### string 基本操作模板

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    // 定义与初始化
    string s1 = "Hello";
    string s2("World");
    string s3 = s1 + " " + s2;   // 拼接
    
    // 输出
    cout << s3 << endl;           // "Hello World"
    cout << "长度: " << s3.length() << endl;  // 11
    
    // 子串
    cout << s3.substr(0, 5) << endl;  // "Hello"
    
    // 查找
    size_t pos = s3.find("World");
    if (pos != string::npos) {
        cout << "找到 'World'，位置: " << pos << endl;
    }
    
    return 0;
}
```

### 字符统计模板

```cpp
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {
    string s;
    getline(cin, s);
    
    int digit_cnt = 0, alpha_cnt = 0;
    for (char c : s) {
        if (isdigit(c)) digit_cnt++;
        if (isalpha(c)) alpha_cnt++;
    }
    
    cout << digit_cnt << " " << alpha_cnt << endl;
    return 0;
}
```

### 子串查找模板

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string text, pattern;
    getline(cin, text);
    getline(cin, pattern);
    
    size_t pos = text.find(pattern);
    if (pos != string::npos) {
        cout << pos << endl;  // 输出第一次出现的位置
    } else {
        cout << "-1" << endl;
    }
    return 0;
}
```

---

## ⚠️ 易错点

1. **`cin >>` 与 `getline` 混用时缓冲区残留换行符**
   - `cin >> n` 后缓冲区留下 `'\n'`，紧接着的 `getline(cin, s)` 会读到空串。
   - **解决方法**：在 `cin >>` 后加 `cin.ignore()` 清除残留换行符。

2. **`.find()` 找不到时返回 `string::npos`，而非 `-1`**
   - 应写 `if (s.find(x) != string::npos)`，不要写 `if (s.find(x) == -1)`（虽然在某些编译器上碰巧正确，但语义不对）。

3. **`.substr(pos, len)` 的第二参数是长度，不是结束索引**
   - `s.substr(2, 3)` 取索引 2、3、4 的字符（共 3 个），而非取索引 2 到 3。
   - 如果 `len` 超出范围，实际只取到字符串末尾，不会报错。

4. **字符判断函数参数必须是 `unsigned char` 或 `EOF`**
   - 如果 `char` 是有符号类型且值为负数（如扩展 ASCII），传入 `isxxx` 函数会导致未定义行为。
   - 安全用法：`isdigit(static_cast<unsigned char>(c))`，但在处理 ASCII 文本时通常不会出问题。

5. **两个 C 风格字符串字面量不能直接用 `+` 拼接**
   - 错误：`string s = "Hello" + " World";`（两个 `const char*` 不能相加）
   - 正确：`string s = string("Hello") + " World";` 或 `string s = "Hello" + string(" World");`，至少有一个操作数是 `string`。

6. **`.c_str()` 返回的指针在下一次修改 string 后可能失效**
   - 不要长期保存 `.c_str()` 的返回值，每次需要时再调用。

---

## 📝 真题精练

### 真题1：string 操作结果判断

**题目描述**：
给定一系列 string 操作，判断操作后字符串的内容和长度。

**问题**：阅读以下代码，输出最终结果。

```cpp
string s = "I love CSP-J";
cout << s.length() << endl;                        // Q1: 输出？
cout << s.substr(7, 5) << endl;                    // Q2: 输出？
cout << s.find("CSP") << endl;                     // Q3: 输出？
s += "!";
cout << s << endl;                                  // Q4: 输出？
cout << (s.find("Python") == string::npos) << endl; // Q5: 输出？
```

**输入格式**：无输入。

**输出格式**：按顺序输出 5 个问题的答案。

**AC 代码**：

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s = "I love CSP-J";

    // Q1: 字符串长度（空格也算一个字符）
    cout << s.length() << endl;  // 12

    // Q2: 从索引7开始取5个字符
    // 索引: 0=I,1= ,2=l,3=o,4=v,5=e,6= ,7=C,8=S,9=P,10=-,11=J
    cout << s.substr(7, 5) << endl;  // "CSP-J"

    // Q3: 查找 "CSP" 第一次出现的位置
    cout << s.find("CSP") << endl;  // 7

    // Q4: 追加 "!"
    s += "!";
    cout << s << endl;  // "I love CSP-J!"

    // Q5: 查找不存在的子串，返回 string::npos
    // string::npos == string::npos 为 true，输出 1
    cout << (s.find("Python") == string::npos) << endl;  // 1

    return 0;
}
```

**代码解析**：
- `.length()` 统计所有字符，空格也计入。
- `.substr(7, 5)` 从索引 7（即字符 'C'）开始取 5 个字符 "CSP-J"。
- `.find("CSP")` 返回子串首字符的索引 7。
- `+=` 直接在原字符串末尾追加字符。
- `string::npos` 是一个特殊常量，`.find()` 找不到时返回它。

---

### 真题2：字符统计与大小写转换

**题目描述**：
给定一个长度不超过 1000 的字符串（可能包含空格、数字、大小写字母和其他字符），请完成以下任务：
1. 统计其中大写字母、小写字母、数字各有多少个。
2. 将字符串中的所有大写字母转为小写，所有小写字母转为大写，其他字符不变，输出转换后的字符串。

**输入格式**：
一行，一个字符串，长度不超过 1000。

**输出格式**：
第一行：三个整数，分别表示大写字母数、小写字母数、数字数，用空格分隔。
第二行：大小写翻转后的字符串。

**样例输入**：
```
Hello World 123!
```

**样例输出**：
```
2 8 3
hELLO wORLD 123!
```

**AC 代码**：

```cpp
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {
    string s;
    getline(cin, s);

    int upper_cnt = 0, lower_cnt = 0, digit_cnt = 0;

    // 统计各类字符数量，同时进行大小写翻转
    for (char &c : s) {
        if (isupper(c)) {
            upper_cnt++;
            c = tolower(c);    // 大写转小写
        } else if (islower(c)) {
            lower_cnt++;
            c = toupper(c);    // 小写转大写
        } else if (isdigit(c)) {
            digit_cnt++;
            // 数字不转换
        }
        // 其他字符保持不变
    }

    cout << upper_cnt << " " << lower_cnt << " " << digit_cnt << endl;
    cout << s << endl;

    return 0;
}
```

**代码解析**：
1. 使用 `getline` 读取包含空格的整行。
2. `for (char &c : s)` 使用引用 `&c`，可以直接修改字符串中的字符。
3. 用 `isupper` / `islower` / `isdigit` 分类统计，同时用 `tolower` / `toupper` 进行转换。
4. 注意 else if 的顺序：先判断大写和小写（两者都是字母），用 `else if` 确保一个字符只进入一个分支。

---

## 🎯 本课小结

1. **string 类的优势**：自动内存管理、直观的运算符重载（`+`、`+=`、`==` 等）、丰富的成员函数，比 C 风格字符串更安全、更便捷。
2. **string 的定义与初始化**：多种构造方式，灵活方便；`+` 拼接至少需要一个 `string` 类型的操作数。
3. **输入方式**：`cin >> s` 遇空格停止；`getline(cin, s)` 读整行。混用时注意用 `cin.ignore()` 清除换行符。
4. **核心操作**：`.length() / .size()` 获取长度；`.substr(pos, len)` 取子串（len 是长度）；`.find(str)` 查找子串（返回位置或 `string::npos`）。
5. **字符判断函数**：`isdigit` / `isalpha` / `islower` / `isupper` / `tolower` / `toupper`，需 `#include <cctype>`，参数和返回值均为 `int` 类型。
6. **string 与 C 风格字符串**：CSP-J 考试中两者都可能出现，要根据题目要求灵活选用。字符串操作频繁时优先使用 `string` 类。
