//#include "syscall.h"

.equ SYS_getarchid, 1

.global getarchid
getarchid:
  li  a7, SYS_getarchid
  ecall
  ret