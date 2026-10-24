#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""第 8 课跟打数据。"""
from __future__ import annotations

from followalong_engine import write_outputs

HEADER = """\
# ============================================
# 第 8 课  对打
# 小游戏：乒乓球大战
# 知识：挡板、反弹、双人键位、先到 5 分获胜
# 操作：左边 W / S，右边 上 / 下
# ============================================

"""

STEP1 = """\
import turtle

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 8 课 · 乒乓球大战")
screen.bgcolor("navy")
screen.tracer(0)
left = turtle.Turtle()
left.shape("square")
left.color("white")
left.shapesize(5, 0.8)
left.penup()
left.goto(-350, 0)
right = turtle.Turtle()
right.shape("square")
right.color("white")
right.shapesize(5, 0.8)
right.penup()
right.goto(350, 0)
ball = turtle.Turtle()
ball.shape("circle")
ball.color("yellow")
ball.penup()
ball_dx = 4
ball_dy = 3

def tick():
    global ball_dx, ball_dy
    ball.setx(ball.xcor() + ball_dx)
    ball.sety(ball.ycor() + ball_dy)
    screen.update()
    screen.ontimer(tick, 16)

screen.ontimer(tick, 16)
turtle.done()
"""

STEP2 = """\
import turtle

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 8 课 · 乒乓球大战")
screen.bgcolor("navy")
screen.tracer(0)
left = turtle.Turtle()
left.shape("square")
left.color("white")
left.shapesize(5, 0.8)
left.penup()
left.goto(-350, 0)
right = turtle.Turtle()
right.shape("square")
right.color("white")
right.shapesize(5, 0.8)
right.penup()
right.goto(350, 0)
ball = turtle.Turtle()
ball.shape("circle")
ball.color("yellow")
ball.penup()
ball_dx = 4
ball_dy = 3

def tick():
    global ball_dx, ball_dy
    ball.setx(ball.xcor() + ball_dx)
    ball.sety(ball.ycor() + ball_dy)
    if ball.ycor() > 280:
        ball.sety(280)
        ball_dy = ball_dy * -1
    if ball.ycor() < -280:
        ball.sety(-280)
        ball_dy = ball_dy * -1
    screen.update()
    screen.ontimer(tick, 16)

screen.ontimer(tick, 16)
turtle.done()
"""

STEP3 = """\
import turtle

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 8 课 · 乒乓球大战")
screen.bgcolor("navy")
screen.tracer(0)
left_v = 0
right_v = 0
left = turtle.Turtle()
left.shape("square")
left.color("white")
left.shapesize(5, 0.8)
left.penup()
left.goto(-350, 0)
right = turtle.Turtle()
right.shape("square")
right.color("white")
right.shapesize(5, 0.8)
right.penup()
right.goto(350, 0)
ball = turtle.Turtle()
ball.shape("circle")
ball.color("yellow")
ball.penup()
ball_dx = 4
ball_dy = 3

def press_w():
    global left_v
    left_v = 7
def stop_w():
    global left_v
    left_v = 0
def press_s():
    global left_v
    left_v = -7
def stop_s():
    global left_v
    left_v = 0
def press_up():
    global right_v
    right_v = 7
def stop_up():
    global right_v
    right_v = 0
def press_down():
    global right_v
    right_v = -7
def stop_down():
    global right_v
    right_v = 0
def tick():
    global ball_dx, ball_dy
    left.sety(left.ycor() + left_v)
    if left.ycor() > 230:
        left.sety(230)
    if left.ycor() < -230:
        left.sety(-230)
    right.sety(right.ycor() + right_v)
    if right.ycor() > 230:
        right.sety(230)
    if right.ycor() < -230:
        right.sety(-230)
    ball.setx(ball.xcor() + ball_dx)
    ball.sety(ball.ycor() + ball_dy)
    if ball.ycor() > 280:
        ball.sety(280)
        ball_dy = ball_dy * -1
    if ball.ycor() < -280:
        ball.sety(-280)
        ball_dy = ball_dy * -1
    if ball.xcor() < -330 and left.distance(ball) < 70:
        ball.setx(-330)
        ball_dx = 4
    if ball.xcor() > 330 and right.distance(ball) < 70:
        ball.setx(330)
        ball_dx = -4
    screen.update()
    screen.ontimer(tick, 16)

screen.listen()
screen.onkeypress(press_w, "w")
screen.onkeyrelease(stop_w, "w")
screen.onkeypress(press_s, "s")
screen.onkeyrelease(stop_s, "s")
screen.onkeypress(press_up, "Up")
screen.onkeyrelease(stop_up, "Up")
screen.onkeypress(press_down, "Down")
screen.onkeyrelease(stop_down, "Down")
screen.ontimer(tick, 16)
turtle.done()
"""

