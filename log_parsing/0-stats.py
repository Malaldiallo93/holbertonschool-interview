#!/usr/bin/python3
"""
    script to log parsing
"""

import sys
import re


total_size = 0
count_line = 0
count_status_code = {'200': 0,
                     '301': 0,
                     '400': 0,
                     '401': 0,
                     '403': 0,
                     '404': 0,
                     '405': 0,
                     '500': 0
                     }
# pattern of line
pattern = (r'^((?:\d{1,3}\.){3}\d{1,3}|[\w.-]+)\s*-\s*\[(.*?)\]'
           r' "GET /projects/\d+ HTTP/1\.1" \d+ \d+$')

try:
    for line in sys.stdin:

        # check line
        match = re.match(pattern, line)
        if match:
            count_line += 1
            # split line
            elements = line.split(" ")
            # add size of total and determine status code
            total_size += int(elements[-1])
            status_code = elements[-2]
            # increment count of status code
            if status_code in count_status_code:
                count_status_code[status_code] += 1

            # print each 10 line
            if count_line % 10 == 0:
                print('File size: {}'.format(total_size))
                # print in sorted order
                for code, count_code in sorted(count_status_code.items()):
                    if count_code != 0:
                        print('{}: {}'.format(code, count_status_code[code]))
                # reinitialized count line
                count_line = 0
        else:
            elements = line.split(" ")
            if len(elements) > 6:
                total_size += int(elements[-1])

except KeyboardInterrupt:
    pass

finally:
    print('File size: {}'.format(total_size))
    # print in sorted order
    for code, count_code in sorted(count_status_code.items()):
        if count_code != 0:
            print('{}: {}'.format(code, count_status_code[code]))
