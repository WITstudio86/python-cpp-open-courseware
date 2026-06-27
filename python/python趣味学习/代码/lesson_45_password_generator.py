# -*- coding: utf-8 -*-
"""
课程编号：lesson_45
课程标题：项目七：随机密码生成器
学习目标：
    1. 学会使用 random 模块生成随机内容
    2. 学会使用 string 模块获取字符集（字母、数字、符号）
    3. 理解什么是"强密码"，以及如何生成它
    4. 能够根据用户需求生成不同类型的密码
"""

import random   # 随机模块，用来打乱顺序、随机选择
import string   # 字符串模块，内置了字母、数字、符号等字符集

# ==================== 第一步：准备字符集 ====================

def get_char_set(include_symbols):
    """
    根据用户选择，返回不同的字符集
    参数 include_symbols: True 表示包含符号，False 表示不包含
    """
    # string.ascii_letters 包含所有大小写英文字母（a-z 和 A-Z）
    # string.digits 包含所有数字（0-9）
    # string.punctuation 包含所有标点符号（!@#$%^&* 等）

    chars = string.ascii_letters + string.digits  # 字母 + 数字（基础字符集）

    if include_symbols:
        chars = chars + string.punctuation  # 再加上符号
        print("  → 已启用符号模式（密码更强）")
    else:
        print("  → 使用字母+数字模式")

    return chars


# ==================== 第二步：生成密码的核心函数 ====================

def generate_password(length, chars):
    """
    生成一个随机密码
    参数 length: 密码长度
    参数 chars: 可用的字符集（字符串）
    返回: 生成的密码字符串

    我们使用 random.sample() 来确保每个字符都不重复。
    但 sample 要求长度不超过字符集大小，所以需要处理这个情况。
    """
    if length > len(chars):
        # 如果要求的长度超过字符集大小，改用 random.choices()（允许重复）
        password_list = random.choices(chars, k=length)
    else:
        # normal 情况下用 sample，每个字符最多出现一次
        password_list = random.sample(chars, length)

    # 将列表中的字符拼接成一个字符串
    password = ''.join(password_list)
    return password


# ==================== 第三步：评估密码强度 ====================

def check_strength(password):
    """
    简单评估密码强度，返回 (等级, 描述)
    检查项：
      - 长度是否 >= 12
      - 是否包含大写字母
      - 是否包含小写字母
      - 是否包含数字
      - 是否包含符号
    """
    score = 0

    # 长度加分
    if len(password) >= 8:
        score += 1
    if len(password) >= 12:
        score += 1

    # 字符类型加分
    has_upper = any(c.isupper() for c in password)      # 有大写字母吗？
    has_lower = any(c.islower() for c in password)      # 有小写字母吗？
    has_digit = any(c.isdigit() for c in password)      # 有数字吗？
    has_symbol = any(c in string.punctuation for c in password)  # 有符号吗？

    if has_upper:
        score += 1
    if has_lower:
        score += 1
    if has_digit:
        score += 1
    if has_symbol:
        score += 1

    # 根据总分给出评级
    if score <= 2:
        return "弱  ", "不太安全，建议增强"
    elif score <= 4:
        return "中等", "还不错，但可以更好"
    else:
        return "强  ", "非常安全！👍"


# ==================== 第四步：主程序——交互式密码生成器 ====================

