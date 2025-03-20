#!/usr/bin/python3
"""
    script to log parsing
"""

import sys
import re

total_size = 0
count_line = 0
count_status_code = {'200': 0, '301': 0, '400': 0, '401': 0,
                     '403': 0, '404': 0, '405': 0, '500': 0}

# Pattern de la ligne de log
pattern = (r'^((?:\d{1,3}\.){3}\d{1,3}|[\w.-]+)\s*-\s*\[(.*?)\]'
           r' "GET /projects/\d+ HTTP/1\.1" (\d+) (\d+)$')

try:
    for line in sys.stdin:
        line = line.strip()

        match = re.match(pattern, line)
        if not match:
            continue  # Ignore la ligne si elle ne correspond pas au pattern

        count_line += 1
        elements = line.split(" ")

        # Vérifier que les éléments sont bien des nombres avant de les convertir
        try:
            status_code = elements[-2]
            size = int(elements[-1])

            total_size += size
            if status_code in count_status_code:
                count_status_code[status_code] += 1
        except (ValueError, IndexError):
            continue  # Ignore si la ligne est mal formée

        # Afficher les stats toutes les 10 lignes
        if count_line % 10 == 0:
            print('File size: {}'.format(total_size))
            for code, count in sorted(count_status_code.items()):
                if count > 0:
                    print('{}: {}'.format(code, count))

except KeyboardInterrupt:
    pass  # Permet d'afficher les logs même en cas d'interruption

finally:
    print('File size: {}'.format(total_size))
    for code, count in sorted(count_status_code.items()):
        if count > 0:
            print('{}: {}'.format(code, count))
