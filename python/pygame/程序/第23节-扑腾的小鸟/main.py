"""
第23节：扑腾的小鸟 —— Flappy Bird（第一节课）
=================================================
本程序演示 Flappy Bird 游戏的核心机制：
1. 重力模拟：velocity += gravity → y += velocity
2. 空格键让小鸟获得向上的速度（拍翅膀）
3. 水管 Rect 生成与向左移动
4. 用 pygame.Surface 自绘小鸟和水管，不依赖外部图片

注意：本节课暂不做碰撞检测（小鸟碰到水管不会死亡），
      碰撞检测将在第24节"水管森林"中实现。

你可以尝试修改以下参数，看看游戏效果的变化：
- GRAVITY（重力大小，默认 0.5）
- JUMP_STRENGTH（跳跃力度，默认 -8）
- PIPE_GAP（水管空隙大小，默认 160）
- PIPE_SPEED（水管移动速度，默认 3）
"""

import pygame
import random

# ============================================
# 1. 初始化 Pygame
# ============================================
pygame.init()

# ============================================
# 2. 窗口设置
# ============================================
WIDTH = 400          # 窗口宽度（像素）
HEIGHT = 600         # 窗口高度（像素）
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("扑腾的小鸟 —— Flappy Bird")

# ============================================
# 3. 颜色定义（RGB 格式）
# ============================================
SKY_BLUE = (135, 206, 235)     # 天空背景色
YELLOW = (255, 255, 0)         # 小鸟身体颜色
WING_COLOR = (255, 200, 0)     # 小鸟翅膀颜色（深黄）
BEAK_COLOR = (255, 150, 0)     # 小鸟嘴巴颜色（橙色）
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GREEN = (0, 180, 0)            # 水管颜色
DARK_GREEN = (0, 100, 0)       # 水管边框/帽檐颜色
BROWN = (139, 90, 43)          # 地面颜色
GRASS_GREEN = (34, 139, 34)    # 草地颜色

# ============================================
# 4. 小鸟属性
# ============================================
bird_x = 80                    # 小鸟的 x 坐标（左右位置固定，只有上下移动）
bird_y = HEIGHT // 2           # 小鸟的 y 坐标（初始在屏幕中间）
bird_velocity = 0              # 小鸟的垂直速度
                               # 正数 = 向下落，负数 = 向上飞

# ============================================
# 5. 物理参数
# ============================================
GRAVITY = 0.5                  # 重力加速度（每帧速度增加的量）
                               # 越大，小鸟下落越快
JUMP_STRENGTH = -8             # 跳跃力度（负数 = 向上）
                               # 绝对值越大，跳得越高

# ============================================
# 6. 水管参数
# ============================================
PIPE_WIDTH = 60                # 水管宽度
PIPE_GAP = 160                 # 上下水管之间的空隙大小（小鸟要通过这里）
                               # 越小，游戏越难
PIPE_SPEED = 3                 # 水管向左移动的速度（像素/帧）
PIPE_SPAWN_INTERVAL = 90       # 每隔多少帧生成一根新水管
                               # 60fps 下，90帧 ≈ 1.5秒

# 水管列表：存储所有活跃的水管
# 每个元素是一个字典，包含位置、Rect、Surface 等信息
pipes = []

# ============================================
# 7. 辅助函数
# ============================================

def create_bird_surface():
    """
    用代码画一只小鸟，返回带有透明背景的 Surface 对象。

    小鸟的构成：
    - 圆形身体（黄色）
    - 小椭圆翅膀（深黄色）
    - 白色眼睛 + 黑色瞳孔
    - 三角形嘴巴（橙色）
    """
    # 创建一个 34×34 的 Surface，SRCALPHA 支持透明
    bird_surf = pygame.Surface((34, 34), pygame.SRCALPHA)

    # ① 身体：黄色圆形，圆心在 (16, 16)，半径 13
    pygame.draw.circle(bird_surf, YELLOW, (16, 16), 13)

    # ② 翅膀：深黄色小椭圆
    pygame.draw.ellipse(bird_surf, WING_COLOR, (2, 12, 12, 7))

    # ③ 眼睛：白色大圆 + 黑色小瞳孔
    pygame.draw.circle(bird_surf, WHITE, (22, 12), 5)
    pygame.draw.circle(bird_surf, BLACK, (23, 12), 2)

    # ④ 嘴巴：橙色小三角形（向右突出）
    pygame.draw.polygon(bird_surf, BEAK_COLOR,
                        [(28, 14), (34, 17), (28, 20)])

    return bird_surf


