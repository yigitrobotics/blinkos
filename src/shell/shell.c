#include "../include/shell.h"

int streq(const char *a, const char *b)
{
    while (*a && *b) {
        if (*a != *b)
            return 0;

        a++;
        b++;
    }

    return *a == *b;
}

int shell(struct VGA_cursor *cursor, char input_buffer[]) {
    if (streq(input_buffer, "cl") == 1) {
        clear_with_shell(cursor);

        return SUCCESS;
    }

    else if (streq(input_buffer, "blf") == 1) {
        print_banner_little(cursor);
        
        return SUCCESS;
    }

    else {
        cursor->y++;
        terminal_write("Command not found sorry :(", 1, cursor->y++, RED_COLOR);
    }

    return FAILURE;
}