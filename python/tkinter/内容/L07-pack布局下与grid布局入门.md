# 第 7 节：pack 布局（下）+ grid 布局入门

## 学习目标

- 掌握 `pack()` 的高级参数：`side`、`anchor`、`fill`、`expand`
- 理解 `grid()` 布局的"行和列"概念
- 能够用 `grid()` 创建表格式的界面排列
- 学会根据界面需求选择合适的布局方式（pack vs grid）

## 本节作品：两种布局对比演示

你将同时看到 pack 和 grid 两种布局方式的效果，直观感受它们的区别！

---

## 知识点

### 1. pack 进阶参数

上一节我们用了 `pack()` 的基本用法（默认从上到下堆叠）。这一节我们来学习更多参数，让你能灵活控制控件的位置。

#### side —— 排列方向

`side` 决定了控件贴在哪个方向：

| 值 | 含义 | 示例 |
|---|---|---|
| `"top"` | 贴在上方（默认） | `pack(side="top")` |
| `"bottom"` | 贴在下方 | `pack(side="bottom")` |
| `"left"` | 贴在左侧 | `pack(side="left")` |
| `"right"` | 贴在右侧 | `pack(side="right")` |

```python
# 4 个按钮分别贴在四个边
btn1.pack(side="top", fill="x")      # ↑ 贴在上边，横向填满
btn2.pack(side="left", fill="y")     # ← 贴在左边，纵向填满
btn3.pack(side="right", fill="y")    # → 贴在右边，纵向填满
btn4.pack(side="bottom", fill="x")   # ↓ 贴在下边，横向填满
```

> side 的顺序很重要！先 pack 的控件"抢占"空间，后面的控件在剩余空间排列。

#### anchor —— 对齐方向

`anchor` 决定了控件在打包空间内靠哪个方向对齐。想象一个指南针：

- `"n"` = 北（上）、`"s"` = 南（下）
- `"w"` = 西（左）、`"e"` = 东（右）
- `"nw"` = 左上、`"ne"` = 右上、`"sw"` = 左下、`"se"` = 右下
- `"center"` = 居中（默认）

```python
# Label 靠左对齐
label.pack(anchor="w")

# Button 靠右上角
button.pack(anchor="ne")
```

记忆技巧：**上北下南左西右东**，`n` 是上、`s` 是下、`w` 是左、`e` 是右。

#### fill —— 填充方式

`fill` 决定控件是否填充分配给它的空间：

| 值 | 含义 |
|---|---|
| `"x"` | 横向填满 |
| `"y"` | 纵向填满 |
| `"both"` | 横向和纵向都填满 |
| `"none"` | 不填充（默认） |

```python
# 按钮横向填满整行
btn.pack(fill="x")

# Frame 双向填满
frame.pack(fill="both", expand=True)
```

#### expand —— 是否扩展

`expand=True` 让控件"吃掉"父容器中多余的空间。通常配合 `fill` 使用。

```python
# 控件占据所有剩余空间
widget.pack(fill="both", expand=True)
```

### 2. grid 布局入门

如果 pack 是"排队放东西"，grid 就是"在表格里放东西"——像 Excel 一样，每个控件都有它自己的行和列！

```python
import tkinter as tk

root = tk.Tk()

# grid 用 row 和 column 定位
btn1 = tk.Button(root, text="(0,0)")
btn1.grid(row=0, column=0)

btn2 = tk.Button(root, text="(0,1)")
btn2.grid(row=0, column=1)

btn3 = tk.Button(root, text="(1,0)")
btn3.grid(row=1, column=0)

btn4 = tk.Button(root, text="(1,1)")
btn4.grid(row=1, column=1)

root.mainloop()
```

grid 的坐标系统：

```
       column=0    column=1    column=2
row=0 | (0,0)   |  (0,1)   |  (0,2)  |
row=1 | (1,0)   |  (1,1)   |  (1,2)  |
row=2 | (2,0)   |  (2,1)   |  (2,2)  |
```

#### grid 常用参数

| 参数 | 含义 | 示例 |
|------|------|------|
| `row` | 行号（从 0 开始） | `row=0` |
| `column` | 列号（从 0 开始） | `column=1` |
| `padx` | 左右外间距 | `padx=5` |
| `pady` | 上下外间距 | `pady=5` |
| `sticky` | 对齐方向（同 anchor） | `sticky="w"`、`sticky="nsew"` |

> 注意：grid 的 `padx` 和 `pady` 是**外间距**，和 pack 的 `padx`、`pady` 一样意思。

### 3. pack vs grid —— 什么时候用哪个？

| 对比维度 | pack | grid |
|----------|------|------|
| 排列方式 | 从上到下 / 从左到右"堆积" | 按行和列的"表格"排列 |
| 适用场景 | 简单纵向/横向排列、工具栏、卡片式布局 | 九宫格、计算器、表单、表格数据 |
| 学习难度 | 简单，容易上手 | 稍复杂，需要规划行列 |
| 灵活性 | 灵活但有局限 | 精确但需要预先规划 |
| 混用规则 | 同一父容器内只能选一种！ | 同一父容器内只能选一种！ |

