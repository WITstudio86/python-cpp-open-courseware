#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""跟打课件共享引擎：讲/打页、学案、教案、终稿 .py。"""
from __future__ import annotations

import ast
import difflib
import html
from pathlib import Path

ROOT = Path(__file__).resolve().parent
PPT = ROOT / "ppt"
PRINT = ROOT / "打印"
CODE = ROOT / "code"

EXTRA_CSS = r"""
  .slide.follow-talk, .slide.follow-type { justify-content: flex-start; padding-top: 40px; padding-bottom: 64px; }
  .slide.follow-type .h2 { font-size: 28px; }
  .where-list { margin: 16px 0 0; padding-left: 1.2em; color: var(--text-2); font-size: 18px; line-height: 1.7; }
  .where-list li { margin: 6px 0; }
  .run-see { border-left: 4px solid var(--accent-3); background: var(--surface); padding: 12px 16px; border-radius: 0 var(--radius) var(--radius) 0; font-size: 15px; color: var(--text-2); margin-top: 14px; }
  .run-see b { color: var(--accent-3); }
  .pitfall { border-left: 4px solid var(--bad); background: var(--surface); padding: 12px 16px; border-radius: 0 var(--radius) var(--radius) 0; font-size: 15px; color: var(--text-2); margin-top: 10px; }
  .pitfall b { color: var(--bad); }
  .follow-card { padding: 10px 12px !important; max-height: 58vh; }
  .slide pre.follow-code,
  .follow-code {
    margin: 0;
    max-height: 56vh;
    overflow: auto;
    font-size: 20px !important;
    line-height: 1.15 !important;
  }
  .slide pre.follow-code code,
  .follow-code code {
    display: block;
    font-size: 20px !important;
    line-height: 1.15 !important;
    color: #f8f8f2;
  }
  .follow-code .line-old, .follow-code .line-new {
    display: block;
    padding: 0 8px;
    margin: 0;
    font-size: 20px !important;
    line-height: 1.15 !important;
  }
  .follow-code .line-old { opacity: .42; }
  .follow-code .line-new { opacity: 1; background: rgba(80,250,123,.16); box-shadow: inset 4px 0 0 #50fa7b; }
  .tok-kw { color: #ff79c6; }
  .tok-str { color: #f1fa8c; }
  .tok-num { color: #bd93f9; }
  .tok-cmt { color: #6272a4; font-style: italic; }
  .tok-fn { color: #50fa7b; }
  .tok-bi { color: #8be9fd; }
  .step-grid { display: grid; grid-template-columns: 1fr 1fr; gap: 12px; margin-top: 22px; }
  .step-card { background: var(--surface); border: 1px solid var(--border); border-radius: var(--radius); padding: 14px 16px; }
  .step-card .n { color: var(--accent); font-weight: 800; font-size: 13px; letter-spacing: .08em; }
  .step-card h4 { margin: 4px 0 4px; font-size: 18px; }
  .step-card p { margin: 0; font-size: 14px; color: var(--text-2); }
"""


def _norm(src: str) -> str:
    return src.replace("\r\n", "\n").strip("\n") + "\n"


def _compress_ranges(nums: list[int]) -> str:
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


def new_line_spec(old: str, new: str) -> str:
    new_lines = _norm(new).splitlines()
    if not old.strip():
        return _compress_ranges(list(range(1, len(new_lines) + 1)))
    old_lines = _norm(old).splitlines()
    sm = difflib.SequenceMatcher(a=old_lines, b=new_lines, autojunk=False)
    nums: list[int] = []
    for tag, _i1, _i2, j1, j2 in sm.get_opcodes():
        if tag in ("insert", "replace"):
            nums.extend(range(j1 + 1, j2 + 1))
    return _compress_ranges(nums)


def check_lesson(lesson: dict) -> None:
    prev = ""
    steps = lesson["steps"]
    if not steps:
        raise SystemExit(f"lesson {lesson['n']}: no steps")
    for step in steps:
        ast.parse(step["code"])
        spec = new_line_spec(prev, step["code"])
        if not spec:
            raise SystemExit(f"lesson {lesson['n']} step {step['n']} produced no new lines")
        prev = step["code"]
    last = _norm(steps[-1]["code"])
    if _norm(lesson["final"]) != last:
        raise SystemExit(f"lesson {lesson['n']}: final drifted from last step")
    ch = lesson.get("challenge_code")
    if ch:
        ast.parse(ch)
        needle = lesson.get("challenge_must_contain")
        if needle and needle not in ch:
            raise SystemExit(f"lesson {lesson['n']}: challenge missing {needle!r}")
        ch_spec = new_line_spec(last, ch)
        if not ch_spec:
            raise SystemExit(f"lesson {lesson['n']}: challenge produced no new lines")


