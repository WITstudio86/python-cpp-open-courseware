#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""第 9 课跟打数据。"""
from __future__ import annotations

from followalong_engine import write_outputs

HEADER = """\
# ============================================
# 第 9 课  长长的身体
# 小游戏：贪吃蛇
# 知识：列表当身体、每一节跟着走、吃食物变长、撞自己
# 操作：方向键转弯；吃到黄点身体 +1；撞墙或撞自己结束
#       R 重新开始
# ============================================

"""

STEP1 = """\
import turtle
import random

STEP = 20
screen = turtle.Screen()
screen.setup(600, 600)
screen.title("第 9 课 · 贪吃蛇")
screen.bgcolor("black")
screen.tracer(0)
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

def tick():
    for i in range(len(snake) - 1, 0, -1):
        snake[i].goto(snake[i - 1].xcor(), snake[i - 1].ycor())
    head = snake[0]
    head.setx(head.xcor() + STEP)
    screen.update()
    screen.ontimer(tick, 140)

screen.ontimer(tick, 140)
turtle.done()
"""

STEP2 = """\
import turtle
import random

STEP = 20
screen = turtle.Screen()
screen.setup(600, 600)
screen.title("第 9 课 · 贪吃蛇")
screen.bgcolor("black")
screen.tracer(0)
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
def tick():
    global direction, pending
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
    screen.update()
    screen.ontimer(tick, 140)

screen.listen()
screen.onkeypress(turn_up, "Up")
screen.onkeypress(turn_down, "Down")
screen.onkeypress(turn_left, "Left")
screen.onkeypress(turn_right, "Right")
screen.ontimer(tick, 140)
turtle.done()
"""

STEP3 = """\
import turtle
import random

STEP = 20
screen = turtle.Screen()
screen.setup(600, 600)
screen.title("第 9 课 · 贪吃蛇")
screen.bgcolor("black")
screen.tracer(0)
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
def tick():
    global direction, pending
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
    if head.distance(food) < 15:
        grow()
        place_food()
    screen.update()
    screen.ontimer(tick, 140)

place_food()
screen.listen()
screen.onkeypress(turn_up, "Up")
screen.onkeypress(turn_down, "Down")
screen.onkeypress(turn_left, "Left")
screen.onkeypress(turn_right, "Right")
screen.ontimer(tick, 140)
turtle.done()
"""

STEP4 = """\
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
def game_over():
    global alive
    alive = False
    hud.goto(0, 0)
    hud.write("游戏结束", align="center", font=("Arial", 24, "bold"))
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
    screen.update()
    screen.ontimer(tick, 140)

place_food()
screen.listen()
screen.onkeypress(turn_up, "Up")
screen.onkeypress(turn_down, "Down")
screen.onkeypress(turn_left, "Left")
screen.onkeypress(turn_right, "Right")
screen.ontimer(tick, 140)
turtle.done()
"""

STEP5 = """\
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
"""

CHALLENGE = STEP5.replace(
    """    if abs(nx) > 280 or abs(ny) > 280:
        game_over()
        screen.update()
        return""",
    """    if abs(nx) > 280:
        nx = -nx
        head.setx(nx)
    if abs(ny) > 280:
        ny = -ny
        head.sety(ny)""",
)

