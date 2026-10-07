struct VGA_cursor;

#include "include/kernel.h"
#include "include/gdt.h"
#include "include/vga.h"
#include "include/interrupt.h"
#include "include/io.h"

void cli() {
    __asm__ volatile ("cli");
}

void sti() {
    __asm__ volatile ("sti");
}

void hlt() {
    __asm__ volatile("hlt");
}

void delay_cycles(unsigned int cycles) {
    while (cycles--)
    {
        __asm__ volatile ("pause");
    }
    
}

void test_io() {
    char testing[] = "Testing I/O Ports";
    for (int i = 0; testing[i] != '\0'; i++) {
        outb(0xE9, testing[i]); // qemu debug console port
    }
}

void kernel_main(void) {
    struct VGA_cursor cursor = {1, 1};

    disable_vga_cursor();
    cli();
    flush_gdt();
    terminal_write_current("[LOG] GDT Loaded", &cursor);
    install_idt();
    terminal_write_current("[LOG] IDT Loaded", &cursor);
    install_interrupt_handlers();
    pic_remap();
    terminal_write_current("[LOG] PIC Remap Successful!", &cursor);
    terminal_write_current("[LOG] Kernel Loaded. Redirecting...", &cursor);
    delay_cycles(10000000);
    terminal_clear();

    test_io();
    print_banner();
    delay_cycles(10000000);
    terminal_clear();
    sti();

    char buff[] = "blish~$ ";
    terminal_write(buff, 1, 1, GREEN_COLOR);

    while (1)
    {
      __asm__ volatile ("hlt"); // sleep kernel until a interrupt triggers 
    }
}