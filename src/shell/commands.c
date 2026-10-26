#include "shell.h"
#include "io.h"

void sys_reboot(void) {
    outb(0x64, 0x4E);
    cli();
    hlt();
}