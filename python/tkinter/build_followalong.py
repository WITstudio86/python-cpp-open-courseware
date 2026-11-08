#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""把 tkinter 课件改成跟打页：每步一份完整程序，data-new 标出新补上的行。

标准对齐「从零开始用 Turtle 做游戏」第 3 课：
讲一页、打一页；打页是到这一步为止的完整代码；绿底是相对上一步新增或替换的行。
"""
from __future__ import annotations

import ast
import difflib
import html
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent
CODE = ROOT / "程序"
PPT = ROOT / "课件"
CONTENT = ROOT / "内容"

# 新行里按顺序命中的第一条，用来写「运行后你该看到」
SEES = [
    (r"\.title\(", "标题栏换成了这一步写的文字。"),
    (r"geometry\(", "窗口变成了你写的宽和高。"),
    (r"Button\(", "窗口里多了按钮。点一下，看它有没有反应。"),
    (r"Radiobutton\(", "出现一组单选，一次只能选中一个。"),
    (r"Checkbutton\(", "出现可以勾选的方框，可以同时选多个。"),
    (r"Entry\(", "出现一个能打字的输入框。"),
    (r"Text\(", "出现一块能写很多行的文本框。"),
    (r"Listbox\(", "出现一份清单，里面能看到多项。"),
    (r"Combobox\(", "出现一个点开才展开的下拉框。"),
    (r"Scale\(", "拖动滑块时，旁边的数字或颜色跟着变。"),
    (r"Spinbox\(", "出现一个可以加减数字的小框。"),
    (r"Canvas\(", "窗口里多了一块画布。"),
    (r"create_", "画布上多出新的图形。"),
    (r"<B1-Motion>", "按住鼠标拖动，画面上有痕迹。"),
    (r"Menu\(", "窗口顶部多了菜单，点开能看到命令。"),
    (r"messagebox", "做完操作后，弹出一个小对话框。"),
    (r"\.grid\(", "控件按行和列对齐，像一张表格。"),
    (r"\.pack\(", "控件排队出现在窗口里，不再叠在同一个点。"),
    (r"Label\(", "窗口里多出一行新的文字。"),
    (r"bind\(", "按键盘或点鼠标时，程序有反应。"),
    (r"after\(", "不用不停点击，画面或数字会自己更新。"),
    (r"configure\(\s*bg|bg\s*=", "背景或控件带上了新的颜色。"),
    (r"mainloop\(", "窗口停在屏幕上，不会一闪而过。"),
]

# 新行里按顺序命中的第一条，用来写「坑」
PITFALLS = [
    (r"command\s*=", "command 后面写函数名，不要加括号。加了括号会马上执行。"),
    (r"\bglobal\b", "函数里要改外面的变量，第一行先写 global。漏了会报 UnboundLocalError。"),
    (r"geometry\(", "窗口大小写成 \"宽x高\"，中间是英文字母 x，不是星号。"),
    (r"bind\(", "bind 的事件名要带尖括号，例如 \"<Return>\"、\"<Button-1>\"。"),
    (r"after\(", "after 的第一个数是毫秒，1000 才是 1 秒。要反复执行，函数末尾再预约自己。"),
    (r"IntVar\(|StringVar\(|BooleanVar\(|DoubleVar\(", "IntVar、StringVar 必须写在 Tk() 之后，不然会报太早创建变量。"),
    (r"\.get\(\)", "Entry 的 get() 得到的是字符串。要拿来计算，先用 int() 转成数字。"),
    (r"messagebox", "用弹窗之前要写 from tkinter import messagebox。"),
    (r"\bttk\.", "ttk 控件要先 from tkinter import ttk。"),
    (r"\.grid\(", "grid 的 row 和 column 从 0 开始。同一个父容器里不要又 pack 又 grid。"),
    (r"\.pack\(", "同一个父容器里不要又 pack 又 grid，否则会直接报错。"),
    (r"random\.", "用 random 之前要 import random。"),
    (r"\bjson\.", "读写 json 时，文件名要和真正保存的文件一致。"),
    (r"Canvas\(|create_", "画布的原点在左上角，y 向下变大，和数学课的坐标不一样。"),
    (r"def ", "def 下面的函数体必须缩进。少缩进一格，运行就会报错。"),
]


def _norm(src: str) -> str:
    return src.replace("\r\n", "\n").strip("\n")


def compress_ranges(nums: list[int]) -> str:
    if not nums:
        return ""
    nums = sorted(set(nums))
    ranges: list[str] = []
    start = prev = nums[0]
    for n in nums[1:]:
        if n == prev + 1:
            prev = n
            continue
        ranges.append(f"{start}-{prev}" if start != prev else str(start))
        start = prev = n
    ranges.append(f"{start}-{prev}" if start != prev else str(start))
    return ",".join(ranges)


def new_line_numbers(old: str, new: str) -> list[int]:
    new_lines = _norm(new).splitlines()
    if not old.strip():
        return list(range(1, len(new_lines) + 1))
    old_lines = _norm(old).splitlines()
    sm = difflib.SequenceMatcher(a=old_lines, b=new_lines, autojunk=False)
    nums: list[int] = []
    for tag, _i1, _i2, j1, j2 in sm.get_opcodes():
        if tag in ("insert", "replace"):
            nums.extend(range(j1 + 1, j2 + 1))
    return nums


def new_line_text(old: str, new: str) -> str:
    lines = _norm(new).splitlines()
    nums = set(new_line_numbers(old, new))
    return "\n".join(lines[i - 1] for i in sorted(nums) if 1 <= i <= len(lines))


def has_mainloop(stmt: ast.AST) -> bool:
    for node in ast.walk(stmt):
        if (
            isinstance(node, ast.Call)
            and isinstance(node.func, ast.Attribute)
            and node.func.attr == "mainloop"
        ):
            return True
    return False


def partition(src: str) -> tuple[list[list[str]], list[str]]:
    """按顶层语句切开。返回 (正文块, mainloop 那一块)。"""
    lines = src.splitlines()
    tree = ast.parse(src)
    chunks: list[list[str]] = []
    prev = 0
    for stmt in tree.body:
        end = stmt.end_lineno or stmt.lineno
        chunks.append(lines[prev:end])
        prev = end
    if prev < len(lines):
        extra = lines[prev:]
        if chunks and any(x.strip() for x in extra):
            chunks[-1].extend(extra)
        elif any(x.strip() for x in extra):
            chunks.append(extra)
    trailer_i = None
    for i, stmt in enumerate(tree.body):
        if has_mainloop(stmt):
            trailer_i = i
    if trailer_i is None:
        raise SystemExit("找不到 mainloop")
    trailer = chunks[trailer_i]
    body = chunks[:trailer_i] + chunks[trailer_i + 1 :]
    return body, trailer


def chunk_is_banner(chunk: list[str]) -> bool:
    for line in chunk[:14]:
        stripped = line.strip()
        if not stripped:
            continue
        if not stripped.startswith("#"):
            return False
        body = stripped[1:].strip()
        if re.search(r"[-=]{3,}", body) and re.search(r"[\u4e00-\u9fffA-Za-z]", body):
            return True
        if re.match(r"第\s*\d+\s*步", body):
            return True
        if re.match(r"\d+\s*[\.、]\s*\S", body):
            return True
        if re.match(r"[-=]{2,}\s*\S", body):
            return True
    return False


def chunk_is_def(chunk: list[str]) -> bool:
    for line in chunk[:16]:
        if line.startswith("def ") or line.startswith("async def ") or line.startswith("class "):
            return True
        if line.strip() and not line.strip().startswith("#"):
            return False
    return False


def join_chunks(chunks: list[list[str]]) -> list[str]:
    lines: list[str] = []
    for chunk in chunks:
        lines.extend(chunk)
    return lines


def line_count(section: list[list[str]]) -> int:
    return sum(len(c) for c in section)


def clean_title(text: str) -> str:
    text = re.sub(r"^第\s*\d+\s*步\s*[：:.]?\s*", "", text)
    text = re.sub(r"^\d+\s*[\.、]\s*", "", text)
    text = re.sub(r"（[^）]*）", "", text)
    text = re.sub(r"\([^)]*\)", "", text)
    text = re.sub(r"\s+", " ", text).strip(" ：:.-")
    if not text or re.fullmatch(r"[-=*\d\s]+", text):
        return ""
    if len(text) <= 20:
        return text.rstrip(" ，,、")
    cut = text[:20]
    tail = re.search(r"[A-Za-z0-9]+$", cut)
    if tail and tail.start() > 4:
        cut = cut[: tail.start()]
    for sep in ("：", ":", "，", ",", "、", " "):
        pos = cut.rfind(sep)
        if pos >= 6:
            cut = cut[:pos]
            break
    return cut.rstrip(" ：:.-,，、") or text[:20].rstrip(" ，,、")


def titles_in(text: str) -> list[str]:
    structured: list[str] = []
    plain: list[str] = []
    for line in text.splitlines():
        stripped = line.strip()
        if not stripped.startswith("#"):
            continue
        body = stripped[1:].strip()
        if re.fullmatch(r"[-=*\s]+", body) or re.match(r"第\s*\d+\s*节", body):
            continue
        matched = re.match(r"[-=]{2,}\s*(.+?)\s*[-=]{2,}$", body)
        if matched and re.search(r"[\u4e00-\u9fffA-Za-z]", matched.group(1)):
            title = clean_title(matched.group(1))
            if title:
                structured.append(title)
            continue
        matched = re.match(r"第\s*\d+\s*步\s*[：:.]?\s*(.+)", body)
        if matched:
            title = clean_title(matched.group(1))
            if title:
                structured.append(title)
            continue
        matched = re.match(r"\d+\s*[\.、]\s*(.+)", body)
        if matched:
            title = clean_title(matched.group(1))
            if title:
                structured.append(title)
            continue
        if (
            line.startswith("# ")
            and not line.startswith("# =")
            and not line.startswith("# -")
            and "。" not in body
            and "！" not in body
            and "？" not in body
            and "注意" not in body
            and re.search(r"[\u4e00-\u9fff]", body)
            and 4 <= len(body) <= 30
        ):
            title = clean_title(body)
            if title:
                plain.append(title)
    return structured or plain


def first_comment(text: str) -> str:
    candidates: list[str] = []
    for line in text.splitlines():
        stripped = line.strip()
        if not stripped.startswith("#"):
            continue
        body = stripped[1:].strip()
        if re.search(r"[-=]{3,}", body):
            continue
        if re.match(r"第\s*\d+\s*[节步]", body) or re.match(r"^\d+\s*[\.、]", body):
            continue
        if len(body) < 8:
            continue
        candidates.append(re.sub(r"\s+", " ", body))
    for body in candidates:
        if any(mark in body for mark in ("——", "。", "因为", "必须", "不要", "注意", "否则", "！")):
            return body[:72]
    return ""


def executable_lines(text: str) -> str:
    kept: list[str] = []
    for line in text.splitlines():
        if line.strip().startswith("#"):
            continue
        kept.append(line)
    return "\n".join(kept)


def match_rule(text: str, rules: list[tuple[str, str]]) -> str:
    for pattern, sentence in rules:
        if re.search(pattern, text):
            return sentence
    return ""


def where_items(text: str) -> list[str]:
    items: list[str] = []
    for name in re.findall(r"^def\s+(\w+)\s*\(", text, re.M):
        items.append(f"写出函数 {name}")
    for widget in re.findall(
        r"\b(?:tk|ttk)\.(Label|Button|Entry|Frame|Text|Canvas|Listbox|Scale|Spinbox|"
        r"Radiobutton|Checkbutton|Menu|Scrollbar|LabelFrame)\b",
        text,
    ):
        label = f"放上 {widget}"
        if label not in items:
            items.append(label)
    if len(items) < 3 and re.search(r"\.grid\(", text):
        items.append("用 grid 按行列摆好")
    if len(items) < 3 and re.search(r"\.pack\(", text):
        items.append("用 pack 把控件放进窗口")
    if not items:
        titles = titles_in(text)
        if titles:
            items.append(f"补上「{titles[0]}」")
        else:
            items.append("把绿底这几行打进同一个文件")
    # 去重并限制 3 条
    uniq: list[str] = []
    for item in items:
        if item not in uniq:
            uniq.append(item)
    return uniq[:3]


def target_max(nlines: int) -> int:
    if nlines <= 40:
        return 3
    if nlines <= 90:
        return 4
    if nlines <= 150:
        return 5
    if nlines <= 220:
        return 6
    if nlines <= 300:
        return 7
    return 8


def group_sections(body: list[list[str]], nlines: int) -> list[list[list[str]]]:
    sections: list[list[list[str]]] = []
    current: list[list[str]] = []
    for chunk in body:
        if current and chunk_is_banner(chunk):
            sections.append(current)
            current = [chunk]
        else:
            current.append(chunk)
    if current:
        sections.append(current)
    if not sections:
        sections = [body]

    # 第 1 步必须已经能创建窗口
    while len(sections) > 1 and "Tk(" not in "\n".join(join_chunks(sections[0])):
        sections[0] = sections[0] + sections[1]
        del sections[1]

    maximum = target_max(nlines)
    minimum = 3 if sum(len(s) for s in sections) >= 3 and nlines >= 18 else 1

    def score_pair(i: int) -> tuple[int, int]:
        left = line_count(sections[i])
        right = line_count(sections[i + 1])
        tiny = 0 if left < 14 or right < 14 else 1
        return (tiny, left + right)

    while len(sections) > maximum:
        index = min(range(len(sections) - 1), key=score_pair)
        sections[index] = sections[index] + sections[index + 1]
        del sections[index + 1]

    while len(sections) < minimum:
        index = max(range(len(sections)), key=lambda i: (len(sections[i]), line_count(sections[i])))
        section = sections[index]
        if len(section) < 2:
            break
        split_at = None
        mid = len(section) / 2
        best = 10**9
        for i in range(1, len(section)):
            if not (chunk_is_banner(section[i]) or chunk_is_def(section[i])):
                continue
            dist = abs(i - mid)
            if dist < best:
                best = dist
                split_at = i
        if split_at is None:
            split_at = max(1, len(section) // 2)
        sections[index : index + 1] = [section[:split_at], section[split_at:]]

    # 某一大段超过 72 行时，按函数或小标题再拆开，避免一步要打一百行
    guard = 0
    while len(sections) < 9 and guard < 12:
        guard += 1
        index = None
        biggest = 72
        for i, section in enumerate(sections):
            count = line_count(section)
            if count > biggest and len(section) >= 2:
                biggest = count
                index = i
        if index is None:
            break
        section = sections[index]
        mid = len(section) / 2
        split_at = None
        best = 10**9
        for i in range(1, len(section)):
            if not (chunk_is_def(section[i]) or chunk_is_banner(section[i])):
                continue
            dist = abs(i - mid)
            if dist < best:
                best = dist
                split_at = i
        if split_at is None:
            split_at = max(1, len(section) // 2)
        sections[index : index + 1] = [section[:split_at], section[split_at:]]

    # 拆段之后仍保证第 1 步已经创建了窗口，否则一运行就会 NameError
    while len(sections) > 1 and "Tk(" not in "\n".join(join_chunks(sections[0])):
        sections[0] = sections[0] + sections[1]
        del sections[1]
    return sections


def inline_md(text: str) -> str:
    parts = re.split(r"(`[^`]+`)", text)
    out: list[str] = []
    for part in parts:
        if len(part) >= 2 and part.startswith("`") and part.endswith("`"):
            out.append('<span class="ic">' + html.escape(part[1:-1]) + "</span>")
        else:
            out.append(html.escape(part).replace("**", ""))
    return "".join(out)


def parse_md(text: str) -> tuple[str, list[str], str]:
    title_match = re.search(r"^#\s+(.+)", text, re.M)
    title = title_match.group(1).strip() if title_match else ""
    goals: list[str] = []
    goal_match = re.search(r"##\s*学习目标\s*\n(.*?)(?=\n##|\Z)", text, re.S)
    if goal_match:
        goals = [m.strip() for m in re.findall(r"^-\s+(.+)", goal_match.group(1), re.M)]
    product = ""
    product_match = re.search(r"##\s*本节课成品[^\n]*\n(.*?)(?=\n##|\n---|\Z)", text, re.S)
    if product_match:
        lines = []
        for line in product_match.group(1).splitlines():
            line = line.strip()
            if not line or line.startswith("#") or line.startswith("|") or line.startswith(">"):
                continue
            lines.append(line)
            if len("".join(lines)) > 80:
                break
        product = " ".join(lines)
    return title, goals, product


def short_title(title: str) -> str:
    return re.sub(r"^第\s*\d+\s*[节课]\s*[·:：\-—|]*\s*", "", title).strip() or title


def lesson_number(path: Path) -> int:
    matched = re.match(r"L(\d+)", path.name)
    if not matched:
        raise SystemExit(f"无法识别课次：{path.name}")
    return int(matched.group(1))


def find_one(folder: Path, number: int) -> Path | None:
    hits = sorted(p for p in folder.iterdir() if re.match(rf"L0*{number}(?:\D|$)", p.name))
    return hits[0] if hits else None


def build_steps(src: str) -> list[dict]:
    body, trailer = partition(src)
    sections = group_sections(body, len(src.splitlines()))
    steps = []
    prev = ""
    for index, section in enumerate(sections, 1):
        lines: list[str] = []
        for sec in sections[:index]:
            lines.extend(join_chunks(sec))
        lines.extend(trailer)
        code = "\n".join(lines)
        ast.parse(code)
        fresh = new_line_text(prev, code)
        if not fresh.strip():
            raise SystemExit(f"第 {index} 步没有新行")
        titles = titles_in(fresh)
        defs = re.findall(r"^def\s+(\w+)\s*\(", fresh, re.M)
        if titles:
            title = titles[0]
        elif "Tk(" in fresh:
            title = "创建窗口"
        elif defs:
            title = defs[0]
        elif re.search(r"^(?:import|from)\s+", fresh, re.M):
            title = "导入模块"
        else:
            title = f"继续补上第 {index} 步"
        executable = executable_lines(fresh)
        if title.startswith("继续补上"):
            shown = re.search(r'text\s*=\s*["\']([^"\']+)', executable)
            if shown:
                label = re.sub(r"[\U0001F300-\U0001FAFF]", "", shown.group(1))
                label = re.split(r"[：:，,！!]", label.strip())[0].strip()
                title = "放上「" + (label[:14] or "新文字") + "」"
        import_only = bool(executable.strip()) and all(
            re.match(r"\s*(import |from )", line) or not line.strip()
            for line in executable.splitlines()
        )
        if not executable.strip():
            see = "这一步主要是注释。运行后窗口还在，画面和上一步一样。"
            pitfall = "说明文字要以 # 开头。漏了 #，Python 会把中文当成代码。"
        elif import_only:
            see = "这一步还不会弹出窗口，只是把后面要用的模块引进来。"
            pitfall = "import 的名字要和后面用的一致。写成 tkinter as tk，后面就要用 tk. 。"
        else:
            see = match_rule(executable, SEES) or "窗口还能打开。绿底这些新行已经出现在窗口里。"
            pitfall = match_rule(executable, PITFALLS) or "打完先运行。报错时先看绿底那几行的引号和缩进。"
        why = first_comment(fresh) or "先让这一小段跑起来。跑通了再往下加，错了也好找。"
        where = where_items(fresh)
        hint = "只打绿底的新行，灰掉的旧行不用重打。"
        if defs:
            hint = f"这一步新写函数 {defs[0]}。" + hint
        elif titles:
            hint = f"这一步补上「{titles[0]}」。" + hint
        steps.append(
            {
                "n": index,
                "title": title,
                "see": see,
                "why": why,
                "pitfall": pitfall,
                "where": where,
                "hint": hint,
                "code": code,
                "spec": compress_ranges(new_line_numbers(prev, code)),
            }
        )
        prev = code
    if _norm(steps[-1]["code"]) != _norm(src):
        raise SystemExit("最后一步和程序文件不一致")
    return steps


def errors_for(src: str) -> list[tuple[str, str, str]]:
    found: list[tuple[str, str, str]] = []

    def add(wrong: str, right: str, why: str) -> None:
        if all(wrong != item[0] for item in found):
            found.append((wrong, right, why))

    if "command=" in src:
        add("command=say_hello()", "command=say_hello", "加了括号，函数会立刻执行，点击时反而不动。")
    if "geometry" in src:
        add('geometry("500*400")', 'geometry("500x400")', "中间必须是英文字母 x。")
    if re.search(r"^\s*global\b", src, re.M):
        add("函数里直接 count += 1", "先写 global count", "漏了 global，改不到外面的变量。")
    if ".pack(" in src and ".grid(" in src:
        add("同一个父容器又 pack 又 grid", "这一层只用一种布局", "混用会报 cannot use geometry manager。")
    if "bind(" in src:
        add('bind("Return", fn)', 'bind("<Return>", fn)', "事件名少了尖括号。")
    if "after(" in src:
        add("after 只调用一次", "函数末尾再 after 自己", "不然数字或画面只动一下就停。")
    add("print(“你好”)", 'print("你好")', "中文引号不是 Python 字符串，一运行就语法错误。")
    if len(found) < 3 and "mainloop" in src:
        add("mainloop() 写在创建控件之前", "mainloop() 放在最后一行", "写在它后面的代码不会执行。")
    return found[:3]


def exercises_for(src: str) -> list[tuple[str, str]]:
    items: list[tuple[str, str]] = []
    matched = re.search(r"\.title\(\s*(['\"])(.+?)\1", src)
    if matched:
        items.append(("改标题", f"把窗口标题「{matched.group(2)}」改成你的名字，运行看标题栏。"))
    matched = re.search(r"(?:bg|fg)\s*=\s*(['\"])(#[0-9A-Fa-f]{3,8}|[A-Za-z]+)\1", src)
    if matched:
        items.append(("改颜色", f"把颜色 {matched.group(2)} 换成 lightyellow 或 #ffe0b2，运行看变化。"))
    matched = re.search(r"geometry\(\s*(['\"])(\d+x\d+)\1", src)
    if matched:
        items.append(("改大小", f"把窗口大小 {matched.group(2)} 的宽加 100，运行看窗口变宽了没有。"))
    matched = re.search(r"font\s*=\s*\(\s*['\"][^'\"]+['\"]\s*,\s*(\d+)", src)
    if matched and len(items) < 3:
        items.append(("改字号", f"把字号 {matched.group(1)} 加 4，运行看文字变大了没有。"))
    pads = [
        ("改一句文字", "找一句界面上的提示，换成你自己的话，运行确认它出现了。"),
        ("改一个间距", "找一个 pady 或 padx，改成 30，看空隙是不是变大。"),
        ("跟同桌换", "和同桌交换一个改法，运行对方的版本。"),
    ]
    for item in pads:
        if len(items) >= 3:
            break
        items.append(item)
    return items[:3]


def collect() -> list[dict]:
    lessons = []
    html_files = sorted(PPT.glob("L*.html"), key=lesson_number)
    for html_path in html_files:
        number = lesson_number(html_path)
        py_path = find_one(CODE, number)
        md_path = find_one(CONTENT, number)
        if py_path is None or md_path is None:
            raise SystemExit(f"第 {number} 节缺少程序或讲义")
        src = py_path.read_text(encoding="utf-8")
        title, goals, product = parse_md(md_path.read_text(encoding="utf-8"))
        steps = build_steps(src)
        lessons.append(
            {
                "n": number,
                "html": html_path,
                "py": py_path,
                "view": CODE / "view" / f"{py_path.stem}.html",
                "title": short_title(title) or html_path.stem,
                "goals": goals,
                "product": product or "把本节程序从头打完，运行后窗口还在。",
                "steps": steps,
                "src": src,
            }
        )
    return lessons


def footer(lesson: dict, index: int, total: int) -> str:
    return (
        f'<div class="deck-footer"><span>第 {lesson["n"]} 节 · {html.escape(lesson["title"])}</span>'
        f'<span class="slide-number" data-current="{index}" data-total="{total}"></span></div>'
    )


def notes(text: str) -> str:
    return f"<aside class=\"notes\">{html.escape(text)}</aside>"


def follow_code(src: str, spec: str) -> str:
    escaped = html.escape(_norm(src))
    return (
        f'<div class="code-card follow-card"><pre class="follow-code" data-new="{spec}">'
        f'<code class="language-python">{escaped}</code></pre></div>'
    )


def build_html(lesson: dict, nxt: dict | None) -> str:
    steps = lesson["steps"]
    n_steps = len(steps)
    slides: list[tuple[str, str, str, str]] = []

    def add(title: str, body: str, note: str, klass: str) -> None:
        slides.append((title, body, note, klass))

    view_href = "../程序/view/" + lesson["view"].name
    py_name = lesson["py"].name
    add(
        "封面",
        f"""
