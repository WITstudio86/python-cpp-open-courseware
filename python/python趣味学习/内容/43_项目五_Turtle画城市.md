# 第43节：项目五 —— Turtle 画城市

## 🎯 教学目标
- 学生能够综合运用 Turtle 库的绘图功能（移动、转向、颜色、填充）
- 学生能够将重复的绘制任务封装成函数（画房子、画树、画太阳）
- 学生能够使用 `.goto()` 和 `.penup()`/`.pendown()` 在画布上移动而不留痕迹
- 学生能够规划画面布局，创作一幅"我的城市"主题画作

## 📝 重点概念
- **Turtle 绘图**：Python 内置的海龟画图库，通过给"小海龟"发指令来画画
- **函数封装绘图**：把"画一个房子"的步骤打包成 `draw_house(x, y)` 函数，需要时一行搞定
- **坐标移动**：`.goto(x, y)` 让海龟飞到指定位置，相当于把笔移到纸上的某个点
- **抬笔/落笔**：`.penup()` 就像把笔抬离纸面（移动不留痕），`.pendown()` 就像把笔放回纸面（移动就画线）

## 📖 讲解内容

### 步骤1：引入（5分钟）

> 老师展示一张城市的简笔画（或快速在纸上手绘）：有房子、树木、太阳、云朵。然后问学生："如果让你们用 Python 代码来画这张画，你们觉得可能吗？"

展示一个用 Turtle 画好的城市效果图（老师提前准备好截图），让学生惊叹。

生活比喻：**Turtle 就像一只会画画的小海龟**
- 你告诉它"往前走 100 步"，它就画一条 100 像素的线
- 你告诉它"向右转 90 度"，它就改变方向
- 你告诉它"变成红色"，它就用红笔画
- 你告诉它"飞到坐标 (100, 50)"，它就嗖的一下移过去

另一个比喻：**函数封装就像制造印章**
- 你做了一个"房子印章"，以后只要说"在这里盖个房子！"就能印出来
- 你做了一个"大树印章"，以后只要说"在这里种棵树！"就能印出来
- 你把各种印章组合在一起，就能建造一座城市！

### 步骤2：核心讲解（15-20分钟）

#### 2.1 Turtle 基础命令回顾

```python
import turtle

# 创建海龟
t = turtle.Turtle()

# 移动
t.forward(100)   # 前进 100 像素
t.backward(50)   # 后退 50 像素

# 转向
t.left(90)       # 左转 90 度
t.right(45)      # 右转 45 度

# 笔的控制
t.penup()        # 抬笔（移动不画线）
t.pendown()      # 落笔（移动就画线）

# 颜色和样式
t.pencolor("red")       # 笔的颜色
t.fillcolor("yellow")   # 填充颜色
t.pensize(3)            # 笔的粗细

# 填充形状
t.begin_fill()    # 开始填充
# ... 画一个封闭形状 ...
t.end_fill()      # 结束填充（自动填色）

# 坐标移动
t.goto(100, 50)   # 飞到坐标 (100, 50)
t.setheading(0)   # 朝向右边（0 度）

# 速度
t.speed(10)       # 1=最慢, 10=最快, 0=瞬间

# 隐藏海龟
t.hideturtle()
```

#### 2.2 坐标系统理解

把画布想象成一张坐标纸：
- 中心点是 (0, 0)
- 向右是 X 轴正方向，向上是 Y 轴正方向
- 默认画布大小约 800x600 像素

```
        Y轴 ↑
        (0, 300)
          |
(-400, 0) ———+——— (400, 0) → X轴
          |
        (0, -300)
```

所以：
- 画房子在地面上 → y 坐标是负数（如 y = -100）
- 画太阳在天空 → y 坐标是正数（如 y = 200）
- 画树排列在一条街上 → x 坐标依次增加（如 x = -200, -100, 0...）

#### 2.3 用函数封装绘图元素

这是一个非常重要的编程思维：**把复杂的东西拆成小块，每块封装成一个函数**。

