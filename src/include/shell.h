#pragma once
#include "../kernel/include/vga.h"

#define SUCCESS 1
#define FAILURE 0


int shell(struct VGA_cursor *cursor, char input_buffer[]);
