#!/usr/bin/python3
"""

Log Parsing Script.

This script reads standard input line by line and processes HTTP logs
in the following format:
<IP Address> - [<date>] "GET /projects/260 HTTP/1.1" <status_code> <file_size>

Features:
- Computes the total file size.
- Counts occurrences of HTTP status codes (200, 301, 400, 401, 403, 404, 405, 500).
- Prints statistics every 10 lines.
- Handles keyboard interruption (CTRL+C) gracefully by displaying the final stats.

Usage:
    ./0-generator.py | ./0-stats.py

Output format:
    File size: <total_size>
    <status_code>: <count>

Status codes are displayed in ascending order if present.
"""

import sys

total_size = 0
count_line = 0
status_codes = {
    '200': 0, '301': 0, '400': 0, '401': 0,
    '403': 0, '404': 0, '405': 0, '500': 0
}


def print_stats():
    """Prints the accumulated statistics."""
    print("File size: {}".format(total_size))
    for code in sorted(status_codes.keys()):
        if status_codes[code] > 0:
            print("{}: {}".format(code, status_codes[code]))


try:
    for line in sys.stdin:
        parts = line.split()
        if len(parts) >= 7:
            try:
                status_code = parts[-2]
                file_size = int(parts[-1])

                total_size += file_size
                if status_code in status_codes:
                    status_codes[status_code] += 1

                count_line += 1
                if count_line % 10 == 0:
                    print_stats()
            except ValueError:
                continue

except KeyboardInterrupt:
    print_stats()
    raise

finally:
    print_stats()
