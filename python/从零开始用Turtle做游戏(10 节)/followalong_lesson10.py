#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""第 10 课跟打数据。"""
from __future__ import annotations

from followalong_engine import write_outputs

HEADER = """\
# ============================================
# 第 10 课  完整作品
# 小游戏：太空大战
# 知识：状态机（菜单 / 游戏 / 结束）、生命、重开
# 操作：空格开始；左右移动；空格射击
#       被敌人撞到或漏到底部扣生命；生命 0 结束
#       R 回到菜单
# ============================================

"""

STEP1 = """\
import turtle
import random

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 10 课 · 太空大战")
screen.bgcolor("black")
screen.tracer(0)
state = "menu"
player = turtle.Turtle()
player.shape("triangle")
player.color("deepskyblue")
player.penup()
player.goto(0, -240)
player.setheading(90)
hud = turtle.Turtle()
hud.hideturtle()
hud.penup()
hud.color("white")

def show_menu():
    global state
    state = "menu"
    hud.clear()
    hud.goto(0, 80)
    hud.write("太空大战", align="center", font=("Arial", 42, "bold"))
    hud.goto(0, -20)
    hud.write("按空格开始", align="center", font=("Arial", 22, "bold"))
    screen.update()
def start_game():
    global state
    state = "play"
    hud.clear()
    player.goto(0, -240)
    player.showturtle()
def fire_or_start():
    if state == "menu":
        start_game()
def tick():
    if state != "play":
        screen.update()
        screen.ontimer(tick, 20)
        return
    screen.update()
    screen.ontimer(tick, 20)

show_menu()
screen.listen()
screen.onkeypress(fire_or_start, "space")
screen.ontimer(tick, 20)
turtle.done()
"""

STEP2 = """\
import turtle
import random

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 10 课 · 太空大战")
screen.bgcolor("black")
screen.tracer(0)
state = "menu"
vx = 0
cool = 0
player = turtle.Turtle()
player.shape("triangle")
player.color("deepskyblue")
player.penup()
player.goto(0, -240)
player.setheading(90)
bullets = []
hud = turtle.Turtle()
hud.hideturtle()
hud.penup()
hud.color("white")

def show_menu():
    global state
    state = "menu"
    hud.clear()
    hud.goto(0, 80)
    hud.write("太空大战", align="center", font=("Arial", 42, "bold"))
    hud.goto(0, -20)
    hud.write("按空格开始", align="center", font=("Arial", 22, "bold"))
    screen.update()
def start_game():
    global state
    state = "play"
    hud.clear()
    player.goto(0, -240)
    player.showturtle()
def make_bullet():
    shot = turtle.Turtle()
    shot.shape("square")
    shot.shapesize(0.3, 0.7)
    shot.color("yellow")
    shot.penup()
    shot.goto(player.xcor(), player.ycor() + 18)
    shot.setheading(90)
    bullets.append(shot)
def press_left():
    global vx
    if state == "play":
        vx = -8
def press_right():
    global vx
    if state == "play":
        vx = 8
def stop():
    global vx
    vx = 0
def fire_or_start():
    global cool
    if state == "menu":
        start_game()
        return
    if state == "play" and cool <= 0 and len(bullets) < 5:
        make_bullet()
        cool = 8
def tick():
    global cool
    if state != "play":
        screen.update()
        screen.ontimer(tick, 20)
        return
    if cool > 0:
        cool = cool - 1
    player.setx(player.xcor() + vx)
    if player.xcor() > 370:
        player.setx(370)
    if player.xcor() < -370:
        player.setx(-370)
    for shot in bullets[:]:
        shot.forward(14)
        if shot.ycor() > 310:
            shot.hideturtle()
            bullets.remove(shot)
    screen.update()
    screen.ontimer(tick, 20)

show_menu()
screen.listen()
screen.onkeypress(press_left, "Left")
screen.onkeypress(press_right, "Right")
screen.onkeyrelease(stop, "Left")
screen.onkeyrelease(stop, "Right")
screen.onkeypress(fire_or_start, "space")
screen.ontimer(tick, 20)
turtle.done()
"""

