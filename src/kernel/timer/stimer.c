/*
 * stimer.c means software timer, which is a software implementation 
 * of hardware timer. timer used by miniOS are all software timers.
 */

#include "minilib.h"
#include "stimer.h"
#include "context.h"
#include "platform.h"

static uint32_t _tick = 0;

#define MAX_TIMER 10
static struct timer timer_list[MAX_TIMER];

struct timer *timer_create(void (*handler)(void *arg), 
                           void *arg, uint32_t timeout) {
  /* TBD: params should be checked more, but now we just simplify this */
  if (handler == NULL || timeout == 0) {
    return NULL;
  }

  /* use lock to protect the shared timer_list between multiple tasks */
  spin_lock();

  struct timer *t = timer_list;

  int i = 0;
  for (; i < MAX_TIMER; i++) {
    if (t->func == NULL) {
      break;
    }
    t++;
  }

  if (i >= MAX_TIMER) {
    spin_unlock();
    return NULL;
  }

  t->func = handler;
  t->arg = arg;
  t->timeout_tick = timeout;

  spin_unlock();

  return t;
}

void timer_delete(struct timer *timer) {
  spin_lock();

  struct timer *t = timer_list;
  for (int i = 0; i < MAX_TIMER; i++) {
    if (t == timer) {
      t->func = NULL;
      t->arg = NULL;
      break;
    }
    t++;
  }

  spin_unlock();
}

/* this routine should be called in interrupt context (interrupt is disabled) */
static inline void timer_check() {
  struct timer *t = timer_list;
  for (int i = 0; i < MAX_TIMER; i++) {
    if (t->func) {
      printf("t->timeout_tick: %d\n", t->timeout_tick);
      printf("_tick: %d\n", _tick);
      if (_tick >= t->timeout_tick) {
        t->func(t->arg);

        /* once time, just delete it after timeout */
        t->func = NULL;
        t->arg = NULL;

        // break;
      }
    }
    t++;
  }
}

void timer_handler() {
  _tick++;
  // printf("tick: %d\n", _tick);

  timer_check();
  /* Clear the status register flag bit */
  STK_REG->CTLR |= (uint32_t)(1 << 5);
  STK_REG->SR &= ~(1 << 0);
}
