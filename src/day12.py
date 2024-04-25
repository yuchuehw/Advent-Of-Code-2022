#!/usr/bin/env python3
import sys

with open(
    sys.argv[1] if len(sys.argv) > 1 else "input.txt", "r", encoding="utf8"
) as f:
    g = f.read().strip()


GRID = [
    [ord(c) for c in row.replace("S", "a").replace("E", "z")] for row in g.split("
")
]

start = None
end = None
for i, row in enumerate(g.split("
")):
    if "S" in row:
        start = (i, row.index("S"))
    if "E" in row:
        end = (i, row.index("E"))


def bfs(grid, candidates, end, seen):
    next_candidates = []
    if not candidates:
        return float("inf")
    for candidate in candidates:
        y, x = candidate[-1]
        for new_point in [(y - 1, x), (y + 1, x), (y, x - 1), (y, x + 1)]:
            ny, nx = new_point
            if (
                0 <= ny < len(grid)
                and 0 <= nx < len(grid[0])
                and new_point not in seen
                and grid[ny][nx] - 1 <= grid[y][x]
            ):
                if new_point == end:
                    return len(candidate)
                seen.add(new_point)
                next_candidates.append(candidate[:] + [new_point])
    return bfs(grid, next_candidates, end, seen)


print(bfs(GRID, [[start]], end, set()))


print(
    min(
        [
            bfs(GRID, [[(i, j)]], end, set())
            for i, row in enumerate(GRID)
            for j, c in enumerate(row)
            if c == ord("a")
        ]
    )
)
