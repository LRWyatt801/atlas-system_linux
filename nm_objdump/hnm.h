#ifndef _HNM_H
#define _HNM_H

/***** LIBRARYS *****/

#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>


/****** STRUCTS ******/

/**
 * struct elf_fmngr_s - struct that contains neccesarry variable for ELF file
 * @prog_name: name of program
 * @filename: name of ELF file
 * @fd: file discriptor
 * @fsize: size of ELF file
 * @ehdr: pointer to ELF header
 * @shdrs: pointer to first section header
 * @sym_shdr: pointer to symbol table section header
 * @sym_table: pointer to start of symbol table
 * @sym_count: total count of symbols in table
 * @str_table: pointer to start of string table
 */

typedef struct elf_fmngr_s
{
    char *prog_name;
    char *filename;
    int fd;
    size_t fsize;
    Elf64_Ehdr *ehdr;
    Elf64_Shdr *shdrs;
    Elf64_Shdr *sym_shdr;
    Elf64_Sym *sym_table;
    size_t sym_count;
    char *str_table;
} elf_fmngr_t;

/****** PROTOTYPES ******/

typedef void (*sym_action_t)(elf_fmngr_t *reader, Elf64_Sym *symbol);
typedef int (*sym_filter_t)(elf_fmngr_t *reader, Elf64_Sym *symbol);

/* FILE_MNGR.C */

int init_fmngr(elf_fmngr_t *elf_fmngr);
void SymbolReader_ProcessSymbols(elf_fmngr_t *reader, sym_action_t action,
	sym_filter_t filter);
void close_mapped_file(elf_fmngr_t *elf_fmngr);

#endif /* _HNM_H */