# 第 8 课 · 美化界面 — ttk 主题和 grid 布局

---

## 🎯 本课目标

- 学会 **ttk**（Tk 主题控件库）— 让界面更现代
- 学会 **grid** 网格布局 — 精确控制控件位置
- 学会 ttk 的 `Combobox`（下拉选择框）
- 理解三大布局方式：pack vs grid vs place
- 给备忘录来一次"颜值升级"，并添加**类别标签**功能

---

## 📚 新知识

### 8.1 tkinter 默认风格 vs ttk 主题

原生的 tkinter 控件风格比较老旧，看起来像 Windows 95 时代的界面。

**ttk**（Tk themed widgets）是 tkinter 的"美化版"控件库，自带了现代主题：

```python
from tkinter import ttk

# 原版 tkinter 按钮（老式风格）
old_btn = tk.Button(window, text="老式按钮")

# ttk 按钮（现代风格）✅
new_btn = ttk.Button(window, text="现代按钮")
```

**ttk 支持的控件**：

| 原版 tkinter | ttk 版本 | 说明 |
|-------------|----------|------|
| `tk.Button` | `ttk.Button` | 按钮 |
| `tk.Label` | `ttk.Label` | 标签 |
| `tk.Entry` | `ttk.Entry` | 输入框 |
| `tk.Frame` | `ttk.Frame` | 框架 |
| `tk.Checkbutton` | `ttk.Checkbutton` | 复选框 |
| `tk.Radiobutton` | `ttk.Radiobutton` | 单选按钮 |
| `tk.Scrollbar` | `ttk.Scrollbar` | 滚动条 |
| — | `ttk.Combobox` | 下拉选择框（ttk 独有！） |
| — | `ttk.Treeview` | 树形/表格视图（ttk 独有！） |

> ⚠️ **注意**：`Listbox` 和 `Menu` **没有** ttk 版本，仍用原版 tkinter。

### 8.2 查看和切换主题

```python
from tkinter import ttk

# 查看所有可用主题
print(ttk.Style().theme_names())
# 输出示例：('clam', 'alt', 'default', 'classic', 'vista', 'xpnative', 'aqua')

# 切换主题
style = ttk.Style()
style.theme_use("clam")  # clam 是跨平台最好看的主题之一
```

**clam 主题**是跨平台最好看、最稳定的选择，我们的备忘录将使用它。

### 8.3 grid 网格布局 — 精确定位

之前我们用 `pack()` 布局，它按"堆放"方式排列控件。

`grid()` 布局将窗口划分为**行（row）和列（column）的网格**，可以精确控制每个控件放在第几行第几列。

```python
# pack：简单堆放（只能从上到下或从左到右）
label1.pack()
label2.pack()
label3.pack()

# grid：指定行列，像 Excel 表格一样排列
label1.grid(row=0, column=0)   # 第 1 行，第 1 列
label2.grid(row=0, column=1)   # 第 1 行，第 2 列（水平排列！）
label3.grid(row=1, column=0)   # 第 2 行，第 1 列
label4.grid(row=1, column=1)   # 第 2 行，第 2 列
```

**grid 的核心参数**：

| 参数 | 说明 | 示例 |
|------|------|------|
| `row` | 行号（从 0 开始） | `row=0` |
| `column` | 列号（从 0 开始） | `column=1` |
| `sticky` | 对齐方向 | `sticky="w"`（左对齐）、`"e"`（右）、`"n"`（上）、`"s"`（下）、`"we"`（左右填满） |
| `padx` | 外部水平间距 | `padx=10` |
| `pady` | 外部垂直间距 | `pady=5` |
| `ipadx` | 内部水平填充 | `ipadx=5` |
| `ipady` | 内部垂直填充 | `ipady=5` |
| `columnspan` | 跨多列 | `columnspan=2`（占两列） |
| `rowspan` | 跨多行 | `rowspan=3`（占三行） |

> 💡 **sticky 方向用东西南北记**：N(北) S(南) W(西) E(东)。`sticky="w"` 就是"靠西"= 左对齐。组合用：`sticky="nsew"` = 上下左右全填满。

### 8.4 三大布局方式对比

