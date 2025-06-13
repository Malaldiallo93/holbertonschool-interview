#include "substring.h"

/**
 * build_word_count - builds a word frequency map
 * @words: the array of words
 * @nb_words: the number of elements in the words array
 *
 * Return: a pointer to the frequency map, or NULL on failure
 */
static int *build_word_count(char const **words, int nb_words)
{
	int *word_count = calloc(nb_words, sizeof(int));

	if (!word_count)
		return (NULL);

	for (int i = 0; i < nb_words; i++)
	{
		for (int j = 0; j < nb_words; j++)
		{
			if (strcmp(words[i], words[j]) == 0)
				word_count[i]++;
		}
	}

	return (word_count);
}

/**
 * check_substring - checks if a substring is valid
 * @s: the string to scan
 * @start: starting index of the substring in s
 * @words: the array of words all substrings must be a concat. arrangement of
 * @nb_words: the number of elements in the words array
 * @word_len: the length of each word in words
 * @word_count: frequency map of words in the input array
 *
 * Return: 1 if valid, 0 otherwise
 */
static int check_substring(char const *s, int start, char const **words,
	int nb_words, int word_len, int *word_count)
{
	int *current_count = calloc(nb_words, sizeof(int));

	if (!current_count)
		return (0);

	for (int j = 0; j < nb_words; j++)
	{
		char const *segment = s + start + j * word_len;
		int k;

		for (k = 0; k < nb_words; k++)
		{
			if (strncmp(segment, words[k], word_len) == 0)
			{
				current_count[k]++;

				if (current_count[k] > word_count[k])
				{
					free(current_count);
					return (0);
				}
				break;
			}
		}

		if (k == nb_words)
		{
			free(current_count);
			return (0);
		}
	}

	free(current_count);
	return (1);
}

/**
 * find_substring - finds all possible substrings containing a list of words
 * @s: the string to scan
 * @words: the array of words all substrings must be a concat. arrangement of
 * @nb_words: the number of elements in the words array
 * @n: address at which to store the number of elements in the returned array
 *
 * Return: an array of indices in s at which a substring was found, or NULL
 */
int *find_substring(char const *s, char const **words, int nb_words, int *n)
{
	if (!s || !words || !*words || nb_words == 0 || !n)
		return (NULL);

	int word_len = strlen(words[0]);
	int s_len = strlen(s);
	int substr_len = word_len * nb_words;
	int *indices = malloc(s_len * sizeof(*indices));
	int found_count = 0;

	if (!indices)
		return (NULL);

	/* Build word frequency map */
	int *word_count = build_word_count(words, nb_words);

	if (!word_count)
	{
		free(indices);
		return (NULL);
	}

	for (int i = 0; i <= s_len - substr_len; i++)
		if (check_substring(s, i, words, nb_words, word_len, word_count))
			indices[found_count++] = i;

	free(word_count);
	if (found_count == 0)
	{
		free(indices);
		*n = 0;
		return (NULL);
	}

	*n = found_count;
	return (indices);
}
