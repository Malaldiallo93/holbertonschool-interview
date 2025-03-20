#!/usr/bin/python3
"""
    Script for log parsing.
"""

import sys
import re

# Variables globales pour stocker les statistiques
total_size = 0
count_line = 0
count_status_code = {
    '200': 0, '301': 0, '400': 0, '401': 0,
    '403': 0, '404': 0, '405': 0, '500': 0
}

# Pattern pour capturer les logs valides
log_pattern = re.compile(
    r'^((?:\d{1,3}\.){3}\d{1,3}|[\w.-]+)\s*-\s*\[(.*?)\] '
    r'"GET /projects/\d+ HTTP/1\.1" (\d+) (\d+)$'
)

def print_stats():
    """ Affiche les statistiques de logs. """
    print(f'File size: {total_size}')
    for code in sorted(count_status_code.keys()):
        if count_status_code[code] > 0:
            print(f'{code}: {count_status_code[code]}')

try:
    for line in sys.stdin:
        line = line.strip()

        match = log_pattern.match(line)
        if match:
            count_line += 1

            # Extraire le code de statut et la taille
            try:
                status_code = match.group(3)
                file_size = int(match.group(4))

                # Ajouter la taille au total
                total_size += file_size

                # Incrémenter le compteur de status code
                if status_code in count_status_code:
                    count_status_code[status_code] += 1

            except ValueError:
                continue  # Ignore les lignes avec une taille invalide

            # Afficher les statistiques toutes les 10 lignes
            if count_line % 10 == 0:
                print_stats()

except KeyboardInterrupt:
    pass  # Permet d'afficher les statistiques même en cas d'interruption

finally:
    print_stats()  # Afficher les statistiques finales après interruption ou fin de fichier