| 布局 | 原理 | 优点 | 缺点 | 适合场景 |
|------|------|------|------|----------|
| `pack()` | 顺序堆放 | 最简单 | 控制力弱 | 简单垂直排列 |
| `grid()` | 网格定位 | 精确控制 | 稍复杂 | **大部分情况（推荐）** |
| `place()` | 绝对坐标 | 完全自由 | 窗口缩放时出问题 | 极少使用 |

> ⚠️ **重要规则**：在一个 Frame 内，**不能混用 pack 和 grid**！要么全部用 pack，要么全部用 grid。

### 8.5 ttk.Combobox — 下拉选择框

`ttk.Combobox` 是一个带下拉选项的输入框，非常适合"类别选择"：

```python
from tkinter import ttk

# 创建下拉选择框
category_combo = ttk.Combobox(
    window,
    values=["学习", "生活", "娱乐", "其他"],  # 下拉选项
    state="readonly",                           # 只读（不允许自由输入）
    font=("微软雅黑", 11)
)

# 设置默认值
category_combo.set("学习")

# 获取当前选中的值
selected = category_combo.get()
```

### 8.6 自定义 ttk 样式

ttk 允许你**自定义控件的样式**，类似 CSS：

```python
style = ttk.Style()

# 自定义按钮样式
style.configure("Add.TButton",       # 样式名（.TButton 表示基于按钮）
    background="#4CAF50",
    foreground="white",
    font=("微软雅黑", 11),
    padding=8
)

# 使用自定义样式
add_btn = ttk.Button(window, text="添加", style="Add.TButton")
```

**样式命名规则**：
- `"名称.控件类型"` — 如 `"Add.TButton"`（TButton = ttk 按钮）
- `"名称"` — 不指定类型，可用于任何控件

**控件类型后缀**：

| 后缀 | 对应控件 |
|------|---------|
| `.TButton` | ttk.Button |
| `.TLabel` | ttk.Label |
| `.TEntry` | ttk.Entry |
| `.TFrame` | ttk.Frame |
| `.TCombobox` | ttk.Combobox |
| `.TCheckbutton` | ttk.Checkbutton |
| `.TRadiobutton` | ttk.Radiobutton |

---

## 💻 写代码

### 步骤 1：导入和主题

新建 `lesson8.py`：

```python
import tkinter as tk
from tkinter import ttk, messagebox
import os

# 设置主题
style = ttk.Style()
# 尝试使用 clam 主题（跨平台最现代的主题）
available_themes = style.theme_names()
if "clam" in available_themes:
    style.theme_use("clam")
    print(f"🎨 使用主题：clam")
else:
    print(f"🎨 可用主题：{available_themes}")
    print(f"🎨 使用默认主题")
```

### 步骤 2：用 grid 布局重新组织界面

将原来的 pack 布局改为 grid：

```python
window = tk.Tk()
window.title("我的备忘录")
window.geometry("500x650")

# 让窗口可缩放时，第 4 行（列表区域）自动拉伸
window.grid_rowconfigure(4, weight=1)      # 第 4 行（列表）可以拉伸
window.grid_columnconfigure(0, weight=1)    # 第 0 列可以拉伸

# ==================== 标题（第 0 行）====================

title_label = ttk.Label(
    window,
    text="📝 我的备忘录",
    font=("微软雅黑", 20, "bold")
)
title_label.grid(row=0, column=0, pady=(15, 5), sticky="n")

# ==================== 副标题（第 1 行）====================

subtitle_label = ttk.Label(
    window,
    text="美化升级版！支持类别标签 🏷️",
    font=("微软雅黑", 10)
)
subtitle_label.grid(row=1, column=0, pady=(0, 10), sticky="n")
```

> 💡 **`grid_rowconfigure(4, weight=1)`** — 设置第 4 行的"权重"为 1。当窗口被拉大时，权重高的行会得到更多的额外空间。这一步让列表区域可以随窗口放大。

### 步骤 3：输入区域 + 类别选择（第 2 行）

