# ============================================
# 第 9 课  装东西的盒子
# 结构：热身 → 主项目 → 加码
# 知识：列表、索引、append/remove/in/len、修改、遍历
# ============================================

print("######## 热身：预置名单 ########")
names = ["小明", "小红", "小刚", "小美"]
print("原始名单：", names)
print("第 1 个 names[0] =", names[0])
print("最后 1 个 names[-1] =", names[-1])
print("长度 len =", len(names))
print()

names.append("小李")
print("append 小李：", names)

names[1] = "小虹"     # 按位置修改
print("把下标 1 改成小虹：", names)

if "小刚" in names:
    names.remove("小刚")
print("remove 小刚：", names)

print()
print("带序号遍历：")
for i in range(len(names)):
    print(f"  {i + 1}. {names[i]}")
print()
print("—— 热身结束，下面做主项目 ——")
print()

# ============================================
# 主项目：购物清单小管家
# ============================================
cart = []

print("######## 主项目：购物清单小管家 ########")
print("命令：")
print("  add   添加")
print("  del   按名称删除")
print("  no    按序号删除（从 1 开始）")
print("  edit  按序号改名")
print("  show  查看")
print("  find  查询某件在不在")
print("  quit  退出")
print()

while True:
    cmd = input("请输入命令：")

    if cmd == "add":
        item = input("要添加的商品：")
        if item in cart:
            print(f"「{item}」已经在清单里了。")
        else:
            cart.append(item)
            print(f"已添加。现在 {len(cart)} 件。")

    elif cmd == "del":
        item = input("要删除的商品：")
        if item in cart:
            cart.remove(item)
            print(f"已删除：{item}")
        else:
            print(f"清单里没有「{item}」。")

    elif cmd == "no":
        if len(cart) == 0:
            print("清单是空的。")
        else:
            k = int(input("删除第几件（从 1 开始）："))
            if k >= 1 and k <= len(cart):
                gone = cart[k - 1]
                # 用 pop 按位置删（没有学函数定义，pop 是列表自带方法）
                cart.pop(k - 1)
                print(f"已删除第 {k} 件：{gone}")
            else:
                print("序号超出范围。")

    elif cmd == "edit":
        if len(cart) == 0:
            print("清单是空的。")
        else:
            k = int(input("修改第几件（从 1 开始）："))
            if k >= 1 and k <= len(cart):
                new_name = input("改成什么：")
                cart[k - 1] = new_name
                print("已修改。")
            else:
                print("序号超出范围。")

    elif cmd == "show":
        if len(cart) == 0:
            print("清单是空的，快去 add。")
        else:
            print("-" * 40)
            print("【我的购物清单】")
            for i in range(len(cart)):
                print(f"  {i + 1}. {cart[i]}")
            print(f"一共 {len(cart)} 件")
            print("-" * 40)

    elif cmd == "find":
        item = input("找什么：")
        if item in cart:
            print(f"找到了，它是第 {cart.index(item) + 1} 件。")
        else:
            print("没有这件。")

    elif cmd == "quit":
        print()
        print("谢谢使用！")
        if len(cart) > 0:
            print("最终清单：", "、".join(cart))
        break

    else:
        print("不认识这个命令。")

    print()

print("—— 主项目结束，下面是加码（选做）——")
print()

# ============================================
# 加码：随机点名器
# ============================================
import random

print("######## 加码：随机点名器 ########")
class_list = ["小明", "小红", "小刚", "小美", "小李", "小华"]
print("班级名单：", class_list)
print("输入 n 点一名，输入 q 结束。")

picked = []
while True:
    cmd = input("n 点名 / q 结束：")
    if cmd == "q":
        break
    if cmd != "n":
        print("请输入 n 或 q。")
        continue
    if len(picked) == len(class_list):
        print("全班都点过了，名单重置。")
        picked = []
    # 抽出一个还没点过的
    lucky = random.choice(class_list)
    while lucky in picked:
        lucky = random.choice(class_list)
    picked.append(lucky)
    print(f"👉 点到：{lucky}    已点 {len(picked)}/{len(class_list)}")

print("已点过的人：", picked)
print()
print("列表要点：索引从 0 起；增 append；删 remove/pop；改 cart[i]=；查 in。")
