# 第 6 节：Frame 框架 + pack 布局（上）

## 学习目标

- 理解什么是 Frame 容器，以及它和控件的"收纳"关系
- 学会创建 Frame 并设置背景、边框等样式
- 掌握 `pack()` 布局的基本用法：默认堆叠、`pady`/`padx` 间距
- 理解"父子关系"（parent 参数），知道控件"属于谁"

## 本节作品：个人信息卡

你将做出一个好看的个人信息卡，用多个 Frame 把不同区域分开，就像一张真正的卡片！

---

## 知识点

### 1. 什么是 Frame？

Frame 就像一个**收纳盒**，你可以把控件放进去，把它们分门别类地管理。

打个比方：你的书桌上有很多东西 —— 笔、橡皮、尺子、书本。如果全部散在桌面上，会很乱。但如果你用几个收纳盒把它们分类装好，桌面就整洁多了！

在 tkinter 中，Frame 就是这个"收纳盒"。你可以给不同区域创建不同的 Frame，让界面更有条理。

```python
import tkinter as tk

root = tk.Tk()
root.title("Frame 示例")

# 创建一个 Frame
my_frame = tk.Frame(root)
my_frame.pack()

root.mainloop()
```

`tk.Frame(root)` 是什么意思？括号里的 `root` 告诉 Frame："你的'爸爸'（父容器）是 root 窗口"。这个后面会详细讲。

### 2. Frame 的样式设置

Frame 可以设置很多外观参数，让它看起来更漂亮：

| 参数 | 含义 | 示例值 |
|------|------|--------|
| `bg` | 背景颜色 | `"#ffffff"`, `"lightblue"` |
| `relief` | 边框样式 | `"groove"`, `"ridge"`, `"solid"`, `"sunken"`, `"flat"` |
| `bd` | 边框宽度（像素） | `2`, `3`, `5` |
| `padx` | 内部左右留白 | `10`, `15`, `20` |
| `pady` | 内部上下留白 | `10`, `15`, `20` |

示例：

```python
frame = tk.Frame(
    root,
    bg="#ffffff",     # 白色背景
    relief="groove",  # 凹槽边框
    bd=3,             # 边框宽度 3 像素
    padx=20,          # 左右内边距 20
    pady=15           # 上下内边距 15
)
frame.pack()
```

> 小提示：`padx` / `pady` 是 Frame **内部**的留白，让里面的控件不会紧贴边框。
> 而 `pack()` 里的 `padx` / `pady` 是 Frame **外部**与其他控件之间的间距。

### 3. pack() 的基本用法

`pack()` 是最简单的布局方法。默认情况下，控件会**从上到下**一个接一个地堆叠。

```python
import tkinter as tk

root = tk.Tk()
root.geometry("300x200")

# 三个按钮默认从上到下排列
tk.Button(root, text="第 1 个").pack()
tk.Button(root, text="第 2 个").pack()
tk.Button(root, text="第 3 个").pack()

root.mainloop()
```

`pack()` 常用的参数：

| 参数 | 含义 | 示例 |
|------|------|------|
| `pady` | 上下外间距 | `pady=10` |
| `padx` | 左右外间距 | `padx=20` |
| `side` | 排列方向 | `side="top"`（默认）、`"bottom"`、`"left"`、`"right"` |
| `fill` | 填充方向 | `fill="x"`（横向填满）、`fill="y"`（纵向填满）、`fill="both"` |
| `anchor` | 对齐方向 | `anchor="w"`（左对齐）、`anchor="center"`（居中） |
| `expand` | 是否扩展 | `expand=True` / `expand=False` |

> 本期我们重点掌握 `pady`、`padx` 和 `fill="x"`。`side`、`anchor` 等参数在下一节详细讲解。

### 4. 父子关系（parent 参数）

在 tkinter 中，每个控件创建时都要指定它的"爸爸"（父容器）。

```python
# root 是"爷爷"（主窗口）
root = tk.Tk()

# frame 的爸爸是 root
frame = tk.Frame(root)

# label 的爸爸是 frame（不是 root！）
label = tk.Label(frame, text="我在 Frame 里")

# 另一个 label 的爸爸是 root
label2 = tk.Label(root, text="我在主窗口里")
```

记住这个口诀：**谁把我装起来，谁就是我的爸爸！**

一个简单的方法判断：看控件 `.pack()` 之后出现在哪个容器里，它就是谁的"孩子"。

---

## 完整代码：个人信息卡