```python
# ==================== 输入区域（第 2 行）====================

input_frame = ttk.Frame(window)
input_frame.grid(row=2, column=0, pady=10, padx=20, sticky="ew")
input_frame.grid_columnconfigure(1, weight=1)  # 输入框列可拉伸

# 类别下拉框
ttk.Label(input_frame, text="类别：", font=("微软雅黑", 10)).grid(
    row=0, column=0, padx=(0, 5), sticky="w"
)

category_combo = ttk.Combobox(
    input_frame,
    values=["学习 📚", "生活 🏠", "娱乐 🎮", "其他 📌"],
    state="readonly",
    font=("微软雅黑", 10),
    width=10
)
category_combo.grid(row=0, column=1, sticky="w")
category_combo.set("学习 📚")  # 默认选中"学习"

# 输入框（第 1 行第 0 列，跨两列）
entry = ttk.Entry(input_frame, font=("微软雅黑", 13))
entry.grid(row=1, column=0, columnspan=2, pady=(8, 8), sticky="ew")

# 按钮栏（第 2 行，跨两列）
btn_frame = ttk.Frame(input_frame)
btn_frame.grid(row=2, column=0, columnspan=2, sticky="w")

add_btn = ttk.Button(btn_frame, text="添加 ✅")
add_btn.grid(row=0, column=0, padx=(0, 5))

toggle_btn = ttk.Button(btn_frame, text="标记 ✔️")
toggle_btn.grid(row=0, column=1, padx=(0, 5))

delete_btn = ttk.Button(btn_frame, text="删除 ❌")
delete_btn.grid(row=0, column=2, padx=(0, 5))

clear_btn = ttk.Button(btn_frame, text="清空 🗑️")
clear_btn.grid(row=0, column=3)
```

### 步骤 4：列表头 + 列表（第 3-4 行）

添加一个表头显示"类别"和"内容"两列的概念：

```python
# ==================== 列表头（第 3 行）====================

header_frame = ttk.Frame(window)
header_frame.grid(row=3, column=0, pady=(15, 0), padx=20, sticky="ew")

ttk.Label(header_frame, text="📋 待办列表", font=("微软雅黑", 12, "bold")).pack(
    side=tk.LEFT
)
ttk.Label(header_frame, text="（双击标记完成，右键更多操作）",
          font=("微软雅黑", 8)).pack(side=tk.LEFT, padx=10)

# ==================== 列表区域（第 4 行）====================

list_frame = ttk.Frame(window)
list_frame.grid(row=4, column=0, pady=5, padx=20, sticky="nsew")
list_frame.grid_rowconfigure(0, weight=1)
list_frame.grid_columnconfigure(0, weight=1)

scrollbar = ttk.Scrollbar(list_frame, orient=tk.VERTICAL)
scrollbar.grid(row=0, column=1, sticky="ns")

# Listbox 还是用原版 tk（ttk 没有 Listbox）
listbox = tk.Listbox(
    list_frame,
    font=("微软雅黑", 12),
    height=15,
    selectbackground="#C8E6C9",
    selectforeground="#333333",
    yscrollcommand=scrollbar.set
)
listbox.grid(row=0, column=0, sticky="nsew")
scrollbar.config(command=listbox.yview)
```

### 步骤 5：底部状态栏（第 5 行）

```python
# ==================== 状态栏（第 5 行）====================

status_frame = ttk.Frame(window)
status_frame.grid(row=5, column=0, pady=8, padx=20, sticky="ew")

status_label = ttk.Label(
    status_frame, text="共 0 条待办", font=("微软雅黑", 9)
)
status_label.pack(side=tk.RIGHT)
```

### 步骤 6：升级数据结构，加入类别

```python
# 数据结构升级：加入 category 字段
todos = []
# 格式：[{"text": "内容", "done": False, "category": "学习 📚"}, ...]
```

修改 `add_todo()`：

```python
def add_todo():
    text = entry.get().strip()
    if text:
        category = category_combo.get()
        todo = {
            "text": text,
            "done": False,
            "category": category
        }
        todos.append(todo)

        # Listbox 显示：类别 + 内容
        display_text = f"[{category}] {text}"
        listbox.insert(tk.END, display_text)
        entry.delete(0, tk.END)
        save_todos()
        update_status()
```

### 步骤 7：升级文件保存/加载

