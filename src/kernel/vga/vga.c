#include "../include/vga.h"
#include "../include/kernel.h"
#include <stdint.h>
#include "../include/io.h"

void terminal_write(const char msg[], int x, int y, uint8_t color) {
    int index = y * 80 + x; 
    for (int i = 0; msg[i] != '\0'; i++) {
        TEXT_VGA_BUFFER[(i + index) * 2] = msg[i];
        TEXT_VGA_BUFFER[(i + index) * 2 + 1] = color;
    }
}

void disable_vga_cursor(void) {
    outb(0x3d4, 0x0a);
    outb(0x3d5, 0x20);
}

void terminal_write_current(const char msg[], struct VGA_cursor *vga_cursor_index) {
    terminal_write(msg, vga_cursor_index->x, vga_cursor_index->y, GRAY_COLOR);
    vga_cursor_index->y++;
}

void terminal_write_current_x(const char msg[], struct VGA_cursor *vga_cursor_index) {
    terminal_write(msg, vga_cursor_index->x, vga_cursor_index->y, GRAY_COLOR);
    vga_cursor_index->x++;
} 

void clear_with_shell(struct VGA_cursor *cursor) {
        terminal_clear();
        terminal_write("blish~$ ", 1, 1, GREEN_COLOR);

        cursor->x = 9;
        cursor->y = 1;
}

void terminal_clear() {
    for (int i = 0; i < 2000; i++) {
        TEXT_VGA_BUFFER[i * 2] = ' ';
        TEXT_VGA_BUFFER[i * 2 + 1] = GRAY_COLOR;
    }
}