#include "hreadelf.h"

/**
 * main - entry point for program
 * @argc: number of arguments
 * @argv: array of arguments
 *
 * Return: 0 on success, 1 on failure
 */

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
	elf_file->class = elf_file->elfheader.v32->e_ident[EI_CLASS];
	print_elf_hdr(elf_file);
	elf_close(elf_file);
	return (EXIT_SUCCESS);
}
