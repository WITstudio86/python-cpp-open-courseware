import tkinter as tk

# ========================================
# 第 15 节：几何图形画廊
# 知识点：Canvas 画布、坐标系统、
#         直线/矩形/椭圆/多边形/文字
# ========================================

# 创建主窗口
root = tk.Tk()
root.title("几何图形画廊")          # 窗口标题
root.geometry("550x500")            # 宽 550，高 500 像素

# ========== 创建画布 ==========
# Canvas 是 tkinter 的绘图控件
# 参数：宽 500 像素，高 400 像素，背景白色
canvas = tk.Canvas(root, width=500, height=400, bg="white")
canvas.pack(pady=20)  # 上下留 20px 间距

# ========== 1. 标题文字 ==========
# create_text(x, y, text="...", 参数...)
# (250, 25) → 画布中央偏上的位置
canvas.create_text(250, 25, text="🎨 几何图形画廊",
                   font=("微软雅黑", 22, "bold"), fill="darkblue")

# ========== 2. 画直线 ==========
# 灰色虚线：作为上方的分隔线
# create_line(x1, y1, x2, y2, ...)
# (30, 60) → (470, 60) 是一条水平线
canvas.create_line(30, 60, 470, 60, fill="gray", width=1, dash=(3, 5))

# 橘色加粗斜线
# (30, 60) → (250, 180) 是一条从左上到右下方的斜线
canvas.create_line(30, 60, 250, 180, fill="orange", width=4)

# 图形说明标签
canvas.create_text(50, 80, text="📏 直线",
                   font=("微软雅黑", 10), fill="gray", anchor="w")

# ========== 3. 画矩形 ==========
# create_rectangle(x1, y1, x2, y2, ...)
# (x1, y1) = 左上角，(x2, y2) = 右下角
# 这个矩形：左上角(30, 100)，右下角(130, 200)
# 宽 = 130 - 30 = 100，高 = 200 - 100 = 100
canvas.create_rectangle(30, 100, 130, 200,
                        fill="lightblue",      # 填充浅蓝色
                        outline="darkblue",    # 边框深蓝色
                        width=2)              # 边框粗细 2px

# 矩形下方的标签
canvas.create_text(80, 220, text="矩形",
                   font=("微软雅黑", 10), fill="gray")

# ========== 4. 画椭圆 ==========
# create_oval(x1, y1, x2, y2, ...)
# 椭圆画在"包围盒子"里，参数也是左上角和右下角
# 这个椭圆的包围盒子是长方形（宽 130，高 100），所以是椭圆
canvas.create_oval(170, 100, 300, 200,
                   fill="lightgreen",        # 填充浅绿色
                   outline="darkgreen",      # 边框深绿色
                   width=2)                 # 边框粗细 2px

canvas.create_text(235, 220, text="椭圆",
                   font=("微软雅黑", 10), fill="gray")

# ========== 5. 画正圆 ==========
# 要让椭圆变成正圆，包围盒子必须是正方形（宽 == 高）
# 这个包围盒子：宽 = 420-340 = 80，高 = 190-110 = 80 → 正方形 → 正圆！
canvas.create_oval(340, 110, 420, 190,
                   fill="pink",             # 填充粉色
                   outline="red",           # 边框红色
                   width=3)                # 边框加粗到 3px

canvas.create_text(380, 220, text="圆形",
                   font=("微软雅黑", 10), fill="gray")

# ========== 6. 画三角形（多边形） ==========
# create_polygon(x1, y1, x2, y2, x3, y3, ...)
# 给出所有顶点的坐标，Canvas 按顺序连接并自动闭合
# 三个顶点：
#   顶   (230, 280)
#   左下 (80,  380)
#   右下 (380, 380)
canvas.create_polygon(230, 280,     # 顶点 1：上方中央
                      80, 380,      # 顶点 2：左下方
                      380, 380,     # 顶点 3：右下方
                      fill="yellow",        # 填充黄色
                      outline="orange",     # 边框橙色
                      width=3)             # 边框粗细 3px

canvas.create_text(230, 400, text="三角形（多边形）",
                   font=("微软雅黑", 10), fill="gray")

# ========== 7. 坐标点标注 ==========
# 画小圆点标记关键坐标位置，帮助理解 Canvas 坐标系统
# 点 (30, 60)：直线的起点
canvas.create_oval(26, 56, 34, 64, fill="red")       # 画一个直径 8px 的小圆
canvas.create_text(45, 55, text="(30, 60)",
                   font=("微软雅黑", 8), fill="red", anchor="w")

# 点 (250, 180)：斜线的终点
canvas.create_oval(246, 176, 254, 184, fill="red")
canvas.create_text(260, 175, text="(250, 180)",
                   font=("微软雅黑", 8), fill="red", anchor="w")

# ========== 8. 底部说明文字 ==========
canvas.create_text(250, 390, text="💡 Canvas 坐标原点在左上角，X 向右增大，Y 向下增大",
                   font=("微软雅黑", 10), fill="#888888")

# 启动主循环（必须放在最后！）
root.mainloop()
