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

LESSONS = [
    {
        "n": 1,
        "title": "电脑开口说话",
        "subtitle": "print()、字符串、注释",
        "project": "个性签名海报",
        "icon": "📣",
        "goals": [
            ("📢", "print()", "让终端显示文字"),
            ("🔤", "字符串", "用引号包起来的文字"),
            ("💬", "注释", "# 后面电脑不执行"),
            ("⭐", "项目", "打印一张个性签名海报"),
        ],
        "know_rows": [
            ("print()", "输出函数", 'print("你好")'),
            ('"..."', "字符串", "文字必须加引号"),
            ("#", "注释", "写给人看的说明"),
            ('"=" * 20', "重复", "字符串乘数字会重复"),
        ],
        "print_know": [
            ("print()", "在屏幕上显示内容", 'print("你好")'),
            ("字符串", "用引号包住的文字", '"Python" 或 \'Python\''),
            ("注释", "# 后的文字不执行", "# 这是注释"),
            ("* 重复", "字符串乘整数", '"哈" * 3 → 哈哈哈'),
        ],
        "io": "====================\n      ★ 我的名片 ★\n====================\n  姓名：小明\n  ...",
        "steps": [
            "新建 lesson1.py 并保存",
            "用 print(\"=\" * 36) 画上下边框",
            "打印姓名、学校、爱好、座右铭（改成自己的）",
            "运行，检查终端里的海报是否整齐",
        ],
        "blanks": [
            '让电脑显示「你好」：print(________)',
            "注释用什么符号开头？________",
            '"*" * 5 的结果是 ________',
            "文件扩展名必须是 ________",
        ],
        "code": 'print("你好，Python！")\nprint("=" * 20)\nprint("★" * 10)',
        "next": "第 2 课：input() 与变量 — 程序开始问你问题",
        "next_short": "和电脑对话 — input 与变量",
        "sum_rows": [
            ("print()", "输出", 'print("文字")'),
            ("字符串", "文字数据", '"你好"'),
            ("注释", "给人看", "# 说明"),
            ("*", "重复字符串", '"=" * 20'),
        ],
        "ex": [
            ("改内容", "把海报上的姓名改成自己的"),
            ("加一行", "再打印喜欢的颜色"),
            ("换边框", "把 = 改成 -"),
            ("猜输出", 'print("Python! " * 3)'),
            ("挑战", "用 print 画一个 3 行三角形"),
        ],
        "knowledge_slides": [
            ("print() 让电脑说话", "print 是函数名，括号里放要显示的内容。文字必须加引号。",
             'print("你好，Python！")'),
            ("字符串与注释", "单引号双引号都可以。# 后面是注释，电脑跳过不执行。",
             '# 这是注释\nprint("我会被显示")\nprint("哈" * 5)'),
        ],
    },
    {
        "n": 2,
        "title": "和电脑对话",
        "subtitle": "input()、变量、f-string",
        "project": "自我介绍生成器",
        "icon": "🎤",
        "goals": [
            ("⌨️", "input()", "程序停下来等你打字"),
            ("🏷️", "变量", "给数据贴标签的盒子"),
            ("🧩", "f-string", "把变量嵌进句子"),
            ("⭐", "项目", "问答生成自我介绍"),
        ],
        "know_rows": [
            ("变量", "name = \"小明\"", "把数据装进盒子"),
            ("input()", 'n = input("名字？")', "读入一行文字"),
            ("f-string", 'f"我叫{n}"', "字符串前加 f"),
        ],
        "print_know": [
            ("变量", "贴了标签的盒子", 'name = "小明"'),
            ("input()", "读取用户输入（永远是字符串）", 'n = input("名字？")'),
            ("f-string", "在字符串里嵌入变量", 'f"我叫 {n}"'),
            ("=", "赋值（不是相等）", "左边是名字，右边是数据"),
        ],
        "io": "你叫什么名字？ 小明\n你今年几岁？ 12\n...\n大家好，我叫 小明！\n今年 12 岁，来自 上海。",
        "steps": [
            "用 input 问姓名、年龄、城市、爱好、食物",
            "每个答案都赋给一个变量",
            "用 f-string 拼出 3～4 句自我介绍",
            "运行并自己当一次用户",
        ],
        "blanks": [
            "把输入存起来：________ = input(\"名字？\")",
            "f-string 要在引号前加字母 ________",
            "在 f-string 里写变量用 ________ 括起来",
            "变量名不能以 ________ 开头",
        ],
        "code": 'name = input("你叫什么名字？ ")\nprint(f"你好，{name}！")',
        "next": "第 3 课：数据类型 — input 拿到的其实全是文字",
        "next_short": "数据的身份证 — 四种类型",
        "sum_rows": [
            ("变量", "存数据", "name = ..."),
            ("input()", "读入文字", "x = input(...)"),
            ("f-string", "嵌入变量", 'f"我叫{name}"'),
        ],
        "ex": [
            ("加问题", "再问一个梦想并写进介绍"),
            ("改提示", "把提示语写得更俏皮"),
            ("嵌变量", 'print(f"{name} 来自 {city}")'),
            ("对照", "故意不赋值，看输入会丢"),
            ("挑战", "落款写成「来自{city}的{name}」"),
        ],
        "knowledge_slides": [
            ("变量是贴了标签的盒子", "左边名字，中间 = ，右边数据。不能以数字开头，不能用关键字。",
             'name = "小明"\nprint(name)'),
            ("input 必须用变量接住", "程序会暂停。括号里是提示语。不赋值的话，用户打的字会丢掉。",
             'name = input("你叫什么名字？ ")'),
            ("f-string", "字符串前面加 f，用 {变量} 占位。比加号拼接更干净。",
             'print(f"我叫 {name}，今年 {age} 岁")'),
        ],
    },
    {
        "n": 3,
        "title": "数据的身份证",
        "subtitle": "int / float / str / bool 与类型转换",
        "project": "个人信息卡",
        "icon": "🪪",
        "goals": [
            ("🔢", "四种类型", "str int float bool"),
            ("🔍", "type()", "查看一个值的类型"),
            ("🔄", "转换", "int() float() str()"),
            ("⭐", "项目", "信息卡 + 计算 BMI"),
        ],
        "know_rows": [
            ("str", '"12"', "文字"),
            ("int", "12", "整数"),
            ("float", "1.75", "小数"),
            ("bool", "True / False", "真或假"),
        ],
        "print_know": [
            ("str", "字符串 / 文字", '"小明"、"12"'),
            ("int", "整数", "12、-3"),
            ("float", "小数", "1.75、3.14"),
            ("bool", "布尔，只有两值", "True、False（首字母大写）"),
            ("int(x)", "把 x 转成整数", 'age = int(input("年龄："))'),
            ("type(x)", "查看类型", "type(18) → int"),
        ],
        "io": "姓名：小明\n年龄：13\n身高（米）：1.60\n体重（公斤）：50\n\n明年 14 岁\nBMI 约 19.5",
        "steps": [
            "姓名用 input 直接接（str）",
            "年龄用 int(...)，身高体重用 float(...)",
            "打印 type() 对照四种类型",
            "计算明年年龄 age+1 和 BMI",
        ],
        "blanks": [
            "input() 返回的类型永远是 ________",
            "把文字变成整数的函数是 ________",
            "True 和 False 属于 ________ 类型",
            '"12" + 1 会 ________（成功 / 报错）',
        ],
        "code": 'age = int(input("年龄："))\nprint(type(age))\nprint(age + 1)',
        "next": "第 4 课：运算符号 — 加减乘除、比较、逻辑",
        "next_short": "让 Python 算账 — 运算符号",
        "sum_rows": [
            ("str / int / float / bool", "四种类型", "文字 / 整数 / 小数 / 真假"),
            ("int() float()", "类型转换", "input 之后再转"),
            ("type()", "查看类型", "type(x)"),
        ],
        "ex": [
            ("改布尔", "把 is_student 改成 False"),
            ("看报错", "年龄输入「十三」"),
            ("对照 type", "打印三个变量的类型"),
            ("再转回去", "str(age) 拼进句子"),
            ("挑战", "再问鞋码并用 int 接收"),
        ],
        "knowledge_slides": [
            ("四种常用类型", "str 文字、int 整数、float 小数、bool 真假。True/False 首字母必须大写。",
             'print(type(18))\nprint(type(1.75))\nprint(type("18"))\nprint(type(True))'),
            ("input 永远是字符串", "看起来像数字，其实是文字。要计算必须先转换。",
             'age = int(input("年龄："))\nheight = float(input("身高："))'),
        ],
    },
    {
        "n": 4,
        "title": "让 Python 算账",
        "subtitle": "算术、比较、逻辑运算",
        "project": "小店收银员",
        "icon": "🛒",
        "goals": [
            ("➗", "算术", "+ - * / // % **"),
            ("⚖️", "比较", "== != > < >= <="),
            ("🔗", "逻辑", "and or not"),
            ("⭐", "项目", "打印小票并检查找零"),
        ],
        "know_rows": [
            ("+", "加", "3+2=5"),
            ("//", "整除", "5//2=2"),
            ("%", "取余", "5%2=1"),
            ("==", "等于", "比较，不是赋值"),
            ("and / or / not", "逻辑", "并且 / 或者 / 取反"),
        ],
        "print_know": [
            ("+ - * /", "加减乘除", "/ 的结果一定是小数"),
            ("//  %", "整除、取余", "47//10=4，47%10=7"),
            ("**", "乘方", "2**3=8"),
            ("== != > <", "比较，结果 True/False", "一个 = 是赋值"),
            ("and or not", "并且 / 或者 / 取反", "两边都要会"),
        ],
        "io": "单价 12.5  数量 3  折扣 0.8  实付 50\n原价 37.50\n应付 30.00\n找零 20.00\n钱够不够？ True",
        "steps": [
            "读入单价、数量、折扣、实付",
            "original = price * qty；total = original * discount",
            "change = paid - total；enough = paid >= total",
            "打印小票，并用 // % 拆找零",
        ],
        "blanks": [
            "比较「相等」要写 ________（几个等号？）",
            "5 // 2 的结果是 ________",
            "5 % 2 的结果是 ________",
            "True and False 的结果是 ________",
        ],
        "code": 'total = price * qty * discount\nchange = paid - total\nenough = paid >= total',
        "next": "第 5 课：if / else — 让程序走不同的路",
        "next_short": "程序会选择了 — if / else",
        "sum_rows": [
            ("+ - * / // % **", "算术", "先乘除后加减"),
            ("== > <", "比较", "得到 True/False"),
            ("and or not", "逻辑", "组合条件"),
        ],
        "ex": [
            ("不打折", "折扣填 1，应付应等于原价"),
            ("钱不够", "实付更少，enough 变 False"),
            ("口算", "17//5 和 17%5"),
            ("区分", "= 和 == 的区别"),
            ("挑战", "每消费 1 元积 1 分"),
        ],
        "knowledge_slides": [
            ("算术七剑客", "除了加减乘除，记住 // 整除、% 取余、** 乘方。",
             "print(5 / 2)   # 2.5\nprint(5 // 2)  # 2\nprint(5 % 2)   # 1\nprint(2 ** 3)  # 8"),
            ("比较得到 True/False", "两个等号才是「等于」。一个等号是装盒子。",
             "print(10 > 3)\nprint(10 == 3)\nenough = paid >= total"),
            ("逻辑运算", "and 两边都真；or 有一边真；not 取反。",
             "need = (not enough) or (change > 100)"),
        ],
    },
    {
        "n": 5,
        "title": "程序会选择了",
        "subtitle": "if / else 与缩进",
        "project": "电影票价查询",
        "icon": "🎬",
        "goals": [
            ("🔀", "if", "条件成立才执行"),
            ("↔️", "else", "否则走另一路"),
            ("⇥", "缩进", "4 个空格表示从属"),
            ("⭐", "项目", "按年龄和周末算票价"),
        ],
        "know_rows": [
            ("if 条件:", "成立则执行", "冒号不能丢"),
            ("else:", "否则", "二选一"),
            ("缩进", "4 空格", "属于谁看缩进"),
        ],
        "print_know": [
            ("if 条件:", "条件为 True 时执行下面缩进块", "冒号是英文 :"),
            ("else:", "条件为 False 时走这里", "和 if 配对"),
            ("缩进", "通常 4 个空格", "缩进错了会 IndentationError"),
            ("==", "比较是否相等", 'day == "y"'),
        ],
        "io": "年龄 15，周末 n  → 学生票 25 元\n年龄 20，周末 y  → 成人票 45 + 10 = 55，送爆米花",
        "steps": [
            "用 int(input) 读年龄",
            "if age < 18 学生票 25，else 成人票 45",
            "再问是否周末，y/Y 则加 10 元",
            "应付 ≥ 50 打印赠品提示",
        ],
        "blanks": [
            "if 这一行末尾必须写符号 ________",
            "条件不成立时走 ________ 分支",
            "Python 用 ________ 表示代码属于 if",
            '判断相等用 ________ 而不是 =',
        ],
        "code": 'if age < 18:\n    price = 25\nelse:\n    price = 45',
        "next": "第 6 课：elif — 三条及以上的路",
        "next_short": "多路选择 — if / elif / else",
        "sum_rows": [
            ("if", "条件成立", "if age < 18:"),
            ("else", "否则", "二选一"),
            ("缩进", "从属关系", "4 个空格"),
        ],
        "ex": [
            ("改分界", "18 改成 16"),
            ("改加价", "周末加 15 元"),
            ("看报错", "取消一行缩进再改回"),
            ("非法年龄", "age < 0 时提示"),
            ("挑战", "用 % 2 判断奇偶"),
        ],
        "knowledge_slides": [
            ("if / else 二选一", "条件写在 if 后面，记得冒号。两路只走一路。",
             "if age < 18:\n    print(\"学生票\")\nelse:\n    print(\"成人票\")"),
            ("缩进是语法", "少空格或多空格都会报 IndentationError。Tab 在 VS Code 里一般等于 4 空格。",
             "if age < 18:\n    print(\"对了\")"),
        ],
    },
    {
        "n": 6,
        "title": "多路选择",
        "subtitle": "if / elif / else",
        "project": "石头剪刀布",
        "icon": "✊",
        "goals": [
            ("3️⃣", "elif", "否则，如果"),
            ("📉", "顺序", "从上往下，命中即停"),
            ("🎲", "random", "电脑随机出拳"),
            ("⭐", "项目", "石头剪刀布对战"),
        ],
        "know_rows": [
            ("if", "第一关", "必须有"),
            ("elif", "中间关", "可以很多个"),
            ("else", "兜底", "可省略"),
            ("random.choice", "随机抽一个", 'choice(["石头","剪刀","布"])'),
        ],
        "print_know": [
            ("elif", "否则如果", "中间可以写很多个"),
            ("命中即停", "从上往下检查", "不要把宽条件写在最前"),
            ("import random", "请来随机工具", "写在文件开头"),
            ("choice(列表)", "随机抽一个元素", 'random.choice(["石头","剪刀","布"])'),
        ],
        "io": "你出了：石头\n电脑出：剪刀\n你赢了！石头砸剪刀 ✊",
        "steps": [
            "import random，电脑 random.choice 出拳",
            "玩家 input 出拳",
            "先判断输入是否合法，再判断平局",
            "再写三路「你赢了」，其余 else 你输",
        ],
        "blanks": [
            "第三种及以上的分支关键字是 ________",
            "if / elif 命中一个之后，后面 ________（还走 / 不走）",
            "从列表随机抽一个：random.________",
            "石头赢 ________",
        ],
        "code": 'if a == b:\n    print("平")\nelif a > b:\n    print("大")\nelse:\n    print("小")',
        "next": "第 7 课：for 循环 — 同一件事做很多遍",
        "next_short": "重复的力量 — for 循环",
        "sum_rows": [
            ("elif", "多路选择", "否则如果"),
            ("顺序", "宽条件在后", "命中即停"),
            ("random.choice", "随机", "电脑出拳"),
        ],
        "ex": [
            ("加理由", "赢的时候说明为什么"),
            ("拦截作弊", "特殊输入提示无效"),
            ("练等级", "用 elif 写 90/60 成绩档"),
            ("想一想", "平局放最后会怎样"),
            ("挑战", "连玩三局（可先手动运行三次）"),
        ],
        "knowledge_slides": [
            ("elif 是否则如果", "从上往下检查，命中一个就停止。宽条件不要写在最前面。",
             "if score >= 90:\n    print(\"优秀\")\nelif score >= 60:\n    print(\"及格\")\nelse:\n    print(\"不及格\")"),
            ("电脑随机出拳", "import random 请来工具箱。choice 从列表里抽一个。",
             'import random\ncomputer = random.choice(["石头", "剪刀", "布"])'),
        ],
    },
    {
        "n": 7,
        "title": "重复的力量",
        "subtitle": "for 与 range()",
        "project": "图案打印机",
        "icon": "🖨️",
        "goals": [
            ("🔁", "for", "按序列重复"),
            ("📏", "range", "含头不含尾"),
            ("🔲", "嵌套", "外层行、内层列"),
            ("⭐", "项目", "矩形 / 三角形 / 乘法表"),
        ],
        "know_rows": [
            ("for i in range(n):", "重复 n 次", "i 从 0 到 n-1"),
            ("range(1, 6)", "1..5", "含头不含尾"),
            ("end='  '", "print 不换行", "乘法表用"),
        ],
        "print_know": [
            ("for i in range(n)", "i = 0,1,...,n-1", "重复 n 次"),
            ("range(a, b)", "从 a 到 b-1", "含头不含尾"),
            ("range(a, b, s)", "步长 s", "range(1,10,2) → 1 3 5 7 9"),
            ('end="  "', "print 结束符改成空格", "默认是换行"),
        ],
        "io": "选择 2，高度 4：\n▲\n▲▲\n▲▲▲\n▲▲▲▲",
        "steps": [
            "菜单：1 矩形  2 三角形  3 乘法表",
            "矩形：外层行，print(\"★\" * cols)",
            "三角形：for i in range(1, n+1): print(\"▲\" * i)",
            "乘法表：嵌套 for + end='  '",
        ],
        "blanks": [
            "range(5) 产生的最后一个数是 ________",
            "range(1, 6) 一共有 ________ 个数",
            "让 print 不换行，要设置 ________ 参数",
            "嵌套循环：外层管________，内层管________",
        ],
        "code": "for i in range(1, 5):\n    print(\"▲\" * i)",
        "next": "第 8 课：while — 次数事先不知道就用它",
        "next_short": "不到目的不罢休 — while",
        "sum_rows": [
            ("for", "遍历序列", "for i in range(5):"),
            ("range", "含头不含尾", "range(1,6)→1..5"),
            ("嵌套", "行×列", "乘法表"),
        ],
        "ex": [
            ("猜 range", "range(2,11,2) 有哪些数"),
            ("求和", "for 算 1 到 10 的和"),
            ("倒三角", "第一行 5 个最后 1 个"),
            ("空心矩形", "只打边框"),
            ("挑战", "等腰三角形（前面加空格）"),
        ],
        "knowledge_slides": [
            ("for + range", "含头不含尾。range(5) 是 0 到 4。想从 1 到 5 就写 range(1, 6)。",
             "for i in range(5):\n    print(i)"),
            ("用循环画图", "字符串乘法配 for，一行一行打。",
             "for i in range(1, 6):\n    print(\"▲\" * i)"),
        ],
    },
    {
        "n": 8,
        "title": "不到目的不罢休",
        "subtitle": "while、break、continue",
        "project": "猜数字游戏",
        "icon": "🔢",
        "goals": [
            ("♾️", "while", "条件成立就继续"),
            ("🛑", "break", "立刻结束循环"),
            ("⏭️", "continue", "跳过本圈后半段"),
            ("⭐", "项目", "1～100 猜数字，7 次机会"),
        ],
        "know_rows": [
            ("while 条件:", "事先不知次数", "记得更新变量"),
            ("break", "下车", "立刻结束"),
            ("continue", "下一圈", "跳过后面"),
            ("randint(1,100)", "随机整数", "含两端"),
        ],
        "print_know": [
            ("while 条件:", "条件为 True 就重复", "记得更新，否则死循环"),
            ("break", "立刻结束整个循环", "猜对就 break"),
            ("continue", "结束本圈，进入下一圈", "非法输入不扣次数"),
            ("randint(a,b)", "随机整数，含 a 和 b", "random.randint(1, 100)"),
        ],
        "io": "第 1 次，请猜：50\n太小了 ⬆\n第 2 次，请猜：75\n太大了 ⬇\n...\n猜对了！",
        "steps": [
            "secret = random.randint(1, 100)",
            "while tries < 7：读入猜测",
            "非数字 continue；猜对 break",
            "提示太大/太小；用完次数公布答案",
        ],
        "blanks": [
            "次数事先不知道，用 ________ 循环",
            "猜对立刻结束循环的关键字是 ________",
            "跳过本圈剩余语句的关键字是 ________",
            "randint(1, 100) 包不包含 100？________",
        ],
        "code": "while tries < 7:\n    guess = int(input(\"猜：\"))\n    if guess == secret:\n        break",
        "next": "第 9 课：列表 — 一个变量装很多东西",
        "next_short": "装东西的盒子 — 列表",
        "sum_rows": [
            ("while", "条件循环", "while tries < 7:"),
            ("break", "立刻结束", "猜对下车"),
            ("continue", "跳过本圈", "非法输入"),
        ],
        "ex": [
            ("改范围", "1～50，5 次机会"),
            ("评语", "按次数给不同评语"),
            ("拒绝负数", "continue"),
            ("一击必杀", "max_tries = 1"),
            ("挑战", "结束后问是否再来一局"),
        ],
        "knowledge_slides": [
            ("for 还是 while", "次数已知用 for；「猜对才停」用 while。三件套：初始、条件、更新。",
             "n = 1\nwhile n <= 5:\n    print(n)\n    n = n + 1"),
            ("break 与 continue", "break 下车；continue 跳过本圈后半段。while True 靠 break 出来。",
             "if guess == secret:\n    break\nif not raw.isdigit():\n    continue"),
        ],
    },
    {
        "n": 9,
        "title": "装东西的盒子",
        "subtitle": "列表增删改查",
        "project": "购物清单小管家",
        "icon": "🛍️",
        "goals": [
            ("📦", "列表", "方括号装一串东西"),
            ("📌", "索引", "从 0 开始"),
            ("➕", "append / remove", "增和删"),
            ("⭐", "项目", "命令式购物清单"),
        ],
        "know_rows": [
            ("[]", "创建列表", 'cart = []'),
            ("cart[0]", "第一个元素", "索引从 0 开始"),
            ("append", "末尾追加", "cart.append(x)"),
            ("remove", "按值删除", "先 in 再删"),
            ("len / in", "长度 / 是否包含", "len(cart)"),
        ],
        "print_know": [
            ("[]", "列表字面量", '["苹果","牛奶"] 或 []'),
            ("索引", "从 0 开始", "cart[0] 是第一件"),
            ("append(x)", "末尾追加", "cart.append(\"鸡蛋\")"),
            ("remove(x)", "删除第一次出现的 x", "不存在会报错"),
            ("in / len", "是否包含 / 长度", '"苹果" in cart'),
        ],
        "io": "请输入命令：add\n要添加的商品：苹果\n已添加：苹果。现在有 1 件。\n请输入命令：show\n  1. 苹果",
        "steps": [
            "cart = []，while True 读命令",
            "add → append；del → 先 in 再 remove",
            "show → for i in range(len(cart)) 带序号打印",
            "quit → 打印最终清单并 break",
        ],
        "blanks": [
            "空列表写作 ________",
            "列表第一个元素的下标是 ________",
            "末尾添加元素用 ________ 方法",
            "判断「苹果在不在清单」：________ in cart",
        ],
        "code": 'cart = []\ncart.append("苹果")\nprint(cart[0])\nprint(len(cart))',
        "next": "第 10 课：综合项目 — 班级成绩统计台",
        "next_short": "语法大综合 — 成绩统计台",
        "sum_rows": [
            ("列表", "一串数据", "cart = []"),
            ("append/remove", "增删", "末尾加 / 按值删"),
            ("索引", "从 0 起", "cart[i]"),
        ],
        "ex": [
            ("去重", "已有则不再添加"),
            ("空清单", "show 时给提示"),
            ("清空", "增加 clear 命令"),
            ("保护", "空列表时不要取 cart[0]"),
            ("挑战", "统计某商品出现次数"),
        ],
        "knowledge_slides": [
            ("列表与索引", "方括号、逗号分隔。第一个是 [0]，不是 [1]。",
             'cart = ["苹果", "牛奶", "面包"]\nprint(cart[0])\nprint(len(cart))'),
            ("增删查", "append 追加；remove 按值删；in 先检查再删。",
             'cart.append("鸡蛋")\nif "牛奶" in cart:\n    cart.remove("牛奶")'),
        ],
    },
    {
        "n": 10,
        "title": "语法大综合",
        "subtitle": "列表 + 循环 + 判断",
        "project": "班级成绩统计台",
        "icon": "📊",
        "goals": [
            ("📥", "录入", "while 读到 -1"),
            ("🧮", "累加 / 擂台 / 计数", "自己写统计"),
            ("📋", "报告", "逐人 + 全班"),
            ("🎉", "结业", "10 节语法一次用上"),
        ],
        "know_rows": [
            ("累加器", "total = total + s", "先准备 0"),
            ("擂台", "if s > highest", "先假设第一个是冠军"),
            ("计数", "passed += 1", "满足条件 +1"),
        ],
        "print_know": [
            ("累加器", "total = 0 再一圈圈加", "求平均：total / len"),
            ("擂台法", "highest = scores[0]", "更大就替换"),
            ("计数", "passed = passed + 1", "及格人数"),
            ("过滤", "新列表只装及格成绩", "for + if + append"),
        ],
        "io": "输入 88, 57, 91, 73, 60, -1\n人数 5  总分 369  平均 73.8\n最高 91  最低 57\n及格 4 人（80%）  优秀 1 人",
        "steps": [
            "while True 录入，-1 break，非法 continue",
            "scores.append(score)",
            "遍历：累加、更新最高最低、计及格优秀",
            "打印逐人报告和全班统计",
        ],
        "blanks": [
            "求平均：total / ________",
            "找最大：先令 highest = ________",
            "及格通常指分数 ≥ ________",
            "本课没有新的大语法，重点是 ________（拼装 / 背函数）",
        ],
        "code": "total = 0\nfor s in scores:\n    total = total + s\navg = total / len(scores)",
        "next": "结业！下一站可去图形化、趣味学习或 Pygame。",
        "next_short": "课程结束 — 去选下一门吧",
        "sum_rows": [
            ("input/类型/运算", "采集与计算", "前 4 课"),
            ("if / for / while", "决策与重复", "第 5～8 课"),
            ("列表", "存放一组成绩", "第 9～10 课"),
        ],
        "ex": [
            ("满分人数", "统计 100 分"),
            ("两位小数", "{avg:.2f}"),
            ("鼓励", "全班不及格时打印一句"),
            ("是第几位", "最高分的序号"),
            ("挑战", "列出低于平均分的成绩"),
        ],
        "knowledge_slides": [
            ("三种统计套路", "累加器、擂台、计数。自己写一遍，比直接调用 sum/max 更懂。",
             "total = 0\nhighest = scores[0]\npassed = 0\nfor s in scores:\n    total = total + s"),
            ("主线：录入 → 存放 → 遍历 → 报告", "10 节语法全部出现在这一条流水线上。",
             "scores = []\n# 录入到 -1\n# for 遍历统计\n# print 报告"),
        ],
    },
]

