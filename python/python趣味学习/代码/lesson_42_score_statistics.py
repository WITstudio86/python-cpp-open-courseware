"""
========================================
课程 42：项目四 —— 成绩统计器
========================================
学习目标：
  1. 学会用列表存储一组数据
  2. 掌握排序、求最大值、最小值、平均值的方法
  3. 用函数封装不同的统计功能
  4. 学会生成格式化的成绩报告
========================================
"""


def input_scores():
    """
    让用户逐个输入成绩，返回一个成绩列表。
    输入 "done" 结束录入。
    """
    scores = []  # 空列表，用来存放成绩
    print("请输入学生成绩（小数或整数），输入 'done' 结束录入：")
    print("-" * 40)

    count = 1
    while True:
        user_input = input(f"请输入第 {count} 个成绩: ").strip()

        if user_input.lower() == "done":
            break  # 结束录入

        # 尝试将输入转换为数字
        try:
            score = float(user_input)
            if score < 0 or score > 100:
                print("⚠️  成绩应在 0~100 之间，请重新输入。")
                continue
            scores.append(score)  # 添加到列表中
            count += 1
        except ValueError:
            print("⚠️  请输入有效的数字，或者输入 'done' 结束。")

    return scores


def calculate_average(scores):
    """计算平均分"""
    if len(scores) == 0:
        return 0
    total = sum(scores)  # 求和
    avg = total / len(scores)  # 平均值 = 总和 / 个数
    return avg


def calculate_pass_rate(scores, pass_line=60):
    """计算及格率（默认60分及格）"""
    if len(scores) == 0:
        return 0
    pass_count = 0  # 及格人数
    for s in scores:
        if s >= pass_line:
            pass_count += 1
    rate = pass_count / len(scores) * 100
    return rate, pass_count


def classify_grades(scores):
    """
    按等级分类成绩
    A: 90~100  优秀
    B: 80~89   良好
    C: 70~79   中等
    D: 60~69   及格
    F: 0~59    不及格
    """
    grades = {"A": 0, "B": 0, "C": 0, "D": 0, "F": 0}
    for s in scores:
        if s >= 90:
            grades["A"] += 1
        elif s >= 80:
            grades["B"] += 1
        elif s >= 70:
            grades["C"] += 1
        elif s >= 60:
            grades["D"] += 1
        else:
            grades["F"] += 1
    return grades


def generate_report(scores):
    """根据成绩列表生成完整的成绩报告"""
    if len(scores) == 0:
        print("📭 没有输入任何成绩，无法生成报告。")
        return

    # 为了让原始列表不变，复制一份用于排序
    sorted_scores = sorted(scores, reverse=True)  # 从高到低排序
    highest = max(scores)  # 最高分
    lowest = min(scores)   # 最低分
    avg = calculate_average(scores)  # 平均分
    pass_rate, pass_count = calculate_pass_rate(scores)  # 及格率
    grades = classify_grades(scores)  # 等级分布
    total = len(scores)  # 总人数

    # ── 打印报告 ────────────────────────────
    print("\n" + "=" * 50)
    print("              📊  成绩统计报告  📊")
    print("=" * 50)
    print(f"  总人数：      {total} 人")
    print(f"  最高分：      {highest} 分")
    print(f"  最低分：      {lowest} 分")
    print(f"  平均分：      {avg:.2f} 分")
    print(f"  及格率：      {pass_rate:.1f}%（{pass_count}/{total} 人及格）")
    print("-" * 50)
    print("  等级分布：")
    print(f"    A（优秀，90~100）：{grades['A']} 人  {'★' * grades['A']}")
    print(f"    B（良好， 80~89 ）：{grades['B']} 人  {'★' * grades['B']}")
    print(f"    C（中等， 70~79 ）：{grades['C']} 人  {'★' * grades['C']}")
    print(f"    D（及格， 60~69 ）：{grades['D']} 人  {'★' * grades['D']}")
    print(f"    F（不及格，< 60 ）：{grades['F']} 人  {'★' * grades['F']}")
    print("-" * 50)
    print(f"  成绩排名（从高到低）：")
    for i, s in enumerate(sorted_scores, start=1):
        # 用☆标记前三名
        if i == 1:
            medal = "🥇"
        elif i == 2:
            medal = "🥈"
        elif i == 3:
            medal = "🥉"
        else:
            medal = "  "
        print(f"    {medal} 第{i}名：{s} 分")
    print("=" * 50)


def load_scores_from_file():
    """从文件中读取成绩列表（可选功能）"""
    filename = input("请输入文件名（如 scores.txt）: ").strip()
    scores = []
    try:
        with open(filename, "r", encoding="utf-8") as f:
            for line in f:
                line = line.strip()
                if line == "":
                    continue
                try:
                    score = float(line)
                    if 0 <= score <= 100:
                        scores.append(score)
                except ValueError:
                    pass  # 跳过不是数字的行
        if len(scores) > 0:
            print(f"✅ 从文件加载了 {len(scores)} 个成绩。")
        else:
            print("⚠️  文件中没有找到有效的成绩。")
    except FileNotFoundError:
        print(f"❌ 找不到文件 '{filename}'，请检查文件名。")
    return scores


def main():
    print("=" * 40)
    print("       📊  欢迎使用成绩统计器  📊")
    print("=" * 40)
    print("  1. 手动输入成绩")
    print("  2. 从文件读取成绩")
    print("-" * 40)

    while True:
        choice = input("请选择 (1/2): ").strip()
        if choice == "1":
            scores = input_scores()
            break
        elif choice == "2":
            scores = load_scores_from_file()
            break
        else:
            print("⚠️  请输入 1 或 2。")

    # 生成成绩报告
    generate_report(scores)


# ── 程序入口 ──────────────────────────────────
if __name__ == "__main__":
    main()


# ============================================================
# 练习题（试着修改代码来实现以下功能）：
# ============================================================
#
# 练习 1：自定义及格线
#   让用户在程序开始时输入自己想要的及格分数线（不一定是60分）。
#   提示：用 input() 读取分数，传给 calculate_pass_rate() 的 pass_line 参数。
#
# 练习 2：添加"中位数"统计
#   中位数是把成绩排好序后最中间的那个数（比平均数更能反映整体水平）。
#   提示：排序后，如果总人数是奇数，取正中间那个；
#   如果是偶数，取中间两个的平均值。
#
# 练习 3：成绩导出到文件
#   增加一个功能：将生成的报告保存到一个 .txt 文件中。
#   提示：可以把报告内容先拼成一个字符串，再用 write() 写入文件。
#
# ============================================================
# 综合小挑战：
# ============================================================
#   打造一个"班级成绩管理系统"：
#   - 支持录入多个科目（语文、数学、英语等）。
#   - 每个学生的成绩是一个字典，如 {"语文": 90, "数学": 85, "英语": 78}
#   - 可以按科目查看统计，也可以看总分排名。
#   - 用嵌套的循环和字典来实现。
#   提示：先设计好数据结构，再一步步实现功能。
# ============================================================
