# 第 13 节 · RGB 调色板

## 学习目标
- 学会使用 Scale 滑块控件（`from_`、`to`、`resolution`、`orient`）
- 学会 Scale 的 `command` 回调，实现实时更新
- 了解 Spinbox 数字微调框的用法（`from_`、`to`、`increment`）
- 理解 RGB 颜色模型：红（R）+ 绿（G）+ 蓝（B）混合出所有颜色

## 本节课成品
一个 RGB 调色板：拖动红、绿、蓝三个滑块，右边的预览区会实时显示混合出来的颜色！你还可以用数字微调框精确调节每个通道的值。

---

## 知识点讲解

### 知识点1：RGB 颜色模型

计算机里的所有颜色都可以用**红（Red）、绿（Green）、蓝（Blue）**三种颜色混合出来——这就是 RGB 颜色模型。

| 通道 | 英文 | 范围 | 说明 |
|------|------|------|------|
| R | Red | 0~255 | 红色分量 |
| G | Green | 0~255 | 绿色分量 |
| B | Blue | 0~255 | 蓝色分量 |

- 三个值都是 0 → **黑色**
- 三个值都是 255 → **白色**
- R=255, G=0, B=0 → **纯红色**
- R=0, G=255, B=0 → **纯绿色**
- R=0, G=0, B=255 → **纯蓝色**

在 tkinter 中，用十六进制表示颜色：`"#RRGGBB"`。比如 `"#FF0000"` 就是红色（R=FF=255, G=00, B=00）。

### 知识点2：Scale 滑块控件

Scale 是一个**滑动条**，用户拖动滑块就能选择一个范围内的数值。

```python
scale = tk.Scale(root, from_=0, to=255, orient=tk.HORIZONTAL,
                 length=300, command=on_change)
scale.pack()
```

| 参数 | 说明 | 例子 |
|------|------|------|
| `from_` | 最小值 | `from_=0` |
| `to` | 最大值 | `to=255` |
| `orient` | 方向 | `tk.HORIZONTAL`（横向）或 `tk.VERTICAL`（纵向） |
| `length` | 滑块长度（像素） | `length=300` |
| `resolution` | 步长精度 | `resolution=1`（每次拖 1 格） |
| `command` | 拖动时的回调函数 | `command=on_change` |

**重要：** `from_` 参数名后面有下划线 `_`，因为 `from` 是 Python 的关键字！

**command 回调函数的特点：** 当用户拖动滑块时，tkinter 会自动把当前值传给回调函数。

```python
def on_change(val):
    # val 是字符串，包含滑块当前值
    print(f"当前值：{val}")

scale = tk.Scale(root, from_=0, to=255, command=on_change)
```

### 知识点3：Spinbox 数字微调框

Spinbox 是一个带上下箭头按钮的数字输入框，用户可以点击箭头微调数值，也可以直接输入。

```python
spinbox = tk.Spinbox(root, from_=0, to=255, increment=1, width=5,
                     command=on_spin)
spinbox.pack()
```

| 参数 | 说明 | 例子 |
|------|------|------|
| `from_` | 最小值 | `from_=0` |
| `to` | 最大值 | `to=255` |
| `increment` | 每次点击变化的步长 | `increment=1` |
| `width` | 输入框宽度（字符数） | `width=5` |
| `command` | 点击箭头时的回调函数 | `command=on_spin` |

### 知识点4：Scale 与 Spinbox 联动

让 Scale 和 Spinbox 联动，需要做到两件事：
1. 拖动 Scale 时 → 更新 Spinbox 的显示值
2. 点击 Spinbox 箭头时 → 更新 Scale 的滑块位置

这就需要在各自的回调函数中相互更新对方的值。

---

## 完整代码

