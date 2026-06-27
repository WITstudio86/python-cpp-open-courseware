"""
第 18 节 · 阶段综合 —— 个人信息小管家 📋
============================================
阶段一收官之作，综合运用以下控件：
  - Label（标签）：显示文字
  - Entry（输入框）：输入姓名
  - Radiobutton（单选按钮）：选择性别
  - Checkbutton（多选按钮）：选择爱好
  - Combobox（下拉框）：选择年级
  - Button（按钮）：提交 / 清空

用到的变量类型：
  - StringVar：姓名、年级（存文字）
  - IntVar：性别（存 1 或 0）
  - BooleanVar：每个爱好一个（存 True / False）

核心理念：「输入 → 处理 → 输出」
  1. 用户通过控件输入信息
  2. 点击按钮触发 submit_info() 读取所有变量
  3. 拼成汇总文字，更新到结果 Label 显示
"""

import tkinter as tk
from tkinter import ttk  # Combobox 在 ttk 模块里，记得导入！


# ==================== 核心函数 ====================

def submit_info():
    """
    提交信息函数 —— 本课的核心！
    1. 用 .get() 方法从每个变量中读取用户填写的内容
    2. 把读到的内容拼成一段漂亮的汇总文字
    3. 用 .config(text=...) 更新结果标签显示
    """
    # --- 1. 读取姓名 ---
    # name_var 是 StringVar，.get() 返回用户输入的文字
    name = name_var.get().strip()
    if not name:  # 如果用户忘记填姓名，提醒一下
        result_label.config(text="⚠️ 请先输入姓名再提交哦～")
        return

    # --- 2. 读取性别 ---
    # gender_var 是 IntVar，1 代表"男"，0 代表"女"
    if gender_var.get() == 1:
        gender = "男 👦"
    else:
        gender = "女 👧"

    # --- 3. 读取爱好 ---
    # 每个爱好对应一个 BooleanVar，选中的为 True，没选的为 False
    hobbies = []
    if hobby_code_var.get():    # 如果勾选了"编程"
        hobbies.append("编程 💻")
    if hobby_draw_var.get():    # 如果勾选了"画画"
        hobbies.append("画画 🎨")
    if hobby_sport_var.get():   # 如果勾选了"运动"
        hobbies.append("运动 ⚽")
    if hobby_music_var.get():   # 如果勾选了"音乐"
        hobbies.append("音乐 🎵")

    # join() 把列表里的爱好用"、"连起来
    if hobbies:
        hobby_text = "、".join(hobbies)
    else:
        hobby_text = "暂无爱好"

    # --- 4. 读取年级 ---
    # grade_var 是 StringVar，绑定了 Combobox
    grade = grade_var.get()
    if not grade:
        grade = "未选择"

    # --- 5. 拼成美观的汇总信息 ---
    # 用 f-string 把读取到的所有信息拼成一段文字
    summary = f"""📋━━━ 个人信息汇总 ━━━📋

👤 姓名：{name}
🚻 性别：{gender}
🎯 爱好：{hobby_text}
📚 年级：{grade}

━━━━━━━━━━━━━━━━━━━━━━"""

    # --- 6. 更新结果标签 ---
    # 用 .config(text=...) 改变 Label 显示的内容
    result_label.config(text=summary)


def clear_form():
    """
    清空表单函数 —— 把一切恢复到初始状态
    每个变量都用 .set() 设置为默认值
    """
    name_var.set("")                    # 清空姓名
    gender_var.set(1)                   # 性别恢复为"男"
    hobby_code_var.set(False)           # 取消"编程"
    hobby_draw_var.set(False)           # 取消"画画"
    hobby_sport_var.set(False)          # 取消"运动"
    hobby_music_var.set(False)          # 取消"音乐"
    grade_var.set("")                   # 清空年级
    # 恢复提示文字
    result_label.config(text="📝 请填写上方信息，然后点击「提交」按钮～")


