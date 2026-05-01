To exit qemu crtl+A then x

## UART Function

**THR(Transmitter Holding Register):** write data -> chapter 4.5.5.2 <br>
**RBR(Receiver Buffer Register):** read <br>
**TSR(Transmitter Shift Register):** send bits on the wire <br>
**DLL(Divisor Latch LSB):** setting the speed. In other words braude rate<br>
**DLAB(Divisor Latch Access Bit)**<br>
**LSR(Line Status Register):** provides information to the CPU of status of data transfer.<br>
**LSR_UART:** Line status register for uart. 14h offset(0x14) -> chapter 19.5.1.19 <br>
**LCR(Line Control Register):** <br>
**THRE(Transmit Holding Register Empty)**<br>
**TEMT(Transmitter Empty)**<br>

### Data frame

start bit + 8 bit data(1 byte) + stop bit

Start and stop bit are temporarily adding data uart hardware. So eventhough it looks 10 bits it only consist of 8 bits(data). If you want to send 'A' then the data bit -> 01000001

~~~
0 | 01000001 | 1
~~~

If FIFO enabled, it can hold 16 frames (16-byte FIFO). 

RBR, THR and DLL share one address. To acess these we need DLAB value. If DLAB = 0, THR/RBR if DLAB = 1, DLL


If we want to write then address is base address + 0x00 (check this statement)

To find the base address we need the memory map. 

~~~
        Start address   End address     Size    Description
UART0   0x44E0_9000     0x44E0_9FFF     4KB     UART Registers
        0x44E0_A000     0x44E0_AFFF     4KB     Reserved
~~~

**UART0 base address = 0x44E09000**

0x44E0A000 - 0x44E09000 = 0x1000 bytes
0x1000 = 4096 bytes(in decimal) = 4 KB

**LSR_UART** = UART0 base address + 0x14 = **0x44E09014**

![LSR](images/LSR.png)

From above image,

Bit 5: THRE -> THR is empty (can send data)

Bit 6: TEMT -> THR + TSR both empty

To check these we do bit masking

~~~
LSR & (1<<5) 
0000 0001 -> shift left 5 times
0010 0000 = 0x20
LSR & 0x20 (AND)
1 & 1 = 1 if not 0
~~~

with bit masking we can check the bit 5 and 6 value. THRE = 1 means empty


**FLow:**

- LSR bit 5 empty or not.
- If THRE = 1 write to the THR
- **THR address** is UART_BASE + 0x00 -> **0x44E09000**
- Then TSR
- Hadware add start bit, data, stop bit

~~~
If THRE = 1
   ↓
CPU writes byte
   ↓
THR (buffer)
   ↓
TSR (shift register)
   ↓
Start bit added
   ↓
Data bits sent 
   ↓
Stop bit added
   ↓
TX wire
~~~

Reffer:

Table 2-2 (page 180) -> Memory Map 
4.5.5 -> UART Register

### Links

Texas Instruments: https://www.ti.com/lit/ug/spruh73q/spruh73q.pdf?ts=1777214445506

