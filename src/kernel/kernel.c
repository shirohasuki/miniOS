
#include "platform.h"
#include "minilib.h"

#include "include/kernel.h"
#include "include/test.h"

extern void os_main(void);

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
  // task_test();
  // exception_test();
  // external_interrupt_test();
  // preemptive_task_test();
  // syscall_test();
  // timer_test();
  // lock_test();
  
  os_main();
  schedule();

  while (1) { 
    printf("should not be here\n"); 
    task_delay(1000);
  }
}