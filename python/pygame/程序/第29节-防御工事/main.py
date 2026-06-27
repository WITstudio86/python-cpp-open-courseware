"""
第29节：防御工事 — 塔防游戏（第一部分）

功能：
  1. 用路径点列表定义敌人行走的路线
  2. 敌人沿路径点依次移动（S形路线）
  3. 点击空地放置炮塔（消耗金币）
  4. 金币系统（初始金币 + 随时间增长）

知识点：
  - 路径点（waypoint）列表
  - 点对点移动 + 目标切换
  - MOUSEBUTTONDOWN 事件处理
  - Sprite 类的使用
"""

import pygame
import math
import random

# ==================== 初始化 ====================
pygame.init()

# 窗口设置
WIDTH = 800
HEIGHT = 600
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("第29节：防御工事 - 塔防游戏")

# 颜色定义
GREEN = (100, 180, 100)          # 草地绿
DARK_GREEN = (70, 140, 70)       # 深绿（网格线）
BROWN = (160, 110, 55)           # 路线棕
DARK_BROWN = (110, 70, 30)       # 路线边缘
LIGHT_BROWN = (190, 140, 80)     # 路线中心
RED = (220, 50, 50)              # 敌人红
DARK_RED = (170, 30, 30)         # 敌人暗红
BLUE = (60, 120, 240)            # 炮塔蓝
DARK_BLUE = (30, 80, 180)        # 炮塔暗蓝
LIGHT_BLUE = (120, 180, 255)     # 炮塔亮蓝
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
YELLOW = (255, 220, 50)          # 金币金
ORANGE = (255, 160, 30)          # 提示橙
GRAY = (160, 160, 160)           # 灰色（不可放置）
DARK_GRAY = (80, 80, 80)         # 深灰

# 游戏设置
clock = pygame.time.Clock()
FPS = 60

# ==================== 路径点定义 ====================
# 路径是一串坐标点，敌人会依次走过这些点
# 设计一条 S 形路线：从左侧进入，经过 4 次拐弯，从右侧出去
PATH_WIDTH = 50   # 路线宽度（像素）

path = [
    (0, 100),      # ① 起点：屏幕左上角入口
    (200, 100),    # ② 第一个拐弯：走到这里后向下转
    (200, 300),    # ③ 第二个拐弯：向下走到底，再向右转
    (500, 300),    # ④ 第三个拐弯：向右走到这里，再向下转
    (500, 500),    # ⑤ 第四个拐弯：向下走到底，再向右转
    (700, 500),    # ⑥ 第五个拐弯：向右走向出口
    (800, 500),    # ⑦ 终点：屏幕右侧出口（敌人走出屏幕）
]

# ==================== 精灵组 ====================
all_sprites = pygame.sprite.Group()     # 所有精灵
enemy_group = pygame.sprite.Group()     # 敌人组
tower_group = pygame.sprite.Group()     # 炮塔组

# ==================== 金币系统 ====================
gold = 200                    # 初始金币
TOWER_COST = 50               # 放置炮塔需要 50 金币
gold_timer = 0                # 金币增长的计时器
GOLD_INCOME_RATE = 120        # 每 120 帧（约 2 秒）获得 1 金币

# ==================== 敌人出生系统 ====================
enemy_spawn_timer = 0
ENEMY_SPAWN_RATE = 90         # 每 90 帧（约 1.5 秒）生成一个敌人

# ==================== 类定义 ====================

class Enemy(pygame.sprite.Sprite):
    """敌人类：沿路径点依次移动"""

    def __init__(self):
        super().__init__()
        # 创建敌人图像（红色圆形，带暗色边框）
        self.radius = 10
        self.image = pygame.Surface((self.radius * 2, self.radius * 2),
                                     pygame.SRCALPHA)
        # 画主体圆
        pygame.draw.circle(self.image, RED,
                           (self.radius, self.radius), self.radius)
        # 画边框
        pygame.draw.circle(self.image, DARK_RED,
                           (self.radius, self.radius), self.radius, 2)
        # 画一个小箭头表示方向（朝向圆心偏右）
        pygame.draw.circle(self.image, (255, 150, 150),
                           (self.radius + 4, self.radius - 3), 3)

        self.rect = self.image.get_rect()

        # 速度：每帧移动多少个像素
        self.speed = 2

        # 当前要去的路径点索引
        # 从 1 开始，因为 0 是起点（敌人已经在起点位置了）
        self.target_index = 1

        # 敌人初始位置 = 路径起点
        self.rect.center = path[0]

    def update(self):
        """每帧调用：向当前目标路径点移动"""
        # 安全检查：目标索引不能越界
        if self.target_index >= len(path):
            self.kill()
            return

        # 1. 获取当前目标路径点
        target = path[self.target_index]

        # 2. 计算从当前位置到目标的方向向量
        dx = target[0] - self.rect.centerx
        dy = target[1] - self.rect.centery

        # 3. 计算距离（勾股定理）
        distance = math.sqrt(dx * dx + dy * dy)

        # 4. 判断是否到达目标点
        if distance < self.speed:
            # 到达当前目标点 → 切换到下一个路径点
            self.target_index += 1

            # 如果已经走完全部路径点，敌人到达终点 → 移除
            if self.target_index >= len(path):
                self.kill()
                return

            # 更新目标，重新计算方向
            target = path[self.target_index]
            dx = target[0] - self.rect.centerx
            dy = target[1] - self.rect.centery
            distance = math.sqrt(dx * dx + dy * dy)

        # 5. 沿方向移动一步
        # 用 (dx/distance) 做"归一化"，确保任何方向的速度都一样
        if distance > 0:
            self.rect.x += (dx / distance) * self.speed
            self.rect.y += (dy / distance) * self.speed


