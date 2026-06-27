# ============================================================
# 第17节：range() —— 循环的好搭档
# 学习目标：掌握 range() 的三种用法和"左闭右开"概念
# 适合年龄：10-12岁
# ============================================================

print("=" * 50)
print("🎮 第17节：range() —— 循环的好搭档")
print("=" * 50)

# ============ 第一部分：range(n) ============
print("\n📝 一、range(n) —— 从 0 到 n-1")
print("-" * 30)

print("range(5) 生成：", end="")
for i in range(5):
    print(i, end=" ")
print()
# 输出：0 1 2 3 4（注意：没有5！）

# 直观展示
n = 5
print(f"\nrange({n}) 生成的数字：{list(range(n))}")
print(f"一共 {n} 个数字（0 到 {n-1}）")

# ============ 第二部分：range(start, stop) ============
print("\n📝 二、range(start, stop) —— 指定开始和结束")
print("-" * 30)

print("range(2, 7) 生成：", end="")
for i in range(2, 7):
    print(i, end=" ")
print()
# 输出：2 3 4 5 6

# ⚠️ 重点理解：左闭右开！
print("\n⚠️ 重点：左闭右开！")
print("  range(2, 7)：包含 2 ✓，不包含 7 ✗")
print(f"  结果：{list(range(2, 7))}")

# 打印 1 到 10
print("\n打印 1 到 10：")
for i in range(1, 11):  # 注意：要写 11，不是 10！
    print(i, end=" ")
print()

# ============ 第三部分：range(start, stop, step) ============
print("\n📝 三、range(start, stop, step) —— 带步长")
print("-" * 30)

# 步长为 2
print("range(0, 10, 2) 生成（偶数）：", end="")
for i in range(0, 10, 2):
    print(i, end=" ")
print()

# 步长为 3
print("range(0, 20, 3) 生成（3的倍数）：", end="")
for i in range(0, 20, 3):
    print(i, end=" ")
print()

# 步长为负数（倒着数）
print("\nrange(10, 0, -1) 生成（倒计时）：", end="")
for i in range(10, 0, -1):
    print(i, end=" ")
print()

# ============ 第四部分：三种用法的汇总对比 ============
print("\n📝 四、range 三种用法汇总")
print("-" * 30)

print("用法1：range(n)          →  0, 1, 2, ..., n-1")
print(f"  例如 range(4) = {list(range(4))}")

print("用法2：range(start, stop) →  start, start+1, ..., stop-1")
print(f"  例如 range(3, 8) = {list(range(3, 8))}")

print("用法3：range(start, stop, step) →  带步长")
print(f"  例如 range(1, 10, 2) = {list(range(1, 10, 2))}")

# ============ 第五部分：实战演示 ============
print("\n📝 五、实战演示")
print("-" * 30)

# 演示1：打印 1-50 的所有奇数
print("1-50 的奇数：")
for i in range(1, 51, 2):
    print(i, end=" ")
print()

# 演示2：九九乘法表的一行
print("\n7 的乘法口诀：")
for i in range(1, 10):
    print(f"7 × {i} = {7 * i}")

# 演示3：求 1+2+...+100 的和
total = 0
for i in range(1, 101):
    total += i
print(f"\n1+2+...+100 = {total}")

# ============ 练习题1：打印 1-20 ============
print("\n" + "=" * 50)
print("✏️ 练习1：用 range 打印 1 到 20")
print("=" * 50)

print("1 到 20 的所有数字：")
for i in range(1, 21):
    print(i, end=" ")
print()

# ============ 练习题2：打印奇数 ============
print("\n" + "=" * 50)
print("✏️ 练习2：打印 1 到 50 的所有奇数")
print("=" * 50)

print("1 到 50 的奇数：")
# 方法1：用步长
for i in range(1, 51, 2):
    print(i, end=" ")
print()

# 方法2：用 if 判断
print("\n（方法2：用if判断）")
for i in range(1, 51):
    if i % 2 == 1:
        print(i, end=" ")
print()

# ============ 练习题3：报数游戏 ============
print("\n" + "=" * 50)
print("✏️ 练习3：报数游戏（3的倍数说'过'）")
print("=" * 50)

print("从1数到30，3的倍数说'过'：")
for i in range(1, 31):
    if i % 3 == 0:
        print("过", end=" ")
    else:
        print(i, end=" ")
print()

# ============ 综合小挑战 ============
print("\n" + "=" * 50)
print("🏆 综合挑战：灵活运用 range")
print("=" * 50)

# 挑战1：倒着打印 100 到 1
print("倒着打印 100 到 1（每10个换行）：")
count = 0
for i in range(100, 0, -1):
    print(f"{i:3d}", end=" ")  # :3d 表示占3个字符宽度
    count += 1
    if count % 10 == 0:
        print()
print()

# 挑战2：打印水仙花数（100-999中，各位数字立方和等于本身的数）
print("\n水仙花数（100-999）：")
for num in range(100, 1000):
    hundreds = num // 100        # 百位
    tens = (num // 10) % 10      # 十位
    ones = num % 10              # 个位
    if hundreds**3 + tens**3 + ones**3 == num:
        print(f"  {num} = {hundreds}³ + {tens}³ + {ones}³")

# 挑战3：打印乘法口诀（单行版）
print("\n请输入一个数字，我来帮你打印它的乘法口诀：")
n = int(input("请输入数字（1-9）："))
if n >= 1 and n <= 9:
    print(f"\n{n} 的乘法口诀：")
    for i in range(1, 10):
        print(f"  {n} × {i} = {n * i}")
else:
    print("请输入 1-9 之间的数字哦~")

print("\n" + "🎉" * 10)
print("恭喜完成第17节的学习！range() 真好用！")
print("🎉" * 10)
