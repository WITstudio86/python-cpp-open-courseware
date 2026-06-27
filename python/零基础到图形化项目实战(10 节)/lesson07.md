# 第 7 课 · 菜单栏和快捷键 — 让程序更专业

---

## 🎯 本课目标

- 学会用 `Menu` 创建菜单栏
- 学会组织多级菜单（文件 / 操作 / 帮助）
- 学会给菜单项绑定快捷键（Ctrl+S, Ctrl+N 等）
- 学会添加**分隔线**和**子菜单**
- 学会右键弹出菜单（上下文菜单）
- 用函数重构代码，让程序更整洁

---

## 📚 新知识

### 7.1 Menu 菜单控件

**菜单栏**是大多数桌面软件顶部的那个条：文件、编辑、视图、帮助……

tkinter 的 `Menu` 控件专门用来创建菜单。

```python
# 1. 创建菜单栏对象
menubar = tk.Menu(window)

# 2. 把菜单栏绑定到窗口
window.config(menu=menubar)

# 3. 创建一个菜单（如"文件"菜单）
file_menu = tk.Menu(menubar, tearoff=0)

# 4. 把菜单添加到菜单栏
menubar.add_cascade(label="文件", menu=file_menu)

# 5. 给菜单添加选项
file_menu.add_command(label="新建", command=函数)
file_menu.add_command(label="保存", command=函数)
file_menu.add_separator()  # 分隔线
file_menu.add_command(label="退出", command=window.destroy)
```

**`tearoff=0`** 是什么？

tkinter 的菜单默认有一个"撕裂线"（虚线），用户可以把它"撕下来"变成一个独立小窗口。用 `tearoff=0` 去掉这个古老的功能。

### 7.2 快捷键（Accelerator）

给菜单项加上键盘快捷键：

```python
# 显示快捷键文字（只是视觉提示）
file_menu.add_command(
    label="保存",
    command=save_todos,
    accelerator="Ctrl+S"    # ⬅ 显示在菜单中的快捷键提示
)

# 真正绑定快捷键行为
window.bind_all("<Control-s>", lambda event: save_todos())
```

**tkinter 键盘绑定格式**：

| 快捷键 | tkinter 写法 | 说明 |
|--------|-------------|------|
| Ctrl + S | `<Control-s>` | Windows/Linux |
| Cmd + S | `<Command-s>` | Mac |
| Ctrl + C | `<Control-c>` | 复制 |
| Ctrl + V | `<Control-v>` | 粘贴 |
| Ctrl + Z | `<Control-z>` | 撤销 |
| Ctrl + N | `<Control-n>` | 新建 |
| F5 | `<F5>` | 功能键 |
| Escape | `<Escape>` | 退出键 |

> ⚠️ **注意大小写**：`<Control-s>` 中的 `s` 是小写。`<Control-S>`（大写 S）等于 Ctrl+Shift+S！

**`bind_all` vs `bind`**：
- `widget.bind(event, func)` — 只绑定到特定控件
- `window.bind_all(event, func)` — 绑定到窗口中的所有控件

### 7.3 右键弹出菜单（上下文菜单）

右键菜单也叫"上下文菜单"，在 Windows 资源管理器、VS Code 中都很常见。

```python
# 创建右键菜单
context_menu = tk.Menu(window, tearoff=0)
context_menu.add_command(label="标记完成", command=toggle_done)
context_menu.add_command(label="删除", command=delete_todo)

# 鼠标右键事件处理
def show_context_menu(event):
    """在鼠标位置显示右键菜单"""
    context_menu.post(event.x_root, event.y_root)

# 绑定到 Listbox
listbox.bind("<Button-3>", show_context_menu)   # Button-3 = 右键
```

**坐标说明**：
- `event.x`, `event.y` — 相对于被点击控件的位置
- `event.x_root`, `event.y_root` — 相对于**整个屏幕**的位置
- `.post()` 需要用屏幕坐标

