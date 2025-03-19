#!/usr/bin/python3
"""
    Island Perimeter
"""


def island_perimeter(grid):
    """
        function to compute perimeter of the island

    :param grid: list of int,
            0: water
            1: land
            each cell is square with side lenght of 1

    :return: perimeter of the corresponding island
    """
    perimeter = 0
    nbr_row = len(grid)
    nbr_col = len(grid[0])

    # add zero border
    grid = [x + [0] for x in grid] + [[0] * nbr_col]

    # read grid
    for row in range(nbr_row):
        for col in range(nbr_col):
            if grid[row][col] == 1:
                perimeter += 4 - 2 * (grid[row + 1][col] + grid[row][col + 1])

    return perimeter
