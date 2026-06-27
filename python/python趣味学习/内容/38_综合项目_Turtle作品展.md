# 第38节：综合项目 —— Turtle 作品展

## 🎯 教学目标
- 学生能够回顾并综合运用 Turtle 课程所学的全部知识
- 学生能够独立完成一个原创 Turtle 画作项目
- 学生能够经历"构思—设计—编码—调试—展示"的完整创作流程
- 学生能够用代码表达创意，体会到编程创作的成就感
- 学生能够欣赏他人的作品，学会从代码中学习

## 📝 重点概念
- **创作流程**：构思主题 → 纸上草图 → 拆解元素 → 编写代码 → 调试修改 → 展示分享
- **拆解思维**：把复杂的画面拆解成基本几何元素（圆、正方形、三角形、弧线、直线）
- **代码组织**：用注释标注不同部分，用变量统一管理颜色和尺寸，让代码清晰易读
- **调试迭代**：运行代码 → 观察效果 → 调整参数 → 再次运行，不断打磨作品

## 📖 讲解内容

### 步骤1：引入（5分钟）

同学们，回想一下这几节课，我们的小海龟学会了多少本领！

（在黑板上快速回顾知识树：）

```
海龟 Turtle
├── 基本移动：forward(), backward(), right(), left()
├── 画正多边形：外角 = 360 ÷ 边数
├── 画圆和弧线：circle(半径), circle(半径, 角度)
├── 颜色魔法：color(), fillcolor(), begin_fill(), end_fill()
├── 画笔控制：pensize(), speed()
├── 移动魔法：penup(), pendown(), goto()
└── 循环花纹：for 循环 + 旋转 = 万花筒
```

短短几节课，我们已经掌握了一整套"画画工具箱"！今天，我们将把这些工具全部用上，每个人都是"Turtle 艺术家"，独立创作一幅属于自己的 Turtle 作品。

今天课堂的流程是：
1. 老师介绍创作思路（5 分钟）
2. 同学们构思和设计（5 分钟）
3. 自由编码创作时间（30 分钟）
4. 作品展示与分享（15 分钟）
5. 投票和颁奖（5 分钟）

**激励**：我们会选出"最佳创意奖"、"最美画面奖"、"最巧代码奖"等，每位同学的作品都会被保存下来！

### 步骤2：创作指导（10分钟）

#### 2.1 如何构思作品

不知道从何下手？这里有一些创作方向供你参考：

**方向一：自然风景**
- 太阳 + 云朵 + 彩虹 + 草地 + 小花
- 夜空：月亮 + 星星 + 流星
- 海底世界：鱼 + 海草 + 泡泡

**方向二：卡通角色**
- 小动物：猫、狗、兔子、熊猫
- 表情人物：笑脸家族、外星人
- 交通工具：小汽车、火箭、帆船

**方向三：几何艺术**
- 万花筒花纹 + 多层旋转
- 彩色马赛克拼图
- 迷宫图案

**方向四：节日主题**
- 圣诞树 + 礼物
- 春节灯笼 + 鞭炮
- 生日蛋糕 + 蜡烛

**方向五：抽象艺术**
- 随机颜色 + 随机大小 + 随机位置 = 独特的抽象画
- 用弧线和圆创造流动感

#### 2.2 拆解步骤

选定主题后，不要急着写代码，先做这三步：

**第 1 步：纸上画草图**
拿出一张白纸，简单画一下你的作品大概长什么样。不需要画得很好看，能看出每个部分在什么位置就行。

**第 2 步：拆解成基本图形**
把草图中的每个元素拆解成 Turtle 能画的基本图形：

| 画面元素 | 用什么 Turtle 命令实现 |
|----------|----------------------|
| 太阳 | `circle(半径)` + 黄色填充 |
| 阳光 | 循环画线段，`forward(长度)` + `right(角度)` |
| 云朵 | 几个叠加的 `circle(半径)` |
| 房子 | 正方形（墙） + 三角形（屋顶） |
| 树 | 长方形（树干） + 三角形/圆（树冠） |
| 花 | 循环 `circle(半径, 180)` 画花瓣 |
| 星星 | 五角星循环 `forward(边长)` + `right(144)` |

**第 3 步：规划代码结构**
用注释把代码分成几个部分：

```python
# ===== 第一部分：设置画布和海龟 =====
# ... screen 和 turtle 的基础设置

# ===== 第二部分：画天空/背景 =====
# ... 

# ===== 第三部分：画主体内容 =====
# ... 

# ===== 第四部分：画细节装饰 =====
# ... 

# ===== 第五部分：完成收尾 =====
t.hideturtle()
turtle.done()
```

#### 2.3 实用技巧

**技巧 1：用变量统一管理**
```python
# 把所有颜色和尺寸放在前面，方便统一修改
SUN_COLOR = "gold"
GRASS_COLOR = "green"
SKY_COLOR = "lightblue"
```

