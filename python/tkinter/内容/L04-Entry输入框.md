# 第 4 节：Entry 输入框 —— 让用户输入信息

## 本节目标 🎯

学完本节后，你将能够：

1. ✅ 创建一个 Entry 输入框
2. ✅ 使用 `get()` 读取用户输入的内容
3. ✅ 使用 `delete()` 清空输入框，使用 `insert()` 插入文字
4. ✅ 使用 `show` 参数制作蜜码输入框

## 最终作品：名字生成器 ✨

这一节我们要做一个有趣的小程序——**名字生成器**！你只需要在输入框中输入自己的名字，点击按钮，程序就会热情地跟你打招呼！还会有一个"清空"按钮来清空输入，还有一个蜜码模式的演示～

---

## 知识点讲解 📖

### 1. 创建 Entry 输入框

`Entry` 是 Tkinter 中用来让用户**输入文字**的控件。来看看怎么创建一个输入框：

```python
name_entry = tk.Entry(
    root,
    font=("微软雅黑", 16),   # 字体和大小
    width=20,               # 输入框宽度（字符数）
    bd=2,                   # 边框宽度
    relief="solid",         # 边框样式：solid 表示实线
    justify="center"        # 文字居中
)
name_entry.pack(pady=10)
```

**参数说明：**

| 参数 | 含义 | 常用值 |
|------|------|--------|
| `font` | 字体和大小 | `("微软雅黑", 16)` |
| `width` | 宽度（字符数） | 数值，如 `20` |
| `bd` | 边框粗细 | 数值，如 `2` |
| `relief` | 边框样式 | `"solid"`、`"sunken"`、`"flat"` |
| `justify` | 文字对齐方式 | `"left"`、`"center"`、`"right"` |
| `show` | 掩码字符 | `"*"`、`"●"`（蜜码模式） |

---

### 2. get() —— 读取用户输入的内容

`get()` 方法可以**读取**输入框中用户输入的文字。

```python
name = name_entry.get()  # 获取输入框中的文字
```

> 💡 **特别提醒**：`get()` 返回的是一个**字符串**。如果输入框是空的，它会返回空字符串 `""`。

**使用场景：**

```python
def generate():
    """读取输入框内容，生成个性化问候"""
    name = name_entry.get()  # ← 读取用户输入
    if name:
        result.config(text=f"你好，{name}！🎉")
    else:
        result.config(text="⚠️ 请先输入你的名字哦～")
```

---

### 3. delete() 和 insert() —— 清空与插入

这两个方法让你可以**操控**输入框中的内容：

#### delete() —— 删除文字

```python
name_entry.delete(0, tk.END)  # 删除从第 0 个字符到末尾的所有内容
```

`delete(起始位置, 结束位置)`：
- `0` 表示第 1 个字符（索引从 0 开始）
- `tk.END` 表示末尾
- 所以 `(0, tk.END)` 就是"从头删到尾"，也就是清空啦！

#### insert() —— 插入文字

```python
name_entry.insert(0, "在这里输入你的名字")  # 在第 0 个位置插入提示文字
```

`insert(位置, 文字)`：
- 第一个参数是插入的位置
- 第二个参数是你要插入的文字

> 💡 **小技巧**：在程序启动时用 `insert(0, "...")` 放入提示文字，用户一看就知道要干嘛！

---

### 4. show 参数 —— 蜜码模式 🔒

如果在创建 Entry 时加上 `show` 参数，输入的内容就会被**隐藏**，只显示你指定的字符！

```python
pwd_entry = tk.Entry(
    root,
    font=("微软雅黑", 14),
    width=20,
    show="●",  # ← 输入时显示 ●，而不是真实字符
    justify="center"
)
```

**常用的 show 值：**
- `show="*"` —— 显示星号
- `show="●"` —— 显示圆点
- `show="#"` —— 显示井号

> 💡 这个功能非常适合做**蜜码输入框**哦！你在登录各种网站时看到的密码输入框，就是用了类似的技术。

---

## 完整代码 📝

