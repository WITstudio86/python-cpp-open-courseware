"""
第46节：打磨我的作品② — 音效演示程序
==========================================
功能：不依赖任何外部音频文件，用纯Python生成各种游戏音效
- 按钮点击音效（短促"嘀"声）
- 跳跃音效（上升音调）
- 射击音效（高频短脉冲）
- 爆炸音效（低频噪音）
- 胜利音效（上行音阶）
- 背景节拍（循环播放的鼓点）

技术：使用 struct 模块将数学波形打包为16位PCM音频数据，
      通过 pygame.mixer.Sound(buffer=...) 加载播放。

适用：中小学生课堂演示，代码有详细中文注释
"""

import pygame
import math
import struct
import random

# ==================== 音效生成器 ====================

def generate_sound_buffer(frequency_func, duration, volume=0.3, sample_rate=22050):
    """
    通用的音效生成函数
    参数:
        frequency_func: 一个函数，接收时间 t（秒），返回当前频率（Hz）
                       可以返回固定值（单一频率），也可以随时间变化（滑音效果）
        duration:      音效时长（秒）
        volume:        音量 0.0 ~ 1.0
        sample_rate:   采样率（Hz），22050 足够游戏音效使用
    返回:
        一个 bytes 对象，包含16位立体声PCM音频数据，可直接传给 Sound(buffer=...)
    """
    n_samples = int(sample_rate * duration)
    raw_data = b''

    for i in range(n_samples):
        t = i / sample_rate  # 当前时间点

        # 调用频率函数得到当前频率
        freq = frequency_func(t)

        # 如果频率为 0 或负数，输出静音
        if freq <= 0:
            sample = 0
        else:
            # 生成正弦波采样值：sin(2π * 频率 * 时间)
            value = math.sin(2 * math.pi * freq * t)

            # 应用音量
            value *= volume

            # 应用淡出效果（最后10%时间逐渐减小，避免"咔嗒"爆音）
            fade_out_start = duration * 0.9
            if t > fade_out_start and duration > 0.05:
                fade = 1.0 - (t - fade_out_start) / (duration * 0.1)
                value *= max(0, fade)

            # 转换为16位有符号整数（范围 -32768 ~ 32767）
            sample = int(max(-1.0, min(1.0, value)) * 32767)

        # 打包为小端序16位整数，左右声道相同（立体声）
        raw_data += struct.pack('<hh', sample, sample)

    return raw_data


def make_sound(frequency_func, duration, volume=0.3, sample_rate=22050):
    """
    快捷函数：生成音频数据并创建 pygame.mixer.Sound 对象
    """
    buffer_data = generate_sound_buffer(frequency_func, duration, volume, sample_rate)
    return pygame.mixer.Sound(buffer=buffer_data)


# ==================== 预设音效 ====================

def create_click_sound():
    """按钮点击音效：短促的高频"嘀"声，像点击鼠标"""
    return make_sound(
        frequency_func=lambda t: 1200,  # 固定 1200Hz
        duration=0.06,                   # 非常短，60毫秒
        volume=0.4
    )


def create_jump_sound():
    """跳跃音效：频率从低到高滑上去，模拟"嗖～"的感觉"""
    return make_sound(
        frequency_func=lambda t: 300 + t * 3000,  # 从300Hz滑到约600Hz
        duration=0.15,
        volume=0.35
    )


def create_shoot_sound():
    """射击音效：高频短脉冲 + 快速衰减，像激光枪"""
    return make_sound(
        frequency_func=lambda t: 1800,  # 1800Hz 高频
        duration=0.08,
        volume=0.5
    )


