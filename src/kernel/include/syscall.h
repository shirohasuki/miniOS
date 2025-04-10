#ifndef __SYSCALL_H__
#define __SYSCALL_H__

#include "types.h"
#include "context.h"

/* System call numbers */
#define SYS_getarchid 1

/* user mode syscall APIs */
extern int getarchid(unsigned int *archid);

typedef struct context *context_t;
extern void do_syscall(context_t cxt);

#endif /* __SYSCALL_H__ */