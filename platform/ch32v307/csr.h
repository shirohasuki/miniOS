#ifndef CSR_H
#define CSR_H

#include "types.h"

/* 
 * Machine Status Register, mstatus
 * Only MPP, MPIE and MIE in CH32V307
 */
#define MSTATUS_MPP (3 << 11)
#define MSTATUS_MPIE (1 << 7)
#define MSTATUS_MIE (1 << 3)

/* No mie csr in CH32V307 */
#if 0
#define MIE_MEIE (1 << 11) // external
#define MIE_MTIE (1 << 7)  // timer
#define MIE_MSIE (1 << 3)  // software
#endif

extern void write_mscratch(reg_t x);
extern void write_mtvec(reg_t x);
extern void write_mepc(reg_t x);
extern void write_mstatus(reg_t x);
extern void write_mie(reg_t x);
extern void write_mcause(reg_t x);

extern reg_t read_tp();
// extern reg_t read_mhartid();
extern reg_t read_mstatus();
extern reg_t read_mie();
extern reg_t read_mcause();

#endif /* CSR_H */
