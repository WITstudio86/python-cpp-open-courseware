# 第 9 课 · 搜索与过滤 — 让备忘录更好用

---

## 🎯 本课目标

- 学会**搜索过滤**— 在大量待办中快速找到目标
- 学会**按类别筛选**— 只看某个分类的事项
- 深入 `for` 循环 — 遍历和条件过滤
- 学会 `StringVar` — tkinter 的字符串变量（双向绑定）
- 学会 `trace` 模式 — 实时监听变量变化（输入即搜索）
- 学会**多 Frame 嵌套布局**的进阶技巧

---

## 📚 新知识

### 9.1 StringVar — tkinter 的变量绑定

之前我们要获取输入框内容，需要调用 `entry.get()`。但如果我们想**实时监听**输入框的变化（比如输入即搜索），就需要 `StringVar`。

```python
# 创建一个 tkinter 字符串变量
search_var = tk.StringVar()

# 绑定到 Entry 控件
entry = ttk.Entry(window, textvariable=search_var)

# 读取值
print(search_var.get())  # 获取当前输入框内容

# 设置值
search_var.set("新内容")  # 输入框会自动更新！

# 监听变化（核心！）
search_var.trace("w", callback_function)
```

**`trace` 模式**：

| 模式 | 说明 |
|------|------|
| `"w"` | 当变量被**写入**（修改）时触发 |
| `"r"` | 当变量被**读取**时触发 |
| `"u"` | 当变量被**删除**时触发 |

> 💡 **`trace("w", callback)`** 是实现"输入即搜索"的关键！每当用户在搜索框输入一个字，`callback` 就会被调用，实时更新列表显示。

### 9.2 列表过滤的逻辑

搜索/过滤的核心流程：

```
原始数据 (todos) → 应用过滤条件 → 刷新 Listbox 显示
```

```python
def filter_todos():
    """根据搜索词和类别过滤待办列表"""
    keyword = search_var.get().lower()     # 获取搜索词，转小写
    category_filter = filter_combo.get()   # 获取类别筛选

    # 1. 清空当前 Listbox
    listbox.delete(0, tk.END)

    # 2. 遍历所有待办，逐一判断是否匹配
    for i, todo in enumerate(todos):
        # 判断搜索词是否匹配（文字中包含关键词即可）
        text_match = keyword in todo["text"].lower()

        # 判断类别是否匹配
        category_match = (
            category_filter == "全部 📋" or
            category_filter == todo["category"]
        )

        # 两个条件都满足，才显示
        if text_match and category_match:
            display_text = f"[{todo['category']}] {todo['text']}"
            listbox.insert(tk.END, display_text)

            # 恢复完成状态样式
            if todo["done"]:
                idx = listbox.size() - 1
                listbox.itemconfig(idx, fg="gray")
                listbox.itemconfig(idx, font=("微软雅黑", 12, "overstrike"))
```

**过滤 vs 删除**：
- **过滤**：数据还在 `todos` 里，只是**暂时不显示**在 Listbox 中
- **删除**：从 `todos` 列表中**彻底移除**

### 9.3 `in` 运算符 — 判断包含关系

```python
# 字符串包含
print("Python" in "学Python编程")   # True
print("Java" in "学Python编程")     # False

# 列表包含
print(3 in [1, 2, 3, 4])           # True
print(5 in [1, 2, 3, 4])           # False

# 字典包含（判断键）
print("name" in {"name": "小明"})   # True
```

> 💡 **`in` 用于搜索**：`keyword in todo["text"].lower()` 判断搜索关键词是否出现在待办文字中。`lower()` 把两边都转成小写，实现**大小写不敏感**的搜索。

### 9.4 实时搜索 vs 按钮搜索

两种搜索触发方式：

| 方式 | 触发时机 | 优点 | 缺点 |
|------|----------|------|------|
| 按钮搜索 | 点"搜索"按钮 | 简单直观 | 需要额外操作 |
| **实时搜索** ✅ | 输入时自动触发 | 体验流畅 | 代码稍复杂 |

