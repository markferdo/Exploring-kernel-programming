.global _start

_start:
    ldr r1, =hello
    
.data

hello: .ascii "Hello World!\n"
