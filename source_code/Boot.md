26.1.6 Booting --> 2

26.1.5 Start-up and Configuration --> 1

AND MOST IMPORTANT:

26.1.8 Memory Booting --> 3
26.1.9 Peripheral Booting --> 4
26.1.10 Image Format --> 5


## Start-up and Configuration (26.1.5)

On this device the main MPU subsystem always starts its execution in secure mode after reset due to the
TrustZone architecture (the Secure ROM Code implements the reset handler). The Public ROM Code is physically located at the address 20000h that is immediately next to the Secure
ROM Code. (Copied from 26.1.5.1)

According to above statement when the chip powers on, the CPU starts the secure mode (ROM) and once it done it hand over to public ROM.


~~~
RESET
  ↓
Secure ROM (TrustZone reset handler)
  ↓
Public ROM (boot code @ 0x20000)
  ↓
DPLL / clock setup (basic)
  ↓
Boot mode selection (SYSBOOT pins)
  ↓
Load boot image (SD / eMMC / UART)
  ↓
Jump to loaded image (U-Boot or SPL)
  ↓
YOUR CODE ENTRY POINT (_start in assembly)
  ↓
C main()
~~~



## Processor details

Beaglebone uses ARM Cortex-A8 based processor (AM335x chip uses this processor)

ARMv7-A architecture (32-bit ARM innstruction set)

~~~
R0–R12  -> general purpose (variables, calculations, functions)
R13     -> Stack Pointer (SP)
R14     -> Link Register (LR) : stores return address
R15     -> Program Counter (PC) : current execution address
CPSR    -> status + mode control
~~~

### Linker

.text for code

.data for initialized globals

.bss for zero-initialized globals


### Links

processor details: https://developer.arm.com/documentation/ddi0344/k/

Linker script: https://developer.arm.com/documentation/107976/22-1-0/Map-code-and-data-to-your-target-device/Linker-scripts/Writing-linker-scripts

https://wiki.osdev.org/Linker_Scripts

https://www.eecs.umich.edu/courses/eecs373/readings/Linker.pdf



