#include "trap.h"
#include "types.h"
#include "minilib.h"

extern void trap_vector(void);

void trap_init() {
  write_mtvec((reg_t)trap_vector);
}

reg_t trap_handler(reg_t epc, reg_t cause) {
  reg_t return_pc = epc;
  reg_t cause_code = cause;

  if (cause & 0x80000000) {
    printf("interruption!\n");
  } else {
    printf("exception! code = %d\n", cause_code);
    /* we don't handle this exception 
     * so the trap test will loop here
     */
  }

  return return_pc;
}

