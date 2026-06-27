import tkinter as tk

# ========================================
# 第 7 节：pack 布局（下）+ grid 入门 —— 两种布局对比
# ========================================

root = tk.Tk()
root.title("两种布局对比演示")
root.geometry("700x550")
root.configure(bg="#fafafa")

# --- 标题 ---
title = tk.Label(
    root,
    text="📐 两种布局方式对比",
    font=("微软雅黑", 20, "bold"),
    fg="#37474f",
    bg="#fafafa"
)
title.pack(pady=10)

# ============= 上方：pack 布局演示 =============
pack_label = tk.Label(
    root,
    text="⬇ pack 布局 —— 灵活排列",
    font=("微软雅黑", 14, "bold"),
    fg="#0277bd",
    bg="#fafafa"
)
pack_label.pack()

pack_frame = tk.Frame(
    root,
    bg="#e1f5fe",
    relief="groove",
    bd=2,
    width=620,
    height=180
)
pack_frame.pack(pady=8, padx=40, fill="x")
pack_frame.pack_propagate(False)  # 保持固定大小

# pack: 用 side 参数控制排列方向
btn_top = tk.Button(pack_frame, text="↑ 顶部 (TOP)", bg="#42a5f5", fg="white")
btn_top.pack(side="top", fill="x", padx=5, pady=2)

btn_left = tk.Button(pack_frame, text="← 左侧 (LEFT)", bg="#66bb6a", fg="white")
btn_left.pack(side="left", fill="y", padx=5, pady=2)

btn_right = tk.Button(pack_frame, text="右侧 (RIGHT) →", bg="#ffa726", fg="white")
btn_right.pack(side="right", fill="y", padx=5, pady=2)

btn_bottom = tk.Button(pack_frame, text="↓ 底部 (BOTTOM)", bg="#ef5350", fg="white")
btn_bottom.pack(side="bottom", fill="x", padx=5, pady=2)

# ============= 下方：grid 布局演示 =============
grid_label = tk.Label(
    root,
    text="⬇ grid 布局 —— 像表格一样精确",
    font=("微软雅黑", 14, "bold"),
    fg="#6a1b9a",
    bg="#fafafa"
)
grid_label.pack(pady=(20, 5))

grid_frame = tk.Frame(
    root,
    bg="#f3e5f5",
    relief="groove",
    bd=2,
    width=620,
    height=180
)
grid_frame.pack(pady=8, padx=40, fill="x")
grid_frame.pack_propagate(False)

# grid: 用 row 和 column 定位
# 第 0 行
tk.Button(grid_frame, text="(0,0)", bg="#ab47bc", fg="white", width=8, height=2
).grid(row=0, column=0, padx=3, pady=3)

tk.Button(grid_frame, text="(0,1)", bg="#ab47bc", fg="white", width=8, height=2
).grid(row=0, column=1, padx=3, pady=3)

tk.Button(grid_frame, text="(0,2)", bg="#ab47bc", fg="white", width=8, height=2
).grid(row=0, column=2, padx=3, pady=3)

# 第 1 行
tk.Button(grid_frame, text="(1,0)", bg="#ce93d8", fg="white", width=8, height=2
).grid(row=1, column=0, padx=3, pady=3)

tk.Button(grid_frame, text="(1,1)", bg="#ce93d8", fg="white", width=8, height=2
).grid(row=1, column=1, padx=3, pady=3)

tk.Button(grid_frame, text="(1,2)", bg="#ce93d8", fg="white", width=8, height=2
).grid(row=1, column=2, padx=3, pady=3)

# 第 2 行
tk.Button(grid_frame, text="(2,0)", bg="#ba68c8", fg="white", width=8, height=2
).grid(row=2, column=0, padx=3, pady=3)

tk.Button(grid_frame, text="(2,1)", bg="#ba68c8", fg="white", width=8, height=2
).grid(row=2, column=1, padx=3, pady=3)

tk.Button(grid_frame, text="(2,2)", bg="#ba68c8", fg="white", width=8, height=2
).grid(row=2, column=2, padx=3, pady=3)

# --- 底部对比说明 ---
note = tk.Label(
    root,
    text="💡 pack 适合简单的上下/左右排列 | grid 适合表格/九宫格/计算器类型的界面",
    font=("微软雅黑", 10),
    fg="#78909c",
    bg="#fafafa",
    wraplength=600
)
note.pack(pady=15)

root.mainloop()
