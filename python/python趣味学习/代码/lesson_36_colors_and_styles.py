# ============================================================
# 课程 36：让画面更漂亮 —— 颜色与样式
# 学习目标：
#   1. 学会用 color() 设置画笔颜色
#   2. 学会用 pensize() 设置画笔粗细
#   3. 学会用 speed() 调整绘图速度
#   4. 学会用 begin_fill() 和 end_fill() 给图形填充颜色
#   5. 综合运用这些功能画出彩色五角星
# ============================================================

import turtle

screen = turtle.Screen()
screen.title("第36课：让画面更漂亮 —— 颜色与样式")
screen.bgcolor("white")

t = turtle.Turtle()
t.shape("turtle")

# =====================================================
# 第一部分：认识颜色 color()
# =====================================================

# color() 可以设置画笔颜色
# 颜色的写法有几种：
#   1. 英文名称："red", "blue", "green", "yellow", "purple"
#   2. 十六进制颜色码："#FF0000"（红色）, "#00FF00"（绿色）

t.penup()
t.goto(-280, 200)
t.pendown()

# 演示不同颜色画线
color_list = ["red", "blue", "green", "orange", "purple", "pink", "brown", "cyan"]

for c in color_list:
    t.color(c)
    t.pensize(5)
    t.forward(60)
    # 在每条线下面写颜色名
    t.write(c, font=("Arial", 8, "normal"))

# 看看！这么多颜色可以用，还可以自己尝试更多：
# "gold"（金色）, "silver"（银色）, "navy"（深蓝）, "lime"（亮绿）


# =====================================================
# 第二部分：画笔粗细 pensize()
# =====================================================

# 清除画布，演示不同粗细
t.clear()
t.penup()
t.goto(-280, 180)
t.pendown()
t.color("black")

# pensize(数字)：数字越大，画笔越粗
width_list = [1, 3, 5, 8, 12, 18]

for w in width_list:
    t.pensize(w)
    t.forward(60)
    # 标注粗细
    t.write(f"粗细={w}", font=("Arial", 8, "normal"))


# =====================================================
# 第三部分：绘图速度 speed()
# =====================================================

t.clear()
t.penup()
t.goto(-280, 100)
t.pendown()

# 演示不同的速度
# speed(1)  = 最慢（可以看到海龟慢慢爬）
# speed(5)  = 正常速度
# speed(10) = 最快
# speed(0)  = 瞬间完成（最快中的最快）

# 这里我们用 speed(5)，方便我们看到绘画过程
t.speed(5)


# =====================================================
# 第四部分：图形填充 begin_fill() 和 end_fill()
# =====================================================

# begin_fill()：告诉海龟"开始填充"
# end_fill()：告诉海龟"填充结束"
# 海龟会把 begin_fill() 之后、end_fill() 之前画的所有图形填满颜色

t.clear()
t.speed(6)

# --- 4.1 填充一个正方形 ---
t.color("blue")       # 边框颜色
t.penup()
t.goto(-250, 120)
t.pendown()

t.begin_fill()        # ← 开始填充
for i in range(4):
    t.forward(80)
    t.right(90)
t.end_fill()          # ← 结束填充（正方形变成蓝色实心方块）

# 标注
t.penup()
t.goto(-250, 90)
t.pendown()
t.write("填充的正方形", font=("Arial", 10, "normal"))


# --- 4.2 填充一个三角形 ---
t.color("green")
t.penup()
t.goto(-110, 130)
t.pendown()

t.begin_fill()
for i in range(3):
    t.forward(90)
    t.right(120)
t.end_fill()

t.penup()
t.goto(-110, 90)
t.pendown()
t.write("填充的三角形", font=("Arial", 10, "normal"))


# --- 4.3 填充一个圆 ---
t.color("red")
t.penup()
t.goto(60, 160)
t.pendown()

t.begin_fill()
t.circle(50)
t.end_fill()

t.penup()
t.goto(50, 90)
t.pendown()
t.write("填充的圆", font=("Arial", 10, "normal"))

