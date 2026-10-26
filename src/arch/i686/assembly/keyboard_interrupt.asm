[bits 32]
global keyboard_interrupt
extern keyboard_interrupt_c

keyboard_interrupt:
    pusha

    call keyboard_interrupt_c

    popa
    iretd