"""
第27节：瞄准发射 —— 泡泡龙（发射器瞄准 + 泡泡飞行 + 六边形网格吸附）

知识点：
1. math.sin(angle) / math.cos(angle)  —— 将角度拆解为 X 和 Y 方向的分量
2. math.radians(角度)                   —— 角度制 → 弧度制
3. math.atan2(-dy, dx)                  —— 根据两点坐标差求角度
4. 六边形网格的坐标计算与吸附算法

操作方式：
- 鼠标移动 → 控制发射器的瞄准方向
- 空格键   → 发射泡泡
- R 键     → 重新开始
"""

import pygame
import math
import random
import sys

# ==================== 初始化 ====================
pygame.init()
WIDTH, HEIGHT = 640, 720
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("第27节：瞄准发射 — 泡泡龙")
clock = pygame.time.Clock()
FPS = 60

# ==================== 颜色常量 ====================
BLACK       = (0, 0, 0)
WHITE       = (255, 255, 255)
GRAY        = (100, 100, 100)
DARK_GRAY   = (50, 50, 50)
LIGHT_GRAY  = (200, 200, 200)
BG_COLOR    = (20, 20, 40)           # 深蓝紫色背景
RED         = (255, 60, 60)
GREEN       = (60, 220, 60)
BLUE        = (60, 120, 255)
YELLOW      = (255, 220, 40)
ORANGE      = (255, 140, 40)
PURPLE      = (200, 60, 220)
CYAN        = (60, 220, 220)
PINK        = (255, 120, 180)

# 泡泡可用颜色列表（用于随机生成）
BUBBLE_COLORS = [RED, GREEN, BLUE, YELLOW, ORANGE, PURPLE]

# ==================== 游戏参数 ====================
BUBBLE_RADIUS = 20                  # 泡泡半径（像素）
TOP_MARGIN = 40                     # 顶部边距

# ---- 六边形网格参数 ----
# 六边形网格中，泡泡紧密排列：
#   水平间距（列间距）= 2 * R（两个相邻泡泡的圆心距离 = 直径）
#   垂直间距（行间距）= √3 * R（六边形的高度）
#   奇数行向右偏移半个格子 → 形成蜂窝状排列
GRID_COLS = 10                      # 网格列数
GRID_ROWS = 13                      # 网格行数
CELL_W = 2 * BUBBLE_RADIUS          # 列间距 = 40
CELL_H = int(BUBBLE_RADIUS * math.sqrt(3))  # 行间距 ≈ 34
# 网格的起始 X 坐标（居中）
GRID_OFFSET_X = (WIDTH - (GRID_COLS - 1) * CELL_W) // 2 - CELL_W // 2

# 二维数组 grid[row][col]：存储每个格子里的泡泡颜色（None = 空格）
grid = [[None for _ in range(GRID_COLS)] for _ in range(GRID_ROWS)]

# 存储所有已停下的泡泡信息（用于碰撞检测和绘制）
# 每个元素是一个字典：{"x": int, "y": int, "color": tuple}
bubble_list = []


def get_grid_pos(col, row):
    """
    计算网格中第 col 列、第 row 行的泡泡的屏幕坐标。

    六边形网格规则：
    - 偶数行（row % 2 == 0）：贴左对齐 → x = col * CELL_W + R
    - 奇数行（row % 2 == 1）：右移半个格子 → x = col * CELL_W + R + CELL_W/2
    - y = row * CELL_H + R + TOP_MARGIN
    """
    x = GRID_OFFSET_X + col * CELL_W + BUBBLE_RADIUS
    # 奇数行右移半个格子（形成蜂窝状错位）
    if row % 2 == 1:
        x += CELL_W // 2
    y = row * CELL_H + BUBBLE_RADIUS + TOP_MARGIN
    return x, y


