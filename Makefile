CC      = i686-elf-gcc
AS      = i686-elf-as
NASM    = nasm

CFLAGS    = -m32 -ffreestanding -fno-pie -fno-stack-protector
LDFLAGS   = -m32 -T src/kernel/linker.ld -ffreestanding -nostdlib
NASMFLAGS = -f elf32

ISO  = blinkos.iso
ROOT = root

C_SRCS    := $(shell find src -type f -name '*.c')
GAS_SRCS  := $(shell find src -type f -name '*.s')
NASM_SRCS := $(shell find src -type f -name '*.asm')

C_OBJS    := $(C_SRCS:.c=.o)
GAS_OBJS  := $(GAS_SRCS:.s=.o)
NASM_OBJS := $(NASM_SRCS:.asm=.o)

OBJS := $(C_OBJS) $(GAS_OBJS) $(NASM_OBJS)

all: $(ISO)

$(ISO): kernel.bin
	mkdir -p $(ROOT)/boot
	cp kernel.bin $(ROOT)/boot/kernel.bin
	grub-mkrescue -o $(ISO) $(ROOT)
	@echo "Success!"

kernel.bin: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) -lgcc

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(AS) --32 $< -o $@

%.o: %.asm
	$(NASM) $(NASMFLAGS) $< -o $@

run: $(ISO)
	qemu-system-i386 \
		-cdrom $(ISO) \
		-display sdl \
		-debugcon stdio

clean:
	find src -type f -name '*.o' -delete
	rm -f kernel.bin
	rm -f $(ISO)
	rm -f $(ROOT)/boot/kernel.bin

.PHONY: all run clean