"""
第40节 - 消行与加速：完整俄罗斯方块游戏
==============================================
功能说明：
  1. 7种标准方块，不同颜色
  2. 满行检测 + 消除 + 上方行整体下移
  3. Combo计分：1行=100, 2行=300, 3行=500, 4行=800
  4. 难度递增：每消10行，下落速度加快50ms（最低100ms）
  5. 下一个方块预览窗口
  6. Game Over判定 + 最终得分显示
  7. 按P暂停/继续，按R重新开始
  8. 棋盘：10列 × 20行

适用年级：中小学生（10-15岁）
"""

import pygame
import random
import sys

# ==================== 初始化 Pygame ====================
pygame.init()

# ==================== 常量定义 ====================
SCREEN_WIDTH = 600   # 窗口宽度
SCREEN_HEIGHT = 700  # 窗口高度
COLS = 10            # 棋盘列数
ROWS = 20            # 棋盘行数
CELL_SIZE = 30       # 每个格子的像素大小
GRID_X = 40          # 棋盘左上角 X 坐标
GRID_Y = 80          # 棋盘左上角 Y 坐标

# ==================== 颜色定义 ====================
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
GRAY = (128, 128, 128)
DARK_GRAY = (50, 50, 50)
LIGHT_GRAY = (180, 180, 180)
BG_COLOR = (20, 20, 30)  # 深蓝黑色背景

# 7种方块的颜色
PIECE_COLORS = {
    'I': (0, 255, 255),      # 青色 - I 形长条
    'O': (255, 255, 0),      # 黄色 - O 形方块
    'T': (160, 32, 240),     # 紫色 - T 形
    'S': (0, 255, 0),        # 绿色 - S 形
    'Z': (255, 0, 0),        # 红色 - Z 形
    'J': (0, 100, 255),      # 蓝色 - J 形
    'L': (255, 165, 0),      # 橙色 - L 形
}

# ==================== 7种标准方块形状定义 ====================
# 每个方块用一个二维列表表示，1 表示有方块，0 表示空
PIECE_SHAPES = {
    'I': [[1, 1, 1, 1]],                     # I - 一竖条
    'O': [[1, 1],                             # O - 正方形
          [1, 1]],
    'T': [[0, 1, 0],                          # T - T形
          [1, 1, 1]],
    'S': [[0, 1, 1],                          # S - S形
          [1, 1, 0]],
    'Z': [[1, 1, 0],                          # Z - Z形
          [0, 1, 1]],
    'J': [[1, 0, 0],                          # J - J形
          [1, 1, 1]],
    'L': [[0, 0, 1],                          # L - L形
          [1, 1, 1]],
}

# ==================== 字体辅助函数 ====================
def get_font(size):
    """获取支持中文的字体，跨平台兼容"""
    font_names = ['PingFang SC', 'STHeiti', 'SimHei', 'Microsoft YaHei', 'Arial']
    for name in font_names:
        try:
            return pygame.font.SysFont(name, size)
        except Exception:
            continue
    # 最后的回退方案：使用默认字体
    return pygame.font.Font(None, size)


def get_font_bold(size):
    """获取支持中文的粗体字体"""
    font_names = ['PingFang SC', 'STHeiti', 'SimHei', 'Microsoft YaHei', 'Arial']
    for name in font_names:
        try:
            return pygame.font.SysFont(name, size, bold=True)
        except Exception:
            continue
    return pygame.font.Font(None, size)


# ==================== 游戏核心函数 ====================
def create_grid():
    """创建一个空的棋盘（所有格子初始为0，表示空）"""
    return [[0 for _ in range(COLS)] for _ in range(ROWS)]


def new_piece():
    """随机生成一个新方块，放置在棋盘顶部中央"""
    name = random.choice(list(PIECE_SHAPES.keys()))
    shape = [row[:] for row in PIECE_SHAPES[name]]  # 深拷贝，避免修改模板
    color = PIECE_COLORS[name]
    # 计算方块的初始 X 位置：居中放置在棋盘顶部
    x = COLS // 2 - len(shape[0]) // 2
    y = 0  # 从棋盘最上方开始
    return {'shape': shape, 'color': color, 'x': x, 'y': y, 'name': name}


