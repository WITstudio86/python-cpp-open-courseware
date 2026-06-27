"""
========================================
课程 43：项目五 —— Turtle 画城市
========================================
学习目标：
  1. 学会使用 Turtle 库画出各种图形
  2. 掌握用函数封装绘图逻辑（画房子、画树等）
  3. 理解 .goto() 坐标移动和 .penup() / .pendown()
  4. 综合运用颜色、填充、形状来创作完整的画面
========================================

注意：本程序需要在本地 Python 环境中运行。
     某些在线编程环境可能不完全支持 Turtle。
     程序最后会调用 turtle.done() 保持窗口不关闭。
"""

import turtle  # 导入海龟绘图库


# ── 初始化画布 ────────────────────────────────
def setup_screen():
    """设置画布大小和背景颜色"""
    turtle.setup(900, 600)  # 设置窗口大小（宽900，高600）
    turtle.bgcolor("#87CEEB")  # 背景色：天蓝色（Sky Blue）
    turtle.title("🏙️  我的城市 - My City")
    turtle.speed(0)  # 设置最快绘制速度
    turtle.hideturtle()  # 隐藏海龟图标，只显示图案


# ── 辅助函数 ──────────────────────────────────
def move_to(x, y):
    """移动海龟到指定坐标，不画线"""
    turtle.penup()  # 抬笔
    turtle.goto(x, y)  # 移动到 (x, y)
    turtle.pendown()  # 落笔


def draw_rectangle(width, height, color):
    """画一个填充颜色的矩形"""
    turtle.fillcolor(color)  # 设置填充颜色
    turtle.begin_fill()  # 开始填充

    for _ in range(2):  # 重复两次：画长边和短边
        turtle.forward(width)
        turtle.left(90)
        turtle.forward(height)
        turtle.left(90)

    turtle.end_fill()  # 结束填充


def draw_circle(radius, color):
    """画一个填充颜色的圆形"""
    turtle.fillcolor(color)
    turtle.begin_fill()
    turtle.circle(radius)
    turtle.end_fill()


# ── 画房子 ────────────────────────────────────
def draw_house(x, y, body_color="#FFD700", roof_color="#FF6347"):
    """
    在 (x, y) 位置画一栋房子
    参数：
        x, y: 房子左下角的坐标
        body_color: 墙体的颜色
        roof_color: 屋顶的颜色
    """
    move_to(x, y)

    # ─ 画墙体 ─
    draw_rectangle(80, 80, body_color)

    # ─ 画屋顶（三角形） ─
    move_to(x - 10, y + 80)
    turtle.fillcolor(roof_color)
    turtle.begin_fill()
    turtle.forward(100)  # 底边
    turtle.left(120)
    turtle.forward(100)  # 右边
    turtle.left(120)
    turtle.forward(100)  # 左边
    turtle.left(120)
    turtle.end_fill()

    # ─ 画门 ─
    move_to(x + 30, y)
    draw_rectangle(20, 35, "#8B4513")

    # ─ 画窗户 ─
    move_to(x + 10, y + 45)
    draw_rectangle(18, 18, "#ADD8E6")
    # 窗户十字
    turtle.pencolor("#333333")
    move_to(x + 19, y + 45)
    turtle.goto(x + 19, y + 63)
    move_to(x + 10, y + 54)
    turtle.goto(x + 28, y + 54)

    move_to(x + 52, y + 45)
    draw_rectangle(18, 18, "#ADD8E6")
    move_to(x + 61, y + 45)
    turtle.goto(x + 61, y + 63)
    move_to(x + 52, y + 54)
    turtle.goto(x + 70, y + 54)

    turtle.pencolor("black")  # 恢复画笔颜色


# ── 画树 ──────────────────────────────────────
def draw_tree(x, y):
    """
    在 (x, y) 位置画一棵树
    """
    # ─ 画树干 ─
    move_to(x + 10, y)
    draw_rectangle(15, 50, "#8B4513")

    # ─ 画树冠（三层圆形叠起来） ─
    move_to(x - 8, y + 30)
    draw_circle(25, "#228B22")  # 深绿色

    move_to(x - 5, y + 50)
    draw_circle(20, "#32CD32")  # 绿色

    move_to(x - 2, y + 65)
    draw_circle(15, "#3CB371")  # 海绿色


