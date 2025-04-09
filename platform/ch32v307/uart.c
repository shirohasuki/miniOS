#include "types.h"
#include "ch32v307.h"
#include "uart.h"

#define RCC_REG(reg)  ((volatile uint32_t *)(RCC + (reg << 2)))
#define GPIO_REG(reg)  ((volatile uint32_t *)(GPIOA + (reg << 2)))
#define UART1_REG(reg) ((volatile uint32_t *)(USART1 + (reg << 2)))
#define UART2_REG(reg) ((volatile uint32_t *)(USART2 + (reg << 2)))


// ref CH32FV2x_V3xRM.PDF v2.3 p32 
typedef enum {
  CTLR = 0,
  CFGR0 = 1,
  INTR = 2,
  APB2PRSTR = 3,
  APB1PRSTR = 4,
  AHBPCENR = 5,
  APB2PCENR = 6,
  APB1PCENR = 7,
  BDCTLR = 8,
  RSTSCKR = 9,
  AHBRSTR = 10,
  CFGR2 = 11,
} RCC_TypeDef;

typedef enum {
  CFGLR = 0,
  CFGHR = 1,
  INDR = 2,
  OUTDR = 3,
  BSHR = 4,
  BCR = 5,
  LCKR = 6,
} GPIO_TypeDef;

typedef enum {
  STATR = 0,
  DATAR = 1,
  BRR = 2,
  CTLR1 = 3,
  CTLR2 = 4,
  CTLR3 = 5,
  GPR = 6,
} UART_TypeDef;

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

#define rcc_read_reg(reg) (*(RCC_REG(reg)))
#define rcc_write_reg(reg, v) (*(RCC_REG(reg)) = (v))

#define gpio_read_reg(reg) (*(GPIO_REG(reg)))
#define gpio_write_reg(reg, v) (*(GPIO_REG(reg)) = (v))

#define uart1_read_reg(reg) (*(UART1_REG(reg)))
#define uart1_write_reg(reg, v) (*(UART1_REG(reg)) = (v))

#define uart2_read_reg(reg) (*(UART2_REG(reg)))
#define uart2_write_reg(reg, v) (*(UART2_REG(reg)) = (v))

/* UART1 Init*/
void uart1_init() {
  /* Enable HSI */
  *RCC_REG(CTLR) |= (uint32_t)0x00000001;

  /* PLL multiplied by 12 */
  *RCC_REG(CFGR0) |= (uint32_t)(0x00280000);

  /* Enable PLL */
  *RCC_REG(CTLR) |= (uint32_t)0x01000000;

  /* Wait till PLL is ready */
  while((*RCC_REG(CTLR) & (uint32_t)0x02000000) == 0);

  /* 
   * Select PLL as system clock source
   *
   * HSI = 8MHz
   * PLLSRC = HSI / 2 = 4MHz
   * PLL = PLLSRC * 12 = 48MHz
   * SYSCLK = PLL = 48MHz
   */
  *RCC_REG(CFGR0) &= (uint32_t)((uint32_t)~(0x00000003));
  *RCC_REG(CFGR0) |= (uint32_t)0x00000002;

  /* 
   * Wait till PLL is used as system clock source
   */
  while ((rcc_read_reg(CFGR0) & (uint32_t)0x0000000C) != (uint32_t)0x08);

  /*
   * Enable clock of USART1 and GPIO_PA
   */
  rcc_write_reg(APB2PCENR, (uint32_t)((uint32_t)(1 << 14) | (uint32_t)(1 << 2)));

  /*
   * Setting GPIO PA9 (TX1) to
   * - Reuse push-pull output mode（CNF[1:0] = 10)
   * - Speed 50MHz (MODE[1:0] = 11)
   */
  *GPIO_REG(CFGHR) |= (uint32_t)(0x000000B0);

  /* Set baud rate to 57600
   * BaudRate = FCLK / (16 * USARTDIV)
   * USARTDIV = DIV_M + ( DIV_F / 16)
   * - DIV_M: [15:4] of BRR
   * - DIV_F: [3:0] of BRR
   */
  uart1_write_reg(BRR, (uint16_t)0x0341);

  /* Enable Rx for UART1 */
  *UART1_REG(CTLR1) |= (uint16_t)(1 << 2);
  /* Enable Tx for UART1 */
  *UART1_REG(CTLR1) |= (uint16_t)(1 << 3);
  /* Enable RXNE(RX buff Not Empty) interrupt for UART1 */
  *UART1_REG(CTLR1) |= (uint16_t)(1 << 5);
  /* Enable UART1 */
  *UART1_REG(CTLR1) |= (uint16_t)(1 << 13);
}

