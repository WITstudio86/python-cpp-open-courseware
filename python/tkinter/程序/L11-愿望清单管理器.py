import tkinter as tk

# ========================================
# 第 11 节：愿望清单管理器
# 知识点：Listbox + Scrollbar + Entry + Button
# ========================================

# 1. 创建主窗口
root = tk.Tk()
root.title("愿望清单管理器")           # 设置窗口标题
root.geometry("450x400")               # 设置窗口大小：宽450，高400
root.configure(bg="#fff8e1")           # 设置背景色：暖黄色

# 2. 顶部标题
title_label = tk.Label(
    root,
    text="🌟 我的愿望清单",
    font=("Microsoft YaHei", 18, "bold"),
    bg="#fff8e1",                      # 背景色与窗口一致
    fg="#e65100"                       # 文字颜色：深橙色
)
title_label.pack(pady=(15, 5))

# 3. 输入区域：一个 Frame 容器，包含输入框和添加按钮
input_frame = tk.Frame(root, bg="#fff8e1")
input_frame.pack(pady=10)

# 3a. 创建输入框
entry = tk.Entry(
    input_frame,
    width=30,                          # 输入框宽度（字符数）
    font=("Microsoft YaHei", 12)
)
entry.pack(side=tk.LEFT, padx=(0, 8))  # 放在 Frame 左边
entry.focus_set()                       # 让输入框自动获得焦点，可以直接打字


# 3b. 定义"添加"功能的函数
def add_wish():
    """获取输入框内容，添加到 Listbox 中"""
    text = entry.get().strip()          # .get() 获取输入文字，.strip() 去掉首尾空格
    if text:                             # 如果内容不为空
        listbox.insert(tk.END, text)     # tk.END 表示添加到列表末尾
        entry.delete(0, tk.END)          # 清空输入框（从第0个字符删到末尾）


# 3c. 创建"添加"按钮
add_btn = tk.Button(
    input_frame,
    text="➕ 添加",
    command=add_wish,                   # 点击时调用 add_wish 函数
    font=("Microsoft YaHei", 11, "bold"),
    bg="#ff9800",                       # 按钮背景色：橙色
    fg="white",                         # 按钮文字色：白色
    activebackground="#f57c00",         # 鼠标按下时的颜色
    relief="flat",                      # 扁平样式
    padx=15, pady=4,                    # 内边距
    cursor="hand2"                      # 鼠标悬停时显示手指
)
add_btn.pack(side=tk.LEFT)              # 放在输入框右边

# 3d. 绑定回车键：在窗口任意位置按回车都能触发添加
root.bind("<Return>", lambda event: add_wish())

# 4. 列表区域：一个 Frame 包含 Listbox 和 Scrollbar
list_frame = tk.Frame(root, bg="#fff8e1")
list_frame.pack(pady=10, fill=tk.BOTH, expand=True, padx=30)

# 4a. 创建滚动条（先放右边）
scrollbar = tk.Scrollbar(list_frame)
scrollbar.pack(side=tk.RIGHT, fill=tk.Y)  # 靠右放置，纵向填满

# 4b. 创建 Listbox，并与滚动条关联
listbox = tk.Listbox(
    list_frame,
    width=35,                           # 列表宽度（字符数）
    height=10,                          # 列表高度（行数）
    font=("Microsoft YaHei", 12),
    bg="#ffffff",                       # 列表背景色：白色
    fg="#333333",                       # 列表文字色
    selectbackground="#ffcc80",         # 选中项的背景色：浅橙色
    selectforeground="#333333",         # 选中项的文字色
    yscrollcommand=scrollbar.set        # 关键！让 Listbox 通知滚动条
)
listbox.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

# 4c. 滚动条也要关联 Listbox（双向绑定）
scrollbar.config(command=listbox.yview)


# 5. 定义"删除"功能的函数
def delete_wish():
    """删除 Listbox 中当前选中的项目"""
    selected = listbox.curselection()   # 获取选中项的索引（返回元组）
    if selected:                         # 如果有选中的项（元组不为空）
        listbox.delete(selected[0])      # 删除第一个选中的项（索引从元组中取）


# 5a. 创建"删除选中"按钮
delete_btn = tk.Button(
    root,
    text="🗑️ 删除选中",
    command=delete_wish,                # 点击时调用 delete_wish 函数
    font=("Microsoft YaHei", 11, "bold"),
    bg="#f44336",                       # 按钮背景色：红色
    fg="white",                         # 按钮文字色：白色
    activebackground="#d32f2f",         # 鼠标按下时的颜色
    relief="flat",
    padx=15, pady=6,
    cursor="hand2"
)
delete_btn.pack(pady=(0, 15))

# 6. 启动主循环（必须放在代码最后！）
root.mainloop()
