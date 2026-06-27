# 第29节：def —— 定义自己的函数

## 🎯 教学目标
- 学生能够掌握 `def` 关键字定义函数的完整语法
- 学生能够理解函数名命名规则（跟变量一样）
- 学生能够正确使用函数体缩进
- 学生能够理解定义和调用的顺序（先定义，后调用）
- 学生能够独立定义 `say_hello()`、`print_line()` 等简单函数

## 📝 重点概念
- **def 语法**：`def 函数名():` 开头，下面缩进写函数体
- **命名规则**：字母、数字、下划线，不能数字开头，要有意义
- **定义 vs 调用**：定义是"造机器"，调用是"用机器"
- **缩进**：函数体内的代码必须统一缩进（4 个空格）

## 📖 讲解内容

### 步骤1：引入（5分钟）

"上节课我们认识了函数，知道它像一台榨汁机。今天我们要亲手造榨汁机！"

**类比**：
- 买来的榨汁机 = Python 内置函数（print、input、len）
- 自己造的榨汁机 = 自定义函数（用 def 定义）

"今天我们就来学习 DIY 函数！"

### 步骤2：核心讲解（15-20分钟）

#### 2.1 def 语法的四个要素

```python
def 函数名():       # ① def + ② 名字 + ③ 括号冒号
    函数体          # ④ 缩进的代码
```

**逐条解析**：

| 要素 | 说明 | 示例 |
|------|------|------|
| `def` | Python 关键字，表示"我要定义函数" | `def` |
| 函数名 | 自己取名，规则跟变量一样 | `say_hello`、`print_line` |
| `():` | 小括号+冒号，必须写，后面会用来放参数 | `():` |
| 函数体 | 缩进的代码块，函数要执行的命令 | `print("你好")` |

#### 2.2 函数命名规则

- 只能用字母、数字、下划线 `_`
- 不能以数字开头
- 区分大小写（`SayHello` 和 `sayhello` 是不同的）
- 要有意义！`say_hello` 比 `f1` 好得多

**好名字 vs 坏名字**：

```python
# 好名字 ✅
def say_hello():       # 一看就知道是"打招呼"
def print_separator(): # 一看就知道是"打印分隔线"
def calculate_total(): # 一看就知道是"计算总数"

# 坏名字 ❌
def a():               # 不知道干什么
def f1():              # 太模糊
def xyz():             # 莫名其妙
```

#### 2.3 定义和调用的顺序

**重要规则：先定义，后调用！**

```python
# ✅ 正确：先定义
def greet():
    print("你好！")

greet()  # 调用成功！

# ❌ 错误：先调用
# hello()  # 报错！NameError: name 'hello' is not defined

def hello():
    print("Hello!")
```

**类比**：你得先造出榨汁机，才能用它榨汁。不能对着空气说"榨汁机，给我榨杯果汁！"

#### 2.4 函数体内的缩进

```python
def greet():
    print("你好！")      # 缩进 4 空格
    print("欢迎光临！")  # 缩进 4 空格
    print("=" * 20)     # 缩进 4 空格

# 这行没有缩进 → 不属于函数
print("我是函数外面的代码")
```

**缩进错误示例**：

```python
def greet():
print("你好！")    # ❌ 没有缩进，报错！IndentationError

def greet():
    print("你好！")
  print("欢迎！")  # ❌ 缩进不一致，报错！
```

### 步骤3：动手演示（10分钟）

```python
# 示范1：最简单的函数
def say_hello():
    """打个招呼"""    # 文档字符串（docstring），解释函数用途
    print("你好，欢迎来到 Python 世界！")

say_hello()

# 示范2：打印分隔线
def print_line():
    print("-" * 30)

print_line()
print("第一章")
print_line()
print("第二章")
print_line()

# 示范3：多个函数配合
def show_menu():
    print_line()
    print("  1. 开始游戏")
    print("  2. 查看成绩")
    print("  3. 退出")
    print_line()

show_menu()

# 示范4：定义和调用的顺序（让学生在互动中体会）
# 提问：如果把 say_hello() 放到 def say_hello(): 前面会怎样？
# 让学生猜，然后演示
```

## 💻 代码示例

