# ============================================
# 第 10 课  完整作品
# 小游戏：太空大战
# 知识：状态机（菜单 / 游戏 / 结束）、生命、重开
# 操作：空格开始；左右移动；空格射击
#       被敌人撞到或漏到底部扣生命；生命 0 结束
#       R 回到菜单
# ============================================

import turtle
import random

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("第 10 课 · 太空大战")
screen.bgcolor("#070b16")
screen.tracer(0)

state = "menu"  # menu / play / over
score = 0
lives = 3
vx = 0
cool = 0
wave = 1

player = turtle.Turtle()
player.shape("triangle")
player.color("#5DADE2")
player.penup()
player.goto(0, -240)
player.setheading(90)

bullets = []
enemies = []
hud = turtle.Turtle()
hud.hideturtle()
hud.penup()
hud.color("#D6EAF8")


def make_enemy():
    e = turtle.Turtle()
    e.shape("turtle")
    e.color("#E74C3C")
    e.penup()
    e.goto(random.randint(-340, 340), random.randint(140, 280))
    e.setheading(270)
    enemies.append(e)


def make_bullet():
    shot = turtle.Turtle()
    shot.shape("square")
    shot.shapesize(0.3, 0.7)
    shot.color("#F7DC6F")
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
    hud.write("太空大战", align="center", font=("PingFang SC", 42, "bold"))
    hud.goto(0, 10)
    hud.write("左右移动  ·  空格射击  ·  躲开红色敌军",
              align="center", font=("PingFang SC", 16, "normal"))
    hud.goto(0, -50)
    hud.write("按空格开始", align="center", font=("PingFang SC", 22, "bold"))
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
    hud.write(f"任务结束  得分 {score}",
              align="center", font=("PingFang SC", 28, "bold"))
    hud.goto(0, -20)
    hud.write("按 R 返回菜单",
              align="center", font=("PingFang SC", 18, "normal"))


def draw_hud():
    hud.clear()
    hud.goto(0, 250)
    hud.write(f"得分 {score}    生命 {lives}    波次 {wave}",
              align="center", font=("PingFang SC", 18, "bold"))


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
    global score, lives, cool, wave
    if state != "play":
        screen.update()
        screen.ontimer(tick, 20)
        return

    if cool > 0:
        cool -= 1

    player.setx(max(-370, min(370, player.xcor() + vx)))

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
            lives -= 1
            make_enemy()
        if player.distance(e) < 24:
            e.hideturtle()
            enemies.remove(e)
            lives -= 1
            make_enemy()
        for shot in bullets[:]:
            if e.distance(shot) < 20:
                score += 10
                shot.hideturtle()
                bullets.remove(shot)
                e.hideturtle()
                enemies.remove(e)
                make_enemy()
                break

    if score >= wave * 80:
        wave += 1
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
