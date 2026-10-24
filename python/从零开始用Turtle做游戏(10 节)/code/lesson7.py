# ============================================
# 第 7 课  发射！
# 小游戏：打气球
# 知识：列表里装子弹和气球、空格开火、打中删除
# 操作：左右移动，空格发射；打到气球得分
#       漏掉 8 个气球就结束
# ============================================

import turtle
import random

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 7 课 · 打气球")
screen.bgcolor("navy")
screen.tracer(0)
score = 0
missed = 0
alive = True
vx = 0
cool = 0
cannon = turtle.Turtle()
cannon.shape("triangle")
cannon.color("skyblue")
cannon.penup()
cannon.goto(0, -250)
cannon.setheading(90)
bullets = []
COLORS = ["red", "purple", "skyblue", "lime", "orange"]
balloons = []
for _ in range(5):
    b = turtle.Turtle()
    b.shape("circle")
    b.color(random.choice(COLORS))
    b.penup()
    b.goto(random.randint(-340, 340), random.randint(40, 260))
    balloons.append(b)
hud = turtle.Turtle()
hud.hideturtle()
hud.penup()
hud.color("white")

def make_bullet():
    shot = turtle.Turtle()
    shot.shape("square")
    shot.shapesize(0.4, 0.8)
    shot.color("yellow")
    shot.penup()
    shot.goto(cannon.xcor(), cannon.ycor() + 20)
    shot.setheading(90)
    bullets.append(shot)
def reset_balloon(b):
    b.color(random.choice(COLORS))
    b.goto(random.randint(-340, 340), random.randint(200, 320))
def press_left():
    global vx
    vx = -8
def press_right():
    global vx
    vx = 8
def stop():
    global vx
    vx = 0
def fire():
    global cool
    if alive and cool <= 0 and len(bullets) < 4:
        make_bullet()
        cool = 10
def draw_hud():
    hud.clear()
    hud.goto(0, 250)
    hud.write(f"打中 {score}    漏掉 {missed}/8    空格发射", align="center", font=("Arial", 18, "bold"))
def tick():
    global cool, score, missed, alive
    if not alive:
        screen.update()
        return
    if cool > 0:
        cool = cool - 1
    cannon.setx(cannon.xcor() + vx)
    if cannon.xcor() > 370:
        cannon.setx(370)
    if cannon.xcor() < -370:
        cannon.setx(-370)
    for shot in bullets[:]:
        shot.forward(12)
        if shot.ycor() > 300:
            shot.hideturtle()
            bullets.remove(shot)
    for balloon in balloons:
        balloon.sety(balloon.ycor() - (2 + score // 8))
        balloon.left(2)
        if balloon.ycor() < -280:
            missed = missed + 1
            reset_balloon(balloon)
            if missed >= 8:
                alive = False
                draw_hud()
                hud.goto(0, 20)
                hud.write("气球飘走太多了……", align="center", font=("Arial", 28, "bold"))
                screen.update()
                return
        for shot in bullets[:]:
            if balloon.distance(shot) < 22:
                score = score + 1
                shot.hideturtle()
                bullets.remove(shot)
                reset_balloon(balloon)
                break
    draw_hud()
    screen.update()
    screen.ontimer(tick, 20)

screen.listen()
screen.onkeypress(press_left, "Left")
screen.onkeypress(press_right, "Right")
screen.onkeyrelease(stop, "Left")
screen.onkeyrelease(stop, "Right")
screen.onkeypress(fire, "space")
screen.ontimer(tick, 20)
turtle.done()