STEP4 = """\
import turtle

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 8 课 · 乒乓球大战")
screen.bgcolor("navy")
screen.tracer(0)
left_score = 0
right_score = 0
left_v = 0
right_v = 0
left = turtle.Turtle()
left.shape("square")
left.color("white")
left.shapesize(5, 0.8)
left.penup()
left.goto(-350, 0)
right = turtle.Turtle()
right.shape("square")
right.color("white")
right.shapesize(5, 0.8)
right.penup()
right.goto(350, 0)
ball = turtle.Turtle()
ball.shape("circle")
ball.color("yellow")
ball.penup()
ball_dx = 4
ball_dy = 3
hud = turtle.Turtle()
hud.hideturtle()
hud.penup()
hud.color("white")

def press_w():
    global left_v
    left_v = 7
def stop_w():
    global left_v
    left_v = 0
def press_s():
    global left_v
    left_v = -7
def stop_s():
    global left_v
    left_v = 0
def press_up():
    global right_v
    right_v = 7
def stop_up():
    global right_v
    right_v = 0
def press_down():
    global right_v
    right_v = -7
def stop_down():
    global right_v
    right_v = 0
def draw_hud():
    hud.clear()
    hud.goto(0, 250)
    hud.write(f"{left_score}          {right_score}", align="center", font=("Arial", 22, "bold"))
def reset_ball(direction):
    global ball_dx, ball_dy
    ball.goto(0, 0)
    ball_dx = 4 * direction
    ball_dy = 3
def tick():
    global ball_dx, ball_dy, left_score, right_score
    left.sety(left.ycor() + left_v)
    if left.ycor() > 230:
        left.sety(230)
    if left.ycor() < -230:
        left.sety(-230)
    right.sety(right.ycor() + right_v)
    if right.ycor() > 230:
        right.sety(230)
    if right.ycor() < -230:
        right.sety(-230)
    ball.setx(ball.xcor() + ball_dx)
    ball.sety(ball.ycor() + ball_dy)
    if ball.ycor() > 280:
        ball.sety(280)
        ball_dy = ball_dy * -1
    if ball.ycor() < -280:
        ball.sety(-280)
        ball_dy = ball_dy * -1
    if ball.xcor() < -330 and left.distance(ball) < 70:
        ball.setx(-330)
        ball_dx = 4.3
    if ball.xcor() > 330 and right.distance(ball) < 70:
        ball.setx(330)
        ball_dx = -4.3
    if ball.xcor() < -390:
        right_score = right_score + 1
        reset_ball(1)
    if ball.xcor() > 390:
        left_score = left_score + 1
        reset_ball(-1)
    draw_hud()
    screen.update()
    screen.ontimer(tick, 16)

screen.listen()
screen.onkeypress(press_w, "w")
screen.onkeyrelease(stop_w, "w")
screen.onkeypress(press_s, "s")
screen.onkeyrelease(stop_s, "s")
screen.onkeypress(press_up, "Up")
screen.onkeyrelease(stop_up, "Up")
screen.onkeypress(press_down, "Down")
screen.onkeyrelease(stop_down, "Down")
screen.ontimer(tick, 16)
turtle.done()
"""