# ── 画太阳 ────────────────────────────────────
def draw_sun(x, y, radius=40):
    """
    在 (x, y) 位置画一个太阳
    （x, y 是太阳的中心位置）
    """
    move_to(x, y)
    draw_circle(radius, "#FFD700")  # 金色太阳

    # 画光芒（用短线条）
    turtle.pencolor("#FFA500")  # 橙色光芒
    turtle.pensize(3)

    for angle in range(0, 360, 30):  # 每30度画一道光芒
        move_to(x, y + radius)
        turtle.setheading(angle)  # 设置方向
        turtle.forward(radius + 5)  # 向外延伸
        move_to(x, y + radius)
        turtle.forward(radius + 15)
        move_to(x, y + radius)

    turtle.pencolor("black")  # 恢复画笔颜色
    turtle.pensize(1)  # 恢复画笔粗细


# ── 画云朵 ────────────────────────────────────
def draw_cloud(x, y, scale=1.0):
    """
    在 (x, y) 位置画一朵云
    云朵由几个圆形组成
    """
    move_to(x, y)
    turtle.fillcolor("white")  # 白色云朵
    turtle.pencolor("#E0E0E0")  # 浅灰边框

    # 画云朵的五个圆形
    circles = [
        (x, y, 20 * scale),          # 中间大圆
        (x - 20 * scale, y, 15 * scale),  # 左边圆
        (x + 20 * scale, y, 15 * scale),  # 右边圆
        (x - 10 * scale, y + 15 * scale, 12 * scale),  # 左上圆
        (x + 10 * scale, y + 15 * scale, 12 * scale),  # 右上圆
    ]

    turtle.begin_fill()
    for (cx, cy, r) in circles:
        move_to(cx, cy)
        turtle.circle(r)
    turtle.end_fill()

    turtle.pencolor("black")  # 恢复画笔颜色


# ── 画地面/草地 ──────────────────────────────
def draw_ground():
    """画底部的绿色草地"""
    move_to(-450, -180)
    turtle.fillcolor("#90EE90")  # 浅绿色草地
    turtle.begin_fill()
    draw_rectangle(900, 120, "#90EE90")
    turtle.end_fill()


# ── 画河流 ────────────────────────────────────
def draw_river():
    """画一条弯弯的河流"""
    move_to(-450, -120)
    turtle.fillcolor("#4A90D9")  # 蓝色河水
    turtle.pensize(1)
    turtle.begin_fill()

    # 用曲线画河流
    turtle.setheading(0)
    for _ in range(3):
        # 波浪形前进
        turtle.circle(30, 90)
        turtle.circle(-30, 90)
    turtle.forward(300)
    for _ in range(3):
        turtle.circle(-30, 90)
        turtle.circle(30, 90)

    turtle.right(90)
    turtle.forward(30)
    turtle.right(90)

    for _ in range(3):
        turtle.circle(30, 90)
        turtle.circle(-30, 90)
    turtle.forward(300)
    for _ in range(3):
        turtle.circle(-30, 90)
        turtle.circle(30, 90)

    turtle.end_fill()
    turtle.pensize(1)


# ── 画学校 ────────────────────────────────────
def draw_school(x, y):
    """在 (x, y) 位置画一所学校（比普通房子大一些）"""
    # 主楼体
    move_to(x, y)
    draw_rectangle(120, 90, "#F5DEB3")  # 小麦色墙体

    # 屋顶
    move_to(x - 10, y + 90)
    turtle.fillcolor("#B22222")  # 深红色屋顶
    turtle.begin_fill()
    turtle.forward(140)
    turtle.left(120)
    turtle.forward(140)
    turtle.left(120)
    turtle.forward(140)
    turtle.left(120)
    turtle.end_fill()

    # 大门
    move_to(x + 45, y)
    draw_rectangle(30, 45, "#8B4513")

    # 窗户
    for wx in [x + 10, x + 80]:
        move_to(wx, y + 50)
        draw_rectangle(20, 20, "#ADD8E6")

    # 旗杆 + 旗帜
    move_to(x + 105, y + 90)
    turtle.pencolor("#666")
    turtle.pensize(3)
    turtle.setheading(90)
    turtle.forward(40)
    # 小旗子
    turtle.fillcolor("red")
    turtle.begin_fill()
    turtle.forward(15)
    turtle.right(90)
    turtle.forward(10)
    turtle.right(90)
    turtle.forward(15)
    turtle.end_fill()
    turtle.pencolor("black")
    turtle.pensize(1)