```python
# ========== 第29节：def —— 定义自己的函数 ==========

# --- 1. 定义第一个函数 ---
print("=== 我的第一个函数 ===")

def say_hello():
    """一个简单的打招呼函数"""
    print("=" * 20)
    print("你好呀！")
    print("我是你自己定义的函数！")
    print("=" * 20)

# 调用函数
say_hello()
print()  # 空一行
say_hello()  # 可以多次调用！

# --- 2. 定义多个函数 ---
print("\n=== 多个函数配合 ===")

def print_star_line():
    """打印星星分隔线"""
    print("⭐" * 15)

def print_dash_line():
    """打印横线分隔线"""
    print("-" * 30)

def greet_user():
    """欢迎用户"""
    print_star_line()
    print("    欢迎来到 Python 乐园！")
    print_star_line()

def say_goodbye():
    """告别用户"""
    print_dash_line()
    print("    感谢使用，再见！")
    print_dash_line()

# 使用函数
greet_user()
print()
print("这里是程序的主要部分...")
print()
say_goodbye()

# --- 3. 函数的命名 ---
print("\n=== 好的函数名 vs 坏的函数名 ===")

# 好的函数名：一看就知道做什么
def print_math_score():
    """打印数学成绩"""
    print("数学成绩：95 分")

def show_game_title():
    """显示游戏标题"""
    print("=== 超级猜数字 ===")

# 坏的函数名：不知道做什么（仅作演示，不要学！）
def a():
    """???（不好的命名）"""
    print("数学成绩：95 分")

print_math_score()
show_game_title()

# --- 4. 函数里的缩进（重要！） ---
print("\n=== 缩进规则 ===")

def demonstrate_indent():
    print("这一行有 4 个空格的缩进")       # 属于函数
    print("这一行也有 4 个空格的缩进")      # 属于函数
    if True:
        print("if 里面再多缩进 4 个空格")   # 属于 if，也属于函数
    print("回到 4 个空格缩进")             # 属于函数

print("这一行没有缩进，不在函数里")          # 不属于函数

demonstrate_indent()

# --- 5. 练习：打造自己的工具函数 ---
print("\n=== 打造工具函数 ===")

def show_menu():
    """显示功能菜单"""
    print()
    print("=" * 30)
    print("    📋 功能菜单")
    print("=" * 30)
    print("  1. 查看个人信息")
    print("  2. 修改密码")
    print("  3. 退出系统")
    print("=" * 30)

def show_welcome():
    """显示欢迎界面"""
    print("🌟" * 10)
    print("  欢迎使用学生管理系统")
    print("🌟" * 10)

def show_error():
    """显示错误提示"""
    print("❌ 输入有误，请重新输入！")

# 实际使用
show_welcome()
show_menu()
show_error()
print("请输入正确的选项...")
show_menu()

# --- 6. 综合例子：打造一个简单的游戏框架 ---
print("\n=== 小游戏框架 ===")

def game_start():
    """游戏开始"""
    print("\n🎮" + "=" * 28)
    print("   猜数字游戏")
    print("=" * 28 + "🎮")
    print("  我想了一个 1-100 之间的数字")
    print("  你准备好了吗？")

def game_win():
    """胜利画面"""
    print("\n🎉🎉🎉")
    print("  恭喜你猜对了！")
    print("🎉🎉🎉")

def game_lose():
    """失败画面"""
    print("\n😢")
    print("  很遗憾，机会用完了")
    print("  下次加油！")

def game_over():
    """游戏结束"""
    print("\n" + "=" * 20)
    print("  游戏结束，再见！")
    print("=" * 20)

# 模拟游戏流程
game_start()
print("\n你猜：50")
print("提示：太小了！")
print("\n你猜：75")
print("提示：太大了！")
print("\n你猜：63")
game_win()
game_over()
```

## ✏️ 课堂练习

### 基础练习
1. **第一个函数**：定义一个 `say_hello()` 函数，让它打印你喜欢的问候语，然后调用它 3 次。
2. **分隔线函数**：定义 `print_line()` 函数，打印一条由 20 个 `~` 组成的分隔线。用它来分隔三段不同的文字。
3. **命名判断**：判断以下函数名好不好，为什么？
   - `get_score()` 
   - `x()`
   - `print123()`
   - `calculate_average_score()`
   - `_secret()`

### 挑战练习
1. **故事函数**：定义 4 个函数：`story_begin()`、`story_middle()`、`story_climax()`、`story_end()`，分别打印故事的不同部分，然后按顺序调用来"讲"一个故事。
2. **菜单框架**：定义函数搭建一个程序菜单框架，有标题、选项和退出画面，就像一个小程序的外壳。

## 📋 小结

### 本节学了什么
- **def 语法**：`def 函数名():` + 缩进的函数体
- **命名规则**：跟变量一样，要有意义
- **定义和调用顺序**：必须先定义，后调用
- **缩进规则**：函数体内统一缩进（4 个空格）

### 记忆口诀
- "def 开头来定义，括号冒号不能忘"
- "函数体要缩进，四格空格是标准"
- "先定义再调用，顺序反了要报错"

### 下节预告
下一节我们学习**参数**——如何给函数传递信息，让函数更灵活！
