"""
第22节：人机对战 — Pong项目第二节课
====================================
功能：
  - 玩家（W/S控制左球拍） vs AI（右球拍自动追踪球）
  - AI速度略慢于球速度，模拟反应时间
  - 得分系统：先到11分者胜
  - 得分后重新发球（随机方向）
  - 半透明中线和虚线网
  - 按P键暂停/继续
  - 按R键重新开始（游戏结束后）
  - 所有图形使用Surface/draw.rect/font绘制，不依赖外部图片文件
"""

import pygame
import random
import sys

# ============================================================
# 初始化
# ============================================================
pygame.init()

# 窗口设置
SCREEN_WIDTH = 800
SCREEN_HEIGHT = 500
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Pong - 人机对战")

# 颜色常量
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
GRAY = (180, 180, 180)
DARK_GRAY = (60, 60, 60)
RED = (255, 80, 80)
GREEN = (80, 255, 80)
YELLOW = (255, 255, 80)

# 字体（使用系统默认中文字体）
try:
    font_score = pygame.font.Font("/System/Library/Fonts/PingFang.ttc", 48)
    font_info = pygame.font.Font("/System/Library/Fonts/PingFang.ttc", 28)
    font_small = pygame.font.Font("/System/Library/Fonts/PingFang.ttc", 20)
except FileNotFoundError:
    # Windows 系统回退
    try:
        font_score = pygame.font.Font("C:/Windows/Fonts/msyh.ttc", 48)
        font_info = pygame.font.Font("C:/Windows/Fonts/msyh.ttc", 28)
        font_small = pygame.font.Font("C:/Windows/Fonts/msyh.ttc", 20)
    except FileNotFoundError:
        # 最终回退：使用 pygame 默认字体
        font_score = pygame.font.Font(None, 48)
        font_info = pygame.font.Font(None, 28)
        font_small = pygame.font.Font(None, 20)

# 帧率
clock = pygame.time.Clock()
FPS = 60

# ============================================================
# 游戏变量
# ============================================================

# 球拍参数
PADDLE_WIDTH = 12
PADDLE_HEIGHT = 80
PADDLE_SPEED = 6  # 玩家球拍移动速度

# 球参数
BALL_SIZE = 12
ball_x = SCREEN_WIDTH // 2
ball_y = SCREEN_HEIGHT // 2
ball_dx = 4  # 球的水平速度
ball_dy = 3  # 球的垂直速度

# 玩家球拍（左侧）
player_x = 30  # 距离左边30像素
player_y = SCREEN_HEIGHT // 2 - PADDLE_HEIGHT // 2

# AI球拍（右侧）
AI_OFFSET = 30  # AI球拍距离右边30像素
ai_x = SCREEN_WIDTH - AI_OFFSET - PADDLE_WIDTH
ai_y = SCREEN_HEIGHT // 2 - PADDLE_HEIGHT // 2
AI_SPEED = 4  # AI移动速度（比球速慢，模拟反应时间）

# 计分
player_score = 0
ai_score = 0
WIN_SCORE = 11

# 游戏状态
paused = False
game_over = False
winner_text = ""


# ============================================================
# 辅助函数
# ============================================================

def reset_ball():
    """重新发球：球回到中心，随机方向飞出"""
    global ball_x, ball_y, ball_dx, ball_dy
    ball_x = SCREEN_WIDTH // 2
    ball_y = SCREEN_HEIGHT // 2
    # 随机水平方向（-1 向左，1 向右）
    ball_dx = random.choice([-4, 4])
    # 随机垂直方向，略微变化使发球有变化
    ball_dy = random.choice([-3, -2, 2, 3])


def reset_game():
    """重置整局游戏"""
    global player_score, ai_score, game_over, winner_text, paused
    global player_y, ai_y
    player_score = 0
    ai_score = 0
    game_over = False
    winner_text = ""
    paused = False
    player_y = SCREEN_HEIGHT // 2 - PADDLE_HEIGHT // 2
    ai_y = SCREEN_HEIGHT // 2 - PADDLE_HEIGHT // 2
    reset_ball()


# ============================================================
# 绘制函数
# ============================================================

