#include <stdlib.h>
#include <stdio.h>
#include "palindrome.h"

/**
 * is_palindrome - test if unsigned interger is a palindrome
 * @n: unsigned long int
 * Return: 1 if palindrome, 0 otherwise
 */
int is_palindrome(unsigned long n)
{
	unsigned long reversed = 0;
	unsigned long copy_n;
	int r;

	if (n == 0)
		return (1);

	copy_n = n;

	while (copy_n != 0)
	{
		r = copy_n % 10;
		reversed = reversed * 10 + r;
		copy_n /= 10;
	}

	if (n == reversed)
		return (1);
	else
		return (0);
}


