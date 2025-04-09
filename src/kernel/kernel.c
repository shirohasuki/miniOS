
#include "platform.h"
#include "minilib.h"

#include "include/test.h"

void start_kernel(void) {
  uart2_init();
  printf("Hello, miniOS!\n");

  page_test();

  // init_shell();

  while (1) {}
}