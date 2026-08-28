#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Generate PPT, printable worksheets, and code-view HTML for this course."""
from __future__ import annotations

import html
from pathlib import Path

ROOT = Path(__file__).resolve().parent
CODE = ROOT / "code"
VIEW = CODE / "view"
PPT = ROOT / "ppt"
PRINT = ROOT / "打印"

COURSE = "从零开始用 Turtle 做游戏"

LESSONS = [
    {
        "n": 1,
        "title": "海龟登场",
        "subtitle": "Screen、Turtle、前进转弯、盖章、点击",
        "project": "彩虹点击画家",
        "icon": "🐢",
        "goals": [
            ("🪟", "Screen", "弹出游戏窗口"),
            ("🐢", "Turtle", "一只会动的画笔"),
            ("🖱️", "点击", "onscreenclick 把坐标给你"),
            ("⭐", "游戏", "点哪里盖一只彩色海龟"),
        ],
        "know_rows": [
            ("Screen()", "画布 / 窗口", "setup / title / bgcolor"),
            ("Turtle()", "海龟对象", "shape / color / speed"),
            ("forward / left", "走和转", "连走 4 次就是正方形"),
            ("stamp()", "盖章", "当前位置印一个形状"),
            ("onscreenclick", "鼠标回调", "函数要收 x, y"),
        ],
        "print_know": [
            ("import turtle", "标准库，不用 pip", "import turtle"),
            ("Screen()", "窗口", "screen.setup(800, 600)"),
            ("Turtle()", "角色", 't.shape("turtle")'),
            ("stamp()", "盖章不拖线", "先 penup 再 stamp"),
            ("onscreenclick(fn)", "点击", "fn(x, y)"),
            ("turtle.done()", "保持窗口", "写在最后"),
        ],
        "io": "窗口弹出后：\n点击画面 → 盖一只彩色小海龟\n空格 → 换颜色\nC → 清屏",
        "steps": [
            "创建 screen 和 painter，penup、shape('turtle')",
            "写 paint(x,y)：goto + 随机朝向 + stamp",
            "onscreenclick(paint)，空格换色，C 清屏",
            "最后 turtle.done()，运行后点几下确认",
        ],
        "blanks": [
            "创建窗口的类是 ________",
            "让海龟前进 100：t.________(100)",
            "点击事件用 screen.________(函数)",
            "窗口不闪退，最后要写 ________",
        ],
        "code": "def paint(x, y):\n    painter.goto(x, y)\n    painter.stamp()\n\nscreen.onscreenclick(paint)\nturtle.done()",
        "next": "第 2 课：键盘控制 — 方向键开车",
        "next_short": "方向盘 — 遥控小车",
        "sum_rows": [
            ("Screen / Turtle", "窗口和角色", "先建再玩"),
            ("forward / left", "走和转", "热身正方形"),
            ("stamp + 点击", "盖章游戏", "点哪里画哪里"),
        ],
        "ex": [
            ("改背景", "bgcolor 换成深蓝"),
            ("改形状", 'shape("circle")'),
            ("加颜色", "调色盘再加一种"),
            ("猜朝向", "left(90) 四次后朝哪"),
            ("挑战", "点击盖 8 瓣花"),
        ],
        "knowledge_slides": [
            ("窗口和海龟是两个东西", "Screen 是画布，Turtle 是角色。两个都要创建。最后 turtle.done() 让窗口留着。",
             "screen = turtle.Screen()\nscreen.setup(800, 600)\nt = turtle.Turtle()\nt.shape('turtle')"),
            ("点击把坐标给你", "onscreenclick 调用你的函数，并传入 x, y。先 goto 再 stamp。",
             "def paint(x, y):\n    t.goto(x, y)\n    t.stamp()\nscreen.onscreenclick(paint)"),
        ],
    },
    {
        "n": 2,
        "title": "方向盘",
        "subtitle": "onkeypress、listen、朝向、边界",
        "project": "遥控小车",
        "icon": "🎮",
        "goals": [
            ("⌨️", "listen", "窗口开始听键盘"),
            ("⬆️", "onkeypress", "把键绑到函数"),
            ("🧭", "setheading", "0 右 90 上 180 左 270 下"),
            ("⭐", "游戏", "开车 + 撞墙弹回"),
        ],
        "know_rows": [
            ("listen()", "开始听键", "忘了就没反应"),
            ('onkeypress(fn,"Up")', "绑方向键", "函数名不要加括号"),
            ("setheading(90)", "朝向", "90 是正北"),
            ("xcor / ycor", "读坐标", "用来做边界"),
        ],
        "print_know": [
            ("listen()", "窗口获得焦点并听键", "screen.listen()"),
            ("onkeypress", "按下时调用", 'onkeypress(go_up, "Up")'),
            ("heading", "0/90/180/270", "右上左下"),
            ("forward(n)", "朝当前方向走", "先 setheading 再走"),
            ("边界", "碰到边缘就回头", "if xcor() > 380"),
        ],
        "io": "方向键开车，留下绿色车辙。\n空格冲刺，碰到窗口边缘弹回。\nR 清轨迹回到起点。",
        "steps": [
            "小车 penup 放到下方，再 pendown 准备留车辙",
            "四个方向函数：setheading + forward",
            "bounce_inside：越界就拉回来并掉头",
            "listen + 绑 Up/Down/Left/Right/space/r",
        ],
        "blanks": [
            "键盘事件之前必须调用 ________()",
            "方向键上的名字是 ________（Up / up）",
            "正北对应 heading = ________",
            "onkeypress(go_up, ...) 能不能写成 go_up()？________",
        ],
        "code": "def go_up():\n    car.setheading(90)\n    car.forward(20)\n\nscreen.listen()\nscreen.onkeypress(go_up, 'Up')",
        "next": "第 3 课：鼠标打地鼠 — 随机坐标 + 点击判定",
        "next_short": "点哪里打哪里 — 打地鼠",
        "sum_rows": [
            ("listen + onkeypress", "键盘", "先听再绑"),
            ("setheading", "朝向", "0 90 180 270"),
            ("边界", "别开丢", "读坐标再拉回"),
        ],
        "ex": [
            ("改步长", "STEP 改成 30"),
            ("加粗车辙", "pensize(6)"),
            ("绑 WASD", "再套一套键"),
            ("穿墙", "右边出去左边出来"),
            ("挑战", "放 3 个障碍桩"),
        ],
        "knowledge_slides": [
            ("键盘三件套", "listen 开始听。onkeypress 绑函数。函数名不要加括号，否则会立刻执行。",
             "screen.listen()\nscreen.onkeypress(go_up, 'Up')"),
            ("朝向是一圈 360 度", "0 朝右，90 朝上。开车就是先转向再 forward。",
             "car.setheading(90)\ncar.forward(20)"),
        ],
    },
    {
        "n": 3,
        "title": "点哪里打哪里",
        "subtitle": "随机坐标、点击判定、倒计时",
        "project": "打地鼠",
        "icon": "🐹",
        "goals": [
            ("🎲", "randint", "地鼠换洞"),
            ("🎯", "distance(x,y)", "点中了吗"),
            ("⏰", "ontimer", "倒计时闹钟"),
            ("⭐", "游戏", "30 秒打地鼠"),
        ],
        "know_rows": [
            ("randint(a,b)", "随机整数", "含两端"),
            ("goto(x,y)", "瞬移", "换洞用这个"),
            ("distance(x,y)", "到点击点的距离", "< 40 算打中"),
            ("ontimer(fn, ms)", "延迟调用", "别用 while True"),
        ],
        "print_know": [
            ("random.randint", "随机整数", "mole.goto(randint(...))"),
            ("distance", "两点距离", "mole.distance(x, y)"),
            ("ontimer", "毫秒后调用", "screen.ontimer(tick, 1000)"),
            ("tracer(0)", "手动刷新", "配合 update()"),
            ("hideturtle", "藏起来", "打中后可先藏"),
        ],
        "io": "橙色地鼠随机出现。\n点中 +1 分并立刻换洞。\n30 秒到，弹出最终得分。",
        "steps": [
            "地鼠 jump_mole：随机 goto + showturtle",
            "hit(x,y)：distance < 40 则加分并换洞",
            "tick_timer 每秒减 1，到 0 结束",
            "mole_wander 自己也会换洞，分数高了间隔更短",
        ],
        "blanks": [
            "随机整数用 random.________",
            "点中判定：mole.________(x, y) < 40",
            "每秒执行一次用 screen.________(函数, 1000)",
            "卡死窗口的写法是 ________ True（不要用）",
        ],
        "code": "def hit(x, y):\n    if mole.distance(x, y) < 40:\n        score += 1\n        jump_mole()\n\nscreen.onscreenclick(hit)",
        "next": "第 4 课：游戏循环 — 金币自己往下掉",
        "next_short": "让画面自己动 — 接住金币",
        "sum_rows": [
            ("randint + goto", "换位置", "地鼠换洞"),
            ("distance", "点中判定", "阈值自己定"),
            ("ontimer", "闹钟", "倒计时 / 换洞"),
        ],
        "ex": [
            ("更难", "命中范围改 25"),
            ("改时限", "15 秒极速"),
            ("点空扣分", "没命中 score -= 1"),
            ("换形状", 'shape("circle")'),
            ("挑战", "颜色也随机"),
        ],
        "knowledge_slides": [
            ("点中就是距离够近", "鼠标很难点到正中心。用 distance < 阈值，不要写 xcor()==x。",
             "if mole.distance(x, y) < 40:\n    score += 1"),
            ("闹钟不要死循环", "while True 会卡死窗口。倒计时用 ontimer 自己叫自己。",
             "def tick():\n    ...\n    screen.ontimer(tick, 1000)"),
        ],
    },
    {
        "n": 4,
        "title": "让画面自己动",
        "subtitle": "游戏循环、下落、按住移动",
        "project": "接住金币",
        "icon": "🪙",
        "goals": [
            ("🔁", "tick 循环", "每 20ms 更新一帧"),
            ("📉", "sety", "金币往下掉"),
            ("↔️", "vx", "按住方向键连续移动"),
            ("⭐", "游戏", "篮子接金币"),
        ],
        "know_rows": [
            ("tracer(0)", "先不自动画", "自己 update"),
            ("ontimer(tick,20)", "游戏循环", "末尾必须再约一次"),
            ("onkeyrelease", "松手停下", "配合 vx"),
            ("distance", "接到了吗", "篮子和金币靠近"),
        ],
        "print_know": [
            ("tracer(0)+update()", "流畅动画", "每帧结束再画"),
            ("游戏循环", "tick 改位置再约自己", "ontimer(tick, 20)"),
            ("vx 速度", "按住 = 有速度", "松开 vx=0"),
            ("onkeyrelease", "松键回调", "stop()"),
            ("掉出屏幕", "重置到天上", "coin.sety(280)"),
        ],
        "io": "左右移动篮子。\n金币从天而降，接到 +1。\n漏掉 8 个游戏结束。接到越多掉得越快。",
        "steps": [
            "篮子在底部，金币从随机 x 的天上开始掉",
            "tick：篮子 += vx，金币 y 减少",
            "掉出底部 missed+1 并重置；靠近篮子则 score+1",
            "漏满 8 个写出结束语",
        ],
        "blanks": [
            "关掉自动刷新：screen.________(0)",
            "游戏循环函数通常叫 ________",
            "松手停下来用 screen.________",
            "tick 末尾忘了 ontimer，动画只会动 ________ 帧",
        ],
        "code": "def tick():\n    coin.sety(coin.ycor() - 5)\n    basket.setx(basket.xcor() + vx)\n    screen.update()\n    screen.ontimer(tick, 20)",
        "next": "第 5 课：碰撞检测 — 吃星星、躲石头",
        "next_short": "碰一碰 — 星星收集者",
        "sum_rows": [
            ("tracer / update", "流畅", "手动刷新"),
            ("tick + ontimer", "循环", "每帧更新"),
            ("vx + release", "按住移动", "松开清零"),
        ],
        "ex": [
            ("加宽篮子", "shapesize(1, 7)"),
            ("更大金币", "shapesize 调大"),
            ("更狠", "漏 5 个就结束"),
            ("热身", "球左右反弹"),
            ("挑战", "再掉一颗炸弹"),
        ],
        "knowledge_slides": [
            ("游戏循环长这样", "改位置 → update → 再约自己。忘了最后一步，动画只动一帧。",
             "def tick():\n    coin.sety(coin.ycor() - 5)\n    screen.update()\n    screen.ontimer(tick, 20)"),
            ("按住才连续动", "onkeypress 给速度，onkeyrelease 把速度清零。点一下走一格是第 2 课的玩法。",
             "def press_left():\n    global vx\n    vx = -8"),
        ],
    },
    {
        "n": 5,
        "title": "碰一碰",
        "subtitle": "distance 碰撞、多种角色、胜负",
        "project": "星星收集者",
        "icon": "⭐",
        "goals": [
            ("📏", "distance", "小于阈值就是撞上"),
            ("⭐", "道具", "吃到就换位置"),
            ("🪨", "障碍", "碰到就失败"),
            ("🏆", "胜负", "吃满 10 颗赢"),
        ],
        "know_rows": [
            ("a.distance(b)", "两龟距离", "碰撞核心"),
            ("阈值", "自己定", "角色越大阈值越大"),
            ("place_star", "刷新道具", "别刷在脚底下"),
            ("keys 字典", "多键同时", "跟手移动"),
        ],
        "print_know": [
            ("distance(海龟)", "两角色距离", "player.distance(star)"),
            ("阈值", "像素半径", "< 28 算吃到"),
            ("胜利", "score >= 10", "写一句你赢了"),
            ("失败", "碰到石头", "立刻 return 停循环"),
            ("penup", "障碍不要拖线", "石头也要抬笔"),
        ],
        "io": "方向键移动绿色海龟。\n吃黄三角 +1，吃满 10 胜利。\n碰到红圆石头立刻结束。",
        "steps": [
            "玩家 / 星星 / 4 颗石头，全部 penup",
            "tick 里按 keys 移动，并夹紧在窗口内",
            "靠近星星：加分并 place_star；满 10 胜利",
            "靠近任一块石头：失败并停止 tick",
        ],
        "blanks": [
            "碰撞检测用的方法名是 ________",
            "阈值太小会 ________（吃不到 / 太容易）",
            "石头忘了 penup 会在屏幕上留下 ________",
            "吃到星星后一定要 ________ 换位置",
        ],
        "code": "if player.distance(star) < 28:\n    score += 1\n    place_star()\nif player.distance(rock) < 26:\n    finish('撞到石头了')",
        "next": "第 6 课：列表管理多个敌人 — 躲避陨石",
        "next_short": "越来越难 — 躲避陨石",
        "sum_rows": [
            ("distance", "碰撞", "比阈值"),
            ("道具 / 障碍", "加分 / 失败", "两种判定"),
            ("结局", "赢或输", "停掉循环"),
        ],
        "ex": [
            ("更贪", "胜利改 15 颗"),
            ("换色", "玩家改成绿色"),
            ("更险", "石头改 6 颗"),
            ("标题显示距离", "screen.title"),
            ("挑战", "石头缓慢游走"),
        ],
        "knowledge_slides": [
            ("没有内置碰撞函数", "自己量距离。阈值跟形状大小有关，课堂上用 25～40 试。",
             "if player.distance(star) < 28:\n    score += 1"),
            ("刷新时躲开别人", "星星刷在脚底下会一帧吃掉。while True 随机，直到离玩家够远。",
             "while True:\n    star.goto(随机)\n    if star.distance(player) > 60:\n        break"),
        ],
    },
    {
        "n": 6,
        "title": "越来越难",
        "subtitle": "列表管敌人、随机刷新、难度曲线",
        "project": "躲避陨石",
        "icon": "☄️",
        "goals": [
            ("📦", "列表", "6 颗陨石一个列表"),
            ("🌧️", "for 更新", "统一往下掉"),
            ("📈", "加速", "分数越高越快"),
            ("⭐", "游戏", "躲开活得越久分越高"),
        ],
        "know_rows": [
            ("append", "造好再装进去", "不要 m1 m2 m3"),
            ("for m in meteors", "统一移动", "掉出就重置"),
            ("speed = 4+score//15", "难度曲线", "整数除法"),
            ("R 重开", "复位变量", "alive=True"),
        ],
        "print_know": [
            ("列表", "一串敌人", "meteors = []"),
            ("工厂循环", "for _ in range(6)", "创建并 append"),
            ("统一更新", "for m in meteors", "移动 + 碰撞"),
            ("//", "整数除法", "score // 15"),
            ("重开", "分数/位置清零", "按 R"),
        ],
        "io": "左右移动蓝色海龟。\n6 颗陨石往下砸，躲开。\n存活时间就是分数。撞到结束，R 再来。",
        "steps": [
            "循环 6 次创建陨石，随机撒在天上",
            "tick：玩家左右移动；陨石 y 减少并旋转",
            "掉出底部 reset；碰到玩家结束",
            "speed 随 score 增加；R 调用 restart",
        ],
        "blanks": [
            "多个敌人应该放进 ________ 而不是 m1 m2 m3",
            "整数除法的符号是 ________",
            "掉出屏幕后应该 ________（扔掉 / 送回天上）",
            "重开时必须把 alive 改回 ________",
        ],
        "code": "for m in meteors:\n    m.sety(m.ycor() - speed)\n    if m.ycor() < -300:\n        reset_meteor(m)\n    if player.distance(m) < 24:\n        结束",
        "next": "第 7 课：子弹列表 — 打气球",
        "next_short": "发射！— 打气球",
        "sum_rows": [
            ("列表", "多个敌人", "append 装起来"),
            ("for 更新", "一起掉", "reset 循环利用"),
            ("难度", "越来越快", "score // n"),
        ],
        "ex": [
            ("更少", "初始 4 颗"),
            ("换色", "玩家换颜色"),
            ("更慢", "speed = 3 + score//20"),
            ("方形陨石", 'shape("square")'),
            ("挑战", "每 20 分再加一颗"),
        ],
        "knowledge_slides": [
            ("敌人用列表养", "不要写 6 个变量名。创建、append、for 更新，是从这课开始的标准套路。",
             "meteors = []\nfor _ in range(6):\n    m = turtle.Turtle()\n    meteors.append(m)"),
            ("循环利用，不要扔掉", "掉出屏幕就 goto 回天上。一直 hideturtle 会越来越少，游戏变空。",
             "if m.ycor() < -300:\n    reset_meteor(m)"),
        ],
    },
    {
        "n": 7,
        "title": "发射！",
        "subtitle": "子弹列表、开火、边遍历边删除",
        "project": "打气球",
        "icon": "🎈",
        "goals": [
            ("🚀", "new 子弹", "按空格 append 一只"),
            ("🗑️", "飞出就删", "hideturtle + remove"),
            ("🎯", "两层循环", "子弹 × 气球测距离"),
            ("⭐", "游戏", "打气球，漏太多结束"),
        ],
        "know_rows": [
            ("make_bullet()", "临时工", "从炮台位置出发"),
            ("bullets[:]", "拷贝再遍历", "才能安全 remove"),
            ("cool", "冷却", "防止机关枪卡死"),
            ("len(bullets)<4", "上限", "限制同屏子弹"),
        ],
        "print_know": [
            ("append 子弹", "按键创建", "bullets.append(shot)"),
            ("[:]", "浅拷贝列表", "for x in xs[:]"),
            ("remove + hideturtle", "先藏再删", "否则留幽灵"),
            ("冷却 cool", "隔几帧才能再射", "cool = 10"),
            ("双层 for", "每颗子弹对每个气球", "打中都删除"),
        ],
        "io": "左右移动三角炮台，空格发射。\n打中气球 +1，气球漏到底部 missed+1。\n漏 8 个结束。",
        "steps": [
            "炮台在底部；5 个气球在天上",
            "空格：冷却好且子弹 < 4 则 make_bullet",
            "tick：子弹向上飞，出屏删除；气球下飘",
            "两层循环测 distance，打中加分并重置气球",
        ],
        "blanks": [
            "遍历时要删除，应该写 for x in xs.________",
            "子弹飞出屏幕要 hideturtle 再 ________",
            "限制连发的变量通常叫 ________",
            "子弹忘了 penup 会拖出一条 ________",
        ],
        "code": "for shot in bullets[:]:\n    shot.forward(12)\n    if shot.ycor() > 300:\n        shot.hideturtle()\n        bullets.remove(shot)",
        "next": "第 8 课：双人对打 — 乒乓球",
        "next_short": "对打 — 乒乓球大战",
        "sum_rows": [
            ("创建子弹", "append", "按键工厂"),
            ("删除", "[:] + remove", "飞出 / 打中"),
            ("冷却", "cool", "别卡成幻灯片"),
        ],
        "ex": [
            ("更少子弹", "同时最多 2 发"),
            ("更大气球", "更容易打"),
            ("更狠", "漏 5 个结束"),
            ("圆形子弹", 'shape("circle")'),
            ("挑战", "彩球不同分"),
        ],
        "knowledge_slides": [
            ("子弹是临时工", "炮台常驻，子弹打完消失。按一次键 new 一只，append 进列表。",
             "def make_bullet():\n    shot = turtle.Turtle()\n    shot.goto(cannon.xcor(), cannon.ycor())\n    bullets.append(shot)"),
            ("边遍历边删要拷贝", "for x in xs 时 remove 会漏。写成 for x in xs[:] 再改原列表。",
             "for shot in bullets[:]:\n    if shot.ycor() > 300:\n        bullets.remove(shot)"),
        ],
    },
    {
        "n": 8,
        "title": "对打",
        "subtitle": "dx/dy 反弹、双人键位、先到 5 分",
        "project": "乒乓球大战",
        "icon": "🏓",
        "goals": [
            ("↔️", "dx / dy", "球的两个速度分量"),
            ("↩️", "反弹", "撞墙把那一轴取反"),
            ("👥", "双人", "W/S 对 上/下"),
            ("⭐", "游戏", "先到 5 分获胜"),
        ],
        "know_rows": [
            ("ball.dx", "自定义属性", "不是官方 API"),
            ("dy *= -1", "上下反弹", "乘 -1 即掉头"),
            ("挡板 distance", "打到就 dx 取反", "再加一点点速度"),
            ("出界得分", "重置中场", "不要让球飞丢"),
        ],
        "print_know": [
            ("dx / dy", "水平 / 垂直速度", "每帧加到坐标上"),
            ("*= -1", "取反", "撞墙反弹"),
            ("挡板", "shapesize(5, 0.8)", "竖着的长方形"),
            ("两套键", "左 W/S 右方向键", "onkeypress 两份"),
            ("先到 N 分", "本课 N=5", "写出谁赢"),
        ],
        "io": "左玩家 W / S，右玩家方向键。\n球碰到挡板反弹并加速。\n先得到 5 分的人获胜。",
        "steps": [
            "左右挡板、一颗球，给球 dx dy",
            "tick：挡板按速度移动；球加 dx dy",
            "上下墙反弹；靠近挡板则 dx 掉头并加速",
            "飞出左/右边：对面得分，球回中场",
        ],
        "blanks": [
            "把垂直速度取反：ball.dy ________ -1",
            "反弹时要把球 ________ 场地内，否则会卡墙",
            "左边玩家的键是 ________ 和 S",
            "球飞出右边界应该给 ________ 边加分",
        ],
        "code": "ball.setx(ball.xcor() + ball.dx)\nball.sety(ball.ycor() + ball.dy)\nif ball.ycor() > 280:\n    ball.dy *= -1",
        "next": "第 9 课：列表当身体 — 贪吃蛇",
        "next_short": "长长的身体 — 贪吃蛇",
        "sum_rows": [
            ("dx / dy", "速度分量", "每帧加坐标"),
            ("反弹", "取反", "墙和挡板"),
            ("双人", "两套键", "先到 5 分"),
        ],
        "ex": [
            ("改慢", "初始 dx dy 改小"),
            ("换色", "左右挡板不同色"),
            ("快进", "先到 3 分"),
            ("红球", "ball.color('red')"),
            ("挑战", "右边自动挡板"),
        ],
        "knowledge_slides": [
            ("速度拆成两个方向", "海龟对象上可以自己挂 dx、dy。每帧加到 x、y 上，就是在飞。",
             "ball.dx = 4\nball.dy = 3\nball.setx(ball.xcor() + ball.dx)"),
            ("卡墙是经典 bug", "反弹时先 sety 拉回场内，再 dy *= -1。否则下一帧还在墙外，会疯狂闪烁。",
             "if ball.ycor() > 280:\n    ball.sety(280)\n    ball.dy *= -1"),
        ],
    },
    {
        "n": 9,
        "title": "长长的身体",
        "subtitle": "列表当身体、跟着走、自撞",
        "project": "贪吃蛇",
        "icon": "🐍",
        "goals": [
            ("🧩", "snake 列表", "[0] 是头"),
            ("👣", "从尾巴抄到头", "后一节走前一节的位"),
            ("🚫", "禁止掉头", "abs 差 180 就忽略"),
            ("⭐", "游戏", "吃食物变长，撞墙/自己结束"),
        ],
        "know_rows": [
            ("snake[0]", "头", "唯一自己走的一节"),
            ("倒序 for", "range(len-1,0,-1)", "从尾巴往前"),
            ("append 新尾巴", "吃到就 grow", "出生在旧尾巴处"),
            ("pending", "缓冲转弯", "避免同一帧冲突"),
        ],
        "print_know": [
            ("身体=列表", "每节一只 Turtle", "snake[0] 是头"),
            ("跟着走", "从尾巴往前抄坐标", "千万别从头抄"),
            ("不能掉头", "差 180 度忽略", "否则立刻撞自己"),
            ("网格", "一格 20 像素", "坐标对齐更好吃"),
            ("自撞", "头和身体 distance", "从 snake[1:] 查"),
        ],
        "io": "方向键转弯。\n吃黄点身体 +1。\n撞墙或撞自己结束，R 重开。越长稍微越快。",
        "steps": [
            "3 节身体排成一排，食物随机放空地",
            "tick：从尾巴往前 goto 前一节，头再迈一格",
            "出界或碰到身体 → game_over",
            "碰到食物 → grow + place_food",
        ],
        "blanks": [
            "蛇头是 snake 的下标 ________",
            "移动时 for 必须从 ________ 往前抄",
            "禁止 ________ 度掉头",
            "食物刷在蛇身上会 ________（连吃 / 没影响）",
        ],
        "code": "for i in range(len(snake) - 1, 0, -1):\n    snake[i].goto(snake[i-1].xcor(), snake[i-1].ycor())\nhead.goto(nx, ny)",
        "next": "第 10 课：状态机毕业作 — 太空大战",
        "next_short": "完整作品 — 太空大战",
        "sum_rows": [
            ("列表身体", "[0] 是头", "append 变长"),
            ("倒序跟随", "尾巴→头", "本课核心"),
            ("死亡", "撞墙/自己", "R 重开"),
        ],
        "ex": [
            ("更长开局", "初始 5 节"),
            ("更大格", "STEP=25"),
            ("三角食物", 'food.shape("triangle")'),
            ("打印长度", "title 显示 len"),
            ("挑战", "穿墙模式"),
        ],
        "knowledge_slides": [
            ("从尾巴往头抄", "后一节走到前一节刚才的位置。从头往后抄，整条蛇会叠在一起。",
             "for i in range(len(snake)-1, 0, -1):\n    snake[i].goto(snake[i-1].xcor(), snake[i-1].ycor())"),
            ("不能 180 度掉头", "否则头一帧就撞上第二节。abs(新-旧)==180 就忽略这次按键。",
             "if abs(heading - direction) == 180:\n    return"),
        ],
    },
    {
        "n": 10,
        "title": "完整作品",
        "subtitle": "状态机、生命、菜单、重开",
        "project": "太空大战",
        "icon": "🚀",
        "goals": [
            ("📋", "state", "menu / play / over"),
            ("❤️", "生命", "漏掉或撞到扣 1"),
            ("🌊", "波次", "分数够了敌人更多更快"),
            ("🎉", "毕业", "能给别人玩的完整游戏"),
        ],
        "know_rows": [
            ('state="menu"', "状态机", "同一套键不同含义"),
            ("清场", "hideturtle + clear", "否则幽灵残留"),
            ("空格两用", "菜单=开始 游戏=射击", "先判断 state"),
            ("tick 不停", "菜单也要 ontimer", "否则按键没人理循环"),
        ],
        "print_know": [
            ("状态机", "一个字符串管阶段", "menu / play / over"),
            ("生命", "lives -= 1", "到 0 进入 over"),
            ("清场", "先 hideturtle 再 clear 列表", "重开必备"),
            ("波次", "score 门槛升高", "wave += 1"),
            ("R 回菜单", "show_menu()", "再按空格新开一局"),
        ],
        "io": "先看到菜单，按空格开始。\n左右移动、空格射击红色敌军。\n3 条命用完出现结束画面，R 回菜单。",
        "steps": [
            "show_menu 写标题；空格 start_game",
            "play：移动、射击、敌军下掉、碰撞扣命",
            "分数达 wave*80 则 wave+1 并加敌人",
            "命 0 → over；R → show_menu 清场",
        ],
        "blanks": [
            "本课用 ________ 变量区分菜单和游戏",
            "空格在菜单里是开始，在游戏里是 ________",
            "重开只 clear 列表不够，还要 ________ 海龟",
            "tick 在菜单里也要继续 ________，否则循环停住",
        ],
        "code": "state = 'menu'\n\ndef tick():\n    if state != 'play':\n        screen.update()\n        screen.ontimer(tick, 20)\n        return\n    # 只在 play 时移动角色",
        "next": "结业！下一站可去 Pygame、语法速通或 Tkinter。",
        "next_short": "课程结束 — 去选下一门吧",
        "sum_rows": [
            ("前 3 课", "窗口/键盘/鼠标", "让海龟听话"),
            ("第 4～7 课", "循环/碰撞/列表", "让游戏自己跑"),
            ("第 8～10 课", "对打/蛇/状态机", "完整作品"),
        ],
        "ex": [
            ("改名", "标题换成你的游戏名"),
            ("换皮", "玩家换喜欢的颜色"),
            ("更易", "初始敌人 3 个"),
            ("生命 5", "lives 初始改 5"),
            ("挑战", "第 5 波敌人变紫色"),
        ],
        "knowledge_slides": [
            ("一个变量管三种画面", "state 是字符串。tick 开头如果不是 play 就只刷新、继续约自己。",
             "if state != 'play':\n    screen.update()\n    screen.ontimer(tick, 20)\n    return"),
            ("清场要藏海龟", "列表 clear 只丢掉引用。屏幕上的形状还在。hideturtle 再 clear。",
             "for e in enemies:\n    e.hideturtle()\nenemies.clear()"),
        ],
    },
]

