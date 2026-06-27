"""
第12节：限时挑战 — 完整打地鼠游戏
知识点：get_ticks()倒计时、计分系统（+10/-5）、难度分级、
        游戏状态管理、Game Over 画面
"""

import pygame
import random
import math

# ==================== 初始化 Pygame ====================
pygame.init()
WIDTH, HEIGHT = 800, 600
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("限时挑战 - 第12节")
clock = pygame.time.Clock()

# ==================== 颜色定义 ====================
COLOR_SKY_BLUE = (135, 206, 235)
COLOR_GRASS_GREEN = (34, 139, 34)
COLOR_HOLE_DARK = (60, 35, 15)
COLOR_HOLE_RIM = (120, 80, 40)
COLOR_MOLE_BODY = (139, 90, 43)
COLOR_MOLE_DARK = (100, 65, 30)
COLOR_WHITE = (255, 255, 255)
COLOR_BLACK = (0, 0, 0)
COLOR_PINK = (255, 182, 193)
COLOR_YELLOW = (255, 255, 0)
COLOR_RED = (255, 60, 60)
COLOR_GREEN = (0, 200, 0)
COLOR_GRAY = (150, 150, 150)
COLOR_DARK_GRAY = (80, 80, 80)
COLOR_ORANGE = (255, 165, 0)
COLOR_GOLD = (255, 215, 0)

# ==================== 游戏配置 ====================
GAME_DURATION = 30  # 游戏时长（秒）

# 难度配置：不同难度对应不同的地鼠换洞间隔（毫秒）
DIFFICULTY_CONFIG = {
    "简单": {"interval": 1200, "color": COLOR_GREEN},
    "普通": {"interval": 800, "color": COLOR_YELLOW},
    "困难": {"interval": 500, "color": COLOR_RED},
}

# ==================== 九宫格布局参数 ====================
GRID_COLS = 3
GRID_ROWS = 3
HOLE_WIDTH = 140
HOLE_HEIGHT = 120
MARGIN_LEFT = 100
MARGIN_TOP = 140
COL_SPACING = 200
ROW_SPACING = 150

# 生成 9 个洞口的 Rect 列表
holes = []
for row in range(GRID_ROWS):
    for col in range(GRID_COLS):
        cx = MARGIN_LEFT + col * COL_SPACING + HOLE_WIDTH // 2
        cy = MARGIN_TOP + row * ROW_SPACING + HOLE_HEIGHT // 2
        hole_rect = pygame.Rect(0, 0, HOLE_WIDTH, HOLE_HEIGHT)
        hole_rect.center = (cx, cy)
        holes.append(hole_rect)

# ==================== 游戏状态变量 ====================
# game_state: "menu" / "playing" / "gameover"
game_state = "menu"
current_difficulty = "普通"   # 默认难度
current_mole = -1            # 当前地鼠所在的洞索引，-1 表示没有
mole_hit = False             # 地鼠是否被打中
hit_timer = 0                # 被打击中效果帧数
hit_effect_pos = None        # 打中效果位置
hit_effect_timer = 0         # 打中效果持续帧数

score = 0                    # 玩家得分
combo = 0                    # 连击计数
best_score = 0               # 最高分记录（本局）

start_ticks = 0              # 游戏开始时的毫秒数
remaining_seconds = GAME_DURATION

# 自定义事件：地鼠换洞
MOLE_CHANGE_EVENT = pygame.USEREVENT + 1

# 设置默认难度的定时器
pygame.time.set_timer(MOLE_CHANGE_EVENT, DIFFICULTY_CONFIG[current_difficulty]["interval"])


# ==================== 辅助函数 ====================

def set_difficulty(level):
    """切换难度并重新设置定时器间隔"""
    global current_difficulty
    current_difficulty = level
    interval = DIFFICULTY_CONFIG[level]["interval"]
    pygame.time.set_timer(MOLE_CHANGE_EVENT, interval)


def reset_game():
    """重置所有游戏变量，准备新一局"""
    global current_mole, mole_hit, hit_timer
    global hit_effect_pos, hit_effect_timer
    global score, combo, start_ticks, remaining_seconds

    current_mole = -1
    mole_hit = False
    hit_timer = 0
    hit_effect_pos = None
    hit_effect_timer = 0
    score = 0
    combo = 0
    start_ticks = pygame.time.get_ticks()
    remaining_seconds = GAME_DURATION
    spawn_mole()