<p class="kicker">Python Tkinter · 第 {lesson["n"]} 节</p>
<h1 class="h1 mt-s">{html.escape(lesson["title"])}</h1>
<p class="lede mt-m">看着课件，一步一步打出今天的程序。灰掉的行是已经打过的，绿底是这一步要补上的。</p>
<div class="row wrap mt-l" style="gap:10px">
  <span class="pill-academic">60–90 分钟</span>
  <span class="pill-academic">同一份文件打到底</span>
  <span class="pill-academic">{n_steps} 步 · 一步一运行</span>
</div>
<div class="cspj-code-btn-wrap">
  <a class="cspj-code-btn" href="{html.escape(view_href)}" target="_blank" rel="noopener">📄 查看配套代码</a>
  <div class="cspj-code-meta">{html.escape(py_name)}</div>
</div>
""",
        "开场先演示成品 10 秒。然后让学生新建今天的文件，从空文件打起。翻一页，打一段，运行一次。",
        "slide full",
    )

    product = lesson["product"]
    add(
        "今天做出来长这样",
        f"""
<p class="kicker">今天的成品</p>
<h2 class="h2 mt-s">{html.escape(lesson["title"])}</h2>
<div class="concept-box mt-m">
  <h4>运行之后</h4>
  <p class="dim">{inline_md(product)}</p>