**画房子的函数**：

```python
def draw_house(t, x, y, color="brown"):
    """在坐标 (x, y) 画一个房子
    
    参数:
        t: 海龟对象
        x, y: 房子的左下角坐标
        color: 房子的颜色
    """
    t.penup()
    t.goto(x, y)      # 飞到房子左下角
    t.pendown()
    t.pencolor("black")
    t.fillcolor(color)
    
    t.begin_fill()
    # 画房子的正方形主体
    for i in range(4):
        t.forward(80)
        t.left(90)
    t.end_fill()
    
    # 画三角形屋顶
    t.fillcolor("red")
    t.begin_fill()
    t.left(60)
    t.forward(80)
    t.right(120)
    t.forward(80)
    t.right(120)
    t.end_fill()
    
    # 画门
    t.penup()
    t.goto(x + 30, y)  # 移到房子底部的中间偏右
    t.pendown()
    t.setheading(90)   # 朝向正上方
    t.fillcolor("white")
    t.begin_fill()
    for i in range(2):
        t.forward(30)
        t.right(90)
        t.forward(20)
        t.right(90)
    t.end_fill()
```

**画树的函数**：

```python
def draw_tree(t, x, y):
    """在坐标 (x, y) 画一棵树"""
    t.penup()
    t.goto(x, y)
    t.pendown()
    t.setheading(90)
    
    # 画树干
    t.pencolor("saddlebrown")
    t.fillcolor("saddlebrown")
    t.pensize(8)
    t.begin_fill()
    t.forward(60)
    t.right(90)
    t.forward(10)
    t.right(90)
    t.forward(60)
    t.right(90)
    t.forward(10)
    t.end_fill()
    
    # 画树冠（圆形）
    t.penup()
    t.goto(x - 20, y + 50)
    t.pendown()
    t.pencolor("green")
    t.fillcolor("limegreen")
    t.pensize(2)
    t.begin_fill()
    t.circle(30)  # 画一个半径 30 的圆
    t.end_fill()
```

**画太阳的函数**：

```python
def draw_sun(t, x, y, radius=50):
    """在坐标 (x, y) 画一个太阳"""
    t.penup()
    t.goto(x, y - radius)  # 圆心在 (x, y)，移到圆的最下方开始画
    t.pendown()
    t.pencolor("orange")
    t.fillcolor("yellow")
    t.pensize(2)
    
    t.begin_fill()
    t.circle(radius)
    t.end_fill()
    
    # 画光芒
    t.penup()
    t.goto(x, y)
    t.pencolor("gold")
    t.pensize(3)
    for angle in range(0, 360, 30):  # 每隔 30 度画一道光芒
        t.penup()
        t.goto(x, y)
        t.setheading(angle)
        t.pendown()
        t.forward(radius + 15)
        t.penup()
        t.goto(x, y)
```

**画云朵的函数**：

```python
def draw_cloud(t, x, y):
    """在坐标 (x, y) 画一朵云"""
    t.penup()
    t.goto(x, y)
    t.pendown()
    t.pencolor("lightgray")
    t.fillcolor("white")
    t.pensize(2)
    
    t.begin_fill()
    t.circle(25)
    t.penup()
    t.goto(x + 30, y + 10)
    t.pendown()
    t.circle(20)
    t.penup()
    t.goto(x + 55, y)
    t.pendown()
    t.circle(25)
    t.penup()
    t.goto(x + 20, y - 10)
    t.pendown()
    t.circle(22)
    t.end_fill()
```

#### 2.4 组合：建造城市

把各个元素放在一起，规划好位置：

