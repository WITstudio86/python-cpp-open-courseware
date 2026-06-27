"""
第28节：同色消除 —— 泡泡龙（完整版）

功能：
1. 六边形网格泡泡布局
2. 鼠标瞄准 + 发射泡泡
3. BFS（广度优先搜索）同色泡泡相邻检测
4. 连通分量 >= 3 个则消除
5. 悬空检测（从顶部 BFS），悬空泡泡掉落
6. 消除动画（泡泡缩放消失）+ 掉落动画（加速下落）

知识要点：
- BFS 算法：用水波扩散的比喻来理解
- 连通分量：与起点相邻且同色的所有泡泡
- 悬空检测：从顶部出发做 BFS，未访问的泡泡即悬空
"""

import pygame
import sys
import math
import random
from collections import deque

# ==================== 初始化 ====================
pygame.init()
WINDOW_WIDTH = 800
WINDOW_HEIGHT = 700
screen = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))
pygame.display.set_caption("泡泡龙 - 第28节：同色消除")
clock = pygame.time.Clock()

# ==================== 常量 ====================
BUBBLE_RADIUS = 22          # 泡泡半径
BUBBLE_DIAMETER = BUBBLE_RADIUS * 2  # 泡泡直径
GRID_COLS = 12              # 网格列数
GRID_ROWS = 12              # 网格行数
GRID_OFFSET_X = 50          # 网格左上角 X 偏移
GRID_OFFSET_Y = 50          # 网格左上角 Y 偏移
SHOOTER_Y = WINDOW_HEIGHT - 60  # 发射器 Y 坐标

# 泡泡颜色列表（用 RGB 元组表示）
COLORS = [
    (233, 69, 96),     # 红色
    (83, 216, 251),    # 蓝色
    (78, 204, 163),    # 绿色
    (245, 197, 24),    # 黄色
    (255, 140, 50),    # 橙色
    (180, 130, 255),   # 紫色
]
COLOR_NAMES = ["红", "蓝", "绿", "黄", "橙", "紫"]
NUM_COLORS = 5  # 实际使用前 5 种颜色

# 偶数行和奇数行的六个邻居方向偏移
# 偶数行 (row % 2 == 0)：泡泡位置偏左，邻居偏移如下
EVEN_NEIGHBORS = [(-1, -1), (-1, 0), (0, -1), (0, 1), (1, -1), (1, 0)]
# 奇数行 (row % 2 == 1)：泡泡位置偏右，邻居偏移如下
ODD_NEIGHBORS  = [(-1, 0), (-1, 1), (0, -1), (0, 1), (1, 0), (1, 1)]

# ==================== 数据结构 ====================
# 网格：grid[row][col] = 颜色索引（0~4）或 None（空格）
grid = [[None for _ in range(GRID_COLS)] for _ in range(GRID_ROWS)]

# 发射器状态
shooter_color = 0           # 当前发射泡泡的颜色
shooter_angle = -90         # 发射角度（-90 = 正上方）
shooter_x = WINDOW_WIDTH // 2  # 发射器 X 坐标

# 飞行中的泡泡
flying_bubble = None  # {'x': float, 'y': float, 'vx': float, 'vy': float, 'color': int}

# 动画列表
eliminate_animations = []  # [{'row':, 'col':, 'color':, 'scale': float}, ...]
falling_animations = []    # [{'x':, 'y':, 'vy':, 'color':}, ...]

# 游戏状态
# 状态:"aiming" = 正在瞄准, "flying" = 泡泡飞行中, "animating" = 动画播放中
game_state = "aiming"

# ==================== 工具函数 ====================

def get_bubble_position(row, col):
    """
    根据网格的行列，计算泡泡在屏幕上的像素坐标
    偶数行向左偏移半个直径（六边形错位排列）
    """
    x = GRID_OFFSET_X + col * BUBBLE_DIAMETER + BUBBLE_RADIUS
    y = GRID_OFFSET_Y + row * (BUBBLE_DIAMETER - 2) + BUBBLE_RADIUS
    if row % 2 == 0:
        x += BUBBLE_RADIUS  # 偶数行向右偏移半个泡泡
    return x, y


