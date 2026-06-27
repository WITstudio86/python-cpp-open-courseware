# ============================================================
# 第20节：break 和 continue
# 学习目标：掌握 break（跳出循环）和 continue（跳过本次）
# 适合年龄：10-12岁
# ============================================================

print("=" * 50)
print("🎮 第20节：break 和 continue")
print("=" * 50)

# ============ 第一部分：认识 break ============
print("\n📝 一、break —— 跳出循环（不玩了！）")
print("-" * 30)

# 示例：找到第一个能被 7 整除的数就停
print("在 1-50 中找第一个能被 7 整除的数：")
for i in range(1, 51):
    if i % 7 == 0:
        print(f"  ✅ 找到了！{i} 是第一个能被 7 整除的数")
        break  # 找到了！不用继续找了
print("  循环结束（找到目标就停了）")

# 对比：没有 break 的话
print("\n如果没有 break，会打印所有 7 的倍数：")
for i in range(1, 51):
    if i % 7 == 0:
        print(f"  {i}", end=" ")
print()

# ============ 第二部分：认识 continue ============
print("\n📝 二、continue —— 跳过本次（这轮跳过！）")
print("-" * 30)

# 示例：打印 1-20，但跳过 3 的倍数
print("打印 1-20，跳过 3 的倍数：")
for i in range(1, 21):
    if i % 3 == 0:
        continue  # 遇到 3 的倍数就跳过
    print(i, end=" ")
print()

# ============ 第三部分：break vs continue 对比 ============
print("\n📝 三、break 和 continue 的区别")
print("-" * 30)

numbers = [1, 3, 5, 6, 7, 9, 10, 11, 12]

print(f"列表：{numbers}")

# break：找到第一个偶数就停
print("\n使用 break（找到第一个偶数就停）：")
for n in numbers:
    if n % 2 == 0:
        print(f"  找到偶数 {n}，停止！")
        break
    print(f"  检查了 {n}（奇数）")

# continue：跳过奇数，只处理偶数
print("\n使用 continue（跳过奇数，只打印偶数）：")
for n in numbers:
    if n % 2 != 0:
        continue  # 奇数跳过
    print(f"  偶数：{n}")

# ============ 第四部分：密码验证（break） ============
print("\n📝 四、项目1：密码验证（最多3次机会）")
print("-" * 30)

correct_password = "abc123"
max_tries = 3
tries = 0

print(f"你有 {max_tries} 次机会输入密码~")

while tries < max_tries:
    remaining = max_tries - tries
    user_pw = input(f"请输入密码（还剩 {remaining} 次机会）：")

    if user_pw == correct_password:
        print("✅ 密码正确！欢迎进入系统！🎉")
        break  # 密码对了，跳出循环
    else:
        tries += 1
        if tries < max_tries:
            print(f"❌ 密码错误！还剩 {max_tries - tries} 次机会")
        else:
            print("❌ 3次机会已用完，账户已锁定！🔒")

# ============ 第五部分：跳过3的倍数（continue） ============
print("\n📝 五、项目2：跳过3的倍数")
print("-" * 30)

print("报数游戏：从 1 到 30，3 的倍数说'过'：")
for i in range(1, 31):
    if i % 3 == 0:
        print("过", end=" ")
        continue  # 跳过，不打印数字
    print(i, end=" ")
print()

# ============ 练习题1：找第一个公倍数 ============
print("\n" + "=" * 50)
print("✏️ 练习1：找第一个同时被3和5整除的数")
print("=" * 50)

print("在 1-100 中，第一个同时被 3 和 5 整除的数是：")
for i in range(1, 101):
    if i % 3 == 0 and i % 5 == 0:
        print(f"  ✅ {i}（15！3×5=15）")
        break

# ============ 练习题2：跳过4的倍数 ============
print("\n" + "=" * 50)
print("✏️ 练习2：打印 1-30，跳过 4 的倍数")
print("=" * 50)

print("1-30 中不是 4 的倍数的数字：")
for i in range(1, 31):
    if i % 4 == 0:
        continue
    print(i, end=" ")
print()

# ============ 练习题3：寻宝游戏 ============
print("\n" + "=" * 50)
print("✏️ 练习3：寻宝游戏")
print("=" * 50)

# 模拟一排箱子，只有一个装宝藏
import random
boxes = ["📦空"] * 10
treasure_index = random.randint(0, 9)
boxes[treasure_index] = "💎宝藏"

print("有 10 个宝箱，其中只有 1 个有宝藏！")
print("开始逐个打开...")

for i, box in enumerate(boxes, 1):
    print(f"  打开第 {i} 个宝箱...", end=" ")
    if box == "💎宝藏":
        print("💎 找到宝藏啦！！！")
        break
    else:
        print("空的，继续找...")

# ============ 综合小挑战 ============
print("\n" + "=" * 50)
print("🏆 综合挑战：智能点名系统")
print("=" * 50)

# 学生名单，有些请假了
students = [
    "小明", "小红（请假）", "小刚",
    "小丽（请假）", "小华", "小强（请假）",
    "小美", "小龙"
]

print("开始点名！")
present_count = 0
absent_count = 0

for student in students:
    if "请假" in student:
        name = student.replace("（请假）", "")
        print(f"  {name} → ⚠️ 请假了（跳过）")
        absent_count += 1
        continue  # 跳过请假的同学

    print(f"  {student} → ✅ 到！")
    present_count += 1

print(f"\n📊 点名结果：应到 {len(students)} 人")
print(f"  实到：{present_count} 人")
print(f"  请假：{absent_count} 人")

# 检查是否全部到齐
if absent_count == 0:
    print("🎉 全部到齐！开始上课！")
else:
    print(f"有 {absent_count} 位同学请假，我们开始上课吧！")

print("\n" + "🎉" * 10)
print("恭喜完成第20节的学习！break 和 continue 都掌握了！")
print("🎉" * 10)
