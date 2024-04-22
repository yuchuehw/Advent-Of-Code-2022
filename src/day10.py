#!/usr/bin/env python3
import sys
import tempfile

with open(sys.argv[1] if len(sys.argv) > 1 else "input.txt", "r", encoding="utf8") as f:
    instructions = f.read()

value = 1
old_value = 1

cycle = 1

answer = 0

with tempfile.TemporaryFile() as tmp:

    def print_(cycle, value):
        if value - 1 <= (cycle - 1) % 40 <= value + 1:
            tmp.write(b"#")
        else:
            tmp.write(b".")
        if cycle and cycle % 40 == 0:
            tmp.write(b"\n")
        if cycle and (cycle - 20) % 40 == 0:
            return cycle * value
        return 0

    for i in instructions.split("\n"):
        answer += print_(cycle, value)
        if " " not in i:
            cycle += 1
        else:
            cycle += 1
            answer += print_(cycle, value)
            cycle += 1
            value += int(i[i.index(" ") + 1:])

    print(answer)
    tmp.seek(0)
    print(str(tmp.read(), "utf-8"))
