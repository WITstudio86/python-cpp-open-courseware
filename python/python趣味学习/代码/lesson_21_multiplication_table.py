# ============================================================
# 第21节：综合练习：乘法表挑战赛
# 学习目标：综合运用 for/while/range，掌握双重循环和格式化打印
# 适合年龄：10-12岁
# ============================================================

print("=" * 50)
print("🎮 第21节：综合练习 —— 乘法表挑战赛")
print("=" * 50)

# ============ 第一部分：理解双重循环 ============
print("\n📝 一、双重循环是怎么工作的？")
print("-" * 30)

print("外层走 1 步，内层走一圈：")
for i in range(1, 4):      # 外层：走 3 步
    for j in range(1, 4):  # 内层：走 3 步
        print(f"  i={i}, j={j}")
    print("  ---")
print("外层 3× 内层 3 = 总共 9 次！")

# ============ 第二部分：用 for 实现乘法表 ============
print("\n📝 二、挑战1：用 for 循环打印九九乘法表")
print("-" * 30)

print("=" * 55)
print("           🌟 九九乘法表（for 版本）🌟")
print("=" * 55)

for i in range(1, 10):        # i 控制行（1到9）
    for j in range(1, i + 1): # j 控制列（第i行有i列）
        # :2d 表示每个结果占2个字符，让表格对齐
        print(f"{j}×{i}={i*j:2d}", end="  ")
    print()  # 一行结束，换行

print("=" * 55)

# ============ 第三部分：用 while 实现乘法表 ============
print("\n📝 三、挑战2：用 while 循环打印九九乘法表")
print("-" * 30)

print("=" * 55)
print("           🌟 九九乘法表（while 版本）🌟")
print("=" * 55)

i = 1
while i <= 9:            # 外层：控制行
    j = 1
    while j <= i:        # 内层：控制列（第i行有i列）
        print(f"{j}×{i}={i*j:2d}", end="  ")
        j += 1           # 内层变量更新
    print()              # 一行结束，换行
    i += 1               # 外层变量更新

print("=" * 55)

# ============ 第四部分：for 和 while 对比 ============
print("\n📝 四、for 和 while 写法对比")
print("-" * 30)

print("""
for 版本的核心：
  for i in range(1, 10):      ← 自动管理 i
      for j in range(1, i+1): ← 自动管理 j
          打印...

while 版本的核心：
  i = 1
  while i <= 9:               ← 手动管理 i
      j = 1
      while j <= i:           ← 手动管理 j
          打印...
          j += 1              ← 手动 +1
      i += 1                  ← 手动 +1

结论：for 更简洁，while 更灵活！
""")

# ============ 练习题1：打印指定行 ============
print("\n" + "=" * 50)
print("✏️ 练习1：打印指定数字的乘法口诀")
print("=" * 50)

n = int(input("请输入一个数字（1-9），我帮你打印它的口诀："))
if n >= 1 and n <= 9:
    print(f"\n{n} 的乘法口诀：")
    for i in range(1, 10):
        print(f"  {n} × {i} = {n * i:2d}")
else:
    print("请输入 1-9 之间的数字哦~")

# ============ 练习题2：倒三角乘法表 ============
print("\n" + "=" * 50)
print("✏️ 练习2：倒三角乘法表（从9×9开始）")
print("=" * 50)

print("=" * 55)
print("        🌟 倒三角九九乘法表 🌟")
print("=" * 55)

# 从 9 到 1 倒着来
for i in range(9, 0, -1):
    for j in range(1, i + 1):
        print(f"{j}×{i}={i*j:2d}", end="  ")
    print()

print("=" * 55)

# ============ 练习题3：自定义乘法表 ============
print("\n" + "=" * 50)
print("✏️ 练习3：自定义大小的乘法表")
print("=" * 50)

size = int(input("请输入乘法表的大小（比如输入 5 就打印 5×5 的表格）："))

print(f"\n{'=' * (size * 8)}")
print(f"    {size}×{size} 乘法表")
print(f"{'=' * (size * 8)}")

for i in range(1, size + 1):
    for j in range(1, i + 1):
        print(f"{j}×{i}={i*j:2d}", end="  ")
    print()

print(f"{'=' * (size * 8)}")

# ============ 综合小挑战 ============
print("\n" + "=" * 50)
print("🏆 综合挑战：花式乘法表")
print("=" * 50)

print("有三种花式乘法表，你想看哪个？")
print("  1 = 标准三角形（左上）")
print("  2 = 倒三角形（右上）")
print("  3 = 完整矩形表格")

choice = input("请选择（1/2/3）：")

if choice == "1":
    print("\n📐 标准三角形（已展示过，再来一遍）：")
    for i in range(1, 10):
        for j in range(1, i + 1):
            print(f"{j}×{i}={i*j:2d}", end="  ")
        print()

elif choice == "2":
    print("\n📐 倒三角形：")
    for i in range(9, 0, -1):
        # 先打印空格，让三角形右对齐
        print("      " * (9 - i), end="")
        for j in range(1, i + 1):
            print(f"{j}×{i}={i*j:2d}", end="  ")
        print()

elif choice == "3":
    print("\n📐 完整矩形表格（9×9全显示）：")
    # 表头
    print("      ", end="")
    for j in range(1, 10):
        print(f"  {j}   ", end="")
    print()
    print("    " + "-" * 54)

    for i in range(1, 10):
        print(f"  {i} |", end="")
        for j in range(1, 10):
            print(f" {i*j:3d} ", end="")
        print()

else:
    print("选择有误，给你看默认的标准三角形：")
    for i in range(1, 10):
        for j in range(1, i + 1):
            print(f"{j}×{i}={i*j:2d}", end="  ")
        print()

# ============ 课程总结 ============
print("\n" + "=" * 50)
print("🎊 第二阶段课程总结")
print("=" * 50)
print("""
你已掌握以下技能：
  ✅ 比较运算符（> < == != >= <=）
  ✅ if / if-else / if-elif-else 条件判断
  ✅ and / or / not 逻辑运算符
  ✅ random 随机数模块
  ✅ for 循环（遍历字符串、列表）
  ✅ range() 生成数字序列
  ✅ 累加器、计数器模式
  ✅ while 循环
  ✅ break 和 continue
  ✅ 双重循环（嵌套循环）
  ✅ 格式化打印

你已经可以写出真正的 Python 程序了！
继续加油，下一阶段会更精彩！🚀
""")

print("🎉" * 15)
print("恭喜完成第21节！第二阶段全部完成！")
print("🎉" * 15)
