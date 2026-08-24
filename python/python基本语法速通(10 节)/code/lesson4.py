# ============================================
# 第 4 课  让 Python 算账
# 结构：热身 → 主项目 → 加码
# 知识：+ - * / // % ** 、比较、逻辑、+=
# ============================================

print("######## 热身：口算对对碰 ########")
print("先自己心算，再看程序给的答案。")
print()

print("7 + 8        =", 7 + 8)
print("20 - 3       =", 20 - 3)
print("6 * 9        =", 6 * 9)
print("17 / 2       =", 17 / 2)     # 一定是小数
print("17 // 2      =", 17 // 2)    # 整除
print("17 % 2       =", 17 % 2)     # 余数
print("2 ** 8       =", 2 ** 8)     # 乘方：256
print("3 + 2 * 4    =", 3 + 2 * 4)  # 先乘后加 = 11
print("(3 + 2) * 4  =", (3 + 2) * 4)
print()

print("比较（结果只有 True / False）：")
print("10 > 3   ", 10 > 3)
print("10 == 10 ", 10 == 10)
print("10 != 7  ", 10 != 7)
print("10 >= 10 ", 10 >= 10)
print()

print("逻辑：")
print("True and False =", True and False)
print("True or False  =", True or False)
print("not True       =", not True)
print()

# += 是「自己加上」
score = 80
score += 5    # 等价于 score = score + 5
print("80 再加 5 分：", score)
print()
print("—— 热身结束，下面做主项目 ——")
print()

# ============================================
# 主项目：小店收银员
# ============================================
print("######## 主项目：小店收银员 ########")
print()
print("建议演示数据：单价 12.5，数量 3，折扣 0.8，实付 50")
print()

price = float(input("商品单价（元）："))
qty = int(input("购买数量："))
discount = float(input("折扣（1=不打折，0.8=八折）："))
paid = float(input("顾客实付（元）："))

original = price * qty
off = original * (1 - discount)
total = original * discount
change = paid - total
points = int(total)          # 消费 1 元积 1 分（丢掉小数）
per_item = total / qty

enough = paid >= total
exact = paid == total
is_deal = discount < 1
need_manager = (not enough) or (change > 100)

yuan = int(change)
ten_bills = yuan // 10
leftover = yuan % 10

print()
print("=" * 40)
print("【小票】")
print(f"单价     ：{price:.2f} 元")
print(f"数量     ：{qty}")
print(f"原价     ：{original:.2f} 元")
print(f"折扣     ：{discount} （优惠 {off:.2f} 元）")
print(f"应付     ：{total:.2f} 元")
print(f"实付     ：{paid:.2f} 元")
print(f"找零     ：{change:.2f} 元  （负数=还差钱）")
print(f"单件折后 ：{per_item:.2f} 元")
print(f"积分     ：{points} 分")
print("-" * 40)
print("【检查】")
print(f"钱够不够？     {enough}")
print(f"刚好付清？     {exact}")
print(f"本单有折扣？   {is_deal}")
print(f"需要店长确认？ {need_manager}")
print(f"找零 {yuan} 元 = {ten_bills} 张十元 + {leftover} 元零头")
print("=" * 40)
print()
print("—— 主项目结束，下面是加码（选做）——")
print()

# ============================================
# 加码 1：秒数拆成时、分、秒
# ============================================
print("######## 加码 1：时长换算 ########")
total_sec = int(input("请输入总秒数（例如 3723）："))
hours = total_sec // 3600
remain = total_sec % 3600
minutes = remain // 60
secs = remain % 60
print(f"{total_sec} 秒 = {hours} 小时 {minutes} 分 {secs} 秒")
print()

# ============================================
# 加码 2：圆的周长和面积
# ============================================
print("######## 加码 2：圆的周长和面积 ########")
r = float(input("圆的半径："))
pi = 3.14159
zhou = 2 * pi * r
mian = pi * r ** 2
print(f"周长 ≈ {zhou:.2f}")
print(f"面积 ≈ {mian:.2f}")
print()
print("公式：周长 = 2πr ，面积 = πr²（r ** 2）")