STEPS = [
    {
        "n": 1,
        "title": "三节跟着走",
        "goal": "三节方块排成一排，从尾巴往头抄坐标，整条往右爬。",
        "why": "后一节走到前一节刚才的位置。从头往后抄，整条蛇会叠在一起。",
        "where": [
            "STEP=20，窗口 600×600",
            "循环 3 次造身体，头是绿色更亮",
            "tick 里倒序 for，然后头 x + 20",
        ],
        "see": "一条三节的蛇往右爬，会爬出窗口。这时还不能转弯。",
        "pitfall": "for 写成 range(len(snake)) 从头抄，三节叠成一团。",
        "talk_note": "这就是热身。在黑板上画 3 格演示倒序。大约 10 分钟。",
        "type_note": "range(len(snake)-1, 0, -1) 一起抄，读出声：从尾巴往前。",
        "type_hint": "for i in range(len(snake)-1, 0, -1) 抄前一节的坐标。头再往右走一格。",
        "code": STEP1,
    },
    {
        "n": 2,
        "title": "方向键转弯",
        "goal": "方向键改变方向。不能立刻 180 度掉头。",
        "why": "掉头会立刻撞上第二节。abs(新-旧)==180 就忽略。pending 记下这一格的转向，下一格再生效。",
        "where": [
            "加 direction=0 和 pending=None",
            "turn + 四个 turn_up 等小函数",
            "tick 开头把 pending 写进 direction，再按方向走",
        ],
        "see": "方向键能转弯。对着身子按反方向，蛇不会掉头。",
        "pitfall": "允许 180 掉头，一按就撞自己。",
        "talk_note": "四个转向函数让学生改数字。大约 10 分钟。",
        "type_note": "不要用 lambda。turn_up 就是 turn(90)。",
        "type_hint": "差 180 度就 return。四个小函数调用 turn。tick 里先处理 pending。",
        "code": STEP2,
    },
    {
        "n": 3,
        "title": "吃食物变长",
        "goal": "吃到黄点：身体 +1，食物换到空地。",
        "why": "食物刷在身上会一帧连吃。while True 随机，直到每一节都离得远。grow 出生在旧尾巴处。",
        "where": [
            "加 food、place_food、grow",
            "tick 里 distance < 15 就 grow + place_food",
            "启动时调用一次 place_food()",
        ],
        "see": "吃黄点身体变长。食物不会刷在蛇身上。",
        "pitfall": "place_food 不用循环避开身体，偶尔会连吃。",
        "talk_note": "网格 STEP=20，食物坐标也是 20 的倍数。大约 10 分钟。",
        "type_note": "ok 标志 + for 循环，不要写 any()。",
        "type_hint": "place_food 用 for 检查每一节。吃到就 grow() 再换位置。",
        "code": STEP3,
    },
    {
        "n": 4,
        "title": "撞墙或自己就结束",
        "goal": "头出界或碰到身体，写出「游戏结束」。",
        "why": "自撞从 snake[1:] 查，不要把头和自己比。alive 关掉后 tick 开头 return。",
        "where": [
            "加 alive、hud、game_over",
            "出界 abs(nx)>280 或 abs(ny)>280",
            "for seg in snake[1:] 测距离",
        ],
        "see": "撞墙或咬到自己，中间出现「游戏结束」，蛇不再动。",
        "pitfall": "自撞写成 for seg in snake，头和自己距离是 0，一运行就死。",
        "talk_note": "让学生故意撞墙一次、绕圈咬自己一次。大约 8 分钟。",
        "type_note": "结束要 return。",
        "type_hint": "出界或碰到 snake[1:] 就 game_over 并 return。不要把头算进身体。",
        "code": STEP4,
    },
    {
        "n": 5,
        "title": "按 R 再来一局",
        "goal": "结束后按 R 回到 3 节；身体越长稍微越快。",
        "why": "多出来的节 pop 并 hideturtle。前 3 节回到起点。速度 140-长度*3，最快 70。",
        "where": [
            "加 draw_hud、restart",
            "绑小写 r",
            "tick 末尾用 wait 再约自己",
        ],
        "see": "头顶显示长度。死后按 R 重新开始。越长爬得越快。",
        "pitfall": "restart 只把 alive 改回 True，身体还是那么长。",
        "talk_note": "这是过关线。让全班死一次再重开。大约 8 分钟。",
        "type_note": "while len(snake)>3: pop。键名小写 r。",
        "type_hint": "restart 把多余的节藏掉，前 3 节回起点，再 tick()。",
        "code": STEP5,
    },
]

