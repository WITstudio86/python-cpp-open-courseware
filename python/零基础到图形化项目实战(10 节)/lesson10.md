# 第 10 课 · 打包发布 — 让所有人用上你的程序！

---

## 🎯 本课目标

- 学会用 **PyInstaller** 把 Python 程序打包成独立可执行文件
- 打包成 `.exe`（Windows）或 `.app`（Mac）
- 自定义程序图标
- 创建程序文件夹，把 `.py` 变成真正的"软件"
- **10 节课总复习**：盘点你学到了什么
- 🎉 结业成就解锁

---

## 📚 新知识

### 10.1 为什么需要打包？

目前运行你的备忘录，需要：
1. 安装 Python
2. 打开 VS Code 或终端
3. 运行 `python lesson9.py`

但如果想发给朋友用，他们可不一定装了 Python！

**PyInstaller** 可以把 Python 程序**打包成一个独立的可执行文件**（`.exe` / `.app`），包含 Python 解释器和所有依赖库。对方不需要安装任何东西，双击就能运行！

```
打包前：
lesson9.py  + Python环境 → 才能运行

打包后：
备忘录.exe  → 直接双击运行！✅
```

### 10.2 安装 PyInstaller

打开终端（Terminal / 命令提示符），输入：

```bash
pip install pyinstaller
```

> `pip` 是 Python 的包管理器，用来安装第三方库。

**验证安装**：

```bash
pyinstaller --version
# 输出类似：6.x.x
```

**如果 `pip` 找不到？**

```bash
# Windows
python -m pip install pyinstaller

# Mac
python3 -m pip install pyinstaller
```

### 10.3 基本打包命令

**最简单的打包**（单文件模式）：

```bash
pyinstaller --onefile lesson9.py
```

参数说明：

| 参数 | 说明 |
|------|------|
| `--onefile` 或 `-F` | 打包成**单个** `.exe` / `.app` 文件 |
| `--windowed` 或 `-w` | 运行时不显示黑色终端窗口（GUI 程序用） |
| `--icon=图标.ico` 或 `-i` | 设置程序图标 |
| `--name="程序名"` 或 `-n` | 指定输出文件名 |
| `--add-data="文件;."` | 打包附带的数据文件 |
| `--clean` | 清理临时文件后重新打包 |

**推荐打包命令**：

```bash
# Windows
pyinstaller --onefile --windowed --name="我的备忘录" lesson9.py

# Mac
pyinstaller --onefile --windowed --name="我的备忘录" lesson9.py
```

### 10.4 理解 PyInstaller 的输出

运行打包命令后，会生成以下文件和文件夹：

```
项目文件夹/
├── lesson9.py              ← 你的源代码
├── todos.txt               ← 数据文件（自动生成）
├── build/                  ← 临时构建文件（可以删除）
│   └── ...
├── dist/                   ← 最终输出！（重要）
│   └── 我的备忘录.exe       ← 🎉 这就是你的程序！
└── 我的备忘录.spec          ← PyInstaller 配置文件
```

> 💡 **`dist/` 文件夹**里面的就是最终成品。把它发给朋友就行了！

### 10.5 处理数据文件

我们的备忘录有 `todos.txt` 数据文件。打包后，这个文件的位置会变化。

**问题**：打包成单个 `.exe` 后，`os.path.exists("todos.txt")` 找的是程序所在目录，这是对的。但如果用户把 `.exe` 放到其他地方运行，数据文件就会被创建在 `.exe` 旁边——这通常就是期望的行为。

**如果需要打包自带数据文件**（如图标、默认配置）：

```bash
# Windows（分号分隔）
pyinstaller --onefile --add-data "todos.txt;." lesson9.py

# Mac（冒号分隔）
pyinstaller --onefile --add-data "todos.txt:." lesson9.py
```

然后在代码中处理路径：

```python
import sys, os

def get_data_path(filename):
    """获取数据文件的正确路径（兼容打包后）"""
    if getattr(sys, 'frozen', False):
        # 打包后运行：文件在临时解压目录
        base_path = sys._MEIPASS
    else:
        # 开发时运行：文件在脚本目录
        base_path = os.path.dirname(os.path.abspath(__file__))
    return os.path.join(base_path, filename)

# 使用
DATA_FILE = get_data_path("todos.txt")
```

> 💡 **`sys.frozen`** — 当程序被 PyInstaller 打包后运行时，这个属性为 `True`。我们可以用它来判断是用临时目录还是脚本目录。

### 10.6 设置程序图标

1. **准备图标文件**：
   - Windows：需要 `.ico` 格式
   - Mac：需要 `.icns` 格式
   - 可以在网上找免费的图标，或自己做一个

2. **转换图标格式**（在线工具）：
   - 搜索 "png to ico converter"
   - 上传图片 → 下载 `.ico` 文件

3. **打包时指定图标**：

