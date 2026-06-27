"""
第24节：水管森林 — Flappy Bird 项目（第2节课）
==============================================
功能：
  1. 小鸟受重力下落，按空格键向上飞
  2. 上下水管对从右向左移动，间隙随机偏移
  3. 小鸟碰撞水管/地面/天空 → 游戏结束
  4. 小鸟穿过一对水管 → 得分 +1
  5. 显示当前分数和最高分（session内保存）
  6. Game Over 画面，按空格重新开始
  7. 全部素材用 pygame.Surface / draw 绘制，不依赖外部图片

知识点：
  - 水管对生成（上水管+间隙+下水管）
  - 三种碰撞检测
  - 过管计分 + scored 标记防重复
  - 游戏状态机（playing / game_over）
  - 最高分记录
"""

import pygame
import random
import sys

# ==================== 初始化 Pygame ====================
pygame.init()

# ==================== 常量定义 ====================
WIDTH = 400                # 窗口宽度
HEIGHT = 600               # 窗口高度
FPS = 60                   # 帧率

# 小鸟相关常量
BIRD_X = 80                # 小鸟的水平位置（固定）
BIRD_RADIUS = 18           # 小鸟半径（用圆形表示）
GRAVITY = 0.5              # 重力加速度（每帧增加的下降速度）
FLAP_STRENGTH = -8         # 空格上升的力度（负值=向上）

# 水管相关常量
PIPE_WIDTH = 60            # 水管宽度
PIPE_SPEED = 3             # 水管向左移动的速度
PIPE_SPAWN_INTERVAL = 100  # 每隔多少帧生成一对水管
GAP_SIZE = 150             # 上下水管之间的间隙（固定大小）

# 颜色定义
SKY_COLOR = (135, 206, 235)       # 天蓝色背景
BIRD_COLOR = (255, 220, 0)        # 小鸟颜色（金黄色）
BIRD_EYE_COLOR = (0, 0, 0)        # 小鸟眼睛颜色（黑色）
BIRD_WING_COLOR = (255, 180, 0)   # 小鸟翅膀颜色（橙色）
PIPE_COLOR = (50, 180, 50)        # 水管颜色（绿色）
PIPE_BORDER_COLOR = (30, 140, 30) # 水管边框颜色（深绿色）
GROUND_COLOR = (200, 180, 100)    # 地面颜色（土黄色）
TEXT_COLOR = (255, 255, 255)      # 文字颜色（白色）
SHADOW_COLOR = (0, 0, 0)          # 阴影/描边颜色（黑色）

# ==================== 创建窗口 ====================
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("第24节：水管森林 — Flappy Bird")
clock = pygame.time.Clock()

# ==================== 文字渲染函数 ====================
def draw_text(text, size, color, x, y, center=False):
    """
    在屏幕上绘制文字。
    center=True 时，(x, y) 为文字的中心位置
    center=False 时，(x, y) 为文字的左上角位置
    """
    font = pygame.font.SysFont("simhei", size)
    text_surface = font.render(str(text), True, color)
    if center:
        text_rect = text_surface.get_rect(center=(x, y))
        screen.blit(text_surface, text_rect)
    else:
        screen.blit(text_surface, (x, y))

# ==================== 游戏状态变量 ====================
# 游戏状态："playing"（游戏中）或 "game_over"（游戏结束）
game_state = "playing"

# 小鸟变量
bird_y = HEIGHT // 2      # 小鸟的 y 坐标（圆心）
bird_vy = 0               # 小鸟的垂直速度（正数向下，负数向上）

# 水管列表：每个元素为 [top_pipe_rect, bottom_pipe_rect, scored]
# scored=False 表示未计分，scored=True 表示已计分
pipes = []

# 水管生成计时器：每帧+1，达到阈值时生成水管并归零
pipe_timer = 0

# 分数
score = 0
high_score = 0            # 最高分（本次运行session内保存）

# ==================== 重置游戏函数 ====================
def reset_game():
    """将所有游戏变量重置为初始状态"""
    global bird_y, bird_vy, pipes, pipe_timer, score, game_state
    bird_y = HEIGHT // 2
    bird_vy = 0
    pipes.clear()
    pipe_timer = 0
    score = 0
    game_state = "playing"

