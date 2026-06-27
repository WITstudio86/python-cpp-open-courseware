# 第19节：while 循环 —— 不达目的不罢休

## 🎯 教学目标
- 学生理解 while 和 for 的区别
- 学生掌握 while 循环的语法
- 学生知道如何避免死循环
- 学生能选择合适的循环类型

## 📝 重点概念
- **while 循环**：只要条件为 True，就一直循环
- **循环条件**：每次循环前检查，True 就继续，False 就退出
- **死循环**：条件永远为 True 导致程序永远停不下来
- **for vs while**：知道次数用 for，满足条件才停用 while

## 📖 讲解内容

### 步骤1：引入 —— for 做不到的事（5分钟）

> "如果让你输入密码，输错了就重试——你不知道用户要试几次！for 循环需要提前知道次数，这种情况就得靠 while！"

### 步骤2：while 基本语法（10分钟）

```python
# 格式
while 条件:
    循环体

# 示例：数到 5
count = 1
while count <= 5:
    print("第", count, "次")
    count += 1         # ⚠️ 一定要改条件！否则死循环！
```

### 步骤3：for vs while 对比（8分钟）

```python
# for：你知道要重复 5 次
for i in range(5):
    print(i)

# while：你不知道用户什么时候猜对
import random
secret = random.randint(1, 100)
guess = 0
while guess != secret:
    guess = int(input("猜数字："))
    if guess < secret:
        print("小了！")
    elif guess > secret:
        print("大了！")
print("猜对了！")
```

### 步骤4：避免死循环（5分钟）

```python
# ❌ 死循环！count 永远不会 >= 10
count = 0
while count < 10:
    print(count)
    # 忘了 count += 1 ！！！

# ⚠️ 如果死循环了，按 Ctrl+C 停止！
```

## 💻 代码示例

见 `./代码/lesson_19_while.py`

## ✏️ 课堂练习

1. **基础练习**：用 while 打印 1-50 的所有偶数。
2. **进阶练习**：做一个"倒数计时器"——从 10 倒数到 0，然后打印"🚀 发射！"。
3. **挑战练习**：做一个"密码验证系统"——正确密码是"python123"，最多 3 次机会，输对就退出。

## 📋 小结
- ✅ while 条件为 True 就循环
- ✅ 循环体内必须改变条件，避免死循环
- ✅ 知道次数用 for，不知道次数用 while
- ✅ Ctrl+C 可以强制停止死循环

> 下节预告：break 和 continue —— 更好地控制循环！
