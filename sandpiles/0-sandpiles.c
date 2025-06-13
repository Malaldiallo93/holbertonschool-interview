#include "sandpiles.h"

/**
 * sandpiles_sum - Computes and prints the sum of two sandpiles
 * @grid1 : the first grid (3 by 3 array of ints)
 * @grid2 : the second grid (3 by 3 array of ints)
 *
 * Return: nothing
 */
void sandpiles_sum(int grid1[3][3], int grid2[3][3])
{
	int i = 0;
	int j = 0;
	char is_unstable = 1;

	add_piles(grid1, grid2);
	while (is_unstable)
	{
		is_unstable = check_instability(grid1);
		if (is_unstable)
			_print_grid(grid1);

		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				if (grid1[i][j] > 3)
				{
					collapse_sandpile(grid1, grid2, i, j);
				}
			}
		}
		add_piles(grid1, grid2);
	}
}

/**
 * collapse_sandpile - Collapses grid1 sandpile in 4 directions on grid2
 * @grid1 : the first grid (3 by 3 array of ints)
 * @grid2 : the second grid (3 by 3 array of ints)
 * @i : the line index of this sandpile
 * @j : the column index of this sandpile
 *
 * Return: Description of the returned value
 */
void collapse_sandpile(int grid1[3][3], int grid2[3][3], int i, int j)
{
	grid1[i][j] -= 4;

	if (j - 1 >= 0)
		grid2[i][j - 1] += 1;
	if (j + 1 < 3)
		grid2[i][j + 1] += 1;
	if (i - 1 >= 0)
		grid2[i - 1][j] += 1;
	if (i + 1 < 3)
		grid2[i + 1][j] += 1;
}

/**
 * add_piles - Computes the sum of two 3 by 3 int arrays into grid1
 * @grid1 : the first grid (3 by 3 array of ints)
 * @grid2 : the second grid (3 by 3 array of ints)
 *
 * Return: nothing
 */
void add_piles(int grid1[3][3], int grid2[3][3])
{
	int i = 0;
	int j = 0;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			grid1[i][j] += grid2[i][j];
			grid2[i][j] = 0;
		}
	}
}

/**
 * _print_grid - Print 3x3 grid
 * @grid: 3x3 grid
 *
 * Return: nothing
 */
void _print_grid(int grid[3][3])
{
	int i, j;

	printf("=\n");
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (j)
				printf(" ");
			printf("%d", grid[i][j]);
		}
		printf("\n");
	}
}

/**
 * check_instability - Check stability of a 3x3 grid
 * @grid: 3x3 grid
 *
 * Return: 0 if stable, 1 if unstable
 */
int check_instability(int grid[3][3])
{
	int i = 0;
	int j = 0;

	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			if (grid[i][j] > 3)
				return (1);

	return (0);
}