```python
import turtle

# 设置画布
screen = turtle.Screen()
screen.setup(800, 600)
screen.bgcolor("skyblue")  # 天空背景
screen.title("我的城市")

t = turtle.Turtle()
t.speed(0)  # 最快速度

# ── 画天空的元素 ──
draw_sun(t, 250, 180, 40)       # 右上角的太阳
draw_cloud(t, -200, 200)        # 左上角的云
draw_cloud(t, 0, 220)           # 中间的云
draw_cloud(t, 200, 190)         # 右边的云

# ── 画地面 ──
t.penup()
t.goto(-400, -100)
t.pendown()
t.pencolor("green")
t.fillcolor("lightgreen")
t.begin_fill()
t.goto(400, -100)   # 画到底部
t.goto(400, -300)
t.goto(-400, -300)
t.goto(-400, -100)
t.end_fill()

# ── 画地上的元素 ──
draw_house(t, -250, -100, "brown")    # 房子 1
draw_house(t, -80, -100, "purple")    # 房子 2
draw_house(t, 90, -100, "blue")       # 房子 3
draw_tree(t, -320, -100)              # 树 1
draw_tree(t, -180, -100)              # 树 2
draw_tree(t, -10, -100)               # 树 3
draw_tree(t, 200, -100)               # 树 4

t.hideturtle()
screen.mainloop()
```

### 步骤3：动手演示（10分钟）

教师按以下顺序演示，让学生看到城市一步步"建造"出来的过程：

1. **导入 turtle 并设置画布**（天空蓝背景 + 绿色草地）
2. **先画天空**：太阳 + 几朵白云（运行一次，让学生看到效果）
3. **再画地面**：用一个大矩形填充绿色（运行一次）
4. **画一栋房子**：运行 `draw_house` 函数（展示函数的神奇：一行代码一栋房子）
5. **复制房子**：改变坐标，画 3 栋不同颜色的房子（展示函数的复用威力）
6. **画树**：在不同位置种树
7. **整体运行**：看完整的城市画面

在演示过程中强调：
- `penup()` 和 `pendown()` 的区别——抬笔才能"飞"，落笔才能画
- `.goto(x, y)` 就是"飞"到指定位置
- 函数封装让代码从 200 行变成 50 行

### 步骤4：独立练习（15分钟）

**基础任务**（所有学生都要完成）：
1. 抄写老师的代码，画出"我的城市"
2. 修改房子和树的位置，规划出自己想要的布局
3. 至少画 3 栋房子和 4 棵树

**挑战任务**（学有余力的学生）：
1. **添加新元素**：画路灯、画小路、画小鸟、画篱笆
2. **画一个学校**：比房子大一点，加个钟楼
3. **画一条马路**：用灰色矩形 + 白色虚线（车道线）
4. **动态效果**：让太阳缓缓移动（从左边升起到右边落下）
5. **多色树冠**：用不同深浅的绿色画树冠，秋天用橙色和红色

**路灯示例**：

```python
def draw_lamp(t, x, y):
    """画一个路灯"""
    # 灯柱
    t.penup()
    t.goto(x, y)
    t.pendown()
    t.pencolor("gray")
    t.pensize(4)
    t.setheading(90)
    t.forward(80)
    # 灯臂
    t.right(90)
    t.forward(20)
    # 灯泡
    t.pencolor("yellow")
    t.fillcolor("yellow")
    t.begin_fill()
    t.circle(10)
    t.end_fill()
```

### 步骤5：分享与总结（5-10分钟）

- **作品展览**：每个学生运行自己的代码，展示"我的城市"，其他人参观
- **最佳城市奖**：投票选出最有创意的城市（最漂亮的、最特别的、最整齐的...）
- 讨论：函数封装的好处是什么？如果不用函数，画 10 栋房子会怎么样？
- 讨论：如果想把房子画大一点，要怎么改？→ 在函数里加一个 `size` 参数

## 💻 代码示例

### 完整版：Turtle 画城市

