"""
第45节：我的游戏我设计 ① — 游戏创意生成器（灵感Demo）

功能说明：
  这是一个「游戏创意生成器」，帮助学生打开创作思路。
  点击按钮随机组合 游戏类型 + 玩法元素 + 主题风格，
  生成一个游戏创意卡片。可以反复生成，直到找到灵感。

  这不是学生必须完成的作品，而是作为选题参考的辅助工具。

操作方式：
  - 点击「生成创意」按钮 → 随机生成一个创意组合
  - 可以多次点击，浏览不同的创意
  - 按 ESC 或关闭窗口退出
"""

import pygame
import random

# 初始化
pygame.init()
WIDTH, HEIGHT = 800, 600
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("游戏创意生成器 - 第45节灵感工具")
clock = pygame.time.Clock()

# ============ 颜色定义 ============
BG_COLOR = (15, 15, 30)
CARD_BG = (25, 25, 50)
WHITE = (255, 255, 255)
YELLOW = (255, 215, 0)
PINK = (255, 105, 145)
CYAN = (0, 210, 255)
PURPLE = (170, 130, 250)
GREEN = (100, 220, 150)
ORANGE = (255, 160, 60)
GRAY = (150, 150, 160)
DARK_GRAY = (80, 80, 100)

# ============ 字体 ============
try:
    font_title = pygame.font.Font(None, 56)
    font_large = pygame.font.Font(None, 44)
    font_medium = pygame.font.Font(None, 32)
    font_small = pygame.font.Font(None, 24)
    font_tiny = pygame.font.Font(None, 20)
except:
    font_title = pygame.font.SysFont("microsoftyahei", 56)
    font_large = pygame.font.SysFont("microsoftyahei", 44)
    font_medium = pygame.font.SysFont("microsoftyahei", 32)
    font_small = pygame.font.SysFont("microsoftyahei", 24)
    font_tiny = pygame.font.SysFont("microsoftyahei", 20)

# ============ 创意数据库 ============
# 游戏类型
GAME_TYPES = [
    {"name": "动作类", "icon": "🏃", "color": PINK},
    {"name": "射击类", "icon": "🎯", "color": ORANGE},
    {"name": "益智类", "icon": "🧩", "color": CYAN},
    {"name": "跑酷类", "icon": "🏃‍♂️", "color": GREEN},
    {"name": "休闲类", "icon": "🍎", "color": YELLOW},
    {"name": "策略类", "icon": "♟️", "color": PURPLE},
    {"name": "音乐类", "icon": "🎵", "color": PINK},
    {"name": "养成类", "icon": "🐣", "color": GREEN},
]

# 核心玩法
GAMEPLAY = [
    {"name": "躲避障碍物", "desc": "控制角色移动，躲开飞来的障碍"},
    {"name": "收集物品", "desc": "在限定时间内尽可能多地收集目标"},
    {"name": "消灭敌人", "desc": "发射子弹/道具消灭屏幕上的敌人"},
    {"name": "跳跃闯关", "desc": "通过跳跃跨过平台间的间隙"},
    {"name": "匹配消除", "desc": "相同颜色的元素连在一起就消除"},
    {"name": "答题闯关", "desc": "答对问题前进，答错受到惩罚"},
    {"name": "塔防防守", "desc": "建造防御塔阻止敌人到达终点"},
    {"name": "弹射反弹", "desc": "利用反弹和角度计算击打目标"},
    {"name": "限时挑战", "desc": "在倒计时结束前达成目标分数"},
    {"name": "对战对决", "desc": "两个玩家同时在屏幕上竞争"},
]

