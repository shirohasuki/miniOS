#include "minilib.h"
#include "syscall.h"

#define DELAY 500

static void user_task0(void) {
  printf("Task 0: Created!\n");

  unsigned int archid = -1;

  /*
   * if syscall is supported, this will trigger exception, 
   * code = 2 (Illegal instruction)
   */
  // archid = r_marchid();
  // printf("hart id is %d\n", archid);

// #ifdef CONFIG_SYSCALL
  int ret = -1;
  ret = getarchid(&archid);
  // ret = getarchid(NULL);
  if (ret) {
    printf("getarchid() failed, return: %d\n", ret);
  } else {
    printf("system call returned, marchid id 0x%X\n", archid);
  }
// #endif

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

void syscall_test(void) {
  printf("============Syscall Test Start============\n");
  task_create(user_task0);
  task_create(user_task1);
  schedule();
  printf("============Syscall Test End============\n");
}
