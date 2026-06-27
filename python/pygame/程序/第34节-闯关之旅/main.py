"""
第34节：闯关之旅 —— 卷轴滚动、敌人与关卡地图

一个完整的横版平台跳跃闯关游戏，展示了：
1. 相机偏移与卷轴滚动：世界大于屏幕，相机跟随角色
2. Tile Map：用二维数组定义关卡地图
3. 踩踏消灭敌人：跳到敌人头顶消灭它
4. 金币收集：碰到金币加分
5. 到达终点：碰到旗帜过关
6. 死亡重生：碰到敌人侧面/底部重新开始

Tile Map 数字含义：
  0 = 空气（空白）
  1 = 地面方块（实心碰撞）
  2 = 平台方块（单向平台，可从下方穿过）
  3 = 金币（可收集）
  4 = 敌人（踩踏消灭）
  5 = 终点旗帜

操作方式：
- 左右方向键：移动
- 空格键：跳跃
- R键：重新开始
- ESC：退出

不需要任何外部文件，所有图形用 pygame Surface 绘制。
"""

import pygame
import sys
import math
import time

# ========== 初始化 Pygame ==========
pygame.init()
SCREEN_WIDTH, SCREEN_HEIGHT = 800, 600
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("第34节：闯关之旅 —— 横版冒险游戏")
clock = pygame.time.Clock()
FPS = 60

# ========== 颜色常量 ==========
SKY_BLUE = (135, 206, 235)          # 天空背景
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
YELLOW = (255, 255, 0)

PLAYER_COLOR = (255, 80, 80)        # 角色（红色）
PLAYER_OUTLINE = (180, 40, 40)      # 角色边框
GROUND_COLOR = (139, 90, 43)        # 地面方块（棕色）
GROUND_OUTLINE = (100, 60, 30)      # 地面边框
PLATFORM_COLOR = (100, 160, 100)    # 平台方块（绿色）
PLATFORM_OUTLINE = (60, 120, 60)    # 平台边框
COIN_COLOR = (255, 215, 0)          # 金币（金色）
COIN_OUTLINE = (200, 160, 0)        # 金币边框
ENEMY_COLOR = (200, 50, 150)        # 敌人（紫色）
ENEMY_OUTLINE = (140, 20, 100)      # 敌人边框
FLAG_COLOR = (50, 200, 50)          # 终点旗帜（亮绿）
FLAG_POLE_COLOR = (150, 150, 150)   # 旗杆（灰色）
UI_COLOR = (40, 40, 40)             # UI文字颜色
UI_BG = (255, 255, 255, 180)        # UI背景

# ========== 游戏常量 ==========
TILE_SIZE = 40          # 每个格子的像素大小
GRAVITY = 0.8           # 重力加速度
JUMP_FORCE = -14        # 跳跃力度
MOVE_SPEED = 5          # 移动速度

# ========== 关卡地图（Tile Map）==========
# 使用二维数组定义整个关卡
# 地图宽度 = 50 个 tile，高度 = 15 个 tile
# 世界总大小：50 * 40 = 2000 宽, 15 * 40 = 600 高

LEVEL_MAP = [
    # 列: 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],  # 行0：天花板
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],  # 行1
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],  # 行2：金币行
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],  # 行3
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],  # 行4
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 1],  # 行5
    [1, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],  # 行6：敌人
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],  # 行7：平台
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 1],  # 行8：敌人
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],  # 行9
    [1, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],  # 行10：平台+金币
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 1],  # 行11：敌人+终点
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],  # 行12：敌人
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],  # 行13
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1],  # 行14：地面（有缺口！）
]

# 世界尺寸
WORLD_WIDTH = len(LEVEL_MAP[0]) * TILE_SIZE   # 50 * 40 = 2000
WORLD_HEIGHT = len(LEVEL_MAP) * TILE_SIZE      # 15 * 40 = 600

