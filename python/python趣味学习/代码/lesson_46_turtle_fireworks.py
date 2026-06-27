# -*- coding: utf-8 -*-
"""
课程编号：lesson_46
课程标题：项目八：Turtle 烟花动画
学习目标：
    1. 学会使用 turtle 模块绘制动画
    2. 理解动画的基本原理：不断清屏 → 更新位置 → 重新绘制
    3. 学会使用 random 模块给烟花添加随机颜色和运动轨迹
    4. 体验编程创造视觉效果的乐趣
"""

import turtle
import random
import math

# ==================== 第一步：设置画布 ====================

# 创建屏幕对象
screen = turtle.Screen()
screen.title("🎆 烟花动画 🎆")       # 窗口标题
screen.bgcolor("black")            # 背景设为黑色（夜空）
screen.setup(width=800, height=700)  # 窗口大小

# 加快绘制速度
screen.tracer(0)  # 关闭自动刷新，手动控制画面更新


# ==================== 第二步：烟花粒子类（用列表 + 字典表示） ====================

def create_firework(x, y, particle_count):
    """
    在坐标 (x, y) 处创建一个烟花
    返回一个粒子列表，每个粒子是一个字典，包含：
      - x, y : 粒子的当前位置
      - vx, vy : 粒子的速度（水平和垂直方向）
      - color : 粒子的颜色
      - life : 剩余生命值（帧数）
      - size : 粒子大小
    """
    particles = []

    # 可选的烟花颜色（明亮的颜色在黑色背景上更好看）
    colors = ["red", "orange", "yellow", "gold", "cyan",
              "magenta", "pink", "spring green", "dodger blue",
              "violet", "white", "hot pink"]

    # 360 度平均分成 particle_count 份
    angle_step = 360 / particle_count

    for i in range(particle_count):
        # 计算当前粒子的发射角度（弧度制）
        angle = math.radians(i * angle_step + random.uniform(-10, 10))

        # 随机速度大小（距离中心越远越快）
        speed = random.uniform(2, 8)

        # 分解为水平速度和垂直速度
        vx = math.cos(angle) * speed     # cos 计算水平分量
        vy = math.sin(angle) * speed     # sin 计算垂直分量

        # 随机生命值（让有些粒子飞得更久）
        life = random.randint(20, 60)

        # 创建粒子字典
        particle = {
            "x": x,                         # 初始 x 坐标
            "y": y,                         # 初始 y 坐标
            "vx": vx,                       # x 方向速度
            "vy": vy,                       # y 方向速度
            "color": random.choice(colors), # 随机颜色
            "life": life,                   # 剩余生命
            "max_life": life,               # 初始生命（用于渐隐效果）
            "size": random.randint(2, 6),   # 粒子大小
        }
        particles.append(particle)

    return particles


# ==================== 第三步：绘制一个粒子 ====================

def draw_particle(p):
    """
    在粒子 p 的当前位置画一个小圆点
    """
    turtle.penup()               # 抬笔（不画线）
    turtle.goto(p["x"], p["y"])  # 移动到粒子位置
    turtle.pendown()             # 落笔

    turtle.color(p["color"])     # 设置颜色
    turtle.dot(p["size"])        # 画一个圆点


# ==================== 第四步：更新粒子位置 ====================

def update_particles(particles):
    """
    更新所有粒子的位置和生命值
    返回还"活着"的粒子列表
    """
    alive = []  # 存放还活着的粒子

    for p in particles:
        # 移动粒子
        p["x"] = p["x"] + p["vx"]
        p["y"] = p["y"] + p["vy"]

        # 模拟重力：垂直速度逐渐减小（烟花粒子向下飘落）
        p["vy"] = p["vy"] - 0.1

        # 生命值减 1
        p["life"] = p["life"] - 1

        # 渐隐效果：生命越少，粒子越小
        fade_ratio = p["life"] / p["max_life"]
        p["size"] = max(0.5, p["size"] * 0.98)  # 缓慢缩小

        # 如果还有生命，保留这个粒子
        if p["life"] > 0:
            alive.append(p)

    return alive


# ==================== 第五步：画一颗星星（装饰夜空） ====================

def draw_stars(count=30):
    """
    在夜空中随机画一些星星作为背景
    """
    turtle.penup()
    turtle.color("white")
    for _ in range(count):
        x = random.randint(-380, 380)
        y = random.randint(-320, 320)
        turtle.goto(x, y)
        size = random.uniform(0.5, 2.5)
        # 有些星星稍微偏黄
        if random.random() < 0.3:
            turtle.color("light yellow")
        else:
            turtle.color("white")
        turtle.dot(size)
    turtle.color("white")  # 恢复颜色


# ==================== 第六步：烟花上升动画 ====================

