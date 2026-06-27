# 第 4 课 · 选中和删除 — 让备忘录能管理事项

---

## 🎯 本课目标

- 学会在 Listbox 中**选中**某条事项
- 学会用 `curselection()` 获取选中的位置
- 学会用 `.delete()` 删除指定事项
- 深入使用 `if...else` 处理"没选中就点删除"的情况
- 学会 `messagebox` 弹出确认提示框

---

## 📚 新知识

### 4.1 获取 Listbox 中的选中项：`curselection()`

`curselection()` 返回用户在 Listbox 中**当前选中项的索引**（位置编号）。

```python
# 获取选中项的索引
selected = listbox.curselection()
```

**重要**：`curselection()` 返回的是一个**元组** `(索引,)`，而不是单个数字！

```python
selected = listbox.curselection()
print(selected)  # 如果选中了第 2 条，输出：(1,)

# 取出第一个（也是唯一的）选中索引
if selected:
    index = selected[0]
    print(f"你选中了第 {index + 1} 条")
```

> 💡 **为什么是元组？** Listbox 支持多选模式（按住 Ctrl 可多选），所以返回的是"所有选中项的索引集合"。本课中我们只用单选，所以取 `[0]` 即可。

### 4.2 删除指定项：`.delete()`

```python
# 删除指定索引的项
listbox.delete(索引)
```

```python
# 示例：删除选中的项
selected = listbox.curselection()
if selected:
    index = selected[0]
    listbox.delete(index)
```

### 4.3 深入 if...else：处理边界情况

好的程序要考虑到各种**边界情况**（edge case）。在删除功能中：

| 情况 | 应该怎么办？ |
|------|-------------|
| 用户选中了一条，点删除 | ✅ 正常删除 |
| 用户没选中任何东西，点删除 | ⚠️ 提示"请先选择要删除的事项" |
| 列表是空的，点删除 | ⚠️ 提示"列表为空" |

```python
def delete_todo():
    # 先判断列表是否为空
    if listbox.size() == 0:
        print("⚠️ 列表为空，没有可删除的事项")
        return  # 提前结束函数

    # 再判断是否有选中项
    selected = listbox.curselection()
    if not selected:
        print("⚠️ 请先选择要删除的事项")
        return

    # 正常删除
    index = selected[0]
    listbox.delete(index)
    print("✅ 删除成功！")
```

> 💡 **`return` 的作用**：在函数中遇到 `return`，函数会立刻停止，后面的代码不再执行。这可以避免多层嵌套的 if。

### 4.4 messagebox — 弹出提示框

`messagebox` 是 tkinter 内置的**弹窗模块**，可以弹出信息提示、警告、确认对话框等。

```python
from tkinter import messagebox
```

**常用弹窗类型**：

| 函数 | 作用 | 返回值 |
|------|------|--------|
| `messagebox.showinfo("标题", "内容")` | 信息提示 | `"ok"` |
| `messagebox.showwarning("标题", "内容")` | 警告提示 | `"ok"` |
| `messagebox.showerror("标题", "内容")` | 错误提示 | `"ok"` |
| `messagebox.askyesno("标题", "问题")` | 是/否确认 | `True` 或 `False` |
| `messagebox.askokcancel("标题", "问题")` | 确认/取消 | `True` 或 `False` |

**使用示例**：

```python
from tkinter import messagebox

# 询问用户是否确认删除
result = messagebox.askyesno(
    "确认删除",
    "确定要删除这条待办事项吗？\n删除后无法恢复哦！"
)

if result:  # 用户点了"是"
    print("执行删除")
else:       # 用户点了"否"
    print("取消删除")
```

> 💡 **`\n`** 是换行符，在弹窗文字中插入换行。

### 4.5 为 Listbox 添加滚动条

当待办事项很多时，需要一个**滚动条**（Scrollbar）来上下翻看。

```python
# 创建滚动条
scrollbar = tk.Scrollbar(window)

# 配置滚动条和 Listbox 互相绑定
scrollbar.config(command=listbox.yview)
listbox.config(yscrollcommand=scrollbar.set)
```

**布局**（滚动条放在列表右边）：

```python
scrollbar.pack(side=tk.RIGHT, fill=tk.Y)  # 放到右边，纵向填满
listbox.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)  # 列表填满剩余空间
```

> 💡 **原理**：滚动条和 Listbox 需要**双向绑定**——滚动条拖动时更新列表的视图，列表滚动时更新滚动条的位置。

---

## 💻 写代码

### 步骤 1：框架

新建 `lesson4.py`，从第 3 课的完整代码开始，然后添加新功能。

### 步骤 2：导入 messagebox

```python
import tkinter as tk
from tkinter import messagebox   # 新增：导入弹窗模块
```

