"""
第42节：关卡系统 —— 多关卡推箱子
==============================================
本程序在第41节单关卡推箱子的基础上，添加了：
1. 多关卡系统（3个不同难度的关卡）
2. 选关界面（点击关卡按钮进入对应关卡）
3. 步数统计（每个关卡独立计步）
4. 通关检测（所有目标点都有箱子）
5. 通关动画（目标点闪烁绿色）
6. 按 N 键进入下一关
7. 撤销功能（U 键）
8. 重新开始（R 键）
9. 按 ESC 回到选关界面

所有图形均使用 pygame.Surface + pygame.draw 绘制，不依赖外部图片文件。

地图数字含义：
    0 = 地板    1 = 墙      2 = 目标点
    3 = 箱子    4 = 玩家    5 = 箱子在目标点上
"""

import pygame
import sys

# ============================================
# 1. 初始化 Pygame
# ============================================
pygame.init()

# ============================================
# 2. 窗口与常量设置
# ============================================
CELL = 64              # 每个格子的大小（像素）
GRID = 10              # 地图网格大小（10x10）
SCREEN_SIZE = GRID * CELL  # 窗口大小：640x640

screen = pygame.display.set_mode((SCREEN_SIZE, SCREEN_SIZE))
pygame.display.set_caption("第42节：关卡系统 —— 多关卡推箱子")

# 字体
font_title = pygame.font.SysFont("simhei", 48)     # 标题
font_large = pygame.font.SysFont("simhei", 36)     # 大字
font_normal = pygame.font.SysFont("simhei", 24)    # 普通
font_small = pygame.font.SysFont("simhei", 18)     # 小字
font_button = pygame.font.SysFont("simhei", 28)    # 按钮

clock = pygame.time.Clock()
FPS = 60

# ============================================
# 3. 颜色定义
# ============================================
COLOR_BLACK      = (0, 0, 0)
COLOR_WHITE      = (255, 255, 255)
COLOR_FLOOR      = (220, 210, 190)   # 地板：米色
COLOR_WALL       = (80, 80, 100)     # 墙：深灰蓝
COLOR_WALL_BORDER = (60, 60, 80)     # 墙边框
COLOR_TARGET     = (255, 60, 60)     # 目标点：红色
COLOR_TARGET_WIN = (50, 255, 50)     # 目标点通关：绿色
COLOR_BOX        = (200, 140, 60)    # 箱子：橙色
COLOR_BOX_ON     = (50, 200, 50)     # 箱子到位：绿色
COLOR_PLAYER     = (50, 120, 255)    # 玩家：蓝色
COLOR_BG         = (25, 25, 45)      # 深蓝背景
COLOR_MENU_BG    = (30, 30, 55)      # 选关背景
COLOR_BTN_NORMAL = (80, 160, 80)     # 按钮普通：绿色
COLOR_BTN_HOVER  = (120, 220, 120)   # 按钮悬停：亮绿
COLOR_BTN_BORDER = (200, 255, 200)   # 按钮边框
COLOR_INFO_TEXT  = (220, 220, 220)   # 信息文字
COLOR_WIN_OVERLAY = (0, 0, 0, 150)   # 通关遮罩

# ============================================
# 4. 关卡数据（三维列表：levels[关卡][行][列]）
# ============================================
LEVELS = [
    # ====== 第1关：初入仓库（1个箱子，1个目标） ======
    [
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 0, 0, 0, 4, 0, 0, 0, 0, 1],   # 玩家在(4,4)
        [1, 0, 0, 0, 3, 0, 2, 0, 0, 1],   # 箱子在(5,4)，目标在(5,6)
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    ],
    # ====== 第2关：渐入佳境（2个箱子，2个目标） ======
    [
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 0, 1, 0, 0, 0, 0, 0, 0, 1],   # 内墙在(2,2)
        [1, 0, 0, 0, 4, 0, 0, 0, 0, 1],   # 玩家在(3,4)
        [1, 0, 0, 0, 0, 0, 0, 2, 0, 1],   # 目标1在(4,7)
        [1, 0, 3, 0, 1, 0, 0, 0, 0, 1],   # 箱子1在(5,2)，内墙在(5,4)
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 0, 2, 0, 0, 0, 3, 0, 0, 1],   # 目标2在(7,2)，箱子2在(7,6)
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    ],
    # ====== 第3关：仓库达人（3个箱子，3个目标） ======
    [
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 0, 1, 0, 1, 0, 0, 2, 0, 1],   # 内墙(2,2)(2,4)，目标1在(2,7)
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 0, 0, 4, 0, 3, 0, 0, 0, 1],   # 玩家在(4,3)，箱子1在(4,5)
        [1, 0, 0, 0, 0, 0, 1, 0, 0, 1],   # 内墙在(5,6)
        [1, 0, 2, 0, 0, 0, 0, 3, 0, 1],   # 目标2在(6,2)，箱子2在(6,7)
        [1, 0, 0, 0, 2, 0, 0, 0, 0, 1],   # 目标3在(7,4)
        [1, 0, 3, 0, 0, 0, 0, 0, 0, 1],   # 箱子3在(8,2)
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    ],
]

