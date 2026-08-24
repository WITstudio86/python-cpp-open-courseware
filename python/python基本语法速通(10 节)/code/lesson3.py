# ============================================
# 第 3 课  数据的身份证
# 结构：热身 → 主项目 → 加码
# 知识：int/float/str/bool、type、转换、:.1f
# ============================================

print("######## 热身：类型侦探 ########")
print()

print("18      的类型：", type(18))
print("1.75    的类型：", type(1.75))
print("'18'    的类型：", type("18"))
print("True    的类型：", type(True))
print()

# 看起来像数字，其实是文字
a = "12"
b = 12
print("a = '12' ，b = 12")
print("a 的类型", type(a), "  b 的类型", type(b))
print("b + 1 =", b + 1)
# print(a + 1)  # 打开这行会报错：文字不能直接加数字
print("a + '1' =", a + "1")   # 文字拼接：121
print("int(a) + 1 =", int(a) + 1)  # 先转换再加：13
print()
print("—— 热身结束，下面做主项目 ——")
print()

# ============================================
# 主项目：个人信息卡 + BMI
# ============================================
print("######## 主项目：个人信息卡 ########")
print()
print("说明：input() 拿到的永远是字符串，要算数必须先转换。")
print()

name = input("姓名：")
age = int(input("年龄："))
height = float(input("身高（米，例如 1.60）："))
weight = float(input("体重（公斤，例如 50）："))
year_now = int(input("今年是哪一年："))
is_student = True

print()
print("-" * 40)
print("【类型检查】")
print("name      =", name, "   ", type(name))
print("age       =", age, "   ", type(age))
print("height    =", height, "   ", type(height))
print("weight    =", weight, "   ", type(weight))
print("is_student=", is_student, "   ", type(is_student))
print("-" * 40)

birth_year = year_now - age
next_year = age + 1
bmi = weight / (height * height)

print()
print("【信息卡】")
print(f"姓名：{name}")
print(f"年龄：{age} 岁（大约出生于 {birth_year} 年）")
print(f"明年：{next_year} 岁")
print(f"身高：{height} 米")
print(f"体重：{weight} 公斤")
print(f"BMI ：{bmi:.1f}   （体重 ÷ 身高 ÷ 身高）")
print(f"是否学生：{is_student}")
print()
print("BMI 参考：18.5~24 大致正常（详细分档第 6 课再做）")
print()
print("—— 主项目结束，下面是加码（选做）——")
print()

# ============================================
# 加码：单位换算器
# ============================================
print("######## 加码：单位换算器 ########")
print()

cm = float(input("身高再写一次（厘米，例如 160）："))
jin = float(input("体重再写一次（斤，例如 100）："))
seconds = int(input("一段时长（秒，例如 375）："))

meters = cm / 100
kg = jin / 2
minutes = seconds // 60
remain = seconds % 60

print()
print("-" * 40)
print(f"{cm} 厘米 = {meters} 米")
print(f"{jin} 斤   = {kg} 公斤")
print(f"{seconds} 秒  = {minutes} 分 {remain} 秒")
print("-" * 40)
print("这里用到了 /（普通除）、//（整除）、%（取余），下节课会系统讲。")
