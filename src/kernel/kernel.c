
#include "platform.h"

void start_kernel(void) {
  uart_init();
  uart_puts("Hello, miniOS!\r\n");

  while (1) {}
}