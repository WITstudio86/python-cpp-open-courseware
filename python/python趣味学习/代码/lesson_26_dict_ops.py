# ============================================================
# 第26节：字典的增删改查
# 适合：10-12 岁 Python 初学者
# ============================================================

# 一、添加和修改（复习）
print("=== 一、添加和修改 ===")

hero = {"名字": "钢铁侠", "能力": "飞行"}
print("初始：", hero)

# 添加：key 不存在就添加
hero["武器"] = "掌心炮"
hero["队友"] = "蜘蛛侠"
print("添加后：", hero)

# 修改：key 存在就修改
hero["能力"] = "超强飞行 + 战斗"
print("修改后：", hero)

# 二、删除：del
print("\n=== 二、删除 del ===")

student = {"姓名": "小明", "年龄": 12, "班级": "五年级", "爱好": "编程"}
print("原始：", student)

del student["爱好"]
print("删除'爱好'后：", student)

# 安全删除：先判断再删除
key = "身高"
if key in student:
    del student[key]
    print(f"已删除 {key}")
else:
    print(f"字典中没有 {key}，跳过删除")

# 三、get() 安全访问
# [] 访问不存在的 key 会报错，get() 不会！
print("\n=== 三、get() 安全访问 ===")

info = {"姓名": "小明", "年龄": 12}

# 方式1：[] 访问 —— 不存在会报错
try:
    print("姓名：", info["姓名"])  # 正常
    print("身高：", info["身高"])  # KeyError! 程序崩溃
except KeyError:
    print("⚠️ 用 [] 访问不存在的 key 会报错！")

# 方式2：get() 访问 —— 安全，不存在返回 None 或默认值
print("\n用 get() 安全访问：")
print("姓名：", info.get("姓名"))         # 存在，返回"小明"
print("身高：", info.get("身高"))         # 不存在，返回 None（不报错！）
print("身高：", info.get("身高", "未知"))  # 不存在，返回默认值"未知"
print("年龄：", info.get("年龄", "保密"))  # 存在，返回12（忽略默认值）

# 四、遍历字典：keys()、values()、items()
print("\n=== 四、遍历字典 ===")

hero = {"名字": "蜘蛛侠", "能力": "吐丝", "城市": "纽约", "武器": "蛛网发射器"}

# keys() —— 只看键（标签）
print("所有键（标签）：")
for k in hero.keys():
    print(f"  - {k}")

# values() —— 只看值（内容）
print("\n所有值（内容）：")
for v in hero.values():
    print(f"  - {v}")

# items() —— 键和值一起看（最常用！）
print("\n完整信息：")
for k, v in hero.items():
    print(f"  {k:8s} → {v}")

# 五、实用的字典操作
print("\n=== 五、实用操作 ===")

# 获取字典长度
print("字典中有", len(hero), "个键值对")

# 清空字典
test = {"a": 1, "b": 2, "c": 3}
print("清空前：", test, "长度：", len(test))
test.clear()
print("清空后：", test, "长度：", len(test))

# ============================================================
# 练习题
# ============================================================

print("\n" + "=" * 40)
print("  课堂练习")
print("=" * 40)

# 练习1：安全查询成绩
print("\n【练习1】安全查询：")
grades = {
    "小明": 95,
    "小红": 88,
    "小刚": 72,
    "小丽": 100,
    "小华": 83
}
# 用 get() 安全查询
name = input("查询谁的成绩？").strip()
score = grades.get(name)
if score is not None:
    print(f"{name} 的成绩是：{score} 分")
else:
    print(f"查无此人：{name}")

# 练习2：三种遍历方式
print("\n【练习2】遍历方式：")
food_calories = {"米饭": 116, "面条": 110, "鸡蛋": 144, "牛奶": 54}

print("只看食物名（keys）：")
for food in food_calories.keys():
    print(f"  - {food}")

print("\n只看卡路里（values）：")
for cal in food_calories.values():
    print(f"  - {cal} 大卡")

print("\n完整信息（items）：")
for food, cal in food_calories.items():
    print(f"  {food}：{cal} 大卡/100g")

# 练习3：安全删除
print("\n【练习3】安全删除：")
info = {"姓名": "小明", "年龄": 12, "班级": "五年级", "爱好": "编程"}
print("当前信息：", info)

key_to_del = input("要删除哪个信息？").strip()
if key_to_del in info:
    del info[key_to_del]
    print(f"✅ 已删除'{key_to_del}'")
else:
    print(f"❌ 没有'{key_to_del}'这个信息")
print("最终信息：", info)

# ============================================================
# 综合小挑战：升级版英汉词典
# ============================================================

print("\n" + "=" * 40)
print("  综合挑战：📖 升级版英汉词典")
print("=" * 40)

dictionary = {
    "apple": "苹果",
    "banana": "香蕉",
    "cat": "猫",
    "dog": "狗",
    "hello": "你好",
    "book": "书"
}

while True:
    print("\n" + "=" * 30)
    print("   📖 英汉词典管理系统")
    print("=" * 30)
    print("  1. 查单词")
    print("  2. 添加/修改单词")
    print("  3. 删除单词")
    print("  4. 查看所有单词")
    print("  5. 单词数量统计")
    print("  6. 退出")
    print("=" * 30)

    choice = input("请选择 (1-6): ").strip()

    if choice == "1":
        word = input("输入要查的英文单词: ").strip().lower()
        meaning = dictionary.get(word)
        if meaning:
            print(f"✅ {word} = {meaning}")
        else:
            print(f"❌ 词典中还没有「{word}」")

    elif choice == "2":
        word = input("输入英文单词: ").strip().lower()
        if word in dictionary:
            print(f"⚠️ 「{word}」已存在，意思是：{dictionary[word]}")
            confirm = input("要修改吗？(y/n): ").strip().lower()
            if confirm == "y":
                meaning = input("输入新的中文含义: ").strip()
                dictionary[word] = meaning
                print("✅ 修改成功！")
        else:
            meaning = input("输入中文含义: ").strip()
            if meaning:
                dictionary[word] = meaning
                print("✅ 添加成功！")

    elif choice == "3":
        word = input("输入要删除的单词: ").strip().lower()
        if word in dictionary:
            confirm = input(f"确认删除「{word} = {dictionary[word]}」？(y/n): ").strip().lower()
            if confirm == "y":
                del dictionary[word]
                print("✅ 删除成功！")
        else:
            print(f"❌ 词典中没有「{word}」")

    elif choice == "4":
        if len(dictionary) == 0:
            print("词典为空！")
        else:
            print(f"\n共有 {len(dictionary)} 个词条：")
            print("-" * 30)
            for en, cn in dictionary.items():
                print(f"  📝 {en:15s} → {cn}")

    elif choice == "5":
        print(f"\n📊 词典统计：")
        print(f"  总词条数：{len(dictionary)}")
        # 统计最长的英文单词
        if dictionary:
            longest = max(dictionary.keys(), key=len)
            print(f"  最长的单词：{longest}（{len(longest)} 个字母）")

    elif choice == "6":
        print("再见！👋")
        break

    else:
        print("⚠️ 请输入 1-6 之间的数字。")

print("\n✅ 第26节完成！")
