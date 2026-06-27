# 第20节：break 和 continue

## 🎯 教学目标
- 学生能够理解 break 的作用：立即跳出整个循环
- 学生能够理解 continue 的作用：跳过本次循环，继续下一次
- 学生能够区分 break 和 continue 的使用场景
- 学生能够独立完成"密码验证"和"跳过3的倍数"项目

## 📝 重点概念
- **break**：立即终止整个循环，执行循环后面的代码。就像"不玩了，退出！"
- **continue**：跳过本次循环剩余的代码，直接开始下一次循环。就像"这轮跳过，下一轮！"
- **区别记忆**：break 是"下课了，全体解散"；continue 是"你留下，其他人继续"
- **适用场景**：break 用于"找到就停"；continue 用于"不符合条件就跳过"
- **break 和 continue 在 for 和 while 中都能用**

## 📖 讲解内容

### 步骤1：引入（5分钟）

**故事比喻**：

"想象你在翻书包找钥匙："
- "一本一本地翻书，翻到钥匙就停止——这就是 break（找到目标就停）"
- "翻到不相关的文具盒就跳过，继续翻别的——这就是 continue（跳过不相关的）"

"再比如体育课排队："
- "老师说'解散！'——所有人都停了，这就是 break"
- "老师说'没穿运动鞋的出列'——部分人退出，其他人继续——这也类似 continue"

### 步骤2：核心讲解（15-20分钟）

**1. break —— 跳出循环（8分钟）**

```python
# 找第一个能被 7 整除的数
for i in range(1, 100):
    if i % 7 == 0:
        print(f"找到了！{i} 是第一个能被 7 整除的数")
        break  # 找到就停，不用继续找了
# 输出：找到了！7 是第一个能被 7 整除的数

# 如果没有 break，会打印所有 7 的倍数
```

**break 在 while 中的使用**：

```python
# 密码验证（最多3次机会）
password = "hello123"
chances = 3

while chances > 0:
    user_input = input(f"请输入密码（还剩{chances}次）：")
    if user_input == password:
        print("密码正确！欢迎！")
        break  # 对了就跳出
    chances -= 1
    if chances > 0:
        print("密码错误！再试一次~")

if chances == 0:
    print("3次机会用完，账户已锁定！")
```

**2. continue —— 跳过本次（7分钟）**

```python
# 打印 1-10，但跳过 3 的倍数
for i in range(1, 11):
    if i % 3 == 0:
        continue  # 跳过本次，不执行下面的 print
    print(i)
# 输出：1 2 4 5 7 8 10
# 注意：3、6、9 被跳过了
```

**continue 的执行流程**：
1. 遇到 continue
2. 跳过循环体中 continue 后面的所有代码
3. 直接进入下一次循环

**3. break vs continue 对比（3分钟）**

```python
# break：找到第一个偶数就停
for i in [1, 3, 5, 6, 7, 8]:
    if i % 2 == 0:
        print(f"找到偶数 {i}，停止！")
        break
# 输出：找到偶数 6，停止！
# 不会继续处理 7 和 8

# continue：只打印偶数，奇数跳过
for i in [1, 3, 5, 6, 7, 8]:
    if i % 2 != 0:
        continue
    print(f"偶数：{i}")
# 输出：偶数：6  偶数：8
```

### 步骤3：动手演示（10分钟）

**演示1：找宝藏**
```python
boxes = ["空", "空", "空", "💎宝藏", "空", "空"]
for i, box in enumerate(boxes, 1):
    print(f"打开第{i}个箱子...")
    if box == "💎宝藏":
        print(f"找到宝藏了！在第{i}个箱子里！")
        break
    print("  是空的，继续找...")
```

**演示2：点名跳过请假同学**
```python
students = ["小明", "小红（请假）", "小刚", "小丽（请假）", "小华"]
for student in students:
    if "请假" in student:
        print(f"  {student} → 跳过")
        continue
    print(f"  {student} → 到！")
```

## 💻 代码示例

```python
# ======== 第20节：break 和 continue ========

# break 示例：在列表中找到第一个大于 50 的数
numbers = [12, 35, 28, 67, 45, 82, 19]
for n in numbers:
    if n > 50:
        print(f"找到了！第一个大于 50 的数是 {n}")
        break

# continue 示例：只打印大于 50 的数
for n in numbers:
    if n <= 50:
        continue
    print(f"大于 50 的数：{n}")
```

## ✏️ 课堂练习

1. **基础练习**：用 break 在 1-100 中找到第一个既能被 3 整除又能被 5 整除的数
2. **应用练习**：用 continue 打印 1-20 中所有不是 4 的倍数的数字
3. **挑战练习**：完善密码验证系统——最多 3 次机会，输对了用 break 退出，输错了提示剩余次数

## 📋 小结
- break = 立即跳出整个循环（不玩了！）
- continue = 跳过本次，继续下一次（这轮跳过！）
- break 常用于"找到目标就停"
- continue 常用于"不符合条件就跳过"
- 两者在 for 和 while 中都能使用

**下节预告**：综合运用 for、while、break、continue，来一场乘法表挑战赛！