</div>
<div class="callout"><b>过关线：</b> 文件保存为 <span class="ic">{html.escape(py_name)}</span>，打完最后一步能运行，窗口里能看到这一课的成品。</div>
""",
        "先让学生说出成品里能看见什么，再打开空文件。不要先把完整代码发下去。",
        "slide follow-plain",
    )

    cards = [
        ("1. 新建文件", f"保存为 <span class=\"ic\">{html.escape(py_name)}</span>。今天只改这一份，打到最后。"),
    ]
    for goal in lesson["goals"][:2]:
        cards.append((f"{len(cards) + 1}. 今天要会", inline_md(goal)))
    cards.append((f"{len(cards) + 1}. 每一步都要运行", "绿底打完就运行。窗口还在，再翻下一步。报错就停在这一步。"))
    card_html = "".join(f'<div class="bullet-card"><h4>{html.escape(h)}</h4><p>{p}</p></div>' for h, p in cards[:3])
    add(
        "开工",
        f"""
<p class="kicker">开工检查</p>
<h2 class="h2 mt-s">先把文件建好</h2>
<div class="stack mt-m">{card_html}</div>
""",
        "确认每个人都新建了今天的文件。还在上一课文件里接着写的，让他另存为今天的文件名。",
        "slide follow-plain",
    )

    step_cards = "".join(
        f'<div class="step-card"><div class="n">第 {s["n"]} 步</div>'
        f'<h4>{html.escape(s["title"])}</h4><p>{html.escape(s["see"])}</p></div>'
        for s in steps
    )
    add(
        f"{n_steps}步地图",
        f"""
