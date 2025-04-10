#include "minilib.h"
#include "context.h"


static void user_task0(void) {
  printf("Task 0: Created!\n");

  task_yield();
  printf("Task 0: I'm back!\n");
  while (1) {
    spin_lock();
    printf("Task 0: Begin...\n");
    for (int i = 0; i < 5; i++) {
      printf("Task 0: Running...\n");
      task_delay(2000);
    }
    printf("Task 0: End...\n");
    spin_unlock();
  }
}

static void user_task1(void) {
  printf("Task 1: Created!\n");
  while (1) {
    printf("Task 1: Begin...\n");
    for (int i = 0; i < 5; i++) {
      printf("Task 1: Running...\n");
      task_delay(2000);
    }
    printf("Task 1: End...\n");
  }
}

void lock_test(void) {
  printf("=======Lock Test Start=====\n");
  task_create(user_task0);
  task_create(user_task1);
  schedule();
  printf("=======Lock Test End=====\n");
}