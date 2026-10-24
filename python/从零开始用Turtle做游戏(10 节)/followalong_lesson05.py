#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""第 5 课跟打课件 / 学案生成器。源码步骤是课件的唯一真相。"""
from __future__ import annotations

HEADER = """\
# ============================================
# 第 5 课  碰一碰
# 小游戏：星星收集者
# 知识：distance 碰撞、多种角色、胜负判定
# 操作：方向键移动；吃到星星 +1；碰到石头就结束
#       吃满 10 颗星星获胜
# ============================================

"""

STEP1 = """\
import turtle
import random

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 5 课 · 星星收集者")
screen.bgcolor("#0d1b2a")
screen.tracer(0)
player = turtle.Turtle()
player.shape("turtle")
player.color("green")
player.shapesize(1.5, 1.5)
player.penup()
player.goto(0, 0)
screen.update()
turtle.done()
"""

STEP2 = """\
import turtle
import random

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 5 课 · 星星收集者")
screen.bgcolor("#0d1b2a")
screen.tracer(0)
vx = 0
vy = 0
player = turtle.Turtle()
player.shape("turtle")
player.color("green")
player.shapesize(1.5, 1.5)
player.penup()
player.goto(0, 0)

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
def tick():
    player.setx(player.xcor() + vx)
    player.sety(player.ycor() + vy)
    screen.update()
    screen.ontimer(tick, 20)

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
"""

STEP3 = """\
import turtle
import random

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 5 课 · 星星收集者")
screen.bgcolor("#0d1b2a")
screen.tracer(0)
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
def draw_hud():
    hud.clear()
    hud.goto(0, 250)
    d = int(player.distance(star))
    hud.write(f"距离 {d}", align="center", font=("Arial", 20, "bold"))
def tick():
    player.setx(player.xcor() + vx)
    player.sety(player.ycor() + vy)
    draw_hud()
    screen.update()
    screen.ontimer(tick, 20)

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
"""

STEP4 = """\
import turtle
import random

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 5 课 · 星星收集者")
screen.bgcolor("#0d1b2a")
screen.tracer(0)
score = 0
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
    hud.write(f"星星 {score}    距离 {d}", align="center", font=("Arial", 20, "bold"))
def tick():
    global score
    player.setx(player.xcor() + vx)
    player.sety(player.ycor() + vy)
    if player.distance(star) < 28:
        score += 1
        place_star()
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
"""

STEP5 = """\
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
    hud.write(f"星星 {score}    距离 {d}", align="center", font=("Arial", 20, "bold"))
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
    if player.distance(star) < 28:
        score += 1
        place_star()
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
"""

STEP6 = """\
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
"""

CHALLENGE = STEP6.replace(
    """    for rock in rocks:
        if player.distance(rock) < 26:""",
    """    for rock in rocks:
        rock.forward(1)
        rock.left(2)
        if player.distance(rock) < 26:""",
)

