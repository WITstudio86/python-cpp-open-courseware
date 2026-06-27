import tkinter as tk
import random

# ========================================
# 第 23 节：项目3 —— 猜数字游戏（上）
# 知识点：
#   1. random.randint() 生成随机数
#   2. Entry 输入框获取用户输入
#   3. int() 把字符串转成整数
#   4. if-elif-else 判断大小关系
#   5. Label.config(text=...) 动态更新反馈文字
#   6. try-except 防止用户输入非数字导致崩溃
# ========================================

# ---------- 游戏初始化：生成秘密数字 ----------
# random.randint(1, 100) 会在 1~100 之间随机挑一个整数
# 包含 1 和 100！所以可能出现 1，也可能出现 100
secret = random.randint(1, 100)

# （调试时可以取消下面这行的注释，看看随机数是多少）
# print(f"调试：秘密数字是 {secret}")

# ---------- 创建主窗口 ----------
root = tk.Tk()
root.title("猜数字游戏")                      # 窗口标题栏文字
root.geometry("450x350")                      # 宽 450，高 350 像素
root.configure(bg="#f5f0e8")                  # 米白色背景，温暖舒适

# ---------- 标题标签 ----------
# 放在窗口最上方，告诉玩家这是什么游戏
title_label = tk.Label(
    root,
    text="🔢 猜数字游戏",                     # 标题文字
    font=("微软雅黑", 22, "bold"),            # 大号加粗字体
    bg="#f5f0e8",                             # 背景色和窗口一致
    fg="#5a3e2b"                              # 深棕色文字
)
title_label.pack(pady=20)                     # 上下各留 20 像素的间距

# ---------- 规则说明标签 ----------
# 告诉玩家游戏规则：数字范围是 1~100
hint_label = tk.Label(
    root,
    text="我心里想了一个 1~100 的数字，你猜猜看？",
    font=("微软雅黑", 13),                    # 中等字体
    bg="#f5f0e8",
    fg="#666666"                              # 灰色文字，比标题低调
)
hint_label.pack(pady=(0, 15))                  # 上方无间距，下方留 15 像素

# ---------- 玩家输入框 ----------
# Entry 控件让玩家输入猜测的数字
entry = tk.Entry(
    root,
    font=("微软雅黑", 18),                    # 输入框字体大一点，看得清楚
    width=8,                                   # 宽度为 8 个字符
    justify="center"                           # 输入的文字居中显示
)
entry.pack(pady=5)
entry.focus()                                  # 让输入框自动获得焦点
# 这样程序一启动，光标就在输入框里，不用鼠标点就能直接输入

# ---------- 结果反馈标签 ----------
# 这个 Label 会随着玩家的猜测动态变化：
#   - 开始："👆 在上面输入数字，点按钮开始！"
#   - 猜大："📉 太大了！再猜小一点"
#   - 猜小："📈 太小了！再猜大一点"
#   - 猜对："🎉 恭喜你猜对了！"
result_label = tk.Label(
    root,
    text="👆 在上面输入数字，点按钮开始！",    # 初始提示文字
    font=("微软雅黑", 14),
    bg="#f5f0e8",
    fg="#2d7d6e"                               # 深绿色文字
)
result_label.pack(pady=15)

# ====================================================
# 核心函数：猜数字逻辑
# ====================================================
def guess():
    """
    获取玩家在输入框里输入的数字，
    和秘密数字 secret 比较，
    然后把比较结果显示在 result_label 上。
    """
    # ----- 第 1 步：获取用户输入并转为整数 -----
    # entry.get() 返回的是字符串（比如 "50"）
    # 必须用 int() 转成整数才能和 secret 比较
    # 如果用户输入了非数字（比如 "abc"），int() 会报错
    # 所以用 try-except 来保护程序，不让它崩溃
    try:
        user_num = int(entry.get())
    except ValueError:
        # 用户输入了不是数字的东西，给出提示
        result_label.config(
            text="⚠️ 请输入一个有效的数字！",
            fg="#c4593f"                       # 红色提示
        )
        entry.delete(0, "end")                 # 清空输入框
        entry.focus()                          # 光标回到输入框
        return                                 # 提前结束，不再往下执行

    # ----- 第 2 步：检查数字是否在范围内 -----
    # 秘密数字是 1~100，超出范围的输入也提示一下
    if user_num < 1 or user_num > 100:
        result_label.config(
            text="⚠️ 请输入 1~100 之间的数字！",
            fg="#c4593f"
        )
        entry.delete(0, "end")
        entry.focus()
        return

    # ----- 第 3 步：比较大小，给出反馈 -----
    # 三种情况：user_num > secret（太大）
    #          user_num < secret（太小）
    #          user_num == secret（猜对！）
    if user_num > secret:
        # 猜大了 → 告诉玩家往小了猜
        result_label.config(
            text=f"📉 {user_num} 太大了！再猜小一点",
            fg="#d88a3a"                       # 橙色
        )
    elif user_num < secret:
        # 猜小了 → 告诉玩家往大了猜
        result_label.config(
            text=f"📈 {user_num} 太小了！再猜大一点",
            fg="#2d7d6e"                       # 绿色
        )
    else:
        # 猜对了！显示庆祝信息
        result_label.config(
            text=f"🎉 恭喜你猜对了！答案就是 {secret}！",
            fg="#2d7d6e"
        )

    # ----- 第 4 步：清空输入框，准备下一次猜测 -----
    # delete(0, "end") 表示删除从第 0 个字符到末尾的全部内容
    entry.delete(0, "end")
    entry.focus()                                # 光标回到输入框
    # 这样玩家猜了一次之后，不用手动删掉旧数字就能直接输入下一次

# ---------- 猜测按钮 ----------
# 点击按钮触发 guess() 函数
guess_btn = tk.Button(
    root,
    text="🎯 猜！",                              # 按钮上的文字
    command=guess,                               # 点击后执行的函数
    font=("微软雅黑", 14, "bold"),              # 按钮字体
    bg="#2d7d6e",                                # 深绿色背景
    fg="#ffffff",                                # 白色文字
    width=10,                                    # 按钮宽度
    cursor="hand2"                               # 鼠标悬停时变成小手形状
)
guess_btn.pack(pady=10)

# ---------- 绑定回车键 ----------
# 除了点按钮，按键盘上的回车键也能触发 guess() 函数
# lambda event: guess() → 因为 bind 会传入一个 event 参数，
# 但 guess() 不需要这个参数，所以用 lambda 把它"吃掉"
root.bind("<Return>", lambda event: guess())

# ---------- 启动窗口主循环 ----------
# mainloop() 让窗口一直显示，监听用户的操作（点击、输入、按键等）
# 没有它，窗口会一闪而过就消失了！
# 必须放在整个程序的最后一行！
root.mainloop()
