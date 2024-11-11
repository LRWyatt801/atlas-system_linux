#ifndef _HNM_H
#define _HNM_H

/***** LIBRARYS *****/

#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


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

#endif /* _HNM_H */