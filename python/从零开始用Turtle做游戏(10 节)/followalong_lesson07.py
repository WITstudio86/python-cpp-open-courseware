#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""第 7 课跟打数据。"""
from __future__ import annotations

from followalong_engine import write_outputs

HEADER = """\
# ============================================
# 第 7 课  发射！
# 小游戏：打气球
# 知识：列表里装子弹和气球、空格开火、打中删除
# 操作：左右移动，空格发射；打到气球得分
#       漏掉 8 个气球就结束
# ============================================

"""

STEP1 = """\
import turtle
import random

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 7 课 · 打气球")
screen.bgcolor("navy")
screen.tracer(0)
vx = 0
cannon = turtle.Turtle()
cannon.shape("triangle")
cannon.color("skyblue")
cannon.penup()
cannon.goto(0, -250)
cannon.setheading(90)

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
    cannon.setx(cannon.xcor() + vx)
    if cannon.xcor() > 370:
        cannon.setx(370)
    if cannon.xcor() < -370:
        cannon.setx(-370)
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
screen.title("第 7 课 · 打气球")
screen.bgcolor("navy")
screen.tracer(0)
vx = 0
cool = 0
cannon = turtle.Turtle()
cannon.shape("triangle")
cannon.color("skyblue")
cannon.penup()
cannon.goto(0, -250)
cannon.setheading(90)
bullets = []

def make_bullet():
    shot = turtle.Turtle()
    shot.shape("square")
    shot.shapesize(0.4, 0.8)
    shot.color("yellow")
    shot.penup()
    shot.goto(cannon.xcor(), cannon.ycor() + 20)
    shot.setheading(90)
    bullets.append(shot)
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
    if cool <= 0 and len(bullets) < 4:
        make_bullet()
        cool = 10
def tick():
    global cool
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
"""

STEP3 = """\
import turtle
import random

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 7 课 · 打气球")
screen.bgcolor("navy")
screen.tracer(0)
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
    if cool <= 0 and len(bullets) < 4:
        make_bullet()
        cool = 10
def tick():
    global cool
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
        balloon.sety(balloon.ycor() - 2)
        balloon.left(2)
        if balloon.ycor() < -280:
            reset_balloon(balloon)
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
"""

STEP4 = """\
import turtle
import random

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 7 课 · 打气球")
screen.bgcolor("navy")
screen.tracer(0)
score = 0
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
    if cool <= 0 and len(bullets) < 4:
        make_bullet()
        cool = 10
def draw_hud():
    hud.clear()
    hud.goto(0, 250)
    hud.write(f"打中 {score}    空格发射", align="center", font=("Arial", 18, "bold"))
def tick():
    global cool, score
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
        balloon.sety(balloon.ycor() - 2)
        balloon.left(2)
        if balloon.ycor() < -280:
            reset_balloon(balloon)
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
"""

STEP5 = """\
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
"""

CHALLENGE = STEP5.replace(
    "                score = score + 1",
    """                if balloon.pencolor() == "red":
                    score = score + 3
                else:
                    score = score + 1""",
)