class Tower(pygame.sprite.Sprite):
    """炮塔类：放置在路边用于防御"""

    def __init__(self, x, y):
        super().__init__()
        # 创建炮塔图像（36x36 像素）
        self.image = pygame.Surface((36, 36), pygame.SRCALPHA)

        # 炮塔底座：蓝色圆角矩形
        pygame.draw.rect(self.image, BLUE, (3, 3, 30, 30),
                         border_radius=5)
        # 底座边框
        pygame.draw.rect(self.image, DARK_BLUE, (3, 3, 30, 30),
                         border_radius=5, width=2)
        # 炮塔中心（炮管基座）
        pygame.draw.circle(self.image, LIGHT_BLUE, (18, 18), 8)
        # 炮管
        pygame.draw.circle(self.image, BLUE, (18, 18), 5)
        pygame.draw.circle(self.image, (200, 220, 255), (18, 18), 2)

        self.rect = self.image.get_rect()
        self.rect.center = (x, y)


# ==================== 辅助函数 ====================

def draw_map():
    """绘制游戏地图：绿色草地 + 棕色路线"""
    # 1. 草地背景
    screen.fill(GREEN)

    # 2. 画网格线（让草地看起来更丰富，像策略游戏地图）
    for x in range(0, WIDTH, 40):
        pygame.draw.line(screen, DARK_GREEN, (x, 0), (x, HEIGHT), 1)
    for y in range(0, HEIGHT, 40):
        pygame.draw.line(screen, DARK_GREEN, (0, y), (WIDTH, y), 1)

    # 3. 画路线（用粗线条把路径点依次连起来）
    if len(path) >= 2:
        # 先画路线深色边缘（稍宽，模拟边框效果）
        pygame.draw.lines(screen, DARK_BROWN, False, path, PATH_WIDTH + 8)
        # 再画路线主体
        pygame.draw.lines(screen, BROWN, False, path, PATH_WIDTH)
        # 路线中心线（让路面有层次感）
        pygame.draw.lines(screen, LIGHT_BROWN, False, path, PATH_WIDTH - 16)

    # 4. 画路径点标记（黄色小圆点，帮助学生理解路径点的位置）
    for point in path:
        pygame.draw.circle(screen, YELLOW, point, 7)
        pygame.draw.circle(screen, BLACK, point, 7, 1)

    # 5. 起点标记（绿色三角形旗帜）
    start = path[0]
    flag_points = [
        (start[0], start[1] - 14),
        (start[0] + 12, start[1] - 6),
        (start[0], start[1] + 2)
    ]
    pygame.draw.polygon(screen, (0, 180, 0), flag_points)

    # 6. 终点标记（红色 X）
    end = path[-1]
    pygame.draw.circle(screen, (200, 0, 0), end, 12)
    pygame.draw.line(screen, WHITE, (end[0] - 6, end[1] - 6),
                     (end[0] + 6, end[1] + 6), 3)
    pygame.draw.line(screen, WHITE, (end[0] + 6, end[1] - 6),
                     (end[0] - 6, end[1] + 6), 3)


