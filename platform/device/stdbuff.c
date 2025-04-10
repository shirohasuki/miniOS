/*
 * Standard Input Output Buffer
 * This is not a real hardware buffer, but a simple implementation of stdio.
 * This helps shell to work.
 */
#include "stdbuff.h"
#include "../platform.h"

static stdio_queue_t stdio_queue;

void stdio_init(void) {
  stdio_queue.head = 0;
  stdio_queue.tail = 0;
  stdio_queue.count = 0;
}

void stdio_pushc(char c) {
  if (stdio_queue.count < STDIO_BUFFER_SIZE) {
    stdio_queue.buffer[stdio_queue.tail] = c;
    stdio_queue.tail = (stdio_queue.tail + 1) % STDIO_BUFFER_SIZE;
    stdio_queue.count++;
  }
}

char stdio_popc(void) {
  if (stdio_queue.count == 0) {
    return -1;
  }
  
  char c = stdio_queue.buffer[stdio_queue.head];
  stdio_queue.head = (stdio_queue.head + 1) % STDIO_BUFFER_SIZE;
  stdio_queue.count--;
  return c;
}

uint32_t stdio_read(char *buf, uint32_t size) {
  uint32_t read_count = 0;
  
  while (read_count < size && stdio_queue.count > 0) {
    buf[read_count++] = stdio_queue.buffer[stdio_queue.head];
    stdio_queue.head = (stdio_queue.head + 1) % STDIO_BUFFER_SIZE;
    stdio_queue.count--;
  }
  
  return read_count;
}

uint32_t stdio_readline(char *buf, uint32_t size) {
  if (size == 0) {
    return 0;
  }

  uint32_t read_count = 0;
  uint32_t temp_head = stdio_queue.head;
  uint32_t temp_count = stdio_queue.count;
  
  // First check if there's a complete line
  while (temp_count > 0 && read_count < size - 1) {
    char c = stdio_queue.buffer[temp_head];
    temp_head = (temp_head + 1) % STDIO_BUFFER_SIZE;
    temp_count--;
    
    if (c == '\n') {
      // Found a complete line, start actual reading
      while (stdio_queue.count > 0 && read_count < size - 1) {
        c = stdio_queue.buffer[stdio_queue.head];
        stdio_queue.head = (stdio_queue.head + 1) % STDIO_BUFFER_SIZE;
        stdio_queue.count--;
        
        buf[read_count++] = c;
        if (c == '\n') {
          buf[read_count] = '\0';
          return read_count;
        }
      }
      break;
    }
  }
  
  return 0; // No complete line found
}

uint32_t stdio_has_char(void) {
  return stdio_queue.count > 0;
}

uint32_t stdio_available(void) {
  uint32_t temp_head = stdio_queue.head;
  uint32_t temp_count = stdio_queue.count;
  
  // Check if there's a complete line
  while (temp_count > 0) {
    if (stdio_queue.buffer[temp_head] == '\n') {
      return 1; // Complete line available
    }
    temp_head = (temp_head + 1) % STDIO_BUFFER_SIZE;
    temp_count--;
  }
  
  return 0; // No complete line available
} 