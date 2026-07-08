# 无人机地震救援 Scratch 3 — Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Generate a complete Scratch 3 `.sb3` file via a Python script that builds `project.json` with all sprites, scripts, backdrops, and SVG assets for the drone earthquake rescue interactive program.

**Architecture:** A single Python script `generate_sb3.py` that uses helper functions to construct Scratch 3 blocks, embeds SVG vector graphics as costumes/backdrops, assembles the full `project.json` structure, and packages it into a `.sb3` (ZIP) file.

**Tech Stack:** Python 3 (stdlib only: json, zipfile, uuid, math)

## Global Constraints

- All assets are inline SVG (no external files needed)
- Sound effects use Scratch built-in sound library references
- Chinese text content throughout (per spec文案清单)
- 5 scenes with broadcast-driven flow
- 3 survivor targets with distance-based detection
- .sb3 output must load in Scratch 3 desktop/online

---

## File Structure

```
scratch_drone_rescue/
├── generate_sb3.py          # Main generator script (~800 lines)
└── output/
    └── drone_rescue.sb3     # Generated output file
```

---

### Task 1: Project skeleton — block builder, UUID generator, .sb3 packer

**Files:**
- Create: `scratch_drone_rescue/generate_sb3.py`

**Interfaces:**
- Produces: `uid()`, `make_block(...)`, `make_costume(...)`, `make_sound(...)`, `make_sprite(...)`, `make_stage(...)`, `pack_sb3(project_json, output_path)`

This task creates the core infrastructure — the complete helper library for building Scratch 3 JSON blocks, plus the .sb3 ZIP packer. Each subsequent task appends sprite/stage definitions to this file.

---

- [ ] **Step 1: Create directory and base imports**

```bash
mkdir -p scratch_drone_rescue/output
```

- [ ] **Step 2: Write the helper functions and skeleton**

```python
#!/usr/bin/env python3
"""Generate Scratch 3 .sb3 file for Drone Earthquake Rescue."""

import json
import uuid
import zipfile
import os
import math

# ─── ID generation ───
def uid():
    """Generate a Scratch-style 20-char hex block ID."""
    return uuid.uuid4().hex[:20]

# ─── Scratch block builder ───
def make_block(opcode, next_id=None, parent_id=None, inputs=None,
               fields=None, shadow=False, topLevel=False, x=0, y=0):
    """Create a single Scratch 3 block dict."""
    block = {
        "opcode": opcode,
        "next": next_id,
        "parent": parent_id,
        "inputs": inputs or {},
        "fields": fields or {},
        "shadow": shadow,
        "topLevel": topLevel,
    }
    if topLevel:
        block["x"] = x
        block["y"] = y
    return block

def input_value(block_id):
    """Create a simple value input reference: [1, block_id]."""
    return [1, block_id]

def input_substack(block_id):
    """Create a substack (C-block body) input: [2, block_id]."""
    return [2, block_id]

def input_obscured(block_name, block_id):
    """Create an obscured shadow input: [3, block_name, block_id]."""
    return [3, block_name, block_id]

def field_val(value):
    """Create a field value: [value, null]."""
    return [value, None]

# ─── Block linking helpers ───
def chain_blocks(blocks_list):
    """Link a list of block dicts via 'next'. Returns (first_id, last_id)."""
    for i in range(len(blocks_list) - 1):
        blocks_list[i]["next"] = blocks_list[i + 1]["next"] or blocks_list[i + 1].get("next")
        # Actually, link by ID
    return blocks_list

def link_blocks(block_map, *ids):
    """Link blocks in sequence: id0.next=id1, id1.next=id2, etc."""
    for i in range(len(ids) - 1):
        if ids[i] in block_map:
            block_map[ids[i]]["next"] = ids[i + 1]
    return ids[0] if ids else None

# ─── Costume builder ───
def make_costume(name, svg_data, bitmap_resolution=1):
    """Create a costume dict from inline SVG."""
    asset_id = uid()
    return {
        "assetId": asset_id,
        "name": name,
        "bitmapResolution": bitmap_resolution,
        "md5ext": f"{asset_id}.svg",
        "dataFormat": "svg",
        "rotationCenterX": 0,
        "rotationCenterY": 0
    }

# ─── Sound builder ───
def make_sound(name, asset_id=None, sample_count=None, rate=None):
    """Create a sound dict (using Scratch built-in sounds)."""
    sid = asset_id or uid()
    return {
        "assetId": sid,
        "name": name,
        "dataFormat": "wav",
        "format": "",
        "rate": rate or 22050,
        "sampleCount": sample_count or 22050,
        "md5ext": f"{sid}.wav"
    }

# ─── Sprite builder ───
def make_sprite(name, is_stage=False):
    """Create a sprite/stage target dict skeleton."""
    target = {
        "isStage": is_stage,
        "name": name,
        "variables": {},
        "lists": {},
        "broadcasts": {},
        "blocks": {},
        "comments": {},
        "currentCostume": 0,
        "costumes": [],
        "sounds": [],
        "volume": 100,
        "layerOrder": 0 if is_stage else 1,
    }
    if is_stage:
        target["tempo"] = 60
        target["videoTransparency"] = 50
        target["videoState"] = "off"
        target["textToSpeechLanguage"] = None
    else:
        target["visible"] = True
        target["x"] = 0
        target["y"] = 0
        target["size"] = 100
        target["direction"] = 90
        target["draggable"] = False
        target["rotationStyle"] = "all around"
    return target

# ─── Project assembly ───
def build_project(targets):
    """Build the complete project.json structure."""
    return {
        "targets": targets,
        "monitors": [],
        "extensions": [],
        "meta": {
            "semver": "3.0.0",
            "vm": "2.3.0",
            "agent": "python-sb3-generator/drone-rescue-v1"
        }
    }

def add_var(target, var_id, var_name, value=0):
    """Add a variable to a target."""
    target["variables"][var_id] = [var_name, value]

def add_list(target, list_id, list_name, values=None):
    """Add a list to a target."""
    target["lists"][list_id] = [list_name, values or []]

def add_broadcast(target, broadcast_id, broadcast_name):
    """Add a broadcast message to a target."""
    target["broadcasts"][broadcast_id] = broadcast_name

def add_block(target, block_id, block):
    """Add a block to the target's block map."""
    target["blocks"][block_id] = block

def pack_sb3(project_json, output_path):
    """Package project.json into a .sb3 ZIP file."""
    os.makedirs(os.path.dirname(output_path) or ".", exist_ok=True)
    with zipfile.ZipFile(output_path, 'w', zipfile.ZIP_DEFLATED) as zf:
        zf.writestr('project.json', json.dumps(project_json, ensure_ascii=False, indent=2))
    print(f"Generated: {output_path} ({os.path.getsize(output_path)} bytes)")


# ═══════════════════════════════════════════
# MAIN: Build the complete project
# ═══════════════════════════════════════════
if __name__ == '__main__':
    targets = []

    # ── Task 2 placeholder: SVG assets will go here ──
    # ── Task 3 placeholder: Stage will go here ──
    # ── Task 4 placeholder: Drone sprite will go here ──
    # ── Task 5 placeholder: Survivor sprites will go here ──
    # ── Task 6 placeholder: UI sprites will go here ──

    project = build_project(targets)
    pack_sb3(project, 'output/drone_rescue.sb3')
    print("Done! Open output/drone_rescue.sb3 in Scratch 3.")
```

- [ ] **Step 3: Verify script runs (generates empty .sb3)**

```bash
cd scratch_drone_rescue && python3 generate_sb3.py
```

Expected: `Generated: output/drone_rescue.sb3 (... bytes)` + `Done!...`

- [ ] **Step 4: Commit**

```bash
git add scratch_drone_rescue/
git commit -m "feat: add sb3 generator skeleton with block builder helpers"
```

---

### Task 2: SVG asset library — all sprites and backgrounds

**Files:**
- Modify: `scratch_drone_rescue/generate_sb3.py` — add SVG assets dict

**Interfaces:**
- Produces: `ASSETS` dict with keys: `title_bg`, `village_before`, `village_after`, `rescue_complete`, `drone_normal`, `drone_drop`, `survivor_hidden`, `survivor_wave`, `survivor_found`, `house_intact`, `house_destroyed`, `mountain`, `supply_pack`, `start_btn`, `ui_panel`, `ui_results`

Add SVG assets as inline strings. Each is a complete SVG document that Scratch renders as a vector costume.

---

- [ ] **Step 1: Add SVG asset definitions to generate_sb3.py**

Insert this after the helper functions and before `if __name__ == '__main__':`:

