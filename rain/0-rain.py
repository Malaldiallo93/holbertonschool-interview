#!/usr/bin/python3
"""
    Rain
"""


def rain(walls):
    """
        Given a list of non-negative integers representing the heights of walls
        with unit width, write a function that returns how much water will
        be retained after it rains.

    :param walls: list of non-negative

    :return: integer representing the total amount of rainwater retained
    """
    # not list or not enough wall to retain water!
    if not walls or len(walls) < 3:
        return 0

    n = len(walls)

    # left[i] contains height of the tallest bar to the
    # left of i'th bar including itself
    left = [0] * n
    # right[i] contains height of the tallest bar to the
    # right of i'th bar including itself
    right = [0] * n

    # Fill left array
    left[0] = walls[0]
    for i in range(1, n):
        left[i] = max(left[i - 1], walls[i])

    # Fill right array
    right[n - 1] = walls[n - 1]
    for i in range(n - 2, -1, -1):
        right[i] = max(right[i + 1], walls[i])

    water = 0
    for i in range(n):
        water += min(left[i], right[i]) - walls[i]

    return water
