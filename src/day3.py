#!/usr/bin/env python3
import sys

def scorer(char):
    if c.isupper():
        return 27 + ord(c) - ord("A")
    else:
        return 1 + ord(c) - ord("a")

with open(sys.argv[1] if len(sys.argv) > 1 else "input.txt", "r", encoding="utf8") as f:
    sum = 0
    f=f.read().split("\n")
    for line in f:
        c = set(line[: len(line) // 2]).intersection(set(line[len(line) // 2 :])).pop()
        sum+=scorer(c)
    print(sum)
    
    sum = 0
    for l1,l2,l3 in zip(f[::3],f[1::3],f[2::3],strict=1):
        c = (set(l1).intersection(set(l2))
                    .intersection(set(l3)).pop())
        sum+=scorer(c)
    print(sum)
