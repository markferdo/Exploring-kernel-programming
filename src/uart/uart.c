/*
This code is for Uart communication on BeagleBone Black (AM335x).
I'm not responsible for the outcome of this code. It is for educational purposes only.
Reffer Texas Instruments data sheet: https://www.ti.com/lit/ug/spruh73q/spruh73q.pdf
*/


/*
MIT License

Copyright (c) 2026 Mark Fernando

Permission is hereby granted, free of charge, to any person obtaining a copy of this 
software and associated documentation files (the “Software”), to deal in the Software 
without restriction, including without limitation the rights to use, copy, modify, 
merge, publish, distribute, sublicense, and/or sell copies of the Software, and to 
permit persons to whom the Software is furnished to do so, subject to the following 
conditions:

The above copyright notice and this permission notice shall be included in all copies 
or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF 
CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE 
OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "uart.h"

// Refer UART registers chapter 19.5
#define UART0_BASE 0x44E090000
#define UART0_THR (UART0_BASE + 0x00)
#define UART0_RHR (UART0_BASE + 0x00) // RHR/RBR
#define UART0_DLL (UART0_BASE + 0x00) // when DLAB=1
#define UART0_DLH (UART0_BASE + 0x04) // when DLAB=1
#define UART0_LCR (UART0_BASE + 0x0C)
#define UART0_LSR (UART0_BASE + 0x14)

void uart_init(){ // call this once only
    // need to use volatile. So, the compiler always reads/writes to the memory address, instead of optimizing it away.
    // *(volatile uint32_t *) this part type casts and also defrerences the pointer to the memory address. So, we can read/write to the memory address directly.
    // Above process can b0e done in one line or separately. 
    // Important: type casting and dereferencing both need to be done.
    // without type casting, it creates a memory in the RAM. But we want to access the uart register.
    
    // config mode LCR = 0x83
    // set baud rate (DLL/DLH)
    // normal mode LCR = 0x03

    *(volatile uint32_t *)(UART0_LCR) = 0x83; // config mode DLAB = 1

    // set baud rate to 115200. From the data sheet, the UART clock is 48MHz, the divisor would be 48MHz / (16 * 115200) = 26.04 ~ 26 (decimal) = 0x1A (hexadecimal)
    // 115.2 kbps   16x   26   0x00, 0x1A   115.38 kbps   +0.16% copied from Table 19-25 in texas instruments data sheet.
    // DLH 0x00, DLL 0x1A
    *(volatile uint32_t *)(UART0_DLL) = 0x1A; // set baud rate (DLL)
    *(volatile uint32_t *)(UART0_DLH) = 0x00; // set baud rate (DLH)


    *(volatile uint32_t *)(UART0_LCR) = 0x03; // normal mode DLAB = 0
    
}

// LSR: Line Status Register    THR(Transmit Holding Register)  RHR(Receive Holding Register)

void uart_read(char *buf, int len){ // this is for terminal inputs
    // refer Table 4-239 
    // LSR bit 0 (DR - Data Ready)
    // In non-FIFO mode:
    // 0 Data is not ready, or the DR bit was cleared because the character was read from the receiver buffer register (RBR).
    // 1 Data is ready. A complete incoming character has been received and transferred into the receiver buffer register (RBR).

    /*
    do{
        char data;
        if (*(volatile uint32_t *)(UART0_LSR) & 0x01){
            
            data = *(volatile uint8_t *)(UART0_RHR);
        }

    }
        
    while(data != '\n');
    */
    
    char data = '0';

    while(data != '\n'){

        if (*(volatile uint32_t *)(UART0_LSR) & 0x01){
            
            data = *(volatile uint8_t *)(UART0_RHR);
        }

    }

}

void uart_write(char *str){ // can print predefined message on the terminal
    // refer Table 4-239
    /*
    Check the LSR bit 5
    In non-FIFO mode:
    0 Transmitter holding register (THR) is not empty. THR has been loaded by the CPU.
    1 Transmitter holding register (THR) is empty (ready to accept a new character). The content of THR has been transferred to the transmitter shift register (TSR).
    */
    // If LSR() bit 5 is 1, THR is empty, we can write to it. If LSR bit 5 is 0, data is ready to be read from RHR..
    // LSR & (1<<5)
    // 0000 0001 <- shift left 5 times
    // 0010 0000 = 0x20
    // LSR & 0x20 (AND)
    while(*str != '\0'){
        if (*(volatile uint32_t *)(UART0_LSR) & 0x20) { 
            // write to THR
            *(volatile uint8_t *)(UART0_THR) = *str; // write the character to THR
            // eventhough the register is 32 bit it only uses 8 bit
            str++; // move to next character (infact next memory address)
        }
        /*
        In non-FIFO mode:
        0 Either the transmitter holding register (THR) or the transmitter shift register (TSR) contains a data character.
        1 Both the transmitter holding register (THR) and the transmitter shift register (TSR) are empty
        */

        // *(volatile uint32_t *)(UART0_BASE + 0x14) & 0x40) this is the logic
        // bit 6 is the TEMT
        // TEMT = 1 means no more characters
        // but we dont need to check that
    }
    

}
 
void mprintf(const char *str){
    // void mprintf(const char *format, ...) if we use this we can use it like printf.
    // With my current implementation, we can only print string.
    // check the LSR bit 5 to see if THR is empty. If it is empty then write the character to THR. 

    uart_write(str);
}
