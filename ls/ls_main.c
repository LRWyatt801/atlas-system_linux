#include "list.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    dir_lister_t parser;
    const char *directory_path = ".";

    directory_lister_init(&parser, directory_path);

    print_dir(&parser);
    return(0);
}