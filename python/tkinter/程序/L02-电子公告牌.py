import tkinter as tk

# ========================================
# 第 2 节：Label 标签 —— 电子公告牌
# ========================================

# 1. 创建窗口
root = tk.Tk()
root.title("电子公告牌")
root.geometry("600x500")
root.configure(bg="#f5f0e8")  # 暖色背景，像一张牛皮纸

# --- 标题 Label：大号字体，深色 ---
title_label = tk.Label(
    root,
    text="📢 电子公告牌",
    font=("微软雅黑", 24, "bold"),  # 24号加粗字体
    fg="#2c3e50",                    # 深灰蓝色文字
    bg="#f5f0e8"                     # 背景色和窗口一致
)
title_label.pack(pady=15)  # pady 设置上下间距

# --- 公告内容 Label：不同样式来区分不同类型 ---

# 公告 1：通知类 —— 红色文字，醒目
notice = tk.Label(
    root,
    text="【通知】明天下午 3 点有编程比赛！",
    font=("微软雅黑", 14),           # 14号普通字体
    fg="#c0392b",                    # 红色文字，表示重要通知
    bg="#f5f0e8"
)
notice.pack(pady=5)

# 公告 2：活动类 —— 蓝色斜体，轻松活泼
activity = tk.Label(
    root,
    text="【活动】周末一起去科技馆参观～",
    font=("微软雅黑", 14, "italic"),  # 斜体表示活动
    fg="#2980b9",                     # 蓝色文字
    bg="#f5f0e8"
)
activity.pack(pady=5)

# 公告 3：提醒类 —— 带黄色背景，像便利贴！
reminder = tk.Label(
    root,
    text="⚠️ 别忘了带你的学生证！",
    font=("微软雅黑", 13),
    fg="#e67e22",                    # 橙色文字
    bg="#fff3cd",                    # 浅黄色背景，像便利贴
    padx=10,                         # 左右内边距 10 像素
    pady=5                           # 上下内边距 5 像素
)
reminder.pack(pady=10)

# --- 带边框的公告区域（用 Frame 包裹 Label）---
frame = tk.Frame(
    root,
    bg="#ffffff",                    # 白色背景
    relief="groove",                 # 凹陷边框样式
    bd=2                             # 边框宽度 2 像素
)
frame.pack(pady=20, padx=40, fill="x")  # fill="x" 让 Frame 横向撑满

long_text = tk.Label(
    frame,
    text="欢迎来到我们的公告牌！\n这里会发布最新的课程信息、\n活动通知和重要提醒。\n记得经常来看看哦~",  # \n 手动换行
    font=("微软雅黑", 12),
    fg="#34495e",
    bg="#ffffff",
    justify="left",                  # 多行文字左对齐
    wraplength=400,                  # 超过 400 像素自动换行
    padx=15,                         # 左右内边距
    pady=15                          # 上下内边距
)
long_text.pack()

# --- 用 StringVar 控制的动态 Label ---
# StringVar 就像一个"魔术变量"，改变它的值，Label 自动更新！
var_text = tk.StringVar()            # 创建一个 StringVar 对象
var_text.set("点击下方按钮可以修改这段文字哦 ↑")  # 设置初始文字

dynamic_label = tk.Label(
    root,
    textvariable=var_text,           # ← 注意！是 textvariable，不是 text
    font=("微软雅黑", 11, "italic"),
    fg="#7f8c8d",                    # 灰色文字
    bg="#f5f0e8"
)
dynamic_label.pack(pady=10)

# 按钮：点击后修改 StringVar 的值
def change_text():
    """修改 var_text 的值，Label 上的文字会自动更新"""
    var_text.set("✅ 文字已经改变！StringVar 让 Label 活起来了！")

change_btn = tk.Button(
    root,
    text="点我修改文字",
    command=change_text,             # 点击按钮时调用 change_text 函数
    font=("微软雅黑", 12),
    bg="#3498db",                    # 蓝色按钮
    fg="white",                      # 白色文字
    padx=20
)
change_btn.pack(pady=5)

# 2. 启动主循环 —— 让窗口一直显示
root.mainloop()
