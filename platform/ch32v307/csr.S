.text

/*
 * ref: https://github.com/mit-pdos/xv6-riscv/blob/riscv/kernel/riscv.h
 */

/*
 * csr register read and write
 * 
 * tp: thread pointer
 * mstatus: machine status
 * mepc: machine exception program counter
 * mscratch: machine scratch
 * mtvec: machine trap vector
 * mcause: machine cause
 * mie: machine interrupt enable
 */
.global read_tp
read_tp:
  mv a0, tp
  ret

.global read_mstatus
read_mstatus:
  csrr a0, mstatus
  ret

.global write_mstatus
write_mstatus:
  csrw mstatus, a0
  ret

.global write_mepc
write_mepc:
  csrw mepc, a0
  ret

.global read_mepc
read_mepc:
  csrr a0, mepc
  ret

.global write_mscratch
write_mscratch:
  csrw mscratch, a0
  ret

.global write_mtvec
write_mtvec:
  csrw mtvec, a0
  ret

.global read_mcause
read_mcause:
  csrr a0, mcause
  ret 
