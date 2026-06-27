import tkinter as tk
from tkinter import ttk, messagebox, filedialog
import json
import csv
import os

# ========================================
# 第 43 节：班级通讯录（下）—— JSON 持久化 + CSV 导入导出
# ========================================

DATA_FILE = "contacts.json"

root = tk.Tk()
root.title("班级通讯录 V3.0")
root.geometry("650x550")
root.configure(bg="#f0f4f8")

# ---------- JSON 数据操作 ----------
def save_to_json():
    """保存 Treeview 数据到 JSON 文件"""
    data = []
    for item in tree.get_children():
        values = tree.item(item, "values")
        data.append({"name": values[0], "phone": values[1], "note": values[2]})
    with open(DATA_FILE, "w", encoding="utf-8") as f:
        json.dump(data, f, ensure_ascii=False, indent=2)


def load_from_json():
    """从 JSON 文件加载数据到 Treeview"""
    if not os.path.exists(DATA_FILE):
        # 文件不存在 → 加载默认数据
        defaults = [
            ("张三", "13800001111", "同桌"),
            ("李四", "13800002222", "班长"),
            ("王五", "13800003333", "学习委员"),
        ]
        for d in defaults:
            tree.insert("", tk.END, values=d)
        return

    with open(DATA_FILE, "r", encoding="utf-8") as f:
        data = json.load(f)
    for contact in data:
        tree.insert("", tk.END,
                     values=(contact["name"], contact["phone"], contact["note"]))


# ---------- 搜索区域 ----------
search_frame = tk.Frame(root, bg="#f0f4f8")
search_frame.pack(pady=10)

tk.Label(search_frame, text="🔍 搜索：", bg="#f0f4f8",
         font=("微软雅黑", 12)).pack(side=tk.LEFT)

search_entry = tk.Entry(search_frame, width=25, font=("微软雅黑", 11))
search_entry.pack(side=tk.LEFT, padx=5)


def search_items(event=None):
    """根据搜索框内容过滤 Treeview"""
    keyword = search_entry.get().strip().lower()
    for item in tree.get_children():
        values = tree.item(item, "values")
        row_text = " ".join(values).lower()
        if keyword == "" or keyword in row_text:
            tree.reattach(item, "", tk.END)
        else:
            tree.detach(item)


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

scrollbar = ttk.Scrollbar(root, orient=tk.VERTICAL, command=tree.yview)
tree.configure(yscrollcommand=scrollbar.set)
scrollbar.pack(side=tk.RIGHT, fill=tk.Y)

tree.pack(pady=10, padx=20, fill=tk.BOTH, expand=True)

# 启动时加载数据
load_from_json()


# ---------- 双击编辑功能 ----------
def open_edit_window(item, old_values):
    """打开编辑窗口"""
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
        ent.insert(0, old_values[i])
        ent.pack(side=tk.LEFT, padx=5)
        entries.append(ent)

    def save_changes():
        new_values = tuple(e.get() for e in entries)
        tree.item(item, values=new_values)
        save_to_json()  # 编辑后自动保存
        edit_win.destroy()

    tk.Button(edit_win, text="💾 保存修改", command=save_changes,
              bg="#a5d6a7", font=("微软雅黑", 12), width=15).pack(pady=15)


def on_double_click(event):
    """双击某一行 → 弹出编辑窗口"""
    selected = tree.selection()
    if not selected:
        return
    item = selected[0]
    values = tree.item(item, "values")
    open_edit_window(item, values)


tree.bind("<Double-1>", on_double_click)


# ---------- 删除功能 ----------
def delete_selected():
    """删除选中联系人（需确认）"""
    selected = tree.selection()
    if not selected:
        messagebox.showwarning("提示", "请先选择要删除的联系人哦~")
        return

    item = selected[0]
    values = tree.item(item, "values")
    name = values[0]

    result = messagebox.askyesno("确认删除",
                                 f"确定要删除联系人「{name}」吗？\n此操作不可撤销！")
    if result:
        tree.delete(item)
        save_to_json()  # 删除后自动保存
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
        new_values = tuple(e.get() for e in entries)
        if new_values[0] == "":
            messagebox.showwarning("提示", "姓名不能为空哦~")
            return
        tree.insert("", tk.END, values=new_values)
        save_to_json()  # 添加后自动保存
        add_win.destroy()

    tk.Button(add_win, text="✅ 确认添加", command=save_new,
              bg="#81c784", font=("微软雅黑", 12), width=15).pack(pady=15)


# ---------- CSV 导入导出 ----------
def export_csv():
    """导出通讯录为 CSV 文件"""
    file_path = filedialog.asksaveasfilename(
        defaultextension=".csv",
        filetypes=[("CSV 文件", "*.csv")],
        title="导出通讯录"
    )
    if not file_path:
        return

    with open(file_path, "w", newline="", encoding="utf-8-sig") as f:
        writer = csv.writer(f)
        writer.writerow(["姓名", "电话", "备注"])  # 写表头
        for item in tree.get_children():
            writer.writerow(tree.item(item, "values"))

    messagebox.showinfo("导出成功", f"通讯录已导出到：\n{file_path}")


def import_csv():
    """从 CSV 文件导入通讯录"""
    file_path = filedialog.askopenfilename(
        filetypes=[("CSV 文件", "*.csv")],
        title="导入通讯录"
    )
    if not file_path:
        return

    with open(file_path, "r", encoding="utf-8-sig") as f:
        reader = csv.reader(f)
        try:
            next(reader)  # 跳过表头
        except StopIteration:
            pass
        count = 0
        for row in reader:
            if len(row) >= 2:
                tree.insert("", tk.END, values=tuple(row))
                count += 1

    save_to_json()  # 导入后保存
    messagebox.showinfo("导入成功", f"成功导入 {count} 条联系人！")


# ---------- 底部按钮 ----------
btn_frame1 = tk.Frame(root, bg="#f0f4f8")
btn_frame1.pack(pady=(10, 0))

tk.Button(btn_frame1, text="➕ 添加联系人", command=add_contact,
          bg="#c8e6c9", font=("微软雅黑", 11), width=14).pack(side=tk.LEFT, padx=5)

tk.Button(btn_frame1, text="🗑️ 删除选中", command=delete_selected,
          bg="#ffcdd2", font=("微软雅黑", 11), width=14).pack(side=tk.LEFT, padx=5)

btn_frame2 = tk.Frame(root, bg="#f0f4f8")
btn_frame2.pack(pady=5)

tk.Button(btn_frame2, text="📥 导入 CSV", command=import_csv,
          bg="#b3e5fc", font=("微软雅黑", 11), width=14).pack(side=tk.LEFT, padx=5)

tk.Button(btn_frame2, text="📤 导出 CSV", command=export_csv,
          bg="#ffe0b2", font=("微软雅黑", 11), width=14).pack(side=tk.LEFT, padx=5)

# 操作提示
tip_label = tk.Label(root, text="💡 数据自动保存到 contacts.json / 双击编辑 / 可导入导出 CSV",
                     bg="#f0f4f8", fg="#666", font=("微软雅黑", 9))
tip_label.pack(pady=(5, 10))


# ---------- 窗口关闭时自动保存 ----------
def on_closing():
    """窗口关闭前保存数据"""
    save_to_json()
    root.destroy()


root.protocol("WM_DELETE_WINDOW", on_closing)

root.mainloop()
