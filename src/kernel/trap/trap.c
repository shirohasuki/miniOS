#include "trap.h"
#include "types.h"
#include "minilib.h"
#include "platform.h"
#include "syscall.h"
#include "stimer.h" // for timer_handler

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
reg_t trap_handler(reg_t epc, reg_t cause, struct context *cxt) {
  reg_t return_pc = epc;
  reg_t cause_code = cause & 0xfff; /* clear the top 4 bits */

  if (cause & 0x80000000) {
    switch (cause_code) {
      case 12:
        // uart_puts("Timer interruption!\n");
        timer_handler();
        break;
      case 14:
        // printf("Software interruption!\n");
        /* Clear the software interrupt bit */
        STK_REG->CTLR &= ~((uint32_t)(1 << 31));
        schedule();
        break;
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
    switch (cause) {
      case 11:
        // printf("System call from U-mode!\n");
        do_syscall(cxt);
        return_pc += 4;
        break;
      default:
        printf("exception! code = %d\n", cause_code);
        panic("System stall!");
        /* we don't handle this exception 
         * so the trap test will loop here
         */
    }
  }

  return return_pc;
}

