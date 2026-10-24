#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""第 3 课跟打数据。"""
from __future__ import annotations

from followalong_engine import write_outputs

HEADER = """\
# ============================================
# 第 3 课  点哪里打哪里
# 小游戏：打地鼠
# 知识：onscreenclick、随机坐标、计分、倒计时
# 操作：地鼠出现后尽快点中；30 秒结束
# ============================================

"""

STEP1 = """\
import turtle
import random

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 3 课 · 打地鼠")
screen.bgcolor("saddlebrown")
screen.tracer(0)
mole = turtle.Turtle()
mole.shape("turtle")
mole.color("orange")
mole.shapesize(2.2, 2.2)
mole.penup()
x = random.randint(-320, 320)
y = random.randint(-180, 180)
mole.goto(x, y)
screen.update()
turtle.done()
"""

STEP2 = """\
import turtle
import random

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 3 课 · 打地鼠")
screen.bgcolor("saddlebrown")
screen.tracer(0)
score = 0
mole = turtle.Turtle()
mole.shape("turtle")
mole.color("orange")
mole.shapesize(2.2, 2.2)
mole.penup()
hud = turtle.Turtle()
hud.hideturtle()
hud.penup()
hud.color("white")

def jump_mole():
    x = random.randint(-320, 320)
    y = random.randint(-180, 180)
    mole.goto(x, y)
    mole.showturtle()
    screen.update()
def draw_hud():
    hud.clear()
    hud.goto(0, 240)
    hud.write(f"得分 {score}", align="center", font=("Arial", 22, "bold"))
    screen.update()
def hit(x, y):
    global score
    if mole.distance(x, y) < 40:
        score = score + 1
        mole.hideturtle()
        draw_hud()
        jump_mole()

draw_hud()
jump_mole()
screen.onscreenclick(hit)
turtle.done()
"""

STEP3 = """\
import turtle
import random

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 3 课 · 打地鼠")
screen.bgcolor("saddlebrown")
screen.tracer(0)
score = 0
time_left = 30
alive = True
mole = turtle.Turtle()
mole.shape("turtle")
mole.color("orange")
mole.shapesize(2.2, 2.2)
mole.penup()
hud = turtle.Turtle()
hud.hideturtle()
hud.penup()
hud.color("white")

def jump_mole():
    if not alive:
        return
    x = random.randint(-320, 320)
    y = random.randint(-180, 180)
    mole.goto(x, y)
    mole.showturtle()
    screen.update()
def draw_hud():
    hud.clear()
    hud.goto(0, 240)
    hud.write(f"得分 {score}    剩余 {time_left} 秒", align="center", font=("Arial", 22, "bold"))
    screen.update()
def hit(x, y):
    global score
    if not alive:
        return
    if mole.distance(x, y) < 40:
        score = score + 1
        mole.hideturtle()
        draw_hud()
        jump_mole()
def tick_timer():
    global time_left, alive
    if not alive:
        return
    time_left = time_left - 1
    draw_hud()
    if time_left <= 0:
        alive = False
        mole.hideturtle()
        hud.goto(0, 40)
        hud.write(f"时间到！最终得分 {score}", align="center", font=("Arial", 28, "bold"))
        screen.update()
        return
    screen.ontimer(tick_timer, 1000)

draw_hud()
jump_mole()
screen.onscreenclick(hit)
screen.ontimer(tick_timer, 1000)
turtle.done()
"""

STEP4 = """\
import turtle
import random

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 3 课 · 打地鼠")
screen.bgcolor("saddlebrown")
screen.tracer(0)
score = 0
time_left = 30
alive = True
mole = turtle.Turtle()
mole.shape("turtle")
mole.color("orange")
mole.shapesize(2.2, 2.2)
mole.penup()
hud = turtle.Turtle()
hud.hideturtle()
hud.penup()
hud.color("white")

def jump_mole():
    if not alive:
        return
    x = random.randint(-320, 320)
    y = random.randint(-180, 180)
    mole.goto(x, y)
    mole.showturtle()
    screen.update()
def draw_hud():
    hud.clear()
    hud.goto(0, 240)
    hud.write(f"得分 {score}    剩余 {time_left} 秒", align="center", font=("Arial", 22, "bold"))
    screen.update()
def hit(x, y):
    global score
    if not alive:
        return
    if mole.distance(x, y) < 40:
        score = score + 1
        mole.hideturtle()
        draw_hud()
        jump_mole()
def tick_timer():
    global time_left, alive
    if not alive:
        return
    time_left = time_left - 1
    draw_hud()
    if time_left <= 0:
        alive = False
        mole.hideturtle()
        hud.goto(0, 40)
        hud.write(f"时间到！最终得分 {score}", align="center", font=("Arial", 28, "bold"))
        screen.update()
        return
    screen.ontimer(tick_timer, 1000)
def mole_wander():
    if not alive:
        return
    jump_mole()
    screen.ontimer(mole_wander, 1400)

draw_hud()
jump_mole()
screen.onscreenclick(hit)
screen.ontimer(tick_timer, 1000)
screen.ontimer(mole_wander, 1400)
turtle.done()
"""

