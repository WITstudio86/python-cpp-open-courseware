"""
第9节：贪吃的小蛇
- 蛇身用列表表示，每个元素是[x, y]坐标
- 方向键控制移动方向（防止反向移动）
- 食物随机生成，不与蛇身重叠
- 吃到食物变长（头插不删尾）
"""

import pygame
import random

# ======================== 初始化 Pygame ========================
pygame.init()

# 窗口设置
WIDTH = 800
HEIGHT = 600
GRID_SIZE = 20          # 每个格子的像素大小
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("贪吃的小蛇 - 第9节")

# 游戏时钟
clock = pygame.time.Clock()
FPS = 10                # 每秒10帧，控制蛇的移动速度

# ======================== 颜色定义 ========================
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
GREEN = (0, 255, 0)          # 蛇头颜色
DARK_GREEN = (0, 180, 0)     # 蛇身颜色
RED = (255, 50, 50)          # 食物颜色
GRID_LINE = (30, 30, 30)     # 网格线颜色（可选装饰）

# ======================== 蛇的初始化 ========================
# 蛇身是一个列表，每个元素是一个坐标列表 [x, y]
# 列表第一个元素是蛇头，最后一个元素是蛇尾
snake = [[400, 300],    # 蛇头
         [380, 300],    # 身体第一节
         [360, 300]]    # 蛇尾

# 方向变量：dx 控制水平移动，dy 控制垂直移动
# 初始方向：向右（dx=20, dy=0）
dx = GRID_SIZE
dy = 0

# ======================== 食物相关 ========================
def generate_food(snake_body):
    """
    随机生成一个不与蛇身重叠的食物位置
    参数 snake_body: 蛇身列表
    返回: [x, y] 食物坐标
    """
    # 计算可用的格子范围
    max_col = (WIDTH // GRID_SIZE) - 1   # 最大列索引 (39)
    max_row = (HEIGHT // GRID_SIZE) - 1  # 最大行索引 (29)

    while True:
        # 随机生成格子坐标，乘以GRID_SIZE对齐到格子上
        fx = random.randint(0, max_col) * GRID_SIZE
        fy = random.randint(0, max_row) * GRID_SIZE
        food_pos = [fx, fy]

        # 确保食物不与蛇身的任何一节重叠
        if food_pos not in snake_body:
            return food_pos

# 生成第一个食物
food = generate_food(snake)

# ======================== 游戏主循环 ========================
running = True
while running:
    # ---------- ① 事件处理 ----------
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.KEYDOWN:
            # 上箭头：向上移动
            # 注意：dy == 0 防止在上下移动时直接反向
            if event.key == pygame.K_UP and dy == 0:
                dx = 0
                dy = -GRID_SIZE
            # 下箭头：向下移动
            elif event.key == pygame.K_DOWN and dy == 0:
                dx = 0
                dy = GRID_SIZE
            # 左箭头：向左移动
            elif event.key == pygame.K_LEFT and dx == 0:
                dx = -GRID_SIZE
                dy = 0
            # 右箭头：向右移动
            elif event.key == pygame.K_RIGHT and dx == 0:
                dx = GRID_SIZE
                dy = 0

    # ---------- ② 蛇的移动逻辑 ----------
    # 计算新蛇头的位置：当前蛇头坐标 + 方向偏移
    new_head = [snake[0][0] + dx, snake[0][1] + dy]

    # 把新蛇头插入到列表最前面
    snake.insert(0, new_head)

    # 检查蛇头是否吃到食物
    if snake[0] == food:
        # 吃到了！生成新食物（不执行pop，蛇自然变长）
        food = generate_food(snake)
    else:
        # 没吃到食物，删除蛇尾（保持蛇的长度不变）
        snake.pop()

    # ---------- ③ 绘制画面 ----------
    # 清屏（黑色背景）
    screen.fill(BLACK)

    # （可选）绘制网格背景，让格子更明显
    for x in range(0, WIDTH, GRID_SIZE):
        pygame.draw.line(screen, GRID_LINE, (x, 0), (x, HEIGHT), 1)
    for y in range(0, HEIGHT, GRID_SIZE):
        pygame.draw.line(screen, GRID_LINE, (0, y), (WIDTH, y), 1)

    # 绘制食物（红色实心方块）
    pygame.draw.rect(screen, RED,
                     (food[0], food[1], GRID_SIZE, GRID_SIZE))

    # 绘制蛇身（逐节画出）
    for i, segment in enumerate(snake):
        # i == 0 是蛇头，用亮绿色；其余用深绿色
        color = GREEN if i == 0 else DARK_GREEN
        # 绘制一个实心方块
        pygame.draw.rect(screen, color,
                         (segment[0], segment[1], GRID_SIZE, GRID_SIZE))
        # 给每节加一个深色边框，让节与节之间区分更明显
        pygame.draw.rect(screen, (0, 100, 0),
                         (segment[0], segment[1], GRID_SIZE, GRID_SIZE), 1)

    # 刷新屏幕
    pygame.display.flip()

    # 控制游戏速度
    clock.tick(FPS)

# 退出游戏
pygame.quit()