<p class="kicker">今天走 {n_steps} 步</p>
<h2 class="h2 mt-s">每一步都要<span class="grad">运行一次</span></h2>
<div class="step-grid">{step_cards}</div>
""",
        "用这一页告诉学生今天停在哪一步算跟上。掉队的人不要跳步。",
        "slide follow-plain",
    )

    for step in steps:
        where = "".join(f"<li>{html.escape(item)}</li>" for item in step["where"])
        add(
            f"第{step['n']}步 · 讲",
            f"""
<p class="kicker">第 {step['n']} / {n_steps} 步 · 讲</p>
<h2 class="h2 mt-s">{html.escape(step['title'])}</h2>
<p class="lede mt-s">{html.escape(step['see'])}</p>
<div class="callout"><b>为什么：</b> {html.escape(step['why'])}</div>
<ol class="where-list">{where}</ol>
<div class="run-see"><b>运行后你该看到：</b> {html.escape(step['see'])}</div>
""",
            f"先讲这一步要补在哪，再翻到打页。问学生：运行之后你应该看到什么？约这一步 8 到 12 分钟。",
            "slide follow-talk",
        )
        add(
            f"第{step['n']}步 · 打",
            f"""
<p class="kicker">第 {step['n']} / {n_steps} 步 · 打</p>
<h2 class="h2 mt-s">{html.escape(step['title'])}</h2>
<p class="lede" style="margin-top:4px">{html.escape(step['hint'])}</p>
<p class="legend-new"><span class="swatch"></span>绿底是这一步要新打的行。灰掉的行前面已经打过。</p>
{follow_code(step['code'], step['spec'])}
<div class="run-see"><b>运行后你该看到：</b> {html.escape(step['see'])}</div>
<div class="pitfall"><b>坑：</b> {html.escape(step['pitfall'])}</div>
""",
            "等全班运行通过再翻下一步。报错的人对照绿底，不要整份重打。",
            "slide follow-type",
        )

    err_html = "".join(
        f'<div class="bullet-card"><h4>❌ {html.escape(wrong)}</h4>'
        f'<p>✅ {html.escape(right)}<br>{html.escape(why)}</p></div>'
        for wrong, right, why in errors_for(lesson["src"])
    )
    add(
        "改错",
        f"""