本课使用**实时搜索**（`trace`），输入即搜，体验最好。

### 9.5 过滤时的索引问题

⚠️ **关键问题**：过滤后 Listbox 中显示的条目索引，和 `todos` 列表中的实际索引**不再一致**！

```
原始数据 (todos):     [0] 学Python    [1] 写作业    [2] 做运动
过滤后显示 (Listbox): [0] 学Python    [1] 做运动      (写作业被过滤掉了)

用户在 Listbox 中选中 [1] "做运动"
→ 但在 todos 中 "做运动" 的索引是 [2]！
```

**解决方案**：在 `todos` 中加一个临时 `_display_index` 字段，记录它在过滤后 Listbox 中的位置。或者，用每个 todo 的 `text` + `category` 拼成一个唯一 ID 来匹配。

**本课采用更简单的方法**：操作时先在过滤后的 Listbox 中找到显示的文字，再用文字和类别反向匹配 `todos` 中的数据。

```python
def find_todo_by_display(display_text):
    """根据 Listbox 中显示的文本，找到 todos 中对应的字典"""
    for todo in todos:
        expected = f"[{todo['category']}] {todo['text']}"
        if expected == display_text:
            return todo
    return None
```

### 9.6 边界情况处理

过滤功能需要考虑的特殊情况：

| 情况 | 处理方式 |
|------|----------|
| 搜索框为空 | 显示所有待办（不过滤） |
| 搜索无结果 | 列表为空，显示"无匹配结果" |
| 过滤后删除 | 从 `todos` 删除，刷新显示 |
| 过滤后标记完成 | 更新 `todos`，刷新显示（保持过滤状态） |
| 过滤后添加新待办 | 添加到 `todos`，但只有在匹配当前过滤条件时才显示 |

---

## 💻 写代码

### 步骤 1：框架

新建 `lesson9.py`，从第 8 课的代码开始修改。

### 步骤 2：搜索栏

在标题和输入区域之间加入搜索栏：

```python
# ==================== 搜索区域（第 2 行）====================

search_frame = ttk.Frame(window)
search_frame.grid(row=2, column=0, pady=(10, 0), padx=20, sticky="ew")

ttk.Label(search_frame, text="🔍", font=("微软雅黑", 12)).pack(side=tk.LEFT, padx=(0, 5))

# 搜索输入框（绑定 StringVar，实现实时搜索）
search_var = tk.StringVar()
search_entry = ttk.Entry(
    search_frame,
    textvariable=search_var,
    font=("微软雅黑", 11),
    width=20
)
search_entry.pack(side=tk.LEFT, fill=tk.X, expand=True, padx=(0, 5))

# 清除搜索按钮
clear_search_btn = ttk.Button(
    search_frame,
    text="✕",
    width=3
)
clear_search_btn.pack(side=tk.LEFT)
```

### 步骤 3：类别筛选下拉框

在搜索栏右边加一个类别筛选：

```python
# 类别筛选
ttk.Label(search_frame, text="筛选：", font=("微软雅黑", 9)).pack(
    side=tk.LEFT, padx=(10, 3)
)

filter_combo = ttk.Combobox(
    search_frame,
    values=["全部 📋", "学习 📚", "生活 🏠", "娱乐 🎮", "其他 📌"],
    state="readonly",
    font=("微软雅黑", 9),
    width=10
)
filter_combo.pack(side=tk.LEFT)
filter_combo.set("全部 📋")
```

### 步骤 4：实时过滤函数

