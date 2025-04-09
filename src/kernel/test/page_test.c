#include "minilib.h"
#include "../include/page.h"
#include "../include/test.h"

int global_init = 0x11111111;
const int global_const = 0x22222222;

void page_test(void) {
  printf("============Page Test Start============\n");

  static int static_var = 0x33333333;
  static int static_var_uninit;
  int auto_var = 0x44444444;

  printf("addr of global_init = %p\n", &global_init);
  printf("addr of global_const = %p\n", &global_const);
  printf("addr of static_var = %p\n", &static_var);
  printf("addr of static_var_uninit = %p\n", &static_var_uninit);
  printf("addr of auto_var = %p\n", &auto_var);

  void *p = page_alloc(2);
  printf("p = %p\n", p);
  page_free(p);
  printf("free p\n");

  void *p2 = page_alloc(3);
  printf("p2 = %p\n", p2);

  void *p3 = page_alloc(4);
  printf("p3 = %p\n", p3);

  printf("============Page Test End============\n");
}
