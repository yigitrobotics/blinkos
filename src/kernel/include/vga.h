#pragma once
#include "kernel.h"
#include <stdint.h>

#define TEXT_VGA_BUFFER ((volatile unsigned char *)0xB8000)
#define GRAY_COLOR 0x07
#define RED_COLOR 0x04
#define GREEN_COLOR 0x02

struct VGA_cursor
{
    int x;
    int y;
};

void terminal_write(const char msg[], int x, int y, uint8_t color);
void terminal_clear();
void terminal_write_current(const char msg[], struct VGA_cursor *vga_cursor_index);
void terminal_write_current_x(const char msg[], struct VGA_cursor *vga_cursor_index);
void clear_with_shell(struct VGA_cursor *cursor);
void print_banner();
void disable_vga_cursor(void);
void print_banner_little(struct VGA_cursor *cursor);