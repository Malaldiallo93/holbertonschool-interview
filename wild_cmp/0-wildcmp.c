#include "holberton.h"
#include <stdio.h>

/**
 * wildcmp - compare two strings
 * @s1: string 1
 * @s2: string 2
 * Return: 1 if the strings can be considered identical, otherwise return 0
*/

int wildcmp(char *s1, char *s2)
{
/* id if same end */
if (*s1 == '\0' && *s2 == '\0')
return (1);

/* if char s2 is '*' */
if (*s2 == '*')
{
/* if '*' last char of s2 */
if (*(s2 + 1) == '\0')
return (1);

/* recursiv call or next char */
if (*s1 == '\0')
return (wildcmp(s1, s2 + 1));
return (wildcmp(s1 + 1, s2) || wildcmp(s1, s2 + 1));
}

/* If same char for s1 and s2 */
if (*s1 == *s2)
return (wildcmp(s1 + 1, s2 + 1));

/* different string*/
return (0);
}