```bash
pyinstaller --onefile --windowed --icon=icon.ico --name="我的备忘录" lesson9.py
```

### 10.7 打包注意事项

| 问题 | 解决方案 |
|------|----------|
| 杀毒软件报警 | 正常现象！PyInstaller 打包的 exe 有时会被误报，添加到信任列表即可 |
| 文件太大 | 正常！PyInstaller 打包了 Python 解释器，通常 30-50MB |
| 中文路径报错 | 路径中不要有中文或空格！放在英文目录下打包 |
| 缺少 tkinter | 通常不会，PyInstaller 会自动检测 tkinter 依赖 |
| 运行时闪退 | 检查代码是否有错误；先不加 `--windowed` 看看终端报什么错 |

---

## 💻 动手操作

### 步骤 1：整理项目文件

把 `lesson9.py` 重命名为 `备忘录.py`：

```bash
cp lesson9.py 备忘录.py
```

### 步骤 2：确认程序能正常运行

在打包之前，先确保程序本身没问题：

```bash
python 备忘录.py
```

测试所有功能：添加、删除、标记、搜索、保存、加载。

### 步骤 3：执行打包

```bash
# 打开终端，切换到项目目录
cd "项目文件夹路径"

# 执行打包（带窗口模式 + 单文件 + 自定义名称）
pyinstaller --onefile --windowed --name="我的备忘录" 备忘录.py

# 等待... 通常需要 30 秒到 2 分钟
```

**打包过程输出示例**：

```
120 INFO: PyInstaller: 6.x.x
130 INFO: Python: 3.12.x
140 INFO: Platform: Windows-10
...
5000 INFO: Building EXE...
6000 INFO: EXE completed.
7000 INFO: Build complete!
```

### 步骤 4：测试打包后的程序

1. 进入 `dist/` 文件夹
2. 双击 `我的备忘录.exe`（Windows）或 `我的备忘录.app`（Mac）
3. 测试所有功能是否正常
4. 把 `.exe` 复制到桌面，看看单独运行是否正常

### 步骤 5：分享给朋友！

把 `dist/我的备忘录.exe` 发给朋友，他们**不需要安装 Python**，直接双击就能用！

---

## 🎓 10 节课总复习

### 你学会的所有知识

| 课次 | 主题 | 核心知识点 | 项目进度 |
|------|------|-----------|----------|
| 第 1 课 | 你好 Python | `print()`、变量、`tk.Tk()`、`title()`、`geometry()`、`mainloop()` | 空窗口 |
| 第 2 课 | 放东西进窗口 | `Label`、`Button`、`pack()`、`f-string`、`def`、`command` | 有文字和按钮 |
| 第 3 课 | 输入和列表 | `Entry`、`.get()`、`Listbox`、`list`、`.append()`、`if`、`Frame` | 能添加待办 |
| 第 4 课 | 选中和删除 | `.curselection()`、`.delete()`、`if...else`、`messagebox`、`Scrollbar` | 能管理待办 |
| 第 5 课 | 标记已完成 | `dict`、`for` 循环、`not` 取反、`itemconfig()`、删除线样式 | 完成状态 |
| 第 6 课 | 数据存文件 | `open()`、`with`、`.read()`/`.write()`、`.split()`/`.join()`、`os.path` | 数据持久化 |
| 第 7 课 | 菜单和快捷键 | `Menu`、`add_cascade()`、`add_command()`、`bind_all()`、右键菜单 | 专业菜单 |
| 第 8 课 | 美化界面 | `ttk`、`Style()`、`theme_use()`、`grid()`、`Combobox`、类别标签 | 现代界面 |
| 第 9 课 | 搜索过滤 | `StringVar`、`trace()`、`in` 运算符、实时过滤、`and`/`or` | 搜索筛选 |
| 第 10 课 | 打包发布 | `PyInstaller`、`--onefile`、`--windowed`、图标、发布 🎉 | 独立程序 |

### Python 核心语法掌握

```python
# 你学会了 Python 的这些核心语法：

# 变量和数据类型
name = "小明"           # str 字符串
age = 12                # int 整数
height = 1.65           # float 浮点数
is_student = True       # bool 布尔值

# 数据容器
fruits = ["苹果", "香蕉"]   # list 列表
person = {"name": "小明"}   # dict 字典

# 条件判断
if age >= 12:
    print("中学生")
elif age >= 6:
    print("小学生")
else:
    print("幼儿")

# 循环
for fruit in fruits:
    print(fruit)

# 函数
def greet(name):
    return f"你好，{name}！"

# 文件操作
with open("data.txt", "r", encoding="utf-8") as f:
    content = f.read()
```

### tkinter GUI 核心控件

