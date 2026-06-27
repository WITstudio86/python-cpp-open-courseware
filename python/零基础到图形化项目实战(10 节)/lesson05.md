# 第 5 课 · 标记已完成 — 样式变化与字典

---

## 🎯 本课目标

- 学会**字典（dict）**——Python 的键值对容器
- 用字典管理每条待办事项的**完成状态**
- 给已完成的待办加上**删除线**和**灰色文字**效果
- 学会 `itemconfig()` 修改 Listbox 中单条数据的样式
- 实现"标记已完成 / 取消完成 / 切换状态"功能

---

## 📚 新知识

### 5.1 字典 dict — 键值对容器

之前我们学了**列表（list）**，列表用数字索引 `[0]`、`[1]`、`[2]` 来访问数据。

**字典（dict）** 则用**自定义的名字**（键 key）来访问数据（值 value）。

```python
# 列表：用数字索引
student_list = ["小明", 12, "六年级"]
name = student_list[0]  # 得记住 0 是名字

# 字典：用自定义键名 ✅ 更清晰！
student_dict = {
    "name": "小明",
    "age": 12,
    "grade": "六年级"
}
name = student_dict["name"]  # 一看就懂！
```

**字典的基本操作**：

```python
# 创建字典
todo_item = {
    "text": "学Python",
    "done": False
}

# 访问值
print(todo_item["text"])   # "学Python"
print(todo_item["done"])   # False

# 修改值
todo_item["done"] = True   # 标记为已完成

# 添加新键值对
todo_item["category"] = "学习"

# 检查键是否存在
if "done" in todo_item:
    print("有 done 这个键")
```

> 💡 **类比**：字典就像真正的字典📖。你要查"apple"这个词（键），就能找到"苹果"这个解释（值）。你不能用页码（数字索引）来查。

### 5.2 用字典列表管理所有待办

一条待办用一个字典来表示，所有待办放在一个列表里：

```python
# 数据结构设计
todos = [
    {"text": "学Python", "done": False},
    {"text": "写作业", "done": True},
    {"text": "做运动", "done": False},
]

# 遍历所有待办
for item in todos:
    status = "✅" if item["done"] else "⬜"
    print(f"{status} {item['text']}")
```

输出：
```
⬜ 学Python
✅ 写作业
⬜ 做运动
```

### 5.3 for 循环 — 遍历数据

`for` 循环用于**重复执行**一段代码，每次从容器中取出一个元素。

```python
# 遍历列表
fruits = ["苹果", "香蕉", "橘子"]
for fruit in fruits:
    print(f"我喜欢吃{fruit}")

# 遍历字典的键值对
student = {"name": "小明", "age": 12}
for key, value in student.items():
    print(f"{key}: {value}")
```

**for 循环的结构**：

```python
for 临时变量 in 容器:
    要重复执行的代码（注意缩进！）
```

> 💡 **`for` + `in` 就是"对于……里面的每一个……"**。
> 读作："**对于** fruits **里面的**每一个 fruit，执行下面的代码。"

### 5.4 Listbox 样式操作

之前我们只能往 Listbox 里插入文字，现在我们来修改**单条数据的外观**。

**`itemconfig(index, **options)`** 用于修改指定索引项的样式：

```python
# 给已完成的事项加删除线 + 灰色
listbox.itemconfig(index, fg="gray")

# 给已完成的事项加删除线
listbox.itemconfig(index, font=("微软雅黑", 12, "overstrike"))

# 取消完成状态（恢复原样）
listbox.itemconfig(index, fg="black")
listbox.itemconfig(index, font=("微软雅黑", 12))
```

> 💡 **`itemconfig()`** = item（条目）+ config（配置）= 配置某一条的样式。

**字体样式**的 `font` 参数：
- `"normal"` — 普通
- `"bold"` — 加粗
- `"italic"` — 倾斜
- `"overstrike"` — 删除线
- `"underline"` — 下划线

