"""
第48节 - 颁奖庆祝动画
输入获奖者名字，播放烟花粒子庆祝效果

运行方式：python 颁奖庆祝动画.py
操作：点击屏幕任意位置发射烟花，按 R 键重置，按 ESC 退出
"""

import pygame
import random
import math

# 初始化
pygame.init()
WIDTH, HEIGHT = 800, 600
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("颁奖庆祝动画 - 第48节")
clock = pygame.time.Clock()

# 颜色常量
BLACK = (5, 10, 25)
DARK_BLUE = (10, 20, 50)
GOLD = (240, 192, 64)
WHITE = (255, 255, 255)

# 烟花颜色主题
FIREWORK_COLORS = [
    (255, 50, 50),    # 红
    (255, 160, 30),   # 橙
    (255, 220, 50),   # 金
    (50, 255, 80),    # 绿
    (50, 180, 255),   # 蓝
    (180, 80, 255),   # 紫
    (255, 80, 180),   # 粉
    (50, 255, 220),   # 青
    (255, 255, 100),  # 黄
]


class Particle:
    """烟花粒子"""
    def __init__(self, x, y, color, speed, angle, life, size=2):
        self.x = x
        self.y = y
        self.color = color
        self.vx = math.cos(angle) * speed
        self.vy = math.sin(angle) * speed
        self.life = life          # 总生命
        self.max_life = life
        self.size = size
        self.gravity = 0.05       # 重力

    def update(self):
        self.vy += self.gravity
        self.x += self.vx
        self.y += self.vy
        self.life -= 1

    @property
    def alive(self):
        return self.life > 0

    @property
    def alpha(self):
        """透明度，生命越短越透明"""
        return max(0, int(255 * self.life / self.max_life))

    def draw(self, surface):
        if not self.alive:
            return
        alpha = self.alpha
        color = tuple(min(255, c * alpha // 255 + 30) for c in self.color)

        # 根据剩余生命调整大小（闪烁效果）
        ratio = self.life / self.max_life
        draw_size = max(1, int(self.size * ratio))

        if draw_size <= 1:
            surface.set_at((int(self.x), int(self.y)), color)
        else:
            pygame.draw.circle(surface, color, (int(self.x), int(self.y)), draw_size)
            # 添加光晕
            if draw_size >= 2:
                glow_color = (color[0] // 3, color[1] // 3, color[2] // 3)
                pygame.draw.circle(surface, glow_color,
                                   (int(self.x), int(self.y)), draw_size + 2, 1)


class Firework:
    """一发烟花"""
    def __init__(self, x, y):
        self.particles = []
        self.age = 0
        self.max_age = 120  # 帧

        # 随机选择颜色主题
        main_color = random.choice(FIREWORK_COLORS)
        particle_count = random.randint(60, 120)

        # 生成粒子
        for _ in range(particle_count):
            angle = random.uniform(0, 2 * math.pi)
            speed = random.uniform(2, 7)
            life = random.randint(30, 80)
            size = random.uniform(1.5, 3.5)

            # 颜色微调（在主题色基础上随机变化）
            color = (
                min(255, main_color[0] + random.randint(-40, 40)),
                min(255, main_color[1] + random.randint(-40, 40)),
                min(255, main_color[2] + random.randint(-40, 40)),
            )
            self.particles.append(Particle(x, y, color, speed, angle, life, size))

    def update(self):
        self.age += 1
        for p in self.particles:
            p.update()

    @property
    def alive(self):
        return self.age < self.max_age

    def draw(self, surface):
        for p in self.particles:
            if p.alive:
                p.draw(surface)


def draw_text(surface, text, x, y, size, color, center=True, bold=False):
    """绘制文字辅助函数"""
    font_name = "SimHei" if pygame.font.get_default_font() else None
    try:
        font = pygame.font.Font(font_name, size) if font_name else pygame.font.Font(None, size)
    except:
        font = pygame.font.Font(None, size)

    text_surf = font.render(text, True, color)
    if center:
        rect = text_surf.get_rect(center=(x, y))
        surface.blit(text_surf, rect)
    else:
        surface.blit(text_surf, (x, y))


def get_input_name():
    """文字输入界面，获取获奖者名字"""
    name = ""
    input_active = True
    cursor_visible = True
    cursor_timer = 0

    while input_active:
        dt = clock.tick(60)
        cursor_timer += dt

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                return None  # 退出程序
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    return None
                elif event.key == pygame.K_RETURN or event.key == pygame.K_KP_ENTER:
                    if name.strip():
                        input_active = False
                elif event.key == pygame.K_BACKSPACE:
                    name = name[:-1]
                else:
                    # 允许输入字母、数字、中文（pygame通过unicode获取）
                    if event.unicode and len(name) < 20:
                        name += event.unicode

        # 光标闪烁
        if cursor_timer > 500:
            cursor_visible = not cursor_visible
            cursor_timer = 0

        # 绘制输入界面
        screen.fill(DARK_BLUE)
        draw_text(screen, "颁奖庆祝动画", WIDTH//2, 100, 48, GOLD)
        draw_text(screen, "请输入获奖者名字", WIDTH//2, 200, 28, WHITE)
        draw_text(screen, "按回车确认 · ESC退出", WIDTH//2, 260, 18, (150, 150, 170))

        # 输入框
        box_w, box_h = 400, 50
        box_x, box_y = WIDTH//2 - box_w//2, 320
        pygame.draw.rect(screen, (50, 50, 80), (box_x, box_y, box_w, box_h), 2, 8)
        pygame.draw.rect(screen, (20, 20, 40), (box_x+2, box_y+2, box_w-4, box_h-4), border_radius=6)

        draw_text(screen, name, WIDTH//2, box_y + box_h//2, 32, WHITE)

        # 闪烁光标
        if cursor_visible:
            text_width = len(name) * 18 if len(name) > 0 else 0
            cursor_x = WIDTH//2 + text_width + 2
            pygame.draw.line(screen, WHITE,
                             (cursor_x, box_y + 10),
                             (cursor_x, box_y + box_h - 10), 2)

        draw_text(screen, "输入后点击屏幕任意位置发射烟花！", WIDTH//2, 430, 18, (180, 180, 200))
        pygame.display.flip()

    return name.strip()


def main():
    # 获取获奖者名字
    winner_name = get_input_name()
    if winner_name is None:
        pygame.quit()
        return

    print(f"🎉 恭喜获奖者：{winner_name}")

    fireworks = []
    running = True
    auto_fire_timer = 0
    name_bounce_timer = 0
    name_wave_effect = 0

    while running:
        dt = clock.tick(60)

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    running = False
                elif event.key == pygame.K_r:
                    # 重置：重新输入名字
                    fireworks.clear()
                    winner_name = get_input_name()
                    if winner_name is None:
                        running = False
                    auto_fire_timer = 0
            elif event.type == pygame.MOUSEBUTTONDOWN:
                # 点击发射烟花
                mx, my = pygame.mouse.get_pos()
                fireworks.append(Firework(mx, my))

        # 自动发射烟花（每秒约1-2发）
        auto_fire_timer += dt
        if auto_fire_timer > random.randint(800, 1500):
            auto_fire_timer = 0
            fx = random.randint(100, WIDTH - 100)
            fy = random.randint(60, HEIGHT - 150)
            fireworks.append(Firework(fx, fy))

        # 名字动画计时器
        name_bounce_timer += dt

        # 更新所有烟花
        for fw in fireworks[:]:
            fw.update()
            if not fw.alive:
                fireworks.remove(fw)

        # 绘制
        screen.fill(BLACK)

        # 绘制微弱的星空背景
        for i in range(30):
            sx = (i * 137 + name_bounce_timer * 0.02) % WIDTH
            sy = (i * 251) % HEIGHT
            brightness = 100 + int(50 * math.sin(name_bounce_timer * 0.003 + i))
            c = (brightness, brightness, brightness + 20)
            pygame.draw.circle(screen, c, (int(sx), int(sy)), 1)

        # 绘制所有烟花
        for fw in fireworks:
            fw.draw(screen)

        # 获奖者名字（带动画效果）
        name_wave_effect = math.sin(name_bounce_timer * 0.003) * 5

        # 名字光晕
        glow_sizes = [48, 52, 56, 60, 64]
        for gs in glow_sizes:
            alpha = 30
            draw_text(screen, f"🏆 {winner_name} 🏆",
                      WIDTH//2, 50 + int(name_wave_effect),
                      gs, (GOLD[0], GOLD[1], GOLD[2], alpha))

        # 名字主体
        draw_text(screen, f"🏆 {winner_name} 🏆",
                  WIDTH//2, 50 + int(name_wave_effect),
                  42, GOLD, bold=True)

        # 提示文字
        draw_text(screen, "点击屏幕发射烟花 | 按 R 重新输入 | 按 ESC 退出",
                  WIDTH//2, HEIGHT - 30, 16, (120, 130, 150))

        # 显示烟花数量
        if fireworks:
            draw_text(screen, f"烟花数量: {len(fireworks)}",
                      WIDTH - 100, HEIGHT - 50, 14, (100, 110, 130), center=True)

        pygame.display.flip()

    pygame.quit()
    print("感谢使用颁奖庆祝动画，下课！")


if __name__ == "__main__":
    main()
