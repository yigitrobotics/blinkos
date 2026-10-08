#include "../include/interrupt.h"
#include "../include/vga.h"

static const char *exception_names[32] = {
    "Divide Error",
    "Debug",
    "NMI",
    "Breakpoint",
    "Overflow",
    "Bound Range Exceeded",
    "Invalid Op-Code",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segmentation Fault",
    "General Protection Fault",
    "Page Fault",
    "Reserved",
    "x87 FP Exception",
    "Align Check",
    "Machine Check",
    "SIMD FP Exception",
    "Virtual. Exception",
    "Control Protection Exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
};


void exception_handler(uint8_t vector_num) {
    if (vector_num >= 32) {
        panic("Unknown Exception");
    }

    panic(exception_names[vector_num]);
}