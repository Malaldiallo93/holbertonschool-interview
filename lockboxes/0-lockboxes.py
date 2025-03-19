#!/usr/bin/python3
"""
    Lockboxes algorithm
"""

import sys

sys.setrecursionlimit(10**4)


def canUnlockAll(boxes):
    """

        Method to test if you can open all boxes

        :param boxes: list of lists

        :return: True or False
    """

    # dict to store keys in associated boxes
    keys = {}
    # calculate n number of locked boxes
    n = len(boxes)

    # set to store unlocked boxes
    unlocked_boxes = set()

    # store all key in dict with corresponding index of boxes
    for i in range(0, n-1):
        keys[i] = boxes[i]

    # recursive function to open boxes
    def unlockbox(box_index):
        # condition to stop
        if box_index in unlocked_boxes:
            return

        # add to set unlock current box
        unlocked_boxes.add(box_index)

        # check keys in this box and recursively unlock
        for key in boxes[box_index]:
            if key < n:
                unlockbox(key)

    # open first box 0
    unlockbox(0)

    # compare boxes and unlocked_boxes
    if len(unlocked_boxes) == len(boxes):
        result = True
    else:
        result = False

    return result