STEP5 = """\
import turtle

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 8 课 · 乒乓球大战")
screen.bgcolor("navy")
screen.tracer(0)
left_score = 0
right_score = 0
alive = True
left_v = 0
right_v = 0
left = turtle.Turtle()
left.shape("square")
left.color("white")
left.shapesize(5, 0.8)
left.penup()
left.goto(-350, 0)
right = turtle.Turtle()
right.shape("square")
right.color("white")
right.shapesize(5, 0.8)
right.penup()
right.goto(350, 0)
ball = turtle.Turtle()
ball.shape("circle")
ball.color("yellow")
ball.penup()
ball_dx = 4
ball_dy = 3
hud = turtle.Turtle()
hud.hideturtle()
hud.penup()
hud.color("white")

def press_w():
    global left_v
    left_v = 7
def stop_w():
    global left_v
    left_v = 0
def press_s():
    global left_v
    left_v = -7
def stop_s():
    global left_v
    left_v = 0
def press_up():
    global right_v
    right_v = 7
def stop_up():
    global right_v
    right_v = 0
def press_down():
    global right_v
    right_v = -7
def stop_down():
    global right_v
    right_v = 0
def draw_hud():
    hud.clear()
    hud.goto(0, 250)
    hud.write(f"{left_score}    先到 5 分    {right_score}", align="center", font=("Arial", 22, "bold"))
def reset_ball(direction):
    global ball_dx, ball_dy
    ball.goto(0, 0)
    ball_dx = 4 * direction
    ball_dy = 3
def finish(winner):
    global alive
    alive = False
    hud.goto(0, 20)
    hud.write(winner, align="center", font=("Arial", 28, "bold"))
def tick():
    global ball_dx, ball_dy, left_score, right_score
    if not alive:
        screen.update()
        return
    left.sety(left.ycor() + left_v)
    if left.ycor() > 230:
        left.sety(230)
    if left.ycor() < -230:
        left.sety(-230)
    right.sety(right.ycor() + right_v)
    if right.ycor() > 230:
        right.sety(230)
    if right.ycor() < -230:
        right.sety(-230)
    ball.setx(ball.xcor() + ball_dx)
    ball.sety(ball.ycor() + ball_dy)
    if ball.ycor() > 280:
        ball.sety(280)
        ball_dy = ball_dy * -1
    if ball.ycor() < -280:
        ball.sety(-280)
        ball_dy = ball_dy * -1
    if ball.xcor() < -330 and left.distance(ball) < 70:
        ball.setx(-330)
        ball_dx = abs(ball_dx) + 0.3
    if ball.xcor() > 330 and right.distance(ball) < 70:
        ball.setx(330)
        ball_dx = -(abs(ball_dx) + 0.3)
    if ball.xcor() < -390:
        right_score = right_score + 1
        reset_ball(1)
        if right_score >= 5:
            draw_hud()
            finish("右边获胜！")
            screen.update()
            return
    if ball.xcor() > 390:
        left_score = left_score + 1
        reset_ball(-1)
        if left_score >= 5:
            draw_hud()
            finish("左边获胜！")
            screen.update()
            return
    draw_hud()
    screen.update()
    screen.ontimer(tick, 16)

screen.listen()
screen.onkeypress(press_w, "w")
screen.onkeyrelease(stop_w, "w")
screen.onkeypress(press_s, "s")
screen.onkeyrelease(stop_s, "s")
screen.onkeypress(press_up, "Up")
screen.onkeyrelease(stop_up, "Up")
screen.onkeypress(press_down, "Down")
screen.onkeyrelease(stop_down, "Down")
screen.ontimer(tick, 16)
turtle.done()
"""

CHALLENGE = STEP5.replace(
    """    right.sety(right.ycor() + right_v)
    if right.ycor() > 230:
        right.sety(230)
    if right.ycor() < -230:
        right.sety(-230)""",
    """    right.sety(ball.ycor())
    if right.ycor() > 230:
        right.sety(230)
    if right.ycor() < -230:
        right.sety(-230)""",
)

