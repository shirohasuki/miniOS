# Save all General-Purpose(GP) registers to context.
# struct context *base = &ctx_task;
# base->ra = ra;
# ......
# These GP registers to be saved don't include gp
# and tp, because they are not caller-saved or
# callee-saved. These two registers are often used
# for special purpose. For example, in RVOS, 'tp'
# (aka "thread pointer") is used to store hartid,
# which is a global value and would not be changed
# during context-switch.
.macro reg_save base
  sw ra, 0(\base)
  sw sp, 4(\base)
  sw t0, 16(\base)
  sw t1, 20(\base)
  sw t2, 24(\base)
  sw s0, 28(\base)
  sw s1, 32(\base)
  sw a0, 36(\base)
  sw a1, 40(\base)
  sw a2, 44(\base)
  sw a3, 48(\base)
  sw a4, 52(\base)
  sw a5, 56(\base)
  sw a6, 60(\base)
  sw a7, 64(\base)
  sw s2, 68(\base)
  sw s3, 72(\base)
  sw s4, 76(\base)
  sw s5, 80(\base)
  sw s6, 84(\base)
  sw s7, 88(\base)
  sw s8, 92(\base)
  sw s9, 96(\base)
  sw s10, 100(\base)
  sw s11, 104(\base)
  sw t3, 108(\base)
  sw t4, 112(\base)
  sw t5, 116(\base)
  # we don't save t6 here, due to we have used
  # it as base, we have to save t6 in an extra step
  # outside of reg_save
.endm

# restore all General-Purpose(GP) registers from the context
# except gp & tp.
# struct context *base = &ctx_task;
# ra = base->ra;
# ......
.macro reg_restore base
  lw ra, 0(\base)
  lw sp, 4(\base)
  lw t0, 16(\base)
  lw t1, 20(\base)
  lw t2, 24(\base)
  lw s0, 28(\base)
  lw s1, 32(\base)
  lw a0, 36(\base)
  lw a1, 40(\base)
  lw a2, 44(\base)
  lw a3, 48(\base)
  lw a4, 52(\base)
  lw a5, 56(\base)
  lw a6, 60(\base)
  lw a7, 64(\base)
  lw s2, 68(\base)
  lw s3, 72(\base)
  lw s4, 76(\base)
  lw s5, 80(\base)
  lw s6, 84(\base)
  lw s7, 88(\base)
  lw s8, 92(\base)
  lw s9, 96(\base)
  lw s10, 100(\base)
  lw s11, 104(\base)
  lw t3, 108(\base)
  lw t4, 112(\base)
  lw t5, 116(\base)
  lw t6, 120(\base)
.endm

# Something to note about save/restore:
# - We use mscratch to hold a pointer to context of current task
# - We use t6 as the 'base' for reg_save/reg_restore, because it is the
#   very bottom register (x31) and would not be overwritten during loading.
#   Note: CSRs(mscratch) can not be used as 'base' due to load/restore
#   instruction only accept general purpose registers.

.text

# interrupts and exceptions while in machine mode come here.
.global trap_vector
# the trap vector base address must always be aligned on a 4-byte boundary
.align 4
trap_vector:
  # save context(registers).
  csrrw   t6, mscratch, t6  # swap t6 and mscratch
  reg_save  t6

  # save the actual t6 register, which we swapped into mscratch
  mv    t5, t6        # t5 points to the context of current task
  csrr  t6, mscratch    # read t6 back from mscratch
  sw    t6, 120(t5)     # save t6 with t5 as base

  # save mepc to context of current task
  csrr    a0, mepc
  sw      a0, 124(t5)

  # Restore the context pointer info mscratch
  csrw  mscratch, t5

  # call the C trap handler in trap.c
  csrr  a0, mepc
  csrr  a1, mcause
  csrr  a2, mscratch
  call  trap_handler

  # trap_handler will return the return address via a0.
  csrw  mepc, a0

  # restore context(registers).
  csrr  t6, mscratch
  reg_restore t6

  # return to whatever we were doing before trap.
  mret

.end  
