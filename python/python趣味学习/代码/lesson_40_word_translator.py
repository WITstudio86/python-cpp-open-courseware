"""
========================================
课程 40：项目二 —— 单词翻译本
========================================
学习目标：
  1. 学会用字典（dict）存储键值对数据
  2. 掌握 while 循环 + 菜单制作交互程序
  3. 学会用文件读写（open/read/write）保存数据
  4. 了解 try-except 处理文件不存在的情况
========================================
"""

import os  # 导入系统模块，用于检查文件是否存在

# ── 单词本文件名 ──────────────────────────────
WORD_FILE = "wordbook.txt"  # 单词保存的文件名


def load_words():
    """从文件中加载已有的单词到字典中"""
    word_dict = {}  # 空字典，用来存放 英文→中文 的翻译

    # 如果文件不存在，返回空字典
    if not os.path.exists(WORD_FILE):
        return word_dict

    # 打开文件，读取每一行
    with open(WORD_FILE, "r", encoding="utf-8") as f:
        for line in f:
            line = line.strip()  # 去掉两边的空格和换行符
            if line == "":
                continue  # 跳过空行
            parts = line.split("=")  # 用等号分割英文和中文
            if len(parts) == 2:
                english = parts[0].strip()
                chinese = parts[1].strip()
                word_dict[english] = chinese  # 存入字典

    return word_dict


def save_words(word_dict):
    """将字典中的所有单词保存到文件"""
    with open(WORD_FILE, "w", encoding="utf-8") as f:
        for english, chinese in word_dict.items():
            f.write(f"{english} = {chinese}\n")  # 每行格式：英文 = 中文
    print("💾 单词已保存到文件！")


def show_all_words(word_dict):
    """显示所有单词"""
    if len(word_dict) == 0:
        print("📭 单词本还是空的，快去添加单词吧！")
        return

    print("\n" + "=" * 40)
    print("📖 当前单词本中的所有单词：")
    print("-" * 40)
    for i, (english, chinese) in enumerate(word_dict.items(), start=1):
        print(f"  {i}. {english} → {chinese}")
    print("-" * 40)
    print(f"共 {len(word_dict)} 个单词")


def add_word(word_dict):
    """添加一个新单词"""
    english = input("请输入英文单词: ").strip()
    if english == "":
        print("⚠️  英文单词不能为空哦！")
        return

    if english in word_dict:
        print(f"⚠️  '{english}' 已经存在了（中文意思：{word_dict[english]}）")
        return

    chinese = input("请输入中文意思: ").strip()
    if chinese == "":
        print("⚠️  中文意思不能为空哦！")
        return

    word_dict[english] = chinese
    print(f"✅ 已添加：{english} → {chinese}")


def search_word(word_dict):
    """查询单词的中文意思"""
    english = input("请输入要查询的英文单词: ").strip()
    if english in word_dict:
        print(f"🔍 查询结果：{english} → {word_dict[english]}")
    else:
        print(f"😕 抱歉，没找到单词 '{english}'，请先添加它。")


def delete_word(word_dict):
    """删除一个单词"""
    english = input("请输入要删除的英文单词: ").strip()
    if english in word_dict:
        chinese = word_dict.pop(english)  # 从字典中移除
        print(f"🗑️  已删除：{english} → {chinese}")
    else:
        print(f"😕 没找到单词 '{english}'，无法删除。")


def modify_word(word_dict):
    """修改一个单词的中文意思"""
    english = input("请输入要修改的英文单词: ").strip()
    if english in word_dict:
        old_chinese = word_dict[english]
        new_chinese = input(f"当前意思：{old_chinese}\n请输入新的中文意思: ").strip()
        if new_chinese == "":
            print("⚠️  中文意思不能为空，修改取消。")
            return
        word_dict[english] = new_chinese
        print(f"✏️  已修改：{english} → {new_chinese}")
    else:
        print(f"😕 没找到单词 '{english}'，请先添加它。")


def show_menu():
    """显示功能菜单"""
    print("\n" + "=" * 40)
    print("        📚  单词翻译本  📚")
    print("=" * 40)
    print("  1. 添加单词")
    print("  2. 查询单词")
    print("  3. 显示全部单词")
    print("  4. 删除单词")
    print("  5. 修改单词")
    print("  6. 保存到文件")
    print("  7. 退出程序")
    print("-" * 40)


def main():
    """主程序"""
    print("=" * 40)
    print("     📚  欢迎使用单词翻译本  📚")
    print("=" * 40)

    # 启动时从文件加载已有的单词
    word_dict = load_words()
    if len(word_dict) > 0:
        print(f"✅ 已从文件中加载了 {len(word_dict)} 个单词。")
    else:
        print("📭 单词本目前是空的，开始添加单词吧！")

    while True:
        show_menu()
        choice = input("请选择功能 (1-7): ").strip()

        if choice == "1":
            add_word(word_dict)

        elif choice == "2":
            search_word(word_dict)

        elif choice == "3":
            show_all_words(word_dict)

        elif choice == "4":
            delete_word(word_dict)

        elif choice == "5":
            modify_word(word_dict)

        elif choice == "6":
            save_words(word_dict)

        elif choice == "7":
            # 退出前自动保存
            if len(word_dict) > 0:
                save_confirm = input("退出前要保存单词吗？(y/n): ").strip().lower()
                if save_confirm == "y":
                    save_words(word_dict)
            print("感谢使用单词翻译本，再见！👋")
            break

        else:
            print("⚠️  输入有误，请输入 1~7 之间的数字。")


# ── 程序入口 ──────────────────────────────────
if __name__ == "__main__":
    main()


# ============================================================
# 练习题（试着修改代码来实现以下功能）：
# ============================================================
#
# 练习 1：反向查询（中→英）
#   增加一个新功能：输入中文，查出对应的英文单词。
#   提示：遍历字典，找到中文匹配的键；注意可能有多个英文对应同一个中文。
#
# 练习 2：单词测验模式
#   增加一个"测验"菜单项，随机显示一个中文，让用户输入英文。
#   答对加分，答错显示正确答案。
#   提示：用 random.choice(list(word_dict.items())) 随机选题。
#
# 练习 3：导入导出
#   增加"批量导入"功能，让用户粘贴多行"英文=中文"格式的文本，
#   一次性加入单词本。
#   提示：用 input() 读取多行直到空行，逐行解析。
#
# ============================================================
# 综合小挑战：
# ============================================================
#   打造一个"智能单词本"：
#   - 支持分类标签（如"动物"、"食物"、"颜色"），每个单词可以有多个标签。
#   - 可以按分类浏览单词。
#   - 测验时可以选择特定分类来练习。
#   提示：单词存储格式改为 "英文=中文#标签1,标签2"；
#   用另一个字典记录标签信息。
# ============================================================
