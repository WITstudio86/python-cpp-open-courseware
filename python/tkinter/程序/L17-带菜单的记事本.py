import tkinter as tk
from tkinter import messagebox

# ========================================
# 第 17 节：带菜单的记事本 —— 像专业软件一样有菜单
# ========================================

root = tk.Tk()
root.title("记事本")
root.geometry("600x450")
root.configure(bg="#f5f5f5")

# ========== 一、创建顶部菜单栏 ==========

# 第 1 步：创建总菜单栏（Menu 控件作为菜单的容器）
menubar = tk.Menu(root)

# 第 2 步：将菜单栏挂载到窗口上（这一步很关键，没有它菜单不会显示！）
root.config(menu=menubar)

# ---------- "文件" 菜单 ----------
# tearoff=False 表示不允许把菜单拖出来变成独立窗口
file_menu = tk.Menu(menubar, tearoff=False)

def new_file():
    """新建文件 —— 弹出确认对话框，用户确认后清空文本区域"""
    result = messagebox.askyesno("新建文件", "当前内容未保存，确定要新建吗？")
    if result:
        # delete("1.0", "end") 删除从第1行第0列到末尾的所有文字
        text_area.delete("1.0", "end")

def open_file():
    """打开文件 —— 提示功能（暂无实际打开功能，后续可扩展）"""
    messagebox.showinfo("打开文件", "打开文件功能需要文件对话框，暂未实现。")

def save_file():
    """保存文件 —— 提示功能（暂无实际保存功能，后续可扩展）"""
    messagebox.showinfo("保存文件", "保存文件功能需要文件对话框，暂未实现。")

def quit_app():
    """退出程序 —— 弹出确认对话框，用户确认后才退出"""
    result = messagebox.askyesno("退出", "确定要退出记事本吗？")
    if result:
        root.quit()  # 关闭程序窗口

# add_command 方法：向菜单添加一个可点击的菜单项
#   label：菜单项显示的文字
#   command：点击菜单项后执行的函数
#   accelerator：在菜单项右边显示的快捷键提示（仅显示，不会真正绑定快捷键）
file_menu.add_command(label="新建", command=new_file, accelerator="Ctrl+N")
file_menu.add_command(label="打开", command=open_file, accelerator="Ctrl+O")
file_menu.add_command(label="保存", command=save_file, accelerator="Ctrl+S")
# add_separator 方法：添加一条分隔线，用于将相关菜单项分组
file_menu.add_separator()
file_menu.add_command(label="退出", command=quit_app, accelerator="Ctrl+Q")

# ---------- "编辑" 菜单 ----------
edit_menu = tk.Menu(menubar, tearoff=False)

def cut_text():
    """剪切 —— 提示功能（后续可对接系统剪贴板）"""
    messagebox.showinfo("剪切", "请先用鼠标选中文字，然后使用 Ctrl+X 剪切。")

def copy_text():
    """复制 —— 提示功能（后续可对接系统剪贴板）"""
    messagebox.showinfo("复制", "请先用鼠标选中文字，然后使用 Ctrl+C 复制。")

def paste_text():
    """粘贴 —— 提示功能（后续可对接系统剪贴板）"""
    messagebox.showinfo("粘贴", "请先复制文字，然后使用 Ctrl+V 粘贴。")

edit_menu.add_command(label="剪切", command=cut_text, accelerator="Ctrl+X")
edit_menu.add_command(label="复制", command=copy_text, accelerator="Ctrl+C")
edit_menu.add_command(label="粘贴", command=paste_text, accelerator="Ctrl+V")

# ---------- "帮助" 菜单 ----------
help_menu = tk.Menu(menubar, tearoff=False)

def show_about():
    """显示"关于"对话框 —— 使用 showinfo 弹出信息框"""
    messagebox.showinfo(
        "关于记事本",
        "简易记事本 v1.0\n\n"
        "用 Python + tkinter 制作\n\n"
        "祝贺你完成了 Tkinter 系列课程的全部内容！🎉"
    )

help_menu.add_command(label="关于", command=show_about)

# add_cascade 方法：将下拉菜单"挂"到菜单栏上
#   label：菜单栏上显示的文字
#   menu：要挂载的下拉菜单对象
menubar.add_cascade(label="文件", menu=file_menu)
menubar.add_cascade(label="编辑", menu=edit_menu)
menubar.add_cascade(label="帮助", menu=help_menu)

# ========== 二、创建右键弹出菜单（上下文菜单）==========

# 右键菜单是另一个独立的 Menu 对象，不挂载到菜单栏
popup_menu = tk.Menu(root, tearoff=False)

# 给右键菜单添加编辑功能（和顶部"编辑"菜单使用相同的命令函数）
popup_menu.add_command(label="剪切", command=cut_text)
popup_menu.add_command(label="复制", command=copy_text)
popup_menu.add_command(label="粘贴", command=paste_text)
popup_menu.add_separator()
popup_menu.add_command(label="全选",
                       command=lambda: messagebox.showinfo("全选", "使用 Ctrl+A 全选。"))

def show_popup(event):
    """
    在鼠标右键点击的位置弹出菜单
    event.x_root：鼠标在屏幕上的绝对 x 坐标（不是控件内部的坐标！）
    event.y_root：鼠标在屏幕上的绝对 y 坐标
    post(x, y)：在指定屏幕坐标显示弹出菜单
    """
    popup_menu.post(event.x_root, event.y_root)

# ========== 三、文本编辑区域 ==========

# Text 是多行文本编辑控件，适合做记事本的主体编辑区
# wrap="word"：按单词边界换行，不会在英文单词中间断开
# insertbackground：设置光标（插入点）的颜色
# padx/pady：文本框内部的内边距
text_area = tk.Text(root, wrap="word",
                    font=("Microsoft YaHei", 12),
                    bg="white", fg="#333333",
                    insertbackground="#333333",
                    padx=10, pady=10)
# fill="both", expand=True 让文本框填满窗口的剩余空间
text_area.pack(fill="both", expand=True, padx=10, pady=10)

# 插入初始提示文字
# insert("1.0", ...) 表示在第 1 行第 0 列插入文字（行号从 1 开始，列号从 0 开始）
text_area.insert("1.0", "欢迎使用简易记事本！\n\n"
                 "在这里输入你的文字吧～\n\n"
                 "💡 试试右键点击编辑区域，会有惊喜哦！")

# 将鼠标右键事件绑定到 Text 控件上
# <Button-3> 表示按下鼠标右键（Button-1 = 左键，Button-2 = 中键，Button-3 = 右键）
text_area.bind("<Button-3>", show_popup)

# ---------- 启动主循环 ----------
root.mainloop()
