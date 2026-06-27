# ============================================================
# 第9节：类型转换
# 主题：str()、int()、float() 三大转换函数
# ============================================================

# ===== 1. input() 的陷阱 =====
print("===== 1. input() 的大陷阱 =====")

# 错误示范：input 返回的是字符串！
# 如果运行下面的代码，输入 3 和 5，会输出 "35" 而不是 8！
# a = input("输入a：")
# b = input("输入b：")
# print("a + b =", a + b)   # "3" + "5" = "35"  不是 8！

# 正确做法：用 int() 转换
print("--- 正确做法 ---")
a = int(input("输入第一个数字："))
b = int(input("输入第二个数字："))
print(f"{a} + {b} = {a + b}")        # 数字加法！
print(f"{a} + {b} 的类型是:", type(a + b))

# ===== 2. str() —— 任何东西变成文字 =====
print("\n===== 2. str() —— 变成文字 =====")

print("str(100) =", str(100), "→ 类型:", type(str(100)))
print("str(3.14) =", str(3.14), "→ 类型:", type(str(3.14)))
print("str(True) =", str(True), "→ 类型:", type(str(True)))

# 实用场景：拼接数字和文字
age = 10
# 不用 str()：
print("我今年", age, "岁")            # 用逗号，可以混搭
# 用 str()：
print("我今年" + str(age) + "岁")     # 用 + 号，必须先转
# 用 f-string（更好）：
print(f"我今年{age}岁")               # 什么都不用管！

# ===== 3. int() —— 变成整数 =====
print("\n===== 3. int() —— 变成整数 =====")

# 字符串 → 整数
print('int("25") =', int("25"))       # 25
print('int("100") =', int("100"))     # 100

# 小数 → 整数（直接砍掉小数部分，不是四舍五入！）
print("int(3.9) =", int(3.9))          # 3（砍掉 .9）
print("int(3.1) =", int(3.1))          # 3（砍掉 .1）
print("int(7.999) =", int(7.999))      # 7（砍掉 .999）

# 不能转换的情况：
# int("3.14")   # 错误！字符串里有小数点，不能直接转int
# int("abc")    # 错误！根本不是数字
# int("你好")   # 错误！文字无法转数字

# 解决方案：先 float 再 int
print('\n带小数的字符串 → 先 float 再 int:')
print('int(float("3.14")) =', int(float("3.14")))    # 3

# ===== 4. float() —— 变成小数 =====
print("\n===== 4. float() —— 变成小数 =====")

# 字符串 → 小数
print('float("3.14") =', float("3.14"))
print('float("7") =', float("7"))          # 自动加 .0

# 整数 → 小数
print("float(5) =", float(5))              # 5.0
print("float(100) =", float(100))          # 100.0

# ===== 5. type() —— 随时检查类型 =====
print("\n===== 5. 用 type() 检查类型 =====")

print('"123" 的类型:', type("123"))          # str
print("123 的类型:", type(123))             # int
print("123.0 的类型:", type(123.0))         # float
print('int("123") 的类型:', type(int("123")))  # int

# 类型转换链条
raw = "42"
print(f'\n链条: raw = "42" (类型:{type(raw)})')
a = float(raw)
print(f'  → float(raw) = {a} (类型:{type(a)})')
b = int(a)
print(f'  → int(float) = {b} (类型:{type(b)})')

# ===== 6. 实用例子 =====
print("\n===== 6. 实用例子 =====")

# 例1：计算出生年份
age_str = input("你今年几岁？")
age = int(age_str)
birth_year = 2024 - age
print(f"你大约出生在 {birth_year} 年")

# 例2：计算总价
price = float(input("商品单价："))
count = int(input("购买数量："))
total = price * count
print(f"总价：{total:.2f} 元")

# 例3：温度转换（摄氏度 → 华氏度）
celsius = float(input("\n请输入摄氏温度："))
fahrenheit = celsius * 1.8 + 32
print(f"{celsius}°C = {fahrenheit:.1f}°F")

# 例4：平均分计算
print("\n--- 平均分计算 ---")
chinese = int(input("语文成绩："))
math = int(input("数学成绩："))
english = int(input("英语成绩："))
average = (chinese + math + english) / 3
print(f"平均分：{average:.1f}")

# ===== 7. 常见错误排查 =====
print("\n===== 7. 常见错误 =====")

# 错误1：忘记转换
# a = input("输入数字：")
# print(a * 2)   # 输入5 → 输出"55"，不是10

# 错误2：转换非数字
# int("abc")     # ValueError！

# 错误3：混淆 + 的作用
print('"3" + "5" =', "3" + "5")     # "35"（拼接）
print("3 + 5 =", 3 + 5)             # 8（加法）

# 错误4：int() 不四舍五入
print("int(4.7) =", int(4.7))      # 4（不是5！）

# ===== 8. 加法练习器 =====
print("\n" + "=" * 36)
print("      🧮 加法练习器 🧮")
print("=" * 36)

import random

score = 0  # 得分

for i in range(1, 6):  # 5道题
    a = random.randint(1, 50)
    b = random.randint(1, 50)

    print(f"\n第{i}题：{a} + {b} = ?")
    try:
        answer = int(input("你的答案："))
    except ValueError:
        print("请输入数字！本题0分")
        continue

    if answer == a + b:
        print("✓ 正确！+20分")
        score += 20
    else:
        print(f"✗ 错误，正确答案是 {a + b}")

print("\n" + "=" * 36)
print(f"挑战结束！你的总分：{score} / 100")
if score == 100:
    print("🏆 满分！你是数学天才！")
elif score >= 60:
    print("👍 不错，继续加油！")
else:
    print("💪 还需要多练习哦！")


# ============================================================
# ✏️ 课堂练习
# ============================================================

# 练习1：类型转换判断
# 判断以下表达式的结果和类型：
# (1) int("99")
# (2) float("3.14")
# (3) str(2024)
# (4) int(3.9)
# (5) type(int(float("5.8")))

# 练习2：修复错误代码
# 下面的代码有错误，请修复：
#   a = input("输入a：")
#   b = input("输入b：")
#   print("a - b =", a - b)

# 练习3：改进计算器
# 写一个程序，接收两个数字输入，计算并输出：
# 和、差、积、商、整除、取余、幂运算
# 提示：记得先转成数字类型！


# ============================================================
# 🏆 综合挑战：多功能计算器
# ============================================================
# 做一个多功能计算器程序：
# 1. 首先问用户想做什么运算（加/减/乘/除）
# 2. 然后让用户输入两个数字
# 3. 根据选择进行相应的运算并输出结果
# 4. 额外功能：如果用户选择"幂"，计算并输出
#
# 要求：
# - 所有输入都要正确使用类型转换
# - 除法结果保留2位小数
# - 如果用户输入的不是数字，给出友好的错误提示
# - 输出格式清晰美观

# --- 在这里写你的代码 ---