ENRICH = {
    1: {
        "warmup": ("热身：正方形 + 三角形", "forward + left(90) 走 4 次；再 left(120) 走 3 次。先别写点击。",
                   "t = turtle.Turtle()\nfor _ in range(4):\n    t.forward(100)\n    t.left(90)"),
        "challenge": ("加码：点击盖一朵花", "点一下不要只 stamp 一次，转 8 次盖 8 瓣。",
                      "for _ in range(8):\n    painter.stamp()\n    painter.left(45)"),
        "mistakes": [
            ("onscreenclick(paint())", "onscreenclick(paint)", "加括号会立刻调用，应传函数名"),
            ("忘了 turtle.done()", "最后写 turtle.done()", "否则窗口闪一下就关"),
            ("Turtle.forward(100)", "t = Turtle(); t.forward(100)", "先有对象再调用"),
        ],
        "more_slides": [
            ("抬笔再盖章", "penup 之后移动不画线。画画游戏几乎一开始就要抬笔。",
             "painter.penup()\npainter.goto(x, y)\npainter.stamp()"),
            ("调色盘是列表", "点空格换下一个颜色。index % len 可以循环取。",
             "color_index += 1\npainter.color(PALETTE[color_index % len(PALETTE)])"),
        ],
        "more_blanks": [
            "抬笔的方法名是 ________",
            "盖章的方法名是 ________",
            "left(90) 的意思是向 ________ 转 90 度",
        ],
        "more_ex": [
            ("花瓣", "加码改成 12 瓣"),
            ("清屏键", "再绑一个键换成 bgcolor"),
        ],
    },
    2: {
        "warmup": ("热身：只绑上键", "每按一次 Up，forward(20)。再绑左右，先不要边界。",
                   "def go_up():\n    car.setheading(90)\n    car.forward(20)"),
        "challenge": ("加码：障碍桩", "中间放 3 个灰色方块。碰到就 reset_car。预告 distance。",
                      "if car.distance(block) < 30:\n    reset_car()"),
        "mistakes": [
            ("写了 onkeypress 没 listen", "screen.listen()", "没听当然没反应"),
            ('"up"', '"Up"', "方向键首字母大写"),
            ("car.forward = 20", "car.forward(20)", "forward 是函数"),
        ],
        "more_slides": [
            ("四个朝向背下来", "右 0、上 90、左 180、下 270。开车先转向再走。",
             "drive(90, STEP)   # 向上"),
            ("边界要四边都写", "只写右边，学生一开上去就丢了。x 和 y 各两头。",
             "if car.xcor() > 380:\n    car.setx(380)\n    car.setheading(180)"),
        ],
        "more_blanks": [
            "正东 heading = ________",
            "碰到右墙应该 setheading(________)",
            "留下车辙要先 ________（抬笔 / 落笔）",
        ],
        "more_ex": [
            ("冲刺", "空格走 40 像素（代码已有，改距离）"),
            ("穿墙", "右边出去从左边出来"),
        ],
    },
    3: {
        "warmup": ("热身：点一下换一次洞", "不要分数、不要倒计时。确认点击回调和随机 goto。",
                   "def hit(x, y):\n    mole.goto(random.randint(-300, 300),\n              random.randint(-180, 180))"),
        "challenge": ("加码：越打越快", "换洞间隔 = max(500, 1400 - score*80)。代码已含，改系数。",
                      "wait = max(500, 1400 - score * 80)\nscreen.ontimer(mole_wander, wait)"),
        "mistakes": [
            ("while True: jump()", "ontimer", "死循环卡死窗口"),
            ("mole.xcor() == x", "distance < 40", "点不到正中心"),
            ("倒计时变负数还不停", "time_left<=0 就 return", "要有结束分支"),
        ],
        "more_slides": [
            ("ontimer 和 sleep 不一样", "sleep 会冻结整个窗口，鼠标也点不了。倒计时必须用闹钟。",
             "screen.ontimer(tick_timer, 1000)"),
            ("tracer(0) 减少闪烁", "地鼠跳来跳去时，关掉自动刷新，自己 update。",
             "screen.tracer(0)\nscreen.update()"),
        ],
        "more_blanks": [
            "randint(1, 3) 可能取到 ________ 和 ________",
            "倒计时 30 秒，ontimer 的毫秒数是 ________",
            "打中后立刻 ________ 可以让玩家看到反馈",
        ],
        "more_ex": [
            ("极速", "时限改 15 秒"),
            ("点空", "没命中扣 1 分"),
        ],
    },
    4: {
        "warmup": ("热身：一颗球往下掉", "没有篮子。y 减到小于 -280 就回到天上。",
                   "def tick():\n    coin.sety(coin.ycor() - 5)\n    if coin.ycor() < -280:\n        coin.sety(280)\n    screen.update()\n    screen.ontimer(tick, 20)"),
        "challenge": ("加码：炸弹", "再做一只红色 bomb 一起掉。接到 score -= 2。",
                      "if basket.distance(bomb) < 70:\n    score -= 2\n    reset_bomb()"),
        "mistakes": [
            ("tick 里忘了 ontimer", "末尾再约一次", "否则只动一帧"),
            ("忘了 global vx", "在函数里写 global vx", "否则改的是局部变量"),
            ("tracer(0) 不 update", "每帧 update()", "否则全黑"),
        ],
        "more_slides": [
            ("接到越多掉得越快", "用 score 参与下落速度。简单又有手感。",
             "coin.sety(coin.ycor() - (5 + score // 3))"),
            ("按住移动靠 vx", "第 2 课是点一下走一格；从这课起按住才像游戏。",
             "basket.setx(basket.xcor() + vx)"),
        ],
        "more_blanks": [
            "松开左键要把 vx 改成 ________",
            "金币掉出底部应该 ________ 而不是结束立刻（本课漏 8 次才结束）",
            "20 毫秒一帧，大约每秒 ________ 帧",
        ],
        "more_ex": [
            ("篮子", "加宽 shapesize"),
            ("炸弹", "加码红色扣分"),
        ],
    },
    5: {
        "warmup": ("热身：打印距离", "键盘动一只，write 实时显示 distance。走近看数字变小。",
                   "hud.write(f'distance={int(a.distance(b))}')"),
        "challenge": ("加码：石头会动", "每帧 rock.forward(1); rock.left(2)。也要 penup。",
                      "for rock in rocks:\n    rock.forward(1)\n    rock.left(2)"),
        "mistakes": [
            ("阈值写成 5", "大约 25～40", "贴着也吃不到"),
            ("吃到不换位置", "place_star()", "星星停在嘴里"),
            ("石头 pendown", "penup", "满屏红线"),
        ],
        "more_slides": [
            ("多键字典", "四个方向各一个 True/False，循环里谁被按住谁走。可以斜着走。",
             "if keys['Left']:\n    player.setheading(180)\n    player.forward(6)"),
            ("两种结局都要停循环", "胜利和失败都把 alive=False，tick 开头就 return。",
             "if not alive:\n    screen.update()\n    return"),
        ],
        "more_blanks": [
            "吃满 ________ 颗星星算赢（本课默认）",
            "player.distance(star) 的单位是 ________（像素）",
            "刷新星星时要避开 ________ 和石头",
        ],
        "more_ex": [
            ("15 颗", "改胜利条件"),
            ("游走石头", "加码 forward"),
        ],
    },
    6: {
        "warmup": ("热身：3 颗陨石下雨", "玩家先站着。确认掉出屏幕会 reset 回天上。",
                   "for m in meteors:\n    m.sety(m.ycor() - 4)\n    if m.ycor() < -300:\n        reset_meteor(m)"),
        "challenge": ("加码：越来越多", "每 20 分 append 一颗新陨石，最多 12。",
                      "if score % 20 == 0:\n    make_meteor()"),
        "mistakes": [
            ("for 里 append 同一列表", "循环后再加", "容易漏或无限加"),
            ("重开忘了 alive=True", "restart 里复位", "R 没反应"),
            ("阈值太大", "大约 24", "站着也被判撞"),
        ],
        "more_slides": [
            ("难度曲线用整数除", "speed = 4 + score//15。一上来就 20 没法玩。",
             "speed = 4 + score // 15"),
            ("R 重开要复位所有状态", "分数、帧计数、位置、alive。漏一个就会残局。",
             "score = 0\nalive = True\nplayer.goto(0, -230)"),
        ],
        "more_blanks": [
            "本课默认同时有 ________ 颗陨石",
            "存活分是靠 ________ 累加的（时间 / 击杀）",
            "reset_meteor 应该把 y 放到 ________（天上 / 地下）",
        ],
        "more_ex": [
            ("更慢", "改 // 的分母"),
            ("加陨石", "加码 append"),
        ],
    },
    7: {
        "warmup": ("热身：空格射出一颗子弹", "没有气球。黄点飞出屏幕后 hideturtle + remove。",
                   "def fire():\n    make_bullet()"),
        "challenge": ("加码：彩球不同分", "给气球 b.points。红 3 分蓝 1 分。",
                      "score += balloon.points"),
        "mistakes": [
            ("for shot in bullets: remove", "for shot in bullets[:]", "否则漏删"),
            ("子弹没 penup", "penup()", "拖一条黄线"),
            ("没有冷却", "cool=10", "机关枪卡死"),
        ],
        "more_slides": [
            ("同屏子弹要有上限", "len(bullets)<4。海龟对象太多，课上电脑会开始卡。",
             "if cool <= 0 and len(bullets) < 4:\n    make_bullet()"),
            ("打中双方都要处理", "子弹藏+删，气球重置回天上。只删一边会留下幽灵。",
             "shot.hideturtle(); bullets.remove(shot)\nreset_balloon(balloon)"),
        ],
        "more_blanks": [
            "[:] 的作用是 ________ 一份列表再遍历",
            "冷却的单位是 ________（帧 / 秒）",
            "本课漏掉 ________ 个气球结束",
        ],
        "more_ex": [
            ("上限 2 发", "改 len 判断"),
            ("彩球分", "加码 points"),
        ],
    },
    8: {
        "warmup": ("热身：球撞四壁", "不要挡板。确认上下左右都会反弹，画面平滑。",
                   "if ball.ycor() > 280:\n    ball.sety(280)\n    ball.dy *= -1"),
        "challenge": ("加码：自动挡板", "右边 sety(ball.ycor())，变成单人电脑。",
                      "right.sety(ball.ycor())"),
        "mistakes": [
            ("反弹不拉回场内", "先 sety(280) 再取反", "否则卡墙闪烁"),
            ("两套键绑同一挡板", "left 和 right 分开", "两人会抢"),
            ("出界不重置", "reset_ball", "球飞丢"),
        ],
        "more_slides": [
            ("打到挡板就加速", "abs(dx)+0.3 再带上方向。后期会非常刺激，注意别快到看不清。",
             "ball.dx = abs(ball.dx) + 0.3"),
            ("自定义属性完全合法", "ball.dx 不是官方方法，是我们挂上去的数字。海龟也是普通对象。",
             "ball.dx = 4\nball.dy = 3"),
        ],
        "more_blanks": [
            "左边玩家用 W 和 ________",
            "先到 ________ 分获胜（本课默认）",
            "dx 乘 -1 会让球在 ________ 方向掉头",
        ],
        "more_ex": [
            ("先到 7 分", "改阈值"),
            ("电脑挡板", "加码 sety"),
        ],
    },
    9: {
        "warmup": ("热身：三节跟着走", "固定长度，能转弯，不吃、不死。看懂倒序抄坐标。",
                   "for i in range(len(snake)-1, 0, -1):\n    snake[i].goto(snake[i-1].xcor(), snake[i-1].ycor())"),
        "challenge": ("加码：穿墙", "x 出界时 goto(-x, y)，不要 game_over。",
                      "if abs(nx) > 280:\n    nx = -nx"),
        "mistakes": [
            ("从头往后抄坐标", "从尾巴往前", "否则叠成一团"),
            ("允许 180 掉头", "差 180 就 return", "立刻自撞"),
            ("食物刷在身上", "随机直到空地", "一帧连吃"),
        ],
        "more_slides": [
            ("网格让碰撞变简单", "STEP=20，食物坐标也是 20 的倍数。对不齐会吃得很别扭。",
             "x = random.randint(-13, 13) * STEP"),
            ("缓冲 pending", "同一帧可能连按两次。先记下 pending，下一格再生效，手感更好。",
             "if pending is not None:\n    direction = pending"),
        ],
        "more_blanks": [
            "本课一格是 ________ 像素",
            "自撞检测从 snake[________:] 开始（不含头）",
            "吃到食物调用 ________ 让身体变长",
        ],
        "more_ex": [
            ("初始 5 节", "改开头 for"),
            ("穿墙", "加码模式"),
        ],
    },
    10: {
        "warmup": ("热身：只有菜单", "空格文字消失玩家出现；R 回到「按空格开始」。先把状态跑顺。",
                   "if state == 'menu':\n    start_game()"),
        "challenge": ("加码：Boss 色", "第 5 波起敌人 color 改成紫色。",
                      "if wave >= 5:\n    e.color('#9B59B6')"),
        "mistakes": [
            ("菜单时敌人还在掉", "tick 开头判断 state", "否则菜单被打穿"),
            ("clear 列表不 hideturtle", "先藏再丢", "幽灵子弹"),
            ("空格不判断 state", "菜单开始 / 游戏射击", "两种含义要分支"),
        ],
        "more_slides": [
            ("菜单里 tick 也不能停", "停了 ontimer 链就断了，再按空格没人把循环接上。",
             "if state != 'play':\n    screen.update()\n    screen.ontimer(tick, 20)\n    return"),
            ("结业：你已经会做完整游戏", "窗口、输入、循环、碰撞、列表、状态。Pygame 只是把海龟换成图片。",
             "state / tick / distance / 列表 / 清场"),
        ],
        "more_blanks": [
            "三个状态是 menu、play、________",
            "漏到屏幕底部会扣 ________",
            "按 R 回到 ________ 状态",
        ],
        "more_ex": [
            ("改游戏名", "title 和菜单大字"),
            ("Boss 色", "加码第 5 波"),
        ],
    },
}


