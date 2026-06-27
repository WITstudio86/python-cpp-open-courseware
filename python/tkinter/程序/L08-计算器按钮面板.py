import tkinter as tk

# ========================================
# 第 8 节：grid 布局实战 —— 计算器按钮面板
# 说明：本课只做界面，不实现计算逻辑
# ========================================

root = tk.Tk()
root.title("计算器")
root.geometry("350x480")
root.configure(bg="#263238")

# --- 标题 ---
title = tk.Label(
    root,
    text="🔢 计算器",
    font=("微软雅黑", 16, "bold"),
    fg="#ffffff",
    bg="#263238"
)
title.grid(row=0, column=0, columnspan=4, pady=(10, 5))

# --- 显示区域（模拟屏幕） ---
display = tk.Label(
    root,
    text="0",
    font=("Consolas", 28, "bold"),
    fg="#ffffff",
    bg="#37474f",
    anchor="e",      # 文字靠右对齐
    padx=15,
    pady=15,
    relief="sunken",
    bd=3
)
display.grid(
    row=1, column=0,
    columnspan=4,    # ← 跨 4 列！
    sticky="nsew",   # ← 填满整个格子
    padx=10, pady=10
)

# --- 按钮样式 ---
btn_config = {
    "font": ("微软雅黑", 14, "bold"),
    "width": 5,
    "height": 2,
    "relief": "raised",
    "bd": 2
}

# --- 第 2 行：C, ÷, ×, ⌫ ---
tk.Button(root, text="C",  bg="#ef5350", fg="white", **btn_config
).grid(row=2, column=0, padx=2, pady=2, sticky="nsew")

tk.Button(root, text="÷", bg="#ffa726", fg="white", **btn_config
).grid(row=2, column=1, padx=2, pady=2, sticky="nsew")

tk.Button(root, text="×", bg="#ffa726", fg="white", **btn_config
).grid(row=2, column=2, padx=2, pady=2, sticky="nsew")

tk.Button(root, text="⌫", bg="#ffa726", fg="white", **btn_config
).grid(row=2, column=3, padx=2, pady=2, sticky="nsew")

# --- 第 3 行：7, 8, 9, - ---
tk.Button(root, text="7", bg="#546e7a", fg="white", **btn_config
).grid(row=3, column=0, padx=2, pady=2, sticky="nsew")

tk.Button(root, text="8", bg="#546e7a", fg="white", **btn_config
).grid(row=3, column=1, padx=2, pady=2, sticky="nsew")

tk.Button(root, text="9", bg="#546e7a", fg="white", **btn_config
).grid(row=3, column=2, padx=2, pady=2, sticky="nsew")

tk.Button(root, text="−", bg="#ffa726", fg="white", **btn_config
).grid(row=3, column=3, padx=2, pady=2, sticky="nsew")

# --- 第 4 行：4, 5, 6, + ---
tk.Button(root, text="4", bg="#546e7a", fg="white", **btn_config
).grid(row=4, column=0, padx=2, pady=2, sticky="nsew")

tk.Button(root, text="5", bg="#546e7a", fg="white", **btn_config
).grid(row=4, column=1, padx=2, pady=2, sticky="nsew")

tk.Button(root, text="6", bg="#546e7a", fg="white", **btn_config
).grid(row=4, column=2, padx=2, pady=2, sticky="nsew")

tk.Button(root, text="+", bg="#ffa726", fg="white", **btn_config
).grid(row=4, column=3, padx=2, pady=2, sticky="nsew")

# --- 第 5 行：1, 2, 3, =（跨行） ---
tk.Button(root, text="1", bg="#546e7a", fg="white", **btn_config
).grid(row=5, column=0, padx=2, pady=2, sticky="nsew")

tk.Button(root, text="2", bg="#546e7a", fg="white", **btn_config
).grid(row=5, column=1, padx=2, pady=2, sticky="nsew")

tk.Button(root, text="3", bg="#546e7a", fg="white", **btn_config
).grid(row=5, column=2, padx=2, pady=2, sticky="nsew")

tk.Button(root, text="=", bg="#66bb6a", fg="white", font=("微软雅黑", 16, "bold"), width=5, height=5, relief="raised", bd=2
).grid(row=5, column=3, rowspan=2, padx=2, pady=2, sticky="nsew")  # ← 跨 2 行！

# --- 第 6 行：0（跨 2 列）, . ---
tk.Button(root, text="0", bg="#546e7a", fg="white", **btn_config
).grid(row=6, column=0, columnspan=2, padx=2, pady=2, sticky="nsew")  # ← 跨 2 列！

tk.Button(root, text=".", bg="#546e7a", fg="white", **btn_config
).grid(row=6, column=2, padx=2, pady=2, sticky="nsew")

# --- 让行列均匀拉伸 ---
for i in range(7):   # 让每一行都能拉伸
    root.grid_rowconfigure(i, weight=1)
for j in range(4):   # 让每一列都能拉伸
    root.grid_columnconfigure(j, weight=1)

# --- 底部提示 ---
tip = tk.Label(
    root,
    text="⚠ 目前只有界面，计算功能在后面课程实现",
    font=("微软雅黑", 9),
    fg="#78909c",
    bg="#263238"
)
tip.grid(row=7, column=0, columnspan=4, pady=(8, 5))

root.mainloop()
