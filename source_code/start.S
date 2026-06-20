.global _start

_start:
    ldr sp, =_stack 
    bic sp, sp, #7
    bl kmain
    

loop2:
    b loop2




