# 第14节：if-elif-else —— 多选一

## 🎯 教学目标
- 学生能够理解 elif 的作用：处理多个条件的分支判断
- 学生能够正确使用 if-elif-else 结构做多选一的判断
- 学生能够独立完成"等级评定系统"项目

## 📝 重点概念
- **elif**：else + if 的缩写，表示"否则如果"。用于在前面的条件不成立时，再判断一个新的条件
- **多选一结构**：if → elif → elif → ... → else，从上到下依次判断，命中一个就停止
- **条件顺序很重要**：条件判断是从上到下的，一旦某个条件成立，后面的就不再判断
- **elif 可以有多个**：根据需要可以写 1 个、2 个、甚至 10 个 elif
- **else 是可选的**：最后一个 else 可以省略（如果不需要"兜底"的话）

## 📖 讲解内容

### 步骤1：引入（5分钟）

**场景引入**：
"上次我们学了 if-else，它能处理两种情况。但生活中很多情况不止两种！"

"比如考试成绩：90分以上是 A，80-89 是 B，70-79 是 C，60-69 是 D，60以下是不及格。这里有五种情况！"

"再比如菜单选择：输入 1 点汉堡，输入 2 点薯条，输入 3 点可乐..."

"这时候，我们就需要 elif 来帮忙！elif 就是'否则如果'的意思。"

**比喻**：
"if-elif-else 就像一个多岔路口："
- "先看第一条路（if）能不能走，能走就走"
- "不能走就看第二条路（elif）能不能走"
- "还不能走就看第三条路（elif）"
- "都走不通就走最后一条（else）"

### 步骤2：核心讲解（15-20分钟）

**1. if-elif-else 基本结构（8分钟）**

```python
score = 85

if score >= 90:
    print("A")
elif score >= 80:
    print("B")
elif score >= 70:
    print("C")
elif score >= 60:
    print("D")
else:
    print("E")
```

**执行逻辑**：
- 先判断 `score >= 90`（85 >= 90？False，跳过）
- 再判断 `score >= 80`（85 >= 80？True！打印 B）
- 后面就不判断了，直接跳过！

**2. 条件顺序的重要性（5分钟）**

```python
# ❌ 错误顺序
score = 95
if score >= 60:
    print("D")      # 95 >= 60 是 True！打印 D 就结束了！
elif score >= 90:
    print("A")      # 永远不会执行到这里！
# 结果：95 分得了 D！太冤了！

# ✅ 正确顺序：从大到小（或从小到大）
score = 95
if score >= 90:
    print("A")      # 先判断最高的
elif score >= 80:
    print("B")
elif score >= 70:
    print("C")
elif score >= 60:
    print("D")
else:
    print("E")
# 结果：A，正确！
```

**强调**：条件要从大到小排列（或者从小到大），否则可能永远走不到某个分支！

**3. elif 可以有多个（3分钟）**

```python
# 菜单选择
choice = 3

if choice == 1:
    print("你选了🍔 汉堡")
elif choice == 2:
    print("你选了🍕 披萨")
elif choice == 3:
    print("你选了🍟 薯条")
elif choice == 4:
    print("你选了🥤 可乐")
else:
    print("没有这个选项哦~")
```

**4. else 可以省略（2分钟）**

```python
# 不需要兜底的情况
weather = "晴天"
if weather == "晴天":
    print("去公园玩！")
elif weather == "阴天":
    print("去图书馆！")
elif weather == "雨天":
    print("在家看书！")
# 如果 weather 是"下雪"？什么都不输出，也没关系
```

### 步骤3：动手演示（10分钟）

**演示1：等级评定系统**

```python
score = int(input("请输入你的分数（0-100）："))

if score >= 90:
    grade = "A"
    comment = "太厉害了，学霸！🌟"
elif score >= 80:
    grade = "B"
    comment = "很不错，继续保持！👍"
elif score >= 70:
    grade = "C"
    comment = "还可以，争取更好！💪"
elif score >= 60:
    grade = "D"
    comment = "刚刚及格，要加油哦！📚"
else:
    grade = "E"
    comment = "不及格，下次努力！🔥"

print(f"你的等级是：{grade}")
print(comment)
```

**演示2：BMI 体重判断**

```python
height = float(input("请输入身高（米）："))
weight = float(input("请输入体重（公斤）："))
bmi = weight / (height * height)
print(f"你的 BMI 是：{bmi:.1f}")

if bmi < 18.5:
    print("偏瘦，要多吃点哦~")
elif bmi < 24:
    print("正常，保持住！")
elif bmi < 28:
    print("偏重，注意饮食~")
else:
    print("肥胖，要运动了！")
```

## 💻 代码示例

```python
# ======== 第14节：if-elif-else ========

score = 85

# 多选一：从上到下依次判断
if score >= 90:
    print("等级：A")
elif score >= 80:
    print("等级：B")
elif score >= 70:
    print("等级：C")
elif score >= 60:
    print("等级：D")
else:
    print("等级：E")

# 注意：85 >= 80 成立，打印 B；后面的不再判断
```

## ✏️ 课堂练习

1. **基础练习**：写一个程序，根据年龄判断人生阶段——0-6岁（幼儿），7-12岁（儿童），13-17岁（青少年），18岁以上（成人）
2. **改造练习**：把上节课的"周末判断器"改成用 if-elif-else，让它可以区分：周一到周五（工作日）、周六（周末）、周日（周末）
3. **挑战练习**：设计一个"智能推荐"——根据用户输入的心情（开心/难过/无聊/生气），推荐不同的活动

## 📋 小结
- elif = else + if，表示"否则如果"
- if-elif-else 从上到下判断，命中一个就停止
- 条件顺序很重要！要从大到小排列
- elif 可以有任意多个，else 可以省略
- 多选一结构让程序能做更复杂的判断

**下节预告**：学完了条件判断的所有知识，下节课我们做一个综合项目——猜数字游戏！
