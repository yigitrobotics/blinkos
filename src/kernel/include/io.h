#pragma once
#include <stdint.h>

// assembly functions
extern void io_outb(uint16_t port, uint8_t value);
extern uint8_t io_inb(uint16_t port);

// C implementation
void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);