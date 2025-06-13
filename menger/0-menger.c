#include <stdio.h>
#include <math.h>
#include "menger.h"

/**
 * draw_char - Draws the right character at the given position coordinates
 * @row: The row index.
 * @col: The column index.
 * @size: The current size of the grid being processed.
 */
void draw_char(unsigned int row, unsigned int col, unsigned int size)
{
	while (size > 0)
	{
		if ((row / size) % 3 == 1 && (col / size) % 3 == 1)
		{
			printf(" ");
			return;
		}
		size /= 3;
	}
	printf("#");
}

/**
 * menger - Draws a 2D Menger Sponge of the given level.
 * @level: The level of the Menger Sponge.
 */
void menger(int level)
{
	unsigned int size, row, col;

	if (level < 0)
	{
		return;
	}

	size = pow(3, level);
	for (row = 0; row < size; row++)
	{
		for (col = 0; col < size; col++)
		{
			draw_char(row, col, size);
		}
		printf("\n");
	}
}
