# 第 7 课 · 发射！— 打气球

**时长 90 分钟。** 过关标准：空格能射出子弹，打中气球加分，漏掉太多会结束。

---

## ⏱️ 90 分钟流程

| 时间 | 环节 | 做什么 |
|------|------|--------|
| 0–10 分 | 复习 | 口答列表 + for 更新 |
| 10–35 分 | 新知识 + 热身 | 按空格生成一颗子弹往上飞 |
| 35–65 分 | 主游戏 | 打气球 |
| 65–82 分 | 加码 | 不同颜色不同分 |
| 82–90 分 | 学案 + 小结 | 填空、预告双人对打 |

---

## 🎯 本课目标

- 会「按一次键，new 一只海龟，append 进列表」
- 会飞出屏幕后 `hideturtle` + `remove`
- 会两层循环：每颗子弹对每个气球测距离
- **主游戏：打气球**

---

## 📚 新知识

### 7.1 子弹是临时工

```python
def make_bullet():
    shot = turtle.Turtle()
    shot.shape("square")
    shot.penup()
    shot.goto(cannon.xcor(), cannon.ycor())
    bullets.append(shot)
```

炮台是常驻的；子弹打完就消失。

### 7.2 边遍历边删除

```python
for shot in bullets[:]:   # 注意 [:] 拷贝
    shot.forward(12)
    if shot.ycor() > 300:
        shot.hideturtle()
        bullets.remove(shot)
```

对着正在遍历的列表 `remove` 会漏元素。先 `[:]` 拷贝再改原列表。

### 7.3 冷却

```python
if cool <= 0 and len(bullets) < 4:
    make_bullet()
    cool = 10
```

没有冷却，按住空格会变成机关枪，屏幕卡死。课堂上强调「限制同时存在的子弹数」。

---

## 🔥 热身

没有气球。按空格，一颗黄点从玩家头顶飞出屏幕后消失。

**课堂提问：** 为什么写 `for shot in bullets[:]` 而不是 `for shot in bullets`？

---

## 💻 主游戏：打气球

`code/lesson7.py`

5 个气球往下飘，打中重置到天上。漏 8 个结束。

---

## 🚀 加码

给气球一个 `b.points` 属性（红 3 分、蓝 1 分）。打中 `score += balloon.points`。

---

## 🐞 改错

1. 子弹没 `penup`，拖出一条黄线
2. 循环中直接 `bullets.remove` 漏打
3. 没有冷却，卡成幻灯片

---

## ✏️ 小练习

1. 同时最多 2 发子弹
2. 气球变大更容易打
3. 漏掉上限改成 5
4. 热身子弹改成圆形
5. 加码彩色分值

---

## 📋 本课完整代码

`code/lesson7.py`

---

## 📖 下节课

两个人抢一个球。乒乓球。
