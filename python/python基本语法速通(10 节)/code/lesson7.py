# ============================================
# 第 7 课  重复的力量
# 结构：热身 → 主项目 → 加码
# 知识：for、range、嵌套、end、求和、遍历字符串
# ============================================

print("######## 热身 A：range 三种写法 ########")
print("range(5)        依次是：", end=" ")
for i in range(5):
    print(i, end=" ")
print()
print("range(1, 6)     依次是：", end=" ")
for i in range(1, 6):
    print(i, end=" ")
print()
print("range(2, 11, 2) 依次是：", end=" ")
for i in range(2, 11, 2):
    print(i, end=" ")
print()
print("口诀：含头不含尾。")
print()

print("######## 热身 B：1 加到 n ########")
n = int(input("热身：把 1 加到几？ "))
s = 0
for i in range(1, n + 1):
    s = s + i
print(f"1 + 2 + ... + {n} = {s}")
print()

print("######## 热身 C：把你的名字拆开打印 ########")
name = input("输入你的名字：")
for ch in name:
    print(f"【{ch}】", end=" ")
print()
print()
print("—— 热身结束，下面做主项目 ——")
print()

# ============================================
# 主项目：图案打印机（5 种图案）
# ============================================
print("######## 主项目：图案打印机 ########")
print("1 实心矩形")
print("2 直角三角形")
print("3 倒三角形")
print("4 空心矩形")
print("5 九九乘法表")
print()
choice = input("请选择 1-5：")
print()

if choice == "1":
    rows = int(input("行数："))
    cols = int(input("列数："))
    print("【实心矩形】")
    for i in range(rows):
        print("★" * cols)

elif choice == "2":
    n = int(input("高度："))
    print("【直角三角形】")
    for i in range(1, n + 1):
        print("▲" * i)

elif choice == "3":
    n = int(input("高度："))
    print("【倒三角形】")
    for i in range(n, 0, -1):     # 步长 -1，从 n 降到 1
        print("▼" * i)

elif choice == "4":
    rows = int(input("行数："))
    cols = int(input("列数："))
    print("【空心矩形】")
    for i in range(rows):
        for j in range(cols):
            # 第一行、最后一行、第一列、最后一列打实心
            if i == 0 or i == rows - 1 or j == 0 or j == cols - 1:
                print("★", end="")
            else:
                print("  ", end="")  # 两个空格，宽度和 ★ 接近
        print()

elif choice == "5":
    print("【九九乘法表】")
    for i in range(1, 10):
        for j in range(1, i + 1):
            print(f"{j}×{i}={i * j:2d}", end="  ")
        print()
else:
    print("没有这个选项。")

print()
print("—— 主项目结束，下面是加码（选做）——")
print()

# ============================================
# 加码 1：等腰三角形（前面补空格）
# ============================================
print("######## 加码 1：等腰三角形 ########")
h = int(input("等腰三角形高度："))
for i in range(1, h + 1):
    spaces = h - i
    stars = 2 * i - 1
    print(" " * spaces + "▲" * stars)
print()

# ============================================
# 加码 2：阶乘（不用函数，只用 for）
# ============================================
print("######## 加码 2：阶乘 ########")
m = int(input("计算 m! ，m = "))
prod = 1
for i in range(1, m + 1):
    prod = prod * i
print(f"{m}! = {prod}")
print()
print("小知识：range(5) 不含 5；倒着数用 range(n, 0, -1)。")