# ==================== 创建主窗口 ====================
root = tk.Tk()
root.title("个人信息小管家 📋")          # 窗口标题
root.geometry("550x580")                # 窗口大小：宽度 550，高度 580
root.resizable(False, False)            # 禁止拉伸窗口（保持布局整齐）

# ==================== 定义变量（控件和代码之间的桥梁） ====================
name_var = tk.StringVar()           # 姓名：StringVar 存文字
gender_var = tk.IntVar(value=1)     # 性别：IntVar 存整数，默认值 1 = 男
hobby_code_var = tk.BooleanVar()    # 爱好-编程：BooleanVar 存 True/False
hobby_draw_var = tk.BooleanVar()    # 爱好-画画
hobby_sport_var = tk.BooleanVar()   # 爱好-运动
hobby_music_var = tk.BooleanVar()   # 爱好-音乐
grade_var = tk.StringVar()          # 年级：StringVar 存文字

# ==================== 顶部标题区域 ====================
title_label = tk.Label(
    root,
    text="📋 个人信息小管家",
    font=("Microsoft YaHei", 20, "bold"),
    fg="#4A90D9"                     # 蓝色标题
)
title_label.pack(pady=15)            # pack 布局，上下各留 15px 间距

subtitle_label = tk.Label(
    root,
    text="阶段一收官之作 · 控件全家福实战 🎉",
    font=("Microsoft YaHei", 11),
    fg="#888888"                     # 灰色副标题
)
subtitle_label.pack(pady=(0, 15))    # 上方 0，下方 15px

# ==================== 表单区域（用 LabelFrame 包裹，美观分组） ====================
form_frame = tk.LabelFrame(
    root,
    text=" 📝 请填写你的信息 ",
    font=("Microsoft YaHei", 12, "bold"),
    fg="#333333",
    padx=15,                          # 内部水平边距
    pady=10                           # 内部垂直边距
)
form_frame.pack(padx=30, pady=5, fill="x")

# --- 第 0 行：姓名 ---
tk.Label(form_frame, text="👤 姓名：", font=("Microsoft YaHei", 11)).grid(
    row=0, column=0, sticky="w", pady=8, padx=(0, 10))
entry_name = tk.Entry(
    form_frame,
    textvariable=name_var,            # 绑定 StringVar
    font=("Microsoft YaHei", 11),
    width=20
)
entry_name.grid(row=0, column=1, sticky="w", pady=8)

# --- 第 1 行：性别（Radiobutton 单选） ---
tk.Label(form_frame, text="🚻 性别：", font=("Microsoft YaHei", 11)).grid(
    row=1, column=0, sticky="w", pady=8, padx=(0, 10))

# 用一个 Frame 把两个 Radiobutton 包在一起，方便横向排列
gender_frame = tk.Frame(form_frame)
gender_frame.grid(row=1, column=1, sticky="w", pady=8)

# 两个 Radiobutton 共享同一个 gender_var，确保只能选一个
tk.Radiobutton(
    gender_frame,
    text="男 👦",
    variable=gender_var,              # 绑定 IntVar
    value=1,                          # 选中时 gender_var 的值 = 1
    font=("Microsoft YaHei", 11)
).pack(side="left", padx=(0, 20))

tk.Radiobutton(
    gender_frame,
    text="女 👧",
    variable=gender_var,              # 同一个变量！
    value=0,                          # 选中时 gender_var 的值 = 0
    font=("Microsoft YaHei", 11)
).pack(side="left")

# --- 第 2 行：爱好（Checkbutton 多选） ---
tk.Label(form_frame, text="🎯 爱好：", font=("Microsoft YaHei", 11)).grid(
    row=2, column=0, sticky="w", pady=8, padx=(0, 10))

# 用一个 Frame 把 4 个 Checkbutton 用 grid 排列成 2x2
hobby_frame = tk.Frame(form_frame)
hobby_frame.grid(row=2, column=1, sticky="w", pady=8)

