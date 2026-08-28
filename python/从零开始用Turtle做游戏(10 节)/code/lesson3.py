# ============================================
# 第 3 课  点哪里打哪里
# 小游戏：打地鼠
# 知识：onscreenclick、随机坐标、计分、倒计时
# 操作：地鼠出现后尽快点中；30 秒结束
# ============================================

import turtle
import random

GAME_SECONDS = 30
screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 3 课 · 打地鼠")
screen.bgcolor("#1b140c")
screen.tracer(0)

score = 0
time_left = GAME_SECONDS
alive = True

# 地鼠
mole = turtle.Turtle()
mole.shape("turtle")
mole.color("#E67E22")
mole.shapesize(2.2, 2.2)
mole.penup()
mole.speed(0)

hud = turtle.Turtle()
hud.hideturtle()
hud.penup()
hud.color("#F8E9C8")

hint = turtle.Turtle()
hint.hideturtle()
hint.penup()
hint.color("#D4A574")
hint.goto(0, -260)
hint.write("点中橙色地鼠得分  ·  点空了不扣分  ·  30 秒挑战",
           align="center", font=("PingFang SC", 14, "normal"))


def jump_mole():
    if not alive:
        return
    x = random.randint(-320, 320)
    y = random.randint(-180, 180)
    mole.goto(x, y)
    mole.setheading(random.randint(0, 360))
    mole.showturtle()
    screen.update()


def draw_hud():
    hud.clear()
    hud.goto(0, 240)
    hud.write(f"得分 {score}    剩余 {time_left} 秒",
              align="center", font=("PingFang SC", 22, "bold"))
    screen.update()


def hit(x, y):
    global score
    if not alive:
        return
    # 点到地鼠附近 40 像素内算打中
    if mole.distance(x, y) < 40:
        score += 1
        mole.hideturtle()
        draw_hud()
        jump_mole()


def tick_timer():
    global time_left, alive
    if not alive:
        return
    time_left -= 1
    draw_hud()
    if time_left <= 0:
        alive = False
        mole.hideturtle()
        hud.goto(0, 40)
        hud.write(f"时间到！最终得分 {score}",
                  align="center", font=("PingFang SC", 28, "bold"))
        screen.update()
        return
    screen.ontimer(tick_timer, 1000)


def mole_wander():
    if not alive:
        return
    jump_mole()
    # 地鼠自己也会换洞，越往后越快一点点
    wait = max(500, 1400 - score * 80)
    screen.ontimer(mole_wander, wait)


draw_hud()
jump_mole()
screen.onscreenclick(hit)
screen.ontimer(tick_timer, 1000)
screen.ontimer(mole_wander, 1400)
screen.update()
turtle.done()
