.global _start

_start:
    ldr r13, =_stack @ Table 2-1 -> EMIF0 SDRAM
    @ In the TI data sheet it says size is 1 GB. Since the beaglebone black has 512 MB we cant use exact end address for the RAM
    @ So the address is 0x9FFFFFFF but its good to reserve some memory since uboot might use RAM top memory
    @ RAM starts at the end address (Cz stack grows downward)
    
    @ To print the welcome message we dont need .bss initialization
    ldr r0, =_bss_start
    ldr r1, =_bss_end
    @ now do the while loop and assign 0. If not garbage value will be assigned
    mov r2, #0
    loop:
        cmp r0, r1 @ if r0<r1
        bge exit
        str r2, [r0] @store value 0 in the address
        add r0, r0, #4 @ move 4 bytes
        b loop
        
    exit:
        bl kmain
    

loop2:
    b loop2




