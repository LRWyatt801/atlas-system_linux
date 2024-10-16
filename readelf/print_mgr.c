#include "hreadelf.h"

#define ELFPRTVER(elf_file) ((elf_file)->class == 1 ? \
		"elf_file->elfheader.v32" : "elf_file->elfheader.v64")
#define ELFCLASS(elf_file) ((elf_file)->class == 1 ? "ELF32" : "ELF64")
#define ELFDATA(elf_file) ((elf_file)->class == ELFCLASS32 ? \
		((elf_file)->elfheader.v32->e_ident[EI_DATA] == ELFDATA2LSB ? \
			"Two's complement, little-endian" : "Two's complement, big-endian") : \
		((elf_file)->elfheader.v64->e_ident[EI_DATA] == ELFDATA2LSB ? \
			"Two's complement, little-endian" : "Two's complement, big-endian"))
#define ELFVERSION(elf_file) \
	((elf_file)->class == ELFCLASS32 ? \
		((elf_file)->elfheader.v32->e_ident[EI_VERSION] == EV_CURRENT ? \
			"1 (current)" : "Unknown version") : \
		((elf_file)->elfheader.v64->e_ident[EI_VERSION] == EV_CURRENT ? \
			"1 (current)" : "Unknown version"))

/**
 * print_elf_hdr - prints ELF Header
 * @elf_file: struct containing necessary variables
 *
 * Return: n/a
 */

void print_elf_hdr(elf_fmgr_t *elf_file)
{
	int i;

	printf("ELF Header:\n");
	printf("\tMagic: ");
	for (i = 0; i < 16; i++)
		printf("%02x ", elf_file->elfheader.v64->e_ident[i]);
	printf("\n");
	printf("\tClass:                             %s\n",
		   ELFCLASS(elf_file));
	printf("\tData:                              %s\n",
		   ELFDATA(elf_file));
	printf("\tVersion:                           %s\n",
		   ELFVERSION(elf_file));
	printf("\tOS/ABI:                            %s\n",
		   getelfosabi(elf_file));
}

/**
 * getelfosabi - gets the os/abi information for an elf file
 * @elf_file: struct containing all necessary variables
 *
 * Return: OS/ABI str, otherwise NULL
 */

char *getelfosabi(elf_fmgr_t *elf_file)
{
	if (!elf_file)
		return NULL;
	
	switch(elf_file->elfheader.v64->e_ident[EI_OSABI])
	{
		case ELFOSABI_SYSV: return ("UNIX System V");
		default: return (NULL);
	}
}