# ============================================================
# 第32节：综合练习：制作工具函数库
# 适合：10-12 岁 Python 初学者
#
# 本节分两个文件：
#   my_tools.py     —— 工具函数库（本文件下半部分）
#   lesson_32_main.py —— 主程序（使用工具库）
#
# 导入方式：
#   import my_tools
#   my_tools.函数名()
# ============================================================

# ==========================================
# 第一部分：在同一个文件里定义所有工具函数
# （实际使用时，这些会放在单独的 my_tools.py 文件中）
# ==========================================

print("=" * 40)
print("  🧰 我的 Python 工具函数库")
print("=" * 40)

# ==========================================
# 显示类工具
# ==========================================

def print_line(char="-", length=30):
    """打印一条分隔线"""
    print(char * length)

def print_title(title, char="="):
    """打印一个带框的标题"""
    length = len(title) + 8
    print(char * length)
    print(f"    {title}")
    print(char * length)

def show_menu(title, options):
    """显示一个菜单
    options 是一个列表，如 ["查看成绩", "计算平均", "退出"]
    """
    print()
    print_line("=", 30)
    print(f"   {title}")
    print_line("=", 30)
    for i, option in enumerate(options, 1):
        print(f"   {i}. {option}")
    print_line("=", 30)

# ==========================================
# 数学类工具
# ==========================================

def add(a, b):
    """加法"""
    return a + b

def subtract(a, b):
    """减法"""
    return a - b

def multiply(a, b):
    """乘法"""
    return a * b

def divide(a, b):
    """除法，自动处理除零错误"""
    if b == 0:
        print("⚠️ 错误：不能除以 0！")
        return None
    return a / b

def is_even(n):
    """判断是否是偶数"""
    return n % 2 == 0

def is_odd(n):
    """判断是否是奇数"""
    return n % 2 != 0

def power(base, exp):
    """计算 base 的 exp 次方"""
    return base ** exp

# ==========================================
# 列表类工具
# ==========================================

def get_average(numbers):
    """计算列表中数字的平均值"""
    if len(numbers) == 0:
        return 0
    return sum(numbers) / len(numbers)

def get_max_min(numbers):
    """返回列表的最大值和最小值"""
    if len(numbers) == 0:
        return None, None
    return max(numbers), min(numbers)

def count_pass(scores, pass_line=60):
    """统计及格人数"""
    count = 0
    for s in scores:
        if s >= pass_line:
            count += 1
    return count

def find_in_list(items, target):
    """在列表中查找目标，返回索引，找不到返回 -1"""
    for i, item in enumerate(items):
        if item == target:
            return i
    return -1

# ==========================================
# 判断类工具
# ==========================================

def grade(score):
    """根据分数返回评级"""
    if score < 0 or score > 100:
        return "无效分数"
    if score >= 90:
        return "优秀"
    elif score >= 80:
        return "良好"
    elif score >= 60:
        return "及格"
    else:
        return "不及格"

def is_passing(score, pass_line=60):
    """判断是否及格"""
    return score >= pass_line

# ==========================================
# 字符串类工具
# ==========================================

def reverse_string(s):
    """反转字符串"""
    return s[::-1]

def count_char(s, char):
    """统计字符串中某个字符出现的次数"""
    return s.count(char)

def is_palindrome(s):
    """判断字符串是否是回文（正着读反着读一样）"""
    s = s.lower().replace(" ", "")  # 去掉空格，统一小写
    return s == s[::-1]

# ==========================================
# 字典类工具
# ==========================================

def safe_get(d, key, default="未知"):
    """安全地在字典中查找，找不到返回默认值"""
    return d.get(key, default)

def merge_dicts(d1, d2):
    """合并两个字典（d2 的值会覆盖 d1 中相同的 key）"""
    result = d1.copy()
    result.update(d2)
    return result

# ==========================================
# 第二部分：使用工具库
# ==========================================

print("\n=== 1. 显示类工具 ===")

print_title("我的工具库")
print_line("~")

show_menu("功能选择", [
    "查看成绩",
    "计算平均分",
    "判断奇偶",
    "字符串操作",
    "退出程序"
])

print("\n=== 2. 数学类工具 ===")

print(f"3 + 5 = {add(3, 5)}")
print(f"10 - 4 = {subtract(10, 4)}")
print(f"6 × 8 = {multiply(6, 8)}")
print(f"15 ÷ 3 = {divide(15, 3)}")
print(f"10 ÷ 0 = {divide(10, 0)}")
print(f"2 的 10 次方 = {power(2, 10)}")

print(f"\n4 是偶数吗？{is_even(4)}")
print(f"7 是偶数吗？{is_even(7)}")
print(f"5 是奇数吗？{is_odd(5)}")

print("\n=== 3. 列表类工具 ===")

scores = [95, 88, 92, 76, 45, 83, 90, 67]
print(f"成绩：{scores}")
print(f"平均分：{get_average(scores):.1f}")

