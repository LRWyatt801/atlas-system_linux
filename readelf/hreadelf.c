#include "hreadelf.h"

int main(int argc, char **argv)
{
    elf_fmgr_t *elf_file;

    if (argc != 2)
    {
        fprintf(stderr, "USAGE: 0-hreadelf <filename>\n");
        return (EXIT_FAILURE);
    }

    elf_file = open_file(argv[1]);
    if (!elf_file)
        return (EXIT_FAILURE);
    printf("elf_file opened\n");
    if (elf_file->elfheader.v64->e_ident[EI_CLASS] == ELFCLASS64)
        printf("class is 64bit\n");

    elf_close(elf_file);
    return (EXIT_SUCCESS);
}
