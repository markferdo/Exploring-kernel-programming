#include "uart.h"

#define UART0_BASE 0x44E090000
#define UART0_THR (UART0_BASE + 0x00)
#define UART0_DLL (UART0_BASE + 0x00) // when DLAB=1
#define UART0_DLH (UART0_BASE + 0x04) // when DLAB=1
#define UART0_LCR (UART0_BASE + 0x0C)
#define UART0_LSR (UART0_BASE + 0x14)


void uart_init(){
    // need to use volatile. So, the compiler always reads/writes to the memory address, instead of optimizing it away.
    *(volatile uint32_t *)(UART0_BASE + 0x0C) = 0x83; // config mode DLAB = 1
    *(volatile uint32_t *)(UART0_BASE + 0x00) = 0x01; // set baud rate (DLL)
    *(volatile uint32_t *)(UART0_BASE + 0x04) = 0x00; // set baud rate (DLH)
    *(volatile uint32_t *)(UART0_BASE + 0x0C) = 0x03; // normal mode DLAB = 0
    printf("Initializing UART0 at base address: 0x%X\n", UART0_BASE);
    // config mode LCR = 0x83
    // set baud rate (DLL/DLH)
    // normal mode LCR = 0x03
}

 