**技巧 2：用函数封装重复元素**
```python
def draw_star(x, y, size, color_name):
    """在 (x, y) 画一个指定大小和颜色的五角星"""
    t.penup()
    t.goto(x, y)
    t.pendown()
    t.color(color_name)
    t.begin_fill()
    for i in range(5):
        t.forward(size)
        t.right(144)
    t.end_fill()
```

**技巧 3：遇到 bug 不要慌**
- 海龟画到不对的位置？→ 用 `penup()` / `goto()` 调整
- 颜色不对？→ 检查 `color()` 的参数拼写
- 填充颜色"漏出来"？→ 确认图形是封闭的
- 图形方向不对？→ 用 `setheading()` 调整海龟朝向

### 步骤3：教师示范项目（简要演示，5分钟）

老师快速展示一个中等复杂度的作品，示范拆解和编码的思路。

**示例：一幅简单的风景画（5 分钟内演示关键步骤）**

```python
# -*- coding: utf-8 -*-
"""
风景画示例：蓝天、草地、太阳、小房子、一朵花
"""
import turtle

screen = turtle.Screen()
screen.title("我的风景画")
screen.bgcolor("skyblue")   # 蓝天背景

t = turtle.Turtle()
t.shape("turtle")
t.speed(8)

# ========== 1. 画草地 ==========
t.penup()
t.goto(-400, -100)
t.pendown()
t.color("green")
t.fillcolor("lightgreen")
t.begin_fill()
for _ in range(2):
    t.forward(800)
    t.right(90)
    t.forward(200)
    t.right(90)
t.end_fill()

# ========== 2. 画太阳 ==========
t.penup()
t.goto(200, 150)
t.pendown()
t.color("orange", "yellow")
t.begin_fill()
t.circle(60)
t.end_fill()

# ========== 3. 画小房子 ==========
def draw_house(x, y):
    t.penup()
    t.goto(x, y)
    t.pendown()
    # 墙壁
    t.color("brown", "wheat")
    t.begin_fill()
    for _ in range(4):
        t.forward(80)
        t.right(90)
    t.end_fill()
    # 屋顶（三角形）
    t.color("red", "red")
    t.begin_fill()
    t.left(45)
    t.forward(57)
    t.right(90)
    t.forward(57)
    t.right(135)
    t.forward(80)
    t.end_fill()

draw_house(-100, -100)

# ========== 4. 画一朵花 ==========
t.penup()
t.goto(-250, -80)
t.pendown()
for i in range(12):
    t.color("magenta")
    t.begin_fill()
    t.circle(15, 180)
    t.end_fill()
    t.right(150)

t.hideturtle()
turtle.done()
```

强调：这只是示例，同学们可以画得更丰富、更有创意！

### 步骤4：自由创作（30分钟）

同学们独立创作，老师在教室走动指导：
- 帮助有困难的同学完成基础任务
- 鼓励有能力的同学增加更多细节
- 提醒大家注意代码的注释和排版

**分层任务**：

**基础级（必须完成）**：
画一幅包含至少 3 种不同图形的作品（如：圆 + 正方形 + 三角形）

**进阶级（推荐完成）**：
画一幅包含至少 5 种元素的彩色作品，使用填充颜色

**挑战级（自由发挥）**：
画一幅完整主题的作品，包含背景、主体、细节，用循环或函数组织代码

### 步骤5：作品展示与分享（15分钟）

**展示环节**（每位同学 1-2 分钟）：
1. 运行你的代码，向全班展示你的作品
2. 介绍一下你的创作主题和想法
3. 说说你用了哪些 Turtle 命令
4. 分享创作过程中遇到的一个小困难，以及你是怎么解决的

**投票评选**：
- 最佳创意奖（1-2名）：主题最有创意
- 最美画面奖（1-2名）：画面最漂亮
- 最巧代码奖（1-2名）：代码写得最清晰、最有技巧
- 最佳进步奖（1-2名）：相比前几节课进步最大的同学

每位同学的作品截图和代码都可以保存下来，作为学习纪念！

## 💻 代码示例

### 示例1：夜空中的烟花

