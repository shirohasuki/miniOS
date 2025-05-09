#include "minilib.h"
#include "stimer.h"
#include "context.h"

struct userdata {
  int counter;
  char *str;
};

/* user must be global */
struct userdata person = {0, "user"};

void timer_func(void *arg) {
  if (arg == NULL)
    return;

  struct userdata *param = (struct userdata *)arg;

  param->counter++;
  printf("======> TIMEOUT: %s: %d\n", param->str, param->counter);
}

static void user_task0(void) {
  printf("Task 0: Created!\n");

  struct timer *t1 = timer_create(timer_func, &person, 3);
  if (t1 == NULL) {
    printf("timer_create() failed!\n");
  }
  struct timer *t2 = timer_create(timer_func, &person, 5);
  if (t2 == NULL) {
    printf("timer_create() failed!\n");
  }
  struct timer *t3 = timer_create(timer_func, &person, 7);
  if (t3 == NULL) {
    printf("timer_create() failed!\n");
  }

  while (1) {
    printf("Task 0: Running...\n");
    task_delay(1000);
  }
}

static void user_task1(void) {
  printf("Task 1: Created!\n");
  while (1) {
    printf("Task 1: Running...\n");
    task_delay(1000);
  }
}

void timer_test(void) {
  printf("=======Timer Test Start=====\n");
  task_create(user_task0);
  task_create(user_task1);
  schedule();
  printf("=======Timer Test End=====\n");
}
