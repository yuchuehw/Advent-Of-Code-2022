#!/usr/bin/python3
import numpy as np

instruct="""R 4
U 4
L 3
D 1
R 4
D 1
L 5
R 2"""

head = np.array((0, 0))
tail = np.array((0, 0))
visited = {(0, 0)}

direction_to_change = {
    "U": np.array((0, 1)),
    "D": np.array((0, -1)),
    "L": np.array((-1, 0)),
    "R": np.array((1, 0)),
}

for row in instruct.split("\n"):
    direction, step = row.split()
    for _ in range(int(step)):
        temp = tuple(head)
        head += direction_to_change[direction]
        if tuple(head) not in [tuple(tail + (x, y)) for x in range(-1, 2) for y in range(-1, 2)]:
            tail = np.array(temp)
            visited.add(temp)

print(len(visited))
