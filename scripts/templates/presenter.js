/**
 * CSP-J 课件演讲者模式
 *
 * 主窗口按 S → 打开 ?presenter=1 演讲者窗
 * 当前页 / 下一页 用 iframe 加载同一课件的 ?preview=N，像素级还原样式
 * 演讲者窗：← → 翻页 · R 重置计时 · Esc 关闭
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
      '  overflow:hidden!important;',
      '}',
      'html.cspj-preview .header-bar,',
      'html.cspj-preview .nav-bar,',
      'html.cspj-preview .nav-buttons,',
      'html.cspj-preview #navBar,',
      'html.cspj-preview #cspj-presenter-hint,',
      'html.cspj-preview .key-hint,',
      'html.cspj-preview .slide-dots,',
      'html.cspj-preview .progress-bar,',
      'html.cspj-preview #progressBar {',
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
      /* 非当前页彻底隐藏；当前页铺满视口，保留课件自身 display/flex 排版 */
      'html.cspj-preview .slide:not(.active) {',
      '  display:none!important;',
      '  pointer-events:none!important;',
      '  opacity:0!important;',
      '  visibility:hidden!important;',
      '}',
      'html.cspj-preview .slide.active {',
      '  position:fixed!important;',
      '  inset:0!important;top:0!important;left:0!important;right:0!important;bottom:0!important;',
      '  width:100%!important;height:100%!important;max-height:none!important;',
      '  margin:0!important;',
      '  z-index:2!important;',
      '  transform:none!important;',
      '  transition:none!important;',
      '  pointer-events:auto!important;',
      '  opacity:1!important;',
      '  visibility:visible!important;',
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
        slides[i].classList.toggle('active', i === idx);
        // 部分课件用 display 控制可见性，再补一层
        if (i === idx) {
          if (slides[i].style.display === 'none') slides[i].style.display = '';
        }
      }
      // 通知父页（可选）
      try {
        if (window.parent && window.parent !== window) {
          window.parent.postMessage({ type: 'preview-ready', index: idx, total: slides.length }, '*');
        }
      } catch (e) {}
    }

    function boot() {
      showIndex(n1based - 1);
      // 课件自身脚本可能在稍后又把第一页设为 active，延迟再设一次
      setTimeout(function () { showIndex(n1based - 1); }, 50);
      setTimeout(function () { showIndex(n1based - 1); }, 200);
    }

    if (document.readyState === 'loading') {
      document.addEventListener('DOMContentLoaded', boot);
    } else {
      boot();
    }

    // 父页无刷新切换预览页
    window.addEventListener('message', function (e) {
      var d = e.data;
      if (!d || typeof d !== 'object') return;
      if (d.type === 'preview-goto') {
        showIndex(d.index | 0);
      }
    });

    // 预览内禁用翻页，避免误操作
    document.addEventListener('keydown', function (e) {
      e.stopPropagation();
      e.preventDefault();
    }, true);

    // 不安装演讲者逻辑
  }

  /* ============================================================
   * 演讲者页面 ?presenter=1
   * ============================================================ */
  function initPresenterPage() {
    var deckUrl = location.href.split('?')[0].split('#')[0];
    var channelName = 'cspj-presenter-' + (location.pathname || deckUrl);
    var state = null;
    var timerStart = Date.now();
    var curIdx = -1;
    var nextIdx = -1;
    var channel = null;

    try { channel = new BroadcastChannel(channelName); } catch (e) {}

    // 整页替换为演讲者 UI
    document.documentElement.innerHTML = '';
    var html = document.documentElement;
    html.lang = 'zh-CN';
    var head = document.createElement('head');
    head.innerHTML = '<meta charset="UTF-8"><meta name="viewport" content="width=device-width,initial-scale=1"><title>演讲者模式</title>';
    var style = document.createElement('style');
    style.textContent = [
      '*{box-sizing:border-box}',
      'html,body{margin:0;height:100%;font-family:-apple-system,BlinkMacSystemFont,"PingFang SC","Microsoft YaHei",sans-serif;background:#0f1419;color:#e7ecf3}',
      'body{display:flex;flex-direction:column;padding:12px;gap:10px}',
      '.top{display:flex;align-items:center;justify-content:space-between;gap:12px;flex-wrap:wrap;flex-shrink:0}',
      '.brand{font-weight:700;color:#d4a853;font-size:15px;letter-spacing:.04em}',
      '.deck-title{font-size:13px;color:#9aa7b8;max-width:46%;overflow:hidden;text-overflow:ellipsis;white-space:nowrap}',
      '.keys{font-size:12px;color:#6b7a8d}',
      '.keys kbd{background:#1c2530;border:1px solid #2d3a4a;border-radius:4px;padding:1px 6px;margin:0 2px;color:#c5d0dc}',
      '.grid{flex:1;min-height:0;display:grid;grid-template-columns:1.35fr 1.35fr 0.9fr;grid-template-rows:1.4fr 1fr;gap:10px}',
      '.card{background:#161d27;border:1px solid #273244;border-radius:12px;display:flex;flex-direction:column;min-height:0;overflow:hidden;box-shadow:0 8px 28px rgba(0,0,0,.28)}',
      '.card-h{display:flex;align-items:center;justify-content:space-between;padding:8px 12px;border-bottom:1px solid #273244;font-size:11px;font-weight:700;letter-spacing:.06em;text-transform:uppercase;flex-shrink:0}',
      '.c-cur{grid-column:1;grid-row:1}',
      '.c-next{grid-column:2;grid-row:1}',
      '.c-script{grid-column:1 / span 2;grid-row:2}',
      '.c-timer{grid-column:3;grid-row:1 / span 2}',
      '.c-cur .card-h{color:#5eb1ff;background:linear-gradient(90deg,rgba(94,177,255,.12),transparent)}',
      '.c-next .card-h{color:#b794f6;background:linear-gradient(90deg,rgba(183,148,246,.12),transparent)}',
      '.c-script .card-h{color:#f6ad55;background:linear-gradient(90deg,rgba(246,173,85,.12),transparent)}',
      '.c-timer .card-h{color:#68d391;background:linear-gradient(90deg,rgba(104,211,145,.12),transparent)}',
      '.preview-stage{flex:1;min-height:0;position:relative;background:#0a0e14;overflow:hidden}',
      '.preview-stage iframe{position:absolute;top:0;left:0;border:0;background:#fff;transform-origin:top left;pointer-events:none}',
      '.preview-empty{position:absolute;inset:0;display:flex;align-items:center;justify-content:center;color:#5c6b7d;font-size:14px}',
      '.script-body{flex:1;min-height:0;overflow:auto;padding:14px 16px;font-size:15px;line-height:1.7;white-space:pre-wrap;word-break:break-word}',
      '.timer-wrap{display:flex;flex-direction:column;align-items:center;justify-content:center;height:100%;gap:16px;padding:16px}',
      '.clock{font-size:52px;font-weight:800;font-variant-numeric:tabular-nums;color:#68d391;letter-spacing:.04em}',
      '.slide-n{font-size:22px;font-weight:700;color:#e7ecf3}',
      '.btns{display:flex;flex-direction:column;gap:8px;width:100%;max-width:200px}',
      'button{appearance:none;border:1px solid #334155;background:#1e293b;color:#e2e8f0;border-radius:8px;padding:10px 14px;font-size:13px;cursor:pointer;font-weight:600;width:100%}',
      'button:hover{background:#273449;border-color:#475569}',
      'button.primary{background:#234e3a;border-color:#2f6b4f;color:#9ae6b4}',
      'button.gold{background:#3d3218;border-color:#6b5420;color:#f0d78c}',
      '.badge{font-size:11px;padding:2px 8px;border-radius:999px;background:#243044;color:#9fb0c3;font-weight:600;text-transform:none;letter-spacing:0}',
      '.badge.on{background:#3d3218;color:#f0d78c}',
      '.status{font-size:12px;color:#6b7a8d;text-align:center}',
      '@media (max-width:1100px){',
      '  .grid{grid-template-columns:1fr 1fr;grid-template-rows:1.2fr 1fr auto}',
      '  .c-timer{grid-column:1 / span 2;grid-row:3}',
      '  .btns{flex-direction:row;max-width:none;justify-content:center}',
      '  button{width:auto}',
      '}'
    ].join('\n');
    head.appendChild(style);
    document.documentElement.appendChild(head);

    var body = document.createElement('body');
    body.innerHTML = [
      '<div class="top">',
      '  <div class="brand">🎤 演讲者模式</div>',
      '  <div class="deck-title" id="deckTitle">连接主窗口中…</div>',
      '  <div class="keys"><kbd>←</kbd><kbd>→</kbd> 翻页 · <kbd>R</kbd> 重置计时 · <kbd>Esc</kbd> 关闭</div>',
      '</div>',
      '<div class="grid">',
      '  <section class="card c-cur">',
      '    <div class="card-h"><span>Current · 当前页</span><span class="badge" id="curBadge">—</span></div>',
      '    <div class="preview-stage" id="curStage">',
      '      <div class="preview-empty" id="curEmpty">等待主窗口同步…</div>',
      '      <iframe id="curFrame" title="当前页预览"></iframe>',
      '    </div>',
      '  </section>',
      '  <section class="card c-next">',
      '    <div class="card-h"><span>Next · 下一页</span><span class="badge" id="nextBadge">—</span></div>',
      '    <div class="preview-stage" id="nextStage">',
      '      <div class="preview-empty" id="nextEmpty">—</div>',
      '      <iframe id="nextFrame" title="下一页预览"></iframe>',
      '    </div>',
      '  </section>',
      '  <section class="card c-script">',
      '    <div class="card-h"><span>Script · 讲稿提示</span><span class="badge" id="scriptBadge">自动摘要</span></div>',
      '    <div class="script-body" id="scriptBody"></div>',
      '  </section>',
      '  <section class="card c-timer">',
      '    <div class="card-h"><span>Timer · 计时</span></div>',
      '    <div class="timer-wrap">',
      '      <div class="clock" id="clock">00:00</div>',
      '      <div class="slide-n" id="slideN">— / —</div>',
      '      <div class="status" id="syncStatus">等待主窗口…</div>',
      '      <div class="btns">',
      '        <button type="button" id="btnPrev">◀ 上一页</button>',
      '        <button type="button" class="primary" id="btnNext">下一页 ▶</button>',
      '        <button type="button" class="gold" id="btnReset">重置计时</button>',
      '      </div>',
      '    </div>',
      '  </section>',
      '</div>'
    ].join('');
    document.documentElement.appendChild(body);

    var curFrame = document.getElementById('curFrame');
    var nextFrame = document.getElementById('nextFrame');
    var curStage = document.getElementById('curStage');
    var nextStage = document.getElementById('nextStage');
    var curEmpty = document.getElementById('curEmpty');
    var nextEmpty = document.getElementById('nextEmpty');
    var clockEl = document.getElementById('clock');

    function fmt(ms) {
      var s = Math.floor(ms / 1000);
      var m = Math.floor(s / 60);
      var h = Math.floor(m / 60);
      s %= 60; m %= 60;
      if (h > 0) return h + ':' + String(m).padStart(2, '0') + ':' + String(s).padStart(2, '0');
      return String(m).padStart(2, '0') + ':' + String(s).padStart(2, '0');
    }

    setInterval(function () {
      if (clockEl) clockEl.textContent = fmt(Date.now() - timerStart);
    }, 250);

    function designSize() {
      // 与常见投影比例接近；预览 iframe 的虚拟分辨率
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
    if (window.ResizeObserver) {
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
      // 已加载过同一课件预览：只 postMessage 切换页，避免闪烁
      if (curSrc && curSrc.indexOf('preview=') !== -1 && iframe.contentWindow) {
        try {
          iframe.contentWindow.postMessage({ type: 'preview-goto', index: index0 }, '*');
          // 若跨页首次尚未 ready，仍设 src
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
      try {
        if (window.opener && !window.opener.closed) window.opener.postMessage(msg, '*');
      } catch (e) {}
      try {
        if (channel) channel.postMessage(msg);
      } catch (e) {}
    }

    function apply(s) {
      if (!s || s.type !== 'presenter-state') return;
      state = s;
      if (s.timerStart) timerStart = s.timerStart;

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
      document.getElementById('scriptBody').textContent = s.autoScript || s.notes || '';

      var total = s.total | 0;
      var idx = s.index | 0;
      var nidx = idx + 1;

      // 当前页
      if (idx !== curIdx || !curFrame.getAttribute('src')) {
        setFrame(curFrame, curEmpty, idx, total, false);
        curIdx = idx;
      } else {
        try { curFrame.contentWindow.postMessage({ type: 'preview-goto', index: idx }, '*'); } catch (e) {}
      }

      // 下一页
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

    document.getElementById('btnPrev').onclick = function () { send({ type: 'presenter-nav', delta: -1 }); };
    document.getElementById('btnNext').onclick = function () { send({ type: 'presenter-nav', delta: 1 }); };
    document.getElementById('btnReset').onclick = function () {
      send({ type: 'presenter-reset-timer' });
      timerStart = Date.now();
    };

    document.addEventListener('keydown', function (e) {
      if (e.key === 'ArrowRight' || e.key === 'ArrowDown' || e.key === ' ') {
        e.preventDefault();
        send({ type: 'presenter-nav', delta: 1 });
      } else if (e.key === 'ArrowLeft' || e.key === 'ArrowUp') {
        e.preventDefault();
        send({ type: 'presenter-nav', delta: -1 });
      } else if (e.key === 'r' || e.key === 'R') {
        e.preventDefault();
        send({ type: 'presenter-reset-timer' });
        timerStart = Date.now();
      } else if (e.key === 'Escape') {
        window.close();
      }
    });

    // 向主窗口报到
    send({ type: 'presenter-ready' });
    // 若 opener 已关，提示
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
    var timerStart = Date.now();
    var channel = null;
    var lastBroadcastAt = 0;

    try { channel = new BroadcastChannel(CHANNEL); } catch (e) {}

    function getSlides() {
      return Array.prototype.slice.call(document.querySelectorAll('.slide'));
    }

    function getActiveIndex() {
      var slides = getSlides();
      for (var i = 0; i < slides.length; i++) {
        if (slides[i].classList.contains('active')) return i;
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

    function navigate(delta) {
      if (delta > 0) {
        var nextBtn = document.getElementById('nextBtn');
        if (nextBtn && !nextBtn.disabled) { nextBtn.click(); return; }
        if (typeof window.goSlide === 'function') { try { window.goSlide(1); return; } catch (e) {} }
        if (typeof window.changeSlide === 'function') { try { window.changeSlide(1); return; } catch (e) {} }
        if (typeof window.nextSlide === 'function') { try { window.nextSlide(); return; } catch (e) {} }
        document.dispatchEvent(new KeyboardEvent('keydown', {
          key: 'ArrowRight', code: 'ArrowRight', bubbles: true, cancelable: true
        }));
      } else if (delta < 0) {
        var prevBtn = document.getElementById('prevBtn');
        if (prevBtn && !prevBtn.disabled) { prevBtn.click(); return; }
        if (typeof window.goSlide === 'function') { try { window.goSlide(-1); return; } catch (e) {} }
        if (typeof window.changeSlide === 'function') { try { window.changeSlide(-1); return; } catch (e) {} }
        if (typeof window.prevSlide === 'function') { try { window.prevSlide(); return; } catch (e) {} }
        document.dispatchEvent(new KeyboardEvent('keydown', {
          key: 'ArrowLeft', code: 'ArrowLeft', bubbles: true, cancelable: true
        }));
      }
    }

    function goToIndex(idx) {
      var slides = getSlides();
      if (idx < 0 || idx >= slides.length) return;

      if (typeof window.goToSlide === 'function') {
        try {
          window.goToSlide(idx);
          if (getActiveIndex() === idx) return;
          window.goToSlide(idx + 1);
          if (getActiveIndex() === idx) return;
        } catch (e) {}
      }
      if (typeof window.showSlide === 'function') {
        try {
          window.showSlide(idx);
          if (getActiveIndex() === idx) return;
          window.showSlide(idx + 1);
          if (getActiveIndex() === idx) return;
        } catch (e) {}
      }

      slides.forEach(function (s, i) {
        s.classList.toggle('active', i === idx);
      });
      var ind = document.getElementById('slideIndicator') ||
        document.getElementById('slideCounter') ||
        document.getElementById('progressText');
      if (ind) ind.textContent = (idx + 1) + ' / ' + slides.length;
      var prevBtn = document.getElementById('prevBtn');
      var nextBtn = document.getElementById('nextBtn');
      if (prevBtn) prevBtn.disabled = idx === 0;
      if (nextBtn) nextBtn.disabled = idx === slides.length - 1;
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
        timerStart: timerStart,
        deckUrl: location.href.split('?')[0].split('#')[0]
      };
    }

    function broadcastState() {
      var now = Date.now();
      // 轻微节流，避免 MutationObserver 连发
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

      var w = 1400;
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

    function onMessage(e) {
      var data = e.data;
      if (!data || typeof data !== 'object') return;
      if (data.type === 'presenter-nav') {
        navigate(data.delta || 0);
        setTimeout(broadcastState, 30);
      } else if (data.type === 'presenter-goto') {
        goToIndex(data.index | 0);
        setTimeout(broadcastState, 30);
      } else if (data.type === 'presenter-reset-timer') {
        timerStart = Date.now();
        broadcastState();
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

    document.addEventListener('keydown', function (e) {
      var t = e.target;
      if (t && (t.tagName === 'INPUT' || t.tagName === 'TEXTAREA' || t.isContentEditable)) return;
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
      hint.title = '按 S 打开演讲者模式（真实样式预览 + 讲稿 + 计时）';
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
