#include "sandpiles.h"
#include <stdbool.h>

/**
 * print_grid - Prints a 3x3 grid
 * @grid: 3x3 grid to print
 */
int is_stable(int grid[3][3])
{
	int i, j;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (grid[i][j] > 3)
			{
				return (false);
			}
		}
	}
	return (true);
}
/**
 * is_stable - Checks if a grid is stable
 * @grid: 3x3 grid
 *
 * Return: 1 if stable, 0 otherwise
 */
void topple(int grid[3][3], int grid_tmp[3][3])
{
	int i, j;

	/* cells need topple */
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (grid[i][j] > 3)
			{
				grid[i][j] -= 4;
				/* TOP topple */
				if (i > 0)
					grid_tmp[i - 1][j]++;
				/* BOTTOM topple */
				if (i < 2)
					grid_tmp[i + 1][j]++;
				/* LEFT topple */
				if (j > 0)
					grid_tmp[i][j - 1]++;
				/* RIGHT topple */
				if (j < 2)
					grid_tmp[i][j + 1]++;
			}
		}
	}
	sandpiles_sum(grid, grid_tmp);
}

/**
 * sandpiles_sum - Computes the sum of two sandpiles
 * @grid1: First 3x3 grid (result stored here)
 * @grid2: Second 3x3 grid
 */
void sandpiles_sum(int grid1[3][3], int grid2[3][3])
{
	int i, j;
	int grid_tmp[3][3];
	/* Add sandpiles */
	for (i = 0; i < 3; ++i)
	{
		for (j = 0; j < 3; ++j)
		{
			grid1[i][j] += grid2[i][j];
			grid_tmp[i][j] = 0;
		}
	}

	/* toppling until stable */
	while (!is_stable(grid1))
	{
		printf("=\n");
		print_grid(grid1);
		topple(grid1, grid_tmp);
	}
}

/**
 * print_grid- print grid
 * @grid: grid[3][3] to print
 * Return: printed grid
 */
static void print_grid(int grid[3][3])
{
	int i, j;

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