# 主题风格
THEMES = [
    {"name": "太空科幻", "icon": "🚀", "desc": "在宇宙中冒险，外星人、星球、飞船"},
    {"name": "海底世界", "icon": "🐠", "desc": "深海探险，鱼群、珊瑚、宝藏"},
    {"name": "魔法学院", "icon": "🔮", "desc": "施展魔法，收集法术书，对战魔兽"},
    {"name": "像素复古", "icon": "👾", "desc": "80年代街机风格，像素方块世界"},
    {"name": "城市冒险", "icon": "🏙️", "desc": "在城市街道中穿梭，躲避车流"},
    {"name": "丛林探险", "icon": "🌴", "desc": "热带雨林中探索，避开野兽和陷阱"},
    {"name": "美食厨房", "icon": "🍕", "desc": "制作/收集食物，满足顾客订单"},
    {"name": "忍者武侠", "icon": "🥷", "desc": "飞檐走壁，暗器对战，轻功跳跃"},
]

# 操作方式
CONTROLS = [
    "键盘方向键移动",
    "鼠标点击操作",
    "空格键跳跃 + 方向键移动",
    "WASD 移动 + 鼠标瞄准",
    "单键（空格）跳跃",
]

# 特殊玩法小提示
BONUS_TIPS = [
    "试试加上「生命值」系统，让游戏更有挑战！",
    "试试加上「关卡递增」——每过一关速度变快！",
    "试试加上「道具系统」——吃到星星会加速！",
    "试试加上「Combo连击」——连续得分有加成！",
    "试试加上「排行榜」——把最高分保存到文件！",
    "试试加上「双人模式」——两个玩家对战！",
    "试试加上「粒子特效」——消除时爆出彩色粒子！",
    "试试加上「Boss战」——每5关出现一个大Boss！",
]


# ============ 按钮类 ============
class Button:
    """一个简单的按钮"""
    def __init__(self, x, y, w, h, text, color, text_color=WHITE):
        self.rect = pygame.Rect(x, y, w, h)
        self.text = text
        self.color = color
        self.text_color = text_color
        self.hover = False

    def draw(self, surface):
        # 悬停效果
        c = self.color
        if self.hover:
            c = tuple(min(255, v + 40) for v in self.color)
        # 绘制按钮
        pygame.draw.rect(surface, c, self.rect, border_radius=12)
        pygame.draw.rect(surface, WHITE, self.rect, 3, border_radius=12)
        # 绘制文字
        text_surf = font_medium.render(self.text, True, self.text_color)
        text_rect = text_surf.get_rect(center=self.rect.center)
        surface.blit(text_surf, text_rect)

    def update(self, mx, my):
        self.hover = self.rect.collidepoint(mx, my)

    def is_clicked(self, pos):
        return self.rect.collidepoint(pos)


# ============ 粒子特效 ============
class Particle:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.vx = random.uniform(-3, 3)
        self.vy = random.uniform(-5, -1)
        self.life = random.randint(20, 50)
        self.max_life = self.life
        self.size = random.randint(3, 8)
        self.color = random.choice([PINK, CYAN, YELLOW, PURPLE, GREEN, ORANGE])

    def update(self):
        self.x += self.vx
        self.y += self.vy
        self.vy += 0.1  # 重力
        self.life -= 1

    def draw(self, surface):
        alpha = int(255 * self.life / self.max_life)
        size = int(self.size * self.life / self.max_life)
        if size > 0:
            s = pygame.Surface((size * 2, size * 2), pygame.SRCALPHA)
            pygame.draw.circle(s, (*self.color, alpha), (size, size), size)
            surface.blit(s, (self.x - size, self.y - size))

    @property
    def alive(self):
        return self.life > 0


