#include "logo.h"
#include "shell.h"
#include "minilib.h"

static void welcome(const char *logo) {
  printf("%s", logo);
  printf("For help, type \"help\"\n");
}

void init_shell() {
	welcome(logo);
  busybox_mainloop();
}