def launch_firework():
    """
    模拟烟花从底部发射升空的过程
    返回爆炸中心坐标 (x, y)
    """
    # 随机选择一个发射位置（画面下方）
    launch_x = random.randint(-250, 250)
    launch_y = -300  # 从底部发射

    # 随机选择目标爆炸高度
    target_y = random.randint(50, 280)

    # 上升动画
    rocket = turtle.Turtle()
    rocket.hideturtle()
    rocket.penup()
    rocket.color("white")
    rocket.goto(launch_x, launch_y)

    # 上升过程：y 坐标逐步增加
    current_y = launch_y
    while current_y < target_y:
        rocket.clear()
        rocket.goto(launch_x, current_y)
        rocket.dot(4)  # 画一个小亮点表示上升中的烟花
        screen.update()
        current_y += 8  # 每次上升 8 像素

    rocket.clear()  # 清除上升痕迹
    return (launch_x, target_y)


# ==================== 第七步：主程序 ====================

def main():
    """
    主程序：循环播放烟花动画
    """

    # 隐藏默认的海龟箭头
    turtle.hideturtle()

    # 先画星星背景
    print("正在绘制星空背景...")
    draw_stars(50)
    screen.update()

    print("烟花表演开始！按 Ctrl+C 或直接关闭窗口退出。")
    print("-" * 40)

    # 连续放 8 个烟花
    for firework_num in range(1, 9):
        print(f"第 {firework_num} 个烟花正在绽放...")

        # 1. 发射升空
        boom_x, boom_y = launch_firework()

        # 2. 创建爆炸粒子（随机 40-80 个粒子）
        particle_count = random.randint(40, 80)
        particles = create_firework(boom_x, boom_y, particle_count)

        # 3. 动画循环：不断更新和绘制粒子
        for frame in range(100):  # 最多 100 帧
            # 清屏（但保留星星背景）
            screen.update()

            # 用黑色覆盖上一帧的所有粒子（简单方式：重画背景）
            # 但这样会擦掉星星 → 所以每帧重画星空太慢
            # 更好的方式：我们使用 turtle 的 clear() 来只清除海龟画的
            # 然后用一个新的隐藏海龟来画粒子

            # 先清除上一帧的粒子
            turtle.clear()

            # 更新粒子状态
            particles = update_particles(particles)

            # 如果所有粒子都消失了，结束这个烟花
            if len(particles) == 0:
                break

            # 绘制当前帧的所有粒子
            for p in particles:
                draw_particle(p)

            # 显示这一帧
            screen.update()

            # 短暂停顿，控制动画速度
            # （turtle 自身的延迟）
            for _ in range(5000):  # 用空循环做简单延迟
                pass

    print("-" * 40)
    print("烟花表演结束！点击窗口关闭。")

    # 保持窗口打开
    turtle.done()


# 运行程序
if __name__ == "__main__":
    main()


# ==================== 练习题 ====================

"""
练习一：画多个烟花同时绽放
---------------------------------------------------
上面的程序是一次放一个烟花。请修改代码，让程序可以"同时"绽放多个烟花。
提示：
  - 创建多个烟花（不同的爆炸位置），把它们的粒子全部放入一个
    大的 particles 列表中
  - 然后在一个动画循环中同时更新和绘制所有粒子
  - 这样看起来就像是多个烟花一起绽放！

练习二：控制烟花粒子的数量
---------------------------------------------------
在 create_firework 函数中，粒子数量是 particle_count 参数决定的。
请为程序增加一个用户输入功能：
  - 程序开始时询问用户："想要多少粒子的烟花？（建议 30-100）"
  - 根据用户的输入来设置粒子数量
  - 还可以让用户选择烟花的颜色主题（暖色/冷色/随机）

练习三：加入渐隐效果
---------------------------------------------------
上面的程序中，粒子会一直保持原来的颜色，直到生命值归零后突然消失。
请改进 update_particles 函数，加入真正的渐隐效果：
提示：
  - Turtle 不支持透明度，但我们可以用"大小逐渐变小"来模拟渐隐
  - 也可以让粒子颜色从亮色逐渐变成暗色（比如从 yellow 变成 dark orange
    再变成 red，最后变成 dark red）
  - 在 update_particles 中根据剩余生命比例来改变颜色
"""


# ==================== 综合小挑战 ====================

"""
综合挑战：打造一场"烟花秀"
---------------------------------------------------
用本课学到的内容，编写一场完整的烟花秀表演！

要求：
1. 背景有星星，还可以加上月亮（画一个黄色大圆）
2. 至少 10 个烟花，分为不同的"节目"：
   - 第一幕：红色系烟花（3 个）
   - 第二幕：蓝紫色系烟花（3 个）
   - 第三幕：金色系烟花（3 个）
   - 终幕：所有颜色混合的烟花（1 个大型烟花，粒子 > 150）
3. 每个烟花之间暂停 1-2 秒
4. 最后屏幕上显示一行文字："THE END" 或 "谢谢观看"
   提示：用 turtle.write() 方法来写文字

扩展思考：
  - 能不能让烟花在爆炸后，粒子不是直线飞出，而是带一点弯曲？
    （提示：给 vx 也加一个微小的变化量）
  - 能不能加入音效？（提示：可以用 winsound 或 pygame 模块）
"""
