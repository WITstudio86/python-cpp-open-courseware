"""
第31节：弹幕来袭 — Boss 弹幕战
功能：
  1. 玩家飞机：方向键移动，空格键发射子弹
  2. Boss 敌人：大型飞机，屏幕上方左右移动
  3. 多样子弹模式：
     - 扇形弹幕：向下方扇形发射 5 颗子弹（普通攻击）
     - 圆形弹幕：360° 均匀发射 20 颗子弹（大招）
     - 直线弹幕：瞄准玩家方向发射
  4. Boss 血条：屏幕顶部大血条，颜色随血量变化
  5. 玩家击中 Boss 扣血，血量归零后 Boss 爆炸消失

知识点：
  - 弹幕生成函数（传入角度、数量、速度 → 批量生成子弹）
  - 扇形弹幕 = 孔雀开屏（60° 范围向下展开）
  - 圆形弹幕 = 烟花绽放（360° 均匀分布）
  - Boss 血条绘制（宽度按血量比例变化）
  - Sprite 精灵类的继承与精灵组管理
  - 三角函数 sin/cos 在游戏中的应用
"""

import pygame
import sys
import math
import random

# ==================== 初始化 Pygame ====================
pygame.init()

# ==================== 常量定义 ====================
WIDTH = 800       # 窗口宽度（像素）
HEIGHT = 700      # 窗口高度（像素）— 留出上方空间给 Boss 和血条
FPS = 60          # 帧率（每秒刷新次数）

# ==================== 颜色定义（RGB 格式） ====================
BLACK       = (0, 0, 0)
WHITE       = (255, 255, 255)
GRAY        = (100, 100, 100)
DARK_GRAY   = (60, 60, 60)
RED         = (255, 50, 50)
GREEN       = (50, 255, 50)
YELLOW      = (255, 255, 50)
BLUE        = (50, 150, 255)
CYAN        = (50, 255, 255)
ORANGE      = (255, 150, 50)
PURPLE      = (200, 100, 255)
PINK        = (255, 100, 200)
LIGHT_RED   = (255, 100, 100)
GOLD        = (255, 200, 50)

# ==================== 创建窗口和时钟 ====================
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("第31节：弹幕来袭 — Boss 弹幕战")
clock = pygame.time.Clock()

# ==================== 精灵组定义 ====================
all_sprites = pygame.sprite.Group()     # 所有精灵（用于统一绘制）
player_bullets = pygame.sprite.Group()  # 玩家子弹组
enemy_bullets = pygame.sprite.Group()   # 敌人子弹组（弹幕）
boss_group = pygame.sprite.Group()      # Boss 组


# ==================== 工具函数：绘制素材 ====================

def create_player_surface():
    """
    用 Surface 绘制玩家飞机（三角形战斗机）

    造型：一个尖头向前的三角形 + 两侧小翼
          △
         ╱ ╲
        ╱▏ ▏╲
    """
    surf = pygame.Surface((40, 44), pygame.SRCALPHA)  # SRCALPHA 支持透明

    # 主体（蓝色三角形，尖头朝上）
    body_points = [(20, 0), (0, 35), (10, 30), (20, 44), (30, 30), (40, 35)]
    pygame.draw.polygon(surf, BLUE, body_points)

    # 驾驶舱（浅蓝色小圆）
    pygame.draw.circle(surf, CYAN, (20, 18), 6)

    # 引擎火焰（橙色）
    pygame.draw.polygon(surf, ORANGE, [(14, 36), (20, 44), (26, 36)])

    # 两侧机翼高亮
    pygame.draw.line(surf, CYAN, (20, 0), (3, 32), 2)
    pygame.draw.line(surf, CYAN, (20, 0), (37, 32), 2)

    return surf


