# 第 1 课 · 你好，Python！— 安装环境 + 第一个窗口

---

## 🎯 本课目标

- 安装 Python 和 VS Code（写代码的工具）
- 用 `print()` 让电脑"说话"
- 学会"变量"——给数据起个名字
- 创建人生中**第一个图形化窗口**！

---

## 📚 新知识

### 1.1 Python 是什么？

Python 是一种**编程语言**。编程语言就是你用来和电脑"对话"的工具。你用 Python 写一段话（代码），电脑就能听懂并执行。

为什么叫 Python？它的创造者 Guido van Rossum 是英国喜剧团体"蒙提·派森"（Monty Python）的粉丝，所以用 Python（蟒蛇）命名。**跟蟒蛇没有直接关系！**

Python 的特点：
- ✅ **语法简单**：写起来像英语，很好读
- ✅ **功能强大**：能做网站、游戏、数据分析、人工智能……
- ✅ **自带"电池"**：内置了大量工具库（比如做 GUI 的 tkinter）

### 1.2 安装 Python

> 📌 **注意**：以下步骤请根据你的操作系统选择。

#### Windows 系统

1. 打开浏览器，访问 https://www.python.org/downloads/
2. 点击黄色的大按钮 **"Download Python 3.x.x"**（数字会随时间更新）
3. 下载完成后，双击运行安装程序
4. ⚠️ **重要**：勾选底部的 **"Add Python to PATH"**（把 Python 加到系统路径）
5. 点击 "Install Now"（立即安装）
6. 安装完成后关闭窗口

**验证安装是否成功**：
- 按 `Win + R`，输入 `cmd`，回车
- 在弹出的黑色窗口（命令提示符）中输入：`python --version`
- 如果显示 `Python 3.x.x`，说明安装成功！✅

#### Mac 系统

1. 打开浏览器，访问 https://www.python.org/downloads/
2. 点击黄色的大按钮 **"Download Python 3.x.x"**
3. 下载完成后，双击 `.pkg` 文件安装
4. 一路点击"继续"，直到完成

**验证安装是否成功**：
- 按 `Command + 空格`，输入 `Terminal`（终端），回车
- 在终端中输入：`python3 --version`
- 如果显示 `Python 3.x.x`，说明安装成功！✅

### 1.3 安装 VS Code（写代码的编辑器）

VS Code（Visual Studio Code）是微软开发的一款**免费**代码编辑器，功能强大、界面友好。

1. 访问 https://code.visualstudio.com/
2. 点击下载按钮，选择你的系统版本
3. 安装并打开 VS Code

**安装 Python 插件**：
1. 打开 VS Code
2. 点击左侧的"扩展"图标（四个方块）
3. 搜索 `Python`
4. 找到微软官方的 Python 插件，点击"安装"

### 1.4 你的第一行 Python 代码：`print()`

`print()` 是 Python 内置的**输出函数**。它的作用是在屏幕上显示文字。

```python
print("你好，Python！")
```

**知识点拆解**：
- `print` — 函数名，意思是"打印/输出"
- `()` — 括号，里面放要输出的内容
- `""` — 双引号，里面的文字叫**字符串**（string）
- `"你好，Python！"` — 这就是要输出的内容

> 💡 **类比**：`print()` 就像一个喇叭📢，括号里的东西会被它"喊"出来。

**运行你的第一行代码**：
1. 打开 VS Code
2. 点击 "File" → "New File"（或 `Ctrl+N` / `Cmd+N`）
3. 输入 `print("你好，Python！")`
4. 点击 "File" → "Save As..."，保存为 `hello.py`
   - `.py` 是 Python 文件的扩展名，非常重要！
5. 点击右上角的 ▶️ 运行按钮
6. 看终端（下方）输出：`你好，Python！`

### 1.5 变量 — 给数据起个名字

**变量**就是给数据起的名字。想象一个贴了标签的盒子，标签就是变量名，盒子里装的就是数据。

```python
name = "小明"
print(name)
```

输出：`小明`

