import tkinter as tk
import random

# ========================================
# 第 45 节：打字速度测试（中）—— 倒计时 + WPM 统计
# ========================================

SAMPLES = [
    "今天天气真好，阳光洒在操场上，同学们在快乐地跑步。",
    "Python 是一门非常有趣的编程语言，简单又强大。",
    "千里之行，始于足下。学习编程也是一步一步来的。",
    "春天来了，花儿开了，小鸟在枝头唱着欢快的歌。",
    "努力不一定会成功，但不努力一定不会成功。",
    "书籍是人类进步的阶梯，多读书，读好书。",
    "学习编程就像搭积木，一块一块地累积起来。",
]

root = tk.Tk()
root.title("打字速度测试 V2.0")
root.geometry("700x520")
root.configure(bg="#f5f5f5")

current_text = random.choice(SAMPLES)
time_left = 60
timer_running = False

# ---------- 顶部信息栏 ----------
info_frame = tk.Frame(root, bg="#f5f5f5")
info_frame.pack(pady=(15, 5), fill=tk.X, padx=30)

title_label = tk.Label(info_frame, text="⌨️ 打字速度测试",
                       font=("微软雅黑", 16, "bold"), bg="#f5f5f5", fg="#333")
title_label.pack(side=tk.LEFT)

timer_label = tk.Label(info_frame, text=f"⏱️ 剩余时间：{time_left} 秒",
                       font=("微软雅黑", 14, "bold"), bg="#f5f5f5", fg="#e65100")
timer_label.pack(side=tk.RIGHT)


# ---------- 范文显示区域 ----------
sample_frame = tk.Frame(root, bg="white", relief=tk.RIDGE, bd=2)
sample_frame.pack(pady=10, padx=30, fill=tk.X)

tk.Label(sample_frame, text="📝 请打以下文字：", font=("微软雅黑", 11),
         bg="white", fg="#888", anchor="w").pack(anchor="w", padx=15, pady=(10, 0))

text_label = tk.Label(sample_frame, text=current_text,
                       font=("微软雅黑", 15), bg="white", fg="#333",
                       wraplength=620, justify="left", padx=15, pady=10)
text_label.pack()

# ---------- 打字输入区域 ----------
tk.Label(root, text="👇 在下面输入：", font=("微软雅黑", 11),
         bg="#f5f5f5", fg="#888").pack(anchor="w", padx=33, pady=(15, 5))

input_text = tk.Text(root, font=("微软雅黑", 15), height=4, width=54,
                     wrap="word", bg="white", relief=tk.SUNKEN, bd=1,
                     state="disabled")  # 初始禁用，点击开始后才能输入
input_text.pack(pady=0, padx=30)

# 配置高亮 tag
input_text.tag_config("correct", foreground="#2e7d32")       # 正确 = 绿色
input_text.tag_config("wrong", foreground="#c62828",
                      background="#ffebee")                   # 错误 = 红色


def check_typing(event=None):
    """实时逐字对比：正确的字变绿，错误的字变红"""
    user_text = input_text.get("1.0", tk.END).rstrip("\n")

    # 清除之前的高亮
    input_text.tag_remove("correct", "1.0", tk.END)
    input_text.tag_remove("wrong", "1.0", tk.END)

    # 逐字对比
    for i, char in enumerate(user_text):
        pos = f"1.{i}"
        if i < len(current_text) and char == current_text[i]:
            input_text.tag_add("correct", pos)
        else:
            input_text.tag_add("wrong", pos)


input_text.bind("<KeyRelease>", check_typing)


# ---------- 倒计时 ----------
def update_timer():
    """每秒更新一次倒计时"""
    global time_left
    if time_left > 0 and timer_running:
        time_left -= 1
        timer_label.config(text=f"⏱️ 剩余时间：{time_left} 秒")
        root.after(1000, update_timer)  # 1 秒后再调用自己
    elif time_left == 0:
        show_result()  # 时间到，显示成绩


