#!/usr/bin/env python3
import sys

with open(sys.argv[1], "r", encoding="utf8") as f:
    f = f.read()
    print(max([sum((*map(int, group.split("\n")),)) for group in f.split("\n\n")]))
    print(
        sum(
            sorted(
                [sum((*map(int, group.split("\n")),)) for group in f.split("\n\n")],
                reverse=True,
            )[:3]
        )
    )
