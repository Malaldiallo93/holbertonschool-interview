#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>

void sandpiles_sum(int grid1[3][3], int grid2[3][3]);
void collapse_sandpile(int grid1[3][3], int grid2[3][3], int i, int j);
void add_piles(int grid1[3][3], int grid2[3][3]);
void _print_grid(int grid[3][3]);
int check_instability(int grid[3][3]);

#endif