def draw_grid_preview():
    """
    用半透明圆形绘制所有空的网格位置
    帮助学生直观理解六边形网格的排列方式
    """
    for row in range(GRID_ROWS):
        for col in range(GRID_COLS):
            if grid[row][col] is None:
                gx, gy = get_grid_pos(col, row)
                # 只绘制在屏幕内的网格位置
                if 0 <= gx <= WIDTH and 0 <= gy <= HEIGHT:
                    # 半透明浅灰色圆圈表示空位
                    pygame.draw.circle(screen, (60, 60, 80),
                                       (int(gx), int(gy)),
                                       BUBBLE_RADIUS, 2)


def snap_to_grid(bx, by):
    """
    网格吸附算法 —— 将飞行泡泡（bx, by）吸附到最近且可用的六边形网格位置。

    算法步骤（三步走）：
    1️⃣ 找最近的列：用 X 坐标除以列间距
    2️⃣ 找最近的行：用 Y 坐标除以行间距（注意奇数行的偏移补偿）
    3️⃣ 从下往上找第一个空位（因为泡泡从下往上飞，可能"挤压"到更下面的空位）
    """
    # ---- 1️⃣ 找最近的列 ----
    # 先将 X 坐标转换到网格坐标系（去掉偏移，找落在哪一列）
    col = round((bx - GRID_OFFSET_X - BUBBLE_RADIUS) / CELL_W)
    col = max(0, min(GRID_COLS - 1, col))  # 限制在有效范围

    # ---- 2️⃣ 找最近的行 ----
    # 注意：如果 col 是奇数，需要补偿 X 偏移再来算行
    # 为什么要补偿？因为奇数行的 X 坐标多了半个格子，Y 的映射会受影响
    offset_x = 0
    if col % 2 == 1:
        offset_x = CELL_W // 2
    row = round((by - TOP_MARGIN - BUBBLE_RADIUS) / CELL_H)
    # 补偿奇数行的X偏移对Y判断的影响
    # （简化处理：如果X偏移导致在格子之间，需要微调）
    row = max(0, min(GRID_ROWS - 1, row))

    # ---- 3️⃣ 从下往上找第一个空位 ----
    # 从计算出的行开始向下找（row 越小越靠上）
    # 因为泡泡是从下往上飞的，碰到障碍后会停在比原本位置更低的位置
    for r in range(row, -1, -1):  # 从 row 往下遍历到 0
        if grid[r][col] is None:
            # 找到了！记录并返回坐标
            gx, gy = get_grid_pos(col, r)
            return gx, gy, col, r

    # 如果整列都满了（理论上不会发生），返回原始坐标
    return bx, by, -1, -1


def reset_game():
    """重置游戏：清空网格，在顶部生成初始泡泡"""
    global grid, bubble_list, flying_bubble, launcher_color
    # 清空所有网格
    for row in range(GRID_ROWS):
        for col in range(GRID_COLS):
            grid[row][col] = None
    bubble_list.clear()

    # ---- 在顶部 3 行随机生成初始泡泡 ----
    # 这样学生就能看到已有的泡泡，新发射的泡泡会粘上去
    for row in range(3):
        for col in range(GRID_COLS):
            # 奇数列在偶数行为空位（因为蜂窝状排列中会留空）
            # 为了画面饱满，奇数行跳过奇数列中的某些位置
            if row == 0 and col % 2 == 0:
                continue  # 第一行的偶数列留一些空，看起来更自然
            color = random.choice(BUBBLE_COLORS)
            grid[row][col] = color
            gx, gy = get_grid_pos(col, row)
            bubble_list.append({"x": gx, "y": gy, "color": color})

    # ---- 飞行泡泡状态 ----
    flying_bubble = None  # 当前飞行的泡泡，None 表示没有飞行中
    launcher_color = random.choice(BUBBLE_COLORS)


