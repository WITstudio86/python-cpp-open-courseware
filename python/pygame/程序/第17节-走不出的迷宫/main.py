"""
第17节：走不出的迷宫
===================
一个基于网格的迷宫探索游戏。
- 使用方向键控制角色移动，每次移动一个格子
- 碰到墙壁无法前进，需要找到通往终点的路线
- 到达绿色目标点即为通关
- 按下 R 键可以重新开始游戏

适用学员：10-15岁，已学习 Pygame 基础绘图与事件处理。
"""

import pygame
import sys

# ==================== 初始化 Pygame ====================
pygame.init()

# ==================== 常量定义 ====================
TILE_SIZE = 40          # 每个格子的像素大小
COLS = 16               # 迷宫列数
ROWS = 12               # 迷宫行数
WIN_WIDTH = COLS * TILE_SIZE    # 窗口宽度 640
WIN_HEIGHT = ROWS * TILE_SIZE   # 窗口高度 480
FPS = 30                # 帧率

# 颜色定义
COLOR_BG = (245, 245, 220)          # 背景色（米白色）
COLOR_FLOOR = (255, 255, 240)       # 地板颜色（浅象牙白）
COLOR_GRID_LINE = (200, 200, 180)   # 网格线颜色
COLOR_WALL = (80, 80, 80)           # 墙壁主色（深灰色）
COLOR_WALL_HIGHLIGHT = (110, 110, 110)  # 墙壁高光
COLOR_WALL_SHADOW = (50, 50, 50)    # 墙壁阴影
COLOR_PLAYER = (255, 180, 50)       # 玩家主色（橙色）
COLOR_PLAYER_EYE = (40, 40, 40)     # 玩家眼睛颜色
COLOR_PLAYER_EYE_WHITE = (255, 255, 255)  # 眼白
COLOR_PLAYER_MOUTH = (40, 40, 40)   # 嘴的颜色
COLOR_GOAL = (50, 200, 80)           # 终点颜色（绿色）
COLOR_GOAL_GLOW = (100, 255, 130)   # 终点光晕
COLOR_TEXT = (60, 60, 60)           # 普通文字颜色
COLOR_HINT_TEXT = (120, 120, 120)   # 提示文字颜色
COLOR_OVERLAY = (0, 0, 0)           # 胜利遮罩底色
COLOR_WIN_TEXT = (255, 255, 100)    # 胜利文字颜色（金黄色）
COLOR_WIN_BG = (50, 50, 80)         # 胜利面板背景
COLOR_STEP_TEXT = (100, 100, 150)   # 步数文字颜色

# ==================== 迷宫数据 ====================
# 0 = 通路（可走）, 1 = 墙壁（不可走）, 2 = 终点（目标）
maze = [
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    [1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1],
    [1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1],
    [1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1],
    [1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1],
    [1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1],
    [1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1],
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 2, 1],  # 终点在 maze[10][14]
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
]

# ==================== 玩家状态 ====================
player_col = 1          # 玩家初始列坐标（网格坐标 x）
player_row = 1          # 玩家初始行坐标（网格坐标 y）
step_count = 0          # 步数计数器
game_won = False        # 是否已通关

# ==================== 创建窗口 ====================
screen = pygame.display.set_mode((WIN_WIDTH, WIN_HEIGHT))
pygame.display.set_caption("第17节：走不出的迷宫")
clock = pygame.time.Clock()

# 字体对象（使用系统默认字体）
font_large = pygame.font.Font(None, 48)       # 大号字体（胜利文字）
font_medium = pygame.font.Font(None, 36)      # 中号字体（面板标题）
font_small = pygame.font.Font(None, 24)       # 小号字体（提示文字、步数）


# ==================== 辅助函数 ====================