def get_grid_position(pixel_x, pixel_y):
    """
    根据屏幕上的像素坐标，反算最近的有效网格位置 (row, col)
    返回 (row, col) 或 None（如果超出网格范围）
    """
    # 先估算所在的行
    approx_row = int((pixel_y - GRID_OFFSET_Y) / (BUBBLE_DIAMETER - 2))
    if approx_row < 0 or approx_row >= GRID_ROWS:
        return None

    # 精确计算：考虑偶数行的偏移
    best_row, best_col = None, None
    best_dist = float('inf')

    # 检查附近的几行（因为估算可能有偏差）
    for row in range(max(0, approx_row - 1), min(GRID_ROWS, approx_row + 2)):
        for col in range(GRID_COLS):
            if grid[row][col] is not None:
                continue  # 已经占用的格子跳过
            cx, cy = get_bubble_position(row, col)
            dist = math.hypot(pixel_x - cx, pixel_y - cy)
            if dist < BUBBLE_DIAMETER and dist < best_dist:
                best_dist = dist
                best_row, best_col = row, col

    return (best_row, best_col) if best_row is not None else None


def get_neighbors(row, col):
    """
    获取格子 (row, col) 的六个邻居方向
    根据行号的奇偶选择正确的偏移
    """
    if row % 2 == 0:
        offsets = EVEN_NEIGHBORS
    else:
        offsets = ODD_NEIGHBORS

    neighbors = []
    for dr, dc in offsets:
        nr, nc = row + dr, col + dc
        if 0 <= nr < GRID_ROWS and 0 <= nc < GRID_COLS:
            neighbors.append((nr, nc))
    return neighbors


# ==================== BFS 算法：同色泡泡连通检测 ====================

def bfs_find_same_color(start_row, start_col):
    """
    使用 BFS（广度优先搜索）找到所有与起点同色且连通的泡泡

    【水波扩散比喻】
    往平静的水面扔一颗石子（起点泡泡），涟漪会一圈一圈向外扩散。
    所有被涟漪触及的"同色泡泡"都会被找到。

    参数：
        start_row, start_col: 起点泡泡的网格坐标

    返回：
        [(row, col), ...] 所有连通的同色泡泡位置列表
    """
    target_color = grid[start_row][start_col]
    if target_color is None:
        return []

    # ===== BFS 准备阶段 =====
    # queue: 双端队列，存储"待探索"的位置（水波的"前沿"）
    # 使用 deque 是因为 popleft() 是 O(1)，而 list.pop(0) 是 O(n)
    queue = deque()
    queue.append((start_row, start_col))

    # visited: 集合，记录已经探索过的位置（避免重复访问和死循环）
    visited = set()
    visited.add((start_row, start_col))

    # result: 收集所有找到的同色连通泡泡
    result = [(start_row, start_col)]

    # ===== BFS 主循环：一层一层地探索 =====
    while queue:
        # 从队首取出一个位置（就像水波从当前点往外扩散）
        row, col = queue.popleft()

        # 检查当前格子的所有邻居（六个方向）
        for nr, nc in get_neighbors(row, col):
            # 跳过已经访问过的格子（防止"回头"）
            if (nr, nc) in visited:
                continue

            # 跳过空格子（没有泡泡）
            if grid[nr][nc] is None:
                continue

            # 【关键判断】如果邻居的颜色与目标颜色相同，加入探索队列
            if grid[nr][nc] == target_color:
                visited.add((nr, nc))      # 标记为已访问
                queue.append((nr, nc))     # 加入队列，等待下一轮探索
                result.append((nr, nc))    # 记录这个同色泡泡

    return result


# ==================== 悬空检测：从顶部出发的 BFS ====================

