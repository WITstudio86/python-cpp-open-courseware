import tkinter as tk
import time

# ========================================
# 第 19 节：项目1 —— 电子时钟（上）
# 知识点：time 模块、strftime、Label 显示、after() 定时刷新
# ========================================

# ---------- 1. 创建窗口 ----------
root = tk.Tk()
root.title("电子时钟")                      # 窗口标题
root.geometry("400x200")                    # 宽 400，高 200（像素）
root.configure(bg="#1a1a1a")                # 深色背景，模拟电子表屏幕

# ---------- 2. 创建时间显示的 Label ----------
# Label 是用来显示文字/图片的控件
# font=("Consolas", 48) → 等宽字体，字号 48，每个数字宽度一样，跳动时不会左右晃动
# fg → 文字颜色（fg = foreground）
# bg → 背景颜色，和窗口背景一致
time_label = tk.Label(
    root,
    text="00:00:00",                        # 程序刚启动时显示的初始文字
    font=("Consolas", 48, "bold"),          # Consolas 等宽字体 + 加粗 + 48号
    fg="#00ff00",                           # 亮绿色（00ff00 = 纯绿色），电子表经典配色
    bg="#1a1a1a"                            # 深灰色背景，和窗口融为一体
)
# expand=True → Label 在窗口里自动居中（上下左右都留出均匀空间）
time_label.pack(expand=True)

# ---------- 3. 定义刷新时间的函数 ----------
def update_time():
    """
    这个函数做了三件事：
    ① 用 time.strftime() 获取当前时间，格式化成 "时:分:秒"
    ② 把格式化后的时间文字设置到 Label 上
    ③ 用 root.after(1000, update_time) 预约 1 秒后再次执行自己
    """
    # 获取当前系统时间，并按指定格式转成字符串
    # %H → 小时（24 小时制，00~23）
    # %M → 分钟（00~59）
    # %S → 秒（00~59）
    current_time = time.strftime("%H:%M:%S")

    # 更新 Label 显示的文字内容
    # config() 可以修改已创建控件的属性
    time_label.config(text=current_time)

    # 关键步骤：用 after() 设置定时器
    # 第一个参数 1000 → 1000 毫秒 = 1 秒
    # 第二个参数 update_time → 1 秒后要执行的函数名（注意：不加括号！）
    # 这样 update_time 运行完 1 秒后又会调用自己，形成无限循环
    root.after(1000, update_time)

# ---------- 4. 启动时钟 ----------
# 第一次手动调用 update_time()，之后它就会用 after() 自动循环下去
update_time()

# ---------- 5. 启动窗口主循环 ----------
# mainloop() 让窗口持续显示，监听用户操作（关闭、点击等）
# 这行必须放在代码末尾！
root.mainloop()