def can_move(col: int, row: int) -> bool:
    """检查玩家是否可以移动到指定的网格位置。

    参数:
        col: 目标列坐标（网格坐标）
        row: 目标行坐标（网格坐标）

    返回:
        bool: 如果可以移动返回 True，否则返回 False
    """
    # 边界检查：不能走出迷宫范围
    if col < 0 or col >= COLS or row < 0 or row >= ROWS:
        return False
    # 墙壁检查：1 是墙壁，不能通行
    if maze[row][col] == 1:
        return False
    return True


def draw_maze(surface: pygame.Surface) -> None:
    """绘制整个迷宫地图。

    遍历迷宫二维列表，根据每个格子的值绘制：
    - 1（墙壁）：深灰色矩形，带高光和阴影边
    - 0（通路）：浅色地板，带网格线
    - 2（终点）：绿色圆形标记，带脉冲光晕
    """
    for row in range(ROWS):
        for col in range(COLS):
            # 计算当前格子的像素位置（左上角）
            x = col * TILE_SIZE
            y = row * TILE_SIZE

            if maze[row][col] == 1:
                # --- 墙壁：深灰色矩形 ---
                # 主体
                pygame.draw.rect(surface, COLOR_WALL,
                                 (x + 1, y + 1, TILE_SIZE - 2, TILE_SIZE - 2))
                # 顶部和左侧高光（模拟立体感）
                pygame.draw.line(surface, COLOR_WALL_HIGHLIGHT,
                                 (x + 1, y + 1), (x + TILE_SIZE - 2, y + 1), 2)
                pygame.draw.line(surface, COLOR_WALL_HIGHLIGHT,
                                 (x + 1, y + 1), (x + 1, y + TILE_SIZE - 2), 2)
                # 底部和右侧阴影
                pygame.draw.line(surface, COLOR_WALL_SHADOW,
                                 (x + 1, y + TILE_SIZE - 2),
                                 (x + TILE_SIZE - 2, y + TILE_SIZE - 2), 2)
                pygame.draw.line(surface, COLOR_WALL_SHADOW,
                                 (x + TILE_SIZE - 2, y + 1),
                                 (x + TILE_SIZE - 2, y + TILE_SIZE - 2), 2)
            else:
                # --- 地板：浅色背景 ---
                pygame.draw.rect(surface, COLOR_FLOOR,
                                 (x, y, TILE_SIZE, TILE_SIZE))
                # 网格线（细线，帮助看清格子边界）
                pygame.draw.rect(surface, COLOR_GRID_LINE,
                                 (x, y, TILE_SIZE, TILE_SIZE), 1)

                # --- 终点标记：绿色圆形 ---
                if maze[row][col] == 2:
                    center_x = x + TILE_SIZE // 2
                    center_y = y + TILE_SIZE // 2
                    # 外圈光晕（较大半透明效果 - 用描边实现脉冲感）
                    pulse = (pygame.time.get_ticks() // 500) % 2  # 每半秒切换一次
                    glow_radius = TILE_SIZE // 2 - 2 if pulse == 0 else TILE_SIZE // 2 - 4
                    pygame.draw.circle(surface, COLOR_GOAL_GLOW,
                                       (center_x, center_y), glow_radius, 2)
                    # 主体绿色圆形
                    pygame.draw.circle(surface, COLOR_GOAL,
                                       (center_x, center_y), TILE_SIZE // 2 - 6)
                    # 中心小白点
                    pygame.draw.circle(surface, (255, 255, 255),
                                       (center_x, center_y), 3)


def draw_player(surface: pygame.Surface, col: int, row: int) -> None:
    """在指定网格位置绘制玩家角色。

    玩家是一个可爱的圆形角色，包含：
    - 橙色圆形身体
    - 两只白色眼眶 + 黑色眼珠
    - 微笑的嘴巴（弧线）

    参数:
        col: 玩家的列坐标（网格坐标）
        row: 玩家的行坐标（网格坐标）
    """
    # 计算玩家圆心的像素位置
    center_x = col * TILE_SIZE + TILE_SIZE // 2
    center_y = row * TILE_SIZE + TILE_SIZE // 2
    radius = TILE_SIZE // 2 - 4  # 身体半径

    # --- 身体（橙色圆形） ---
    pygame.draw.circle(surface, COLOR_PLAYER, (center_x, center_y), radius)
    # 身体描边
    pygame.draw.circle(surface, (200, 130, 20), (center_x, center_y), radius, 2)

    # --- 眼睛 ---
    eye_offset_x = radius // 2        # 眼睛水平偏移
    eye_offset_y = radius // 3        # 眼睛垂直偏移（向上）
    eye_white_r = radius // 3         # 眼白半径
    eye_pupil_r = radius // 6         # 瞳孔半径

    # 左眼
    left_eye_x = center_x - eye_offset_x
    left_eye_y = center_y - eye_offset_y
    pygame.draw.circle(surface, COLOR_PLAYER_EYE_WHITE,
                       (left_eye_x, left_eye_y), eye_white_r)
    pygame.draw.circle(surface, COLOR_PLAYER_EYE,
                       (left_eye_x, left_eye_y), eye_pupil_r)

    # 右眼
    right_eye_x = center_x + eye_offset_x
    right_eye_y = center_y - eye_offset_y
    pygame.draw.circle(surface, COLOR_PLAYER_EYE_WHITE,
                       (right_eye_x, right_eye_y), eye_white_r)
    pygame.draw.circle(surface, COLOR_PLAYER_EYE,
                       (right_eye_x, right_eye_y), eye_pupil_r)

    # --- 嘴巴（微笑弧线） ---
    # 使用 arc 绘制一个向下的弧线表示微笑
    mouth_rect = pygame.Rect(
        center_x - radius // 2,
        center_y - radius // 4,
        radius,
        radius // 2
    )
    # arc 参数：surface, color, rect, start_angle, end_angle, width
    # 从 π/6 到 5π/6 画弧线（下半圆的一部分）
    import math
    pygame.draw.arc(surface, COLOR_PLAYER_MOUTH, mouth_rect,
                    math.pi / 6, 5 * math.pi / 6, 2)


def draw_step_counter(surface: pygame.Surface) -> None:
    """在屏幕角落绘制步数计数器。"""
    text = f"步数: {step_count}"
    step_surf = font_small.render(text, True, COLOR_STEP_TEXT)
    surface.blit(step_surf, (10, WIN_HEIGHT - 28))


def draw_hints(surface: pygame.Surface) -> None:
    """在屏幕底部中央绘制操作提示。"""
    hint_text = "方向键移动 | R 重新开始"
    hint_surf = font_small.render(hint_text, True, COLOR_HINT_TEXT)
    hint_rect = hint_surf.get_rect(center=(WIN_WIDTH // 2, WIN_HEIGHT - 16))
    surface.blit(hint_surf, hint_rect)


def draw_win_screen(surface: pygame.Surface) -> None:
    """绘制通关胜利画面。

    显示半透明遮罩层 + 中央面板 + 恭喜文字 + 步数统计 + 重新开始提示。
    """
    # --- 半透明遮罩（覆盖整个窗口） ---
    overlay = pygame.Surface((WIN_WIDTH, WIN_HEIGHT))
    overlay.set_alpha(180)  # 透明度 180/255
    overlay.fill(COLOR_OVERLAY)
    surface.blit(overlay, (0, 0))

    # --- 中央面板 ---
    panel_width = 360
    panel_height = 220
    panel_x = (WIN_WIDTH - panel_width) // 2
    panel_y = (WIN_HEIGHT - panel_height) // 2
    # 面板背景
    pygame.draw.rect(surface, COLOR_WIN_BG,
                     (panel_x, panel_y, panel_width, panel_height),
                     border_radius=15)
    # 面板边框
    pygame.draw.rect(surface, COLOR_WIN_TEXT,
                     (panel_x, panel_y, panel_width, panel_height),
                     3, border_radius=15)

    # --- "恭喜通关！" 大标题 ---
    win_surf = font_large.render("恭喜通关！", True, COLOR_WIN_TEXT)
    win_rect = win_surf.get_rect(
        center=(WIN_WIDTH // 2, panel_y + 50)
    )
    surface.blit(win_surf, win_rect)

    # --- 步数统计 ---
    steps_surf = font_medium.render(
        f"你用了 {step_count} 步走出了迷宫！", True, (220, 220, 220)
    )
    steps_rect = steps_surf.get_rect(
        center=(WIN_WIDTH // 2, panel_y + 100)
    )
    surface.blit(steps_surf, steps_rect)

    # --- 重新开始提示 ---
    restart_surf = font_small.render(
        "按 R 键重新挑战", True, (180, 180, 200)
    )
    restart_rect = restart_surf.get_rect(
        center=(WIN_WIDTH // 2, panel_y + 150)
    )
    surface.blit(restart_surf, restart_rect)

    # --- 装饰：面板两侧画小星星 ---
    star_color = (255, 255, 200)
    for offset_x in [-1, 1]:
        star_x = WIN_WIDTH // 2 + offset_x * 130
        star_y = panel_y + 55
        # 用一个小菱形图案代替星星
        pts = [
            (star_x, star_y - 8),
            (star_x + 5, star_y),
            (star_x, star_y + 8),
            (star_x - 5, star_y),
        ]
        pygame.draw.polygon(surface, star_color, pts)


def reset_game() -> None:
    """重置游戏状态，玩家回到起点，步数归零。"""
    global player_col, player_row, step_count, game_won
    player_col = 1
    player_row = 1
    step_count = 0
    game_won = False


def handle_movement(key: int) -> None:
    """处理玩家的移动输入。

    根据按下的方向键，检查目标格子是否可以通行。
    如果可以通行，更新玩家坐标并增加步数。
    如果到达终点格子，设置 game_won = True。

    参数:
        key: pygame 按键常量 (pygame.K_UP / K_DOWN / K_LEFT / K_RIGHT)
    """
    global player_col, player_row, step_count, game_won

    new_col = player_col
    new_row = player_row

    # 根据按键方向计算目标网格坐标
    if key == pygame.K_UP:
        new_row -= 1
    elif key == pygame.K_DOWN:
        new_row += 1
    elif key == pygame.K_LEFT:
        new_col -= 1
    elif key == pygame.K_RIGHT:
        new_col += 1

    # 检查目标位置是否可以通行
    if can_move(new_col, new_row):
        # 【音效位置】播放移动音效
        player_col = new_col
        player_row = new_row
        step_count += 1

        # 检查是否到达终点
        if maze[player_row][player_col] == 2:
            game_won = True
            # 【音效位置】播放胜利音效


# ==================== 主游戏循环 ====================
def main() -> None:
    """主函数：运行游戏。"""
    global game_won  # 需要在函数内修改 game_won

    running = True
    while running:
        # --- 事件处理 ---
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

            elif event.type == pygame.KEYDOWN:
                # 如果游戏已通关，只响应 R 键（重新开始）
                if game_won:
                    if event.key == pygame.K_r:
                        reset_game()
                    # 通关后忽略其他按键
                    continue

                # 方向键移动
                if event.key in (pygame.K_UP, pygame.K_DOWN,
                                 pygame.K_LEFT, pygame.K_RIGHT):
                    handle_movement(event.key)

                # 任何时候都可以按 R 重新开始
                elif event.key == pygame.K_r:
                    reset_game()

        # --- 画面绘制 ---
        screen.fill(COLOR_BG)           # 填充背景色
        draw_maze(screen)               # 绘制迷宫
        draw_player(screen, player_col, player_row)  # 绘制玩家
        draw_step_counter(screen)       # 绘制步数
        draw_hints(screen)              # 绘制操作提示

        # 如果通关，绘制胜利画面
        if game_won:
            draw_win_screen(screen)

        # --- 刷新屏幕 ---
        pygame.display.flip()
        clock.tick(FPS)

    # --- 退出游戏 ---
    pygame.quit()
    sys.exit()


# ==================== 程序入口 ====================
if __name__ == "__main__":
    main()
