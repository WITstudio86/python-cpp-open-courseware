"""
第5节：会反弹的球 — 弹球消砖块项目（第1节课）
功能：
  1. 一个球在窗口内自动弹跳（碰到上下左右边界反弹）
  2. 底部有一个挡板跟随鼠标左右移动
  3. 球碰到挡板也反弹
  4. 如果球落到挡板下方（没接住），球重新从顶部发出

知识点：
  - Rect 对象（x, y, width, height）
  - colliderect() 碰撞检测
  - 反弹逻辑（vx = -vx / vy = -vy）
  - mouse.get_pos() 获取鼠标位置
"""

import pygame
import sys

# ==================== 初始化 Pygame ====================
pygame.init()

# ==================== 常量定义 ====================
WIDTH = 800       # 窗口宽度（像素）
HEIGHT = 600      # 窗口高度（像素）
FPS = 60          # 帧率（每秒刷新次数）

# ==================== 颜色定义（RGB格式） ====================
WHITE  = (255, 255, 255)   # 白色（背景）
BLACK  = (0,   0,   0)     # 黑色
RED    = (255, 0,   0)     # 红色（小球）
BLUE   = (0,   100, 200)   # 蓝色（挡板）
GREEN  = (0,   200, 0)     # 绿色（备选）

# ==================== 创建窗口和时钟 ====================
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("第5节：会反弹的球")
clock = pygame.time.Clock()   # 控制帧率

# ==================== 创建角色：球（Rect对象） ====================
# Rect(左边界x, 上边界y, 宽度, 高度)
# 小球初始位置：窗口中央偏上
ball_radius = 15               # 球的半径（像素）
ball = pygame.Rect(
    WIDTH // 2 - ball_radius,  # x：水平居中
    HEIGHT // 2 - ball_radius, # y：垂直居中偏上
    ball_radius * 2,           # 宽度 = 直径
    ball_radius * 2            # 高度 = 直径
)

# 球的速度（每帧移动的像素数）
# 正数 = 向右/向下移动，负数 = 向左/向上移动
ball_vx = 6    # 水平速度
ball_vy = 6    # 垂直速度

# ==================== 创建角色：挡板（Rect对象） ====================
# 挡板放在窗口底部偏上一点的位置
paddle_width  = 120   # 挡板宽度
paddle_height = 20    # 挡板高度（厚薄）
paddle = pygame.Rect(
    WIDTH // 2 - paddle_width // 2,   # x：水平居中
    HEIGHT - 50,                       # y：窗口底部往上50像素
    paddle_width,
    paddle_height
)

# ==================== 游戏循环 ====================
running = True
while running:
    # ---------- 第1步：处理事件 ----------
    for event in pygame.event.get():
        if event.type == pygame.QUIT:   # 点击关闭按钮
            running = False

    # ---------- 第2步：更新游戏状态 ----------

    # 2.1 移动球：速度加到坐标上
    ball.x += ball_vx
    ball.y += ball_vy

    # 2.2 边界碰撞检测 —— 反弹！
    # 碰到左墙或右墙 → 水平反弹
    if ball.left <= 0 or ball.right >= WIDTH:
        ball_vx = -ball_vx   # 水平速度取反（左↔右）
        # 防止球卡在墙壁里：把球拉回到窗口内
        if ball.left < 0:
            ball.left = 0
        if ball.right > WIDTH:
            ball.right = WIDTH

    # 碰到上墙 → 垂直反弹
    if ball.top <= 0:
        ball_vy = -ball_vy   # 垂直速度取反（上↔下）
        ball.top = 0         # 把球拉回窗口内

    # 碰到下墙（球掉出底部）→ 重新发球，从挡板上方弹出
    if ball.bottom >= HEIGHT:
        # 球没接住！将球重置到窗口中央
        ball.centerx = WIDTH // 2
        ball.centery = HEIGHT // 2 - 100
        ball_vx = 6    # 速度改回初始值
        ball_vy = 6

    # 2.3 挡板跟随鼠标左右移动
    mouse_x, mouse_y = pygame.mouse.get_pos()  # 获取鼠标当前坐标
    paddle.centerx = mouse_x   # 挡板的水平中心 = 鼠标的 x 坐标

    # 限制挡板不超出窗口左右边界
    if paddle.left < 0:
        paddle.left = 0
    if paddle.right > WIDTH:
        paddle.right = WIDTH

    # 2.4 球与挡板的碰撞检测
    if ball.colliderect(paddle):
        # 碰撞了！垂直反弹
        ball_vy = -ball_vy

        # 把球移到挡板上方，防止"卡住"
        ball.bottom = paddle.top

    # ---------- 第3步：绘制画面 ----------
    screen.fill(WHITE)   # 1. 清屏（用白色填充背景）

    # 绘制小球（红色实心圆）
    # 参数：表面, 颜色, 圆心坐标, 半径
    pygame.draw.circle(screen, RED, ball.center, ball_radius)

    # 绘制挡板（蓝色矩形）
    # 参数：表面, 颜色, Rect对象
    pygame.draw.rect(screen, BLUE, paddle)

    # 绘制边框（可选，帮助看清窗口范围）
    pygame.draw.rect(screen, BLACK, (0, 0, WIDTH, HEIGHT), 3)  # 3是线宽

    # ---------- 第4步：更新画面 ----------
    pygame.display.flip()   # 将所有绘制内容显示到屏幕上

    # ---------- 第5步：控制帧率 ----------
    clock.tick(FPS)   # 限制每秒最多运行60次循环

# ==================== 退出 ====================
pygame.quit()
sys.exit()