def find_floating_bubbles():
    """
    用 BFS 从顶部出发，找出所有悬空（不再与顶部连通）的泡泡

    【摘葡萄比喻】
    葡萄一串串挂在藤（顶部行）上。
    如果中间被摘掉几颗，下面的葡萄就断了连接 → 悬空了！

    返回：
        [(row, col), ...] 所有悬空泡泡的位置列表
    """
    # ===== 步骤1：从顶部第一行出发，把所有顶部泡泡加入队列 =====
    # 这些就是"葡萄藤"——只要还和它们连着的，就是安全的
    queue = deque()
    visited = set()

    for col in range(GRID_COLS):
        if grid[0][col] is not None:  # 顶部这一格有泡泡
            queue.append((0, col))
            visited.add((0, col))

    # ===== 步骤2：BFS 向下探索所有"还连着顶部"的泡泡 =====
    while queue:
        row, col = queue.popleft()

        # 检查六个方向的邻居
        for nr, nc in get_neighbors(row, col):
            if (nr, nc) in visited:
                continue
            if grid[nr][nc] is not None:  # 这里有一个泡泡
                visited.add((nr, nc))      # 标记：这个泡泡还连着顶部
                queue.append((nr, nc))     # 继续从这个泡泡往下探索

    # ===== 步骤3：找出"没有被访问到"的泡泡 = 悬空泡泡 =====
    # 所有存在泡泡但没有被 BFS 访问到的位置 → 断了连接的葡萄！
    floating = []
    for row in range(GRID_ROWS):
        for col in range(GRID_COLS):
            if grid[row][col] is not None and (row, col) not in visited:
                floating.append((row, col))

    return floating


# ==================== 消除和掉落逻辑 ====================

def try_eliminate(row, col):
    """
    尝试消除：BFS 找到同色连通泡泡，如果 >= 3 个就消除
    返回 True 表示有泡泡被消除
    """
    connected = bfs_find_same_color(row, col)

    if len(connected) >= 3:
        # 有足够多的同色泡泡 → 消除！
        for r, c in connected:
            # 添加到消除动画列表（记录初始状态）
            cx, cy = get_bubble_position(r, c)
            eliminate_animations.append({
                'row': r, 'col': c,
                'x': cx, 'y': cy,
                'color': grid[r][c],
                'scale': 1.0,       # 初始缩放为 1（正常大小）
                'max_scale': 1.2,   # 先放大再缩小（弹跳效果）
                'growing': True,    # 初始阶段：放大
            })
            grid[r][c] = None  # 从网格中移除
        return True
    else:
        return False


def check_and_drop_floating():
    """
    消除后检查悬空泡泡，让它们掉落
    """
    floating = find_floating_bubbles()
    for r, c in floating:
        # 添加到掉落动画列表
        cx, cy = get_bubble_position(r, c)
        falling_animations.append({
            'x': cx,
            'y': cy,
            'vy': 1.0,             # 初始下落速度
            'color': grid[r][c],
        })
        grid[r][c] = None  # 从网格中移除
    return len(floating) > 0


# ==================== 初始化网格 ====================

def init_grid():
    """初始化网格：在第 0~4 行随机填充泡泡（给游戏一个初始状态）"""
    global grid
    grid = [[None for _ in range(GRID_COLS)] for _ in range(GRID_ROWS)]

    # 填充前 5 行（行0到行4），模拟已存在的泡泡
    for row in range(5):
        for col in range(GRID_COLS):
            # 偶数行的最后一列可以不填（六边形错位导致这里可能超出）
            # 为了让游戏更容易测试消除，我们填满大部分
            if row % 2 == 0 and col == GRID_COLS - 1:
                continue  # 偶数行最后一列留空
            color_idx = random.randint(0, NUM_COLORS - 1)
            grid[row][col] = color_idx


# ==================== 发射泡泡 ====================

def launch_bubble():
    """从发射器发射泡泡，计算飞行速度"""
    global flying_bubble, game_state

    # 角度转弧度（pygame 中 0 度是右方，-90 度是上方）
    radians = math.radians(shooter_angle)

    # 飞行速度
    speed = 12
    vx = math.cos(radians) * speed
    vy = math.sin(radians) * speed

    flying_bubble = {
        'x': float(shooter_x),
        'y': float(SHOOTER_Y),
        'vx': vx,
        'vy': vy,
        'color': shooter_color,
    }
    game_state = "flying"

    # 预选下一个泡泡的颜色
    change_shooter_color()


def change_shooter_color():
    """随机更换发射器中的泡泡颜色"""
    global shooter_color
    # 从当前网格中存在的颜色里随机选（增加游戏可玩性）
    existing_colors = set()
    for row in range(GRID_ROWS):
        for col in range(GRID_COLS):
            if grid[row][col] is not None:
                existing_colors.add(grid[row][col])

    if existing_colors:
        shooter_color = random.choice(list(existing_colors))
    else:
        shooter_color = random.randint(0, NUM_COLORS - 1)


# ==================== 更新逻辑 ====================