### 7.4 代码重构 — 用函数组织代码

随着代码越来越长，我们需要用**函数**把功能组织得更清晰。

**重构前**（散乱的代码）：
```python
# 所有代码堆在一起，难以阅读
```

**重构后**（模块化结构）：
```python
# ========== 文件操作 ==========
def save_todos(): ...
def load_todos(): ...

# ========== 核心功能 ==========
def add_todo(): ...
def delete_todo(): ...
def toggle_done(): ...
def clear_all(): ...

# ========== 界面创建 ==========
def create_widgets(): ...
def create_menus(): ...

# ========== 主程序 ==========
def main():
    create_widgets()
    create_menus()
    load_todos()
    window.mainloop()
```

---

## 💻 写代码

### 步骤 1：框架

新建 `lesson7.py`，从第 6 课代码开始，进行重构和功能添加。

### 步骤 2：创建菜单栏

```python
def create_menus():
    """创建所有菜单"""

    # ========== 主菜单栏 ==========
    menubar = tk.Menu(window)
    window.config(menu=menubar)

    # ========== "文件"菜单 ==========
    file_menu = tk.Menu(menubar, tearoff=0)
    menubar.add_cascade(label="文件", menu=file_menu)

    file_menu.add_command(
        label="导出为文本文件",
        command=export_to_file,
        accelerator="Ctrl+E"
    )
    file_menu.add_separator()  # 分隔线
    file_menu.add_command(
        label="退出",
        command=on_closing,
        accelerator="Ctrl+Q"
    )

    # ========== "操作"菜单 ==========
    action_menu = tk.Menu(menubar, tearoff=0)
    menubar.add_cascade(label="操作", menu=action_menu)

    action_menu.add_command(
        label="添加待办",
        command=lambda: entry.focus(),
        accelerator="Ctrl+N"
    )
    action_menu.add_command(
        label="标记完成/取消",
        command=toggle_done,
        accelerator="Ctrl+D"
    )
    action_menu.add_command(
        label="删除选中",
        command=delete_todo,
        accelerator="Delete"
    )
    action_menu.add_separator()
    action_menu.add_command(
        label="清空全部",
        command=clear_all,
        accelerator="Ctrl+Shift+X"
    )

    # ========== "帮助"菜单 ==========
    help_menu = tk.Menu(menubar, tearoff=0)
    menubar.add_cascade(label="帮助", menu=help_menu)

    help_menu.add_command(
        label="使用说明",
        command=show_help
    )
    help_menu.add_command(
        label="关于",
        command=show_about
    )

    # ========== 右键菜单 ==========
    context_menu = tk.Menu(window, tearoff=0)
    context_menu.add_command(
        label="标记完成/取消",
        command=toggle_done
    )
    context_menu.add_command(
        label="删除",
        command=delete_todo
    )
    context_menu.add_separator()
    context_menu.add_command(
        label="清空全部",
        command=clear_all
    )

    # 绑定右键点击
    listbox.bind("<Button-3>", lambda e: context_menu.post(e.x_root, e.y_root))

    # 在 Mac 上也支持 Control+点击（Mac 的常见右键方式）
    listbox.bind("<Button-2>", lambda e: context_menu.post(e.x_root, e.y_root))


def create_shortcuts():
    """绑定全局快捷键"""
    window.bind_all("<Control-n>", lambda e: entry.focus())
    window.bind_all("<Control-d>", lambda e: toggle_done())
    window.bind_all("<Control-e>", lambda e: export_to_file())
    window.bind_all("<Control-q>", lambda e: on_closing())
    window.bind("<Delete>", lambda e: delete_todo())
    window.bind_all("<Control-Shift-X>", lambda e: clear_all())
```

### 步骤 3：新功能 — 导出到文本文件

除了自动保存的 `todos.txt`（格式是为程序读取设计的），再加一个"导出为人类友好的文本文件"功能：