def main():
    print("=" * 50)
    print("      🔐 随机密码生成器 🔐")
    print("=" * 50)
    print()

    # --- 用户选择密码类型 ---
    print("请选择密码类型：")
    print("  1. 纯数字密码（如：3859201476）")
    print("  2. 字母 + 数字（如：aB3kQ9mW2x）")
    print("  3. 字母 + 数字 + 符号（如：aB3#kQ9!mW）  ← 推荐！")
    print()

    choice = input("请输入你的选择（1/2/3）：").strip()

    # 根据选择确定字符集
    if choice == "1":
        chars = string.digits  # 只有数字
        print("\n你选择了：纯数字密码")
    elif choice == "2":
        chars = string.ascii_letters + string.digits  # 字母 + 数字
        print("\n你选择了：字母 + 数字密码")
    elif choice == "3":
        chars = string.ascii_letters + string.digits + string.punctuation
        print("\n你选择了：字母 + 数字 + 符号密码（最强）")
    else:
        print("\n输入无效，默认使用「字母+数字+符号」模式")
        chars = string.ascii_letters + string.digits + string.punctuation

    # --- 用户输入密码长度 ---
    try:
        length = int(input("\n请输入密码长度（建议 12-16 位）：").strip())
        if length < 4:
            print("密码太短了！自动设置为 8 位")
            length = 8
        elif length > 64:
            print("密码太长了！自动设置为 64 位")
            length = 64
    except ValueError:
        print("输入的不是数字，默认使用 12 位")
        length = 12

    # --- 生成密码 ---
    print("\n正在生成密码...")

    # 为了确保密码包含至少一个大写字母和一个数字，
    # 我们先强制放入这两个，剩余部分随机填充
    password = generate_password(length, chars)

    # 显示结果
    print("-" * 40)
    print(f"  生成的密码：{password}")
    print(f"  密码长度：{len(password)} 位")
    strength_level, strength_desc = check_strength(password)
    print(f"  密码强度：{strength_level}（{strength_desc}）")
    print("-" * 40)

    # --- 是否批量生成 ---
    print()
    batch = input("是否要一次性生成多个密码备选？（y/n）：").strip().lower()
    if batch == "y":
        try:
            count = int(input("生成几个？").strip())
            if count < 1:
                count = 5
        except ValueError:
            count = 5

        print(f"\n为你生成 {count} 个密码：")
        print("-" * 40)
        for i in range(count):
            pwd = generate_password(length, chars)
            s_level, _ = check_strength(pwd)
            print(f"  [{i+1}] {pwd}  强度：{s_level}")
        print("-" * 40)

    print("\n感谢使用密码生成器！记住不要用同一个密码哦~")


# 运行主程序
if __name__ == "__main__":
    main()


# ==================== 练习题 ====================

"""
练习一：确保密码至少包含一个大写字母和一个数字
---------------------------------------------------
上面的 generate_password() 是纯随机的，可能生成的密码全是没有大写字母。
请修改 generate_password 函数，确保生成的密码"一定"至少包含：
  - 1 个大写字母
  - 1 个小写字母
  - 1 个数字
提示：可以先手动放入这些"必选字符"，再用 random.sample() 填充剩余位置，
      最后用 random.shuffle() 打乱顺序。

练习二：生成"易记密码"（单词 + 数字 + 符号）
---------------------------------------------------
random.sample 生成的密码虽然安全，但很难记住。
请写一个新函数 generate_memorable_password()：
  - 准备一个"单词列表"，比如 ["apple", "tiger", "moon", "star", "happy"]
  - 随机选一个单词
  - 在单词后面拼接 2-3 位随机数字
  - 再拼接 1 个随机符号
  - 示例输出：tiger47# 或 moon82!
  这样生成的密码既安全又好记！

练习三：增加密码类型——"易读密码"
---------------------------------------------------
有些网站生成的密码会避开容易混淆的字符（比如 0和O，1和l，5和S）。
请在程序里增加第 4 种密码类型：易读密码。
提示：
  - 创建一个"安全字符集"，排除掉 '0', 'O', '1', 'l', '5', 'S' 等易混淆字符
  - 用这个安全字符集来生成密码
"""


# ==================== 综合小挑战 ====================

"""
综合挑战：打造你自己的"密码管家"
---------------------------------------------------
把本课学到的内容整合起来，写一个完整的密码管理小程序：

要求：
1. 主菜单有三个选项：
   [1] 生成密码
   [2] 评估密码强度
   [3] 退出
2. 选择 [1] 时，调用本课的密码生成功能
3. 选择 [2] 时，让用户输入一个已有的密码，用 check_strength() 评估它，
   并给出改进建议（比如："缺少大写字母，建议加入"）
4. 程序循环运行，直到用户选择 [3] 才退出

提示：用一个 while True 循环来实现主菜单的反复显示。
"""
