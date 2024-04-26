#!/usr/bin/env python3
from ast import literal_eval
from bisect import bisect_left
from functools import cmp_to_key
import sys

with open(sys.argv[1] if len(sys.argv) > 1 else "input.txt", "r", encoding="utf8") as f:
    data = f.read().strip()


def compare(a, b):
    assert isinstance(a, (int, list))
    assert isinstance(b, (int, list))
    if isinstance(a, int) and isinstance(b, int):
        return -1 if a < b else 0 if a == b else 1
    if isinstance(b, int):
        return compare(a, [b])
    if isinstance(a, int):
        return compare([a], b)
    if a and b:
        r = compare(a[0], b[0])
        return r if r else compare(a[1:], b[1:])
    return 1 if a else -1 if b else 0


KEY = cmp_to_key(compare)
FLAG1 = [[2]]
FLAG2 = [[6]]
counter = 0
signal_list = [FLAG1, FLAG2]
for i, pair in enumerate(data.split("\n\n"), start=1):
    l1, l2 = [literal_eval(_) for _ in pair.split("\n")]
    i1 = bisect_left(signal_list, KEY(l1), key=KEY)
    signal_list.insert(i1, l1)
    i2 = bisect_left(signal_list, KEY(l2), key=KEY)
    signal_list.insert(i2, l2)
    counter += i * (i1 < i2)

print(counter)

print(
    (bisect_left(signal_list, KEY(FLAG1), key=KEY) + 1)
    * ((bisect_left(signal_list, KEY(FLAG2), key=KEY) + 1))
)
