#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @s: string s
 * Return: length of string
 */
int _strlen(char *s)
{
	char *p = s;

	while (*s)
	{
		s++;
	}
	return (s - p);
}

/**
 * _strcat - concatenates two strings
 * @dest: copy destination
 * @src: copy source
 * Return: concatenated string
 */
char *_strcat(char *dest, char *src)
{
	char *ptr = dest + _strlen(dest);

	while (*src)
	{
		*ptr++ = *src++;
	}
	*ptr = 0;
	return (dest);
}

/**
 * _strcmp - compares two strings
 * @s1: string 1
 * @s2: string 2
 * Return: 1 if true, 0 if false
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1)
	{
		if (*s1 != *s2)
		{
			break;
		}
		s1++;
		s2++;
	}

	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/**
 * _strdup - returns a pointer to a newly allocated space in memory,
 * which contains a copy of the string given as a parameter.
 * @str: string to be copied
 * Return: copied string
 */
char *_strdup(char *str)
{
	int i, len;
	char *copy;

	if (!str)
	{
		return (NULL);
	}
	len = _strlen(str);
	copy = malloc(sizeof(char) * len + 1);
	if (!copy)
	{
		perror("Malloc failed\n");
		exit(errno);
		free(copy);
	}
	for (i = 0; i < len; i++)
	{
		copy[i] = str[i];
	}
	copy[i] = 0;
	return (copy);
}

/**
 * *_strcpy - copies the string pointed to by src,
 * including the terminating null byte
 * @dest: copied string
 * @src: string to be copied
 * Return: pointer to new copied string
 */
char *_strcpy(char *dest, char *src)
{
	char *ptr = dest;

	while (*src)
	{
		*dest++ = *src++;
	}
	*dest = 0;
	return (ptr);
}

/**
 * _strtok - tokenizes strings at delimiter
 * @str: input string
 * @delim: delimiter
 * Return: pointer to start of string
 */

char *_strtok(char *str, char *delim)
{
	static char *lastptr;
	char ch;

	if (str == NULL)
	{
		str = lastptr;
	}
	do {
		ch = *str++;
		if (!ch)
		{
			return (NULL);
		}
	} while (_strchr(delim, ch));
	str--;
	lastptr = str + _strcspn(str, delim);
	if (*lastptr)
	{
		*lastptr++ = 0;
	}
	return (str);
}

/**
 * _strcspn - returns first occurence of any char in
 * second string in first string
 * @string: input string to search
 * @chars: input chars to check
 * Return: pointer to first match
 */
int _strcspn(char *string, char *chars)
{
	char ch;
	char *ptr, *_str;

	for (_str = string, ch = *_str; ch; _str++, ch = *_str)
	{
		for (ptr = chars; *ptr; ptr++)
		{
			if (ch == *ptr)
			{
				return (_str - string);
			}
		}
	}

	return (_str - string);
}

/**
 * _strchr - locates a character in a string
 * @s: string to be searched
 * @c: target char
 * Return: pointer to first occurrence of c or
 * NULL if char not found
 */
char *_strchr(char *s, char c)
{
	char x;

	while (true)
	{
		x = *s++;
		if (x == c)
		{
			return (s - 1);
		}
		if (!x)
		{
			return (NULL);
		}
	}
}
