/**
 * 课件通用增强（自动生成）
 * - 封面配套代码按钮（UTF-8 浅色查看页）
 * - 代码块至少约 10 行可视高度并可滚动
 * - 幻灯片内容过多时可滚动
 * 课程：Python Tkinter
 */
(function () {
  'use strict';
  if (window.__cspjCoursewareUi) return;
  window.__cspjCoursewareUi = true;

  var qs = location.search || '';
  var isPreview = /[?&]preview=/.test(qs);
  var isPresenter = /[?&]presenter=1/.test(qs);

  var CODE_FILES = {
    1: "L01-第一个窗口.html",
    2: "L02-电子公告牌.html",
    3: "L03-点我计数小工具.html",
    4: "L04-名字生成器.html",
    5: "L05-打招呼机器人.html",
    6: "L06-个人信息卡.html",
    7: "L07-两种布局对比.html",
    8: "L08-计算器按钮面板.html",
    9: "L09-喜好收集器.html",
    10: "L10-趣味问答小测验.html",
    11: "L11-愿望清单管理器.html",
    12: "L12-个性名片生成器.html",
    13: "L13-RGB调色板.html",
    14: "L14-迷你记事本.html",
    15: "L15-几何图形画廊.html",
    16: "L16-涂鸦板.html",
    17: "L17-带菜单的记事本.html",
    18: "L18-个人信息小管家.html",
    19: "L19-电子时钟上.html",
    20: "L20-电子时钟下.html",
    21: "L21-简易计算器上.html",
    22: "L22-简易计算器下.html",
    23: "L23-猜数字游戏上.html",
    24: "L24-猜数字游戏下.html",
    25: "L25-待办事项清单上.html",
    26: "L26-待办事项清单-下.html",
    27: "L27-电子相册-上.html",
    28: "L28-电子相册-下.html",
    29: "L29-天气预报查询-上.html",
    30: "L30-天气预报查询-下.html",
    31: "L31-单词记忆卡-上.html",
    32: "L32-单词记忆卡-下.html",
    33: "L33-迷你画图板-上.html",
    34: "L34-迷你画图板下.html",
    35: "L35-密码管理器上.html",
    36: "L36-密码管理器下.html",
    37: "L37-贪吃蛇游戏上.html",
    38: "L38-贪吃蛇游戏下.html",
    39: "L39-倒计时番茄钟上.html",
    40: "L40-倒计时番茄钟下.html",
    41: "L41-班级通讯录上.html",
    42: "L42-班级通讯录中.html",
    43: "L43-班级通讯录下.html",
    44: "L44-打字速度测试上.html",
    45: "L45-打字速度测试中.html",
    46: "L46-打字速度测试下.html",
    47: "L47-tkinter进阶.html",
    48: "L48-自由创作-作品模板.html"
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