LEVEL_NAMES = ["第1关：初入仓库", "第2关：渐入佳境", "第3关：仓库达人"]
LEVEL_DIFFICULTY = ["★☆☆☆☆", "★★★☆☆", "★★★★★"]

# ============================================
# 5. 游戏状态
# ============================================
# 游戏状态机：menu / playing / win
game_state = "menu"

# 当前关卡索引
current_level = 0

# 每个关卡的步数记录和完成状态
level_steps = [0] * len(LEVELS)
level_completed = [False] * len(LEVELS)

# 当前关卡运行时数据
player_x, player_y = 0, 0         # 玩家位置
boxes = []                         # 箱子位置列表 [(x,y), ...]
targets = []                       # 目标点位置列表 [(x,y), ...]
static_grid = []                   # 静态地图（0=地板, 1=墙, 2=目标点）
steps = 0                          # 当前关卡步数
history = []                       # 撤销历史 [(px, py, boxes_copy), ...]

# 通关动画
win_start_time = 0
FLASH_INTERVAL = 200               # 闪烁间隔（毫秒）
WIN_ANIMATION_DURATION = 3000      # 通关动画总时长
show_win_text = False


# ============================================
# 6. 游戏素材生成（用 Surface 绘制）
# ============================================

def create_sprite_floor():
    """绘制地板素材：米色方块"""
    surf = pygame.Surface((CELL, CELL))
    surf.fill(COLOR_FLOOR)
    # 加一点纹理（细线边框）
    pygame.draw.rect(surf, (200, 190, 170), (0, 0, CELL, CELL), 1)
    return surf


