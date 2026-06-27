import tkinter as tk

# ========================================
# 第 21 节：项目2 — 简易计算器（上）
# 知识点：grid 网格布局 + lambda 传参 + StringVar 数字拼接
# 本节目标：搭好计算器按钮面板，点击按钮能输入数字和运算符
# ========================================

# 1. 创建主窗口
root = tk.Tk()
root.title("简易计算器")                 # 窗口标题
root.geometry("350x420")                 # 窗口大小：宽350，高420
root.configure(bg="#f0f4f8")             # 背景色：浅灰蓝
root.resizable(False, False)             # 禁止调整窗口大小，保持布局整齐

# 2. 创建 StringVar，用于绑定输入框的显示内容
#    StringVar 是 tkinter 专用的字符串变量，修改它会自动更新 Entry 的显示
entry_var = tk.StringVar()

# 3. 创建输入框（显示屏）
#    使用 state="readonly" 防止用户用键盘直接打字
#    用户只能通过点击按钮来输入，更像真实的计算器
entry = tk.Entry(
    root,
    textvariable=entry_var,              # 绑定到 StringVar，二者自动同步
    font=("Arial", 22),                  # 字体：Arial，大小 22
    justify="right",                     # 文字右对齐，像计算器显示屏
    state="readonly",                    # 只读模式：禁止键盘输入
    readonlybackground="white",          # 只读时的背景色
    relief="flat",                       # 扁平边框
    bd=10                                # 边框宽度（内边距效果）
)
# Entry 放在第 0 行，横跨 4 列，左右拉伸填满
entry.grid(row=0, column=0, columnspan=4,
           sticky="ew", padx=10, pady=(15, 8))


# 4. 定义按钮点击后的回调函数
def click(key):
    """
    处理按钮点击：把点击的字符拼接到显示屏已有内容的后面
    参数 key：被点击按钮代表的字符（如 "1"、"+"、"C" 等）
    """
    current = entry_var.get()            # 获取当前显示屏的内容
    entry_var.set(current + key)         # 在当前内容后追加新字符


def clear():
    """清空显示屏（C 按钮的回调函数）"""
    entry_var.set("")                    # 把 StringVar 设为空字符串


def backspace():
    """删除最后一个字符（← 按钮的回调函数）"""
    current = entry_var.get()
    entry_var.set(current[:-1])          # 切片取到倒数第二位，相当于删除最后一位


# 5. 创建所有按钮
#    按钮排列按照标准计算器布局：4 列，从 row=1 开始

# ---- 第 1 行：C、←、（空）、/ ----
btn_c = tk.Button(
    root, text="C",
    font=("Arial", 15, "bold"),
    bg="#ff6b6b", fg="white",           # 红色背景，白色文字（清空按钮突出显示）
    activebackground="#ee5a5a",         # 鼠标按下时的颜色
    command=clear,                       # 点击后调用 clear() 清空屏幕
    width=5, height=2,
    relief="flat",                       # 扁平样式
    cursor="hand2"                       # 鼠标悬停时显示手指光标
)
btn_c.grid(row=1, column=0, padx=3, pady=3)

btn_back = tk.Button(
    root, text="←",
    font=("Arial", 15, "bold"),
    bg="#ffd93d", fg="#333333",         # 黄色背景
    activebackground="#f0c930",
    command=backspace,                   # 点击后删除最后一个字符
    width=5, height=2,
    relief="flat",
    cursor="hand2"
)
btn_back.grid(row=1, column=1, padx=3, pady=3)

# column=2 留空（可选地放其他符号按钮）

btn_div = tk.Button(
    root, text="/",
    font=("Arial", 15, "bold"),
    bg="#6c5ce7", fg="white",           # 紫色背景（运算符统一颜色）
    activebackground="#5a4bd1",
    command=lambda: click("/"),          # 用 lambda 传参：点击时调用 click("/")
    width=5, height=2,
    relief="flat",
    cursor="hand2"
)
btn_div.grid(row=1, column=3, padx=3, pady=3)