```python
# -*- coding: utf-8 -*-
"""
综合项目示例：夜空中的烟花
使用循环 + 随机 + 颜色，创造烟花绽放的效果
"""

import turtle
import random

screen = turtle.Screen()
screen.title("烟花大会")
screen.bgcolor("black")

t = turtle.Turtle()
t.shape("turtle")
t.speed(0)      # 最快速度
t.pensize(2)

# 烟花颜色
firework_colors = ["red", "orange", "yellow", "gold",
                   "green", "cyan", "blue", "purple",
                   "magenta", "pink", "white"]

def draw_firework(x, y, color_name):
    """在 (x, y) 画一朵烟花"""
    t.penup()
    t.goto(x, y)
    t.pendown()
    t.color(color_name)
    
    # 烟花的每一条光线
    for i in range(18):         # 18条光线
        t.forward(50)
        t.backward(50)
        t.right(20)             # 360 ÷ 18 = 20度

# 在随机位置画多个烟花
for _ in range(8):
    x = random.randint(-300, 300)
    y = random.randint(-200, 200)
    color = random.choice(firework_colors)
    draw_firework(x, y, color)

# 画一个城市地平线
t.penup()
t.goto(-400, -200)
t.pendown()
t.color("gray")
t.pensize(1)
t.fillcolor("darkgray")
t.begin_fill()
t.forward(800)
t.left(90)
t.forward(70)
t.left(90)
t.forward(800)
t.left(90)
t.forward(70)
t.end_fill()

t.hideturtle()
turtle.done()
```

### 示例2：海底世界

```python
# -*- coding: utf-8 -*-
"""
综合项目示例：海底世界
包含鱼、泡泡、海草、海底沙地
"""

import turtle

screen = turtle.Screen()
screen.title("海底世界")
screen.bgcolor("darkblue")

t = turtle.Turtle()
t.shape("turtle")
t.speed(8)
t.pensize(3)

# ===== 1. 画海底沙地 =====
t.penup()
t.goto(-400, -200)
t.pendown()
t.color("sandybrown")
t.fillcolor("sandybrown")
t.begin_fill()
t.forward(800)
t.left(90)
t.forward(100)
t.left(90)
t.forward(800)
t.left(90)
t.forward(100)
t.end_fill()

# ===== 2. 画海草 =====
def draw_seaweed(x, y):
    """画一根海草"""
    t.penup()
    t.goto(x, y)
    t.pendown()
    t.pensize(3)
    t.color("green")
    t.setheading(90)
    t.circle(30, 120)
    t.circle(-30, 120)

# 画多根海草
for i in range(6):
    draw_seaweed(-300 + i * 100, -180)

# ===== 3. 画一条鱼 =====
def draw_fish(x, y, body_color):
    """画一条鱼"""
    t.penup()
    t.goto(x, y)
    t.pendown()
    t.pensize(2)
    
    # 鱼身（椭圆用拉伸的圆模拟）
    t.color(body_color)
    t.fillcolor(body_color)
    t.setheading(0)
    t.begin_fill()
    t.circle(25, 180)      # 上半部分
    t.circle(-25, 180)     # 下半部分
    t.end_fill()
    
    # 鱼尾（三角形）
    t.color("orange")
    t.fillcolor("orange")
    t.begin_fill()
    t.left(120)
    t.forward(30)
    t.left(120)
    t.forward(30)
    t.end_fill()
    
    # 鱼眼
    t.penup()
    t.setheading(0)
    t.forward(10)
    t.left(90)
    t.forward(12)
    t.pendown()
    t.color("black")
    t.fillcolor("white")
    t.begin_fill()
    t.circle(5)
    t.end_fill()
    t.color("black")
    t.fillcolor("black")
    t.begin_fill()
    t.circle(2)
    t.end_fill()

# 画两条鱼
draw_fish(-100, 50, "orange")
draw_fish(80, 80, "hotpink")

# ===== 4. 画泡泡 =====
def draw_bubble(x, y, size):
    t.penup()
    t.goto(x, y)
    t.pendown()
    t.pensize(1)
    t.color("lightcyan")
    t.circle(size)

for bx in [-150, -50, 50, 150, -100]:
    by = -120 + bx * 0.3
    draw_bubble(bx, by, 10 + (bx % 20))

t.hideturtle()
turtle.done()
```

### 示例3：生日蛋糕