STEPS = [
    {
        "n": 1,
        "title": "窗口和玩家",
        "goal": "弹出深蓝窗口，正中间有一只绿色海龟。",
        "why": "tracer(0) 会暂时不自动画画，所以最后要 screen.update()，否则窗口是黑的。",
        "where": [
            "文件最开头写两行 import（random 等会儿用）",
            "创建 screen，再创建 player",
            "最后两行：screen.update() 和 turtle.done()",
        ],
        "see": "800×600 深蓝窗口，正中间一只绿色海龟。这时还不会动。",
        "pitfall": "写了 tracer(0) 却忘了 update，窗口一片黑。",
        "talk_note": "先让每人建好 lesson5.py。random 这课还不用，但写在开头，后面就不用插到文件顶上。点运行，确认看见海龟再翻页。大约 6 分钟。",
        "type_note": "让学生把这一页从头打到 done。跑起来再翻。有人黑屏，问他有没有 update。",
        "type_hint": "从 import 写到 turtle.done()。tracer(0) 后面一定要有 screen.update()。",
        "code": STEP1,
    },
    {
        "n": 2,
        "title": "方向键开走",
        "goal": "按住方向键，海龟连续走；松开就停。",
        "why": "和第 4 课篮子左右移动一样：按住改速度，tick 里每帧加上速度。今天多一个 vy 管上下。",
        "where": [
            "在 player 上面加 vx = 0 和 vy = 0",
            "删掉单独的 screen.update()，改成 6 个小函数 + tick",
            "turtle.done() 前面绑 8 次键，再 ontimer(tick, 20)",
        ],
        "see": "按住方向键海龟连续移动。可以斜着走（左右和上下同时按）。",
        "pitfall": "函数里改 vx 忘了写 global vx，海龟原地不动。",
        "talk_note": "老师当场打 press_left 和 stop_x。其余四个让学生对着改方向。提醒：onkeypress 后面写函数名，不要加括号。大约 10 分钟。",
        "type_note": "六个函数长得很像，抄完一个改数字和名字。打完先跑，能走再翻页。",
        "type_hint": "先抄 press_left 和 stop_x，另外四个改方向。tick 末尾要 ontimer。",
        "code": STEP2,
    },
    {
        "n": 3,
        "title": "屏幕上的距离",
        "goal": "再放一颗黄星星。头顶数字是你和星星的距离，走近就变小。",
        "why": "没有内置碰撞函数。碰撞就是 distance 小于一个数。先把数字看在眼睛里。",
        "where": [
            "player 下面加 star（黄三角）和 hud（只写字，藏起来）",
            "六个按键函数下面加 draw_hud",
            "tick 里，update 之前调用 draw_hud()",
        ],
        "see": "黄三角在右上方。走动时头顶「距离 xx」变小或变大。贴上去大约是 20 多。",
        "pitfall": "hud 忘了 hideturtle，屏幕上会多一只小箭头。",
        "talk_note": "这就是以前的热身。让学生走进去看数字。问：阈值写成 5 会怎样？写成 200 会怎样？告诉他们下一步用 28。大约 8 分钟。",
        "type_note": "distance 这一行是今天的核心，打的时候读出声：玩家到星星的距离。",
        "type_hint": "加上黄三角 star 和只写字的 hud。tick 里调用 draw_hud()，走近看数字变小。",
        "code": STEP3,
    },
    {
        "n": 4,
        "title": "吃星星加分",
        "goal": "贴上星星：分数 +1，星星跳到别处。不能刷在脚底下。",
        "why": "星星刷在脚底下会一帧吃掉。while True 随机，直到离玩家大于 60 再停。",
        "where": [
            "vx 上面加 score = 0",
            "draw_hud 上面加 place_star",
            "tick 开头写 global score；移动之后判断 distance < 28",
            "listen 之前调用一次 place_star()",
        ],
        "see": "吃到黄三角，分数 +1，星星换位置。头顶同时显示分数和距离。",
        "pitfall": "吃到了却不调用 place_star()，星星停在嘴里，分数狂加。",
        "talk_note": "阈值 28 和 shapesize 1.5 配套，贴着就能吃到。while True 一定要有 break。大约 10 分钟。",
        "type_note": "tick 里面要加 global score，否则加分会报错。打完先吃 2 颗再翻页。",
        "type_hint": "distance < 28 就加分并 place_star()。tick 开头写 global score。",
        "code": STEP4,
    },
    {
        "n": 5,
        "title": "石头会让你失败",
        "goal": "场上 4 颗红圆。碰到任意一颗，写出「撞到石头了」，游戏停。",
        "why": "道具加分、障碍结束，都是 distance，只是阈值和后果不同。结束时要把 alive 关掉，tick 开头就 return。",
        "where": [
            "score 旁边加 alive = True",
            "star 下面用 for 循环做 4 颗红石头，装进 rocks 列表",
            "加 finish(msg)，tick 开头判断 if not alive",
            "tick 里 for rock in rocks 检查距离 < 26",
        ],
        "see": "四颗红圆散落。撞上去立刻出现「撞到石头了」，海龟不再动。",
        "pitfall": "石头忘了 penup，一跑起来满屏红线。",
        "talk_note": "列表和第 6 课是同一句型，今天只要会 append 和 for 遍历。刷石头也要离玩家 > 80，避免一运行就失败。大约 10 分钟。",
        "type_note": "finish 把「停下来 + 写大字」收成一个函数，下一步胜利会再用。",
        "type_hint": "for 循环做 4 颗红圆，碰到就 finish。每只石头都要 penup。",
        "code": STEP5,
    },
    {
        "n": 6,
        "title": "满 10 颗就赢",
        "goal": "吃满 10 颗写出「你赢了」；海龟走不出窗口。",
        "why": "胜利和失败都走 finish，都要停掉 tick。边界用四条 if 夹紧，比一行 max/min 好读。",
        "where": [
            "draw_hud 的文字改成 星星 {score} / 10",
            "tick 里移动之后加四条边界 if",
            "吃到星星之后再判断 if score >= 10: finish(...)",
        ],
        "see": "走到窗口边缘会被挡住。吃满 10 颗出现「收集完成！你赢了」。",
        "pitfall": "赢了却继续 ontimer，还能撞石头把胜利字盖掉。finish 之后要 return。",
        "talk_note": "这是过关线。让全班先玩到赢一次或输一次。没做完的人不要跳加码。大约 8 分钟。",
        "type_note": "四条边界 if 可以一起打。赢的判断写在 place_star() 后面。",
        "type_hint": "四条 if 夹紧窗口。score >= 10 时 finish 并 return。",
        "code": STEP6,
    },
]


from followalong_engine import write_outputs as _write

