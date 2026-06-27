import tkinter as tk
from tkinter import ttk, messagebox

# ========================================
# 第 42 节：班级通讯录（中）—— 搜索、编辑、删除
# ========================================

root = tk.Tk()
root.title("班级通讯录 V2.0")
root.geometry("650x500")
root.configure(bg="#f0f4f8")

# ---------- 数据存储 ----------
contacts = [
    ("张三", "13800001111", "同桌"),
    ("李四", "13800002222", "班长"),
    ("王五", "13800003333", "学习委员"),
    ("赵六", "13800004444", "体育委员"),
    ("陈七", "13800005555", "文艺委员"),
]

# ---------- 搜索区域 ----------
search_frame = tk.Frame(root, bg="#f0f4f8")
search_frame.pack(pady=10)

tk.Label(search_frame, text="🔍 搜索：", bg="#f0f4f8",
         font=("微软雅黑", 12)).pack(side=tk.LEFT)

search_entry = tk.Entry(search_frame, width=25, font=("微软雅黑", 11))
search_entry.pack(side=tk.LEFT, padx=5)


def search_items(event=None):
    """根据搜索框内容过滤 Treeview 的显示"""
    keyword = search_entry.get().strip().lower()
    # 遍历 Treeview 中所有行
    for item in tree.get_children():
        values = tree.item(item, "values")
        # 把整行数据拼成一个字符串，方便搜索
        row_text = " ".join(values).lower()
        if keyword == "" or keyword in row_text:
            tree.reattach(item, "", tk.END)  # 重新显示这行
        else:
            tree.detach(item)  # 暂时隐藏这行


# 绑定按键松开事件：每输入一个字就触发搜索
search_entry.bind("<KeyRelease>", search_items)

tk.Button(search_frame, text="✕ 清除",
          command=lambda: (search_entry.delete(0, tk.END), search_items()),
          bg="#ffccbc", font=("微软雅黑", 9)).pack(side=tk.LEFT)

# ---------- Treeview 表格 ----------
columns = ("name", "phone", "note")
tree = ttk.Treeview(root, columns=columns, show="headings", height=12)
tree.heading("name", text="姓名")
tree.heading("phone", text="电话")
tree.heading("note", text="备注")
tree.column("name", width=120)
tree.column("phone", width=150)
tree.column("note", width=200)

# 添加滚动条
scrollbar = ttk.Scrollbar(root, orient=tk.VERTICAL, command=tree.yview)
tree.configure(yscrollcommand=scrollbar.set)
scrollbar.pack(side=tk.RIGHT, fill=tk.Y)

tree.pack(pady=10, padx=20, fill=tk.BOTH, expand=True)

# 加载初始数据
for c in contacts:
    tree.insert("", tk.END, values=c)


# ---------- 双击编辑功能 ----------
def open_edit_window(item, old_values):
    """打开编辑窗口（Toplevel 子窗口）"""
    edit_win = tk.Toplevel(root)
    edit_win.title("编辑联系人")
    edit_win.geometry("320x280")
    edit_win.configure(bg="#fff3e0")

    tk.Label(edit_win, text="编辑联系人", font=("微软雅黑", 14, "bold"),
             bg="#fff3e0").pack(pady=10)

    fields = ["姓名：", "电话：", "备注："]
    entries = []

    for i, label_text in enumerate(fields):
        f = tk.Frame(edit_win, bg="#fff3e0")
        f.pack(pady=5)
        tk.Label(f, text=label_text, bg="#fff3e0", font=("微软雅黑", 11),
                 width=6, anchor="e").pack(side=tk.LEFT)
        ent = tk.Entry(f, font=("微软雅黑", 11), width=22)
        ent.insert(0, old_values[i])  # 预填原来的值
        ent.pack(side=tk.LEFT, padx=5)
        entries.append(ent)

    def save_changes():
        """保存修改到 Treeview"""
        new_values = tuple(e.get() for e in entries)
        tree.item(item, values=new_values)
        edit_win.destroy()

    tk.Button(edit_win, text="💾 保存修改", command=save_changes,
              bg="#a5d6a7", font=("微软雅黑", 12), width=15).pack(pady=15)


def on_double_click(event):
    """双击 Treeview 某一行时触发"""
    selected = tree.selection()
    if not selected:
        return
    item = selected[0]
    values = tree.item(item, "values")
    open_edit_window(item, values)


# 绑定双击事件
tree.bind("<Double-1>", on_double_click)


# ---------- 删除功能 ----------
def delete_selected():
    """删除选中的联系人（弹出确认框）"""
    selected = tree.selection()
    if not selected:
        messagebox.showwarning("提示", "请先选择要删除的联系人哦~")
        return

    item = selected[0]
    values = tree.item(item, "values")
    name = values[0]

    # 弹出确认对话框
    result = messagebox.askyesno(
        "确认删除",
        f"确定要删除联系人「{name}」吗？\n此操作不可撤销！"
    )

    if result:  # 用户点了"是"
        tree.delete(item)
        messagebox.showinfo("成功", f"已删除「{name}」")


# ---------- 添加功能 ----------
def add_contact():
    """打开添加联系人窗口"""
    add_win = tk.Toplevel(root)
    add_win.title("添加联系人")
    add_win.geometry("320x280")
    add_win.configure(bg="#e8f5e9")

    tk.Label(add_win, text="添加新联系人", font=("微软雅黑", 14, "bold"),
             bg="#e8f5e9").pack(pady=10)

    fields = ["姓名：", "电话：", "备注："]
    entries = []

    for label_text in fields:
        f = tk.Frame(add_win, bg="#e8f5e9")
        f.pack(pady=5)
        tk.Label(f, text=label_text, bg="#e8f5e9", font=("微软雅黑", 11),
                 width=6, anchor="e").pack(side=tk.LEFT)
        ent = tk.Entry(f, font=("微软雅黑", 11), width=22)
        ent.pack(side=tk.LEFT, padx=5)
        entries.append(ent)

    def save_new():
        """保存新联系人到 Treeview"""
        new_values = tuple(e.get() for e in entries)
        if new_values[0] == "":
            messagebox.showwarning("提示", "姓名不能为空哦~")
            return
        tree.insert("", tk.END, values=new_values)
        add_win.destroy()

    tk.Button(add_win, text="✅ 确认添加", command=save_new,
              bg="#81c784", font=("微软雅黑", 12), width=15).pack(pady=15)


# ---------- 底部按钮 ----------
btn_frame = tk.Frame(root, bg="#f0f4f8")
btn_frame.pack(pady=10)

tk.Button(btn_frame, text="➕ 添加联系人", command=add_contact,
          bg="#c8e6c9", font=("微软雅黑", 11), width=14).pack(side=tk.LEFT, padx=5)

tk.Button(btn_frame, text="🗑️ 删除选中", command=delete_selected,
          bg="#ffcdd2", font=("微软雅黑", 11), width=14).pack(side=tk.LEFT, padx=5)

# 操作提示标签
tip_label = tk.Label(root, text="💡 双击某一行可以编辑 / 输入关键字实时搜索",
                     bg="#f0f4f8", fg="#666", font=("微软雅黑", 9))
tip_label.pack(pady=(0, 10))

root.mainloop()
