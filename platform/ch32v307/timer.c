#include "timer.h"
#include "map.h"

#define SYSTEM_CORE_CLOCK 48000000

static uint8_t  p_us = 0;
static uint16_t p_ms = 0;

void timer_init() {
  p_us = SYSTEM_CORE_CLOCK / 8000000;
  p_ms = (uint16_t)p_us * 1000;

  /* Set CMP register to 1 second */
  STK_REG->CMP = (uint64_t)(p_ms * 1000);

  /* Enable SysTick */
  STK_REG->CTLR |= (uint32_t)(1 << 0);
  /* Enable SysTick interrupts */
  STK_REG->CTLR |= (uint32_t)(1 << 1);
  /* Clear the count value to 0 */
  STK_REG->CTLR |= (uint32_t)(1 << 5);

  /* Clear the status register flag bit */
  STK_REG->SR &= ~(1 << 0);
}