# 注意：填充颜色和边框颜色可以不一样！
# 用 color("边框色", "填充色") 来分别设置
# 例如：t.color("black", "yellow") → 黑边框，黄填充


# =====================================================
# 第五部分：画彩色五角星并填充
# =====================================================

t.clear()
t.speed(5)

# 移动到画布中央下方
t.penup()
t.goto(0, -100)
t.pendown()

# 设置颜色：金色边框 + 黄色填充
t.color("gold", "yellow")
t.pensize(4)

# 画五角星：5 条边，每次转 144 度
t.begin_fill()
for i in range(5):
    t.forward(150)  # 五角星的边长
    t.right(144)    # 五角星的转角
t.end_fill()

# 在五角星下方写标题
t.penup()
t.goto(0, -180)
t.pendown()
t.color("black")
t.write("★ 金色五角星 ★", align="center", font=("Arial", 16, "bold"))


# =====================================================
# 第六部分：彩虹色条（综合演示）
# =====================================================

t.penup()
t.goto(-200, 200)
t.pendown()

rainbow_colors = ["red", "orange", "yellow", "green", "blue", "purple"]
t.pensize(20)

# 用彩虹色画一排粗线
for color_name in rainbow_colors:
    t.color(color_name)
    t.pendown()
    t.forward(60)
    t.penup()
    t.forward(10)  # 颜色之间的空隙

t.hideturtle()
turtle.done()


# ============================================================
# 练习题 1：画彩色正方形并填充
#
# 要求：
# - 画一个正方形，边长 120
# - 边框颜色用 "blue"，填充颜色用 "lightblue"
# - 提示：用 color("blue", "lightblue") 分别设置边框和填充色
# - 用 begin_fill() 和 end_fill() 填充
#
# import turtle
# t = turtle.Turtle()
# t.speed(5)
#
# t.color("blue", "lightblue")  # 边框蓝色，填充淡蓝
# t.pensize(3)
# t.begin_fill()
# for i in range(4):
#     t.forward(120)
#     t.right(90)
# t.end_fill()
#
# turtle.done()
# ============================================================


# ============================================================
# 练习题 2：画彩色三角形并填充
#
# 要求：
# - 画一个等边三角形，边长 100
# - 用你喜欢的两种颜色（边框和填充）
# - 填充三角形
#
# import turtle
# t = turtle.Turtle()
# t.speed(5)
#
# # 【你的代码】画一个填充的三角形
#
# turtle.done()
# ============================================================


# ============================================================
# 练习题 3：设置不同画笔粗细画线条
#
# 要求：
# - 画 5 条水平线，粗细分别为 1, 3, 6, 10, 15
# - 每条线用不同的颜色
# - 线之间间隔 30 像素
#
# import turtle
# t = turtle.Turtle()
# t.speed(5)
#
# colors = ["red", "blue", "green", "orange", "purple"]
# widths = [1, 3, 6, 10, 15]
#
# # 【你的代码】用循环画 5 条不同粗细的彩色线
#
# turtle.done()
# ============================================================


# ============================================================
# 综合小挑战：画"彩虹房子"
#
# 挑战内容：
# 用学到的颜色、填充、画笔粗细知识，画一栋"彩虹房子"。
#
# 要求：
#   1. 房子主体：一个填充的大正方形（颜色自选，比如淡黄色）
#   2. 房顶：一个填充的三角形（红色或橙色）
#   3. 窗户：两个填充的小正方形（蓝色），左右各一个
#   4. 门：一个填充的长方形（棕色），在房子中间下方
#   5. 烟囱：一个填充的长方形（灰色），从房顶伸出来
#   6. 天空：画一条粗粗的蓝色弧线表示天空（可选）
#   7. 草地：画一条粗粗的绿色线表示草地（可选）
#
# 提示：
#   - 多用 penup()/pendown() 移动到不同位置
#   - 每个部分用不同的 color(边框色, 填充色)
#   - 合理安排大小比例
#
# import turtle
# t = turtle.Turtle()
# t.speed(5)
#
# # 【你的代码】画一栋漂亮的彩虹房子
#
# turtle.done()
#
# 发挥你的想象力，画出你梦想中的房子！
# ============================================================