# ---- 第 2 行：7、8、9、* ----
# 使用循环批量创建数字按钮，减少重复代码
# 注意：lambda n=num 的写法确保了每个按钮记住自己的数字
for i, num in enumerate([7, 8, 9]):
    btn = tk.Button(
        root, text=str(num),
        font=("Arial", 15),
        bg="#ffffff", fg="#333333",     # 白色背景
        activebackground="#e8e8e8",
        # 关键：用 lambda n=num 来"固定"当前循环变量的值
        # 如果写成 lambda: click(str(num))，所有按钮都会用 num 的最终值
        command=lambda n=num: click(str(n)),
        width=5, height=2,
        relief="flat",
        cursor="hand2"
    )
    btn.grid(row=2, column=i, padx=3, pady=3)

btn_mul = tk.Button(
    root, text="*",
    font=("Arial", 15, "bold"),
    bg="#6c5ce7", fg="white",
    activebackground="#5a4bd1",
    command=lambda: click("*"),
    width=5, height=2,
    relief="flat",
    cursor="hand2"
)
btn_mul.grid(row=2, column=3, padx=3, pady=3)

# ---- 第 3 行：4、5、6、- ----
for i, num in enumerate([4, 5, 6]):
    btn = tk.Button(
        root, text=str(num),
        font=("Arial", 15),
        bg="#ffffff", fg="#333333",
        activebackground="#e8e8e8",
        command=lambda n=num: click(str(n)),
        width=5, height=2,
        relief="flat",
        cursor="hand2"
    )
    btn.grid(row=3, column=i, padx=3, pady=3)

btn_sub = tk.Button(
    root, text="-",
    font=("Arial", 15, "bold"),
    bg="#6c5ce7", fg="white",
    activebackground="#5a4bd1",
    command=lambda: click("-"),
    width=5, height=2,
    relief="flat",
    cursor="hand2"
)
btn_sub.grid(row=3, column=3, padx=3, pady=3)

# ---- 第 4 行：1、2、3、+ ----
for i, num in enumerate([1, 2, 3]):
    btn = tk.Button(
        root, text=str(num),
        font=("Arial", 15),
        bg="#ffffff", fg="#333333",
        activebackground="#e8e8e8",
        command=lambda n=num: click(str(n)),
        width=5, height=2,
        relief="flat",
        cursor="hand2"
    )
    btn.grid(row=4, column=i, padx=3, pady=3)

btn_add = tk.Button(
    root, text="+",
    font=("Arial", 15, "bold"),
    bg="#6c5ce7", fg="white",
    activebackground="#5a4bd1",
    command=lambda: click("+"),
    width=5, height=2,
    relief="flat",
    cursor="hand2"
)
btn_add.grid(row=4, column=3, padx=3, pady=3)

# ---- 第 5 行：0（跨2列）、.、= ----
btn_0 = tk.Button(
    root, text="0",
    font=("Arial", 15),
    bg="#ffffff", fg="#333333",
    activebackground="#e8e8e8",
    command=lambda: click("0"),
    width=12, height=2,                 # 宽度更大，因为跨 2 列
    relief="flat",
    cursor="hand2"
)
# 0 按钮横跨第 0 和第 1 列，像真实计算器那样
btn_0.grid(row=5, column=0, columnspan=2, padx=3, pady=3)

btn_dot = tk.Button(
    root, text=".",
    font=("Arial", 15, "bold"),
    bg="#ffffff", fg="#333333",
    activebackground="#e8e8e8",
    command=lambda: click("."),
    width=5, height=2,
    relief="flat",
    cursor="hand2"
)
btn_dot.grid(row=5, column=2, padx=3, pady=3)

btn_eq = tk.Button(
    root, text="=",
    font=("Arial", 15, "bold"),
    bg="#00b894", fg="white",           # 绿色背景（等号按钮突出显示）
    activebackground="#00a381",
    command=lambda: click("="),          # 本节暂时只显示 "="，下一节才做计算
    width=5, height=2,
    relief="flat",
    cursor="hand2"
)
btn_eq.grid(row=5, column=3, padx=3, pady=3)


# 6. 启动主循环（必须放在代码最后！）
root.mainloop()