def create_boss_surface():
    """
    用 Surface 绘制 Boss 大型敌机

    造型：一个庞大的飞行器，有驾驶舱、机翼、引擎
         ╔══════════╗
        ╱ ╲  ╱▔▔▔╲  ╱ ╲
       ╱   ╲╱█████╲╱   ╲
      ╱    ╱  ███  ╲    ╲
    """
    surf = pygame.Surface((120, 80), pygame.SRCALPHA)

    # 主体（深红色大菱形/六边形）
    body_points = [
        (60, 0),     # 顶部尖角
        (110, 20),   # 右上
        (115, 40),   # 右中
        (110, 60),   # 右下
        (60, 75),    # 底部
        (10, 60),    # 左下
        (5, 40),     # 左中
        (10, 20),    # 左上
    ]
    pygame.draw.polygon(surf, (180, 30, 30), body_points)

    # 装饰条纹（亮红色）
    pygame.draw.polygon(surf, (220, 60, 60), body_points, 3)

    # 驾驶舱（黄色横条）
    pygame.draw.rect(surf, GOLD, (30, 22, 60, 15), border_radius=5)
    pygame.draw.rect(surf, (200, 150, 30), (30, 22, 60, 15), 2, border_radius=5)

    # "眼睛"（两个发光点）
    pygame.draw.circle(surf, (255, 230, 100), (40, 30), 5)
    pygame.draw.circle(surf, (255, 230, 100), (80, 30), 5)

    # 下方引擎（两个）
    pygame.draw.rect(surf, DARK_GRAY, (20, 55, 20, 10))
    pygame.draw.rect(surf, DARK_GRAY, (80, 55, 20, 10))
    # 引擎火焰
    pygame.draw.polygon(surf, ORANGE, [(22, 65), (30, 78), (38, 65)])
    pygame.draw.polygon(surf, ORANGE, [(82, 65), (90, 78), (98, 65)])

    # 顶部炮口标记
    pygame.draw.circle(surf, PINK, (60, 8), 5)

    return surf


