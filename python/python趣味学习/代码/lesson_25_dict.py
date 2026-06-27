# ============================================================
# 第25节：字典 —— 成对存储
# 适合：10-12 岁 Python 初学者
# ============================================================

# 一、创建字典
# 字典用花括号 {}，key: value 成对出现
print("=== 一、创建字典 ===")

# 个人信息字典
me = {
    "名字": "小明",
    "年龄": 12,
    "年级": "五年级",
    "爱好": "编程",
    "喜欢的颜色": "蓝色"
}
print("个人信息：", me)

# 空字典
empty = {}
print("空字典：", empty)

# 成绩字典
scores = {
    "语文": 95,
    "数学": 88,
    "英语": 92,
    "科学": 100
}
print("成绩：", scores)

# 二、通过键（key）访问值（value）
print("\n=== 二、通过键访问值 ===")

print("我的名字：", me["名字"])
print("我的年龄：", me["年龄"])
print("我的爱好：", me["爱好"])

# 用变量作为 key
field = "年级"
print(f"我的{field}：", me[field])

# ⚠️ 访问不存在的 key 会报错！
# print(me["身高"])  # KeyError!

# 三、添加新键值对
print("\n=== 三、添加信息 ===")

me["宠物"] = "小猫"
me["梦想"] = "成为程序员"
me["身高"] = 155
print("添加后：", me)

# 四、修改已有的值
print("\n=== 四、修改信息 ===")

print("修改前的年龄：", me["年龄"])
me["年龄"] = 13  # 长大一岁！
print("修改后的年龄：", me["年龄"])

me["爱好"] = "编程和画画"  # 爱好变多了
print("修改后的爱好：", me["爱好"])

# 五、用 in 判断 key 是否存在
print("\n=== 五、判断 key 是否存在 ===")

print("有'名字'这个信息吗？", "名字" in me)
print("有'体重'这个信息吗？", "体重" in me)

# 安全访问：先判断再访问
key = "身高"
if key in me:
    print(f"{key}：{me[key]}")
else:
    print(f"字典中没有 {key} 这个信息")

# 六、遍历字典
print("\n=== 六、遍历字典 ===")

# 遍历所有的键
print("所有的键：")
for key in me:
    print(f"  - {key}")

# 通过键获取值
print("\n完整信息：")
for key in me:
    print(f"  {key}：{me[key]}")

# ============================================================
# 练习题
# ============================================================

print("\n" + "=" * 40)
print("  课堂练习")
print("=" * 40)

# 练习1：创建个人字典
print("\n【练习1】我的个人信息：")
my_info = {
    "姓名": "请输入你的名字",
    "年龄": 10,
    "班级": "请输入你的班级",
    "爱好": "请输入你的爱好"
}
# 请修改上面的字典，填入你自己的信息
# 然后打印每一项
print("姓名：", my_info["姓名"])
print("年龄：", my_info["年龄"])
print("班级：", my_info["班级"])
print("爱好：", my_info["爱好"])

# 练习2：水果中英文对照
print("\n【练习2】水果词典：")
fruit_dict = {
    "apple": "苹果",
    "banana": "香蕉",
    "orange": "橘子",
    "grape": "葡萄",
    "watermelon": "西瓜"
}

# 查询
word = input("请输入水果的英文名：").strip().lower()
if word in fruit_dict:
    print(f"📝 {word} = {fruit_dict[word]}")
else:
    print("❌ 词典里还没有这个词，你可以帮我添加！")
    chinese = input("它对应的中文是：").strip()
    if chinese:
        fruit_dict[word] = chinese
        print(f"✅ 已添加：{word} → {chinese}")

# 练习3：成绩字典
print("\n【练习3】我的成绩单：")
my_scores = {
    "语文": 95,
    "数学": 88,
    "英语": 92
}
for subject, score in my_scores.items():
    print(f"  {subject}：{score} 分")
print(f"总分：{sum(my_scores.values())}")

# ============================================================
# 综合小挑战：迷你英汉词典
# ============================================================

print("\n" + "=" * 40)
print("  综合挑战：📖 迷你英汉词典")
print("=" * 40)

# 词典数据
dictionary = {
    "apple": "苹果",
    "banana": "香蕉",
    "cat": "猫",
    "dog": "狗",
    "hello": "你好",
    "thank you": "谢谢",
    "goodbye": "再见",
    "book": "书",
    "water": "水",
    "sun": "太阳",
    "moon": "月亮",
    "star": "星星"
}

print("欢迎使用英汉词典！")
print("输入 q 退出程序\n")

while True:
    word = input("请输入英文单词：").strip().lower()

    if word == "q":
        print("再见！👋")
        break

    if word in dictionary:
        print(f"  📝 {word} = {dictionary[word]}")
    else:
        print(f"  ❌ 词典中还没有「{word}」")
        add = input(f"  要添加「{word}」到词典吗？(y/n)：").strip().lower()
        if add == "y":
            meaning = input(f"  请输入「{word}」的中文意思：").strip()
            if meaning:
                dictionary[word] = meaning
                print(f"  ✅ 已添加！{word} = {meaning}")

print(f"\n词典中共有 {len(dictionary)} 个词条")
print("\n所有词条：")
for en, cn in dictionary.items():
    print(f"  {en:15s} → {cn}")

print("\n✅ 第25节完成！")
