#pragma once
#include <stdint.h>

// PIC ports
#define PIC_MASTER_CMD 0x20
#define PIC_MASTER_DATA 0x21
#define PIC_SLAVE_CMD 0xA0
#define PIC_SLAVE_DATA 0xA1

// PIC write definitions
#define PIC_INIT 0x11
#define PIC_MASTER_START 0x20 // from 32th port
#define PIC_SLAVE_START 0x28 // from 40th port
#define PIC_MASTER_IRQ2_RESERVE 0x04
#define PIC_SLAVE_IRQ2_RESERVE_CMD 0x02
#define PIC_MODE 0x01

extern void idt_load(uint32_t idt_ptr_addr);
void idt_set_gate(uint8_t num, uint32_t base);
void pic_remap(void);
void install_idt();
void install_interrupt_handlers();

struct idt_entry
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

extern uint64_t idt[256];
extern struct idt_entry idt_ptr;