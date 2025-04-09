#include "csr.h"

/* 
 * Machine Status Register, mstatus
 * Only MPP, MPIE and MIE in CH32V307
 */
#define MSTATUS_MPP (3 << 11)
#define MSTATUS_MPIE (1 << 7)
#define MSTATUS_MIE (1 << 3)

/* No mhartid csr in CH32V307 */
#if 0
#define MIE_MEIE (1 << 11) // external
#define MIE_MTIE (1 << 7)  // timer
#define MIE_MSIE (1 << 3)  // software
#endif
