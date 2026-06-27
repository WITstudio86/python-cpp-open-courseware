# 第46节：项目八 —— Turtle 烟花动画

## 🎯 教学目标
- 学生能够理解动画的基本原理：快速地在每一帧"画 → 清除 → 再画"
- 学生能够使用 `turtle.clear()` 清空画布实现帧刷新
- 学生能够使用循环和随机颜色模拟烟花粒子扩散的效果
- 学生能够独立完成一个烟花绽放动画程序

## 📝 重点概念
- **动画原理**：像翻页动画书一样，一幅画面快速切换到下一幅，眼睛就会产生"动"的错觉
- **turtle.clear()**：擦除海龟画过的所有痕迹，就像用黑板擦擦黑板
- **turtle.tracer()**：控制动画刷新速度，关闭后可以"一口气画完再显示"，避免闪烁
- **粒子系统**：把一朵烟花拆成很多个"小光点"（粒子），每个粒子独立移动，合起来就是一朵烟花
- **随机颜色**：每次烟花都用不同的颜色，让夜空五彩斑斓

## 📖 讲解内容

### 步骤1：引入（5分钟）

**教师开场：**

"同学们，过年的时候你们看过烟花吗？还记得烟花是怎么绽放的吗？"

（等待学生回应，引导描述：一个亮点飞上天空，然后'砰'地炸开，向四面八方散开）

"太棒了！烟花从中间炸开，向四面八方散出很多小光点，每个光点都拖着一条亮亮的尾巴。今天我们要当一回'数字烟花设计师'，用 Python 的 Turtle 海龟在屏幕上放烟花！"

"而且，我们不需要等到过年——只要运行我们的程序，随时都能看到美丽的烟花秀！"

**教师展示最终效果（提前运行准备）：**
"大家看，这就是我们今天要做出来的效果！一朵朵彩色的烟花在夜空中绽放，每朵颜色都不一样。"

**小互动：** 请学生用身体动作模拟烟花绽放——蹲下，然后跳起来，手臂向四面八方展开。体会"从中心向四周散开"的感觉。

### 步骤2：核心讲解（15-20分钟）

#### 2.1 动画是怎么"动"起来的？

"大家玩过翻页动画书吗？就是那种快速翻动书页，上面的小人就会动起来的书。计算机动画的原理和这个一模一样！"

**生活中的比喻：**
- 翻页动画书的每一页 = 程序中的一"帧"
- 快速地翻页 = 程序高速循环
- 小人动了 = 画面发生了变化

"在 Turtle 世界中，动画的流程非常简单："

```
循环执行：
    ① 画当前帧的内容（烟花的各个粒子）
    ② turtle.clear() —— 擦掉！准备画下一帧
    ③ 计算每个粒子下一帧的位置（向外移动一点点）
    ④ 再画新位置的内容
```

"因为我们一秒钟循环很多次（比如 30 次），你的眼睛就会被'骗'，觉得烟花真的在动！"

#### 2.2 turtle.tracer() —— 动画的"开关"

"如果不做特殊设置，Turtle 画一笔你就能看到一笔，速度很慢，而且会一闪一闪的。我们可以用一个神奇的设置来解决这个问题："

```python
turtle.tracer(0)  # 关闭自动刷新：告诉海龟'先别急着显示，等我说可以了再显示'
# ... 画很多东西 ...
turtle.update()   # 手动刷新：'好了，现在一次性显示出来！'
```

**生活中的比喻：** 如果把画画过程实时直播，观众会看到乱七八糟的线条。但如果先把画藏起来，画好了再揭开布——哇！一幅完整的画！`tracer(0)` 就是把"布"盖上，`update()` 就是揭开布。

#### 2.3 烟花的"物理"原理

"一朵烟花的绽放可以拆解成以下步骤："

1. **准备阶段**：在屏幕下方随机选择一个位置作为"发射点"
2. **上升阶段**：一个小光点从发射点快速上升（可选做）
3. **爆炸阶段**：在爆炸点创建几十个"粒子"
4. **扩散阶段**：每个粒子以不同的速度和方向向外飞
5. **消失阶段**：粒子越来越暗（变小或变淡），最后消失

