#include "src/uart/uart.h"
/*
include "stdint.h" // already included in the uart.h
include "stdbool.h"
include "<stddef.h>"

*/

void kmain(void){
    uart_init();
    
    char str[] = "Hello I'm Mark Fernando. Welcome to my kernel!";
    mprintf(str);

    while(1);
}