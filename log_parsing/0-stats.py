#!/usr/bin/python3

"""
Log Parsing Script.

This script reads standard input line by line and processes HTTP logs
in the following format:
<IP Address> - [<date>] "GET /projects/260 HTTP/1.1" <status_code> <file_size>

Features:
- Computes the total file size.
- Counts occurrences of HTTP status codes (200, 301, 400, 401, 403, 404, 405, 500).
- Prints statistics every 10 lines or on keyboard interruption (CTRL+C).
"""

import sys
import signal

# Global variables
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


def signal_handler(sig, frame):
    """Handles keyboard interruption (CTRL+C) by printing stats before exiting."""
    print_stats()
    sys.exit(0)


# Attach the signal handler to SIGINT (CTRL+C)
signal.signal(signal.SIGINT, signal_handler)

try:
    for line in sys.stdin:
        parts = line.split()
        if len(parts) >= 7:
            try:
                # Déclarer les variables globales AVANT de les modifier
                global total_size, count_line
                
                status_code = parts[-2]
                file_size = int(parts[-1])

                # Update global counters
                total_size += file_size
                if status_code in status_codes:
                    status_codes[status_code] += 1

                count_line += 1
                if count_line % 10 == 0:
                    print_stats()
            except ValueError:
                continue

except EOFError:
    pass  # Handle end of input gracefully

finally:
    print_stats()