def create_pipe_surface(pipe_height, is_top=True):
    """
    创建一根水管的 Surface 图像。

    参数：
        pipe_height: 水管的高度（像素）
        is_top: True=上水管（帽檐在底部），False=下水管（帽檐在顶部）

    返回：
        带有水管绘制的 Surface 对象
    """
    if pipe_height <= 0:
        pipe_height = 1  # 防止高度为 0 或负数

    # 创建水管 Surface
    pipe_surf = pygame.Surface((PIPE_WIDTH, pipe_height))

    # ① 填充水管主体颜色（绿色）
    pipe_surf.fill(GREEN)

    # ② 画水管边框（深绿色描边，3像素宽）
    pygame.draw.rect(pipe_surf, DARK_GREEN,
                     (0, 0, PIPE_WIDTH, pipe_height), 3)

    # ③ 画管道的"帽檐"（比管身宽 6 像素，看起来更立体）
    CAP_HEIGHT = min(25, pipe_height)  # 帽檐高度，不超过水管高度

    if is_top:
        # 上水管：帽檐在底部
        cap_y = pipe_height - CAP_HEIGHT
    else:
        # 下水管：帽檐在顶部
        cap_y = 0

    pygame.draw.rect(pipe_surf, DARK_GREEN,
                     (-3, cap_y, PIPE_WIDTH + 6, CAP_HEIGHT))

    return pipe_surf


def create_pipe(x_position):
    """
    生成一对水管（上水管 + 下水管），放在指定的 x 坐标位置。

    水管对的空隙位置是随机的，这样每根水管的难度都不一样。

    返回一个字典，包含完整的水管信息。
    """
    # 随机决定空隙中心的 y 坐标
    # 范围：顶部留 50 像素，底部留 50 像素（给地面留空间）
    gap_center_y = random.randint(100, HEIGHT - 150)

    # 计算空隙的上下边界
    gap_top = gap_center_y - PIPE_GAP // 2      # 空隙顶部
    gap_bottom = gap_center_y + PIPE_GAP // 2   # 空隙底部

    # 上水管：从屏幕顶部到空隙顶部
    top_pipe_height = gap_top
    # 下水管：从空隙底部到屏幕底部
    bottom_pipe_height = HEIGHT - gap_bottom

    # 创建水管 Surface
    top_surf = create_pipe_surface(top_pipe_height, is_top=True)
    bottom_surf = create_pipe_surface(bottom_pipe_height, is_top=False)

    # 返回水管信息字典
    return {
        "x": x_position,                                        # 水管左边缘的 x 坐标
        "top_rect": pygame.Rect(x_position, 0,                  # 上水管碰撞矩形
                                PIPE_WIDTH, top_pipe_height),
        "bottom_rect": pygame.Rect(x_position, gap_bottom,      # 下水管碰撞矩形
                                   PIPE_WIDTH, bottom_pipe_height),
        "top_surf": top_surf,                                   # 上水管图像
        "bottom_surf": bottom_surf,                             # 下水管图像
        "gap_center_y": gap_center_y,                           # 空隙中心（调试用）
        "scored": False                                         # 是否已经计分（第24节用）
    }


def draw_ground():
    """绘制地面（底部棕色土地 + 绿色草地）"""
    # 棕色土地
    pygame.draw.rect(screen, BROWN, (0, HEIGHT - 40, WIDTH, 40))
    # 绿色草地（比土地稍高一点）
    pygame.draw.rect(screen, GRASS_GREEN, (0, HEIGHT - 45, WIDTH, 8))


