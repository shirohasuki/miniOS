#ifndef __STIMER_H__
#define __STIMER_H__

struct timer {
  void (*func)(void *arg);
  void *arg;
  uint32_t timeout_tick;
};

struct timer *timer_create(void (*handler)(void *arg), void *arg, uint32_t timeout);
void timer_delete(struct timer *timer);

void timer_handler();

#endif /* __STIMER_H__ */