<p class="kicker">改错时刻</p>
<h2 class="h2 mt-s">这三处最容易错</h2>
<div class="stack mt-m">{err_html}</div>
""",
        "挑一个学生的报错，对着这三张卡片对一下。先问他错在哪，再公布正确写法。",
        "slide follow-plain",
    )

    ex_html = "".join(
        f'<div class="concept-box"><h4>{i}. {html.escape(title)}</h4><p class="dim">{html.escape(desc)}</p></div>'
        for i, (title, desc) in enumerate(exercises_for(lesson["src"]), 1)
    )
    add(
        "改一改",
        f"""
<p class="kicker">改一改</p>
<h2 class="h2 mt-s">程序能跑了，再改一处</h2>
<div class="stack mt-m">{ex_html}</div>
""",
        "主程序没跑通的人继续改错，不要做改一改。跑通的人只改一处，改完必须再运行。",
        "slide follow-plain",
    )

    rows = "".join(
        f"<tr><td>{html.escape(step['title'])}</td><td>{html.escape(step['see'])}</td>"
        f"<td>{html.escape(step['pitfall'])}</td></tr>"
        for step in steps
    )
    if nxt:
        next_line = f"第 {nxt['n']} 节 · {nxt['title']}"
    else:
        next_line = "课程到这里。用今天的窗口骨架，做一件你自己想做的小程序。"
    add(
        "本课小结",
        f"""
