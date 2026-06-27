# 第 2 节 · Label 标签 —— 在窗口上显示文字

## 学习目标
- 学会创建 Label（标签），在窗口上显示文字
- 学会设置字体、颜色、大小
- 理解文字对齐方式（左对齐、居中、换行）
- 学会用 StringVar 让文字"活"起来 —— 动态改变 Label 的内容

## 本节课成品
一个「电子公告牌」—— 窗口上有不同样式的公告文字，还有一个可以动态变化的提示标签。

---

## 知识点讲解

### 什么是 Label？
Label 就像一个**贴纸**，你可以把它贴在窗口上，上面写着你想要的文字。比如通知、提示、标题……都可以用 Label 来显示。

Label 是 tkinter 里最常用、最简单的控件之一。它不能点击，只能"看"。

### 第 1 步：创建你的第一个 Label

```python
label = tk.Label(root, text="你好，世界！")
label.pack()
```

- `root` 是 Label 的"家"——也就是它贴在哪个窗口上
- `text="..."` 是 Label 上显示的文字
- `.pack()` 是把 Label "打包"放进窗口里（后面会学更多布局方式）

### 第 2 步：让文字更好看 —— 字体与颜色

```python
label = tk.Label(
    root,
    text="Hello, Tkinter!",
    font=("微软雅黑", 20, "bold"),  # 字体、大小、样式
    fg="#c0392b",                    # 文字颜色（foreground）
    bg="#f5f0e8"                     # 背景颜色（background）
)
```

| 参数 | 含义 | 示例 |
|------|------|------|
| `font` | 字体设置 | `("微软雅黑", 16, "bold")` |
| `fg` | 文字颜色 | `"red"`、`"#2980b9"` |
| `bg` | 背景颜色 | `"#fff3cd"`、`"lightyellow"` |

**font 的三个值：**
1. **字体名**：`"微软雅黑"`、`"宋体"`、`"Arial"`
2. **大小**：数字越大字越大，比如 `16`、`24`
3. **样式**（可选）：`"bold"`（加粗）、`"italic"`（斜体）、`"bold italic"`（加粗+斜体）

### 第 3 步：对齐与换行

有时候文字很长，需要换行显示；或者你想让文字靠左、居中、靠右。

```python
label = tk.Label(
    root,
    text="这是一段很长的文字，\n它会在窗口里换行显示。",
    font=("微软雅黑", 12),
    justify="left",      # 多行文字的对齐方式：left / center / right
    wraplength=300,      # 超过 300 像素自动换行
    anchor="w"           # 文字在 Label 区域内的锚点：w=西(左), e=东(右), center=居中
)
```

- **justify**：多行文字之间的对齐方式
- **wraplength**：设置最大宽度（像素），超过自动换行。跟 `\n` 手动换行不一样哦
- **anchor**：文字在整个 Label 区域里的位置。用方位表示：`"w"`（左）、`"e"`（右）、`"center"`（居中）、`"n"`（上）、`"s"`（下）

### 第 4 步：让文字"活"起来 —— StringVar

前面的 Label 文字写死就不能变了。如果想**动态改变** Label 上的文字怎么办？用 `StringVar`！

`StringVar` 就像一个**可以变魔术的盒子**——你改变盒子里的内容，Label 上的文字会自动跟着变！

```python
# 1. 创建一个 StringVar
var_text = tk.StringVar()
var_text.set("初始文字")

# 2. 绑定到 Label（注意是 textvariable，不是 text！）
label = tk.Label(root, textvariable=var_text)

# 3. 改变文字
var_text.set("新的文字！")  # Label 自动更新！
```

**对比：**
- `text="写死的文字"` —— 创建后不能改
- `textvariable=var_text` —— 绑定变量，变量改了 Label 就跟着变

---

## 完整代码

```python
import tkinter as tk

# ========================================
# 第 2 节：Label 标签 —— 电子公告牌
# ========================================

root = tk.Tk()
root.title("电子公告牌")
root.geometry("600x500")
root.configure(bg="#f5f0e8")

# --- 标题 Label：大号字体，深色 ---
title_label = tk.Label(
    root,
    text="📢 电子公告牌",
    font=("微软雅黑", 24, "bold"),
    fg="#2c3e50",
    bg="#f5f0e8"
)
title_label.pack(pady=15)

# --- 公告内容 Label：不同样式 ---
# Label 1: 通知类，红色文字
notice = tk.Label(
    root,
    text="【通知】明天下午 3 点有编程比赛！",
    font=("微软雅黑", 14),
    fg="#c0392b",
    bg="#f5f0e8"
)
notice.pack(pady=5)

# Label 2: 活动类，蓝色文字
activity = tk.Label(
    root,
    text="【活动】周末一起去科技馆参观～",
    font=("微软雅黑", 14, "italic"),
    fg="#2980b9",
    bg="#f5f0e8"
)
activity.pack(pady=5)

# Label 3: 提醒类，带背景色
reminder = tk.Label(
    root,
    text="⚠️ 别忘了带你的学生证！",
    font=("微软雅黑", 13),
    fg="#e67e22",
    bg="#fff3cd",
    padx=10,
    pady=5
)
reminder.pack(pady=10)

# --- 带边框的公告区域 ---
frame = tk.Frame(root, bg="#ffffff", relief="groove", bd=2)
frame.pack(pady=20, padx=40, fill="x")

long_text = tk.Label(
    frame,
    text="欢迎来到我们的公告牌！\n这里会发布最新的课程信息、\n活动通知和重要提醒。\n记得经常来看看哦~",
    font=("微软雅黑", 12),
    fg="#34495e",
    bg="#ffffff",
    justify="left",
    wraplength=400,
    padx=15,
    pady=15
)
long_text.pack()

# --- 用 StringVar 控制的动态 Label ---
var_text = tk.StringVar()
var_text.set("点击下方按钮可以修改这段文字哦 ↑")

dynamic_label = tk.Label(
    root,
    textvariable=var_text,  # ← 用 textvariable 绑定变量
    font=("微软雅黑", 11, "italic"),
    fg="#7f8c8d",
    bg="#f5f0e8"
)
dynamic_label.pack(pady=10)

# 按钮：点击后修改 var_text 的值
def change_text():
    var_text.set("✅ 文字已经改变！StringVar 让 Label 活起来了！")

change_btn = tk.Button(
    root,
    text="点我修改文字",
    command=change_text,
    font=("微软雅黑", 12),
    bg="#3498db",
    fg="white",
    padx=20
)
change_btn.pack(pady=5)

root.mainloop()
```

---

## 动手试试

1. **加一条公告**：在公告牌上再添加一条你自己的公告（比如"本周五不上课"）
2. **换字体**：把某条公告的字体换成 `"宋体"` 或 `"Arial"`，看看有什么不同
3. **改颜色**：把通知的红色换成绿色，活动通知的蓝色换成紫色
4. **挑战**：用 `StringVar` 做一个倒计时 —— 修改 `.set()` 里的内容，让文字从 10 变到 0

---

## 小贴士
- `text` 和 `textvariable` **只能用一个**，不能同时使用
- 如果你想让 Label 的文字**居中**显示，设置 `anchor="center"`
- `padx` 和 `pady` 是 Label 内部的留白距离（内边距），让文字不那么挤
- StringVar 需要从 `tk.StringVar()` 创建，不要忘记括号！
- 大部分 tkinter 控件的文字都可以用 `textvariable` 来动态控制，这是个很重要的概念
