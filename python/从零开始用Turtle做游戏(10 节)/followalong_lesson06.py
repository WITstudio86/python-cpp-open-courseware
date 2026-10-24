#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""第 6 课跟打数据。"""
from __future__ import annotations

from followalong_engine import write_outputs

HEADER = """\
# ============================================
# 第 6 课  越来越难
# 小游戏：躲避陨石
# 知识：列表管多个敌人、随机刷新、难度递增
# 操作：左右移动躲开从上往下砸的陨石
#       撑得越久分越高；撞到就结束，R 重开
# ============================================

"""

STEP1 = """\
import turtle
import random

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 6 课 · 躲避陨石")
screen.bgcolor("black")
screen.tracer(0)
vx = 0
player = turtle.Turtle()
player.shape("turtle")
player.color("deepskyblue")
player.shapesize(1.4, 1.4)
player.penup()
player.goto(0, -230)
player.setheading(90)

def press_left():
    global vx
    vx = -8
def press_right():
    global vx
    vx = 8
def stop():
    global vx
    vx = 0
def tick():
    player.setx(player.xcor() + vx)
    if player.xcor() > 370:
        player.setx(370)
    if player.xcor() < -370:
        player.setx(-370)
    screen.update()
    screen.ontimer(tick, 20)

screen.listen()
screen.onkeypress(press_left, "Left")
screen.onkeypress(press_right, "Right")
screen.onkeyrelease(stop, "Left")
screen.onkeyrelease(stop, "Right")
screen.ontimer(tick, 20)
turtle.done()
"""

STEP2 = """\
import turtle
import random

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 6 课 · 躲避陨石")
screen.bgcolor("black")
screen.tracer(0)
vx = 0
player = turtle.Turtle()
player.shape("turtle")
player.color("deepskyblue")
player.shapesize(1.4, 1.4)
player.penup()
player.goto(0, -230)
player.setheading(90)
meteors = []
for _ in range(6):
    m = turtle.Turtle()
    m.shape("circle")
    m.color("orange")
    m.penup()
    m.goto(random.randint(-360, 360), random.randint(80, 360))
    meteors.append(m)

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
def tick():
    player.setx(player.xcor() + vx)
    if player.xcor() > 370:
        player.setx(370)
    if player.xcor() < -370:
        player.setx(-370)
    for m in meteors:
        m.sety(m.ycor() - 4)
        if m.ycor() < -300:
            reset_meteor(m)
    screen.update()
    screen.ontimer(tick, 20)

screen.listen()
screen.onkeypress(press_left, "Left")
screen.onkeypress(press_right, "Right")
screen.onkeyrelease(stop, "Left")
screen.onkeyrelease(stop, "Right")
screen.ontimer(tick, 20)
turtle.done()
"""

STEP3 = """\
import turtle
import random

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 6 课 · 躲避陨石")
screen.bgcolor("black")
screen.tracer(0)
alive = True
vx = 0
player = turtle.Turtle()
player.shape("turtle")
player.color("deepskyblue")
player.shapesize(1.4, 1.4)
player.penup()
player.goto(0, -230)
player.setheading(90)
meteors = []
for _ in range(6):
    m = turtle.Turtle()
    m.shape("circle")
    m.color("orange")
    m.penup()
    m.goto(random.randint(-360, 360), random.randint(80, 360))
    meteors.append(m)
hud = turtle.Turtle()
hud.hideturtle()
hud.penup()
hud.color("white")

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
def tick():
    global alive
    if not alive:
        screen.update()
        return
    player.setx(player.xcor() + vx)
    if player.xcor() > 370:
        player.setx(370)
    if player.xcor() < -370:
        player.setx(-370)
    for m in meteors:
        m.sety(m.ycor() - 4)
        if m.ycor() < -300:
            reset_meteor(m)
        if player.distance(m) < 24:
            alive = False
            hud.goto(0, 20)
            hud.write("被砸中了！", align="center", font=("Arial", 26, "bold"))
            screen.update()
            return
    screen.update()
    screen.ontimer(tick, 20)

screen.listen()
screen.onkeypress(press_left, "Left")
screen.onkeypress(press_right, "Right")
screen.onkeyrelease(stop, "Left")
screen.onkeyrelease(stop, "Right")
screen.ontimer(tick, 20)
turtle.done()
"""