```python
import tkinter as tk

# ========================================
# 第 13 节：RGB 调色板
# 知识点：Scale 滑块、Spinbox 数字框、实时颜色更新
# ========================================

root = tk.Tk()
root.title("RGB 调色板")
root.geometry("500x400")
root.configure(bg="#f5f5f5")


# ---------- 颜色更新函数 ----------
def update_color(*args):
    """读取 RGB 三个值，合成颜色并更新预览区"""
    r = red_scale.get()
    g = green_scale.get()
    b = blue_scale.get()

    # 把十进制 RGB 转成十六进制颜色码
    hex_color = f"#{r:02x}{g:02x}{b:02x}"

    # 更新颜色预览区
    color_preview.config(bg=hex_color)

    # 更新颜色值标签
    rgb_label.config(text=f"R: {r}  G: {g}  B: {b}\n{hex_color}")

    # 同步 Spinbox 的值
    red_spin.delete(0, tk.END)
    red_spin.insert(0, str(r))
    green_spin.delete(0, tk.END)
    green_spin.insert(0, str(g))
    blue_spin.delete(0, tk.END)
    blue_spin.insert(0, str(b))


# ---------- 标题 ----------
title_label = tk.Label(root, text="🎨 RGB 调色板", font=("微软雅黑", 20, "bold"),
                       bg="#f5f5f5", fg="#333")
title_label.pack(pady=10)

# ---------- 主容器（左右布局） ----------
main_frame = tk.Frame(root, bg="#f5f5f5")
main_frame.pack(pady=10)

# 左侧：滑块区域
left_frame = tk.Frame(main_frame, bg="#f5f5f5")
left_frame.pack(side=tk.LEFT, padx=(0, 15))

# 右侧：颜色预览区
color_preview = tk.Label(main_frame, text="", bg="#000000",
                         width=18, height=8, relief="ridge", bd=3)
color_preview.pack(side=tk.LEFT)

# ---------- 红色滑块 ----------
red_frame = tk.Frame(left_frame, bg="#f5f5f5")
red_frame.pack(pady=5, anchor="w")
tk.Label(red_frame, text="🔴 R：", font=("微软雅黑", 12),
         bg="#f5f5f5", fg="#c0392b", width=6).pack(side=tk.LEFT)
red_scale = tk.Scale(red_frame, from_=0, to=255, orient=tk.HORIZONTAL,
                     length=220, command=update_color, bg="#f5f5f5")
red_scale.set(128)  # 初始值
red_scale.pack(side=tk.LEFT)
red_spin = tk.Spinbox(red_frame, from_=0, to=255, width=4,
                      command=update_color, font=("微软雅黑", 10))
red_spin.delete(0, tk.END)
red_spin.insert(0, "128")
red_spin.pack(side=tk.LEFT, padx=5)

# ---------- 绿色滑块 ----------
green_frame = tk.Frame(left_frame, bg="#f5f5f5")
green_frame.pack(pady=5, anchor="w")
tk.Label(green_frame, text="🟢 G：", font=("微软雅黑", 12),
         bg="#f5f5f5", fg="#27ae60", width=6).pack(side=tk.LEFT)
green_scale = tk.Scale(green_frame, from_=0, to=255, orient=tk.HORIZONTAL,
                       length=220, command=update_color, bg="#f5f5f5")
green_scale.set(128)
green_scale.pack(side=tk.LEFT)
green_spin = tk.Spinbox(green_frame, from_=0, to=255, width=4,
                        command=update_color, font=("微软雅黑", 10))
green_spin.delete(0, tk.END)
green_spin.insert(0, "128")
green_spin.pack(side=tk.LEFT, padx=5)

# ---------- 蓝色滑块 ----------
blue_frame = tk.Frame(left_frame, bg="#f5f5f5")
blue_frame.pack(pady=5, anchor="w")
tk.Label(blue_frame, text="🔵 B：", font=("微软雅黑", 12),
         bg="#f5f5f5", fg="#2980b9", width=6).pack(side=tk.LEFT)
blue_scale = tk.Scale(blue_frame, from_=0, to=255, orient=tk.HORIZONTAL,
                      length=220, command=update_color, bg="#f5f5f5")
blue_scale.set(128)
blue_scale.pack(side=tk.LEFT)
blue_spin = tk.Spinbox(blue_frame, from_=0, to=255, width=4,
                       command=update_color, font=("微软雅黑", 10))
blue_spin.delete(0, tk.END)
blue_spin.insert(0, "128")
blue_spin.pack(side=tk.LEFT, padx=5)

# ---------- 颜色值信息标签 ----------
rgb_label = tk.Label(root, text="R: 128  G: 128  B: 128\n#808080",
                     font=("微软雅黑", 13), bg="#f5f5f5", fg="#333")
rgb_label.pack(pady=10)

# ---------- 快捷按钮 ----------
def set_preset(r, g, b, name):
    """设置预设颜色"""
    red_scale.set(r)
    green_scale.set(g)
    blue_scale.set(b)
    update_color()

preset_frame = tk.Frame(root, bg="#f5f5f5")
preset_frame.pack(pady=5)
presets = [
    ("红色", 255, 0, 0),
    ("绿色", 0, 255, 0),
    ("蓝色", 0, 0, 255),
    ("白色", 255, 255, 255),
    ("黑色", 0, 0, 0),
]

for name, r, g, b in presets:
    btn = tk.Button(preset_frame, text=name,
                    bg=f"#{r:02x}{g:02x}{b:02x}",
                    fg="white" if (r + g + b) < 384 else "black",
                    font=("微软雅黑", 10),
                    command=lambda r=r, g=g, b=b: set_preset(r, g, b))
    btn.pack(side=tk.LEFT, padx=3)

root.mainloop()
```

---

## 动手试试

1. **改初始颜色**：把三个滑块的初始值从 128 改成其他数值，看看预览区初始是什么颜色
2. **调出你的幸运色**：试着拖动滑块，调出你最爱的颜色，记下它的 RGB 值
3. **挑战题**：增加一个"复制颜色码"按钮，点击后把当前的十六进制颜色码（如 `#FF8800`）复制到剪贴板
4. **挑战题**：增加一个 Label 显示颜色名称——根据 RGB 值判断是"偏红"、"偏绿"还是"偏蓝"

---

## 小贴士
- `from_` 参数后面有下划线是因为 `from` 是 Python 关键字，不能直接用作参数名
- Scale 的 `command` 回调函数会自动接收当前值作参数（字符串类型）
- Spinbox 和 Scale 的 `command` 有些不同：Scale 在拖动时实时触发，Spinbox 在点击箭头时触发
- `f"#{r:02x}"` 是 f-string 格式化，把整数转成两位十六进制（如 255 → "ff"）
- Spinbox 直接输入数值后按回车，不会自动触发 command——需要额外的 `bind("<Return>", ...)` 绑定回车事件