```python
"""
我的城市 —— Turtle 绘图项目
用 Python 的海龟画图建造一座美丽的城市！
"""

import turtle

# ──────────── 工具函数：绘制各种元素 ────────────

def draw_sun(t, x, y, radius=50):
    """画一个带光芒的太阳
    
    参数:
        t: 海龟对象
        x, y: 太阳中心的坐标
        radius: 太阳的半径
    """
    # 画太阳本体
    t.penup()
    t.goto(x, y - radius)  # 移到圆的底部开始画
    t.pendown()
    t.pencolor("orange")
    t.fillcolor("gold")
    t.pensize(2)
    
    t.begin_fill()
    t.circle(radius)
    t.end_fill()
    
    # 画光芒（12 道光线）
    t.pencolor("gold")
    t.pensize(3)
    for angle in range(0, 360, 30):
        t.penup()
        t.goto(x, y)
        t.setheading(angle)
        t.pendown()
        t.forward(radius + 15)
        # 画完一道光，回到中心准备画下一道
        t.penup()
        t.goto(x, y)


def draw_cloud(t, x, y, scale=1.0):
    """画一朵白云（用几个圆拼成）
    
    参数:
        t: 海龟对象
        x, y: 云朵左下角的参考坐标
        scale: 缩放比例（1.0 = 正常大小）
    """
    r1 = 25 * scale
    r2 = 20 * scale
    
    t.penup()
    t.goto(x, y)
    t.pendown()
    t.pencolor("lightgray")
    t.fillcolor("white")
    t.pensize(2)
    
    t.begin_fill()
    t.circle(r1)                    # 左下大圆
    t.penup()
    t.goto(x + 30 * scale, y + 10 * scale)
    t.pendown()
    t.circle(r2)                    # 上部小圆
    t.penup()
    t.goto(x + 55 * scale, y)
    t.pendown()
    t.circle(r1)                    # 右下大圆
    t.penup()
    t.goto(x + 20 * scale, y - 10 * scale)
    t.pendown()
    t.circle(r2 + 2 * scale)        # 中间底部圆
    t.end_fill()


def draw_house(t, x, y, wall_color="brown", width=80, height=70):
    """画一座带门和窗户的房子
    
    参数:
        t: 海龟对象
        x, y: 房子左下角坐标
        wall_color: 墙壁颜色
        width: 房子宽度
        height: 墙壁高度
    """
    # ── 画墙壁（矩形）──
    t.penup()
    t.goto(x, y)
    t.pendown()
    t.setheading(0)          # 朝右
    t.pencolor("black")
    t.fillcolor(wall_color)
    t.pensize(2)
    
    t.begin_fill()
    for i in range(2):
        t.forward(width)
        t.left(90)
        t.forward(height)
        t.left(90)
    t.end_fill()
    
    # ── 画三角形屋顶 ──
    t.fillcolor("darkred")
    t.begin_fill()
    t.left(45)               # 倾斜 45 度
    roof_side = (width / 2) / 0.707  # 用三角函数算斜边
    t.forward(roof_side)
    t.right(90)
    t.forward(roof_side)
    t.right(135)             # 回正
    t.end_fill()
    
    # ── 画门 ──
    t.penup()
    t.goto(x + width * 0.4, y)  # 门在底部中间
    t.pendown()
    t.setheading(90)         # 朝上
    t.fillcolor("peru")
    t.begin_fill()
    for i in range(2):
        t.forward(height * 0.45)
        t.right(90)
        t.forward(width * 0.2)
        t.right(90)
    t.end_fill()
    
    # ── 画门把手 ──
    t.penup()
    t.goto(x + width * 0.55, y + height * 0.15)
    t.pendown()
    t.pencolor("gold")
    t.fillcolor("gold")
    t.begin_fill()
    t.circle(2)
    t.end_fill()
    
    # ── 画窗户（左边）──
    t.penup()
    t.goto(x + width * 0.1, y + height * 0.4)
    t.pendown()
    t.setheading(90)
    t.pencolor("lightblue")
    t.fillcolor("lightblue")
    t.begin_fill()
    for i in range(4):
        t.forward(15)
        t.right(90)
    t.end_fill()
    
    # ── 画窗户（右边）──
    t.penup()
    t.goto(x + width * 0.7, y + height * 0.4)
    t.pendown()
    t.begin_fill()
    for i in range(4):
        t.forward(15)
        t.right(90)
    t.end_fill()


def draw_tree(t, x, y, scale=1.0):
    """画一棵树（树干 + 圆形树冠）
    
    参数:
        t: 海龟对象
        x, y: 树的底部坐标
        scale: 缩放比例
    """
    trunk_w = 10 * scale
    trunk_h = 60 * scale
    crown_r = 30 * scale
    
    # ── 画树干 ──
    t.penup()
    t.goto(x - trunk_w/2, y)
    t.pendown()
    t.setheading(90)
    t.pencolor("saddlebrown")
    t.fillcolor("saddlebrown")
    t.pensize(2)
    
    t.begin_fill()
    for i in range(2):
        t.forward(trunk_h)
        t.right(90)
        t.forward(trunk_w)
        t.right(90)
    t.end_fill()
    
    # ── 画树冠（圆形）──
    t.penup()
    t.goto(x - crown_r, y + trunk_h * 0.8)
    t.pendown()
    t.pencolor("darkgreen")
    t.fillcolor("forestgreen")
    
    t.begin_fill()
    t.circle(crown_r)
    t.end_fill()
    
    # 加一些"叶子"的点缀（深浅绿色交替）
    t.fillcolor("limegreen")
    t.penup()
    t.goto(x - crown_r * 0.3, y + trunk_h * 0.8 + crown_r * 0.5)
    t.pendown()
    t.begin_fill()
    t.circle(crown_r * 0.4)
    t.end_fill()


def draw_ground(t, ground_y=-100):
    """画绿色的草地
    
    参数:
        t: 海龟对象
        ground_y: 地面线的 y 坐标
    """
    t.penup()
    t.goto(-400, ground_y)
    t.pendown()
    t.setheading(0)
    t.pencolor("green")
    t.fillcolor("lightgreen")
    
    t.begin_fill()
    t.goto(400, ground_y)   # 画地面线
    t.goto(400, -300)       # 右下角
    t.goto(-400, -300)      # 左下角
    t.goto(-400, ground_y)  # 回到起点
    t.end_fill()
    
    # 给地面画一条深绿色的边线
    t.penup()
    t.goto(-400, ground_y)
    t.pendown()
    t.pencolor("forestgreen")
    t.pensize(3)
    t.goto(400, ground_y)


def draw_road(t, y=-120):
    """画一条灰色的马路
    
    参数:
        t: 海龟对象
        y: 马路的 y 坐标
    """
    t.penup()
    t.goto(-400, y)
    t.pendown()
    t.setheading(0)
    t.pencolor("gray")
    t.fillcolor("gray")
    t.pensize(2)
    
    t.begin_fill()
    t.goto(400, y)
    t.goto(400, y - 50)
    t.goto(-400, y - 50)
    t.goto(-400, y)
    t.end_fill()
    
    # 画虚线（车道分界线）
    t.pencolor("white")
    t.pensize(3)
    t.penup()
    t.goto(-380, y - 25)
    for i in range(20):
        t.pendown()
        t.forward(20)
        t.penup()
        t.forward(20)


# ──────────── 主程序：建造城市 ────────────

def main():
    # 设置画布
    screen = turtle.Screen()
    screen.setup(900, 650)           # 画布大小
    screen.bgcolor("skyblue")        # 天空背景色
    screen.title("🏙️  我的城市 —— Python Turtle")
    screen.tracer(0)                 # 关闭动画，让绘制瞬间完成
    
    # 创建海龟
    t = turtle.Turtle()
    t.speed(0)  # 最快速度
    t.hideturtle()
    
    # ── 第一步：画天空元素 ──
    print("正在画天空...")
    draw_sun(t, 300, 180, 45)       # 太阳在右上角
    draw_cloud(t, -250, 200)        # 左边一朵大云
    draw_cloud(t, -50, 230, 0.8)    # 中间一朵小云
    draw_cloud(t, 180, 200, 0.9)    # 右边一朵云
    
    # ── 第二步：画地面 ──
    print("正在画地面和马路...")
    draw_ground(t, -100)            # 绿色草地
    draw_road(t, -120)              # 灰色马路
    
    # ── 第三步：画地上的建筑和植物 ──
    print("正在建造房屋和种植树木...")
    
    # 后排远景（小一点的房子，在 y 比较高的位置）
    draw_house(t, -180, -40, "tan", 50, 40)
    draw_house(t, 20, -40, "wheat", 50, 40)
    
    # 前排房子（大房子）
    draw_house(t, -320, -100, "burlywood", 70, 60)
    draw_house(t, -160, -100, "cadetblue", 75, 65)
    draw_house(t, 0, -100, "rosybrown", 70, 55)
    draw_house(t, 150, -100, "mediumpurple", 65, 60)
    
    # 在房子旁边种树
    tree_positions = [-350, -260, -100, -40, 70, 220, 280]
    for pos in tree_positions:
        # 用不同的大小，让树看起来有远近层次
        import random
        s = random.uniform(0.7, 1.2)
        draw_tree(t, pos, -100, s)
    
    # ── 第四步：署名 ──
    t.penup()
    t.goto(0, -260)
    t.pendown()
    t.pencolor("white")
    t.write("🏙️  我的城市", align="center", font=("Arial", 20, "bold"))
    
    t.penup()
    t.goto(0, -285)
    t.pencolor("lightgray")
    t.write("用 Python Turtle 绘制", align="center", font=("Arial", 12, "normal"))
    
    # ── 完成 ──
    screen.tracer(1)  # 恢复动画
    print("✅ 城市建设完成！点击画布窗口关闭。")
    screen.mainloop()


# 程序入口
if __name__ == "__main__":
    main()
```

