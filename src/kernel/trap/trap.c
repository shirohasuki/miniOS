#include "trap.h"
#include "types.h"
#include "minilib.h"
#include "platform.h"

extern void trap_vector(void);

void trap_init() {
  write_mtvec((reg_t)trap_vector);
}

/*
 * cause id
 * ref CH32FV2x_V3xRM.PDF v2.3 p78 
 * 
 * 53: USART1
 * 54: USART2
 */
reg_t trap_handler(reg_t epc, reg_t cause) {
  reg_t return_pc = epc;
  reg_t cause_code = cause & 0xfff; /* clear the top 4 bits */

  if (cause & 0x80000000) {
    switch (cause_code) {
      case 53: 
        // printf("USART1 interruption!\n");
        uart1_irq_handler();
        break;
      case 54:
        // printf("USART2 interruption!\n");
        uart2_irq_handler();
        break;
      default:
        printf("unkown interruption! code = %d\n", cause_code);
        break;
      }
  } else {
    printf("exception! code = %d\n", cause_code);
    /* 
     * we don't handle this exception 
     * so the trap test will loop here
     */
  }
  return return_pc;
}

