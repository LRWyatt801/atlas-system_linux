#include "list.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int print_oneperline(dir_lister_t *parser)
{
    if (!parser)
        return (-1);

    while (next_entry(parser))
    {
        if (*parser->current_entry->d_name != '.')
            printf("%s\n", parser->current_entry->d_name);
    }
    return (0);
}

int printall(dir_lister_t *parser)
{
    if (!parser)
        return (-1);

    while (next_entry(parser))
    {
        printf("%s ", parser->current_entry->d_name);
    }
    printf("\n");
    return (0);
}

int printAll_notcurnt(dir_lister_t *parser)
{
    if (!parser)
        return (-1);

    while (next_entry(parser))
    {
        if (_strcmp(parser->current_entry->d_name, ".") == 0)
            continue;
        else if (_strcmp(parser->current_entry->d_name, "..") == 0)
            continue;
        else
            printf("%s ", parser->current_entry->d_name);
    }
    printf("\n");
    return (0);
}

int printlongformat(dir_lister_t *parser)
{
    (void)parser;
    printf("long format\n");
    return (0);
}

/***** STRING TOOLS *****/

/**
 * _strcmp - compares two strings
 * @s1: string to compare
 * @s2: string to compare
 *
 * Return: 0 if s1 == s2
 *	   - value if s1 < s2
 *	   + value if s1 > s2
 */

int _strcmp(char *s1, char *s2)
{
    for (; *s1 == *s2; s1++, s2++)
        if (*s1 == '\0')
            return (0);
    return (*s1 - *s2);
}