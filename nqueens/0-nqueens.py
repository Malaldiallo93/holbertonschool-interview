#!/usr/bin/python3
"""
N Queens
"""
import sys


def check_diagonals(a, b):
    """
    Check if the two given positions are diagonally aligned.
    """
    return a[0] - a[1] == b[0] - b[1] or a[0] + a[1] == b[0] + b[1]


def is_safe(positions, new_pos):
    """
    Check the given new position against all previously placed positions.
    Returns False if they are aligned in any way, or True if they aren't.
    """
    for pos in positions:
        if pos[1] == new_pos[1] or check_diagonals(pos, new_pos):
            return False
    return True


def solve_nqueens(N):
    """
    Uses backtracking to find all possible solutions to the N Queens problem
    and returns them as a list of lists.
    """
    def backtrack(row):
        """Recursively runs on each row of a solution."""
        if row == N:
            # Found N correct positions, save this solution and stop here
            solutions.append(positions.copy())
            return

        for col in range(N):
            new_pos = [row, col]
            if is_safe(positions, new_pos):
                # Add to the list of positions
                positions.append(new_pos)
                # Run on next row
                backtrack(row + 1)
                # Remove the positions after the backtracking
                positions.pop()

    solutions = []
    positions = []
    # Start the backtracking recursion, at row 0
    backtrack(0)
    return solutions


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: nqueens N")
        exit(1)

    try:
        n = int(sys.argv[1])
    except ValueError:
        print("N must be a number")
        exit(1)

    if n < 4:
        print("N must be at least 4")
        exit(1)

    solutions = solve_nqueens(n)
    for solution in solutions:
        print(solution)
