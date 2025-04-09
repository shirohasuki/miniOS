#include "map.h"
#include "csr.h"

// ref CH32FV2x_V3xRM.PDF v2.3 p78 

void pfic_init(void) {
  /* enable machine-mode global interrupts. */
  write_mstatus(read_mstatus() | MSTATUS_MPIE | MSTATUS_MIE);

  /* enable SysTick interrupts. */
  PFIC_REG->IENR[0] |= (uint32_t)(0x00001000);

  /* enable usart1 interrupts. */
  // PFIC_REG->IENR[1] |= (uint32_t)(0x00200000);

  /* enable usart2 interrupts. */
  PFIC_REG->IENR[1] |= (uint32_t)(0x00400000);
}