### 步骤 3：添加删除按钮

在输入区域（input_frame）中添加一个删除按钮：

```python
# 添加按钮（已有）
add_btn = tk.Button(
    input_frame,
    text="添加 ✅",
    font=("微软雅黑", 12),
    bg="#4CAF50",
    fg="white",
    padx=8,
    pady=5
)
add_btn.pack(side=tk.LEFT, padx=(0, 3))

# 删除按钮（新增）
delete_btn = tk.Button(
    input_frame,
    text="删除 ❌",
    font=("微软雅黑", 12),
    bg="#f44336",
    fg="white",
    padx=8,
    pady=5
)
delete_btn.pack(side=tk.LEFT)
```

### 步骤 4：实现删除功能

```python
def delete_todo():
    """删除选中的待办事项"""
    # 情况 1：列表为空
    if listbox.size() == 0:
        messagebox.showwarning("提示", "列表为空，没有可删除的事项！")
        return

    # 情况 2：没有选中任何项
    selected = listbox.curselection()
    if not selected:
        messagebox.showwarning("提示", "请先选择要删除的事项！")
        return

    # 情况 3：正常获取选中项
    index = selected[0]
    item_text = listbox.get(index)  # 获取选中项的文字

    # 弹出确认对话框
    result = messagebox.askyesno(
        "确认删除",
        f"确定要删除「{item_text}」吗？\n删除后无法恢复哦！"
    )

    if result:  # 用户点了"是"
        listbox.delete(index)
        print(f"❌ 删除了：{item_text}")
        messagebox.showinfo("成功", f"已删除「{item_text}」")

# 绑定删除按钮
delete_btn.config(command=delete_todo)
```

### 步骤 5：添加滚动条

```python
# --- 列表 + 滚动条 ---

# 创建一个框架来装列表和滚动条
list_frame = tk.Frame(window)
list_frame.pack(pady=5, fill=tk.BOTH, expand=True, padx=20)

# 滚动条
scrollbar = tk.Scrollbar(list_frame)
scrollbar.pack(side=tk.RIGHT, fill=tk.Y)

# 列表（绑定滚动条）
listbox = tk.Listbox(
    list_frame,
    font=("微软雅黑", 12),
    height=15,
    selectbackground="#C8E6C9",
    selectforeground="#333333",
    yscrollcommand=scrollbar.set  # 绑定：列表变化时通知滚动条
)
listbox.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

# 绑定：滚动条拖动时更新列表
scrollbar.config(command=listbox.yview)
```

### 步骤 6：添加键盘删除快捷键

按 `Delete` 键也能删除选中项：

```python
def on_delete_press(event):
    """按 Delete 键触发删除"""
    delete_todo()

# 绑定 Delete 键到整个窗口（因为不在输入框中操作）
window.bind("<Delete>", on_delete_press)
```

### 步骤 7：添加快捷清空按钮

加一个"清空全部"按钮，让学生体验 `.delete(0, tk.END)`：

```python
def clear_all():
    """清空所有待办事项"""
    if listbox.size() == 0:
        messagebox.showwarning("提示", "列表已经是空的！")
        return

    result = messagebox.askyesno(
        "确认清空",
        f"列表中有 {listbox.size()} 条事项，确定全部清空吗？"
    )

    if result:
        listbox.delete(0, tk.END)  # 从头删到尾 = 全部清空
        print("🗑️ 已清空全部待办事项")

# 清空按钮
clear_btn = tk.Button(
    window,
    text="清空全部 🗑️",
    font=("微软雅黑", 9),
    bg="#FF9800",
    fg="white",
    command=clear_all
)
clear_btn.pack(pady=5)
```

---

## ▶️ 运行看效果

运行程序后，试试以下操作：

| 操作 | 预期结果 |
|------|----------|
| 添加 3 条待办 | 列表显示 3 条 |
| 选中第 2 条，点"删除" | 弹出确认框，点"是"→ 删除 |
| 不选任何，点"删除" | 弹出警告"请先选择要删除的事项" |
| 列表为空时点"删除" | 弹出警告"列表为空" |
| 点"清空全部" | 弹出确认，点"是"→ 全部删除 |
| 按键盘 `Delete` 键 | 同删除按钮效果 |
| 添加超过 15 条 | 滚动条出现，可以滚动查看 |

> 📸 *（此处放置操作截图：确认删除弹窗、滚动条效果）*

---

## ✏️ 小练习

1. **改确认文字**：把删除确认弹窗的提示文字改成 `"真的不要这条了吗？(╥﹏╥)"`
2. **添加上移/下移**：加两个按钮，让选中的事项在列表中上移或下移一行（提示：先 `get()` 获取文字，再 `insert()` 插入新位置，再 `delete()` 旧位置）
3. **编辑功能**：加一个"编辑"按钮，点击后将选中事项的文字**回填到输入框**中，修改后重新添加
4. **挑战题**：在窗口底部加一个状态栏，实时显示 `"共 X 条待办事项"`

