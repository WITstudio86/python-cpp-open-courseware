# ============================================
# 第 8 课  对打
# 小游戏：乒乓球大战
# 知识：挡板、反弹、双人键位、先到 5 分获胜
# 操作：左边 W / S，右边 上 / 下
# ============================================

import turtle

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 8 课 · 乒乓球大战")
screen.bgcolor("#0b1d2a")
screen.tracer(0)

left_score = 0
right_score = 0
alive = True
left_v = 0
right_v = 0


def make_paddle(x):
    p = turtle.Turtle()
    p.shape("square")
    p.color("#EAF2F8")
    p.shapesize(5, 0.8)
    p.penup()
    p.goto(x, 0)
    return p


left = make_paddle(-350)
right = make_paddle(350)

ball = turtle.Turtle()
ball.shape("circle")
ball.color("#F4D03F")
ball.penup()
ball.dx = 4
ball.dy = 3

hud = turtle.Turtle()
hud.hideturtle()
hud.penup()
hud.color("#D4E6F1")

# 中间虚线
mid = turtle.Turtle()
mid.hideturtle()
mid.color("#1F618D")
mid.penup()
mid.goto(0, 260)
mid.setheading(270)
mid.pensize(2)
for _ in range(18):
    mid.pendown()
    mid.forward(14)
    mid.penup()
    mid.forward(14)


def draw_hud():
    hud.clear()
    hud.goto(0, 250)
    hud.write(f"{left_score}    先到 5 分    {right_score}",
              align="center", font=("PingFang SC", 22, "bold"))


def reset_ball(direction):
    ball.goto(0, 0)
    ball.dx = 4 * direction
    ball.dy = 3 if direction > 0 else -3


def finish(winner):
    global alive
    alive = False
    hud.goto(0, 20)
    hud.write(winner, align="center", font=("PingFang SC", 28, "bold"))


def tick():
    global left_score, right_score
    if not alive:
        screen.update()
        return

    left.sety(max(-230, min(230, left.ycor() + left_v)))
    right.sety(max(-230, min(230, right.ycor() + right_v)))

    ball.setx(ball.xcor() + ball.dx)
    ball.sety(ball.ycor() + ball.dy)

    # 上下墙壁反弹
    if ball.ycor() > 280:
        ball.sety(280)
        ball.dy *= -1
    if ball.ycor() < -280:
        ball.sety(-280)
        ball.dy *= -1

    # 挡板反弹：打到后稍微加速
    if ball.xcor() < -330 and left.distance(ball) < 70:
        ball.setx(-330)
        ball.dx = abs(ball.dx) + 0.3
    if ball.xcor() > 330 and right.distance(ball) < 70:
        ball.setx(330)
        ball.dx = -(abs(ball.dx) + 0.3)

    if ball.xcor() < -390:
        right_score += 1
        reset_ball(1)
        if right_score >= 5:
            draw_hud()
            finish("右边获胜！")
            screen.update()
            return
    if ball.xcor() > 390:
        left_score += 1
        reset_ball(-1)
        if left_score >= 5:
            draw_hud()
            finish("左边获胜！")
            screen.update()
            return

    draw_hud()
    screen.update()
    screen.ontimer(tick, 16)


def lv(v):
    def inner():
        global left_v
        left_v = v
    return inner


def rv(v):
    def inner():
        global right_v
        right_v = v
    return inner


draw_hud()
screen.listen()
screen.onkeypress(lv(7), "w")
screen.onkeypress(lv(-7), "s")
screen.onkeyrelease(lv(0), "w")
screen.onkeyrelease(lv(0), "s")
screen.onkeypress(rv(7), "Up")
screen.onkeypress(rv(-7), "Down")
screen.onkeyrelease(rv(0), "Up")
screen.onkeyrelease(rv(0), "Down")
screen.ontimer(tick, 16)
turtle.done()