```python
import tkinter as tk

# ========================================
# 第 4 节：Entry 输入框 —— 名字生成器
# ========================================

root = tk.Tk()
root.title("名字生成器")
root.geometry("500x450")
root.configure(bg="#f3e5f5")

# --- 标题 ---
title = tk.Label(
    root,
    text="✨ 名字生成器",
    font=("微软雅黑", 22, "bold"),
    fg="#6a1b9a",
    bg="#f3e5f5"
)
title.pack(pady=20)

# --- 提示文字 ---
prompt = tk.Label(
    root,
    text="请输入你的名字：",
    font=("微软雅黑", 14),
    fg="#7b1fa2",
    bg="#f3e5f5"
)
prompt.pack(pady=5)

# --- 输入框 ---
name_entry = tk.Entry(
    root,
    font=("微软雅黑", 16),
    width=20,
    bd=2,
    relief="solid",
    justify="center"
)
name_entry.pack(pady=10)
# 默认显示提示文字
name_entry.insert(0, "在这里输入你的名字")

# --- 结果展示 Label ---
result = tk.Label(
    root,
    text="",
    font=("微软雅黑", 18, "bold"),
    fg="#4a148c",
    bg="#f3e5f5"
)
result.pack(pady=15)

# --- 生成按钮 ---
def generate():
    """读取输入框内容，生成个性化问候"""
    name = name_entry.get()  # ← get() 读取输入框内容
    if name and name != "在这里输入你的名字":
        result.config(text=f"你好，{name}！🎉\n欢迎来到编程世界！")
    else:
        result.config(text="⚠️ 请先输入你的名字哦～")

gen_btn = tk.Button(
    root,
    text="🎯 生成我的专属称呼",
    command=generate,
    font=("微软雅黑", 14),
    bg="#9c27b0",
    fg="white",
    padx=25,
    pady=8
)
gen_btn.pack(pady=8)

# --- 清空按钮 ---
def clear():
    """清空输入框"""
    name_entry.delete(0, tk.END)  # ← 从第0个字符删到末尾

clear_btn = tk.Button(
    root,
    text="🗑️ 清空",
    command=clear,
    font=("微软雅黑", 12),
    bg="#ce93d8",
    fg="white",
    padx=15,
    pady=5
)
clear_btn.pack(pady=5)

# --- 蜜码输入演示区 ---
pwd_label = tk.Label(
    root,
    text="----- 蜜码模式演示 -----",
    font=("微软雅黑", 10),
    fg="#ab47bc",
    bg="#f3e5f5"
)
pwd_label.pack(pady=(25, 5))

pwd_entry = tk.Entry(
    root,
    font=("微软雅黑", 14),
    width=20,
    show="●",  # ← show 参数：输入时显示 ● 而不是真实字符
    justify="center"
)
pwd_entry.pack(pady=5)
pwd_entry.insert(0, "试试输入蜜码")

root.mainloop()
```

---

## 动手试试 💪

### 🟢 基础练习

1. **修改默认文字**：把输入框中的默认提示文字 `"在这里输入你的名字"` 改成你自己喜欢的提示语。

2. **换个问候语**：修改 `generate()` 函数中的问候话术，让回答更有趣。比如：`"{name}，你是最棒的！💪"`

3. **蜜码输入升级**：修改蜜码演示中的 `show` 参数，试试 `"*"` 和 `"#"` 两种不同的掩码效果。

### 🟡 进阶挑战

4. **字数统计器**：在输入框下方加一个 Label，用 `get()` 实时显示用户输入了多少个字。提示：你可以在 Entry 的每次修改后更新 Label 的文字 `f"已输入 {len(name)} 个字"`。

---

## 小贴士 💡

- **`get()` 记住哦**：Entry 读取内容用 `get()`，和 Label 不一样！Label 用 `cget("text")` 或 `.config(text=...)` 后的 `.cget("text")` 来读取文字。记住：**Entry 用 get，Label 用 cget**！

- **清空再输入**：如果你要在输入框中预填文字，建议先用 `delete()` 清空，再用 `insert()` 插入，避免重复堆积。

- **蜜码框的安全性**：`show` 参数只是**视觉上隐藏**了输入内容，程序内部用 `get()` 还是能读到真实文字的。所以它适合做界面体验，但不能作为真正的加密手段哦。

- **多个 Entry 时**：每个 Entry 控件都要有自己的变量名，就像每个人有自己的名字一样。这样你才知道 `get()` 读取的是哪个输入框的内容。

---

> 🎉 恭喜你！学会了 Entry 输入框，你的程序终于可以**和用户互动**啦！用户输入名字，程序做出响应——这就是交互式程序的开始！
>
> 下一节，我们将做一个综合小练习，把 Label、Button、Entry 三个好朋友组合在一起，打造一个**打招呼机器人**！🤖
