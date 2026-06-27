import tkinter as tk

# ========================================
# 第 22 节：项目2 —— 简易计算器（下）
# 知识点：连续运算、C/← 功能、eval() 求值、键盘绑定 bind()
# ========================================

# ---------- 创建窗口 ----------
root = tk.Tk()
root.title("简易计算器")
root.geometry("350x450")
root.configure(bg="#2c3e50")        # 深色背景，衬托出计算器的科技感
root.resizable(False, False)       # 固定窗口大小，防止布局错乱

# ============================================
# ① 输入框（显示表达式和计算结果）
# ============================================

# StringVar 是 tkinter 的"魔法变量"——你改它的值，Entry 自动更新
entry_var = tk.StringVar()
entry_var.set("")  # 初始为空

entry = tk.Entry(
    root,
    textvariable=entry_var,          # 绑定 StringVar，实现动态更新
    font=("Consolas", 24),           # 等宽大字体，数字对齐好看
    justify="right",                 # 文字右对齐（像真正的计算器）
    state="readonly",                # 只读模式，禁止用户直接在输入框打字
    readonlybackground="#ecf0f1",    # 只读时的背景色（米白色）
    fg="#2c3e50"                     # 文字颜色（深灰色）
)
# 输入框横跨 4 列，占据第 0 行
entry.grid(row=0, column=0, columnspan=4, padx=10, pady=15, sticky="nsew")

# ============================================
# ② 按钮回调函数 —— 计算器的"大脑"
# ============================================

def click(key):
    """
    普通按键回调：把按下的字符追加到输入框的表达式末尾
    参数 key: 要追加的字符（如 "1"、"+"、"*" 等）
    """
    current = entry_var.get()        # 获取当前输入框的内容
    entry_var.set(current + str(key))  # 把新字符拼接到末尾


def clear():
    """
    C 按钮回调：一键清空输入框
    把 StringVar 设成空字符串，输入框立刻变空
    """
    entry_var.set("")


def backspace():
    """
    ← 按钮回调：删除最后一个字符（退格）
    用字符串切片 [:-1] 去掉末尾字符
    空字符串 [:-1] 仍然是空字符串，不会报错
    """
    current = entry_var.get()
    entry_var.set(current[:-1])      # 切片：从开头取到倒数第二个字符


def calculate():
    """
    = 按钮回调：计算表达式的值
    用 eval() 把输入框的字符串当成 Python 代码执行
    try-except 是"安全网"——表达式非法时不崩溃，显示"错误"
    """
    try:
        # eval() 会自动处理运算优先级，比如 "2+3*4" 会算出 14 而不是 20
        result = eval(entry_var.get())
        # 把结果转成字符串，写回输入框
        # 如果是整数就去掉 .0（比如 3.0 → 3），保留小数
        if isinstance(result, float) and result == int(result):
            result = int(result)
        entry_var.set(str(result))
    except:
        # 表达式出错（如除以 0、连续运算符等），显示"错误"
        entry_var.set("错误")


# ============================================
# ③ 按钮数据 —— 定义每个按钮的文字和位置
# ============================================
# 格式：(按钮文字, 所在行, 所在列, 占几列)
buttons = [
    # 第 1 行：功能键 + 乘除
    ("C",  1, 0, 1), ("←", 1, 1, 1), ("/",  1, 2, 1), ("*", 1, 3, 1),
    # 第 2 行：7 8 9 -
    ("7",  2, 0, 1), ("8", 2, 1, 1), ("9",  2, 2, 1), ("-", 2, 3, 1),
    # 第 3 行：4 5 6 +
    ("4",  3, 0, 1), ("5", 3, 1, 1), ("6",  3, 2, 1), ("+", 3, 3, 1),
    # 第 4 行：1 2 3
    ("1",  4, 0, 1), ("2", 4, 1, 1), ("3",  4, 2, 1),
    # 第 5 行：0 . =
    ("0",  5, 0, 1), (".", 5, 1, 1), ("=",  5, 2, 2),   # = 占 2 列
]

# ============================================
# ④ 创建按钮 —— 把数据变成真正的按钮控件
# ============================================
for (text, row, col, colspan) in buttons:
    # 根据按钮文字，决定点击后调用哪个函数
    if text == "C":
        cmd = clear                      # C → 清空
    elif text == "←":
        cmd = backspace                  # ← → 退格
    elif text == "=":
        cmd = calculate                  # = → 计算
    else:
        # lambda 技巧：用默认参数 t=text 把当前的 text 值"捕获"进去
        # 如果不这样做，lambda 会延迟取值，所有按钮都会传最后一个 text
        cmd = lambda t=text: click(t)    # 数字/运算符 → 追加

    btn = tk.Button(
        root,
        text=text,                       # 按钮上显示的文字
        font=("Consolas", 16, "bold"),  # 等宽字体，加粗
        width=5,                         # 按钮宽度（字符数）
        height=2,                        # 按钮高度（行数）
        command=cmd,                     # 点击后调用的函数
        bg="#34495e",                    # 默认背景色（深蓝灰）
        fg="white",                      # 文字颜色（白色）
        activebackground="#1abc9c",      # 鼠标按下时的背景色（青色）
        relief="flat",                   # 扁平风格，无边框凸起
        bd=1                             # 边框宽度为 1 像素
    )
    btn.grid(row=row, column=col, columnspan=colspan, padx=2, pady=2, sticky="nsew")

    # 把 = 按钮标成醒目的橙色，和其他按钮区分开
    if text == "=":
        btn.configure(bg="#e67e22", activebackground="#d35400")


# ============================================
# ⑤ 键盘按键绑定 —— 不用鼠标也能操作！
# ============================================
def key_press(event):
    """
    键盘按键事件处理函数
    参数 event: tkinter 传入的事件对象，包含按键信息
      - event.char:    可打印字符（如 "1"、"+"、"a"）
      - event.keysym:  按键的名称（如 "Return"、"BackSpace"、"Escape"）
    """
    key = event.char  # 获取按键对应的字符

    # ① 数字、运算符、小数点 → 和点击按钮一样，追加到表达式
    if key in "0123456789+-*/.=":
        if key == "=":
            calculate()       # 键盘上的 = 也是等于
        else:
            click(key)

    # ② 回车键（Enter / Return）→ 等于 =
    elif event.keysym == "Return":
        calculate()

    # ③ 退格键（Backspace）→ 删除最后一个字符
    elif event.keysym == "BackSpace":
        backspace()

    # ④ ESC 键 → 清空（等于 C 按钮）
    elif event.keysym == "Escape":
        clear()

    # 其他按键（如字母、空格等）直接忽略，不做任何反应


# 把 <Key> 事件绑定到整个窗口
# 这样无论焦点在哪个控件上，按键都能被捕获
root.bind("<Key>", key_press)


# ============================================
# ⑥ 布局权重设置 —— 让按钮均匀分布
# ============================================
# 设置每行每列的 weight，让按钮在窗口缩放时能自适应大小
for i in range(6):     # 6 行（第 0 行是输入框，第 1~5 行是按钮）
    root.grid_rowconfigure(i, weight=1)
for j in range(4):     # 4 列
    root.grid_columnconfigure(j, weight=1)

# ============================================
# ⑦ 启动窗口主循环
# ============================================
root.mainloop()
