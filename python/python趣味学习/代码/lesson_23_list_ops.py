# ============================================================
# 第23节：列表的增删改查
# 适合：10-12 岁 Python 初学者
# ============================================================

# 一、增加元素
print("=== 一、增加元素 ===")

# append() —— 加到末尾
animals = ["猫", "狗"]
print("初始列表：", animals)

animals.append("兔子")
print("append('兔子') 后：", animals)

animals.append("仓鼠")
print("再 append('仓鼠') 后：", animals)

# insert() —— 插到指定位置
animals.insert(1, "鹦鹉")  # 在索引1的位置插入
print("insert(1, '鹦鹉') 后：", animals)

animals.insert(0, "金鱼")  # 插到最前面
print("insert(0, '金鱼') 后：", animals)

# 二、删除元素
print("\n=== 二、删除元素 ===")

# remove() —— 按值删除（只删第一个匹配的）
colors = ["红", "蓝", "绿", "蓝", "黄"]
print("初始：", colors)
colors.remove("蓝")  # 只删除第一个"蓝"
print("remove('蓝') 后：", colors)

# pop() —— 按索引删除，会返回被删的值
colors = ["红", "蓝", "绿", "黄"]
print("\n新列表：", colors)
removed = colors.pop(1)  # 删除索引1的元素
print(f"pop(1) 删除了：'{removed}'")
print("剩余：", colors)

last = colors.pop()  # 不写索引，默认删最后一个
print(f"pop() 删除了最后一个：'{last}'")
print("剩余：", colors)

# del —— 直接删除，不返回值
colors = ["红", "蓝", "绿", "黄"]
print("\n新列表：", colors)
del colors[0]
print("del[0] 后：", colors)

# 三、修改元素
print("\n=== 三、修改元素 ===")

scores = [85, 90, 78, 92]
print("原始成绩：", scores)
scores[2] = 88  # 把索引2的78改成88
print("修改索引2后：", scores)
scores[-1] = 95  # 把最后一个改成95
print("修改最后一个后：", scores)

# 四、查找元素
print("\n=== 四、查找元素 ===")

fruits = ["苹果", "香蕉", "橘子", "葡萄"]
print("水果列表：", fruits)

# 用 in 判断是否存在
print("'苹果' 在列表里吗？", "苹果" in fruits)
print("'西瓜' 在列表里吗？", "西瓜" in fruits)

# 用 index() 查找位置
print("'橘子' 的位置：", fruits.index("橘子"))

# ============================================================
# 练习题
# ============================================================

print("\n" + "=" * 40)
print("  课堂练习")
print("=" * 40)

# 练习1：购物清单增删
print("\n【练习1】购物清单：")
shopping = []
shopping.append("牛奶")
shopping.append("面包")
shopping.append("鸡蛋")
print("初始清单：", shopping)

shopping.insert(0, "水果")  # 插到最前面
print("加入水果后：", shopping)

shopping.remove("面包")  # 删掉面包
print("删除面包后：", shopping)

# 练习2：成绩修改
print("\n【练习2】成绩修改：")
scores = [88, 92, 75, 96, 83]
print("原始成绩：", scores)
# 把不及格的75改成80（索引2）
if scores[2] < 80:
    scores[2] = 80
    print("修改不及格成绩后：", scores)

# 练习3：排队游戏
print("\n【练习3】排队游戏：")
queue = ["小明", "小红", "小刚", "小丽"]
print("排队：", queue)

# 第一个人办完事离开
gone = queue.pop(0)
print(f"{gone} 办完事离开了")
print("现在的队伍：", queue)

# 新来一个人
queue.append("小华")
print("小华来了，队伍：", queue)

# 又走一个
gone = queue.pop(0)
print(f"{gone} 也离开了，队伍：", queue)

# 又来了一个
queue.append("小强")
print("小强来了，队伍：", queue)

# ============================================================
# 综合小挑战：待办事项小程序
# ============================================================

print("\n" + "=" * 40)
print("  综合挑战：📋 待办事项管理器")
print("=" * 40)

todos = []

while True:
    print("\n--- 待办事项菜单 ---")
    print("1. 添加待办")
    print("2. 查看待办")
    print("3. 完成待办（删除）")
    print("4. 插入紧急事项")
    print("5. 修改待办")
    print("6. 退出")

    choice = input("请选择 (1-6): ").strip()

    if choice == "1":
        task = input("输入新待办：").strip()
        if task:
            todos.append(task)
            print(f"✅ 已添加：「{task}」")

    elif choice == "2":
        if len(todos) == 0:
            print("📭 待办列表是空的！")
        else:
            print("\n📋 当前待办事项：")
            for i, task in enumerate(todos, 1):
                print(f"  {i}. {task}")
            print(f"共 {len(todos)} 件事")

    elif choice == "3":
        if len(todos) == 0:
            print("没有待办可以完成。")
        else:
            for i, task in enumerate(todos, 1):
                print(f"  {i}. {task}")
            num = input("输入要完成的序号：").strip()
            if num.isdigit():
                idx = int(num) - 1
                if 0 <= idx < len(todos):
                    done = todos.pop(idx)
                    print(f"✅ 完成了「{done}」")
                else:
                    print("❌ 序号无效！")

    elif choice == "4":
        task = input("输入紧急事项：").strip()
        if task:
            todos.insert(0, task)
            print(f"⚠️ 紧急事项已插到最前面：「{task}」")

    elif choice == "5":
        if len(todos) == 0:
            print("没有待办可以修改。")
        else:
            for i, task in enumerate(todos, 1):
                print(f"  {i}. {task}")
            num = input("输入要修改的序号：").strip()
            if num.isdigit():
                idx = int(num) - 1
                if 0 <= idx < len(todos):
                    new_task = input("输入新内容：").strip()
                    if new_task:
                        old = todos[idx]
                        todos[idx] = new_task
                        print(f"✅ 已修改「{old}」→「{new_task}」")

    elif choice == "6":
        print("再见！记得完成待办哦💪")
        break

    else:
        print("请输入1-6之间的数字。")

print("\n✅ 第23节完成！")