def draw_cloud(x, y, size):
    """用椭圆画一朵简笔云"""
    # 云由几个重叠的椭圆组成
    pygame.draw.ellipse(screen, WHITE, (x, y, size, size // 2))
    pygame.draw.ellipse(screen, WHITE, (x + size // 3, y - size // 4, size // 2, size // 2))
    pygame.draw.ellipse(screen, WHITE, (x + size // 2, y, size // 2, size // 2))
    pygame.draw.ellipse(screen, WHITE, (x + size // 4, y + size // 6, size // 2, size // 2))


# ============================================
# 8. 初始化游戏对象
# ============================================

# 创建小鸟素材
bird_image = create_bird_surface()
# 小鸟的绘制矩形（用于定位）
bird_rect = bird_image.get_rect(center=(bird_x, int(bird_y)))

# 生成第一根水管（放在屏幕右侧外面，让它慢慢滑入视野）
pipes.append(create_pipe(WIDTH + 100))

# 帧计数器（用于控制水管生成间隔）
frame_count = 0

# 创建云朵列表（装饰用，固定位置）
clouds = [
    (50, 60, 40),
    (180, 30, 50),
    (300, 70, 35),
]

# ============================================
# 9. 游戏主循环
# ============================================
clock = pygame.time.Clock()
FPS = 60
running = True

print("=" * 50)
print("  扑腾的小鸟 —— Flappy Bird")
print("  按 空格键 让小鸟飞起来！")
print("  点击窗口 × 按钮退出游戏")
print("=" * 50)

while running:
    # ========================================
    # 9.1 事件处理
    # ========================================
    for event in pygame.event.get():
        # 点击关闭按钮 → 退出游戏
        if event.type == pygame.QUIT:
            running = False

        # 键盘按下事件
        elif event.type == pygame.KEYDOWN:
            # 空格键：小鸟向上跳！
            if event.key == pygame.K_SPACE:
                bird_velocity = JUMP_STRENGTH  # 直接设置速度（不是累加！）
                # 注意：这里用 = 而不是 +=
                # 如果写成 +=，连续按空格会让速度越来越大
                # 小鸟会像火箭一样冲出屏幕

    # ========================================
    # 9.2 更新物理 —— 重力模拟
    # ========================================
    # ① 速度不断增加（重力加速度的效果）
    bird_velocity += GRAVITY

    # ② 位置根据速度变化
    bird_y += bird_velocity

    # ③ 更新小鸟的 Rect 位置（用于后续绘制）
    bird_rect.centery = int(bird_y)

    # ========================================
    # 9.3 更新水管
    # ========================================
    # ① 移动所有水管（向左匀速移动）
    for pipe in pipes:
        pipe["x"] -= PIPE_SPEED
        # 同步更新碰撞矩形的位置
        pipe["top_rect"].x = pipe["x"]
        pipe["bottom_rect"].x = pipe["x"]

    # ② 移除已经飞出屏幕左侧的水管
    #    列表推导式：保留 x > -PIPE_WIDTH 的水管
    pipes = [p for p in pipes if p["x"] > -PIPE_WIDTH]

    # ③ 每隔一定帧数，在屏幕右侧生成一根新水管
    frame_count += 1
    if frame_count >= PIPE_SPAWN_INTERVAL:
        pipes.append(create_pipe(WIDTH + 50))
        frame_count = 0  # 重置计数器

    # ========================================
    # 9.4 绘制画面
    # ========================================
    # ① 清屏（画天空背景）
    screen.fill(SKY_BLUE)

    # ② 画云朵（装饰）
    for cx, cy, cs in clouds:
        draw_cloud(cx, cy, cs)

    # ③ 画所有水管
    for pipe in pipes:
        # 上水管
        screen.blit(pipe["top_surf"], (pipe["x"], 0))
        # 下水管
        screen.blit(pipe["bottom_surf"],
                    (pipe["x"], pipe["bottom_rect"].y))

    # ④ 画地面（画在水管前面，盖住水管底部）
    draw_ground()

    # ⑤ 画小鸟（画在最前面）
    screen.blit(bird_image, bird_rect)

    # ⑥ 刷新显示（把画好的内容显示到屏幕上）
    pygame.display.flip()

    # ⑦ 控制帧率（每秒最多 60 帧）
    clock.tick(FPS)

# ============================================
# 10. 退出游戏
# ============================================
pygame.quit()
print("游戏已退出，再见！")
