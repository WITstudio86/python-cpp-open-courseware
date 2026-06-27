import tkinter as tk

# ========================================
# 第 39 节：倒计时番茄钟（上）
# 功能：设定工作分钟数 → Canvas 进度环 + Label 显示倒计时
# 核心技巧：after() 定时循环、create_arc 动态更新、Entry 输入
# ========================================

root = tk.Tk()
root.title("番茄钟 · 倒计时")
root.geometry("420x540")
root.configure(bg="#fafafa")
root.resizable(False, False)

# ========== 标题 ==========
title = tk.Label(
    root,
    text="🍅 番茄钟",
    font=("Arial", 24, "bold"),
    bg="#fafafa",
    fg="#e74c3c"  # 番茄红
)
title.pack(pady=(20, 5))

# ========== 时间输入区 ==========
input_frame = tk.Frame(root, bg="#fafafa")
input_frame.pack(pady=10)

# 标签：工作时间
tk.Label(
    input_frame,
    text="工作时间：",
    font=("Arial", 13),
    bg="#fafafa"
).pack(side=tk.LEFT)

# 输入框：分钟数
entry = tk.Entry(
    input_frame,
    font=("Arial", 16),
    width=4,
    justify="center",   # 文字居中
    relief="solid",     # 边框样式
    bd=1
)
entry.pack(side=tk.LEFT, padx=5)
entry.insert(0, "25")  # 默认 25 分钟（一个标准番茄钟）

# 标签：分钟
tk.Label(
    input_frame,
    text="分钟",
    font=("Arial", 13),
    bg="#fafafa"
).pack(side=tk.LEFT)

# ========== Canvas 进度环 ==========
canvas = tk.Canvas(
    root,
    width=300,
    height=300,
    bg="#fafafa",
    highlightthickness=0  # 去掉画布边框
)
canvas.pack(pady=10)

# 底部装饰环（浅灰色，不动，作为"总时长"的参考线）
canvas.create_arc(
    40, 40, 260, 260,       # 外接矩形：左上(40,40) 到 右下(260,260)
    start=90,               # 从 12 点钟方向开始
    extent=359.9,           # 几乎一整圈（不能设 360，否则不显示）
    outline="#e0e0e0",      # 浅灰色
    width=22,               # 弧线粗细（像素）
    style="arc"             # 只画弧线，不填充
)

# 进度弧（红色，随倒计时减少而缩短）
progress_arc = canvas.create_arc(
    40, 40, 260, 260,
    start=90,
    extent=359.9,           # 初始：满圈
    outline="#ff6b6b",      # 温暖的红色
    width=22,
    style="arc"
)

# 时间文字（叠在圆环中心）
time_label = tk.Label(
    canvas,
    text="25:00",
    font=("Arial", 42, "bold"),
    bg="#fafafa",
    fg="#333333"
)
# create_window 可以把 Label "嵌入"到 Canvas 的指定位置
canvas.create_window(150, 150, window=time_label)

# ========== 状态提示 ==========
status_label = tk.Label(
    root,
    text="准备开始",
    font=("Arial", 12),
    bg="#fafafa",
    fg="#888888"
)
status_label.pack(pady=5)

# ========== 按钮区 ==========
btn_frame = tk.Frame(root, bg="#fafafa")
btn_frame.pack(pady=10)


def start_timer():
    """
    开始倒计时：
      1. 从 Entry 获取用户输入的分钟数
      2. 转换成总秒数
      3. 禁用输入框和开始按钮（防止误操作）
      4. 启动 countdown() 循环
    """
    global total_seconds, original_total, running

    # 防止重复点击开始
    if running:
        return

    # 获取并验证输入
    try:
        minutes = int(entry.get())
        if minutes <= 0:
            status_label.config(text="请输入大于 0 的数字！", fg="#e74c3c")
            return
    except ValueError:
        status_label.config(text="请输入有效的数字！", fg="#e74c3c")
        return

    # 初始化倒计时
    total_seconds = minutes * 60
    original_total = total_seconds  # 保存初始总秒数（用于计算进度比例）
    running = True

    # 更新界面状态
    status_label.config(text="工作中… 专注！💪", fg="#2ecc71")
    entry.config(state="disabled")       # 计时中禁止修改
    start_btn.config(state="disabled")   # 计时中禁止再次点击

    # 开始倒计时循环
    countdown()


def countdown():
    """
    倒计时的核心函数 —— 每秒调用自己一次。
    每调用一次：秒数减 1 → 更新显示 → 更新进度环。
    秒数归零时停止。
    """
    global total_seconds, running

    if total_seconds > 0 and running:
        total_seconds -= 1

        # --- 更新 MM:SS 文字显示 ---
        m = total_seconds // 60   # 整除 → 剩余分钟
        s = total_seconds % 60    # 取余 → 剩余秒钟
        time_label.config(text=f"{m:02d}:{s:02d}")
        # :02d 表示保留两位数字，不足时前面补 0（如 05:03）

        # --- 更新进度弧 ---
        # 计算剩余比例：剩余秒数 / 总秒数
        progress = total_seconds / original_total
        # 动态修改弧的角度跨度
        canvas.itemconfig(progress_arc, extent=359.9 * progress)

        # 1 秒（1000 毫秒）后再调用自己
        root.after(1000, countdown)

    elif total_seconds <= 0 and running:
        # 时间到！
        running = False
        time_label.config(text="00:00")
        canvas.itemconfig(progress_arc, extent=0)  # 进度环归零
        status_label.config(text="时间到！休息一下吧 🎉", fg="#e74c3c")

        # 恢复按钮状态
        entry.config(state="normal")
        start_btn.config(state="normal")


def reset_timer():
    """
    重置倒计时：
      - 停止倒计时循环
      - 恢复显示为初始状态
      - 进度环恢复满圈
    """
    global total_seconds, running

    running = False                     # 停止循环
    total_seconds = 0

    # 恢复界面显示
    time_label.config(text="25:00")
    canvas.itemconfig(progress_arc, extent=359.9)  # 进度环满圈
    status_label.config(text="准备开始", fg="#888888")

    # 恢复按钮和输入框
    entry.config(state="normal")
    start_btn.config(state="normal")


# 开始按钮（绿色）
start_btn = tk.Button(
    btn_frame,
    text="▶ 开始计时",
    font=("Arial", 14, "bold"),
    bg="#2ecc71",
    fg="white",
    width=10,
    activebackground="#27ae60",
    command=start_timer
)
start_btn.pack(side=tk.LEFT, padx=5)

# 重置按钮（灰色）
reset_btn = tk.Button(
    btn_frame,
    text="↺ 重置",
    font=("Arial", 14),
    bg="#ecf0f1",
    fg="#333333",
    width=8,
    activebackground="#dfe4e5",
    command=reset_timer
)
reset_btn.pack(side=tk.LEFT, padx=5)

# ========== 全局变量 ==========
total_seconds = 0        # 剩余总秒数
original_total = 25 * 60  # 初始总秒数（默认 25 分钟）
running = False           # 是否正在计时

root.mainloop()
