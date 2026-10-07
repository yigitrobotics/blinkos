#include "../include/keyboard.h"
#include "../include/io.h"
#include "../include/vga.h"
#include "../../include/shell.h"

#define SUCCESS 1
#define FAIL 0

static const char keyboard_scancode_map[128] = {
    [2] = '1', [3] = '2', [4] = '3', [5] = '4', [6] = '5',
    [7] = '6', [8] = '7', [9] = '8', [10] = '9', [11] = '0',

    [14] = '\b', // Backspace

    [16] = 'q', [17] = 'w', [18] = 'e', [19] = 'r', [20] = 't',
    [21] = 'y', [22] = 'u', [23] = 'i', [24] = 'o', [25] = 'p',

    [28] = '\n', // Enter

    [30] = 'a', [31] = 's', [32] = 'd', [33] = 'f', [34] = 'g',
    [35] = 'h', [36] = 'j', [37] = 'k', [38] = 'l',

    [44] = 'z', [45] = 'x', [46] = 'c', [47] = 'v', [48] = 'b',
    [49] = 'n', [50] = 'm',

    [57] = ' '
};

char input_buffer[KEYBOARD_INPUT_BUFFER];
int input_buffer_current_index = 0;

void terminal_text(struct VGA_cursor *vga_cursor) {
    terminal_write("blish~$ ", 1, vga_cursor->y, GREEN_COLOR);
}


void keyboard_interrupt_c() {
    static struct VGA_cursor cursor = {9, 1};
    uint8_t scancode = inb(0x60);
    outb(0x20, 0x20);

    if (cursor.y >= 25) {
        clear_with_shell(&cursor);
    }

    if (cursor.x >= 80) {
        cursor.y++;
        cursor.x = 1;
    }

    char output_attribute[2] = { keyboard_scancode_map[scancode], '\0' };

    if (scancode & 0x80 || keyboard_scancode_map[scancode] == '\0') {
        return;
    }
    if (keyboard_scancode_map[scancode] == '\b') {
        if (cursor.x <= 9) { return; }
        
        input_buffer[input_buffer_current_index] = '\0';
        input_buffer_current_index--;

        if (cursor.x == 1) {
            cursor.y--;
        }

        cursor.x--;

        char backspace_attribute[2] = { ' ', '\0'};
        terminal_write(backspace_attribute, cursor.x, cursor.y, GRAY_COLOR);
        return;
    }

    else if (keyboard_scancode_map[scancode] == '\n') {
        input_buffer[input_buffer_current_index] = '\0';
        int shell_return = shell(&cursor, input_buffer);

        input_buffer_current_index = 0;

        if (shell_return != SUCCESS) {
            cursor.y++;
            terminal_text(&cursor);
            cursor.x = 9;
    
        }
        return;
    }
    
    if (input_buffer_current_index >= KEYBOARD_INPUT_BUFFER - 1)
        return;

    terminal_write_current_x(output_attribute, &cursor);

    input_buffer[input_buffer_current_index++] = output_attribute[0];
}
