#include <stdio.h>
#include <stddef.h>
#include "sort.h"

/**
 * getMax - Get the maximum value in an array
 * @array: The array to search
 * @size: The size of the array
 * Return: Maximum value in the array
 */
int getMax(int array[], size_t size)
{
size_t i;
int max;
max = array[0];

for (i = 1; i < size; i++)
{
if (array[i] > max)
max = array[i];
}
return (max);
}

/**
 * countSort - Sort an array based on a significant digit
 * @array: The array to sort
 * @size: The size of the array
 * @exp: The significant digit to sort on
 */
void countSort(int array[], size_t size, int exp)
{
/* output array */
int *output = malloc(sizeof(int) * size);
size_t i;
int count[10] = {0};

for (i = 0; i < size; i++)
count[(array[i] / exp) % 10]++;

for (i = 1; i < 10; i++)
count[i] += count[i - 1];

for (i = size - 1; (int)i >= 0; i--)
{
output[count[(array[i] / exp) % 10] - 1] = array[i];
count[(array[i] / exp) % 10]--;
}

for (i = 0; i < size; i++)
array[i] = output[i];

free(output);
}

/**
* radix_sort - Function that sorts arr[] using Radix Sort
* @array: The array to sort
* @size: The size of the array
*/
void radix_sort(int *array, size_t size)
{
int m, exp;

if (!array || size <= 1)
return;

m = getMax(array, size);

for (exp = 1; m / exp > 0; exp *= 10)
{
countSort(array, size, exp);
print_array(array, size);
}
}
