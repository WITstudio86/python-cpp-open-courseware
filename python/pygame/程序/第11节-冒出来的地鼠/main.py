"""
第11节：冒出来的地鼠 — 打地鼠游戏
知识点：Rect网格布局（3x3九宫格）、自定义事件USEREVENT、
        set_timer定时器、collidepoint点击检测
"""

import pygame
import random

# ==================== 初始化 Pygame ====================
pygame.init()
WIDTH, HEIGHT = 800, 600
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("冒出来的地鼠 - 第11节")
clock = pygame.time.Clock()

# ==================== 颜色定义 ====================
COLOR_SKY_BLUE = (135, 206, 235)     # 天空蓝
COLOR_GRASS_GREEN = (34, 139, 34)    # 草地绿
COLOR_HOLE_DARK = (60, 35, 15)       # 洞口深棕色
COLOR_HOLE_RIM = (120, 80, 40)       # 洞口边框
COLOR_MOLE_BODY = (139, 90, 43)      # 地鼠身体棕色
COLOR_MOLE_DARK = (100, 65, 30)      # 地鼠深色
COLOR_WHITE = (255, 255, 255)
COLOR_BLACK = (0, 0, 0)
COLOR_PINK = (255, 182, 193)         # 鼻子粉色
COLOR_YELLOW = (255, 255, 0)
COLOR_RED = (255, 60, 60)
COLOR_DIRT = (160, 120, 80)          # 泥土色

# ==================== 九宫格布局参数 ====================
GRID_COLS = 3          # 列数
GRID_ROWS = 3          # 行数
HOLE_WIDTH = 140       # 洞口宽度
HOLE_HEIGHT = 120      # 洞口高度
MARGIN_LEFT = 100      # 左边留白
MARGIN_TOP = 140       # 上边留白（给标题和分数留空间）
COL_SPACING = 200      # 列间距（洞中心之间的距离）
ROW_SPACING = 150      # 行间距（洞中心之间的距离）

# ==================== 生成 9 个洞口的 Rect 列表 ====================
holes = []  # 存储每个洞的 Rect 对象
for row in range(GRID_ROWS):
    for col in range(GRID_COLS):
        # 计算洞的中心坐标
        cx = MARGIN_LEFT + col * COL_SPACING + HOLE_WIDTH // 2
        cy = MARGIN_TOP + row * ROW_SPACING + HOLE_HEIGHT // 2
        # 创建 Rect 并以中心点定位
        hole_rect = pygame.Rect(0, 0, HOLE_WIDTH, HOLE_HEIGHT)
        hole_rect.center = (cx, cy)
        holes.append(hole_rect)

# ==================== 地鼠状态 ====================
current_mole = -1  # 当前有地鼠的洞的索引，-1 表示没有地鼠
mole_hit = False   # 地鼠是否刚被打中（用于显示被打效果）
hit_timer = 0      # 被打效果持续时间计数器

# ==================== 自定义事件：地鼠换洞 ====================
# USEREVENT 是 Pygame 预留的自定义事件起始编号，我们 +1 避免冲突
MOLE_CHANGE_EVENT = pygame.USEREVENT + 1
# 设置定时器：每隔 800 毫秒自动触发一次 MOLE_CHANGE_EVENT
pygame.time.set_timer(MOLE_CHANGE_EVENT, 800)


def spawn_mole():
    """随机选择一个洞口，让地鼠冒出来"""
    global current_mole, mole_hit
    current_mole = random.randint(0, 8)  # 0~8 随机选一个洞
    mole_hit = False  # 新地鼠出现，重置被打状态