def update_flying_bubble():
    """更新飞行中泡泡的位置和碰撞检测"""
    global flying_bubble, game_state

    if flying_bubble is None:
        return

    # 移动泡泡
    flying_bubble['x'] += flying_bubble['vx']
    flying_bubble['y'] += flying_bubble['vy']

    x, y = flying_bubble['x'], flying_bubble['y']

    # 边界反弹（左右墙壁）
    if x - BUBBLE_RADIUS <= 0:
        flying_bubble['vx'] = abs(flying_bubble['vx'])
        flying_bubble['x'] = BUBBLE_RADIUS
    elif x + BUBBLE_RADIUS >= WINDOW_WIDTH:
        flying_bubble['vx'] = -abs(flying_bubble['vx'])
        flying_bubble['x'] = WINDOW_WIDTH - BUBBLE_RADIUS

    # 碰到顶部 → 直接停靠最近的格子
    if y - BUBBLE_RADIUS <= GRID_OFFSET_Y:
        snap_bubble(x, y)
        return

    # 检测是否与其他泡泡碰撞
    for row in range(GRID_ROWS):
        for col in range(GRID_COLS):
            if grid[row][col] is None:
                continue
            bx, by = get_bubble_position(row, col)
            if math.hypot(x - bx, y - by) < BUBBLE_DIAMETER:
                snap_bubble(x, y)
                return


def snap_bubble(x, y):
    """
    泡泡停靠到最近的空格子
    然后执行消除逻辑和悬空检测
    """
    global flying_bubble, game_state

    # 找到最近的空格子
    grid_pos = get_grid_position(x, y)
    if grid_pos is None:
        # 找不到有效位置，让泡泡继续飞（或放到一个默认位置）
        # 尝试找到最近的可放置格子
        best_dist = float('inf')
        best_pos = None
        for row in range(GRID_ROWS):
            for col in range(GRID_COLS):
                if grid[row][col] is not None:
                    continue
                cx, cy = get_bubble_position(row, col)
                dist = math.hypot(x - cx, y - cy)
                if dist < best_dist:
                    best_dist = dist
                    best_pos = (row, col)

        if best_pos:
            grid_pos = best_pos
        else:
            # 没有空格了，游戏结束
            game_state = "aiming"
            flying_bubble = None
            return

    row, col = grid_pos
    color = flying_bubble['color']

    # 把泡泡放到网格中
    grid[row][col] = color
    flying_bubble = None

    # 开始消除检测
    game_state = "animating"

    # 步骤1：尝试消除同色泡泡
    eliminated = try_eliminate(row, col)

    if eliminated:
        # 步骤2：消除后，检查悬空泡泡
        check_and_drop_floating()

    # 如果没有动画要播放，直接回到瞄准状态
    if not eliminate_animations and not falling_animations:
        game_state = "aiming"
        change_shooter_color()


def update_animations():
    """更新消除动画和掉落动画"""
    global game_state, eliminate_animations, falling_animations

    # ===== 更新消除动画 =====
    # 泡泡先放大（弹跳效果），再缩小直到消失
    finished_elim = []
    for anim in eliminate_animations:
        if anim['growing']:
            # 放大阶段：scale 从 1.0 增长到 1.2
            anim['scale'] += 0.03
            if anim['scale'] >= anim['max_scale']:
                anim['growing'] = False
        else:
            # 缩小阶段：scale 从 1.2 减小到 0
            anim['scale'] -= 0.06
            if anim['scale'] <= 0:
                finished_elim.append(anim)

    # 移除已完成的消除动画
    for anim in finished_elim:
        eliminate_animations.remove(anim)

    # ===== 更新掉落动画 =====
    # 泡泡加速下落（模拟重力）
    finished_fall = []
    for anim in falling_animations:
        anim['vy'] += 0.4      # 重力加速度：速度每帧增加
        anim['y'] += anim['vy']  # 更新位置
        if anim['y'] > WINDOW_HEIGHT + BUBBLE_DIAMETER:
            finished_fall.append(anim)

    # 移除已完成的掉落动画
    for anim in finished_fall:
        falling_animations.remove(anim)

    # 如果所有动画都播放完了，回到瞄准状态
    if not eliminate_animations and not falling_animations and game_state == "animating":
        game_state = "aiming"
        change_shooter_color()


# ==================== 绘制函数 ====================

