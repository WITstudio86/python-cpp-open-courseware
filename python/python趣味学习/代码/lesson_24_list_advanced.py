# ============================================================
# 第24节：列表的更多操作
# 适合：10-12 岁 Python 初学者
# ============================================================

# 一、排序：sort() 和 sorted()
print("=== 一、排序 ===")

# sort()：原地排序，直接修改原列表
numbers = [5, 2, 8, 1, 9, 3]
print("原始列表：", numbers)

numbers.sort()
print("sort() 升序后：", numbers)

numbers.sort(reverse=True)
print("sort(reverse=True) 降序后：", numbers)

# sorted()：生成新列表，原列表不变
numbers = [5, 2, 8, 1, 9, 3]
print("\n原列表不变：", numbers)

sorted_numbers = sorted(numbers)
print("sorted() 新列表（升序）：", sorted_numbers)
print("原列表还是：", numbers)

sorted_desc = sorted(numbers, reverse=True)
print("sorted(..., reverse=True)（降序）：", sorted_desc)

# 字符串列表也能排序（按字母顺序/拼音）
fruits = ["banana", "apple", "cherry", "date"]
fruits.sort()
print("\n水果按字母排序：", fruits)

# 二、反转
print("\n=== 二、反转 reverse() ===")

items = [1, 2, 3, 4, 5]
print("原始：", items)
items.reverse()
print("反转后：", items)

# 注意：reverse() 只是翻转，不是排序！
nums = [3, 1, 5, 2, 4]
print("\n不是排序：", nums)
nums.reverse()
print("翻转（不是排序）：", nums)

# 三、in 判断存在
print("\n=== 三、in 判断存在 ===")

classmates = ["小明", "小红", "小刚", "小丽", "小华"]

# 直接用 in
print("小明在班里吗？", "小明" in classmates)
print("小李在班里吗？", "小李" in classmates)

# in 配合 if 使用
name = "小红"
if name in classmates:
    print(f"✅ {name} 是我们班的同学！")
else:
    print(f"❌ {name} 不是我们班的同学。")

# 四、数值统计：min()、max()、sum()
print("\n=== 四、数值统计 ===")

scores = [95, 88, 92, 100, 76, 83, 91, 89]
print("成绩列表：", scores)

print("最高分 max()：", max(scores))
print("最低分 min()：", min(scores))
print("总分 sum()：", sum(scores))

# 计算平均分
average = sum(scores) / len(scores)
print(f"平均分：{average:.1f}")

# 统计几个特殊值
above_90 = 0
for s in scores:
    if s >= 90:
        above_90 += 1
print(f"90分以上的人数：{above_90}")

# ============================================================
# 练习题
# ============================================================

print("\n" + "=" * 40)
print("  课堂练习")
print("=" * 40)

# 练习1：数字排序
print("\n【练习1】排序比较：")
data = [7, 3, 9, 1, 5, 2, 8, 4, 6]
print("原始数据：", data)

# 用 sorted() 生成新的（原数据不变）
new_data = sorted(data)
print("sorted() 后原数据：", data)
print("sorted() 新数据：", new_data)

# 用 sort() 直接修改
data.sort()
print("sort() 后原数据被修改：", data)

# 练习2：名字查找
print("\n【练习2】查找同学：")
students = ["张三", "李四", "王五", "赵六", "孙七"]
search_name = input("请输入要查找的同学姓名：").strip()
if search_name in students:
    print(f"✅ {search_name} 在班级名单中！")
else:
    print(f"❌ {search_name} 不在班级名单中。")

# 练习3：成绩统计
print("\n【练习3】成绩统计：")
scores = [85, 92, 78, 95, 88, 72, 90, 66]
print("成绩：", scores)
print(f"最高分：{max(scores)}")
print(f"最低分：{min(scores)}")
print(f"总分：{sum(scores)}")
print(f"平均分：{sum(scores)/len(scores):.1f}")

# 排序后更容易看
sorted_scores = sorted(scores, reverse=True)
print(f"从高到低：{sorted_scores}")
print(f"第一名：{sorted_scores[0]} 分")
print(f"最后一名：{sorted_scores[-1]} 分")

# ============================================================
# 综合小挑战：成绩管理器
# ============================================================

print("\n" + "=" * 40)
print("  综合挑战：📊 成绩管理器")
print("=" * 40)

# 让用户输入成绩
scores_input = input("请输入成绩，用空格分隔（如：90 85 78 92）：").strip()
scores_list = []
for s in scores_input.split():
    if s.isdigit():
        scores_list.append(int(s))

if len(scores_list) == 0:
    # 如果用户没输，用默认数据
    scores_list = [95, 88, 92, 100, 76, 83, 91, 89, 45, 72]
    print("使用默认成绩数据。")

print(f"\n分析的成绩：{scores_list}")
print(f"共 {len(scores_list)} 个成绩")

# 排序查看
ascending = sorted(scores_list)
descending = sorted(scores_list, reverse=True)
print(f"\n从低到高：{ascending}")
print(f"从高到低：{descending}")

# 统计信息
print(f"\n📊 统计报告：")
print(f"  最高分：{max(scores_list)}")
print(f"  最低分：{min(scores_list)}")
print(f"  总分：{sum(scores_list)}")
print(f"  平均分：{sum(scores_list)/len(scores_list):.1f}")

# 及格统计
passing = 0
failing = 0
excellent = 0  # >= 90
for s in scores_list:
    if s >= 90:
        excellent += 1
    if s >= 60:
        passing += 1
    else:
        failing += 1

print(f"\n📋 分类统计：")
print(f"  优秀（>= 90）：{excellent} 人")
print(f"  及格（>= 60）：{passing} 人")
print(f"  不及格（< 60）：{failing} 人")
print(f"  及格率：{passing/len(scores_list)*100:.1f}%")

# 反转挑战
print(f"\n反转后的成绩：{scores_list[::-1]}")

print("\n✅ 第24节完成！")