STEPS = [
    {
        "n": 1,
        "title": "炮台能走",
        "goal": "深蓝窗口，底部一个朝上的三角炮台，按住左右能走。",
        "why": "和第 4、6 课一样：vx + tick。炮台常驻，子弹等下一步再造。",
        "where": [
            "创建 cannon，放到 (0, -250)，朝上",
            "三个按键函数 + tick",
            "listen 后绑键",
        ],
        "see": "底部青色三角左右滑动。这时空格还没反应。",
        "pitfall": "忘了 setheading(90)，三角横着。",
        "talk_note": "复习列表和 vx。大约 5 分钟。",
        "type_note": "从 import 写到 done。能走再翻页。",
        "type_hint": "炮台放底部，setheading(90)。press_left 改 vx。",
        "code": STEP1,
    },
    {
        "n": 2,
        "title": "空格发射",
        "goal": "按空格射出黄点，飞出屏幕就删掉。",
        "why": "子弹是临时工。按一次键 new 一只，append 进列表。边遍历边删要写成 bullets[:]。",
        "where": [
            "加 bullets = []、cool = 0、make_bullet、fire",
            "tick 里 for shot in bullets[:]：forward，出屏 hideturtle+remove",
            "绑 space",
        ],
        "see": "空格射出黄点往上飞，到顶消失。连按太快会被冷却拦住。",
        "pitfall": "写成 for shot in bullets: remove，会漏删。",
        "talk_note": "黑板上写 [:] 的原因。强调子弹也要 penup。大约 12 分钟。",
        "type_note": "make_bullet 从炮台位置出发。cool=10 大约 0.2 秒。",
        "type_hint": "for shot in bullets[:] 再 remove。子弹一定 penup。空格键名字是 space。",
        "code": STEP2,
    },
    {
        "n": 3,
        "title": "气球往下飘",
        "goal": "天上 5 个彩色圆往下飘，掉出底部就送回天上。",
        "why": "和第 6 课陨石同一句型。reset 循环利用，不要 hideturtle 丢掉。",
        "where": [
            "加 COLORS 和 balloons 列表，循环 5 次",
            "加 reset_balloon",
            "tick 里气球 y 减 2，掉出就 reset",
        ],
        "see": "5 个彩圆往下飘并慢慢转。打中它们还没反应。",
        "pitfall": "气球忘了 penup，满屏彩线。",
        "talk_note": "颜色用 random.choice。大约 8 分钟。",
        "type_note": "和陨石几乎一样，只是名字换成 balloon。",
        "type_hint": "5 个气球装进列表。掉出 -280 就 reset_balloon。每只都要 penup。",
        "code": STEP3,
    },
    {
        "n": 4,
        "title": "打中加分",
        "goal": "子弹碰到气球：分数 +1，子弹消失，气球回天上。",
        "why": "两层循环：每个气球对每颗子弹测 distance。打中两边都要处理。",
        "where": [
            "加 score 和 hud",
            "气球循环里再 for shot in bullets[:]",
            "distance < 22 就加分、删子弹、reset 气球",
        ],
        "see": "打中彩圆分数 +1，气球跳回天上。",
        "pitfall": "只删子弹不 reset 气球，屏幕上留下幽灵圆。",
        "talk_note": "打中要 break，避免一颗子弹打两个。大约 10 分钟。",
        "type_note": "tick 开头 global cool, score。",
        "type_hint": "两层 for。distance < 22 就加分，子弹 hideturtle+remove，气球 reset。",
        "code": STEP4,
    },
    {
        "n": 5,
        "title": "漏 8 个结束",
        "goal": "气球漏到底部 missed+1；漏满 8 个游戏结束。",
        "why": "和第 4 课漏金币一样。alive 关掉后 tick 开头 return。分数高了气球掉得稍快。",
        "where": [
            "加 missed、alive",
            "掉出时 missed+1，满 8 结束",
            "fire 里加 if alive",
        ],
        "see": "头顶「漏掉 n/8」。漏满 8 个出现「气球飘走太多了」。",
        "pitfall": "结束之后还能发射。fire 里要判断 alive。",
        "talk_note": "这是过关线。让全班打中几个再故意漏完。大约 8 分钟。",
        "type_note": "hud 改成带漏掉数。结束 return。",
        "type_hint": "漏满 8 个就停。fire 里加 if alive。下落改成 2 + score // 8。",
        "code": STEP5,
    },
]

