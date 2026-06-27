# ============================================================
# 第19节：while 循环 —— 不达目的不罢休
# 学习目标：掌握 while 语法、理解 for/while 区别、避免死循环
# 适合年龄：10-12岁
# ============================================================

import time  # 用于倒计时的暂停效果

print("=" * 50)
print("🎮 第19节：while 循环 —— 不达目的不罢休")
print("=" * 50)

# ============ 第一部分：认识 while 循环 ============
print("\n📝 一、while 循环的基本结构")
print("-" * 30)
print("""
while 条件:
    循环体（条件成立时执行）

⚠️ 循环体里一定要改变条件！否则死循环！
""")

# 简单例子：从 1 数到 5
print("从 1 数到 5：")
i = 1
while i <= 5:
    print(f"  {i}", end="")
    i += 1  # 每次 +1，最终 i 会 > 5
print()

# ============ 第二部分：for vs while 对比 ============
print("\n📝 二、for 和 while 对比")
print("-" * 30)

print("用 for 打印 1-5：")
for n in range(1, 6):
    print(f"  {n}", end="")
print()

print("用 while 打印 1-5：")
n = 1
while n <= 5:
    print(f"  {n}", end="")
    n += 1
print()

print("\n规则：知道次数用 for，知道条件用 while！")

# ============ 第三部分：while 的典型场景 ============
print("\n📝 三、while 的典型使用场景")
print("-" * 30)

# 场景1：不知道循环次数——用户说了算
print("场景1：一直问，直到用户说 yes")
answer = ""
while answer != "yes":
    answer = input("  你学会了吗？(输入 yes)：")
print("  太好了！让我们继续~")

# 场景2：累加到超过目标
print("\n场景2：1+2+3+... 加到什么时候总和超过 50？")
total = 0
num = 1
while total <= 50:
    total += num
    num += 1
print(f"  加到 {num-1} 时，总和 = {total}，超过了 50！")

# ============ 第四部分：倒数计时器 ============
print("\n📝 四、项目：倒数计时器")
print("-" * 30)

countdown = 10
print("🚀 火箭即将发射！")
while countdown > 0:
    print(f"  {countdown}...")
    countdown -= 1
    time.sleep(0.5)  # 暂停 0.5 秒，让效果更好看
print("🚀 发射！冲冲冲！")
print()

# ============ 第五部分：警惕死循环 ============
print("\n📝 五、⚠️ 警惕死循环！")
print("-" * 30)
print("""
死循环示例（千万不要这样写！）：
  i = 1
  while i <= 5:
      print(i)
      # 忘记写 i += 1 → 死循环！

解决方法：
  1. 确保循环体里有改变条件的代码
  2. 如果死循环了，按 Ctrl + C 强制停止
""")

# ============ 练习题1：用 while 打印 1-10 ============
print("\n" + "=" * 50)
print("✏️ 练习1：用 while 打印 1 到 10")
print("=" * 50)

num = 1
print("1 到 10：", end=" ")
while num <= 10:
    print(num, end=" ")
    num += 1
print()

# ============ 练习题2：倒计时 ============
print("\n" + "=" * 50)
print("✏️ 练习2：自由设定倒计时")
print("=" * 50)

start = int(input("请输入倒计时从几开始："))
print(f"\n从 {start} 开始倒计时：")
while start > 0:
    print(f"  {start}!")
    start -= 1
    time.sleep(0.3)
print("  💥 时间到！")

# ============ 练习题3：加法练习器 ============
print("\n" + "=" * 50)
print("✏️ 练习3：加法练习器（答对5题过关）")
print("=" * 50)

import random

correct_count = 0  # 答对的题数
while correct_count < 5:
    # 出题
    a = random.randint(1, 20)
    b = random.randint(1, 20)
    answer = int(input(f"  {a} + {b} = ? "))

    if answer == a + b:
        correct_count += 1
        print(f"  ✅ 答对了！已答对 {correct_count}/5 题")
    else:
        print(f"  ❌ 错了！正确答案是 {a + b}，继续加油~")

print(f"\n🎉 恭喜！你答对了 5 题，过关！")

# ============ 综合小挑战 ============
print("\n" + "=" * 50)
print("🏆 综合挑战：猜数字 2.0（限制次数版）")
print("=" * 50)

# 猜数字游戏，但限制 7 次机会
secret = random.randint(1, 100)
chances = 7
print(f"我想好了一个 1-100 的数字，你有 {chances} 次机会！")

while chances > 0:
    print(f"\n剩余机会：{chances}")
    guess = int(input("请猜："))

    if guess < 1 or guess > 100:
        print("要猜 1-100 之间的数字哦，这次不算~")
        continue

    if guess == secret:
        print(f"🎉 猜对了！就是 {secret}！")
        print(f"你用了 {7 - chances + 1} 次机会")
        break

    chances -= 1
    if guess > secret:
        print("📈 猜大了！")
    else:
        print("📉 猜小了！")

    if chances > 0:
        print(f"再试试，还剩 {chances} 次机会~")

if chances == 0:
    print(f"\n😢 机会用完了！秘密数字是 {secret}")

print("\n" + "🎉" * 10)
print("恭喜完成第19节的学习！while 循环也掌握了！")
print("🎉" * 10)
