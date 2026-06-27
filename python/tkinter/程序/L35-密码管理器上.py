import tkinter as tk
from tkinter import messagebox
import base64
import json
import os

# ========================================
# 第 35 节：密码管理器（上）
# 知识点：Entry 输入框 + base64 加密 + JSON 文件存储
# 成品：能加密保存密码的小工具
# 说明：本项目分两节课完成——
#       （上）本课：加密保存 + 查看已存密码的核心功能
#       （下）36节：删除密码、复制到剪贴板、主密码保护等
# ========================================

# ---------- 常量定义 ----------
# 密码数据文件的名字，保存在程序同目录下
DATA_FILE = "passwords.json"

# ---------- 数据操作函数 ----------
def load_data():
    """
    从 JSON 文件加载已保存的密码数据。
    返回一个列表，每个元素是一个字典：{"site": 网站, "user": 账号, "pwd": 加密后的密码}
    如果文件不存在，返回空列表（第一次运行程序时就是如此）。
    """
    if os.path.exists(DATA_FILE):
        with open(DATA_FILE, "r", encoding="utf-8") as f:
            return json.load(f)  # json.load 把 JSON 文件内容转成 Python 列表
    return []


def save_data(data):
    """
    将密码数据列表保存到 JSON 文件。
    ensure_ascii=False：允许保存中文（否则会被转义成 unicode 编码）
    indent=2：缩进 2 格，让文件内容排版好看、方便人类阅读
    """
    with open(DATA_FILE, "w", encoding="utf-8") as f:
        json.dump(data, f, ensure_ascii=False, indent=2)


def encrypt(plain_text):
    """
    用 base64 对明文进行加密。
    步骤：
    ① plain_text.encode("utf-8") —— 把字符串变成字节（bytes）
    ② base64.b64encode(...)       —— 把字节编码成 base64 字节
    ③ .decode("utf-8")            —— 把 base64 字节变回字符串（方便显示和存储）
    """
    return base64.b64encode(plain_text.encode("utf-8")).decode("utf-8")


def decrypt(encoded_text):
    """
    用 base64 对密文进行解密。
    步骤与加密相反：
    ① encoded_text.encode("utf-8") —— 字符串 → 字节
    ② base64.b64decode(...)        —— base64 字节 → 原始字节
    ③ .decode("utf-8")             —— 原始字节 → 明文字符串
    """
    return base64.b64decode(encoded_text.encode("utf-8")).decode("utf-8")


# ---------- 1. 创建主窗口 ----------
root = tk.Tk()
root.title("密码管理器")              # 窗口标题
root.geometry("520x580")             # 窗口大小
root.configure(bg="#f0f2f5")         # 背景色：浅灰蓝

# ---------- 2. 顶部标题 ----------
title_label = tk.Label(
    root,
    text="🔐 密码管理器",
    font=("Microsoft YaHei", 22, "bold"),
    bg="#f0f2f5",
    fg="#2c3e50"
)
title_label.pack(pady=(20, 5))

subtitle = tk.Label(
    root,
    text="加密保存你的秘密，只有你能查看！",
    font=("Microsoft YaHei", 10),
    bg="#f0f2f5",
    fg="#7f8c8d"
)
subtitle.pack(pady=(0, 15))

# ---------- 3. 输入表单区域 ----------
# 用一个白色的 Frame 把输入框框起来，看起来像一个卡片
card = tk.Frame(root, bg="#ffffff", relief="flat", bd=0)
card.pack(pady=10, padx=40, fill="x")

# 卡片内部加一点内边距（用空的 Label 撑开）
card_inner = tk.Frame(card, bg="#ffffff")
card_inner.pack(padx=25, pady=15, fill="x")

# 卡片标题
tk.Label(
    card_inner,
    text="📝 添加新密码",
    font=("Microsoft YaHei", 13, "bold"),
    bg="#ffffff",
    fg="#2c3e50"
).pack(anchor="w", pady=(0, 12))

