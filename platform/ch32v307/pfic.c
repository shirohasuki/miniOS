#include "pfic.h"
#include "csr.h"

// ref CH32FV2x_V3xRM.PDF v2.3 p78 

#define PFIC_IENR2 0xE000E104L

void pfic_init(void) {
  /* enable machine-mode global interrupts. */
  write_mstatus(MSTATUS_MPIE | MSTATUS_MIE);

  /* enable usart1 interrupts. */
  *(uint32_t *)PFIC_IENR2 |= (uint32_t)(0x00200000);

  /* enable usart2 interrupts. */
  *(uint32_t *)PFIC_IENR2 |= (uint32_t)(0x00400000);
}
