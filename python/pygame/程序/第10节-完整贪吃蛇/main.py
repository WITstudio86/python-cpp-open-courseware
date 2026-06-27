"""
第10节：完整贪吃蛇
在第9节基础上增加：
- 蛇头碰撞墙壁死亡
- 蛇头碰撞自身死亡（Rect.collidelist）
- 分数面板显示（文字居中）
- 按R键重新开始（reset_game函数）
"""

import pygame
import random

# ======================== 初始化 Pygame ========================
pygame.init()

# 窗口设置
WIDTH = 800
HEIGHT = 600
GRID_SIZE = 20
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("完整贪吃蛇 - 第10节")

# 游戏时钟
clock = pygame.time.Clock()
FPS = 10

# ======================== 字体初始化 ========================
# 尝试多种中文字体名，确保跨平台兼容
font_name = None
for name in ["simhei", "microsoftyahei", "pingfang", "stheiti", "arialunicode"]:
    try:
        # 简单测试能否使用该字体
        test_font = pygame.font.SysFont(name, 32)
        font_name = name
        break
    except:
        continue
if font_name is None:
    font_name = pygame.font.get_default_font()

font = pygame.font.SysFont(font_name, 32)       # 普通字体（分数、提示）
big_font = pygame.font.SysFont(font_name, 64)   # 大字体（游戏结束标题）

# ======================== 颜色定义 ========================
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
GREEN = (0, 255, 0)          # 蛇头
DARK_GREEN = (0, 180, 0)     # 蛇身
RED = (255, 50, 50)          # 食物
GRAY = (50, 50, 50)          # 网格线
BORDER_GREEN = (0, 100, 0)   # 蛇身边框

# ======================== 全局游戏状态 ========================
snake = []
dx = 0
dy = 0
food = []
score = 0
game_over = False


