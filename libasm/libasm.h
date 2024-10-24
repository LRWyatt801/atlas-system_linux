#ifndef __LIBASM_H
#define __LIBASM_H

#include <stdio.h>

/****** Prototypes ******/

char *asm_strchr(const char *s, int c);
int asm_strcmp(const char *s1, const char *s2);
size_t asm_strlen(const char *str);
int asm_strncmp(const char *s1, const char *s2, size_t n);

#endif
