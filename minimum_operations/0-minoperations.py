#!/usr/bin/python3
"""
    Module minoperations
    function to define the fewest number of operations needed
    to result in exactly n H characters in the file.

"""


def minOperations(n):
    """
        function to define the fewest number of operations needed
        to result in exactly n H characters in the file.

        :param n: number

        :return: int or 0 if n is impossible to achieve
    """
    if n <= 1:
        return 0

    operations = 0
    divisor = 2

    while divisor <= n:
        while n % divisor == 0:
            operations += divisor
            n //= divisor
        divisor += 1

    return operations