# 玩家初始位置（Tile坐标）
PLAYER_START_TILE_X = 2
PLAYER_START_TILE_Y = 12
PLAYER_START_X = PLAYER_START_TILE_X * TILE_SIZE
PLAYER_START_Y = PLAYER_START_TILE_Y * TILE_SIZE


# ========== 游戏对象类 ==========

class Tile:
    """地图方块（地面或平台）"""

    def __init__(self, x, y, w, h, tile_type):
        self.rect = pygame.Rect(x, y, w, h)
        self.tile_type = tile_type  # "ground" 或 "platform"

    def draw(self, surface, camera_x, camera_y):
        """绘制方块（坐标减去相机偏移）"""
        draw_rect = pygame.Rect(
            self.rect.x - camera_x,
            self.rect.y - camera_y,
            self.rect.width,
            self.rect.height
        )

        if self.tile_type == "ground":
            color = GROUND_COLOR
            outline = GROUND_OUTLINE
        else:  # platform
            color = PLATFORM_COLOR
            outline = PLATFORM_OUTLINE

        pygame.draw.rect(surface, color, draw_rect)
        pygame.draw.rect(surface, outline, draw_rect, 2)


class Coin:
    """金币 —— 角色碰到后收集，加分"""

    def __init__(self, x, y):
        self.base_x = x + TILE_SIZE // 2  # 金币中心x
        self.base_y = y + TILE_SIZE // 2  # 金币中心y
        self.radius = 10
        self.collected = False
        self.create_time = time.time()

    def rect(self):
        """返回金币的碰撞矩形"""
        return pygame.Rect(
            self.base_x - self.radius,
            self.display_y() - self.radius,
            self.radius * 2,
            self.radius * 2
        )

    def display_y(self):
        """金币上下浮动效果"""
        offset = math.sin(time.time() * 4 + self.create_time) * 4
        return self.base_y + offset

    def draw(self, surface, camera_x, camera_y):
        """绘制金币（带浮动动画）"""
        if self.collected:
            return
        screen_x = self.base_x - camera_x
        screen_y = self.display_y() - camera_y
        pygame.draw.circle(surface, COIN_COLOR, (int(screen_x), int(screen_y)), self.radius)
        pygame.draw.circle(surface, COIN_OUTLINE, (int(screen_x), int(screen_y)), self.radius, 2)
        # 金币上的 $ 符号
        font = pygame.font.SysFont("Arial", 12, bold=True)
        dollar = font.render("$", True, COIN_OUTLINE)
        surface.blit(dollar, (int(screen_x) - 5, int(screen_y) - 8))


class Enemy:
    """敌人 —— 角色踩到头顶可消灭，碰到侧面/底部则死亡"""

    def __init__(self, x, y):
        self.start_x = x
        self.start_y = y
        self.x = x
        self.y = y
        self.width = 30
        self.height = 30
        self.alive = True
        # 巡逻相关
        self.patrol_dir = 1     # 1=向右, -1=向左
        self.patrol_speed = 1.5
        self.patrol_left = x - 30
        self.patrol_right = x + 60

    def rect(self):
        """返回敌人的碰撞矩形"""
        return pygame.Rect(self.x, self.y, self.width, self.height)

    def update(self):
        """敌人巡逻移动"""
        if not self.alive:
            return
        self.x += self.patrol_speed * self.patrol_dir
        # 到达巡逻边界时反转方向
        if self.x <= self.patrol_left:
            self.x = self.patrol_left
            self.patrol_dir = 1
        elif self.x >= self.patrol_right:
            self.x = self.patrol_right
            self.patrol_dir = -1

    def draw(self, surface, camera_x, camera_y):
        """绘制敌人"""
        if not self.alive:
            return
        draw_rect = pygame.Rect(
            self.x - camera_x, self.y - camera_y,
            self.width, self.height
        )
        # 身体
        pygame.draw.rect(surface, ENEMY_COLOR, draw_rect)
        pygame.draw.rect(surface, ENEMY_OUTLINE, draw_rect, 2)
        # 眼睛
        eye_y = int(self.y - camera_y + 8)
        pygame.draw.circle(surface, WHITE, (int(self.x - camera_x + 8), eye_y), 5)
        pygame.draw.circle(surface, WHITE, (int(self.x - camera_x + 22), eye_y), 5)
        pygame.draw.circle(surface, BLACK, (int(self.x - camera_x + 9), eye_y), 2)
        pygame.draw.circle(surface, BLACK, (int(self.x - camera_x + 23), eye_y), 2)
        # 嘴巴（小弧线）
        mouth_y = int(self.y - camera_y + 18)
        pygame.draw.arc(surface, BLACK,
                        (int(self.x - camera_x + 10), mouth_y, 10, 8),
                        0, math.pi, 2)


