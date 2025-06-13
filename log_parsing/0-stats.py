#!/usr/bin/python3
"""
Script that reads stdin line by line and computes metrics.
"""

if __name__ == '__main__':

    import sys

    def print_results(statusCodes, fileSize):
        """
        Print accumulated statistics.
        """
        print(f"File size: {fileSize}")
        for statusCode, times in sorted(statusCodes.items()):
            if times:
                print(f"{statusCode}: {times}")

    # Initialize dictionary to store counts of status codes
    statusCodes = {
        "200": 0,
        "301": 0,
        "400": 0,
        "401": 0,
        "403": 0,
        "404": 0,
        "405": 0,
        "500": 0
    }
    # Initialize total file size and line counter
    fileSize = 0
    n_lines = 0

    try:
        # Read stdin line by line
        for line in sys.stdin:
            # Print statistics after every 10 lines
            if n_lines != 0 and n_lines % 10 == 0:
                print_results(statusCodes, fileSize)
            n_lines += 1
            data = line.split()
            if len(data) >= 2:
                try:
                    # Parse and compute metrics
                    statusCode = data[-2]
                    if statusCode in statusCodes:
                        statusCodes[statusCode] += 1
                    fileSize += int(data[-1])
                except (IndexError, ValueError):
                    # Skip lines with invalid formats
                    continue
        # Print final statistics at EOF
        print_results(statusCodes, fileSize)
    except KeyboardInterrupt:
        # Print statistics on keyboard interruption (Ctrl+C)
        print_results(statusCodes, fileSize)
        raise
