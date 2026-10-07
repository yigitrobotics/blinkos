#include "../include/vga.h"
#include "../include/kernel.h"
#include <stdarg.h>

__attribute__((noreturn))
void panic(const char *msg) {
    cli();

    terminal_clear();
    terminal_write("KERNEL PANIC!", 1, 1, RED_COLOR);
    terminal_write(msg, 2, 2, GRAY_COLOR);

    while (1)
    {
        hlt();
    }
    
}