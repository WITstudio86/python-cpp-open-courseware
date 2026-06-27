import tkinter as tk
from tkinter import ttk

# ========================================
# 第 47 节：tkinter 进阶 —— ttk 美化番茄钟对比演示
# ========================================
# 本节重点：演示 ttk 主题美化、进度条、Combobox 等进阶组件
# 对比普通 tk 和 ttk 的视觉差异

root = tk.Tk()
root.title("番茄钟 · ttk 美化版")
root.geometry("420x480")
root.configure(bg="#fafafa")

# ---- 设置 ttk 主题和样式 ----
style = ttk.Style()
# 查看可用主题（不同系统显示不同）
available_themes = style.theme_names()
print(f"可用主题：{available_themes}")

# 选择主题（macOS 可用 aqua，Windows 可用 vista，跨平台推荐 clam）
style.theme_use("clam")

# 全局样式：影响所有对应类型的 ttk 控件
style.configure("TLabel", font=("微软雅黑", 12), background="#fafafa")
style.configure("TButton", font=("微软雅黑", 11), padding=(15, 8))

# 自定义子样式：只影响指定了 style 名称的控件
style.configure("Title.TLabel",
                font=("微软雅黑", 20, "bold"),
                foreground="#e65100",
                background="#fafafa")

style.configure("Timer.TLabel",
                font=("微软雅黑", 56, "bold"),
                foreground="#1565c0",
                background="white")

style.configure("Start.TButton",
                font=("微软雅黑", 13, "bold"),
                padding=(25, 10))

style.configure("Reset.TButton",
                font=("微软雅黑", 11))

# 主容器 Frame
main_frame = tk.Frame(root, bg="#fafafa")
main_frame.pack(expand=True, fill=tk.BOTH, padx=30, pady=20)

# 标题
ttk.Label(main_frame, text="🍅 番茄钟", style="Title.TLabel").pack(pady=(10, 5))

# 计时器显示（用 Frame 包一层做白色背景卡片效果）
timer_bg = tk.Frame(main_frame, bg="white", relief=tk.RIDGE, bd=2)
timer_bg.pack(pady=20, ipadx=40, ipady=30)

timer_label = ttk.Label(timer_bg, text="25:00", style="Timer.TLabel")
timer_label.pack()

# 状态模式显示
mode_var = tk.StringVar(value="▶ 工作中...")
mode_label = ttk.Label(main_frame, textvariable=mode_var,
                       font=("微软雅黑", 13), foreground="#666")
mode_label.pack(pady=5)

# 进度条（ttk 独有控件！普通 tk 没有）
progress = ttk.Progressbar(main_frame, length=300, mode="determinate")
progress.pack(pady=(10, 20))
progress["value"] = 30  # 演示：设置到 30% 位置

# 按钮区域
btn_frame = tk.Frame(main_frame, bg="#fafafa")
btn_frame.pack(pady=10)

start_btn = ttk.Button(btn_frame, text="▶ 开始专注", style="Start.TButton")
start_btn.pack(side=tk.LEFT, padx=5)

reset_btn = ttk.Button(btn_frame, text="🔄 重置", style="Reset.TButton")
reset_btn.pack(side=tk.LEFT, padx=5)

# 时间设置（Combobox：ttk 独有控件！）
setting_frame = tk.Frame(main_frame, bg="#fafafa")
setting_frame.pack(pady=20)

ttk.Label(setting_frame, text="时长设置：").pack(side=tk.LEFT)

combo = ttk.Combobox(setting_frame,
                     values=["15分钟", "25分钟", "45分钟", "60分钟"],
                     width=10, state="readonly")
combo.pack(side=tk.LEFT, padx=10)
combo.current(1)  # 默认选中第 2 项（25分钟）

# 底部提示
ttk.Label(main_frame,
          text="💡 ttk 主题让界面更现代化\n试试切换 theme_use 看不同风格",
          font=("微软雅黑", 9), foreground="#aaa",
          justify="center").pack(pady=(15, 0))

root.mainloop()