# ==================== 绘制小鸟函数 ====================
def draw_bird(x, y):
    """
    用 Surface 绘制一只可爱的小鸟（不用外部图片）。
    小鸟由圆形身体 + 小眼睛 + 小翅膀组成。
    """
    # 1. 画身体（圆形）
    pygame.draw.circle(screen, BIRD_COLOR, (x, y), BIRD_RADIUS)
    pygame.draw.circle(screen, SHADOW_COLOR, (x, y), BIRD_RADIUS, 2)  # 描边

    # 2. 画眼睛（白色大圆 + 黑色小瞳孔）
    eye_x = x + 6   # 眼睛在身体右侧
    eye_y = y - 4   # 眼睛稍微靠上
    pygame.draw.circle(screen, (255, 255, 255), (eye_x, eye_y), 6)     # 眼白
    pygame.draw.circle(screen, BIRD_EYE_COLOR, (eye_x + 2, eye_y), 3) # 瞳孔

    # 3. 画翅膀（小椭圆，用矩形近似）
    wing_x = x - 4
    wing_y = y - 2
    pygame.draw.ellipse(screen, BIRD_WING_COLOR,
                        (wing_x - 8, wing_y - 4, 16, 10))

# ==================== 绘制水管函数 ====================
def draw_pipe(pipe_rect):
    """
    用 Surface 绘制一根水管。
    水管有主体颜色和深色边框，顶部/底部有管口装饰。
    """
    # 画水管主体
    pygame.draw.rect(screen, PIPE_COLOR, pipe_rect)
    # 画水管边框（立体感）
    pygame.draw.rect(screen, PIPE_BORDER_COLOR, pipe_rect, 2)

    # 画管口装饰（让水管看起来像水管）
    # 上水管的底部管口 或 下水管的顶部管口
    cap_height = 8
    cap_rect = pygame.Rect(
        pipe_rect.x - 4,       # 管口比管身略宽（左右各多4像素）
        pipe_rect.y + pipe_rect.height - cap_height,  # 默认底部管口
        pipe_rect.width + 8,
        cap_height
    )
    # 如果是下水管（top > 0），管口在顶部
    if pipe_rect.top > HEIGHT // 2:
        cap_rect.y = pipe_rect.y
    pygame.draw.rect(screen, PIPE_BORDER_COLOR, cap_rect)

