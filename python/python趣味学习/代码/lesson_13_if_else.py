# ============================================================
# 第13节：if-else —— 二选一
# 学习目标：掌握 if-else 结构，实现二选一判断
# 适合年龄：10-12岁
# ============================================================

print("=" * 50)
print("🎮 第13节：if-else —— 二选一")
print("=" * 50)

# ============ 第一部分：认识 if-else ============
print("\n📝 一、if-else 的基本结构")
print("-" * 30)
print("""
if 条件:
    条件成立时执行
else:
    条件不成立时执行

注意：else 后面没有条件！直接跟冒号！
""")

# ============ 第二部分：升级版及格判断器 ============
print("\n📝 二、项目：升级版及格判断器")
print("-" * 30)

score = 85
print(f"你的分数是：{score}分")

if score >= 60:
    print("🎉 及格啦！")
    print("  太棒了，给你一朵小红花 🌺")
    print("  继续加油，下次争取更高分！")
else:
    print("😢 这次没及格")
    print("  别灰心，下次一定可以的！")
    print("  有不会的题要多问老师哦~")

print("（判断结束）")

# ============ 第三部分：试试不及格的情况 ============
print("\n📝 三、不及格的情况——看看 else 怎么工作")
print("-" * 30)

score2 = 55
print(f"你的分数是：{score2}分")

if score2 >= 60:
    print("🎉 及格啦！")
else:
    print("😢 这次没及格")
    print("  没关系，失败是成功之母！💪")

# ============ 第四部分：生活中的二选一 ============
print("\n📝 四、生活中的二选一例子")
print("-" * 30)

# 例子1：偶数判断
number = 7
print(f"数字 {number}：")
if number % 2 == 0:
    print(f"  → {number} 是偶数（能被2整除）")
else:
    print(f"  → {number} 是奇数（不能被2整除）")

# 例子2：是否成年
age = 15
print(f"\n年龄 {age} 岁：")
if age >= 18:
    print("  → 你成年了，可以考驾照了！")
else:
    wait = 18 - age
    print(f"  → 你还未成年，再过 {wait} 年就可以考驾照啦！")

# 例子3：余额判断
balance = 20
price = 35
print(f"\n余额：{balance}元，价格：{price}元")
if balance >= price:
    change = balance - price
    print(f"  ✅ 购买成功！找回 {change} 元")
else:
    need = price - balance
    print(f"  ❌ 余额不足！还差 {need} 元")

# ============ 练习题1：温度判断 ============
print("\n" + "=" * 50)
print("✏️ 练习1：温度判断（if-else版）")
print("=" * 50)

temp = 38  # 试试改成 20、30、40
print(f"当前温度：{temp}°C")

if temp > 35:
    print("🔥 太热了！注意防暑降温！")
else:
    print("🌤️ 温度还行，不算太热~")

# ============ 练习题2：判断是否大于100 ============
print("\n" + "=" * 50)
print("✏️ 练习2：判断数字大小")
print("=" * 50)

num = 150  # 试试改成 50、100、200
print(f"数字：{num}")

if num > 100:
    print("很大！")
else:
    print("不大。")

# ============ 练习题3：周末判断 ============
print("\n" + "=" * 50)
print("✏️ 练习3：周末判断器")
print("=" * 50)

day = int(input("请输入今天是星期几（1=周一, 7=周日）："))

if day == 6 or day == 7:
    print("🎊 耶！今天是周末！可以尽情玩耍！")
else:
    print("📚 今天要上学/上班，加油！")

# ============ 综合小挑战 ============
print("\n" + "=" * 50)
print("🏆 综合挑战：登录小系统")
print("=" * 50)

# 预设密码
secret_password = "hello123"

print("=== 欢迎登录 ===")
username = input("请输入用户名：")
password = input("请输入密码：")

# 判断用户名和密码
if password == secret_password:
    print(f"\n✅ 登录成功！欢迎你，{username}！")
    print("  祝你今天开心！🌈")
else:
    print(f"\n❌ 密码错误！")
    print("  提示：密码是 hello123")
    print("  请重新运行程序再试~")

print("\n" + "🎉" * 10)
print("恭喜完成第13节的学习！程序会二选一了！")
print("🎉" * 10)
