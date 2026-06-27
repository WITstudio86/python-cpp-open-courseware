"""
接苹果游戏 — Pygame 入门示例
=============================
苹果（红色圆形）从屏幕顶部随机位置落下，
玩家用左右方向键移动篮子（棕色矩形）去接苹果。
接到苹果得 10 分，漏接的苹果会重新从顶部生成。
"""

import pygame
import random
import sys

# ============================================================
# 1. 初始化 Pygame
# ============================================================
pygame.init()

# ============================================================
# 2. 常量定义
# ============================================================
SCREEN_WIDTH = 800          # 窗口宽度
SCREEN_HEIGHT = 600         # 窗口高度
BACKGROUND_COLOR = (173, 216, 230)  # 浅蓝色背景 (lightblue)
FPS = 60                    # 帧率

# 苹果相关常量
APPLE_RADIUS = 20           # 苹果半径
APPLE_COLOR = (255, 0, 0)   # 苹果颜色：红色
APPLE_SPEED = 3             # 苹果下落速度（像素/帧）

# 篮子相关常量
BASKET_WIDTH = 100          # 篮子宽度
BASKET_HEIGHT = 20          # 篮子高度
BASKET_COLOR = (139, 69, 19)  # 篮子颜色：棕色
BASKET_SPEED = 8            # 篮子移动速度（像素/帧）

# ============================================================
# 3. 创建游戏窗口和时钟
# ============================================================
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("接苹果游戏")  # 设置窗口标题
clock = pygame.time.Clock()               # 用于控制帧率

# ============================================================
# 4. 初始化游戏变量
# ============================================================
score = 0  # 玩家得分

