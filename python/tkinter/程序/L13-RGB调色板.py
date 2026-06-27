import tkinter as tk

# ========================================
# 第 13 节：RGB 调色板
# 知识点：Scale 滑块、Spinbox 数字框、实时颜色更新
# ========================================

# 1. 创建主窗口
root = tk.Tk()
root.title("RGB 调色板")
root.geometry("500x400")
root.configure(bg="#f5f5f5")


# ---------- 颜色更新函数 ----------
def update_color(*args):
    """
    核心函数：读取 RGB 三个滑块的值，合成颜色并更新预览区。
    *args 让这个函数既可以接收 Scale 传过来的值，
    也可以被 Spinbox 的 command 调用。
    """
    # 从三个 Scale 滑块获取当前值
    r = red_scale.get()
    g = green_scale.get()
    b = blue_scale.get()

    # 把十进制 RGB 转成十六进制颜色码（如 255 → "ff"）
    hex_color = f"#{r:02x}{g:02x}{b:02x}"

    # 更新右侧颜色预览区的背景色
    color_preview.config(bg=hex_color)

    # 更新下方 RGB 数值标签
    rgb_label.config(text=f"R: {r}  G: {g}  B: {b}\n{hex_color}")

    # 同步 Spinbox 的值（让数字框和滑块保持一致）
    red_spin.delete(0, tk.END)
    red_spin.insert(0, str(r))
    green_spin.delete(0, tk.END)
    green_spin.insert(0, str(g))
    blue_spin.delete(0, tk.END)
    blue_spin.insert(0, str(b))


# ---------- 标题 ----------
title_label = tk.Label(root, text="🎨 RGB 调色板",
                       font=("微软雅黑", 20, "bold"),
                       bg="#f5f5f5", fg="#333")
title_label.pack(pady=10)

# ---------- 主容器（左右布局） ----------
main_frame = tk.Frame(root, bg="#f5f5f5")
main_frame.pack(pady=10)

# 左侧：滑块控制区域
left_frame = tk.Frame(main_frame, bg="#f5f5f5")
left_frame.pack(side=tk.LEFT, padx=(0, 15))

# 右侧：颜色预览区（用一个 Label 显示混合后的颜色）
color_preview = tk.Label(main_frame, text="",
                         bg="#000000",        # 初始黑色
                         width=18, height=8,
                         relief="ridge", bd=3)  # 凸起边框
color_preview.pack(side=tk.LEFT)

# ========================================
# 红色通道：Scale 滑块 + Spinbox 数字框
# ========================================
red_frame = tk.Frame(left_frame, bg="#f5f5f5")
red_frame.pack(pady=5, anchor="w")

tk.Label(red_frame, text="🔴 R：", font=("微软雅黑", 12),
         bg="#f5f5f5", fg="#c0392b", width=6).pack(side=tk.LEFT)

# Scale 滑块：from_=0, to=255, 横向，每次拖动调用 update_color
red_scale = tk.Scale(red_frame, from_=0, to=255,
                     orient=tk.HORIZONTAL,   # 横向
                     length=220,              # 滑块轨道长度
                     command=update_color,    # 拖动时自动调用
                     bg="#f5f5f5")
red_scale.set(128)  # 设置初始值（灰色 128）
red_scale.pack(side=tk.LEFT)

# Spinbox 数字微调框：精确调节红色分量
red_spin = tk.Spinbox(red_frame, from_=0, to=255,
                      width=4,                # 输入框宽度
                      command=update_color,   # 点击箭头时调用
                      font=("微软雅黑", 10))
red_spin.delete(0, tk.END)
red_spin.insert(0, "128")  # 初始显示 128
red_spin.pack(side=tk.LEFT, padx=5)

# ========================================
# 绿色通道
# ========================================
green_frame = tk.Frame(left_frame, bg="#f5f5f5")
green_frame.pack(pady=5, anchor="w")

tk.Label(green_frame, text="🟢 G：", font=("微软雅黑", 12),
         bg="#f5f5f5", fg="#27ae60", width=6).pack(side=tk.LEFT)

green_scale = tk.Scale(green_frame, from_=0, to=255,
                       orient=tk.HORIZONTAL,
                       length=220,
                       command=update_color,
                       bg="#f5f5f5")
green_scale.set(128)
green_scale.pack(side=tk.LEFT)

green_spin = tk.Spinbox(green_frame, from_=0, to=255,
                        width=4,
                        command=update_color,
                        font=("微软雅黑", 10))
green_spin.delete(0, tk.END)
green_spin.insert(0, "128")
green_spin.pack(side=tk.LEFT, padx=5)

# ========================================
# 蓝色通道
# ========================================
blue_frame = tk.Frame(left_frame, bg="#f5f5f5")
blue_frame.pack(pady=5, anchor="w")

tk.Label(blue_frame, text="🔵 B：", font=("微软雅黑", 12),
         bg="#f5f5f5", fg="#2980b9", width=6).pack(side=tk.LEFT)

blue_scale = tk.Scale(blue_frame, from_=0, to=255,
                      orient=tk.HORIZONTAL,
                      length=220,
                      command=update_color,
                      bg="#f5f5f5")
blue_scale.set(128)
blue_scale.pack(side=tk.LEFT)

blue_spin = tk.Spinbox(blue_frame, from_=0, to=255,
                       width=4,
                       command=update_color,
                       font=("微软雅黑", 10))
blue_spin.delete(0, tk.END)
blue_spin.insert(0, "128")
blue_spin.pack(side=tk.LEFT, padx=5)

# ---------- 颜色值信息标签 ----------
# 显示当前的 RGB 数值和十六进制颜色码
rgb_label = tk.Label(root, text="R: 128  G: 128  B: 128\n#808080",
                     font=("微软雅黑", 13),
                     bg="#f5f5f5", fg="#333")
rgb_label.pack(pady=10)

# ---------- 预设颜色快捷按钮 ----------
def set_preset(r, g, b):
    """
    一键设置预设颜色。
    把三个滑块和 Spinbox 都设置为指定的 RGB 值。
    """
    red_scale.set(r)
    green_scale.set(g)
    blue_scale.set(b)
    update_color()  # 手动触发颜色更新

preset_frame = tk.Frame(root, bg="#f5f5f5")
preset_frame.pack(pady=5)

# 预设颜色列表：（名称, R, G, B）
presets = [
    ("红色", 255, 0, 0),
    ("绿色", 0, 255, 0),
    ("蓝色", 0, 0, 255),
    ("白色", 255, 255, 255),
    ("黑色", 0, 0, 0),
]

for name, r, g, b in presets:
    # 根据颜色的亮度决定按钮文字颜色（深色背景用白字，浅色背景用黑字）
    text_color = "white" if (r + g + b) < 384 else "black"
    btn = tk.Button(preset_frame, text=name,
                    bg=f"#{r:02x}{g:02x}{b:02x}",   # 按钮背景色 = 预设颜色
                    fg=text_color,
                    font=("微软雅黑", 10),
                    command=lambda r=r, g=g, b=b: set_preset(r, g, b))
    btn.pack(side=tk.LEFT, padx=3)

# 2. 启动主循环
root.mainloop()