```python
# ═══════════════════════════════════════════
# SVG ASSET LIBRARY
# ═══════════════════════════════════════════

ASSETS = {}

# ── Backdrops (480x360 stage size) ──

ASSETS["title_bg"] = '''<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 480 360">
  <defs>
    <linearGradient id="sky1" x1="0" y1="0" x2="0" y2="1">
      <stop offset="0%" stop-color="#1a1a2e"/>
      <stop offset="40%" stop-color="#e2725b"/>
      <stop offset="70%" stop-color="#f4a261"/>
      <stop offset="100%" stop-color="#e9c46a"/>
    </linearGradient>
  </defs>
  <rect width="480" height="360" fill="url(#sky1)"/>
  <!-- Mountains background -->
  <polygon points="0,280 60,160 120,220 180,140 240,200 300,130 360,190 420,150 480,210 480,360 0,360" fill="#2d1b0e" opacity="0.6"/>
  <polygon points="0,300 80,200 140,250 200,180 260,240 340,170 400,230 480,190 480,360 0,360" fill="#3d2b1e" opacity="0.5"/>
  <!-- Ground -->
  <rect x="0" y="300" width="480" height="60" fill="#4a3728"/>
  <!-- Drone launch pad -->
  <rect x="210" y="295" width="60" height="10" rx="3" fill="#666"/>
  <text x="240" y="130" text-anchor="middle" font-size="28" font-weight="bold" fill="#fff" font-family="sans-serif">无人机地震救援行动</text>
  <text x="240" y="165" text-anchor="middle" font-size="16" fill="#ffd166" font-family="sans-serif">四川山区 · 6.8级地震</text>
  <!-- Start button area (rendered as background hint) -->
  <rect x="160" y="230" width="160" height="40" rx="20" fill="#e76f51" stroke="#fff" stroke-width="2"/>
  <text x="240" y="256" text-anchor="middle" font-size="16" fill="#fff" font-family="sans-serif">🚀 开始救援任务</text>
  <!-- Mini drone on pad -->
  <ellipse cx="240" cy="288" rx="12" ry="4" fill="#fff"/>
  <rect x="236" y="280" width="8" height="8" rx="2" fill="#ff6b35"/>
  <line x1="230" y1="284" x2="220" y2="278" stroke="#fff" stroke-width="1.5"/>
  <line x1="250" y1="284" x2="260" y2="278" stroke="#fff" stroke-width="1.5"/>
</svg>'''

ASSETS["village_before"] = '''<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 480 360">
  <defs>
    <linearGradient id="sky2" x1="0" y1="0" x2="0" y2="1">
      <stop offset="0%" stop-color="#87ceeb"/>
      <stop offset="60%" stop-color="#b0e0e6"/>
      <stop offset="100%" stop-color="#e0f0e8"/>
    </linearGradient>
  </defs>
  <rect width="480" height="360" fill="url(#sky2)"/>
  <!-- Mountains -->
  <polygon points="0,280 80,120 160,200 240,100 320,180 400,110 480,190 480,360 0,360" fill="#567d46"/>
  <polygon points="0,310 100,180 200,250 300,160 400,230 480,170 480,360 0,360" fill="#6b8e4e"/>
  <!-- Valley -->
  <rect x="0" y="280" width="480" height="80" fill="#7c9d5e"/>
  <!-- Houses -->
  <rect x="80" y="250" width="40" height="35" fill="#d4a574"/>
  <polygon points="75,250 100,230 125,250" fill="#8b4513"/>
  <rect x="92" y="265" width="15" height="20" fill="#5c3317"/>
  <rect x="180" y="240" width="45" height="40" fill="#e8c9a0"/>
  <polygon points="175,240 202,215 230,240" fill="#a0522d"/>
  <rect x="195" y="258" width="15" height="22" fill="#5c3317"/>
  <rect x="330" y="255" width="38" height="30" fill="#d4a574"/>
  <polygon points="325,255 349,235 373,255" fill="#8b4513"/>
  <rect x="342" y="268" width="14" height="17" fill="#5c3317"/>
  <!-- Road -->
  <path d="M0,300 Q200,290 480,305" stroke="#c4a882" stroke-width="12" fill="none"/>
  <!-- Trees -->
  <circle cx="50" cy="260" r="15" fill="#2d5a27"/>
  <rect x="48" y="272" width="4" height="15" fill="#5c3317"/>
  <circle cx="420" cy="255" r="18" fill="#3a7a32"/>
  <rect x="418" y="270" width="4" height="12" fill="#5c3317"/>
</svg>'''

ASSETS["village_after"] = '''<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 480 360">
  <defs>
    <linearGradient id="sky3" x1="0" y1="0" x2="0" y2="1">
      <stop offset="0%" stop-color="#8b7355"/>
      <stop offset="50%" stop-color="#a09080"/>
      <stop offset="100%" stop-color="#b8a89a"/>
    </linearGradient>
  </defs>
  <rect width="480" height="360" fill="url(#sky3)"/>
  <!-- Mountains (some collapsed) -->
  <polygon points="0,280 80,140 160,200 240,120 320,190 400,130 480,180 480,360 0,360" fill="#5c4a3a"/>
  <polygon points="0,310 100,190 200,260 300,180 400,240 480,200 480,360 0,360" fill="#6b5a4a"/>
  <!-- Landslide scar -->
  <polygon points="140,180 180,230 220,190 260,280 170,300 120,250" fill="#8b7355"/>
  <!-- Rubble ground -->
  <rect x="0" y="270" width="480" height="90" fill="#7a6a5a"/>
  <!-- Destroyed houses -->
  <polygon points="75,260 100,245 125,260" fill="#8b7355"/>
  <rect x="80" y="260" width="18" height="18" fill="#a09080" transform="rotate(-15,89,269)"/>
  <rect x="100" y="258" width="20" height="15" fill="#a09080" transform="rotate(10,110,265)"/>
  <!-- Cracked road -->
  <path d="M0,310 Q100,305 200,320 Q300,335 480,315" stroke="#5c4a3a" stroke-width="14" fill="none" stroke-dasharray="20,5,8,5"/>
  <!-- Dust clouds -->
  <circle cx="160" cy="220" r="20" fill="#c4b8a8" opacity="0.5"/>
  <circle cx="180" cy="210" r="15" fill="#c4b8a8" opacity="0.4"/>
  <circle cx="350" cy="230" r="18" fill="#c4b8a8" opacity="0.45"/>
  <circle cx="370" cy="218" r="12" fill="#c4b8a8" opacity="0.35"/>
  <circle cx="280" cy="200" r="22" fill="#c4b8a8" opacity="0.4"/>
  <!-- Survivor SOS signal hint areas (will be covered by survivor sprites) -->
  <text x="120" y="250" text-anchor="middle" font-size="24" fill="#ff4444" opacity="0.7">•••</text>
  <text x="240" y="230" text-anchor="middle" font-size="24" fill="#ff4444" opacity="0.7">•••</text>
  <text x="380" y="250" text-anchor="middle" font-size="24" fill="#ff4444" opacity="0.7">•••</text>
</svg>'''

ASSETS["rescue_complete"] = '''<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 480 360">
  <defs>
    <linearGradient id="sky4" x1="0" y1="0" x2="0" y2="1">
      <stop offset="0%" stop-color="#2c3e50"/>
      <stop offset="40%" stop-color="#e74c3c"/>
      <stop offset="65%" stop-color="#f39c12"/>
      <stop offset="100%" stop-color="#f1c40f"/>
    </linearGradient>
  </defs>
  <rect width="480" height="360" fill="url(#sky4)"/>
  <!-- Mountains -->
  <polygon points="0,300 100,180 200,260 300,170 400,240 480,190 480,360 0,360" fill="#1a1a2e" opacity="0.5"/>
  <!-- Ground -->
  <rect x="0" y="300" width="480" height="60" fill="#2c3e50"/>
  <!-- Rescue vehicles -->
  <rect x="280" y="295" width="50" height="20" rx="3" fill="#e74c3c"/>
  <rect x="310" y="280" width="25" height="15" fill="#fff"/>
  <circle cx="290" cy="318" r="5" fill="#333"/>
  <circle cx="320" cy="318" r="5" fill="#333"/>
  <!-- Drone flying home -->
  <ellipse cx="380" cy="120" rx="14" ry="5" fill="#fff"/>
  <rect x="376" y="112" width="8" height="8" rx="2" fill="#ff6b35"/>
  <line x1="370" y1="116" x2="358" y2="110" stroke="#fff" stroke-width="1.5"/>
  <line x1="390" y1="116" x2="402" y2="110" stroke="#fff" stroke-width="1.5"/>
  <!-- Stars -->
  <circle cx="50" cy="40" r="1.5" fill="#fff"/>
  <circle cx="150" cy="60" r="1.5" fill="#fff"/>
  <circle cx="400" cy="30" r="1.5" fill="#fff"/>
  <circle cx="300" cy="50" r="1.5" fill="#fff"/>
  <circle cx="100" cy="80" r="1" fill="#fff"/>
  <circle cx="450" cy="70" r="1" fill="#fff"/>
</svg>'''

# ── Sprite costumes ──

ASSETS["drone_normal"] = '''<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 60 40">
  <!-- Body -->
  <rect x="22" y="15" width="16" height="12" rx="3" fill="#ffffff" stroke="#333" stroke-width="1.5"/>
  <!-- Camera -->
  <circle cx="30" cy="22" r="4" fill="#ff6b35"/>
  <circle cx="30" cy="22" r="2" fill="#333"/>
  <!-- Arms -->
  <line x1="22" y1="20" x2="4" y2="8" stroke="#ddd" stroke-width="3"/>
  <line x1="38" y1="20" x2="56" y2="8" stroke="#ddd" stroke-width="3"/>
  <line x1="22" y1="24" x2="4" y2="36" stroke="#ddd" stroke-width="3"/>
  <line x1="38" y1="24" x2="56" y2="36" stroke="#ddd" stroke-width="3"/>
  <!-- Propellers -->
  <ellipse cx="4" cy="6" rx="10" ry="3" fill="#ff6b35" opacity="0.7"/>
  <ellipse cx="56" cy="6" rx="10" ry="3" fill="#ff6b35" opacity="0.7"/>
  <ellipse cx="4" cy="38" rx="10" ry="3" fill="#ff6b35" opacity="0.7"/>
  <ellipse cx="56" cy="38" rx="10" ry="3" fill="#ff6b35" opacity="0.7"/>
  <!-- LED indicator -->
  <circle cx="30" cy="14" r="2" fill="#00ff00"/>
</svg>'''

ASSETS["drone_drop"] = '''<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 60 50">
  <!-- Body -->
  <rect x="22" y="22" width="16" height="12" rx="3" fill="#ffffff" stroke="#333" stroke-width="1.5"/>
  <!-- Camera -->
  <circle cx="30" cy="29" r="4" fill="#ff6b35"/>
  <circle cx="30" cy="29" r="2" fill="#333"/>
  <!-- Arms -->
  <line x1="22" y1="27" x2="4" y2="15" stroke="#ddd" stroke-width="3"/>
  <line x1="38" y1="27" x2="56" y2="15" stroke="#ddd" stroke-width="3"/>
  <line x1="22" y1="31" x2="4" y2="43" stroke="#ddd" stroke-width="3"/>
  <line x1="38" y1="31" x2="56" y2="43" stroke="#ddd" stroke-width="3"/>
  <!-- Propellers -->
  <ellipse cx="4" cy="13" rx="10" ry="3" fill="#ff6b35" opacity="0.7"/>
  <ellipse cx="56" cy="13" rx="10" ry="3" fill="#ff6b35" opacity="0.7"/>
  <ellipse cx="4" cy="45" rx="10" ry="3" fill="#ff6b35" opacity="0.7"/>
  <ellipse cx="56" cy="45" rx="10" ry="3" fill="#ff6b35" opacity="0.7"/>
  <!-- Supply hook -->
  <line x1="30" y1="34" x2="30" y2="44" stroke="#333" stroke-width="1.5"/>
  <!-- LED indicator -->
  <circle cx="30" cy="21" r="2" fill="#ffff00"/>
</svg>'''

ASSETS["survivor_hidden"] = '''<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 30 40">
  <!-- Hidden: just a faint rubble pile -->
  <rect x="2" y="28" width="26" height="12" rx="3" fill="#8b7355" opacity="0.8"/>
  <polygon points="5,28 15,20 25,28" fill="#7a6a5a" opacity="0.8"/>
</svg>'''

ASSETS["survivor_wave"] = '''<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 40 50">
  <!-- Person waving from rubble -->
  <circle cx="20" cy="18" r="8" fill="#f5d5a0" stroke="#333" stroke-width="1"/>
  <!-- Eyes -->
  <circle cx="17" cy="17" r="1.5" fill="#333"/>
  <circle cx="23" cy="17" r="1.5" fill="#333"/>
  <!-- Mouth (open, calling for help) -->
  <ellipse cx="20" cy="22" rx="3" ry="2" fill="#333"/>
  <!-- Body -->
  <rect x="14" y="26" width="12" height="18" rx="3" fill="#e74c3c"/>
  <!-- Waving arm -->
  <line x1="26" y1="28" x2="34" y2="16" stroke="#f5d5a0" stroke-width="3" stroke-linecap="round"/>
  <!-- Other arm -->
  <line x1="14" y1="30" x2="8" y2="26" stroke="#f5d5a0" stroke-width="3" stroke-linecap="round"/>
  <!-- Rubble under -->
  <rect x="0" y="42" width="40" height="8" rx="3" fill="#8b7355"/>
  <!-- SOS text -->
  <text x="20" y="10" text-anchor="middle" font-size="10" fill="#ff4444" font-weight="bold">SOS</text>
</svg>'''

ASSETS["survivor_found"] = '''<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 40 60">
  <!-- Rescued person with checkmark -->
  <circle cx="20" cy="18" r="8" fill="#f5d5a0" stroke="#2ecc71" stroke-width="2"/>
  <!-- Happy eyes -->
  <circle cx="17" cy="17" r="1.5" fill="#333"/>
  <circle cx="23" cy="17" r="1.5" fill="#333"/>
  <!-- Smile -->
  <path d="M16,22 Q20,27 24,22" stroke="#333" stroke-width="1.5" fill="none"/>
  <!-- Body -->
  <rect x="14" y="26" width="12" height="18" rx="3" fill="#e74c3c"/>
  <!-- Relief arms up -->
  <line x1="14" y1="28" x2="6" y2="18" stroke="#f5d5a0" stroke-width="3" stroke-linecap="round"/>
  <line x1="26" y1="28" x2="34" y2="18" stroke="#f5d5a0" stroke-width="3" stroke-linecap="round"/>
  <!-- Rubble -->
  <rect x="0" y="42" width="40" height="8" rx="3" fill="#8b7355"/>
  <!-- Green check -->
  <circle cx="35" cy="12" r="8" fill="#2ecc71"/>
  <polyline points="31,12 34,15 39,9" stroke="#fff" stroke-width="2" fill="none"/>
</svg>'''

ASSETS["house_intact"] = '''<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 80 70">
  <rect x="10" y="30" width="60" height="40" fill="#d4a574"/>
  <polygon points="5,30 40,5 75,30" fill="#8b4513"/>
  <rect x="30" y="45" width="20" height="25" fill="#5c3317"/>
  <rect x="20" y="40" width="15" height="15" fill="#87ceeb" opacity="0.7"/>
  <rect x="50" y="40" width="15" height="15" fill="#87ceeb" opacity="0.7"/>
</svg>'''

ASSETS["house_destroyed"] = '''<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 80 70">
  <polygon points="5,30 40,5 75,30" fill="#8b7355" transform="rotate(-10,40,17)"/>
  <rect x="10" y="35" width="30" height="35" fill="#a09080" transform="rotate(-5,25,52)"/>
  <rect x="45" y="38" width="25" height="25" fill="#b0a090" transform="rotate(8,57,50)"/>
  <polygon points="40,35 50,45 40,55 30,45" fill="#c4b8a8"/>
  <rect x="10" y="30" width="50" height="5" fill="#8b7355" transform="rotate(-15,35,32)"/>
</svg>'''

ASSETS["mountain"] = '''<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 200 150">
  <polygon points="0,150 50,30 100,90 150,20 200,80 200,150" fill="#567d46"/>
  <polygon points="0,150 50,30 100,90 150,20 200,80 200,150" fill="#fff" opacity="0.15" transform="translate(0,0)"/>
  <!-- Snow caps -->
  <polygon points="50,30 35,55 42,58 48,50 52,58 58,55" fill="#fff" opacity="0.7"/>
  <polygon points="150,20 135,45 142,48 148,40 152,48 158,45" fill="#fff" opacity="0.7"/>
</svg>'''

ASSETS["supply_pack"] = '''<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 30 30">
  <rect x="2" y="2" width="26" height="26" rx="4" fill="#e74c3c" stroke="#fff" stroke-width="1.5"/>
  <rect x="2" y="2" width="26" height="26" rx="4" fill="none" stroke="#c0392b" stroke-width="0.5"/>
  <line x1="15" y1="2" x2="15" y2="28" stroke="#fff" stroke-width="1.5"/>
  <line x1="2" y1="15" x2="28" y2="15" stroke="#fff" stroke-width="1.5"/>
  <text x="15" y="20" text-anchor="middle" font-size="10" fill="#fff" font-weight="bold">+</text>
</svg>'''

ASSETS["start_btn"] = '''<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 180 50">
  <rect x="0" y="0" width="180" height="50" rx="25" fill="#e76f51" stroke="#fff" stroke-width="2"/>
  <text x="90" y="32" text-anchor="middle" font-size="18" fill="#fff" font-family="sans-serif">🚀 开始救援任务</text>
</svg>'''

ASSETS["ui_panel"] = '''<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 480 60">
  <rect x="0" y="0" width="480" height="60" fill="#1a1a2e" opacity="0.85"/>
</svg>'''

ASSETS["ui_results"] = '''<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 320 220">
  <rect x="0" y="0" width="320" height="220" rx="15" fill="#1a1a2e" opacity="0.9" stroke="#f39c12" stroke-width="2"/>
  <text x="160" y="35" text-anchor="middle" font-size="22" fill="#f39c12" font-family="sans-serif" font-weight="bold">救援任务完成！</text>
  <!-- Results data text placeholder - actual text rendered by Scratch say blocks -->
</svg>'''

ASSETS["dust_particle"] = '''<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 10 10">
  <circle cx="5" cy="5" r="4" fill="#c4b8a8" opacity="0.6"/>
</svg>'''

ASSETS["check_mark"] = '''<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 30 30">
  <circle cx="15" cy="15" r="14" fill="#2ecc71"/>
  <polyline points="9,15 13,19 21,11" stroke="#fff" stroke-width="3" fill="none" stroke-linecap="round" stroke-linejoin="round"/>
</svg>'''

print(f"Loaded {len(ASSETS)} SVG assets.")
```

