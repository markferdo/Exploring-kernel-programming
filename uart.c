#include "uart.h"

#define UART0_BASE 0x44E090000
#define UART0_THR (UART0_BASE + 0x00)
#define UART0_DLL (UART0_BASE + 0x00) // when DLAB=1
#define UART0_DLH (UART0_BASE + 0x04) // when DLAB=1
#define UART0_LCR (UART0_BASE + 0x0C)
#define UART0_LSR (UART0_BASE + 0x14)


void uart_init(){
    // need to use volatile. So, the compiler always reads/writes to the memory address, instead of optimizing it away.
    // *(volatile uint32_t *) this part type casts and also defrerences the pointer to the memory address. So, we can read/write to the memory address directly.
    // Above process can b0e done in one line or separately. 
    // Important: type casting and dereferencing both need to be done.
    // without type casting, it creates a memory in the RAM. But we want to access the uart register.
    
    // config mode LCR = 0x83
    // set baud rate (DLL/DLH)
    // normal mode LCR = 0x03

    *(volatile uint32_t *)(UART0_BASE + 0x0C) = 0x83; // config mode DLAB = 1

    // set baud rate to 115200. From the data sheet, the UART clock is 48MHz, the divisor would be 48MHz / (16 * 115200) = 26.04 ~ 26 (decimal) = 0x1A (hexadecimal)
    // 115.2 kbps   16x   26   0x00, 0x1A   115.38 kbps   +0.16% copied from Table 19-25 in texas instruments data sheet.
    // DLH 0x00, DLL 0x1A
    *(volatile uint32_t *)(UART0_BASE + 0x00) = 0x1A; // set baud rate (DLL)
    *(volatile uint32_t *)(UART0_BASE + 0x04) = 0x00; // set baud rate (DLH)


    *(volatile uint32_t *)(UART0_BASE + 0x0C) = 0x03; // normal mode DLAB = 0
    
}

void uart_read(char *buf, int len){
    // refer Table 4-239 
    // LSR: Line Status Register    THR(Transmit Holding Register)  RHR(Receive Holding Register)
    // If LSR() bit 5 is 1, THR is empty, we can write to it. If LSR bit 5 is 0, data is ready to be read from RHR..
    *(volatile uint32_t *)(UART0_BASE + 0x14); // check if data is ready to be read (LSR bit 0)
    // above line is incomplete.
}

void uart_write(char *str){

}
 
void mprintf(const char *format, ...){
    // check the LSR bit 5 to see if THR is empty. If it is empty then write the character to THR. 

}
