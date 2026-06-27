import tkinter as tk
import random

# ========================================
# 第 38 节：贪吃蛇游戏（下）—— 完整版
# 上接第 37 节：蛇的移动 + 方向控制
# 新增：食物随机生成、吃食物变长、得分系统、碰撞检测、重新开始
# ========================================

root = tk.Tk()
root.title("贪吃蛇大作战 🐍")
root.geometry("600x670")
root.configure(bg="#2e7d32")
root.resizable(False, False)  # 禁止改变窗口大小

# ========== 得分显示区 ==========
score = 0
score_label = tk.Label(
    root,
    text="得分：0",
    font=("Arial", 16, "bold"),
    bg="#2e7d32",
    fg="white"
)
score_label.pack(pady=5)

# ========== 游戏主画布 ==========
# 600x600 的 Canvas，划分成 30x30 的网格（每格 20 像素）
canvas = tk.Canvas(
    root,
    width=600,
    height=600,
    bg="#1b5e20",       # 深绿色背景（草地感）
    highlightthickness=0  # 去掉边框
)
canvas.pack()

# ========== 蛇的数据结构 ==========
# snake 是一个列表，每个元素是 (x, y) 坐标元组
# snake[0] 是蛇头，snake[-1] 是蛇尾
snake = [(300, 300), (280, 300), (260, 300)]  # 初始 3 节，水平排列
direction = "Right"  # 当前移动方向


def draw_snake():
    """
    在画布上画出整条蛇。
    步骤：先清除旧蛇，再遍历 snake 列表逐节绘制。
    蛇头用深绿色，身体用浅绿色。
    """
    canvas.delete("snake")  # 清除所有带 "snake" 标签的图形

    for i, (x, y) in enumerate(snake):
        # 蛇头颜色更深，方便辨认
        color = "#4caf50" if i == 0 else "#81c784"
        canvas.create_rectangle(
            x, y, x + 20, y + 20,
            fill=color,
            outline="#1b5e20",
            tags="snake"  # 打上标签，方便批量删除
        )


# ========== 食物系统 ==========
food_x, food_y = 0, 0  # 当前食物坐标

# 在画布上创建一个红色方块作为食物
food = canvas.create_rectangle(
    0, 0, 20, 20,
    fill="#ff5252",       # 红色（苹果色）
    outline="#d32f2f",    # 深红边框
    tags="food"
)


def create_food():
    """
    在空白位置随机生成食物。
    坐标以 20 像素为步长，保证对齐蛇的网格。
    如果随机到的位置正好在蛇身上，就重新随机。
    """
    global food_x, food_y

    while True:
        # random.randint(0, 29) → 0~29 的随机整数
        # 乘以 20 → 变为 0, 20, 40, ..., 580
        food_x = random.randint(0, 29) * 20
        food_y = random.randint(0, 29) * 20

        # 确保食物不落在蛇身上
        if (food_x, food_y) not in snake:
            break

    # 移动食物到新位置
    canvas.coords(food, food_x, food_y, food_x + 20, food_y + 20)


# ========== 键盘方向控制 ==========
def change_direction(new_dir):
    """
    改变蛇的移动方向。
    防止「反向行驶」——比如正在向右时不能立刻向左，
    否则蛇会撞到自己身体的第二节。
    """
    global direction
    opposites = {
        "Up": "Down",
        "Down": "Up",
        "Left": "Right",
        "Right": "Left"
    }
    # 新方向和当前方向不是相反方向，才允许转向
    if new_dir != opposites.get(direction):
        direction = new_dir


# 绑定方向键（上下左右）
root.bind("<Up>", lambda e: change_direction("Up"))
root.bind("<Down>", lambda e: change_direction("Down"))
root.bind("<Left>", lambda e: change_direction("Left"))
root.bind("<Right>", lambda e: change_direction("Right"))


# ========== 碰撞检测 ==========
def check_collision(head_x, head_y):
    """
    检测蛇头是否发生碰撞。
    返回 True 表示游戏结束，False 表示安全。
    两种情况会触发碰撞：
      1. 撞墙 —— 蛇头坐标超出 600x600 画布范围
      2. 撞自己 —— 蛇头坐标和身体（snake[1:]）的某节重合
    """
    # 情况 1：撞墙
    if head_x < 0 or head_x >= 600 or head_y < 0 or head_y >= 600:
        return True

    # 情况 2：撞到自己身体
    if (head_x, head_y) in snake[1:]:
        return True

    return False


