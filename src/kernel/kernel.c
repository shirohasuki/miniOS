
#include "platform.h"
#include "minilib.h"

#include "include/kernel.h"
#include "include/test.h"

void start_kernel(void) {
  rcc_init();
  uart2_init();
  printf("Hello, miniOS!\n");

  page_init();
  trap_init();
  pfic_init();
  timer_init();
  
  sched_init();

  /* test case */
  // page_test();
  task_test();
  // exception_test();
  // external_interrupt_test();

  while (1) { printf("should not be here\n"); }
}