def can_place_tower(x, y):
    """检查某个 (x, y) 位置是否可以放置炮塔"""

    # 1. 检查是否在屏幕范围内
    if x < 20 or x > WIDTH - 20 or y < 20 or y > HEIGHT - 20:
        return False

    # 2. 检查是否在路线上（遍历每一段路径）
    for i in range(len(path) - 1):
        p1 = path[i]
        p2 = path[i + 1]

        # 构造这段路径的包围矩形（扩展 PATH_WIDTH/2 的宽度）
        min_x = min(p1[0], p2[0]) - PATH_WIDTH // 2 - 18
        max_x = max(p1[0], p2[0]) + PATH_WIDTH // 2 + 18
        min_y = min(p1[1], p2[1]) - PATH_WIDTH // 2 - 18
        max_y = max(p1[1], p2[1]) + PATH_WIDTH // 2 + 18

        # 如果点击位置在这个矩形内，说明在路线上 → 不能放置
        if min_x <= x <= max_x and min_y <= y <= max_y:
            return False

    # 3. 检查是否和已有的炮塔重叠
    for tower in tower_group:
        # 计算两个炮塔中心之间的距离
        dist = math.sqrt((x - tower.rect.centerx) ** 2 +
                         (y - tower.rect.centery) ** 2)
        if dist < 40:  # 至少间隔 40 像素
            return False

    return True


def draw_ui():
    """绘制游戏界面信息（金币、提示等）"""
    # 半透明背景条
    ui_bg = pygame.Surface((250, 130), pygame.SRCALPHA)
    ui_bg.fill((0, 0, 0, 120))
    screen.blit(ui_bg, (10, 10))

    # 金币显示
    font_large = pygame.font.SysFont("simhei", 28, bold=True)
    gold_text = font_large.render(f"💰 金币: {gold}", True, YELLOW)
    # 文字阴影（黑色描边效果）
    gold_shadow = font_large.render(f"💰 金币: {gold}", True, BLACK)
    screen.blit(gold_shadow, (22, 22))
    screen.blit(gold_text, (20, 20))

    # 炮塔价格
    font_small = pygame.font.SysFont("simhei", 18)
    cost_text = font_small.render(f"放置炮塔需要 {TOWER_COST} 金币", True,
                                  WHITE if gold >= TOWER_COST else RED)
    screen.blit(cost_text, (20, 58))

    # 炮塔数量
    count_text = font_small.render(f"已放置 {len(tower_group)} 个炮塔",
                                   True, WHITE)
    screen.blit(count_text, (20, 82))

    # 操作提示
    hint_text = font_small.render("点击空地 → 放置炮塔", True, ORANGE)
    screen.blit(hint_text, (20, 106))

    # 底部提示
    font_tiny = pygame.font.SysFont("simhei", 16)
    bottom_hint = font_tiny.render(
        "提示：敌人从左上角出发，沿棕色路线行走 | 金币不足时等待自动增长",
        True, DARK_GRAY)
    screen.blit(bottom_hint, (WIDTH // 2 - bottom_hint.get_width() // 2,
                               HEIGHT - 25))


# ==================== 主循环 ====================

def main():
    global gold, gold_timer, enemy_spawn_timer

    running = True
    # 预先生成第一个敌人
    enemy = Enemy()
    all_sprites.add(enemy)
    enemy_group.add(enemy)

    while running:
        # ===== 事件处理 =====
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

            elif event.type == pygame.MOUSEBUTTONDOWN:
                # 鼠标点击 → 尝试放置炮塔
                mouse_x, mouse_y = event.pos

                # 条件1：金币够
                # 条件2：位置合法（不在路线上）
                if gold >= TOWER_COST and can_place_tower(mouse_x, mouse_y):
                    tower = Tower(mouse_x, mouse_y)
                    all_sprites.add(tower)
                    tower_group.add(tower)
                    gold -= TOWER_COST  # 扣除金币

            elif event.type == pygame.KEYDOWN:
                # 按空格键：手动生成一个敌人（用于测试）
                if event.key == pygame.K_SPACE:
                    enemy = Enemy()
                    all_sprites.add(enemy)
                    enemy_group.add(enemy)

        # ===== 自动生成敌人 =====
        enemy_spawn_timer += 1
        if enemy_spawn_timer >= ENEMY_SPAWN_RATE:
            enemy_spawn_timer = 0
            enemy = Enemy()
            all_sprites.add(enemy)
            enemy_group.add(enemy)

        # ===== 金币被动增长 =====
        gold_timer += 1
        if gold_timer >= GOLD_INCOME_RATE:
            gold_timer = 0
            gold += 1  # 每约 2 秒获得 1 金币

        # ===== 更新所有精灵 =====
        all_sprites.update()

        # ===== 绘制画面 =====
        draw_map()                    # 1. 画地图（草地 + 路线）
        all_sprites.draw(screen)      # 2. 画精灵（敌人 + 炮塔）
        draw_ui()                     # 3. 画 UI 信息

        # 刷新屏幕
        pygame.display.flip()
        clock.tick(FPS)

    pygame.quit()


# ==================== 程序入口 ====================
if __name__ == "__main__":
    main()
