#!/usr/bin/python3
import sys
from typing import List, Tuple
import numpy as np


DIRECTION_TO_CHANGE = {
    "U": np.array((0, 1)),
    "D": np.array((0, -1)),
    "L": np.array((-1, 0)),
    "R": np.array((1, 0)),
}


def find_visited(
    nodes: List[np.ndarray[Tuple[int, int]]], instruct: str, visited: set
) -> None:
    assert len(nodes) >= 2 and "there must be at least two nodes"
    for row in instruct.split("\n"):
        direction, step = row.split()
        for _ in range(int(step)):
            nodes[0] += DIRECTION_TO_CHANGE[direction]
            previous_node = nodes[0]
            for i, node in enumerate(nodes):
                if not i:
                    continue
                if any(abs(previous_node - node) > 1):
                    delta = [
                        -1 if i < 0 else 1 if i else 0 for i in (previous_node - node)
                    ]
                    node += delta
                    previous_node = node
                else:
                    break
            visited.add(tuple(nodes[-1]))


def main():
    filename = sys.argv[1] if len(sys.argv) > 1 else "input.txt"
    with open(filename, "r", encoding="utf8") as f:
        instruct = f.read()
    visited = {(0, 0)}
    find_visited([np.array((0, 0)) for _ in range(2)], instruct, visited)
    print(len(visited))

    visited = {(0, 0)}
    find_visited([np.array((0, 0)) for _ in range(10)], instruct, visited)
    print(len(visited))


if __name__ == "__main__":
    main()