CHALLENGE = STEP4.replace(
    "    screen.ontimer(mole_wander, 1400)",
    "    wait = max(500, 1400 - score * 80)\n    screen.ontimer(mole_wander, wait)",
)

STEPS = [
    {
        "n": 1,
        "title": "地鼠出现",
        "goal": "棕色窗口里，一只橙色地鼠出现在随机位置。",
        "why": "randint 含两端。goto 是瞬移换洞。tracer(0) 要配 update，否则窗口是黑的。",
        "where": [
            "开头两行 import",
            "创建 screen 和 mole，全部 penup",
            "随机坐标 goto，再 update 和 done",
        ],
        "see": "窗口里一只橙色大海龟，每次运行位置可能不同。这时点它没反应。",
        "pitfall": "写了 tracer(0) 却忘了 update，窗口一片黑。",
        "talk_note": "这就是热身。让每人运行两次，看位置会变。大约 6 分钟。",
        "type_note": "从 import 写到 done。确认看见地鼠再翻页。",
        "type_hint": "mole 随机 goto。tracer(0) 后面一定要有 screen.update()。",
        "code": STEP1,
    },
    {
        "n": 2,
        "title": "点中加分",
        "goal": "点到地鼠附近 40 像素内：分数 +1，地鼠立刻换洞。",
        "why": "鼠标很难点到正中心。用 distance < 阈值，不要写 xcor()==x。",
        "where": [
            "加 score、hud、jump_mole、draw_hud、hit",
            "hit 里要写 global score",
            "onscreenclick(hit)，函数名不要加括号",
        ],
        "see": "点中橙色地鼠，头顶分数 +1，地鼠跳到别处。点空了没反应。",
        "pitfall": "写成 onscreenclick(hit())，点击没反应。",
        "talk_note": "让学生点空和点中对比。问：阈值写成 5 会怎样？下一步仍用 40。大约 10 分钟。",
        "type_note": "distance 这一行读出声：地鼠到点击点的距离。",
        "type_hint": "hit 里 distance < 40 就加分并 jump_mole()。hit 开头写 global score。",
        "ask": "阈值写成 5 会怎样？写成 200 会怎样？",
        "code": STEP2,
    },
    {
        "n": 3,
        "title": "30 秒倒计时",
        "goal": "头顶同时显示剩余秒数。到 0 写出最终得分，游戏停。",
        "why": "while True 会卡死窗口。倒计时用 ontimer 自己叫自己，间隔 1000 毫秒。",
        "where": [
            "score 旁边加 time_left = 30 和 alive = True",
            "加 tick_timer：减 1，到 0 就停",
            "done 之前 ontimer(tick_timer, 1000)",
        ],
        "see": "头顶「剩余 xx 秒」往下减。到 0 出现「时间到！最终得分」。",
        "pitfall": "tick_timer 末尾忘了再约自己，倒计时只跳一次。",
        "talk_note": "强调不要 while True。让全班看完 5 秒确认在减。大约 10 分钟。",
        "type_note": "到 0 之后 return，不要再 ontimer。",
        "type_hint": "tick_timer 每秒减 1。末尾要 ontimer。到 0 就 return。",
        "code": STEP3,
    },
    {
        "n": 4,
        "title": "地鼠自己换洞",
        "goal": "即使你不点，地鼠大约 1.4 秒也会自己跳一次。",
        "why": "打地鼠要有紧张感。mole_wander 也是 ontimer 自己叫自己。",
        "where": [
            "加 mole_wander：先 jump_mole，再约 1400 毫秒后自己",
            "启动时 ontimer(mole_wander, 1400)",
        ],
        "see": "地鼠自己会换洞。点中立刻跳；不点也会跳。30 秒结束。",
        "pitfall": "wander 里不判断 alive，时间到了地鼠还在跳。",
        "talk_note": "这是过关线。加码才把间隔跟分数挂钩。大约 8 分钟。",
        "type_note": "mole_wander 只有几行。打完先玩一局。",
        "type_hint": "mole_wander 里 jump_mole，再 ontimer 1400。开头也要判断 alive。",
        "code": STEP4,
    },
]

