# ============================================
# 第 3 课：Entry 输入框和 Listbox 列表
# ============================================

import tkinter as tk

# ==================== 创建窗口 ====================

window = tk.Tk()
window.title("我的备忘录")
window.geometry("400x550")

# ==================== 标题区域 ====================

title_label = tk.Label(
    window,
    text="📝 我的备忘录",
    font=("微软雅黑", 20, "bold"),
    fg="#333333"
)
title_label.pack(pady=15)

subtitle_label = tk.Label(
    window,
    text="输入待办事项，点击添加吧！",
    font=("微软雅黑", 10),
    fg="#888888"
)
subtitle_label.pack(pady=5)

# ==================== 输入区域 ====================

input_frame = tk.Frame(window)
input_frame.pack(pady=15)

entry = tk.Entry(
    input_frame,
    font=("微软雅黑", 13),
    width=25
)
entry.pack(side=tk.LEFT, padx=(0, 5))

add_btn = tk.Button(
    input_frame,
    text="添加 ✅",
    font=("微软雅黑", 12),
    bg="#4CAF50",
    fg="white",
    padx=10,
    pady=5
)
add_btn.pack(side=tk.LEFT)

# ==================== 列表区域 ====================

list_label = tk.Label(
    window,
    text="📋 待办事项",
    font=("微软雅黑", 12, "bold"),
    fg="#555555"
)
list_label.pack(pady=(20, 5))

listbox = tk.Listbox(
    window,
    font=("微软雅黑", 12),
    height=15,
    width=40,
    selectbackground="#C8E6C9",
    selectforeground="#333333"
)
listbox.pack(pady=5)

# ==================== 核心功能 ====================

def add_todo():
    """获取输入框内容，添加到列表中"""
    # 获取并清理文字（去掉首尾空格）
    text = entry.get().strip()

    # 判断是否为空
    if text:
        # 添加到列表框
        listbox.insert(tk.END, text)
        # 清空输入框
        entry.delete(0, tk.END)
        # 控制台确认
        print(f"✅ 添加了：{text}")
    else:
        print("⚠️ 请输入待办事项！")

# 绑定按钮点击
add_btn.config(command=add_todo)

# 绑定回车键
def on_enter_press(event):
    """按回车时也添加"""
    add_todo()

entry.bind("<Return>", on_enter_press)

# ==================== 运行 ====================

# 让光标默认停在输入框里
entry.focus()

window.mainloop()
