# ============================================
# 第 5 课  碰一碰
# 小游戏：星星收集者
# 知识：distance 碰撞、多种角色、胜负判定
# 操作：方向键移动；吃到星星 +1；碰到石头就结束
#       吃满 10 颗星星获胜
# ============================================

import turtle
import random

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 5 课 · 星星收集者")
screen.bgcolor("#0d1b2a")
screen.tracer(0)
score = 0
alive = True
vx = 0
vy = 0
player = turtle.Turtle()
player.shape("turtle")
player.color("green")
player.shapesize(1.5, 1.5)
player.penup()
player.goto(0, 0)
star = turtle.Turtle()
star.shape("triangle")
star.color("yellow")
star.penup()
star.goto(180, 120)
rocks = []
for _ in range(4):
    rock = turtle.Turtle()
    rock.shape("circle")
    rock.color("red")
    rock.penup()
    while True:
        rock.goto(random.randint(-320, 320), random.randint(-200, 200))
        if rock.distance(player) > 80:
            break
    rocks.append(rock)
hud = turtle.Turtle()
hud.hideturtle()
hud.penup()
hud.color("white")

def press_left():
    global vx
    vx = -6
def press_right():
    global vx
    vx = 6
def press_up():
    global vy
    vy = 6
def press_down():
    global vy
    vy = -6
def stop_x():
    global vx
    vx = 0
def stop_y():
    global vy
    vy = 0
def place_star():
    while True:
        x = random.randint(-330, 330)
        y = random.randint(-220, 200)
        star.goto(x, y)
        if star.distance(player) > 60:
            break
def draw_hud():
    hud.clear()
    hud.goto(0, 250)
    d = int(player.distance(star))
    hud.write(f"星星 {score} / 10    距离 {d}", align="center", font=("Arial", 20, "bold"))
def finish(msg):
    global alive
    alive = False
    hud.goto(0, 30)
    hud.write(msg, align="center", font=("Arial", 28, "bold"))
def tick():
    global score
    if not alive:
        screen.update()
        return
    player.setx(player.xcor() + vx)
    player.sety(player.ycor() + vy)
    if player.xcor() > 370:
        player.setx(370)
    if player.xcor() < -370:
        player.setx(-370)
    if player.ycor() > 250:
        player.sety(250)
    if player.ycor() < -270:
        player.sety(-270)
    if player.distance(star) < 28:
        score += 1
        place_star()
        if score >= 10:
            draw_hud()
            finish("收集完成！你赢了")
            screen.update()
            return
    for rock in rocks:
        if player.distance(rock) < 26:
            finish("撞到石头了")
            screen.update()
            return
    draw_hud()
    screen.update()
    screen.ontimer(tick, 20)

place_star()
screen.listen()
screen.onkeypress(press_left, "Left")
screen.onkeyrelease(stop_x, "Left")
screen.onkeypress(press_right, "Right")
screen.onkeyrelease(stop_x, "Right")
screen.onkeypress(press_up, "Up")
screen.onkeyrelease(stop_y, "Up")
screen.onkeypress(press_down, "Down")
screen.onkeyrelease(stop_y, "Down")
screen.ontimer(tick, 20)
turtle.done()
