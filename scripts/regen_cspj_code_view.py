#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Regenerate cpp/csp-j/程序/view/*.html from companion .cpp files."""
from __future__ import annotations

import html as H
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
PROG = ROOT / "cpp" / "csp-j" / "程序"
VIEW = PROG / "view"

TEMPLATE = """<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>{title}</title>
<style>
  :root {{
    --bg: #f5f7fa;
    --panel: #ffffff;
    --text: #1a1a2e;
    --muted: #5a6570;
    --gold: #b8860b;
    --gold-bg: #fff8e6;
    --code-bg: #ffffff;
    --code-text: #1f2933;
    --border: #d8dee6;
    --top-bg: #ffffff;
    --top-border: #e5e9ef;
  }}
  * {{ box-sizing: border-box; }}
  html, body {{
    margin: 0; padding: 0;
    background: var(--bg);
    color: var(--text);
    font-family: -apple-system, BlinkMacSystemFont, "PingFang SC", "Microsoft YaHei", sans-serif;
    min-height: 100%;
  }}
  .top {{
    position: sticky; top: 0; z-index: 10;
    display: flex; flex-wrap: wrap; align-items: center; justify-content: space-between;
    gap: 10px;
    padding: 12px 18px;
    background: var(--top-bg);
    border-bottom: 1px solid var(--top-border);
    box-shadow: 0 1px 8px rgba(15, 23, 42, 0.06);
  }}
  .brand {{ color: var(--gold); font-weight: 700; font-size: 14px; letter-spacing: 0.04em; }}
  .title {{ font-size: 15px; font-weight: 600; color: var(--text); max-width: 52vw; overflow: hidden; text-overflow: ellipsis; white-space: nowrap; }}
  .actions {{ display: flex; gap: 8px; flex-wrap: wrap; }}
  .btn {{
    appearance: none; border: 1px solid var(--border);
    background: #fff; color: var(--text);
    border-radius: 999px; padding: 8px 14px; font-size: 13px; font-weight: 600;
    text-decoration: none; cursor: pointer;
  }}
  .btn:hover {{ background: #f0f3f7; }}
  .btn.gold {{
    background: linear-gradient(135deg, #f0d78c, #d4a853);
    color: #0a2540; border-color: #e0c06a;
  }}
  .meta {{
    padding: 10px 18px; color: var(--muted); font-size: 12px;
    border-bottom: 1px solid var(--border);
    background: var(--panel);
  }}
  .wrap {{ padding: 16px 18px 40px; }}
  pre {{
    margin: 0;
    background: var(--code-bg);
    color: var(--code-text);
    border: 1px solid var(--border);
    border-radius: 12px;
    padding: 18px 20px;
    overflow: auto;
    font-family: "SF Mono", "JetBrains Mono", "Fira Code", Consolas, "Courier New", monospace;
    font-size: 13.5px;
    line-height: 1.55;
    white-space: pre;
    tab-size: 4;
    box-shadow: 0 2px 12px rgba(15, 23, 42, 0.05);
  }}
  .hint {{ margin-top: 12px; color: var(--muted); font-size: 12px; }}
  @media print {{
    html, body {{ background: #fff !important; color: #000 !important; }}
    .top {{
      position: static; box-shadow: none; border-bottom: 1px solid #ccc;
      background: #fff !important; -webkit-print-color-adjust: exact; print-color-adjust: exact;
    }}
    .actions {{ display: none !important; }}
    .meta {{ background: #fff !important; border-color: #ddd; color: #333; }}
    .wrap {{ padding: 0; }}
    pre {{
      background: #fff !important; color: #000 !important; border: 1px solid #bbb;
      box-shadow: none; border-radius: 0; white-space: pre-wrap; word-break: break-word;
      font-size: 11pt; line-height: 1.4;
    }}
    .hint {{ display: none; }}
    a {{ color: #000; text-decoration: none; }}
  }}
</style>
</head>
<body>
  <div class="top">
    <div class="brand">CSP-J · 配套代码</div>
    <div class="title">{title}</div>
    <div class="actions">
      <a class="btn" href="../{cpp_name}" download="{cpp_name}">⬇️ 下载 .cpp</a>
      <a class="btn gold" href="javascript:history.back()">← 返回课件</a>
    </div>
  </div>
  <div class="meta">编码：UTF-8 · 文件：{cpp_name} · 共 {lines} 行 · 浅色主题便于打印</div>
  <div class="wrap">
    <pre id="code">{code}</pre>
    <p class="hint">本页使用浅色主题，可直接打印或导出 PDF。需要源文件请点「下载 .cpp」。</p>
  </div>
</body>
</html>
"""


def build_one(cpp: Path) -> Path:
    text = cpp.read_text(encoding="utf-8")
    lines = text.count("\n") + (0 if text.endswith("\n") or not text else 1)
    name = cpp.name
    title = cpp.stem
    html = TEMPLATE.format(
        title=title,
        cpp_name=name,
        lines=lines,
        code=H.escape(text),
    )
    dest = VIEW / (title + ".html")
    dest.write_text(html, encoding="utf-8")
    return dest


def main(args: list[str]) -> None:
    VIEW.mkdir(parents=True, exist_ok=True)
    if args:
        files = []
        for a in args:
            p = Path(a)
            if not p.is_absolute():
                p = PROG / a if (PROG / a).exists() else ROOT / a
            files.append(p)
    else:
        files = sorted(PROG.glob("lesson*.cpp"))
    for f in files:
        if not f.exists():
            print("skip missing", f)
            continue
        d = build_one(f)
        print("wrote", d.relative_to(ROOT))


if __name__ == "__main__":
    main(sys.argv[1:])