STEP3 = """\
import turtle
import random

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 10 课 · 太空大战")
screen.bgcolor("black")
screen.tracer(0)
state = "menu"
score = 0
vx = 0
cool = 0
player = turtle.Turtle()
player.shape("triangle")
player.color("deepskyblue")
player.penup()
player.goto(0, -240)
player.setheading(90)
bullets = []
enemies = []
hud = turtle.Turtle()
hud.hideturtle()
hud.penup()
hud.color("white")

def make_enemy():
    e = turtle.Turtle()
    e.shape("turtle")
    e.color("red")
    e.penup()
    e.goto(random.randint(-340, 340), random.randint(140, 280))
    e.setheading(270)
    enemies.append(e)
def make_bullet():
    shot = turtle.Turtle()
    shot.shape("square")
    shot.shapesize(0.3, 0.7)
    shot.color("yellow")
    shot.penup()
    shot.goto(player.xcor(), player.ycor() + 18)
    shot.setheading(90)
    bullets.append(shot)
def hide_all():
    for shot in bullets:
        shot.hideturtle()
    bullets.clear()
    for e in enemies:
        e.hideturtle()
    enemies.clear()
def show_menu():
    global state
    state = "menu"
    hide_all()
    hud.clear()
    hud.goto(0, 80)
    hud.write("太空大战", align="center", font=("Arial", 42, "bold"))
    hud.goto(0, -20)
    hud.write("按空格开始", align="center", font=("Arial", 22, "bold"))
    screen.update()
def start_game():
    global state, score
    state = "play"
    score = 0
    hide_all()
    player.goto(0, -240)
    for _ in range(4):
        make_enemy()
    hud.clear()
def press_left():
    global vx
    if state == "play":
        vx = -8
def press_right():
    global vx
    if state == "play":
        vx = 8
def stop():
    global vx
    vx = 0
def fire_or_start():
    global cool
    if state == "menu":
        start_game()
        return
    if state == "play" and cool <= 0 and len(bullets) < 5:
        make_bullet()
        cool = 8
def draw_hud():
    hud.clear()
    hud.goto(0, 250)
    hud.write(f"得分 {score}", align="center", font=("Arial", 18, "bold"))
def tick():
    global cool, score
    if state != "play":
        screen.update()
        screen.ontimer(tick, 20)
        return
    if cool > 0:
        cool = cool - 1
    player.setx(player.xcor() + vx)
    if player.xcor() > 370:
        player.setx(370)
    if player.xcor() < -370:
        player.setx(-370)
    for shot in bullets[:]:
        shot.forward(14)
        if shot.ycor() > 310:
            shot.hideturtle()
            bullets.remove(shot)
    for e in enemies[:]:
        e.sety(e.ycor() - 2)
        e.left(3)
        for shot in bullets[:]:
            if e.distance(shot) < 20:
                score = score + 10
                shot.hideturtle()
                bullets.remove(shot)
                e.hideturtle()
                enemies.remove(e)
                make_enemy()
                break
    draw_hud()
    screen.update()
    screen.ontimer(tick, 20)

show_menu()
screen.listen()
screen.onkeypress(press_left, "Left")
screen.onkeypress(press_right, "Right")
screen.onkeyrelease(stop, "Left")
screen.onkeyrelease(stop, "Right")
screen.onkeypress(fire_or_start, "space")
screen.ontimer(tick, 20)
turtle.done()
"""