---

## 📋 本课完整代码

```python
# ============================================
# 第 4 课：选中和删除
# ============================================

import tkinter as tk
from tkinter import messagebox

# ==================== 创建窗口 ====================

window = tk.Tk()
window.title("我的备忘录")
window.geometry("450x600")

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
    text="添加、删除、管理你的待办事项！",
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
    width=22
)
entry.pack(side=tk.LEFT, padx=(0, 3))

add_btn = tk.Button(
    input_frame,
    text="添加 ✅",
    font=("微软雅黑", 11),
    bg="#4CAF50",
    fg="white",
    padx=8,
    pady=5
)
add_btn.pack(side=tk.LEFT, padx=(0, 3))

delete_btn = tk.Button(
    input_frame,
    text="删除 ❌",
    font=("微软雅黑", 11),
    bg="#f44336",
    fg="white",
    padx=8,
    pady=5
)
delete_btn.pack(side=tk.LEFT)

# ==================== 列表 + 滚动条区域 ====================

list_label = tk.Label(
    window,
    text="📋 待办事项",
    font=("微软雅黑", 12, "bold"),
    fg="#555555"
)
list_label.pack(pady=(20, 5))

# 列表框架
list_frame = tk.Frame(window)
list_frame.pack(pady=5, fill=tk.BOTH, expand=True, padx=20)

# 滚动条
scrollbar = tk.Scrollbar(list_frame)
scrollbar.pack(side=tk.RIGHT, fill=tk.Y)

# 列表
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

# ==================== 底部按钮 ====================

clear_btn = tk.Button(
    window,
    text="清空全部 🗑️",
    font=("微软雅黑", 9),
    bg="#FF9800",
    fg="white",
    padx=10,
    pady=3
)
clear_btn.pack(pady=5)

# ==================== 核心功能 ====================

def add_todo():
    """添加待办事项"""
    text = entry.get().strip()
    if text:
        listbox.insert(tk.END, text)
        entry.delete(0, tk.END)
        print(f"✅ 添加了：{text}")
    else:
        messagebox.showwarning("提示", "请输入待办事项！")

def delete_todo():
    """删除选中的待办事项"""
    if listbox.size() == 0:
        messagebox.showwarning("提示", "列表为空，没有可删除的事项！")
        return

    selected = listbox.curselection()
    if not selected:
        messagebox.showwarning("提示", "请先选择要删除的事项！")
        return

    index = selected[0]
    item_text = listbox.get(index)

    result = messagebox.askyesno(
        "确认删除",
        f"确定要删除「{item_text}」吗？\n删除后无法恢复哦！"
    )

    if result:
        listbox.delete(index)
        print(f"❌ 删除了：{item_text}")
        messagebox.showinfo("成功", f"已删除「{item_text}」")

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
        listbox.delete(0, tk.END)
        print("🗑️ 已清空全部待办事项")

# 绑定按钮
add_btn.config(command=add_todo)
delete_btn.config(command=delete_todo)
clear_btn.config(command=clear_all)

# 绑定键盘事件
entry.bind("<Return>", lambda event: add_todo())
window.bind("<Delete>", lambda event: delete_todo())

# ==================== 运行 ====================

entry.focus()
window.mainloop()
```

---

## 🧠 本课小结

| 学到的知识 | 是什么 | 怎么用 |
|-----------|--------|--------|
| `.curselection()` | 获取选中项索引 | `selected = listbox.curselection()` |
| `.delete(index)` | 删除指定项 | `listbox.delete(0)` |
| `.get(index)` | 获取指定项内容 | `text = listbox.get(0)` |
| `.size()` | 获取列表条数 | `count = listbox.size()` |
| `messagebox.showwarning()` | 警告弹窗 | `messagebox.showwarning("标题", "内容")` |
| `messagebox.askyesno()` | 确认弹窗 | 返回 `True` / `False` |
| `messagebox.showinfo()` | 信息弹窗 | `messagebox.showinfo("标题", "内容")` |
| `Scrollbar` | 滚动条 | 和 Listbox 双向绑定 |
| `return` | 提前结束函数 | 遇到 `return` 函数立刻停止 |
| `lambda` | 匿名函数 | `lambda event: add_todo()` |

---

## 📖 下节课预告

第 5 课：**标记已完成 — 样式变化与字典**

我们将学会用**字典（dict）**来管理每条待办事项的状态，给已完成的事项加上**删除线效果**，实现"标记已完成 / 取消完成"。