```python
import tkinter as tk

root = tk.Tk()
root.title("个人信息卡")
root.geometry("450x550")
root.configure(bg="#fff8e1")

# --- 主标题 ---
title = tk.Label(
    root,
    text="📇 个人信息卡",
    font=("微软雅黑", 20, "bold"),
    fg="#e65100",
    bg="#fff8e1"
)
title.pack(pady=15)

# ============= Frame 1：基本信息区 =============
frame_basic = tk.Frame(
    root,
    bg="#ffffff",
    relief="groove",
    bd=2,
    padx=15,
    pady=15
)
frame_basic.pack(pady=10, padx=30, fill="x")

tk.Label(frame_basic, text="👤 基本信息",
         font=("微软雅黑", 14, "bold"),
         fg="#bf360c", bg="#ffffff").pack(anchor="w")

tk.Label(frame_basic, text="姓名：小明同学",
         font=("微软雅黑", 12),
         fg="#4e342e", bg="#ffffff").pack(anchor="w", pady=2)

tk.Label(frame_basic, text="年龄：13 岁",
         font=("微软雅黑", 12),
         fg="#4e342e", bg="#ffffff").pack(anchor="w", pady=2)

tk.Label(frame_basic, text="班级：七年级（3）班",
         font=("微软雅黑", 12),
         fg="#4e342e", bg="#ffffff").pack(anchor="w", pady=2)

# ============= Frame 2：爱好区 =============
frame_hobby = tk.Frame(
    root,
    bg="#e8f5e9",
    relief="ridge",
    bd=2,
    padx=15,
    pady=15
)
frame_hobby.pack(pady=10, padx=30, fill="x")

tk.Label(frame_hobby, text="🌟 兴趣爱好",
         font=("微软雅黑", 14, "bold"),
         fg="#1b5e20", bg="#e8f5e9").pack(anchor="w")

tk.Label(frame_hobby,
         text="🎮 编程\n📚 阅读科幻小说\n⚽ 踢足球",
         font=("微软雅黑", 12),
         fg="#33691e", bg="#e8f5e9",
         justify="left").pack(anchor="w", pady=5)

# ============= Frame 3：学习目标区 =============
frame_goal = tk.Frame(
    root,
    bg="#e3f2fd",
    relief="groove",
    bd=2,
    padx=15,
    pady=15
)
frame_goal.pack(pady=10, padx=30, fill="x")

tk.Label(frame_goal, text="🎯 学习目标",
         font=("微软雅黑", 14, "bold"),
         fg="#0d47a1", bg="#e3f2fd").pack(anchor="w")

tk.Label(frame_goal,
         text="✅ 学会 Python 基础\n✅ 掌握 tkinter 图形界面\n⬜ 做出自己的第一个 App",
         font=("微软雅黑", 12),
         fg="#1565c0", bg="#e3f2fd",
         justify="left").pack(anchor="w", pady=5)

# --- 底部按钮 ---
btn_frame = tk.Frame(root, bg="#fff8e1")
btn_frame.pack(pady=15)

tk.Button(btn_frame, text="👍 赞",
          font=("微软雅黑", 12, "bold"),
          bg="#4caf50", fg="white",
          padx=20, pady=5).pack(side="left", padx=5)

tk.Button(btn_frame, text="💬 留言",
          font=("微软雅黑", 12, "bold"),
          bg="#2196f3", fg="white",
          padx=20, pady=5).pack(side="left", padx=5)

tk.Button(btn_frame, text="🔗 分享",
          font=("微软雅黑", 12, "bold"),
          bg="#ff9800", fg="white",
          padx=20, pady=5).pack(side="left", padx=5)

root.mainloop()
```

---

## 动手试试

1. **修改样式**：把 `frame_basic` 的 `relief` 改成 `"ridge"`，`bd` 改成 `4`，看看有什么不同？
2. **增加 Frame**：仿照上面的写法，自己再加一个 Frame，叫做"📅 近期计划"，写出你最近想做的 3 件事。
3. **改变颜色**：把三个 Frame 的背景色换成你喜欢的颜色搭配。
4. **添加 Label**：在个人信息卡的开头，加一行 `tk.Label` 显示日期（比如 "2026 年 6 月"），注意它的 parent 是谁？

---

## 小贴士

- Frame 本身是**看不见**的（除非你设置了背景色和边框），它只是一个"容器"。如果发现界面空空如也，检查一下是不是忘了给 Frame 设置 `bg` 和 `relief`！
- 创建控件时**一定要想清楚它的 parent 是谁**。如果 parent 写错了，控件就会跑到错误的地方去。
- `fill="x"` 可以让 Frame 横向填满父容器，非常适合做卡片式的布局。
- 如果你想让 Frame 保持固定大小，可以用 `pack_propagate(False)`（这个先了解即可，后面会细讲）。
