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
