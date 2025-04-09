
#include "platform.h"
#include "minilib.h"

#include "include/kernel.h"
#include "include/test.h"

void start_kernel(void) {
  uart2_init();
  printf("Hello, miniOS!\n");

  page_init();
  sched_init();
  trap_init();

  // page_test();
  // task_test();
  exception_test();

  while (1) {}
}