# 每个 Checkbutton 绑定独立的 BooleanVar，互不影响
tk.Checkbutton(
    hobby_frame, text="编程 💻",
    variable=hobby_code_var,          # 绑定 BooleanVar
    font=("Microsoft YaHei", 10)
).grid(row=0, column=0, sticky="w", padx=(0, 15))

tk.Checkbutton(
    hobby_frame, text="画画 🎨",
    variable=hobby_draw_var,
    font=("Microsoft YaHei", 10)
).grid(row=0, column=1, sticky="w", padx=(0, 15))

tk.Checkbutton(
    hobby_frame, text="运动 ⚽",
    variable=hobby_sport_var,
    font=("Microsoft YaHei", 10)
).grid(row=1, column=0, sticky="w", padx=(0, 15))

tk.Checkbutton(
    hobby_frame, text="音乐 🎵",
    variable=hobby_music_var,
    font=("Microsoft YaHei", 10)
).grid(row=1, column=1, sticky="w", padx=(0, 15))

# --- 第 3 行：年级（Combobox 下拉框） ---
tk.Label(form_frame, text="📚 年级：", font=("Microsoft YaHei", 11)).grid(
    row=3, column=0, sticky="w", pady=8, padx=(0, 10))

# Combobox 来自 ttk 模块，不是 tk 哦！
grade_combo = ttk.Combobox(
    form_frame,
    textvariable=grade_var,           # 绑定 StringVar
    font=("Microsoft YaHei", 11),
    values=["三年级 📗", "四年级 📘", "五年级 📙", "六年级 📕"],
    state="readonly",                 # 只读模式：只能选，不能乱打
    width=18
)
grade_combo.grid(row=3, column=1, sticky="w", pady=8)

# ==================== 按钮区域 ====================
button_frame = tk.Frame(root)
button_frame.pack(pady=15)

# 提交按钮 —— 点击时调用 submit_info() 函数
submit_btn = tk.Button(
    button_frame,
    text="✅ 提交信息",
    command=submit_info,              # 绑定函数（不要加括号！）
    font=("Microsoft YaHei", 12, "bold"),
    bg="#4A90D9",                     # 蓝色背景
    fg="white",                       # 白色文字
    activebackground="#357ABD",       # 按下时的深蓝背景
    activeforeground="white",
    width=12,
    height=1,
    cursor="hand2"                    # 鼠标悬停时变成小手
)
submit_btn.pack(side="left", padx=10)

# 清空按钮 —— 点击时调用 clear_form() 函数
clear_btn = tk.Button(
    button_frame,
    text="🔄 清空重填",
    command=clear_form,               # 绑定清空函数
    font=("Microsoft YaHei", 12, "bold"),
    bg="#E8E8E8",                     # 浅灰背景
    fg="#333333",
    activebackground="#D0D0D0",
    width=12,
    height=1,
    cursor="hand2"
)
clear_btn.pack(side="left", padx=10)

# ==================== 结果展示区域 ====================
result_frame = tk.LabelFrame(
    root,
    text=" 📊 信息汇总 ",
    font=("Microsoft YaHei", 12, "bold"),
    fg="#333333",
    padx=15,
    pady=10
)
# fill="both", expand=True 让结果区域随窗口扩展
result_frame.pack(padx=30, pady=5, fill="both", expand=True)

# 结果标签 —— 显示汇总信息的地方
result_label = tk.Label(
    result_frame,
    text="📝 请填写上方信息，然后点击「提交」按钮～",
    font=("Microsoft YaHei", 12),
    fg="#555555",
    justify="left",                   # 文字左对齐
    anchor="w"                        # Label 内容靠左
)
result_label.pack(anchor="w", expand=True)

# ==================== 底部信息栏 ====================
footer_label = tk.Label(
    root,
    text="🎓 阶段一 · 完美收官！ 下一站：阶段二 · 电子时钟项目 ⏰",
    font=("Microsoft YaHei", 10),
    fg="#AAAAAA"
)
footer_label.pack(pady=(5, 10))

# ==================== 启动主循环 ====================
# 这一行必须放在最后！它让窗口一直显示，等待用户操作
root.mainloop()
