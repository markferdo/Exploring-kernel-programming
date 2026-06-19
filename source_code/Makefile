CC = arm-none-eabi-gcc
CFLAGS = -c -nostdlib -ffreestanding

build:
	$(CC) $(CFLAGS) main.c -o main.o
	$(CC) $(CFLAGS) src/uart/uart.c -o uart.o
	arm-none-eabi-as start.S -o start.o
	arm-none-eabi-ld -T linker.ld start.o main.o uart.o -o kernel.elf

clean:
	rm -f *.o *.elf