def apply_enrich():
    for L in LESSONS:
        e = ENRICH.get(L["n"], {})
        L["knowledge_slides"] = L.get("knowledge_slides", []) + e.get("more_slides", [])
        L["blanks"] = L.get("blanks", []) + e.get("more_blanks", [])
        L["ex"] = L.get("ex", []) + e.get("more_ex", [])
        for key in ("warmup", "challenge", "mistakes"):
            if key in e:
                L[key] = e[key]

apply_enrich()



PPT_CSS = r"""
  .slide { padding: 56px 72px; display: flex; flex-direction: column; justify-content: center; }
  .slide.full { justify-content: center; align-items: center; text-align: center; }
  .slide.full .deck-footer { position: absolute; bottom: 28px; left: 56px; right: 56px; }
  .slide .deck-footer { position: absolute; bottom: 28px; left: 56px; right: 56px; }
  .h1 { font-family: 'Inter','Noto Sans SC',sans-serif; font-size: 64px; line-height: 1.08; font-weight: 800; letter-spacing: -0.02em; color: var(--text-1); }
  .h2 { font-family: 'Inter','Noto Sans SC',sans-serif; font-size: 44px; line-height: 1.15; font-weight: 700; letter-spacing: -0.015em; color: var(--text-1); }
  .kicker { font-size: 12px; font-weight: 700; letter-spacing: .14em; text-transform: uppercase; color: var(--accent); }
  .lede { font-size: 20px; color: var(--text-2); line-height: 1.7; max-width: 64ch; }
  .bullet-card { background: var(--surface); border: 1px solid var(--border); border-radius: var(--radius); padding: 20px 24px; }
  .bullet-card h4 { margin: 0 0 6px; color: var(--accent); font-size: 17px; }
  .bullet-card p { margin: 0; font-size: 15px; color: var(--text-2); line-height: 1.6; }
  .code-card { background: #1e1f29; border-radius: var(--radius); padding: 20px 24px; overflow: auto; }
  .code-card pre { margin: 0; }
  .code-card code { font-family: 'JetBrains Mono','Fira Code',monospace; font-size: 15px; line-height: 1.75; }
  .ic { font-family: 'JetBrains Mono','Fira Code',monospace; background: var(--surface-2); padding: 2px 8px; border-radius: 4px; font-size: .9em; color: var(--accent-2); }
  .sum-table { width: 100%; border-collapse: collapse; font-size: 15px; }
  .sum-table th { padding: 12px 16px; text-align: left; font-size: 11px; text-transform: uppercase; letter-spacing: .1em; color: var(--text-3); font-weight: 600; border-bottom: 2px solid var(--border-strong); }
  .sum-table td { padding: 12px 16px; border-bottom: 1px solid var(--border); color: var(--text-2); }
  .sum-table td:first-child { font-family: 'JetBrains Mono',monospace; color: var(--accent-2); font-size: 14px; }
  .grad { background: var(--grad); -webkit-background-clip: text; -webkit-text-fill-color: transparent; background-clip: text; }
  .callout { border-left: 4px solid var(--accent); background: var(--surface); padding: 16px 20px; border-radius: 0 var(--radius) var(--radius) 0; font-size: 15px; color: var(--text-2); }
  .callout b { color: var(--accent-2); }
  .ex-item { background: var(--surface); border: 1px solid var(--border); border-radius: var(--radius); padding: 16px 20px; display: flex; gap: 14px; align-items: flex-start; }
  .ex-num { flex: none; width: 28px; height: 28px; border-radius: 50%; background: var(--surface-2); border: 2px solid var(--accent); color: var(--accent); display: flex; align-items: center; justify-content: center; font-weight: 700; font-size: 13px; }
  .ex-item p { margin: 0; color: var(--text-2); font-size: 14px; line-height: 1.5; }
  .code-btn { display: inline-flex; align-items: center; gap: 8px; padding: 12px 28px; background: var(--accent); color: #fff; border: none; border-radius: 8px; font-size: 16px; font-weight: 600; cursor: pointer; text-decoration: none; transition: all .2s; margin-top: 24px; }
  .code-btn:hover { background: var(--accent-2); transform: translateY(-2px); }
  .print-btn { display: inline-flex; align-items: center; gap: 8px; padding: 12px 28px; background: transparent; color: var(--text-1); border: 1px solid var(--border); border-radius: 8px; font-size: 16px; font-weight: 600; cursor: pointer; text-decoration: none; margin-top: 24px; margin-left: 12px; }
"""


