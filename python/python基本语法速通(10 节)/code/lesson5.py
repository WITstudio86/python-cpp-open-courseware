# ============================================
# 第 5 课  程序会选择了
# 结构：热身 → 主项目 → 加码
# 知识：if / else、缩进、嵌套 if、多段独立 if
# ============================================

print("######## 热身：三个小判断 ########")
print()

# 1) 及格判定
score = int(input("热身1  输入一个成绩："))
if score >= 60:
    print("及格")
else:
    print("不及格")

# 2) 奇偶
n = int(input("热身2  输入一个整数："))
if n % 2 == 0:
    print(f"{n} 是偶数")
else:
    print(f"{n} 是奇数")

# 3) 正负零
x = int(input("热身3  输入一个整数（可正可负）："))
if x > 0:
    print("正数")
else:
    if x < 0:
        print("负数")
    else:
        print("是零")
print()
print("—— 热身结束，下面做主项目 ——")
print()

# ============================================
# 主项目：电影票价查询（含会员、周末、赠品）
# ============================================
print("######## 主项目：电影票价查询 ########")
print()
print("规则：未成年 25 元，成年 45 元；周末 +10；会员 9 折；满 50 送爆米花")
print()

age = int(input("观影人年龄："))
if age < 0:
    print("年龄不合法，按 0 岁处理。")
    age = 0

if age < 18:
    print("未成年人 → 学生票 25 元")
    price = 25
else:
    print("成年人 → 成人票 45 元")
    price = 45

day = input("今天是周末吗？(y/n)：")
if day == "y" or day == "Y":
    extra = 10
    print("周末加收 10 元")
else:
    extra = 0
    print("工作日无加价")

price = price + extra

vip = input("有会员卡吗？(y/n)：")
if vip == "y" or vip == "Y":
    # 嵌套：会员里面再判断是否满 30，满 30 才打折
    if price >= 30:
        price = price * 0.9
        print("会员满 30，打九折")
    else:
        print("会员但未满 30，原价")
else:
    print("非会员，原价")

print()
print("-" * 40)
print(f"应付票价：{price:.2f} 元")
if price >= 50:
    print("满 50，送一小桶爆米花！")
else:
    print("再凑一凑就满 50，可以送爆米花。")
print("祝观影愉快！")
print("-" * 40)
print()
print("—— 主项目结束，下面是加码（选做）——")
print()

# ============================================
# 加码 1：登录门卫（两层 if）
# ============================================
print("######## 加码 1：登录门卫 ########")
ok_user = "xiaoming"
ok_pwd = "1234"

user = input("用户名：")
if user == ok_user:
    pwd = input("密码：")
    if pwd == ok_pwd:
        print("欢迎回来，小明！")
    else:
        print("密码错误。")
else:
    print("没有这个用户。")
print()

# ============================================
# 加码 2：温度穿衣顾问
# ============================================
print("######## 加码 2：温度穿衣顾问 ########")
temp = float(input("今天气温（℃）："))
rain = input("会下雨吗？(y/n)：")

if temp < 10:
    print("建议：厚外套 + 长裤")
else:
    print("建议：薄外套或长袖就行")

if rain == "y" or rain == "Y":
    print("另外：带伞！")
else:
    print("另外：不用带伞。")
print()
print("本课只用 if/else（二选一）。三种以上的路，下一课用 elif。")
