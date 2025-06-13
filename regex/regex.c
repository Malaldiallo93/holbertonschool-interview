#include "regex.h"

/**
 * regex_match - Regex pattern matchin supporting '*' and '.' wildcards
 * @str: string 1
 * @pattern: string 2, can contain '.' and '*' wildcards
 *
 * Description: Regex matching must support the characters . and *
 *    - . matches any single character
 *    - * matches zero or more of the preceding character
 *
 * Return: 1 if the strings can be considered identical, otherwise return 0
 */
int regex_match(char const *str, char const *pattern)
{
	if (!*str && !*pattern)
		return (1);

	if (*str && *pattern == '*' && !*(pattern + 1))
		return (1);

	if (*str != *pattern && *pattern && *(pattern + 1) == '*')
		return (regex_match(str, pattern + 1));

	if (*pattern == '.' || *str == *pattern)
		return (regex_match(str + 1, pattern + 1));

	if (*pattern == '*')
	{
		if (regex_match(str, pattern + 1))
			return (1);
		if (*str && regex_match(str + 1, pattern))
			return (1);
	}

	return (0);
}