def footer(lesson: dict, i: int, total: int) -> str:
    return (
        f'<div class="deck-footer"><span class="dim2">第 {lesson["n"]} 课 · {html.escape(lesson["title"])}</span>'
        f'<span class="slide-number" data-current="{i}" data-total="{total}"></span></div>'
    )


def notes(text: str) -> str:
    return f'<div class="notes">{html.escape(text)}</div>'


def follow_code(src: str, spec: str) -> str:
    return (
        f'<div class="code-card follow-card"><pre class="follow-code" data-new="{spec}">'
        f'<code class="language-python">{html.escape(_norm(src).rstrip(chr(10)))}</code></pre></div>'
    )


def build_ppt(lesson: dict) -> str:
    import sys

    if str(ROOT) not in sys.path:
        sys.path.insert(0, str(ROOT))
    from _build_html import PPT_CSS

    n = lesson["n"]
    n_steps = len(lesson["steps"])
    slides: list[tuple[str, str, str, str]] = []

    def add(title: str, body: str, note: str, klass: str = "slide") -> None:
        slides.append((title, body, note, klass))

    add(
        "Cover",
        f"""
    <p class="kicker anim-fade-down" data-anim="fade-down" style="color:var(--accent-2)">从零开始用 Turtle 做游戏 · 第 {n} 课</p>
    <h1 class="h1 anim-rise-in" data-anim="rise-in" style="font-size:72px;margin-top:12px">{lesson["icon"]} <span class="grad">{html.escape(lesson["title"])}</span></h1>
    <p class="lede anim-fade-up" data-anim="fade-up" style="margin-top:16px;font-size:22px">看着课件，一步一步打出「{html.escape(lesson["project"])}」</p>
    <div class="row wrap anim-fade-up" data-anim="fade-up" style="margin-top:32px;gap:12px;justify-content:center">
      <span class="pill" style="background:rgba(189,147,249,.15);color:var(--accent);border:1px solid rgba(189,147,249,.3)">90 分钟</span>
      <span class="pill" style="background:rgba(139,233,253,.15);color:var(--accent-3);border:1px solid rgba(139,233,253,.3)">同一份文件打到底</span>
      <span class="pill" style="background:rgba(255,121,198,.15);color:var(--accent-2);border:1px solid rgba(255,121,198,.3)">{n_steps} 步 · 一步一运行</span>
    </div>
    <div>
      <a href="../code/lesson{n}.py" target="_blank" class="code-btn"><span class="btn-icon">📄</span> 查看完整代码</a>
      <a href="../打印/lesson{n:02d}.html" target="_blank" class="print-btn">🖨️ 打印学案</a>
    </div>
    """,
        lesson["cover_note"],
        "slide full",
    )

    io_html = html.escape(lesson["io"])
    add(
        "今天做出来长这样",
        f"""
    <p class="kicker">🎮 今天的成品</p>
    <h2 class="h2" style="margin-top:6px">{html.escape(lesson["project"])}</h2>
    <div class="io-card" style="margin-top:22px;background:var(--surface);border:1px solid var(--border);border-radius:var(--radius);padding:18px 22px">
      <div style="font-size:12px;color:var(--text-3);letter-spacing:.1em;margin-bottom:8px">玩法</div>
      <pre style="margin:0;font-family:'JetBrains Mono',monospace;font-size:18px;line-height:1.7;color:var(--text-1);white-space:pre-wrap">{io_html}</pre>
    </div>
    <div class="callout" style="margin-top:18px"><b>过关线：</b> {html.escape(lesson["pass_line"])} 加码不是全班必须完成。</div>
    """,
        lesson["product_note"],
    )

    start_cards = "".join(
        f'<div class="bullet-card"><h4>{html.escape(h)}</h4><p>{p}</p></div>'
        for h, p in lesson["start_cards"]
    )
    add(
        "开工",
        f"""
    <p class="kicker">🛠️ 开工检查</p>
    <h2 class="h2" style="margin-top:6px">先把文件建好</h2>
    <div class="grid g1" style="margin-top:24px;gap:14px">
      {start_cards}
    </div>
    """,
        lesson["start_note"],
    )

    cards = []
    for s in lesson["steps"]:
        cards.append(
            f'<div class="step-card"><div class="n">第 {s["n"]} 步</div>'
            f'<h4>{html.escape(s["title"])}</h4><p>{html.escape(s["goal"])}</p></div>'
        )
    add(
        f"{n_steps}步地图",
        f"""
    <p class="kicker">🗺️ 今天走{n_steps}步</p>
    <h2 class="h2" style="margin-top:6px">每一步都要<span class="grad">运行一次</span></h2>
    <div class="step-grid">{''.join(cards)}</div>
    """,
        lesson["map_note"],
    )

    prev = ""
    for s in lesson["steps"]:
        where = "".join(f"<li>{html.escape(item)}</li>" for item in s["where"])
        add(
            f"第{s['n']}步 · 讲",
            f"""
    <p class="kicker">第 {s['n']} / {n_steps} 步 · 讲</p>
    <h2 class="h2" style="margin-top:6px">{html.escape(s['title'])}</h2>
    <p class="lede" style="margin-top:8px">{html.escape(s['goal'])}</p>
    <div class="callout" style="margin-top:18px"><b>为什么：</b> {html.escape(s['why'])}</div>
    <ol class="where-list">{where}</ol>
    <div class="run-see"><b>运行后你该看到：</b> {html.escape(s['see'])}</div>
    """,
            s["talk_note"],
            "slide follow-talk",
        )
        spec = new_line_spec(prev, s["code"])
        add(
            f"第{s['n']}步 · 打",
            f"""
    <p class="kicker">第 {s['n']} / {n_steps} 步 · 打</p>
    <h2 class="h2" style="margin-top:6px">{html.escape(s['title'])}</h2>
    <p class="lede" style="margin-top:8px">{html.escape(s['type_hint'])}</p>
    {follow_code(s['code'], spec)}
    <div class="run-see"><b>运行后你该看到：</b> {html.escape(s['see'])}</div>
    <div class="pitfall"><b>坑：</b> {html.escape(s['pitfall'])}</div>
    """,
            s["type_note"],
            "slide follow-type",
        )
        prev = s["code"]

    err_cards = "".join(
        f'<div class="bullet-card"><h4>❌ {html.escape(w)}</h4><p>✅ {html.escape(r)}<br>{html.escape(why)}</p></div>'
        for w, r, why in lesson["errors"]
    )
    add(
        "改错",
        f"""
    <p class="kicker">🐞 改错时刻</p>
    <h2 class="h2" style="margin-top:6px">这三处，<span class="grad">课上必踩</span></h2>
    <div class="grid g1 anim-stagger-list" data-anim-target style="margin-top:24px;gap:12px">
      {err_cards}
    </div>
    """,
        lesson["errors_note"],
    )

    if lesson.get("challenge_code"):
        ch_spec = new_line_spec(lesson["final"], lesson["challenge_code"])
        add(
            "加码",
            f"""
    <p class="kicker">🚀 65–82 分 · 加码（选做）</p>
    <h2 class="h2" style="margin-top:6px">{html.escape(lesson["challenge_title"])}</h2>
    <p class="lede" style="margin-top:8px">{html.escape(lesson["challenge_lede"])}</p>
    {follow_code(lesson["challenge_code"], ch_spec)}
    <div class="run-see"><b>运行后你该看到：</b> {html.escape(lesson["challenge_see"])}</div>
    <div class="pitfall"><b>分层：</b> 没做完主游戏不要跳到加码。</div>
    """,
            lesson["challenge_note"],
            "slide follow-type",
        )

    ex_items = "".join(
        f'<div class="ex-item"><div class="ex-num">{i}</div><div><b style="color:var(--text-1)">{html.escape(t)}</b><p>{html.escape(d)}</p></div></div>'
        for i, (t, d) in enumerate(lesson["ex"], 1)
    )
    add(
        "改一改",
        f"""
    <p class="kicker">✏️ 改一改</p>
    <h2 class="h2" style="margin-top:6px">动动手，<span class="grad">改数字</span></h2>
    <div class="grid g2 anim-stagger-list" data-anim-target style="margin-top:24px;gap:14px">
      {ex_items}
    </div>
    """,
        lesson["ex_note"],
    )

    sum_rows = "".join(
        f"<tr><td>{html.escape(a)}</td><td>{html.escape(b)}</td><td>{html.escape(c)}</td></tr>"
        for a, b, c in lesson["sum_rows"]
    )
    add(
        "本课小结",
        f"""
    <p class="kicker" style="color:var(--accent-2)">🧠 本课小结</p>
    <h1 class="h1" style="font-size:48px;margin-top:8px">你今天<span class="grad">打出了</span></h1>
    <div style="max-width:900px;width:100%;margin-top:24px">
      <div class="card" style="padding:16px 20px">
        <table class="sum-table">
          <thead><tr><th>知识</th><th>是什么</th><th>怎么用</th></tr></thead>
          <tbody>
            {sum_rows}
          </tbody>
        </table>
      </div>
    </div>
    <div class="callout" style="margin-top:22px;max-width:900px;width:100%">
      <b>📖 下一课：</b> {html.escape(lesson["next_line"])}
    </div>
    """,
        lesson["sum_note"],
        "slide full",
    )

    total = len(slides)
    parts = []
    for i, (title, body, note, klass) in enumerate(slides, 1):
        if i == 1:
            klass = klass + " is-active"
        parts.append(
            f'<section class="{klass}" data-title="{html.escape(title)}">\n'
            f"{body}\n{footer(lesson, i, total)}\n{notes(note)}\n</section>"
        )
    inner = "\n\n".join(parts)
    css = PPT_CSS + "\n" + EXTRA_CSS
    return f"""<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>第{n}课 · {html.escape(lesson["title"])}</title>
<link rel="stylesheet" href="assets/fonts.css">
<link rel="stylesheet" href="assets/base.css">
<link rel="stylesheet" id="theme-link" href="assets/themes/dracula.css">
<link rel="stylesheet" href="assets/animations/animations.css">
<style>{css}</style>
</head>
<body>
<div class="deck" data-themes="dracula,tokyo-night,catppuccin-mocha,nord,terminal-green,cyberpunk-neon" data-theme-base="assets/themes/">
{inner}
</div>
<script src="assets/runtime.js"></script>
<script src="assets/animations/fx-runtime.js"></script>
<script src="courseware-ui.js"></script>
</body>
</html>
"""


