import pygame
import random
import sys
import math

# ============================================================
# 初始化 Pygame
# ============================================================
pygame.init()

# ============================================================
# 游戏常量配置
# ============================================================
SCREEN_WIDTH = 800   # 窗口宽度
SCREEN_HEIGHT = 600  # 窗口高度
FPS = 60             # 帧率

# 颜色定义（RGB）
COLOR_BG = (25, 25, 80)           # 深蓝色背景
COLOR_WHITE = (255, 255, 255)     # 白色
COLOR_BLACK = (0, 0, 0)           # 黑色
COLOR_RED = (255, 0, 0)           # 红色
COLOR_GREEN = (0, 255, 0)         # 绿色
COLOR_DARK_GREEN = (0, 100, 0)    # 深绿（西瓜条纹）
COLOR_YELLOW = (255, 255, 0)      # 黄色
COLOR_BROWN = (139, 69, 19)       # 棕色（篮子）
COLOR_BROWN_DARK = (101, 67, 33)  # 深棕（篮子边框）
COLOR_GRAY = (200, 200, 200)      # 灰色（引线）
COLOR_ORANGE = (255, 200, 0)      # 橙色（火花）
COLOR_LEAF_GREEN = (0, 150, 0)    # 叶子绿
COLOR_STEM_GREEN = (0, 100, 0)    # 茎绿

# 篮子属性
BASKET_WIDTH = 120   # 篮子宽度
BASKET_HEIGHT = 25   # 篮子高度
BASKET_SPEED = 8     # 篮子移动速度
BASKET_Y_OFFSET = 60 # 篮子距底部距离

# 速度配置
INITIAL_SPEED = 3        # 初始下落速度
SPEED_INCREMENT = 0.5    # 每次速度增幅
SPEED_INTERVAL = 10      # 速度增加间隔（秒）

# 生成配置
INITIAL_SPAWN_INTERVAL = 60  # 初始生成间隔（帧数）
MIN_SPAWN_INTERVAL = 25      # 最小生成间隔（帧数）
BOMB_PROBABILITY = 0.1       # 炸弹出现概率 10%

# 生命值
INITIAL_LIVES = 3


# ============================================================
# 游戏状态机：PLAYING（游戏中）/ GAME_OVER（游戏结束）
# ============================================================
class GameState:
    PLAYING = "playing"
    GAME_OVER = "game_over"