class Flag:
    """终点旗帜 —— 角色碰到即过关"""

    def __init__(self, x, y):
        self.x = x + TILE_SIZE // 2 - 5   # 旗杆x
        self.y = y                         # 旗杆顶部y
        self.pole_height = TILE_SIZE * 2   # 旗杆高度

    def rect(self):
        """返回旗帜的碰撞矩形"""
        return pygame.Rect(self.x - 15, self.y, 30, self.pole_height)

    def draw(self, surface, camera_x, camera_y):
        """绘制旗帜"""
        pole_x = self.x - camera_x
        pole_top_y = self.y - camera_y
        pole_bottom_y = self.y + self.pole_height - camera_y
        # 旗杆
        pygame.draw.line(surface, FLAG_POLE_COLOR,
                         (int(pole_x), int(pole_top_y)),
                         (int(pole_x), int(pole_bottom_y)), 6)
        # 旗帜三角
        flag_points = [
            (int(pole_x), int(pole_top_y + 5)),
            (int(pole_x + 25), int(pole_top_y + 15)),
            (int(pole_x), int(pole_top_y + 25))
        ]
        pygame.draw.polygon(surface, FLAG_COLOR, flag_points)
        pygame.draw.polygon(surface, (30, 150, 30), flag_points, 2)


class Player:
    """玩家角色"""

    def __init__(self, x, y):
        self.width = 28
        self.height = 38
        self.x = x
        self.y = y
        self.vx = 0
        self.vy = 0
        self.on_ground = False

    def rect(self):
        return pygame.Rect(self.x, self.y, self.width, self.height)

    def move(self, keys):
        """处理键盘输入"""
        self.vx = 0
        if keys[pygame.K_LEFT]:
            self.vx = -MOVE_SPEED
        if keys[pygame.K_RIGHT]:
            self.vx = MOVE_SPEED
        if keys[pygame.K_SPACE] and self.on_ground:
            self.vy = JUMP_FORCE
            self.on_ground = False

    def apply_gravity(self):
        """应用重力"""
        self.vy += GRAVITY
        self.y += self.vy
        if self.vy > 15:
            self.vy = 15

    def apply_horizontal(self):
        """应用水平移动"""
        self.x += self.vx
        # 不超出世界边界
        if self.x < 0:
            self.x = 0
        if self.x + self.width > WORLD_WIDTH:
            self.x = WORLD_WIDTH - self.width

    def draw(self, surface, camera_x, camera_y):
        """绘制角色"""
        draw_rect = pygame.Rect(
            self.x - camera_x, self.y - camera_y,
            self.width, self.height
        )
        pygame.draw.rect(surface, PLAYER_COLOR, draw_rect)
        pygame.draw.rect(surface, PLAYER_OUTLINE, draw_rect, 2)
        # 眼睛
        eye_y = int(self.y - camera_y + 8)
        pygame.draw.circle(surface, WHITE, (int(self.x - camera_x + 7), eye_y), 4)
        pygame.draw.circle(surface, WHITE, (int(self.x - camera_x + 21), eye_y), 4)
        pygame.draw.circle(surface, BLACK, (int(self.x - camera_x + 8), eye_y), 2)
        pygame.draw.circle(surface, BLACK, (int(self.x - camera_x + 22), eye_y), 2)


