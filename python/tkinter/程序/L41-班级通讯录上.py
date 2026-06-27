import tkinter as tk
from tkinter import ttk

# ========================================
# 第 41 节：项目 12 —— 班级通讯录（上）
# 知识点：Treeview 表格控件、列定义、插入数据、多 Entry 录入、Scrollbar
# 说明：通讯录项目第一部分——搭建表格框架，实现增删查看
# ========================================

# 1. 创建主窗口
root = tk.Tk()
root.title("班级通讯录")
root.geometry("650x520")
root.configure(bg="#e8f0fe")  # 浅蓝色背景，清爽整洁


# 2. 标题区域
title_label = tk.Label(
    root,
    text="📒 班级通讯录",
    font=("微软雅黑", 20, "bold"),
    bg="#e8f0fe",
    fg="#1a237e"                # 深蓝色文字
)
title_label.pack(pady=(15, 10))


# 3. 录入表单区域
#    使用 Frame + grid 布局，排放 4 个 Entry 输入框和 1 个添加按钮
form_frame = tk.Frame(root, bg="#e8f0fe")
form_frame.pack(pady=10)

# ------ 第一行：姓名 + 电话 ------
tk.Label(
    form_frame, text="姓名：", bg="#e8f0fe",
    font=("微软雅黑", 12)
).grid(row=0, column=0, sticky="e", padx=5, pady=3)

name_entry = tk.Entry(form_frame, width=14, font=("微软雅黑", 11))
name_entry.grid(row=0, column=1, padx=5, pady=3)

tk.Label(
    form_frame, text="电话：", bg="#e8f0fe",
    font=("微软雅黑", 12)
).grid(row=0, column=2, sticky="e", padx=5, pady=3)

phone_entry = tk.Entry(form_frame, width=18, font=("微软雅黑", 11))
phone_entry.grid(row=0, column=3, padx=5, pady=3)

# ------ 第二行：QQ + 备注 ------
tk.Label(
    form_frame, text="QQ：", bg="#e8f0fe",
    font=("微软雅黑", 12)
).grid(row=1, column=0, sticky="e", padx=5, pady=3)

qq_entry = tk.Entry(form_frame, width=14, font=("微软雅黑", 11))
qq_entry.grid(row=1, column=1, padx=5, pady=3)

tk.Label(
    form_frame, text="备注：", bg="#e8f0fe",
    font=("微软雅黑", 12)
).grid(row=1, column=2, sticky="e", padx=5, pady=3)

note_entry = tk.Entry(form_frame, width=18, font=("微软雅黑", 11))
note_entry.grid(row=1, column=3, padx=5, pady=3)


# 4. 添加联系人函数
def add_contact():
    """收集 4 个 Entry 的内容 → 插入 Treeview → 清空输入框"""
    # 获取用户输入，strip() 去掉首尾空格
    name = name_entry.get().strip()
    phone = phone_entry.get().strip()
    qq = qq_entry.get().strip()
    note = note_entry.get().strip()

    # 姓名不能为空（最基本的校验）
    if name == "":
        return

    # 插入 Treeview 表格
    tree.insert("", tk.END, values=(name, phone, qq, note))

    # 清空所有输入框，方便输入下一个
    name_entry.delete(0, tk.END)
    phone_entry.delete(0, tk.END)
    qq_entry.delete(0, tk.END)
    note_entry.delete(0, tk.END)

    # 让姓名输入框重新获得焦点（光标回到第一个框）
    name_entry.focus_set()


# 添加按钮（跨两行，竖向居中）
add_btn = tk.Button(
    form_frame,
    text="➕ 添加联系人",
    command=add_contact,
    font=("微软雅黑", 11, "bold"),
    bg="#4caf50",                # 绿色按钮
    fg="white",
    activebackground="#388e3c",
    relief="flat",
    padx=15, pady=5,
    cursor="hand2"
)
add_btn.grid(row=0, column=4, rowspan=2, padx=15, sticky="ns")


# 5. Treeview 表格区域
# ==============================

# 5a. 定义列名（内部名称，代码中使用）
columns = ("name", "phone", "qq", "note")

# 5b. 创建 Treeview 控件
#     show="headings" → 只显示表头（纯表格模式）
#     height=10 → 最多显示 10 行，多的需要滚动条
tree = ttk.Treeview(root, columns=columns, show="headings", height=10)

# 5c. 设置表头显示文字（用户看到的中文名）
tree.heading("name", text="姓名")
tree.heading("phone", text="电话")
tree.heading("qq", text="QQ")
tree.heading("note", text="备注")

# 5d. 设置每列宽度（单位：像素）
tree.column("name", width=100)   # 姓名列 100px
tree.column("phone", width=130)  # 电话列 130px
tree.column("qq", width=120)     # QQ 列 120px
tree.column("note", width=180)   # 备注列 180px（宽一些，备注可能比较长）


# 6. 滚动条 —— 和 Treeview 配对
#    command=tree.yview：用户拖滚动条 → Treeview 滚动
#    yscrollcommand=scrollbar.set：Treeview 内容变化 → 滚动条更新
scrollbar = ttk.Scrollbar(root, orient=tk.VERTICAL, command=tree.yview)
tree.configure(yscrollcommand=scrollbar.set)

# 放置 Treeview（左侧）和滚动条（右侧）
tree.pack(pady=10, padx=20, fill=tk.BOTH, expand=True, side=tk.LEFT)
scrollbar.pack(side=tk.RIGHT, fill=tk.Y)


# 7. 预置示例数据（让表格不是空的）
sample_data = [
    ("张三", "13800001111", "12345678", "同桌"),
    ("李四", "13800002222", "23456789", "班长"),
    ("王五", "13800003333", "34567890", "学习委员"),
    ("赵六", "13800004444", "45678901", "体育委员"),
    ("陈七", "13800005555", "56789012", "文艺委员"),
]

# 逐行插入示例数据
for item in sample_data:
    tree.insert("", tk.END, values=item)


# 8. 删除选中联系人函数
def delete_contact():
    """删除 Treeview 中当前选中的所有行"""
    selected = tree.selection()   # 获取所有选中行的 ID 列表
    if selected:                  # 如果有选中的行
        for item in selected:
            tree.delete(item)     # 逐行删除


# 删除按钮
delete_btn = tk.Button(
    root,
    text="🗑️ 删除选中",
    command=delete_contact,
    font=("微软雅黑", 11, "bold"),
    bg="#f44336",                # 红色按钮（删除操作要醒目）
    fg="white",
    activebackground="#d32f2f",
    relief="flat",
    padx=20, pady=5,
    cursor="hand2"
)
delete_btn.pack(pady=(5, 0))


# 9. 底部操作提示
tip = tk.Label(
    root,
    text="💡 在输入框中填写信息 → 点「添加」→ 选中某行点「删除」",
    font=("微软雅黑", 9),
    bg="#e8f0fe",
    fg="#666666"
)
tip.pack(pady=(5, 10))


# 10. 启动窗口主循环（必须放在最后！）
root.mainloop()
