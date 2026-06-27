# ============================================================
# 第16节：for 循环初步
# 学习目标：掌握 for 循环语法，遍历字符串和列表
# 适合年龄：10-12岁
# ============================================================

print("=" * 50)
print("🎮 第16节：for 循环初步")
print("=" * 50)

# ============ 第一部分：认识 for 循环 ============
print("\n📝 一、for 循环的基本结构")
print("-" * 30)
print("""
for 变量 in 序列:
    循环体（要重复执行的代码）

就像点名一样，一个个地取出来处理！
""")

# ============ 第二部分：遍历字符串 ============
print("\n📝 二、遍历字符串 —— 逐个打印每个字")
print("-" * 30)

name = "小明爱编程"
print(f"名字：{name}")
print("逐个打印：")
for char in name:
    print(f"  → {char}")

# 试试其他字符串
print()
word = "Hello"
print(f"单词：{word}")
for letter in word:
    print(f"  字母：{letter}")

# ============ 第三部分：遍历列表 ============
print("\n📝 三、遍历列表 —— 逐个处理每个元素")
print("-" * 30)

# 水果列表
fruits = ["苹果 🍎", "香蕉 🍌", "橘子 🍊", "葡萄 🍇", "西瓜 🍉"]
print("我喜欢的水果：")
for fruit in fruits:
    print(f"  我喜欢吃 {fruit}")

# 数字列表
print()
scores = [95, 88, 76, 92, 100, 58, 83]
print("成绩单：")
for score in scores:
    if score >= 90:
        star = "🌟 优秀！"
    elif score >= 60:
        star = "✅ 及格"
    else:
        star = "❌ 不及格"
    print(f"  {score} 分 → {star}")

# ============ 第四部分：带编号的遍历 ============
print("\n📝 四、给遍历加上编号")
print("-" * 30)

friends = ["小明", "小红", "小刚", "小丽", "小华"]
print("我的朋友列表：")
num = 1
for friend in friends:
    print(f"  {num}. {friend}")
    num += 1

# ============ 第五部分：循环体里可以做任何事 ============
print("\n📝 五、循环体里的操作")
print("-" * 30)

# 统计
numbers = [15, 8, 22, 9, 30, 4, 17]
print(f"数字列表：{numbers}")

# 找出大于10的数
print("大于10的数：")
for n in numbers:
    if n > 10:
        print(f"  {n}", end="")
print()

# 计算总和
total = 0
for n in numbers:
    total += n
print(f"所有数字的总和：{total}")

# ============ 练习题1：打印名字 ============
print("\n" + "=" * 50)
print("✏️ 练习1：逐个打印你的名字")
print("=" * 50)

your_name = input("请输入你的名字：")
print(f"'{your_name}' 的每个字是：")
for zi in your_name:
    print(f"  ✨ {zi}")

# ============ 练习题2：颜色列表 ============
print("\n" + "=" * 50)
print("✏️ 练习2：输出喜欢的颜色")
print("=" * 50)

colors = ["红色", "蓝色", "绿色", "黄色", "紫色", "粉色"]
for color in colors:
    print(f"  {color} 是我喜欢的颜色！")

# ============ 练习题3：找偶数 ============
print("\n" + "=" * 50)
print("✏️ 练习3：找出列表中的偶数")
print("=" * 50)

nums = [11, 24, 37, 42, 55, 68, 73, 86, 99]
print(f"数字列表：{nums}")
print("其中的偶数有：")
for n in nums:
    if n % 2 == 0:
        print(f"  {n} ✓")

# ============ 综合小挑战 ============
print("\n" + "=" * 50)
print("🏆 综合挑战：制作购物清单")
print("=" * 50)

# 创建一个购物清单
shopping_list = ["牛奶", "面包", "鸡蛋", "苹果", "薯片"]

print("🛒 今天的购物清单：")
for i, item in enumerate(shopping_list, 1):
    print(f"  {i}. {item}")

# 计算总价（模拟）
prices = [6, 8, 12, 15, 5]
total = 0
print("\n💰 价格明细：")
for i in range(len(shopping_list)):
    print(f"  {shopping_list[i]}：{prices[i]} 元")
    total += prices[i]
print(f"  总计：{total} 元")

# 检查预算
budget = 50
print(f"\n预算：{budget} 元")
if total <= budget:
    print(f"✅ 预算够用！还能剩 {budget - total} 元")
else:
    print(f"❌ 超出预算 {total - budget} 元，需要取舍一下~")

print("\n" + "🎉" * 10)
print("恭喜完成第16节的学习！学会 for 循环了！")
print("🎉" * 10)
