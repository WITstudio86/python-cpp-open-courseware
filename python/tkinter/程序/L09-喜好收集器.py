import tkinter as tk

# ========================================
# 第 9 节：Radiobutton + Checkbutton —— 喜好收集器
# ========================================

root = tk.Tk()
root.title("喜好收集器")
root.geometry("500x600")
root.configure(bg="#fce4ec")

# --- 标题 ---
title = tk.Label(
    root,
    text="📋 喜好收集器",
    font=("微软雅黑", 20, "bold"),
    fg="#880e4f",
    bg="#fce4ec"
)
title.pack(pady=15)

subtitle = tk.Label(
    root,
    text="告诉我你的喜好，让我更了解你～",
    font=("微软雅黑", 12),
    fg="#ad1457",
    bg="#fce4ec"
)
subtitle.pack()

# ============= 单选题：性别 =============
gender_frame = tk.Frame(root, bg="#ffffff", relief="groove", bd=2, padx=20, pady=15)
gender_frame.pack(pady=15, padx=40, fill="x")

tk.Label(
    gender_frame,
    text="① 你的性别（单选）",
    font=("微软雅黑", 14, "bold"),
    fg="#c2185b",
    bg="#ffffff"
).pack(anchor="w")

gender_var = tk.StringVar(value="")  # ← StringVar 存储选中的值

tk.Radiobutton(
    gender_frame,
    text="👦 男生",
    variable=gender_var,  # ← 绑定到同一个变量
    value="男生",         # ← 选中时，gender_var 的值
    font=("微软雅黑", 13),
    bg="#ffffff",
    activebackground="#fce4ec"
).pack(anchor="w", pady=3)

tk.Radiobutton(
    gender_frame,
    text="👧 女生",
    variable=gender_var,  # ← 同一个变量！
    value="女生",
    font=("微软雅黑", 13),
    bg="#ffffff",
    activebackground="#fce4ec"
).pack(anchor="w", pady=3)

tk.Radiobutton(
    gender_frame,
    text="🤫 保密",
    variable=gender_var,
    value="保密",
    font=("微软雅黑", 13),
    bg="#ffffff",
    activebackground="#fce4ec"
).pack(anchor="w", pady=3)

# ============= 多选题：兴趣爱好 =============
hobby_frame = tk.Frame(root, bg="#ffffff", relief="groove", bd=2, padx=20, pady=15)
hobby_frame.pack(pady=15, padx=40, fill="x")

tk.Label(
    hobby_frame,
    text="② 你的兴趣爱好（多选）",
    font=("微软雅黑", 14, "bold"),
    fg="#c2185b",
    bg="#ffffff"
).pack(anchor="w")

# 每个 Checkbutton 需要自己的 IntVar
hobby1_var = tk.IntVar()  # 0 = 未选中, 1 = 选中
hobby2_var = tk.IntVar()
hobby3_var = tk.IntVar()
hobby4_var = tk.IntVar()
hobby5_var = tk.IntVar()

hobbies = [
    ("🎮 玩游戏", hobby1_var),
    ("📖 阅读",    hobby2_var),
    ("⚽ 运动",    hobby3_var),
    ("🎨 画画",    hobby4_var),
    ("🎵 音乐",    hobby5_var),
]

for text, var in hobbies:
    tk.Checkbutton(
        hobby_frame,
        text=text,
        variable=var,      # ← 绑定到各自的 IntVar
        onvalue=1,         # 选中时值为 1
        offvalue=0,        # 未选中时值为 0
        font=("微软雅黑", 13),
        bg="#ffffff",
        activebackground="#fce4ec"
    ).pack(anchor="w", pady=3)

# ============= 结果显示区 =============
result_label = tk.Label(
    root,
    text="",
    font=("微软雅黑", 14),
    fg="#4a148c",
    bg="#fce4ec",
    justify="left",
    wraplength=400
)
result_label.pack(pady=15)

# ============= 提交按钮 =============
def submit():
    """收集所有选项，显示结果"""
    gender = gender_var.get()  # ← 读取单选结果

    # 读取多选结果
    selected_hobbies = []
    hobby_names = ["玩游戏", "阅读", "运动", "画画", "音乐"]
    hobby_vars = [hobby1_var, hobby2_var, hobby3_var, hobby4_var, hobby5_var]

    for name, var in zip(hobby_names, hobby_vars):
        if var.get() == 1:
            selected_hobbies.append(name)

    # 拼接显示文本
    result = f"性别：{gender}\n"
    if selected_hobbies:
        result += f"爱好：{'、'.join(selected_hobbies)}"
    else:
        result += "爱好：还没有选哦～"

    result_label.config(text=result)

submit_btn = tk.Button(
    root,
    text="✅ 提交我的喜好",
    command=submit,
    font=("微软雅黑", 14, "bold"),
    bg="#e91e63",
    fg="white",
    activebackground="#c2185b",
    padx=25,
    pady=8
)
submit_btn.pack(pady=5)

# --- 清空按钮 ---
def reset():
    """重置所有选项"""
    gender_var.set("")  # 清空单选
    hobby1_var.set(0)
    hobby2_var.set(0)
    hobby3_var.set(0)
    hobby4_var.set(0)
    hobby5_var.set(0)
    result_label.config(text="")

reset_btn = tk.Button(
    root,
    text="🔄 重新选择",
    command=reset,
    font=("微软雅黑", 12),
    bg="#f8bbd0",
    fg="#880e4f",
    padx=15,
    pady=5
)
reset_btn.pack(pady=5)

root.mainloop()