```python
def export_to_file():
    """将待办导出为人类友好的文本文件"""
    if not todos:
        messagebox.showwarning("提示", "列表为空，没有可导出的内容！")
        return

    with open("备忘录_导出.txt", "w", encoding="utf-8") as file:
        file.write("📝 我的备忘录\n")
        file.write("=" * 30 + "\n\n")

        for i, todo in enumerate(todos, 1):  # enumerate 从 1 开始编号
            status = "☑ 已完成" if todo["done"] else "☐ 未完成"
            file.write(f"{i}. [{status}] {todo['text']}\n")

        file.write(f"\n共 {len(todos)} 条待办事项\n")

    messagebox.showinfo("导出成功",
        f"已导出到「备忘录_导出.txt」！\n共 {len(todos)} 条待办事项。")

    print(f"📤 已导出 {len(todos)} 条待办")
```

> 💡 **`enumerate(todos, 1)`** — 同时获取索引和值，第二个参数 `1` 表示从 1 开始编号（默认从 0）。

### 步骤 4：新功能 — 帮助和关于

```python
def show_help():
    """显示使用说明"""
    help_text = (
        "📝 备忘录 使用说明\n\n"
        "➤ 添加待办：在输入框中输入，按回车或点「添加」按钮\n"
        "➤ 标记完成：选中事项，点「标记」按钮、或双击、或按 Ctrl+D\n"
        "➤ 删除待办：选中事项，点「删除」按钮、或按 Delete 键\n"
        "➤ 右键菜单：在列表上点鼠标右键\n"
        "➤ 清空全部：点「清空全部」按钮\n"
        "➤ 数据自动保存，关闭程序不会丢失！"
    )
    messagebox.showinfo("使用说明", help_text)

def show_about():
    """显示关于信息"""
    about_text = (
        "📝 我的备忘录 v1.0\n\n"
        "用 Python + tkinter 制作\n"
        "零基础到图形化项目实战\n\n"
        "恭喜你已经学完了 7 节课！\n"
        "你的备忘录已经是一个真正的软件了 🎉"
    )
    messagebox.showinfo("关于", about_text)
```

### 步骤 5：组织主函数

```python
def main():
    """主函数 — 程序的入口"""
    # 创建菜单
    create_menus()

    # 绑定快捷键
    create_shortcuts()

    # 绑定窗口关闭事件
    window.protocol("WM_DELETE_WINDOW", on_closing)

    # 加载已有数据
    load_todos()
    update_status()

    # 光标放在输入框
    entry.focus()

    # 启动主循环
    window.mainloop()

# 程序启动
if __name__ == "__main__":
    main()
```

> 💡 **`if __name__ == "__main__":`** — 这是一个 Python 的常用模式。意思是"如果这个文件被直接运行（不是被导入），就执行 `main()`"。这是写"正式程序"的好习惯。

---

## ▶️ 运行看效果

| 操作 | 预期结果 |
|------|----------|
| 点击菜单栏"文件" | 下拉菜单显示"导出"和"退出" |
| 点击菜单栏"操作" | 下拉菜单显示添加/标记/删除/清空 |
| 点击菜单栏"帮助" | 下拉菜单显示"使用说明"和"关于" |
| 按 Ctrl+N | 光标跳转到输入框 |
| 按 Ctrl+D | 切换选中项的完成状态 |
| 按 Ctrl+E | 导出到 `备忘录_导出.txt` |
| 选中事项，右键 | 弹出菜单：标记完成、删除、清空 |
| 点击"帮助 → 使用说明" | 弹出详细的操作指南 |
| 点击"帮助 → 关于" | 弹出程序信息 |

> 📸 *（此处放置截图：菜单栏展开状态 + 右键菜单）*

---

## ✏️ 小练习

1. **加菜单项**：在"操作"菜单中加一个"全部标记为完成"选项
2. **改右键菜单**：在右键菜单中加一个"上移"和"下移"选项（移动待办顺序）
3. **换个快捷键**：把 Ctrl+D 改成 Ctrl+Space，试试看会怎样？（Ctrl+Space 在某些系统上被输入法占用）
4. **挑战题**：给"文件"菜单加上"导入"功能——从 `备忘录_导出.txt` 读回待办事项（需要解析文件格式）