多个样式可以组合：`font=("微软雅黑", 12, "overstrike", "bold")`

### 5.5 数据结构升级

之前 Listbox 只存文字，现在需要**把 Listbox 显示和字典数据关联起来**。

**核心思路**：
1. 添加待办时，同时创建字典（`{"text": ..., "done": False}`）存到列表 `todos` 中
2. Listbox 只显示文字（带样式标记状态）
3. 通过 Listbox 的索引，找到 `todos` 中对应的字典

```python
todos = []  # 存储所有待办的字典列表

def add_todo():
    text = entry.get().strip()
    if text:
        todo = {"text": text, "done": False}  # 创建字典
        todos.append(todo)                     # 存入列表
        listbox.insert(tk.END, text)           # 显示在 Listbox
```

---

## 💻 写代码

### 步骤 1：框架

新建 `lesson5.py`，从第 4 课的代码骨架开始。

### 步骤 2：数据结构

```python
# ==================== 数据结构 ====================

todos = []  # 存储所有待办事项的字典列表
# 每个字典的格式：{"text": "待办内容", "done": False/True}
```

### 步骤 3：重构添加功能

```python
def add_todo():
    """添加待办事项（同时更新数据和显示）"""
    text = entry.get().strip()
    if text:
        # 1. 创建数据字典
        todo = {"text": text, "done": False}
        todos.append(todo)

        # 2. 添加到 Listbox 显示
        listbox.insert(tk.END, text)
        entry.delete(0, tk.END)
        print(f"✅ 添加了：{text}")
    else:
        messagebox.showwarning("提示", "请输入待办事项！")
```

### 步骤 4：实现"标记已完成"功能

这是本课的**核心新功能**：

```python
def toggle_done():
    """切换选中事项的完成状态"""
    # 检查列表是否为空
    if listbox.size() == 0:
        return

    # 检查是否有选中
    selected = listbox.curselection()
    if not selected:
        messagebox.showwarning("提示", "请先选择要标记的事项！")
        return

    # 获取索引
    index = selected[0]

    # 切换状态
    todo = todos[index]                     # 取出对应字典
    todo["done"] = not todo["done"]         # 翻转 True↔False

    # 根据新状态更新显示样式
    if todo["done"]:
        # 已完成：灰色 + 删除线
        listbox.itemconfig(index, fg="gray")
        listbox.itemconfig(index, font=("微软雅黑", 12, "overstrike"))
        print(f"✅ 标记完成：{todo['text']}")
    else:
        # 未完成：恢复原样
        listbox.itemconfig(index, fg="black")
        listbox.itemconfig(index, font=("微软雅黑", 12))
        print(f"🔄 取消完成：{todo['text']}")
```

> 💡 **`not todo["done"]`** — `not` 是取反操作符。如果原来是 `True`，`not True` = `False`；原来是 `False`，`not False` = `True`。这样就能一键切换！

### 步骤 5：修改删除功能

删除时要**同时更新数据和显示**：

```python
def delete_todo():
    """删除选中的待办事项"""
    if listbox.size() == 0:
        messagebox.showwarning("提示", "列表为空！")
        return

    selected = listbox.curselection()
    if not selected:
        messagebox.showwarning("提示", "请先选择要删除的事项！")
        return

    index = selected[0]
    todo = todos[index]  # 获取对应的字典

    result = messagebox.askyesno(
        "确认删除",
        f"确定要删除「{todo['text']}」吗？"
    )

    if result:
        listbox.delete(index)   # 删除显示
        todos.pop(index)        # 删除数据（pop = 弹出指定位置的元素）
        print(f"❌ 删除了：{todo['text']}")
```

> 💡 **`.pop(index)`** — 从列表中移除指定位置的元素，和 `.delete()` 不同：
> - `.delete(值)` — 按值删除
> - `.pop(索引)` — 按位置删除并返回该元素
> - `.remove(值)` — 按值删除第一个匹配项

