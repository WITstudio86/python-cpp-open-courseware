"""
第21节：双人对战 —— Pong游戏
面向10-15岁中小学生 | Pygame课程

控制说明：
  玩家1（左球拍）：W键上移 / S键下移
  玩家2（右球拍）：↑键上移 / ↓键下移

功能：
  - 两个球拍分别由两个玩家控制
  - 球在屏幕中弹跳
  - 球拍碰撞时根据击球位置调整反弹角度
  - 球出界后对方得分，重新发球
  - 显示比分
  - 全部使用Surface/draw绘制，不依赖外部图片
"""

import pygame
import sys
import random

# ============================================================
# 1. 初始化 Pygame
# ============================================================
pygame.init()

# 窗口尺寸
WIDTH, HEIGHT = 800, 500
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Pong - 双人对战")

# 时钟：控制帧率
clock = pygame.time.Clock()
FPS = 60

# ============================================================
# 2. 颜色常量
# ============================================================
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
GRAY = (80, 80, 80)
RED = (233, 69, 96)       # 用于装饰/提示

# ============================================================
# 3. 创建游戏对象（全部用 Rect + Surface 绘制，不依赖外部图片）
# ============================================================

# --- 球拍 ---
PADDLE_WIDTH = 15
PADDLE_HEIGHT = 100
PADDLE_SPEED = 6  # 球拍移动速度

# 左球拍（玩家1）
left_paddle = pygame.Rect(
    30,                      # 距左边界30像素
    HEIGHT // 2 - PADDLE_HEIGHT // 2,  # 垂直居中
    PADDLE_WIDTH,
    PADDLE_HEIGHT
)

# 右球拍（玩家2）
right_paddle = pygame.Rect(
    WIDTH - 30 - PADDLE_WIDTH,  # 距右边界30像素
    HEIGHT // 2 - PADDLE_HEIGHT // 2,
    PADDLE_WIDTH,
    PADDLE_HEIGHT
)

# --- 球 ---
BALL_SIZE = 20
MAX_BOUNCE_SPEED = 6  # 碰撞时最大垂直反弹速度

ball = pygame.Rect(
    WIDTH // 2 - BALL_SIZE // 2,   # 水平居中
    HEIGHT // 2 - BALL_SIZE // 2,  # 垂直居中
    BALL_SIZE,
    BALL_SIZE
)

# 球的初始速度方向（随机）
ball_speed_x = 4 * random.choice([-1, 1])
ball_speed_y = 4 * random.choice([-1, 1])

# --- 比分 ---
left_score = 0   # 左方（玩家1）得分
right_score = 0  # 右方（玩家2）得分

# --- 字体 ---
font = pygame.font.Font(None, 48)       # 比分显示字体
small_font = pygame.font.Font(None, 24)  # 提示文字字体

# ============================================================
# 4. 辅助函数
# ============================================================