```python
# -*- coding: utf-8 -*-
"""
综合项目示例：生日蛋糕
包含多层蛋糕、奶油花边、蜡烛、火焰
"""

import turtle

screen = turtle.Screen()
screen.title("生日快乐！")
screen.bgcolor("lightyellow")

t = turtle.Turtle()
t.shape("turtle")
t.speed(5)

# ===== 1. 蛋糕底层 =====
t.penup()
t.goto(-150, -100)
t.pendown()
t.color("chocolate")
t.fillcolor("pink")
t.begin_fill()
for _ in range(2):
    t.forward(300)
    t.left(90)
    t.forward(60)
    t.left(90)
t.end_fill()

# ===== 2. 蛋糕中层 =====
t.penup()
t.goto(-120, -40)
t.pendown()
t.color("chocolate")
t.fillcolor("lightyellow")
t.begin_fill()
for _ in range(2):
    t.forward(240)
    t.left(90)
    t.forward(55)
    t.left(90)
t.end_fill()

# ===== 3. 蛋糕顶层 =====
t.penup()
t.goto(-90, 15)
t.pendown()
t.color("chocolate")
t.fillcolor("lightpink")
t.begin_fill()
for _ in range(2):
    t.forward(180)
    t.left(90)
    t.forward(50)
    t.left(90)
t.end_fill()

# ===== 4. 奶油花边 =====
t.penup()
t.goto(-150, -40)
t.pendown()
t.pensize(4)
t.color("white")
for _ in range(7):    # 7个奶油波浪
    t.circle(10, 180)
    t.right(180)
    t.forward(40)

t.penup()
t.goto(-120, 15)
t.pendown()
for _ in range(6):
    t.circle(10, 180)
    t.right(180)
    t.forward(40)

# ===== 5. 蜡烛 =====
candle_positions = [-50, -20, 10, 40]
for cx in candle_positions:
    t.penup()
    t.goto(cx, 65)
    t.pendown()
    t.color("blue")
    t.pensize(6)
    t.setheading(90)
    t.forward(50)      # 蜡烛棒
    
    # 火焰
    t.color("orange")
    t.fillcolor("yellow")
    t.begin_fill()
    t.circle(6)
    t.end_fill()

# ===== 6. 文字 =====
t.penup()
t.goto(-140, 150)
t.pendown()
t.pensize(1)
t.color("red")
t.write("Happy Birthday!", font=("Arial", 24, "bold"))

t.hideturtle()
turtle.done()
```

## ✏️ 创作任务

### 你的创作任务：自由创作一幅 Turtle 画作

**要求**：
1. **确定主题**：给你的作品选一个主题（风景、卡通、几何艺术、节日...）
2. **使用至少 3 种不同的 Turtle 命令**：如 `forward()`、`circle()`、`begin_fill()` 等
3. **使用至少 2 种颜色**：让你的画面丰富多彩
4. **代码要有注释**：标明每个部分画的是什么
5. **给它起个名字**：写在代码开头的注释里

**创作流程**：
```
第1步（5分钟）：确定主题 + 纸上画草图
第2步（5分钟）：拆解成基本图形，规划代码结构
第3步（25分钟）：编写代码，不断调试完善
第4步（预留时间）：展示与分享
```

**创意参考**：

| 主题 | 可能用到的元素 | 难度 |
|------|--------------|------|
| 笑脸 | 圆、弧线、小圆点 | ★★☆ |
| 雪人 | 3个圆、三角形鼻子、围巾 | ★★☆ |
| 太阳花 | 圆 + 循环花瓣 | ★★★ |
| 小房子 | 正方形 + 三角形 + 长方形 | ★★★ |
| 彩虹风景 | 弧线 + 太阳 + 草地 | ★★★★ |
| 海底世界 | 鱼 + 泡泡 + 海草 + 沙地 | ★★★★ |
| 万花筒艺术 | 循环 + 旋转 + 多彩颜色 | ★★★★★ |
| 烟花夜景 | 循环 + 随机 + 多种颜色 | ★★★★★ |

## 📋 小结

### 本节学了什么
- **综合创作**：将 Turtle 全部知识整合运用，完成一幅完整的作品
- **创作流程**：构思 → 草图 → 拆解 → 编码 → 调试 → 展示
- **拆解思维**：把复杂画面拆成基本图形，再用代码逐个实现
- **代码组织**：用注释、变量、函数让代码清晰有条理

### Turtle 系列课程回顾

六节课的 Turtle 之旅到这里就结束了。让我们一起回顾一下：

| 节次 | 内容 | 你学会了 |
|------|------|----------|
| 第33节 | 认识 Turtle | import turtle, forward, backward, right, left |
| 第34节 | 基本图形 | for 循环, 外角公式, 正多边形 |
| 第35节 | 圆和弧线 | circle(半径), circle(半径, 角度), 笑脸/雪人 |
| 第36节 | 让画面漂亮 | color, pensize, speed, fill, penup/pendown |
| 第37节 | 循环花纹 | 旋转对称, 万花筒, 颜色渐变 |
| 第38节 | 综合创作 | 拆解思维, 完整项目, 创意表达 |

从最初的"往前走 100 步"，到如今能独立创作出色彩斑斓的画作，你们每个人都是了不起的"海龟小画家"！

**最重要的收获**：编程不只是敲代码——它是**用逻辑创造美、用创意表达想法**的过程。希望这六节课不仅教会了你们 Turtle 的用法，更让你们感受到了编程的乐趣和创造的成就感。

### 下一步学什么？
Turtle 只是 Python 世界的一个小角落。接下来，我们可以探索更多有趣的 Python 知识——比如用 Pygame 做小游戏、用 Python 处理图片、甚至用 Python 控制机器人！编程的世界无限广阔，希望你们保持好奇心和创造力，继续前行！
