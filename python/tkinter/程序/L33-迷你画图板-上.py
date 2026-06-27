import tkinter as tk

# ========================================
# 第 33 节：项目 8 — 迷你画图板（铅笔 + 直线）
# 功能：铅笔自由涂鸦、直线工具（带预览虚线）、清空画布
# ========================================

# 1. 创建主窗口
root = tk.Tk()
root.title("迷你画图板 🎨")
root.geometry("750x580")
root.configure(bg="#f5f5f5")

# ========================================
# 2. 状态变量
# ========================================

# 当前选中的工具（pencil 或 line）
tool = tk.StringVar(value="pencil")

# 画笔颜色和粗细
pen_color = "black"
pen_width = 2

# 铅笔工具用的「上一个点」坐标
last_x = None
last_y = None

# 直线工具用的「起始点」坐标
start_x = None
start_y = None

# 直线工具的预览线 ID（虚线，拖拽时显示）
preview_line_id = None

# ========================================
# 3. 鼠标事件处理函数
# ========================================

def on_mouse_press(event):
    """鼠标按下时的处理"""
    global last_x, last_y, start_x, start_y

    current_tool = tool.get()

    if current_tool == "pencil":
        # 铅笔：记录起始点，准备开始画线
        last_x = event.x
        last_y = event.y

    elif current_tool == "line":
        # 直线：记录起点
        start_x = event.x
        start_y = event.y


def on_mouse_drag(event):
    """鼠标拖拽（按住移动）时的处理"""
    global last_x, last_y, preview_line_id

    current_tool = tool.get()

    if current_tool == "pencil":
        # 铅笔：从上一点到当前点画一条小线段
        if last_x is not None and last_y is not None:
            canvas.create_line(
                last_x, last_y,           # 起点（上一个位置）
                event.x, event.y,         # 终点（当前位置）
                fill=pen_color,
                width=pen_width,
                capstyle=tk.ROUND,        # 圆头线端，让笔迹更流畅
                smooth=True               # 平滑处理
            )
            # 更新「上一个点」为当前位置
            last_x = event.x
            last_y = event.y

    elif current_tool == "line":
        # 直线：先删除旧的预览线，再画新的
        if preview_line_id is not None:
            canvas.delete(preview_line_id)

        # 画灰色虚线作为预览
        preview_line_id = canvas.create_line(
            start_x, start_y,
            event.x, event.y,
            fill="gray",
            dash=(5, 5),   # 虚线样式：5px 实线 + 5px 空白
            width=1
        )


def on_mouse_release(event):
    """鼠标释放时的处理"""
    global last_x, last_y, preview_line_id

    current_tool = tool.get()

    if current_tool == "pencil":
        # 铅笔：重置上一个点
        last_x = None
        last_y = None

    elif current_tool == "line":
        # 直线：删除预览虚线，画真正的直线
        if preview_line_id is not None:
            canvas.delete(preview_line_id)
            preview_line_id = None

        # 画最终的直线
        canvas.create_line(
            start_x, start_y,
            event.x, event.y,
            fill=pen_color,
            width=pen_width,
            capstyle=tk.ROUND
        )


# ========================================
# 4. 辅助功能
# ========================================

def clear_canvas():
    """清空画布上的所有内容"""
    canvas.delete("all")


def set_color(new_color):
    """切换画笔颜色"""
    global pen_color
    pen_color = new_color


# ========================================
# 5. 界面布局
# ========================================

# --- 标题 ---
title_label = tk.Label(
    root,
    text="🎨 迷你画图板",
    font=("微软雅黑", 20, "bold"),
    bg="#f5f5f5",
    fg="#333333"
)
title_label.pack(pady=(15, 5))

# --- 工具栏 ---
toolbar = tk.Frame(
    root,
    bg="#e8e8e8",
    relief="solid",
    bd=1,
    padx=5,
    pady=5
)
toolbar.pack(fill=tk.X, padx=15, pady=5)

# 工具选择标签
tk.Label(
    toolbar,
    text="🔧 工具：",
    font=("微软雅黑", 12),
    bg="#e8e8e8",
    fg="#333"
).pack(side=tk.LEFT, padx=(10, 5))

# 铅笔工具（单选按钮）
tk.Radiobutton(
    toolbar,
    text="✏️ 铅笔",
    variable=tool,
    value="pencil",
    bg="#e8e8e8",
    font=("微软雅黑", 11),
    indicatoron=True
).pack(side=tk.LEFT, padx=5)

# 直线工具（单选按钮）
tk.Radiobutton(
    toolbar,
    text="📏 直线",
    variable=tool,
    value="line",
    bg="#e8e8e8",
    font=("微软雅黑", 11),
    indicatoron=True
).pack(side=tk.LEFT, padx=5)

# 分隔线
tk.Frame(toolbar, width=2, height=24, bg="#ccc").pack(
    side=tk.LEFT, padx=10
)

# 颜色选择标签
tk.Label(
    toolbar,
    text="🎨 颜色：",
    font=("微软雅黑", 12),
    bg="#e8e8e8",
    fg="#333"
).pack(side=tk.LEFT, padx=(5, 5))

# 颜色按钮
colors = [
    ("⚫ 黑", "black"),
    ("🔴 红", "#e74c3c"),
    ("🔵 蓝", "#3498db"),
    ("🟢 绿", "#2ecc71"),
    ("🟠 橙", "#f39c12"),
]

for label, color_val in colors:
    btn = tk.Button(
        toolbar,
        text=label,
        command=lambda c=color_val: set_color(c),
        font=("微软雅黑", 10),
        bg="white" if color_val != pen_color else "#ddd",
        relief="flat",
        padx=8,
        cursor="hand2"
    )
    btn.pack(side=tk.LEFT, padx=3)

# 清空按钮（放在工具栏最右边）
clear_btn = tk.Button(
    toolbar,
    text="🗑️ 清空画布",
    command=clear_canvas,
    font=("微软雅黑", 11),
    bg="#e07060",
    fg="white",
    relief="flat",
    padx=15,
    cursor="hand2"
)
clear_btn.pack(side=tk.RIGHT, padx=10)

# --- Canvas 画布 ---
canvas = tk.Canvas(
    root,
    width=700,
    height=420,
    bg="white",
    relief="solid",
    bd=1,
    cursor="crosshair"  # 鼠标在画布上显示十字准星
)
canvas.pack(padx=15, pady=10)

# 绑定鼠标事件到画布
canvas.bind("<Button-1>", on_mouse_press)          # 鼠标左键按下
canvas.bind("<B1-Motion>", on_mouse_drag)          # 按住左键拖拽
canvas.bind("<ButtonRelease-1>", on_mouse_release) # 鼠标左键释放

# --- 底部提示 ---
hint_label = tk.Label(
    root,
    text="💡 铅笔 = 自由涂鸦（按住拖拽） | 直线 = 点击拖拽画线（虚线预览）",
    font=("微软雅黑", 10),
    bg="#f5f5f5",
    fg="#999999"
)
hint_label.pack(pady=12)

# ========================================
# 6. 启动主循环
# ========================================

root.mainloop()