def create_explosion_sound():
    """爆炸音效：低频噪音，模拟"轰～"的震动感"""
    n_samples = int(22050 * 0.4)  # 0.4秒
    raw_data = b''

    for i in range(n_samples):
        t = i / 22050
        # 混合多个低频正弦波 + 随机噪音，模拟爆炸
        value = (
            math.sin(2 * math.pi * 60 * t) * 0.4 +   # 60Hz 基频
            math.sin(2 * math.pi * 110 * t) * 0.3 +  # 110Hz
            math.sin(2 * math.pi * 180 * t) * 0.2 +  # 180Hz
            (random.random() - 0.5) * 0.5             # 白噪音
        )
        # 快速衰减（音量随时间指数下降）
        decay = math.exp(-t * 8)
        value *= decay * 0.5

        sample = int(max(-1.0, min(1.0, value)) * 32767)
        raw_data += struct.pack('<hh', sample, sample)

    return pygame.mixer.Sound(buffer=raw_data)


def create_victory_sound():
    """胜利音效：三个上行音符（C-E-G 大三和弦），欢快的感觉"""
    # 音符频率：C5=523, E5=659, G5=784
    notes = [
        (523, 0.15),  # Do
        (659, 0.15),  # Mi
        (784, 0.3),   # Sol（最后一个音长一点）
    ]
    total_duration = sum(d[1] for d in notes)
    sample_rate = 22050
    n_samples = int(sample_rate * total_duration)
    raw_data = b''

    current_time = 0
    note_index = 0
    note_start = 0

    for i in range(n_samples):
        t = i / sample_rate

        # 检查是否切换到下一个音符
        if t >= note_start + notes[note_index][1] and note_index < len(notes) - 1:
            note_start += notes[note_index][1]
            note_index += 1

        note_t = t - note_start
        freq = notes[note_index][0]

        value = math.sin(2 * math.pi * freq * note_t)

        # 每个音符有独立的淡出
        note_duration = notes[note_index][1]
        fade_start = note_duration * 0.85
        if note_t > fade_start:
            fade = 1.0 - (note_t - fade_start) / (note_duration * 0.15)
            value *= max(0, fade)

        value *= 0.35
        sample = int(max(-1.0, min(1.0, value)) * 32767)
        raw_data += struct.pack('<hh', sample, sample)

    return pygame.mixer.Sound(buffer=raw_data)


def create_beat_sound():
    """节拍音效：短促的低频"咚"声，模拟鼓点"""
    return make_sound(
        frequency_func=lambda t: 80 + math.exp(-t * 30) * 200,  # 80Hz + 快速衰减的高频成分
        duration=0.1,
        volume=0.5
    )


# ==================== 按钮类 ====================

class Button:
    """自定义按钮，支持 hover 变色和点击动画"""

    def __init__(self, x, y, width, height, text, color, hover_color, text_color=(255, 255, 255)):
        self.rect = pygame.Rect(x, y, width, height)
        self.text = text
        self.color = color
        self.hover_color = hover_color
        self.text_color = text_color
        self.is_hovered = False
        self.scale = 1.0          # 当前缩放比例（用于动画）
        self.target_scale = 1.0   # 目标缩放比例

    def update(self, mouse_pos):
        """更新按钮状态（hover检测 + 动画）"""
        self.is_hovered = self.rect.collidepoint(mouse_pos)

        # 缩放动画：hover时放大，松开时恢复
        if self.is_hovered:
            self.target_scale = 1.08
        else:
            self.target_scale = 1.0

        # 平滑过渡
        self.scale += (self.target_scale - self.scale) * 0.3

    def draw(self, screen, font):
        """绘制按钮（带缩放和颜色变化）"""
        # 计算缩放后的矩形
        w = int(self.rect.width * self.scale)
        h = int(self.rect.height * self.scale)
        x = self.rect.centerx - w // 2
        y = self.rect.centery - h // 2

        # 选择颜色
        current_color = self.hover_color if self.is_hovered else self.color

        # 绘制按钮背景（圆角矩形用多个矩形近似）
        pygame.draw.rect(screen, current_color, (x + 4, y, w - 8, h), border_radius=10)
        pygame.draw.rect(screen, current_color, (x, y + 4, w, h - 8), border_radius=10)

        # 绘制真正的圆角矩形（如果pygame版本支持）
        try:
            pygame.draw.rect(screen, current_color, (x, y, w, h), border_radius=10)
        except:
            # 降级方案：四个角的小圆
            pygame.draw.rect(screen, current_color, (x, y, w, h))

        # 绘制按钮边框
        border_color = tuple(min(c + 40, 255) for c in current_color)
        try:
            pygame.draw.rect(screen, border_color, (x, y, w, h), width=2, border_radius=10)
        except:
            pygame.draw.rect(screen, border_color, (x, y, w, h), width=2)

        # 绘制文字
        text_surf = font.render(self.text, True, self.text_color)
        text_rect = text_surf.get_rect(center=(self.rect.centerx, self.rect.centery))
        screen.blit(text_surf, text_rect)

    def is_clicked(self, event):
        """检查按钮是否被点击"""
        if event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
            return self.rect.collidepoint(event.pos)
        return False


