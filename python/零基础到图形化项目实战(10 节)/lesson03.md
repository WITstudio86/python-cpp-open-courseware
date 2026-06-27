# 第 3 课 · 输入文字吧 — Entry 输入框和 Listbox 列表

---

## 🎯 本课目标

- 学会用 `Entry` 输入框让用户打字
- 学会 `.get()` 获取输入框内容
- 学会用 `Listbox` 显示事项列表
- 学会 `list` 列表类型，用 `append()` 添加数据
- 学会 `if` 条件判断，防止空输入
- 实现备忘录的**核心功能**：输入 → 添加 → 显示

---

## 📚 新知识

### 3.1 Entry 输入框 — 让用户打字

`Entry` 是一个**单行文本输入框**。用户可以点击它，然后用键盘输入文字。

```python
entry = tk.Entry(窗口对象, font=("字体", 字号), width=宽度)
entry.pack()
```

**核心方法**：

| 方法 | 作用 | 示例 |
|------|------|------|
| `.get()` | **获取**输入框里的文字 | `text = entry.get()` |
| `.delete(0, tk.END)` | **清空**输入框 | `entry.delete(0, tk.END)` |
| `.insert(0, "文字")` | **插入**文字 | `entry.insert(0, "默认文字")` |

**`delete(0, tk.END)` 参数详解**：
- `0` — 从第 0 个字符开始（即开头）
- `tk.END` — 到最后一个字符（即末尾）
- 合起来意思：**从头删到尾** = 全部清空

> 💡 **类比**：Entry 就像一张便利贴。`.get()` 是读上面的内容，`.delete(0, END)` 是把便利贴撕掉换新的。

### 3.2 Listbox 列表框 — 显示一列内容

`Listbox` 是一个**滚动列表**，可以显示多条内容。

```python
listbox = tk.Listbox(窗口对象, font=("字体", 字号), height=高度)
listbox.pack()
```

**核心方法**：

| 方法 | 作用 | 示例 |
|------|------|------|
| `.insert(tk.END, "内容")` | 在末尾**添加**一条 | `listbox.insert(tk.END, "学Python")` |
| `.delete(索引)` | **删除**指定位置的一条 | `listbox.delete(0)` 删除第一条 |
| `.size()` | 获取当前**共有几条** | `count = listbox.size()` |
| `.get(索引)` | **获取**指定位置的内容 | `item = listbox.get(0)` |

**索引（index）**：列表中每条数据都有一个编号，从 `0` 开始。

```
位置 0 → 第一条数据
位置 1 → 第二条数据
位置 2 → 第三条数据
```

> 💡 `tk.END` 是一个特殊常量，表示"列表末尾"。`listbox.insert(tk.END, "学Python")` 的意思是"在列表末尾插入一条"学Python""。

### 3.3 list 列表 — Python 的数据容器

**列表（list）** 是 Python 中最常用的数据容器，可以**按顺序存放多个数据**。

```python
# 创建一个列表
todos = ["学Python", "写作业", "做运动"]

# 列表操作
todos.append("学吉他")       # 添加元素 → ["学Python", "写作业", "做运动", "学吉他"]
first = todos[0]             # 访问第 1 个 → "学Python"
second = todos[1]            # 访问第 2 个 → "写作业"
count = len(todos)           # 获取长度 → 4

# 列表可以混合不同类型
mixed = ["文字", 123, True, 3.14]
```

> 💡 **类比**：列表就像购物清单 📋—— 一行一行写，有顺序，可以随时加新东西。

### 3.4 if 条件判断 — 让程序学会"思考"

`if` 语句让程序能根据条件做出不同的反应。

```python
if 条件:
    条件成立时执行的代码
else:
    条件不成立时执行的代码
```

```python
age = 15

if age >= 18:
    print("你是成年人")
else:
    print("你是未成年人")
```

**比较运算符**：

| 运算符 | 含义 | 示例 | 结果 |
|--------|------|------|------|
| `==` | 等于 | `5 == 5` | `True` |
| `!=` | 不等于 | `5 != 3` | `True` |
| `>` | 大于 | `10 > 3` | `True` |
| `<` | 小于 | `3 < 10` | `True` |
| `>=` | 大于等于 | `10 >= 10` | `True` |
| `<=` | 小于等于 | `3 <= 5` | `True` |

> ⚠️ **注意**：判断"等于"用 `==`（两个等号），和赋值的 `=`（一个等号）完全不同！

