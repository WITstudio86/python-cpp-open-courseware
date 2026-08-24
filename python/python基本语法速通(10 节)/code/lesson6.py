# ============================================
# 第 6 课  多路选择
# 结构：热身 → 主项目 → 加码
# 知识：if / elif / else、顺序、random.choice
# ============================================

print("######## 热身：成绩等级 ########")
print("规则：90 优秀  80 良好  60 及格  否则不及格")
print("注意：要把高分档写在前面，否则 95 会被判成及格。")
print()

score = int(input("输入成绩："))
if score > 100 or score < 0:
    print("成绩应在 0~100")
elif score >= 90:
    print("优秀")
elif score >= 80:
    print("良好")
elif score >= 60:
    print("及格")
else:
    print("不及格")
print()
print("—— 热身结束，下面做主项目 ——")
print()

# ============================================
# 主项目：石头剪刀布
# ============================================
import random

print("######## 主项目：石头剪刀布 ########")
print("规则：石头赢剪刀，剪刀赢布，布赢石头")
print()

player = input("请出拳（石头 / 剪刀 / 布）：")
computer = random.choice(["石头", "剪刀", "布"])

print()
print(f"你出了：{player}")
print(f"电脑出：{computer}")
print("-" * 40)

if player != "石头" and player != "剪刀" and player != "布":
    print("输入无效，只能出 石头 / 剪刀 / 布")
    result = "无效"
elif player == computer:
    print("平局！")
    result = "平"
elif player == "石头" and computer == "剪刀":
    print("你赢了！石头砸剪刀 ✊")
    result = "赢"
elif player == "剪刀" and computer == "布":
    print("你赢了！剪刀剪布 ✌️")
    result = "赢"
elif player == "布" and computer == "石头":
    print("你赢了！布包石头 🖐️")
    result = "赢"
else:
    print("你输了……电脑赢了这一局。")
    result = "输"

print("-" * 40)
print(f"本局结果：{result}")
print("想再玩就重新运行程序。连玩三局，看谁赢的多。")
print()
print("—— 主项目结束，下面是加码（选做）——")
print()

# ============================================
# 加码 1：菜单点餐
# ============================================
print("######## 加码 1：菜单点餐 ########")
print("1 汉堡 18 元")
print("2 薯条 8 元")
print("3 可乐 6 元")
print("4 套餐（汉堡+薯条+可乐）28 元")
choice = input("请输入序号 1-4：")

if choice == "1":
    print("你点了汉堡，请支付 18 元")
elif choice == "2":
    print("你点了薯条，请支付 8 元")
elif choice == "3":
    print("你点了可乐，请支付 6 元")
elif choice == "4":
    print("你点了套餐，请支付 28 元（省 4 元）")
else:
    print("菜单上没有这个序号。")
print()

# ============================================
# 加码 2：BMI 分档（把第 3 课的 BMI 用起来）
# ============================================
print("######## 加码 2：BMI 健康分档 ########")
h = float(input("身高（米）："))
w = float(input("体重（公斤）："))
bmi = w / (h * h)
print(f"你的 BMI = {bmi:.1f}")

if bmi < 18.5:
    print("偏瘦，记得多吃一点、加强营养。")
elif bmi < 24:
    print("正常，继续保持！")
elif bmi < 28:
    print("偏胖，建议多运动。")
else:
    print("肥胖范围，建议咨询专业建议。")
print()
print("elif 口诀：从上往下，命中一个就停；宽条件写后面。")