hi, lo = get_max_min(scores)
print(f"最高分：{hi}，最低分：{lo}")
print(f"及格人数（>=60）：{count_pass(scores)}")
print(f"优秀人数（>=90）：{count_pass(scores, 90)}")

idx = find_in_list(scores, 100)
if idx >= 0:
    print(f"100 分在索引 {idx}")
else:
    print("没有 100 分的成绩")

print("\n=== 4. 判断类工具 ===")

for s in [95, 85, 72, 55, -5]:
    print(f"  {s} 分 → {grade(s)}, {'及格' if is_passing(s) else '不及格'}")

print("\n=== 5. 字符串类工具 ===")

text = "hello world"
print(f"'{text}' 反转：{reverse_string(text)}")
print(f"'{text}' 中 'l' 出现了 {count_char(text, 'l')} 次")

# 回文判断
for word in ["racecar", "hello", "上海自来水来自海上"]:
    if is_palindrome(word):
        print(f"✅ '{word}' 是回文！")
    else:
        print(f"❌ '{word}' 不是回文。")

print("\n=== 6. 字典类工具 ===")

info = {"姓名": "小明", "年龄": 12}
print(f"查找'姓名'：{safe_get(info, '姓名')}")
print(f"查找'身高'：{safe_get(info, '身高', '未记录')}")

extra = {"身高": 155, "爱好": "编程"}
merged = merge_dicts(info, extra)
print(f"合并后：{merged}")

# ============================================================
# 练习题
# ============================================================

print("\n" + "=" * 40)
print("  课堂练习")
print("=" * 40)

# 练习1：使用工具库函数
print("\n【练习1】用工具库算一下：")
print(f"100 + 200 = {add(100, 200)}")
print(f"50 × 8 = {multiply(50, 8)}")
print(f"3 的 5 次方 = {power(3, 5)}")

# 练习2：成绩分析
print("\n【练习2】用工具库分析成绩：")
my_scores = [88, 95, 72, 83, 90, 67, 100]
print(f"成绩：{my_scores}")
print(f"平均分：{get_average(my_scores):.1f}")
print(f"最高分：{max(my_scores)}，最低分：{min(my_scores)}")
print(f"及格人数：{count_pass(my_scores)}")
print("评级：")
for i, s in enumerate(my_scores, 1):
    print(f"  {i}. {s} 分 → {grade(s)}")

# 练习3：字符串操作
print("\n【练习3】字符串工具：")
msg = "Python is fun!"
print(f"原句：{msg}")
print(f"反转：{reverse_string(msg)}")
print(f"字母 'n' 出现了 {count_char(msg, 'n')} 次")

# ============================================================
# 综合小挑战：用工具库搭建成绩管理系统
# ============================================================

print("\n" + "=" * 40)
print("  综合挑战：📊 成绩管理系统")
print("=" * 40)

# 用工具库搭建完整程序
all_scores = {
    "小明": [95, 88, 92],
    "小红": [78, 85, 90],
    "小刚": [65, 72, 58],
    "小丽": [100, 98, 96]
}

print_title("全班成绩报告")

# 计算每个人的统计
print(f"{'姓名':<8}{'平均分':<8}{'最高':<6}{'最低':<6}{'评级':<10}")
print_line("-", 40)
for name, scores in all_scores.items():
    avg = get_average(scores)
    hi, lo = get_max_min(scores)
    g = grade(avg)
    print(f"{name:<8}{avg:<8.1f}{hi:<6}{lo:<6}{g:<10}")

# 全班汇总
all_scores_list = []
for scores in all_scores.values():
    all_scores_list.extend(scores)

print_line("=", 40)
print(f"\n📊 全班汇总：")
print(f"  总人数：{len(all_scores)} 人")
print(f"  总成绩数：{len(all_scores_list)} 个")
print(f"  全班平均分：{get_average(all_scores_list):.1f}")
print(f"  全班最高分：{max(all_scores_list)}")
print(f"  全班最低分：{min(all_scores_list)}")
print(f"  及格率：{count_pass(all_scores_list)/len(all_scores_list)*100:.1f}%")

# 优秀学生榜
print(f"\n🏆 优秀学生榜（平均分 >= 90）：")
for name, scores in all_scores.items():
    if get_average(scores) >= 90:
        print(f"  🌟 {name}（平均 {get_average(scores):.1f} 分）")

# 需要加油的同学
print(f"\n💪 需要加油的同学（有不及格的）：")
for name, scores in all_scores.items():
    for s in scores:
        if s < 60:
            print(f"  {name} 有 {s} 分不及格，要加油哦！")
            break  # 一个人只显示一次

print("\n✅ 第32节完成！")
print("\n🎉 恭喜你完成了函数部分的全部学习！")
print("你已经是 Python 小工程师了！")
