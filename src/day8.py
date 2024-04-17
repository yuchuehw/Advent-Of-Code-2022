#!/usr/bin/env python3
import sys
import numpy as np

with open(sys.argv[1] if len(sys.argv) > 1 else "input.txt", "r", encoding="utf8") as f:
    grid = f.read()

grid_array = np.array([[int(i) for i in row]for row in grid.split("\n")])
visible = grid_array*0



def label_visible(grid_array,visible):
    for i, row in enumerate(grid_array):
        max_ = -1
        for j, tree in enumerate(row):
            if tree > max_:
                max_ = tree
                visible[i][j] = 1

label_visible(grid_array,visible)
label_visible(grid_array[::,::-1],visible[::,::-1])
label_visible(grid_array.T,visible.T)
label_visible(grid_array.T[::,::-1],visible.T[::,::-1])


print(sum(sum(visible)))