# ---------- 3a. 网站输入行 ----------
row_site = tk.Frame(card_inner, bg="#ffffff")
tk.Label(
    row_site,
    text="网站",
    font=("Microsoft YaHei", 11),
    bg="#ffffff",
    fg="#555555",
    width=6,
    anchor="e"
).pack(side="left", padx=(0, 8))

site_entry = tk.Entry(
    row_site,
    width=32,
    font=("Microsoft YaHei", 11),
    relief="solid",
    bd=1
)
site_entry.pack(side="left")
row_site.pack(pady=5)

# ---------- 3b. 账号输入行 ----------
row_user = tk.Frame(card_inner, bg="#ffffff")
tk.Label(
    row_user,
    text="账号",
    font=("Microsoft YaHei", 11),
    bg="#ffffff",
    fg="#555555",
    width=6,
    anchor="e"
).pack(side="left", padx=(0, 8))

user_entry = tk.Entry(
    row_user,
    width=32,
    font=("Microsoft YaHei", 11),
    relief="solid",
    bd=1
)
user_entry.pack(side="left")
row_user.pack(pady=5)

# ---------- 3c. 密码输入行 ----------
row_pwd = tk.Frame(card_inner, bg="#ffffff")
tk.Label(
    row_pwd,
    text="密码",
    font=("Microsoft YaHei", 11),
    bg="#ffffff",
    fg="#555555",
    width=6,
    anchor="e"
).pack(side="left", padx=(0, 8))

pwd_entry = tk.Entry(
    row_pwd,
    width=32,
    font=("Microsoft YaHei", 11),
    show="*",         # 密码模式：输入的任何字符都显示为 *
    relief="solid",
    bd=1
)
pwd_entry.pack(side="left")
row_pwd.pack(pady=5)

# ---------- 4. 加密保存按钮 ----------
def add_password():
    """
    获取用户输入的网站、账号、密码，
    用 base64 加密密码后，追加保存到 JSON 文件中，
    然后清空输入框并刷新密码列表。
    """
    # 获取用户输入，并用 .strip() 去掉首尾空格
    site = site_entry.get().strip()
    user = user_entry.get().strip()
    pwd = pwd_entry.get().strip()

    # 校验：三个输入框都不能为空
    if not site or not user or not pwd:
        messagebox.showwarning("输入不完整", "请填写网站、账号和密码！")
        return

    # 加载已有数据
    data = load_data()

    # 构造一条新记录（密码被加密后保存！）
    new_record = {
        "site": site,
        "user": user,
        "pwd": encrypt(pwd)   # 重点：这里把明文密码加密后再存入！
    }
    data.append(new_record)

    # 保存到 JSON 文件
    save_data(data)

    # 清空三个输入框，方便输入下一条
    site_entry.delete(0, tk.END)
    user_entry.delete(0, tk.END)
    pwd_entry.delete(0, tk.END)

    # 提示保存成功
    messagebox.showinfo("保存成功", f"「{site}」的密码已加密保存！🔒")

    # 刷新下方的密码列表
    refresh_list()


# 添加按钮
add_btn = tk.Button(
    card_inner,
    text="🔒 加密保存",
    command=add_password,
    font=("Microsoft YaHei", 13, "bold"),
    bg="#3498db",               # 蓝色按钮
    fg="white",
    activebackground="#2980b9", # 鼠标按下时的颜色
    relief="flat",
    padx=30,
    pady=8,
    cursor="hand2"
)
add_btn.pack(pady=(15, 5))

# ---------- 5. 已保存密码列表区域 ----------
# 分隔标题
tk.Label(
    root,
    text="📋 已保存的密码",
    font=("Microsoft YaHei", 13, "bold"),
    bg="#f0f2f5",
    fg="#2c3e50"
).pack(pady=(15, 5), anchor="w", padx=45)

# 列表容器 Frame
list_container = tk.Frame(root, bg="#ffffff")
list_container.pack(pady=5, padx=40, fill="both", expand=True)

