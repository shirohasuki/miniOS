#include "../../app/minishell/include/shell.h"
#include "context.h"
#include "minilib.h"

static void user_task1(void) {
  printf("Task 1: Created!\n"); 
  while (1) {
    printf("Task 1: Running...\n");
    task_delay(2000);
  }
}

void os_main(void) {
  task_create(init_shell);
  task_create(user_task1);
}