"今天我们重点做爆炸和扩散这两个最精彩的部分！"

#### 2.4 粒子是什么？

"一个'粒子'就是一个独立的小光点。它需要记住："
- 自己的位置（x, y 坐标）
- 自己飞行的方向（用角度表示）
- 自己飞行的速度
- 自己的颜色

"我们可以用一个列表来表示一个粒子：`[x, y, 角度, 速度, 颜色]`，这样很方便。"

"几十个这样的粒子同时向不同方向飞出去——加在一起就是一朵烟花了！"

#### 2.5 程序设计的思路

"来看看我们的施工蓝图："

1. 设置夜空背景（黑色画布）
2. 准备多个烟花的"爆炸点"位置
3. 对每个烟花：
   a. 随机选一个颜色
   b. 创建 30-50 个粒子，让它们以爆炸点为中心向四面八方飞
   c. 用循环让粒子一步步向外扩散（每步画一次 → 清除 → 移动 → 再画）
   d. 扩散约 30 步后，这朵烟花结束
4. 开始下一朵烟花（回到步骤 3）

"这样，一朵接一朵的烟花就在我们的屏幕上绽放了！"

### 步骤3：动手演示（10分钟）

**教师边敲代码边讲解：**

```python
import turtle
import random
import math

# ========== 第1步：设置舞台 ==========
screen = turtle.Screen()
screen.bgcolor("black")          # 夜空背景
screen.title("🎆 烟花动画秀 🎆")
screen.setup(800, 600)           # 窗口大小

turtle.tracer(0)  # 关闭自动刷新，手动控制动画

# ========== 第2步：创建画烟花的"画笔" ==========
pen = turtle.Turtle()
pen.speed(0)       # 最快速度
pen.hideturtle()   # 隐藏海龟图标
pen.penup()        # 提起笔，移动时不画线

# ========== 第3步：定义"炸一朵烟花"的函数 ==========
def explode_firework(x, y):
    """
    在坐标(x, y)处炸一朵烟花
    x, y: 爆炸中心坐标
    """
    # 随机选一个鲜艳的颜色
    colors = ["red", "orange", "yellow", "lime", "cyan", 
              "magenta", "pink", "gold", "violet", "white"]
    firework_color = random.choice(colors)
    
    # 创建粒子：每个粒子记录 [当前x, 当前y, 角度, 速度, 颜色]
    num_particles = random.randint(30, 50)
    particles = []
    
    for i in range(num_particles):
        # 每个粒子以爆炸点为中心
        start_x = x
        start_y = y
        # 随机角度（0到360度），均匀覆盖各个方向
        angle = random.uniform(0, 2 * math.pi)
        # 随机速度（让有的粒子飞得远，有的飞得近）
        speed = random.uniform(2, 8)
        # 存入粒子列表
        particles.append([start_x, start_y, angle, speed, firework_color])
    
    # 动画循环：让粒子一步步扩散
    for step in range(40):  # 总共扩散40步
        pen.clear()  # 擦掉上一帧的画面
        
        for particle in particles:
            # 分解出粒子的各个属性
            px, py, angle, speed, color = particle
            
            # 计算新位置：利用三角函数算水平分量和垂直分量
            dx = math.cos(angle) * speed
            dy = math.sin(angle) * speed
            
            new_x = px + dx
            new_y = py + dy
            
            # 更新粒子的位置
            particle[0] = new_x
            particle[1] = new_y
            
            # 加上一点点"重力"效果（让粒子微微向下掉）
            particle[2] = angle  # 保持角度不变
            # 速度慢慢减小（模拟空气阻力）
            particle[3] = speed * 0.95
            
            # 画这个小粒子
            pen.goto(new_x, new_y)
            # 粒子越来越小（模拟消失）
            size = max(1, 5 - step * 0.1)
            pen.dot(size, color)
        
        # 这一帧画完了，更新屏幕
        turtle.update()

# ========== 第4步：循环放烟花 ==========
print("🎆 烟花秀开始了！在窗口中观看...")
print("   关闭窗口即可退出。")

for _ in range(8):  # 放8朵烟花
    # 随机选择爆炸位置
    explosion_x = random.randint(-300, 300)
    explosion_y = random.randint(-100, 250)
    
    explode_firework(explosion_x, explosion_y)

# 画完后停留
pen.goto(0, -280)
pen.color("white")
pen.write("🎆 烟花秀结束！", align="center", font=("Arial", 24, "bold"))
turtle.update()

# 点击关闭窗口
screen.exitonclick()
```

