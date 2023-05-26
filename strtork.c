#include "prototyp.h"
#include <stdio.h>
#include <string.h>

/**
* strtokk - Custom implementation of strtok function
* @str: The string to tokenize
* @delim: The delimiter characters
*
* Return: A pointer to the next token found in the string
*/
char *strtokk(char *str, const char *delim)
{
static char *buffer;
char *token_start;

if (str != NULL)
{
buffer = str;
}

if (buffer == NULL)
{
return (NULL);
}

token_start = buffer;
buffer = strpbrk(buffer, delim);

if (buffer != NULL)
{
*buffer++ = '\0';
}

return (token_start);
}

