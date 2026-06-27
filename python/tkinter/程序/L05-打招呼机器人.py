import tkinter as tk

# ========================================
# 第 5 节：综合小练 —— 打招呼机器人
# ========================================

root = tk.Tk()
root.title("打招呼机器人 🤖")
root.geometry("500x450")
root.configure(bg="#e0f7fa")

# --- 标题 Label ---
title = tk.Label(
    root,
    text="🤖 打招呼机器人",
    font=("微软雅黑", 22, "bold"),
    fg="#006064",
    bg="#e0f7fa"
)
title.pack(pady=20)

# --- 机器人头像（用大号 emoji Label 代替）---
avatar = tk.Label(
    root,
    text="🤖",
    font=("微软雅黑", 60),
    bg="#e0f7fa"
)
avatar.pack(pady=5)

# --- 提示 ---
prompt = tk.Label(
    root,
    text="机器人：你叫什么名字呀？",
    font=("微软雅黑", 14),
    fg="#00838f",
    bg="#e0f7fa"
)
prompt.pack(pady=10)

# --- 输入框 ---
name_entry = tk.Entry(
    root,
    font=("微软雅黑", 15),
    width=20,
    justify="center",
    bd=2,
    relief="solid"
)
name_entry.pack(pady=5)

# --- 回复显示 Label（动态更新） ---
reply = tk.Label(
    root,
    text="",
    font=("微软雅黑", 16, "bold"),
    fg="#004d40",
    bg="#e0f7fa",
    wraplength=380
)
reply.pack(pady=15)

# --- 打招呼按钮 ---
def say_hello():
    """读取名字，更新回复"""
    name = name_entry.get().strip()
    if name:
        reply.config(text=f"你好，{name}！很高兴认识你！😊\n今天过得怎么样呀～")
    else:
        reply.config(text="你还没告诉我你的名字呢！😅")

hello_btn = tk.Button(
    root,
    text="👋 打招呼！",
    command=say_hello,
    font=("微软雅黑", 14, "bold"),
    bg="#0097a7",
    fg="white",
    activebackground="#00838f",
    padx=25,
    pady=8
)
hello_btn.pack(pady=5)

# --- 换一句按钮 ---
import random
greetings = [
    "嘿，{name}！今天也要加油哦 💪",
    "{name}同学，准备好学编程了吗？🚀",
    "哇，{name}！这名字真好听～",
    "{name}，你今天看起来精神很好！✨"
]

def random_greet():
    """随机选一句问候语"""
    name = name_entry.get().strip()
    if name:
        msg = random.choice(greetings).format(name=name)
        reply.config(text=msg)
    else:
        reply.config(text="先输入名字再点我嘛～")

random_btn = tk.Button(
    root,
    text="🎲 换一句",
    command=random_greet,
    font=("微软雅黑", 12),
    bg="#4dd0e1",
    fg="white",
    padx=15,
    pady=5
)
random_btn.pack(pady=5)

# --- 清空按钮 ---
def clear_all():
    """清空输入框和回复"""
    name_entry.delete(0, tk.END)
    reply.config(text="")

clear_btn = tk.Button(
    root,
    text="🗑️ 清空",
    command=clear_all,
    font=("微软雅黑", 11),
    bg="#b2ebf2",
    fg="#006064",
    padx=12,
    pady=3
)
clear_btn.pack(pady=3)

# --- 底部签名 ---
footer = tk.Label(
    root,
    text="—— 由你亲手打造的第一个互动程序 💻",
    font=("微软雅黑", 10, "italic"),
    fg="#80deea",
    bg="#e0f7fa"
)
footer.pack(side="bottom", pady=10)

root.mainloop()