**本课的应用**：判断输入框是否为空。

```python
text = entry.get()      # 获取输入的文字
if text:                 # 如果文字非空（等价于 text != ""）
    listbox.insert(tk.END, text)
else:
    print("请输入内容！")
```

在 Python 中，**空字符串 `""` 被视为 `False`**，非空字符串被视为 `True`。所以 `if text:` 就是在判断"输入了东西吗？"

---

## 💻 写代码

### 步骤 1：项目框架

新建 `lesson3.py`。这次的代码会以第 2 课为基础，但用新的控件替换掉"点击计数"的部分。

```python
import tkinter as tk

# 创建窗口
window = tk.Tk()
window.title("我的备忘录")
window.geometry("400x550")
```

### 步骤 2：标题和副标题

```python
# 标题
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
    text="输入待办事项，点击添加吧！",
    font=("微软雅黑", 10),
    fg="#888888"
)
subtitle_label.pack(pady=5)
```

### 步骤 3：输入框区域

```python
# --- 输入框区域 ---

# 创建一个 Frame（框架）来容纳输入框和按钮
# Frame 是一个"看不见的容器"，方便把多个控件组织在一起
input_frame = tk.Frame(window)
input_frame.pack(pady=15)

# 输入框
entry = tk.Entry(
    input_frame,
    font=("微软雅黑", 13),
    width=25  # 宽度按字符数计算（不是像素）
)
entry.pack(side=tk.LEFT, padx=(0, 5))  # 放在框架左边，右边留 5 像素空隙

# 添加按钮
add_btn = tk.Button(
    input_frame,
    text="添加 ✅",
    font=("微软雅黑", 12),
    bg="#4CAF50",
    fg="white",
    padx=10,
    pady=5
)
add_btn.pack(side=tk.LEFT)  # 放在输入框右边
```

> 💡 **Frame 的作用**：Frame 就像一个"看不见的盒子"，可以把多个控件装在一起，方便整体布局。上面的代码用 Frame 把输入框和按钮**水平排列**在一起。

### 步骤 4：列表区域

```python
# --- 待办事项列表 ---

# 列表标题
list_label = tk.Label(
    window,
    text="📋 待办事项",
    font=("微软雅黑", 12, "bold"),
    fg="#555555"
)
list_label.pack(pady=(20, 5))

# Listbox 列表控件
listbox = tk.Listbox(
    window,
    font=("微软雅黑", 12),
    height=15,            # 最多显示 15 行
    width=40,
    selectbackground="#C8E6C9",  # 选中项的背景色（浅绿）
    selectforeground="#333333"   # 选中项的文字色
)
listbox.pack(pady=5)
```

### 步骤 5：实现添加功能

```python
# --- 核心逻辑：添加待办事项 ---

def add_todo():
    """获取输入框内容，添加到列表中"""
    # 1. 获取输入的文字
    text = entry.get()

    # 2. 去掉首尾空格
    text = text.strip()

    # 3. 判断是否为空
    if text:
        # 非空：添加到列表
        listbox.insert(tk.END, text)
        # 清空输入框
        entry.delete(0, tk.END)
        # 在终端打印确认
        print(f"✅ 添加了：{text}")
    else:
        # 空输入：提示
        print("⚠️ 请输入待办事项！")

# 把函数绑定到按钮上
add_btn.config(command=add_todo)
```

> 💡 **`strip()` 的作用**：去掉字符串首尾的空格。比如用户输入 `"  学Python  "` → `strip()` 后变成 `"学Python"`。

### 步骤 6：快捷键支持

让用户按**回车键**也能添加，不用每次都点按钮：

```python
# --- 快捷键：按回车键也能添加 ---

def on_enter_press(event):
    """当输入框中按下回车键时触发"""
    add_todo()

# 绑定回车键事件
entry.bind("<Return>", on_enter_press)
```

> 💡 **`<Return>`** 是 tkinter 中"回车键"的名称。`.bind()` 用于绑定键盘事件。

### 步骤 7：运行

```python
# 让光标默认停在输入框里
entry.focus()

window.mainloop()
```

---

## ▶️ 运行看效果

运行程序后，你应该能：

