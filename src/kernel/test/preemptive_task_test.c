#include "context.h"
#include "minilib.h"

#define DELAY 1000

/* Task Test
 * first create task 0 and task 1
 * then task 0 and task 1 will be scheduled by the kernel
 * task 0 and task 1 will be running in turn
 */

static void user_task0(void) {
  printf("Task 0: Created!\n");
  while (1) {
    printf("Task 0: Running...\n");
    task_delay(DELAY);
  }
}

static void user_task1(void) {
  printf("Task 1: Created!\n"); 
  while (1) {
    printf("Task 1: Running...\n");
    task_delay(DELAY);
  }
}

void preemptive_task_test(void) {
  printf("============Task Test Start============\n");
  task_create(user_task0);
  task_create(user_task1);
  schedule();
  printf("============Task Test End============\n");
}