def create_sprite_wall():
    """绘制墙壁素材：深灰蓝砖块"""
    surf = pygame.Surface((CELL, CELL))
    surf.fill(COLOR_WALL)
    # 砖块纹理
    pygame.draw.rect(surf, COLOR_WALL_BORDER, (0, 0, CELL, CELL), 2)
    # 水平砖缝
    pygame.draw.line(surf, COLOR_WALL_BORDER, (0, CELL // 2), (CELL, CELL // 2), 1)
    # 垂直砖缝（错开的）
    pygame.draw.line(surf, COLOR_WALL_BORDER, (CELL // 2, 0), (CELL // 2, CELL // 2), 1)
    pygame.draw.line(surf, COLOR_WALL_BORDER, (0, CELL // 2), (0, CELL), 1)
    pygame.draw.line(surf, COLOR_WALL_BORDER, (CELL, CELL // 2), (CELL, CELL), 1)
    return surf


def create_sprite_target():
    """绘制目标点素材：红色菱形（地板底色 + 红色标记）"""
    surf = pygame.Surface((CELL, CELL), pygame.SRCALPHA)
    surf.fill((0, 0, 0, 0))  # 透明背景
    surf.blit(create_sprite_floor(), (0, 0))
    # 红色菱形（旋转的正方形）
    cx, cy = CELL // 2, CELL // 2
    r = CELL // 4
    points = [
        (cx, cy - r), (cx + r, cy),
        (cx, cy + r), (cx - r, cy)
    ]
    pygame.draw.polygon(surf, COLOR_TARGET, points)
    pygame.draw.polygon(surf, (200, 30, 30), points, 1)
    return surf


def create_sprite_target_win():
    """绘制通关目标点素材：绿色菱形"""
    surf = pygame.Surface((CELL, CELL), pygame.SRCALPHA)
    surf.fill((0, 0, 0, 0))
    surf.blit(create_sprite_floor(), (0, 0))
    cx, cy = CELL // 2, CELL // 2
    r = CELL // 4
    points = [
        (cx, cy - r), (cx + r, cy),
        (cx, cy + r), (cx - r, cy)
    ]
    pygame.draw.polygon(surf, COLOR_TARGET_WIN, points)
    pygame.draw.polygon(surf, (30, 200, 30), points, 1)
    # 加一个白色对勾表示完成
    check_pts = [(cx - 8, cy), (cx - 3, cy + 6), (cx + 8, cy - 8)]
    pygame.draw.lines(surf, COLOR_WHITE, False, check_pts, 3)
    return surf


def create_sprite_box():
    """绘制箱子素材：橙色方块 + 十字带"""
    surf = pygame.Surface((CELL, CELL), pygame.SRCALPHA)
    surf.fill((0, 0, 0, 0))
    margin = 4
    rect = pygame.Rect(margin, margin, CELL - 2 * margin, CELL - 2 * margin)
    pygame.draw.rect(surf, COLOR_BOX, rect, border_radius=6)
    pygame.draw.rect(surf, (160, 100, 30), rect, 2, border_radius=6)
    # 十字带
    cx, cy = CELL // 2, CELL // 2
    half = CELL // 3
    pygame.draw.line(surf, (120, 70, 20), (cx - half, cy), (cx + half, cy), 3)
    pygame.draw.line(surf, (120, 70, 20), (cx, cy - half), (cx, cy + half), 3)
    return surf


def create_sprite_box_on_target():
    """绘制箱子到位素材：绿色方块 + 十字带"""
    surf = pygame.Surface((CELL, CELL), pygame.SRCALPHA)
    surf.fill((0, 0, 0, 0))
    margin = 4
    rect = pygame.Rect(margin, margin, CELL - 2 * margin, CELL - 2 * margin)
    pygame.draw.rect(surf, COLOR_BOX_ON, rect, border_radius=6)
    pygame.draw.rect(surf, (30, 160, 30), rect, 2, border_radius=6)
    cx, cy = CELL // 2, CELL // 2
    half = CELL // 3
    pygame.draw.line(surf, (30, 140, 30), (cx - half, cy), (cx + half, cy), 3)
    pygame.draw.line(surf, (30, 140, 30), (cx, cy - half), (cx, cy + half), 3)
    return surf


def create_sprite_player():
    """绘制玩家素材：蓝色小人（圆形身体 + 眼睛 + 微笑）"""
    surf = pygame.Surface((CELL, CELL), pygame.SRCALPHA)
    surf.fill((0, 0, 0, 0))
    cx, cy = CELL // 2, CELL // 2
    r = CELL // 2 - 6
    # 身体（蓝色圆）
    pygame.draw.circle(surf, COLOR_PLAYER, (cx, cy), r)
    pygame.draw.circle(surf, (30, 80, 200), (cx, cy), r, 2)
    # 眼睛（白色 + 黑色瞳孔）
    eye_offset = r // 3
    eye_r = r // 4
    # 左眼
    pygame.draw.circle(surf, COLOR_WHITE, (cx - eye_offset, cy - r // 4), eye_r)
    pygame.draw.circle(surf, COLOR_BLACK, (cx - eye_offset + 2, cy - r // 4), eye_r // 2)
    # 右眼
    pygame.draw.circle(surf, COLOR_WHITE, (cx + eye_offset, cy - r // 4), eye_r)
    pygame.draw.circle(surf, COLOR_BLACK, (cx + eye_offset + 2, cy - r // 4), eye_r // 2)
    # 微笑
    smile_rect = pygame.Rect(cx - r // 3, cy + r // 6, 2 * r // 3, r // 2)
    pygame.draw.arc(surf, COLOR_WHITE, smile_rect, 0.2, 3.0, 2)
    return surf


# 生成所有素材
spr_floor = create_sprite_floor()
spr_wall = create_sprite_wall()
spr_target = create_sprite_target()
spr_target_win = create_sprite_target_win()
spr_box = create_sprite_box()
spr_box_on = create_sprite_box_on_target()
spr_player = create_sprite_player()


# ============================================
# 7. 游戏逻辑函数
# ============================================

def load_level(level_index):
    """加载指定关卡：解析地图数据，初始化玩家和箱子"""
    global player_x, player_y, boxes, targets, static_grid, steps, history

    map_data = LEVELS[level_index]
    static_grid = []  # 只存 0=地板, 1=墙, 2=目标点
    boxes = []
    targets = []
    steps = 0
    history = []

    for row in range(GRID):
        static_row = []
        for col in range(GRID):
            cell = map_data[row][col]
            if cell == 1:          # 墙
                static_row.append(1)
            elif cell == 2:        # 目标点
                static_row.append(2)
                targets.append((col, row))
            elif cell == 3:        # 箱子
                static_row.append(0)
                boxes.append((col, row))
            elif cell == 4:        # 玩家
                static_row.append(0)
                player_x, player_y = col, row
            elif cell == 5:        # 箱子在目标点上
                static_row.append(2)
                boxes.append((col, row))
                targets.append((col, row))
            else:                  # 地板
                static_row.append(0)
        static_grid.append(static_row)


def move_player(dx, dy):
    """尝试移动玩家（包含推箱子逻辑）
    dx, dy: 移动方向（-1, 0, 1）
    返回 True 表示移动成功（步数+1）"""
    global player_x, player_y, boxes, steps, history

    new_x = player_x + dx
    new_y = player_y + dy

    # 边界检查
    if not (0 <= new_x < GRID and 0 <= new_y < GRID):
        return False

    # 撞墙检查
    if static_grid[new_y][new_x] == 1:
        return False

    # 保存当前状态用于撤销
    history.append((player_x, player_y, boxes.copy()))

    # 检查前方是否有箱子
    if (new_x, new_y) in boxes:
        # 尝试推箱子
        box_new_x = new_x + dx
        box_new_y = new_y + dy

        # 箱子不能推出界
        if not (0 <= box_new_x < GRID and 0 <= box_new_y < GRID):
            history.pop()  # 移动失败，回退历史
            return False

        # 箱子不能推到墙上
        if static_grid[box_new_y][box_new_x] == 1:
            history.pop()
            return False

        # 箱子不能推到另一个箱子上
        if (box_new_x, box_new_y) in boxes:
            history.pop()
            return False

        # 推箱子成功
        boxes.remove((new_x, new_y))
        boxes.append((box_new_x, box_new_y))
        player_x, player_y = new_x, new_y
        steps += 1
        return True

    # 没有箱子，直接移动
    player_x, player_y = new_x, new_y
    steps += 1
    return True


def undo_move():
    """撤销上一步操作"""
    global player_x, player_y, boxes, steps

    if len(history) == 0:
        return  # 没有可以撤销的操作

    prev_px, prev_py, prev_boxes = history.pop()
    player_x, player_y = prev_px, prev_py
    boxes = prev_boxes
    steps = max(0, steps - 1)


def check_win():
    """检查是否通关：所有目标点上都有箱子"""
    for tx, ty in targets:
        if (tx, ty) not in boxes:
            return False
    return True


def reset_level():
    """重新开始当前关卡"""
    load_level(current_level)


# ============================================
# 8. 选关界面按钮
# ============================================

def get_level_buttons():
    """生成选关界面的按钮矩形列表"""
    buttons = []
    btn_w, btn_h = 160, 90
    for i in range(len(LEVELS)):
        col = i % 3
        row = i // 3
        x = 80 + col * 200
        y = 220 + row * 140
        buttons.append(pygame.Rect(x, y, btn_w, btn_h))
    return buttons


level_buttons = get_level_buttons()


# ============================================
# 9. 绘制函数
# ============================================

def draw_game_grid():
    """绘制游戏地图（静态网格 + 箱子 + 玩家）"""
    for row in range(GRID):
        for col in range(GRID):
            x, y = col * CELL, row * CELL
            cell_type = static_grid[row][col]

            if cell_type == 1:       # 墙
                screen.blit(spr_wall, (x, y))
            elif cell_type == 2:     # 目标点
                screen.blit(spr_target, (x, y))
            else:                    # 地板
                screen.blit(spr_floor, (x, y))

    # 绘制箱子
    for bx, by in boxes:
        px, py = bx * CELL, by * CELL
        if (bx, by) in targets:
            screen.blit(spr_box_on, (px, py))  # 箱子在目标上 → 绿色
        else:
            screen.blit(spr_box, (px, py))     # 普通箱子 → 橙色

    # 绘制玩家
    screen.blit(spr_player, (player_x * CELL, player_y * CELL))


def draw_game_info():
    """绘制游戏信息栏（关卡名、步数）"""
    # 顶部半透明信息栏背景
    info_bg = pygame.Surface((SCREEN_SIZE, 40), pygame.SRCALPHA)
    info_bg.fill((0, 0, 0, 120))
    screen.blit(info_bg, (0, 0))

    # 关卡名称
    name_text = font_small.render(
        f"{LEVEL_NAMES[current_level]}  |  步数: {steps}  |  R重来  U撤销  ESC菜单",
        True, COLOR_INFO_TEXT
    )
    screen.blit(name_text, (10, 10))

    # 操作提示（底部）
    hint_bg = pygame.Surface((SCREEN_SIZE, 30), pygame.SRCALPHA)
    hint_bg.fill((0, 0, 0, 100))
    screen.blit(hint_bg, (0, SCREEN_SIZE - 30))
    hint_text = font_small.render(
        "方向键/WASD移动  R重来  U撤销  ESC菜单",
        True, (180, 180, 180)
    )
    screen.blit(hint_text, (10, SCREEN_SIZE - 26))


def draw_menu():
    """绘制选关界面"""
    screen.fill(COLOR_MENU_BG)

    # 标题
    title = font_title.render("推箱子", True, (255, 215, 0))
    title_rect = title.get_rect(center=(SCREEN_SIZE // 2, 60))
    screen.blit(title, title_rect)

    subtitle = font_normal.render("选择关卡", True, (200, 200, 200))
    subtitle_rect = subtitle.get_rect(center=(SCREEN_SIZE // 2, 110))
    screen.blit(subtitle, subtitle_rect)

    # 装饰线
    pygame.draw.line(screen, (255, 215, 0),
                     (SCREEN_SIZE // 4, 140),
                     (SCREEN_SIZE * 3 // 4, 140), 2)

    # 关卡按钮
    mouse_pos = pygame.mouse.get_pos()
    for i, btn in enumerate(level_buttons):
        # 悬停效果
        if btn.collidepoint(mouse_pos):
            btn_color = COLOR_BTN_HOVER
            border_width = 4
        else:
            btn_color = COLOR_BTN_NORMAL
            border_width = 2

        # 如果已完成，显示不同的颜色
        if level_completed[i]:
            btn_color = (btn_color[0] // 2, btn_color[1], btn_color[2] // 2)

        pygame.draw.rect(screen, btn_color, btn, border_radius=15)
        pygame.draw.rect(screen, (200, 240, 200), btn, border_width, border_radius=15)

        # 关卡名称
        level_text = font_button.render(f"第{i + 1}关", True, COLOR_WHITE)
        level_rect = level_text.get_rect(center=(btn.centerx, btn.centery - 10))
        screen.blit(level_text, level_rect)

        # 难度星级
        diff_text = font_small.render(LEVEL_DIFFICULTY[i], True, (255, 255, 200))
        diff_rect = diff_text.get_rect(center=(btn.centerx, btn.centery + 18))
        screen.blit(diff_text, diff_rect)

        # 完成标记
        if level_completed[i]:
            check_text = font_small.render("✓ 完成", True, (100, 255, 100))
            check_rect = check_text.get_rect(center=(btn.centerx, btn.centery - 32))
            screen.blit(check_text, check_rect)

    # 底部提示
    hint = font_small.render("点击关卡按钮开始游戏", True, (150, 150, 150))
    hint_rect = hint.get_rect(center=(SCREEN_SIZE // 2, SCREEN_SIZE - 40))
    screen.blit(hint, hint_rect)


def draw_win_effect():
    """绘制通关动画效果"""
    elapsed = pygame.time.get_ticks() - win_start_time

    # 目标点闪烁
    flash_on = (elapsed // FLASH_INTERVAL) % 2 == 0

    for tx, ty in targets:
        px, py = tx * CELL, ty * CELL
        if flash_on:
            # 闪烁时：用绿色目标点素材替换
            screen.blit(spr_target_win, (px, py))
        else:
            # 不闪烁时：保持红色
            screen.blit(spr_target, (px, py))

    # 通关文字（闪烁结束后显示）
    if elapsed > WIN_ANIMATION_DURATION // 2:
        # 半透明遮罩
        overlay = pygame.Surface((SCREEN_SIZE, SCREEN_SIZE), pygame.SRCALPHA)
        overlay.fill((0, 0, 0, 160))
        screen.blit(overlay, (0, 0))

        # 通关大字
        win_text = font_title.render("通关！", True, (255, 215, 0))
        win_rect = win_text.get_rect(center=(SCREEN_SIZE // 2, SCREEN_SIZE // 2 - 50))
        screen.blit(win_text, win_rect)

        # 步数展示
        step_text = font_large.render(f"用了 {steps} 步", True, COLOR_WHITE)
        step_rect = step_text.get_rect(center=(SCREEN_SIZE // 2, SCREEN_SIZE // 2 + 10))
        screen.blit(step_text, step_rect)

        # 操作提示
        if current_level < len(LEVELS) - 1:
            next_text = font_normal.render("按 N 进入下一关  按 ESC 返回选关", True, (180, 180, 180))
        else:
            next_text = font_large.render("全部通关！太厉害了！", True, (255, 215, 0))
            next_rect2 = next_text.get_rect(center=(SCREEN_SIZE // 2, SCREEN_SIZE // 2 + 55))
            screen.blit(next_text, next_rect2)
            next_text = font_normal.render("按 ESC 返回选关", True, (180, 180, 180))

        next_rect = next_text.get_rect(center=(SCREEN_SIZE // 2, SCREEN_SIZE // 2 + 95))
        screen.blit(next_text, next_rect)


# ============================================
# 10. 主循环
# ============================================

def main():
    global game_state, current_level, win_start_time, level_completed, level_steps

    running = True

    while running:
        # ========== 事件处理 ==========
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

            # --- 选关界面事件 ---
            if game_state == "menu":
                if event.type == pygame.MOUSEBUTTONDOWN:
                    if event.button == 1:  # 左键
                        mouse_pos = event.pos
                        for i, btn in enumerate(level_buttons):
                            if btn.collidepoint(mouse_pos):
                                current_level = i
                                load_level(current_level)
                                game_state = "playing"
                                break

                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_1:
                        current_level = 0
                        load_level(current_level)
                        game_state = "playing"
                    elif event.key == pygame.K_2 and len(LEVELS) > 1:
                        current_level = 1
                        load_level(current_level)
                        game_state = "playing"
                    elif event.key == pygame.K_3 and len(LEVELS) > 2:
                        current_level = 2
                        load_level(current_level)
                        game_state = "playing"

            # --- 游戏中事件 ---
            elif game_state == "playing":
                if event.type == pygame.KEYDOWN:
                    # 方向键移动
                    if event.key == pygame.K_LEFT or event.key == pygame.K_a:
                        move_player(-1, 0)
                    elif event.key == pygame.K_RIGHT or event.key == pygame.K_d:
                        move_player(1, 0)
                    elif event.key == pygame.K_UP or event.key == pygame.K_w:
                        move_player(0, -1)
                    elif event.key == pygame.K_DOWN or event.key == pygame.K_s:
                        move_player(0, 1)
                    elif event.key == pygame.K_r:
                        reset_level()
                    elif event.key == pygame.K_u:
                        undo_move()
                    elif event.key == pygame.K_ESCAPE:
                        game_state = "menu"

                    # 通关检测（每次移动后检查）
                    if check_win():
                        game_state = "win"
                        win_start_time = pygame.time.get_ticks()
                        level_completed[current_level] = True
                        level_steps[current_level] = steps

            # --- 通关动画事件 ---
            elif game_state == "win":
                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_n:
                        if current_level < len(LEVELS) - 1:
                            current_level += 1
                            load_level(current_level)
                            game_state = "playing"
                        else:
                            game_state = "menu"  # 全部通关，回菜单
                    elif event.key == pygame.K_ESCAPE:
                        game_state = "menu"
                    elif event.key == pygame.K_r:
                        reset_level()
                        game_state = "playing"

        # ========== 绘制 ==========
        if game_state == "menu":
            draw_menu()
            # 在选关界面也显示完成信息
            y_offset = 160
            for i in range(len(LEVELS)):
                if level_completed[i]:
                    info = font_small.render(
                        f"{LEVEL_NAMES[i]} - {level_steps[i]}步",
                        True, (150, 255, 150)
                    )
                    info_rect = info.get_rect(center=(SCREEN_SIZE // 2, y_offset))
                    screen.blit(info, info_rect)
                    y_offset += 22

        elif game_state == "playing":
            draw_game_grid()
            draw_game_info()

        elif game_state == "win":
            draw_game_grid()
            draw_win_effect()
            draw_game_info()

        pygame.display.flip()
        clock.tick(FPS)

    pygame.quit()
    sys.exit()


# ============================================
# 11. 启动游戏
# ============================================
if __name__ == "__main__":
    load_level(0)  # 预加载第1关（用于菜单展示）
    main()