def footer(lesson, i, total, extra_class=""):
    return (
        f'<div class="deck-footer"><span class="dim2">第 {lesson["n"]} 课 · {lesson["title"]}</span>'
        f'<span class="slide-number" data-current="{i}" data-total="{total}"></span></div>'
    )


def notes(text):
    return f'<div class="notes">{html.escape(text)}</div>'


def code_block(src):
    return (
        '<div class="code-card"><pre><code class="language-python">'
        + html.escape(src)
        + "</code></pre></div>"
    )


def build_ppt(lesson):
    slides = []
    n = lesson["n"]
    title = lesson["title"]
    # we'll fill totals later
    tmp = []

    def add(title_attr, body, note):
        tmp.append((title_attr, body, note))

    add(
        "Cover",
        f"""
    <p class="kicker anim-fade-down" data-anim="fade-down" style="color:var(--accent-2)">从零开始用 Turtle 做游戏 · 第 {n} 课</p>
    <h1 class="h1 anim-rise-in" data-anim="rise-in" style="font-size:72px;margin-top:12px">{lesson["icon"]} <span class="grad">{html.escape(title)}</span></h1>
    <p class="lede anim-fade-up" data-anim="fade-up" style="margin-top:16px;font-size:22px">{html.escape(lesson["subtitle"])}</p>
    <div class="row wrap anim-fade-up" data-anim="fade-up" style="margin-top:32px;gap:12px;justify-content:center">
      <span class="pill" style="background:rgba(189,147,249,.15);color:var(--accent);border:1px solid rgba(189,147,249,.3)">90 分钟</span>
      <span class="pill" style="background:rgba(139,233,253,.15);color:var(--accent-3);border:1px solid rgba(139,233,253,.3)">热身 + 小游戏 + 加码</span>
      <span class="pill" style="background:rgba(255,121,198,.15);color:var(--accent-2);border:1px solid rgba(255,121,198,.3)">主项目 · {html.escape(lesson["project"])}</span>
    </div>
    <div>
      <a href="../code/lesson{n}.py" target="_blank" class="code-btn"><span class="btn-icon">📄</span> 查看完整代码</a>
      <a href="../打印/lesson{n:02d}.html" target="_blank" class="print-btn">🖨️ 打印学案</a>
    </div>
    """,
        f"欢迎来到第{n}课，今天 90 分钟。主项目是「{lesson['project']}」。流程：热身练手感 → 主项目交付 → 加码给吃得快的同学。主项目能跑就算过关。",
    )

    ghtml = []
    for icon, h, p in lesson["goals"]:
        ghtml.append(
            f'<div class="bullet-card" style="display:flex;gap:16px;align-items:flex-start">'
            f'<span style="font-size:32px">{icon}</span><div><h4>{html.escape(h)}</h4>'
            f"<p>{html.escape(p)}</p></div></div>"
        )
    add(
        "本课目标",
        f"""
    <p class="kicker">🎯 本课目标</p>
    <h2 class="h2" style="margin-top:6px">今天要拿下的 <span class="grad">几件事</span></h2>
    <div class="grid g2 anim-stagger-list" data-anim-target style="margin-top:32px;gap:18px">
      {''.join(ghtml)}
    </div>
    """,
        "语法点加主项目。90 分钟里主项目是过关线，加码是选做。",
    )

    timing = [
        ("0–10 分", "开场 / 复习", "打开本课文件；复习上节 3 道口答题"),
        ("10–35 分", "新知识 + 热身", "讲语法，跟打热身代码，对照输出"),
        ("35–65 分", "主项目", "拆成若干步，一步一运行，改成自己的数据"),
        ("65–82 分", "加码挑战", "先完成的人做加码；其他人继续主项目"),
        ("82–90 分", "学案 + 小结", "填空、互讲一个知识点、听下节预告"),
    ]
    trows = "".join(
        f"<tr><td>{html.escape(a)}</td><td>{html.escape(b)}</td><td>{html.escape(c)}</td></tr>"
        for a, b, c in timing
    )
    add(
        "90分钟节奏",
        f"""
    <p class="kicker">⏱️ 课堂节奏</p>
    <h2 class="h2" style="margin-top:6px">今天 <span class="grad">90 分钟</span> 怎么用</h2>
    <div class="card" style="padding:12px 8px;margin-top:24px">
      <table class="sum-table">
        <thead><tr><th>时间</th><th>环节</th><th>做什么</th></tr></thead>
        <tbody>{trows}</tbody>
      </table>
    </div>
    <div class="callout" style="margin-top:18px"><b>过关线：</b> 主项目能独立运行。加码不是全班必须完成。</div>
    """,
        "把 90 分钟写在黑板上。主项目 30 分钟不要压缩。加码是分层作业，不是拖堂理由。",
    )

    for hs, lede, src in lesson["knowledge_slides"]:
        add(
            hs,
            f"""
    <p class="kicker">📚 新知识</p>
    <h2 class="h2" style="margin-top:6px">{html.escape(hs)}</h2>
    <p class="lede" style="margin-top:10px">{html.escape(lede)}</p>
    <div style="margin-top:24px">{code_block(src)}</div>
    """,
            lede,
        )

    rows = "".join(
        f"<tr><td>{html.escape(a)}</td><td>{html.escape(b)}</td><td>{html.escape(c)}</td></tr>"
        for a, b, c in lesson["know_rows"]
    )
    add(
        "速查表",
        f"""
    <p class="kicker">📋 速查</p>
    <h2 class="h2" style="margin-top:6px">本课语法 <span class="grad">一张表</span></h2>
    <div class="card" style="padding:12px 8px;margin-top:24px">
      <table class="sum-table">
        <thead><tr><th>写法</th><th>是什么</th><th>记住</th></tr></thead>
        <tbody>{rows}</tbody>
      </table>
    </div>
    """,
        "这张表可以对照打印学案。课堂上先看表，再写项目。",
    )

    add(
        "本节项目",
        f"""
    <p class="kicker">⭐ 本节项目</p>
    <h2 class="h2" style="margin-top:6px">{html.escape(lesson["project"])}</h2>
    <p class="lede" style="margin-top:10px">用刚刚的语法，做一个能当场演示的小程序。</p>
    <div class="io-card" style="margin-top:22px;background:var(--surface);border:1px solid var(--border);border-radius:var(--radius);padding:18px 22px">
      <div style="font-size:12px;color:var(--text-3);letter-spacing:.1em;margin-bottom:8px">运行效果（示例）</div>
      <pre style="margin:0;font-family:'JetBrains Mono',monospace;font-size:15px;line-height:1.7;color:var(--text-1);white-space:pre-wrap">{html.escape(lesson["io"])}</pre>
    </div>
    """,
        f"项目是{lesson['project']}。先看输入输出长什么样，再打开代码跟做。",
    )

    add(
        "关键代码",
        f"""
    <p class="kicker">💻 关键代码</p>
    <h2 class="h2" style="margin-top:6px">先看懂这几行</h2>
    <p class="lede" style="margin-top:8px">完整程序在 <span class="ic">code/lesson{n}.py</span>，这里只抓核心。</p>
    <div style="margin-top:22px">{code_block(lesson["code"])}</div>
    <div class="callout" style="margin-top:20px"><b>跟做建议：</b> 先把这几行跑通，再去补打印格式和边框。</div>
    """,
        "不要一上来复制全文。先让核心逻辑跑起来，再美化输出。",
    )

    if lesson.get("warmup"):
        wh, wl, wc = lesson["warmup"]
        add(
            "热身",
            f"""
    <p class="kicker">🔥 10–35 分 · 热身</p>
    <h2 class="h2" style="margin-top:6px">{html.escape(wh)}</h2>
    <p class="lede" style="margin-top:10px">{html.escape(wl)}</p>
    <div style="margin-top:22px">{code_block(wc)}</div>
    <div class="callout" style="margin-top:18px"><b>课堂：</b> 学生必须自己打一遍，不要只看老师演示。</div>
    """,
            wl,
        )

    if lesson.get("challenge"):
        ch, cl, cc = lesson["challenge"]
        add(
            "加码",
            f"""
    <p class="kicker">🚀 65–82 分 · 加码（选做）</p>
    <h2 class="h2" style="margin-top:6px">{html.escape(ch)}</h2>
    <p class="lede" style="margin-top:10px">{html.escape(cl)}</p>
    <div style="margin-top:22px">{code_block(cc)}</div>
    <div class="callout" style="margin-top:18px"><b>分层：</b> 主项目还没跑通的同学不要跳到加码。先完成再挑战。</div>
    """,
            cl,
        )

    if lesson.get("mistakes"):
        mhtml = []
        for bad, good, why in lesson["mistakes"]:
            mhtml.append(
                f'<div class="bullet-card"><h4>❌ {html.escape(bad)}</h4>'
                f"<p>✅ {html.escape(good)}<br>{html.escape(why)}</p></div>"
            )
        add(
            "常见错误",
            f"""
    <p class="kicker">🐞 改错时刻</p>
    <h2 class="h2" style="margin-top:6px">这几类错，<span class="grad">课上必踩</span></h2>
    <div class="grid g1 anim-stagger-list" data-anim-target style="margin-top:24px;gap:12px">
      {''.join(mhtml)}
    </div>
    """,
            "用投影仪打错误代码，让学生找茬。改错 5 分钟很值钱，比再讲一遍概念有效。",
        )

    exs = []
    for i, (h, p) in enumerate(lesson["ex"], 1):
        exs.append(
            f'<div class="ex-item"><div class="ex-num">{i}</div>'
            f'<div><b style="color:var(--text-1)">{html.escape(h)}</b><p>{html.escape(p)}</p></div></div>'
        )
    add(
        "小练习",
        f"""
    <p class="kicker">✏️ 小练习</p>
    <h2 class="h2" style="margin-top:6px">动动手，<span class="grad">改一改</span></h2>
    <div class="grid g2 anim-stagger-list" data-anim-target style="margin-top:24px;gap:14px">
      {''.join(exs)}
    </div>
    """,
        "前几个改参数，后面才是挑战。做不完可以当课后作业，打印学案上也有填空。",
    )

    srows = "".join(
        f"<tr><td>{html.escape(a)}</td><td>{html.escape(b)}</td><td>{html.escape(c)}</td></tr>"
        for a, b, c in lesson["sum_rows"]
    )
    add(
        "本课小结",
        f"""
    <p class="kicker" style="color:var(--accent-2)">🧠 本课小结</p>
    <h1 class="h1" style="font-size:48px;margin-top:8px">你今天<span class="grad">学到了</span></h1>
    <div style="max-width:900px;width:100%;margin-top:24px">
      <div class="card" style="padding:16px 20px">
        <table class="sum-table">
          <thead><tr><th>知识</th><th>是什么</th><th>怎么用</th></tr></thead>
          <tbody>{srows}</tbody>
        </table>
      </div>
    </div>
    <div class="callout" style="margin-top:22px;max-width:900px;width:100%">
      <b>📖 下一课：</b> {html.escape(lesson["next"])}
    </div>
    """,
        lesson["next"],
    )

    total = len(tmp)
    out = []
    for i, (t, body, note) in enumerate(tmp, 1):
        klass = "slide full" if i in (1, total) else "slide"
        out.append(
            f'<section class="{klass}" data-title="{html.escape(t)}">\n'
            f"{body}\n{footer(lesson, i, total)}\n{notes(note)}\n</section>"
        )
    inner = "\n\n".join(out)
    return f"""<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>第{n}课 · {html.escape(title)}</title>
<link rel="stylesheet" href="assets/fonts.css">
<link rel="stylesheet" href="assets/base.css">
<link rel="stylesheet" id="theme-link" href="assets/themes/dracula.css">
<link rel="stylesheet" href="assets/animations/animations.css">
<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/highlight.js@11.10.0/styles/dracula.min.css">
<script src="https://cdn.jsdelivr.net/npm/highlight.js@11.10.0/lib/core.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/highlight.js@11.10.0/lib/languages/python.min.js"></script>
<script>addEventListener('DOMContentLoaded',()=>{{hljs.registerLanguage('python',window.hljsLangPython||window.hljs.getLanguage('python'));document.querySelectorAll('pre code').forEach(el=>hljs.highlightElement(el))}})</script>
<style>{PPT_CSS}</style>
</head>
<body>
<div class="deck" data-themes="dracula,tokyo-night,catppuccin-mocha,nord,terminal-green,cyberpunk-neon" data-theme-base="assets/themes/">
{inner}
</div>
<script src="assets/runtime.js"></script>
<script src="assets/animations/fx-runtime.js"></script>
<script src="courseware-ui.js"></script>
</body>
</html>
"""


