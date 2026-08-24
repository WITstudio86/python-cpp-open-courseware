# ============================================
# 第 2 课  和电脑对话
# 结构：热身 → 主项目 → 加码
# 知识：变量、起名规则、input、f-string、拼接
# ============================================

print("######## 热身：变量三连 ########")
print()

# 变量 = 贴了标签的盒子
animal = "小猫"
count = "3"
print("我养了", count, "只", animal)

# 可以重新赋值，盒子里的东西会被换掉
animal = "小狗"
print("现在改口：我养了", count, "只", animal)

# 把两个文字拼起来：加号（两边都必须是字符串）
who = "小明"
hobby = "篮球"
print(who + "喜欢" + hobby)

print()
print("—— 热身结束，下面做主项目 ——")
print()

# ============================================
# 主项目：自我介绍生成器
# ============================================
print("######## 主项目：自我介绍生成器 ########")
print()
print("=" * 40)
print("      🎤 请回答下面 6 个问题")
print("=" * 40)

name = input("1. 你叫什么名字？ ")
age = input("2. 你今年几岁？ ")
city = input("3. 你住在哪个城市？ ")
school = input("4. 你在哪所学校？ ")
hobby = input("5. 你最大的爱好是什么？ ")
food = input("6. 你最喜欢吃什么？ ")
dream = input("7. 你的一个小梦想？ ")

print()
print("-" * 40)
print("【自我介绍卡片】")
print("-" * 40)
print(f"大家好，我叫 {name}！")
print(f"今年 {age} 岁，来自 {city}，在 {school} 上学。")
print(f"平时最爱 {hobby}，嘴馋的时候就想吃 {food}。")
print(f"我的小梦想是：{dream}")
print(f"—— 来自 {city} 的 {name} 敬上")
print("-" * 40)
print()
print("—— 主项目结束，下面是加码（选做）——")
print()

# ============================================
# 加码：故事填空机
# ============================================
print("######## 加码：故事填空机 ########")
print("请随便填词，我会编一个小故事。")
print()

hero = input("一个名字： ")
place = input("一个地点： ")
thing = input("一个物品： ")
adj = input("一个形容词（比如：神奇的）： ")
verb = input("一个动词（比如：吃掉）： ")

print()
print("=" * 40)
print("【生成的故事】")
print("=" * 40)
print(f"从前，{hero} 来到了 {place}。")
print(f"地上突然冒出 {adj}{thing}。")
print(f"{hero} 想也没想，就把 {thing} {verb} 了！")
print(f"从此，{place} 的人都认识了 {hero}。")
print("（全文完）")
print("=" * 40)
