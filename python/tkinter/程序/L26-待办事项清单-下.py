import tkinter as tk

# ========================================
# 第 26 节：项目 4 — 待办事项清单（完整版）
# 功能：添加、删除、标记完成、保存到文件、启动加载
# ========================================

# 1. 创建主窗口
root = tk.Tk()
root.title("待办事项清单 📝")
root.geometry("500x520")
root.configure(bg="#f5f0e8")  # 米白色背景，温暖舒适

# ========================================
# 2. 功能函数定义
# ========================================

def add_task():
    """添加新任务到列表"""
    task = entry.get().strip()  # 获取输入框内容，去掉首尾空格
    if task:  # 如果输入不为空
        listbox.insert(tk.END, task)  # 插入到列表末尾
        entry.delete(0, tk.END)       # 清空输入框


def delete_task():
    """删除选中的任务"""
    selection = listbox.curselection()  # 获取选中项的索引（元组）
    if selection:  # 如果有选中的项
        listbox.delete(selection[0])    # 删除第一个选中的


def mark_done():
    """标记选中的任务为「已完成」
    方法：在文字前加 ✓ ，并把文字颜色改成灰色
    """
    selection = listbox.curselection()
    if selection:
        i = selection[0]                # 取索引
        task = listbox.get(i)           # 获取该项的文字
        if not task.startswith("✓ "):   # 如果还没被标记过
            listbox.delete(i)           # 删掉旧的
            listbox.insert(i, "✓ " + task)  # 插入带 ✓ 的新文字
            listbox.itemconfig(i, fg="gray")  # 把前景色改成灰色


def save_tasks():
    """把所有任务保存到 tasks.txt 文件中"""
    with open("tasks.txt", "w", encoding="utf-8") as f:
        # 获取 Listbox 中所有项目（从索引 0 到 END）
        all_tasks = listbox.get(0, tk.END)
        for task in all_tasks:
            f.write(task + "\n")  # 每行一个任务
    print("💾 任务已保存到 tasks.txt")


def load_tasks():
    """程序启动时，从 tasks.txt 加载已有的任务"""
    try:
        with open("tasks.txt", "r", encoding="utf-8") as f:
            lines = f.readlines()  # 读取所有行
            for line in lines:
                task = line.strip()  # 去掉行末的换行符 \n
                if task:  # 跳过空行
                    listbox.insert(tk.END, task)
                    # 如果这个任务是已完成状态，恢复灰色
                    if task.startswith("✓ "):
                        last_idx = listbox.size() - 1  # 最后一项的索引
                        listbox.itemconfig(last_idx, fg="gray")
    except FileNotFoundError:
        # 第一次运行没有 tasks.txt 文件，很正常，跳过即可
        print("📂 未找到 tasks.txt，将创建新文件")
        pass


def on_closing():
    """窗口关闭时的处理：先保存，再关闭"""
    save_tasks()
    root.destroy()  # 真正关闭窗口


# ========================================
# 3. 界面布局
# ========================================

# --- 标题 ---
title_label = tk.Label(
    root,
    text="📝 我的待办清单",
    font=("微软雅黑", 22, "bold"),
    bg="#f5f0e8",
    fg="#5a4a3a"  # 深棕色文字
)
title_label.pack(pady=(20, 10))

# --- 输入区域 ---
input_frame = tk.Frame(root, bg="#f5f0e8")
input_frame.pack(pady=5)

entry = tk.Entry(
    input_frame,
    font=("微软雅黑", 14),
    width=30,
    relief="solid",
    bd=1
)
entry.pack(side=tk.LEFT, padx=(0, 5))

# 绑定回车键：在输入框按回车也能添加任务
entry.bind("<Return>", lambda event: add_task())

add_btn = tk.Button(
    input_frame,
    text="➕ 添加",
    command=add_task,
    font=("微软雅黑", 12, "bold"),
    bg="#7d9d6e",      # 绿色
    fg="white",
    padx=15,
    relief="flat",
    cursor="hand2"     # 鼠标悬停时变成手型
)
add_btn.pack(side=tk.LEFT)

# --- 任务列表 ---
listbox = tk.Listbox(
    root,
    font=("微软雅黑", 13),
    width=45,
    height=14,
    selectmode=tk.SINGLE,       # 单选模式
    bg="#fffaf0",               # 奶白色列表背景
    fg="#3a3a3a",
    selectbackground="#c8d6af", # 选中项的背景色（淡绿）
    selectforeground="#2a2a2a",
    relief="solid",
    bd=1
)
listbox.pack(pady=15)

# --- 操作按钮区 ---
btn_frame = tk.Frame(root, bg="#f5f0e8")
btn_frame.pack(pady=10)

# 标记完成按钮（黄色）
tk.Button(
    btn_frame, text="✅ 标记完成", command=mark_done,
    font=("微软雅黑", 12), bg="#f0c060", fg="#5a4a3a",
    padx=12, relief="flat", cursor="hand2"
).pack(side=tk.LEFT, padx=6)

# 删除按钮（红色）
tk.Button(
    btn_frame, text="🗑️ 删除", command=delete_task,
    font=("微软雅黑", 12), bg="#e07060", fg="white",
    padx=18, relief="flat", cursor="hand2"
).pack(side=tk.LEFT, padx=6)

# 手动保存按钮（蓝色）
tk.Button(
    btn_frame, text="💾 保存", command=save_tasks,
    font=("微软雅黑", 12), bg="#60a0c0", fg="white",
    padx=18, relief="flat", cursor="hand2"
).pack(side=tk.LEFT, padx=6)

# ========================================
# 4. 启动程序
# ========================================

# 程序启动时，先加载已有任务
load_tasks()

# 设置关闭窗口时的回调：自动保存
root.protocol("WM_DELETE_WINDOW", on_closing)

# 让输入框获得焦点（光标自动出现在输入框里）
entry.focus_set()

# 启动主循环
root.mainloop()