```python
def refresh_display():
    """根据搜索词和类别筛选，刷新 Listbox 显示"""
    # 获取过滤条件
    keyword = search_var.get().strip().lower()
    category_filter = filter_combo.get()

    # 保存当前选中（如果有的话）
    selected_indices = listbox.curselection()
    selected_display = None
    if selected_indices:
        selected_display = listbox.get(selected_indices[0])

    # 清空 Listbox
    listbox.delete(0, tk.END)

    # 遍历过滤
    for todo in todos:
        # 搜索词匹配
        text_match = (not keyword) or (keyword in todo["text"].lower())

        # 类别匹配
        category_match = (
            category_filter == "全部 📋" or
            category_filter == todo["category"]
        )

        if text_match and category_match:
            display_text = f"[{todo['category']}] {todo['text']}"
            listbox.insert(tk.END, display_text)

            # 恢复完成样式
            if todo["done"]:
                idx = listbox.size() - 1
                listbox.itemconfig(idx, fg="gray")
                listbox.itemconfig(idx, font=("微软雅黑", 12, "overstrike"))

            # 恢复选中状态
            if selected_display and display_text == selected_display:
                listbox.selection_set(listbox.size() - 1)

    # 更新状态栏
    update_status()

    # 无结果提示
    if listbox.size() == 0 and todos:
        listbox.insert(tk.END, "（无匹配结果）")
        listbox.itemconfig(0, fg="#AAAAAA")

# 绑定实时搜索
search_var.trace("w", lambda *args: refresh_display())

# 绑定类别筛选
filter_combo.bind("<<ComboboxSelected>>", lambda e: refresh_display())

# 绑定清除搜索
def clear_search():
    search_var.set("")
    search_entry.focus()

clear_search_btn.config(command=clear_search)
```

### 步骤 5：根据显示匹配数据

```python
def find_todo_by_display(display_text):
    """根据显示文本找到对应的 todo 字典"""
    if not display_text or display_text == "（无匹配结果）":
        return None
    for todo in todos:
        expected = f"[{todo['category']}] {todo['text']}"
        if expected == display_text:
            return todo
    return None

def get_selected_todo():
    """获取当前选中项对应的 todo 字典"""
    selected = listbox.curselection()
    if not selected:
        return None

    display_text = listbox.get(selected[0])
    return find_todo_by_display(display_text)
```

### 步骤 6：修改操作函数

修改 `toggle_done`、`delete_todo` 等，使用新的匹配方式：

```python
def toggle_done():
    todo = get_selected_todo()
    if not todo:
        return

    if "（无匹配结果）" in str(listbox.get(tk.ACTIVE) if listbox.size() > 0 else ""):
        return

    todo["done"] = not todo["done"]
    save_todos()
    refresh_display()  # 刷新（保持过滤状态）

def delete_todo():
    todo = get_selected_todo()
    if not todo:
        messagebox.showwarning("提示", "请先选择要删除的事项！")
        return

    display_text = listbox.get(listbox.curselection()[0])
    if display_text == "（无匹配结果）":
        return

    result = messagebox.askyesno("确认删除", f"确定要删除「{todo['text']}」吗？")
    if result:
        todos.remove(todo)
        save_todos()
        refresh_display()
```

### 步驟 7：快捷键优化

加入 Ctrl+F 聚焦搜索框：

```python
window.bind_all("<Control-f>", lambda e: search_entry.focus())
window.bind_all("<Control-l>", lambda e: clear_search())  # Ctrl+L 清除搜索
```

---

## ▶️ 运行看效果

| 操作 | 预期结果 |
|------|----------|
| 添加 6 条待办（不同类别） | 全部显示 |
| 在搜索框输入"Python" | 只显示包含"Python"的待办 |
| 清空搜索框 | 恢复全部显示 |
| 筛选类别为"学习 📚" | 只显示学习类别的待办 |
| 同时搜索 + 筛选 | 两个条件取交集 |
| 过滤状态下标记完成 | 待办变灰，保持过滤状态 |
| 过滤状态下删除 | 从数据中删除，显示刷新 |
| 搜索无匹配 | 显示灰色"（无匹配结果）" |
| 按 Ctrl+F | 光标跳到搜索框 |

> 📸 *（此处放置截图：搜索过滤效果、无结果提示）*