def create_bullet_surface(color, size=(6, 14)):
    """创建一个子弹的 Surface（长椭圆形）"""
    surf = pygame.Surface(size, pygame.SRCALPHA)
    # 子弹主体（圆角效果用椭圆模拟）
    pygame.draw.ellipse(surf, color, (0, 0, size[0], size[1]))
    # 高光
    pygame.draw.ellipse(surf, WHITE, (size[0]//2 - 1, 1, 2, size[1]//3))
    return surf


def create_explosion_particles():
    """创建爆炸粒子 Surface 列表（用于 Boss 爆炸动画）"""
    particles = []
    colors = [RED, ORANGE, YELLOW, GOLD, (255, 255, 200)]
    for _ in range(30):
        size = random.randint(3, 10)
        surf = pygame.Surface((size * 2, size * 2), pygame.SRCALPHA)
        pygame.draw.circle(surf, random.choice(colors), (size, size), size)
        particles.append(surf)
    return particles


# ==================== 精灵类定义 ====================

class Player(pygame.sprite.Sprite):
    """
    玩家飞机精灵

    操作：
    - ↑↓←→ 方向键：上下左右移动
    - 空格键：发射子弹
    """
    def __init__(self):
        super().__init__()
        self.image = create_player_surface()
        self.rect = self.image.get_rect()
        self.rect.centerx = WIDTH // 2          # 水平居中
        self.rect.bottom = HEIGHT - 30          # 屏幕底部上方 30 像素
        self.speed = 6                           # 移动速度
        self.shoot_cooldown = 0                  # 发射冷却计时器
        self.shoot_delay = 15                    # 发射间隔（帧数）

    def update(self):
        """每帧更新：处理键盘输入、移动、发射"""
        keys = pygame.key.get_pressed()

        # —— 移动 ——
        if keys[pygame.K_LEFT] and self.rect.left > 0:
            self.rect.x -= self.speed
        if keys[pygame.K_RIGHT] and self.rect.right < WIDTH:
            self.rect.x += self.speed
        if keys[pygame.K_UP] and self.rect.top > 0:
            self.rect.y -= self.speed
        if keys[pygame.K_DOWN] and self.rect.bottom < HEIGHT:
            self.rect.y += self.speed

        # —— 发射子弹 ——
        if self.shoot_cooldown > 0:
            self.shoot_cooldown -= 1              # 冷却计时

        if keys[pygame.K_SPACE] and self.shoot_cooldown == 0:
            self.shoot()
            self.shoot_cooldown = self.shoot_delay  # 重置冷却

    def shoot(self):
        """发射一颗子弹（从机头向上飞出）"""
        bullet = Bullet(
            x=self.rect.centerx,
            y=self.rect.top - 5,                 # 从机头上方发出
            vx=0,
            vy=-8,                               # 向上飞（负速度）
            color=CYAN,
            is_player=True
        )
        player_bullets.add(bullet)
        all_sprites.add(bullet)


class Bullet(pygame.sprite.Sprite):
    """
    子弹精灵

    参数：
    - x, y: 初始位置
    - vx, vy: 水平/垂直速度（像素/帧）
    - color: 子弹颜色
    - is_player: 是否是玩家的子弹（影响精灵组归属）
    """
    def __init__(self, x, y, vx, vy, color, is_player=False):
        super().__init__()
        self.vx = vx                             # 水平速度
        self.vy = vy                             # 垂直速度
        self.color = color
        self.is_player = is_player

        # 根据速度方向旋转子弹外观
        # 子弹应该是椭圆形的，朝向飞行方向
        speed_total = math.hypot(vx, vy)         # 总速度（用于计算方向）
        if speed_total > 0:
            # 计算飞行角度（用于旋转子弹）
            angle = math.degrees(math.atan2(vy, vx)) + 90
            # 创建基本子弹 Surface
            base = create_bullet_surface(color)
            self.image = pygame.transform.rotate(base, -angle)
        else:
            self.image = create_bullet_surface(color)

        self.rect = self.image.get_rect(center=(x, y))

    def update(self):
        """每帧移动子弹，飞出屏幕则销毁"""
        self.rect.x += self.vx
        self.rect.y += self.vy

        # 飞出屏幕边界 → 自动销毁（防止积攒过多精灵导致卡顿）
        if (self.rect.bottom < 0 or self.rect.top > HEIGHT or
            self.rect.right < 0 or self.rect.left > WIDTH):
            self.kill()


class Boss(pygame.sprite.Sprite):
    """
    Boss 敌机精灵

    特性：
    - 大型飞机，在屏幕上方左右移动
    - 拥有独立血量（hp / max_hp）
    - 根据血量阶段切换弹幕模式
    - 血量归零后爆炸消失
    """
    def __init__(self):
        super().__init__()
        self.image = create_boss_surface()
        self.rect = self.image.get_rect()
        self.rect.centerx = WIDTH // 2           # 水平居中
        self.rect.top = 40                       # 屏幕顶部下方（血条下方）
        self.direction = 1                        # 移动方向：1=右，-1=左
        self.move_speed = 2                       # 水平移动速度

        # —— 血量系统 ——
        self.max_hp = 300                         # 最大血量
        self.hp = self.max_hp                     # 当前血量

        # —— 攻击系统 ——
        self.attack_timer = 0                     # 攻击计时器（帧计数）
        self.fan_interval = 60                    # 扇形弹幕间隔（帧数 = 1秒）
        self.aim_interval = 50                    # 瞄准弹幕间隔
        self.circle_interval = 120                # 圆形弹幕间隔（2秒）

        # —— 爆炸系统 ——
        self.exploding = False                    # 是否正在爆炸
        self.explosion_timer = 0                  # 爆炸动画计时器
        self.explosion_duration = 45              # 爆炸持续帧数
        self.explosion_particles = []             # 爆炸粒子数据

        # —— 闪烁预警 ——
        self.flash_timer = 0                      # 闪烁计时器
        self.flash_visible = True                 # 当前是否可见

    def update(self):
        """每帧更新：移动、攻击、检查血量"""
        if self.hp <= 0:
            self.update_explosion()
            return

        # —— 移动：左右巡逻 ——
        self.rect.x += self.direction * self.move_speed
        if self.rect.right >= WIDTH - 10:
            self.direction = -1                    # 碰到右边就向左走
        elif self.rect.left <= 10:
            self.direction = 1                     # 碰到左边就向右走

        # —— 攻击：定时发射弹幕 ——
        self.attack_timer += 1

        # 普通攻击：扇形弹幕（全程都发射）
        if self.attack_timer % self.fan_interval == 0:
            fire_fan_pattern(self)

        # 瞄准攻击：向玩家方向发射（全程发射，间隔不同）
        if self.attack_timer % self.aim_interval == 0:
            fire_aim_pattern(self)

        # 半血大招：圆形弹幕（血量低于 50% 时触发）
        hp_ratio = self.hp / self.max_hp
        if hp_ratio <= 0.5 and self.attack_timer % self.circle_interval == 0:
            fire_circle_pattern(self)

        # 残血狂暴：弹幕频率加倍（血量低于 25%）
        if hp_ratio <= 0.25:
            # 再多发射一轮圆形弹幕（错开时间）
            if self.attack_timer % (self.circle_interval // 2) == 0:
                fire_circle_pattern(self)

    def take_damage(self, damage):
        """Boss 受到伤害"""
        if self.hp <= 0:
            return
        self.hp -= damage
        if self.hp < 0:
            self.hp = 0
        if self.hp <= 0:
            self.start_explosion()

    def start_explosion(self):
        """开始爆炸动画"""
        self.exploding = True
        self.explosion_timer = 0
        # 生成随机爆炸粒子
        for _ in range(30):
            self.explosion_particles.append({
                'x': self.rect.centerx + random.randint(-40, 40),
                'y': self.rect.centery + random.randint(-20, 20),
                'vx': random.uniform(-3, 3),
                'vy': random.uniform(-3, 3),
                'life': random.randint(15, 40),
                'max_life': 40,
                'color': random.choice([RED, ORANGE, YELLOW, GOLD, WHITE]),
                'size': random.randint(3, 8),
            })

    def update_explosion(self):
        """更新爆炸动画"""
        self.explosion_timer += 1
        # 更新粒子位置
        for p in self.explosion_particles:
            p['x'] += p['vx']
            p['y'] += p['vy']
            p['life'] -= 1

        # 移除失效粒子
        self.explosion_particles = [p for p in self.explosion_particles if p['life'] > 0]

        # 爆炸结束 → 移除 Boss
        if self.explosion_timer >= self.explosion_duration:
            self.kill()


# ==================== 弹幕生成函数 ====================

def create_bullet_pattern(center_x, center_y, start_angle, angle_range, count, speed, color):
    """
    弹幕生成器 —— "子弹工厂"

    这是整个弹幕系统的核心函数！无论扇形、圆形还是其他形状的弹幕，
    都可以通过传入不同的参数来实现。

    参数说明（用"烟花"打比方，方便理解）：
    ┌─────────────────┬──────────────────────────────────┐
    │ 参数             │ 含义                             │
    ├─────────────────┼──────────────────────────────────┤
    │ center_x, center_y │ 发射位置（烟花炸开的中心点）   │
    │ start_angle     │ 起始角度（0°=正右，90°=正下）     │
    │ angle_range     │ 覆盖的角度范围（扇形=60°，圆形=360°）│
    │ count           │ 子弹数量（扇形=5~7，圆形=16~24）  │
    │ speed           │ 子弹飞行速度（像素/帧）            │
    │ color           │ 子弹颜色（RGB 元组）               │
    └─────────────────┴──────────────────────────────────┘

    核心算法：
    - 角度均匀分布：第 i 颗子弹的角度 = start_angle + angle_range × i/(count-1)
    - 三角函数分解：vx = speed × cos(角度), vy = speed × sin(角度)

    使用示例：
    >>> # 扇形弹幕：从60°到120°，均匀发射5颗子弹
    >>> create_bullet_pattern(400, 200, 60, 60, 5, 5, RED)

    >>> # 圆形弹幕：360°均匀发射20颗子弹
    >>> create_bullet_pattern(400, 200, 0, 360, 20, 4, GOLD)
    """
    for i in range(count):
        # —— 第1步：计算第 i 颗子弹的角度 ——
        if count == 1:
            # 只有1颗子弹 → 直接用起始角度（通常用于瞄准发射）
            angle_deg = start_angle
        else:
            # 多颗子弹 → 在角度范围内均匀分布
            # 例：start=60°, range=60°, count=5
            # i=0    i=1    i=2    i=3    i=4
            #  60°    75°    90°   105°   120°
            angle_deg = start_angle + angle_range * i / (count - 1)

        # —— 第2步：角度转弧度（计算机只认识弧度！）——
        rad = math.radians(angle_deg)

        # —— 第3步：三角函数拆解方向 ——
        # cos 管左右（水平分量），sin 管上下（垂直分量）
        vx = speed * math.cos(rad)
        vy = speed * math.sin(rad)

        # —— 第4步：创建子弹精灵并加入敌人子弹组 ——
        bullet = Bullet(center_x, center_y, vx, vy, color)
        enemy_bullets.add(bullet)
        all_sprites.add(bullet)


def fire_fan_pattern(boss):
    """
    扇形弹幕 —— "孔雀开屏"

    从 Boss 底部向下方扇形展开 5 颗子弹，覆盖 60° 范围

    视觉效果：
         Boss 👾
      ╱    |    ╲
     ╱     |     ╲
    ●   ●  ●  ●   ●     ← 5颗子弹向下扇形展开（60°~120°）

    参数设计思路：
    - start_angle=60°  → 扇子左边从 60° 开始（时钟3点方向顺时针60° = 右下）
    - angle_range=60°  → 扇子打开 60° 到 120°（时钟4点方向 = 左下）
    - 这样扇子正好居中朝下！
    """
    create_bullet_pattern(
        center_x=boss.rect.centerx,          # Boss 的水平中心
        center_y=boss.rect.bottom + 10,      # Boss 底部往下一点
        start_angle=60,                       # 起始角 60°（扇子左边缘）
        angle_range=60,                       # 覆盖 60°（扇子右边缘 = 120°）
        count=5,                              # 5 颗子弹（不太密也不太稀）
        speed=5,                              # 速度适中
        color=LIGHT_RED,                      # 浅红色（和 Boss 颜色呼应）
    )


def fire_circle_pattern(boss):
    """
    圆形弹幕 —— "烟花绽放"

    从 Boss 中心向 360° 所有方向均匀发射 20 颗子弹，场面壮观！

    视觉效果：
         ●   ●   ●
      ●           ●
    ●     Boss     ●
      ●     👾    ●
    ●               ●
      ●           ●
         ●   ●   ●

    参数设计思路：
    - start_angle=0°  → 从正右方开始
    - angle_range=360° → 转一整圈
    - count=20        → 20颗子弹，360÷20=18° 间隔
    """
    create_bullet_pattern(
        center_x=boss.rect.centerx,          # Boss 中心 X
        center_y=boss.rect.centery,          # Boss 中心 Y（从正中心发出）
        start_angle=0,                        # 从 0°（正右）开始
        angle_range=360,                      # 覆盖 360° 完整一圈！
        count=20,                             # 20 颗子弹
        speed=4,                              # 速度稍慢（距离远了要给人反应时间）
        color=GOLD,                           # 金黄色（大招要华丽！）
    )


def fire_aim_pattern(boss):
    """
    瞄准弹幕 —— "精确打击"

    向玩家当前位置发射子弹。先计算 Boss 到玩家的角度，然后发射。

    注意：只取方向，不追踪！子弹发射后沿直线飞行，不会拐弯。
    （追踪弹留在下一节讲解）
    """
    # 找到玩家精灵
    player = None
    for sprite in all_sprites:
        if isinstance(sprite, Player):
            player = sprite
            break

    if player is None:
        return  # 玩家不存在就不发射

    # 计算从 Boss 中心指向玩家中心的角度
    dx = player.rect.centerx - boss.rect.centerx
    dy = player.rect.centery - boss.rect.centery
    aim_angle_rad = math.atan2(dy, dx)       # atan2 返回弧度
    aim_angle_deg = math.degrees(aim_angle_rad)  # 转为角度制

    # 用弹幕工厂生成 1 颗瞄准子弹
    # 注意：count=1 时，只发射一颗，朝 aim_angle_deg 方向
    create_bullet_pattern(
        center_x=boss.rect.centerx,
        center_y=boss.rect.centery,
        start_angle=aim_angle_deg,
        angle_range=0,                       # 范围 0°，就一颗
        count=1,
        speed=6,                             # 瞄准弹稍快一点
        color=PURPLE,                        # 紫色（和弹幕区分）
    )


# ==================== UI 绘制函数 ====================

def draw_boss_health_bar(screen, boss):
    """
    绘制 Boss 大血条（屏幕顶部）

    设计思路：
    1. 灰色底条 = 总血量（固定的背景）
    2. 彩色前景条 = 当前血量（宽度按比例计算）
    3. 血量颜色根据比例变化：
       - >50%：绿色（安全）
       - 25%~50%：黄色（警告）
       - <25%：红色（危险！）
    4. 显示 Boss 名字和血量数字（BOSS  150/300）

    血条就像是手机电量条：灰色底是总电量，彩色前景是剩余电量。
    """
    bar_width = WIDTH - 100                    # 血条总宽度（左右各留 50 像素）
    bar_height = 24                            # 血条高度
    bar_x = 50                                 # 左上角 X 坐标
    bar_y = 8                                  # 左上角 Y 坐标

    # —— 第1层：背景底条（深灰色） ——
    pygame.draw.rect(screen, DARK_GRAY,
                     (bar_x, bar_y, bar_width, bar_height),
                     border_radius=5)

    # —— 第2层：当前血量条（彩色） ——
    if boss.hp > 0:
        hp_ratio = boss.hp / boss.max_hp        # 血量比例：0.0 ~ 1.0
        current_width = int(bar_width * hp_ratio)  # 当前血量条的宽度

        # 根据血量比例决定颜色
        if hp_ratio > 0.5:
            hp_color = GREEN                     # 满血 → 绿色（安全）
        elif hp_ratio > 0.25:
            hp_color = YELLOW                    # 半血 → 黄色（警告）
        else:
            hp_color = RED                       # 残血 → 红色（危险！）

        pygame.draw.rect(screen, hp_color,
                         (bar_x, bar_y, current_width, bar_height),
                         border_radius=5)

    # —— 第3层：白色边框 ——
    pygame.draw.rect(screen, WHITE,
                     (bar_x, bar_y, bar_width, bar_height),
                     3, border_radius=5)

    # —— 第4层：血条上方的 Boss 名字 ——
    font = pygame.font.Font(None, 28)
    name_text = font.render("BOSS", True, WHITE)
    screen.blit(name_text, (bar_x + 8, bar_y - 22))

    # —— 第5层：血条右侧的血量数字 ——
    hp_text = font.render(f"{boss.hp} / {boss.max_hp}", True, WHITE)
    screen.blit(hp_text, (bar_x + bar_width - hp_text.get_width() - 10,
                           bar_y + 2))


def draw_explosion(screen, boss):
    """绘制 Boss 爆炸粒子"""
    for p in boss.explosion_particles:
        alpha = int(255 * p['life'] / p['max_life'])  # 逐渐变透明
        s = p['size']
        surf = pygame.Surface((s * 2, s * 2), pygame.SRCALPHA)
        pygame.draw.circle(surf, (*p['color'], alpha), (s, s), s)
        screen.blit(surf, (p['x'] - s, p['y'] - s))


# ==================== 游戏主循环 ====================

def main():
    """主函数：初始化游戏、运行主循环"""
    # —— 创建玩家和 Boss ——
    player = Player()
    boss = Boss()

    all_sprites.add(player)
    all_sprites.add(boss)
    boss_group.add(boss)

    # —— 游戏状态 ——
    running = True
    game_over = False
    victory = False
    score = 0

    while running:
        # ========== 第1步：处理事件 ==========
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            # 按 R 键重新开始
            if event.type == pygame.KEYDOWN and event.key == pygame.K_r:
                # 清空所有精灵组
                all_sprites.empty()
                player_bullets.empty()
                enemy_bullets.empty()
                boss_group.empty()
                # 重新创建
                player = Player()
                boss = Boss()
                all_sprites.add(player)
                all_sprites.add(boss)
                boss_group.add(boss)
                game_over = False
                victory = False
                score = 0

        # ========== 第2步：更新游戏状态 ==========
        if not game_over:
            all_sprites.update()

            # —— 碰撞检测：玩家子弹 vs Boss ——
            if boss.hp > 0:
                # groupcollide 检测两组精灵之间的碰撞
                hits = pygame.sprite.groupcollide(
                    player_bullets,    # 组A：玩家子弹
                    boss_group,        # 组B：Boss
                    True,              # 组A碰撞后是否销毁？→ 是（子弹消失）
                    False              # 组B碰撞后是否销毁？→ 否（Boss扣血但不消失）
                )
                # 每颗击中 Boss 的子弹造成 10 点伤害
                for bullet, boss_list in hits.items():
                    for _ in boss_list:
                        boss.take_damage(10)
                        score += 10

            # —— 检查 Boss 是否被击败 ——
            if boss.hp <= 0 and not boss.exploding:
                boss.start_explosion()
            if boss.exploding and boss.explosion_timer >= boss.explosion_duration:
                victory = True
                game_over = True

            # —— 碰撞检测：敌人弹幕 vs 玩家 ——
            # 如果玩家被击中，游戏结束（失败）
            if boss.hp > 0:  # Boss 活着时弹幕才有效
                player_hit = pygame.sprite.spritecollide(
                    player,             # 单个精灵：玩家
                    enemy_bullets,      # 精灵组：敌人弹幕
                    True                # 碰撞后弹幕是否销毁？→ 是
                )
                if player_hit:
                    game_over = True    # 玩家被击中，游戏结束

        # ========== 第3步：绘制画面 ==========
        screen.fill(BLACK)  # 黑色背景（深空感）

        # —— 绘制星空背景（装饰） ——
        for i in range(30):
            x = (i * 137 + 53) % WIDTH
            y = (i * 223 + 17 + pygame.time.get_ticks() // 50 * (i % 3 + 1)) % HEIGHT
            pygame.draw.circle(screen, (80, 80, 100), (x, y), 1)

        # —— 绘制所有精灵 ——
        for sprite in all_sprites:
            if sprite != boss or not boss.exploding or boss.explosion_timer < 20:
                screen.blit(sprite.image, sprite.rect)

        # —— 绘制 Boss 爆炸粒子 ——
        if boss.exploding:
            draw_explosion(screen, boss)

        # —— 绘制 Boss 血条 ——
        if boss.hp > 0:
            draw_boss_health_bar(screen, boss)

        # —— 显示分数 ——
        font = pygame.font.Font(None, 32)
        score_text = font.render(f"得分: {score}", True, WHITE)
        screen.blit(score_text, (WIDTH - score_text.get_width() - 20, HEIGHT - 40))

        # —— 游戏结束画面 ——
        if game_over:
            overlay = pygame.Surface((WIDTH, HEIGHT), pygame.SRCALPHA)
            overlay.fill((0, 0, 0, 150))     # 半透明黑色遮罩
            screen.blit(overlay, (0, 0))

            big_font = pygame.font.Font(None, 72)
            small_font = pygame.font.Font(None, 36)

            if victory:
                msg = big_font.render("胜利！Boss 击败！", True, GOLD)
                sub_msg = small_font.render(
                    f"最终得分: {score}  按 R 重新开始", True, WHITE)
            else:
                msg = big_font.render("游戏结束", True, RED)
                sub_msg = small_font.render("按 R 重新开始", True, WHITE)

            msg_rect = msg.get_rect(center=(WIDTH // 2, HEIGHT // 2 - 30))
            sub_rect = sub_msg.get_rect(center=(WIDTH // 2, HEIGHT // 2 + 30))
            screen.blit(msg, msg_rect)
            screen.blit(sub_msg, sub_rect)

        # —— 操作提示（左上角） ——
        hint_font = pygame.font.Font(None, 22)
        hints = [
            "↑↓←→ 移动",
            "空格 发射",
            "R 重新开始",
        ]
        for i, hint in enumerate(hints):
            hint_surf = hint_font.render(hint, True, GRAY)
            screen.blit(hint_surf, (10, HEIGHT - 80 + i * 22))

        # ========== 第4步：刷新画面 ==========
        pygame.display.flip()

        # ========== 第5步：控制帧率 ==========
        clock.tick(FPS)

    # ==================== 退出 ====================
    pygame.quit()
    sys.exit()


# ==================== 程序入口 ====================
if __name__ == "__main__":
    main()
