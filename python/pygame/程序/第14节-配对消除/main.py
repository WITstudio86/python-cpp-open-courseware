"""
第14节：配对消除 —— 记忆翻牌游戏完成
功能：翻两张牌判断是否匹配，匹配成功消除，不匹配延迟翻回，步数统计，全部消除胜利
知识点：游戏状态机、pygame.time.delay()、配对逻辑、胜利判定
"""

import pygame
import random
import sys
import math

# ═══════════════════════════════════════
# 初始化Pygame
# ═══════════════════════════════════════
pygame.init()

# 窗口设置
SCREEN_W = 800
SCREEN_H = 600
screen = pygame.display.set_mode((SCREEN_W, SCREEN_H))
pygame.display.set_caption("第14节：配对消除 —— 记忆翻牌游戏")

# 时钟
clock = pygame.time.Clock()

# ═══════════════════════════════════════
# 卡牌尺寸和网格计算
# ═══════════════════════════════════════
ROWS = 4
COLS = 4
CARD_W = 120
CARD_H = 120
GAP = 20

GRID_W = COLS * CARD_W + (COLS - 1) * GAP
GRID_H = ROWS * CARD_H + (ROWS - 1) * GAP

OFFSET_X = (SCREEN_W - GRID_W) // 2
OFFSET_Y = (SCREEN_H - GRID_H) // 2

# ═══════════════════════════════════════
# 8种卡牌颜色（8对）
# ═══════════════════════════════════════
COLORS = [
    (255, 50, 50),     # 红色
    (50, 130, 255),    # 蓝色
    (50, 200, 50),     # 绿色
    (255, 200, 0),     # 黄色
    (200, 50, 255),    # 紫色
    (255, 130, 0),     # 橙色
    (0, 200, 200),     # 青色
    (255, 100, 180)    # 粉色
]

# ═══════════════════════════════════════
# 游戏状态常量（状态机的4个状态）
# ═══════════════════════════════════════
STATE_WAIT_FIRST = "wait_first"    # 等待翻第一张牌
STATE_WAIT_SECOND = "wait_second"  # 等待翻第二张牌
STATE_CHECKING = "checking"         # 正在检查两张牌是否匹配
STATE_GAME_OVER = "game_over"      # 游戏结束（胜利！）


def create_board():
    """创建4x4棋盘，随机放置8对颜色"""
    # 生成8对颜色编号
    pairs = []
    for i in range(8):
        pairs.append(i)
        pairs.append(i)

    random.shuffle(pairs)

    # 填入二维列表
    board = []
    for row in range(ROWS):
        current_row = []
        for col in range(COLS):
            index = row * COLS + col
            color_index = pairs[index]
            card = {
                "color": COLORS[color_index],
                "shape_index": color_index,
                "state": "hidden"       # hidden / revealed / matched
            }
            current_row.append(card)
        board.append(current_row)

    return board


def get_card_at_pos(mouse_x, mouse_y):
    """鼠标坐标换算为卡牌行列位置"""
    if mouse_x < OFFSET_X or mouse_y < OFFSET_Y:
        return None

    col = (mouse_x - OFFSET_X) // (CARD_W + GAP)
    row = (mouse_y - OFFSET_Y) // (CARD_H + GAP)

    if not (0 <= row < ROWS and 0 <= col < COLS):
        return None

    # 精确判断是否点在牌面上（而非间隙）
    card_x = OFFSET_X + col * (CARD_W + GAP)
    card_y = OFFSET_Y + row * (CARD_H + GAP)
    if card_x <= mouse_x <= card_x + CARD_W and card_y <= mouse_y <= card_y + CARD_H:
        return (row, col)

    return None


