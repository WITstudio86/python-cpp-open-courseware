"""
第4节：鼠标与图片 (Mouse & Images)
—— 用 Surface 绘制角色，角色跟随鼠标移动，点击切换大小
"""

import pygame
import sys

# ============================================================
# 初始化 Pygame
# ============================================================
pygame.init()

# ============================================================
# 常量定义
# ============================================================
SCREEN_WIDTH = 800       # 窗口宽度
SCREEN_HEIGHT = 600      # 窗口高度
FPS = 60                 # 帧率
BACKGROUND_COLOR = (30, 30, 50)   # 深蓝紫色背景

# 角色基础尺寸（被 scale 之前的原始 Surface 边长）
CHAR_BASE_SIZE = 150

# 三种缩放比例：小 / 中 / 大 —— 点击鼠标时在这三者之间循环
SIZE_SCALES = [0.6, 1.0, 1.5]


# ============================================================
# 颜色常量
# ============================================================
COLOR_WHITE       = (255, 255, 255)
COLOR_BLACK       = (0, 0, 0)
COLOR_PINK        = (255, 182, 193)
COLOR_DARK_PINK   = (255, 105, 135)
COLOR_YELLOW      = (255, 230, 100)
COLOR_ORANGE      = (255, 160, 60)
COLOR_SKY_BLUE    = (135, 206, 235)
COLOR_PURPLE      = (180, 130, 255)
COLOR_LIGHT_GRAY  = (200, 210, 220)
COLOR_CHAR_BODY   = (255, 200, 150)   # 肤色（浅橙色）
COLOR_CHEEK       = (255, 160, 160)   # 腮红
COLOR_HAT         = (220, 60, 80)     # 帽子红色

