# 第 6 课 · 数据存文件 — 关了也不丢

---

## 🎯 本课目标

- 学会 `open()` 打开文件
- 学会 `.read()` 读取文件内容
- 学会 `.write()` 写入文件
- 学会 `with` 语句安全操作文件
- 学会 `str.split()` 和 `str.join()` 分割与合并字符串
- 实现保存 → 下次打开程序**自动加载数据**

---

## 📚 新知识

### 6.1 为什么需要文件？

到现在为止，我们添加的待办事项都存在**内存**里。关闭程序后，内存数据就消失了。

**文件**（File）是存在**硬盘**上的数据，关了电脑也不会丢。就像你的 Word 文档——保存后，下次打开还在。

| 存储方式 | 位置 | 持久性 |
|----------|------|--------|
| 变量 / 列表 | 内存（RAM） | ❌ 关程序就消失 |
| 文件 | 硬盘（SSD/HDD） | ✅ 永久保存 |

### 6.2 打开文件：`open()`

```python
# 基本语法
file = open("文件名", "模式")
# ... 读或写 ...
file.close()  # 用完要关闭！
```

**文件模式**：

| 模式 | 说明 | 文件不存在时 |
|------|------|-------------|
| `"r"` | 只读（read） | ❌ 报错 |
| `"w"` | 写入（write），覆盖原内容 | ✅ 自动创建 |
| `"a"` | 追加（append），在原内容后添加 | ✅ 自动创建 |
| `"r+"` | 读写 | ❌ 报错 |

```python
# 写入模式
file = open("todos.txt", "w")   # 打开 todos.txt，准备写入
file.write("学Python\n")         # 写入一行
file.write("写作业\n")           # 再写一行
file.close()                     # 关闭文件（重要！）

# 读取模式
file = open("todos.txt", "r")   # 打开文件，准备读取
content = file.read()            # 读取全部内容
print(content)
file.close()
```

> ⚠️ **别忘了 `.close()`！** 如果不关闭文件，数据可能还没真正写入硬盘，而且会占用系统资源。

### 6.3 `with` 语句 — 自动关闭文件（推荐！）

`with` 语句能**自动关闭文件**，不需要手动写 `.close()`，更安全。

```python
# ❌ 旧方式：需要手动 close
file = open("todos.txt", "r")
content = file.read()
file.close()  # 容易忘！

# ✅ with 方式：自动关闭（推荐！）
with open("todos.txt", "r") as file:
    content = file.read()
# 出了 with 语句块，文件自动关闭
```

> 💡 **`as` 的作用**：`as file` 就是给打开的文件对象起个名字，后面用 `file` 来操作它。类似 `import tkinter as tk`。

**读文件常用方法**：

```python
with open("todos.txt", "r") as f:
    all_text = f.read()          # 一次读取全部
    all_lines = f.readlines()    # 读取所有行，返回列表
    one_line = f.readline()      # 读取一行
    for line in f:               # 逐行遍历（推荐）
        print(line.strip())
```

### 6.4 字符串的 `.split()` 和 `.join()`

把字符串和列表互相转换：

```python
# split()：字符串 → 列表（按分隔符切分）
text = "学Python,写作业,做运动"
items = text.split(",")     # ["学Python", "写作业", "做运动"]

text = "苹果 香蕉 橘子"
items = text.split()        # 默认按空白字符分割 → ["苹果", "香蕉", "橘子"]

# join()：列表 → 字符串（用分隔符连接）
items = ["学Python", "写作业", "做运动"]
text = ",".join(items)      # "学Python,写作业,做运动"

text = "\n".join(items)     # "学Python\n写作业\n做运动"
```

### 6.5 文件格式设计

我们需要把每条待办的**文字**和**完成状态**一起存到文件中。

**方案：每行一条，用 `|` 分隔状态和内容**

```
0|学Python
1|写作业
0|做运动
```

- `0` = 未完成（`False`）
- `1` = 已完成（`True`）
- `|` = 分隔符

**保存流程**：
```
todos 列表 → 格式化成字符串 → 写入文件
```

**加载流程**：
```
读取文件 → 按行分割 → 解析每行 → 重建 todos 列表和数据
```

---

## 💻 写代码

### 步骤 1：框架

新建 `lesson6.py`，从第 5 课的代码开始修改。

