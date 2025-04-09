#ifndef CSR_H
#define CSR_H

#include "types.h"

extern void write_mscratch(reg_t x);
extern void write_mtvec(reg_t x);
extern void write_mepc(reg_t x);
extern void write_mstatus(reg_t x);
extern void write_mie(reg_t x);
extern void write_mcause(reg_t x);

extern reg_t read_tp();
extern reg_t read_mhartid();
extern reg_t read_mstatus();
extern reg_t read_mie();
extern reg_t read_mcause();

#endif /* CSR_H */
