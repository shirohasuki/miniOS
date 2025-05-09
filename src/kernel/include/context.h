#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "types.h"

#define MAX_TASKS 5
#define STACK_SIZE 2048

struct context {
    /* ignore x0 */
    reg_t ra;
    reg_t sp;
    reg_t gp;
    reg_t tp;
    reg_t t0;
    reg_t t1;
    reg_t t2;
    reg_t s0;
    reg_t s1;
    reg_t a0;
    reg_t a1;
    reg_t a2;
    reg_t a3;
    reg_t a4;
    reg_t a5;
    reg_t a6;
    reg_t a7;
    reg_t s2;
    reg_t s3;
    reg_t s4;
    reg_t s5;
    reg_t s6;
    reg_t s7;
    reg_t s8;
    reg_t s9;
    reg_t s10;
    reg_t s11;
    reg_t t3;
    reg_t t4;
    reg_t t5;
    reg_t t6;
    // upon is trap frame

    // save the pc to run in next schedule cycle
    reg_t pc; // offset: 31 * 4 = 124
};

void sched_init();
void schedule();
int task_create(void (*start_routine)(void));
void task_yield();
void task_delay(volatile int count);

/* Lock */
int spin_lock();
int spin_unlock();

#endif /* __CONTEXT_H__ */
