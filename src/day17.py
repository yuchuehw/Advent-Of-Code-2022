#!/usr/bin/env python3
from itertools import cycle
import sys

BLOCKS = """\
####

.#.
###
.#.

..#
..#
###

#
#
#
#

##
##"""

BLOCKS_ARRAY = [[[i for i,v in enumerate(row) if v == "#"]for row in reversed(blocks.split("\n"))]for blocks in BLOCKS.split("\n\n")]

GRID_MIN_X = -2
GRID_MAX_X = 4

GRID_MIN_Y = 0

ROCKS_TO_DROP = 2022

filename = sys.argv[1] if len(sys.argv) > 1 else "input.txt"

with open(filename, "r", encoding="utf8") as f:
    INSTRUCTION = list(f.read().strip())

blocks_iterator = cycle(BLOCKS_ARRAY)
instruct_iterator = cycle(INSTRUCTION)

occupied = set()
high_point = 0

for i in range(ROCKS_TO_DROP):
    lowest_Y = high_point + (4 if i else 3)
    offset_X = 0
    new_occupied = []
    block = next(blocks_iterator)
    # print(block)
    while True:
        temp_occupied = []
        
        dx = 1 if next(instruct_iterator)==">"else -1
        
        if all((k+offset_X+dx,lowest_Y+j) not in occupied and GRID_MIN_X<=k+offset_X+dx<=GRID_MAX_X for j, row in enumerate(block) for k in row):
            offset_X+=dx
            # print(offset_X)
            
        if all((k+offset_X,lowest_Y-1+j) not in occupied and lowest_Y-1+j>=0 for j, row in enumerate(block) for k in row):
            lowest_Y -= 1
        else:
            break
    
    high_point = max(lowest_Y+len(block)-1,high_point)
    occupied.update([(k+offset_X,lowest_Y+j) for j, row in enumerate(block) for k in row])

print(high_point+1)
