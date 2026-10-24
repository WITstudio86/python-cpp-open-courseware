# ============================================
# 第 1 课  海龟登场
# 小游戏：彩虹点击画家
# 知识：Screen、Turtle、前进转弯、盖章、点击
# 操作：鼠标点击画面 → 盖一只彩色小海龟
#       空格换下一种颜色    C 清屏
# ============================================

import turtle
import random

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 1 课 · 彩虹点击画家")
screen.bgcolor("navy")
PALETTE = ["red", "orange", "yellow", "lime", "cyan", "violet"]
color_index = 0
painter = turtle.Turtle()
painter.shape("turtle")
painter.color(PALETTE[0])
painter.penup()
hud = turtle.Turtle()
hud.hideturtle()
hud.penup()
hud.color("white")
hud.goto(0, 250)
hud.write("点击盖章  ·  空格换色  ·  C 清屏", align="center", font=("Arial", 18, "normal"))

def paint(x, y):
    painter.goto(x, y)
    painter.setheading(random.randint(0, 360))
    painter.stamp()

def next_color():
    global color_index
    color_index = color_index + 1
    painter.color(PALETTE[color_index % len(PALETTE)])

def clear_canvas():
    painter.clear()

screen.onscreenclick(paint)
screen.listen()
screen.onkeypress(next_color, "space")
screen.onkeypress(clear_canvas, "c")
turtle.done()