def build_print(lesson):
    n = lesson["n"]
    rows = "".join(
        f"<tr><td class='mono'>{html.escape(a)}</td><td>{html.escape(b)}</td>"
        f"<td class='mono'>{html.escape(c)}</td></tr>"
        for a, b, c in lesson["print_know"]
    )
    steps = "".join(f"<li>{html.escape(s)}</li>" for s in lesson["steps"])
    blanks = []
    for i, q in enumerate(lesson["blanks"], 1):
        blanks.append(
            f'<div class="ex"><div class="q">{i}. {html.escape(q)}</div>'
            f'<div class="lines"><div class="line"></div></div></div>'
        )
    prev_href = f"lesson{n-1:02d}.html" if n > 1 else "index.html"
    next_href = f"lesson{n+1:02d}.html" if n < 10 else "index.html"
    return f"""<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>第{n}课学案 · {html.escape(lesson["title"])}</title>
<link rel="stylesheet" href="print.css">
</head>
<body>
<div class="toolbar">
  <div>
    <a href="index.html">全部学案</a>
    <a href="{prev_href}">上一课</a>
    <a href="{next_href}">下一课</a>
  </div>
  <button class="print-btn" onclick="window.print()">🖨️ 打印本页（A4）</button>
</div>
<article class="sheet">
  <header class="hdr">
    <div>
      <div class="course">TURTLE 做游戏 · 学案</div>
      <h1>第 {n} 课　{html.escape(lesson["title"])}</h1>
    </div>
    <div class="meta">
      姓名 <span class="blank"></span><br>
      日期 <span class="blank"></span>
    </div>
  </header>

  <h2>一、本课目标（90 分钟）</h2>
  <p>学会 <strong>{html.escape(lesson["subtitle"])}</strong>。过关：主项目「<strong>{html.escape(lesson["project"])}</strong>」能运行。加码选做。</p>
  <table>
    <thead><tr><th>时间</th><th>环节</th></tr></thead>
    <tbody>
      <tr><td>0–10</td><td>开场 / 复习</td></tr>
      <tr><td>10–35</td><td>新知识 + 热身</td></tr>
      <tr><td>35–65</td><td>主项目跟做</td></tr>
      <tr><td>65–82</td><td>加码（选做）</td></tr>
      <tr><td>82–90</td><td>学案填空 + 小结</td></tr>
    </tbody>
  </table>

  <h2>二、知识点速查（可剪下来当小抄）</h2>
  <table>
    <thead><tr><th>名称</th><th>意思</th><th>写法 / 例子</th></tr></thead>
    <tbody>{rows}</tbody>
  </table>

  <h2>三、热身（10–35 分）</h2>
  <p><strong>{html.escape(lesson.get("warmup", ("热身",))[0])}</strong> — {html.escape(lesson.get("warmup", ("", "跟打 code/lesson"+str(n)+".py 上半段"))[1] if lesson.get("warmup") else "跟打代码上半段。")}</p>
  <ul class="steps">
    <li>自己把热身代码打一遍并运行</li>
    <li>对照输出，和同桌讲清「刚才那一行在干什么」</li>
  </ul>

  <h2>四、主项目任务单（35–65 分）</h2>
  <p>项目名称：<strong>{html.escape(lesson["project"])}</strong>　配套代码：<span class="mono">code/lesson{n}.py</span></p>
  <div class="io">{html.escape(lesson["io"])}</div>
  <ul class="steps">{steps}</ul>

  <h2>五、加码（65–82 分，选做）</h2>
  <p><strong>{html.escape(lesson.get("challenge", ("加码",))[0])}</strong></p>
  <p>{html.escape(lesson.get("challenge", ("", "见教案加码部分"))[1] if lesson.get("challenge") else "见教案。")}</p>
  <ul class="steps">
    <li>主项目还没跑通 → 继续主项目，不要跳到加码</li>
    <li>主项目已跑通 → 做加码，改成自己的数据</li>
  </ul>

  <h2>六、改错</h2>
  {"".join(
      f"<p><strong>{i}.</strong> 错：<span class='mono'>{html.escape(bad)}</span><br>对：________　　原因：________</p>"
      for i, (bad, _good, _why) in enumerate(lesson.get("mistakes") or [], 1)
  ) or "<p>（本课改错见课件）</p>"}

  <h2>七、课堂填空</h2>
  {''.join(blanks)}

  <h2>八、改一改（写在纸上或改代码）</h2>
  <ol>
    {''.join(f'<li>{html.escape(h)}：{html.escape(p)}</li>' for h, p in lesson['ex'])}
  </ol>

  <h2>九、下课打卡</h2>
  <p>☐ 热身跑通　☐ 主项目能运行　☐ 加码已尝试（或主项目加时完成）　☐ 能向同桌讲清一个知识点　☐ 姓名已写</p>
  <p>今天最大的收获：</p>
  <div class="lines"><div class="line"></div><div class="line"></div></div>

  <div class="foot">
    <span>下一课：{html.escape(lesson["next_short"])}</span>
    <span>第 {n} / 10 课</span>
  </div>
</article>
</body>
</html>
"""