def draw_center_line():
    """绘制半透明中线（实线）"""
    # 创建带透明度通道的Surface
    mid_line = pygame.Surface((4, SCREEN_HEIGHT), pygame.SRCALPHA)
    mid_line.fill(WHITE)
    mid_line.set_alpha(50)  # 设置透明度（0=完全透明，255=完全不透明）
    screen.blit(mid_line, (SCREEN_WIDTH // 2 - 2, 0))


def draw_dashed_net():
    """绘制虚线网（循环画短矩形）"""
    dash_length = 18  # 每段虚线的长度
    gap = 14          # 虚线之间的间隔
    line_width = 4    # 虚线宽度
    line_x = SCREEN_WIDTH // 2 - line_width // 2

    # 创建带透明度的表面
    for y in range(0, SCREEN_HEIGHT, dash_length + gap):
        # 绘制每段虚线
        dash_surface = pygame.Surface((line_width, dash_length), pygame.SRCALPHA)
        dash_surface.fill(WHITE)
        dash_surface.set_alpha(80)
        screen.blit(dash_surface, (line_x, y))


def draw_paddle(x, y, width, height, color):
    """绘制球拍"""
    pygame.draw.rect(screen, color, (x, y, width, height))
    # 给球拍加边框，更美观
    pygame.draw.rect(screen, WHITE, (x, y, width, height), 2)


def draw_ball():
    """绘制球"""
    # 球用一个小正方形表示
    ball_rect = pygame.Rect(ball_x - BALL_SIZE // 2, ball_y - BALL_SIZE // 2,
                            BALL_SIZE, BALL_SIZE)
    pygame.draw.rect(screen, WHITE, ball_rect)
    # 加发光效果：外层半透明
    glow = pygame.Surface((BALL_SIZE + 8, BALL_SIZE + 8), pygame.SRCALPHA)
    glow.fill((255, 255, 255, 30))
    screen.blit(glow, (ball_x - BALL_SIZE // 2 - 4, ball_y - BALL_SIZE // 2 - 4))


def draw_score():
    """绘制比分"""
    # 玩家分数（左侧）
    player_text = font_score.render(str(player_score), True, WHITE)
    player_rect = player_text.get_rect()
    player_rect.centerx = SCREEN_WIDTH // 2 - 80
    player_rect.top = 20
    screen.blit(player_text, player_rect)

    # AI分数（右侧）
    ai_text = font_score.render(str(ai_score), True, WHITE)
    ai_rect = ai_text.get_rect()
    ai_rect.centerx = SCREEN_WIDTH // 2 + 80
    ai_rect.top = 20
    screen.blit(ai_text, ai_rect)

    # 标签
    label_p = font_small.render("玩家", True, GRAY)
    lp_rect = label_p.get_rect(centerx=player_rect.centerx, top=player_rect.bottom + 2)
    screen.blit(label_p, lp_rect)

    label_a = font_small.render("AI", True, GRAY)
    la_rect = label_a.get_rect(centerx=ai_rect.centerx, top=ai_rect.bottom + 2)
    screen.blit(label_a, la_rect)


def draw_status():
    """绘制游戏状态提示（暂停/结束）"""
    if game_over:
        # 游戏结束：显示获胜信息
        # 半透明遮罩
        overlay = pygame.Surface((SCREEN_WIDTH, SCREEN_HEIGHT), pygame.SRCALPHA)
        overlay.fill((0, 0, 0, 160))
        screen.blit(overlay, (0, 0))

        # 胜利文字
        if player_score >= WIN_SCORE:
            win_text = font_info.render("玩家获胜！", True, GREEN)
        else:
            win_text = font_info.render("AI获胜！", True, RED)

        win_rect = win_text.get_rect(center=(SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2 - 30))
        screen.blit(win_text, win_rect)

        # 重新开始提示
        restart_text = font_small.render("按 R 键重新开始", True, WHITE)
        restart_rect = restart_text.get_rect(center=(SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2 + 20))
        screen.blit(restart_text, restart_rect)

    elif paused:
        # 暂停状态
        overlay = pygame.Surface((SCREEN_WIDTH, SCREEN_HEIGHT), pygame.SRCALPHA)
        overlay.fill((0, 0, 0, 120))
        screen.blit(overlay, (0, 0))

        pause_text = font_info.render("暂停中", True, YELLOW)
        pause_rect = pause_text.get_rect(center=(SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2 - 15))
        screen.blit(pause_text, pause_rect)

        hint_text = font_small.render("按 P 键继续", True, GRAY)
        hint_rect = hint_text.get_rect(center=(SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2 + 25))
        screen.blit(hint_text, hint_rect)


def draw_controls_hint():
    """绘制操作提示（底部）"""
    hint_text = font_small.render("W/S: 移动球拍  |  P: 暂停  |  ESC: 退出", True, DARK_GRAY)
    hint_rect = hint_text.get_rect(center=(SCREEN_WIDTH // 2, SCREEN_HEIGHT - 15))
    screen.blit(hint_text, hint_rect)


# ============================================================
# 更新函数
# ============================================================

def update_ball():
    """移动球并处理上下边界反弹"""
    global ball_x, ball_y, ball_dx, ball_dy

    ball_x += ball_dx
    ball_y += ball_dy

    # 上下边界反弹
    if ball_y - BALL_SIZE // 2 <= 0:
        ball_y = BALL_SIZE // 2
        ball_dy = -ball_dy
    elif ball_y + BALL_SIZE // 2 >= SCREEN_HEIGHT:
        ball_y = SCREEN_HEIGHT - BALL_SIZE // 2
        ball_dy = -ball_dy


def update_ai():
    """AI追踪逻辑：AI球拍中心向球的y坐标靠近"""
    global ai_y

    # 计算AI球拍中心点的y坐标
    ai_center_y = ai_y + PADDLE_HEIGHT // 2

    # 球在AI球拍下方 → AI向下移动
    if ai_center_y < ball_y:
        ai_y += AI_SPEED
    # 球在AI球拍上方 → AI向上移动
    elif ai_center_y > ball_y:
        ai_y -= AI_SPEED

    # 边界限制（AI球拍也不能跑出屏幕）
    if ai_y < 0:
        ai_y = 0
    elif ai_y + PADDLE_HEIGHT > SCREEN_HEIGHT:
        ai_y = SCREEN_HEIGHT - PADDLE_HEIGHT


def update_player():
    """更新玩家球拍位置（根据按键状态）"""
    global player_y

    keys = pygame.key.get_pressed()
    if keys[pygame.K_w]:
        player_y -= PADDLE_SPEED
    if keys[pygame.K_s]:
        player_y += PADDLE_SPEED

    # 边界限制
    if player_y < 0:
        player_y = 0
    elif player_y + PADDLE_HEIGHT > SCREEN_HEIGHT:
        player_y = SCREEN_HEIGHT - PADDLE_HEIGHT


def check_paddle_collision(paddle_x, paddle_y):
    """检查球是否与指定球拍碰撞，碰撞则反弹"""
    global ball_x, ball_y, ball_dx, ball_dy

    paddle_rect = pygame.Rect(paddle_x, paddle_y, PADDLE_WIDTH, PADDLE_HEIGHT)
    ball_rect = pygame.Rect(ball_x - BALL_SIZE // 2, ball_y - BALL_SIZE // 2,
                            BALL_SIZE, BALL_SIZE)

    if ball_rect.colliderect(paddle_rect):
        # 球碰到球拍：水平方向反弹
        ball_dx = -ball_dx
        # 根据碰撞位置微调垂直方向（增加变化）
        # 球碰到球拍上部分 → 向上弹；下部分 → 向下弹
        offset = (ball_y - (paddle_y + PADDLE_HEIGHT // 2)) / (PADDLE_HEIGHT // 2)
        ball_dy += int(offset * 2)  # 微调垂直角度
        # 限制垂直速度范围
        if ball_dy > 6:
            ball_dy = 6
        elif ball_dy < -6:
            ball_dy = -6
        return True
    return False


def check_score():
    """检测得分：球出左右边界"""
    global ball_x, player_score, ai_score, game_over, winner_text

    if ball_x - BALL_SIZE // 2 <= 0:
        # 球超出左边界 → AI得分
        ai_score += 1
        if ai_score >= WIN_SCORE:
            game_over = True
            winner_text = "AI获胜！"
        else:
            reset_ball()

    elif ball_x + BALL_SIZE // 2 >= SCREEN_WIDTH:
        # 球超出右边界 → 玩家得分
        player_score += 1
        if player_score >= WIN_SCORE:
            game_over = True
            winner_text = "玩家获胜！"
        else:
            reset_ball()


# ============================================================
# 主游戏循环
# ============================================================

def main():
    """游戏主函数"""
    global player_y, ai_y, paused, game_over, player_score, ai_score, winner_text

    running = True

    while running:
        # --------------------------------------------------------
        # 1. 事件处理
        # --------------------------------------------------------
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    # ESC键退出游戏
                    running = False

                elif event.key == pygame.K_p:
                    # P键切换暂停状态（游戏结束时不允许暂停）
                    if not game_over:
                        paused = not paused

                elif event.key == pygame.K_r:
                    # R键重新开始游戏
                    if game_over:
                        reset_game()

        # --------------------------------------------------------
        # 2. 更新游戏逻辑（非暂停 + 游戏未结束）
        # --------------------------------------------------------
        if not paused and not game_over:
            update_player()           # 更新玩家球拍
            update_ai()               # AI追踪球
            update_ball()             # 移动球
            check_paddle_collision(player_x, player_y)  # 球 vs 玩家球拍
            check_paddle_collision(ai_x, ai_y)          # 球 vs AI球拍
            check_score()             # 得分检测

        # --------------------------------------------------------
        # 3. 绘制画面
        # --------------------------------------------------------
        screen.fill(BLACK)            # 黑色背景

        draw_center_line()            # 半透明中线
        draw_dashed_net()             # 虚线网
        draw_paddle(player_x, player_y, PADDLE_WIDTH, PADDLE_HEIGHT, GREEN)  # 玩家球拍（绿色）
        draw_paddle(ai_x, ai_y, PADDLE_WIDTH, PADDLE_HEIGHT, RED)            # AI球拍（红色）
        draw_ball()                   # 球
        draw_score()                  # 比分
        draw_status()                 # 游戏状态（暂停/结束）
        draw_controls_hint()          # 底部操作提示

        pygame.display.flip()         # 刷新屏幕

        # --------------------------------------------------------
        # 4. 控制帧率
        # --------------------------------------------------------
        clock.tick(FPS)

    # 游戏退出
    pygame.quit()
    sys.exit()


# ============================================================
# 程序入口
# ============================================================
if __name__ == "__main__":
    main()
