# ============================================================
# 第14节：if-elif-else —— 多选一
# 学习目标：掌握 if-elif-else 结构，实现多条件判断
# 适合年龄：10-12岁
# ============================================================

print("=" * 50)
print("🎮 第14节：if-elif-else —— 多选一")
print("=" * 50)

# ============ 第一部分：认识 if-elif-else ============
print("\n📝 一、if-elif-else 基本结构")
print("-" * 30)
print("""
if 条件1:
    条件1成立 → 执行这里
elif 条件2:
    条件1不成立，条件2成立 → 执行这里
elif 条件3:
    前面都不成立，条件3成立 → 执行这里
else:
    所有条件都不成立 → 执行这里

规则：从上到下判断，命中一个就停！
""")

# ============ 第二部分：等级评定系统 ============
print("\n📝 二、项目：等级评定系统")
print("-" * 30)

score = 85
print(f"分数：{score}分")

if score >= 90:
    grade = "A"
    message = "太厉害了，学霸！🌟"
elif score >= 80:
    grade = "B"
    message = "很不错，继续保持！👍"
elif score >= 70:
    grade = "C"
    message = "还可以，争取更好！💪"
elif score >= 60:
    grade = "D"
    message = "刚刚及格，要加油哦！📚"
else:
    grade = "E"
    message = "不及格，下次努力！🔥"

print(f"等级：{grade}")
print(f"评语：{message}")

# ============ 第三部分：演示条件顺序的重要性 ============
print("\n📝 三、⚠️ 条件顺序非常重要！")
print("-" * 30)

print("❌ 错误示范（条件从低到高排）：")
score = 95
print(f"分数：{score}")
if score >= 60:
    print("  → 结果：D  ← 95>=60成立！后面的就不判断了！")
elif score >= 90:
    print("  → A（永远不会执行到这里！）")
print("  结论：95分得了D，太冤了！条件要从高到低排列！")

print("\n✅ 正确示范（条件从高到低排）：")
if score >= 90:
    print(f"  → 等级：A（正确！95>=90 成立）")
elif score >= 80:
    print("  → B")
elif score >= 70:
    print("  → C")
elif score >= 60:
    print("  → D")
else:
    print("  → E")

# ============ 第四部分：生活例子 ============
print("\n📝 四、生活中的多选一例子")
print("-" * 30)

# 例子1：人生阶段
age = 15
print(f"年龄：{age} 岁")
if age < 0:
    print("  年龄不合法！")
elif age <= 6:
    print("  → 幼儿阶段")
elif age <= 12:
    print("  → 儿童阶段")
elif age <= 17:
    print("  → 青少年阶段")
else:
    print("  → 成人阶段")

# 例子2：身高评价
height = 140
print(f"\n身高：{height} cm")
if height >= 180:
    print("  → 很高！可以打篮球！")
elif height >= 160:
    print("  → 中等偏高")
elif height >= 140:
    print("  → 中等偏矮，还在长身体~")
else:
    print("  → 偏矮，多喝牛奶早睡觉哦~")

# ============ 练习题1：BMI 计算 ============
print("\n" + "=" * 50)
print("✏️ 练习1：BMI 体重判断")
print("=" * 50)

height = float(input("请输入身高（米），例如 1.50："))
weight = float(input("请输入体重（公斤），例如 45："))

bmi = weight / (height * height)
print(f"\n你的 BMI 指数：{bmi:.1f}")

if bmi < 18.5:
    print("📊 偏瘦 —— 要多吃点，加强营养哦~")
elif bmi < 24:
    print("📊 正常 —— 很好，保持住！")
elif bmi < 28:
    print("📊 偏重 —— 注意饮食，多运动~")
else:
    print("📊 肥胖 —— 需要认真减肥了！动起来！")

# ============ 练习题2：天气建议 ============
print("\n" + "=" * 50)
print("✏️ 练习2：智能天气建议")
print("=" * 50)

print("请选择今天的天气：")
print("  1 = 晴天")
print("  2 = 阴天")
print("  3 = 雨天")
print("  4 = 下雪")

weather_choice = input("请输入编号（1-4）：")

if weather_choice == "1":
    print("☀️ 晴天 → 适合去公园玩！记得戴帽子~")
elif weather_choice == "2":
    print("☁️ 阴天 → 适合去图书馆看书~")
elif weather_choice == "3":
    print("🌧️ 雨天 → 在家看电影！出门记得带伞~")
elif weather_choice == "4":
    print("❄️ 下雪 → 堆雪人！注意保暖！")
else:
    print("输入有误，请输入 1-4 的数字哦~")

# ============ 练习题3：心情推荐 ============
print("\n" + "=" * 50)
print("✏️ 练习3：心情智能推荐")
print("=" * 50)

mood = input("你今天的心情怎么样？（开心/难过/无聊/生气）：")

if mood == "开心":
    print("😊 开心就分享快乐！给朋友打个电话吧~")
elif mood == "难过":
    print("😢 别难过，吃点甜食心情会变好！🍰")
elif mood == "无聊":
    print("🥱 无聊就来写 Python 代码呀！编程最有趣了！")
elif mood == "生气":
    print("😤 深呼吸，数到10...或者出去跑两圈！")
else:
    print("🤔 这个心情我没见过...但祝你开心每一天！")

# ============ 综合小挑战 ============
print("\n" + "=" * 50)
print("🏆 综合挑战：智能菜单点餐系统")
print("=" * 50)

print("=== 欢迎来到 Python 餐厅 ===")
print("1. 🍔 汉堡 —— 15元")
print("2. 🍕 披萨 —— 25元")
print("3. 🍟 薯条 —— 8元")
print("4. 🥤 可乐 —— 5元")
print("5. 🍦 冰淇淋 —— 10元")

choice = input("\n请选择编号（1-5）：")

if choice == "1":
    food = "汉堡 🍔"
    price = 15
elif choice == "2":
    food = "披萨 🍕"
    price = 25
elif choice == "3":
    food = "薯条 🍟"
    price = 8
elif choice == "4":
    food = "可乐 🥤"
    price = 5
elif choice == "5":
    food = "冰淇淋 🍦"
    price = 10
else:
    food = "无"
    price = 0
    print("❌ 没有这个选项哦！")

if price > 0:
    money = float(input(f"你点了 {food}，需要 {price} 元。请输入付款金额："))
    if money >= price:
        change = money - price
        print(f"✅ 付款成功！找回 {change:.1f} 元。请享用！")
    else:
        print(f"❌ 金额不足！还差 {price - money:.1f} 元。")

print("\n" + "🎉" * 10)
print("恭喜完成第14节的学习！程序会多选一了！")
print("🎉" * 10)
