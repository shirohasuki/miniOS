#ifndef UART_H
#define UART_H

void uart2_init(void);
void uart_puts(char *s);
void uart_putc(uint16_t ch);
int uart_getc(void);
void uart1_irq_handler(void);
void uart2_irq_handler(void);
#endif /* UART_H */
