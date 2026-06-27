import tkinter as tk

# ========================================
# 第 3 节：Button 按钮 —— 点我计数小工具
# ========================================

# 1. 创建窗口
root = tk.Tk()
root.title("点我计数小工具")
root.geometry("450x400")
root.configure(bg="#e8f0fe")  # 浅蓝色背景

# --- 计数变量 ---
count = 0  # 用普通变量记录点击次数（定义在函数外，是"全局变量"）

# --- 标题 Label ---
title = tk.Label(
    root,
    text="🖱️ 点我计数小工具",
    font=("微软雅黑", 20, "bold"),
    fg="#1a237e",    # 深蓝色文字
    bg="#e8f0fe"
)
title.pack(pady=20)

# --- 计数显示 Label ---
count_label = tk.Label(
    root,
    text="点击次数：0",
    font=("微软雅黑", 16),
    fg="#283593",
    bg="#e8f0fe"
)
count_label.pack(pady=10)

# --- 点击按钮 ---
def add_count():
    """点击一次，计数 +1，更新显示"""
    global count                      # 声明要修改全局变量 count
    count += 1                        # 次数 +1
    count_label.config(text=f"点击次数：{count}")  # f-string 更新文字
    # 根据次数改变颜色 —— 给用户视觉反馈
    if count >= 20:
        count_label.config(fg="#c62828")  # 红色：超过 20 次了！
    elif count >= 10:
        count_label.config(fg="#e65100")  # 橙色：超过 10 次了

click_btn = tk.Button(
    root,
    text="👆 点我！",
    command=add_count,               # ← 注意：函数名不加括号！
    font=("微软雅黑", 18, "bold"),
    bg="#42a5f5",                    # 蓝色背景
    fg="white",                      # 白色文字
    activebackground="#1e88e5",      # 鼠标悬停时的背景色
    activeforeground="white",        # 鼠标悬停时的文字色
    padx=30,                         # 左右内边距
    pady=10,                         # 上下内边距
    relief="raised",                 # 凸起边框
    bd=3                             # 边框宽度
)
click_btn.pack(pady=15)

# --- 重置按钮 ---
def reset_count():
    """重置计数为 0"""
    global count                     # 声明修改全局变量
    count = 0                        # 归零
    count_label.config(text="点击次数：0", fg="#283593")  # 恢复默认颜色

reset_btn = tk.Button(
    root,
    text="🔄 归零",
    command=reset_count,
    font=("微软雅黑", 12),
    bg="#78909c",                    # 灰色背景
    fg="white",
    padx=20,
    pady=5
)
reset_btn.pack(pady=5)

# --- 切换按钮（演示文字切换） ---
is_on = False  # 状态标记：False=关闭, True=开启

def toggle():
    """切换按钮文字和颜色 —— Toggle 模式"""
    global is_on
    is_on = not is_on                # 翻转状态（not：True 变 False，False 变 True）
    if is_on:
        # 开启状态：红色
        toggle_btn.config(text="🔴 已开启", bg="#ef5350")
    else:
        # 关闭状态：绿色
        toggle_btn.config(text="🟢 已关闭", bg="#66bb6a")

toggle_btn = tk.Button(
    root,
    text="🟢 已关闭",
    command=toggle,
    font=("微软雅黑", 12),
    bg="#66bb6a",                    # 绿色（初始为关闭状态）
    fg="white",
    padx=20,
    pady=5
)
toggle_btn.pack(pady=10)

# --- 提示 Label ---
tip = tk.Label(
    root,
    text="试试连续点击，看看颜色会不会变？",
    font=("微软雅黑", 10),
    fg="#78909c",                    # 灰色提示文字
    bg="#e8f0fe"
)
tip.pack(pady=15)

# 2. 启动主循环 —— 让窗口一直显示
root.mainloop()
