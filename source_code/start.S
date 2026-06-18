.global _start

_start:
    ldr r13, =_stack @ Table 2-1 -> EMIF0 SDRAM
    @ In the TI data sheet it says size is 1 GB. Since the beaglebone black has 512 MB we cant use exact end address for the RAM
    @ So the address is 0x9FFFFFFF but its good to reserve some memory since uboot might use RAM top memory
    @ RAM starts at the end address (Cz stack grows downward)
    
    ldr r0, =_bss_start
    ldr r1, =_bss_end
    @ now do the while loop and assign 0
    @ if r0<r1
    
    bl kmain
    

loop:
    b loop