# ── 画花朵 ────────────────────────────────────
def draw_flower(x, y):
    """在 (x, y) 位置画一朵小花"""
    # 花茎
    move_to(x + 3, y)
    turtle.pencolor("#228B22")
    turtle.pensize(2)
    turtle.setheading(90)
    turtle.forward(20)

    # 花瓣
    move_to(x, y + 15)
    turtle.pencolor("#FF69B4")
    for _ in range(5):  # 5片花瓣
        turtle.fillcolor("#FFB6C1")
        turtle.begin_fill()
        turtle.circle(5)
        turtle.end_fill()
        turtle.right(72)

    # 花蕊
    move_to(x + 1, y + 17)
    turtle.fillcolor("#FFD700")
    turtle.begin_fill()
    turtle.circle(3)
    turtle.end_fill()

    turtle.pencolor("black")
    turtle.pensize(1)


# ── 标题文字 ──────────────────────────────────
def draw_title():
    """在画面顶部写标题"""
    move_to(0, 240)
    turtle.pencolor("#333333")
    # 用 turtle.write() 写字
    turtle.write("🏙️  我的城市  🏙️",
                 align="center",
                 font=("Arial", 24, "bold"))


# ── 主绘制函数 ────────────────────────────────
def draw_city():
    """绘制整个城市的场景"""
    setup_screen()

    # 1. 画地面
    draw_ground()

    # 2. 画河流
    draw_river()

    # 3. 画太阳
    draw_sun(350, 150, 45)

    # 4. 画云朵
    draw_cloud(-250, 180, scale=1.2)
    draw_cloud(-50, 200, scale=1.0)
    draw_cloud(150, 190, scale=0.8)
    draw_cloud(300, 160, scale=0.7)

    # 5. 画房子
    draw_house(-350, -170, "#FFD700", "#FF6347")  # 黄色房子
    draw_house(-230, -170, "#87CEEB", "#4682B4")  # 蓝色房子
    draw_house(-110, -170, "#FFB6C1", "#FF1493")  # 粉色房子

    # 6. 画学校
    draw_school(70, -170)

    # 7. 画树
    draw_tree(-380, -170)
    draw_tree(-180, -170)
    draw_tree(50, -170)
    draw_tree(230, -170)
    draw_tree(320, -170)

    # 8. 画花朵（在房子前面）
    for fx in range(-340, 400, 40):
        draw_flower(fx, -175)

    # 9. 画标题
    draw_title()

    # 完成！保持窗口不关闭
    turtle.done()


# ── 程序入口 ──────────────────────────────────
if __name__ == "__main__":
    draw_city()


# ============================================================
# 练习题（试着修改代码来实现以下功能）：
# ============================================================
#
# 练习 1：添加更多建筑
#   试着添加 draw_hospital() 函数，画一所医院（红色十字标志）。
#   或者画一个超市、图书馆。每个建筑用不同颜色区分。
#   提示：参考 draw_house() 的写法，改变颜色和大小。
#
# 练习 2：添加更多自然元素
#   画一条弯弯的河流（已经在代码中实现了）。
#   再添加一些小鸟（V字形）、蝴蝶、或者山脉。
#   提示：小鸟可以用两个小角度线条画成 V 字形。
#
# 练习 3：让城市更有色彩
#   给不同的建筑使用不同的颜色，添加细节如烟囱、栅栏、
#   路灯等。让画面更加丰富多彩！
#   提示：用 turtle.pencolor() 和 turtle.fillcolor() 改变颜色。
#
# ============================================================
# 综合小挑战：
# ============================================================
#   打造一个"互动城市"：
#   - 让用户输入想在哪个位置建造什么建筑。
#   - 例如输入 "房子 100 200"，就在 (100, 200) 画一栋房子。
#   - 支持多种建筑类型：房子、学校、医院、公园等。
#   提示：用 input() 读取用户指令，解析坐标；
#   用 if-elif 判断建筑类型，调用对应的绘图函数。
# ============================================================
