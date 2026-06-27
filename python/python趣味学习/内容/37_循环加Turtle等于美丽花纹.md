# 第37节：循环加 Turtle 等于美丽花纹

## 🎯 教学目标
- 学生能够利用 for 循环配合旋转，创造出重复对称的花纹图案
- 学生能够理解"旋转对称"的概念：每次画完一个图形后旋转一定角度，再次画同样的图形
- 学生能够在循环中动态改变颜色和大小，产生渐变效果
- 学生能够独立写出"万花筒花纹"程序（36 次画圆，每次旋转 10 度）
- 学生能够体会到"简单的规则重复多次"能产生惊人美丽的图案

## 📝 重点概念
- **旋转对称**：把一个图形围绕中心点旋转一定角度后，和原来的图形完全重合。比如雪花有 6 重对称（360 ÷ 6 = 60°），五角星有 5 重对称（360 ÷ 5 = 72°）
- **循环加旋转**：在 for 循环中，每次画一个图形，然后旋转一个固定角度。用公式表达就是：`旋转角度 = 360 ÷ 重复次数`。如果重复 36 次，每次转 10°，刚好转满一整圈
- **万花筒效果**：当重复次数很多、每次旋转角度很小时，多个图形重叠交错，产生类似万花筒的奇幻效果
- **渐变颜色**：在循环中使用颜色列表，每次取不同颜色，让花纹色彩丰富

## 📖 讲解内容

### 步骤1：引入（5分钟）

同学们，你们玩过万花筒吗？

（展示一张万花筒的图片，或者拿一个真实的万花筒）

万花筒里面有几面镜子，把一些彩色碎屑反射、重复、对称地排列，就变出了让人眼花缭乱的美丽图案。你转一下万花筒，图案就会变化——但无论怎么变，它总是**对称的**、**有规律的**。

（在黑板上画一个简单的例子：画一个花瓣，旋转 60 度再画一个，转 60 度再画……共 6 次，组成一朵花）

今天我们要让海龟变成一个"万花筒制造机"！秘诀超级简单，就三步：
1. 在循环中画一个图形
2. 旋转一个角度
3. 不断重复

就这么简单！但画出来的效果会让你大吃一惊——几个正方形旋转叠加就能变成一朵花，几个圆旋转叠加就能变成一朵盛开的玫瑰！

**互动**：猜猜看，如果把一个正方形旋转 10 次，每次转 36 度（360 ÷ 10），会变成什么图案？（学生猜测后，老师演示——其实就是一个多层重叠的"星形花"）

### 步骤2：核心讲解（15-20分钟）

#### 2.1 旋转对称的秘密

核心思想非常简单：

```python
for i in range(重复次数):
    画一个图形()
    t.right(360 / 重复次数)    # 旋转角度 = 360 ÷ 重复次数
```

只要"重复次数"能整除 360，转完一整圈后所有图形就会完美地对称排列。

**举例说明**：

| 重复次数 | 每次旋转角度 | 效果 |
|----------|-------------|------|
| 4 | 90° | 4 个图形均匀分布（像指南针的四个方向） |
| 6 | 60° | 6 个图形均匀分布（像雪花） |
| 8 | 45° | 8 个图形均匀分布 |
| 12 | 30° | 12 个图形均匀分布（密密麻麻） |
| 36 | 10° | 36 个图形均匀分布（万花筒级别！） |

**生活化比喻**：想象你站在一个圆形舞台上，手拿一只画笔。你向前走几步画一条线，然后舞台把你旋转 30°，你再次向前画线，再转 30°……转了 12 次后（12 × 30° = 360°），你刚好转回原位。你画的 12 条线均匀分布在圆的一周——这就是旋转对称。

#### 2.2 循环中改变颜色

在循环里，我们可以用两种方法让颜色变化：

**方法一：颜色列表轮换**

