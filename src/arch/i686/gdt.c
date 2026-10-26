#include "kernel.h"
#include "gdt.h"
#include <stdint.h>

struct gdt_ptr
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

struct gdt_entry_struct {
    unsigned short limit_low;  
    unsigned short base_low; 
    unsigned char  base_middle;
    unsigned char  access;      
    unsigned char  granularity; 
    unsigned char  base_high;
} __attribute__((packed)); 

struct gdt_ptr gp;
extern void gdt_flush(uint32_t gdt_ptr_addr);
struct gdt_entry_struct gdt_entry[3];

void flush_gdt(void) {
    // Null descriptor of gdt
    gdt_entry[0].limit_low = 0x0000;
    gdt_entry[0].base_low = 0x0000;
    gdt_entry[0].base_middle = 0x00;
    gdt_entry[0].access = 0x00;
    gdt_entry[0].granularity = 0x00;
    gdt_entry[0].base_high = 0x00;

    // Kernel code segment
    gdt_entry[1].limit_low = 0xFFFF;
    gdt_entry[1].base_low = 0x0000;
    gdt_entry[1].base_middle = 0x00;
    gdt_entry[1].access = 0x9A;
    gdt_entry[1].granularity = 0xCF;
    gdt_entry[1].base_high = 0x00;

    // Kernel data segment
    gdt_entry[2].limit_low = 0xFFFF;
    gdt_entry[2].base_low = 0x0000;
    gdt_entry[2].base_middle = 0x00;
    gdt_entry[2].access = 0x92;
    gdt_entry[2].granularity = 0xCF;
    gdt_entry[2].base_high = 0x00;

    gp.limit = sizeof(gdt_entry) - 1;
    gp.base = (uint32_t)&gdt_entry;

    gdt_flush((uint32_t)&gp);
}