#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""第 1 课跟打数据。"""
from __future__ import annotations

from followalong_engine import write_outputs

HEADER = """\
# ============================================
# 第 1 课  海龟登场
# 小游戏：彩虹点击画家
# 知识：Screen、Turtle、前进转弯、盖章、点击
# 操作：鼠标点击画面 → 盖一只彩色小海龟
#       空格换下一种颜色    C 清屏
# ============================================

"""

STEP1 = """\
import turtle

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 1 课 · 彩虹点击画家")
screen.bgcolor("navy")
painter = turtle.Turtle()
painter.shape("turtle")
painter.color("lime")
painter.forward(100)
painter.left(90)
painter.forward(100)
painter.left(90)
painter.forward(100)
painter.left(90)
painter.forward(100)
painter.left(90)
turtle.done()
"""

STEP2 = """\
import turtle

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 1 课 · 彩虹点击画家")
screen.bgcolor("navy")
painter = turtle.Turtle()
painter.shape("turtle")
painter.color("lime")
painter.penup()
painter.goto(-120, 0)
painter.stamp()
painter.goto(0, 0)
painter.stamp()
painter.goto(120, 0)
painter.stamp()
turtle.done()
"""

STEP3 = """\
import turtle

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 1 课 · 彩虹点击画家")
screen.bgcolor("navy")
painter = turtle.Turtle()
painter.shape("turtle")
painter.color("lime")
painter.penup()

def paint(x, y):
    painter.goto(x, y)
    painter.stamp()

screen.onscreenclick(paint)
turtle.done()
"""

STEP4 = """\
import turtle

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 1 课 · 彩虹点击画家")
screen.bgcolor("navy")
PALETTE = ["red", "orange", "yellow", "lime", "cyan", "violet"]
color_index = 0
painter = turtle.Turtle()
painter.shape("turtle")
painter.color(PALETTE[0])
painter.penup()

def paint(x, y):
    painter.goto(x, y)
    painter.stamp()

def next_color():
    global color_index
    color_index = color_index + 1
    painter.color(PALETTE[color_index % len(PALETTE)])

screen.onscreenclick(paint)
screen.listen()
screen.onkeypress(next_color, "space")
turtle.done()
"""

STEP5 = """\
import turtle
import random

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 1 课 · 彩虹点击画家")
screen.bgcolor("navy")
PALETTE = ["red", "orange", "yellow", "lime", "cyan", "violet"]
color_index = 0
painter = turtle.Turtle()
painter.shape("turtle")
painter.color(PALETTE[0])
painter.penup()
hud = turtle.Turtle()
hud.hideturtle()
hud.penup()
hud.color("white")
hud.goto(0, 250)
hud.write("点击盖章  ·  空格换色  ·  C 清屏", align="center", font=("Arial", 18, "normal"))

def paint(x, y):
    painter.goto(x, y)
    painter.setheading(random.randint(0, 360))
    painter.stamp()

def next_color():
    global color_index
    color_index = color_index + 1
    painter.color(PALETTE[color_index % len(PALETTE)])

def clear_canvas():
    painter.clear()

screen.onscreenclick(paint)
screen.listen()
screen.onkeypress(next_color, "space")
screen.onkeypress(clear_canvas, "c")
turtle.done()
"""

CHALLENGE = STEP5.replace(
    """def paint(x, y):
    painter.goto(x, y)
    painter.setheading(random.randint(0, 360))
    painter.stamp()""",
    """def paint(x, y):
    painter.goto(x, y)
    for _ in range(8):
        painter.stamp()
        painter.left(45)""",
)