def rotate_shape(shape):
    """
    将方块顺时针旋转90度
    原理：将矩阵的行变为列（转置后再水平翻转每一行）
    new[j][i] = old[len(old)-1-j][i]
    """
    rows = len(shape)
    cols = len(shape[0])
    new = [[0] * rows for _ in range(cols)]
    for r in range(rows):
        for c in range(cols):
            new[c][rows - 1 - r] = shape[r][c]
    return new


def valid_position(grid, piece, dx=0, dy=0):
    """
    检查方块在棋盘中的位置是否合法
    参数 dx, dy 允许检查移动后的位置
    返回 True 表示位置合法，False 表示不合法
    """
    for r in range(len(piece['shape'])):
        for c in range(len(piece['shape'][0])):
            if piece['shape'][r][c]:
                new_x = piece['x'] + c + dx
                new_y = piece['y'] + r + dy
                # 检查左右边界
                if new_x < 0 or new_x >= COLS:
                    return False
                # 检查底部边界
                if new_y >= ROWS:
                    return False
                # 如果格子已在棋盘内，检查是否与已有方块重叠
                if new_y >= 0 and grid[new_y][new_x] != 0:
                    return False
    return True


def place_piece(grid, piece):
    """将当前方块"刻"到棋盘上，使其成为永久方块"""
    for r in range(len(piece['shape'])):
        for c in range(len(piece['shape'][0])):
            if piece['shape'][r][c]:
                y = piece['y'] + r
                x = piece['x'] + c
                if y >= 0:  # 只放置棋盘内的格子
                    grid[y][x] = piece['color']


def clear_lines(grid):
    """
    检测并消除满行，上方行整体下移

    算法说明（从上往下扫描 + pop删除 + insert空行）：
    1. 从第0行开始扫描
    2. 如果当前行所有格子都不为0 → 该行已满
       → 用 pop() 删除该行
       → 在顶部 insert 一个空行，模拟上方行整体下移
       → 不增加索引（因为下一行已自动移到了当前索引位置）
    3. 如果当前行未满 → 继续检查下一行
    4. 返回更新后的棋盘和消除的行数
    """
    cleared = 0
    r = 0
    while r < len(grid):
        # 检查第r行是否所有格子都非空（即整行已被填满）
        if all(cell != 0 for cell in grid[r]):
            # 删除满行
            grid.pop(r)
            # 在顶部插入一个空行（上方所有行整体下移一格）
            grid.insert(0, [0] * COLS)
            cleared += 1
            # 注意：不增加 r！因为原本的 r+1 行已经移到了 r 位置
        else:
            r += 1  # 该行不满，继续检查下一行
    return grid, cleared


def calc_score(lines_cleared):
    """
    根据一次消除的行数计算得分（Combo计分规则）

    为什么一次消多行得分比例更高？
    - 俄罗斯方块的魅力在于"冒险"：玩家故意垒高，等待长条来一次消4行
    - 消1行只是基本操作，消4行（俄罗斯方块Tetris）才是终极奖励
    - 越高的风险（垒得越高）应该获得越大的回报（得分倍数）
    """
    score_table = {
        1: 100,   # 单行消除：基本分
        2: 300,   # 双行消除：奖励50%（100×2×1.5=300）
        3: 500,   # 三行消除：奖励67%（100×3×1.67≈500）
        4: 800,   # 四行消除（俄罗斯方块！）：奖励100%（100×4×2=800）
    }
    return score_table.get(lines_cleared, 0)


def calc_fall_speed(total_lines):
    """
    根据已消除的总行数计算下落速度（毫秒）

    难度递增规则：
    - 初始速度：800ms（即每0.8秒下落一格）
    - 每消除10行，速度加快（间隔缩短50ms）
    - 最快不超过100ms（即每0.1秒下落一格，对高手也足够有挑战）

    等级 = total_lines // 10
    速度 = max(100, 800 - 等级 × 50)
    """
    level = total_lines // 10
    return max(100, 800 - level * 50)


