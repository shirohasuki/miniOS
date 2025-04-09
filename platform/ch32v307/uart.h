#ifndef UART_H
#define UART_H

void uart1_init(void);
void uart2_init(void);
void uart_puts(char *s);
int uart1_getc(void);
int uart2_getc(void);
void uart1_irq_handler(void);
void uart2_irq_handler(void);

#endif /* UART_H */
