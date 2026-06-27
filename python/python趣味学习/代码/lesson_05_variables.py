# ============================================================
# 第5节：变量 —— 贴标签的盒子
# 主题：理解变量的概念，学习变量命名和使用
# ============================================================

# ===== 1. 什么是变量？=====
print("===== 1. 创建变量 =====")

# 变量就像贴了标签的盒子
# = 号是把右边的数据"放进去"
# 从右往左读：score "获得" 95
score = 95
name = "小明"
height = 1.45
is_student = True

print("姓名：", name)
print("分数：", score)
print("身高：", height, "米")
print("是学生吗？", is_student)

# 用 type() 看盒子里的数据类型
print("\n--- 查看类型 ---")
print("name 的类型：", type(name))       # str（字符串）
print("score 的类型：", type(score))     # int（整数）
print("height 的类型：", type(height))   # float（小数）
print("is_student 的类型：", type(is_student))  # bool（真假）

# ===== 2. 变量可以修改 =====
print("\n===== 2. 修改变量 =====")

my_number = 100
print("原来的值：", my_number)

my_number = 200      # 把盒子里的东西换掉！
print("修改后的值：", my_number)

my_number = "你好"    # 甚至可以换成完全不同的类型
print("又改了：", my_number, "（类型：", type(my_number), "）")

# --- 一年过去了 ---
print("\n--- 一年后 ---")
age = 10
print("今年：", age, "岁")
age = age + 1         # age + 1 = 11，然后把 11 放回 age 盒子
print("明年：", age, "岁")

# ===== 3. 变量名规则 =====
print("\n===== 3. 变量名规则 =====")

# ✓ 正确的变量名
player_name = "小红"    # 字母 + 下划线
score1 = 90             # 字母 + 数字
_height = 175           # 下划线开头也可以
中文变量名 = "可以但有"   # Python 3 支持中文，但不推荐

print("正确示范：", player_name, score1, _height)

# ✗ 错误的变量名（下面这些都会报错，所以注释掉了）：
# 1player = "小明"      # 不能以数字开头
# my-name = "小明"      # 不能有减号
# my name = "小明"      # 不能有空格
# class = "小明"        # class 是 Python 关键字！不能用！
# print = "小明"        # print 也是关键字 / 内置函数名！

# ===== 4. 好名字 vs 坏名字 =====
print("\n===== 4. 好名字 vs 坏名字 =====")

# 坏名字：看不出来是干什么的
a = "小明"              # a 是什么？看不懂
bbb = 10               # bbb 是什么？更看不懂
x1 = 95.5              # 完全不知道存的是什么

# 好名字：一看就知道
student_name = "小明"           # 哦，学生的名字
student_age = 10               # 哦，学生的年龄
student_score = 95.5           # 哦，学生的分数
number_of_students = 45        # 哦，学生人数

print("好名字示范：")
print("姓名：", student_name)
print("年龄：", student_age)
print("分数：", student_score)
print("班级人数：", number_of_students)

# ===== 5. 变量运算 =====
print("\n===== 5. 变量之间也能运算 =====")

apples = 5
bananas = 3
total_fruits = apples + bananas      # 5 + 3 = 8
print("水果总数：", total_fruits)

price = 12        # 单价
quantity = 4      # 数量
total = price * quantity             # 12 * 4 = 48
print("总价：", total, "元")

# ===== 6. Python 关键字 —— 不能用作变量名！=====
print("\n===== 6. Python 关键字 =====")

import keyword
kw_list = keyword.kwlist
print("Python 一共有", len(kw_list), "个关键字")
print("前10个：", kw_list[:10])
print("常见关键字：if, else, for, while, def, class, True, False, None...")
print("这些单词都不能用作变量名哦！")

# ===== 7. 变量交换 =====
print("\n===== 7. 魔术：交换变量 =====")

a = "苹果"
b = "香蕉"
print("交换前：a =", a, ", b =", b)

# 方法一：用临时变量（经典方法）
temp = a    # 把 a 暂存到 temp
a = b       # 把 b 放到 a
b = temp    # 把暂存的 temp 放到 b
print("交换后：a =", a, ", b =", b)

# 方法二：Python 独门绝技（超简洁！）
a, b = b, a   # 一行搞定！
print("再交换：a =", a, ", b =", b)

# ===== 8. 变量实战：成绩统计 =====
print("\n===== 8. 实战：成绩统计 =====")

chinese = 90
math = 85
english = 92
science = 88

total_score = chinese + math + english + science
average_score = total_score / 4

print("语文：", chinese)
print("数学：", math)
print("英语：", english)
print("科学：", science)
print("----------------")
print("总分：", total_score)
print("平均分：", average_score)


# ============================================================
# ✏️ 课堂练习
# ============================================================

# 练习1：创建变量
# 创建三个变量存储你的姓名、年龄、身高，然后打印出来
# 提示：name = "你的名字"

# 练习2：计算购物总价
# 铅笔2元/支，买了5支；橡皮1.5元/块，买了3块
# 用变量计算总价，输出结果

# 练习3：找错误
# 下面哪些变量名是错误的？为什么？
# ① my_name = "小明"    ② 3score = 100
# ③ class = "三年级"     ④ player-1 = "小红"
# ⑤ _total = 50          ⑥ import = 123


# ============================================================
# 🏆 综合挑战：个人财务小管家
# ============================================================
# 模拟一个简单的零花钱管理系统：
# 1. 创建变量存你的初始零花钱（如 100 元）
# 2. 减去买文具花的钱
# 3. 加上做家务赚的钱
# 4. 计算剩余多少钱
# 5. 计算出花掉的钱占总数的百分比
#
# 要求：每个数字都用有意义的变量名
# 输出格式要清晰好看

# --- 在这里写你的代码 ---