1. 在输入框中输入文字，比如 `"学Python"`
2. 点击"添加 ✅"按钮，下方列表出现 `学Python`
3. 输入框自动清空，准备好输入下一条
4. 继续输入 `"写作业"`、`"做运动"`，列表依次增加
5. 直接按回车键，效果和点按钮一样
6. 输入空白内容点添加，终端显示 `⚠️ 请输入待办事项！`

> 📸 *（此处放置窗口截图）*

---

## ✏️ 小练习

1. **改提示**：把空输入时只在终端提示，改为弹出一个错误标签（提示：创建一个红色的 Label，用 `.config()` 更新文字）
2. **改颜色**：把"添加"按钮改成蓝色（`bg="#2196F3"`）
3. **统计数量**：在列表标题后面显示当前待办数量，比如 `"📋 待办事项（共 3 条）"`
4. **挑战题**：加一个"清空全部"按钮，点击后删除 Listbox 中的所有内容（提示：`listbox.delete(0, tk.END)`）

---

## 📋 本课完整代码

```python
# ============================================
# 第 3 课：Entry 输入框和 Listbox 列表
# ============================================

import tkinter as tk

# ==================== 创建窗口 ====================

window = tk.Tk()
window.title("我的备忘录")
window.geometry("400x550")

# ==================== 标题区域 ====================

title_label = tk.Label(
    window,
    text="📝 我的备忘录",
    font=("微软雅黑", 20, "bold"),
    fg="#333333"
)
title_label.pack(pady=15)

subtitle_label = tk.Label(
    window,
    text="输入待办事项，点击添加吧！",
    font=("微软雅黑", 10),
    fg="#888888"
)
subtitle_label.pack(pady=5)

# ==================== 输入区域 ====================

input_frame = tk.Frame(window)
input_frame.pack(pady=15)

entry = tk.Entry(
    input_frame,
    font=("微软雅黑", 13),
    width=25
)
entry.pack(side=tk.LEFT, padx=(0, 5))

add_btn = tk.Button(
    input_frame,
    text="添加 ✅",
    font=("微软雅黑", 12),
    bg="#4CAF50",
    fg="white",
    padx=10,
    pady=5
)
add_btn.pack(side=tk.LEFT)

# ==================== 列表区域 ====================

list_label = tk.Label(
    window,
    text="📋 待办事项",
    font=("微软雅黑", 12, "bold"),
    fg="#555555"
)
list_label.pack(pady=(20, 5))

listbox = tk.Listbox(
    window,
    font=("微软雅黑", 12),
    height=15,
    width=40,
    selectbackground="#C8E6C9",
    selectforeground="#333333"
)
listbox.pack(pady=5)

# ==================== 核心功能 ====================

def add_todo():
    """获取输入框内容，添加到列表中"""
    # 获取并清理文字
    text = entry.get().strip()

    if text:
        # 添加到列表框
        listbox.insert(tk.END, text)
        # 清空输入框
        entry.delete(0, tk.END)
        # 控制台确认
        print(f"✅ 添加了：{text}")
    else:
        print("⚠️ 请输入待办事项！")

# 绑定按钮点击
add_btn.config(command=add_todo)

# 绑定回车键
def on_enter_press(event):
    add_todo()

entry.bind("<Return>", on_enter_press)

# ==================== 运行 ====================

# 让光标默认停在输入框里
entry.focus()

window.mainloop()
```

---

## 🧠 本课小结

| 学到的知识 | 是什么 | 怎么用 |
|-----------|--------|--------|
| `Entry` | 单行输入框 | `entry = tk.Entry(window)` |
| `.get()` | 获取输入内容 | `text = entry.get()` |
| `.strip()` | 去掉首尾空格 | `text = text.strip()` |
| `.delete(0, END)` | 清空输入框 | `entry.delete(0, tk.END)` |
| `Listbox` | 列表框 | `listbox = tk.Listbox(window)` |
| `.insert(END, x)` | 添加到列表 | `listbox.insert(tk.END, "内容")` |
| `if text:` | 判断非空 | 空字符串是 `False` |
| `Frame` | 容器框架 | `frame = tk.Frame(window)` |
| `.bind()` | 绑定键盘事件 | `entry.bind("<Return>", 函数)` |

---

## 📖 下节课预告

第 4 课：**选中和删除 — 让备忘录能管理事项**

我们将学会如何**选中**列表中的某条事项，然后**删除**它。这会引入 `curselection()` 获取选中项、`if...else` 深入使用，以及 `messagebox` 弹出确认提示框。