STEP4 = """\
import turtle
import random

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 10 课 · 太空大战")
screen.bgcolor("black")
screen.tracer(0)
state = "menu"
score = 0
lives = 3
vx = 0
cool = 0
player = turtle.Turtle()
player.shape("triangle")
player.color("deepskyblue")
player.penup()
player.goto(0, -240)
player.setheading(90)
bullets = []
enemies = []
hud = turtle.Turtle()
hud.hideturtle()
hud.penup()
hud.color("white")

def make_enemy():
    e = turtle.Turtle()
    e.shape("turtle")
    e.color("red")
    e.penup()
    e.goto(random.randint(-340, 340), random.randint(140, 280))
    e.setheading(270)
    enemies.append(e)
def make_bullet():
    shot = turtle.Turtle()
    shot.shape("square")
    shot.shapesize(0.3, 0.7)
    shot.color("yellow")
    shot.penup()
    shot.goto(player.xcor(), player.ycor() + 18)
    shot.setheading(90)
    bullets.append(shot)
def hide_all():
    for shot in bullets:
        shot.hideturtle()
    bullets.clear()
    for e in enemies:
        e.hideturtle()
    enemies.clear()
def show_menu():
    global state
    state = "menu"
    hide_all()
    hud.clear()
    hud.goto(0, 80)
    hud.write("太空大战", align="center", font=("Arial", 42, "bold"))
    hud.goto(0, -20)
    hud.write("按空格开始", align="center", font=("Arial", 22, "bold"))
    screen.update()
def start_game():
    global state, score, lives
    state = "play"
    score = 0
    lives = 3
    hide_all()
    player.goto(0, -240)
    for _ in range(4):
        make_enemy()
    hud.clear()
def game_over():
    global state
    state = "over"
    hud.goto(0, 40)
    hud.write(f"任务结束  得分 {score}", align="center", font=("Arial", 28, "bold"))
    hud.goto(0, -20)
    hud.write("按 R 返回菜单", align="center", font=("Arial", 18, "normal"))
def press_left():
    global vx
    if state == "play":
        vx = -8
def press_right():
    global vx
    if state == "play":
        vx = 8
def stop():
    global vx
    vx = 0
def fire_or_start():
    global cool
    if state == "menu":
        start_game()
        return
    if state == "play" and cool <= 0 and len(bullets) < 5:
        make_bullet()
        cool = 8
def draw_hud():
    hud.clear()
    hud.goto(0, 250)
    hud.write(f"得分 {score}    生命 {lives}", align="center", font=("Arial", 18, "bold"))
def tick():
    global cool, score, lives
    if state != "play":
        screen.update()
        screen.ontimer(tick, 20)
        return
    if cool > 0:
        cool = cool - 1
    player.setx(player.xcor() + vx)
    if player.xcor() > 370:
        player.setx(370)
    if player.xcor() < -370:
        player.setx(-370)
    for shot in bullets[:]:
        shot.forward(14)
        if shot.ycor() > 310:
            shot.hideturtle()
            bullets.remove(shot)
    for e in enemies[:]:
        e.sety(e.ycor() - 2)
        e.left(3)
        if e.ycor() < -280:
            e.hideturtle()
            enemies.remove(e)
            lives = lives - 1
            make_enemy()
        if player.distance(e) < 24:
            e.hideturtle()
            enemies.remove(e)
            lives = lives - 1
            make_enemy()
        for shot in bullets[:]:
            if e.distance(shot) < 20:
                score = score + 10
                shot.hideturtle()
                bullets.remove(shot)
                e.hideturtle()
                enemies.remove(e)
                make_enemy()
                break
    if lives <= 0:
        lives = 0
        draw_hud()
        game_over()
        screen.update()
        screen.ontimer(tick, 20)
        return
    draw_hud()
    screen.update()
    screen.ontimer(tick, 20)

show_menu()
screen.listen()
screen.onkeypress(press_left, "Left")
screen.onkeypress(press_right, "Right")
screen.onkeyrelease(stop, "Left")
screen.onkeyrelease(stop, "Right")
screen.onkeypress(fire_or_start, "space")
screen.onkeypress(show_menu, "r")
screen.ontimer(tick, 20)
turtle.done()
"""

