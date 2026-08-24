# ============================================
# 第 10 课  语法大综合
# 结构：热身 → 主项目 → 加码
# 知识：列表 + 循环 + 判断 拼装
# ============================================

print("######## 热身：先用固定成绩走一遍套路 ########")
demo = [88, 57, 91, 73, 60]
print("示例成绩：", demo)

total = 0
highest = demo[0]
lowest = demo[0]
passed = 0
for s in demo:
    total = total + s
    if s > highest:
        highest = s
    if s < lowest:
        lowest = s
    if s >= 60:
        passed = passed + 1
avg = total / len(demo)
print(f"人数 {len(demo)}  总分 {total}  平均 {avg:.1f}")
print(f"最高 {highest}  最低 {lowest}  及格 {passed} 人")
print()
print("三种套路：累加器 / 擂台 / 计数。下面换成你自己录入。")
print()
print("—— 热身结束，下面做主项目 ——")
print()

# ============================================
# 主项目：班级成绩统计台
# ============================================
print("######## 主项目：班级成绩统计台 ########")
print("依次输入成绩，输入 -1 结束。建议先用 88 57 91 73 60 -1 对答案。")
print()

scores = []
while True:
    raw = input(f"第 {len(scores) + 1} 位同学的成绩：")
    score = float(raw)
    if score == -1:
        break
    if score < 0 or score > 100:
        print("成绩应在 0~100，请重新输入。")
        continue
    scores.append(score)

print()

if len(scores) == 0:
    print("没有录入任何成绩。")
else:
    total = 0
    passed = 0
    excellent = 0
    fail = 0
    highest = scores[0]
    lowest = scores[0]
    hi_index = 0

    print("-" * 40)
    print("【逐人报告】")
    for i in range(len(scores)):
        s = scores[i]
        total = total + s
        if s > highest:
            highest = s
            hi_index = i
        if s < lowest:
            lowest = s
        if s >= 90:
            excellent = excellent + 1
            passed = passed + 1
            flag = "优秀"
        elif s >= 80:
            passed = passed + 1
            flag = "良好"
        elif s >= 60:
            passed = passed + 1
            flag = "及格"
        else:
            fail = fail + 1
            flag = "不及格"
        print(f"  第 {i + 1:2d} 位：{s:5.1f} 分  {flag}")

    avg = total / len(scores)
    rate = passed / len(scores) * 100

    print("-" * 40)
    print("【全班统计】")
    print(f"人数     ：{len(scores)}")
    print(f"总分     ：{total:.1f}")
    print(f"平均分   ：{avg:.1f}")
    print(f"最高分   ：{highest:.1f}  （第 {hi_index + 1} 位）")
    print(f"最低分   ：{lowest:.1f}")
    print(f"及格人数 ：{passed}  （及格率 {rate:.0f}%）")
    print(f"优秀人数 ：{excellent}")
    print(f"不及格   ：{fail}")
    print("-" * 40)

    passed_list = []
    fail_list = []
    for s in scores:
        if s >= 60:
            passed_list.append(s)
        else:
            fail_list.append(s)
    print(f"及格成绩：{passed_list}")
    print(f"不及格  ：{fail_list}")
    print()
    print("—— 主项目结束，下面是加码（选做）——")
    print()

    # ============================================
    # 加码 1：用星星画分数条形图
    # ============================================
    print("######## 加码 1：分数条形图 ########")
    for i in range(len(scores)):
        s = scores[i]
        bars = int(s // 5)     # 每 5 分一颗星，100 分 20 颗
        print(f"{i + 1:2d} | {'★' * bars} {s:.0f}")
    print()

    # ============================================
    # 加码 2：低于平均分的同学
    # ============================================
    print("######## 加码 2：低于平均分 ########")
    below = []
    for i in range(len(scores)):
        if scores[i] < avg:
            below.append(i + 1)
    if len(below) == 0:
        print("没有人低于平均分。")
    else:
        print("低于平均分的座位号：", below)
        for i in below:
            print(f"  第 {i} 位：{scores[i - 1]} 分")

    print()
    print("=" * 40)
    print("10 节课过完啦！你已经会：")
    print("  输入输出、类型、运算、判断、循环、列表。")
    print("下一站：零基础到图形化项目实战 / Python 趣味学习 / Pygame")
    print("=" * 40)