def draw_card_shape(screen, x, y, w, h, shape_index, color):
    """在卡牌中央绘制形状图标"""
    cx = x + w // 2
    cy = y + h // 2
    r = 25

    if shape_index == 0:       # 红色 —— 菱形
        points = [(cx, cy - r), (cx + r, cy), (cx, cy + r), (cx - r, cy)]
        pygame.draw.polygon(screen, (255, 255, 255), points)
    elif shape_index == 1:     # 蓝色 —— 圆形
        pygame.draw.circle(screen, (255, 255, 255), (cx, cy), r)
    elif shape_index == 2:     # 绿色 —— 三角形
        points = [(cx, cy - r), (cx + r, cy + r), (cx - r, cy + r)]
        pygame.draw.polygon(screen, (255, 255, 255), points)
    elif shape_index == 3:     # 黄色 —— 五角星
        points = []
        for i in range(10):
            angle = math.pi / 2 + i * math.pi / 5
            radius = r if i % 2 == 0 else r * 0.4
            px = cx + radius * math.cos(angle)
            py = cy - radius * math.sin(angle)
            points.append((px, py))
        pygame.draw.polygon(screen, (255, 255, 255), points)
    elif shape_index == 4:     # 紫色 —— 正方形
        pygame.draw.rect(screen, (255, 255, 255), (cx - r, cy - r, 2 * r, 2 * r))
    elif shape_index == 5:     # 橙色 —— 六边形
        points = []
        for i in range(6):
            angle = math.pi / 2 + i * math.pi / 3
            px = cx + r * math.cos(angle)
            py = cy - r * math.sin(angle)
            points.append((px, py))
        pygame.draw.polygon(screen, (255, 255, 255), points)
    elif shape_index == 6:     # 青色 —— 四角星
        points = []
        for i in range(8):
            angle = math.pi / 2 + i * math.pi / 4
            radius = r if i % 2 == 0 else r * 0.3
            px = cx + radius * math.cos(angle)
            py = cy - radius * math.sin(angle)
            points.append((px, py))
        pygame.draw.polygon(screen, (255, 255, 255), points)
    elif shape_index == 7:     # 粉色 —— 爱心
        pygame.draw.circle(screen, (255, 255, 255), (cx - r // 2, cy - r // 3), r // 2)
        pygame.draw.circle(screen, (255, 255, 255), (cx + r // 2, cy - r // 3), r // 2)
        points = [(cx - r, cy - r // 3), (cx + r, cy - r // 3), (cx, cy + r)]
        pygame.draw.polygon(screen, (255, 255, 255), points)


def draw_board(screen, board):
    """绘制16张卡牌"""
    screen.fill((25, 25, 45))

    for row in range(ROWS):
        for col in range(COLS):
            x = OFFSET_X + col * (CARD_W + GAP)
            y = OFFSET_Y + row * (CARD_H + GAP) + 15

            card = board[row][col]

            if card["state"] == "hidden":
                # 灰色牌背
                pygame.draw.rect(screen, (60, 60, 100), (x, y, CARD_W, CARD_H), border_radius=10)
                pygame.draw.rect(screen, (130, 130, 200), (x, y, CARD_W, CARD_H), 3, border_radius=10)
                # "?"号
                q_font = pygame.font.Font(None, 60)
                q_text = q_font.render("?", True, (180, 180, 220))
                q_rect = q_text.get_rect(center=(x + CARD_W // 2, y + CARD_H // 2))
                screen.blit(q_text, q_rect)

            elif card["state"] == "revealed":
                # 彩色牌面
                pygame.draw.rect(screen, card["color"], (x, y, CARD_W, CARD_H), border_radius=10)
                pygame.draw.rect(screen, (255, 255, 255), (x, y, CARD_W, CARD_H), 3, border_radius=10)
                draw_card_shape(screen, x, y, CARD_W, CARD_H, card["shape_index"], card["color"])

            elif card["state"] == "matched":
                # 已匹配：颜色变暗（表示已消除）
                gray_color = tuple(c // 3 for c in card["color"])
                pygame.draw.rect(screen, gray_color, (x, y, CARD_W, CARD_H), border_radius=10)
                pygame.draw.rect(screen, (80, 80, 80), (x, y, CARD_W, CARD_H), 2, border_radius=10)
                # 画一个淡淡的形状（表示这里曾是张牌）
                draw_card_shape(screen, x, y, CARD_W, CARD_H, card["shape_index"], gray_color)


def draw_ui(screen, steps, pairs_found, game_state, best_steps):
    """绘制游戏信息：标题、步数、配对进度、胜利画面"""
    font = pygame.font.Font(None, 36)
    big_font = pygame.font.Font(None, 56)
    small_font = pygame.font.Font(None, 28)

    # ── 标题 ──
    title = font.render("第14节：配对消除 —— 记忆翻牌游戏", True, (200, 200, 220))
    screen.blit(title, (SCREEN_W // 2 - title.get_width() // 2, 10))

    # ── 左上：步数 ──
    step_text = font.render(f"步数: {steps}", True, (255, 255, 255))
    screen.blit(step_text, (15, SCREEN_H - 45))

    # ── 右上：配对进度 ──
    progress_text = font.render(f"配对: {pairs_found} / 8", True, (100, 255, 100))
    screen.blit(progress_text, (SCREEN_W - progress_text.get_width() - 15, SCREEN_H - 45))

    # ── 操作提示 ──
    if game_state != STATE_GAME_OVER:
        hint = small_font.render("按 R 键重新开始 | 点击卡牌翻牌", True, (150, 150, 170))
        screen.blit(hint, (SCREEN_W // 2 - hint.get_width() // 2, SCREEN_H - 25))

    # ── 胜利画面 ──
    if game_state == STATE_GAME_OVER:
        # 半透明遮罩
        overlay = pygame.Surface((SCREEN_W, SCREEN_H))
        overlay.set_alpha(190)
        overlay.fill((0, 0, 0))
        screen.blit(overlay, (0, 0))

        # 胜利标题
        win_text = big_font.render("恭喜你赢了！", True, (255, 215, 0))
        win_rect = win_text.get_rect(center=(SCREEN_W // 2, SCREEN_H // 2 - 60))
        screen.blit(win_text, win_rect)

        # 步数成绩
        result_text = font.render(f"你用了 {steps} 步完成游戏！", True, (255, 255, 255))
        result_rect = result_text.get_rect(center=(SCREEN_W // 2, SCREEN_H // 2))
        screen.blit(result_text, result_rect)

        # 最佳成绩
        if best_steps is not None:
            best_text = font.render(f"最佳成绩: {best_steps} 步", True, (255, 200, 100))
            best_rect = best_text.get_rect(center=(SCREEN_W // 2, SCREEN_H // 2 + 40))
            screen.blit(best_text, best_rect)
            if steps <= best_steps:
                new_record = font.render("★ 新纪录！ ★", True, (255, 50, 50))
                new_rect = new_record.get_rect(center=(SCREEN_W // 2, SCREEN_H // 2 + 80))
                screen.blit(new_record, new_rect)

        # 评分（星级评价）
        if steps <= 8:
            stars = "⭐⭐⭐ 完美！"
        elif steps <= 12:
            stars = "⭐⭐ 不错！"
        elif steps <= 16:
            stars = "⭐ 加油！"
        else:
            stars = "继续努力！"
        star_text = font.render(stars, True, (255, 255, 100))
        star_rect = star_text.get_rect(center=(SCREEN_W // 2, SCREEN_H // 2 + 120))
        screen.blit(star_text, star_rect)

        # 重新开始提示
        restart = font.render("按 R 键重新开始", True, (180, 180, 200))
        restart_rect = restart.get_rect(center=(SCREEN_W // 2, SCREEN_H // 2 + 160))
        screen.blit(restart, restart_rect)


def reset_game():
    """重置所有游戏变量，返回初始状态"""
    board = create_board()
    return {
        "board": board,
        "game_state": STATE_WAIT_FIRST,
        "first_card": None,
        "second_card": None,
        "steps": 0,
        "pairs_found": 0
    }


# ═══════════════════════════════════════
# 主程序
# ═══════════════════════════════════════
def main():
    # 初始化游戏
    game = reset_game()
    board = game["board"]
    game_state = game["game_state"]
    first_card = game["first_card"]
    second_card = game["second_card"]
    steps = game["steps"]
    pairs_found = game["pairs_found"]
    best_steps = None  # 历史最佳成绩

    running = True

    print("=" * 50)
    print("第14节：配对消除 —— 记忆翻牌游戏")
    print("翻两张牌，颜色相同就消除，不同就翻回去！")
    print("=" * 50)

    while running:
        # ═══════════════════════════════════════
        # 1. 事件处理
        # ═══════════════════════════════════════
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

            elif event.type == pygame.MOUSEBUTTONDOWN:
                # 在"检查中"或"游戏结束"状态下，不响应点击
                if game_state in [STATE_CHECKING, STATE_GAME_OVER]:
                    continue

                mouse_x, mouse_y = event.pos
                result = get_card_at_pos(mouse_x, mouse_y)

                if result is None:
                    continue  # 点到了空白处

                row, col = result
                card = board[row][col]

                # 只有隐藏状态的牌才能点
                if card["state"] != "hidden":
                    continue

                # ── 状态1：等待翻第一张牌 ──
                if game_state == STATE_WAIT_FIRST:
                    card["state"] = "revealed"
                    first_card = (row, col)
                    game_state = STATE_WAIT_SECOND
                    print(f"翻开第一张牌：({row}, {col})")

                # ── 状态2：等待翻第二张牌 ──
                elif game_state == STATE_WAIT_SECOND:
                    # 不能点同一张牌
                    if (row, col) == first_card:
                        continue

                    card["state"] = "revealed"
                    second_card = (row, col)
                    steps += 1
                    game_state = STATE_CHECKING
                    print(f"翻开第二张牌：({row}, {col})，当前步数：{steps}")

            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_r:
                    # 按R键重新开始
                    game = reset_game()
                    board = game["board"]
                    game_state = game["game_state"]
                    first_card = game["first_card"]
                    second_card = game["second_card"]
                    steps = game["steps"]
                    pairs_found = game["pairs_found"]
                    print("游戏重新开始！")

        # ═══════════════════════════════════════
        # 2. 游戏逻辑（状态机检查）
        # ═══════════════════════════════════════
        if game_state == STATE_CHECKING:
            r1, c1 = first_card
            r2, c2 = second_card
            card1 = board[r1][c1]
            card2 = board[r2][c2]

            # ── 判断是否匹配：比较颜色 ──
            if card1["color"] == card2["color"]:
                # ✅ 匹配成功！两张牌变为 matched 状态
                card1["state"] = "matched"
                card2["state"] = "matched"
                pairs_found += 1
                print(f"配对成功！已完成 {pairs_found} / 8 对")

                # 检查是否全部消除
                if pairs_found == 8:
                    game_state = STATE_GAME_OVER
                    # 更新最佳成绩
                    if best_steps is None or steps < best_steps:
                        best_steps = steps
                    print(f"恭喜！全部配对完成！用了 {steps} 步！")
                else:
                    game_state = STATE_WAIT_FIRST

            else:
                # ❌ 不匹配！先刷新显示让玩家看清，再延迟翻回
                # 关键：必须先 flip 再 delay！
                draw_board(screen, board)
                draw_ui(screen, steps, pairs_found, game_state, best_steps)
                pygame.display.flip()          # 刷新屏幕（让玩家看到两张牌）
                pygame.time.delay(500)         # 等待500毫秒 = 0.5秒

                card1["state"] = "hidden"      # 翻回第一张
                card2["state"] = "hidden"      # 翻回第二张
                print("不匹配，牌已翻回！")

                game_state = STATE_WAIT_FIRST  # 回到初始状态

            # 清空选中的牌记录
            first_card = None
            second_card = None

        # ═══════════════════════════════════════
        # 3. 绘制画面
        # ═══════════════════════════════════════
        draw_board(screen, board)
        draw_ui(screen, steps, pairs_found, game_state, best_steps)
        pygame.display.flip()

        clock.tick(60)

    pygame.quit()
    sys.exit()


if __name__ == "__main__":
    main()
