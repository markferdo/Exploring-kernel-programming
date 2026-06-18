ENTRY(_start)

MEMORY
{
    RAM : ORIGIN = 0x80000000, LENGTH = 512M
}

SECTIONS
{
    .text: { *(.text) } > RAM
    .data : { *(.data) } > RAM
    .bss : { 
        _bss_start = .; // 
            *(.bss) 
        _bss_end = .;} > RAM

        // bss end and start initialize the non zero variables


    //.text 0x80000000: { *(.text) }
    //.data 0x80010000: { *(.data) }
    //.bss 0x80020000: { *(.bss) }

    
}

_stack = 0x9FFFC000; // define stack and link to .s file stack


