#pragma once

void panic(const char *msg);
void delay_cycles(unsigned int cycles);
void cli();
void sti();
void hlt();