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
    """保存到文件"""
    with open(DATA_FILE, "w", encoding="utf-8") as file:
        for todo in todos:
            status = "1" if todo["done"] else "0"
            file.write(f"{status}|{todo['text']}\n")
    print(f"💾 已保存 {len(todos)} 条待办")

def load_todos():
    """从文件加载"""
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
    """导出为人类友好的文本文件"""
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

    messagebox.showinfo(
        "导出成功",
        f"已导出到「备忘录_导出.txt」！\n共 {len(todos)} 条待办事项。"
    )
    print(f"📤 已导出 {len(todos)} 条待办")

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
    bottom_frame, text="共 0 条待办",
    font=("微软雅黑", 9), fg="#999999"
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
    result = messagebox.askyesno(
        "确认清空",
        f"列表中有 {listbox.size()} 条事项，确定全部清空吗？"
    )
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

# ==================== 菜单栏 ====================

def create_menus():
    menubar = tk.Menu(window)
    window.config(menu=menubar)

    # --- 文件菜单 ---
    file_menu = tk.Menu(menubar, tearoff=0)
    menubar.add_cascade(label="文件", menu=file_menu)
    file_menu.add_command(
        label="导出为文本文件",
        command=export_to_file,
        accelerator="Ctrl+E"
    )
    file_menu.add_separator()
    file_menu.add_command(
        label="退出",
        command=on_closing,
        accelerator="Ctrl+Q"
    )

    # --- 操作菜单 ---
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

    # --- 帮助菜单 ---
    help_menu = tk.Menu(menubar, tearoff=0)
    menubar.add_cascade(label="帮助", menu=help_menu)
    help_menu.add_command(label="使用说明", command=show_help)
    help_menu.add_command(label="关于", command=show_about)

    # --- 右键菜单 ---
    context_menu = tk.Menu(window, tearoff=0)
    context_menu.add_command(label="标记完成/取消", command=toggle_done)
    context_menu.add_command(label="删除", command=delete_todo)
    context_menu.add_separator()
    context_menu.add_command(label="清空全部", command=clear_all)

    listbox.bind("<Button-3>", lambda e: context_menu.post(e.x_root, e.y_root))
    # Mac 兼容：Control + 点击
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
