import tkinter as tk
import random

# ========================================
# 第 44 节：打字速度测试（上）—— 实时逐字对比
# ========================================

# 范文库
SAMPLES = [
    "今天天气真好，阳光洒在操场上，同学们在快乐地跑步。",
    "Python 是一门非常有趣的编程语言，简单又强大。",
    "千里之行，始于足下。学习编程也是一步一步来的。",
    "春天来了，花儿开了，小鸟在枝头唱着欢快的歌。",
    "努力不一定会成功，但不努力一定不会成功。",
    "书籍是人类进步的阶梯，多读书，读好书。",
]

root = tk.Tk()
root.title("打字速度测试 V1.0")
root.geometry("700x450")
root.configure(bg="#f5f5f5")

# 随机选择一篇范文
current_text = random.choice(SAMPLES)

# ---------- 标题 ----------
title_label = tk.Label(root, text="⌨️ 打字速度测试",
                       font=("微软雅黑", 16, "bold"), bg="#f5f5f5", fg="#333")
title_label.pack(pady=(15, 5))

# ---------- 范文显示区域 ----------
sample_frame = tk.Frame(root, bg="white", relief=tk.RIDGE, bd=2)
sample_frame.pack(pady=10, padx=30, fill=tk.X)

tk.Label(sample_frame, text="📝 请打以下文字：", font=("微软雅黑", 11),
         bg="white", fg="#888", anchor="w").pack(anchor="w", padx=15, pady=(10, 0))

text_label = tk.Label(sample_frame, text=current_text,
                       font=("微软雅黑", 16), bg="white", fg="#333",
                       wraplength=620, justify="left", padx=15, pady=10)
text_label.pack()

# ---------- 打字输入区域 ----------
tk.Label(root, text="👇 在下面输入：", font=("微软雅黑", 11),
         bg="#f5f5f5", fg="#888").pack(anchor="w", padx=33, pady=(15, 5))

input_text = tk.Text(root, font=("微软雅黑", 16), height=4, width=52,
                     wrap="word", bg="white", relief=tk.SUNKEN, bd=1)
input_text.pack(pady=0, padx=30)

# 配置高亮 tag：正确 = 绿色，错误 = 红色 + 浅红背景
input_text.tag_config("correct", foreground="#2e7d32")
input_text.tag_config("wrong", foreground="#c62828", background="#ffebee")


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


# 绑定按键事件：每打一个字就触发对比
input_text.bind("<KeyRelease>", check_typing)


# ---------- 换一篇按钮 ----------
def change_sample():
    """随机换一篇范文"""
    global current_text
    current_text = random.choice(SAMPLES)
    text_label.config(text=current_text)
    input_text.delete("1.0", tk.END)


tk.Button(root, text="🔄 换一篇", command=change_sample,
          bg="#e3f2fd", font=("微软雅黑", 11), width=12).pack(pady=15)

# 统计提示
info_label = tk.Label(root, text="💡 打对的字会变绿色，打错的字会变红色哦~",
                      font=("微软雅黑", 9), bg="#f5f5f5", fg="#888")
info_label.pack(pady=(0, 10))

root.mainloop()
