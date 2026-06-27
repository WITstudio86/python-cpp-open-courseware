import tkinter as tk

# ========================================
# 第 25 节：项目4 — 待办事项清单（上）
# 知识点：Listbox · Entry · 添加任务 · 删除任务 · 防止重复
# ========================================

# 1. 创建主窗口
root = tk.Tk()
root.title("待办事项清单")               # 设置窗口标题
root.geometry("480x480")                  # 设置窗口大小：宽480，高480
root.configure(bg="#f0f4f8")              # 设置背景色：浅蓝灰

# 2. 顶部标题
title_label = tk.Label(
    root,
    text="📋 我的待办事项",
    font=("Microsoft YaHei", 20, "bold"),  # 大号粗体标题
    bg="#f0f4f8",                          # 背景色与窗口一致
    fg="#2c3e50"                           # 文字颜色：深蓝灰
)
title_label.pack(pady=(20, 5))

# 3. 副标题 / 小提示
sub_label = tk.Label(
    root,
    text="输入任务 → 点击添加 → 完成！",
    font=("Microsoft YaHei", 10),
    bg="#f0f4f8",
    fg="#7f8c8d"                           # 灰色小字
)
sub_label.pack(pady=(0, 10))

# 4. 输入区域：一个 Frame 容器，包含输入框和添加按钮
input_frame = tk.Frame(root, bg="#f0f4f8")
input_frame.pack(pady=10)

# 4a. 创建输入框
entry = tk.Entry(
    input_frame,
    width=35,                               # 输入框宽度（字符数）
    font=("Microsoft YaHei", 13)
)
entry.pack(side=tk.LEFT, padx=(0, 8))       # 放在 Frame 左边，右边留8像素间距
entry.focus_set()                            # 让输入框自动获得焦点，打开就能打字


# 4b. 定义"添加任务"的函数
def add_task():
    """
    添加新任务到 Listbox
    ① 获取输入内容并去掉首尾空格
    ② 检查是否为空
    ③ 检查是否与已有任务重复
    ④ 满足条件就添加到列表末尾，并清空输入框
    """
    task = entry.get().strip()               # .get() 获取输入文字，.strip() 去掉首尾空格

    # 检查1：不能添加空白内容
    if not task:
        return                                # 空内容直接返回，不做任何操作

    # 检查2：防止重复添加
    all_tasks = listbox.get(0, tk.END)        # 获取 Listbox 中从第0项到末尾的所有任务
    if task in all_tasks:
        # 如果任务已存在，在底部状态标签中显示警告
        result_label.config(text="⚠️ 这个任务已经存在！", fg="#e74c3c")
        return                                # 重复则返回，不添加

    # 通过检查：添加任务
    listbox.insert(tk.END, task)              # tk.END 表示添加到列表末尾
    entry.delete(0, tk.END)                   # 清空输入框（从第0个字符删到末尾）
    result_label.config(text="✅ 任务已添加！", fg="#27ae60")  # 显示成功提示


# 4c. 创建"添加"按钮
add_btn = tk.Button(
    input_frame,
    text="➕ 添加",
    command=add_task,                        # 点击时调用 add_task 函数
    font=("Microsoft YaHei", 12, "bold"),
    bg="#3498db",                            # 按钮背景色：蓝色
    fg="white",                              # 按钮文字色：白色
    activebackground="#2980b9",              # 鼠标按下时的颜色：深蓝
    relief="flat",                           # 扁平样式
    padx=18, pady=6,                         # 内边距
    cursor="hand2"                           # 鼠标悬停时显示手指
)
add_btn.pack(side=tk.LEFT)                    # 放在输入框右边

# 4d. 绑定回车键：在输入框中按回车也能添加任务
root.bind("<Return>", lambda event: add_task())

# 5. 删除按钮（放在输入框下方）
def delete_task():
    """
    删除 Listbox 中当前选中的任务
    ① 获取选中项的索引
    ② 如果有选中项就删除
    """
    selected = listbox.curselection()        # 获取选中项的索引（返回元组，如 (2,)）
    if selected:                              # 如果有选中的项（元组不为空）
        listbox.delete(selected[0])           # 删除第一个选中的项（索引从元组中取）
        result_label.config(text="🗑 任务已删除", fg="#7f8c8d")  # 显示删除提示


delete_btn = tk.Button(
    root,
    text="🗑 删除选中",
    command=delete_task,                     # 点击时调用 delete_task 函数
    font=("Microsoft YaHei", 12, "bold"),
    bg="#e74c3c",                            # 按钮背景色：红色
    fg="white",                              # 按钮文字色：白色
    activebackground="#c0392b",              # 鼠标按下时的颜色：深红
    relief="flat",
    padx=18, pady=6,
    cursor="hand2"
)
delete_btn.pack(pady=(8, 10))

# 6. 任务列表 Listbox
listbox = tk.Listbox(
    root,
    width=40,                                # 列表宽度（字符数）
    height=12,                               # 列表高度（行数）
    font=("Microsoft YaHei", 13),
    bg="#ffffff",                            # 列表背景色：白色
    fg="#2c3e50",                            # 列表文字色：深蓝灰
    selectbackground="#aed6f1",              # 选中项的背景色：浅蓝
    selectforeground="#2c3e50"               # 选中项的文字色
)
listbox.pack(pady=5)

# 7. 底部状态提示标签
#    用于显示"添加成功"、"任务已存在"、"删除成功"等反馈信息
result_label = tk.Label(
    root,
    text="",                                 # 初始为空
    font=("Microsoft YaHei", 11),
    bg="#f0f4f8",
    fg="#7f8c8d"                             # 灰色
)
result_label.pack(pady=8)

# 8. 启动主循环（必须放在代码最后！）
root.mainloop()