STEP5 = """\
import turtle
import random

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 10 课 · 太空大战")
screen.bgcolor("black")
screen.tracer(0)
state = "menu"
score = 0
lives = 3
vx = 0
cool = 0
wave = 1
player = turtle.Turtle()
player.shape("triangle")
player.color("deepskyblue")
player.penup()
player.goto(0, -240)
player.setheading(90)
bullets = []
enemies = []
hud = turtle.Turtle()
hud.hideturtle()
hud.penup()
hud.color("white")

def make_enemy():
    e = turtle.Turtle()
    e.shape("turtle")
    e.color("red")
    e.penup()
    e.goto(random.randint(-340, 340), random.randint(140, 280))
    e.setheading(270)
    enemies.append(e)
def make_bullet():
    shot = turtle.Turtle()
    shot.shape("square")
    shot.shapesize(0.3, 0.7)
    shot.color("yellow")
    shot.penup()
    shot.goto(player.xcor(), player.ycor() + 18)
    shot.setheading(90)
    bullets.append(shot)
def hide_all():
    for shot in bullets:
        shot.hideturtle()
    bullets.clear()
    for e in enemies:
        e.hideturtle()
    enemies.clear()
def show_menu():
    global state, score, lives, wave, vx, cool
    state = "menu"
    score = 0
    lives = 3
    wave = 1
    vx = 0
    cool = 0
    player.goto(0, -240)
    player.showturtle()
    hide_all()
    hud.clear()
    hud.goto(0, 80)
    hud.write("太空大战", align="center", font=("Arial", 42, "bold"))
    hud.goto(0, 10)
    hud.write("左右移动  ·  空格射击  ·  躲开红色敌军", align="center", font=("Arial", 16, "normal"))
    hud.goto(0, -50)
    hud.write("按空格开始", align="center", font=("Arial", 22, "bold"))
    screen.update()
def start_game():
    global state, score, lives, wave
    state = "play"
    score = 0
    lives = 3
    wave = 1
    hide_all()
    player.goto(0, -240)
    for _ in range(4):
        make_enemy()
    hud.clear()
def game_over():
    global state
    state = "over"
    hud.goto(0, 40)
    hud.write(f"任务结束  得分 {score}", align="center", font=("Arial", 28, "bold"))
    hud.goto(0, -20)
    hud.write("按 R 返回菜单", align="center", font=("Arial", 18, "normal"))
def press_left():
    global vx
    if state == "play":
        vx = -8
def press_right():
    global vx
    if state == "play":
        vx = 8
def stop():
    global vx
    vx = 0
def fire_or_start():
    global cool
    if state == "menu":
        start_game()
        return
    if state == "play" and cool <= 0 and len(bullets) < 5:
        make_bullet()
        cool = 8
def draw_hud():
    hud.clear()
    hud.goto(0, 250)
    hud.write(f"得分 {score}    生命 {lives}    波次 {wave}", align="center", font=("Arial", 18, "bold"))
def tick():
    global cool, score, lives, wave
    if state != "play":
        screen.update()
        screen.ontimer(tick, 20)
        return
    if cool > 0:
        cool = cool - 1
    player.setx(player.xcor() + vx)
    if player.xcor() > 370:
        player.setx(370)
    if player.xcor() < -370:
        player.setx(-370)
    for shot in bullets[:]:
        shot.forward(14)
        if shot.ycor() > 310:
            shot.hideturtle()
            bullets.remove(shot)
    enemy_speed = 2 + wave * 0.4
    for e in enemies[:]:
        e.sety(e.ycor() - enemy_speed)
        e.left(3)
        if e.ycor() < -280:
            e.hideturtle()
            enemies.remove(e)
            lives = lives - 1
            make_enemy()
        if player.distance(e) < 24:
            e.hideturtle()
            enemies.remove(e)
            lives = lives - 1
            make_enemy()
        for shot in bullets[:]:
            if e.distance(shot) < 20:
                score = score + 10
                shot.hideturtle()
                bullets.remove(shot)
                e.hideturtle()
                enemies.remove(e)
                make_enemy()
                break
    if score >= wave * 80:
        wave = wave + 1
        make_enemy()
    if lives <= 0:
        lives = 0
        draw_hud()
        game_over()
        screen.update()
        screen.ontimer(tick, 20)
        return
    draw_hud()
    screen.update()
    screen.ontimer(tick, 20)

show_menu()
screen.listen()
screen.onkeypress(press_left, "Left")
screen.onkeypress(press_right, "Right")
screen.onkeyrelease(stop, "Left")
screen.onkeyrelease(stop, "Right")
screen.onkeypress(fire_or_start, "space")
screen.onkeypress(show_menu, "r")
screen.ontimer(tick, 20)
turtle.done()
"""

CHALLENGE = STEP5.replace(
    """    e.color("red")
    e.penup()""",
    """    if wave >= 5:
        e.color("purple")
    else:
        e.color("red")
    e.penup()""",
)

