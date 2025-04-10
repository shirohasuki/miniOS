// #include "app/minishell/include/shell.h"
#include "context.h"
#include "minilib.h"
static void user_task0(void) {
  printf("Task 0: Created!\n");
  while (1) {
    printf("Task 0: Running...\n");
    task_delay(2000);
  }
}

static void user_task1(void) {
  printf("Task 1: Created!\n"); 
  while (1) {
    printf("Task 1: Running...\n");
    task_delay(2000);
  }
}

void os_main(void) {
  task_create(user_task0);
  task_create(user_task1);

  // init_shell();
  // cmdbox_mainloop();
}