def spawn_mole():
    """随机选择一个洞口让地鼠出现"""
    global current_mole, mole_hit
    current_mole = random.randint(0, 8)
    mole_hit = False


# ==================== 绘制函数 ====================

def draw_background():
    """绘制天空和草地背景"""
    # 天空渐变
    for i in range(HEIGHT):
        ratio = i / HEIGHT
        r = int(135 * (1 - ratio) + 34 * ratio)
        g = int(206 * (1 - ratio) + 139 * ratio)
        b = int(235 * (1 - ratio) + 34 * ratio)
        pygame.draw.line(screen, (r, g, b), (0, i), (WIDTH, i))

    # 草地
    ground_rect = pygame.Rect(0, MARGIN_TOP - 30, WIDTH, HEIGHT - MARGIN_TOP + 30)
    pygame.draw.rect(screen, COLOR_GRASS_GREEN, ground_rect)

    # 装饰草地纹理
    for i in range(0, WIDTH, 25):
        grass_h = random.randint(8, 18)
        grass_x = i + random.randint(-5, 5)
        grass_y = MARGIN_TOP - 30 + random.randint(-3, 3)
        pygame.draw.line(screen, (50, 160, 50), (grass_x, grass_y),
                         (grass_x + random.randint(-3, 3), grass_y - grass_h), 2)


def draw_hole(hole_rect):
    """绘制地鼠洞（椭圆形深坑）"""
    shadow_rect = hole_rect.inflate(16, 10)
    pygame.draw.ellipse(screen, COLOR_HOLE_DARK, shadow_rect)
    pygame.draw.ellipse(screen, COLOR_HOLE_RIM, hole_rect)
    inner_rect = hole_rect.inflate(-20, -16)
    pygame.draw.ellipse(screen, (30, 18, 8), inner_rect)