# ========== 游戏管理器 ==========
class Game:
    """管理整个游戏状态"""

    def __init__(self):
        self.reset()

    def reset(self):
        """重置游戏到初始状态"""
        self.player = Player(PLAYER_START_X, PLAYER_START_Y)

        # 基于Tile Map生成游戏对象
        self.tiles = []          # 地面和平台方块
        self.coins = []          # 金币列表
        self.enemies = []        # 敌人列表
        self.flag = None         # 终点旗帜

        # 保存初始状态（用于重生时恢复）
        self.initial_coins = []
        self.initial_enemies = []

        self._build_world()

        # 保存初始状态的副本
        self._save_initial_state()

        # 相机偏移
        self.camera_x = 0
        self.camera_y = 0

        # 游戏状态
        self.score = 0
        self.game_over = False
        self.level_complete = False
        self.death_message_timer = 0

    def _build_world(self):
        """从Tile Map生成所有游戏对象"""
        for row in range(len(LEVEL_MAP)):
            for col in range(len(LEVEL_MAP[row])):
                tile_type = LEVEL_MAP[row][col]
                x = col * TILE_SIZE
                y = row * TILE_SIZE

                if tile_type == 1:  # 地面方块
                    self.tiles.append(Tile(x, y, TILE_SIZE, TILE_SIZE, "ground"))
                elif tile_type == 2:  # 平台方块（单向）
                    self.tiles.append(Tile(x, y, TILE_SIZE, TILE_SIZE, "platform"))
                elif tile_type == 3:  # 金币
                    self.coins.append(Coin(x, y))
                elif tile_type == 4:  # 敌人
                    self.enemies.append(Enemy(x, y))
                elif tile_type == 5:  # 终点旗帜
                    self.flag = Flag(x, y)

    def _save_initial_state(self):
        """保存金币和敌人的初始状态，用于重生时恢复"""
        self.initial_coins = [Coin(c.base_x - TILE_SIZE // 2, c.base_y - TILE_SIZE // 2)
                              for c in self.coins]
        self.initial_enemies = [Enemy(e.start_x, e.start_y) for e in self.enemies]

    def update_camera(self):
        """更新相机位置 —— 卷轴滚动"""
        # 目标：让角色保持在屏幕左侧约1/3处
        target_camera_x = self.player.x - SCREEN_WIDTH // 3

        # 平滑相机移动（缓动效果）
        self.camera_x += (target_camera_x - self.camera_x) * 0.1

        # 限制相机不超出世界边界
        self.camera_x = max(0, min(self.camera_x, WORLD_WIDTH - SCREEN_WIDTH))
        self.camera_y = max(0, min(self.camera_y, WORLD_HEIGHT - SCREEN_HEIGHT))

    def handle_platform_collisions(self):
        """处理角色与所有平台方块的碰撞"""
        player_rect = self.player.rect()
        on_ground = False

        for tile in self.tiles:
            tile_rect = tile.rect

            # ---- 垂直碰撞：站在上面 ----
            # 对于"platform"类型：只在下落时碰撞（单向平台）
            # 对于"ground"类型：总是碰撞
            should_check_vertical = True
            if tile.tile_type == "platform":
                should_check_vertical = (self.player.vy > 0)

            if should_check_vertical and self.player.vy > 0:
                prev_bottom = self.player.y - self.player.vy + self.player.height
                overlap_x = (player_rect.right > tile_rect.left and
                             player_rect.left < tile_rect.right)

                if overlap_x:
                    if prev_bottom <= tile_rect.top and player_rect.bottom >= tile_rect.top:
                        self.player.y = tile_rect.top - self.player.height
                        self.player.vy = 0
                        on_ground = True
                        continue

            # ---- 水平碰撞：侧面挡住 ----
            # 只对"ground"类型做水平碰撞（平台可以穿过）
            if tile.tile_type == "ground":
                if player_rect.colliderect(tile_rect):
                    prev_rect = pygame.Rect(
                        self.player.x - self.player.vx,
                        self.player.y,
                        self.player.width,
                        self.player.height
                    )
                    # 从左边撞来
                    if prev_rect.right <= tile_rect.left:
                        self.player.x = tile_rect.left - self.player.width
                    # 从右边撞来
                    elif prev_rect.left >= tile_rect.right:
                        self.player.x = tile_rect.right

        return on_ground

    def handle_enemy_collisions(self):
        """处理与敌人的碰撞 —— 踩踏消灭 vs 被伤害"""
        for enemy in self.enemies[:]:  # 用[:]遍历副本，以便安全删除
            if not enemy.alive:
                continue

            if self.player.rect().colliderect(enemy.rect()):
                # 判断是否从上方踩下来
                # 条件：角色在下落 且 角色底部接近敌人顶部
                if (self.player.vy > 0 and
                        self.player.rect().bottom - enemy.rect().top < 18):
                    # 踩踏消灭！
                    enemy.alive = False
                    self.player.vy = -8  # 弹跳效果
                    self.score += 100
                else:
                    # 碰到侧面或底部 → 死亡
                    self.game_over = True
                    self.death_message_timer = 90  # 显示死亡信息1.5秒

    def handle_coin_collection(self):
        """处理金币收集"""
        for coin in self.coins[:]:
            if coin.collected:
                continue
            if self.player.rect().colliderect(coin.rect()):
                coin.collected = True
                self.score += 50

    def handle_flag(self):
        """检查是否到达终点"""
        if self.flag and self.player.rect().colliderect(self.flag.rect()):
            self.level_complete = True

    def restart(self):
        """重新开始（死亡后）"""
        self.player.x = PLAYER_START_X
        self.player.y = PLAYER_START_Y
        self.player.vx = 0
        self.player.vy = 0
        self.player.on_ground = False
        self.camera_x = 0
        self.camera_y = 0
        self.game_over = False

        # 恢复敌人
        self.enemies = [Enemy(e.start_x, e.start_y) for e in self.initial_enemies]
        # 恢复金币
        self.coins = [Coin(c.base_x - TILE_SIZE // 2, c.base_y - TILE_SIZE // 2)
                      for c in self.initial_coins]
        # 分数保留（也可以重置，这里选择保留）
        # self.score = 0

    def update(self):
        """每帧更新游戏状态"""
        if self.game_over:
            self.death_message_timer -= 1
            if self.death_message_timer <= 0:
                self.restart()
            return

        if self.level_complete:
            return

        # 更新敌人巡逻
        for enemy in self.enemies:
            enemy.update()

        # 更新相机
        self.update_camera()

        # 角色移动
        keys = pygame.key.get_pressed()
        self.player.move(keys)
        self.player.apply_gravity()
        self.player.apply_horizontal()

        # 碰撞检测
        self.player.on_ground = self.handle_platform_collisions()
        self.handle_enemy_collisions()
        self.handle_coin_collection()
        self.handle_flag()

        # 掉出世界 → 死亡
        if self.player.y > WORLD_HEIGHT + 100:
            self.game_over = True
            self.death_message_timer = 60

    def draw(self, surface):
        """绘制整个游戏画面"""
        # 天空背景
        surface.fill(SKY_BLUE)

        # 绘制所有方块
        for tile in self.tiles:
            # 只绘制在屏幕范围内的方块（性能优化）
            if (tile.rect.right - self.camera_x > -TILE_SIZE and
                    tile.rect.left - self.camera_x < SCREEN_WIDTH + TILE_SIZE and
                    tile.rect.bottom - self.camera_y > -TILE_SIZE and
                    tile.rect.top - self.camera_y < SCREEN_HEIGHT + TILE_SIZE):
                tile.draw(surface, self.camera_x, self.camera_y)

        # 绘制金币
        for coin in self.coins:
            coin.draw(surface, self.camera_x, self.camera_y)

        # 绘制敌人
        for enemy in self.enemies:
            enemy.draw(surface, self.camera_x, self.camera_y)

        # 绘制终点旗帜
        if self.flag:
            self.flag.draw(surface, self.camera_x, self.camera_y)

        # 绘制角色
        self.player.draw(surface, self.camera_x, self.camera_y)

        # 绘制UI
        self.draw_ui(surface)

        # 绘制游戏结束/通关信息
        if self.game_over:
            self.draw_message(surface, "💀 你挂了！重新开始中...", (255, 80, 80))
        elif self.level_complete:
            self.draw_message(surface, "🎉 通关！恭喜你！", (50, 255, 50))

    def draw_ui(self, surface):
        """绘制UI信息"""
        font = pygame.font.SysFont("Microsoft YaHei", 20)
        small_font = pygame.font.SysFont("Microsoft YaHei", 15)

        # 分数
        score_text = f"得分: {self.score}"
        score_surf = font.render(score_text, True, UI_COLOR)
        # 半透明背景
        bg_rect = pygame.Rect(5, 5, score_surf.get_width() + 16, 36)
        bg_surf = pygame.Surface((bg_rect.width, bg_rect.height))
        bg_surf.set_alpha(180)
        bg_surf.fill((255, 255, 255))
        surface.blit(bg_surf, (bg_rect.x, bg_rect.y))
        surface.blit(score_surf, (13, 11))

        # 金币收集进度
        total_coins = len(self.initial_coins)
        collected = sum(1 for c in self.coins if c.collected)
        coin_text = f"金币: {collected}/{total_coins}"
        coin_surf = font.render(coin_text, True, UI_COLOR)
        coin_y = bg_rect.bottom + 8
        coin_bg = pygame.Rect(5, coin_y, coin_surf.get_width() + 16, 36)
        coin_bg_surf = pygame.Surface((coin_bg.width, coin_bg.height))
        coin_bg_surf.set_alpha(180)
        coin_bg_surf.fill((255, 255, 255))
        surface.blit(coin_bg_surf, (coin_bg.x, coin_bg.y))
        surface.blit(coin_surf, (13, coin_y + 5))

        # 操作提示（屏幕底部）
        hint_text = "← → 移动 | 空格跳跃 | R 重新开始 | ESC 退出"
        hint_surf = small_font.render(hint_text, True, UI_COLOR)
        hint_x = SCREEN_WIDTH // 2 - hint_surf.get_width() // 2
        hint_y = SCREEN_HEIGHT - 30
        # 半透明背景
        hint_bg = pygame.Rect(hint_x - 8, hint_y - 4,
                              hint_surf.get_width() + 16, hint_surf.get_height() + 8)
        hint_bg_surf = pygame.Surface((hint_bg.width, hint_bg.height))
        hint_bg_surf.set_alpha(160)
        hint_bg_surf.fill((255, 255, 255))
        surface.blit(hint_bg_surf, (hint_bg.x, hint_bg.y))
        surface.blit(hint_surf, (hint_x, hint_y))

    def draw_message(self, surface, text, color):
        """在屏幕中央显示大号提示信息"""
        font = pygame.font.SysFont("Microsoft YaHei", 40, bold=True)
        text_surf = font.render(text, True, color)
        # 黑色描边效果
        outline_surf = font.render(text, True, BLACK)
        x = SCREEN_WIDTH // 2 - text_surf.get_width() // 2
        y = SCREEN_HEIGHT // 2 - text_surf.get_height() // 2
        for dx, dy in [(-1, -1), (-1, 1), (1, -1), (1, 1)]:
            surface.blit(outline_surf, (x + dx, y + dy))
        surface.blit(text_surf, (x, y))


# ========== 主函数 ==========
def main():
    """游戏主循环"""
    game = Game()
    running = True

    while running:
        # ---- 事件处理 ----
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    running = False
                if event.key == pygame.K_r:
                    # 按R键重新开始
                    game.reset()

        # ---- 更新游戏状态 ----
        game.update()

        # ---- 绘制画面 ----
        game.draw(screen)
        pygame.display.flip()
        clock.tick(FPS)

    pygame.quit()
    sys.exit()


# ========== 程序入口 ==========
if __name__ == "__main__":
    main()