```python
colors = ["red", "orange", "yellow", "green", "blue", "purple"]

for i in range(36):
    t.color(colors[i % len(colors)])   # i%6 让颜色循环
    # 画一个图形...
    t.right(10)
```

`i % 6` 的含义：
- i=0 → 0 % 6 = 0 → red
- i=1 → 1 % 6 = 1 → orange
- i=2 → 2 % 6 = 2 → yellow
- ...
- i=6 → 6 % 6 = 0 → red（循环回来了！）

**方法二：使用 RGB 颜色**

Python 的 turtle 基于 tkinter，支持十六进制颜色码。不过对于小学生来说，用颜色名称就足够了。

#### 2.3 循环中改变大小

除了颜色，我们还可以在每次循环中改变图形大小：

```python
for i in range(36):
    size = 50 + i * 5    # 每次都变大一点
    t.circle(size)
    t.right(10)
```

这样画出来的就是**螺旋花纹**——从中心向外越来越大，加上旋转，效果非常惊艳！

#### 2.4 经典花纹配方

以下是几种"经典配方"，保证画出来很好看：

**配方1：正方形花（8 个正方形，每次旋转 45°）**
```python
for i in range(8):
    for j in range(4):     # 画一个正方形
        t.forward(100)
        t.right(90)
    t.right(45)            # 旋转 45°
```

**配方2：圆形万花筒（36 个圆，每次旋转 10°）**
```python
for i in range(36):
    t.circle(100)
    t.right(10)
```

**配方3：渐变螺旋圆（36 个圆，越来越大，每次旋转 10°）**
```python
for i in range(36):
    t.circle(50 + i * 3)  # 半径从 50 逐渐增大到 155
    t.right(10)
```

### 步骤3：动手演示（10分钟）

**演示1：正方形花**

```python
import turtle

screen = turtle.Screen()
screen.title("正方形花")
screen.bgcolor("black")

t = turtle.Turtle()
t.shape("turtle")
t.pensize(2)
t.speed(10)

colors = ["red", "orange", "yellow", "green", 
          "cyan", "blue", "purple", "pink"]

for i in range(12):           # 画12个正方形
    t.color(colors[i % 8])     # 8种颜色轮换
    # 画一个正方形
    for j in range(4):
        t.forward(100)
        t.right(90)
    t.right(360 / 12)          # 旋转30度（360÷12=30）

t.hideturtle()
turtle.done()
```

让学生观察：12 个正方形重叠在一起，形成了一个星芒状的美丽图案！

**演示2：圆形万花筒（重头戏！）**

```python
import turtle

screen = turtle.Screen()
screen.title("圆形万花筒")
screen.bgcolor("black")

t = turtle.Turtle()
t.shape("turtle")
t.speed(0)          # 最快速度
t.pensize(1)

colors = ["red", "orange", "gold", "green", 
          "cyan", "blue", "purple", "magenta"]

for i in range(36):          # 画36个圆
    t.color(colors[i % 8])    # 8种颜色轮换
    t.circle(100)             # 半径100的圆
    t.right(10)               # 旋转10度（360÷36=10）

t.hideturtle()
turtle.done()
```

（运行这个代码时，通常会引起学生"哇——"的惊叹！36 个彩色圆重叠在一起，形成一朵复杂华丽的花纹。）

**演示3：渐变万花筒**

```python
# 在上面的代码基础上修改
for i in range(36):
    t.color(colors[i % 8])
    t.circle(30 + i * 4)   # 半径越来越大：30, 34, 38, 42, ..., 170
    t.right(10)
```

这次画的圆从中心向外越来越大，形成了螺旋放射状的华丽图案！

### 步骤4：独立练习（15分钟）

**基础任务**：
1. 画 6 个正方形，每次旋转 60°（360 ÷ 6），形成六角星花纹
2. 画 8 个正三角形，每次旋转 45°（360 ÷ 8），用彩虹色