def build_print(lesson: dict) -> str:
    n = lesson["n"]
    n_steps = len(lesson["steps"])
    cn = ["零", "一", "二", "三", "四", "五", "六", "七", "八", "九", "十"][n_steps]
    rows = []
    for s in lesson["steps"]:
        rows.append(
            f"<tr><td>第 {s['n']} 步</td><td>{html.escape(s['title'])}</td>"
            f"<td>{html.escape(s['see'])}</td><td>☐ 已运行</td></tr>"
        )
    know_rows = "".join(
        f'<tr><td class="mono">{html.escape(a)}</td><td>{html.escape(b)}</td>'
        f'<td class="mono">{html.escape(c)}</td></tr>'
        for a, b, c in lesson["print_know"]
    )
    err_ps = "".join(
        f'<p><strong>{i}.</strong> 错：<span class="mono">{html.escape(w)}</span><br>'
        f"对：________　　原因：________</p>"
        for i, (w, _r, _why) in enumerate(lesson["errors"], 1)
    )
    blanks = "".join(
        f'<div class="ex"><div class="q">{html.escape(q)}</div>'
        f'<div class="lines"><div class="line"></div></div></div>'
        for q in lesson["print_blanks"]
    )
    prev_link = (
        f'<a href="lesson{n - 1:02d}.html">上一课</a>' if n > 1 else "<span></span>"
    )
    next_link = (
        f'<a href="lesson{n + 1:02d}.html">下一课</a>' if n < 10 else "<span></span>"
    )
    times = lesson["print_times"]
    time_rows = "".join(
        f"<tr><td>{html.escape(a)}</td><td>{html.escape(b)}</td></tr>" for a, b in times
    )
    return f"""<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>第{n}课学案 · {html.escape(lesson["title"])}</title>
<link rel="stylesheet" href="print.css">
</head>
<body>
<div class="toolbar">
  <div>
    <a href="index.html">全部学案</a>
    {prev_link}
    {next_link}
  </div>
  <button class="print-btn" onclick="window.print()">🖨️ 打印本页（A4）</button>
</div>
<article class="sheet">
  <header class="hdr">
    <div>
      <div class="course">TURTLE 做游戏 · 学案</div>
      <h1>第 {n} 课　{html.escape(lesson["title"])}</h1>
    </div>
    <div class="meta">
      姓名 <span class="blank"></span><br>
      日期 <span class="blank"></span>
    </div>
  </header>

  <h2>一、本课目标（90 分钟）</h2>
  <p>对着课件把「<strong>{html.escape(lesson["project"])}</strong>」打出来。过关：{html.escape(lesson["pass_line"])}加码选做。</p>
  <table>
    <thead><tr><th>时间</th><th>环节</th></tr></thead>
    <tbody>
      {time_rows}
    </tbody>
  </table>

  <h2>二、{cn}步任务单（对着课件打，一步一运行）</h2>
  <p>完整代码在投影上。本页只记「打完该看到什么」。</p>
  <table>
    <thead><tr><th>步</th><th>做什么</th><th>运行后你该看到</th><th>打勾</th></tr></thead>
    <tbody>
      {''.join(rows)}
    </tbody>
  </table>

  <h2>三、知识点小抄</h2>
  <table>
    <thead><tr><th>名称</th><th>意思</th><th>写法</th></tr></thead>
    <tbody>
      {know_rows}
    </tbody>
  </table>

  <h2>四、加码（选做）</h2>
  <p>{lesson["print_challenge"]}</p>

  <h2>五、改错</h2>
  {err_ps}

  <h2>六、课堂填空</h2>
  {blanks}

  <h2>七、下课打卡</h2>
  <p>☐ 前半步已运行　☐ 主游戏能玩　☐ 加码已尝试（或主游戏加时完成）　☐ 能向同桌讲清本课一个 API　☐ 姓名已写</p>
  <p>今天最大的收获：</p>
  <div class="lines"><div class="line"></div><div class="line"></div></div>

  <div class="foot">
    <span>下一课：{html.escape(lesson["next_short"])}</span>
    <span>第 {n} / 10 课</span>
  </div>
</article>
</body>
</html>
"""


