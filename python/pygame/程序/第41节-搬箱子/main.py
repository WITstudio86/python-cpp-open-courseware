"""
第41节：搬箱子 —— 推箱子游戏（单关版本）
============================================

地图编码：
    0 = 地板（空地）    1 = 墙        2 = 箱子
    3 = 目标点          4 = 玩家      5 = 箱子在目标点上

操作说明：
    方向键（↑↓←→）  移动玩家 / 推箱子
    U 键             撤销上一步（可连续撤销）
    R 键             重新开始本关
    ESC              退出游戏

所有游戏素材均用 pygame.draw 绘制，不依赖任何外部图片文件。
"""

import pygame
import sys

# ==================== 初始化 ====================
pygame.init()
CELL = 64                     # 每个格子的像素大小
ROWS, COLS = 10, 10           # 地图大小：10行 × 10列
WIDTH, HEIGHT = COLS * CELL, ROWS * CELL + 50  # 底部留 50px 显示步数
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("第41节：搬箱子 —— 推箱子游戏")
clock = pygame.time.Clock()

# 字体（用于显示步数、胜利提示、操作说明）
# 根据操作系统自动选择合适的中文字体
def _get_chinese_font(size, bold=False):
    """尝试加载系统中可用的中文字体，若都不可用则回退到默认字体"""
    font_names = []
    if sys.platform == "darwin":
        font_names = ["PingFang SC", "Heiti SC", "STHeiti", "Arial Unicode MS"]
    else:
        font_names = ["Microsoft YaHei", "SimHei", "Noto Sans SC", "Arial Unicode MS"]
    for name in font_names:
        try:
            return pygame.font.SysFont(name, size, bold=bold)
        except Exception:
            continue
    return pygame.font.Font(None, size)  # 最后的回退

font_small = _get_chinese_font(22)
font_medium = _get_chinese_font(28)
font_big = _get_chinese_font(48)

# ==================== 地图数据 ====================
# 10x10 关卡地图，0~5 编码
ORIGINAL_MAP = [
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 2, 0, 1],
    [1, 0, 0, 3, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 1, 1, 0, 0, 0, 0, 0, 1, 1],
    [1, 0, 0, 0, 0, 4, 0, 0, 0, 1],
    [1, 0, 2, 0, 0, 0, 3, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
]

# ==================== 游戏状态变量 ====================
game_map = [row[:] for row in ORIGINAL_MAP]  # 当前地图（深拷贝）
player_x, player_y = 0, 0                      # 玩家坐标
targets = set()                                # 所有目标点的初始坐标（用于恢复地图）
steps = 0                                      # 步数统计
move_history = []                              # 撤销历史：[{player_x, player_y, game_map, steps}, ...]


def find_player_and_targets():
    """遍历地图，找到玩家位置和所有目标点位置"""
    global player_x, player_y, targets
    targets.clear()
    for y in range(ROWS):
        for x in range(COLS):
            if game_map[y][x] == 4:
                player_x, player_y = x, y
            if game_map[y][x] == 3:
                targets.add((x, y))


# 启动时初始化
find_player_and_targets()


# ==================== 绘制函数 ====================

