# BlinkOS

BlinkOS is a personal hobby operating system project that I am developing to learn kernel development and low-level system programming.

> ⚠️ This project is not AI-written.

## Features

* x86 Protected Mode
* GDT and IDT
* Hardware interrupt handling
* PS/2 keyboard input
* VGA text-mode terminal
* Basic shell with simple command support

## Project Status

BlinkOS is currently under active development.
The project is mainly focused on learning and experimenting with low-level system programming and operating system development.

## How to Run

### Arch Linux

```bash
sudo pacman -S nasm xorriso qemu-desktop grub
```

The `i686-elf-gcc` and `i686-elf-binutils` cross-compiler toolchain must also be installed.

### Debian / Ubuntu

```bash
sudo apt install nasm xorriso qemu-system-x86 grub-pc-bin
```

The `i686-elf-gcc` and `i686-elf-binutils` cross-compiler toolchain must also be installed.

### Build and Run

```bash
make
make run
```