---

## 📋 本课完整代码

```python
# ============================================
# 第 7 课：菜单栏和快捷键 — 让程序更专业
# ============================================

import tkinter as tk
from tkinter import messagebox
import os

# ==================== 配置 ====================

DATA_FILE = "todos.txt"

# ==================== 创建窗口 ====================

window = tk.Tk()
window.title("我的备忘录")
window.geometry("450x600")

# ==================== 数据结构 ====================

todos = []

# ==================== 文件操作 ====================

def save_todos():
    with open(DATA_FILE, "w", encoding="utf-8") as file:
        for todo in todos:
            status = "1" if todo["done"] else "0"
            file.write(f"{status}|{todo['text']}\n")
    print(f"💾 已保存 {len(todos)} 条待办")

def load_todos():
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
                    idx = listbox.size() - 1
                    listbox.itemconfig(idx, fg="gray")
                    listbox.itemconfig(idx, font=("微软雅黑", 12, "overstrike"))
    print(f"📂 已从文件加载 {len(todos)} 条待办")

def export_to_file():
    if not todos:
        messagebox.showwarning("提示", "列表为空，没有可导出的内容！")
        return
    with open("备忘录_导出.txt", "w", encoding="utf-8") as file:
        file.write("📝 我的备忘录\n")
        file.write("=" * 30 + "\n\n")
        for i, todo in enumerate(todos, 1):
            status = "☑ 已完成" if todo["done"] else "☐ 未完成"
            file.write(f"{i}. [{status}] {todo['text']}\n")
        file.write(f"\n共 {len(todos)} 条待办事项\n")
    messagebox.showinfo("导出成功", f"已导出到「备忘录_导出.txt」！\n共 {len(todos)} 条待办事项。")

# ==================== 标题区域 ====================

title_label = tk.Label(
    window, text="📝 我的备忘录",
    font=("微软雅黑", 20, "bold"), fg="#333333"
)
title_label.pack(pady=15)

subtitle_label = tk.Label(
    window, text="试试菜单栏和快捷键！",
    font=("微软雅黑", 10), fg="#888888"
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
    list_frame, font=("微软雅黑", 12), height=15,
    selectbackground="#C8E6C9", selectforeground="#333333",
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
    save_todos()
    window.destroy()

# ==================== 帮助与关于 ====================

def show_help():
    help_text = (
        "📝 备忘录 使用说明\n\n"
        "➤ 添加待办：输入文字，按回车或点「添加」按钮\n"
        "➤ 标记完成：选中事项，点「标记」、双击、或右键\n"
        "➤ 删除待办：选中事项，点「删除」或按 Delete 键\n"
        "➤ 右键菜单：在列表上点鼠标右键\n"
        "➤ 清空全部：点「清空全部」按钮\n"
        "➤ 数据自动保存，关闭程序不会丢失！"
    )
    messagebox.showinfo("使用说明", help_text)

def show_about():
    about_text = (
        "📝 我的备忘录 v1.0\n\n"
        "用 Python + tkinter 制作\n"
        "零基础到图形化项目实战\n\n"
        "你已经学完了 7 节课！\n"
        "你的备忘录已经是一个真正的软件了 🎉"
    )
    messagebox.showinfo("关于", about_text)

# ==================== 菜单 ====================

def create_menus():
    menubar = tk.Menu(window)
    window.config(menu=menubar)

    # 文件菜单
    file_menu = tk.Menu(menubar, tearoff=0)
    menubar.add_cascade(label="文件", menu=file_menu)
    file_menu.add_command(label="导出为文本文件", command=export_to_file, accelerator="Ctrl+E")
    file_menu.add_separator()
    file_menu.add_command(label="退出", command=on_closing, accelerator="Ctrl+Q")

    # 操作菜单
    action_menu = tk.Menu(menubar, tearoff=0)
    menubar.add_cascade(label="操作", menu=action_menu)
    action_menu.add_command(label="添加待办", command=lambda: entry.focus(), accelerator="Ctrl+N")
    action_menu.add_command(label="标记完成/取消", command=toggle_done, accelerator="Ctrl+D")
    action_menu.add_command(label="删除选中", command=delete_todo, accelerator="Delete")
    action_menu.add_separator()
    action_menu.add_command(label="清空全部", command=clear_all, accelerator="Ctrl+Shift+X")

    # 帮助菜单
    help_menu = tk.Menu(menubar, tearoff=0)
    menubar.add_cascade(label="帮助", menu=help_menu)
    help_menu.add_command(label="使用说明", command=show_help)
    help_menu.add_command(label="关于", command=show_about)

    # 右键菜单
    context_menu = tk.Menu(window, tearoff=0)
    context_menu.add_command(label="标记完成/取消", command=toggle_done)
    context_menu.add_command(label="删除", command=delete_todo)
    context_menu.add_separator()
    context_menu.add_command(label="清空全部", command=clear_all)

    listbox.bind("<Button-3>", lambda e: context_menu.post(e.x_root, e.y_root))
    listbox.bind("<Button-2>", lambda e: context_menu.post(e.x_root, e.y_root))

# ==================== 快捷键 ====================

def create_shortcuts():
    window.bind_all("<Control-n>", lambda e: entry.focus())
    window.bind_all("<Control-d>", lambda e: toggle_done())
    window.bind_all("<Control-e>", lambda e: export_to_file())
    window.bind_all("<Control-q>", lambda e: on_closing())
    window.bind("<Delete>", lambda e: delete_todo())
    window.bind_all("<Control-Shift-X>", lambda e: clear_all())

# ==================== 绑定按钮 ====================

add_btn.config(command=add_todo)
toggle_btn.config(command=toggle_done)
delete_btn.config(command=delete_todo)
clear_btn.config(command=clear_all)
entry.bind("<Return>", lambda e: add_todo())
listbox.bind("<Double-1>", lambda e: toggle_done())

# ==================== 主函数 ====================

def main():
    create_menus()
    create_shortcuts()
    window.protocol("WM_DELETE_WINDOW", on_closing)
    load_todos()
    update_status()
    entry.focus()
    window.mainloop()

if __name__ == "__main__":
    main()
```

