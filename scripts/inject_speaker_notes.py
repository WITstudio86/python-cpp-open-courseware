#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
为课件每页注入讲稿备注（aside.notes），供演讲者模式读取。

数据来源优先级：
1. 同课「内容/*.md」中与幻灯片标题匹配的章节
2. 课程大纲中的考点 / 练习提示
3. 幻灯片正文要点（兜底）

已有 .notes / aside.notes / .speaker-notes 的幻灯片不会覆盖。
"""

from __future__ import annotations

import re
import sys
from html import escape
from pathlib import Path
from typing import Dict, List, Optional, Tuple

try:
    from bs4 import BeautifulSoup, NavigableString
except ImportError:
    print("需要 beautifulsoup4: pip install beautifulsoup4", file=sys.stderr)
    sys.exit(1)

ROOT = Path(__file__).resolve().parents[1]

COURSE_SPECS = [
    {
        "name": "csp-j",
        "课件": ROOT / "cpp/csp-j/课件",
        "内容": ROOT / "cpp/csp-j/内容",
        "大纲": ROOT / "cpp/csp-j/课程大纲.md",
        "glob": "第*.html",
    },
    {
        "name": "csp-s",
        "课件": ROOT / "cpp/csp-s/课件",
        "内容": ROOT / "cpp/csp-s/内容",
        "大纲": ROOT / "cpp/csp-s/课程大纲.md",
        "glob": "第*.html",
    },
    {
        "name": "c++算法提高",
        "课件": ROOT / "cpp/c++算法提高/课件",
        "内容": ROOT / "cpp/c++算法提高/内容",
        "大纲": ROOT / "cpp/c++算法提高/课程大纲.md",
        "glob": "第*.html",
    },
    {
        "name": "c++趣味学习",
        "课件": ROOT / "cpp/c++趣味学习/课件",
        "内容": ROOT / "cpp/c++趣味学习/内容",
        "大纲": ROOT / "cpp/c++趣味学习/课程大纲.md",
        "glob": "第*.html",
    },
    {
        "name": "4节小课",
        "课件": ROOT / "cpp/4节小课: 工具/课件",
        "内容": ROOT / "cpp/4节小课: 工具/内容",
        "大纲": None,
        "glob": "第*.html",
    },
    {
        "name": "pygame",
        "课件": ROOT / "python/pygame/课件",
        "内容": ROOT / "python/pygame/内容",
        "大纲": ROOT / "python/pygame/Pygame零基础到实践-48节课课程大纲.md",
        "glob": "第*.html",
    },
    {
        "name": "python趣味学习",
        "课件": ROOT / "python/python趣味学习/课件",
        "内容": ROOT / "python/python趣味学习/内容",
        "大纲": ROOT / "python/python趣味学习/Python趣味学习_48节大纲.md",
        "glob": "lesson_*.html",
    },
    {
        "name": "tkinter",
        "课件": ROOT / "python/tkinter/课件",
        "内容": ROOT / "python/tkinter/内容",
        "大纲": ROOT / "python/tkinter/课程大纲_Python_Tkinter_48节课.md",
        "glob": "L*.html",
    },
    {
        "name": "零基础10节",
        "课件": ROOT / "python/零基础到图形化项目实战(10 节)/ppt",
        "内容": ROOT / "python/零基础到图形化项目实战(10 节)",
        "大纲": None,
        "glob": "lesson*.html",
        "content_glob": "lesson*.md",
    },
]


def clean_text(s: str) -> str:
    s = re.sub(r"<[^>]+>", "", s)
    s = s.replace("\xa0", " ")
    s = re.sub(r"[ \t]+", " ", s)
    s = re.sub(r"\n{3,}", "\n\n", s)
    return s.strip()


def lesson_num_from_name(name: str) -> Optional[int]:
    patterns = [
        r"第0*(\d+)课",
        r"lesson[_\s-]?0*(\d+)",
        r"^L0*(\d+)",
        r"第0*(\d+)节",
    ]
    for p in patterns:
        m = re.search(p, name, re.I)
        if m:
            return int(m.group(1))
    return None


def parse_outline_rows(path: Optional[Path]) -> Dict[int, Dict[str, str]]:
    """从 markdown 表格/列表中提取每课考点。"""
    out: Dict[int, Dict[str, str]] = {}
    if not path or not path.exists():
        return out
    text = path.read_text(encoding="utf-8", errors="ignore")
    # 表格行：| 第N课 | 标题 | 考点 | 练习 |
    for line in text.splitlines():
        if "|" not in line:
            continue
        cells = [c.strip() for c in line.strip().strip("|").split("|")]
        if len(cells) < 2:
            continue
        m = re.search(r"第\s*0*(\d+)\s*课", cells[0]) or re.search(
            r"(?:L|lesson|第)?\s*0*(\d+)", cells[0], re.I
        )
        if not m:
            # 有些大纲第一列就是数字
            m = re.match(r"0*(\d+)$", cells[0])
        if not m:
            continue
        n = int(m.group(1))
        title = cells[1] if len(cells) > 1 else ""
        points = cells[2] if len(cells) > 2 else ""
        practice = cells[3] if len(cells) > 3 else ""
        if re.match(r"^[-:]+$", title + points):
            continue
        out[n] = {
            "title": clean_text(title),
            "points": clean_text(points),
            "practice": clean_text(practice),
        }
    # 再扫 ## 第N课 段落
    for m in re.finditer(
        r"##+\s*第\s*0*(\d+)\s*[课节][：:\s]*([^\n]*)\n(.*?)(?=\n##+\s*第\s*0*\d+|\Z)",
        text,
        re.S,
    ):
        n = int(m.group(1))
        title = clean_text(m.group(2))
        body = clean_text(m.group(3))[:400]
        if n not in out:
            out[n] = {"title": title, "points": body, "practice": ""}
        else:
            if not out[n].get("points") and body:
                out[n]["points"] = body
            if not out[n].get("title") and title:
                out[n]["title"] = title
    return out


def load_content_md(content_dir: Path, lesson: Optional[int], html_name: str, content_glob: str = "*.md") -> str:
    if not content_dir or not content_dir.exists():
        return ""
    candidates: List[Path] = []
    if lesson is not None:
        for p in content_dir.glob(content_glob):
            n = lesson_num_from_name(p.name)
            if n == lesson:
                candidates.append(p)
    if not candidates:
        # 按文件名关键词
        stem = Path(html_name).stem
        key = re.sub(r"^(第0*\d+课[-—]?|lesson[_\s-]?0*\d+[-_]?|L0*\d+[-]?)", "", stem, flags=re.I)
        key = key.strip("-_ ")
        for p in content_dir.glob(content_glob):
            if key and key in p.stem:
                candidates.append(p)
    if not candidates:
        return ""
    return candidates[0].read_text(encoding="utf-8", errors="ignore")


def split_md_sections(md: str) -> List[Tuple[str, str]]:
    """返回 [(heading, body), ...]"""
    if not md:
        return []
    parts = re.split(r"(?m)^(#{1,3})\s+(.+)$", md)
    # parts: [pre, h, title, body, h, title, body, ...]
    sections: List[Tuple[str, str]] = []
    if parts and parts[0].strip():
        sections.append(("导言", parts[0].strip()))
    i = 1
    while i + 2 < len(parts):
        title = clean_text(parts[i + 1])
        body = parts[i + 2].strip()
        sections.append((title, body))
        i += 3
    return sections


def bullets_from_md(body: str, limit: int = 6) -> List[str]:
    lines = []
    for raw in body.splitlines():
        s = raw.strip()
        if not s:
            continue
        s = re.sub(r"^[-*+]\s+", "", s)
        s = re.sub(r"^\d+[\.、]\s*", "", s)
        s = re.sub(r"^\*\*(.+?)\*\*", r"\1", s)
        s = re.sub(r"`([^`]+)`", r"\1", s)
        s = clean_text(s)
        if len(s) < 4:
            continue
        if s.startswith("#") or s.startswith("```"):
            continue
        if s.startswith("|"):
            continue
        lines.append(s)
        if len(lines) >= limit:
            break
    return lines


def slide_title(slide) -> str:
    for tag in ("h1", "h2", "h3"):
        h = slide.find(tag)
        if h:
            return clean_text(h.get_text(" ", strip=True))
    dt = slide.get("data-title")
    if dt:
        return clean_text(dt)
    return ""


def slide_bullets(slide, limit: int = 8) -> List[str]:
    texts = []
    # skip notes
    for el in slide.find_all(["li", "p", "h4", ".card h4", "strong"]):
        if el.find_parent(class_=re.compile(r"notes|speaker-notes")):
            continue
        t = clean_text(el.get_text(" ", strip=True))
        if len(t) < 4 or len(t) > 120:
            continue
        if t in texts:
            continue
        texts.append(t)
        if len(texts) >= limit:
            break
    if not texts:
        raw = clean_text(slide.get_text("\n", strip=True))
        for line in raw.splitlines():
            line = line.strip()
            if 4 <= len(line) <= 100:
                texts.append(line)
            if len(texts) >= limit:
                break
    return texts


def match_section(title: str, sections: List[Tuple[str, str]]) -> Optional[Tuple[str, str]]:
    if not title or not sections:
        return None
    t = re.sub(r"\s+", "", title)
    best = None
    best_score = 0
    for h, body in sections:
        hh = re.sub(r"\s+", "", h)
        score = 0
        if t == hh:
            score = 100
        elif t in hh or hh in t:
            score = 80
        else:
            # token overlap
            ta = set(re.findall(r"[\u4e00-\u9fff]{2,}|[A-Za-z0-9_]{3,}", title))
            hb = set(re.findall(r"[\u4e00-\u9fff]{2,}|[A-Za-z0-9_]{3,}", h))
            if ta and hb:
                score = int(100 * len(ta & hb) / max(1, len(ta)))
        if score > best_score:
            best_score = score
            best = (h, body)
    return best if best_score >= 30 else None


def build_note(
    slide_idx: int,
    total: int,
    title: str,
    classes: List[str],
    bullets: List[str],
    outline: Optional[Dict[str, str]],
    sections: List[Tuple[str, str]],
    lesson_title: str,
) -> str:
    lines: List[str] = []
    is_cover = any("cover" in c or "title" in c for c in classes) or slide_idx == 0
    is_summary = any("summary" in c or "end" in c for c in classes) or any(
        k in title for k in ("小结", "总结", "回顾", "本课", "你学会了")
    )
    is_practice = any(k in title for k in ("练习", "真题", "挑战", "作业", "练一练", "实战"))
    is_code = any(k in title for k in ("代码", "模板", "示例", "程序"))

    if is_cover:
        lines.append(f"【开场】第 {slide_idx + 1}/{total} 页 · {lesson_title or title}")
        lines.append("用 30 秒说明本课目标与学完能做什么，再进入正题。")
        if outline:
            if outline.get("points"):
                lines.append(f"大纲考点：{outline['points']}")
            if outline.get("practice"):
                lines.append(f"配套练习方向：{outline['practice']}")
        if bullets:
            lines.append("封面关键词：")
            for b in bullets[:4]:
                lines.append(f"· {b}")
        lines.append("互动：问学生「今天最想搞清楚什么？」，收 1–2 个期待。")
        return "\n".join(lines)

    if is_summary:
        lines.append(f"【收尾】回顾本课主线：{title or lesson_title}")
        if outline and outline.get("points"):
            lines.append(f"对照大纲再过一遍：{outline['points']}")
        if bullets:
            lines.append("板书/口述要点：")
            for b in bullets[:6]:
                lines.append(f"· {b}")
        if outline and outline.get("practice"):
            lines.append(f"课后任务：{outline['practice']}")
        lines.append("结束前留 2 分钟答疑；布置 1 道小练习检验是否真正掌握。")
        return "\n".join(lines)

    sec = match_section(title, sections)
    lines.append(f"【讲解】{title or f'第 {slide_idx + 1} 页'}")
    if sec:
        h, body = sec
        pts = bullets_from_md(body, limit=5)
        if pts:
            lines.append(f"结合讲义《{h}》强调：")
            for p in pts:
                lines.append(f"· {p}")
        else:
            snippet = clean_text(body)[:220]
            if snippet:
                lines.append(f"讲义提要：{snippet}")

    if bullets and not (sec and bullets_from_md(sec[1], 1)):
        lines.append("本页要点（照着讲即可）：")
        for b in bullets[:6]:
            lines.append(f"· {b}")
    elif bullets and sec:
        # still list top slide bullets if different
        extra = [b for b in bullets[:4] if b]
        if extra:
            lines.append("幻灯片上可见要点：")
            for b in extra:
                lines.append(f"· {b}")

    if is_code:
        lines.append("代码页节奏：先读懂输入输出 → 再走主流程 → 最后点出易错点（边界/类型/下标）。")
        lines.append("可让学生预测下一行输出，再运行对照。")
    elif is_practice:
        lines.append("练习页节奏：先独立想 1 分钟 → 再点拨思路 → 最后对答案讲为什么。")
        if outline and outline.get("practice"):
            lines.append(f"可联系：{outline['practice']}")
    else:
        lines.append("讲解时放慢关键术语；用 1 个生活类比 + 1 个反例加深印象。")

    if outline and outline.get("points") and slide_idx == 1:
        lines.append(f"本课大纲考点（可适时点题）：{outline['points']}")

    return "\n".join(lines)


def has_notes(slide) -> bool:
    return bool(slide.select_one(".notes, aside.notes, .speaker-notes"))


def inject_into_html(html_path: Path, outline: Optional[Dict[str, str]], content_md: str, dry_run: bool = False) -> Tuple[int, int]:
    raw = html_path.read_text(encoding="utf-8", errors="ignore")
    soup = BeautifulSoup(raw, "html.parser")
    slides = soup.select(".slide")
    if not slides:
        return 0, 0

    sections = split_md_sections(content_md)
    lesson_title = ""
    if outline and outline.get("title"):
        lesson_title = outline["title"]
    else:
        t = soup.title.get_text(strip=True) if soup.title else html_path.stem
        lesson_title = re.sub(r"\s*[-|·].*$", "", t).strip()

    added = 0
    skipped = 0
    total = len(slides)
    for i, slide in enumerate(slides):
        if has_notes(slide):
            skipped += 1
            continue
        title = slide_title(slide)
        classes = slide.get("class") or []
        bullets = slide_bullets(slide)
        note = build_note(i, total, title, classes, bullets, outline, sections, lesson_title)
        aside = soup.new_tag("aside")
        aside["class"] = "notes"
        aside.string = note
        # 插到 slide 末尾
        slide.append(NavigableString("\n"))
        slide.append(aside)
        slide.append(NavigableString("\n"))
        added += 1

    if added and not dry_run:
        # 尽量少改格式：用原始 parser 输出
        out = str(soup)
        # BeautifulSoup 可能改 doctype；若原文件有标准 doctype 则保留
        if raw.lstrip().lower().startswith("<!doctype") and not out.lstrip().lower().startswith("<!doctype"):
            out = "<!DOCTYPE html>\n" + out
        html_path.write_text(out, encoding="utf-8")
    return added, skipped


def main():
    dry = "--dry-run" in sys.argv
    only = None
    for a in sys.argv[1:]:
        if a.startswith("--only="):
            only = a.split("=", 1)[1]

    total_added = 0
    total_skipped = 0
    total_files = 0

    for spec in COURSE_SPECS:
        if only and only not in spec["name"]:
            continue
        course_dir: Path = spec["课件"]
        if not course_dir.exists():
            print(f"[skip] 无目录 {course_dir}")
            continue
        outline_map = parse_outline_rows(spec.get("大纲"))
        content_dir: Path = spec["内容"]
        content_glob = spec.get("content_glob", "*.md")
        files = sorted(course_dir.glob(spec["glob"]))
        files = [f for f in files if f.name not in ("总览.html", "index.html")]
        print(f"\n== {spec['name']} · {len(files)} 个课件 ==")
        for f in files:
            n = lesson_num_from_name(f.name)
            outline = outline_map.get(n) if n is not None else None
            md = load_content_md(content_dir, n, f.name, content_glob=content_glob)
            # 零基础：内容就在 ppt 上一级的 lessonXX.md
            if not md and spec["name"] == "零基础10节":
                parent = course_dir.parent
                for cand in parent.glob(f"lesson{n:02d}.md") if n else []:
                    md = cand.read_text(encoding="utf-8", errors="ignore")
                    break
                if not md and n:
                    for cand in parent.glob(f"lesson{n}.md"):
                        md = cand.read_text(encoding="utf-8", errors="ignore")
                        break
            added, skipped = inject_into_html(f, outline, md, dry_run=dry)
            total_added += added
            total_skipped += skipped
            total_files += 1
            if added:
                print(f"  +{added:2d} notes  skip={skipped}  {f.name}")
        print(f"  小计: 已处理 {len(files)} 文件")

    mode = "DRY-RUN" if dry else "DONE"
    print(f"\n[{mode}] files={total_files} notes_added={total_added} slides_kept={total_skipped}")


if __name__ == "__main__":
    main()
