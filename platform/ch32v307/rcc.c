#include "rcc.h"
#include "map.h"

void rcc_init() {
  /* Enable HSI */
  RCC_REG->CTLR |= (uint32_t)0x00000001;

  /* PLL multiplied by 12 */
  RCC_REG->CFGR0 |= (uint32_t)(0x00280000);

  /* Enable PLL */
  RCC_REG->CTLR |= (uint32_t)0x01000000;

  /* Wait till PLL is ready */
  while((RCC_REG->CTLR & (uint32_t)0x02000000) == 0);

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
  RCC_REG->CFGR0 &= (uint32_t)((uint32_t)~(0x7 << 10));
  RCC_REG->CFGR0 |= (uint32_t)((uint32_t)(1 << 1) | (uint32_t)(0x4 << 10));

  /* 
   * Wait till PLL is used as system clock source
   */
  while ((RCC_REG->CFGR0 & (uint32_t)0x0000000C) != (uint32_t)0x08);
}