STEPS = [
    {
        "n": 1,
        "title": "窗口和正方形",
        "goal": "弹出深蓝窗口，绿色海龟走出一个正方形。",
        "why": "Screen 是画布，Turtle 是角色。两个都要创建。forward 走，left(90) 转直角，连走 4 次就是正方形。",
        "where": [
            "文件最开头写 import turtle",
            "先创建 screen，再创建 painter",
            "最后一行 turtle.done()，窗口才不会闪退",
        ],
        "see": "800×600 深蓝窗口，一只绿色海龟画出正方形后停在起点附近。",
        "pitfall": "忘了 turtle.done()，窗口闪一下就关。",
        "talk_note": "先让每人建好 lesson1.py。老师带着打完正方形。问：再 left(90) 四次后朝哪？大约 8 分钟。",
        "type_note": "四次 forward + left 可以一起打。跑起来看见正方形再翻页。",
        "type_hint": "从 import 写到 turtle.done()。forward(100) 和 left(90) 连写 4 次。",
        "ask": "left(90) 四次之后，海龟朝哪？",
        "code": STEP1,
    },
    {
        "n": 2,
        "title": "抬笔再盖章",
        "goal": "海龟抬笔，在三个位置各盖一个章，不拖线。",
        "why": "画画游戏一开始就要 penup。stamp 只印形状，不走线。goto 是瞬移。",
        "where": [
            "正方形那 8 行删掉，改成 penup",
            "goto 三个点，每个点 stamp 一次",
        ],
        "see": "屏幕上并排三只绿色海龟章，中间没有连线。",
        "pitfall": "忘了 penup，goto 会拖出一条线。",
        "talk_note": "对比上一步的正方形线。问 penup 和 pendown 的区别。大约 6 分钟。",
        "type_note": "三个 goto + stamp 长得像，抄完一个改坐标。",
        "type_hint": "先 penup，再 goto 三个点各 stamp 一次。",
        "ask": "penup() 和 pendown() 有什么区别？",
        "code": STEP2,
    },
    {
        "n": 3,
        "title": "点哪里盖哪里",
        "goal": "鼠标点画面，海龟走到那里盖一个章。",
        "why": "onscreenclick 会调用你的函数，并传入 x, y。函数名不要加括号，否则会立刻执行。",
        "where": [
            "三个 stamp 删掉，改成 paint 函数",
            "turtle.done() 前面写 screen.onscreenclick(paint)",
        ],
        "see": "点击画面，点一下盖一只绿色海龟。",
        "pitfall": "写成 onscreenclick(paint())，加括号会立刻调用，点击没反应。",
        "talk_note": "强调函数名不加括号。让每人点 5 下确认。大约 8 分钟。",
        "type_note": "paint 只要两行：goto 和 stamp。",
        "type_hint": "写 paint(x, y)：goto 再 stamp。onscreenclick 后面写函数名，不要加括号。",
        "code": STEP3,
    },
    {
        "n": 4,
        "title": "空格换颜色",
        "goal": "按空格，下一笔换成调色盘里的下一种颜色。",
        "why": "颜色放进列表，用下标取。% len 可以循环取，不会越界。键盘事件之前必须 listen。",
        "where": [
            "painter 上面加 PALETTE 列表和 color_index = 0",
            "加 next_color，里面要写 global color_index",
            "listen 之后绑空格",
        ],
        "see": "点几下是红色；按空格再点，变成橙色，再按变成黄色。",
        "pitfall": "改 color_index 忘了 global，颜色一直不变。",
        "talk_note": "调色盘 6 种颜色读一遍。空格的名字是 space。大约 8 分钟。",
        "type_note": "PALETTE 一行一个颜色，好打。% len(PALETTE) 一起抄。",
        "type_hint": "加上调色盘。next_color 里 global color_index。空格键名字是 space。",
        "code": STEP4,
    },
    {
        "n": 5,
        "title": "随机朝向和清屏",
        "goal": "每次盖章朝向随机；按 C 清掉所有章；头顶有操作说明。",
        "why": "setheading 随机 0～360，章不会都朝一个方向。clear 只擦章，不关窗口。C 键名字是小写 c。",
        "where": [
            "开头加 import random",
            "paint 里 stamp 之前 setheading",
            "加 hud 写说明，加 clear_canvas，绑到 c",
        ],
        "see": "点击盖的海龟朝向各不相同。按 C 画面清空，头顶字还在。",
        "pitfall": "绑成大写 C，按 C 没反应。键盘名字区分大小写。",
        "talk_note": "这是过关线。让全班点、换色、清屏各试一次。大约 8 分钟。",
        "type_note": "hud 四行：hideturtle、penup、color、goto 再 write。",
        "type_hint": "paint 里加 setheading。清屏绑小写 c。头顶写一行说明。",
        "code": STEP5,
    },
]

