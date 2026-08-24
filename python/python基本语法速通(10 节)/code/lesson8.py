# ============================================
# 第 8 课  不到目的不罢休
# 结构：热身 → 主项目 → 加码
# 知识：while、break、continue、再来一局
# ============================================

print("######## 热身 A：倒计时 ########")
n = int(input("从几开始倒数？ "))
while n > 0:
    print(n)
    n = n - 1
print("发射！")
print()

print("######## 热身 B：口令循环 ########")
print("输入 go 才会继续（体会 while 条件）。")
word = input("请输入 go：")
while word != "go":
    word = input("不对，再输入一次 go：")
print("收到，出发！")
print()
print("—— 热身结束，下面做主项目 ——")
print()

# ============================================
# 主项目：猜数字（可再来一局）
# ============================================
import random

print("######## 主项目：猜数字游戏 ########")

again = "y"
while again == "y" or again == "Y":
    secret = random.randint(1, 100)
    tries = 0
    max_tries = 7
    guess = None

    print()
    print("=" * 40)
    print("我想了一个 1~100 的整数，你有 7 次机会。")
    print("=" * 40)

    while tries < max_tries:
        raw = input(f"第 {tries + 1} 次，请猜：")
        if not raw.isdigit():
            print("请输入整数！这次不算数。")
            continue

        guess = int(raw)
        if guess < 1 or guess > 100:
            print("超出 1~100，这次不算数。")
            continue

        tries = tries + 1

        if guess == secret:
            print(f"猜对了！答案 {secret}，用了 {tries} 次。")
            if tries == 1:
                print("评语：天选之人！")
            elif tries <= 3:
                print("评语：厉害。")
            else:
                print("评语：过关。")
            break
        elif guess < secret:
            print("太小了 ⬆")
        else:
            print("太大了 ⬇")

        left = max_tries - tries
        if left > 0:
            print(f"还剩 {left} 次。")

    if guess != secret:
        print(f"次数用完。正确答案是 {secret}。")

    again = input("再来一局？(y/n)：")

print("主项目结束，谢谢来玩！")
print()
print("—— 下面是加码（选做）——")
print()

# ============================================
# 加码 1：密码重试 3 次
# ============================================
print("######## 加码 1：密码重试 3 次 ########")
pwd = "python"
used = 0
ok = False
while used < 3:
    guess_pwd = input(f"请输入密码（还剩 {3 - used} 次）：")
    used = used + 1
    if guess_pwd == pwd:
        print("登录成功！")
        ok = True
        break
    print("密码错误。")
if not ok:
    print("三次都错，账户锁定。正确答案是 python（课堂演示用）。")
print()

# ============================================
# 加码 2：输入数字累加，输入 0 结束
# ============================================
print("######## 加码 2：累加器 ########")
print("不断输入数字，输入 0 结束并求和。")
total = 0
count = 0
while True:
    x = float(input("数字（0 结束）："))
    if x == 0:
        break
    total = total + x
    count = count + 1
print(f"共输入 {count} 个数，总和 {total}。")
if count > 0:
    print(f"平均 {total / count:.1f}")
print()
print("while 三件套：初始值、条件、更新。死循环就检查是不是忘了更新。")