## ✏️ 课堂练习

### 1. 基础练习：补全画房子的函数

下面画房子的函数缺少了几个参数，请补全：

```python
def draw_house(t, x, y, color):
    # 画墙壁
    t.penup()
    t.______(x, y)        # ① 飞到指定位置
    t.pendown()
    t.fillcolor(______)   # ② 应该填什么？
    t.begin_fill()
    for i in range(______):  # ③ 正方形需要循环几次？
        t.forward(80)
        t.left(90)
    t.end_fill()
```

### 2. 挑战练习：创意城市

在基础城市的基础上，发挥你的创意：

**任务 A：画一个学校**
- 比普通房子大两倍
- 上方有一个钟楼（长方形 + 圆形时钟）
- 旁边有一个小操场（绿色矩形）
- 校门口插一面红旗

**任务 B：画夜晚的城市**
- 背景改成深蓝色（`screen.bgcolor("darkblue")`）
- 太阳换成月亮和星星
- 给每个房子的窗户涂上黄色（亮灯）
- 用黑色画几个小人在路上走

**任务 C：动态城市**（最难）
- 让太阳从左边移动到右边（用 for 循环和 `time.sleep()`）
- 画完后让一辆小车从马路左边开到右边
- 给云朵加一个缓慢飘动的效果

## 📋 小结

### 本节学了什么
- **Turtle 综合应用**：forward、left、right、penup、pendown、goto、color、fill 等命令的组合使用
- **函数封装绘图**：用 `def draw_xxx(t, x, y)` 把元素做成"印章"，需要时一行调用
- **坐标布局**：用 `.goto(x, y)` 精确控制每个元素的位置，规划画面
- **抬笔落笔**：`.penup()` "飞"着走，`.pendown()` 画着走
- **创意编程**：代码不仅能做计算，还能创作艺术作品

### 下节预告
最后一节项目课——"问答大挑战"！用列表和字典做一个趣味知识问答游戏，10 道题，每题计分，最后给出评语。看看谁是答题王！

### 课后任务
1. 回家继续完善你的城市：加更多元素，让城市更丰富
2. 截图你的城市作品，下次课分享给大家看
3. 想一想：如果让你画一个游乐场（摩天轮、过山车、旋转木马），每个设备怎么用 Turtle 实现？
