#!/usr/bin/python3
"""
    Change comes from within
"""


def makeChange(coins, total):
    """
        determine the fewest number of coins needed to meet
        a given amount total

    :param coins: list of the values of the coins in your possession
    :param total: given amount to meet

    :return: fewest number of coins needed to meet total
        if total == 0 or less, return 0
        if total cannot be met by any number of coins you have
        return -1
    """

    if total <= 0:
        return 0

    # init solutions array with "infinity" value
    # index: amount, value:minimum number coins needed
    solutions = [total + 1] * (total + 1)
    solutions[0] = 0

    # build solution bottom-up
    for m in range(1, total + 1):
        # try each coins
        for c in coins:
            if c <= m:
                # update solution
                solutions[m] = min(solutions[m], 1 + solutions[m - c])

    return solutions[total] if solutions[total] <= total else - 1
