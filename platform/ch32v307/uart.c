#include "types.h"
#include "map.h"
#include "uart.h"
#include "stdbuff.h"

// ref CH32FV2x_V3xRM.PDF v2.3 p32 

/*
 * USART STATUS REGISTER (STATR)
 * STATR BIT 5:
 * 0 = Data not yet received.
 * 1 = Data received and can be read.
 * ......
 * STATR BIT 6:
 * 0 = Transmission not yet completed.
 * 1 = Transmission completed.
 * ......
 */
#define STATR_RX_READY (1 << 5)
#define STATR_TX_IDLE  (1 << 7)

/* UART2 Init*/
void uart2_init() {

  /*
   * Enable clock of USART2 and GPIO_PA
   */
  RCC_REG->APB1PCENR |= (uint32_t)(1 << 17);
  RCC_REG->APB2PCENR |= (uint32_t)(1 << 2);

  /*
   * Setting GPIO PA2 (TX2) to
   * - Reuse push-pull output mode (CNF[1:0] = 10)
   * - Speed 50MHz (MODE[1:0] = 11)
   */
  GPIOA_REG->CFGLR |= (uint32_t)(0x00000B00);

  /* Set baud rate to 57600
   * BaudRate = FCLK / (16 * USARTDIV)
   * USARTDIV = DIV_M + ( DIV_F / 16)
   * - DIV_M: [15:4] of BRR
   * - DIV_F: [3:0] of BRR
   */
  UART2_REG->BRR = (uint16_t)0x0341;

  /* Enable Rx for UART2 */
  UART2_REG->CTLR1 |= (uint16_t)(1 << 2);
  /* Enable Tx for UART2 */
  UART2_REG->CTLR1 |= (uint16_t)(1 << 3);
  /* Enable RXNE(RX buff Not Empty) interrupt for UART2 */
  UART2_REG->CTLR1 |= (uint16_t)(1 << 5);
  /* Enable UART2 */
  UART2_REG->CTLR1 |= (uint16_t)(1 << 13);
}

void uart_putc(uint16_t ch) {
  UART2_REG->DATAR = (ch & (uint16_t)0x01FF);
  while ((UART2_REG->STATR & STATR_TX_IDLE) == (uint16_t)0);
}

void uart_puts(char *s) {
  while (*s) {
    uart_putc(*s++);
  }
}



int uart_getc(void) {
  if (UART2_REG->STATR & STATR_RX_READY) {
    return (uint16_t)(UART2_REG->DATAR & (uint16_t)0x01FF);
  } else {
    return -1;
  }
}

/*
 * handle uart1 interrupt, raised because input has arrived, 
 * called from trap.c. The reserved data will be print by uart2.
 */
void uart1_irq_handler(void) {
  uart_puts("uart1 interrupt\n");
}

/*
 * handle uart2 interrupt, raised because input has arrived, 
 * called from trap.c. The reserved data will be print by uart2.
 */
void uart2_irq_handler(void) {
  while (1) {
    int c = uart_getc();
    if (c == -1) {
      break;
    } else {
      stdio_pushc((char)c);
    }
  }
}
