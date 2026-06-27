import tkinter as tk
from tkinter import ttk

# ========================================
# 第 12 节：个性名片生成器
# 知识点：ttk.Combobox 下拉选择框、<<ComboboxSelected>> 事件绑定
# ========================================

# 1. 创建主窗口
root = tk.Tk()
root.title("个性名片生成器")
root.geometry("450x450")
root.configure(bg="#f5f0e8")  # 米白色背景，像纸张

# ---------- 标题 ----------
title_label = tk.Label(root, text="🎨 个性名片生成器",
                       font=("微软雅黑", 20, "bold"),
                       bg="#f5f0e8", fg="#5a3e2b")
title_label.pack(pady=15)

# ---------- 选择区域 ----------
# 名字选择：Combobox 下拉框让用户选择名字
tk.Label(root, text="📛 选择名字：", font=("微软雅黑", 13),
         bg="#f5f0e8", fg="#5a3e2b").pack(pady=(10, 0))
name_combo = ttk.Combobox(root,
                          values=["小明", "小红", "小刚", "小丽", "小华"],
                          state="readonly",  # 只能选，不能输入
                          font=("微软雅黑", 12), width=15)
name_combo.current(0)  # 默认选中第 0 项（小明）
name_combo.pack(pady=5)

# 年龄选择：下拉框选择年龄段
tk.Label(root, text="🎂 选择年龄：", font=("微软雅黑", 13),
         bg="#f5f0e8", fg="#5a3e2b").pack(pady=(10, 0))
age_combo = ttk.Combobox(root,
                         values=["8岁", "9岁", "10岁", "11岁", "12岁", "13岁"],
                         state="readonly",
                         font=("微软雅黑", 12), width=15)
age_combo.current(2)  # 默认选中 "10岁"
age_combo.pack(pady=5)

# 爱好选择：下拉框选择爱好（带 emoji 更有趣）
tk.Label(root, text="⚽ 选择爱好：", font=("微软雅黑", 13),
         bg="#f5f0e8", fg="#5a3e2b").pack(pady=(10, 0))
hobby_combo = ttk.Combobox(root,
                           values=["编程 💻", "画画 🎨", "足球 ⚽",
                                   "阅读 📚", "弹琴 🎹", "跳舞 💃"],
                           state="readonly",
                           font=("微软雅黑", 12), width=15)
hobby_combo.current(0)  # 默认选中第一个
hobby_combo.pack(pady=5)


# ---------- 更新名片预览的函数 ----------
def update_card(event=None):
    """
    当下拉框选择改变时，自动更新名片预览。
    event=None 让这个函数既可以被 bind 调用，也可以被 button command 调用。
    """
    name = name_combo.get()      # 获取当前选中的名字
    age = age_combo.get()        # 获取当前选中的年龄
    hobby = hobby_combo.get()    # 获取当前选中的爱好
    # 更新预览标签的文字
    card_display.config(text=f"姓名：{name}\n年龄：{age}\n爱好：{hobby}")


# ---------- 生成名片的函数 ----------
def generate_card():
    """点击"生成名片"按钮时调用，生成带边框的名片效果"""
    name = name_combo.get()
    age = age_combo.get()
    hobby = hobby_combo.get()
    # 用字符画的方式生成一张"卡片"
    card_display.config(
        text=f"┌──────────────────┐\n"
             f"│   🌟 我的名片 🌟   │\n"
             f"│                  │\n"
             f"│  姓名：{name}    │\n"
             f"│  年龄：{age}      │\n"
             f"│  爱好：{hobby}    │\n"
             f"│                  │\n"
             f"└──────────────────┘"
    )


# 绑定事件：当下拉框选项改变时，自动调用 update_card 更新预览
name_combo.bind("<<ComboboxSelected>>", update_card)
age_combo.bind("<<ComboboxSelected>>", update_card)
hobby_combo.bind("<<ComboboxSelected>>", update_card)

# ---------- 名片预览区域 ----------
# 用一个 Label 作为"名片纸"，显示预览信息
card_display = tk.Label(root,
                        text="请选择信息后点击「生成名片」",
                        font=("微软雅黑", 13),
                        bg="#fff8e7",      # 米黄色卡片纸
                        fg="#5a3e2b",      # 深棕色文字
                        width=30, height=8,
                        relief="ridge", bd=2,  # 凸起边框效果
                        justify="left", anchor="nw")
card_display.pack(pady=15)

# ---------- 生成按钮 ----------
btn = tk.Button(root, text="🎫 生成名片",
                font=("微软雅黑", 14, "bold"),
                bg="#5a3e2b", fg="white",
                padx=20, pady=6,
                cursor="hand2",           # 鼠标悬停时变成手指
                command=generate_card)    # 点击时调用 generate_card
btn.pack(pady=10)

# 2. 启动主循环 —— 让窗口一直显示
root.mainloop()