def draw_launcher(lx, ly, angle):
    """
    绘制发射器。
    发射器由以下几部分组成：
    - 底座（半圆形）
    - 炮管（矩形，随 angle 旋转）
    - 待发射的泡泡（在炮口位置）
    """
    # ---- 底座（半圆） ----
    base_rect = pygame.Rect(lx - 35, ly - 15, 70, 40)
    pygame.draw.ellipse(screen, DARK_GRAY, base_rect)
    pygame.draw.ellipse(screen, GRAY, base_rect, 2)

    # ---- 炮管（随角度旋转） ----
    # 炮管从发射器中心出发，沿 angle 方向延伸
    barrel_length = 48
    barrel_end_x = lx + barrel_length * math.cos(angle)
    barrel_end_y = ly - barrel_length * math.sin(angle)  # 屏幕Y轴向下，取负
    pygame.draw.line(screen, GRAY, (lx, ly),
                     (int(barrel_end_x), int(barrel_end_y)), 10)
    # 炮管高光
    pygame.draw.line(screen, LIGHT_GRAY, (lx, ly),
                     (int(barrel_end_x), int(barrel_end_y)), 4)

    # ---- 待在发射器上的泡泡（炮口位置） ----
    pygame.draw.circle(screen, launcher_color,
                       (int(barrel_end_x), int(barrel_end_y)),
                       BUBBLE_RADIUS)
    # 泡泡高光（小白点，让泡泡看起来有立体感）
    highlight_x = int(barrel_end_x - BUBBLE_RADIUS * 0.3)
    highlight_y = int(barrel_end_y - BUBBLE_RADIUS * 0.3)
    pygame.draw.circle(screen, (255, 255, 255, 180),
                       (highlight_x, highlight_y),
                       BUBBLE_RADIUS // 3)


def draw_aim_line(lx, ly, angle, mouse_dist):
    """
    绘制瞄准线（虚线效果）。
    从发射器出发，沿 angle 方向画到屏幕边缘或鼠标附近。

    参数：
    - lx, ly: 发射器坐标
    - angle: 瞄准角度（弧度）
    - mouse_dist: 鼠标到发射器的距离（用于调整瞄准线长度）
    """
    # 瞄准线的最大长度（画到屏幕外）
    max_length = WIDTH
    # 实际长度 = min(最大长度, 鼠标距离 * 1.2)，让瞄准线比鼠标位置稍远一点
    line_length = min(max_length, mouse_dist * 1.5 + 30)

    end_x = lx + line_length * math.cos(angle)
    end_y = ly - line_length * math.sin(angle)  # 屏幕Y轴向下，取负

    # ---- 虚线效果 ----
    # 用多段小线段模拟虚线
    dash_count = 20
    dash_length = line_length / dash_count
    gap_ratio = 0.4  # 实线占比
    for i in range(dash_count):
        start_t = i / dash_count
        end_t = (i + gap_ratio) / dash_count
        if end_t > 1:
            end_t = 1
        sx = lx + start_t * line_length * math.cos(angle)
        sy = ly - start_t * line_length * math.sin(angle)
        ex = lx + end_t * line_length * math.cos(angle)
        ey = ly - end_t * line_length * math.sin(angle)
        pygame.draw.line(screen, (255, 255, 255, 120),
                         (int(sx), int(sy)), (int(ex), int(ey)), 2)


def draw_flying_bubble(bx, by, color):
    """绘制飞行中的泡泡（带高光和运动拖尾效果）"""
    # 主泡泡
    pygame.draw.circle(screen, color, (int(bx), int(by)), BUBBLE_RADIUS)
    # 边框
    pygame.draw.circle(screen, tuple(max(0, c - 40) for c in color),
                       (int(bx), int(by)), BUBBLE_RADIUS, 2)
    # 高光
    hx = int(bx - BUBBLE_RADIUS * 0.3)
    hy = int(by - BUBBLE_RADIUS * 0.3)
    pygame.draw.circle(screen, (255, 255, 255, 160),
                       (hx, hy), BUBBLE_RADIUS // 3)
    # 小拖尾（运动方向的反方向一个小圆）
    trail_x = int(bx - flying_bubble["vx"] * 1.5)
    trail_y = int(by - flying_bubble["vy"] * 1.5)
    pygame.draw.circle(screen, tuple(min(255, c + 30) for c in color),
                       (trail_x, trail_y), BUBBLE_RADIUS // 2, 1)


def draw_bubble(bx, by, color):
    """绘制一个已停下的泡泡（带高光效果）"""
    # 主体
    pygame.draw.circle(screen, color, (int(bx), int(by)), BUBBLE_RADIUS)
    # 暗色边框（用颜色加深模拟）
    darker = tuple(max(0, c - 50) for c in color)
    pygame.draw.circle(screen, darker, (int(bx), int(by)), BUBBLE_RADIUS, 2)
    # 高光亮点（模拟光线反射，让泡泡有立体感）
    hx = int(bx - BUBBLE_RADIUS * 0.3)
    hy = int(by - BUBBLE_RADIUS * 0.3)
    pygame.draw.circle(screen, (255, 255, 255, 170),
                       (hx, hy), BUBBLE_RADIUS // 3)
    # 小高光（更亮的小点）
    hx2 = int(bx - BUBBLE_RADIUS * 0.15)
    hy2 = int(by - BUBBLE_RADIUS * 0.45)
    pygame.draw.circle(screen, (255, 255, 255, 220),
                       (hx2, hy2), BUBBLE_RADIUS // 6)


# ==================== 主程序 ====================
def main():
    global flying_bubble, launcher_color

    reset_game()
    flying_bubble = None
    # 发射器固定在底部中央
    launcher_x = WIDTH // 2
    launcher_y = HEIGHT - 40

    running = True
    while running:
        # ========== 事件处理 ==========
        mx, my = pygame.mouse.get_pos()

        # ---- 计算瞄准角度 ----
        # 使用 math.atan2(-dy, dx) 计算从发射器指向鼠标的角度
        #   atan2(y, x)：返回从 (0,0) 到 (x,y) 的向量的角度
        #   因为屏幕的 Y 轴向下，而我们习惯的角度是"上方为正"
        #   所以 dy 要取负号（把屏幕坐标翻转为数学坐标）
        dx = mx - launcher_x
        dy = my - launcher_y
        aim_angle = math.atan2(-dy, dx)  # ← 关键！dy 取负

        # 限制发射角度在合理范围（10° ~ 170°，即大致在上半圆）
        # 防止玩家水平或向下发射
        min_angle = math.radians(10)    # 10°（接近正上方偏右一点）
        max_angle = math.radians(170)   # 170°（接近正上方偏左一点）
        aim_angle = max(min_angle, min(max_angle, aim_angle))

        # 鼠标到发射器的距离（用于调整瞄准线长度）
        mouse_dist = math.hypot(dx, dy)

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

            elif event.type == pygame.KEYDOWN:
                # ---- 空格键：发射泡泡 ----
                if event.key == pygame.K_SPACE and flying_bubble is None:
                    # ============================================
                    # 🧮 三角函数核心代码 —— 将角度拆解为 X/Y 速度
                    # ============================================
                    # cos(角度) = 邻边/斜边 → 水平分量（X 方向的速度）
                    # sin(角度) = 对边/斜边 → 垂直分量（Y 方向的速度）
                    # 注意：vy 要取负号！因为屏幕坐标系中 Y 轴向下
                    #       向上飞 = Y 减小 = 负的速度
                    speed = 8
                    vx = speed * math.cos(aim_angle)   # X 方向速度
                    vy = -speed * math.sin(aim_angle)  # Y 方向速度（取负！）

                    # 创建飞行泡泡的字典
                    flying_bubble = {
                        "x": launcher_x,
                        "y": launcher_y,
                        "vx": vx,
                        "vy": vy,
                        "color": launcher_color
                    }
                    # 准备下一个泡泡的颜色
                    launcher_color = random.choice(BUBBLE_COLORS)

                # ---- R 键：重新开始 ----
                elif event.key == pygame.K_r:
                    reset_game()
                    flying_bubble = None

        # ========== 更新逻辑 ==========

        # ---- 更新飞行泡泡的位置 ----
        if flying_bubble is not None:
            flying_bubble["x"] += flying_bubble["vx"]
            flying_bubble["y"] += flying_bubble["vy"]

            bx = flying_bubble["x"]
            by = flying_bubble["y"]

            # ---- 碰撞检测 1：碰到顶部边界 ----
            if by - BUBBLE_RADIUS <= TOP_MARGIN:
                flying_bubble["y"] = TOP_MARGIN + BUBBLE_RADIUS
                gx, gy, col, row = snap_to_grid(bx, TOP_MARGIN + BUBBLE_RADIUS)
                if col >= 0 and row >= 0:
                    grid[row][col] = flying_bubble["color"]
                    bubble_list.append({"x": gx, "y": gy, "color": flying_bubble["color"]})
                flying_bubble = None

            # ---- 碰撞检测 2：碰到已存在的泡泡 ----
            elif flying_bubble is not None:
                collided = False
                for b in bubble_list:
                    # 计算飞行泡泡与已有泡泡的圆心距离
                    # math.hypot(dx, dy) = √(dx² + dy²)  ← 勾股定理
                    dist = math.hypot(bx - b["x"], by - b["y"])
                    # 两个泡泡碰撞的条件：圆心距离 < 直径
                    if dist < 2 * BUBBLE_RADIUS - 2:  # -2 是为了更自然的碰撞感
                        gx, gy, col, row = snap_to_grid(bx, by)
                        if col >= 0 and row >= 0:
                            grid[row][col] = flying_bubble["color"]
                            bubble_list.append({"x": gx, "y": gy, "color": flying_bubble["color"]})
                        flying_bubble = None
                        collided = True
                        break

            # ---- 超出屏幕左右边界时也停下并吸附 ----
            if flying_bubble is not None:
                if bx - BUBBLE_RADIUS <= 0 or bx + BUBBLE_RADIUS >= WIDTH:
                    gx, gy, col, row = snap_to_grid(bx, by)
                    if col >= 0 and row >= 0:
                        grid[row][col] = flying_bubble["color"]
                        bubble_list.append({"x": gx, "y": gy, "color": flying_bubble["color"]})
                    flying_bubble = None

        # ========== 绘制 ==========
        screen.fill(BG_COLOR)

        # ---- 绘制顶部边界线 ----
        pygame.draw.line(screen, GRAY, (0, TOP_MARGIN), (WIDTH, TOP_MARGIN), 2)

        # ---- 绘制六边形网格预览（半透明圆圈） ----
        draw_grid_preview()

        # ---- 绘制所有已停下的泡泡 ----
        for b in bubble_list:
            draw_bubble(b["x"], b["y"], b["color"])

        # ---- 绘制飞行中的泡泡 ----
        if flying_bubble is not None:
            draw_flying_bubble(flying_bubble["x"], flying_bubble["y"],
                               flying_bubble["color"])

        # ---- 绘制瞄准线 ----
        draw_aim_line(launcher_x, launcher_y, aim_angle, mouse_dist)

        # ---- 绘制发射器 ----
        draw_launcher(launcher_x, launcher_y, aim_angle)

        # ---- 绘制角度信息（调试/学习用） ----
        angle_deg = math.degrees(aim_angle)
        font = pygame.font.SysFont("microsoftyahei", 16)
        info_text = f"瞄准角度: {angle_deg:.1f}°  |  网格: {GRID_COLS}×{GRID_ROWS}"
        info_surf = font.render(info_text, True, LIGHT_GRAY)
        screen.blit(info_surf, (10, HEIGHT - 24))

        # ---- 操作提示 ----
        hint_text = "鼠标控制方向 | 空格发射 | R 重新开始"
        hint_surf = font.render(hint_text, True, GRAY)
        screen.blit(hint_surf, (WIDTH - hint_surf.get_width() - 10, HEIGHT - 24))

        # ---- 三角函数知识点提示（学习用） ----
        if flying_bubble is not None:
            trig_font = pygame.font.SysFont("microsoftyahei", 14)
            vx_val = flying_bubble["vx"]
            vy_val = flying_bubble["vy"]
            trig_text = f"vx=cos(θ)*speed={vx_val:.1f}  vy=-sin(θ)*speed={vy_val:.1f}"
            trig_surf = trig_font.render(trig_text, True, YELLOW)
            screen.blit(trig_surf, (10, 10))

        pygame.display.flip()
        clock.tick(FPS)

    pygame.quit()
    sys.exit()


if __name__ == "__main__":
    main()
