# 第 9 节：Radiobutton + Checkbutton —— 选择题与多选

## 学习目标

1. 掌握 `Radiobutton` 实现单选题（单选按钮组）
2. 掌握 `Checkbutton` 实现多选题（复选框）
3. 理解 `IntVar` / `StringVar` 变量绑定机制
4. 独立搭建一个完整的"喜好收集器"应用

## 成品预览

一个粉红色风格的喜好收集器，包含性别单选（男 / 女 / 保密）、兴趣爱好多选（玩游戏 / 阅读 / 运动 / 画画 / 音乐），点击"提交"按钮后在下方展示收集结果，支持重置清空。

## 知识点讲解

### 1. Radiobutton —— 单选题

`Radiobutton` 用于在一组互斥选项中选择**唯一一个**。关键参数：

```python
gender_var = tk.StringVar(value="")  # 存储选中值的变量

tk.Radiobutton(root, text="男生", variable=gender_var, value="男生")
tk.Radiobutton(root, text="女生", variable=gender_var, value="女生")
tk.Radiobutton(root, text="保密", variable=gender_var, value="保密")
```

- `variable`：所有同一组的 Radiobutton 必须**绑定到同一个变量**
- `value`：选中此选项时，变量被赋的值
- 一个组内同时只能有一个被选中

### 2. IntVar / StringVar 绑定变量

Tkinter 提供特殊的变量类型来存储组件的值：

| 类型 | 存储内容 | 初始值示例 |
|------|----------|------------|
| `StringVar` | 字符串 | `tk.StringVar(value="")` |
| `IntVar` | 整数 | `tk.IntVar(value=0)` |
| `BooleanVar` | 布尔值 | `tk.BooleanVar(value=False)` |

这些变量的特殊之处在于：**当变量值改变时，绑定它的组件会自动更新**。

```python
# 读取值
print(gender_var.get())   # 获取当前选中的值

# 设置值
gender_var.set("")        # 清空选择
```

### 3. Checkbutton —— 多选题

`Checkbutton` 用于独立的勾选，每个选项之间**互不影响**，可以同时选中多个。

```python
hobby_var = tk.IntVar()  # 每个 Checkbutton 需要自己的变量

tk.Checkbutton(
    root,
    text="玩游戏",
    variable=hobby_var,
    onvalue=1,     # 选中时变量的值
    offvalue=0     # 未选中时变量的值
)
```

关键参数：
- `onvalue`：勾选时变量的值（默认 1）
- `offvalue`：取消勾选时变量的值（默认 0）
- **每个 Checkbutton 需要独立的变量**，这一点与 Radiobutton 不同

### 4. 读取选中值

```python
# 读取单选
gender = gender_var.get()  # 返回 "男生" / "女生" / "保密"

# 读取多选
if hobby1_var.get() == 1:
    print("选中了玩游戏")
```

### 5. 重置所有选项

```python
def reset():
    gender_var.set("")   # 清空单选
    hobby1_var.set(0)    # 逐个清空复选框
    hobby2_var.set(0)
    result_label.config(text="")  # 清空结果展示
```

## 完整代码

见程序文件夹中的 `L09-喜好收集器.py`。

## 动手试试

1. **添加新选项**：在性别选择中增加一个"自定义"选项，在爱好中增加"编程"和"摄影"
2. **修改默认值**：让程序启动时性别默认选中"保密"
3. **改用 BooleanVar**：把爱好选项的 `IntVar` 改成 `BooleanVar`，对比两种方式的区别
4. **增加计数功能**：在结果显示区额外显示"你共选择了 X 项爱好"

## 小贴士

- Radiobutton 的多个选项必须绑定**同一个变量**，否则就不是互斥的单选了
- Checkbutton 的每个选项需要**独立的变量**，否则勾选一个会影响到其他
- `IntVar` 的 `get()` 返回的是整数，`StringVar` 的 `get()` 返回的是字符串
- 如果不设置 `onvalue` 和 `offvalue`，Checkbutton 默认选中为 1、未选中为 0
- 变量需要在函数外部定义（全局或外层作用域），否则回调函数无法访问到它们
