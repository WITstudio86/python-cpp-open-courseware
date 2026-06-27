import tkinter as tk
import random
import json
import os
from datetime import datetime

# ========================================
# 第 46 节：打字速度测试（下）—— 历史记录 + 排行榜 + 难度选择
# ========================================

HISTORY_FILE = "typing_history.json"

# 难度分级范文库
SAMPLES_EASY = [
    "今天天气真好。",
    "我喜欢学 Python。",
    "小明在操场上跑步。",
    "学习让我快乐。",
    "春天花开了。",
]

SAMPLES_MEDIUM = [
    "今天天气真好，阳光洒在操场上，同学们在快乐地跑步。",
    "Python 是一门非常有趣的编程语言，简单又强大。",
    "千里之行，始于足下。学习编程也是一步一步来的。",
    "春天来了，花儿开了，小鸟在枝头唱着欢快的歌。",
]

SAMPLES_HARD = [
    "千里之行，始于足下。学习编程也是一步一步来的，不能着急，要打好基础才能走得更远。",
    "学习编程就像搭积木，一块一块地累积起来，最终搭建出属于自己的程序世界。",
    "书籍是人类进步的阶梯，多读书，读好书，从书中汲取知识和智慧。",
]


def get_sample():
    """根据当前难度返回随机范文"""
    diff = difficulty.get()
    if diff == "easy":
        return random.choice(SAMPLES_EASY)
    elif diff == "hard":
        return random.choice(SAMPLES_HARD)
    else:
        return random.choice(SAMPLES_MEDIUM)


root = tk.Tk()
root.title("打字速度测试 V3.0")
root.geometry("700x580")
root.configure(bg="#f5f5f5")

current_text = get_sample()
time_left = 60
timer_running = False
difficulty = tk.StringVar(value="medium")

# ---------- 顶部信息栏 ----------
info_frame = tk.Frame(root, bg="#f5f5f5")
info_frame.pack(pady=(15, 5), fill=tk.X, padx=30)

title_label = tk.Label(info_frame, text="⌨️ 打字速度测试",
                       font=("微软雅黑", 16, "bold"), bg="#f5f5f5", fg="#333")
title_label.pack(side=tk.LEFT)

timer_label = tk.Label(info_frame, text=f"⏱️ 剩余时间：{time_left} 秒",
                       font=("微软雅黑", 14, "bold"), bg="#f5f5f5", fg="#e65100")
timer_label.pack(side=tk.RIGHT)

# ---------- 难度选择 ----------
diff_frame = tk.Frame(root, bg="#f5f5f5")
diff_frame.pack(pady=5)

tk.Label(diff_frame, text="难度：", bg="#f5f5f5",
         font=("微软雅黑", 11)).pack(side=tk.LEFT)

tk.Radiobutton(diff_frame, text="🌱 短文", variable=difficulty,
               value="easy", bg="#f5f5f5", font=("微软雅黑", 11)).pack(side=tk.LEFT, padx=5)

tk.Radiobutton(diff_frame, text="🌿 中文", variable=difficulty,
               value="medium", bg="#f5f5f5", font=("微软雅黑", 11)).pack(side=tk.LEFT, padx=5)

tk.Radiobutton(diff_frame, text="🌳 长文", variable=difficulty,
               value="hard", bg="#f5f5f5", font=("微软雅黑", 11)).pack(side=tk.LEFT, padx=5)

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
input_text.tag_config("correct", foreground="#2e7d32")
input_text.tag_config("wrong", foreground="#c62828", background="#ffebee")


def check_typing(event=None):
    """实时逐字对比高亮"""
    user_text = input_text.get("1.0", tk.END).rstrip("\n")
    input_text.tag_remove("correct", "1.0", tk.END)
    input_text.tag_remove("wrong", "1.0", tk.END)
    for i, char in enumerate(user_text):
        pos = f"1.{i}"
        if i < len(current_text) and char == current_text[i]:
            input_text.tag_add("correct", pos)
        else:
            input_text.tag_add("wrong", pos)


input_text.bind("<KeyRelease>", check_typing)


# ---------- 倒计时 ----------
def update_timer():
    """每秒更新倒计时"""
    global time_left
    if time_left > 0 and timer_running:
        time_left -= 1
        timer_label.config(text=f"⏱️ 剩余时间：{time_left} 秒")
        root.after(1000, update_timer)
    elif time_left == 0:
        show_result()


# ---------- 统计计算 ----------
def calc_stats():
    """计算并返回 (wpm, accuracy, correct_count)"""
    user_text = input_text.get("1.0", tk.END).rstrip("\n")
    elapsed = 60 - time_left
    if elapsed == 0:
        return 0, 0, 0

    correct_count = sum(
        1 for i, ch in enumerate(user_text)
        if i < len(current_text) and ch == current_text[i]
    )

    wpm = round((correct_count / elapsed) * 60, 1)
    accuracy = round((correct_count / max(len(user_text), 1)) * 100, 1)

    return wpm, accuracy, correct_count


