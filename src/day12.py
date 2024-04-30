#!/usr/bin/env python3
import sys
import numpy as np

with open(
    sys.argv[1] if len(sys.argv) > 1 else "input.txt", "r", encoding="utf8"
) as f:
    g = f.read().strip()


GRID = [
    [ord(c) for c in row.replace("S", "a").replace("E", "z")] for row in g.split("\n")
]

start = None
end = None
for i, row in enumerate(g.split("\n")):
    if "S" in row:
        start = (i, row.index("S"))
    if "E" in row:
        end = (i, row.index("E"))


def bfs(grid, candidates, end, seen, step = 0):
    next_candidates = []
    if not candidates:
        return float("inf")
    for candidate in candidates:
        y, x = candidate
        seen[y][x] = 1
        for new_point in [(y - 1, x), (y + 1, x), (y, x - 1), (y, x + 1)]:
            ny, nx = new_point
            if (
                0 <= ny < len(grid)
                and 0 <= nx < len(grid[0])
                and not seen[ny][nx]
                and grid[ny][nx] - 1 <= grid[y][x]
            ):
                if new_point == end:
                    return step+1
                seen[ny][nx]=1
                next_candidates.append(new_point)
    return bfs(grid, next_candidates, end, seen,step+1)


print(bfs(GRID, [start], end, np.zeros_like(GRID),0))


print(
    min(
        [
            bfs(GRID, [(i, j)], end, np.zeros_like(GRID))
            for i, row in enumerate(GRID)
            for j, c in enumerate(row)
            if c == ord("a")
        ]
    )
)
