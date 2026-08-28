# 第 1 课 · 海龟登场 — 窗口、画笔、点击盖章

**时长 90 分钟。** 过关标准：主游戏「彩虹点击画家」窗口能打开，点击画面会出现彩色小海龟。

---

## ⏱️ 90 分钟流程

| 时间 | 环节 | 做什么 |
|------|------|--------|
| 0–15 分 | 开场 | turtle 是什么、怎么运行 `.py` 弹出窗口 |
| 15–35 分 | 新知识 + 热身 | 窗口、海龟、前进、转弯、盖章 |
| 35–65 分 | 主游戏 | 点击画家：点哪里盖哪里 |
| 65–82 分 | 加码 | 点击一次盖一朵花（转一圈 stamp） |
| 82–90 分 | 学案 + 小结 | 填空、预告方向键 |

---

## 🎯 本课目标

- 知道 `turtle` 是 Python 自带的画画/小游戏工具
- 会创建窗口 `Screen` 和海龟 `Turtle`
- 会 `forward` / `left` / `color` / `stamp` / `onscreenclick`
- **主游戏：彩虹点击画家**
- **加码：点击改成一朵花**

---

## 📚 新知识

### 1.1 海龟在哪儿

```python
import turtle

screen = turtle.Screen()
screen.setup(800, 600)
screen.title("我的窗口")
screen.bgcolor("black")
```

`Screen` 是画布，`Turtle` 是画笔。两个都要创建。

### 1.2 让海龟走一步

```python
t = turtle.Turtle()
t.shape("turtle")
t.color("lime")
t.forward(100)
t.left(90)
```

连走 4 次 `forward` + `left(90)` 就是正方形。这是热身。

### 1.3 点击和盖章

```python
t.penup()          # 抬笔，移动不画线
t.stamp()          # 在当前位置盖一个海龟章

def paint(x, y):
    t.goto(x, y)
    t.stamp()

screen.onscreenclick(paint)
turtle.done()      # 窗口保持开着
```

`onscreenclick` 会把鼠标坐标传进函数。最后一定要 `turtle.done()`，否则窗口闪一下就关。

---

## 🔥 热身

自己打：海龟走一个正方形，再换颜色走一个三角形（转 120 度，走 3 次）。

**课堂提问：** `penup()` 和 `pendown()` 有什么区别？

---

## 💻 主游戏：彩虹点击画家

完整代码见 `code/lesson1.py`。

- 点击 → `goto` + `stamp`
- 空格 → 换调色盘里的下一种颜色
- C → 清屏

让学生把调色盘改成自己喜欢的颜色。

---

## 🚀 加码

点击时不要只盖一章，而是：

```python
for _ in range(8):
    painter.stamp()
    painter.left(45)
```

一朵 8 瓣的小花。

---

## 🐞 改错

1. `Turtle.forward(100)`（应该先创建对象）
2. 忘了 `turtle.done()`，窗口闪退
3. `onscreenclick(paint())` —— 括号会立刻调用，应传函数名

---

## ✏️ 小练习

1. 把背景改成深蓝
2. 海龟形状改成 `"circle"`
3. 调色盘加一种自己的颜色
4. 加码花瓣改成 12 瓣
5. 猜：`left(90)` 四次后朝哪

---

## 📋 本课完整代码

`code/lesson1.py`

---

## 📖 下节课

方向键开车。海龟开始听键盘的话。
