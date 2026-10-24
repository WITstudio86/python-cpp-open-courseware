# ============================================
# 第 9 课  长长的身体
# 小游戏：贪吃蛇
# 知识：列表当身体、每一节跟着走、吃食物变长、撞自己
# 操作：方向键转弯；吃到黄点身体 +1；撞墙或撞自己结束
#       R 重新开始
# ============================================

import turtle
import random

STEP = 20
screen = turtle.Screen()
screen.setup(600, 600)
screen.title("第 9 课 · 贪吃蛇")
screen.bgcolor("black")
screen.tracer(0)
alive = True
direction = 0
pending = None
snake = []
for i in range(3):
    s = turtle.Turtle()
    s.shape("square")
    if i == 0:
        s.color("lime")
    else:
        s.color("green")
    s.penup()
    s.goto(-i * STEP, 0)
    snake.append(s)
food = turtle.Turtle()
food.shape("circle")
food.color("yellow")
food.penup()
food.goto(80, 80)
hud = turtle.Turtle()
hud.hideturtle()
hud.penup()
hud.color("white")

def turn(heading):
    global pending
    if abs(heading - direction) == 180:
        return
    pending = heading
def turn_up():
    turn(90)
def turn_down():
    turn(270)
def turn_left():
    turn(180)
def turn_right():
    turn(0)
def place_food():
    while True:
        x = random.randint(-13, 13) * STEP
        y = random.randint(-13, 12) * STEP
        ok = True
        for seg in snake:
            if seg.distance(x, y) < 10:
                ok = False
                break
        if ok:
            food.goto(x, y)
            break
def grow():
    tail = turtle.Turtle()
    tail.shape("square")
    tail.color("green")
    tail.penup()
    last = snake[-1]
    tail.goto(last.xcor(), last.ycor())
    snake.append(tail)
def draw_hud():
    hud.clear()
    hud.goto(0, 260)
    hud.write(f"长度 {len(snake)}    方向键转向  ·  R 重开", align="center", font=("Arial", 16, "bold"))
def game_over():
    global alive
    alive = False
    hud.goto(0, 0)
    hud.write("游戏结束  按 R 再来一局", align="center", font=("Arial", 24, "bold"))
def restart():
    global alive, direction, pending
    alive = True
    direction = 0
    pending = None
    while len(snake) > 3:
        extra = snake.pop()
        extra.hideturtle()
    for i in range(3):
        snake[i].showturtle()
        snake[i].goto(-i * STEP, 0)
    snake[0].color("lime")
    place_food()
    hud.clear()
    tick()
def tick():
    global direction, pending
    if not alive:
        screen.update()
        return
    if pending is not None:
        direction = pending
        pending = None
    for i in range(len(snake) - 1, 0, -1):
        snake[i].goto(snake[i - 1].xcor(), snake[i - 1].ycor())
    head = snake[0]
    nx = head.xcor()
    ny = head.ycor()
    if direction == 0:
        nx = nx + STEP
    if direction == 180:
        nx = nx - STEP
    if direction == 90:
        ny = ny + STEP
    if direction == 270:
        ny = ny - STEP
    head.goto(nx, ny)
    head.setheading(direction)
    if abs(nx) > 280 or abs(ny) > 280:
        game_over()
        screen.update()
        return
    for seg in snake[1:]:
        if head.distance(seg) < 10:
            game_over()
            screen.update()
            return
    if head.distance(food) < 15:
        grow()
        place_food()
    draw_hud()
    screen.update()
    wait = 140 - len(snake) * 3
    if wait < 70:
        wait = 70
    screen.ontimer(tick, wait)

place_food()
draw_hud()
screen.listen()
screen.onkeypress(turn_up, "Up")
screen.onkeypress(turn_down, "Down")
screen.onkeypress(turn_left, "Left")
screen.onkeypress(turn_right, "Right")
screen.onkeypress(restart, "r")
screen.ontimer(tick, 140)
turtle.done()
