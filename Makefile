C_SOURCES = $(wildcard Kernel/*.c Drivers/*.c)
HEADERS = $(wildcard Kernel/*.h Drivers/*.h)
OBJ = ${C_SOURCES:.c=.o}
KERNEL_OFFSET = 0x8200

CC = gcc
GDB = gdb

CFLAGS = -elf64 -std=c11 -fno-pie -O3 -msse -msse2 -Wall -Wextra -Werror

Cyrax64.iso: Boot/BootLoader.bin Kernel.bin
	cat $^ > Cyrax64.iso

Kernel.bin: Boot/Head.o ${OBJ}
	ld -o $@ -z max-page-size=4096 -Ttext ${KERNEL_OFFSET} $^ --oformat binary

Kernel.elf: Boot/Head.o ${OBJ}
	ld -o $@ -z max-page-size=4096 -Ttext ${KERNEL_OFFSET} $^ 

run: Cyrax64.iso
	qemu-system-x86_64 -fda Cyrax64.iso

debug: Cyrax64.iso Kernel.elf
	qemu-system-x86_64 -s -fda Cyrax64.iso&
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file Kernel.elf"

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -nostdlib -c $< -o $@
	${CC} ${CFLAGS} -ffreestanding -nostdlib -c -S $< -o $<.asm

Boot/BootLoader.bin: Boot/BootLoader.S
	as Boot/BootLoader.S -o Boot/BootLoader.tmp
	ld --oformat binary -Ttext 0x7C00 -o Boot/BootLoader.bin Boot/BootLoader.tmp
	rm Boot/BootLoader.tmp

%.o: %.S
	as $< -o $@
	ld --oformat binary -o $@ $@

%.bin: %.S
	as $< -o $@
	ld --oformat binary -o $@ $@

clean:
	rm -rf *.bin *.dis *.o *.elf
	rm -rf Kernel/*.o Boot/*.bin Drivers/*.o Boot/*.o
	rm -rf Kernel/*.c.asm Drivers/*.c.asm