STEP4 = """\
import turtle
import random

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 6 课 · 躲避陨石")
screen.bgcolor("black")
screen.tracer(0)
score = 0
alive = True
vx = 0
frames = 0
player = turtle.Turtle()
player.shape("turtle")
player.color("deepskyblue")
player.shapesize(1.4, 1.4)
player.penup()
player.goto(0, -230)
player.setheading(90)
meteors = []
for _ in range(6):
    m = turtle.Turtle()
    m.shape("circle")
    m.color("orange")
    m.penup()
    m.goto(random.randint(-360, 360), random.randint(80, 360))
    meteors.append(m)
hud = turtle.Turtle()
hud.hideturtle()
hud.penup()
hud.color("white")

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
    hud.write(f"存活分 {score}", align="center", font=("Arial", 18, "bold"))
def tick():
    global alive, score, frames
    if not alive:
        screen.update()
        return
    frames = frames + 1
    if frames % 5 == 0:
        score = score + 1
    player.setx(player.xcor() + vx)
    if player.xcor() > 370:
        player.setx(370)
    if player.xcor() < -370:
        player.setx(-370)
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
            hud.write(f"被砸中了！最终分 {score}", align="center", font=("Arial", 26, "bold"))
            screen.update()
            return
    draw_hud()
    screen.update()
    screen.ontimer(tick, 20)

screen.listen()
screen.onkeypress(press_left, "Left")
screen.onkeypress(press_right, "Right")
screen.onkeyrelease(stop, "Left")
screen.onkeyrelease(stop, "Right")
screen.ontimer(tick, 20)
turtle.done()
"""

STEP5 = """\
import turtle
import random

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 6 课 · 躲避陨石")
screen.bgcolor("black")
screen.tracer(0)
score = 0
alive = True
vx = 0
frames = 0
player = turtle.Turtle()
player.shape("turtle")
player.color("deepskyblue")
player.shapesize(1.4, 1.4)
player.penup()
player.goto(0, -230)
player.setheading(90)
meteors = []
for _ in range(6):
    m = turtle.Turtle()
    m.shape("circle")
    m.color("orange")
    m.penup()
    m.goto(random.randint(-360, 360), random.randint(80, 360))
    meteors.append(m)
hud = turtle.Turtle()
hud.hideturtle()
hud.penup()
hud.color("white")

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
    hud.write(f"存活分 {score}    左右躲开  ·  R 重开", align="center", font=("Arial", 18, "bold"))
def tick():
    global alive, score, frames
    if not alive:
        screen.update()
        return
    frames = frames + 1
    if frames % 5 == 0:
        score = score + 1
    player.setx(player.xcor() + vx)
    if player.xcor() > 370:
        player.setx(370)
    if player.xcor() < -370:
        player.setx(-370)
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
            hud.write(f"被砸中了！最终分 {score}  按 R 再来", align="center", font=("Arial", 26, "bold"))
            screen.update()
            return
    draw_hud()
    screen.update()
    screen.ontimer(tick, 20)
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

screen.listen()
screen.onkeypress(press_left, "Left")
screen.onkeypress(press_right, "Right")
screen.onkeyrelease(stop, "Left")
screen.onkeyrelease(stop, "Right")
screen.onkeypress(restart, "r")
screen.ontimer(tick, 20)
turtle.done()
"""

CHALLENGE = STEP5.replace(
    """    if frames % 5 == 0:
        score = score + 1""",
    """    if frames % 5 == 0:
        score = score + 1
        if score % 20 == 0 and len(meteors) < 12:
            m = turtle.Turtle()
            m.shape("circle")
            m.color("orange")
            m.penup()
            reset_meteor(m)
            meteors.append(m)""",
)

