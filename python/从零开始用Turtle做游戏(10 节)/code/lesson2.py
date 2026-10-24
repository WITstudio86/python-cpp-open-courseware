# ============================================
# 第 2 课  方向盘
# 小游戏：遥控小车
# 知识：onkeypress、listen、setheading、边界
# 操作：方向键开车；空格加速；R 重置
# ============================================

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