# ==================== 绘制函数 ====================
def draw_grid_bg(screen):
    """绘制棋盘背景（边框和网格线）"""
    # 外边框
    rect = (GRID_X - 2, GRID_Y - 2, COLS * CELL_SIZE + 4, ROWS * CELL_SIZE + 4)
    pygame.draw.rect(screen, GRAY, rect, 2)
    # 内部网格线
    for r in range(ROWS):
        for c in range(COLS):
            cell_rect = (GRID_X + c * CELL_SIZE, GRID_Y + r * CELL_SIZE,
                         CELL_SIZE, CELL_SIZE)
            pygame.draw.rect(screen, DARK_GRAY, cell_rect, 1)


def draw_grid(screen, grid):
    """绘制棋盘上已经固定的方块"""
    for r in range(ROWS):
        for c in range(COLS):
            if grid[r][c] != 0:
                cell_rect = (GRID_X + c * CELL_SIZE, GRID_Y + r * CELL_SIZE,
                             CELL_SIZE, CELL_SIZE)
                # 绘制方块主体
                pygame.draw.rect(screen, grid[r][c], cell_rect)
                # 绘制边框（3D效果）
                pygame.draw.rect(screen, WHITE, cell_rect, 1)


def draw_piece(screen, piece):
    """绘制当前正在下落的方块"""
    for r in range(len(piece['shape'])):
        for c in range(len(piece['shape'][0])):
            if piece['shape'][r][c]:
                x = GRID_X + (piece['x'] + c) * CELL_SIZE
                y = GRID_Y + (piece['y'] + r) * CELL_SIZE
                # 只绘制在棋盘可见范围内的部分
                if piece['y'] + r >= 0:
                    cell_rect = (x, y, CELL_SIZE, CELL_SIZE)
                    pygame.draw.rect(screen, piece['color'], cell_rect)
                    pygame.draw.rect(screen, WHITE, cell_rect, 1)


def draw_info_panel(screen, score, level, total_lines, x, y):
    """绘制信息面板：分数、等级、已消行数"""
    font = get_font(26)
    font_bold = get_font_bold(28)

    # 面板背景
    panel_rect = (x - 10, y - 10, 190, 150)
    pygame.draw.rect(screen, (40, 40, 55), panel_rect)
    pygame.draw.rect(screen, GRAY, panel_rect, 2)

    # 分数
    score_label = font.render("分 数", True, LIGHT_GRAY)
    screen.blit(score_label, (x, y))
    score_val = font_bold.render(str(score), True, WHITE)
    screen.blit(score_val, (x + 80, y))

    # 等级
    level_label = font.render("等 级", True, LIGHT_GRAY)
    screen.blit(level_label, (x, y + 40))
    level_val = font_bold.render(str(level), True, WHITE)
    screen.blit(level_val, (x + 80, y + 40))

    # 已消行数
    lines_label = font.render("消 行", True, LIGHT_GRAY)
    screen.blit(lines_label, (x, y + 80))
    lines_val = font_bold.render(str(total_lines), True, WHITE)
    screen.blit(lines_val, (x + 80, y + 80))


def draw_next_piece_preview(screen, piece, x, y):
    """绘制下一个方块预览窗口"""
    font = get_font(24)

    # 标题
    title = font.render("下一个方块", True, LIGHT_GRAY)
    screen.blit(title, (x, y))

    # 预览区域背景
    preview_size = 22  # 预览区域每个小格子的大小
    preview_x = x + 5
    preview_y = y + 35

    # 计算预览框的大小（固定5x5区域）
    box_w = 5 * preview_size
    box_h = 5 * preview_size
    box_rect = (preview_x - 3, preview_y - 3, box_w + 6, box_h + 6)
    pygame.draw.rect(screen, (40, 40, 55), box_rect)
    pygame.draw.rect(screen, GRAY, box_rect, 2)

    # 计算方块在预览框中的居中偏移
    shape = piece['shape']
    shape_w = len(shape[0]) * preview_size
    shape_h = len(shape) * preview_size
    offset_x = preview_x + (box_w - shape_w) // 2
    offset_y = preview_y + (box_h - shape_h) // 2

    # 绘制预览方块
    for r in range(len(shape)):
        for c in range(len(shape[0])):
            if shape[r][c]:
                px = offset_x + c * preview_size
                py = offset_y + r * preview_size
                cell_rect = (px, py, preview_size, preview_size)
                pygame.draw.rect(screen, piece['color'], cell_rect)
                pygame.draw.rect(screen, WHITE, cell_rect, 1)


