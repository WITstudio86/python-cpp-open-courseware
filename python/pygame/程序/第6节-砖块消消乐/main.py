"""
第6节：砖块消消乐 — 弹球消砖块项目（第2节课）
功能：
  1. 球在窗口内弹跳，碰到左右上边界反弹
  2. 底部挡板跟随鼠标左右移动，球碰到挡板反弹
  3. 5行彩色砖块阵列（嵌套循环生成），球碰到砖块 → 砖块消失 + 得分
  4. 左上角显示当前分数
  5. 球掉出屏幕底部 → 游戏结束，显示 GAME OVER
  6. 按 R 键重新开始游戏

知识点：
  - 嵌套循环生成砖块阵列
  - 列表管理多个游戏对象（bricks = [], append, remove）
  - font.render() 文字显示
  - 游戏结束判定与重新开始
"""

import pygame
import sys

# ==================== 初始化 Pygame ====================
pygame.init()

# ==================== 常量定义 ====================
WIDTH  = 800       # 窗口宽度
HEIGHT = 600       # 窗口高度
FPS    = 60        # 帧率

# ==================== 颜色定义（RGB格式） ====================
WHITE  = (255, 255, 255)
BLACK  = (0,   0,   0)
RED    = (255, 0,   0)
BLUE   = (0,   100, 200)
GRAY   = (100, 100, 100)

# 砖块颜色：5行砖块，每行一种颜色（从上到下）
BRICK_COLORS = [
    (255, 80,  80),    # 第1行：红色（最上面）
    (255, 180, 50),    # 第2行：橙色
    (255, 255, 80),    # 第3行：黄色
    (80,  255, 80),    # 第4行：绿色
    (80,  180, 255),   # 第5行：蓝色（最下面）
]

# ==================== 创建窗口和时钟 ====================
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("第6节：砖块消消乐 — 完整打砖块游戏")
clock = pygame.time.Clock()

# ==================== 创建字体（用于显示分数和游戏结束） ====================
# Font(字体文件, 字号)。None = 使用 Pygame 默认字体
font = pygame.font.Font(None, 36)            # 分数字体
big_font = pygame.font.Font(None, 64)        # 游戏结束大字体
small_font = pygame.font.Font(None, 28)      # 提示小字体

# ==================== 创建角色：球 ====================
ball_radius = 12
ball = pygame.Rect(
    WIDTH // 2 - ball_radius,
    HEIGHT // 2,
    ball_radius * 2,
    ball_radius * 2
)
ball_vx = 6    # 球的水平速度
ball_vy = 6    # 球的垂直速度

# ==================== 创建角色：挡板 ====================
paddle_width  = 120
paddle_height = 18
paddle = pygame.Rect(
    WIDTH // 2 - paddle_width // 2,
    HEIGHT - 40,
    paddle_width,
    paddle_height
)

# ==================== 砖块参数 ====================
BRICK_ROWS   = 5       # 砖块行数
BRICK_COLS   = 8       # 砖块每行的列数
BRICK_WIDTH  = 88      # 单块砖的宽度
BRICK_HEIGHT = 22      # 单块砖的高度
BRICK_GAP    = 5       # 砖块之间的间隔
BRICK_TOP    = 60      # 砖块区域的顶部偏移（留空间给分数）

# ==================== 生成砖块阵列（嵌套循环） ====================
# 用一个列表来管理所有砖块
bricks = []

def create_bricks():
    """使用嵌套循环生成砖块阵列，并填充到 bricks 列表中"""
    global bricks
    bricks = []   # 先清空（以防重复调用）

    for row in range(BRICK_ROWS):          # 外层循环：第几行
        for col in range(BRICK_COLS):      # 内层循环：该行的第几列

            # 计算砖块坐标
            # x = 左边间隔 + 列号 × (砖宽 + 间隔)
            brick_x = BRICK_GAP + col * (BRICK_WIDTH + BRICK_GAP)
            # y = 顶部偏移 + 行号 × (砖高 + 间隔)
            brick_y = BRICK_TOP + row * (BRICK_HEIGHT + BRICK_GAP)

            # 创建砖块的 Rect 对象
            brick = pygame.Rect(brick_x, brick_y, BRICK_WIDTH, BRICK_HEIGHT)

            # 把砖块加入列表
            bricks.append(brick)

# 初始生成砖块
create_bricks()

# ==================== 游戏状态变量 ====================
score = 0            # 当前分数
game_over = False    # 是否游戏结束