**挑战任务**：
1. 画"圆形万花筒"：36 个圆，每次旋转 10°，半径 80，用 6 种颜色轮换
2. 画"正方形万花筒"：18 个正方形，每次旋转 20°（360 ÷ 18），边长 80

**超级挑战**：
设计你自己的"万花筒花纹"：
- 选择一种基本图形（正方形、三角形、圆形、or 半圆……）
- 选择重复次数和旋转角度
- 选择颜色方案
- 加上渐变大小效果
- 给你的花纹起个名

### 步骤5：分享与总结（5-10分钟）

举办"花纹设计大赛"：
- 每位同学展示自己的花纹作品
- 全班投票选出"最华丽花纹"、"最创意花纹"、"最彩色花纹"
- 请获奖同学分享代码思路

**讨论**：
- 为什么重复次数越多，花纹越"密"？
- 如果旋转角度不是 360 的约数（比如每次转 53 度），图案会怎样？（不会刚好合拢，会形成更复杂的重叠）
- 你还想到可以用哪些基本图形来创造花纹？

## 💻 代码示例

### 示例1：花瓣花纹（用弧线画花瓣）

```python
# -*- coding: utf-8 -*-
"""
第37节：用弧线画一朵美丽的"花瓣花纹"
每次画一个花瓣（弧线），旋转后画下一个
"""

import turtle

screen = turtle.Screen()
screen.title("花瓣花纹")
screen.bgcolor("lightyellow")

t = turtle.Turtle()
t.shape("turtle")
t.pensize(2)
t.speed(10)

# 花瓣的颜色
petal_colors = ["hotpink", "deeppink", "orchid", 
                "violet", "plum", "mediumpurple"]

for i in range(18):                    # 画18片花瓣
    t.color(petal_colors[i % 6])        # 6种粉色系颜色轮换
    
    # 画一片花瓣：两条弧线组成
    t.circle(60, 90)     # 第一段弧线（90度，四分之一圆）
    t.left(90)           # 调整方向
    t.circle(60, 90)     # 第二段弧线（回来）
    
    t.left(160)          # 旋转准备画下一片花瓣（注意不是 right，方向不同）

t.hideturtle()
turtle.done()
```

### 示例2：彩色圆形万花筒（经典36圆）

```python
# -*- coding: utf-8 -*-
"""
经典万花筒：36个彩色圆，每次旋转10度
这是最受学生欢迎的例子！
"""

import turtle

# ----- 设置 -----
screen = turtle.Screen()
screen.title("万花筒花纹")
screen.bgcolor("black")     # 黑色背景，颜色更突出！

t = turtle.Turtle()
t.shape("turtle")
t.speed(0)                  # 最快速度
t.pensize(1)

# 彩虹色列表
rainbow = ["red", "orange", "gold", "green", 
           "cyan", "blue", "purple", "magenta"]

print("万花筒开始转动啦！")

# ----- 36个圆，每次旋转10度 -----
for i in range(36):
    t.color(rainbow[i % len(rainbow)])  # 颜色循环
    t.circle(100)                        # 画半径100的圆
    t.right(10)                          # 旋转10度

print("万花筒完成！")

t.hideturtle()
turtle.done()
```

### 示例3：渐变大小的螺旋万花筒

```python
# -*- coding: utf-8 -*-
"""
渐变万花筒：36个圆从中心向外越来越大
"""

import turtle

screen = turtle.Screen()
screen.title("渐变万花筒")
screen.bgcolor("black")

t = turtle.Turtle()
t.shape("turtle")
t.speed(0)
t.pensize(1)

colors = ["red", "orange", "yellow", "green", 
          "cyan", "blue", "purple", "magenta"]

for i in range(36):
    t.color(colors[i % len(colors)])
    radius = 30 + i * 5    # 半径从30渐变到205
    t.circle(radius)        # 画圆
    t.right(10)             # 旋转10度

t.hideturtle()
turtle.done()
```

