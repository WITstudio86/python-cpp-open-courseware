# ============================================================
# 第30节：参数 —— 给函数传信息
# 适合：10-12 岁 Python 初学者
# ============================================================

# 一、从无参数到有参数
print("=== 一、从无参数到有参数 ===")

# 无参数：每次做同样的事
def greet_everyone():
    """只能跟'大家'打招呼"""
    print("大家好！")

greet_everyone()
print("上面这个函数只能跟'大家'打招呼，太死板了！")

# 有参数：可以针对不同的人
def greet(name):
    """向指定的人打招呼，name 是参数"""
    print(f"你好，{name}！")

greet("小明")
greet("小红")
greet("王老师")
print("这个函数灵活多了！想跟谁打招呼都行。")

# 二、形参和实参
print("\n=== 二、形参和实参 ===")

print("形参（形式参数）：函数定义时小括号里的变量")
print("  就像电影院的座位 —— 预留位置")
print()
print("实参（实际参数）：调用函数时传入的具体值")
print("  就像坐上去的人 —— 实际填充")
print()

def introduce(name, age):
    """介绍一个人，name 和 age 都是形参"""
    print(f"我叫{name}，今年{age}岁。")

# "小明" 和 12 都是实参
introduce("小明", 12)   # 实参按位置对应形参
introduce("小红", 11)

# 三、多个参数
print("\n=== 三、多个参数 ===")

def add(a, b):
    """两个数相加"""
    result = a + b
    print(f"{a} + {b} = {result}")

def multiply(a, b):
    """两个数相乘"""
    result = a * b
    print(f"{a} × {b} = {result}")

add(3, 5)
add(100, 200)
multiply(6, 7)
multiply(9, 9)

# 注意：参数顺序要对应！
def order_matters(first, second):
    """演示参数顺序的重要性"""
    print(f"第一个参数：{first}")
    print(f"第二个参数：{second}")

print("\n正确顺序：")
order_matters("苹果", "香蕉")
print("\n如果顺序反了：")
order_matters("香蕉", "苹果")  # 结果完全不同！

# 四、默认参数
print("\n=== 四、默认参数 ===")

def greet_with_default(name, greeting="你好"):
    """打招呼，greeting 有默认值"你好" """
    print(f"{greeting}，{name}！")

# 不传 greeting，用默认值
greet_with_default("小明")     # 你好，小明！

# 传了 greeting，覆盖默认值
greet_with_default("小红", "生日快乐")  # 生日快乐，小红！

# 用参数名指定
greet_with_default("王老师", greeting="下午好")  # 下午好，王老师！

# 灵活的分隔线
def print_line(length=30, char="-"):
    """打印分隔线，可以指定长度和字符"""
    print(char * length)

print("\n灵活的分隔线：")
print_line()           # 默认：30 个 '-'
print_line(15)         # 15 个 '-'
print_line(20, "=")    # 20 个 '='
print_line(char="*")   # 30 个 '*'
print_line(char="~", length=40)  # 40 个 '~'，指定参数名可以不按顺序

# 五、实用参数函数
print("\n=== 五、实用参数函数 ===")

def power(base, exp=2):
    """计算 base 的 exp 次方，默认平方"""
    result = base ** exp
    return result

print(f"3 的平方（默认）：{power(3)}")
print(f"3 的 3 次方：{power(3, 3)}")
print(f"2 的 10 次方：{power(2, 10)}")

def multiplication_table(n):
    """打印 n 的乘法表"""
    print(f"\n{n} 的乘法表：")
    print_line(20, "-")
    for i in range(1, 10):
        print(f"  {i} × {n} = {i * n}")
    print_line(20, "-")

multiplication_table(5)
multiplication_table(7)

# ============================================================
# 练习题
# ============================================================

print("\n" + "=" * 40)
print("  课堂练习")
print("=" * 40)

# 练习1：打招呼函数
print("\n【练习1】问候不同的人：")

def say_hello(name):
    """向某人问好"""
    print(f"你好，{name}！欢迎来学 Python！")

say_hello("小明")
say_hello("小红")
say_hello("老师")

# 练习2：乘法表
print("\n【练习2】打印乘法表：")

def show_table(n):
    """打印 n 的乘法表"""
    print(f"--- {n} 的乘法表 ---")
    for i in range(1, 10):
        print(f"  {i} × {n} = {i * n}")

show_table(3)
show_table(8)

# 练习3：默认参数
print("\n【练习3】默认参数测试：")

def my_print_line(length=20, char="-"):
    """打印分隔线的各种用法"""
    print(char * length)

print("默认（20 个 -）：", end="")
my_print_line()

print("指定长度（10 个 -）：", end="")
my_print_line(10)

print("指定字符（20 个 *）：", end="")
my_print_line(char="*")

print("两个都指定（40 个 ~）：", end="")
my_print_line(40, "~")

# ============================================================
# 综合小挑战：成绩报告生成器
# ============================================================

print("\n" + "=" * 40)
print("  综合挑战：📊 成绩报告生成器")
print("=" * 40)

def print_report(name, score, subject="数学", max_score=100):
    """打印一份成绩报告"""
    pct = score / max_score * 100

    print("\n" + "=" * 30)
    print(f"  📝 成绩报告")
    print("=" * 30)
    print(f"  科目：{subject}")
    print(f"  姓名：{name}")
    print(f"  成绩：{score}/{max_score}")
    print(f"  百分比：{pct:.1f}%")

    # 评级
    if pct >= 90:
        grade = "优秀 🌟"
    elif pct >= 80:
        grade = "良好 👍"
    elif pct >= 60:
        grade = "及格"
    else:
        grade = "需要加油 💪"
    print(f"  评级：{grade}")
    print("=" * 30)

# 生成几份报告
print_report("小明", 95)                    # 默认科目和满分
print_report("小红", 82, "英语")            # 指定科目
print_report("小刚", 65, "语文", 100)       # 完整指定
print_report("小丽", 45, max_score=100)     # 用参数名

# 让用户输入生成报告
print("\n--- 生成你自己的成绩报告 ---")
name = input("你的名字：").strip()
score_input = input("你的分数：").strip()
subject = input("科目（直接回车默认数学）：").strip()

if name and score_input.isdigit():
    score = int(score_input)
    if subject:
        print_report(name, score, subject)
    else:
        print_report(name, score)

print("\n✅ 第30节完成！")
