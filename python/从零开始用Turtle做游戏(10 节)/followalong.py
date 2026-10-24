#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""生成全部 10 课跟打课件 / 学案 / 终稿代码。"""
from __future__ import annotations

from followalong_engine import write_outputs
from followalong_lesson01 import LESSON as L1
from followalong_lesson02 import LESSON as L2
from followalong_lesson03 import LESSON as L3
from followalong_lesson04 import LESSON as L4
from followalong_lesson05 import LESSON as L5
from followalong_lesson06 import LESSON as L6
from followalong_lesson07 import LESSON as L7
from followalong_lesson08 import LESSON as L8
from followalong_lesson09 import LESSON as L9
from followalong_lesson10 import LESSON as L10

ALL = [L1, L2, L3, L4, L5, L6, L7, L8, L9, L10]


def write_all() -> None:
    for lesson in ALL:
        write_outputs(lesson)


if __name__ == "__main__":
    write_all()
