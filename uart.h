#include <stdint.h>
void uart_init();
void uart_read(char *buf, int len);
void uart_write(char *str);
void mprintf(const char *format, ...);