# ============================================================
# 函数：绘制可爱角色（小猫）
# ============================================================
def draw_character_surface(size: int) -> pygame.Surface:
    """
    在指定尺寸的 Surface 上绘制一个可爱的小猫角色。
    返回带有 alpha 通道的 Surface（已调用 convert_alpha 优化性能）。
    """
    # 创建带透明通道的 Surface
    surf = pygame.Surface((size, size), pygame.SRCALPHA)
    surf.fill((0, 0, 0, 0))  # 透明背景

    center_x = size // 2
    center_y = size // 2
    r = size // 2 - 4        # 主体半径，留一点边距

    # ---------- 帽子 ----------
    hat_left  = center_x - int(r * 0.7)
    hat_right = center_x + int(r * 0.7)
    hat_top   = center_y - int(r * 1.3)
    hat_mid   = center_y - int(r * 0.95)
    hat_bottom = center_y - int(r * 0.75)
    hat_ball_y = hat_top - int(r * 0.15)

    pygame.draw.rect(surf, COLOR_HAT,
                     (hat_left, hat_mid, hat_right - hat_left, hat_bottom - hat_mid))
    pygame.draw.polygon(surf, COLOR_HAT, [
        (hat_left,  hat_mid),
        (hat_right, hat_mid),
        (center_x,  hat_top + r // 8)
    ])
    pygame.draw.circle(surf, COLOR_WHITE, (center_x, hat_ball_y), int(r * 0.12))

    # ---------- 耳朵（两只三角形） ----------
    ear_offset_x = int(r * 0.85)
    ear_offset_y = int(r * 0.20)
    ear_width    = int(r * 0.35)
    ear_height   = int(r * 0.70)

    # 左耳
    left_ear_points = [
        (center_x - ear_offset_x, center_y - ear_offset_y),
        (center_x - ear_offset_x - ear_width//2, center_y - ear_offset_y - ear_height),
        (center_x - ear_offset_x - ear_width,  center_y - ear_offset_y)
    ]
    pygame.draw.polygon(surf, COLOR_CHAR_BODY, left_ear_points)
    # 左耳内部
    inner_left = [
        (center_x - ear_offset_x, center_y - ear_offset_y + 5),
        (center_x - ear_offset_x - ear_width//3, center_y - ear_offset_y - ear_height + 10),
        (center_x - ear_offset_x - ear_width + 5, center_y - ear_offset_y + 5)
    ]
    pygame.draw.polygon(surf, COLOR_PINK, inner_left)

    # 右耳
    right_ear_points = [
        (center_x + ear_offset_x, center_y - ear_offset_y),
        (center_x + ear_offset_x + ear_width//2, center_y - ear_offset_y - ear_height),
        (center_x + ear_offset_x + ear_width,  center_y - ear_offset_y)
    ]
    pygame.draw.polygon(surf, COLOR_CHAR_BODY, right_ear_points)
    # 右耳内部
    inner_right = [
        (center_x + ear_offset_x, center_y - ear_offset_y + 5),
        (center_x + ear_offset_x + ear_width//3, center_y - ear_offset_y - ear_height + 10),
        (center_x + ear_offset_x + ear_width - 5, center_y - ear_offset_y + 5)
    ]
    pygame.draw.polygon(surf, COLOR_PINK, inner_right)

    # ---------- 头部主体（圆形） ----------
    # 主体肤色大圆
    pygame.draw.circle(surf, COLOR_CHAR_BODY, (center_x, center_y), r)
    # 深色描边
    pygame.draw.circle(surf, (200, 120, 60), (center_x, center_y), r, 2)

    # ---------- 眼睛 ----------
    eye_offset_x = int(r * 0.35)
    eye_offset_y = int(r * 0.10)
    eye_width    = int(r * 0.28)
    eye_height   = int(r * 0.38)

    # 左眼
    left_eye_rect = pygame.Rect(
        center_x - eye_offset_x - eye_width // 2,
        center_y - eye_offset_y - eye_height // 2,
        eye_width, eye_height
    )
    pygame.draw.ellipse(surf, COLOR_WHITE, left_eye_rect)
    # 左眼瞳孔
    pupil_radius = int(eye_width * 0.35)
    pygame.draw.circle(surf, COLOR_BLACK,
                       (center_x - eye_offset_x, center_y - eye_offset_y + 2), pupil_radius)
    # 左眼高光
    pygame.draw.circle(surf, COLOR_WHITE,
                       (center_x - eye_offset_x + pupil_radius//2,
                        center_y - eye_offset_y - pupil_radius//2), pupil_radius // 3)

    # 右眼
    right_eye_rect = pygame.Rect(
        center_x + eye_offset_x - eye_width // 2,
        center_y - eye_offset_y - eye_height // 2,
        eye_width, eye_height
    )
    pygame.draw.ellipse(surf, COLOR_WHITE, right_eye_rect)
    pygame.draw.circle(surf, COLOR_BLACK,
                       (center_x + eye_offset_x, center_y - eye_offset_y + 2), pupil_radius)
    pygame.draw.circle(surf, COLOR_WHITE,
                       (center_x + eye_offset_x + pupil_radius//2,
                        center_y - eye_offset_y - pupil_radius//2), pupil_radius // 3)

    # ---------- 腮红 ----------
    cheek_offset_x = int(r * 0.55)
    cheek_offset_y = int(r * 0.40)
    cheek_radius   = int(r * 0.15)
    pygame.draw.circle(surf, COLOR_CHEEK,
                       (center_x - cheek_offset_x, center_y + cheek_offset_y), cheek_radius)
    pygame.draw.circle(surf, COLOR_CHEEK,
                       (center_x + cheek_offset_x, center_y + cheek_offset_y), cheek_radius)

    # ---------- 鼻子 ----------
    nose_y = center_y + int(r * 0.12)
    nose_size = int(r * 0.13)
    nose_points = [
        (center_x, nose_y - nose_size),
        (center_x + nose_size, nose_y + nose_size),
        (center_x - nose_size, nose_y + nose_size),
    ]
    pygame.draw.polygon(surf, COLOR_DARK_PINK, nose_points)
    # 鼻子高光
    pygame.draw.circle(surf, COLOR_WHITE,
                       (center_x - nose_size//3, nose_y - nose_size//4), nose_size // 3)

    # ---------- 嘴巴 ----------
    mouth_y = nose_y + nose_size + int(r * 0.08)
    # 中间的竖线
    pygame.draw.line(surf, COLOR_BLACK,
                     (center_x, nose_y + nose_size),
                     (center_x, mouth_y + int(r * 0.15)), 2)
    # 左边的弧线（用两条短线模拟微笑）
    pygame.draw.arc(surf, COLOR_BLACK,
                    (center_x - int(r * 0.25), mouth_y - int(r * 0.05),
                     int(r * 0.25), int(r * 0.20)),
                    3.14 * 0.1, 3.14 * 0.5, 2)
    # 右边的弧线
    pygame.draw.arc(surf, COLOR_BLACK,
                    (center_x, mouth_y - int(r * 0.05),
                     int(r * 0.25), int(r * 0.20)),
                    3.14 * 0.5, 3.14 * 0.9, 2)

    # ---------- 胡须 ----------
    whisker_length = int(r * 0.40)
    whisker_y1 = nose_y + int(r * 0.02)
    whisker_y2 = nose_y + int(r * 0.15)

    # 左侧胡须
    pygame.draw.line(surf, COLOR_BLACK,
                     (center_x - int(r * 0.35), whisker_y1),
                     (center_x - int(r * 0.35) - whisker_length, whisker_y1 - 8), 2)
    pygame.draw.line(surf, COLOR_BLACK,
                     (center_x - int(r * 0.35), whisker_y2),
                     (center_x - int(r * 0.35) - whisker_length, whisker_y2), 2)

    # 右侧胡须
    pygame.draw.line(surf, COLOR_BLACK,
                     (center_x + int(r * 0.35), whisker_y1),
                     (center_x + int(r * 0.35) + whisker_length, whisker_y1 - 8), 2)
    pygame.draw.line(surf, COLOR_BLACK,
                     (center_x + int(r * 0.35), whisker_y2),
                     (center_x + int(r * 0.35) + whisker_length, whisker_y2), 2)

    # ---------- 身体（小圆形） ----------
    body_y = center_y + r + int(r * 0.05)
    body_radius = int(r * 0.45)
    pygame.draw.circle(surf, COLOR_CHAR_BODY, (center_x, body_y), body_radius)
    pygame.draw.circle(surf, (200, 120, 60), (center_x, body_y), body_radius, 2)
    # 肚皮白色椭圆
    pygame.draw.ellipse(surf, COLOR_WHITE,
                        (center_x - int(body_radius * 0.55),
                         body_y - int(body_radius * 0.35),
                         int(body_radius * 1.1),
                         int(body_radius * 0.9)))

    # ---------- 小围巾/蝴蝶结 ----------
    bow_y = center_y + int(r * 0.75)
    bow_x = center_x
    bow_size = int(r * 0.15)
    # 左蝴蝶结
    pygame.draw.polygon(surf, COLOR_YELLOW, [
        (bow_x, bow_y),
        (bow_x - bow_size, bow_y - bow_size),
        (bow_x - bow_size, bow_y + bow_size),
    ])
    # 右蝴蝶结
    pygame.draw.polygon(surf, COLOR_YELLOW, [
        (bow_x, bow_y),
        (bow_x + bow_size, bow_y - bow_size),
        (bow_x + bow_size, bow_y + bow_size),
    ])
    pygame.draw.circle(surf, COLOR_ORANGE, (bow_x, bow_y), bow_size // 2)

    # 调用 convert_alpha 优化 blit 性能
    return surf.convert_alpha()


# ============================================================
# 函数：切换大小索引（在 0 / 1 / 2 之间循环）
# ============================================================
def toggle_size_index(current_index: int) -> int:
    """
    接收当前大小索引，返回下一个大小索引（0→1→2→0 循环）。
    """
    return (current_index + 1) % len(SIZE_SCALES)


# ============================================================
# 函数：主循环
# ============================================================
def main():
    """
    程序主函数：创建窗口、绘制角色、处理鼠标事件、进入主循环。
    """
    # ---------- 创建窗口 ----------
    screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
    pygame.display.set_caption("第4节：鼠标与图片 —— 可爱小猫跟你走！")

    # ---------- 时钟对象，控制帧率 ----------
    clock = pygame.time.Clock()

    # ---------- 预绘制原始角色 Surface（基础尺寸）----------
    base_surface = draw_character_surface(CHAR_BASE_SIZE)

    # ---------- 状态变量 ----------
    size_index = 1                        # 初始为中等大小（SIZE_SCALES[1] = 1.0）
    char_pos_x = SCREEN_WIDTH // 2        # 角色中心 X（初始居中）
    char_pos_y = SCREEN_HEIGHT // 2       # 角色中心 Y（初始居中）
    running = True                        # 主循环控制变量

    # ---------- 主循环 ----------
    while running:
        # ---- 事件处理 ----
        for event in pygame.event.get():
            # 关闭窗口（点击 X）或按下 ESC 键 → 退出
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE:
                running = False

            # 鼠标移动 → 角色跟随鼠标
            elif event.type == pygame.MOUSEMOTION:
                char_pos_x, char_pos_y = event.pos

            # 鼠标点击 → 切换角色大小
            elif event.type == pygame.MOUSEBUTTONDOWN:
                size_index = toggle_size_index(size_index)

        # ---- 计算当前缩放后的角色 Surface ----
        current_scale = SIZE_SCALES[size_index]
        new_width  = int(CHAR_BASE_SIZE * current_scale)
        new_height = int(CHAR_BASE_SIZE * current_scale)
        # 使用 pygame.transform.scale 缩放角色
        scaled_surface = pygame.transform.scale(base_surface, (new_width, new_height))

        # ---- 计算角色的绘制位置（使角色中心对准鼠标）----
        char_rect = scaled_surface.get_rect()
        char_rect.center = (char_pos_x, char_pos_y)

        # ---- 绘制画面 ----
        screen.fill(BACKGROUND_COLOR)                 # 清屏

        # 绘制装饰：跟随鼠标的彩色光晕（多个半透明圆）
        for i in range(3, 0, -1):
            alpha_color = (100 - i * 20, 140 - i * 20, 220 - i * 20)
            glow_radius = new_width // 2 + i * 15
            glow_surf = pygame.Surface((glow_radius * 2, glow_radius * 2), pygame.SRCALPHA)
            pygame.draw.circle(glow_surf, (*alpha_color, 30),
                               (glow_radius, glow_radius), glow_radius)
            glow_rect = glow_surf.get_rect(center=(char_pos_x, char_pos_y))
            screen.blit(glow_surf, glow_rect)

        screen.blit(scaled_surface, char_rect)        # 绘制角色

        # 显示大小提示文字
        font = pygame.font.SysFont("simhei", 24)
        size_labels = ["小", "中", "大"]
        hint_text = font.render(
            f"当前大小：{size_labels[size_index]}（点击鼠标切换）  按 ESC 退出",
            True, COLOR_WHITE
        )
        screen.blit(hint_text, (20, SCREEN_HEIGHT - 50))

        pygame.display.flip()                         # 刷新屏幕

        # ---- 帧率控制 ----
        clock.tick(FPS)

    # ---------- 退出程序 ----------
    pygame.quit()
    sys.exit()


# ============================================================
# 程序入口
# ============================================================
if __name__ == "__main__":
    main()
