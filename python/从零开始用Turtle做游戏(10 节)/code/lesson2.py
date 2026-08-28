# ============================================
# 第 2 课  方向盘
# 小游戏：遥控小车
# 知识：onkeypress、listen、setheading、goto、边界
# 操作：方向键开车；空格加速；R 重置
# ============================================

import turtle

WIDTH, HEIGHT = 800, 600
STEP = 20
BOOST = 40

screen = turtle.Screen()
screen.setup(WIDTH, HEIGHT)
screen.title("第 2 课 · 遥控小车")
screen.bgcolor("#102018")

car = turtle.Turtle()
car.shape("turtle")
car.color("#7CFFB2")
car.shapesize(1.8, 1.8)
car.pensize(3)
car.speed(0)
car.penup()
car.goto(0, -180)
car.pendown()
car.setheading(90)

hud = turtle.Turtle()
hud.hideturtle()
hud.penup()
hud.color("#c8f5d4")
hud.goto(0, 250)
hud.write("方向键开车  ·  空格加速冲刺  ·  R 重新出发",
          align="center", font=("PingFang SC", 16, "normal"))


def bounce_inside():
    """碰到窗口边缘就轻轻弹回来，车子不会开丢。"""
    x, y = car.xcor(), car.ycor()
    limit_x = WIDTH // 2 - 20
    limit_y = HEIGHT // 2 - 20
    if x > limit_x:
        car.setx(limit_x)
        car.setheading(180)
    elif x < -limit_x:
        car.setx(-limit_x)
        car.setheading(0)
    if y > limit_y:
        car.sety(limit_y)
        car.setheading(270)
    elif y < -limit_y:
        car.sety(-limit_y)
        car.setheading(90)


def drive(heading, distance):
    car.setheading(heading)
    car.forward(distance)
    bounce_inside()


def go_up():
    drive(90, STEP)


def go_down():
    drive(270, STEP)


def go_left():
    drive(180, STEP)


def go_right():
    drive(0, STEP)


def boost():
    drive(car.heading(), BOOST)


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
