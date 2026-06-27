# ============================================
# 第 4 课：选中和删除 — 管理待办事项
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

# ==================== 列表 + 滚动条 ====================

list_label = tk.Label(
    window,
    text="📋 待办事项",
    font=("微软雅黑", 12, "bold"),
    fg="#555555"
)
list_label.pack(pady=(20, 5))

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
    # 情况 1：列表为空
    if listbox.size() == 0:
        messagebox.showwarning("提示", "列表为空，没有可删除的事项！")
        return

    # 情况 2：没有选中任何项
    selected = listbox.curselection()
    if not selected:
        messagebox.showwarning("提示", "请先选择要删除的事项！")
        return

    # 情况 3：正常删除
    index = selected[0]
    item_text = listbox.get(index)

    # 弹出确认对话框
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