### 步骤 2：定义文件路径

```python
import os  # os 模块用于处理文件路径

# 数据文件路径（和程序在同一个文件夹）
DATA_FILE = "todos.txt"
```

### 步骤 3：保存函数

```python
def save_todos():
    """将待办列表保存到文件中"""
    with open(DATA_FILE, "w", encoding="utf-8") as file:
        for todo in todos:
            # 格式：状态|内容
            # 0 = 未完成, 1 = 已完成
            status = "1" if todo["done"] else "0"
            line = f"{status}|{todo['text']}\n"
            file.write(line)
    print(f"💾 已保存 {len(todos)} 条待办到文件")
```

> 💡 **`encoding="utf-8"`** 指定文件编码为 UTF-8，这样可以正确存储**中文**。如果不写这个，在 Windows 上可能出现乱码。

### 步骤 4：加载函数

```python
def load_todos():
    """从文件中加载待办列表"""
    import os  # 确保导入

    # 如果文件不存在，直接返回（第一次运行时还没有文件）
    if not os.path.exists(DATA_FILE):
        print("📂 数据文件不存在，创建新的备忘录")
        return

    with open(DATA_FILE, "r", encoding="utf-8") as file:
        for line in file:
            line = line.strip()  # 去掉换行符
            if not line:          # 跳过空行
                continue

            # 解析：按 | 分割
            parts = line.split("|")
            if len(parts) == 2:
                status_str, text = parts
                todo = {
                    "text": text,
                    "done": status_str == "1"  # "1" -> True, "0" -> False
                }
                todos.append(todo)

                # 添加到 Listbox 显示
                listbox.insert(tk.END, text)

                # 根据状态设置样式
                index = listbox.size() - 1
                if todo["done"]:
                    listbox.itemconfig(index, fg="gray")
                    listbox.itemconfig(index, font=("微软雅黑", 12, "overstrike"))

    print(f"📂 已从文件加载 {len(todos)} 条待办")
```

**逐行解析**：

| 代码 | 解释 |
|------|------|
| `os.path.exists(DATA_FILE)` | 检查文件是否存在 |
| `line.strip()` | 去掉每行末尾的 `\n` |
| `if not line: continue` | 跳过空行 |
| `line.split("\|")` | 按 `\|` 分割，得到 `["0", "学Python"]` |
| `status_str == "1"` | 字符串 `"1"` → 布尔 `True`，"0" → `False` |
| `listbox.size() - 1` | 新插入项的索引 = 当前总数 - 1 |

### 步骤 5：每次操作后保存

修改 `add_todo`、`delete_todo`、`toggle_done`、`clear_all`，在每次修改数据后调用 `save_todos()`：

```python
def add_todo():
    # ... 原有代码 ...
        todos.append(todo)
        listbox.insert(tk.END, text)
        entry.delete(0, tk.END)
        save_todos()          # ⬅ 新增：保存到文件
        update_status()

def toggle_done():
    # ... 原有代码 ...
    if todo["done"]:
        # ...
    else:
        # ...
    save_todos()              # ⬅ 新增：保存到文件
    update_status()

def delete_todo():
    # ... 原有代码 ...
    if result:
        listbox.delete(index)
        todos.pop(index)
        save_todos()          # ⬅ 新增：保存到文件
        update_status()

def clear_all():
    # ... 原有代码 ...
    if result:
        listbox.delete(0, tk.END)
        todos.clear()
        save_todos()          # ⬅ 新增：保存到文件
        update_status()
```

### 步骤 6：程序启动时加载数据

在 `window.mainloop()` 之前调用：

```python
# ==================== 启动加载 ====================

load_todos()   # 从文件加载已有数据
update_status()
entry.focus()
window.mainloop()
```

### 步骤 7：窗口关闭时自动保存

tkinter 窗口关闭时，可以绑定一个保存操作（作为额外的安全措施）：

```python
def on_closing():
    """窗口关闭前的处理"""
    save_todos()
    window.destroy()  # 真正关闭窗口

# 绑定窗口关闭事件
window.protocol("WM_DELETE_WINDOW", on_closing)
```

---

## ▶️ 运行看效果

1. 运行程序，添加几条待办（如"学Python"、"写作业"）
2. 标记其中一条为完成
3. **关闭程序**
4. 检查程序目录，应该生成了 `todos.txt` 文件，内容是：
   ```
   0|学Python
   1|写作业
   ```
