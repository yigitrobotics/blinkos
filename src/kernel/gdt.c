#include "include/kernel.h"
#include "include/gdt.h"
#include <stdint.h>

struct gdt_ptr
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

uint64_t gdt[3] = {
    0x0000000000000000ULL,
    0x00CF9A000000FFFFULL,
    0x00CF92000000FFFFULL
};

struct gdt_ptr gp;
extern void gdt_flush(uint32_t gdt_ptr_addr);

void flush_gdt(void) {
    gp.limit = sizeof(gdt) - 1;
    gp.base = (uint32_t)&gdt;

    gdt_flush((uint32_t)&gp);
}