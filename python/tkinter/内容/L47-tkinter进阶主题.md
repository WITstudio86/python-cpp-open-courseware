# 第 47 节 · tkinter 进阶主题

## 学习目标
- 了解 ttk 主题美化（`ttk.Style` 设置全局样式）🎨
- 学会设置窗口图标（`iconbitmap` / `iconphoto`）🪟
- 了解 pyinstaller 打包成 exe 的基本方法 📦
- 认识几个好用的 tkinter 扩展库 🔌

## 本节成品
用 ttk 美化后的番茄钟界面对比——同一个功能，换个风格立刻"高大上"！

> 这节课偏**演示讲解**，重点在开阔眼界。代码以展示为主，动手做简单尝试即可。

---

## 知识点讲解

### 1. ttk 主题美化

`ttk`（themed tk）是 tkinter 的"美化版"。同样的控件，ttk 版本会随操作系统主题变化，看起来更现代化。

```python
import tkinter as tk
from tkinter import ttk

root = tk.Tk()
root.title("ttk 主题演示")
root.geometry("500x400")

# 查看所有可用主题
print(ttk.Style().theme_names())
# 输出示例：('clam', 'alt', 'default', 'classic', 'vista', 'xpnative', 'aqua')

# 设置主题
style = ttk.Style()
style.theme_use("clam")  # macOS 常用 aqua, Windows 用 vista

# 自定义样式
style.configure("TButton", font=("微软雅黑", 12), padding=10)
style.configure("TLabel", font=("微软雅黑", 14), background="#f0f0f0")
style.configure("Timer.TLabel", font=("微软雅黑", 48, "bold"), foreground="#e91e63")
# "Timer.TLabel" 是自定义子样式，只影响指定了这个样式的 Label
```

**对比：tk 控件 vs ttk 控件**

| 功能 | tk 写法 | ttk 写法 |
|------|---------|----------|
| 按钮 | `tk.Button(root, text="确定")` | `ttk.Button(root, text="确定")` |
| 标签 | `tk.Label(root, text="你好")` | `ttk.Label(root, text="你好")` |
| 输入框 | `tk.Entry(root)` | `ttk.Entry(root)` |
| 进度条 | 无内置 | `ttk.Progressbar(root)` |
| 组合框 | 无内置 | `ttk.Combobox(root)` |

ttk 有而 tk 没有的控件：`Progressbar`、`Combobox`、`Notebook`（选项卡）、`Treeview`（我们一直在用！）。

### 2. 番茄钟界面对比演示

下面是同一个番茄钟功能，用**普通 tk** 和 **ttk 美化**两种方式实现的对比：

**普通 tk 版本（朴素）**：
```python
timer_label = tk.Label(root, text="25:00", font=("Arial", 48),
                       bg="white", fg="black")
start_btn = tk.Button(root, text="开始", bg="lightgreen")
```

**ttk 美化版本（好看）**：
```python
style = ttk.Style()
style.theme_use("clam")
style.configure("Timer.TLabel", font=("微软雅黑", 60, "bold"),
                foreground="#e91e63", background="#fff3e0")
style.configure("Start.TButton", font=("微软雅黑", 14),
                padding=(20, 10))

timer_label = ttk.Label(root, text="25:00", style="Timer.TLabel")
start_btn = ttk.Button(root, text="开始", style="Start.TButton")
```

**美化效果**：
- 按钮有圆角、悬停变色、按下有动画
- 字体更大更清晰
- 配色更协调
- 整体看起来像"真正的软件"

### 3. 设置窗口图标

给窗口左上角加上自定义图标：

```python
# 方法 1：ico 格式（Windows 常用，macOS 兼容）
root.iconbitmap("icon.ico")

# 方法 2：png/gif 格式（macOS/跨平台推荐）
icon_img = tk.PhotoImage(file="icon.png")
root.iconphoto(True, icon_img)
```

> 没有图标文件？可以先用 Python 画一个简单的图标，或者从网上下载一个免费图标。

### 4. pyinstaller 打包成 exe

写完程序后，怎么分享给没有安装 Python 的朋友？用 **pyinstaller** 打包！

```bash
# 1. 安装 pyinstaller
pip install pyinstaller

# 2. 打包成单个 exe 文件
pyinstaller --onefile --windowed --name "我的程序" main.py

# 参数说明：
# --onefile   → 打包成单个文件
# --windowed  → 不显示命令行黑窗口（GUI 程序必加！）
# --name      → 指定生成的 exe 文件名
# --icon      → 指定 exe 的图标（Windows）
```

打包完成后，在 `dist/` 文件夹里找到 `.exe` 文件，发给别人就能直接双击运行了！

```bash
# 完整示例（带图标）
pyinstaller --onefile --windowed --name "番茄钟" --icon tomato.ico tomato_timer.py
```

**注意事项**：
- 打包后的文件较大（因为包含了 Python 解释器）
- macOS 用户打包成 `.app`（同样用 pyinstaller）
- 如果程序用到了外部文件（如 JSON 数据），要注意路径问题

### 5. 好用的 tkinter 扩展库

| 扩展库 | 作用 | 安装 |
|--------|------|------|
| **sv_ttk** | 一键让 ttk 变好看（Sun Valley 主题） | `pip install sv-ttk` |
| **tkinterweb** | 在 tkinter 里显示网页 | `pip install tkinterweb` |
| **Pillow** | 处理图片（显示 jpg/png） | `pip install Pillow` |
| **tkcalendar** | 日期选择器控件 | `pip install tkcalendar` |
| **customtkinter** | 全新的现代化 UI 框架 | `pip install customtkinter` |

