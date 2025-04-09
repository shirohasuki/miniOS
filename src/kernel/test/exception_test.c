#include "trap.h"
#include "minilib.h"
#include "test.h"

void exception_test() {
  printf("===Exception Test Start===\n");
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
  printf("===Exception Test End===\n");
}