STEPS = [
    {
        "n": 1,
        "title": "菜单和空格开始",
        "goal": "先看到菜单。按空格，大字消失，进入游戏状态。",
        "why": "state 是字符串。tick 开头如果不是 play 也要继续 ontimer，否则循环停住，再按空格没人接。",
        "where": [
            "state = \"menu\"，写 show_menu / start_game / fire_or_start",
            "tick 里 if state != \"play\" 仍要 ontimer",
            "空格绑 fire_or_start",
        ],
        "see": "打开是「太空大战 / 按空格开始」。按空格字消失，底部出现三角。",
        "pitfall": "菜单里 tick 不 ontimer，按空格开始后画面不再刷新。",
        "talk_note": "这就是热身。让每人按空格进出一次。大约 8 分钟。",
        "type_note": "菜单时也要 ontimer。空格先只负责开始。",
        "type_hint": "state 先是 menu。空格调用 start_game。tick 不是 play 也要再约自己。",
        "code": STEP1,
    },
    {
        "n": 2,
        "title": "移动和射击",
        "goal": "游戏中左右移动，空格发射黄点。菜单里空格仍是开始。",
        "why": "同一颗空格两种含义：先判断 state。子弹和第 7 课一样，[:] 删除。",
        "where": [
            "加 vx、cool、bullets、make_bullet",
            "fire_or_start 里 play 才发射",
            "tick 里移动玩家、更新子弹",
        ],
        "see": "开始后能左右走、空格射击。天上还没有敌人。",
        "pitfall": "空格不判断 state，菜单里也会射出子弹。",
        "talk_note": "强调空格两用。大约 10 分钟。",
        "type_note": "press_left 里 if state == \"play\"。子弹一定 penup。",
        "type_hint": "空格：菜单开始，游戏射击。子弹 for shot in bullets[:] 再删除。",
        "code": STEP2,
    },
    {
        "n": 3,
        "title": "敌军和打中",
        "goal": "4 只红色敌军往下掉。打中 +10 分，再补一只。",
        "why": "hide_all 先 hideturtle 再 clear 列表，否则幽灵残留。开始一局要清场再造 4 只。",
        "where": [
            "加 enemies、score、make_enemy、hide_all",
            "start_game 里造 4 只",
            "tick 里敌军下落，碰到子弹就加分",
        ],
        "see": "能打中红海龟得分。打掉一只立刻补一只。",
        "pitfall": "clear 列表不 hideturtle，屏幕上留下残影。",
        "talk_note": "清场两步：藏，再丢。大约 10 分钟。",
        "type_note": "show_menu 和 start_game 都要 hide_all。",
        "type_hint": "hide_all 先 hideturtle 再 clear。打中 +10 并 make_enemy()。",
        "code": STEP3,
    },
    {
        "n": 4,
        "title": "3 条命",
        "goal": "敌军漏到底或撞到玩家：生命 -1。生命 0 进入结束画面。R 回菜单。",
        "why": "over 也是一种 state。tick 开头不是 play 就只刷新。R 绑 show_menu。",
        "where": [
            "加 lives=3、game_over",
            "漏底或碰撞 lives-1；<=0 则 game_over",
            "绑 r 到 show_menu",
        ],
        "see": "头顶有生命。撞三次出现「任务结束」。按 R 回到菜单。",
        "pitfall": "game_over 之后 tick 不再 ontimer，按 R 菜单出来了但循环已断。",
        "talk_note": "结束时仍要 ontimer。让学生死一次再按 R。大约 10 分钟。",
        "type_note": "lives<=0 时也要 ontimer 再 return。",
        "type_hint": "漏底或碰撞扣命。命 0 进入 over。R 调用 show_menu。tick 在 over 也要 ontimer。",
        "code": STEP4,
    },
    {
        "n": 5,
        "title": "波次越来越难",
        "goal": "分数到 wave*80：波次 +1，多一只敌人，掉得更快。",
        "why": "毕业作要把前几课拼起来：菜单、射击、碰撞、列表、难度。",
        "where": [
            "加 wave=1",
            "enemy_speed = 2 + wave * 0.4",
            "score >= wave*80 则 wave+1 并 make_enemy",
        ],
        "see": "头顶有波次。打得越多敌人越多越快。能回菜单再开一局。",
        "pitfall": "wave+1 写在每帧都会进，一秒钟加几十波。要用 score >= wave*80。",
        "talk_note": "这是过关线。让全班打到第 2 波或死一次。大约 8 分钟。",
        "type_note": "菜单说明可以写三行。show_menu 复位所有变量。",
        "type_hint": "score >= wave * 80 时 wave+1 并加敌人。速度 2 + wave * 0.4。",
        "code": STEP5,
    },
]

