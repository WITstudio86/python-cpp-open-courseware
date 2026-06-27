# 第 3 节 · Button 按钮 —— 让程序"听"你的指令

## 学习目标
- 学会创建 Button（按钮）并绑定点击事件
- 理解 `command` 参数 —— 让按钮"知道"被点后该做什么
- 做出点击计数器 —— 按钮每点一次，数字就 +1
- 学会切换按钮文字 —— 一个按钮，两种身份

## 本节课成品
一个「点我计数小工具」—— 点击按钮数字增加，归零按钮重置，还有切换按钮体验状态变化。

---

## 知识点讲解

### 什么是 Button？
Button 就像现实生活中的**开关或按键**——你按它一下，它就会执行某个动作。在程序里，这个"动作"是一段 Python 代码（一个函数）。

和 Label 不同：Label 只能看，Button 可以**交互**！

### 第 1 步：创建你的第一个按钮

```python
def say_hello():
    print("你好！你点击了按钮！")

btn = tk.Button(
    root,
    text="点我！",        # 按钮上显示的文字
    command=say_hello     # 点击后执行哪个函数
)
btn.pack()
```

- `text="点我！"`：按钮上显示的文字
- `command=say_hello`：**最重要的参数！** 告诉按钮"被点击后调用 `say_hello` 函数"。注意这里写的是**函数名**，不要加括号 `()`

**加括号 vs 不加括号：**
```python
command=say_hello    # ✅ 正确：传函数本身，点击时才调用
command=say_hello()  # ❌ 错误：会立刻调用函数！
```

### 第 2 步：点击计数器

计数器的逻辑很简单：用一个变量记录点了多少次，每次点击 +1，然后更新显示。

```python
count = 0  # 全局变量，记录点击次数

def add_count():
    global count           # 声明要修改全局变量
    count += 1             # 次数 +1
    label.config(text=f"点击次数：{count}")  # 更新显示
```

**为什么要用 `global`？**
因为 `count` 定义在函数外面，函数里修改它需要 `global` 声明，否则 Python 会把它当成局部变量。

### 第 3 步：让按钮更漂亮

Button 也有很多美化参数：

| 参数 | 含义 | 示例 |
|------|------|------|
| `font` | 字体 | `("微软雅黑", 14, "bold")` |
| `bg` | 背景颜色 | `"#42a5f5"` |
| `fg` | 文字颜色 | `"white"` |
| `padx` / `pady` | 内边距 | `padx=20, pady=10` |
| `activebackground` | 鼠标悬停时的背景色 | `"#1e88e5"` |
| `activeforeground` | 鼠标悬停时的文字色 | `"white"` |
| `relief` | 边框样式 | `"raised"`（凸起）、`"sunken"`（凹陷）、`"flat"`（平坦） |

### 第 4 步：切换按钮（Toggle）

切换按钮就是：点一下变成"开"，再点一下变成"关"，用 `config()` 动态修改按钮的属性和文字。

```python
is_on = False  # 记录当前状态

def toggle():
    global is_on
    is_on = not is_on           # 翻转状态
    if is_on:
        btn.config(text="🔴 已开启", bg="#ef5350")   # 红色：开
    else:
        btn.config(text="🟢 已关闭", bg="#66bb6a")   # 绿色：关
```

**`config()` 方法**可以动态修改控件的任何属性（文字、颜色、字体……），不需要重新创建控件。这是一个非常强大的方法！

---

## 完整代码

```python
import tkinter as tk

# ========================================
# 第 3 节：Button 按钮 —— 点我计数小工具
# ========================================

root = tk.Tk()
root.title("点我计数小工具")
root.geometry("450x400")
root.configure(bg="#e8f0fe")

# --- 计数变量 ---
count = 0  # 用普通变量记录点击次数

# --- 标题 ---
title = tk.Label(
    root,
    text="🖱️ 点我计数小工具",
    font=("微软雅黑", 20, "bold"),
    fg="#1a237e",
    bg="#e8f0fe"
)
title.pack(pady=20)

# --- 计数显示 Label ---
count_label = tk.Label(
    root,
    text="点击次数：0",
    font=("微软雅黑", 16),
    fg="#283593",
    bg="#e8f0fe"
)
count_label.pack(pady=10)

# --- 点击按钮 ---
def add_count():
    """点击一次，计数 +1，更新显示"""
    global count
    count += 1
    count_label.config(text=f"点击次数：{count}")
    # 根据次数改变颜色
    if count >= 20:
        count_label.config(fg="#c62828")  # 红色：超过 20 次
    elif count >= 10:
        count_label.config(fg="#e65100")  # 橙色：超过 10 次

click_btn = tk.Button(
    root,
    text="👆 点我！",
    command=add_count,
    font=("微软雅黑", 18, "bold"),
    bg="#42a5f5",
    fg="white",
    activebackground="#1e88e5",
    activeforeground="white",
    padx=30,
    pady=10,
    relief="raised",
    bd=3
)
click_btn.pack(pady=15)

# --- 重置按钮 ---
def reset_count():
    """重置计数为 0"""
    global count
    count = 0
    count_label.config(text="点击次数：0", fg="#283593")

reset_btn = tk.Button(
    root,
    text="🔄 归零",
    command=reset_count,
    font=("微软雅黑", 12),
    bg="#78909c",
    fg="white",
    padx=20,
    pady=5
)
reset_btn.pack(pady=5)

# --- 切换按钮（演示文字切换） ---
is_on = False

def toggle():
    """切换按钮文字和颜色"""
    global is_on
    is_on = not is_on
    if is_on:
        toggle_btn.config(text="🔴 已开启", bg="#ef5350")
    else:
        toggle_btn.config(text="🟢 已关闭", bg="#66bb6a")

toggle_btn = tk.Button(
    root,
    text="🟢 已关闭",
    command=toggle,
    font=("微软雅黑", 12),
    bg="#66bb6a",
    fg="white",
    padx=20,
    pady=5
)
toggle_btn.pack(pady=10)

# --- 提示 Label ---
tip = tk.Label(
    root,
    text="试试连续点击，看看颜色会不会变？",
    font=("微软雅黑", 10),
    fg="#78909c",
    bg="#e8f0fe"
)
tip.pack(pady=15)

root.mainloop()
```

---

## 动手试试

1. **加一个减按钮**：新增一个按钮，点击让计数 -1（想想会不会减到负数？）
2. **改颜色阈值**：把颜色变化的阈值从 10/20 改成 5/15，看效果
3. **添加一个"x2"按钮**：点击后让计数翻倍
4. **挑战**：让切换按钮从两档变成三档：🔵 关闭 → 🟢 低档 → 🔴 高档

---

## 小贴士
- `command=函数名` 不要加括号！加了括号会在创建按钮时就执行，而不是点击时执行
- 修改函数外的变量要用 `global` 声明，否则 Python 会报错
- `config()` 是一个非常强大的方法，可以动态修改任何控件的任何属性
- `f-string`（`f"点击次数：{count}"`）是 Python 3.6+ 的新特性，用来把变量嵌入字符串，非常方便
- 按钮变色的逻辑写在 `add_count()` 里，每次点击都会检查当前次数并更新颜色