VIEW_TMPL = """<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>{filename}</title>
<style>
  :root {{
    --bg: #f5f7fa; --panel: #ffffff; --text: #1a1a2e; --muted: #5a6570;
    --gold: #b8860b; --code-bg: #ffffff; --code-text: #1f2933;
    --border: #d8dee6; --top-bg: #ffffff; --top-border: #e5e9ef;
  }}
  * {{ box-sizing: border-box; }}
  html, body {{
    margin: 0; padding: 0; background: var(--bg); color: var(--text);
    font-family: -apple-system, BlinkMacSystemFont, "PingFang SC", "Microsoft YaHei", sans-serif;
    min-height: 100%;
  }}
  .top {{
    position: sticky; top: 0; z-index: 10;
    display: flex; flex-wrap: wrap; align-items: center; justify-content: space-between;
    gap: 10px; padding: 12px 18px; background: var(--top-bg);
    border-bottom: 1px solid var(--top-border); box-shadow: 0 1px 8px rgba(15, 23, 42, 0.06);
  }}
  .brand {{ color: var(--gold); font-weight: 700; font-size: 14px; letter-spacing: 0.04em; }}
  .title {{ font-size: 15px; font-weight: 600; color: var(--text); }}
  .actions {{ display: flex; gap: 8px; flex-wrap: wrap; }}
  .btn {{
    appearance: none; border: 1px solid var(--border); background: #fff; color: var(--text);
    border-radius: 999px; padding: 8px 14px; font-size: 13px; font-weight: 600;
    text-decoration: none; cursor: pointer;
  }}
  .btn.gold {{ background: linear-gradient(135deg, #f0d78c, #d4a853); color: #0a2540; border-color: #e0c06a; }}
  .meta {{
    padding: 10px 18px; color: var(--muted); font-size: 12px;
    border-bottom: 1px solid var(--border); background: var(--panel);
  }}
  .wrap {{ padding: 16px 18px 40px; }}
  pre {{
    margin: 0; background: var(--code-bg); color: var(--code-text);
    border: 1px solid var(--border); border-radius: 12px; padding: 18px 20px;
    overflow: auto; font-family: "SF Mono", "JetBrains Mono", Consolas, "Courier New", monospace;
    font-size: 13.5px; line-height: 1.55; white-space: pre; tab-size: 4;
  }}
  .hint {{ margin-top: 12px; color: var(--muted); font-size: 12px; }}
  @media print {{
    html, body {{ background: #fff !important; color: #000 !important; }}
    .top {{ position: static; box-shadow: none; border-bottom: 1px solid #ccc; background: #fff !important; }}
    .actions {{ display: none !important; }}
    .meta {{ background: #fff !important; border-color: #ddd; color: #333; }}
    .wrap {{ padding: 0; }}
    pre {{
      background: #fff !important; color: #000 !important;
      border: 1px solid #bbb; box-shadow: none; border-radius: 0;
      white-space: pre-wrap; word-break: break-word; font-size: 11pt; line-height: 1.4;
    }}
    .hint {{ display: none; }}
    a {{ color: #000; text-decoration: none; }}
  }}
</style>
</head>
<body>
  <div class="top">
    <div class="brand">从零开始用 Turtle 做游戏 · 配套代码</div>
    <div class="title">{filename}</div>
    <div class="actions">
      <a class="btn" href="../{filename}" download="{filename}">⬇️ 下载源文件</a>
      <a class="btn" href="javascript:window.print()">🖨️ 打印代码</a>
      <a class="btn gold" href="javascript:history.back()">← 返回课件</a>
    </div>
  </div>
  <div class="meta">编码：UTF-8 · 文件：{filename} · 共 {lines} 行 · 浅色主题便于打印</div>
  <div class="wrap">
    <pre id="code">{code}</pre>
    <p class="hint">本页使用浅色主题与 UTF-8 编码，可直接打印或导出 PDF。</p>
  </div>
</body>
</html>
"""