```python
# 你掌握的 tkinter 控件：
import tkinter as tk
from tkinter import ttk

window = tk.Tk()
tk.Label(window, text="标签")         # 文字标签
tk.Button(window, text="按钮")        # 按钮
tk.Entry(window)                      # 输入框
tk.Listbox(window)                    # 列表框
tk.Menu(window)                       # 菜单
tk.Scrollbar(window)                  # 滚动条
ttk.Combobox(window, values=[...])    # 下拉框
messagebox.showinfo("标题", "内容")    # 弹窗
messagebox.askyesno("标题", "问题")    # 确认弹窗
```

---

## ✏️ 课后挑战

1. **写一份"软件说明书"**：给你的备忘录写一个 README.txt，介绍功能和用法
2. **换一个图标**：在网上找一个免费的备忘录图标，给你的程序换上
3. **打包多个版本**：尝试改成不同窗口大小或主题，打包几个版本看看差异
4. **分享并收集反馈**：把程序发给 3 个同学/朋友，收集他们的改进建议
5. **终极挑战**：想一个新的功能，自己实现它！你已经有了所有需要的技能 💪

---

## 📋 完整打包脚本

为了方便以后重复打包，可以创建一个 `build.sh`（Mac/Linux）或 `build.bat`（Windows）脚本：

**Mac/Linux — `build.sh`**：

```bash
#!/bin/bash
echo "🚀 开始打包备忘录..."
pyinstaller --onefile --windowed --name="我的备忘录" --clean 备忘录.py
echo "✅ 打包完成！文件在 dist/ 文件夹中"
```

**Windows — `build.bat`**：

```batch
@echo off
echo 🚀 开始打包备忘录...
pyinstaller --onefile --windowed --name="我的备忘录" --clean 备忘录.py
echo ✅ 打包完成！文件在 dist\ 文件夹中
pause
```

---

## 🧠 本课小结

| 学到的知识 | 是什么 | 怎么用 |
|-----------|--------|--------|
| `pip install` | 安装第三方库 | `pip install pyinstaller` |
| `pyinstaller` | 打包工具 | `pyinstaller --onefile -w script.py` |
| `--onefile` | 单文件模式 | 打包成单个 .exe |
| `--windowed` | 无终端模式 | GUI 程序不显示黑窗口 |
| `--icon` | 自定义图标 | `--icon=icon.ico` |
| `--name` | 自定义名称 | `--name="我的程序"` |
| `sys.frozen` | 判断是否打包 | 打包后为 `True` |
| `sys._MEIPASS` | 临时解压目录 | 打包后数据文件的位置 |

---

## 🎉 恭喜你！

```
╔══════════════════════════════════════════╗
║                                          ║
║   🎓 恭喜完成「零基础到图形化项目实战」！  ║
║                                          ║
║   你从一行 print("你好") 开始，           ║
║   到现在做出了一个功能完整的桌面应用！     ║
║                                          ║
║   ✅ 掌握了 Python 核心语法               ║
║   ✅ 学会了 tkinter GUI 编程              ║
║   ✅ 做出了"我的备忘录"桌面软件            ║
║   ✅ 学会了打包发布                       ║
║                                          ║
║   🚀 这只是开始！Python 的世界还有：       ║
║   • 网站开发（Flask / Django）            ║
║   • 游戏开发（Pygame）                   ║
║   • 数据分析（Pandas）                   ║
║   • 人工智能（机器学习 / 深度学习）        ║
║                                          ║
║   编程的世界，由你来探索！                 ║
║                                          ║
╚══════════════════════════════════════════╝
```

### 下一步可以做什么？

1. **继续完善备忘录**：添加提醒功能、云端同步、数据加密……
2. **做新项目**：试试计算器、天气预报、小游戏……
3. **学习进阶内容**：面向对象编程（class）、数据库（SQLite）、网络编程（requests）
4. **加入社区**：在 GitHub 上分享你的代码，参与开源项目

> 💡 **记住**：编程不是"学完"的，而是"用熟"的。多写、多改、多折腾，你就能越来越强！

---

## 📖 附录：项目文件结构

```
零基础到图形化项目实战/
├── lesson01.md          ← 第 1 课讲义
├── lesson02.md          ← 第 2 课讲义
├── lesson03.md          ← 第 3 课讲义
├── lesson04.md          ← 第 4 课讲义
├── lesson05.md          ← 第 5 课讲义
├── lesson06.md          ← 第 6 课讲义
├── lesson07.md          ← 第 7 课讲义
├── lesson08.md          ← 第 8 课讲义
├── lesson09.md          ← 第 9 课讲义
├── lesson10.md          ← 第 10 课讲义
├── 备忘录.py             ← 最终版本源代码
├── todos.txt            ← 数据文件（运行时生成）
├── build.sh             ← 打包脚本（Mac/Linux）
├── build.bat            ← 打包脚本（Windows）
├── dist/                ← 打包输出目录
│   └── 我的备忘录.exe    ← 🎉 最终成品！
└── 备忘录.spec           ← PyInstaller 配置文件
```

---

**感谢学习！祝你编程愉快！🐍**