# Listbox：展示所有已保存的网站和账号
pwd_listbox = tk.Listbox(
    list_container,
    font=("Microsoft YaHei", 11),
    height=6,
    selectmode="single",   # 只能单选
    relief="flat",
    bd=0,
    highlightthickness=0,
    bg="#fafbfc",
    fg="#2c3e50",
    selectbackground="#d5e8fb",  # 选中项的背景色
    selectforeground="#2c3e50"   # 选中项的文字色
)
pwd_listbox.pack(side="left", fill="both", expand=True, padx=(10, 0), pady=10)

# 滚动条
scrollbar = tk.Scrollbar(list_container)
scrollbar.pack(side="right", fill="y", padx=(0, 5), pady=10)

# 将 Listbox 和滚动条关联起来
pwd_listbox.config(yscrollcommand=scrollbar.set)
scrollbar.config(command=pwd_listbox.yview)

# ---------- 6. 查看详情按钮 ----------
def show_detail():
    """
    当用户在列表中选择了一项后，
    解密该项的密码，并用弹窗显示完整信息。
    """
    # 获取用户选中的项的索引
    selection = pwd_listbox.curselection()
    if not selection:
        messagebox.showwarning("未选择", "请先在密码列表中选择一项！")
        return

    # 从列表中取数据
    data = load_data()
    index = selection[0]
    item = data[index]

    # 解密密码
    decrypted_pwd = decrypt(item["pwd"])

    # 弹窗显示完整信息
    messagebox.showinfo(
        f"🔍 {item['site']}",
        f"网站：{item['site']}\n"
        f"账号：{item['user']}\n"
        f"密码：{decrypted_pwd}"
    )


# 按钮行（查看详情）
btn_row = tk.Frame(root, bg="#f0f2f5")
btn_row.pack(pady=10, padx=40, fill="x")

detail_btn = tk.Button(
    btn_row,
    text="🔍 查看详情",
    command=show_detail,
    font=("Microsoft YaHei", 11),
    bg="#27ae60",               # 绿色按钮
    fg="white",
    activebackground="#219a52",
    relief="flat",
    padx=18,
    pady=6,
    cursor="hand2"
)
detail_btn.pack(side="left", padx=(0, 10))

# 复制密码按钮（挑战功能）
def copy_password():
    """
    将选中项的密码解密后复制到系统剪贴板。
    clipboard_append() 把文字放入剪贴板。
    """
    selection = pwd_listbox.curselection()
    if not selection:
        messagebox.showwarning("未选择", "请先在密码列表中选择一项！")
        return

    data = load_data()
    item = data[selection[0]]
    decrypted_pwd = decrypt(item["pwd"])

    # 先清空剪贴板，再放入密码
    root.clipboard_clear()
    root.clipboard_append(decrypted_pwd)

    messagebox.showinfo("已复制", f"「{item['site']}」的密码已复制到剪贴板！📋")


copy_btn = tk.Button(
    btn_row,
    text="📋 复制密码",
    command=copy_password,
    font=("Microsoft YaHei", 11),
    bg="#8e44ad",               # 紫色按钮
    fg="white",
    activebackground="#7d3c98",
    relief="flat",
    padx=18,
    pady=6,
    cursor="hand2"
)
copy_btn.pack(side="left")

# ---------- 7. 刷新列表函数 ----------
def refresh_list():
    """
    从 JSON 文件读取所有数据，更新 Listbox 的显示。
    列表中显示每一项的「网站 (账号)」格式。
    """
    pwd_listbox.delete(0, tk.END)  # 先清空列表中的所有项
    data = load_data()
    for item in data:
        # 格式化显示文字：bilibili.com (xiaoming)
        display_text = f"{item['site']}  ({item['user']})"
        pwd_listbox.insert(tk.END, display_text)


# ---------- 8. 程序启动时加载已有数据 ----------
refresh_list()

# ---------- 9. 启动主循环 ----------
root.mainloop()
