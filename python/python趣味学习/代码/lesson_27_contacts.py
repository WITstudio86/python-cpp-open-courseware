# ============================================================
# 第27节：综合练习：通讯录小管家
# 适合：10-12 岁 Python 初学者
# ============================================================

# 一、数据结构：列表里放字典
print("=== 一、通讯录数据结构 ===")

# 每个联系人是一个字典，整个通讯录是一个列表
contacts = [
    {"姓名": "小明", "电话": "13800138001", "关系": "同学"},
    {"姓名": "小红", "电话": "13800138002", "关系": "朋友"},
    {"姓名": "王老师", "电话": "13800138003", "关系": "老师"},
]

print(f"通讯录有 {len(contacts)} 个联系人：")
for c in contacts:
    print(f"  {c['姓名']:6s} | {c['电话']:15s} | {c['关系']}")

# 二、查找联系人
print("\n=== 二、查找联系人 ===")

def find_contact(contacts, name):
    """在通讯录中查找联系人，找到了返回字典，找不到返回 None"""
    for contact in contacts:
        if contact["姓名"] == name:
            return contact
    return None

# 测试查找
name = "小明"
result = find_contact(contacts, name)
if result:
    print(f"找到了！{result['姓名']}，电话：{result['电话']}")
else:
    print(f"通讯录中没有「{name}」")

name = "小李"
result = find_contact(contacts, name)
if result:
    print(f"找到了！{result['姓名']}，电话：{result['电话']}")
else:
    print(f"通讯录中没有「{name}」")

# 三、添加联系人
print("\n=== 三、添加联系人 ===")

new_name = "小刚"
existing = find_contact(contacts, new_name)
if existing:
    print(f"「{new_name}」已存在！")
else:
    contacts.append({"姓名": new_name, "电话": "13900001111", "关系": "同学"})
    print(f"✅ 已添加「{new_name}」")

print("通讯录更新后：", len(contacts), "人")

# 四、删除联系人
print("\n=== 四、删除联系人 ===")

name_to_delete = "小刚"
for i, c in enumerate(contacts):
    if c["姓名"] == name_to_delete:
        contacts.pop(i)
        print(f"✅ 已删除「{name_to_delete}」")
        break
else:
    print(f"未找到「{name_to_delete}」")

# ============================================================
# 综合小挑战：通讯录小管家
# ============================================================

print("\n" + "=" * 40)
print("  综合挑战：📞 通讯录小管家")
print("=" * 40)

# 预设联系人
contacts = [
    {"姓名": "小明", "电话": "13800138001"},
    {"姓名": "小红", "电话": "13800138002"},
]

while True:
    print("\n--- 📞 功能菜单 ---")
    print("  1. 添加联系人")
    print("  2. 查找联系人")
    print("  3. 显示全部联系人")
    print("  4. 删除联系人")
    print("  5. 修改联系人")
    print("  6. 退出程序")
    print("-" * 25)

    choice = input("请选择功能 (1-6): ").strip()

    if choice == "1":
        # 添加联系人
        print("\n--- 添加联系人 ---")
        name = input("姓名: ").strip()
        phone = input("电话: ").strip()

        if not name or not phone:
            print("❌ 姓名和电话不能为空！")
            continue

        existing = find_contact(contacts, name)
        if existing:
            print(f"⚠️「{name}」已存在！电话: {existing['电话']}")
            overwrite = input("是否覆盖？(y/n): ").strip().lower()
            if overwrite == "y":
                existing["电话"] = phone
                print("✅ 已更新！")
        else:
            contacts.append({"姓名": name, "电话": phone})
            print(f"✅ 已添加「{name}」！")

    elif choice == "2":
        # 查找联系人
        print("\n--- 查找联系人 ---")
        name = input("请输入要查找的姓名: ").strip()
        result = find_contact(contacts, name)
        if result:
            print(f"📞 找到联系人：{result['姓名']} - {result['电话']}")
        else:
            print(f"❌ 通讯录中没有「{name}」")

    elif choice == "3":
        # 显示全部联系人
        print("\n--- 📋 全部联系人 ---")
        if len(contacts) == 0:
            print("📭 通讯录是空的，快去添加联系人吧！")
        else:
            print(f"共有 {len(contacts)} 个联系人:\n")
            print(f"{'序号':<6}{'姓名':<12}{'电话':<15}")
            print("-" * 33)
            for i, c in enumerate(contacts, 1):
                print(f"{i:<6}{c['姓名']:<12}{c['电话']:<15}")

    elif choice == "4":
        # 删除联系人
        print("\n--- 删除联系人 ---")
        name = input("请输入要删除的联系人姓名: ").strip()
        found = False
        for i, c in enumerate(contacts):
            if c["姓名"] == name:
                confirm = input(f"确认删除「{name}」？(y/n): ").strip().lower()
                if confirm == "y":
                    contacts.pop(i)
                    print(f"✅ 已删除「{name}」")
                else:
                    print("已取消删除。")
                found = True
                break
        if not found:
            print(f"❌ 通讯录中没有「{name}」")

    elif choice == "5":
        # 修改联系人
        print("\n--- 修改联系人 ---")
        name = input("请输入要修改的联系人姓名: ").strip()
        result = find_contact(contacts, name)
        if result:
            print(f"当前信息：{result['姓名']} - {result['电话']}")
            new_phone = input("请输入新电话（直接回车保持不变）: ").strip()
            if new_phone:
                result["电话"] = new_phone
                print("✅ 修改成功！")
            else:
                print("未做修改。")
        else:
            print(f"❌ 通讯录中没有「{name}」")

    elif choice == "6":
        print("再见！👋")
        break

    else:
        print("⚠️ 请输入 1-6 之间的数字。")

print("\n✅ 第27节完成！")