LESSON = {
    "n": 9,
    "title": "长长的身体",
    "icon": "🐍",
    "project": "贪吃蛇",
    "header": HEADER,
    "final": STEP5,
    "io": "方向键转弯。\n吃黄点身体 +1。\n撞墙或撞自己结束，R 重开。越长稍微越快。",
    "pass_line": "能转弯吃食物变长，撞墙或自己会结束。",
    "start_cards": [
        ("1. 新建文件", "保存为 <span class=\"ic\">lesson9.py</span>。今天从头写到尾，只用这一份。"),
        ("2. 带着第 6～8 课", "列表管身体。<span class=\"ic\">direction</span> 0/90/180/270 和第 2 课一样。"),
        ("3. 每一步都要运行", "打完这一步就点运行。跑通再翻下一步。"),
    ],
    "cover_note": "今天列表变成身体。翻一页，打一段，运行一次。",
    "product_note": "先演示贪吃蛇 20 秒，再让学生关窗口、打开空文件。",
    "start_note": "口答：乒乓球反弹为什么要先拉回。有人还在 lesson8.py 里接着写，让他新建。",
    "map_note": "第 1 步倒序是核心。掉队的人停在当前步。",
    "errors": [
        ("从头往后抄坐标", "从尾巴往前", "否则叠成一团"),
        ("允许 180 掉头", "差 180 就 return", "立刻自撞"),
        ("食物刷在身上", "随机直到空地", "一帧连吃"),
    ],
    "errors_note": "叠成一团一定是抄错方向。一运行就死，查自撞有没有包含头。",
    "challenge_code": CHALLENGE,
    "challenge_must_contain": "nx = -nx",
    "challenge_title": "穿墙模式",
    "challenge_lede": "主游戏能玩之后：出界不要 game_over，把 nx 改成 -nx。",
    "challenge_see": "从右边出去会从左边出来。咬自己仍会结束。",
    "challenge_note": "穿墙后仍要查自撞。",
    "ex": [
        ("更长开局", "初始 5 节"),
        ("更大格", "STEP=25"),
        ("三角食物", 'food.shape("triangle")'),
        ("更慢", "ontimer 改 180"),
    ],
    "ex_note": "改数字最适合这个时间点。",
    "sum_rows": [
        ("列表身体", "[0] 是头", "append 变长"),
        ("倒序跟随", "尾巴→头", "本课核心"),
        ("死亡", "撞墙/自己", "R 重开"),
    ],
    "sum_note": "抽人到黑板演示倒序抄坐标。预告第 10 课毕业作。",
    "next_line": "第 10 课：状态机毕业作 — 太空大战",
    "next_short": "完整作品 — 太空大战",
    "print_know": [
        ("身体=列表", "每节一只 Turtle", "snake[0] 是头"),
        ("跟着走", "从尾巴往前抄坐标", "千万别从头抄"),
        ("不能掉头", "差 180 度忽略", "否则立刻撞自己"),
        ("网格", "一格 20 像素", "坐标对齐更好吃"),
        ("自撞", "头和身体 distance", "从 snake[1:] 查"),
    ],
    "print_blanks": [
        "1. 蛇头是 snake 的下标 ________",
        "2. 移动时 for 必须从 ________ 往前抄",
        "3. 禁止 ________ 度掉头",
        "4. 食物刷在蛇身上会 ________（连吃 / 没影响）",
        "5. 本课一格是 ________ 像素",
        "6. 吃到食物调用 ________ 让身体变长",
    ],
    "print_challenge": "主游戏能玩之后，出界把 <span class=\"mono\">nx = -nx</span>，不要 game_over。",
    "print_times": [
        ("0–8", "看成品，新建 lesson9.py"),
        ("8–35", "第 1～3 步（跟着走、转弯、吃）"),
        ("35–65", "第 4～5 步（死亡、R 重开）"),
        ("65–82", "加码：穿墙（选做）"),
        ("82–90", "改错 + 填空 + 小结"),
    ],
    "steps": STEPS,
}

if __name__ == "__main__":
    write_outputs(LESSON)