---

## 🧠 本课小结

| 学到的知识 | 是什么 | 怎么用 |
|-----------|--------|--------|
| `tk.Menu()` | 创建菜单 | `menubar = tk.Menu(window)` |
| `add_cascade()` | 添加菜单到菜单栏 | `menubar.add_cascade(label="文件", menu=...)` |
| `add_command()` | 菜单项 | `menu.add_command(label="保存", command=fn)` |
| `add_separator()` | 分隔线 | `menu.add_separator()` |
| `tearoff=0` | 禁用撕裂线 | `tk.Menu(menubar, tearoff=0)` |
| `accelerator` | 显示快捷键 | `accelerator="Ctrl+S"` |
| `bind_all()` | 全局快捷键 | `window.bind_all("<Control-s>", fn)` |
| `context_menu.post()` | 右键菜单 | `context_menu.post(e.x_root, e.y_root)` |
| `<Button-3>` | 鼠标右键事件 | `widget.bind("<Button-3>", fn)` |
| `enumerate()` | 带序号遍历 | `for i, item in enumerate(list, 1):` |
| `if __name__ == "__main__"` | 主程序入口 | 程序被直接运行时才执行 |

---

## 📖 下节课预告

第 8 课：**美化界面 — ttk 主题和 grid 布局**

告别灰色的老式界面！我们将用 **ttk**（Tk 主题控件）给程序"换皮肤"，用 **grid** 网格布局替换 pack 布局，让界面更有设计感。
