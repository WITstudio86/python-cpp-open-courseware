#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""第 4 课跟打数据。"""
from __future__ import annotations

from followalong_engine import write_outputs

HEADER = """\
# ============================================
# 第 4 课  让画面自己动
# 小游戏：接住金币
# 知识：ontimer 游戏循环、下落、左右移动
# 操作：左右方向键移动篮子，接住掉下来的金币
# ============================================

"""

STEP1 = """\
import turtle
import random

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 4 课 · 接住金币")
screen.bgcolor("navy")
screen.tracer(0)
basket = turtle.Turtle()
basket.shape("square")
basket.color("gold")
basket.shapesize(1, 5)
basket.penup()
basket.goto(0, -240)
coin = turtle.Turtle()
coin.shape("circle")
coin.color("yellow")
coin.penup()
coin.goto(0, 260)
screen.update()
turtle.done()
"""

STEP2 = """\
import turtle
import random

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 4 课 · 接住金币")
screen.bgcolor("navy")
screen.tracer(0)
vx = 0
basket = turtle.Turtle()
basket.shape("square")
basket.color("gold")
basket.shapesize(1, 5)
basket.penup()
basket.goto(0, -240)
coin = turtle.Turtle()
coin.shape("circle")
coin.color("yellow")
coin.penup()
coin.goto(0, 260)

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
    basket.setx(basket.xcor() + vx)
    if basket.xcor() > 350:
        basket.setx(350)
    if basket.xcor() < -350:
        basket.setx(-350)
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
screen.title("第 4 课 · 接住金币")
screen.bgcolor("navy")
screen.tracer(0)
vx = 0
basket = turtle.Turtle()
basket.shape("square")
basket.color("gold")
basket.shapesize(1, 5)
basket.penup()
basket.goto(0, -240)
coin = turtle.Turtle()
coin.shape("circle")
coin.color("yellow")
coin.penup()
coin.goto(0, 260)

def reset_coin():
    coin.goto(random.randint(-340, 340), 280)
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
    basket.setx(basket.xcor() + vx)
    if basket.xcor() > 350:
        basket.setx(350)
    if basket.xcor() < -350:
        basket.setx(-350)
    coin.sety(coin.ycor() - 5)
    if coin.ycor() < -280:
        reset_coin()
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
screen.title("第 4 课 · 接住金币")
screen.bgcolor("navy")
screen.tracer(0)
score = 0
missed = 0
vx = 0
basket = turtle.Turtle()
basket.shape("square")
basket.color("gold")
basket.shapesize(1, 5)
basket.penup()
basket.goto(0, -240)
coin = turtle.Turtle()
coin.shape("circle")
coin.color("yellow")
coin.penup()
coin.goto(0, 260)
hud = turtle.Turtle()
hud.hideturtle()
hud.penup()
hud.color("white")

def reset_coin():
    coin.goto(random.randint(-340, 340), 280)
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
    hud.write(f"接到 {score}    漏掉 {missed}", align="center", font=("Arial", 20, "bold"))
def tick():
    global score, missed
    basket.setx(basket.xcor() + vx)
    if basket.xcor() > 350:
        basket.setx(350)
    if basket.xcor() < -350:
        basket.setx(-350)
    coin.sety(coin.ycor() - 5)
    if coin.ycor() < -280:
        missed = missed + 1
        reset_coin()
    if coin.ycor() < -210 and basket.distance(coin) < 70:
        score = score + 1
        reset_coin()
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
screen.title("第 4 课 · 接住金币")
screen.bgcolor("navy")
screen.tracer(0)
score = 0
missed = 0
alive = True
vx = 0
basket = turtle.Turtle()
basket.shape("square")
basket.color("gold")
basket.shapesize(1, 5)
basket.penup()
basket.goto(0, -240)
coin = turtle.Turtle()
coin.shape("circle")
coin.color("yellow")
coin.penup()
coin.goto(0, 260)
hud = turtle.Turtle()
hud.hideturtle()
hud.penup()
hud.color("white")

def reset_coin():
    coin.goto(random.randint(-340, 340), 280)
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
    hud.write(f"接到 {score}    漏掉 {missed}/8", align="center", font=("Arial", 20, "bold"))
def game_over(msg):
    global alive
    alive = False
    hud.goto(0, 20)
    hud.write(msg, align="center", font=("Arial", 28, "bold"))
def tick():
    global score, missed
    if not alive:
        screen.update()
        return
    basket.setx(basket.xcor() + vx)
    if basket.xcor() > 350:
        basket.setx(350)
    if basket.xcor() < -350:
        basket.setx(-350)
    coin.sety(coin.ycor() - (5 + score // 3))
    if coin.ycor() < -280:
        missed = missed + 1
        reset_coin()
        if missed >= 8:
            draw_hud()
            game_over("金币漏光了……再开一局试试")
            screen.update()
            return
    if coin.ycor() < -210 and basket.distance(coin) < 70:
        score = score + 1
        reset_coin()
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

CHALLENGE = STEP5.replace(
    """coin = turtle.Turtle()