def draw_bubble(surface, x, y, color_idx, radius=BUBBLE_RADIUS, alpha=255, highlight=False):
    """
    绘制一个泡泡（用 Surface 绘制，不依赖外部图片）

    泡泡效果：
    - 主体颜色
    - 左上角高光（白色半透明圆）
    - 右下角阴影（深色半透明弧）
    """
    # 创建临时 surface（支持透明度）
    temp_surf = pygame.Surface((radius * 2, radius * 2), pygame.SRCALPHA)
    cx, cy = radius, radius

    if color_idx is None:
        return

    # 获取颜色
    base_color = COLORS[color_idx % len(COLORS)]

    # 主体圆形（带一点立体感）
    pygame.draw.circle(temp_surf, (*base_color, alpha), (cx, cy), radius)

    # 高光：左上角的白色半透明小圆
    highlight_radius = int(radius * 0.35)
    highlight_offset_x = int(radius * 0.3)
    highlight_offset_y = int(radius * 0.3)
    pygame.draw.circle(
        temp_surf,
        (255, 255, 255, min(160, alpha)),
        (cx - highlight_offset_x, cy - highlight_offset_y),
        highlight_radius
    )

    # 更小的高光点（让泡泡看起来更立体）
    tiny_highlight_radius = int(radius * 0.15)
    pygame.draw.circle(
        temp_surf,
        (255, 255, 255, min(200, alpha)),
        (cx - int(radius * 0.25), cy - int(radius * 0.4)),
        tiny_highlight_radius
    )

    # 如果正在高亮显示，额外加一圈光晕
    if highlight:
        pygame.draw.circle(
            temp_surf,
            (255, 255, 255, 100),
            (cx, cy),
            radius + 2,
            2
        )

    # 将临时 surface 贴到目标位置
    surface.blit(temp_surf, (x - radius, y - radius))


def draw_grid_bubbles():
    """绘制网格中所有的泡泡"""
    for row in range(GRID_ROWS):
        for col in range(GRID_COLS):
            if grid[row][col] is not None:
                x, y = get_bubble_position(row, col)
                draw_bubble(screen, x, y, grid[row][col])


def draw_eliminate_animations():
    """绘制消除动画中的泡泡（带缩放效果）"""
    for anim in eliminate_animations:
        scaled_radius = int(BUBBLE_RADIUS * anim['scale'])
        if scaled_radius > 0:
            draw_bubble(screen, int(anim['x']), int(anim['y']),
                       anim['color'], radius=scaled_radius)


def draw_falling_animations():
    """绘制掉落动画中的泡泡"""
    for anim in falling_animations:
        draw_bubble(screen, int(anim['x']), int(anim['y']), anim['color'])


def draw_shooter():
    """绘制发射器（底部的待发射泡泡 + 瞄准线）"""
    # 绘制瞄准线（虚线效果）
    radians = math.radians(shooter_angle)
    line_length = 80

    # 计算虚线终点
    end_x = shooter_x + math.cos(radians) * line_length
    end_y = SHOOTER_Y + math.sin(radians) * line_length

    # 绘制虚线
    dash_length = 6
    gap_length = 4
    total_len = math.hypot(end_x - shooter_x, end_y - SHOOTER_Y)
    if total_len > 0:
        dx = (end_x - shooter_x) / total_len
        dy = (end_y - SHOOTER_Y) / total_len
        drawn = 0
        while drawn < total_len:
            seg_start = drawn
            seg_end = min(drawn + dash_length, total_len)
            sx = shooter_x + dx * seg_start
            sy = SHOOTER_Y + dy * seg_start
            ex = shooter_x + dx * seg_end
            ey = SHOOTER_Y + dy * seg_end
            pygame.draw.line(screen, (255, 255, 255, 150), (sx, sy), (ex, ey), 2)
            drawn = seg_end + gap_length

    # 绘制发射器底座
    pygame.draw.circle(screen, (60, 60, 80), (shooter_x, SHOOTER_Y), BUBBLE_RADIUS + 5)

    # 绘制待发射的泡泡
    draw_bubble(screen, shooter_x, SHOOTER_Y, shooter_color, highlight=True)

    # 绘制角度指示文字
    font_small = pygame.font.SysFont("microsoftyahei", 20)
    angle_text = font_small.render(f"角度: {abs(shooter_angle + 90):.0f}°", True, (200, 200, 200))
    screen.blit(angle_text, (shooter_x + 30, SHOOTER_Y - 30))


