ENTRY(_start)

MEMORY
{
    RAM (xrw) : ORIGIN = 0x80000000, LENGTH = 512M
}

SECTIONS
{
    .text : { 
        . = ALIGN(4);
        *(.text*) 
        *(.rodata*)
        } > RAM
    .data : { 
        . = ALIGN(4);
        *(.data*) } > RAM
    
    .bss : 
    { 

        bss_start = .; 
        *(.bss*)
        *(COMMON)
        bss_end = .;
    } > RAM
    
    /* bss end and start initialize the non zero variables*/

    
}

_stack = ORIGIN(RAM) + LENGTH(RAM); 
/*define stack and link to .s file stack*/