coin.shape("circle")
coin.color("yellow")
coin.penup()
coin.goto(0, 260)
hud = turtle.Turtle()""",
    """coin = turtle.Turtle()
coin.shape("circle")
coin.color("yellow")
coin.penup()
coin.goto(0, 260)
bomb = turtle.Turtle()
bomb.shape("circle")
bomb.color("red")
bomb.penup()
bomb.goto(120, 320)
hud = turtle.Turtle()""",
).replace(
    """    if coin.ycor() < -210 and basket.distance(coin) < 70:
        score = score + 1
        reset_coin()
    draw_hud()""",
    """    if coin.ycor() < -210 and basket.distance(coin) < 70:
        score = score + 1
        reset_coin()
    bomb.sety(bomb.ycor() - 4)
    if bomb.ycor() < -280:
        bomb.goto(random.randint(-340, 340), 300)
    if bomb.ycor() < -210 and basket.distance(bomb) < 70:
        score = score - 2
        bomb.goto(random.randint(-340, 340), 300)
    draw_hud()""",
)

STEPS = [
    {
        "n": 1,
        "title": "篮子和金币",
        "goal": "深蓝窗口：底部一条金色篮子，天上一个黄圆。",
        "why": "先摆角色。tracer(0) 必须配 update。shapesize(1, 5) 把方块拉成横条。",
        "where": [
            "创建 screen，tracer(0)",
            "basket 放 (0, -240)，coin 放 (0, 260)",
            "最后 update 和 done",
        ],
        "see": "底部一条金色横条，天上一个黄圆。这时都不会动。",
        "pitfall": "写了 tracer(0) 却忘了 update，窗口一片黑。",
        "talk_note": "这就是热身的舞台。确认看见两样东西再翻。大约 5 分钟。",
        "type_note": "从 import 写到 done。篮子 shapesize(1, 5) 不要抄反。",
        "type_hint": "篮子在 (0, -240)，金币在 (0, 260)。tracer(0) 后面要有 update。",
        "code": STEP1,
    },
    {
        "n": 2,
        "title": "按住篮子会走",
        "goal": "按住左右方向键，篮子连续移动；松开就停。",
        "why": "点一下走一格是第 2 课。从这课起：按住改 vx，tick 每帧加上速度。",
        "where": [
            "basket 上面加 vx = 0",
            "三个小函数 + tick，末尾 ontimer(tick, 20)",
            "listen 后绑 press 和 release",
        ],
        "see": "按住方向键篮子连续走。松开立刻停。金币还停在天上。",
        "pitfall": "函数里改 vx 忘了 global vx，篮子原地不动。",
        "talk_note": "老师当场打 press_left 和 stop。强调 onkeyrelease。大约 10 分钟。",
        "type_note": "tick 末尾一定再约自己，否则只动一帧。",
        "type_hint": "press_left 把 vx 改成 -8。tick 末尾要 ontimer。松开用 onkeyrelease。",
        "ask": "tick 末尾忘了 ontimer，动画会怎样？",
        "code": STEP2,
    },
    {
        "n": 3,
        "title": "金币往下掉",
        "goal": "金币每帧往下掉；掉出底部就回到天上随机位置。",
        "why": "下落就是 sety 减小。掉出屏幕不要结束，先送回天上。",
        "where": [
            "加 reset_coin",
            "tick 里 coin.sety(... - 5)",
            "y < -280 就 reset_coin()",
        ],
        "see": "黄圆不断下落，掉出窗口后又从天上随机位置出现。",
        "pitfall": "掉出后不 reset，金币一去不回，游戏变空。",
        "talk_note": "这就是原来的热身。让学生盯着看它循环。大约 8 分钟。",
        "type_note": "reset_coin 一行 goto 随机 x 和 280。",
        "type_hint": "tick 里金币 y 减 5。掉出 -280 就 reset_coin()。",
        "code": STEP3,
    },
    {
        "n": 4,
        "title": "接到和漏掉",
        "goal": "靠近篮子：分数 +1；掉出底部：漏掉 +1。头顶显示两个数字。",
        "why": "接到用 distance。先判断掉出，再判断接到，顺序不要反。tick 开头 global score, missed。",
        "where": [
            "vx 上面加 score 和 missed，再加 hud",
            "tick 开头 global；掉出 missed+1；靠近则 score+1",
        ],
        "see": "接到黄圆分数 +1 并换一枚。漏掉头顶漏掉数 +1。",
        "pitfall": "tick 里不加 global score，一接到就报错。",
        "talk_note": "让每人接到 2 个、故意漏 1 个。大约 8 分钟。",
        "type_note": "distance < 70 和 y < -210 一起判断，避免天上就算接到。",
        "type_hint": "tick 开头 global score, missed。靠近篮子 distance < 70 就加分。",
        "code": STEP4,
    },
    {
        "n": 5,
        "title": "漏 8 个就结束",
        "goal": "漏满 8 个写出结束语；接到越多掉得越快。",
        "why": "alive 关掉后 tick 开头就 return。速度用 5 + score//3，整数除法。",
        "where": [
            "加 alive 和 game_over",
            "tick 开头 if not alive: return",
            "missed >= 8 就结束；下落速度改成 5 + score//3",
        ],
        "see": "漏满 8 个出现「金币漏光了」。接到越多，后面掉得越快。",
        "pitfall": "结束之后还 ontimer，字会被下一帧清掉。game_over 后要 return。",
        "talk_note": "这是过关线。让全班玩到结束一次。大约 8 分钟。",
        "type_note": "hud 改成 漏掉 n/8。game_over 后一定 return。",
        "type_hint": "漏满 8 个 game_over 并 return。下落改成 5 + score // 3。",
        "code": STEP5,
    },
]

LESSON = {
    "n": 4,
    "title": "让画面自己动",
    "icon": "🪙",
    "project": "接住金币",
    "header": HEADER,
    "final": STEP5,
    "io": "左右移动篮子。\n金币从天而降，接到 +1。\n漏掉 8 个游戏结束。接到越多掉得越快。",
    "pass_line": "能左右移动接金币，漏 8 个会结束。",
    "start_cards": [
        ("1. 新建文件", "保存为 <span class=\"ic\">lesson4.py</span>。今天从头写到尾，只用这一份。"),
        ("2. 带着第 3 课", "<span class=\"ic\">distance</span> 判断靠近；<span class=\"ic\">ontimer</span> 不要死循环。今天 ontimer 会变成每 20 毫秒一帧。"),
        ("3. 每一步都要运行", "打完这一步就点运行。跑通再翻下一步。"),
    ],
    "cover_note": "今天画面开始自己动。翻一页，打一段，运行一次。",
    "product_note": "先演示接金币，再让学生关窗口、打开空文件。",
    "start_note": "口答：为什么倒计时不用 while True。有人还在 lesson3.py 里接着写，让他新建。",
    "map_note": "第 2 步 vx 是后面几课的基础。掉队的人停在当前步。",
    "errors": [
        ("tick 里忘了 ontimer", "末尾再约一次", "否则只动一帧"),
        ("忘了 global vx", "在函数里写 global vx", "否则改的是局部变量"),
        ("tracer(0) 不 update", "每帧 update()", "否则全黑"),
    ],
    "errors_note": "只动一帧 = 忘了 ontimer。原地不动 = 忘了 global。",
    "challenge_code": CHALLENGE,
    "challenge_must_contain": "bomb",
    "challenge_title": "再掉一颗炸弹",
    "challenge_lede": "主游戏能玩之后：再做一只红色 bomb 一起掉。接到 score -= 2。",
    "challenge_see": "红圆和黄圆一起掉。接到红的扣 2 分。",
    "challenge_note": "巡堂。炸弹也要 penup。没做完主游戏不要跳。",
    "ex": [
        ("加宽篮子", "shapesize(1, 7)"),
        ("更大金币", "shapesize 调大"),
        ("更狠", "漏 5 个就结束"),
        ("更快", "vx 的 8 改成 12"),
    ],
    "ex_note": "改参数比再写新功能更适合这个时间点。",
    "sum_rows": [
        ("tracer / update", "流畅", "手动刷新"),
        ("tick + ontimer", "循环", "每帧更新"),
        ("vx + release", "按住移动", "松开清零"),
    ],
    "sum_note": "抽人讲 tick 三步：改位置、update、再约自己。预告第 5 课碰撞。",
    "next_line": "第 5 课：碰撞检测 — 吃星星、躲石头",
    "next_short": "碰一碰 — 星星收集者",
    "print_know": [
        ("tracer(0)+update()", "流畅动画", "每帧结束再画"),
        ("游戏循环", "tick 改位置再约自己", "ontimer(tick, 20)"),
        ("vx 速度", "按住 = 有速度", "松开 vx=0"),
        ("onkeyrelease", "松键回调", "stop()"),
        ("掉出屏幕", "重置到天上", "coin.sety(280)"),
    ],
    "print_blanks": [
        "1. 关掉自动刷新：screen.________(0)",
        "2. 游戏循环函数通常叫 ________",
        "3. 松手停下来用 screen.________",
        "4. tick 末尾忘了 ontimer，动画只会动 ________ 帧",
        "5. 松开左键要把 vx 改成 ________",
        "6. 20 毫秒一帧，大约每秒 ________ 帧",
    ],
    "print_challenge": "主游戏能玩之后，再做一只红色 bomb 一起掉。接到 <span class=\"mono\">score -= 2</span>。",
    "print_times": [
        ("0–8", "看成品，新建 lesson4.py"),
        ("8–35", "第 1～3 步（舞台、能走、下落）"),
        ("35–65", "第 4～5 步（计分、结束）"),
        ("65–82", "加码：炸弹扣分（选做）"),
        ("82–90", "改错 + 填空 + 小结"),
    ],
    "steps": STEPS,
}

if __name__ == "__main__":
    write_outputs(LESSON)