### 示例4：星形万花筒（用正方形创造星芒）

```python
# -*- coding: utf-8 -*-
"""
用正方形旋转叠加，创造放射状星芒效果
"""

import turtle

screen = turtle.Screen()
screen.title("星芒万花筒")
screen.bgcolor("navy")     # 深蓝色背景，像夜空

t = turtle.Turtle()
t.shape("turtle")
t.pensize(2)
t.speed(0)

# 金色系的颜色
star_colors = ["gold", "yellow", "orange", "lightyellow", 
               "khaki", "wheat"]

for i in range(18):           # 画18个正方形
    t.color(star_colors[i % len(star_colors)])
    
    # 画一个正方形
    for j in range(4):
        t.forward(120)
        t.right(90)
    
    t.right(20)               # 旋转20度（360÷18=20）

t.hideturtle()
turtle.done()
```

### 示例5：半圆花朵

```python
# -*- coding: utf-8 -*-
"""
用半圆画一朵漂亮的花
"""

import turtle

screen = turtle.Screen()
screen.title("半圆花朵")
screen.bgcolor("lightcyan")

t = turtle.Turtle()
t.shape("turtle")
t.pensize(3)
t.speed(10)

colors = ["coral", "tomato", "salmon", "lightcoral", 
          "indianred", "red"]

for i in range(12):                 # 12片花瓣
    t.color(colors[i % len(colors)])
    t.fillcolor(colors[i % len(colors)])
    t.begin_fill()
    t.circle(50, 180)               # 画一个半圆（就是一片花瓣）
    t.end_fill()
    t.right(150)                    # 转向下一片花瓣的位置

# 画花心
t.penup()
t.goto(0, -15)
t.pendown()
t.color("gold")
t.fillcolor("gold")
t.begin_fill()
t.circle(15)
t.end_fill()

t.hideturtle()
turtle.done()
```

## ✏️ 课堂练习

### 1. 基础练习：六角星花纹
- 画 6 个正方形，每次右转 60°（360 ÷ 6 = 60）
- 6 个正方形分别用红、橙、黄、绿、蓝、紫六种颜色
- 使用 `for i in range(6)` 的循环结构

### 2. 挑战练习：圆形万花筒
- 画 36 个圆，每次右转 10°
- 半径设为 80 或 100
- 从红、橙、黄、绿、青、蓝、紫、品红 8 种颜色中选择，在循环中轮换
- 设置背景为黑色，效果更佳

### 3. 超级挑战：设计你的专属花纹
- 选择你喜欢的基本图形（圆、正方形、三角形、弧线等）
- 决定重复次数和旋转角度
- 加入颜色变化和大小渐变
- 给你的花纹起一个好听的名字
- 写一段注释说明你的创作思路

## 📋 小结

### 本节学了什么
- **旋转对称**：`旋转角度 = 360 ÷ 重复次数`，利用这个公式可以创造完美的对称图案
- **循环 + 旋转**：在 for 循环中，每画一个图形后旋转一个固定角度，重复多次就形成了花纹
- **颜色轮换**：在循环中用 `colors[i % len(colors)]` 让颜色自动循环
- **渐变效果**：在循环中逐步改变图形大小，产生渐变/螺旋效果
- **万花筒原理**：简单的图形 + 重复旋转 = 复杂美丽的图案

最重要的启发是：**简单的事情重复做，就能创造出惊人的美丽**。就像万花筒，里面不过是几片彩色碎屑，但经过镜面的反复反射，就变成了令人叹为观止的图案。编程也是如此——用最基础的命令，加上循环和一点创意，就能创造出无限可能。

### 下节预告
下节课是本系列 Turtle 课程的最后一节——综合创作课！大家要用前面学到的所有技能，独立完成一幅 Turtle 画作。你可以画一幅风景画、一个卡通人物、一个抽象艺术图案……你的画笔你做主！发挥想象力，让我们看看谁的作品最精彩！