def generate_food(snake_body):
    """
    随机生成一个不与蛇身重叠的食物位置
    """
    max_col = (WIDTH // GRID_SIZE) - 1
    max_row = (HEIGHT // GRID_SIZE) - 1

    while True:
        fx = random.randint(0, max_col) * GRID_SIZE
        fy = random.randint(0, max_row) * GRID_SIZE
        food_pos = [fx, fy]
        if food_pos not in snake_body:
            return food_pos


def check_wall_collision(head):
    """
    检查蛇头是否碰到墙壁
    参数 head: 蛇头坐标 [x, y]
    返回: True=碰撞, False=安全
    """
    x, y = head[0], head[1]
    # 4种碰墙情况：左墙、右墙、上墙、下墙
    return x < 0 or x >= WIDTH or y < 0 or y >= HEIGHT


def check_self_collision(snake_body):
    """
    检查蛇头是否碰到自己的身体
    使用 Rect.collidelist() 进行高效碰撞检测
    参数 snake_body: 蛇身列表
    返回: True=碰撞, False=安全
    """
    # 将蛇头转换为 Rect 对象
    head_rect = pygame.Rect(snake_body[0][0], snake_body[0][1],
                            GRID_SIZE, GRID_SIZE)

    # 将身体每一节（从第2节开始）都转换为 Rect 对象
    body_rects = []
    for segment in snake_body[1:]:
        body_rect = pygame.Rect(segment[0], segment[1],
                                GRID_SIZE, GRID_SIZE)
        body_rects.append(body_rect)

    # collidelist() 检测蛇头是否与身体中的任何一节碰撞
    # 返回 -1 表示没有碰撞，返回 >=0 的值表示碰撞
    return head_rect.collidelist(body_rects) != -1


def reset_game():
    """
    重置游戏到初始状态
    所有全局变量恢复到初始值
    """
    global snake, dx, dy, food, score, game_over

    # 蛇的初始位置：3节横排，放在屏幕中央偏左
    snake = [[400, 300],    # 蛇头
             [380, 300],    # 身体
             [360, 300]]    # 蛇尾

    # 初始方向：向右
    dx = GRID_SIZE
    dy = 0

    # 生成食物（确保不在蛇身上）
    food = generate_food(snake)

    # 分数归零
    score = 0

    # 游戏状态：进行中
    game_over = False


def draw_score_panel(screen_obj, sc):
    """
    在屏幕左上角显示当前分数
    """
    score_text = font.render(f"分数: {sc}", True, WHITE)
    # 给文字加一个半透明背景，让它在任何背景上都清晰可见
    bg_rect = pygame.Rect(5, 5, score_text.get_width() + 20, score_text.get_height() + 10)
    bg_surface = pygame.Surface((bg_rect.width, bg_rect.height))
    bg_surface.set_alpha(150)  # 半透明
    bg_surface.fill(BLACK)
    screen_obj.blit(bg_surface, (bg_rect.x, bg_rect.y))
    screen_obj.blit(score_text, (15, 10))


def draw_game_over_screen(screen_obj, final_score):
    """
    绘制游戏结束画面
    包含：半透明遮罩、游戏结束文字、最终得分、重新开始提示
    """
    # 1. 半透明黑色遮罩（让背景的蛇和食物若隐若现）
    overlay = pygame.Surface((WIDTH, HEIGHT))
    overlay.set_alpha(180)  # 180 = 较深半透明（0=透明, 255=不透明）
    overlay.fill(BLACK)
    screen_obj.blit(overlay, (0, 0))

    # 2. "游戏结束" 大字（红色，屏幕正中偏上）
    title_text = big_font.render("游戏结束", True, RED)
    title_rect = title_text.get_rect(center=(WIDTH // 2, HEIGHT // 2 - 70))
    # 给标题加一个深色背景框，更加醒目
    title_bg = pygame.Rect(title_rect.x - 20, title_rect.y - 10,
                           title_rect.width + 40, title_rect.height + 20)
    pygame.draw.rect(screen_obj, (20, 0, 0), title_bg)
    pygame.draw.rect(screen_obj, RED, title_bg, 2)
    screen_obj.blit(title_text, title_rect)

    # 3. 最终得分（白色大字）
    score_text = font.render(f"最终得分: {final_score}", True, WHITE)
    score_rect = score_text.get_rect(center=(WIDTH // 2, HEIGHT // 2 + 10))
    screen_obj.blit(score_text, score_rect)

    # 4. 重新开始提示（绿色，带轻微上下浮动效果示意按键）
    restart_text = font.render("按 R 键重新开始", True, GREEN)
    restart_rect = restart_text.get_rect(center=(WIDTH // 2, HEIGHT // 2 + 60))
    screen_obj.blit(restart_text, restart_rect)


# ======================== 启动游戏 ========================
reset_game()

# ======================== 游戏主循环 ========================
running = True
while running:
    # ---------- ① 事件处理 ----------
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        elif event.type == pygame.KEYDOWN:
            # --- 方向键：只在游戏进行中才响应 ---
            if not game_over:
                # 上键：上下方向不能反向
                if event.key == pygame.K_UP and dy == 0:
                    dx = 0
                    dy = -GRID_SIZE
                # 下键
                elif event.key == pygame.K_DOWN and dy == 0:
                    dx = 0
                    dy = GRID_SIZE
                # 左键：左右方向不能反向
                elif event.key == pygame.K_LEFT and dx == 0:
                    dx = -GRID_SIZE
                    dy = 0
                # 右键
                elif event.key == pygame.K_RIGHT and dx == 0:
                    dx = GRID_SIZE
                    dy = 0

            # --- R键：重新开始（只在游戏结束时有效）---
            if event.key == pygame.K_r and game_over:
                reset_game()

    # ---------- ② 游戏逻辑（只在游戏进行中执行）----------
    if not game_over:
        # 计算新蛇头位置
        new_head = [snake[0][0] + dx, snake[0][1] + dy]

        # 将新蛇头插入到列表最前面
        snake.insert(0, new_head)

        # 检查是否吃到食物
        if snake[0] == food:
            # 吃到食物：生成新食物，加分，不删蛇尾（自动变长）
            food = generate_food(snake)
            score += 10
        else:
            # 没吃到：删除蛇尾，保持长度不变
            snake.pop()

        # 检查碰撞（墙壁 + 自身）
        if check_wall_collision(snake[0]) or check_self_collision(snake):
            game_over = True

    # ---------- ③ 绘制画面 ----------
    screen.fill(BLACK)

    # 绘制网格背景
    for x in range(0, WIDTH, GRID_SIZE):
        pygame.draw.line(screen, GRAY, (x, 0), (x, HEIGHT), 1)
    for y in range(0, HEIGHT, GRID_SIZE):
        pygame.draw.line(screen, GRAY, (0, y), (WIDTH, y), 1)

    # 绘制食物
    pygame.draw.rect(screen, RED,
                     (food[0], food[1], GRID_SIZE, GRID_SIZE))

    # 绘制蛇身
    for i, segment in enumerate(snake):
        color = GREEN if i == 0 else DARK_GREEN
        pygame.draw.rect(screen, color,
                         (segment[0], segment[1], GRID_SIZE, GRID_SIZE))
        pygame.draw.rect(screen, BORDER_GREEN,
                         (segment[0], segment[1], GRID_SIZE, GRID_SIZE), 1)

    # 绘制分数面板（始终显示）
    draw_score_panel(screen, score)

    # 如果游戏结束，绘制结束画面
    if game_over:
        draw_game_over_screen(screen, score)

    # 刷新屏幕
    pygame.display.flip()

    # 控制速度
    clock.tick(FPS)

# 退出游戏
pygame.quit()