# 90 分钟加厚：热身 / 加码 / 改错 / 额外知识点（合并进上面的课）
ENRICH = {
    1: {
        "warmup": ("热身：print 的六种玩法", "多参数、sep、数字算式、字符串乘法、\\n/\\t、end 不换行。跟打 10 分钟。",
                   'print("我", "爱", "编程", sep="-")\nprint("100+23=", 100 + 23)\nprint("哈" * 8)\nprint("A", end="")\nprint("B")'),
        "challenge": ("加码：ASCII 小房子 + 课程表", "用 print 画房子；再用 \\t 打一周课程表。改成自己的课表。",
                      "    /\\\n   /  \\\n  /____\\\n  |    |\n  | [] |"),
        "mistakes": [
            ('print(你好)', 'print("你好")', "文字必须加引号，否则被当成变量"),
            ("print('你好\")", 'print("你好")', "左右引号要配对"),
            ("Print('hi')", "print('hi')", "函数名全小写，Python 区分大小写"),
        ],
        "more_slides": [
            ("sep、end、换行符", "sep 改分隔符；end 改结尾（默认换行）；\\n 换行、\\t 制表。",
             'print("A", "B", sep="-")\nprint("同行", end="")\nprint("还在这")\nprint("上一行\\n下一行")'),
            ("print 还能算数", "引号里的是文字；没引号的数字会先算再显示。",
             'print("2+3")    # 文字：2+3\nprint(2 + 3)    # 算式：5\nprint(2 ** 10)  # 1024'),
        ],
        "more_blanks": [
            'print("A", "B", sep="-") 输出 ________',
            "让 print 不换行，要写 ________",
            "\\n 的意思是 ________",
        ],
        "more_ex": [
            ("画房子", "加码里的 ASCII 小房子，改成两扇窗"),
            ("课程表", "把加码课程表改成你班真实的三天课表"),
        ],
    },
    2: {
        "warmup": ("热身：变量三连", "赋值、重新赋值、字符串用 + 拼接。体会盒子里的东西能被换掉。",
                   'animal = "小猫"\nprint(animal)\nanimal = "小狗"\nprint(animal)\nprint("小明" + "喜欢" + "篮球")'),
        "challenge": ("加码：故事填空机", "收集名字、地点、物品、形容词、动词，生成一段小故事。",
                      "从前，小明 来到了 森林。\n地上突然冒出 神奇的石头。"),
        "mistakes": [
            ("1name = 'a'", "name1 = 'a'", "变量名不能以数字开头"),
            ("my name = 'a'", "my_name = 'a'", "不能有空格，用下划线"),
            ('print("我叫 {name}")', 'print(f"我叫 {name}")', "f-string 必须在引号前加 f"),
        ],
        "more_slides": [
            ("变量起名规则", "字母数字下划线；不能数字开头；区分大小写；不用关键字。",
             "ok = 1\nmy_name = '小明'\n# 1n = 1     错\n# my name = 1  错"),
            ("input 必须接住", "不赋值，用户打的字会丢掉。input 得到的永远是字符串。",
             'name = input("名字？ ")\nprint(type(name))  # 下节课细讲'),
        ],
        "more_blanks": [
            "name = 'A' 然后 name = 'B'，现在 name 是 ________",
            '"小明" + "12" 的结果是 ________',
            "不写 f，{name} 会原样打印还是换成变量？________",
        ],
        "more_ex": [
            ("故事机", "加码故事再加一个「反派名字」字段"),
            ("名片落款", "最后一行改成「——来自{city}的{name}」"),
        ],
    },
    3: {
        "warmup": ("热身：类型侦探", "对照 18 / 1.75 / '18' / True 的 type。演示 '12'+1 会报错。",
                   "print(type(18))\nprint(type('18'))\nprint(int('12') + 1)"),
        "challenge": ("加码：单位换算器", "厘米→米、斤→公斤、秒→分秒（// 和 % 预告下节课）。",
                      "160 厘米 = 1.6 米\n100 斤 = 50.0 公斤\n375 秒 = 6 分 15 秒"),
        "mistakes": [
            ('age = input("年龄：")\nprint(age + 1)', "age = int(input(...))", "input 是字符串，要先 int()"),
            ("int('3.5')", "float('3.5') 或 int(float('3.5'))", "带小数点的文字不能直接 int"),
            ("true", "True", "布尔值首字母必须大写"),
        ],
        "more_slides": [
            ("为什么必须转换", "'12' 和 12 对 Python 完全不是一回事。要算数，先换身份证。",
             "a = '12'\n# print(a + 1)   报错\nprint(int(a) + 1)  # 13"),
            ("小数怎么留一位", "{bmi:.1f} 表示保留 1 位小数。:.2f 就是 2 位。",
             'bmi = 19.531\nprint(f"{bmi:.1f}")  # 19.5'),
        ],
        "more_blanks": [
            "float('1.6') 的类型是 ________",
            "str(18) 的结果是 ________（带不带引号？）",
            "BMI 公式：体重 ÷ ________ ÷ ________",
        ],
        "more_ex": [
            ("出生年", "用「今年 - 年龄」估算出生年"),
            ("换算", "把加码再加一项：小时 → 分钟"),
        ],
    },
    4: {
        "warmup": ("热身：口算对对碰", "先心算再看程序。覆盖 + - * / // % ** 和优先级。",
                   "print(17 // 2)  # 8\nprint(17 % 2)   # 1\nprint(3 + 2 * 4)  # 11"),
        "challenge": ("加码：秒→时分秒 + 圆的面积", "3723 秒 = 1 小时 2 分 3 秒；面积 = πr²。",
                      "hours = total // 3600\nremain = total % 3600\nmian = 3.14159 * r ** 2"),
        "mistakes": [
            ("x = 5\nx = x + 1 写成 x + 1", "x += 1 或 x = x + 1", "算完必须存回去"),
            ("if 10 = 10", "10 == 10", "一个等号是赋值，比较用两个"),
            ("5 / 2 以为是 2", "5 / 2 是 2.5；整除才是 5 // 2", "/ 永远得到小数"),
        ],
        "more_slides": [
            ("// 和 % 是一对", "47 // 10 = 4 张十元，47 % 10 = 7 元零头。换算时间同理。",
             "sec = 3723\nprint(sec // 3600)      # 小时\nprint(sec % 3600 // 60) # 分钟"),
            ("比较 + 逻辑", "比较得到 True/False；and 两边都真，or 有一边真，not 取反。",
             "enough = paid >= total\nneed = (not enough) or (change > 100)"),
        ],
        "more_blanks": [
            "2 ** 3 等于 ________",
            "3 + 2 * 4 等于 ________",
            "True or False 等于 ________",
            "score += 5 等价于 ________",
        ],
        "more_ex": [
            ("积分", "消费 1 元积 1 分（已经在主项目里，改成满 10 元积 1 分）"),
            ("圆", "再算一个球的体积 4/3 πr³（选做）"),
        ],
    },
    5: {
        "warmup": ("热身：及格 / 奇偶 / 正负", "三个独立小判断，练熟冒号和缩进。正负用嵌套 if。",
                   "if n % 2 == 0:\n    print('偶数')\nelse:\n    print('奇数')"),
        "challenge": ("加码：登录门卫 + 穿衣顾问", "两层 if 做用户名/密码；温度 + 下雨两个独立 if。",
                      "if user == 'xiaoming':\n    pwd = input('密码：')\n    if pwd == '1234':\n        print('欢迎')"),
        "mistakes": [
            ("if age < 18", "if age < 18:", "漏了冒号"),
            ("if age < 18:\nprint('未成年')", "第二行缩进 4 格", "缩进是语法，不是好看"),
            ("if day = 'y'", "if day == 'y'", "判断相等必须 =="),
        ],
        "more_slides": [
            ("缩进决定「属于谁」", "属于 if 的句子必须缩进。通常 4 个空格。少一格都会报错。",
             "if age < 18:\n    print('学生票')\n    price = 25\nelse:\n    print('成人票')"),
            ("嵌套 if：判断里面再判断", "会员打折：先问是不是会员，再问满不满 30。注意再缩进一层。",
             "if vip == 'y':\n    if price >= 30:\n        price = price * 0.9"),
        ],
        "more_blanks": [
            "偶数的判断条件是 n % 2 ________ 0",
            "if 和 else 两路会走几路？________",
            "嵌套 if 时，内层要多缩进 ________ 格",
        ],
        "more_ex": [
            ("非法年龄", "age < 0 时提示不合法"),
            ("密码", "把加码登录的密码改成你自己的"),
        ],
    },
    6: {
        "warmup": ("热身：成绩等级", "90 优秀 / 80 良好 / 60 及格。强调「高分档写前面」。",
                   "if score >= 90:\n    print('优秀')\nelif score >= 60:\n    print('及格')\nelse:\n    print('不及格')"),
        "challenge": ("加码：菜单点餐 + BMI 分档", "1-4 号点餐；BMI 四档 elif。把第 3 课的 BMI 用起来。",
                      "if bmi < 18.5: 偏瘦\nelif bmi < 24: 正常\nelif bmi < 28: 偏胖\nelse: 肥胖"),
        "mistakes": [
            ("先写 >=60 再写 >=90", "高分档必须在前", "95 会被判成及格"),
            ("elif 单独出现", "elif 必须跟在 if 后面", "没有 if 不能直接 elif"),
            ("三个独立 if 当多路", "用 if/elif/else", "独立 if 可能走好几路"),
        ],
        "more_slides": [
            ("顺序比你想的更重要", "从上往下，命中一个就停。宽条件（>=60）一定写在窄条件（>=90）后面。",
             "# 错误示范：95 会变成及格\nif score >= 60:\n    print('及格')\nelif score >= 90:\n    print('优秀')"),
            ("random.choice", "从列表里随机抽一个。import 写在文件开头。",
             'import random\nprint(random.choice(["石头", "剪刀", "布"]))'),
        ],
        "more_blanks": [
            "第三种及以上分支的关键字是 ________",
            "石头赢 ________",
            "BMI 正常大约在 18.5 到 ________",
        ],
        "more_ex": [
            ("连玩", "主项目重新运行三局，记录赢/平/输"),
            ("菜单", "给套餐再加一个儿童套餐 5 号"),
        ],
    },
    7: {
        "warmup": ("热身：range + 求和 + 拆名字", "三种 range；1 加到 n；for ch in name 遍历字符串。",
                   "s = 0\nfor i in range(1, n + 1):\n    s = s + i"),
        "challenge": ("加码：等腰三角 + 阶乘", "前面补空格打等腰三角；用累乘算 m!。",
                      "for i in range(1, h+1):\n    print(' ' * (h-i) + '▲' * (2*i-1))"),
        "mistakes": [
            ("range(5) 以为有 5", "0 1 2 3 4，不含 5", "含头不含尾"),
            ("for i in range(1, 5) 想打 5 行", "range(1, 6)", "右端要 +1"),
            ("内层循环忘了 print() 换行", "内层 end=''，外层 print()", "乘法表每一行结束要换行"),
        ],
        "more_slides": [
            ("嵌套：外层行、内层列", "空心矩形、乘法表都是两层 for。先写外层，再往里面加。",
             "for i in range(rows):\n    for j in range(cols):\n        print('★', end='')\n    print()"),
            ("倒着数：步长 -1", "range(n, 0, -1) 从 n 降到 1，用来打倒三角。",
             "for i in range(5, 0, -1):\n    print('▼' * i)"),
        ],
        "more_blanks": [
            "range(1, 6) 最后一个数是 ________",
            "range(n, 0, -1) 的步长是 ________",
            "1 加到 10 的和是 ________",
        ],
        "more_ex": [
            ("空心", "把空心矩形的角改成 ○"),
            ("阶乘", "打印 1! 到 8! 一张表"),
        ],
    },
    8: {
        "warmup": ("热身：倒计时 + 口令 go", "while n>0 倒数；while word!='go' 直到输入正确。",
                   "n = 5\nwhile n > 0:\n    print(n)\n    n = n - 1"),
        "challenge": ("加码：密码 3 次 + 累加到 0", "密码错误再试；输入数字累加，0 结束求平均。",
                      "while True:\n    x = float(input())\n    if x == 0:\n        break\n    total += x"),
        "mistakes": [
            ("while 里忘了更新", "n = n - 1", "会变成死循环"),
            ("break 和 continue 搞反", "break 下车；continue 跳过本圈后半段", "非法输入用 continue"),
            ("while True 没有 break", "必须有离开的路", "否则程序停不下来"),
        ],
        "more_slides": [
            ("for 还是 while", "次数已知 → for；「猜对才停 / 输入 0 才停」→ while。",
             "while tries < 7:\n    ...\n    if guess == secret:\n        break"),
            ("再来一局：外层再套 while", "内层一局游戏，外层问 y/n。两层循环不要怕。",
             "again = 'y'\nwhile again == 'y':\n    # 玩一局\n    again = input('再来？')"),
        ],
        "more_blanks": [
            "立刻结束循环用 ________",
            "跳过本圈后半段用 ________",
            "randint(1,100) 包不包含 100？________",
        ],
        "more_ex": [
            ("评语", "按次数给天选/厉害/过关（主项目已有，改文案）"),
            ("累加", "拒绝负数：输入 <0 时 continue"),
        ],
    },
    9: {
        "warmup": ("热身：预置名单", "创建、取下标、append、修改、remove、带序号遍历。先不写菜单。",
                   'names = ["小明", "小红"]\nnames.append("小刚")\nnames[0] = "小明同学"'),
        "challenge": ("加码：随机点名器", "n 点一名，不重复，点完重置。体会 in + 列表。",
                      "lucky = random.choice(class_list)\nwhile lucky in picked:\n    lucky = random.choice(class_list)"),
        "mistakes": [
            ("cart[1] 当第一件", "cart[0] 才是第一件", "索引从 0 开始"),
            ("remove 不存在的东西", "先 if x in cart", "否则报 ValueError"),
            ("空列表还取 cart[0]", "先判断 len(cart)==0", "IndexError"),
        ],
        "more_slides": [
            ("按位置改、按位置删", "cart[i] = 新值；cart.pop(i) 删第 i 个（从 0 计）。用户看到的序号要 +1 / -1。",
             "k = int(input('第几件：'))\ncart[k - 1] = '新名字'"),
            ("两种遍历", "要序号用 range(len)；只要元素用 for x in cart。",
             "for i in range(len(cart)):\n    print(i + 1, cart[i])"),
        ],
        "more_blanks": [
            "修改第 3 件应写 cart[________] = ...",
            "cart.pop(0) 删的是第 ________ 件（对人来说）",
            "「已经有了就不加」用 ________ 判断",
        ],
        "more_ex": [
            ("clear", "增加命令把清单清空：cart = []"),
            ("点名", "把加码名单改成你们小组的名字"),
        ],
    },
    10: {
        "warmup": ("热身：固定成绩走一遍套路", "先对 [88,57,91,73,60] 手算，再让程序算，对上平均 73.8。",
                   "demo = [88, 57, 91, 73, 60]\ntotal = 0\nfor s in demo:\n    total = total + s"),
        "challenge": ("加码：条形图 + 低于平均分", "每 5 分一颗星；列出低于平均分的座位号。",
                      "bars = int(s // 5)\nprint('★' * bars, s)"),
        "mistakes": [
            ("avg = total / scores", "avg = total / len(scores)", "除以人数不是除以列表"),
            ("最高分初始写成 0", "highest = scores[0]", "否则全是负数时会错；空列表要先判断"),
            ("优秀忘了算进及格", ">=90 时 passed 也 +1", "优秀是及格的子集"),
        ],
        "more_slides": [
            ("录入到 -1 结束", "哨兵值：约定 -1 表示结束，不当作成绩。非法分数 continue。",
             "if score == -1:\n    break\nif score < 0 or score > 100:\n    continue"),
            ("结业清单", "输入输出、类型、运算、判断、循环、列表。下门课可以去做窗口或游戏。",
             "# 你已经能写：\n# 交互程序 / 计算器 / 小游戏 / 管理清单 / 统计报告"),
        ],
        "more_blanks": [
            "哨兵值 -1 的作用是 ________",
            "每 5 分一颗星：星星数量 = 分数 ________ 5",
            "低于平均分：if scores[i] ________ avg",
        ],
        "more_ex": [
            ("满分", "统计 100 分人数"),
            ("条形图", "把 ★ 改成 █，满 100 分 20 格"),
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
    <p class="kicker anim-fade-down" data-anim="fade-down" style="color:var(--accent-2)">Python 基本语法速通 · 第 {n} 课</p>
    <h1 class="h1 anim-rise-in" data-anim="rise-in" style="font-size:72px;margin-top:12px">{lesson["icon"]} <span class="grad">{html.escape(title)}</span></h1>
    <p class="lede anim-fade-up" data-anim="fade-up" style="margin-top:16px;font-size:22px">{html.escape(lesson["subtitle"])}</p>
    <div class="row wrap anim-fade-up" data-anim="fade-up" style="margin-top:32px;gap:12px;justify-content:center">
      <span class="pill" style="background:rgba(189,147,249,.15);color:var(--accent);border:1px solid rgba(189,147,249,.3)">90 分钟</span>
      <span class="pill" style="background:rgba(139,233,253,.15);color:var(--accent-3);border:1px solid rgba(139,233,253,.3)">热身 + 主项目 + 加码</span>
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
      <div class="course">PYTHON 基本语法速通 · 学案</div>
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
    <div class="brand">Python 基本语法速通 · 配套代码</div>
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
<title>打印学案 · Python 基本语法速通</title>
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
  <div class="course">PYTHON 基本语法速通</div>
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
<title>Python 基本语法速通 · 全部学案（10 课）</title>
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
    print("done")


if __name__ == "__main__":
    main()
