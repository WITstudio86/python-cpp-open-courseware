# ============================================================
# 第12节：if 语句 —— 程序会选择了
# 学习目标：掌握 if 语句的基本语法和缩进规则
# 适合年龄：10-12岁
# ============================================================

print("=" * 50)
print("🎮 第12节：if 语句 —— 程序会选择了")
print("=" * 50)

# ============ 第一部分：认识 if 语句 ============
print("\n📝 一、if 语句的基本结构")
print("-" * 30)
print("""
if 条件:
    条件成立时要执行的代码（注意：前面有4个空格缩进！）
""")

# ============ 第二部分：及格判断器 1.0 ============
print("\n📝 二、项目：及格判断器 1.0")
print("-" * 30)

score = 85
print(f"你的分数是：{score}分")

if score >= 60:
    print("🎉 及格啦！")
    print("你太棒了，继续加油！")

print("（判断结束）")

# ============ 第三部分：试试不及格的情况 ============
print("\n📝 三、不及格的情况")
print("-" * 30)

score2 = 55
print(f"你的分数是：{score2}分")

if score2 >= 60:
    print("🎉 及格啦！")  # 这句话不会执行，因为55<60

print("（判断结束）—— 你看，什么也没打印，因为条件不成立")

# ============ 第四部分：多个 if 各自判断 ============
print("\n📝 四、多个 if 各自判断")
print("-" * 30)

age = 10
print(f"你今年 {age} 岁：")

if age >= 6:
    print("  ✅ 可以上小学了（6岁以上）")

if age >= 12:
    print("  ✅ 可以上初中了（12岁以上）")

if age >= 15:
    print("  ✅ 可以上高中了（15岁以上）")

if age >= 18:
    print("  ✅ 你成年了！（18岁以上）")

# ============ 第五部分：if 里面可以写多行 ============
print("\n📝 五、if 里面可以写多行代码")
print("-" * 30)

weather = "晴天"
print(f"今天天气：{weather}")

if weather == "晴天":
    print("☀️ 天气真好！")
    print("  我们一起去公园玩吧！")
    print("  记得戴帽子哦~")

# ============ 练习题1：温度警报 ============
print("\n" + "=" * 50)
print("✏️ 练习1：高温警报器")
print("=" * 50)

# 请修改 temperature 的值，看看效果
temperature = 38  # 试试改成 25、30、40 看看
print(f"当前温度：{temperature}°C")

if temperature > 35:
    print("🔥 太热了！注意防暑！")
    print("  建议：多喝水，减少户外活动")

if temperature < 10:
    print("❄️ 太冷了！注意保暖！")

# ============ 练习题2：购物判断 ============
print("\n" + "=" * 50)
print("✏️ 练习2：零花钱够不够？")
print("=" * 50)

# 修改 money 和 price，看效果
money = 50
price = 30
print(f"零花钱：{money}元，商品价格：{price}元")

if money >= price:
    print("✅ 够买！下单吧！")
    change = money - price
    print(f"   还能找回 {change} 元")

if money < price:
    print("❌ 不够买哦，再攒攒吧")

# ============ 练习题3：输入互动版 ============
print("\n" + "=" * 50)
print("✏️ 练习3：互动版及格判断器")
print("=" * 50)

# 让用户输入分数
user_score = int(input("请输入你的考试分数："))
print(f"你输入了：{user_score}分")

if user_score >= 60:
    print("🎉 恭喜你，及格啦！")
    if user_score >= 90:
        print("   而且还是高分呢！学霸！")
    if user_score == 100:
        print("   满分！！！你是传奇！")

if user_score < 60:
    print("这次没及格，下次加油！")

# ============ 综合小挑战 ============
print("\n" + "=" * 50)
print("🏆 综合挑战：VIP 判断系统")
print("=" * 50)

# 等级判断
name = input("请输入你的名字：")
points = int(input(f"{name}，请输入你的积分："))

print(f"\n--- {name} 的VIP等级 ---")

if points >= 1000:
    print("🌟 钻石VIP！享受所有特权")
    print("   - 免运费")
    print("   - 专属客服")
    print("   - 生日礼物")

if points >= 500 and points < 1000:
    print("⭐ 黄金VIP！享受部分特权")
    print("   - 免运费")
    print("   - 专属客服")

if points >= 100 and points < 500:
    print("✨ 白银会员！享受基础特权")
    print("   - 免运费")

if points < 100:
    print("🔰 普通会员，继续加油攒积分吧！")
    print(f"   距离白银会员还差 {100 - points} 积分")

print("\n" + "🎉" * 10)
print("恭喜完成第12节的学习！程序会做选择了！")
print("🎉" * 10)
