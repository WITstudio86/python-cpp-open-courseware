/**
 * CSP-J 课件通用增强
 * 1) 封面「查看配套代码」按钮 → 配套 程序/lessonXX_*.cpp
 * 2) 代码块至少约 10 行可视高度，超出可滚动
 * 3) 幻灯片内容过多时可纵向滚动，避免裁切省略
 */
(function () {
  'use strict';
  if (window.__cspjCoursewareUi) return;
  window.__cspjCoursewareUi = true;

  var qs = location.search || '';
  var isPreview = /[?&]preview=/.test(qs);
  var isPresenter = /[?&]presenter=1/.test(qs);

  var CODE_FILES = {
    1: "lesson01_计算机基础与进制转换.html",
    2: "lesson02_C++编程环境.html",
    3: "lesson03_变量与基本数据类型.html",
    4: "lesson04_输入输出与格式化.html",
    5: "lesson05_运算符与表达式上.html",
    6: "lesson06_运算符与表达式下.html",
    7: "lesson07_顺序结构与程序调试.html",
    8: "lesson08_if_else分支结构.html",
    9: "lesson09_switch_case多分支.html",
    10: "lesson10_for循环结构.html",
    11: "lesson11_while与do_while循环.html",
    12: "lesson12_循环控制与综合应用.html",
    13: "lesson13_一维数组.html",
    14: "lesson14_二维数组.html",
    15: "lesson15_C风格字符串.html",
    16: "lesson16_string类与字符处理.html",
    17: "lesson17_函数的定义与调用.html",
    18: "lesson18_参数传递与作用域.html",
    19: "lesson19_递归函数入门.html",
    20: "lesson20_递归应用与经典问题.html",
    21: "lesson21_结构体定义与使用.html",
    22: "lesson22_指针基础.html",
    23: "lesson23_STL入门vector与string.html",
    24: "lesson24_STL容器stack与queue.html",
    25: "lesson25_枚举算法上.html",
    26: "lesson26_枚举算法下.html",
    27: "lesson27_模拟算法上.html",
    28: "lesson28_模拟算法下.html",
    29: "lesson29_冒泡排序与选择排序.html",
    30: "lesson30_插入排序与计数排序.html",
    31: "lesson31_STLsort与自定义排序.html",
    32: "lesson32_二分查找.html",
    33: "lesson33_贪心算法上.html",
    34: "lesson34_贪心算法下.html",
    35: "lesson35_递推与数学基础.html",
    36: "lesson36_数论基础.html",
    37: "lesson37_动态规划基础.html",
    38: "lesson38_线性DP.html",
    39: "lesson39_背包问题上.html",
    40: "lesson40_背包问题下与区间DP.html",
    41: "lesson41_图论基础.html",
    42: "lesson42_DFS深度优先搜索.html",
    43: "lesson43_BFS广度优先搜索.html",
    44: "lesson44_树的基础.html",
    45: "lesson45_综合模拟一.html",
    46: "lesson46_综合模拟二.html",
    47: "lesson47_综合模拟三.html",
    48: "lesson48_考前冲刺与应试技巧.html"
  };

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
"/* 避免 pre/code 再限高导致内容被压扁；滚动由外层 .code-block 承担 */",
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
"/* 封面代码按钮 */",
".cspj-code-btn-wrap {",
"  display: flex;",
"  flex-direction: column;",
"  align-items: center;",
"  justify-content: center;",
"  margin-top: 18px;",
"  gap: 8px;",
"}",
".cspj-code-btn {",
"  display: inline-flex !important;",
"  align-items: center;",
"  gap: 8px;",
"  padding: 12px 22px;",
"  border-radius: 999px;",
"  background: linear-gradient(135deg, #d4a853, #c4922e);",
"  color: #0a2540 !important;",
"  font-weight: 700;",
"  font-size: 15px;",
"  text-decoration: none !important;",
"  box-shadow: 0 6px 18px rgba(212,168,83,0.35);",
"  border: 1px solid rgba(255,255,255,0.25);",
"  cursor: pointer;",
"  transition: transform .15s ease, box-shadow .15s ease;",
"  z-index: 5;",
"}",
".cspj-code-btn:hover {",
"  transform: translateY(-2px);",
"  box-shadow: 0 10px 24px rgba(212,168,83,0.45);",
"}",
".cspj-code-meta {",
"  font-size: 12px;",
"  opacity: 0.72;",
"}"
    ].join("\n");
    style.textContent = css;
    (document.head || document.documentElement).appendChild(style);
  }

  function detectLesson() {
    var path = decodeURIComponent(location.pathname || location.href || '');
    var m = path.match(/第0*(\d+)课/);
    if (m) return parseInt(m[1], 10);
    m = (document.title || '').match(/第\s*0*(\d+)\s*课/);
    if (m) return parseInt(m[1], 10);
    m = path.match(/lesson0*(\d+)/i);
    if (m) return parseInt(m[1], 10);
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
    var href = '../程序/view/' + file;

    var wrap = document.createElement('div');
    wrap.className = 'cspj-code-btn-wrap';

    var a = document.createElement('a');
    a.className = 'cspj-code-btn';
    a.href = href;
    a.target = '_blank';
    a.rel = 'noopener noreferrer';
    a.textContent = '📄 查看配套代码';
    a.title = '打开本课完整代码（UTF-8 查看页）：' + file;

    var meta = document.createElement('div');
    meta.className = 'cspj-code-meta';
    meta.textContent = '程序/view/' + file;

    wrap.appendChild(a);
    wrap.appendChild(meta);

    var anchor = first.querySelector('.decor') || first.querySelector('.subtitle') || first.querySelector('h1');
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
