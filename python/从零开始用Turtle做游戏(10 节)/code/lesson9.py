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
screen.bgcolor("#0e1a12")
screen.tracer(0)

alive = True
direction = 0  # 0 右  90 上  180 左  270 下
pending = None  # 缓冲下一次转弯，避免同一帧掉头

snake = []
for i in range(3):
    s = turtle.Turtle()
    s.shape("square")
    s.color("#58D68D" if i == 0 else "#1E8449")
    s.penup()
    s.goto(-i * STEP, 0)
    snake.append(s)

food = turtle.Turtle()
food.shape("circle")
food.color("#F4D03F")
food.penup()
food.goto(80, 80)

hud = turtle.Turtle()
hud.hideturtle()
hud.penup()
hud.color("#D5F5E3")


def grid_point():
    x = random.randint(-13, 13) * STEP
    y = random.randint(-13, 12) * STEP
    return x, y


def place_food():
    while True:
        x, y = grid_point()
        if any(seg.distance(x, y) < 10 for seg in snake):
            continue
        food.goto(x, y)
        break


def draw_hud():
    hud.clear()
    hud.goto(0, 260)
    hud.write(f"长度 {len(snake)}    方向键转向  ·  R 重开",
              align="center", font=("PingFang SC", 16, "bold"))


def turn(heading):
    global pending
    # 不能直接 180 度掉头
    if abs(heading - direction) == 180:
        return
    pending = heading


def grow():
    tail = turtle.Turtle()
    tail.shape("square")
    tail.color("#1E8449")
    tail.penup()
    last = snake[-1]
    tail.goto(last.xcor(), last.ycor())
    snake.append(tail)


def restart():
    global alive, direction, pending
    alive = True
    direction = 0
    pending = None
    while len(snake) > 3:
        extra = snake.pop()
        extra.hideturtle()
        extra.clear()
    for i, seg in enumerate(snake):
        seg.showturtle()
        seg.goto(-i * STEP, 0)
    snake[0].color("#58D68D")
    place_food()
    hud.clear()
    tick()


def game_over():
    global alive
    alive = False
    hud.goto(0, 0)
    hud.write("游戏结束  按 R 再来一局",
              align="center", font=("PingFang SC", 24, "bold"))


def tick():
    global direction, pending
    if not alive:
        screen.update()
        return

    if pending is not None:
        direction = pending
        pending = None

    head = snake[0]
    nx = head.xcor()
    ny = head.ycor()
    if direction == 0:
        nx += STEP
    elif direction == 180:
        nx -= STEP
    elif direction == 90:
        ny += STEP
    else:
        ny -= STEP

    # 从尾巴往前挪：每一节走到前一节刚才的位置
    for i in range(len(snake) - 1, 0, -1):
        snake[i].goto(snake[i - 1].xcor(), snake[i - 1].ycor())
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
    # 身体越长稍微越快
    wait = max(70, 140 - len(snake) * 3)
    screen.ontimer(tick, wait)


place_food()
draw_hud()
screen.listen()
screen.onkeypress(lambda: turn(90), "Up")
screen.onkeypress(lambda: turn(270), "Down")
screen.onkeypress(lambda: turn(180), "Left")
screen.onkeypress(lambda: turn(0), "Right")
screen.onkeypress(restart, "r")
screen.ontimer(tick, 140)
turtle.done()
