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
    (void)parser;
    printf("all\n");
    return (0);
}

int printAll_notcurnt(dir_lister_t *parser)
{
    (void)parser;
    printf("ALL not curnt\n");
    return (0);
}

int printlongformat(dir_lister_t *parser)
{
    (void)parser;
    printf("long format\n");
    return (0);
}