# ==================== 粒子效果（点击反馈） ====================

class ClickParticle:
    """点击按钮时产生的粒子特效"""

    def __init__(self, x, y, color):
        self.x = x
        self.y = y
        self.color = color
        angle = random.uniform(0, 2 * math.pi)
        speed = random.uniform(1.5, 4.0)
        self.vx = math.cos(angle) * speed
        self.vy = math.sin(angle) * speed
        self.life = 1.0       # 生命值 1.0 → 0.0
        self.decay = random.uniform(0.02, 0.05)

    def update(self):
        self.x += self.vx
        self.y += self.vy
        self.vy += 0.05  # 重力
        self.life -= self.decay

    def draw(self, screen):
        if self.life > 0:
            alpha = int(self.life * 255)
            size = int(3 + self.life * 5)
            # 用简单的圆表示粒子
            r = min(255, self.color[0] + (255 - self.color[0]) // 2)
            g = min(255, self.color[1] + (255 - self.color[1]) // 2)
            b = min(255, self.color[2] + (255 - self.color[2]) // 2)
            pygame.draw.circle(screen, (r, g, b), (int(self.x), int(self.y)), max(1, size))

    @property
    def alive(self):
        return self.life > 0


# ==================== 主程序 ====================

def main():
    # ---------- 初始化 ----------
    pygame.init()
    pygame.mixer.init(frequency=22050, size=-16, channels=2, buffer=512)

    # 屏幕设置
    SCREEN_WIDTH, SCREEN_HEIGHT = 900, 600
    screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
    pygame.display.set_caption("🎵 音效演示器 — 用代码生成声音！")

    # 设置窗口图标（用程序画一个简单的图标）
    icon_surf = pygame.Surface((32, 32), pygame.SRCALPHA)
    pygame.draw.circle(icon_surf, (180, 130, 255), (16, 16), 14)  # 紫色圆
    pygame.draw.polygon(icon_surf, (255, 215, 0), [(8, 10), (8, 22), (24, 16)])  # 金色播放三角
    pygame.display.set_icon(icon_surf)

    clock = pygame.time.Clock()

    # ---------- 颜色定义 ----------
    BG_COLOR = (20, 10, 40)           # 深紫黑背景
    TITLE_COLOR = (240, 210, 140)     # 金色标题
    SUBTITLE_COLOR = (180, 160, 210)  # 淡紫副标题
    CARD_COLOR = (40, 25, 65)         # 卡片背景
    ACCENT_PURPLE = (140, 100, 220)   # 紫色强调
    ACCENT_GOLD = (212, 168, 67)      # 金色强调
    GREEN = (80, 200, 120)
    RED = (220, 100, 100)
    BLUE = (90, 150, 220)
    ORANGE = (230, 160, 60)
    PINK = (220, 120, 180)

    # ---------- 生成所有音效 ----------
    print("🔊 正在生成音效...")

    sound_click = create_click_sound()
    sound_jump = create_jump_sound()
    sound_shoot = create_shoot_sound()
    sound_explosion = create_explosion_sound()
    sound_victory = create_victory_sound()
    sound_beat = create_beat_sound()

    # 设置各音效的音量
    sound_click.set_volume(0.6)
    sound_jump.set_volume(0.5)
    sound_shoot.set_volume(0.7)
    sound_explosion.set_volume(0.5)
    sound_victory.set_volume(0.6)
    sound_beat.set_volume(0.4)

    print("✅ 音效生成完毕！")

    # ---------- 创建按钮 ----------
    # 布局：两行，每行3个按钮
    btn_w, btn_h = 200, 70
    gap_x, gap_y = 30, 25
    start_x = (SCREEN_WIDTH - (3 * btn_w + 2 * gap_x)) // 2
    start_y = 190

    buttons = [
        Button(start_x, start_y, btn_w, btn_h,
               "🖱️ 点击音效", (100, 80, 180), (140, 120, 220)),
        Button(start_x + btn_w + gap_x, start_y, btn_w, btn_h,
               "⬆️ 跳跃音效", (60, 140, 100), (100, 190, 140)),
        Button(start_x + 2 * (btn_w + gap_x), start_y, btn_w, btn_h,
               "🔫 射击音效", (180, 70, 70), (220, 110, 110)),

        Button(start_x, start_y + btn_h + gap_y, btn_w, btn_h,
               "💥 爆炸音效", (180, 120, 40), (220, 160, 70)),
        Button(start_x + btn_w + gap_x, start_y + btn_h + gap_y, btn_w, btn_h,
               "🏆 胜利音效", (50, 160, 80), (80, 210, 120)),
        Button(start_x + 2 * (btn_w + gap_x), start_y + btn_h + gap_y, btn_w, btn_h,
               "🥁 背景节拍", (100, 70, 180), (140, 110, 220)),
    ]

    # 额外：音量调节按钮（右下角）
    btn_small_w, btn_small_h = 140, 45
    btn_vol_down = Button(
        SCREEN_WIDTH - 340, SCREEN_HEIGHT - 60,
        btn_small_w, btn_small_h,
        "🔉 音量-", (80, 70, 130), (120, 110, 170))
    btn_vol_up = Button(
        SCREEN_WIDTH - 180, SCREEN_HEIGHT - 60,
        btn_small_w, btn_small_h,
        "🔊 音量+", (80, 70, 130), (120, 110, 170))

    # ---------- 字体 ----------
    try:
        font_title = pygame.font.SysFont("SimHei", 38, bold=True)
        font_subtitle = pygame.font.SysFont("SimHei", 20)
        font_btn = pygame.font.SysFont("SimHei", 22)
        font_info = pygame.font.SysFont("SimHei", 16)
        font_volume = pygame.font.SysFont("SimHei", 18)
    except:
        # 如果 SimHei 不可用，使用默认字体
        font_title = pygame.font.Font(None, 38)
        font_subtitle = pygame.font.Font(None, 20)
        font_btn = pygame.font.Font(None, 22)
        font_info = pygame.font.Font(None, 16)
        font_volume = pygame.font.Font(None, 18)

    # ---------- 状态变量 ----------
    particles = []          # 粒子特效列表
    beat_timer = 0          # 节拍计时器
    beat_playing = False    # 是否正在播放节拍
    beat_interval = 500     # 节拍间隔（毫秒），500ms = 120BPM
    master_volume = 0.5     # 主音量
    last_clicked_button = None  # 最后点击的按钮（用于显示反馈文字）
    feedback_timer = 0      # 反馈文字显示计时器
    feedback_text = ""      # 反馈文字内容

    # ---------- 主循环 ----------
    running = True
    while running:
        dt = clock.get_time()  # 上一帧耗时（毫秒）
        mouse_pos = pygame.mouse.get_pos()

        # --- 事件处理 ---
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

            elif event.type == pygame.KEYDOWN:
                # 键盘快捷键
                if event.key == pygame.K_ESCAPE:
                    running = False
                elif event.key == pygame.K_SPACE:
                    # 空格键：切换背景节拍
                    beat_playing = not beat_playing
                    if beat_playing:
                        sound_beat.play()
                        feedback_text = "节拍开始！🥁"
                    else:
                        feedback_text = "节拍停止"
                    feedback_timer = 60
                    last_clicked_button = None

            elif event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
                # 检查按钮点击
                for i, btn in enumerate(buttons):
                    if btn.is_clicked(event):
                        # 播放对应音效
                        sound_list = [sound_click, sound_jump, sound_shoot,
                                      sound_explosion, sound_victory, sound_beat]
                        if i < len(sound_list):
                            # 复制音效对象以支持重叠播放
                            s = sound_list[i]
                            s.play()

                        # 产生粒子
                        for _ in range(12):
                            if i == 3:  # 爆炸：红色粒子
                                particles.append(ClickParticle(mouse_pos[0], mouse_pos[1], RED))
                            else:
                                color_choice = [ACCENT_PURPLE, GREEN, BLUE, ORANGE, PINK, ACCENT_GOLD]
                                particles.append(ClickParticle(mouse_pos[0], mouse_pos[1], color_choice[i % len(color_choice)]))

                        # 反馈文字
                        names = ["点击！", "跳跃！", "射击！", "爆炸！", "胜利！", "节拍！"]
                        feedback_text = names[i]
                        feedback_timer = 45
                        last_clicked_button = i

                        # 如果点击了节拍按钮，切换节拍状态
                        if i == 5:
                            beat_playing = not beat_playing
                            if beat_playing:
                                feedback_text = "节拍开始！🥁"
                            else:
                                feedback_text = "节拍停止"
                        break

                # 音量调节按钮
                if btn_vol_down.is_clicked(event):
                    master_volume = max(0.0, master_volume - 0.1)
                    _apply_master_volume(sound_click, sound_jump, sound_shoot,
                                         sound_explosion, sound_victory, sound_beat,
                                         master_volume)
                    feedback_text = f"音量: {int(master_volume * 100)}%"
                    feedback_timer = 30
                elif btn_vol_up.is_clicked(event):
                    master_volume = min(1.0, master_volume + 0.1)
                    _apply_master_volume(sound_click, sound_jump, sound_shoot,
                                         sound_explosion, sound_victory, sound_beat,
                                         master_volume)
                    feedback_text = f"音量: {int(master_volume * 100)}%"
                    feedback_timer = 30

        # --- 背景节拍逻辑 ---
        if beat_playing:
            beat_timer += dt
            if beat_timer >= beat_interval:
                beat_timer = 0
                sound_beat.play()

        # --- 更新 ---
        for btn in buttons:
            btn.update(mouse_pos)
        btn_vol_down.update(mouse_pos)
        btn_vol_up.update(mouse_pos)

        # 更新粒子
        for p in particles[:]:
            p.update()
            if not p.alive:
                particles.remove(p)

        # 更新反馈文字计时器
        if feedback_timer > 0:
            feedback_timer -= 1

        # --- 绘制 ---
        # 背景
        screen.fill(BG_COLOR)

        # 背景装饰：几个半透明的大圆
        for i, (cx, cy, r, alpha) in enumerate([
            (150, 120, 80, 15), (750, 100, 60, 12),
            (100, 450, 100, 10), (800, 480, 70, 14),
        ]):
            s = pygame.Surface((r * 2, r * 2), pygame.SRCALPHA)
            pygame.draw.circle(s, (140, 100, 220, alpha), (r, r), r)
            screen.blit(s, (cx - r, cy - r))

        # 标题
        title_surf = font_title.render("🎵 pygame 音效演示器", True, TITLE_COLOR)
        title_rect = title_surf.get_rect(center=(SCREEN_WIDTH // 2, 45))
        screen.blit(title_surf, title_rect)

        # 副标题
        sub_surf = font_subtitle.render("不依赖外部音频文件，用数学公式生成游戏音效！", True, SUBTITLE_COLOR)
        sub_rect = sub_surf.get_rect(center=(SCREEN_WIDTH // 2, 85))
        screen.blit(sub_surf, sub_rect)

        # 信息卡片（技术说明）
        card_rect = pygame.Rect(40, 115, SCREEN_WIDTH - 80, 50)
        pygame.draw.rect(screen, CARD_COLOR, card_rect, border_radius=10)
        pygame.draw.rect(screen, (80, 60, 120), card_rect, width=1, border_radius=10)

        info_lines = [
            f"💡 原理：正弦波 → struct打包 → Sound(buffer=...)  |  采样率：22050Hz  |  格式：16位立体声 PCM",
        ]
        info_surf = font_info.render(info_lines[0], True, SUBTITLE_COLOR)
        screen.blit(info_surf, (60, 130))

        # 绘制按钮
        for btn in buttons:
            btn.draw(screen, font_btn)

        # 音量按钮
        btn_vol_down.draw(screen, font_volume)
        btn_vol_up.draw(screen, font_volume)

        # 音量显示
        vol_text = f"🔊 主音量: {int(master_volume * 100)}%"
        vol_surf = font_volume.render(vol_text, True, SUBTITLE_COLOR)
        screen.blit(vol_surf, (SCREEN_WIDTH - 340, SCREEN_HEIGHT - 85))

        # 节拍状态显示
        beat_status = "🟢 节拍进行中..." if beat_playing else "⚫ 节拍已停止"
        beat_color = GREEN if beat_playing else (120, 100, 160)
        beat_surf = font_volume.render(beat_status, True, beat_color)
        screen.blit(beat_surf, (40, SCREEN_HEIGHT - 55))

        # 反馈文字（点击按钮后短暂显示）
        if feedback_timer > 0 and feedback_text:
            alpha = min(255, feedback_timer * 8)
            fb_color = (255, 220, 100, alpha)  # 无法直接用alpha，这里简化处理
            fb_surf = font_title.render(feedback_text, True, TITLE_COLOR)
            fb_rect = fb_surf.get_rect(center=(SCREEN_WIDTH // 2, SCREEN_HEIGHT - 110))
            # 简易闪烁效果
            if feedback_timer > 20:
                screen.blit(fb_surf, fb_rect)

        # 底部提示
        hint_text = "按 空格键 切换节拍 | 按 ESC 退出 | 点击按钮播放音效"
        hint_surf = font_info.render(hint_text, True, (100, 80, 150))
        hint_rect = hint_surf.get_rect(center=(SCREEN_WIDTH // 2, SCREEN_HEIGHT - 25))
        screen.blit(hint_surf, hint_rect)

        # 绘制粒子
        for p in particles:
            p.draw(screen)

        # --- 刷新 ---
        pygame.display.flip()
        clock.tick(60)

    # ---------- 退出 ----------
    pygame.quit()
    print("👋 音效演示程序已退出，感谢使用！")


def _apply_master_volume(click, jump, shoot, explosion, victory, beat, vol):
    """批量设置所有音效的主音量"""
    click.set_volume(0.6 * vol)
    jump.set_volume(0.5 * vol)
    shoot.set_volume(0.7 * vol)
    explosion.set_volume(0.5 * vol)
    victory.set_volume(0.6 * vol)
    beat.set_volume(0.4 * vol)


# ==================== 运行 ====================
if __name__ == "__main__":
    print("=" * 55)
    print("   🎵 第46节：音效演示程序")
    print("   用纯Python生成游戏音效，无需音频文件！")
    print("=" * 55)
    print()
    print("操作说明：")
    print("  🖱️  点击按钮 → 播放对应音效")
    print("  空格键    → 切换背景节拍")
    print("  🔊/🔉   → 调节音量")
    print("  ESC      → 退出程序")
    print()
    main()
