build:
	arm-none-eabi-as start.S -o start.o
	arm-none-eabi-ld start.o -o kernel.elf

run:
	qemu-system-arm \
		-M versatilepb \
		-cpu cortex-a8 \
		-nographic \
		-kernel kernel.elf
clean:
	rm -f *.o *.elf
