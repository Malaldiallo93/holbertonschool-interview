#include <stdlib.h>
#include <stdio.h>
#include "regex.h"

/**
 * regex_match - Checks if a given pattern matches a given string
 * @str: The string to scan
 * @pattern: The regular expression pattern
 *
 * Return: 1 if the pattern matches the string, 0 otherwise
 */
int regex_match(char const *str, char const *pattern)
{
    /* If the pattern is empty, check if the string is also empty */
    if (*pattern == '\0')
        return (*str == '\0');

    /* Check if the first character matches */
    int first_match = (*str && (*str == *pattern || *pattern == '.'));

    /* Handle '*' which means zero or more occurrences of the preceding character */
    if (*(pattern + 1) == '*')
    {
        return (regex_match(str, pattern + 2) || /* Ignore '*' pattern */
                (first_match && regex_match(str + 1, pattern))); /* Match and move */
    }
    else
    {
        return (first_match && regex_match(str + 1, pattern + 1));
    }
}
