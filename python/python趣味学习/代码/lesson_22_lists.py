# ============================================================
# 第22节：列表 —— 一个装很多东西的盒子
# 适合：10-12 岁 Python 初学者
# ============================================================

# 一、创建列表
# 列表用方括号 []，元素之间用逗号隔开
print("=== 一、创建列表 ===")

# 字符串列表 —— 像一个水果篮
fruits = ["苹果", "香蕉", "橘子", "葡萄", "西瓜"]
print("水果列表：", fruits)

# 数字列表 —— 像一个成绩单
scores = [95, 88, 92, 100, 76]
print("成绩列表：", scores)

# 混合列表 —— 可以放不同类型的东西
student = ["小明", 12, 155.5]
print("学生信息：", student)

# 空列表 —— 先准备一个空盒子，后面再装东西
todo = []
print("空列表：", todo)

# 二、访问元素：用索引
# 索引从 0 开始！0 是第一个，-1 是最后一个
print("\n=== 二、访问元素 ===")

fruits = ["苹果", "香蕉", "橘子", "葡萄", "西瓜"]
# 正数索引:  0      1      2      3      4
# 负数索引:  -5     -4     -3     -2     -1

print("第一个水果（索引 0）：", fruits[0])
print("第二个水果（索引 1）：", fruits[1])
print("第三个水果（索引 2）：", fruits[2])
print("最后一个水果（索引 -1）：", fruits[-1])
print("倒数第二个（索引 -2）：", fruits[-2])

# 三、列表长度 len()
print("\n=== 三、列表长度 len() ===")

print("水果列表有", len(fruits), "个元素")
print("成绩列表有", len(scores), "个元素")
print("空列表有", len(todo), "个元素")

# 注意：长度是 5，索引范围是 0 到 4
# 最后一个元素的索引是 len(列表) - 1
print("最后一个水果：", fruits[len(fruits) - 1])

# 四、列表切片 —— 取一段
print("\n=== 四、列表切片 ===")

print("前3个水果 fruits[0:3]：", fruits[0:3])
print("第2到第4个 fruits[1:4]：", fruits[1:4])
print("从第3个到最后 fruits[2:]：", fruits[2:])
print("前两个 fruits[:2]：", fruits[:2])

# 五、遍历列表
print("\n=== 五、遍历列表 ===")

shopping = ["牛奶", "面包", "鸡蛋", "苹果", "香蕉"]
print("我的购物清单：")
for item in shopping:
    print("  📦", item)

# 带序号的遍历
print("\n带序号的购物清单：")
for i, item in enumerate(shopping, 1):
    print(f"  {i}. {item}")

# ============================================================
# 练习题
# ============================================================

print("\n" + "=" * 40)
print("  课堂练习")
print("=" * 40)

# 练习1：创建你最喜欢的5种食物列表，打印第一个和最后一个
print("\n【练习1】我的美食列表：")
my_foods = ["披萨", "汉堡", "寿司", "冰淇淋", "巧克力"]
print("第一个喜欢的食物：", my_foods[0])
print("最后一个喜欢的食物：", my_foods[-1])
print("一共", len(my_foods), "种食物")

# 练习2：创建一个同学名单，用索引和 len 操作
print("\n【练习2】班级同学：")
classmates = ["小明", "小红", "小刚", "小丽", "小华"]
print("第一个同学：", classmates[0])
print("最后一个同学：", classmates[-1])
print("班上共有", len(classmates), "个同学")
print("前两个同学：", classmates[:2])
print("后两个同学：", classmates[-2:])

# 练习3：让用户输入3个喜欢的动物，存到列表中
print("\n【练习3】动物收集：")
animals = []
for i in range(3):
    animal = input(f"请输入第{i+1}个喜欢的动物：")
    animals.append(animal)
print("你喜欢的动物有：", animals)
print("一共", len(animals), "种动物")

# ============================================================
# 综合小挑战：我的收藏夹
# ============================================================

print("\n" + "=" * 40)
print("  综合挑战：我的收藏夹")
print("=" * 40)

# 创建一个包含多种信息的列表
my_collection = ["Python", "数学", 100, "蓝色", "编程"]

print("我的收藏夹里有：", my_collection)
print("一共有", len(my_collection), "项收藏")

# 用索引访问每项
labels = ["最喜欢的语言", "最喜欢的科目", "最高分", "最喜欢的颜色", "最大的爱好"]
for i in range(len(my_collection)):
    print(f"  {labels[i]}：{my_collection[i]}")

# 切片挑战
print("\n前三项收藏：", my_collection[:3])
print("后两项收藏：", my_collection[-2:])

# 给自己出题：猜猜下面会输出什么？
# fruits = ["A", "B", "C", "D", "E"]
# print(fruits[1:4])    →
# print(fruits[-3:])    →
# print(fruits[:])      →

print("\n✅ 第22节完成！")
