#include "../include/vga.h"
#include "../include/kernel.h"
#include <stdarg.h>

__attribute__((noreturn))
void panic(const char *msg) {
    cli();

    int start_x = 1;
    int start_y = 3;

    terminal_clear();
    terminal_write("BLINK CRASH!", 1, 1, RED_COLOR);
    terminal_write(".-. .-')", start_x, start_y++, RED_COLOR);
    terminal_write("\\  ( x x )", start_x, start_y++, RED_COLOR);
    terminal_write(" ;-----.\\", start_x, start_y++, RED_COLOR);
    terminal_write(" | .-.  |", start_x, start_y++, RED_COLOR);
    terminal_write(" | '-' /_)", start_x, start_y++, RED_COLOR);
    terminal_write(" | .-. `.", start_x, start_y++, RED_COLOR);
    terminal_write(" | |  \\  |", start_x, start_y++, RED_COLOR);
    terminal_write(" | '--'  /", start_x, start_y++, RED_COLOR);
    terminal_write(" `------'", start_x, start_y++, RED_COLOR);

    terminal_write(msg, start_x, start_y++, GRAY_COLOR);

    while (1)
    {
        hlt();
    }
    
}