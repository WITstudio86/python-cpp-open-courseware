"""
第19节：while 循环 —— 不达目的不罢休
学习目标：掌握 while 循环，理解 for vs while 的区别
"""

import random

# ============================================
# 1. while 基本语法
# ============================================

print("===== while 基本用法 =====")

count = 1
while count <= 5:
    print(f"第 {count} 次循环")
    count += 1      # ⚠️ 一定要改条件！否则死循环！

print("循环结束！")

# ============================================
# 2. for vs while 对比
# ============================================

print("\n===== for vs while =====")

# 打印 1-5：两种写法
print("用 for：", end=" ")
for i in range(1, 6):
    print(i, end=" ")
print()

print("用 while：", end=" ")
i = 1
while i <= 5:
    print(i, end=" ")
    i += 1
print()

# ============================================
# 3. while 的典型场景：不知道次数
# ============================================

print("\n===== 密码验证（不知道试几次）=====")

PASSWORD = "python123"
max_attempts = 3
attempts = 0

while attempts < max_attempts:
    pwd = input("请输入密码：")
    attempts += 1

    if pwd == PASSWORD:
        print("✅ 密码正确！欢迎进入系统！")
        break
    else:
        remaining = max_attempts - attempts
        if remaining > 0:
            print(f"❌ 密码错误！还剩 {remaining} 次机会")
        else:
            print("❌ 密码错误！次数用完了！账户已锁定！")

# ============================================
# 4. 倒数计时器
# ============================================

print("\n===== 🚀 火箭发射倒数 =====")

import time
countdown = 10

while countdown > 0:
    print(f"  {countdown}...")
    countdown -= 1
    # time.sleep(0.5)   # 等 0.5 秒（可选，让效果更好）

print("  🚀 发射！")

# ============================================
# 5. 猜数字（while 版本）
# ============================================

print("\n===== 🎯 猜数字（while 版）=====")

secret = random.randint(1, 100)
guess = 0       # 初始化一个不可能的值
attempts = 0

print("我想了一个 1-100 的数字，来猜猜看！")

while guess != secret:
    guess = int(input("你猜："))
    attempts += 1

    if guess < secret:
        print("  太小了！往大猜")
    elif guess > secret:
        print("  太大了！往小猜")

print(f"🎉 猜对了！就是 {secret}！你猜了 {attempts} 次")

# ============================================
# 6. 避免死循环
# ============================================

print("\n===== ⚠️ 死循环警告 =====")
print("如果把 count += 1 忘记，就会这样：")
print("  count = 1")
print("  while count <= 5:")
print("      print(count)")
print("      # 忘了 count += 1！！！")
print("  → 永远输出 1，永不停止！")
print("  按 Ctrl+C 可以强制停止")

# ============================================
# 7. 综合：简易菜单系统
# ============================================

print("\n===== 📋 简易菜单 =====")
print("1. 说你好")
print("2. 算加法")
print("3. 退出")

while True:
    choice = input("\n请选择（1/2/3）：")

    if choice == "1":
        name = input("你叫什么？")
        print(f"你好，{name}！")
    elif choice == "2":
        a = int(input("第一个数："))
        b = int(input("第二个数："))
        print(f"{a} + {b} = {a + b}")
    elif choice == "3":
        print("再见！👋")
        break
    else:
        print("输入有误，请重新选择！")

# ============================================
# 练习题
# ============================================

# 练习1：用 while 打印 1-50 的所有偶数
# 你的代码：


# 练习2：做一个"倒数计时器"——输入秒数，从该秒数倒数到0
# 你的代码：


# 练习3（挑战）：做一个"存款模拟器"
# 初始存款 0 元，每次可以选择存钱(1)或取钱(2)或退出(3)
# 取钱时如果余额不足要提示
# 你的代码：
