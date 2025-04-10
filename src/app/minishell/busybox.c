#include "utils/macro.h"
#include "readline.h"
#include "minilib.h"
#include "shell.h"
#include "kernel.h"


static char* rl_gets() {
  static char *line_read = NULL;
  line_read = readline("(miniOS) "); 

  if (line_read && *line_read) {
    add_history(line_read);
  }

  return line_read;
}

static int cmd_help(char *args);
static int cmd_lscpu(char *args);
static int cmd_free(char *args);
static int cmd_q(char *args);

static struct {
  const char *name;
  const char *description;
  int (*handler) (char *);
} cmd_table [] = {
  { "help"	, "Display informations about all supported commands", cmd_help  },
  { "lscpu"	, "Display information about the CPU", 								 cmd_lscpu },
  { "free"	, "Display information about the memory", 						 cmd_free  },
  { "q"			, "Exit MiniOS", 																			 cmd_q 		 },
};

#define NR_CMD ARRLEN(cmd_table)

static int cmd_help(char *args) {
	/* extract the first argument */
	char *arg = strtok(NULL, " ");
	int i;

	if (arg == NULL) {
		/* no argument given */
		printf("Common options:\n");
		for (i = 0; i < NR_CMD; i++) {
			printf("\t%-4s - %s\n", cmd_table[i].name, cmd_table[i].description);
		}
	} else {
		for (i = 0; i < NR_CMD; i++) {
			if (strcmp(arg, cmd_table[i].name) == 0) {
				printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
				return 0;
			}
		}
		printf("Unknown command '%s'\n", arg);
	}
	return 0;
}

static int cmd_lscpu(char *args) {
  unsigned int archid = -1;
	int ret = -1;
  ret = getarchid(&archid);
  if (ret) {
    printf("getarchid() failed, return: %d\n", ret);
  } else {
    printf("ChipID:%08x\r\n", archid);
  }
  return 0;
}

static int cmd_free(char *args) {
  printf("Memory info\n");
  printf("TEXT:   0x%x -> 0x%x\n", TEXT_START, TEXT_END);
  printf("RODATA: 0x%x -> 0x%x\n", RODATA_START, RODATA_END);
  printf("DATA:   0x%x -> 0x%x\n", DATA_START, DATA_END);
  printf("BSS:  	0x%x -> 0x%x\n", BSS_START, BSS_END);
  printf("HEAP:   0x%x -> 0x%x\n", HEAP_START, HEAP_START + HEAP_SIZE);
  printf("STACK:  0x%x -> 0x%x\n", STACK_START, STACK_END);
  return 0;
}

static int cmd_q(char *args) {
  return -1;
}

void busybox_mainloop() {
	for (char *str; (str = rl_gets()) != NULL; ) { 
		char *str_end = str + strlen(str);

		// Splitting a string into a set of strings
		char *cmd = strtok(str, " ");  
		if (cmd == NULL) { continue; }

		char *args = cmd + strlen(cmd) + 1;
		if (args >= str_end) {
			args = NULL;
		}

		for (int i = 0; i < NR_CMD; i ++) {
			if (strcmp(cmd, cmd_table[i].name) == 0) {
				if (cmd_table[i].handler(args) < 0) { return; }
				break;
			}
			if (i == NR_CMD - 1) { printf("Unknown command '%s'\n", cmd); }
		}
	}
	// while (1) {
  //   printf("Busybox: Running...\n");
  //   task_delay(1000);
  // }
}
