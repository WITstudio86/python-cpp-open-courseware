# ============================================================
# 第18节：for 循环实战
# 学习目标：掌握累加器、计数器、字符串累加、九九乘法表
# 适合年龄：10-12岁
# ============================================================

print("=" * 50)
print("🎮 第18节：for 循环实战")
print("=" * 50)

# ============ 第一部分：累加器模式 ============
print("\n📝 一、累加器模式 —— 像存钱罐一样")
print("-" * 30)

# 求 1+2+3+4+5 的和
total = 0  # 空存钱罐
print("计算 1+2+3+4+5：")
for i in range(1, 6):
    total += i  # 等价于 total = total + i
    print(f"  加了 {i}，现在总和 = {total}")
print(f"✅ 最终结果：{total}")

# 1+2+...+100（高斯的故事）
print(f"\n1+2+...+100 的和：")
total2 = 0
for i in range(1, 101):
    total2 += i
print(f"  = {total2}（高斯算出来也是 5050！）")

# ============ 第二部分：计数器模式 ============
print("\n📝 二、计数器模式 —— 记下满足条件的次数")
print("-" * 30)

# 统计 1-50 中 7 的倍数有几个
count = 0
print("1-50 中 7 的倍数：")
for i in range(1, 51):
    if i % 7 == 0:
        print(f"  {i}", end="")
        count += 1
print(f"\n一共有 {count} 个")

# 统计 1-100 中能被 3 整除的有多少个？
print("\n1-100 中能被 3 整除的有多少个？")
count2 = 0
for i in range(1, 101):
    if i % 3 == 0:
        count2 += 1
print(f"  一共有 {count2} 个")

# ============ 第三部分：字符串累加 ============
print("\n📝 三、字符串累加 —— 像串珠子")
print("-" * 30)

# 把名字的每个字用 ⭐ 连起来
name = "我爱编程"
result = ""
for char in name:
    result += char + "⭐"
print(f"'{name}' 串起来：{result}")

# 用逗号分隔
result2 = ""
for char in name:
    result2 += char + ", "
print(f"用逗号分隔：{result2}")

# ============ 第四部分：九九乘法表 ============
print("\n📝 四、九九乘法表")
print("-" * 30)

# 单行版
print("7 的乘法口诀：")
for i in range(1, 10):
    print(f"  7 × {i} = {7 * i}")

# 完整版（双重循环）
print("\n📝 完整九九乘法表：")
print("=" * 60)
for i in range(1, 10):        # 外层：控制行（第几行）
    for j in range(1, i+1):   # 内层：控制列（这一行有几列）
        print(f"{j}×{i}={i*j:2d}", end="  ")
    print()  # 一行结束，换行
print("=" * 60)

# ============ 第五部分：求和器项目 ============
print("\n📝 五、项目：求和器")
print("-" * 30)

n = int(input("请输入 n，我会帮你算 1+2+...+n 的和："))
sum_result = 0
for i in range(1, n + 1):
    sum_result += i
print(f"1+2+...+{n} = {sum_result}")

# 验证：用公式 n*(n+1)/2
formula_result = n * (n + 1) // 2
print(f"公式验证：{n} × ({n}+1) ÷ 2 = {formula_result}")
print(f"结果一致！✅" if sum_result == formula_result else "结果不一致！❌")

# ============ 练习题1：1到100的和 ============
print("\n" + "=" * 50)
print("✏️ 练习1：计算 1+2+...+100")
print("=" * 50)

total_100 = 0
for i in range(1, 101):
    total_100 += i
print(f"1+2+...+100 = {total_100}")
print(f"高斯公式法：100×101÷2 = {100*101//2}")

# ============ 练习题2：输入5个数求平均 ============
print("\n" + "=" * 50)
print("✏️ 练习2：输入5个数字，求和与平均值")
print("=" * 50)

total_input = 0
for i in range(1, 6):
    num = float(input(f"请输入第 {i} 个数字："))
    total_input += num

average = total_input / 5
print(f"\n总和：{total_input}")
print(f"平均值：{average:.2f}")

# ============ 练习题3：找最大值 ============
print("\n" + "=" * 50)
print("✏️ 练习3：在一组数字中找最大值")
print("=" * 50)

numbers = [23, 45, 12, 67, 34, 89, 7, 56, 91, 28]
print(f"数字列表：{numbers}")

max_num = numbers[0]  # 先假设第一个最大
for n in numbers:
    if n > max_num:
        max_num = n

print(f"最大值是：{max_num}")

# 也找一下最小值
min_num = numbers[0]
for n in numbers:
    if n < min_num:
        min_num = n
print(f"最小值是：{min_num}")

# ============ 综合小挑战 ============
print("\n" + "=" * 50)
print("🏆 综合挑战：成绩统计分析器")
print("=" * 50)

# 用户输入若干成绩，统计总分、平均分、最高分、最低分、及格人数
print("请输入学生成绩，输入 -1 结束：")

scores_list = []
while True:
    s = float(input("请输入成绩："))
    if s == -1:
        break
    if s >= 0 and s <= 100:
        scores_list.append(s)
    else:
        print("成绩应在 0-100 之间，请重新输入")

if len(scores_list) > 0:
    total_s = 0
    max_s = scores_list[0]
    min_s = scores_list[0]
    pass_count = 0

    for s in scores_list:
        total_s += s
        if s > max_s:
            max_s = s
        if s < min_s:
            min_s = s
        if s >= 60:
            pass_count += 1

    avg_s = total_s / len(scores_list)

    print(f"\n📊 成绩分析报告")
    print(f"  总人数：{len(scores_list)}")
    print(f"  总分：{total_s}")
    print(f"  平均分：{avg_s:.1f}")
    print(f"  最高分：{max_s}")
    print(f"  最低分：{min_s}")
    print(f"  及格人数：{pass_count}")
    print(f"  及格率：{pass_count / len(scores_list) * 100:.1f}%")
else:
    print("没有输入任何成绩~")

print("\n" + "🎉" * 10)
print("恭喜完成第18节的学习！for 循环实战能力大增！")
print("🎉" * 10)
