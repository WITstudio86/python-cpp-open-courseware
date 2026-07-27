/**
 * 课件演讲者模式
 *
 * 主窗口按 S → 打开 ?presenter=1 演讲者窗
 * 当前页 / 下一页 用 iframe 加载同一课件的 ?preview=N，像素级还原样式
 * 演讲者窗：← → 翻页 · Esc 关闭 · 拖动分隔条调整区域尺寸
 *
 * 无计时器；当前页默认占更大空间；布局比例写入 localStorage
 */
(function () {
  'use strict';
  if (window.__cspjPresenterInstalled) return;
  window.__cspjPresenterInstalled = true;

  var params = new URLSearchParams(location.search || '');
  var previewParam = params.get('preview');
  var isPresenterPage = params.get('presenter') === '1';

  if (previewParam !== null && previewParam !== '') {
    initPreviewMode(Math.max(1, parseInt(previewParam, 10) || 1));
    return;
  }

  if (isPresenterPage) {
    initPresenterPage();
    return;
  }

  initAudienceMode();

  /* ============================================================
   * 预览模式：iframe 内只显示第 N 页，隐藏导航 chrome
   * ============================================================ */
  function initPreviewMode(n1based) {
    document.documentElement.classList.add('cspj-preview');

    var style = document.createElement('style');
    style.id = 'cspj-preview-style';
    style.textContent = [
      'html.cspj-preview, html.cspj-preview body {',
      '  margin:0!important;padding:0!important;height:100%!important;width:100%!important;',
      '  overflow:hidden!important;background:#fff!important;',
      '}',
      'html.cspj-preview .header-bar,',
      'html.cspj-preview .nav-bar,',
      'html.cspj-preview .nav-buttons,',
      'html.cspj-preview #navBar,',
      'html.cspj-preview #cspj-presenter-hint,',
      'html.cspj-preview .key-hint,',
      'html.cspj-preview .slide-dots,',
      'html.cspj-preview .progress-bar,',
      'html.cspj-preview #progressBar,',
      'html.cspj-preview .deck-header,',
      'html.cspj-preview .deck-footer,',
      'html.cspj-preview .notes-overlay,',
      'html.cspj-preview .overview {',
      '  display:none!important;',
      '}',
      'html.cspj-preview .deck,',
      'html.cspj-preview .slides-container,',
      'html.cspj-preview .slides-wrapper,',
      'html.cspj-preview .presentation {',
      '  position:fixed!important;inset:0!important;width:100%!important;height:100%!important;',
      '  top:0!important;left:0!important;right:0!important;bottom:0!important;',
      '  margin:0!important;padding:0!important;overflow:hidden!important;',
      '}',
      /* 兼容 .active 与 .is-active */
      'html.cspj-preview .slide:not(.active):not(.is-active) {',
      '  display:none!important;',
      '  pointer-events:none!important;',
      '  opacity:0!important;',
      '  visibility:hidden!important;',
      '}',
      'html.cspj-preview .slide.active,',
      'html.cspj-preview .slide.is-active {',
      '  position:fixed!important;',
      '  inset:0!important;top:0!important;left:0!important;right:0!important;bottom:0!important;',
      '  width:100%!important;height:100%!important;max-height:none!important;',
      '  margin:0!important;padding:24px 40px!important;',
      '  z-index:2!important;',
      '  transform:none!important;',
      '  transition:none!important;',
      '  pointer-events:auto!important;',
      '  opacity:1!important;',
      '  visibility:visible!important;',
      '  display:flex!important;',
      '  overflow:auto!important;',
      '}'
    ].join('\n');
    (document.head || document.documentElement).appendChild(style);

    function getSlides() {
      return Array.prototype.slice.call(document.querySelectorAll('.slide'));
    }

    function showIndex(idx0) {
      var slides = getSlides();
      if (!slides.length) return;
      var idx = Math.max(0, Math.min(slides.length - 1, idx0 | 0));
      for (var i = 0; i < slides.length; i++) {
        var on = i === idx;
        slides[i].classList.toggle('active', on);
        slides[i].classList.toggle('is-active', on);
        // 内联强制可见性，覆盖课件自身 opacity/transform 动画
        if (on) {
          slides[i].style.setProperty('display', 'flex', 'important');
          slides[i].style.setProperty('opacity', '1', 'important');
          slides[i].style.setProperty('visibility', 'visible', 'important');
          slides[i].style.setProperty('pointer-events', 'auto', 'important');
          slides[i].style.setProperty('transform', 'none', 'important');
          slides[i].style.setProperty('position', 'fixed', 'important');
          slides[i].style.setProperty('inset', '0', 'important');
          slides[i].style.setProperty('width', '100%', 'important');
          slides[i].style.setProperty('height', '100%', 'important');
          slides[i].style.setProperty('z-index', '2', 'important');
        } else {
          slides[i].style.setProperty('display', 'none', 'important');
          slides[i].style.setProperty('opacity', '0', 'important');
          slides[i].style.setProperty('visibility', 'hidden', 'important');
          slides[i].style.setProperty('pointer-events', 'none', 'important');
        }
      }
      try {
        if (window.parent && window.parent !== window) {
          window.parent.postMessage({ type: 'preview-ready', index: idx, total: slides.length }, '*');
        }
      } catch (e) {}
    }

    function boot() {
      showIndex(n1based - 1);
      setTimeout(function () { showIndex(n1based - 1); }, 50);
      setTimeout(function () { showIndex(n1based - 1); }, 200);
    }

    if (document.readyState === 'loading') {
      document.addEventListener('DOMContentLoaded', boot);
    } else {
      boot();
    }

    window.addEventListener('message', function (e) {
      var d = e.data;
      if (!d || typeof d !== 'object') return;
      if (d.type === 'preview-goto') {
        showIndex(d.index | 0);
      }
    });

    document.addEventListener('keydown', function (e) {
      e.stopPropagation();
      e.preventDefault();
    }, true);
  }

  /* ============================================================
   * 演讲者页面 ?presenter=1
   * ============================================================ */
  function initPresenterPage() {
    var deckUrl = location.href.split('?')[0].split('#')[0];
    var channelName = 'cspj-presenter-' + (location.pathname || deckUrl);
    var storageKey = 'cspj-presenter-layout:' + (location.pathname || deckUrl);
    var state = null;
    var curIdx = -1;
    var nextIdx = -1;
    var channel = null;
    var msgSeq = 0;

    try { channel = new BroadcastChannel(channelName); } catch (e) {}

    /*
     * 关键：不要 document.documentElement.innerHTML='' 后再 createElement('body')。
     * 浏览器清空 html 后会自动生成空 body；再 append 新 body 时元素挂不上 document，
     * getElementById 得到 null，后续脚本抛错 → 演讲者页整页空白（“不可见”）。
     * 改为复用现有 head/body，清掉旧样式后写入 UI。
     */
    var cssText = [
      '*{box-sizing:border-box}',
      'html,body{margin:0!important;padding:0!important;height:100%!important;width:100%!important;',
      '  font-family:-apple-system,BlinkMacSystemFont,"PingFang SC","Microsoft YaHei",sans-serif;',
      '  background:#0f1419!important;color:#e7ecf3;overflow:hidden!important}',
      'body{display:flex!important;flex-direction:column!important;padding:10px!important;gap:8px!important}',
      '.top{display:flex;align-items:center;justify-content:space-between;gap:12px;flex-wrap:wrap;flex-shrink:0}',
      '.brand{font-weight:700;color:#d4a853;font-size:15px;letter-spacing:.04em}',
      '.deck-title{font-size:13px;color:#9aa7b8;max-width:42%;overflow:hidden;text-overflow:ellipsis;white-space:nowrap}',
      '.keys{font-size:12px;color:#6b7a8d}',
      '.keys kbd{background:#1c2530;border:1px solid #2d3a4a;border-radius:4px;padding:1px 6px;margin:0 2px;color:#c5d0dc}',
      '.main{',
      '  flex:1 1 auto!important;min-height:0!important;height:100%!important;',
      '  display:grid!important;',
      '  grid-template-columns:minmax(200px,2.1fr) 6px minmax(140px,1fr);',
      '  grid-template-rows:minmax(120px,1fr) 6px minmax(90px,0.32fr);',
      '  gap:0;',
      '}',
      '.card{background:#161d27;border:1px solid #273244;border-radius:12px;display:flex;flex-direction:column;min-height:0;overflow:hidden;box-shadow:0 8px 28px rgba(0,0,0,.28)}',
      '.card-h{display:flex;align-items:center;justify-content:space-between;padding:8px 12px;border-bottom:1px solid #273244;font-size:11px;font-weight:700;letter-spacing:.06em;text-transform:uppercase;flex-shrink:0}',
      '.c-cur{grid-column:1;grid-row:1;min-height:0}',
      '.c-right{grid-column:3;grid-row:1;display:flex;flex-direction:column;gap:8px;min-height:0}',
      '.c-next{flex:1;min-height:0;display:flex;flex-direction:column}',
      '.c-ctrl{flex:0 0 auto}',
      '.c-script{grid-column:1 / span 3;grid-row:3;min-height:0}',
      '.c-cur .card-h{color:#5eb1ff;background:linear-gradient(90deg,rgba(94,177,255,.12),transparent)}',
      '.c-next .card-h{color:#b794f6;background:linear-gradient(90deg,rgba(183,148,246,.12),transparent)}',
      '.c-script .card-h{color:#f6ad55;background:linear-gradient(90deg,rgba(246,173,85,.12),transparent)}',
      '.c-ctrl .card-h{color:#9fb0c3;background:linear-gradient(90deg,rgba(159,176,195,.1),transparent)}',
      '.preview-stage{flex:1;min-height:0;position:relative;background:#0a0e14;overflow:hidden}',
      '.preview-stage iframe{position:absolute;top:0;left:0;border:0;background:#fff;transform-origin:top left;pointer-events:none}',
      '.preview-empty{position:absolute;inset:0;display:flex;align-items:center;justify-content:center;color:#5c6b7d;font-size:14px;z-index:1}',
      '.script-body{flex:1;min-height:0;overflow:auto;padding:14px 16px;font-size:15px;line-height:1.7;white-space:pre-wrap;word-break:break-word}',
      '.ctrl-body{display:flex;flex-direction:column;align-items:stretch;gap:10px;padding:12px}',
      '.slide-n{font-size:22px;font-weight:700;color:#e7ecf3;text-align:center;font-variant-numeric:tabular-nums}',
      '.status{font-size:12px;color:#6b7a8d;text-align:center}',
      '.btns{display:flex;gap:8px}',
      'button{appearance:none;border:1px solid #334155;background:#1e293b;color:#e2e8f0;border-radius:8px;padding:10px 12px;font-size:13px;cursor:pointer;font-weight:600;flex:1}',
      'button:hover{background:#273449;border-color:#475569}',
      'button.primary{background:#234e3a;border-color:#2f6b4f;color:#9ae6b4}',
      'button.ghost{background:transparent;border-color:#334155;color:#9fb0c3;flex:0 0 auto;padding:8px 10px;font-size:12px}',
      '.badge{font-size:11px;padding:2px 8px;border-radius:999px;background:#243044;color:#9fb0c3;font-weight:600;text-transform:none;letter-spacing:0}',
      '.badge.on{background:#3d3218;color:#f0d78c}',
      '.split-v,.split-h{position:relative;z-index:5;background:transparent}',
      '.split-v{grid-column:2;grid-row:1;cursor:col-resize}',
      '.split-h{grid-column:1 / span 3;grid-row:2;cursor:row-resize}',
      '.split-v::after,.split-h::after{',
      '  content:"";position:absolute;inset:0;margin:auto;',
      '  background:#2d3a4a;border-radius:3px;opacity:.85;',
      '  transition:background .15s,opacity .15s',
      '}',
      '.split-v::after{width:3px;height:48px}',
      '.split-h::after{height:3px;width:64px}',
      '.split-v:hover::after,.split-h:hover::after,.split-v.active::after,.split-h.active::after{background:#5eb1ff;opacity:1}',
      'body.resizing-col,body.resizing-col *{cursor:col-resize!important;user-select:none!important}',
      'body.resizing-row,body.resizing-row *{cursor:row-resize!important;user-select:none!important}',
      '@media (max-width:900px){',
      '  .main{grid-template-columns:1fr!important;grid-template-rows:1.4fr 6px .7fr 6px .9fr!important}',
      '  .c-cur{grid-column:1;grid-row:1}',
      '  .split-v{display:none}',
      '  .c-right{grid-column:1;grid-row:3;flex-direction:row}',
      '  .c-next{flex:1.2}',
      '  .c-ctrl{flex:0.8;min-width:140px}',
      '  .split-h{grid-column:1;grid-row:4}',
      '  .c-script{grid-column:1;grid-row:5}',
      '}'
    ].join('\n');

    var bodyHtml = [
      '<div class="top">',
      '  <div class="brand">🎤 演讲者模式</div>',
      '  <div class="deck-title" id="deckTitle">连接主窗口中…</div>',
      '  <div class="keys"><kbd>←</kbd><kbd>→</kbd> 翻页 · 拖动分隔条调尺寸 · <kbd>Esc</kbd> 关闭</div>',
      '</div>',
      '<div class="main" id="mainGrid">',
      '  <section class="card c-cur">',
      '    <div class="card-h"><span>Current · 当前页</span><span class="badge" id="curBadge">—</span></div>',
      '    <div class="preview-stage" id="curStage">',
      '      <div class="preview-empty" id="curEmpty">等待主窗口同步…</div>',
      '      <iframe id="curFrame" title="当前页预览"></iframe>',
      '    </div>',
      '  </section>',
      '  <div class="split-v" id="splitV" title="拖动调整左右比例"></div>',
      '  <div class="c-right">',
      '    <section class="card c-next">',
      '      <div class="card-h"><span>Next · 下一页</span><span class="badge" id="nextBadge">—</span></div>',
      '      <div class="preview-stage" id="nextStage">',
      '        <div class="preview-empty" id="nextEmpty">—</div>',
      '        <iframe id="nextFrame" title="下一页预览"></iframe>',
      '      </div>',
      '    </section>',
      '    <section class="card c-ctrl">',
      '      <div class="card-h"><span>Control · 控制</span><button type="button" class="ghost" id="btnResetLayout" title="恢复默认布局">重置布局</button></div>',
      '      <div class="ctrl-body">',
      '        <div class="slide-n" id="slideN">— / —</div>',
      '        <div class="status" id="syncStatus">等待主窗口…</div>',
      '        <div class="btns">',
      '          <button type="button" id="btnPrev">◀ 上一页</button>',
      '          <button type="button" class="primary" id="btnNext">下一页 ▶</button>',
      '        </div>',
      '      </div>',
      '    </section>',
      '  </div>',
      '  <div class="split-h" id="splitH" title="拖动调整讲稿高度"></div>',
      '  <section class="card c-script">',
      '    <div class="card-h"><span>Script · 讲稿备注</span><span class="badge" id="scriptBadge">自动摘要</span></div>',
      '    <div class="script-body" id="scriptBody"></div>',
      '  </section>',
      '</div>'
    ].join('');

    document.documentElement.lang = 'zh-CN';
    document.documentElement.style.cssText = 'height:100%;margin:0;padding:0;background:#0f1419;';

    // 移除课件原有样式，避免覆盖演讲者 UI
    var oldSheets = document.querySelectorAll('style, link[rel="stylesheet"]');
    for (var si = 0; si < oldSheets.length; si++) {
      try { oldSheets[si].parentNode.removeChild(oldSheets[si]); } catch (e) {}
    }

    var head = document.head;
    if (!head) {
      head = document.createElement('head');
      document.documentElement.insertBefore(head, document.documentElement.firstChild);
    }
    head.innerHTML = '<meta charset="UTF-8"><meta name="viewport" content="width=device-width,initial-scale=1"><title>演讲者模式</title>';
    var style = document.createElement('style');
    style.id = 'cspj-presenter-style';
    style.textContent = cssText;
    head.appendChild(style);

    var body = document.body;
    if (!body) {
      body = document.createElement('body');
      document.documentElement.appendChild(body);
    }
    body.className = '';
    body.removeAttribute('style');
    body.style.cssText = 'display:flex;flex-direction:column;height:100%;margin:0;padding:10px;gap:8px;background:#0f1419;color:#e7ecf3;overflow:hidden;';
    body.innerHTML = bodyHtml;

    var mainGrid = document.getElementById('mainGrid');
    var curFrame = document.getElementById('curFrame');
    var nextFrame = document.getElementById('nextFrame');
    var curStage = document.getElementById('curStage');
    var nextStage = document.getElementById('nextStage');
    var curEmpty = document.getElementById('curEmpty');
    var nextEmpty = document.getElementById('nextEmpty');

    if (!mainGrid || !curFrame || !nextFrame) {
      // 极端兜底：整页 document.write
      try {
        document.open();
        document.write('<!DOCTYPE html><html lang="zh-CN"><head><meta charset="UTF-8"><title>演讲者模式</title><style>' +
          cssText + '</style></head><body style="display:flex;flex-direction:column;height:100%;margin:0;padding:10px;gap:8px;background:#0f1419;color:#e7ecf3">' +
          bodyHtml + '</body></html>');
        document.close();
      } catch (e) {}
      mainGrid = document.getElementById('mainGrid');
      curFrame = document.getElementById('curFrame');
      nextFrame = document.getElementById('nextFrame');
      curStage = document.getElementById('curStage');
      nextStage = document.getElementById('nextStage');
      curEmpty = document.getElementById('curEmpty');
      nextEmpty = document.getElementById('nextEmpty');
    }

    function defaultLayout() {
      return { curPct: 68, scriptPct: 24 };
    }

    function loadLayout() {
      try {
        var raw = localStorage.getItem(storageKey);
        if (!raw) return defaultLayout();
        var o = JSON.parse(raw);
        return {
          curPct: clamp(o.curPct, 40, 82),
          scriptPct: clamp(o.scriptPct, 14, 50)
        };
      } catch (e) {
        return defaultLayout();
      }
    }

    function saveLayout(layout) {
      try { localStorage.setItem(storageKey, JSON.stringify(layout)); } catch (e) {}
    }

    function clamp(n, a, b) {
      n = Number(n);
      if (isNaN(n)) return a;
      return Math.max(a, Math.min(b, n));
    }

    function applyLayout(layout) {
      if (!mainGrid) return;
      // 用 fr 比例，避免 % 在 grid 中高度未确定时塌成 0
      var cur = layout.curPct;
      var right = Math.max(18, 100 - cur);
      var top = Math.max(50, 100 - layout.scriptPct);
      var script = layout.scriptPct;
      mainGrid.style.gridTemplateColumns =
        'minmax(200px,' + cur + 'fr) 6px minmax(140px,' + right + 'fr)';
      mainGrid.style.gridTemplateRows =
        'minmax(120px,' + top + 'fr) 6px minmax(90px,' + script + 'fr)';
    }

    var layout = loadLayout();
    applyLayout(layout);

    function bindSplitter(el, axis) {
      if (!el || !mainGrid) return;
      el.addEventListener('mousedown', function (e) {
        if (e.button !== 0) return;
        e.preventDefault();
        el.classList.add('active');
        document.body.classList.add(axis === 'col' ? 'resizing-col' : 'resizing-row');
        var rect = mainGrid.getBoundingClientRect();

        function onMove(ev) {
          if (axis === 'col') {
            var x = ev.clientX - rect.left;
            var pct = (x / rect.width) * 100;
            layout.curPct = clamp(pct, 40, 82);
            applyLayout(layout);
            fitAll();
          } else {
            var fromBottom = rect.bottom - ev.clientY;
            var pctH = (fromBottom / rect.height) * 100;
            layout.scriptPct = clamp(pctH, 14, 50);
            applyLayout(layout);
            fitAll();
          }
        }
        function onUp() {
          el.classList.remove('active');
          document.body.classList.remove('resizing-col', 'resizing-row');
          document.removeEventListener('mousemove', onMove);
          document.removeEventListener('mouseup', onUp);
          saveLayout(layout);
          fitAll();
        }
        document.addEventListener('mousemove', onMove);
        document.addEventListener('mouseup', onUp);
      });
    }

    bindSplitter(document.getElementById('splitV'), 'col');
    bindSplitter(document.getElementById('splitH'), 'row');

    var btnReset = document.getElementById('btnResetLayout');
    if (btnReset) {
      btnReset.onclick = function () {
        layout = defaultLayout();
        applyLayout(layout);
        saveLayout(layout);
        fitAll();
      };
    }

    function designSize() {
      return { w: 1280, h: 720 };
    }

    function fitFrame(stage, iframe) {
      if (!stage || !iframe || !iframe.getAttribute('src')) return;
      var ds = designSize();
      var sw = stage.clientWidth;
      var sh = stage.clientHeight;
      if (sw < 10 || sh < 10) return;
      var scale = Math.min(sw / ds.w, sh / ds.h);
      iframe.style.width = ds.w + 'px';
      iframe.style.height = ds.h + 'px';
      iframe.style.transform = 'scale(' + scale + ')';
      iframe.style.left = Math.round((sw - ds.w * scale) / 2) + 'px';
      iframe.style.top = Math.round((sh - ds.h * scale) / 2) + 'px';
    }

    function fitAll() {
      fitFrame(curStage, curFrame);
      fitFrame(nextStage, nextFrame);
    }

    window.addEventListener('resize', fitAll);
    if (window.ResizeObserver && curStage && nextStage) {
      var ro = new ResizeObserver(fitAll);
      ro.observe(curStage);
      ro.observe(nextStage);
    }

    function previewUrl(index0) {
      return deckUrl + '?preview=' + (index0 + 1);
    }

    function setFrame(iframe, emptyEl, index0, total, isEnd) {
      if (isEnd || index0 < 0 || index0 >= total) {
        iframe.removeAttribute('src');
        iframe.style.visibility = 'hidden';
        if (emptyEl) {
          emptyEl.style.display = 'flex';
          emptyEl.textContent = isEnd ? '已是最后一页' : '—';
        }
        return;
      }
      if (emptyEl) emptyEl.style.display = 'none';
      iframe.style.visibility = 'visible';
      var want = previewUrl(index0);
      var curSrc = iframe.getAttribute('src') || '';
      if (curSrc && curSrc.indexOf('preview=') !== -1 && iframe.contentWindow) {
        try {
          iframe.contentWindow.postMessage({ type: 'preview-goto', index: index0 }, '*');
          if (!iframe.__previewReady) {
            iframe.src = want;
          }
          return;
        } catch (e) {
          iframe.src = want;
          return;
        }
      }
      iframe.onload = function () {
        iframe.__previewReady = true;
        try {
          iframe.contentWindow.postMessage({ type: 'preview-goto', index: index0 }, '*');
        } catch (e) {}
        fitAll();
      };
      iframe.__previewReady = false;
      iframe.src = want;
    }

    function send(msg) {
      msgSeq += 1;
      msg._id = msgSeq;
      msg._ts = Date.now();
      // 优先 opener.postMessage；BroadcastChannel 作备用。
      // 接收端会按 _id 去重，避免双通道导致连翻。
      var sentOpener = false;
      try {
        if (window.opener && !window.opener.closed) {
          window.opener.postMessage(msg, '*');
          sentOpener = true;
        }
      } catch (e) {}
      try {
        if (channel) channel.postMessage(msg);
      } catch (e) {}
      return sentOpener || !!channel;
    }

    function apply(s) {
      if (!s || s.type !== 'presenter-state') return;
      state = s;

      document.getElementById('deckTitle').textContent = s.title || '';
      document.getElementById('curBadge').textContent = (s.index + 1) + ' / ' + s.total;
      document.getElementById('nextBadge').textContent =
        s.index + 1 < s.total ? (s.index + 2) + ' / ' + s.total : 'END';
      document.getElementById('slideN').textContent = (s.index + 1) + ' / ' + s.total;
      document.getElementById('syncStatus').textContent = '已与主窗口同步';
      document.title = '演讲者 · ' + (s.index + 1) + '/' + s.total + ' · ' + (s.currentTitle || '');

      var badge = document.getElementById('scriptBadge');
      if (s.hasNotes) {
        badge.textContent = '逐字稿';
        badge.className = 'badge on';
      } else {
        badge.textContent = '自动摘要';
        badge.className = 'badge';
      }
      document.getElementById('scriptBody').textContent = s.notes || s.autoScript || '';

      var total = s.total | 0;
      var idx = s.index | 0;
      var nidx = idx + 1;

      if (idx !== curIdx || !curFrame.getAttribute('src')) {
        setFrame(curFrame, curEmpty, idx, total, false);
        curIdx = idx;
      } else {
        try { curFrame.contentWindow.postMessage({ type: 'preview-goto', index: idx }, '*'); } catch (e) {}
      }

      if (nidx >= total) {
        setFrame(nextFrame, nextEmpty, -1, total, true);
        nextIdx = -1;
      } else if (nidx !== nextIdx || !nextFrame.getAttribute('src')) {
        setFrame(nextFrame, nextEmpty, nidx, total, false);
        nextIdx = nidx;
      } else {
        try { nextFrame.contentWindow.postMessage({ type: 'preview-goto', index: nidx }, '*'); } catch (e) {}
      }

      requestAnimationFrame(fitAll);
      setTimeout(fitAll, 100);
      setTimeout(fitAll, 400);
    }

    window.addEventListener('message', function (e) {
      if (e.data && e.data.type === 'presenter-state') apply(e.data);
    });
    if (channel) {
      channel.onmessage = function (e) {
        if (e.data && e.data.type === 'presenter-state') apply(e.data);
      };
    }

    var btnPrev = document.getElementById('btnPrev');
    var btnNext = document.getElementById('btnNext');
    if (btnPrev) btnPrev.onclick = function () { send({ type: 'presenter-nav', delta: -1 }); };
    if (btnNext) btnNext.onclick = function () { send({ type: 'presenter-nav', delta: 1 }); };

    document.addEventListener('keydown', function (e) {
      // 忽略系统按键连发，避免一次长按/重复 keydown 多翻几页
      if (e.repeat) return;
      if (e.metaKey || e.ctrlKey || e.altKey) return;
      if (e.key === 'ArrowRight' || e.key === 'ArrowDown' || e.key === ' ' || e.key === 'PageDown') {
        e.preventDefault();
        send({ type: 'presenter-nav', delta: 1 });
      } else if (e.key === 'ArrowLeft' || e.key === 'ArrowUp' || e.key === 'PageUp') {
        e.preventDefault();
        send({ type: 'presenter-nav', delta: -1 });
      } else if (e.key === 'Escape') {
        window.close();
      }
    });

    send({ type: 'presenter-ready' });
    setTimeout(function () {
      if (!state) {
        document.getElementById('syncStatus').textContent =
          '未收到主窗口状态：请从课件主窗口按 S 打开本页，不要单独打开 ?presenter=1';
      }
    }, 1500);
  }

  /* ============================================================
   * 观众主窗口
   * ============================================================ */
  function initAudienceMode() {
    var CHANNEL = 'cspj-presenter-' + (location.pathname || location.href);
    var presenterWin = null;
    var channel = null;
    var lastBroadcastAt = 0;
    var lastNavKey = '';
    var lastNavAt = 0;

    try { channel = new BroadcastChannel(CHANNEL); } catch (e) {}

    function getSlides() {
      return Array.prototype.slice.call(document.querySelectorAll('.slide'));
    }

    function getActiveIndex() {
      var slides = getSlides();
      for (var i = 0; i < slides.length; i++) {
        if (slides[i].classList.contains('active') || slides[i].classList.contains('is-active')) return i;
      }
      return 0;
    }

    function extractText(el) {
      if (!el) return '';
      var clone = el.cloneNode(true);
      var notes = clone.querySelectorAll('.notes, aside.notes, .speaker-notes');
      for (var i = 0; i < notes.length; i++) notes[i].parentNode.removeChild(notes[i]);
      return (clone.innerText || clone.textContent || '')
        .replace(/\r/g, '')
        .replace(/[ \t]+\n/g, '\n')
        .replace(/\n{3,}/g, '\n\n')
        .trim();
    }

    function extractNotes(el) {
      if (!el) return '';
      var noteEl = el.querySelector('.notes, aside.notes, .speaker-notes');
      if (!noteEl) return '';
      return (noteEl.innerText || noteEl.textContent || '').trim();
    }

    function extractTitle(el) {
      if (!el) return '（无）';
      var h = el.querySelector('h1, h2, h3');
      if (h) return (h.innerText || h.textContent || '').trim();
      var t = extractText(el).split('\n')[0] || '（无标题）';
      return t.slice(0, 80);
    }

    function buildAutoScript(el) {
      var text = extractText(el);
      if (!text) return '（本页暂无内容）';
      var lines = text.split('\n').map(function (l) { return l.trim(); }).filter(Boolean);
      var out = [];
      for (var i = 0; i < lines.length && out.length < 12; i++) {
        var line = lines[i];
        if (line.length < 2) continue;
        if (/^[\d\s/|·•\-—]+$/.test(line)) continue;
        out.push('• ' + line);
      }
      return out.join('\n') || text.slice(0, 500);
    }

    function goToIndex(idx) {
      var slides = getSlides();
      if (idx < 0 || idx >= slides.length) return false;

      if (typeof window.goToSlide === 'function') {
        try {
          window.goToSlide(idx);
          if (getActiveIndex() === idx) return true;
          // 部分课件为 1-based
          window.goToSlide(idx + 1);
          if (getActiveIndex() === idx) return true;
        } catch (e) {}
      }
      if (typeof window.showSlide === 'function') {
        try {
          window.showSlide(idx);
          if (getActiveIndex() === idx) return true;
          window.showSlide(idx + 1);
          if (getActiveIndex() === idx) return true;
        } catch (e) {}
      }

      // 直接切换 class，并尽量同步内部 current 变量相关 UI
      slides.forEach(function (s, i) {
        s.classList.toggle('active', i === idx);
        s.classList.toggle('is-active', i === idx);
      });
      var ind = document.getElementById('slideIndicator') ||
        document.getElementById('slideCounter') ||
        document.getElementById('progressText');
      if (ind) ind.textContent = (idx + 1) + ' / ' + slides.length;
      var prevBtn = document.getElementById('prevBtn');
      var nextBtn = document.getElementById('nextBtn');
      if (prevBtn) prevBtn.disabled = idx === 0;
      if (nextBtn) nextBtn.disabled = idx === slides.length - 1;
      return getActiveIndex() === idx;
    }

    /**
     * 只走一条导航路径，避免 nextBtn + goSlide + 合成键盘 叠加连翻。
     * 优先调用课件自身 API（会更新内部 current），最后才兜底改 class。
     */
    function navigate(delta) {
      if (!delta) return;
      var slides = getSlides();
      if (!slides.length) return;
      var idx = getActiveIndex();
      var target = idx + (delta > 0 ? 1 : -1);
      if (target < 0 || target >= slides.length) return;

      try {
        // 1) 绝对跳转 API（若存在且生效）
        if (typeof window.goToSlide === 'function') {
          window.goToSlide(target);
          if (getActiveIndex() === target) return;
          window.goToSlide(target + 1); // 兼容 1-based
          if (getActiveIndex() === target) return;
        }
        if (typeof window.showSlide === 'function') {
          window.showSlide(target);
          if (getActiveIndex() === target) return;
          window.showSlide(target + 1);
          if (getActiveIndex() === target) return;
        }

        // 2) 相对 API / 按钮 —— 只调用其中一个
        if (delta > 0) {
          if (typeof window.nextSlide === 'function') { window.nextSlide(); return; }
          if (typeof window.changeSlide === 'function') { window.changeSlide(1); return; }
          if (typeof window.goSlide === 'function') { window.goSlide(1); return; }
          var nextBtn = document.getElementById('nextBtn');
          if (nextBtn && !nextBtn.disabled) { nextBtn.click(); return; }
        } else {
          if (typeof window.prevSlide === 'function') { window.prevSlide(); return; }
          if (typeof window.changeSlide === 'function') { window.changeSlide(-1); return; }
          if (typeof window.goSlide === 'function') { window.goSlide(-1); return; }
          var prevBtn = document.getElementById('prevBtn');
          if (prevBtn && !prevBtn.disabled) { prevBtn.click(); return; }
        }
      } catch (e) {}

      // 3) 兜底：直接改 class（部分课件无全局导航函数）
      goToIndex(target);
    }

    function getState() {
      var slides = getSlides();
      var idx = getActiveIndex();
      var cur = slides[idx] || null;
      var notes = extractNotes(cur);
      return {
        type: 'presenter-state',
        index: idx,
        total: slides.length,
        title: document.title || '',
        currentTitle: extractTitle(cur),
        notes: notes,
        autoScript: notes || buildAutoScript(cur),
        hasNotes: !!notes,
        deckUrl: location.href.split('?')[0].split('#')[0]
      };
    }

    function broadcastState() {
      var now = Date.now();
      if (now - lastBroadcastAt < 40) {
        clearTimeout(broadcastState._t);
        broadcastState._t = setTimeout(broadcastState, 50);
        return;
      }
      lastBroadcastAt = now;
      var state = getState();
      if (presenterWin && !presenterWin.closed) {
        try { presenterWin.postMessage(state, '*'); } catch (e) {}
      }
      if (channel) {
        try { channel.postMessage(state); } catch (e) {}
      }
    }

    function openPresenter() {
      var base = location.href.split('?')[0].split('#')[0];
      var url = base + '?presenter=1';

      if (presenterWin && !presenterWin.closed) {
        try {
          presenterWin.focus();
          broadcastState();
          return;
        } catch (e) {}
      }

      var w = 1440;
      var h = 900;
      var left = Math.max(0, (screen.width - w) / 2);
      var top = Math.max(0, (screen.height - h) / 2);
      presenterWin = window.open(
        url,
        'cspj-presenter',
        'width=' + w + ',height=' + h + ',left=' + left + ',top=' + top + ',resizable=yes,scrollbars=yes'
      );
      if (!presenterWin) {
        alert('无法打开演讲者窗口。请允许本站弹出窗口后，再按 S。');
        return;
      }

      setTimeout(broadcastState, 120);
      setTimeout(broadcastState, 400);
      setTimeout(broadcastState, 1000);
    }

    function shouldAcceptNav(data) {
      var now = Date.now();
      var key = (data._id != null ? String(data._id) : '') + '|' + (data.delta || 0) + '|' + (data._ts || '');
      // 同一条消息经 postMessage + BroadcastChannel 双达：去重
      if (key && key === lastNavKey && now - lastNavAt < 400) return false;
      // 短时间重复 delta 也挡一下（异常双绑）
      if (now - lastNavAt < 90 && lastNavKey.indexOf('|' + (data.delta || 0) + '|') !== -1) return false;
      lastNavKey = key || ('d' + (data.delta || 0) + now);
      lastNavAt = now;
      return true;
    }

    function onMessage(e) {
      var data = e.data;
      if (!data || typeof data !== 'object') return;
      if (data.type === 'presenter-nav') {
        if (!shouldAcceptNav(data)) return;
        navigate(data.delta || 0);
        setTimeout(broadcastState, 30);
      } else if (data.type === 'presenter-goto') {
        goToIndex(data.index | 0);
        setTimeout(broadcastState, 30);
      } else if (data.type === 'presenter-ready') {
        broadcastState();
      }
    }

    window.addEventListener('message', onMessage);
    if (channel) {
      channel.onmessage = function (e) { onMessage({ data: e.data }); };
    }

    var observer = new MutationObserver(function () { broadcastState(); });

    function observeSlides() {
      var slides = getSlides();
      for (var i = 0; i < slides.length; i++) {
        observer.observe(slides[i], { attributes: true, attributeFilter: ['class'] });
      }
    }

    // 捕获阶段拦截方向键连发：部分课件自身 keydown 未判断 e.repeat，会一次按住连翻多页
    document.addEventListener('keydown', function (e) {
      if (!e.repeat) return;
      var k = e.key;
      if (k === 'ArrowLeft' || k === 'ArrowRight' || k === 'ArrowUp' || k === 'ArrowDown' ||
          k === ' ' || k === 'PageUp' || k === 'PageDown' || k === 'Enter' || k === 'Backspace') {
        e.preventDefault();
        e.stopImmediatePropagation();
      }
    }, true);

    document.addEventListener('keydown', function (e) {
      var t = e.target;
      if (t && (t.tagName === 'INPUT' || t.tagName === 'TEXTAREA' || t.isContentEditable)) return;
      if (e.repeat) return;
      if (e.key === 's' || e.key === 'S') {
        if (e.metaKey || e.ctrlKey || e.altKey) return;
        e.preventDefault();
        openPresenter();
      }
    });

    function injectHint() {
      if (document.getElementById('cspj-presenter-hint')) return;
      var hint = document.createElement('div');
      hint.id = 'cspj-presenter-hint';
      hint.textContent = 'S 演讲者';
      hint.title = '按 S 打开演讲者模式（当前页大预览 + 讲稿备注 + 可调布局）';
      hint.style.cssText = [
        'position:fixed', 'right:12px', 'bottom:12px', 'z-index:99999',
        'background:rgba(10,37,64,0.88)', 'color:#f0d78c',
        'font:600 12px/1.2 -apple-system,BlinkMacSystemFont,"PingFang SC","Microsoft YaHei",sans-serif',
        'padding:6px 10px', 'border-radius:999px', 'border:1px solid rgba(212,168,83,0.45)',
        'cursor:pointer', 'user-select:none', 'letter-spacing:0.04em',
        'box-shadow:0 4px 16px rgba(0,0,0,0.25)', 'opacity:0.92'
      ].join(';');
      hint.addEventListener('click', openPresenter);
      document.body.appendChild(hint);
    }

    function hideNotesOnAudience() {
      if (document.getElementById('cspj-notes-hide-style')) return;
      var style = document.createElement('style');
      style.id = 'cspj-notes-hide-style';
      style.textContent = '.notes, aside.notes, .speaker-notes{display:none!important}';
      document.head.appendChild(style);
    }

    function boot() {
      hideNotesOnAudience();
      observeSlides();
      injectHint();
    }

    if (document.readyState === 'loading') {
      document.addEventListener('DOMContentLoaded', boot);
    } else {
      boot();
    }

    window.openPresenterMode = openPresenter;
  }
})();
