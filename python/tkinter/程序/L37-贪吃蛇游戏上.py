import tkinter as tk

# ========================================
# 第 37 节：贪吃蛇游戏（上）—— 会移动的蛇
# 知识点：Canvas 绘制 + keyboard 键盘事件 + after() 定时器 + 列表存坐标
#
# 本节目标：做出一条能用方向键控制的、自动移动的蛇
# 下一节（第 38 节）将添加：食物、吃食物变长、分数系统
# ========================================

# ========================================
# 0. 游戏配置（可以修改这些数值来调整游戏手感）
# ========================================
CELL_SIZE = 20           # 每节蛇身的大小（像素），越大蛇越粗
CANVAS_WIDTH = 400       # 画布宽度
CANVAS_HEIGHT = 400      # 画布高度
INITIAL_SPEED = 150      # 移动速度（毫秒），越小蛇跑得越快

# ========================================
# 1. 创建主窗口
# ========================================
root = tk.Tk()
root.title("🐍 贪吃蛇游戏")
root.geometry("500x550")
root.configure(bg="#1a1a2e")           # 深色背景，有"游戏机"的感觉
root.resizable(False, False)           # 固定窗口大小，防止拖动改变大小

# ========================================
# 2. 标题标签
# ========================================
title_label = tk.Label(
    root,
    text="🐍 贪吃蛇游戏",
    font=("微软雅黑", 18, "bold"),
    bg="#1a1a2e", fg="#00ff88"          # 荧光绿色标题
)
title_label.pack(pady=(15, 5))

# ========================================
# 3. 创建画布（Canvas）—— 游戏的主舞台
# ========================================
# Canvas 是一个"画板"，我们可以在上面画矩形、圆形、线条等
# 蛇的每一节身体，就是在 Canvas 上画的一个个小矩形
canvas = tk.Canvas(
    root,
    width=CANVAS_WIDTH,                # 画布宽度
    height=CANVAS_HEIGHT,              # 画布高度
    bg="#16213e",                      # 深蓝色画布背景
    highlightthickness=0               # 去掉画布的外边框
)
canvas.pack(pady=10)

# ========================================
# 4. 蛇的数据结构
# ========================================
# 蛇身是一个列表，列表中的每个元素是一个 (x, y) 坐标元组
# 列表的第 0 项（索引 0）是蛇头
# 列表的最后一项是蛇尾
#
# 蛇的移动算法：
#   新蛇身 = [新蛇头位置] + 旧蛇身去掉尾巴
#   即：snake_body = [new_head] + snake_body[:-1]
#
# 初始蛇身：4 节，水平排列，向右移动
snake_body = [
    (200, 200),   # 蛇头（x=200, y=200）
    (180, 200),   # 第 2 节
    (160, 200),   # 第 3 节
    (140, 200),   # 蛇尾
]

# 当前移动方向（初始向右）
direction = "Right"

# 当前得分
score = 0


# ========================================
# 5. 绘制函数
# ========================================
def draw_snake():
    """
    在 Canvas 上绘制整条蛇
    策略：先清空画布上的旧蛇身（通过 tag="snake" 找到并删除），
         再根据 snake_body 列表逐节画出新的矩形
    """
    # 删除所有带有 "snake" 标签的图形（即上一次画的蛇身）
    canvas.delete("snake")

    # 遍历蛇身的每一节
    for i, segment in enumerate(snake_body):
        x, y = segment  # 解包坐标

        # 蛇头的颜色亮一点，身体深一点——好看又好区分
        if i == 0:
            color = "#00ff88"       # 蛇头：亮绿色
        else:
            color = "#00cc66"       # 身体：稍深一点的绿色

        # 在 Canvas 上画一个矩形（一节蛇身）
        canvas.create_rectangle(
            x, y,                           # 左上角坐标
            x + CELL_SIZE, y + CELL_SIZE,   # 右下角坐标
            fill=color,                     # 填充颜色
            outline="#00aa55",              # 边框颜色
            width=1,                        # 边框宽度
            tag="snake"                     # ★ 打上标签，方便统一删除
        )


