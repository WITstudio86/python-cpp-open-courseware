import tkinter as tk
import requests

# ========================================
# 第 29 节：项目 6 — 天气预报查询（上）
# 功能：输入城市名 → 调用 wttr.in API → 显示天气
# ========================================

# 1. 创建主窗口
root = tk.Tk()
root.title("天气预报查询 🌤️")
root.geometry("480x480")
root.configure(bg="#e8f4fd")  # 浅蓝色背景，天空的感觉

# ========================================
# 2. API 调用函数
# ========================================

def get_weather(city):
    """
    调用 wttr.in 免费天气 API，获取指定城市的天气数据
    参数：city - 城市名（中文或英文）
    返回：JSON 数据字典，失败返回 None
    """
    try:
        # wttr.in 的 JSON 格式 API
        # ?format=j1 表示返回 JSON 格式的详细天气数据
        url = f"https://wttr.in/{city}?format=j1"

        # 发送 GET 请求，timeout=5 表示最多等 5 秒
        response = requests.get(url, timeout=5)

        # 检查 HTTP 状态码，不是 200 就抛出异常
        response.raise_for_status()

        # 把返回的 JSON 字符串转成 Python 字典
        return response.json()

    except requests.exceptions.ConnectionError:
        # 网络连接失败（比如没联网）
        return None
    except requests.exceptions.Timeout:
        # 请求超时（网络太慢）
        return None
    except Exception:
        # 其他任何错误（城市名错误、服务器故障等）
        return None


# ========================================
# 3. 查询功能
# ========================================

def search():
    """获取输入框中的城市名，查询天气并更新显示"""
    city = entry.get().strip()  # 获取输入，去掉首尾空格

    # 检查是否输入了城市名
    if not city:
        result_label.config(
            text="⚠️ 请输入城市名！\n例如：北京、上海、Tokyo",
            fg="#c0392b"
        )
        return

    # 显示"查询中"提示
    result_label.config(text="🔄 正在查询天气，请稍候...", fg="#7f8c8d")
    root.update()  # 强制刷新界面，让用户看到提示

    # 调用 API 获取数据
    data = get_weather(city)

    # 检查是否获取成功
    if data is None:
        result_label.config(
            text="❌ 网络连接失败！\n请检查网络后重试",
            fg="#c0392b"
        )
        return

    # 解析 JSON 数据，提取天气信息
    try:
        # current_condition 是一个列表，[0] 取第一个（当前天气）
        current = data["current_condition"][0]

        # 提取各项天气数据
        temp = current["temp_C"]                        # 当前温度（摄氏度）
        feels_like = current["FeelsLikeC"]              # 体感温度
        desc = current["weatherDesc"][0]["value"]       # 天气描述（晴、多云等）
        humidity = current["humidity"]                  # 湿度百分比
        wind_speed = current["windspeedKmph"]           # 风速（公里/小时）
        wind_dir = current["winddir16Point"]            # 风向（16 方位）
        visibility = current["visibility"]              # 能见度（公里）

        # 组装显示文字
        result_text = (
            f"🏙️  城市：{city}\n"
            f"{'─' * 30}\n"
            f"🌡️  温度：{temp}°C（体感 {feels_like}°C）\n"
            f"☁️  天气：{desc}\n"
            f"💧  湿度：{humidity}%\n"
            f"💨  风速：{wind_speed} km/h（{wind_dir}）\n"
            f"👁️  能见度：{visibility} km"
        )

        result_label.config(text=result_text, fg="#2c3e50")

    except (KeyError, IndexError):
        # 城市名可能存在但数据格式不对
        result_label.config(
            text="❌ 未找到该城市的信息\n请检查城市名是否正确",
            fg="#c0392b"
        )


# ========================================
# 4. 界面布局
# ========================================

# --- 标题 ---
title_label = tk.Label(
    root,
    text="🌤️  天气预报查询",
    font=("微软雅黑", 24, "bold"),
    bg="#e8f4fd",
    fg="#1a5276"
)
title_label.pack(pady=(25, 10))

# --- 说明文字 ---
hint_label = tk.Label(
    root,
    text="输入城市名，支持中文和英文",
    font=("微软雅黑", 11),
    bg="#e8f4fd",
    fg="#7f8c8d"
)
hint_label.pack()

# --- 输入框 ---
entry = tk.Entry(
    root,
    font=("微软雅黑", 16),
    width=20,
    justify="center",  # 文字居中
    relief="solid",
    bd=1
)
entry.pack(pady=(15, 5))

# 绑定回车键：在输入框按回车也能查询
entry.bind("<Return>", lambda event: search())

# --- 查询按钮 ---
search_btn = tk.Button(
    root,
    text="🔍 查询天气",
    command=search,
    font=("微软雅黑", 14, "bold"),
    bg="#3498db",
    fg="white",
    padx=30,
    pady=6,
    relief="flat",
    cursor="hand2"
)
search_btn.pack(pady=15)

# --- 结果展示区域 ---
result_label = tk.Label(
    root,
    text="",
    font=("微软雅黑", 13),
    bg="#e8f4fd",
    fg="#2c3e50",
    justify=tk.LEFT,  # 文字左对齐
    anchor="w"        # 标签内的文字靠左
)
result_label.pack(pady=(10, 20), padx=30, fill=tk.BOTH)

# --- 底部提示 ---
footer_label = tk.Label(
    root,
    text="数据来源：wttr.in（免费天气 API）",
    font=("微软雅黑", 9),
    bg="#e8f4fd",
    fg="#bdc3c7"
)
footer_label.pack(side=tk.BOTTOM, pady=10)

# ========================================
# 5. 启动主循环
# ========================================

# 让输入框自动获得焦点
entry.focus_set()

root.mainloop()