### 步骤 6：修改清空功能

```python
def clear_all():
    """清空全部事项"""
    if listbox.size() == 0:
        messagebox.showwarning("提示", "列表已经是空的！")
        return

    result = messagebox.askyesno(
        "确认清空",
        f"列表中有 {listbox.size()} 条事项，确定全部清空吗？"
    )

    if result:
        listbox.delete(0, tk.END)  # 清空显示
        todos.clear()              # 清空数据（clear() 清空整个列表）
        print("🗑️ 已清空全部待办事项")
```

### 步骤 7：添加"标记"按钮

在按钮区域添加一个"标记完成"按钮：

```python
# 标记完成/取消按钮
toggle_btn = tk.Button(
    input_frame,
    text="标记 ✔️",
    font=("微软雅黑", 11),
    bg="#2196F3",
    fg="white",
    padx=8,
    pady=5,
    command=toggle_done
)
toggle_btn.pack(side=tk.LEFT, padx=(5, 0))
```

### 步骤 8：双击切换完成状态

让用户**双击**列表中的事项也能切换状态：

```python
def on_double_click(event):
    """双击列表项时触发"""
    toggle_done()

listbox.bind("<Double-1>", on_double_click)  # Double-1 = 鼠标左键双击
```

> 💡 **事件名称**：`<Double-1>` = 鼠标左键双击，`<Button-1>` = 单击左键，`<Button-3>` = 单击右键。

---

## ▶️ 运行看效果

| 操作 | 预期结果 |
|------|----------|
| 添加 3 条待办：学Python、写作业、做运动 | 列表显示 3 条，均为黑色正常字体 |
| 选中"学Python"，点"标记 ✔️" | 文字变灰 + 删除线 |
| 再次选中"学Python"，点"标记 ✔️" | 恢复黑色正常字体 |
| 双击"写作业" | 切换完成状态（灰/黑） |
| 删除一条已完成的待办 | 数据同步删除，不影响其他待办 |
| 清空全部 | 数据和显示都清空 |

> 📸 *（此处放置截图：有已完成条目的列表，删除线效果）*

---

## ✏️ 小练习

1. **改标记按钮**：让按钮的文字随着选中项状态变化——如果选中已完成的，按钮显示"取消完成 🔄"；如果选中未完成的，按钮显示"标记完成 ✔️"
2. **统计完成数**：在底部状态栏显示 `"共 5 条，已完成 2 条"`
3. **全部标记**：加一个按钮，一键把所有事项标记为已完成
4. **挑战题**：用右键弹出菜单（`Menu` + `post()`），包含"标记完成"和"删除"选项

---

## 📋 本课完整代码

