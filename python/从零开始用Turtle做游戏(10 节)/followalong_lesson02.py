#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""第 2 课跟打数据。"""
from __future__ import annotations

from followalong_engine import write_outputs

HEADER = """\
# ============================================
# 第 2 课  方向盘
# 小游戏：遥控小车
# 知识：onkeypress、listen、setheading、边界
# 操作：方向键开车；空格加速；R 重置
# ============================================

"""

STEP1 = """\
import turtle

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 2 课 · 遥控小车")
screen.bgcolor("darkgreen")
car = turtle.Turtle()
car.shape("turtle")
car.color("lime")
car.shapesize(1.8, 1.8)
car.pensize(3)
car.penup()
car.goto(0, -180)
car.pendown()
car.setheading(90)
turtle.done()
"""

STEP2 = """\
import turtle

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 2 课 · 遥控小车")
screen.bgcolor("darkgreen")
car = turtle.Turtle()
car.shape("turtle")
car.color("lime")
car.shapesize(1.8, 1.8)
car.pensize(3)
car.penup()
car.goto(0, -180)
car.pendown()
car.setheading(90)

def go_up():
    car.setheading(90)
    car.forward(20)
def go_down():
    car.setheading(270)
    car.forward(20)
def go_left():
    car.setheading(180)
    car.forward(20)
def go_right():
    car.setheading(0)
    car.forward(20)

screen.listen()
screen.onkeypress(go_up, "Up")
screen.onkeypress(go_down, "Down")
screen.onkeypress(go_left, "Left")
screen.onkeypress(go_right, "Right")
turtle.done()
"""

STEP3 = """\
import turtle

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 2 课 · 遥控小车")
screen.bgcolor("darkgreen")
car = turtle.Turtle()
car.shape("turtle")
car.color("lime")
car.shapesize(1.8, 1.8)
car.pensize(3)
car.penup()
car.goto(0, -180)
car.pendown()
car.setheading(90)

def bounce_inside():
    if car.xcor() > 380:
        car.setx(380)
        car.setheading(180)
    if car.xcor() < -380:
        car.setx(-380)
        car.setheading(0)
    if car.ycor() > 280:
        car.sety(280)
        car.setheading(270)
    if car.ycor() < -280:
        car.sety(-280)
        car.setheading(90)
def go_up():
    car.setheading(90)
    car.forward(20)
    bounce_inside()
def go_down():
    car.setheading(270)
    car.forward(20)
    bounce_inside()
def go_left():
    car.setheading(180)
    car.forward(20)
    bounce_inside()
def go_right():
    car.setheading(0)
    car.forward(20)
    bounce_inside()

screen.listen()
screen.onkeypress(go_up, "Up")
screen.onkeypress(go_down, "Down")
screen.onkeypress(go_left, "Left")
screen.onkeypress(go_right, "Right")
turtle.done()
"""

STEP4 = """\
import turtle

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 2 课 · 遥控小车")
screen.bgcolor("darkgreen")
car = turtle.Turtle()
car.shape("turtle")
car.color("lime")
car.shapesize(1.8, 1.8)
car.pensize(3)
car.penup()
car.goto(0, -180)
car.pendown()
car.setheading(90)
hud = turtle.Turtle()
hud.hideturtle()
hud.penup()
hud.color("white")
hud.goto(0, 250)
hud.write("方向键开车  ·  空格冲刺  ·  R 重新出发", align="center", font=("Arial", 16, "normal"))

def bounce_inside():
    if car.xcor() > 380:
        car.setx(380)
        car.setheading(180)
    if car.xcor() < -380:
        car.setx(-380)
        car.setheading(0)
    if car.ycor() > 280:
        car.sety(280)
        car.setheading(270)
    if car.ycor() < -280:
        car.sety(-280)
        car.setheading(90)
def go_up():
    car.setheading(90)
    car.forward(20)
    bounce_inside()
def go_down():
    car.setheading(270)
    car.forward(20)
    bounce_inside()
def go_left():
    car.setheading(180)
    car.forward(20)
    bounce_inside()
def go_right():
    car.setheading(0)
    car.forward(20)
    bounce_inside()
def boost():
    car.forward(40)
    bounce_inside()
def reset_car():
    car.clear()
    car.penup()
    car.goto(0, -180)
    car.pendown()
    car.setheading(90)

screen.listen()
screen.onkeypress(go_up, "Up")
screen.onkeypress(go_down, "Down")
screen.onkeypress(go_left, "Left")
screen.onkeypress(go_right, "Right")
screen.onkeypress(boost, "space")
screen.onkeypress(reset_car, "r")
turtle.done()
"""

