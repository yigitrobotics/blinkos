; AI-generated file.
; This file is part of the BlinkOS kernel.
;
; Exception handling is not a current focus of development.
; This implementation was generated with AI assistance to avoid
; spending development time on repetitive exception stubs.
;
; I understand the general structure and some implementation details,
; but this file is intentionally treated as a generated component.

[bits 32]
extern exception_handler

%macro ISR_NO_ERROR 1
    global isr%+%1
    isr%+%1:
        push dword 0
        push dword %1
        jmp exception_common
%endmacro

%macro ISR_ERROR 1
    global isr%+%1
    isr%+%1:
        push dword %1
        jmp exception_common
%endmacro

%assign vector 0
%rep 32
    %if vector = 8 || vector = 10 || vector = 11 || vector = 12 || vector = 13 || vector = 14 || vector = 17 || vector = 20 || vector = 21 || vector = 29 || vector = 30
        ISR_ERROR vector
    %else
        ISR_NO_ERROR vector
    %endif
    %assign vector vector + 1
%endrep

exception_common:
    pusha
    push dword [esp + 32]
    call exception_handler
    add esp, 4
    popa
    add esp, 8
    iretd

section .rodata
global exception_stub_table
exception_stub_table:
%assign vector 0
%rep 32
    dd isr%+vector
    %assign vector vector + 1
%endrep
