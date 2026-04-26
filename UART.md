To exit qemu crtl+A then x

## UART Function

THR(Transmitter Holding Register): write
RBR(Receiver Buffer Register): read
TSR(Transmitter Shift Register)
DLL(Divisor Latch LSB): setting the speed. In other words braude rate
DLAB(Divisor Latch Access Bit)

### Data frame

start bit + 8 bit data(1 byte) + stop bit

Start and stop bit are temporarily adding data uart hardware. If you want to send 'A' then the data bit -> 01000001

If FIFO enabled, it can hold 16 frames (16-byte FIFO). 

RBR, THR and DLL share one address. To acess these we need DLAB value. If DLAB = 0, THR/RBR if DLAB = 1, DLL

Reffer

4.5.5 -> UART Register

