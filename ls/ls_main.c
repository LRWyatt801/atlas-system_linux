#include "list.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    dir_lister_t parser;
    const char *directory_path = NULL;

    if (argc == 1)
        directory_path = ".";
    else
        directory_path = argv[1];

    directory_lister_init(&parser, directory_path);

    print_dir(&parser);
    close_dir(&parser);
    return(0);
}