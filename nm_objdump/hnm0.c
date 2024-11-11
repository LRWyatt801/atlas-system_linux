#include "hnm.h"

/**
 * main - Entry point hnm
 * @argc: argument count
 * @argv: argument vector
 *
 * Copycat function of the GNU nm
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */

int main(int argc, char **argv)
{
	elf_fmngr_t elf_fmngr;
	int i;

	elf_fmngr.prog_name = argv[0];

	/* loop for all input files to be printed */
	for(i = 0; i < argc; i++)
	{
		if (argc == 1)
			elf_fmngr.filename = "a.out";
		else
		{
			if (i == 0)
				continue;
			elf_fmngr.filename = argv[i];
		}
		if (init_elf_fmngr(&elf_fmngr) == EXIT_FAILURE)
			return (EXIT_FAILURE);

		close_mapped_file(&elf_fmngr);	
	}
	return (EXIT_SUCCESS);
}