# ========== 吃食物逻辑 ==========
def eat_food():
    """
    判断蛇头是否吃到食物。
    如果吃到：加分、重新生成食物，返回 True（蛇不缩短 → 变长）
    如果没吃到：返回 False（蛇正常移动 → 长度不变）
    """
    global score
    head_x, head_y = snake[0]  # 蛇头坐标

    if head_x == food_x and head_y == food_y:
        # 加分！
        score += 10
        score_label.config(text=f"得分：{score}")
        # 重新生成食物
        create_food()
        return True

    return False


# ========== 蛇的移动（核心循环） ==========
running = True  # 游戏是否正在运行


def move():
    """
    蛇的每一步移动。
    原理：
      1. 根据方向计算新蛇头坐标
      2. 碰撞检测：撞了就结束
      3. 把新蛇头插入列表头部（前进）
      4. 如果吃到食物 → 不删尾巴（变长）
         如果没吃到 → 删掉尾巴（长度不变）
      5. 重绘蛇
      6. 150ms 后再次调用自己（递归循环）
    """
    global running

    if not running:
        return

    # 计算新蛇头坐标
    head_x, head_y = snake[0]

    if direction == "Right":
        new_head = (head_x + 20, head_y)
    elif direction == "Left":
        new_head = (head_x - 20, head_y)
    elif direction == "Down":
        new_head = (head_x, head_y + 20)
    elif direction == "Up":
        new_head = (head_x, head_y - 20)
    else:
        return  # 未知方向，不动

    # 碰撞检测 —— 撞了就 Game Over
    if check_collision(new_head[0], new_head[1]):
        game_over()
        return

    # 蛇头前进：把新头部插入列表最前面
    snake.insert(0, new_head)

    # 吃食物判断
    if not eat_food():
        # 没吃到食物 → 删除尾部，保持长度不变
        snake.pop()
    # 吃到了 → 不 pop()，尾部保留 → 身体自然变长一节！

    # 重绘蛇
    draw_snake()

    # 150 毫秒后再次移动（控制游戏速度）
    root.after(150, move)


# ========== 游戏结束处理 ==========
def game_over():
    """
    游戏结束：
      - 停止移动循环
      - 在画布上显示"游戏结束"文字和最终得分
      - 显示重新开始按钮
    """
    global running
    running = False

    # 游戏结束提示文字
    canvas.create_text(
        300, 270,
        text="游戏结束！",
        font=("Arial", 40, "bold"),
        fill="#ff5252",
        tags="gameover"
    )
    canvas.create_text(
        300, 320,
        text=f"最终得分：{score}",
        font=("Arial", 20),
        fill="white",
        tags="gameover"
    )

    # 重新开始按钮
    restart_btn = tk.Button(
        root,
        text="↻ 重新开始",
        font=("Arial", 15, "bold"),
        bg="#4caf50",
        fg="white",
        activebackground="#66bb6a",
        command=restart_game
    )
    restart_btn.place(x=240, y=350)


def restart_game():
    """
    重置游戏到初始状态：
      - 清除画布上的蛇和 Game Over 文字
      - 重置蛇的位置、方向、得分
      - 移除重新开始按钮
      - 重新画蛇、生成食物、开始移动
    """
    global snake, direction, score, running

    # 清除画布上的旧内容
    canvas.delete("snake")
    canvas.delete("gameover")

    # 重置游戏数据
    snake = [(300, 300), (280, 300), (260, 300)]
    direction = "Right"
    score = 0
    running = True

    # 更新得分显示
    score_label.config(text="得分：0")

    # 移除所有 place 布局的按钮（即重新开始按钮）
    for widget in root.place_slaves():
        widget.destroy()

    # 重新开始
    draw_snake()
    create_food()
    move()


# ========== 启动游戏 ==========
draw_snake()   # 画初始蛇
create_food()  # 生成第一个食物
move()         # 开始移动循环

root.mainloop()