LESSON = {
    "n": 5,
    "title": "碰一碰",
    "icon": "⭐",
    "project": "星星收集者",
    "header": HEADER,
    "final": STEP6,
    "io": "方向键开走绿色海龟。\n吃到黄三角：+1 分，星星换位置。\n吃满 10 颗：你赢了。\n碰到红圆石头：游戏结束。",
    "pass_line": "能吃星星、会输会赢。",
    "start_cards": [
        ("1. 新建文件", "保存为 <span class=\"ic\">lesson5.py</span>。今天从头写到尾，只用这一份。"),
        ("2. 带着第 4 课的三句话", "<span class=\"ic\">tracer(0)</span> 要配 <span class=\"ic\">update()</span>；<span class=\"ic\">tick</span> 末尾再约自己；按住移动靠 <span class=\"ic\">vx</span>。"),
        ("3. 每一步都要运行", "打完这一步就点运行，对照页上的「运行后你该看到」。跑通再翻下一步。"),
    ],
    "cover_note": "今天不先讲一堆概念。翻一页，打一段，运行一次。下课要能把窗口打开给别人玩。",
    "product_note": "先演示一遍老师做好的版本，再让学生关窗口、打开空文件。不要让他们对着成品抄。",
    "start_note": "巡视文件名。有人还在 lesson4.py 里接着写，让他新建。三句话口答一遍再开始第 1 步。",
    "map_note": "指着地图说：前三步 8–35 分，后三步 35–65 分。掉队的人停在当前步，不要跳。",
    "errors": [
        ("阈值写成 5", "星星用 28，石头用 26", "贴着也吃不到"),
        ("吃到不调用 place_star()", "加分后立刻换位置", "星星停在嘴里会连续加分"),
        ("石头忘了 penup", "每只石头都要抬笔", "否则满屏红线"),
    ],
    "errors_note": "用投影仪打错误现象，让学生在自己代码里找。改错 5 分钟很值钱。",
    "challenge_code": CHALLENGE,
    "challenge_must_contain": "rock.forward(1)",
    "challenge_title": "石头会慢慢转圈",
    "challenge_lede": "主游戏能玩之后：在 for rock 循环里加 rock.forward(1) 和 rock.left(2)。",
    "challenge_see": "红圆缓慢游走，仍要躲开它们。",
    "challenge_note": "巡堂。加码只有两行，但石头动起来之后难度明显上升。提醒仍然要 penup。",
    "ex": [
        ("更贪", "胜利改成 15 颗"),
        ("换色", "玩家改成自己喜欢的颜色"),
        ("更险", "石头改成 6 颗（改 range）"),
        ("更快", "vx / vy 的 6 改成 9"),
    ],
    "ex_note": "改参数比再写新功能更适合这个时间点。做不完当课后。",
    "sum_rows": [
        ("distance", "两只海龟的距离", "小于 28 算吃到"),
        ("道具 / 障碍", "加分 / 失败", "两种判定"),
        ("alive", "游戏还在进行吗", "赢或输都要停 tick"),
    ],
    "sum_note": "抽两个人：一个讲 distance，一个讲为什么 finish 之后要 return。预告第 6 课敌人会变成一串。",
    "next_line": "第 6 课：列表管理多个敌人 — 躲避陨石",
    "next_short": "越来越难 — 躲避陨石",
    "print_know": [
        ("distance", "两只海龟的距离", "player.distance(star)"),
        ("阈值", "小于它就算碰到", "星星 28 · 石头 26"),
        ("place_star", "换位置，别刷在脚下", "distance > 60 再 break"),
        ("alive", "游戏还在进行吗", "赢或输都改成 False"),
        ("penup", "障碍不要拖线", "每只石头都要抬笔"),
    ],
    "print_blanks": [
        "1. 碰撞检测用的方法名是 ________",
        "2. 阈值太小会 ________（吃不到 / 太容易）",
        "3. 石头忘了 penup 会在屏幕上留下 ________",
        "4. 吃到星星后一定要调用 ________",
        "5. 吃满 ________ 颗星星算赢（本课默认）",
        "6. player.distance(star) 的单位是 ________",
    ],
    "print_challenge": "主游戏能玩之后，在石头循环里加：<span class=\"mono\">rock.forward(1)</span> 和 <span class=\"mono\">rock.left(2)</span>。",
    "print_times": [
        ("0–8", "看成品，新建 lesson5.py"),
        ("8–35", "第 1～3 步（窗口、能走、看距离）"),
        ("35–65", "第 4～6 步（吃星星、石头、胜负）"),
        ("65–82", "加码：石头会动（选做）"),
        ("82–90", "改错 + 填空 + 小结"),
    ],
    "steps": STEPS,
}


def write_outputs() -> None:
    _write(LESSON)


if __name__ == "__main__":
    write_outputs()
