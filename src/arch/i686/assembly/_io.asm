[bits 32]
global io_outb
global io_inb

io_outb:
    mov dx, [esp + 4] ; port
    mov al, [esp + 8] ; value
    out dx, al ; outb
    ret

io_inb:
    mov dx, [esp + 4]
    in al, dx
    ret