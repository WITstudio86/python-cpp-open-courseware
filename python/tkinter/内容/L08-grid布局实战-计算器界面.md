# 第 8 节：grid 布局实战 —— 计算器界面

## 学习目标

1. 掌握 `grid` 布局的精确行列定位（`row` / `column`）
2. 理解 `columnspan` 和 `rowspan` 实现跨行跨列
3. 掌握 `sticky` 参数控制组件在格子内的对齐方式
4. 独立搭建一个完整的计算器按钮面板

## 成品预览

一个深色风格的计算器按钮面板，包含数字键 0~9、运算符 +、-、x、/、小数点、等号、清除键 C 和退格键。**本课只做界面，不实现计算逻辑。**

## 知识点讲解

### 1. grid 精确定位

`grid` 布局将窗口划分为网格，通过 `row`（行号）和 `column`（列号）将组件放到指定位置。

```python
label.grid(row=0, column=0)   # 放在第 0 行、第 0 列
btn.grid(row=1, column=2)     # 放在第 1 行、第 2 列
```

行号和列号都从 `0` 开始计数。如果某个位置没有放置组件，该行/列会自动收缩。

**grid 与 pack 不能混用**在同一个父容器中，只能在同一个容器内选择一种布局管理器。

### 2. columnspan —— 跨多列

让一个组件占据多列的宽度，适用于显示区域、标题栏等需要更大空间的元素。

```python
display.grid(row=0, column=0, columnspan=4)  # 横跨 4 列
```

在计算器中，显示屏需要占据整个宽度，所以设置 `columnspan=4` 横跨 4 列。

### 3. rowspan —— 跨多行

让一个组件占据多行的高度，例如等号按钮通常高于普通按钮。

```python
equal_btn.grid(row=5, column=3, rowspan=2)   # 纵跨 2 行
```

在计算器中，`=` 按钮跨 2 行，使其高度与其他两个按钮加起来一致。

### 4. sticky —— 对齐方式

`sticky` 控制组件在分配到的格子内的对齐方式，取值基于方位：

| 取值 | 含义 |
|------|------|
| `N` | 靠上（北） |
| `S` | 靠下（南） |
| `E` | 靠右（东） |
| `W` | 靠左（西） |
| `NSEW` | 填满整个格子（拉伸到四边） |
| `EW` | 水平填满 |
| `NS` | 垂直填满 |

```python
btn.grid(row=1, column=0, sticky="nsew")   # 按钮填满格子
display.grid(row=0, column=0, sticky="ew")  # 只在水平方向填满
```

**注意：** `sticky="nsew"` 只是让组件"想要"填满格子。格子本身是否足够大，还取决于 `grid_rowconfigure` 和 `grid_columnconfigure` 的 `weight` 设置。

### 5. 让行列均匀拉伸

```python
for i in range(7):
    root.grid_rowconfigure(i, weight=1)
for j in range(4):
    root.grid_columnconfigure(j, weight=1)
```

`weight` 表示该行/列在窗口拉伸时的"权重"。权重越大，分配到的额外空间越多。设为 1 表示均匀分配。

## 完整代码

见程序文件夹中的 `L08-计算器按钮面板.py`。

## 动手试试

1. **修改按钮颜色**：把数字键改成你喜欢的颜色
2. **调整按钮间距**：修改 `padx` 和 `pady` 的值，观察效果变化
3. **添加新按钮**：在现有面板上增加一个 `%` 或 `√` 按钮，调整布局
4. **改变窗口大小**：手动拉伸窗口，观察 `weight=1` 的效果

## 小贴士

- `grid` 的 `padx`/`pady` 和 `sticky` 是独立的概念：`padx`/`pady` 控制组件与格子边界的**外部间距**，`sticky` 控制组件在格子内的**对齐拉伸**
- 使用 `**dict` 解包可以减少重复代码，让按钮配置更简洁
- 确保 `columnspan` 的总列数不超过实际列数（本计算器为 4 列）
- 如果不设置 `weight`，窗口拉伸时组件不会随之变化