# ==================== 游戏循环 ====================
running = True
while running:
    # ---------- 第1步：处理事件 ----------
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # ---------- 第2步：游戏结束时的处理 ----------
    if game_over:
        # 检测 R 键是否被按下 → 重新开始
        keys = pygame.key.get_pressed()
        if keys[pygame.K_r]:
            # 重置所有状态
            game_over = False
            score = 0

            # 重新生成砖块
            create_bricks()

            # 重置球的位置和速度
            ball.centerx = WIDTH // 2
            ball.centery = HEIGHT // 2
            ball_vx = 6
            ball_vy = 6

        # 绘制游戏结束画面
        screen.fill(BLACK)

        # "游戏结束" 大字（红色，居中）
        over_text = big_font.render("游戏结束", True, RED)
        over_rect = over_text.get_rect(center=(WIDTH // 2, HEIGHT // 2 - 40))
        screen.blit(over_text, over_rect)

        # "按 R 键重新开始" 提示
        hint_text = font.render("按 R 键重新开始", True, WHITE)
        hint_rect = hint_text.get_rect(center=(WIDTH // 2, HEIGHT // 2 + 40))
        screen.blit(hint_text, hint_rect)

        # 显示最终分数
        final_score_text = font.render(f"最终得分: {score}", True, (255, 255, 0))
        final_rect = final_score_text.get_rect(center=(WIDTH // 2, HEIGHT // 2 + 90))
        screen.blit(final_score_text, final_rect)

        pygame.display.flip()
        clock.tick(FPS)
        continue   # ← 跳过游戏逻辑，直接进入下一帧

    # ---------- 第3步：更新球的位置 ----------
    ball.x += ball_vx
    ball.y += ball_vy

    # ---------- 第4步：球与窗口边界的碰撞检测 ----------
    # 碰左墙或右墙 → 水平反弹
    if ball.left <= 0 or ball.right >= WIDTH:
        ball_vx = -ball_vx
        # 防止球卡在墙里
        if ball.left < 0:
            ball.left = 0
        if ball.right > WIDTH:
            ball.right = WIDTH

    # 碰上墙 → 垂直反弹
    if ball.top <= 0:
        ball_vy = -ball_vy
        ball.top = 0

    # 球掉出底部 → 游戏结束！
    if ball.bottom >= HEIGHT:
        game_over = True

    # ---------- 第5步：挡板跟随鼠标 ----------
    mouse_x, mouse_y = pygame.mouse.get_pos()
    paddle.centerx = mouse_x

    # 限制挡板不超出窗口
    if paddle.left < 0:
        paddle.left = 0
    if paddle.right > WIDTH:
        paddle.right = WIDTH

    # ---------- 第6步：球与挡板的碰撞检测 ----------
    if ball.colliderect(paddle):
        ball_vy = -ball_vy                # 垂直反弹
        ball.bottom = paddle.top          # 防止球卡进挡板

    # ---------- 第7步：球与砖块的碰撞检测 ----------
    # 使用 bricks[:] 创建列表副本进行遍历（安全做法）
    for brick in bricks[:]:
        if ball.colliderect(brick):
            bricks.remove(brick)     # 消除这块砖
            ball_vy = -ball_vy       # 球反弹
            score += 10              # 分数 +10
            break                    # 一帧只消除一块砖，防止重复删除

    # ---------- 第8步：绘制画面 ----------
    screen.fill(BLACK)   # 黑色背景

    # 8.1 绘制所有砖块（不同行不同颜色）
    for row in range(BRICK_ROWS):
        color = BRICK_COLORS[row]   # 从颜色列表获取该行的颜色
        for col in range(BRICK_COLS):
            # 计算出当前砖块的索引（在 bricks 列表中的位置）
            index = row * BRICK_COLS + col
            if index < len(bricks):   # 安全检查（砖块可能已被消除）
                pygame.draw.rect(screen, color, bricks[index])
                # 给砖块加个边框，更好看
                pygame.draw.rect(screen, BLACK, bricks[index], 1)

    # 8.2 绘制球（红色实心圆）
    pygame.draw.circle(screen, RED, ball.center, ball_radius)

    # 8.3 绘制挡板（蓝色矩形，带圆角效果用普通矩形+边框）
    pygame.draw.rect(screen, BLUE, paddle)
    pygame.draw.rect(screen, (150, 200, 255), paddle, 2)  # 浅色边框

    # 8.4 绘制分数文字（左上角）
    score_text = font.render(f"分数: {score}", True, WHITE)
    screen.blit(score_text, (15, 15))

    # ---------- 第9步：更新画面 + 控制帧率 ----------
    pygame.display.flip()
    clock.tick(FPS)

# ==================== 退出 ====================
pygame.quit()
sys.exit()