LESSON = {
    "n": 1,
    "title": "海龟登场",
    "icon": "🐢",
    "project": "彩虹点击画家",
    "header": HEADER,
    "final": STEP5,
    "io": "点击画面 → 盖一只彩色小海龟。\n空格 → 换下一种颜色。\nC → 清屏。",
    "pass_line": "点击能盖章，空格能换色。",
    "start_cards": [
        ("1. 新建文件", "保存为 <span class=\"ic\">lesson1.py</span>。今天从头写到尾，只用这一份。"),
        ("2. turtle 是自带的", "不用 pip。终端或 VS Code 运行 <span class=\"ic\">python3 lesson1.py</span> 就会弹窗口。"),
        ("3. 每一步都要运行", "打完这一步就点运行，对照页上的「运行后你该看到」。跑通再翻下一步。"),
    ],
    "cover_note": "第一节课先让窗口出现。翻一页，打一段，运行一次。下课要能把窗口打开给别人玩。",
    "product_note": "先演示一遍老师做好的版本，再让学生关窗口、打开空文件。不要让他们对着成品抄。",
    "start_note": "巡视文件名和运行方式。有人在交互里打，让他保存成文件。",
    "map_note": "前两步是热身并进主游戏。掉队的人停在当前步，不要跳。",
    "errors": [
        ("onscreenclick(paint())", "onscreenclick(paint)", "加括号会立刻调用，应传函数名"),
        ("忘了 turtle.done()", "最后写 turtle.done()", "否则窗口闪一下就关"),
        ("绑成大写 C", "onkeypress(..., \"c\")", "键盘名字区分大小写"),
    ],
    "errors_note": "用投影仪打错误现象，让学生在自己代码里找。",
    "challenge_code": CHALLENGE,
    "challenge_must_contain": "painter.left(45)",
    "challenge_title": "点击盖一朵花",
    "challenge_lede": "主游戏能玩之后：paint 里不要只 stamp 一次，转 8 次盖 8 瓣。",
    "challenge_see": "点一下出现一圈海龟，像一朵花。",
    "challenge_note": "巡堂。8 瓣花只要改 paint。没做完主游戏不要跳。",
    "ex": [
        ("改背景", "bgcolor 换成 black"),
        ("改形状", 'shape("circle")'),
        ("加颜色", "调色盘再加一种"),
        ("更大", "shapesize(2, 2)"),
    ],
    "ex_note": "改参数比再写新功能更适合这个时间点。",
    "sum_rows": [
        ("Screen / Turtle", "窗口和角色", "先建再玩"),
        ("forward / left", "走和转", "热身正方形"),
        ("stamp + 点击", "盖章游戏", "点哪里画哪里"),
    ],
    "sum_note": "抽两个人：一个讲 Screen 和 Turtle 的区别，一个讲为什么函数名不加括号。预告第 2 课方向键。",
    "next_line": "第 2 课：键盘控制 — 方向键开车",
    "next_short": "方向盘 — 遥控小车",
    "print_know": [
        ("import turtle", "标准库，不用 pip", "import turtle"),
        ("Screen()", "窗口", "screen.setup(800, 600)"),
        ("Turtle()", "角色", 't.shape("turtle")'),
        ("stamp()", "盖章不拖线", "先 penup 再 stamp"),
        ("onscreenclick(fn)", "点击", "fn(x, y)"),
        ("turtle.done()", "保持窗口", "写在最后"),
    ],
    "print_blanks": [
        "1. 创建窗口的类是 ________",
        "2. 让海龟前进 100：t.________(100)",
        "3. 点击事件用 screen.________(函数)",
        "4. 窗口不闪退，最后要写 ________",
        "5. 空格键的名字是 ________",
        "6. 清屏函数是 painter.________()",
    ],
    "print_challenge": "主游戏能玩之后，在 paint 里转 8 次盖 8 瓣：<span class=\"mono\">for _ in range(8): stamp(); left(45)</span>。",
    "print_times": [
        ("0–8", "看成品，新建 lesson1.py"),
        ("8–35", "第 1～3 步（正方形、盖章、点击）"),
        ("35–65", "第 4～5 步（换色、清屏）"),
        ("65–82", "加码：点击盖一朵花（选做）"),
        ("82–90", "改错 + 填空 + 小结"),
    ],
    "steps": STEPS,
}

if __name__ == "__main__":
    write_outputs(LESSON)