> **重要规则**：在一个 Frame 内部，`pack()` 和 `grid()` **不能混用**！但你可以外层用 pack，内层用 grid（不同 Frame 之间不冲突）。

**选 layout 的口诀**：
- 简单的上下或左右排列 → **pack**
- 需要做表格、九宫格、计算器 → **grid**
- 一个 Frame 里只能有一种 layout，但不同 Frame 可以不同！

---

## 完整代码：两种布局对比演示

```python
import tkinter as tk

root = tk.Tk()
root.title("两种布局对比演示")
root.geometry("700x550")
root.configure(bg="#fafafa")

# --- 标题 ---
title = tk.Label(
    root,
    text="📐 两种布局方式对比",
    font=("微软雅黑", 20, "bold"),
    fg="#37474f",
    bg="#fafafa"
)
title.pack(pady=10)

# ============= pack 布局演示 =============
pack_label = tk.Label(
    root,
    text="⬇ pack 布局 —— 灵活排列",
    font=("微软雅黑", 14, "bold"),
    fg="#0277bd",
    bg="#fafafa"
)
pack_label.pack()

pack_frame = tk.Frame(
    root,
    bg="#e1f5fe",
    relief="groove",
    bd=2,
    width=620,
    height=180
)
pack_frame.pack(pady=8, padx=40, fill="x")
pack_frame.pack_propagate(False)

# 四个方向的按钮
btn_top = tk.Button(pack_frame, text="↑ 顶部 (TOP)",
                     bg="#42a5f5", fg="white")
btn_top.pack(side="top", fill="x", padx=5, pady=2)

btn_left = tk.Button(pack_frame, text="← 左侧 (LEFT)",
                      bg="#66bb6a", fg="white")
btn_left.pack(side="left", fill="y", padx=5, pady=2)

btn_right = tk.Button(pack_frame, text="右侧 (RIGHT) →",
                       bg="#ffa726", fg="white")
btn_right.pack(side="right", fill="y", padx=5, pady=2)

btn_bottom = tk.Button(pack_frame, text="↓ 底部 (BOTTOM)",
                        bg="#ef5350", fg="white")
btn_bottom.pack(side="bottom", fill="x", padx=5, pady=2)

# ============= grid 布局演示 =============
grid_label = tk.Label(
    root,
    text="⬇ grid 布局 —— 像表格一样精确",
    font=("微软雅黑", 14, "bold"),
    fg="#6a1b9a",
    bg="#fafafa"
)
grid_label.pack(pady=(20, 5))

grid_frame = tk.Frame(
    root,
    bg="#f3e5f5",
    relief="groove",
    bd=2,
    width=620,
    height=180
)
grid_frame.pack(pady=8, padx=40, fill="x")
grid_frame.pack_propagate(False)

# 3x3 网格
for r in range(3):
    for c in range(3):
        tk.Button(
            grid_frame,
            text=f"({r},{c})",
            bg="#ab47bc" if r == 0 else "#ce93d8" if r == 1 else "#ba68c8",
            fg="white",
            width=8,
            height=2
        ).grid(row=r, column=c, padx=3, pady=3)

# --- 底部说明 ---
note = tk.Label(
    root,
    text="💡 pack 适合简单排列 | grid 适合表格/九宫格/计算器",
    font=("微软雅黑", 10),
    fg="#78909c",
    bg="#fafafa",
    wraplength=600
)
note.pack(pady=15)

root.mainloop()
```

---

## 动手试试

1. **改变 side 顺序**：把 pack 演示中的 4 个按钮调整顺序（比如先 pack bottom，再 pack top），观察界面变化。你发现了什么规律？
2. **增加 grid 行列**：把 3x3 的 grid 改成 4x4 或 5x5，看看效果。
3. **给 grid 加 sticky**：给 grid 中的按钮加上 `sticky="nsew"`，观察和默认排列有什么不同。
4. **对比挑战**：尝试用 grid 方式做一个和上节"个人信息卡"一样的界面，体会两者布局思路的差异。

---

## 小贴士

- **pack 的 side 顺序会互相影响空间分配**。如果你先 `pack(side="left")`，它会把左侧空间占满，后面的控件只能在剩余空间排列。
- **grid 的行和列编号都从 0 开始**，和 Python 列表的索引一样。
- **一个 Frame 内只能使用一种布局方式**。如果你的 Frame 里用了 pack，就不要再在里面用 grid（反过来也一样）。如果实在需要混用，就嵌套一个新的子 Frame。
- `pack_propagate(False)` 可以让 Frame 不随内部控件自动缩放，保持你设置的 `width` 和 `height`。这个在需要固定大小区域时很有用。
- **sticky 参数的记忆**：它就是 anchor 的"加强版"，不仅控制对齐，还能让控件拉伸填满网格单元格。