def draw_controls_hint(screen, x, y):
    """绘制操作提示"""
    font = get_font(18)
    hints = [
        "← →  左右移动",
        "↑     旋转方块",
        "↓     加速下落",
        "空格  直接落底",
        "P     暂停/继续",
        "R     重新开始",
    ]
    for i, hint in enumerate(hints):
        text = font.render(hint, True, LIGHT_GRAY)
        screen.blit(text, (x, y + i * 26))


def draw_game_over(screen, score):
    """绘制游戏结束画面"""
    # 半透明遮罩
    overlay = pygame.Surface((SCREEN_WIDTH, SCREEN_HEIGHT))
    overlay.set_alpha(200)
    overlay.fill(BLACK)
    screen.blit(overlay, (0, 0))

    font_large = get_font_bold(72)
    font_medium = get_font(36)
    font_small = get_font(28)

    # 游戏结束文字
    go_text = font_large.render("游戏结束", True, (255, 80, 80))
    screen.blit(go_text, (SCREEN_WIDTH // 2 - go_text.get_width() // 2,
                          SCREEN_HEIGHT // 2 - 100))

    # 最终得分
    score_text = font_medium.render(f"最终得分: {score}", True, WHITE)
    screen.blit(score_text, (SCREEN_WIDTH // 2 - score_text.get_width() // 2,
                             SCREEN_HEIGHT // 2 - 20))

    # 重新开始提示
    restart_text = font_small.render("按 R 键重新开始", True, LIGHT_GRAY)
    screen.blit(restart_text, (SCREEN_WIDTH // 2 - restart_text.get_width() // 2,
                               SCREEN_HEIGHT // 2 + 40))


def draw_pause(screen):
    """绘制暂停画面"""
    # 半透明遮罩
    overlay = pygame.Surface((SCREEN_WIDTH, SCREEN_HEIGHT))
    overlay.set_alpha(180)
    overlay.fill(BLACK)
    screen.blit(overlay, (0, 0))

    font_large = get_font_bold(72)
    font_small = get_font(28)

    pause_text = font_large.render("暂停中", True, (255, 255, 100))
    screen.blit(pause_text, (SCREEN_WIDTH // 2 - pause_text.get_width() // 2,
                             SCREEN_HEIGHT // 2 - 50))

    hint_text = font_small.render("按 P 键继续游戏", True, LIGHT_GRAY)
    screen.blit(hint_text, (SCREEN_WIDTH // 2 - hint_text.get_width() // 2,
                            SCREEN_HEIGHT // 2 + 20))


def draw_title(screen):
    """绘制游戏标题"""
    font = get_font_bold(32)
    title = font.render("俄罗斯方块", True, WHITE)
    screen.blit(title, (SCREEN_WIDTH // 2 - title.get_width() // 2, 15))

    font_small = get_font(16)
    subtitle = font_small.render("第40节 - 消行与加速", True, LIGHT_GRAY)
    screen.blit(subtitle, (SCREEN_WIDTH // 2 - subtitle.get_width() // 2, 52))


# ==================== 游戏初始化 ====================
def init_game():
    """初始化（或重置）游戏状态"""
    grid = create_grid()
    current = new_piece()
    nxt = new_piece()
    return {
        'grid': grid,
        'current': current,
        'next': nxt,
        'score': 0,
        'total_lines': 0,
        'game_over': False,
        'paused': False,
        'fall_time': 0,     # 累计下落计时（毫秒）
    }


# ==================== 主游戏循环 ====================
def main():
    """主函数：游戏的核心循环"""
    screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
    pygame.display.set_caption("俄罗斯方块 - 第40节 消行与加速")
    clock = pygame.time.Clock()

    # 初始化游戏状态
    state = init_game()

    running = True
    while running:
        # 控制帧率为60FPS，dt是距离上一帧的毫秒数
        dt = clock.tick(60)

        # ======== 1. 处理事件（键盘输入等） ========
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

            if event.type == pygame.KEYDOWN:
                # ---- 任何时候都可以用的按键 ----
                if event.key == pygame.K_r:
                    # R键：重新开始游戏
                    state = init_game()

                if event.key == pygame.K_p:
                    # P键：暂停/继续（仅在游戏未结束时有效）
                    if not state['game_over']:
                        state['paused'] = not state['paused']

                # ---- 仅在游戏进行中且未暂停时有效 ----
                if not state['game_over'] and not state['paused']:
                    if event.key == pygame.K_LEFT:
                        # 左移
                        if valid_position(state['grid'], state['current'], dx=-1):
                            state['current']['x'] -= 1

                    elif event.key == pygame.K_RIGHT:
                        # 右移
                        if valid_position(state['grid'], state['current'], dx=1):
                            state['current']['x'] += 1

                    elif event.key == pygame.K_DOWN:
                        # 软降：加速下落一格
                        if valid_position(state['grid'], state['current'], dy=1):
                            state['current']['y'] += 1

                    elif event.key == pygame.K_UP:
                        # 旋转方块
                        rotated = rotate_shape(state['current']['shape'])
                        old_shape = state['current']['shape']
                        state['current']['shape'] = rotated
                        # 如果旋转后位置不合法，恢复原形状
                        if not valid_position(state['grid'], state['current']):
                            state['current']['shape'] = old_shape

                    elif event.key == pygame.K_SPACE:
                        # 硬降（Hard Drop）：直接落到底部
                        while valid_position(state['grid'], state['current'], dy=1):
                            state['current']['y'] += 1
                        # 立即放置方块并处理消行
                        place_piece(state['grid'], state['current'])
                        state['grid'], cleared = clear_lines(state['grid'])
                        if cleared > 0:
                            state['score'] += calc_score(cleared)
                            state['total_lines'] += cleared
                        # 切换下一个方块
                        state['current'] = state['next']
                        state['next'] = new_piece()
                        # 检查新方块是否能放置（Game Over判定）
                        if not valid_position(state['grid'], state['current']):
                            state['game_over'] = True
                        # 重置下落计时器
                        state['fall_time'] = 0

        # ======== 2. 游戏逻辑更新（仅在游戏进行中且未暂停）========
        if not state['game_over'] and not state['paused']:
            # 根据总消行数计算当前下落速度
            fall_speed = calc_fall_speed(state['total_lines'])

            # 累计下落计时
            state['fall_time'] += dt
            if state['fall_time'] >= fall_speed:
                state['fall_time'] = 0  # 重置计时器

                # 尝试下落一格
                if valid_position(state['grid'], state['current'], dy=1):
                    state['current']['y'] += 1
                else:
                    # 无法继续下落，方块到达底部
                    # 1. 将方块固定到棋盘
                    place_piece(state['grid'], state['current'])

                    # 2. 检测并消除满行
                    state['grid'], cleared = clear_lines(state['grid'])
                    if cleared > 0:
                        state['score'] += calc_score(cleared)
                        state['total_lines'] += cleared

                    # 3. 生成下一个方块
                    state['current'] = state['next']
                    state['next'] = new_piece()

                    # 4. 检查新方块是否能在出生位置放置
                    if not valid_position(state['grid'], state['current']):
                        state['game_over'] = True

        # ======== 3. 绘制画面 ========
        screen.fill(BG_COLOR)

        # 标题
        draw_title(screen)

        # 棋盘背景和已固定的方块
        draw_grid_bg(screen)
        draw_grid(screen, state['grid'])

        # 当前下落中的方块（游戏未结束时绘制）
        if not state['game_over']:
            draw_piece(screen, state['current'])

        # 右侧信息面板
        info_x = GRID_X + COLS * CELL_SIZE + 40
        draw_info_panel(screen, state['score'],
                        state['total_lines'] // 10,
                        state['total_lines'],
                        info_x, GRID_Y)

        # 下一个方块预览
        draw_next_piece_preview(screen, state['next'], info_x, GRID_Y + 180)

        # 操作提示
        draw_controls_hint(screen, info_x + 10, GRID_Y + 380)

        # 游戏结束画面
        if state['game_over']:
            draw_game_over(screen, state['score'])

        # 暂停画面（覆盖在游戏结束画面之上则不绘制）
        if state['paused'] and not state['game_over']:
            draw_pause(screen)

        # 刷新屏幕
        pygame.display.flip()

    pygame.quit()
    sys.exit()


# ==================== 程序入口 ====================
if __name__ == '__main__':
    main()