CHALLENGE = STEP4.replace(
    """hud.write("方向键开车  ·  空格冲刺  ·  R 重新出发", align="center", font=("Arial", 16, "normal"))
""",
    """hud.write("方向键开车  ·  空格冲刺  ·  R 重新出发", align="center", font=("Arial", 16, "normal"))
posts = []
for x in [-160, 0, 160]:
    post = turtle.Turtle()
    post.shape("square")
    post.color("orange")
    post.penup()
    post.goto(x, 40)
    posts.append(post)
""",
)

STEPS = [
    {
        "n": 1,
        "title": "把小车放好",
        "goal": "深绿窗口，小车在下方，朝上，落下笔准备留车辙。",
        "why": "先摆好角色再绑键。setheading(90) 是正北。pendown 之后走就会留下线。",
        "where": [
            "创建 screen 和 car",
            "penup 放到 (0, -180)，再 pendown",
            "最后 turtle.done()",
        ],
        "see": "窗口下方一只绿色海龟，头朝上。这时按键还没反应。",
        "pitfall": "忘了 pendown，后面开车没有车辙。",
        "talk_note": "复习第 1 课 Screen / Turtle。朝向 0 右 90 上 180 左 270 下，在黑板上画十字。大约 6 分钟。",
        "type_note": "从 import 写到 done。确认看见小车再翻页。",
        "type_hint": "小车放到 (0, -180)，setheading(90)，先抬笔再落笔。",
        "code": STEP1,
    },
    {
        "n": 2,
        "title": "方向键开车",
        "goal": "按一下方向键，小车转向并走 20。",
        "why": "键盘三件套：listen 开始听，onkeypress 绑函数，函数名不要加括号。这课是点一下走一格。",
        "where": [
            "四个方向函数：setheading + forward(20)",
            "listen 之后绑 Up Down Left Right",
        ],
        "see": "方向键能开车，身后留下绿色车辙。",
        "pitfall": "忘了 screen.listen()，按键完全没反应。",
        "talk_note": "老师打 go_up，其余三个让学生改数字。强调 Up 首字母大写。大约 10 分钟。",
        "type_note": "四个函数长得很像，抄完一个改朝向。",
        "type_hint": "先抄 go_up，另外三个改 heading。绑键之前一定 listen。",
        "ask": "onkeypress(go_up, ...) 能不能写成 go_up()？",
        "code": STEP2,
    },
    {
        "n": 3,
        "title": "撞墙弹回",
        "goal": "开到窗口边缘会被拉回来并掉头。",
        "why": "读 xcor / ycor 做边界。四条 if 夹紧，比一行 max/min 好读。掉头用 setheading。",
        "where": [
            "加 bounce_inside，四条 if",
            "四个开车函数末尾都调用 bounce_inside()",
        ],
        "see": "开到边上会弹回来，不会开丢。",
        "pitfall": "只判断左右，忘了上下，车会从顶上开出去。",
        "talk_note": "让学生故意开出去试。大约 8 分钟。",
        "type_note": "四条 if 可以一起打。每个 go_ 函数末尾加一行调用。",
        "type_hint": "bounce_inside 用四条 if 夹紧。每个开车函数末尾都要调用它。",
        "code": STEP3,
    },
    {
        "n": 4,
        "title": "冲刺和重置",
        "goal": "空格朝当前方向冲 40；R 清轨迹回到起点。",
        "why": "boost 不再转向，只 forward。reset 要 clear、回到 (0,-180)、再朝上。R 键是小写 r。",
        "where": [
            "加 hud 写说明",
            "加 boost 和 reset_car",
            "绑 space 和 r",
        ],
        "see": "空格冲得更远。按 R 车辙消失，小车回到下方。",
        "pitfall": "reset 里忘了 pendown，重置之后不再留车辙。",
        "talk_note": "这是过关线。让全班开一圈、冲刺、重置。大约 8 分钟。",
        "type_note": "reset_car 五步：clear、penup、goto、pendown、朝上。",
        "type_hint": "空格 forward(40)。R 清轨迹并回到 (0, -180)。键名是小写 r。",
        "code": STEP4,
    },
]

