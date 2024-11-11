#include "hnm.h"
#include "hnm_macros.h"

#include <sys/mman.h>
#include <sys/stat.h>

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
	memset(elf_fmngr, 0, sizeof(elf_fmngr));
}
