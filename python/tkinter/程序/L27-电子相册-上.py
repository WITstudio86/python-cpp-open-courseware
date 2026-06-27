import tkinter as tk
from PIL import Image, ImageTk, ImageDraw

# ========================================
# 第 27 节：项目 5 — 电子相册（上）
# 功能：加载并显示一张图片（使用占位图，不依赖外部文件）
# ========================================

# 1. 创建主窗口
root = tk.Tk()
root.title("电子相册 📸")
root.geometry("600x550")
root.configure(bg="#2c2c2c")  # 深灰色背景，模拟相册底色

# ========================================
# 2. 生成占位图片（不依赖真实图片文件）
# ========================================

# 创建一张 500x350 的纯色图片
# 模式 "RGB"、尺寸 (宽, 高)、颜色
img = Image.new("RGB", (500, 350), color="#3a6fb5")

# 用 ImageDraw 在图片上画装饰
draw = ImageDraw.Draw(img)

# 画白色外边框
draw.rectangle([8, 8, 491, 341], outline="white", width=2)

# 画两条横线（装饰）
draw.line([(40, 70), (460, 70)], fill="#ffffff", width=1)
draw.line([(40, 280), (460, 280)], fill="#ffffff", width=1)

# 写文字（PIL 的默认字体比较小，这里用较大的字号效果）
# 注意：Pillow 默认字体不支持中文，我们用英文 + emoji
draw.text((130, 110), "My Photo Album", fill="white")
draw.text((160, 160), "Photo #1", fill="#cccccc")
draw.text((180, 200), "Use real photos next time!", fill="#aaaaaa")

# ========================================
# 3. 转换成 tkinter 可用的格式
# ========================================

tk_img = ImageTk.PhotoImage(img)

# ========================================
# 4. 界面布局
# ========================================

# --- 标题标签 ---
title_label = tk.Label(
    root,
    text="📷 我的电子相册",
    font=("微软雅黑", 22, "bold"),
    fg="white",
    bg="#2c2c2c"
)
title_label.pack(pady=(20, 15))

# --- 图片显示区域 ---
# 用 Label 显示图片（Label 不仅能显示文字，也能显示图片）
img_label = tk.Label(root, image=tk_img, bg="#2c2c2c")
img_label.image = tk_img  # ⚠️ 必须保存引用！否则图片不会显示
img_label.pack(pady=10)

# --- 底部提示 ---
hint_label = tk.Label(
    root,
    text="💡 下节课我们加上翻页和自动播放功能！",
    font=("微软雅黑", 12),
    fg="#aaaaaa",
    bg="#2c2c2c"
)
hint_label.pack(pady=20)

# ========================================
# 5. 启动主循环
# ========================================

root.mainloop()
