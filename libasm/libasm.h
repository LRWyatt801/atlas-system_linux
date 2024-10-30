#ifndef __LIBASM_H
#define __LIBASM_H

#include <stdio.h>

/****** Prototypes ******/

void *asm_memcpy(void *dest, const void *src, size_t n);
size_t asm_putc(int c);
size_t asm_puts(const char *str);
char *asm_strchr(const char *s, int c);
int asm_strcasecmp(const char *s1, const char *s2);
int asm_strcmp(const char *s1, const char *s2);
size_t asm_strlen(const char *str);
int asm_strncasecmp(const char *s1, const char *s2, size_t n);
int asm_strncmp(const char *s1, const char *s2, size_t n);
char *asm_strstr(const char *haystack, const char *needle);

#endif
