# ============================================
# 第 2 课：Label 标签和 Button 按钮
# ============================================

import tkinter as tk

# --- 创建窗口 ---
window = tk.Tk()
window.title("我的备忘录")
window.geometry("400x500")

# --- 定义函数 ---

click_count = 0  # 计数器

def on_button_click():
    """按钮被点击时执行"""
    global click_count
    click_count = click_count + 1
    print(f"按钮被点击了！第 {click_count} 次")
    # 更新标签文字
    info_label.config(text=f"按钮已被点击 {click_count} 次")

# --- 创建控件 ---

# 1. 大标题标签
title_label = tk.Label(
    window,
    text="📝 我的备忘录",
    font=("微软雅黑", 20, "bold"),
    fg="#333333"
)
title_label.pack(pady=15)

# 2. 副标题标签
subtitle_label = tk.Label(
    window,
    text="用 Python 打造自己的专属工具！",
    font=("微软雅黑", 10),
    fg="#888888"
)
subtitle_label.pack(pady=5)

# 3. 点击按钮
btn = tk.Button(
    window,
    text="点击我！",
    font=("微软雅黑", 14),
    command=on_button_click,
    bg="#4CAF50",
    fg="white",
    padx=20,
    pady=10
)
btn.pack(pady=20)

# 4. 点击次数显示标签
info_label = tk.Label(
    window,
    text="还没有点击过",
    font=("微软雅黑", 12),
    fg="#666666"
)
info_label.pack(pady=10)

# 5. 退出按钮
quit_btn = tk.Button(
    window,
    text="退出程序",
    font=("微软雅黑", 10),
    command=window.destroy,
    bg="#f44336",
    fg="white"
)
quit_btn.pack(pady=30)

# 6. 底部说明
footer_label = tk.Label(
    window,
    text="第 2 课 · Label 与 Button",
    font=("微软雅黑", 8),
    fg="#CCCCCC"
)
footer_label.pack(side=tk.BOTTOM, pady=10)

# --- 运行主循环 ---
window.mainloop()
