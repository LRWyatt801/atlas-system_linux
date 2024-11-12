#include "hnm.h"
#include "hnm_macros.h"

static void print_value_and_str(elf_fmngr_t *reader, Elf64_Sym *symbol);

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
		if (init_fmngr(&elf_fmngr) == EXIT_FAILURE)
			return (EXIT_FAILURE);

		/* Process all symbol-table entries with `print_value_and_str` */
	SymbolReader_ProcessSymbols(&elf_fmngr, print_value_and_str, NULL);

		close_mapped_file(&elf_fmngr);	
	}
	return (EXIT_SUCCESS);
}

/**
 * print_value_and_str - Callback for `SymbolReader_ProcessSymbols`
 * @reader: Pointer to `SymbolReader` struct
 * @sym: Pointer to symbol-table entry
 */
static void
print_value_and_str(elf_fmngr_t *reader, Elf64_Sym *symbol)
{
	const char *str = SYMBOL_STRING(reader->str_table, symbol);
	printf("%016lx %s\n", symbol->st_value, str);
}