# ========================================
# 6. 移动函数（核心算法！）
# ========================================
def move_snake():
    """
    让蛇向前移动一格

    核心算法分 4 步：
    ① 获取当前蛇头坐标
    ② 根据方向计算新蛇头坐标
    ③ 新蛇身 = [新蛇头] + 旧蛇身[:-1]（加新头，去旧尾）
    ④ 检查是否撞到自己，重绘画布
    """
    global snake_body, score

    # ---- 6a. 获取当前蛇头坐标 ----
    head_x, head_y = snake_body[0]

    # ---- 6b. 根据方向计算新蛇头坐标 ----
    if direction == "Right":
        head_x += CELL_SIZE       # 向右：x 坐标增加
    elif direction == "Left":
        head_x -= CELL_SIZE       # 向左：x 坐标减少
    elif direction == "Up":
        head_y -= CELL_SIZE       # 向上：y 坐标减少（Canvas 的 y 轴向下！）
    elif direction == "Down":
        head_y += CELL_SIZE       # 向下：y 坐标增加

    # ---- 6c. 穿墙处理（可选功能）----
    # 如果蛇头超出画布边界，让它从对面钻出来
    if head_x >= CANVAS_WIDTH:            # 撞到右墙
        head_x = 0                        # 从左墙出来
    elif head_x < 0:                      # 撞到左墙
        head_x = CANVAS_WIDTH - CELL_SIZE # 从右墙出来
    if head_y >= CANVAS_HEIGHT:           # 撞到下墙
        head_y = 0                        # 从上墙出来
    elif head_y < 0:                      # 撞到上墙
        head_y = CANVAS_HEIGHT - CELL_SIZE# 从下墙出来

    # ---- 6d. 构造新蛇身 ----
    # 新蛇头放在列表最前面，旧蛇身去掉最后一节（尾巴）
    new_head = (head_x, head_y)
    snake_body = [new_head] + snake_body[:-1]

    # ---- 6e. 检查是否撞到自己 ----
    # 如果新蛇头的位置和身体任何一节重合，游戏结束
    if new_head in snake_body[1:]:        # snake_body[1:] 是除了蛇头之外的所有身体
        game_over()
        return                            # 游戏结束后不再重绘和移动

    # ---- 6f. 重新绘制蛇 ----
    draw_snake()

    # ---- 6g. 更新得分和方向显示 ----
    score_label.config(text=f"得分：{score}　　方向：{direction}")


# ========================================
# 7. 键盘事件处理
# ========================================
def change_direction(event):
    """
    当用户按下方向键时，改变蛇的移动方向

    重要规则：蛇不能原地 180° 掉头！
    例如：蛇正在向右走，按左键应该被忽略（否则蛇头会撞到自己的脖子）
    判断方式：新方向和旧方向不能是"相反方向"
    """
    global direction
    key = event.keysym  # 获取按下的键名

    # 上键：只有当前不是"向下"时才允许改为"向上"
    if key == "Up" and direction != "Down":
        direction = "Up"
    # 下键：只有当前不是"向上"时才允许改为"向下"
    elif key == "Down" and direction != "Up":
        direction = "Down"
    # 左键：只有当前不是"向右"时才允许改为"向左"
    elif key == "Left" and direction != "Right":
        direction = "Left"
    # 右键：只有当前不是"向左"时才允许改为"向右"
    elif key == "Right" and direction != "Left":
        direction = "Right"


# ========================================
# 8. 游戏主循环（"心跳"）
# ========================================
def game_loop():
    """
    游戏的主循环 —— 像心跳一样持续跳动

    原理：
    ① 移动蛇 → move_snake()
    ② 设置定时器 → root.after(150, game_loop)
       意思是"150 毫秒后再调用 game_loop() 一次"
    ③ game_loop() 被再次调用时，又执行 ①②……
       这样就形成了一个永不停歇的循环！
    """
    move_snake()                              # 先移动一格
    root.after(INITIAL_SPEED, game_loop)       # 延迟后再调用自己


# ========================================
# 9. 游戏结束
# ========================================
def game_over():
    """蛇撞到自己，显示游戏结束画面"""
    canvas.create_text(
        CANVAS_WIDTH // 2,           # x 坐标：画布水平中心
        CANVAS_HEIGHT // 2,          # y 坐标：画布垂直中心
        text="游戏结束！\n按 R 键重新开始",
        font=("微软雅黑", 24, "bold"),
        fill="#ff4444",              # 红色文字
        justify="center",            # 文字居中对齐
        tag="gameover"               # 打标签，方便重新开始时清除
    )


# ========================================
# 10. 重新开始
# ========================================
def restart(event=None):
    """
    重新开始游戏
    按 R 键触发（大小写都支持）
    event=None 让这个函数也能被按钮调用
    """
    global snake_body, direction, score

    # 重置蛇身（回到初始位置和长度）
    snake_body = [(200, 200), (180, 200), (160, 200), (140, 200)]

    # 重置方向
    direction = "Right"

    # 重置得分
    score = 0

    # 清除画布上的 "游戏结束" 文字
    canvas.delete("gameover")

    # 重新绘制蛇
    draw_snake()

    # 更新信息显示
    score_label.config(text=f"得分：{score}　　方向：{direction}")


# ========================================
# 11. 绑定键盘事件到窗口
# ========================================
# bind("<Key>") 会监听所有键盘按键
# change_direction 函数中会过滤出需要的方向键
root.bind("<Key>", change_direction)

# 重新开始：大小写 R 都支持
root.bind("<r>", restart)
root.bind("<R>", restart)


# ========================================
# 12. 底部信息显示
# ========================================
# 得分和方向显示
score_label = tk.Label(
    root,
    text=f"得分：{score}　　方向：{direction}",
    font=("微软雅黑", 13),
    bg="#1a1a2e", fg="#cccccc"
)
score_label.pack(pady=5)

# 操作提示
tip_label = tk.Label(
    root,
    text="↑ ↓ ← → 控制方向　｜　R 键重新开始",
    font=("微软雅黑", 10),
    bg="#1a1a2e", fg="#666688"       # 暗灰色提示
)
tip_label.pack(pady=(0, 10))


# ========================================
# 13. 初始化和启动
# ========================================
# 先画一次蛇（启动时就能看到蛇）
draw_snake()

# 启动游戏主循环（蛇开始自动移动！）
game_loop()

# 启动 tkinter 主循环（必须放在代码最后！）
root.mainloop()
