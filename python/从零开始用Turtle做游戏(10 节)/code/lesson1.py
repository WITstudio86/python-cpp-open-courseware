# ============================================
# 第 1 课  海龟登场
# 小游戏：彩虹点击画家
# 知识：Screen、Turtle、前进转弯、颜色、点击、盖章
# 操作：鼠标点击画面 → 盖一只彩色小海龟
#       空格换下一种颜色    C 清屏
# ============================================

import turtle
import random

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 1 课 · 彩虹点击画家")
screen.bgcolor("#0b1220")
screen.colormode(255)

# 调色盘：点一下换一种心情
PALETTE = [
    (255, 99, 132),
    (54, 162, 235),
    (255, 206, 86),
    (75, 192, 192),
    (153, 102, 255),
    (255, 159, 64),
    (46, 204, 113),
]
color_index = 0

# 画家海龟：抬笔，这样移动时不会拖出线
painter = turtle.Turtle()
painter.shape("turtle")
painter.shapesize(1.6, 1.6)
painter.speed(0)
painter.penup()
painter.color(PALETTE[0])

# 专门写字的海龟，hideturtle 后只留下文字
writer = turtle.Turtle()
writer.hideturtle()
writer.penup()
writer.color("#d0e6ff")
writer.goto(0, 250)
writer.write("点击画面盖章  ·  空格换色  ·  C 清屏",
             align="center", font=("PingFang SC", 18, "normal"))


def current_color():
    return PALETTE[color_index % len(PALETTE)]


def paint(x, y):
    """鼠标点哪里，海龟就走到哪里盖一个章。"""
    painter.goto(x, y)
    painter.setheading(random.randint(0, 360))
    painter.color(current_color())
    painter.stamp()


def next_color():
    global color_index
    color_index += 1
    painter.color(current_color())


def clear_canvas():
    painter.clear()


# 热身可以先自己在交互里试：
# painter.forward(100)
# painter.left(90)
# 连走 4 次就是正方形

screen.onscreenclick(paint)
screen.listen()
screen.onkeypress(next_color, "space")
screen.onkeypress(clear_canvas, "c")
turtle.done()
