#include "include/io.h"
#include "include/kernel.h"

void outb(uint16_t port, uint8_t value) { io_outb(port, value); }
uint8_t inb(uint16_t port) {
    uint8_t inb_read = io_inb(port);
    return inb_read;
}