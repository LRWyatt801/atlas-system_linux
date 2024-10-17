#ifndef HREADELF_H
#define HREADELF_H

/****** LIBRARIES ******/

#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

/****** MACROS ******/

/****** STRUCTS or UNIONS ******/

/**
 * union elf_hdr_u - union for ELF header
 * @v32: Cast as `Elf32_Ehdr *`
 * @v64: Cast as `Elf64_Ehdr *`
 * @addr: void pointer
 */

typedef union elf_hdr_u
{
	Elf32_Ehdr *v32;
	Elf64_Ehdr *v64;
	void *addr;
} elf_hdr_t;

/**
 * struct elf_fmgr_s - a Struct containing necessary variables for ELF File
 * @elfheader: ELF header
 * @fsize: size of file
 * @class: Class of ELF file
 * @fd: file descriptor for open file
 */

typedef struct elf_fmgr_s
{
	elf_hdr_t elfheader;
	size_t fsize;
	int class;
	int fd;
} elf_fmgr_t;

/****** PROTOTYPES ******/

/* HREADELF.C */

/* MEM_MGR.C */

elf_fmgr_t *open_file(char *filename);
void elf_close(elf_fmgr_t *filemgr);

/* PRINT_MGR.C */

void print_elf_hdr(elf_fmgr_t *filemgr);
char *getelfosabi(elf_fmgr_t *elf_file);
char *getelftype(elf_fmgr_t *elf_file);
char *getelfmachine(elf_fmgr_t *elf_file);

#endif /*HREADELF_H*/