**知识点**：
- `name` — 变量名（我们自己起的）
- `=` — 赋值符号，把右边的数据"装进"左边的变量
- `"小明"` — 字符串数据
- `print(name)` — 输出变量里的内容，**不用加引号**

**变量起名规则**：
- ✅ 可以用字母、数字、下划线
- ✅ 区分大小写：`name` 和 `Name` 是不同的
- ❌ 不能以数字开头
- ❌ 不能用 Python 的关键字（如 `print`、`if`、`for`）

```python
# ✅ 好的变量名
my_name = "小华"
age = 12
hobby_1 = "编程"

# ❌ 不好的变量名
1name = "错误"     # 数字开头
print = "不行"     # print 是关键字
my name = "不行"   # 不能有空格
```

### 1.6 什么是 tkinter？

**tkinter** 是 Python 自带的一个库（library），专门用来创建**图形用户界面**（GUI — Graphical User Interface）。

> 💡 **通俗理解**：tkinter 就是一套"积木"，你可以用它搭建窗口、按钮、输入框、列表等图形界面。

**不需要额外安装**！Python 安装时就自带 tkinter。

### 1.7 创建你的第一个窗口

```python
import tkinter as tk          # 导入 tkinter，简称为 tk

window = tk.Tk()              # 创建一个窗口对象
window.title("我的备忘录")      # 设置窗口标题
window.geometry("400x500")    # 设置窗口大小（宽x高）
window.mainloop()             # 让窗口一直运行
```

**逐行讲解**：

| 代码 | 解释 |
|------|------|
| `import tkinter as tk` | 导入 tkinter 库，`as tk` 的意思是给它起个简称 `tk`，后面写代码时更省事 |
| `window = tk.Tk()` | 创建一个窗口对象，赋值给变量 `window`。`Tk()` 是 tkinter 的核心，表示"一个窗口" |
| `window.title("我的备忘录")` | 设置窗口顶部的标题文字 |
| `window.geometry("400x500")` | 设置窗口的宽和高，`"400x500"` 表示宽 400 像素、高 500 像素。`x` 是小写字母 x |
| `window.mainloop()` | **关键的一行！** 让窗口保持运行，不停地检测你有没有点击按钮、关闭窗口等 |

> 💡 **类比**：`mainloop()` 就像一个前台接待员，一直站在那里，等着你操作窗口。如果没有这行，窗口会"闪一下"就消失。

### 1.8 Label 标签 — 在窗口里显示文字

`Label` 是 tkinter 中最简单的**控件**（Widget），专门用来**显示文字**（用户不能修改）。

```python
# 创建标签
label = tk.Label(窗口对象, text="要显示的文字", font=("字体名", 字号))

# 把标签放到窗口里
label.pack()
```

**参数详解**：

| 参数 | 说明 | 示例 |
|------|------|------|
| 第一个参数 | 这个标签属于哪个窗口 | `window` |
| `text` | 要显示的文字内容 | `text="欢迎使用备忘录！"` |
| `font` | 字体设置，是一个元组 `("字体名", 字号)` | `font=("微软雅黑", 16)` |
| `fg` | 文字颜色（foreground） | `fg="blue"` 或 `fg="#3333FF"` |
| `bg` | 背景颜色（background） | `bg="yellow"` |

```python
# 示例：创建一个蓝色大标题标签
title_label = tk.Label(
    window,
    text="📝 我的备忘录",
    font=("微软雅黑", 20),
    fg="blue"
)
title_label.pack()
```

> 💡 **注意**：创建控件后，**必须调用 `.pack()`** 才能把它放到窗口里显示出来。否则控件虽然被创建了，但不会显示在窗口上。

---

## 💻 写代码

### 步骤 1：创建文件

在 VS Code 中新建文件，保存为 `lesson1.py`。

### 步骤 2：编写代码

我们先写一个简单的 `print()` 热身，再写窗口：