def draw_title():
    """绘制顶部标题栏"""
    title_font = pygame.font.Font(None, 48)
    title_text = title_font.render("🐹 冒出来的地鼠", True, COLOR_YELLOW)
    title_rect = title_text.get_rect(center=(WIDTH // 2, 35))
    screen.blit(title_text, title_rect)

    # 提示文字
    hint_font = pygame.font.Font(None, 28)
    hint_text = hint_font.render("用鼠标点击冒出来的地鼠！", True, COLOR_WHITE)
    hint_rect = hint_text.get_rect(center=(WIDTH // 2, 80))
    screen.blit(hint_text, hint_rect)


def draw_hole(hole_rect):
    """绘制一个地鼠洞（椭圆形深坑）"""
    # 洞口阴影（稍大的深色椭圆）
    shadow_rect = hole_rect.inflate(16, 10)
    pygame.draw.ellipse(screen, COLOR_HOLE_DARK, shadow_rect)
    # 洞口主体
    pygame.draw.ellipse(screen, COLOR_HOLE_RIM, hole_rect)
    # 洞口内部（更深的颜色，模拟洞的深度）
    inner_rect = hole_rect.inflate(-20, -16)
    pygame.draw.ellipse(screen, (30, 18, 8), inner_rect)


def draw_mole(hole_rect):
    """在指定的洞口绘制地鼠"""
    # --- 地鼠身体（从洞里冒出来，所以底部对齐洞口底部）---
    body_width = HOLE_WIDTH - 30
    body_height = HOLE_HEIGHT - 10

    body_rect = pygame.Rect(0, 0, body_width, body_height)
    body_rect.centerx = hole_rect.centerx
    body_rect.bottom = hole_rect.bottom - 5

    # 根据是否被打中来决定地鼠的颜色
    if mole_hit:
        body_color = COLOR_RED  # 被打中时变红
    else:
        body_color = COLOR_MOLE_BODY

    pygame.draw.ellipse(screen, body_color, body_rect)
    # 身体轮廓线
    pygame.draw.ellipse(screen, COLOR_MOLE_DARK, body_rect, 2)

    # --- 地鼠的耳朵（两个小半圆）---
    ear_w, ear_h = 20, 18
    # 左耳
    left_ear = pygame.Rect(0, 0, ear_w, ear_h)
    left_ear.centerx = body_rect.centerx - 22
    left_ear.bottom = body_rect.top + 15
    pygame.draw.ellipse(screen, body_color, left_ear)
    pygame.draw.ellipse(screen, COLOR_MOLE_DARK, left_ear, 2)
    # 右耳
    right_ear = pygame.Rect(0, 0, ear_w, ear_h)
    right_ear.centerx = body_rect.centerx + 22
    right_ear.bottom = body_rect.top + 15
    pygame.draw.ellipse(screen, body_color, right_ear)
    pygame.draw.ellipse(screen, COLOR_MOLE_DARK, right_ear, 2)

    # --- 地鼠的眼睛 ---
    eye_r = 9  # 眼睛半径
    left_eye_center = (body_rect.centerx - 14, body_rect.centery - 8)
    right_eye_center = (body_rect.centerx + 14, body_rect.centery - 8)

    if mole_hit:
        # 被打中时显示 X_X 眼睛
        x_offset = 5
        pygame.draw.line(screen, COLOR_BLACK,
                         (left_eye_center[0] - x_offset, left_eye_center[1] - x_offset),
                         (left_eye_center[0] + x_offset, left_eye_center[1] + x_offset), 3)
        pygame.draw.line(screen, COLOR_BLACK,
                         (left_eye_center[0] - x_offset, left_eye_center[1] + x_offset),
                         (left_eye_center[0] + x_offset, left_eye_center[1] - x_offset), 3)
        pygame.draw.line(screen, COLOR_BLACK,
                         (right_eye_center[0] - x_offset, right_eye_center[1] - x_offset),
                         (right_eye_center[0] + x_offset, right_eye_center[1] + x_offset), 3)
        pygame.draw.line(screen, COLOR_BLACK,
                         (right_eye_center[0] - x_offset, right_eye_center[1] + x_offset),
                         (right_eye_center[0] + x_offset, right_eye_center[1] - x_offset), 3)
    else:
        # 正常状态：白色眼球 + 黑色眼珠
        pygame.draw.circle(screen, COLOR_WHITE, left_eye_center, eye_r)
        pygame.draw.circle(screen, COLOR_WHITE, right_eye_center, eye_r)
        pygame.draw.circle(screen, COLOR_BLACK, left_eye_center, eye_r // 2)
        pygame.draw.circle(screen, COLOR_BLACK, right_eye_center, eye_r // 2)

    # --- 地鼠的鼻子（粉色小椭圆）---
    nose_center = (body_rect.centerx, body_rect.centery + 10)
    nose_rect = pygame.Rect(0, 0, 14, 10)
    nose_rect.center = nose_center
    pygame.draw.ellipse(screen, COLOR_PINK, nose_rect)

    # --- 地鼠的胡须 ---
    whisker_y = nose_center[1]
    whisker_color = (80, 50, 30)
    # 左边胡须
    pygame.draw.line(screen, whisker_color,
                     (nose_center[0] - 7, whisker_y),
                     (nose_center[0] - 28, whisker_y - 5), 1)
    pygame.draw.line(screen, whisker_color,
                     (nose_center[0] - 7, whisker_y),
                     (nose_center[0] - 28, whisker_y + 5), 1)
    # 右边胡须
    pygame.draw.line(screen, whisker_color,
                     (nose_center[0] + 7, whisker_y),
                     (nose_center[0] + 28, whisker_y - 5), 1)
    pygame.draw.line(screen, whisker_color,
                     (nose_center[0] + 7, whisker_y),
                     (nose_center[0] + 28, whisker_y + 5), 1)

    # --- 地鼠的牙齿（两个小白方块）---
    tooth_w, tooth_h = 7, 9
    left_tooth = pygame.Rect(0, 0, tooth_w, tooth_h)
    left_tooth.centerx = nose_center[0] - 5
    left_tooth.top = nose_center[1] + 5
    pygame.draw.rect(screen, COLOR_WHITE, left_tooth)
    pygame.draw.rect(screen, (200, 200, 200), left_tooth, 1)

    right_tooth = pygame.Rect(0, 0, tooth_w, tooth_h)
    right_tooth.centerx = nose_center[0] + 5
    right_tooth.top = nose_center[1] + 5
    pygame.draw.rect(screen, COLOR_WHITE, right_tooth)
    pygame.draw.rect(screen, (200, 200, 200), right_tooth, 1)


def draw_hit_effect(pos):
    """在鼠标点击位置绘制一个打中效果（爆炸星形）"""
    x, y = pos
    # 绘制放射状线条
    for angle in range(0, 360, 45):
        import math
        rad = math.radians(angle)
        end_x = x + math.cos(rad) * 30
        end_y = y + math.sin(rad) * 30
        pygame.draw.line(screen, COLOR_YELLOW, (x, y), (end_x, end_y), 3)
    # 中心圆
    pygame.draw.circle(screen, COLOR_RED, (x, y), 8)


# ==================== 游戏启动：让第一只地鼠出现 ====================
spawn_mole()

# ==================== 主循环 ====================
running = True
hit_effect_pos = None  # 打中效果的位置
hit_effect_timer = 0   # 打中效果持续帧数

while running:
    # --- 事件处理 ---
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        # 自定义事件：地鼠换洞
        elif event.type == MOLE_CHANGE_EVENT:
            spawn_mole()

        # 鼠标点击事件：检测是否打中了地鼠
        elif event.type == pygame.MOUSEBUTTONDOWN:
            mouse_x, mouse_y = event.pos

            # 检查是否点中了当前有地鼠的洞
            if current_mole != -1:
                mole_rect = holes[current_mole]
                if mole_rect.collidepoint(mouse_x, mouse_y):
                    # 🎯 打中地鼠！
                    print(f"打中啦！洞号: {current_mole}")
                    mole_hit = True         # 地鼠变红、变表情
                    hit_timer = 15          # 被打效果持续 15 帧
                    hit_effect_pos = event.pos  # 记录打中位置
                    hit_effect_timer = 15

                    # 注意：这里不把 current_mole 设为 -1，
                    # 让玩家看到地鼠被打的"惨状"一小会儿
                    # 地鼠会在 hit_timer 倒计时结束后或下次换洞时消失

                else:
                    # 点到了洞之外的地方，或者点错了洞
                    print("没打中！")

    # --- 更新逻辑 ---
    # 被打效果计时器倒计时
    if hit_timer > 0:
        hit_timer -= 1
        if hit_timer == 0:
            # 效果结束，地鼠消失
            current_mole = -1
            mole_hit = False

    if hit_effect_timer > 0:
        hit_effect_timer -= 1

    # --- 绘制画面 ---
    # 天空背景（渐变效果：上浅下深）
    for i in range(HEIGHT):
        ratio = i / HEIGHT
        r = int(135 * (1 - ratio) + 34 * ratio)
        g = int(206 * (1 - ratio) + 139 * ratio)
        b = int(235 * (1 - ratio) + 34 * ratio)
        pygame.draw.line(screen, (r, g, b), (0, i), (WIDTH, i))

    # 地面区域（下半部分）
    ground_rect = pygame.Rect(0, MARGIN_TOP - 30, WIDTH, HEIGHT - MARGIN_TOP + 30)
    pygame.draw.rect(screen, COLOR_GRASS_GREEN, ground_rect)

    # 绘制装饰性草地纹理
    for i in range(0, WIDTH, 25):
        grass_h = random.randint(8, 18)
        grass_x = i + random.randint(-5, 5)
        grass_y = MARGIN_TOP - 30 + random.randint(-3, 3)
        pygame.draw.line(screen, (50, 160, 50), (grass_x, grass_y),
                         (grass_x + random.randint(-3, 3), grass_y - grass_h), 2)

    # 绘制标题
    draw_title()

    # 绘制所有 9 个洞口
    for i, hole_rect in enumerate(holes):
        draw_hole(hole_rect)

        # 如果这个洞当前有地鼠，绘制地鼠
        if i == current_mole:
            draw_mole(hole_rect)

    # 绘制打中效果
    if hit_effect_timer > 0 and hit_effect_pos:
        draw_hit_effect(hit_effect_pos)

    # 更新屏幕
    pygame.display.flip()
    clock.tick(60)  # 每秒 60 帧

pygame.quit()
