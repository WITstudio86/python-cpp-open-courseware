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
screen.bgcolor("navy")
screen.tracer(0)
left_score = 0
right_score = 0
alive = True
left_v = 0
right_v = 0
left = turtle.Turtle()
left.shape("square")
left.color("white")
left.shapesize(5, 0.8)
left.penup()
left.goto(-350, 0)
right = turtle.Turtle()
right.shape("square")
right.color("white")
right.shapesize(5, 0.8)
right.penup()
right.goto(350, 0)
ball = turtle.Turtle()
ball.shape("circle")
ball.color("yellow")
ball.penup()
ball_dx = 4
ball_dy = 3
hud = turtle.Turtle()
hud.hideturtle()
hud.penup()
hud.color("white")

def press_w():
    global left_v
    left_v = 7
def stop_w():
    global left_v
    left_v = 0
def press_s():
    global left_v
    left_v = -7
def stop_s():
    global left_v
    left_v = 0
def press_up():
    global right_v
    right_v = 7
def stop_up():
    global right_v
    right_v = 0
def press_down():
    global right_v
    right_v = -7
def stop_down():
    global right_v
    right_v = 0
def draw_hud():
    hud.clear()
    hud.goto(0, 250)
    hud.write(f"{left_score}    先到 5 分    {right_score}", align="center", font=("Arial", 22, "bold"))
def reset_ball(direction):
    global ball_dx, ball_dy
    ball.goto(0, 0)
    ball_dx = 4 * direction
    ball_dy = 3
def finish(winner):
    global alive
    alive = False
    hud.goto(0, 20)
    hud.write(winner, align="center", font=("Arial", 28, "bold"))
def tick():
    global ball_dx, ball_dy, left_score, right_score
    if not alive:
        screen.update()
        return
    left.sety(left.ycor() + left_v)
    if left.ycor() > 230:
        left.sety(230)
    if left.ycor() < -230:
        left.sety(-230)
    right.sety(right.ycor() + right_v)
    if right.ycor() > 230:
        right.sety(230)
    if right.ycor() < -230:
        right.sety(-230)
    ball.setx(ball.xcor() + ball_dx)
    ball.sety(ball.ycor() + ball_dy)
    if ball.ycor() > 280:
        ball.sety(280)
        ball_dy = ball_dy * -1
    if ball.ycor() < -280:
        ball.sety(-280)
        ball_dy = ball_dy * -1
    if ball.xcor() < -330 and left.distance(ball) < 70:
        ball.setx(-330)
        ball_dx = abs(ball_dx) + 0.3
    if ball.xcor() > 330 and right.distance(ball) < 70:
        ball.setx(330)
        ball_dx = -(abs(ball_dx) + 0.3)
    if ball.xcor() < -390:
        right_score = right_score + 1
        reset_ball(1)
        if right_score >= 5:
            draw_hud()
            finish("右边获胜！")
            screen.update()
            return
    if ball.xcor() > 390:
        left_score = left_score + 1
        reset_ball(-1)
        if left_score >= 5:
            draw_hud()
            finish("左边获胜！")
            screen.update()
            return
    draw_hud()
    screen.update()
    screen.ontimer(tick, 16)

screen.listen()
screen.onkeypress(press_w, "w")
screen.onkeyrelease(stop_w, "w")
screen.onkeypress(press_s, "s")
screen.onkeyrelease(stop_s, "s")
screen.onkeypress(press_up, "Up")
screen.onkeyrelease(stop_up, "Up")
screen.onkeypress(press_down, "Down")
screen.onkeyrelease(stop_down, "Down")
screen.ontimer(tick, 16)
turtle.done()