# ==================== 游戏循环 ====================
running = True
while running:
    # ========== 第1步：处理事件 ==========
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        # 空格键按下：小鸟向上飞 / 重新开始游戏
        if event.type == pygame.KEYDOWN and event.key == pygame.K_SPACE:
            if game_state == "playing":
                bird_vy = FLAP_STRENGTH  # 给小鸟一个向上的速度
            elif game_state == "game_over":
                reset_game()  # 重新开始游戏

    # ========== 第2步：更新游戏状态 ==========

    if game_state == "playing":
        # --- 2.1 更新小鸟位置 ---
        bird_vy += GRAVITY          # 重力影响：速度增加（向下加速度）
        bird_y += bird_vy           # 速度影响位置

        # --- 2.2 创建小鸟的碰撞检测矩形 ---
        bird_rect = pygame.Rect(
            BIRD_X - BIRD_RADIUS,   # 矩形左边界 = 圆心x - 半径
            bird_y - BIRD_RADIUS,   # 矩形上边界 = 圆心y - 半径
            BIRD_RADIUS * 2,        # 矩形宽度 = 直径
            BIRD_RADIUS * 2         # 矩形高度 = 直径
        )

        # --- 2.3 生成水管 ---
        pipe_timer += 1
        if pipe_timer >= PIPE_SPAWN_INTERVAL:
            pipe_timer = 0
            # 随机生成间隙的 y 坐标（间隙上沿位置）
            # 范围：不能太靠近顶部和底部
            gap_y = random.randint(80, HEIGHT - 80 - GAP_SIZE)

            # 上水管：从窗口顶部(0) 延伸到 间隙上沿(gap_y)
            top_pipe = pygame.Rect(WIDTH, 0, PIPE_WIDTH, gap_y)

            # 下水管：从间隙下沿(gap_y + GAP_SIZE) 延伸到 窗口底部(HEIGHT)
            bottom_pipe = pygame.Rect(
                WIDTH,
                gap_y + GAP_SIZE,
                PIPE_WIDTH,
                HEIGHT - gap_y - GAP_SIZE
            )

            # 将水管对添加到列表，scored=False 表示还没计分
            pipes.append([top_pipe, bottom_pipe, False])

        # --- 2.4 移动水管并从列表中移除移出屏幕的水管 ---
        for pipe_pair in pipes[:]:  # 用[:]切片遍历副本，避免删除时出错
            pipe_pair[0].x -= PIPE_SPEED  # 上水管向左移动
            pipe_pair[1].x -= PIPE_SPEED  # 下水管向左移动

            # 如果水管完全移出屏幕左边界，从列表中删除
            if pipe_pair[0].right < 0:
                pipes.remove(pipe_pair)

        # --- 2.5 碰撞检测（三种死亡方式） ---
        dead = False

        # 碰撞1：小鸟撞到水管
        for pipe_pair in pipes:
            top_pipe, bottom_pipe, scored = pipe_pair
            if bird_rect.colliderect(top_pipe) or bird_rect.colliderect(bottom_pipe):
                dead = True
                break  # 已经死亡，不需要继续检测

        # 碰撞2：小鸟撞到地面（小鸟底部超出窗口下边界）
        if bird_rect.bottom >= HEIGHT:
            dead = True

        # 碰撞3：小鸟撞到天空（小鸟顶部超出窗口上边界）
        if bird_rect.top <= 0:
            dead = True

        # 如果死亡，切换到 game_over 状态
        if dead:
            game_state = "game_over"
            # 更新最高分
            if score > high_score:
                high_score = score

        # --- 2.6 过管计分检测 ---
        # 条件：小鸟的左边缘超过了水管的右边缘，且这对水管还没被计过分
        for pipe_pair in pipes:
            top_pipe, bottom_pipe, scored = pipe_pair
            if bird_rect.left > top_pipe.right and not scored:
                score += 1
                pipe_pair[2] = True  # 标记为已计分，防止重复加分

    # ========== 第3步：绘制画面 ==========

    # --- 3.1 清屏 ---
    screen.fill(SKY_COLOR)

    if game_state == "playing":
        # --- 3.2 绘制水管 ---
        for pipe_pair in pipes:
            draw_pipe(pipe_pair[0])  # 上水管
            draw_pipe(pipe_pair[1])  # 下水管

        # --- 3.3 绘制地面（装饰线） ---
        pygame.draw.rect(screen, GROUND_COLOR, (0, HEIGHT - 15, WIDTH, 15))
        # 地面花纹（简单的小草或条纹）
        for i in range(0, WIDTH, 40):
            pygame.draw.rect(screen, (100, 140, 60),
                             (i, HEIGHT - 15, 20, 8))

        # --- 3.4 绘制小鸟 ---
        draw_bird(BIRD_X, int(bird_y))

        # --- 3.5 绘制分数（左上角） ---
        # 分数背景框
        score_bg = pygame.Rect(5, 5, 120, 35)
        pygame.draw.rect(screen, (0, 0, 0, 100), score_bg, border_radius=5)
        draw_text(f"分数: {score}", 24, TEXT_COLOR, 10, 10)

        # 最高分（右上角）
        high_bg = pygame.Rect(WIDTH - 130, 5, 125, 35)
        pygame.draw.rect(screen, (0, 0, 0, 100), high_bg, border_radius=5)
        draw_text(f"最高: {high_score}", 20, TEXT_COLOR, WIDTH - 125, 12)

    elif game_state == "game_over":
        # --- 3.6 游戏结束画面 ---
        # 先绘制静态的游戏画面（水管和小鸟停在原地）
        for pipe_pair in pipes:
            draw_pipe(pipe_pair[0])
            draw_pipe(pipe_pair[1])
        pygame.draw.rect(screen, GROUND_COLOR, (0, HEIGHT - 15, WIDTH, 15))
        for i in range(0, WIDTH, 40):
            pygame.draw.rect(screen, (100, 140, 60),
                             (i, HEIGHT - 15, 20, 8))
        draw_bird(BIRD_X, int(bird_y))

        # 半透明遮罩
        overlay = pygame.Surface((WIDTH, HEIGHT))
        overlay.set_alpha(160)  # 透明度
        overlay.fill((0, 0, 0))
        screen.blit(overlay, (0, 0))

        # Game Over 标题
        draw_text("游戏结束", 48, (255, 80, 80), WIDTH // 2, 180, center=True)

        # 本局分数
        draw_text(f"本局得分: {score}", 30, TEXT_COLOR, WIDTH // 2, 250, center=True)

        # 最高分
        if score >= high_score and score > 0:
            draw_text(f"🏆 新纪录！", 28, (255, 255, 0), WIDTH // 2, 300, center=True)
        draw_text(f"最高分: {high_score}", 26, TEXT_COLOR, WIDTH // 2, 340, center=True)

        # 重新开始提示
        draw_text("按 空格键 重新开始", 24, (200, 200, 200),
                  WIDTH // 2, 420, center=True)

    # ========== 第4步：更新画面 ==========
    pygame.display.flip()

    # ========== 第5步：控制帧率 ==========
    clock.tick(FPS)

# ==================== 退出 ====================
pygame.quit()
sys.exit()
