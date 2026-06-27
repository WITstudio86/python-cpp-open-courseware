# ============================================================
# 第11节：比较运算符 —— 学会比大小
# 学习目标：掌握 > < == != >= <= 六种比较运算符
# 适合年龄：10-12岁
# ============================================================

print("=" * 50)
print("🎮 第11节：比较运算符 —— 学会比大小")
print("=" * 50)

# ============ 第一部分：认识比较运算符 ============
print("\n📝 一、认识六个比较运算符")
print("-" * 30)

print("1. >  大于号（开口朝左，左边大）")
print("   10 > 5 =", 10 > 5)      # 结果为 True
print("   3 > 8 =", 3 > 8)        # 结果为 False

print("\n2. <  小于号（开口朝右，右边大）")
print("   5 < 10 =", 5 < 10)      # True
print("   10 < 3 =", 10 < 3)      # False

print("\n3. == 等于号（两个等号！用来判断是否相等）")
print("   7 == 7 =", 7 == 7)      # True
print("   7 == 8 =", 7 == 8)      # False
print("   ⚠️ 注意：一个 = 是赋值，两个 == 才是判断相等！")

print("\n4. != 不等于号")
print("   7 != 8 =", 7 != 8)      # True
print("   7 != 7 =", 7 != 7)      # False

print("\n5. >= 大于等于（大于或者等于都算）")
print("   10 >= 10 =", 10 >= 10)  # True（等于也算）
print("   10 >= 5  =", 10 >= 5)   # True
print("   5 >= 10  =", 5 >= 10)   # False

print("\n6. <= 小于等于（小于或者等于都算）")
print("   5 <= 5  =", 5 <= 5)     # True
print("   5 <= 10 =", 5 <= 10)    # True
print("   10 <= 5 =", 10 <= 5)    # False

# ============ 第二部分：用变量比较 ============
print("\n📝 二、用变量来做比较")
print("-" * 30)

# 比身高
ming_height = 145
hong_height = 150
print(f"小明身高：{ming_height}cm，小红身高：{hong_height}cm")
print(f"小红比小明高吗？{hong_height > ming_height}")
print(f"他们一样高吗？{ming_height == hong_height}")

# 比年龄
my_age = 11
friend_age = 12
print(f"\n我今年 {my_age} 岁，朋友今年 {friend_age} 岁")
print(f"朋友比我大吗？{friend_age > my_age}")
print(f"我们同岁吗？{my_age == friend_age}")
print(f"我至少10岁吗？{my_age >= 10}")

# ============ 第三部分：字符串比较 ============
print("\n📝 三、字符串也能比较")
print("-" * 30)

# 字符串按字母顺序比较
print('"apple" < "banana" =', "apple" < "banana")   # True，a在b前面
print('"cat" > "dog" =', "cat" > "dog")             # False，c在d前面
print('"hello" == "hello" =', "hello" == "hello")   # True，完全相同
print('"Hello" == "hello" =', "Hello" == "hello")   # False，大小写不同！

# ============ 第四部分：比较结果存起来 ============
print("\n📝 四、把比较结果存到变量里")
print("-" * 30)

score = 85
is_pass = score >= 60  # 把比较的 True/False 存起来
print(f"分数：{score}")
print(f"及格了吗？{is_pass}")
print(f"is_pass 的类型是：{type(is_pass)}")  # <class 'bool'>

# ============ 练习题1：判断下面结果 ============
print("\n" + "=" * 50)
print("✏️ 练习1：猜猜下面的结果，然后运行验证")
print("=" * 50)

# 请先自己猜，再运行看答案
print("100 > 99 =", 100 > 99)
print("50 == 50 =", 50 == 50)
print("30 != 30 =", 30 != 30)
print('"cat" < "dog" =', "cat" < "dog")
print("你的年龄 >= 10？", 11 >= 10)

# ============ 练习题2：比分数 ============
print("\n" + "=" * 50)
print("✏️ 练习2：三个同学比分数")
print("=" * 50)

# 小明数学88分，小红92分，小刚88分
ming_math = 88
hong_math = 92
gang_math = 88

print(f"小明：{ming_math}分，小红：{hong_math}分，小刚：{gang_math}分")

# 小红是不是最高的？
hong_highest = (hong_math > ming_math) and (hong_math > gang_math)
print(f"小红考得最高吗？{hong_highest}")

# 小明和小刚分数一样吗？
print(f"小明和小刚分数一样吗？{ming_math == gang_math}")

# ============ 练习题3：购物判断 ============
print("\n" + "=" * 50)
print("✏️ 练习3：零花钱够不够？")
print("=" * 50)

# 商品价格50元，零花钱35元
price = 50
money = 35

can_buy = money >= price
print(f"商品价格：{price}元")
print(f"我的零花钱：{money}元")
print(f"够买吗？{can_buy}")

# 如果不够，差多少钱？
if not can_buy:
    need_more = price - money
    print(f"还差 {need_more} 元钱 😢")

# ============ 综合小挑战 ============
print("\n" + "=" * 50)
print("🏆 综合挑战：猜猜谁的年龄大")
print("=" * 50)

# 任务：输入两个人的名字和年龄，比较谁更大
name1 = input("请输入第一个人的名字：")
age1 = int(input(f"请输入{name1}的年龄："))

name2 = input("请输入第二个人的名字：")
age2 = int(input(f"请输入{name2}的年龄："))

print(f"\n--- 比较结果 ---")
print(f"{name1}比{name2}大？{age1 > age2}")
print(f"{name1}比{name2}小？{age1 < age2}")
print(f"两人同龄？{age1 == age2}")

# 判断成年
print(f"{name1}成年了吗？（>=18）{age1 >= 18}")
print(f"{name2}成年了吗？（>=18）{age2 >= 18}")

print("\n" + "🎉" * 10)
print("恭喜完成第11节的学习！你已经学会比较大小了！")
print("🎉" * 10)
