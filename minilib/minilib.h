#ifndef MINILIB_H
#define MINILIB_H

#include "types.h"
#include <stddef.h>
#include <stdarg.h>

// printf
int printf(const char *s, ...);
void panic(char *s);

// string
char *strcpy(char *dst, const char *src);
char *strncpy(char *dst, const char *src, size_t n);
char *strcat(char *dst, const char *src);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);
size_t strlen(const char *s);
char *strtok(char *str, const char *delim);
char *strchr(const char *s, int c);

#endif /* MINILIB_H */