STEPS = [
    {
        "n": 1,
        "title": "挡板和球",
        "goal": "两块白挡板，中间一颗黄球自己飞。",
        "why": "速度拆成 ball_dx、ball_dy。每帧加到 x、y 上，就是在飞。",
        "where": [
            "创建 left、right、ball",
            "ball_dx = 4，ball_dy = 3",
            "tick 里球加 dx dy，再 update、ontimer",
        ],
        "see": "黄球斜着飞出窗口。挡板还不会动。",
        "pitfall": "tick 忘了 global ball_dx，下一步反弹会报错。",
        "talk_note": "这就是热身舞台。大约 6 分钟。",
        "type_note": "两块挡板 shapesize(5, 0.8) 是竖条。",
        "type_hint": "挡板放 x=-350 和 350。tick 里球加 ball_dx 和 ball_dy。",
        "code": STEP1,
    },
    {
        "n": 2,
        "title": "上下墙壁反弹",
        "goal": "球碰到上下边会掉头，先拉回场内再取反。",
        "why": "反弹时先 sety 拉回，再 dy 乘 -1。否则下一帧还在墙外，会疯狂闪烁。",
        "where": [
            "tick 里两段 if：y>280 和 y<-280",
            "先 sety，再 ball_dy = ball_dy * -1",
        ],
        "see": "球在上下边来回弹。左右还是会飞出去。",
        "pitfall": "只取反不拉回，球会卡在墙里闪烁。",
        "talk_note": "让学生盯着上边看一眼。大约 6 分钟。",
        "type_note": "乘 -1 就是掉头。",
        "type_hint": "碰到上边先 sety(280)，再 dy 乘 -1。下边同样。",
        "code": STEP2,
    },
    {
        "n": 3,
        "title": "挡板能打",
        "goal": "左边 W/S，右边方向键。球碰到挡板就掉头。",
        "why": "八个小函数管两个人的速度。挡板碰撞也是 distance。打到后把球拉回场内。",
        "where": [
            "加 left_v、right_v 和八个按键函数",
            "tick 里移动挡板，四条 if 夹紧",
            "球靠近挡板则 dx 掉头",
        ],
        "see": "两人能上下移动挡板，把球打回去。",
        "pitfall": "两套键绑到同一块挡板，两人会抢。",
        "talk_note": "老师打 press_w / stop_w，其余让学生改。键名 w/s 小写，Up/Down 大写。大约 12 分钟。",
        "type_note": "八个函数长得很像。挡板夹紧用 230。",
        "type_hint": "左边 w/s，右边 Up/Down。碰到挡板先 setx 拉回，再改 ball_dx。",
        "code": STEP3,
    },
    {
        "n": 4,
        "title": "出界得分",
        "goal": "球飞出左边，右边 +1 分并重置中场。飞出右边相反。",
        "why": "出界不要让球飞丢。reset_ball 回 (0,0)，direction 决定下一次朝哪边开。",
        "where": [
            "加 left_score、right_score、hud、reset_ball",
            "x < -390 右边得分；x > 390 左边得分",
        ],
        "see": "头顶出现比分。球飞出一侧，对面得分，球回中间。",
        "pitfall": "出界不重置，球飞丢，游戏卡住。",
        "talk_note": "飞出右边界给左边加分，别弄反。大约 8 分钟。",
        "type_note": "reset_ball(1) 朝右，reset_ball(-1) 朝左。",
        "type_hint": "飞出左边 right_score+1 并 reset_ball(1)。飞出右边相反。",
        "code": STEP4,
    },
    {
        "n": 5,
        "title": "先到 5 分获胜",
        "goal": "谁先到 5 分写出获胜；挡板打到后球会稍微加速。",
        "why": "和第 5 课一样：finish 关掉 alive，tick 开头 return。加速用 abs(dx)+0.3。",
        "where": [
            "加 alive 和 finish",
            "得分之后判断 >= 5",
            "挡板反弹改成 abs(ball_dx)+0.3",
        ],
        "see": "头顶「先到 5 分」。打到后面球越来越快。有人到 5 出现获胜字。",
        "pitfall": "赢了还继续 ontimer，球还会飞。finish 之后要 return。",
        "talk_note": "这是过关线。找两人上来打一局。大约 8 分钟。",
        "type_note": "hud 改成带「先到 5 分」。加速那两行一起改。",
        "type_hint": "score >= 5 时 finish 并 return。挡板反弹用 abs(dx)+0.3。",
        "code": STEP5,
    },
]