LESSON = {
    "n": 2,
    "title": "方向盘",
    "icon": "🎮",
    "project": "遥控小车",
    "header": HEADER,
    "final": STEP4,
    "io": "方向键开车，留下绿色车辙。\n空格冲刺，碰到窗口边缘弹回。\nR 清轨迹回到起点。",
    "pass_line": "方向键能开，撞墙会弹回。",
    "start_cards": [
        ("1. 新建文件", "保存为 <span class=\"ic\">lesson2.py</span>。今天从头写到尾，只用这一份。"),
        ("2. 带着第 1 课", "还记得 <span class=\"ic\">onscreenclick</span> 传函数名不加括号吗？键盘也是这样。"),
        ("3. 每一步都要运行", "打完这一步就点运行。跑通再翻下一步。"),
    ],
    "cover_note": "今天从鼠标换成键盘。翻一页，打一段，运行一次。",
    "product_note": "先演示开车和弹墙，再让学生关窗口、打开空文件。",
    "start_note": "口答：函数名为什么不加括号。有人还在 lesson1.py 里接着写，让他新建。",
    "map_note": "第 2 步是核心。掉队的人停在当前步。",
    "errors": [
        ("忘了 listen()", "screen.listen()", "窗口没获得焦点，按键没反应"),
        ("onkeypress(go_up())", "onkeypress(go_up, \"Up\")", "加括号会立刻执行"),
        ("方向键写成 up", "写成 Up", "首字母必须大写"),
    ],
    "errors_note": "按键没反应时，先查 listen，再查键名大小写。",
    "challenge_code": CHALLENGE,
    "challenge_must_contain": "posts.append(post)",
    "challenge_title": "放 3 个障碍桩",
    "challenge_lede": "主游戏能玩之后：在场地里放 3 个橙色方桩。先会摆，下一课再学碰撞。",
    "challenge_see": "场上多了 3 个橙色方块。开车能绕过去。",
    "challenge_note": "桩只要摆出来。不要在这课做碰撞。",
    "ex": [
        ("改步长", "forward 的 20 改成 30"),
        ("加粗车辙", "pensize(6)"),
        ("换车漆", "color 换成自己喜欢的"),
        ("绑 WASD", "再套一套键"),
    ],
    "ex_note": "改数字最适合这个时间点。",
    "sum_rows": [
        ("listen + onkeypress", "键盘", "先听再绑"),
        ("setheading", "朝向", "0 90 180 270"),
        ("边界", "别开丢", "读坐标再拉回"),
    ],
    "sum_note": "抽人讲 90 是哪一边。预告第 3 课鼠标打地鼠。",
    "next_line": "第 3 课：鼠标打地鼠 — 随机坐标 + 点击判定",
    "next_short": "点哪里打哪里 — 打地鼠",
    "print_know": [
        ("listen()", "窗口获得焦点并听键", "screen.listen()"),
        ("onkeypress", "按下时调用", 'onkeypress(go_up, "Up")'),
        ("heading", "0/90/180/270", "右上左下"),
        ("forward(n)", "朝当前方向走", "先 setheading 再走"),
        ("边界", "碰到边缘就回头", "if xcor() > 380"),
    ],
    "print_blanks": [
        "1. 键盘事件之前必须调用 ________()",
        "2. 方向键上的名字是 ________（Up / up）",
        "3. 正北对应 heading = ________",
        "4. onkeypress(go_up, ...) 能不能写成 go_up()？________",
        "5. 空格键的名字是 ________",
        "6. 重置键 R 要写成 ________（r / R）",
    ],
    "print_challenge": "主游戏能玩之后，用 for 循环放 3 个橙色方桩在 x = -160、0、160。",
    "print_times": [
        ("0–8", "看成品，新建 lesson2.py"),
        ("8–35", "第 1～2 步（摆车、方向键）"),
        ("35–65", "第 3～4 步（弹墙、冲刺重置）"),
        ("65–82", "加码：3 个障碍桩（选做）"),
        ("82–90", "改错 + 填空 + 小结"),
    ],
    "steps": STEPS,
}

if __name__ == "__main__":
    write_outputs(LESSON)