5. **重新运行程序**——待办事项都还在！完成的也保持灰色+删除线！

> 📸 *（此处放置截图：程序界面 + 文件内容 side-by-side）*

---

## ✏️ 小练习

1. **手动改文件**：用记事本打开 `todos.txt`，添加一行 `0|新任务`，保存后重新运行程序。看看会怎样？
2. **改分隔符**：把分隔符 `|` 改成 `,` 或 `||`，保证程序仍然正常运行（两边都要改）
3. **显示文件路径**：在状态栏里显示数据文件保存的位置
4. **挑战题**：用 **CSV 格式**（Comma-Separated Values，逗号分隔值）代替 `|` 分隔。CSV 是更标准的格式，可以用 Excel 打开！

---

## 📋 本课完整代码

```python
# ============================================
# 第 6 课：数据存文件 — 关了也不丢
# ============================================

import tkinter as tk
from tkinter import messagebox
import os

# ==================== 配置 ====================

DATA_FILE = "todos.txt"   # 数据文件名

# ==================== 创建窗口 ====================

window = tk.Tk()
window.title("我的备忘录")
window.geometry("450x600")

# ==================== 数据结构 ====================

todos = []  # 存储待办字典的列表

# ==================== 文件操作 ====================

def save_todos():
    """将待办列表保存到文件中"""
    with open(DATA_FILE, "w", encoding="utf-8") as file:
        for todo in todos:
            status = "1" if todo["done"] else "0"
            line = f"{status}|{todo['text']}\n"
            file.write(line)
    print(f"💾 已保存 {len(todos)} 条待办到文件")

def load_todos():
    """从文件中加载待办列表"""
    if not os.path.exists(DATA_FILE):
        print("📂 数据文件不存在，创建新的备忘录")
        return

    with open(DATA_FILE, "r", encoding="utf-8") as file:
        for line in file:
            line = line.strip()
            if not line:
                continue

            parts = line.split("|")
            if len(parts) == 2:
                status_str, text = parts
                todo = {"text": text, "done": status_str == "1"}
                todos.append(todo)

                listbox.insert(tk.END, text)

                if todo["done"]:
                    index = listbox.size() - 1
                    listbox.itemconfig(index, fg="gray")
                    listbox.itemconfig(index, font=("微软雅黑", 12, "overstrike"))

    print(f"📂 已从文件加载 {len(todos)} 条待办")

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
    text="数据自动保存，关了也不丢！",
    font=("微软雅黑", 10),
    fg="#888888"
)
subtitle_label.pack(pady=5)

# ==================== 按钮区域 ====================

input_frame = tk.Frame(window)
input_frame.pack(pady=15)

entry = tk.Entry(input_frame, font=("微软雅黑", 13), width=18)
entry.pack(side=tk.LEFT, padx=(0, 3))

add_btn = tk.Button(
    input_frame, text="添加 ✅", font=("微软雅黑", 11),
    bg="#4CAF50", fg="white", padx=6, pady=5
)
add_btn.pack(side=tk.LEFT, padx=(0, 2))

toggle_btn = tk.Button(
    input_frame, text="标记 ✔️", font=("微软雅黑", 11),
    bg="#2196F3", fg="white", padx=6, pady=5
)
toggle_btn.pack(side=tk.LEFT, padx=(0, 2))

delete_btn = tk.Button(
    input_frame, text="删除 ❌", font=("微软雅黑", 11),
    bg="#f44336", fg="white", padx=6, pady=5
)
delete_btn.pack(side=tk.LEFT)

# ==================== 列表 + 滚动条 ====================

list_frame = tk.Frame(window)
list_frame.pack(pady=5, fill=tk.BOTH, expand=True, padx=20)

scrollbar = tk.Scrollbar(list_frame)
scrollbar.pack(side=tk.RIGHT, fill=tk.Y)

listbox = tk.Listbox(
    list_frame,
    font=("微软雅黑", 12),
    height=15,
    selectbackground="#C8E6C9",
    selectforeground="#333333",
    yscrollcommand=scrollbar.set
)
listbox.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
scrollbar.config(command=listbox.yview)

# ==================== 底部区域 ====================

bottom_frame = tk.Frame(window)
bottom_frame.pack(pady=5, fill=tk.X, padx=20)

clear_btn = tk.Button(
    bottom_frame, text="清空全部 🗑️", font=("微软雅黑", 9),
    bg="#FF9800", fg="white", padx=10, pady=3
)
clear_btn.pack(side=tk.LEFT)

status_label = tk.Label(
    bottom_frame, text="共 0 条待办", font=("微软雅黑", 9), fg="#999999"
)
status_label.pack(side=tk.RIGHT)

# ==================== 核心功能 ====================

def update_status():
    total = len(todos)
    status_label.config(text=f"共 {total} 条待办")

def add_todo():
    text = entry.get().strip()
    if text:
        todo = {"text": text, "done": False}
        todos.append(todo)
        listbox.insert(tk.END, text)
        entry.delete(0, tk.END)
        save_todos()
        update_status()
        print(f"✅ 添加了：{text}")
    else:
        messagebox.showwarning("提示", "请输入待办事项！")

def toggle_done():
    if listbox.size() == 0:
        return
    selected = listbox.curselection()
    if not selected:
        messagebox.showwarning("提示", "请先选择要标记的事项！")
        return

    index = selected[0]
    todo = todos[index]
    todo["done"] = not todo["done"]

    if todo["done"]:
        listbox.itemconfig(index, fg="gray")
        listbox.itemconfig(index, font=("微软雅黑", 12, "overstrike"))
    else:
        listbox.itemconfig(index, fg="black")
        listbox.itemconfig(index, font=("微软雅黑", 12))

    save_todos()
    update_status()

def delete_todo():
    if listbox.size() == 0:
        messagebox.showwarning("提示", "列表为空！")
        return
    selected = listbox.curselection()
    if not selected:
        messagebox.showwarning("提示", "请先选择要删除的事项！")
        return

    index = selected[0]
    todo = todos[index]
    result = messagebox.askyesno("确认删除", f"确定要删除「{todo['text']}」吗？")
    if result:
        listbox.delete(index)
        todos.pop(index)
        save_todos()
        update_status()

def clear_all():
    if listbox.size() == 0:
        return
    result = messagebox.askyesno("确认清空", f"列表中有 {listbox.size()} 条事项，确定全部清空吗？")
    if result:
        listbox.delete(0, tk.END)
        todos.clear()
        save_todos()
        update_status()

def on_closing():
    """窗口关闭时自动保存"""
    save_todos()
    window.destroy()

# ==================== 绑定事件 ====================

add_btn.config(command=add_todo)
toggle_btn.config(command=toggle_done)
delete_btn.config(command=delete_todo)
clear_btn.config(command=clear_all)

entry.bind("<Return>", lambda e: add_todo())
window.bind("<Delete>", lambda e: delete_todo())
listbox.bind("<Double-1>", lambda e: toggle_done())
window.protocol("WM_DELETE_WINDOW", on_closing)

# ==================== 启动 ====================

load_todos()     # 从文件加载数据
update_status()
entry.focus()
window.mainloop()
```