---

## ✏️ 小练习

1. **搜索高亮**：在搜索结果中，把匹配的关键词变成红色（提示：没法在 Listbox 中直接做到——思考一下还有什么替代方案？）
2. **拼音搜索**：让搜索支持拼音首字母（如输入"py"能搜到"朋友"）— 这是一个有挑战性的功能
3. **排序功能**：加一个排序下拉框（按时间 / 按字母 / 按类别），可以重新排列 Listbox 的显示顺序
4. **挑战题**：给搜索框加一个"搜索历史"下拉提示（类似搜索引擎的搜索建议）

---

## 📋 本课完整代码

> ⚠️ 由于代码较长（约 350 行），请在第 8 课代码的基础上，按以下步骤修改：
>
> 1. 在标题和输入区之间插入搜索栏（search_frame）
> 2. 添加 `search_var`、`filter_combo` 和 `refresh_display()`
> 3. 添加 `find_todo_by_display()` 和 `get_selected_todo()`
> 4. 修改所有操作函数（`toggle_done`、`delete_todo`、`clear_all`），用 `get_selected_todo()` + `refresh_display()` 替代原来基于 index 的操作
> 5. 所有修改数据的操作后调用 `refresh_display()` 而不是直接操作 Listbox

**关键代码结构**：

```python
# ============================================
# 第 9 课：搜索与过滤 — 完整框架
# ============================================

import tkinter as tk
from tkinter import ttk, messagebox
import os

# --- 配置 ---
DATA_FILE = "todos.txt"

# --- 窗口 ---
window = tk.Tk()
window.title("我的备忘录")
window.geometry("500x700")
window.grid_rowconfigure(5, weight=1)  # 列表行可拉伸
window.grid_columnconfigure(0, weight=1)

# --- 数据 ---
todos = []
search_var = tk.StringVar()

# --- 文件操作 ---
# ... save_todos(), load_todos() ...

# --- 界面 ---
# ... 标题、搜索栏、输入区、列表、状态栏 ...

# --- 核心逻辑 ---
def refresh_display():
    """核心：根据搜索/筛选条件刷新显示"""
    pass  # 见上文详细代码

def get_selected_todo():
    """获取当前选中对应的数据"""
    pass

# --- 操作函数 ---
# ... add_todo, toggle_done, delete_todo, clear_all ...

# --- 事件绑定 ---
search_var.trace("w", lambda *a: refresh_display())
filter_combo.bind("<<ComboboxSelected>>", lambda e: refresh_display())

# --- 启动 ---
load_todos()
refresh_display()
window.mainloop()
```

---

## 🧠 本课小结

| 学到的知识 | 是什么 | 怎么用 |
|-----------|--------|--------|
| `StringVar` | tkinter 字符串变量 | `var = tk.StringVar()` |
| `textvariable` | 双向绑定 | `Entry(textvariable=var)` |
| `.trace("w", fn)` | 监听变量变化 | 实时搜索的核心 |
| `in` | 判断包含 | `"搜索词" in "待办文字".lower()` |
| `.lower()` | 转小写 | 实现大小写不敏感 |
| `"且"`（and） | 多条件过滤 | `keyword_match and category_match` |
| `"或"`（or） | 多条件任一 | `category == "全部" or category == todo["category"]` |
| `<<ComboboxSelected>>` | 下拉框选择事件 | `combo.bind("<<ComboboxSelected>>", fn)` |
| 过滤模式 | 数据不动，显示过滤 | 核心设计模式 |
| 反向匹配 | 显示→数据 | `find_todo_by_display()` |

---

## 📖 下节课预告

第 10 课（最终课）：**打包发布 — 让所有人用上你的程序！**

学会用 **PyInstaller** 把 Python 程序打包成 `.exe`（Windows）或 `.app`（Mac），可以发给没装 Python 的朋友直接运行！课程总复习 + 成就解锁 🎉