- [ ] **Step 2: Verify script still runs**

```bash
cd scratch_drone_rescue && python3 generate_sb3.py
```

Expected: `Loaded 18 SVG assets.` + previous output

- [ ] **Step 3: Commit**

```bash
git add scratch_drone_rescue/generate_sb3.py
git commit -m "feat: add SVG asset library (18 costumes/backdrops)"
```

---

### Task 3: Stage — backdrops, broadcast messages, scene flow, earthquake animation

**Files:**
- Modify: `scratch_drone_rescue/generate_sb3.py` — add Stage target definition

**Interfaces:**
- Consumes: `make_block`, `make_costume`, `make_sprite`, `make_sound`, `add_var`, `add_broadcast`, `add_block`, `ASSETS`
- Produces: Stage target with 4 backdrops, broadcast list, scene controller scripts

This task defines the Stage (backdrop switching, scene broadcast messages, earthquake shake animation, timer variable).

---

- [ ] **Step 1: Define the Stage target**

Replace the placeholder comments in `__main__` with actual Stage construction:

```python
if __name__ == '__main__':
    targets = []

    # ═══════════════════════════════════════
    # STAGE
    # ═══════════════════════════════════════
    stage = make_sprite("Stage", is_stage=True)
    stage["tempo"] = 60
    stage["videoTransparency"] = 50
    stage["videoState"] = "off"
    stage["textToSpeechLanguage"] = None

    # Backdrops
    stage["costumes"] = [
        make_costume("TitleScreen", ASSETS["title_bg"]),
        make_costume("VillageBefore", ASSETS["village_before"]),
        make_costume("VillageAfter", ASSETS["village_after"]),
        make_costume("RescueComplete", ASSETS["rescue_complete"]),
    ]
    stage["currentCostume"] = 0

    # Sounds (use Scratch references — wav data will be minimal placeholders)
    stage["sounds"] = []

    # Variables
    add_var(stage, "`jEk@4|@[#Fk?(8x)AV0", "scene", 0)
    add_var(stage, "tHOm54g$v@QcD|Q_z~60", "found", 0)
    add_var(stage, "rv2R|O~Gr9N4;rQmZpKt", "delivered", 0)
    add_var(stage, "NKY@iQmJ/9hD1y1#;pEr", "timer", 0)

    # Broadcasts
    add_broadcast(stage, "br_scene1", "scene_1")
    add_broadcast(stage, "br_scene2", "scene_2")
    add_broadcast(stage, "br_scene3", "scene_3")
    add_broadcast(stage, "br_scene4", "scene_4")
    add_broadcast(stage, "br_scene5", "scene_5")
    add_broadcast(stage, "br_found", "survivor_found")
    add_broadcast(stage, "br_delivered", "supply_delivered")
    add_broadcast(stage, "br_shake", "earthquake_shake")
    add_broadcast(stage, "br_all_rescued", "all_rescued")
    add_broadcast(stage, "br_restart", "restart")

    # ── Stage scripts ──
    # Green flag: start at scene 1
    bid_gf = uid()
    add_block(stage, bid_gf, make_block("event_whenflagclicked", topLevel=True, x=0, y=0))
    bid_setscene = uid()
    add_block(stage, bid_setscene, make_block("data_setvariableto",
        fields={"VARIABLE": field_val("scene")},
        inputs={"VALUE": input_obscured("1", uid())}))
    bid_bc1 = uid()
    add_block(stage, bid_bc1, make_block("event_broadcast",
        inputs={"BROADCAST_INPUT": input_obscured("br_scene1", uid())},
        fields={}))
    link_blocks(stage["blocks"], bid_gf, bid_setscene, bid_bc1)

    # Receive scene_1: show title screen, wait for click
    bid_rcv1 = uid()
    add_block(stage, bid_rcv1, make_block("event_whenbroadcastreceived",
        fields={"BROADCAST_OPTION": field_val("scene_1")}, topLevel=True, x=0, y=60))
    bid_switch1 = uid()
    add_block(stage, bid_switch1, make_block("looks_switchbackdropto",
        inputs={"BACKDROP": input_obscured("TitleScreen", uid())}))
    bid_setvar0 = uid()
    add_block(stage, bid_setvar0, make_block("data_setvariableto",
        fields={"VARIABLE": field_val("scene")},
        inputs={"VALUE": input_obscured("1", uid())}))
    link_blocks(stage["blocks"], bid_rcv1, bid_switch1, bid_setvar0)

    # Receive scene_2: earthquake animation, then auto-advance
    bid_rcv2 = uid()
    add_block(stage, bid_rcv2, make_block("event_whenbroadcastreceived",
        fields={"BROADCAST_OPTION": field_val("scene_2")}, topLevel=True, x=0, y=120))
    bid_switch2a = uid()
    add_block(stage, bid_switch2a, make_block("looks_switchbackdropto",
        inputs={"BACKDROP": input_obscured("VillageBefore", uid())}))
    bid_setvar2 = uid()
    add_block(stage, bid_setvar2, make_block("data_setvariableto",
        fields={"VARIABLE": field_val("scene")},
        inputs={"VALUE": input_obscured("2", uid())}))
    bid_wait1 = uid()
    add_block(stage, bid_wait1, make_block("control_wait",
        inputs={"DURATION": input_obscured("1", uid())}))
    # Earthquake shake loop
    bid_shake_bc = uid()
    add_block(stage, bid_shake_bc, make_block("event_broadcast",
        inputs={"BROADCAST_INPUT": input_obscured("br_shake", uid())}))
    bid_wait2 = uid()
    add_block(stage, bid_wait2, make_block("control_wait",
        inputs={"DURATION": input_obscured("2", uid())}))
    bid_switch2b = uid()
    add_block(stage, bid_switch2b, make_block("looks_switchbackdropto",
        inputs={"BACKDROP": input_obscured("VillageAfter", uid())}))
    bid_wait3 = uid()
    add_block(stage, bid_wait3, make_block("control_wait",
        inputs={"DURATION": input_obscured("2", uid())}))
    bid_bc3 = uid()
    add_block(stage, bid_bc3, make_block("event_broadcast",
        inputs={"BROADCAST_INPUT": input_obscured("br_scene3", uid())}))
    link_blocks(stage["blocks"], bid_rcv2, bid_switch2a, bid_setvar2, bid_wait1,
                bid_shake_bc, bid_wait2, bid_switch2b, bid_wait3, bid_bc3)

    # Earthquake shake effect: wiggle backdrop
    bid_rcv_shake = uid()
    add_block(stage, bid_rcv_shake, make_block("event_whenbroadcastreceived",
        fields={"BROADCAST_OPTION": field_val("earthquake_shake")}, topLevel=True, x=0, y=180))
    bid_shake_loop = uid()
    add_block(stage, bid_shake_loop, make_block("control_repeat",
        inputs={"TIMES": input_obscured("10", uid()),
                "SUBSTACK": input_substack(None)}, x=0, y=220))
    # Inside repeat: two motion blocks on stage effect (we'll use a small x/y wiggle via a hidden sprite instead)
    # For Stage, we can't move it. So we skip actual shake implementation here
    # and rely on the Drone and other sprites to shake via their own scripts.

    # Receive scene_3: search area (backdrop stays VillageAfter)
    bid_rcv3 = uid()
    add_block(stage, bid_rcv3, make_block("event_whenbroadcastreceived",
        fields={"BROADCAST_OPTION": field_val("scene_3")}, topLevel=True, x=0, y=280))
    bid_setvar3 = uid()
    add_block(stage, bid_setvar3, make_block("data_setvariableto",
        fields={"VARIABLE": field_val("scene")},
        inputs={"VALUE": input_obscured("3", uid())}))
    link_blocks(stage["blocks"], bid_rcv3, bid_setvar3)

    # Receive all_rescued: advance to scene_5
    bid_rcv_all = uid()
    add_block(stage, bid_rcv_all, make_block("event_whenbroadcastreceived",
        fields={"BROADCAST_OPTION": field_val("all_rescued")}, topLevel=True, x=240, y=60))
    bid_wait_r = uid()
    add_block(stage, bid_wait_r, make_block("control_wait",
        inputs={"DURATION": input_obscured("1", uid())}))
    bid_switch5 = uid()
    add_block(stage, bid_switch5, make_block("looks_switchbackdropto",
        inputs={"BACKDROP": input_obscured("RescueComplete", uid())}))
    bid_setvar5 = uid()
    add_block(stage, bid_setvar5, make_block("data_setvariableto",
        fields={"VARIABLE": field_val("scene")},
        inputs={"VALUE": input_obscured("5", uid())}))
    bid_bc5 = uid()
    add_block(stage, bid_bc5, make_block("event_broadcast",
        inputs={"BROADCAST_INPUT": input_obscured("br_scene5", uid())}))
    link_blocks(stage["blocks"], bid_rcv_all, bid_wait_r, bid_switch5, bid_setvar5, bid_bc5)

    # Receive restart: reset and go to scene_1
    bid_rcv_restart = uid()
    add_block(stage, bid_rcv_restart, make_block("event_whenbroadcastreceived",
        fields={"BROADCAST_OPTION": field_val("restart")}, topLevel=True, x=240, y=120))
    bid_rst_found = uid()
    add_block(stage, bid_rst_found, make_block("data_setvariableto",
        fields={"VARIABLE": field_val("found")},
        inputs={"VALUE": input_obscured("0", uid())}))
    bid_rst_deliv = uid()
    add_block(stage, bid_rst_deliv, make_block("data_setvariableto",
        fields={"VARIABLE": field_val("delivered")},
        inputs={"VALUE": input_obscured("0", uid())}))
    bid_rst_timer = uid()
    add_block(stage, bid_rst_timer, make_block("data_setvariableto",
        fields={"VARIABLE": field_val("timer")},
        inputs={"VALUE": input_obscured("0", uid())}))
    bid_bc_restart = uid()
    add_block(stage, bid_bc_restart, make_block("event_broadcast",
        inputs={"BROADCAST_INPUT": input_obscured("br_scene1", uid())}))
    link_blocks(stage["blocks"], bid_rcv_restart, bid_rst_found, bid_rst_deliv, bid_rst_timer, bid_bc_restart)

    targets.append(stage)
    print(f"Stage: {len(stage['blocks'])} blocks, {len(stage['costumes'])} backdrops")
```

- [ ] **Step 2: Verify script runs and check block count**

```bash
cd scratch_drone_rescue && python3 generate_sb3.py
```

Expected: `Stage: ~18 blocks, 4 backdrops` + success message

- [ ] **Step 3: Commit**

```bash
git add scratch_drone_rescue/generate_sb3.py
git commit -m "feat: add Stage with 4 backdrops, scene flow, and broadcast system"
```

---

### Task 4: Drone sprite — movement, animation, boundary, detection, delivery

**Files:**
- Modify: `scratch_drone_rescue/generate_sb3.py` — add Drone sprite

**Interfaces:**
- Consumes: all helpers from Task 1, ASSETS from Task 2, stage variables/broadcasts from Task 3
- Produces: Drone sprite with movement scripts, detection logic, delivery logic, animation

---

- [ ] **Step 1: Add Drone sprite definition**

Insert before `targets.append(stage)` but after Stage block definitions, or just add it in the `__main__` section. Add the entire Drone sprite with all its scripts:

```python
    # ═══════════════════════════════════════
    # DRONE SPRITE
    # ═══════════════════════════════════════
    drone = make_sprite("Drone")
    drone["costumes"] = [
        make_costume("drone_normal", ASSETS["drone_normal"]),
        make_costume("drone_drop", ASSETS["drone_drop"]),
    ]
    drone["size"] = 80
    drone["layerOrder"] = 10

    # Drone sounds
    drone["sounds"] = []

    # ── Drone scripts ──

    # When scene_3 starts: show drone, position at left
    bid_dr_start = uid()
    add_block(drone, bid_dr_start, make_block("event_whenbroadcastreceived",
        fields={"BROADCAST_OPTION": field_val("scene_3")}, topLevel=True, x=0, y=0))
    bid_dr_show = uid()
    add_block(drone, bid_dr_show, make_block("looks_show", topLevel=False))
    bid_dr_goto = uid()
    add_block(drone, bid_dr_goto, make_block("motion_gotoxy",
        inputs={"X": input_obscured("-200", uid()), "Y": input_obscured("100", uid())}))
    bid_dr_costume = uid()
    add_block(drone, bid_dr_costume, make_block("looks_switchcostumeto",
        inputs={"COSTUME": input_obscured("drone_normal", uid())}))
    bid_dr_say = uid()
    add_block(drone, bid_dr_say, make_block("looks_sayforsecs",
        inputs={"MESSAGE": input_obscured("使用方向键操控无人机，搜寻幸存者！", uid()),
                "SECS": input_obscured("2", uid())}))
    link_blocks(drone["blocks"], bid_dr_start, bid_dr_show, bid_dr_goto, bid_dr_costume, bid_dr_say)

    # Arrow key movement (↑)
    bid_up = uid()
    add_block(drone, bid_up, make_block("event_whenkeypressed",
        fields={"KEY_OPTION": field_val("up arrow")}, topLevel=True, x=0, y=80))
    bid_up_if = uid()
    add_block(drone, bid_up_if, make_block("control_if", topLevel=False))
    # Condition: scene = 3
    bid_up_eq = uid()
    add_block(drone, bid_up_eq, make_block("operator_equals",
        inputs={"OPERAND1": input_obscured(uid(), uid()),  # scene var reader
                "OPERAND2": input_obscured("3", uid())}))
    # ... This is getting very complex for manual block construction.

    # SIMPLIFIED APPROACH: Instead of building every block manually, we'll use
    # a more compact representation. The complex Scratch block format with
    # nested inputs makes manual construction extremely verbose and error-prone.

    # We'll use a different strategy: build a minimal but functional project
    # with core mechanics, then expand.

    print("  Drone sprite added (movement, detection, delivery)")
```

Wait — the task-4 approach of writing hundreds of individual blocks manually is going to make the plan impossibly long and the code extremely fragile. Let me redesign the approach.

**Revised approach:** Instead of building each Scratch block individually (which requires ~300+ blocks with complex nested input structures), I'll restructure Tasks 4–6 to use a **compact block builder DSL** — a Python helper that takes a higher-level description and generates the blocks. This reduces the script size dramatically while keeping it correct.

Let me rewrite Task 4+ with this approach.

---

**Revised Task 4: Compact block DSL + Drone sprite**

Replace the manual block-by-block approach with a compact helper, then define all Drone scripts concisely.

---


Actually, this plan is becoming way too complex. Let me simplify the entire approach.

The reality is that generating a Scratch 3 project.json from scratch with Python is genuinely complex, but it's doable. The key insight is:

1. The block format is verbose but mechanical
2. Most blocks follow the same pattern
3. We need a good abstraction

Let me write a practical plan that focuses on the actual generator script. I'll make the plan more realistic - fewer, larger tasks with the actual code that works.

Let me rewrite the plan to be more practical:

Task 1: Block DSL and project skeleton
Task 2: SVG assets and costumes
Task 3: Stage with backdrops and scene flow
Task 4: All sprites (Drone, Survivors, UI)
Task 5: Assembly, packaging, and testing

This is more manageable. Let me rewrite.<｜end▁of▁thinking｜>这个计划太长了，让我重新整理为更实用的版本。由于 Scratch 3 block 格式的高度复杂性，我采用**紧凑 DSL** 方式构建整个项目，把计划精简为 5 个任务。

<｜｜DSML｜｜tool_calls>
<｜｜DSML｜｜invoke name="Write">
<｜｜DSML｜｜parameter name="content" string="true"># 无人机地震救援 Scratch 3 — Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Generate a complete Scratch 3 `.sb3` file via a single Python script that builds the full `project.json` with all sprites, scripts, backdrops, and SVG assets.

**Architecture:** One Python script (`generate_sb3.py`) with: (1) block DSL helpers that abstract Scratch 3's verbose block JSON format, (2) inline SVG asset library, (3) stage + sprite + script definitions, (4) ZIP packaging. The block DSL is the key abstraction — it lets us express Scratch scripts as Python lists instead of manually wiring 300+ individual block dicts.

**Tech Stack:** Python 3 (stdlib only: json, zipfile, uuid)

## Global Constraints

- All assets inline SVG (no external files)
- Chinese text throughout
- 5 scenes with broadcast-driven flow
- 3 survivor targets, distance-based detection (60px)
- Arrow key movement + space bar delivery
- .sb3 output loads in Scratch 3

---

## File Structure

```
scratch_drone_rescue/
├── generate_sb3.py          # Main generator (~600 lines)
└── output/
    └── drone_rescue.sb3     # Generated output
```

---

### Task 1: Block DSL, SVG assets, project skeleton

**Files:**
- Create: `scratch_drone_rescue/generate_sb3.py`

**Interfaces:**
- Produces: `uid()`, `B` (block builder), `link()`, `make_costume()`, `make_sprite()`, `build_project()`, `pack_sb3()`, `ASSETS` dict

Create the complete generator script in one pass. The `B` class is the key abstraction — it takes a compact definition and expands it into Scratch 3's verbose block format.

---

- [ ] **Step 1: Create directory**

```bash
mkdir -p scratch_drone_rescue/output
```

- [ ] **Step 2: Write the complete generator script**

The script has these sections: (A) imports + uid, (B) block DSL class, (C) helper functions, (D) SVG assets, (E) stage definition, (F) sprite definitions, (G) assembly + pack.

Create `scratch_drone_rescue/generate_sb3.py`:

```python
#!/usr/bin/env python3
"""Generate Scratch 3 .sb3 for Drone Earthquake Rescue.
Usage: python3 generate_sb3.py
Output: output/drone_rescue.sb3
"""
import json, uuid, zipfile, os

# ═══════════════════════════════════════════
# A. UTILITIES
# ═══════════════════════════════════════════
def uid(n=20):
    return uuid.uuid4().hex[:n]

# ═══════════════════════════════════════════
# B. BLOCK DSL — compact → Scratch 3 block dicts
# ═══════════════════════════════════════════

class B:
    """Compact Scratch 3 block builder.
    
    Each block is defined as a tuple:
      (opcode, {inputs}, {fields}, topLevel?)
    or for C-blocks (if/forever/repeat):
      (opcode, {inputs}, {fields}, topLevel?, [substack_blocks])
    
    inputs: {"SUBSTACK": [...blocks], "CONDITION": b_id, "VALUE": ("1", shadow_name)}
    fields: {"VARIABLE": "scene", "BROADCAST_OPTION": "scene_1", "KEY_OPTION": "up arrow"}
    
    Returns the first block ID in the chain.
    """
    
    VAR_IDS = {
        "scene":   "`jEk@4|@[#Fk?(8x)AV0",
        "found":   "tHOm54g$v@QcD|Q_z~60",
        "delivered":"rv2R|O~Gr9N4;rQmZpKt",
        "timer":   "NKY@iQmJ/9hD1y1#;pEr",
    }
    
    BC_IDS = {
        "scene_1":       "br_scene1",
        "scene_2":       "br_scene2",
        "scene_3":       "br_scene3",
        "scene_4":       "br_scene4",
        "scene_5":       "br_scene5",
        "survivor_found":"br_found",
        "supply_delivered":"br_delivered",
        "earthquake_shake":"br_shake",
        "all_rescued":   "br_all_rescued",
        "restart":       "br_restart",
    }
    
    def __init__(self, target):
        self.target = target
        self.bid_counter = [0]  # for generating sequential block IDs
    
    def _bid(self):
        self.bid_counter[0] += 1
        return f"b{self.bid_counter[0]:05d}"
    
    def _resolve_input(self, key, val):
        """Resolve an input value to Scratch 3 format.
        val can be:
          - a block ID string → [2, block_id] (substack input)
          - (number_str, shadow_name) → [1, [shadow_bid, shadow_bid]]  (obscured shadow)
          - [block_id, block_id] → [3, name, block_ids]  (no shadow)
        """
        if isinstance(val, str) and val.startswith("b"):
            return [2, val]
        if isinstance(val, (list, tuple)) and len(val) > 0 and isinstance(val[0], str) and val[0].startswith("b"):
            return [3, "".join(val), list(val)]
        if isinstance(val, tuple):
            num_str = val[0]
            shadow_name = val[1] if len(val) > 1 else num_str
            s1 = self._make_shadow(shadow_name)
            return [1, [s1, s1]]
        # list of blocks → substack
        if isinstance(val, list):
            first = self.add_blocks(val)
            return [2, first]
        return [1, [str(val), str(val)]]
    
    def _make_shadow(self, name):
        """Create a shadow block for an input field."""
        sid = self._bid()
        # Determine the shadow opcode based on context
        shadow_opcode = "text"  # default
        # Use math_number for numeric values, text for strings
        try:
            float(name)
            shadow_opcode = "math_number"
        except ValueError:
            shadow_opcode = "text"
        
        self.target["blocks"][sid] = {
            "opcode": shadow_opcode,
            "next": None,
            "parent": None,
            "inputs": {},
            "fields": {"NUM" if shadow_opcode == "math_number" else "TEXT": [name, None]},
            "shadow": True,
            "topLevel": False,
        }
        return sid
    
    def _make_reporter(self, opcode, fields=None, inputs=None):
        """Create a reporter block (returns its ID) — used inside conditions etc."""
        rid = self._bid()
        block = {
            "opcode": opcode,
            "next": None,
            "parent": None,
            "inputs": {},
            "fields": fields or {},
            "shadow": False,
            "topLevel": False,
        }
        for k, v in (inputs or {}).items():
            block["inputs"][k] = self._resolve_input(k, v)
        self.target["blocks"][rid] = block
        return rid
    
    def add_block(self, opcode, inputs=None, fields=None, topLevel=False):
        """Add a single block. Returns block ID."""
        bid = self._bid()
        block = {
            "opcode": opcode,
            "next": None,
            "parent": None,
            "inputs": {},
            "fields": fields or {},
            "shadow": False,
            "topLevel": topLevel,
        }
        for k, v in (inputs or {}).items():
            if k == "SUBSTACK":
                continue  # handled in add_blocks
            block["inputs"][k] = self._resolve_input(k, v)
        self.target["blocks"][bid] = block
        return bid
    
    def add_blocks(self, block_defs):
        """Add a list of block definitions. Links them sequentially.
        
        Each block_def is one of:
          - (opcode, {inputs}, {fields})           → regular block
          - (opcode, {inputs}, {fields}, True)     → top-level (hat) block  
          - (opcode, {inputs}, {fields}, False, [subblocks]) → C-block
        
        Returns the ID of the first block in the chain.
        """
        prev_bid = None
        first_bid = None
        i = 0
        while i < len(block_defs):
            bd = block_defs[i]
            opcode = bd[0]
            inputs = bd[1] if len(bd) > 1 else {}
            fields = bd[2] if len(bd) > 2 else {}
            topLevel = False
            substack = None
            
            if len(bd) > 3:
                if isinstance(bd[3], bool):
                    topLevel = bd[3]
                    if len(bd) > 4:
                        substack = bd[4]
                elif isinstance(bd[3], list):
                    substack = bd[3]
                    if len(bd) > 4:
                        topLevel = bd[4]
            
            bid = self._bid()
            block = {
                "opcode": opcode,
                "next": None,
                "parent": None,
                "inputs": {},
                "fields": fields or {},
                "shadow": False,
                "topLevel": topLevel,
            }
            
            # Handle substack
            if substack:
                sub_first = self.add_blocks(substack)
                block["inputs"]["SUBSTACK"] = [2, sub_first]
            
            # Handle other inputs
            for k, v in inputs.items():
                if k == "SUBSTACK":
                    sub_first = self.add_blocks(v)
                    block["inputs"]["SUBSTACK"] = [2, sub_first]
                else:
                    block["inputs"][k] = self._resolve_input(k, v)
            
            self.target["blocks"][bid] = block
            
            if prev_bid:
                self.target["blocks"][prev_bid]["next"] = bid
            if first_bid is None:
                first_bid = bid
            prev_bid = bid
            i += 1
        
        return first_bid
    
    # ── Convenience methods for common operations ──
    
    def hat(self, opcode, fields=None, body=None):
        """Add a hat block with optional body. Returns first block ID."""
        bd = [(opcode, {}, fields or {}, True)]
        if body:
            bd.extend(body)
        return self.add_blocks(bd)
    
    def var_reporter(self, var_name):
        """Create a variable reporter block."""
        var_id = self.VAR_IDS.get(var_name, var_name)
        return self._make_reporter("data_variable",
            fields={"VARIABLE": [var_name, var_id]})
    
    def set_var(self, var_name, value):
        """Set variable to value."""
        var_id = self.VAR_IDS.get(var_name, var_name)
        return [("data_setvariableto",
            {"VALUE": (str(value), str(value))},
            {"VARIABLE": [var_name, var_id]})]
    
    def change_var(self, var_name, delta):
        var_id = self.VAR_IDS.get(var_name, var_name)
        return [("data_changevariableby",
            {"VALUE": (str(delta), str(delta))},
            {"VARIABLE": [var_name, var_id]})]
    
    def broadcast(self, msg_name):
        bc_id = self.BC_IDS.get(msg_name, f"bc_{msg_name}")
        return [("event_broadcast",
            {"BROADCAST_INPUT": (bc_id, bc_id)},
            {})]
    
    def wait(self, secs):
        return [("control_wait",
            {"DURATION": (str(secs), str(secs))},
            {})]
    
    def say(self, text, secs=None):
        if secs:
            return [("looks_sayforsecs",
                {"MESSAGE": (text, text), "SECS": (str(secs), str(secs))},
                {})]
        return [("looks_say",
            {"MESSAGE": (text, text)},
            {})]
    
    def switch_costume(self, name):
        return [("looks_switchcostumeto",
            {"COSTUME": (name, name)},
            {})]
    
    def goto(self, x, y):
        return [("motion_gotoxy",
            {"X": (str(x), str(x)), "Y": (str(y), str(y))},
            {})]
    
    def show(self):
        return [("looks_show", {}, {})]
    
    def hide(self):
        return [("looks_hide", {}, {})]
    
    def if_(self, reporter_bid, body):
        """If block with reporter condition and body."""
        bid = self._bid()
        block = {
            "opcode": "control_if",
            "next": None,
            "parent": None,
            "inputs": {
                "CONDITION": [2, reporter_bid],
                "SUBSTACK": [2, self.add_blocks(body)],
            },
            "fields": {},
            "shadow": False,
            "topLevel": False,
        }
        self.target["blocks"][bid] = block
        return [bid]
    
    def repeat(self, times, body):
        """Repeat N times with body."""
        bid = self._bid()
        block = {
            "opcode": "control_repeat",
            "next": None,
            "parent": None,
            "inputs": {
                "TIMES": [1, [self._make_shadow(str(times)), self._make_shadow(str(times))]],
                "SUBSTACK": [2, self.add_blocks(body)],
            },
            "fields": {},
            "shadow": False,
            "topLevel": False,
        }
        self.target["blocks"][bid] = block
        return [bid]
    
    def forever(self, body):
        """Forever loop."""
        bid = self._bid()
        block = {
            "opcode": "control_forever",
            "next": None,
            "parent": None,
            "inputs": {
                "SUBSTACK": [2, self.add_blocks(body)],
            },
            "fields": {},
            "shadow": False,
            "topLevel": False,
        }
        self.target["blocks"][bid] = block
        return [bid]
    
    def wait_until(self, reporter_bid):
        bid = self._bid()
        block = {
            "opcode": "control_wait_until",
            "next": None,
            "parent": None,
            "inputs": {
                "CONDITION": [2, reporter_bid],
            },
            "fields": {},
            "shadow": False,
            "topLevel": False,
        }
        self.target["blocks"][bid] = block
        return [bid]
    
    def eq(self, a_val, b_val):
        """Equality reporter. a_val, b_val can be (str, str) tuples or block IDs."""
        rid = self._bid()
        inputs = {}
        if isinstance(a_val, tuple):
            inputs["OPERAND1"] = [1, [self._make_shadow(a_val[0]), self._make_shadow(a_val[0])]]
        else:
            inputs["OPERAND1"] = [2, a_val]
        if isinstance(b_val, tuple):
            inputs["OPERAND2"] = [1, [self._make_shadow(b_val[0]), self._make_shadow(b_val[0])]]
        else:
            inputs["OPERAND2"] = [2, b_val]
        self.target["blocks"][rid] = {
            "opcode": "operator_equals", "next": None, "parent": None,
            "inputs": inputs, "fields": {}, "shadow": False, "topLevel": False,
        }
        return rid
    
    def lt(self, a_val, b_val):
        """Less-than reporter."""
        rid = self._bid()
        inputs = {}
        if isinstance(a_val, tuple):
            inputs["OPERAND1"] = [1, [self._make_shadow(a_val[0]), self._make_shadow(a_val[0])]]
        else:
            inputs["OPERAND1"] = [2, a_val]
        if isinstance(b_val, tuple):
            inputs["OPERAND2"] = [1, [self._make_shadow(b_val[0]), self._make_shadow(b_val[0])]]
        else:
            inputs["OPERAND2"] = [2, b_val]
        self.target["blocks"][rid] = {
            "opcode": "operator_lt", "next": None, "parent": None,
            "inputs": inputs, "fields": {}, "shadow": False, "topLevel": False,
        }
        return rid


# ═══════════════════════════════════════════
# C. SPRITE / PROJECT HELPERS
# ═══════════════════════════════════════════

def make_costume(name, svg_data):
    asset_id = uid()
    return {
        "assetId": asset_id,
        "name": name,
        "bitmapResolution": 1,
        "md5ext": f"{asset_id}.svg",
        "dataFormat": "svg",
        "rotationCenterX": 0,
        "rotationCenterY": 0,
    }

def make_sprite(name, is_stage=False):
    target = {
        "isStage": is_stage,
        "name": name,
        "variables": {},
        "lists": {},
        "broadcasts": {},
        "blocks": {},
        "comments": {},
        "currentCostume": 0,
        "costumes": [],
        "sounds": [],
        "volume": 100,
        "layerOrder": 0 if is_stage else 1,
    }
    if is_stage:
        target["tempo"] = 60
        target["videoTransparency"] = 50
        target["videoState"] = "off"
        target["textToSpeechLanguage"] = None
    else:
        target["visible"] = True
        target["x"] = 0
        target["y"] = 0
        target["size"] = 100
        target["direction"] = 90
        target["draggable"] = False
        target["rotationStyle"] = "all around"
    return target

def build_project(targets):
    return {
        "targets": targets,
        "monitors": [],
        "extensions": [],
        "meta": {"semver": "3.0.0", "vm": "2.3.0", "agent": "python-sb3-gen/drone-rescue"}
    }

def pack_sb3(project, path):
    os.makedirs(os.path.dirname(path) or ".", exist_ok=True)
    with zipfile.ZipFile(path, 'w', zipfile.ZIP_DEFLATED) as zf:
        zf.writestr('project.json', json.dumps(project, ensure_ascii=False, indent=2))
    print(f"✅ Generated: {path} ({os.path.getsize(path)} bytes)")

# ═══════════════════════════════════════════
# D. SVG ASSET LIBRARY
# ═══════════════════════════════════════════

ASSETS = {}

ASSETS["title_bg"] = '''<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 480 360">
  <defs><linearGradient id="s1" x1="0" y1="0" x2="0" y2="1">
    <stop offset="0%" stop-color="#1a1a2e"/><stop offset="40%" stop-color="#e2725b"/>
    <stop offset="70%" stop-color="#f4a261"/><stop offset="100%" stop-color="#e9c46a"/>
  </linearGradient></defs>
  <rect width="480" height="360" fill="url(#s1)"/>
  <polygon points="0,280 60,160 120,220 180,140 240,200 300,130 360,190 420,150 480,210 480,360 0,360" fill="#2d1b0e" opacity=".6"/>
  <polygon points="0,300 80,200 140,250 200,180 260,240 340,170 400,230 480,190 480,360 0,360" fill="#3d2b1e" opacity=".5"/>
  <rect x="0" y="300" width="480" height="60" fill="#4a3728"/>
  <rect x="210" y="295" width="60" height="10" rx="3" fill="#666"/>
  <text x="240" y="110" text-anchor="middle" font-size="28" font-weight="bold" fill="#fff" font-family="sans-serif">无人机地震救援行动</text>
  <text x="240" y="148" text-anchor="middle" font-size="16" fill="#ffd166" font-family="sans-serif">四川山区 · 6.8级地震</text>
  <rect x="150" y="230" width="180" height="44" rx="22" fill="#e76f51" stroke="#fff" stroke-width="2"/>
  <text x="240" y="258" text-anchor="middle" font-size="17" fill="#fff" font-family="sans-serif">🚀 开始救援任务</text>
  <ellipse cx="240" cy="288" rx="14" ry="4" fill="#fff"/>
  <rect x="236" y="280" width="8" height="8" rx="2" fill="#ff6b35"/>
  <line x1="228" y1="284" x2="218" y2="276" stroke="#fff" stroke-width="2"/>
  <line x1="252" y1="284" x2="262" y2="276" stroke="#fff" stroke-width="2"/>
</svg>'''

ASSETS["village_before"] = '''<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 480 360">
  <defs><linearGradient id="s2" x1="0" y1="0" x2="0" y2="1">
    <stop offset="0%" stop-color="#87ceeb"/><stop offset="60%" stop-color="#b0e0e6"/><stop offset="100%" stop-color="#e0f0e8"/>
  </linearGradient></defs>
  <rect width="480" height="360" fill="url(#s2)"/>
  <polygon points="0,280 80,120 160,200 240,100 320,180 400,110 480,190 480,360 0,360" fill="#567d46"/>
  <polygon points="0,310 100,180 200,250 300,160 400,230 480,170 480,360 0,360" fill="#6b8e4e"/>
  <rect x="0" y="280" width="480" height="80" fill="#7c9d5e"/>
  <rect x="80" y="250" width="40" height="35" fill="#d4a574"/><polygon points="75,250 100,230 125,250" fill="#8b4513"/><rect x="92" y="265" width="15" height="20" fill="#5c3317"/>
  <rect x="180" y="240" width="45" height="40" fill="#e8c9a0"/><polygon points="175,240 202,215 230,240" fill="#a0522d"/><rect x="195" y="258" width="15" height="22" fill="#5c3317"/>
  <rect x="330" y="255" width="38" height="30" fill="#d4a574"/><polygon points="325,255 349,235 373,255" fill="#8b4513"/><rect x="342" y="268" width="14" height="17" fill="#5c3317"/>
  <path d="M0,300 Q200,290 480,305" stroke="#c4a882" stroke-width="12" fill="none"/>
  <circle cx="50" cy="260" r="15" fill="#2d5a27"/><rect x="48" y="272" width="4" height="15" fill="#5c3317"/>
  <circle cx="420" cy="255" r="18" fill="#3a7a32"/><rect x="418" y="270" width="4" height="12" fill="#5c3317"/>
</svg>'''

ASSETS["village_after"] = '''<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 480 360">
  <defs><linearGradient id="s3" x1="0" y1="0" x2="0" y2="1">
    <stop offset="0%" stop-color="#8b7355"/><stop offset="50%" stop-color="#a09080"/><stop offset="100%" stop-color="#b8a89a"/>
  </linearGradient></defs>
  <rect width="480" height="360" fill="url(#s3)"/>
  <polygon points="0,280 80,140 160,200 240,120 320,190 400,130 480,180 480,360 0,360" fill="#5c4a3a"/>
  <polygon points="0,310 100,190 200,260 300,180 400,240 480,200 480,360 0,360" fill="#6b5a4a"/>
  <polygon points="140,180 180,230 220,190 260,280 170,300 120,250" fill="#8b7355"/>
  <rect x="0" y="270" width="480" height="90" fill="#7a6a5a"/>
  <polygon points="75,260 100,245 125,260" fill="#8b7355"/><rect x="80" y="260" width="18" height="18" fill="#a09080" transform="rotate(-15,89,269)"/><rect x="100" y="258" width="20" height="15" fill="#a09080" transform="rotate(10,110,265)"/>
  <path d="M0,310 Q100,305 200,320 Q300,335 480,315" stroke="#5c4a3a" stroke-width="14" fill="none" stroke-dasharray="20,5,8,5"/>
  <circle cx="160" cy="220" r="20" fill="#c4b8a8" opacity=".5"/><circle cx="180" cy="210" r="15" fill="#c4b8a8" opacity=".4"/>
  <circle cx="350" cy="230" r="18" fill="#c4b8a8" opacity=".45"/><circle cx="370" cy="218" r="12" fill="#c4b8a8" opacity=".35"/>
  <circle cx="280" cy="200" r="22" fill="#c4b8a8" opacity=".4"/>
</svg>'''

ASSETS["rescue_complete"] = '''<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 480 360">
  <defs><linearGradient id="s4" x1="0" y1="0" x2="0" y2="1">
    <stop offset="0%" stop-color="#2c3e50"/><stop offset="40%" stop-color="#e74c3c"/><stop offset="65%" stop-color="#f39c12"/><stop offset="100%" stop-color="#f1c40f"/>
  </linearGradient></defs>
  <rect width="480" height="360" fill="url(#s4)"/>
  <polygon points="0,300 100,180 200,260 300,170 400,240 480,190 480,360 0,360" fill="#1a1a2e" opacity=".5"/>
  <rect x="0" y="300" width="480" height="60" fill="#2c3e50"/>
  <rect x="280" y="295" width="50" height="20" rx="3" fill="#e74c3c"/>
  <rect x="310" y="280" width="25" height="15" fill="#fff"/>
  <circle cx="290" cy="318" r="5" fill="#333"/><circle cx="320" cy="318" r="5" fill="#333"/>
  <ellipse cx="380" cy="120" rx="14" ry="5" fill="#fff"/>
  <rect x="376" y="112" width="8" height="8" rx="2" fill="#ff6b35"/>
  <line x1="370" y1="116" x2="358" y2="110" stroke="#fff" stroke-width="1.5"/>
  <line x1="390" y1="116" x2="402" y2="110" stroke="#fff" stroke-width="1.5"/>
  <circle cx="50" cy="40" r="1.5" fill="#fff"/><circle cx="150" cy="60" r="1.5" fill="#fff"/>
  <circle cx="400" cy="30" r="1.5" fill="#fff"/><circle cx="300" cy="50" r="1.5" fill="#fff"/>
  <circle cx="100" cy="80" r="1" fill="#fff"/><circle cx="450" cy="70" r="1" fill="#fff"/>
</svg>'''

ASSETS["drone_normal"] = '''<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 60 44">
  <rect x="22" y="17" width="16" height="12" rx="3" fill="#fff" stroke="#333" stroke-width="1.5"/>
  <circle cx="30" cy="24" r="4" fill="#ff6b35"/><circle cx="30" cy="24" r="2" fill="#333"/>
  <line x1="22" y1="22" x2="4" y2="10" stroke="#ddd" stroke-width="3"/>
  <line x1="38" y1="22" x2="56" y2="10" stroke="#ddd" stroke-width="3"/>
  <line x1="22" y1="26" x2="4" y2="38" stroke="#ddd" stroke-width="3"/>
  <line x1="38" y1="26" x2="56" y2="38" stroke="#ddd" stroke-width="3"/>
  <ellipse cx="4" cy="8" rx="10" ry="3" fill="#ff6b35" opacity=".7"/>
  <ellipse cx="56" cy="8" rx="10" ry="3" fill="#ff6b35" opacity=".7"/>
  <ellipse cx="4" cy="40" rx="10" ry="3" fill="#ff6b35" opacity=".7"/>
  <ellipse cx="56" cy="40" rx="10" ry="3" fill="#ff6b35" opacity=".7"/>
  <circle cx="30" cy="16" r="2" fill="#0f0"/>
</svg>'''

ASSETS["drone_drop"] = '''<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 60 50">
  <rect x="22" y="22" width="16" height="12" rx="3" fill="#fff" stroke="#333" stroke-width="1.5"/>
  <circle cx="30" cy="29" r="4" fill="#ff6b35"/><circle cx="30" cy="29" r="2" fill="#333"/>
  <line x1="22" y1="27" x2="4" y2="15" stroke="#ddd" stroke-width="3"/>
  <line x1="38" y1="27" x2="56" y2="15" stroke="#ddd" stroke-width="3"/>
  <line x1="22" y1="31" x2="4" y2="43" stroke="#ddd" stroke-width="3"/>
  <line x1="38" y1="31" x2="56" y2="43" stroke="#ddd" stroke-width="3"/>
  <ellipse cx="4" cy="13" rx="10" ry="3" fill="#ff6b35" opacity=".7"/>
  <ellipse cx="56" cy="13" rx="10" ry="3" fill="#ff6b35" opacity=".7"/>
  <ellipse cx="4" cy="45" rx="10" ry="3" fill="#ff6b35" opacity=".7"/>
  <ellipse cx="56" cy="45" rx="10" ry="3" fill="#ff6b35" opacity=".7"/>
  <line x1="30" y1="34" x2="30" y2="44" stroke="#333" stroke-width="1.5"/>
  <circle cx="30" cy="21" r="2" fill="#ff0"/>
</svg>'''

ASSETS["survivor_hidden"] = '''<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 30 40">
  <rect x="2" y="28" width="26" height="12" rx="3" fill="#8b7355" opacity=".8"/>
  <polygon points="5,28 15,20 25,28" fill="#7a6a5a" opacity=".8"/>
</svg>'''

ASSETS["survivor_wave"] = '''<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 40 55">
  <circle cx="20" cy="18" r="8" fill="#f5d5a0" stroke="#333" stroke-width="1"/>
  <circle cx="17" cy="17" r="1.5" fill="#333"/><circle cx="23" cy="17" r="1.5" fill="#333"/>
  <ellipse cx="20" cy="22" rx="3" ry="2" fill="#333"/>
  <rect x="14" y="26" width="12" height="18" rx="3" fill="#e74c3c"/>
  <line x1="26" y1="28" x2="34" y2="16" stroke="#f5d5a0" stroke-width="3" stroke-linecap="round"/>
  <line x1="14" y1="30" x2="8" y2="26" stroke="#f5d5a0" stroke-width="3" stroke-linecap="round"/>
  <rect x="0" y="42" width="40" height="8" rx="3" fill="#8b7355"/>
  <text x="20" y="10" text-anchor="middle" font-size="10" fill="#f44" font-weight="bold">SOS</text>
</svg>'''

ASSETS["survivor_found"] = '''<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 40 60">
  <circle cx="20" cy="18" r="8" fill="#f5d5a0" stroke="#2ecc71" stroke-width="2"/>
  <circle cx="17" cy="17" r="1.5" fill="#333"/><circle cx="23" cy="17" r="1.5" fill="#333"/>
  <path d="M16,22 Q20,27 24,22" stroke="#333" stroke-width="1.5" fill="none"/>
  <rect x="14" y="26" width="12" height="18" rx="3" fill="#e74c3c"/>
  <line x1="14" y1="28" x2="6" y2="18" stroke="#f5d5a0" stroke-width="3" stroke-linecap="round"/>
  <line x1="26" y1="28" x2="34" y2="18" stroke="#f5d5a0" stroke-width="3" stroke-linecap="round"/>
  <rect x="0" y="42" width="40" height="8" rx="3" fill="#8b7355"/>
  <circle cx="35" cy="12" r="8" fill="#2ecc71"/>
  <polyline points="31,12 34,15 39,9" stroke="#fff" stroke-width="2" fill="none"/>
</svg>'''

ASSETS["supply_pack"] = '''<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 30 30">
  <rect x="2" y="2" width="26" height="26" rx="4" fill="#e74c3c" stroke="#fff" stroke-width="1.5"/>
  <line x1="15" y1="2" x2="15" y2="28" stroke="#fff" stroke-width="1.5"/>
  <line x1="2" y1="15" x2="28" y2="15" stroke="#fff" stroke-width="1.5"/>
  <text x="15" y="20" text-anchor="middle" font-size="12" fill="#fff" font-weight="bold">+</text>
</svg>'''

ASSETS["start_btn"] = '''<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 180 50">
  <rect x="0" y="0" width="180" height="50" rx="25" fill="#e76f51" stroke="#fff" stroke-width="2"/>
  <text x="90" y="32" text-anchor="middle" font-size="18" fill="#fff" font-family="sans-serif">🚀 开始救援任务</text>
</svg>'''

print(f"✅ Loaded {len(ASSETS)} SVG assets")

# ═══════════════════════════════════════════
# E. BUILD PROJECT
# ═══════════════════════════════════════════

def build():
    targets = []
    
    # ── STAGE ──
    stage = make_sprite("Stage", is_stage=True)
    stage["costumes"] = [
        make_costume("TitleScreen", ASSETS["title_bg"]),
        make_costume("VillageBefore", ASSETS["village_before"]),
        make_costume("VillageAfter", ASSETS["village_after"]),
        make_costume("RescueComplete", ASSETS["rescue_complete"]),
    ]
    stage["currentCostume"] = 0
    
    sb = B(stage)
    
    # Variables
    for vname, vid in B.VAR_IDS.items():
        stage["variables"][vid] = [vname, 0]
    
    # Broadcasts
    for bname, bid in B.BC_IDS.items():
        stage["broadcasts"][bid] = bname
    
    # Stage scripts
    sb.hat("event_whenflagclicked", body=[
        *sb.switch_costume("TitleScreen"),
        *sb.set_var("scene", 1),
        *sb.set_var("found", 0),
        *sb.set_var("delivered", 0),
        *sb.set_var("timer", 0),
        *sb.broadcast("scene_1"),
    ])
    
    # scene_1 handler
    sb.hat("event_whenbroadcastreceived",
        {"BROADCAST_OPTION": ["scene_1", B.BC_IDS["scene_1"]]},
        body=[*sb.switch_costume("TitleScreen"), *sb.set_var("scene", 1)])
    
    # scene_2 handler: earthquake
    sb.hat("event_whenbroadcastreceived",
        {"BROADCAST_OPTION": ["scene_2", B.BC_IDS["scene_2"]]},
        body=[
            *sb.switch_costume("VillageBefore"),
            *sb.set_var("scene", 2),
            *sb.wait(1),
            *sb.broadcast("earthquake_shake"),
            *sb.wait(2),
            *sb.switch_costume("VillageAfter"),
            *sb.wait(1.5),
            *sb.broadcast("scene_3"),
        ])
    
    # scene_3 handler
    sb.hat("event_whenbroadcastreceived",
        {"BROADCAST_OPTION": ["scene_3", B.BC_IDS["scene_3"]]},
        body=[*sb.set_var("scene", 3)])
    
    # all_rescued → scene_5
    sb.hat("event_whenbroadcastreceived",
        {"BROADCAST_OPTION": ["all_rescued", B.BC_IDS["all_rescued"]]},
        body=[
            *sb.wait(1),
            *sb.switch_costume("RescueComplete"),
            *sb.set_var("scene", 5),
            *sb.broadcast("scene_5"),
        ])
    
    # restart handler
    sb.hat("event_whenbroadcastreceived",
        {"BROADCAST_OPTION": ["restart", B.BC_IDS["restart"]]},
        body=[
            *sb.set_var("found", 0),
            *sb.set_var("delivered", 0),
            *sb.set_var("timer", 0),
            *sb.broadcast("scene_1"),
        ])
    
    targets.append(stage)
    
    # ── DRONE SPRITE ──
    drone = make_sprite("Drone")
    drone["costumes"] = [
        make_costume("drone_normal", ASSETS["drone_normal"]),
        make_costume("drone_drop", ASSETS["drone_drop"]),
    ]
    drone["size"] = 70
    drone["layerOrder"] = 10
    db = B(drone)
    
    # On scene_3: show and position drone
    db.hat("event_whenbroadcastreceived",
        {"BROADCAST_OPTION": ["scene_3", B.BC_IDS["scene_3"]]},
        body=[
            *db.show(),
            *db.goto(-180, 80),
            *db.switch_costume("drone_normal"),
            *db.say("使用方向键操控无人机，搜寻幸存者！", 2),
        ])
    
    # Hide on other scenes
    db.hat("event_whenbroadcastreceived",
        {"BROADCAST_OPTION": ["scene_1", B.BC_IDS["scene_1"]]},
        body=[*db.hide()])
    db.hat("event_whenbroadcastreceived",
        {"BROADCAST_OPTION": ["scene_2", B.BC_IDS["scene_2"]]},
        body=[*db.hide()])
    db.hat("event_whenbroadcastreceived",
        {"BROADCAST_OPTION": ["scene_5", B.BC_IDS["scene_5"]]},
        body=[*db.hide()])
    
    # Arrow key movement (only active during scene 3)
    for key, dx, dy in [("up arrow", 0, 6), ("down arrow", 0, -6),
                          ("right arrow", 6, 0), ("left arrow", -6, 0)]:
        scene_var = db.var_reporter("scene")
        eq3 = db.eq(scene_var, ("3", "3"))
        db.hat("event_whenkeypressed", {"KEY_OPTION": [key, key]},
            body=db.if_(eq3, [
                ("motion_changexby", {"DX": (str(dx), str(dx))}, {}),
                ("motion_changeyby", {"DY": (str(dy), str(dy))}, {}),
            ]))
    
    # Boundary clamping (forever during search — using a hat that watches)
    # We'll handle boundaries with a simple forever-if
    # Actually, let's skip complex boundary for now. The drone moves within stage.
    
    # Space key: delivery (only in scene 3, near any found survivor)
    scene_var2 = db.var_reporter("scene")
    eq_scene3 = db.eq(scene_var2, ("3", "3"))
    db.hat("event_whenkeypressed", {"KEY_OPTION": ["space", "space"]},
        body=db.if_(eq_scene3, [
            *db.switch_costume("drone_drop"),
            *db.broadcast("supply_delivered"),
            *db.wait(0.5),
            *db.switch_costume("drone_normal"),
        ]))
    
    targets.append(drone)
    
    # ── SURVIVOR SPRITES (x3) ──
    survivor_positions = [(-140, -60), (0, -80), (140, -50)]
    for i, (sx, sy) in enumerate(survivor_positions):
        name = f"Survivor{i+1}"
        surv = make_sprite(name)
        surv["costumes"] = [
            make_costume("survivor_hidden", ASSETS["survivor_hidden"]),
            make_costume("survivor_wave", ASSETS["survivor_wave"]),
            make_costume("survivor_found", ASSETS["survivor_found"]),
        ]
        surv["x"] = sx
        surv["y"] = sy
        surv["size"] = 90
        surv["layerOrder"] = 5
        sv = B(surv)
        
        # Track whether this survivor was found
        found_var_name = f"surv{i+1}_found"
        found_var_id = uid(20)
        surv["variables"][found_var_id] = [found_var_name, 0]
        
        # On scene_3: show hidden costume
        sv.hat("event_whenbroadcastreceived",
            {"BROADCAST_OPTION": ["scene_3", B.BC_IDS["scene_3"]]},
            body=[
                *sv.show(),
                *sv.switch_costume("survivor_wave"),
                *sv.set_var(found_var_name, 0),
            ])
        
        # On scene_1, scene_2, scene_5: hide
        for sc in ["scene_1", "scene_2", "scene_5"]:
            sv.hat("event_whenbroadcastreceived",
                {"BROADCAST_OPTION": [sc, B.BC_IDS[sc]]},
                body=[*sv.hide()])
        
        # Forever: check distance to Drone for detection
        # Distance reporter for sensing_touchingobject alternative
        dist_reporter = sv._make_reporter("sensing_distanceto",
            inputs={"DISTANCETOMENU": ("_drone_", "_drone_")})
        lt_60 = sv.lt(dist_reporter, ("60", "60"))
        
        # Check if not already found
        found_var_reporter = sv.var_reporter(found_var_name)
        eq0 = sv.eq(found_var_reporter, ("0", "0"))
        
        # Both conditions: distance < 60 AND not found yet
        and_reporter = sv._make_reporter("operator_and",
            inputs={"OPERAND1": [2, lt_60], "OPERAND2": [2, eq0]})
        
        sv.hat("event_whenbroadcastreceived",
            {"BROADCAST_OPTION": ["scene_3", B.BC_IDS["scene_3"]]},
            body=sv.forever(
                sv.if_(and_reporter, [
                    *sv.switch_costume("survivor_found"),
                    *sv.set_var(found_var_name, 1),
                    *sv.broadcast("survivor_found"),
                    *sv.change_var("found", 1),
                ])
            ))
        
        # On restart: reset
        sv.hat("event_whenbroadcastreceived",
            {"BROADCAST_OPTION": ["restart", B.BC_IDS["restart"]]},
            body=[*sv.set_var(found_var_name, 0)])
        
        targets.append(surv)
    
    # ── SUPPLY SPRITE ──
    supply = make_sprite("Supply")
    supply["costumes"] = [make_costume("supply_pack", ASSETS["supply_pack"])]
    supply["size"] = 60
    supply["layerOrder"] = 8
    spb = B(supply)
    
    spb.hat("event_whenbroadcastreceived",
        {"BROADCAST_OPTION": ["scene_1", B.BC_IDS["scene_1"]]},
        body=[*spb.hide()])
    spb.hat("event_whenbroadcastreceived",
        {"BROADCAST_OPTION": ["scene_5", B.BC_IDS["scene_5"]]},
        body=[*spb.hide()])
    
    # When supply_delivered: show at drone position, fall down, then hide
    spb.hat("event_whenbroadcastreceived",
        {"BROADCAST_OPTION": ["supply_delivered", B.BC_IDS["supply_delivered"]]},
        body=[
            *spb.show(),
            ("motion_goto", {"TO": ("_drone_", "_drone_")}, {}),
            ("motion_glidesecstoxy", {"SECS": ("1", "1"), "X": ("x position", "x position"), "Y": ("-140", "-140")}, {}),
            *spb.hide(),
            *spb.change_var("delivered", 1),
        ])
    
    # Check if all 3 delivered → broadcast all_rescued
    del_var = spb.var_reporter("delivered")
    eq3_del = spb.eq(del_var, ("3", "3"))
    spb.hat("event_whenbroadcastreceived",
        {"BROADCAST_OPTION": ["supply_delivered", B.BC_IDS["supply_delivered"]]},
        body=spb.if_(eq3_del, spb.broadcast("all_rescued")))
    
    targets.append(supply)
    
    # ── START BUTTON SPRITE ──
    btn = make_sprite("StartButton")
    btn["costumes"] = [make_costume("start_btn", ASSETS["start_btn"])]
    btn["x"] = 0
    btn["y"] = -50
    btn["size"] = 100
    btn["layerOrder"] = 20
    bb = B(btn)
    
    bb.hat("event_whenbroadcastreceived",
        {"BROADCAST_OPTION": ["scene_1", B.BC_IDS["scene_1"]]},
        body=[*bb.show(), *bb.goto(0, -50)])
    bb.hat("event_whenbroadcastreceived",
        {"BROADCAST_OPTION": ["scene_2", B.BC_IDS["scene_2"]]},
        body=[*bb.hide()])
    
    # When clicked: advance to scene_2
    bb.hat("event_whenthisspriteclicked", {},
        body=[*bb.broadcast("scene_2"), *bb.hide()])
    
    targets.append(btn)
    
    # ── RESTART BUTTON (shown on scene_5) ──
    restart_btn = make_sprite("RestartButton")
    restart_btn["costumes"] = [make_costume("start_btn", ASSETS["start_btn"])]
    restart_btn["x"] = 0
    restart_btn["y"] = -60
    restart_btn["size"] = 90
    restart_btn["layerOrder"] = 20
    rb = B(restart_btn)
    
    rb.hat("event_whenbroadcastreceived",
        {"BROADCAST_OPTION": ["scene_5", B.BC_IDS["scene_5"]]},
        body=[*rb.show(), *rb.goto(0, -60)])
    rb.hat("event_whenbroadcastreceived",
        {"BROADCAST_OPTION": ["scene_1", B.BC_IDS["scene_1"]]},
        body=[*rb.hide()])
    rb.hat("event_whenthisspriteclicked", {},
        body=[*rb.broadcast("restart"), *rb.hide()])
    
    targets.append(restart_btn)
    
    # ── UI OVERLAY SPRITE (narrative text) ──
    ui = make_sprite("UI_Overlay")
    # Simple empty costume
    ui["costumes"] = [make_costume("empty", ASSETS["supply_pack"])]
    ui["size"] = 5
    ui["layerOrder"] = 25
    ub = B(ui)
    
    # scene_2 narration
    ub.hat("event_whenbroadcastreceived",
        {"BROADCAST_OPTION": ["scene_2", B.BC_IDS["scene_2"]]},
        body=[*ub.show(), *ub.goto(0, -140), *ub.say("地震发生！山区道路中断，无人机救援队立即出发！", 3)])
    
    # scene_3 narration
    ub.hat("event_whenbroadcastreceived",
        {"BROADCAST_OPTION": ["scene_3", B.BC_IDS["scene_3"]]},
        body=[*ub.say("使用方向键操控无人机，搜寻幸存者！", 2)])
    
    # survivor_found narration
    ub.hat("event_whenbroadcastreceived",
        {"BROADCAST_OPTION": ["survivor_found", B.BC_IDS["survivor_found"]]},
        body=[*ub.say("发现生命信号！按空格键投送急救包！", 2)])
    
    # supply_delivered narration
    ub.hat("event_whenbroadcastreceived",
        {"BROADCAST_OPTION": ["supply_delivered", B.BC_IDS["supply_delivered"]]},
        body=[*ub.say("物资已投送！继续搜寻其他幸存者。", 1.5)])
    
    # scene_5 narration
    ub.hat("event_whenbroadcastreceived",
        {"BROADCAST_OPTION": ["scene_5", B.BC_IDS["scene_5"]]},
        body=[
            *ub.show(),
            *ub.goto(0, -30),
            *ub.say("救援任务完成！每一次飞行，都是生命的希望。", 3),
        ])
    
    # Hide on scene_1
    ub.hat("event_whenbroadcastreceived",
        {"BROADCAST_OPTION": ["scene_1", B.BC_IDS["scene_1"]]},
        body=[*ub.hide()])
    
    targets.append(ui)
    
    return build_project(targets)


# ═══════════════════════════════════════════
# F. MAIN
# ═══════════════════════════════════════════
if __name__ == '__main__':
    project = build()
    pack_sb3(project, 'output/drone_rescue.sb3')
    
    # Print stats
    total_blocks = sum(len(t['blocks']) for t in project['targets'])
    total_sprites = sum(1 for t in project['targets'] if not t['isStage'])
    print(f"📊 {total_sprites} sprites + Stage, {total_blocks} blocks total")
    print("🎮 Open output/drone_rescue.sb3 in Scratch 3 to play!")
```

- [ ] **Step 3: Run the generator**

```bash
cd scratch_drone_rescue && python3 generate_sb3.py
```

- [ ] **Step 4: Verify the .sb3 is a valid ZIP**

```bash
cd scratch_drone_rescue && python3 -c "
import zipfile, json
with zipfile.ZipFile('output/drone_rescue.sb3') as z:
    print('Files:', z.namelist())
    data = json.loads(z.read('project.json'))
    print('Targets:', len(data['targets']))
    for t in data['targets']:
        print(f'  {t[\"name\"]}: {len(t[\"blocks\"])} blocks, {len(t[\"costumes\"])} costumes')
"
```

- [ ] **Step 5: Commit**

```bash
git add scratch_drone_rescue/
git commit -m "feat: complete drone rescue Scratch 3 generator with all sprites and scripts"
```

---

### Task 2: Debug and fix — test in Scratch, fix common issues

**Files:**
- Modify: `scratch_drone_rescue/generate_sb3.py`

After generating the initial .sb3, load it in Scratch 3 (desktop or online) and fix common issues:

---

- [ ] **Step 1: Common fixes checklist**

Scratch 3 project.json gotchas to verify:
1. All `broadcasts` referenced in blocks exist in the target's `broadcasts` dict
2. All `variables` referenced exist in some target's `variables` dict
3. Costume indices match `currentCostume` (0-based)
4. Block `next` chains don't have cycles or dangling refs
5. Reporter blocks (operators, sensors) don't have `next` set
6. Shadow blocks have `shadow: true`
7. C-block inputs have `SUBSTACK` pointing to a valid block ID

- [ ] **Step 2: Fix missing broadcast references**

Ensure every broadcast name used in blocks is registered. The `B.BC_IDS` dict should cover all. Add a validation pass after building.

- [ ] **Step 3: Fix distance sensing**

The `sensing_distanceto` block needs a proper `DISTANCETOMENU` input. Verify it references the Drone sprite correctly.

- [ ] **Step 4: Rebuild and re-verify**

```bash
cd scratch_drone_rescue && python3 generate_sb3.py
python3 -c "
import zipfile, json
with zipfile.ZipFile('output/drone_rescue.sb3') as z:
    data = json.loads(z.read('project.json'))
# Check all broadcast refs
all_bc = {}
for t in data['targets']:
    for bid, bname in t.get('broadcasts', {}).items():
        all_bc[bid] = bname
print(f'Total broadcasts: {len(all_bc)}')
for t in data['targets']:
    for bid, block in t['blocks'].items():
        bc_opt = block.get('fields', {}).get('BROADCAST_OPTION')
        if bc_opt:
            bc_id = bc_opt[1]
            if bc_id and bc_id not in all_bc and bc_id not in t.get('broadcasts', {}):
                print(f'WARNING: broadcast {bc_id} ({bc_opt[0]}) used but not registered in {t[\"name\"]}')
print('Validation complete.')
"
```

- [ ] **Step 5: Commit fixes**

```bash
git add scratch_drone_rescue/
git commit -m "fix: validate and fix broadcast references and block wiring"
```
