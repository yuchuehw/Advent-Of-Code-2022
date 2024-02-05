#!/usr/bin/env python3
import sys
from collections import defaultdict, namedtuple

with open(sys.argv[1] if len(sys.argv) > 1 else "input.txt", "r", encoding="utf8") as f:
    d1 = defaultdict(list)
    instructions = []
    Instrction = namedtuple("Instruction", "quantity origin destination")
    L = ""
    for line in f.read().split("\n"):
        if not L and not set(line) - set(" 0123456789"):
            L = line
        elif L and line:
            _, quantity, _, origin, _, destination = line.split()
            instructions.append(Instrction(int(quantity), origin, destination))
        elif not L:
            for i, c in enumerate(line):
                if c in "ABCDEFGHIJKLMNOPQRSTUVWXYZ":
                    d1[i].insert(0, c)
    d2 = {}
    for o in L.split():
        d2[o] = d1[L.index(o)]
    for quantity, origin, destination in instructions:
        for _ in range(quantity):
            d2[destination].append(d2[origin].pop())
    for i in sorted(d2):
        print(d2[i].pop(), end="")
    print()
