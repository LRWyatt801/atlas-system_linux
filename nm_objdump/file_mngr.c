#include "hnm.h"
#include "hnm_macros.h"

#include <sys/stat.h>

static int parse_symbol_header(elf_fmngr_t *elf_fmngr);
static int dummy_filter(elf_fmngr_t *reader, Elf64_Sym *sym);

/**
 * init_fmngr - initializes the fmngr struct
 * @elf_fmngr: elf_fmngr struct that holds needed info for the program
 *
 * Return: 0 on success, 1 on failure
 */

int init_fmngr(elf_fmngr_t *elf_fmngr)
{
	void *fmap;
	struct stat statbuff;
	int fd;

	if (elf_fmngr->filename == NULL)
		return (EXIT_FAILURE);
	fd = open(elf_fmngr->filename, O_RDONLY);
	if (fd == -1)
	{
		fprintf(stderr, "%s: no such file exits", elf_fmngr->prog_name);
		return (EXIT_FAILURE);
	}
	if (fstat(fd, &statbuff) == -1)
	{
		close(fd);
		return (EXIT_FAILURE);
	}
	fmap = mmap(NULL, statbuff.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (fmap == MAP_FAILED)
	{
		close(fd);
		return (EXIT_FAILURE);
	}
	elf_fmngr->fd = fd;
	elf_fmngr->fsize = statbuff.st_size;
	elf_fmngr->ehdr = fmap;
	if (parse_symbol_header(elf_fmngr) == EXIT_FAILURE)
	{
		munmap(fmap, statbuff.st_size);
		close(fd);
		return (EXIT_FAILURE);
	}

	if (parse_symbol_header(elf_fmngr) == -1)
	{
		close_mapped_file(elf_fmngr);
		return (EXIT_FAILURE);
	}

	/* link symbol and string tables */
	elf_fmngr->sym_table = SYMBOL_TABLE(elf_fmngr->ehdr, elf_fmngr->sym_shdr);
	elf_fmngr->str_table = STRING_TABLE(elf_fmngr->ehdr, elf_fmngr->shdrs,
		elf_fmngr->sym_shdr);
	return (EXIT_SUCCESS);
}

/**
 * parse_symbol_header - Finds symbol-table section header and symbol count
 * @elf_fmngr: Pointer to `Symbolelf_fmngr` struct
 *
 * Return: `0` on success, `-1` on failure
 */

static int
parse_symbol_header(elf_fmngr_t *elf_fmngr)
{
	uint64_t i;

	/* assign section header address and find symbol-table header */
	elf_fmngr->shdrs = SECTION_HEADERS(elf_fmngr->ehdr);
	elf_fmngr->sym_shdr = NULL;

	for (i = 0; i < SECTION_COUNT(elf_fmngr->ehdr); ++i) {
		if (elf_fmngr->shdrs[i].sh_type == SHT_SYMTAB) {
			elf_fmngr->sym_shdr = elf_fmngr->shdrs + i;
			break;
		}
	}

	if (!elf_fmngr->sym_shdr)
		return (-1);

	elf_fmngr->sym_count = SYMBOL_COUNT(elf_fmngr->sym_shdr);
	return (0);
}

/**
 * SymbolReader_ProcessSymbols - Sequentially performs `action` on all symbols
 * @reader: Pointer to `SymbolReader` structure
 * @action: Pointer to symbol-processing function
 * @filter: Pointer to optional filter function, symbol processed when true
 */
void
SymbolReader_ProcessSymbols(elf_fmngr_t *reader, sym_action_t action,
	sym_filter_t filter)
{
	uint64_t i;

	if (!reader || !action)
		return;
	
	if (!filter)
		filter = dummy_filter;

	/* iterate over the symbol table entries */
	for (i = 0; i < reader->sym_count; ++i) {
		/* skip symbol if `filter` returns false */
		if (filter(reader, reader->sym_table + i)) {
			/* process symbol with `action` */
			action(reader, reader->sym_table + i);
		}
	}
}

/**
 * close_mapped_file - closes the mapped file
 * @elf_fmngr: elf_fmngr struct that holds needed info for the program
 *
 * Return: void
 */

void close_mapped_file(elf_fmngr_t *elf_fmngr)
{
	if (!elf_fmngr)
		return;
	munmap(elf_fmngr->ehdr, elf_fmngr->fsize);
	close(elf_fmngr->fd);
	memset(elf_fmngr, 0, sizeof(*elf_fmngr));
}

/**
 * dummy_filter - Dummy default filter for `SymbolReader_ProcessSymbols`
 * @reader: Pointer to `elf_fmngr_t` struct
 * @sym: Pointer to symbol-table entry
 *
 * Return: Always `1`
 */
static int
dummy_filter(elf_fmngr_t *reader, Elf64_Sym *sym)
{
	(void)reader;
	(void)sym;
	return (1);
}