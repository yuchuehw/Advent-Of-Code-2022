#!/usr/bin/env python3
import sys
import numpy as np

def label_visible(grid_array, visible, view_rating):
    """
    Label the visible trees and calculate the view rating.

    Args:
        grid_array (numpy.ndarray): Input grid array.
        visible (numpy.ndarray): Array to store visible trees.
        view_rating (numpy.ndarray): Array to store view ratings.
    """
    for i, row in enumerate(grid_array):
        max_tree_height = -1
        for j, tree_height in enumerate(row):
            if tree_height > max_tree_height:
                max_tree_height = tree_height
                visible[i][j] = 1

            score = 0
            for other_tree_height in row[:j][::-1]:
                score += 1
                if tree_height <= other_tree_height:
                    break
            view_rating[i][j] *= score

def main():
    filename = sys.argv[1] if len(sys.argv) > 1 else "input.txt"

    with open(filename, "r", encoding="utf8") as f:
        grid = f.read()

    grid_array = np.array([[int(i) for i in row] for row in grid.split("\n")])
    visible = np.zeros_like(grid_array)
    view_rating = np.ones_like(grid_array)

    label_visible(grid_array, visible, view_rating)
    label_visible(grid_array[:, ::-1], visible[:, ::-1], view_rating[:, ::-1])
    label_visible(grid_array.T, visible.T, view_rating.T)
    label_visible(grid_array.T[:, ::-1], visible.T[:, ::-1], view_rating.T[:, ::-1])

    print("Total visible trees:", np.sum(visible))
    print("Maximum view rating:", np.max(view_rating))

if __name__ == "__main__":
    main()