<p class="kicker">本课小结</p>
<h1 class="h1 mt-s" style="font-size:42px">你今天<span class="grad">一步一步打出来了</span></h1>
<div class="card mt-m" style="padding:8px 12px;max-height:46vh;overflow:auto">
  <table class="sum-table">
    <thead><tr><th>这一步</th><th>运行后</th><th>记住的坑</th></tr></thead>
    <tbody>{rows}</tbody>
  </table>
</div>
<div class="callout"><b>下一节：</b> {html.escape(next_line)}</div>
""",
        "让两个学生用自己的话说：绿底是什么意思，mainloop 为什么在最后。再预告下一节。",
        "slide full",
    )

    total = len(slides)
    parts = []
    for index, (title, body, note, klass) in enumerate(slides, 1):
        if index == 1:
            klass += " is-active"
        parts.append(
            f'<section class="{klass}" data-title="{html.escape(title)}">\n'
            f"{body}\n{footer(lesson, index, total)}\n{notes(note)}\n</section>"
        )
    inner = "\n\n".join(parts)
    return f"""<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>第{lesson["n"]}节 · {html.escape(lesson["title"])} · Python Tkinter</title>
<link rel="stylesheet" href="assets/fonts.css">
<link rel="stylesheet" href="assets/base.css">
<link rel="stylesheet" id="theme-link" href="assets/themes/soft-pastel.css">
<link rel="stylesheet" href="assets/animations/animations.css">
<link rel="stylesheet" href="style.css">
</head>
<body class="tpl-tkinter-course" data-theme-base="assets/themes/" data-themes="soft-pastel,rainbow-gradient,sunset-warm,minimal-white">
<div class="deck">
{inner}
</div>
<script src="assets/runtime.js"></script>
<script src="courseware-ui.js"></script>
</body>
</html>
"""


def main() -> None:
    write = "--write" in sys.argv
    lessons = collect()
    report = []
    for i, lesson in enumerate(lessons):
        nxt = lessons[i + 1] if i + 1 < len(lessons) else None
        specs = []
        for step in lesson["steps"]:
            specs.append(f"    {step['n']} {step['title']}  +{step['spec']}")
        report.append(
            f"L{lesson['n']:02d} {lesson['title']}  {len(lesson['steps'])}步  {lesson['py'].name}\n"
            + "\n".join(specs)
        )
        if write:
            lesson["html"].write_text(build_html(lesson, nxt), encoding="utf-8")
    text = "\n".join(report)
    print(text)
    print(f"\nlessons={len(lessons)} write={write}")


if __name__ == "__main__":
    main()
