#include "../include/vga.h"

void print_banner() {
    terminal_write(".-. .-')                         .-') _ .-. .-')                 .-')", 1, 5, GREEN_COLOR);
    terminal_write("\\  ( OO )                       ( OO ) )\\  ( OO )               ( OO ).", 1, 6, GREEN_COLOR);
    terminal_write(" ;-----.\  ,--.      ,-.-') ,--./ ,--,' ,--. ,--.  .-'),-----. (_)---\\_)", 1, 7, GREEN_COLOR);
    terminal_write(" | .-.  |  |  |.-')  |  |OO)|   \\ |  |\\ |  .'   / ( OO'  .-.  '/    _ |", 1, 8, GREEN_COLOR);
    terminal_write(" | '-' /_) |  | OO ) |  |  \\|    \\|  | )|      /, /   |  | |  |\\  :` `.", 1, 9, GREEN_COLOR);
    terminal_write(" | .-. `.  |  |`-' | |  |(_/|  .     |/ |     ' _)_\\_) |  |\\|  | '..`''.)", 1, 10, GREEN_COLOR);
    terminal_write(" | |  \\  |(|  '---.',|  |_.'|  |\\    |  |  .   \\    \\ |  | |  |.-._)   \\", 1, 11, GREEN_COLOR);
    terminal_write(" | '--'  / |      |(_|  |   |  | \\   |  |  |\\   \\    `'  '-'  '\\       /", 1, 12, GREEN_COLOR);
    terminal_write(" `------'  `------'  `--'   `--'  `--'  `--' '--'      `-----'  `-----'", 1, 13, GREEN_COLOR);

    terminal_write("BlinkOS v0.2 by: YigitRobotics", 1, 14, GRAY_COLOR);
}

void print_banner_little(struct VGA_cursor *cursor) {
    int start_x = cursor->x;
    int start_y = cursor->y;

    start_y++;
    terminal_write(".-. .-')", start_x, start_y++, GREEN_COLOR);
    terminal_write("\\  ( OO )", start_x, start_y++, GREEN_COLOR);
    terminal_write(" ;-----.\\", start_x, start_y++, GREEN_COLOR);
    terminal_write(" | .-.  |", start_x, start_y++, GREEN_COLOR);
    terminal_write(" | '-' /_)", start_x, start_y++, GREEN_COLOR);
    terminal_write(" | .-. `.", start_x, start_y++, GREEN_COLOR);
    terminal_write(" | |  \\  |", start_x, start_y++, GREEN_COLOR);
    terminal_write(" | '--'  /", start_x, start_y++, GREEN_COLOR);
    terminal_write(" `------'", start_x, start_y++, GREEN_COLOR);

    terminal_write("BlinkOS v0.2 by: YigitRobotics",
                   start_x, start_y++, GREEN_COLOR);

    terminal_write("----------SUPPORTED COMMANDS----------",
                   start_x, start_y++, 0x1);

    terminal_write("> cl",
                   start_x, start_y++, GRAY_COLOR);

    terminal_write("> blf",
                   start_x, start_y++, GRAY_COLOR);

    cursor->y = start_y;
}