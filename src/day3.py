#!/usr/bin/env python3
import sys

with open(sys.argv[1] if len(sys.argv) > 1 else "input.txt", "r", encoding="utf8") as f:
    sum = 0
    f=f.read().split("\n")
    for line in f:
        c = set(line[: len(line) // 2]).intersection(set(line[len(line) // 2 :])).pop()
        if c.isupper():
            sum += 27
            sum += ord(c) - ord("A")
        else:
            sum += 1
            sum += ord(c) - ord("a")
    print(sum)
    sum = 0
    for l1,l2,l3 in zip(f[::3],f[1::3],f[2::3],strict=1):
        c = (set(l1).intersection(set(l2))
                    .intersection(set(l3)).pop())
        if c.isupper():
            sum += 27
            sum += ord(c) - ord("A")
        else:
            sum += 1
            sum += ord(c) - ord("a")
    
    print(sum)
