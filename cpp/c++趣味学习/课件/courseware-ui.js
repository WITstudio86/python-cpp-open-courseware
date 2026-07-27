/**
 * 课件通用增强（自动生成）
 * - 封面配套代码按钮（UTF-8 浅色查看页）
 * - 代码块至少约 10 行可视高度并可滚动
 * - 幻灯片内容过多时可滚动
 * 课程：C++ 趣味学习
 */
(function () {
  'use strict';
  if (window.__cspjCoursewareUi) return;
  window.__cspjCoursewareUi = true;

  var qs = location.search || '';
  var isPreview = /[?&]preview=/.test(qs);
  var isPresenter = /[?&]presenter=1/.test(qs);

  var CODE_FILES = {
    1: "lesson01_hello.html",
    2: "lesson02_structure.html",
    3: "lesson03_comments.html",
    4: "lesson04_compile.html",
    5: "lesson05_cout.html",
    6: "lesson06_variables.html",
    7: "lesson07_cin.html",
    8: "lesson08_types.html",
    9: "lesson09_arithmetic.html",
    10: "lesson10_type_cast.html",
    11: "lesson11_comparison.html",
    12: "lesson12_logic.html",
    13: "lesson13_if.html",
    14: "lesson14_if_else.html",
    15: "lesson15_else_if.html",
    16: "lesson16_switch.html",
    17: "lesson17_while.html",
    18: "lesson18_for.html",
    19: "lesson19_dowhile.html",
    20: "lesson20_break_continue.html",
    21: "lesson21_nested_loop.html",
    22: "lesson22_triangle.html",
    23: "lesson23_diamond.html",
    24: "lesson24_math.html",
    25: "lesson25_数组初识.html",
    26: "lesson26_数组遍历.html",
    27: "lesson27_数组查找.html",
    28: "lesson28_数组趣味应用.html",
    29: "lesson29_二维数组入门.html",
    30: "lesson30_二维数组遍历.html",
    31: "lesson31_矩阵转置.html",
    32: "lesson32_二维数组趣味应用.html",
    33: "lesson33_char_ascii.html",
    34: "lesson34_string_intro.html",
    35: "lesson35_string_operations.html",
    36: "lesson36_cipher.html",
    37: "lesson37_functions_intro.html",
    38: "lesson38_parameters_return.html",
    39: "lesson39_scope.html",
    40: "lesson40_function_carnival.html",
    41: "lesson41_struct_basics.html",
    42: "lesson42_bubble_sort.html",
    43: "lesson43_selection_sort.html",
    44: "lesson44_sorting_comprehensive.html",
    45: "lesson45_guess_number.html",
    46: "lesson46_rps_game.html",
    47: "lesson47_quiz_system.html",
    48: "lesson48_graduation.html"
  };

  var VIEW_PREFIX = "../程序/view/";

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

  function boot() {
    injectCss();
    addCoverCodeButton();
  }

  if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', boot);
  } else {
    boot();
  }
})();
