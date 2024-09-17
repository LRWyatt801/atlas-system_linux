#include "list.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int print_oneperline(dir_lister_t *parser)
{
    (void)parser;
    printf("one perline\n");
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