LESSON = {
    "n": 7,
    "title": "发射！",
    "icon": "🎈",
    "project": "打气球",
    "header": HEADER,
    "final": STEP5,
    "io": "左右移动三角炮台，空格发射。\n打中气球 +1，气球漏到底部 missed+1。\n漏 8 个结束。",
    "pass_line": "能发射、能打中气球，漏 8 个结束。",
    "start_cards": [
        ("1. 新建文件", "保存为 <span class=\"ic\">lesson7.py</span>。今天从头写到尾，只用这一份。"),
        ("2. 带着第 6 课", "敌人用列表。<span class=\"ic\">for x in xs[:]</span> 才能边遍历边删。"),
        ("3. 每一步都要运行", "打完这一步就点运行。跑通再翻下一步。"),
    ],
    "cover_note": "今天子弹会出现又消失。翻一页，打一段，运行一次。",
    "product_note": "先演示打气球，再让学生关窗口、打开空文件。",
    "start_note": "口答：第 6 课陨石掉出为什么不删除。有人还在 lesson6.py 里接着写，让他新建。",
    "map_note": "第 2 步 [:] 是核心。掉队的人停在当前步。",
    "errors": [
        ("for shot in bullets: remove", "for shot in bullets[:]", "否则漏删"),
        ("子弹没 penup", "penup()", "拖一条黄线"),
        ("没有冷却", "cool = 10", "机关枪卡死"),
    ],
    "errors_note": "漏删用 [:]。卡成幻灯片是没冷却。",
    "challenge_code": CHALLENGE,
    "challenge_must_contain": "pencolor",
    "challenge_title": "彩球不同分",
    "challenge_lede": "主游戏能玩之后：打中时如果 balloon.pencolor() == \"red\" 就 +3，否则 +1。",
    "challenge_see": "打中红气球一次加 3 分。",
    "challenge_note": "创建气球时也要赋 points，否则第一批红球还是 1 分。reset 会在第一次打中后生效。可提醒他们游戏一开始就 reset 一次。",
    "ex": [
        ("更少子弹", "同时最多 2 发"),
        ("更大气球", "更容易打"),
        ("更狠", "漏 5 个结束"),
        ("圆形子弹", 'shape("circle")'),
    ],
    "ex_note": "改数字最适合这个时间点。",
    "sum_rows": [
        ("创建子弹", "append", "按键工厂"),
        ("删除", "[:] + remove", "飞出 / 打中"),
        ("冷却", "cool", "别卡成幻灯片"),
    ],
    "sum_note": "抽人讲为什么 for x in xs[:] 。预告第 8 课双人对打。",
    "next_line": "第 8 课：双人对打 — 乒乓球",
    "next_short": "对打 — 乒乓球大战",
    "print_know": [
        ("append 子弹", "按键创建", "bullets.append(shot)"),
        ("[:]", "浅拷贝列表", "for x in xs[:]"),
        ("remove + hideturtle", "先藏再删", "否则留幽灵"),
        ("冷却 cool", "隔几帧才能再射", "cool = 10"),
        ("双层 for", "每颗子弹对每个气球", "打中都删除"),
    ],
    "print_blanks": [
        "1. 遍历时要删除，应该写 for x in xs.________",
        "2. 子弹飞出屏幕要 hideturtle 再 ________",
        "3. 限制连发的变量通常叫 ________",
        "4. 子弹忘了 penup 会拖出一条 ________",
        "5. [:] 的作用是 ________ 一份列表再遍历",
        "6. 本课漏掉 ________ 个气球结束",
    ],
    "print_challenge": "主游戏能玩之后，打中时如果 <span class=\"mono\">balloon.pencolor() == \"red\"</span> 就 +3 分，否则 +1。",
    "print_times": [
        ("0–8", "看成品，新建 lesson7.py"),
        ("8–35", "第 1～3 步（炮台、发射、气球）"),
        ("35–65", "第 4～5 步（打中、漏掉结束）"),
        ("65–82", "加码：彩球不同分（选做）"),
        ("82–90", "改错 + 填空 + 小结"),
    ],
    "steps": STEPS,
}

if __name__ == "__main__":
    write_outputs(LESSON)