def draw_mole(hole_rect):
    """绘制地鼠（身体 + 耳朵 + 眼睛 + 鼻子 + 胡须 + 牙齿）"""
    body_width = HOLE_WIDTH - 30
    body_height = HOLE_HEIGHT - 10

    body_rect = pygame.Rect(0, 0, body_width, body_height)
    body_rect.centerx = hole_rect.centerx
    body_rect.bottom = hole_rect.bottom - 5

    body_color = COLOR_RED if mole_hit else COLOR_MOLE_BODY

    # 身体
    pygame.draw.ellipse(screen, body_color, body_rect)
    pygame.draw.ellipse(screen, COLOR_MOLE_DARK, body_rect, 2)

    # 耳朵
    ear_w, ear_h = 20, 18
    for side in [-1, 1]:
        ear = pygame.Rect(0, 0, ear_w, ear_h)
        ear.centerx = body_rect.centerx + side * 22
        ear.bottom = body_rect.top + 15
        pygame.draw.ellipse(screen, body_color, ear)
        pygame.draw.ellipse(screen, COLOR_MOLE_DARK, ear, 2)

    eye_r = 9
    left_eye_center = (body_rect.centerx - 14, body_rect.centery - 8)
    right_eye_center = (body_rect.centerx + 14, body_rect.centery - 8)

    if mole_hit:
        # 被打中：X_X 眼
        xo = 5
        for eye in [left_eye_center, right_eye_center]:
            pygame.draw.line(screen, COLOR_BLACK,
                             (eye[0] - xo, eye[1] - xo),
                             (eye[0] + xo, eye[1] + xo), 3)
            pygame.draw.line(screen, COLOR_BLACK,
                             (eye[0] - xo, eye[1] + xo),
                             (eye[0] + xo, eye[1] - xo), 3)
    else:
        # 正常眼睛
        for eye in [left_eye_center, right_eye_center]:
            pygame.draw.circle(screen, COLOR_WHITE, eye, eye_r)
            pygame.draw.circle(screen, COLOR_BLACK, eye, eye_r // 2)

    # 鼻子
    nose_center = (body_rect.centerx, body_rect.centery + 10)
    nose_rect = pygame.Rect(0, 0, 14, 10)
    nose_rect.center = nose_center
    pygame.draw.ellipse(screen, COLOR_PINK, nose_rect)

    # 胡须
    whisker_y = nose_center[1]
    for side in [-1, 1]:
        pygame.draw.line(screen, (80, 50, 30),
                         (nose_center[0] + side * 7, whisker_y),
                         (nose_center[0] + side * 28, whisker_y - 5), 1)
        pygame.draw.line(screen, (80, 50, 30),
                         (nose_center[0] + side * 7, whisker_y),
                         (nose_center[0] + side * 28, whisker_y + 5), 1)

    # 牙齿
    tooth_w, tooth_h = 7, 9
    for side in [-1, 1]:
        tooth = pygame.Rect(0, 0, tooth_w, tooth_h)
        tooth.centerx = nose_center[0] + side * 5
        tooth.top = nose_center[1] + 5
        pygame.draw.rect(screen, COLOR_WHITE, tooth)
        pygame.draw.rect(screen, (200, 200, 200), tooth, 1)


def draw_hit_effect(pos):
    """打中效果：放射状星形 + 分数弹出"""
    x, y = pos
    for angle in range(0, 360, 45):
        rad = math.radians(angle)
        end_x = x + math.cos(rad) * 30
        end_y = y + math.sin(rad) * 30
        pygame.draw.line(screen, COLOR_YELLOW, (x, y), (end_x, end_y), 3)
    pygame.draw.circle(screen, COLOR_RED, (x, y), 8)

    # 显示"+10"文字
    font = pygame.font.Font(None, 40)
    text = font.render("+10", True, COLOR_YELLOW)
    screen.blit(text, (x - 20, y - 50))


def draw_hud():
    """绘制游戏中的 HUD（倒计时 + 分数 + 难度）"""
    font = pygame.font.Font(None, 40)

    # 倒计时（左上角）
    if remaining_seconds > 10:
        timer_color = COLOR_WHITE
    elif remaining_seconds > 5:
        timer_color = COLOR_YELLOW  # 少于10秒变黄
    else:
        timer_color = COLOR_RED     # 少于5秒变红（紧急）

    timer_text = font.render(f"⏱ 剩余: {remaining_seconds} 秒", True, timer_color)
    screen.blit(timer_text, (20, 20))

    # 分数（右上角）
    score_text = font.render(f"🏆 分数: {score}", True, COLOR_YELLOW)
    score_rect = score_text.get_rect(topright=(WIDTH - 20, 20))
    screen.blit(score_text, score_rect)

    # 难度（左上角第二行）
    diff_font = pygame.font.Font(None, 30)
    diff_color = DIFFICULTY_CONFIG[current_difficulty]["color"]
    diff_text = diff_font.render(f"难度: {current_difficulty}", True, diff_color)
    screen.blit(diff_text, (20, 60))

    # 连击显示（如果有连击）
    if combo >= 2:
        combo_font = pygame.font.Font(None, 36)
        combo_text = combo_font.render(f"🔥 {combo}连击!", True, COLOR_ORANGE)
        combo_rect = combo_text.get_rect(center=(WIDTH // 2, 60))
        screen.blit(combo_text, combo_rect)


def draw_menu():
    """绘制开始菜单：标题 + 难度选择 + 开始按钮"""
    # 标题
    title_font = pygame.font.Font(None, 60)
    title_text = title_font.render("🐹 限时打地鼠大挑战", True, COLOR_GOLD)
    title_rect = title_text.get_rect(center=(WIDTH // 2, 100))
    # 标题阴影
    shadow_text = title_font.render("🐹 限时打地鼠大挑战", True, COLOR_BLACK)
    screen.blit(shadow_text, title_rect.move(3, 3))
    screen.blit(title_text, title_rect)

    # 副标题
    sub_font = pygame.font.Font(None, 36)
    sub_text = sub_font.render(f"30 秒内尽可能多地打中地鼠！", True, COLOR_WHITE)
    sub_rect = sub_text.get_rect(center=(WIDTH // 2, 160))
    screen.blit(sub_text, sub_rect)

    # 难度选择标题
    diff_title_font = pygame.font.Font(None, 40)
    diff_title = diff_title_font.render("选择难度：", True, COLOR_WHITE)
    diff_title_rect = diff_title.get_rect(center=(WIDTH // 2, 230))
    screen.blit(diff_title, diff_title_rect)

    # 难度按钮
    button_font = pygame.font.Font(None, 36)
    difficulty_buttons = []
    btn_width, btn_height = 140, 50
    total_btns_width = len(DIFFICULTY_CONFIG) * btn_width + (len(DIFFICULTY_CONFIG) - 1) * 20
    btn_start_x = (WIDTH - total_btns_width) // 2

    for i, (name, config) in enumerate(DIFFICULTY_CONFIG.items()):
        btn_x = btn_start_x + i * (btn_width + 20)
        btn_y = 280
        btn_rect = pygame.Rect(btn_x, btn_y, btn_width, btn_height)

        # 当前选中的难度高亮
        if name == current_difficulty:
            bg_color = config["color"]
            border_color = COLOR_WHITE
        else:
            bg_color = COLOR_DARK_GRAY
            border_color = COLOR_GRAY

        pygame.draw.rect(screen, bg_color, btn_rect, border_radius=10)
        pygame.draw.rect(screen, border_color, btn_rect, 3, border_radius=10)

        btn_text = button_font.render(name, True, COLOR_WHITE)
        btn_text_rect = btn_text.get_rect(center=btn_rect.center)
        screen.blit(btn_text, btn_text_rect)

        difficulty_buttons.append((btn_rect, name))

    # 难度说明文字
    desc_font = pygame.font.Font(None, 28)
    desc_text = desc_font.render(
        f"地鼠每 {DIFFICULTY_CONFIG[current_difficulty]['interval'] / 1000:.1f} 秒换一次位置",
        True, COLOR_GRAY)
    desc_rect = desc_text.get_rect(center=(WIDTH // 2, 360))
    screen.blit(desc_text, desc_rect)

    # 开始按钮
    start_btn_width, start_btn_height = 220, 65
    start_btn_rect = pygame.Rect(0, 0, start_btn_width, start_btn_height)
    start_btn_rect.center = (WIDTH // 2, 440)

    # 按钮呼吸动画效果
    pulse = math.sin(pygame.time.get_ticks() * 0.003) * 0.2 + 0.8
    pulse_color = (
        int(0 * pulse + 200 * (1 - pulse)),
        int(180 * pulse + 50 * (1 - pulse)),
        int(0 * pulse + 50 * (1 - pulse)),
    )

    pygame.draw.rect(screen, COLOR_GREEN, start_btn_rect, border_radius=15)
    pygame.draw.rect(screen, COLOR_WHITE, start_btn_rect, 3, border_radius=15)

    start_font = pygame.font.Font(None, 48)
    start_text = start_font.render("🎮 开始游戏", True, COLOR_WHITE)
    start_text_rect = start_text.get_rect(center=start_btn_rect.center)
    screen.blit(start_text, start_text_rect)

    # 计分规则说明
    rule_font = pygame.font.Font(None, 26)
    rules = [
        "规则：打中地鼠 +10 分 | 空点（点洞口没地鼠）-5 分",
        "按 ← → 方向键翻页",
    ]
    for i, rule in enumerate(rules):
        rule_text = rule_font.render(rule, True, COLOR_GRAY)
        rule_rect = rule_text.get_rect(center=(WIDTH // 2, 530 + i * 30))
        screen.blit(rule_text, rule_rect)

    return difficulty_buttons, start_btn_rect


def draw_gameover():
    """绘制 Game Over 画面：半透明遮罩 + 得分 + 重新开始按钮"""
    # 半透明黑色遮罩
    overlay = pygame.Surface((WIDTH, HEIGHT))
    overlay.set_alpha(190)
    overlay.fill((0, 0, 0))
    screen.blit(overlay, (0, 0))

    # 标题"游戏结束"
    big_font = pygame.font.Font(None, 72)
    title_text = big_font.render("游戏结束!", True, COLOR_RED)
    title_rect = title_text.get_rect(center=(WIDTH // 2, 130))
    # 阴影
    shadow = big_font.render("游戏结束!", True, COLOR_BLACK)
    screen.blit(shadow, title_rect.move(4, 4))
    screen.blit(title_text, title_rect)

    # 分数面板背景
    panel_rect = pygame.Rect(0, 0, 400, 200)
    panel_rect.center = (WIDTH // 2, 280)
    pygame.draw.rect(screen, (30, 30, 50), panel_rect, border_radius=16)
    pygame.draw.rect(screen, COLOR_GRAY, panel_rect, 2, border_radius=16)

    # 最终得分
    score_font = pygame.font.Font(None, 52)
    score_text = score_font.render(f"最终得分: {score}", True, COLOR_GOLD)
    score_text_rect = score_text.get_rect(center=(WIDTH // 2, 230))
    screen.blit(score_text, score_text_rect)

    # 难度信息
    diff_font = pygame.font.Font(None, 36)
    diff_text = diff_font.render(f"难度: {current_difficulty}", True, COLOR_WHITE)
    diff_text_rect = diff_text.get_rect(center=(WIDTH // 2, 280))
    screen.blit(diff_text, diff_text_rect)

    # 最高分
    if score >= best_score and score > 0:
        best_text = diff_font.render("🎉 新纪录！", True, COLOR_GOLD)
    else:
        best_text = diff_font.render(f"最高分: {best_score}", True, COLOR_GRAY)
    best_text_rect = best_text.get_rect(center=(WIDTH // 2, 325))
    screen.blit(best_text, best_text_rect)

    # 评价文字
    eval_font = pygame.font.Font(None, 40)
    if score >= 100:
        evaluation = "🏆 打地鼠大师！"
        eval_color = COLOR_GOLD
    elif score >= 50:
        evaluation = "👍 很不错！"
        eval_color = COLOR_GREEN
    elif score >= 20:
        evaluation = "😊 继续加油！"
        eval_color = COLOR_YELLOW
    elif score >= 0:
        evaluation = "🤔 还需练习..."
        eval_color = COLOR_GRAY
    else:
        evaluation = "😅 下次别乱点了..."
        eval_color = COLOR_RED

    eval_text = eval_font.render(evaluation, True, eval_color)
    eval_text_rect = eval_text.get_rect(center=(WIDTH // 2, 380))
    screen.blit(eval_text, eval_text_rect)

    # 重新开始按钮
    restart_btn = pygame.Rect(0, 0, 240, 60)
    restart_btn.center = (WIDTH // 2 - 130, 470)

    pygame.draw.rect(screen, (0, 140, 0), restart_btn, border_radius=12)
    pygame.draw.rect(screen, COLOR_WHITE, restart_btn, 3, border_radius=12)

    restart_font = pygame.font.Font(None, 40)
    restart_text = restart_font.render("🔄 再来一局", True, COLOR_WHITE)
    restart_text_rect = restart_text.get_rect(center=restart_btn.center)
    screen.blit(restart_text, restart_text_rect)

    # 返回菜单按钮
    menu_btn = pygame.Rect(0, 0, 240, 60)
    menu_btn.center = (WIDTH // 2 + 130, 470)

    pygame.draw.rect(screen, (100, 100, 100), menu_btn, border_radius=12)
    pygame.draw.rect(screen, COLOR_WHITE, menu_btn, 3, border_radius=12)

    menu_btn_text = restart_font.render("📋 返回菜单", True, COLOR_WHITE)
    menu_btn_text_rect = menu_btn_text.get_rect(center=menu_btn.center)
    screen.blit(menu_btn_text, menu_btn_text_rect)

    # 提示：按 R 键也可以重新开始
    hint_font = pygame.font.Font(None, 26)
    hint_text = hint_font.render("按 R 键重新开始 | 按 ESC 返回菜单", True, COLOR_GRAY)
    hint_text_rect = hint_text.get_rect(center=(WIDTH // 2, 545))
    screen.blit(hint_text, hint_text_rect)

    return restart_btn, menu_btn


# ==================== 主循环 ====================
running = True

while running:
    # ========== 事件处理 ==========
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        # --- 键盘事件（全局） ---
        if event.type == pygame.KEYDOWN:
            if game_state == "gameover" and event.key == pygame.K_r:
                # R 键重新开始
                reset_game()
                game_state = "playing"
            elif game_state == "gameover" and event.key == pygame.K_ESCAPE:
                # ESC 返回菜单
                game_state = "menu"

        # --- 菜单状态 ---
        if game_state == "menu":
            if event.type == pygame.MOUSEBUTTONDOWN:
                mouse_pos = event.pos

                # 检查是否点击了难度按钮
                for btn_rect, name in menu_buttons:
                    if btn_rect.collidepoint(mouse_pos):
                        set_difficulty(name)

                # 检查是否点击了开始按钮
                if start_button_rect.collidepoint(mouse_pos):
                    reset_game()
                    game_state = "playing"

        # --- 游戏中状态 ---
        elif game_state == "playing":
            if event.type == MOLE_CHANGE_EVENT:
                # 定时器触发：地鼠换洞
                spawn_mole()

            elif event.type == pygame.MOUSEBUTTONDOWN:
                mouse_x, mouse_y = event.pos
                hit_something = False

                # 检查是否点中了当前有地鼠的洞
                if current_mole != -1:
                    mole_rect = holes[current_mole]
                    if mole_rect.collidepoint(mouse_x, mouse_y):
                        # 🎯 打中地鼠！
                        combo += 1              # 连击 +1
                        bonus = (combo - 1) * 2  # 连击奖励：第1只+10, 第2只+12, 第3只+14...
                        points = 10 + bonus
                        score += points
                        mole_hit = True
                        hit_timer = 12          # 显示被打效果
                        hit_effect_pos = event.pos
                        hit_effect_timer = 12
                        hit_something = True

                # 如果没有打中地鼠，但点到了任意洞口 → 空点扣分
                if not hit_something:
                    for hole_rect in holes:
                        if hole_rect.collidepoint(mouse_x, mouse_y):
                            score -= 5
                            combo = 0  # 空点重置连击
                            break

        # --- Game Over 状态 ---
        elif game_state == "gameover":
            if event.type == pygame.MOUSEBUTTONDOWN:
                mouse_pos = event.pos

                if restart_button_rect.collidepoint(mouse_pos):
                    # 点击"再来一局"
                    if score > best_score:
                        best_score = score
                    reset_game()
                    game_state = "playing"

                elif menu_button_rect.collidepoint(mouse_pos):
                    # 点击"返回菜单"
                    if score > best_score:
                        best_score = score
                    game_state = "menu"

    # ========== 更新逻辑 ==========
    if game_state == "playing":
        # 计算剩余时间
        elapsed_ms = pygame.time.get_ticks() - start_ticks
        remaining_seconds = GAME_DURATION - elapsed_ms // 1000
        if remaining_seconds <= 0:
            remaining_seconds = 0
            if score > best_score:
                best_score = score
            game_state = "gameover"

        # 被打效果计时器
        if hit_timer > 0:
            hit_timer -= 1
            if hit_timer == 0:
                current_mole = -1
                mole_hit = False

        if hit_effect_timer > 0:
            hit_effect_timer -= 1

    # ========== 绘制画面 ==========
    draw_background()

    if game_state == "menu":
        # 绘制菜单
        menu_buttons, start_button_rect = draw_menu()

    elif game_state == "playing":
        # 绘制 HUD
        draw_hud()

        # 绘制所有洞口和地鼠
        for i, hole_rect in enumerate(holes):
            draw_hole(hole_rect)
            if i == current_mole:
                draw_mole(hole_rect)

        # 绘制打中效果
        if hit_effect_timer > 0 and hit_effect_pos:
            draw_hit_effect(hit_effect_pos)

    elif game_state == "gameover":
        # 先绘制底层的游戏画面（所有洞口 + 最后的地鼠状态）
        draw_hud()
        for i, hole_rect in enumerate(holes):
            draw_hole(hole_rect)
            if i == current_mole:
                draw_mole(hole_rect)

        # 再叠上 Game Over 画面
        restart_button_rect, menu_button_rect = draw_gameover()

    # 刷新屏幕
    pygame.display.flip()
    clock.tick(60)

pygame.quit()
