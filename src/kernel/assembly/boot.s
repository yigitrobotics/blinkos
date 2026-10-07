.intel_syntax noprefix

.set ALIGN, 1<<0
.set MEMINFO, 1<<1
.set MAGIC, 0x1BADB002
.set FLAGS, ALIGN | MEMINFO
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
    .align 4

    .long MAGIC
    .long FLAGS
    .long CHECKSUM

.section .bss  
    .align 16
stack_bottom:
    .skip 32768
    .align 16
stack_top:

.section .text
    .global _start
    .type _start, @function

_start:
    mov esp, offset stack_top

    call kernel_main

    cli
    1: hlt
        jmp 1b
