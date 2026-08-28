# ============================================
# 第 4 课  让画面自己动
# 小游戏：接住金币
# 知识：ontimer 游戏循环、下落、左右移动
# 操作：左右方向键移动篮子，接住掉下来的金币
# ============================================

import turtle
import random

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 4 课 · 接住金币")
screen.bgcolor("#101828")
screen.tracer(0)

score = 0
missed = 0
alive = True
vx = 0  # 篮子水平速度

basket = turtle.Turtle()
basket.shape("square")
basket.color("#F4D03F")
basket.shapesize(1, 5)
basket.penup()
basket.goto(0, -240)

coin = turtle.Turtle()
coin.shape("circle")
coin.color("#F7DC6F")
coin.penup()
coin.goto(random.randint(-340, 340), 260)

hud = turtle.Turtle()
hud.hideturtle()
hud.penup()
hud.color("#F8E9C8")


def reset_coin():
    coin.goto(random.randint(-340, 340), 280)


def press_left():
    global vx
    vx = -8


def press_right():
    global vx
    vx = 8


def stop():
    global vx
    vx = 0


def draw_hud():
    hud.clear()
    hud.goto(0, 250)
    hud.write(f"接到 {score}    漏掉 {missed}/8",
              align="center", font=("PingFang SC", 20, "bold"))


def game_over(msg):
    global alive
    alive = False
    hud.goto(0, 20)
    hud.write(msg, align="center", font=("PingFang SC", 28, "bold"))


def tick():
    global score, missed
    if not alive:
        screen.update()
        return

    # 篮子移动，并限制在窗口里
    basket.setx(basket.xcor() + vx)
    if basket.xcor() > 350:
        basket.setx(350)
    if basket.xcor() < -350:
        basket.setx(-350)

    # 金币往下落；接到越多掉得越快
    coin.sety(coin.ycor() - (5 + score // 3))

    if coin.ycor() < -280:
        missed += 1
        reset_coin()
        if missed >= 8:
            draw_hud()
            game_over("金币漏光了……再开一局试试")
            screen.update()
            return

    if coin.ycor() < -210 and basket.distance(coin) < 70:
        score += 1
        reset_coin()

    draw_hud()
    screen.update()
    screen.ontimer(tick, 20)


draw_hud()
screen.listen()
screen.onkeypress(press_left, "Left")
screen.onkeypress(press_right, "Right")
screen.onkeyrelease(stop, "Left")
screen.onkeyrelease(stop, "Right")
screen.ontimer(tick, 20)
turtle.done()
