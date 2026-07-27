/**
 * 课件通用增强（自动生成）
 * - 封面配套代码按钮（UTF-8 浅色查看页）
 * - 代码块至少约 10 行可视高度并可滚动
 * - 幻灯片内容过多时可滚动
 * 课程：Python 趣味学习
 */
(function () {
  'use strict';
  if (window.__cspjCoursewareUi) return;
  window.__cspjCoursewareUi = true;

  var qs = location.search || '';
  var isPreview = /[?&]preview=/.test(qs);
  var isPresenter = /[?&]presenter=1/.test(qs);

  var CODE_FILES = {
    1: "lesson_01_hello_python.html",
    2: "lesson_02_first_program.html",
    3: "lesson_03_print_fun.html",
    4: "lesson_04_input_chat.html",
    5: "lesson_05_variables.html",
    6: "lesson_06_numbers.html",
    7: "lesson_07_strings.html",
    8: "lesson_08_string_methods.html",
    9: "lesson_09_type_conversion.html",
    10: "lesson_10_chatbot.html",
    11: "lesson_11_comparison.html",
    12: "lesson_12_if_statement.html",
    13: "lesson_13_if_else.html",
    14: "lesson_14_if_elif_else.html",
    15: "lesson_15_guessing_game.html",
    16: "lesson_16_for_loop.html",
    17: "lesson_17_range.html",
    18: "lesson_18_for_loop_practice.html",
    19: "lesson_19_while_loop.html",
    20: "lesson_20_break_continue.html",
    21: "lesson_21_multiplication_table.html",
    22: "lesson_22_lists.html",
    23: "lesson_23_list_ops.html",
    24: "lesson_24_list_advanced.html",
    25: "lesson_25_dict.html",
    26: "lesson_26_dict_ops.html",
    27: "lesson_27_contacts.html",
    28: "lesson_28_function_intro.html",
    29: "lesson_29_def.html",
    30: "lesson_30_params.html",
    31: "lesson_31_return.html",
    32: "lesson_32_toolbox.html",
    33: "lesson_33_turtle_intro.html",
    34: "lesson_34_basic_shapes.html",
    35: "lesson_35_circles_and_arcs.html",
    36: "lesson_36_colors_and_styles.html",
    37: "lesson_37_loop_patterns.html",
    38: "lesson_38_turtle_exhibition.html",
    39: "lesson_39_dice_simulator.html",
    40: "lesson_40_word_translator.html",
    41: "lesson_41_rock_paper_scissors.html",
    42: "lesson_42_score_statistics.html",
    43: "lesson_43_turtle_city.html",
    44: "lesson_44_quiz_challenge.html",
    45: "lesson_45_password_generator.html",
    46: "lesson_46_turtle_fireworks.html",
    47: "lesson_47_challenge_gates_part1.html",
    48: "lesson_48_challenge_gates_part2.html"
  };

  var VIEW_PREFIX = "../代码/view/";

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
