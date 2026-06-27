# 第19节：while 循环 —— 不达目的不罢休

## 🎯 教学目标
- 学生能够理解 while 循环和 for 循环的区别和使用场景
- 学生能够正确书写 while 循环语法
- 学生能够避免死循环
- 学生能够独立完成"倒数计时器"项目

## 📝 重点概念
- **while 循环**：当条件成立时，不断重复执行。条件不成立就停止
- **while vs for**：知道循环次数用 for，不知道次数（满足条件才停）用 while
- **死循环**：条件永远成立，循环停不下来。按 Ctrl+C 可以强制停止
- **循环条件**：while 后面跟一个条件表达式，每次循环开始前都会检查
- **条件更新**：循环体里一定要有改变条件的代码，否则就会死循环！

## 📖 讲解内容

### 步骤1：引入（5分钟）

**生活场景对比**：
"for 循环像是：'把这 10 个包子都吃完'——你知道一共 10 个。"

"while 循环像是：'一直吃，直到吃饱为止'——你不知道要吃几个，只知道吃饱了就停。"

**更多例子**：
- 跑步：跑 10 圈（for） vs 跑到累了为止（while）
- 存钱：存 12 个月（for） vs 存够 1000 元为止（while）
- 做作业：做 5 道题（for） vs 做到全对为止（while）

**简洁记忆**：
- for：知道次数
- while：知道条件

### 步骤2：核心讲解（15-20分钟）

**1. while 基本结构（8分钟）**

```python
# while 的基本骨架
while 条件:
    循环体（条件成立时执行）
# 条件不成立时，跳出循环

# 简单例子：从 1 数到 5
i = 1
while i <= 5:
    print(i)
    i += 1  # 重要！改变条件，否则死循环！
# 输出：1 2 3 4 5
```

**执行流程**：
1. 检查 `i <= 5`（1 <= 5 是 True）→ 执行循环体 → i 变成 2
2. 检查 `i <= 5`（2 <= 5 是 True）→ 执行循环体 → i 变成 3
3. ...
4. 检查 `i <= 5`（6 <= 5 是 False）→ 停止循环！

**2. for 和 while 可以互相转换（5分钟）**

```python
# for 版本
for i in range(1, 6):
    print(i)

# while 版本
i = 1
while i <= 5:
    print(i)
    i += 1

# 结果完全一样！
```

**3. while 的典型使用场景（5分钟）**

```python
# 场景1：不知道要循环几次——用户输入决定
answer = ""
while answer != "yes":
    answer = input("你准备好了吗？(输入 yes 继续)：")

# 场景2：倒计时
count = 10
while count > 0:
    print(count)
    count -= 1
print("发射！")

# 场景3：累加到超过某个值
total = 0
i = 1
while total < 100:
    total += i
    i += 1
print(f"加了 {i-1} 个数后，总和 {total} 超过了 100")
```

**4. 避免死循环（2分钟）**

```python
# ❌ 死循环！i 永远不会变
i = 1
while i <= 5:
    print(i)
    # 忘记写 i += 1 了！

# ❌ 死循环！条件永远成立
while True:
    print("停不下来了！")

# ✅ 正确：条件最终会变成 False
i = 1
while i <= 5:
    print(i)
    i += 1  # i 每次+1，最终会 > 5
```

### 步骤3：动手演示（10分钟）

**演示1：倒数计时器**
```python
import time
countdown = 10
print("火箭即将发射！")
while countdown > 0:
    print(f"  {countdown}...")
    time.sleep(1)  # 暂停 1 秒
    countdown -= 1
print("🚀 发射！")
```

**演示2：猜数字（while 版本）**
```python
import random
secret = random.randint(1, 100)
guess = 0  # 初始值不等于 secret
while guess != secret:
    guess = int(input("猜一个数字："))
    if guess > secret:
        print("大了！")
    elif guess < secret:
        print("小了！")
print("猜对了！")
```

## 💻 代码示例

```python
# ======== 第19节：while 循环 ========

# 基本 while 循环
i = 1
while i <= 5:
    print(i)
    i += 1  # 别忘了这行！否则死循环

# 倒数计时器
count = 10
while count > 0:
    print(count)
    count -= 1
print("🚀 发射！")

# 用户输入控制循环
password = ""
while password != "123456":
    password = input("请输入密码：")
print("密码正确！")
```

## ✏️ 课堂练习

1. **基础练习**：用 while 循环打印 1 到 10 的数字
2. **应用练习**：做一个"倒数计时器"——从 10 倒数到 0，最后说"发射！"
3. **挑战练习**：用 while 循环做一个"加法练习器"——不断出加法题，直到答对 5 题为止

## 📋 小结
- while 循环：条件成立就一直执行
- for 知道次数，while 知道条件
- 循环体内一定要改变条件，否则死循环！
- while 特别适合"用户输入控制"和"不确定次数"的场景
- 如果死循环了，按 Ctrl+C 强制停止

**下节预告**：有时候我们需要在循环中途跳出来，或者跳过某一次——break 和 continue 来帮忙！
