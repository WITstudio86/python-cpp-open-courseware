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
keys = {"Up": False, "Down": False, "Left": False, "Right": False}

player = turtle.Turtle()
player.shape("turtle")
player.color("#48C9B0")
player.shapesize(1.5, 1.5)
player.penup()
player.goto(0, 0)

star = turtle.Turtle()
star.shape("triangle")
star.color("#F7DC6F")
star.penup()
star.goto(180, 120)

rocks = []
for _ in range(4):
    rock = turtle.Turtle()
    rock.shape("circle")
    rock.color("#E74C3C")
    rock.penup()
    rock.goto(random.randint(-320, 320), random.randint(-200, 200))
    rocks.append(rock)

hud = turtle.Turtle()
hud.hideturtle()
hud.penup()
hud.color("#D6EAF8")


def place_star():
    while True:
        x = random.randint(-330, 330)
        y = random.randint(-220, 200)
        star.goto(x, y)
        # 不要刷在玩家或石头身上
        if star.distance(player) < 60:
            continue
        if any(star.distance(r) < 50 for r in rocks):
            continue
        break


def press(name):
    def inner():
        keys[name] = True
    return inner


def release(name):
    def inner():
        keys[name] = False
    return inner


def draw_hud():
    hud.clear()
    hud.goto(0, 250)
    hud.write(f"星星 {score} / 10    躲开红色石头",
              align="center", font=("PingFang SC", 20, "bold"))


def finish(msg):
    global alive
    alive = False
    hud.goto(0, 30)
    hud.write(msg, align="center", font=("PingFang SC", 28, "bold"))


def tick():
    global score
    if not alive:
        screen.update()
        return

    if keys["Left"]:
        player.setheading(180)
        player.forward(6)
    if keys["Right"]:
        player.setheading(0)
        player.forward(6)
    if keys["Up"]:
        player.setheading(90)
        player.forward(6)
    if keys["Down"]:
        player.setheading(270)
        player.forward(6)

    # 不出界
    player.setx(max(-370, min(370, player.xcor())))
    player.sety(max(-270, min(250, player.ycor())))

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
            finish("撞到石头了……")
            screen.update()
            return

    draw_hud()
    screen.update()
    screen.ontimer(tick, 20)


place_star()
draw_hud()
screen.listen()
for k in keys:
    screen.onkeypress(press(k), k)
    screen.onkeyrelease(release(k), k)
screen.ontimer(tick, 20)
turtle.done()