LESSON = {
    "n": 8,
    "title": "对打",
    "icon": "🏓",
    "project": "乒乓球大战",
    "header": HEADER,
    "final": STEP5,
    "io": "左玩家 W / S，右玩家方向键。\n球碰到挡板反弹并加速。\n先得到 5 分的人获胜。",
    "pass_line": "两人能打，先到 5 分有胜负。",
    "start_cards": [
        ("1. 新建文件", "保存为 <span class=\"ic\">lesson8.py</span>。今天从头写到尾，只用这一份。"),
        ("2. 带着第 7 课", "<span class=\"ic\">distance</span> 碰撞；速度这次拆成 <span class=\"ic\">dx</span> / <span class=\"ic\">dy</span>。"),
        ("3. 每一步都要运行", "打完这一步就点运行。跑通再翻下一步。"),
    ],
    "cover_note": "今天第一次双人。翻一页，打一段，运行一次。",
    "product_note": "先演示对打 20 秒，再让学生关窗口、打开空文件。",
    "start_note": "口答：子弹为什么用 [:] 删除。有人还在 lesson7.py 里接着写，让他新建。",
    "map_note": "第 3 步键位最多。掉队的人停在当前步。",
    "errors": [
        ("反弹不拉回场内", "先 sety(280) 再取反", "否则卡墙闪烁"),
        ("两套键绑同一挡板", "left 和 right 分开", "两人会抢"),
        ("出界不重置", "reset_ball", "球飞丢"),
    ],
    "errors_note": "闪烁先查有没有拉回。球飞丢查 reset。",
    "challenge_code": CHALLENGE,
    "challenge_must_contain": "right.sety(ball.ycor())",
    "challenge_title": "右边自动挡板",
    "challenge_lede": "主游戏能玩之后：右边每帧 sety(ball.ycor())，变成单人电脑。",
    "challenge_see": "右边挡板跟着球走，一个人也能打。",
    "challenge_note": "电脑挡板几乎不会漏。想变难可以把跟随改慢。",
    "ex": [
        ("改慢", "初始 dx dy 改小"),
        ("换色", "左右挡板不同色"),
        ("快进", "先到 3 分"),
        ("红球", "ball.color('red')"),
    ],
    "ex_note": "改数字最适合这个时间点。",
    "sum_rows": [
        ("dx / dy", "速度分量", "每帧加坐标"),
        ("反弹", "取反", "墙和挡板"),
        ("双人", "两套键", "先到 5 分"),
    ],
    "sum_note": "抽人讲为什么反弹要先拉回。预告第 9 课贪吃蛇。",
    "next_line": "第 9 课：列表当身体 — 贪吃蛇",
    "next_short": "长长的身体 — 贪吃蛇",
    "print_know": [
        ("dx / dy", "水平 / 垂直速度", "每帧加到坐标上"),
        ("* -1", "取反", "撞墙反弹"),
        ("挡板", "shapesize(5, 0.8)", "竖着的长方形"),
        ("两套键", "左 W/S 右方向键", "onkeypress 两份"),
        ("先到 N 分", "本课 N=5", "写出谁赢"),
    ],
    "print_blanks": [
        "1. 把垂直速度取反：ball_dy ________ -1",
        "2. 反弹时要把球 ________ 场地内，否则会卡墙",
        "3. 左边玩家的键是 ________ 和 S",
        "4. 球飞出右边界应该给 ________ 边加分",
        "5. 先到 ________ 分获胜（本课默认）",
        "6. dx 乘 -1 会让球在 ________ 方向掉头",
    ],
    "print_challenge": "主游戏能玩之后，右边挡板每帧 <span class=\"mono\">right.sety(ball.ycor())</span>，变成电脑。",
    "print_times": [
        ("0–8", "看成品，新建 lesson8.py"),
        ("8–35", "第 1～3 步（球、反弹、挡板）"),
        ("35–65", "第 4～5 步（计分、先到 5 分）"),
        ("65–82", "加码：自动挡板（选做）"),
        ("82–90", "改错 + 填空 + 小结"),
    ],
    "steps": STEPS,
}

if __name__ == "__main__":
    write_outputs(LESSON)
