#include "sort.h"

/**
 * copy_array - Copies elements from source array to destination array
 * @dest: The destination array
 * @src: The source array
 * @start: Starting index in the source array
 * @end: Ending index in the source array
 */
void copy_array(int *dest, int *src, size_t start, size_t end)
{
	size_t i;

	for (i = start; i <= end; i++)
		dest[i] = src[i];
}

/**
 * merge - Merges two sorted sub-arrays into one sorted array
 * @array: The original array being sorted
 * @temp: A temporary array used for merging
 * @left: Start index of the left sub-array
 * @mid: End index of the left sub-array (mid + 1 is start of right sub-array)
 * @right: End index of the right sub-array
 */
void merge(int *array, int *temp, size_t left, size_t mid, size_t right)
{
	size_t i = left, j = mid + 1, k = left;

	/* Merge the two halves into temp[] */
	while (i <= mid && j <= right)
	{
		if (array[i] <= array[j])
			temp[k++] = array[i++];
		else
			temp[k++] = array[j++];
	}

	/* Copy the remaining elements of left sub-array (if any) */
	while (i <= mid)
		temp[k++] = array[i++];

	/* Copy the remaining elements of right sub-array (if any) */
	while (j <= right)
		temp[k++] = array[j++];

	/* Copy back the merged elements into the original array */
	copy_array(array, temp, left, right);
}

/**
 * print_subarrays - print the left and right sub-arrays being merged
 * @array: The original array
 * @left: The start index of the left sub-array
 * @mid: The end index of the left sub-array
 * @right: The end index of the right sub-array
 */
void print_subarrays(int *array, size_t left, size_t mid, size_t right)
{
	printf("Merging...\n[left]: ");
	print_array(&array[left], mid - left + 1);
	printf("[right]: ");
	print_array(&array[mid + 1], right - mid);
}

/**
 * merge_sort_recursive - recursively sorts an array
 * @array: The array to sort
 * @temp: A temporary array used for merging
 * @left: Start index of the sub-array
 * @right: End index of the sub-array
 */
void merge_sort_recursive(int *array, int *temp, size_t left, size_t right)
{
	if (left < right)
	{
		size_t mid = left + (right - left + 1) / 2 - 1;

		/* Sort the left half */
		merge_sort_recursive(array, temp, left, mid);

		/* Sort the right half */
		merge_sort_recursive(array, temp, mid + 1, right);

		/* Print the sub-arrays before merging */
		print_subarrays(array, left, mid, right);

		/* Merge the sorted halves */
		merge(array, temp, left, mid, right);

		/* Print the merged array */
		printf("[Done]: ");
		print_array(&array[left], right - left + 1);
	}
}

/**
 * merge_sort - Sorts an array of ints with the top-down merge sort algorithm
 * @array: The array of integers to sort
 * @size: The size of the array
 */
void merge_sort(int *array, size_t size)
{
	if (array == NULL || size < 2)
		return;

	/* Allocate temp array for merging, then verify the allocation */
	int *temp = malloc(size * sizeof(int));

	if (temp == NULL)
		return;

	merge_sort_recursive(array, temp, 0, size - 1);

	/* Free the temporary array after sorting */
	free(temp);
}