---

## 🧠 本课小结

| 学到的知识 | 是什么 | 怎么用 |
|-----------|--------|--------|
| `open()` | 打开文件 | `open("文件名", "模式")` |
| `"w"` 模式 | 写入（覆盖） | `open("a.txt", "w")` |
| `"r"` 模式 | 读取 | `open("a.txt", "r")` |
| `with` 语句 | 自动关闭 | `with open(...) as f:` |
| `.write()` | 写内容 | `file.write("内容\n")` |
| `.strip()` | 去首尾空白 | `line.strip()` |
| `.split()` | 字符串→列表 | `"a,b".split(",")` → `["a","b"]` |
| `.join()` | 列表→字符串 | `",".join(["a","b"])` → `"a,b"` |
| `os.path.exists()` | 判断文件是否存在 | `os.path.exists("a.txt")` |
| `encoding="utf-8"` | 指定编码 | 正确显示中文 |
| `.protocol()` | 窗口关闭事件 | `window.protocol("WM_DELETE_WINDOW", fn)` |

---

## 📖 下节课预告

第 7 课：**菜单栏和快捷键 — 让程序更专业**

加入真正的菜单栏（文件 / 编辑 / 帮助），配上键盘快捷键（Ctrl+S 保存、Ctrl+N 新建），让备忘录看起来像一个真正的软件！