def draw_flying_bubble():
    """绘制空中飞行的泡泡"""
    if flying_bubble:
        draw_bubble(
            screen,
            int(flying_bubble['x']),
            int(flying_bubble['y']),
            flying_bubble['color'],
            highlight=True
        )


def draw_ui():
    """绘制界面提示"""
    font = pygame.font.SysFont("microsoftyahei", 28)
    font_small = pygame.font.SysFont("microsoftyahei", 20)

    # 标题
    title = font.render("泡泡龙 - 第28节：同色消除", True, (255, 255, 255))
    screen.blit(title, (WINDOW_WIDTH // 2 - title.get_width() // 2, 10))

    # 状态提示
    if game_state == "aiming":
        hint = font_small.render("🖱️ 移动鼠标瞄准 | 点击发射 | ← → 调整角度", True, (200, 200, 200))
    elif game_state == "flying":
        hint = font_small.render("🚀 泡泡飞行中...", True, (245, 197, 24))
    elif game_state == "animating":
        hint = font_small.render("✨ 消除动画中...", True, (78, 204, 163))
    else:
        hint = font_small.render("", True, (200, 200, 200))
    screen.blit(hint, (20, WINDOW_HEIGHT - 35))


# ==================== 主循环 ====================

def main():
    global shooter_angle, shooter_x, game_state

    # 初始化网格
    init_grid()
    change_shooter_color()

    running = True
    while running:
        # ===== 事件处理 =====
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
                pygame.quit()
                sys.exit()

            elif event.type == pygame.MOUSEMOTION:
                if game_state == "aiming":
                    # 鼠标移动时更新瞄准角度
                    mouse_x, mouse_y = event.pos
                    dx = mouse_x - shooter_x
                    dy = SHOOTER_Y - mouse_y  # Y 轴反转（向上为负）
                    shooter_angle = math.degrees(math.atan2(-dy, dx))

                    # 限制角度范围：只能向上发射（-170 到 -10 度）
                    if shooter_angle > -10:
                        shooter_angle = -10
                    elif shooter_angle < -170:
                        shooter_angle = -170

            elif event.type == pygame.MOUSEBUTTONDOWN:
                if game_state == "aiming" and event.button == 1:  # 左键发射
                    launch_bubble()

            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_LEFT:
                    if game_state == "aiming":
                        shooter_angle -= 2
                elif event.key == pygame.K_RIGHT:
                    if game_state == "aiming":
                        shooter_angle += 2
                elif event.key == pygame.K_r:
                    # 按 R 键重新开始
                    init_grid()
                    change_shooter_color()
                    eliminate_animations.clear()
                    falling_animations.clear()
                    flying_bubble = None
                    game_state = "aiming"

        # ===== 更新逻辑 =====
        if game_state == "flying":
            update_flying_bubble()

        if eliminate_animations or falling_animations:
            update_animations()

        # ===== 绘制 =====
        # 清屏（深色背景 + 渐变效果）
        screen.fill((25, 25, 50))

        # 绘制网格区域的背景（稍微亮一点）
        grid_bg_rect = pygame.Rect(
            GRID_OFFSET_X - 10, GRID_OFFSET_Y - 10,
            GRID_COLS * BUBBLE_DIAMETER + 20,
            GRID_ROWS * BUBBLE_DIAMETER + 20
        )
        pygame.draw.rect(screen, (35, 35, 60), grid_bg_rect, border_radius=8)
        pygame.draw.rect(screen, (60, 60, 90), grid_bg_rect, 2, border_radius=8)

        # 绘制网格线（辅助参考线，半透明）
        for row in range(GRID_ROWS):
            for col in range(GRID_COLS):
                x, y = get_bubble_position(row, col)
                if row % 2 == 0 and col == GRID_COLS - 1:
                    continue
                pygame.draw.circle(screen, (50, 50, 70, 40), (int(x), int(y)), BUBBLE_RADIUS, 1)

        # 绘制所有元素
        draw_grid_bubbles()
        draw_eliminate_animations()
        draw_falling_animations()
        draw_flying_bubble()
        draw_shooter()
        draw_ui()

        # 刷新画面
        pygame.display.flip()
        clock.tick(60)  # 60 FPS


# ==================== 程序入口 ====================
if __name__ == "__main__":
    main()
