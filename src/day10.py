#!/usr/bin/env python3
import sys


def print_(cycle: int, value: int, p2_answer: list):
    if value - 1 <= (cycle - 1) % 40 <= value + 1:
        p2_answer.append("#")
    else:
        p2_answer.append(".")
    if cycle and cycle % 40 == 0:
        p2_answer.append("\n")
    if cycle and (cycle - 20) % 40 == 0:
        return cycle * value
    return 0


def main():

    with open(
        sys.argv[1] if len(sys.argv) > 1 else "input.txt", "r", encoding="utf8"
    ) as f:
        instructions = f.read()

    value = 1

    cycle = 1

    p1_answer = 0
    p2_answer = []

    for i in instructions.split("\n"):
        p1_answer += print_(cycle, value, p2_answer)
        if " " not in i:
            cycle += 1
        else:
            cycle += 1
            p1_answer += print_(cycle, value, p2_answer)
            cycle += 1
            value += int(i[i.index(" ") + 1 :])

    print(p1_answer)

    print("".join(p2_answer))


if __name__ == "__main__":
    main()
