/**
 * 课件通用增强（自动生成）
 * - 封面配套代码按钮（UTF-8 浅色查看页）
 * - 代码块至少约 10 行可视高度并可滚动
 * - 幻灯片内容过多时可滚动
 * 课程：Pygame 零基础
 */
(function () {
  'use strict';
  if (window.__cspjCoursewareUi) return;
  window.__cspjCoursewareUi = true;

  var qs = location.search || '';
  var isPreview = /[?&]preview=/.test(qs);
  var isPresenter = /[?&]presenter=1/.test(qs);

  var CODE_FILES = {
    47: "第47节-游戏博览会__README.html",
    1: "第1节-HelloPygame__main.html",
    2: "第2节-让画面动起来__main.html",
    3: "第3节-键盘是我的遥控器__main.html",
    4: "第4节-鼠标与图片__main.html",
    5: "第5节-会反弹的球__main.html",
    6: "第6节-砖块消消乐__main.html",
    7: "第7节-天上掉水果__main.html",
    8: "第8节-水果升级__main.html",
    9: "第9节-贪吃的小蛇__main.html",
    10: "第10节-完整贪吃蛇__main.html",
    11: "第11节-冒出来的地鼠__main.html",
    12: "第12节-限时挑战__main.html",
    13: "第13节-翻开看看__main.html",
    14: "第14节-配对消除__main.html",
    15: "第15节-战机起飞__main.html",
    16: "第16节-敌人来袭__main.html",
    17: "第17节-走不出的迷宫__main.html",
    18: "第18节-寻找终点__main.html",
    19: "第19节-数字会合并__main.html",
    20: "第20节-完整2048__main.html",
    21: "第21节-双人对战__main.html",
    22: "第22节-人机对战__main.html",
    23: "第23节-扑腾的小鸟__main.html",
    24: "第24节-水管森林__main.html",
    25: "第25节-外星人军团__main.html",
    26: "第26节-保卫地球__main.html",
    27: "第27节-瞄准发射__main.html",
    28: "第28节-同色消除__main.html",
    29: "第29节-防御工事__main.html",
    30: "第30节-炮塔开火__main.html",
    31: "第31节-弹幕来袭__main.html",
    32: "第32节-火力全开__main.html",
    33: "第33节-跑和跳__main.html",
    34: "第34节-闯关之旅__main.html",
    35: "第35节-屏幕在抖__main.html",
    36: "第36节-特效大赏__main.html",
    37: "第37节-极速躲避__main.html",
    38: "第38节-收集与道具__main.html",
    39: "第39节-方块下落__main.html",
    40: "第40节-消行与加速__main.html",
    41: "第41节-搬箱子__main.html",
    42: "第42节-关卡系统__main.html",
    43: "第43节-回合对战__main.html",
    44: "第44节-冒险启程__main.html",
    45: "第45节-我的游戏我设计1__main.html",
    46: "第46节-打磨我的作品2__main.html",
    48: "第48节-回顾与展望__颁奖庆祝动画.html"
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
