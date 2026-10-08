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

static int parse_int(const char *str)
{
    int sign = 1;
    int value = 0;

    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    while (*str >= '0' && *str <= '9') {
        value = value * 10 + (*str - '0');
        str++;
    }

    return sign * value;
}

static void itoa(int value, char *buffer)
{
    char reversed[sizeof(unsigned int) * 3];
    unsigned int magnitude;
    unsigned int digit_count = 0;
    unsigned int output_index = 0;
    int negative = value < 0;

    magnitude = negative ? 0u - (unsigned int)value : (unsigned int)value;

    do {
        reversed[digit_count++] = (char)('0' + magnitude % 10);
        magnitude /= 10;
    } while (magnitude != 0);

    if (negative) {
        buffer[output_index++] = '-';
    }

    while (digit_count > 0) {
        buffer[output_index++] = reversed[--digit_count];
    }

    buffer[output_index] = '\0';
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

    /*
    command calc structure: calc <operation> <operand1> <operand2>
    supported operations: add, sub, mul, div
    example: calc add 5 10
    */

    // Add more commands here as needed
    // basic parser for future commands, can be extended to support arguments and more complex commands
    char *argv[16];
    int argc = 0;
    char *p = input_buffer;

    while (*p) {
        while (*p && *p == ' ') {
            p++;
        }

        if (*p) {
            if (argc >= 16) {
                break;
            }

            argv[argc++] = p;

            while (*p && *p != ' ') {
                p++;
            }

            if (*p) {
                *p++ = '\0';
            }
        }
    }

    if (argc > 0) {
        if (streq(argv[0], "calc") == 1) {
            if (argc != 4) {
                cursor->y++;
                terminal_write("Usage: calc <operation> <operand1> <operand2>", 1, cursor->y++, RED_COLOR);
                return FAILURE;
            }

            const char *operation = argv[1];
            int operand1 = parse_int(argv[2]);
            int operand2 = parse_int(argv[3]);
            int result;

            if (streq(operation, "add") == 1) {
                result = operand1 + operand2;
            } else if (streq(operation, "sub") == 1) {
                result = operand1 - operand2;
            } else if (streq(operation, "mul") == 1) {
                result = operand1 * operand2;
            } else if (streq(operation, "div") == 1) {
                result = operand1 / operand2;
            } else {
                cursor->y++;
                terminal_write("Error: Unknown operation", 1, cursor->y++, RED_COLOR);
                return FAILURE;
            }

            char result_str[32];
            itoa(result, result_str);
            cursor->y++;
            terminal_write("Result: ", 1, cursor->y++, GREEN_COLOR);
            terminal_write(result_str, 9, cursor->y - 1, GREEN_COLOR);

            return SUCCESS;
        }
    }


    else {
        cursor->y++;
        terminal_write("Command not found sorry :(", 1, cursor->y++, RED_COLOR);
    }

    return FAILURE;
}