def build_md(lesson: dict) -> str:
    n = lesson["n"]
    n_steps = len(lesson["steps"])
    cn = ["零", "一", "二", "三", "四", "五", "六", "七", "八", "九", "十"][n_steps]
    times = "\n".join(f"| {a} | {b} |" for a, b in lesson["print_times"])
    step_md = []
    for s in lesson["steps"]:
        q = s.get("ask") or ""
        ask = f"\n\n**课堂提问：** {q}" if q else ""
        step_md.append(
            f"### 第 {s['n']} 步 · {s['title']}\n\n"
            f"{s['goal']}\n\n"
            f"{s['why']}\n\n"
            f"**运行后：** {s['see']}\n\n"
            f"**坑：** {s['pitfall']}{ask}\n"
        )
    return f"""# 第 {n} 课 · {lesson["title"]} — {lesson["project"]}

**时长 90 分钟。** 过关标准：对着课件把主游戏打出来——{lesson["pass_line"]}

热身并进主游戏：同一份 `lesson{n}.py`，从空文件写到能玩。不要另开热身文件。

---

## ⏱️ 90 分钟流程

| 时间 | 做什么 |
|------|--------|
{times}

---

## 🎯 本课目标

- **主游戏：{lesson["project"]}**（对着课件 {n_steps} 步打完）
- {lesson["pass_line"]}

---

## 课件怎么用

投影 `ppt/lesson{n:02d}.html`。每一步两页：

1. **讲**：这一步要做出什么、加在文件哪、运行后该看到什么
2. **打**：到这一步为止的完整程序。绿色底是新加或改过的行

老师翻「打」页之后，等全班跑通再翻下一步。完整参考在 `code/lesson{n}.py`，和学生打完第 {n_steps} 步的文件一致。

---

## {cn}步

{"".join(step_md)}
---

## 加码（选做）

{lesson["challenge_title"]}：{lesson.get("challenge_lede", "")}

没做完主游戏的人不要跳加码。

---

## 下一课

{lesson["next_line"]}
"""


def write_outputs(lesson: dict) -> None:
    check_lesson(lesson)
    n = lesson["n"]
    (CODE / f"lesson{n}.py").write_text(
        lesson["header"] + _norm(lesson["final"]), encoding="utf-8"
    )
    PPT.mkdir(parents=True, exist_ok=True)
    PRINT.mkdir(parents=True, exist_ok=True)
    (PPT / f"lesson{n:02d}.html").write_text(build_ppt(lesson), encoding="utf-8")
    (PRINT / f"lesson{n:02d}.html").write_text(build_print(lesson), encoding="utf-8")
    (ROOT / f"lesson{n:02d}.md").write_text(build_md(lesson), encoding="utf-8")
    print(f"ok lesson {n} follow-along")
    prev = ""
    for s in lesson["steps"]:
        spec = new_line_spec(prev, s["code"])
        print(f"  step {s['n']}: {s['code'].count(chr(10)) + 1} lines, new={spec}")
        prev = s["code"]