# ---- 初始化苹果位置 ----
# 苹果的 x 坐标：在屏幕宽度范围内随机，但要留有苹果半径的边距
apple_x = random.randint(APPLE_RADIUS, SCREEN_WIDTH - APPLE_RADIUS)
# 苹果的 y 坐标：从屏幕顶部开始（可以是负值，也可以从 0 开始）
apple_y = random.randint(-SCREEN_HEIGHT // 2, 0)

# ---- 初始化篮子位置 ----
# 篮子初始在屏幕底部中央
basket_x = SCREEN_WIDTH // 2 - BASKET_WIDTH // 2
basket_y = SCREEN_HEIGHT - BASKET_HEIGHT - 10  # 距离底部 10 像素

# ---- 定方向键状态（用于连续移动） ----
left_pressed = False   # 左方向键是否按下
right_pressed = False  # 右方向键是否按下

# ============================================================
# 5. 文字渲染函数（用于显示分数）
# ============================================================
def draw_text(text, font_size, color, x, y):
    """
    在屏幕上绘制文字。
    :param text: 要显示的文字内容
    :param font_size: 字体大小
    :param color: 文字颜色
    :param x: 文字左上角的 x 坐标
    :param y: 文字左上角的 y 坐标
    """
    # 使用系统默认中文字体以支持中文
    font = pygame.font.SysFont("simhei", font_size)
    text_surface = font.render(text, True, color)
    screen.blit(text_surface, (x, y))


# ============================================================
# 6. 苹果重置函数
# ============================================================
def reset_apple():
    """
    将苹果重新放置到屏幕顶部随机位置。
    返回新的 (apple_x, apple_y)。
    """
    new_x = random.randint(APPLE_RADIUS, SCREEN_WIDTH - APPLE_RADIUS)
    # y 坐标从屏幕上方随机位置开始，制造错落的掉落节奏
    new_y = random.randint(-200, -APPLE_RADIUS)
    return new_x, new_y


# ============================================================
# 7. 碰撞检测函数
# ============================================================
def check_collision(apple_x, apple_y, basket_rect):
    """
    检测苹果和篮子是否发生碰撞。
    将苹果视作一个正方形（外接矩形）与篮子的矩形做碰撞检测。
    :param apple_x: 苹果圆心 x 坐标
    :param apple_y: 苹果圆心 y 坐标
    :param basket_rect: 篮子的 pygame.Rect 对象
    :return: True 表示碰撞，False 表示未碰撞
    """
    # 创建一个代表苹果外接正方形的 Rect
    # 左上角坐标 = (圆心x - 半径, 圆心y - 半径)，边长 = 直径
    apple_rect = pygame.Rect(
        apple_x - APPLE_RADIUS,
        apple_y - APPLE_RADIUS,
        APPLE_RADIUS * 2,
        APPLE_RADIUS * 2
    )
    # 使用 colliderect 判断两个矩形是否相交
    return apple_rect.colliderect(basket_rect)


# ============================================================
# 8. 游戏主循环
# ============================================================
running = True  # 控制主循环是否继续

while running:
    # --------------------------------------------------------
    # 8.1 事件处理（键盘输入、窗口关闭等）
    # --------------------------------------------------------
    for event in pygame.event.get():
        # 关闭窗口事件
        if event.type == pygame.QUIT:
            running = False  # 退出主循环，结束游戏

        # ---- 方向键按下事件 ----
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_LEFT:
                left_pressed = True  # 标记左键为按下状态
            elif event.key == pygame.K_RIGHT:
                right_pressed = True  # 标记右键为按下状态

        # ---- 方向键松开事件 ----
        elif event.type == pygame.KEYUP:
            if event.key == pygame.K_LEFT:
                left_pressed = False  # 取消左键按下状态
            elif event.key == pygame.K_RIGHT:
                right_pressed = False  # 取消右键按下状态

    # --------------------------------------------------------
    # 8.2 更新游戏状态
    # --------------------------------------------------------

    # ---- 更新篮子位置（根据方向键状态） ----
    if left_pressed:
        basket_x -= BASKET_SPEED  # 篮子向左移动
    if right_pressed:
        basket_x += BASKET_SPEED  # 篮子向右移动

    # ---- 限制篮子不超出窗口边界 ----
    if basket_x < 0:
        basket_x = 0
    if basket_x > SCREEN_WIDTH - BASKET_WIDTH:
        basket_x = SCREEN_WIDTH - BASKET_WIDTH

    # ---- 更新苹果位置（向下掉落） ----
    apple_y += APPLE_SPEED  # 每帧下落 3 像素

    # ---- 构建篮子的 Rect 对象（用于碰撞检测） ----
    basket_rect = pygame.Rect(basket_x, basket_y, BASKET_WIDTH, BASKET_HEIGHT)

    # ---- 碰撞检测：苹果是否碰到篮子 ----
    if check_collision(apple_x, apple_y, basket_rect):
        score += 10                        # 得分 +10
        apple_x, apple_y = reset_apple()   # 苹果重新生成在顶部

    # ---- 边界检测：苹果是否掉出屏幕底部 ----
    if apple_y > SCREEN_HEIGHT + APPLE_RADIUS:
        # 苹果完全掉出屏幕，且未被接到，重新生成
        apple_x, apple_y = reset_apple()

    # --------------------------------------------------------
    # 8.3 绘制画面
    # --------------------------------------------------------
    # 填充背景颜色（浅蓝色）
    screen.fill(BACKGROUND_COLOR)

    # ---- 绘制苹果（红色圆形） ----
    pygame.draw.circle(screen, APPLE_COLOR, (apple_x, apple_y), APPLE_RADIUS)

    # ---- 绘制篮子（棕色矩形） ----
    pygame.draw.rect(screen, BASKET_COLOR, basket_rect)

    # ---- 绘制分数（左上角显示） ----
    draw_text(f"得分：{score}", 36, (0, 0, 0), 10, 10)

    # 更新整个屏幕显示
    pygame.display.flip()

    # ---- 控制帧率 ----
    clock.tick(FPS)

# ============================================================
# 9. 退出游戏
# ============================================================
pygame.quit()  # 卸载 Pygame 模块
sys.exit()     # 退出程序