STEPS = [
    {
        "n": 1,
        "title": "左右躲开",
        "goal": "黑色窗口，底部一只蓝色海龟，按住左右能走。",
        "why": "和第 4 课篮子一样：vx + tick。今天玩家在底部，只左右移动。",
        "where": [
            "创建 screen 和 player，放到 (0, -230)",
            "三个按键函数 + tick",
            "listen 后绑键，ontimer(tick, 20)",
        ],
        "see": "按住左右，蓝色海龟在底部滑动。天上还没有陨石。",
        "pitfall": "忘了 global vx，海龟原地不动。",
        "talk_note": "复习第 4 课三句话。大约 6 分钟。",
        "type_note": "从 import 写到 done。能走再翻页。",
        "type_hint": "player 放底部。press_left 改 vx。tick 末尾要 ontimer。",
        "code": STEP1,
    },
    {
        "n": 2,
        "title": "6 颗陨石下雨",
        "goal": "6 个橙圆从天上往下掉，掉出底部就送回天上。",
        "why": "不要写 m1 m2 m3。创建、append、for 更新，是从这课开始的标准套路。",
        "where": [
            "player 下面 meteors = []，for 循环 6 次 append",
            "加 reset_meteor",
            "tick 里 for m in meteors：y 减 4，掉出就 reset",
        ],
        "see": "6 颗橙圆往下砸，掉出窗口后又从天上出现。这时撞上还没事。",
        "pitfall": "陨石忘了 penup，满屏橙线。",
        "talk_note": "这就是热身。强调列表。大约 10 分钟。",
        "type_note": "for _ in range(6) 造敌人。掉出是送回天上，不是删除。",
        "type_hint": "用列表装 6 颗橙圆。掉出 -300 就 reset_meteor。每只都要 penup。",
        "code": STEP2,
    },
    {
        "n": 3,
        "title": "撞到就结束",
        "goal": "碰到任意一颗陨石，写出「被砸中了」，游戏停。",
        "why": "和第 5 课石头一样：distance < 24。alive 关掉后 tick 开头 return。",
        "where": [
            "加 alive = True 和 hud",
            "tick 开头 if not alive",
            "for 循环里再判断 distance < 24",
        ],
        "see": "撞上橙圆立刻出现「被砸中了」，海龟不再动。",
        "pitfall": "阈值写成 80，站着也被判撞。",
        "talk_note": "让学生故意撞一次。大约 8 分钟。",
        "type_note": "结束时 return，不要再 ontimer。",
        "type_hint": "player.distance(m) < 24 就结束。tick 开头判断 alive。",
        "code": STEP3,
    },
    {
        "n": 4,
        "title": "活得越久分越高",
        "goal": "头顶出现存活分；分数越高陨石掉得越快。",
        "why": "每 5 帧 +1 分。speed = 4 + score//15。一上来就很快没法玩。",
        "where": [
            "加 score 和 frames",
            "tick 里 frames+1，每 5 帧 score+1",
            "下落速度改成 4 + score // 15；陨石 left(4) 旋转",
        ],
        "see": "头顶分数往上加。撑得越久，陨石越快。",
        "pitfall": "speed 写成 4 + score，几秒就没法躲。要用 // 15。",
        "talk_note": "整数除法写在黑板上。大约 8 分钟。",
        "type_note": "hud 每帧重画。撞到时把最终分写出来。",
        "type_hint": "每 5 帧加 1 分。速度 4 + score // 15。",
        "code": STEP4,
    },
    {
        "n": 5,
        "title": "按 R 再来一局",
        "goal": "结束后按 R：分数清零、陨石回天上、游戏继续。",
        "why": "重开要复位所有状态：分数、帧、alive、速度、位置。漏一个就会残局。",
        "where": [
            "加 restart，里面 alive=True，再调用 tick()",
            "绑小写 r",
        ],
        "see": "撞死后按 R，又能躲。头顶提示「R 重开」。",
        "pitfall": "restart 忘了 alive=True，按 R 没反应。",
        "talk_note": "这是过关线。让全班死一次再重开。大约 8 分钟。",
        "type_note": "restart 里 for m in meteors: reset_meteor(m)，最后 tick()。",
        "type_hint": "restart 把 score、frames、alive、vx 都复位，再 tick()。键名是小写 r。",
        "code": STEP5,
    },
]

