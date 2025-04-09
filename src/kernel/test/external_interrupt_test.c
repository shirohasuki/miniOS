#include "test.h"
#include "context.h"
#include "minilib.h"

void external_interrupt_test() {
  printf("===External Interrupt Test Start===\n");
  printf("You can type something to test if external interrupt works.\n");
  // int i = 0;
  while (1) {
    // printf("Loop %d\n", i++);
    // task_delay(1000);
    // if (i > 100) { i = 0;}
  }
  printf("===External Interrupt Test End===\n");
}
