#include <stdlib.h>
#include <stdio.h>
#include "slide_line.h"



/**
 * slide_line_left - Slide and merge an array of integers to the left
 * @line: Pointer to the array of integers
 * @size: Number of elements in @line
 */
void slide_line_left(int *line, size_t size)
{
	unsigned long int i, j;

	for (i = 0, j = 1; j < size; j++)
	{
		if (line[j] != 0)
		{
			if (line[i] == 0)
			{
				line[i] = line[j];
				line[j] = 0;
			}
			else if (line[i] == line[j])
			{
				line[i] *= 2;
				line[j] = 0;
				i++;
			}
			else
			{
				i++;
				if (i != j)
				{
					line[i] = line[j];
					line[j] = 0;
				}
			}
		}
	}
}

/**
 * slide_line_right - Slide and merge an array of integers to the right
 * @line: Pointer to the array of integers
 * @size: Number of elements in @line
 */
void slide_line_right(int *line, size_t size)
{
	int i, j;

	for (i = size - 1, j = size - 2; j >= 0; j--)
	{
		if (line[j] != 0)
		{
			if (line[i] == 0)
			{
				line[i] = line[j];
				line[j] = 0;
			}
			else if (line[i] == line[j])
			{
				line[i] *= 2;
				line[j] = 0;
				i--;
			}
			else
			{
				i--;
				if (i != j)
				{
					line[i] = line[j];
					line[j] = 0;
				}
			}
		}
	}
}


/**
 * slide_line - Slide and merge an array of integers to the left
 *			or to the right
 * @line: pointer to the array of integers
 * @size: Number of elements in @line
 * @direction: SLIDE_LEFT or SLIDE_RIGHT
 * Return: 1 if success, or 0 upon failure
 */

int slide_line(int *line, size_t size, int direction)
{
	/* Failure : Invalid direction */
	if (direction != SLIDE_LEFT && direction != SLIDE_RIGHT)
		return (0);

	/* Nothing to slide or merge */
	if (size < 2)
		return (1);
	/* direction == SLIDE_LEFT */
	if (direction == SLIDE_LEFT)
	{
		slide_line_left(line, size);
	}
	/* direction == SLIDE_RIGHT */
	else
	{
		slide_line_right(line, size);
	}

	/* SUCCESS */
	return (1);
}