# ============ 创意卡片类 ============
class IdeaCard:
    """显示游戏创意卡片的视觉效果"""
    def __init__(self):
        self.card_rect = pygame.Rect(70, 100, 660, 380)
        self.visible = False
        self.alpha = 0  # 淡入动画
        self.scale = 0.8  # 弹出动画
        self.particles = []

        # 当前创意
        self.game_type = None
        self.gameplay = None
        self.theme = None
        self.control = None
        self.bonus_tip = None

    def generate(self):
        """随机生成一个新的创意组合"""
        self.game_type = random.choice(GAME_TYPES)
        self.gameplay = random.choice(GAMEPLAY)
        self.theme = random.choice(THEMES)
        self.control = random.choice(CONTROLS)
        self.bonus_tip = random.choice(BONUS_TIPS)
        self.visible = True
        self.alpha = 0
        self.scale = 0.8

        # 生成粒子
        cx = self.card_rect.centerx
        cy = self.card_rect.centery
        self.particles = [Particle(cx + random.randint(-100, 100),
                                   cy + random.randint(-50, 50))
                          for _ in range(30)]

    def update(self):
        # 淡入动画
        if self.alpha < 255:
            self.alpha = min(255, self.alpha + 15)
        # 弹出动画
        if self.scale < 1.0:
            self.scale = min(1.0, self.scale + 0.04)

        # 更新粒子
        for p in self.particles:
            p.update()
        self.particles = [p for p in self.particles if p.alive]

    def draw(self, surface):
        if not self.visible:
            return

        # 卡片缩放效果
        r = self.card_rect
        scaled_w = int(r.width * self.scale)
        scaled_h = int(r.height * self.scale)
        scaled_x = r.centerx - scaled_w // 2
        scaled_y = r.centery - scaled_h // 2

        # 绘制半透明背景的卡片
        card_surf = pygame.Surface((r.width, r.height), pygame.SRCALPHA)
        # 卡片背景
        pygame.draw.rect(card_surf, (*CARD_BG, min(255, self.alpha)),
                         (0, 0, r.width, r.height), border_radius=20)
        # 边框（用游戏类型的颜色）
        border_color = (*self.game_type["color"], min(255, self.alpha))
        pygame.draw.rect(card_surf, border_color,
                         (0, 0, r.width, r.height), 4, border_radius=20)

        # 顶部装饰条
        pygame.draw.rect(card_surf, border_color,
                         (20, 20, r.width - 40, 6), border_radius=3)

        # ===== 卡片内容绘制 =====
        # 第1行：类型标签
        type_text = font_medium.render(
            f"{self.game_type['icon']}  {self.game_type['name']}",
            True, self.game_type["color"])
        type_rect = type_text.get_rect(topleft=(40, 45))
        card_surf.blit(type_text, type_rect)

        # 主题标签（右上角）
        theme_text = font_small.render(
            f"{self.theme['icon']} {self.theme['name']}",
            True, PURPLE)
        theme_rect = theme_text.get_rect(topright=(r.width - 40, 50))
        card_surf.blit(theme_text, theme_rect)

        # 分隔线
        pygame.draw.line(card_surf, (*GRAY, min(100, self.alpha)),
                         (40, 90), (r.width - 40, 90), 1)

        # 第2行：玩法描述
        play_title = font_small.render("🎮 核心玩法", True, CYAN)
        card_surf.blit(play_title, (40, 110))
        play_text = font_large.render(self.gameplay["name"], True, WHITE)
        card_surf.blit(play_text, (40, 140))
        play_desc = font_small.render(self.gameplay["desc"], True, GRAY)
        card_surf.blit(play_desc, (40, 190))

        # 第3行：主题说明
        theme_title = font_small.render("🎨 主题风格", True, PURPLE)
        card_surf.blit(theme_title, (40, 230))
        theme_desc = font_small.render(self.theme["desc"], True, GRAY)
        card_surf.blit(theme_desc, (40, 260))

        # 第4行：操作建议
        ctrl_text = font_small.render(f"🕹️  推荐操作：{self.control}", True, GREEN)
        card_surf.blit(ctrl_text, (40, 300))

        # 第5行：Bonus小提示
        tip_label = font_small.render("💡 加分项", True, YELLOW)
        card_surf.blit(tip_label, (40, 335))
        # 文字可能太长，需要截断
        tip_text = self.bonus_tip
        tip_surf = font_tiny.render(tip_text, True, YELLOW)
        card_surf.blit(tip_surf, (170, 338))

        # 底部装饰点
        for i in range(5):
            dot_x = 40 + i * 40
            dot_color = [PINK, CYAN, YELLOW, GREEN, PURPLE][i]
            pygame.draw.circle(card_surf, dot_color, (dot_x, r.height - 20), 5)

        # 缩放并绘制到屏幕
        if self.scale < 1.0:
            scaled = pygame.transform.smoothscale(
                card_surf,
                (scaled_w, scaled_h))
            surface.blit(scaled, (scaled_x, scaled_y))
        else:
            surface.blit(card_surf, (r.x, r.y))

        # 绘制粒子
        for p in self.particles:
            p.draw(surface)


