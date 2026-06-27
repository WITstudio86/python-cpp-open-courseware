# 第17节：range() —— 循环的好搭档

## 🎯 教学目标
- 学生能够使用 range(n) 生成从 0 到 n-1 的数字序列
- 学生能够使用 range(start, stop) 生成指定范围的数字
- 学生能够使用 range(start, stop, step) 生成带步长的数字序列
- 学生能够理解"左闭右开"的含义

## 📝 重点概念
- **range(n)**：生成 0, 1, 2, ..., n-1（共 n 个数字）。注意不包含 n！
- **range(start, stop)**：生成 start, start+1, ..., stop-1。包含 start，不包含 stop
- **range(start, stop, step)**：以 step 为步长生成数字。step 可以是负数（倒着数）
- **左闭右开**：range 生成的数字，左边端点包含，右边端点不包含。就像数学里的 [start, stop)
- **range 不是列表**：range 是一个"序列生成器"，高效省内存。可以用 list(range(...)) 转成列表查看

## 📖 讲解内容

### 步骤1：引入（5分钟）

"上节课我们学了 for 循环，用它遍历了字符串和列表。但如果我想打印 1 到 100 的所有数字，难道要先写一个 [1, 2, 3, ..., 100] 的列表？那也太累了！"

"这时候，range() 就派上用场了！range 就像一个'数字生成器'，可以方便地生成一系列数字。"

**比喻**：
"range 就像一个自动发牌机——你告诉它从几开始，到几结束，每次加几，它就自动把数字一个个发给你。"

### 步骤2：核心讲解（15-20分钟）

**1. range(n) —— 生成 n 个数字（5分钟）**

```python
# range(5) 生成：0, 1, 2, 3, 4
for i in range(5):
    print(i)
# 输出：0 1 2 3 4

# 注意：不包含 5！左闭右开！
```

**口诀**：range(n) 就是从 0 数到 n-1，一共 n 个数。

**2. range(start, stop) —— 指定起止（5分钟）**

```python
# range(2, 6) 生成：2, 3, 4, 5
for i in range(2, 6):
    print(i)
# 输出：2 3 4 5
# 注意：包含 2（左闭），不包含 6（右开）

# 打印 1 到 10
for i in range(1, 11):
    print(i)  # 1 2 3 ... 10
```

**为什么是 range(1, 11) 而不是 range(1, 10)？**
因为 stop 不包含！要打印 1-10，stop 要写 11！

**3. range(start, stop, step) —— 带步长（5分钟）**

```python
# 打印偶数：0, 2, 4, 6, 8
for i in range(0, 10, 2):
    print(i)

# 打印奇数：1, 3, 5, 7, 9
for i in range(1, 10, 2):
    print(i)

# 倒着数：10, 9, 8, ..., 1
for i in range(10, 0, -1):
    print(i)
```

**step 是负数时**：start > stop，每次减 |step|

**4. 理解"左闭右开"（3分钟）**

用坐标轴讲解：
```
range(2, 7)
     ●—————○
     2         7
     ↑         ↑
    包含     不包含
```

类比：数学课上的区间表示 [2, 7)，左闭右开！

### 步骤3：动手演示（10分钟）

**演示1：打印 1-100**
```python
for i in range(1, 101):
    print(i, end=" ")  # end=" " 让数字横着打印
```

**演示2：打印所有偶数**
```python
# 方法1：用步长
for i in range(2, 101, 2):
    print(i, end=" ")

# 方法2：用 if 判断
for i in range(1, 101):
    if i % 2 == 0:
        print(i, end=" ")
```

**演示3：倒计时**
```python
for i in range(10, 0, -1):
    print(i)
print("发射！🚀")
```

## 💻 代码示例

```python
# ======== 第17节：range() ========

# 1. range(n)：0 到 n-1
print("range(5)：")
for i in range(5):
    print(i, end=" ")  # 0 1 2 3 4
print()

# 2. range(start, stop)：start 到 stop-1
print("\nrange(2, 7)：")
for i in range(2, 7):
    print(i, end=" ")  # 2 3 4 5 6
print()

# 3. range(start, stop, step)：带步长
print("\n0到10的偶数：")
for i in range(0, 11, 2):
    print(i, end=" ")  # 0 2 4 6 8 10
print()

# 4. 倒着数
print("\n倒计时：")
for i in range(10, 0, -1):
    print(i, end=" ")
print("发射！")
```

## ✏️ 课堂练习

1. **基础练习**：用 range() 打印 1 到 20 的所有数字
2. **应用练习**：用 range() 打印 1 到 50 中所有的奇数（提示：step=2）
3. **挑战练习**：用 range() 实现一个"报数游戏"——从 1 数到 30，遇到 3 的倍数就说"过"而不是说数字

## 📋 小结
- range(n)：0 到 n-1，共 n 个数
- range(start, stop)：start 到 stop-1
- range(start, stop, step)：带步长，step 可以是负数
- 左闭右开：包含左边，不包含右边
- range + for 是最佳搭档，处理数字循环超方便！

**下节预告**：学了 for 和 range，下节课我们用循环来做实战项目——求和、乘法表！