```python
# 保存：状态|类别|内容
def save_todos():
    with open(DATA_FILE, "w", encoding="utf-8") as file:
        for todo in todos:
            status = "1" if todo["done"] else "0"
            category = todo.get("category", "其他 📌")
            file.write(f"{status}|{category}|{todo['text']}\n")

# 加载：解析三部分
def load_todos():
    if not os.path.exists(DATA_FILE):
        return
    with open(DATA_FILE, "r", encoding="utf-8") as file:
        for line in file:
            line = line.strip()
            if not line:
                continue
            parts = line.split("|")
            if len(parts) == 3:
                status_str, category, text = parts
            elif len(parts) == 2:
                # 兼容旧格式（没有类别字段）
                status_str, text = parts
                category = "其他 📌"
            else:
                continue

            todo = {"text": text, "done": status_str == "1", "category": category}
            todos.append(todo)

            display_text = f"[{category}] {text}"
            listbox.insert(tk.END, display_text)

            if todo["done"]:
                idx = listbox.size() - 1
                listbox.itemconfig(idx, fg="gray")
                listbox.itemconfig(idx, font=("微软雅黑", 12, "overstrike"))
    print(f"📂 已加载 {len(todos)} 条待办")
```

---

## ▶️ 运行看效果

对比第 7 课和第 8 课的界面差异：

| 方面 | 第 7 课（pack + tk） | 第 8 课（grid + ttk） |
|------|---------------------|----------------------|
| 按钮风格 | 老式凸起按钮 | 现代扁平按钮 |
| 布局方式 | 垂直堆叠 | 网格精确排列 |
| 类别选择 | 无 | 下拉选择框 |
| 列表显示 | 纯文字 | 带类别标签 |
| 窗口缩放 | 控件不动 | 列表自动拉伸 |
| 主题 | 灰色经典 | clam 现代风格 |

> 📸 *（此处放置升级前后对比截图）*

---

## ✏️ 小练习

1. **换主题**：尝试 `"alt"` 或 `"default"` 主题，看看有什么不同
2. **加类别**：在 Combobox 中添加 `"运动 💪"` 选项
3. **改布局**：把按钮从 `sticky="w"`（左对齐）改成居中对齐（提示：用 Frame 的 pack 居中再放按钮）
4. **挑战题**：给输入框加**占位文字**（placeholder），显示"请输入待办事项..."，点击后消失（提示：绑定 `<FocusIn>` 和 `<FocusOut>` 事件）

---

## 📋 本课完整代码

> ⚠️ 由于篇幅限制，完整代码请参考第 7 课的最终代码，将以下部分进行替换：
> 1. `import tkinter as tk` → 加上 `from tkinter import ttk`
> 2. 所有布局从 `pack()` 改为 `grid()`
> 3. 所有控件从 `tk.Button` 改为 `ttk.Button`（Listbox 和 Menu 保持不变）
> 4. 添加 category_combo 和类别相关逻辑
> 5. 保存/加载格式从 2 字段升级为 3 字段

---

## 🧠 本课小结

| 学到的知识 | 是什么 | 怎么用 |
|-----------|--------|--------|
| `ttk` | 主题控件库 | `from tkinter import ttk` |
| `ttk.Style()` | 样式管理器 | `style = ttk.Style()` |
| `theme_use()` | 切换主题 | `style.theme_use("clam")` |
| `grid()` | 网格布局 | `widget.grid(row=0, column=1)` |
| `sticky` | 对齐方式 | `sticky="w"` = 左对齐 |
| `columnspan` | 跨列 | `columnspan=2` |
| `grid_rowconfigure(..., weight=1)` | 行拉伸权重 | 窗口缩放时自动调整 |
| `ttk.Combobox` | 下拉选择框 | `ttk.Combobox(values=[...], state="readonly")` |
| 自定义样式 | 类似 CSS | `style.configure("Name.TButton", ...)` |

---

## 📖 下节课预告

第 9 课：**搜索与过滤 — 让备忘录更好用**

待办事项多了不好找？我们加入**搜索/过滤**功能，可以按关键词搜索或按类别筛选。还会引入 `Frame` 嵌套布局的进阶技巧。