def build_print_index():
    cards = []
    for L in LESSONS:
        cards.append(
            f'<a class="card" href="lesson{L["n"]:02d}.html">'
            f'<div class="num">第 {L["n"]:02d} 课</div>'
            f'<div class="t">{html.escape(L["title"])} — {html.escape(L["project"])}</div>'
            f"</a>"
        )
    return f"""<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>打印学案 · 从零开始用 Turtle 做游戏</title>
<link rel="stylesheet" href="print.css">
<style>
  .wrap {{ max-width: 860px; margin: 0 auto; padding: 24px 16px 48px; }}
  h1 {{ font-size: 22pt; margin: 8px 0 6px; }}
  .lead {{ color: #444; margin-bottom: 18px; }}
  .cards {{ display: grid; grid-template-columns: 1fr 1fr; gap: 10px; }}
  .card {{
    display: block; background: #fff; border: 1px solid #ddd; border-radius: 10px;
    padding: 14px 16px; text-decoration: none; color: #111;
  }}
  .card .num {{ font-size: 11pt; color: #0b5cab; font-weight: 700; }}
  .card .t {{ font-size: 13pt; font-weight: 650; margin-top: 4px; }}
  .hintbox {{ background: #fff; border: 1px dashed #aaa; padding: 12px 14px; margin: 16px 0 20px; }}
  @media print {{
    .toolbar {{ display: none !important; }}
    .wrap {{ padding: 0; }}
    .card {{ break-inside: avoid; }}
  }}
</style>
</head>
<body>
<div class="toolbar">
  <a href="../ppt/总览.html">← 返回课程总览</a>
  <a href="全部.html">📄 一次打印全部 10 课</a>
  <span style="color:#666">打开任意一课 → 点「打印本页」；纸张选 A4</span>
</div>
<div class="wrap">
  <div class="course">TURTLE 海龟做游戏</div>
  <h1>配套打印学案（10 课）</h1>
  <p class="lead">每课一页 A4：知识点小抄 + 项目任务单 + 填空。浏览器打开后按 Ctrl / Cmd + P，背景图形可关闭以省墨。</p>
  <div class="hintbox">
    <strong>打印建议：</strong> 纸张 A4 · 纵向 · 边距默认 · 取消「页眉页脚」可更干净。
    需要把代码也印出来时，打开 <span class="mono">code/view/lessonN.html</span> 再打印。
    整套 10 课一次打完：打开 <a href="全部.html">全部.html</a> 再打印。
  </div>
  <div class="cards">
    {''.join(cards)}
  </div>
</div>
</body>
</html>
"""


