all: bios uefi kernel

bios:
	nasm -f bin sys/boot/bios/boot.asm -o sys/build/boot-bios.bin

kernel:
	i386-elf-gcc -ffreestanding -m32 -c sys/kernel/kernel.c -o sys/build/kernel.o
	i386-elf-ld -T sys/kernel/linker.ld -o sys/build/kernel.bin sys/build/kernel.o --oformat binary

uefi:
	x86_64-w64-mingw32-gcc -shared -nostdlib -Wl,--subsystem,10 \
		sys/boot/uefi/boot.c -o sys/build/BOOTX64.EFI

clean:
	rm -f sys/build/*