/* UART2 Init*/
void uart2_init() {
  /* Enable HSI */
  *RCC_REG(CTLR) |= (uint32_t)0x00000001;

  /* PLL multiplied by 12 */
  *RCC_REG(CFGR0) |= (uint32_t)(0x00280000);

  /* Enable PLL */
  *RCC_REG(CTLR) |= (uint32_t)0x01000000;

  /* Wait till PLL is ready */
  while((*RCC_REG(CTLR) & (uint32_t)0x02000000) == 0);

  /* 
   * Select PLL as system clock source
   *
   * HSI = 8MHz
   * PLLSRC = HSI / 2 = 4MHz
   * PLL = PLLSRC * 12 = 48MHz
   * SYSCLK = PLL = 48MHz
   * 
   * Attention: USART2 is on APB1, USART1 is on APB2
   * APB1 config PPRE1 to divide frequency (default not divide).
   * APB2 config PPRE2 to divide frequency (default not divide).
   * Theoretically, the default crossover coefficient for both APB1 and APB2 is 1, 
   * but I don't know why we need to set APB1 separately (APB2 does not need to set). 
   */
  *RCC_REG(CFGR0) &= (uint32_t)((uint32_t)~(0x7 << 10));
  *RCC_REG(CFGR0) |= (uint32_t)((uint32_t)(1 << 1) | (uint32_t)(0x4 << 10));
  /* 
   * Wait till PLL is used as system clock source
   */
  while ((rcc_read_reg(CFGR0) & (uint32_t)0x0000000C) != (uint32_t)0x08);

  /*
   * Enable clock of USART2 and GPIO_PA
   */
  rcc_write_reg(APB1PCENR, (uint32_t)(1 << 17));
  rcc_write_reg(APB2PCENR, (uint32_t)(1 << 2));

  /*
   * Setting GPIO PA2 (TX2) to
   * - Reuse push-pull output mode (CNF[1:0] = 10)
   * - Speed 50MHz (MODE[1:0] = 11)
   */
  *GPIO_REG(CFGLR) |= (uint32_t)(0xB << 8);

  /* Set baud rate to 57600
   * BaudRate = FCLK / (16 * USARTDIV)
   * USARTDIV = DIV_M + ( DIV_F / 16)
   * - DIV_M: [15:4] of BRR
   * - DIV_F: [3:0] of BRR
   */
  uart2_write_reg(BRR, (uint16_t)0x0341);

  /* Enable Rx for UART2 */
  *UART2_REG(CTLR1) |= (uint16_t)(1 << 2);
  /* Enable Tx for UART2 */
  *UART2_REG(CTLR1) |= (uint16_t)(1 << 3);
  /* Enable RXNE(RX buff Not Empty) interrupt for UART2 */
  *UART2_REG(CTLR1) |= (uint16_t)(1 << 5);
  /* Enable UART2 */
  *UART2_REG(CTLR1) |= (uint16_t)(1 << 13);
}

void uart_putc(uint16_t ch) {
  uart2_write_reg(DATAR, (ch & (uint16_t)0x01FF));
  while ((uart2_read_reg(STATR) & STATR_TX_IDLE) == (uint16_t)0);
}

void uart_puts(char *s) {
  while (*s) {
    uart_putc(*s++);
  }
}

int uart1_getc(void) {
  if (uart1_read_reg(STATR) & STATR_RX_READY) {
    return (uint16_t)(uart1_read_reg(DATAR) & (uint16_t)0x01FF);
  } else {
    return -1;
  }
}

int uart2_getc(void) {
  if (uart2_read_reg(STATR) & STATR_RX_READY) {
    return (uint16_t)(uart2_read_reg(DATAR) & (uint16_t)0x01FF);
  } else {
    return -1;
  }
}

/*
 * handle uart1 interrupt, raised because input has arrived, 
 * called from trap.c. The reserved data will be print by uart2.
 */
void uart1_irq_handler(void) {
	while (1) {
		int c = uart1_getc();
		if (c == -1) {
			break;
		} else {
			uart_putc((char)c);
			uart_putc('\n');
		}
	}
}

/*
 * handle uart2 interrupt, raised because input has arrived, 
 * called from trap.c. The reserved data will be print by uart2.
 */
void uart2_irq_handler(void) {
	while (1) {
		int c = uart2_getc();
		if (c == -1) {
			break;
		} else {
			uart_putc((char)c);
			uart_putc('\n');
		}
	}
}