```python
# 第 1 课：你好，Python！

# 第一步：让电脑说话
print("你好，Python！")
print("今天开始学编程！")

# 第二步：试试变量
my_name = "小明"
my_age = 12
print("我叫" + my_name)
print("我今年" + str(my_age) + "岁")

# 第三步：创建窗口
import tkinter as tk

# 创建主窗口
window = tk.Tk()

# 设置窗口标题
window.title("我的备忘录")

# 设置窗口大小（宽x高，中间是小写字母 x）
window.geometry("400x500")

# 第四步：在窗口里添加一个标签（Label）
hello_label = tk.Label(
    window,
    text="欢迎来到我的备忘录！",
    font=("微软雅黑", 14),
    fg="#333333"
)
hello_label.pack(pady=20)

# 让窗口保持运行（这一行要放在最后）
window.mainloop()
```

### 步骤 3：运行

点击 VS Code 右上角的 ▶️ 运行按钮。

---

## ▶️ 运行看效果

运行后，你应该会看到：

**终端输出**：
```
你好，Python！
今天开始学编程！
我叫小明
我今年12岁
```

**窗口**：一个灰色的窗口弹出来，标题栏写着"我的备忘录"，大小是 400×500 像素。

> 📸 *（此处放置窗口截图）*

你可以试着拖动窗口、调整大小（会发现有最小尺寸约束）、点击关闭按钮。

---

## ✏️ 小练习

1. **改标题**：把窗口标题改成你自己的名字，比如 `"小华的备忘录"`
2. **改大小**：把窗口大小改成 `"600x400"`，看看长方形窗口的效果
3. **加一行 print**：在代码最前面让电脑打印一句 `"我要做出一个超棒的备忘录！"`
4. **试试变量**：创建两个新变量，分别存你的年龄和爱好，用 `print()` 打印出来
5. **改 Label**：把标签的文字改成 `"你好，我是xxx！"`，试试改字体大小和颜色（`fg`）

---

## 📋 本课完整代码

```python
# ============================================
# 第 1 课：你好，Python！— 第一个窗口 + Label 标签
# ============================================

# --- 第一部分：print() 和变量 ---

# 让电脑说话
print("你好，Python！")
print("今天开始学编程！")

# 变量练习
my_name = "小明"
my_age = 12
my_hobby = "编程"

print("我叫" + my_name)
print("我今年" + str(my_age) + "岁")
print("我的爱好是" + my_hobby)

# --- 第二部分：创建第一个 GUI 窗口 ---

# 导入 tkinter 库
import tkinter as tk

# 创建主窗口（就像买了一个空画框）
window = tk.Tk()

# 设置窗口标题（给画框贴个标签）
window.title("我的备忘录")

# 设置窗口大小（宽x高，单位是像素）
window.geometry("400x500")

# --- 第三部分：添加 Label 标签 ---

# 添加一个欢迎标签
hello_label = tk.Label(
    window,
    text="欢迎来到我的备忘录！",
    font=("微软雅黑", 14),
    fg="#333333"
)
hello_label.pack(pady=20)

# 让窗口一直显示（事件循环，必须放最后）
window.mainloop()
```

---

## 🧠 本课小结

| 学到的知识 | 是什么 | 怎么用 |
|-----------|--------|--------|
| `print()` | 输出函数 | `print("要显示的内容")` |
| 变量 | 给数据起名字 | `name = "小明"` |
| `import ... as ...` | 导入库 | `import tkinter as tk` |
| `tk.Tk()` | 创建窗口 | `window = tk.Tk()` |
| `.title()` | 设标题 | `window.title("标题")` |
| `.geometry()` | 设大小 | `window.geometry("宽x高")` |
| `tk.Label()` | 文字标签 | `tk.Label(window, text="文字", font=("字体", 字号))` |
| `.pack()` | 放置控件 | `label.pack(pady=间距)` |
| `.mainloop()` | 窗口循环 | `window.mainloop()` |

---

## 📖 下节课预告

第 2 课：**按钮与交互 — Button 按钮、pack 布局和 f-string**

我们将添加可点击的按钮，学会 pack() 布局和 f-string 格式化，让窗口"活"起来！
