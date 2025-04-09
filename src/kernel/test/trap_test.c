#include "trap.h"
#include "minilib.h"
#include "test.h"

void trap_test() {
  printf("===Trap Test Start===\n");
  /*
   * Synchronous exception code = 4
   * Load address misaligned
   */
  int a = *(int *)0xFFFFFFF;

  /*
   * Synchronous exception code = 5
   * Load access fault
   */
  // int a = *(int *)0xFFFFFFC;
  printf("a = %d\n", a);

  printf("back from trap!\n");
  printf("===Trap Test End===\n");
}