LESSON = {
    "n": 3,
    "title": "点哪里打哪里",
    "icon": "🐹",
    "project": "打地鼠",
    "header": HEADER,
    "final": STEP4,
    "io": "橙色地鼠随机出现。\n点中 +1 分并立刻换洞。\n30 秒到，弹出最终得分。",
    "pass_line": "点中地鼠能加分，30 秒会结束。",
    "start_cards": [
        ("1. 新建文件", "保存为 <span class=\"ic\">lesson3.py</span>。今天从头写到尾，只用这一份。"),
        ("2. 带着第 2 课", "函数名不加括号。今天点击用 <span class=\"ic\">onscreenclick</span>，倒计时用 <span class=\"ic\">ontimer</span>。"),
        ("3. 每一步都要运行", "打完这一步就点运行。跑通再翻下一步。"),
    ],
    "cover_note": "今天把点击和随机坐标做成游戏。翻一页，打一段，运行一次。",
    "product_note": "先演示打地鼠 10 秒，再让学生关窗口、打开空文件。",
    "start_note": "口答：第 2 课方向键名字为什么是 Up 不是 up。有人还在 lesson2.py 里接着写，让他新建。",
    "map_note": "第 2 步是核心判定。掉队的人停在当前步。",
    "errors": [
        ("onscreenclick(hit())", "onscreenclick(hit)", "加括号会立刻调用"),
        ("while True 倒计时", "ontimer(tick_timer, 1000)", "死循环会卡死窗口"),
        ("阈值写成 5", "distance < 40", "贴着也点不中"),
    ],
    "errors_note": "卡死窗口几乎一定是 while True。倒计时必须用 ontimer。",
    "challenge_code": CHALLENGE,
    "challenge_must_contain": "1400 - score",
    "challenge_title": "地鼠越打越快",
    "challenge_lede": "主游戏能玩之后：换洞等待改成 max(500, 1400 - score * 80)。分数越高跳得越勤。",
    "challenge_see": "打中越多，地鼠换洞越快，最快 0.5 秒一次。",
    "challenge_note": "巡堂。没做完主游戏不要跳加码。",
    "ex": [
        ("更难", "命中范围改 25"),
        ("改时限", "15 秒极速"),
        ("点空扣分", "没命中 score -= 1"),
        ("换形状", 'shape("circle")'),
    ],
    "ex_note": "改数字最适合这个时间点。",
    "sum_rows": [
        ("randint + goto", "换位置", "地鼠换洞"),
        ("distance", "点中判定", "阈值自己定"),
        ("ontimer", "闹钟", "倒计时 / 换洞"),
    ],
    "sum_note": "抽人讲为什么不用 while True。预告第 4 课金币会自己往下掉。",
    "next_line": "第 4 课：游戏循环 — 金币自己往下掉",
    "next_short": "让画面自己动 — 接住金币",
    "print_know": [
        ("random.randint", "随机整数", "mole.goto(randint(...))"),
        ("distance", "两点距离", "mole.distance(x, y)"),
        ("ontimer", "毫秒后调用", "screen.ontimer(tick, 1000)"),
        ("tracer(0)", "手动刷新", "配合 update()"),
        ("hideturtle", "藏起来", "打中后可先藏"),
    ],
    "print_blanks": [
        "1. 随机整数用 random.________",
        "2. 点中判定：mole.________(x, y) < 40",
        "3. 每秒执行一次用 screen.________(函数, 1000)",
        "4. 卡死窗口的写法是 ________ True（不要用）",
        "5. 本课倒计时是 ________ 秒",
        "6. 点击事件函数要接收 ________ 和 y",
    ],
    "print_challenge": "主游戏能玩之后，换洞等待改成 <span class=\"mono\">max(500, 1400 - score * 80)</span>。",
    "print_times": [
        ("0–8", "看成品，新建 lesson3.py"),
        ("8–35", "第 1～2 步（出现、点中加分）"),
        ("35–65", "第 3～4 步（倒计时、自己换洞）"),
        ("65–82", "加码：越打越快（选做）"),
        ("82–90", "改错 + 填空 + 小结"),
    ],
    "steps": STEPS,
}

if __name__ == "__main__":
    write_outputs(LESSON)
