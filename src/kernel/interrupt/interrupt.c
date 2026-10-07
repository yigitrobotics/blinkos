#include "../include/interrupt.h"
#include "../include/kernel.h"
#include "../include/vga.h"
#include "../include/io.h"
#include "../include/keyboard.h"
#include <stdint.h>

uint64_t idt[256];
struct idt_entry idt_ptr;

void pic_remap(void) {
    uint8_t master_mask = inb(PIC_MASTER_DATA);
    uint8_t slave_mask = inb(PIC_SLAVE_DATA);

    // icw1 - init
    outb(PIC_MASTER_CMD, PIC_INIT);
    outb(PIC_SLAVE_CMD, PIC_INIT);
    
    // icw2 - set INTR 32-48
    outb(PIC_MASTER_DATA, PIC_MASTER_START);
    outb(PIC_SLAVE_DATA, PIC_SLAVE_START);

    // icw3 - reserve irq2 for slave pic
    outb(PIC_MASTER_DATA, PIC_MASTER_IRQ2_RESERVE);
    outb(PIC_SLAVE_DATA, PIC_SLAVE_IRQ2_RESERVE_CMD);

    // icw4 - set 8086 mode
    outb(PIC_MASTER_DATA, PIC_MODE);
    outb(PIC_SLAVE_DATA, PIC_MODE);

    // giving mask again
    outb(PIC_MASTER_DATA, (master_mask | 0x01) & ~0x02);
    outb(PIC_SLAVE_DATA, slave_mask);
}

void idt_set_gate(uint8_t num, uint32_t base) {
    uint64_t entry = 0;
    
    entry |= (base & 0xFFFF0000ULL) << 32; // Base High (Bit 48..63)
    entry |= (0x8E00ULL) << 32;            // Flags (Bit 40..47)
    entry |= (0x080000ULL);                // Segment Selector = 0x08 (Code Segment)
    entry |= (base & 0x0000FFFFULL);       // Base Low (Bit 0..15)

    idt[num] = entry;
}

void install_idt() {
    idt_ptr.limit = (sizeof(uint64_t) * 256) - 1;
    idt_ptr.base = (uint32_t)&idt;

    for (int i = 0; i < 256; i++) {
        idt[i] = 0;
    }

    idt_load((uint32_t)&idt_ptr);
}


void install_interrupt_handlers() {
    idt_set_gate(0x21, (uint32_t)keyboard_interrupt);
}