**sv_ttk 示例（两行代码美化整个程序）**：
```python
import sv_ttk
import tkinter as tk
from tkinter import ttk

root = tk.Tk()
sv_ttk.set_theme("dark")  # 一键切换暗色主题！
# 之后所有 ttk 控件都会自动变好看
```

**customtkinter 示例（更现代化的选择）**：
```python
import customtkinter as ctk

ctk.set_appearance_mode("dark")  # 暗色模式
root = ctk.CTk()
btn = ctk.CTkButton(root, text="现代按钮")  # 自带圆角、动画
```

---

## 完整代码（ttk 美化番茄钟对比演示）

```python
import tkinter as tk
from tkinter import ttk

# ========================================
# 第 47 节：tkinter 进阶 —— ttk 美化番茄钟对比
# ========================================

root = tk.Tk()
root.title("番茄钟 · ttk 美化版")
root.geometry("420x480")
root.configure(bg="#fafafa")

# ---- 设置 ttk 主题和样式 ----
style = ttk.Style()
style.theme_use("clam")  # 如果用 macOS，试试 "aqua"

# 全局样式
style.configure("TLabel", font=("微软雅黑", 12), background="#fafafa")
style.configure("TButton", font=("微软雅黑", 11), padding=(15, 8))

# 自定义子样式
style.configure("Title.TLabel", font=("微软雅黑", 20, "bold"),
                foreground="#e65100", background="#fafafa")
style.configure("Timer.TLabel", font=("微软雅黑", 56, "bold"),
                foreground="#1565c0", background="white")
style.configure("Start.TButton", font=("微软雅黑", 13, "bold"),
                padding=(25, 10))
style.configure("Reset.TButton", font=("微软雅黑", 11))

# 主容器
main_frame = tk.Frame(root, bg="#fafafa")
main_frame.pack(expand=True, fill=tk.BOTH, padx=30, pady=20)

# 标题
ttk.Label(main_frame, text="🍅 番茄钟", style="Title.TLabel").pack(pady=(10, 5))

# 计时器显示（用 Frame 包一层做白色背景）
timer_bg = tk.Frame(main_frame, bg="white", relief=tk.RIDGE, bd=2)
timer_bg.pack(pady=20, ipadx=40, ipady=30)

timer_label = ttk.Label(timer_bg, text="25:00", style="Timer.TLabel")
timer_label.pack()

# 模式显示
mode_var = tk.StringVar(value="▶ 工作中...")
mode_label = ttk.Label(main_frame, textvariable=mode_var,
                       font=("微软雅黑", 13), foreground="#666")
mode_label.pack(pady=5)

# 进度条
progress = ttk.Progressbar(main_frame, length=300, mode="determinate")
progress.pack(pady=(10, 20))

# 按钮区域
btn_frame = tk.Frame(main_frame, bg="#fafafa")
btn_frame.pack(pady=10)

ttk.Button(btn_frame, text="▶ 开始专注", style="Start.TButton").pack(side=tk.LEFT, padx=5)
ttk.Button(btn_frame, text="🔄 重置", style="Reset.TButton").pack(side=tk.LEFT, padx=5)

# 时间设置
setting_frame = tk.Frame(main_frame, bg="#fafafa")
setting_frame.pack(pady=20)

ttk.Label(setting_frame, text="时长设置：").pack(side=tk.LEFT)
ttk.Combobox(setting_frame, values=["15分钟", "25分钟", "45分钟", "60分钟"],
             width=10, state="readonly").pack(side=tk.LEFT, padx=10)
ttk.Combobox(setting_frame, values=["15分钟", "25分钟", "45分钟", "60分钟"],
             width=10, state="readonly").pack(side=tk.LEFT, padx=10)
# 默认选中第2项（25分钟）
setting_frame.winfo_children()[-1].current(1)

# 底部提示
ttk.Label(main_frame, text="💡 ttk 主题让界面更现代化 | 试试切换 theme_use 看不同风格",
          font=("微软雅黑", 9), foreground="#aaa").pack(pady=(15, 0))

# ---- 如果想看普通 tk 的对比效果，取消下面注释 ----
# root2 = tk.Tk()
# root2.title("番茄钟 · 普通 tk 版")
# root2.geometry("350x400")
# root2.configure(bg="white")
# tk.Label(root2, text="🍅 番茄钟", font=("Arial", 20, "bold"),
#          bg="white").pack(pady=20)
# tk.Label(root2, text="25:00", font=("Arial", 48),
#          bg="white").pack(pady=20)
# tk.Button(root2, text="开始", font=("Arial", 12),
#           bg="lightgreen", width=10).pack(pady=10)

root.mainloop()
```

---

## 动手试试

1. **换个主题**：把 `theme_use("clam")` 换成 `"alt"` 或 `"default"` 看看效果
2. **改颜色**：修改 `style.configure` 里的 `foreground` 和 `background`
3. **试试加图标**：找一个 `.png` 文件，用 `iconphoto` 设置窗口图标
4. **探索**：如果你感兴趣，课后试试安装 `sv_ttk` 或 `customtkinter`

---

## 小贴士
- ttk 控件**不支持** `bg`、`fg` 等参数，所有样式必须通过 `style.configure()` 设置
- `style.configure("TButton", ...)` 影响所有 ttk 按钮
- `style.configure("My.TButton", ...)` 只影响指定了 `style="My.TButton"` 的按钮
- macOS 上 ttk 默认主题就是 `aqua`，和系统风格一致
- pyinstaller 打包时 `--windowed` 很重要，否则运行时会弹出黑窗口
- `sv_ttk` 是社区开发的，安装后一行代码 `sv_ttk.set_theme("dark")` 就能让程序变暗色主题
