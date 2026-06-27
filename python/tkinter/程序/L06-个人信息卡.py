import tkinter as tk

# ========================================
# 第 6 节：Frame 框架 + pack 布局 —— 个人信息卡
# ========================================

root = tk.Tk()
root.title("个人信息卡")
root.geometry("450x550")
root.configure(bg="#fff8e1")

# --- 主标题 ---
title = tk.Label(
    root,
    text="📇 个人信息卡",
    font=("微软雅黑", 20, "bold"),
    fg="#e65100",
    bg="#fff8e1"
)
title.pack(pady=15)

# ============= Frame 1：基本信息区 =============
frame_basic = tk.Frame(
    root,
    bg="#ffffff",
    relief="groove",  # 边框样式
    bd=2,             # 边框宽度
    padx=15,
    pady=15
)
frame_basic.pack(pady=10, padx=30, fill="x")

# 在 frame_basic 里面放 Label
tk.Label(
    frame_basic,  # ← 注意：parent 是 frame_basic，不是 root！
    text="👤 基本信息",
    font=("微软雅黑", 14, "bold"),
    fg="#bf360c",
    bg="#ffffff"
).pack(anchor="w")  # anchor 控制对齐方向

tk.Label(
    frame_basic,
    text="姓名：小明同学",
    font=("微软雅黑", 12),
    fg="#4e342e",
    bg="#ffffff"
).pack(anchor="w", pady=2)

tk.Label(
    frame_basic,
    text="年龄：13 岁",
    font=("微软雅黑", 12),
    fg="#4e342e",
    bg="#ffffff"
).pack(anchor="w", pady=2)

tk.Label(
    frame_basic,
    text="班级：七年级（3）班",
    font=("微软雅黑", 12),
    fg="#4e342e",
    bg="#ffffff"
).pack(anchor="w", pady=2)

# ============= Frame 2：爱好区 =============
frame_hobby = tk.Frame(
    root,
    bg="#e8f5e9",
    relief="ridge",
    bd=2,
    padx=15,
    pady=15
)
frame_hobby.pack(pady=10, padx=30, fill="x")

tk.Label(
    frame_hobby,
    text="🌟 兴趣爱好",
    font=("微软雅黑", 14, "bold"),
    fg="#1b5e20",
    bg="#e8f5e9"
).pack(anchor="w")

tk.Label(
    frame_hobby,
    text="🎮 编程\n📚 阅读科幻小说\n⚽ 踢足球",
    font=("微软雅黑", 12),
    fg="#33691e",
    bg="#e8f5e9",
    justify="left"
).pack(anchor="w", pady=5)

# ============= Frame 3：学习目标区 =============
frame_goal = tk.Frame(
    root,
    bg="#e3f2fd",
    relief="groove",
    bd=2,
    padx=15,
    pady=15
)
frame_goal.pack(pady=10, padx=30, fill="x")

tk.Label(
    frame_goal,
    text="🎯 学习目标",
    font=("微软雅黑", 14, "bold"),
    fg="#0d47a1",
    bg="#e3f2fd"
).pack(anchor="w")

tk.Label(
    frame_goal,
    text="✅ 学会 Python 基础\n✅ 掌握 tkinter 图形界面\n⬜ 做出自己的第一个 App",
    font=("微软雅黑", 12),
    fg="#1565c0",
    bg="#e3f2fd",
    justify="left"
).pack(anchor="w", pady=5)

# --- 底部按钮 ---
btn_frame = tk.Frame(root, bg="#fff8e1")
btn_frame.pack(pady=15)

tk.Button(
    btn_frame,
    text="👍 赞",
    font=("微软雅黑", 12, "bold"),
    bg="#4caf50",
    fg="white",
    padx=20,
    pady=5
).pack(side="left", padx=5)

tk.Button(
    btn_frame,
    text="💬 留言",
    font=("微软雅黑", 12, "bold"),
    bg="#2196f3",
    fg="white",
    padx=20,
    pady=5
).pack(side="left", padx=5)

tk.Button(
    btn_frame,
    text="🔗 分享",
    font=("微软雅黑", 12, "bold"),
    bg="#ff9800",
    fg="white",
    padx=20,
    pady=5
).pack(side="left", padx=5)

root.mainloop()
