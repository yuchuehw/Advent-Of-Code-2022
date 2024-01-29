#!/usr/bin/env python3
import sys

with open(sys.argv[1] if len(sys.argv) > 1 else "input.txt", "r", encoding="utf8") as f:
    sum = 0
    for line in f.read().split("\n"):
        c = set(line[: len(line) // 2]).intersection(set(line[len(line) // 2 :])).pop()
        if c.isupper():
            sum += 27
            sum += ord(c) - ord("A")
        else:
            sum += 1
            sum += ord(c) - ord("a")

    print(sum)
