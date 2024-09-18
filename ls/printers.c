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

int print_longlistfmt(dir_lister_t *parser)
{
    struct stat statbuf;
    longlistfmt_t longlist;
    const char *entry_name = NULL;
    const char *entry_path = NULL;

    entry_name = parser->current_entry->d_name;
    entry_path = path_join(parser->path, entry_name);

    if (lstat(entry_path, &statbuf) == -1)
        return (-1);

    longlistfmt_init(&longlist, entry_name, &statbuf);
    longlistfmt_print(&longlist);
    return (0);
}
