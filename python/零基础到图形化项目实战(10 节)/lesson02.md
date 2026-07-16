# 第 2 课 · 按钮与交互 — Button 按钮、pack 布局和 f-string

---

## 🎯 本课目标

- 理解"控件"（Widget）的概念
- 在窗口中添加可点击的按钮（Button）
- 学会 `pack()` 布局方式
- 学会用 `f-string` 格式化文字
- 学会用 `def` 定义自己的函数
- 给按钮绑定 `command`，实现"点按钮做事情"
- 学会 `.config()` 动态修改控件属性

---

## 📚 新知识

### 2.1 什么是"控件"（Widget）？

**控件**（Widget）就是窗口里的各种"零件"。你可以把窗口想象成一块画板，控件就是贴在上面的贴纸：

| 控件 | 中文名 | 作用 | 像什么？ |
|------|--------|------|----------|
| `Label` | 标签 | 显示文字 | 便利贴 📝 |
| `Button` | 按钮 | 点击触发操作 | 开关 🔘 |
| `Entry` | 输入框 | 让用户打字 | 填空题的空格 ✏️ |
| `Listbox` | 列表框 | 显示一列选项 | 清单 📋 |

> 💡 **控件的生命周期**：创建控件 → 设置属性 → 放到窗口里 → 显示

### 2.2 Button 按钮 — 可点击

`Button` 是一个**可以点击**的控件。点击后可以执行你指定的操作。

```python
# 创建按钮
btn = tk.Button(窗口对象, text="按钮上的文字", command=函数名)

# 把按钮放到窗口里
btn.pack()
```

**核心参数 `command`**：指定点击按钮后要执行的函数。

> ⚠️ **注意**：`command=函数名` **不要加括号**！
> - ✅ 正确：`command=say_hello`
> - ❌ 错误：`command=say_hello()`（这样会在创建按钮时就执行函数，而不是点击时）

### 2.3 pack() — 最简单的布局

`pack()` 是 tkinter 三种布局方式中最简单的一种。

**规则**：按照控件创建的**先后顺序**，从上到下依次堆叠。

```python
label1.pack()   # 第一个，出现在最上面
label2.pack()   # 第二个，出现在 label1 下面
button1.pack()  # 第三个，出现在 label2 下面
```

> 💡 **类比**：`pack()` 就像叠罗汉，谁先"站上去"谁就在上面。

`pack()` 的常用参数：

| 参数 | 说明 | 取值 |
|------|------|------|
| `side` | 靠哪边 | `tk.TOP`（默认）、`tk.BOTTOM`、`tk.LEFT`、`tk.RIGHT` |
| `pady` | 上下留空（像素） | `pady=10` |
| `padx` | 左右留空（像素） | `padx=20` |
| `fill` | 是否填满 | `tk.X`（横向填满）、`tk.Y`（纵向填满）、`tk.BOTH` |

### 2.4 f-string — 格式化文字

`f-string` 是 Python 3.6 以后的新特性，可以**把变量嵌入到字符串中**，非常方便。

```python
name = "小明"
age = 12

# 普通拼接（麻烦）
print("我叫" + name + "，今年" + str(age) + "岁")

# f-string（简洁优雅）✅ 推荐！
print(f"我叫{name}，今年{age}岁")
```

**语法**：
- 字符串前面加 `f`
- 变量用 `{ }` 包起来
- 花括号里甚至可以写简单的计算：`f"明年我{age + 1}岁"`

### 2.5 函数入门 — 用 `def` 定义操作

**函数**是一段有名字的代码，可以被重复调用。在第 1 课我们用过 `print()` 这个内置函数，现在我们自己定义函数。

```python
def 函数名():
    要执行的代码
    要执行的代码
```

```python
# 定义一个函数
def say_hello():
    print("你好！")
    print("按钮被点击了！")

# 调用函数（执行）
say_hello()  # 输出两行文字
```

**定义 vs 调用**：
- **定义**（`def`）= 写菜谱 — 只是记下来，还不做
- **调用**（`函数名()`）= 炒菜 — 真正执行

---

## 💻 写代码

### 步骤 1：创建文件

新建 `lesson2.py`。

### 步骤 2：搭建窗口骨架

```python
import tkinter as tk

window = tk.Tk()
window.title("我的备忘录")
window.geometry("400x500")
```

### 步骤 3：添加标签（复习第 1 课）

Label 在第 1 课已经学过，这里快速复习一下：

```python
# 大标题
title_label = tk.Label(
    window,
    text="📝 我的备忘录",
    font=("微软雅黑", 20, "bold"),
    fg="#333333"
)
title_label.pack(pady=15)

# 副标题
subtitle_label = tk.Label(
    window,
    text="用 Python 打造自己的专属工具！",
    font=("微软雅黑", 10),
    fg="#888888"
)
subtitle_label.pack(pady=5)
```

### 步骤 4：添加按钮和功能

