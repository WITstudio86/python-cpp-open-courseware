import tkinter as tk
from tkinter import ttk, messagebox, filedialog
import random
import json
import os
from datetime import datetime

# ========================================
# 第 48 节：自由创作 · 作品模板骨架
# ========================================
# 这是一个空白窗口模板，帮同学们快速开始自己的创作。
# 注释中列出了所有可用的控件和常用操作，根据需要选用即可。

root = tk.Tk()
root.title("我的作品")  # ← 改成你的作品名
root.geometry("600x500")
root.configure(bg="#f5f5f5")

# ============================================================
# 你的代码从这里开始 ↓↓↓
# ============================================================

# ---------- 可用的基础控件 ----------

# 标签（显示文字）
# tk.Label(root, text="你好，世界！", font=("微软雅黑", 16),
#          bg="#f5f5f5", fg="#333").pack(pady=10)

# 按钮（点击触发动作）
# tk.Button(root, text="点击我", command=lambda: print("按钮被点击了！"),
#           bg="#c8e6c9", font=("微软雅黑", 12), width=15).pack(pady=10)

# 单行输入框
# entry = tk.Entry(root, font=("微软雅黑", 12), width=25)
# entry.pack(pady=10)
# 获取内容：entry.get()
# 设置内容：entry.insert(0, "默认文字")
# 清空：entry.delete(0, tk.END)

# 多行文本框
# text = tk.Text(root, font=("微软雅黑", 12), height=5, width=40)
# text.pack(pady=10)
# 获取内容：text.get("1.0", tk.END)
# 插入内容：text.insert(tk.END, "新内容\n")
# 清空：text.delete("1.0", tk.END)

# 列表框
# listbox = tk.Listbox(root, font=("微软雅黑", 11), height=8, width=30)
# listbox.pack(pady=10)
# 添加：listbox.insert(tk.END, "项目")
# 删除选中：listbox.delete(listbox.curselection())
# 获取选中：listbox.get(listbox.curselection())

# 画布（画图、做动画）
# canvas = tk.Canvas(root, width=400, height=300, bg="white")
# canvas.pack(pady=10)
# 画线：canvas.create_line(x1, y1, x2, y2, fill="red", width=3)
# 画矩形：canvas.create_rectangle(x1, y1, x2, y2, fill="blue")
# 画椭圆：canvas.create_oval(x1, y1, x2, y2, fill="green")
# 画文字：canvas.create_text(x, y, text="文字", font=("微软雅黑", 20))

# 表格（ttk.Treeview）
# tree = ttk.Treeview(root, columns=("col1", "col2"), show="headings", height=10)
# tree.heading("col1", text="列1")
# tree.heading("col2", text="列2")
# tree.pack(pady=10)
# 添加行：tree.insert("", tk.END, values=("值1", "值2"))
# 获取选中：tree.item(tree.selection()[0], "values")

# 下拉选择框（ttk.Combobox）
# combo = ttk.Combobox(root, values=["选项A", "选项B", "选项C"],
#                      state="readonly", width=15)
# combo.pack(pady=10)
# combo.current(0)  # 默认选中第一项
# 获取选中：combo.get()

# 滑动条
# scale = tk.Scale(root, from_=0, to=100, orient=tk.HORIZONTAL,
#                  length=200, font=("微软雅黑", 10))
# scale.pack(pady=10)
# 获取值：scale.get()

# 复选框
# check_var = tk.BooleanVar()
# tk.Checkbutton(root, text="启用某功能", variable=check_var,
#                font=("微软雅黑", 11)).pack()
# 获取状态：check_var.get()  # True 或 False

# 单选框
# radio_var = tk.StringVar(value="a")
# tk.Radiobutton(root, text="选项A", variable=radio_var,
#                value="a", font=("微软雅黑", 11)).pack()
# tk.Radiobutton(root, text="选项B", variable=radio_var,
#                value="b", font=("微软雅黑", 11)).pack()
# 获取选中：radio_var.get()

# 进度条（ttk.Progressbar）
# progress = ttk.Progressbar(root, length=300, mode="determinate")
# progress.pack(pady=10)
# 设置进度：progress["value"] = 50

# ---------- 常用弹窗 ----------
# 信息提示：messagebox.showinfo("标题", "消息内容")
# 警告提示：messagebox.showwarning("标题", "警告内容")
# 确认弹窗：result = messagebox.askyesno("标题", "确定吗？")
# 文件打开：file = filedialog.askopenfilename(filetypes=[("所有文件", "*.*")])
# 文件保存：file = filedialog.asksaveasfilename(defaultextension=".txt")

# ---------- 常用事件绑定 ----------
# 键盘事件：widget.bind("<KeyRelease>", function)
# 鼠标点击：widget.bind("<Button-1>", function)
# 鼠标双击：widget.bind("<Double-1>", function)

# ---------- 定时器 ----------
# root.after(1000, function)  # 1000 毫秒后执行 function
# 要做循环定时，在 function 内部再调用 root.after(1000, function)

# ---------- 数据保存 ----------
# JSON 保存：
# with open("data.json", "w", encoding="utf-8") as f:
#     json.dump(data_dict, f, ensure_ascii=False, indent=2)
# JSON 读取：
# with open("data.json", "r", encoding="utf-8") as f:
#     data = json.load(f)

# ---------- 布局技巧 ----------
# pack(side=tk.TOP/BOTTOM/LEFT/RIGHT, padx=10, pady=10, fill=tk.X, expand=True)
# grid(row=0, column=0, padx=10, pady=10, sticky="w")
# Frame 容器：
# frame = tk.Frame(root, bg="#f5f5f5")
# frame.pack(pady=10)

# ============================================================
# 你的代码到这里结束 ↑↑↑
# ============================================================

# ---------- 示例：一个简单的标题和欢迎信息 ----------
# 以下是一个最小示例，你可以删除它们，换成自己的代码

title_label = tk.Label(root, text="🎨 我的第一个作品",
                       font=("微软雅黑", 20, "bold"),
                       bg="#f5f5f5", fg="#333")
title_label.pack(pady=30)

subtitle_label = tk.Label(root, text="从这里开始你的创作之旅！",
                          font=("微软雅黑", 13),
                          bg="#f5f5f5", fg="#888")
subtitle_label.pack(pady=5)

info_label = tk.Label(root, text="💡 提示：打开本文件的注释，里面有所有可用的控件清单哦~",
                      font=("微软雅黑", 9),
                      bg="#f5f5f5", fg="#aaa")
info_label.pack(pady=30)

root.mainloop()