**教师演示要点：**
- 第一次运行展示完整效果
- 第二次逐段解释代码，每段运行看看效果
- 重点解释 `math.cos(angle)` 和 `math.sin(angle)` 是如何让粒子向四面八方飞的

### 步骤4：独立练习（15分钟）

**基础任务（所有学生完成）：**
1. 把代码敲一遍并运行，看到烟花动画
2. 修改烟花数量（8朵改成更多或更少）
3. 修改粒子数量（30-50 改成其他范围），观察效果变化

**挑战任务（学有余力的学生）：**

**挑战一：让烟花上升**
在"爆炸"之前，添加一个"光点上升"的动画——一个小光点从底部缓缓上升到爆炸位置，然后再炸开。

提示：
```python
# 上升光点动画
rise_pen = turtle.Turtle()
rise_pen.speed(0)
rise_pen.hideturtle()
rise_pen.penup()

# 从底部到爆炸位置，一步一步向上移
start_x = explosion_x
for step in range(20):
    rise_pen.clear()
    rise_y = -280 + step * (explosion_y + 280) / 20
    rise_pen.goto(start_x, rise_y)
    rise_pen.dot(6, "yellow")
    turtle.update()
```

**挑战二：彩色渐变烟花**
让一朵烟花中有多种颜色，而不是单一颜色。比如外层粒子是红色，内层是黄色。

**挑战三：添加音效（可选，需要额外库）**
使用 `winsound` 或 `playsound` 库在烟花爆炸时播放音效。

### 步骤5：分享与总结（5-10分钟）

1. 请同学展示自己的烟花动画，看看谁的设计最有创意
2. 讨论：为什么粒子要越来越慢？如果不减速会怎样？
3. 讨论：除了烟花，这种"粒子系统"还能做什么？（下雨、下雪、泡泡、星空……）

## 💻 代码示例