```python
# --- 定义函数：按钮点击后做什么 ---

click_count = 0  # 计数器变量，记录点击次数

def on_button_click():
    """按钮被点击时执行这个函数"""
    global click_count  # 声明要修改全局变量
    click_count = click_count + 1
    print(f"按钮被点击了！第 {click_count} 次")

    # 更新标签的文字
    info_label.config(text=f"按钮已被点击 {click_count} 次")

# --- 创建控件 ---

# 一个普通按钮
btn = tk.Button(
    window,
    text="点击我！",
    font=("微软雅黑", 14),
    command=on_button_click,  # 注意：不要加括号！
    bg="#4CAF50",             # 绿色背景
    fg="white",               # 白色文字
    padx=20,                  # 按钮内部水平留白
    pady=10                   # 按钮内部垂直留白
)
btn.pack(pady=20)

# 显示点击次数的标签
info_label = tk.Label(
    window,
    text="还没有点击过",
    font=("微软雅黑", 12),
    fg="#666666"
)
info_label.pack(pady=10)

# 退出按钮
quit_btn = tk.Button(
    window,
    text="退出程序",
    font=("微软雅黑", 10),
    command=window.destroy,  # .destroy() 可以关闭窗口
    bg="#f44336",            # 红色背景
    fg="white"
)
quit_btn.pack(pady=30)
```

### 步骤 5：运行主循环

```python
window.mainloop()
```

---

## ▶️ 运行看效果

**终端输出**（每次点击按钮后）：
```
按钮被点击了！第 1 次
按钮被点击了！第 2 次
按钮被点击了！第 3 次
```

**窗口效果**：窗口顶部显示大标题和副标题，中间有一个绿色按钮，下面是点击次数，最下面是红色退出按钮。

> 📸 *（此处放置窗口截图）*

---

## ✏️ 小练习

1. **多加一个按钮**：创建第三个按钮，文字是"打招呼"，点击后在终端打印 `print("你好呀！")`
2. **改颜色**：把标题 `fg` 改成 `"blue"`，把绿色按钮的背景 `bg` 改成 `"#FF9800"`（橙色）
3. **改字体**：把标题字体改成 `"Arial"`，看看英文系统默认字体的效果
4. **挑战题**：尝试用 `pack(side=tk.LEFT)` 把两个按钮水平并排显示（提示：需要创建一个 Frame 容器）

---

## 📋 本课完整代码

```python
# ============================================
# 第 2 课：Button 按钮、pack 布局和 f-string
# ============================================

import tkinter as tk

# --- 创建窗口 ---
window = tk.Tk()
window.title("我的备忘录")
window.geometry("400x500")

# --- 定义函数 ---

click_count = 0  # 计数器

def on_button_click():
    """按钮被点击时执行"""
    global click_count
    click_count = click_count + 1
    print(f"按钮被点击了！第 {click_count} 次")
    # 更新标签文字
    info_label.config(text=f"按钮已被点击 {click_count} 次")

# --- 创建控件 ---

# 1. 大标题标签
title_label = tk.Label(
    window,
    text="📝 我的备忘录",
    font=("微软雅黑", 20, "bold"),
    fg="#333333"
)
title_label.pack(pady=15)

# 2. 副标题标签
subtitle_label = tk.Label(
    window,
    text="用 Python 打造自己的专属工具！",
    font=("微软雅黑", 10),
    fg="#888888"
)
subtitle_label.pack(pady=5)

# 3. 点击按钮
btn = tk.Button(
    window,
    text="点击我！",
    font=("微软雅黑", 14),
    command=on_button_click,
    bg="#4CAF50",
    fg="white",
    padx=20,
    pady=10
)
btn.pack(pady=20)

# 4. 点击次数显示标签
info_label = tk.Label(
    window,
    text="还没有点击过",
    font=("微软雅黑", 12),
    fg="#666666"
)
info_label.pack(pady=10)

# 5. 退出按钮
quit_btn = tk.Button(
    window,
    text="退出程序",
    font=("微软雅黑", 10),
    command=window.destroy,
    bg="#f44336",
    fg="white"
)
quit_btn.pack(pady=30)

# 6. 底部说明
footer_label = tk.Label(
    window,
    text="第 2 课 · Button 与交互",
    font=("微软雅黑", 8),
    fg="#CCCCCC"
)
footer_label.pack(side=tk.BOTTOM, pady=10)

# --- 运行主循环 ---
window.mainloop()
```

---

## 🧠 本课小结

| 学到的知识 | 是什么 | 怎么用 |
|-----------|--------|--------|
| `Button` | 按钮控件 | `tk.Button(window, text="按钮", command=函数名)` |
| `pack()` | 布局方式 | `控件.pack(pady=间距)` |
| `f-string` | 格式化文字 | `f"我叫{name}"` |
| `def` | 定义函数 | `def 函数名():` |
| `command=` | 绑定点击操作 | `command=函数名`（不加括号！） |
| `.config()` | 修改控件属性 | `label.config(text="新文字")` |

---

## 📖 下节课预告

第 3 课：**输入文字吧 — Entry 输入框和 Listbox 列表**

我们将加入输入框，让你可以**打字输入待办事项**，点击按钮后添加到下方的列表中——备忘录的核心交互来了！
