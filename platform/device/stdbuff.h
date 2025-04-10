#ifndef _STDBUFF_H
#define _STDBUFF_H

#include "types.h"

#define STDIO_BUFFER_SIZE 1024

typedef struct {
    char buffer[STDIO_BUFFER_SIZE];
    uint32_t head;
    uint32_t tail;
    uint32_t count;
} stdio_queue_t;

void stdio_init(void);
void stdio_pushc(char c);
char stdio_popc(void);
uint32_t stdio_available(void);      // Check if there's a complete line
uint32_t stdio_has_char(void);       // Check if there's any character available
uint32_t stdio_read(char *buf, uint32_t size);
uint32_t stdio_readline(char *buf, uint32_t size);

#endif /* _STDBUFF_H */ 