# ---------- 统计计算 ----------
def calculate_wpm():
    """计算 WPM（每分钟正确打字数）"""
    user_text = input_text.get("1.0", tk.END).rstrip("\n")
    elapsed = 60 - time_left  # 已经用掉的秒数
    if elapsed == 0:
        return 0

    # 统计正确的字符数
    correct_count = sum(
        1 for i, char in enumerate(user_text)
        if i < len(current_text) and char == current_text[i]
    )

    # WPM = 正确字数 / 已用秒数 × 60
    wpm = (correct_count / elapsed) * 60
    return round(wpm, 1)


def calculate_accuracy():
    """计算准确率（百分比）"""
    user_text = input_text.get("1.0", tk.END).rstrip("\n")
    if len(user_text) == 0:
        return 0

    correct_count = sum(
        1 for i, char in enumerate(user_text)
        if i < len(current_text) and char == current_text[i]
    )

    # 准确率 = 正确字数 / 总打字数 × 100%
    accuracy = (correct_count / len(user_text)) * 100
    return round(accuracy, 1)


# ---------- 显示成绩 ----------
def show_result():
    """时间到，弹出成绩窗口"""
    global timer_running
    timer_running = False
    input_text.config(state="disabled")  # 禁用输入

    wpm = calculate_wpm()
    accuracy = calculate_accuracy()

    result_win = tk.Toplevel(root)
    result_win.title("打字成绩")
    result_win.geometry("350x280")
    result_win.configure(bg="#e8f5e9")
    result_win.grab_set()  # 强制聚焦在这个窗口

    tk.Label(result_win, text="🏆 打字成绩", font=("微软雅黑", 18, "bold"),
             bg="#e8f5e9").pack(pady=15)

    tk.Label(result_win, text=f"速度：{wpm} 字/分钟",
             font=("微软雅黑", 16), bg="#e8f5e9", fg="#1565c0").pack(pady=5)

    tk.Label(result_win, text=f"准确率：{accuracy}%",
             font=("微软雅黑", 16), bg="#e8f5e9", fg="#2e7d32").pack(pady=5)

    # 根据成绩给出评价
    if wpm >= 60 and accuracy >= 95:
        grade = "🌟 打字高手！"
    elif wpm >= 30 and accuracy >= 80:
        grade = "👍 不错哦，继续加油！"
    else:
        grade = "💪 多多练习，就会越来越快！"

    tk.Label(result_win, text=grade, font=("微软雅黑", 14),
             bg="#e8f5e9", fg="#e65100").pack(pady=15)

    tk.Button(result_win, text="关闭", command=result_win.destroy,
              bg="#c8e6c9", font=("微软雅黑", 11), width=10).pack(pady=10)


# ---------- 按钮区域 ----------
def start_test():
    """开始打字测试"""
    global timer_running, time_left, current_text

    # 随机换一篇范文
    current_text = random.choice(SAMPLES)
    text_label.config(text=current_text)

    # 启用输入框，清空内容
    input_text.config(state="normal")
    input_text.delete("1.0", tk.END)
    input_text.focus_set()  # 自动聚焦到输入框

    # 启动倒计时
    time_left = 60
    timer_label.config(text=f"⏱️ 剩余时间：{time_left} 秒")
    timer_running = True
    update_timer()

    start_btn.config(state="disabled")


def reset_test():
    """重置测试"""
    global timer_running, time_left
    timer_running = False
    time_left = 60
    timer_label.config(text=f"⏱️ 剩余时间：{time_left} 秒")
    current_text = random.choice(SAMPLES)
    text_label.config(text=current_text)
    input_text.config(state="normal")
    input_text.delete("1.0", tk.END)
    start_btn.config(state="normal")


btn_frame = tk.Frame(root, bg="#f5f5f5")
btn_frame.pack(pady=15)

start_btn = tk.Button(btn_frame, text="▶️ 开始测试", command=start_test,
                      bg="#c8e6c9", font=("微软雅黑", 12), width=12)
start_btn.pack(side=tk.LEFT, padx=5)

tk.Button(btn_frame, text="🔄 重置", command=reset_test,
          bg="#fff9c4", font=("微软雅黑", 12), width=12).pack(side=tk.LEFT, padx=5)

# 操作提示
info_label = tk.Label(root, text="💡 点击「开始测试」启动 60 秒倒计时 / 打对变绿、打错变红",
                      font=("微软雅黑", 9), bg="#f5f5f5", fg="#888")
info_label.pack(pady=(0, 10))

root.mainloop()
