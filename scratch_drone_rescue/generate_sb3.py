#!/usr/bin/env python3
"""Generate Scratch 3 .sb3 for Drone Earthquake Rescue.
Usage: python3 generate_sb3.py
Output: output/drone_rescue.sb3
"""
import json, uuid, zipfile, os

# Global registry of SVG assets to embed in the .sb3 ZIP
_SVG_ASSETS = {}

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
        self._pending_shadows = []  # shadows created during current block, need parent set

    def _bid(self):
        self.bid_counter[0] += 1
        return f"b{self.bid_counter[0]:05d}"

    def _resolve_input(self, key, val):
        """Resolve an input value to Scratch 3 format.
        val can be:
          - a block ID string → [2, block_id] (substack input)
          - (number_str, shadow_name) → [1, [shadow_bid, shadow_bid]]  (obscured shadow)
          - [block_id, block_id] → [3, name, block_ids]  (no shadow)
          - Already in Scratch 3 format [type, ...] → pass through
        """
        # Already in Scratch 3 format [type, data, ...]
        if isinstance(val, (list, tuple)) and len(val) > 0 and isinstance(val[0], int):
            return val
        if isinstance(val, str) and val.startswith("b"):
            return [2, val]
        if isinstance(val, (list, tuple)) and len(val) > 0 and isinstance(val[0], str) and val[0].startswith("b") and val[0][1:].isdigit():
            return [3, "".join(val), list(val)]
        if isinstance(val, tuple):
            num_str = val[0]
            shadow_name = val[1] if len(val) > 1 else num_str
            sid = self._make_shadow(key, shadow_name)
            self._pending_shadows.append(sid)
            return [1, [sid, sid]]
        # list of blocks → substack
        if isinstance(val, list):
            first = self.add_blocks(val)
            return [2, first]
        return [1, [str(val), str(val)]]

    _SHADOW_TYPES = {
        "BROADCAST_INPUT": ("event_broadcast_menu", "BROADCAST_OPTION"),
        "TO": ("motion_gotom_menu", "TO"),
    }

    def _make_shadow(self, input_key, name):
        """Create a shadow block with the correct opcode for the input type."""
        sid = self._bid()
        if input_key in self._SHADOW_TYPES:
            opcode, field_key = self._SHADOW_TYPES[input_key]
            fields = {field_key: [name, None]}
        else:
            try:
                float(name)
                opcode = "math_number"
                fields = {"NUM": [name, None]}
            except ValueError:
                opcode = "text"
                fields = {"TEXT": [name, None]}

        self.target["blocks"][sid] = {
            "opcode": opcode,
            "next": None,
            "parent": None,
            "inputs": {},
            "fields": fields,
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

            # Set parent on any shadow blocks created during this block's input resolution
            for shadow_id in self._pending_shadows:
                if shadow_id in self.target["blocks"]:
                    self.target["blocks"][shadow_id]["parent"] = bid
            self._pending_shadows.clear()

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

    def var_reporter(self, var_name, *, var_id=None):
        """Create a variable reporter block."""
        vid = var_id if var_id else self.VAR_IDS.get(var_name, var_name)
        return self._make_reporter("data_variable",
            fields={"VARIABLE": [var_name, vid]})

    def set_var(self, var_name, value, *, var_id=None):
        """Set variable to value."""
        vid = var_id if var_id else self.VAR_IDS.get(var_name, var_name)
        return [("data_setvariableto",
            {"VALUE": (str(value), str(value))},
            {"VARIABLE": [var_name, vid]})]

    def change_var(self, var_name, delta, *, var_id=None):
        vid = var_id if var_id else self.VAR_IDS.get(var_name, var_name)
        return [("data_changevariableby",
            {"VALUE": (str(delta), str(delta))},
            {"VARIABLE": [var_name, vid]})]

    def broadcast(self, msg_name):
        bc_id = self.BC_IDS.get(msg_name, f"bc_{msg_name}")
        # Create proper event_broadcast_menu shadow block
        shadow_id = self._bid()
        self.target["blocks"][shadow_id] = {
            "opcode": "event_broadcast_menu",
            "next": None,
            "parent": None,
            "inputs": {},
            "fields": {"BROADCAST_OPTION": [msg_name, bc_id]},
            "shadow": True,
            "topLevel": False,
        }
        return [("event_broadcast",
            {"BROADCAST_INPUT": [1, [shadow_id, shadow_id]]},
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
        """If block with reporter condition and body. Returns block definition tuple."""
        return [("control_if",
            {"CONDITION": [2, reporter_bid], "SUBSTACK": body},
            {},
            False)]

    def repeat(self, times, body):
        """Repeat N times with body. Returns block definition tuple."""
        return [("control_repeat",
            {"TIMES": (str(times), str(times)), "SUBSTACK": body},
            {},
            False)]

    def forever(self, body):
        """Forever loop. Returns block definition tuple."""
        return [("control_forever",
            {"SUBSTACK": body},
            {},
            False)]

    def wait_until(self, reporter_bid):
        """Wait until condition. Returns block definition tuple."""
        return [("control_wait_until",
            {"CONDITION": [2, reporter_bid]},
            {},
            False)]

    def _shadow_for(self, input_key, val):
        """Create a shadow and track it for parent assignment. Returns shadow ID."""
        sid = self._make_shadow(input_key, val)
        self._pending_shadows.append(sid)
        return sid

    def eq(self, a_val, b_val):
        """Equality reporter. a_val, b_val can be (str, str) tuples or block IDs."""
        rid = self._bid()
        inputs = {}
        if isinstance(a_val, tuple):
            s = self._shadow_for("OPERAND1", a_val[0])
            inputs["OPERAND1"] = [1, [s, s]]
        else:
            inputs["OPERAND1"] = [2, a_val]
        if isinstance(b_val, tuple):
            s = self._shadow_for("OPERAND2", b_val[0])
            inputs["OPERAND2"] = [1, [s, s]]
        else:
            inputs["OPERAND2"] = [2, b_val]
        block = {
            "opcode": "operator_equals", "next": None, "parent": None,
            "inputs": inputs, "fields": {}, "shadow": False, "topLevel": False,
        }
        self.target["blocks"][rid] = block
        # Set parent on shadows
        for shadow_id in self._pending_shadows:
            if shadow_id in self.target["blocks"]:
                self.target["blocks"][shadow_id]["parent"] = rid
        self._pending_shadows.clear()
        return rid

    def lt(self, a_val, b_val):
        """Less-than reporter."""
        rid = self._bid()
        inputs = {}
        if isinstance(a_val, tuple):
            s = self._shadow_for("OPERAND1", a_val[0])
            inputs["OPERAND1"] = [1, [s, s]]
        else:
            inputs["OPERAND1"] = [2, a_val]
        if isinstance(b_val, tuple):
            s = self._shadow_for("OPERAND2", b_val[0])
            inputs["OPERAND2"] = [1, [s, s]]
        else:
            inputs["OPERAND2"] = [2, b_val]
        block = {
            "opcode": "operator_lt", "next": None, "parent": None,
            "inputs": inputs, "fields": {}, "shadow": False, "topLevel": False,
        }
        self.target["blocks"][rid] = block
        # Set parent on shadows
        for shadow_id in self._pending_shadows:
            if shadow_id in self.target["blocks"]:
                self.target["blocks"][shadow_id]["parent"] = rid
        self._pending_shadows.clear()
        return rid


# ═══════════════════════════════════════════
# C. SPRITE / PROJECT HELPERS
# ═══════════════════════════════════════════

def make_costume(name, svg_data):
    asset_id = uid()
    filename = f"{asset_id}.svg"
    _SVG_ASSETS[filename] = svg_data
    return {
        "assetId": asset_id,
        "name": name,
        "bitmapResolution": 1,
        "md5ext": filename,
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
        for filename, data in _SVG_ASSETS.items():
            zf.writestr(filename, data)
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

ASSETS["transparent"] = '<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 1 1"><rect width="1" height="1" fill="none"/></svg>'

ASSETS["start_btn"] = '''<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 180 50">
  <rect x="0" y="0" width="180" height="50" rx="25" fill="#e76f51" stroke="#fff" stroke-width="2"/>
  <text x="90" y="32" text-anchor="middle" font-size="18" fill="#fff" font-family="sans-serif">🚀 开始救援任务</text>
</svg>'''

ASSETS["restart_btn"] = '''<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 180 50">
  <rect x="0" y="0" width="180" height="50" rx="25" fill="#2ecc71" stroke="#fff" stroke-width="2"/>
  <text x="90" y="32" text-anchor="middle" font-size="18" fill="#fff" font-family="sans-serif">🔄 再次出发</text>
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

    # Timer increment during scene 3 (every 1 second)
    sb.hat("event_whenbroadcastreceived",
        {"BROADCAST_OPTION": ["scene_3", B.BC_IDS["scene_3"]]},
        body=[*sb.set_var("timer", 0)])

    sb.hat("event_whenbroadcastreceived",
        {"BROADCAST_OPTION": ["scene_3", B.BC_IDS["scene_3"]]},
        body=sb.forever([
            *sb.wait(1),
            *sb.change_var("timer", 1),
        ]))

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

    # Boundary clamping (forever loop during scene 3)
    x_reporter = db._make_reporter("motion_xposition")
    y_reporter = db._make_reporter("motion_yposition")
    db.hat("event_whenbroadcastreceived",
        {"BROADCAST_OPTION": ["scene_3", B.BC_IDS["scene_3"]]},
        body=db.forever([
            *db.if_(db.lt(("220", "220"), x_reporter), [
                ("motion_setx", {"X": ("220", "220")}, {})]),
            *db.if_(db.lt(x_reporter, ("-220", "-220")), [
                ("motion_setx", {"X": ("-220", "-220")}, {})]),
            *db.if_(db.lt(("160", "160"), y_reporter), [
                ("motion_sety", {"Y": ("160", "160")}, {})]),
            *db.if_(db.lt(y_reporter, ("-160", "-160")), [
                ("motion_sety", {"Y": ("-160", "-160")}, {})]),
        ]))

    # Earthquake shake handler
    db.hat("event_whenbroadcastreceived",
        {"BROADCAST_OPTION": ["earthquake_shake", B.BC_IDS["earthquake_shake"]]},
        body=db.repeat(15, [
            ("motion_changexby", {"DX": ("5", "5")}, {}),
            ("motion_changeyby", {"DY": ("3", "3")}, {}),
            ("control_wait", {"DURATION": ("0.05", "0.05")}, {}),
            ("motion_changexby", {"DX": ("-5", "-5")}, {}),
            ("motion_changeyby", {"DY": ("-3", "-3")}, {}),
            ("control_wait", {"DURATION": ("0.05", "0.05")}, {}),
        ]))

    # Space key: delivery (only in scene 3, near any found survivor)
    # Build distance check for proximity-gated delivery
    dist_s1 = db._make_reporter("sensing_distanceto",
        fields={"DISTANCETOMENU": ["Survivor1", None]})
    dist_s2 = db._make_reporter("sensing_distanceto",
        fields={"DISTANCETOMENU": ["Survivor2", None]})
    dist_s3 = db._make_reporter("sensing_distanceto",
        fields={"DISTANCETOMENU": ["Survivor3", None]})

    lt_s1 = db.lt(dist_s1, ("80", "80"))
    lt_s2 = db.lt(dist_s2, ("80", "80"))
    lt_s3 = db.lt(dist_s3, ("80", "80"))

    # OR chain: near Survivor1 OR Survivor2 OR Survivor3
    or_12 = db._make_reporter("operator_or",
        inputs={"OPERAND1": [2, lt_s1], "OPERAND2": [2, lt_s2]})
    near_any = db._make_reporter("operator_or",
        inputs={"OPERAND1": [2, or_12], "OPERAND2": [2, lt_s3]})

    # Final condition: scene == 3 AND near any survivor
    scene_var2 = db.var_reporter("scene")
    eq_scene3 = db.eq(scene_var2, ("3", "3"))
    can_deliver = db._make_reporter("operator_and",
        inputs={"OPERAND1": [2, eq_scene3], "OPERAND2": [2, near_any]})

    db.hat("event_whenkeypressed", {"KEY_OPTION": ["space", "space"]},
        body=db.if_(can_deliver, [
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
                *sv.set_var(found_var_name, 0, var_id=found_var_id),
            ])

        # On scene_1, scene_2, scene_5: hide
        for sc in ["scene_1", "scene_2", "scene_5"]:
            sv.hat("event_whenbroadcastreceived",
                {"BROADCAST_OPTION": [sc, B.BC_IDS[sc]]},
                body=[*sv.hide()])

        # Forever: check distance to Drone for detection
        # Distance reporter for sensing_touchingobject alternative
        dist_reporter = sv._make_reporter("sensing_distanceto",
            fields={"DISTANCETOMENU": ["Drone", None]})
        lt_60 = sv.lt(dist_reporter, ("60", "60"))

        # Check if not already found
        found_var_reporter = sv.var_reporter(found_var_name, var_id=found_var_id)
        eq0 = sv.eq(found_var_reporter, ("0", "0"))

        # Both conditions: distance < 60 AND not found yet
        and_reporter = sv._make_reporter("operator_and",
            inputs={"OPERAND1": [2, lt_60], "OPERAND2": [2, eq0]})

        sv.hat("event_whenbroadcastreceived",
            {"BROADCAST_OPTION": ["scene_3", B.BC_IDS["scene_3"]]},
            body=sv.forever(
                sv.if_(and_reporter, [
                    *sv.switch_costume("survivor_found"),
                    *sv.set_var(found_var_name, 1, var_id=found_var_id),
                    *sv.broadcast("survivor_found"),
                    *sv.change_var("found", 1),
                ])
            ))

        # On restart: reset
        sv.hat("event_whenbroadcastreceived",
            {"BROADCAST_OPTION": ["restart", B.BC_IDS["restart"]]},
            body=[*sv.set_var(found_var_name, 0, var_id=found_var_id)])

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
        {"BROADCAST_OPTION": ["scene_2", B.BC_IDS["scene_2"]]},
        body=[*spb.hide()])
    spb.hat("event_whenbroadcastreceived",
        {"BROADCAST_OPTION": ["scene_5", B.BC_IDS["scene_5"]]},
        body=[*spb.hide()])

    # When supply_delivered: show at drone position, fall down, then hide
    # After increment, check if all 3 delivered → broadcast all_rescued
    del_var = spb.var_reporter("delivered")
    eq3_del = spb.eq(del_var, ("3", "3"))
    spb.hat("event_whenbroadcastreceived",
        {"BROADCAST_OPTION": ["supply_delivered", B.BC_IDS["supply_delivered"]]},
        body=[
            *spb.show(),
            ("motion_goto", {"TO": ("Drone", "Drone")}, {}),
            ("motion_glidesecstoxy", {"SECS": ("1", "1"), "X": ("x position", "x position"), "Y": ("-140", "-140")}, {}),
            *spb.hide(),
            *spb.change_var("delivered", 1),
            *spb.if_(eq3_del, spb.broadcast("all_rescued")),
        ])

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
    restart_btn["costumes"] = [make_costume("restart_btn", ASSETS["restart_btn"])]
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
    # Transparent costume (1x1 invisible SVG)
    ui["costumes"] = [make_costume("empty", ASSETS["transparent"])]
    ui["size"] = 5
    ui["layerOrder"] = 25
    ub = B(ui)

    # scene_2 narration
    ub.hat("event_whenbroadcastreceived",
        {"BROADCAST_OPTION": ["scene_2", B.BC_IDS["scene_2"]]},
        body=[*ub.show(), *ub.goto(0, -140), *ub.say("地震发生！山区道路中断，地面救援队难以进入。无人机救援队，立即出发！", 3)])

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

    # ── POST-PROCESSING: Fix shadow parent references ──
    for target in targets:
        block_ids = set(target['blocks'].keys())
        for bid, block in target['blocks'].items():
            for iname, ival in block.get('inputs', {}).items():
                if isinstance(ival, list) and len(ival) >= 2:
                    refs = ival[1]
                    # Handle [[sid, sid]] format (obscured shadow)
                    if isinstance(refs, list):
                        for rid in refs:
                            if rid in block_ids and target['blocks'].get(rid, {}).get('shadow'):
                                if not target['blocks'][rid].get('parent'):
                                    target['blocks'][rid]['parent'] = bid
                    # Handle single shadow reference
                    elif isinstance(refs, str) and refs in block_ids:
                        if target['blocks'].get(refs, {}).get('shadow'):
                            if not target['blocks'][refs].get('parent'):
                                target['blocks'][refs]['parent'] = bid

    return build_project(targets)


# ═══════════════════════════════════════════
# F. MAIN
# ═══════════════════════════════════════════
if __name__ == '__main__':
    script_dir = os.path.dirname(os.path.abspath(__file__))
    out_path = os.path.join(script_dir, 'output', 'drone_rescue.sb3')
    project = build()
    pack_sb3(project, out_path)

    # Print stats
    total_blocks = sum(len(t['blocks']) for t in project['targets'])
    total_sprites = sum(1 for t in project['targets'] if not t['isStage'])
    print(f"📊 {total_sprites} sprites + Stage, {total_blocks} blocks total")
    print("🎮 Open output/drone_rescue.sb3 in Scratch 3 to play!")
