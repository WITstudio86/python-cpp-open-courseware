/**
 * CSP-J 课件演讲者模式
 * 按 S 打开演讲者窗口：当前页 / 下一页 / 讲稿提示 / 计时器
 * 演讲者窗口：← → 翻页（同步主窗口）· R 重置计时 · Esc 关闭
 */
(function () {
  'use strict';
  if (window.__cspjPresenterInstalled) return;
  window.__cspjPresenterInstalled = true;

  // 预览模式：只渲染指定页，供 iframe 像素预览
  var previewMatch = /[?&]preview=(\d+)/.exec(location.search);
  if (previewMatch) {
    initPreviewMode(parseInt(previewMatch[1], 10));
    return;
  }

  var CHANNEL = 'cspj-presenter-' + (location.pathname || location.href);
  var presenterWin = null;
  var timerStart = Date.now();
  var channel = null;

  try {
    channel = new BroadcastChannel(CHANNEL);
  } catch (e) {
    channel = null;
  }

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
    var text = (clone.innerText || clone.textContent || '')
      .replace(/\r/g, '')
      .replace(/[ \t]+\n/g, '\n')
      .replace(/\n{3,}/g, '\n\n')
      .trim();
    return text;
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
      // 跳过纯装饰/页码
      if (/^[\d\s/|·•\-—]+$/.test(line)) continue;
      out.push('• ' + line);
    }
    return out.join('\n') || text.slice(0, 500);
  }

  function navigate(delta) {
    if (delta > 0) {
      var nextBtn = document.getElementById('nextBtn');
      if (nextBtn && !nextBtn.disabled) {
        nextBtn.click();
        return;
      }
      if (typeof window.goSlide === 'function') {
        try { window.goSlide(1); return; } catch (e) {}
      }
      if (typeof window.changeSlide === 'function') {
        try { window.changeSlide(1); return; } catch (e) {}
      }
      if (typeof window.nextSlide === 'function') {
        try { window.nextSlide(); return; } catch (e) {}
      }
      document.dispatchEvent(new KeyboardEvent('keydown', {
        key: 'ArrowRight', code: 'ArrowRight', bubbles: true, cancelable: true
      }));
    } else if (delta < 0) {
      var prevBtn = document.getElementById('prevBtn');
      if (prevBtn && !prevBtn.disabled) {
        prevBtn.click();
        return;
      }
      if (typeof window.goSlide === 'function') {
        try { window.goSlide(-1); return; } catch (e) {}
      }
      if (typeof window.changeSlide === 'function') {
        try { window.changeSlide(-1); return; } catch (e) {}
      }
      if (typeof window.prevSlide === 'function') {
        try { window.prevSlide(); return; } catch (e) {}
      }
      document.dispatchEvent(new KeyboardEvent('keydown', {
        key: 'ArrowLeft', code: 'ArrowLeft', bubbles: true, cancelable: true
      }));
    }
  }

  function goToIndex(idx) {
    var slides = getSlides();
    if (idx < 0 || idx >= slides.length) return;

    // 优先用已有 API（兼容 0/1 基下标）
    if (typeof window.goToSlide === 'function') {
      try {
        // 多数 0 基；若无效再试 1 基
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

    // 回退：直接切换 active
    slides.forEach(function (s, i) {
      s.classList.toggle('active', i === idx);
    });
    // 同步常见 UI
    var ind = document.getElementById('slideIndicator') || document.getElementById('slideCounter') || document.getElementById('progressText');
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
    var next = slides[idx + 1] || null;
    var notes = extractNotes(cur);
    return {
      type: 'presenter-state',
      index: idx,
      total: slides.length,
      title: document.title || '',
      currentTitle: extractTitle(cur),
      nextTitle: next ? extractTitle(next) : '（已是最后一页）',
      currentText: extractText(cur),
      nextText: next ? extractText(next) : '',
      notes: notes,
      autoScript: notes || buildAutoScript(cur),
      hasNotes: !!notes,
      timerStart: timerStart,
      deckUrl: location.href.split('?')[0].split('#')[0]
    };
  }

  function broadcastState() {
    var state = getState();
    if (presenterWin && !presenterWin.closed) {
      try {
        presenterWin.postMessage(state, '*');
      } catch (e) {}
    }
    if (channel) {
      try {
        channel.postMessage(state);
      } catch (e) {}
    }
  }

  function openPresenter() {
    if (presenterWin && !presenterWin.closed) {
      presenterWin.focus();
      broadcastState();
      return;
    }

    var w = 1280;
    var h = 800;
    var left = Math.max(0, (screen.width - w) / 2);
    var top = Math.max(0, (screen.height - h) / 2);
    presenterWin = window.open(
      '',
      'cspj-presenter',
      'width=' + w + ',height=' + h + ',left=' + left + ',top=' + top + ',resizable=yes,scrollbars=yes'
    );
    if (!presenterWin) {
      alert('无法打开演讲者窗口。请允许本站弹出窗口后，再按 S。');
      return;
    }

    var html = buildPresenterHTML();
    presenterWin.document.open();
    presenterWin.document.write(html);
    presenterWin.document.close();

    // 等子窗口脚本就绪后再推状态
    setTimeout(broadcastState, 80);
    setTimeout(broadcastState, 250);
  }

  function buildPresenterHTML() {
    var ch = CHANNEL.replace(/\\/g, '\\\\').replace(/'/g, "\\'");
    return '<!DOCTYPE html><html lang="zh-CN"><head><meta charset="UTF-8">' +
      '<meta name="viewport" content="width=device-width,initial-scale=1">' +
      '<title>演讲者模式</title>' +
      '<style>' +
      '*{box-sizing:border-box}html,body{margin:0;height:100%;font-family:-apple-system,BlinkMacSystemFont,"PingFang SC","Microsoft YaHei",sans-serif;background:#0f1419;color:#e7ecf3}' +
      'body{display:flex;flex-direction:column;padding:14px;gap:12px}' +
      '.top{display:flex;align-items:center;justify-content:space-between;gap:12px;flex-wrap:wrap}' +
      '.brand{font-weight:700;color:#d4a853;font-size:15px;letter-spacing:.04em}' +
      '.deck-title{font-size:13px;color:#9aa7b8;max-width:50%;overflow:hidden;text-overflow:ellipsis;white-space:nowrap}' +
      '.keys{font-size:12px;color:#6b7a8d}' +
      '.keys kbd{background:#1c2530;border:1px solid #2d3a4a;border-radius:4px;padding:1px 6px;margin:0 2px;color:#c5d0dc}' +
      '.grid{flex:1;min-height:0;display:grid;grid-template-columns:1.1fr 1.1fr;grid-template-rows:1.2fr 1fr;gap:12px}' +
      '.card{background:#161d27;border:1px solid #273244;border-radius:12px;display:flex;flex-direction:column;min-height:0;overflow:hidden;box-shadow:0 8px 28px rgba(0,0,0,.28)}' +
      '.card-h{display:flex;align-items:center;justify-content:space-between;padding:10px 14px;border-bottom:1px solid #273244;font-size:12px;font-weight:700;letter-spacing:.06em;text-transform:uppercase}' +
      '.card-b{flex:1;min-height:0;overflow:auto;padding:14px 16px;font-size:14px;line-height:1.65;white-space:pre-wrap;word-break:break-word}' +
      '.c-cur .card-h{color:#5eb1ff;background:linear-gradient(90deg,rgba(94,177,255,.12),transparent)}' +
      '.c-next .card-h{color:#b794f6;background:linear-gradient(90deg,rgba(183,148,246,.12),transparent)}' +
      '.c-script .card-h{color:#f6ad55;background:linear-gradient(90deg,rgba(246,173,85,.12),transparent)}' +
      '.c-timer .card-h{color:#68d391;background:linear-gradient(90deg,rgba(104,211,145,.12),transparent)}' +
      '.card-title{font-size:16px;font-weight:700;color:#fff;margin-bottom:10px;line-height:1.4}' +
      '.muted{color:#7f8b9b}' +
      '.empty{color:#5c6b7d;font-style:italic}' +
      '.timer-wrap{display:flex;flex-direction:column;align-items:center;justify-content:center;height:100%;gap:14px;padding:12px}' +
      '.clock{font-size:56px;font-weight:800;font-variant-numeric:tabular-nums;color:#68d391;letter-spacing:.04em}' +
      '.slide-n{font-size:22px;font-weight:700;color:#e7ecf3}' +
      '.btns{display:flex;gap:8px;flex-wrap:wrap;justify-content:center}' +
      'button{appearance:none;border:1px solid #334155;background:#1e293b;color:#e2e8f0;border-radius:8px;padding:8px 14px;font-size:13px;cursor:pointer;font-weight:600}' +
      'button:hover{background:#273449;border-color:#475569}' +
      'button.primary{background:#234e3a;border-color:#2f6b4f;color:#9ae6b4}' +
      'button.gold{background:#3d3218;border-color:#6b5420;color:#f0d78c}' +
      '.badge{font-size:11px;padding:2px 8px;border-radius:999px;background:#243044;color:#9fb0c3;font-weight:600;text-transform:none;letter-spacing:0}' +
      '.badge.on{background:#3d3218;color:#f0d78c}' +
      '@media (max-width:900px){.grid{grid-template-columns:1fr;grid-template-rows:auto}}' +
      '</style></head><body>' +
      '<div class="top">' +
      '<div class="brand">🎤 演讲者模式</div>' +
      '<div class="deck-title" id="deckTitle">加载中…</div>' +
      '<div class="keys"><kbd>←</kbd><kbd>→</kbd> 翻页 · <kbd>R</kbd> 重置计时 · <kbd>Esc</kbd> 关闭 · 主窗口 <kbd>S</kbd></div>' +
      '</div>' +
      '<div class="grid">' +
      '<section class="card c-cur"><div class="card-h"><span>Current · 当前页</span><span class="badge" id="curBadge">—</span></div>' +
      '<div class="card-b"><div class="card-title" id="curTitle"></div><div id="curText" class="muted"></div></div></section>' +
      '<section class="card c-next"><div class="card-h"><span>Next · 下一页</span><span class="badge" id="nextBadge">—</span></div>' +
      '<div class="card-b"><div class="card-title" id="nextTitle"></div><div id="nextText" class="muted"></div></div></section>' +
      '<section class="card c-script"><div class="card-h"><span>Script · 讲稿提示</span><span class="badge" id="scriptBadge">自动摘要</span></div>' +
      '<div class="card-b" id="scriptBody"></div></section>' +
      '<section class="card c-timer"><div class="card-h"><span>Timer · 计时</span></div>' +
      '<div class="card-b"><div class="timer-wrap">' +
      '<div class="clock" id="clock">00:00</div>' +
      '<div class="slide-n" id="slideN">— / —</div>' +
      '<div class="btns">' +
      '<button type="button" id="btnPrev">◀ 上一页</button>' +
      '<button type="button" class="primary" id="btnNext">下一页 ▶</button>' +
      '<button type="button" class="gold" id="btnReset">重置计时</button>' +
      '</div></div></div></section>' +
      '</div>' +
      '<script>(function(){' +
      'var channelName="' + ch + '";' +
      'var state=null;var timerStart=Date.now();var clockEl=document.getElementById("clock");' +
      'function fmt(ms){var s=Math.floor(ms/1000);var m=Math.floor(s/60);var h=Math.floor(m/60);s%=60;m%=60;' +
      'if(h>0)return h+":"+String(m).padStart(2,"0")+":"+String(s).padStart(2,"0");' +
      'return String(m).padStart(2,"0")+":"+String(s).padStart(2,"0");}' +
      'setInterval(function(){if(!clockEl)return;clockEl.textContent=fmt(Date.now()-timerStart);},250);' +
      'function send(msg){try{if(window.opener&&!window.opener.closed)window.opener.postMessage(msg,"*");}catch(e){}' +
      'try{if(window.__ch)window.__ch.postMessage(msg);}catch(e){}}' +
      'function apply(s){if(!s||s.type!=="presenter-state")return;state=s;' +
      'if(s.timerStart)timerStart=s.timerStart;' +
      'document.getElementById("deckTitle").textContent=s.title||"";' +
      'document.getElementById("curBadge").textContent=(s.index+1)+" / "+s.total;' +
      'document.getElementById("nextBadge").textContent=s.index+1<s.total?((s.index+2)+" / "+s.total):"END";' +
      'document.getElementById("curTitle").textContent=s.currentTitle||"";' +
      'document.getElementById("nextTitle").textContent=s.nextTitle||"";' +
      'document.getElementById("curText").textContent=s.currentText||"";' +
      'document.getElementById("nextText").textContent=s.nextText||"";' +
      'var badge=document.getElementById("scriptBadge");' +
      'if(s.hasNotes){badge.textContent="逐字稿";badge.className="badge on";}else{badge.textContent="自动摘要";badge.className="badge";}' +
      'document.getElementById("scriptBody").textContent=s.autoScript||s.notes||"";' +
      'document.getElementById("slideN").textContent=(s.index+1)+" / "+s.total;' +
      'document.title="演讲者 · "+(s.index+1)+"/"+s.total+" · "+(s.currentTitle||"");' +
      '}' +
      'window.addEventListener("message",function(e){if(e.data&&e.data.type==="presenter-state")apply(e.data);});' +
      'try{window.__ch=new BroadcastChannel(channelName);window.__ch.onmessage=function(e){if(e.data&&e.data.type==="presenter-state")apply(e.data);};}catch(e){}' +
      'document.getElementById("btnPrev").onclick=function(){send({type:"presenter-nav",delta:-1});};' +
      'document.getElementById("btnNext").onclick=function(){send({type:"presenter-nav",delta:1});};' +
      'document.getElementById("btnReset").onclick=function(){send({type:"presenter-reset-timer"});timerStart=Date.now();};' +
      'document.addEventListener("keydown",function(e){' +
      'if(e.key==="ArrowRight"||e.key==="ArrowDown"||e.key===" "){e.preventDefault();send({type:"presenter-nav",delta:1});}' +
      'else if(e.key==="ArrowLeft"||e.key==="ArrowUp"){e.preventDefault();send({type:"presenter-nav",delta:-1});}' +
      'else if(e.key==="r"||e.key==="R"){e.preventDefault();send({type:"presenter-reset-timer"});timerStart=Date.now();}' +
      'else if(e.key==="Escape"){window.close();}' +
      '});' +
      'send({type:"presenter-ready"});' +
      '})();<\/script></body></html>';
  }

  function onMessage(e) {
    var data = e.data;
    if (!data || typeof data !== 'object') return;
    if (data.type === 'presenter-nav') {
      navigate(data.delta || 0);
      // 等 DOM 更新后再广播
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
    channel.onmessage = function (e) {
      onMessage({ data: e.data });
    };
  }

  // 监听翻页（主窗口按键 / 按钮）
  var observer = new MutationObserver(function () {
    broadcastState();
  });

  function observeSlides() {
    var slides = getSlides();
    for (var i = 0; i < slides.length; i++) {
      observer.observe(slides[i], { attributes: true, attributeFilter: ['class'] });
    }
  }

  document.addEventListener('keydown', function (e) {
    // 输入框内不拦截
    var t = e.target;
    if (t && (t.tagName === 'INPUT' || t.tagName === 'TEXTAREA' || t.isContentEditable)) return;

    if (e.key === 's' || e.key === 'S') {
      // 避免与输入法/组合键冲突
      if (e.metaKey || e.ctrlKey || e.altKey) return;
      e.preventDefault();
      openPresenter();
    }
  });

  // 底部提示条（不打断现有导航）
  function injectHint() {
    if (document.getElementById('cspj-presenter-hint')) return;
    var hint = document.createElement('div');
    hint.id = 'cspj-presenter-hint';
    hint.textContent = 'S 演讲者';
    hint.title = '按 S 打开演讲者模式（第二屏：当前页 / 下一页 / 讲稿 / 计时）';
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

  function initPreviewMode(n) {
    // n 为 1-based 页码
    document.documentElement.classList.add('cspj-preview');
    var style = document.createElement('style');
    style.textContent = [
      '.header-bar,.nav-bar,.nav-buttons,#navBar,#cspj-presenter-hint,.key-hint{display:none!important}',
      'body{overflow:hidden}'
    ].join('');
    document.head.appendChild(style);

    function showOnly() {
      var slides = getSlides();
      var idx = Math.max(0, Math.min(slides.length - 1, n - 1));
      slides.forEach(function (s, i) {
        s.classList.toggle('active', i === idx);
      });
    }
    if (document.readyState === 'loading') {
      document.addEventListener('DOMContentLoaded', showOnly);
    } else {
      showOnly();
    }
    // 禁用本脚本后续逻辑
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

  // 暴露给调试
  window.openPresenterMode = openPresenter;
})();