# ============ 主程序 ============
def main():
    # 创建按钮
    btn_generate = Button(
        WIDTH // 2 - 120, HEIGHT - 90, 240, 60,
        "✨ 生成创意", (100, 60, 180))

    # 创建创意卡片
    idea_card = IdeaCard()
    idea_card.generate()  # 启动时就生成一个

    # 提示信息
    hint_text = font_small.render("点击按钮随机生成游戏创意，找到你的灵感！", True, GRAY)
    hint_rect = hint_text.get_rect(center=(WIDTH // 2, HEIGHT - 130))

    counter_text = None
    counter_timer = 0  # "已生成N个" 的显示计时器

    running = True
    while running:
        mx, my = pygame.mouse.get_pos()
        dt = clock.tick(60)

        # ===== 事件处理 =====
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    running = False
                if event.key == pygame.K_SPACE:
                    # 空格也可以生成
                    idea_card.generate()
                    counter_timer = 120
            if event.type == pygame.MOUSEBUTTONDOWN:
                if event.button == 1:
                    if btn_generate.is_clicked(event.pos):
                        idea_card.generate()
                        counter_timer = 120

        # ===== 更新 =====
        btn_generate.update(mx, my)
        idea_card.update()
        if counter_timer > 0:
            counter_timer -= 1

        # ===== 绘制 =====
        screen.fill(BG_COLOR)

        # 背景装饰圆点
        for i in range(20):
            x = (i * 97 + 30) % WIDTH
            y = (i * 73 + 50) % HEIGHT
            alpha = 30 + int(15 * pygame.time.get_ticks() / 1000 % 3)
            pygame.draw.circle(screen, (60, 60, 100), (x, y), 3)

        # 标题
        title = font_title.render("🎮  游戏创意生成器", True, WHITE)
        title_rect = title.get_rect(center=(WIDTH // 2, 45))
        # 标题阴影
        shadow = font_title.render("🎮  游戏创意生成器", True, (40, 40, 80))
        screen.blit(shadow, (title_rect.x + 2, title_rect.y + 2))
        screen.blit(title, title_rect)

        # 副标题
        subtitle = font_small.render("随机组合游戏类型 × 玩法 × 主题，激发你的灵感！", True, GRAY)
        sub_rect = subtitle.get_rect(center=(WIDTH // 2, 85))
        screen.blit(subtitle, sub_rect)

        # 创意卡片
        idea_card.draw(screen)

        # 提示文字
        screen.blit(hint_text, hint_rect)

        # 生成按钮
        btn_generate.draw(screen)

        # 快捷键提示
        shortcut_hint = font_tiny.render("按空格键也可以生成", True, DARK_GRAY)
        screen.blit(shortcut_hint, (WIDTH // 2 - 80, HEIGHT - 25))

        # "已生成N个创意" （如果刚生成过）
        if counter_timer > 0:
            counter_surf = font_small.render("💡 新创意已生成！看看喜不喜欢？", True, YELLOW)
            screen.blit(counter_surf, (WIDTH // 2 - 160, HEIGHT - 155))

        pygame.display.flip()

    pygame.quit()


if __name__ == "__main__":
    main()
