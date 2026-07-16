# ============================================
# 第 1 课：你好，Python！— 第一个 GUI 窗口 + Label 标签
# ============================================

# --- 第一部分：print() 和变量 ---

# 让电脑说话
print("你好，Python！")
print("今天开始学编程！")

# 变量练习
my_name = "小明"
my_age = 12
my_hobby = "编程"

print("我叫" + my_name)
print("我今年" + str(my_age) + "岁")
print("我的爱好是" + my_hobby)

# --- 第二部分：创建第一个 GUI 窗口 ---

# 导入 tkinter 库（Python 自带的图形界面工具）
import tkinter as tk

# 创建主窗口（就像买了一个空画框）
window = tk.Tk()

# 设置窗口标题（给画框贴个标签）
window.title("我的备忘录")

# 设置窗口大小（宽x高，单位是像素）
window.geometry("400x500")

# --- 第三部分：添加 Label 标签 ---

# 添加一个欢迎标签
hello_label = tk.Label(
    window,
    text="欢迎来到我的备忘录！",
    font=("微软雅黑", 14),
    fg="#333333"
)
hello_label.pack(pady=20)

# 让窗口一直显示（事件循环，必须放最后）
window.mainloop()