# ---------- 成绩保存到 JSON ----------
def save_score(wpm, accuracy, diff_name):
    """保存成绩到 JSON 历史文件"""
    record = {
        "date": datetime.now().strftime("%Y-%m-%d %H:%M"),
        "wpm": wpm,
        "accuracy": accuracy,
        "difficulty": diff_name
    }

    history = []
    if os.path.exists(HISTORY_FILE):
        with open(HISTORY_FILE, "r", encoding="utf-8") as f:
            history = json.load(f)

    history.append(record)
    # 按 WPM 降序排列
    history.sort(key=lambda x: x["wpm"], reverse=True)
    # 只保留前 20 条
    history = history[:20]

    with open(HISTORY_FILE, "w", encoding="utf-8") as f:
        json.dump(history, f, ensure_ascii=False, indent=2)


# ---------- 显示成绩 ----------
def show_result():
    """时间到，弹出成绩窗口"""
    global timer_running
    timer_running = False
    input_text.config(state="disabled")

    wpm, accuracy, _ = calc_stats()
    diff_name = {"easy": "短文", "medium": "中文", "hard": "长文"}[difficulty.get()]
    save_score(wpm, accuracy, diff_name)

    result_win = tk.Toplevel(root)
    result_win.title("打字成绩")
    result_win.geometry("350x300")
    result_win.configure(bg="#e8f5e9")
    result_win.grab_set()

    tk.Label(result_win, text="🏆 打字成绩", font=("微软雅黑", 18, "bold"),
             bg="#e8f5e9").pack(pady=15)

    tk.Label(result_win, text=f"速度：{wpm} 字/分钟",
             font=("微软雅黑", 16), bg="#e8f5e9", fg="#1565c0").pack(pady=5)

    tk.Label(result_win, text=f"准确率：{accuracy}%",
             font=("微软雅黑", 16), bg="#e8f5e9", fg="#2e7d32").pack(pady=5)

    tk.Label(result_win, text=f"难度：{diff_name}",
             font=("微软雅黑", 12), bg="#e8f5e9", fg="#666").pack(pady=5)

    # 趣味评价
    if wpm >= 60 and accuracy >= 95:
        grade = "🌟 打字高手！"
    elif wpm >= 30 and accuracy >= 80:
        grade = "👍 不错哦，继续加油！"
    else:
        grade = "💪 多多练习，就会越来越快！"

    tk.Label(result_win, text=grade, font=("微软雅黑", 14),
             bg="#e8f5e9", fg="#e65100").pack(pady=10)

    tk.Button(result_win, text="关闭", command=result_win.destroy,
              bg="#c8e6c9", font=("微软雅黑", 11), width=10).pack(pady=10)


# ---------- 排行榜 ----------
def show_leaderboard():
    """显示排行榜窗口"""
    lb_win = tk.Toplevel(root)
    lb_win.title("🏆 排行榜")
    lb_win.geometry("480x420")
    lb_win.configure(bg="#fff8e1")

    tk.Label(lb_win, text="🏆 打字排行榜", font=("微软雅黑", 16, "bold"),
             bg="#fff8e1").pack(pady=10)

    listbox = tk.Listbox(lb_win, font=("微软雅黑", 11), width=55, height=15,
                         bg="white", relief=tk.SUNKEN)
    listbox.pack(pady=10, padx=20)

    if os.path.exists(HISTORY_FILE):
        with open(HISTORY_FILE, "r", encoding="utf-8") as f:
            history = json.load(f)

        for i, record in enumerate(history, 1):
            medal = ["🥇", "🥈", "🥉"][i-1] if i <= 3 else f"  {i}."
            line = f"{medal} {record['wpm']:6.1f} 字/分  |  {record['accuracy']:5.1f}%  |  {record['difficulty']}  |  {record['date']}"
            listbox.insert(tk.END, line)
    else:
        listbox.insert(tk.END, "  还没有成绩记录，快来测试吧！")

    tk.Button(lb_win, text="关闭", command=lb_win.destroy,
              bg="#ffe0b2", font=("微软雅黑", 11), width=10).pack(pady=10)


# ---------- 按钮区域 ----------
btn_frame = tk.Frame(root, bg="#f5f5f5")
btn_frame.pack(pady=15)


def start_test():
    """开始打字测试"""
    global timer_running, time_left, current_text
    current_text = get_sample()
    text_label.config(text=current_text)
    input_text.config(state="normal")
    input_text.delete("1.0", tk.END)
    input_text.focus_set()
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
    current_text = get_sample()
    text_label.config(text=current_text)
    input_text.config(state="normal")
    input_text.delete("1.0", tk.END)
    start_btn.config(state="normal")


start_btn = tk.Button(btn_frame, text="▶️ 开始测试", command=start_test,
                      bg="#c8e6c9", font=("微软雅黑", 12), width=12)
start_btn.pack(side=tk.LEFT, padx=5)

tk.Button(btn_frame, text="🔄 重置", command=reset_test,
          bg="#fff9c4", font=("微软雅黑", 12), width=12).pack(side=tk.LEFT, padx=5)

tk.Button(btn_frame, text="🏆 排行榜", command=show_leaderboard,
          bg="#ffe0b2", font=("微软雅黑", 12), width=12).pack(side=tk.LEFT, padx=5)

# 操作提示
info_label = tk.Label(root, text="💡 选择难度 → 点击开始 → 60秒倒计时 → 查看排行榜",
                      font=("微软雅黑", 9), bg="#f5f5f5", fg="#888")
info_label.pack(pady=(0, 10))

root.mainloop()
