import tkinter as tk

# ========================================
# 第 4 节：Entry 输入框 —— 名字生成器
# ========================================

root = tk.Tk()
root.title("名字生成器")
root.geometry("500x450")
root.configure(bg="#f3e5f5")

# --- 标题 ---
title = tk.Label(
    root,
    text="✨ 名字生成器",
    font=("微软雅黑", 22, "bold"),
    fg="#6a1b9a",
    bg="#f3e5f5"
)
title.pack(pady=20)

# --- 提示文字 ---
prompt = tk.Label(
    root,
    text="请输入你的名字：",
    font=("微软雅黑", 14),
    fg="#7b1fa2",
    bg="#f3e5f5"
)
prompt.pack(pady=5)

# --- 输入框 ---
name_entry = tk.Entry(
    root,
    font=("微软雅黑", 16),
    width=20,
    bd=2,
    relief="solid",
    justify="center"
)
name_entry.pack(pady=10)
# 默认显示提示文字
name_entry.insert(0, "在这里输入你的名字")

# --- 结果展示 Label ---
result = tk.Label(
    root,
    text="",
    font=("微软雅黑", 18, "bold"),
    fg="#4a148c",
    bg="#f3e5f5"
)
result.pack(pady=15)

# --- 生成按钮 ---
def generate():
    """读取输入框内容，生成个性化问候"""
    name = name_entry.get()  # ← get() 读取输入框内容
    if name and name != "在这里输入你的名字":
        result.config(text=f"你好，{name}！🎉\n欢迎来到编程世界！")
    else:
        result.config(text="⚠️ 请先输入你的名字哦～")

gen_btn = tk.Button(
    root,
    text="🎯 生成我的专属称呼",
    command=generate,
    font=("微软雅黑", 14),
    bg="#9c27b0",
    fg="white",
    padx=25,
    pady=8
)
gen_btn.pack(pady=8)

# --- 清空按钮 ---
def clear():
    """清空输入框"""
    name_entry.delete(0, tk.END)  # ← 从第0个字符删到末尾

clear_btn = tk.Button(
    root,
    text="🗑️ 清空",
    command=clear,
    font=("微软雅黑", 12),
    bg="#ce93d8",
    fg="white",
    padx=15,
    pady=5
)
clear_btn.pack(pady=5)

# --- 蜜码输入演示区 ---
pwd_label = tk.Label(
    root,
    text="----- 蜜码模式演示 -----",
    font=("微软雅黑", 10),
    fg="#ab47bc",
    bg="#f3e5f5"
)
pwd_label.pack(pady=(25, 5))

pwd_entry = tk.Entry(
    root,
    font=("微软雅黑", 14),
    width=20,
    show="●",  # ← show 参数：输入时显示 ● 而不是真实字符
    justify="center"
)
pwd_entry.pack(pady=5)
pwd_entry.insert(0, "试试输入蜜码")

root.mainloop()