LESSON = {
    "n": 6,
    "title": "越来越难",
    "icon": "☄️",
    "project": "躲避陨石",
    "header": HEADER,
    "final": STEP5,
    "io": "左右移动蓝色海龟。\n6 颗陨石往下砸，躲开。\n存活时间就是分数。撞到结束，R 再来。",
    "pass_line": "能躲开陨石，撞到会结束，R 能重开。",
    "start_cards": [
        ("1. 新建文件", "保存为 <span class=\"ic\">lesson6.py</span>。今天从头写到尾，只用这一份。"),
        ("2. 带着第 5 课", "<span class=\"ic\">distance</span> 判断碰撞；<span class=\"ic\">vx</span> 按住移动。今天敌人变成一串。"),
        ("3. 每一步都要运行", "打完这一步就点运行。跑通再翻下一步。"),
    ],
    "cover_note": "今天用列表管多个敌人。翻一页，打一段，运行一次。",
    "product_note": "先演示躲避，再让学生关窗口、打开空文件。",
    "start_note": "口答：第 5 课石头为什么用列表。有人还在 lesson5.py 里接着写，让他新建。",
    "map_note": "第 2 步列表是核心。掉队的人停在当前步。",
    "errors": [
        ("重开忘了 alive=True", "restart 里复位", "R 没反应"),
        ("掉出屏幕不 reset", "reset_meteor(m)", "陨石越来越少"),
        ("阈值太大", "大约 24", "站着也被判撞"),
    ],
    "errors_note": "R 没反应先查 alive。场上越来越空先查 reset。",
    "challenge_code": CHALLENGE,
    "challenge_must_contain": "len(meteors)",
    "challenge_title": "每 20 分加一颗陨石",
    "challenge_lede": "主游戏能玩之后：分数每到 20 的倍数，再 append 一颗，最多 12 颗。",
    "challenge_see": "活得越久，天上的陨石越多。",
    "challenge_note": "加陨石写在 score+1 后面，这样每 20 分只加一次。",
    "ex": [
        ("更少", "初始 4 颗"),
        ("换色", "玩家换颜色"),
        ("更慢", "speed = 3 + score//20"),
        ("方形陨石", 'shape("square")'),
    ],
    "ex_note": "改数字最适合这个时间点。",
    "sum_rows": [
        ("列表", "多个敌人", "append 装起来"),
        ("for 更新", "一起掉", "reset 循环利用"),
        ("难度", "越来越快", "score // n"),
    ],
    "sum_note": "抽人讲为什么掉出要送回天上。预告第 7 课子弹也是列表。",
    "next_line": "第 7 课：子弹列表 — 打气球",
    "next_short": "发射！— 打气球",
    "print_know": [
        ("列表", "一串敌人", "meteors = []"),
        ("工厂循环", "for _ in range(6)", "创建并 append"),
        ("统一更新", "for m in meteors", "移动 + 碰撞"),
        ("//", "整数除法", "score // 15"),
        ("重开", "分数/位置清零", "按 R"),
    ],
    "print_blanks": [
        "1. 多个敌人应该放进 ________ 而不是 m1 m2 m3",
        "2. 整数除法的符号是 ________",
        "3. 掉出屏幕后应该 ________（扔掉 / 送回天上）",
        "4. 重开时必须把 alive 改回 ________",
        "5. 本课默认同时有 ________ 颗陨石",
        "6. 存活分是靠 ________ 累加的（时间 / 击杀）",
    ],
    "print_challenge": "主游戏能玩之后，每 20 分 <span class=\"mono\">append</span> 一颗新陨石，最多 12 颗。",
    "print_times": [
        ("0–8", "看成品，新建 lesson6.py"),
        ("8–35", "第 1～3 步（能走、下雨、碰撞）"),
        ("35–65", "第 4～5 步（计分加速、R 重开）"),
        ("65–82", "加码：越来越多陨石（选做）"),
        ("82–90", "改错 + 填空 + 小结"),
    ],
    "steps": STEPS,
}

if __name__ == "__main__":
    write_outputs(LESSON)