```python
# ============================================
# 第 5 课：标记已完成 — 样式变化与字典
# ============================================

import tkinter as tk
from tkinter import messagebox

# ==================== 创建窗口 ====================

window = tk.Tk()
window.title("我的备忘录")
window.geometry("450x600")

# ==================== 数据结构 ====================

todos = []  # 存储待办字典的列表
# 格式：[{"text": "内容", "done": False}, ...]

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
    text="双击或点按钮标记完成！已完成会用删除线显示",
    font=("微软雅黑", 10),
    fg="#888888"
)
subtitle_label.pack(pady=5)

# ==================== 按钮区域 ====================

input_frame = tk.Frame(window)
input_frame.pack(pady=15)

entry = tk.Entry(
    input_frame,
    font=("微软雅黑", 13),
    width=18
)
entry.pack(side=tk.LEFT, padx=(0, 3))

add_btn = tk.Button(
    input_frame,
    text="添加 ✅",
    font=("微软雅黑", 11),
    bg="#4CAF50",
    fg="white",
    padx=6,
    pady=5
)
add_btn.pack(side=tk.LEFT, padx=(0, 2))

toggle_btn = tk.Button(
    input_frame,
    text="标记 ✔️",
    font=("微软雅黑", 11),
    bg="#2196F3",
    fg="white",
    padx=6,
    pady=5
)
toggle_btn.pack(side=tk.LEFT, padx=(0, 2))

delete_btn = tk.Button(
    input_frame,
    text="删除 ❌",
    font=("微软雅黑", 11),
    bg="#f44336",
    fg="white",
    padx=6,
    pady=5
)
delete_btn.pack(side=tk.LEFT)

# ==================== 列表 + 滚动条区域 ====================

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
    bottom_frame,
    text="清空全部 🗑️",
    font=("微软雅黑", 9),
    bg="#FF9800",
    fg="white",
    padx=10,
    pady=3
)
clear_btn.pack(side=tk.LEFT)

# 状态标签
status_label = tk.Label(
    bottom_frame,
    text="共 0 条待办",
    font=("微软雅黑", 9),
    fg="#999999"
)
status_label.pack(side=tk.RIGHT)

# ==================== 核心功能 ====================

def update_status():
    """更新状态栏显示"""
    total = len(todos)
    done_count = sum(1 for t in todos if t["done"])
    status_label.config(text=f"共 {total} 条待办")

def add_todo():
    """添加待办事项"""
    text = entry.get().strip()
    if text:
        todo = {"text": text, "done": False}
        todos.append(todo)
        listbox.insert(tk.END, text)
        entry.delete(0, tk.END)
        update_status()
        print(f"✅ 添加了：{text}")
    else:
        messagebox.showwarning("提示", "请输入待办事项！")

def toggle_done():
    """切换完成状态"""
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
        print(f"✅ 标记完成：{todo['text']}")
    else:
        listbox.itemconfig(index, fg="black")
        listbox.itemconfig(index, font=("微软雅黑", 12))
        print(f"🔄 取消完成：{todo['text']}")

    update_status()

def delete_todo():
    """删除选中的待办事项"""
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
        update_status()
        print(f"❌ 删除了：{todo['text']}")

def clear_all():
    """清空全部事项"""
    if listbox.size() == 0:
        return
    result = messagebox.askyesno(
        "确认清空",
        f"列表中有 {listbox.size()} 条事项，确定全部清空吗？"
    )
    if result:
        listbox.delete(0, tk.END)
        todos.clear()
        update_status()
        print("🗑️ 已清空")

# ==================== 绑定事件 ====================

add_btn.config(command=add_todo)
toggle_btn.config(command=toggle_done)
delete_btn.config(command=delete_todo)
clear_btn.config(command=clear_all)

entry.bind("<Return>", lambda e: add_todo())
window.bind("<Delete>", lambda e: delete_todo())
listbox.bind("<Double-1>", lambda e: toggle_done())

# ==================== 运行 ====================

entry.focus()
update_status()
window.mainloop()
```

---

## 🧠 本课小结

| 学到的知识 | 是什么 | 怎么用 |
|-----------|--------|--------|
| `dict` | 键值对容器 | `{"key": "value"}` |
| `todo["done"]` | 访问字典值 | `todo["done"]` |
| `not` | 布尔取反 | `not True` → `False` |
| `for ... in ...` | 遍历循环 | `for item in todos:` |
| `itemconfig()` | 修改列表项样式 | `listbox.itemconfig(i, fg="gray")` |
| `overstrike` | 删除线字体 | `font=("微软雅黑", 12, "overstrike")` |
| `.pop(index)` | 按索引移除 | `todos.pop(0)` |
| `.clear()` | 清空列表 | `todos.clear()` |
| `<Double-1>` | 双击事件 | `listbox.bind("<Double-1>", fn)` |

---

## 📖 下节课预告

第 6 课：**数据存文件 — 关了也不丢**

关闭程序后待办就消失了？No！我们将学会**文件读写**，把待办事项保存到 `.txt` 文件中。下次打开程序时自动加载，数据不再丢失！
