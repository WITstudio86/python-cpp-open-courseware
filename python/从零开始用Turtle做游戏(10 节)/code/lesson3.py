# ============================================
# 第 3 课  点哪里打哪里
# 小游戏：打地鼠
# 知识：onscreenclick、随机坐标、计分、倒计时
# 操作：地鼠出现后尽快点中；30 秒结束
# ============================================

import turtle
import random

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 3 课 · 打地鼠")
screen.bgcolor("saddlebrown")
screen.tracer(0)
score = 0
time_left = 30
alive = True
mole = turtle.Turtle()
mole.shape("turtle")
mole.color("orange")
mole.shapesize(2.2, 2.2)
mole.penup()
hud = turtle.Turtle()
hud.hideturtle()
hud.penup()
hud.color("white")

def jump_mole():
    if not alive:
        return
    x = random.randint(-320, 320)
    y = random.randint(-180, 180)
    mole.goto(x, y)
    mole.showturtle()
    screen.update()
def draw_hud():
    hud.clear()
    hud.goto(0, 240)
    hud.write(f"得分 {score}    剩余 {time_left} 秒", align="center", font=("Arial", 22, "bold"))
    screen.update()
def hit(x, y):
    global score
    if not alive:
        return
    if mole.distance(x, y) < 40:
        score = score + 1
        mole.hideturtle()
        draw_hud()
        jump_mole()
def tick_timer():
    global time_left, alive
    if not alive:
        return
    time_left = time_left - 1
    draw_hud()
    if time_left <= 0:
        alive = False
        mole.hideturtle()
        hud.goto(0, 40)
        hud.write(f"时间到！最终得分 {score}", align="center", font=("Arial", 28, "bold"))
        screen.update()
        return
    screen.ontimer(tick_timer, 1000)
def mole_wander():
    if not alive:
        return
    jump_mole()
    screen.ontimer(mole_wander, 1400)

draw_hud()
jump_mole()
screen.onscreenclick(hit)
screen.ontimer(tick_timer, 1000)
screen.ontimer(mole_wander, 1400)
turtle.done()