LESSON = {
    "n": 10,
    "title": "完整作品",
    "icon": "🚀",
    "project": "太空大战",
    "header": HEADER,
    "final": STEP5,
    "io": "先看到菜单，按空格开始。\n左右移动、空格射击红色敌军。\n3 条命用完出现结束画面，R 回菜单。",
    "pass_line": "有菜单、能打、有生命、能回菜单再来一局。",
    "start_cards": [
        ("1. 新建文件", "保存为 <span class=\"ic\">lesson10.py</span>。今天从头写到尾，只用这一份。"),
        ("2. 带着前 9 课", "循环、碰撞、列表、子弹。今天用 <span class=\"ic\">state</span> 把菜单和游戏接起来。"),
        ("3. 每一步都要运行", "打完这一步就点运行。跑通再翻下一步。"),
    ],
    "cover_note": "毕业课。翻一页，打一段，运行一次。下课要能把窗口打开给别人玩。",
    "product_note": "先演示完整一局：菜单、打、死、回菜单。再让学生打开空文件。",
    "start_note": "口答：贪吃蛇为什么从尾巴往前抄。有人还在 lesson9.py 里接着写，让他新建。",
    "map_note": "第 1 步状态机是骨架。掉队的人停在当前步。",
    "errors": [
        ("菜单时敌人还在掉", "tick 开头判断 state", "否则菜单被打穿"),
        ("clear 列表不 hideturtle", "先藏再丢", "幽灵子弹"),
        ("空格不判断 state", "菜单开始 / 游戏射击", "两种含义要分支"),
    ],
    "errors_note": "菜单被打穿 = tick 没判断 state。残影 = 没 hideturtle。",
    "challenge_code": CHALLENGE,
    "challenge_must_contain": "wave >= 5",
    "challenge_title": "第 5 波敌人变紫色",
    "challenge_lede": "主游戏能玩之后：make_enemy 里如果 wave >= 5，颜色改成 purple。",
    "challenge_see": "打到第 5 波，新出现的敌人是紫色。",
    "challenge_note": "已经在场上的红色不会变，新造的才会紫。",
    "ex": [
        ("改名", "标题换成你的游戏名"),
        ("换皮", "玩家换喜欢的颜色"),
        ("更易", "初始敌人 3 个"),
        ("生命 5", "lives 初始改 5"),
    ],
    "ex_note": "改成自己的作品名，下课可以给别人玩。",
    "sum_rows": [
        ("前 3 课", "窗口/键盘/鼠标", "让海龟听话"),
        ("第 4～7 课", "循环/碰撞/列表", "让游戏自己跑"),
        ("第 8～10 课", "对打/蛇/状态机", "完整作品"),
    ],
    "sum_note": "结业。抽人讲 state 三个值。下一站可以去 Pygame。",
    "next_line": "结业！下一站可去 Pygame、语法速通或 Tkinter。",
    "next_short": "课程结束 — 去选下一门吧",
    "print_know": [
        ("状态机", "一个字符串管阶段", "menu / play / over"),
        ("生命", "lives -= 1", "到 0 进入 over"),
        ("清场", "先 hideturtle 再 clear 列表", "重开必备"),
        ("波次", "score 门槛升高", "wave += 1"),
        ("R 回菜单", "show_menu()", "再按空格新开一局"),
    ],
    "print_blanks": [
        "1. 本课用 ________ 变量区分菜单和游戏",
        "2. 空格在菜单里是开始，在游戏里是 ________",
        "3. 重开只 clear 列表不够，还要 ________ 海龟",
        "4. tick 在菜单里也要继续 ________，否则循环停住",
        "5. 三个状态是 menu、play、________",
        "6. 按 R 回到 ________ 状态",
    ],
    "print_challenge": "主游戏能玩之后，第 5 波起敌人 <span class=\"mono\">color(\"purple\")</span>。",
    "print_times": [
        ("0–8", "看成品，新建 lesson10.py"),
        ("8–35", "第 1～3 步（菜单、射击、敌军）"),
        ("35–65", "第 4～5 步（生命、波次）"),
        ("65–82", "加码：第 5 波紫色（选做）"),
        ("82–90", "改错 + 填空 + 小结"),
    ],
    "steps": STEPS,
}

if __name__ == "__main__":
    write_outputs(LESSON)