def build_print_all():
    sheets = []
    for L in LESSONS:
        page = build_print(L)
        start = page.find("<article")
        end = page.find("</article>") + len("</article>")
        sheets.append(page[start:end])
    body = "\n".join(sheets)
    return f"""<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="UTF-8">
<title>从零开始用 Turtle 做游戏 · 全部学案（10 课）</title>
<link rel="stylesheet" href="print.css">
<style>
  .sheet {{ page-break-after: always; box-shadow: none; margin: 12px auto; }}
  .sheet:last-of-type {{ page-break-after: auto; }}
  @media print {{
    .sheet {{ margin: 0; page-break-after: always; }}
    .sheet:last-of-type {{ page-break-after: auto; }}
  }}
</style>
</head>
<body>
<div class="toolbar">
  <a href="index.html">← 学案目录</a>
  <button class="print-btn" onclick="window.print()">🖨️ 一次打印全部 10 课</button>
</div>
{body}
</body>
</html>
"""


def _lesson_card(L):
    return (
        f'<a href="lesson{L["n"]:02d}.html" class="lesson-card">'
        f'<div class="lesson-num">🎮 第{L["n"]:02d}课</div>'
        f'<div class="lesson-title">{html.escape(L["title"])} — {html.escape(L["subtitle"].split("、")[0])}'
        f'<span class="lesson-proj">游戏：{html.escape(L["project"])}</span>'
        f"</div></a>"
    )


def build_overview():
    stages = [
        ("🐢", "海龟听话了", "第 1 ~ 3 课 · 窗口、键盘、鼠标", [1, 2, 3]),
        ("🎞️", "画面自己动", "第 4 ~ 6 课 · 循环、碰撞、难度", [4, 5, 6]),
        ("🎯", "对打与射击", "第 7 ~ 8 课 · 子弹列表、双人反弹", [7, 8]),
        ("🚀", "完整游戏", "第 9 ~ 10 课 · 贪吃蛇与状态机毕业作", [9, 10]),
    ]
    by_n = {L["n"]: L for L in LESSONS}
    stage_html = []
    for icon, title, rng, nums in stages:
        cards = "".join(_lesson_card(by_n[n]) for n in nums)
        stage_html.append(
            f"""
    <div class="stage-section">
        <div class="stage-header">
            <div class="stage-icon">{icon}</div>
            <div class="stage-info">
                <h2>{html.escape(title)}</h2>
                <div class="stage-range">{html.escape(rng)}</div>
            </div>
        </div>
        <div class="lesson-grid">{cards}</div>
    </div>"""
        )
    return f"""<!DOCTYPE html>
<html lang="zh-CN">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>从零开始用 Turtle 做游戏 — 课程总览</title>
    <style>
        * {{ margin: 0; padding: 0; box-sizing: border-box; }}
        body {{
            font-family: 'PingFang SC', 'Microsoft YaHei', 'Noto Sans SC', sans-serif;
            background: linear-gradient(135deg, #e0f2f1 0%, #b2dfdb 30%, #c8e6c9 70%, #e8f5e9 100%);
            min-height: 100vh; color: #37474f;
        }}
        .header {{
            background: linear-gradient(135deg, #004d40 0%, #00695c 50%, #00838f 100%);
            color: white; text-align: center; padding: 55px 20px 50px;
            border-radius: 0 0 60px 60px; position: relative; overflow: hidden;
        }}
        .header::before {{
            content: ''; position: absolute; top: -80px; left: -80px;
            width: 200px; height: 200px; background: rgba(255,255,255,0.12); border-radius: 50%;
        }}
        .header::after {{
            content: ''; position: absolute; bottom: -60px; right: -60px;
            width: 180px; height: 180px; background: rgba(255,255,255,0.10); border-radius: 50%;
        }}
        .header h1 {{
            font-size: 2.8em; margin-bottom: 10px; text-shadow: 3px 3px 6px rgba(0,0,0,0.15);
            position: relative; z-index: 1;
        }}
        .header .subtitle, .header .desc {{ position: relative; z-index: 1; }}
        .header .subtitle {{ font-size: 1.3em; opacity: 0.95; margin-bottom: 8px; }}
        .header .desc {{
            font-size: 1.02em; opacity: 0.85; max-width: 740px; margin: 0 auto; line-height: 1.7;
        }}
        .main-container {{ max-width: 1000px; margin: 0 auto 60px; padding: 0 25px; }}
        .stats-bar {{
            display: flex; justify-content: center; gap: 25px; flex-wrap: wrap;
            margin: -35px 0 25px; position: relative; z-index: 3;
        }}
        .stat-item {{
            background: white; padding: 16px 26px; border-radius: 18px; text-align: center;
            min-width: 120px; box-shadow: 0 8px 30px rgba(0,0,0,0.10); transition: transform 0.3s;
        }}
        .stat-item:hover {{ transform: translateY(-4px) scale(1.04); }}
        .stat-item .stat-num {{ font-size: 2em; font-weight: bold; color: #00695c; }}
        .stat-item .stat-label {{ font-size: 0.9em; color: #999; margin-top: 4px; }}
        .quick-links {{
            display: flex; justify-content: center; gap: 12px; flex-wrap: wrap; margin-bottom: 22px;
        }}
        .quick-links a {{
            background: #fff; color: #00695c; text-decoration: none; font-weight: 700;
            font-size: 0.95em; padding: 10px 18px; border-radius: 999px;
            box-shadow: 0 4px 16px rgba(0,105,92,0.12);
        }}
        .quick-links a:hover {{ background: #e0f2f1; }}
        .stage-section {{
            background: white; border-radius: 24px; padding: 28px 28px 22px;
            margin-bottom: 22px; box-shadow: 0 6px 30px rgba(0,0,0,0.08);
        }}
        .stage-header {{
            display: flex; align-items: center; margin-bottom: 18px;
            padding-bottom: 14px; border-bottom: 3px dashed #b2dfdb;
        }}
        .stage-icon {{
            font-size: 2.6em; margin-right: 16px; width: 60px; height: 60px;
            display: flex; align-items: center; justify-content: center;
            border-radius: 16px; flex-shrink: 0; background: #e0f2f1;
        }}
        .stage-info h2 {{ font-size: 1.5em; margin-bottom: 3px; color: #004d40; }}
        .stage-info .stage-range {{ font-size: 0.9em; color: #aaa; }}
        .lesson-grid {{
            display: grid; grid-template-columns: repeat(auto-fill, minmax(280px, 1fr)); gap: 12px;
        }}
        .lesson-card {{
            display: flex; align-items: center; gap: 12px; padding: 14px 18px;
            background: #f1faf6; border-radius: 12px; border-left: 4px solid #26a69a;
            text-decoration: none; color: #37474f; transition: all 0.25s;
        }}
        .lesson-card:hover {{
            background: #e0f2f1; transform: translateY(-2px);
            box-shadow: 0 6px 18px rgba(0,137,123,0.22);
        }}
        .lesson-num {{
            font-size: 0.82em; font-weight: bold; color: #00897b;
            min-width: 52px; white-space: nowrap;
        }}
        .lesson-title {{ font-size: 1em; font-weight: 600; line-height: 1.4; }}
        .lesson-proj {{ display: block; font-size: 0.82em; font-weight: 400; color: #789; margin-top: 2px; }}
        .back-link {{
            display: inline-block; margin-top: 10px; color: #00695c; text-decoration: none;
            font-size: 0.95em; font-weight: 600; padding: 10px 0;
        }}
        .back-link:hover {{ color: #004d40; }}
        .footer {{ text-align: center; padding: 20px; color: #999; font-size: 0.85em; }}
        @media (max-width: 768px) {{
            .header {{ padding: 35px 15px 30px; border-radius: 0 0 40px 40px; }}
            .header h1 {{ font-size: 2em; }}
            .lesson-grid {{ grid-template-columns: 1fr; }}
        }}
    </style>
</head>
<body>
<header class="header">
    <h1>🐢 从零开始用 Turtle 做游戏</h1>
    <p class="subtitle">10 节课 · 每节 90 分钟 · 每课一个可玩小游戏</p>
    <p class="desc">
        只用 Python 自带的 turtle，从点击盖章到太空大战。
        不装 Pygame。热身练 API，主游戏当堂能玩，加码给吃得快的同学。
    </p>
</header>
<main class="main-container">
    <div class="stats-bar">
        <div class="stat-item"><div class="stat-num">10</div><div class="stat-label">节课</div></div>
        <div class="stat-item"><div class="stat-num">10</div><div class="stat-label">可玩小游戏</div></div>
        <div class="stat-item"><div class="stat-num">10</div><div class="stat-label">打印学案</div></div>
        <div class="stat-item"><div class="stat-num">90</div><div class="stat-label">分钟 / 课</div></div>
    </div>
    <div class="quick-links">
        <a href="../打印/index.html">🖨️ 打印学案（A4）</a>
        <a href="../打印/全部.html">📄 一次打印全部 10 课</a>
        <a href="../课程大纲.md">📑 课程大纲</a>
        <a href="../code/view/lesson1.html">💻 第 1 课代码</a>
    </div>
    {''.join(stage_html)}
    <a href="../../index.html" class="back-link">← 返回课程总览</a>
</main>
<footer class="footer">
    <p>Python 与 C++ 开放课件 · 从零开始用 Turtle 做游戏</p>
</footer>
</body>
</html>
"""


def main():
    VIEW.mkdir(parents=True, exist_ok=True)
    PPT.mkdir(parents=True, exist_ok=True)
    PRINT.mkdir(parents=True, exist_ok=True)

    for L in LESSONS:
        n = L["n"]
        (PPT / f"lesson{n:02d}.html").write_text(build_ppt(L), encoding="utf-8")
        (PRINT / f"lesson{n:02d}.html").write_text(build_print(L), encoding="utf-8")
        src = CODE / f"lesson{n}.py"
        text = src.read_text(encoding="utf-8")
        lines = text.count("\n") + (0 if text.endswith("\n") else 1)
        (VIEW / f"lesson{n}.html").write_text(
            VIEW_TMPL.format(
                filename=f"lesson{n}.py",
                lines=lines,
                code=html.escape(text),
            ),
            encoding="utf-8",
        )
        print(f"ok lesson {n}")

    (PRINT / "index.html").write_text(build_print_index(), encoding="utf-8")
    (PRINT / "全部.html").write_text(build_print_all(), encoding="utf-8")
    (PPT / "总览.html").write_text(build_overview(), encoding="utf-8")
    print("done")


if __name__ == "__main__":
    main()
