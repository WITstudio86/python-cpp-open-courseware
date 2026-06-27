import tkinter as tk

# ========================================
# 第 14 节：迷你记事本
# 知识点：Text 控件、Scrollbar 滚动条、
#         insert() / get() / delete() 三大方法
# ========================================

# 创建主窗口
root = tk.Tk()
root.title("迷你记事本")          # 窗口标题
root.geometry("500x400")          # 宽 500，高 400 像素

# ========== 多行文本框 + 滚动条 ==========
# 用 Frame 容器把 Text 和 Scrollbar 组合在一起
frame = tk.Frame(root)
frame.pack(fill="both", expand=True, padx=10, pady=(10, 5))

# 创建垂直滚动条，放在 Frame 的右侧，撑满高度
scrollbar = tk.Scrollbar(frame)
scrollbar.pack(side="right", fill="y")

# 创建 Text 多行文本框
# width/height 不用设，因为用了 fill="both" + expand=True 会自动撑满
# yscrollcommand=scrollbar.set  → 文字超出时，自动更新滚动条滑块位置
text = tk.Text(frame, font=("微软雅黑", 12),
               yscrollcommand=scrollbar.set)
text.pack(side="left", fill="both", expand=True)

# 关键！让滚动条也能控制文本框的滚动
# command=text.yview → 拖动滚动条时，文本框内容跟着滚动
# 这个和上面的 yscrollcommand 必须成对出现，称为「双向绑定」
scrollbar.config(command=text.yview)

# ========== 功能函数 ==========

def insert_demo():
    """插入一行演示文字到文本框末尾"""
    # "end" 表示文字末尾 → 相当于追加
    text.insert("end", "这是一条新记录...\n")

def clear_text():
    """清空文本框的全部内容"""
    # delete("1.0", "end") → 删除从第1行第0列到末尾的所有文字
    text.delete("1.0", "end")

def read_text():
    """读取文本框的全部内容，打印到控制台"""
    # get("1.0", "end-1c") → 获取全部文字
    # "end-1c" 是 "end 往前 1 个字符"，去掉末尾多余的换行符 \n
    content = text.get("1.0", "end-1c")
    print("=" * 30)
    print("📝 记事本内容：")
    print(content)
    print("=" * 30)

# ========== 按钮区域 ==========
btn_frame = tk.Frame(root)
btn_frame.pack(fill="x", padx=10, pady=5)

# 按钮 1：添加一行（绿色背景）
tk.Button(btn_frame, text="✏️ 添加一行", command=insert_demo,
          bg="#e8f5e9", font=("微软雅黑", 10)).pack(side="left", padx=5)

# 按钮 2：读取内容到控制台（蓝色背景）
tk.Button(btn_frame, text="📖 读取内容", command=read_text,
          bg="#e3f2fd", font=("微软雅黑", 10)).pack(side="left", padx=5)

# 按钮 3：清空文本框（粉色背景）
tk.Button(btn_frame, text="🗑️ 清空", command=clear_text,
          bg="#fce4ec", font=("微软雅黑", 10)).pack(side="left", padx=5)

# 底部提示标签
tip = tk.Label(root, text="💡 提示：点击「读取内容」后，查看 Python 控制台输出",
               fg="#888888", font=("微软雅黑", 9))
tip.pack(pady=(0, 8))

# 启动主循环（必须放在最后！）
root.mainloop()