```python
import turtle
import random
import math

# ==================== 初始化设置 ====================
WIDTH, HEIGHT = 800, 600  # 窗口宽高

screen = turtle.Screen()
screen.setup(WIDTH, HEIGHT)
screen.bgcolor("midnightblue")  # 深蓝夜空
screen.title("🎆 Python 烟花秀 🎆")
screen.tracer(0)  # 关闭自动刷新，手动控制动画帧

# ==================== 创建画笔 ====================
artist = turtle.Turtle()
artist.speed(0)      # 最快绘制速度
artist.hideturtle()  # 隐藏海龟，只看画的内容
artist.penup()       # 抬笔，移动不留痕迹

# ==================== 烟花爆炸函数 ====================
def boom(x, y, color_name=None):
    """
    在(x, y)位置炸开一朵烟花
    
    参数:
        x, y: 爆炸中心坐标
        color_name: 烟花颜色（不指定则随机选择）
    """
    # 如果没指定颜色，从鲜艳的颜色中随机选一个
    bright_colors = [
        "#FF0000", "#FF4500", "#FF8C00", "#FFD700", "#FFFF00",
        "#ADFF2F", "#00FF00", "#00FA9A", "#00FFFF", "#1E90FF",
        "#8A2BE2", "#FF00FF", "#FF1493", "#FF69B4", "#FFB6C1"
    ]
    if color_name is None:
        color_name = random.choice(bright_colors)
    
    # 创建一堆粒子
    # 每个粒子格式：[x坐标, y坐标, 飞行角度(弧度), 速度, 颜色, 生命值]
    num = random.randint(35, 55)  # 这朵烟花有多少粒子
    particles = []
    
    for _ in range(num):
        angle = random.uniform(0, 2 * math.pi)       # 随机发射方向
        speed = random.uniform(3.0, 10.0)            # 随机速度
        life = random.randint(25, 45)                # 随机生命值（能飞多少步）
        particles.append([x, y, angle, speed, color_name, life])
    
    # 动画主循环：一步步更新粒子位置
    max_steps = max(p[5] for p in particles)  # 取最长的生命值
    for step in range(max_steps):
        artist.clear()  # ★清屏——这是动画的关键！
        
        # 更新并画出还活着的粒子
        for p in particles:
            px, py, angle, speed, color, life = p
            
            if step < life:  # 粒子还存活
                # 根据角度计算位移
                dx = math.cos(angle) * speed
                dy = math.sin(angle) * speed
                
                # 更新位置
                p[0] = px + dx
                p[1] = py + dy - 0.1 * step  # 轻微的重力效果（向下掉）
                
                # 速度慢慢变慢（空气阻力）
                p[3] = speed * 0.96
                
                # 粒子越来越小（模拟熄灭）
                size = max(1, 6 - step * 0.12)
                
                # 画粒子
                artist.goto(p[0], p[1])
                artist.dot(int(size), color)
        
        screen.update()  # 显示这一帧


# ==================== 主程序 ====================
print("🎆 烟花秀即将开始！请观看 Turtle 窗口...")
print("💡 提示：关闭窗口即可退出程序")

# 循环放多朵烟花
for i in range(10):
    # 每朵烟花随机位置
    firework_x = random.randint(-350, 350)
    firework_y = random.randint(-200, 200)
    
    boom(firework_x, firework_y)

# 结束画面
artist.goto(0, -270)
artist.color("white")
artist.write("🎆 烟花秀结束！谢谢你观看 🎆", 
             align="center", font=("SimHei", 20, "bold"))
screen.update()

screen.exitonclick()
```

## ✏️ 课堂练习

### 1. 基础练习：代码填空
补全下面的代码，让烟花粒子能够正确地向外扩散：

```python
import math

# 粒子的当前坐标
x, y = 0, 0
# 粒子飞行的角度（弧度）
angle = math.radians(45)  # 45度角
# 粒子飞行的速度
speed = 5

# 计算下一帧的位置
new_x = x + math.____(angle) * speed
new_y = y + math.____(angle) * speed

print(f"粒子飞到了：({new_x:.2f}, {new_y:.2f})")
```

### 2. 基础练习：修改动画参数
- 将扩散步数从 40 改为 20，观察烟花有什么变化
- 将粒子数量从 30-50 改为 100-150，观察烟花有什么变化
- 去掉 `speed * 0.96` 这行（取消减速），观察效果

### 3. 挑战练习：下雨动画
运用今天学的"粒子系统"思想，做一个**下雨动画**。思路：
- 所有粒子初始在屏幕顶部，随机水平位置
- 每个粒子向下"落下"
- 当粒子落到屏幕底部时，重新回到顶部（循环）
- 雨滴可以是蓝色的短线或小圆点

### 4. 挑战练习：文字烟花
修改程序，让烟花爆炸后，粒子拼成一个文字或图案（比如一个爱心❤）。提示：可以预设一些目标坐标，让粒子"飞向"这些目标位置。

## 📋 小结

### 本节学了什么
- **动画原理**：用"画 → 清除 → 移动 → 再画"的循环来创造运动效果
- **turtle.tracer(0) 和 update()**：关闭自动刷新，手动控制帧显示，让动画更流畅
- **粒子系统**：把复杂的效果拆成很多独立的小粒子，每个粒子有自己的位置、方向和速度
- **三角函数在动画中的应用**：`math.cos(angle)` 和 `math.sin(angle)` 用来计算粒子在 x 和 y 方向的位移分量
- **随机**：用 `random` 让每朵烟花都有独一无二的颜色、大小和形态

### 下节预告
下节课我们要进行一场激动人心的**综合闯关挑战**！我们将把之前学过的知识（变量、条件判断、循环、列表、字符串、随机数）全部用上，设计关卡来考验自己的编程能力。你准备好了吗？让我们看看谁能通关成为"Python小达人"！