def reset_ball():
    """重新发球：球回到屏幕中央，随机方向发出"""
    global ball_speed_x, ball_speed_y
    ball.center = (WIDTH // 2, HEIGHT // 2)
    # 随机水平方向（左或右）
    ball_speed_x = 4 * random.choice([-1, 1])
    # 随机垂直方向（上或下）
    ball_speed_y = 4 * random.choice([-1, 1])


def handle_paddle_collision(paddle):
    """
    处理球与球拍的碰撞，根据击球位置调整反弹角度。
    球拍上半部分 → 球向上弹；球拍下半部分 → 球向下弹。
    """
    global ball_speed_x, ball_speed_y

    # 计算球心与球拍中心的垂直偏移，归一化到 [-1, 1]
    # -1 = 球拍顶部, 0 = 球拍中心, 1 = 球拍底部
    offset_y = (ball.centery - paddle.centery) / (paddle.height / 2)

    # 根据偏移量设置垂直速度
    ball_speed_y = int(offset_y * MAX_BOUNCE_SPEED)

    # 水平速度始终反转（球向反方向弹回）
    ball_speed_x = -ball_speed_x


def draw_objects():
    """绘制所有游戏对象"""
    # 背景
    screen.fill(BLACK)

    # 中线（虚线效果：用多个短线段）
    for y in range(0, HEIGHT, 30):
        pygame.draw.rect(screen, GRAY, (WIDTH // 2 - 1, y, 2, 15))

    # 左球拍
    pygame.draw.rect(screen, WHITE, left_paddle)
    # 球拍边框装饰
    pygame.draw.rect(screen, GRAY, left_paddle, 1)

    # 右球拍
    pygame.draw.rect(screen, WHITE, right_paddle)
    pygame.draw.rect(screen, GRAY, right_paddle, 1)

    # 球（用椭圆绘制，更像圆形）
    pygame.draw.ellipse(screen, WHITE, ball)

    # 比分
    left_text = font.render(str(left_score), True, WHITE)
    right_text = font.render(str(right_score), True, WHITE)
    screen.blit(left_text, (WIDTH // 4, 20))
    screen.blit(right_text, (WIDTH * 3 // 4 - right_text.get_width(), 20))

    # 操作提示（屏幕底部）
    tip1 = small_font.render("玩家1: W/S", True, GRAY)
    tip2 = small_font.render("玩家2: ↑/↓", True, GRAY)
    screen.blit(tip1, (80, HEIGHT - 30))
    screen.blit(tip2, (WIDTH - 220, HEIGHT - 30))

    # 更新屏幕
    pygame.display.flip()


# ============================================================
# 5. 游戏主循环
# ============================================================
running = True

while running:
    # --- 事件处理 ---
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        # 按 ESC 键也可以退出
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                running = False

    # --- 按键输入处理（双玩家）---
    keys = pygame.key.get_pressed()

    # 玩家1：左球拍（W键上移 / S键下移）
    if keys[pygame.K_w]:
        left_paddle.y -= PADDLE_SPEED
    if keys[pygame.K_s]:
        left_paddle.y += PADDLE_SPEED

    # 玩家2：右球拍（↑键上移 / ↓键下移）
    if keys[pygame.K_UP]:
        right_paddle.y -= PADDLE_SPEED
    if keys[pygame.K_DOWN]:
        right_paddle.y += PADDLE_SPEED

    # --- 边界限制：防止球拍移出屏幕 ---
    if left_paddle.top < 0:
        left_paddle.top = 0
    if left_paddle.bottom > HEIGHT:
        left_paddle.bottom = HEIGHT
    if right_paddle.top < 0:
        right_paddle.top = 0
    if right_paddle.bottom > HEIGHT:
        right_paddle.bottom = HEIGHT

    # --- 球移动 ---
    ball.x += ball_speed_x
    ball.y += ball_speed_y

    # --- 上下边界反弹 ---
    if ball.top <= 0:
        ball.top = 0  # 修正位置，防止卡边界
        ball_speed_y = -ball_speed_y
    if ball.bottom >= HEIGHT:
        ball.bottom = HEIGHT
        ball_speed_y = -ball_speed_y

    # --- 球拍碰撞检测（带角度变化）---
    if ball.colliderect(left_paddle):
        # 将球推到球拍右侧，防止重复碰撞
        ball.left = left_paddle.right
        handle_paddle_collision(left_paddle)

    if ball.colliderect(right_paddle):
        # 将球推到球拍左侧，防止重复碰撞
        ball.right = right_paddle.left
        handle_paddle_collision(right_paddle)

    # --- 出界判定与得分 ---
    if ball.left <= 0:
        # 球越过左边界 → 右方（玩家2）得分
        right_score += 1
        reset_ball()

    if ball.right >= WIDTH:
        # 球越过右边界 → 左方（玩家1）得分
        left_score += 1
        reset_ball()

    # --- 绘制 ---
    draw_objects()

    # --- 控制帧率 ---
    clock.tick(FPS)

# ============================================================
# 6. 退出游戏
# ============================================================
pygame.quit()
sys.exit()
