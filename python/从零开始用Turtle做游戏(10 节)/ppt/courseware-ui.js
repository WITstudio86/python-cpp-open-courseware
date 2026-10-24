/**
 * 课件通用增强（自动生成）
 * - 封面配套代码按钮（UTF-8 浅色查看页）
 * - 代码块至少约 10 行可视高度并可滚动
 * - 幻灯片内容过多时可滚动
 * 课程：从零开始用 Turtle 做游戏
 */
(function () {
  'use strict';
  if (window.__cspjCoursewareUi) return;
  window.__cspjCoursewareUi = true;

  var qs = location.search || '';
  var isPreview = /[?&]preview=/.test(qs);
  var isPresenter = /[?&]presenter=1/.test(qs);

  var CODE_FILES = {
    1: "lesson1.html",
    2: "lesson2.html",
    3: "lesson3.html",
    4: "lesson4.html",
    5: "lesson5.html",
    6: "lesson6.html",
    7: "lesson7.html",
    8: "lesson8.html",
    9: "lesson9.html",
    10: "lesson10.html"
  };

  var VIEW_PREFIX = "../code/view/";

  function injectCss() {
    if (document.getElementById('cspj-courseware-ui-style')) return;
    var style = document.createElement('style');
    style.id = 'cspj-courseware-ui-style';
    var css = [
"/* 幻灯片内容过多时可滚动，避免裁切 */",
".slide, .slide.active, .slide-content, .slide-summary, .slide-title, .title-slide {",
"  overflow-x: hidden !important;",
"  overflow-y: auto !important;",
"  -webkit-overflow-scrolling: touch;",
"}",
"/* 代码块：至少约 10 行高度，超出内部滚动 */",
".code-block, div.code-block, .slide .code-block, pre.code, pre.code-block, .slide pre {",
"  box-sizing: border-box !important;",
"  min-height: calc(1.45em * 10 + 28px) !important;",
"  max-height: min(62vh, 34em) !important;",
"  overflow-x: auto !important;",
"  overflow-y: auto !important;",
"  white-space: pre !important;",
"  line-height: 1.45 !important;",
"}",
".slide pre.follow-code, .slide pre.follow-code code, .follow-code .line-old, .follow-code .line-new {",
"  font-size: 20px !important;",
"  line-height: 1.15 !important;",
"  min-height: 0 !important;",
"}",
".tok-kw { color: #ff79c6; }",
".tok-str { color: #f1fa8c; }",
".tok-num { color: #bd93f9; }",
".tok-cmt { color: #6272a4; font-style: italic; }",
".tok-fn { color: #50fa7b; }",
".tok-bi { color: #8be9fd; }",
".code-block > pre, .code-block pre, .code-block > code, .code-block code {",
"  max-height: none !important;",
"  min-height: 0 !important;",
"  overflow: visible !important;",
"  white-space: pre !important;",
"}",
".code-block pre code, pre code {",
"  white-space: pre !important;",
"  display: block !important;",
"}",
".cspj-code-btn-wrap {",
"  display: flex; flex-direction: column; align-items: center; justify-content: center;",
"  margin-top: 18px; gap: 8px;",
"}",
".cspj-code-btn {",
"  display: inline-flex !important; align-items: center; gap: 8px;",
"  padding: 12px 22px; border-radius: 999px;",
"  background: linear-gradient(135deg, #d4a853, #c4922e);",
"  color: #0a2540 !important; font-weight: 700; font-size: 15px;",
"  text-decoration: none !important;",
"  box-shadow: 0 6px 18px rgba(212,168,83,0.35);",
"  border: 1px solid rgba(255,255,255,0.25); cursor: pointer;",
"  transition: transform .15s ease, box-shadow .15s ease; z-index: 5;",
"}",
".cspj-code-btn:hover { transform: translateY(-2px); box-shadow: 0 10px 24px rgba(212,168,83,0.45); }",
".cspj-code-meta { font-size: 12px; opacity: 0.72; }"
    ].join("\n");
    style.textContent = css;
    (document.head || document.documentElement).appendChild(style);
  }

  function detectLesson() {
    var path = decodeURIComponent(location.pathname || location.href || '');
    var base = path.split('/').pop() || '';
    var patterns = [
      /第0*(\d+)课/,
      /第0*(\d+)节/,
      /lesson[_-]?0*(\d+)/i,
      /^L0*(\d+)/i,
      /lesson_cli_0*(\d+)/i
    ];
    for (var i = 0; i < patterns.length; i++) {
      var m = base.match(patterns[i]) || path.match(patterns[i]) || (document.title || '').match(patterns[i]);
      if (m) return parseInt(m[1], 10);
    }
    return null;
  }

  function addCoverCodeButton() {
    if (isPreview || isPresenter) return;
    var lesson = detectLesson();
    if (!lesson || !CODE_FILES[lesson]) return;

    var slides = document.querySelectorAll('.slide');
    if (!slides.length) return;
    var first = slides[0];
    if (first.querySelector('.cspj-code-btn')) return;

    var file = CODE_FILES[lesson];
    var href = VIEW_PREFIX + file;

    var wrap = document.createElement('div');
    wrap.className = 'cspj-code-btn-wrap';

    var a = document.createElement('a');
    a.className = 'cspj-code-btn';
    a.href = href;
    a.target = '_blank';
    a.rel = 'noopener noreferrer';
    a.textContent = '📄 查看配套代码';
    a.title = '打开本课完整代码（UTF-8 浅色查看页）：' + file;

    var meta = document.createElement('div');
    meta.className = 'cspj-code-meta';
    meta.textContent = file;

    wrap.appendChild(a);
    wrap.appendChild(meta);

    var anchor = first.querySelector('.decor') || first.querySelector('.subtitle') || first.querySelector('h1') || first.querySelector('.h1') || first.querySelector('.title');
    if (anchor && anchor.parentNode === first) {
      if (anchor.nextSibling) first.insertBefore(wrap, anchor.nextSibling);
      else first.appendChild(wrap);
    } else if (anchor && anchor.parentNode) {
      anchor.parentNode.appendChild(wrap);
    } else {
      first.appendChild(wrap);
    }
  }

  var PY_KW = {
    and:1, as:1, assert:1, break:1, class:1, continue:1, def:1, del:1,
    elif:1, else:1, except:1, False:1, finally:1, for:1, from:1, global:1,
    if:1, import:1, in:1, is:1, lambda:1, None:1, nonlocal:1, not:1, or:1,
    pass:1, raise:1, return:1, True:1, try:1, while:1, with:1, yield:1
  };
  var PY_BI = {
    abs:1, bool:1, dict:1, enumerate:1, float:1, int:1, len:1, list:1,
    max:1, min:1, print:1, range:1, set:1, str:1, tuple:1, zip:1, input:1
  };

  function escHtml(s) {
    return s.replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;');
  }

  function highlightPythonLine(line) {
    if (!line) return '';
    var html = '';
    var i = 0;
    var n = line.length;
    var afterDef = false;
    function wrap(cls, s) {
      return '<span class="' + cls + '">' + escHtml(s) + '</span>';
    }
    function isIdentStart(c) {
      return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c === '_';
    }
    function isIdent(c) {
      return isIdentStart(c) || (c >= '0' && c <= '9');
    }
    while (i < n) {
      var ch = line.charAt(i);
      if (ch === '#') {
        html += wrap('tok-cmt', line.slice(i));
        break;
      }
      if (ch === '"' || ch === "'") {
        var q = ch;
        var j = i + 1;
        while (j < n) {
          if (line.charAt(j) === '\\') { j += 2; continue; }
          if (line.charAt(j) === q) { j += 1; break; }
          j += 1;
        }
        html += wrap('tok-str', line.slice(i, j));
        i = j;
        continue;
      }
      if ((ch === 'f' || ch === 'F' || ch === 'r' || ch === 'R' || ch === 'b' || ch === 'B') &&
          i + 1 < n && (line.charAt(i + 1) === '"' || line.charAt(i + 1) === "'" ||
            ((line.charAt(i + 1) === 'f' || line.charAt(i + 1) === 'F' ||
              line.charAt(i + 1) === 'r' || line.charAt(i + 1) === 'R') &&
             i + 2 < n && (line.charAt(i + 2) === '"' || line.charAt(i + 2) === "'")))) {
        var prev = i === 0 ? '' : line.charAt(i - 1);
        if (!isIdent(prev)) {
          var p = i + 1;
          while (p < n && isIdentStart(line.charAt(p)) && line.charAt(p) !== '"' && line.charAt(p) !== "'") p += 1;
          if (p < n && (line.charAt(p) === '"' || line.charAt(p) === "'")) {
            html += wrap('tok-kw', line.slice(i, p));
            i = p;
            continue;
          }
        }
      }
      if ((ch >= '0' && ch <= '9') && (i === 0 || !isIdent(line.charAt(i - 1)))) {
        var k = i + 1;
        while (k < n && ((line.charAt(k) >= '0' && line.charAt(k) <= '9') || line.charAt(k) === '.')) k += 1;
        html += wrap('tok-num', line.slice(i, k));
        i = k;
        continue;
      }
      if (isIdentStart(ch)) {
        var e = i + 1;
        while (e < n && isIdent(line.charAt(e))) e += 1;
        var word = line.slice(i, e);
        if (afterDef) {
          html += wrap('tok-fn', word);
          afterDef = false;
        } else if (PY_KW[word]) {
          html += wrap('tok-kw', word);
          afterDef = word === 'def';
        } else if (PY_BI[word]) {
          html += wrap('tok-bi', word);
        } else {
          html += escHtml(word);
        }
        i = e;
        continue;
      }
      html += escHtml(ch);
      i += 1;
    }
    return html;
  }

  function parseNewSpec(spec) {
    var set = {};
    if (!spec) return set;
    spec.split(',').forEach(function (part) {
      part = part.trim();
      if (!part) return;
      var dash = part.indexOf('-');
      if (dash > 0) {
        var a = parseInt(part.slice(0, dash), 10);
        var b = parseInt(part.slice(dash + 1), 10);
        if (!a || !b) return;
        for (var i = a; i <= b; i++) set[i] = true;
      } else {
        var n = parseInt(part, 10);
        if (n) set[n] = true;
      }
    });
    return set;
  }

  function markNewLines() {
    document.querySelectorAll('.deck pre[data-new]').forEach(function (pre) {
      if (pre.getAttribute('data-marked') === '1') return;
      var code = pre.querySelector('code') || pre;
      var set = parseNewSpec(pre.getAttribute('data-new'));
      var raw = (code.textContent || '').replace(/\n$/, '');
      var lines = raw.split('\n');
      code.innerHTML = lines.map(function (line, idx) {
        var cls = set[idx + 1] ? 'line-new' : 'line-old';
        return '<span class="' + cls + '">' + (highlightPythonLine(line) || ' ') + '</span>';
      }).join('');
      pre.setAttribute('data-marked', '1');
    });
    document.querySelectorAll('pre code.language-python').forEach(function (code) {
      var pre = code.closest('pre');
      if (pre && pre.getAttribute('data-marked') === '1') return;
      if (code.getAttribute('data-hl') === '1') return;
      var raw = (code.textContent || '').replace(/\n$/, '');
      code.innerHTML = raw.split('\n').map(highlightPythonLine).join('\n');
      code.setAttribute('data-hl', '1');
    });
  }

  function scrollNewIn(slide) {
    if (!slide) return;
    var neu = slide.querySelector('.line-new');
    if (!neu) return;
    var pre = neu.closest('pre');
    if (!pre) return;
    var nr = neu.getBoundingClientRect();
    var pr = pre.getBoundingClientRect();
    pre.scrollTop += (nr.top - pr.top) - pre.clientHeight * 0.28;
  }

  function watchSlides() {
    var slides = document.querySelectorAll('.deck > .slide');
    if (!slides.length || !window.MutationObserver) return;
    slides.forEach(function (slide) {
      var obs = new MutationObserver(function () {
        if (slide.classList.contains('is-active') || slide.classList.contains('active')) {
          scrollNewIn(slide);
        }
      });
      obs.observe(slide, { attributes: true, attributeFilter: ['class'] });
    });
    var current = document.querySelector('.slide.is-active, .slide.active') || slides[0];
    scrollNewIn(current);
  }

  function boot() {
    injectCss();
    addCoverCodeButton();
    markNewLines();
    watchSlides();
  }

  if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', boot);
  } else {
    boot();
  }
})();
