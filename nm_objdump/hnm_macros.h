#ifndef _HNM_MACROS_H
#define _HNM_MACROS_H

#include <elf.h>

#define OFFSET(ptr, n) ((char *)(ptr) + (n))
#define SECTION_HEADERS(ehdr) ((Elf64_Shdr *)OFFSET((ehdr), (ehdr)->e_shoff));
#define SECTION_COUNT(ehdr) ((uint64_t)(ehdr)->e_shnum)
#define SYMBOL_COUNT(sh) ((uint64_t)(sh)->sh_size / sizeof(Elf64_Sym))


#endif /*_HNM_MACROS_H*/