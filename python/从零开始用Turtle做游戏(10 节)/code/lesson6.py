# ============================================
# 第 6 课  越来越难
# 小游戏：躲避陨石
# 知识：列表管理多个敌人、随机刷新、难度递增
# 操作：左右移动躲开从上往下砸的陨石
#       撑得越久分越高；撞到就结束，R 重开
# ============================================

import turtle
import random

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 6 课 · 躲避陨石")
screen.bgcolor("#120c18")
screen.tracer(0)

score = 0
alive = True
vx = 0
frames = 0

player = turtle.Turtle()
player.shape("turtle")
player.color("#5DADE2")
player.shapesize(1.4, 1.4)
player.penup()
player.goto(0, -230)
player.setheading(90)

meteors = []
for _ in range(6):
    m = turtle.Turtle()
    m.shape("circle")
    m.color("#E59866")
    m.penup()
    m.goto(random.randint(-360, 360), random.randint(80, 360))
    meteors.append(m)

hud = turtle.Turtle()
hud.hideturtle()
hud.penup()
hud.color("#F5CBA7")


def reset_meteor(m):
    m.goto(random.randint(-360, 360), random.randint(280, 420))


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
    hud.write(f"存活分 {score}    左右躲开陨石  ·  R 重开",
              align="center", font=("PingFang SC", 18, "bold"))


def restart():
    global score, alive, frames, vx
    score = 0
    frames = 0
    alive = True
    vx = 0
    player.goto(0, -230)
    for m in meteors:
        reset_meteor(m)
    hud.clear()
    tick()


def tick():
    global score, alive, frames
    if not alive:
        screen.update()
        return

    frames += 1
    if frames % 5 == 0:
        score += 1

    player.setx(max(-370, min(370, player.xcor() + vx)))

    # 分数越高，陨石掉得越快
    speed = 4 + score // 15
    for m in meteors:
        m.sety(m.ycor() - speed)
        m.left(4)
        if m.ycor() < -300:
            reset_meteor(m)
        if player.distance(m) < 24:
            alive = False
            draw_hud()
            hud.goto(0, 20)
            hud.write(f"被砸中了！最终分 {score}  按 R 再来",
                      align="center", font=("PingFang SC", 26, "bold"))
            screen.update()
            return

    draw_hud()
    screen.update()
    screen.ontimer(tick, 20)


draw_hud()
screen.listen()
screen.onkeypress(press_left, "Left")
screen.onkeypress(press_right, "Right")
screen.onkeyrelease(stop, "Left")
screen.onkeyrelease(stop, "Right")
screen.onkeypress(restart, "r")
screen.ontimer(tick, 20)
turtle.done()