def draw_map():
    """
    用 pygame.draw 绘制整个游戏地图。
    不需任何外部图片 —— 所有图形都是矩形、圆形、线条的组合。
    """
    for y in range(ROWS):
        for x in range(COLS):
            cell = game_map[y][x]
            rect = pygame.Rect(x * CELL, y * CELL, CELL, CELL)

            if cell == 0:
                # 地板：浅灰底色 + 细网格线
                pygame.draw.rect(screen, (210, 200, 180), rect)
                pygame.draw.rect(screen, (180, 170, 150), rect, 1)

            elif cell == 1:
                # 墙：深棕色 + 砖纹效果
                pygame.draw.rect(screen, (100, 75, 50), rect)
                pygame.draw.rect(screen, (130, 100, 70), rect, 3)
                # 砖缝线
                pygame.draw.line(screen, (70, 50, 30),
                                 (x * CELL, y * CELL + CELL // 2),
                                 (x * CELL + CELL, y * CELL + CELL // 2), 2)
                pygame.draw.line(screen, (70, 50, 30),
                                 (x * CELL + CELL // 2, y * CELL),
                                 (x * CELL + CELL // 2, y * CELL + CELL // 2), 2)

            elif cell == 2:
                # 箱子：橙色方块 + 十字绑带
                pygame.draw.rect(screen, (210, 200, 180), rect)  # 先画地板底色
                pygame.draw.rect(screen, (180, 170, 150), rect, 1)
                # 箱子主体
                box_margin = 6
                box_rect = pygame.Rect(x * CELL + box_margin, y * CELL + box_margin,
                                       CELL - 2 * box_margin, CELL - 2 * box_margin)
                pygame.draw.rect(screen, (240, 165, 0), box_rect, border_radius=4)
                pygame.draw.rect(screen, (200, 130, 0), box_rect, 3, border_radius=4)
                # 十字绑带
                cx, cy = x * CELL + CELL // 2, y * CELL + CELL // 2
                pygame.draw.line(screen, (160, 100, 0), (cx, y * CELL + 10), (cx, y * CELL + CELL - 10), 3)
                pygame.draw.line(screen, (160, 100, 0), (x * CELL + 10, cy), (x * CELL + CELL - 10, cy), 3)

            elif cell == 3:
                # 目标点：红色圆点标记
                pygame.draw.rect(screen, (210, 200, 180), rect)
                pygame.draw.rect(screen, (180, 170, 150), rect, 1)
                center = (x * CELL + CELL // 2, y * CELL + CELL // 2)
                pygame.draw.circle(screen, (255, 100, 80), center, CELL // 4)
                pygame.draw.circle(screen, (200, 60, 40), center, CELL // 4, 2)

            elif cell == 4:
                # 玩家：蓝色小人（圆头 + 身体）
                pygame.draw.rect(screen, (210, 200, 180), rect)
                pygame.draw.rect(screen, (180, 170, 150), rect, 1)
                cx, cy = x * CELL + CELL // 2, y * CELL + CELL // 2
                # 头（圆）
                pygame.draw.circle(screen, (70, 180, 255), (cx, cy - 8), CELL // 5)
                pygame.draw.circle(screen, (30, 120, 200), (cx, cy - 8), CELL // 5, 2)
                # 身体（椭圆）
                body_rect = pygame.Rect(cx - CELL // 5, cy + 2, 2 * CELL // 5, CELL // 3)
                pygame.draw.ellipse(screen, (70, 180, 255), body_rect)
                pygame.draw.ellipse(screen, (30, 120, 200), body_rect, 2)
                # 眼睛
                eye_r = 4
                pygame.draw.circle(screen, (255, 255, 255), (cx - 5, cy - 12), eye_r)
                pygame.draw.circle(screen, (255, 255, 255), (cx + 5, cy - 12), eye_r)
                pygame.draw.circle(screen, (0, 0, 0), (cx - 5, cy - 12), 2)
                pygame.draw.circle(screen, (0, 0, 0), (cx + 5, cy - 12), 2)

            elif cell == 5:
                # 箱子到位：绿色箱子 + 红色目标点底色
                pygame.draw.rect(screen, (210, 200, 180), rect)
                pygame.draw.rect(screen, (180, 170, 150), rect, 1)
                # 目标点光圈
                center = (x * CELL + CELL // 2, y * CELL + CELL // 2)
                pygame.draw.circle(screen, (255, 140, 120), center, CELL // 3 - 2)
                # 到位箱子（绿色）
                box_margin = 6
                box_rect = pygame.Rect(x * CELL + box_margin, y * CELL + box_margin,
                                       CELL - 2 * box_margin, CELL - 2 * box_margin)
                pygame.draw.rect(screen, (80, 210, 130), box_rect, border_radius=4)
                pygame.draw.rect(screen, (40, 160, 80), box_rect, 3, border_radius=4)
                # 对勾标记
                check_size = 8
                lx, ly = x * CELL + CELL // 2 - 4, y * CELL + CELL // 2 + 2
                pygame.draw.line(screen, (255, 255, 255), (lx, ly), (lx + check_size, ly + check_size), 3)
                pygame.draw.line(screen, (255, 255, 255), (lx + check_size, ly + check_size),
                                 (lx + check_size + 10, ly - 6), 3)


def draw_ui():
    """绘制底部 UI：步数统计、操作提示"""
    ui_y = ROWS * CELL + 5

    # 底部背景条
    pygame.draw.rect(screen, (30, 30, 45), (0, ROWS * CELL, WIDTH, 50))

    # 步数
    steps_text = font_medium.render(f"步数: {steps}", True, (255, 200, 50))
    screen.blit(steps_text, (15, ui_y + 10))

    # 操作提示
    hint_text = font_small.render("方向键=移动  U=撤销  R=重来", True, (180, 180, 200))
    screen.blit(hint_text, (WIDTH - 400, ui_y + 14))


def draw_win_screen():
    """绘制胜利画面"""
    # 半透明黑色遮罩
    overlay = pygame.Surface((WIDTH, HEIGHT), pygame.SRCALPHA)
    overlay.fill((0, 0, 0, 180))
    screen.blit(overlay, (0, 0))

    # 胜利文字
    win_text = font_big.render("恭喜通关！", True, (255, 215, 0))
    text_rect = win_text.get_rect(center=(WIDTH // 2, HEIGHT // 2 - 30))
    screen.blit(win_text, text_rect)

    # 步数信息
    steps_text = font_medium.render(f"你用了 {steps} 步完成！", True, (255, 255, 255))
    steps_rect = steps_text.get_rect(center=(WIDTH // 2, HEIGHT // 2 + 30))
    screen.blit(steps_text, steps_rect)

    # 提示按R重新开始
    restart_text = font_small.render("按 R 键重新开始", True, (200, 200, 200))
    restart_rect = restart_text.get_rect(center=(WIDTH // 2, HEIGHT // 2 + 70))
    screen.blit(restart_text, restart_rect)


# ==================== 游戏逻辑 ====================

def save_state():
    """
    保存当前游戏状态的「快照」到 move_history 列表中。
    每次玩家移动之前调用，用于后续的撤销操作。

    关键点：必须对 game_map 做深拷贝 [row[:] for row in game_map]，
    否则后续修改会污染历史记录中的地图。
    """
    snapshot = {
        'player_x': player_x,
        'player_y': player_y,
        'game_map': [row[:] for row in game_map],  # 深拷贝每一行
        'steps': steps
    }
    move_history.append(snapshot)


def undo():
    """
    撤销上一步操作。
    从 move_history 末尾取出最近一次快照，恢复到该状态。
    可以连续撤销，直到回到初始状态。
    """
    global player_x, player_y, game_map, steps

    if not move_history:
        # 没有历史记录，无法撤销
        return

    # 取出最后一步的快照
    snapshot = move_history.pop()

    # 恢复到快照中的状态
    player_x = snapshot['player_x']
    player_y = snapshot['player_y']
    game_map = [row[:] for row in snapshot['game_map']]  # 深拷贝恢复
    steps = snapshot['steps']


def try_move(dx, dy):
    """
    尝试向 (dx, dy) 方向移动玩家。

    参数：
        dx: 水平方向偏移量（-1 左, 1 右, 0 不移动）
        dy: 垂直方向偏移量（-1 上, 1 下, 0 不移动）

    移动逻辑：
        1. 前方是地板(0)或目标点(3) → 玩家直接走过去
        2. 前方是箱子(2)或箱子到位(5) → 检查箱子前方
           - 箱子前方是地板(0)或目标点(3) → 推动箱子，玩家同时前进
           - 箱子前方是墙/箱子 → 无法推动，原地不动
        3. 前方是墙(1) → 无法通过，原地不动
    """
    global player_x, player_y, game_map, steps

    # ----- 计算玩家前方坐标 -----
    next_x = player_x + dx
    next_y = player_y + dy
    front = game_map[next_y][next_x]

    # ----- 情况1：前方是地板或目标点 → 直接走 -----
    if front == 0 or front == 3:
        save_state()

        # 玩家离开原位置：如果原来站在目标点上，恢复为目标点；否则恢复为地板
        game_map[player_y][player_x] = 3 if (player_x, player_y) in targets else 0

        # 玩家移动到新位置
        player_x, player_y = next_x, next_y
        game_map[player_y][player_x] = 4
        steps += 1

    # ----- 情况2：前方是箱子（普通箱子或已到位的箱子）→ 尝试推 -----
    elif front == 2 or front == 5:
        # 计算箱子前方一格（要被推过去的位置）
        box_next_x = next_x + dx
        box_next_y = next_y + dy
        beyond_box = game_map[box_next_y][box_next_x]

        # 箱子前方是地板或目标点 → 可以推动
        if beyond_box == 0 or beyond_box == 3:
            save_state()

            # 1) 清空玩家原位置
            game_map[player_y][player_x] = 3 if (player_x, player_y) in targets else 0

            # 2) 箱子移到新位置
            #    如果箱子前方是目标点(3)，箱子变成 5（到位）；否则变成 2（普通箱子）
            game_map[box_next_y][box_next_x] = 5 if beyond_box == 3 else 2

            # 3) 玩家站到箱子原来位置
            player_x, player_y = next_x, next_y
            game_map[player_y][player_x] = 4
            steps += 1

        # 箱子前方是墙/另一个箱子 → 推不动，什么都不做

    # ----- 情况3：前方是墙 → 什么都不做 -----


def check_win():
    """
    检查是否通关。
    通关条件：地图上不再有任何空的目标点（即没有值为 3 的格子）。
    所有目标点都已经被箱子占据（变成了 5）。
    """
    for row in game_map:
        if 3 in row:
            return False  # 还有空目标点，没赢
    return True  # 所有目标点都有箱子


def restart():
    """重置游戏到初始状态"""
    global game_map, player_x, player_y, steps, move_history

    # 从原始地图恢复（深拷贝）
    game_map = [row[:] for row in ORIGINAL_MAP]
    steps = 0
    move_history = []

    # 重新定位玩家
    find_player_and_targets()


# ==================== 主循环 ====================
running = True
won = False  # 是否已通关

while running:
    # ----- 事件处理 -----
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        elif event.type == pygame.KEYDOWN:
            # 退出
            if event.key == pygame.K_ESCAPE:
                running = False

            # 重新开始（任何时候都可以按）
            elif event.key == pygame.K_r:
                restart()
                won = False

            # 如果已经通关，不再响应移动和撤销（只能按R重来）
            elif won:
                continue

            # 撤销（U 键）
            elif event.key == pygame.K_u:
                undo()

            # 移动（方向键）
            elif event.key == pygame.K_UP:
                try_move(0, -1)
            elif event.key == pygame.K_DOWN:
                try_move(0, 1)
            elif event.key == pygame.K_LEFT:
                try_move(-1, 0)
            elif event.key == pygame.K_RIGHT:
                try_move(1, 0)

    # ----- 胜利检测（每帧检查） -----
    if not won and check_win():
        won = True

    # ----- 绘制 -----
    screen.fill((20, 20, 35))
    draw_map()
    draw_ui()

    if won:
        draw_win_screen()

    pygame.display.flip()
    clock.tick(60)

# ==================== 退出 ====================
pygame.quit()
sys.exit()