# ============================================================
# 游戏主类
# ============================================================
class FruitCatchGame:
    """接水果升级版游戏"""

    def __init__(self):
        """初始化游戏窗口和基本属性"""
        self.screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
        pygame.display.set_caption("接水果升级版")
        self.clock = pygame.time.Clock()
        self.font_small = pygame.font.Font(None, 36)    # 小字体（分数、提示）
        self.font_medium = pygame.font.Font(None, 48)   # 中字体（最终得分）
        self.font_large = pygame.font.Font(None, 72)    # 大字体（游戏结束）
        self.reset_game()

    def reset_game(self):
        """重置游戏到初始状态"""
        self.state = GameState.PLAYING           # 游戏状态
        self.score = 0                            # 当前分数
        self.lives = INITIAL_LIVES                # 剩余生命
        self.items = []                           # 下落物品列表
        self.basket_x = SCREEN_WIDTH // 2 - BASKET_WIDTH // 2  # 篮子水平位置
        self.game_start_time = pygame.time.get_ticks()  # 游戏开始时刻（毫秒）
        self.spawn_timer = 0                      # 生成计时器

    # ============================================================
    # 获取当前时刻的下落速度（随时间递增）
    # 规则：初始 speed=3，每过10秒 +0.5
    # ============================================================
    def get_current_speed(self):
        """根据游戏已进行时间计算当前下落速度"""
        elapsed_seconds = (pygame.time.get_ticks() - self.game_start_time) / 1000
        speed_level = int(elapsed_seconds // SPEED_INTERVAL)  # 经过了几个10秒
        return INITIAL_SPEED + speed_level * SPEED_INCREMENT

    # ============================================================
    # 获取当前生成间隔（随时间递减，增加难度）
    # ============================================================
    def get_current_spawn_interval(self):
        """根据游戏已进行时间计算当前物品生成间隔"""
        elapsed_seconds = (pygame.time.get_ticks() - self.game_start_time) / 1000
        # 每10秒减少5帧间隔，但不低于最小值
        reduction = int(elapsed_seconds // SPEED_INTERVAL) * 5
        return max(MIN_SPAWN_INTERVAL, INITIAL_SPAWN_INTERVAL - reduction)

    # ============================================================
    # 创建一个新物品（水果或炸弹）
    # 物品使用字典存储属性，包含类型、分数、速度、颜色等
    # ============================================================
    def create_item(self):
        """随机生成一个水果或炸弹，返回物品字典"""
        current_speed = self.get_current_speed()

        # 10% 概率生成炸弹
        if random.random() < BOMB_PROBABILITY:
            return {
                "type": "bomb",          # 物品类型：炸弹
                "score": -50,            # 接到扣50分
                "speed": current_speed,  # 当前下落速度
                "color": COLOR_BLACK,    # 黑色圆形
                "radius": 18,            # 半径18
                "x": random.randint(25, SCREEN_WIDTH - 25),  # 随机水平位置
                "y": 0                   # 从顶部开始下落
            }

        # 90% 概率随机生成一种水果
        fruit_type = random.choice(["apple", "banana", "watermelon"])

        if fruit_type == "apple":
            # 苹果：红色圆形，半径20，接住+10分
            return {
                "type": "apple",
                "score": 10,
                "speed": current_speed,
                "color": COLOR_RED,
                "radius": 20,
                "x": random.randint(25, SCREEN_WIDTH - 25),
                "y": 0
            }

        elif fruit_type == "banana":
            # 香蕉：黄色椭圆，宽30高20，接住+20分
            return {
                "type": "banana",
                "score": 20,
                "speed": current_speed,
                "color": COLOR_YELLOW,
                "radius_x": 15,   # 椭圆水平半轴（总宽30）
                "radius_y": 10,   # 椭圆垂直半轴（总高20）
                "x": random.randint(20, SCREEN_WIDTH - 20),
                "y": 0
            }

        else:  # watermelon
            # 西瓜：绿色大圆，半径30，接住+30分
            return {
                "type": "watermelon",
                "score": 30,
                "speed": current_speed,
                "color": COLOR_GREEN,
                "radius": 30,
                "x": random.randint(35, SCREEN_WIDTH - 35),
                "y": 0
            }

    # ============================================================
    # 获取篮子的碰撞矩形
    # ============================================================
    def get_basket_rect(self):
        """返回篮子当前的 pygame.Rect，用于碰撞检测"""
        return pygame.Rect(
            self.basket_x,
            SCREEN_HEIGHT - BASKET_Y_OFFSET,
            BASKET_WIDTH,
            BASKET_HEIGHT
        )

    # ============================================================
    # 获取物品的碰撞矩形（用于 pygame.Rect 碰撞检测）
    # ============================================================
    def get_item_rect(self, item):
        """根据物品字典返回其 pygame.Rect 包围盒"""
        if item["type"] == "banana":
            # 椭圆物品使用包围椭圆的最小矩形
            return pygame.Rect(
                item["x"] - item["radius_x"],
                item["y"] - item["radius_y"],
                item["radius_x"] * 2,
                item["radius_y"] * 2
            )
        else:
            # 圆形物品使用包围圆的正方形
            r = item["radius"]
            return pygame.Rect(
                item["x"] - r,
                item["y"] - r,
                r * 2,
                r * 2
            )

    # ============================================================
    # 绘制爱心（生命值图标）
    # 使用两个圆 + 一个三角形组合成爱心形状
    # ============================================================
    def draw_heart(self, x, y, size=14):
        """
        在指定位置绘制一个红色爱心
        x, y: 爱心中心位置
        size: 爱心大小
        """
        # 左侧圆弧
        pygame.draw.circle(self.screen, COLOR_RED,
                           (int(x - size * 0.3), int(y)), int(size * 0.3))
        # 右侧圆弧
        pygame.draw.circle(self.screen, COLOR_RED,
                           (int(x + size * 0.3), int(y)), int(size * 0.3))
        # 底部三角形（形成爱心尖端）
        pygame.draw.polygon(self.screen, COLOR_RED, [
            (int(x - size * 0.55), int(y + size * 0.25)),   # 左下
            (int(x + size * 0.55), int(y + size * 0.25)),   # 右下
            (int(x), int(y + size * 0.95))                   # 底部尖端
        ])

    # ============================================================
    # 主游戏循环
    # ============================================================
    def run(self):
        """启动游戏主循环"""
        running = True
        while running:
            # ---- 事件处理 ----
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False

                # 游戏结束状态下按 R 键重新开始
                if event.type == pygame.KEYDOWN:
                    if self.state == GameState.GAME_OVER and event.key == pygame.K_r:
                        self.reset_game()

            # ---- 输入处理（仅在游戏进行中） ----
            if self.state == GameState.PLAYING:
                keys = pygame.key.get_pressed()
                if keys[pygame.K_LEFT]:   # 左方向键
                    self.basket_x -= BASKET_SPEED
                if keys[pygame.K_RIGHT]:  # 右方向键
                    self.basket_x += BASKET_SPEED
                # 限制篮子不超出屏幕边界
                self.basket_x = max(0, min(SCREEN_WIDTH - BASKET_WIDTH, self.basket_x))

            # ---- 更新逻辑（仅在游戏进行中） ----
            if self.state == GameState.PLAYING:
                self.update()

            # ---- 绘制画面 ----
            self.draw()

            # 控制帧率
            self.clock.tick(FPS)

        # 退出游戏
        pygame.quit()
        sys.exit()

    # ============================================================
    # 更新游戏逻辑：生成物品、移动物品、碰撞检测、状态检查
    # ============================================================
    def update(self):
        """每帧更新游戏状态"""

        # -- 1. 按间隔生成新物品 --
        self.spawn_timer += 1
        spawn_interval = self.get_current_spawn_interval()
        if self.spawn_timer >= spawn_interval:
            self.spawn_timer = 0
            self.items.append(self.create_item())

        # -- 2. 更新物品位置并进行碰撞检测 --
        basket_rect = self.get_basket_rect()

        for item in self.items[:]:  # 使用切片遍历，以便安全删除
            # 物品向下移动
            item["y"] += item["speed"]

            # 获取物品的碰撞矩形
            item_rect = self.get_item_rect(item)

            # ---- 碰撞检测：物品碰到篮子 ----
            if item_rect.colliderect(basket_rect):
                if item["type"] == "bomb":
                    # 接到炸弹：扣50分，减1条命（分数不低于0）
                    self.score = max(0, self.score + item["score"])
                    self.lives -= 1
                else:
                    # 接到水果：加对应分数
                    self.score += item["score"]
                self.items.remove(item)
                continue  # 已处理，跳过后续检查

            # ---- 物品落到屏幕底部 ----
            if item["y"] > SCREEN_HEIGHT + 50:
                if item["type"] != "bomb":
                    # 漏掉水果（没接住）：减1条命
                    self.lives -= 1
                # 漏掉炸弹：不扣命，直接移除
                self.items.remove(item)

        # -- 3. 检查游戏是否结束 --
        if self.lives <= 0:
            self.lives = 0
            self.state = GameState.GAME_OVER

    # ============================================================
    # 绘制画面：背景、物品、篮子、UI
    # 所有图形使用 pygame.draw 绘制，不依赖外部图片
    # ============================================================
    def draw(self):
        """绘制当前帧的所有内容"""

        # ---- 背景 ----
        self.screen.fill(COLOR_BG)

        # ---- 绘制篮子 ----
        basket_rect = self.get_basket_rect()
        # 篮子主体（棕色矩形）
        pygame.draw.rect(self.screen, COLOR_BROWN, basket_rect)
        # 篮子上沿（深棕色边框装饰）
        rim_rect = pygame.Rect(
            self.basket_x - 5,
            SCREEN_HEIGHT - BASKET_Y_OFFSET,
            BASKET_WIDTH + 10,
            5
        )
        pygame.draw.rect(self.screen, COLOR_BROWN_DARK, rim_rect)
        # 篮子底部加厚边
        bottom_rim = pygame.Rect(
            self.basket_x - 3,
            SCREEN_HEIGHT - BASKET_Y_OFFSET + BASKET_HEIGHT - 4,
            BASKET_WIDTH + 6,
            4
        )
        pygame.draw.rect(self.screen, COLOR_BROWN_DARK, bottom_rim)

        # ---- 绘制所有下落物品 ----
        for item in self.items:
            self.draw_item(item)

        # ---- 左上角：分数显示 ----
        score_text = self.font_small.render(f"分数: {self.score}", True, COLOR_WHITE)
        self.screen.blit(score_text, (15, 15))

        # ---- 右上角：生命值（红色爱心） ----
        for i in range(self.lives):
            heart_x = SCREEN_WIDTH - 45 - i * 38
            heart_y = 22
            self.draw_heart(heart_x, heart_y, size=14)

        # ---- 游戏结束画面 ----
        if self.state == GameState.GAME_OVER:
            self.draw_game_over()

        # 更新显示
        pygame.display.flip()

    # ============================================================
    # 绘制单个物品（水果或炸弹）
    # ============================================================
    def draw_item(self, item):
        """根据物品类型绘制对应的图形"""

        if item["type"] == "apple":
            # -- 苹果：红色圆形 + 绿色茎 + 叶子 --
            cx, cy = int(item["x"]), int(item["y"])
            r = item["radius"]
            # 苹果主体
            pygame.draw.circle(self.screen, item["color"], (cx, cy), r)
            # 高光（左上亮斑）
            pygame.draw.circle(self.screen, (255, 150, 150), (cx - 5, cy - 6), r // 3)
            # 茎（竖直短线）
            pygame.draw.line(self.screen, COLOR_STEM_GREEN,
                             (cx, cy - r), (cx, cy - r - 8), 2)
            # 叶子（三角形）
            leaf_points = [
                (cx, cy - r - 3),
                (cx + 9, cy - r - 9),
                (cx + 5, cy - r - 1)
            ]
            pygame.draw.polygon(self.screen, COLOR_LEAF_GREEN, leaf_points)

        elif item["type"] == "banana":
            # -- 香蕉：黄色椭圆 --
            ellipse_rect = pygame.Rect(
                int(item["x"] - item["radius_x"]),
                int(item["y"] - item["radius_y"]),
                item["radius_x"] * 2,
                item["radius_y"] * 2
            )
            pygame.draw.ellipse(self.screen, item["color"], ellipse_rect)
            # 深黄色描边
            pygame.draw.ellipse(self.screen, (200, 200, 0), ellipse_rect, 2)
            # 高光
            highlight_rect = pygame.Rect(
                int(item["x"] - item["radius_x"] + 4),
                int(item["y"] - item["radius_y"] + 2),
                item["radius_x"] - 4,
                item["radius_y"] - 4
            )
            pygame.draw.ellipse(self.screen, (255, 255, 150), highlight_rect, 1)

        elif item["type"] == "watermelon":
            # -- 西瓜：绿色大圆 + 深绿色条纹 --
            cx, cy = int(item["x"]), int(item["y"])
            r = item["radius"]
            # 西瓜主体
            pygame.draw.circle(self.screen, item["color"], (cx, cy), r)
            # 深绿色边框
            pygame.draw.circle(self.screen, (0, 180, 0), (cx, cy), r, 2)
            # 深绿色弧形条纹（模拟西瓜纹路）
            for i in range(-2, 3):
                stripe_x = cx + i * 11
                stripe_rect = pygame.Rect(stripe_x - 7, cy - r + 5, 14, r * 2 - 10)
                # 只绘制在西瓜范围内的上半弧
                if abs(i * 11) < r - 5:
                    pygame.draw.arc(self.screen, COLOR_DARK_GREEN,
                                    stripe_rect, 0.2, math.pi - 0.2, 2)

        elif item["type"] == "bomb":
            # -- 炸弹：黑色圆形 + 灰色引线 + 橙色火花 --
            cx, cy = int(item["x"]), int(item["y"])
            r = item["radius"]
            # 炸弹主体
            pygame.draw.circle(self.screen, item["color"], (cx, cy), r)
            # 灰色高光（立体感）
            pygame.draw.circle(self.screen, (60, 60, 60), (cx - 5, cy - 5), r // 3)
            # 引线（灰色曲线，从顶部伸出）
            fuse_start = (cx + 3, cy - r)
            fuse_mid = (cx + 8, cy - r - 8)
            fuse_end = (cx + 14, cy - r - 14)
            pygame.draw.line(self.screen, COLOR_GRAY, fuse_start, fuse_mid, 3)
            pygame.draw.line(self.screen, COLOR_GRAY, fuse_mid, fuse_end, 2)
            # 引线末端的火花（闪烁效果：根据时间交替显示）
            tick = pygame.time.get_ticks() // 150
            if tick % 2 == 0:
                spark_color = COLOR_ORANGE
            else:
                spark_color = (255, 255, 100)  # 亮黄色火花
            pygame.draw.circle(self.screen, spark_color, fuse_end, 4)
            pygame.draw.circle(self.screen, (255, 255, 255), fuse_end, 2)

    # ============================================================
    # 绘制游戏结束画面
    # ============================================================
    def draw_game_over(self):
        """绘制游戏结束遮罩和提示文字"""
        # 半透明黑色遮罩
        overlay = pygame.Surface((SCREEN_WIDTH, SCREEN_HEIGHT))
        overlay.set_alpha(180)
        overlay.fill(COLOR_BLACK)
        self.screen.blit(overlay, (0, 0))

        # "游戏结束" 大字
        game_over_text = self.font_large.render("游戏结束", True, (255, 50, 50))
        text_rect = game_over_text.get_rect(center=(SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2 - 70))
        self.screen.blit(game_over_text, text_rect)

        # 最终得分
        final_score_text = self.font_medium.render(
            f"最终得分: {self.score}", True, COLOR_WHITE
        )
        score_rect = final_score_text.get_rect(center=(SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2))
        self.screen.blit(final_score_text, score_rect)

        # 重新开始提示
        restart_text = self.font_small.render(
            "按 R 键重新开始", True, COLOR_GRAY
        )
        restart_rect = restart_text.get_rect(center=(SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2 + 60))
        self.screen.blit(restart_text, restart_rect)


# ============================================================
# 程序入口
# ============================================================
if __name__ == "__main__":
    game = FruitCatchGame()
    game.run()
