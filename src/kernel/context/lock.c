#include "platform.h"
#include "context.h"

int spin_lock() {
  write_mstatus(read_mstatus() & ~MSTATUS_MIE);
  return 0;
}

int spin_unlock() {
  write_mstatus(read_mstatus() | MSTATUS_MIE);
  return 0;
}
