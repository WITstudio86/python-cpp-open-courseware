import tkinter as tk
import random

# ========================================
# 第 24 节：项目3 —— 猜数字游戏（下）
# 知识点：全局变量 · 计数器 · 排行榜 · reset 按钮
# ========================================

# 1. 创建主窗口
root = tk.Tk()
root.title("猜数字游戏 2.0")                # 设置窗口标题
root.geometry("450x400")                    # 设置窗口大小：宽450，高400
root.configure(bg="#f0f7ff")                # 设置背景色：浅蓝

# 2. 全局变量
#    secret：电脑想的随机数（1~100）
#    count：当前这一局已经猜了多少次
#    best_score：历史最低步数（最佳纪录），初始设 999 保证第一次就能破纪录
secret = random.randint(1, 100)
count = 0
best_score = 999

# 3. 标题标签
title_label = tk.Label(
    root,
    text="🎯 猜数字游戏",
    font=("Microsoft YaHei", 22, "bold"),
    bg="#f0f7ff",
    fg="#1a237e"                            # 深蓝色文字
)
title_label.pack(pady=15)

# 4. 结果反馈标签
#    用来提示用户"太大了"、"太小了"或"恭喜猜对"
result_label = tk.Label(
    root,
    text="我想了一个 1~100 之间的数字，猜猜看！",
    font=("Microsoft YaHei", 13),
    bg="#f0f7ff",
    fg="#333333",
    wraplength=380                          # 文字自动换行的宽度
)
result_label.pack(pady=5)

# 5. 猜测次数显示标签
count_label = tk.Label(
    root,
    text="已猜次数: 0",
    font=("Microsoft YaHei", 13),
    bg="#f0f7ff",
    fg="#555555"                            # 灰色文字
)
count_label.pack(pady=5)

# 6. 最佳纪录显示标签
best_label = tk.Label(
    root,
    text="🏆 最佳纪录: ---",
    font=("Microsoft YaHei", 13, "bold"),
    bg="#f0f7ff",
    fg="#e65100"                            # 橙色文字，醒目
)
best_label.pack(pady=5)

# 7. 输入框
#    用户在这里输入自己猜的数字
entry = tk.Entry(
    root,
    font=("Microsoft YaHei", 16),
    justify="center",                       # 文字居中显示
    width=10,
    relief="solid",                         # 实线边框
    bd=1                                    # 边框宽度 1 像素
)
entry.pack(pady=10)

# 8. 猜测按钮的回调函数 —— 核心逻辑！
def guess():
    """
    用户点击"猜！"按钮时执行：
    ① 读取输入框的文字，转成整数
    ② 计数器 +1，更新显示
    ③ 和 secret 比较，给出"大了/小了/猜对"的提示
    ④ 如果猜对了，检查是否打破最佳纪录
    """
    # ★ 重要：告诉 Python 我们要修改外面的全局变量
    global count, best_score

    # 8a. 获取用户输入
    user_input = entry.get()
    if user_input == "":
        result_label.config(text="请输入一个数字！")
        return

    # 8b. 尝试将输入转成整数（用户可能输入了字母）
    try:
        guess_num = int(user_input)
    except ValueError:
        result_label.config(text="请输入有效的整数！比如 50")
        return

    # 8c. 计数器 +1，更新显示
    count += 1
    count_label.config(text=f"已猜次数: {count}")

    # 8d. 比较猜测值和答案
    if guess_num < secret:
        # 猜小了 —— 给提示
        result_label.config(text=f"{guess_num} 太小了，再大一点！")
    elif guess_num > secret:
        # 猜大了 —— 给提示
        result_label.config(text=f"{guess_num} 太大了，再小一点！")
    else:
        # 猜对了！🎉
        result_label.config(text=f"🎉 恭喜！{secret} 就是正确答案！用了 {count} 次")

        # 检查是否打破最佳纪录
        if count < best_score:
            best_score = count
            best_label.config(text=f"🏆 最佳纪录: {best_score} 步（新纪录！）")
        else:
            best_label.config(text=f"🏆 最佳纪录: {best_score} 步（本次用了 {count} 步，未破纪录）")

# 9. 重新开始按钮的回调函数
def reset():
    """
    重置游戏到初始状态：
    ① 生成新的随机数
    ② 计数器归零，更新显示
    ③ 清空输入框和结果提示
    ④ 注意：best_score 不重置，保留最佳纪录
    """
    global secret, count                     # ★ 修改全局变量必须写 global

    # 9a. 生成新的随机数（1~100）
    secret = random.randint(1, 100)

    # 9b. 计数器归零
    count = 0
    count_label.config(text="已猜次数: 0")

    # 9c. 恢复提示文字
    result_label.config(text="新游戏开始！请输入你的猜测")

    # 9d. 清空输入框
    entry.delete(0, tk.END)

    # 9e. best_score 不重置 —— 让最佳纪录一直保留！

# 10. 创建按钮区域的容器（Frame）
btn_frame = tk.Frame(root, bg="#f0f7ff")
btn_frame.pack(pady=15)

# 11. "猜！" 按钮
guess_btn = tk.Button(
    btn_frame,
    text="🔍 猜！",
    command=guess,
    font=("Microsoft YaHei", 14, "bold"),
    bg="#283593",                            # 深蓝色背景
    fg="white",                              # 白色文字
    activebackground="#1a237e",              # 按下时的颜色（更深）
    activeforeground="white",
    relief="flat",                           # 扁平样式
    padx=20,
    pady=6,
    cursor="hand2"                           # 鼠标悬停时显示手指
)
guess_btn.pack(side="left", padx=10)

# 12. "重新开始" 按钮
reset_btn = tk.Button(
    btn_frame,
    text="🔄 重新开始",
    command=reset,
    font=("Microsoft YaHei", 14, "bold"),
    bg="#e65100",                            # 橙色背景，和猜按钮区分
    fg="white",
    activebackground="#bf360c",              # 按下时的颜色（深橙）
    activeforeground="white",
    relief="flat",
    padx=20,
    pady=6,
    cursor="hand2"
)
reset_btn.pack(side="left", padx=10)

# 13. 绑定回车键
#     在输入框里按回车键，效果等同于点击"猜！"按钮
root.bind("<Return>", lambda event: guess())

# 14. 启动主循环（必须放在代码最后！）
root.mainloop()
